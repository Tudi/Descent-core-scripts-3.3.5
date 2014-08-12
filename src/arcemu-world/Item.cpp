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

Item::Item()//this is called when constructing as container
{
	m_bufferPoolId = OBJECT_WAS_ALLOCATED_STANDARD_WAY;
	m_itemProto = NULL;
	m_owner = NULL;
	loot = NULL;
	locked = false;
	wrapped_item_id = 0;
	m_objectTypeId = TYPEID_ITEM;
	internal_object_type = INTERNAL_OBJECT_TYPE_ITEM;
	m_valuesCount = ITEM_END;
	m_uint32Values = _fields;
	m_updateMask.SetCount(ITEM_END);
	random_prop = 0;
	random_suffix = 0;
	mSemaphoreTeleport = false;
	m_faction = NULL;
	m_factionDBC = NULL;
	m_instanceId = WORLD_INSTANCE;
	Active = false;
	m_inQueue = false;
//	m_extensions = NULL;
	m_loadedFromDB = false;

	Enchantments.clear();
}

//called instead of parametrized constructor
void Item::Init( uint32 high, uint32 low )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	SetUInt32Value( OBJECT_FIELD_GUID, low );
	SetUInt32Value( OBJECT_FIELD_GUID + 1, high );
	m_wowGuid.Init( GetGUID() );
}

void Item::Virtual_Constructor()
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	memset( m_uint32Values, 0, (ITEM_END) * sizeof( uint32 ) );
	SetUInt32Value( OBJECT_FIELD_TYPE,TYPE_ITEM | TYPE_OBJECT );
	SetFloatValue( OBJECT_FIELD_SCALE_X, 1 );//always 1
	SetFloatValue( OBJECT_FIELD_SCALE_X, 1 );//always 1
	m_itemProto = NULL;
	m_owner = NULL;
	loot = NULL;
	locked = false;
	m_isDirty = true;
	random_prop = 0;
	random_suffix = 0;
	wrapped_item_id = 0;

	m_mapId = 0;
	m_zoneId = 0;
	m_objectUpdated = false;

	mSemaphoreTeleport = false;
	m_faction = NULL;
	m_factionDBC = NULL;
	m_instanceId = WORLD_INSTANCE;
	Active = false;
	m_inQueue = false;
//	m_extensions = NULL;
	m_loadedFromDB = false;
	EventableObject::Virtual_Constructor();	//clear out event holder. There is a bug that if player logoud out in an instance and item was attached to it then item get invalid pointer to a holder
}

Item::~Item()
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	if( m_bufferPoolId != OBJECT_WAS_ALLOCATED_STANDARD_WAY )
		ASSERT( false ); //we are deleting a pooled object. This leads to mem corruptions
	if( loot != NULL )
	{
		delete loot;
		loot = NULL;
	}

	sEventMgr.RemoveEvents( this );

	EnchantmentMap::iterator itr;
	for( itr = Enchantments.begin(); itr != Enchantments.end(); ++itr )
	{
		delete itr->second;
		itr->second = NULL;
	}
	Enchantments.clear();

	if( IsInWorld() )
		RemoveFromWorld();

	m_owner = NULL;

	//avoid Unit destructor referencing to this object ass item after creature destructor call
	//if object destructor will acces player fields after destructor it could create memcorruptions
	m_objectTypeId = TYPEID_UNUSED;
	internal_object_type = INTERNAL_OBJECT_TYPE_NONE;
}

void Item::Virtual_Destructor()
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	if( loot != NULL )
	{
		delete loot;
		loot = NULL;
	}

	sEventMgr.RemoveEvents( this );

	EnchantmentMap::iterator itr;
	for( itr = Enchantments.begin(); itr != Enchantments.end(); ++itr )
	{
		delete itr->second;
		itr->second = NULL;
	}
	Enchantments.clear();

	//don't want to keep context ....
	//it makes a big difference where we mark Events deleted !
	EventableObject::Virtual_Destructor();

	if( IsInWorld() )
		RemoveFromWorld();

	m_owner = NULL;
	enchant_spell_book.clear();
}

void Item::Create( uint32 itemid, Player* owner )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	SetUInt32Value( OBJECT_FIELD_ENTRY, itemid );
 
	if( owner != NULL )
	{
		SetUInt64Value( ITEM_FIELD_OWNER, owner->GetGUID() );
		SetUInt64Value( ITEM_FIELD_CONTAINED, owner->GetGUID() );
	}

	SetUInt32Value( ITEM_FIELD_STACK_COUNT, 1 );

	m_itemProto = ItemPrototypeStorage.LookupEntry( itemid );

	ASSERT( m_itemProto );
	 
	SetUInt32Value( ITEM_FIELD_SPELL_CHARGES, m_itemProto->Spells[0].Charges );
	SetUInt32Value( ITEM_FIELD_SPELL_CHARGES_1, m_itemProto->Spells[1].Charges );
	SetUInt32Value( ITEM_FIELD_SPELL_CHARGES_2, m_itemProto->Spells[2].Charges );
	SetUInt32Value( ITEM_FIELD_SPELL_CHARGES_3, m_itemProto->Spells[3].Charges );
	SetUInt32Value( ITEM_FIELD_SPELL_CHARGES_4, m_itemProto->Spells[4].Charges );
	SetUInt32Value( ITEM_FIELD_MAXDURABILITY, m_itemProto->MaxDurability );
	SetUInt32Value( ITEM_FIELD_DURABILITY, m_itemProto->MaxDurability );

	m_owner = owner;
	if( m_itemProto->LockId > 1 )
		locked = true;
	else
		locked = false;
}

void Item::LoadFromDB(Field* fields, Player* plr, bool light )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	uint32 itemid = fields[2].GetUInt32();
	uint32 random_prop, random_suffix;
	m_itemProto = ItemPrototypeStorage.LookupEntry( itemid );

	ASSERT( m_itemProto );
	
	if(m_itemProto->LockId > 1)
		locked = true;
	else
		locked = false;
	
	SetUInt32Value( OBJECT_FIELD_ENTRY, itemid );
	m_owner = plr;

	wrapped_item_id=fields[3].GetUInt32();
	m_uint32Values[ITEM_FIELD_GIFTCREATOR] = fields[4].GetUInt32();
	m_uint32Values[ITEM_FIELD_CREATOR] = fields[5].GetUInt32();

	int32 count = fields[6].GetUInt32();
	if ( count > (int32)m_itemProto->MaxCount )
		count = m_itemProto->MaxCount;
	SetUInt32Value( ITEM_FIELD_STACK_COUNT,  count );

	// Again another for that did not indent to make it do anything for more than 
	// one iteration x == 0 was the only one executed
	for( uint32 x = 0; x < 5; x++ )
	{
		if( m_itemProto->Spells[x].Id )
		{
			SetUInt32Value( ITEM_FIELD_SPELL_CHARGES + x , fields[7].GetUInt32() );
			break;
		}
	}

	SetUInt32Value( ITEM_FIELD_FLAGS, fields[8].GetUInt32() );
	random_prop = fields[9].GetUInt32();
	random_suffix = fields[10].GetUInt32();

	SetRandomProperty( random_prop );
	SetRandomSuffix( random_suffix );

	int32 rprop = int32( random_prop );
	// If random properties point is negative that means the item uses random suffix as random enchantment
//	if( rprop < 0 )
//		SetRandomSuffix( random_suffix );
//	else
//		SetRandomSuffix( 0 );

//	SetUInt32Value( ITEM_FIELD_ITEM_TEXT_ID, fields[11].GetUInt32() );

	SetUInt32Value( ITEM_FIELD_MAXDURABILITY, m_itemProto->MaxDurability );
	SetUInt32Value( ITEM_FIELD_DURABILITY, fields[11].GetUInt32() );

	if( light )
	{ 
		return;
	}

	string enchant_field = fields[14].GetString();
	vector< string > enchants = StrSplit( enchant_field, ";" );
	uint32 enchant_id;
	EnchantEntry* entry;
	uint32 time_left;
	uint32 enchslot;

	for( vector<string>::iterator itr = enchants.begin(); itr != enchants.end(); ++itr )
	{
		if( sscanf( (*itr).c_str(), "%u,%u,%u", (unsigned int*)&enchant_id, (unsigned int*)&time_left, (unsigned int*)&enchslot) == 3 )
		{
			entry = dbcEnchant.LookupEntry( enchant_id );
			if( entry && entry->Id == enchant_id && m_itemProto->SubClass != ITEM_SUBCLASS_WEAPON_THROWN)
			{
				AddEnchantment( entry, time_left, ( time_left == 0 ), false, false, enchslot );
				//(enchslot != 2) ? false : true, false);
			}
			else
			{
				/*
				EnchantEntry *pEnchant = new EnchantEntry;
				memset(pEnchant,0,sizeof(EnchantEntry));

				pEnchant->Id = enchant_id;
				if(enchslot != 2)
					AddEnchantment(pEnchant,0,true, false);
				else
					AddEnchantment(pEnchant,0,false,false);
				*/
			}
		}
	}	

	ApplyRandomProperties( false );

	// Charter stuff
	if(m_uint32Values[OBJECT_FIELD_ENTRY] == ITEM_ENTRY_GUILD_CHARTER)
	{
		SetUInt32Value( ITEM_FIELD_FLAGS, 1 );
		SetUInt32Value( ITEM_FIELD_STACK_COUNT, 1 );
		SetUInt32Value( ITEM_FIELD_PROPERTY_SEED, 57813883 );
		if( plr && plr->m_charters[CHARTER_TYPE_GUILD] )
			SetUInt32Value( ITEM_FIELD_ENCHANTMENT_1_1 , plr->m_charters[CHARTER_TYPE_GUILD]->GetID() );
	}

	if( m_uint32Values[OBJECT_FIELD_ENTRY] == ARENA_TEAM_CHARTER_2v2 )
	{
		SetUInt32Value( ITEM_FIELD_FLAGS, 1 );
		SetUInt32Value( ITEM_FIELD_STACK_COUNT, 1 );
		SetUInt32Value( ITEM_FIELD_PROPERTY_SEED, 57813883 );
		if( plr && plr->m_charters[CHARTER_TYPE_ARENA_2V2] )
			SetUInt32Value( ITEM_FIELD_ENCHANTMENT_1_1 , plr->m_charters[CHARTER_TYPE_ARENA_2V2]->GetID() );
	}

	if( m_uint32Values[OBJECT_FIELD_ENTRY] == ARENA_TEAM_CHARTER_3v3 )
	{
		SetUInt32Value( ITEM_FIELD_FLAGS, 1 );
		SetUInt32Value( ITEM_FIELD_STACK_COUNT, 1 );
		SetUInt32Value( ITEM_FIELD_PROPERTY_SEED, 57813883 );
		if( plr && plr->m_charters[CHARTER_TYPE_ARENA_3V3] )
			SetUInt32Value( ITEM_FIELD_ENCHANTMENT_1_1 , plr->m_charters[CHARTER_TYPE_ARENA_3V3]->GetID() );
	}

	if( m_uint32Values[OBJECT_FIELD_ENTRY] == ARENA_TEAM_CHARTER_5v5 )
	{
		SetUInt32Value( ITEM_FIELD_FLAGS, 1 );
		SetUInt32Value( ITEM_FIELD_STACK_COUNT, 1 );
		SetUInt32Value( ITEM_FIELD_PROPERTY_SEED, 57813883 );
		if( plr && plr->m_charters[CHARTER_TYPE_ARENA_5V5] )
			SetUInt32Value( ITEM_FIELD_ENCHANTMENT_1_1 , plr->m_charters[CHARTER_TYPE_ARENA_5V5]->GetID() );
	}
}

void Item::ApplyRandomProperties( bool apply )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	// apply random properties
	if( m_uint32Values[ITEM_FIELD_RANDOM_PROPERTIES_ID] != 0 )
	{
		if( int32( m_uint32Values[ITEM_FIELD_RANDOM_PROPERTIES_ID] ) > 0 )		// Random Property
		{
			RandomProps* rp= dbcRandomProps.LookupEntry( m_uint32Values[ITEM_FIELD_RANDOM_PROPERTIES_ID] );
			int32 Slot;
			for( int k = 0; k < 3; k++ )
			{
				if( rp->spells[k] != 0 )
				{	
					EnchantEntry* ee = dbcEnchant.LookupEntry( rp->spells[k] );
					Slot = HasEnchantment( ee->Id );
					if( Slot < 0 ) 
					{
						Slot = FindFreeEnchantSlot( ee, 1 );
						AddEnchantment( ee, 0, false, apply, true, Slot );
					}
					else
						if( apply )
							ApplyEnchantmentBonus( Slot, true );
				}
			}
		}
		else
		{
			ItemRandomSuffixEntry* rs = dbcItemRandomSuffix.LookupEntry( abs( int( m_uint32Values[ITEM_FIELD_RANDOM_PROPERTIES_ID] ) ) );
			int32 Slot;
			for( uint32 k = 0; k < 3; ++k )
			{
				if( rs->enchantments[k] != 0 )
				{
					EnchantEntry* ee = dbcEnchant.LookupEntry( rs->enchantments[k] );
					Slot = HasEnchantment( ee->Id );
					if( Slot < 0 ) 
					{
						Slot = FindFreeEnchantSlot( ee, 2 );
						AddEnchantment( ee, 0, false, apply, true, Slot, rs->prefixes[k] );
					}
					else
						if( apply )
							ApplyEnchantmentBonus( Slot, true );
				}
			}
		}
	}
}

void Item::SaveToDB( int16 containerslot, int16 slot, bool firstsave, QueryBuffer* buf )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	if( !m_isDirty && !firstsave )
	{ 
		return;
	}

	std::stringstream ss;

	ss << "REPLACE INTO playeritems VALUES(";

	ss << m_uint32Values[ITEM_FIELD_OWNER] << ",";
    ss << m_uint32Values[OBJECT_FIELD_GUID] << ",";
	ss << m_uint32Values[OBJECT_FIELD_ENTRY] << ",";
	ss << wrapped_item_id << ",";
	ss << m_uint32Values[ITEM_FIELD_GIFTCREATOR] << ",";
	ss << m_uint32Values[ITEM_FIELD_CREATOR] << ",";

	ss << GetUInt32Value(ITEM_FIELD_STACK_COUNT) << ",";
	ss << GetChargesLeft() << ",";
	ss << GetUInt32Value(ITEM_FIELD_FLAGS) << ",";
	ss << random_prop << ", " << random_suffix << ", ";
//	ss << GetUInt32Value(ITEM_FIELD_ITEM_TEXT_ID) << ",";
	ss << GetUInt32Value(ITEM_FIELD_DURABILITY) << ",";
	ss << (int32)(containerslot) << ",";
	ss << (int32)(slot) << ",'";

	// Pack together enchantment fields
	if( Enchantments.size() > 0 )
	{
		EnchantmentMap::iterator itr = Enchantments.begin();
		for(; itr != Enchantments.end(); ++itr)
		{
			if( itr->second->RemoveAtLogout )
				continue;

			uint32 elapsed_duration = uint32( UNIXTIME - itr->second->ApplyTime );
			int32 remaining_duration = itr->second->Duration - elapsed_duration;
			if( remaining_duration < 0 )
				remaining_duration = 0;
		
			/*
			if( !itr->second.RemoveAtLogout && (remaining_duration > 5 && itr->second.Slot != 2) || itr->second.Slot == 2)  // no point saving stuff with < 5 seconds... unless is perm enchant
			{
				ss << itr->second.Enchantment->Id << ",";
				ss << remaining_duration << ",";
				ss << itr->second.Slot << ";";
			}
			*/
		  
			if( itr->second->Enchantment && ( remaining_duration && remaining_duration > 5 || itr->second->Duration == 0 ) )
			{
				ss << itr->second->Enchantment->Id << ",";
				ss << remaining_duration << ",";
				ss << itr->second->Slot << ";";
			}
		}
	}
	ss << "')";
	
	if( firstsave )
		CharacterDatabase.WaitExecute( ss.str().c_str() );
	else
	{
		if( buf == NULL )
			CharacterDatabase.Execute( ss.str().c_str() );
		else
			buf->AddQueryStr( ss.str() );
	}

	m_isDirty = false;
}

void Item::DeleteFromDB()
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	if( m_itemProto->ContainerSlots>0 && IsContainer() )
	{
		/* deleting a container */
		for( uint32 i = 0; i < m_itemProto->ContainerSlots; ++i )
		{
			if( SafeContainerCast( this )->GetItem( i ) != NULL )
			{
				/* abort the delete */
				return;
			}
		}
	}

	CharacterDatabase.Execute( "DELETE FROM playeritems WHERE guid = %u", m_uint32Values[OBJECT_FIELD_GUID] );
}

void Item::DeleteMe()
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	if( !IsItem() )
	{
		sLog.outDebug(" Item::DeleteMe : !!! omg invalid call on wrong object !\n");
		ASSERT(false);
		return;
	}
	//Don't inline me!
	if( IsContainer() )
	{
		INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
		delete SafeContainerCast(this);
	} 
	else 
	{
		ItemPool.PooledDelete( this );
	}
}

uint32 GetSkillByProto( uint32 Class, uint32 SubClass )
{
	if( Class == 4 && SubClass < 7 )
	{
		return arm_skills[SubClass];
	} 
    else if( Class == 2 )
	{
		if( SubClass < 20 )//no skill for fishing
		{
			return weap_skills[SubClass];
		}
	}
	return 0;
}

//This map is used for profess.
//Prof packe strcut: {SMSG_SET_PROFICIENCY,(uint8)item_class,(uint32)1<<item_subclass}
//ie: for fishing (it's class=2--weapon, subclass ==20 -- fishing rod) permissive packet
// will have structure 0x2,524288
//this table is needed to get class/subclass by skill, valid classes are 2 and 4

const ItemProf* GetProficiencyBySkill( uint32 skill )
{
	switch( skill )
	{
		case SKILL_CLOTH:
			return &prof[0];
		case SKILL_LEATHER:
			return &prof[1];
		case SKILL_MAIL:
			return &prof[2];
		case SKILL_PLATE_MAIL:
			return &prof[3];
		case SKILL_SHIELD:
			return &prof[4];
		case SKILL_AXES:
			return &prof[5];
		case SKILL_2H_AXES:
			return &prof[6];
		case SKILL_BOWS:
			return &prof[7];
		case SKILL_GUNS:
			return &prof[8];
		case SKILL_MACES:
			return &prof[9];
		case SKILL_2H_MACES:
			return &prof[10];
		case SKILL_POLEARMS:
			return &prof[11];
		case SKILL_SWORDS:
			return &prof[12];
		case SKILL_2H_SWORDS:
			return &prof[13];
		case SKILL_STAVES:
			return &prof[14];
		case SKILL_FIST_WEAPONS:
			return &prof[15];
		case SKILL_DAGGERS:
			return &prof[16];
		case SKILL_THROWN:
			return &prof[17];
//		case SKILL_SPEARS:
//			return &prof[18];
		case SKILL_CROSSBOWS:
			return &prof[19];
		case SKILL_WANDS:
			return &prof[20];
		case SKILL_FISHING:
			return &prof[21];
		default:
			return NULL;
	}
}

uint32 GetSellPriceForItem( ItemPrototype *proto, uint32 count )
{
	int32 cost;
	cost = proto->SellPrice * ( ( count < 1 ) ? 1 : count );
	return cost;
}

uint32 GetBuyPriceForItem( ItemPrototype* proto, uint32 count, Player* plr, Creature* vendor )
{
	int32 cost = proto->BuyPrice;

	if( plr != NULL && vendor != NULL )
	{
		Standing plrstanding = plr->GetStandingRank( vendor->m_faction->Faction );
		cost = float2int32( ceilf( float( proto->BuyPrice ) * pricemod[plrstanding] ) );
	}

	return cost * count;
}

uint32 GetSellPriceForItem( uint32 itemid, uint32 count )
{
	if( ItemPrototype* proto = ItemPrototypeStorage.LookupEntry( itemid ) )
	{ 
		return GetSellPriceForItem(proto, count);
	}
	else
		return 1;
}

uint32 GetBuyPriceForItem( uint32 itemid, uint32 count, Player* plr, Creature* vendor )
{
	if( ItemPrototype* proto = ItemPrototypeStorage.LookupEntry( itemid ) )
	{ 
		return GetBuyPriceForItem( proto, count, plr, vendor );
	}
	else
		return 1;
}

void Item::RemoveFromWorld()
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	// if we have an owner->send destroy
	if( m_owner != NULL )
	{
		DestroyForPlayer( m_owner );
	}

	if( !IsInWorld() )
	{ 
		return;
	}

	mSemaphoreTeleport = true;
	m_mapMgr->RemoveObject( this, false );
	m_mapMgr = NULL;
  
	// update our event holder
	event_Relocate();
}

void Item::SetOwner( Player* owner )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
 
	if( owner != NULL )
		SetUInt64Value( ITEM_FIELD_OWNER, owner->GetGUID() );
	else SetUInt64Value( ITEM_FIELD_OWNER, 0 );

	m_owner = owner; 
}


int32 Item::AddEnchantment( EnchantEntry* Enchantment, uint32 Duration, bool Perm /* = false */, bool apply /* = true */, bool RemoveAtLogout /* = false */, uint32 Slot_, uint32 RandomSuffix )
{
	int32 Slot = Slot_;
	m_isDirty = true;

/*
	if(Perm)
	{
		if(Slot_)
		{
			Slot=Slot_;
		}
		else
        {
			Slot = FindFreeEnchantSlot(Enchantment);
        }
	}
	else
	{
		if(Enchantment->EnchantGroups > 1) // replaceable temp enchants
		{
			Slot = 1;
			RemoveEnchantment(1);
		}
		else
		{
			Slot = FindFreeEnchantSlot(Enchantment);*/
			/*
			Slot = Enchantment->type ? 3 : 0;
			 //that's 's code
			for(uint32 Index = ITEM_FIELD_ENCHANTMENT_09; Index < ITEM_FIELD_ENCHANTMENT_32; Index += 3)
			{
				if(m_uint32Values[Index] == 0) break;;	
				++Slot;
			}

			//Slot = FindFreeEnchantSlot(Enchantment);
			// reach max of temp enchants
			if(Slot >= 11) return -1;
			*/
		/*}
	}   
*/

	//now why would this happen ?
	if( Slot >= (ITEM_FIELD_ENCHANTMENT_12_3-ITEM_FIELD_ENCHANTMENT_1_1)/3 )
		return Slot; //oh no, what about error codes ?

	//this should do nothing theoretically
	RemoveEnchantment( Slot );

	// Create the enchantment struct.
	EnchantmentInstance *Instance;
	Instance = new EnchantmentInstance;
	Instance->ApplyTime = UNIXTIME;
	Instance->BonusApplied = false;
	Instance->Slot = Slot;
	Instance->Enchantment = Enchantment;
	Instance->Duration = Duration;
	Instance->RemoveAtLogout = RemoveAtLogout;
	Instance->RandomSuffix = RandomSuffix;

	// Set the enchantment in the item fields.
	uint32 EnchantBase = Slot * 3 + ITEM_FIELD_ENCHANTMENT_1_1 ;
	SetUInt32Value( EnchantBase, Enchantment->Id );
	SetUInt32Value( EnchantBase + 1, (uint32)Instance->ApplyTime );
	SetUInt32Value( EnchantBase + 2, 0 ); // charges

	// Add it to our map.
	Enchantments[(uint32)Slot ] = Instance;

	if( m_owner == NULL )
	{ 
		return Slot;
	}

	// Add the removal event.
	if( Duration )
		sEventMgr.AddEvent( this, &Item::RemoveEnchantment, uint32(Slot), EVENT_REMOVE_ENCHANTMENT1 + Slot, Duration * 1000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );

	// No need to send the log packet, if the owner isn't in world (we're still loading)
	if( !m_owner->IsInWorld() )
	{
		return Slot;
	}

	if( apply )
	{
		WorldPacket EnchantLog( SMSG_ENCHANTMENTLOG, 25 );
		EnchantLog << m_owner->GetNewGUID();
		EnchantLog << m_owner->GetNewGUID();
		EnchantLog << m_uint32Values[OBJECT_FIELD_ENTRY];
		EnchantLog << Enchantment->Id;
		m_owner->GetSession()->SendPacket( &EnchantLog );

		if( m_owner->GetTradeTarget() )
			m_owner->SendTradeUpdate();
	
		/* Only apply the enchantment bonus if we're equipped */
		uint16 slot = m_owner->GetItemInterface()->GetInventorySlotByGuid( GetGUID() );
		if( slot >= EQUIPMENT_SLOT_START && slot < EQUIPMENT_SLOT_END )
            ApplyEnchantmentBonus( Slot, APPLY );
	}

	return Slot;
}

void Item::RemoveEnchantment( uint32 EnchantmentSlot )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	// Make sure we actually exist.
	EnchantmentMap::iterator itr = Enchantments.find( EnchantmentSlot );
	if( itr == Enchantments.end() )
	{ 
		return;
	}

	m_isDirty = true;
	uint32 Slot = itr->first;
	if( itr->second->BonusApplied )
		ApplyEnchantmentBonus( EnchantmentSlot, REMOVE );

	// Unset the item fields.
	uint32 EnchantBase = Slot * 3 + ITEM_FIELD_ENCHANTMENT_1_1 ;

	//never hurts to double check
	if( EnchantBase > ITEM_FIELD_ENCHANTMENT_12_3 )
	{ 
		return;
	}

	SetUInt32Value( EnchantBase + 0, 0 );
	SetUInt32Value( EnchantBase + 1, 0 );
	SetUInt32Value( EnchantBase + 2, 0 );

	// Remove the enchantment event for removal.
	event_RemoveEvents( EVENT_REMOVE_ENCHANTMENT1 + Slot );

	// delete the actual enchantment 
	delete itr->second;
	itr->second = NULL;	//just make sure it is not used anywhere else

	// Remove the enchantment instance.
	Enchantments.erase( itr );
}

//some gems can have effect applied only X times
uint32 Item::GetEnchantCountOfCustomGroup( uint32 custom_group )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	uint32 ret=0;
	EnchantmentMap::iterator itr, itr2;
	for( itr = Enchantments.begin(); itr != Enchantments.end();  )
	{
		itr2 = itr++;
		if( itr2->second->BonusApplied == false )
			continue; //now why is that ?
		if( itr2->second->Enchantment->custom_enchant_group == custom_group )
			ret++;
	}
	return ret;
}

void Item::ApplyEnchantmentBonus( uint32 Slot, bool Apply )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	if( m_owner == NULL 
		//this is exploit protection for enchanting broken items while equipped
		|| ( ( GetUInt32Value( ITEM_FIELD_DURABILITY ) == 0 && GetUInt32Value( ITEM_FIELD_MAXDURABILITY ) != 0 )
				&& Apply == true )	//we should be able to remove enchant when item "just broke down"
		)
	{ 
		return;
	}

	EnchantmentMap::iterator itr = Enchantments.find( Slot );
	if( itr == Enchantments.end() )
	{ 
		return;
	}

	if( itr->second->BonusApplied == Apply )
	{ 
		return;
	}

	EnchantEntry* Entry = itr->second->Enchantment;
	uint32 RandomSuffixAmount = itr->second->RandomSuffix;
	if( Apply )
	{
		if( Entry->required_skill && GetOwner() && GetOwner()->_GetSkillLineCurrent(Entry->required_skill,true) < Entry->required_skill_rank )
		{
			if( Entry->Name )
			{
				if( GetProto()->Name1 )
					GetOwner()->BroadcastMessage("Could not apply enchantment %s from %s", Entry->Name, GetProto()->Name1);
				else
					GetOwner()->BroadcastMessage("Could not apply enchantment: %s", Entry->Name);
			}
			else
				GetOwner()->BroadcastMessage("Could not apply enchantment from item");
			return;
		}
		// check if we are allowed to add any more of this enchant type. First appeared at prismatic gems
		if( Entry->custom_enchant_group && Entry->custom_enchant_maxstack && GetOwner() && GetOwner()->GetItemInterface() )
		{
			uint32 cur_grouped_enchant_count = 0;
			//get each equipped item 
			ItemInterface *ii = GetOwner()->GetItemInterface();
			for(int i=EQUIPMENT_SLOT_START;i<EQUIPMENT_SLOT_END;i++)
			{
				//see how many enchants of this type the player has already applied from this item
				Item *it = ii->GetInventoryItem( i );
				if( it )
					cur_grouped_enchant_count += it->GetEnchantCountOfCustomGroup( Entry->custom_enchant_group );

				//check if there is still a chance to apply the enchantment after checking this item
				if( cur_grouped_enchant_count >= Entry->custom_enchant_maxstack )
				{
					if( GetOwner() )
					{
						if( Entry->Name )
						{
							if( GetProto()->Name1 )
								GetOwner()->BroadcastMessage("Could not apply enchantment %s from %s", Entry->Name, GetProto()->Name1);
							else
								GetOwner()->BroadcastMessage("Could not apply enchantment: %s", Entry->Name);
						}
						else
							GetOwner()->BroadcastMessage("Could not apply enchantment from item");
					}
					return;
				}
			}
		}
		// Send the enchantment time update packet.
		if( itr->second->Duration ) 
			SendEnchantTimeUpdate( itr->second->Slot, itr->second->Duration );
		//increase player gear score if possible
		if( GetOwner() )
			GetOwner()->item_enchant_level_sum += Entry->custom_GearScore;
	}
	else
	{
		//increase player gear score if possible
		if( GetOwner() && GetOwner()->item_enchant_level_sum >= Entry->custom_GearScore )
			GetOwner()->item_enchant_level_sum -= Entry->custom_GearScore;
	}

	itr->second->BonusApplied = Apply;

	// Apply the visual on the player.
	if( Slot == 0 )
	{
		uint32 ItemSlot = m_owner->GetItemInterface()->GetInventorySlotByGuid( GetGUID() ) * (PLAYER_VISIBLE_ITEM_2_ENTRYID - PLAYER_VISIBLE_ITEM_1_ENTRYID);
		uint32 VisibleBase = PLAYER_VISIBLE_ITEM_1_ENTRYID + ItemSlot;
		m_owner->SetUInt32Value( VisibleBase + 1 + Slot, Apply ? Entry->Id : 0 );
	}

	// Another one of those for loop that where not indented properly god knows what will break
	// but i made it actually affect the code below it
	for( uint32 c = 0; c < 3; c++ )
	{
		if( Entry->type[c] )
		{
			// Depending on the enchantment type, take the appropriate course of action.
			switch( Entry->type[c] )
			{
			case SPELL_ENCHANT_TYPE_ADD_SPELL:
				{
					//this spell will be added to item and clietn will let player trigger it when he wants it
					if( Entry->spell[c] != 0 )
					{
						if( Apply )
							AddTemporalSpellBookSpell( Entry->spell[c] );
						else
							RemoveTemporalSpellBookSpell( Entry->spell[c] );
					}

				}break;
			case SPELL_ENCHANT_TYPE_TRIGGER_SPELL_ON_MELEE_HIT:		 // Trigger spell on melee attack.
				{
					if( Apply && Entry->spell[c] != 0 )
					{
						// Create a proc trigger spell
						SpellEntry* sp = dbcSpell.LookupEntryForced( Entry->spell[c] );
						if( !sp )
							continue;
						ProcTriggerSpell *TS = new ProcTriggerSpell(sp);
						TS->caster = m_owner->GetGUID();
						TS->origId = 0;
						TS->procFlags = PROC_ON_MELEE_ATTACK;
						TS->procCharges = 0;
						/* This needs to be modified based on the attack speed of the weapon.
						 * Secondly, need to assign some static chance for instant attacks (ss,
						 * gouge, etc.) */
						if( Entry->min[c] )
							TS->procChance = Entry->min[c];
						else if( TS->procChance == 0 )
							TS->procChance = 50;
						if( GetProto()->Class == ITEM_CLASS_WEAPON )
						{
							/////// procChance calc ///////
							float ppm = 0;
							switch( sp->NameHash )
							{
								case SPELL_HASH_FROSTBRAND_ATTACK:
									ppm = 9.0f;
								break;
								case SPELL_HASH_INSTANT_POISON:
									ppm = 8.53f;	//!!! can be moded by talent !
								break;
								case SPELL_HASH_WOUND_POISON:
									ppm = 21.43f;	//!!! can be moded by talent !
								break;
							}
							if( ppm != 0 )
								TS->procInterval = uint32(60000 / ppm);	
							else if( Entry->min[c] == 0 )
							{
								float speed = (float)GetProto()->Delay;
								TS->procChance = (uint32)( speed / 600.0f );
							}
							if( TS->procInterval < 500 )
								TS->procInterval = 500;	//someone reported that deathfrost hit 500 times a second. I have a feeling that was a different exploit
							///////////////////////////////
						}
						
						Log.Debug( "Enchant", "Setting procChance to %u%% with interval %u.", TS->procChance,TS->procInterval );
						TS->deleted = false;
						TS->spellId = Entry->spell[c];
						m_owner->m_procSpells.push_front( TS );
					}
					else
					{
						// Remove the proctriggerspell
						CommitPointerListNode<ProcTriggerSpell> *itr;
						for(itr = m_owner->m_procSpells.begin();itr != m_owner->m_procSpells.end();itr = itr->Next() )
							if( itr->data->spellId == Entry->spell[c] && itr->data->deleted == false && itr->data->caster == m_owner->GetGUID() )
							{
								itr->data->deleted = true;
								break; //all or 1 ?
							}
					}
				}break;

			case SPELL_ENCHANT_TYPE_MOD_DMG:		 // Mod damage done.
				{
					int32 val = Entry->min[c];
					if( RandomSuffixAmount )
						val = RANDOM_SUFFIX_MAGIC_CALCULATION( RandomSuffixAmount, GetItemRandomSuffixFactor() );

//					if( m_owner->getClass() == DEATHKNIGHT )
//						continue;

					if( Apply )
						m_owner->ModUnsigned32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS, val );
					else
						m_owner->ModUnsigned32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS, -val );
					m_owner->CalcDamage();
				}break;

			case SPELL_ENCHANT_TYPE_CAST_SPELL:		 // Cast spell (usually means apply aura)
				{
					if( Apply )
					{
						SpellCastTargets targets( m_owner->GetGUID() );
						SpellEntry* sp;
						Spell* spell;
						
						if( Entry->spell[c] != 0 )
						{
							sp = dbcSpell.LookupEntry( Entry->spell[c] );
							if( sp == NULL )
								continue;

							spell = SpellPool.PooledNew();
							spell->Init( m_owner, sp, true, 0 );
							spell->i_caster = this;
							spell->prepare( &targets );
						}
					}
					else
					{
						if( Entry->spell[c] != 0 )
								m_owner->RemoveAura( Entry->spell[c] );
					}

				}break;

			case SPELL_ENCHANT_TYPE_MOD_RESIST:		 // Modify physical resistance
				{
					int32 val = Entry->min[c];
					if( RandomSuffixAmount )
						val = RANDOM_SUFFIX_MAGIC_CALCULATION( RandomSuffixAmount, GetItemRandomSuffixFactor() );

					if( Apply )
					{
						m_owner->FlatResistanceModifierPos[Entry->spell[c]] += val;
					}
					else
					{
						m_owner->FlatResistanceModifierPos[Entry->spell[c]] -= val;
					}
					m_owner->CalcResistance( Entry->spell[c] );
				}break;

			case SPELL_ENCHANT_TYPE_MOD_RATING:	 //Modify rating ...order is PLAYER_FIELD_COMBAT_RATING_1 and above
				{
					//spellid is enum ITEM_STAT_TYPE
					//min=max is amount
					int32 val = Entry->min[c];
					if( RandomSuffixAmount )
						val = RANDOM_SUFFIX_MAGIC_CALCULATION( RandomSuffixAmount, GetItemRandomSuffixFactor() );

					m_owner->ModifyBonuses( Entry->spell[c], val, Apply );
					m_owner->UpdateStats();
				}break;

			case SPELL_ENCHANT_TYPE_MOD_DPS:	 // Rockbiter weapon (increase damage per second... how the hell do you calc that)
				{
					if( m_owner->getClass() == DEATHKNIGHT )
						continue;

					if( Apply )
					{
						//m_owner->ModUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS, Entry->min[c]);
						//if i'm not wrong then we should apply DMPS formula for this. This will have somewhat a larger value 28->34
						int32 val = Entry->min[c];
						if( RandomSuffixAmount )
							val = RANDOM_SUFFIX_MAGIC_CALCULATION( RandomSuffixAmount, GetItemRandomSuffixFactor() );

						int32 value = GetProto()->Delay * val / 1000;
						m_owner->ModUnsigned32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS, value );
					}
					else
					{
						int32 val = Entry->min[c];
						if( RandomSuffixAmount )
							val = RANDOM_SUFFIX_MAGIC_CALCULATION( RandomSuffixAmount, GetItemRandomSuffixFactor() );

						int32 value =- (int32)(GetProto()->Delay * val / 1000 );
						m_owner->ModUnsigned32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS, value );
					}
					m_owner->CalcDamage();
				}break;
			case SPELL_ENCHANT_TYPE_ADD_SOCKET:	 // add socket holder
				{
					//nothing to be done atm. Client will show socket. I think spell id is socket color mask
				}break;
			default:
				{
					sLog.outError( "Unknown enchantment type: %u (%u)", Entry->type[c], Entry->Id );
				}break;
			}
		}
	}
}

void Item::ApplyEnchantmentBonuses()
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	EnchantmentMap::iterator itr, itr2;
	EnchantmentMap tlist = Enchantments;	//somehow this list get emptied while updating enchantments
	for( itr = tlist.begin(); itr != tlist.end(); itr++ )
	{
		itr2 = Enchantments.find( itr->first );
		if( itr2 != Enchantments.end() )
			ApplyEnchantmentBonus( itr2->first, APPLY );
	}
}

void Item::RemoveEnchantmentBonuses()
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	EnchantmentMap::iterator itr, itr2;
	for( itr = Enchantments.begin(); itr != Enchantments.end(); )
	{
		itr2 = itr++;
		ApplyEnchantmentBonus( itr2->first, REMOVE );
	}
}

void Item::EventRemoveEnchantment( uint32 Slot )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	// Remove the enchantment.
	RemoveEnchantment( Slot );
}

int32 Item::FindFreeEnchantSlot( EnchantEntry* Enchantment, uint32 random_type )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	
	uint32 GemSlotsReserve = GetSocketsCount();
	if( GetProto()->SocketBonus )
		GemSlotsReserve++;

	if( random_type == RANDOMPROPERTY )		// random prop
	{
		for( uint32 Slot = ITEM_ENCHANT_SLOT_RANDOM_PROP2; Slot <= ITEM_ENCHANT_SLOT_RANDOM_PROP4; ++Slot )
			if( m_uint32Values[ITEM_FIELD_ENCHANTMENT_1_1 + Slot * 3] == 0 )
			{ 
				return Slot;
			}
	}
	else if( random_type == RANDOMSUFFIX )	// random suffix
	{
		for( uint32 Slot = ITEM_ENCHANT_SLOT_RANDOM_PROP0; Slot <= ITEM_ENCHANT_SLOT_RANDOM_PROP4; ++Slot )
			if( m_uint32Values[ITEM_FIELD_ENCHANTMENT_1_1 + Slot * 3] == 0 )
			{ 
				return Slot;
			}
	}
	
	for( uint32 Slot = GemSlotsReserve + ITEM_ENCHANT_SLOT_GEM1; Slot <= ITEM_ENCHANT_SLOT_RANDOM_PROP4; Slot++ )
	{
		if( m_uint32Values[ITEM_FIELD_ENCHANTMENT_1_1 + Slot * 3] == 0 )
		{ 
			return Slot;	
		}
	}

	return -1;
}

int32 Item::HasEnchantment( uint32 Id )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	for( uint32 Slot = 0; Slot <= ITEM_ENCHANT_SLOT_RANDOM_PROP4; Slot++ )
	{
		if( m_uint32Values[ITEM_FIELD_ENCHANTMENT_1_1 + Slot * 3] == Id )
		{ 
			return Slot;
		}
	}

	return -1;
}

bool Item::HasEnchantmentOnSlot( uint32 slot )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	EnchantmentMap::iterator itr = Enchantments.find( slot );
	if( itr == Enchantments.end() )
	{ 
		return false;
	}

	return true;
}

void Item::ModifyEnchantmentTime( uint32 Slot, uint32 Duration )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	EnchantmentMap::iterator itr = Enchantments.find( Slot );
	if( itr == Enchantments.end() )
	{ 
		return;
	}

	// Reset the apply time.
	itr->second->ApplyTime = UNIXTIME;
	itr->second->Duration = Duration;

	// Change the event timer.
	event_ModifyRepeatInterval( EVENT_REMOVE_ENCHANTMENT1 + Slot, Duration * 1000 );

	// Send update packet
	SendEnchantTimeUpdate( itr->second->Slot, Duration );
}

void Item::SendEnchantTimeUpdate( uint32 Slot, uint32 Duration )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	/*
	{SERVER} Packet: (0x01EB) SMSG_ITEM_ENCHANT_TIME_UPDATE Size = 24
	|------------------------------------------------|----------------|
	|00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |0123456789ABCDEF|
	|------------------------------------------------|----------------|
	|69 32 F0 35 00 00 00 40 01 00 00 00 08 07 00 00 |i2.5...@........|
	|51 46 35 00 00 00 00 00						 |QF5.....		|
	-------------------------------------------------------------------

	uint64 item_guid
	uint32 count?
	uint32 time_in_seconds
	uint64 player_guid
	*/

	WorldPacket* data = new WorldPacket(SMSG_ITEM_ENCHANT_TIME_UPDATE, 24 );
	*data << GetGUID();
	*data << Slot;
	*data << Duration;
	*data << m_owner->GetGUID();
	m_owner->delayedPackets.add( data );
}

void Item::RemoveAllEnchantments( bool OnlyTemporary )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	EnchantmentMap::iterator itr, it2;
	for( itr = Enchantments.begin(); itr != Enchantments.end(); )
	{
		it2 = itr++;

		if( OnlyTemporary && it2->second->Duration == 0 ) 
			continue;
			
		RemoveEnchantment( it2->first );
	}
}

void Item::RemoveRelatedEnchants( EnchantEntry* newEnchant )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	EnchantmentMap::iterator itr,itr2;
	for( itr = Enchantments.begin(); itr != Enchantments.end(); )
	{
		itr2 = itr++;
		
		if( itr2->second->Enchantment->Id == newEnchant->Id || ( itr2->second->Enchantment->EnchantGroups > 1 && newEnchant->EnchantGroups > 1 ) )
		{ 
			RemoveEnchantment( itr2->first );
		}
	}
}

void Item::RemoveProfessionEnchant()
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	EnchantmentMap::iterator itr;
	for( itr = Enchantments.begin(); itr != Enchantments.end(); itr++ )
	{
		if( itr->second->Duration != 0 )// not perm
			continue;
		if( IsGemRelated( itr->second->Enchantment ) )
			continue;

		RemoveEnchantment( itr->first );
		return;
	}
}

void Item::RemoveSocketBonusEnchant()
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	EnchantmentMap::iterator itr;
	
	for( itr = Enchantments.begin(); itr != Enchantments.end(); itr++ )
	{
		if( itr->second->Enchantment->Id == GetProto()->SocketBonus )
		{
			RemoveEnchantment( itr->first );
			return;
		}	
	}
}

EnchantmentInstance* Item::GetEnchantment( uint32 slot )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	EnchantmentMap::iterator itr = Enchantments.find( slot );
	if( itr != Enchantments.end() )
	{ 
		return itr->second;
	}
	else
		return NULL;
}

bool Item::IsGemRelated( EnchantEntry* Enchantment )
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	if( GetProto()->SocketBonus == Enchantment->Id )
	{ 
		return true;
	}
	
	return( Enchantment->GemEntry != 0 );
}

uint32 Item::GetSocketsCount()
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	if( IsContainer() ) // no sockets on containers.
	{ 
		return 0;
	}

	uint32 c = 0;
	for( uint32 x = 0; x < 3; x++ )
		if( GetProto()->Sockets[x].SocketColor )
			c++;

	//Enchantments may add extra sockets
	EnchantmentMap::iterator itr;
	for( itr = Enchantments.begin(); itr != Enchantments.end(); itr++ )
		for(int i=0;i<3;i++)
			if( itr->second->Enchantment->type[i] == SPELL_ENCHANT_TYPE_ADD_SOCKET )
				c++;

	return c;
}

uint32 Item::GenerateRandomSuffixFactor( ItemPrototype* m_itemProto )
{
	double value;

	if( m_itemProto->Class == ITEM_CLASS_ARMOR && m_itemProto->Quality > ITEM_QUALITY_UNCOMMON_GREEN )
		value = SuffixMods[m_itemProto->InventoryType] * 1.24;
	else
		value = SuffixMods[m_itemProto->InventoryType];

	value = ( value * double( m_itemProto->ItemLevel ) ) + 0.5;
	return long2int32( value );
}

string Item::GetItemLink(uint32 language = NULL)
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	return GetItemLinkByProto(GetProto(), language);
}

string GetItemLinkByProto(ItemPrototype * iProto, uint32 language = NULL)
{
	const char * ItemLink;
	char buffer[256];
	std::string colour;

	switch(iProto->Quality)
	{
		case ITEM_QUALITY_POOR_GREY:
			colour = "cff9d9d9d";
		break;
		case ITEM_QUALITY_NORMAL_WHITE:
			colour = "cffffffff";
		break;
		case ITEM_QUALITY_UNCOMMON_GREEN:
			colour = "cff1eff00";
		break;
		case ITEM_QUALITY_RARE_BLUE:
			colour = "cff0070dd";
		break;
		case ITEM_QUALITY_EPIC_PURPLE:
			colour = "cffa335ee";
		break;
		case ITEM_QUALITY_LEGENDARY_ORANGE:
			colour = "cffff8000";
		break;
		case ITEM_QUALITY_ARTIFACT_LIGHT_YELLOW:
			colour = "c00fce080";
		break;
		case ITEM_QUALITY_HEIRLOOM_LIGHT_YELLOW:
			colour = "c00fce080";
		break;
		default:
			colour = "cff9d9d9d";
	}
	
	// try to get localized version
	LocalizedItem *lit	= (language>0) ? sLocalizationMgr.GetLocalizedItem(iProto->ItemId, language) : NULL;

	if(lit)
		snprintf(buffer, 256, "|%s|Hitem:%u:0:0:0:0:0:0:0|h[%s]|h|r", colour.c_str(), iProto->ItemId, lit->Name);
	else
		snprintf(buffer, 256, "|%s|Hitem:%u:0:0:0:0:0:0:0|h[%s]|h|r", colour.c_str(), iProto->ItemId, iProto->Name1);
	

	ItemLink	= reinterpret_cast<const char*>(buffer);

	return ItemLink;
}

int32 Item::event_GetInstanceID() 
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	if( m_owner )
	{ 
		return m_owner->event_GetInstanceID();
	}
	return WORLD_INSTANCE;
}

void Item::AddTemporalSpellBookSpell(uint32 new_spell)
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	if( HasTemporalSpellBookSpell( new_spell ) )
		return;
	enchant_spell_book.push_back( new_spell );
}

void Item::RemoveTemporalSpellBookSpell(uint32 new_spell)
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	enchant_spell_book.remove( new_spell );

/*	list<uint32>::iterator itr;
	for(itr=enchant_spell_book.begin();itr!=enchant_spell_book.end();itr++)
		if( *itr == new_spell )
		{
			enchant_spell_book.remove( *itr );
			return;
		}*/
}

bool Item::HasTemporalSpellBookSpell(uint32 spellId)
{
	INSTRUMENT_TYPECAST_CHECK_ITEM_OBJECT_TYPE
	list<uint32>::iterator itr;
	for(itr=enchant_spell_book.begin();itr!=enchant_spell_book.end();itr++)
		if( *itr == spellId )
		{
			return true;
		}
	return false;
}

void Item::SendItemDuration()
{
    if (!GetUInt32Value(ITEM_FIELD_DURATION))
        return;

	sStackWolrdPacket( data ,SMSG_ITEM_TIME_UPDATE, 8+4+2);
    data << (uint64)GetGUID();
    data << (uint32)GetUInt32Value(ITEM_FIELD_DURATION);
    m_owner->GetSession()->SendPacket(&data);
}

//cannot return more then 17 atm !
uint32 GetStatScalingStatValueColumn(ItemPrototype *proto, uint32 type)
{
	switch(type)
	{
		case SCALINGSTATSTAT:
		{ 
			//this flag is not used at all ?
			if(proto->ScalingStatsFlag & 16)
			{ 
//			    return 4;
			    return 16;	//relocated in 3.2.0, maybe shared with something else ?
			}
			if(proto->ScalingStatsFlag & 8)
			{ 
			    return 3;
			}
			if(proto->ScalingStatsFlag & 4)
			{ 
			    return 2;
			}
			if(proto->ScalingStatsFlag & 2)
			{ 
			    return 1;
			}
			if(proto->ScalingStatsFlag & 1)
			{ 
				return 0;
			}
		}break;

		case SCALINGSTATARMOR:
		{ 
			if(proto->ScalingStatsFlag & 256)
			{ 
				return 7;
			}
			if(proto->ScalingStatsFlag & 256)
			{ 
				return 7;
			}
			if(proto->ScalingStatsFlag & 128)
			{ 
				return 6;
			}
			if(proto->ScalingStatsFlag & 64)
			{ 
				return 5;
			}
			if(proto->ScalingStatsFlag & 32)
			{ 
				return 4;
			}
		}break;

		case SCALINGSTATDAMAGE:
		{ 
			if(proto->ScalingStatsFlag & 16384)
			{ 
				return 13;
			}
			if(proto->ScalingStatsFlag & 8192)
			{ 
				return 12;
			}
			if(proto->ScalingStatsFlag & 4096)
			{ 
				return 11;
			}
			if(proto->ScalingStatsFlag & 2048)
			{ 
				return 10;
			}
			if(proto->ScalingStatsFlag & 1024)
			{ 
				return 9;
			}
			if(proto->ScalingStatsFlag & 512)
			{ 
				return 8;
			}
		}break;

		case SCALINGSTATSPELLPOWER:
		{ 
			if(proto->ScalingStatsFlag & 32768)
			{ 
				return 14;
			}
		}break;
		//need more flags to decode the rest ?
	}
	sLog.outDebug("Item %u Unknown Scalling stat type %u\n",proto->ItemId,type);
	return 0;
}
