/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdAfx.h"

void WorldSession::HandlePetAction(WorldPacket & recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		sLog.outDebug("HandlePetAction:Owner is not in world.Exiting");
		return;
	}

	//WorldPacket data;
	uint64 petGuid = 0;
	uint16 misc = 0;
	uint16 action = 0;

	uint64 targetguid = 0;
	recv_data >> petGuid >> misc >> action;
	//recv_data.hexlike();

	//printf("Pet_Action: 0x%.4X 0x%.4X\n", misc, action);

	if(action == PET_ACTION_ACTION && misc == PET_ACTION_DISMISS )
	{
		Vehicle *veh = _player->GetVehicle( );
		if( veh && veh->GetGUID() == petGuid )
			veh->RemovePassenger( _player );
	}
	if(GET_TYPE_FROM_GUID(petGuid) == HIGHGUID_TYPE_UNIT)
	{
		Creature *pCharm = GetPlayer()->GetMapMgr()->GetCreature( petGuid );
		if(!pCharm) 
		{ 
			sLog.outDebug("HandlePetAction:Could not find creature on this map. Exiting");
			return;
		}

		// must be a mind controled creature..
		if(action == PET_ACTION_ACTION)
		{
			recv_data >> targetguid;
			switch(misc)
			{
			case PET_ACTION_ATTACK:
				{
					if(!sEventMgr.HasEvent(_player, EVENT_PLAYER_CHARM_ATTACK))
					{
						uint32 timer = pCharm->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME);
						if(!timer) timer = 2000;

						sEventMgr.AddEvent(_player, &Player::_EventCharmAttack, EVENT_PLAYER_CHARM_ATTACK, timer, 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
						_player->_EventCharmAttack();
					}
				}break;
			}
		}
		sLog.outDebug("HandlePetAction:Finished handling simple summon case. Exiting");
		return;
	}

	Pet *pPet = _player->GetMapMgr()->GetPet( petGuid );
	
	if( !pPet )
	{ 
		sLog.outDebug("HandlePetAction:Could not find pet on this map. Exiting");
		return;
	}
	
	if( !pPet->isAlive() )
	{
		pPet->SendActionFeedback( PET_FEEDBACK_PET_DEAD );	
		sLog.outDebug("HandlePetAction:Pet is dead. Exiting");
		return;
	}

	Unit *pTarget = NULL;

	if(action == PET_ACTION_SPELL || action == PET_ACTION_SPELL_1 || action == PET_ACTION_SPELL_2 || (action == PET_ACTION_ACTION && misc == PET_ACTION_ATTACK )) // >> target
	{
		recv_data >> targetguid;
		pTarget = _player->GetMapMgr()->GetUnit(targetguid);
		if(!pTarget) pTarget = pPet;	// target self
	}

	switch(action)
	{
	case PET_ACTION_ACTION:
	case PET_ACTION_NOTDEF:
		{
			pPet->SetPetAction(misc);	   // set current action
			//make pet stand up
			if( misc!=PET_ACTION_STAY )// stand up 
				pPet->SetStandState( STANDSTATE_STAND );
			switch(misc)
			{
			case PET_ACTION_ATTACK:
				{
					// make sure the target is attackable
					if( pTarget == pPet || !isAttackable( pPet, pTarget ) )
 					{
						pPet->SendActionFeedback( PET_FEEDBACK_CANT_ATTACK_TARGET );
						sLog.outDebug("HandlePetAction:Unable to perform on non attackable target. Exiting");
						return;
					}

					// Clear the threat
					pPet->GetAIInterface()->WipeTargetList();
					pPet->GetAIInterface()->WipeHateList();

					// Attack target with melee if the owner if we dont have spells - other wise cast. All done by AIInterface.
					if(pPet->GetAIInterface()->getUnitToFollow() == NULL)
						pPet->GetAIInterface()->SetUnitToFollow(_player);

					// EVENT_PET_ATTACK
					pPet->GetAIInterface()->SetAIState(STATE_ATTACKING);
					pPet->GetAIInterface()->AttackReaction(pTarget, 1, 0);
					pPet->GetAIInterface()->m_forced_target = pTarget->GetGUID();	//should not let pet retarget other due to agro
				}break;
			case PET_ACTION_FOLLOW:
				{
					// Clear the threat
					pPet->GetAIInterface()->WipeTargetList();
					pPet->GetAIInterface()->WipeHateList();

					// Follow the owner... run to him...
					pPet->GetAIInterface()->SetUnitToFollow(_player);
					pPet->GetAIInterface()->HandleEvent(EVENT_FOLLOWOWNER, pPet, 0);
				}break;
			case PET_ACTION_STAY:
				{
					// Clear the threat
					pPet->GetAIInterface()->WipeTargetList();
					pPet->GetAIInterface()->WipeHateList();
					pPet->GetAIInterface()->m_forced_target = 0;

					// Stop following the owner, and sit.
					pPet->GetAIInterface()->SetUnitToFollow(NULL);
					pPet->SetStandState(STANDSTATE_SIT);
				}break;
			case PET_ACTION_DISMISS:
				{
					// Bye byte...
					pPet->Dismiss();
				}break;
			}
		}break;

	case PET_ACTION_SPELL_2:
	case PET_ACTION_SPELL_1:
	case PET_ACTION_SPELL:
		{
			// misc == spellid
			SpellEntry * entry = dbcSpell.LookupEntry( misc );
			if( entry == NULL ) 
			{ 
				sLog.outDebug("HandlePetAction:Could not find spell with id %u. Exiting",misc);
				return;
			}

			AI_Spell * sp = pPet->GetAISpellForSpellId( entry->Id );
			if( sp != NULL )
			{
				// Check the cooldown
				if(sp->cooldowntime && getMSTime() < sp->cooldowntime)
				{
					pPet->SendCastFailed( misc, SPELL_FAILED_NOT_READY );
					sLog.outDebug("HandlePetAction:Spell is cooling down. Exiting");
					return;
				}
				else
				{
//					if( ( entry->c_is_flags & SPELL_FLAG_IS_BUFF ) == 0 )
					{
						// make sure the target is attackable if spell is a bad spell for us. Need to define what is a negative spell :(
//						if( pTarget != pPet && pTarget != _player && !isAttackable( pPet, pTarget ) )
						if( (entry->c_is_flags & SPELL_FLAG_IS_DAMAGING) && !isAttackable( pPet, pTarget ) )
						{
							pPet->SendActionFeedback( PET_FEEDBACK_CANT_ATTACK_TARGET );
							sLog.outDebug("HandlePetAction:Target is not attackable. Exiting");
							return;
						}
					}

					if(sp->autocast_type != AUTOCAST_EVENT_ATTACK)
					{
//						if(sp->autocast_type == AUTOCAST_EVENT_OWNER_ATTACKED)
//							pPet->CastSpell(_player, sp->spell, false);
//						else
//							pPet->CastSpell(pPet, sp->spell, false);
							pPet->CastSpell(pTarget, sp->spell, false);
					}
					//should we always agro our spell cast target ? Ex: sucubus invisibility
					else if( isAttackable( pPet, pTarget ) == true )
					{
						// Clear the threat
						pPet->GetAIInterface()->WipeTargetList();
						pPet->GetAIInterface()->WipeHateList();

						pPet->GetAIInterface()->AttackReaction(pTarget, 1, 0);
						pPet->GetAIInterface()->SetNextSpell(sp);
						pPet->GetAIInterface()->m_forced_target = pTarget->GetGUID();	//should not let pet retarget other due to agro
					}
				}
			}
			else
				sLog.outDebug("HandlePetAction:Pet does not have spell %u(cheat ?). Exiting",misc);
		}break;
	case PET_ACTION_STATE:
		{
			pPet->SetPetState(misc);
		}break;
	default:
		{
			printf("WARNING: Unknown pet action received. Action = %.4X, Misc = %.4X\n", action, misc);
		}break;
	}

	/* Send pet action sound - WHEE THEY TALK */
	WorldPacket actionp(SMSG_PET_ACTION_SOUND, 12);
	actionp << pPet->GetGUID() << uint32(1);
	SendPacket(&actionp);
}

void WorldSession::HandlePetInfo(WorldPacket & recv_data)
{
	//nothing
	sLog.outDebug("HandlePetInfo is called");
}

void WorldSession::HandlePetNameQuery(WorldPacket & recv_data)
{
	sLog.outDebug("Received CMSG_PET_NAME_QUERY ");
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	uint32 petNumber = 0;
	uint64 petGuid = 0;

	recv_data >> petNumber >> petGuid;
	Pet *pPet = _player->GetMapMgr()->GetPet( petGuid ) ;
	if(!pPet)
	{ 
		return;
	}

	WorldPacket data(8 + pPet->GetName()->size());
	data.SetOpcode(SMSG_PET_NAME_QUERY_RESPONSE);
	data << pPet->GetUInt32Value( UNIT_FIELD_PETNUMBER );
	data << pPet->GetName()->c_str();
	data << pPet->GetUInt32Value(UNIT_FIELD_PET_NAME_TIMESTAMP);		// stops packet flood
	SendPacket(&data);
}

void WorldSession::HandleStablePet(WorldPacket & recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		sLog.outDebug("HandleStablePet: we are not ingame.Exiting");
		return;
	}

	// remove pet from world and association with player
	Pet *pPet = _player->GetSummon();
	if(pPet && pPet->GetUInt32Value(UNIT_CREATED_BY_SPELL) != 0) 
	{ 
		sLog.outDebug("HandleStablePet: Pet was created by spell.Exiting");
		return;
	}
	
	PlayerPet *pet = _player->GetPlayerPet(_player->GetUnstabledPetNumber());
	if(!pet) 
	{ 
		sLog.outDebug("HandleStablePet: Player has no active pet summoned.Exiting");
		return;
	}
	pet->stablestate = STABLE_STATE_PASSIVE;
	
	if(pPet) 
		pPet->Remove(true, true);	// no safedelete needed

	WorldPacket data(1);
	data.SetOpcode(SMSG_STABLE_RESULT);
	data << uint8(0x8);  // success
	SendPacket(&data);
}

void WorldSession::HandleUnstablePet(WorldPacket & recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	
	uint64 npcguid = 0;
	uint32 petnumber = 0;

	recv_data >> npcguid >> petnumber;
	PlayerPet *pet = _player->GetPlayerPet(petnumber);
	if(!pet)
	{
		sLog.outError("PET SYSTEM: Player "I64FMT" tried to unstable non-existant pet %d", _player->GetGUID(), petnumber);
		return;
	}
	_player->SpawnPet(petnumber);
	pet->stablestate = STABLE_STATE_ACTIVE;

	WorldPacket data(1);
	data.SetOpcode(SMSG_STABLE_RESULT);
	data << uint8(0x9); // success?
	SendPacket(&data);
}
void WorldSession::HandleStableSwapPet(WorldPacket & recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}

	uint64 npcguid = 0;
	uint32 petnumber = 0;
	recv_data >> npcguid >> petnumber;

	PlayerPet *pet = _player->GetPlayerPet(petnumber);
	if(!pet)
	{
		sLog.outError("PET SYSTEM: Player "I64FMT" tried to unstable non-existant pet %d", _player->GetGUID(), petnumber);
		return;
	}
	Pet *pPet = _player->GetSummon();
	if(pPet && pPet->GetUInt32Value(UNIT_CREATED_BY_SPELL) != 0) 
	{ 
		return;
	}

	//stable current pet
	PlayerPet *pet2 = _player->GetPlayerPet(_player->GetUnstabledPetNumber());
	if(!pet2) 
	{ 
		return;
	}
	if(pPet)
		pPet->Remove(true, true);	// no safedelete needed
	pet2->stablestate = STABLE_STATE_PASSIVE;

	//unstable selected pet
	_player->SpawnPet(petnumber);
	pet->stablestate = STABLE_STATE_ACTIVE;

	WorldPacket data;
	data.SetOpcode(SMSG_STABLE_RESULT);
	data << uint8(0x09);
	SendPacket(&data);
}

void WorldSession::HandleStabledPetList(WorldPacket & recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	uint64 npcguid = 0;
	recv_data >> npcguid;
	SendStabledPetList( npcguid );
}

void WorldSession::SendStabledPetList(uint64 GUID)
{
	if( _player == NULL || !_player->IsInWorld() ) 
	{ 
		return;
	}
	sStackWolrdPacket( data, MSG_LIST_STABLED_PETS, 10 + 15 * 35 + 30);

	data << GUID;

	data << uint8(_player->m_Pets.size());
	data << uint8(_player->m_StableSlotCount);
	char i=0;
	for(std::map<uint32, PlayerPet*>::iterator itr = _player->m_Pets.begin(); itr != _player->m_Pets.end(); ++itr)
	{
		data << uint32(itr->first); // pet no
		data << uint32(itr->second->entry); // entryid
		data << uint32(itr->second->level); // level
		data << itr->second->name;		  // name
//		data << uint32(itr->second->loyaltylvl); //no more loyalty
		if(itr->second->stablestate == STABLE_STATE_ACTIVE)
			data << uint8(STABLE_STATE_ACTIVE);
		else
		{
			data << uint8(STABLE_STATE_PASSIVE + i);
			i++;
		}
	}

	SendPacket(&data);
}

void WorldSession::HandleBuyStableSlot(WorldPacket &recv_data)
{
	if( !_player->IsInWorld() || _player->GetStableSlotCount() >= 4 ) 
	{ 
		return;
	}

	BankSlotPrice* bsp = dbcStableSlotPrices.LookupEntry( _player->GetStableSlotCount() + 1 );
	int32 cost = ( bsp != NULL ) ? bsp->Price : 99999999;
	
	WorldPacket data( SMSG_STABLE_RESULT, 1 );
	
	if( cost > (int32)_player->GetGold( ) )
	{
		data << uint8(1); // not enough money
		SendPacket( &data );
 		return;
	}
 	_player->ModGold( -cost );
 	
	data << uint8( 0x0A );
	SendPacket( &data );
 	
	_player->m_StableSlotCount++;
}


void WorldSession::HandlePetSetActionOpcode(WorldPacket& recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	uint32 unk1;
	uint32 unk2;
	uint32 slot;
	uint16 spell;
	uint16 state;
	recv_data >> unk1 >> unk2 >> slot >> spell >> state;

	if( slot >= PET_ACTIONBAR_MAXSIZE )
	{ 
		return;
	}

	if(!_player->GetSummon())
	{ 
		return;
	}

	Pet * pet = _player->GetSummon();
	SpellEntry * spe = dbcSpell.LookupEntryForced( spell );
	if( spe == NULL )
	{ 
		return;
	}

	// do we have the spell? if not don't set it (exploit fix)
	PetSpellMap::iterator itr = pet->GetSpells()->find( spe );
	if( itr == pet->GetSpells()->end( ) )
	{ 
		return;
	}
	pet->ActionBar[slot] = spell;
	pet->SetSpellState(spell, state);
}

void WorldSession::HandlePetRename(WorldPacket & recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	uint64 guid;
	string name;
	recv_data >> guid >> name;

	if(!_player->GetSummon() || _player->GetSummon()->GetGUID() != guid)
	{
		sChatHandler.SystemMessage(this, "That pet is not your current pet, or you do not have a pet.");
		return;
	}

	Pet * pet = _player->GetSummon();
	pet->Rename(name);

	// Disable pet rename.
//	pet->SetUInt32Value(UNIT_FIELD_BYTES_2, 1 | (0x28 << 8) | (0x2 << 16));
	pet->SetUInt32Value( UNIT_FIELD_BYTES_2, U_FIELD_BYTES_ANIMATION_FROZEN | (UNIT_BYTE2_FLAG_PET_DETAILS << 16) );// 0x3 -> Enable pet rename.
}

void WorldSession::HandlePetAbandon(WorldPacket & recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	Pet * pet = _player->GetSummon();
	if(!pet) 
	{ 
		return;
	}

	pet->Dismiss();
}

void WorldSession::HandlePetUnlearn(WorldPacket & recv_data)
{
	if( !_player->IsInWorld() )
	{ 
		return;
	}

	uint64 guid;
	recv_data >> guid;

	Pet* pPet = _player->GetSummon();
	if( pPet == NULL || pPet->GetGUID() != guid )
	{
		sChatHandler.SystemMessage(this, "That pet is not your current pet, or you do not have a pet.");
		return;
	}

	int32 cost = pPet->GetUntrainCost();
	if( cost > ( int32 )_player->GetGold( ) )
	{
		WorldPacket data(SMSG_BUY_FAILED, 12);
		data << uint64( _player->GetGUID() );
		data << uint32( 0 );
		data << uint8( 2 );		//not enough money
		return;	
	}
	_player->ModGold( -cost );
	pPet->WipeTalents();
	pPet->SetTalentPoints( pPet->GetTalentPointsForLevel( pPet->getLevel() ) );
}

void WorldSession::HandlePetSpellAutocast( WorldPacket& recvPacket )
{
	// handles toggle autocast from spellbook
	if( !_player->IsInWorld() )
	{ 
		return;
	}

	uint64 guid;
    uint16 spellid;
    uint16 unk;
    uint8  state;
    recvPacket >> guid >> spellid >> unk >> state;

	Pet * pPet = _player->GetSummon();
	if( pPet == NULL )
	{ 
		return;
	}
	
	SpellEntry * spe = dbcSpell.LookupEntryForced( spellid );
	if( spe == NULL )
	{ 
		return;
	}
	
	// do we have the spell? if not don't set it (exploit fix)
	PetSpellMap::iterator itr = pPet->GetSpells()->find( spe );
	if( itr == pPet->GetSpells()->end( ) )
	{ 
		return;
	}

	pPet->SetSpellState( spellid, state > 0 ? AUTOCAST_SPELL_STATE : DEFAULT_SPELL_STATE );
}
void WorldSession::HandlePetCancelAura( WorldPacket& recvPacket )
{
	if( !_player->IsInWorld() )
	{ 
		return;
	}

	uint64 guid;
    uint16 spellid;

	recvPacket >> guid >> spellid;

	Pet * pPet = _player->GetSummon();
	if( pPet == NULL )
	{ 
		return;
	}

	if( !pPet->RemoveAura( spellid ) )
		sLog.outError("PET SYSTEM: Player "I64FMT" failed to cancel aura %u from pet", _player->GetGUID(), spellid );
}

void WorldSession::HandlePetLearnTalent( WorldPacket & recvPacket )
{
	if( !_player->IsInWorld() )
	{ 
		return;
	}

	uint64 guid;
    uint32 talentid;
	uint32 talentcol;

	recvPacket >> guid >> talentid >> talentcol;

	Pet * pPet = _player->GetSummon();
	if( pPet == NULL )
	{ 
		return;
	}
	pPet->LearnTalent( talentid, talentcol, false );
}

void WorldSession::HandlePetLearnPreviewTalent( WorldPacket & recvPacket )
{
    uint32 talentcount;
    uint32 talentid;
    uint32 rank;

    sLog.outDebug("Recieved packet CMSG_LEARN_PREVIEW_TALENTS_PET.");

    if( !_player->IsInWorld() )
        return;

	uint64 guid;
	recvPacket >> guid;

	Pet * pPet = _player->GetSummon();
	if( pPet == NULL )
	{ 
		return;
	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 0x04C1 CMSG_LEARN_TALENTS_MULTIPLE
    //  As of 3.2.2.10550 the client sends this packet when clicking "learn" on the talent interface (in preview talents mode)
    //  This packet tells the server which talents to learn
    //
    // Structure:
    //
    // struct talentdata{
    //  uint32 talentid;                - unique numeric identifier of the talent (index of talent.dbc)
    //  uint32 talentrank;              - rank of the talent
    //  };
    //
    // uint32 talentcount;              - number of talentid-rank pairs in the packet
    // talentdata[ talentcount ];
    //  
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    recvPacket >> talentcount;

    for( uint32 i = 0; i < talentcount; ++i )
    {
        recvPacket >> talentid;
        recvPacket >> rank;

        pPet->LearnTalent( talentid, rank, true );
    }
}