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

#ifndef _SPELL_EFFECT_OVERRIDE_H
#define _SPELL_EFFECT_OVERRIDE_H

// the idea is to provide a way to override effects of a spell
// these are very similar to proc handler but do not have a special spell created for them(sadly)
// example	: transform damage effect into heal effect
// example2 : provide a way to script the effect value unconditionally

class Spell;
class Unit;
class Aura;

enum SPELL_EFFECT_OVERRIDE_RETURNS
{
	SPELL_EFFECT_OVERRIDE_CONTINUE_EXECUTION	= 1,
	SPELL_EFFECT_OVERRIDE_BREAK_EXECUTION		= 2,
};

class SpellEffectOverrideScript
{
public:
	SpellEffectOverrideScript();	//constructor !
	uint32	ori_spell_id;			//the spell that created this effect
	uint32	required_namehash[3];	//only do effects if there is a NameHashMatch
	uint32	required_spell_id;		//only do effects on 1 spell
	uint32	required_effect_type[3];//only do mod if effect matches;
	uint32	required_aura_type[3];	//only do mod if aura matches;
	int32	mod_amount[3];			//mod effect with this flat value
	int32	mod_amount_pct[3];		//mod effect after adding flat by pct value
	//special case handler
	SPELL_EFFECT_OVERRIDE_RETURNS (*ApplyHandler)(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i,SpellEffectOverrideScript *so);
	SPELL_EFFECT_OVERRIDE_RETURNS (*RemoveHandler)(Aura *aur,Unit *caster,Unit *target, int32 &value, int32 i,SpellEffectOverrideScript *so);
};

SPELL_EFFECT_OVERRIDE_RETURNS HandleDefaultEffectOverride(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);

SPELL_EFFECT_OVERRIDE_RETURNS HandleGlyphOfLesserHealingWave(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleGlyphOfRegrowth(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleMoltenFury(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleStarfireBonus(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleDeatsEmbrace(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleTestOfFaith(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleMercilessCombat(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleRageOfRivedare(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleTundraStalker(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleMarkedForDeath(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleNourishHealBoost(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleAspectMastery(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleSoulSiphon(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);
SPELL_EFFECT_OVERRIDE_RETURNS HandleTormentTheWeak(Spell *sp,Unit *caster,Unit *target, int32 &value, int32 i, SpellEffectOverrideScript *so);

//these are handlers added to spell effects to catch and modify dmg/effect of a spell. These are static and not depending on caster spellbook
SPELL_EFFECT_OVERRIDE_RETURNS HandleSteadyShot(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleDeadlyPoison(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleInstantPoison(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleWoundPoison(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleArcaneShot(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleSerpentSting(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleKillShot(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleEviscerate(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleDivineSpiritPrayerOfSpirit(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleSealOfLight(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleFlashOfLight(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleDivineStorm(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleHysteria(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleRend(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleFerociousBite(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleFaerieFire(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleReplenishment1(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleReplenishment2(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleVictoryRush(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleOwlkinFrenzy(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleRake(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleInnervate(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleGarotte(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleRupture(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleRip(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleExplosiveShot(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleBlackArrow(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleRevenge(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleMangooseBite(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleSwipeBear(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleBloodFury(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleJudgeSealOfVengeanceSealOfCorruption(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleSealOfRightous(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleHammerOfRightous(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleShieldOfRightous(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleExorcism(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleShatteringThrow(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleHolyVengeanceBloodCorruption(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleGauge(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleDeathStrike(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleBloodBoil(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleBloodStrikeObliterate(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleHearthStrike(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleScourgeStrike(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleBloodCakedStrike(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleAntiMagicShell(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandlePlagueStrike(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleRuneStrike(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleIceLance(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleChaosBane(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleTympanicTantum(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleConflagrate(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleHandOfReckoning(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleAvangersShield(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleVampiricEmbrace(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleEnvenom(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleEvocationGlyph(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleCounterAttack(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleImprovedDemonicTactics(Spell *sp,Unit *target, int32 &value, int32 i);
SPELL_EFFECT_OVERRIDE_RETURNS HandleConsecration(Spell *sp,Unit *target, int32 &value, int32 i);

void RegisterCanCastOverrides();
void RegisterEffectOverrides();
void RegisterTargetingOverride();
#endif