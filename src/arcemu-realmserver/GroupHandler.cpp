#include "RStdAfx.h"

void ClientMgr::DeleteGroup(uint32 guid)
{
	if (m_groups.find(guid) == m_groups.end())
		return;

	Group* g = m_groups[guid];

	for(uint32 i = 0; i < 8; ++i)
		for(uint32 j = 0; j < 5; ++j)
			if (g->members[i][j] && sClientMgr.GetRPlayer(g->members[i][j]))
			{
				Session * sess = sClientMgr.GetSession(sClientMgr.GetRPlayer(g->members[i][j])->Sessid);

				uint8 buffer[24];
				memset(buffer, 0, 24);
				sess->OutPacket( SMSG_GROUP_LIST, 24, buffer );

				WorldPacket data(50);

				data.SetOpcode( SMSG_GROUP_DESTROYED );
				sess->SendPacket( &data );
	
				data.Initialize( SMSG_PARTY_COMMAND_RESULT );
				data << uint32(2) << uint8(0) << uint32(0);  // you leave the group
				sess->SendPacket( &data );
			}

	m_groups.erase(m_groups.find(guid));
	delete g;
}

Group* ClientMgr::GetGroupForGuid(uint32 guid)
{
	for (GroupMap::iterator itr = m_groups.begin(); itr != m_groups.end(); ++itr)
	{
		Group* g = itr->second;

		for(uint32 i = 0; i < 8; ++i)
			for(uint32 j = 0; j < 5; ++j)
				if(g->members[i][j] == guid)
					return g;
	}
	return NULL;
}

void ClientMgr::LoadGroups()
{
	QueryResult * result = CharacterDatabase.Query("SELECT * FROM groups WHERE group_id < 2147483647");
	if(result)
	{
		if(result->GetFieldCount() != 51)
		{
			Log.LargeErrorMessage(LARGERRORMESSAGE_WARNING, "groups table format is invalid. Please update your database.");
			return;
		}
		do 
		{
			Field * fields = result->Fetch();
			Group * g = new Group;
			g->groupId = fields[0].GetUInt32();

			g->groupType = fields[1].GetUInt8();
			g->subCnt = fields[2].GetUInt8();
			g->lootMeth = fields[3].GetUInt8();
			g->lootThres = fields[4].GetUInt8();
			g->difficulty = fields[5].GetUInt8();
			g->leader = fields[6].GetUInt32();
			g->mTank = fields[7].GetUInt32();
			g->mAssist = fields[8].GetUInt32();

			// assign players into groups

			//megai2: null
			for(int i = 0; i < 8; ++i)
			{
				g->targetIcons[i] = 0;
				for(int j = 0; j < 5; ++j)
					g->members[i][j] = 0;
			}

			for(int i=0; i<NUM_MAPS; i++)
			{	
				for(int j=0; j<NUM_INSTANCE_MODES; j++)
				{
					g->instanceIds[i][j] = 0;
				}
			}

			for(int i = 0; i < g->subCnt; ++i)
			{
				for(int j = 0; j < 5; ++j)
				{
					uint32 guid = fields[9 + (i*5) + j].GetUInt32();
					if( guid == 0 )
						continue;
					
					g->members[i][j] = guid;
				}
			}
		
			char *ids = strdup(fields[50].GetString());
					char *q = ids;
			char *p = strchr(q, ' ');
			while(p)
			{
				char *r = strchr(q, ':');
				if(r == NULL || r > p)
					continue;
				*p = 0;
				*r = 0;
				char *s = strchr(r+1, ':');
				if(s == NULL || s > p)
					continue;
				*s = 0;
				uint32 mapId = atoi(q);
				uint32 mode = atoi(r+1);
				uint32 instanceId = atoi(s+1);
		
				if(mapId >= NUM_MAPS)
					continue;

				g->instanceIds[mapId][mode] = instanceId;
	
				q = p+1;
				p = strchr(q, ' ');
			}
			free(ids);
			
			m_groups[g->groupId] = g;

			g = NULL;	
		} while(result->NextRow());
		Log.Notice("ObjectMgr", "%u groups loaded.", result->GetRowCount());
		delete result;
	}
}

void ClientMgr::SaveGroups()
{	
	//megai2: saveall

	if (m_groups.empty())
		return;

	for (GroupMap::iterator itr = m_groups.begin(); itr != m_groups.end(); ++itr)
	{
		std::stringstream ss;

		ss.str("");

		Group* g = itr->second;

	/*	if(!m_disbandOnNoMembers)	// don't save bg groups 
			return;*/

		ss << "REPLACE INTO groups VALUES("
			<< g->groupId << ","
			<< uint32(g->groupType) << ","
			<< uint32(g->subCnt) << ","
			<< uint32(g->lootMeth) << ","
			<< uint32(g->lootThres) << ","
			<< uint32(g->difficulty) << ","
			<< g->leader << "," 
			<< g->mTank << ","
			<< g->mAssist << ",";
	
		for(uint32 i = 0; i < 8; ++i)
			for(uint32 j = 0; j < 5; ++j)
			{
				ss << g->members[i][j] << ",";
			}
	
	
		ss << (uint32)UNIXTIME << ",'";
		for(int i=0; i<NUM_MAPS; i++)
		{
			for(int j=0; j<NUM_INSTANCE_MODES; j++)
			{
				if(g->instanceIds[i][j] > 0)
				{
					ss << i << ":" << j << ":" << g->instanceIds << " ";
				}
			}
		}
		ss << "')";
		/*printf("==%s==\n", ss.str().c_str());*/

		CharacterDatabase.Query(ss.str().c_str());
	}
}
Group * ClientMgr::CreateGroup()
{
	++sGuidInfo.m_hiGroupGuid;

	Group * g = new Group;
	g->groupId = sGuidInfo.m_hiGroupGuid;

	g->groupType = GROUP_TYPE_PARTY;
	g->subCnt = 1;
	g->lootMeth = PARTY_LOOT_GROUP;
	g->lootThres = 2;
	g->difficulty = g->leader = g->mTank = g->mAssist = 0;

	//megai2: null
	for(int i = 0; i < 8; ++i)
	{
		g->targetIcons[i] = 0;
		for(int j = 0; j < 5; ++j)
			g->members[i][j] = 0;
	}

	for(int i = 0; i < NUM_MAPS; ++i)
		for(int j = 0; j < NUM_INSTANCE_MODES; ++j)
			g->instanceIds[i][j] = 0;
			
	m_groups[g->groupId] = g;

	return g;
}

void Session::GroupUpdate()
{
	Group* g = NULL;
	if (GetPlayer() && GetPlayer()->m_Group)
		g = GetPlayer()->m_Group;
	else
		return;

	WorldPacket data(SMSG_GROUP_LIST, 50 + ( 40 * 20 ));

	uint32 MemberCount = 0;

	for(int32 i = 0; i < 1 + 7 * g->groupType; ++i)
		for(uint32 j = 0; j < 5; ++j)
			if (g->members[i][j])
				++MemberCount;



	for(int32 i = 0; i < 1 + 7 * g->groupType; ++i)
		for(uint32 j = 0; j < 5; ++j)
		{
			if (g->members[i][j] == 0)
				continue;

			if (!sClientMgr.GetRPlayer(g->members[i][j]))
				continue;

			RPlayerInfo* plr = sClientMgr.GetRPlayer(g->members[i][j]);

			if (plr->onBg)
				continue;

			if (plr->LootInfo = -1 || plr->LootInfo != (g->lootThres << 16 | g->lootMeth))
				plr->LootInfo = g->lootThres << 16 | g->lootMeth;

			data.Initialize(SMSG_GROUP_LIST);
			data << uint8(g->groupType);	//0=party,1=raid
			data << uint8(0);   // unk
			data << uint8(i+1);
			data << uint8(0);	// unk2
			//data << uint64(0);	// unk3
			data << uint64(0x500000000004BC0CULL);
			data << uint32(MemberCount-1);	// we don't include self

			for(int32 k = 0; k < 1 + 7 * g->groupType; ++k)
				for(uint32 l = 0; l < 5; ++l)
				{
					if( g->members[i][j] == g->members[k][l])
						continue;

					// should never happen but just in case
					if(g->members[k][l] == 0)
						continue;

					data << sClientMgr.GetPlayerName(g->members[k][l]).c_str() << g->members[k][l] << uint32(0);	// highguid
							
					if( sClientMgr.GetRPlayer(g->members[k][l]) )
						data << uint8( 1 );
					else
						data << uint8( 0 );

					data << uint8( k + 1 );
						
					uint8 flags = 0;

					if( g->members[k][l] == g->leader )
						flags |= 1;
					if( g->members[k][l] == g->mTank )
						flags |= 2;
					if( g->members[k][l] == g->mAssist )
						flags |= 4;

					data << flags;
				}


			data << uint32(g->leader) << uint32(0) << uint8( g->lootMeth);
			data << uint64( 0 );//megai2: looter ><
			data << uint8( g->lootThres ) << uint8( g->difficulty );

			Session * Sess = sClientMgr.GetSession(plr->Sessid);
			Sess->SendPacket(&data);

			//megai2: походу я перебрал %)
			data.Initialize(ISMSG_PARTY_UPDATE);
			data << uint8(PUT_SELF_TO_OTHER);
			data << g->members[i][j];

			for(int32 k = 0; k < 1 + 7 * g->groupType; ++k)
				for(uint32 l = 0; l < 5; ++l)
				{
					if (g->members[k][l] && sClientMgr.GetRPlayer(g->members[k][l]))
						data << sClientMgr.GetRPlayer(g->members[k][l])->Sessid;
				}
			data << uint32(0);
				
			if (Sess->GetServer())
			{
				Sess->GetServer()->SendPacket(&data);
				sClientMgr.SendPlayerUpdate(plr->Guid);
			}
		}
}

#define BG_CHECK if (_player->onBg)  { if (GetServer()) GetServer()->SendWoWPacket(this, &pck); return;	}

void Session::HandleGroupInviteOpcode(WorldPacket & pck)
{
	RPlayerInfo * _player = NULL; 
	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	CHECK_PACKET_SIZE(pck, 1);
	WorldPacket data(100);
	std::string membername;
	RPlayerInfo * player = NULL;
	Group *group = NULL;

	pck >> membername;
	if(GetPlayer()->inviter)
		return;

	player = sClientMgr.GetRPlayerByName(membername.c_str());

	if ( player == NULL)
	{
		SendPartyCommandResult(_player, 0, membername, ERR_PARTY_CANNOT_FIND);
		return;
	}

	if (player == _player)
	{
		return;
	}

	if (player->onBg)
	{
		SendPartyCommandResult(_player, 0, membername, ERR_PARTY_ALREADY_IN_GROUP);
		return;
	}

	if (_player->m_Group && _player->m_Group->leader != _player->Guid)
	{
		SendPartyCommandResult(_player, 0, "", ERR_PARTY_YOU_ARE_NOT_LEADER);
		return;
	}

	group = _player->m_Group;
	if ( group != NULL )
	{
		if (group->IsFull())
		{
			SendPartyCommandResult(_player, 0, "", ERR_PARTY_IS_FULL);
			return;
		}
	}
	
	if ( player->m_Group )
	{
		SendPartyCommandResult(_player, player->m_Group->groupType, membername, ERR_PARTY_ALREADY_IN_GROUP);
		data.SetOpcode(SMSG_GROUP_INVITE);
		data << uint8(0);
		data << GetPlayer()->Name.c_str();
		sClientMgr.GetSession(player->Sessid)->SendPacket(&data);
		return;
	}
	
	if(player->GetTeam()!=_player->GetTeam() && _player->GMPermissions.length() == 0 && !sConfig.interfaction_group)
	{
		SendPartyCommandResult(_player, 0, membername, ERR_PARTY_WRONG_FACTION);
		return;
	}

	if ( player->inviter )
	{
		SendPartyCommandResult(_player, 0, membername, ERR_PARTY_ALREADY_IN_GROUP);
		return;
	}

	/*if( player->Social_IsIgnoring( _player->GetLowGUID() ) )
	{
		SendPartyCommandResult(_player, 0, membername, ERR_PARTY_IS_IGNORING_YOU);
		return;
	}*/
	
	if(player->bGMTag)
	{
		SendPartyCommandResult(_player, 0, membername, ERR_PARTY_CANNOT_FIND);
		return;
	}
	
	data.SetOpcode(SMSG_GROUP_INVITE);
	data << uint8(1);
	data << GetPlayer()->Name.c_str();

	sClientMgr.GetSession(player->Sessid)->SendPacket(&data);

	uint32 gtype = 0;
	if(group)
		gtype = group->groupType;

	SendPartyCommandResult(_player, gtype, membername, ERR_PARTY_NO_ERROR);

	// 16/08/06 - change to guid to prevent very unlikely event of a crash in deny, etc
	player->inviter = _player->Guid;
}

void Session::HandleGroupCancelOpcode(WorldPacket & pck){ 

} 

void Session::HandleGroupAcceptOpcode(WorldPacket & pck)
{ 
	RPlayerInfo * _player;

	if (!GetPlayer() || !GetPlayer()->inviter)
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	//if(!_player->IsInWorld()) return;

	RPlayerInfo *player = sClientMgr.GetRPlayer(_player->inviter);
	if ( !player )
		return;
	
	player->inviter = 0;
	_player->inviter = 0;

	if (player->onBg)
		return;
	
	Group *grp = player->m_Group;

	if(grp)
	{
		if (grp->AddMember(_player->Guid))
			_player->m_Group = grp;

		GroupUpdate();

		//_player->iInstanceType = grp->m_difficulty;
		//_player->SendDungeonDifficulty();

        //sInstanceSavingManager.ResetSavedInstancesForPlayer(_player);
		return;
	}
	
	// If we're this far, it means we have no existing group, and have to make one.
	
	grp = sClientMgr.CreateGroup();
	grp->difficulty = 0/*player->iInstanceType*/;
	grp->leader = player->Guid;
	if (grp->AddMember(player->Guid))		// add the inviter first, therefore he is the leader
		player->m_Group = grp;
	if (grp->AddMember(_player->Guid))		// add us.
		_player->m_Group = grp;	  

	WorldPacket data( SMSG_GROUP_SET_LEADER, player->Name.length() + 1 );
	data << player->Name;
	for(int32 i = 0; i < 1 + 7 * grp->groupType; ++i)
		for(uint32 j = 0; j < 5; ++j)
		{	
			if (sClientMgr.GetRPlayer(grp->members[i][j]))
				sClientMgr.GetSession(sClientMgr.GetRPlayer(grp->members[i][j])->Sessid)->SendPacket(&data);	
		}

	GroupUpdate();

	//_player->iInstanceType = grp->m_difficulty;
	//_player->SendDungeonDifficulty();

	/*Instance *instance = sInstanceMgr.GetInstanceByIds(player->GetMapId(), player->GetInstanceID());
	if(instance != NULL && instance->m_creatorGuid == player->GetLowGUID())
	{
		grp->m_instanceIds[instance->m_mapId][instance->m_difficulty] = instance->m_instanceId;
		instance->m_creatorGroup = grp->GetID();
		instance->m_creatorGuid = 0;
		instance->SaveToDB();
	}*/

    //sInstanceSavingManager.ResetSavedInstancesForPlayer(_player);

	// Currentgroup and all that shit are set by addmember.
} 

void Session::HandleGroupDeclineOpcode(WorldPacket & pck)
{ 
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	WorldPacket data(SMSG_GROUP_DECLINE, 100);

	RPlayerInfo* player = sClientMgr.GetRPlayer(GetPlayer()->inviter);
	if(!player) 
		return;

	data << GetPlayer()->Name.c_str();

	sClientMgr.GetSession(player->Sessid)->SendPacket( &data );
	player->inviter = 0;
	GetPlayer()->inviter = 0;
} 

void Session::HandleGroupUninviteOpcode(WorldPacket & pck)
{ 
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	CHECK_PACKET_SIZE(pck, 1);
	std::string membername;
	Group *group;
	RPlayerInfo * player;

	pck >> membername;

	player = sClientMgr.GetRPlayerByName(membername.c_str());
	if ( player == NULL && sClientMgr.GetPlayerGuid(membername) == 0)
	{
		SendPartyCommandResult(_player, 0, membername, ERR_PARTY_CANNOT_FIND);
		return;
	}

	if (player && (!_player->m_Group || _player->m_Group != player->m_Group))
	{
		SendPartyCommandResult(_player, 0, membername, ERR_PARTY_IS_NOT_IN_YOUR_PARTY);
		return;
	}

	if (_player->m_Group && _player->Guid != _player->m_Group->leader )
	{
		if (player == NULL)
		{
			SendPartyCommandResult(_player, 0, membername, ERR_PARTY_CANNOT_FIND);
			return;
		}
		else if(_player != player)
		{
			SendPartyCommandResult(_player, 0, "", ERR_PARTY_YOU_ARE_NOT_LEADER);
			return;
		}
	}

	group = _player->m_Group;

	//megai2: создаем инсту 
	if (player && sClientMgr.GetSession(player->Sessid)->GetTeleportPendingPck() != NULL)
	{
		SendPartyCommandResult(_player, 0, membername, ERR_PARTY_UNK);//megai2: WOW!
		return;
	}

	if(!group)
		return;

	if (group->RemoveMember(sClientMgr.GetPlayerGuid(membername)) && player)
		player->m_Group = NULL;	

	if (player)
	{
		Session * sess = sClientMgr.GetSession(player->Sessid);

		uint8 buffer[24];
		memset(buffer, 0, 24);
		sess->OutPacket( SMSG_GROUP_LIST, 24, buffer );

		WorldPacket data(50);

		data.SetOpcode( SMSG_GROUP_DESTROYED );
		sess->SendPacket( &data );
	
		data.Initialize( SMSG_PARTY_COMMAND_RESULT );
		data << uint32(2) << uint8(0) << uint32(0);  // you leave the group
		sess->SendPacket( &data );

		player->m_Group = NULL;
		player->LootInfo = -1;

		sClientMgr.SendPlayerUpdate(player->Guid);
	}

	if (_player == player)
	{
		for(int32 i = 0; i < 1 + 7 * group->groupType; ++i)
			for(uint32 j = 0; j < 5; ++j)
			{	
				if (group->members[i][j] && sClientMgr.GetRPlayer(group->members[i][j]))
				{
					sClientMgr.GetSession(sClientMgr.GetRPlayer(group->members[i][j])->Sessid)->GroupUpdate();
					break;
				}
			}
	} else
		GroupUpdate();

	uint32 MemberCount = 0;

	for(int32 i = 0; i < 1 + 7 * group->groupType; ++i)
		for(uint32 j = 0; j < 5; ++j)
			if (group->members[i][j])
				++MemberCount;

	if (MemberCount <= 2)
		HandleGroupDisbandOpcode(pck);
} 
void Session::HandleGroupUninviteGuildOpcode(WorldPacket & pck)
{ 

} 

void Session::HandleGroupSetLeaderOpcode(WorldPacket & pck)
{ 
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	CHECK_PACKET_SIZE(pck, 1);
	WorldPacket data;
	uint64 MemberGuid;
	RPlayerInfo * player;

	pck >> MemberGuid;
	
	player = sClientMgr.GetRPlayer((uint32)MemberGuid);

	if ( player == NULL )
	{
		//SendPartyCommandResult(_player, 0, membername, ERR_PARTY_CANNOT_FIND);
		SendPartyCommandResult(_player, 0, _player->Name, ERR_PARTY_CANNOT_FIND);
		return;
	}

	if(_player->m_Group->leader != _player->Guid)
	{
		SendPartyCommandResult(_player, 0, "", ERR_PARTY_YOU_ARE_NOT_LEADER);
		return;
	}
	
	if(player->m_Group != _player->m_Group)
	{
		//SendPartyCommandResult(_player, 0, membername, ERR_PARTY_IS_NOT_IN_YOUR_PARTY);
		SendPartyCommandResult(_player, 0, _player->Name, ERR_PARTY_IS_NOT_IN_YOUR_PARTY);
		return;
	}

	Group *pGroup = _player->m_Group;
	if(pGroup)
	{
		pGroup->leader = (uint32)MemberGuid;	
		WorldPacket data( SMSG_GROUP_SET_LEADER, player->Name.length() + 1 );
		data << player->Name;
		for(int32 i = 0; i < 1 + 7 * pGroup->groupType; ++i)
			for(uint32 j = 0; j < 5; ++j)
			{	
				if (sClientMgr.GetRPlayer(pGroup->members[i][j]))
					sClientMgr.GetSession(sClientMgr.GetRPlayer(pGroup->members[i][j])->Sessid)->SendPacket(&data);	
			}
		GroupUpdate();
	}
} 

void Session::HandleGroupDisbandOpcode(WorldPacket & pck)
{ 
	//megai2: походу оно работает как лив ><
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	Group* pGroup = _player->m_Group;
	if(!pGroup) 
		return;

	uint32 MemberCount = 0;

	for(int32 i = 0; i < 1 + 7 * pGroup->groupType; ++i)
		for(uint32 j = 0; j < 5; ++j)
			if (pGroup->members[i][j])
				++MemberCount;

	uint32 oldLead = pGroup->leader;

	//megai2: ремувим всех кого нужно!
	for(int32 i = 0; i < 1 + 7 * pGroup->groupType; ++i)
		for(uint32 j = 0; j < 5; ++j)
			if (pGroup->members[i][j] && (MemberCount <= 2 || pGroup->members[i][j] == _player->Guid))
			{
				RPlayerInfo * player = sClientMgr.GetRPlayer(pGroup->members[i][j]);
				if (player)
				{
					Session * sess = sClientMgr.GetSession(player->Sessid);

					//megai2: никуда ты не дисбанднешся, понял? -_-
					if (sess->GetTeleportPendingPck() != NULL)
						return;
		
					uint8 buffer[24];
					memset(buffer, 0, 24);
					sess->OutPacket( SMSG_GROUP_LIST, 24, buffer );

					WorldPacket data(50);

					data.SetOpcode( SMSG_GROUP_DESTROYED );
					sess->SendPacket( &data );
		
					data.Initialize( SMSG_PARTY_COMMAND_RESULT );
					data << uint32(2) << uint8(0) << uint32(0);  // you leave the group
					sess->SendPacket( &data );

					player->m_Group = NULL;
					player->LootInfo = -1;

					sClientMgr.SendPlayerUpdate(player->Guid);
				}
				pGroup->RemoveMember(pGroup->members[i][j]);
			}

	RPlayerInfo* lead = sClientMgr.GetRPlayer(pGroup->leader);
	if (lead && pGroup->leader != oldLead)
	{
		WorldPacket data( SMSG_GROUP_SET_LEADER, lead->Name.length() + 1 );
		data << lead->Name;
		for(int32 i = 0; i < 1 + 7 * pGroup->groupType; ++i)
			for(uint32 j = 0; j < 5; ++j)
			{	
				if (sClientMgr.GetRPlayer(pGroup->members[i][j]))
					sClientMgr.GetSession(sClientMgr.GetRPlayer(pGroup->members[i][j])->Sessid)->SendPacket(&data);	
			}		
	}



	if (MemberCount <= 2)
		sClientMgr.DeleteGroup(pGroup->groupId);

	_player->m_Group = NULL;
} 
 
void Session::HandleLootMethodOpcode(WorldPacket & pck)
{ 
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	CHECK_PACKET_SIZE(pck, 16);

	if (!_player->m_Group)
		return;

	uint32 lootMethod;
	uint64 lootMaster;
	uint32 threshold;

	pck >> lootMethod >> lootMaster >> threshold;
  
	if(_player->m_Group->leader != _player->Guid)
	{
		SendPartyCommandResult(_player, 0, "", ERR_PARTY_YOU_ARE_NOT_LEADER);
		return;
	}
	
	Group* pGroup = _player->m_Group; 

	if( pGroup == NULL)
		return;

	pGroup->lootMeth = lootMethod;
	pGroup->looter = GetPlayer()->Guid;
	pGroup->lootThres = threshold;

	GroupUpdate();

	//megai2: TODO

	/*Player * pLootMaster = objmgr.GetPlayer((uint32)lootMaster);

	if ( pLootMaster )
		pGroup->SetLooter(pLootMaster , lootMethod, threshold );
	else
		pGroup->SetLooter(_player , lootMethod, threshold );*/

  // cebernic: Extended this code,it supports diff leader & lootmaster.
 /* Player *plr = objmgr.GetPlayer((uint32)lootMaster);
  if ( _player->m_playerInfo->guid == lootMaster || !plr) {
    Group* pGroup = _player->GetGroup();
    if ( !pGroup ) return;
    pGroup->SetLooter(_player, lootMethod, threshold );
  }
  else {
    Group* pGroup = plr->GetGroup();
    if ( !pGroup ) return;
    pGroup->SetLooter(plr, lootMethod, threshold );
  }*/
} 

void Session::HandleMinimapPingOpcode(WorldPacket & pck)
{ 
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();	

	BG_CHECK

	CHECK_PACKET_SIZE(pck, 8);

	if(!_player->m_Group)
		return;

	Group * party= _player->m_Group;

	if(!party)
		return;

	float x,y;
	pck >> x >> y;
	WorldPacket data;
	data.SetOpcode(MSG_MINIMAP_PING);
	data << uint64(_player->Guid);
	data << x << y;
	for(int32 i = 0; i < 1 + 7 * party->groupType; ++i)
		for(uint32 j = 0; j < 5; ++j)
		{	
			if (sClientMgr.GetRPlayer(party->members[i][j]))
				sClientMgr.GetSession(sClientMgr.GetRPlayer(party->members[i][j])->Sessid)->SendPacket(&data);	
		}
} 
void Session::HandleConvertGroupToRaidOpcode(WorldPacket & pck)
{ 
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	// This is just soooo easy now   
	Group *pGroup = _player->m_Group;
	if(!pGroup)
		return;

	if ( pGroup->leader != _player->Guid )   //access denied
	{
		SendPartyCommandResult(_player, 0, "", ERR_PARTY_YOU_ARE_NOT_LEADER);
		return;
	}

	pGroup->groupType = GROUP_TYPE_RAID;
	SendPartyCommandResult(_player, 0, "", ERR_PARTY_NO_ERROR);
	GroupUpdate();
} 
 
void Session::HandleGroupChangeSubGroup(WorldPacket & pck)
{ 
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	std::string name;
	uint8 subGroup;

	pck >> name;
	pck >> subGroup;

	uint32 inf = sClientMgr.GetPlayerGuid(name);
	--subGroup;
	
	if(!inf || !_player->m_Group || subGroup > 7)
		return;

	Group * g = _player->m_Group;

	if (g->groupType != GROUP_TYPE_RAID)
		return;
	
	for(int32 i = 0; i < 8; ++i)
		for(uint32 j = 0; j < 5; ++j)
		{	
			if (g->members[i][j] == inf)
			{
				for(uint32 l = 0; l < 5; ++l)				
				{
					if (g->members[subGroup][l] == 0)
					{
						g->members[subGroup][l] = inf;
						g->members[i][j] = 0;
						GroupUpdate();
						return;
					}
				}
				//megai2: занято! делаем свап
				uint32 tmp = g->members[subGroup][0];
				g->members[subGroup][0] = inf;
				g->members[i][j] = tmp;
				GroupUpdate();
				return;
			}	
		}
} 
 
void Session::HandleGroupAssistantLeader(WorldPacket & pck)
{ 
	uint64 guid;
	uint8 on;

	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	if(_player->m_Group == NULL)
		return;

	if ( _player->Guid != _player->m_Group->leader )   //access denied
	{
		SendPartyCommandResult(_player, 0, "", ERR_PARTY_YOU_ARE_NOT_LEADER);
		return;
	}

	pck  >> guid >> on;

	if(on == 0)
	{
		_player->m_Group->mAssist = 0;
	}
	else
	{
		RPlayerInfo * np = sClientMgr.GetRPlayer((uint32)guid);
		if(np==NULL)
			_player->m_Group->mAssist = 0;
		else
		{
			if(_player->m_Group == np->m_Group)
				_player->m_Group->mAssist = uint32(guid);
		}
	}
	GroupUpdate();
} 
 
void Session::HandleRequestRaidInfoOpcode(WorldPacket & pck)
{ 

} 
 
void Session::HandleReadyCheckOpcode(WorldPacket & pck)
{ 
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	Group * pGroup  = _player->m_Group;

	if(!pGroup)
		return;

	if(pck.size() == 0)
	{
		if(pGroup->leader == _player->Guid)
		{
			WorldPacket data(MSG_RAID_READY_CHECK, 8);
			data << (uint64)GetPlayer()->Guid;
			/* send packet to group */
			for(int32 i = 0; i < 1 + 7 * pGroup->groupType; ++i)
				for(uint32 j = 0; j < 5; ++j)
				{	
					if (sClientMgr.GetRPlayer(pGroup->members[i][j]))
						sClientMgr.GetSession(sClientMgr.GetRPlayer(pGroup->members[i][j])->Sessid)->SendPacket(&data);	
				}			
		}
	}
	else
	{
		uint8 ready;
		pck >> ready;

		WorldPacket data(MSG_RAID_READY_CHECK_CONFIRM, 9);
		data << (uint64)_player->Guid;
		data << ready;

		if(pGroup->leader && sClientMgr.GetRPlayer(pGroup->leader))
			sClientMgr.GetSession(sClientMgr.GetRPlayer(pGroup->leader)->Sessid)->SendPacket(&data);	
	}
} 
 
void Session::HandleSetPlayerIconOpcode(WorldPacket & pck)
{ 
	uint64 guid;
	uint8 icon;
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	// This is just soooo easy now   
	Group *pGroup = _player->m_Group;
	if(!pGroup)
		return;

	pck >> icon;

	if(icon == 0xFF)
	{
		// client request
		WorldPacket data(MSG_RAID_TARGET_UPDATE, 73);
		data << uint8(1);
		for(uint8 i = 0; i < 8; ++i)
			data << i << pGroup->targetIcons[i];

		SendPacket(&data);
	}
	else if(_player->Guid == pGroup->leader)
	{
		pck >> guid;
		if(icon > 7)
			return;			// whhopes,buffer overflow :p

		// setting icon
		WorldPacket data(MSG_RAID_TARGET_UPDATE, 10);
		data << uint8(0) << icon << guid;

		for(int32 i = 0; i < 1 + 7 * pGroup->groupType; ++i)
			for(uint32 j = 0; j < 5; ++j)
			{	
				if (sClientMgr.GetRPlayer(pGroup->members[i][j]))
					sClientMgr.GetSession(sClientMgr.GetRPlayer(pGroup->members[i][j])->Sessid)->SendPacket(&data);	
			}

		pGroup->targetIcons[icon] = uint32(guid);
	}
} 
 
void Session::HandlePartyMemberStatsOpcode(WorldPacket & pck)
{ 
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

	uint64 guid;
	pck >> guid;

	RPlayerInfo * plr = sClientMgr.GetRPlayer(uint32(guid));

	if(!_player->m_Group || !plr)
		return;

	WorldPacket data(200);
	if(_player->m_Group != plr->m_Group)
		return;			// invalid player


	data.Initialize(ISMSG_PARTY_UPDATE);
	data << PUT_OTHER_TO_SELF;

	data << uint32(guid);
	data << _player->Sessid;
	
	if (sClientMgr.GetSession(plr->Sessid)->GetServer())
		sClientMgr.GetSession(plr->Sessid)->GetServer()->SendPacket(&data);
} 
 
void Session::HandleGroupPromote(WorldPacket & pck)
{ 

} 

void Session::HandleDungeonDifficultyOpcode(WorldPacket& pck)
{
	RPlayerInfo * _player;

	if (!GetPlayer())
		return;
	else
		_player = GetPlayer();

	BG_CHECK

    uint32 data;
    pck >> data;

	if (data > NUM_INSTANCE_MODES - 1)
		return;

	Group * m_Group = _player->m_Group;

	if(m_Group && m_Group->leader == _player->Guid)
    {
		m_Group->difficulty = data;

		WorldPacket pack(MSG_SET_DUNGEON_DIFFICULTY, 12);
		pack << (uint32)m_Group->difficulty;
		pack << (uint32)0x1;
		pack << (uint32)1;
       
		for(int32 i = 0; i < 8; ++i)
			for(uint32 j = 0; j < 5; ++j)
			{
				if (!m_Group->members[i][j] || !sClientMgr.GetRPlayer(m_Group->members[i][j]))
					continue;

				sClientMgr.GetSession(sClientMgr.GetRPlayer(m_Group->members[i][j])->Sessid)->SendPacket(&pack);
			}
		
		GroupUpdate();

    }
	else if(!_player->m_Group)
    {
		WorldPacket data(MSG_SET_DUNGEON_DIFFICULTY, 12);
		data << (uint32)0;
		data << (uint32)0x1;
		data << (uint32)0;
		SendPacket(&data);
    }

#ifdef OPTIMIZED_PLAYER_SAVING
	_player->save_InstanceType();
#endif
}

void Session::SendPartyCommandResult(RPlayerInfo* pPlayer, uint32 p1, std::string name, uint32 err)
{
	// if error message do not work, please sniff it and leave me a message
	if(pPlayer)
	{
		WorldPacket data;
		data.Initialize(SMSG_PARTY_COMMAND_RESULT);
		data << p1;
		if(!name.length())
			data << uint8(0);
		else
			data << name.c_str();

		data << err;
		sClientMgr.GetSession(pPlayer->Sessid)->SendPacket(&data);
	}
}
 
