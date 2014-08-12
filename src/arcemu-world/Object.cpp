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
#include "Unit.h"
using namespace std;

//#define DEG2RAD (M_PI/180.0)
#ifndef M_PI
	#define M_PI		3.14159265358979323846
#endif
#define M_H_PI		1.57079632679489661923
#define M_Q_PI		0.785398163397448309615

static float DamageToRageConversionTable[PLAYER_LEVEL_CAP+1]=
{
	0.0f,
	3.33333332596f,
	2.32494760373f,
	1.78264780661f,
	1.44396357117f,
	1.2123533165f,
	1.04397785496f,
	0.916056052096f,
	0.815576431602f,
	0.734567160417f,
	0.66787149277f,
	0.612005960162f,
	0.564532608393f,
	0.523694129722f,
	0.488191825581f,
	0.457045164141f,
	0.429499969492f,
	0.404966667879f,
	0.382977704896f,
	0.363157531812f,
	0.345201035638f,
	0.328857765668f,
	0.313920217094f,
	0.300215004319f,
	0.287596125288f,
	0.27593976089f,
	0.265140216201f,
	0.255106721412f,
	0.24576088725f,
	0.23703466382f,
	0.228868690383f,
	0.221210951417f,
	0.214015674635f,
	0.20724242161f,
	0.200855332852f,
	0.194822497576f,
	0.189115424762f,
	0.183708597032f,
	0.178579092584f,
	0.17370626337f,
	0.169071460011f,
	0.164657795691f,
	0.160449942759f,
	0.156433956854f,
	0.152597124314f,
	0.148927829351f,
	0.145415438059f,
	0.142050196824f,
	0.138823143098f,
	0.1357260268f,
	0.132751240913f,
	0.129891760035f,
	0.127141085846f,
	0.124493198595f,
	0.121942513852f,
	0.119483843862f,
	0.117112362949f,
	0.114823576474f,
	0.112613292937f,
	0.110477598847f,
	0.108412836061f,
	0.106415581293f,
	0.104482627572f,
	0.102610967429f,
	0.100797777624f,
	0.0990404052564f,
	0.0973363551185f,
	0.0956832781503f,
	0.094078960901f,
	0.0925213158854f,
	0.0910083727537f,
	0.0921596033f,
	0.0917794521f,
	0.0914051053f,
	0.0911665678f,
	0.0907718719f,
	0.0903840302f,
	0.0900089266f,
	0.089775394f,
	0.0894637303f,
	0.0891139013f,
	0.0887196815f,
	0.0884899819f,
	0.0881336161f,
	0.0878987529f,
	0.0876733074f,
	0.0873275189f,
	0.0870549665f,
	0.0867432723f,
	0.0863807419f,
	0.0861801926f,
	0.0858762193f,
	0.0855271472f,
	0.0851279225f,
	0.0848151907f,
	0.0844208122f,
	0.0842050652f,
	0.0839757867f,
	0.0836747004f,
	0.0832871822f,
	0.0830067135f,
	0.0827602719f,
	0.0824759092f,
	0.0822487669f,
	0.0820367797f,
	0.0816923157f,
	0.0814110048f,
	0.0810540042f,
	0.0806749516f,
	0.0803578558f,
	0.0801471747f,
	0.0798263313f,
	0.0795759163f,
	0.0793178292f,
	0.0790266062f,
	0.0786641857f,
	0.0782693616f,
	0.077908174f,
	0.0776664871f,
	0.077441005f,
	0.0771599748f,
	0.0768398272f,
	0.0765590045f,
	0.0762052266f,
	0.0759274435f,
	0.0755987266f,
	0.0752713463f,
	0.074980288f,
	0.0747264551f,
	0.0744458094f,
	0.0742456996f,
	0.0739646267f,
	0.0735866972f,
	0.0732170135f,
	0.0729992523f,
	0.0727316804f,
	0.0724128573f,
	0.0721232761f,
};

Object::Object() : m_position(0,0,0,0), m_spawnLocation(0,0,0,0)
{
	m_mapId = 0;
	m_zoneId = 0;

	m_uint32Values = 0;
	m_objectUpdated = false;


	m_valuesCount = 0;

	//official Values
	m_walkSpeed = 2.5f;
	m_runSpeed = 9.0f;
	m_base_runSpeed = m_runSpeed;
	m_base_walkSpeed = m_walkSpeed;

	m_flySpeed = 7.0f;
	m_backFlySpeed = 4.5f;

	m_backWalkSpeed = 4.5f;	// this should really be named m_backRunSpeed
	m_swimSpeed = 4.722222f;
	m_backSwimSpeed = 2.5f;
	m_turnRate = 3.141593f;
	m_pitchRate = 3.141593f;
	m_movementFlags = 0;

	m_mapMgr = 0;
	m_mapCell = 0;

	mSemaphoreTeleport = false;


	m_faction = NULL;
	m_factionDBC = NULL;

	m_instanceId = WORLD_INSTANCE;
	Active = false;
	m_inQueue = false;
	m_loadedFromDB = false;
	static_object = false;

	m_faction = dbcFactionTemplate.LookupRow( 0 );
	m_factionDBC = dbcFaction.LookupRow( 0 );

	m_objectsInRange.clear();
	m_inRangePlayers.clear();
//	m_oppFactsInRange.clear();
//	m_sameFactsInRange.clear();
	deleted = OBJ_AVAILABLE;
	m_phase = 0x01;
	next_inrage_update_stamp = 0;
}

Object::~Object( )
{
	Virtual_Destructor();
	deleted = OBJ_DELETED;	//pointless but might help debugging
}

void Object::Virtual_Destructor( )
{
	if(m_objectTypeId != TYPEID_ITEM)
		ASSERT(!m_inQueue);

	if( this->IsInWorld() && IsItem() == false )
		this->RemoveFromWorld(false);

	ClearInRangeSet();
	// for linux
	m_instanceId = WORLD_INSTANCE;
	
	m_extensions.clear();

	//avoid leaving traces in eventmanager. Have to work on the speed. Not all objects ever had events so list iteration can be skipped
	sEventMgr.RemoveEvents( this );

	m_objectTypeId = TYPEID_UNUSED;
	internal_object_type = INTERNAL_OBJECT_TYPE_NONE;
	deleted = OBJ_POOLED_FOR_DELETE;	//pointless but might help debugging
	EventableObject::Virtual_Destructor();	//mark object as unable to store new events
}

ARCEMU_INLINE void Object::Update( uint32 p_time )
{
	{
		//removing objects from ingame parses visibility list to remove himself from other. 
		//If A is getting removed, A does not see B, but B sees A then a corrupted pointer is created. 
		//Example player logs out near invisible player then invisible player casts a spell on him
		if( next_inrage_update_stamp < getMSTime() )
			return;
		next_inrage_update_stamp = getMSTime() + GARBAGE_DELETE_DELAY / 2;
		AquireInrangeLock(); //make sure to release lock before exit function !
		Object::InRangeSet::iterator iter,itr2;
		for (iter = GetInRangeSetBegin(); iter != GetInRangeSetEnd();)
		{
			itr2 = iter;
			iter++;
			if( (*itr2) == NULL || (*itr2)->deleted != OBJ_AVAILABLE )
				m_objectsInRange.erase( itr2 );
		}
		std::set<Player*>::iterator iter3,iter4;
		for (iter3 = GetInRangePlayerSetBegin(); iter3 != GetInRangePlayerSetEnd();)
		{
			iter4 = iter3;
			iter3++;
			if( (*iter4) == NULL || (*iter4)->deleted != OBJ_AVAILABLE )
				m_inRangePlayers.erase( iter4 );
		}
		ReleaseInrangeLock();
	}
}

void Object::_Create( uint32 mapid, float x, float y, float z, float ang )
{
	m_mapId = mapid;
	m_position.ChangeCoords(x, y, z, ang);
	m_spawnLocation.ChangeCoords(x, y, z, ang);
	m_lastMapUpdatePosition.ChangeCoords(x,y,z,ang);
}

uint32 Object::BuildCreateUpdateBlockForPlayer(ByteBuffer *data, Player *target)
{
	uint16 flags = 0;
	uint32 flags2 = 0;
	uint8 temp_objectTypeId = m_objectTypeId; //omg this can be owerwriten by objects that can be destroyed ?

	uint8 updatetype = UPDATETYPE_CREATE_OBJECT;
	//zack : wtf is this ?
	if(m_objectTypeId == TYPEID_CORPSE)
	{
		if(m_uint32Values[CORPSE_FIELD_DISPLAY_ID] == 0)
		{ 
			return 0;
		}
	}

	// any other case
	switch(m_objectTypeId)
	{
		// items + containers: 0x10 -> can be 0x18 too, rarely noticed only 0x10
		// i put 0x18 to make sure we send a unique crap to avoid value collisions. Something is making items randomly not show !
	case TYPEID_ITEM:
	case TYPEID_CONTAINER:
		flags = 0x10;		//note that both 0x8 and 0x10 flags are not know fields to be sent. Might cause issues
		break;
		
		// player/unit: 0x68 (except self)
	case TYPEID_UNIT:
		flags = 0x60;
//		if( SafeUnitCast( this )->GetVehicle() )
//			flags |= 0x80;
		break;

	/*
	02 
	8F 81 7C 39 03 01 04 
	78 00 
	00 00 00 00
	00 00 
	2E 65 63 AF 
	ED CA C8 44 
	BD E1 88 C5 
	FB 70 1F 41 
	8B 47 B6 40
	39 03 
	00 00 
	00 00 20 40 
	00 00 E0 40 
	00 00 90 40 
	72 1C 97 40 
	00 00 20 40 
	00 00 E0 40 
	00 00 90 40
	DB 0F 49 40 
	DB 0F 49 40
	80 E1 2F D2 78 E1 2F D2 2A -> wtf 0x8 | 0x10 */

	//3.3.3 = 0x60 maybe(0x0E,0x78)
	case TYPEID_PLAYER:
		flags = 0x60;
		break;

		// gameobject/dynamicobject
	case TYPEID_GAMEOBJECT:
		flags = 0x0350;
		switch( GetByte(GAMEOBJECT_BYTES_1,GAMEOBJECT_BYTES_TYPEID) )
		{
			case GAMEOBJECT_TYPE_MO_TRANSPORT:  
				{
					if(GetTypeFromGUID() != HIGHGUID_TYPE_TRANSPORTER)
						return 0;   // bad transporter
					else
						flags = 0x0352;	//if we need to link this object to something else then send 352
				}break;

			case GAMEOBJECT_TYPE_TRANSPORT:
				{
					/* deeprun tram, etc */
					flags = 0x252;
				}break;

			case GAMEOBJECT_TYPE_DUEL_ARBITER:
				{
					// duel flags have to stay as updatetype 3, otherwise
					// it won't animate
					updatetype = UPDATETYPE_CREATE_YOURSELF;
				}break;
			case GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING:
				{
					//EoE platform where people can stand on. Also a lot of towers use this. I bet they can be destroyed
					//also building like things use this
					//flags = 0x0F0;
					//temp_objectTypeId = TYPEID_UNIT;
				}break;

		}
		break;

	case TYPEID_DYNAMICOBJECT:
		flags = 0x0050;
		break;

	case TYPEID_CORPSE:
		flags = 0x0150;
		break;
		// anyone else can get fucked and die!
	}

	if(target == this)
	{
		// player creating self
		flags |= 0x01;
		updatetype = UPDATETYPE_CREATE_YOURSELF;
	}

	// build our actual update
	*data << updatetype;

	// we shouldn't be here, under any cercumstances, unless we have a wowguid..
	ASSERT(m_wowGuid.GetNewGuidLen());
	*data << m_wowGuid;
	
	*data << temp_objectTypeId;

	_BuildMovementUpdate(data, flags, flags2, target);

	// we have dirty data, or are creating for ourself.
	UpdateMask updateMask;
	updateMask.SetCount( m_valuesCount );
	_SetCreateBits( &updateMask, target );

	// this will cache automatically if needed
	_BuildValuesUpdate( data, &updateMask, target );

	// update count: 1 ;)
	return 1;
}


//That is dirty fix it actually creates update of 1 field with
//the given value ignoring existing changes in fields and so on
//usefull if we want update this field for certain players
//NOTE: it does not change fields. This is also very fast method
WorldPacket *Object::BuildFieldUpdatePacket( uint32 index,uint32 value)
{
   // uint64 guidfields = GetGUID();
   // uint8 guidmask = 0;
	WorldPacket * packet=new WorldPacket(1500);
	packet->SetOpcode( SMSG_UPDATE_OBJECT );
	
	*packet << (uint32)1;//number of update/create blocks

	*packet << (uint8) UPDATETYPE_VALUES;		// update type == update
	*packet << GetNewGUID();

	uint32 mBlocks = index/32+1;
	*packet << (uint8)mBlocks;
	
	for(uint32 dword_n=mBlocks-1;dword_n;dword_n--)
		*packet <<(uint32)0;

	*packet <<(((uint32)(1))<<(index%32));
	*packet << value;
	
	return packet;
}

void Object::BuildFieldUpdatePacket(Player* Target, uint32 Index, uint32 Value)
{
	ByteBuffer buf(500);
	buf << uint8(UPDATETYPE_VALUES);
	buf << GetNewGUID();

	uint32 mBlocks = Index/32+1;
	buf << (uint8)mBlocks;

	for(uint32 dword_n=mBlocks-1;dword_n;dword_n--)
		buf <<(uint32)0;

	buf <<(((uint32)(1))<<(Index%32));
	buf << Value;

	Target->PushUpdateData(&buf, 1);
}

void Object::BuildFieldUpdatePacket(ByteBuffer * buf, uint32 Index, uint32 Value)
{
	*buf << uint8(UPDATETYPE_VALUES);
	*buf << GetNewGUID();

	uint32 mBlocks = Index/32+1;
	*buf << (uint8)mBlocks;

	for(uint32 dword_n=mBlocks-1;dword_n;dword_n--)
		*buf <<(uint32)0;

	*buf <<(((uint32)(1))<<(Index%32));
	*buf << Value;
}

uint32 Object::BuildValuesUpdateBlockForPlayer(ByteBuffer *data, Player *target)
{
	//might fail if sending to others due to visibility mask = no updates
	if(m_updateMask.GetBlockCount() )
	{
		*data << (uint8) UPDATETYPE_VALUES;		// update type == update
		ASSERT(m_wowGuid.GetNewGuidLen());
		*data << m_wowGuid;
		_BuildValuesUpdate( data, &m_updateMask, target );
		return 1;
	}
	return 0;
}

uint32 Object::BuildValuesUpdateBlockForPlayer(ByteBuffer * buf, UpdateMask * mask )
{
	// returns: update count
	*buf << (uint8) UPDATETYPE_VALUES;		// update type == update

	ASSERT(m_wowGuid.GetNewGuidLen());
	*buf << m_wowGuid;

	_BuildValuesUpdate( buf, mask, 0 );

	// 1 update.
	return 1;
}

void Object::DestroyForPlayer(Player *target, uint8 anim) const
{
	if(target->GetSession() == 0) 
	{ 
		return;
	}

	ASSERT(target);

	sStackWolrdPacket( data, SMSG_DESTROY_OBJECT, 20 );
	data << GetGUID();
	data << uint8(anim);
	target->GetSession()->SendPacket( &data );
}


///////////////////////////////////////////////////////////////
/// Build the Movement Data portion of the update packet
/// Fills the data with this object's movement/speed info
/// TODO: rewrite this stuff, document unknown fields and flags
uint32 TimeStamp();

void Object::_BuildMovementUpdate(ByteBuffer * data, uint16 flags, uint32 flags2, Player* target )
{
	/* ByteBuffer *splinebuf = (m_objectTypeId == TYPEID_UNIT) ? target->GetAndRemoveSplinePacket(GetGUID()) : 0; */
//	uint16 flag16 = 0;	// some other flag
	*data << (uint16)flags;

	Player * pThis = NULL;
	MovementInfo* moveinfo = NULL;
	if(GetTypeId() == TYPEID_PLAYER)
	{
		pThis = SafePlayerCast( this );
		if(pThis->GetSession())
			moveinfo = pThis->GetSession()->GetMovementInfo();
		if(target == this)
		{
			// Updating our last speeds.
			pThis->UpdateLastSpeeds();
		}
	}
	Creature * uThis = NULL;
	if (GetTypeId() == TYPEID_UNIT)
		uThis = SafeCreatureCast(this);

	if( flags & 0x0100 )
	{
//		if( IsGameObject() && SafeGOCast(this)->m_rotation != 0 )
//			*data << this->GetNewGUID();
//		else
			*data << uint8( 0 ); //some say it is like parent guid ?
	}

	if (flags & 0x20)
	{
		if(pThis && pThis->m_TransporterGUID != 0)
			flags2 |= 0x200;
		else if(uThis != NULL && uThis->m_transportGuid != 0 && uThis->m_transportPosition != NULL)
			flags2 |= 0x200;
//		else if( IsUnit() && SafeUnitCast( this )->GetVehicle() )
//			flags2 |= 0x200;

		/* if(splinebuf)
		{
			flags2 |= 0x08000001;	   //1=move forward
			if(uThis != NULL)
			{
				if(uThis->GetAIInterface()->m_moveRun == false)
					flags2 |= 0x100;	//100=walk
			}			
		}
		*/

		if(uThis != NULL)
		{
			//		 Don't know what this is, but I've only seen it applied to spirit healers.
			//		 maybe some sort of invisibility flag? :/

			switch(GetEntry())
			{
			case 6491:  // Spirit Healer
			case 13116: // Alliance Spirit Guide
			case 13117: // Horde Spirit Guide
				{
					flags2 |= 0x10000000;
				}break;
			}
		
			if(uThis->GetAIInterface()->IsFlying())
				flags2 |= 0x400; //Zack : Teribus the Cursed had flag 400 instead of 800 and he is flying all the time 
			if(uThis->GetProto() && uThis->GetProto()->extra_a9_flags)
			{
//do not send shit we can't honor
#define UNKNOWN_FLAGS2 ( 0x0200 | 0x00002000 | 0x00001000 | 0x00200000 | 0x04000000 | 0x08000000 )
				uint32 inherit = uThis->GetProto()->extra_a9_flags & UNKNOWN_FLAGS2;
				flags2 |= inherit;
			}
/*			if(GetGUIDHigh() == HIGHGUID_WAYPOINT)
			{
				if(GetUInt32Value(UNIT_FIELD_STAT0) == 768)		// flying waypoint
					flags2 |= 0x800;
			}*/
		}

		*data << (uint32)flags2;

		*data << (uint16)m_movementFlags;

		*data << getMSTime(); // this appears to be time in ms but can be any thing. Maybe packet serializer ?

		// this stuff:
		//   0x01 -> Enable Swimming?
		//   0x04 -> ??
		//   0x10 -> disables movement compensation and causes players to jump around all the place
		//   0x40 -> disables movement compensation and causes players to jump around all the place
	}

	if( ( flags & 0x0100 ) )
	{
		*data << (float)m_position.x;
		*data << (float)m_position.y;
		*data << (float)m_position.z;
		*data << (float)m_position.x;
		*data << (float)m_position.y;
		*data << (float)m_position.z;
		*data << (float)m_position.o;
		if( IsCorpse() )
			*data << (float)m_position.o; 
		else
			*data << (float)0; 
	}
	else if (flags & 0x40)
	{
		*data << (float)m_position.x;
		*data << (float)m_position.y;
		*data << (float)m_position.z;
		*data << (float)m_position.o;

		if(flags2 & 0x0200)
		{
			Vehicle *pVehicle;
			if(uThis && uThis->GetParentSpawnID())
			{
				// Find Pointer To Parent Vehicle
				ParentInfo * info = uThis->GetParentInfo();
				pVehicle = GetMapMgr()->GetSqlIdVehicle( info->parentspawnid );
				if(pVehicle != NULL)
				{
					*data << pVehicle->GetNewGUID();
					*data << info->offsetX;
					*data << info->offsetY;
					*data << info->offsetZ;
					*data << info->orientation;
					*data << (uint32)(0);
					*data << uint8(info->seatid);
				}
				else
					goto EMPTYTRANSPORTDATA;
			}
			else if( IsUnit() && (pVehicle = SafeUnitCast(this)->GetVehicle()) != NULL ) // we are on a vehicle no matter wich seat we're in
			{
				Unit* pUnit = SafeUnitCast(this);
				VehicleEntry* v = dbcVehicleEntry.LookupEntry(pVehicle->GetVehicleID());
				if (v == NULL)
					goto EMPTYTRANSPORTDATA;
				int8 seat = pUnit->GetSeatID();
				VehicleSeatEntry * seatentry = dbcVehicleSeatEntry.LookupEntry(pVehicle->GetVehicleEntry()->m_seatID[seat]);
				if (seatentry == NULL)
					goto EMPTYTRANSPORTDATA;
				*data << pUnit->GetVehicle()->GetNewGUID();
				*data << seatentry->m_attachmentOffsetX;
				*data << seatentry->m_attachmentOffsetY;
				*data << seatentry->m_attachmentOffsetZ;
				*data << float(0.0f);
				*data << uint32(0);
				*data << uint8(pUnit->GetSeatID());
			}
			else if(pThis)
			{
				WoWGuid wowguid(pThis->m_TransporterGUID);
				*data << wowguid;
				*data << pThis->m_TransporterX << pThis->m_TransporterY << pThis->m_TransporterZ << pThis->m_TransporterO;
				*data << pThis->m_TransporterTime;
				*data << (uint8)0;
			}
			else if(uThis != NULL && uThis->m_transportPosition != NULL)
			{
				uint64 tguid = ((uint64)HIGHGUID_TYPE_TRANSPORTER << 32) | uThis->m_transportGuid;
				WoWGuid wowguid( tguid );
				*data << wowguid;
				*data << uThis->m_transportPosition->x << uThis->m_transportPosition->y << 
					uThis->m_transportPosition->z << uThis->m_transportPosition->o;
				*data << uint32(0);
				*data << uint8(0);
			}
			else
			{
EMPTYTRANSPORTDATA:
				*data << uint8(0);
				*data << LocationVector(0, 0, 0);
				*data << (float)0;
				*data << uint32(0);
				*data << uint8(0);
			}
		}
	}

	if (flags & 0x20)
	{
		if( flags2 & 0x0200000 ) //flying/swimming, && unk sth to do with vehicles?
		{
			if(pThis && moveinfo)
				*data << moveinfo->pitch;
			else 
				*data << (float)0; //pitch
		}

//		if(pThis && moveinfo)
//			*data << moveinfo->unklast;
//		else
			*data << (uint32)0; //last fall time

		if( ( flags2 & 0x00002000 ) || ( flags2 & 0x00001000 ) )
		{
			if(pThis && moveinfo)
			{
				*data << moveinfo->FallTime;
				*data << moveinfo->jump_sinAngle;
				*data << moveinfo->jump_cosAngle;
				*data << moveinfo->jump_xySpeed;
			}
			else
			{
				*data << (float)0;
				*data << (float)1.0;
				*data << (float)0;
				*data << (float)0;
			}
		}
		if( flags2 & 0x02000000 )
			*data << (uint32)0; //?
		if( flags2 & 0x00200000 )
			*data << (uint32)0; //?
		if( flags2 & 0x04000000 )
			*data << (uint32)0; //?

		if( m_walkSpeed == 0 )
			*data << 8.0f;
		else
			*data << m_walkSpeed;	 // walk speed
		if( m_runSpeed == 0 )
			*data << 8.0f;
		else
			*data << m_runSpeed;	  // run speed
		*data << m_backWalkSpeed; // backwards walk speed
		*data << m_swimSpeed;	 // swim speed
		*data << m_backSwimSpeed; // backwards swim speed
		if( m_flySpeed == 0 )
			*data << 8.0f;
		else
			*data << m_flySpeed;		// fly speed
		*data << m_backFlySpeed;	// back fly speed
		*data << m_turnRate;	  // turn rate
		*data << m_pitchRate;
		/*if( flags2 & 0x08000000 )
			if(splinebuf)
			{
				data->append(*splinebuf);
				delete splinebuf;
				splinebuf = NULL;
			}/**/
	}

	if( ( flags & 0x08 ) && ( flags & 0x10 ) )
	{
		//!!! this is defenetly not guid. Seems to be some huge number that increases by every item sent to client
		//note that any object can have 0x18 flags
		/*
		02 - create packet for item
		9F 98 46 DD 43 02 41 01 - item guid
		18 00 - flags
		AC 0F 49 D2 98 46 DD 43 - this 8 byte number, what is it ?

		02 9F B0 89 CD 37 02 41 01 18 00 AC 0F 49 D2 B0 89 CD 37
		02 9F 1F 89 CD 37 02 41 01 18 00 AC 0F 49 D2 1F 89 CD 37
		02 9F 29 25 22 39 02 41 01 18 00 AC 0F 49 D2 29 25 22 39
		02 9F 2D 89 CD 37 02 41 01 18 00 AC 0F 49 D2 2D 89 CD 37
		02 9F 09 CC 1C 3B 02 41 01 18 00 AC 0F 49 D2 09 CC 1C 3B
		02 9F 2E 89 CD 37 02 41 01 18 00 AC 0F 49 D2 2E 89 CD 37
		02 9F 1D 89 CD 37 02 41 01 18 00 AC 0F 49 D2 1D 89 CD 37
		02 9F 20 89 CD 37 02 41 01 18 00 AC 0F 49 D2 20 89 CD 37
		02 9F 1E 89 CD 37 02 41 01 18 00 AC 0F 49 D2 1E 89 CD 37
		02 9F 2A 89 CD 37 02 41 01 18 00 AC 0F 49 D2 2A 89 CD 37
		02 9F 6B 05 79 42 02 41 01 18 00 AC 0F 49 D2 6B 05 79 42
		02 9F 23 89 CD 37 02 41 01 18 00 AC 0F 49 D2 23 89 CD 37
		02 9F 2B 89 CD 37 02 41 01 18 00 AC 0F 49 D2 2B 89 CD 37
		02 9F 72 70 A1 3F 02 41 01 18 00 AC 0F 49 D2 72 70 A1 3F
		02 9F 66 AE F5 39 02 41 01 18 00 AC 0F 49 D2 66 AE F5 39
		02 9F 33 89 CD 37 02 41 01 18 00 AC 0F 49 D2 33 89 CD 37
		02 9F 32 89 CD 37 02 41 02 18 00 AC 0F 49 D2 32 89 CD 37

		02 9F BD 89 CD 37 02 41 01 18 00 B9 18 18 FA BD 89 CD 37
		02 9F 13 89 CD 37 02 41 01 10 00 13 89 CD 37
		02 9F 16 89 CD 37 02 41 01 10 00 16 89 CD 37
		02 8F AB BF 38 03 01 04 78 00 00 00 00 00 00 00 D5 08 64 AF A5 43 F0 44 85 66 91 C5 43 79 E7 41 34 0A 0B 40 BD 02 00 00 00 00 20 40 CD CC 00 41 00 00 90 40 72 1C 97 40 00 00 20 40 00 00 E0 40 00 00 90 40 DB 0F 49 40 DB 0F 49 40 80 E1 2F D2 78 E1 2F D2 2A
		*/

		//AC 0F 49 D2 - seems to be changing slower then the next 4 bytes.
		*data << GetUInt32Value(OBJECT_FIELD_GUID_01);	//defenetly not HIGHguid
//		*data << uint32( 0x0xD2490FAC );	//seems to be a static number / block ?
		*data << GetUInt32Value(OBJECT_FIELD_GUID);			//confirmed to be lowguid only for item !
	}
	else if(flags & 0x10)
	{
        switch(GetTypeId())
        {
            case TYPEID_OBJECT:
            case TYPEID_ITEM:
            case TYPEID_CONTAINER:
            case TYPEID_GAMEOBJECT:
            case TYPEID_DYNAMICOBJECT:
            case TYPEID_CORPSE:
                *data << GetUInt32Value(OBJECT_FIELD_GUID);		//confirmed
                break;
            case TYPEID_UNIT:
                *data << uint32(0x0000000B);                // unk, can be 0xB or 0xC
                break;
            case TYPEID_PLAYER:
                if(flags & 0x1)	//self
                    *data << uint32(0x0000002F);            // unk, can be 0x15 or 0x22
                else
                    *data << uint32(0x00000008);            // unk, can be 0x7 or 0x8
                break;
            default:
                *data << uint32(0x00000000);                // unk
                break;
        }
	}

	if( flags & 0x04 )
		*data << (uint8)0;	//some compressed GUID -> some say it is target guid

	if( flags & 0x80 )
	{
		if( IsUnit() )
			*data << (uint32)(SafeUnitCast(this)->GetCurrentVehicleID()); //vehicle ID
		else
			*data << (uint32)0; 
		*data << (float)0; //facing adjustments or simply facing ?
//		*data << (float)GetOrientation(); //facing adjustments or simply facing ?
	}

	if(flags & 0x2)
	{
		if(target)
		{
			/*int32 m_time = TimeStamp() - target->GetSession()->m_clientTimeDelay;
			*data << m_time;*/
			*data << getMSTime();
		}
		else
            *data << getMSTime();
	}
	if( flags & 0x0200 )
	{
		if( IsGameObject() )
			*data << SafeGOCast( this )->m_rotation;
		else
			*data << (uint64)0; //?
	}
}


//=======================================================================================
//  Creates an update block with the values of this object as
//  determined by the updateMask.
//=======================================================================================
void Object::_BuildValuesUpdate(ByteBuffer * data, UpdateMask *updateMask, Player* target)
{
	bool activate_quest_object = false;
	bool reset = false;
	uint32 oldflags = 0;
	uint32 oldunitflags = 0; //gms should be able to delete even not selectable mobs, or talk to them

	if( updateMask->GetBit(OBJECT_FIELD_GUID) && target )	   // We're creating.
	{
		Creature * pThis = SafeCreatureCast(this);
		if( GetTypeId() == TYPEID_UNIT )
		{
			if( ( m_uint32Values[UNIT_FIELD_FLAGS] & UNIT_FLAG_NOT_SELECTABLE ) && target->GetSession() && target->GetSession()->HasGMPermissions() )
			{
				oldunitflags = m_uint32Values[UNIT_FIELD_FLAGS];
	//			m_uint32Values[UNIT_FIELD_FLAGS] = oldunitflags & ~(UNIT_FLAG_NOT_ATTACKABLE_2|UNIT_FLAG_NOT_ATTACKABLE_9|UNIT_FLAG_NOT_SELECTABLE);
				m_uint32Values[UNIT_FIELD_FLAGS] = oldunitflags & ~(UNIT_FLAG_NOT_SELECTABLE);
			}
			if( pThis->TaggerGuid && (pThis->loot.gold || pThis->loot.items.size()))
			{
				// Let's see if we're the tagger or not.
				oldflags = m_uint32Values[UNIT_DYNAMIC_FLAGS];
				uint32 Flags = m_uint32Values[UNIT_DYNAMIC_FLAGS];
				uint32 oldFlags = 0;

				//if player group killed it or tagger was not in a group when started attacking
				if( pThis->TaggerGroupId == target->GetGroup() || ( pThis->TaggerGroupId == NULL && pThis->TaggerGuid == target->GetGUID() ) )
				{
					// Our target is our tagger.
					oldFlags = U_DYN_FLAG_TAGGED_BY_OTHER;

					if(Flags & U_DYN_FLAG_TAGGED_BY_OTHER)
						Flags &= ~oldFlags;

					if(!(Flags & U_DYN_FLAG_LOOTABLE))
						Flags |= U_DYN_FLAG_LOOTABLE;
				}
				else
				{
					// Target is not the tagger.
					oldFlags = U_DYN_FLAG_LOOTABLE;

					if(!(Flags & U_DYN_FLAG_TAGGED_BY_OTHER))
						Flags |= U_DYN_FLAG_TAGGED_BY_OTHER;

					if(Flags & U_DYN_FLAG_LOOTABLE)
						Flags &= ~oldFlags;
				}

				m_uint32Values[UNIT_DYNAMIC_FLAGS] = Flags;

				updateMask->SetBit(UNIT_DYNAMIC_FLAGS);
				
				reset = true;
			}
		}

		if( IsGameObject() )
		{
			GameObject *go = SafeGOCast(this);
			QuestLogEntry *qle;
			GameObjectInfo *info;

			if ( go )
			{
				if( go->HasQuests() )
				{
					activate_quest_object = true;
				}
				else
				{
					info = go->GetInfo();
					if( info && ( info->goMap.size() || info->itemMap.size() ) )
					{
						for( GameObjectGOMap::iterator itr = go->GetInfo()->goMap.begin(); itr != go->GetInfo()->goMap.end(); ++itr )
						{
							qle = target->GetQuestLogForEntry( itr->first->id );
							if( qle != NULL )
							{
								if( qle->GetQuest()->count_required_mob == 0 )
									continue;
								for( uint32 i = 0; i < 4; ++i )
								{
									if( qle->GetQuest()->required_mob[i] == (int32)go->GetEntry() && (int32)qle->GetMobCount(i) < qle->GetQuest()->required_mobcount[i])
									{
										activate_quest_object = true;
										break;
									}
								}
								if(activate_quest_object)
									break;
							}
						}

						if(!activate_quest_object)
						{
							for(GameObjectItemMap::iterator itr = go->GetInfo()->itemMap.begin();
								itr != go->GetInfo()->itemMap.end();
								++itr)
							{
								for(std::map<uint32, uint32>::iterator it2 = itr->second.begin();
									it2 != itr->second.end(); 
									++it2)
								{
									if((qle = target->GetQuestLogForEntry(itr->first->id)) != 0)
									{
										if(target->GetItemInterface()->GetItemCount(it2->first) < it2->second)
										{
											activate_quest_object = true;
											break;
										}
									}
								}
								if(activate_quest_object)
									break;
							}
						}
					}
				}
			}
		}
	}


	if(activate_quest_object)
	{
		oldflags = m_uint32Values[GAMEOBJECT_DYNAMIC];
		if(!updateMask->GetBit(GAMEOBJECT_DYNAMIC))
			updateMask->SetBit(GAMEOBJECT_DYNAMIC);
		m_uint32Values[GAMEOBJECT_DYNAMIC] = 1 | 8; // 8 to show sparkling
		reset = true;
	}

	WPAssert( updateMask && updateMask->GetCount() == m_valuesCount );
	uint32 bc;
	uint32 values_count;
	uint8 *m = NULL;
	if( updateMask->GetBit(OBJECT_FIELD_GUID) == 0 )//it is an update not a create
	{
		if( 
//			1 == 1 ||
			target == this 
			|| !IsUnit() 
			|| GetUInt32Value( UNIT_FIELD_CHARMEDBY ) == m_uint32Values[ OBJECT_FIELD_GUID ]
			|| GetUInt32Value( UNIT_FIELD_SUMMONEDBY ) == m_uint32Values[ OBJECT_FIELD_GUID ]
			|| GetUInt32Value( UNIT_FIELD_CREATEDBY ) == m_uint32Values[ OBJECT_FIELD_GUID ]
			)	//updating self or stuff that is ours
		{
			bc = updateMask->GetUpdateBlockCount();
			values_count = min<uint32>( bc * 32, m_valuesCount );
		}
		else
		{
			m = (uint8*)sWorld.create_update_for_other_masks[ GetTypeId() ]->GetMask();
			bc = updateMask->GetUpdateBlockCount( (uint32*)m );
			values_count = min<uint32>( bc * 32, m_valuesCount );
		}
	}
	else 
	{
		bc=updateMask->GetBlockCount();
		values_count=m_valuesCount;
	}

	/*
//#define DEBUG_A9_CONTENT 1	//if enabled it should produce same output as parser does. Comparison should be simple
#ifdef DEBUG_A9_CONTENT
	#include "A9_human/human_form.cpp"
	sLog.outDebug("Mask is : ");
	const uint8 *mask = updateMask->GetMask();
	for( unsigned int i=0; i<bc*4; i++ )
		sLog.outDebug("%02X ",mask[i]);
	sLog.outDebug("\n");
#endif
	for( uint32 index = 0; index < values_count; index ++ )
		if( updateMask->GetBit( index ) )
		{
#ifdef DEBUG_A9_CONTENT
			if( player_field_lookup_table[ index ][ 0 ].type == 1 )
				sLog.outDebug(" %s = %u , index = %u\n",player_field_lookup_table[ index ][ 0 ].name, m_uint32Values[ index ], index );		
			else if( player_field_lookup_table[ index ][ 0 ].type == 2 )
				sLog.outDebug(" %s = %f , index = %u\n",player_field_lookup_table[ index ][ 0 ].name, *(float*)&m_uint32Values[ index ], index );		
#endif
			*data << m_uint32Values[ index ];
		}*/

	//we can messup the packet if we do not send any mask and content i think
	if( bc == 0 )
	{
		//just send an empty mask. Shit happens i guess a lot of times( really lot of times ) on live servers
		*data << (uint8)1;	
		*data << (uint32)0;
	}
	else
	{
		*data << (uint8)bc;
		//this is probably create for self or just create for others ( in this case we made a temp update mask already )
		if( m == NULL )
		{
			data->append( updateMask->GetMask(), bc*4 );
			for( uint32 index = 0; index < values_count; index ++ )
				if( updateMask->GetBit( index ) )
					*data << m_uint32Values[ index ];
		}
		//this is update
		else
		{
			//add a mask that filters visibility bits only
			uint32 *m32 = (uint32 *)m;
			for( uint32 index = 0; index < bc; index ++ )
				*data << (updateMask->GetBlock( index ) & m32[ index ]);
			//only add values filtered by visibility bits
			for( uint32 index = 0; index < values_count; index ++ )
				if( updateMask->GetBit( index, m ) )
					*data << m_uint32Values[ index ];
		}
	}

	if( oldunitflags )
		m_uint32Values[UNIT_FIELD_FLAGS] = oldunitflags;
	if(reset)
	{
		switch(GetTypeId())
		{
		case TYPEID_UNIT:
			m_uint32Values[UNIT_DYNAMIC_FLAGS] = oldflags;
			break;
		case TYPEID_GAMEOBJECT:
			m_uint32Values[GAMEOBJECT_DYNAMIC] = oldflags;
			break;
		}
	}

}

void Object::BuildHeartBeatMsg(WorldPacket *data) const
{
	data->Initialize(MSG_MOVE_HEARTBEAT);

	*data << GetNewGUID();

	*data << uint32(0); // flags
	*data << uint16(0); // flags2
	*data << uint32( getMSTime() ); // mysterious value #1

	*data << m_position;
	*data << m_position.o;

	*data << uint32(0); //unk1 - one check showed orientation / 2
	*data << uint32(0); //unk2
}

WorldPacket * Object::BuildTeleportAckMsg(const LocationVector & v)
{
	if( !IsPlayer() )
		return NULL;
	///////////////////////////////////////
	//Update player on the client with TELEPORT_ACK
	SafePlayerCast( this )->SetPlayerStatus( TRANSFER_PENDING );
	SafePlayerCast( this )->m_sentTeleportPosition = v;
/*
{SERVER} Packet: (0x00C7) MSG_MOVE_TELEPORT_ACK PacketSize = 40 TimeStamp = 4491377
8F BB B1 82 02 07 
00 00 00 00 
00 00 00 00
00 00 
F2 50 4B 9D 
58 E9 0C 44 
21 3F B8 42 
A0 9A C5 43
DC 0F C9 3F
00 00 00 00
*/
	WorldPacket * data = new WorldPacket(MSG_MOVE_TELEPORT_ACK, 80);
	*data << GetNewGUID();
	*data << uint32( 0 ); // 
	*data << uint32( 0 ); // flags -> this 0x0C is from a packet when we blinked. Might be something else !
	*data << uint16( 0 );
	*data << uint32( getMSTime() ); // mysterious value #1 -> this can be just 0 ?
	*data << v;
	*data << v.o;
	*data << uint32(0);	//falltime ?
	return data;
}

bool Object::SetPosition(const LocationVector & v, bool allowPorting /* = false */)
{
	bool updateMap = false, result = true;

	if (m_position.x != v.x || m_position.y != v.y)
		updateMap = true;

	m_position = const_cast<LocationVector&>(v);

	if (!allowPorting && v.z < -500)
	{
		m_position.z = 500;
		sLog.outError( "setPosition: fell through map; height ported" );

		result = false;
	}

	if (IsInWorld() && updateMap)
	{
		m_mapMgr->ChangeObjectLocation(this);
	}

	return result;
}

bool Object::SetPosition( float newX, float newY, float newZ, float newOrientation, bool allowPorting )
{
	bool updateMap = false, result = true;

	//It's a good idea to push through EVERY transport position change, no matter how small they are. By: VLack aka. VLsoft
	if( GetTypeId() == TYPEID_GAMEOBJECT && SafeGOCast(this)->GetInfo()->Type == GAMEOBJECT_TYPE_TRANSPORT )
		updateMap = true;

	//if (m_position.x != newX || m_position.y != newY)
		//updateMap = true;
	if(m_lastMapUpdatePosition.Distance2DSq(newX, newY) > (7.0f*7.0f))		/* 2.0f */
		updateMap = true;

	m_position.ChangeCoords(newX, newY, newZ, newOrientation);

	if (!allowPorting && newZ < -500)
	{
		m_position.z = 500;
		sLog.outError( "setPosition: fell through map; height ported" );

		result = false;
	}

	if (IsInWorld() && updateMap)
	{
		m_lastMapUpdatePosition.ChangeCoords(newX,newY,newZ,newOrientation);
		m_mapMgr->ChangeObjectLocation(this);

		if( m_objectTypeId == TYPEID_PLAYER && SafePlayerCast( this )->GetGroup() && SafePlayerCast( this )->m_last_group_position.Distance2DSq(m_position) > 25.0f ) // distance of 5.0
		{
            SafePlayerCast( this )->GetGroup()->HandlePartialChange( GROUP_UPDATE_FLAG_POSITION, SafePlayerCast( this ) );
		}	
	}

	return result;
}

void Object::SetRotation( uint64 guid )
{
	sStackWolrdPacket(data,SMSG_AI_REACTION, 15);
	data << guid;
	data << uint32(2);
	SendMessageToSet(&data, false);
}

void Object::OutPacketToSet(uint16 Opcode, uint16 Len, const void * Data, bool self)
{
	if(self && m_objectTypeId == TYPEID_PLAYER && SafePlayerCast( this )->GetSession() )
		SafePlayerCast( this )->GetSession()->OutPacket(Opcode, Len, Data);

	if(!IsInWorld())
	{ 
		return;
	}

	std::set<Player*>::iterator itr = m_inRangePlayers.begin();
	std::set<Player*>::iterator it_end = m_inRangePlayers.end();
	int gm = ( m_objectTypeId == TYPEID_PLAYER ? SafePlayerCast( this )->m_isGmInvisible : 0 );
	for(; itr != it_end; ++itr)
	{
		ASSERT((*itr)->GetSession());
		if( gm )
		{
			if( (*itr)->GetSession()->GetPermissionCount() > 0 )
				(*itr)->GetSession()->OutPacket(Opcode, Len, Data);
		}
		else
		{
			(*itr)->GetSession()->OutPacket(Opcode, Len, Data);
		}
	}
}

void Object::SendMessageToDuel(StackWorldPacket * data)
{
	if( !GetMapMgr() )
		return;	//packets and no map ?
	//use normal packet sending when we are in BG or instance
	if( GetMapMgr()->GetMapId() != 0 && GetMapMgr()->GetMapId() != 1 && GetMapMgr()->GetMapId() != 530 )
	{
		SendMessageToSet( data, true );
	}
	else
	{
		Player *owner;
		if( IsPlayer() )
			owner = SafePlayerCast( this );
		else if( IsCreature() && GetUInt32Value( UNIT_FIELD_CREATEDBY ) )
			owner = GetMapMgr()->GetPlayer( GetUInt64Value( UNIT_FIELD_CREATEDBY ) );
		else
			owner = NULL;

		if( owner && owner->IsInWorld() && owner->GetSession() )
		{
			owner->GetSession()->OutPacket( data->GetOpcode(), data->GetSize(), data->GetBufferPointer() );
			if( owner->DuelingWith && owner->DuelingWith->IsInWorld() && owner->DuelingWith->GetSession() )
				owner->DuelingWith->GetSession()->OutPacket( data->GetOpcode(), data->GetSize(), data->GetBufferPointer() );
		}
	}
}

void Object::SendMessageToSet(WorldPacket *data, bool bToSelf,bool myteam_only)
{
	if(bToSelf && m_objectTypeId == TYPEID_PLAYER)
	{
		SafePlayerCast( this )->GetSession()->SendPacket(data);		
	}

	if(!IsInWorld())
	{ 
		return;
	}

	std::set<Player*>::iterator itr = m_inRangePlayers.begin();
	std::set<Player*>::iterator it_end = m_inRangePlayers.end();
	bool gminvis = (m_objectTypeId == TYPEID_PLAYER ? SafePlayerCast( this )->m_isGmInvisible : false);
	//Zehamster: Splitting into if/else allows us to avoid testing "gminvis==true" at each loop...
	//		   saving cpu cycles. Chat messages will be sent to everybody even if player is invisible.
	if(myteam_only)
	{
		uint32 myteam=SafePlayerCast( this )->GetTeam();
		if(gminvis && data->GetOpcode()!=SMSG_MESSAGECHAT)
		{
			for(; itr != it_end; ++itr)
			{
				ASSERT((*itr)->GetSession());
				if((*itr)->GetSession()->GetPermissionCount() > 0 && (*itr)->GetTeam()==myteam)
					(*itr)->GetSession()->SendPacket(data);
			}
		}
		else
		{
			for(; itr != it_end; ++itr)
			{
				ASSERT((*itr)->GetSession());
				if((*itr)->GetTeam()==myteam)
					(*itr)->GetSession()->SendPacket(data);
			}
		}
	}
	else
	{
		if(gminvis && data->GetOpcode()!=SMSG_MESSAGECHAT)
		{
			for(; itr != it_end; ++itr)
			{
				ASSERT((*itr)->GetSession());
				if((*itr)->GetSession()->GetPermissionCount() > 0)
					(*itr)->GetSession()->SendPacket(data);
			}
		}
		else
		{
			for(; itr != it_end; ++itr)
			{
				ASSERT((*itr)->GetSession());
				(*itr)->GetSession()->SendPacket(data);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////
/// Fill the object's Update Values from a space deliminated list of values.
void Object::LoadValues(const char* data)
{
	// thread-safe ;) strtok is not.
	std::string ndata = data;
	std::string::size_type last_pos = 0, pos = 0;
	uint32 index = 0;
	uint32 val;
	do 
	{
		// prevent overflow
		if(index >= m_valuesCount)
		{
			break;
		}
		pos = ndata.find(" ", last_pos);
		val = atol(ndata.substr(last_pos, (pos-last_pos)).c_str());
		if(m_uint32Values[index] == 0)
			m_uint32Values[index] = val;
		last_pos = pos+1;
		++index;
	} while(pos != std::string::npos);
}

void Object::_SetUpdateBits(UpdateMask *updateMask, Player *target) const
{
	*updateMask = m_updateMask;
}


void Object::_SetCreateBits(UpdateMask *updateMask, Player *target) const
{
	/*for( uint16 index = 0; index < m_valuesCount; index++ )
	{
		if(GetUInt32Value(index) != 0)
			updateMask->SetBit(index);
	}*/
	for(uint32 i = 0; i < m_valuesCount; ++i)
		if(m_uint32Values[i] != 0)
			updateMask->SetBit(i);
}

void Object::AddToWorld()
{
	MapMgr *mapMgr = sInstanceMgr.GetInstance(this);
	if(!mapMgr)
	{ 
		return;
	}

	if(this->IsPlayer())
	{
		Player *plr = SafePlayerCast( this );

		//this should not happen, before adding to some world we should removed from other
		//however due to teleport event on teleport exist it is possible that this gets bugged
		if( IsInWorld() )
			RemoveFromWorld( false );

		if(mapMgr->pInstance != NULL && !plr->bGMTagOn)
		{
			// Player limit?
			if(mapMgr->GetMapInfo()->playerlimit && mapMgr->GetPlayerCount() >= mapMgr->GetMapInfo()->playerlimit)
			{ 
				return;
			}
			Group* group = plr->GetGroup();
			// Player in group?
			if(group == NULL && mapMgr->pInstance->m_creatorGuid == 0)
			{ 
				return;
			}
			// If set: Owns player the instance?
			if(mapMgr->pInstance->m_creatorGuid != 0 && mapMgr->pInstance->m_creatorGuid != plr->GetLowGUID())
			{ 
				return;
			}
			// Is instance empty or owns our group the instance?
			if(mapMgr->pInstance->m_creatorGroup != 0 && group != NULL && mapMgr->pInstance->m_creatorGroup != group->GetID())
			{
				// Player not in group or another group is already playing this instance.
				sChatHandler.SystemMessageToPlr(plr, "Another group is already inside this instance of the dungeon.");
				if(plr->GetSession()->GetPermissionCount() > 0)
					sChatHandler.BlueSystemMessageToPlr(plr, "Enable your GameMaster flag to ignore this rule.");
				return; 
			}
			else if(group != NULL && mapMgr->pInstance->m_creatorGroup == 0)
				// Players group now "owns" the instance.
				mapMgr->pInstance->m_creatorGroup = group->GetID(); 
		}
	}

	m_mapMgr = mapMgr;
	m_inQueue = true;

	mapMgr->AddObject(this);

	// correct incorrect instance id's
	m_instanceId = m_mapMgr->GetInstanceID();
//	m_mapId = m_mapMgr->GetMapId();
	event_Relocate(); //changed map ? then we need to port events to this map

	mSemaphoreTeleport = false;
}

void Object::AddToWorld(MapMgr * pMapMgr)
{
	if( !pMapMgr|| (pMapMgr->GetMapInfo()->playerlimit && this->IsPlayer() && pMapMgr->GetPlayerCount() >= pMapMgr->GetMapInfo()->playerlimit) )
		return; //instance add failed

	//this should not happen, before adding to some world we should removed from other
	//however due to teleport event on teleport exist it is possible that this gets bugged
	if( IsInWorld() )
		RemoveFromWorld( false );

	m_mapMgr = pMapMgr;
	m_inQueue = true;

	pMapMgr->AddObject(this);

	// correct incorrect instance id's
	m_instanceId = pMapMgr->GetInstanceID();
//	m_mapId = m_mapMgr->GetMapId();
	event_Relocate();

	mSemaphoreTeleport = false;
}

//Unlike addtoworld it pushes it directly ignoring add pool
//this can only be called from the thread of mapmgr!!!
void Object::PushToWorld(MapMgr*mgr)
{
	if(!mgr || deleted/* || (m_mapMgr != NULL && m_mapCell != NULL) */)
		return; //instance add failed

	m_mapId=mgr->GetMapId();
	m_instanceId = mgr->GetInstanceID();

	m_mapMgr = mgr;
	OnPrePushToWorld();

	mgr->PushObject(this);

	// correct incorrect instance id's
	mSemaphoreTeleport = false;
	m_inQueue = false;
   
	event_Relocate();
	
	// call virtual function to handle stuff.. :P
	OnPushToWorld();
}

void Object::RemoveFromWorld(bool free_guid)
{
//	ASSERT(m_mapMgr);
	MapMgr * m = m_mapMgr;
	m_mapMgr = NULL;

	mSemaphoreTeleport = true;

	if( m ) 
		m->RemoveObject(this, free_guid);
	
	// update our event holder
	event_Relocate();

//	m_instanceId = 0;
//	m_mapId = 0;
	//m_inQueue is set to true when AddToWorld() is called. AddToWorld() queues the Object to be pushed, but if it's not pushed and RemoveFromWorld()
	//is called, m_inQueue will still be true even if the Object is no more inworld, nor queued.
	m_inQueue = false;
}

//! Set uint32 property
void Object::SetUInt32Value( const uint32 index, const uint32 value )
{
	ASSERT( index < m_valuesCount );
	// save updating when val isn't changing.
	if(m_uint32Values[index] == value)
	{ 
		return;
	}

	m_uint32Values[ index ] = value;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}

	// Group update handling
	if(m_objectTypeId == TYPEID_PLAYER)
	{
		if(IsInWorld())
		{
			Group* pGroup = SafePlayerCast( this )->GetGroup();
			if( pGroup != NULL )
				pGroup->HandleUpdateFieldChange( index, SafePlayerCast( this ) );
		}
	}
}
/*
//must be in %
void Object::ModPUInt32Value(const uint32 index, const int32 value, bool apply )
{
	ASSERT( index < m_valuesCount );
	int32 basevalue = (int32)m_uint32Values[ index ];
	if(apply)
		m_uint32Values[ index ] += ((basevalue*value)/100);
	else
		m_uint32Values[ index ] = (basevalue*100)/(100+value);

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated )
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}
}
*/
uint32 Object::GetModPUInt32Value(const uint32 index, const int32 value)
{
	ASSERT( index < m_valuesCount );
	int32 basevalue = (int32)m_uint32Values[ index ];
	return ((basevalue*value)/100);
}

void Object::ModUnsigned32Value(uint32 index, int32 mod)
{
	ASSERT( index < m_valuesCount );
	if(mod == 0)
	{ 
		return;
	}

	m_uint32Values[ index ] += mod;
	if( (int32)m_uint32Values[index] < 0 )
		m_uint32Values[index] = 0;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}
}

void Object::ModSignedInt32Value(uint32 index, int32 value )
{
	ASSERT( index < m_valuesCount );
	if(value == 0)
	{ 
		return;
	}

	m_uint32Values[ index ] += value;
	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}
}

void Object::ModFloatValue(const uint32 index, const float value )
{
	ASSERT( index < m_valuesCount );
	m_floatValues[ index ] += value;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}
}
void Object::ModFloatValueByPCT( const uint32 index, int32 byPct )
{
	ASSERT( index < m_valuesCount );
	if( byPct > 0 )
		m_floatValues[ index ] *= 1.0f + float( byPct ) / 100.0f;
	else
		m_floatValues[ index ] /= 1.0f + float( -byPct ) / 100.0f;


	if( IsInWorld() )
	{
		m_updateMask.SetBit( index );

		if( !m_objectUpdated )
		{
			m_mapMgr->ObjectUpdated( this );
			m_objectUpdated = true;
		}
	}
}

//! Set uint64 property
void Object::SetUInt64Value( const uint32 index, const uint64 value )
{
	assert( index + 1 < m_valuesCount );
#ifndef USING_BIG_ENDIAN
	if(m_uint32Values[index] == GUID_LOPART(value) && m_uint32Values[index+1] == GUID_HIPART(value))
	{ 
		return;
	}

	m_uint32Values[ index ] = *((uint32*)&value);
	m_uint32Values[ index + 1 ] = *(((uint32*)&value) + 1);
#else
	m_uint32Values[index] = value & 0xffffffff;
	m_uint32Values[index+1] = (value >> 32) & 0xffffffff;
#endif

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );
		m_updateMask.SetBit( index + 1 );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}
}

//! Set float property
void Object::SetFloatValue( const uint32 index, const float value )
{
	ASSERT( index < m_valuesCount );
	if(m_floatValues[index] == value)
	{ 
		return;
	}

	m_floatValues[ index ] = value;
	
	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}
}


void Object::SetFlag( const uint32 index, uint32 newFlag )
{
	ASSERT( index < m_valuesCount );

	//no change -> no update
	if((m_uint32Values[ index ] & newFlag)==newFlag)
	{ 
		return;
	}

	m_uint32Values[ index ] |= newFlag;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}
}


void Object::RemoveFlag( const uint32 index, uint32 oldFlag )
{
	ASSERT( index < m_valuesCount );

	//no change -> no update
	if((m_uint32Values[ index ] & oldFlag)==0)
	{ 
		return;
	}

	m_uint32Values[ index ] &= ~oldFlag;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}
}

void Object::SetByteFlag(const uint32 index, const uint32 flag, uint8 newFlag)
{
   if( HasByteFlag(index,flag,newFlag))
   { 
      return;
   }

   SetByte(index, flag, GetByte(index,flag)|newFlag);

   if(IsInWorld())
   {
      m_updateMask.SetBit( index );

      if(!m_objectUpdated)
      {
         m_mapMgr->ObjectUpdated( this );
         m_objectUpdated = true;
      }
   }
}

void Object::RemoveByteFlag(const uint32 index, const uint32 flag, uint8 checkFlag)
{
   if( !HasByteFlag(index,flag,checkFlag))
   { 
      return;
   }

   SetByte(index,flag, GetByte(index,flag) & ~checkFlag );

   if(IsInWorld())
   {
      m_updateMask.SetBit( index );

      if(!m_objectUpdated)
      {
         m_mapMgr->ObjectUpdated( this );
         m_objectUpdated = true;
      }
   }
}

bool Object::HasByteFlag(const uint32 index, const uint32 flag, uint8 checkFlag)
{
   if( GetByte(index,flag) & checkFlag )
   { 
      return true;
   }
   else
      return false;
}
////////////////////////////////////////////////////////////

float Object::CalcDistance(Object *Ob)
{
	ASSERT(Ob != NULL);
	return CalcDistance(this->GetPositionX(), this->GetPositionY(), this->GetPositionZ(), Ob->GetPositionX(), Ob->GetPositionY(), Ob->GetPositionZ());
}
float Object::CalcDistance(float ObX, float ObY, float ObZ)
{
	return CalcDistance(this->GetPositionX(), this->GetPositionY(), this->GetPositionZ(), ObX, ObY, ObZ);
}
float Object::CalcDistance(Object *Oa, Object *Ob)
{
	ASSERT(Oa != NULL);
	ASSERT(Ob != NULL);
	return CalcDistance(Oa->GetPositionX(), Oa->GetPositionY(), Oa->GetPositionZ(), Ob->GetPositionX(), Ob->GetPositionY(), Ob->GetPositionZ());
}
float Object::CalcDistance(Object *Oa, float ObX, float ObY, float ObZ)
{
	ASSERT(Oa != NULL);
	return CalcDistance(Oa->GetPositionX(), Oa->GetPositionY(), Oa->GetPositionZ(), ObX, ObY, ObZ);
}

float Object::CalcDistance(float OaX, float OaY, float OaZ, float ObX, float ObY, float ObZ)
{
	float xdest = OaX - ObX;
	float ydest = OaY - ObY;
	float zdest = OaZ - ObZ;
	return sqrtf(zdest*zdest + ydest*ydest + xdest*xdest);
}

bool Object::IsWithinDistInMap(Object* obj, const float dist2compare) const
{
	ASSERT(obj != NULL);
	float xdest = this->GetPositionX() - obj->GetPositionX();
	float ydest = this->GetPositionY() - obj->GetPositionY();
	float zdest = this->GetPositionZ() - obj->GetPositionZ();
	return sqrtf(zdest*zdest + ydest*ydest + xdest*xdest) <= dist2compare;
}

bool Object::IsWithinLOSInMap(Object* obj)
{
	ASSERT(obj != NULL);
    if (!IsInMap(obj)) 
    { 
    	return false;
    }
	LocationVector location;
    location = obj->GetPosition();
    return IsWithinLOS(location );
}

bool Object::IsWithinLOS( LocationVector location )
{
    LocationVector location2;
    location2 = GetPosition();

	if (sWorld.Collision) {
	{ 
		return CollideInterface.CheckLOS(GetMapId(), location2.x, location2.y, location2.z+2.0f, location.x, location.y, location.z+2.0f);
	}
	} else {
		return true;
	}
}


float Object::calcAngle( float Position1X, float Position1Y, float Position2X, float Position2Y )
{
	float dx = Position2X-Position1X;
	float dy = Position2Y-Position1Y;
	double angle=0.0f;

	// Calculate angle
	if (dx == 0.0)
	{
		if (dy == 0.0)
			angle = 0.0;
		else if (dy > 0.0)
			angle = M_PI * 0.5 /* / 2 */;
		else
			angle = M_PI * 3.0 * 0.5/* / 2 */;
	}
	else if (dy == 0.0)
	{
		if (dx > 0.0)
			angle = 0.0;
		else
			angle = M_PI;
	}
	else
	{
		if (dx < 0.0)
			angle = atanf(dy/dx) + M_PI;
		else if (dy < 0.0)
			angle = atanf(dy/dx) + (2*M_PI);
		else
			angle = atanf(dy/dx);
	}

	// Convert to degrees
	angle = angle * float(180 / M_PI);

	// Return
	return float(angle);
}

float Object::calcRadAngle( float Position1X, float Position1Y, float Position2X, float Position2Y )
{
	double dx = double(Position2X-Position1X);
	double dy = double(Position2Y-Position1Y);
	double angle=0.0;

	// Calculate angle
	if (dx == 0.0)
	{
		if (dy == 0.0)
			angle = 0.0;
		else if (dy > 0.0)
			angle = M_PI * 0.5/*/ 2.0*/;
		else
			angle = M_PI * 3.0 * 0.5/*/ 2.0*/;
	}
	else if (dy == 0.0)
	{
		if (dx > 0.0)
			angle = 0.0;
		else
			angle = M_PI;
	}
	else
	{
		if (dx < 0.0)
			angle = atan(dy/dx) + M_PI;
		else if (dy < 0.0)
			angle = atan(dy/dx) + (2*M_PI);
		else
			angle = atan(dy/dx);
	}

	// Return
	return float(angle);
}

float Object::getEasyAngle( float angle )
{
	while ( angle < 0 ) {
		angle = angle + 360;
	}
	while ( angle >= 360 ) {
		angle = angle - 360;
	}
	return angle;
}

bool Object::inArc(float Position1X, float Position1Y, float FOV, float Orientation, float Position2X, float Position2Y )
{
	float angle = calcAngle( Position1X, Position1Y, Position2X, Position2Y );
	float lborder = getEasyAngle( ( Orientation - (FOV*0.5f/*/2*/) ) );
	float rborder = getEasyAngle( ( Orientation + (FOV*0.5f/*/2*/) ) );
	//sLog.outDebug("Orientation: %f Angle: %f LeftBorder: %f RightBorder %f",Orientation,angle,lborder,rborder);
	if(((angle >= lborder) && (angle <= rborder)) || ((lborder > rborder) && ((angle < rborder) || (angle > lborder))))
	{
		return true;
	}
	else
	{
		return false;
	}
} 

bool Object::isInFront(Object* target)
{
	// check if we facing something ( is the object within a 180 degree slice of our positive y axis )

    double x = target->GetPositionX() - m_position.x;
    double y = target->GetPositionY() - m_position.y;

    double angle = atan2( y, x );
    angle = ( angle >= 0.0 ) ? angle : 2.0 * M_PI + angle;
	angle -= m_position.o;

    while( angle > M_PI)
        angle -= 2.0 * M_PI;

    while(angle < -M_PI)
        angle += 2.0 * M_PI;

	// replace M_PI in the two lines below to reduce or increase angle

    double left = -1.0 * ( M_PI / 2.0 );
    double right = ( M_PI / 2.0 );

    return( ( angle >= left ) && ( angle <= right ) );
}

bool Object::isInBack(Object* target)
{
	// check if we are behind something ( is the object within a 180 degree slice of our negative y axis )

    double x = m_position.x - target->GetPositionX();
    double y = m_position.y - target->GetPositionY();

    double angle = atan2( y, x );
    angle = ( angle >= 0.0 ) ? angle : 2.0 * M_PI + angle;

	// if we are a unit and have a UNIT_FIELD_TARGET then we are always facing them
	if( m_objectTypeId == TYPEID_UNIT && m_uint32Values[UNIT_FIELD_TARGET] != 0 && SafeUnitCast( this )->GetAIInterface()->GetNextTarget() )
	{
		Unit* pTarget = SafeUnitCast( this )->GetAIInterface()->GetNextTarget();
		angle -= double( Object::calcRadAngle( target->m_position.x, target->m_position.y, pTarget->m_position.x, pTarget->m_position.y ) );
	}
	else
		angle -= target->GetOrientation();

    while( angle > M_PI)
        angle -= 2.0 * M_PI;

    while(angle < -M_PI)
        angle += 2.0 * M_PI;

	// replace M_H_PI in the two lines below to reduce or increase angle

    double left = -1.0 * ( M_H_PI / 2.0 );
    double right = ( M_H_PI / 2.0 );

    return( ( angle <= left ) && ( angle >= right ) );
}
bool Object::isInArc(Object* target , float angle) // angle in degrees
{
    return inArc( GetPositionX() , GetPositionY() , angle , GetOrientation() , target->GetPositionX() , target->GetPositionY() );
}

bool Object::HasInArc( float degrees, Object* target )
{
	return isInArc(target, degrees);
}

bool Object::isInRange(Object* target, float range)
{
	float dist = CalcDistance( target );
	return( dist <= range );
}

bool Object::IsPet()
{
	if( IsUnit() == false )
	{ 
		return false;
	}

	if( internal_object_type & INTERNAL_OBJECT_TYPE_PET )
	{
		return true;
	}

/*	if( m_uint32Values[UNIT_FIELD_CREATEDBY] != 0 && m_uint32Values[UNIT_FIELD_SUMMONEDBY] != 0 )
	{ 
		return true;
	}*/

	return false;
}

void Object::_setFaction()
{
	FactionTemplateDBC* factT = NULL;

	if(GetTypeId() == TYPEID_UNIT || GetTypeId() == TYPEID_PLAYER)
	{
		factT = dbcFactionTemplate.LookupEntry(GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
		if( !factT )
			sLog.outDetail("Unit does not have a valid faction. It will make him act stupid in world. Don't blame us, blame yourself for not checking :P, faction %u set to entry %u",GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE),GetUInt32Value(OBJECT_FIELD_ENTRY) );
	}
	else
	if(GetTypeId() == TYPEID_GAMEOBJECT)
	{
		factT = dbcFactionTemplate.LookupEntry(GetUInt32Value(GAMEOBJECT_FACTION));
		if( !factT )
			sLog.outDetail("Game Object does not have a valid faction. It will make him act stupid in world. Don't blame us, blame yourself for not checking :P, faction %u set to entry %u",GetUInt32Value(GAMEOBJECT_FACTION),GetUInt32Value(OBJECT_FIELD_ENTRY) );
	}

	if(!factT)
	{
		factT = dbcFactionTemplate.LookupRow( 0 );
		//this is causeing a lot of crashes cause people have shitty dbs
//		return;
	}
	m_faction = factT;
	m_factionDBC = dbcFaction.LookupEntry(factT->Faction);
	if( !m_factionDBC )
		m_factionDBC = dbcFaction.LookupRow( 0 );
}

/*
void Object::UpdateOppFactionSet()
{
	m_oppFactsInRange.clear();
	this->AquireInrangeLock(); //make sure to release lock before exit function !
	for(Object::InRangeSet::iterator i = GetInRangeSetBegin(); i != GetInRangeSetEnd(); ++i)
	{
		if (((*i)->GetTypeId() == TYPEID_UNIT) || ((*i)->GetTypeId() == TYPEID_PLAYER) || ((*i)->GetTypeId() == TYPEID_GAMEOBJECT))
		{
			if (isHostile(this, (*i)))
			{
				if(!(*i)->IsInRangeOppFactSet(this))
					(*i)->m_oppFactsInRange.insert(this);
				if (!IsInRangeOppFactSet((*i)))
					m_oppFactsInRange.insert((*i));
				
			}
			else
			{
				if((*i)->IsInRangeOppFactSet(this))
					(*i)->m_oppFactsInRange.erase(this);
				if (IsInRangeOppFactSet((*i)))
					m_oppFactsInRange.erase((*i));
			}
		}
	}
	this->ReleaseInrangeLock();
}*/

/*
void Object::UpdateSameFactionSet()
{
	m_sameFactsInRange.clear();
	this->AquireInrangeLock(); //make sure to release lock before exit function !
	for(Object::InRangeSet::iterator i = GetInRangeSetBegin(); i != GetInRangeSetEnd(); ++i)
	{
		if (((*i)->GetTypeId() == TYPEID_UNIT) || ((*i)->GetTypeId() == TYPEID_PLAYER) || ((*i)->GetTypeId() == TYPEID_GAMEOBJECT))
		{
			if (isFriendly(this, (*i)))
			{
				if(!(*i)->IsInRangeSameFactSet(this))
					(*i)->m_sameFactsInRange.insert(this);
				if (!IsInRangeOppFactSet((*i)))
					m_sameFactsInRange.insert((*i));
				
			}
			else
			{
				if((*i)->IsInRangeSameFactSet(this))
					(*i)->m_sameFactsInRange.erase(this);
				if (IsInRangeSameFactSet((*i)))
					m_sameFactsInRange.erase((*i));
			}
		}
	}
	this->ReleaseInrangeLock();
}*/

void Object::EventSetUInt32Value(uint32 index, uint32 value)
{
	SetUInt32Value(index,value);
}

//This is created with statitics data based on bugs found inside emu! Needs to be update periodically
//attacker is index[0] and victim is index [1] => table[a][v] = chance to win the fight / 4
//X% of extra win chance of attacker is converted into victim defense
//Y% of extra loose chance of victim is converted into victim dmg
//X+Y can differ from 100% because more defense mod is used then DMG
//!!!values are relative to previous forced balancing !!
float PVP_forced_balancing[12][12] = 
{
//   none     warr     pala     hunter   rogue    priest   DK       shaman   mage     warlock  none     druid    
    {0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f}, // none
    {0.0000f, 0.0000f, 1.0380f, 0.5635f, 0.4665f, 0.5635f, 1.3246f, 0.8376f, 0.9355f, 0.4772f, 0.0000f, 0.4690f}, // warr
    {0.0000f, 0.9619f, 0.0000f, 0.9825f, 0.7474f, 0.7858f, 1.2724f, 0.8174f, 0.9744f, 0.4853f, 0.0000f, 1.0681f}, // pala
    {0.0000f, 1.0364f, 1.0175f, 0.0000f, 0.9649f, 1.0324f, 1.1403f, 0.9690f, 0.8486f, 0.9583f, 0.0000f, 1.1547f}, // hunter
    {0.0000f, 1.1334f, 1.2525f, 1.0350f, 0.0000f, 0.4744f, 1.1867f, 1.3142f, 0.9040f, 0.5222f, 0.0000f, 1.0911f}, // rogue
    {0.0000f, 1.0364f, 1.2141f, 0.9675f, 1.1255f, 0.0000f, 1.2546f, 1.1298f, 0.9003f, 0.9655f, 0.0000f, 0.6985f}, // priest
    {0.0000f, 0.6753f, 0.7276f, 0.8596f, 0.4132f, 0.7453f, 0.0000f, 0.6755f, 0.8246f, 0.7331f, 0.0000f, 0.8211f}, // DK
    {0.0000f, 1.1623f, 1.1825f, 1.0309f, 0.6857f, 0.8701f, 1.3244f, 0.0000f, 0.9352f, 0.8939f, 0.0000f, 0.8438f}, // shaman
    {0.0000f, 1.0644f, 1.0255f, 1.1513f, 1.0959f, 1.0996f, 1.1753f, 1.0647f, 0.0000f, 0.8410f, 0.0000f, 0.7677f}, // mage
    {0.0000f, 1.1227f, 1.1146f, 1.0416f, 1.0777f, 1.0344f, 1.2668f, 1.1061f, 1.1589f, 0.0000f, 0.0000f, 1.1898f}, // warlock
    {0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f}, // none
    {0.0000f, 1.1310f, 0.9318f, 0.8452f, 0.9088f, 1.3014f, 1.1788f, 1.1561f, 1.2322f, 0.8101f, 0.0000f, 0.0000f}, // druid
};

void Object::DealDamage(Unit *pVictim, uint32 damage, uint32 targetEvent, uint32 unitEvent, uint32 spellId, bool no_remove_auras)
{
	Player* plr = 0;

#ifdef FORCED_GM_TRAINEE_MODE
	if( this->IsPlayer() && SafePlayerCast( this )->GetSession() && SafePlayerCast( this )->GetSession()->HasPermissions() && !SafePlayerCast( this )->GetSession()->HasGMPermissions() )
		return; //no DMG by trainees
#endif

	if( !pVictim || !pVictim->isAlive() || !pVictim->IsInWorld() || !IsInWorld() )
	{ 
		return;
	}
	if( pVictim->bInvincible )
	{
		return;
	}
	if( pVictim->IsSpiritHealer() )
	{ 
		return;
	}

	//this is emu crap balancer - convert win / loose chance into a DMG mod
/*	if( this->IsUnit() && PVP_forced_balancing[ SafeUnitCast(this)->getClass() ][ pVictim->getClass() ] != 0.0f )
	{
		float dmg_mod = PVP_forced_balancing[ SafeUnitCast(this)->getClass() ][ pVictim->getClass() ];
		uint32 new_dmg = float2int32( damage * dmg_mod );
		//sanity check to make sure nothing went uber wrong
		if( new_dmg < damage / 2 )
			new_dmg = damage / 2;
		else if( new_dmg < damage * 2 ) 
			new_dmg = damage * 2;
		damage = new_dmg;
	}/**/

	if( this->IsUnit() && pVictim->IsUnit() && pVictim != this )
	{
		// Set our attack target to the victim.
		SafeUnitCast( this )->CombatStatus.OnDamageDealt( pVictim );
		if( sWorld.AnyKillerBlowReduction && sWorld.AnyKillerBlowBelow > damage && pVictim->IsPlayer() )
		{
			uint32 max_dmg = (int32)( pVictim->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) / sWorld.AnyKillerBlowReduction ) ;
			if( damage > max_dmg )
				damage = max_dmg;
		}
/*		//patch for beez : weapon X does Y phisical DMG all the time. Strongly hardcoded shit
		if( spellId == 0					//needs phizical weapon
			&& pVictim->GetEntry() == 1715	//change mob entry here !
			&& this->IsPlayer()										//it's a must to have a weapon
			&& SafePlayerCast( this )->GetItemInterface()	//can never happen
			&& SafePlayerCast( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND )	//probably true if we get here
			&& SafePlayerCast( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND )->GetEntry() == 25 //change item entry here !
			)
			damage = 50000;	// change dmg here !!
			*/
	}
	
	if( pVictim->GetStandState() )//not standing-> standup
	{
		pVictim->SetStandState( STANDSTATE_STAND );//probably mobs also must standup
	}

	// This one is easy. If we're attacking a hostile target, and we're not flagged, flag us.
	// Also, you WONT get flagged if you are dueling that person - FiShBaIt
	if( pVictim->IsPlayer() )
	{
		//aplied individually
		//in 3.2 resiliance reduces all damage not just spells
		float dmg_reduction_pct;
		if( spellId )
			dmg_reduction_pct = SafePlayerCast(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE ) * 2.2f / 100.0f;
		else 
			dmg_reduction_pct = SafePlayerCast(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE ) * 2.2f / 100.0f;
		//if this is crit dmg then multiply reisliance by 2.2f
		if( dmg_reduction_pct >= 0.8f )
			dmg_reduction_pct = 0.8f; // not sure about this cap, defenetly not good to resist all
		damage = float2int32( damage - damage * dmg_reduction_pct );

		if( IsPlayer() )
		{	
			if( isHostile( this, pVictim ) && SafePlayerCast( pVictim )->DuelingWith != SafePlayerCast( this ) )
				SafePlayerCast( this )->SetPvPFlag();
		}

		//If our pet attacks  - flag us.
		if( IsPet() )
		{
			Player* owner = SafePetCast( this )->GetPetOwner() ;
			if( owner != NULL )
			{  
				if( owner->isAlive() && SafePlayerCast( pVictim )->DuelingWith != owner )
					owner->SetPvPFlag();
			}
		}
		else if( IsCreature() &&  SafeCreatureCast( this )->IsTotem() )
		{
			Player* owner = SafeCreatureCast( this )->GetTotemOwner() ;
			if( owner != NULL && owner->isAlive() && SafePlayerCast( pVictim )->DuelingWith != owner )
				owner->SetPvPFlag();		
		}
	}
	//pets inherit owner resiliance
	if( pVictim->IsPet() )
	{
		Player* owner = SafePetCast( pVictim )->GetPetOwner() ;
		if( owner != NULL )
		{  
			float dmg_reduction_pct;
			if( spellId )
				dmg_reduction_pct = owner->CalcRating( PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE ) * 2.2f / 100.0f;
			else 
				dmg_reduction_pct = owner->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE ) * 2.2f / 100.0f;
			if( dmg_reduction_pct >= 0.8f )
				dmg_reduction_pct = 0.8f; // not sure about this cap, defenetly not good to resist all
			damage = float2int32( damage - damage * dmg_reduction_pct );
		}
	}

	if(!no_remove_auras)
	{
		//zack 2007 04 24 : root should not remove self (and also other unknown spells)
		if(spellId)
		{
			pVictim->RemoveAurasByInterruptFlagButSkip(AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN,spellId);
//			if(Rand(35))
//				pVictim->RemoveAurasByInterruptFlagButSkip(AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN,spellId);
		}
		else
		{
			pVictim->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN);
//			if(Rand(35))
//				pVictim->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN);
		}
	}

	if(this->IsUnit())
	{
		if( pVictim->IsPlayer() )
		{
			if( pVictim->CombatStatus.IsInCombat() )
				sHookInterface.OnEnterCombat( SafePlayerCast( pVictim ), SafeUnitCast( this ) );
			SafePlayerCast( pVictim )->m_dmg_received_since_login += damage;
		}

		if(IsPlayer() && ! SafePlayerCast( this )->CombatStatus.IsInCombat() == true )
			sHookInterface.OnEnterCombat( SafePlayerCast( this ), SafePlayerCast( this ) );

		//the black sheep , no actually it is paladin : Ardent Defender
		if(SafeUnitCast(this)->DamageTakenPctModOnHP35 && HasFlag(UNIT_FIELD_AURASTATE , AURASTATE_FLAG_HEALTH_BELOW_35_PCT) )
			damage = damage - float2int32(damage * SafeUnitCast(this)->DamageTakenPctModOnHP35) / 100 ;
			
		plr = 0;
		if(IsPet())
			plr = SafePetCast(this)->GetPetOwner();
		else if(IsPlayer())
		{
			plr = SafePlayerCast( this );
			plr->m_dmg_made_since_login += damage;
			plr->m_dmg_made_last_time = damage;
		}

		if(pVictim->GetTypeId()==TYPEID_UNIT && plr && plr->GetTypeId() == TYPEID_PLAYER) // Units can't tag..
		{
			// Tagging
			Creature *victim = SafeCreatureCast(pVictim);
			bool taggable;
			if(victim->GetCreatureInfo() && (victim->GetCreatureInfo()->Type == CRITTER || victim->IsPet()))
				taggable = false;
			else 
				taggable = true;

			if(taggable && victim->TaggerGroupId == NULL && victim->TaggerGuid == 0 )
			{
//				victim->Tagged = true;
				//try to tag it as group + as person
				victim->TaggerGroupId = plr->GetGroup();
				victim->TaggerGuid = plr->GetGUID();

				/* set loot method */
				if( plr->GetGroup() != NULL )
					victim->m_lootMethod = plr->GetGroup()->GetMethod();

				// For new players who get a create object
				uint32 Flags = pVictim->m_uint32Values[UNIT_DYNAMIC_FLAGS];
				Flags |= U_DYN_FLAG_TAPPED_BY_PLAYER;

				pVictim->m_uint32Values[UNIT_DYNAMIC_FLAGS] |= U_DYN_FLAG_TAGGED_BY_OTHER;

				// Update existing players.
				ByteBuffer buf(500);
				ByteBuffer buf1(500);

				pVictim->BuildFieldUpdatePacket(&buf1, UNIT_DYNAMIC_FLAGS, Flags);
				pVictim->BuildFieldUpdatePacket(&buf, UNIT_DYNAMIC_FLAGS, pVictim->m_uint32Values[UNIT_DYNAMIC_FLAGS]);

				// Loop inrange set, append to their update data.
				for(std::set<Player*>::iterator itr = m_inRangePlayers.begin(); itr != m_inRangePlayers.end(); ++itr)
				{
					if (SafePlayerCast(plr)->InGroup())
					{
						if (SafePlayerCast(*itr)->GetGroup() && SafePlayerCast(plr)->GetGroup()->GetID() == SafePlayerCast(*itr)->GetGroup()->GetID())
						{
							(*itr)->PushUpdateData(&buf1, 1);
						} 
						else
						{
							(*itr)->PushUpdateData(&buf, 1);
						}
						
					} 
					else
					{
						(*itr)->PushUpdateData(&buf, 1);
					}
				}

				// Update ourselves
				plr->PushUpdateData(&buf1, 1);

			}
		}		
	}

        ///Rage
	if( pVictim->GetPowerType() == POWER_TYPE_RAGE && pVictim != this )
	{
		float val;
		uint32 level = pVictim->getLevel();
		float conv;
		if( level <= PLAYER_LEVEL_CAP )
			conv = DamageToRageConversionTable[ level ];
		else 
			conv = ( 2.5f * 10 ) / (0.0091107836f * level * level + 3.225598133f * level + 4.2652911f);
		val = damage * conv;
		if( pVictim->IsPlayer() )
			val *= ( 1 + ( SafePlayerCast( pVictim )->rageFromDamageTaken / 100.0f ) );
		uint32 rage = pVictim->GetUInt32Value( UNIT_FIELD_POWER2 );
		if( rage + float2int32( val ) > 1000 )
			val = 1000.0f - (float)pVictim->GetUInt32Value( UNIT_FIELD_POWER2 );

		pVictim->ModUnsigned32Value( UNIT_FIELD_POWER2, (int32)val) ;
	}

	if( pVictim->IsPlayer() )
	{
		Player *pThis = SafePlayerCast(pVictim);
		if(pThis->cannibalize)
		{
			sEventMgr.RemoveEvents(pVictim, EVENT_CANNIBALIZE);
			pThis->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
			pThis->cannibalize = false;
		}
	}

	//* BATTLEGROUND DAMAGE COUNTER *//
	if( pVictim != this )
	{
		if( IsPlayer() )
		{
			plr = SafePlayerCast( this );
		}
		else if( IsPet() )
		{
			plr = SafePetCast( this )->GetPetOwner();
			if (plr)
				if( plr != NULL && plr->GetMapMgr() == GetMapMgr() )
					plr = NULL;
		}

		if( plr != NULL && plr->m_bg != NULL && plr->GetMapMgr() == GetMapMgr() )
		{
			plr->m_bgScore.DamageDone += damage;
			plr->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_DAMAGE_DONE,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,damage,ACHIEVEMENT_EVENT_ACTION_ADD);
			//strange huh ? 2 objects on same map but one has fucked up BG pointer
//			if( BattlegroundManager.IsValidBGPointer( plr->m_bg ) )
				plr->m_bg->UpdatePvPData();
//			else
//				plr->m_bg = NULL;
		}
	}
   
	uint32 health = pVictim->GetUInt32Value(UNIT_FIELD_HEALTH );

	/*------------------------------------ DUEL HANDLERS --------------------------*/
	//Both Players. Victim is receiving dmg from dueling player
	if((pVictim->IsPlayer()) && (this->IsPlayer()) && SafePlayerCast(pVictim)->DuelingWith == SafePlayerCast( this ) ) 
	{
		if((health <= damage) && SafePlayerCast( this )->DuelingWith != NULL)
//		if( health <= damage && pVictim->IsPlayer() && SafePlayerCast(pVictim)->DuelingWith )
		{
			//Player in Duel and Player Victim has lost
			uint32 NewHP = pVictim->GetUInt32Value(UNIT_FIELD_MAXHEALTH)/100;

			if(NewHP < 5) 
				NewHP = 5;

			//Set there health to 1% or 5 if 1% is lower then 5
			pVictim->SetUInt32Value(UNIT_FIELD_HEALTH, NewHP);
			//End Duel
			Player *owner;
			if( GetUInt32Value( UNIT_FIELD_CREATEDBY ) && GetMapMgr() )
				owner = GetMapMgr()->GetPlayer( GetUInt64Value( UNIT_FIELD_CREATEDBY ) );
			else if( IsPlayer() )
				owner = SafePlayerCast( this );
			else
				owner = NULL;
			if( owner )
				owner->EndDuel(DUEL_WINNER_KNOCKOUT);
			else
				SafePlayerCast( pVictim )->EndDuel( DUEL_WINNER_RETREAT );

			// surrender emote
			pVictim->Emote(EMOTE_ONESHOT_BEG);			// Animation

			return;		  
		}
	}

	if((pVictim->IsPlayer()) && (IsPet())) 
	{
		if((health <= damage) && SafePlayerCast(pVictim)->DuelingWith == SafePetCast(this)->GetPetOwner())
		{
			Player *petOwner = SafePetCast(this)->GetPetOwner();
			if(petOwner)
			{
				//Player in Duel and Player Victim has lost
				uint32 NewHP = pVictim->GetUInt32Value(UNIT_FIELD_MAXHEALTH)/100;
				if(NewHP < 5) NewHP = 5;
				
				//Set there health to 1% or 5 if 1% is lower then 5
				pVictim->SetUInt32Value(UNIT_FIELD_HEALTH, NewHP);
				//End Duel
				petOwner->EndDuel(DUEL_WINNER_KNOCKOUT);
				return;
			}
		}
	}
	/*------------------------------------ DUEL HANDLERS END--------------------------*/

	bool isCritter = false;
	if(pVictim->IsCreature() && SafeCreatureCast(pVictim)->GetCreatureInfo())
	{
			if(SafeCreatureCast(pVictim)->GetCreatureInfo()->Type == CRITTER)
				isCritter = true;
	}
	/* -------------------------- HIT THAT CAUSES VICTIM TO DIE ---------------------------*/
	if ((isCritter || health <= damage) )
	{
		//general hook for die
		sHookInterface.OnPreUnitDie( SafeUnitCast( this ), pVictim);
		//warlock - seed of corruption
		if( IsUnit() )
		{
			SpellEntry *killerspell;
			if( spellId )
				killerspell = dbcSpell.LookupEntry( spellId );
			else killerspell = NULL;
			pVictim->HandleProc( PROC_ON_DIE, SafeUnitCast( this ), killerspell );
			SafeUnitCast( this )->HandleProc( PROC_ON_TARGET_DIE, pVictim, killerspell );
		}
		// check if pets owner is combat participant
		bool owner_participe = false;
		if( IsPet() )
		{
			Player* owner = SafePetCast( this )->GetPetOwner();
			if( owner != NULL && pVictim->GetAIInterface()->getThreatByPtr( owner ) > 0 )
				owner_participe = true;
		}

		/* -------------------------------- HONOR + BATTLEGROUND CHECKS ------------------------ */
		//Zack : this event should ocure before setting death state !
		plr = NULL;
		if( IsPlayer() )
			plr = SafePlayerCast( this );
		else if(IsPet())
			plr = SafePetCast( this )->GetPetOwner();

		if( plr != NULL)
		{
			//crap, we should check flags and map for this. But we do not have the support for it atm
			if( pVictim->IsPlayer() )
			{
#ifdef GENERATE_CLASS_BALANCING_STATISTICS
				if( plr->getLevel() == pVictim->getLevel() 
					&& plr->getClass() != pVictim->getClass() 
					&& plr->GetHealthPct() < 75
					)
				{
					Player *pvictim = SafePlayerCast( pVictim );
					//players should have similar gear - 100 means they have very similar gear score
					int32 plr1_str = plr->item_level_sum / ( plr->item_count_sum + 1 );
					int32 plr2_str = pvictim->item_level_sum / ( pvictim->item_count_sum + 1 );
					float difference_pct_score1 = ( (float)abs(plr1_str - plr2_str) / (float)( plr1_str + plr2_str + 1 ) );
					//no naked player testing dmg on other
					if( difference_pct_score1 <= 0.25 
						&& plr->CombatStatus.HealSize() < 2 && plr->CombatStatus.AttackersSize() < 2			//avoid imba group fights
						&& pvictim->CombatStatus.HealSize() < 2 && pvictim->CombatStatus.AttackersSize() < 2 )	//avoid imba group fights
						CharacterDatabase.Execute("Update war_balancer set c=c+1 where A=%d and v=%d",plr->getClass(),pVictim->getClass());
				}
#endif
				if( plr->m_bg != 0 )
					plr->m_bg->HookOnPlayerKill( plr, SafePlayerCast( pVictim ) );

				sHookInterface.OnKillPlayer( plr, SafePlayerCast( pVictim ) );
				bool setAurastateFlag = false;
				if(plr->getLevel() > pVictim->getLevel())
				{
					unsigned int diff = plr->getLevel() - pVictim->getLevel();
					if( diff <= 8 )
					{
						HonorHandler::OnPlayerKilledUnit(plr, pVictim);
						setAurastateFlag = true;
					}
				}
				else
				{
					HonorHandler::OnPlayerKilledUnit( plr, pVictim );
					setAurastateFlag = true;
				}

				if (setAurastateFlag)
				{
					this->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_LASTKILLWITHHONOR);
					if(!sEventMgr.HasEvent(this,EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE))
						sEventMgr.AddEvent(SafeUnitCast(this),&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_LASTKILLWITHHONOR,EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE,20000,1,0);
					else sEventMgr.ModifyEventTimeLeft(this,EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE,20000);
				}
			}
			else
			{
				if (!isCritter) // REPUTATION
				{
					plr->Reputation_OnKilledUnit( pVictim, false );
				}
			}
			plr->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HIT_DEALT,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,damage,ACHIEVEMENT_EVENT_ACTION_SET_MAX);
		}
		/* -------------------------------- END : HONOR + BATTLEGROUND CHECKS END------------------------ */

		/* victim died! */
		if( pVictim->IsPlayer() )
		{
			SafePlayerCast( pVictim )->KillPlayer();
			SafePlayerCast( pVictim )->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HIT_RECEIVED,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,damage,ACHIEVEMENT_EVENT_ACTION_SET_MAX);
			SafePlayerCast( pVictim )->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_TOTAL_DAMAGE_RECEIVED,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,damage,ACHIEVEMENT_EVENT_ACTION_ADD);
			if( this->IsPlayer() )
			{
				if( pVictim != this )
				{
					SafePlayerCast( pVictim )->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_PLAYER,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
					plr->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_EARN_HONORABLE_KILL,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
					if( plr->m_bg )
						plr->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
				}
			}
			else
			{
				SafePlayerCast( pVictim )->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_CREATURE,GetUInt32Value( OBJECT_FIELD_ENTRY),ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
			}
		}
		else
		{
			pVictim->setDeathState( JUST_DIED );	//and add respawn event for corpse
			if( IsUnit() )
				pVictim->GetAIInterface()->HandleEvent( EVENT_LEAVECOMBAT, SafeUnitCast( this ), 0);
			if( plr )
				plr->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE,pVictim->GetUInt32Value( OBJECT_FIELD_ENTRY),ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
		}

		if( pVictim->IsPlayer() && !IsPlayer())
		{
			SafePlayerCast( pVictim )->DeathDurabilityLoss(0.10);
		}

		/* Zone Under Attack */
        MapInfo * pMapInfo = WorldMapInfoStorage.LookupEntry(GetMapId());
        if( pMapInfo && IS_STATIC_MAP( pMapInfo ) && !pVictim->IsPlayer() && !pVictim->IsPet() && ( IsPlayer() || IsPet() ) )
		{
			// Only NPCs that bear the PvP flag can be truly representing their faction.
			if( SafeCreatureCast(pVictim)->HasFlag( UNIT_FIELD_FLAGS, UNIT_FLAG_PVP ) )
			{
				Player * pAttacker = NULL;
				if( IsPet() )
					pAttacker = SafePetCast( this )->GetPetOwner();
				else if(IsPlayer())
					pAttacker = SafePlayerCast( this );

				if( pAttacker != NULL)
                {
				    uint8 teamId = (uint8)pAttacker->GetTeam();
				    if(teamId == 0) // Swap it.
					    teamId = 1;
				    else
					    teamId = 0;
//				    uint32 AreaID = pVictim->GetMapMgr()->GetAreaID(pVictim->GetPositionX(), pVictim->GetPositionY());
				    uint32 AreaID = sTerrainMgr.GetAreaID( pVictim->GetMapId(), pVictim->GetPositionX(), pVictim->GetPositionY(), pVictim->GetPositionZ() );
				    if(!AreaID)
					    AreaID = pAttacker->GetZoneId(); // Failsafe for a shitty TerrainMgr

				    if(AreaID)
				    {
					    WorldPacket data(SMSG_ZONE_UNDER_ATTACK, 4);
					    data << AreaID;
					    sWorld.SendFactionMessage(&data, teamId);
				    }
                }
			}
		}
		
		if(pVictim->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT) > 0)
		{
			Spell *spl = pVictim->GetCurrentSpell();
			if(spl != NULL)
			{
				for(int i = 0; i < 3; i++)
				{
					if(spl->GetProto()->Effect[i] == SPELL_EFFECT_PERSISTENT_AREA_AURA)
					{
						DynamicObject *dObj = GetMapMgr()->GetDynamicObject( pVictim->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT) );
						if(!dObj)
						{ 
							return;
						}
						WorldPacket data(SMSG_GAMEOBJECT_DESPAWN_ANIM, 8);
						data << dObj->GetGUID();
						dObj->SendMessageToSet(&data, false);
						dObj->Remove();
					}
				}
				if(spl->GetProto()->ChannelInterruptFlags == 48140) 
					spl->safe_cancel();
			}
		}
		
		/* Remove all Auras */
		pVictim->DropAurasOnDeath();

		/* Stop players from casting */
		std::set<Player*>::iterator itr;
		for( itr = pVictim->GetInRangePlayerSetBegin() ; itr != pVictim->GetInRangePlayerSetEnd() ; itr ++ )
		{
			//if player has selection on us
			if( (*itr)->GetSelection()==pVictim->GetGUID())							
			{
				if( (*itr)->isCasting() )
					(*itr)->CancelSpell( NULL ); //cancel current casting spell
			}
		}
		/* Stop victim from attacking */
		if( this->IsUnit() )
			pVictim->smsg_AttackStop( SafeUnitCast( this ) );

		if( pVictim->GetTypeId() == TYPEID_PLAYER )
		{
			SafePlayerCast( pVictim )->EventAttackStop();
			CALL_INSTANCE_SCRIPT_EVENT( m_mapMgr, OnPlayerDeath )( SafePlayerCast(pVictim) , SafeUnitCast(this) );
		}

		/* Set victim health to 0 */
		pVictim->SetUInt32Value(UNIT_FIELD_HEALTH, 0);
		if(pVictim->IsPlayer())
		{
			uint32 self_res_spell = 0;
			if (SafePlayerCast( pVictim )->m_bg == NULL || (SafePlayerCast( pVictim )->m_bg != NULL && SafePlayerCast( pVictim )->m_bg->GetType() != BATTLEGROUND_ARENA_5V5 && SafePlayerCast( pVictim )->m_bg->GetType() != BATTLEGROUND_ARENA_3V3 && SafePlayerCast( pVictim )->m_bg->GetType() != BATTLEGROUND_ARENA_2V2))
			{
				self_res_spell = SafePlayerCast( pVictim )->SoulStone;
				SafePlayerCast( pVictim )->SoulStone = SafePlayerCast( pVictim )->SoulStoneReceiver = 0;

				if( !self_res_spell && SafePlayerCast( pVictim )->bReincarnation )
				{
					SpellEntry* m_reincarnSpellInfo = dbcSpell.LookupEntry( 20608 );
					if( SafePlayerCast( pVictim )->Cooldown_CanCast( m_reincarnSpellInfo ) )
					{
						uint32 ankh_count = SafePlayerCast( pVictim )->GetItemInterface()->GetItemCount( 17030 );
						if( ankh_count )
							self_res_spell = 21169;
					}
				}
			}
			pVictim->SetUInt32Value( PLAYER_SELF_RES_SPELL, self_res_spell );
			pVictim->SetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID , 0 );
			//pVictim->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_MOUNTED_TAXI);
		}

		// Wipe our attacker set on death
		pVictim->CombatStatus.Vanished();

		//		 sent to set. don't send it to the party, becuase if they're out of
		//		 range they won't know this guid exists -> possible 132.

		/*if (this->IsPlayer())
			if( SafePlayerCast( this )->InGroup() )
				SafePlayerCast( this )->GetGroup()->SendPartyKillLog( this, pVictim );*/

		/* Stop Unit from attacking */
		if( this->IsPlayer() && (SafePlayerCast(this)->GetSelection() == pVictim->GetGUID()) )
			SafePlayerCast( this )->EventAttackStop();
	   
		if( this->IsUnit() )
		{
			CALL_SCRIPT_EVENT( this, OnTargetDied )( pVictim );

			//stop attack if he was our target
			if( ( IsPlayer() && SafePlayerCast( this )->GetSelection() == pVictim->GetGUID() )
				|| ( SafeUnitCast( this )->GetAIInterface() && SafeUnitCast( this )->GetAIInterface()->GetNextTarget() == pVictim ) )
				SafeUnitCast( this )->smsg_AttackStop( pVictim );
		
			/* Tell Unit that it's target has Died */
			SafeUnitCast( this )->addStateFlag( UF_TARGET_DIED );

			// We will no longer be attacking this target, as it's dead.
			//SafeUnitCast(this)->setAttackTarget(NULL);
		}
		//so now we are completely dead
		//lets see if we have spirit of redemption
		if( pVictim->IsPlayer() )
		{
			if( SafePlayerCast( pVictim)->HasSpell( 20711 ) ) //check for spirit of Redemption
			{
				SpellEntry* sorInfo = dbcSpell.LookupEntry(27827);
				if( sorInfo != NULL )
				{
					Spell *sor = SpellPool.PooledNew();
					sor->Init( pVictim, sorInfo, true, NULL );
					SpellCastTargets targets;
					targets.m_unitTarget = pVictim->GetGUID();
					sor->prepare(&targets);
				}
			}
		}
		uint64 victimGuid = pVictim->GetGUID();

		if( IsPlayer() )
		{
			WorldPacket data( SMSG_PARTYKILLLOG, 20 );
			data << GetGUID() << pVictim->GetGUID();
			if( SafePlayerCast( this )->GetGroup() )
				SafePlayerCast( this )->GetGroup()->SendPacketToAll( &data );
			else if( SafePlayerCast( this )->GetSession() )
				SafePlayerCast( this )->GetSession()->SendPacket( &data );
		}			

		if( pVictim->IsCreature() )
		{
			pVictim->GetAIInterface()->OnDeath(this);

			/* Tell Unit that it's target has Died */
			SafeUnitCast( pVictim )->SetFlag( UNIT_FIELD_FLAGS, UNIT_FLAG_DEAD );
			SafeUnitCast( pVictim )->RemoveFlag( UNIT_FIELD_FLAGS_2, UNIT_FLAG_ALIVE );

			// it Seems that pets some how dont get a name and cause a crash here
			//bool isCritter = (pVictim->GetCreatureInfo() != NULL)? pVictim->GetCreatureInfo()->Type : 0;

			//-----------------------------------LOOOT--------------------------------------------
			if ( (!pVictim->IsPet())&& ( !isCritter ) )
			{
				Creature * victim = SafeCreatureCast(pVictim);
				// fill loot vector.
				victim->generateLoot();

				Player *owner = NULL;
				if(victim->TaggerGuid)
					owner = GetMapMgr()->GetPlayer( victim->TaggerGuid );

				if(owner == NULL)  // no owner
				{
					// donno why this would happen, but anyway.. anyone can loot ;p
					// no owner no loot
					//victim->SetFlag(UNIT_DYNAMIC_FLAGS, U_DYN_FLAG_LOOTABLE);
					//Zack : reassign to killer if owner left
					if( plr )
					{
						victim->TaggerGuid = plr->GetGUID();	//probably player DCed
						victim->TaggerGroupId = plr->GetGroup();	//probably player DCed
						owner = plr;
					}
				}
				if( owner != NULL )
				{
					// Build the actual update.
					ByteBuffer buf( 500 );

					uint32 Flags = victim->m_uint32Values[ UNIT_DYNAMIC_FLAGS ];
					Flags |= U_DYN_FLAG_LOOTABLE;
					Flags |= U_DYN_FLAG_TAPPED_BY_PLAYER;

					victim->BuildFieldUpdatePacket( &buf, UNIT_DYNAMIC_FLAGS, Flags );

					// Check for owner's group.
					Group * pGroup = owner->GetGroup();
					if( pGroup != NULL )
					{
						// Owner was in a party.
						// Check loot method.
						victim->m_lootMethod = pGroup->GetMethod();
						switch( victim->m_lootMethod )
						{
						case PARTY_LOOT_RR:
/*						//this commented code is not used because it was never tested and finished !
						{
								//get new tagger for creature
								Player *tp = pGroup->GetnextRRlooter();
								if(tp)
								{
									//we force on creature a new tagger
									victim->TaggerGuid = tp->GetGUID();
									victim->Tagged = true;
									if(tp->IsVisible(victim))  // Save updates for non-existant creatures
										tp->PushUpdateData(&buf, 1);
								}
							}break;*/
						case PARTY_LOOT_FFA:
						case PARTY_LOOT_GROUP:
						case PARTY_LOOT_NBG:
							{
								// Loop party players and push update data.
								GroupMembersSet::iterator itr;
								SubGroup * sGrp;
								pGroup->Lock();
								for( uint32 Index = 0; Index < pGroup->GetSubGroupCount(); ++Index )
								{
									sGrp = pGroup->GetSubGroup( Index );
									itr = sGrp->GetGroupMembersBegin();
									for( ; itr != sGrp->GetGroupMembersEnd(); ++itr )
									{
										if( (*itr)->m_loggedInPlayer && (*itr)->m_loggedInPlayer->IsVisible( victim ) )	   // Save updates for non-existant creatures
											(*itr)->m_loggedInPlayer->PushUpdateData( &buf, 1 );
									}
								}
								pGroup->Unlock();
							}break;
						case PARTY_LOOT_MASTER:
							{
								GroupMembersSet::iterator itr;
								SubGroup * sGrp;
								pGroup->Lock();
								for( uint32 Index = 0; Index < pGroup->GetSubGroupCount(); ++Index )
								{
									sGrp = pGroup->GetSubGroup( Index );
									itr = sGrp->GetGroupMembersBegin();
									for( ; itr != sGrp->GetGroupMembersEnd(); ++itr )
									{
										if( (*itr)->m_loggedInPlayer && (*itr)->m_loggedInPlayer->IsVisible( victim ) )	   // Save updates for non-existant creatures
											(*itr)->m_loggedInPlayer->PushUpdateData( &buf, 1 );
									}
								}
								pGroup->Unlock();

								Player * pLooter = pGroup->GetLooter() ? pGroup->GetLooter()->m_loggedInPlayer : NULL;
								if( pLooter == NULL )
									pLooter = pGroup->GetLeader()->m_loggedInPlayer;

								if( pLooter->IsVisible( victim ) )  // Save updates for non-existant creatures
									pLooter->PushUpdateData( &buf, 1 );
							}break;
						}
					}
					else
					{
						// Owner killed the mob solo.
						if( owner->IsVisible( victim ) )
							owner->PushUpdateData( &buf, 1 );
					}
				}
			}
			//---------------------------------loot-----------------------------------------  

			// ----------------------------- XP --------------
			if ( pVictim->GetUInt64Value( UNIT_FIELD_CREATEDBY ) == 0 && 
				pVictim->GetUInt64Value( OBJECT_FIELD_CREATED_BY ) == 0 &&
				pVictim->GetMapMgr() &&
				!pVictim->IsPet() && SafeCreatureCast(pVictim)->TaggerGuid )
			{
				Unit *uTagger = pVictim->GetMapMgr()->GetUnit(SafeCreatureCast(pVictim)->TaggerGuid);
				if (uTagger != NULL)
				{
					if (uTagger->IsPlayer())
					{
						Player *pTagger = SafePlayerCast(uTagger);
						if (pTagger)
						{
							if (pTagger->InGroup())
							{
								pTagger->GiveGroupXP( pVictim, pTagger);
							}
							else if( IsUnit() ) 
							{
								uint32 xp = CalculateXpToGive( pVictim, uTagger );
								if( xp > 0 )
								{
									pTagger->GiveXP( xp, victimGuid, true );

									// This is crashing sometimes, commented by now
									this->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_LASTKILLWITHHONOR);
									if(!sEventMgr.HasEvent(this,EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE))
										sEventMgr.AddEvent(SafeUnitCast(this),&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_LASTKILLWITHHONOR,EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE,20000,1,0);
									else
										sEventMgr.ModifyEventTimeLeft(this,EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE,20000);

									if( pTagger->GetSummon() && pTagger->GetSummon()->CanGainXP() )
									{
										xp = CalculateXpToGive( pVictim, pTagger->GetSummon() );
										if( xp > 0 )
											pTagger->GetSummon()->GiveXP( xp );
									}
								}
							}
							if( !pVictim->IsPlayer() )
								sQuestMgr.OnPlayerKill( pTagger, SafeCreatureCast( pVictim ), true );
						}
					}
					else if (uTagger->IsPet())
					{
						Pet* petTagger = SafePetCast(uTagger);
						if (petTagger != NULL)
						{
							Player* petOwner = petTagger->GetPetOwner();
							if( petOwner != NULL)
							{
								if( petOwner->InGroup() )
								{
									//Calc Group XP
									petOwner->GiveGroupXP( pVictim, petOwner );
								}
								else if( IsUnit() )
								{
									uint32 xp = CalculateXpToGive( pVictim, petOwner );
									if( xp > 0 )
									{
										petOwner->GiveXP( xp, victimGuid, true );

										// This is crashing sometimes, commented by now
										this->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_LASTKILLWITHHONOR);
										if(!sEventMgr.HasEvent(this,EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE))
											sEventMgr.AddEvent(SafeUnitCast(this),&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_LASTKILLWITHHONOR,EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE,20000,1,0);
										else
											sEventMgr.ModifyEventTimeLeft(this,EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE,20000);

										if( petTagger->CanGainXP() )
										{
											xp = CalculateXpToGive( pVictim, petTagger );
											if( xp > 0 )
												petTagger->GiveXP( xp );
										}
									}
								}
								if(pVictim->GetTypeId() != TYPEID_PLAYER)
									sQuestMgr.OnPlayerKill( petOwner, SafeCreatureCast( pVictim ), true );
							}
						}
					}
				}
				// ----------------------------- XP --------------
			/* ----------------------------- PET XP HANDLING END-------------- */

			/* ----------------------------- PET DEATH HANDLING -------------- */
				if( pVictim->IsPet() )
				{
					Pet* pPet = SafePetCast( pVictim );
					Player* owner = pPet->GetPetOwner();

					// dying pet looses 1 happiness level (not in BG)
					if( !pPet->IsSummon() && !pPet->IsInBg() )
					{
						uint32 hap = pPet->GetUInt32Value( UNIT_FIELD_POWER5 );
						hap = hap - PET_HAPPINESS_UPDATE_VALUE > 0 ? hap - PET_HAPPINESS_UPDATE_VALUE : 0;
						pPet->SetUInt32Value( UNIT_FIELD_POWER5, hap );
					}
					
					pPet->DelayedRemove( false, true );
					
					//remove owner warlock soul link from caster
					if( owner != NULL )
						owner->EventDismissPet();
				}
				/* ----------------------------- PET DEATH HANDLING END -------------- */
				else if( pVictim->GetUInt64Value( UNIT_FIELD_CHARMEDBY ) )
				{
					//remove owner warlock soul link from caster
					Unit *owner=pVictim->GetMapMgr()->GetUnit( pVictim->GetUInt64Value( UNIT_FIELD_CHARMEDBY ) );
					if( owner != NULL && owner->IsPlayer())
						SafePlayerCast( owner )->EventDismissPet();
				}
			}
		}
		else if( pVictim->IsPlayer() )
		{
/*			//give XP ? !!THIS IS CUSTOM : loot and XP for BG player kill
			Player *owner;
			if( IsPlayer() )
				owner = SafePlayerCast( this );
			else if( this->IsPet() )
				owner = SafePetCast( this )->GetPetOwner();
			else 
				owner = NULL;
			if( owner && owner->m_bg )
			{
				float direct_base_gold = 10;
				float coef = 0;
				int lvl_diff = owner->getLevel() - pVictim->getLevel();
				if( lvl_diff > 3 )
				{
					coef = 0.1f;
					//catchup system
					uint32 xp = CalculateXpToGive( owner, pVictim ) / 2;
					pVictim->m_uint32Values[ PLAYER_XP ] += xp;
					//0.3 silver / level with 10 rates => 30 silver at level 10 ?
					pVictim->m_uint32Values[ PLAYER_FIELD_COINAGE ] += 30 * (uint32)(sWorld.getRate(RATE_MONEY)) * owner->getLevel() ;
				}
				else if( lvl_diff == 3 )
					coef = 0.25f;
				else if( lvl_diff == 2 )
					coef = 0.5f;
				else if( lvl_diff == 1 )
					coef = 0.75f;
				else if( lvl_diff == 0 )
					coef = 1.0f;
				else if( lvl_diff == -1 )
					coef = 1.25f;
				else if( lvl_diff == -2 )
					coef = 1.5f;
				else if( lvl_diff == -3 )
					coef = 1.75f;
				else if( lvl_diff < -3 )
					coef = 2.0f;
				// the more DMG and heal a char makes the faster he will level. But they all get same amount of gold. So noob players will have more time to get better geared.
				if ( owner->InGroup() )
				{
					owner->GiveGroupXP( pVictim, owner);
					//killer gets a small bonus ? 3 silver * 80 level = 2.5 gold top ?
					uint32 extra_kill_reward = 30 * (uint32)(coef * sWorld.getRate(RATE_MONEY)) * owner->getLevel();
					if( extra_kill_reward > 10000 )
						extra_kill_reward = 10000;
					owner->m_uint32Values[ PLAYER_FIELD_COINAGE ] += 30 * (uint32)(coef * sWorld.getRate(RATE_MONEY)) * owner->getLevel() ;
				}
//				else
//				{
//					uint32 xp = CalculateXpToGive( pVictim, owner );
//					if( xp > 0 )
//						owner->GiveXP( xp, victimGuid, true );
//				}	
				//now give gold to all killer raid
				Group* party = owner->GetGroup();
				if(party)
				{
					uint32 killer_party_strength = 1;
					vector<Player*> targets;
					targets.reserve(party->MemberCount());

					GroupMembersSet::iterator itr;
					SubGroup * sgrp;
					party->getLock().Acquire();
					for(uint32 i = 0; i < party->GetSubGroupCount(); i++)
					{
						sgrp = party->GetSubGroup(i);
						for(itr = sgrp->GetGroupMembersBegin(); itr != sgrp->GetGroupMembersEnd(); ++itr)
						{
							if((*itr)->m_loggedInPlayer 
								&& owner->GetMapMgr() == (*itr)->m_loggedInPlayer->GetMapMgr()
								&& owner->GetDistanceSq((*itr)->m_loggedInPlayer)<60*60
								)
							{
								targets.push_back((*itr)->m_loggedInPlayer);
								killer_party_strength += (*itr)->m_loggedInPlayer->item_level_sum;
							}
						}
					}
					party->getLock().Release();
					if(targets.size())
					{
						uint32 money =  1000 * (uint32)(coef * sWorld.getRate(RATE_MONEY)) * owner->getLevel() / 10;
//						uint32 share = money / uint32(targets.size());
//						if( share > 100000 )	//10 gold ?
//							share = 100000;
	
						for(vector<Player*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
						{
							uint32 local_strength_PCT = 100 - (*itr)->item_level_sum * 100 / killer_party_strength; //inverse strength factor. Noobs get more gold.
							uint32 local_share = money / 2 + money * local_strength_PCT / 200;
							if( local_share > 100000 )	//10 gold ?
								local_share = 100000;
							WorldPacket pkt;
							pkt.SetOpcode(SMSG_LOOT_MONEY_NOTIFY);
							pkt << local_share;
							(*itr)->ModGold( local_share);
							(*itr)->GetSession()->SendPacket(&pkt);
						}
					}
				}
			}/**/

			/* -------------------- RESET BREATH STATE ON DEATH -------------- */
			SafePlayerCast( pVictim )->m_UnderwaterTime = 0;
			SafePlayerCast( pVictim )->m_UnderwaterState = 0;
			SafePlayerCast( pVictim )->m_BreathDamageTimer = 0;
			SafePlayerCast( pVictim )->m_SwimmingTime = 0;

			/* -------------------- KILL PET WHEN PLAYER DIES ---------------*/
			if( SafePlayerCast( pVictim )->GetSummon() != NULL )
			{
				if( pVictim->GetUInt32Value( UNIT_CREATED_BY_SPELL ) > 0 )
					SafePlayerCast( pVictim )->GetSummon()->Dismiss( );
				else
					SafePlayerCast( pVictim )->GetSummon()->Remove( true, false );
			}
			/* -------------------- KILL PET WHEN PLAYER DIES END---------------*/
		}
		else sLog.outError("DealDamage for Unknown Object.");
	}
	else /* ---------- NOT DEAD YET --------- */
	{
		if(pVictim != this /* && updateskill */)
		{
			// Send AI Reaction UNIT vs UNIT
			/* Weird: why should WE react on OUR damage?
			If meaning of this is to get reaction of victim, then its already handled few rows below... 
			if( GetTypeId() ==TYPEID_UNIT )
			{
				SafeUnitCast( this )->GetAIInterface()->AttackReaction( pVictim, damage, spellId );
			}*/
			
			// Send AI Victim Reaction
			if( this->IsPlayer() || this->IsCreature() )
			{
				if( !pVictim->IsPlayer() )
				{
					SafeCreatureCast( pVictim )->GetAIInterface()->AttackReaction( SafeUnitCast( this ), damage, spellId );
				}
				else
				{
					// Defensive pet
					Pet* pPet = SafePlayerCast( pVictim )->GetSummon();
					if( pPet != NULL && pPet->GetPetState() != PET_STATE_PASSIVE )
					{
						pPet->GetAIInterface()->AttackReaction( SafeUnitCast( this ), 1, 0 );
						pPet->HandleAutoCastEvent( AUTOCAST_EVENT_OWNER_ATTACKED );
					}
				}
			}
		}
		
		// TODO: Mark victim as a HK
		/*if( SafePlayerCast( pVictim )->GetCurrentBattleground() != NULL && SafePlayerCast( this )->GetCurrentBattleground() != NULL)
		{
			
		}*/	

		pVictim->SetUInt32Value( UNIT_FIELD_HEALTH, health - damage );

		if ( IsCreature() 
//			&& !IsPet()	//removed by zack : why don't pets get agro from target ?
			)
			SafeUnitCast(this)->GetAIInterface()->HandleEvent(EVENT_DAMAGEDEALT, pVictim, damage);
	}
}

void Object::SpellNonMeleeDamageLog(Unit *pVictim, SpellEntry *spellInfo, uint32 damage, bool allowProc, bool static_damage, bool no_remove_auras,uint32 DOTticks, int32 pct_mod )
{
//==========================================================================================
//==============================Unacceptable Cases Processing===============================
//==========================================================================================
	if(!pVictim || !pVictim->isAlive())
	{ 
		return;
	}

	if(!spellInfo)
	{ 
        return;
	}

	if (this->IsPlayer() && !SafePlayerCast( this )->canCast(spellInfo))
	{ 
		return;
	}
//==========================================================================================
//==============================Variables Initialization====================================
//========================================================================================== 
	uint32 school = spellInfo->School;
	uint32 spellID = spellInfo->Id;
	float res = float(damage);
	int32 spell_dmg_bonus;
	uint32 aproc;
	uint32 vproc;
	if( DOTticks == 1 )
	{
		aproc = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_ANY_SPELL_DAMAGE_DONE;
		vproc = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_ANY_DAMAGE_VICTIM; /*| PROC_ON_SPELL_HIT_VICTIM;*/
	}
	else
	{
		aproc = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_SPELL_HIT | PROC_ON_ANY_SPELL_DAMAGE_DONE;
		vproc = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_SPELL_HIT_VICTIM | PROC_ON_ANY_DAMAGE_VICTIM; 
	}
	
	//A school damage is not necessarily magic
	switch( spellInfo->Spell_Dmg_Type )
	{
	case SPELL_DMG_TYPE_RANGED:	{
			aproc |= PROC_ON_RANGED_ATTACK;
			vproc |= PROC_ON_RANGED_ATTACK_VICTIM;
		}break;
		
	case SPELL_DMG_TYPE_MELEE:{
			aproc |= PROC_ON_MELEE_ATTACK;
			vproc |= PROC_ON_MELEE_ATTACK_VICTIM;
		}break;

	case SPELL_DMG_TYPE_MAGIC:{
			aproc |= PROC_ON_SPELL_HIT;
			vproc |= PROC_ON_SPELL_HIT_VICTIM;
		}break;
	}

	bool critical = false;
//==========================================================================================
//==============================+Spell Damage Bonus Calculations============================
//==========================================================================================
//------------------------------by stats----------------------------------------------------

	if( this->IsUnit() )
	{
		Unit* caster = SafeUnitCast( this );
		caster->RemoveAurasByInterruptFlagButSkip( AURA_INTERRUPT_ON_START_ATTACK , spellID );
		if( !static_damage )
		{
			int32 dmg_i = (int32)res;
			spell_dmg_bonus = caster->GetSpellDmgBonus( pVictim, spellInfo, dmg_i, DOTticks ) / (int32)DOTticks;

			//big hack to balance classes !!!!
	//		if( caster->getClass() == MAGE || caster->getClass() == PRIEST || caster->getClass() == WARLOCK )
//				spell_dmg_bonus += spell_dmg_bonus * 11 / 100;
				spell_dmg_bonus += spell_dmg_bonus * 6 / 100;
			//big hack to balance classes !!!!

			res += spell_dmg_bonus;
		}
		float spell_crit_mod = 0.0f;
		if( Need_SM_Apply(spellInfo) )
		{
			SM_FFValue(caster->SM_CriticalChance, &spell_crit_mod, spellInfo->SpellGroupType);
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
			float spell_flat_modifers=0;
			SM_FFValue(caster->SM_CriticalChance,&spell_flat_modifers,spellInfo->SpellGroupType);
			if(spell_flat_modifers!=0)
				printf("!!!!spell critchance mod flat %f ,spell group %u\n",spell_flat_modifers,spellInfo->SpellGroupType);
#endif
		}
//==========================================================================================
//==============================Post +SpellDamage Bonus Modifications=======================
//==========================================================================================
		if( res < 0 )
			res = 0;
		else if( (spellInfo->spell_can_crit == true && DOTticks == 1) || ( ( spellInfo->spell_DOT_can_crit == true || spell_crit_mod != 0 ) && DOTticks != 1 )   )
		{
//------------------------------critical strike chance--------------------------------------	
			// lol ranged spells were using spell crit chance
			float CritChance=0.0f;
			if( spellInfo->is_ranged_spell )
			{

				if( IsPlayer() )
				{
					CritChance = GetFloatValue( PLAYER_RANGED_CRIT_PERCENTAGE );
					if( pVictim->IsPlayer() )
						CritChance += SafePlayerCast(pVictim)->res_R_crit_get();
				}
				else
				{
					CritChance = 5.0f; // static value for mobs.. not blizzlike, but an unfinished formula is not fatal :)
				}
				CritChance += (float)(pVictim->AttackerCritChanceMod[spellInfo->School]);
				if( pVictim->IsPlayer() )
					CritChance -= SafePlayerCast(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_RANGED_CRIT_RESILIENCE ) * 2;
			}
			else if( spellInfo->is_melee_spell )
			{
				// Same shit with the melee spells, such as Judgement/Seal of Command
				if( IsPlayer() )
				{
					CritChance = GetFloatValue(PLAYER_CRIT_PERCENTAGE);
				}
				if( pVictim->IsPlayer() )
				{
					CritChance += SafePlayerCast(pVictim)->res_R_crit_get(); //this could be ability but in that case we overwrite the value
				}
				// Resilience
				CritChance -= pVictim->IsPlayer() ? SafePlayerCast(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE ) * 2 : 0.0f;
				// Victim's (!) crit chance mod for physical attacks?
				CritChance += (float)(pVictim->AttackerCritChanceMod[0]);
			}
			else
			{
				CritChance = caster->spellcritperc + caster->SpellCritChanceSchool[school] + pVictim->AttackerCritChanceMod[school];
				if( caster->IsPlayer() && ( pVictim->m_rooted - pVictim->m_stunned ) )	
					CritChance += SafePlayerCast( caster )->m_RootedCritChanceBonus;

				//screw special cases 
				if( spellInfo->NameHash == SPELL_HASH_LAVA_BURST && pVictim->HasAurasWithNameHash( SPELL_HASH_FLAME_SHOCK ) )
					CritChance += 200;

				if( pVictim->IsPlayer() )
					CritChance -= SafePlayerCast(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE ) * 2.2f;
			}
			CritChance += spell_crit_mod;
			if( CritChance < 0 ) 
				CritChance = 0;
			if( CritChance > 95 ) 
				CritChance = 95;
			critical = Rand(CritChance);
			//sLog.outString( "SpellNonMeleeDamageLog: Crit Chance %f%%, WasCrit = %s" , CritChance , critical ? "Yes" : "No" );
//==========================================================================================
//==============================Spell Critical Hit==========================================
//==========================================================================================
			if (critical)
			{		
				int32 critical_bonus = 100;
				if( Need_SM_Apply(spellInfo) )
					SM_FIValue( caster->SM_PCriticalDamage, &critical_bonus, spellInfo->SpellGroupType );

				if( critical_bonus > 0 )
				{
					// the bonuses are halved by 50% (funky blizzard math :S)
					float b;
					if( spellInfo->School == 0 || spellInfo->is_melee_spell || spellInfo->is_ranged_spell )		// physical || hackfix SoCommand/JoCommand
						b = ( ( float(critical_bonus) ) / 100.0f ) + 1.0f;
					else
						b = ( ( float(critical_bonus) / 2.0f ) / 100.0f ) + 1.0f;
			
					res *= b;
				}

				//crits are further reduced
				if( pVictim->IsPlayer() )
				{
					//res = res*(1.0f-2.0f*SafePlayerCast(pVictim)->CalcRating(PLAYER_RATING_MODIFIER_MELEE_CRIT_RESISTANCE));
					//Resilience is a special new rating which was created to reduce the effects of critical hits against your character.
					//It has two components; it reduces the chance you will be critically hit by x%, 
					//and it reduces the damage dealt to you by critical hits by 2x%. x is the percentage resilience granted by a given resilience rating. 
					//It is believed that resilience also functions against spell crits, 
					//though it's worth noting that NPC mobs cannot get critical hits with spells.
					float dmg_reduction_pct = 2.2f * SafePlayerCast(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE ) / 100.0f;
					if( dmg_reduction_pct > 0.8f )
						dmg_reduction_pct = 0.8f; //we cannot resist more then he is criticalling us, there is no point of the critical then :P
					res = res - res * dmg_reduction_pct;
				}

				if (pVictim->GetTypeId() == TYPEID_UNIT && SafeCreatureCast(pVictim)->GetCreatureInfo() && SafeCreatureCast(pVictim)->GetCreatureInfo()->Rank != ELITE_WORLDBOSS)
					pVictim->Emote( EMOTE_ONESHOT_WOUNDCRITICAL );
				/*aproc |= PROC_ON_SPELL_CRIT_HIT;
				vproc |= PROC_ON_SPELL_CRIT_HIT_VICTIM;*/

				switch( spellInfo->Spell_Dmg_Type )
				{
				case SPELL_DMG_TYPE_RANGED:	{
						aproc |= PROC_ON_RANGED_CRIT_ATTACK;
						vproc |= PROC_ON_RANGED_CRIT_ATTACK_VICTIM;
					}break;
					
				case SPELL_DMG_TYPE_MELEE:{
						aproc |= PROC_ON_CRIT_ATTACK;
						vproc |= PROC_ON_CRIT_HIT_VICTIM;
					}break;

				case SPELL_DMG_TYPE_MAGIC:{
						aproc |= PROC_ON_SPELL_CRIT_HIT;
						vproc |= PROC_ON_SPELL_CRIT_HIT_VICTIM;
					}break;
				}
			}
		}
	}
//==========================================================================================
//==============================Post Roll Calculations======================================
//==========================================================================================
//------------------------------absorption--------------------------------------------------	
	uint32 ress=(uint32)res;
	if( pct_mod > 0 )
		ress = ress * pct_mod / 100;	//this comes from spells with chained targetting that loose PCT as they jump
	int32 abs_dmg = pVictim->AbsorbDamage(school, &ress);
	uint32 ms_abs_dmg= pVictim->ManaShieldAbsorb(ress);
	if (ms_abs_dmg)
	{
		if(ms_abs_dmg > ress)
			ress = 0;
		else
			ress-=ms_abs_dmg;

		abs_dmg += ms_abs_dmg;
	}

	if(ress < 0) 
		ress = 0;

	res=(float)ress;
	dealdamage dmg;
	dmg.school_type = school;
	dmg.full_damage = ress;
	dmg.resisted_damage = 0;
	
	if(res <= 0) 
		dmg.resisted_damage = dmg.full_damage;

	//------------------------------resistance reducing-----------------------------------------	
	if(res > 0 && this->IsUnit())
	{
		SafeUnitCast(this)->CalculateResistanceReduction(pVictim,&dmg,spellInfo);
		if((int32)dmg.resisted_damage > dmg.full_damage)
			res = 0;
		else
			res = float(dmg.full_damage - dmg.resisted_damage);
	}
	//------------------------------special states----------------------------------------------
	if(pVictim->bInvincible == true)
	{
		res = float(dmg.full_damage);
		dmg.resisted_damage = dmg.full_damage;
	}

	// Paladin: Blessing of Sacrifice, and Warlock: Soul Link
	if( pVictim->m_damageSplitTarget)
	{
		res = (float)pVictim->DoDamageSplitTarget((uint32)res, school, false);
	}
	
//==========================================================================================
//==============================Data Sending ProcHandling===================================
//==========================================================================================
	if( this->IsUnit() && allowProc && spellInfo->Id != 25501 && spellInfo->noproc == false)
	{
		int32 tdmg = float2int32(res);
		int32 last_minute_resist;

		last_minute_resist = pVictim->HandleProc( vproc, SafeUnitCast( this ), spellInfo, tdmg, (abs_dmg + dmg.resisted_damage) );
		SafeUnitCast( this )->HandleProc( aproc, pVictim, spellInfo, tdmg, (abs_dmg + dmg.resisted_damage) );

		//due to some procs dmg may change
		dmg.resisted_damage += last_minute_resist;
		res -= last_minute_resist;
		//avoid negative dmg !
		if( res < 0 )
			res = 0;
	}

	uint32 ID_for_the_logs ;
	if( spellInfo->spell_id_client )
		ID_for_the_logs = spellInfo->spell_id_client;
	else
		ID_for_the_logs = spellInfo->Id;
	if( DOTticks > 1 )
		SendSpellPeriodicAuraLog(this, pVictim, ID_for_the_logs, school, float2int32(res), abs_dmg, dmg.resisted_damage, FLAG_PERIODIC_DAMAGE, critical);
	else
		SendSpellNonMeleeDamageLog(this, pVictim, ID_for_the_logs, float2int32(res), school, abs_dmg, dmg.resisted_damage, false, 0, critical, IsPlayer());
	DealDamage( pVictim, float2int32( res ), 2, 0, spellID );

	if( !(dmg.full_damage == 0 && abs_dmg) && DOTticks <= 1 )
	{
		//Only pushback the victim current spell if it's not fully absorbed
		if( pVictim->GetCurrentSpell() )
			pVictim->GetCurrentSpell()->AddTime( school );
	}

//==========================================================================================
//==============================Post Damage Processing======================================
//==========================================================================================
	if( (int32)dmg.resisted_damage == dmg.full_damage && !abs_dmg )
	{
		//Magic Absorption
		if( pVictim->IsPlayer() )
		{
			if( SafePlayerCast( pVictim )->m_RegenManaOnSpellResist )
			{
				Player* pl = SafePlayerCast( pVictim );
				uint32 maxmana = pl->GetUInt32Value( UNIT_FIELD_MAXPOWER1 );

				//TODO: wtf is this ugly mess of casting bullshit
				uint32 amount = uint32(float( float(maxmana)*pl->m_RegenManaOnSpellResist));

				pVictim->Energize( pVictim, 29442, amount, POWER_TYPE_MANA );
			}
			// we still stay in combat dude
			SafePlayerCast(pVictim)->CombatStatusHandler_ResetPvPTimeout();
		}
		if( IsPlayer() )
			SafePlayerCast(this)->CombatStatusHandler_ResetPvPTimeout();
	}
	//zack : learn to never use hackfixes if possible 
	if( school == SHADOW_DAMAGE )
	{
		if( pVictim->isAlive() && this->IsUnit() )
		{
			//Shadow Word:Death
			if( spellID == 32379 || spellID == 32996 || spellID == 48157 || spellID == 48158 ) 
			{
				uint32 damage = (uint32)( res + abs_dmg );
				uint32 absorbed = SafeUnitCast( this )->AbsorbDamage( school, &damage );
				DealDamage( SafeUnitCast( this ), damage, 2, 0, spellID );
				SendSpellNonMeleeDamageLog( this, this, spellID, damage, school, absorbed, 0, false, 0, false, this->IsPlayer() );
			}
		}
	}/**/
}

void Object::SpellNonMeleeDamageLog(Unit *pVictim, uint32 SpellId, uint32 damage, bool allowProc, bool static_damage, bool no_remove_auras,uint32 DOTticks)
{
	SpellEntry *spellInfo = dbcSpell.LookupEntryForced( SpellId );
	if( spellInfo )
		SpellNonMeleeDamageLog( pVictim, spellInfo, damage, allowProc, static_damage, no_remove_auras, DOTticks );
}

//*****************************************************************************************
//* SpellLog packets just to keep the code cleaner and better to read
//*****************************************************************************************

void Object::SendSpellLog(Object *Caster, Object *Target,uint32 Ability, uint8 SpellLogType)
{
	if ( ( ( !Caster || !Target	) && Ability ) )
		return;

/*
1C A7 00 00 
68 00 00 99 5D 00 30 F1 
01 
01 00 00 00 
69 00 00 99 5D 00 30 F1 
03 - dodge
70 1C DE 40 
00 00 00 00

3B D0 00 00 
01 6F 54 01 00 00 00 00 
00 - it's 0 and not 1 as we suspect it to be. Maybe it signals packet extension ?
01 00 00 00
49 0F 00 F1 76 00 30 F1 
02 - resist
*/
	sStackWolrdPacket( data, SMSG_SPELLLOGMISS, 60 );
	data << Ability;										// spellid
	data << Caster->GetGUID();							  // caster / player
	if( SpellLogType == SPELL_LOG_RESIST )
		data << (uint8)0;									   // unknown but I think they are const
	else
		data << (uint8)1;									   // unknown but I think they are const
	data << (uint32)1;									  // unknown but I think they are const
	data << Target->GetGUID();							  // target
	data << SpellLogType;								   // spelllogtype
#ifdef MINIMIZE_NETWORK_TRAFIC
	SendMessageToDuel( &data );
#else
	Caster->SendMessageToSet(&data, true);
#endif
}

void Object::SendSpellPeriodicAuraLog(Object* Caster, Unit * Target, uint32 SpellID, uint32 School, uint32 Amount, uint32 abs_dmg, uint32 resisted_damage, uint32 Flags, uint8 crit)
{
	if ((!Caster || !Target) && SpellID)
	{ 
		return;
	}

	sStackWolrdPacket( data, SMSG_PERIODICAURALOG, 150);
	data << Target->GetNewGUID();		   // target guid
	data << Caster->GetNewGUID();
	data << SpellID;						// spellid
	data << (uint32)1;						// 1 simple cast, 2 channeled
	data << uint32(Flags | 0x1);			// aura = 1, type of action, 15 for mana regen ?
	data << Amount;							// amount of done to target / heal / damage
	data << uint32(Target->GetOverkill(Amount));
	data << g_spellSchoolConversionTable[School];
	data << uint32(abs_dmg);
	data << uint32(resisted_damage);
	data << crit;

#ifdef MINIMIZE_NETWORK_TRAFIC
	SendMessageToDuel( &data );
#else
	Caster->SendMessageToSet(&data, true);
#endif
}

void Object::SendSpellNonMeleeDamageLog( Object* Caster, Object* Target, uint32 SpellID, uint32 Damage, uint8 School, uint32 AbsorbedDamage, uint32 ResistedDamage, bool PhysicalDamage, uint32 BlockedDamage, bool CriticalHit, bool bToset )
{
	if ((!Caster || !Target) && SpellID)
	{ 
		return;
	}

	sStackWolrdPacket( data, SMSG_SPELLNONMELEEDAMAGELOG, 150);
	data << Target->GetNewGUID();
	data << Caster->GetNewGUID();
	data << SpellID;                    // SpellID / AbilityID
	data << Damage;                     // All Damage
	if( Target->IsUnit() )
		data << uint32(SafeUnitCast(Target)->GetOverkill(Damage));
	else
		data << uint32(0);
	data << uint8(g_spellSchoolConversionTable[School]);                     // School
	data << AbsorbedDamage;             // Absorbed Damage
	data << ResistedDamage;             // Resisted Damage
	data << uint8(PhysicalDamage);      // Physical Damage (true/false)
	data << uint8(0);                   // unknown or it binds with Physical Damage
	data << BlockedDamage;		     // Physical Damage (true/false)
	data << uint8(CriticalHit ? 7 : 5);                   // unknown const
	data << uint32(0);

#ifdef MINIMIZE_NETWORK_TRAFIC
	SendMessageToDuel( &data );
#else
	Caster->SendMessageToSet( &data, bToset );
#endif
}

void Object::SendAttackerStateUpdate( Object* Caster, Object* Target, dealdamage *Dmg, uint32 Damage, uint32 Abs, uint32 BlockedDamage, uint32 HitStatus, uint32 VState )
{
	if (!Caster || !Target || !Dmg)
	{ 
		return;
	}

	sStackWolrdPacket( data ,SMSG_ATTACKERSTATEUPDATE, 250 );
	//0x4--dualwield,0x10 miss,0x20 absorbed,0x80 crit,0x4000 -glancing,0x8000-crushing
	//only for melee!

	data << (uint32)HitStatus;   
	data << Caster->GetNewGUID();
	data << Target->GetNewGUID();
		
	data << (uint32)Damage;				// Realdamage;
//	data << (uint32)Abs;				// Damage absorbed
//	data << (uint32)Dmg->resisted_damage;	// Damage resisted
	if( this->IsUnit() )
		data << (uint32)(SafeUnitCast(this)->GetOverkill(Damage));	// Damage resisted
	else
		data << uint32(0);
	data << (uint8)1;					// Damage type counter / swing type

	data << (uint32)g_spellSchoolConversionTable[Dmg->school_type];				  // Damage school
	data << (float)Dmg->full_damage;	// Damage float
	data << (uint32)Dmg->full_damage;	// Damage amount

	if( HitStatus & HITSTATUS_ABSORBED )
		data << uint32( Abs );				// Damage absorbed

	if( HitStatus & HITSTATUS_RESIST )
		data << uint32( Dmg->resisted_damage );	// Damage resisted

	data << uint8( VState );
	data << uint32( 0 );				// can be 0,1000 or -1
	data << uint32( 0 );

	if( HitStatus & HITSTATUS_BLOCK )
		data << uint32( BlockedDamage );		// Damage amount blocked


	if ( HitStatus & HITSTATUS_UNK2 )
		data << uint32( 0 );				// unknown

	if( HitStatus & HITSTATUS_UNK )
	{
		data << uint32( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );
		data << float( 0 );

		data << float( 0 ); // Found in loop
		data << float( 0 );	// Found in loop
		data << uint32( 0 );
	}

	SendMessageToSet(&data, Caster->IsPlayer());
}

int32 Object::event_GetInstanceID()
{
	// return -1 for non-inworld.. so we get our shit moved to the right thread
	if(!IsInWorld())
	{ 
		return WORLD_INSTANCE;
	}
	else
		return m_instanceId;
}

void Object::EventSpellDamage(uint64 Victim, uint32 SpellID, uint32 Damage)
{
	if(!IsInWorld())
	{ 
		return;
	}

	Unit * pUnit = GetMapMgr()->GetUnit(Victim);
	if(pUnit == 0) 
	{ 
		return;
	}

	SpellNonMeleeDamageLog(pUnit, SpellID, Damage, true);
}

bool Object::CanActivate()
{
	switch(m_objectTypeId)
	{
	case TYPEID_UNIT:
		{
			if(!IsPet())
			{ 
				return true;
			}
		}break;

	case TYPEID_GAMEOBJECT:
		{
			if(SafeGOCast(this)->HasAI() && GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPEID) != GAMEOBJECT_TYPE_TRAP)
			{ 
				return true;
			}
		}break;
	}

	return false;
}

void Object::Activate(MapMgr * mgr)
{
	switch(m_objectTypeId)
	{
	case TYPEID_UNIT:
		mgr->activeCreatures.insert(SafeCreatureCast(this));
		break;

	case TYPEID_GAMEOBJECT:
		mgr->activeGameObjects.insert(SafeGOCast(this));
		break;
	}

	Active = true;
}

void Object::Deactivate(MapMgr * mgr)
{
	//very experimental -> static objects set by scripts that always get updated even if the cell beneath them is not active anymore !
	//might crah like hell
	if( static_object == true )
		return;

	switch(m_objectTypeId)
	{
	case TYPEID_UNIT:
		// check iterator
		if(mgr->activeCreaturesItr != mgr->activeCreatures.end() && (*mgr->activeCreaturesItr) == SafeCreatureCast(this))
			++mgr->activeCreaturesItr;
		mgr->activeCreatures.erase(SafeCreatureCast(this));
		break;

	case TYPEID_GAMEOBJECT:
		mgr->activeGameObjects.erase(SafeGOCast(this));
		break;
	}
	Active = false;
}

void Object::SetByte(uint32 index, uint32 index1,uint8 value)
{
	ASSERT( index < m_valuesCount );
	// save updating when val isn't changing.
	#ifndef USING_BIG_ENDIAN
	uint8 * v =&((uint8*)m_uint32Values)[index*4+index1];
	#else
	uint8 * v = &((uint8*)m_uint32Values)[index*4+(3-index1)];
	#endif
	if(*v == value)
	{ 
		return;
	}

	*v = value;

	if(IsInWorld())
	{
		m_updateMask.SetBit( index );

		if(!m_objectUpdated)
		{
			m_mapMgr->ObjectUpdated(this);
			m_objectUpdated = true;
		}
	}

}

void Object::SetZoneId(uint32 newZone)
{
	m_zoneId = newZone;
	if( m_objectTypeId == TYPEID_PLAYER && SafePlayerCast( this )->GetGroup() )
		SafePlayerCast( this )->GetGroup()->HandlePartialChange( GROUP_UPDATE_FLAG_ZONEID, SafePlayerCast( this ) );
}

void Object::PlaySoundToSet(uint32 sound_entry)
{
	WorldPacket data(SMSG_PLAY_SOUND, 4);
	data << sound_entry;
	SendMessageToSet(&data, true);
}

void Object::PlaySoundTarget(uint32 sound_entry, uint64 &guid)
{
	WorldPacket data(SMSG_PLAY_OBJECT_SOUND, 16);
	data << sound_entry << guid;
	SendMessageToSet(&data, true);
}

bool Object::IsInBg()
{
	MapInfo *pMapinfo = WorldMapInfoStorage.LookupEntry(this->GetMapId());
	if(pMapinfo)
	{
		return (pMapinfo->type_flags == INSTANCE_FLAG_PVP);
	}

	return false;
}

uint32 Object::GetTeam()
{
	if (IsPlayer())
	{
		return SafePlayerCast( this )->GetTeam();
	}
	if (IsPet())
	{
		if (SafePetCast( this )->GetPetOwner() != NULL)
		{
			return SafePetCast( this )->GetPetOwner()->GetTeam();
		}
	}
	if ( IsCreature() && SafeCreatureCast( this )->IsTotem() )
	{
		if (SafeCreatureCast( this )->GetTotemOwner() != NULL)
		{
			return SafeCreatureCast( this )->GetTotemOwner()->GetTeam();
		}
	}

	return (uint32)(-1);
}

void Object::SetSpawnPosition(const LocationVector & v)
{
	SetSpawnPosition(v.x, v.y, v.z, v.o);
}
 
void Object::SetSpawnPosition(float newX, float newY, float newZ, float newOrientation)
{
	m_spawnLocation.x=newX;
	m_spawnLocation.y=newY;
	m_spawnLocation.z=newZ;
}

//Manipulates the phase value, see "enum PHASECOMMANDS" in Object.h for a longer explanation!
void Object::Phase(uint8 command, uint32 newphase)
{
	switch( command )
	{
	case PHASE_SET:
		m_phase = newphase;
		break;
	case PHASE_ADD:
		m_phase |= newphase;
		break;
	case PHASE_DEL:
		m_phase &= ~newphase;
		break;
	case PHASE_RESET:
		m_phase = 1;
		break;
	default:
		return;
	}

/*	if ( IsPlayer() ) 
	{
		Player * p_player=SafePlayerCast( this );
		std::list<Pet*> summons = p_player->GetSummons();
		for(std::list<Pet*>::iterator itr = summons.begin(); itr != summons.end(); ++itr)
		{
			(*itr)->Phase(command, newphase);
		}
		//We should phase other, non-combat "pets" too...
	}*/

	for( std::set<Object*>::iterator itr=m_objectsInRange.begin(); itr!=m_objectsInRange.end(); ++itr )
	{
		if ( (*itr)->IsUnit() )
		{
			if( (*itr)->GetUInt64Value( UNIT_FIELD_CREATEDBY ) == this->GetUInt64Value( OBJECT_FIELD_GUID ) )
				(*itr)->Phase(command, newphase);
			SafeUnitCast( *itr )->UpdateVisibility();
		}
	}

	if ( IsUnit() )
		SafeUnitCast( this )->UpdateVisibility();

	return;
}

ARCEMU_INLINE uint32 Object::GetAreaID()
{
	return sTerrainMgr.GetAreaID( GetMapId(), GetPositionX(), GetPositionY(), GetPositionZ() );
}
