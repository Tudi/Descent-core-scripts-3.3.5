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

void WorldSession::HandleLearnTalentOpcode( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
 	 
	uint32 talent_id, requested_rank;
	recv_data >> talent_id >> requested_rank;

	_player->LearnTalent( talent_id, requested_rank, false );
}

void WorldSession::HandleLearnPreviewTalentOpcode( WorldPacket & recv_data )
{
    uint32 talentcount;
    uint32 talentid;
    uint32 rank;

    sLog.outDebug("Recieved packet CMSG_LEARN_TALENTS_MULTIPLE.");

    if( !_player->IsInWorld() )
        return;

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

    recv_data >> talentcount;

    for( uint32 i = 0; i < talentcount; ++i )
    {
        recv_data >> talentid;
        recv_data >> rank;

        _player->LearnTalent( talentid, rank, true );
    }
}

void WorldSession::HandleUnlearnTalents( WorldPacket & recv_data )
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}

	//check if we have nearby trainer -> avoid respecing on the field
	std::set<Object*>::iterator itr;
	_player->AquireInrangeLock(); //make sure to release lock before exit function !
	bool found_trainer = false;
	for( itr = _player->GetInRangeSetBegin(); itr != _player->GetInRangeSetEnd(); itr++ )
	{
		if(!((*itr)->IsUnit()) || !SafeUnitCast((*itr))->isAlive() || !(*itr)->IsCreature())
			continue;
		Creature *cr = SafeCreatureCast(*itr);
		Trainer * pTrainer = cr->GetTrainer();
		if( pTrainer == NULL || !CanTrainAt(_player, pTrainer) )
			continue;
		found_trainer = true;
		break;
	}
	_player->ReleaseInrangeLock();
	//ups, we are using client script to respec anywhere
	if( found_trainer == false )
	{
		sLog.outDebug("ResetTalent: We are not close enough to a trainer");
		return;
	}

	uint32 playerGold = GetPlayer()->GetGold( );
	uint32 price = GetPlayer()->CalcTalentResetCost(GetPlayer()->GetTalentResetTimes());

	if( playerGold < price ) 
	{ 
		sLog.outDebug("ResetTalent: Not enough gold");
		return;
	}

	GetPlayer()->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TALENTS,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	GetPlayer()->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_NUMBER_OF_TALENT_RESETS,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	GetPlayer()->SetTalentResetTimes(GetPlayer()->GetTalentResetTimes() + 1);
	GetPlayer()->SetGold( playerGold - price );
	GetPlayer()->Reset_Talents();

/*	// Unlearn all talent spells
	WorldPacket data;
	std::list<uint32> *talentproto = GetPlayer()->getTalentproto();

	std::list<uint32>::iterator itr;
	for (itr = talentproto->begin(); itr != talentproto->end(); ++itr)
	{
		GetPlayer()->removeSpell((*itr));

		// Handled in removespell.
		//data.Initialize(SMSG_REMOVED_SPELL);
		//data << (*itr); 
		//SendPacket( &data );
	}
	talentproto->clear();
*/
}

void WorldSession::HandleUnlearnSkillOpcode(WorldPacket& recv_data)
{
	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	uint32 skill_line;
#ifndef CATACLYSM_SUPPORT
	uint32 points_remaining=_player->GetUInt32Value(PLAYER_CHARACTER_POINTS2);
#endif
	recv_data >> skill_line;

	// Cheater detection
	// if(!_player->HasSkillLine(skill_line)) return;

	// Remove any spells within that line that the player has
	_player->RemoveSpellsFromLine(skill_line);
	
	// Remove any quests finished and active for this skill
	_player->RemoveQuestsFromLine(skill_line);

	// Finally, remove the skill line.
	_player->_RemoveSkillLine(skill_line);

	//added by Zack : This is probably wrong or already made elsewhere : restore skill learnability
#ifndef CATACLYSM_SUPPORT
	if(points_remaining==_player->GetUInt32Value(PLAYER_CHARACTER_POINTS2))
	{
		//we unlearned a skill so we enable a new one to be learned
		skilllineentry *sk=dbcSkillLine.LookupEntry(skill_line);
		if(!sk)
		{ 
			return;
		}
		if(sk->type==SKILL_TYPE_PROFESSION && points_remaining<2)
			_player->SetUInt32Value(PLAYER_CHARACTER_POINTS2,points_remaining+1);
	}
#endif
}
