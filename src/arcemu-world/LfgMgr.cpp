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

initialiseSingleton( LfgMgr );

LfgMgr::LfgMgr()
{
}

LfgMgr::~LfgMgr()
{
}

//check which players are still online and looking for a group
void LfgMgr::RB_RefreshClientLists()
{
}

void LfgMgr::LFGDungeonJoin( Player *plr )
{
	m_lookingForDungeonPlayerGUIDs.insert( plr->GetGUID() );
	if( plr->GetGroup() )
		plr->LFG_PartyUpdateClientUI( LFG_UPDATETYPE_JOIN_PROPOSAL );
	else
	{
		plr->LFG_JoinResponse( LFG_JOIN_OK, 0 );
		plr->LFG_UpdateClientUI( LFG_UPDATETYPE_JOIN_PROPOSAL );
	}
}

void LfgMgr::LFGDungeonLeave( Player *plr )
{
	m_lookingForDungeonPlayerGUIDs.erase( plr->GetGUID() );
	if( plr->GetGroup() )
		plr->LFG_PartyUpdateClientUI( LFG_UPDATETYPE_REMOVED_FROM_QUEUE );
	else
		plr->LFG_UpdateClientUI( LFG_UPDATETYPE_REMOVED_FROM_QUEUE );
	plr->LFG_dungeons.SafeClear();
}

void LfgMgr::RBSendLookingPlayerList( Player *plr )
{
	/*
02 00 00 00 type
E3 00 00 00 map
00 ?
00 00 00 00 counter
00 00 00 00 ?
01 00 00 00 counter
01 00 00 00 ?
for counter
{
	74 27 3D 02 00 00 00 07 - guid
	FF 00 00 00 - flags
	if( flags & ? )
	{
		50 level
		02 class
		01 race ?
		0A
		0A 
		33
		0A 36 00 00 
		00 00 00 00 
		00 00 00 00 
		AC 02 00 00 
		AC 02 00 00 
		AC 02 00 00 
		00 00 98 41 float 19 
		00 00 00 00 float ?
		3A 0B 00 00 
		73 00 00 00 
		6A 53 00 00 
		57 16 00 00 
		00 00 00 00 
		4B 4B 17 43 float 151.29411315918 
		35 00 00 00 
		35 00 00 00 
		00 00 00 00 
		00 00 00 00 
		B0 00 00 00 
		06 00 00 00 - 20th value
		00 comment
		00 ?
		00 00 00 00 00 00 00 00 guid 
		04 role 
		2B 11 00 00 
		00 
		00 00 00 00 00 00 00 00 guid
		00 00 00 00 ?
	}
} 

//other example
02 00 00 00 type
2C 00 00 00 map
00 ?
00 00 00 00 
00 00 00 00 
02 00 00 00 counter ?
02 00 00 00 counter ?
{
	B4 8B BA 02 00 00 00 07 guid
	FF 00 00 00 flags
	50 level
	06 class
	04 race
	33 
	00 
	14 
	D5 36 00 00 ?
	00 00 00 00
	00 00 00 00
	37 02 00 00 
	37 02 00 00 
	37 02 00 00 
	00 00 00 00 float ?
	00 00 00 00 float ?
	2D 0E 00 00
	BB 00 00 00 
	29 5A 00 00 
	00 00 00 00
	00 00 00 00 float ?
	00 00 0E 43 float 142 
	2F 00 00 00 
	4D 00 00 00
	00 00 00 00
	CA 01 00 00
	A0 00 00 00 
	14 00 00 00
	44 4B 20 44 50 53 20 20 67 73 20 34 34 36 32 00 - comment
	00 
	00 00 00 00 00 00 00 00
	09 
	2B 11 00 00 maybe gear score
	00 
	00 00 00 00 00 00 00 00
	00 00 00 00 - end of player 1 data
	A1 B1 82 02 00 00 00 07 
	FF 00 00 00 flags
	50 lvl 80
	03 HUNTER
	03 RACE_DWARF
	00 
	33 
	14 
	EF 24 00 00 ?
	00 00 00 00
	00 00 00 00 
	86 02 00 00
	AE 02 00 00
	86 02 00 00
	00 00 10 42 float 36 
	00 00 00 00 float ?
	89 04 00 00
	5F 03 00 00 
	02 57 00 00
	45 2F 00 00 
	00 00 00 00 
	97 96 08 43 float 136.58824157715
	00 00 00 00 float ?
	3B 00 00 00
	00 00 00 00 
	39 00 00 00
	00 00 00 00
	05 00 00 00
	69 20 77 61 6E 74 20 63 6F 6F 6B 69 65 73 20 21 00 comment
	00 
	00 00 00 00 00 00 00 00 
	09 
	C3 0F 00 00 
	00 
	00 00 00 00 00 00 00 00 
	00 00 00 00 
*/
	sStackWolrdPacket( data, SMSG_UPDATE_LFG_LIST, 2000 );
	data << plr->RB_type;
	data << plr->RB_map_id;
	data << uint8( 0 );	// ?
	data << uint32( 0 );	// ?
	data << uint32( 0 );	// ?
	uint32 counter_pos,counter_val;
	counter_pos = data.GetSize();
	counter_val = 0;
	data << uint32( 0 );	// counter ?
	data << uint32( 0 );	// seems to have same value as counter
	//fill packet with other players that are looking for a group
	std::set<uint64>::iterator itr,itr2;
	for( itr=m_lookingForDungeonPlayerGUIDs.begin(); itr!=m_lookingForDungeonPlayerGUIDs.end();  )
	{
		itr2 = itr;
		itr++;
		Player *tp = objmgr.GetPlayer( *itr2 );
		if( tp == NULL )
		{
			m_lookingForDungeonPlayerGUIDs.erase( itr2 );
			continue;
		}
		//check if this player also looking for the specific raid we are trying to find
		if( tp->RB_IsLookingFor( plr->RB_map_id, plr->RB_type ) == false )
			return;
		data << tp->GetGUID();
		data << uint32( 0x000000FF );	//flags and fags
		data << (uint8)tp->getLevel();
		data << (uint8)tp->getClass();
		data << (uint8)tp->getRace();	//not sure
		data << (uint8)( 0x0A ); //?
		data << (uint8)( 0x0A ); //?
		data << (uint8)( 0x33 ); //? 
		data << (uint32)( 0x0000360A ); //?
		data << (uint32)( 0x00000000 ); //?
		data << (uint32)( 0x00000000 ); //?
		data << (uint32)( 0x000002AC ); //?
		data << (uint32)( 0x000002AC ); //?
		data << (uint32)( 0x000002AC ); //?
		data << (float)( 19.0f ); //?
		data << (uint32)( 0x00000000 ); //?
		data << (uint32)( 0x00000B3A ); //?
		data << (uint32)( 0x00000073 ); //?
		data << (uint32)( 0x0000536A ); //?
		data << (uint32)( 0x00001657 ); //?
		data << (uint32)( 0x00000000 ); //?
		data << (float)( 151.29411315918f ); //?
		data << (uint32)( 0x00000035 ); //?
		data << (uint32)( 0x00000035 ); //?
		data << (uint32)( 0x00000000 ); //?
		data << (uint32)( 0x00000000 ); //?
		data << (uint32)( 0x000000B0 ); //?
		data << (uint32)( 0x00000006 ); //?
		char tbuff[2000];
		sprintf( tbuff,"(%d)%s",tp->LFG_GetGearScore( ),tp->LFG_comment.c_str());
		data << tbuff;
		data << (uint8)( 0x00 ); //?
		data << (uint64)( 0 ); //guid ?
		data << (uint8)( tp->LFG_roles ); 
		data << (uint32)( 0x0000015B ); // seems like this is a part of some mask who killed what boss
		data << (uint8)( 0x00 ); //?
		data << (uint64)( 0 ); //guid ?
		data << (uint32)( 0x00000000 ); //?
		counter_val++;
	}
	data.WriteAtPos( counter_val, counter_pos );
	data.WriteAtPos( counter_val, counter_pos + 4 );	//not sure about this, maybe marks our position in the list ? or show ammount ?
	plr->GetSession()->SendPacket(&data);
}
