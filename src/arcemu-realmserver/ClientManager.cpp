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

initialiseSingleton(ClientMgr);

ClientMgr::ClientMgr()
{
	m_clients.clear();
	m_groups.clear();
	bCharCreate = false;
	peakOnline = 0;
	Session::InitHandlers();
	m_maxSessionId = 0;
	memset(m_sessions, 0, MAX_SESSIONS * sizeof(void*));
	Log.Success("ClientMgr", "Interface Created");
}

ClientMgr::~ClientMgr()
{

};

void ClientMgr::LoadGuildNames()
{
	QueryResult * result = CharacterDatabase.Query("SELECT guildId, guildName FROM guilds");
	if(result)
	{
		do
		{
			Field * fields = result->Fetch();
			m_guildNames.insert(make_pair(fields[0].GetUInt32(), fields[1].GetString()));
		} while(result->NextRow());
		Log.Notice("ClienMgr", "%u guild names loaded.", result->GetRowCount());
		delete result;
	}
}

void ClientMgr::LoadPlayerNames()
{
	QueryResult * result = CharacterDatabase.Query("SELECT guid, name FROM characters");
	if(result)
	{
		do
		{
			Field * fields = result->Fetch();
			m_plNames.insert(make_pair(fields[0].GetUInt32(), fields[1].GetString()));
		} while(result->NextRow());
		Log.Notice("ClienMgr", "%u player names loaded.", result->GetRowCount());
		delete result;
	}
}
void ClientMgr::SendPackedClientInfo(WServer * server)
{
	if(!m_clients.size())
		return;

	WorldPacket data(ISMSG_PACKED_PLAYER_INFO, sizeof(RPlayerInfo) * m_clients.size() + 4);
	data << uint32(m_clients.size());

	/* pack them all togther, w000t! */
	ClientMap::iterator itr = m_clients.begin();
	RPlayerInfo * pi;
	for(; itr != m_clients.end(); ++itr)
	{
		pi = itr->second;
		WorldPacket* data = new WorldPacket(ISMSG_PLAYER_INFO, 300);
		pi->Pack(*data);
		server->SendPacket(data);
	}

    /* TODO: compress the packet */
	server->SendPacket(&data);
}

void ClientMgr::InsertSession(Session* sess)
{
	uint32 i = 0;
	uint32 j = 1;

	/* make sure nothing with this id exists already */
	for(; j < MAX_SESSIONS; ++j)
	{
		if(m_sessions[j] == 0)
		{
			if(!i)
				i = j;
		}
		else
		{
			if(m_sessions[j]->GetAccountId() == sess->GetAccountId() && m_sessions[j]->GetSocket())
			{
				Log.Error("ClientMgr", "Could not create session for account %u due to a session already existing from %s", sess->GetAccountId(), 
					m_sessions[i]->GetSocket()->GetRemoteIP().c_str());

				sess->SafeRemove();
				return;
			}
		}
	}

	if(i == 0)
	{
		sess->SafeRemove();
		return;
	}

	if(m_maxSessionId < i)
	{
		Log.Debug("ClientMgr", "New max session id: %u", i);
		m_maxSessionId = i;
	}

	Log.Debug("ClientMgr", "Allocating session %u for account id %u", i, sess->GetAccountId());
	sess->SetSessionID(i);
	m_sessions[i] = sess;
	sess->lastPing = 1;
	sess->lastPingTime = (uint32)UNIXTIME;
}

Session * ClientMgr::CreateSession(uint32 AccountId)
{
	Session* sess = new Session(0xFFFFFFFF);
	m_SessInsertQueue.Push(sess);
	return sess;
}

void ClientMgr::Update()
{
	Session* insSess;
	while((insSess = m_SessInsertQueue.Pop()))
		InsertSession(insSess);
	if (bCharCreate)
		return;
 	for(uint32 i = 1; i <= m_maxSessionId; ++i)
	{
		if (bCharCreate)
			return;
		if(m_sessions[i])			
			if (m_sessions[i]->IsDeleted())
			{
				Log.Debug("ClientMgr", "Removing session id %u account %u", i, m_sessions[i]->GetAccountId());
				if (m_sessions[i]->GetNextServer())
					continue;
				else if (m_sessions[i]->GetPlayer() && m_sessions[i]->GetServer())//megai2: залогигены на сервере, делаем логаут
				{
					m_sessions[i]->GetServer()->LogoutPlayer(i, LS_DISCONNECT);
					m_sessions[i]->Update();
				}
				else {//megai2: удаляемся
					delete m_sessions[i];
					m_sessions[i] = NULL;
				}
			} else 
				m_sessions[i]->Update();
	}
}

RPlayerInfo * ClientMgr::CreateRPlayer(uint32 guid)
{
	ASSERT(m_clients.find(guid) == m_clients.end());
	RPlayerInfo * rp = new RPlayerInfo;
	rp->Guid = guid;
	m_clients[guid] = rp;
	return rp;
}

void ClientMgr::DestroyRPlayerInfo(uint32 guid)
{
	RPlayerInfo * rp;
	ClientMap::iterator itr = m_clients.find(guid);
	if(itr != m_clients.end())
	{
		rp = itr->second;
		m_clients.erase(itr);
		delete rp;
	}
}
 void ClientMgr::RemoveSession(uint32 id)
 {
 	if (!m_sessions[id]) 
 		return;
	m_sessions[id]->SetDeleted();
 }
 
void ClientMgr::SendPlayerUpdate(uint32 guid, WServer * server)
{
	if (!GetRPlayer(guid))
		return;

	WorldPacket* data = new WorldPacket(ISMSG_PLAYER_INFO, 300);
	GetRPlayer(guid)->Pack(*data);
	sClusterMgr.DistributePacketToAll(data, server);
}
