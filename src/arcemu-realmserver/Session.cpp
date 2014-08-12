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

SessionPacketHandler Session::Handlers[NUM_MSG_TYPES];
void Session::InitHandlers()
{
	memset(Handlers, 0, sizeof(void*) * NUM_MSG_TYPES);
	Handlers[CMSG_PLAYER_LOGIN] = &Session::HandlePlayerLogin;
	Handlers[CMSG_CHAR_ENUM] = &Session::HandleCharacterEnum;
	Handlers[CMSG_ITEM_QUERY_SINGLE] = &Session::HandleItemQuerySingleOpcode;
	Handlers[CMSG_CHAR_CREATE] = &Session::HandleCharacterCreate;
	Handlers[CMSG_CHAR_DELETE] = &Session::HandleCharacterDelete;
	Handlers[CMSG_WHO]				= &Session::HandleWhoOpcode; 
	Handlers[CMSG_MESSAGECHAT]      = &Session::HandleChatMessage;

	// Groups / Raids
	Handlers[CMSG_GROUP_INVITE]							  = &Session::HandleGroupInviteOpcode;
	Handlers[CMSG_GROUP_CANCEL]							  = &Session::HandleGroupCancelOpcode;
	Handlers[CMSG_GROUP_ACCEPT]							  = &Session::HandleGroupAcceptOpcode;
	Handlers[CMSG_GROUP_DECLINE]							 = &Session::HandleGroupDeclineOpcode;
	Handlers[CMSG_GROUP_UNINVITE]							= &Session::HandleGroupUninviteOpcode;
	Handlers[CMSG_GROUP_UNINVITE_GUID]					   = &Session::HandleGroupUninviteGuildOpcode;
	Handlers[CMSG_GROUP_SET_LEADER]						  = &Session::HandleGroupSetLeaderOpcode;
	Handlers[CMSG_GROUP_DISBAND]							 = &Session::HandleGroupDisbandOpcode;
	Handlers[CMSG_LOOT_METHOD]							   = &Session::HandleLootMethodOpcode;
	Handlers[MSG_MINIMAP_PING]							   = &Session::HandleMinimapPingOpcode;
	Handlers[CMSG_GROUP_RAID_CONVERT]						= &Session::HandleConvertGroupToRaidOpcode;
	Handlers[CMSG_GROUP_CHANGE_SUB_GROUP]					= &Session::HandleGroupChangeSubGroup;
	Handlers[CMSG_GROUP_ASSISTANT_LEADER]					= &Session::HandleGroupAssistantLeader;
	Handlers[CMSG_REQUEST_RAID_INFO]						 = &Session::HandleRequestRaidInfoOpcode;
	Handlers[MSG_RAID_READY_CHECK]						   = &Session::HandleReadyCheckOpcode;
	Handlers[CMSG_REQUEST_PARTY_MEMBER_STATS]				= &Session::HandlePartyMemberStatsOpcode;
	Handlers[MSG_SET_DUNGEON_DIFFICULTY]					 =	&Session::HandleDungeonDifficultyOpcode;
	//megai2: removed? о_О
	//Handlers[MSG_GROUP_SET_PLAYER_ICON]					  = &Session::HandleSetPlayerIconOpcode;
	//Handlers[CMSG_GROUP_PROMOTE]								= &Session::HandleGroupPromote;

	// Battlegrounds
	Handlers[CMSG_BATTLEFIELD_PORT]						= &Session::HandleBgOps;
	Handlers[CMSG_BATTLEFIELD_STATUS]					= &Session::HandleBgOps;
	Handlers[CMSG_BATTLEMASTER_JOIN_ARENA]				= &Session::HandleBgOps;
	Handlers[CMSG_BATTLEMASTER_JOIN]					= &Session::HandleBgOps;

/* 7z - надо перенести
	// Френды покачто в мире 
	WorldPacketHandlers[CMSG_FRIEND_LIST].handler							   = &Session::HandleFriendListOpcode;
	WorldPacketHandlers[CMSG_ADD_FRIEND].handler								= &Session::HandleAddFriendOpcode;
	WorldPacketHandlers[CMSG_DEL_FRIEND].handler								= &Session::HandleDelFriendOpcode;
	WorldPacketHandlers[CMSG_ADD_IGNORE].handler								= &Session::HandleAddIgnoreOpcode;
	WorldPacketHandlers[CMSG_DEL_IGNORE].handler								= &Session::HandleDelIgnoreOpcode;
	WorldPacketHandlers[CMSG_BUG].handler									   = &Session::HandleBugOpcode;
	WorldPacketHandlers[CMSG_SET_FRIEND_NOTE].handler							= &Session::HandleSetFriendNote;

	// LFG System
	WorldPacketHandlers[CMSG_SET_LOOKING_FOR_GROUP_COMMENT].handler				= &Session::HandleSetLookingForGroupComment;
	WorldPacketHandlers[MSG_LOOKING_FOR_GROUP].handler							= &Session::HandleMsgLookingForGroup;
	WorldPacketHandlers[CMSG_SET_LOOKING_FOR_GROUP].handler						= &Session::HandleSetLookingForGroup;
	WorldPacketHandlers[CMSG_SET_LOOKING_FOR_MORE].handler						= &Session::HandleSetLookingForMore;
	WorldPacketHandlers[CMSG_ENABLE_AUTOJOIN].handler							= &Session::HandleEnableAutoJoin;
	WorldPacketHandlers[CMSG_DISABLE_AUTOJOIN].handler							= &Session::HandleDisableAutoJoin;
	WorldPacketHandlers[CMSG_ENABLE_AUTOADD_MEMBERS].handler					= &Session::HandleEnableAutoAddMembers;
	WorldPacketHandlers[CMSG_DISABLE_AUTOADD_MEMBERS].handler					= &Session::HandleDisableAutoAddMembers;
	WorldPacketHandlers[CMSG_CLEAR_LOOKING_FOR_GROUP_STATE].handler				= &Session::HandleLfgClear;

*/
}

Session::Session(uint32 id) : m_sessionId(id)
{
	m_socket = 0;
	m_server = 0;
	m_accountId = 0;
	m_currentPlayer = 0;
	latency = 0;
	m_accountFlags = 0;
	m_build = 0;
	m_nextServer = 0;
	m_oldServer = 0;
	latency = 0;
	m_deleted = false;
	m_muted = 0;
	lastPing = 1;
	lastPingTime = (uint32)UNIXTIME;
	pendingIID = 0;
	pendingSID = 0;
	teleportRq = NULL;
	has_dk = false;
	has_55_lvl = false;
	actQu = false;
}

Session::~Session()
{
	WorldPacket * pck;
	while((pck = m_readQueue[!actQu].Pop()) != 0)
		delete pck;
	while((pck = m_readQueue[actQu].Pop()) != 0)
		delete pck;
}

void Session::Update()
{

	if ((UNIXTIME - lastPingTime > WORLDSOCKET_TIMEOUT && lastPing) && m_socket && m_socket->IsConnected())
 	{
 		m_socket->Disconnect();
 		return;
 	}
	if (GetNextServer() && GetPlayer())
		return;

	WorldPacket * pck;
	uint16 opcode;
	while((pck = m_readQueue[actQu].Pop()))
	{
		opcode = pck->GetOpcode();

		/* can we handle it ourselves? */
		if(Session::Handlers[opcode] != 0)
		{
			(this->*Session::Handlers[opcode])(*pck);
			if (sClientMgr.bCharCreate || GetNextServer())
			{
				delete pck;
				return;
			}
		}
		else
		{
			/* no? pass it back to the worker server for handling. */
			if (GetServer())
				GetServer()->SendWoWPacket(this, pck);
		}
		delete pck;
	}
	actQu = !actQu;
}

void Session::SystemMessage(const char * format, ...)
 {
	char buffer[1024];
	va_list ap;
	va_start(ap,format);
	vsnprintf(buffer,1024,format,ap);
	va_end(ap);

	uint32 messageLength = (uint32)strlen((char*)buffer) + 1;

	WorldPacket * data = new WorldPacket(SMSG_MESSAGECHAT, 30 + messageLength);
	*data << (uint8)CHAT_MSG_SYSTEM;
	*data << (uint32)LANG_UNIVERSAL;
	
	*data << (uint64)0; // Who cares about guid when there's no nickname displayed heh ?
	*data << (uint32)0;
	*data << (uint64)0;

	*data << messageLength;
	*data << buffer;

	*data << uint8(0);

	SendPacket(data);
	delete data;
}
