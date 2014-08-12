#include "StdAfx.h"

SPELL_EFFECT_OVERRIDE_RETURNS HandleDefaultEffectOverride(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	//test if we should trigger at all
	if( so->required_namehash[0] )
	{
		if( sp->GetProto()->NameHash != so->required_namehash[0] 
			&& sp->GetProto()->NameHash != so->required_namehash[1]
			&& sp->GetProto()->NameHash != so->required_namehash[2]
			)
			return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	}
	if( so->required_spell_id && sp->GetProto()->Id != so->required_spell_id )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( so->required_effect_type[i] != SPELL_EFFECT_NULL && sp->GetProto()->Effect[ i ] != so->required_effect_type[i] )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( so->required_aura_type[i] != SPELL_AURA_NONE && sp->GetProto()->Effect[ i ] != so->required_aura_type[i] )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;

	//do our stuff
	value += so->mod_amount[ i ];
	if( so->mod_amount_pct[ i ] != 0 )
		value = value * so->mod_amount_pct[ i ] / 100;

	//this is a simple effect mod so no need to break execution
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SpellEffectOverrideScript::SpellEffectOverrideScript() 
{
	for(int i=0;i<3;i++)
	{
		mod_amount[i] = 0;		//for backward compatibility
		mod_amount_pct[i] = 0;	//for backward compatibility
		required_effect_type[i] = SPELL_EFFECT_NULL;
		required_aura_type[i] = SPELL_AURA_NONE;
		required_namehash[i] = 0;
	}
	ApplyHandler = &HandleDefaultEffectOverride;	// we can normally handle this
	RemoveHandler = NULL;
	required_spell_id = 0;
	ori_spell_id = 0;
};

SPELL_EFFECT_OVERRIDE_RETURNS HandleGlyphOfLesserHealingWave(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( sp->GetProto()->NameHash != SPELL_HASH_LESSER_HEALING_WAVE )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( target == NULL || target->HasAurasWithNameHash( SPELL_HASH_EARTH_SHIELD ) == 0 )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	value = value * so->mod_amount_pct[ i ] / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleGlyphOfRegrowth(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( sp->GetProto()->NameHash != SPELL_HASH_REGROWTH )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( target == NULL || target->HasAurasWithNameHash( SPELL_HASH_EARTH_SHIELD ) == 0 )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	value = value * so->mod_amount_pct[ i ] / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleMoltenFury(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( target == NULL || target->GetHealthPct() > 35 )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( IsDamagingSpell(sp->GetProto(),i) == false )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	value = value * so->mod_amount_pct[ i ] / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleStarfireBonus(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( sp->GetProto()->NameHash != SPELL_HASH_STARFIRE )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( target == NULL || ( target->HasAurasWithNameHash( SPELL_HASH_INSECT_SWARM ) == 0 && target->HasAurasWithNameHash( SPELL_HASH_MOONFIRE ) == 0) )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	value = value * so->mod_amount_pct[ i ] / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleDeatsEmbrace(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( sp->GetProto()->NameHash == SPELL_HASH_DRAIN_LIFE && caster && caster->GetHealthPct() < 20)
		value = value * so->mod_amount_pct[ 0 ] / 100;
	if( target && target->GetHealthPct() < 35 && sp->GetProto()->School == SCHOOL_SHADOW )
		value = value * so->mod_amount_pct[ 1 ] / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleTestOfFaith(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( target == NULL || target->GetHealthPct() > 50 )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( IsHealingEffect(sp->GetProto(),i) == false )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	value = value * so->mod_amount_pct[ i ] / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleMercilessCombat(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if(		( sp->GetProto()->NameHash == SPELL_HASH_ICY_TOUCH && i == 0 )
		||	( sp->GetProto()->NameHash != SPELL_HASH_HOWLING_BLAST && i == 1 )
		||	( sp->GetProto()->NameHash != SPELL_HASH_OBLITERATE && i == 1 )
		||	( sp->GetProto()->NameHash != SPELL_HASH_FROST_STRIKE && i == 1 )
		)
	{
		if( target && target->GetHealthPct() < 35 )
			value = value * so->mod_amount_pct[ 0 ] / 100;
	}
		
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleRageOfRivedare(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( target == NULL || target->HasAurasWithNameHash( SPELL_HASH_BLOOD_PLAGUE ) == 0 )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( IsDamagingSpell(sp->GetProto(),i) == false )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	value = value * so->mod_amount_pct[ i ] / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleTundraStalker(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( target == NULL || target->HasAurasWithNameHash( SPELL_HASH_FROST_FEVER ) == 0 )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( IsDamagingSpell(sp->GetProto(),i) == false )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	value = value * so->mod_amount_pct[ i ] / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleMarkedForDeath(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( target == NULL || target->HasAurasWithNameHash( SPELL_HASH_HUNTER_S_MARK ) == 0 )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	value = value * so->mod_amount_pct[ i ] / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleNourishHealBoost(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( target == NULL )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( sp->GetProto()->NameHash != SPELL_HASH_NOURISH )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	uint32 pct_sum = 100;
	for( uint32 i = 0; i < MAX_POSITIVE_AURAS1( target ); i++ )
		if( target->m_auras[i] && ( target->m_auras[i]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_HEAL_OVER_TIME ) )
			pct_sum += so->mod_amount_pct[ i ] - 100;
	value = value * pct_sum / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleSoulSiphon(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( target == NULL )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( sp->GetProto()->NameHash != SPELL_HASH_DRAIN_LIFE && sp->GetProto()->NameHash != SPELL_HASH_DRAIN_SOUL )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	uint32 coun_auras = 0;
	for( uint32 i = NEG_AURAS_START; i < MAX_NEGATIVE_AURAS1( target ); i++ )
		if( target->m_auras[i] 
			&& target->m_auras[i]->GetCasterGUID() == caster->GetGUID()
			&& target->m_auras[i]->GetSpellProto()->spell_skilline[0] == SKILL_AFFLICTION )
			{
				coun_auras++;
				if( coun_auras == 3 )
					break;
			}
	if(  sp->GetProto()->NameHash == SPELL_HASH_DRAIN_LIFE )
		sp->forced_miscvalues[i] = so->mod_amount_pct[0] * coun_auras;	//pass the overall pct bonus
	else
		value += value * so->mod_amount_pct[0] * coun_auras / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleTormentTheWeak(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	if( target == NULL )
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( sp->GetProto()->NameHash != SPELL_HASH_FROSTBOLT 
		&& sp->GetProto()->NameHash != SPELL_HASH_FROSTFIRE_BOLT
		&& sp->GetProto()->NameHash != SPELL_HASH_PYROBLAST
		&& sp->GetProto()->NameHash != SPELL_HASH_ARCANE_MISSILES
		&& sp->GetProto()->NameHash != SPELL_HASH_ARCANE_BLAST
		&& sp->GetProto()->NameHash != SPELL_HASH_ARCANE_BARRAGE
		)
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	if( sp->GetProto()->Effect[i] != SPELL_EFFECT_SCHOOL_DAMAGE 
		&& sp->GetProto()->EffectApplyAuraName[i] != SPELL_AURA_PERIODIC_DAMAGE 
		)
		return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
	uint32 can_apply = 0;
	for( uint32 i = NEG_AURAS_START; i < MAX_NEGATIVE_AURAS1( target ); i++ )
		if( target->m_auras[i] &&
			( target->m_auras[i]->GetSpellProto()->EffectMechanic[0] == MECHANIC_SLOWED
			|| target->m_auras[i]->GetSpellProto()->EffectMechanic[0] == MECHANIC_SLOWED
			|| target->m_auras[i]->GetSpellProto()->EffectMechanic[0] == MECHANIC_SLOWED
			|| target->m_auras[i]->GetSpellProto()->EffectMechanic[0] == MECHANIC_ENSNARED
			|| target->m_auras[i]->GetSpellProto()->EffectMechanic[0] == MECHANIC_ENSNARED
			|| target->m_auras[i]->GetSpellProto()->EffectMechanic[0] == MECHANIC_ENSNARED ))
			{
				can_apply = 1;
				break;
			}
	if( can_apply == 1 )
	{
		SpellEntry *spellInfo = sp->GetProto();
		int32 spell_dmg_bonus = caster->GetSpellDmgBonus( target, spellInfo, value, spellInfo->quick_tickcount ) / (int32)spellInfo->quick_tickcount;
		value += ( value + spell_dmg_bonus ) * so->mod_amount_pct[0]/ 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

