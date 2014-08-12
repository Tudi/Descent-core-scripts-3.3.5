/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
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

#include "StdAfx.h"

//////////////////////////////////////////////////////////////
/// This function handles CMSG_NAME_QUERY:
//////////////////////////////////////////////////////////////
void WorldSession::HandleNameQueryOpcode( WorldPacket & recv_data )
{
	CHECK_PACKET_SIZE(recv_data, 8);
	uint64 guid;
	recv_data >> guid;

	PlayerInfo *pn = objmgr.GetPlayerInfo( (uint32)guid );
	Player *pp;
	if( _player->GetMapMgr() )
		pp = _player->GetMapMgr()->GetPlayer( guid );
	else
		pp = NULL;
	WoWGuid pguid(guid);

	if(!pn)
		return;

	sLog.outDebug( "Received CMSG_NAME_QUERY for: %s", pn->name );

	sStackWolrdPacket( data, SMSG_NAME_QUERY_RESPONSE, 80 + 35);
	data << pguid;	
	data << uint8(0);			//if not 0 then client will keep asking for new one.Maybe not ready flag ?
	data << pn->name;
	if( pp )
		data << pp->m_name_suffix.c_str();	   // this is a string showed besides players name (eg. in combat log), a custom title ?
	else 
		data << uint8(0);	   // this is a string showed besides players name (eg. in combat log), a custom title ?
	data << (uint8)pn->race << (uint8)pn->gender << (uint8)pn->cl;
	data << uint8(0);			// name is not forbidden
	SendPacket( &data );
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_QUERY_TIME:
//////////////////////////////////////////////////////////////
void WorldSession::HandleQueryTimeOpcode( WorldPacket & recv_data )
{
	OutPacket(SMSG_QUERY_TIME_RESPONSE, 8, &UNIXTIME);
}

void WorldSession::HandleWorldStateUITimerUpdate(WorldPacket& recv_data)
{
	// empty opcode
	sLog.outDebug("WORLD: CMSG_WORLD_STATE_UI_TIMER_UPDATE");

	sStackWolrdPacket( data, SMSG_WORLD_STATE_UI_TIMER_UPDATE, 10 );
	data << uint32(UNIXTIME);
	SendPacket(&data);
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_CREATURE_QUERY:
//////////////////////////////////////////////////////////////
void WorldSession::HandleCreatureQueryOpcode( WorldPacket & recv_data )
{
	CHECK_PACKET_SIZE(recv_data, 12);
	sStackWolrdPacket( data, SMSG_CREATURE_QUERY_RESPONSE, sizeof(CreatureInfo) + 250*4 );
	uint32 entry;
	uint64 guid;
	CreatureInfo *ci;

	recv_data >> entry;
	recv_data >> guid;

	if(entry == 300000)
	{
		data << (uint32)entry;
		data << "WayPoint";
		data << uint8(0) << uint8(0) << uint8(0);
		data << "Level is WayPoint ID";
		for(uint32 i = 0; i < 8;i++)
		{
			data << uint32(0);
		}
		data << uint8(0);  
	}
	else
	{
		ci = CreatureNameStorage.LookupEntry(entry);
		if(ci == NULL)
			return;

		LocalizedCreatureName * lcn = (language>0) ? sLocalizationMgr.GetLocalizedCreatureName(entry, language) : NULL;

		if(lcn == NULL)
		{
			sLog.outDetail("WORLD: CMSG_CREATURE_QUERY '%s'", ci->Name);
			data << (uint32)entry;
			data << ci->Name;
			data << uint8(0) << uint8(0) << uint8(0);
			data << ci->SubName;
		}
		else
		{
			sLog.outDetail("WORLD: CMSG_CREATURE_QUERY '%s' (localized to %s)", ci->Name, lcn->Name);
			data << (uint32)entry;
			data << lcn->Name;
			data << uint8(0) << uint8(0) << uint8(0);
			data << lcn->SubName;
		}
		data << ci->info_str; //!!! this is a string in 2.3.0 Example: stormwind guard has : "Direction"
		data << ci->Flags1;  
		data << ci->Type;
		data << ci->Family;
		data << ci->Rank;
		data << ci->killcredit[0];
		data << ci->killcredit[1];
		data << ci->Male_DisplayID;
		data << ci->Female_DisplayID;
		data << ci->Male_DisplayID2;
		data << ci->Female_DisplayID2;
		data << ci->base_HP_mod;
		data << ci->base_MP_mod;
		data << ci->Leader;
		data << ci->quest_item[0];
		data << ci->quest_item[1];
		data << ci->quest_item[2];
		data << ci->quest_item[3];
		data << ci->quest_item[4];
		data << ci->quest_item[5];
		data << ci->creature_movetype;
#ifdef CATACLYSM_SUPPORT
		data << uint32(0);//unk - all 0 so far
#endif
	}

	SendPacket( &data );
}

//////////////////////////////////////////////////////////////
/// This function handles CMSG_GAMEOBJECT_QUERY:
//////////////////////////////////////////////////////////////
void WorldSession::HandleGameObjectQueryOpcode( WorldPacket & recv_data )
{
	CHECK_PACKET_SIZE(recv_data, 12);
	sStackWolrdPacket( data, SMSG_GAMEOBJECT_QUERY_RESPONSE, sizeof( GameObjectInfo) + 250 * 6 );

	uint32 entryID;
	uint64 guid;
	GameObjectInfo *goinfo;
	

	recv_data >> entryID;
	recv_data >> guid;

	sLog.outDetail("WORLD: CMSG_GAMEOBJECT_QUERY '%u'", entryID);

	goinfo = GameObjectNameStorage.LookupEntry(entryID);
	if(goinfo == NULL)
		return;

	LocalizedGameObjectName * lgn = (language>0) ? sLocalizationMgr.GetLocalizedGameObjectName(entryID, language) : NULL;
    
	data << entryID;
	data << goinfo->Type;
	data << goinfo->DisplayID;
	if(lgn)
		data << lgn->Name;
	else
		data << goinfo->Name;

	data << uint8(0) << uint8(0) << uint8(0);
	data << goinfo->info_str;
	data << goinfo->castbarcaption;
	data << uint8(0);   // new string in 1.12
	data << goinfo->SpellFocus;
	data << goinfo->sound1;
	data << goinfo->sound2;
	data << goinfo->sound3;
	data << goinfo->sound4;
	data << goinfo->sound5;
	data << goinfo->sound6;
	data << goinfo->sound7;
	data << goinfo->sound8;
	data << goinfo->sound9;
	data << goinfo->Unknown1;
	data << goinfo->Unknown2;
	data << goinfo->Unknown3;
	data << goinfo->Unknown4;
	data << goinfo->Unknown5;
	data << goinfo->Unknown6;
	data << goinfo->Unknown7;
	data << goinfo->Unknown8;
	data << goinfo->Unknown9;
	data << goinfo->Unknown10;
	data << goinfo->Unknown11;
	data << goinfo->Unknown12;
	data << goinfo->Unknown13;
	data << goinfo->Unknown14;
	data << goinfo->Scale;
	data << goinfo->RelatedItemId1;
	data << goinfo->RelatedItemId2;
	data << goinfo->RelatedItemId3;
	data << goinfo->RelatedItemId4;
	data << goinfo->RelatedItemId5;
	data << goinfo->RelatedItemId6;
#ifdef CATACLYSM_SUPPORT
		data << uint32(0);//unk - all 0 so far
#endif

	SendPacket( &data );
}

//////////////////////////////////////////////////////////////
/// This function handles MSG_CORPSE_QUERY:
//////////////////////////////////////////////////////////////
void WorldSession::HandleCorpseQueryOpcode(WorldPacket &recv_data)
{
	sLog.outDetail("WORLD: Received MSG_CORPSE_QUERY");

	Corpse *pCorpse;
	sStackWolrdPacket( data, MSG_CORPSE_QUERY, 50 );
	MapInfo *pMapinfo;

	pCorpse = objmgr.GetCorpseByOwner(GetPlayer()->GetLowGUID());
	if(pCorpse)
	{
		pMapinfo = WorldMapInfoStorage.LookupEntry(pCorpse->GetMapId());
		if(pMapinfo)
		{
			if( HAS_GRAVEYARDS_MAP( pMapinfo ) )
			{
				data << uint8(0x01); //show ?
				data << pCorpse->GetMapId(); // mapid (that tombstones shown on)
				data << pCorpse->GetPositionX();
				data << pCorpse->GetPositionY();
				data << pCorpse->GetPositionZ();
				data << pCorpse->GetMapId(); //instance mapid (needs to be same as mapid to be able to recover corpse)
				data << uint32(0); // epenis size
				SendPacket(&data);
			}
			else
			{
				data << uint8(0x01); //show ?
				data << pMapinfo->repopmapid; // mapid (that tombstones shown on)
				data << pMapinfo->repopx;
				data << pMapinfo->repopy;
				data << pMapinfo->repopz;
				data << pCorpse->GetMapId(); //instance mapid (needs to be same as mapid to be able to recover corpse)
				data << uint32(0); // epenis size
				SendPacket(&data);
			}
		}
		else
		{

			data.Initialize(MSG_CORPSE_QUERY);
			data << uint8(0x01); //show ?
			data << pCorpse->GetMapId(); // mapid (that tombstones shown on)
			data << pCorpse->GetPositionX();
			data << pCorpse->GetPositionY();
			data << pCorpse->GetPositionZ();
			data << pCorpse->GetMapId(); //instance mapid (needs to be same as mapid to be able to recover corpse)
			data << uint32(0); // epenis size
			SendPacket(&data);

		}
	}
}

void WorldSession::HandleCorpseQueryMapOpcode(WorldPacket &recv_data)
{
	sLog.outDetail("WORLD: Received CMSG_CORPSE_MAP_POSITION_QUERY");

	uint32 unk;
	recv_data >> unk;
	Corpse *pCorpse;
	sStackWolrdPacket( data, SMSG_CORPSE_MAP_POSITION_QUERY_RESPONSE, 50 );

	pCorpse = objmgr.GetCorpseByOwner(GetPlayer()->GetLowGUID());
	//lucky guess. have not even met this packet to be able to test it ! :S
	if(pCorpse)
	{
		data << pCorpse->GetPositionX();
		data << pCorpse->GetPositionY();
		data << pCorpse->GetPositionZ();
		data << pCorpse->GetOrientation();
		SendPacket(&data);
	}
}

void WorldSession::HandlePageTextQueryOpcode( WorldPacket & recv_data )
{
	CHECK_PACKET_SIZE(recv_data, 4);
	uint32 pageid = 0;
	recv_data >> pageid;

	while(pageid)
	{
		ItemPage * page = ItemPageStorage.LookupEntry(pageid);
		if(!page)
			return;

		LocalizedItemPage * lpi = (language>0) ? sLocalizationMgr.GetLocalizedItemPage(pageid,language):NULL;
		sStackWolrdPacket( data, SMSG_PAGE_TEXT_QUERY_RESPONSE, 1000);
		data << pageid;
		if(lpi)
			data << lpi->Text;
		else
			data << page->text;

		data << page->next_page;
		pageid = page->next_page;
		SendPacket(&data);
	}

}
//////////////////////////////////////////////////////////////
/// This function handles CMSG_ITEM_NAME_QUERY:
//////////////////////////////////////////////////////////////
void WorldSession::HandleItemNameQueryOpcode( WorldPacket & recv_data )
{
   CHECK_PACKET_SIZE(recv_data, 4);
   WorldPacket reply(SMSG_ITEM_NAME_QUERY_RESPONSE, 100);
   uint32 itemid;
   recv_data >> itemid;
   reply << itemid;
   ItemPrototype *proto=ItemPrototypeStorage.LookupEntry(itemid);
   ItemName *MetaName = ItemNameStorage.LookupEntry(itemid);
   if(!proto && !MetaName)
      reply << "Unknown Item";
   else
   {
      if(proto)
      {
         LocalizedItem * li = (language>0) ? sLocalizationMgr.GetLocalizedItem(itemid, language) : NULL;
         if(li)
            reply << li->Name;
         else
            reply << proto->Name1;
      }
      else
         reply << MetaName->name;
   }

   SendPacket(&reply);   

}

void WorldSession::HandleInrangeQuestgiverQuery(WorldPacket & recv_data)
{
	CHECK_INWORLD_RETURN;

	WorldPacket data(SMSG_QUESTGIVER_STATUS_MULTIPLE, 1000);
	Object::InRangeSet::iterator itr;
	Creature * pCreature;
	uint32 count = 0;
	data << count;

	// 32 count
	// <foreach count>
	//    64 guid
	//    8 status

	for( itr = _player->m_objectsInRange.begin(); itr != _player->m_objectsInRange.end(); ++itr )
	{
		if( (*itr)->IsCreature() == false )
			continue;

		pCreature = SafeCreatureCast(*itr);
		if( pCreature->isQuestGiver() )
		{
			data << pCreature->GetGUID();
			data << uint8(sQuestMgr.CalcStatus( pCreature, _player ));
			++count;
		}
	}

	*(uint32*)(data.contents()) = count;
	SendPacket(&data);
}

void WorldSession::HandleAchievmentQueryOpcode( WorldPacket & recv_data )
{
	sLog.outDebug("WORLD: CMSG_QUERY_INSPECT_ACHIEVEMENTS ");

	if( !_player->IsInWorld() || !_player->GetMapMgr() )
		return;

	WoWGuid compressed_guid;
	recv_data >> compressed_guid;

	Player *target_player;
	target_player = _player->GetMapMgr()->GetPlayer( compressed_guid.GetOldGuid() );

	if( target_player == NULL ) 
		return;

	WorldPacket data(SMSG_RESPOND_INSPECT_ACHIEVEMENTS, target_player->m_achievements.size() * 3 * 4 + 4);
	data << compressed_guid;
	//generate block of finished acheivements
	std::map<uint32,AchievementVal*>::iterator itr;
	for(itr=target_player->m_achievements.begin();itr!=target_player->m_achievements.end();itr++)
	{
		uint32 critentry = itr->first;
		AchievementCriteriaEntry *criteria = dbcAchievementCriteriaStore.LookupEntry( critentry );
		if( !criteria ) 
			continue; //wtf ?
		if( criteria->raw.requiredAchievementRelatedCount <= itr->second->cur_value )
		{
			data << uint32( criteria->referredAchievement );
			data << uint32( TimeToGametime( itr->second->completed_at_stamp ) ); // -sometimes it is durations
		}
	}
	//partial progress. Let's not flood trafic with bullshit. This tends to grow large in time
	data << uint32( 0xFFFFFFFF ); //maybe a terminator like a null terminated string ?
	/*
			//sometimes this is duration left
			data << uint32( criteria->ID );
			data << uint8( 1 );
			data << uint8( itr->second->cur_value ); //probably not since it does not fit into this size. Also seems to change from time to time
			data << GetNewGUID();
			data << uint32( 0 ); //no idea. was always 0
			data << uint32( UNIXTIME ); //seems to be something that increases in time. Also seems to a large enough value for time
			data << uint32(0); //duration
			data << uint32(0); //duration left
			*/
	SendPacket(&data);
}

void WorldSession::HandleMirrorImageQueryOpcode( WorldPacket & recv_data )
{
	/*
{SERVER} Packet: (0x0402) SMSG_MIRRORIMAGE_DATA PacketSize = 68 TimeStamp = 9986421
3E 56 04 F0 79 00 30 F1 73 3C 00 00 0A 01 08 05 06 03 05 02 DB 58 85 00 00 00 00 00 8A F2 00 00 00 33 00 00 AA F1 00 00 A5 F1 00 00 7B F2 00 00 9C F2 00 00 83 F1 00 00 72 F2 00 00 DA EF 00 00 98 AD 00 00 

{SERVER} Packet: (0x0402) SMSG_MIRRORIMAGE_DATA PacketSize = 68 TimeStamp = 9986468
3D 56 04 F0 79 00 30 F1 
73 3C 00 00 
0A 01 08 
05 06 03 05 
02 
DB 58 85 00
00 00 00 00 8A F2 00 00 00 33 00 00 AA F1 00 00 A5 F1 00 00 7B F2 00 00 9C F2 00 00 83 F1 00 00 72 F2 00 00 DA EF 00 00 98 AD 00 00 

{SERVER} Packet: (0x0402) SMSG_MIRRORIMAGE_DATA PacketSize = 68 TimeStamp = 9986468
3C 56 04 F0 79 00 30 F1 
73 3C 00 00 15475 - display ID
0A - race
01 - gender
08 - class
05 06 03 05	- PLAYER_BYTES
02 PLAYER_BYTES_2[0] - facialHair
DB 58 85 00 - PLAYER_GUILDID
00 00 00 00 - probably head if helmet is not disabled
8A F2 00 00 62090 - shoulder item display
00 33 00 00 13056 - shirt
AA F1 00 00 61866 - chest
A5 F1 00 00 61861 - Waist
7B F2 00 00 62075 - legs
9C F2 00 00 62108 - feet
83 F1 00 00 61827 - bracer
72 F2 00 00 62066 - hands
DA EF 00 00 61402 - Cloaks
98 AD 00 00 44440 - tabard
*/
	if( _player->GetMapMgr() == NULL )
		return;

	uint64 guid;
	recv_data >> guid;

	Unit *the_image;
	the_image = _player->GetMapMgr()->GetUnit( guid );
	if( the_image == NULL )
		return;

	Player *owner_player;
	owner_player = _player->GetMapMgr()->GetPlayer( the_image->GetUInt32Value( UNIT_FIELD_CREATEDBY ) );
	if( owner_player == NULL )
		return;

	WorldPacket data(SMSG_MIRRORIMAGE_DATA, 80);
	data << guid;
	data << owner_player->GetUInt32Value( UNIT_FIELD_DISPLAYID );

	{
		data << owner_player->getRace();
		data << owner_player->getGender();
		data << owner_player->getClass();
		data << owner_player->GetUInt32Value( PLAYER_BYTES );	//(skin) | (face << 8) | (hairStyle << 16) | (hairColor << 24)
		data << owner_player->GetByte( PLAYER_BYTES_2, 0 );	//facialHair
	}

#ifndef CATACLYSM_SUPPORT
	data << owner_player->GetUInt32Value( PLAYER_GUILDID );
#else
	data << uint32( 0 );
#endif
	if( owner_player->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_NOHELM) == true	)
		data << uint32(0);
	else
		data << owner_player->GetItemInterface()->GetInventoryItemDisplay( EQUIPMENT_SLOT_HEAD );
	data << owner_player->GetItemInterface()->GetInventoryItemDisplay( EQUIPMENT_SLOT_SHOULDERS );
	data << owner_player->GetItemInterface()->GetInventoryItemDisplay( EQUIPMENT_SLOT_BODY );
	data << owner_player->GetItemInterface()->GetInventoryItemDisplay( EQUIPMENT_SLOT_CHEST );
	data << owner_player->GetItemInterface()->GetInventoryItemDisplay( EQUIPMENT_SLOT_WAIST );
	data << owner_player->GetItemInterface()->GetInventoryItemDisplay( EQUIPMENT_SLOT_LEGS );
	data << owner_player->GetItemInterface()->GetInventoryItemDisplay( EQUIPMENT_SLOT_FEET );
	data << owner_player->GetItemInterface()->GetInventoryItemDisplay( EQUIPMENT_SLOT_WRISTS );
	data << owner_player->GetItemInterface()->GetInventoryItemDisplay( EQUIPMENT_SLOT_HANDS );
	data << owner_player->GetItemInterface()->GetInventoryItemDisplay( EQUIPMENT_SLOT_BACK );
	data << owner_player->GetItemInterface()->GetInventoryItemDisplay( EQUIPMENT_SLOT_TABARD );
	SendPacket(&data);
}