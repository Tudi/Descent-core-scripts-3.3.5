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

#define SPELL_CHANNEL_UPDATE_INTERVAL 1000

/// externals for spell system
extern pSpellEffect SpellEffectsHandler[TOTAL_SPELL_EFFECTS];
extern pSpellTarget SpellTargetHandler[EFF_TARGET_LIST_LENGTH_MARKER];

extern char* SpellEffectNames[TOTAL_SPELL_EFFECTS];

enum SpellTargetSpecification
{
    TARGET_SPECT_NONE       = 0,
    TARGET_SPEC_INVISIBLE   = 1,
    TARGET_SPEC_DEAD        = 2,
};

void SpellCastTargets::read( WorldPacket & data,uint64 caster )
{
	m_unitTarget = m_itemTarget = 0;
	m_srcX = m_srcY = m_srcZ = m_destX = m_destY = m_destZ = missilepitch = missilespeed = 0.0f;
	missileunkcheck = 0;
	unkdoodah = unkdoodah2 = 0;
	m_strTarget = "";

//	data >> m_missileFlags; - not sure all packets have it so this is set in client packet handler function
	data >> m_targetMask;
	data >> m_targetMaskExtended;

	if( m_targetMask == TARGET_FLAG_SELF )
	{
		m_unitTarget = caster;
	}

	if( m_targetMask & (TARGET_FLAG_OBJECT | TARGET_FLAG_UNIT | TARGET_FLAG_CORPSE | TARGET_FLAG_CORPSE2 ) )
	{
		data >> guid;
		m_unitTarget = guid.GetOldGuid();
	}

	if( m_targetMask & ( TARGET_FLAG_ITEM | TARGET_FLAG_TRADE_ITEM ) )
	{
		data >> guid;
		m_itemTarget = guid.GetOldGuid();
	}

	if( m_targetMask & TARGET_FLAG_SOURCE_LOCATION )
	{
		data >> guid;	//added in 3.2
		data >> m_srcX >> m_srcY >> m_srcZ;

		if( !( m_targetMask & TARGET_FLAG_DEST_LOCATION ) )
		{
			m_destX = m_srcX;
			m_destY = m_srcY;
			m_destZ = m_srcZ;
		}
	}

	if( m_targetMask & TARGET_FLAG_DEST_LOCATION )
	{
		data >> guid >> m_destX >> m_destY >> m_destZ;
		if( !( m_targetMask & TARGET_FLAG_SOURCE_LOCATION ) )
		{
			m_srcX = m_destX;
			m_srcY = m_destY;
			m_srcZ = m_destZ;
		}
	}
	if( m_targetMask & TARGET_FLAG_PET_DEST_LOCATION )
	{
		WoWGuid guid2;
		data >> guid;
		data >> guid2;
//		targets.m_unitTarget = guid2.GetOldGuid();
		data >> m_destX >> m_destY >> m_destZ;
	}

	if( m_targetMask & TARGET_FLAG_STRING )
	{
		data >> m_strTarget;
	}

	if (m_missileFlags & 0x2)
 	{
		data >> missilepitch >> missilespeed >> missileunkcheck;

		if (missileunkcheck == 1)
		{
//			WoWGuid tguid;
//			data >> tguid;	//compressed guid instead of doodah !
//			data >> unkdoodah;
//			data >> unkdoodah2;
		}

		float dx = m_destX - m_srcX;
		float dy = m_destY - m_srcY;
		if (missilepitch != M_PI / 4 && missilepitch != -M_PI / 4)
			traveltime = (sqrtf(dx * dx + dy * dy) / (cosf(missilepitch) * missilespeed)) * 1000;
 	}
}

void SpellCastTargets::write( StackWorldPacket& data )
{
	data << m_targetMask;
	data << m_targetMaskExtended;

	if( /*m_targetMask == TARGET_FLAG_SELF || */m_targetMask & (TARGET_FLAG_UNIT | TARGET_FLAG_CORPSE | TARGET_FLAG_CORPSE2 | TARGET_FLAG_OBJECT ) )
        FastGUIDPack( data, m_unitTarget );

    if( m_targetMask & ( TARGET_FLAG_ITEM | TARGET_FLAG_TRADE_ITEM ) )
        FastGUIDPack( data, m_itemTarget );

	if( m_targetMask & TARGET_FLAG_SOURCE_LOCATION )
	{
		data << guid;	//3.3
		data << m_srcX << m_srcY << m_srcZ;
	}

	if( m_targetMask & TARGET_FLAG_DEST_LOCATION )
	{
		data << guid; //303 -> this is packed guid
		data << m_destX << m_destY << m_destZ;
	}
	if( m_targetMask & TARGET_FLAG_STRING )
		data << m_strTarget;
	if( m_targetMask & TARGET_FLAG_PET_DEST_LOCATION )
	{
		WoWGuid guid2;
		data << uint8(0);	//guid 1
		data << uint8(0);	//guid 2
		data << m_destX << m_destY << m_destZ;
	}
/*	if (m_missileFlags & 0x2)
 	{
		data << missilepitch << missilespeed << missileunkcheck;
		if (missileunkcheck == 1)
		{
			data << unkdoodah;
			data << unkdoodah2;
		}
 	}*/
}

Spell::Spell()
{
	m_bufferPoolId = OBJECT_WAS_ALLOCATED_STANDARD_WAY;
}

void Spell::Virtual_Constructor()
{
}

void Spell::Init(Object* Caster, SpellEntry *info, bool triggered, Aura* aur)
{
	ASSERT( Caster != NULL )
	ASSERT( info != NULL );

#ifdef DEBUG_SPELL_CASTS
	if( info->Id < MAX_USABLE_SPELL_ID )
	{
		if( casted_spells[ info->Id ] == 0 )
			DumpToFileUniqueSpells( true );
		casted_spells[ info->Id ] = 1;
//printf("!!!spell cast %u -> %u pool id %u, caster guid %u \n",info->Id,last_N_spells_index,m_bufferPoolId,(uint32)(Caster->GetGUID()) );
//CStackWalker sw;
//sw.ShowCallstack();
		if( last_N_spells_FILE )
		{
			last_N_spells_index = ( last_N_spells_index + 1 ) % LOG_LAST_N_SPELLS;
			last_N_spells[ last_N_spells_index ] = info->Id;
			fseek(last_N_spells_FILE,SEEK_SET,0);
			for(int i=0;i<LOG_LAST_N_SPELLS;i++)
				fprintf(last_N_spells_FILE,"%u\n",last_N_spells[ (100 + last_N_spells_index - i ) % LOG_LAST_N_SPELLS ]);
		}
	}
#endif
	GlyphSlot = 0xFFFFFFFF; //we do not have it set
	UniqueTargets.clear();
	ModeratedTargets.clear();
	chaincast_jump_pct_mod = 100;
	bDurSet = 0;
	damage = 0;
	m_targetUnits[0].clear();
	m_targetUnits[1].clear();
	m_targetUnits[2].clear();
	bRadSet[0] = 0;
	bRadSet[1] = 0;
	bRadSet[2] = 0;

	m_spellInfo = info;
//	m_spellInfo_override = NULL;
	m_caster = Caster;
	duelSpell = false;

	switch( Caster->GetTypeId() )
	{
		case TYPEID_PLAYER:
		{
			g_caster = NULL;
			i_caster = NULL;
			u_caster = SafeUnitCast( Caster );
			p_caster = SafePlayerCast( Caster );
			if( p_caster->GetDuelState() == DUEL_STATE_STARTED )
				duelSpell = true;
		} break;

		case TYPEID_UNIT:
		{
			g_caster = NULL;
			i_caster = NULL;
			p_caster = NULL;
			u_caster = SafeUnitCast( Caster );
			if( u_caster->IsPet() && SafePetCast( u_caster)->GetPetOwner() != NULL && SafePetCast( u_caster )->GetPetOwner()->GetDuelState() == DUEL_STATE_STARTED )
				duelSpell = true;
		} break;

		case TYPEID_ITEM:
		case TYPEID_CONTAINER:
		{
			g_caster = NULL;
			u_caster = NULL;
			p_caster = NULL;
			i_caster = SafeItemCast( Caster );
			if( i_caster->GetOwner() && i_caster->GetOwner()->GetDuelState() == DUEL_STATE_STARTED )
				duelSpell = true;
		} break;

		case TYPEID_GAMEOBJECT:
		{
			u_caster = NULL;
			p_caster = NULL;
			i_caster = NULL;
			g_caster = SafeGOCast( Caster );
		} break;

		default:
			sLog.outDebug("[DEBUG][SPELL] Incompatible object type, please report this to the dev's");
			break;
	}

	m_spellState = SPELL_STATE_NULL;

	m_castPositionX = m_castPositionY = m_castPositionZ = 0;
	//TriggerSpellId = 0;
	//TriggerSpellTarget = 0;
	m_triggeredSpell = triggered;
	m_AreaAura = false;

	m_triggeredByAura = aur;

	damageToHit = 0;
	castedItemId = 0;

	m_usesMana = false;
	m_Spell_Failed = false;
	m_CanRelect = false;
	m_IsReflected = false;
	hadEffect = false;
	bDurSet = false;
	bRadSet[0] = false;
	bRadSet[1] = false;
	bRadSet[2] = false;

	cancastresult = SPELL_CANCAST_OK;

	m_requiresCP = false;
	unitTarget = NULL;
	ModeratedTargets.clear();
	itemTarget = NULL;
	gameObjTarget = NULL;
	playerTarget = NULL;
	corpseTarget = NULL;
	add_damage = 0;
	m_Delayed = false;
	pSpellId = 0;
	m_cancelled = false;
	ProcedOnSpell = 0;
	forced_basepoints[0] = forced_basepoints[1] = forced_basepoints[2] = 0;
	forced_miscvalues[0] = forced_miscvalues[1] = forced_miscvalues[2] = 0;
	static_dmg[0] = static_dmg[1] = static_dmg[2] = 0;
	forced_duration = 0;
	extra_cast_number = 0;
	m_reflectedParent = NULL;
	m_isCasting = false;
	channel_delays = 0;
	//create rune avail snapshot
	if( p_caster && p_caster->getClass() == DEATHKNIGHT )
	{
		m_rune_avail_before = 0;
		m_runes_to_update = 0;
		for( int i=0;i<TOTAL_USED_RUNES;i++)
			if( p_caster->m_runes[ i ] == MAX_RUNE_VALUE )
				m_rune_avail_before |= (1 << i);
	}
	m_missilePitch = 0;
	m_missileTravelTime = 0;
}

Spell::~Spell()
{
	if( m_bufferPoolId != OBJECT_WAS_ALLOCATED_STANDARD_WAY )
		ASSERT( false ); //we are deleting a pooled object. This leads to mem corruptions
}

void Spell::Virtual_Destructor()
{
	if( u_caster != NULL && u_caster->GetCurrentSpell() == this )
		u_caster->SetCurrentSpell(NULL);

	if( p_caster )
		if( hadEffect || ( cancastresult == SPELL_CANCAST_OK && !GetSpellFailed() ) )
			RemoveItems();

//	if (m_spellInfo_override !=NULL)
//		delete[] m_spellInfo_override;

//	sEventMgr.RemoveEvents( this ); //do even spells have events ?
}

//i might forget conditions here. Feel free to add them
bool Spell::IsStealthSpell()
{
	//check if aura name is some stealth aura
	if( GetProto()->EffectApplyAuraName[0] == SPELL_AURA_MOD_STEALTH || GetProto()->EffectApplyAuraName[1] == SPELL_AURA_MOD_STEALTH || GetProto()->EffectApplyAuraName[2] == SPELL_AURA_MOD_STEALTH )
	{ 
		return true;
	}
	return false;
}

//i might forget conditions here. Feel free to add them
bool Spell::IsInvisibilitySpell()
{
	//check if aura name is some invisibility aura
	if( GetProto()->EffectApplyAuraName[0] == SPELL_AURA_MOD_INVISIBILITY || GetProto()->EffectApplyAuraName[1] == SPELL_AURA_MOD_INVISIBILITY || GetProto()->EffectApplyAuraName[2] == SPELL_AURA_MOD_INVISIBILITY )
	{ 
		return true;
	}
	return false;
}

void Spell::FillSpecifiedTargetsInArea( float srcx, float srcy, float srcz, uint32 ind, uint32 specification )
{
	FillSpecifiedTargetsInArea( ind, srcx, srcy, srcz, GetRadius(ind), specification );
}

// for the moment we do invisible targets
void Spell::FillSpecifiedTargetsInArea(uint32 i,float srcx,float srcy,float srcz, float range, uint32 specification)
{
	TargetsList *tmpMap=&m_targetUnits[i];
	//IsStealth()
	float r = range * range;
	uint8 did_hit_result;
	m_caster->AquireInrangeLock(); //make sure to release lock before exit function !
	for(std::set<Object*>::iterator itr = m_caster->GetInRangeSetBegin(); itr != m_caster->GetInRangeSetEnd(); itr++ )
	{
		// don't add objects that are not units and that are dead
		if( !( (*itr)->IsUnit() ) || ! SafeUnitCast( *itr )->isAlive())
			continue;

		//SafeUnitCast( *itr )->IsStealth()
		if( !TargetTypeCheck( (*itr), GetProto()->TargetCreatureType ) )
			continue;

		if(IsInrange(srcx,srcy,srcz,(*itr),r))
		{
			if( u_caster != NULL )
			{
				if( isAttackable( u_caster, SafeUnitCast( *itr ), !( GetProto()->c_is_flags & SPELL_FLAG_IS_TARGETINGSTEALTHED ) ) )
				{
					did_hit_result = DidHit(i, SafeUnitCast( *itr ) );
					if( did_hit_result != SPELL_DID_HIT_SUCCESS )
						ModeratedTargets.push_back(SpellTargetMod((*itr)->GetGUID(), did_hit_result));
					else
						SafeAddTarget(tmpMap, (*itr)->GetGUID());
				}

			}
			else //cast from GO
			{
				if ( g_caster && g_caster->GetUInt32Value( OBJECT_FIELD_CREATED_BY ) && g_caster->m_summoner )
				{
					//trap, check not to attack owner and friendly
					if(isAttackable(g_caster->m_summoner,(*itr),!(GetProto()->c_is_flags & SPELL_FLAG_IS_TARGETINGSTEALTHED)))
						SafeAddTarget(tmpMap, (*itr)->GetGUID());
				}
				else
					SafeAddTarget(tmpMap, (*itr)->GetGUID());
			}
			if( GetProto()->MaxTargets )
			{
				int32 MaxTargets = GetProto()->MaxTargets;
				if((GetProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && u_caster)
					SM_FIValue(u_caster->SM_FAdditionalTargets,&MaxTargets,GetProto()->SpellGroupType);
				if( MaxTargets <= (int32)tmpMap->size())
				{
					m_caster->ReleaseInrangeLock();
					return;
				}
			}
		}
	}
	m_caster->ReleaseInrangeLock();
}
void Spell::FillAllTargetsInArea(LocationVector & location,uint32 ind)
{
	FillAllTargetsInArea(ind,location.x,location.y,location.z,GetRadius(ind));
}

void Spell::FillAllTargetsInArea(float srcx,float srcy,float srcz,uint32 ind)
{
	FillAllTargetsInArea(ind,srcx,srcy,srcz,GetRadius(ind));
}

/// We fill all the targets in the area, including the stealth ed one's
void Spell::FillAllTargetsInArea(uint32 i,float srcx,float srcy,float srcz, float range)
{
	TargetsList *tmpMap=&m_targetUnits[i];
	float r = range*range;
	uint8 did_hit_result;
	std::set<Object*>::iterator itr,itr2;
	m_caster->AquireInrangeLock(); //make sure to release lock before exit function !
	for( itr2 = m_caster->GetInRangeSetBegin(); itr2 != m_caster->GetInRangeSetEnd();)
	{
		itr = itr2;
		itr2++; //maybe scripts can change list. Should use lock instead of this to prevent multiple changes. This protects to 1 deletion only
		if( !( (*itr)->IsUnit() ) 
				|| !SafeUnitCast( *itr )->isAlive() 
				//fix for spell not targetting totems ? But they are not supposed to target them no ?
//				|| ( SafeUnitCast( *itr )->IsCreature() && SafeCreatureCast( *itr )->IsTotem()) 
				)
			continue;

		if( !TargetTypeCheck( (*itr), GetProto()->TargetCreatureType ) )
			continue;

		if( IsInrange( srcx, srcy, srcz, (*itr), r ) )
		{
			if( u_caster != NULL )
			{
				if( isAttackable( u_caster, ( *itr ), !(GetProto()->c_is_flags & SPELL_FLAG_IS_TARGETINGSTEALTHED) ) )
				{
					did_hit_result = DidHit(i,SafeUnitCast( *itr ) );
					if( did_hit_result == SPELL_DID_HIT_SUCCESS )
						SafeAddTarget(tmpMap, (*itr)->GetGUID());
					else
						ModeratedTargets.push_back( SpellTargetMod( (*itr)->GetGUID(), did_hit_result ) );
				}
			}
			else //cast from GO
			{
				if( g_caster != NULL && g_caster->GetUInt32Value( OBJECT_FIELD_CREATED_BY ) && g_caster->m_summoner != NULL )
				{
					//trap, check not to attack owner and friendly
					if( isAttackable( g_caster->m_summoner, SafeUnitCast( *itr ), !(GetProto()->c_is_flags & SPELL_FLAG_IS_TARGETINGSTEALTHED) ) )
						SafeAddTarget(tmpMap, (*itr)->GetGUID());
				}
				else
					SafeAddTarget(tmpMap, (*itr)->GetGUID());
			}
			if( GetProto()->MaxTargets )
			{
				int32 MaxTargets = GetProto()->MaxTargets;
				if((GetProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && u_caster)
					SM_FIValue(u_caster->SM_FAdditionalTargets,&MaxTargets,GetProto()->SpellGroupType);
				if( MaxTargets <= (int32)tmpMap->size() )
				{
					m_caster->ReleaseInrangeLock();
					return;
				}
			}
		}
	}
	m_caster->ReleaseInrangeLock();
}

// We fill all the targets in the area, including the stealth ed one's
void Spell::FillAllFriendlyInArea( uint32 i, float srcx, float srcy, float srcz, float range )
{
	TargetsList *tmpMap=&m_targetUnits[i];
	float r = range * range;
	uint8 did_hit_result;
	std::set<Object*>::iterator itr,itr2;
	m_caster->AquireInrangeLock(); //make sure to release lock before exit function !
	for( itr2 = m_caster->GetInRangeSetBegin(); itr2 != m_caster->GetInRangeSetEnd();)
	{
		itr = itr2;
		itr2++; //maybe scripts can change list. Should use lock instead of this to prevent multiple changes. This protects to 1 deletion only
		if( !((*itr)->IsUnit()) || !SafeUnitCast( *itr )->isAlive() )
			continue;

		if( !TargetTypeCheck( (*itr), GetProto()->TargetCreatureType ) )
			continue;

		if( IsInrange( srcx, srcy, srcz, (*itr), r ) )
		{
			if( u_caster != NULL )
			{
				if( isFriendly( u_caster, SafeUnitCast( *itr ) ) )
				{
					did_hit_result = DidHit(i, SafeUnitCast( *itr ) );
					if( did_hit_result == SPELL_DID_HIT_SUCCESS )
						SafeAddTarget(tmpMap, (*itr)->GetGUID());
					else
						ModeratedTargets.push_back( SpellTargetMod( (*itr)->GetGUID(), did_hit_result ) );
				}
			}
			else //cast from GO
			{
				if( g_caster != NULL && g_caster->GetUInt32Value( OBJECT_FIELD_CREATED_BY ) && g_caster->m_summoner != NULL )
				{
					//trap, check not to attack owner and friendly
					if( isFriendly( g_caster->m_summoner, SafeUnitCast( *itr ) ) )
						SafeAddTarget(tmpMap, (*itr)->GetGUID());
				}
				else
					SafeAddTarget(tmpMap, (*itr)->GetGUID());
			}
			if( GetProto()->MaxTargets )
			{
				int32 MaxTargets = GetProto()->MaxTargets;
				if((GetProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && u_caster)
					SM_FIValue(u_caster->SM_FAdditionalTargets,&MaxTargets,GetProto()->SpellGroupType);
				if( MaxTargets <= (int32)tmpMap->size() )
				{
					m_caster->ReleaseInrangeLock();
					return;
				}
			}
		}
	}
	m_caster->ReleaseInrangeLock();
}

uint64 Spell::GetSinglePossibleEnemy(uint32 i,float prange)
{
	float r;
	if(prange)
		r = prange;
	else
	{
		r = GetProto()->base_range_or_radius_sqr;
		if( Need_SM_Apply(GetProto()) && u_caster)
		{
			SM_FFValue(u_caster->SM_FRadius,&r,GetProto()->SpellGroupType);
			SM_PFValue(u_caster->SM_PRadius,&r,GetProto()->SpellGroupType);
		}
	}
	float srcx = m_caster->GetPositionX(), srcy = m_caster->GetPositionY(), srcz = m_caster->GetPositionZ();
	m_caster->AquireInrangeLock(); //make sure to release lock before exit function !
	for( std::set<Object*>::iterator itr = m_caster->GetInRangeSetBegin(); itr != m_caster->GetInRangeSetEnd(); itr++ )
	{
		if( !( (*itr)->IsUnit() ) || !SafeUnitCast( *itr )->isAlive() )
			continue;

		if( !TargetTypeCheck( (*itr), GetProto()->TargetCreatureType ) )
			continue;

		if(IsInrange(srcx,srcy,srcz,(*itr),r))
		{
			if( u_caster != NULL )
			{
				if(isAttackable(u_caster, *itr ,!(GetProto()->c_is_flags & SPELL_FLAG_IS_TARGETINGSTEALTHED)) && DidHit(i,((Unit*)*itr))==SPELL_DID_HIT_SUCCESS)
				{
					m_caster->ReleaseInrangeLock();
					return (*itr)->GetGUID();
				}
			}
			else //cast from GO
			{
				if(g_caster && g_caster->GetUInt32Value(OBJECT_FIELD_CREATED_BY) && g_caster->m_summoner)
				{
					//trap, check not to attack owner and friendly
					if( isAttackable( g_caster->m_summoner, SafeUnitCast( *itr ),!(GetProto()->c_is_flags & SPELL_FLAG_IS_TARGETINGSTEALTHED)))
					{
						m_caster->ReleaseInrangeLock();
						return (*itr)->GetGUID();
					}
				}
			}
		}
	}
	m_caster->ReleaseInrangeLock();
	return 0;
}

uint64 Spell::GetSinglePossibleFriend(uint32 i,float prange)
{
	float r;
	if(prange)
		r = prange;
	else
	{
		r = GetProto()->base_range_or_radius_sqr;
		if( Need_SM_Apply(GetProto()) && u_caster)
		{
			SM_FFValue(u_caster->SM_FRadius,&r,GetProto()->SpellGroupType);
			SM_PFValue(u_caster->SM_PRadius,&r,GetProto()->SpellGroupType);
		}
	}
	float srcx=m_caster->GetPositionX(),srcy=m_caster->GetPositionY(),srcz=m_caster->GetPositionZ();
	m_caster->AquireInrangeLock(); //make sure to release lock before exit function !
	for(std::set<Object*>::iterator itr = m_caster->GetInRangeSetBegin(); itr != m_caster->GetInRangeSetEnd(); itr++ )
	{
		if( !( (*itr)->IsUnit() ) || !SafeUnitCast( *itr )->isAlive() )
			continue;

		if( !TargetTypeCheck( (*itr), GetProto()->TargetCreatureType ) )
			continue;

		if(IsInrange(srcx,srcy,srcz,(*itr),r))
		{
			if( u_caster != NULL )
			{
				if( isFriendly( u_caster, ( *itr ) ) && DidHit(i, ((Unit*)*itr))==SPELL_DID_HIT_SUCCESS)
				{
					m_caster->ReleaseInrangeLock();
					return (*itr)->GetGUID();
				}
			}
			else //cast from GO
			{
				if(g_caster && g_caster->GetUInt32Value(OBJECT_FIELD_CREATED_BY) && g_caster->m_summoner)
				{
					//trap, check not to attack owner and friendly
					if( isFriendly( g_caster->m_summoner, SafeUnitCast( *itr ) ) )
					{
						m_caster->ReleaseInrangeLock();
						return (*itr)->GetGUID();
					}
				}
			}
		}
	}
	m_caster->ReleaseInrangeLock();
	return 0;
}

uint8 Spell::DidHit(uint32 effindex,Unit* target)
{
	//note resistchance is vise versa, is full hit chance
	Unit* u_victim = target;
	Player* p_victim = ( target->GetTypeId() == TYPEID_PLAYER ) ? SafePlayerCast( target ) : NULL;

	//
	float baseresist[3] = { 4.0f, 5.0f, 6.0f };
	int32 lvldiff;
	float resistchance ;
	if( u_victim == NULL )
		return SPELL_DID_HIT_MISS;

	/************************************************************************/
	/* Can't resist non-unit                                                */
	/************************************************************************/
	if(!u_caster)
		return SPELL_DID_HIT_SUCCESS;

	/************************************************************************/
	/* Can't reduce your own spells                                         */
	/************************************************************************/
	if(u_caster == u_victim)
		return SPELL_DID_HIT_SUCCESS;

	/************************************************************************/
	/* Check if the unit is evading                                         */
	/************************************************************************/
	if(u_victim->GetTypeId()==TYPEID_UNIT && u_victim->GetAIInterface()->getAIState()==STATE_EVADE)
		return SPELL_DID_HIT_EVADE;

	/************************************************************************/
	/* Check if the target is immune to this spell school                   */
	/* Unless the spell would actually dispel invulnerabilities             */
	/************************************************************************/
	int dispelMechanic = GetProto()->Effect[0] == SPELL_EFFECT_DISPEL_MECHANIC && GetProto()->EffectMiscValue[0] == MECHANIC_INVULNERABLE;
	if(u_victim->SchoolImmunityList[GetProto()->School] && !dispelMechanic)
		return SPELL_DID_HIT_IMMUNE;

	/* Check if player target has god mode */
	//Zack : i want in debug mode to see other effects too
#ifndef _DEBUG
	if( p_victim && p_victim->bInvincible )
		return SPELL_DID_HIT_IMMUNE;
#endif

	/*************************************************************************/
	/* Check if the target is immune to this mechanic                        */
	/*************************************************************************/
	if(u_victim->MechanicsDispels[GetProto()->MechanicsType])
	{
		// Immune - IF, and ONLY IF, there is no damage component!
		bool no_damage_component = true;
		for( int x = 0 ; x <= 2 ; x ++ )
		{
			if( GetProto()->Effect[x] == SPELL_EFFECT_SCHOOL_DAMAGE
				|| GetProto()->Effect[x] == SPELL_EFFECT_WEAPON_PERCENT_DAMAGE
				|| GetProto()->Effect[x] == SPELL_EFFECT_WEAPON_DAMAGE
				|| GetProto()->Effect[x] == SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL
//				|| GetProto()->Effect[x] == SPELL_EFFECT_DUMMY
				|| ( GetProto()->Effect[x] == SPELL_EFFECT_APPLY_AURA && GetProto()->EffectApplyAuraName[x] == SPELL_AURA_PERIODIC_DAMAGE )
				)
			{
				no_damage_component = false;
				break;
			}
		}
		if( no_damage_component )
			return SPELL_DID_HIT_IMMUNE; // Moved here from Spell::CanCast
	}

	/************************************************************************/
	/* Check if the target has a % resistance to this mechanic              */
	/************************************************************************/
		/* Never mind, it's already done below. Lucky I didn't go through with this, or players would get double resistance. */

	/************************************************************************/
	/* Check if the spell is a melee attack and if it was missed/parried    */
	/************************************************************************/
	uint32 melee_test_result;
	if( GetProto()->is_melee_spell || GetProto()->is_ranged_spell )
	{
		uint32 _type;
		if( GetType() == SPELL_DMG_TYPE_RANGED )
			_type = RANGED;
		else
		{
			if (GetProto()->AttributesExC & FLAGS4_TYPE_OFFHAND)
				_type =  OFFHAND;
			else
				_type = MELEE;
		}

		melee_test_result = u_caster->GetSpellDidHitResult( u_victim, _type, GetProto() );
		if(melee_test_result != SPELL_DID_HIT_SUCCESS)
			return (uint8)melee_test_result;
	}

	/************************************************************************/
	/* Check if the spell is resisted.                                      */
	/************************************************************************/
	if( GetProto()->School == 0  && !GetProto()->MechanicsType )
		return SPELL_DID_HIT_SUCCESS;

	bool pvp =(p_caster && p_victim);

	if(pvp)
		lvldiff = p_victim->getLevel() - p_caster->getLevel();
	else
		lvldiff = u_victim->getLevel() - u_caster->getLevel();
	if (lvldiff < 0)
	{
		resistchance = baseresist[0] +lvldiff;
	}
	else
	{
		if(lvldiff < 3)
		{
				resistchance = baseresist[lvldiff];
		}
		else
		{
			if(pvp)
				resistchance = baseresist[2] + (((float)lvldiff-2.0f)*7.0f);
			else
				resistchance = baseresist[2] + (((float)lvldiff-2.0f)*11.0f);
		}
	}
	//check mechanical resistance
	//i have no idea what is the best pace for this code
	if( GetProto()->MechanicsType < MECHANIC_TOTAL )
	{
		if(p_victim)
			resistchance += p_victim->MechanicsResistancesPCT[GetProto()->MechanicsType];
		else
			resistchance += u_victim->MechanicsResistancesPCT[GetProto()->MechanicsType];
	}
	//rating bonus
	if( p_caster != NULL )
	{
		resistchance -= p_caster->CalcRating( PLAYER_RATING_MODIFIER_SPELL_HIT );
		resistchance -= p_caster->GetHitFromSpell();
	}

	if(p_victim && GetProto()->School != 0)
		resistchance += p_victim->m_resist_hit[ MOD_SPELL ];

	if( this->GetProto()->Effect[effindex] == SPELL_EFFECT_DISPEL && Need_SM_Apply(GetProto()) && u_caster)
	{
		SM_FFValue(u_victim->SM_FRezist_dispell,&resistchance,GetProto()->SpellGroupType);
		SM_PFValue(u_victim->SM_PRezist_dispell,&resistchance,GetProto()->SpellGroupType);
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		int spell_flat_modifers=0;
		int spell_pct_modifers=0;
		SM_FIValue(u_caster->SM_FRezist_dispell,&spell_flat_modifers,GetProto()->SpellGroupType);
		SM_FIValue(u_caster->SM_PRezist_dispell,&spell_pct_modifers,GetProto()->SpellGroupType);
		if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
			printf("!!!!!spell dipell resist mod flat %d , spell dipell resist mod pct %d , spell dipell resist %d, spell group %u\n",spell_flat_modifers,spell_pct_modifers,resistchance,GetProto()->SpellGroupType);
#endif
	}

	if(Need_SM_Apply(GetProto()) && u_caster)
	{
		float hitchance=0;
		SM_FFValue(u_caster->SM_FHitchance,&hitchance,GetProto()->SpellGroupType);
		resistchance -= hitchance;
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		float spell_flat_modifers=0;
		SM_FFValue(u_caster->SM_FHitchance,&spell_flat_modifers,GetProto()->SpellGroupType);
		if(spell_flat_modifers!=0 )
			printf("!!!!!spell to hit mod flat %f, spell resist chance %f, spell group %u\n",spell_flat_modifers,resistchance,GetProto()->SpellGroupType);
#endif
	}

	if (GetProto()->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY)
		resistchance = 0.0f;

	if(resistchance >= 100.0f)
		return SPELL_DID_HIT_RESIST;
	else
	{
		uint8 res;
		if(resistchance<=1.0)//resist chance >=1
			res =  (Rand(1.0f) ? SPELL_DID_HIT_RESIST : SPELL_DID_HIT_SUCCESS);
		else
			res =  (Rand(resistchance) ? SPELL_DID_HIT_RESIST : SPELL_DID_HIT_SUCCESS);

		if (res == SPELL_DID_HIT_SUCCESS) // proc handling. mb should be moved outside this function
		{
//			u_caster->HandleProc(PROC_ON_SPELL_LAND,target,GetProto());
		}

		return res;
	}

}
//generate possible target list for a spell. Use as last resort since it is not acurate
//this function makes a rough estimation for possible target !
//!!!disabled parts that were not tested !!
void Spell::GenerateTargets(SpellCastTargets *store_buff)
{
	float r = GetProto()->base_range_or_radius_sqr;
	if( Need_SM_Apply(GetProto()) && u_caster)
	{
		SM_FFValue(u_caster->SM_FRadius,&r,GetProto()->SpellGroupType);
		SM_PFValue(u_caster->SM_PRadius,&r,GetProto()->SpellGroupType);
	}
	uint32 cur;
	for(uint32 i=0;i<3;i++)
		for(uint32 j=0;j<2;j++)
		{
			if(j==0)
				cur = GetProto()->EffectImplicitTargetA[i];
			else // if(j==1)
				cur = GetProto()->EffectImplicitTargetB[i];
			switch(cur)
			{
				case EFF_TARGET_NONE:{
					//this is bad for us :(
					}break;
				case EFF_TARGET_SELF:{
						if(m_caster->IsUnit())
							store_buff->m_unitTarget = m_caster->GetGUID();
					}break;
					// need more research
				case 4:{ // dono related to "Wandering Plague", "Spirit Steal", "Contagion of Rot", "Retching Plague" and "Copy of Wandering Plague"
					}break;
				case EFF_TARGET_PET:
					{// Target: Pet
						if(p_caster && p_caster->GetSummon())
							store_buff->m_unitTarget = p_caster->GetSummon()->GetGUID();
					}break;
				case EFF_TARGET_SINGLE_ENEMY:// Single Target Enemy
				case 77:					// grep: i think this fits
				case 8: // related to Chess Move (DND), Firecrackers, Spotlight, aedm, Spice Mortar
				case EFF_TARGET_ALL_ENEMY_IN_AREA: // All Enemies in Area of Effect (TEST)
				case EFF_TARGET_ALL_ENEMY_IN_AREA_INSTANT: // All Enemies in Area of Effect instant (e.g. Flamestrike)
				case EFF_TARGET_ALL_ENEMIES_AROUND_CASTER:
				case EFF_TARGET_IN_FRONT_OF_CASTER:
				case EFF_TARGET_ALL_ENEMY_IN_AREA_CHANNELED:// All Enemies in Area of Effect(Blizzard/Rain of Fire/volley) channeled
				case 31:// related to scripted effects
				case 53:// Target Area by Players CurrentSelection()
				case 54:// Targets in Front of the Caster
					{
						if( p_caster != NULL )
						{
							Unit *selected = p_caster->GetMapMgr()->GetUnit(p_caster->GetSelection());
							if(isAttackable(p_caster,selected,!(GetProto()->c_is_flags & SPELL_FLAG_IS_TARGETINGSTEALTHED)))
								store_buff->m_unitTarget = p_caster->GetSelection();
						}
						else if( u_caster != NULL )
						{
							if(	u_caster->GetAIInterface()->GetNextTarget() &&
								isAttackable(u_caster,u_caster->GetAIInterface()->GetNextTarget(),!(GetProto()->c_is_flags & SPELL_FLAG_IS_TARGETINGSTEALTHED)) &&
								u_caster->GetDistanceSq(u_caster->GetAIInterface()->GetNextTarget()) <= r)
							{
								store_buff->m_unitTarget = u_caster->GetAIInterface()->GetNextTarget()->GetGUID();
							}
							if(u_caster->GetAIInterface()->getAITargetsCount() && u_caster->GetMapMgr())
							{
								//try to get most hated creature
								u_caster->GetAIInterface()->LockAITargets(true);
								TargetMap *m_aiTargets = u_caster->GetAIInterface()->GetAITargets();
								TargetMap::iterator itr;
								for(itr = m_aiTargets->begin(); itr != m_aiTargets->end();itr++)
								{
									Unit *hate_t = u_caster->GetMapMgr()->GetUnit( itr->first );
									if( /*m_caster->GetMapMgr()->GetUnit(itr->first->GetGUID()) &&*/
										hate_t &&
										hate_t->GetMapMgr() == m_caster->GetMapMgr() &&
										hate_t->isAlive() &&
										m_caster->GetDistanceSq(hate_t) <= r &&
										isAttackable(u_caster,hate_t,!(GetProto()->c_is_flags & SPELL_FLAG_IS_TARGETINGSTEALTHED))
										)
									{
										store_buff->m_unitTarget=itr->first;
										break;
									}
								}
								u_caster->GetAIInterface()->LockAITargets(false);
							}
						}
						//try to get a whatever target
						if(!store_buff->m_unitTarget)
						{
							store_buff->m_unitTarget=GetSinglePossibleEnemy(i);
						}
						//if we still couldn't get a target, check maybe we could use
//						if(!store_buff->m_unitTarget)
//						{
//						}
					}break;
					// spells like 17278:Cannon Fire and 21117:Summon Son of Flame A
				case 17: // A single target at a xyz location or the target is a possition xyz
				case 18:// Land under caster.Maybe not correct
					{
						store_buff->m_srcX=m_caster->GetPositionX();
						store_buff->m_srcY=m_caster->GetPositionY();
						store_buff->m_srcZ=m_caster->GetPositionZ();
						store_buff->m_targetMask |= TARGET_FLAG_SOURCE_LOCATION;
					}break;
				case EFF_TARGET_ALL_RAID:
					{
						Player* p = p_caster;
						if( p == NULL)
						{
							if( u_caster->IsCreature() && SafeCreatureCast( u_caster )->IsTotem() )
								p = SafePlayerCast( SafeCreatureCast( u_caster )->GetTotemOwner() );
						}
						if( p != NULL )
						{
							if(IsInrange(m_caster->GetPositionX(),m_caster->GetPositionY(),m_caster->GetPositionZ(),p,r))
							{
								store_buff->m_unitTarget = m_caster->GetGUID();
								break;
							}
							if( p->GetGroup() )
							{
								uint32 count = p->GetGroup()->GetSubGroupCount();
								for( uint8 k = 0; k < count; k++ )
								{
									SubGroup * subgroup = p->GetGroup()->GetSubGroup( k );
									if( subgroup )
									{
										p->GetGroup()->Lock();
										for(GroupMembersSet::iterator itr = subgroup->GetGroupMembersBegin(); itr != subgroup->GetGroupMembersEnd(); ++itr)
										{
											if(!(*itr)->m_loggedInPlayer || m_caster == (*itr)->m_loggedInPlayer)
												continue;
											if(IsInrange(m_caster->GetPositionX(),m_caster->GetPositionY(),m_caster->GetPositionZ(),(*itr)->m_loggedInPlayer,r))
											{
												store_buff->m_unitTarget = (*itr)->m_loggedInPlayer->GetGUID();
												break;
											}
										}
										p->GetGroup()->Unlock();
									}
								}
							}
						}
					}break;
				case EFF_TARGET_ALL_PARTY_AROUND_CASTER:
					{// All Party Members around the Caster in given range NOT RAID!
						Player* p = p_caster;
						if( p == NULL)
						{
							if( u_caster->IsCreature() && SafeCreatureCast( u_caster )->IsTotem() )
								p = SafePlayerCast( SafeCreatureCast( u_caster )->GetTotemOwner() );
						}
						if( p != NULL )
						{
							if(IsInrange(m_caster->GetPositionX(),m_caster->GetPositionY(),m_caster->GetPositionZ(),p,r))
							{
								store_buff->m_unitTarget = m_caster->GetGUID();
								break;
							}
							SubGroup * subgroup = p->GetGroup() ?
								p->GetGroup()->GetSubGroup(p->GetSubGroup()) : 0;

							if(subgroup)
							{
								p->GetGroup()->Lock();
								for(GroupMembersSet::iterator itr = subgroup->GetGroupMembersBegin(); itr != subgroup->GetGroupMembersEnd(); ++itr)
								{
									if(!(*itr)->m_loggedInPlayer || m_caster == (*itr)->m_loggedInPlayer)
										continue;
									if(IsInrange(m_caster->GetPositionX(),m_caster->GetPositionY(),m_caster->GetPositionZ(),(*itr)->m_loggedInPlayer,r))
									{
										store_buff->m_unitTarget = (*itr)->m_loggedInPlayer->GetGUID();
										break;
									}
								}
								p->GetGroup()->Unlock();
							}
						}

/*						if ( u_caster != NULL && u_caster->IsCreature() )
						{
							//target friendly npcs
							for( std::set<Object*>::iterator itr = u_caster->GetInRangeSameFactsSetBegin(); itr != u_caster->GetInRangeSameFactsSetEnd(); itr++ )
							{
								if ( (*itr) != NULL && ((*itr)->GetTypeId() == TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->IsInWorld() && ((Unit*)*itr)->isAlive() && IsInrange(u_caster, (*itr), r) )
								{
									store_buff->m_unitTarget = (*itr)->GetGUID();
									break;
								}
							}
						}*/
					}break;
				case EFF_TARGET_SINGLE_FRIEND:
				case 45:// Chain,!!only for healing!! for chain lightning =6
				case 57:// Targeted Party Member
					{// Single Target Friend
						if( p_caster != NULL )
						{
							if(isFriendly(p_caster,p_caster->GetMapMgr()->GetUnit(p_caster->GetSelection())))
								store_buff->m_unitTarget = p_caster->GetSelection();
							else store_buff->m_unitTarget = p_caster->GetGUID();
						}
						else if( u_caster != NULL )
						{
							if(u_caster->GetUInt64Value(UNIT_FIELD_CREATEDBY))
								store_buff->m_unitTarget = u_caster->GetUInt64Value(UNIT_FIELD_CREATEDBY);
							 else
							 {
								//target friendly npcs
/*								for( std::set<Object*>::iterator itr = u_caster->GetInRangeSameFactsSetBegin(); itr != u_caster->GetInRangeSameFactsSetEnd(); itr++ )
								{
									if ( (*itr) != NULL && ((*itr)->GetTypeId() == TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->IsInWorld() && ((Unit*)*itr)->isAlive() && IsInrange(u_caster, (*itr), r) )
									{

										//few additional checks
										if (IsHealingSpell(GetProto()) && ((Unit*)*itr)->GetHealthPct() == 100 && !((Unit*)*itr)->HasAura(GetProto()->Id) 
										//!((Unit*)*itr)->HasActiveAura(GetProto()->Id, m_caster->GetGUID())
								 )
											continue;

										//check if an aura is being applied, and check if it already exists
										bool applies_aura=false;
										for (int i=0; i<3; i++)
										{
											if (GetProto()->Effect[i] == SPELL_EFFECT_APPLY_AURA || GetProto()->Effect[i] == SPELL_EFFECT_APPLY_AREA_AURA)
											{
												applies_aura=true;
												break;
											}
										}

										//majority of healing spells stack, infact I think they all do as of 2.0.1
										if (!IsHealingSpell(GetProto()) && applies_aura && ((Unit*)*itr)->HasAura(GetProto()->Id))
											continue;


										store_buff->m_unitTarget = (*itr)->GetGUID();
										break;
									 }
								}*/
							}
						}
					}break;
				case EFF_TARGET_GAMEOBJECT:
					{
						if(p_caster && p_caster->GetSelection())
							store_buff->m_unitTarget = p_caster->GetSelection();
					}break;
				case EFF_TARGET_DUEL:
					{// Single Target Friend Used in Duel
						if(p_caster && p_caster->DuelingWith && p_caster->DuelingWith->isAlive() && IsInrange(p_caster,p_caster->DuelingWith,r))
							store_buff->m_unitTarget = p_caster->GetSelection();
					}break;
				case EFF_TARGET_GAMEOBJECT_ITEM:{// Gameobject/Item Target
						//shit
					}break;
				case 27:{ // target is owner of pet
					// please correct this if not correct does the caster variablen need a Pet caster variable?
						if(u_caster && u_caster->IsPet())
							store_buff->m_unitTarget = SafePetCast( u_caster )->GetPetOwner()->GetGUID();
					}break;
				case EFF_TARGET_MINION:
				case 73:
					{// Minion Target
						if(m_caster->GetUInt64Value(UNIT_FIELD_SUMMON) == 0)
							store_buff->m_unitTarget = m_caster->GetGUID();
						else store_buff->m_unitTarget = m_caster->GetUInt64Value(UNIT_FIELD_SUMMON);
					}break;
				case 33://Party members of totem, inside given range
				case EFF_TARGET_SINGLE_PARTY:// Single Target Party Member
				case EFF_TARGET_ALL_PARTY: // all Members of the targets party
					{
						Player *p=NULL;
						if( p_caster != NULL )
								p = p_caster;
						else if( u_caster->IsCreature() && SafeCreatureCast( u_caster )->IsTotem() )
								p = SafePlayerCast( SafeCreatureCast( u_caster )->GetTotemOwner() );
						if( p_caster != NULL )
						{
							if(IsInrange(m_caster->GetPositionX(),m_caster->GetPositionY(),m_caster->GetPositionZ(),p,r))
							{
								store_buff->m_unitTarget = p->GetGUID();
								break;
							}
							SubGroup * pGroup = p_caster->GetGroup() ?
								p_caster->GetGroup()->GetSubGroup(p_caster->GetSubGroup()) : 0;

							if( pGroup )
							{
								p_caster->GetGroup()->Lock();
								for(GroupMembersSet::iterator itr = pGroup->GetGroupMembersBegin();
									itr != pGroup->GetGroupMembersEnd(); ++itr)
								{
									if(!(*itr)->m_loggedInPlayer || p == (*itr)->m_loggedInPlayer)
										continue;
									if(IsInrange(m_caster->GetPositionX(),m_caster->GetPositionY(),m_caster->GetPositionZ(),(*itr)->m_loggedInPlayer,r))
									{
										store_buff->m_unitTarget = (*itr)->m_loggedInPlayer->GetGUID();
										break;
									}
								}
								p_caster->GetGroup()->Unlock();
							}
						}

/*						if ( u_caster != NULL && u_caster->IsCreature() )
						{
							//target friendly npcs
							for( std::set<Object*>::iterator itr = u_caster->GetInRangeSameFactsSetBegin(); itr != u_caster->GetInRangeSameFactsSetEnd(); itr++ )
							{
								if ( (*itr) != NULL && ((*itr)->GetTypeId() == TYPEID_UNIT || (*itr)->GetTypeId() == TYPEID_PLAYER) && (*itr)->IsInWorld() && ((Unit*)*itr)->isAlive() && IsInrange(u_caster, (*itr), r) )								{
									store_buff->m_unitTarget = (*itr)->GetGUID();
									break;
								}
							}
						}*/
					}break;
				case 38:{//Dummy Target
					//have no idea
					}break;
				case EFF_TARGET_SELF_FISHING://Fishing
				case 46://Unknown Summon Atal'ai Skeleton
				case 47:// Portal
				case 52:	// Lightwells, etc
					{
						store_buff->m_unitTarget = m_caster->GetGUID();
					}break;
				case 40://Activate Object target(probably based on focus)
				case EFF_TARGET_TOTEM_EARTH:
				case EFF_TARGET_TOTEM_WATER:
				case EFF_TARGET_TOTEM_AIR:
				case EFF_TARGET_TOTEM_FIRE:// Totem
					{
						if( p_caster != NULL )
						{
							uint32 slot = cur - EFF_TARGET_TOTEM_EARTH;
							if( slot < 4 && p_caster->m_TotemSlots[slot] != 0 )
								store_buff->m_unitTarget = p_caster->m_TotemSlots[slot]->GetGUID();
						}
					}break;
				case 61:{ // targets with the same group/raid and the same class
					//shit again
				}break;
				case EFF_TARGET_ALL_FRIENDLY_IN_AREA:{

				}break;

			}//end switch
		}//end for
	if(store_buff->m_unitTarget)
		store_buff->m_targetMask |= TARGET_FLAG_UNIT;
	if(store_buff->m_srcX)
		store_buff->m_targetMask |= TARGET_FLAG_SOURCE_LOCATION;
	if(store_buff->m_destX)
		store_buff->m_targetMask |= TARGET_FLAG_DEST_LOCATION;
}//end function

uint8 Spell::prepare( SpellCastTargets * targets )
{
	uint8 ccr;

	//what about passive spells casted on player on login ?
//	if( !m_caster->IsInWorld() )
//	{
//		sLog.outDebug("Object "I64FMT" is casting Spell ID %u while not in World", m_caster->GetGUID(), GetProto()->Id);
//		SpellPool.PooledDelete( this );	//prepare early exit, cast / finish / cancel is not called
//		return SPELL_FAILED_DONT_REPORT;
//	}
	if( IsSpellDisabled( GetProto() ) )
	{ 
		SpellPool.PooledDelete( this ); //prepare early exit, cast / finish / cancel is not called
		return SPELL_FAILED_SPELL_UNAVAILABLE;
	}
	if( GetProto()->RequiredPlayerClass 
		&& m_caster->IsUnit() 
		&& ( GetProto()->RequiredPlayerClass & (1 << SafeUnitCast(m_caster)->getClass() ) ) == 0 )
	{ 
		SpellPool.PooledDelete( this ); //prepare early exit, cast / finish / cancel is not called
		return SPELL_FAILED_SPELL_UNAVAILABLE;
	}

	//check if this spell is a non player spell and report the usage of it for GMs
	if( GetProto()->spell_skilline[0] == 0
		&& m_triggeredSpell == false
		&& p_caster && p_caster->GetSession() && p_caster->GetSession()->GetPlayer() && p_caster->GetSession()->HasPermissions() && p_caster->GetMapMgr() )
	{
		Unit *target = p_caster->GetMapMgr()->GetUnit( targets->m_unitTarget );
		if( target && target->IsPlayer() )
			sGMLog.writefromsession(p_caster->GetSession(),"Casted non player spell %u -> %s on player %s",GetProto()->Id, GetProto()->Name, SafePlayerCast(target)->GetName() );
		else if( target && target->IsCreature() && (SafeCreatureCast(target))->GetCreatureInfo() )
			sGMLog.writefromsession(p_caster->GetSession(),"Casted non player spell %u -> %s on creature %s",GetProto()->Id, GetProto()->Name,SafeCreatureCast(target)->GetCreatureInfo()->Name );
		else 
			sGMLog.writefromsession(p_caster->GetSession(),"Casted non player spell %u -> %s on wtf no targets ?",GetProto()->Id, GetProto()->Name );
	}

	// In case spell got cast from a script check fear/wander states
	if (!p_caster && u_caster && u_caster->GetAIInterface())
	{
		AIInterface *ai = u_caster->GetAIInterface();
		if (ai->getAIState() == STATE_FEAR || ai->getAIState() == STATE_WANDER)
		{ 
			SpellPool.PooledDelete( this ); //prepare early exit, cast / finish / cancel is not called
			return SPELL_FAILED_NOT_READY;
		}
	}

	m_targets = *targets;

	if( m_triggeredSpell || ( p_caster != NULL && p_caster->CastTimeCheat ) )
		m_castTime = 0;
	else
	{
		m_castTime = GetCastTime( dbcSpellCastTime.LookupEntry( GetProto()->CastingTimeIndex ) );

		if( m_castTime && Need_SM_Apply(GetProto()) && u_caster != NULL )
		{
			SM_FIValue( u_caster->SM_FCastTime, (int32*)&m_castTime, GetProto()->SpellGroupType );
			SM_PIValue( u_caster->SM_PCastTime, (int32*)&m_castTime, GetProto()->SpellGroupType );
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
			int spell_flat_modifers=0;
			int spell_pct_modifers=0;
			SM_FIValue(u_caster->SM_FCastTime,&spell_flat_modifers,GetProto()->SpellGroupType);
			SM_FIValue(u_caster->SM_PCastTime,&spell_pct_modifers,GetProto()->SpellGroupType);
			if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
				printf("!!!!!spell casttime mod flat %d , spell casttime mod pct %d , spell casttime %d, spell group %u\n",spell_flat_modifers,spell_pct_modifers,m_castTime,GetProto()->SpellGroupType);
#endif
		}

		// handle MOD_CAST_TIME
		if( m_castTime > 0 && u_caster != NULL)
			m_castTime = float2int32( m_castTime * u_caster->GetSpellHaste() );
	}

	if( p_caster != NULL )
	{
		if( p_caster->cannibalize )
		{
			sEventMgr.RemoveEvents( p_caster, EVENT_CANNIBALIZE );
			p_caster->SetUInt32Value( UNIT_NPC_EMOTESTATE, 0 );
			p_caster->cannibalize = false;
		}
	}

	//let us make sure cast_time is within decent range
	//this is a hax but there is no spell that has more then 10 minutes cast time

	if( m_castTime < 0 )
		m_castTime = 0;
	else if( m_castTime > 60 * 10 * 1000)
		m_castTime = 60 * 10 * 1000; //we should limit cast time to 10 minutes right ?

	m_timer = m_castTime;

	//if( p_caster != NULL )
	//   m_castTime -= 100;	  // session update time


	if( !m_triggeredSpell && p_caster != NULL && p_caster->CooldownCheat )
		p_caster->ClearCooldownForSpell( GetProto()->Id );

	m_spellState = SPELL_STATE_PREPARING;

	if( m_triggeredSpell )
		cancastresult = SPELL_CANCAST_OK;
	else
		cancastresult = CanCast(false);

	//sLog.outString( "CanCast result: %u. Refer to SpellFailure.h to work out why." , cancastresult );

	ccr = cancastresult;
	if( cancastresult != SPELL_CANCAST_OK )
	{
		SendCastResult( cancastresult );

		if( m_triggeredSpell == false )	//do not cancel channeled spells by triggered spells
		{
			if( m_triggeredByAura )
			{
				SendChannelUpdate( 0 );
				if( u_caster != NULL )
					u_caster->RemoveAura( m_triggeredByAura );
			}
			else 
			{
				// HACK, real problem is the way spells are handled
				// when a spell is channeling and a new spell is casted
				// that is a channeling spell, but not triggert by a aura
				// the channel bar/spell is bugged
				if( u_caster && u_caster->GetUInt64Value( UNIT_FIELD_CHANNEL_OBJECT) > 0 && u_caster->GetCurrentSpell() )
				{
					u_caster->GetCurrentSpell()->cancel();
					SendChannelUpdate( 0 );
					cancel();
					SpellPool.PooledDelete( this ); //prepare early exit, cast / finish / cancel is not called
					sLog.outDebug("PrepareCast: Already channeling");
					return ccr;
				}
			}
		}
		finish();
		sLog.outDebug("PrepareCast: Cannot cast it");
		return ccr;
	}
	else
	{
		if( p_caster != NULL 
			&& p_caster->IsStealth() 
			&& (m_spellInfo->AttributesEx & ATTRIBUTESEX_NOT_BREAK_STEALTH) == 0
//			&& (m_spellInfo->c_is_flags & SPELL_FLAG_IS_HEALING) == 0
			&& (m_spellInfo->Attributes & ATTRIBUTES_PASSIVE) == 0
			&& (pSpellId == 0 || dbcSpell.LookupEntry(pSpellId)->Attributes & ATTRIBUTES_PASSIVE ) == 0
			)
		{
			p_caster->RemoveAura(p_caster->m_stealth);
			p_caster->m_stealth = 0;
		}

		SendSpellStart();

		// start cooldown handler
		if( p_caster != NULL && !p_caster->CastTimeCheat && !m_triggeredSpell )
		{
			AddStartCooldown();
		}

		if( i_caster == NULL )
		{
			if( p_caster != NULL && m_timer > 0 && !m_triggeredSpell )
				p_caster->delayAttackTimer( m_timer + 1000 );
				//p_caster->setAttackTimer(m_timer + 1000, false);
		}

		// aura state removal
		if( GetProto()->CasterAuraState )
			u_caster->RemoveFlag( UNIT_FIELD_AURASTATE, GetProto()->CasterAuraState );
	}

	//instant cast(or triggered) and not channeling
	if( u_caster != NULL && ( m_castTime > 0 || GetProto()->ChannelInterruptFlags ) && !m_triggeredSpell )
	{
		m_castPositionX = m_caster->GetPositionX();
		m_castPositionY = m_caster->GetPositionY();
		m_castPositionZ = m_caster->GetPositionZ();

		u_caster->castSpell( this );
	}
	else
	{
		cast( false );
	}

	return ccr;
}

void Spell::cancel()
{
	if (m_spellState == SPELL_STATE_FINISHED)
	{ 
		return;
	}

	//avoid multiple cancels
	if( u_caster != NULL )
		u_caster->SetCurrentSpell( NULL );

	SendInterrupted(0);
	SendCastResult(SPELL_FAILED_INTERRUPTED);

	if(m_spellState == SPELL_STATE_CASTING)
	{
		if( u_caster != NULL )
			u_caster->RemoveAura( GetProto()->Id );

		if(m_timer > 0 || m_Delayed)
		{
			if(p_caster && p_caster->IsInWorld())
			{
				Unit *pTarget = p_caster->GetMapMgr()->GetUnit(m_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT));
				if(!pTarget)
					pTarget = p_caster->GetMapMgr()->GetUnit(p_caster->GetSelection());

				if(pTarget)
				{
					pTarget->RemoveAura(GetProto()->Id, m_caster->GetGUID());
				}
				if(m_AreaAura)//remove of blizz and shit like this
				{

					DynamicObject* dynObj=m_caster->GetMapMgr()->GetDynamicObject(m_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT));
					if(dynObj)
						dynObj->Remove();
				}

				if(p_caster->GetSummonedObject())
				{
					if(p_caster->GetSummonedObject()->IsInWorld())
						p_caster->GetSummonedObject()->RemoveFromWorld(true);
					// for now..
					ASSERT(p_caster->GetSummonedObject()->GetTypeId() == TYPEID_GAMEOBJECT);
					sGarbageCollection.AddObject( p_caster->GetSummonedObject() );
					p_caster->SetSummonedObject(NULL);
				}
				if (m_timer > 0)
					p_caster->delayAttackTimer(-m_timer);
//				p_caster->setAttackTimer(1000, false);
			 }
		}
	}
	SendChannelUpdate(0);

	//m_spellState = SPELL_STATE_FINISHED;

	// prevent memory corruption. free it up later.
	// if this is true it means we are currently in the cast() function somewhere else down the stack
	// (recursive spells) and we don't wanna have this class delete'd when we return to it.
	// at the end of cast() it will get freed anyway.
	if( !m_isCasting )
		finish();
}

void Spell::AddCooldown()
{
	Player *tp_caster;
	if( p_caster )
		tp_caster = p_caster;
	else if( u_caster->IsPet() )
		tp_caster = SafePetCast( u_caster )->GetPetOwner();
	else
		tp_caster = NULL;
	if( tp_caster != NULL )
		tp_caster->Cooldown_Add( GetProto(), i_caster );
}

void Spell::AddStartCooldown()
{
	Player *tp_caster;
	if( p_caster )
		tp_caster = p_caster;
	else if( u_caster->IsPet() )
		tp_caster = SafePetCast( u_caster )->GetPetOwner();
	else
		tp_caster = NULL;
	if( tp_caster != NULL )
		tp_caster->Cooldown_AddStart( GetProto() );
}

void Spell::cast(bool check)
{
	if( duelSpell && (
		( p_caster != NULL && p_caster->GetDuelState() != DUEL_STATE_STARTED ) ||
		( u_caster != NULL && u_caster->IsPet() && SafePetCast( u_caster )->GetPetOwner() && SafePetCast( u_caster )->GetPetOwner()->GetDuelState() != DUEL_STATE_STARTED ) ) )
	{
		// Can't cast that!
		SendInterrupted( SPELL_FAILED_TARGET_FRIENDLY );
		finish();
		sLog.outDebug("SpellCast: Friendly target");
		return;
	}

	if( p_caster )
		sLog.outDebug("Spell::cast %u(%s), Player: %u", GetProto()->Id,GetProto()->Name, m_caster->GetLowGUID());
	else
		sLog.outDebug("Spell::cast %u(%s), Unit: %u", GetProto()->Id,GetProto()->Name, m_caster->GetLowGUID());

	if(check)
		cancastresult = CanCast(true);
	else
		cancastresult = SPELL_CANCAST_OK;

	if(cancastresult == SPELL_CANCAST_OK)
	{
		if( GetProto()->Attributes & ATTRIBUTE_ON_NEXT_ATTACK)
		{
			if(!m_triggeredSpell)
			{
				// on next attack - we don't take the mana till it actually attacks.
				if(!HasPower())
				{
					SendInterrupted(SPELL_FAILED_NO_POWER);
					finish();
					sLog.outDebug("SpellCast: Not enough power");
					return;
				}
			}
			else
			{
				// this is the actual spell cast
				if(!TakePower())	// shouldn't happen
				{
					SendInterrupted(SPELL_FAILED_NO_POWER);
					finish();
					return;
				}
			}
		}
		else
		{
			if(!m_triggeredSpell)
			{
				if(!TakePower()) //not enough mana
				{
					//sLog.outDebug("Spell::Not Enough Mana");
					SendInterrupted(SPELL_FAILED_NO_POWER);
					finish();
					sLog.outDebug("SpellCast: Not enough power");
					return;
				}
				//this needs to be rewriten when we support vehicle spells. Right now is to avoid passengers stealthing and stuff
				if( p_caster )
					p_caster->ExitVehicle();
			}
		}

#ifdef _DEBUG
		uint32 total_targets_count = 0;
#endif
		for(uint32 i=0;i<3;i++)
        {
			if( GetProto()->Effect[i] && GetProto()->Effect[i] != SPELL_EFFECT_PERSISTENT_AREA_AURA)
			{
				 FillTargetMap(i);
#ifdef _DEBUG
				total_targets_count += (uint32)m_targetUnits[i].size();
#endif
			}
        }
#ifdef _DEBUG
		if( total_targets_count == 0 )
			sLog.outDebug("SpellCast: Warning this spell could not find any targets ( id = %u )",GetProto()->Id );
#endif

#ifdef FORCED_GM_TRAINEE_MODE
		if( p_caster && p_caster->GetSession() && p_caster->GetSession()->HasPermissions() && !p_caster->GetSession()->HasGMPermissions() && m_targetUnits[0].size() && *(m_targetUnits[0].begin()) != p_caster->GetGUID() )
		{
			finish();
			return;
		}
#endif

		SendCastResult(cancastresult);
		if(cancastresult != SPELL_CANCAST_OK)
		{
			finish();
			sLog.outDebug("SpellCast: Cannot cast it for some reason");
			return;
		}

		m_isCasting = true;

		//sLog.outString( "CanCastResult: %u" , cancastresult );
		if(!m_triggeredSpell)
			AddCooldown();

		if( p_caster )
		{
			if( GetProto()->NameHash == SPELL_HASH_SLAM)
			{
				/* slam - reset attack timer */
				p_caster->setAttackTimer( 0, true );
				p_caster->setAttackTimer( 0, false );
			}
			else if( m_spellInfo->NameHash == SPELL_HASH_VICTORY_RUSH )
				p_caster->RemoveFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_LASTKILLWITHHONOR);
			else if( GetProto()->NameHash == SPELL_HASH_HOLY_LIGHT || GetProto()->NameHash == SPELL_HASH_FLASH_OF_LIGHT)
			{
			   p_caster->RemoveAura(53672);
               p_caster->RemoveAura(54149);
			}

			/*if( p_caster->IsStealth() && !(GetProto()->AttributesEx & ATTRIBUTESEX_NOT_BREAK_STEALTH)
				 && GetProto()->Id != 1 ) //check spells that get trigger spell 1 after spell loading
			{
				// talents procing - don't remove stealth either 
				if (!(GetProto()->Attributes & ATTRIBUTES_PASSIVE) &&
					!( pSpellId && dbcSpell.LookupEntry(pSpellId)->Attributes & ATTRIBUTES_PASSIVE ) )
				{
					p_caster->RemoveAura(p_caster->m_stealth);
					p_caster->m_stealth = 0;
				}
			} */
			if( p_caster->IsStealth() 
				&& (m_spellInfo->AttributesEx & ATTRIBUTESEX_NOT_BREAK_STEALTH) == 0
//				&& (m_spellInfo->c_is_flags & SPELL_FLAG_IS_HEALING) == 0
				&& (m_spellInfo->Attributes & ATTRIBUTES_PASSIVE) == 0
				&& (pSpellId == 0 || dbcSpell.LookupEntry(pSpellId)->Attributes & ATTRIBUTES_PASSIVE ) == 0
				)
			{
				p_caster->RemoveAura(p_caster->m_stealth);
				p_caster->m_stealth = 0;
			}

			// special case battleground additional actions
			if(p_caster->m_bg)
			{
				// SOTA Gameobject spells
				if (p_caster->m_bg->GetType() == BATTLEGROUND_STRAND_OF_THE_ANCIENT)
				{
					StrandOfTheAncient * sota = static_cast<StrandOfTheAncient *>(p_caster->m_bg);
					// Transporter platforms
					if (GetProto()->Id == 54640)
						sota->OnPlatformTeleport(p_caster);
				}
				// warsong gulch & eye of the storm flag pickup check
				// also includes check for trying to cast stealth/etc while you have the flag
				switch(GetProto()->Id)
				{
					case 21651:
						// Arathi Basin opening spell, remove stealth, invisibility, etc.
						p_caster->RemoveStealth();
						p_caster->RemoveInvisibility();
						p_caster->RemoveAllAuraByNameHash(SPELL_HASH_DIVINE_SHIELD);
						p_caster->RemoveAllAuraByNameHash(SPELL_HASH_DIVINE_PROTECTION);
						p_caster->RemoveAllAuraByNameHash(SPELL_HASH_BLESSING_OF_PROTECTION);
						break;
					case 23333:
					case 23335:
					case 34976:
						// if we're picking up the flag remove the buffs
						p_caster->RemoveStealth();
						p_caster->RemoveInvisibility();
						p_caster->RemoveAllAuraByNameHash(SPELL_HASH_DIVINE_SHIELD);
						p_caster->RemoveAllAuraByNameHash(SPELL_HASH_DIVINE_PROTECTION);
						p_caster->RemoveAllAuraByNameHash(SPELL_HASH_BLESSING_OF_PROTECTION);
						p_caster->ExitVehicle();
						break;
					// cases for stealth - etc
					// we can cast the spell, but we drop the flag (if we have it)
                    case 1784:		// Stealth rank 1
                    case 1785:		// Stealth rank 2
                    case 1786:		// Stealth rank 3
                    case 1787:		// Stealth rank 4
                    case 5215:		// Prowl rank 1
                    case 6783:		// Prowl rank 2
					case 9913:		// Prowl rank 3
					case 498:		// Divine protection
					case 5573:		// Unknown spell
					case 642:		// Divine shield
					case 1020:		// Unknown spell
					case 1022:		// Hand of Protection rank 1 (ex blessing of protection)
					case 5599:		// Hand of Protection rank 2 (ex blessing of protection)
                    case 10278:		// Hand of Protection rank 3 (ex blessing of protection)
					case 1856:		// Vanish rank 1
					case 1857:		// Vanish rank 2
					case 26889:		// Vanish rank 3
					case 45438:		// Ice block
					case 20580:		// Unknown spell
					case 58984:		// Shadowmeld
					case 17624:		// Petrification-> http://www.wowhead.com/?spell=17624
					case 66:		// Invisibility
						if(p_caster->m_bg->GetType() == BATTLEGROUND_WARSONG_GULCH)
						{
							if(p_caster->GetTeam() == 0)
								p_caster->RemoveAura(23333);	// ally player drop horde flag if they have it
							else
								p_caster->RemoveAura(23335); 	// horde player drop ally flag if they have it
						}
						if(p_caster->m_bg->GetType() == BATTLEGROUND_EYE_OF_THE_STORM)

							p_caster->RemoveAura(34976);	// drop the flag
						break;
				}
			}
		}

		/*SpellExtraInfo* sp = objmgr.GetSpellExtraData(GetProto()->Id);
		if(sp)
		{
			Unit *Target = objmgr.GetUnit(m_targets.m_unitTarget);
			if(Target)
				Target->RemoveBySpecialType(sp->specialtype, p_caster->GetGUID());
		}*/

		if(!((GetProto()->Attributes & ATTRIBUTE_ON_NEXT_ATTACK ) && m_triggeredSpell==false))//on next attack
		{
			SendSpellGo();

			//******************** SHOOT SPELLS ***********************
			//* Flags are now 1,4,19,22 (4718610) //0x480012

			if (GetProto()->AttributesExC & FLAGS4_PLAYER_RANGED_SPELLS && m_caster->IsPlayer() && m_caster->IsInWorld())
			{
                /// Part of this function contains a hack fix
                /// hack fix for shoot spells, should be some other resource for it
                //p_caster->SendSpellCoolDown(GetProto()->Id, GetProto()->RecoveryTime ? GetProto()->RecoveryTime : 2300);
				sStackWolrdPacket(data, SMSG_SPELL_COOLDOWN, 20 );
				data << GetProto()->Id;
				data << p_caster->GetNewGUID();
				data << uint32(GetProto()->RecoveryTime ? GetProto()->RecoveryTime : 2300);
				p_caster->GetSession()->SendPacket(&data);
			}
			else
			{
				if( GetProto()->ChannelInterruptFlags != 0 && m_triggeredSpell == false)
				{
					/*
					Channeled spells are handled a little differently. The five second rule starts when the spell's channeling starts; i.e. when you pay the mana for it.
					The rule continues for at least five seconds, and longer if the spell is channeled for more than five seconds. For example,
					Mind Flay channels for 3 seconds and interrupts your regeneration for 5 seconds, while Tranquility channels for 10 seconds
					and interrupts your regeneration for the full 10 seconds.
					*/

					uint32 channelDuration = GetDuration();
					if( u_caster )
						channelDuration = (uint32)(channelDuration * u_caster->GetSpellHaste());
					m_spellState = SPELL_STATE_CASTING;
					SendChannelStart(channelDuration);
					if( p_caster != NULL )
					{
						//Use channel interrupt flags here
						if( p_caster->GetSummon() && ( GetProto()->EffectImplicitTargetA[0] == EFF_TARGET_PET || GetProto()->EffectImplicitTargetB[0] == EFF_TARGET_PET ) )
							u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, p_caster->GetSummon()->GetGUID() );	//not sure if this would work for health funnel
						else if(m_targets.m_targetMask == TARGET_FLAG_DEST_LOCATION || m_targets.m_targetMask == TARGET_FLAG_SOURCE_LOCATION)
							u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, p_caster->GetSelection());
						else if( m_targets.m_targetMask == TARGET_FLAG_ITEM )
							u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, m_targets.m_itemTarget );
						else if(p_caster->GetSelection() == m_caster->GetGUID())
						{
							if(p_caster->GetSummon())
								u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, p_caster->GetSummon()->GetGUID());
							else if(m_targets.m_unitTarget)
								u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, m_targets.m_unitTarget);
							else
								u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, p_caster->GetSelection());
						}
						else
						{
							if(p_caster->GetSelection())
								u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, p_caster->GetSelection());
							else if(p_caster->GetSummon())
								u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, p_caster->GetSummon()->GetGUID());
							else if(m_targets.m_unitTarget)
								u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT, m_targets.m_unitTarget);
							else
							{
								m_isCasting = false;
								cancel();
								sLog.outDebug("SpellCast: missing channel target");
								return;
							}
						}
					}
					if(u_caster && u_caster->GetPowerType()==POWER_TYPE_MANA)
					{
						if(channelDuration <= 5000)
							u_caster->DelayPowerRegeneration(5000);
						else if( channelDuration != -1 ) //wtf infinit cast time ?
							u_caster->DelayPowerRegeneration(channelDuration);
					}
				}
			}

			std::vector<uint64>::iterator i, i2;

			// this is here to avoid double search in the unique list
			//bool canreflect = false, reflected = false;
			for(int j=0;j<3;j++)
			{
				switch(GetProto()->EffectImplicitTargetA[j])
				{
					case 6:
					case 22:
					case 24:
					case 25:
						SetCanReflect();
						break;
				}
				if(GetCanReflect())
					continue;
				else
					break;
			}

			if(!IsReflected() && GetCanReflect() && m_caster->IsInWorld())
			{
				for(i= UniqueTargets.begin();i != UniqueTargets.end();i++)
				{
					Unit *Target = m_caster->GetMapMgr()->GetUnit(*i);
					if(Target)
					{
					   SetReflected(Reflect(Target));
					}

					// if the spell is reflected
					if(IsReflected())
						break;
				}
			}
			else
				SetReflected(false);

			//uint32 spellid = GetProto()->Id;

			// we're much better to remove this here, because otherwise spells that change powers etc,
			// don't get applied.
			if(u_caster && !m_triggeredSpell && !m_triggeredByAura)
				u_caster->RemoveAurasByInterruptFlagButSkip(AURA_INTERRUPT_ON_CAST_SPELL, GetProto()->Id, GetProto()->NameHash);

            // if the spell is not reflected
			if(!IsReflected())
			{
				for(uint32 x=0;x<3;x++)
				{
                    // check if we actualy have a effect
					if( GetProto()->Effect[x])
					{
						if( GetProto()->Effect[x] == SPELL_EFFECT_PERSISTENT_AREA_AURA)
							HandleEffects(m_caster->GetGUID(),x);
						else if ( m_targetUnits[x].size() > 0 )
						{
							for(i= m_targetUnits[x].begin();i != m_targetUnits[x].end();)
                            {
								i2 = i++;
								HandleEffects((*i2),x);
                            }
						}
						else if( m_targets.m_itemTarget )
							HandleEffects( 0 , x );
						// Capt: The way this is done is NOT GOOD. Target code should be redone.
						else if( GetProto()->Effect[x] == SPELL_EFFECT_TELEPORT_UNITS ||
							     GetProto()->Effect[x] == SPELL_EFFECT_SUMMON ||
								 GetProto()->Effect[x] == SPELL_EFFECT_SUMMON_OBJECT_SLOT1 ||
								 GetProto()->Effect[x] == SPELL_EFFECT_SUMMON_OBJECT_SLOT2 ||
								 GetProto()->Effect[x] == SPELL_EFFECT_SUMMON_OBJECT_SLOT3 ||
								 GetProto()->Effect[x] == SPELL_EFFECT_SUMMON_OBJECT_SLOT4 ||
								 GetProto()->Effect[x] == SPELL_EFFECT_TRIGGER_SPELL
								 //not good damaging spells suck with this
								 //GetProto()->EffectImplicitTargetA[x] == EFF_TARGET_LOCATION_TO_SUMMON ||
								 //GetProto()->EffectImplicitTargetB[x] == EFF_TARGET_LOCATION_TO_SUMMON
								 )
                        {
							HandleEffects(m_caster->GetGUID(),x);
                        }
					}
				}

				/* don't call HandleAddAura unless we actually have auras... - Burlex*/
				if( GetProto()->EffectApplyAuraName[0] != 0 || GetProto()->EffectApplyAuraName[1] != 0 ||
				   GetProto()->EffectApplyAuraName[2] != 0)
				{
					hadEffect = true; // spell has had an effect (for item removal & possibly other things)

					for(i= UniqueTargets.begin();i != UniqueTargets.end();i++)
						HandleAddAura((*i));
				}
				// spells that proc on spell cast, some talents
				if(
					u_caster &&	// well units should also proc on cast
//					p_caster && 
					u_caster->IsInWorld())
				{
					for(i= UniqueTargets.begin();i != UniqueTargets.end();i++)
					{
						Unit * Target = u_caster->GetMapMgr()->GetUnit((*i));

						if(!Target)
							continue; //we already made this check, so why make it again ?

						//some spells simply do not have enough effect field so they cast another spell after suing up all 3 effects
						if( GetProto()->chained_cast )
						{
							Spell *spell = SpellPool.PooledNew();
							spell->Init( u_caster, GetProto()->chained_cast ,true, NULL);
							SpellCastTargets targets( (*i) );
							spell->prepare(&targets);
						}

						if(	( !m_triggeredSpell || (GetProto()->c_is_flags & SPELL_FLAG_IS_PROC_TRIGGER_PROC) ) && (GetProto()->c_is_flags & SPELL_FLAG_IS_DISABLE_OTHER_SPELL_CPROC) == 0 )
						{
							//p_caster->HandleProc(PROC_ON_CAST_SPELL,Target, GetProto());
							//Target->HandleProc(PROC_ON_SPELL_LAND_VICTIM,u_caster,GetProto());
							//zack : !!!!!! damage represents calculate effect last value and not some actual dmg !!!
							u_caster->HandleProc(PROC_ON_CAST_SPELL,Target, GetProto(), damage);
							Target->HandleProc(PROC_ON_SPELL_LAND_VICTIM,u_caster,GetProto(), damage);
						}

						Target->RemoveFlag(UNIT_FIELD_AURASTATE,GetProto()->TargetAuraState);
						if( Target->IsPlayer() )
						{
							//these are scripted a lot. But better then nothing to have them anywayz
							SafePlayerCast( Target )->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET,GetProto()->Id,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
							SafePlayerCast( Target )->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2,GetProto()->Id,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
						}
					}
					//!! this is required for Area or summon spells that might not have any targets but proc events
					if( UniqueTargets.size() == 0 && ( !m_triggeredSpell || (GetProto()->c_is_flags & SPELL_FLAG_IS_PROC_TRIGGER_PROC) ) )
						u_caster->HandleProc(PROC_ON_CAST_SPELL,u_caster, GetProto(), damage);
					if( p_caster )
					{
						p_caster->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL,GetProto()->Id,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
						p_caster->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL2,GetProto()->Id,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
					}
				}
			} /**/

			m_isCasting = false;

			if(m_spellState != SPELL_STATE_CASTING)
				finish();
		}
		else //this shit has nothing to do with instant, this only means it will be on NEXT melee hit
		{
			// we're much better to remove this here, because otherwise spells that change powers etc,
			// don't get applied.

			if(u_caster && !m_triggeredSpell && !m_triggeredByAura)
				u_caster->RemoveAurasByInterruptFlagButSkip(AURA_INTERRUPT_ON_CAST_SPELL, GetProto()->Id, GetProto()->NameHash);

			//not sure if it must be there...
			/*if( p_caster != NULL )
			{
				if(p_caster->m_onAutoShot)
				{
					p_caster->GetSession()->OutPacket(SMSG_CANCEL_AUTO_REPEAT);
					p_caster->GetSession()->OutPacket(SMSG_CANCEL_COMBAT);
					p_caster->m_onAutoShot = false;
				}
			}*/

			m_isCasting = false;
			SendCastResult(cancastresult);
			if( u_caster != NULL )
				u_caster->SetOnMeleeSpell(GetProto()->Id, extra_cast_number);

			finish();
		}
	}
	else
	{
		// cancast failed
		SendCastResult(cancastresult);
		finish();
	}

	//maybe some spells only trigger cooldown after expiration ?
	if( ( GetProto()->c_is_flags & SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE ) )
	{
		packetSMSG_COOLDOWN_EVENT data;
		data.spellid = GetProto()->Id;
		data.guid = m_caster->GetGUID();
		if( m_caster->IsPlayer() && SafePlayerCast( m_caster )->GetSession() )
			SafePlayerCast( m_caster )->GetSession()->OutPacket( SMSG_COOLDOWN_EVENT, sizeof( packetSMSG_COOLDOWN_EVENT ), &data );
	}
}

void Spell::AddTime(uint32 type)
{
	if( channel_delays >= 3 )
		return; //spells get delayed top 3 times in 303
	channel_delays++;
	if(u_caster && u_caster->IsPlayer())
	{
		if( GetProto()->InterruptFlags & CAST_INTERRUPT_ON_DAMAGE_TAKEN)
		{
			cancel();
			return;
		}
		if( Need_SM_Apply(GetProto()) && u_caster)
		{
			float ch=0;
			SM_FFValue(u_caster->SM_PNonInterrupt,&ch,GetProto()->SpellGroupType);
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
			float spell_pct_modifers=0;
			SM_FFValue(u_caster->SM_PNonInterrupt,&spell_pct_modifers,GetProto()->SpellGroupType);
			if(spell_pct_modifers!=0)
				printf("!!!!!spell interrupt chance mod pct %f , uninterrupt chance %f, spell group %u\n",spell_pct_modifers,ch,GetProto()->SpellGroupType);
#endif
			if(Rand(ch))
			{ 
				return;
			}
		}
		if( p_caster != NULL )
		{
			if(Rand(p_caster->SpellDelayResist[type]))
			{ 
				return;
			}
		}
		if(m_spellState==SPELL_STATE_PREPARING)
		{
			// no pushback for some spells
			if ((GetProto()->InterruptFlags & CAST_INTERRUPT_PUSHBACK) == 0)
			{ 
				return;
			}

			int32 delay = m_castTime/(3+channel_delays);
			m_timer+=delay;
			if(m_timer>m_castTime)
			{
				delay -= (m_timer - m_castTime);
				m_timer=m_castTime;
				if(delay<0)
					delay = 1;
			}

			sStackWolrdPacket(data,SMSG_SPELL_DELAYED,15);
			data << u_caster->GetNewGUID();
			data << uint32(delay);
			u_caster->SendMessageToSet(&data, true);

			if(!p_caster)
			{
				if(m_caster->GetTypeId() == TYPEID_UNIT)
					u_caster->GetAIInterface()->AddStopTime(delay);
			}
			//in case cast is delayed, make sure we do not exit combat
			else
			{
//				sEventMgr.ModifyEventTimeLeft(p_caster,EVENT_ATTACK_TIMEOUT,PLAYER_ATTACK_TIMEOUT_INTERVAL,true);
				// also add a new delay to offhand and main hand attacks to avoid cutting the cast short
				p_caster->delayAttackTimer(delay);
			}
		}
		else if( GetProto()->ChannelInterruptFlags != 48140)
		{
			int32 delay = GetDuration()/(2+channel_delays);
			m_timer-=delay;
			if(m_timer<0)
				m_timer=0;
			else
				p_caster->delayAttackTimer(-delay);

			m_Delayed = true;
			if(m_timer>0)
				SendChannelUpdate(m_timer);

		}
	}
}

void Spell::update(uint32 difftime)
{
	// skip cast if we're more than 2/3 of the way through
	// TODO: determine which spells can be casted while moving.
	// Client knows this, so it should be easy once we find the flag.
	// XD, it's already there!
	if( ( GetProto()->InterruptFlags & CAST_INTERRUPT_ON_MOVEMENT ) &&
		(((float)m_castTime / 1.5f) > (float)m_timer ) &&
//		float(m_castTime)/float(m_timer) >= 2.0f		&&
		(
		m_castPositionX != m_caster->GetPositionX() ||
		m_castPositionY != m_caster->GetPositionY() ||
		m_castPositionZ != m_caster->GetPositionZ()
		)
		)
	{
		if( u_caster != NULL )
		{
			if(u_caster->HasNoInterrupt() == 0 && GetProto()->EffectMechanic[1] != MECHANIC_INCAPACIPATED )
			{
				cancel();
				return;
			}
		}
	}

	if(m_cancelled)
	{
		cancel();
		return;
	}

	switch(m_spellState)
	{
	case SPELL_STATE_PREPARING:
		{
			//printf("spell::update m_timer %u, difftime %d, newtime %d\n", m_timer, difftime, m_timer-difftime);
			if((int32)difftime >= m_timer)
				cast(true);
			else
			{
				m_timer -= difftime;
				if((int32)difftime >= m_timer)
				{
					m_timer = 0;
					cast(true);
				}
			}


		} break;
	case SPELL_STATE_CASTING:
		{
			if(m_timer > 0)
			{
				if((int32)difftime >= m_timer)
					m_timer = 0;
				else
					m_timer -= difftime;
			}
			if(m_timer <= 0)
			{
				SendChannelUpdate(0);
				finish();
			}
		} break;
	}
}

void Spell::finish()
{
	/*
	//this will leak memory if we early exit ..somehow this check should be made somewhere else
	if (m_spellState == SPELL_STATE_FINISHED)
	{ 
		return;
	} */

	m_spellState = SPELL_STATE_FINISHED;
	if( u_caster != NULL )
	{
		u_caster->m_canMove = true;
		// mana           channeled                                                     power type is mana
		if(m_usesMana && (GetProto()->ChannelInterruptFlags == 0 && !m_triggeredSpell) && u_caster->GetPowerType()==POWER_TYPE_MANA)
		{
			/*
			Five Second Rule
			After a character expends mana in casting a spell, the effective amount of mana gained per tick from spirit-based regeneration becomes a ratio of the normal
			listed above, for a period of 5 seconds. During this period mana regeneration is said to be interrupted. This is commonly referred to as the five second rule.
			By default, your interrupted mana regeneration ratio is 0%, meaning that spirit-based mana regeneration is suspended for 5 seconds after casting.
			Several effects can increase this ratio, including:
			*/

			u_caster->DelayPowerRegeneration(5000);
		}
	}
	/* Mana Regenerates while in combat but not for 5 seconds after each spell */
	/* Only if the spell uses mana, will it cause a regen delay.
	   is this correct? is there any spell that doesn't use mana that does cause a delay?
	   this is for creatures as effects like chill (when they have frost armor on) prevents regening of mana	*/

	//moved to spellhandler.cpp -> remove item when click on it! not when it finishes

	//enable pvp when attacking another player with spells
	if( p_caster != NULL )
	{
		if (GetProto()->Attributes & ATTRIBUTES_STOP_ATTACK && p_caster->IsAttacking() )
		{
			p_caster->EventAttackStop();
			p_caster->smsg_AttackStop( p_caster->GetSelection() );
			p_caster->GetSession()->OutPacket( SMSG_CANCEL_COMBAT );
		}

		if(m_requiresCP && !GetSpellFailed())
		{
			if(p_caster->m_spellcomboPoints)
			{
				p_caster->m_comboPoints = p_caster->m_spellcomboPoints;
				p_caster->UpdateComboPoints(); //this will make sure we do not use any wrong values here
			}
			else
			{
				p_caster->NullComboPoints();
			}
		}
		if(m_Delayed)
		{
			Unit *pTarget = NULL;
			if( p_caster->IsInWorld() )
			{
				pTarget = p_caster->GetMapMgr()->GetUnit(m_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT));
				if(!pTarget)
					pTarget = p_caster->GetMapMgr()->GetUnit(p_caster->GetSelection());
			}

			if(pTarget)
			{
				pTarget->RemoveAura(GetProto()->Id, m_caster->GetGUID());
			}
		}
	}

	if( GetProto()->Effect[0] == SPELL_EFFECT_SUMMON_OBJECT ||
		GetProto()->Effect[1] == SPELL_EFFECT_SUMMON_OBJECT ||
		GetProto()->Effect[2] == SPELL_EFFECT_SUMMON_OBJECT)
		if( p_caster != NULL )
			p_caster->SetSummonedObject(NULL);
	/*
	Set cooldown on item
	*/
	if( i_caster && i_caster->GetOwner() && cancastresult == SPELL_CANCAST_OK && !GetSpellFailed() )
	{
			uint32 x;
		for(x = 0; x < 5; x++)
		{
			if(i_caster->GetProto()->Spells[x].Trigger == USE)
			{
				if(i_caster->GetProto()->Spells[x].Id)
					break;
			}
		}
		//these are tinker spells from engeneering ;) 
		if( x >= 5 )
		{
			if( p_caster )
				p_caster->Cooldown_Add( GetProto(), i_caster );
		}
		else
			i_caster->GetOwner()->Cooldown_AddItem( i_caster->GetProto() , x , GetProto()->Attributes & ATTRIBUTES_START_COOLDOWN_AFTER_COMBAT );
	}
	/*
	We set current spell only if this spell has cast time or is channeling spell
	otherwise it's instant spell and we delete it right after completion
	*/

	if( u_caster != NULL )
	{
		if(!m_triggeredSpell && (GetProto()->ChannelInterruptFlags || m_castTime>0))
			u_caster->SetCurrentSpell(NULL);
	}

	// Send Spell cast info to QuestMgr
	if( cancastresult == SPELL_CANCAST_OK && p_caster != NULL && p_caster->IsInWorld() )
	{
		// Taming quest spells are handled in SpellAuras.cpp, in SpellAuraDummy
		// OnPlayerCast shouldn't be called here for taming-quest spells, in case the tame fails (which is handled in SpellAuras)
		bool isTamingQuestSpell = false;
/*		uint32 tamingQuestSpellIds[] = { 19688, 19694, 19693, 19674, 19697, 19696, 19687, 19548, 19689, 19692, 19699, 19700, 30099, 30105, 30102, 30646, 30653, 30654, 0 };
		uint32* spellidPtr = tamingQuestSpellIds;
		while( *spellidPtr ) // array ends with 0, so this works
		{
			if( *spellidPtr == m_spellInfo->Id ) // it is a spell for taming beast quest
			{
				isTamingQuestSpell = true;
				break;
			}
			++spellidPtr;
		}*/
		// Don't call QuestMgr::OnPlayerCast for next-attack spells, either.  It will be called during the actual spell cast.
//		if( !(hasAttribute(ATTRIBUTE_ON_NEXT_ATTACK) && !m_triggeredSpell) && !isTamingQuestSpell )
		if( m_triggeredSpell == false )
		{
			uint32 numTargets = 0;
			TargetsList::iterator itr = UniqueTargets.begin();
			for(; itr != UniqueTargets.end(); ++itr)
			{
				if( GET_TYPE_FROM_GUID(*itr) == HIGHGUID_TYPE_UNIT )
				{
					++numTargets;
					sQuestMgr.OnPlayerCast(p_caster,GetProto()->Id,*itr);
				}
			}
			if( numTargets == 0 )
			{
				uint64 guid = p_caster->GetTargetGUID();
					sQuestMgr.OnPlayerCast( p_caster, GetProto()->Id, guid );
			}
		}
	}
	SpellPool.PooledDelete( this );
}

void Spell::SendCastResult(uint8 result)
{
	uint32 Extra = 0;
	if(result == SPELL_CANCAST_OK) 
	{ 
		return;
	}

	SetSpellFailed();

	if(!m_caster->IsInWorld()) 
	{ 
		return;
	}

	Player * plr = p_caster;

	if(!plr && u_caster)
		plr = u_caster->m_redirectSpellPackets;
	if(!plr) 
	{ 
		return;
	}

	// for some reason, the result extra is not working for anything, including SPELL_FAILED_REQUIRES_SPELL_FOCUS
	switch( result )
	{
	case SPELL_FAILED_REQUIRES_SPELL_FOCUS:
		Extra = GetProto()->RequiresSpellFocus;
		break;

	case SPELL_FAILED_REQUIRES_AREA:
		Extra = GetProto()->RequiresAreaId;
		if( GetProto()->RequiresAreaId > 0 )
		{
			AreaGroup *ag = dbcAreaGroup.LookupEntry( GetProto()->RequiresAreaId );
			if( ag )
			{
//				uint16 plrarea = plr->GetMapMgr()->GetAreaID( plr->GetPositionX(), plr->GetPositionY() );
				uint16 plrarea = sTerrainMgr.GetAreaID( plr->GetMapId(), plr->GetPositionX(), plr->GetPositionY(), plr->GetPositionZ() );
				for( uint8 i = 0; i < 7; i++ )
					if( ag->AreaId[i] != 0 && ag->AreaId[i] != plrarea )
					{	
						Extra = ag->AreaId[i];
						break;
					}
			}
		}
		break;

	case SPELL_FAILED_TOTEMS:
		Extra = GetProto()->Totem[1] ? GetProto()->Totem[1] : GetProto()->Totem[0];
		break;
	case SPELL_FAILED_ONLY_SHAPESHIFT:
		Extra = GetProto()->RequiredShapeShift;
		break;

	//case SPELL_FAILED_TOTEM_CATEGORY: seems to be fully client sided.
	}

	//plr->SendCastResult(GetProto()->Id, result, extra_cast_number, Extra);
	if( Extra )
	{
		packetSMSG_CASTRESULT_EXTRA pe;
		pe.SpellId = GetProto()->Id;
		pe.ErrorMessage = result;
		pe.MultiCast = extra_cast_number;
		pe.Extra = Extra;
		plr->GetSession()->OutPacket( SMSG_CAST_FAILED, sizeof( packetSMSG_CASTRESULT_EXTRA ), &pe );
	}
	else if( result == SPELL_FAILED_NOT_READY )
	{
		sStackWolrdPacket(data,SMSG_CAST_FAILED, 1+4+1+4+1+20);
		data << extra_cast_number;
		data << GetProto()->Id;
		data << uint8(SPELL_FAILED_NOT_READY);
		data << uint8(0);	//so which 0 is first ? no idea
		data << uint32(0);	//maybe this is cooldown remaining
		plr->GetSession()->SendPacket( &data );
	}
	else
	{
		packetSMSG_CASTRESULT pe;
		pe.SpellId = GetProto()->Id;
		pe.ErrorMessage = result;
		pe.MultiCast = extra_cast_number;
		plr->GetSession()->OutPacket( SMSG_CAST_FAILED, sizeof( packetSMSG_CASTRESULT ), &pe );
	}
}

// uint16 0xFFFF
enum SpellStartFlags
{
	//0x01
	SPELL_START_FLAG_DEFAULT = 0x02, // atm set as default flag
	//0x04
	//0x08
	//0x10
	SPELL_START_FLAG_RANGED = 0x20,
	//0x40
	//0x80
	//0x100
	//0x200
	//0x400
	//0x800
	//0x1000
	//0x2000
	//0x4000
	//0x8000
};

void Spell::SendSpellStart()
{
	// no need to send this on passive spells
	if( !m_caster->IsInWorld() 
		|| ( GetProto()->Attributes & ATTRIBUTES_PASSIVE )
		|| m_triggeredSpell
		//no point of sending visual packet if there is no visual about it
		//speed has spells like "shoot" which do have a visual effect after a while
		|| ( m_spellInfo->SpellVisual == 0 && m_spellInfo->speed == 0 )
		// X Msec cast is lost due to latency ? Don't worry, spell_go packet will handle the visual part
		// also note that most cast times are 1.5 second but due to hasting they might get to 1 sec cast time
		|| m_castTime <= 1100	
		)
		return;

	sStackWolrdPacket(data,SMSG_SPELL_START,500 );

	uint32 cast_flags = 2;

	if( GetType() == SPELL_DMG_TYPE_RANGED )
		cast_flags |= 0x20;

    // hacky yeaaaa
	if( GetProto()->Id == 8326 ) // death
		cast_flags = 0x0F;
	if (m_missileTravelTime)
		cast_flags |= 0x1006000E;
//	if (cast_flags & 0x20000)	//(missleflags << 16) ?
//		data << m_missilePitch << m_missileTravelTime;

	if( i_caster != NULL )
		data << i_caster->GetNewGUID() << u_caster->GetNewGUID();
	else
		data << m_caster->GetNewGUID() << m_caster->GetNewGUID();

	data << extra_cast_number; 
	data << GetProto()->Id;
	data << cast_flags;
	data << (uint32)m_castTime;

//	if( cast_flags & 0x04 )
		m_targets.write( data );
//	else
		data << (uint32) 0;	//client simply does not care most of the time ? There must be a flag for this

	if( GetType() == SPELL_DMG_TYPE_RANGED )
	{
		ItemPrototype* ip = NULL;
		if( GetProto()->Id == SPELL_RANGED_THROW ) // throw
		{
			if( p_caster != NULL )
			{
				Item *itm = p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_RANGED );
				if( itm != NULL )
				{
					ip = itm->GetProto();
					/* Throwing Weapon Patch by Supalosa
					p_caster->GetItemInterface()->RemoveItemAmt(it->GetEntry(),1);
					(Supalosa: Instead of removing one from the stack, remove one from durability)
					We don't need to check if the durability is 0, because you can't cast the Throw spell if the thrown weapon is broken, because it returns "Requires Throwing Weapon" or something.
					*/

					// burlex - added a check here anyway (wpe suckers :P)
					if( itm->GetDurability() > 0 )
					{
						itm->SetDurability( itm->GetDurability() - 1 );
						if( itm->GetDurability() == 0 )
							p_caster->ApplyItemMods( itm, EQUIPMENT_SLOT_RANGED, false, true );
					}
				}
				else
				{
					ip = ItemPrototypeStorage.LookupEntry( 2512 );	/*rough arrow*/
				}
			}
		}
#ifndef CATACLYSM_SUPPORT
		else if( GetProto()->AttributesExC & FLAGS4_PLAYER_RANGED_SPELLS )
		{
			if( p_caster != NULL )
				ip = ItemPrototypeStorage.LookupEntry( p_caster->GetUInt32Value( PLAYER_AMMO_ID ) );
			else
				ip = ItemPrototypeStorage.LookupEntry( 2512 );	/*rough arrow*/
		}
#endif
		if( ip != NULL )
			data << ip->DisplayInfoID << ip->InventoryType;
		else data << uint32( 0 ) << uint32 ( 0 ); 
	}

	m_caster->SendMessageToSet( &data, true );
}

/************************************************************************/
/* General Spell Go Flags, for documentation reasons                    */
/************************************************************************/
enum SpellGoFlags
{
	//seems to make server send 1 less byte at the end. Byte seems to be 0 and not sent on triggered spells
	//this is used only when server also sends power update to client
	//maybe it is regen related ?
	SPELL_GO_FLAGS_LOCK_PLAYER_CAST_ANIM	= 0x01,  //also do not send standstate update
	//0x02
	//0x04
	//0x08 //seems like all of these mean some spell anim state
	//0x10
	SPELL_GO_FLAGS_RANGED           = 0x20, //2 functions are called on 2 values
	//0x40
	//0x80
	SPELL_GO_FLAGS_ITEM_CASTER      = 0x100,
	SPELL_GO_FLAGS_UNK200			= 0x200, 
	SPELL_GO_FLAGS_EXTRA_MESSAGE    = 0x400, //TARGET MISSES AND OTHER MESSAGES LIKE "Resist"
	SPELL_GO_FLAGS_POWER_UPDATE		= 0x800, //seems to work hand in hand with some visual effect of update actually
	//0x1000
	SPELL_GO_FLAGS_UNK2000			= 0x2000, 
	SPELL_GO_FLAGS_UNK1000			= 0x1000, //no idea
	//0x4000
	SPELL_GO_FLAGS_UNK8000			= 0x8000, //seems to make server send extra 2 bytes before SPELL_GO_FLAGS_UNK1 and after SPELL_GO_FLAGS_UNK20000
	SPELL_GO_FLAGS_UNK20000			= 0x20000, //seems to make server send an uint32 after m_targets.write
	SPELL_GO_FLAGS_UNK40000			= 0x40000, //1 uint32. this is not confirmed but i have a feeling about it :D
	SPELL_GO_FLAGS_UNK80000			= 0x80000, //2 functions called (same ones as for ranged but different)
	SPELL_GO_FLAGS_RUNE_UPDATE		= 0x200000, //2 bytes for the rune cur and rune next flags
	SPELL_GO_FLAGS_UNK400000		= 0x400000, //seems to make server send an uint32 after m_targets.write
};

void Spell::SendSpellGo()
{
	// Fill UniqueTargets
	TargetsList::iterator i, j;
	for( uint32 x = 0; x < 3; x++ )
	{
		if( GetProto()->Effect[x] )
		{
			bool add = true;
			for( i = m_targetUnits[x].begin(); i != m_targetUnits[x].end(); i++ )
			{
				add = true;
				for( j = UniqueTargets.begin(); j != UniqueTargets.end(); j++ )
				{
					if( (*j) == (*i) )
					{
						add = false;
						break;
					}
				}
				if( add && (*i) != 0 )
					UniqueTargets.push_back( (*i) );
				//TargetsList::iterator itr = std::unique(m_targetUnits[x].begin(), m_targetUnits[x].end());
				//UniqueTargets.insert(UniqueTargets.begin(),));
				//UniqueTargets.insert(UniqueTargets.begin(), itr);
			}
			
			if( m_targets.m_itemTarget )
			{
				add = true;
				for( j = UniqueTargets.begin(); j != UniqueTargets.end(); j++ )
				{
					if( m_targets.m_itemTarget == (*j) )
					{
						add = false;
						break;
					}
				}
				if( add )
					UniqueTargets.push_back( m_targets.m_itemTarget );
			}
		}
	}

	// no need to send this on passive spells
	if( !m_caster->IsInWorld() 
		|| ( GetProto()->Attributes & ATTRIBUTES_PASSIVE )
		|| ( m_triggeredSpell && m_spellInfo->SpellVisual == 0 && m_spellInfo->speed == 0 )
		)
		return;

	// Start Spell
	sStackWolrdPacket( data,SMSG_SPELL_GO,5500 );
	uint32 flags = 0;

	if ( GetType() == SPELL_DMG_TYPE_RANGED )
		flags |= SPELL_GO_FLAGS_RANGED; // 0x20 RANGED

	if( i_caster != NULL )
		flags |= SPELL_GO_FLAGS_ITEM_CASTER; // 0x100 ITEM CASTER

	if( ModeratedTargets.size() > 0 )
		flags |= SPELL_GO_FLAGS_EXTRA_MESSAGE; // 0x400 TARGET MISSES AND OTHER MESSAGES LIKE "Resist"

	//experiments with rune updates
	uint8 cur_have_runes;
	if( p_caster && p_caster->getClass() == DEATHKNIGHT ) //send our rune updates ^^
	{
		//see what we will have after cast
		cur_have_runes = 0;
		for( int i=0;i<TOTAL_USED_RUNES;i++)
			if( p_caster->m_runes[ i ] == MAX_RUNE_VALUE )
				cur_have_runes |= (1 << i);
		if( cur_have_runes != m_rune_avail_before )
			flags |= SPELL_GO_FLAGS_RUNE_UPDATE | SPELL_GO_FLAGS_POWER_UPDATE;
	}

	// hacky..
	if( GetProto()->Id == 8326 ) // death
		flags = SPELL_GO_FLAGS_ITEM_CASTER | 0x0D;

	if( i_caster != NULL && u_caster != NULL ) // this is needed for correct cooldown on items
	{
		data << i_caster->GetNewGUID() << u_caster->GetNewGUID();
	}
	else
	{
		data << m_caster->GetNewGUID() << m_caster->GetNewGUID();
	}

	data << extra_cast_number; //3.0.2
	data << GetProto()->Id;
	data << flags;
	data << getMSTime();
	data << (uint8)(UniqueTargets.size()); //number of hits
	writeSpellGoTargets( &data );

	if( flags & SPELL_GO_FLAGS_EXTRA_MESSAGE )
	{
		data << (uint8)(ModeratedTargets.size()); //number if misses
		writeSpellMissedTargets( &data );
	}
	else 
		data << uint8( 0 ); //moderated target size is 0 since we did not set the flag

	m_targets.write( data ); // this write is included the target flag

	// er why handle it being null inside if if you can't get into if if its null
	if( GetType() == SPELL_DMG_TYPE_RANGED )
	{
		ItemPrototype* ip = NULL;
		if( GetProto()->Id == SPELL_RANGED_THROW )
		{
			if( p_caster != NULL )
			{
				Item* it = p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_RANGED );
				if( it != NULL )
					ip = it->GetProto();
			}
			else
				ip = ItemPrototypeStorage.LookupEntry(2512);	/*rough arrow*/
		}
#ifndef CATACLYSM_SUPPORT
		else
		{
			if( p_caster != NULL )
				ip = ItemPrototypeStorage.LookupEntry(p_caster->GetUInt32Value( PLAYER_AMMO_ID ) );
			else // HACK FIX
				ip = ItemPrototypeStorage.LookupEntry(2512);	/*rough arrow*/
		}
#endif
		if( ip != NULL)
			data << ip->DisplayInfoID << ip->InventoryType;
		else 
			data << uint32( 0 ) << uint32( 0 );
	}

	//data order depending on flags : 0x800, 0x200000, 0x20000, 0x20, 0x80000, 0x40 (this is not spellgoflag but seems to be from spellentry or packet..)
//.text:00401110                 mov     eax, [ecx+14h] -> them
//.text:00401115                 cmp     eax, [ecx+10h] -> us
	if( flags & SPELL_GO_FLAGS_RUNE_UPDATE )
	{
		if( flags & SPELL_GO_FLAGS_POWER_UPDATE )
			data << uint32( 0 ); //no idea about this :S.If not sent there is no visual update
		//we already substracted power
		data << uint8( m_rune_avail_before );
		data << uint8( cur_have_runes );
		for(uint8 i=0;i<m_runes_to_update;i++)
			data << uint8( 0 ); //values of the rune converted into byte. We just think it is 0 but maybe it is not :P 
	}
	if( m_targets.m_targetMask & 0x40 )
		data << uint8( 0 ); //some spells require this ? not sure if it is last byte or before that.

	m_caster->SendMessageToSet( &data, true );

	// spell log execute is still send 2.08
	// as I see with this combination, need to test it more
	//if (flags != 0x120 && GetProto()->Attributes & 16) // not ranged and flag 5
	//SendLogExecute(0,m_targets.m_unitTarget);
}

void Spell::writeSpellGoTargets( StackWorldPacket * data )
{
	TargetsList::iterator i;
	for ( i = UniqueTargets.begin(); i != UniqueTargets.end(); i++ )
	{
//		SendCastSuccess(*i);
		*data << (*i);
	}
}

void Spell::writeSpellMissedTargets( StackWorldPacket * data )
{
	/*
	 * The flags at the end known to us so far are.
	 * 1 = Miss
	 * 2 = Resist
	 * 3 = Dodge // mellee only
	 * 4 = Deflect
	 * 5 = Block // mellee only
	 * 6 = Evade
	 * 7 = Immune
	 */
	SpellTargetsList::iterator i;
	if(u_caster && u_caster->isAlive())
	{
		for ( i = ModeratedTargets.begin(); i != ModeratedTargets.end(); i++ )
		{
			*data << (*i).TargetGuid;       // uint64
			*data << (*i).TargetModType;    // uint8
			///handle proc on resist spell
			Unit* target = u_caster->GetMapMgr()->GetUnit((*i).TargetGuid);
			if(target && target->isAlive())
			{
				u_caster->HandleProc(PROC_ON_RESIST_VICTIM,target,GetProto()/*,damage*/);		/** Damage is uninitialized at this point - burlex */
				target->CombatStatusHandler_ResetPvPTimeout(); // aaa
				u_caster->CombatStatusHandler_ResetPvPTimeout(); // bbb
			}
		}
	}
	else
		for ( i = ModeratedTargets.begin(); i != ModeratedTargets.end(); i++ )
		{
			*data << (*i).TargetGuid;       // uint64
			*data << (*i).TargetModType;    // uint8
		}
}
/*
void Spell::SendLogExecute(uint32 damage, uint64 & targetGuid)
{
	sStackWolrdPacket(data,SMSG_SPELLLOGEXECUTE,50);
	data << m_caster->GetNewGUID();
	data << GetProto()->Id;
	data << uint32(1);
	data << GetProto()->SpellVisual;
	data << uint32(1);
	if (m_caster->GetGUID() != targetGuid)
		data << targetGuid;
	if (damage)
		data << damage;
	m_caster->SendMessageToSet(&data,true);
}*/

void Spell::SendInterrupted( uint8 result )
{
	SetSpellFailed();

	if( m_caster == NULL || !m_caster->IsInWorld() )
	{ 
		return;
	}

	sStackWolrdPacket( data,SMSG_SPELL_FAILURE, 50 );

	// send the failure to pet owner if we're a pet
	Player *plr = p_caster;
	if( plr == NULL && m_caster->IsPet() )
 	{
		SafePetCast(m_caster)->SendCastFailed( m_spellInfo->Id, result );
 	}
	else
	{
		if( plr == NULL && u_caster != NULL && u_caster->m_redirectSpellPackets != NULL )
			plr = u_caster->m_redirectSpellPackets;
	
		if( plr != NULL && plr->IsPlayer() )
		{
			data << m_caster->GetNewGUID();
			data << extra_cast_number;
			data << m_spellInfo->Id;
			data << uint8( result );
			plr->GetSession()->SendPacket( &data );
		}
	}
	//Zack : is there a reason we need to send others spell fail reason ? Isn't this personal ?
	data.Initialize( SMSG_SPELL_FAILED_OTHER );
	data << m_caster->GetNewGUID();
	data << extra_cast_number;
	data << GetProto()->Id;
	m_caster->SendMessageToSet( &data, true );
	/**/
}

void Spell::SendChannelUpdate(uint32 time)
{
	if(time == 0)
	{
		if(u_caster && u_caster->IsInWorld())
		{
			DynamicObject* dynObj=u_caster->GetMapMgr()->GetDynamicObject(u_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT));
			if(dynObj)
				dynObj->Remove();

			u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT,0);
			u_caster->SetUInt32Value(UNIT_CHANNEL_SPELL,0);
		}
	}

	if (!p_caster)
	{ 
		return;
	}

	sStackWolrdPacket(data, MSG_CHANNEL_UPDATE,20);
	data << p_caster->GetNewGUID();
	data << time;

	p_caster->SendMessageToSet(&data, true);
}

void Spell::SendChannelStart(uint32 duration)
{
	if (m_caster->GetTypeId() != TYPEID_GAMEOBJECT)
	{
		// Send Channel Start
		sStackWolrdPacket(data,MSG_CHANNEL_START,50);
		data << m_caster->GetNewGUID();
		data << GetProto()->Id;
		data << duration;
		m_caster->SendMessageToSet(&data, true);
	}

	m_castTime = m_timer = duration;

	if( u_caster != NULL )
		u_caster->SetUInt32Value(UNIT_CHANNEL_SPELL,GetProto()->Id);

	/*
	Unit* target = objmgr.GetCreature( SafePlayerCast( m_caster )->GetSelection());
	if(!target)
		target = objmgr.GetObject<Player>( SafePlayerCast( m_caster )->GetSelection());
	if(!target)
		return;

	m_caster->SetUInt32Value(UNIT_FIELD_CHANNEL_OBJECT,target->GetGUIDLow());
	m_caster->SetUInt32Value(UNIT_FIELD_CHANNEL_OBJECT+1,target->GetGUIDHigh());
	//disabled it can be not only creature but GO as well
	//and GO is not selectable, so this method will not work
	//these fields must be filled @ place of call
	*/
}

void Spell::SendResurrectRequest(Player* target)
{
	string name;
	if( p_caster )
		name = p_caster->GetName();
	else if( m_caster->IsCreature() && SafeCreatureCast( m_caster )->myFamily )
		name = SafeCreatureCast( m_caster )->myFamily->name;
	else name ="";
	WorldPacket data(SMSG_RESURRECT_REQUEST, 8 + 4 + name.size() + 1 + 4 );
	data << m_caster->GetGUID();
	data << uint32( name.size() + 1 );//null terminated
	data << name;
	data << uint8(0);
	if( m_caster->IsCreature() )
		data << uint32( 1 );
	else
		data << uint32( 0 );
	target->GetSession()->SendPacket(&data);
	target->m_resurrecter = m_caster->GetGUID();
}

void Spell::SendTameFailure( uint8 result )
{
    if( p_caster != NULL )
    {
        WorldPacket data( SMSG_PET_TAME_FAILURE, 1 );
        data << uint8( result );
        p_caster->GetSession()->SendPacket( &data );
    }
}

bool Spell::HasPower()
{
	int32 powerField;
	if( u_caster != NULL )
		if(u_caster->HasFlag(UNIT_NPC_FLAGS,UNIT_NPC_FLAG_TRAINER))
		{ 
			return true;
		}

	if(p_caster && p_caster->PowerCheat)
	{ 
		return true;
	}

	// Free cast for battle preparation
	if( p_caster && IS_INSTANCE(p_caster->GetMapId()) )
	{
		if ( p_caster->HasAura(44521))
		{ 
			return true;
		}
		if ( p_caster->HasAura(44535))
		{ 
			return true;
		}
		if ( p_caster->HasAura(32727))
		{ 
			return true;
		}
	}

	switch(GetProto()->powerType)
	{
	case POWER_TYPE_HEALTH:
		{
			powerField = UNIT_FIELD_HEALTH;
		} break;
	case POWER_TYPE_MANA:
		{
			powerField = UNIT_FIELD_POWER1;
			m_usesMana = true;
		} break;
	case POWER_TYPE_RAGE:
		{
			powerField = UNIT_FIELD_POWER2;
		} break;
	case POWER_TYPE_FOCUS:
		{
			powerField = UNIT_FIELD_POWER3;
		}	break;
	case POWER_TYPE_ENERGY:
		{
			powerField = UNIT_FIELD_POWER4;
		} break;
	case POWER_TYPE_HAPPINESS:
		{
			powerField = UNIT_FIELD_POWER5; //elixirs 
		} break;
	case POWER_TYPE_RUNIC_POWER:
		{
			powerField = UNIT_FIELD_POWER7; //not sure yet
		 }break;
	case POWER_TYPE_RUNES:
		{
			if( !p_caster )
			{ 
				return true;	//mobs have runes all the time :D
			}
			//lookup the requirements for this spell
			SpellRuneCostEntry *cost = dbcSpellRuneCostEntry.LookupEntryForced( GetProto()->RuneCostID );
			if( !cost )
			{
				sLog.outDebug("Could not find runecost for spell %u with cost id %u",GetProto()->Id,GetProto()->RuneCostID);
				return false;
			}
			//not sure here. Description says there are runes that refill in 10 seconds. Runecosts sugest that not everything is consumed ? 
			uint8 fail_count=0;
			for(int rune_type=0;rune_type<TOTAL_NORMAL_RUNE_TYPES;rune_type++)
				if( cost->costs[rune_type] )
				{	
					uint8 t = p_caster->GetFullRuneCount( rune_type );
					if( t < cost->costs[rune_type] )
						fail_count += ( cost->costs[rune_type] - t );
				}
			if( fail_count == 0 || p_caster->GetFullRuneCount( RUNE_DEATH ) >= fail_count )
			{ 
				return true;
			}
			return false; 
		}break;
	default:
		{
			sLog.outDebug("unknown power type %u",GetProto()->powerType);
			// we should'nt be here to return
			return false;
		} break;
	}


	//FIXME: add handler for UNIT_FIELD_POWER_COST_MODIFIER
	//UNIT_FIELD_POWER_COST_MULTIPLIER
	if( u_caster != NULL )
	{
		if( GetProto()->AttributesEx & ATTRIBUTESEX_DRAIN_WHOLE_MANA ) // Uses %100 mana
		{
			m_caster->SetUInt32Value(powerField, 0);
			return true;
		}
	}

	int32 currentPower = m_caster->GetUInt32Value(powerField);

	int32 cost;
	if( GetProto()->ManaCostPercentage)//Percentage spells cost % of !!!BASE!!! mana
	{
		if( GetProto()->powerType==POWER_TYPE_MANA)
			cost = (m_caster->GetUInt32Value(UNIT_FIELD_BASE_MANA)*GetProto()->ManaCostPercentage)/100;
		else
			cost = (m_caster->GetUInt32Value(UNIT_FIELD_BASE_HEALTH)*GetProto()->ManaCostPercentage)/100;
	}
	else
	{
		cost = GetProto()->manaCost;
	}

	if((int32)GetProto()->powerType==POWER_TYPE_HEALTH)
		cost -= GetProto()->baseLevel;//FIX for life tap
	else if( u_caster != NULL )
	{
		if( GetProto()->powerType==POWER_TYPE_MANA)
			cost += u_caster->PowerCostMod[GetProto()->School];//this is not percent!
		else
			cost += u_caster->PowerCostMod[0];
		cost +=float2int32(cost*u_caster->GetFloatValue(UNIT_FIELD_POWER_COST_MULTIPLIER+GetProto()->School));
	}

	 //hackfix for shiv's energy cost
	if (p_caster != NULL && m_spellInfo->NameHash == SPELL_HASH_SHIV && p_caster->GetItemInterface())
	{
		Item *it = p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
		if( it != NULL )
			cost += (uint32)(10* (it->GetProto()->Delay / 1000.0f));
	}

	//apply modifiers
	if( Need_SM_Apply(GetProto()) && u_caster)
	{
		SM_FIValue(u_caster->SM_FCost,&cost,GetProto()->SpellGroupType);
		SM_PIValue(u_caster->SM_PCost,&cost,GetProto()->SpellGroupType);
	}

	if (cost <=0)
	{ 
		return true;
	}

	//FIXME:DK:if field value < cost what happens
	if(powerField == UNIT_FIELD_HEALTH)
	{
		return true;
	}
	else
	{
		if(cost <= currentPower) // Unit has enough power (needed for creatures)
		{
			return true;
		}
		else
			return false;
	}
}

bool Spell::TakePower()
{
	int32 powerField;
	if( u_caster != NULL && u_caster->HasFlag(UNIT_NPC_FLAGS,UNIT_NPC_FLAG_TRAINER) )
	{ 
		return true;
	}

	if(p_caster && p_caster->PowerCheat)
	{ 
		return true;
	}

	// Free cast for battle preparation
	if( p_caster && IS_INSTANCE(p_caster->GetMapId()) )
	{
		if ( p_caster->HasAura(44521))
		{ 
			return true;
		}
		if ( p_caster->HasAura(44535))
		{ 
			return true;
		}
		if ( p_caster->HasAura(32727))
		{ 
			return true;
		}
	}

	switch(GetProto()->powerType)
	{
		case POWER_TYPE_HEALTH:{
			powerField = UNIT_FIELD_HEALTH;
							   }break;
		case POWER_TYPE_MANA:{
			powerField = UNIT_FIELD_POWER1;
			m_usesMana=true;
							 }break;
		case POWER_TYPE_RAGE:{
			powerField = UNIT_FIELD_POWER2;
							 }break;
		case POWER_TYPE_FOCUS:{
			powerField = UNIT_FIELD_POWER3;
							  }break;
		case POWER_TYPE_ENERGY:{
			powerField = UNIT_FIELD_POWER4;
							  }break;
		case POWER_TYPE_HAPPINESS:{
			powerField = UNIT_FIELD_POWER5; //elixirs
			//!!!some might not work because we do not have power for this. Ex : 26677 - Cure Poison
							   }break;
		case POWER_TYPE_RUNIC_POWER:{
			powerField = UNIT_FIELD_POWER7; //not sure yet
							  }break;
		case POWER_TYPE_RUNES:
			{
				if( !p_caster )
				{ 
					return true;
				}
//				if( !HasPower() )
//					return false;

				//lookup the requirements for this spell
				SpellRuneCostEntry *cost = dbcSpellRuneCostEntry.LookupEntryForced( GetProto()->RuneCostID );
				if( !cost )
				{
					sLog.outDebug("Could not find runecost for spell %u with cost id %u",GetProto()->Id,GetProto()->RuneCostID);
					return false;
				}

				//!!!need to work on this. No idea how to select to which rune the reduction applies !
				//right now i imagine 1 flat reduction eliminates 1 rune. Can't imagine the PCT ones though :(
				int32 cost_red = cost->costs[ 0 ] + cost->costs[ 1 ] + cost->costs[ 2 ];
				if( Need_SM_Apply(GetProto()) )
				{
					SM_FIValue(u_caster->SM_FCost,&cost_red,GetProto()->SpellGroupType);
					SM_PIValue(u_caster->SM_PCost,&cost_red,GetProto()->SpellGroupType);
				}

				//not sure here. Description says there are runes that refill in 10 seconds. Runecosts sugest that not everything is consumed ? 
				//need to apply cost mods too !
				uint8 fail_count=0;
				for(int rune_type=0;rune_type<TOTAL_NORMAL_RUNE_TYPES;rune_type++)
					if( cost->costs[ rune_type ] )
					{
						m_runes_to_update++;
						if( cost_red < 0 )
						{
							cost_red += 1;
							continue;
						}
						fail_count += p_caster->TakeFullRuneCount( rune_type, cost->costs[rune_type] );
					}
				if( fail_count != 0 )
				{
					fail_count = p_caster->TakeFullRuneCount( RUNE_DEATH, fail_count );
					sLog.outDebug("Spell is trying to consume more runes then we have. Eighter proc spell is eating power or something went wrong");
				}
				//add runic power if there is one
				int32 runic_gain = cost->runic_power_conversion;
				if( runic_gain )
				{
					if( Need_SM_Apply(GetProto()) )
					{
						SM_FIValue(p_caster->SM_FCost,&runic_gain,GetProto()->SpellGroupType);
						SM_PIValue(p_caster->SM_PCost,&runic_gain,GetProto()->SpellGroupType);
					}
					p_caster->ModUnsigned32Value( UNIT_FIELD_POWER7, runic_gain );
					u_caster->UpdatePowerAmm();
				}

				//DK talent that procs if all blood runes are on cooldown
				if( p_caster->GetFullRuneCount( RUNE_BLOOD ) == 0 )
					p_caster->HandleProc( PROC_SCRIPTED_PROCTEST, p_caster, GetProto() );
				return true;
			}break;
		default:{
			sLog.outDebug("unknown power type");
			// we should'nt be here to return
			return false;
				}break;
	}

	//FIXME: add handler for UNIT_FIELD_POWER_COST_MODIFIER
	//UNIT_FIELD_POWER_COST_MULTIPLIER
	if( u_caster != NULL )
	{
		if( GetProto()->AttributesEx & ATTRIBUTESEX_DRAIN_WHOLE_MANA ) // Uses %100 mana
		{
			m_caster->SetUInt32Value(powerField, 0);
			u_caster->UpdatePowerAmm();
			return true;
		}
	}

	int32 currentPower = m_caster->GetUInt32Value(powerField);

	int32 cost;
	if( GetProto()->ManaCostPercentage)//Percentage spells cost % of !!!BASE!!! mana
	{
		if( GetProto()->powerType==POWER_TYPE_MANA)
			cost = (m_caster->GetUInt32Value(UNIT_FIELD_BASE_MANA)*GetProto()->ManaCostPercentage)/100;
		else
			cost = (m_caster->GetUInt32Value(UNIT_FIELD_BASE_HEALTH)*GetProto()->ManaCostPercentage)/100;
	}
	else
	{
		cost = GetProto()->manaCost;
	}

	if((int32)GetProto()->powerType==POWER_TYPE_HEALTH)
			cost -= GetProto()->baseLevel;//FIX for life tap
	else if( u_caster != NULL )
	{
		if( GetProto()->powerType==POWER_TYPE_MANA)
			cost += u_caster->PowerCostMod[GetProto()->School];//this is not percent!
		else
			cost += u_caster->PowerCostMod[0];
		cost +=float2int32(cost*u_caster->GetFloatValue(UNIT_FIELD_POWER_COST_MULTIPLIER+GetProto()->School));
	}

	 //hackfix for shiv's energy cost
	if (p_caster != NULL && m_spellInfo->NameHash == SPELL_HASH_SHIV && p_caster->GetItemInterface())
	{
		Item *it = p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
		if( it != NULL )
			cost += (uint32)(10* (it->GetProto()->Delay / 1000.0f));
	}

	//apply modifiers
	if( Need_SM_Apply(GetProto()) && u_caster)
	{
		  SM_FIValue(u_caster->SM_FCost,&cost,GetProto()->SpellGroupType);
		  SM_PIValue(u_caster->SM_PCost,&cost,GetProto()->SpellGroupType);
	}

#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
	int spell_flat_modifers=0;
	int spell_pct_modifers=0;
	SM_FIValue(u_caster->SM_FCost,&spell_flat_modifers,GetProto()->SpellGroupType);
	SM_FIValue(u_caster->SM_PCost,&spell_pct_modifers,GetProto()->SpellGroupType);
	if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
		printf("!!!!!spell cost mod flat %d , spell cost mod pct %d , spell dmg %d, spell group %u\n",spell_flat_modifers,spell_pct_modifers,cost,GetProto()->SpellGroupType);
#endif

	if (cost <=0)
	{ 
		return true;
	}

	//FIXME:DK:if field value < cost what happens
	if(powerField == UNIT_FIELD_HEALTH)
	{
		m_caster->DealDamage(u_caster, cost, 0, 0, 0,true);
		return true;
	}
	else
	{
		if(cost <= currentPower) // Unit has enough power (needed for creatures)
		{
			m_caster->SetUInt32Value(powerField, currentPower - cost);
			if( u_caster )
				u_caster->UpdatePowerAmm();
			return true;
		}
		else
			return false;
	}
}

void Spell::HandleEffects(uint64 guid, uint32 i)
{
	uint32 id;
	playerTarget = 0;	//make sure to reset this so effect 1 will not use the same value effect 0 set
	if(guid == m_caster->GetGUID() || guid == 0)
	{
		unitTarget = u_caster;
		gameObjTarget = g_caster;
		playerTarget = p_caster;
		if( p_caster && m_targets.m_itemTarget && p_caster->GetItemInterface() )
			itemTarget = p_caster->GetItemInterface()->GetItemByGUID( m_targets.m_itemTarget );
		else
			itemTarget = i_caster;
	}
	else
	{
		if( p_caster && m_targets.m_itemTarget && p_caster->GetItemInterface() )
			itemTarget = p_caster->GetItemInterface()->GetItemByGUID( m_targets.m_itemTarget );
		if(!m_caster->IsInWorld())
		{
			unitTarget = 0;
			playerTarget = 0;
			itemTarget = 0;
			gameObjTarget = 0;
			corpseTarget = 0;
		}
		else if( m_targets.m_targetMask & TARGET_FLAG_TRADE_ITEM && p_caster != NULL )
		{
			Player * plr = p_caster->GetTradeTarget();
			if(plr)
				itemTarget = plr->getTradeItem((uint32)guid);
		}
		else
		{
//			unitTarget = NULL;
			switch(GET_TYPE_FROM_GUID(guid))
			{
			case HIGHGUID_TYPE_UNIT:
				unitTarget = m_caster->GetMapMgr()->GetCreature( guid );
				break;
			case HIGHGUID_TYPE_PET:
				unitTarget = m_caster->GetMapMgr()->GetPet( guid );
				break;
			case HIGHGUID_TYPE_PLAYER:
				{
					unitTarget =  m_caster->GetMapMgr()->GetPlayer( guid );
					if( unitTarget )
						playerTarget = SafePlayerCast(unitTarget);
				}break;
			case HIGHGUID_TYPE_ITEM:
				if( p_caster != NULL )
					itemTarget = p_caster->GetItemInterface()->GetItemByGUID(guid);

				break;
			case HIGHGUID_TYPE_GAMEOBJECT:
				gameObjTarget = m_caster->GetMapMgr()->GetGameObject( guid );
				break;
			case HIGHGUID_TYPE_CORPSE:
				corpseTarget = objmgr.GetCorpse((uint32)guid);
				break;
			}
		}
	}

	damage = CalculateEffect(i,unitTarget);

	id = GetProto()->Effect[i];
	if( id<TOTAL_SPELL_EFFECTS)
	{
		uint32 guid = 0;
		if( unitTarget )
			guid = unitTarget->GetLowGUID();
		sLog.outDebug( "WORLD: Spell effect id = %u (%s), damage = %d, target = %u", id, SpellEffectNames[id], damage, guid );

		/*if(unitTarget && p_caster && isAttackable(p_caster,unitTarget))
			sEventMgr.ModifyEventTimeLeft(p_caster,EVENT_ATTACK_TIMEOUT,PLAYER_ATTACK_TIMEOUT_INTERVAL);*/

		(*this.*SpellEffectsHandler[id])(i);
	}
	else
		sLog.outError("SPELL: unknown effect %u spellid %u", id, GetProto()->Id);
#ifdef _CRTDBG_MAP_ALLOC_TEST_MEM
	_CrtCheckMemory();
#endif
}

void Spell::HandleAddAura(uint64 guid)
{
	Unit * Target = 0;
	if(guid == 0)
	{ 
		return;
	}

	if(u_caster && u_caster->GetGUID() == guid)
		Target = u_caster;
	else if(m_caster->IsInWorld())
		Target = m_caster->GetMapMgr()->GetUnit(guid);

	if(!Target)
	{ 
		return;
	}

	// Applying an aura to a flagged target will cause you to get flagged.
    // self casting doesnt flag himself.
	if(Target->IsPlayer() && p_caster && p_caster != SafePlayerCast(Target))
	{
		if(SafePlayerCast(Target)->IsPvPFlagged())
			p_caster->SetPvPFlag();
	}

	// remove any auras with same type
	if( GetProto()->BGR_one_buff_on_target > 0)
	{
		uint32 skip_self;
		if( GetProto()->maxstack > 1 )
			skip_self = GetProto()->Id;
		else
			skip_self = 0;
		Target->RemoveAurasByBuffType(GetProto()->BGR_one_buff_on_target, m_caster->GetGUID(),skip_self,GetProto()->BGR_one_buff_on_target_skip_caster_check);
	}

	// avoid map corruption
	if(Target->GetInstanceID()!=m_caster->GetInstanceID())
	{ 
		return;
	}

	std::map<uint32,Aura*>::iterator itr=Target->tmpAura.find(GetProto()->Id);
	if(itr!=Target->tmpAura.end())
	{
		if(itr->second)
		{
			if(itr->second->GetSpellProto()->procCharges>0)
			{
				int32 charges = itr->second->GetSpellProto()->procCharges;
				if( Need_SM_Apply(itr->second->GetSpellProto()) && u_caster != NULL )
				{
					SM_FIValue( u_caster->SM_FCharges, &charges, itr->second->GetSpellProto()->SpellGroupType );
					SM_PIValue( u_caster->SM_PCharges, &charges, itr->second->GetSpellProto()->SpellGroupType );
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
					float spell_flat_modifers=0;
					float spell_pct_modifers=0;
					SM_FIValue(u_caster->SM_FCharges,&spell_flat_modifers,itr->second->GetSpellProto()->SpellGroupType);
					SM_FIValue(u_caster->SM_PCharges,&spell_pct_modifers,itr->second->GetSpellProto()->SpellGroupType);
					if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
						printf("!!!!!spell charge bonus mod flat %f , spell range bonus pct %f , spell range %f, spell group %u\n",spell_flat_modifers,spell_pct_modifers,maxRange,GetProto()->SpellGroupType);
#endif
				}
				if( charges > MAX_AURAS / 4 )
					charges = MAX_AURAS / 4; //seen this happen with spell with 10k charges to "deadlock" realm
				for(int i=0;i<charges-1;i++)
				{
					Aura *aur = AuraPool.PooledNew();
					aur->Init(itr->second->GetSpellProto(),itr->second->GetDuration(),itr->second->GetCaster(),itr->second->GetTarget(), i_caster);
					Target->AddAura(aur);
					aur=NULL;
				}
				if( !(itr->second->GetSpellProto()->procFlags2 & PROC2_REMOVEONUSE)	)
				{
					if( Target->m_chargeSpells.find( itr->second->GetSpellId() ) == Target->m_chargeSpells.end() )
					{
						SpellCharge charge;
						charge.count=charges;
//						charge.spellId=itr->second->GetSpellId();
						charge.spe=itr->second->GetSpellProto();
						if( itr->second->GetSpellProto()->procFlagsRemove != 0 )
							charge.ProcFlag=itr->second->GetSpellProto()->procFlagsRemove;
						else
							charge.ProcFlag=itr->second->GetSpellProto()->procFlags;
						Target->m_chargeSpells.insert(make_pair(itr->second->GetSpellId(),charge));
					}
					else
					{
						Target->m_chargeSpells[ itr->second->GetSpellId() ].count += charges;	//zack, is it even possible to stack up mor ethen "charge" count ?
//						Target->m_chargeSpells[ itr->second->GetSpellId() ].count = charges;
						//just in case charges cannot stack
						//there is a bug here. sometimes charges will sum up to maxstack even if player does not have maxstack aura count on him
						if( (int32)itr->second->GetSpellProto()->maxstack * charges < Target->m_chargeSpells[ itr->second->GetSpellId() ].count )
							Target->m_chargeSpells[ itr->second->GetSpellId() ].count = itr->second->GetSpellProto()->maxstack * charges;
					}
				}
			}
			Target->AddAura(itr->second); // the real spell is added last so the modifier is removed last
			Target->tmpAura.erase(itr);
		}
	}
#ifdef _CRTDBG_MAP_ALLOC_TEST_MEM
	_CrtCheckMemory();
#endif
}

/*
void Spell::TriggerSpell()
{
	if(TriggerSpellId != 0)
	{
		// check for spell id
		SpellEntry *spellInfo = sSpellStore.LookupEntry(TriggerSpellId );

		if(!spellInfo)
		{
			sLog.outError("WORLD: unknown spell id %i\n", TriggerSpellId);
			return;
		}

		Spell *spell = new Spell(m_caster, spellInfo,false, NULL);
		WPAssert(spell);

		SpellCastTargets targets;
		if(TriggerSpellTarget)
			targets.m_unitTarget = TriggerSpellTarget;
		else
			targets.m_unitTarget = m_targets.m_unitTarget;

		spell->prepare(&targets);
	}
}*/
/*
void Spell::DetermineSkillUp()
{
	skilllinespell* skill = objmgr.GetSpellSkill(GetProto()->Id);
	if (m_caster->GetTypeId() == TYPEID_PLAYER)
	{
		if ((skill) && SafePlayerCast( m_caster )->HasSkillLine( skill->skilline ) )
		{
			uint32 amt = SafePlayerCast( m_caster )->GetBaseSkillAmt(skill->skilline);
			uint32 max = SafePlayerCast( m_caster )->GetSkillMax(skill->skilline);
			if (amt >= skill->grey) //grey
			{
			}
			else if ((amt >= (((skill->grey - skill->green) / 2) + skill->green)) && (amt < max))
			{
				if (rand()%100 < 33) //green
					SafePlayerCast( m_caster )->AdvanceSkillLine(skill->skilline);

			}
			else if ((amt >= skill->green) && (amt < max))
			{
				if (rand()%100 < 66) //yellow
					SafePlayerCast( m_caster )->AdvanceSkillLine(skill->skilline);

			}
			else
			{
				if (amt < max) //brown
					SafePlayerCast( m_caster )->AdvanceSkillLine(skill->skilline);
			}
		}
	}
}
*/

uint8 Spell::CanCast(bool tolerate)
{
	uint32 i;
	if( IsSpellDisabled( GetProto() ) )
	{ 
		return SPELL_FAILED_SPELL_UNAVAILABLE;
	}
	Unit *target = NULL;

	if( GetProto()->CanCastHandler )
	{
		uint32 special_check_res =  GetProto()->CanCastHandler( this );
		if( special_check_res != SPELL_FAILED_SUCCESS )
			return special_check_res;
	}

	if( i_caster && i_caster->GetMapMgr() )
		target = i_caster->GetMapMgr()->GetUnit( m_targets.m_unitTarget );

	if(m_caster->IsInWorld())
	{
		Unit *target = m_caster->GetMapMgr()->GetUnit( m_targets.m_unitTarget );

		if( target )
		{
			if( GetProto()->required_target_type != SPELL_TARGET_TYPE_REQUIRE_NO_CHECK )
			{
				uint32 target_value;
				if( GetProto()->required_target_type == SPELL_TARGET_TYPE_REQUIRE_FACTION_CHECK )
					target_value = target->_getFaction();
				else if( GetProto()->required_target_type == SPELL_TARGET_TYPE_REQUIRE_ENTRY_CHECK )
					target_value = target->GetEntry();
				bool target_check_passed = false;
				for(uint32 i=0;i<GetProto()->required_target_value.GetMaxSize();i++)
					if( GetProto()->required_target_value.GetValue( i ) == target_value )
					{
						target_check_passed = true;
						break;
					}
				if( target_check_passed == false )
					return SPELL_FAILED_BAD_TARGETS;
			}
			//check for forbearanbce on target
			if( GetProto()->MechanicsType == MECHANIC_INVULNERABLE )
			{
				for(uint32 x=MAX_POSITIVE_AURAS;x<target->m_auras_neg_size;x++)
					if(target->m_auras[x] && target->m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_INVULNERABLE_FORBID )
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
			}

			// GM Flagged Players should be immune to other players' casts, but not their own.
			if (target->IsPlayer() && target != m_caster && SafePlayerCast(target)->HasFlag(PLAYER_FLAGS, PLAYER_FLAG_GM))
			{ 
				return SPELL_FAILED_BM_OR_INVISGOD;
			}

			//you can't mind control someone already mind controlled
			if (GetProto()->NameHash == SPELL_HASH_MIND_CONTROL && target->HasAurasWithNameHash(SPELL_HASH_MIND_CONTROL))
			{ 
				return SPELL_FAILED_BAD_TARGETS;
			}


			/* Shady: wtf is that? commented.
			else  if(GetProto()->NameHash == SPELL_HASH_VINDICATION)
			{
				if( !target->IsPlayer() )
					return SPELL_FAILED_BAD_TARGETS;
			}*/
		}
		if(GetProto()->Id == 48743)
		{
			if( p_caster == NULL || p_caster->GetSummon() == NULL )
				return SPELL_FAILED_REAGENTS;
		}
		if(GetProto()->Id == 32146)
		{
			Creature *corpse = m_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ(), 18240);
			if(corpse != NULL)
				if (m_caster->CalcDistance(m_caster, corpse) > 5)
				{ 
					return SPELL_FAILED_NOT_HERE;
				}
		}

		else if( GetProto()->Id == 37830 )
		{
			if( target != m_caster )
			{ 
				return SPELL_FAILED_BAD_TARGETS;
			}
		} 
	
		else if(GetProto()->Id == 39246)
		{
			Creature *cleft = m_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ(), 22105);
			if(cleft == NULL || cleft->isAlive())
			{ 
				return SPELL_FAILED_NOT_HERE;
			}
		}

		else if(GetProto()->Id == 30988)
		{
			Creature *corpse = m_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ(), 17701);
			if(corpse != NULL)
				if (m_caster->CalcDistance(m_caster, corpse) > 5  || corpse->isAlive())
				{ 
					return SPELL_FAILED_NOT_HERE;
				}
		}

		else if(GetProto()->Id == 43723)
		{
			Creature *abysal = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ(), 19973);
			if(abysal != NULL)
			{
				if(!abysal->isAlive())
					if(!(p_caster->GetItemInterface()->GetItemCount(31672, FALSE) > 1 && p_caster->GetItemInterface()->GetItemCount(31673, FALSE) > 0 && p_caster->CalcDistance(p_caster, abysal) < 10))
					{ 
						return SPELL_FAILED_NOT_HERE;
					}
			}
			else
				return SPELL_FAILED_NOT_HERE;
		}

		else if(GetProto()->Id == 32307)
		{
			Creature *kilsorrow = p_caster->GetMapMgr()->GetInterface()->GetCreatureNearestCoords(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
			if(kilsorrow == NULL || kilsorrow->isAlive() || p_caster->CalcDistance(p_caster, kilsorrow) > 1)
			{ 
				return SPELL_FAILED_NOT_HERE;
			}
			if(kilsorrow->GetEntry() != 17147 && kilsorrow->GetEntry() != 17148 && kilsorrow->GetEntry() != 18397 && kilsorrow->GetEntry() != 18658 && kilsorrow->GetEntry() != 17146)
			{ 
				return SPELL_FAILED_NOT_HERE;
			}
		}
		else if( GetProto()->NameHash == SPELL_HASH_HUNGER_FOR_BLOOD )
		{
			if( target && target->HasNegAuraWithMechanic( MECHANIC_BLEEDING ) == false )
				return SPELL_FAILED_BAD_TARGETS;
		}
		else if( GetProto()->NameHash == SPELL_HASH_POUNCE )
		{
			if( p_caster && ( p_caster->GetShapeShift() != FORM_CAT || p_caster->HasAurasWithNameHash( SPELL_HASH_PROWL ) == 0 ) )
				return SPELL_FAILED_BAD_TARGETS;
		}
		else if( GetProto()->NameHash == SPELL_HASH_RAISE_DEAD )
		{
			Object *corpse = NULL;
			std::set<Object*>::iterator itr;
			for( itr = m_caster->GetInRangeSetBegin(); itr != m_caster->GetInRangeSetEnd();itr++)
			{
				if( (*itr)->IsCorpse() )
				{
					corpse = (*itr);
					break;
				}
				if(!((*itr)->IsUnit()) || SafeUnitCast((*itr))->isAlive())
					continue;
				if( (*itr)->IsCreature() && SafeCreatureCast((*itr))->GetCreatureInfo()
					&& SafeCreatureCast((*itr))->GetCreatureInfo()->Type == HUMANOID )
				{
					corpse = (*itr);
					break;
				}
//				if( (*itr)->IsPlayer() )
//				{
//					corpse = (*itr);
//					break;
//				}
			}

			if( corpse )
			{
				//oh crap, what to do now ? what about global events and such ? memleak ?
				corpse->RemoveFromWorld( false );
			}
			//check if player has corpse dust
			else if( p_caster && p_caster->GetItemInterface()->RemoveItemAmt( 37201, 1 ) == 0 )
				return SPELL_FAILED_ITEM_GONE;
		}
		//this is correct to have but it sucks cause client does not gray out the spell as with others
		/*
		else if( GetProto()->NameHash == SPELL_HASH_RUNE_STRIKE )
		{
			if( m_caster && m_caster->HasFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_DODGE_BLOCK | AURASTATE_FLAG_DODGE_BLOCK) == false )
				return SPELL_FAILED_CASTER_AURASTATE;
		}
		*/
	}

	if( u_caster != NULL )
	{
		if ( ( GetProto()->Attributes & ATTRIBUTES_REQ_OOC) && u_caster->CombatStatus.IsInCombat() )
		{
			if( (GetProto()->Id !=  100 && GetProto()->Id != 6178 && GetProto()->Id != 11578 ) 
				|| ( p_caster != NULL && p_caster->ignoreShapeShiftChecks == false && p_caster->IgnoreSpellSpecialCasterStateRequirement==0) )	// Warbringer (Warrior 51Prot Talent effect)
				return SPELL_FAILED_TARGET_IN_COMBAT;
		}

		// check for cooldowns
		Player *tp_caster;
		if( p_caster )
			tp_caster = p_caster;
		else if( u_caster->IsPet() )
			tp_caster = SafePetCast( u_caster )->GetPetOwner();
		else
			tp_caster = NULL;
		if(!tolerate && tp_caster && tp_caster->CooldownCheat == false && !tp_caster->Cooldown_CanCast(GetProto()))
		{ 
				return SPELL_FAILED_NOT_READY;
		}
	}

	//Shady: EquippedItemClass, EquippedItemSubClass (doesn't it handled with client?)

	if( p_caster != NULL )
	{
		if( ( GetProto()->Attributes & ATTRIBUTES_REQ_STEALTH ) && !p_caster->IsStealth() && !p_caster->ignoreShapeShiftChecks ) 
		{ 
			return SPELL_FAILED_ONLY_STEALTHED;
		}

		if( !HasPower() )
		{ 
			return SPELL_FAILED_NO_POWER;
		}

		if (sWorld.Collision) {
			if (GetProto()->MechanicsType == MECHANIC_MOUNTED)
			{
				if (CollideInterface.IsIndoor( p_caster->GetMapId(), p_caster->GetPositionNC() ))
				{ 
					return SPELL_FAILED_NO_MOUNTS_ALLOWED;
				}
			}
			else if( GetProto()->Attributes & ATTRIBUTES_ONLY_OUTDOORS )
			{
				if( !CollideInterface.IsOutdoor( p_caster->GetMapId(), p_caster->GetPositionNC() ) )
				{ 
					return SPELL_FAILED_ONLY_OUTDOORS;
				}
			}
		}

		//are we in an arena and the spell cooldown is longer then 15mins?
		if ( p_caster->m_bg && ( p_caster->m_bg->GetType() >= BATTLEGROUND_ARENA_2V2 && p_caster->m_bg->GetType() <= BATTLEGROUND_ARENA_5V5 ) &&
			( GetProto()->RecoveryTime > 900000 || GetProto()->CategoryRecoveryTime > 900000 ) )
			return SPELL_FAILED_SPELL_UNAVAILABLE;

		//some spells cannot be casted while in PVP
		if( (GetProto()->AuraInterruptFlags & AURA_INTERRUPT_CUSTOM_ON_PVP) && p_caster->IsPvPFlagged() )
		{ 
			return SPELL_FAILED_NO_VALID_TARGETS;
		}

		//are we in an arena and the spell cooldown is longer then 15mins?
		if ( p_caster->m_bg && ( p_caster->m_bg->GetType() >= BATTLEGROUND_ARENA_2V2 && p_caster->m_bg->GetType() <= BATTLEGROUND_ARENA_5V5 ) &&
			( GetProto()->RecoveryTime > 900000 || GetProto()->CategoryRecoveryTime > 900000 ) )
			return SPELL_FAILED_SPELL_UNAVAILABLE;

		//if ( !p_caster->HasSpell(GetProto()->Id) && i_caster == NULL && !tolerate )
		//	return SPELL_FAILED_SPELL_UNAVAILABLE;

		// backstab/ambush
		/*Shady: This shit shouldn't be here
		We have special attribute ATTRIBUTES_REQ_STEALTH for stealth requiring.
		Also we have EquippedItemClass, EquippedItemSubClass fields in DBC for items handling. 
		SO FUCKING USE IT!
		if( GetProto()->NameHash == SPELL_HASH_BACKSTAB || GetProto()->NameHash == SPELL_HASH_AMBUSH )
		{
			if( GetProto()->NameHash == SPELL_HASH_AMBUSH && !p_caster->IsStealth() )
				return SPELL_FAILED_ONLY_STEALTHED;

			Item * pMainHand = p_caster->GetItemInterface()->GetInventoryItem( INVENTORY_SLOT_NOT_SET, EQUIPMENT_SLOT_MAINHAND );
			if( !pMainHand || pMainHand->GetProto()->Class != 2 || pMainHand->GetProto()->SubClass != 15 )
				return SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND;
		}*/

		if(p_caster->GetDuelState() == DUEL_STATE_REQUESTED)
		{
			for(i = 0; i < 3; ++i)
			{
				if( GetProto()->Effect[i] && GetProto()->Effect[i] != SPELL_EFFECT_APPLY_AURA && GetProto()->Effect[i] != SPELL_EFFECT_APPLY_PET_AURA
					&& GetProto()->Effect[i] != SPELL_EFFECT_APPLY_AREA_AURA && GetProto()->Effect[i] != SPELL_EFFECT_APPLY_AREA_AURA2)
				{
					return SPELL_FAILED_TARGET_DUELING;
				}
			}
		}

		// check for duel areas
		if(p_caster && GetProto()->Id == 7266)
		{
			AreaTable* at = dbcArea.LookupEntry( p_caster->GetAreaID() );
			if(at->AreaFlags & AREA_CITY_AREA)
			{ 
				return SPELL_FAILED_NO_DUELING;
			}
			// instance & stealth checks
			if ( p_caster->GetMapMgr() && p_caster->GetMapMgr()->GetMapInfo() 
				&& IS_DUEL_ENABLED_MAP( p_caster->GetMapMgr()->GetMapInfo() ) == false )
			{ 
					return SPELL_FAILED_NO_DUELING;
			}
			if ( p_caster->IsStealth() )
			{ 
				return SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED;
			}
		}

		// check if spell is allowed while player is on a taxi
		if(p_caster->m_onTaxi && !(GetProto()->Attributes & ATTRIBUTES_MOUNT_CASTABLE) )//Are mount castable spells allowed on a taxi?
		{
			if( m_spellInfo->Id != 33836 && m_spellInfo->Id != 45072 && m_spellInfo->Id != 45115 && m_spellInfo->Id != 31958) // exception for taxi bombs
			{ 
				return SPELL_FAILED_NOT_ON_TAXI;
			}
		}
		
		if( !p_caster->m_onTaxi )
		{
			if( m_spellInfo->Id == 33836 || m_spellInfo->Id == 45072 || m_spellInfo->Id == 45115 || m_spellInfo->Id == 31958)
			{ 
				return SPELL_FAILED_NOT_HERE;
			}
		}

		// check if spell is allowed while player is on a transporter
		if(p_caster->m_CurrentTransporter)
		{
			// no mounts while on transporters
			if( GetProto()->EffectApplyAuraName[0] == SPELL_AURA_MOUNTED || GetProto()->EffectApplyAuraName[1] == SPELL_AURA_MOUNTED || GetProto()->EffectApplyAuraName[2] == SPELL_AURA_MOUNTED)
			{ 
				return SPELL_FAILED_NOT_ON_TRANSPORT;
			}
		}

		// check if spell is allowed while not mounted
		if(!p_caster->IsMounted())
		{
			if( GetProto()->Id == 25860) // Reindeer Transformation
			{ 
				return SPELL_FAILED_ONLY_MOUNTED;
			}
		}
		else
		{
			if (!(GetProto()->Attributes & ATTRIBUTES_MOUNT_CASTABLE))
			{ 
				return SPELL_FAILED_NOT_MOUNTED;
			}
		}

		if( GetProto()->Effect[ 0 ] == SPELL_EFFECT_ACTIVATE_TALENT_SPEC && p_caster->m_tanlentSpecRespecTimer > getMSTime() )
		{ 
			return SPELL_FAILED_NOT_READY;
		}

		// check if spell is allowed while shapeshifted
		if(p_caster->GetShapeShift())
		{
			switch(p_caster->GetShapeShift())
			{
				case FORM_MOONKIN:
				{
					//only balance spells and remove curse
					if( 
//						GetProto()->spell_skilline[0] != SKILL_BALANCE 
						//allow potions and stuff
						( GetProto()->spell_skilline[0] == SKILL_RESTORATION2 ||  GetProto()->spell_skilline[0] == SKILL_FERAL_COMBAT )
						&& GetProto()->NameHash != SPELL_HASH_REMOVE_CURSE 
						&& GetProto()->NameHash != SPELL_HASH_BARKSKIN
						)
						return SPELL_FAILED_NOT_ON_SHAPESHIFT;
				}break;
				case FORM_TREE:
				{
					//only balance spells and remove curse
					if( 
						//GetProto()->spell_skilline[0] != SKILL_RESTORATION2 
						//allow potions
						( GetProto()->spell_skilline[0] == SKILL_BALANCE ||  GetProto()->spell_skilline[0] == SKILL_FERAL_COMBAT )
						&& GetProto()->NameHash != SPELL_HASH_INNERVATE
						&& GetProto()->NameHash != SPELL_HASH_BARKSKIN
						&& GetProto()->NameHash != SPELL_HASH_NATURE_S_GRASP
						&& GetProto()->NameHash != SPELL_HASH_THORNS
						)
						return SPELL_FAILED_NOT_ON_SHAPESHIFT;					
				}break;
				case FORM_BATTLESTANCE:
				case FORM_DEFENSIVESTANCE:
				case FORM_BERSERKERSTANCE:
				case FORM_SHADOW:
				case FORM_STEALTH:
				{
					break;
				}

				case FORM_SWIFT:
				case FORM_FLIGHT:
				{
					// check if item is allowed (only special items allowed in flight forms)
					if(i_caster && !(i_caster->GetProto()->Flags & ITEM_FLAG_SHAPESHIFT_OK))
					{ 
						return SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED;
					}

					break;
				}

				//case FORM_CAT:
				//case FORM_TRAVEL:
				//case FORM_AQUA:
				//case FORM_BEAR:
				//case FORM_AMBIENT:
				//case FORM_GHOUL:
				//case FORM_DIREBEAR:
				//case FORM_CREATUREBEAR:
				//case FORM_GHOSTWOLF:

				case FORM_SPIRITOFREDEMPTION:
				{
					//Spirit of Redemption (20711) fix
					if (!(GetProto()->c_is_flags & SPELL_FLAG_IS_HEALING) && GetProto()->Id != 7355)
					{ 
						return SPELL_FAILED_CASTER_DEAD;
					}
					break;
				}
				

				default:
				{
					// check if item is allowed (only special & equipped items allowed in other forms)
					if(i_caster && !(i_caster->GetProto()->Flags & ITEM_FLAG_SHAPESHIFT_OK))
						if(i_caster->GetProto()->InventoryType == INVTYPE_NON_EQUIP)
						{ 
							return SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED;
						}
				}
			}
		}
		//Zack : not good
		//check if spell requires shapeshift
		//if( GetProto()->RequiredShapeShift && !( ((uint32)1 << (p_caster->GetShapeShift()-1)) & GetProto()->RequiredShapeShift ) )
		//	return SPELL_FAILED_ONLY_SHAPESHIFT;


		// Arathi Basin opening spell, remove stealth, invisibility, etc. 
		// hacky but haven't found a better way that works
		if ( p_caster->m_bg )
		{
			if( GetProto()->Id == 21651 )
			{
				p_caster->RemoveStealth();
				p_caster->RemoveInvisibility();
				p_caster->RemoveAllAuraByNameHash(SPELL_HASH_ICE_BLOCK);
				p_caster->RemoveAllAuraByNameHash(SPELL_HASH_DIVINE_SHIELD);
				p_caster->RemoveAllAuraByNameHash(SPELL_HASH_BLESSING_OF_PROTECTION);
			}
		}

		// item spell checks
		if(i_caster && i_caster->GetProto()) //Let's just make sure there's something here, so we don't crash ;)
		{
			//check for Recently Bandaged on target
			if( target && GetProto()->MechanicsType == MECHANIC_HEALING )
			{
				for(uint32 x=MAX_POSITIVE_AURAS;x<target->m_auras_neg_size;x++)
					if(target->m_auras[x] && target->m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_HEALING )
					{ 
							return SPELL_FAILED_BAD_TARGETS;
					}
			}

			if( i_caster->GetProto()->ZoneNameID && i_caster->GetProto()->ZoneNameID != i_caster->GetZoneId() )
			{ 
				return SPELL_FAILED_NOT_HERE;
			}
			if( i_caster->GetProto()->MapID && i_caster->GetProto()->MapID != i_caster->GetMapId() )
			{ 
				return SPELL_FAILED_NOT_HERE;
			}

			if(i_caster->GetProto()->Spells[0].Charges != 0)
			{
				// check if the item has the required charges
				if(i_caster->GetUInt32Value(ITEM_FIELD_SPELL_CHARGES) == 0)
				{ 
					return SPELL_FAILED_NO_CHARGES_REMAIN;
				}

				// for items that combine to create a new item, check if we have the required quantity of the item
				if(i_caster->GetProto()->ItemId == GetProto()->Reagent[0])
					if(p_caster->GetItemInterface()->GetItemCount(GetProto()->Reagent[0]) < 1 + GetProto()->ReagentCount[0])
					{ 
						return SPELL_FAILED_ITEM_GONE;
					}
			}
		}

		// check if we have the required reagents
		if( !( i_caster != NULL && (i_caster->GetProto()->Flags &  ITEM_FLAGS_ENCHANT_SCROLL)) //these are enchanting scrolls and reagent was already consumend when enchanter created them
//			&& !(p_caster->removeReagentCost && GetProto()->AttributesExD & 2) )//zack : wtf is flag 2 put there for ?
			&& p_caster->removeReagentCost == false )//zack : wtf is flag 2 put there for ?
		{
			for(i=0; i<8 ;i++)
			{
				if( GetProto()->Reagent[i] == 0 || GetProto()->ReagentCount[i] == 0)
					continue;

				if(p_caster->GetItemInterface()->GetItemCount(GetProto()->Reagent[i]) < GetProto()->ReagentCount[i])
				{ 
					return SPELL_FAILED_ITEM_GONE;
				}
			}
		}

		// check if we have the required tools, totems, etc
		for(i=0; i<2 ;i++)
		{
			if( GetProto()->Totem[i] != 0)
			{
				//in 3.3 there are some items that if equipped will make you not require any totems in bag anymore
				Item *relic = p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_RANGED );
				//we have them all ?
				if( relic && relic->GetProto() && relic->GetProto()->TotemCategory == TOTEM_CATEGORY_ALL_TOTEMS )
					break;
				if( !p_caster->GetItemInterface()->GetItemCount(GetProto()->Totem[i]) )
				{ 
					return SPELL_FAILED_TOTEMS;
				}
			}
		}

		// stealth check
		//Shady: :\ ATTRIBUTES_REQ_OOC owns!!!
		/*if( GetProto()->NameHash == SPELL_HASH_STEALTH )
		{
			if( p_caster->CombatStatus.IsInCombat() )
				return SPELL_FAILED_TARGET_IN_COMBAT;
		}*/

		// check if we have the required gameobject focus
		float focusRange;

		if( GetProto()->RequiresSpellFocus)
		{
			bool found = false;

			m_caster->AquireInrangeLock(); //make sure to release lock before exit function !
			for(std::set<Object*>::iterator itr = p_caster->GetInRangeSetBegin(); itr != p_caster->GetInRangeSetEnd(); itr++ )
			{
				if((*itr)->GetTypeId() != TYPEID_GAMEOBJECT)
					continue;

				if((*itr)->GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPEID) != GAMEOBJECT_TYPE_SPELL_FOCUS)
					continue;

				GameObjectInfo *info = SafeGOCast((*itr))->GetInfo();
				if(!info)
				{
					sLog.outDebug("Warning: could not find info about game object %u",(*itr)->GetEntry());
					continue;
				}

				// professions use rangeIndex 1, which is 0yds, so we will use 5yds, which is standard interaction range.
				if(info->sound1)
					focusRange = float(info->sound1);
				else
					focusRange = GetMaxRange(dbcSpellRange.LookupEntry(GetProto()->rangeIndex));

				// check if focus object is close enough
				if(!IsInrange(p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ(), (*itr), (focusRange * focusRange)))
					continue;

				if(info->SpellFocus == GetProto()->RequiresSpellFocus)
				{
					found = true;
					break;
				}
			}

			m_caster->ReleaseInrangeLock();
			if(!found)
			{ 
				return SPELL_FAILED_REQUIRES_SPELL_FOCUS;
			}
		}

		if( GetProto()->RequiresAreaId > 0 ) 
		{
			AreaGroup *ag = dbcAreaGroup.LookupEntry( GetProto()->RequiresAreaId );
			uint8 i;
//			uint16 plrarea = p_caster->GetMapMgr()->GetAreaID( p_caster->GetPositionX(), p_caster->GetPositionY() );
			uint16 plrarea = sTerrainMgr.GetAreaID( p_caster->GetMapId(), p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ() );
			for( i = 0; i < 7; i++ )
				if( ag->AreaId[i] == plrarea )
					break;
			if( 7 == i )
			{ 
				return SPELL_FAILED_REQUIRES_AREA;
			}
		}

		// aurastate check
		if( GetProto()->CasterAuraState )
		{
			if( !p_caster->HasFlag( UNIT_FIELD_AURASTATE, GetProto()->CasterAuraState ) 
				&& p_caster->IgnoreSpellSpecialCasterStateRequirement==0
				)
				return SPELL_FAILED_CASTER_AURASTATE;
		}
		if( GetProto()->CasterAuraStateNot && p_caster->HasFlag( UNIT_FIELD_AURASTATE, GetProto()->CasterAuraStateNot ) )
		{ 
			return SPELL_FAILED_CASTER_AURASTATE;
		}
		// aura check
		if( GetProto()->casterAuraSpell && !p_caster->HasAura( GetProto()->casterAuraSpell ) )
		{ 
			return SPELL_FAILED_NOT_READY;
		}
		if( GetProto()->casterAuraSpellNot && p_caster->HasAura( GetProto()->casterAuraSpellNot ) )
		{ 
			return SPELL_FAILED_NOT_READY;
		}
	}

	// Targetted Item Checks
	if(m_targets.m_itemTarget && p_caster)
	{
		Item *i_target = NULL;

		// check if the targeted item is in the trade box
		if( m_targets.m_targetMask & TARGET_FLAG_TRADE_ITEM )
		{
			switch( GetProto()->Effect[0] )
			{
				// only lockpicking and enchanting can target items in the trade box
				case SPELL_EFFECT_OPEN_LOCK:
				case SPELL_EFFECT_ENCHANT_ITEM:
				case SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY:
				{
					// check for enchants that can only be done on your own items
					if( GetProto()->AttributesExB & FLAGS3_ENCHANT_OWN_ONLY )
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}

					// get the player we are trading with
					Player* t_player = p_caster->GetTradeTarget();
					// get the targeted trade item
					if( t_player != NULL )
						i_target = t_player->getTradeItem((uint32)m_targets.m_itemTarget);
				}
			}
		}
		// targeted item is not in a trade box, so get our own item
		else
		{
			i_target = p_caster->GetItemInterface()->GetItemByGUID( m_targets.m_itemTarget );
		}

		// check to make sure we have a targeted item
		if( i_target == NULL )
		{ 
			return SPELL_FAILED_BAD_TARGETS;
		}

		ItemPrototype* proto = i_target->GetProto();

		// check to make sure we have it's prototype info
		if(!proto || ( i_target->GetDurability() == 0 && proto->MaxDurability != 0 ) )
		{ 
			return SPELL_FAILED_BAD_TARGETS;
		}

		// check to make sure the targeted item is acceptable
		switch(GetProto()->Effect[0])
		{
			// Lock Picking Targeted Item Check
			case SPELL_EFFECT_OPEN_LOCK:
			{
				// this is currently being handled in SpellEffects
				break;
			}

			// Enchanting Targeted Item Check
			case SPELL_EFFECT_ENCHANT_ITEM:
			case SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY:
			{
				// If enchant is permanent and we are casting on Vellums
				if(GetProto()->Effect[0] == SPELL_EFFECT_ENCHANT_ITEM && GetProto()->EffectItemType[0] != 0 &&
				   (proto->ItemId == 38682 || proto->ItemId == 37602 || proto->ItemId == 43145 || 
					proto->ItemId == 39349 || proto->ItemId == 39350 || proto->ItemId == 43146 ))
				{
					// Weapons enchants
					if(GetProto()->EquippedItemClass == 2)
					{
						// These are armor vellums
						if( proto->ItemId == 38682 || proto->ItemId == 37602 || proto->ItemId == 43145 )
							return SPELL_FAILED_BAD_TARGETS;

						// You tried to cast wotlk enchant on bad item
						if(GetProto()->baseLevel == 60 && proto->ItemId != 43146)
							return SPELL_FAILED_BAD_TARGETS;
						
						// you tried to cast tbc enchant on bad item
						if(GetProto()->baseLevel == 35 && proto->ItemId == 39349)
							return SPELL_FAILED_BAD_TARGETS;

						// you tried to cast non-lvl enchant on bad item
						if(GetProto()->baseLevel == 0 && proto->ItemId != 39349)
							return SPELL_FAILED_BAD_TARGETS;

						break;
					}

					// Armors enchants
					else if(GetProto()->EquippedItemClass == 4)
					{
						// These are weapon vellums
						if( proto->ItemId == 39349 || proto->ItemId == 39350 || proto->ItemId == 43146 )
							return SPELL_FAILED_BAD_TARGETS;

						// You tried to cast wotlk enchant on bad item
						if(GetProto()->baseLevel == 60 && proto->ItemId != 43145)
							return SPELL_FAILED_BAD_TARGETS;

						// you tried to cast tbc enchant on bad item
						if(GetProto()->baseLevel == 35 && proto->ItemId == 38682)
							return SPELL_FAILED_BAD_TARGETS;

						// you tried to cast non-lvl enchant on bad item
						if(GetProto()->baseLevel == 0 && proto->ItemId != 38682)
							return SPELL_FAILED_BAD_TARGETS;
					}
					
					// If We are here it means that we have right Vellum and right enchant to cast
					break;
				}
				// check if we have the correct class, subclass, and inventory type of target item
				if( GetProto()->EquippedItemClass != (int32)proto->Class)
				{ 
					return SPELL_FAILED_BAD_TARGETS;
				}

				if( GetProto()->EquippedItemSubClass && !(GetProto()->EquippedItemSubClass & (1 << proto->SubClass)))
				{ 
					return SPELL_FAILED_BAD_TARGETS;
				}

				if( GetProto()->RequiredItemFlags && !(GetProto()->RequiredItemFlags & (1 << proto->InventoryType)))
				{ 
					return SPELL_FAILED_BAD_TARGETS;
				}

				if (GetProto()->Effect[0] == SPELL_EFFECT_ENCHANT_ITEM &&
					GetProto()->baseLevel && (GetProto()->baseLevel > proto->ItemLevel))
					return int8(SPELL_FAILED_BAD_TARGETS); // maybe there is different err code

				if( i_caster && i_caster->GetProto()->Flags == 2097216)
					break;

				if( GetProto()->AttributesExB & FLAGS3_ENCHANT_OWN_ONLY && !(i_target->IsSoulbound()))
				{ 
					return SPELL_FAILED_BAD_TARGETS;
				}

				break;
			}

			// Disenchanting Targeted Item Check
			case SPELL_EFFECT_DISENCHANT:
			{
				// check if item can be disenchanted
				if(proto->DisenchantReqSkill < 1)
				{ 
					return SPELL_FAILED_CANT_BE_DISENCHANTED;
				}

				// check if we have high enough skill
				if((int32)p_caster->_GetSkillLineCurrent(SKILL_ENCHANTING) < proto->DisenchantReqSkill)
				{ 
					return SPELL_FAILED_CANT_BE_DISENCHANTED_SKILL;
				}

				break;
			}

			// Feed Pet Targeted Item Check
			case SPELL_EFFECT_FEED_PET:
			{
				Pet *pPet = p_caster->GetSummon();

				// check if we have a pet
				if(!pPet)
				{ 
					return SPELL_FAILED_NO_PET;
				}
				
				// check if pet lives
				if( !pPet->isAlive() )
				{ 
					return SPELL_FAILED_TARGETS_DEAD;
				}

				// check if item is food
				if(!proto->FoodType)
				{ 
					return SPELL_FAILED_BAD_TARGETS;
				}

				// check if food type matches pets diet
				if(!(pPet->GetPetDiet() & (1 << (proto->FoodType - 1))))
				{ 
					return SPELL_FAILED_WRONG_PET_FOOD;
				}

				// check food level: food should be max 30 lvls below pets level
				if(pPet->getLevel() > proto->ItemLevel + 30)
				{ 
					return SPELL_FAILED_FOOD_LOWLEVEL;
				}

				break;
			}

			// Prospecting Targeted Item Check
			case SPELL_EFFECT_PROSPECTING:
			{
				// check if the item can be prospected
				if(!(proto->Flags & ITEM_FLAG_PROSPECTABLE))
				{ 
					return SPELL_FAILED_CANT_BE_PROSPECTED;
				}

				// check if we have at least 5 of the item
				if(p_caster->GetItemInterface()->GetItemCount(proto->ItemId) < 5)
				{ 
					return SPELL_FAILED_ITEM_GONE;
				}

				// check if we have high enough skill
				if(p_caster->_GetSkillLineCurrent(SKILL_JEWELCRAFTING) < proto->RequiredSkillRank)
				{ 
					return SPELL_FAILED_LOW_CASTLEVEL;
				}

				break;
			}
			// Milling Targeted Item Check
			case SPELL_EFFECT_MILLING:
			{
				// check if the item can be prospected
				if(!(proto->Flags & ITEM_FLAG_MILLABLE))
				{ 
					return SPELL_FAILED_CANT_BE_PROSPECTED;
				}

				// check if we have at least 5 of the item
				if(p_caster->GetItemInterface()->GetItemCount(proto->ItemId) < 5)
				{ 
					return SPELL_FAILED_ITEM_GONE;
				}

				// check if we have high enough skill
				if(p_caster->_GetSkillLineCurrent(SKILL_INSCRIPTION) < proto->RequiredSkillRank)
				{ 
					return SPELL_FAILED_LOW_CASTLEVEL;
				}

				break;
			}
		}
	}

	// set up our max Range
	float maxRange = GetMaxRange( dbcSpellRange.LookupEntry( GetProto()->rangeIndex ) );
		// latency compensation!!
		// figure out how much extra distance we need to allow for based on our movespeed and latency.
		if( u_caster && m_caster->GetMapMgr() && m_targets.m_unitTarget )
		{
			Unit * utarget;

			utarget = m_caster->GetMapMgr()->GetUnit( m_targets.m_unitTarget );
			if( utarget && utarget->IsPlayer() && SafePlayerCast( utarget )->m_isMoving )
				{
					// this only applies to PvP.
					uint32 lat = SafePlayerCast( utarget )->GetSession() ? SafePlayerCast( utarget )->GetSession()->GetLatency() : 0;

					// if we're over 500 get fucked anyway.. your gonna lag! and this stops cheaters too
					lat = ( lat > 500 ) ? 500 : lat;

					// calculate the added distance
					maxRange += ( u_caster->m_runSpeed * 0.001f ) * float( lat );
				}
		}
	if( Need_SM_Apply(GetProto()) && u_caster != NULL )
	{
		SM_FFValue( u_caster->SM_FRange, &maxRange, GetProto()->SpellGroupType );
		SM_PFValue( u_caster->SM_PRange, &maxRange, GetProto()->SpellGroupType );
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		float spell_flat_modifers=0;
		float spell_pct_modifers=0;
		SM_FFValue(u_caster->SM_FRange,&spell_flat_modifers,GetProto()->SpellGroupType);
		SM_FFValue(u_caster->SM_PRange,&spell_pct_modifers,GetProto()->SpellGroupType);
		if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
			printf("!!!!!spell range bonus mod flat %f , spell range bonus pct %f , spell range %f, spell group %u\n",spell_flat_modifers,spell_pct_modifers,maxRange,GetProto()->SpellGroupType);
#endif
	}

	// Targeted Location Checks (AoE spells)
	if( m_targets.m_targetMask == TARGET_FLAG_DEST_LOCATION )
	{
		if( !IsInrange( m_targets.m_destX, m_targets.m_destY, m_targets.m_destZ, m_caster, ( maxRange * maxRange ) ) )
		{ 
			return SPELL_FAILED_OUT_OF_RANGE;
		}
	}

	// Targeted Unit Checks
	if(m_targets.m_unitTarget)
	{
		target = (m_caster->IsInWorld()) ? m_caster->GetMapMgr()->GetUnit(m_targets.m_unitTarget) : NULL;

		if(target)
		{
			// Partha: +2.52yds to max range, this matches the range the client is calculating.
			// see extra/supalosa_range_research.txt for more info

			if( tolerate ) // add an extra 33% to range on final check (squared = 1.78x)
			{
//				float localrange=maxRange + 2.52f;
//				float localrange=maxRange + target->GetFloatValue(UNIT_FIELD_BOUNDINGRADIUS);
				float localrange=maxRange + target->GetModelHalfSize();
				if( !IsInrange( m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ(), target, ( localrange * localrange * 1.78f ) ) )
				{ 
					return SPELL_FAILED_OUT_OF_RANGE;
				}
			}
			else
			{
//				float localrange=maxRange + 2.52f;
//				float localrange=maxRange + target->GetFloatValue(UNIT_FIELD_BOUNDINGRADIUS);
				float localrange=maxRange + target->GetModelHalfSize();
				if( !IsInrange( m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ(), target, ( localrange * localrange ) ) )
				{ 
					return SPELL_FAILED_OUT_OF_RANGE;
				}
			}

			/* Target OOC check */
			if( ( GetProto()->AttributesEx & ATTRIBUTESEX_REQ_OOC_TARGET ) && target->CombatStatus.IsInCombat() )
			{ 
				return SPELL_FAILED_TARGET_IN_COMBAT;
			}

			if( p_caster != NULL )
			{
				if( GetProto()->Id == SPELL_RANGED_THROW)
				{
					Item * itm = p_caster->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_RANGED);
					if(!itm || (itm->GetDurability() == 0 && itm->GetProto()->MaxDurability > 0 ) )
					{ 
						return SPELL_FAILED_NO_AMMO;
					}
				}

				if (sWorld.Collision) {
					if (p_caster->GetMapId() == target->GetMapId() && !CollideInterface.CheckLOS(p_caster->GetMapId(),p_caster->GetPositionNC(),target->GetPositionNC()))
					{ 
						return SPELL_FAILED_LINE_OF_SIGHT;
					}
				}

				// check aurastate
				if( GetProto()->TargetAuraState )
				{
					if( !target->HasFlag( UNIT_FIELD_AURASTATE, GetProto()->TargetAuraState ) 
						&& p_caster->IgnoreSpellSpecialCasterStateRequirement==0 
						)
						return SPELL_FAILED_TARGET_AURASTATE;
				}
				if( GetProto()->TargetAuraStateNot && target->HasFlag( UNIT_FIELD_AURASTATE, GetProto()->TargetAuraStateNot ) )
				{ 
					return SPELL_FAILED_TARGET_AURASTATE;
				}
				
				// check aura
				if( GetProto()->targetAuraSpell && !target->HasAura( GetProto()->targetAuraSpell ) )
				{ 
					return SPELL_FAILED_NOT_READY;
				}
				if( GetProto()->targetAuraSpellNot && target->HasAura( GetProto()->targetAuraSpellNot ) )
				{ 
					return SPELL_FAILED_NOT_READY;
				}

				if(target->IsPlayer())
				{
					// disallow spell casting in sanctuary zones
					// allow attacks in duels
					if( p_caster->DuelingWith != target && !isFriendly( p_caster, target ) )
					{
						AreaTable* atCaster = dbcArea.LookupEntry( p_caster->GetAreaID() );
						AreaTable* atTarget = dbcArea.LookupEntry( SafePlayerCast( target )->GetAreaID() );
						if( atCaster->AreaFlags & 0x800 || atTarget->AreaFlags & 0x800 )
						{ 
							return SPELL_FAILED_NOT_HERE;
						}
					}
				}
				else
				{
					if (target->GetAIInterface()->GetIsSoulLinked() && u_caster && target->GetAIInterface()->getSoullinkedWith() != u_caster)
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}

				// pet training
				if( GetProto()->EffectImplicitTargetA[0] == EFF_TARGET_PET &&
					GetProto()->Effect[0] == SPELL_EFFECT_LEARN_SPELL )
				{
					Pet *pPet = p_caster->GetSummon();
					// check if we have a pet
					if( pPet == NULL )
					{ 
						return SPELL_FAILED_NO_PET;
					}

					// other checks
					SpellEntry* trig = dbcSpell.LookupEntry( GetProto()->EffectTriggerSpell[0] );
					if( trig == NULL )
					{ 
						return SPELL_FAILED_SPELL_UNAVAILABLE;
					}

					uint32 status = pPet->CanLearnSpell( trig );
					if( status != 0 )
					{ 
						return (uint8)(status);
					}
				}

				if( GetProto()->EffectApplyAuraName[0] == SPELL_AURA_MOD_POSSESS
					|| GetProto()->EffectApplyAuraName[0] == SPELL_AURA_MOD_CHARM
					)//mind control or enslave demon
				{
					if( GetProto()->EffectBasePoints[0])//got level req;
					{
						if((int32)target->getLevel() > GetProto()->EffectBasePoints[0]+1 + int32(p_caster->getLevel() - GetProto()->spellLevel))
						{ 
							return SPELL_FAILED_HIGHLEVEL;
						}
						else if(target->GetTypeId() == TYPEID_UNIT)
						{
							Creature * c = SafeCreatureCast(target);
							if (c&&c->GetCreatureInfo()&&c->GetCreatureInfo()->Rank > ELITE_ELITE)
							{ 
								return SPELL_FAILED_CANT_BE_CHARMED;
							}
						}
					}
				}
			}

			// scripted spell stuff
			switch(GetProto()->Id)
			{
				case 2825:	//bloodlust
				case 32182: //heroism
					{
						if( target->HasAurasWithNameHash( SPELL_HASH_SATED ) )
							return SPELL_FAILED_NOT_READY;	//i wonder what is correct error code
						if( target->HasAurasWithNameHash( SPELL_HASH_EXHAUSTION ) )
							return SPELL_FAILED_NOT_READY;	//i wonder what is correct error code
					}break;
				case 61336: //survival instincts
				{
					if( target->IsPlayer() && SafePlayerCast(target)->IsInFeralForm() == false )
						return SPELL_FAILED_ONLY_SHAPESHIFT;
				}break;
				case 1515: // tame beast
				{
                    if( !p_caster )
						return PETTAME_INVALIDCREATURE;
					uint8 result = 0;
					Unit* tgt = unitTarget;
					if( tgt == NULL )
					{
						// we have to pick a target manually as this is a dummy spell which triggers tame effect at end of channeling
						if( p_caster->GetSelection() != 0 )
							tgt =  p_caster->GetMapMgr()->GetUnit( p_caster->GetSelection() );
						else
							return SPELL_FAILED_UNKNOWN;
					}
					if( tgt == NULL )
						return PETTAME_INVALIDCREATURE;

					Creature *tame = tgt->GetTypeId() == TYPEID_UNIT ? SafeCreatureCast( tgt ) : NULL;
                    
					if ( tame == NULL )
						result = PETTAME_INVALIDCREATURE;
					else if( !tame->isAlive() )
						result = PETTAME_DEAD;
					else if( tame->IsPet() )
						result = PETTAME_CREATUREALREADYOWNED;
					else if( !tame->GetCreatureInfo() || tame->GetCreatureInfo()->Type != BEAST || !tame->GetCreatureInfo()->Family )
						result = PETTAME_NOTTAMEABLE;
					else if( !p_caster->isAlive() || p_caster->getClass() != HUNTER )
						result = PETTAME_UNITSCANTTAME;
					else if( tame->getLevel() > p_caster->getLevel() )
						result = PETTAME_TOOHIGHLEVEL;
					else if( p_caster->GetSummon() || p_caster->GetUnstabledPetNumber() )
						result = PETTAME_ANOTHERSUMMONACTIVE;
					else if( p_caster->GetPetCount() >= 5 )
						result = PETTAME_TOOMANY;
					//cannot tame exotic beasts
					else if( ( tame->GetCreatureInfo()->Family == 45 || tame->GetCreatureInfo()->Family == 46 || tame->GetCreatureInfo()->Family == 38 || tame->GetCreatureInfo()->Family == 39 || tame->GetCreatureInfo()->Family == 42 || tame->GetCreatureInfo()->Family == 43 || tame->GetCreatureInfo()->Family == 41 )
							&& p_caster->HasPassiveAurasWithNameHash( SPELL_HASH_BEAST_MASTERY ) == false )
						result = PETTAME_CANTCONTROLEXOTIC;
					else
					{
						CreatureFamilyEntry* cf = dbcCreatureFamily.LookupEntry( tame->GetCreatureInfo()->Family );
						if( cf && !cf->tameable )
							result = PETTAME_NOTTAMEABLE;
					}
					if( result != 0 )
					{
						SendTameFailure( result );
						return SPELL_FAILED_DONT_REPORT;
					}
				}break;
				case 603: //curse of doom, can't be casted on players
				case 30910:
				{
					if(target->IsPlayer())
					{ 
						return SPELL_FAILED_TARGET_IS_PLAYER;
					}
				}break;
				case 13907: // Smite Demon
				{
					if ( target->IsPlayer() || target->getClass()!=TARGET_TYPE_DEMON )
					{ 
						return SPELL_FAILED_SPELL_UNAVAILABLE;
					}
				}break;
				// Dash (can't use namehash, as there is hunters/pets ability using same namehash)
				case 1850:
				case 9821:
				case 33357:
				{
					if(p_caster && p_caster->GetShapeShift() != FORM_CAT)
					{ 
						return SPELL_FAILED_ONLY_SHAPESHIFT;
					}
				}break;
				case 982: //Revive Pet
				{
					if( !p_caster )
						return SPELL_FAILED_BAD_TARGETS;
					Pet *pPet = p_caster->GetSummon();
					if(pPet && !pPet->IsDead())
					{ 
						return SPELL_FAILED_TARGET_NOT_DEAD;
					}
				}break;
/*				case 66474:	//Throw Net
				{
					if(target->GetEntry() != 29618 || target->isAlive())
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 52252:	//Charm Channel
				case 52244:	//Charm Channel
				{
					if(target->GetEntry() != 28750 || target->isAlive()) //Blight Geist
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 52487:	//Charm Channel
				{
					if(target->GetEntry() != 28843 || target->isAlive())//Bloated Abomination
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 53102:	//Charm Channel
				{
					if(target->GetEntry() != 28931 || target->isAlive())//Blightblood Troll
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 52389:	//Charm Channel
				{
					if(target->GetEntry() != 28802 || target->isAlive())//Servant of Drakuru
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 60983:	//Bright Flare
				{
					if(target->GetEntry() != 30164 || target->isAlive())
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 66588:	//Flaming Spear
				{
					if(target->GetEntry() != 34925 || target->isAlive())
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 43354:	//Enchanted Ice Core	-> freez target
				{
					if(target->GetEntry() != 23876 || target->isAlive())
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 63124:	//Incapacitate Maloric	-> stun target
				{
					if(target->GetEntry() != 33498 || target->isAlive())
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 2699:
				{
					if(target->GetEntry() != 5307 || target->isAlive())
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 30877:
				{
					if(target->GetEntry() != 17326 && target != m_caster)
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 34665:
				{
					if(target->GetEntry() != 16880)
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 3607:
				{
					if(target->GetEntry() != 2530)
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 36310:
				{
					if(target->GetEntry() != 20058)
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 41291:
				{
					if(target->GetEntry() != 22357)
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 28369: // Gas
				{
					if( !target->IsCreature() || target->GetEntry() != 18879 ) // Phase Hunter
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				} break;
				case 29528: // Inoculation
				{
					if( !target->IsCreature() || target->GetEntry() != 16518 ) // Nestlewood Owlkin
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 41621: // Wolpertinger Net
				{
					if(!target->IsCreature() || target->GetEntry()!=23487 ) // Wild Wolpertinger
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 32578: // Gor'drek's Ointment
				{
					if(!target->IsCreature() || target->GetEntry()!=20748) // Thunderlord Dire Wolf NPC
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 44997: // Converting Sentry
				{
					if( !target->IsCreature() || target->GetEntry()!=24972 ) // Erratic Sentry
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}

					if( !target->IsCreature() || !target->IsDead() )
					{ 
						return SPELL_FAILED_TARGET_NOT_DEAD;
					}
				}break;
				case 30077: // Carinda's Retribution
				{
					if(!target->IsCreature() || target->GetEntry()!=17226 ) // Viera Sunwhisper
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 32825: // Soul Cannon
				{
					if( !target->IsCreature() || target->GetEntry() != 22357 ) // Reth'hedron the Subduer
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 19938: // Awaken Peon (Foreman's Blackjack)
				{
					if( !target->IsCreature() || target->GetEntry() != 10556 ) // Lazy Peon
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 27907: // Disciplinary Rod
				{
					if(!target->IsCreature() || target->GetEntry() != 15945 && target->GetEntry() != 15941 ) // 'Apprentice Meledor' and 'Apprentice Ralen'
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				// disable spell
				case 38554: //Absorb Eye of Grillok
				{
					// do not allow spell to be cast
					if( !target->IsCreature() || target->GetEntry()!= 19440 )
					{ 
						return SPELL_FAILED_SPELL_UNAVAILABLE;
					}
				}break;
				case 36314: //The Seer's Presence
				{
					// this spell can be cast only on socrethar. Otherwife cool exploit
					if(target->IsPlayer() || !target->IsUnit())
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					// this spell should be used only for a specific quest on specific monster = "Socrethar"
					if(target->GetEntry()!=20132) //nasty fixed numbers :(
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}break;
				case 38177: //Blackwhelp Net
				{
					if( !target->IsCreature() || target->GetEntry()!= 21387 ) // castable only on Wyrmcult Blackwhelps
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				} break;
				case 35772: // Energy Field Modulator
				{
					if ( !target->IsCreature() || target->GetEntry() != 20774 ) // castable only on Farahlon Lasher
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				} break;
				case 19688: // Taming rod
					if( !target || target->GetEntry() != 2956 ) // Adult Plainstrider
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 19694: // Taming rod
					if( !target || target->GetEntry() != 3099 ) // Dire Mottled Boar
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 19693: // Taming rod
					if( !target || target->GetEntry() != 1998) // Webwood Lurker
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 19674: // Taming rod
					if( !target || target->GetEntry() != 1126) // Large Crag Boar
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 19697: // Taming rod
					if( !target || target->GetEntry() != 3126) // Armored Scorpid
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 19696: // Taming rod
					if( !target || target->GetEntry() != 3107) // Surf Crawler
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 19687: // Taming rod
					if( !target || target->GetEntry() != 1201) // Snow Leopard
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 19548: // Taming rod
					if( !target || target->GetEntry() != 1196) // Ice Claw Bear
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 19689: // Taming rod
					if( !target || target->GetEntry() != 2959) // Prairie Stalker
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 19692: // Taming rod
					if( !target || target->GetEntry() != 2970) // Swoop
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 19699: // Taming rod
					if( !target || target->GetEntry() != 2043) // Nightsaber Stalker
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 19700: // Taming rod
					if( !target || target->GetEntry() != 1996) // Strigid Screecher
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 30099: // Taming rod
					if( !target || target->GetEntry() != 15650) // Crazed Dragonhawk
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 30105: // Taming rod
					if( !target || target->GetEntry() != 16353) // Mistbat
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 30102: // Taming rod
					if( !target || target->GetEntry() != 15652) // Elder Springpaw
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 30646: // Taming totem
					if( !target || target->GetEntry() != 17217) // Barbed Crawler
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 30653: // Taming totem
					if( !target || target->GetEntry() != 17374) // Greater Timberstrider
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 30654: // Taming totem
					if( !target || target->GetEntry() != 17203) // Nightstalker
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 47394: // Kurun's Blessing
					if( !target || target->GetEntry() != 26261) // Grizzly Hills Giant
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
					break;
				case 4130: // Banish Burning Exile
				{
					if(target->GetEntry()!= 2760) // target needs to be a Burning Exile
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				} break;
				case 4131:// Banish Cresting Exile
				{
					if(target->GetEntry()!= 2761) // target needs to be a Cresting Exile
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				} break;
				case 4132:// Banish Thundering Exile
				{
					if(target->GetEntry()!= 2762) // target needs to be a Thundering Exile
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				} break;/**/
			}

			// if the target is not the unit caster and not the masters pet
			if(target != u_caster && !m_caster->IsPet())
			{
/*				switch( GetProto()->NameHash )
				{
					case SPELL_HASH_EXORCISM:
					{
						if( target->IsPlayer() )
						{ 
							return SPELL_FAILED_BAD_TARGETS;
						}
					}break;
				}*/

				/***********************************************************
				* Inface checks, these are checked in 2 ways
				* 1e way is check for damage type, as 3 is always ranged
				* 2e way is trough the data in the extraspell db
				*
				**********************************************************/

				/* burlex: units are always facing the target! */
				if( p_caster && ( GetProto()->FacingCasterFlags & ( CASTER_FACE_FACING | CASTER_FACE_FACING_WIDE | CASTER_FACE_FACING_WIDE2 | TARGET_FACE_CASTER ) ) )
				{
					if( ( GetProto()->FacingCasterFlags & TARGET_FACE_CASTER ) && u_caster->isInFront(target) == false )
					{
						return SPELL_FAILED_UNIT_NOT_INFRONT;
					}
					else if( ( GetProto()->AttributesExB & FLAGS3_REQ_BEHIND_TARGET ) && target->isInFront(u_caster) )
					{ 
						return SPELL_FAILED_NOT_BEHIND;
					}
					else if( !u_caster->isInFront(target) )
					{ 
						return SPELL_FAILED_UNIT_NOT_INFRONT;
					}
				}
			}

			// if target is already skinned, don't let it be skinned again
			if( GetProto()->Effect[0] == SPELL_EFFECT_SKINNING) // skinning
				if(target->IsUnit() && (SafeCreatureCast(target)->Skinned) )
				{ 
					return SPELL_FAILED_TARGET_UNSKINNABLE;
				}

			// all spells with target 61 need to be in group or raid
			// TODO: need to research this if its not handled by the client!!!
			/*if(
				GetProto()->EffectImplicitTargetA[0] == EFF_TARGET_AREAEFFECT_PARTY_AND_CLASS ||
				GetProto()->EffectImplicitTargetA[1] == EFF_TARGET_AREAEFFECT_PARTY_AND_CLASS ||
				GetProto()->EffectImplicitTargetA[2] == EFF_TARGET_AREAEFFECT_PARTY_AND_CLASS)
			{
				if( target->IsPlayer() && !SafePlayerCast( target )->InGroup() )
					return SPELL_FAILED_NOT_READY;//return SPELL_FAILED_TARGET_NOT_IN_PARTY or SPELL_FAILED_TARGET_NOT_IN_PARTY;
			}*/

			// pet's owner stuff
			/*if (GetProto()->EffectImplicitTargetA[0] == EFF_TARGET_PET_MASTER ||
				GetProto()->EffectImplicitTargetA[1] == EFF_TARGET_PET_MASTER ||
				GetProto()->EffectImplicitTargetA[2] == EFF_TARGET_PET_MASTER)
			{
				if (!target->IsPlayer())
					return SPELL_FAILED_TARGET_NOT_PLAYER; //if you are there something is very wrong
			}*/

			// target 39 is fishing, all fishing spells are handled
			if( GetProto()->EffectImplicitTargetA[0] == EFF_TARGET_SELF_FISHING )//||
			 //GetProto()->EffectImplicitTargetA[1] == EFF_TARGET_SELF_FISHING ||
			 //GetProto()->EffectImplicitTargetA[2] == EFF_TARGET_SELF_FISHING)
			{
				uint32 entry = GetProto()->EffectMiscValue[0];
				if(entry == GO_FISHING_BOBBER)
				{
					//uint32 mapid = p_caster->GetMapId();
					float px=u_caster->GetPositionX();
					float py=u_caster->GetPositionY();
					//float pz=u_caster->GetPositionZ();
					float orient = m_caster->GetOrientation();
					float posx = 0,posy = 0,posz = 0;
					float co = cos(orient);
					float si = sin(orient);
					MapMgr * map = m_caster->GetMapMgr();

					float r;
					float land_height;
					for(r=20; r>10; r--)
					{
						posx = px + r * co;
						posy = py + r * si;
						land_height = map->GetLandHeight(posx,posy);
						if( (sTerrainMgr.GetLiquidFlags( u_caster->GetMapId(), posx, posy, INVALID_HEIGHT ) & MAP_LIQUID_TYPE_WATER) == 0  )//water
							continue;
						posz = sTerrainMgr.GetLiquidHeight(u_caster->GetMapId(),posx,posy, 0.0f );
						if( posz == VMAP_VALUE_NOT_INITIALIZED )
							continue;
						if( posz > land_height )//water
							break;
					}
					if( r<=10 || posz <= land_height )
					{ 
						return SPELL_FAILED_NOT_FISHABLE;
					}

					// if we are already fishing, dont cast it again
					if(p_caster->GetSummonedObject())
						if(p_caster->GetSummonedObject()->GetEntry() == GO_FISHING_BOBBER)
						{ 
							return SPELL_FAILED_SPELL_IN_PROGRESS;
						}
					m_targets.m_destX = posx;
					m_targets.m_destY = posy;
					m_targets.m_destZ = posz;
				}
			}

			if( p_caster != NULL )
			{
				if( GetProto()->NameHash == SPELL_HASH_GOUGE )// Gouge
					if(!target->isInFront(p_caster))
					{ 
						return SPELL_FAILED_NOT_INFRONT;
					}

			
				//Shady: use SpellEntry::in_front_status = SPELL_INFRONT_STATUS_REQUIRE_INFRONT
				/*if( GetProto()->NameHash == SPELL_HASH_MOONFIRE )// Moonfire
					if(!p_caster->isInFront(target))
						return SPELL_FAILED_UNIT_NOT_INFRONT;*/


				if( GetProto()->Category==1131)//Hammer of wrath, requires target to have 20- % of hp
				{
					if(target->GetUInt32Value(UNIT_FIELD_HEALTH) == 0)
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}

					if(target->GetUInt32Value(UNIT_FIELD_MAXHEALTH)/target->GetUInt32Value(UNIT_FIELD_HEALTH)<5)
					{ 
						 return SPELL_FAILED_BAD_TARGETS;
					}
				}
				/*else if( GetProto()->Category==672)//Conflagrate, requires immolation spell on victim
				{
					if(!target->HasAurasWithNameHash( SPELL_HASH_IMMOLATE ))
					{ 
						return SPELL_FAILED_BAD_TARGETS;
					}
				}*/

				if(target->dispels[GetProto()->DispelType])
				{ 
					return SPELL_FAILED_DAMAGE_IMMUNE;		
				}

				// Removed by Supalosa and moved to 'completed cast'
				//if(target->MechanicsDispels[GetProto()->MechanicsType])
				//	return SPELL_FAILED_PREVENTED_BY_MECHANIC-1; // Why not just use 	SPELL_FAILED_DAMAGE_IMMUNE                                   = 144,
			}

			// if we're replacing a higher rank, deny it
			AuraCheckResponse acr = target->AuraCheck(GetProto()->NameHash, GetProto()->RankNumber,m_caster);
			if( acr.Error == AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT )
			{ 
				return SPELL_FAILED_AURA_BOUNCED;
			}

			//check if we are trying to stealth or turn invisible but it is not allowed right now
			if( IsStealthSpell() || IsInvisibilitySpell() )
			{
				//if we have Faerie Fire, we cannot stealth or turn invisible
				if( u_caster->HasNegativeAuraWithNameHash( SPELL_HASH_FAERIE_FIRE ) || u_caster->HasNegativeAuraWithNameHash( SPELL_HASH_FAERIE_FIRE__FERAL_ ) )
				{ 
					return SPELL_FAILED_SPELL_UNAVAILABLE;
				}
			}

			/*SpellReplacement*rp=objmgr.GetReplacingSpells(GetProto()->Id);
			if(rp)
			{
				if(isAttackable(u_caster,target))//negative, replace only our own spell
				{
					for(uint32 x=0;x<rp->count;x++)
					{
						if(target->HasActiveAura(rp->spells[x],m_caster->GetGUID()))
						{
							return SPELL_FAILED_AURA_BOUNCED;
						}
					}
				}
				else
				{
					for(uint32 x=0;x<rp->count;x++)
					{
						if(target->HasActiveAura(rp->spells[x]))
						{
							return SPELL_FAILED_AURA_BOUNCED;
						}
					}
				}
			}	*/
		}
	}

	// Special State Checks (for creatures & players)
	if( u_caster )
	{
		if( u_caster->SchoolCastPrevent[GetProto()->School] >= getMSTime() )
		{
			// HACK FIX
			switch( GetProto()->NameHash )
			{
				// This is actually incorrect. school lockouts take precedence over silence.
				// So ice block/divine shield are not usable while their schools are locked out,
				// but can be used while silenced.
				/*case SPELL_HASH_ICE_BLOCK: //Ice Block
				case 0x9840A1A6: //Divine Shield
					break;
				*/
				//we may cast only killing spree while inside killing spree
				case SPELL_HASH_KILLING_SPREE:
				case SPELL_HASH_BLADESTORM:
					{}break;
				case SPELL_HASH_WILL_OF_THE_FORSAKEN: //Will of the Forsaken
					{
						if( u_caster->m_special_state & ( UNIT_STATE_FEAR | UNIT_STATE_CHARM | UNIT_STATE_SLEEP ) )
							break;
					}break;

				case SPELL_HASH_DEATH_WISH: //Death Wish
				case SPELL_HASH_FEAR_WARD: //Fear Ward
				case SPELL_HASH_BERSERKER_RAGE: //Berserker Rage
					{
						if( u_caster->m_special_state & UNIT_STATE_FEAR )
							break;
					}break;

				// {Insignia|Medallion} of the {Horde|Alliance}
				case 0xC7C45478:				//Immune Movement Impairment and Loss of Control
				//case 0x048c32f9:				// insignia of the alliance/horde
				case SPELL_HASH_PVP_TRINKET:	// Stop fucking renaming the spell, Blizzard! (This time it's PvP Trinket)
				case SPELL_HASH_EVERY_MAN_FOR_HIMSELF:
					break;
//					if( u_caster->m_special_state & ( UNIT_STATE_FEAR | UNIT_STATE_CHARM | UNIT_STATE_SLEEP | UNIT_STATE_ROOT | UNIT_STATE_STUN | UNIT_STATE_CONFUSE | UNIT_STATE_SNARE ) )
//						break;
				case SPELL_HASH_BARKSKIN: // Barksin
				case SPELL_HASH_LIVING_FREE_ACTION:
				{ // This spell is usable while stunned, frozen, incapacitated, feared or asleep.  Lasts 12 sec.
					if( u_caster->m_special_state & ( UNIT_STATE_STUN | UNIT_STATE_FEAR | UNIT_STATE_SLEEP ) ) // Uh, what unit_state is Frozen? (freezing trap...)
						break;
				}

				default:
					return SPELL_FAILED_SILENCED;
			}
		}
		if( u_caster->m_silenced && GetProto()->School != NORMAL_DAMAGE )// can only silence non-physical
		{
			switch( GetProto()->NameHash )
			{
				case SPELL_HASH_ICE_BLOCK: //Ice Block
				case SPELL_HASH_DIVINE_SHIELD: //Divine Shield
				case SPELL_HASH_DISPERSION:
					break;
				// {Insignia|Medallion} of the {Horde|Alliance}
				case SPELL_HASH_PVP_TRINKET:	// Stop fucking renaming the spell, Blizzard! (This time it's PvP Trinket)
				case SPELL_HASH_EVERY_MAN_FOR_HIMSELF:
				case SPELL_HASH_LIVING_FREE_ACTION:
					if( u_caster->m_special_state & ( UNIT_STATE_STUN | UNIT_STATE_FEAR | UNIT_STATE_SLEEP | UNIT_STATE_POLYMORPH) ) // Uh, what unit_state is Frozen? (freezing trap...)
						break;

				default:
					return SPELL_FAILED_SILENCED;
			}
		}

		//zack : aa wtf ? breaking this, will fix after report comes in what this was for
/*		if(target) // -Supalosa- Shouldn't this be handled on Spell Apply? 
		{
			for( int i = 0; i < 3; i++ ) // if is going to cast a spell that breaks stun remove stun auras, looks a bit hacky but is the best way i can find
			{
				if( GetProto()->EffectApplyAuraName[i] == SPELL_AURA_MECHANIC_IMMUNITY )
				{
					target->RemoveAllAurasByMechanic( GetProto()->EffectMiscValue[i] , (uint32)(-1) , true );
					// Remove all debuffs of that mechanic type.
					// This is also done in SpellAuras.cpp - wtf?
				}
				/*
				if( GetProto()->EffectApplyAuraName[i] == SPELL_AURA_MECHANIC_IMMUNITY && (GetProto()->EffectMiscValue[i] == 12 || GetProto()->EffectMiscValue[i] == 17))
				{
					for(uint32 x=MAX_POSITIVE_AURAS;x<MAX_AURAS;x++)
						if(target->m_auras[x])
							if(target->m_auras[x]->GetSpellProto()->MechanicsType == GetProto()->EffectMiscValue[i])
								target->m_auras[x]->Remove();
				}
				*/
/*			}
		}*/

		if( u_caster->IsPacified() && GetProto()->School == NORMAL_DAMAGE ) // only affects physical damage
		{
			// HACK FIX
			switch( GetProto()->NameHash )
			{
				case SPELL_HASH_ICE_BLOCK: //Ice Block
				case SPELL_HASH_DIVINE_SHIELD: //Divine Shield
				case SPELL_HASH_WILL_OF_THE_FORSAKEN: //Will of the Forsaken
				{
					if( u_caster->m_special_state & (UNIT_STATE_FEAR | UNIT_STATE_CHARM | UNIT_STATE_SLEEP))
						break;
				}break;
				// {Insignia|Medallion} of the {Horde|Alliance}
				case SPELL_HASH_PVP_TRINKET:	// Stop fucking renaming the spell, Blizzard! (This time it's PvP Trinket)
				case SPELL_HASH_EVERY_MAN_FOR_HIMSELF:
				case SPELL_HASH_LIVING_FREE_ACTION:
					if( u_caster->m_special_state & ( UNIT_STATE_STUN | UNIT_STATE_FEAR | UNIT_STATE_SLEEP | UNIT_STATE_POLYMORPH) ) // Uh, what unit_state is Frozen? (freezing trap...)
						break;

				default:
					return SPELL_FAILED_PACIFIED;
			}
		}

		if( u_caster->IsStunned() || u_caster->IsFeared())
		{
			// HACK FIX
			switch( GetProto()->NameHash )
			{
				case SPELL_HASH_ICE_BLOCK: //Ice Block
				case SPELL_HASH_DIVINE_SHIELD: //Divine Shield
				case SPELL_HASH_DIVINE_PROTECTION: //Divine Protection
				case SPELL_HASH_BARKSKIN: //Barkskin
				/* -Supalosa- For some reason, being charmed or sleep'd is counted as 'Stunned'.
				Check it: http://www.wowhead.com/?spell=700 */
				case 0xC7C45478:						/* Immune Movement Impairment and Loss of Control (PvP Trinkets) */
				case SPELL_HASH_WILL_OF_THE_FORSAKEN: /* Will of the Forsaken (Undead Racial) */
				//case 0x048c32f9:						// insignia of the alliance/horde
				case SPELL_HASH_PVP_TRINKET:			// Stop fucking renaming the spell, Blizzard! (This time it's PvP Trinket)
				case SPELL_HASH_EVERY_MAN_FOR_HIMSELF:
				case SPELL_HASH_DISPERSION:
				case SPELL_HASH_HAND_OF_FREEDOM:
				case SPELL_HASH_BLINK:
				case SPELL_HASH_THUNDERSTORM:
				case SPELL_HASH_LIVING_FREE_ACTION:
					break;

				case SPELL_HASH_PAIN_SUPPRESSION:
					{
						if( u_caster->IsFeared() || p_caster == NULL || p_caster->HasGlyphWithID( GLYPH_PRIEST_PAIN_SUPRESSION ) == false )
							return SPELL_FAILED_STUNNED;
					}break;
				case SPELL_HASH_BERSERKER_RAGE://Berserker Rage frees the caster from fear effects.
				case SPELL_HASH_BERSERK://this should be only druid berserk 50334
					{
						if( u_caster->IsStunned() )
							return SPELL_FAILED_STUNNED;
					}break;
				case SPELL_HASH_SHAMANISTIC_RAGE:
					{
						if( u_caster->IsFeared() )
							return SPELL_FAILED_STUNNED;
					}break;

				default:
					return SPELL_FAILED_STUNNED;
			}
		}

		if(u_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT) > 0)
		{
			SpellEntry * t_spellInfo = (u_caster->GetCurrentSpell() ? u_caster->GetCurrentSpell()->GetProto() : NULL);

			if(!t_spellInfo || !m_triggeredSpell)
				return SPELL_FAILED_SPELL_IN_PROGRESS;
			else if (t_spellInfo)
			{
				if(
					t_spellInfo->EffectTriggerSpell[0] != GetProto()->Id &&
					t_spellInfo->EffectTriggerSpell[1] != GetProto()->Id &&
					t_spellInfo->EffectTriggerSpell[2] != GetProto()->Id)
				{
					return SPELL_FAILED_SPELL_IN_PROGRESS;
				}
			}
		}
	}

	// no problems found, so we must be ok
	return SPELL_CANCAST_OK;
}

void Spell::RemoveItems()
{
	// Item Charges & Used Item Removal
	if(i_caster)
	{
		// Stackable Item -> remove 1 from stack
		if ( i_caster->GetUInt32Value(ITEM_FIELD_STACK_COUNT) > 1 )
		{
			i_caster->ModUnsigned32Value( ITEM_FIELD_STACK_COUNT, -1 );
			i_caster->m_isDirty = true;
		}
		else
		{
			for ( uint32 x = 0; x < 5; x++ )
			{
				int32 charges = (int32)i_caster->GetUInt32Value( ITEM_FIELD_SPELL_CHARGES + x );
				if ( charges == -1 ) // if expendable item && item has no charges remaining -> delete item
				{
					//i bet this crashed happend due to some script. Items wihtout owners ?
					if( i_caster->GetOwner() && i_caster->GetOwner()->GetItemInterface() )
						i_caster->GetOwner()->GetItemInterface()->SafeFullRemoveItemByGuid( i_caster->GetGUID() );
					i_caster = NULL;
					break;
				}
				else if ( charges > 0 || charges < -1 ) // remove 1 charge
				{
					i_caster->ModSignedInt32Value( ITEM_FIELD_SPELL_CHARGES + x, ( charges < 0 ) ? +1 : -1 ); // if charges < 0 then -1 else +1
					i_caster->m_isDirty = true;
					break;
				}
			}
		}
	}
	// Ammo Removal
#ifndef CATACLYSM_SUPPORT
	if( GetProto()->AttributesExB == FLAGS3_REQ_RANGED_WEAPON || GetProto()->AttributesExC & FLAGS4_PLAYER_RANGED_SPELLS)
	{
		p_caster->GetItemInterface()->RemoveItemAmt_ProtectPointer(p_caster->GetUInt32Value(PLAYER_AMMO_ID), 1, &i_caster);
	}
#endif
	// Reagent Removal
	if( !( i_caster != NULL && (i_caster->GetProto()->Flags &  ITEM_FLAGS_ENCHANT_SCROLL))	//these are enchanting scrolls and reagent was already consumend when enchanter created them
//		&& !(p_caster->removeReagentCost && GetProto()->AttributesExD & 2) ) //zack : wtf is flag 2 put there for ?
		&& p_caster->removeReagentCost == false )
	{
		for(uint32 i=0; i<8 ;i++)
		{
			if( GetProto()->Reagent[i])
			{
				p_caster->GetItemInterface()->RemoveItemAmt_ProtectPointer(GetProto()->Reagent[i], GetProto()->ReagentCount[i], &i_caster);
			}
		}
	}
}

int32 Spell::CalculateEffect(uint32 i,Unit *target)
{
	int32 value = 0;

	float basePointsPerLevel    = GetProto()->EffectRealPointsPerLevel[i];
	int32 basePoints = GetProto()->EffectBasePoints[i] + 1;
	int32 randomPoints = GetProto()->EffectDieSides[i];

	//added by Zack : some talents inherit their basepoints from the previously casted spell: see mage - Master of Elements
	if(forced_basepoints[i])
		basePoints = forced_basepoints[i];

	// Random suffix value calculation 
	if(i_caster && (int32(i_caster->GetUInt32Value(ITEM_FIELD_RANDOM_PROPERTIES_ID)) < 0))
	{
        ItemRandomSuffixEntry * si = dbcItemRandomSuffix.LookupEntry(abs(int(i_caster->GetUInt32Value(ITEM_FIELD_RANDOM_PROPERTIES_ID))));
		EnchantEntry * ent;
		uint32 j,k;

		for(j = 0; j < 3; ++j)
		{
			if(si->enchantments[j] != 0)
			{
				ent = dbcEnchant.LookupEntry(si->enchantments[j]);
				for(k = 0; k < 3; ++k)
				{
					if(ent->spell[k] == GetProto()->Id)
					{
						if(si->prefixes[k] == 0)
							goto exit;

						value = RANDOM_SUFFIX_MAGIC_CALCULATION(si->prefixes[j], i_caster->GetItemRandomSuffixFactor());

						if(value == 0)
							goto exit;

						return value;
					}
				}
			}
		}
	}
exit:

	if( u_caster != NULL )
	{
		int32 diff = -(int32)GetProto()->baseLevel;
		if (GetProto()->maxLevel && u_caster->getLevel()>GetProto()->maxLevel)
			diff +=GetProto()->maxLevel;
		else
			diff +=u_caster->getLevel();
		basePoints += float2int32(diff * basePointsPerLevel );
	}

	if(randomPoints < -1 )
		value = basePoints - ( RandomUInt() % ( -randomPoints ) );
	else 
	{
		if(randomPoints <= 1)
			value = basePoints;
		else
			value = basePoints + RandomUInt() % randomPoints;
	}

	int32 comboDamage = (int32)GetProto()->EffectPointsPerComboPoint[i];
	if(comboDamage && p_caster != NULL )
	{
		m_requiresCP = true;
		value += ( comboDamage * p_caster->m_comboPoints );
			//this is ugly so i will explain the case maybe someone ha a better idea :
			// while casting a spell talent will trigger uppon the spell prepare faze
			// the effect of the talent is to add 1 combo point but when triggering spell finishes it will clear the extra combo point
		p_caster->m_spellcomboPoints = 0;
	}

	//scripted shit
	if( GetProto()->EffectHandler )
		GetProto()->EffectHandler( this, target, value, i );

	if( p_caster != NULL )
	{
		ApplyClassScriptOverridesToEffect( value, i, p_caster, target );

		// DK spells gain damage based on AP
		if( GetProto()->DK_AP_spell_bonus[i]!=0 && p_caster->GetItemInterface())
		{
			// http://deathknight.info/wiki/index.php?title=Mechanics -> all spells gain based on AP
			//Normalised Weapon Damage = Tool-tip Weapon Damage + (AP/14)*(Normalisation Constant) 
			//The Normalisation Constant for 2h weapons is 3.3
			//The Normalisation Constant for 1h weapons is 2.4
			Item *it = p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
			uint32 type = 0;
			uint32 bonus_value = 0;
			if( it && it->GetProto() )
				type = it->GetProto()->InventoryType;
			if( type == INVTYPE_WEAPON || type == INVTYPE_WEAPONMAINHAND )
				bonus_value += p_caster->GetAP() * 24 / 140;//		normalization = 2.4f;
			else if( type == INVTYPE_2HWEAPON )
				bonus_value += p_caster->GetAP() * 33 / 140;//		normalization = 3.3f;

			bonus_value = float2int32(((float)bonus_value) * ( GetProto()->DK_AP_spell_bonus[i] + p_caster->ModAbillityAPBonusCoef ) );

			// in case spell is over time then we divide the ammount
			if( ProcedOnSpell && ProcedOnSpell->quick_tickcount > GetProto()->quick_tickcount )
				value += bonus_value / ProcedOnSpell->quick_tickcount; //these are periodic trigger pells
			else
				value += bonus_value / GetProto()->quick_tickcount;
		}

		if( (GetProto()->c_is_flags & SPELL_FLAG_IS_REQ_ITEM_CASTER_MOD_CHK) && i_caster )
		{
			if( p_caster->has_mixology_talent && ( GetProto()->c_is_flags & SPELL_FLAG_IS_FLASK_OR_ELIXIR ) )
				value = value*3/2;	//this is not flat 1.5, It depends on item and effect too
			if( p_caster->has_alchemist_stone_effect && ( GetProto()->c_is_flags & SPELL_FLAG_IS_ALCHEMIST_STONE_TARGET ) )
				value = value*140/100;	//fixed 40% extra effect
		}
	}

	// TODO: INHERIT ITEM MODS FROM REAL ITEM OWNER - BURLEX BUT DO IT PROPERLY
	if( Need_SM_Apply( GetProto() ) )
	{
		if( target && target != u_caster )
		{
			//!! it is possible that this only affects first effect only ?
			SM_FIValue(target->SM_FEffectTargetBonus,&value,GetProto()->SpellGroupType);
			SM_PIValue(target->SM_PEffectTargetBonus,&value,GetProto()->SpellGroupType);
		}
		if( u_caster != NULL)
		{
			SM_FIValue(u_caster->SM_FMiscEffect,&value,GetProto()->SpellGroupType);
			SM_PIValue(u_caster->SM_PMiscEffect,&value,GetProto()->SpellGroupType);
			if( i == 0 )
			{
				SM_FIValue(u_caster->SM_FAddEffect1,&value,GetProto()->SpellGroupType);
				SM_PIValue(u_caster->SM_PAddEffect1,&value,GetProto()->SpellGroupType);
			}
			else if( i == 1 )
			{
				SM_FIValue(u_caster->SM_FAddEffect2,&value,GetProto()->SpellGroupType);
				SM_PIValue(u_caster->SM_PAddEffect2,&value,GetProto()->SpellGroupType);
			}
			else if( i == 2 )
			{
				SM_FIValue(u_caster->SM_FAddEffect3,&value,GetProto()->SpellGroupType);
				SM_PIValue(u_caster->SM_PAddEffect3,&value,GetProto()->SpellGroupType);
			}

			SM_FIValue(u_caster->SM_FEffectBonus,&value,GetProto()->SpellGroupType);
			SM_PIValue(u_caster->SM_PEffectBonus,&value,GetProto()->SpellGroupType);
		}
		else if( i_caster != NULL && target)
		{
			//we should inherit the modifiers from the conjured food caster
			Unit *item_creator = target->GetMapMgr()->GetUnit( i_caster->GetUInt64Value( ITEM_FIELD_CREATOR ) );
			if( item_creator != NULL )
			{
				SM_FIValue(item_creator->SM_FMiscEffect,&value,GetProto()->SpellGroupType);
				SM_PIValue(item_creator->SM_PMiscEffect,&value,GetProto()->SpellGroupType);

				SM_FIValue(item_creator->SM_FEffectBonus,&value,GetProto()->SpellGroupType);
				SM_PIValue(item_creator->SM_PEffectBonus,&value,GetProto()->SpellGroupType);
			}
		}
	}

	//this is some custom shit to make heroic instnaces a little bit harder to make then normal ones
	if( u_caster && u_caster->IsCreature() && u_caster->GetMapMgr() && target && target->IsPlayer() )
	{
		if( GetProto()->c_is_flags & SPELL_FLAG_IS_HEALING )
		{
			if( IS_HEROIC_INSTANCE_DIFFICULTIE( u_caster->GetMapMgr()->instance_difficulty ) )
				value = (int32)( value * sWorld.mob_HeroicHealSpellFactor );
			else 
				value = (int32)( value * sWorld.mob_NormalHealSpellFactor );
		}
		if( GetProto()->c_is_flags & SPELL_FLAG_IS_DAMAGING )
		{
			if( IS_HEROIC_INSTANCE_DIFFICULTIE( u_caster->GetMapMgr()->instance_difficulty ) )
				value = (int32)( value * sWorld.mob_HeroicDmgSpellFactor );
			else 
				value = (int32)( value * sWorld.mob_NormalDmgSpellFactor );

			//check to not kill the poor mothe fucker in 1 blow ?
			if( sWorld.mob_SpellKillerBlowReduction && value < sWorld.mob_SpellKillerBlowBelow )
			{
				int32 max_dmg = (int32)( target->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) / sWorld.mob_SpellKillerBlowReduction ) ;
				if( value > max_dmg )
					value = max_dmg;
			}
		}
	}

	return value;
}

void Spell::HandleTeleport(uint32 id, Unit* Target)
{
	if(Target->GetTypeId()!=TYPEID_PLAYER)
	{ 
		return;
	}

	Player* pTarget = SafePlayerCast( Target );

	float x,y,z;
	uint32 mapid;

	// predefined behavior
	if (GetProto()->Id == 8690 || GetProto()->Id == 556 || GetProto()->Id == 39937)// 556 - Astral Recall ; 39937 - Ruby Slippers
	{
		x = pTarget->GetBindPositionX();
		y = pTarget->GetBindPositionY();
		z = pTarget->GetBindPositionZ();
		mapid = pTarget->GetBindMapId();
	}
	else // normal behavior
	{
		TeleportCoords* TC = TeleportCoordStorage.LookupEntry(id);
		if(!TC)
		{ 
			return;
		}

		x=TC->x;
		y=TC->y;
		z=TC->z;
		mapid=TC->mapId;
	}
	pTarget->EventAttackStop();
	pTarget->SetSelection(0);

	// We use a teleport event on this one. Reason being because of UpdateCellActivity,
	// the game object set of the updater thread WILL Get messed up if we teleport from a gameobject
	// caster.
	if(!sEventMgr.HasEvent(pTarget, EVENT_PLAYER_TELEPORT))
		sEventMgr.AddEvent(pTarget, &Player::EventTeleport, mapid, x, y, z, EVENT_PLAYER_TELEPORT, 1, 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
}

void Spell::CreateItem(uint32 itemId)
{
    if( !itemId || !p_caster )
    { 
        return;
    }

	Item*			newItem;
	Item*			add;
	SlotResult		slotresult;
	ItemPrototype*	m_itemProto;

	m_itemProto = ItemPrototypeStorage.LookupEntry( itemId );
	if( m_itemProto == NULL )
	{ 
	    return;
	}

	if (p_caster->GetItemInterface()->CanReceiveItem(m_itemProto, 1))
	{
		SendCastResult(SPELL_FAILED_TOO_MANY_OF_ITEM);
		return;
	}

	add = p_caster->GetItemInterface()->FindItemLessMax(itemId, 1, false);
	if (!add)
	{
		slotresult = p_caster->GetItemInterface()->FindFreeInventorySlot(m_itemProto);
		if(!slotresult.Result)
		{
			 SendCastResult(SPELL_FAILED_TOO_MANY_OF_ITEM);
			 return;
		}

		newItem = objmgr.CreateItem(itemId, p_caster);
		AddItemResult result = p_caster->GetItemInterface()->SafeAddItem(newItem, slotresult.ContainerSlot, slotresult.Slot);
		if( result == ADD_ITEM_RESULT_ERROR )
		{
			newItem->DeleteMe();
			return;
		}

		newItem->SetUInt64Value(ITEM_FIELD_CREATOR,m_caster->GetGUID());
		newItem->SetUInt32Value(ITEM_FIELD_STACK_COUNT, damage);

		/*WorldPacket data(45);
		p_caster->GetSession()->BuildItemPushResult(&data, p_caster->GetGUID(), 1, 1, itemId ,0,0xFF,1,0xFFFFFFFF);
		p_caster->SendMessageToSet(&data, true);*/
		p_caster->GetSession()->SendItemPushResult(newItem,true,false,true,true,slotresult.ContainerSlot,slotresult.Slot,1);
		newItem->m_isDirty = true;

	}
	else
	{
		add->SetUInt32Value(ITEM_FIELD_STACK_COUNT,add->GetUInt32Value(ITEM_FIELD_STACK_COUNT) + damage);
		/*WorldPacket data(45);
		p_caster->GetSession()->BuildItemPushResult(&data, p_caster->GetGUID(), 1, 1, itemId ,0,0xFF,1,0xFFFFFFFF);
		p_caster->SendMessageToSet(&data, true);*/
		p_caster->GetSession()->SendItemPushResult(add,true,false,true,false,p_caster->GetItemInterface()->GetBagSlotByGuid(add->GetGUID()),0xFFFFFFFF,1);
		add->m_isDirty = true;
	}
}

/*void Spell::_DamageRangeUpdate()
{
	if(unitTarget)
	{
		if(unitTarget->isAlive())
		{
			m_caster->SpellNonMeleeDamageLog(unitTarget,GetProto()->Id, damageToHit);
		}
		else
		{	if( u_caster != NULL )
			if(u_caster->GetCurrentSpell() != this)
			{
					if(u_caster->GetCurrentSpell() != NULL)
					{
						u_caster->GetCurrentSpell()->SendChannelUpdate(0);
						u_caster->GetCurrentSpell()->cancel();
					}
			}
			SendChannelUpdate(0);
			cancel();
		}
		sEventMgr.RemoveEvents(this, EVENT_SPELL_DAMAGE_HIT);
		delete this;
	}
	else if(gameObjTarget)
	{
		sEventMgr.RemoveEvents(this, EVENT_SPELL_DAMAGE_HIT);
		delete this;
		//Go Support
	}
	else
	{
		sEventMgr.RemoveEvents(this, EVENT_SPELL_DAMAGE_HIT);
		delete this;
	}
}*/

void Spell::SendHealSpellOnPlayer(Object* caster, Object* target, uint32 dmg,bool critical)
{
	if(!caster || !target || !target->IsPlayer())
	{ 
		return;
	}
	sStackWolrdPacket( data, SMSG_SPELLHEALLOG, 40);
	// Bur: I know it says obsolete, but I just logged this tonight and got this packet.

	data << target->GetNewGUID();
	data << caster->GetNewGUID();
	if( GetProto()->spell_id_client )
		data << GetProto()->spell_id_client;
	else
		data << (pSpellId ? pSpellId : GetProto()->Id);
	data << uint32(dmg);	// amt healed
	if( target->IsUnit() )
		data << uint32( SafeUnitCast(target)->GetOverHeal( dmg ) );	// overheal
	else
		data << uint32( dmg );
	data << uint32( 0 );		//absorb ? wtf ?
	data << uint16(critical==true);	 //this is critical message or maybe some flags ?

#ifdef MINIMIZE_NETWORK_TRAFIC
	caster->SendMessageToDuel( &data );
#else
	caster->SendMessageToSet(&data, true);
#endif
}

void SendHealSpellOnPlayer(Object* caster, Object* target, uint32 dmg,bool critical,SpellEntry *sp)
{
	if(!caster || !target || !target->IsPlayer())
	{ 
		return;
	}
	sStackWolrdPacket( data, SMSG_SPELLHEALLOG, 40 );
	// Bur: I know it says obsolete, but I just logged this tonight and got this packet.

	data << target->GetNewGUID();
	data << caster->GetNewGUID();
	if( sp->spell_id_client )
		data << sp->spell_id_client;
	else
		data << sp->Id;
	data << uint32(dmg);	// amt healed
	if( target->IsUnit() )
		data << uint32( SafeUnitCast(target)->GetOverHeal( dmg ) );	// overheal
	else
		data << uint32( dmg );
	data << uint32( 0 );	//absorb ? but why ?
	data << uint16(critical==true);	 //this is critical message or maybe some flags ?

#ifdef MINIMIZE_NETWORK_TRAFIC
	caster->SendMessageToDuel( &data );
#else
	caster->SendMessageToSet(&data, true);
#endif
}

void Spell::Heal(int32 amount, bool ForceCrit,uint32 eff_index)
{
	int32 base_amount = amount; //store base_amount for later use

	if(!unitTarget || !unitTarget->isAlive() || unitTarget->GetUInt32Value( UNIT_FIELD_HEALTH ) == 0)
	{ 
		return;
	}

	if( p_caster != NULL )
		p_caster->last_heal_spell = GetProto();

    //self healing shouldn't flag himself
	if(p_caster && playerTarget && p_caster != playerTarget)
	{
		// Healing a flagged target will flag you.
		if(playerTarget->IsPvPFlagged())
			p_caster->SetPvPFlag();
		//cannot heal ones that are Dueling(and not self)
		if( playerTarget->DuelingWith )
			return;
	}

	uint32 a_proc = PROC_ON_HEAL_SPELL | PROC_ON_SPELL_HIT;
	uint32 v_proc = PROC_ON_SPELL_HIT_VICTIM;
	//Make it critical
	bool critical = false;
	int32 critchance = 0;
	int32 bonus = 0;
	if( u_caster != NULL && m_spellInfo->Spell_value_is_scripted == false && static_dmg[eff_index] == 0 )
	{
		if(u_caster->IsPlayer())
			if(m_spellInfo->NameHash == SPELL_HASH_FLASH_HEAL || m_spellInfo->NameHash == SPELL_HASH_BINDING_HEAL || m_spellInfo->NameHash == SPELL_HASH_GREATER_HEAL)
				u_caster->RemoveAura(34754, u_caster->GetGUID());

		//item spells do not get spell power bonus
		bonus = u_caster->GetSpellHealBonus( unitTarget, GetProto(), amount, 1);

		// Healing Way fix
		if(m_spellInfo->NameHash == SPELL_HASH_HEALING_WAVE && unitTarget->HasActiveAura(29203))
			amount += amount * 18 / 100;

		if(m_spellInfo->spell_can_crit)
		{
			critchance = float2int32(u_caster->spellcritperc + u_caster->SpellCritChanceSchool[GetProto()->School]);
			critical = Rand(critchance);
		}

		if( critical == true || ForceCrit == true )
		{
			int32 critical_bonus = 100;
			if( Need_SM_Apply(GetProto()) )
				SM_FIValue( u_caster->SM_PCriticalDamage, &critical_bonus, GetProto()->SpellGroupType );

			if( critical_bonus > 0 )
			{
				// the bonuses are halved by 50% (funky blizzard math :S)
				float b = ( ( float(critical_bonus) / 2.0f ) / 100.0f );
				bonus += float2int32( float(amount + bonus) * b );
			}
			bonus += u_caster->HealCritDonePctMod * amount / 100;

			v_proc |= PROC_ON_SPELL_CRIT_HIT_VICTIM;
			a_proc |= PROC_ON_SPELL_CRIT_HIT;
		}

		if( bonus < 0 )
			bonus = 0; //!! the mods i tell you !

		amount += bonus;	
	}

	amount = amount * chaincast_jump_pct_mod / 100;

	if(amount < 0)
		amount = 0;

	//send heal log
	if( unitTarget->IsPlayer() )
		SendHealSpellOnPlayer( m_caster, SafePlayerCast( unitTarget ), amount, critical );

	//maybe consider pets and totems here ?
	if( p_caster != NULL )
	{
		p_caster->m_bgScore.HealingDone += amount;
		if( p_caster->m_bg != NULL )
		{
			//you might wonder how this gets invalid. Well i agree with you. This should not get invalid ever. Sadly some players get stuck in teleporting state until they fuck up pointer ..
//			if( BattlegroundManager.IsValidBGPointer( p_caster->m_bg ) )
				p_caster->m_bg->UpdatePvPData();
//			else
//				p_caster->m_bg = NULL;
			if( unitTarget->IsPlayer() ) 
				SafePlayerCast( unitTarget )->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_TOTAL_HEALING_RECEIVED,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,amount,ACHIEVEMENT_EVENT_ACTION_ADD);
			p_caster->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_HEALING_DONE,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,amount,ACHIEVEMENT_EVENT_ACTION_ADD);
		}
		p_caster->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEAL_CASTED,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,amount,ACHIEVEMENT_EVENT_ACTION_SET_MAX);

		//also contains overheal value and gives a chance to detect missing health
		p_caster->HandleProc( a_proc, unitTarget, GetProto(), amount ,0 );
	}
	//no double proc please
	if( unitTarget != m_caster )
		unitTarget->HandleProc( v_proc, u_caster, GetProto(), amount);

	uint32 curHealth = unitTarget->GetUInt32Value(UNIT_FIELD_HEALTH);
	uint32 maxHealth = unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
	if((curHealth + amount) >= maxHealth)
	{
		amount = maxHealth - curHealth;
		unitTarget->SetUInt32Value(UNIT_FIELD_HEALTH, maxHealth);
	}
	else
		unitTarget->ModUnsigned32Value(UNIT_FIELD_HEALTH, amount);

	//only consider used up healing and not total overheal too
	if( p_caster != NULL )
		p_caster->m_heal_made_since_login += amount;
	if( unitTarget->IsPlayer() )
		SafePlayerCast( unitTarget )->m_heal_received_since_login += amount;

	unitTarget->RemoveAurasByHeal();

	// add threat for spells that cause threath
	if( u_caster != NULL && GetProto()->ThreatForSpellCoef != 0 && m_triggeredSpell == false )
	{
		std::vector<Unit*> target_threat;
		int count = 0;
		for(std::set<Object*>::iterator itr = u_caster->GetInRangeSetBegin(); itr != u_caster->GetInRangeSetEnd(); ++itr)
		{
			if((*itr)->GetTypeId() != TYPEID_UNIT || !SafeUnitCast(*itr)->CombatStatus.IsInCombat() || (SafeUnitCast(*itr)->GetAIInterface()->getThreatByPtr(u_caster) == 0 && SafeUnitCast(*itr)->GetAIInterface()->getThreatByPtr(unitTarget) == 0))
				continue;

			target_threat.push_back(SafeUnitCast(*itr));
			count++;
		}
		if (count == 0)
		{ 
			return;
		}

		amount = amount / count;

		for(std::vector<Unit*>::iterator itr = target_threat.begin(); itr != target_threat.end(); ++itr)
			SafeUnitCast(*itr)->GetAIInterface()->HealReaction(u_caster, unitTarget, m_spellInfo, amount);

		// remember that we healed (for combat status)
		if(unitTarget->IsInWorld() && u_caster->IsInWorld())
			u_caster->CombatStatus.WeHealed(unitTarget);
	}
}

void Spell::DetermineSkillUp(uint32 skillid,uint32 targetlevel)
{
	if(!p_caster)
	{ 
		return;
	}
	if(p_caster->GetSkillUpChance(skillid)<0.01)
	{
		return;//to preven getting higher skill than max
	}
	int32 diff=p_caster->_GetSkillLineCurrent(skillid,false)/5-targetlevel;
	if(diff<0)
		diff=-diff;
	float chance;
	if(diff<=5)
		chance=95.0;
	else if(diff<=10)
		chance=66;
	else if(diff <=15)
		chance=33;
	else 
	{ 
		return;
	}
	if(Rand(chance*sWorld.getRate(RATE_SKILLCHANCE)))
		p_caster->_AdvanceSkillLine(skillid, float2int32( 1.0f * sWorld.getRate(RATE_SKILLRATE)));
}

void Spell::DetermineSkillUp(uint32 skillid)
{
	//This code is wrong for creating items and disenchanting.
	if(!p_caster)
	{ 
		return;
	}
	float chance = 0.0f;
	skilllinespell* skill = GetProto()->spell_skill;
	if( skill && SafePlayerCast( m_caster )->_HasSkillLine( skill->skilline ) )
	{
		uint32 amt = SafePlayerCast( m_caster )->_GetSkillLineCurrent( skill->skilline, false );
		uint32 max = SafePlayerCast( m_caster )->_GetSkillLineMax( skill->skilline );
		if( amt >= max )
		{ 
			return;
		}
		if( amt >= skill->grey ) //grey
			chance = 0.0f;
		else if( ( amt >= ( ( ( skill->grey - skill->green) / 2 ) + skill->green ) ) ) //green
			chance = 33.0f;
		else if( amt >= skill->green ) //yellow
			chance = 66.0f;
		else //brown
			chance=100.0f;
		if(Rand(chance*sWorld.getRate(RATE_SKILLCHANCE)))
			p_caster->_AdvanceSkillLine(skillid, float2int32( 1.0f * sWorld.getRate(RATE_SKILLRATE)));
	}
}

void Spell::SafeAddTarget(TargetsList* tgt,uint64 guid)
{
	if(guid == 0)
	{ 
		return;
	}

	for(TargetsList::iterator i=tgt->begin();i!=tgt->end();i++)
		if((*i)==guid)
		{ 
			return;
		}

	tgt->push_back(guid);
}

void Spell::SafeAddMissedTarget(uint64 guid)
{
    for(SpellTargetsList::iterator i=ModeratedTargets.begin();i!=ModeratedTargets.end();i++)
        if((*i).TargetGuid==guid)
        {
            //sLog.outDebug("[SPELL] Something goes wrong in spell target system");
			// this isnt actually wrong, since we only have one missed target map,
			// whereas hit targets have multiple maps per effect.
            return;
        }

    ModeratedTargets.push_back(SpellTargetMod(guid,2));
}

void Spell::SafeAddModeratedTarget(uint64 guid, uint16 type)
{
	for(SpellTargetsList::iterator i=ModeratedTargets.begin();i!=ModeratedTargets.end();i++)
		if((*i).TargetGuid==guid)
        {
            //sLog.outDebug("[SPELL] Something goes wrong in spell target system");
			// this isnt actually wrong, since we only have one missed target map,
			// whereas hit targets have multiple maps per effect.
			return;
        }

	ModeratedTargets.push_back(SpellTargetMod(guid, (uint8)type));
}

bool Spell::Reflect(Unit *refunit)
{
	SpellEntry * refspell = NULL;

	//do not bounce reflected spell. we cannto reflect spells that we cast on ourself
	if( m_reflectedParent != NULL || refunit == NULL || m_caster == refunit )
	{ 
		return false;
	}

	// if the spell to reflect is a reflect spell, do nothing.
	for(int i=0; i<3; i++)
	{
		if( GetProto()->Effect[i] == SPELL_EFFECT_APPLY_AURA && (GetProto()->EffectApplyAuraName[i] == SPELL_AURA_REFLECT_SPELLS_SCHOOL || GetProto()->EffectApplyAuraName[i] == SPELL_AURA_REFLECT_SPELLS))
		{ 
			return false;
		}
	}
	refunit->m_reflectSpellSchool.BeginLoop();
	for(CommitPointerListNode<struct ReflectSpellSchool> *i = refunit->m_reflectSpellSchool.begin();i != refunit->m_reflectSpellSchool.end();i = i->Next())
	{
		ReflectSpellSchool *rss = i->data;
		if(rss->school == -1 || rss->school == (int32)GetProto()->School)
		{
			if(Rand((float)rss->chance))
			{
				//the god blessed special case : mage - Frost Warding = is an augmentation to frost warding
				if(rss->require_aura_hash && !refunit->HasAurasWithNameHash(rss->require_aura_hash))
                {
					continue;
                }
				if (rss->charges > 0)
				{
					rss->charges--;
					if (rss->charges <= 0)
					{
						uint32 ID = rss->spellId;
						refunit->m_reflectSpellSchool.SafeRemove( i, 1 );
						rss = NULL;	//make sure it is not used somewhere else
						refunit->RemoveAura(ID);	//aura remove will not find this iterator !
					}
				}
				refspell = GetProto();
				break;
			}
		}
	}
	refunit->m_reflectSpellSchool.EndLoopAndCommit();

	if(!refspell) 
	{ 
		return false;
	}

	//we cannot reflect spells back to items or GOs. But we can simply nulify the spellcast
	if( m_caster->IsUnit() == true )
	{
		Spell *spell = SpellPool.PooledNew();
		spell->Init(refunit, refspell, true, NULL);
		spell->SetReflected();
		SpellCastTargets targets;
		targets.m_unitTarget = m_caster->GetGUID();
		spell->prepare(&targets);
	}

	return true;
}

void ApplyDiminishingReturnTimer(uint32 * Duration, Unit * Target, SpellEntry * spell)
{
	ApplyDiminishingReturnTimer( Duration, Target, spell->DiminishStatus );
}

void ApplyDiminishingReturnTimer(uint32 * Duration, Unit * Target, uint32 grp)
{
   uint32 status = grp;
   uint32 Grp = status & 0xFFFF;   // other bytes are if apply to pvp
   uint32 PvE = (status >> 16) & 0xFFFF;

   // Make sure we have a group
   if( Grp == 0xFFFF )
   { 
      return;
   }

   // Check if we don't apply to pve
   if(!PvE && Target->GetTypeId() != TYPEID_PLAYER && !Target->IsPet())
   { 
      return;
   }

   // TODO: check for spells that should do this
   uint32 OldDur = *Duration;
   uint32 NewDur = OldDur;
   uint32 count;

   //this last max 10 sec in PVP and even then they get diminished
   if( OldDur > 10000 &&
	   ( status == DIMINISHING_GROUP_GOUGE_POLY_SAP 
	   || status == DIMINISHING_GROUP_STUN
	   || status == DIMINISHING_GROUP_ROOT
	   || status == DIMINISHING_GROUP_FEAR
	   || status == DIMINISHING_GROUP_SLEEP
	   || status == DIMINISHING_GROUP_CHARM
	   )
	   && ( Target->IsPlayer() || Target->IsPet() ) )
   {
		OldDur = 10000;
		NewDur = 10000;	//in case first sap
   }

   //we are applying an aura on target so we can increase this
   if( getMSTime() >= Target->m_diminishExpireStamp[Grp] )
   {
		Target->m_diminishCount[Grp] = 1;
	   //set new timer -> make sure we will be able to have 100(0),50(1),25(2),0(3+)
		Target->m_diminishExpireStamp[Grp] = getMSTime() + OldDur*4;	//make sure we remove diminishing return only after we have aura expired
		count = 0;
   }
   else
   {
	   count = Target->m_diminishCount[Grp];
	   Target->m_diminishCount[Grp]++;
   }

   if( count )
   {
	   if( count > 2 ) // Target immune to spell
		  NewDur = 0;
	   else 
	   {
		  uint32 tDur = OldDur >> count; //100%, 50%, 25% bitwise
		  if( status == DIMINISHING_GROUP_FIX_DIMINISHED )
		  {
			  if( tDur < 10000 )
				  tDur = 10000;
			  if( ( Target->IsPlayer() || Target->IsPet() ) && OldDur > tDur )
				  NewDur = tDur;
		  }
		  else
			  NewDur = tDur;
	   }
   }
   *Duration = NewDur;
}

uint32 GetDiminishingGroup(uint32 NameHash)
{
	int32 grp = -1;
	bool pve = false;

	switch(NameHash)
	{
	case SPELL_HASH_BASH:
	case SPELL_HASH_IMPACT:
	case SPELL_HASH_CHEAP_SHOT:
	case SPELL_HASH_SHADOWFURY:
	case SPELL_HASH_CHARGE_STUN:
//	case SPELL_HASH_INTERCEPT_STUN:
	case SPELL_HASH_CONCUSSION_BLOW:
	case SPELL_HASH_INTIMIDATION:
	case SPELL_HASH_WAR_STOMP:
	case SPELL_HASH_POUNCE:
	case SPELL_HASH_HAMMER_OF_JUSTICE:
	case SPELL_HASH_SHOCKWAVE:
	case SPELL_HASH_CHARGE:
	case SPELL_HASH_INTERCEPT:
	case SPELL_HASH_IMPROVED_REVENGE:
	case SPELL_HASH_GAG_ORDER:
		{
			grp = DIMINISHING_GROUP_STUN;
			pve = true;
		}break;

	case SPELL_HASH_STARFIRE_STUN:
 	case SPELL_HASH_STONECLAW_STUN:
	case SPELL_HASH_STUN:					// Generic ones
	case SPELL_HASH_BLACKOUT:
//	case SPELL_HASH_MACE_STUN_EFFECT:		// Mace Specialization
		{
			grp = DIMINISHING_GROUP_STUN_PROC;
			pve = true;
		}break;

	case SPELL_HASH_ENTANGLING_ROOTS:
	case SPELL_HASH_FROST_NOVA:
			grp = DIMINISHING_GROUP_ROOT;
		break;

	case SPELL_HASH_IMPROVED_WING_CLIP:	
	case SPELL_HASH_FROSTBITE:
	case SPELL_HASH_IMPROVED_HAMSTRING:
	case SPELL_HASH_ENTRAPMENT:
			grp = DIMINISHING_GROUP_ROOT_PROC;
		break;

	case SPELL_HASH_HIBERNATE:
 	case SPELL_HASH_WYVERN_STING:
 	case SPELL_HASH_SLEEP:
 	case SPELL_HASH_RECKLESS_CHARGE:		//Gobling Rocket Helmet
			grp = DIMINISHING_GROUP_SLEEP;
		break;

	case SPELL_HASH_CYCLONE:
	case SPELL_HASH_BLIND:
		{
			grp = DIMINISHING_GROUP_BLIND_CYCLONE;
			pve = true;
		}break;

	case SPELL_HASH_GOUGE:
	case SPELL_HASH_REPENTANCE:				// Repentance
	case SPELL_HASH_SAP:
	case SPELL_HASH_POLYMORPH:				// Polymorph
	case SPELL_HASH_POLYMORPH__CHICKEN:		// Chicken
//	case SPELL_HASH_POLYMORPH__PIG:			// Pig
//	case SPELL_HASH_POLYMORPH__TURTLE:		// Turtle
	case SPELL_HASH_POLYMORPH__SHEEP:		// Good ol' sheep
	case SPELL_HASH_MAIM:					// Maybe here?
			grp = DIMINISHING_GROUP_GOUGE_POLY_SAP;
		break;

	case SPELL_HASH_FEAR:
	case SPELL_HASH_PSYCHIC_SCREAM:
	case SPELL_HASH_SEDUCTION:
	case SPELL_HASH_HOWL_OF_TERROR:
	case SPELL_HASH_SCARE_BEAST:
			grp = DIMINISHING_GROUP_FEAR;
		break;

	case SPELL_HASH_ENSLAVE_DEMON:			// Enslave Demon
	case SPELL_HASH_MIND_CONTROL:
	case SPELL_HASH_TURN_EVIL:
			grp = DIMINISHING_GROUP_CHARM;		//Charm???
		break;

	case SPELL_HASH_KIDNEY_SHOT:
		{
			grp = DIMINISHING_GROUP_KIDNEY_SHOT;
			pve = true;
		}break;

	case SPELL_HASH_DEATH_COIL:
			grp = DIMINISHING_GROUP_HORROR;
		break;
	

	case SPELL_HASH_BANISH:					// Banish
			grp = DIMINISHING_GROUP_BANISH;
		break;

	// group where only 10s limit in pvp is applied, not DR
	case SPELL_HASH_FREEZING_TRAP_EFFECT:	// Freezing Trap Effect
	case SPELL_HASH_HAMSTRING:	// Hamstring
	case SPELL_HASH_CURSE_OF_TONGUES:
		{
			grp = DIMINISHING_GROUP_FIX_DIMINISHED;
		}break;

	case SPELL_HASH_RIPOSTE:			// Riposte
	case SPELL_HASH_DISARM:			// Disarm
		{
			grp = DIMINISHING_GROUP_DISARM;
		}break;
	case SPELL_HASH_SILENCE:
	case SPELL_HASH_GARROTE___SILENCE:
	case SPELL_HASH_SILENCED___IMPROVED_COUNTERSPELL:
	case SPELL_HASH_SILENCED___IMPROVED_KICK:
	case SPELL_HASH_SILENCED___GAG_ORDER:
		{
 			grp = DIMINISHING_GROUP_SILENCE;
		}break;
	case SPELL_HASH_SLOW:
	case SPELL_HASH_THUNDER_CLAP:
		{
 			grp = DIMINISHING_GROUP_SLOW;
		}break;
	}

	uint32 ret;
	if( pve )
		ret = grp | (1 << 16);
	else
		ret = grp;

	return ret;
}

void Spell::ApplyClassScriptOverridesToEffect(int32 &value, int32 i, Player *caster, Unit *target)
{
	if( caster == NULL )
		return;
	//!!!this atm is not list protected. In case one handler changes list it will crash!!
	SimplePointerListNode<SpellEffectOverrideScript> *itr;
	for( itr = caster->mSpellOverrideMap.begin(); itr != caster->mSpellOverrideMap.end(); itr = itr->Next() )
		itr->data->ApplyHandler( this, caster, target, value, i, itr->data );
}

uint32 Spell::GetDuration()
{
    if(bDurSet)
		return Dur;
    bDurSet=true;
	if( forced_duration )
	{
		this->Dur = forced_duration;
		if( (GetProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && u_caster)
		{
			SM_FIValue(u_caster->SM_FDur,(int32*)&this->Dur,GetProto()->SpellGroupType);
			SM_PIValue(u_caster->SM_PDur,(int32*)&this->Dur,GetProto()->SpellGroupType);
		}
		return this->Dur;
	}

    int32 c_dur = 0;
    if(GetProto()->DurationIndex)
    {
        SpellDuration *sd=dbcSpellDuration.LookupEntry(GetProto()->DurationIndex);
        if(sd)
        {
            //check for negative and 0 durations.
            //duration affected by level
            if((int32)sd->Duration1 < 0 && sd->Duration2 && u_caster)
            {
                this->Dur = uint32(((int32)sd->Duration1 + (sd->Duration2 * u_caster->getLevel())));
                if((int32)this->Dur > 0 && sd->Duration3 > 0 && (int32)this->Dur > (int32)sd->Duration3)
                {
                    this->Dur = sd->Duration3;
                }

                if((int32)this->Dur < 0)
					this->Dur = 0;
				c_dur = this->Dur;
            }
            if(sd->Duration1 >= 0 && !c_dur)
            {
                this->Dur = sd->Duration1;
            }
            //combo point lolerCopter? ;P
            if(p_caster)  
            {
                uint32 cp=p_caster->m_comboPoints;
                if(cp)
                {
                    uint32 bonus=(cp*(sd->Duration3-sd->Duration1))/5;
                    if(bonus)
                    {
                        this->Dur+=bonus;
                        m_requiresCP=true;
                    }
                }
            }

            if( (GetProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && u_caster)
            {
                SM_FIValue(u_caster->SM_FDur,(int32*)&this->Dur,GetProto()->SpellGroupType);
                SM_PIValue(u_caster->SM_PDur,(int32*)&this->Dur,GetProto()->SpellGroupType);
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
				int spell_flat_modifers=0;
				int spell_pct_modifers=0;
				SM_FIValue(u_caster->SM_FDur,&spell_flat_modifers,GetProto()->SpellGroupType);
				SM_FIValue(u_caster->SM_PDur,&spell_pct_modifers,GetProto()->SpellGroupType);
				if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
					printf("!!!!!spell duration mod flat %d , spell duration mod pct %d , spell duration %d, spell group %u\n",spell_flat_modifers,spell_pct_modifers,Dur,GetProto()->SpellGroupType);
#endif
            }
        }
        else
        {
            this->Dur = (uint32)-1;
        }
    }
    else
    {
         this->Dur = (uint32)-1;
    }

	if( p_caster && p_caster->has_mixology_talent && ( GetProto()->c_is_flags & SPELL_FLAG_IS_FLASK_OR_ELIXIR ) )
		this->Dur *= 2;

	//frikkin hackfix to make last tick happen
	this->Dur += GetProto()->quick_ExtendDuration;	//should let the last update to take place

    return this->Dur;
}

float Spell::GetRadius(uint32 i)
{
	if(i>=3)return 0; //you are joking right ?
    if(bRadSet[i])return Rad[i];
    bRadSet[i]=true;
    Rad[i]=::GetRadius(dbcSpellRadius.LookupEntry(GetProto()->EffectRadiusIndex[i]));
	if((GetProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && u_caster)
    {
        SM_FFValue(u_caster->SM_FRadius,&Rad[i],GetProto()->SpellGroupType);
        SM_PFValue(u_caster->SM_PRadius,&Rad[i],GetProto()->SpellGroupType);
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		float spell_flat_modifers=0;
		float spell_pct_modifers=1;
		SM_FFValue(u_caster->SM_FRadius,&spell_flat_modifers,GetProto()->SpellGroupType);
		SM_PFValue(u_caster->SM_PRadius,&spell_pct_modifers,GetProto()->SpellGroupType);
		if(spell_flat_modifers!=0 || spell_pct_modifers!=1)
			printf("!!!!!spell radius mod flat %f , spell radius mod pct %f , spell radius %f, spell group %u\n",spell_flat_modifers,spell_pct_modifers,Rad[i],GetProto()->SpellGroupType);
#endif
    }

    return Rad[i];
}

bool IsInrange(LocationVector & location, Object * o, float square_r)
{
    float r = o->GetDistanceSq(location);
    return ( r<=square_r);
}

bool IsInrange(float x1,float y1, float z1, Object * o,float square_r)
{
    float r = o->GetDistanceSq(x1, y1, z1);
    return ( r<=square_r);
}
 /*  
bool IsInrange(Object * o1,Object * o2,float square_r)
{
    return IsInrange(o1->GetPositionX(),o1->GetPositionY(),o1->GetPositionZ(),
        o2->GetPositionX(),o2->GetPositionY(),o2->GetPositionZ(),square_r);
}*/

bool TargetTypeCheck(Object *obj,uint32 ReqCreatureTypeMask)
{
	if( !ReqCreatureTypeMask )
		return true;

	if( obj->IsCreature() )
	{
		CreatureInfo* inf = SafeCreatureCast( obj )->GetCreatureInfo();
		if( inf == NULL || !( 1 << ( inf->Type - 1 ) & ReqCreatureTypeMask ) )
			return false;
	}
	else if( obj->IsPlayer() )
	{
		if( !(UNIT_TYPE_HUMANOID_BIT & ReqCreatureTypeMask) )
			return false;
	}
	//invalid type or wrong object
	else 
		return false;

	return true;
}

int GetAiTargetType(SpellEntry *sp)
{
	/*	this is not good as one spell effect can target self and other one an enemy,
		maybe we should make it for each spell effect or use as flags */	
	if( 
		HasTargetType(sp,EFF_TARGET_INVISIBLE_OR_HIDDEN_ENEMIES_AT_LOCATION_RADIUS) ||
		HasTargetType(sp,EFF_TARGET_ALL_TARGETABLE_AROUND_LOCATION_IN_RADIUS) ||
		HasTargetType(sp,EFF_TARGET_ALL_ENEMY_IN_AREA) ||
		HasTargetType(sp,EFF_TARGET_ALL_ENEMY_IN_AREA_INSTANT) ||
		HasTargetType(sp,EFF_TARGET_ALL_ENEMY_IN_AREA_CHANNELED) ||
		HasTargetType(sp,EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME)
		)
		return TTYPE_DESTINATION;
	if( 
		HasTargetType(sp,EFF_TARGET_LOCATION_TO_SUMMON) ||
		HasTargetType(sp,EFF_TARGET_IN_FRONT_OF_CASTER) ||
		HasTargetType(sp,EFF_TARGET_ALL_FRIENDLY_IN_AREA) ||
		HasTargetType(sp,EFF_TARGET_PET_SUMMON_LOCATION) ||
		HasTargetType(sp,EFF_TARGET_LOCATION_INFRONT_CASTER)
		)
		return TTYPE_SOURCE;
	if( 
		HasTargetType(sp,EFF_TARGET_SINGLE_ENEMY) ||
		HasTargetType(sp,EFF_TARGET_ALL_ENEMIES_AROUND_CASTER) ||
		HasTargetType(sp,EFF_TARGET_DUEL) ||
		HasTargetType(sp,EFF_TARGET_SCRIPTED_OR_SINGLE_TARGET) ||
		HasTargetType(sp,EFF_TARGET_CHAIN) ||
		HasTargetType(sp,EFF_TARGET_CURRENT_SELECTION) ||
		HasTargetType(sp,EFF_TARGET_TARGET_AT_ORIENTATION_TO_CASTER) ||
		HasTargetType(sp,EFF_TARGET_MULTIPLE_GUARDIAN_SUMMON_LOCATION) ||
		HasTargetType(sp,EFF_TARGET_SELECTED_ENEMY_CHANNELED)
		)
		return TTYPE_SINGLETARGET;
	if( 
		HasTargetType(sp,EFF_TARGET_ALL_PARTY_AROUND_CASTER) ||
		HasTargetType(sp,EFF_TARGET_SINGLE_FRIEND) ||
		HasTargetType(sp,EFF_TARGET_PET_MASTER) ||
		HasTargetType(sp,EFF_TARGET_ALL_ENEMY_AT_ENEMY_IN_AREA_CHANNELED) ||
		HasTargetType(sp,EFF_TARGET_ALL_PARTY_IN_AREA) ||
		HasTargetType(sp,EFF_TARGET_SINGLE_PARTY) ||
		HasTargetType(sp,EFF_TARGET_ALL_PARTY) ||
		HasTargetType(sp,EFF_TARGET_ALL_RAID) ||
		HasTargetType(sp,EFF_TARGET_PARTY_MEMBER) ||
		HasTargetType(sp,EFF_TARGET_AREAEFFECT_PARTY_AND_CLASS)
		)
		return TTYPE_OWNER;
	if( 
		HasTargetType(sp,EFF_TARGET_SELF) ||
		HasTargetType(sp,4) ||
		HasTargetType(sp,EFF_TARGET_PET) ||
		HasTargetType(sp,EFF_TARGET_MINION)
		)
		return TTYPE_CASTER;
	return TTYPE_NULL;
}

bool IsTargetingStealthed(SpellEntry *sp)
{
	if(
		HasTargetType(sp,EFF_TARGET_INVISIBLE_OR_HIDDEN_ENEMIES_AT_LOCATION_RADIUS) ||
		HasTargetType(sp,EFF_TARGET_ALL_ENEMIES_AROUND_CASTER) ||
		HasTargetType(sp,EFF_TARGET_ALL_ENEMY_IN_AREA_CHANNELED) ||
		HasTargetType(sp,EFF_TARGET_ALL_ENEMY_IN_AREA_INSTANT)
		)
		return 1;

	if(
		sp->NameHash == SPELL_HASH_MAGMA_TOTEM
		)
		return 1;

	return 0;
}

uint32 IsHealingSpell(SpellEntry *sp)
{
	if( IsHealingEffect( sp, 0 ) )
		return 1;
	if( IsHealingEffect( sp, 1 ) )
		return 2;
	if( IsHealingEffect( sp, 2 ) )
		return 3;
	//flash of light, holy light uses scripted effect which is not neceserally heal spell
	if( sp->NameHash == SPELL_HASH_HOLY_LIGHT || sp->NameHash == SPELL_HASH_FLASH_OF_LIGHT  )
		return 1;
	
    return 0;
}
bool CanAgroHash(uint32 spellhashname)
{
    if (spellhashname == SPELL_HASH_HUNTER_S_MARK) //hunter's mark
        return false;
    else
        return true;
}
/*
void Spell::SendCastSuccess(Object * target)
{
	Player * plr = p_caster;
	if(!plr && u_caster)
		plr = u_caster->m_redirectSpellPackets;
	if(!plr||!plr->IsPlayer())
	{ 
		return;
	}

/*	WorldPacket data(SMSG_CLEAR_EXTRA_AURA_INFO, 13);
	data << ((target != 0) ? target->GetNewGUID() : uint64(0));
	data << GetProto()->Id;

	plr->GetSession()->SendPacket(&data);*/
/*
}

void Spell::SendCastSuccess(const uint64& guid)
{
	Player * plr = p_caster;
	if(!plr && u_caster)
		plr = u_caster->m_redirectSpellPackets;
	if(!plr || !plr->IsPlayer())
	{ 
		return;
	}

	// fuck bytebuffers
	unsigned char buffer[13];
	uint32 c = FastGUIDPack(guid, buffer, 0);
#ifdef USING_BIG_ENDIAN
	*(uint32*)&buffer[c] = swap32(GetProto()->Id);         c += 4;
#else
	*(uint32*)&buffer[c] = GetProto()->Id;                 c += 4;
#endif

//	plr->GetSession()->OutPacket(SMSG_CLEAR_EXTRA_AURA_INFO, c, buffer);
}*/
/*
bool IsBeneficSpell(SpellEntry *sp)
{
	uint32 cur;
	for(uint32 i=0;i<3;i++)
		for(uint32 j=0;j<2;j++)
		{
			if(j==0)
				cur = sp->EffectImplicitTargetA[i];
			else // if(j==1)
				cur = sp->EffectImplicitTargetB[i];
			switch(cur)
			{
				case EFF_TARGET_SELF:
				case EFF_TARGET_PET:
				case EFF_TARGET_ALL_PARTY_AROUND_CASTER:
				case EFF_TARGET_SINGLE_FRIEND:
				case 45:// Chain,!!only for healing!! for chain lightning =6
				case 57:// Targeted Party Member
				case 27: // target is owner of pet
				case EFF_TARGET_MINION:// Minion Target
				case 33://Party members of totem, inside given range
				case EFF_TARGET_SINGLE_PARTY:// Single Target Party Member
				case EFF_TARGET_ALL_PARTY: // all Members of the targets party
				case EFF_TARGET_SELF_FISHING://Fishing
				case 46://Unknown Summon Atal'ai Skeleton
				case 47:// Portal
				case 52:	// Lightwells, etc
				case 40://Activate Object target(probably based on focus)
				case EFF_TARGET_TOTEM_EARTH:
				case EFF_TARGET_TOTEM_WATER:
				case EFF_TARGET_TOTEM_AIR:
				case EFF_TARGET_TOTEM_FIRE:// Totem
				case 61: // targets with the same group/raid and the same class
				case 32:
				case 73:
					return true;
			}//end switch
		}//end for
	return false;
}

AI_SpellTargetType RecommandAISpellTargetType(SpellEntry *sp)
{
	uint32 cur;
	for(uint32 i=0;i<3;i++)
		for(uint32 j=0;j<2;j++)
		{
			if(j==0)
				cur = sp->EffectImplicitTargetA[i];
			else // if(j==1)
				cur = sp->EffectImplicitTargetB[i];
			switch(cur)
			{
				case EFF_TARGET_NONE:
				case EFF_TARGET_GAMEOBJECT:
				case EFF_TARGET_GAMEOBJECT_ITEM:// Gameobject/Item Target
				case EFF_TARGET_SELF_FISHING://Fishing
				case 47:// Portal
				case 52:	// Lightwells, etc
				case 40://Activate Object target(probably based on focus)
					return TTYPE_NULL;

				case EFF_TARGET_SELF:
				case 38://Dummy Target
				case 32:
				case 73:
					return TTYPE_CASTER;

				case EFF_TARGET_ALL_ENEMY_IN_AREA: // All Enemies in Area of Effect (TEST)
				case EFF_TARGET_ALL_ENEMY_IN_AREA_INSTANT: // All Enemies in Area of Effect instant (e.g. Flamestrike)
				case EFF_TARGET_ALL_ENEMY_IN_AREA_CHANNELED:// All Enemies in Area of Effect(Blizzard/Rain of Fire/volley) channeled
					return TTYPE_DESTINATION;

				case 4: // dono related to "Wandering Plague", "Spirit Steal", "Contagion of Rot", "Retching Plague" and "Copy of Wandering Plague"
				case EFF_TARGET_PET:
				case EFF_TARGET_SINGLE_ENEMY:// Single Target Enemy
				case 77:					// grep: i think this fits
				case 8: // related to Chess Move (DND), Firecrackers, Spotlight, aedm, Spice Mortar
				case EFF_TARGET_IN_FRONT_OF_CASTER:
				case 31:// related to scripted effects
				case 53:// Target Area by Players CurrentSelection()
				case 54:// Targets in Front of the Caster
				case EFF_TARGET_ALL_PARTY_AROUND_CASTER:
				case EFF_TARGET_SINGLE_FRIEND:
				case 45:// Chain,!!only for healing!! for chain lightning =6
				case 57:// Targeted Party Member
				case EFF_TARGET_DUEL:
				case 27: // target is owner of pet
				case EFF_TARGET_MINION:// Minion Target
				case 33://Party members of totem, inside given range
				case EFF_TARGET_SINGLE_PARTY:// Single Target Party Member
				case EFF_TARGET_ALL_PARTY: // all Members of the targets party
				case EFF_TARGET_TOTEM_EARTH:
				case EFF_TARGET_TOTEM_WATER:
				case EFF_TARGET_TOTEM_AIR:
				case EFF_TARGET_TOTEM_FIRE:// Totem
				case 61: // targets with the same group/raid and the same class
					return TTYPE_SINGLETARGET;

					// spells like 17278:Cannon Fire and 21117:Summon Son of Flame A
				case 17: // A single target at a xyz location or the target is a possition xyz
				case 18:// Land under caster.Maybe not correct
				case 46://Unknown Summon Atal'ai Skeleton
				case EFF_TARGET_ALL_ENEMIES_AROUND_CASTER:
					return TTYPE_SOURCE;

			}//end switch
		}//end for
	return TTYPE_NULL;// this means a new spell :P
}
*/
