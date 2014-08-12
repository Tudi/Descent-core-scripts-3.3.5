#include "RStdAfx.h"

void Session::HandleChatMessage(WorldPacket & recv_data)
{
	CHECK_PACKET_SIZE(recv_data, 9);
	WorldPacket *data;
	if(!GetServer())
		return;
	
	WServer* srcSrv = GetServer();

	uint32 type;
	int32 lang;

	const char * pMisc = 0;
	const char * pMsg = 0;
	recv_data >> type;
	recv_data >> lang;

	if( lang >= NUM_LANGUAGES )
		return;

	std::string msg;
	msg.reserve(256);

	//arghhh STFU. I'm not giving you gold or items NOOB
	switch(type)
	{
	case CHAT_MSG_EMOTE:
	case CHAT_MSG_SAY:
	case CHAT_MSG_YELL:
	case CHAT_MSG_WHISPER:
	case CHAT_MSG_CHANNEL:
		{
			if( m_muted && m_muted >= (uint32)UNIXTIME )
			{
				SystemMessage("Your voice is currently muted by a moderator.");
				return;
			}
		}break;
	}

	switch(type)
	{
	case CHAT_MSG_EMOTE:
	case CHAT_MSG_SAY:
	case CHAT_MSG_YELL:
	case CHAT_MSG_AFK:
	case CHAT_MSG_DND:
	case CHAT_MSG_RAID:
	case CHAT_MSG_RAID_LEADER:
	case CHAT_MSG_RAID_WARNING:
	case CHAT_MSG_CHANNEL:
		{
			std::string channel = "";
			recv_data >> channel >> msg;

			data = new WorldPacket(ISMSG_CHAT, 600);

			*data << type << GetPlayer()->Guid << lang << channel << msg;
			sClusterMgr.DistributePacketToAll(data, srcSrv);

			//megai2: passthrough
			recv_data.rpos(0);
			GetServer()->SendWoWPacket(this, &recv_data);
		}break;
	case CHAT_MSG_PARTY:
		{
			if (!GetPlayer() || !GetPlayer()->m_Group)
				return;

			//megai2: никаких проверок, ибо нафиг не надо
			recv_data >> msg;

			WorldPacket *data = new WorldPacket(SMSG_MESSAGECHAT, msg.length() + 30);
	
			*data << (uint8)CHAT_MSG_PARTY;
			*data << lang;

			*data << uint64(GetPlayer()->Guid);
			*data << uint32(0);

			*data << uint64(GetPlayer()->Guid);
	
			*data << msg.length() + 1;
			*data << msg;

			*data << uint8(GetPlayer()->bGMTag ? 4 : 0);

			for(int32 i = 0; i < 1 + 7 * GetPlayer()->m_Group->groupType; ++i)
				for(uint32 j = 0; j < 5; ++j)
				{
					if (GetPlayer()->m_Group->members[i][j] && sClientMgr.GetRPlayer(GetPlayer()->m_Group->members[i][j])
						&& sClientMgr.GetSession(sClientMgr.GetRPlayer(GetPlayer()->m_Group->members[i][j])->Sessid))
						sClientMgr.GetSession(sClientMgr.GetRPlayer(GetPlayer()->m_Group->members[i][j])->Sessid)->SendPacket(data);
				}
		}
	case CHAT_MSG_OFFICER:
	case CHAT_MSG_GUILD:
		{
			recv_data >> msg;
			
			if ((!GetPlayer()->GuildId) && !(GetPlayer()->hasGMCommand('c')))
			{
				//megai2: not in guild or dont have permissions
				break;
			}
			
			//megai2: посылаем запрос
			data = new WorldPacket(ISMSG_CHAT, 600);
			
			*data  << type << GetSessionId() << GetPlayer()->Guid << msg << lang;
			sClusterMgr.DistributePacketToAll(data, srcSrv);
				
			delete data;
			
			//megai2: passthrough
			recv_data.rpos(0);
			GetServer()->SendWoWPacket(this, &recv_data);		
		}break;		
	case CHAT_MSG_WHISPER:
		{
			std::string to = "",tmp;
			recv_data >> to >> msg;

			if(sConfig.interfaction_chat && lang > 0)
				lang=0;
		 
			RPlayerInfo* player = sClientMgr.GetRPlayerByName(to.c_str());
			WServer* dstServer;
			
			//megai2: без сервера ничего не посылаем
			if(!player || !sClientMgr.GetSession(player->Sessid)->GetServer())
			{
				data = new WorldPacket(SMSG_CHAT_PLAYER_NOT_FOUND, to.length() + 1);
				*data << to;
				SendPacket(data);
				delete data;
				break;
			} else 
				dstServer = sClientMgr.GetSession(player->Sessid)->GetServer();
			
			if (srcSrv != dstServer)
			{			
				//megai2: посылаем запрос
				data = new WorldPacket(ISMSG_CHAT, 600);
			
				*data  << type << player->Sessid << lang << GetPlayer()->Guid << msg;
				dstServer->SendPacket(data);
				
				delete data;
				break;
			} else {
				//megai2: passthrough
				recv_data.rpos(0);
				GetServer()->SendWoWPacket(this, &recv_data);				
			}		
		}break;
	default:
		sLog.outError("CHAT: unknown msg type %u, lang: %u", type, lang);
	}
}
