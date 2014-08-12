/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2009 <http://www.ArcEmu.org/>
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

void WorldSession::HandleBattlefieldPortOpcode(WorldPacket &recv_data)
{
	uint16 mapinfo, unk;
	uint8 action;
	uint32 bgtype;

	if(!_player->IsInWorld()) 
	{ 
		return;
	}
	recv_data >> unk >> bgtype >> mapinfo >> action;

	if(action == 0)
	{
		BattlegroundManager.RemovePlayerFromQueues(_player);
	}
	else
	{
		/* Usually the fields in the packet would've been used to check what instance we're porting into, however since we're not
		 * doing "queue multiple battleground types at once" we can just use our cached pointer in the player class. - Burlex
		 */

		if( _player->m_pendingBattleground )
		{
			if( BattlegroundManager.IsValidBGPointer( _player->m_pendingBattleground ) )
				_player->m_pendingBattleground->PortPlayer(_player);
			//omef mem corruption or i forgot to clear this variable ?
			else
			{
				_player->m_pendingBattleground = NULL; 
				BattlegroundManager.RemovePlayerFromQueues(_player);
			}
		}
	}
}

void WorldSession::HandleBattlefieldStatusOpcode(WorldPacket &recv_data)
{
	/* This is done based on whether we are queued, inside, or not in a battleground.
	 */
	if(_player->m_pendingBattleground)		// Ready to port
	{
		if( BattlegroundManager.IsValidBGPointer( _player->m_pendingBattleground ) )
			BattlegroundManager.SendBattlefieldStatus(_player, BF_STATUS_PACKET_ALLOW_ENTER_PLAYER, _player->m_pendingBattleground->GetType(), _player->m_pendingBattleground->GetId(), 120000, 0, _player->m_pendingBattleground->Rated());
		else
			_player->m_pendingBattleground = NULL;
	}
	else if(_player->m_bg)					// Inside a bg
		BattlegroundManager.SendBattlefieldStatus(_player, BF_STATUS_PACKET_TEL_PLAYER, _player->m_bg->GetType(), _player->m_bg->GetId(), (uint32)UNIXTIME - _player->m_bg->GetStartTime(), _player->GetMapId(), _player->m_bg->Rated());
	else									// None
		BattlegroundManager.SendBattlefieldStatus(_player, BF_STATUS_PACKET_REMOVE_PLAYER, 0, 0, 0, 0, 0);	
}

void WorldSession::HandleBattlefieldListOpcode(WorldPacket &recv_data)
{
/*	uint64 guid;
	recv_data >> guid;

	CHECK_INWORLD_RETURN;
	Creature * pCreature = _player->GetMapMgr()->GetCreature( GET_LOWGUID_PART(guid) );
	if( pCreature == NULL )
		return;

	SendBattlegroundList( pCreature, 0 );*/
	uint32 battlegroundType;
	uint8 requestType; // 0 = ShowBattlefieldList, 1 = RequestBattlegroundInstanceInfo
	recv_data >> battlegroundType >> requestType;
	CHECK_INWORLD_RETURN;
	BattlegroundManager.HandleBattlegroundListPacket(this, battlegroundType, false);
}

void WorldSession::SendBattlegroundList(Creature* pCreature, uint32 mapid)
{
	if(!pCreature)
	{ 
		return;
	}

	/* we should have a bg id selection here. */
	uint32 t = BATTLEGROUND_WARSONG_GULCH;
	if (mapid == 0)
	{
		if(pCreature->GetCreatureInfo())
		{
			if(strstr(pCreature->GetCreatureInfo()->SubName, "Arena") != NULL)
				t = BATTLEGROUND_ARENA_2V2;
			else if(strstr(pCreature->GetCreatureInfo()->SubName, "Arathi") != NULL)
				t = BATTLEGROUND_ARATHI_BASIN;
			else if(strstr(pCreature->GetCreatureInfo()->SubName, "Eye of the Storm") != NULL)
				t = BATTLEGROUND_EYE_OF_THE_STORM;
			else if(strstr(pCreature->GetCreatureInfo()->SubName, "Warsong") != NULL)
				t = BATTLEGROUND_WARSONG_GULCH;
			else if(strstr(pCreature->GetCreatureInfo()->SubName, "Alterac") != NULL)
				t = BATTLEGROUND_ALTERAC_VALLEY;
			else if(strstr(pCreature->GetCreatureInfo()->SubName, "Strand") != NULL)
				t = BATTLEGROUND_STRAND_OF_THE_ANCIENT;
		}
	}
	else
		t = mapid;

    BattlegroundManager.HandleBattlegroundListPacket( this, t, true );
}

void WorldSession::HandleBattleMasterHelloOpcode(WorldPacket &recv_data)
{
	CHECK_PACKET_SIZE(recv_data, 8);
	if( !_player->IsInWorld() )
	{ 
		return;
	}

	uint64 guid;
	recv_data >> guid;
	sLog.outDebug("Received CMSG_BATTLEMASTER_HELLO from " I64FMT, guid);

	Creature * bm = _player->GetMapMgr()->GetCreature( guid );

	if(!bm)
	{ 
		return;
	}

	if(!bm->isBattleMaster())		// Not a Battlemaster
	{ 
		return;
	}

	SendBattlegroundList(bm, 0);
}

void WorldSession::HandleLeaveBattlefieldOpcode(WorldPacket &recv_data)
{
	if(_player->m_bg && _player->IsInWorld())
	{
		if( BattlegroundManager.IsValidBGPointer( _player->m_bg ) )
			_player->m_bg->RemovePlayer(_player, false);
		else
			_player->m_bg = NULL;
	}
}

void WorldSession::HandleAreaSpiritHealerQueryOpcode(WorldPacket &recv_data)
{
	if(!_player->IsInWorld() || !_player->m_bg) 
	{ 
		return;
	}
	uint64 guid;
	recv_data >> guid;

	Creature * psg = _player->GetMapMgr()->GetCreature( guid );
	if(psg == NULL)
	{ 
		return;
	}
	
	uint32 restime = _player->m_bg->GetLastResurrect() + 30;
	if((uint32)UNIXTIME > restime)
		restime = 1000;
	else
		restime = (restime - (uint32)UNIXTIME) * 1000;

	WorldPacket data(SMSG_AREA_SPIRIT_HEALER_TIME, 12);
	data << guid << restime;
	SendPacket(&data);
}

void WorldSession::HandleAreaSpiritHealerQueueOpcode(WorldPacket &recv_data)
{
	if(!_player->IsInWorld() || !_player->m_bg) 
	{ 
		return;
	}
	uint64 guid;
	recv_data >> guid;
	Creature * psg = _player->GetMapMgr()->GetCreature( guid );
	if(psg == NULL)
	{ 
		return;
	}

	_player->m_bg->QueuePlayerForResurrect(_player, psg);
	_player->CastSpell(_player,2584,true);
}

void WorldSession::HandleBattlegroundPlayerPositionsOpcode(WorldPacket &recv_data)
{
	// empty opcode
	CBattleground *bg = _player->m_bg;
    if(!_player->IsInWorld() || !bg)
        return;

	if(bg->GetType() == BATTLEGROUND_WARSONG_GULCH)
    {
        uint32 count1 = 0;
		uint32 count2 = 0;

        Player *ap = objmgr.GetPlayer(static_cast<WarsongGulch*>(bg)->GetAllianceFlagHolderGUID());
        if(ap) ++count2;

        Player *hp = objmgr.GetPlayer(static_cast<WarsongGulch*>(bg)->GetHordeFlagHolderGUID());
        if(hp) ++count2;

        WorldPacket data(MSG_BATTLEGROUND_PLAYER_POSITIONS, (4+4+16*count1+16*count2));
        data << count1;
        data << count2;
		if(ap)
		{
			data << (uint64)ap->GetGUID();
			data << (float)ap->GetPositionX();
			data << (float)ap->GetPositionY();
		}
		if(hp)
		{
			data << (uint64)hp->GetGUID();
			data << (float)hp->GetPositionX();
			data << (float)hp->GetPositionY();
		}

		SendPacket(&data);
	}
	else if(bg->GetType() == BATTLEGROUND_EYE_OF_THE_STORM)
	{
		uint32 count1 = 0;
		uint32 count2 = 0;

		Player *ap = objmgr.GetPlayer(static_cast<EyeOfTheStorm*>(bg)->GetFlagHolderGUID());
		if(ap) ++count2;

		WorldPacket data(MSG_BATTLEGROUND_PLAYER_POSITIONS, (4+4+16*count1+16*count2));
		data << count1;
		data << count2;
		if(ap)
		{
			data << (uint64)ap->GetGUID();
			data << (float)ap->GetPositionX();
			data << (float)ap->GetPositionY();
		}

		SendPacket(&data);
	}
}

void WorldSession::HandleBattleMasterJoinOpcode(WorldPacket &recv_data)
{
	CHECK_INWORLD_RETURN

	if(_player->HasAura(BG_DESERTER))
	{
		WorldPacket data(SMSG_GROUP_JOINED_BATTLEGROUND, 4);
		data << (uint32) 0xFFFFFFFE;
		_player->GetSession()->SendPacket(&data);
		return;
	}

	if(_player->GetGroup() && _player->GetGroup()->m_isqueued)
	{
		SystemMessage("You are in a group that is already queued for a battleground or inside a battleground. Leave this first.");
		return;
	}

	/* are we already in a queue? */
	if(_player->m_bgIsQueued)
		BattlegroundManager.RemovePlayerFromQueues(_player);

	if(_player->IsInWorld())
		BattlegroundManager.HandleBattlegroundJoin(this, recv_data);
}

void WorldSession::HandleArenaJoinOpcode(WorldPacket &recv_data)
{
	CHECK_INWORLD_RETURN
	if(_player->GetGroup() && _player->GetGroup()->m_isqueued)
	{
		SystemMessage("You are in a group that is already queued for a battleground or inside a battleground. Leave this first.");
		return;
	}

	/* are we already in a queue? */
    if(_player->m_bgIsQueued)
		BattlegroundManager.RemovePlayerFromQueues(_player);

	uint32 bgtype=0;
	uint64 guid;
	uint8 arenacategory;
	uint8 as_group;
	uint8 rated_match;
    recv_data >> guid >> arenacategory >> as_group >> rated_match;
	switch(arenacategory)
	{
	case 0:		// 2v2
		bgtype = BATTLEGROUND_ARENA_2V2;
		break;

	case 1:		// 3v3
		bgtype = BATTLEGROUND_ARENA_3V3;
		break;

	case 2:		// 5v5
		bgtype = BATTLEGROUND_ARENA_5V5;
		break;
	}

	if(bgtype != 0)
		BattlegroundManager.HandleArenaJoin(this, bgtype, as_group, rated_match);
}

void WorldSession::HandleInspectHonorStatsOpcode( WorldPacket &recv_data )
{
    CHECK_PACKET_SIZE( recv_data, 8 );
	CHECK_INWORLD_RETURN

    uint64 guid;
    recv_data >> guid;

  	if( _player == NULL )
	{
		sLog.outError( "HandleInspectHonorStatsOpcode : _player was null" );
		return;
	}

	if( _player->GetMapMgr() == NULL )
	{
		sLog.outError( "HandleInspectHonorStatsOpcode : _player map mgr was null" );
		return;
	}

	if( _player->GetMapMgr()->GetPlayer( guid ) == NULL )
	{
		sLog.outError( "HandleInspectHonorStatsOpcode : guid was null" );
		return;
	}

    Player* player =  _player->GetMapMgr()->GetPlayer( guid );

    WorldPacket data( MSG_INSPECT_HONOR_STATS, 13 );

    data << player->GetGUID();
#ifndef CATACLYSM_SUPPORT
	data << (uint8)player->GetUInt32Value( PLAYER_FIELD_HONOR_CURRENCY );
#endif
    data << player->GetUInt32Value( PLAYER_FIELD_KILLS );
#ifndef CATACLYSM_SUPPORT
    data << player->GetUInt32Value( PLAYER_FIELD_TODAY_CONTRIBUTION );
    data << player->GetUInt32Value( PLAYER_FIELD_YESTERDAY_CONTRIBUTION );
#endif
    data << player->GetUInt32Value( PLAYER_FIELD_LIFETIME_HONORBALE_KILLS );

    SendPacket( &data );
}

void WorldSession::HandleInspectArenaStatsOpcode( WorldPacket & recv_data )
{
    CHECK_PACKET_SIZE( recv_data, 8 );
	CHECK_INWORLD_RETURN

    uint64 guid;
    recv_data >> guid;

    Player* player =  _player->GetMapMgr()->GetPlayer( guid );
	if( player == NULL )
	{
		sLog.outError( "HandleInspectHonorStatsOpcode : guid was null" );
		return;
	}

	uint32 id;

    for( uint8 i = 0; i < 3; i++ )
    {
		id = player->GetUInt32Value( PLAYER_FIELD_ARENA_TEAM_INFO_1_1 + ( i * ARENA_TEAM_INFO_SIZE ) + ARENA_TEAM_ID );
        if( id > 0 )
        {
            ArenaTeam* team = objmgr.GetArenaTeamById( id );
            if( team != NULL )
			{
				WorldPacket data( MSG_INSPECT_ARENA_TEAMS, 8 + 1 + 4 * 5 );
				data << player->GetGUID();
				data << team->m_type;
				data << team->m_id;
				data << team->m_stat_rating;
				data << team->m_stat_gamesplayedweek;
				data << team->m_stat_gameswonweek;
				data << team->m_stat_gamesplayedseason;
				SendPacket( &data );

			}
        }
    }
}


void WorldSession::HandlePVPLogDataOpcode(WorldPacket &recv_data)
{
	CHECK_INWORLD_RETURN
	if(_player->m_bg)
		_player->m_bg->SendPVPData(_player);
}



