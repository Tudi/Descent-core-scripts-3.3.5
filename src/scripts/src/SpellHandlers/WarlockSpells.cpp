/****************************************************************************
 *
 * SpellHandler Plugin
 * Copyright (c) 2007 Team arcemu
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to Creative Commons,
 * 543 Howard Street, 5th Floor, San Francisco, California, 94105, USA.
 *
 * EXCEPT TO THE EXTENT REQUIRED BY APPLICABLE LAW, IN NO EVENT WILL LICENSOR BE LIABLE TO YOU
 * ON ANY LEGAL THEORY FOR ANY SPECIAL, INCIDENTAL, CONSEQUENTIAL, PUNITIVE OR EXEMPLARY DAMAGES
 * ARISING OUT OF THIS LICENSE OR THE USE OF THE WORK, EVEN IF LICENSOR HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 */

#include "StdAfx.h"
#include "Setup.h"

int32 GetSpellDmgBonusNoNerf(Unit *caster, Unit *pVictim, SpellEntry *spellInfo,int32 base_dmg)
{
	int32 plus_damage = 0;
	uint32 school = spellInfo->School;

//------------------------------by school---------------------------------------------------
	plus_damage += caster->GetDamageDoneMod(school);
//------------------------------by victim type----------------------------------------------
	if(pVictim->IsCreature() && static_cast< Creature*>(pVictim)->GetCreatureInfo() && caster->IsPlayer() )
		plus_damage += static_cast< Player* >(caster)->IncreaseDamageByType[static_cast<Creature*>(pVictim)->GetCreatureInfo()->Type]; //this might create a crash. Leaving it like this to detect new creature types :)
//==============================Bonus Adding To Main Damage=================================
	int32 bonus_damage = plus_damage;
	if((spellInfo->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD))
	{
		SM_FIValue(caster->SM_FDamageBonus, &bonus_damage, spellInfo->SpellGroupType);
		int dmg_bonus_pct=0;
		SM_FIValue(caster->SM_PDamageBonus,&dmg_bonus_pct,spellInfo->SpellGroupType);
		bonus_damage += (base_dmg+bonus_damage)*dmg_bonus_pct/100;
	}
//------------------------------by school----------------------------------------------
	float summaryPCTmod = caster->GetDamageDonePctMod(school)-1; //value is initialized with 1
//	summaryPCTmod += caster->DamageDoneModPCT[school];	// BURLEX FIXME
	int32 res = (int32)((base_dmg+bonus_damage)*summaryPCTmod + bonus_damage);
	return res;
}

//this spell cannot be resisted, or absorbed
bool ChaosBolt(uint32 i, Spell *pSpell)
{
	Unit *pVictim = pSpell->GetUnitTarget();
	if(!pSpell->u_caster || !pVictim) 
		return true;

	SpellEntry *spellInfo = pSpell->GetProto();
	uint32 spellID = spellInfo->Id;
	Unit *caster = pSpell->u_caster;
	uint32 school = spellInfo->School;
	float res = float(pSpell->damage);
	int32 spell_dmg_bonus;
	uint32 aproc;
	uint32 vproc;
	aproc = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_ANY_SPELL_DAMAGE_DONE | PROC_ON_SPELL_HIT;
	vproc = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_ANY_DAMAGE_VICTIM | PROC_ON_SPELL_HIT_VICTIM; 

	bool critical = false;
//==============================+Spell Damage Bonus Calculations============================
	caster->RemoveAurasByInterruptFlagButSkip( AURA_INTERRUPT_ON_START_ATTACK, spellID );
	int32 dmg_i = (int32)res;
	spell_dmg_bonus = GetSpellDmgBonusNoNerf( caster, pVictim, spellInfo, dmg_i ) ;
	res += spell_dmg_bonus;
//------------------------------critical strike chance--------------------------------------	
	float CritChance=0.0f;
	CritChance = caster->spellcritperc + caster->SpellCritChanceSchool[school] + pVictim->AttackerCritChanceMod[school];
	if( caster->IsPlayer() && ( pVictim->m_rooted - pVictim->m_stunned ) )	
		CritChance += static_cast< Player* >( caster )->m_RootedCritChanceBonus;

	if( Need_SM_Apply(spellInfo) )
		SM_FFValue(caster->SM_CriticalChance, &CritChance, spellInfo->SpellGroupType);

	if( pVictim->IsPlayer() )
		CritChance -= static_cast< Player* >(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE );

	if( CritChance < 0 ) 
		CritChance = 0;
	if( CritChance > 95 ) 
		CritChance = 95;
	critical = Rand(CritChance);
//==============================Spell Critical Hit==========================================
	if (critical)
	{		
		int32 critical_bonus = 100;
		if( Need_SM_Apply(spellInfo) )
			SM_FIValue( caster->SM_PCriticalDamage, &critical_bonus, spellInfo->SpellGroupType );

		if( critical_bonus > 0 )
			res = res * (( ( float(critical_bonus) / 2.0f ) / 100.0f ) + 1.0f);
		if (pVictim->GetTypeId() == TYPEID_UNIT && static_cast<Creature*>(pVictim)->GetCreatureInfo() && static_cast<Creature*>(pVictim)->GetCreatureInfo()->Rank != ELITE_WORLDBOSS)
			pVictim->Emote( EMOTE_ONESHOT_WOUNDCRITICAL );
		aproc |= PROC_ON_SPELL_CRIT_HIT;
		vproc |= PROC_ON_SPELL_CRIT_HIT_VICTIM;
	}

	if(res < 0) 
		res = 0;

	res=(float)res;
	dealdamage dmg;
	dmg.school_type = school;

	// Paladin: Blessing of Sacrifice, and Warlock: Soul Link
	if( pVictim->m_damageSplitTarget)
		res = (float)pVictim->DoDamageSplitTarget((uint32)res, school, false);
	
//==============================Data Sending ProcHandling===================================
	caster->SendSpellNonMeleeDamageLog(caster, pVictim, spellInfo->Id, float2int32(res), school, 0, 0, false, 0, critical, caster->IsPlayer());
	caster->DealDamage( pVictim, float2int32( res ), 2, 0, spellID );
	
	int32 tdmg = float2int32(res);
	pVictim->HandleProc( vproc, static_cast< Unit* >( caster ), spellInfo, tdmg, 0 );
	static_cast< Unit* >( caster )->HandleProc( aproc, pVictim, spellInfo, tdmg, 0 );

	if( pVictim->GetCurrentSpell() )
		pVictim->GetCurrentSpell()->AddTime( school );

//==========================================================================================
//==============================Post Damage Processing======================================
//==========================================================================================
	if( caster->IsPlayer() )
		static_cast< Player* >(caster)->CombatStatusHandler_ResetPvPTimeout();

	return true;
}

void SetupWarlockSpells(ScriptMgr * mgr)
{
    mgr->register_dummy_spell(50796, &ChaosBolt);
    mgr->register_dummy_spell(59170, &ChaosBolt);
    mgr->register_dummy_spell(59171, &ChaosBolt);
    mgr->register_dummy_spell(59172, &ChaosBolt);
}

