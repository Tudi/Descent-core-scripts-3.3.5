#include "StdAfx.h"

#define REGISTER_HANDLER( spell, i ) sp = dbcSpell.LookupEntryForced( spell ); \
	ASSERT( sp->TargettingOverride[i] == 0 ); \
	sp->TargettingOverride[i] = &TO_ ## spell ## _ ## i;
#define REGISTER_SAMEHANDLER(spell, i , copy_from) sp = dbcSpell.LookupEntryForced( spell ); \
	ASSERT( sp->TargettingOverride[i] == 0 ); \
	sp->TargettingOverride[i] = &TO_ ## copy_from ## _ ## i;
#define REGISTER_SAME_INDEX_HANDLER(spell, src_i , dest_i) sp = dbcSpell.LookupEntryForced( spell ); \
	ASSERT( sp->TargettingOverride[dest_i] == 0 ); \
	sp->TargettingOverride[dest_i] = &TO_ ## spell ## _ ## src_i;

void TO_50882_0(Spell *sp,uint8 i)
{
	//Icy Talons only self proc if we do not have improved icy talons on ourself
	if( sp->u_caster && sp->u_caster->HasPassiveAurasWithNameHash( SPELL_HASH_IMPROVED_ICY_TALONS ) == 0 )
	{
		TargetsList *tmpMap=&sp->m_targetUnits[i];
		sp->SafeAddTarget( tmpMap  ,sp->u_caster->GetGUID() );
	}
}

void TO_48743_1(Spell *sp,uint8 i)
{
	TargetsList *tmpMap=&sp->m_targetUnits[i];
	if( sp->p_caster && sp->p_caster->GetSummon() )
		sp->SafeAddTarget(tmpMap,sp->p_caster->GetSummon()->GetGUID());
/*
	std::set<Object*>::iterator itr,itr2;
	sp->m_caster->AquireInrangeLock(); //make sure to release lock before exit function !
	for( itr2 = sp->m_caster->GetInRangeSetBegin(); itr2 != sp->m_caster->GetInRangeSetEnd();)
	{
		itr = itr2;
		itr2++;
		if( !(*itr)->IsUnit() 
			|| !SafeUnitCast((*itr))->isAlive()
			|| ( (*itr)->GetUInt32Value(UNIT_FIELD_SUMMONEDBY) != sp->m_caster->GetUInt32Value(OBJECT_FIELD_GUID)
				 && (*itr)->GetUInt32Value(UNIT_FIELD_CREATEDBY) != sp->m_caster->GetUInt32Value(OBJECT_FIELD_GUID) )
			)
			continue;
		//our creations are always friendly
		sp->SafeAddTarget(tmpMap,(*itr)->GetGUID());
		break;
	}
	sp->m_caster->ReleaseInrangeLock();
	*/
}

void TO_64382_0(Spell *sp,uint8 i)
{
	Unit * pTarget = sp->m_caster->GetMapMgr()->GetUnit(sp->m_targets.m_unitTarget);
	if( pTarget && pTarget->isAlive() )
	{
		TargetsList *tmpMap=&sp->m_targetUnits[i];
		sp->SafeAddTarget(tmpMap, pTarget->GetGUID());	
	}
}

void TO_51690_1(Spell *sp,uint8 i)
{
	//just gather targets the normal way
	sp->SpellTargetLandUnderCaster( i, 0 );
	//now in case we did not gather enough, just repeat adding one of them
	int32 target_repeats = sp->GetProto()->MaxTargets - sp->m_targetUnits[i].size();
	uint64 first_target;
	if( sp->m_targetUnits[i].size() )
		first_target = sp->m_targetUnits[i][0];
	else
		first_target = sp->m_targets.m_unitTarget;
	for(int32 j=0;j<target_repeats;j++)
		sp->m_targetUnits[i].push_back( first_target );
}

void TO_1535_0(Spell *sp,uint8 i)
{
	if( sp->p_caster && sp->p_caster->m_TotemSlots[EFF_TARGET_TOTEM_FIRE - EFF_TARGET_TOTEM_EARTH] )
		sp->m_targetUnits[i].push_back( sp->p_caster->m_TotemSlots[EFF_TARGET_TOTEM_FIRE - EFF_TARGET_TOTEM_EARTH]->GetGUID() );
}

void TO_47541_1(Spell *sp,uint8 i)
{
	Unit * pTarget = sp->m_caster->GetMapMgr()->GetUnit( sp->m_targets.m_unitTarget );
	if( pTarget && pTarget->isAlive() && isAttackable( sp->m_caster, pTarget ) == false && ( pTarget->getRace() == UNDEAD || pTarget->HasPosAurasWithNameHash( SPELL_HASH_LICHBORNE ) ) )
		sp->m_targetUnits[i].push_back( sp->m_targets.m_unitTarget );
}

void TO_49016_1(Spell *sp,uint8 i)
{
	if( sp->u_caster )
	{
		TargetsList *tmpMap=&sp->m_targetUnits[i];
		sp->SafeAddTarget( tmpMap  ,sp->u_caster->GetGUID() );
	}
}

void TO_46579_1(Spell *sp,uint8 i)
{
	if( sp->u_caster )
	{
		TargetsList *tmpMap=&sp->m_targetUnits[i];
		//this is melee weapon enchant. When it procs we are targetting the vistim
		Unit *sel = sp->u_caster->GetMapMgr()->GetUnit( sp->u_caster->GetTargetGUID() );
		if( sel && sel->getLevel() < 73 )
			sp->SafeAddTarget( tmpMap, sel->GetGUID() );
	}
}

void RegisterTargetingOverride()
{
	SpellEntry *sp;
	//Deathfrost
	REGISTER_HANDLER( 46579, 1 );	
	//hysteria - self target to dmg - this is actually protection in case some smartass ads atttack check
	REGISTER_HANDLER( 49016, 1 );	
	//death coil only heals undead
	REGISTER_HANDLER( 47541, 1 );	
	REGISTER_SAMEHANDLER( 49892, 1, 47541 );
	REGISTER_SAMEHANDLER( 49893, 1, 47541 );
	REGISTER_SAMEHANDLER( 49894, 1, 47541 );
	REGISTER_SAMEHANDLER( 49895, 1, 47541 );
	//fire nova triggers at totem location and not caster 
	REGISTER_HANDLER( 1535, 0 );	
	REGISTER_SAMEHANDLER( 8498, 0, 1535 );
	REGISTER_SAMEHANDLER( 8499, 0, 1535 );
	REGISTER_SAMEHANDLER( 11314, 0, 1535 );
	REGISTER_SAMEHANDLER( 11315, 0, 1535 );
	REGISTER_SAMEHANDLER( 25546, 0, 1535 );
	REGISTER_SAMEHANDLER( 25547, 0, 1535 );
	REGISTER_SAMEHANDLER( 61649, 0, 1535 );
	REGISTER_SAMEHANDLER( 61657, 0, 1535 );
	//killing spree
	REGISTER_HANDLER( 51690, 1 );	//we need exactly N targets :P 
	//Shattering Throw
	REGISTER_HANDLER( 64382, 0 );	//targets immune targets also
	REGISTER_SAME_INDEX_HANDLER( 64382, 0, 1);
	//Death Pact
	REGISTER_HANDLER( 48743, 1 );	//kill minions
	//Icy Talons only self proc if we do not have improved icy talons on ourself
	REGISTER_HANDLER( 50882, 0 );
	REGISTER_SAMEHANDLER( 58575, 0, 50882 );
	REGISTER_SAMEHANDLER( 58576, 0, 50882 );
	REGISTER_SAMEHANDLER( 58577, 0, 50882 );
	REGISTER_SAMEHANDLER( 58578, 0, 50882 );
}
