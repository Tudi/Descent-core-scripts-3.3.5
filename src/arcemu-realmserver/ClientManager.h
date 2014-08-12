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

#define MAX_SESSIONS 3000

class ClientMgr : public Singleton<ClientMgr>
{
public:
	typedef HM_NAMESPACE::hash_map<uint32, RPlayerInfo*> ClientMap;
	typedef HM_NAMESPACE::hash_map<uint32, Group*> GroupMap;
	typedef HM_NAMESPACE::hash_map<uint32, std::string> NameMap;

protected:
	ClientMap m_clients;
	GroupMap m_groups;
	uint32 m_maxSessionId;
	Session * m_sessions[MAX_SESSIONS];
	FastQueue<Session*, Mutex> m_SessInsertQueue;

public:
	ClientMgr();
	~ClientMgr();
	
	uint32 peakOnline;

	/* create rplayerinfo struct */
	RPlayerInfo * CreateRPlayer(uint32 guid);

	/* destroy rplayerinfo struct */
	void DestroyRPlayerInfo(uint32 guid);

	void SendPlayerUpdate(uint32 guid, WServer * server = NULL);
 
	ARCEMU_INLINE int32 GetPlayersCount()
	{
		return m_clients.size();
	}

	NameMap m_plNames;
	NameMap m_guildNames;

	void LoadPlayerNames();
	void LoadGuildNames();

	ARCEMU_INLINE std::string GetGuildName(uint32 guid)
	{
		NameMap::iterator itr = m_guildNames.find(guid);
		if (itr != m_guildNames.end())
			return itr->second;
		else
			return "guild";//megai2: failsafe
	}
	
	ARCEMU_INLINE std::string GetPlayerName(uint32 guid)
	{
		NameMap::iterator itr = m_plNames.find(guid);
		if (itr != m_plNames.end())
			return itr->second;
		else
			return "name_not_found_xxx";//megai2: нижние подчеркивания + тройная буква, создать такую жесть не смогут вроде  =)
	}

	ARCEMU_INLINE uint32 GetPlayerGuid(std::string name)
	{
		for (NameMap::iterator itr = m_plNames.begin(); itr != m_plNames.end(); ++itr)
		{
			if (itr->second == name)
				return itr->first;
		}
		return 0;
	}

	/* get rplayer */
	ARCEMU_INLINE RPlayerInfo * GetRPlayer(uint32 guid)
	{
		ClientMap::iterator itr = m_clients.find(guid);
		return (itr != m_clients.end()) ? itr->second : 0;
	}
	ARCEMU_INLINE RPlayerInfo * GetRPlayerByName(const char* name)
	{
		ClientMap::iterator itr;
		if (m_clients.empty())
			return NULL;
		for (itr = m_clients.begin(); itr != m_clients.end(); ++itr)
		{
			if(!strcmp(itr->second->Name.c_str(), name))
				return itr->second;
		}
		return NULL;
	}
	/* send "mini" client data to all servers */
	void SendPackedClientInfo(WServer * server);

	/* create a new session, returns null if the player is already logged in */
//	Session * CreateSession(uint32 AccountId);
	ARCEMU_INLINE Session * GetSessionByAcc(uint32 acct)
	{
		for (uint32 i = 1; i <= m_maxSessionId; ++i)
		{
			if (m_sessions[i] && m_sessions[i]->GetAccountId() == acct)
				return m_sessions[i];
		}		
		return NULL;
	}
	ARCEMU_INLINE uint32 GetSessionsCount()
 	{
		return m_maxSessionId;
	}

	/* get session by id */
	ARCEMU_INLINE Session * GetSession(uint32 Id) // get session by id 
	{
		return (Id < MAX_SESSIONS) ? m_sessions[Id] : 0; 
	}
	Session * CreateSession(uint32 AccountId);// create a new session, returns null if the player is already logged in 
	void InsertSession(Session* sess);//megai2: добавляет сессию в массив при апдейте
	void RemoveSession(uint32 id);// removes session 

	uint32 bCharCreate;//megai2: создаеться ли уже чар? =)

	//megai2: Group

	void DeleteGroup(uint32 guid);
	void LoadGroups();
	Group* CreateGroup();
	void SaveGroups();
	Group* GetGroupForGuid(uint32 guid);

	/* updates sessions */
	void Update();
};

#define sClientMgr ClientMgr::getSingleton()


