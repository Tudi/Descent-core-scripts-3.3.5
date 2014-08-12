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

void WorldSession::HandleRepopRequestOpcode( WorldPacket & recv_data )
{
	sLog.outDebug( "WORLD: Recvd CMSG_REPOP_REQUEST Message" );

	if(_player->getDeathState() != JUST_DIED)
	{ 
		return;
	}

	if(_player->m_CurrentTransporter)
		_player->m_CurrentTransporter->RemovePlayer(_player);

	if( GetPlayer() )
	  GetPlayer()->RepopRequestedPlayer();
}

void WorldSession::HandleAutostoreLootItemOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
//	uint8 slot = 0;
	uint32 itemid = 0;
	uint32 amt = 1;
	uint8 lootSlot = 0;
	uint8 error = 0;
	SlotResult slotresult;

	Item *add;
	Loot *pLoot = NULL;

	if(_player->isCasting())
		_player->InterruptSpell();
	GameObject * pGO = NULL;
	Creature * pCreature = NULL;

	uint32 guidtype = GET_TYPE_FROM_GUID(_player->GetLootGUID());
	if(guidtype == HIGHGUID_TYPE_UNIT)
	{
		pCreature = _player->GetMapMgr()->GetCreature( GetPlayer()->GetLootGUID() );
		if (!pCreature)
		{ 
			return;
		}
		//anti ninja, If we are not the tagger then don't steal loot. Can be done with packet hacks or group leave
		if( !(pCreature->TaggerGroupId == _player->GetGroup() || ( pCreature->TaggerGroupId == NULL && pCreature->TaggerGuid == _player->GetGUID() ) ) )
		{
			return;
		}
		pLoot=&pCreature->loot;
	}
	else if(guidtype == HIGHGUID_TYPE_GAMEOBJECT)
	{
		pGO = _player->GetMapMgr()->GetGameObject( GetPlayer()->GetLootGUID() );
		if(!pGO)
		{ 
			return;
		}
		pLoot=&pGO->loot;
	}else if( guidtype == HIGHGUID_TYPE_ITEM )
	{
		Item *pItem = _player->GetItemInterface()->GetItemByGUID(_player->GetLootGUID());
		if(!pItem)
		{ 
			return;
		}
		pLoot = pItem->loot;
	}else if( guidtype == HIGHGUID_TYPE_PLAYER )
	{
		Player * pl = _player->GetMapMgr()->GetPlayer( GetPlayer()->GetLootGUID() );
		if(!pl) 
		{ 
			return;
		}
		pLoot = &pl->loot;
	}

	if(!pLoot) 
	{ 
		return;
	}

	recv_data >> lootSlot;
	if (lootSlot >= pLoot->items.size())
	{
		sLog.outDebug("AutoLootItem: Player %s might be using a hack! (slot %d, size %d)",GetPlayer()->GetName(), lootSlot, pLoot->items.size());
		return;
	}

	amt = pLoot->items.at(lootSlot).iItemsCount;
	if( pLoot->items.at(lootSlot).roll != NULL )
	{ 
		return;
	}

	if (!pLoot->items.at(lootSlot).ffa_loot)
	{
		if (!amt)//Test for party loot
		{  
			GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL,INV_ERR_ALREADY_LOOTED);
			return;
		}
	}
	else
	{
		//make sure this player can still loot it in case of ffa_loot
		LooterSet::iterator itr = pLoot->items.at(lootSlot).has_looted.find(_player->GetLowGUID());

		if (pLoot->items.at(lootSlot).has_looted.end() != itr)
		{
			GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL,INV_ERR_ALREADY_LOOTED);
			return;
		}
	}

	itemid = pLoot->items.at(lootSlot).item.itemproto->ItemId;
	ItemPrototype* it = pLoot->items.at(lootSlot).item.itemproto;

	if((error = _player->GetItemInterface()->CanReceiveItem(it, 1)) != 0)
	{
		_player->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, error);
		return;
	}

	if(pGO)
	{
		CALL_GO_SCRIPT_EVENT(pGO, OnLootTaken)(_player, it);
	}
	else if(pCreature)
		CALL_SCRIPT_EVENT(pCreature, OnLootTaken)(_player, it);

	add = GetPlayer()->GetItemInterface()->FindItemLessMax(itemid, amt, false);
	sHookInterface.OnLoot(_player, pCreature, 0, itemid);
	if (!add)
	{
		slotresult = GetPlayer()->GetItemInterface()->FindFreeInventorySlot(it);
		if(!slotresult.Result)
		{
			GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_INVENTORY_FULL);
			return;
		}
	
		sLog.outDebug("AutoLootItem MISC");
		Item *item = objmgr.CreateItem( itemid, GetPlayer());

		item->SetUInt32Value(ITEM_FIELD_STACK_COUNT,amt);
		if(pLoot->items.at(lootSlot).iRandomProperty!=NULL)
		{
			item->SetRandomProperty(pLoot->items.at(lootSlot).iRandomProperty->ID);
			item->ApplyRandomProperties(false);
		}
		else if(pLoot->items.at(lootSlot).iRandomSuffix != NULL)
		{
			item->SetRandomSuffix(pLoot->items.at(lootSlot).iRandomSuffix->id);
			item->ApplyRandomProperties(false);
		}

		AddItemResult res = GetPlayer()->GetItemInterface()->SafeAddItem(item,slotresult.ContainerSlot, slotresult.Slot);
		if( res == ADD_ITEM_RESULT_OK )
		{
			sQuestMgr.OnPlayerItemPickup(GetPlayer(),item);
			_player->GetSession()->SendItemPushResult(item,false,true,true,true,slotresult.ContainerSlot,slotresult.Slot,1);
		}
		else if( res == ADD_ITEM_RESULT_ERROR )
		{
			item->DeleteMe();
			item = NULL;
		}
	}
	else 
	{	
		add->SetCount(add->GetUInt32Value(ITEM_FIELD_STACK_COUNT) + amt);
		add->m_isDirty = true;

		sQuestMgr.OnPlayerItemPickup(GetPlayer(),add);
		_player->GetSession()->SendItemPushResult(add, false, false, true, false, _player->GetItemInterface()->GetBagSlotByGuid(add->GetGUID()), 0xFFFFFFFF,amt);
	}

	_player->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM,itemid,ACHIEVEMENT_UNUSED_FIELD_VALUE,amt,ACHIEVEMENT_EVENT_ACTION_ADD);
	if( it->Quality == ITEM_QUALITY_EPIC_PURPLE )
		_player->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_LOOT_EPIC_ITEM,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,amt,ACHIEVEMENT_EVENT_ACTION_ADD);

	//in case of ffa_loot update only the player who recives it.
	if (!pLoot->items.at(lootSlot).ffa_loot)
	{
		pLoot->items.at(lootSlot).iItemsCount = 0;

		// this gets sent to all looters
		WorldPacket data(1);
		data.SetOpcode(SMSG_LOOT_REMOVED);
		data << lootSlot;
		Player * plr;
		for(LooterSet::iterator itr = pLoot->looters.begin(); itr != pLoot->looters.end(); ++itr)
		{
			if((plr = _player->GetMapMgr()->GetPlayer(*itr)) != 0)
				plr->GetSession()->SendPacket(&data);
		}
	}
	else
	{
		pLoot->items.at(lootSlot).has_looted.insert(_player->GetLowGUID());
		WorldPacket data(1);
		data.SetOpcode(SMSG_LOOT_REMOVED);
		data << lootSlot;
		_player->GetSession()->SendPacket(&data);
	}

/*    WorldPacket idata(45);
    if(it->Class == ITEM_CLASS_QUEST)
    {
        uint32 pcount = _player->GetItemInterface()->GetItemCount(it->ItemId, true);
		BuildItemPushResult(&idata, _player->GetGUID(), ITEM_PUSH_TYPE_LOOT, amt, itemid, pLoot->items.at(lootSlot).iRandomProperty ? pLoot->items.at(lootSlot).iRandomProperty->ID : 0,0xFF,0,0xFFFFFFFF,pcount);
    }
	else BuildItemPushResult(&idata, _player->GetGUID(), ITEM_PUSH_TYPE_LOOT, amt, itemid, pLoot->items.at(lootSlot).iRandomProperty ? pLoot->items.at(lootSlot).iRandomProperty->ID : 0);

	if(_player->InGroup())
		_player->GetGroup()->SendPacketToAll(&idata);
	else
		SendPacket(&idata);*/

	/* any left yet? (for fishing bobbers) */
	if(pGO && pGO->GetEntry() ==GO_FISHING_BOBBER)
	{
		int count=0;
		for(vector<__LootItem>::iterator itr = pLoot->items.begin(); itr != pLoot->items.end(); ++itr)
			count += (*itr).iItemsCount;
		if(!count)
			pGO->ExpireAndDelete();
	}
}

void WorldSession::HandleLootMoneyOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	Loot * pLoot = NULL;
	uint64 lootguid=GetPlayer()->GetLootGUID();
	if(!lootguid)
		return;   // duno why this happens

	if(_player->isCasting())
		_player->InterruptSpell();

	WorldPacket pkt;	
	Unit * pt = 0;
	uint32 guidtype = GET_TYPE_FROM_GUID(lootguid);

	if(guidtype == HIGHGUID_TYPE_UNIT)
	{
		Creature* pCreature = _player->GetMapMgr()->GetCreature( lootguid );
		if(!pCreature)
		{ 
			return;
		}
		//anti ninja, If we are not the tagger then don't steal loot. Can be done with packet hacks or group leave
		if( !(pCreature->TaggerGroupId == _player->GetGroup() || ( pCreature->TaggerGroupId == NULL && pCreature->TaggerGuid == _player->GetGUID() ) ) )
		{
			return;
		}
		pLoot=&pCreature->loot;
		pt = pCreature;
	}
	else if(guidtype == HIGHGUID_TYPE_GAMEOBJECT)
	{
		GameObject* pGO = _player->GetMapMgr()->GetGameObject( lootguid );
		if(!pGO)
		{ 
			return;
		}
		pLoot=&pGO->loot;
	}
	else if(guidtype == HIGHGUID_TYPE_CORPSE)
	{
		Corpse *pCorpse = objmgr.GetCorpse((uint32)lootguid);
		if(!pCorpse)
		{ 
			return;
		}
		pLoot=&pCorpse->loot;
	}
	else if(guidtype == HIGHGUID_TYPE_PLAYER)
	{
		Player * pPlayer = _player->GetMapMgr()->GetPlayer( lootguid );
		if(!pPlayer) 
		{ 
			return;
		}
		pLoot = &pPlayer->loot;
		pPlayer->bShouldHaveLootableOnCorpse = false;
		pt = pPlayer;
	}
	else if( guidtype == HIGHGUID_TYPE_ITEM )
	{
		Item *pItem = _player->GetItemInterface()->GetItemByGUID(lootguid);
		if(!pItem)
		{ 
			return;
		}
		pLoot = pItem->loot;
	}

	if (!pLoot)
	{
		//bitch about cheating maybe?
		return;
	}

	uint32 money = pLoot->gold;

	pLoot->gold=0;
	WorldPacket data(1);
	data.SetOpcode(SMSG_LOOT_CLEAR_MONEY);
	// send to all looters
	Player * plr;
	for(LooterSet::iterator itr = pLoot->looters.begin(); itr != pLoot->looters.end(); ++itr)
	{
		if((plr = _player->GetMapMgr()->GetPlayer(*itr)) != 0)
			plr->GetSession()->SendPacket(&data);
	}

	if(!_player->InGroup())
	{
		if(money)
		{
			GetPlayer()->ModGold( money);
			GetPlayer()->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,money,ACHIEVEMENT_EVENT_ACTION_ADD);
			sHookInterface.OnLoot(_player, pt, money, 0);
		}
	}
	else
	{
		//this code is wrong mustbe party not raid!
		Group* party = _player->GetGroup();
		if(party)
		{
			/*uint32 share = money/party->MemberCount();*/
			vector<Player*> targets;
			targets.reserve(party->MemberCount());

			GroupMembersSet::iterator itr;
			SubGroup * sgrp;
			party->getLock().Acquire();
			for(uint32 i = 0; i < party->GetSubGroupCount(); i++)
			{
				sgrp = party->GetSubGroup(i);
				for(itr = sgrp->GetGroupMembersBegin(); itr != sgrp->GetGroupMembersEnd(); ++itr)
				{
					if((*itr)->m_loggedInPlayer 
						&& (*itr)->m_loggedInPlayer->GetMapMgr() == _player->GetMapMgr() 
						&& _player->GetDistanceSq((*itr)->m_loggedInPlayer)<100*100
						)
						targets.push_back((*itr)->m_loggedInPlayer);
				}
			}
			party->getLock().Release();

			if(!targets.size())
			{ 
				return;
			}

			uint32 share = money / uint32(targets.size());

			pkt.SetOpcode(SMSG_LOOT_MONEY_NOTIFY);
			pkt << share;

			for(vector<Player*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
			{
				(*itr)->ModGold( share);
				(*itr)->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,share,ACHIEVEMENT_EVENT_ACTION_ADD);
				(*itr)->GetSession()->SendPacket(&pkt);
			}
		}
	}   
}

void WorldSession::HandleLootOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld())
	{ 
		return;
	}

	uint64 guid;
	recv_data >> guid;

	if(_player->isCasting())
		_player->InterruptSpell();
		
	_player->RemoveStealth(); // ceberwow:RemoveStealth when looting. Blizzlike

	if(_player->InGroup() && !_player->m_bg)
	{
		Group * party = _player->GetGroup();
		if(party)
		{
			if(party->GetMethod() == PARTY_LOOT_MASTER)
			{				
				WorldPacket data(SMSG_LOOT_MASTER_LIST, 330);  // wont be any larger
				data << (uint8)party->MemberCount();
				uint32 real_count = 0;
				SubGroup *s;
				GroupMembersSet::iterator itr;
				party->Lock();
				for(uint32 i = 0; i < party->GetSubGroupCount(); ++i)
				{
					s = party->GetSubGroup(i);
					for(itr = s->GetGroupMembersBegin(); itr != s->GetGroupMembersEnd(); ++itr)
					{
						if((*itr)->m_loggedInPlayer && _player->GetZoneId() == (*itr)->m_loggedInPlayer->GetZoneId())
						{
							data << (*itr)->m_loggedInPlayer->GetGUID();
							++real_count;
						}
					}
				}
				party->Unlock();
				*(uint8*)&data.contents()[0] = real_count;

				party->SendPacketToAll(&data);
			}
/*			//this commented code is not used because it was never tested and finished !
			else if(party->GetMethod() == PARTY_LOOT_RR)
			{
				Creature *target=GetPlayer()->GetMapMgr()->GetCreature(guid); //maybe we should extend this to other object types too
				if(target)
				{
					if(target->TaggerGuid==GetPlayer()->GetGUID())
						GetPlayer()->SendLoot(guid,LOOT_CORPSE);
					else return;
				}
			}*/
		}	
	}
	//not sure if 1 should be used here, found only fishing and disenchant in DBC
//	GetPlayer()->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE,1,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	GetPlayer()->SendLoot(guid,LOOT_CORPSE);
}


void WorldSession::HandleLootReleaseOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	uint64 guid;

	recv_data >> guid;

	WorldPacket data(SMSG_LOOT_RELEASE_RESPONSE, 9);
	data << guid << uint8( 1 );
	SendPacket( &data );

	_player->SetLootGUID(0);
	_player->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOOTING);
	_player->m_currentLoot = 0;

	if( GET_TYPE_FROM_GUID( guid ) == HIGHGUID_TYPE_UNIT )
	{
		Creature* pCreature = _player->GetMapMgr()->GetCreature( guid );
		if( pCreature == NULL )
		{ 
			return;
		}
		// remove from looter set
		pCreature->loot.looters.erase(_player->GetLowGUID());
		if( pCreature->loot.gold <= 0)
		{			
			for( std::vector<__LootItem>::iterator i = pCreature->loot.items.begin(); i != pCreature->loot.items.end(); i++ )
			if( i->iItemsCount > 0 )
			{
				ItemPrototype* proto = i->item.itemproto;
				if( proto->Class != ITEM_CLASS_QUEST )
				{ 
					return;
				}
				if( _player->HasQuestForItem( i->item.itemproto->ItemId ) )
				{ 
					return;
				}
			}
			pCreature->BuildFieldUpdatePacket( _player, UNIT_DYNAMIC_FLAGS, 0 );

			if( !pCreature->Skinned )
			{
				if( lootmgr.IsSkinnable( pCreature->GetEntry() ) )
				{
					pCreature->BuildFieldUpdatePacket( _player, UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE );
				}
			}
		}
	}
	else if( GET_TYPE_FROM_GUID( guid ) == HIGHGUID_TYPE_GAMEOBJECT )
	{
		GameObject* pGO = _player->GetMapMgr()->GetGameObject( guid );
		if( pGO == NULL || pGO->IsInWorld() == false )
		{ 
			return;
		}

		switch( pGO->GetByte( GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPEID ) )
		{
		case GAMEOBJECT_TYPE_FISHINGNODE:
			{
				pGO->loot.looters.erase(_player->GetLowGUID());
				if(pGO->IsInWorld())
				{
					pGO->RemoveFromWorld(true);
				}
				sGarbageCollection.AddObject( pGO );
				pGO = NULL;
			}break;
		case GAMEOBJECT_TYPE_CHEST:
			{
				pGO->loot.looters.erase( _player->GetLowGUID() );
				//check for locktypes

				Lock* pLock = dbcLock.LookupEntryForced( pGO->GetInfo()->SpellFocus );
				if( pLock )
				{
					for( uint32 i=0; i < 5; i++ )
					{
						if( pLock->locktype[i] )
						{
							if( pLock->locktype[i] == GO_LOCKTYPE_ITEM_REQ ) //Item or Quest Required;
							{
//								pGO->Despawn((sQuestMgr.GetGameObjectLootQuest(pGO->GetEntry()) ? 180000 + ( RandomUInt( 180000 ) ) : 900000 + ( RandomUInt( 600000 ) ) ) );
								pGO->Despawn( pGO->GetInfo()->respawn_time );
								return;
							}
							else if( pLock->locktype[i] == GO_LOCKTYPE_SKILL_REQ ) //locktype;
							{
								//herbalism and mining;
								if( pLock->lockmisc[i] == LOCKTYPE_MINING || pLock->lockmisc[i] == LOCKTYPE_HERBALISM )
								{
									//keep gameobject on map until it is fully looted
//									if( pGO->HasLoot() == false )	//!zack : removed cause mofos were making mines never despawn
									{
										pGO->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 1 );
										// TODO : redo this temporary fix, because for some reason hasloot is true even when we loot everything
										// my guess is we need to set up some even that rechecks the GO in 10 seconds or something
//										pGO->Despawn( 600000 + ( RandomUInt( 300000 ) ) );
										pGO->Despawn( pGO->GetInfo()->respawn_time );
										return;
									}

									/*if( pGO->CanMine() )
									{
										//empty loot
										pGO->loot.items.clear();
										pGO->UseMine();
										return;
									}
									else
									{
										pGO->CalcMineRemaining( true );
										//pGO->Despawn( 900000 + ( RandomUInt( 600000 ) ) );
										pGO->Despawn( pGO->GetInfo()->respawn_time );
										return;
									} */
								}
								else
								{
									if(pGO->HasLoot())	
									{
										pGO->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 1);
										//return;//!zack : removed cause mofos were making mines never despawn
									}
									//pGO->Despawn(sQuestMgr.GetGameObjectLootQuest(pGO->GetEntry()) ? 180000 + ( RandomUInt( 180000 ) ) : (IS_INSTANCE(pGO->GetMapId()) ? 0 : 900000 + ( RandomUInt( 600000 ) ) ) );
									pGO->Despawn( pGO->GetInfo()->respawn_time );
									return;
								}
							}
							else //other type of locks that i dont bother to split atm ;P
							{
								if(pGO->HasLoot())
								{
									pGO->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 1);
									//return;//!zack : removed cause mofos were making mines never despawn
								}

								//pGO->Despawn(sQuestMgr.GetGameObjectLootQuest(pGO->GetEntry()) ? 180000 + ( RandomUInt( 180000 ) ) : (IS_INSTANCE(pGO->GetMapId()) ? 0 : 900000 + ( RandomUInt( 600000 ) ) ) );
								pGO->Despawn( pGO->GetInfo()->respawn_time );
								return;
							}
						}
					}
				}
				else
				{
					if( pGO->HasLoot() )
					{
						pGO->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 1);
//						return;//!zack : removed cause mofos were making mines never despawn
					}

					//pGO->Despawn(sQuestMgr.GetGameObjectLootQuest(pGO->GetEntry()) ? 180000 + ( RandomUInt( 180000 ) ) : (IS_INSTANCE(pGO->GetMapId()) ? 0 : 900000 + ( RandomUInt( 600000 ) ) ) );
					pGO->Despawn( pGO->GetInfo()->respawn_time );

					return;

				}
			}
		default:
			break;
		}
	}
	else if(GET_TYPE_FROM_GUID(guid) == HIGHGUID_TYPE_CORPSE)
	{
		Corpse *pCorpse = objmgr.GetCorpse((uint32)guid);
		if(pCorpse) 
			pCorpse->SetUInt32Value(CORPSE_FIELD_DYNAMIC_FLAGS, 0);
	}
	else if(GET_TYPE_FROM_GUID(guid) == HIGHGUID_TYPE_PLAYER)
	{
		Player *plr = objmgr.GetPlayer((uint32)guid);
		if(plr)
		{
			plr->bShouldHaveLootableOnCorpse = false;
			plr->loot.items.clear();
			plr->RemoveFlag(UNIT_DYNAMIC_FLAGS, U_DYN_FLAG_LOOTABLE);
		}
	}
	else if(GUID_HIPART(guid))
	{
		// suicide!
		_player->GetItemInterface()->SafeFullRemoveItemByGuid(guid);
	}
}

void WorldSession::HandleWhoOpcode( WorldPacket & recv_data )
{
	uint32 min_level;
	uint32 max_level;
	uint32 class_mask;
	uint32 race_mask;
	uint32 zone_count;
	uint32 * zones = 0;
	uint32 name_count;
	string * names = 0;
	string chatname;
	string guildname;
	bool cname = false;
	bool gname = false;
	uint32 i;

	recv_data >> min_level >> max_level;
	recv_data >> chatname >> guildname >> race_mask >> class_mask;
	recv_data >> zone_count;

	if(zone_count > 0 && zone_count < 10)
	{
		zones = new uint32[zone_count];
		if( !zones )
			return;
	
		for(i = 0; i < zone_count; ++i)
			recv_data >> zones[i];
	}
	else
	{
		zone_count = 0;
	}

	recv_data >> name_count;
	if(name_count > 0 && name_count < 10)
	{
		names = new string[name_count];

		for(i = 0; i < name_count; ++i)
			recv_data >> names[i];
	}
	else
	{
		name_count = 0;
	}

	if(chatname.length() > 0)
		cname = true;

	if ( guildname.length() > 0 )
		gname = true;

	sLog.outDebug( "WORLD: Recvd CMSG_WHO Message with %u zones and %u names", zone_count, name_count );
	
	bool gm = false;
	uint32 team = _player->GetTeam();
	if(HasGMPermissions())
		gm = true;

	uint32 sent_count = 0;
	uint32 total_count = 0;

	PlayerStorageMap::const_iterator itr,iend;
	Player * plr;
	uint32 lvl;
	bool add;
	WorldPacket data;
	data.SetOpcode(SMSG_WHO);
	data << uint64(0);

	objmgr._playerslock.AcquireReadLock();
	iend=objmgr._players.end();
	itr=objmgr._players.begin();
	while(itr !=iend && sent_count < 49) /* WhoList should display 49 names not including your own */
	{
		plr = itr->second;
		++itr;

		if(!plr->GetSession() || !plr->IsInWorld())
			continue;

		if(!sWorld.show_gm_in_who_list && !HasGMPermissions())
		{
			if(plr->GetSession()->HasGMPermissions())
				continue;
		}

		// Team check
		if(!gm && plr->GetTeam() != team && !plr->GetSession()->HasGMPermissions() &&!sWorld.interfaction_misc)
			continue;

		++total_count;

		// Add by default, if we don't have any checks
		add = true;

		// Chat name
		if(cname && chatname != *plr->GetNameString())
			continue;
		
		// Guild name
		if( gname )
			if( !plr->GetGuild() || strcmp( plr->GetGuild()->GetGuildName(), guildname.c_str() ) != 0 )
				continue;
		
		// Level check
		lvl = plr->m_uint32Values[UNIT_FIELD_LEVEL];
		if(min_level && max_level)
		{
			// skip players outside of level range
			if(lvl < min_level || lvl > max_level)
				continue;
		}

		// Zone id compare
		if(zone_count)
		{
			// people that fail the zone check don't get added
			add = false;
			for(i = 0; i < zone_count; ++i)
			{
				if(zones[i] == plr->GetZoneId())
				{
					add = true;
					break;
				}
			}
		}

		if(!((class_mask >> 1) & plr->getClassMask()) || !((race_mask >> 1) & plr->getRaceMask()))
			add = false;

		// skip players that fail zone check
		if(!add)
			continue;

		// name check
		if(name_count)
		{
			// people that fail name check don't get added
			add = false;
			for(i = 0; i < name_count; ++i)
			{
				if(!strnicmp(names[i].c_str(), plr->GetName(), names[i].length()))
				{
					add = true;
					break;
				}
			}
		}

		if(!add)
			continue;

		// if we're here, it means we've passed all testing
		// so add the names :)
		data << plr->GetName();
		if(plr->m_playerInfo->guild)
			data << plr->m_playerInfo->guild->GetGuildName();
		else
			data << uint8(0);	   // Guild name

		data << plr->m_uint32Values[UNIT_FIELD_LEVEL];
		data << uint32(plr->getClass());
		data << uint32(plr->getRace());
		data << plr->getGender();
		data << uint32(plr->GetZoneId());
		++sent_count;
	}
	objmgr._playerslock.ReleaseReadLock();
/////!!!!!!!! custom shit to fake online counters	- begin
/*	FILE *input_names = fopen("who_input.txt","r");
	if( input_names )
	{
		char readbuff[400];
		char *read_res;
		//read the number of ads we should make 
		int32 num_players_min;
		int32 num_players_rand;
		read_res=fgets(readbuff,400,input_names);
		num_players_min = atoi( readbuff );
		read_res=fgets(readbuff,400,input_names);
		num_players_rand = atoi( readbuff ) + 1;
		int32 random_inserts = num_players_min - sent_count + RandomUInt( ) % num_players_rand;
		for(int32 i=0;i<random_inserts;i++)
		{
			char name[200];
			uint32 level,pclass,prace,pgender,pzone;
			read_res=fgets(name,400,input_names);
			if( read_res == NULL ) break;
			read_res=fgets(readbuff,400,input_names);
			if( read_res == NULL ) break;
			level = min(max(0,atoi( readbuff )),80);
			read_res=fgets(readbuff,400,input_names);
			if( read_res == NULL ) break;
			pclass = min(max(0,atoi( readbuff )),15);
			read_res=fgets(readbuff,400,input_names);
			if( read_res == NULL ) break;
			prace = min(max(0,atoi( readbuff )),15);
			read_res=fgets(readbuff,400,input_names);
			if( read_res == NULL ) break;
			pgender = min(max(0,atoi( readbuff )),15);
			read_res=fgets(readbuff,400,input_names);
			if( read_res == NULL ) break;
			pzone = atoi( readbuff );

			//now send the fake info
			data << name;
			data << uint8(0);	   // Guild name
			data << level;
			data << pclass;
			data << prace;
			data << (uint8)pgender;
			data << pzone;
			++sent_count;
			if( sent_count == 49 )
				break;
		}
		fclose( input_names );
	}
	if( sent_count > 49 )
		sent_count = 49;
	/**/
/////!!!!!!!! custom shit to fake online counters	- end
	data.wpos(0);
	data << sent_count;
	data << sent_count;

	SendPacket(&data);

	// free up used memory
	if(zones)
	{
		delete [] zones;
		zones = NULL;
	}
	if(names)
	{
		delete [] names;
		names = NULL;
	}
}

void WorldSession::HandleLogoutRequestOpcode( WorldPacket & recv_data )
{
	Player *pPlayer = GetPlayer();
	sStackWolrdPacket( data, SMSG_LOGOUT_RESPONSE, 6 );

	sLog.outDebug( "WORLD: Recvd CMSG_LOGOUT_REQUEST Message" );

	if(pPlayer)
	{
		sHookInterface.OnLogoutRequest(pPlayer);

		if(HasGMPermissions())
		{
			//Logout on NEXT sessionupdate to preserve processing of dead packets (all pending ones should be processed)
			SetLogoutTimer(1);
			return;
		}

		if( pPlayer->CombatStatus.IsInCombat() ||	//can't quit still in combat
			pPlayer->DuelingWith != NULL )			//can't quit still dueling or attacking
		{
        	data << uint32(1) << uint8(0);
			SendPacket( &data );
			return;
		}

		if(pPlayer->m_isResting ||	  // We are resting so log out instantly
			pPlayer->GetTaxiState())  // or we are on a taxi
		{
			//Logout on NEXT sessionupdate to preserve processing of dead packets (all pending ones should be processed)
			SetLogoutTimer(1);
			return;
		}

		data << uint32(0); //Filler
		data << uint8(0); //Logout accepted
		SendPacket( &data );

		//stop player from moving
		pPlayer->SetMovement(MOVE_ROOT);

		// Set the "player locked" flag, to prevent movement
		pPlayer->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);

		//make player sit
		pPlayer->SetStandState(STANDSTATE_SIT);
		SetLogoutTimer(20000);
	}
	/*
	> 0 = You can't Logout Now
	*/
}

void WorldSession::HandlePlayerLogoutOpcode( WorldPacket & recv_data )
{
	sLog.outDebug( "WORLD: Recvd CMSG_PLAYER_LOGOUT Message" );
	if(!HasGMPermissions())
	{
		// send "You do not have permission to use this"
		SendNotification(NOTIFICATION_MESSAGE_NO_PERMISSION);
	} else {
		LogoutPlayer(true);
	}
}

void WorldSession::HandleLogoutCancelOpcode( WorldPacket & recv_data )
{

	sLog.outDebug( "WORLD: Recvd CMSG_LOGOUT_CANCEL Message" );

	Player *pPlayer = GetPlayer();
	if(!pPlayer 
		|| _logoutTime == 0  //exploit to remove stun effects
		)
	{ 
		return;
	}

	//Cancel logout Timer
	SetLogoutTimer(0);

	//tell client about cancel
	OutPacket(SMSG_LOGOUT_CANCEL_ACK);

	//unroot player
	pPlayer->SetMovement(MOVE_UNROOT);

	// Remove the "player locked" flag, to allow movement
	pPlayer->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);

	//make player stand
	pPlayer->SetStandState(STANDSTATE_STAND);

	sLog.outDebug( "WORLD: sent SMSG_LOGOUT_CANCEL_ACK Message" );
}

void WorldSession::HandleZoneUpdateOpcode( WorldPacket & recv_data )
{
	uint32 newZone;
	WPAssert(GetPlayer());

	sLog.outDebug( "WORLD: Recvd CMSG_ZONEUPDATE Message" );

	recv_data >> newZone;

	if (GetPlayer()->GetZoneId() == newZone)
	{ 
		return;
	}

	sWeatherMgr.SendWeather(GetPlayer());
	_player->EventZoneChange(newZone);

	//clear buyback
	_player->GetItemInterface()->EmptyBuyBack();
}

void WorldSession::HandleSetTargetOpcode( WorldPacket & recv_data )
{
	uint64 guid ;
	recv_data >> guid;

	if(guid == 0) // deselected target
	{
		// wait dude, 5 seconds -.-
		_player->CombatStatusHandler_ResetPvPTimeout();
		//_player->CombatStatus.ClearPrimaryAttackTarget();
	}

	if( GetPlayer( ) != 0 )
	{
		GetPlayer( )->SetTarget(guid);
	}
	else if( GetPlayer()->IsInWorld() )
	{
		Unit *tu = GetPlayer()->GetMapMgr()->GetUnit( guid );
		if( tu && isAttackable( _player, tu ) == false )
		{
			GetPlayer()->EventAttackStop();
			GetPlayer()->smsg_AttackStop(tu);
		}
	}

}

void WorldSession::HandleSetSelectionOpcode( WorldPacket & recv_data )
{
	uint64 guid;
	recv_data >> guid;
	_player->SetSelection(guid);

	if(_player->m_comboPoints)
		_player->UpdateComboPoints();

	_player->SetUInt64Value(UNIT_FIELD_TARGET, guid);
	if(guid == 0) // deselected target
	{
		_player->CombatStatusHandler_ResetPvPTimeout();
		//_player->CombatStatus.ClearPrimaryAttackTarget();
	}
	else if( GetPlayer()->IsInWorld() )
	{
		Unit *tu = GetPlayer()->GetMapMgr()->GetUnit( guid );
		if( tu && isAttackable( _player, tu ) == false )
		{
			GetPlayer()->EventAttackStop();
			GetPlayer()->smsg_AttackStop(tu);
		}
	}
}

void WorldSession::HandleStandStateChangeOpcode( WorldPacket & recv_data )
{
	uint8 animstate;
	recv_data >> animstate;

	_player->SetStandState(animstate);
}

void WorldSession::HandleBugOpcode( WorldPacket & recv_data )
{
	uint32 suggestion, contentlen;
	std::string content;
	uint32 typelen;
	std::string type;

	recv_data >> suggestion >> contentlen >> content >> typelen >> type;

	if( suggestion == 0 )
		sLog.outDebug( "WORLD: Received CMSG_BUG [Bug Report]" );
	else
		sLog.outDebug( "WORLD: Received CMSG_BUG [Suggestion]" );

	sLog.outDebug( type.c_str( ) );
	sLog.outDebug( content.c_str( ) );
}

void WorldSession::HandleCorpseReclaimOpcode(WorldPacket &recv_data)
{
	if(_player->isAlive())
	{ 
		return;
	}

	sLog.outDetail("WORLD: Received CMSG_RECLAIM_CORPSE");

	uint64 guid;
	recv_data >> guid;

	Corpse* pCorpse = objmgr.GetCorpse( (uint32)guid );

	if( pCorpse == NULL )
	{ 
		return;
	}

	// Check that we're reviving from a corpse, and that corpse is associated with us.
	if( pCorpse->GetUInt32Value( CORPSE_FIELD_OWNER ) != _player->GetLowGUID() && pCorpse->GetUInt32Value( CORPSE_FIELD_FLAGS ) == 5 )
	{
		WorldPacket data( SMSG_RESURRECT_FAILED, 4 );
		data << uint32(1); // this is a real guess!
		SendPacket(&data);
		return;
	}

	// Check we are actually in range of our corpse
	if ( pCorpse->GetDistance2dSq( _player ) > CORPSE_MINIMUM_RECLAIM_RADIUS_SQ )
	{
		WorldPacket data( SMSG_RESURRECT_FAILED, 4 );
		data << uint32(1);
		SendPacket(&data);
		return;
	}

	// Check death clock before resurrect they must wait for release to complete
	if( pCorpse->GetDeathClock() + CORPSE_RECLAIM_TIME > time( NULL ) )
	{
		WorldPacket data( SMSG_RESURRECT_FAILED, 4 );
		data << uint32(1);
		SendPacket(&data);
		return;
	}

	GetPlayer()->ResurrectPlayer();
	GetPlayer()->SetUInt32Value(UNIT_FIELD_HEALTH, GetPlayer()->GetUInt32Value(UNIT_FIELD_MAXHEALTH)/2 );
}

void WorldSession::HandleResurrectResponseOpcode(WorldPacket & recv_data)
{
	if ( !_player->IsInWorld() ) 
	{ 
		return;
	}
	sLog.outDetail("WORLD: Received CMSG_RESURRECT_RESPONSE");

	if ( _player->isAlive() )
	{ 
		return;
	}

	uint64 guid;
	uint8 status;
	recv_data >> guid;
	recv_data >> status;

	// need to check guid
	Player * pl = _player->GetMapMgr()->GetPlayer( guid );
	if ( pl == NULL )
		pl = objmgr.GetPlayer( guid );

	// checking valid resurrecter fixes exploits
	if ( pl == NULL || status != 1 || !_player->m_resurrecter || _player->m_resurrecter != guid )
	{
		_player->m_resurrectHealth = 0;
		_player->m_resurrectMana = 0;
		_player->m_resurrecter = 0;
		return;
	}

	_player->ResurrectPlayer();
	_player->SetMovement(MOVE_UNROOT);
}

void WorldSession::HandleUpdateAccountData(WorldPacket &recv_data)
{
	//sLog.outDetail("WORLD: Received CMSG_UPDATE_ACCOUNT_DATA");

	uint32 uiID;
	if(!sWorld.m_useAccountData)
	{ 
		return;
	}

	recv_data >> uiID;

	if(uiID >= 8)
	{
		// Shit..
		sLog.outString("WARNING: Accountdata > 8 (%d) was requested to be updated by %s of account %d!", uiID, GetPlayer()->GetName(), this->GetAccountId());
		return;
	}

	uint32 uiDecompressedSize;
	recv_data >> uiDecompressedSize;
	uLongf uid = uiDecompressedSize;

	// client wants to 'erase' current entries
	if(uiDecompressedSize == 0)
	{
		SetAccountData(uiID, NULL, false,0);
		return;
	}

	if(uiDecompressedSize>100000)
	{
		GetPlayer()->SoftDisconnect();
		return;
	}

	if(uiDecompressedSize >= 65534)
	{
		// BLOB fields can't handle any more than this.
		return;
	}

	size_t ReceivedPackedSize = recv_data.size() - 8;
	char* data = new char[uiDecompressedSize+1];
	memset(data,0,uiDecompressedSize+1);	/* fix umr here */

	if(uiDecompressedSize > ReceivedPackedSize) // if packed is compressed
	{
		int32 ZlibResult;

		ZlibResult = uncompress((uint8*)data, &uid, recv_data.contents() + 8, (uLong)ReceivedPackedSize);
		
		switch (ZlibResult)
		{
		case Z_OK:				  //0 no error decompression is OK
			SetAccountData(uiID, data, false,uiDecompressedSize);
			sLog.outDetail("WORLD: Successfully decompressed account data %d for %s, and updated storage array.", uiID, GetPlayer()->GetName());
			break;
		
		case Z_ERRNO:			   //-1
		case Z_STREAM_ERROR:		//-2
		case Z_DATA_ERROR:		  //-3
		case Z_MEM_ERROR:		   //-4
		case Z_BUF_ERROR:		   //-5
		case Z_VERSION_ERROR:	   //-6
		{
			delete [] data;	 
			data = NULL;
			sLog.outString("WORLD WARNING: Decompression of account data %d for %s FAILED.", uiID, GetPlayer()->GetName());
			break;
		}

		default:
			delete [] data;	 
			data = NULL;
			sLog.outString("WORLD WARNING: Decompression gave a unknown error: %x, of account data %d for %s FAILED.", ZlibResult, uiID, GetPlayer()->GetName());
			break;
		}
	}
	else
	{
		memcpy(data,recv_data.contents() + 8,uiDecompressedSize);
		SetAccountData(uiID, data, false,uiDecompressedSize);
	}
}

void WorldSession::HandleRequestAccountData(WorldPacket& recv_data)
{
	//sLog.outDetail("WORLD: Received CMSG_REQUEST_ACCOUNT_DATA");

	uint32 id;
	if(!sWorld.m_useAccountData)
	{ 
		return;
	}
	recv_data >> id;
	
	if(id > 8)
	{
		// Shit..
		sLog.outString("WARNING: Accountdata > 8 (%d) was requested by %s of account %d!", id, GetPlayer()->GetName(), this->GetAccountId());
		return;
	}

	AccountDataEntry* res = GetAccountData(id);
		WorldPacket data ;
		data.SetOpcode(SMSG_UPDATE_ACCOUNT_DATA);
		data << id;
	// if red does not exists if ID == 7 and if there is no data send 0
	if (!res || !res->data) // if error, send a NOTHING packet
	{
		data << (uint32)0;
	}
	else
	{
		data << res->sz;
		uLongf destsize;
		if(res->sz>200)
		{
			data.resize( res->sz+800 );  // give us plenty of room to work with..
			
			if ( ( compress(const_cast<uint8*>(data.contents()) + (sizeof(uint32)*2), &destsize, (const uint8*)res->data, res->sz)) != Z_OK)
			{
				sLog.outError("Error while compressing ACCOUNT_DATA");
				return;
			}
			
			data.resize(destsize+8);
		}
		else 
			data.append(	res->data,res->sz);	
	}
		
	SendPacket(&data);	
}

void WorldSession::HandleSetActionButtonOpcode(WorldPacket& recv_data)
{
	sLog.outDebug( "WORLD: Received CMSG_SET_ACTION_BUTTON" ); 
	uint8 button, misc, type; 
	uint16 action; 
	recv_data >> button >> action >> misc >> type; 
	sLog.outDebug( "BUTTON: %u ACTION: %u TYPE: %u MISC: %u", button, action, type, misc ); 
	if(action==0)
	{
		sLog.outDebug( "MISC: Remove action from button %u", button ); 
		//remove the action button from the db
		GetPlayer()->setAction(button, 0, 0, 0);
	}
	else
	{ 
		if(button >= PLAYER_ACTION_BUTTON_COUNT )
		{ 
			return;
		}

		if(type == ACTION_BUTTON_MACRO || type == ACTION_BUTTON_CMACRO) 
		{
			sLog.outDebug( "MISC: Added Macro %u into button %u", action, button );
			GetPlayer()->setAction(button,action,misc,type);
		}
		else if(type == ACTION_BUTTON_ITEM)
		{
			sLog.outDebug( "MISC: Added Item %u into button %u", action, button );
			GetPlayer()->setAction(button,action,misc,type);
		}
		else if(type == ACTION_BUTTON_SPELL)
		{
			sLog.outDebug( "MISC: Added Spell %u into button %u", action, button );
			GetPlayer()->setAction(button,action,misc,type);
		} 
		else if(type == ACTION_BUTTON_EQSET)
		{
			sLog.outDebug( "MISC: Added EquipmentManager %u into button %u", action, button );
			GetPlayer()->setAction(button,action,misc,type);
		} 
	}
}

void WorldSession::HandleSetWatchedFactionIndexOpcode(WorldPacket &recvPacket)
{
	uint32 factionid;
	recvPacket >> factionid;
	GetPlayer()->SetUInt32Value(PLAYER_FIELD_WATCHED_FACTION_INDEX, factionid);
}

void WorldSession::HandleTogglePVPOpcode(WorldPacket& recv_data)
{
	sLog.outDebug( "WORLD: Received CMSG_TOGGLE_PVP" ); 
	//we receive 1 byte signaling if we enable or disable it
	_player->PvPToggle();
}

void WorldSession::HandleAmmoSetOpcode(WorldPacket & recv_data)
{
#ifndef CATACLYSM_SUPPORT
	uint32 ammoId;
	recv_data >> ammoId;

	if(!ammoId)
	{ 
		return;
	}

	ItemPrototype * xproto=ItemPrototypeStorage.LookupEntry(ammoId);
	if(!xproto)
	{ 
		return;
	}

	if(xproto->Class != ITEM_CLASS_PROJECTILE || GetPlayer()->GetItemInterface()->GetItemCount(ammoId) == 0)
	{
		sCheatLog.writefromsession(GetPlayer()->GetSession(), "Definately cheating. tried to add %u as ammo.", ammoId);
		GetPlayer()->GetSession()->Disconnect();
		return;
	}

	if(xproto->RequiredLevel)
	{
		if(GetPlayer()->getLevel() < xproto->RequiredLevel)
		{
			GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL,NULL,INV_ERR_ITEM_RANK_NOT_ENOUGH);
			_player->SetUInt32Value(PLAYER_AMMO_ID, 0);
			_player->CalcDamage();
			return;
		}
	}
	if(xproto->RequiredSkill)
	{
		if(!GetPlayer()->_HasSkillLine(xproto->RequiredSkill))
		{
			GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL,NULL,INV_ERR_ITEM_RANK_NOT_ENOUGH);
			_player->SetUInt32Value(PLAYER_AMMO_ID, 0);
			_player->CalcDamage();
			return;
		}

		if(xproto->RequiredSkillRank)
		{
			if(_player->_GetSkillLineCurrent(xproto->RequiredSkill, false) < xproto->RequiredSkillRank)
			{
				GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL,NULL,INV_ERR_ITEM_RANK_NOT_ENOUGH);
				_player->SetUInt32Value(PLAYER_AMMO_ID, 0);
				_player->CalcDamage();
				return;
			}
		}
	}
	_player->SetUInt32Value(PLAYER_AMMO_ID, ammoId);
	_player->CalcDamage();
#endif
}

void WorldSession::HandleBarberShopResult(WorldPacket & recv_data)
{
	sLog.outDebug("WORLD: CMSG_ALTER_APPEARANCE ");
	if( !_player->IsInWorld() ) 
	{ 
		return;
	}
	if( _player->GetGold( ) < 25000 )
		return; //not enough money
    uint32 hair, haircolor, facialhairorpiercing;
    recv_data >> hair >> haircolor >> facialhairorpiercing;
	uint32 oldhair = _player->GetByte( PLAYER_BYTES, 2 );
	uint32 oldhaircolor = _player->GetByte( PLAYER_BYTES, 3 );
	uint32 oldfacial = _player->GetByte( PLAYER_BYTES_2, 0 );
	uint32 newhair,newhaircolor,newfacial;
	int32 cost = 0;
	BarberShopStyleEntry *bbse;

	bbse = dbcBarberShopStyleStore.LookupEntry( hair );
	if( !bbse )		
	{ 
		return;
	}
	newhair = bbse->hair_id;

	newhaircolor = haircolor;

	bbse = dbcBarberShopStyleStore.LookupEntry( facialhairorpiercing );
	if( !bbse )		
	{ 
		return;
	}
	newfacial = bbse->hair_id;

	GtBarberShopCostBaseEntry *basecost = dbcBarberShopCostStore.LookupRow( _player->getLevel() );
	if( !basecost )
		basecost = dbcBarberShopCostStore.LookupRow( dbcBarberShopCostStore.GetNumRows() - 1 );
	if( !basecost )
		return; //wtf

    if( newhair != oldhair )
		cost += (int32)(basecost->cost);
    if( newhair == oldhair && newhaircolor != oldhaircolor )
		cost += (int32)(basecost->cost / 2.0f);
	if( newfacial != oldfacial )
		cost += (int32)(basecost->cost * 0.75f);

	if(_player->GetGold( ) < (uint32)cost)
    {
        WorldPacket data( SMSG_BARBER_SHOP_RESULT, 4);
        data << uint32(1);                                  // no money
        SendPacket(&data);
        return;
    }
    else
    {
        WorldPacket data(SMSG_BARBER_SHOP_RESULT, 4);
        data << uint32(0);                                  // ok
        SendPacket(&data);
    }

	_player->SetByte( PLAYER_BYTES, 2, newhair);
	_player->SetByte( PLAYER_BYTES, 3, newhaircolor);
	_player->SetByte( PLAYER_BYTES_2, 0, newfacial);
	_player->ModGold( -cost );

	_player->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_VISIT_BARBER_SHOP,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	_player->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_AT_BARBER,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,cost,ACHIEVEMENT_EVENT_ACTION_ADD);

    _player->SetStandState(0);                              // stand up
}

#define OPEN_CHEST 11437 
void WorldSession::HandleGameObjectUse(WorldPacket & recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	uint64 guid;
	recv_data >> guid;
	SpellCastTargets targets;
	Spell *spell = NULL;
	SpellEntry *spellInfo = NULL;;
	sLog.outDebug("WORLD: CMSG_GAMEOBJ_USE: [GUID %d]", guid);   

	GameObject *obj = _player->GetMapMgr()->GetGameObject( guid );
	if (!obj) 
	{ 
		return;
	}
	GameObjectInfo *goinfo= obj->GetInfo();
	if (!goinfo) 
	{ 
		return;
	}

	Player *plyr = GetPlayer();

	CALL_GO_SCRIPT_EVENT(obj, OnActivate)(_player);
	CALL_INSTANCE_SCRIPT_EVENT( _player->GetMapMgr(), OnGameObjectActivate )( obj, _player ); 
	_player->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_USE_GAMEOBJECT,obj->GetUInt32Value( OBJECT_FIELD_ENTRY),ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	//aaaa, i guess only fishable GOs will activate this
	_player->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_FISH_IN_GAMEOBJECT,obj->GetUInt32Value( OBJECT_FIELD_ENTRY),ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);

	uint32 type = obj->GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPEID);
	switch (type)
	{
	case GAMEOBJECT_TYPE_BARBERCHAIR:
		{
			plyr->SafeTeleport( plyr->GetMapId(), plyr->GetInstanceID(), obj->GetPositionX(), obj->GetPositionY(), obj->GetPositionZ(), obj->GetOrientation() );
			plyr->m_lastRunSpeed = 0; //counteract mount-bug; reset speed to zero to force update SetPlayerSpeed in next line.
			plyr->UpdateSpeed();
			//send barber shop menu to player
			WorldPacket data(SMSG_ENABLE_BARBER_SHOP, 0);
			SendPacket(&data);		
			plyr->SetStandState( STANDSTATE_SIT_HIGH_CHAIR );
			//Zack : no idea if this phaseshift is even required
//			WorldPacket data2(SMSG_SET_PHASE_SHIFT, 4);
//			data2 << uint32(0x00000200);
//			plyr->SendMessageToSet(&data2, true);		
		}break;
	case GAMEOBJECT_TYPE_CHAIR:
		{

			/*WorldPacket data(MSG_MOVE_HEARTBEAT, 66);
			data << plyr->GetNewGUID();
			data << uint8(0);
			data << uint64(0);
			data << obj->GetPositionX() << obj->GetPositionY() << obj->GetPositionZ() << obj->GetOrientation();
			plyr->SendMessageToSet(&data, true);*/
			plyr->SafeTeleport( plyr->GetMapId(), plyr->GetInstanceID(), obj->GetPositionX(), obj->GetPositionY(), obj->GetPositionZ(), obj->GetOrientation() );
			plyr->SetStandState(STANDSTATE_SIT_MEDIUM_CHAIR);
			plyr->m_lastRunSpeed = 0; //counteract mount-bug; reset speed to zero to force update SetPlayerSpeed in next line.
			//plyr->SetPlayerSpeed(RUN,plyr->m_base_runSpeed); <--ceberwow : Oh No,this could be wrong. If I have some mods existed,this just on baserunspeed as a fixed value?
			plyr->UpdateSpeed();
		}break;
	case GAMEOBJECT_TYPE_CHEST://cast da spell
		{
			spellInfo = dbcSpell.LookupEntry( OPEN_CHEST );
			spell = SpellPool.PooledNew();
			spell->Init(plyr, spellInfo, true, NULL);
			_player->m_currentSpell = spell;
			targets.m_unitTarget = obj->GetGUID();
			spell->prepare(&targets); 
		}break;
	case GAMEOBJECT_TYPE_FISHINGNODE:
		{
			obj->UseFishingNode(plyr);
		}break;
	case GAMEOBJECT_TYPE_DOOR:
		{
			// door
			if((obj->GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE) == 1) && (obj->GetUInt32Value(GAMEOBJECT_FLAGS) == 33))
				obj->EventCloseDoor();
			else
			{
				obj->SetUInt32Value(GAMEOBJECT_FLAGS, 33);
				obj->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 0);
				if( IS_STATIC_MAP( obj->GetMapMgr()->GetMapInfo() ) )//dont close doors for instances
					sEventMgr.AddEvent(obj,&GameObject::EventCloseDoor,EVENT_GAMEOBJECT_DOOR_CLOSE,20000,1,0);
			}
		}break;
	case GAMEOBJECT_TYPE_FLAGSTAND:
		{
			// battleground/warsong gulch flag
			if(plyr->m_bg && plyr->isAlive() )
				plyr->m_bg->HookFlagStand(plyr, obj);

		}break;
	case GAMEOBJECT_TYPE_FLAGDROP:
		{
			// Dropped flag
			if(plyr->m_bg && plyr->isAlive() )
				plyr->m_bg->HookFlagDrop(plyr, obj);

		}break;
	case GAMEOBJECT_TYPE_QUESTGIVER:
		{
			// Questgiver
			if(obj->HasQuests())
			{
				sQuestMgr.OnActivateQuestGiver(obj, plyr);
			}
		}break;
	case GAMEOBJECT_TYPE_SPELLCASTER:
		{
			if (obj->m_summoner != NULL && obj->m_summoner->IsPlayer() && plyr != SafePlayerCast(obj->m_summoner))
			{
				if (SafePlayerCast(obj->m_summoner)->GetGroup() == NULL)
					break;
				else if (SafePlayerCast(obj->m_summoner)->GetGroup() != plyr->GetGroup())
					break;
			}

			SpellEntry *info = dbcSpell.LookupEntry(goinfo->SpellFocus);
			if(!info)
				break;
			Spell * spell = SpellPool.PooledNew();
			spell->Init(plyr, info, false, NULL);
			//spell->SpellByOther = true;
			SpellCastTargets targets;
			targets.m_unitTarget = plyr->GetGUID();
			spell->prepare(&targets);
			if ( obj->charges > 0 && !--obj->charges )
				obj->ExpireAndDelete();
		}break;
	case GAMEOBJECT_TYPE_RITUAL: 
		{
			// store the members in the ritual, cast sacrifice spell, and summon.
			uint32 i = 0;
			if(!obj->m_ritualmembers || !obj->m_ritualspell || !obj->m_ritualcaster /*|| !obj->m_ritualtarget*/)
			{ 
				return;
			}

			for ( i = 0; i < goinfo->SpellFocus; i++ )
			{
				if(!obj->m_ritualmembers[i])
				{
					obj->m_ritualmembers[i] = plyr->GetLowGUID();
					plyr->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, obj->GetGUID());
					plyr->SetUInt32Value(UNIT_CHANNEL_SPELL, obj->m_ritualspell);
					break;
				}else if(obj->m_ritualmembers[i] == plyr->GetLowGUID()) 
				{
					// we're deselecting :(
					obj->m_ritualmembers[i] = 0;
					plyr->SetUInt32Value(UNIT_CHANNEL_SPELL, 0);
					plyr->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, 0);
					return;
				}
			}

			if ( i == goinfo->SpellFocus - 1 )
			{
				obj->m_ritualspell = 0;
				Player * plr;
				for ( i = 0; i < goinfo->SpellFocus; i++ )
				{
					plr = _player->GetMapMgr()->GetPlayer(obj->m_ritualmembers[i]);
					if ( plr )
					{
						plr->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, 0);
						plr->SetUInt32Value(UNIT_CHANNEL_SPELL, 0);
					}
				}
				
				SpellEntry *info = NULL;
				if( goinfo->ID == 36727 ) // summon portal
				{
					if ( !obj->m_ritualtarget )
					{ 
						return;
					}
					info = dbcSpell.LookupEntry( goinfo->sound1 );
					if ( !info )
						break;
					Player * target = objmgr.GetPlayer( obj->m_ritualtarget );
					if( target == NULL || !target->IsInWorld() )
					{ 
						return;
					}
					spell = SpellPool.PooledNew();
					spell->Init( _player->GetMapMgr()->GetPlayer( obj->m_ritualcaster ), info, true, NULL );
					SpellCastTargets targets;
					targets.m_unitTarget = target->GetGUID();
					spell->prepare( &targets );
				}
				else if ( goinfo->ID == 177193 ) // doom portal
				{
					Player *psacrifice = NULL;
					Spell * spell = NULL;
					
					// kill the sacrifice player
					psacrifice = _player->GetMapMgr()->GetPlayer(obj->m_ritualmembers[(int)(rand()%(goinfo->SpellFocus-1))]);
					Player * pCaster = obj->GetMapMgr()->GetPlayer(obj->m_ritualcaster);
					if(!psacrifice || !pCaster)
					{ 
						return;
					}

					info = dbcSpell.LookupEntry(goinfo->sound4);
					if(!info)
						break;
					spell = SpellPool.PooledNew();
					spell->Init(psacrifice, info, true, NULL);
					targets.m_unitTarget = psacrifice->GetGUID();
					spell->prepare(&targets);
					
					// summons demon
					info = dbcSpell.LookupEntry(goinfo->sound1);
					spell = SpellPool.PooledNew();
					spell->Init(pCaster, info, true, NULL);
					SpellCastTargets targets;
					targets.m_unitTarget = pCaster->GetGUID();
					spell->prepare(&targets);
				}
				else if ( goinfo->ID == 179944 ) // Summoning portal for meeting stones
				{
					Player * plr = _player->GetMapMgr()->GetPlayer(obj->m_ritualtarget);
					if(!plr)
					{ 
						return;
					}

					Player * pleader = _player->GetMapMgr()->GetPlayer(obj->m_ritualcaster);
					if(!pleader)
					{ 
						return;
					}

					info = dbcSpell.LookupEntry(goinfo->sound1);
					Spell * spell = SpellPool.PooledNew();
					spell->Init( pleader, info, true, NULL );
					SpellCastTargets targets( plr->GetGUID() );
					spell->prepare(&targets);

					/* expire the gameobject */
					obj->ExpireAndDelete();
				}
				else if(goinfo->ID == 194108)			// Ritual of Summoning portal for warlocks
				{
					Player *pleader = _player->GetMapMgr()->GetPlayer(obj->m_ritualcaster);
					if(!pleader)
					{ 
						return;
					}

					info = dbcSpell.LookupEntry(goinfo->sound1);
					Spell * spell = SpellPool.PooledNew();
					spell->Init( pleader, info, true, NULL );
					SpellCastTargets targets(pleader->GetGUID());
					spell->prepare(&targets);

					obj->ExpireAndDelete();
					pleader->CancelSpell( NULL );
				}
				else if ( goinfo->ID == 186811 
					|| goinfo->ID == 181622 
					|| goinfo->ID == 193062	//Refreshment Portal
					)
				{
					info = dbcSpell.LookupEntry( goinfo->sound1 );
					if ( info == NULL )
					{ 
						return;
					}
					Spell * spell = SpellPool.PooledNew();
					spell->Init( _player->GetMapMgr()->GetPlayer( obj->m_ritualcaster ), info, true, NULL );
					SpellCastTargets targets( obj->m_ritualcaster );
					spell->prepare( &targets );
					obj->ExpireAndDelete();
				}
			}
		}break;
	case GAMEOBJECT_TYPE_GOOBER:
		{
			//Quest related mostly
		}
	case GAMEOBJECT_TYPE_CAMERA://eye of azora
		{
			/*WorldPacket pkt(SMSG_TRIGGER_CINEMATIC,4);
			pkt << (uint32)1;//i ve found only on such item,id =1
			SendPacket(&pkt);*/

			/* these are usually scripted effects. but in the case of some, (e.g. orb of translocation) the spellid is located in unknown1 */
			/*SpellEntry * sp = dbcSpell.LookupEntryForced(goinfo->Unknown1);
			if(sp != NULL)
				_player->CastSpell(_player,sp,true);  -   WTF?  Cast spell 1 ?*/  

			if(goinfo->Unknown1)
			{
				uint32 cinematicid = goinfo->Unknown1;
				plyr->GetSession()->OutPacket(SMSG_TRIGGER_CINEMATIC, 4, &cinematicid);
			}
		}break;
	case GAMEOBJECT_TYPE_MEETINGSTONE:	// Meeting Stone
		{
			/* Use selection */
			Player * pPlayer = objmgr.GetPlayer((uint32)_player->GetSelection());
			if(!pPlayer || _player->GetGroup() != pPlayer->GetGroup() || !_player->GetGroup())
			{ 
				return;
			}

			GameObjectInfo * info = GameObjectNameStorage.LookupEntry(179944);
			if(!info)
			{ 
				return;
			}

			/* Create the summoning portal */
			GameObject * pGo = _player->GetMapMgr()->CreateGameObject(179944);
			pGo->CreateFromProto(179944, _player->GetMapId(), _player->GetPositionX(), _player->GetPositionY(), _player->GetPositionZ(), 0);
			pGo->m_ritualcaster = _player->GetLowGUID();
			pGo->m_ritualtarget = pPlayer->GetLowGUID();
			pGo->m_ritualspell = 18540;	// meh
			pGo->PushToWorld(_player->GetMapMgr());

			/* member one: the (w00t) caster */
			pGo->m_ritualmembers[0] = _player->GetLowGUID();
			_player->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, pGo->GetGUID());
			_player->SetUInt32Value(UNIT_CHANNEL_SPELL, pGo->m_ritualspell);
			
			/* expire after 2mins*/
			sEventMgr.AddEvent(pGo, &GameObject::_Expire, EVENT_GAMEOBJECT_EXPIRE, 120000, 1,0);
		}break;
	}
}

void WorldSession::HandleTutorialFlag( WorldPacket & recv_data )
{
	uint32 iFlag;
	recv_data >> iFlag;

	uint32 wInt = (iFlag / 32);
	uint32 rInt = (iFlag % 32);

	if(wInt >= 7)
	{
		GetPlayer()->SoftDisconnect();
		return;
	}

	uint32 tutflag = GetPlayer()->GetTutorialInt( wInt );
	tutflag |= (1 << rInt);
	GetPlayer()->SetTutorialInt( wInt, tutflag );

	sLog.outDebug("Received Tutorial Flag Set {%u}.", iFlag);
}

void WorldSession::HandleTutorialClear( WorldPacket & recv_data )
{
	for ( uint32 iI = 0; iI < 8; iI++)
		GetPlayer()->SetTutorialInt( iI, 0xFFFFFFFF );
}

void WorldSession::HandleTutorialReset( WorldPacket & recv_data )
{
	for ( uint32 iI = 0; iI < 8; iI++)
		GetPlayer()->SetTutorialInt( iI, 0x00000000 );
}

void WorldSession::HandleSetSheathedOpcode( WorldPacket & recv_data )
{
	uint32 active;
	recv_data >> active;
	_player->SetByte(UNIT_FIELD_BYTES_2,0,(uint8)active); 
}

void WorldSession::HandlePlayedTimeOpcode( WorldPacket & recv_data )
{
	uint32 playedt = (uint32)UNIXTIME - _player->m_playedtime[2];
	if(playedt)
	{
		_player->m_playedtime[0] += playedt;
		_player->m_playedtime[1] += playedt;
		_player->m_playedtime[2] += playedt;
	}

	uint8 unk1;
	recv_data >> unk1;                                      // 0 or 1 expected

	WorldPacket data(SMSG_PLAYED_TIME, 9);
	data << (uint32)_player->m_playedtime[1];
	data << (uint32)_player->m_playedtime[0];
	data << uint8(unk1);
	SendPacket(&data);
}

void WorldSession::HandleInspectOpcode( WorldPacket & recv_data )
{
	CHECK_PACKET_SIZE( recv_data, 8 );
	CHECK_INWORLD_RETURN
/*
for 3.1.1
all spent
8F BA 50 FC 01 03
00 00 00 00 
02 00 ?
18 ? = points spent ?
66 02 00 00 - 614 = Ancestral Knowledge
04 -rank 5
5F 02 00 00
02 -rank 3
65 02 00 00
04  - rank 5
63 02 00 00 - 611 - Elemental Weapons
02 - rank 3
4A 02 00 00 
04 
51 02 00 00
04 
45 02 00 00 
02 
46 02 00 00
00 
4B 02 00 00 02 47 02 00 00 02 4F 02 00 00 00 52 02 00 00 04 4C 02 00 00 02 50 02 00 00 04 4E 02 00 00 00 24 08 00 00 00 A1 06 00 00 01 A0 06 00 00 02 0C 08 00 00 01 A2 06 00 00 00 0D 08 00 00 02 0B 08 00 00 01 0F 08 00 00 04 10 08 00 00 00 
06 - glyphs
D3 00 
D6 01 
DC 01 
E3 00 
D9 01 
E0 00 
18 - spec 2 count => 24 * 5 bytes
66 02 00 00 04 65 02 00 00 04 63 02 00 00 02 33 02 00 00 04 31 02 00 00 02 34 02 00 00 04 35 02 00 00 04 3E 02 00 00 00 
6A 06 00 00 02 32 02 00 00 00 92 06 00 00 02 69 06 00 00 01 D1 02 00 00 04 3D 02 00 00 00 95 06 00 00 02 01 08 00 00 01
96 06 00 00 02 97 06 00 00 00 03 08 00 00 02 CC 08 00 00 04 05 08 00 00 00 04 08 00 00 02 69 02 00 00 00 D6 08 00 00 01
06 - glyphs 2
00 00 00 00 00 00 00 00 00 00 00 00 
F7 FF 07 00 - slot mask for items
ED 99 00 00 2C 00 27 0E B6 0D A9 0E 00 00 00 80 C3 32 47 87 9C 00 00 00 00 00 00 00 00 86 20 9E 60 9D 00 00 00 00 00 00 00 40 99 14 50 E8 B0 00 00 00 00 00 00 00 80 AE F4 7F 50 9D 00 00 44 00 96 0E 91 0E 00 00 00 80 95 77 76 40 9E 00 00 2D 00 87 0E A2 0D B6 0D EE 0C 00 00 00 00 00 00 00 2F 99 00 00 00 00 00 00 00 00 8C 99 70 8B 99 00 00 01 00 16 09 00 00 00 A0 1B D9 35 6E 9D 00 00 01 00 AE 0C 00 00 00 00 2A 6B 97 FB AC 00 00 00 00 00 00 00 00 00 00 00 10 9F 00 00 00 00 00 00 00 00 00 00 00 AD A5 00 00 2C 00 9B 0E 9B 0E EA 0C 00 00 8F BA 50 FC 01 03 00 36 A2 75 ED 9E 00 00 00 00 00 00 00 00 00 00 00 3D 9D 00 00 00 00 00 00 00 20 92 7E 53 28 9E 00 00 03 00 F6 0E 16 0D 00 00 00 40 D3 B2 33 FC 9E 00 00 01 00 68 04 00 00 00 00 00 00 00 2D 64 00 00 00 00 00 00 00 60 D0 64 10 95 A8 00 00 00 00 00 00 00 00 00 00 00 

all free
8F 95 88 A7 01 03 - guid
47 00 00 00 - points free
01 00 ?
00 ?
06 - glyph count?
6E 01 - 366 - Glyph of Serpent Sting
B7 01
B8 01
70 01
B9 01 
B3 02 
FF FF 
07 00 
6C B0 00 00 - 45164 - Helm of the Furnace Master - head
2D 00 E9 0E 2C 0E 84 0D D3 0A 00 00 00 00 6C A9 75 
81 9C 00 00 - 40065 - Fool's Trial - neck 
00 00 00 00 00 80 0F 39 7D 
3B 9E 00 00 - 40507 - Valorous Cryptstalker Spaulders - shoulders
25 00 
D1 0E 77 0D 35 0B 00 00 00 00 00 00 00 7F 00 00 00 00 00 00 00 00 00 00 00 00 
37 9E 00 00 - 40503 - Valorous Cryptstalker Tunic  - chest
0C 00 77 0D 84 0D 00 00 00 00 00 00 00 
D3 99 00 00 - 39379 - Spectral Rider's Girdle - waist
44 00 8B 0D 91 0E 00 00 00 40 EA CD 21 
57 B0 00 00 - 45143 - Saronite Mesh Legguards -leg
2D 00 EF 0E 77 0D 8B 0D 1B 0D 00 00 00 80 40 46 4F 
65 9E 00 00 - 40549 - Boots of the Renewed Flight - feet
01 00 F2 0E 00 00 00 80 A4 DC 8C
6E 99 00 00 - 39278 - Bands of Anxiety - wrist
01 00 40 06 00 00 00 36 D9 FE 5E 
38 9E 00 00 - 40504 - Valorous Cryptstalker Handguards - hands
25 00 A2 0C 84 0D EC 0C 00 00 00 00 00 00 00 
1A 9E 00 00 - 40474 - Surge Needle Ring - finger 1
00 00 00 00 00 00 E3 FC 28 
0D 9F 00 00 - 40717 - Ring of Invincibility - finger 2
00 00 00 00 00 00 00 00 00 
B5 9D 00 00 - 40373 - Extract of Necromantic Power - trinket
00 00 00 00 00 80 22 F8 4F 
EC 9E 00 00
00 00 00 00 00 00 00 00 00 
3A 9D 00 00 
01 00 
4B 04 00 00 00 80 86 C7 92 
FC 99 00 00 
01 00 
46 06 00 00 00 00 03 83 76 
2F 9D 00 00 
01 00 
4F 04 00 00 00 00 0D 43 5A 
9A 9D 00 00 
01 00 
18 0E 00 00 00 80 F7 FE 5E 
92 A8 00 00 
00 00 00 00 00 00 00 00 00 

1 spent
8F 95 88 A7 01 03 
46 00 00 00 
01 00 
01 - counter ?
1C 07 00 00 
00 - rank1 ?
06 6E 01 B7 01 B8 01 70 01 B9 01 B3 02 FF FF 07 00 6C B0 00 00 2D 00 E9 0E 2C 0E 84 0D D3 0A 00 00 00 00 6C A9 75 81 9C 00 00 00 00 00 00 00 80 0F 39 7D 3B 9E 00 00 25 00 D1 0E 77 0D 35 0B 00 00 00 00 00 00 00 7F 00 00 00 00 00 00 00 00 00 00 00 00 37 9E 00 00 0C 00 77 0D 84 0D 00 00 00 00 00 00 00 D3 99 00 00 44 00 8B 0D 91 0E 00 00 00 40 EA CD 21 57 B0 00 00 2D 00 EF 0E 77 0D 8B 0D 1B 0D 00 00 00 80 40 46 4F 65 9E 00 00 01 00 F2 0E 00 00 00 80 A4 DC 8C 6E 99 00 00 01 00 40 06 00 00 00 36 D9 FE 5E 38 9E 00 00 25 00 A2 0C 84 0D EC 0C 00 00 00 00 00 00 00 1A 9E 00 00 00 00 00 00 00 00 E3 FC 28 0D 9F 00 00 00 00 00 00 00 00 00 00 00 B5 9D 00 00 00 00 00 00 00 80 22 F8 4F EC 9E 00 00 00 00 00 00 00 00 00 00 00 3A 9D 00 00 01 00 4B 04 00 00 00 80 86 C7 92 FC 99 00 00 01 00 46 06 00 00 00 00 03 83 76 2F 9D 00 00 01 00 4F 04 00 00 00 00 0D 43 5A 9A 9D 00 00 01 00 18 0E 00 00 00 80 F7 FE 5E 92 A8 00 00 00 00 00 00 00 00 00 00 00 

3 spent
8F 95 88 A7 01 03
44 00 00 00 
01 00 
01 
1C 07 00 00 - talententry = 1820 = hawk eye
02 -rank2
06 6E 01 B7 01 B8 01 70 01 B9 01 B3 02 FF FF 07 00 6C B0 00 00 2D 00 E9 0E 2C 0E 84 0D D3 0A 00 00 00 00 6C A9 75 81 9C 00 00 00 00 00 00 00 80 0F 39 7D 3B 9E 00 00 25 00 D1 0E 77 0D 35 0B 00 00 00 00 00 00 00 7F 00 00 00 00 00 00 00 00 00 00 00 00 37 9E 00 00 0C 00 77 0D 84 0D 00 00 00 00 00 00 00 D3 99 00 00 44 00 8B 0D 91 0E 00 00 00 40 EA CD 21 57 B0 00 00 2D 00 EF 0E 77 0D 8B 0D 1B 0D 00 00 00 80 40 46 4F 65 9E 00 00 01 00 F2 0E 00 00 00 80 A4 DC 8C 6E 99 00 00 01 00 40 06 00 00 00 36 D9 FE 5E 38 9E 00 00 25 00 A2 0C 84 0D EC 0C 00 00 00 00 00 00 00 1A 9E 00 00 00 00 00 00 00 00 E3 FC 28 0D 9F 00 00 00 00 00 00 00 00 00 00 00 B5 9D 00 00 00 00 00 00 00 80 22 F8 4F EC 9E 00 00 00 00 00 00 00 00 00 00 00 3A 9D 00 00 01 00 4B 04 00 00 00 80 86 C7 92 FC 99 00 00 01 00 46 06 00 00 00 00 03 83 76 2F 9D 00 00 01 00 4F 04 00 00 00 00 0D 43 5A 9A 9D 00 00 01 00 18 0E 00 00 00 80 F7 FE 5E 92 A8 00 00 00 00 00 00 00 00 00 00 00 
*/

	uint64 guid;
	uint32 talent_points;
	recv_data >> guid;

	Player * player = _player->GetMapMgr()->GetPlayer( guid );

	if( player == NULL )
	{
		sLog.outError( "HandleInspectOpcode: guid was null" );
		return;
	}
	talent_points = player->GetUInt32Value( PLAYER_CHARACTER_POINTS1 );

	_player->SetUInt64Value(UNIT_FIELD_TARGET, guid);

	_player->SetSelection( guid );

	if(_player->m_comboPoints)
		_player->UpdateComboPoints();

	WorldPacket data( SMSG_INSPECT_TALENT, 8 + 4 + 2 + 1 + talent_points * 6 + EQUIPMENT_SLOT_END * 13);

	data.appendPackGUID( guid );
	player->fill_talent_info_in_packet( data );
	uint32 slotUsedMask = 0;
	uint16 enchantmentMask = 0;
	size_t maskPos = data.wpos();
	data << uint32(slotUsedMask);	// will be replaced later. Blizz sent 0x0007FFFF
	for(uint32 slot = 0; slot < EQUIPMENT_SLOT_END; slot++)
	{
		Item *item = player->GetItemInterface()->GetInventoryItem( slot );
		if( item )
		{
			slotUsedMask |= 1 << slot;
			data << uint32(item->GetEntry());
			size_t maskPosEnch = data.wpos();
			enchantmentMask = 0;
			data << uint16(enchantmentMask); // will be replaced later
			for(uint32 ench = 0; ench < 12; ench++)
			{
				uint16 enchId = (uint16) item->GetUInt32Value( ITEM_FIELD_ENCHANTMENT_1_1 + ench * 3);
				if( enchId )
				{
					enchantmentMask |= 1 << ench;
					data << uint16(enchId);
				}
			}
			*(uint16*)&data.contents()[maskPosEnch] = enchantmentMask;
			data << uint16(0);	// unk
			FastGUIDPack(data, item->GetUInt32Value(ITEM_FIELD_CREATOR));
			data << uint32(0);	// unk
		}
	}
	*(uint32*)&data.contents()[maskPos] = slotUsedMask;

	SendPacket( &data );
}

void WorldSession::HandleSetActionBarTogglesOpcode(WorldPacket &recvPacket)
{
	uint8 cActionBarId;
	recvPacket >> cActionBarId;
	sLog.outDebug("Received CMSG_SET_ACTIONBAR_TOGGLES for actionbar id %d.", cActionBarId);

	GetPlayer()->SetByte(PLAYER_FIELD_BYTES,2, cActionBarId);
}

// Handlers for acknowledgement opcodes (removes some 'unknown opcode' flood from the logs)
void WorldSession::HandleAcknowledgementOpcodes( WorldPacket & recv_data )
{
	if(!_player)
	{ 
		return;
	}
	if(recv_data.GetOpcode() == CMSG_MOVE_WATER_WALK_ACK )
		_player->m_waterwalk = _player->m_setwaterwalk;
	else if(recv_data.GetOpcode() == CMSG_MOVE_SET_CAN_FLY_ACK )
		_player->FlyCheat = _player->m_setflycheat;

   /* uint16 opcode = recv_data.GetOpcode();
	std::stringstream ss;
	ss << "Received ";
	switch( opcode )
	{
	case CMSG_MOVE_FEATHER_FALL_ACK:			ss << "Move_Feather_Fall"; break;
	case CMSG_MOVE_WATER_WALK_ACK:			  ss << "Move_Water_Walk"; break;
	case CMSG_MOVE_KNOCK_BACK_ACK:			  ss << "Move_Knock_Back"; break;
	case CMSG_MOVE_HOVER_ACK:				   ss << "Move_Hover"; break;
	case CMSG_FORCE_WALK_SPEED_CHANGE_ACK:	  ss << "Force_Walk_Speed_Change"; break;
	case CMSG_FORCE_SWIM_SPEED_CHANGE_ACK:	  ss << "Force_Swim_Speed_Change"; break;
	case CMSG_FORCE_SWIM_BACK_SPEED_CHANGE_ACK: ss << "Force_Swim_Back_Speed_Change"; break;
	case CMSG_FORCE_TURN_RATE_CHANGE_ACK:	   ss << "Force_Turn_Rate_Change"; break;
	case CMSG_FORCE_RUN_SPEED_CHANGE_ACK:	   ss << "Force_Run_Speed_Change"; break;
	case CMSG_FORCE_RUN_BACK_SPEED_CHANGE_ACK:  ss << "Force_Run_Back_Speed_Change"; break;
	case CMSG_FORCE_MOVE_ROOT_ACK:			  ss << "Force_Move_Root"; break;
	case CMSG_FORCE_MOVE_UNROOT_ACK:			ss << "Force_Move_Unroot"; break;
	default:									ss << "Unknown"; break;
	}
	ss << " Acknowledgement. PktSize: " << recv_data.size();
	sLog.outDebug( ss.str().c_str() );*/

	/*uint16 opcode = recv_data.GetOpcode();
	if (opcode == CMSG_FORCE_RUN_SPEED_CHANGE_ACK)
	{
 
		uint64 GUID;
		uint32 Flags, unk0, unk1, d_time;
		float X, Y, Z, O, speed;
		
		recv_data >> GUID;
		recv_data >> unk0 >> Flags;
		if (Flags & (0x2000 | 0x6000))			 //0x2000 == jumping  0x6000 == Falling
		{
			uint32 unk2, unk3, unk4, unk5;
			float OldSpeed;

			recv_data >> d_time;
			recv_data >> X >> Y >> Z >> O;
			recv_data >> unk2 >> unk3;						  //no idea, maybe unk2 = flags2
			recv_data >> unk4 >> unk5;						  //no idea
			recv_data >> OldSpeed >> speed;
		}
		else													//single check
		{
			recv_data >> d_time;
			recv_data >> X >> Y >> Z >> O;
			recv_data >> unk1 >> speed;
		}
		
		// if its not good kick player???
		if (_player->GetPlayerSpeed() != speed)
		{
			sLog.outError("SpeedChange player:%s is NOT correct, its set to: %f he seems to be cheating",_player->GetName(), speed);
		}
	}*/

}

void WorldSession::HandleSelfResurrectOpcode(WorldPacket& recv_data)
{
	uint32 self_res_spell = _player->GetUInt32Value(PLAYER_SELF_RES_SPELL);
	if(self_res_spell)
	{
		SpellEntry * sp=dbcSpell.LookupEntry(self_res_spell);
		Spell *s=SpellPool.PooledNew();
		s->Init(_player,sp,true,NULL);
		SpellCastTargets tgt;
		tgt.m_unitTarget=_player->GetGUID();
		s->prepare(&tgt);	
	}
}

void WorldSession::HandleRandomRollOpcode(WorldPacket &recv_data)
{
	uint32 min, max;
	recv_data >> min >> max;

	sLog.outDetail("WORLD: Received MSG_RANDOM_ROLL: %u-%u", min, max);

	WorldPacket data(20);
	data.SetOpcode(MSG_RANDOM_ROLL);
	data << min << max;

	uint32 roll;

	if(max > RAND_MAX)
		max = RAND_MAX;
	
	if(min > max)
		min = max;
	min = 1; //zack : no, not going to let them cheat anymore ! :P

	// generate number
	roll = RandomUInt(max - min) + min;
	
	// append to packet, and guid
	data << roll << _player->GetGUID();

	// send to set
	if(_player->InGroup())
		_player->GetGroup()->SendPacketToAll(&data);
	else
	    SendPacket(&data);
}

void WorldSession::HandleLootMasterGiveOpcode(WorldPacket& recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
//	uint8 slot = 0;
	uint32 itemid = 0;
	uint32 amt = 1;
	uint8 error = 0;
	SlotResult slotresult;

	Creature *pCreature = NULL;
	GameObject *pGameObject = NULL; //ceberwow added it
	Object *pObj= NULL;
	Loot *pLoot = NULL;
	/* struct:
	{CLIENT} Packet: (0x02A3) CMSG_LOOT_MASTER_GIVE PacketSize = 17
	|------------------------------------------------|----------------|
	|00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |0123456789ABCDEF|
	|------------------------------------------------|----------------|
	|39 23 05 00 81 02 27 F0 01 7B FC 02 00 00 00 00 |9#....'..{......|
	|00											  |.			   |
	-------------------------------------------------------------------

		uint64 creatureguid
		uint8  slotid
		uint64 target_playerguid

	*/
	uint64 creatureguid, target_playerguid;
	uint8 slotid;
	recv_data >> creatureguid >> slotid >> target_playerguid;

	if(_player->GetGroup() == NULL || _player->GetGroup()->GetLooter() != _player->m_playerInfo)
		return;

	Player *player = _player->GetMapMgr()->GetPlayer( target_playerguid );
	if(!player)
		return;

	// cheaterz!
	if(_player->GetLootGUID() != creatureguid)
		return;

	//now its time to give the loot to the target player
	if(GET_TYPE_FROM_GUID(GetPlayer()->GetLootGUID()) == HIGHGUID_TYPE_UNIT)
	{
		pCreature = _player->GetMapMgr()->GetCreature( creatureguid );
		if (!pCreature)return;
		pLoot=&pCreature->loot;	
	}
	else
	if(GET_TYPE_FROM_GUID(GetPlayer()->GetLootGUID()) == HIGHGUID_TYPE_GAMEOBJECT) // ceberwow added it support gomastergive
	{
		pGameObject = _player->GetMapMgr()->GetGameObject( creatureguid );
		if (!pGameObject)return;
		pGameObject->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE,0);
		pLoot=&pGameObject->loot;
	}


	if(!pLoot)
		return;
	if ( pCreature )
		pObj = pCreature;
	else
		pObj = pGameObject;

	if ( !pObj )
		return;

  // telling him or not.
	/*float targetDist = player->CalcDistance(pObj);
  if(targetDist > 130.0f) {
    _player->GetSession()->SendNotification("so far!"));
    return;
  }*/

	if (slotid >= pLoot->items.size())
	{
		sLog.outDebug("AutoLootItem: Player %s might be using a hack! (slot %d, size %d)",GetPlayer()->GetName(), slotid, pLoot->items.size());
		return;
	}

	amt = pLoot->items.at(slotid).iItemsCount;

	if (!pLoot->items.at(slotid).ffa_loot)
	{
		if (!amt)//Test for party loot
		{  
			GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL,INV_ERR_ALREADY_LOOTED);
			return;
		} 
	}
	else
	{
		//make sure this player can still loot it in case of ffa_loot
		LooterSet::iterator itr = pLoot->items.at(slotid).has_looted.find(player->GetLowGUID());

		if (pLoot->items.at(slotid).has_looted.end() != itr)
		{
			GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL,INV_ERR_ALREADY_LOOTED);
			return;
		}
	}

	itemid = pLoot->items.at(slotid).item.itemproto->ItemId;
	ItemPrototype* it = pLoot->items.at(slotid).item.itemproto;

	if((error = player->GetItemInterface()->CanReceiveItem(it, 1)) != 0)
	{
		_player->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, error);
		return;
	}

	if(pCreature)
		CALL_SCRIPT_EVENT(pCreature, OnLootTaken)(player, it);
	
	
	slotresult = player->GetItemInterface()->FindFreeInventorySlot(it);
	if(!slotresult.Result)
	{
		GetPlayer()->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_INVENTORY_FULL);
		return;
	}

	Item *item = objmgr.CreateItem( itemid, player);
	
	item->SetUInt32Value(ITEM_FIELD_STACK_COUNT,amt);
	if(pLoot->items.at(slotid).iRandomProperty!=NULL)
	{
		item->SetRandomProperty(pLoot->items.at(slotid).iRandomProperty->ID);
		item->ApplyRandomProperties(false);
	}
	else if(pLoot->items.at(slotid).iRandomSuffix != NULL)
	{
		item->SetRandomSuffix(pLoot->items.at(slotid).iRandomSuffix->id);
		item->ApplyRandomProperties(false);
	}

	AddItemResult res = player->GetItemInterface()->SafeAddItem(item,slotresult.ContainerSlot, slotresult.Slot);
	if( res == ADD_ITEM_RESULT_OK )
	{
		player->GetSession()->SendItemPushResult(item,false,true,true,true,slotresult.ContainerSlot,slotresult.Slot,1);
		sQuestMgr.OnPlayerItemPickup(player,item);
	}
	else if( res == ADD_ITEM_RESULT_ERROR )
	{
		item->DeleteMe();
		item = NULL;
	}

	pLoot->items.at(slotid).iItemsCount=0;

	// this gets sent to all looters
	if (!pLoot->items.at(slotid).ffa_loot)
	{
		pLoot->items.at(slotid).iItemsCount=0;

		// this gets sent to all looters
		WorldPacket data(1);
		data.SetOpcode(SMSG_LOOT_REMOVED);
		data << slotid;
		Player * plr;
		for(LooterSet::iterator itr = pLoot->looters.begin(); itr != pLoot->looters.end(); ++itr)
		{
			if((plr = _player->GetMapMgr()->GetPlayer(*itr)) != 0)
				plr->GetSession()->SendPacket(&data);
		}
	}
	else
	{
		pLoot->items.at(slotid).has_looted.insert(player->GetLowGUID());
	}

/*    WorldPacket idata(45);
    if(it->Class == ITEM_CLASS_QUEST)
    {
        uint32 pcount = player->GetItemInterface()->GetItemCount(it->ItemId, true);
		BuildItemPushResult(&idata, GetPlayer()->GetGUID(), ITEM_PUSH_TYPE_LOOT, amt, itemid, pLoot->items.at(slotid).iRandomProperty ? pLoot->items.at(slotid).iRandomProperty->ID : 0,0xFF,0,0xFFFFFFFF,pcount);
    }
    else
    {
		BuildItemPushResult(&idata, player->GetGUID(), ITEM_PUSH_TYPE_LOOT, amt, itemid, pLoot->items.at(slotid).iRandomProperty ? pLoot->items.at(slotid).iRandomProperty->ID : 0);
    }

	if(_player->InGroup())
		_player->GetGroup()->SendPacketToAll(&idata);
	else
		SendPacket(&idata);*/
}

void WorldSession::HandleLootRollOpcode(WorldPacket& recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	/* struct:

	{CLIENT} Packet: (0x02A0) CMSG_LOOT_ROLL PacketSize = 13
	|------------------------------------------------|----------------|
	|00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |0123456789ABCDEF|
	|------------------------------------------------|----------------|
	|11 4D 0B 00 BD 06 01 F0 00 00 00 00 02		  |.M...........   |
	-------------------------------------------------------------------

	uint64 creatureguid
	uint21 slotid
	uint8  choice

	*/
	uint64 creatureguid;
	uint32 slotid;
	uint8 choice;
	recv_data >> creatureguid >> slotid >> choice;

	LootRoll *li = NULL;

	uint32 guidtype = GET_TYPE_FROM_GUID(creatureguid);
	if (guidtype == HIGHGUID_TYPE_GAMEOBJECT) 
	{
		GameObject* pGO = _player->GetMapMgr()->GetGameObject( creatureguid );
		if (!pGO)
			return;
		if (slotid >= pGO->loot.items.size() || pGO->loot.items.size() == 0)
			return;
		if (pGO->GetInfo() && pGO->GetInfo()->Type == GAMEOBJECT_TYPE_CHEST)
			li = pGO->loot.items[slotid].roll;
	} 
	else if (guidtype == HIGHGUID_TYPE_UNIT) 
	{
		// Creatures
		Creature *pCreature = _player->GetMapMgr()->GetCreature( creatureguid );
		if (!pCreature)
			return;

		//anti ninja, If we are not the tagger then don't steal loot. Can be done with packet hacks or group leave
		if( !(pCreature->TaggerGroupId == _player->GetGroup() || ( pCreature->TaggerGroupId == NULL && pCreature->TaggerGuid == _player->GetGUID() ) ) )
		{
			return;
		}

		if (slotid >= pCreature->loot.items.size() || pCreature->loot.items.size() == 0)
			return;

		li = pCreature->loot.items[slotid].roll;
	}
	else
		return;

	if(!li)
		return;

	li->PlayerRolled(_player, choice);
}

void WorldSession::HandleOpenItemOpcode(WorldPacket &recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	CHECK_PACKET_SIZE(recv_data, 2);
	int8 slot, containerslot;
	recv_data >> containerslot >> slot;

	Item *pItem = _player->GetItemInterface()->GetInventoryItem(containerslot, slot);
	if(!pItem)
	{ 
		return;
	}

	// gift wrapping handler
	if(pItem->GetUInt32Value(ITEM_FIELD_GIFTCREATOR) && pItem->wrapped_item_id)
	{
		ItemPrototype * it = ItemPrototypeStorage.LookupEntry(pItem->wrapped_item_id);
		if (it == NULL)
		{ 
			return;
		}

		pItem->SetUInt32Value(ITEM_FIELD_GIFTCREATOR,0);
		pItem->SetUInt32Value(OBJECT_FIELD_ENTRY,pItem->wrapped_item_id);
		pItem->wrapped_item_id=0;
		pItem->SetProto(it);

		if ( it->Bonding == ITEM_BIND_ON_PICKUP ) 
		{
			if(it->Flags & ITEM_FLAG_ACCOUNTBOUND) // don't "Soulbind" account-bound items
				pItem->AccountBind();
			else
				pItem->SoulBind();
		}

		if(it->MaxDurability)
		{
			pItem->SetUInt32Value(ITEM_FIELD_DURABILITY,it->MaxDurability);
			pItem->SetUInt32Value(ITEM_FIELD_MAXDURABILITY,it->MaxDurability);
		}

		pItem->m_isDirty=true;
		pItem->SaveToDB(containerslot,slot, false, NULL);
		return;
	}

	Lock *lock = dbcLock.LookupEntry( pItem->GetProto()->LockId );

	uint32 removeLockItems[5] = {0,0,0,0,0};

	if(lock) // locked item
	{
		for(int i=0;i<5;i++)
		{
			if(lock->locktype[i] == GO_LOCKTYPE_ITEM_REQ && lock->lockmisc[i] > 0)
			{
				int16 slot = _player->GetItemInterface()->GetInventorySlotById(lock->lockmisc[i]);
				if(slot != ITEM_NO_SLOT_AVAILABLE && slot >= INVENTORY_SLOT_ITEM_START && slot < INVENTORY_SLOT_ITEM_END)
				{
					removeLockItems[i] = lock->lockmisc[i];
				}
				else
				{
					_player->GetItemInterface()->BuildInventoryChangeError(pItem,NULL,INV_ERR_ITEM_LOCKED);
					return;
				}
			}
			else if(lock->locktype[i] == GO_LOCKTYPE_SKILL_REQ && pItem->locked)
			{
				_player->GetItemInterface()->BuildInventoryChangeError(pItem,NULL,INV_ERR_ITEM_LOCKED);
				return;
			}
		}
		for(int i=0;i<5;i++)
			if(removeLockItems[i])
				_player->GetItemInterface()->RemoveItemAmt(removeLockItems[i],1);
	}

	// fill loot
	_player->SetLootGUID(pItem->GetGUID());
	if(!pItem->loot)
	{
		pItem->loot = new Loot;
		lootmgr.FillItemLoot(pItem->loot, pItem->GetEntry());
	}
	_player->SendLoot(pItem->GetGUID(), LOOT_DISENCHANTING);
}

void WorldSession::HandleCompleteCinematic(WorldPacket &recv_data)
{
	// when a Cinematic is started the player is going to sit down, when its finished its standing up.
	_player->SetStandState(STANDSTATE_STAND);
};

void WorldSession::HandleResetInstanceOpcode(WorldPacket& recv_data)
{
	sInstanceMgr.ResetSavedInstances(_player);
}

void EncodeHex(const char* source, char* dest, uint32 size)
{
	char temp[5];
	for(uint32 i = 0; i < size; ++i)
	{
		snprintf(temp, 5, "%02X", source[i]);
		strcat(dest, temp);
	}
}

void DecodeHex(const char* source, char* dest, uint32 size)
{
	char temp = 0;
	char* acc = const_cast<char*>(source);
	for(uint32 i = 0; i < size; ++i)
	{
		sscanf("%02X", &temp);
		acc = ((char*)&source[2]);
		strcat(dest, &temp);
	}
}

void WorldSession::HandleToggleCloakOpcode(WorldPacket &recv_data)
{
	//////////////////////////
	//	PLAYER_FLAGS									   = 3104 / 0x00C20 / 0000000000000000000110000100000
	//																							 ^ 
	// This bit, on = toggled OFF, off = toggled ON.. :S

	//uint32 SetBit = 0 | (1 << 11);

	if(_player->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_NOCLOAK))
		_player->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_NOCLOAK);
	else
		_player->SetFlag(PLAYER_FLAGS, PLAYER_FLAG_NOCLOAK);
}

void WorldSession::HandleToggleHelmOpcode(WorldPacket &recv_data)
{
	//////////////////////////
	//	PLAYER_FLAGS									   = 3104 / 0x00C20 / 0000000000000000000110000100000
	//																							  ^ 
	// This bit, on = toggled OFF, off = toggled ON.. :S

	//uint32 SetBit = 0 | (1 << 10);

	if(_player->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_NOHELM))
		_player->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_NOHELM);
	else
		_player->SetFlag(PLAYER_FLAGS, PLAYER_FLAG_NOHELM);
}

void WorldSession::HandleDungeonDifficultyOpcode(WorldPacket& recv_data)
{
    uint32 data;
    recv_data >> data;

	if( data >= TOTAL_DUNGEON_DIFFICULTIES )
	{
		sLog.outDebug(" Trying to set an out of range dungeon difficulty mode");
		return;
	}
	Group * m_Group = _player->GetGroup();

    if(m_Group && _player->IsGroupLeader())
    {
		m_Group->dungeon_difficulty = data;
        sInstanceMgr.ResetSavedInstances(_player);
        m_Group->Lock();
		for(uint32 i = 0; i < m_Group->GetSubGroupCount(); ++i)
		{
			for(GroupMembersSet::iterator itr = m_Group->GetSubGroup(i)->GetGroupMembersBegin(); itr != m_Group->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
			{
				if((*itr)->m_loggedInPlayer)
				{
                    (*itr)->m_loggedInPlayer->dungeon_difficulty = data;
					(*itr)->m_loggedInPlayer->SendDungeonDifficulty();
				}
			}
		}
		m_Group->Unlock();
    }
    else if(!_player->GetGroup())
    {
        _player->dungeon_difficulty = data;
        sInstanceMgr.ResetSavedInstances(_player);
    }
}

void WorldSession::HandleRaidDifficultyOpcode(WorldPacket& recv_data)
{
    uint32 data;
    recv_data >> data;
	if( data >= TOTAL_RAID_DIFFICULTIES )
	{
		sLog.outDebug(" Trying to set an out of range  raid difficulty mode");
		return;
	}

	Group * m_Group = _player->GetGroup();

    if(m_Group && _player->IsGroupLeader())
    {
		m_Group->raid_difficulty = data;
        sInstanceMgr.ResetSavedInstances(_player);
        m_Group->Lock();
		for(uint32 i = 0; i < m_Group->GetSubGroupCount(); ++i)
		{
			for(GroupMembersSet::iterator itr = m_Group->GetSubGroup(i)->GetGroupMembersBegin(); itr != m_Group->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
			{
				if((*itr)->m_loggedInPlayer)
				{
                    (*itr)->m_loggedInPlayer->raid_difficulty = data;
					(*itr)->m_loggedInPlayer->SendRaidDifficulty();
				}
			}
		}
		m_Group->Unlock();
    }
    else if(!_player->GetGroup())
    {
        _player->raid_difficulty = data;
        sInstanceMgr.ResetSavedInstances(_player);
    }
}

void WorldSession::HandleSummonResponseOpcode(WorldPacket & recv_data)
{
	uint32 unk;
	uint32 SummonerGUID;
	uint8 IsClickOk;

	recv_data >> SummonerGUID >> unk >> IsClickOk;

	if(!IsClickOk)
	{ 
		return;
	}
	if(!_player->m_summoner)
	{
		SendNotification(NOTIFICATION_MESSAGE_NO_PERMISSION);
		return;
	}

	if(_player->CombatStatus.IsInCombat())
	{ 
		return;
	}

	_player->SafeTeleport( _player->m_summonMapId, _player->m_summonInstanceId, _player->m_summonPos );

	_player->m_summoner = _player->m_summonInstanceId = _player->m_summonMapId = 0;
}

void WorldSession::HandleDismountOpcode(WorldPacket& recv_data)
{
	sLog.outDebug( "WORLD: Received CMSG_CANCEL_MOUNT_AURA"  );

	if( !_player->IsInWorld() || _player->GetTaxiState())
	{ 
		return;
	}

	if( _player->m_MountSpellId )
		_player->RemoveAura( _player->m_MountSpellId );
}

void WorldSession::HandleSetAutoLootPassOpcode(WorldPacket & recv_data)
{
	uint32 on;
	recv_data >> on;

	if( _player->IsInWorld() )
		_player->BroadcastMessage("Auto loot passing is now %s.", on ? "on" : "off");

	_player->m_passOnLoot = (on!=0) ? true : false;
}

void WorldSession::HandleRealmStateRequestOpcode( WorldPacket & recv_data )
{
	CHECK_PACKET_SIZE(recv_data, 4);

	sLog.outDebug( "WORLD: Received CMSG_REALM_SPLIT");

	uint32 unk;
	std::string split_date = "01/01/01";
	recv_data >> unk;

	WorldPacket data(SMSG_REALM_SPLIT, 4+4+split_date.size()+1);
	data << unk;
	data << uint32(0x00000000);                             // realm split state
	// split states:
	// 0x0 realm normal
	// 0x1 realm split
	// 0x2 realm split pending
	data << split_date;
	SendPacket(&data);
}

