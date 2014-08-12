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

#define MAX_WORKER_SERVERS 100
#define MAX_SINGLE_MAPID 600

struct Instance
{
	uint32 InstanceId;
	uint32 MapId;
	WServer * Server;
	bool loading;
};

class ClusterMgr : public Singleton<ClusterMgr>
{
	typedef map<uint32, Instance*> InstanceMap;

	WServer * WorkerServers[MAX_WORKER_SERVERS];
	Instance * SingleInstanceMaps[MAX_SINGLE_MAPID];
	
	InstanceMap Instances;
	uint32 m_maxInstanceId;
	uint32 m_maxWorkerServer;

	FastQueue<WServer*, Mutex> m_wsInsertQueue;

public:
	ClusterMgr();

	ARCEMU_INLINE uint32 GetServersCount() { return m_maxWorkerServer; }

	void DeleteWorkerServer(uint32 Idx);

	WServer * GetServerByInstanceId(uint32 InstanceId);
	WServer * GetServerByMapId(uint32 MapId);

	Instance * GetInstanceByInstanceId(uint32 InstanceId);
	Instance * GetInstanceByMapId(uint32 MapId);

	void InsertWorkerServer(WServer * s);
	WServer * CreateWorkerServer(WSSocket * s);
	ARCEMU_INLINE WServer * GetWorkerServer(uint32 Id) { return (Id < MAX_WORKER_SERVERS) ? WorkerServers[Id] : 0; }
	void AllocateInitialInstances(WServer * server, vector<WorldInstanceInfo>& preferred);

	// find the worker server with the least load for the new instance
	WServer * GetWorkerServerForNewInstance();

	/* create new instance, or a main map */
	Instance * CreateInstance(uint32 MapId, WServer* server);

	/* create new instance based on template, or a saved instance */
	Instance * CreateInstance(uint32 InstanceId, uint32 MapId, bool heroic=false);
	Instance * AppendInstance(uint32 InstanceId, uint32 MapId, WServer* ws);

	/* gets the instance struct by instance id */
	Instance * GetInstance(uint32 InstanceId)
	{
		InstanceMap::iterator itr = Instances.find(InstanceId);
		return (itr == Instances.end()) ? 0 : itr->second;
	}

	/* distribute packet to all worker servers */
	ARCEMU_INLINE void DistributePacketToAll(WorldPacket * data) { DistributePacketToAll(data, 0); }
	ARCEMU_INLINE void DistributeWOWPacketToAll(Session* from, WorldPacket * data) { DistributeWOWPacketToAll(from, data, 0); }

	/* distribute packet to all worker server excluding one */
	void DistributePacketToAll(WorldPacket * data, WServer * exclude);
	void DistributeWOWPacketToAll(Session* from, WorldPacket * data, WServer * exclude);

	/* loop */
	void Update();

};


#define sClusterMgr ClusterMgr::getSingleton()


