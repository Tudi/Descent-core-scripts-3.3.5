#include "StdAfx.h"

#define REGISTER_HANDLER( spell ) sp = dbcSpell.LookupEntryForced( spell ); \
	ASSERT( sp->EffectHandler == 0 ); \
	sp->EffectHandler = &EH_##spell;
#define REGISTER_SAMEHANDLER(spell,copy_from) sp = dbcSpell.LookupEntryForced( spell ); \
	ASSERT( sp->EffectHandler == 0 ); \
	sp->EffectHandler = &EH_##copy_from;

///////////////////////////////////////////////////////////////////////////////////////////
// Static Spell Functions used in Spell.cpp to calculate spell effect value
///////////////////////////////////////////////////////////////////////////////////////////

SPELL_EFFECT_OVERRIDE_RETURNS HandleSteadyShot(Spell *sp,Unit *target, int32 &value, int32 i)
{
	//A steady shot that causes ${$RAP*0.3+$m1} damage.
	//	Actual Equation (http://www.wowwiki.com/Steady_Shot)
	//		* The tooltip is proven to be wrong and the following is the best player worked out formula so far with data taken from [1]
	//		* Formula: DamagePercentageBonus*RangedWeaponSpecialization*(150 + WeaponDamage/WeaponSpeed*2.8 + 0.2*RAP + [Dazed: 175])
	if(i==0 && sp->u_caster)
	{
		if( sp->p_caster != NULL )
		{
			Item *it;
			if(sp->p_caster->GetItemInterface())
			{
				it = sp->p_caster->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_RANGED);
				if(it)
				{
					float weapondmg = RandomFloat(1)*(it->GetProto()->Damage[0].Max - it->GetProto()->Damage[0].Min) + it->GetProto()->Damage[0].Min;
					value += float2int32( sp->GetProto()->EffectBasePoints[0] + weapondmg/float(it->GetProto()->Delay/1000.0f)*2.8f);
				}
			}
		}
		if(target && target->IsDazed() )
			value += sp->GetProto()->EffectBasePoints[1];
		value += (uint32)(sp->u_caster->GetRAP() * 0.1f);
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleDeadlyPoison(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( (sp->GetProto()->c_is_flags & SPELL_FLAG_IS_POISON) && sp->GetProto()->EffectApplyAuraName[ i ]==SPELL_AURA_PERIODIC_DAMAGE && sp->u_caster )
	{
		//Each strike has a $2823h% chance of poisoning the enemy for ${$2818m1*4+0.12*$AP} Nature damage over $2818d.  Stacks up to 5 times on a single target.
		value = value * 4 + sp->u_caster->GetAP() * 12 / 100;
		value = value / sp->GetProto()->quick_tickcount;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleInstantPoison(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( (sp->GetProto()->c_is_flags & SPELL_FLAG_IS_POISON) && i==0 && sp->GetProto()->Effect[ i ]==SPELL_EFFECT_SCHOOL_DAMAGE && sp->u_caster )
	{
		//Each strike has a $57967h% chance of poisoning the enemy which instantly inflicts ${$57964m1+0.10*$AP} Nature damage.
		value = value + sp->u_caster->GetAP() * 10 / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleWoundPoison(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( (sp->GetProto()->c_is_flags & SPELL_FLAG_IS_POISON) && i==1 && sp->GetProto()->Effect[ i ]==SPELL_EFFECT_SCHOOL_DAMAGE && sp->u_caster )
	{
		//Each strike has a $57967h% chance of poisoning the enemy which instantly inflicts ${$57964m1+0.10*$AP} Nature damage.
		value = value + sp->u_caster->GetAP() * 4 / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleArcaneShot(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i==0 && sp->u_caster )//An instant shot that causes [RAP * 0.15 + 492] Arcane damage.
	{
		value = (int32)( sp->u_caster->GetRAP() * 0.15f ) + value;
//		if( u_caster->HasAurasOfNameHashWithCaster(SPELL_HASH_RAPID_KILLING, u_caster) ) //Arcane shot deals Y% extra damage with rapid killing buff
//			value += (uint32)(value * GetProto()->RankNumber / 10);
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleSerpentSting(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i==0 && sp->u_caster )//Stings the target, causing ${$RAP*0.2+$m1*5} Nature damage over $d.  Only one Sting per Hunter can be active on any one target.
		value = (int32)((( sp->u_caster->GetRAP() * 0.20f ) + value * 5) / sp->GetProto()->quick_tickcount );
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleKillShot(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i==0 && sp->u_caster )//An instant shot that causes [RAP * 0.15 + 492] Arcane damage.
		value = (int32)( sp->u_caster->GetRAP() * 0.40f ) + value;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleEviscerate(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->p_caster != NULL ) //Eviscerate
	{
		//1 point  : ${$m1+(($b1*1)+$AP*0.03)*$<mult>}-${$M1+(($b1*1)+$AP*0.07)*$<mult>} damage
		uint32 base = (uint32)( (5 * sp->p_caster->m_comboPoints + sp->p_caster->GetAP() *  0.03f) * sp->p_caster->m_comboPoints  );
		if( base )
		{
			value += base;
			uint32 random = RandomUInt() % base;
			value += random;
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleDivineSpiritPrayerOfSpirit(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i>0 && sp->p_caster )
	{
		Aura *a;
		a = sp->p_caster->FindAura( 33174 );
		if( a && a->m_modcount && a->mod )
			value = (sp->GetProto()->EffectBasePoints[0] + 1) * a->mod->m_amount / 100;
		else
		{
			a = sp->p_caster->FindAura( 33182 );
			if( a && a->m_modcount && a->mod )
				value = (sp->GetProto()->EffectBasePoints[0] + 1) * a->mod->m_amount / 100;
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleSealOfLight(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->u_caster )
	{
		//each melee attack a chance to heal the Paladin for ${0.15*$AP+0.15*$SPH}.  Only one Seal can be active on the Paladin at any one time.
		value = ( sp->u_caster->GetAP() + sp->u_caster->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SCHOOL_HOLY) ) * 15 / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleFlashOfLight(Spell *sp,Unit *target, int32 &value, int32 i)
{
	//description does not say it procs a new flash of light anymore( only in 320).
	//this is :Infusion of Light talent
	if( sp->GetProto()->Id != 66922 && target && target->HasAurasWithNameHash( SPELL_HASH_SACRED_SHIELD ) )	//no cyclic casts
	{
		SpellEntry *spellInfo = dbcSpell.LookupEntry( 66922 ); //sadly this value is only in description :(
		Spell *spell = SpellPool.PooledNew();
		spell->Init( sp->m_caster, spellInfo ,true, NULL );
		spell->forced_basepoints[0] = value * ( spellInfo->EffectBasePoints[0] + 1 ) / 100 / spellInfo->quick_tickcount;	//another x%
		SpellCastTargets targets2( target->GetGUID() );
		spell->prepare(&targets2);
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleDivineStorm(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->p_caster ) //heal is based on total damage made to N enemies
	{
//		if( i == 0 && forced_basepoints[ 2 ] == 0 )
//		{
//			forced_basepoints[ 2 ] = p_caster->m_dmg_made_since_login; 
//		}
//		else 
			if( i == 1 )
		{
			//not good since some procs may alter the actual dmg we are looking for
//			int32 dmg_diff = p_caster->m_dmg_made_since_login - forced_basepoints[ 2 ];
//			if( dmg_diff < 0 ) 
//				dmg_diff = 0;	//noway
			//value = dmg_diff * ( GetProto()->EffectBasePoints[1] + 1) / 100; 
			//learn to code protection
			uint32 hit_target_with_dmg = (uint32)(sp->m_targetUnits[0].size());
			if( hit_target_with_dmg > 3 )
				hit_target_with_dmg = 3;
			//bug protection
			if( sp->p_caster->m_dmg_made_last_time > 10000 )
				sp->p_caster->m_dmg_made_last_time = 10000;
			value = sp->p_caster->m_dmg_made_last_time * hit_target_with_dmg * ( sp->GetProto()->EffectBasePoints[1] + 1) / 100; 
			//now divide the amount between the number of party members we are healing
			if( sp->m_targetUnits[1].size() )
				value = value / (int32)(sp->m_targetUnits[1].size());
			//!!! hackfix to avoid making paladins unkillable by protecting themself then maxheal
			if( target && value > (int32)target->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * 20 / 100 )
				value = target->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * 20 / 100;
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleHysteria(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target && i == 1 )
	{
//		value = target->GetUInt32Value( UNIT_FIELD_BASE_HEALTH ) * value / 100;
		value = target->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * value / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleRend(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target && sp->p_caster )
	{
		// Wounds the target causing them to bleed for $o1 damage plus an additional ${0.2*5*(($MWB+$mwb)/2+$AP/14*$MWS)} (based on weapon damage) over $d.
		Item *it;
		if( sp->p_caster->GetItemInterface() )
		{
			it = sp->p_caster->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
			if(it)
			{
				float weapondmg = ( it->GetProto()->Damage[0].Max + it->GetProto()->Damage[0].Min ) / 2;
				float MVS = ( it->GetProto()->Delay + 75 ) / 1000.0f;
				value = float2int32( ( weapondmg + sp->p_caster->GetAP()/14*MVS ) );
				value = value * sp->GetProto()->EffectAmplitude[i] / sp->GetDuration(); //per tick ofc
			}
		}
		if( sp->GetProto()->EffectBasePoints[2] && target->GetHealthPct() > 75 )
			value = value * (sp->GetProto()->EffectBasePoints[2] + 1 ) / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleFerociousBite(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->p_caster != NULL  )
	{
		value += (uint32)( ( sp->p_caster->GetAP() * 0.1526f ) + ( sp->p_caster->GetUInt32Value( UNIT_FIELD_POWER4 ) * sp->GetProto()->dmg_multiplier[i] ) );
		sp->p_caster->SetUInt32Value( UNIT_FIELD_POWER4, 0 );
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleFaerieFire(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->u_caster && i == 2 )
	{
		//Deals ${$AP*0.15+1} damage and additional threat when used in Bear Form or Dire Bear Form.
		value = sp->u_caster->GetAP() * 15 / 100 + 1;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleReplenishment1(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i==0 )
		value = target->GetUInt32Value(UNIT_FIELD_MAXPOWER1) * 25 / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleReplenishment2(Spell *sp,Unit *target, int32 &value, int32 i)
{
	//there are 2 Replenishment spells that do different things !
	//+ Judgements of the Wise
	if( target )
	{
		value = target->GetUInt32Value(UNIT_FIELD_MAXPOWER1) / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleVictoryRush(Spell *sp,Unit *target, int32 &value, int32 i)
{
	//causing ${$AP*$m1/100} damage
	if(i==0 && sp->u_caster)
		value = (value*sp->u_caster->GetAP())/100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleOwlkinFrenzy(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i==2 && sp->u_caster )
	{ // restore $s3% base mana every $T3 sec
		value = value * sp->u_caster->GetUInt32Value( UNIT_FIELD_POWER1 ) / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleRake(Spell *sp,Unit *target, int32 &value, int32 i)
{
	//Rake the target for ${$AP/100+$m1} bleed damage and an additional ${$m2*3+$AP*0.06} damage over $d.
	if( sp->u_caster != NULL )
	{
		float ap = (float)sp->u_caster->GetAP();
		if(i==0)
			value+=(uint32)ceilf((ap*0.01f));	// / 100
		else if(i==1)
			value=(int32)ceilf((float(value * 3) + ceilf((ap*0.06f))) / 3.0f);
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleInnervate(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target )
	{
		value = value * target->GetUInt32Value( UNIT_FIELD_BASE_MANA ) / 100 / sp->GetProto()->quick_tickcount;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleGarotte(Spell *sp,Unit *target, int32 &value, int32 i)
{
	// WoWWiki says +( 0.18 * attack power / number of ticks )
	// Tooltip gives no specific reading, but says ", increased by your attack power.".
	if( sp->u_caster != NULL && i == 0 )
			value += (uint32) ceilf( ( sp->u_caster->GetAP() * 0.18f ) / 6 );
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleRupture(Spell *sp,Unit *target, int32 &value, int32 i)
{
//	1pt = Attack Power * 0.04 + x
//	2pt = Attack Power * 0.10 + y
//	3pt = Attack Power * 0.18 + z
//	4pt = Attack Power * 0.21 + a
//	5pt = Attack Power * 0.24 + b
	if( sp->p_caster != NULL && i == 0 )
	{
		int8 cp = sp->p_caster->m_comboPoints;
		value += (uint32) ceilf( ( sp->u_caster->GetAP() * 0.04f * cp ) / ( ( 6 + ( cp * 2 ) ) / 2 ) );
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleRip(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->u_caster != NULL )
		value += (uint32)ceilf(sp->u_caster->GetAP() * 0.036f);
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleExplosiveShot(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->u_caster != NULL ) 
	{
		//You fire an explosive charge into the enemy target, dealing ${$RAP*0.14+$m1}-${$RAP*0.14+$M1} Fire damage. The charge will blast the target every second for an additional $d.
		value += sp->u_caster->GetRAP() * 14 / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleBlackArrow(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->u_caster != NULL ) 
	{
		//..and dealing [RAP * 0.1 + 785] Shadow damage over 15 sec. 
		value += sp->u_caster->GetRAP() * 10 / 100 / sp->GetProto()->quick_tickcount;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleRevenge(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->u_caster != NULL )
	{
		//Instantly counterattack an enemy for ${$m1+$AP*0.2} to ${$M1+$AP*0.2} damage.   Revenge is only usable after the warrior blocks, dodges or parries an attack.
		value += sp->u_caster->GetRAP() * 20 / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleMangooseBite(Spell *sp,Unit *target, int32 &value, int32 i)
{
	// ${$AP*0.2+$m1} damage.
	if( sp->u_caster != NULL )
		value+=sp->u_caster->GetAP()/5;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleSwipeBear(Spell *sp,Unit *target, int32 &value, int32 i)
{
	// ${$AP*0.06+$m1} damage.
	if( sp->u_caster != NULL )
		value+=float2int32( sp->u_caster->GetAP()*0.06f );
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleBloodFury(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target ) // 20572 - orc racial Blood Fury -> each class has it's own so do not namhash this 
	{
		value = target->GetUInt32Value( UNIT_FIELD_LEVEL ) * 4 + 2;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleJudgeSealOfVengeanceSealOfCorruption(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->p_caster && target ) // Seal of vengeance: Judgement + Seal of Corruption: Judgement
	{
		value += float2int32(1 + 0.22f * sp->u_caster->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SCHOOL_HOLY) + 0.14f * sp->u_caster->GetAP());
		Aura *p = sp->u_caster->FindAura( sp->m_spellInfo->Id );
		if( p && p->m_visualSlot < MAX_VISIBLE_AURAS )
		{
			uint32 c = target->m_auraStackCount[ p->m_visualSlot ];
			value += float2int32(value * 1.0f + (c / 100.0f));
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleSealOfRightous(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->p_caster && i==0 ) // Seal of Righteousness: ..granting each melee attack ${$MWS*(0.022*$AP+0.044*$SPH)} additional Holy damage.  Only one Seal can be active on the Paladin at any one time.
	{
		Item *it;
		float MVS = 0;
		if(sp->p_caster->GetItemInterface())
		{
			it = sp->p_caster->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
			if(it)
				MVS = ( it->GetProto()->Delay + 75 ) / 1000.0f; //yeah that 75 is really strange but at this time it produces blizzlike value :S
		}
		else 
			MVS = sp->p_caster->GetUInt32Value( UNIT_FIELD_BASEATTACKTIME ) / 1000.0f;
		value = (int32)( MVS * float2int32( 0.044f * sp->u_caster->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SCHOOL_HOLY) + 0.022f * sp->u_caster->GetAP()) );
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleHammerOfRightous(Spell *sp,Unit *target, int32 &value, int32 i)
{
/*	if( sp->p_caster ) // Seal of Righteousness: ..granting each melee attack ${$MWS*(0.022*$AP+0.044*$SPH)} additional Holy damage.  Only one Seal can be active on the Paladin at any one time.
	{
		Item *it;
		if(sp->p_caster->GetItemInterface())
		{
			it = sp->p_caster->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
			if(it)
			{
				uint32 dmg = float2int32( (it->GetProto()->Damage[0].Min + it->GetProto()->Damage[0].Max)/2.0f );
				uint32 dps = dmg * 1000 / it->GetProto()->Delay; 
				value = dps * 4;
			}
		}
	}/**/
	if( sp->u_caster )
	{
		float dmg = (sp->u_caster->GetFloatValue(UNIT_FIELD_MINDAMAGE) + sp->u_caster->GetFloatValue(UNIT_FIELD_MAXDAMAGE))/2.0f;
		float dps = dmg * 1000 / sp->u_caster->GetUInt32Value(UNIT_FIELD_BASEATTACKTIME_1);
		value = float2int32( dps * 4.0f );
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleShieldOfRightous(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->p_caster && i==0 ) // Shield of Righteousness
	{
		value += sp->p_caster->GetUInt32Value( PLAYER_SHIELD_BLOCK );
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleExorcism(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->p_caster && target ) // Holy Vengeance/ Blood Corruption
	{
		// which deals Causes ${$m1+0.15*$SPH+0.15*$AP} to ${$M1+0.15*$SPH+0.15*$AP} Holy damage to an enemy target.  If the target is Undead or Demon, it will always critically hit.
		uint32 SPH = sp->u_caster->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SCHOOL_HOLY);
		uint32 AP = sp->u_caster->GetAP();
		value += float2int32(0.15f * SPH + 0.15f * AP);
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleShatteringThrow(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target )
	{
		if( i == 0 )
		{
			//...causing ${$64382m1+$AP*.50} damage ...
			value += sp->u_caster->GetAP() / 2;
		}
		else if( i == 1 )
		{
			//if target has imunities then remove those
			for( uint32 x = 0; x < MAX_POSITIVE_AURAS1(target); x++ )
			{
				if( target->m_auras[x] != NULL &&
					( target->m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_INVULNERABLE ) )
					{
						target->m_auras[x]->Remove();
						value = 0;	//skipp decreasing armor if we removed imunity
					}
			}
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleHolyVengeanceBloodCorruption(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->p_caster ) // Holy Vengeance/ Blood Corruption
	{
		// which deals ${(0.013*$SPH+0.025*$AP)*6} additional Holy damage over $31803d.
		uint32 SPH = sp->u_caster->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SCHOOL_HOLY);
		uint32 AP = sp->u_caster->GetAP();
//		value = float2int32(0.088f * SPH + 0.15f * AP);
		value = float2int32(6.0f*0.013f * SPH + 6.0f*0.025f * AP);
		value /= sp->GetProto()->quick_tickcount;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleGauge(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 0 ) //gouge
	{
		if( sp->u_caster != NULL )
			value += (uint32)ceilf(sp->u_caster->GetAP() * 0.21f);
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleDeathStrike(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->u_caster && target )
	{
		if( i == 1 ) 
		{
			//try to find the target we casted the spell on
			//target is attack target now, heal will target the caster
			uint32 disease_cnt = target->GetDKDiseaseCount();
//			value = sp->u_caster->GetUInt32Value(UNIT_FIELD_BASE_HEALTH) * disease_cnt * 5 / 100; //pct heal of the disease dmg. This is quite some value
			sp->forced_basepoints[2] = sp->u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * disease_cnt * 5 / 100; //pct heal of the disease dmg. This is quite some value
		}
		else if( i == 2 )
		{
			value = sp->forced_basepoints[2];
			if( (int32)sp->u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH) < value * 5 )
				value = 0;
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleBloodBoil(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target )
	{
		//...base damage is 275-315 (a flat increase of 95) Attack power coefficient is 0.095 (an additional 0.035 * AP).
		uint32 disease_cnt = target->GetDKDiseaseCount();
		disease_cnt = MIN( disease_cnt, 3);	//no more bugget values this gets limited here
		if( disease_cnt )
			value += 35 * disease_cnt;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleBloodStrikeObliterate(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target )
	{
		// Instantly strike the enemy, causing $s2% weapon damage plus ${$m1*$m2/100}, total damage increased by ${$m3/2}.1% for each of your diseases on the target.
		if( i == 1 ) //count diseases on target
		{
			//try to find the target we casted the spell on
			uint32 disease_cnt = target->GetDKDiseaseCount();
			//we already calced add_dmg in effect0 but we are overwriting that
//			add_damage = ( sp->GetProto()->EffectBasePoints[0]+1) * ( sp->GetProto()->EffectBasePoints[1]+1) / 100 * disease_cnt *( sp->GetProto()->EffectBasePoints[2]+1)/200;
			sp->add_damage = sp->add_damage + sp->add_damage * disease_cnt * ( sp->GetProto()->EffectBasePoints[2]+1)/200;
			//pct dmg is increased too
			value = value + disease_cnt*(sp->GetProto()->EffectBasePoints[2]+1)/2;
			if( sp->GetProto()->NameHash == SPELL_HASH_OBLITERATE 
				//talent that removes the effect of removing diseases
				&& sp->p_caster && sp->p_caster->FindAuraPassiveByNameHash( SPELL_HASH_ANNIHILATION ) == false 
				)
			{
				target->RemoveAuraByNameHash( SPELL_HASH_BLOOD_PLAGUE );
				target->RemoveAuraByNameHash( SPELL_HASH_FROST_FEVER );
			}
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleHearthStrike(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target )
	{
		// causing $s2% weapon damage plus ${$m1*$m2/100}, total damage increased by $m3% for each of your diseases on the target.
		if( i == 1 ) //count diseases on target
		{
			//try to find the target we casted the spell on
			uint32 disease_cnt = target->GetDKDiseaseCount();
			//simpleformula that is not in sinc with client opinion :(
			int32 bonus_pct_dmg = (sp->GetProto()->EffectBasePoints[2] + 1)*disease_cnt ;
			if( sp->u_caster != NULL )
				SM_PIValue(sp->u_caster->SM_PCost,&bonus_pct_dmg,sp->GetProto()->SpellGroupType);
			sp->add_damage = sp->add_damage + sp->add_damage * bonus_pct_dmg / 100;
			value += bonus_pct_dmg;
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleScourgeStrike(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target )
	{
		//deals $s2% of weapon damage as Shadow damage plus ${$m1*$m2*1.25/100}, total damage increased $s3% per each of your diseases on the target.
		if( i == 1 ) //count diseases on target
		{
			//we already calced add_dmg in effect0 but we are overwriting that
			sp->add_damage = sp->add_damage*125/100;
			//try to find the target we casted the spell on
			uint32 disease_cnt = target->GetDKDiseaseCount();
			//simpleformula that is not in sinc with client opinion :(
			int32 bonus_pct_dmg = (sp->GetProto()->EffectBasePoints[2] + 1)*disease_cnt ;
			if( sp->u_caster != NULL )
				SM_PIValue(sp->u_caster->SM_PCost,&bonus_pct_dmg,sp->GetProto()->SpellGroupType);
			sp->add_damage = sp->add_damage * (bonus_pct_dmg + 100 )/ 100;
			value += bonus_pct_dmg;
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleBloodCakedStrike(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target )
	{
		// hits for $50463s1% weapon damage plus ${$50463m1/2}.1% for each of your diseases on the target.
		if( i == 1 ) //count diseases on target
		{
			//try to find the target we casted the spell on
			uint32 disease_cnt = target->GetDKDiseaseCount();
			disease_cnt = MIN( disease_cnt, 3 );
			//simpleformula that is not in sinc with client opinion :(
			int32 bonus_add_dmg = (sp->GetProto()->EffectBasePoints[1] + 1) * disease_cnt / 2;
			if( sp->u_caster != NULL )
				SM_PIValue(sp->u_caster->SM_PCost,&bonus_add_dmg,sp->GetProto()->SpellGroupType);
			value += bonus_add_dmg;
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleAntiMagicShell(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target && i == 0)
	{
		value = target->GetUInt32Value(UNIT_FIELD_MAXHEALTH)*50/100;	//value is in description
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandlePlagueStrike(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i==0 && target )
	{
		//remove 1 heal over time effect from target
		for(uint32 t=0;t<MAX_POSITIVE_AURAS1(target);t++)
			if( target->m_auras[ t ] && target->m_auras[ t ]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_HEAL_OVER_TIME )
			{
				target->m_auras[ t ]->Remove();
				break;
			}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleRuneStrike(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 1 && sp->u_caster)
	{
		//Strike the target for $s2% weapon damage plus ${$m2*$AP*$m3/10000}.  Only usable after an attack is dodged or parried.  Can't be dodged, blocked, or parried.
		sp->add_damage = value * sp->u_caster->GetAP() * (sp->GetProto()->EffectBasePoints[2] + 1) / 10000;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleIceLance(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target )
	{
		if( target->HasFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_FROZEN ) ) //Ice Lance deals 3x damage if target is frozen
			value *= 2;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleChaosBane(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->m_targetUnits[i].size() )
	{
		//Deals $s1 Shadow damage, split between all enemy targets within $a1 yards of the impact crater.
		value = value / (int32)(sp->m_targetUnits[i].size());	//if this is 0 then this function would never get called
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleTympanicTantum(Spell *sp,Unit *target, int32 &value, int32 i)
{
	//Deals $s1% damage every $t1 sec for $d. Nearby enemies are also dazed for the duration.
	if( target && i == 0)
	{
		value = target->GetUInt32Value( UNIT_FIELD_BASE_HEALTH ) * (sp->GetProto()->EffectBasePoints[ i ] + 1) / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleConflagrate(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target )
	{
		//$?s56235[Causes][Consumes] an Immolate or Shadowflame effect on the enemy target to instantly deal damage equal to 60% of your Immolate or Shadowflame, and causes an additional $s3% damage over $d.
		if( i == 0 )
		{
			Aura *ta = target->FindAuraByNameHash( SPELL_HASH_IMMOLATE );
			if( ta == NULL || ta->m_modcount == 0 )
				ta = target->FindAuraByNameHash( SPELL_HASH_SHADOWFLAME );

			if( ta != NULL && ta->m_modcount != 0 )
			{
				//immolate total dmg
				sp->forced_basepoints[0] = ta->m_modList[0].m_amount * ta->GetSpellProto()->quick_tickcount;
				sp->forced_basepoints[0] *= 2;	//for the sake of DD part
				//only 60% dmg is converted to instant dmg
				value = sp->forced_basepoints[0] * value / 100;
				if( sp->p_caster == NULL || sp->p_caster->HasGlyphWithID( GLYPH_WARLOCK_CONFLAGRATE ) == false )
				{
					ta->Remove();				//glyph of conflagrate might negate this
					target->RemoveFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_IMMOLATE );
				}
				ta = NULL;					//sanity
			}
			else sp->forced_basepoints[0] = 0;
		}
		else if( i == 1 )
		{
			//only 40% dmg is converted to DOTs
			value = sp->forced_basepoints[0] * value / 100 / sp->GetProto()->quick_tickcount;
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleHandOfReckoning(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 0 && target )
	{
		if( target->IsPlayer() )
			value = 0;
//		else if( sp->u_caster && target->IsCreature() && target->GetAIInterface()->GetNextTarget() != sp->m_caster )
		else if( sp->u_caster )
			value = sp->u_caster->GetAP() * 50 / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleAvangersShield(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 0 && sp->u_caster )
	{
		value += ( sp->u_caster->GetAP() +  sp->u_caster->GetDamageDoneMod( SCHOOL_HOLY ) ) * 7 / 100 + 1;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleVampiricEmbrace(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( target )
	{
		if( target != sp->m_caster )
			value = value / 5;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleEnvenom(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 0 && sp->p_caster )//Envenom
	{
		value *= sp->p_caster->m_comboPoints;
		value += (uint32)(sp->p_caster->GetAP()*(0.09f*sp->p_caster->m_comboPoints));
		sp->m_requiresCP=true;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleEvocationGlyph(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 1 && sp->p_caster && sp->p_caster->HasGlyphWithID(GLYPH_MAGE_EVOCATION) )
		value = 15;	//also restore 60% of max HP over X seconds
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleAspectMastery(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so)
{
	//Aspect of the Viper - Reduces the damage penalty by $s1%.
	if( sp->GetProto()->NameHash == SPELL_HASH_ASPECT_OF_THE_VIPER && i == 1 )
	{
		value = value * so->mod_amount_pct[0] / 100;	
	}
	//Aspect of the Monkey - Reduces the damage done to you while active by $s2%.
	else if( sp->GetProto()->NameHash == SPELL_HASH_ASPECT_OF_THE_MONKEY && i == 1 )
	{
		value += so->mod_amount[1];	//value was - but need + ?
	}
	//Aspect of the Hawk - Increases the attack power bonus by $s3%.
	else if( sp->GetProto()->NameHash == SPELL_HASH_ASPECT_OF_THE_HAWK && i == 0 )
	{
		value = value * so->mod_amount_pct[2] / 100;
	}
	//Aspect of the Dragonhawk - Combines the bonuses from Aspect of the Monkey and Hawk.
//	else if( sp->GetProto()->NameHash == SPELL_HASH_ASPECT_OF_THE_DRAGONHAWK && i == 1 )
	else if( (sp->GetProto()->Id == 61846 || sp->GetProto()->Id == 61847) && i == 0 )	//the additional cast mod only
			value = value * so->mod_amount_pct[2] / 100;
	else if( sp->GetProto()->Id == 61848 && i == 1 )	//the additional cast mod only
			value += so->mod_amount[1];	
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleCounterAttack(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->u_caster )
		value += sp->u_caster->GetAP() * 20 / 100;	//also restore 60% of max HP over X seconds
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleImprovedDemonicTactics(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( sp->u_caster )
	{
		int32 base_critchance_now = 0;
		for( uint32 t=0;t<SCHOOL_COUNT;t++)
			base_critchance_now = MAX( base_critchance_now, float2int32( sp->u_caster->SpellCritChanceSchool[t] ));
		base_critchance_now	+= float2int32( sp->u_caster->spellcritperc );

		value = base_critchance_now * value / 100;
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

SPELL_EFFECT_OVERRIDE_RETURNS HandleConsecration(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 0 && sp->u_caster )
		value = ( value + ( sp->u_caster->GetAP() +  sp->u_caster->GetDamageDoneMod( SCHOOL_HOLY ) ) * 4 / 100 );
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

//Sacrifice
SPELL_EFFECT_OVERRIDE_RETURNS EH_47986(Spell *sp,Unit *target, int32 &value, int32 i)
{
	//25% of voidvalker HP
	if( i == 1 && target )
		value = target->GetMaxHealth() * value / 100 ;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

//Sonic Screech
SPELL_EFFECT_OVERRIDE_RETURNS EH_64422(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 0 &&  sp->m_targetUnits[i].size() > 1 )
		value = value / (int32)(sp->m_targetUnits[i].size());	//should already target mobs infront
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

//Pulsing Shockwave
SPELL_EFFECT_OVERRIDE_RETURNS EH_52942(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 0 &&  target && sp->u_caster )
	{
		float _distance = sp->u_caster->CalcDistance( target );
		if( _distance >= 2.0f )
			value = float2int32(value * _distance);
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

//Incinerate
SPELL_EFFECT_OVERRIDE_RETURNS EH_29722(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 0 &&  target && target->HasFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_IMMOLATE ) )
		value += value / 4;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

//gore
SPELL_EFFECT_OVERRIDE_RETURNS EH_35290(Spell *sp,Unit *target, int32 &value, int32 i)
{
	//this check will probably always fail :(
	if( i == 0 &&  sp->p_caster && sp->p_caster->Cooldown_CanCast( sp->GetProto() ) == false )
		value = value * 2;
	else if( Rand( 50 ) )
		value = value * 2;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

//Bloodthirst
SPELL_EFFECT_OVERRIDE_RETURNS EH_23881(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 0 && sp->u_caster)
		value = sp->u_caster->GetAP()*value/100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

//Shield Slam
SPELL_EFFECT_OVERRIDE_RETURNS EH_23922(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 1 && sp->p_caster != NULL )
	{
		Item *it = sp->p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
		if( it && it->GetProto()->InventoryType == INVTYPE_SHIELD )
		{
			uint32 blockable_damage = sp->p_caster->GetUInt32Value( PLAYER_SHIELD_BLOCK );
			if( blockable_damage > 10000 )
				blockable_damage = 10000;
			value += blockable_damage;
		}
	}
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

//Heroic Throw
SPELL_EFFECT_OVERRIDE_RETURNS EH_57755(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 0 && sp->u_caster)
		value += sp->u_caster->GetAP() / 2;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

//Intercept
SPELL_EFFECT_OVERRIDE_RETURNS EH_20253(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 1 && sp->u_caster)
		value = sp->u_caster->GetAP() * 12 / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

//Thunder Clap
SPELL_EFFECT_OVERRIDE_RETURNS EH_6343(Spell *sp,Unit *target, int32 &value, int32 i)
{
	if( i == 0 && sp->u_caster)
		value = sp->u_caster->GetAP() * 20 / 100;
	return SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION;
}

void RegisterEffectOverrides()
{
	SpellEntry *sp;
	//Thunder Clap
	REGISTER_HANDLER( 6343 );
	REGISTER_SAMEHANDLER( 8198, 6343 );
	REGISTER_SAMEHANDLER( 8204, 6343 );
	REGISTER_SAMEHANDLER( 8205, 6343 );
	REGISTER_SAMEHANDLER( 11580, 6343 );
	REGISTER_SAMEHANDLER( 11581, 6343 );
	REGISTER_SAMEHANDLER( 25264, 6343 );
	REGISTER_SAMEHANDLER( 47501, 6343 );
	REGISTER_SAMEHANDLER( 47502, 6343 );
	REGISTER_SAMEHANDLER( 57832, 6343 );
	REGISTER_SAMEHANDLER( 60019, 6343 );
	//Intercept
	REGISTER_HANDLER( 20253 );
	//Heroic Throw
	REGISTER_HANDLER( 57755 );
	//Shield Slam
	REGISTER_HANDLER( 23922 );
	REGISTER_SAMEHANDLER( 23885, 23922 );
	REGISTER_SAMEHANDLER( 23923, 23922 );
	REGISTER_SAMEHANDLER( 23924, 23922 );
	REGISTER_SAMEHANDLER( 23925, 23922 );
	REGISTER_SAMEHANDLER( 25258, 23922 );
	REGISTER_SAMEHANDLER( 30356, 23922 );
	REGISTER_SAMEHANDLER( 47487, 23922 );
	REGISTER_SAMEHANDLER( 47488, 23922 );
	//Bloodthirst
	REGISTER_HANDLER( 23881 );
	REGISTER_SAMEHANDLER( 23892, 23881 );
	REGISTER_SAMEHANDLER( 23893, 23881 );
	REGISTER_SAMEHANDLER( 23894, 23881 );
	REGISTER_SAMEHANDLER( 25251, 23881 );
	REGISTER_SAMEHANDLER( 30335, 23881 );
	REGISTER_SAMEHANDLER( 57790, 23881 );
	REGISTER_SAMEHANDLER( 71938, 23881 );
	//gore - Your boar gores the enemy for $35290s1.  Causes double damage if used within 6 sec of a Charge.
	REGISTER_HANDLER( 35290 );
	REGISTER_SAMEHANDLER( 35291, 35290 );
	REGISTER_SAMEHANDLER( 35292, 35290 );
	REGISTER_SAMEHANDLER( 35293, 35290 );
	REGISTER_SAMEHANDLER( 35294, 35290 );
	REGISTER_SAMEHANDLER( 35295, 35290 );
	//Incinerate
	REGISTER_HANDLER( 29722 );
	REGISTER_SAMEHANDLER( 32231, 29722 );
	REGISTER_SAMEHANDLER( 47837, 29722 );
	REGISTER_SAMEHANDLER( 47838, 29722 );
	//Pulsing Shockwave
	REGISTER_HANDLER( 52942 );
	REGISTER_SAMEHANDLER( 59837, 52942 );
	//Sonic Screech, Auriaya encounter
	REGISTER_HANDLER( 64422 );
	REGISTER_SAMEHANDLER( 64688, 64422 );
	//Meteor Slash
	REGISTER_SAMEHANDLER( 45150, 64422 );
	//Sacrifice
	REGISTER_HANDLER( 47986 );
}