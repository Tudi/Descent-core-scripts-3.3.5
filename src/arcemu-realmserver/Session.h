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

#ifndef _R_SESSION_H
#define _R_SESSION_H

#define WORLDSOCKET_TIMEOUT		 120
#define CHECK_PACKET_SIZE(pckp, ssize) if(ssize && pckp.size() < ssize) { SafeRemove(); return; }

typedef void(Session::*SessionPacketHandler)(WorldPacket&);

class Session
{
public:
	friend class WorldSocket;
	Session(uint32 id);
	~Session();

protected:
	FastQueue<WorldPacket*, Mutex> m_readQueue[2];
	bool actQu;
	WorldSocket * m_socket;
	WServer * m_server;
	WServer * m_nextServer;
	WServer * m_oldServer;
	uint32 m_sessionId;
	uint32 m_accountId;
	RPlayerInfo * m_currentPlayer;
	uint32 m_muted;
	uint8 _side;
	bool has_55_lvl;
	bool has_dk;
	bool banned;
	bool m_deleted;
	WorldPacket* teleportRq;
	uint32 pendingSID;
	uint32 pendingIID;
	uint32 m_accountFlags;
	string m_GMPermissions;
	string m_accountName;
	uint32 m_build;
	uint32 m_lang;
	static SessionPacketHandler Handlers[NUM_MSG_TYPES];

public:
	uint32 latency;
	uint32 lastPing;
	uint32 lastPingTime;
	void SystemMessage(const char * format, ...);
	static void InitHandlers();
	void Update();
	ARCEMU_INLINE RPlayerInfo * GetPlayer() { return m_currentPlayer; }

	ARCEMU_INLINE void ClearCurrentPlayer() { m_currentPlayer = 0; }
	ARCEMU_INLINE void ClearServers() { m_nextServer = m_server = 0; }
	ARCEMU_INLINE void SetOldServer(WServer * s) { m_oldServer = s; }
	ARCEMU_INLINE void SetNextServerValue(WServer * s) { m_nextServer = s; }
	ARCEMU_INLINE void SetNextServer() { 
			m_oldServer = m_server;
			m_server = m_nextServer; 
			m_nextServer = NULL;
		}
	ARCEMU_INLINE void SetServer(WServer * s) { m_oldServer = m_server; m_server = s; }
	ARCEMU_INLINE WServer * GetOldServer() { return m_oldServer; }
	ARCEMU_INLINE WServer * GetServer() { return m_server; }
	ARCEMU_INLINE WServer * GetNextServer() { return m_nextServer; }
	ARCEMU_INLINE WorldSocket * GetSocket() { return m_socket; }
	ARCEMU_INLINE uint32 GetAccountId() { return m_accountId; }
	string GetGMPremissions() { return m_GMPermissions; }
	string GetAccountName() { return m_accountName; }
	ARCEMU_INLINE uint32 GetAccountFlags() { return m_accountFlags; }
	ARCEMU_INLINE uint32 GetSessionId() { return m_sessionId; }
	ARCEMU_INLINE void SetSessionID(uint32 val) { m_sessionId = val; }
	ARCEMU_INLINE void SetDeleted() { m_deleted = true; }
	ARCEMU_INLINE void SetSocket(WorldSocket *socket) { m_socket = socket; }
	ARCEMU_INLINE bool IsDeleted() { return m_deleted; }
	ARCEMU_INLINE void SetTeleportPending(WorldPacket* pck, uint32 sid, uint32 IID) { 
		teleportRq = pck; 
		if (teleportRq)
			teleportRq->rpos(0);
		pendingSID = sid; 
		pendingIID = IID;
	}
	ARCEMU_INLINE WorldPacket* GetTeleportPendingPck() { return teleportRq; }
	ARCEMU_INLINE uint32 GetTeleportPendingSID() { return pendingSID; }
	ARCEMU_INLINE uint32 GetTeleportPendingIID() { return pendingIID; }
	void GroupUpdate();

	void SafeRemove()
	{
		if(m_socket && m_socket->IsConnected())
		{
			m_socket->Disconnect();
			if (m_sessionId == 0xFFFFFFFF)
				delete this;
		}
		else 
			delete this;
	}

	void SendPacket(WorldPacket * data)
	{
		if(m_socket && m_socket->IsConnected())
			m_socket->SendPacket(data);
	}
	void OutPacket(uint16 opcode, uint16 len, const void* data)
	{
		if(m_socket && m_socket->IsConnected())
			m_socket->OutPacket(opcode, len, data);
	}

	ARCEMU_INLINE bool HasGMPermissions() { return (bool)(m_GMPermissions.length() > 0); } 

	void SendPartyCommandResult(RPlayerInfo* pPlayer, uint32 p1, std::string name, uint32 err);

	void HandlePlayerLogin(WorldPacket & pck);
	void HandleCharacterEnum(WorldPacket & pck);
	void HandleCharacterCreate(WorldPacket & pck);
	void HandleCharacterDelete(WorldPacket & pck);
	void HandleCharacterRename(WorldPacket & pck);
	
	void HandlePing(WorldPacket & pck);
	void HandleItemQuerySingleOpcode(WorldPacket & pck);
	void HandleCreatureQueryOpcode(WorldPacket & pck);
	void HandleGameObjectQueryOpcode(WorldPacket & pck);
	void HandleItemPageQueryOpcode(WorldPacket & pck);
	void HandleNpcTextQueryOpcode(WorldPacket & pck);
	void HandleChatMessage(WorldPacket & recv_data);
	void HandleWhoOpcode(WorldPacket & pck);
	void HandleGroupInviteOpcode(WorldPacket & pck);
	void HandleGroupCancelOpcode(WorldPacket & pck);
	void HandleGroupAcceptOpcode(WorldPacket & pck);
	void HandleGroupDeclineOpcode(WorldPacket & pck);
	void HandleGroupUninviteOpcode(WorldPacket & pck);
	void HandleGroupUninviteGuildOpcode(WorldPacket & pck);
	void HandleGroupSetLeaderOpcode(WorldPacket & pck);
	void HandleGroupDisbandOpcode(WorldPacket & pck);
	void HandleLootMethodOpcode(WorldPacket & pck);
	void HandleMinimapPingOpcode(WorldPacket & pck);
	void HandleConvertGroupToRaidOpcode(WorldPacket & pck);
	void HandleGroupChangeSubGroup(WorldPacket & pck);
	void HandleGroupAssistantLeader(WorldPacket & pck);
	void HandleRequestRaidInfoOpcode(WorldPacket & pck);
	void HandleReadyCheckOpcode(WorldPacket & pck);
	void HandleSetPlayerIconOpcode(WorldPacket & pck);
	void HandlePartyMemberStatsOpcode(WorldPacket & pck);
	void HandleGroupPromote(WorldPacket & pck);
	void HandleDungeonDifficultyOpcode(WorldPacket& pck);
	void HandleBgOps(WorldPacket &recv_data);
};

#endif


