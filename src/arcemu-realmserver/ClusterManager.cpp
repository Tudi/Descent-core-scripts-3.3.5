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

initialiseSingleton(ClusterMgr);
ClusterMgr::ClusterMgr()
{
	memset(SingleInstanceMaps, 0, sizeof(WServer*) * MAX_SINGLE_MAPID);
	memset(WorkerServers, 0, sizeof(WServer*) * MAX_WORKER_SERVERS);
	m_maxInstanceId = 0;
	m_maxWorkerServer = 0;
	Log.Success("ClusterMgr", "Interface Created");

	WServer::InitHandlers();
}

void ClusterMgr::DeleteWorkerServer(uint32 Idx)
{
	if (WorkerServers[Idx])
		WorkerServers[Idx]->SetDeleted();
}

WServer * ClusterMgr::GetServerByInstanceId(uint32 InstanceId)
{
	InstanceMap::iterator itr = Instances.find(InstanceId);
	return (itr == Instances.end()) ? 0 : itr->second->Server;
}

WServer * ClusterMgr::GetServerByMapId(uint32 MapId)
{
	ASSERT(IS_MAIN_MAP(MapId));
	if (SingleInstanceMaps[MapId])
		return SingleInstanceMaps[MapId]->Server;
	else
		return NULL;
}

Instance * ClusterMgr::GetInstanceByInstanceId(uint32 InstanceId)
{
	InstanceMap::iterator itr = Instances.find(InstanceId);
	return (itr == Instances.end()) ? 0 : itr->second;
}

Instance * ClusterMgr::GetInstanceByMapId(uint32 MapId)
{
	ASSERT(IS_MAIN_MAP(MapId));
	return SingleInstanceMaps[MapId];
}

void ClusterMgr::InsertWorkerServer(WServer * s)
{
	/* find an id */
	uint32 i;
	for(i = 1; i < MAX_WORKER_SERVERS; ++i)
	{
		if(WorkerServers[i] == 0)
			break;
	}

	if(i == MAX_WORKER_SERVERS)
		return;		// No spaces

	if (s->GetSocket() && s->GetSocket()->IsConnected())
		Log.Debug("ClusterMgr", "Allocating worker server %u to %s:%u", i, s->GetSocket()->GetRemoteIP().c_str(), s->GetSocket()->GetRemotePort());

	s->SetServerID(i);
	WorkerServers[i] = s;

	//megai2: грузим гуиды
	WorldPacket data(ISMSG_INITIALIZE_GUIDS, 200);
	data << uint32((GLOBAL_MAX_GUID / sGuidInfo.realmsCnt) * (sGuidInfo.globalOffset-1) + ((GLOBAL_MAX_GUID / sGuidInfo.realmsCnt) / MAX_ACTIVE_WS) * i);//megai2: whoot whoot
	--i;//megai2: поправляем индекс
	data << sGuidInfo.m_hiItemGuid[i] << sGuidInfo.m_hiPlayerGuid[i] << sGuidInfo.m_hiContainerGuid[i] << sGuidInfo.m_hiGuildGuid[i] << sGuidInfo.m_mailGuid[i] << sGuidInfo.m_auctionGuid[i];
	s->SendPacket(&data);
	
	++i;//megai2: ещё раз
	if(m_maxWorkerServer < i)
		m_maxWorkerServer = i;
}

WServer * ClusterMgr::CreateWorkerServer(WSSocket * s)
{
	WServer * tmp = new WServer(0xFFFFFFFF, s);
	m_wsInsertQueue.Push(tmp);
	return tmp;
}

void ClusterMgr::AllocateInitialInstances(WServer * server, vector<WorldInstanceInfo>& preferred)
{
	for(uint32 a = 0; a < preferred.size(); a++)
		Log.Debug("AllocateInitialInstances", "preferred contain instance %u, map %u", preferred[a].InstanceId, preferred[a].MapId);

	vector<WorldInstanceInfo> result;
	result.reserve(10);

	for(vector<WorldInstanceInfo>::iterator itr = preferred.begin(); itr != preferred.end(); ++itr)
	{
		if(IS_MAIN_MAP(itr->MapId) && SingleInstanceMaps[itr->MapId] == 0)
		{
			result.push_back(*itr);
		}
	}

	for(vector<WorldInstanceInfo>::iterator itr = result.begin(); itr != result.end(); ++itr)
	{
		CreateInstance(itr->MapId, server);
	}
}

Instance * ClusterMgr::CreateInstance(uint32 MapId, WServer * server)
{
	//вдруг уже создана.
	if(IS_MAIN_MAP(MapId)) {
		if(GetInstanceByMapId(MapId))
			return GetInstanceByMapId(MapId);
		else
			;
	} else
		return NULL;

	Instance * pInstance = new Instance;
	pInstance->InstanceId = 0;
	pInstance->MapId = MapId;
	pInstance->Server = server;
	pInstance->loading = false;//megai2: сингл мапы всегда уже загружены

	//Instances.insert( make_pair( pInstance->InstanceId, pInstance ) );

	if(IS_MAIN_MAP(MapId))
		SingleInstanceMaps[MapId] = pInstance;

	/* tell the actual server to create the instance */
	WorldPacket data(ISMSG_CREATE_INSTANCE, 8);
	data << MapId << pInstance->InstanceId;
	server->SendPacket(&data);
	server->AddInstance(pInstance);
	Log.Debug("ClusterMgr", "Allocating instance %u on map %u to server %u", pInstance->InstanceId, pInstance->MapId, server->GetID());
	return pInstance;
}

WServer * ClusterMgr::GetWorkerServerForNewInstance()
{
    WServer * lowest = 0;
	uint32 lowest_load = -1;

	/* for now we'll just work with the instance count. in the future we might want to change this to
	   use cpu load instead. */

	for(uint32 i = 0; i < MAX_WORKER_SERVERS; ++i) {
		if(WorkerServers[i] != 0) {
			if((WorkerServers[i]->GetInstanceCount() < lowest_load) && (WorkerServers[i]->type == WT_INSTANCE_WORLD))
			{
				lowest = WorkerServers[i];
				lowest_load = int32(WorkerServers[i]->GetInstanceCount());
			}
		}
	}

	return lowest;
}

/* create new instance based on template, or a saved instance */
Instance * ClusterMgr::CreateInstance(uint32 InstanceId, uint32 MapId, bool heroic)
{
	/* pick a server for us :) */
	WServer * server = GetWorkerServerForNewInstance();
	if(!server) 
		return 0;

	if (InstanceId == 0)
		InstanceId = m_maxInstanceId + 1;

	ASSERT(GetInstance(InstanceId) == NULL);

	/* bump up the max id if necessary */
	if(m_maxInstanceId <= InstanceId)
		m_maxInstanceId = InstanceId + 1;

    Instance * pInstance = new Instance;
	pInstance->InstanceId = InstanceId;
	pInstance->MapId = MapId;
	pInstance->Server = server;
	pInstance->loading = true;

	Instances.insert( make_pair( InstanceId, pInstance ) );

	/* tell the actual server to create the instance */
	WorldPacket data(ISMSG_CREATE_INSTANCE, 8);
	data << MapId << InstanceId << uint8(heroic);
	server->SendPacket(&data);
	server->AddInstance(pInstance);
	Log.Debug("ClusterMgr", "Allocating instance %u on map %u to server %u", pInstance->InstanceId, pInstance->MapId, server->GetID());
	return pInstance;
}

Instance * ClusterMgr::AppendInstance(uint32 InstanceId, uint32 MapId, WServer* ws)
{
    Instance * pInstance = new Instance;
	pInstance->InstanceId = InstanceId;
	pInstance->MapId = MapId;
	pInstance->Server = ws;
	pInstance->loading = false;

	Instances.insert( make_pair( InstanceId, pInstance ) );

	ws->AddInstance(pInstance);
	Log.Debug("ClusterMgr", "Allocating instance %u on map %u to server %u", pInstance->InstanceId, pInstance->MapId, ws->GetID());
	return pInstance;
}

void ClusterMgr::Update()
{
	WServer* insWS;
	while((insWS = m_wsInsertQueue.Pop()))
		InsertWorkerServer(insWS);	
	for(uint32 i = 1; i <= m_maxWorkerServer; ++i)
		if(WorkerServers[i])
			if (WorkerServers[i]->IsDeleted())
			{
				if (sClientMgr.bCharCreate == i)
					sClientMgr.bCharCreate = false;
				//megai2: хз как это делать, надо высвобождать память есчо %)
				for(uint32 j = 0; j <= MAX_SINGLE_MAPID; ++j)
				{
					if ((SingleInstanceMaps[j] != NULL) && (SingleInstanceMaps[j]->Server == WorkerServers[i])) {
						Log.Debug("ClusterMgr", "Removing single instance %u mapid %u", SingleInstanceMaps[j]->InstanceId, SingleInstanceMaps[j]->MapId);
						delete SingleInstanceMaps[j];
						SingleInstanceMaps[j] = NULL;
					}
				}
				for(uint32 j = 1; j <= m_maxInstanceId; ++j)
				{
					if ((Instances[j] != NULL) && (Instances[j]->Server == WorkerServers[i])) {
						Log.Debug("ClusterMgr", "Removing instance %u mapid %u", Instances[j]->InstanceId, Instances[j]->MapId);
						delete Instances[j];
						Instances.erase(j);
					}
				}
				delete WorkerServers[i];
				WorkerServers[i] = NULL;				
			} else 
				WorkerServers[i]->Update();
}

void ClusterMgr::DistributePacketToAll(WorldPacket * data, WServer * exclude)
{
	for(uint32 i = 0; i <= m_maxWorkerServer; ++i)
		if(WorkerServers[i] && WorkerServers[i] != exclude)
			WorkerServers[i]->SendPacket(data);
}

void ClusterMgr::DistributeWOWPacketToAll(Session* from, WorldPacket * data, WServer * exclude)
{
	for(uint32 i = 0; i <= m_maxWorkerServer; ++i)
		if(WorkerServers[i] && WorkerServers[i] != exclude && WorkerServers[i]->GetSocket())
			WorkerServers[i]->GetSocket()->SendWoWPacket(from, data);
}
