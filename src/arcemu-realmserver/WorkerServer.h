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

#define MAX_SESSIONS_PER_SERVER 1000

enum WType {
	WT_CONTINENT = 0,
	WT_INSTANCE_WORLD = 1,
	WT_BATTLEGROUP_WORLD = 2
};

enum LogoutSrc {
	LS_DISCONNECT = 0,
	LS_LOGOUT = 1
};

struct Instance;
typedef void(WServer::*WServerHandler)(WorldPacket &);
typedef void(WServer::*WServerHandlerW)(WorldPacket &, uint32);

class WServer
{
	static WServerHandler PHandlers[IMSG_NUM_TYPES];
	uint32 m_id;
	WSSocket * m_socket;
	FastQueue<WorldPacket*, Mutex> m_recvQueue[2];
	bool actQu;
	list<Instance*> m_instances;
	bool m_deleted;
	uint32 lastPing;
	uint32 lastPong;

public:
	static WServerHandlerW WHandlers[NUM_MSG_TYPES];
	static void InitHandlers();
	WServer(uint32 id, WSSocket * s);
	~WServer();
	uint32 latency;

	WType type;
	ARCEMU_INLINE size_t GetInstanceCount() { return m_instances.size(); }
	ARCEMU_INLINE void SendPacket(WorldPacket * data) { if(m_socket) m_socket->SendPacket(data); }
	ARCEMU_INLINE void SendWoWPacket(Session * from, WorldPacket * data) { if(m_socket) m_socket->SendWoWPacket(from, data); }
	ARCEMU_INLINE void AddInstance(Instance * pInstance) { m_instances.push_back(pInstance); }
	ARCEMU_INLINE void QueuePacket(WorldPacket * data) {lastPong = (uint32)UNIXTIME; m_recvQueue[!actQu].Push(data); }
	ARCEMU_INLINE uint32 GetID() { return m_id; }
	ARCEMU_INLINE WSSocket * GetSocket() { return m_socket; }
	ARCEMU_INLINE void SetServerID(uint32 val) { m_id = val; }
	ARCEMU_INLINE void SetDeleted() { m_deleted = true; }
	ARCEMU_INLINE bool IsDeleted() { return m_deleted; }
	ARCEMU_INLINE void SetSocket(WSSocket* val) { m_socket = val; }
	void LogoutPlayer(uint32 session, LogoutSrc src);

	void Update();

protected:
	/* packet handlers */
	void HandlePong(WorldPacket & pck);
	void HandleRegisterWorker(WorldPacket & pck);
	void HandleWoWPacket(WorldPacket & pck);
	void HandleWoWPacket(uint32 op, uint32 sessionid, WorldPacket & pck);
	void HandlePlayerLoginResult(WorldPacket & pck);
	void HandleTeleportRequest(WorldPacket & pck);
	void HandlePlayerChangeServerInfo(WorldPacket & pck);
	//void HandlePlayerChangedServers(WorldPacket & pck);
	void HandlePlayerInfoUpdate(WorldPacket & pck);
	void HandleGuidIncrement(WorldPacket & pck);
	void HandlePlayerCreated(WorldPacket & pck);
	void HandleGuildDisband(WorldPacket & pck);
	void HandleMailUpdate(WorldPacket & pck);
	void HandleInstanceCreated(WorldPacket & pck);
	void HandleGuildNameUpdate(WorldPacket & pck);
	void HandlePartyUpdate(WorldPacket & pck);

	//World handlers
	void HandlePlayerLogout(WorldPacket & pck, uint32 session);
	void HandleRollOps(WorldPacket & pck, uint32 session);
};
