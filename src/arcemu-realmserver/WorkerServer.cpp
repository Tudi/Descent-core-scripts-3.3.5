/*
 * ArcEmu MMORPG Server
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

#include "RStdAfx.h"

//megai2: максимальное время ожидания ответа
#define MAX_PONG_TIME 90
//megai2: каждые 20с
#define PING_INTERVAL 20

WServerHandler  WServer::PHandlers[IMSG_NUM_TYPES];
WServerHandlerW WServer::WHandlers[NUM_MSG_TYPES];

void WServer::InitHandlers()
{
	memset(PHandlers, 0, sizeof(void*) * IMSG_NUM_TYPES);
	PHandlers[ICMSG_REGISTER_WORKER] = &WServer::HandleRegisterWorker;
	PHandlers[ICMSG_WOW_PACKET] = &WServer::HandleWoWPacket;
	PHandlers[ICMSG_PLAYER_LOGIN_RESULT] = &WServer::HandlePlayerLoginResult;
	//PHandlers[ICMSG_PLAYER_LOGOUT] = &WServer::HandlePlayerLogout;//SMSG_LOGOUT_COMPLETE
	PHandlers[ICMSG_TELEPORT_REQUEST] = &WServer::HandleTeleportRequest;
	PHandlers[ICMSG_PONG] = &WServer::HandlePong;
	PHandlers[ICMSG_PLAYER_CHANGE_SERVER_INFO] = &WServer::HandlePlayerChangeServerInfo;
	PHandlers[ICMSG_PLAYER_INFO] = &WServer::HandlePlayerInfoUpdate;
	PHandlers[ICMSG_GUID_INCREMENT] = &WServer::HandleGuidIncrement;
//	PHandlers[ICMSG_PLAYER_CREATED] = &WServer::HandlePlayerCreated;
	PHandlers[ICMSG_GUILD_DISBAND] = &WServer::HandleGuildDisband;
	PHandlers[ICMSG_MAIL_UPDATE] = &WServer::HandleMailUpdate;
	PHandlers[ICMSG_INSTANCE_CREATED] = &WServer::HandleInstanceCreated;
	PHandlers[ICMSG_UPDATE_GUILD_NAMES] = &WServer::HandleGuildNameUpdate;
	PHandlers[ICMSG_PARTY_UPDATE] = &WServer::HandlePartyUpdate;

	memset(WHandlers, 0, sizeof(void*) * NUM_MSG_TYPES);
	WHandlers[SMSG_LOGOUT_COMPLETE] = &WServer::HandlePlayerLogout;
	WHandlers[SMSG_LOOT_START_ROLL] = &WServer::HandleRollOps;
	WHandlers[SMSG_LOOT_ROLL] = &WServer::HandleRollOps;
	WHandlers[SMSG_LOOT_ALL_PASSED] = &WServer::HandleRollOps;
	WHandlers[SMSG_LOOT_ROLL_WON] = &WServer::HandleRollOps;
	WHandlers[SMSG_ITEM_PUSH_RESULT] = &WServer::HandleRollOps;
}

WServer::WServer(uint32 id, WSSocket * s) : m_id(id), m_socket(s)
{
	m_deleted = false;
	actQu = false;
	lastPing = (uint32)UNIXTIME - PING_INTERVAL;
	lastPong = (uint32)UNIXTIME;
	latency = 0;
}

WServer::~WServer(){
	//megai2: ищем себя и удаляем
	Log.Debug("WServer", "Worker %u has closed socket, cleanup", m_id);
	for(uint32 j = 1; j <= sClientMgr.GetSessionsCount(); ++j)
	{
		Session * currSess = sClientMgr.GetSession(j);
		//megai2: так должно работать т.к. обновления сессий и серверов идут в одном потоке
		if(currSess && currSess->GetServer() == this) {
			Log.Debug("World socket", "Removing player from session %u", j);
			LogoutPlayer(j, LS_LOGOUT); 
		} 
		if (currSess && ((currSess->GetTeleportPendingSID() == m_id) || (currSess->GetNextServer() == this)))
		{
			if (currSess->GetOldServer())
			{
				WorldPacket data = WorldPacket(SMSG_TRANSFER_ABORTED, 4); 
				data << uint32(0x02); 
				currSess->SendPacket(&data);
				currSess->SetNextServerValue(NULL);
				currSess->SetServer(currSess->GetOldServer());
			} else {
				//megai2: на случай если сервер падает во время загрузки
				WorldPacket data = WorldPacket(SMSG_CHARACTER_LOGIN_FAILED, 4); 
				data << uint8(CHAR_LOGIN_NO_WORLD);
				currSess->SendPacket(&data);
				if (currSess->GetPlayer())
					sClientMgr.DestroyRPlayerInfo(currSess->GetPlayer()->Guid);
				currSess->ClearCurrentPlayer();
				currSess->ClearServers();
			}
		}
		if (currSess && currSess->GetOldServer() == this)
			currSess->SetOldServer(NULL);
	}
	m_instances.clear();
}

void WServer::HandlePartyUpdate(WorldPacket & pck)
{
	uint32 session = 0;

	pck >> session;

	if (!sClientMgr.GetSession(session))
		return;

	Session* srcSess = sClientMgr.GetSession(session);
	RPlayerInfo* srcPlr = srcSess->GetPlayer();

	WorldPacket* data = new WorldPacket(SMSG_PARTY_MEMBER_STATS, 500);

	uint8* buf = new uint8[pck.size()-4];
	pck.read(buf, pck.size()-4);

	data->append(buf, pck.size()-4);
	data->wpos(0);
	data->rpos(0);

	if (srcPlr && srcPlr->m_Group)
	{
		Group* pGroup = srcPlr->m_Group;
		for(int32 i = 0; i < 1 + 7 * pGroup->groupType; ++i)
			for(uint32 j = 0; j < 5; ++j)
			{	
				if (!pGroup->members[i][j])
					continue;

				RPlayerInfo* dstPlr = sClientMgr.GetRPlayer(pGroup->members[i][j]);
				Session * dstSess = NULL;

				//megai2: если есть игрок значит в любом случае есть сессия
				if (!dstPlr)
					continue;

				dstSess = sClientMgr.GetSession(dstPlr->Sessid);

				dstSess->SendPacket(data);	
			}
	}
}

void WServer::HandleGuildDisband(WorldPacket & pck)
{
	//нет нужды обновлять RPlayerInfo, поскольку на текущем сервере это уже сделано, 
	// а на остальных таким же образом будет сделано.
	pck.SetOpcode(ISMSG_GUILD_DISBAND);
	sClusterMgr.DistributePacketToAll(&pck, this);
}

void WServer::HandleMailUpdate(WorldPacket & pck)
{
	uint32 guid;
	pck >> guid;
	RPlayerInfo *receiver = sClientMgr.GetRPlayer(guid);
	if(!receiver)
		return;
	WServer* dstServer = sClientMgr.GetSession(receiver->Sessid)->GetServer();

	if (!dstServer)
		return;
	
	pck.rpos(0);
	pck.SetOpcode(ISMSG_MAIL_UPDATE);
	dstServer->SendPacket(&pck);
}

void WServer::HandlePong(WorldPacket & pck)
{
	//megai2: от сервера до клиента, время от клиента до сервера не учитываеться
	pck >> latency;
}

void WServer::HandlePlayerCreated(WorldPacket & pck)
{
	uint32 acct;
	Session * sess;
	uint8 res;
	pck >> acct >> res;

	sClientMgr.bCharCreate = false;

	sess = sClientMgr.GetSessionByAcc(acct);
	if (!sess)
		return;

//	if ( res == E_CHAR_CREATE_SUCCESS )
	if ( res == 0 )
	{
		WorldPacket data(ISMSG_PLAYER_CREATED, 300);

		uint8* buf = new uint8[pck.size()-5];
		pck.read(buf, pck.size()-5);

		data.append(buf, pck.size()-5);
		data.wpos(0);
		data.rpos(0);
	
		sClusterMgr.DistributePacketToAll(&data, this);
	}

	sess->OutPacket(SMSG_CHAR_CREATE, 1, &res);
}

void WServer::HandleGuildNameUpdate(WorldPacket & pck)
{
	uint32 guid;
	std::string name;

	pck >> guid >> name;

	if (sClientMgr.m_guildNames.find(guid) != sClientMgr.m_guildNames.end())
		return;

	sClientMgr.m_guildNames.insert(make_pair(guid, name));
}

void WServer::HandleInstanceCreated(WorldPacket & pck)
{
	uint32 IID = 0;
	uint32 map = -1;
	uint32 res = 0;
	uint32 j = 1;

	pck >> IID >> map >> res;

	Log.Success("WServer", "Created instance %u map %u result %u", IID, map, res);

	if (!sClusterMgr.GetInstanceByInstanceId(IID) && IS_BG_MAP(map))
		sClusterMgr.AppendInstance(IID, map, this);

	if (res && sClusterMgr.GetInstanceByInstanceId(IID))
		sClusterMgr.GetInstanceByInstanceId(IID)->loading = false;

	//megai2: во время апдейта количество сессий не увеличиваеться
	for (uint32 i = 1; i <= sClientMgr.GetSessionsCount(); ++i) 
	{
		Session* sess = sClientMgr.GetSession(i);
		if (sess == NULL)
			continue;

		if (sess->GetTeleportPendingSID() == m_id && sess->GetTeleportPendingIID() == IID)
		{
			//megai2: порт или снятие пендинга с ошибкой %)	
			if (res && sess->GetTeleportPendingPck() && sess->GetServer())
				sess->GetServer()->HandleTeleportRequest(*sess->GetTeleportPendingPck());
			else {
				WorldPacket data = WorldPacket(SMSG_TRANSFER_ABORTED, 4); 
				data << uint32(0x02); 
				sess->SendPacket(&data);
				sess->SetTeleportPending(NULL, 0, 0);//megai2: ну и все)
			}
		}
	}
}

void WServer::HandleRegisterWorker(WorldPacket & pck)
{
	vector<WorldInstanceInfo> preferred;
	uint32 build;
	WorldInstanceInfo tmp;
	pck >> build;
	for (uint32 i = 1; i <= (pck.size() - 4) / 8; ++i) 
	{
		pck.read((uint8*)&tmp, 8);
		preferred.push_back(tmp);
	}

	Log.Debug("WServer", "Server %u registred (build %u)", GetID(), build);
	/* send a packed packet of all online players to this server */
	sClientMgr.SendPackedClientInfo(this);

	/* allocate initial instances for this worker */
	sClusterMgr.AllocateInitialInstances(this, preferred);
	if (preferred.empty())
	{
		type = WT_INSTANCE_WORLD;
		QueryResult * result = CharacterDatabase.Query("SELECT `id`, `mapid` FROM instances");
		if (result)
		{
			do 
			{

				Field* dt = result->Fetch();
				sClusterMgr.CreateInstance(dt[0].GetInt32(), dt[1].GetInt32());

			} while(result->NextRow());
		}
		delete result;
	}
	else if(preferred.size() == 2)
		type = WT_BATTLEGROUP_WORLD;
	else
		type = WT_CONTINENT;

	WorldPacket data(ISMSG_REGISTER_RESULT, 4);
	data << GetID();
	SendPacket(&data);
}

void WServer::HandleWoWPacket(WorldPacket & pck)
{
	uint32 sessionid, size;
	uint16 opcode;

	/* get session */
	pck >> sessionid >> opcode >> size;
	Session * session = sClientMgr.GetSession(sessionid);
	if(!session) 
		return;

	/* write it to that session's output buffer */
	WorldSocket * s = session->GetSocket();
	if(s) 
		s->OutPacket(opcode, size, size ? ((const void*)(pck.contents() + 10)) : 0);
}

void WServer::HandleWoWPacket(uint32 op, uint32 sessionid, WorldPacket & pck)
{
	Session * session = sClientMgr.GetSession(sessionid);
	if(!session)
		return;

	/* write it to that session's output buffer */
	WorldSocket * s = session->GetSocket();
	if(s)
		s->OutPacket(op, pck.size(), pck.size() ? ((const void*)(pck.contents() + 10)) : 0);
}

void WServer::HandlePlayerInfoUpdate(WorldPacket & pck)
{
	if (pck.size() < 9)
		return;
	uint32 guid;
	uint32 value;
	uint8 idx;

	pck >> guid >> idx >> value;

	if (!sClientMgr.GetRPlayer(guid))
		return;

	RPlayerInfo * plr = sClientMgr.GetRPlayer(guid);
	//megai2: делаю свитчем - мало ли что потом придется приделать
	switch (idx) 
	{
		case UI_LEVEL:
			{
				plr->Level = value;
			}break;
		case UI_GUILD:	
			{
				plr->GuildId = value;
			}break;
		case UI_ZONE:
			{
				plr->ZoneId = value;
			}break;
		case UI_GMTAG:
			{
				//megai2: ><
				plr->bGMTag = value!=0;
			}break;
		case UI_GUILDR:
			{
				plr->GuildPrem = value;
			}break;
		case UI_GINVITER:
			{
				plr->guildinviter = value;
			}break;
		default:
			return;
		break;
	}		

	WorldPacket* data = new WorldPacket(ISMSG_PLAYER_INFO, 300);
	plr->Pack(*data);
	sClusterMgr.DistributePacketToAll(data, this);
	//Log.Debug("WServer", "Updated  playerinfo of player %u (idx %u): set %i", guid, idx, value);
}

void WServer::LogoutPlayer(uint32 session, LogoutSrc src)
{
	Session * s = sClientMgr.GetSession(session);

	RPlayerInfo * pi = NULL;
	if (s)
		pi = s->GetPlayer();

	if(pi && s)
	{

		/* tell all other servers this player has gone offline */
		WorldPacket data(ISMSG_DESTROY_PLAYER_INFO, 4);
		data << pi->Guid << session;
		sClusterMgr.DistributePacketToAll(&data);

		if (src == LS_LOGOUT)
		{
			Log.Debug("WServer","Hooked SMSG_LOGOUT_COMPLETE to session %u", session);

			/* clear the player from the session */
			s->ClearCurrentPlayer();
			s->ClearServers();

			Group * pGroup = pi->m_Group;

			if (pGroup && pi->Guid == pGroup->leader)
			{
				for(int32 i = 0; i < 1 + 7 * pGroup->groupType; ++i)
					for(uint32 j = 0; j < 5; ++j)								
						if (pGroup->members[i][j] && pGroup->members[i][j] != pi->Guid && sClientMgr.GetRPlayer(pGroup->members[i][j]))
						{
							pGroup->leader = pGroup->members[i][j];
						}
				RPlayerInfo* lead = sClientMgr.GetRPlayer(pGroup->leader);
				if (lead)
				{
					WorldPacket data( SMSG_GROUP_SET_LEADER, lead->Name.length() + 1 );
					data << lead->Name;
					for(int32 i = 0; i < 1 + 7 * pGroup->groupType; ++i)
						for(uint32 j = 0; j < 5; ++j)
						{	
							if (sClientMgr.GetRPlayer(pGroup->members[i][j]) && pGroup->members[i][j] != pi->Guid)
								sClientMgr.GetSession(sClientMgr.GetRPlayer(pGroup->members[i][j])->Sessid)->SendPacket(&data);	
						}		
				}
			}

			/* destroy the playerinfo struct here */
			sClientMgr.DestroyRPlayerInfo(pi->Guid);

			//megai2: обновляем группу %)
			if (pGroup)
			{
				for(int32 i = 0; i < 1 + 7 * pGroup->groupType; ++i)
					for(uint32 j = 0; j < 5; ++j)
						if (pGroup->members[i][j] && sClientMgr.GetRPlayer(pGroup->members[i][j]))
						{
							sClientMgr.GetSession(sClientMgr.GetRPlayer(pGroup->members[i][j])->Sessid)->GroupUpdate();
							break;
						}
			}

			WorldPacket nullPck(0);
			HandleWoWPacket(SMSG_LOGOUT_COMPLETE, session, nullPck);
		}
	} 
}

void WServer::HandleRollOps(WorldPacket & pck, uint32 session)
{
	//megai2: лут виден тока на той мапе на которой убит моб
	if (!sClientMgr.GetSession(session))
		return;

	Session* srcSess = sClientMgr.GetSession(session);
	RPlayerInfo* srcPlr = srcSess->GetPlayer();

	if (srcPlr && srcPlr->m_Group)
	{
		Group* pGroup = srcPlr->m_Group;
		for(int32 i = 0; i < 1 + 7 * pGroup->groupType; ++i)
			for(uint32 j = 0; j < 5; ++j)
			{	
				if (!pGroup->members[i][j])
					continue;

				RPlayerInfo* dstPlr = sClientMgr.GetRPlayer(pGroup->members[i][j]);
				Session * dstSess = NULL;

				//megai2: если есть игрок значит в любом случае есть сессия
				if (!dstPlr)
					continue;

				dstSess = sClientMgr.GetSession(dstPlr->Sessid);

				//megai2: все игроки на данной карте =)
				if (dstSess->GetServer() != srcSess->GetServer() || dstPlr->InstanceId != srcPlr->InstanceId 
					|| dstPlr->MapId != srcPlr->MapId)
					continue;
				
				dstSess->SendPacket(&pck);	
			}
	} else if (srcPlr)
		srcSess->SendPacket(&pck);	
}

void WServer::HandlePlayerLogout(WorldPacket & pck, uint32 session)
{
	if (sClientMgr.GetSession(session) && !sClientMgr.GetSession(session)->GetNextServer() && sClientMgr.GetSession(session)->GetServer() == this)
		LogoutPlayer(session, LS_LOGOUT);
}

void WServer::HandleGuidIncrement(WorldPacket & pck)
{
	//megai2: инкремент!
	uint8 type;
	uint32 val;
	pck >> type;
	if (type == GT_CONTAINER)
		val = ++sGuidInfo.m_hiContainerGuid[GetID()-1];
	else if (type == GT_ITEM)
		val = ++sGuidInfo.m_hiItemGuid[GetID()-1];
	else if(type == GT_PLAYER)
		val = ++sGuidInfo.m_hiPlayerGuid[GetID()-1];	
	else if(type == GT_GUILD)
		val = ++sGuidInfo.m_hiGuildGuid[GetID()-1];
	else if (type == GT_AUCTION)
		val = ++sGuidInfo.m_auctionGuid[GetID()-1];
	else
		val = ++sGuidInfo.m_mailGuid[GetID()-1];

	Log.Debug("WServer", "Incremented guid %u to %u by server %u request", type, val, GetID());

	/*WorldPacket* data = new WorldPacket(ISMSG_GUID_INCREMENTED, 9);
	*data << type << val << GetID();
	sClusterMgr.DistributePacketToAll(data);
	delete data;*/
}

void WServer::HandleTeleportRequest(WorldPacket & pck)
{
	WorldPacket data(ISMSG_TELEPORT_RESULT, 100);
	RPlayerInfo * pi;
	Session * s;
	Instance * dest = NULL;
	uint32 mapid, sessionid, instanceid, wserverid;

	/* this packet is only used upon changing main maps! */
	pck >> sessionid >> mapid >> instanceid;

	wserverid = GetID();

	s = sClientMgr.GetSession(sessionid);
	if(s)
	{
		pi = s->GetPlayer();
		ASSERT(pi);

		//megai2: пыщь!
#define ABORT_TRANSFER { data.Initialize(SMSG_TRANSFER_ABORTED); data << uint32(0x02); s->SendPacket(&data); data << sessionid << uint8(2); SendPacket(&data); return; }

		if (mapid > NUM_MAPS)
			ABORT_TRANSFER

		/* find the destination server */
		//megai2: нету сервера ничего не создаем %)
		if(IS_BG_MAP(mapid) && mapid != 449 && mapid != 450)
		{
			//megai2: на случай если мир сразу портает в инст
			if (!sClusterMgr.GetInstanceByInstanceId(instanceid))
			{
				//megai2: нене не портаем %)
				//s->SetTeleportPending(&pck, dest->Server->GetID(), dest->InstanceId);
				ABORT_TRANSFER
			} else
				dest = sClusterMgr.GetInstanceByInstanceId(instanceid);
		}else
		if(!IS_MAIN_MAP(mapid) && sClusterMgr.GetWorkerServerForNewInstance())
		{
			MapInfo* mInf = WorldMapInfoStorage.LookupEntry(mapid);

			if ((!mInf || !mInf->HasFlag(0x1/*WMI_INSTANCE_ENABLED*/)) ||
				(mInf->minlevel > pi->Level) ||//megai2: проверка уровня
				(pi->m_Group && IS_HEROIC_INSTANCE_DIFFICULTIE( pi->m_Group->difficulty ) && mInf->type != INSTANCE_MULTIMODE && mInf->type != INSTANCE_NULL) ||//проверка доступности хероика
				(mInf->type == INSTANCE_RAID && (!pi->m_Group || (pi->m_Group && pi->m_Group->groupType != GROUP_TYPE_RAID))) ||//проверка рейда
				(mInf->type == INSTANCE_MULTIMODE && !pi->m_Group) ||//проверка группы
				(pi->Level<80 && pi->m_Group && IS_HEROIC_INSTANCE_DIFFICULTIE( pi->m_Group->difficulty ) && mInf->type == INSTANCE_MULTIMODE))//проверка лвла для героика
					ABORT_TRANSFER

			//megai2: без группы создавать инсты - нельзя
			if (pi->m_Group && pi->m_Group->instanceIds[mapid][pi->m_Group->difficulty] > 0)
			{
				dest = sClusterMgr.GetInstanceByInstanceId(pi->m_Group->instanceIds[mapid][pi->m_Group->difficulty]);
				//megai2: а если нету по какой либо причине?
				if (!dest)
				{
					if (!pi->m_Group)
						ABORT_TRANSFER
					dest = sClusterMgr.CreateInstance(0, mapid, IS_HEROIC_INSTANCE_DIFFICULTIE(pi->m_Group->difficulty ));
				}
			} else  {
				if (!pi->m_Group)
					ABORT_TRANSFER
				dest = sClusterMgr.CreateInstance(0, mapid, IS_HEROIC_INSTANCE_DIFFICULTIE(pi->m_Group->difficulty));
			}
		} else if(IS_MAIN_MAP(mapid))
			dest = sClusterMgr.GetInstanceByMapId(mapid);		
		else
			ABORT_TRANSFER

		if (!dest || !dest->Server)
			ABORT_TRANSFER

#undef ABORT_TRANSFER

		//megai2: место назначения найдено - биндим
		if (pi->m_Group)
			pi->m_Group->instanceIds[mapid][pi->m_Group->difficulty] = dest->InstanceId;

		//megai2: ещё грузица
		if (dest->loading)
		{
			WorldPacket* pndPck = new WorldPacket(pck);
			s->SetTeleportPending(pndPck, dest->Server->GetID(), dest->InstanceId);
			return;
		}

		instanceid = dest->InstanceId;

		/* server found! */
		LocationVector vec;
		pck >> vec.x >> vec.y >> vec.z >> vec.o;

		pi->MapId = mapid;
		pi->InstanceId = instanceid;
		pi->PositionX = vec.x;
		pi->PositionY = vec.y;
		pi->PositionZ = vec.z;

		s->lastPingTime = (uint32)UNIXTIME;
		s->lastPing = 0;
		
		/* notify the old server to pack the player info together to send to the new server, and delete the player */
		//megai2: ждем когда придет PlayerChangeServerInfo
		Log.Debug("WServer", "Player %s changing servers from %u to %u", pi->Name.c_str(), wserverid, dest->Server->GetID()); 
		s->SetServer(NULL);
		s->SetNextServerValue(dest->Server);
		data << sessionid << uint8(0) << mapid << instanceid;
		SendPacket(&data);
		
		s->SetTeleportPending(NULL, 0, 0);//megai2: очищяемс
	}
}

void WServer::HandlePlayerChangeServerInfo(WorldPacket & pck)
{
	//megai2: удалились со старого сервера, прыгаем на новый
	WorldPacket data(ISMSG_PLAYER_INFO, 100);
	RPlayerInfo * pi;
	Session * s;
	uint32 sessionid;	
	uint8 res;

	pck >> res >> sessionid;	

	s = sClientMgr.GetSession(sessionid);
	if(s)
	{
		pi = s->GetPlayer();
		ASSERT(pi);

		//megai2: ну не можем мы удалиться со старого сервера, продолжаем его юзать
		if (res != 0)
		{
			s->lastPing = 1;
			s->lastPingTime = (uint32)UNIXTIME;
			if (!s->GetOldServer())
			{
				sClientMgr.DestroyRPlayerInfo(pi->Guid);
				data.Initialize(SMSG_CHARACTER_LOGIN_FAILED);
				data << uint8(CHAR_LOGIN_NO_WORLD);
				s->SendPacket(&data);
				s->ClearCurrentPlayer();
				s->ClearServers();	
			} else {
				data.Initialize(SMSG_TRANSFER_ABORTED); 
				data << uint32(0x02); 
				s->SendPacket(&data); 
				s->SetServer(s->GetOldServer());
				s->SetNextServerValue(NULL);
			}
			return;
		}

		data.Initialize(ISMSG_PLAYER_INFO);
		pi->Pack(data);
		sClusterMgr.DistributePacketToAll(&data);

		float orient = 0;

		data.Initialize(SMSG_NEW_WORLD);
		data << pi->MapId << pi->PositionX << pi->PositionY << pi->PositionZ << orient;
		s->SendPacket(&data);

		Log.Debug("WServer", "Player %s logged out from old server sending logon message to new server", pi->Name.c_str());

		//megai2: обновляем пинг тайм, дискает иногда
		s->lastPingTime = (uint32)UNIXTIME;
		s->lastPing = 0;

		//игрок поменял свой сервер, логиним его по уже имеющейся инфе
		data.Initialize(ISMSG_PLAYER_CHANGED_SERVERS);
//		data << uint32(sessionid) << s->GetAccountName() << s->GetGMPremissions() << s->GetAccountFlags() << uint32(pi->Guid) << s->m_lang;
		data << uint32(sessionid) << s->GetAccountName() << s->GetGMPremissions() << s->GetAccountFlags() << uint32(pi->Guid) << 0;
		s->GetNextServer()->SendPacket(&data);
	}
}

void WServer::HandlePlayerLoginResult(WorldPacket & pck)
{
	uint32 guid, sessionid;
	uint8 result;
	pck >> guid >> sessionid >> result;
	if(result)
	{
		Log.Success("WServer", "Worldserver %u reports successful login of player %u", m_id, guid);
		Session * s = sClientMgr.GetSession(sessionid);
		if(s)
		{
			s->lastPing = 1;
			s->lastPingTime = (uint32)UNIXTIME;
			/* update server */
			Log.Debug("WServer", "Login session next serv %u", s->GetNextServer());
			s->SetNextServer();

			RPlayerInfo* pi = s->GetPlayer();
			
			//megai2: улучшить обработку логина
			/* pack together a player info packet and distribute it to all the other servers */
			ASSERT(pi);

			if (!pi)
				return;

			//megai2: раньше?
			WorldPacket data(ISMSG_PLAYER_INFO, 100);
			pi->Pack(data);
			sClusterMgr.DistributePacketToAll(&data);

			if (IS_BG_MAP(pi->MapId))
			{
				pi->onBg = true;
				if (pi->m_Group)
				{
					//megai2: конечно должно быть сделано лучше и оптимизированней... %)
					pi->m_Group->RemoveMember(pi->Guid);

					//megai2: походу это уже будет не нужно, т.к. все должно почиститься само )
				/*	uint8 buffer[24];
					memset(buffer, 0, 24);
					s->OutPacket( SMSG_GROUP_LIST, 24, buffer );
	
					data.Initialize( SMSG_GROUP_DESTROYED);
					s->SendPacket( &data );
	
					data.Initialize( SMSG_PARTY_COMMAND_RESULT );
					data << uint32(2) << uint8(0) << uint32(0);  // you leave the group
					s->SendPacket( &data );
	
					pi->m_Group = NULL;
					pi->LootInfo = -1;*/

					sClientMgr.SendPlayerUpdate(pi->Guid);

					for(int32 i = 0; i < 1 + 7 * pi->m_Group->groupType; ++i)
						for(uint32 j = 0; j < 5; ++j)
						{	
							if (pi->m_Group->members[i][j] && sClientMgr.GetRPlayer(pi->m_Group->members[i][j]))
							{
								sClientMgr.GetSession(sClientMgr.GetRPlayer(pi->m_Group->members[i][j])->Sessid)->GroupUpdate();
								break;
							}
						}
					
					pi->m_Group = NULL;
				}
			} else {
				pi->onBg = false;
				s->GroupUpdate();//megai2: апдейт группы для того чтобы не было лагов с отображением
			}
		}
	}
	else
	{
		Log.Error("WServer", "Worldserver %u reports failed login of player %u", m_id, guid);
		Session * s = sClientMgr.GetSession(sessionid);
		if(s)
		{
			s->lastPing = 1;
			s->lastPingTime = (uint32)UNIXTIME;
			WorldPacket data(SMSG_CHARACTER_LOGIN_FAILED, 2);
			data << uint8(CHAR_LOGIN_NO_WORLD);
			s->SendPacket(&data);
			s->ClearCurrentPlayer();
			s->ClearServers();
		}

		sClientMgr.DestroyRPlayerInfo(guid);
	}
}

void WServer::Update()
{
	WorldPacket * pck;
	uint16 opcode;
	if ((uint32)UNIXTIME - lastPing > PING_INTERVAL)
	{
		pck = new WorldPacket(ISMSG_PING, 4);
		*pck << uint32(GetTickCount());
		SendPacket(pck);
		lastPing = (uint32)UNIXTIME;
		delete pck;
	}
	while((pck = m_recvQueue[actQu].Pop()))
	{
		opcode = pck->GetOpcode();
		if(opcode < IMSG_NUM_TYPES && WServer::PHandlers[opcode] != 0)
			(this->*WServer::PHandlers[opcode])(*pck);
		else
			Log.Error("WServer", "Unhandled packet %u\n", opcode);

		//megai2: удалять то тоже нужно о_О
		delete pck;
	}
	actQu = !actQu;

	if ((uint32)UNIXTIME - lastPong > MAX_PONG_TIME)
		m_socket->Disconnect();
}


