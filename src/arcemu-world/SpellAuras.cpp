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

pSpellAura SpellAuraHandler[TOTAL_SPELL_AURAS]={
		&Aura::SpellAuraNULL,//SPELL_AURA_NONE = 0
		&Aura::SpellAuraBindSight,//SPELL_AURA_BIND_SIGHT = 1
		&Aura::SpellAuraModPossess,//SPELL_AURA_MOD_POSSESS = 2,
		&Aura::SpellAuraPeriodicDamage,//SPELL_AURA_PERIODIC_DAMAGE = 3,
		&Aura::SpellAuraDummy,//SPELL_AURA_DUMMY = 4,
		&Aura::SpellAuraModConfuse,//SPELL_AURA_MOD_CONFUSE = 5,
		&Aura::SpellAuraModCharm,//SPELL_AURA_MOD_CHARM = 6,
		&Aura::SpellAuraModFear,//SPELL_AURA_MOD_FEAR = 7,
		&Aura::SpellAuraPeriodicHeal,//SPELL_AURA_PERIODIC_HEAL = 8,
		&Aura::SpellAuraModAttackSpeed,//SPELL_AURA_MOD_ATTACKSPEED = 9,
		&Aura::SpellAuraModThreatGeneratedSchoolPCT,//SPELL_AURA_MOD_THREAT = 10,
		&Aura::SpellAuraModTaunt,//SPELL_AURA_MOD_TAUNT = 11,
		&Aura::SpellAuraModStun,//SPELL_AURA_MOD_STUN = 12,
		&Aura::SpellAuraModDamageDone,//SPELL_AURA_MOD_DAMAGE_DONE = 13,
		&Aura::SpellAuraModDamageTaken,//SPELL_AURA_MOD_DAMAGE_TAKEN = 14,
		&Aura::SpellAuraDamageShield,//SPELL_AURA_DAMAGE_SHIELD = 15,
		&Aura::SpellAuraModStealth,//SPELL_AURA_MOD_STEALTH = 16,
		&Aura::SpellAuraModDetect,//SPELL_AURA_MOD_DETECT = 17,
		&Aura::SpellAuraModInvisibility,//SPELL_AURA_MOD_INVISIBILITY = 18,
		&Aura::SpellAuraModInvisibilityDetection,//SPELL_AURA_MOD_INVISIBILITY_DETECTION = 19,
		&Aura::SpellAuraModTotalHealthRegenPct,// SPELL_AURA_MOD_TOTAL_HEALTH_REGEN_PCT = 20
		&Aura::SpellAuraModTotalManaRegenPct,// SPELL_AURA_MOD_TOTAL_MANA_REGEN_PCT = 21
		&Aura::SpellAuraModResistance,//SPELL_AURA_MOD_RESISTANCE = 22,
		&Aura::SpellAuraPeriodicTriggerSpell,//SPELL_AURA_PERIODIC_TRIGGER_SPELL = 23,
		&Aura::SpellAuraPeriodicEnergize,//SPELL_AURA_PERIODIC_ENERGIZE = 24,
		&Aura::SpellAuraModPacify,//SPELL_AURA_MOD_PACIFY = 25,
		&Aura::SpellAuraModRoot,//SPELL_AURA_MOD_ROOT = 26,
		&Aura::SpellAuraModSilence,//SPELL_AURA_MOD_SILENCE = 27,
		&Aura::SpellAuraReflectSpells,//SPELL_AURA_REFLECT_SPELLS = 28,
		&Aura::SpellAuraModStat,//SPELL_AURA_MOD_STAT = 29,
		&Aura::SpellAuraModSkill,//SPELL_AURA_MOD_SKILL = 30,
		&Aura::SpellAuraModIncreaseSpeed,//SPELL_AURA_MOD_INCREASE_SPEED = 31,
		&Aura::SpellAuraModIncreaseMountedSpeed,//SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED = 32,
		&Aura::SpellAuraModDecreaseSpeed,//SPELL_AURA_MOD_DECREASE_SPEED = 33,
		&Aura::SpellAuraModIncreaseHealth,//SPELL_AURA_MOD_INCREASE_HEALTH = 34,
		&Aura::SpellAuraModIncreaseEnergy,//SPELL_AURA_MOD_INCREASE_ENERGY = 35,
		&Aura::SpellAuraModShapeshift,//SPELL_AURA_MOD_SHAPESHIFT = 36,
		&Aura::SpellAuraModEffectImmunity,//SPELL_AURA_EFFECT_IMMUNITY = 37,
		&Aura::SpellAuraModStateImmunity,//SPELL_AURA_STATE_IMMUNITY = 38,
		&Aura::SpellAuraModSchoolImmunity,//SPELL_AURA_SCHOOL_IMMUNITY = 39,
		&Aura::SpellAuraModDmgImmunity,//SPELL_AURA_DAMAGE_IMMUNITY = 40,
		&Aura::SpellAuraModDispelImmunity,//SPELL_AURA_DISPEL_IMMUNITY = 41,
		&Aura::SpellAuraProcTriggerSpell,//SPELL_AURA_PROC_TRIGGER_SPELL = 42,
		&Aura::SpellAuraProcTriggerDamage,//SPELL_AURA_PROC_TRIGGER_DAMAGE = 43,
		&Aura::SpellAuraTrackCreatures,//SPELL_AURA_TRACK_CREATURES = 44,
		&Aura::SpellAuraTrackResources,//SPELL_AURA_TRACK_RESOURCES = 45,
		&Aura::SpellAuraNULL,//SPELL_AURA_MOD_PARRY_SKILL = 46, obsolete? not used in 1.12.1 spell.dbc
		&Aura::SpellAuraModParryPerc,//SPELL_AURA_MOD_PARRY_PERCENT = 47,
		&Aura::SpellAuraNULL,//SPELL_AURA_MOD_DODGE_SKILL = 48, obsolete?
		&Aura::SpellAuraModDodgePerc,//SPELL_AURA_MOD_DODGE_PERCENT = 49,
		&Aura::SpellAuraCritHealDoneModPct,//SPELL_AURA_MOD_CRIT_HEAL_DONE_PCT = 50,
		&Aura::SpellAuraModBlockPerc,//SPELL_AURA_MOD_BLOCK_PERCENT = 51,
		&Aura::SpellAuraModCritPerc,//SPELL_AURA_MOD_CRIT_PERCENT = 52,
		&Aura::SpellAuraPeriodicLeech,//SPELL_AURA_PERIODIC_LEECH = 53,
		&Aura::SpellAuraModHitChance,//SPELL_AURA_MOD_HIT_CHANCE = 54,
		&Aura::SpellAuraModSpellHitChance,//SPELL_AURA_MOD_SPELL_HIT_CHANCE = 55,
		&Aura::SpellAuraTransform,//SPELL_AURA_TRANSFORM = 56,
		&Aura::SpellAuraModSpellCritChance,//SPELL_AURA_MOD_SPELL_CRIT_CHANCE = 57,
		&Aura::SpellAuraIncreaseSwimSpeed,//SPELL_AURA_MOD_INCREASE_SWIM_SPEED = 58,
		&Aura::SpellAuraModCratureDmgDone,//SPELL_AURA_MOD_DAMAGE_DONE_CREATURE = 59,
		&Aura::SpellAuraPacifySilence,//SPELL_AURA_MOD_PACIFY_SILENCE = 60,
		&Aura::SpellAuraModScale,//SPELL_AURA_MOD_SCALE = 61,
		&Aura::SpellAuraPeriodicHealthFunnel,//SPELL_AURA_PERIODIC_HEALTH_FUNNEL = 62,
		&Aura::SpellAuraNULL,//SPELL_AURA_PERIODIC_MANA_FUNNEL = 63,//obselete?
		&Aura::SpellAuraPeriodicManaLeech,//SPELL_AURA_PERIODIC_MANA_LEECH = 64,
		&Aura::SpellAuraModCastingSpeed,//SPELL_AURA_MOD_CASTING_SPEED = 65,
		&Aura::SpellAuraFeignDeath,//SPELL_AURA_FEIGN_DEATH = 66,
		&Aura::SpellAuraModDisarm,//SPELL_AURA_MOD_DISARM = 67,
		&Aura::SpellAuraModStalked,//SPELL_AURA_MOD_STALKED = 68,
		&Aura::SpellAuraSchoolAbsorb,//SPELL_AURA_SCHOOL_ABSORB = 69,
		&Aura::SpellAuraNULL,//SPELL_AURA_EXTRA_ATTACKS = 70,//obselete?
		&Aura::SpellAuraModSpellCritChanceSchool,//SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL = 71,
		&Aura::SpellAuraModPowerCost,//SPELL_AURA_MOD_POWER_COST = 72,
		&Aura::SpellAuraModPowerCostSchool,//SPELL_AURA_MOD_POWER_COST_SCHOOL = 73,
		&Aura::SpellAuraReflectSpellsSchool,//SPELL_AURA_REFLECT_SPELLS_SCHOOL = 74,
		&Aura::SpellAuraModLanguage,//SPELL_AURA_MOD_LANGUAGE = 75,
		&Aura::SpellAuraAddFarSight,//SPELL_AURA_FAR_SIGHT = 76,
		&Aura::SpellAuraMechanicImmunity,//SPELL_AURA_MECHANIC_IMMUNITY = 77,
		&Aura::SpellAuraMounted,//SPELL_AURA_MOUNTED = 78,
		&Aura::SpellAuraModDamagePercDone,//SPELL_AURA_MOD_DAMAGE_PERCENT_DONE = 79,
		&Aura::SpellAuraModPercStat,//SPELL_AURA_MOD_PERCENT_STAT = 80,
		&Aura::SpellAuraSplitDamage,//SPELL_AURA_SPLIT_DAMAGE = 81,
		&Aura::SpellAuraWaterBreathing,//SPELL_AURA_WATER_BREATHING = 82,
		&Aura::SpellAuraModBaseResistance,//SPELL_AURA_MOD_BASE_RESISTANCE = 83,
		&Aura::SpellAuraModRegen,//SPELL_AURA_MOD_REGEN = 84,
		&Aura::SpellAuraModPowerRegen,//SPELL_AURA_MOD_POWER_REGEN = 85,
		&Aura::SpellAuraChannelDeathItem,//SPELL_AURA_CHANNEL_DEATH_ITEM = 86,
		&Aura::SpellAuraModDamagePercTaken,//SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN = 87,
		&Aura::SpellAuraModRegenPercent,//SPELL_AURA_MOD_PERCENT_REGEN = 88,
		&Aura::SpellAuraPeriodicDamagePercent,//SPELL_AURA_PERIODIC_DAMAGE_PERCENT = 89,
		&Aura::SpellAuraModResistChance,//SPELL_AURA_MOD_RESIST_CHANCE = 90,
		&Aura::SpellAuraModDetectRange,//SPELL_AURA_MOD_DETECT_RANGE = 91,
		&Aura::SpellAuraPreventsFleeing,//SPELL_AURA_PREVENTS_FLEEING = 92,
		&Aura::SpellAuraModUnattackable,//SPELL_AURA_MOD_UNATTACKABLE = 93,
		&Aura::SpellAuraInterruptRegen,//SPELL_AURA_INTERRUPT_REGEN = 94,
		&Aura::SpellAuraGhost,//SPELL_AURA_GHOST = 95,
		&Aura::SpellAuraMagnet,//SPELL_AURA_SPELL_MAGNET = 96,
		&Aura::SpellAuraManaShield,//SPELL_AURA_MANA_SHIELD = 97,
		&Aura::SpellAuraSkillTalent,//SPELL_AURA_MOD_SKILL_TALENT = 98,
		&Aura::SpellAuraModAttackPower,//SPELL_AURA_MOD_ATTACK_POWER = 99,
		&Aura::SpellAuraVisible,//SPELL_AURA_AURAS_VISIBLE = 100,
		&Aura::SpellAuraModResistancePCT,//SPELL_AURA_MOD_RESISTANCE_PCT = 101,
		&Aura::SpellAuraModCreatureAttackPower,//SPELL_AURA_MOD_CREATURE_ATTACK_POWER = 102,
		&Aura::SpellAuraModTotalThreat,//SPELL_AURA_MOD_TOTAL_THREAT = 103,
		&Aura::SpellAuraWaterWalk,//SPELL_AURA_WATER_WALK = 104,
		&Aura::SpellAuraFeatherFall,//SPELL_AURA_FEATHER_FALL = 105,
		&Aura::SpellAuraHover,//SPELL_AURA_HOVER = 106,
		&Aura::SpellAuraAddFlatModifier,//SPELL_AURA_ADD_FLAT_MODIFIER = 107,
		&Aura::SpellAuraAddPctMod,//SPELL_AURA_ADD_PCT_MODIFIER = 108,
		&Aura::SpellAuraProcTriggerSpell,//SPELL_AURA_ADD_TARGET_TRIGGER = 109,
		&Aura::SpellAuraModPowerRegPerc,//SPELL_AURA_MOD_POWER_REGEN_PERCENT = 110,
		&Aura::SpellAuraNULL,//SPELL_AURA_ADD_CASTER_HIT_TRIGGER = 111,
		&Aura::SpellAuraOverrideClassScripts,//SPELL_AURA_OVERRIDE_CLASS_SCRIPTS = 112,
		&Aura::SpellAuraModRangedDamageTaken,//SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN = 113,
		&Aura::SpellAuraNULL,//SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT = 114,
		&Aura::SpellAuraModHealing,//SPELL_AURA_MOD_HEALING = 115,
		&Aura::SpellAuraIgnoreRegenInterrupt,//SPELL_AURA_IGNORE_REGEN_INTERRUPT = 116,
		&Aura::SpellAuraModMechanicResistance,//SPELL_AURA_MOD_MECHANIC_RESISTANCE = 117,
		&Aura::SpellAuraModHealingPCT,//SPELL_AURA_MOD_HEALING_PCT = 118,
		&Aura::SpellAuraNULL,//SPELL_AURA_SHARE_PET_TRACKING = 119,//obselete
		&Aura::SpellAuraUntrackable,//SPELL_AURA_UNTRACKABLE = 120,
		&Aura::SpellAuraEmphaty,//SPELL_AURA_EMPATHY = 121,
		&Aura::SpellAuraModOffhandDamagePCT,//SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT = 122,
		&Aura::SpellAuraModPenetration,//SPELL_AURA_MOD_POWER_COST_PCT = 123, --> armor penetration & spell penetration, NOT POWER COST!
		&Aura::SpellAuraModRangedAttackPower,//SPELL_AURA_MOD_RANGED_ATTACK_POWER = 124,
		&Aura::SpellAuraModMeleeDamageTaken,//SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN = 125,
		&Aura::SpellAuraModMeleeDamageTakenPct,//SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT = 126,
		&Aura::SpellAuraRAPAttackerBonus,//SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS = 127,
		&Aura::SpellAuraModPossessPet,//SPELL_AURA_MOD_POSSESS_PET = 128,
		&Aura::SpellAuraModIncreaseSpeedAlways,//SPELL_AURA_MOD_INCREASE_SPEED_ALWAYS = 129,
		&Aura::SpellAuraModIncreaseMountedSpeed,//SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS = 130,
		&Aura::SpellAuraModCreatureRangedAttackPower,//SPELL_AURA_MOD_CREATURE_RANGED_ATTACK_POWER = 131,
		&Aura::SpellAuraModIncreaseEnergyPerc,//SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT = 132,
		&Aura::SpellAuraModIncreaseMaxHealthPerc,//SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT = 133,
		&Aura::SpellAuraModManaRegInterrupt,//SPELL_AURA_MOD_MANA_REGEN_INTERRUPT = 134,
		&Aura::SpellAuraModHealingDone,//SPELL_AURA_MOD_HEALING_DONE = 135,
		&Aura::SpellAuraModHealingDonePct,//SPELL_AURA_MOD_HEALING_DONE_PERCENT = 136,
		&Aura::SpellAuraModTotalStatPerc,//SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE = 137,
		&Aura::SpellAuraModHaste,//SPELL_AURA_MOD_HASTE = 138,
		&Aura::SpellAuraForceReaction,//SPELL_AURA_FORCE_REACTION = 139,
		&Aura::SpellAuraModRangedHaste,//SPELL_AURA_MOD_RANGED_HASTE = 140,
		&Aura::SpellAuraModRangedAmmoHaste,//SPELL_AURA_MOD_RANGED_AMMO_HASTE = 141,
		&Aura::SpellAuraModBaseResistancePerc,//SPELL_AURA_MOD_BASE_RESISTANCE_PCT = 142,
		&Aura::SpellAuraModResistanceExclusive,//SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE = 143,
		&Aura::SpellAuraSafeFall,//SPELL_AURA_SAFE_FALL = 144,
		&Aura::SpellAuraNULL,//SPELL_AURA_CHARISMA = 145,//obselete?
		&Aura::SpellAuraNULL,//SPELL_AURA_PERSUADED = 146,//obselete
		&Aura::SpellAuraCrowdControlImmunity,//SPELL_AURA_ADD_CONTROL_IMMUNITY = 147,//http://wow.allakhazam.com/db/spell.html?wspell=36798
		&Aura::SpellAuraRetainComboPoints,//SPELL_AURA_RETAIN_COMBO_POINTS = 148,
		&Aura::SpellAuraResistPushback,//SPELL_AURA_RESIST_PUSHBACK = 149,//	Resist Pushback //Simply resist spell casting delay
		&Aura::SpellAuraModShieldBlockPCT,//SPELL_AURA_MOD_SHIELD_BLOCK_PCT = 150,//	Mod Shield Absorbed dmg %
		&Aura::SpellAuraTrackStealthed,//SPELL_AURA_TRACK_STEALTHED = 151,//	Track Stealthed
		&Aura::SpellAuraModDetectedRange,//SPELL_AURA_MOD_DETECTED_RANGE = 152,//	Mod Detected Range
		&Aura::SpellAuraSplitDamageFlat,//SPELL_AURA_SPLIT_DAMAGE_FLAT= 153,//	Split Damage Flat
		&Aura::SpellAuraModStealthLevel,//SPELL_AURA_MOD_STEALTH_LEVEL = 154,//	Stealth Level Modifier
		&Aura::SpellAuraModUnderwaterBreathing,//SPELL_AURA_MOD_WATER_BREATHING = 155,//	Mod Water Breathing
		&Aura::SpellAuraModReputationAdjust,//SPELL_AURA_MOD_REPUTATION_ADJUST = 156,//	Mod Reputation Gain
		&Aura::SpellAuraNULL,//SPELL_AURA_PET_DAMAGE_MULTI = 157,//	Mod Pet Damage
		&Aura::SpellAuraModBlockValue,//SPELL_AURA_MOD_SHIELD_BLOCKVALUE = 158//used Apply Aura: Mod Shield Block //http://www.thottbot.com/?sp=25036
		&Aura::SpellAuraNoPVPCredit,//missing = 159 //used Apply Aura: No PVP Credit http://www.thottbot.com/?sp=2479
		&Aura::SpellAuraNULL,//missing = 160 //Apply Aura: Mod Side/Rear PBAE Damage Taken %//used http://www.thottbot.com/?sp=23198
		&Aura::SpellAuraModHealthRegInCombat,//SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT = 161,
		&Aura::SpellAuraPowerBurn,//missing = 162 //used //Apply Aura: Power Burn (Mana) //http://www.thottbot.com/?sp=19659
		&Aura::SpellAuraModCritDmgPhysical,//missing = 163 //Apply Aura: Mod Crit Damage Bonus (Physical)
		&Aura::SpellAuraNULL,//missing = 164 //used //test spell
		&Aura::SpellAuraAPAttackerBonus,//SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS = 165,	// Melee AP Attacker Bonus
		&Aura::SpellAuraModAttackPowerPct,//SPELL_AURA_MOD_ATTACK_POWER_PCT = 166 //used //Apply Aura: Mod Attack Power % // http://www.thottbot.com/?sp=30803
		&Aura::SpellAuraModRangedAttackPowerPct,//missing = 167 //http://www.thottbot.com/s34485
		&Aura::SpellAuraIncreaseDamageTypePCT,//missing = 168 //used //Apply Aura: Increase Damage % *type* //http://www.thottbot.com/?sp=24991
		&Aura::SpellAuraIncreaseCricticalTypePCT,//missing = 169 //used //Apply Aura: Increase Critical % *type* //http://www.thottbot.com/?sp=24293
		&Aura::SpellAuraNULL,//missing = 170 //used //Apply Aura: Detect Amore //http://www.thottbot.com/?sp=26802
		&Aura::SpellAuraIncreasePartySpeed,//missing = 171
		&Aura::SpellAuraIncreaseMovementAndMountedSpeed,//missing = 172 //used //Apply Aura: Increase Movement and Mounted Speed (Non-Stacking) //http://www.thottbot.com/?sp=26022 2e effect
		&Aura::SpellAuraNULL,//missing = 173 // Apply Aura: Allow Chperiodion Spells
		&Aura::SpellAuraIncreaseSpellDamageByAttribute,//missing = 174 //used //Apply Aura: Increase Spell Damage by % Spirit (Spells) //http://www.thottbot.com/?sp=15031
		&Aura::SpellAuraIncreaseHealingByAttribute,//missing = 175 //used //Apply Aura: Increase Spell Healing by % Spirit //http://www.thottbot.com/?sp=15031
		&Aura::SpellAuraSpiritOfRedemption,//missing = 176 //used // Apply Aura: Spirit of Redemption
		&Aura::SpellAuraModCharm,//missing = 177 //used //Apply Aura: Area Charm // http://www.thottbot.com/?sp=26740
		&Aura::SpellAuraNULL,//missing = 178 //Apply Aura: Increase Debuff Resistance
		&Aura::SpellAuraIncreaseAttackerSpellCrit,//SPELL_AURA_INCREASE_ATTACKER_SPELL_CRIT//Apply Aura: Increase Attacker Spell Crit % *type* //http://www.thottbot.com/?sp=12579
		&Aura::SpellAuraModCratureDmgDone,//missing = 180 //used //Apply Aura: Increase Spell Damage *type* //http://www.thottbot.com/?sp=29113
		&Aura::SpellAuraNULL,//missing = 181
		&Aura::SpellAuraIncreaseArmorByPctInt,//missing = 182 //used //Apply Aura: Increase Armor by % of Intellect //http://www.thottbot.com/?sp=28574  SPELL_AURA_INC_ARMOR_BY_PCT_INT
		&Aura::SpellAuraNULL,//missing = 183 //used //Apply Aura: Decrease Critical Threat by % (Spells) //http://www.thottbot.com/?sp=28746
		&Aura::SpellAuraReduceAttackerMHitChance,//184//Apply Aura: Reduces Attacker Chance to Hit with Melee //http://www.thottbot.com/s31678
		&Aura::SpellAuraReduceAttackerRHitChance,//185//Apply Aura: Reduces Attacker Chance to Hit with Ranged //http://www.thottbot.com/?sp=30895
		&Aura::SpellAuraReduceAttackerSHitChance,//186//Apply Aura: Reduces Attacker Chance to Hit with Spells (Spells) //http://www.thottbot.com/?sp=30895
		&Aura::SpellAuraReduceEnemyMCritChance,//missing = 187 //used //Apply Aura: Reduces Attacker Chance to Crit with Melee (Ranged?) //http://www.thottbot.com/?sp=30893
		&Aura::SpellAuraReduceEnemyRCritChance,//missing = 188 //used //Apply Aura: Reduces Attacker Chance to Crit with Ranged (Melee?) //http://www.thottbot.com/?sp=30893
		&Aura::SpellAuraIncreaseRating,//missing = 189 //Apply Aura: Increases Rating
		&Aura::SpellAuraIncreaseRepGainPct,//SPELL_AURA_MOD_FACTION_REPUTATION_GAIN //used // Apply Aura: Increases Reputation Gained by % //http://www.thottbot.com/?sp=30754
		&Aura::SpellAuraLimitSpeed,//missing = 191 //used // noname //http://www.thottbot.com/?sp=29894
		&Aura::SpellAuraMeleeHaste,//192 Apply Aura: Melee Slow %
		&Aura::SpellAuraIncreaseTimeBetweenAttacksPCT,//193 Apply Aura: Increase Time Between Attacks (Melee, Ranged and Spell) by %
		&Aura::SpellAuraNULL,//194 //&Aura::SpellAuraIncreaseSpellDamageByInt,//194 Apply Aura: Increase Spell Damage by % of Intellect (All)
		&Aura::SpellAuraNULL,//195 //&Aura::SpellAuraIncreaseHealingByInt,//195 Apply Aura: Increase Healing by % of Intellect
		&Aura::SpellAuraNULL,//196 Apply Aura: Mod All Weapon Skills (6)
		&Aura::SpellAuraModAttackerCritChance,//197 Apply Aura: Reduce Attacker Critical Hit Chance by %
		&Aura::SpellAuraIncreaseAllWeaponSkill,//198
		&Aura::SpellAuraIncreaseHitRate,//199 Apply Aura: Increases Spell % To Hit (Fire, Nature, Frost)
		&Aura::SpellAuraIncreaseExpGainPct,//200 // Increases experience earned by $s1%.  Lasts $d.
		&Aura::SpellAuraNULL,//201 - root or unroot or add flyight abillity. More like reduce gravity
		&Aura::SpellAuraFinishingMovesCannotBeDodged,//202 // Finishing moves cannot be dodged - 32601, 44452
		&Aura::SpellAuraReduceCritMeleeAttackDmg,//203 Apply Aura: Reduces Attacker Critical Hit Damage with Melee by %
		&Aura::SpellAuraReduceCritRangedAttackDmg,//204 Apply Aura: Reduces Attacker Critical Hit Damage with Ranged by %
		&Aura::SpellAuraNULL,//205 // SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_DAMAGE
		&Aura::SpellAuraEnableFlight,//206 // Take flight on a worn old carpet. - Spell 43343
		&Aura::SpellAuraEnableFlight,//207 set fly
		&Aura::SpellAuraEnableFlightWithUnmountedSpeed,//208
		&Aura::SpellAuraModMountedSpeedPCT,//209  // 
		&Aura::SpellAuraModFlyghtSpeedPCT,//210	// 
		&Aura::SpellAuraIncreaseFlightSpeed,//211
		&Aura::SpellAuraIncreaseRangedAPStatPCT,//SPELL_AURA_MOD_RANGED_ATTACK_POWER_OF_INTELLECT //212 Apply Aura: Increase Ranged Atk Power by % of Intellect
		&Aura::SpellAuraIncreaseRageFromDamageDealtPCT, //213 Apply Aura: Increase Rage from Damage Dealt by %
		&Aura::SpellAuraNULL,//214 // Tamed Pet Passive (DND)
		&Aura::SpellAuraRemoveReagentCost,//215 // arena preparation buff - cancel soul shard requirement?
		&Aura::SpellAuraModCastingSpeed,//216 Increases casting time %, reuse existing handler...
		&Aura::SpellAuraNULL,//217 // not used
		&Aura::SpellAuraNULL,//218 // increases time between ranged attacks
		&Aura::SpellAuraRegenManaStatPCT,//219 SPELL_AURA_REGEN_MANA_STAT_PCT Regenerate mana equal to $s1% of your Intellect every 5 sec, even while casting
		&Aura::SpellAuraRatingBasedOnStat,//220 Increases your rating by %of stat
		&Aura::SpellAuraNULL,//221 Detaunt "Ignores an enemy, forcing the caster to not attack it unless there is no other target nearby. When the effect wears off, the creature will attack the most threatening target."
		&Aura::SpellAuraNULL,//222 // not used
		&Aura::SpellAuraNULL,//223 // used in one spell, cold stare 43593
		&Aura::SpellAuraNULL,//224 // not used
		&Aura::SpellAuraNULL,//225 // Prayer of Mending "Places a spell on the target that heals them for $s1 the next time they take damage.  When the heal occurs, Prayer of Mending jumps to a raid member within $a1 yards.  Jumps up to $n times and lasts $d after each jump.  This spell can only be placed on one target at a time."
		&Aura::SpellAuraPeriodicDummy,//SPELL_AURA_DRINK_NEW 226 // used in brewfest spells, headless hoerseman, Aspect of the Viper
		&Aura::SpellAuraPeriodicTriggerSpellWithValue,//227 Inflicts [SPELL DAMAGE] damage to enemies in a cone in front of the caster. (based on combat range) http://www.thottbot.com/s40938. Mind flay also does periodic damage to target
		&Aura::SpellAuraModStealthDetection,//228 Stealth Detection. http://www.thottbot.com/s34709
		&Aura::SpellAuraNULL,//229 Apply Aura:Reduces the damage taken from area of effect attacks http://www.thottbot.com/s35694
		&Aura::SpellAuraIncreaseMaxHealth,//230 SPELL_AURA_INCREASE_MAX_HEALTH Increase Max Health (commanding shout);
        &Aura::SpellAuraProcTriggerSpell,//231 - proc some action by chance
        &Aura::SpellAuraReduceEffectDuration,//232 // Reduces duration of Magic effects by $s2%.
        &Aura::SpellAuraNULL,//233 // Beer Goggles
        &Aura::SpellAuraReduceEffectDuration,//234 Apply Aura: Reduces Silence or Interrupt effects, Item spell magic http://www.thottbot.com/s42184
		&Aura::SpellAuraNULL,//235 33206 Instantly reduces a friendly target's threat by $44416s1%, reduces all damage taken by $s1% and increases resistance to Dispel mechanics by $s2% for $d.
		&Aura::HandleAuraControlVehicle,                        //236 SPELL_AURA_CONTROL_VEHICLE
		&Aura::SpellAuraModHealingByAP,//237	//increase spell healing by X pct from attack power
		&Aura::SpellAuraModSpellDamageByAP,//238	//increase spell dmg by X pct from attack power
		&Aura::SpellAuraModScale,//239 - mod scale pct
		&Aura::SpellAuraExpertieseModifier,//240 Increase Expertiese X
		&Aura::SpellAuraNULL,//241 - camera control
		&Aura::SpellAuraNULL,//242 - spell damage + healing from intelect
		&Aura::SpellAuraNULL,//243 - mod faction standing
		&Aura::SpellAuraNULL,//244 - language ?
		&Aura::SpellAuraModOffensiveMagicalDurationPCT,//245 - reduce duration of spell mechanics (magical harmfull effects)
		&Aura::SpellAuraNULL,//246 - SMT_DURATION
		&Aura::SpellAuraNULL,//247 - target clone or share health the caster
		&Aura::SpellAuraNULL,//248 - reduce chance for target to dodge
		&Aura::SpellAuraConvertRune,//249 - seems to be for some power conversion but it does not seem to be required anywhere 
		&Aura::SpellAuraAddHealth,//250 - increase max health and health by flat value
		&Aura::SpellAuraNULL,//251
		&Aura::SpellAuraNULL,//252	- SPELL_AURA_MOD_ATTACK_CAST_SPEED_PCT
		&Aura::SpellAuraNULL,//253 - chance on block to block double amount
		&Aura::SpellAuraNULL,//254
		&Aura::SpellAuraModDMGTakenMechanic,//255 - SMT_EFFECT_TARGET	- mod spell value if mechanics match and sometimes spell name
		&Aura::SpellAuraRemoveReagentCost,//256 - mod reagent cost
		&Aura::SpellAuraNULL,//257
		&Aura::SpellAuraNULL,//258
		&Aura::SpellAuraNULL,//259 - add spell effect
		&Aura::SpellAuraNULL,//260 - visual or scripted
		&Aura::SpellAuraNULL,//261 - realm shift (like ghost world)
		&Aura::SpellAuraModIgnoreState,//262 - ignore / set caster / target aura state/stance
		&Aura::SpellAuraModNoCast,//263 - SPELL_AURA_MOD_NOCAST
		&Aura::SpellAuraNULL,//264
		&Aura::SpellAuraNULL,//265
		&Aura::SpellAuraNULL,//266 
		&Aura::SpellAuraAuraSchoolImmunity,//267 - imunity to auras
		&Aura::SpellAuraModAPBasedOnStat,//268 - AP pct based on stat x
		&Aura::SpellAuraNULL,//269	//damage reduction for school
		&Aura::SpellAuraNULL,//270
		&Aura::SpellAuraModDamagePercTaken,//271 target inc school dmg taken by x% / SMT_EFFECT_TARGET
		&Aura::SpellAuraNULL,//272 
		&Aura::SpellAuraNULL,//273 - scripted
		&Aura::SpellAuraNULL,//274
		&Aura::SpellAuraIgnoreShapeshift,//275 - ignore casteraura requirements
		&Aura::SpellAuraNULL,//276
		&Aura::SpellAuraNULL,//277 - SM target count
		&Aura::SpellAuraNULL,//278 - seems to be scripted : visual only + disarm hands (shield + weapon)
		&Aura::SpellAuraNULL,//279 - clone caster by target
		&Aura::SpellAuraModIgnoreArmorForWeapon,//280 attack with item type ignore armor
		&Aura::SpellAuraModHonorGainPCT,//281 honor gained from faction
		&Aura::SpellAuraModIncreaseMaxHealthPerc,//282 base health by x%
		&Aura::SpellAuraNULL,//283
		&Aura::SpellAuraNULL,//284 - seems to be scripted, sometimes it is proc,negate ability,summon
		&Aura::SpellAuraIncreaseAPBasedOnArmor,//285		
		&Aura::SpellAuraNULL,//286 - DOT ability to crit
		&Aura::SpellAuraModDeflectChance,//287
		&Aura::SpellAuraNULL,//288
		&Aura::SpellAuraNULL,//289
		&Aura::SpellAuraNULL,//290
		&Aura::SpellAuraNULL,//291
		&Aura::SpellAuraOpenStableUI,//292 - items that let you use stable pet interface from anywhere
		&Aura::SpellAuraNULL,//293
		&Aura::SpellAuraNULL,//294
		&Aura::SpellAuraNULL,//295
		&Aura::SpellAuraNULL,//296
		&Aura::SpellAuraNULL,//297
		&Aura::SpellAuraNULL,//298
		&Aura::SpellAuraNULL,//299
		&Aura::SpellAuraMirrorDMG,//300
		&Aura::SpellAuraNULL,//301	SPELL_AURA_HEAL_ABSORB 5 spells
		&Aura::SpellAuraNULL,//302
		&Aura::SpellAuraNULL,//303
		&Aura::SpellAuraNULL,//304
		&Aura::SpellAuraNULL,//305
		&Aura::SpellAuraNULL,//306
		&Aura::SpellAuraNULL,//307
		&Aura::SpellAuraNULL,//308
		&Aura::SpellAuraNULL,//309
		&Aura::SpellAuraNULL,//310	SPELL_AURA_MOD_PET_AOE_DAMAGE_AVOIDANCE
		&Aura::SpellAuraNULL,//311
		&Aura::SpellAuraNULL,//312
};

char* SpellAuraNames[TOTAL_SPELL_AURAS] = {
    "NONE",												//   0 None
    "BIND_SIGHT",										//   1 Bind Sight
    "MOD_POSSESS",										//   2 Mod Possess
    "PERIODIC_DAMAGE",									//   3 Periodic Damage
    "DUMMY",											//   4 Script Aura
    "MOD_CONFUSE",										//   5 Mod Confuse
    "MOD_CHARM",										//   6 Mod Charm
    "MOD_FEAR",											//   7 Mod Fear
    "PERIODIC_HEAL",									//   8 Periodic Heal
    "MOD_ATTACKSPEED",									//   9 Mod Attack Speed
    "MOD_THREAT_SCHOOL_PCT",							//  10 Mod Threat
    "MOD_TAUNT",										//  11 Taunt
    "MOD_STUN",											//  12 Stun
    "MOD_DAMAGE_DONE",									//  13 Mod Damage Done
    "MOD_DAMAGE_TAKEN",									//  14 Mod Damage Taken
    "DAMAGE_SHIELD",									//  15 Damage Shield
    "MOD_STEALTH",										//  16 Mod Stealth
    "MOD_DETECT",										//  17 Mod Detect
    "MOD_INVISIBILITY",									//  18 Mod Invisibility
    "MOD_INVISIBILITY_DETECTION",						//  19 Mod Invisibility Detection
    "MOD_TOTAL_HEALTH_REGEN_PCT",						//  20
    "MOD_TOTAL_MANA_REGEN_PCT",							//  21
    "MOD_RESISTANCE",									//  22 Mod Resistance
    "PERIODIC_TRIGGER_SPELL",							//  23 Periodic Trigger
    "PERIODIC_ENERGIZE",								//  24 Periodic Energize
    "MOD_PACIFY",										//  25 Pacify
    "MOD_ROOT",											//  26 Root
    "MOD_SILENCE",										//  27 Silence
    "REFLECT_SPELLS",									//  28 Reflect Spells %
    "MOD_STAT",											//  29 Mod Stat
    "MOD_SKILL",										//  30 Mod Skill
    "MOD_INCREASE_SPEED",								//  31 Mod Speed
    "MOD_INCREASE_MOUNTED_SPEED",						//  32 Mod Speed Mounted
    "MOD_DECREASE_SPEED",								//  33 Mod Speed Slow
    "MOD_INCREASE_HEALTH",								//  34 Mod Increase Health
    "MOD_INCREASE_ENERGY",								//  35 Mod Increase Energy
    "MOD_SHAPESHIFT",									//  36 Shapeshift
    "EFFECT_IMMUNITY",									//  37 Immune Effect
    "STATE_IMMUNITY",									//  38 Immune State
    "SCHOOL_IMMUNITY",									//  39 Immune School    
    "DAMAGE_IMMUNITY",									//  40 Immune Damage
    "DISPEL_IMMUNITY",									//  41 Immune Dispel Type
    "PROC_TRIGGER_SPELL",								//  42 Proc Trigger Spell
    "PROC_TRIGGER_DAMAGE",								//  43 Proc Trigger Damage
    "TRACK_CREATURES",									//  44 Track Creatures
    "TRACK_RESOURCES",									//  45 Track Resources
    "MOD_PARRY_SKILL",									//  46 Mod Parry Skill
    "MOD_PARRY_PERCENT",								//  47 Mod Parry Percent
    "MOD_DODGE_SKILL",									//  48 Mod Dodge Skill
    "MOD_DODGE_PERCENT",								//  49 Mod Dodge Percent  
    "MOD_BLOCK_SKILL",									//  50 Mod Block Skill
    "MOD_BLOCK_PERCENT",								//  51 Mod Block Percent
    "MOD_CRIT_PERCENT",									//  52 Mod Crit Percent
    "PERIODIC_LEECH",									//  53 Periodic Leech
    "MOD_HIT_CHANCE",									//  54 Mod Hit Chance
    "MOD_SPELL_HIT_CHANCE",								//  55 Mod Spell Hit Chance
    "TRANSFORM",										//  56 Transform
    "MOD_SPELL_CRIT_CHANCE",							//  57 Mod Spell Crit Chance
    "MOD_INCREASE_SWIM_SPEED",							//  58 Mod Speed Swim
    "MOD_DAMAGE_DONE_CREATURE",							//  59 Mod Creature Dmg Done   
    "MOD_PACIFY_SILENCE",								//  60 Pacify & Silence
    "MOD_SCALE",										//  61 Mod Scale
    "PERIODIC_HEALTH_FUNNEL",							//  62 Periodic Health Funnel
    "PERIODIC_MANA_FUNNEL",								//  63 Periodic Mana Funnel
    "PERIODIC_MANA_LEECH",								//  64 Periodic Mana Leech
    "MOD_CASTING_SPEED",								//  65 Haste - Spells
    "FEIGN_DEATH",										//  66 Feign Death
    "MOD_DISARM",										//  67 Disarm
    "MOD_STALKED",										//  68 Mod Stalked
    "SCHOOL_ABSORB",									//  69 School Absorb    
    "EXTRA_ATTACKS",									//  70 Extra Attacks
    "MOD_SPELL_CRIT_CHANCE_SCHOOL",						//  71 Mod School Spell Crit Chance
    "MOD_POWER_COST",									//  72 Mod Power Cost
    "MOD_POWER_COST_SCHOOL",							//  73 Mod School Power Cost
    "REFLECT_SPELLS_SCHOOL",							//  74 Reflect School Spells %
    "MOD_LANGUAGE",										//  75 Mod Language
    "FAR_SIGHT",										//  76 Far Sight
    "MECHANIC_IMMUNITY",								//  77 Immune Mechanic
    "MOUNTED",											//  78 Mounted
    "MOD_DAMAGE_PERCENT_DONE",							//  79 Mod Dmg %   
    "MOD_PERCENT_STAT",									//  80 Mod Stat %
    "SPLIT_DAMAGE",										//  81 Split Damage
    "WATER_BREATHING",									//  82 Water Breathing
    "MOD_BASE_RESISTANCE",								//  83 Mod Base Resistance
    "MOD_REGEN",										//  84 Mod Health Regen
    "MOD_POWER_REGEN",									//  85 Mod Power Regen
    "CHANNEL_DEATH_ITEM",								//  86 Create Death Item
    "MOD_DAMAGE_PERCENT_TAKEN",							//  87 Mod Dmg % Taken
    "MOD_PERCENT_REGEN",								//  88 Mod Health Regen Percent
    "PERIODIC_DAMAGE_PERCENT",							//  89 Periodic Damage Percent   
    "MOD_RESIST_CHANCE",								//  90 Mod Resist Chance
    "MOD_DETECT_RANGE",									//  91 Mod Detect Range
    "PREVENTS_FLEEING",									//  92 Prevent Fleeing
    "MOD_UNATTACKABLE",									//  93 Mod Uninteractible
    "INTERRUPT_REGEN",									//  94 Interrupt Regen
    "GHOST",											//  95 Ghost
    "SPELL_MAGNET",										//  96 Spell Magnet
    "MANA_SHIELD",										//  97 Mana Shield
    "MOD_SKILL_TALENT",									//  98 Mod Skill Talent
    "MOD_ATTACK_POWER",									//  99 Mod Attack Power
    "AURAS_VISIBLE",									// 100 Auras Visible
    "MOD_RESISTANCE_PCT",								// 101 Mod Resistance %
    "MOD_CREATURE_ATTACK_POWER",						// 102 Mod Creature Attack Power
    "MOD_TOTAL_THREAT",									// 103 Mod Total Threat (Fade)
    "WATER_WALK",										// 104 Water Walk
    "FEATHER_FALL",										// 105 Feather Fall
    "HOVER",											// 106 Hover
    "ADD_FLAT_MODIFIER",								// 107 Add Flat Modifier
    "ADD_PCT_MODIFIER",									// 108 Add % Modifier
    "ADD_TARGET_TRIGGER",								// 109 Add Class Target Trigger    
    "MOD_POWER_REGEN_PERCENT",							// 110 Mod Power Regen %
    "ADD_CASTER_HIT_TRIGGER",							// 111 Add Class Caster Hit Trigger
    "OVERRIDE_CLASS_SCRIPTS",							// 112 Override Class Scripts
    "MOD_RANGED_DAMAGE_TAKEN",							// 113 Mod Ranged Dmg Taken
    "MOD_RANGED_DAMAGE_TAKEN_PCT",						// 114 Mod Ranged % Dmg Taken
    "MOD_HEALING",										// 115 Mod Healing
    "IGNORE_REGEN_INTERRUPT",							// 116 Regen During Combat
    "MOD_MECHANIC_RESISTANCE",							// 117 Mod Mechanic Resistance
    "MOD_HEALING_PCT",									// 118 Mod Healing %
    "SHARE_PET_TRACKING",								// 119 Share Pet Tracking    
    "UNTRACKABLE",										// 120 Untrackable
    "EMPATHY",											// 121 Empathy (Lore, whatever)
    "MOD_OFFHAND_DAMAGE_PCT",							// 122 Mod Offhand Dmg %
    "MOD_POWER_COST_PCT",								// 123 Mod Power Cost % --> armor penetration & spell penetration
    "MOD_RANGED_ATTACK_POWER",							// 124 Mod Ranged Attack Power
    "MOD_MELEE_DAMAGE_TAKEN",							// 125 Mod Melee Dmg Taken
    "MOD_MELEE_DAMAGE_TAKEN_PCT",						// 126 Mod Melee % Dmg Taken
    "RANGED_ATTACK_POWER_ATTACKER_BONUS",				// 127 Rngd Atk Pwr Attckr Bonus
    "MOD_POSSESS_PET",									// 128 Mod Possess Pet
    "MOD_INCREASE_SPEED_ALWAYS",						// 129 Mod Speed Always   
    "MOD_MOUNTED_SPEED_ALWAYS",							// 130 Mod Mounted Speed Always
    "MOD_CREATURE_RANGED_ATTACK_POWER",					// 131 Mod Creature Ranged Attack Power
    "MOD_INCREASE_ENERGY_PERCENT",						// 132 Mod Increase Energy %
    "MOD_INCREASE_HEALTH_PERCENT",						// 133 Mod Max Health %
    "MOD_MANA_REGEN_INTERRUPT",							// 134 Mod Interrupted Mana Regen
    "MOD_HEALING_DONE",									// 135 Mod Healing Done
    "MOD_HEALING_DONE_PERCENT",							// 136 Mod Healing Done %
    "MOD_TOTAL_STAT_PERCENTAGE",						// 137 Mod Total Stat %
    "MOD_HASTE",										// 138 Haste - Melee
    "FORCE_REACTION",									// 139 Force Reaction    
    "MOD_RANGED_HASTE",									// 140 Haste - Ranged
    "MOD_RANGED_AMMO_HASTE",							// 141 Haste - Ranged (Ammo Only)
    "MOD_BASE_RESISTANCE_PCT",							// 142 Mod Base Resistance %
    "MOD_RESISTANCE_EXCLUSIVE",							// 143 Mod Resistance Exclusive
    "SAFE_FALL",										// 144 Safe Fall
    "CHARISMA",											// 145 Charisma
    "PERSUADED",										// 146 Persuaded
    "SPELL_AURA_ADD_CONTROL_IMMUNITY",					// 147 Add Creature Immunity
    "RETAIN_COMBO_POINTS",								// 148 Retain Combo Points
    "RESIST_PUSHBACK",									// 149 Resist Pushback
    "MOD_SHIELD_BLOCK_PCT",								// 150 Mod Shield Block %
    "TRACK_STEALTHED",									// 151 Track Stealthed
    "MOD_DETECTED_RANGE",								// 152 Mod Detected Range
    "SPLIT_DAMAGE_FLAT",								// 153 Split Damage Flat
    "MOD_STEALTH_LEVEL",								// 154 Stealth Level Modifier
    "MOD_WATER_BREATHING",								// 155 Mod Water Breathing
    "MOD_REPUTATION_ADJUST",							// 156 Mod Reputation Gain
    "PET_DAMAGE_MULTI",									// 157 Mod Pet Damage
    "MOD_SHIELD_BLOCK",									// 158 Mod Shield Block
    "NO_PVP_CREDIT",									// 159 No PVP Credit 
    "MOD_SIDE_REAR_PDAE_DAMAGE_TAKEN",					// 160 Mod Side/Rear PBAE Damage Taken 
    "MOD_HEALTH_REGEN_IN_COMBAT",						// 161 Mod Health Regen In Combat
    "POWER_BURN",										// 162 Power Burn 
    "MOD_CRIT_DAMAGE_BONUS_MELEE",						// 163 Mod Critical Damage Bonus (Physical)
	"",													// 164
    "MELEE_ATTACK_POWER_ATTACKER_BONUS",				// 165 Melee AP Attacker Bonus
    "MOD_ATTACK_POWER_PCT",								// 166 Mod Attack Power
    "MOD_RANGED_ATTACK_POWER_PCT",						// 167 Mod Ranged Attack Power %
    "INCREASE_DAMAGE",									// 168 Increase Damage Type
    "INCREASE_CRITICAL",								// 169 Increase Critical Type
    "DETECT_AMORE",										// 170 Detect Amore
	"",													// 171
    "INCREASE_MOVEMENT_AND_MOUNTED_SPEED",				// 172 Increase Movement and Mounted Speed (Non-Stacking)
	"",													// 173
    "INCREASE_SPELL_DAMAGE_BY_ATTRIBUTE",				// 174 Increase Spell Damage by % status
    "INCREASE_SPELL_HEALING_BY_ATTRIBUTE",				// 175 Increase Spell Healing by % status
    "SPIRIT_OF_REDEMPTION",								// 176 Spirit of Redemption Auras
    "AREA_CHARM",										// 177 Area Charm 
	"",													// 178
    "INCREASE_ATTACKER_SPELL_CRIT",						// 179 Increase Attacker Spell Crit Type
    "INCREASE_SPELL_DAMAGE_VS_TYPE",					// 180 Increase Spell Damage Type
	"",													// 181
    "INCREASE_ARMOR_BASED_ON_INTELLECT_PCT",			// 182 Increase Armor based on Intellect
    "DECREASE_CRIT_THREAT",								// 183 Decrease Critical Threat by
    "DECREASE_ATTACKER_CHANCE_TO_HIT_MELEE",			// 184 Reduces Attacker Chance to Hit with Melee
    "DECREASE_ATTACKER_CHANGE_TO_HIT_RANGED",			// 185 Reduces Attacker Chance to Hit with Ranged 
    "DECREASE_ATTACKER_CHANGE_TO_HIT_SPELLS",			// 186 Reduces Attacker Chance to Hit with Spells
    "DECREASE_ATTACKER_CHANGE_TO_CRIT_MELEE",			// 187 Reduces Attacker Chance to Crit with Melee (Ranged?)
    "DECREASE_ATTACKER_CHANGE_TO_CRIT_RANGED",			// 188 Reduces Attacker Chance to Crit with Ranged (Melee?)
	"INCREASE_RATING",									// 189
    "INCREASE_REPUTATION",								// 190 Increases reputation from killed creatures
    "SPEED_LIMIT",										// 191 speed limit
    "MELEE_SLOW_PCT",									// 192
    "INCREASE_TIME_BETWEEN_ATTACKS",					// 193
    "INREASE_SPELL_DAMAGE_PCT_OF_INTELLECT",			// 194 NOT USED ANYMORE - 174 used instead
    "IGNORE_ABSORB_FOR_SPELL",							// 195 
    "MOD_ALL_WEAPON_SKILLS",							// 196
    "REDUCE_ATTACKER_CRICTICAL_HIT_CHANCE_PCT",			// 197
	"",													// 198
    "INCREASE_SPELL_HIT_PCT",							// 199
	"SPELL_AURA_MOD_XP_AND_REP_PCT",					// 200
    "CANNOT_BE_DODGED",									// 201
	"FINISHING_MOVES_CANNOT_BE_DODGED",					// 202
    "REDUCE_ATTACKER_CRICTICAL_HIT_DAMAGE_MELEE_PCT",	// 203
    "REDUCE_ATTACKER_CRICTICAL_HIT_DAMAGE_RANGED_PCT",	// 204
	"",													// 205
	"",													// 206
	"",													// 207
	"",													// 208
	"SPELL_AURA_MOD_MOUNTED_SPEED_PCT",					// 209
	"SPELL_AURA_MOD_FLIGHT_SPEED_PCT",					// 210
	"",													// 211
    "INCREASE_RANGED_ATTACK_POWER_PCT_OF_INTELLECT",	// 212
    "INCREASE_RAGE_FROM_DAMAGE_DEALT_PCT",				// 213
	"",													// 214
	"",													// 215
    "INCREASE_CASTING_TIME_PCT",						// 216
	"",													// 217
	"",													// 218
    "REGEN_MANA_STAT_PCT",								// 219
    "HEALING_STAT_PCT",									// 220
	"",													// 221
	"",													// 222
	"",													// 223
	"",													// 224
	"",													// 225
	"PERIODIC_DUMMY",									// 226
	"",													// 227
	"",													// 228
	"",													// 229
    "INCREASE_MAX_HEALTH",								// 230 Used by Commanding Shout
	"SPELL_AURA_PROC_TRIGGER_SPELL2",					// 231
	"",													// 232
	"",													// 233
	"",													// 234
	"",													// 235
	"CONTROL_VEHICLE",									// 236
	"",													// 237
	"",													// 238
	"MOD_SCALE_PCT",									// 239
	"MODIFY_AXE_SKILL",									// 240
	"241",												// 241
    "MOD_SPELL_DAMAGE_FROM_HEALING",					// 242
    "SPELL_AURA_MOD_FACTION",							// 243
    "244",												// 244
    "MOD_DURATION_OF_MAGIC_EFFECTS",					// 245
    "246",												// 246
    "247",												// 247
    "MOD_COMBAT_RESULT_CHANCE",							// 248
    "249",												// 249
    "MOD_INCREASE_HEALTH_2",							// 250
    "MOD_ENEMY_DODGE",									// 251
    "SPELL_AURA_MOD_ATTACK_CAST_SPEED_PCT",				// 252
    "253",												// 253
    "254",												// 254
    "SPELL_AURA_MOD_DMG_TAKEN_MECHANIC_FLAT",			// 255
    "SPELL_AURA_MOD_REAGENT_COST2",						// 256
    "257",												// 257
    "258",												// 258
    "259",												// 259
	"SPELL_AURA_SCREEN_EFFECT",							// 260
	"SPELL_AURA_PHASE ",								// 261
	"262",												// 262
	"SPELL_AURA_MOD_NOCAST",							// 263
	"264",												// 264
	"265",												// 265
	"266",												// 266
	"SPELL_AURA_MOD_SCHOOL_IMMUNITY",					// 267
	"SPELL_AURA_MOD_AP_BY_STAT",						// 268
	"269",												// 269
	"270",												// 270
	"SPELL_AURA_MOD_DAMAGE_TAKEN_PCT",					// 271
	"272",												// 272
	"273",												// 273
	"274",												// 274
	"SPELL_AURA_MOD_IGNORE_SHAPESHIFT",					// 275
	"276",												// 276
	"277",												// 277
	"278",												// 278
	"279",												// 279
	"SPELL_AURA_MOD_IGNOREARMOR_FOR_WEAPON",			// 280
	"SPELL_AURA_MOD_HONOR_GAIN_PCT",					// 281
	"SPELL_AURA_MOD_HEALTHPCT",							// 282
	"283",												// 283
	"284",												// 284
	"SPELL_AURA_MOD_ATTACK_POWER_BY_ARMOR",				// 285
	"286",												// 286
	"SPELL_AURA_MOD_DEFLECT",							// 287
	"288",												// 288
	"289",												// 289
	"290",												// 290
	"291",												// 291
	"292",												// 292
	"293",												// 293
	"294",												// 294
	"295",												// 295
	"296",												// 296
	"297",												// 297
	"298",												// 298
	"299",												// 299
	"SPELL_AURA_MOD_MIRROR_DMG",						// 300
};


/*
ARCEMU_INLINE void ApplyFloatSM(float ** m,float v,uint32 mask, float def)
{
	if(*m == 0)
	{
		*m = new float[SPELL_GROUPS];

		for(uint32 x=0;x<SPELL_GROUPS;x++)
		{
			(*m)[x] = def;
			if((1<<x) & mask)
				(*m)[x]+=v;
		}
	}
	else
	{
		for(uint32 x=0;x<SPELL_GROUPS;x++)
		{
			if((1<<x) & mask)
				(*m)[x]+=v;
		}
	}
}*/
/*
ARCEMU_INLINE void ApplyFloatPSM(float ** m,int32 v,uint32 mask, float def)
{
	if(*m == 0)
	{
		*m = new float[SPELL_GROUPS];

		for(uint32 x=0;x<SPELL_GROUPS;x++)
		{
			(*m)[x] = def;
			if((1<<x) & mask)
				(*m)[x]+=((float)v)/100.0f;
		}
	}
	else
	{
		for(uint32 x=0;x<SPELL_GROUPS;x++)
		{
			if((1<<x) & mask)
				(*m)[x]+=((float)v)/100.0f;
		}
	}
}*/

Unit* Aura::GetUnitCaster()
{
	//!!!! AMG fix this. We are removed while we are handling aura !!! This is mem corruption
	if( !m_target )
		return NULL;

	if( m_casterGuid == m_target->GetGUID() )
		return m_target;
	if( m_target->GetMapMgr() )
		return m_target->GetMapMgr()->GetUnit( m_casterGuid );
	else
		return NULL;
}

Object* Aura::GetCaster()
{
	if( m_casterGuid == m_target->GetGUID() )
	{ 
		return m_target;
	}
	if( m_target->GetMapMgr() )
	{ 
		return m_target->GetMapMgr()->_GetObject( m_casterGuid );
	}
	else
		return NULL;
}

Aura::Aura()
{
	m_bufferPoolId = OBJECT_WAS_ALLOCATED_STANDARD_WAY;
}

void Aura::Init( SpellEntry* proto, int32 duration, Object* caster, Unit* target, Item* i_caster )
{
	m_spellId = proto->Id;
	m_castInDuel = false;
	m_spellProto = proto;
	m_duration = duration;
	m_positive = 0; //we suppose spell will have positive impact on target
	m_deleted = 0;
	m_ignoreunapply = false;
	m_casterGuid = caster->GetGUID();
	m_target = target;

	if( m_target && m_target->GetTypeId() == TYPEID_PLAYER )
		p_target = SafePlayerCast( m_target );
	else
		p_target = NULL;

	if ( i_caster != NULL && i_caster->GetProto() )
		m_castedItemId = i_caster->GetProto()->ItemId;
	else
		m_castedItemId = 0;

	// Modifies current aura duration based on its mechanic type
	if(m_target && m_target->IsPlayer())
	{
		int32 DurationModifier = 0;
		if( proto->MechanicsType < MECHANIC_TOTAL )
			DurationModifier = SafePlayerCast( m_target )->MechanicDurationPctMod[ proto->MechanicsType ];
		if(DurationModifier < - 100)
			DurationModifier = -100; // Can't reduce by more than 100%
		SetDuration((GetDuration()*(100+DurationModifier))/100);
	}

	//SetCasterFaction(caster->_getFaction());

	//m_auraSlot = 0;
	mod = NULL;	//do not keep refenerence to previous usage of this aura. Modlist should be static but it seems something is corrupting it
	m_modcount = 0;
	m_dynamicValue = 0;
	m_areaAura = false;

	if( m_spellProto->c_is_flags & SPELL_FLAG_IS_FORCEDDEBUFF )
		SetNegative( 100 );
	else if( m_spellProto->c_is_flags & SPELL_FLAG_IS_FORCEDBUFF )
		SetPositive( 100 );
	if( caster->IsUnit() )
	{
		if( m_spellProto->BGR_one_buff_from_caster_on_1target > 0 && caster->IsPlayer() )
		{
			( SafePlayerCast(caster) )->RemoveSpellTargets( m_spellProto->BGR_one_buff_from_caster_on_1target, target);
			( SafePlayerCast(caster) )->SetSpellTargetType( m_spellProto->BGR_one_buff_from_caster_on_1target, target);
		}
		if( m_spellProto->BGR_one_buff_from_caster_on_self != 0 )
			SafeUnitCast(caster)->RemoveAllAuraFromSelfType2( m_spellProto->BGR_one_buff_from_caster_on_self, m_spellProto->NameHash );

		if( isAttackable( caster, target ) )
		{
			SetNegative();
			/*if(caster->IsPlayer())
			{
				SafePlayerCast( caster )->CombatModeDelay = COMBAT_DECAY_TIME;
			}
			else if(caster->IsPet())
			{
				Player* p = SafePetCast( caster )->GetPetOwner();
				if(p)
					p->CombatModeDelay = COMBAT_DECAY_TIME;
			}*/
		}
		else
			SetPositive();

		if( p_target && p_target->DuelingWith == caster )
			m_castInDuel = true;
	}

	if( !IsPassive() )
		timeleft = ( uint32 )UNIXTIME;

	m_visualSlot = AURA_INVALID_VISUAL_SLOT;
	pSpellId = 0;
//	periodic_target = 0;
	//sLog.outDetail("Aura::Constructor %u (%s) from %u.", m_spellProto->Id, m_spellProto->Name, m_target->GetLowGUID());
	m_auraSlot = AURA_IN_PROCESS_TO_ADD;
	m_interrupted = -1;
	m_flags = 0;
	//fixed_amount = 0;//used only for percent values to be able to recover value correctly.No need to init this if we are not using it
    uint32 flag = 0;
    if( m_spellProto->MechanicsType == MECHANIC_ENRAGED )
		flag |= AURASTATE_FLAG_ENRAGE;
    else if( m_spellProto->MechanicsType == MECHANIC_BLEEDING )
		flag |= AURASTATE_FLAG_BLEED;
    if( m_spellProto->BGR_one_buff_on_target & SPELL_TYPE_SEAL )
        flag |= AURASTATE_FLAG_JUDGEMENT;
//    m_target->RemoveFlag( UNIT_FIELD_AURASTATE, flag );
    m_target->SetFlag( UNIT_FIELD_AURASTATE, flag );
}

void Aura::Virtual_Constructor()
{
	EventableObject::Virtual_Constructor();
	m_holder = NULL;	//clear out event holder. There is a bug that if player logoud out in an instance and item was attached to it then item get invalid pointer to a holder
}

Aura::~Aura()
{
	sEventMgr.RemoveEvents( this );
	if( m_bufferPoolId != OBJECT_WAS_ALLOCATED_STANDARD_WAY )
		ASSERT( false ); //we are deleting a pooled object. This leads to mem corruptions
}

void Aura::Virtual_Destructor()
{
	//forget about context and events to avoid memory leaks
	EventableObject::Virtual_Destructor();
	//this should do nothing now
	sEventMgr.RemoveEvents( this );
}

void Aura::Remove()
{
	//required to remove events always since there is a chance that mod 1 removes aura while mod 2 applies a periodic spell on the deleted aura
	sEventMgr.RemoveEvents( this );

	//just lol, this should be properly solved ? 
	//Zack : changing from bool to numeric to see if there is a thread concurency issue here
	{
		if( m_deleted != 0 )
		{ 
			return;
		}
		m_deleted++;
	}

	//in case i forget to remove this then it is only for temp debug :P
//	CStackWalker sw; 
//	if( GetSpellProto()->Id == 49005 )
//		sw.ShowCallstack(); 

	//we already deleted all events so this should do nothing in theory
	sEventMgr.RemoveEvents( this );

	//first thing to do is to remove ourself from unit check list
	// this increases the chance that on removing aura we do not trigger event to double delete us
	if( m_auraSlot != AURA_IN_PROCESS_TO_ADD )
	{
		//just a wtf check : object does not have the aura but aura thinks he still belongs to the object. This should never happen
		if( m_target->m_auras[ m_auraSlot ] == this )
			m_target->m_auras[ m_auraSlot ] = NULL;
		else
		{
			bool found_on_target = false;
			uint32 i;
			for(i=FIRST_AURA_SLOT;i<MAX_PASSIVE_AURAS;i++)
				if( m_target->m_auras[ i ] == this )
				{
					m_target->m_auras[ i ] = NULL;
					found_on_target = true;
				}
			if( found_on_target == false )
			{
				printf("Removing aura from target but target does not have the aura ! %d - %s - %d\n",m_spellProto->Id,m_spellProto->Name,m_auraSlot);
//				ASSERT( false );
				return;
			}
			else
			{
				printf("Removing aura from target from incorrect slot ! %d - %s - %d - %d\n",m_spellProto->Id,m_spellProto->Name,m_auraSlot,i);
			}
		}
/*		if( m_auraSlot + 1 == m_target->m_auras_pos_size )
			m_target->m_auras_pos_size--;
		else if( m_auraSlot + 1 == m_target->m_auras_neg_size )
			m_target->m_auras_neg_size--;
		else if( m_auraSlot + 1 == m_target->m_auras_pas_size )
			m_target->m_auras_pas_size--;*/
		m_auraSlot = AURA_IN_PROCESS_TO_ADD;
	}

	if( !IsPassive() || ( IsPassive() && m_spellProto->AttributesEx & 1024 ) )
//		RemoveAuraVisual();
		m_target->ModVisualAuraStackCount( this, -1 );

	ApplyModifiers( false );

	for( uint32 x = 0; x < 3; x++ )
	{
		if( !m_spellProto->Effect[x] )
			continue;

		if( m_spellProto->Effect[x] == SPELL_EFFECT_TRIGGER_SPELL )
		{
			// Im not sure about this! FIXME!!
			SpellEntry *tsp = dbcSpell.LookupEntryForced( GetSpellProto()->EffectTriggerSpell[x] );
			if ( tsp && tsp->DurationIndex < m_spellProto->DurationIndex )
				m_target->RemoveAura( GetSpellProto()->EffectTriggerSpell[x] );
		}
		else if( (m_spellProto->Effect[x] == SPELL_EFFECT_APPLY_AREA_AURA || m_spellProto->Effect[x] == SPELL_EFFECT_APPLY_AREA_AURA2) && m_casterGuid == m_target->GetGUID())
		{
			RemoveAA();	//need to call this after marking this aura in process of being removed to avoid loop calls !
		}
	}

	if( m_spellProto->procCharges > 0 
//		&& m_spellProto->proc_interval == 0 
		)
	{
		std::map< uint32, struct SpellCharge >::iterator iter;
		iter = m_target->m_chargeSpells.find( GetSpellId() );
		if( iter != m_target->m_chargeSpells.end() )
			if( iter->second.count >= 1 )
				--iter->second.count;	//deletion will be made only in handleproc function
	}

	// reset diminishing return timer if needed
	//::UnapplyDiminishingReturnTimer( m_target, m_spellProto );

	// remove attacker
	Unit* caster = GetUnitCaster();
	if( caster != NULL)
	{
		if( caster != m_target )
		{
			caster->CombatStatus.RemoveAttackTarget( m_target );
			m_target->CombatStatus.RemoveAttacker( caster, caster->GetGUID() );
		}

		if( m_spellProto->BGR_one_buff_from_caster_on_1target != 0 && m_target->IsPlayer() )
			SafePlayerCast( m_target )->RemoveSpellIndexReferences( m_spellProto->BGR_one_buff_from_caster_on_1target );

		/**********************Cooldown**************************
		* this is only needed for some spells
		* for now only spells that have:
		* (m_spellInfo->Attributes == 0x2050000) && !(m_spellInfo->AttributesEx) ||
		* m_spellProto->Attributes == 0x2040100
		* are handled. Its possible there are more spells like this
		*************************************************************/

		if( caster->IsPlayer() && caster->IsInWorld() )
		{
/*			if( m_spellProto->c_is_flags & SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE )
			{
				packetSMSG_COOLDOWN_EVENT data;
				data.spellid = m_spellProto->Id;
				data.guid = caster->GetGUID();
//				caster->OutPacketToSet( SMSG_COOLDOWN_EVENT, sizeof( packetSMSG_COOLDOWN_EVENT ), &data, true );
				if( caster->IsPlayer() && SafePlayerCast( caster )->GetSession() )
					SafePlayerCast( caster )->GetSession()->OutPacket( SMSG_COOLDOWN_EVENT, sizeof( packetSMSG_COOLDOWN_EVENT ), &data );
			}*/

			//check for farsight removal
			int j;
			for( j = 0; j < 3; ++j )
				if( m_spellProto->Effect[j] == SPELL_EFFECT_ADD_FARSIGHT )
				{
					caster->SetUInt64Value(PLAYER_FARSIGHT, 0);
					break;
				}
		}

		//warning !!! this might create a lag or loop. Casting 60 auras a second by player is very much possible and it might lag
		//only proc after we removed all auras of this spell
		if( m_modcount
//			&& mod->i == mod->total_mods 
			)
		{
			if( caster != m_target )
			{
				m_target->HandleProc( PROC_ON_AURA_REMOVE, caster, m_spellProto, m_modList[0].m_amount );
				caster->HandleProc( PROC_ON_AURA_REMOVE, m_target, m_spellProto, m_modList[0].m_amount );
			}
			else
				caster->HandleProc( PROC_ON_AURA_REMOVE, caster, m_spellProto, m_modList[0].m_amount );
		}
		//only used by wyvern sting ?
		if( m_spellProto->aura_remove_cast )
			caster->CastSpell( m_target, m_spellProto->aura_remove_cast, true );
	}
	else
		m_target->CombatStatus.RemoveAttacker( NULL, m_casterGuid );

	if( m_spellProto->MechanicsType == MECHANIC_ENRAGED )
		m_target->RemoveFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_ENRAGE );
	else if( m_spellProto->MechanicsType == MECHANIC_BLEEDING )
		m_target->RemoveFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_BLEED );
    if( m_spellProto->BGR_one_buff_on_target & SPELL_TYPE_SEAL )
		m_target->SetFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_JUDGEMENT );

	//if this spell had a linked cast then also remove that one :P
	if( GetSpellProto()->chained_cast )
		m_target->RemoveAuraPos( GetSpellProto()->chained_cast->Id, m_casterGuid, true );
	//remove spell "extensions". Note that food eat buff is a periodical trigger spell that should not be removed
	if( ( GetSpellProto()->Effect[0] == SPELL_EFFECT_TRIGGER_SPELL || GetSpellProto()->Effect[0] == SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE ) && GetSpellProto()->EffectTriggerSpell[0] )
		m_target->RemoveAuraPos( GetSpellProto()->EffectTriggerSpell[0], m_casterGuid, true );
	if( ( GetSpellProto()->Effect[1] == SPELL_EFFECT_TRIGGER_SPELL || GetSpellProto()->Effect[1] == SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE ) && GetSpellProto()->EffectTriggerSpell[1] )
		m_target->RemoveAuraPos( GetSpellProto()->EffectTriggerSpell[1], m_casterGuid, true );
	if( ( GetSpellProto()->Effect[2] == SPELL_EFFECT_TRIGGER_SPELL || GetSpellProto()->Effect[2] == SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE ) && GetSpellProto()->EffectTriggerSpell[2] )
		m_target->RemoveAuraPos( GetSpellProto()->EffectTriggerSpell[2], m_casterGuid, true );

	mod = NULL;	//this might cause crashes. X spell has aura that casts spell Y that removes X. When X returns control he has invalid pointers
	m_target = NULL;
	p_target = NULL;
	m_spellProto = NULL;
	m_casterGuid = 0;

	//maybe some idiot coder added new events in the process of remove ? Purge the evil !
	sEventMgr.RemoveEvents( this );

	AuraPool.PooledDelete( this ); // suicide xD	leaking this shit out
}

void Aura::AddMod( uint32 t, int32 a, uint32 miscValue, uint32 i )
{
	//this is fix, when u have the same unit in target list several times
	//for(uint32 x=0;x<m_modcount;x++)
	//	if(m_modList[x].i==i)return;

	/*if(m_modList[0].m_type == t ||
		m_modList[1].m_type == t ||
		m_modList[2].m_type == t)
		return; // dont duplicate mods // some spells apply duplicate mods, like some seals*/

	if( m_modcount >= 3 )
	{
		//this might happen when mob is dead and we keep adding auras to temp list
		sLog.outString("Tried to add >3 (%u) mods to spellid %u [%u:%u, %u:%u, %u:%u]", m_modcount+1, this->m_spellProto->Id, m_modList[0].m_type, m_modList[0].m_amount, m_modList[1].m_type, m_modList[1].m_amount, m_modList[2].m_type, m_modList[2].m_amount);
		return;
	}
	m_modList[m_modcount].m_type = t;
	m_modList[m_modcount].m_amount = a;
	m_modList[m_modcount].m_miscValue = miscValue;
	m_modList[m_modcount].i = i;
	m_modList[m_modcount].list_ind = m_modcount;
	m_modcount++;
	//ASSERT(m_modcount<=3);
}

void Aura::ApplyModifiers( bool apply )
{
	if( apply == true && m_target )
	{
	    if( m_spellProto->BGR_one_buff_on_target & SPELL_TYPE_SEAL )
			m_target->SetFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_JUDGEMENT );
	}
	for( uint32 x = 0; x < m_modcount; x++ )
	{
		mod = &m_modList[x];
//		mod->total_mods = m_modcount-1;
		if(mod->m_type<TOTAL_SPELL_AURAS)
		{
			sLog.outDebug( "WORLD: target = %u , Spell Aura id = %u (%s), SpellId  = %u, i = %u, apply = %s, duration = %u, damage = %d, period = %u",m_target->GetLowGUID(),mod->m_type, SpellAuraNames[mod->m_type], m_spellProto->Id, mod->i, apply ? "true" : "false",GetDuration(),mod->m_amount,m_spellProto->EffectAmplitude[ mod->i ]);
			(*this.*SpellAuraHandler[mod->m_type])(apply);
		}
		else
			sLog.outError("Unknown Aura id %d", (uint32)mod->m_type);
	}
}

void Aura::UpdateModifiers( )
{
	for( uint32 x = 0; x < m_modcount; x++ )
	{
		mod = &m_modList[x];

		if(mod->m_type<TOTAL_SPELL_AURAS)
		{
			sLog.outDebug( "WORLD: target = %u , Spell Aura id = %u (%s), SpellId  = %u, i = %u, duration = %u, damage = %d",m_target->GetLowGUID(),mod->m_type, SpellAuraNames[mod->m_type], m_spellProto->Id, mod->i, GetDuration(),mod->m_amount);
			switch (mod->m_type)
			{
				case 33: UpdateAuraModDecreaseSpeed(); break;

			}
		}
		else
			sLog.outError("Unknown Aura id %d", (uint32)mod->m_type);
	}
}

void Aura::EventUpdateAA(float r)
{
	uint32 i;
	vector<uint64> NewTargets;
	vector<uint64>::iterator NewTargetsitr;
	Group * group = NULL;

	// if the caster is no longer valid->remove the aura
	if( m_target == NULL || m_target->deleted != OBJ_AVAILABLE )
	{
		Remove();
		//since we lost the caster we cannot do anything more
		return;
	}

	bool skip_group_check = true;

	//if we are not added to a map then there is no point adding auras to anyone atm, just remove from old targets
	if( m_target->GetMapMgr() )
	{
		group = m_target->GetGroup();
		if( group )
		{
			skip_group_check = false;
			group->Lock();
			uint32 count = group->GetSubGroupCount();
			// Loop through each raid group.
			for( uint8 k = 0; k < count; k++ )
			{
				SubGroup * sgroup = group->GetSubGroup( k );
				if(sgroup && sgroup->GetMemberCount() > 0 )
				{
					GroupMembersSet::iterator itr;
					for(itr = sgroup->GetGroupMembersBegin(); itr != sgroup->GetGroupMembersEnd(); ++itr)
						if( (*itr) 
							&& (*itr)->m_loggedInPlayer 
							&& (*itr)->m_loggedInPlayer->GetInstanceID() == m_target->GetInstanceID()
							&& (*itr)->m_loggedInPlayer->GetDistanceSq(m_target) <= r 
							&& (*itr)->m_loggedInPlayer->isAlive()
							)
						{
							if( (*itr)->m_loggedInPlayer->HasAura(m_spellProto->Id) == false )
								NewTargets.push_back( (*itr)->m_loggedInPlayer->GetGUID() );
							//summons are also inside the group ?
							if( (*itr)->m_loggedInPlayer->GetSummon() && (*itr)->m_loggedInPlayer->GetSummon()->HasAura(m_spellProto->Id) == false )
								NewTargets.push_back( (*itr)->m_loggedInPlayer->GetSummon()->GetGUID() );
						}
				}
			}
			group->Unlock();
		}
		else
		{
			if( m_target->isAlive() && m_target->HasAura(m_spellProto->Id) == false )
				NewTargets.push_back( m_target->GetLowGUID() );	//no frikkin way
			else if( m_target->IsPlayer() && SafePlayerCast( m_target )->GetSummon() && SafePlayerCast( m_target )->GetSummon()->HasAura(m_spellProto->Id) == false  )
				NewTargets.push_back( SafePlayerCast( m_target )->GetSummon()->GetGUID() );
			else if( m_target->IsPet() && SafePetCast( m_target )->GetPetOwner() && SafePetCast( m_target )->GetPetOwner()->HasAura(m_spellProto->Id) == false  )
				NewTargets.push_back( SafePetCast( m_target )->GetPetOwner()->GetGUID() );
			else
			{
				Unit *topA = m_target->GetTopOwner();	//totem owner ;)
				if( topA && topA->HasAura(m_spellProto->Id) == false )
					NewTargets.push_back( topA->GetLowGUID() );
			}
		}

		//add aura to the new targets
		for( NewTargetsitr=NewTargets.begin();NewTargetsitr!=NewTargets.end();NewTargetsitr++)
		{
			Unit *target = m_target->GetMapMgr()->GetUnit( *NewTargetsitr );	//maybe one cast removes spawns ?
			if( target )
			{
				Aura * aura = NULL;
				aura = AuraPool.PooledNew();
				aura->Init(m_spellProto, -1, m_target, target);
				for(i = 0; i < m_modcount; ++i)
					if(m_spellProto->Effect[m_modList[i].i] == SPELL_EFFECT_APPLY_AREA_AURA
						|| m_spellProto->Effect[m_modList[i].i] == SPELL_EFFECT_APPLY_AREA_AURA2
						)
						aura->AddMod(m_modList[i].m_type, m_modList[i].m_amount,m_modList[i].m_miscValue, m_modList[i].i);
				aura->m_areaAura = true;	//! so other players may remove aura if clicked on it
				target->AddAura(aura);
			}
		}
	}

	// Update the existing players in the target set.
	AreaAuraList::iterator itr, it2;
	for(itr = targets.begin(); itr != targets.end(); )
	{
		it2 = itr;
		++itr;

		// Check if the target is 'valid'.
		Unit *target;
		if(m_target->IsInWorld())
			target = m_target->GetMapMgr()->GetUnit(*it2);
		else
			target = NULL;

		if( target == NULL )
			target = objmgr.GetPlayer(*it2);

		if( target == NULL )
		{
			targets.erase(it2);
			continue;
		}

		//caster does not loose aura, ever
		if( m_target == target ) 
			continue;

		if( target->GetDistanceSq( m_target ) > r || target->GetInstanceID() != m_target->GetInstanceID() || target->deleted != OBJ_AVAILABLE )
		{
			targets.erase(it2);
			target->RemoveAura(m_spellProto->Id);
			continue;
		}

		if(skip_group_check == false && ( !group || target->GetGroup() != group ) )
		{
			// execute in the correct context
			target->RemoveAura( m_spellProto->Id );
			targets.erase(it2);
		}
	}

	// Push new targets into the set.
	for(NewTargetsitr = NewTargets.begin(); NewTargetsitr != NewTargets.end(); ++NewTargetsitr)
		targets.insert( (*NewTargetsitr) );

	NewTargets.clear();
}

//!! this removes auras only from targets. We are not included here ! We are not supposed to be included !
void Aura::RemoveAA()
{
	AreaAuraList::iterator itr;

	for(itr = targets.begin(); itr != targets.end(); ++itr)
	{
		// Check if the target is 'valid'.
		Unit *aatarget;
		if(m_target->IsInWorld())
			aatarget = m_target->GetMapMgr()->GetUnit( *itr );
		else
			aatarget = objmgr.GetPlayer(*itr);

		if( !aatarget )
			continue;

		aatarget->RemoveAura( m_spellProto->Id );
	}
	targets.clear();
}

//------------------------- Aura Effects -----------------------------

void Aura::SpellAuraModBaseResistance(bool apply)
{
	SpellAuraModResistance(apply);
	//both add/decrease some resistance difference is unknown
}

void Aura::SpellAuraModBaseResistancePerc(bool apply)
{
	uint32 Flag = mod->m_miscValue;
	int32 amt;
	if(apply)
	{
		amt = mod->m_amount;
		if(amt > 0)
			SetPositive();
		else
			SetNegative();
	}
	else
		amt =- mod->m_amount;

	for(uint32 x=0;x<7;x++)
	{
		if(Flag & (((uint32)1)<< x))
		{
			if(m_target->GetTypeId() == TYPEID_PLAYER)
			{
				if(mod->m_amount>0)
				{
					SafePlayerCast( m_target )->BaseResistanceModPctPos[x]+=amt;
				}
				else
				{
					SafePlayerCast( m_target )->BaseResistanceModPctNeg[x]-=amt;
				}
				SafePlayerCast( m_target )->CalcResistance(x);

			}
			else if(m_target->GetTypeId() == TYPEID_UNIT)
			{
				SafeCreatureCast(m_target)->BaseResistanceModPct[x]+=amt;
				SafeCreatureCast(m_target)->CalcResistance(x);
			}
		}
	}
}

void Aura::SpellAuraNULL(bool apply)
{
	 sLog.outDebug("Unknown Aura id %d", (uint32)mod->m_type);
}

void Aura::SpellAuraBindSight(bool apply)
{
	SetPositive();
	// MindVision
	if(apply)
	{
		Unit *caster = GetUnitCaster();
		if(!caster || !caster->IsPlayer())
		{ 
			return;
		}
		caster->SetUInt64Value(PLAYER_FARSIGHT, m_target->GetGUID());
	}
	else
	{
		Unit *caster = GetUnitCaster();
		if(!caster || !caster->IsPlayer())
		{ 
			return;
		}
		caster->SetUInt64Value(PLAYER_FARSIGHT, 0 );
	}
}

void Aura::SpellAuraModPossess(bool apply)
{
	Unit *caster = GetUnitCaster();

	if(apply)
	{
		if( caster != NULL && caster->IsInWorld() && caster->GetTypeId() == TYPEID_PLAYER )
		{
			SafePlayerCast(caster)->Possess( m_target );
			SafePlayerCast(caster)->SpeedCheatDelay( GetDuration() );
		}
	}
	else
	{
		if( caster != NULL && caster->IsInWorld() && caster->GetTypeId() == TYPEID_PLAYER )
		{
			SafePlayerCast(caster)->UnPossess();
//			SafePlayerCast(caster)->SpeedCheatReset();
		}

		// make sure Player::UnPossess() didn't fail, if it did we will just free the target here
		if( m_target->GetUInt64Value( UNIT_FIELD_CHARMEDBY ) != 0 )
		{
			if( m_target->GetTypeId() == TYPEID_UNIT )
			{
				m_target->setAItoUse( true );
				m_target->m_redirectSpellPackets = 0;
			}

			m_target->SetUInt64Value( UNIT_FIELD_CHARMEDBY, 0 );
			m_target->RemoveFlag( UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED_CREATURE );
			m_target->SetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE, m_target->GetCharmTempVal() );
			m_target->_setFaction();
//			m_target->UpdateOppFactionSet();
		}
		else
		{
			//mob woke up and realized he was controlled. He will turn to controller and also notify the other mobs he is fighting that they should attack the caster
			//sadly i got only 3 test cases about this so i might be wrong :(
			//zack : disabled until tested
			m_target->GetAIInterface()->EventChangeFaction( caster );
		}
	}
}

void Aura::SpellAuraPeriodicDamage(bool apply)
{
	if(apply)
	{
		if( m_target )
		{
			if( m_spellProto->MechanicsType == MECHANIC_BLEEDING && m_target->MechanicsDispels[MECHANIC_BLEEDING] )
			{
				m_flags |= 1 << mod->i;
				return;
			}
		}
		int32 dmg	= mod->m_amount;
		Unit *c = GetUnitCaster();
		switch(m_spellProto->Id)
		{
			case 703:
			case 8631:
			case 8632:
			case 8633:
			case 8818:
			case 11289:
			case 11290:
				if(c)
					c->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_START_ATTACK);  // remove stealth
				break;
		};
		//this is warrior : Deep Wounds
		if(c && c->IsPlayer() && pSpellId)
		{
			uint32 multiplyer=0;
			if(pSpellId==12834)
					multiplyer = 16;//level 1 of the talent should apply 20 of avarege melee weapon dmg
			else if(pSpellId==12849)
					multiplyer = 32;
			else if (pSpellId==12867)
					multiplyer = 48;
			if(multiplyer)
			{
				Player *pr=SafePlayerCast(c);
				if(pr->GetItemInterface())
				{
					Item *it;
					it = pr->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
					if(it && it->GetProto())
					{
						dmg = 0;
						for(int i=0;i<ITEM_DAMAGE_COUNT;i++)
							if(it->GetProto()->Damage[i].Type==SCHOOL_NORMAL)
								dmg += int32((it->GetProto()->Damage[i].Min + it->GetProto()->Damage[i].Max) / 2);
						dmg = multiplyer * dmg /100;
					}
				}
			}
		}

		if(Need_SM_Apply(GetSpellProto()))
		{
			Unit*c=GetUnitCaster();
			if(c)
			{
				SM_FIValue(c->SM_FDOT,(int32*)&dmg,GetSpellProto()->SpellGroupType);
				SM_PIValue(c->SM_PDOT,(int32*)&dmg,GetSpellProto()->SpellGroupType);
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
				int spell_flat_modifers=0;
				int spell_pct_modifers=0;
				SM_FIValue(c->SM_FDOT,&spell_flat_modifers,GetSpellProto()->SpellGroupType);
				SM_FIValue(c->SM_PDOT,&spell_pct_modifers,GetSpellProto()->SpellGroupType);
				if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
					printf("!!!!!spell periodic dmg mod flat %d , spell dmg bonus pct %d , spell dmg bonus %d, spell group %u\n",spell_flat_modifers,spell_pct_modifers,dmg,gr);
#endif
			}
		}

		if(dmg<=0)
			return; //who would want a neagtive dmg here ?

		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHasteDots() );
		}
		if( period < 500 )
			period = 500;

		int32 ticks = GetDuration() / period;
		if( ticks < 1 )
			ticks = 1;
//		sLog.outDebug("Registering periodic ticks. Total dmg %u, period %u \n",dmg,period);
		sEventMgr.AddEvent(this, &Aura::EventPeriodicDamage,(uint32)dmg,(uint32)ticks,
				EVENT_AURA_PERIODIC_DAMAGE, period ,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

		/*SafePlayerCast( c )->GetSession()->SystemMessage("dot will do %u damage every %u seconds (total of %u)", dmg,m_spellProto->EffectAmplitude[mod->i],(GetDuration()/m_spellProto->EffectAmplitude[mod->i])*dmg);
		printf("dot will do %u damage every %u seconds (total of %u)\n", dmg,m_spellProto->EffectAmplitude[mod->i],(GetDuration()/m_spellProto->EffectAmplitude[mod->i])*dmg);*/
		SetNegative();
		if( m_spellProto->NameHash == SPELL_HASH_IMMOLATE || m_spellProto->NameHash == SPELL_HASH_SHADOWFLAME )
			m_target->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_IMMOLATE);
		//maybe poison aurastate should get triggered on other spells too ?
		else if( m_spellProto->c_is_flags & SPELL_FLAG_IS_POISON )//deadly poison
			m_target->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_POISON);
	}
	else if( (m_flags & (1 << mod->i)) == 0 ) //add these checks to mods where imunity can cancel only 1 mod and not whole spell
	{
//		if( m_spellProto->BGR_one_buff_on_target & SPELL_TYPE_WARLOCK_IMMOLATE )
		if( (m_spellProto->NameHash == SPELL_HASH_IMMOLATE || m_spellProto->NameHash == SPELL_HASH_SHADOWFLAME) )
		{
			Unit *u_caster = GetUnitCaster();
			Player *p_caster;
			if( u_caster && u_caster->IsPlayer() )
				p_caster = SafePlayerCast( u_caster );
			else
				p_caster = NULL;
			 if( p_caster == NULL || p_caster->HasGlyphWithID( GLYPH_WARLOCK_CONFLAGRATE ) == false )
				m_target->RemoveFlag( UNIT_FIELD_AURASTATE,AURASTATE_FLAG_IMMOLATE );
		}
		//maybe poison aurastate should get triggered on other spells too ?
		else if( m_spellProto->c_is_flags & SPELL_FLAG_IS_POISON )//deadly poison
			m_target->RemoveFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_POISON);
	}
}

void Aura::EventPeriodicDamage(uint32 amount,uint32 ticks)
{
	//DOT
	if(!m_target || !m_target->isAlive())
	{ 
		return;
	}
	if(m_target->SchoolImmunityList[GetSpellProto()->School])
	{ 
		return;
	}
	Unit * c = GetUnitCaster();
	if(m_target->GetGUID()!=m_casterGuid)//don't use resist when cast on self-- this is some internal stuff
	{
		if(c)
		{
			c->SpellNonMeleeDamageLog( m_target, GetSpellProto()->Id, amount, true, false, false, ticks);
			return; //!! aura can get deleted while doing dmg !!
		}
	}
}

void Aura::SpellAuraDummy(bool apply)
{
	// Try a dummy SpellHandler
	if(sScriptMgr.CallScriptedDummyAura(GetSpellId(), mod->i, this, apply))
	{ 
		return;
	}

	uint32 TamingSpellid = 0;

	Player * _ptarget;

	if( m_target->IsPlayer() )
		_ptarget = SafePlayerCast( m_target );
	else 
		_ptarget = NULL;

	switch(GetSpellId())
	{
#include "../arcemu-customs/custom_spell_auras.cpp"
		case 43827:
			{
				if( apply )
					m_target->SetUInt32Value( UNIT_FIELD_DISPLAYID, 30721 );
				else
					m_target->SetUInt32Value( UNIT_FIELD_DISPLAYID, m_target->GetUInt32Value( UNIT_FIELD_NATIVEDISPLAYID ) );
			}break;
		//druid Master Shapeshifter
		case 48411:
		case 48412:
			{
				if( _ptarget )
				{
					if( apply )
					{
						uint32 spell_to_cast = 0;
						if( _ptarget->GetShapeShift() == FORM_BEAR )
							spell_to_cast = 48418;
						else if( _ptarget->GetShapeShift() == FORM_CAT )
							spell_to_cast = 48420;
						else if( _ptarget->GetShapeShift() == FORM_MOONKIN )
							spell_to_cast = 48421;
						else if( _ptarget->GetShapeShift() == FORM_TREE )
							spell_to_cast = 48422;
						if( spell_to_cast )
						{
		                    SpellCastTargets targets2( _ptarget->GetGUID() );
							SpellEntry *spellInfo = dbcSpell.LookupEntry( spell_to_cast );
							Spell *spell = SpellPool.PooledNew();
							spell->Init(_ptarget, spellInfo ,true, NULL);
							spell->forced_basepoints[0] = GetSpellProto()->EffectBasePoints[0]+1;
							spell->prepare(&targets2);
						}
						mod->fixed_amount[ 0 ] = spell_to_cast;
					}
					else if( mod->fixed_amount[ 0 ] )
					{
						_ptarget->RemoveAura( mod->fixed_amount[ 0 ] );
					}
				}
			}break;
		//Corrupt Soul - boss spell
		case 68839:
			{
				if( apply == false && m_target )
				{
					Unit *u_caster = GetUnitCaster();
					if( u_caster )
						u_caster->create_guardian( 36535, 10*60*1000, 0, NULL, m_target->GetPositionV() );
				}
			}break;
		case 53563:	//beacon of light
			{
				Unit *caster = GetUnitCaster();
				if( caster == NULL )
					return; //nothing we can do here
				if( apply )
				{
					ProcTriggerSpell *pts = new ProcTriggerSpell(GetSpellProto());
//					pts->procChance = GetSpellProto()->procChance;
//					pts->procCharges = GetSpellProto()->procCharges;
					pts->spellId = GetSpellProto()->EffectTriggerSpell[mod->i];
					pts->caster = m_target->GetGUID();		//orginally blizz made it so beacon registers this cast
					caster->m_procSpells.push_front(pts);	//if caster casts a healing spell
				}
				else
				{
					uint64 tcasterguid = m_target->GetGUID();
					CommitPointerListNode<ProcTriggerSpell> *itr;
					for(itr = caster->m_procSpells.begin();itr != caster->m_procSpells.end();itr = itr->Next() )
						if(itr->data->origId == GetSpellId() && itr->data->caster == tcasterguid && !itr->data->deleted)
						{
							itr->data->deleted = true;
							break;
						}
				}
			}break;
		case 48018:
			{
				//Demonic Circle: Summon -> periodic trigger ? we do not really need it, one cast is enough
				if( _ptarget && _ptarget->GetSession() )
				{
					if( apply )
					{
						//!! this spell does not exist in our DBC, client however knows about it !
						sStackWolrdPacket(data, SMSG_AURA_UPDATE, 20 );
						data << _ptarget->GetNewGUID();
						data << uint8( 255 );	//slot, it is fictional !
						data << uint32( 62388 );	//spell id
						data << uint8( VISUALAURA_FLAG_REMOVABLE | VISUALAURA_FLAG_SELF_CAST | VISUALAURA_FLAG_VISIBLE_1 | VISUALAURA_FLAG_VISIBLE_2 | VISUALAURA_FLAG_VISIBLE_3 );	//flags, cause i say so
						data << uint8( 80 );	//lvl 80 rules
						data << uint8( 0 );		//stack, ofc it does not stack
						_ptarget->GetSession()->SendPacket( &data );
					}
					else
					{
						sStackWolrdPacket(data, SMSG_AURA_UPDATE, 20 );
						data << _ptarget->GetNewGUID();
						data << uint8( 255 );	//slot, it is fictional !
						data << uint32( 0 );	//spell id = clear
						_ptarget->GetSession()->SendPacket( &data );
					}
				}
			}break;
		//Impurity
		case 49220:	
		case 49633:
		case 49635:
		case 49636:
		case 49638:	
			{
				if( _ptarget )
				{
					if( apply )
						_ptarget->ModAbillityAPBonusCoef += mod->m_amount / 100.0f;
					else
						_ptarget->ModAbillityAPBonusCoef -= mod->m_amount / 100.0f;
				}
			}break;
		case 61336:	//Survival Instincts
			{
				if( _ptarget )
					SpellAuraModIncreaseMaxHealthPerc(apply);
			}break;
		case 62061:	//Festive Holiday Mount
			{
				if( _ptarget )
				{
					if( apply )
						_ptarget->mount_look_override = 22724;
					else
						_ptarget->mount_look_override = 0;
				}
			}break;
		case 62062: //Brewfestive Holiday Mount
			{
				if( _ptarget )
				{
					if( apply )
						_ptarget->mount_look_override = 24757;
					else
						_ptarget->mount_look_override = 0;
				}
			}break;
		case 53270: //hunter : beast mastery
			{
				if( _ptarget )
				{
					if( apply )
					{
						_ptarget->pet_extra_talent_points += mod->m_amount;
						if( _ptarget->GetSummon() )
							_ptarget->GetSummon()->smsg_TalentsInfo();
					}
					else
					{
						_ptarget->pet_extra_talent_points -= mod->m_amount;
						//only take these actions on talent reset 
						//_ptarget->ForceAllPetTalentAndSpellReset();
					}
				}
			}break;
		case 53042: //mixology
			{
				if( _ptarget )
				{
					if( apply )
						_ptarget->has_mixology_talent++;
					else if( _ptarget->has_mixology_talent )
						_ptarget->has_mixology_talent--;
				}
			}break;
		case 17619: //alchemist stone
			{
				if( _ptarget )
				{
					if( apply )
						_ptarget->has_alchemist_stone_effect++;
					else if( _ptarget->has_alchemist_stone_effect )
						_ptarget->has_alchemist_stone_effect--;
				}
			}break;
	// Deadly Throw Interrupt
	case 32748:
	{
		if ( m_target == NULL )
		{ 
			return;
		}

		uint32 school = 0;
		if(m_target->GetCurrentSpell())
		{
			school = m_target->GetCurrentSpell()->GetProto()->School;
		}
		m_target->InterruptSpell();
		m_target->SchoolCastPrevent[school]=3000+getMSTime();
	}break;
	//improved sprint effect
	case 30918:
	{
		m_target->RemoveAllMovementImpairing();
	}break;
	//Requires No Ammo
	case 46699:
		{
			if( m_target->IsPlayer() )
				SafePlayerCast( m_target )->m_requiresNoAmmo = apply;

		}break;
	//Hunter - Bestial Wrath & The Beast Within
	//Both should provide immunity for all CC effect, but the dbc specifies only stuns. Imba!
	case 19574:
	case 34471:
		{
			static uint32 mechanics[15] = { MECHANIC_CHARMED, MECHANIC_DISORIENTED,	MECHANIC_DISTRACED, MECHANIC_FLEEING, 
											MECHANIC_ROOTED, MECHANIC_ASLEEP, MECHANIC_ENSNARED, MECHANIC_STUNNED,
											MECHANIC_FROZEN, MECHANIC_INCAPACIPATED, MECHANIC_POLYMORPHED, MECHANIC_BANISHED,
											MECHANIC_INFECTED, MECHANIC_HORRIFIED, MECHANIC_SAPPED };
			
			for( uint32 x = 0; x < 15; x++ )
			{
				if( apply )
				{
					m_target->MechanicsDispels[ mechanics[x] ]++;
					m_target->RemoveAllAurasByMechanic( mechanics[x], (uint32)(-1), false );
				}
				else if( m_target->MechanicsDispels[ mechanics[x] ] > 0 )
					m_target->MechanicsDispels[ mechanics[x] ]--;
			}
		}break;
	//Warlock - Demonic Knowledge
	case 35696:
		{
			if ( m_target->IsPet() )
			{
				Unit* PetOwner;
				if ( SafePetCast( m_target )->GetPetOwner() )
				{
					PetOwner = SafePetCast( m_target )->GetPetOwner();
					if( apply == true )
					{
						uint32 val1 = m_target->GetUInt32Value( UNIT_FIELD_STAT2 ); // stamina
						uint32 val2 = m_target->GetUInt32Value( UNIT_FIELD_STAT3 ); // intelect
						uint32 val0 = val1+val2;
						mod->m_amount = val0*mod->m_amount/100;
					}
					Unit *old_target = m_target;
					m_target = PetOwner;
					SpellAuraModDamageDone( apply );	//avoid code redundancy, let same function handle us
					if( m_target = PetOwner )			//maybe aura got removed ...call chains are evil with shared memory ;)
						m_target = old_target;
				}
			}
		}break;
	//paladin - Blessing of Light.
/*	case 19977:
	case 19978:
	case 19979:
	case 27144:
	case 32770:
	case 27145:
	case 25890:
		{
			if( mod->i == 0 )
				SMTMod_On_target( apply, false, 0x9B56A8F5, mod->m_amount ); //holy light
			if( mod->i == 1 )
				SMTMod_On_target( apply, false, 0x333C4740, mod->m_amount ); //flash of light
		}break;*/
	//shaman - Healing Way - effect
/*	case 29203:
		{
			SMTMod_On_target( apply, true, 0x08F1A7EF, mod->m_amount ); // Healing Wave
		}break;*/
	//druid - mangle
	case 33878:
	case 33986:
	case 33987:
	case 33876:
	case 33982:
	case 33983:
		{
			int32 val = (apply) ? 30 : -30;
			m_target->ModDamageTakenByMechCoef[MECHANIC_BLEEDING] += float( val ) / 100.0f;
		}break;
	//warrior - berserker rage (Forcing a dummy aura, so we can add the missing 4th effect).
	case 18499:
		{
			if( !m_target->IsPlayer() )
			{ 
				return;
			}

			Player * p = SafePlayerCast( m_target );

			if( apply )
				p->rageFromDamageTaken += 100;
			else
				p->rageFromDamageTaken -= 100;

			for( int32 i = 0; i < 3; i++ )
			{
				if( apply )
				{
					p->MechanicsDispels[ GetSpellProto()->EffectMiscValue[i] ]++;
					p->RemoveAllAurasByMechanic( GetSpellProto()->EffectMiscValue[i] , (uint32)(-1) , false );
				}
				else if( p->MechanicsDispels[ GetSpellProto()->EffectMiscValue[i] ] > 0 )
					p->MechanicsDispels[ GetSpellProto()->EffectMiscValue[i] ]--;
			}
		}break;
	//warrior - sweeping strikes
	case 12328:
		{
			if(apply)
				m_target->AddExtraStrikeTarget(GetSpellProto(), 10);
			else
				m_target->RemoveExtraStrikeTarget(GetSpellProto());
		}break;
	//taming rod spells
	case 19548:	{                 //invoke damage to trigger attack
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19597; //uses Spelleffect3 #19614
	}break;
	case 19674:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19677;
	}break;
	case 19687:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19676;
	}break;
	case 19688:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19678;
	}break;
	case 19689:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19679;
	}break;
	case 19692:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19680;
	}break;
	case 19693:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19684;
	}break;
	case 19694:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19681;
	}break;
	case 19696:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19682;
	}break;
	case 19697:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19683;
	}break;
	case 19699:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19685;
	}break;
	case 19700:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=19686;
	}break;
	case 30099:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=30100;
	}break;
	case 30102:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=30103;
	}break;
	case 30105:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=30104;
	}break;
	case 30646:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=30647;
	}break;
	case 30653:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=30648;
	}break;
	case 30654:	{
		if (apply)
		{
			m_target->GetAIInterface()->AttackReaction( GetUnitCaster(), 10, 0);
			break;
		}
		else
			TamingSpellid=30648;
	}break;
	case 16972://Predatory Strikes
	case 16974:
	case 16975:
	{
		if(apply)
		{
			SetPositive();
			mod->fixed_amount[0] = (mod->m_amount * m_target->getLevel())/100;
			m_target->ModUnsigned32Value(UNIT_FIELD_ATTACK_POWER_MODS,mod->fixed_amount[0]);
		}else
			m_target->ModUnsigned32Value(UNIT_FIELD_ATTACK_POWER_MODS, -mod->fixed_amount[0]);
		m_target->CalcDamage();
	}break;
	case 974:	//Earth Shield
	case 32593:
	case 32594:
		{
			if(apply)
			{
				ProcTriggerSpell *pts = new ProcTriggerSpell(GetSpellProto());
				pts->caster = m_casterGuid;
				pts->procChance = GetSpellProto()->procChance;
				int charges = GetSpellProto()->procCharges;
				if( (GetSpellProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && GetUnitCaster() != NULL )
				{
					SM_FIValue( GetUnitCaster()->SM_FCharges, &charges, GetSpellProto()->SpellGroupType );
					SM_PIValue( GetUnitCaster()->SM_PCharges, &charges, GetSpellProto()->SpellGroupType );
	#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
					float spell_flat_modifers=0;
					float spell_pct_modifers=0;
					SM_FIValue(GetUnitCaster()->SM_FCharges,&spell_flat_modifers,GetSpellProto()->SpellGroupType);
					SM_FIValue(GetUnitCaster()->SM_PCharges,&spell_pct_modifers,GetSpellProto()->SpellGroupType);
					if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
						printf("!!!!!spell charge bonus mod flat %f , spell range bonus pct %f , spell range %f, spell group %u\n",spell_flat_modifers,spell_pct_modifers,maxRange,m_spellInfo->SpellGroupType);
	#endif
				}
				pts->procCharges = charges;
				m_target->m_procSpells.push_front(pts);
			}
			else
			{
				CommitPointerListNode<ProcTriggerSpell> *itr;
				for(itr = m_target->m_procSpells.begin();itr != m_target->m_procSpells.end();itr = itr->Next() )
					if(itr->data->origId == GetSpellId() && itr->data->caster == m_casterGuid && !itr->data->deleted)
					{
						//m_target->m_procSpells.erase(itr);
						itr->data->deleted = true;
						break;
					}
			}
		}break;
	case 126: //Eye of Kilrogg
		{
			/*if(m_target->IsInWorld() == false)
				return;

			if(!apply)
			{
				m_target->SetUInt64Value(PLAYER_FARSIGHT,0);
				Creature *summon = m_target->GetMapMgr()->GetCreature(m_target->GetUInt32Value(UNIT_FIELD_SUMMON));
				m_target->SetUInt64Value(UNIT_FIELD_SUMMON, 0);
				m_target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);

				if(summon)
				{
					summon->RemoveFromWorld(false,true);
					delete summon;
				}
				m_target->m_noInterrupt--;
				if(m_target->m_noInterrupt < 0)
					m_target->m_noInterrupt = 0;
			}*/
		}break;
	case 17056://Furor
	case 17058:
	case 17059:
	case 17060:
	case 17061:
		{
			if( !_ptarget )
				return;
			if( apply ) 
			{
				mod->fixed_amount[0] = 0;
				if( m_target->getClass() == DRUID && Rand( mod->m_amount ) )
				{
//					uint32 furorSpell;
					uint32 ss = _ptarget->GetShapeShift();
					if( ss == FORM_CAT )
	//					furorSpell = 17099;	//it's ok
						m_target->SetUInt32Value(UNIT_FIELD_POWER1 + POWER_TYPE_ENERGY, mod->m_amount );
					else if( ss == FORM_BEAR || ss == FORM_DIREBEAR )
	//					furorSpell = 17057;	//it's ok
						m_target->SetUInt32Value(UNIT_FIELD_POWER1 + POWER_TYPE_RAGE, 10 * 10 );
					else if( ss == FORM_MOONKIN )
					{
						mod->fixed_amount[0] = GetSpellProto()->EffectBasePoints[1] + 1;
						_ptarget->StatModPctPos[ STAT_INTELLECT ] += mod->fixed_amount[0];
						_ptarget->CalcStat( STAT_INTELLECT );
						_ptarget->UpdateStats();
						_ptarget->UpdateChances();
					}
	/*				else
						furorSpell = 0;

					if( furorSpell != 0 )
					{
						SpellEntry *spellInfo = dbcSpell.LookupEntry( furorSpell );

						Spell *sp = SpellPool.PooledNew();
						sp->Init( m_target, spellInfo, true, NULL );
						SpellCastTargets tgt(m_target->GetGUID());
						sp->prepare(&tgt);
					}*/
				}
			}
			else
			{
				if( mod->fixed_amount[0] != 0 )
				{
					_ptarget->StatModPctPos[ STAT_INTELLECT ] -= mod->fixed_amount[0];
					_ptarget->CalcStat( STAT_INTELLECT );
					_ptarget->UpdateStats();
					_ptarget->UpdateChances();
				}
			}
		}break;
	case 12295:
	case 12676:
	case 12677:
	case 12678:
		{
			if( !_ptarget )
				return;
			if(apply)
				_ptarget->m_retainedrage += mod->m_amount*10; //don't really know if value is all value or needs to be multiplyed with 10
			else
				_ptarget->m_retainedrage -= mod->m_amount*10;
		}break;
	case 2096://MindVision
		{
		}break;
	case 6196://FarSight
		{
			if(apply)
			{
			}
			else
			{
				// disabled this due to unstableness :S
#if 0
				Creature *summon = m_target->GetMapMgr()->GetCreature(m_target->GetUInt32Value(PLAYER_FARSIGHT));
				if(summon)
				{
					summon->RemoveFromWorld(false,true);
					delete summon;
				}
				m_target->SetUInt64Value(PLAYER_FARSIGHT,0);
#endif
			}
		}break;
	case 18182:
	case 18183:
		{//improved life tap give amt% bonus for convers
			if( _ptarget == NULL )
				return;
			if(apply)
				_ptarget->m_lifetapbonus=mod->m_amount;
			else
				_ptarget->m_lifetapbonus=0;
		}break;
	case 20608://Reincarnation
		{
			if( _ptarget == NULL )
				return;
			if(apply)
				_ptarget->bReincarnation = true;
			else
				_ptarget->bReincarnation = false;
		}break;
	case 20707://Soulstone Resurrecton
		if( _ptarget )
		{
			if(apply)
			{
			    _ptarget->SetSoulStone(3026);
				_ptarget->SetSoulStoneReceiver((uint32)m_casterGuid);
			}
			else if(m_target->isAlive())
			{
	            _ptarget->SetSoulStone(0);
		        _ptarget->SetSoulStoneReceiver(0);
			}break;
		}
	case 20762:
		if( _ptarget )
		{
			if(apply)
			{
				_ptarget->SoulStone = 20758;
				_ptarget->SoulStoneReceiver = (uint32)m_casterGuid;
			}
			else if(m_target->isAlive())
				_ptarget->SoulStone = _ptarget->SoulStoneReceiver = 0;
			}
		break;
	case 20763:
		if( _ptarget )
		{
			if(apply)
			{
				_ptarget->SoulStone = 20759;
				_ptarget->SoulStoneReceiver = (uint32)m_casterGuid;
			}
			else if(m_target->isAlive())
				_ptarget->SoulStone = _ptarget->SoulStoneReceiver = 0;
		}
		break;
	case 20764:
		if( _ptarget )
		{
			if(apply)
			{
				_ptarget->SoulStone = 20760;
				_ptarget->SoulStoneReceiver = (uint32)m_casterGuid;
			}
			else if(m_target->isAlive())
				_ptarget->SoulStone = _ptarget->SoulStoneReceiver = 0;
		}
		break;
	case 20765:
		if( _ptarget )
		{
			if(apply)
			{
				_ptarget->SoulStone = 20761;
				_ptarget->SoulStoneReceiver = (uint32)m_casterGuid;
			}
			else if(m_target->isAlive())
				_ptarget->SoulStone = _ptarget->SoulStoneReceiver = 0;
		}
		break;
	case 27239:
		{
			if( _ptarget )
			{
				if(apply)
				{
					_ptarget->SoulStone = 27240;
					_ptarget->SoulStoneReceiver = (uint32)m_casterGuid;
				}
				else if(m_target->isAlive())
					_ptarget->SoulStone = _ptarget->SoulStoneReceiver = 0;
			}
		}break;
	case 47883:
		{
			if( _ptarget )
			{
				if(apply)
				{
					_ptarget->SoulStone = 47882;
					_ptarget->SoulStoneReceiver = (uint32)m_casterGuid;
				}
				else if(m_target->isAlive())
					_ptarget->SoulStone = _ptarget->SoulStoneReceiver = 0;
			}
		}break;
	case 570:   // far sight
	case 1345:
	case 6197:
	case 6198:  // eagle eye
	case 24125:
	case 21171:
		{
			/*if(!apply && m_target->GetTypeId() == TYPEID_PLAYER && m_target->IsInWorld())
			{
				// reset players vision
				Player * plr = SafePlayerCast( m_target );
				plr->GetMapMgr()->ChangeFarsightLocation(plr, NULL);

				Creature * farsight = plr->GetMapMgr()->GetCreature(plr->GetUInt32Value(PLAYER_FARSIGHT));
				plr->SetUInt64Value(PLAYER_FARSIGHT, 0);
				if(farsight)
				{
					farsight->RemoveFromWorld(false,true);
					delete farsight;
				}
			}*/
		}break;

	case 23701://Darkmoon Card: Twisting Nether give 10% chance to self resurrect ->cast 23700
		{
			//if(!apply)

		}break;

	//Second Wind - triggers only on stun and Immobilize
	case 29834:
		{
			Unit *caster = GetUnitCaster();
			if(caster && caster->IsPlayer())
				SafePlayerCast(caster)->SetTriggerStunOrImmobilize(29841,100, true);//fixed 100% chance
		}break;
	case 29838:
		{
			Unit *caster = GetUnitCaster();
			if(caster && caster->IsPlayer())
				SafePlayerCast(caster)->SetTriggerStunOrImmobilize(29842,100, true);//fixed 100% chance
		}break;
	//mage Magic Absorption
	case 29441:
	case 29444:
	case 29445:
	case 29446:
	case 29447:
		{
			if (m_target->IsPlayer())
			{
				SafePlayerCast( m_target )->m_RegenManaOnSpellResist += ((apply) ? 1:-1)*(float)mod->m_amount/100;
			}
		}break;
/*	//warlock - seed of corruption
	case 27243:
	case 32863:
	case 36123:
	case 38252:
	case 39367:
		{
			//register a cast on death of the player
			if(apply)
			{
				ProcTriggerSpell pts;
				pts.origId = GetSpellProto()->Id;
				pts.caster = m_casterGuid;
//					pts.spellId=GetSpellProto()->Id;
				pts.spellId=32865;
				if(!pts.spellId)
					return;
				pts.procChance = GetSpellProto()->procChance;
//					pts.procFlags = GetSpellProto()->procFlags;
				pts.procFlags = PROC_ON_DIE;
				pts.procCharges = GetSpellProto()->procCharges;
				pts.LastTrigger = 0;
				pts.deleted = false;
				m_target->m_procSpells.push_front(pts);
			}
			else
			{
				for(std::list<struct ProcTriggerSpell>::iterator itr = m_target->m_procSpells.begin();itr != m_target->m_procSpells.end();itr++)
				{
					if(itr->origId == GetSpellId() && itr->caster == m_casterGuid)
					{
						//m_target->m_procSpells.erase(itr);
						itr->deleted = true;
						break;
					}
				}
			}
		}break;*/

	case 740:
	case 8918:
	case 9862:
	case 9863:
	case 21791:
	case 25817:
	case 26983:
	case 34550:
	case 48446:
	case 48447:		// Tranquility 6+7 Fix by MtR
		{
			//uint32 duration = GetDuration();
			//printf("moo\n");
			if(apply)
				sEventMgr.AddEvent(this, &Aura::EventPeriodicHeal1, (uint32)mod->m_amount, EVENT_AURA_PERIODIC_HEAL, 2000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			else
				sEventMgr.RemoveEvents(this, EVENT_AURA_PERIODIC_HEAL);

		}break;

	case 16914:
	case 17401:
	case 17402:
	case 27012:		// hurricane
		{
			if(apply)
			{
				uint32 ticks = GetDuration() / 1000;
				sEventMgr.AddEvent(this, &Aura::EventPeriodicDamage, (uint32)mod->m_amount / ticks,ticks, EVENT_AURA_PERIODIC_DAMAGE, 1000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			}
			else
				sEventMgr.RemoveEvents(this, EVENT_AURA_PERIODIC_DAMAGE);
		}break;

	case 33763:		// Lifebloom Rank 1 by MtR
		{
			if(apply)
			{ 
				return;
			}

			// apply ONCE only.
			if( m_ignoreunapply )
			{ 
				return;
			}

			Unit * pCaster = GetUnitCaster();
			if( pCaster == NULL )
				pCaster = m_target;

			// Remove other Lifeblooms - but do NOT handle unapply again
			bool expired = true;
			for(uint32 x=MAX_AURAS;x<m_target->m_auras_pas_size;x++)
			{
				if(m_target->m_auras[x])
				{
					if( m_target->m_auras[x]->GetSpellId() == 33763 )
					{
						m_target->m_auras[x]->m_ignoreunapply = true;
						if( m_target->m_auras[x]->GetTimeLeft() )
							expired = false;
						m_target->m_auras[x]->Remove();
					}
				}
			}
			
			if( expired )
			{
				Spell *spell=SpellPool.PooledNew();
				spell->Init(pCaster, m_spellProto, true, NULL);
				spell->SetUnitTarget( m_target );
				spell->Heal( mod->m_amount );
			}
			
		}break;
	case 48450:		// Lifebloom Rank 2 by MtR
		{
			if(apply)
			{ 
				return;
			}

			// apply ONCE only.
			if( m_ignoreunapply )
			{ 
				return;
			}

			Unit * pCaster = GetUnitCaster();
			if( pCaster == NULL )
				pCaster = m_target;

			// Remove other Lifeblooms - but do NOT handle unapply again
			bool expired = true;
			for(uint32 x=MAX_AURAS;x<m_target->m_auras_pas_size;x++)
			{
				if(m_target->m_auras[x])
				{
					if( m_target->m_auras[x]->GetSpellId() == 48450 )
					{
						m_target->m_auras[x]->m_ignoreunapply = true;
						if( m_target->m_auras[x]->GetTimeLeft() )
							expired = false;
						m_target->m_auras[x]->Remove();
					}
				}
			}
			
			if( expired )
			{
				Spell *spell=SpellPool.PooledNew();
				spell->Init(pCaster, m_spellProto, true, NULL);
				spell->SetUnitTarget( m_target );
				spell->Heal( mod->m_amount );
			}
			
		}break;
	case 48451:		// Lifebloom Rank 3 by MtR
		{
			if(apply)
			{ 
				return;
			}

			// apply ONCE only.
			if( m_ignoreunapply )
			{ 
				return;
			}

			Unit * pCaster = GetUnitCaster();
			if( pCaster == NULL )
				pCaster = m_target;

			// Remove other Lifeblooms - but do NOT handle unapply again
			bool expired = true;
			for(uint32 x=MAX_AURAS;x<m_target->m_auras_pas_size;x++)
			{
				if(m_target->m_auras[x])
				{
					if( m_target->m_auras[x]->GetSpellId() == 48451 )
					{
						m_target->m_auras[x]->m_ignoreunapply = true;
						if( m_target->m_auras[x]->GetTimeLeft() )
							expired = false;
						m_target->m_auras[x]->Remove();
					}
				}
			}
			
			if( expired )
			{
				Spell *spell=SpellPool.PooledNew();
				spell->Init(pCaster, m_spellProto, true, NULL);
				spell->SetUnitTarget( m_target );
				spell->Heal( mod->m_amount );
			}
			
		}break;
	case 2584:			// Area spirit healer aura for BG's
		{
			if( !m_target->IsPlayer() || apply )		// already applied in opcode handler
			{ 
				return;
			}

			Player* pTarget = SafePlayerCast( m_target );
			uint64 crtguid = pTarget->m_areaSpiritHealer_guid;
			Creature* pCreature = pTarget->IsInWorld() ? pTarget->GetMapMgr()->GetCreature( crtguid ) : NULL;
			if(pCreature==NULL || pTarget->m_bg==NULL)
			{ 
				return;
			}

			pTarget->m_bg->RemovePlayerFromResurrect(pTarget,pCreature);
		}break;

	case 34477: // Misdirection
		{
			if (GetUnitCaster()->GetTypeId() != TYPEID_PLAYER)
			{ 
				return;
			}

			if (!apply)
			{
				sEventMgr.AddEvent(SafePlayerCast(GetUnitCaster()), &Player::SetMisdirectionTarget,(uint64)0, EVENT_UNK, 250, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
				//SafePlayerCast(GetUnitCaster())->SetMisdirectionTarget(0);
			}
		}break;

	case 17007: //Druid:Leader of the Pack
		{
			if( !m_target->IsPlayer() )
			{ 
				return;
			}

			Player * pTarget = SafePlayerCast(m_target);
			if( apply )
				pTarget->AddShapeShiftSpell( 24932 );
			else
				pTarget->RemoveShapeShiftSpell( 24932 );
		}break;
	case 48384: //Druid:Improved Moonkin Form
		{
			if( !m_target->IsPlayer() )
			{ 
				return;
			}

			Player * pTarget = SafePlayerCast(m_target);
			if( apply )
				pTarget->AddShapeShiftSpell( 50170 );
			else
				pTarget->RemoveShapeShiftSpell( 50170 );
		}break;
	case 48385: //Druid:Improved Moonkin Form
		{
			if( !m_target->IsPlayer() )
			{ 
				return;
			}

			Player * pTarget = SafePlayerCast(m_target);
			if( apply )
				pTarget->AddShapeShiftSpell( 50171 );
			else
				pTarget->RemoveShapeShiftSpell( 50171 );
		}break;
	case 48396: //Druid:Improved Moonkin Form
		{
			if( !m_target->IsPlayer() )
			{ 
				return;
			}

			Player * pTarget = SafePlayerCast(m_target);
			if( apply )
				pTarget->AddShapeShiftSpell( 50172 );
			else
				pTarget->RemoveShapeShiftSpell( 50172 );
		}break;
	case 31223:
	case 31222:
	case 31221:		// Rogue : Master of Subtlety
		{
			if( !m_target->IsPlayer() )
			{ 
				return;
			}

			Player * pTarget = SafePlayerCast(m_target);
			if( apply )
			{
				pTarget->m_outStealthDamageBonusPct += mod->m_amount;
				pTarget->m_outStealthDamageBonusPeriod = 6;			// 6 seconds
				pTarget->m_outStealthDamageBonusTimer = 0;			// reset it
			}
			else
			{
				pTarget->m_outStealthDamageBonusPct -= mod->m_amount;
				pTarget->m_outStealthDamageBonusPeriod = 6;			// 6 seconds
				pTarget->m_outStealthDamageBonusTimer = 0;			// reset it
			}
		}break;
	case 17804: // Warlock: Soul Siphon
	case 17805:
		{
			Unit *caster = GetUnitCaster();
			if(caster) {
				if( apply )
					caster->m_soulSiphon.amt+= mod->m_amount;
				else
					caster->m_soulSiphon.amt-= mod->m_amount;
			}
		}break;
	}
	if ( TamingSpellid && ! GetTimeLeft() )
	{
		// Creates a 15 minute pet, if player has the quest that goes with the spell and if target corresponds to quest
		Player *p_caster =SafePlayerCast(GetUnitCaster());
		SpellEntry *triggerspell = dbcSpell.LookupEntry( TamingSpellid );
		Quest* tamequest = QuestStorage.LookupEntry( triggerspell->EffectMiscValue[1] );
		if ( p_caster->GetQuestLogForEntry(tamequest->id )&& m_target->GetEntry() == tamequest->required_mob[0] )
		{
			if( Rand( 75.0f ) )// 75% chance on success
			{
				Creature *tamed = ( ( m_target->GetTypeId() == TYPEID_UNIT ) ? ( SafeCreatureCast(m_target) ) : 0 );
				QuestLogEntry *qle = p_caster->GetQuestLogForEntry(tamequest->id );

				tamed->GetAIInterface()->HandleEvent( EVENT_LEAVECOMBAT, p_caster, 0 );
				Pet *pPet = objmgr.CreatePet( tamed->GetEntry(), p_caster->GeneratePetNumber() );
				pPet->SetInstanceID( p_caster->GetInstanceID() );
				pPet->CreateAsSummon( tamed->GetEntry(), tamed->GetCreatureInfo(), tamed, p_caster, triggerspell, 2, 900000 );
				pPet->CastSpell( tamed, triggerspell, false );
				tamed->SafeDelete();
				qle->SetMobCount( 0, 1 );
				qle->SendUpdateAddKill( 1 );
				qle->UpdatePlayerFields();
				qle->SendQuestComplete();
			}
			else
			{
				p_caster->SendCastResult( triggerspell->Id,SPELL_FAILED_TRY_AGAIN,0,0 );
			}
		}
		else
		{
			p_caster->SendCastResult( triggerspell->Id,SPELL_FAILED_BAD_TARGETS,0,0 );
		}
		TamingSpellid = 0;
	}
}

void Aura::SpellAuraModConfuse(bool apply)
{
	Unit* u_caster = GetUnitCaster();

	if( m_target->IsCreature() && SafeCreatureCast(m_target)->IsTotem() )
	{ 
		return;
	}

	if(apply)
	{
		if( u_caster == NULL ) 
		{ 
			return;
		}

		// Check Mechanic Immunity
		mod->fixed_amount[0] = 0; //not immune
		if( m_target )
		{
			if( m_target->MechanicsDispels[MECHANIC_DISORIENTED]
			|| ( m_spellProto->MechanicsType == MECHANIC_POLYMORPHED && m_target->MechanicsDispels[MECHANIC_POLYMORPHED] )
			)
			{
				mod->fixed_amount[0] = 1; //immune
				return;
			}
		}
		SetNegative();

		m_target->m_special_state |= UNIT_STATE_CONFUSE;
		m_target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);

		m_target->setAItoUse(true);
		m_target->GetAIInterface()->HandleEvent(EVENT_WANDER, u_caster, 0);

		if(p_target)
		{
			// this is a hackfix to stop player from moving -> see AIInterface::_UpdateMovement() Wander AI for more info
			WorldPacket data1(9);
			data1.Initialize( SMSG_CLIENT_CONTROL_UPDATE );
			data1 << m_target->GetNewGUID() << uint8(0x00);
			p_target->GetSession()->SendPacket(&data1);
			p_target->SpeedCheatDelay( GetDuration() );
		}
	}
	else if( mod->fixed_amount[0] == 0 ) //add these checks to mods where imunity can cancel only 1 mod and not whole spell
	{
		m_target->m_special_state &= ~UNIT_STATE_CONFUSE;
		m_target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
		if( p_target )
			p_target->SpeedCheatReset();

		m_target->GetAIInterface()->HandleEvent( EVENT_UNWANDER, NULL, 0 );

		if(p_target)
		{
			// re-enable movement
			WorldPacket data1(9);
			data1.Initialize( SMSG_CLIENT_CONTROL_UPDATE );
			data1 << m_target->GetNewGUID() << uint8(0x01);
			p_target->GetSession()->SendPacket(&data1);

			m_target->setAItoUse(false);

			if( u_caster != NULL )
				sHookInterface.OnEnterCombat( p_target, u_caster );
		}
		else
			m_target->GetAIInterface()->AttackReaction(u_caster, 1, 0);
		//some clients somehow do not stop moving after getting back client control
		m_target->GetAIInterface()->StopMovement( 0 );
	}
}

void Aura::SpellAuraModCharm(bool apply)
{
	Unit* ucaster = GetUnitCaster();

	if( ucaster == NULL || ucaster->IsPlayer() == false )
		return;

	Player* caster = SafePlayerCast( ucaster );
	Creature* target = SafeCreatureCast( m_target );

	SetPositive(3); //we ignore the other 2 effect of this spell and force it to be a positive spell

	//!!!! AMG fix this. We are removed while we are handling aura !!! This is mem corruption
	if( m_target == NULL || m_target->GetTypeId() != TYPEID_UNIT )
	{ 
		return;
	}

	if( SafeCreatureCast( m_target )->IsTotem() )
	{ 
		return;
	}

	if( apply )
	{
		if( (int32)m_target->getLevel() > mod->m_amount || m_target->IsPet() )
		{ 
			return;
		}

		// this should be done properly
		if( target->GetEnslaveCount() >= 10 )
		{ 
			return;
		}

		if( caster->GetUInt64Value( UNIT_FIELD_CHARM ) != 0 )
		{ 
			return;
		}

		m_target->m_special_state |= UNIT_STATE_CHARM;
		m_target->SetCharmTempVal( m_target->GetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE ) );
		m_target->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, caster->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
		m_target->_setFaction();
//		m_target->UpdateOppFactionSet();
		m_target->GetAIInterface()->Init(m_target, AITYPE_PET, MOVEMENTTYPE_NONE, caster);
		m_target->SetUInt64Value(UNIT_FIELD_CHARMEDBY, caster->GetGUID());
		caster->SetUInt64Value(UNIT_FIELD_CHARM, target->GetGUID());
		//damn it, the other effects of enslaive demon will agro him on us anyway :S
		m_target->GetAIInterface()->WipeHateList();
		m_target->GetAIInterface()->WipeTargetList();
		m_target->GetAIInterface()->SetNextTarget( (Unit*)NULL);

		target->SetEnslaveCount(target->GetEnslaveCount() + 1);

		if( caster->GetSession() ) // crashfix
		{
			WorldPacket data(SMSG_PET_SPELLS, 500);
			data << target->GetGUID();
			data << uint16(1) << uint32(0) << uint32(0x1000);
			data << uint32(PET_SPELL_ATTACK);
			data << uint32(PET_SPELL_FOLLOW);
			data << uint32(PET_SPELL_STAY);
			for(int i = 0; i < 4; i++)
				data << uint32(0);
			data << uint32(PET_SPELL_AGRESSIVE);
			data << uint32(PET_SPELL_DEFENSIVE);
			data << uint32(PET_SPELL_PASSIVE);
			caster->GetSession()->SendPacket(&data);
			target->SetEnslaveSpell(m_spellProto->Id);
		}
	}
	else
	{
		m_target->m_special_state &= ~UNIT_STATE_CHARM;
		m_target->SetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE, m_target->GetCharmTempVal() );
		m_target->_setFaction();
		m_target->GetAIInterface()->WipeHateList();
		m_target->GetAIInterface()->WipeTargetList();
//		m_target->UpdateOppFactionSet();
		m_target->GetAIInterface()->Init(m_target, AITYPE_AGRO, MOVEMENTTYPE_NONE);
		m_target->SetUInt64Value(UNIT_FIELD_CHARMEDBY, 0);

		if( caster != NULL && caster->GetSession() != NULL ) // crashfix
		{
			caster->SetUInt64Value(UNIT_FIELD_CHARM, 0);
			WorldPacket data(SMSG_PET_SPELLS, 8);
			data << uint64(0);
			data << uint32(0);
			caster->GetSession()->SendPacket(&data);
			target->SetEnslaveSpell(0);
		}
	}
}

void Aura::SpellAuraModFear(bool apply)
{
	Unit* u_caster = GetUnitCaster();

	if( m_target->IsCreature() && SafeCreatureCast(m_target)->IsTotem() )
	{ 
		return;
	}

	if(apply)
	{
		if( u_caster == NULL ) 
		{ 
			return;
		}
		// Check Mechanic Immunity
		if( m_target )
		{
			if( m_target->MechanicsDispels[MECHANIC_FLEEING] )
			{
				m_flags |= 1 << mod->i;
				return;
			}
		}

		SetNegative();

		m_target->m_special_state |= UNIT_STATE_FEAR;
		m_target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_FLEEING);

		m_target->setAItoUse(true);
		m_target->GetAIInterface()->HandleEvent(EVENT_FEAR, u_caster, 0);
		m_target->m_fearmodifiers++;
		if(p_target)
		{
			// this is a hackfix to stop player from moving -> see AIInterface::_UpdateMovement() Fear AI for more info
			WorldPacket data1(9);
			data1.Initialize( SMSG_CLIENT_CONTROL_UPDATE );
			data1 << m_target->GetNewGUID() << uint8(0x00);
			p_target->GetSession()->SendPacket(&data1);
			p_target->SpeedCheatDelay( GetDuration() );
		}
	}
	else if( (m_flags & (1 << mod->i)) == 0 ) //add these checks to mods where imunity can cancel only 1 mod and not whole spell
	{
		m_target->m_fearmodifiers--;

		if(m_target->m_fearmodifiers <= 0)
		{
			m_target->m_special_state &= ~UNIT_STATE_FEAR;
			m_target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_FLEEING);

			m_target->GetAIInterface()->HandleEvent( EVENT_UNFEAR, NULL, 0 );

			if(p_target)
			{
				// re-enable movement
				WorldPacket data1(9);
				data1.Initialize( SMSG_CLIENT_CONTROL_UPDATE );
				data1 << m_target->GetNewGUID() << uint8(0x01);
				p_target->GetSession()->SendPacket(&data1);

				m_target->setAItoUse(false);

				if( u_caster != NULL )
					sHookInterface.OnEnterCombat( p_target, u_caster );
				p_target->SpeedCheatReset();
			}
			else
				m_target->GetAIInterface()->AttackReaction(u_caster, 1, 0);
		}

		//hackfix
		if( GetSpellProto()->NameHash == SPELL_HASH_PSYCHIC_SCREAM && u_caster && u_caster->IsPlayer() )
		{
			uint32 procspell = 0;
			if( SafePlayerCast(u_caster)->HasSpell( 47572 ) )
				procspell = 59980;
			else if( SafePlayerCast(u_caster)->HasSpell( 47571 ) )
				procspell = 59981;
			if( procspell )
			{
				SpellEntry* spellInfo = dbcSpell.LookupEntry( procspell );
				Spell* spell = SpellPool.PooledNew();
				spell->Init( u_caster, spellInfo, true, NULL );
				SpellCastTargets targets( m_target->GetGUID() );
				spell->prepare( &targets );
			}
		}
		//some clients somehow do not stop moving after getting back client control
		m_target->GetAIInterface()->StopMovement( 0 );
	}
}

void Aura::SpellAuraPeriodicHeal( bool apply )
{
	if( apply )
	{
		SetPositive();

		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHaste() );
		}
		if( period < 500 )
			period = 500;

		mod->fixed_amount[0] = period;	//need this for Swiftmend to take into count hasting
		sEventMgr.AddEvent( this, &Aura::EventPeriodicHeal,(uint32)mod->m_amount,period, EVENT_AURA_PERIODIC_HEAL, period , 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );

		if( GetSpellProto()->NameHash == SPELL_HASH_REJUVENATION || GetSpellProto()->NameHash == SPELL_HASH_REGROWTH )
		{
			m_target->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_REJUVENATE);
			if(!sEventMgr.HasEvent( m_target, EVENT_REJUVENATION_FLAG_EXPIRE ) )
			{
				sEventMgr.AddEvent( m_target, &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_REJUVENATE, EVENT_REJUVENATION_FLAG_EXPIRE, GetDuration(), 1, 0 );
			}
			else
			{
				sEventMgr.ModifyEventTimeLeft( m_target,EVENT_REJUVENATION_FLAG_EXPIRE, GetDuration() );
			}
		}
	}
}

void Aura::EventPeriodicHeal( uint32 amount,int32 period )
{
	if( m_target==NULL || !m_target->isAlive() )
	{ 
		return;
	}

	Unit* c = GetUnitCaster();

	int32 bonus = 0;
	int32 add = 0;

	if( c != NULL)
	{ 
		//ver 2
		bonus += c->GetSpellHealBonus( m_target, GetSpellProto(), amount, GetSpellProto()->quick_tickcount );
		if ( (GetSpellProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) )
			SM_PIValue(c->SM_PDOT,&bonus,m_spellProto->SpellGroupType);

		add = bonus + amount;

		if( add < 0 )
			add = 0;
		c->HandleProc( PROC_ON_HEAL_SPELL | PROC_ON_SPELL_HIT, m_target, GetSpellProto(), add ,0 );

		//!!handleproc removed us !!
		if( m_target == NULL )
			return;
	}

	SendPeriodicHealAuraLog( add );

	uint32 curHealth = m_target->GetUInt32Value(UNIT_FIELD_HEALTH);
	uint32 maxHealth = m_target->GetUInt32Value(UNIT_FIELD_MAXHEALTH);

	if((curHealth + add) >= maxHealth)
	{
		add = maxHealth - curHealth;
	}

	if (add > 0)
		m_target->ModUnsigned32Value(UNIT_FIELD_HEALTH, add);

	m_target->RemoveAurasByHeal();
	//self nutkick !
	if( m_target == NULL )
		return;

	if( GetSpellProto()->AuraInterruptFlags & AURA_INTERRUPT_ON_STAND_UP )
	{
		m_target->Emote( EMOTE_ONESHOT_EAT );
	}

	// add threat
	Unit* u_caster = this->GetUnitCaster();
	if( u_caster != NULL )
	{
		if (GetSpellProto()->NameHash == SPELL_HASH_HEALTH_FUNNEL && add > 0) 
		{
			dealdamage sdmg;

			sdmg.full_damage = add;
			sdmg.resisted_damage = 0;
			sdmg.school_type = 0;
			u_caster->DealDamage(u_caster, add, 0, 0, 0);
			u_caster->SendAttackerStateUpdate(u_caster, u_caster, &sdmg, add, 0, 0, 0, ATTACK);
		}

		std::vector<Unit*> target_threat;
		int count = 0;
		for(std::set<Object*>::iterator itr = u_caster->GetInRangeSetBegin(); itr != u_caster->GetInRangeSetEnd(); ++itr)
		{
			if((*itr)->GetTypeId() != TYPEID_UNIT || !SafeUnitCast(*itr)->CombatStatus.IsInCombat() || (SafeUnitCast(*itr)->GetAIInterface()->getThreatByPtr(u_caster) == 0 && SafeUnitCast(*itr)->GetAIInterface()->getThreatByPtr(m_target) == 0))
				continue;

			target_threat.push_back(SafeUnitCast(*itr));
			count++;
		}
		if (count == 0)
		{ 
			return;
		}

		add = add / count;

		for(std::vector<Unit*>::iterator itr = target_threat.begin(); itr != target_threat.end(); ++itr)
		{
			SafeUnitCast(*itr)->GetAIInterface()->HealReaction(u_caster, m_target, m_spellProto, add);
		}

		if(m_target && m_target->IsInWorld() && u_caster->IsInWorld())
			u_caster->CombatStatus.WeHealed(m_target);
	}
}

void Aura::SpellAuraModAttackSpeed( bool apply )
{
	if( mod->m_amount < 0 )
		SetNegative();
	else
		SetPositive();

	if ( m_target->GetTypeId() == TYPEID_PLAYER )
	{
		if(apply)
		{

			SafePlayerCast( m_target )->ModAttackSpeed( mod->m_amount, MOD_MELEE );
			SafePlayerCast( m_target )->ModAttackSpeed( mod->m_amount, MOD_RANGED );
		}
		else
		{
			SafePlayerCast( m_target )->ModAttackSpeed( -mod->m_amount, MOD_MELEE );
			SafePlayerCast( m_target )->ModAttackSpeed( -mod->m_amount, MOD_RANGED );
		}
		SafePlayerCast( m_target )->UpdateStats();
	}
	else
	{
		if(apply)
		{
			mod->fixed_amount[0] = m_target->GetModPUInt32Value(UNIT_FIELD_BASEATTACKTIME,mod->m_amount);
			mod->fixed_amount[1] = m_target->GetModPUInt32Value(UNIT_FIELD_BASEATTACKTIME_1,mod->m_amount);
			mod->fixed_amount[2] = m_target->GetModPUInt32Value(UNIT_FIELD_RANGEDATTACKTIME,mod->m_amount);
			m_target->ModUnsigned32Value(UNIT_FIELD_BASEATTACKTIME, -mod->fixed_amount[0]);
			m_target->ModUnsigned32Value(UNIT_FIELD_BASEATTACKTIME_1, -mod->fixed_amount[1]);
			m_target->ModUnsigned32Value(UNIT_FIELD_RANGEDATTACKTIME, -mod->fixed_amount[2]);
		}
		else
		{
			m_target->ModUnsigned32Value(UNIT_FIELD_BASEATTACKTIME, mod->fixed_amount[0]);
			m_target->ModUnsigned32Value(UNIT_FIELD_BASEATTACKTIME_1, mod->fixed_amount[1]);
			m_target->ModUnsigned32Value(UNIT_FIELD_RANGEDATTACKTIME, mod->fixed_amount[2]);
		}
	}

}

void Aura::SpellAuraModThreatGeneratedSchoolPCT(bool apply)
{
	if(!m_target)
	{ 
		return;
	}

	mod->m_amount < 0 ? SetPositive() : SetNegative();
	for( uint32 x = 0; x < 7; x++ )
	{
		if( mod->m_miscValue & ( ( (uint32)1 ) << x ) )
		{
			if ( apply )
				m_target->ModGeneratedThreatModifyerPCT(x, mod->m_amount);
			else
				m_target->ModGeneratedThreatModifyerPCT(x, -(mod->m_amount));
		}
	}
}

void Aura::SpellAuraModTaunt(bool apply)
{
	Unit* m_caster = GetUnitCaster();
	if(!m_caster || !m_caster->isAlive())
	{ 
		return;
	}

	SetNegative();

	if(apply)
	{
		m_target->GetAIInterface()->AttackReaction(m_caster, 1, 0);
		m_target->GetAIInterface()->taunt(m_caster, true);
	}
	else
	{
		if(m_target->GetAIInterface()->getTauntedBy() == m_caster)
		{
			m_target->GetAIInterface()->taunt(m_caster, false);
		}
	}
}

void Aura::SpellAuraModStun(bool apply)
{
	if(!m_target) 
	{ 
		return;
	}

	if(apply)
	{
		// Check Mechanic Immunity
		// Stun is a tricky one... it's used for all different kinds of mechanics as a base Aura
		if( m_target && !IsPositive() && m_spellProto->NameHash != SPELL_HASH_ICE_BLOCK )  // ice block stuns you, don't want our own spells to ignore stun effects
		{
			if( ( m_spellProto->MechanicsType == MECHANIC_CHARMED &&  m_target->MechanicsDispels[MECHANIC_CHARMED] )
			|| ( m_spellProto->MechanicsType == MECHANIC_INCAPACIPATED && m_target->MechanicsDispels[MECHANIC_INCAPACIPATED] )

			|| ( m_spellProto->MechanicsType == MECHANIC_SAPPED && m_target->MechanicsDispels[MECHANIC_SAPPED] )
			|| ( m_target->MechanicsDispels[MECHANIC_STUNNED] )
				)
			{
				m_flags |= 1 << mod->i;
				return;
			}
		}
		SetNegative();

		m_target->m_rooted++;

		if(m_target->m_rooted == 1)
			m_target->Root();

		if (m_target->IsStealth())
			m_target->RemoveStealth();

		m_target->m_stunned++;
		m_target->m_special_state |= UNIT_STATE_STUN;
		m_target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);

		if(m_target->GetTypeId() == TYPEID_UNIT)
			m_target->GetAIInterface()->SetNextTarget( (Unit*)NULL );

		// remove the current spell (for channelers)
		if(m_target->m_currentSpell && m_target->GetGUID() != m_casterGuid &&
			m_target->m_currentSpell->getState() == SPELL_STATE_CASTING )
		{
			m_target->m_currentSpell->safe_cancel();
			//remove periodic casted beneficial spell -> report was for starfall but i guees it should be the same for other periodic spells ?
			for(uint32 x=FIRST_AURA_SLOT;x<MAX_POSITIVE_AURAS;x++)
				if( m_target->m_auras[x] && m_target->m_auras[x]->GetSpellProto()->quick_tickcount > 1 )
					m_target->m_auras[x]->Remove();
		}

		//warrior talent - second wind triggers on stun and immobilize. This is not used as proc to be triggered always !
		Unit *caster = GetUnitCaster();
		if( caster && m_target )
			SafeUnitCast(caster)->EventStunOrImmobilize( m_target );
		if( m_target && caster )
			SafeUnitCast(m_target)->EventStunOrImmobilize( caster, true );
		if (m_target->isCasting())
			m_target->CancelSpell(NULL); //cancel spells.
	}
	else if( (m_flags & (1 << mod->i)) == 0 ) //add these checks to mods where imunity can cancel only 1 mod and not whole spell
	{
		m_target->m_rooted--;

		if(m_target->m_rooted == 0)
			m_target->Unroot();

		m_target->m_stunned--;

		if(m_target->m_stunned == 0)
		{
			m_target->m_special_state &= ~UNIT_STATE_STUN;
			m_target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
		}

		// attack them back.. we seem to lose this sometimes for some reason
		if(m_target->GetTypeId() == TYPEID_UNIT)
		{
			Unit * target = GetUnitCaster();
			if(m_target->GetAIInterface()->GetNextTarget() != 0)
				target = m_target->GetAIInterface()->GetNextTarget();

			if(!target) 
			{ 
				return;
			}
			m_target->GetAIInterface()->AttackReaction(target, 1, 0);
		}
	}

/*
	if(apply)
	{
		switch(this->m_spellProto->Id)
		{
		case 652:
		case 2070:
		case 6770:
		case 6771:
		case 11297:
		case 11298:
			{
				// sap
				Unit *c = GetUnitCaster();
				if(c)
					c->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_START_ATTACK);  // remove stealth
			}break;
		case 1776:
		case 1777:
		case 1780:
		case 1781:
		case 8629:
		case 8630:
		case 11285:
		case 11286:
		case 11287:
		case 11288:
		case 12540:
		case 13579:
		case 24698:
		case 28456:
			{
				// gouge
				Unit *c = GetUnitCaster();
				if(c && c->GetTypeId() == TYPEID_PLAYER)
				{
					//SafePlayerCast( c )->CombatModeDelay = 10;
					SafePlayerCast( c )->EventAttackStop();
					c->smsg_AttackStop(m_target);
					c->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_START_ATTACK);  // remove stealth
				}
			}
		}
	}*/
}

void Aura::SpellAuraModDamageDone(bool apply)
{
	int32 val;

//	if( m_target->getClass() == DEATHKNIGHT )
//	{ 
//		return;
//	}

	if( m_target->IsPlayer() )
	{
		uint32 index;

		if( mod->m_amount > 0 )
		{
			if( apply )
			{
				SetPositive();
				val = mod->m_amount;
			}
			else
			{
				val = -mod->m_amount;
			}
			index = PLAYER_FIELD_MOD_DAMAGE_DONE_POS;

		}
		else
		{
			if( apply )
			{
				SetNegative();
				val = -mod->m_amount;
			}
			else
			{
				val = mod->m_amount;
			}
			index = PLAYER_FIELD_MOD_DAMAGE_DONE_NEG;
		}

		for( uint32 x = 0; x < 7; x++ )
		{
			if( mod->m_miscValue & ( ( (uint32)1 ) << x ) )
			{
				m_target->ModUnsigned32Value( index + x, val );
			}
		}
	}
	else if( m_target->GetTypeId() == TYPEID_UNIT )
	{
		if( mod->m_amount > 0 )
		{
			if( apply )
			{
				SetPositive();
				val = mod->m_amount;
			}
			else
			{
				val = -mod->m_amount;
			}

		}
		else
		{
			if( apply )
			{
				SetNegative();
				val = mod->m_amount;
			}
			else
			{
				val = -mod->m_amount;
			}
		}

		for( uint32 x = 0; x < 7; x++ )
		{
			if( mod->m_miscValue & ( ( (uint32)1 ) << x ) )
			{
				SafeCreatureCast( m_target )->ModDamageDone[x] += val;
			}
		}
	}

	if( mod->m_miscValue & 1 )
		m_target->CalcDamage();
}

void Aura::SpellAuraModDamageTaken(bool apply)
{
	int32 val = (apply) ? mod->m_amount : -mod->m_amount;
	for(uint32 x=0;x<7;x++)
	{
		if (mod->m_miscValue & (((uint32)1)<<x) )
		{
			m_target->DamageTakenMod[x]+=val;
		}
	}
}

void Aura::SpellAuraDamageShield(bool apply)
{
	if(apply)
	{
		SetPositive();
		DamageProc ds;// = new DamageShield();
		ds.m_damage = mod->m_amount;
		ds.m_spellId = GetSpellProto()->Id;
		ds.m_school = GetSpellProto()->School;
		ds.m_flags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_SCRIPTED_PROCTEST; //maybe later we might want to add other flags too here
		ds.owner = (void*)this;
		m_target->m_damageShields.push_back(ds);
	}
	else
	{
		for(std::list<struct DamageProc>::iterator i = m_target->m_damageShields.begin();i != m_target->m_damageShields.end();i++)
		{
			if(i->owner==this)
			{
				 m_target->m_damageShields.erase(i);
				 return;
			}
		}
	}
}

void Aura::SpellAuraModStealth(bool apply)
{
	if(apply)
	{
		if(p_target && p_target->m_bgHasFlag)
		{
			if(p_target->m_bg && p_target->m_bg->GetType() == BATTLEGROUND_WARSONG_GULCH)
				static_cast<WarsongGulch*>(p_target->m_bg)->HookOnFlagDrop(p_target);
			else if(p_target->m_bg && p_target->m_bg->GetType() == BATTLEGROUND_EYE_OF_THE_STORM)
				static_cast<EyeOfTheStorm*>(p_target->m_bg)->HookOnFlagDrop(p_target);
	    }
		SetPositive();
		if( m_spellProto->NameHash != SPELL_HASH_VANISH)
			m_target->SetStealth(GetSpellId());

		if( m_spellProto->NameHash == SPELL_HASH_STEALTH)
			m_target->SetFlag(UNIT_FIELD_BYTES_2,0x1E000000);//sneak anim

		m_target->SetFlag(UNIT_FIELD_BYTES_1, 0x020000);
		if( m_target->IsPlayer() )
			m_target->SetFlag(PLAYER_FIELD_BYTES2, 0x2000);

		m_target->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_STEALTH | AURA_INTERRUPT_ON_INVINCIBLE);
		m_target->m_stealthLevel += mod->m_amount;

		// hack fix for vanish stuff
		if( m_spellProto->NameHash == SPELL_HASH_VANISH && m_target->GetTypeId() == TYPEID_PLAYER )	 // Vanish
		{
			for (Object::InRangeSet::iterator iter = m_target->GetInRangeSetBegin();iter != m_target->GetInRangeSetEnd(); ++iter)
			{
				if ((*iter) == NULL || !(*iter)->IsUnit())
					continue;

				if (!SafeUnitCast(*iter)->isAlive())
					continue;

				if (SafeUnitCast(*iter)->GetCurrentSpell() && SafeUnitCast(*iter)->GetCurrentSpell()->GetUnitTarget() == m_target)
					SafeUnitCast(*iter)->GetCurrentSpell()->safe_cancel();

				if(SafeUnitCast(*iter)->GetAIInterface() != NULL )
					SafeUnitCast(*iter)->GetAIInterface()->RemoveThreatByPtr( m_target );
			}			
			for( uint32 x = MAX_POSITIVE_AURAS; x < MAX_NEGATIVE_AURAS1(m_target); x++ )
			{
				if( m_target->m_auras[x] != NULL )
				{
					if( m_target->m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ROOTED || m_target->m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ENSNARED ) // Remove roots and slow spells
					{
						m_target->m_auras[x]->Remove();
					}
					else // if got immunity for slow, remove some that are not in the mechanics
					{
						for( int i = 0; i < 3; i++ )
						{
							uint32 AuraEntry = m_target->m_auras[x]->GetSpellProto()->EffectApplyAuraName[i];
							if( AuraEntry == SPELL_AURA_MOD_DECREASE_SPEED || AuraEntry == SPELL_AURA_MOD_ROOT || AuraEntry == SPELL_AURA_MOD_STALKED)
							{
								m_target->m_auras[x]->Remove();
								break;
							}
						}
					}
				}
			}

			// check for stealh spells
			Player* p_caster = SafePlayerCast( m_target );
			uint32 stealth_id = 0;
			SpellSet::iterator itr = p_caster->mSpells.begin();
			SpellSet::iterator end = p_caster->mSpells.end();
			for(; itr != end; ++itr)
			{
				if(((*itr) == 1787 || (*itr) == 1786 || (*itr) == 1785 || (*itr) == 1784) && stealth_id < (*itr))
				{
					stealth_id = *itr;
				}
			}
			if(stealth_id)
				p_caster->CastSpell(p_caster, dbcSpell.LookupEntry(stealth_id), true);

			if(p_caster->IsMounted())
				p_caster->RemoveAura(p_caster->m_MountSpellId);

			if(p_caster->m_bg && p_caster->m_bgHasFlag)
			{
				if(p_caster->m_bg->GetType() == BATTLEGROUND_WARSONG_GULCH)
					static_cast<WarsongGulch*>(p_caster->m_bg)->HookOnFlagDrop(p_caster);
				if(p_caster->m_bg->GetType() == BATTLEGROUND_EYE_OF_THE_STORM)
					static_cast<EyeOfTheStorm*>(p_caster->m_bg)->HookOnFlagDrop(p_caster);
			 }
		}
	}
	else if(m_spellProto->NameHash != SPELL_HASH_VANISH)
	{
		m_target->SetStealth(0);
		m_target->m_stealthLevel -= mod->m_amount;
		if( m_spellProto->NameHash == SPELL_HASH_STEALTH)
			m_target->RemoveFlag(UNIT_FIELD_BYTES_2,0x1E000000);

		m_target->RemoveFlag(UNIT_FIELD_BYTES_1, 0x020000);

		if( m_target->GetTypeId() == TYPEID_PLAYER )
		{
			m_target->RemoveFlag(PLAYER_FIELD_BYTES2, 0x2000);
			packetSMSG_COOLDOWN_EVENT cd;
			cd.guid = m_target->GetGUID();
			cd.spellid = m_spellProto->Id;
			SafePlayerCast(m_target)->GetSession()->OutPacket( SMSG_COOLDOWN_EVENT, sizeof(packetSMSG_COOLDOWN_EVENT), &cd);
			if( SafePlayerCast(m_target)->m_outStealthDamageBonusPeriod && SafePlayerCast(m_target)->m_outStealthDamageBonusPct )
				SafePlayerCast(m_target)->m_outStealthDamageBonusTimer = (uint32)UNIXTIME + SafePlayerCast(m_target)->m_outStealthDamageBonusPeriod;
		}
	}

	m_target->UpdateVisibility();
}

void Aura::SpellAuraModDetect(bool apply)
{
	if(apply)
	{
		//SetPositive();
		m_target->m_stealthDetectBonus += mod->m_amount;
	}
	else
		m_target->m_stealthDetectBonus -= mod->m_amount;
}

void Aura::SpellAuraModInvisibility(bool apply)
{
	SetPositive();
	if(m_spellProto->Effect[mod->i] == 128)
	{ 
		return;
	}

	if(apply)
	{
		m_target->SetInvisibility(GetSpellId());
		m_target->m_invisFlag = mod->m_miscValue;
		if( m_target->GetTypeId() == TYPEID_PLAYER )
		{
			if( GetSpellProto()->NameHash == SPELL_HASH_INVISIBILITY ) 
				SafePlayerCast(m_target)->SetFlag( PLAYER_FIELD_BYTES2, 0x4000 ); //Mage Invis self visual
		}

		m_target->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_INVINCIBLE);
	}
	else
	{
		m_target->m_invisFlag = INVIS_FLAG_NORMAL;
		if( m_target->GetTypeId() == TYPEID_PLAYER )
		{
			if( GetSpellProto()->NameHash == SPELL_HASH_INVISIBILITY ) 
				SafePlayerCast(m_target)->RemoveFlag( PLAYER_FIELD_BYTES2, 0x4000 );
		}
	}

	m_target->m_invisible = apply;
	m_target->UpdateVisibility();
}

void Aura::SpellAuraModInvisibilityDetection(bool apply)
{
	//Always Positive

	assert(mod->m_miscValue < INVIS_FLAG_TOTAL);
	if(apply)
	{
		m_target->m_invisDetect[mod->m_miscValue] += mod->m_amount;
		SetPositive ();
	}
	else
		m_target->m_invisDetect[mod->m_miscValue] -= mod->m_amount;

	if(m_target->IsPlayer())
		SafePlayerCast( m_target )->UpdateVisibility();
}

void Aura::SpellAuraModTotalHealthRegenPct(bool apply)
{
	if(apply)
	{
		SetPositive();

		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHasteDots() );
		}
		if( period < 500 )
			period = 500;

		//there is gotto be a better way for this. Any ideas ?
/*		if( mod->i == 0 && strstr( "$o1%", GetSpellProto()->Description ) )
			mod->m_amount = mod->m_amount / GetSpellProto()->quick_tickcount;
		else if( mod->i == 1 && strstr( "$o2%", GetSpellProto()->Description ) )
			mod->m_amount = mod->m_amount / GetSpellProto()->quick_tickcount;
		else if( mod->i == 2 && strstr( "$o3%", GetSpellProto()->Description ) )
			mod->m_amount = mod->m_amount / GetSpellProto()->quick_tickcount; */

		sEventMgr.AddEvent(this, &Aura::EventPeriodicHealPct,(float)mod->m_amount,
			EVENT_AURA_PERIODIC_HEALPERC, period ,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

void Aura::EventPeriodicHealPct(float RegenPct)
{
	if(!m_target->isAlive())
	{ 
		return;
	}

	uint32 add = float2int32(m_target->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * (RegenPct / 100.0f));

	uint32 newHealth = m_target->GetUInt32Value(UNIT_FIELD_HEALTH) + add;

	if(newHealth <= m_target->GetUInt32Value(UNIT_FIELD_MAXHEALTH))
		m_target->SetUInt32Value(UNIT_FIELD_HEALTH, newHealth);
	else
		m_target->SetUInt32Value(UNIT_FIELD_HEALTH, m_target->GetUInt32Value(UNIT_FIELD_MAXHEALTH));

//	SendPeriodicAuraLog(m_casterGuid, m_target, m_spellProto->Id, m_spellProto->School, add, 0, 0, FLAG_PERIODIC_HEAL);
	Unit *m_caster = GetUnitCaster();
	if( m_caster && m_target->IsPlayer() )
		SendHealSpellOnPlayer( m_caster, SafePlayerCast( m_target ), add, 0, GetSpellProto() );

	if(GetSpellProto()->AuraInterruptFlags & AURA_INTERRUPT_ON_STAND_UP)
	{
		m_target->Emote(EMOTE_ONESHOT_EAT);
	}

	m_target->RemoveAurasByHeal();
}

void Aura::SpellAuraModTotalManaRegenPct(bool apply)
{
	if(apply)
	{
		SetPositive();

		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHasteDots() );
		}
		if( period < 500 )
			period = 500;

		sEventMgr.AddEvent(this, &Aura::EventPeriodicManaPct,(float)mod->m_amount,
			EVENT_AURA_PERIOCIC_MANA, period ,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

void Aura::EventPeriodicManaPct(float RegenPct)
{
	if(!m_target->isAlive())
	{ 
		return;
	}

	uint32 add = float2int32(m_target->GetUInt32Value(UNIT_FIELD_MAXPOWER1) * (RegenPct / 100.0f));

	uint32 newpower = m_target->GetUInt32Value(UNIT_FIELD_POWER1) + add;

	if(newpower <= m_target->GetUInt32Value(UNIT_FIELD_MAXPOWER1))
		m_target->SetUInt32Value(UNIT_FIELD_POWER1, newpower);
	else
		m_target->SetUInt32Value(UNIT_FIELD_POWER1, m_target->GetUInt32Value(UNIT_FIELD_MAXPOWER1));

	// CAPT
	// TODO: sniff it or disasm wow.exe to find the mana flag
	//SendPeriodicAuraLog(m_target, m_casterGuid, GetSpellProto()->Id, FLAG_PERIODIC_HEAL, add,true);
	//SendPeriodicAuraLog(m_target, m_casterGuid, GetSpellProto()->Id, FLAG_PERIODIC_HEAL, add);

	if(GetSpellProto()->AuraInterruptFlags & AURA_INTERRUPT_ON_STAND_UP)
	{
		m_target->Emote(EMOTE_ONESHOT_EAT);
	}
}

void Aura::SpellAuraModResistance(bool apply)
{
	uint32 Flag = mod->m_miscValue;
	int32 amt;
	if(apply)
	{
		amt = mod->m_amount;
		if(amt <0 )//dont' change it
			SetNegative();
		else
			SetPositive();
	}
	else
		amt = -mod->m_amount;

	if( this->GetSpellProto() && ( this->GetSpellProto()->NameHash == SPELL_HASH_FAERIE_FIRE || this->GetSpellProto()->NameHash == SPELL_HASH_FAERIE_FIRE__FERAL_ ) )
		m_target->m_can_stealth = !apply;

	if( m_target->GetTypeId() == TYPEID_PLAYER )
	{
		for( uint32 x = 0; x < 7; x++ )
		{
			if(Flag & (((uint32)1)<< x) )
			{
				if(mod->m_amount>0)
					SafePlayerCast( m_target )->FlatResistanceModifierPos[x]+=amt;
				else
					SafePlayerCast( m_target )->FlatResistanceModifierNeg[x]-=amt;
				SafePlayerCast( m_target )->CalcResistance(x);
			}
		}
	}
	else if(m_target->GetTypeId() == TYPEID_UNIT)
	{
		for(uint32 x=0;x<7;x++)
		{
			if(Flag & (((uint32)1)<<x))
			{
				SafeCreatureCast(m_target)->FlatResistanceMod[x]+=amt;
				SafeCreatureCast(m_target)->CalcResistance(x);
			}
		}
	}
}

void Aura::SpellAuraPeriodicTriggerSpell(bool apply)
{
	if(m_spellProto->EffectTriggerSpell[mod->i] == 0)
	{ 
		return;
	}

	/*
	// This should be fixed in other way...
	if(IsPassive() &&
		m_spellProto->dummy != 2010 &&
		m_spellProto->dummy != 2020 &&
		m_spellProto->dummy != 2255 &&
		m_spellProto->Id != 8145 &&
		m_spellProto->Id != 8167 &&
		m_spellProto->Id != 8172)
	{
		Unit * target = (m_target != 0) ? m_target : GetUnitCaster();
		if(target == 0 || !target->IsPlayer())
			return; //what about creatures ?

		SpellEntry *proto = dbcSpell.LookupEntry( m_spellProto->EffectTriggerSpell[mod->i] );

		if( apply )
			SafePlayerCast( target )->AddOnStrikeSpell( proto, m_spellProto->EffectAmplitude[mod->i] );
		else
			SafePlayerCast( target )->RemoveOnStrikeSpell( proto );

		return;
	}
			*/

	if(apply)
	{
		//FIXME: positive or negative?
		uint32 sp = GetSpellProto()->EffectTriggerSpell[mod->i];
		SpellEntry *spe = dbcSpell.LookupEntry(sp);
		if(!sp || !spe)
		{
			//	sp=22845;
			return;//null spell
		}

		Unit *m_caster = GetUnitCaster();
		if(!m_caster)
		{ 
			return;
		}

		if ( GetSpellProto()->Id == 23493 || GetSpellProto()->Id == 24379 )
			// Cebernic: Restoration on battleground fixes(from p2wow's merged)
			// it wasn't prefectly,just for tempfix
		{
			SetPositive();
			sEventMgr.AddEvent(this, &Aura::EventPeriodicHealPct,10.0f,
			EVENT_AURA_PERIODIC_HEALPERC,	GetSpellProto()->EffectAmplitude[mod->i],0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

			sEventMgr.AddEvent(this, &Aura::EventPeriodicManaPct,10.0f,
			EVENT_AURA_PERIOCIC_MANA,	GetSpellProto()->EffectAmplitude[mod->i],0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			return;
		}

		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			//atm only missle barrage has this 
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHasteDots() );
		}
		if( period < 500 )
			period = 500;

		if(m_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT))
		{
			sEventMgr.AddEvent(this, &Aura::EventPeriodicTriggerSpell, spe, (int32)0,m_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT),
			EVENT_AURA_PERIODIC_TRIGGERSPELL, period , 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

//            periodic_target = m_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT);
		}
		else if(m_target)
		{
			sEventMgr.AddEvent(this, &Aura::EventPeriodicTriggerSpell, spe, (int32)0,m_target->GetGUID(),
				EVENT_AURA_PERIODIC_TRIGGERSPELL, period , 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
//			periodic_target = m_target->GetGUID();
		}
	}
//	else
//		sEventMgr.RemoveEvents( this, EVENT_AURA_PERIODIC_TRIGGERSPELL ); //i hope we will not remove other mods of this aura too

}

void Aura::SpellAuraPeriodicTriggerSpellWithValue(bool apply)
{
	if(m_spellProto->EffectTriggerSpell[mod->i] == 0)
	{ 
		return;
	}
	if(apply)
	{
		uint32 sp = GetSpellProto()->EffectTriggerSpell[mod->i];
		SpellEntry *spe = dbcSpell.LookupEntry(sp);
		if(!sp || !spe)
			return; // invalid spell

		Unit *m_caster = GetUnitCaster();
		if(!m_caster)
			return; // invalid caster

		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			//atm only missle barrage has this 
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHasteDots() );
		}
		if( period < 500 )
			period = 500;

		if(m_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT))
		{
			sEventMgr.AddEvent(this, &Aura::EventPeriodicTriggerSpell, spe, (int32)mod->m_amount,m_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT),
			EVENT_AURA_PERIODIC_TRIGGERSPELL,period, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
//			periodic_target = m_caster->GetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT);
		}
		else if(m_target)
		{
			sEventMgr.AddEvent(this, &Aura::EventPeriodicTriggerSpell, spe,(int32)mod->m_amount,m_target->GetGUID(),
				EVENT_AURA_PERIODIC_TRIGGERSPELL,period, 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
//			periodic_target = m_target->GetGUID();
		}
	}
}

void Aura::EventPeriodicTriggerSpell(SpellEntry* spellInfo,int32 value_overwrite, uint64 periodic_target)
{
	// Trigger Spell
	// check for spell id
	Unit *m_caster=GetUnitCaster();
	if(!m_caster || !m_caster->IsInWorld())
	{ 
		return;
	}

	//sniper training cast condition is to stand still for 6 seconds
	if( spellInfo->NameHash == SPELL_HASH_SNIPER_TRAINING && m_caster->IsPlayer() )
	{
		Player *p = SafePlayerCast(m_caster);
		if( p->last_moved + 6000 > getMSTime() )
			return;
		//avoid packet spam ? This spell is casted every second ...
//		if( p->HasAurasWithNameHash( SPELL_HASH_SNIPER_TRAINING ) )
//			return;
	}
	if( spellInfo->EffectImplicitTargetA[0] == EFF_TARGET_LOCATION_TO_SUMMON )			// Hellfire, if there are any others insert here
	{
		Spell *spell = SpellPool.PooledNew();
		spell->Init(m_caster, spellInfo, true, this);
		if( value_overwrite )
			spell->forced_basepoints[ 0 ] = value_overwrite;
		SpellCastTargets targets;
		targets.m_targetMask = TARGET_FLAG_SOURCE_LOCATION;
		targets.m_srcX = m_caster->GetPositionX();
		targets.m_srcY = m_caster->GetPositionY();
		targets.m_srcZ = m_caster->GetPositionZ();
		spell->prepare(&targets);
		return;
	}

	Object * oTarget = m_target->GetMapMgr()->_GetObject(periodic_target);

	if(oTarget==NULL)
	{ 
		return;
	}

	if(oTarget->GetTypeId()==TYPEID_DYNAMICOBJECT)
	{
		Spell *spell = SpellPool.PooledNew();
		spell->Init(m_caster, spellInfo, true, this);
		if( value_overwrite )
			spell->forced_basepoints[ 0 ] = value_overwrite;
		SpellCastTargets targets;
		targets.m_targetMask = TARGET_FLAG_DEST_LOCATION;
		targets.m_destX = oTarget->GetPositionX();
		targets.m_destY = oTarget->GetPositionY();
		targets.m_destZ = oTarget->GetPositionZ();
		spell->prepare(&targets);
		return;
	}

	Unit *pTarget = SafeUnitCast(oTarget);

	if(!oTarget->IsUnit())
	{ 
		return;
	}

	if(pTarget->IsDead())
	{
		SendInterrupted(SPELL_FAILED_TARGETS_DEAD, m_caster);
		SendChannelUpdate(0, m_caster);
//		this->Remove();
		return;
	}

	//maybe there are beneficial periodic spells too ?
	if(pTarget != m_caster && !isAttackable(m_caster, pTarget)
		&& (spellInfo->c_is_flags & SPELL_FLAG_IS_DAMAGING) 
		)
	{
		SendInterrupted(SPELL_FAILED_BAD_TARGETS, m_caster);
		SendChannelUpdate(0, m_caster);
		this->Remove();
		return;
	}

	if(spellInfo->NameHash == SPELL_HASH_ARCANE_MISSILES ) // this is arcane missles to avoid casting on self
		if(m_casterGuid == pTarget->GetGUID())
		{ 
			return;
		}

	// set up our max Range
	float maxRange = GetMaxRange( dbcSpellRange.LookupEntry( spellInfo->rangeIndex ) );

	if( (GetSpellProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) )
	{
		SM_FFValue( m_caster->SM_FRange, &maxRange, spellInfo->SpellGroupType );
		SM_PFValue( m_caster->SM_PRange, &maxRange, spellInfo->SpellGroupType );
	}

	if( 
		m_caster != pTarget && //self stun like something explodes in hand
		( m_caster->IsStunned() || m_caster->IsFeared() || m_caster->GetDistance2dSq( pTarget ) > ( maxRange*maxRange ) ) )
	{
		if( maxRange == 0 )
			sLog.outDebug("Spell has range = 0. Aborting cast \n");
		// no longer valid
		SendInterrupted(SPELL_FAILED_INTERRUPTED, m_caster);
		SendChannelUpdate(0, m_caster);
		this->Remove();
		return;
	}

	Spell *spell = SpellPool.PooledNew();
	spell->Init(m_caster, spellInfo, true, this);
	spell->ProcedOnSpell = GetSpellProto();
	if( value_overwrite )
		spell->forced_basepoints[ 0 ] = value_overwrite;
	SpellCastTargets targets( pTarget->GetGUID() );
	spell->prepare(&targets);
}

void Aura::SpellAuraPeriodicEnergize(bool apply)
{
	if(apply)
	{
		SetPositive();

		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHasteDots() );
		}
		if( period < 500 )
			period = 500;

		sEventMgr.AddEvent(this, &Aura::EventPeriodicEnergize,(uint32)mod->m_amount,(uint32)mod->m_miscValue,
			EVENT_AURA_PERIODIC_ENERGIZE, period ,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

void Aura::EventPeriodicEnergize( uint32 amount, uint32 type )
{
	uint32 POWER_TYPE = UNIT_FIELD_POWER1 + type;

//	ASSERT( POWER_TYPE <= UNIT_FIELD_POWER5 );

	if( POWER_TYPE > UNIT_FIELD_POWER7 )
		return;

	if( GetUnitCaster() == NULL )
	{ 
		return;
	}
	
	GetUnitCaster()->Energize( m_target, m_spellProto->Id, amount, type );

	if( ( GetSpellProto()->AuraInterruptFlags & AURA_INTERRUPT_ON_STAND_UP ) && type == POWER_TYPE_MANA )
	{
		m_target->Emote( EMOTE_ONESHOT_EAT );
	}
}

void Aura::SpellAuraModPacify(bool apply)
{
	// Can't Attack
	if( apply )
	{
		if( m_spellProto->Id == 24937 || m_spellProto->NameHash == SPELL_HASH_BLESSING_OF_PROTECTION )
			SetPositive();
		else
			SetNegative();

		m_target->m_pacified++;
		m_target->m_special_state |= UNIT_STATE_PACIFY;
		m_target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
	}
	else
	{
		m_target->m_pacified--;

		if(m_target->m_pacified == 0)
		{
			m_target->m_special_state &= ~UNIT_STATE_PACIFY;
			m_target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
		}
	}
}

void Aura::SpellAuraModRoot(bool apply)
{
	if(apply)
	{
		// Check Mechanic Immunity
		if( m_target )
		{
			if( m_target->MechanicsDispels[MECHANIC_ROOTED] )
			{
				m_flags |= 1 << mod->i;
				return;
			}
		}
		SetNegative();

		m_target->m_rooted++;

		if(m_target->m_rooted == 1)
			m_target->Root();

		//warrior talent - second wind triggers on stun and immobilize. This is not used as proc to be triggered always !
		Unit *caster = GetUnitCaster();
		if( caster && m_target )
			SafeUnitCast(caster)->EventStunOrImmobilize( m_target );
		if( m_target && caster )
			SafeUnitCast(m_target)->EventStunOrImmobilize( caster, true );
		if (m_target->isCasting())
			m_target->CancelSpell(NULL); //cancel spells.

		if( m_target->IsUnit() && GetSpellProto()->School == SCHOOL_FROST )
			m_target->SetFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_FROZEN );

		/* -Supalosa- TODO: Mobs will attack nearest enemy in range on aggro list when rooted. */
	}
	else if( (m_flags & (1 << mod->i)) == 0 ) //add these checks to mods where imunity can cancel only 1 mod and not whole spell
	{
		m_target->m_rooted--;

		if(m_target->m_rooted == 0)
			m_target->Unroot();

		if(m_target->GetTypeId() == TYPEID_UNIT)
			m_target->GetAIInterface()->AttackReaction(GetUnitCaster(), 1, 0);

		if( GetSpellProto()->School == SCHOOL_FROST )
			m_target->RemoveFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_FROZEN );
	}
}

void Aura::SpellAuraModSilence(bool apply)
{
	if(apply)
	{
		m_target->m_silenced++;
		m_target->m_special_state |= UNIT_STATE_SILENCE;
		m_target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SILENCED);

		// remove the current spell (for channelers)
		if(m_target->m_currentSpell && m_target->GetGUID() != m_casterGuid &&
			m_target->m_currentSpell->getState() == SPELL_STATE_CASTING )
		{
			m_target->m_currentSpell->safe_cancel();
		}
	}
	else
	{
		m_target->m_silenced--;

		if(m_target->m_silenced == 0)
		{
			m_target->m_special_state &= ~UNIT_STATE_SILENCE;
			m_target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SILENCED);
		}
	}
}

void Aura::SpellAuraReflectSpells(bool apply)
{
	if(apply)
	{
		SpellEntry *sp = dbcSpell.LookupEntry(GetSpellId());
		if (sp == NULL) 
		{ 
			return;
		}

		CommitPointerListNode<struct ReflectSpellSchool> *itr;
		m_target->m_reflectSpellSchool.BeginLoop();
		for(itr = m_target->m_reflectSpellSchool.begin(); itr != m_target->m_reflectSpellSchool.end();itr = itr->Next() )
			if(GetSpellProto()->Id == itr->data->spellId)
				m_target->m_reflectSpellSchool.SafeRemove(itr,1);
		m_target->m_reflectSpellSchool.EndLoopAndCommit();

		ReflectSpellSchool *rss = new ReflectSpellSchool;

		rss->chance = mod->m_amount;
		rss->spellId = GetSpellId();
		rss->school = -1;
		rss->require_aura_hash = 0;
		rss->charges = sp->procCharges;
		m_target->m_reflectSpellSchool.push_front(rss);
	}
	else
	{
		CommitPointerListNode<struct ReflectSpellSchool> *itr;
		m_target->m_reflectSpellSchool.BeginLoop();
		for(itr = m_target->m_reflectSpellSchool.begin(); itr != m_target->m_reflectSpellSchool.end();itr = itr->Next() )
			if(GetSpellProto()->Id == itr->data->spellId)
				m_target->m_reflectSpellSchool.SafeRemove(itr,1);
		m_target->m_reflectSpellSchool.EndLoopAndCommit();
	}
}

void Aura::SpellAuraModStat( bool apply )
{
	int32 stat = ( int32 )mod->m_miscValue;
	int32 val;

	if( apply )
	{
		val = mod->m_amount;
		if( val < 0 )
			SetNegative();
		else
			SetPositive();
	}
	else
	{
		val = -mod->m_amount;
	}

	if ( stat == -1 )//all stats
	{
		if( m_target->IsPlayer() )
		{
			for( uint8 x = 0; x < 5; x++ )
			{
				if( mod->m_amount > 0 )
					SafePlayerCast( m_target )->FlatStatModPos[x] += val;
				else
					SafePlayerCast( m_target )->FlatStatModNeg[x] -= val;

				SafePlayerCast( m_target )->CalcStat(x);
			}

			SafePlayerCast( m_target )->UpdateStats();
			SafePlayerCast( m_target )->UpdateChances();
		}
		else if( m_target->GetTypeId() == TYPEID_UNIT )
		{
			for( uint8 x = 0; x < 5; x++ )
			{
				SafeCreatureCast( m_target )->FlatStatMod[x] += val;
				SafeCreatureCast( m_target )->CalcStat(x);
			}
		}
	}
	else if( stat >= 0 )
	{
		ASSERT( mod->m_miscValue < 5 );
		if( m_target->IsPlayer() )
		{
			if( mod->m_amount > 0 )
				SafePlayerCast( m_target )->FlatStatModPos[ mod->m_miscValue ] += val;
			else
				SafePlayerCast( m_target )->FlatStatModNeg[ mod->m_miscValue ] -= val;

			SafePlayerCast( m_target )->CalcStat( mod->m_miscValue );

			SafePlayerCast( m_target )->UpdateStats();
			SafePlayerCast( m_target )->UpdateChances();
		}
		else if( m_target->GetTypeId() == TYPEID_UNIT )
		{
			SafeCreatureCast( m_target )->FlatStatMod[ mod->m_miscValue ] += val;
			SafeCreatureCast( m_target )->CalcStat( mod->m_miscValue );
		}
	}
}

void Aura::SpellAuraModSkill(bool apply)
{
	if (m_target->GetTypeId() == TYPEID_PLAYER)
	{
		if(apply)
		{
			SetPositive();
			SafePlayerCast( m_target )->_ModifySkillBonus(mod->m_miscValue, mod->m_amount);
		}
		else
			SafePlayerCast( m_target )->_ModifySkillBonus(mod->m_miscValue, -mod->m_amount);

		SafePlayerCast( m_target )->UpdateStats();
	}
}

void Aura::SpellAuraModIncreaseSpeed(bool apply)
{
	if(apply)
	{
		if( (GetSpellProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) )
		{
			int32 speedmod=0;
			SM_FIValue(m_target->SM_FSpeedMod,&speedmod,GetSpellProto()->SpellGroupType);
			mod->m_amount += speedmod;
		}

		m_target->speedIncreaseMap.push_front( mod );
	}
	else
		m_target->speedIncreaseMap.remove( mod );

	if( m_target->GetSpeedIncrease() )
		m_target->UpdateSpeed();
}

void Aura::SpellAuraModIncreaseMountedSpeed(bool apply)
{
/*	if( GetSpellId() == 68768 || GetSpellId() == 68769 && p_target != NULL )
	{
		int32 newspeed = 0;

		if( p_target->_GetSkillLineCurrent( SKILL_RIDING, true ) >= 150 )
			newspeed = 100;
		else if( p_target->_GetSkillLineCurrent( SKILL_RIDING, true ) >= 75 )
			newspeed = 60;

		mod->m_amount = newspeed; // EffectBasePoints + 1 (59+1 and 99+1)
	} */
	if(apply)
	{
		SetPositive();
		m_target->m_mountedspeedModifier += mod->m_amount;
	}
	else
		m_target->m_mountedspeedModifier -= mod->m_amount;
	m_target->UpdateSpeed();
}

void Aura::SpellAuraModCreatureRangedAttackPower(bool apply)
{
	if(apply)
	{
		for(uint32 x = 0; x < CREATURE_TYPES; x++)
			if (mod->m_miscValue & (((uint32)1)<<x) )
				m_target->CreatureRangedAttackPowerMod[x+1] += mod->m_amount;
		if(mod->m_amount < 0)
			SetNegative();
		else
			SetPositive();
	}
	else
	{
		for(uint32 x = 0; x < CREATURE_TYPES; x++)
		{
			if (mod->m_miscValue & (((uint32)1)<<x) )
			{
				m_target->CreatureRangedAttackPowerMod[x+1] -= mod->m_amount;
			}
		}
	}
	m_target->CalcDamage();
}

void Aura::SpellAuraModDecreaseSpeed(bool apply)
{
	//there can not be 2 slow downs only most powerfull is applied
	if(apply)
	{
		// Check Mechanic Immunity
		if( m_target )
		{
			if( m_target->MechanicsDispels[MECHANIC_ENSNARED] )
			{
				m_flags |= 1 << mod->i;
				return;
			}
		}
		switch(m_spellProto->NameHash)
		{
			case SPELL_HASH_STEALTH:			// Stealth
				SetPositive();
				break;

			case SPELL_HASH_DAZED:			// Dazed
				SetNegative();
				break;

			default:
				/* burlex: this would be better as a if(caster is hostile to target) then effect = negative) */
				if(m_casterGuid != m_target->GetGUID())
					SetNegative();
				break;
		}

		if( (GetSpellProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) )
		{
			int32 speedmod=0;
			SM_FIValue(m_target->SM_FSpeedMod,&speedmod,GetSpellProto()->SpellGroupType);
			mod->m_amount += speedmod;
		}

		m_target->speedReductionMap.push_front( mod );
		//m_target->m_slowdown=this;
		//m_target->m_speedModifier += mod->m_amount;
	}
	else if( (m_flags & (1 << mod->i)) == 0 ) //add these checks to mods where imunity can cancel only 1 mod and not whole spell
	{
		m_target->speedReductionMap.remove( mod );
		//m_target->m_speedModifier -= mod->m_amount;
		//m_target->m_slowdown=NULL;
	}
	if(m_target->GetSpeedDecrease())
		m_target->UpdateSpeed();
}

void Aura::UpdateAuraModDecreaseSpeed()
{
	if( m_target )
	{
		if( m_target->MechanicsDispels[MECHANIC_ENSNARED] )
		{
			m_flags |= 1 << mod->i;
			return;
		}
	}
}

void Aura::SpellAuraModIncreaseHealth(bool apply)
{
	int32 amt;

	if(apply)
	{
		//threet special cases. We should move these to scripted spells maybe
		switch(m_spellProto->NameHash)
		{
			case SPELL_HASH_GIFT_OF_LIFE:// Gift of Life
			  mod->m_amount = 1500;
			  break;
			case SPELL_HASH_LAST_STAND:// Last Stand
			  mod->m_amount = (uint32)(m_target->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * 30 / 100 );
			  break;
			case SPELL_HASH_VAMPIRIC_BLOOD:
			  mod->m_amount = m_target->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * mod->m_amount / 100 ;
			  break;
		}
		SetPositive();

		//adjust value so when it is removed it is not removing more then he should
//		int32 max_amt = m_target->GetUInt32Value(UNIT_FIELD_MAXHEALTH) - m_target->GetUInt32Value(UNIT_FIELD_HEALTH);
//		if( mod->m_amount > max_amt )
//			mod->m_amount = max_amt;

		amt = mod->m_amount;

	}
	else
		amt =- mod->m_amount;

	if(m_target->IsPlayer())
	{
		//maybe we should not adjust hitpoints too but only maximum health
		SafePlayerCast( m_target )->SetHealthFromSpell(SafePlayerCast( m_target )->GetHealthFromSpell() + amt);
		if( m_target->isAlive() )
			SafePlayerCast( m_target )->UpdateStats();
	}

	if(apply)
	{
		m_target->ModUnsigned32Value(UNIT_FIELD_HEALTH,amt);
	}
	else
	{
		if((int32)m_target->GetUInt32Value(UNIT_FIELD_HEALTH)>-amt)//watch it on remove value is negative
			m_target->ModUnsigned32Value(UNIT_FIELD_HEALTH,amt);
		else if( m_target->isAlive() )
			m_target->SetUInt32Value(UNIT_FIELD_HEALTH,1); //do not kill player but do strip him good
	}
}

void Aura::SpellAuraModIncreaseEnergy(bool apply)
{
	if( mod->m_miscValue > UNIT_FIELD_POWER7 - UNIT_FIELD_POWER1 )
	{ 
		return;
	}

	SetPositive();

	uint32 powerField1 = UNIT_FIELD_POWER1 + mod->m_miscValue;
	uint32 powerField2 = UNIT_FIELD_MAXPOWER1 + mod->m_miscValue;

	m_target->ModUnsigned32Value(powerField1,apply?mod->m_amount:-mod->m_amount); //not always
	m_target->ModUnsigned32Value(powerField2,apply?mod->m_amount:-mod->m_amount);

	if(powerField1 == UNIT_FIELD_POWER1 && m_target->GetTypeId() == TYPEID_PLAYER)
	{
		int32 amt = apply ? mod->m_amount : -mod->m_amount;
		SafePlayerCast( m_target )->SetManaFromSpell(SafePlayerCast( m_target )->GetManaFromSpell() + amt);
	}
}

void Aura::SpellAuraModShapeshift(bool apply)
{
	if( p_target == NULL )
	{ 
		return;
	}

	if( p_target->m_MountSpellId && p_target->m_MountSpellId != m_spellProto->Id )
		if( !(mod->m_miscValue & ( FORM_BATTLESTANCE | FORM_DEFENSIVESTANCE | FORM_BERSERKERSTANCE ) ) )
			m_target->RemoveAura( p_target->m_MountSpellId ); // these spells are not compatible

	uint32 additional_cast_spellId = 0;
	uint32 modelId = 0;

	bool freeMovements = false;

	switch( mod->m_miscValue )
	{
	case FORM_CAT:
		{//druid
			freeMovements = true;
			additional_cast_spellId = 3025;
			if(apply)
			{
				m_target->SetByte(UNIT_FIELD_BYTES_0,3,POWER_TYPE_ENERGY);
				m_target->SetUInt32Value(UNIT_FIELD_MAXPOWER4,100);//100 Energy
				m_target->SetUInt32Value(UNIT_FIELD_POWER4,0);//0 Energy
				if(m_target->getRace() == RACE_NIGHTELF)
				{
//					modelId = 892;
					//get hair color
					const int models[4] = { 29405,29406,29407,29408 };
					uint32 hair_color = m_target->GetByte( PLAYER_BYTES, 3 );
					hair_color = hair_color % 4;	//no idea how many there are, i think 8 or 7
					modelId = models[ hair_color ];
				}
				else //TAUREN
				{
//					modelId = 8571;
					const int models[4] = { 29409,29410,29411,29412 };
					uint32 hair_color = m_target->GetByte( PLAYER_BYTES, 3 );
					hair_color = hair_color % 4;	//no idea how many there are, i think 8 or 7
					modelId = models[ hair_color ];
				}
				sEventMgr.AddEvent( this, &Aura::EventParalelManaRegen, EVENT_PERIODIC_DUMMY_AURA_TRIGGER, 2000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
			}
			else
			{//turn back to mana
				//m_target->SetUInt32Value(UNIT_FIELD_BASEATTACKTIME,oldap);
				m_target->SetByte(UNIT_FIELD_BYTES_0,3,POWER_TYPE_MANA);
				if(m_target->m_stealth)
				{
					uint32 sp = m_target->m_stealth;
					m_target->m_stealth = 0;
					m_target->RemoveAura(sp);//prowl
				}
				if(m_target->HasActiveAura(1850))
					m_target->RemoveAura(1850);//Dash rank1
				if(m_target->HasActiveAura(9821))
					m_target->RemoveAura(9821);//Dash rank2
				if(m_target->HasActiveAura(33357))
					m_target->RemoveAura(33357);//Dash rank3
			}
			SafePlayerCast( m_target )->UpdateAttackSpeed();

		} break;
	case FORM_TREE:
		{
			modelId  = 864;
			freeMovements=true;
			additional_cast_spellId = 34123;//
		} break;
	case FORM_TRAVEL:
		{//druid
			freeMovements = true;
			additional_cast_spellId = 5419;
			modelId = 918;
		} break;
	case FORM_AQUA:
		{//druid aqua
			freeMovements = true;
			additional_cast_spellId = 5421;
			modelId = 2428;
		} break;
	case FORM_BEAR:
		{//druid only
			freeMovements = true;
			additional_cast_spellId = 1178;
			if(apply)
			{
				m_target->SetByte(UNIT_FIELD_BYTES_0,3,POWER_TYPE_RAGE);
				m_target->SetUInt32Value(UNIT_FIELD_MAXPOWER2, 1000);
				m_target->SetUInt32Value(UNIT_FIELD_POWER2, 0);//0 rage

				if(m_target->getRace() == RACE_NIGHTELF)
				{
//					modelId = 2281;
					const int models[5] = { 29414,29415,29416,29417,29413};	//1 is extra but which one ?
					uint32 hair_color = m_target->GetByte( PLAYER_BYTES, 3 );
					hair_color = hair_color % 4;	//no idea how many there are, i think 8 or 7
					modelId = models[ hair_color ];
				}
				else //TAUREN
				{
//					modelId = 2289;
					const int models[4] = { 29418,29419,29420,29421 };
					uint32 hair_color = m_target->GetByte( PLAYER_BYTES, 3 );
					hair_color = hair_color % 4;	//no idea how many there are, i think 8 or 7
					modelId = models[ hair_color ];
				}
				sEventMgr.AddEvent( this, &Aura::EventParalelManaRegen, EVENT_PERIODIC_DUMMY_AURA_TRIGGER, 2000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );

				//some say there is a second effect
				SpellEntry* spellInfo = dbcSpell.LookupEntry( 21178 );

				Spell *sp = SpellPool.PooledNew();
				sp->Init( m_target, spellInfo, true, NULL );
				SpellCastTargets tgt;
				tgt.m_unitTarget = m_target->GetGUID();
				sp->prepare( &tgt );
			}
			else
			{//reset back to mana
				m_target->SetByte(UNIT_FIELD_BYTES_0,3,POWER_TYPE_MANA);
				m_target->RemoveAura( 21178 ); // remove Bear Form (Passive2)
			}
		} break;
	case FORM_DIREBEAR:
		{//druid only
			freeMovements = true;
			additional_cast_spellId = 9635;
			if(apply)
			{
				m_target->SetByte(UNIT_FIELD_BYTES_0,3,POWER_TYPE_RAGE);
				m_target->SetUInt32Value(UNIT_FIELD_MAXPOWER2, 1000);
				m_target->SetUInt32Value(UNIT_FIELD_POWER2, 0);//0 rage
				if(m_target->getRace() == 4)//NE
				{
//					modelId = 2281;
					const int models[5] = { 29414,29415,29416,29417,29413};	//1 is extra but which one ?
					uint32 hair_color = m_target->GetByte( PLAYER_BYTES, 3 );
					hair_color = hair_color % 4;	//no idea how many there are, i think 8 or 7
					modelId = models[ hair_color ];
				}
				else //TAUREN
				{
//					modelId = 2289;
					const int models[4] = { 29418,29419,29420,29421 };
					uint32 hair_color = m_target->GetByte( PLAYER_BYTES, 3 );
					hair_color = hair_color % 4;	//no idea how many there are, i think 8 or 7
					modelId = models[ hair_color ];
				}
				sEventMgr.AddEvent( this, &Aura::EventParalelManaRegen, EVENT_PERIODIC_DUMMY_AURA_TRIGGER, 2000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
			}
			else //reset back to mana
				m_target->SetByte(UNIT_FIELD_BYTES_0,3,POWER_TYPE_MANA);
		} break;
	case FORM_GHOSTWOLF:
		{
			modelId = 4613;
		} break;
	case FORM_BATTLESTANCE:
		{
			additional_cast_spellId = 21156;
		} break;
	case FORM_DEFENSIVESTANCE:
		{
			additional_cast_spellId = 7376;
		} break;
	case FORM_BERSERKERSTANCE:
		{
			additional_cast_spellId = 7381;
		} break;
	case FORM_SHADOW:
		{
		}break;
	case FORM_FLIGHT:
		{// druid
			freeMovements = true;
			additional_cast_spellId = 33948;
			if(apply)
			{
			    if(m_target->getRace() == RACE_NIGHTELF)
				    modelId = 20857;
			    else
				    modelId = 20872;			
			}
		}break;
	case FORM_STEALTH:
		{// rogue
			if (!m_target->m_can_stealth)
			{ 
				return;
			}
			//m_target->UpdateVisibility();
		} break;
	case FORM_MOONKIN:
		{//druid
			freeMovements = true;
			additional_cast_spellId = 24905;
			if(apply)
			{
				if(m_target->getRace() == RACE_NIGHTELF)
					modelId = 15374;
				else
					modelId = 15375;
			}
		}break;
	case FORM_SWIFT: //not tested yet, right now going on trust
		{// druid
			freeMovements = true;
			additional_cast_spellId = 40121; //Swift Form Passive
			if(apply)
			{
				if(m_target->getRace() == RACE_NIGHTELF)//NE
					modelId = 21243;
				else //TAUREN
					modelId = 21244;
			}
		}break;
	case FORM_SPIRITOFREDEMPTION:
		{
			additional_cast_spellId = 27795;
			modelId = 12824;
		}break;
	case FORM_DEMON:
		{
			additional_cast_spellId = 59673; //could use this only when we learn the talent as it teaches 3 spells
			modelId = 25277;
			if (apply)
			{
				//m_target->m_modlanguage = LANG_DEMONIC;
				m_target->CastSpell(m_target, 54817, true);
				m_target->CastSpell(m_target, 54879, true);
				m_target->CastSpell(m_target, 61610, true);
			}
			else
			{
				//m_target->m_modlanguage = -1;
				m_target->RemoveAura(54817);
				m_target->RemoveAura(54879);
				m_target->RemoveAura(61610);
			}
		}break;
	case FORM_RESURRECT_AS_GHOUL:
		{
			additional_cast_spellId = 40251;
			modelId = 571;
		}break;
	}

	if( apply )
	{
		if( m_target->getClass() == WARRIOR && m_target->GetUInt32Value( UNIT_FIELD_POWER2 ) > SafePlayerCast( m_target )->m_retainedrage )
			m_target->SetUInt32Value(UNIT_FIELD_POWER2, SafePlayerCast( m_target )->m_retainedrage );

		if( additional_cast_spellId != GetSpellId() && m_target->IsPlayer() )
		{
			if( SafePlayerCast( m_target )->m_ShapeShifted )
				SafePlayerCast( m_target )->RemoveAura( SafePlayerCast( m_target )->m_ShapeShifted );

			SafePlayerCast( m_target )->m_ShapeShifted = GetSpellId();
		}

		if( modelId != 0 )
		{
			m_target->SetUInt32Value( UNIT_FIELD_DISPLAYID, modelId );
			m_target->EventModelChange();
		}

		SafePlayerCast( m_target )->SetShapeShift( mod->m_miscValue );

		// check for spell id
		if( additional_cast_spellId == 0 )
		{ 
			return;
		}

		SpellEntry* spellInfo = dbcSpell.LookupEntry(additional_cast_spellId );

		Spell *sp = SpellPool.PooledNew();
		sp->Init( m_target, spellInfo, true, NULL );
		SpellCastTargets tgt(m_target->GetGUID());
		sp->prepare( &tgt );

		// remove the caster from imparing movements
		if( freeMovements )
			m_target->RemoveAllAurasByMechanic( MECHANIC_ENSNARED, -1, false );

		//execute after we changed shape
		SafePlayerCast( m_target )->EventTalentHearthOfWildChange( true );
	}
	else
	{
		//remove auras that reauire this shapeshift(including talents)
		for(uint32 i = FIRST_AURA_SLOT; i < MAX_PASSIVE_AURAS1(m_target); ++i)
		{
			if( m_target->m_auras[i] != NULL && m_target->m_auras[i]->GetSpellProto() && m_target->m_auras[i]->IsPositive() )
			{
				uint32 requiredShapeShift = m_target->m_auras[i]->GetSpellProto()->RequiredShapeShift;
				uint32 mask = 1 << ( mod->m_miscValue - 1 );
				if( requiredShapeShift & mask )
					m_target->m_auras[i]->Remove();
			}
		}
		//execute before changing shape back
		SafePlayerCast( m_target )->EventTalentHearthOfWildChange( false );
		m_target->SetUInt32Value( UNIT_FIELD_DISPLAYID, m_target->GetUInt32Value( UNIT_FIELD_NATIVEDISPLAYID ) );
		m_target->EventModelChange();

		if( additional_cast_spellId != GetSpellId() && additional_cast_spellId != 0 )
				m_target->RemoveAura( additional_cast_spellId );

		SafePlayerCast( m_target )->m_ShapeShifted = 0;
		SafePlayerCast( m_target )->SetShapeShift( 0 );

	}
	SafePlayerCast( m_target )->UpdateStats();
}

void Aura::SpellAuraModEffectImmunity(bool apply)
{
	if( m_spellProto->Id == 24937 )
		SetPositive();

	if( m_spellProto->Id == 23333 || m_spellProto->Id == 23335 || m_spellProto->Id == 34976 )
	{
		if( !apply )
		{
            Player* plr = SafePlayerCast( GetUnitCaster() );
			if( plr == NULL || plr->GetTypeId() != TYPEID_PLAYER || plr->m_bg == NULL)
			{ 
				return;
			}

			plr->m_bg->HookOnFlagDrop(plr);
		}
	}
}

void Aura::SpellAuraModStateImmunity(bool apply)
{
	//%50 chance to dispel 1 magic effect on target
	//23922
}

void Aura::SendIgnoreStateAura()
{
	if( m_target == NULL || !m_target->IsPlayer() )
		return;
	//already sent packet for these
	if( IsVisible() )
		return;
	WorldPacket tpacket(SMSG_AURA_UPDATE, 14+2);
	tpacket << m_target->GetNewGUID();
	tpacket << (uint8)(m_visualSlot);	//some unexistent slot from our point of view
	tpacket << GetSpellProto()->Id;
	tpacket << (uint8)0x0F;	//cause blizz says so flags
	tpacket << (uint8)0x4B;	//cause blizz says so spell level (never !)
	tpacket << (uint8)0x00;	//cause blizz says so stack
	SafePlayerCast(m_target)->GetSession()->SendPacket( &tpacket );
}

void Aura::RemoveIgnoreStateAura()
{
	if( m_target == NULL || !m_target->IsPlayer() )
		return;
	//already sent packet for these
	if( IsVisible() )
		return;
	WorldPacket tpacket(SMSG_AURA_UPDATE, 14+2);
	tpacket << m_target->GetNewGUID();
	tpacket << (uint8)(m_visualSlot);	//some unexistent slot from our point of view
	tpacket << uint32(0);
	SafePlayerCast(m_target)->GetSession()->SendPacket( &tpacket );
}

void Aura::SpellAuraModIgnoreState(bool apply)
{
	if( !m_target->IsPlayer() ) 
	{ 
		return;
	}
	//do we have to do anything here or client will let us use anything ?
	if( apply )
	{
		m_visualSlot = 255 - SafePlayerCast( m_target )->IgnoreSpellSpecialCasterStateRequirement;
		uint32 slot = m_visualSlot;
		m_flags |= NEED_STATEIGNORE_RESEND_ON_MAPCHANGE;
		SafePlayerCast( m_target )->IgnoreSpellSpecialCasterStateRequirement++;
		//trigger as soon as possible
		sEventMgr.AddEvent( this, &Aura::SendIgnoreStateAura, EVENT_SEND_PACKET_TO_PLAYER_AFTER_LOGIN, 5000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
		//hackfix until i fix it properly. On chaning maps we need to resend this
//		if( GetDuration() != (uint32)(-1) )
//			sEventMgr.AddEvent( this, &Aura::SendIgnoreStateAura, GetSpellId(), slot, EVENT_SEND_PACKET_TO_PLAYER_AFTER_LOGIN, 60*1000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
	else if( SafePlayerCast( m_target )->IgnoreSpellSpecialCasterStateRequirement > 0 )
	{
		sEventMgr.RemoveEvents( this, EVENT_SEND_PACKET_TO_PLAYER_AFTER_LOGIN );
		RemoveIgnoreStateAura();
		SafePlayerCast( m_target )->IgnoreSpellSpecialCasterStateRequirement--;
	}
}

void Aura::SpellAuraModSchoolImmunity(bool apply)
{
	if( apply && ( m_spellProto->NameHash == SPELL_HASH_DIVINE_SHIELD || m_spellProto->NameHash == SPELL_HASH_ICE_BLOCK) ) // Paladin - Divine Shield
	{
		if( !m_target || !m_target->isAlive())
		{ 
			return;
		}

		Aura * pAura;
		for(uint32 i = MAX_POSITIVE_AURAS; i < MAX_NEGATIVE_AURAS1(m_target); ++i)
		{
			pAura = m_target->m_auras[i];
			if( pAura != this && pAura != NULL && !pAura->IsPassive() && !pAura->IsPositive() && !(pAura->GetSpellProto()->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY) )
				pAura->Remove();
		}
	}

	if( apply && ( m_spellProto->NameHash == SPELL_HASH_DIVINE_SHIELD || m_spellProto->NameHash == SPELL_HASH_BLESSING_OF_PROTECTION || m_spellProto->NameHash == SPELL_HASH_ICE_BLOCK) )
	{
		m_target->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_INVINCIBLE);
	}

	if(apply)
	{
		//fixme me may be negative
		Unit * c = GetUnitCaster();
		if(c)
		{
			if(isAttackable(c,m_target))
				SetNegative();
			else SetPositive();
		}else
			SetPositive();

		sLog.outDebug("%s: value=%x", __FUNCTION__, mod->m_miscValue);
		for(uint32 i = 0; i < 7; i++)
		{
			if(mod->m_miscValue & (1<<i))
			{
				m_target->SchoolImmunityList[i] ++;
				m_target->RemoveAurasOfSchool(i, false, true);
			}
		}
	}
	else
	{
		for(int i = 0; i < 7; i++)
			if( ( mod->m_miscValue & (1<<i) ) && m_target->SchoolImmunityList[i]>0 )
				m_target->SchoolImmunityList[i]--;
	}
}

void Aura::SpellAuraModAPBasedOnStat(bool apply)
{
	if( mod->m_miscValue > 5 )
	{ 
		return;
	}

	if( apply )
	{
		if(mod->m_amount<0)
			SetNegative();
		else
			SetPositive();

		mod->fixed_amount[ 0 ] = mod->m_amount * m_target->GetUInt32Value( UNIT_FIELD_STAT0 + mod->m_miscValue ) / 100;
		m_target->ModUnsigned32Value(UNIT_FIELD_ATTACK_POWER_MODS,mod->fixed_amount[ 0 ]);
	}
	else
		m_target->ModUnsigned32Value(UNIT_FIELD_ATTACK_POWER_MODS,-mod->fixed_amount[ 0 ]);

	m_target->CalcDamage();
}

void Aura::SpellAuraModDmgImmunity(bool apply)
{

}

void Aura::SpellAuraModDispelImmunity(bool apply)
{
	assert(mod->m_miscValue < 10);
	if(apply)
		m_target->dispels[mod->m_miscValue]++;
	else
		m_target->dispels[mod->m_miscValue]--;

	if(apply)
	{
		for(uint32 x=0;x<MAX_NEGATIVE_AURAS1(m_target);x++)
			if(m_target->m_auras[x])
				if(m_target->m_auras[x]->GetSpellProto()->DispelType==(uint32)mod->m_miscValue)
					m_target->m_auras[x]->Remove();
	}
}

void Aura::SpellAuraProcTriggerSpell(bool apply)
{
	if(apply)
	{
		ProcTriggerSpell *pts = new ProcTriggerSpell( GetSpellProto() );
		pts->caster = m_casterGuid;
		if(GetSpellProto()->EffectTriggerSpell[mod->i])
			pts->spellId=GetSpellProto()->EffectTriggerSpell[mod->i];
		else
		{
			sLog.outDebug("Warning,trigger spell is null for spell %u",GetSpellProto()->Id);
			return;
		}
		Unit *caster = GetUnitCaster();
		int32 proc_Chance = pts->procChance;
		if( caster ) 
			SM_FIValue( caster->SM_FChanceOfSuccess, (int32*)&proc_Chance, GetSpellProto()->SpellGroupType );
		if( proc_Chance <= 0 )
		{
			sLog.outDebug("Warning,trigger spell %u proc chance is less then 0",GetSpellProto()->Id);
			return;
		}
		else 
			pts->procChance = proc_Chance;
		pts->created_with_value = mod->m_amount;
		int charges = GetSpellProto()->procCharges;
		if( (GetSpellProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && caster != NULL )
		{
			SM_FIValue( caster->SM_FCharges, &charges, GetSpellProto()->SpellGroupType );
			SM_PIValue( caster->SM_PCharges, &charges, GetSpellProto()->SpellGroupType );
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
			float spell_flat_modifers=0;
			float spell_pct_modifers=0;
			SM_FIValue(GetUnitCaster()->SM_FCharges,&spell_flat_modifers,GetSpellProto()->SpellGroupType);
			SM_FIValue(GetUnitCaster()->SM_PCharges,&spell_pct_modifers,GetSpellProto()->SpellGroupType);
			if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
				printf("!!!!!spell charge bonus mod flat %f , spell range bonus pct %f , spell range %f, spell group %u\n",spell_flat_modifers,spell_pct_modifers,maxRange,m_spellInfo->SpellGroupType);
#endif
		}
		pts->procCharges = charges;

		if( m_castedItemId && GetSpellProto()->proc_interval == 0 )
			pts->procChance = 5;
		m_target->m_procSpells.push_front(pts);
		sLog.outDebug("%u is registering %u chance %u flags %u charges %u triggeronself %u interval %u requires hash %u\n",pts->origId,pts->spellId,pts->procChance,m_spellProto->procFlags,charges,(m_spellProto->procFlags2 & PROC2_TARGET_SELF)!=0,m_spellProto->proc_interval,m_spellProto->ProcOnNameHash[0] || m_spellProto->ProcOnNameHash[1] || m_spellProto->ProcOnNameHash[2]);
	}
	else
	{
		CommitPointerListNode<ProcTriggerSpell> *itr;
		for(itr = m_target->m_procSpells.begin();itr != m_target->m_procSpells.end();itr = itr->Next() )
			if(itr->data->origId == GetSpellId() && itr->data->caster == m_casterGuid && !itr->data->deleted)
			{
				itr->data->deleted = true;
				break; //only 1 instance of a proc spell per caster ? //zack : not true
			}
	}
}

void Aura::SpellAuraProcTriggerDamage(bool apply)
{
	if(apply)
	{
		DamageProc ds;
		ds.m_damage = mod->m_amount;
		ds.m_spellId = GetSpellProto()->Id;
		ds.m_school = GetSpellProto()->School;
		ds.m_flags = m_spellProto->procFlags;
		ds.owner = (void*)this;
		m_target->m_damageShields.push_back(ds);
		sLog.outDebug("registering dmg proc %u, school %u, flags %u, charges at least %u \n",ds.m_spellId,ds.m_school,ds.m_flags,m_spellProto->procCharges);
	}
	else
	{
		for(std::list<struct DamageProc>::iterator i = m_target->m_damageShields.begin();i != m_target->m_damageShields.end();i++)
		{
			if(i->owner == this)
			{
				m_target->m_damageShields.erase(i);
				break;
			}
		}
	}
}

void Aura::SpellAuraTrackCreatures(bool apply)
{
	if(m_target->GetTypeId() == TYPEID_PLAYER)
	{
		if(apply)
		{
			if(SafePlayerCast( m_target )->TrackingSpell)
				m_target->RemoveAura( SafePlayerCast( m_target )->TrackingSpell);

			m_target->SetUInt32Value(PLAYER_TRACK_CREATURES,(uint32)1<< (mod->m_miscValue-1));
			SafePlayerCast( m_target )->TrackingSpell = GetSpellId();
		}
		else
		{
			SafePlayerCast( m_target )->TrackingSpell = 0;
			m_target->SetUInt32Value(PLAYER_TRACK_CREATURES,0);
		}
	}
}

void Aura::SpellAuraTrackResources(bool apply)
{
	if(m_target->GetTypeId() == TYPEID_PLAYER)
	{
		if(apply)
		{
			if(SafePlayerCast( m_target )->TrackingSpell)
				m_target->RemoveAura(SafePlayerCast( m_target )->TrackingSpell);

			m_target->SetUInt32Value(PLAYER_TRACK_RESOURCES,(uint32)1<< (mod->m_miscValue-1));
			SafePlayerCast( m_target )->TrackingSpell = GetSpellId();
		}
		else
		{
			SafePlayerCast( m_target )->TrackingSpell = 0;
			m_target->SetUInt32Value(PLAYER_TRACK_RESOURCES,0);
		}
	}
}

void Aura::SpellAuraModParryPerc(bool apply)
{
	//if (m_target->GetTypeId() == TYPEID_PLAYER)
	{
		int32 amt;
		if(apply)
		{
			amt = mod->m_amount;
			if(amt<0)
				SetNegative();
			else
				SetPositive();

		}
		else
			amt = -mod->m_amount;

		m_target->SetParryFromSpell(m_target->GetParryFromSpell() + amt );
		if ((m_target->GetTypeId() == TYPEID_PLAYER))
		{
			SafePlayerCast( m_target )->UpdateChances();
		}
	}
}

void Aura::SpellAuraModDodgePerc(bool apply)
{
	//if (m_target->GetTypeId() == TYPEID_PLAYER)
	{
		int32 amt = mod->m_amount;
//		SM_FIValue(m_target->SM_FSPELL_VALUE, &amt, GetSpellProto()->SpellGroupType);
		if(apply)
		{
			if(amt<0)
				SetNegative();
			else
				SetPositive();
		}
		else
			amt = -amt;

		m_target->SetDodgeFromSpell(m_target->GetDodgeFromSpell() + amt );
		if (m_target->GetTypeId() == TYPEID_PLAYER)
		{
			SafePlayerCast( m_target )->UpdateChances();
		}
	}
}

void Aura::SpellAuraModBlockPerc(bool apply)
{
	//if (m_target->GetTypeId() == TYPEID_PLAYER)
	{
		int32 amt;
		if(apply)
		{
			amt = mod->m_amount;
			if(amt<0)
				SetNegative();
			else
				SetPositive();
		}
		else
			amt = -mod->m_amount;

		m_target->SetBlockFromSpell(m_target->GetBlockFromSpell() + amt);
		if (m_target->GetTypeId() == TYPEID_PLAYER)
		{
			SafePlayerCast( m_target )->UpdateStats();
		}
	}
}

void Aura::SpellAuraModCritPerc(bool apply)
{
	if (m_target->IsPlayer())
	{
		if(apply)
		{
			WeaponModifier *md;
			md = new WeaponModifier;
			md->value = float(mod->m_amount);
			md->wclass = GetSpellProto()->EquippedItemClass;
			md->subclass = GetSpellProto()->EquippedItemSubClass;
			md->spellentry = GetSpellProto();
			p_target->tocritchance.push_front( md );
		}
		else
		{
			SimplePointerListNode<WeaponModifier> *i;
			for( i=p_target->tocritchance.begin();i!=p_target->tocritchance.end();i = i->Next() )
				if( i->data->spellentry == GetSpellProto() )
				{
					p_target->tocritchance.remove( i, 1 );
					break;
				}
		}
		SafePlayerCast( m_target )->UpdateChances();
	}
	else if( m_target->IsCreature())
	{
		if(apply)
			SafeCreatureCast(m_target)->crit_chance_mod += mod->m_amount;
		else
			SafeCreatureCast(m_target)->crit_chance_mod -= mod->m_amount;
	}
}

void Aura::SpellAuraPeriodicLeech(bool apply)
{
	if(apply)
	{
		SetNegative();
//		uint32 amt = mod->m_amount;

		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHasteDots() );
		}
		if( period < 500 )
			period = 500;

//		sEventMgr.AddEvent(this, &Aura::EventPeriodicLeech,amt,period, (int32)mod->i,
		sEventMgr.AddEvent(this, &Aura::EventPeriodicLeech,mod->list_ind,period,
			EVENT_AURA_PERIODIC_LEECH, period ,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

//void Aura::EventPeriodicLeech(uint32 amount,int32 period,int32 effect_index)
void Aura::EventPeriodicLeech(uint32 aura_list_ind,int32 period)
{
	Unit* m_caster = GetUnitCaster();

	if(!m_caster || !m_target)
	{ 
		return;
	}

	if(m_target->isAlive() && m_caster->isAlive())
	{
		if(m_target->SchoolImmunityList[GetSpellProto()->School])
		{ 
			return;
		}
		//check if still in range
		float maxRange = GetMaxRange( dbcSpellRange.LookupEntry( GetSpellProto()->rangeIndex ) );
		if( Need_SM_Apply(GetSpellProto()) )
		{
			SM_FFValue( m_caster->SM_FRange, &maxRange, GetSpellProto()->SpellGroupType );
			SM_PFValue( m_caster->SM_PRange, &maxRange, GetSpellProto()->SpellGroupType );
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
			float spell_flat_modifers=0;
			float spell_pct_modifers=0;
			SM_FFValue(u_caster->SM_FRange,&spell_flat_modifers,GetProto()->SpellGroupType);
			SM_FFValue(u_caster->SM_PRange,&spell_pct_modifers,GetProto()->SpellGroupType);
			if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
				printf("!!!!!spell range bonus mod flat %f , spell range bonus pct %f , spell range %f, spell group %u\n",spell_flat_modifers,spell_pct_modifers,maxRange,GetProto()->SpellGroupType);
#endif
		}
		if( maxRange * maxRange < m_caster->GetDistance2dSq( m_target ) )
		{
//			m_caster->CancelSpell( NULL );
			Remove();		//suicide here ! I wonder if canceling spell already deleted us
			return;	
		}


		Modifier *mod = &m_modList[ aura_list_ind ];
		uint32 amount = mod->m_amount;
		int32 effect_index = mod->i;
		uint32 SoulSiphonPCTBonus = mod->m_miscValue;		//i know this sucks, but it is not used apart from this

		//hasting affects ticks too
		amount += m_caster->GetSpellDmgBonus(m_target,GetSpellProto(), amount, GetSpellProto()->quick_tickcount ) / GetSpellProto()->quick_tickcount;
		amount += amount * SoulSiphonPCTBonus / 100;

		uint32 Amount = (uint32)min( amount, m_target->GetUInt32Value( UNIT_FIELD_HEALTH ) );

		uint32 dmg_amount = Amount;
		float conv_coef = GetSpellProto()->EffectConversionCoef[effect_index];
		uint32 heal_amount = float2int32( dmg_amount * conv_coef );
		uint32 newHealth = m_caster->GetUInt32Value(UNIT_FIELD_HEALTH) + heal_amount ;

		uint32 mh = m_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
		if(newHealth <= mh)
			m_caster->SetUInt32Value(UNIT_FIELD_HEALTH, newHealth);
		else
			m_caster->SetUInt32Value(UNIT_FIELD_HEALTH, mh);

		SendPeriodicHealAuraLog( m_target, m_caster, heal_amount );
//		m_target->SendSpellPeriodicAuraLog(m_caster, m_target, m_spellProto->Id, m_spellProto->School, Amount, 0, 0, FLAG_PERIODIC_LEECH, 0);
		//cause priest devouring plague is using it
		m_target->SendSpellNonMeleeDamageLog(m_caster, m_target, m_spellProto->Id,dmg_amount,m_spellProto->School,0,0,0,0,0,true);

		//deal damage before we add healing bonus to damage
		m_caster->DealDamage(m_target, dmg_amount, 0, 0, GetSpellProto()->Id,false);

		//!!! OMG aura got removed while we use it. This will lead to mem corruption !!
		if( !m_target || !m_target->isAlive() )
		{ 
			return;
		}

		m_caster->HandleProc(PROC_ON_ANY_HOSTILE_ACTION,m_target, m_spellProto,dmg_amount);

		//!!! OMG aura got removed while we use it. This will lead to mem corruption !!
		if( !m_target )
		{ 
			return;
		}

		m_target->HandleProc(PROC_ON_ANY_HOSTILE_ACTION|PROC_ON_ANY_DAMAGE_VICTIM|PROC_ON_SPELL_HIT_VICTIM,m_caster,m_spellProto,dmg_amount);

		//!!! OMG aura got removed while we use it. This will lead to mem corruption !!
		if( !m_target )
		{ 
			return;
		}

		m_target->RemoveAurasByHeal();
	}
}

void Aura::SpellAuraModHitChance(bool apply)
{
	if (m_target->IsUnit())
	{
		if (apply)
		{
			SafeUnitCast( m_target )->SetHitFromMeleeSpell( SafeUnitCast( m_target )->GetHitFromMeleeSpell() + mod->m_amount);
			if(mod->m_amount<0)
				SetNegative();
			else
				SetPositive();
		}
		else
		{
			SafeUnitCast( m_target )->SetHitFromMeleeSpell( SafeUnitCast( m_target )->GetHitFromMeleeSpell() - mod->m_amount);
			if( SafeUnitCast( m_target )->GetHitFromMeleeSpell() < 0 )
			{
				SafeUnitCast( m_target )->SetHitFromMeleeSpell( 0 );
			}
		}
	}
}

void Aura::SpellAuraModSpellHitChance(bool apply)
{
	if (m_target->IsPlayer())
	{
		if (apply)
		{
			SafePlayerCast( m_target )->SetHitFromSpell(SafePlayerCast( m_target )->GetHitFromSpell() + mod->m_amount);
			if(mod->m_amount<0)
				SetNegative();
			else
				SetPositive();
		}
		else
		{
			SafePlayerCast( m_target )->SetHitFromSpell(SafePlayerCast( m_target )->GetHitFromSpell() - mod->m_amount);
			if(SafePlayerCast( m_target )->GetHitFromSpell() < 0)
			{
				SafePlayerCast( m_target )->SetHitFromSpell(0);
			}
		}
	}
}

void Aura::SpellAuraTransform(bool apply)
{
	// Try a dummy SpellHandler
	if(sScriptMgr.CallScriptedDummyAura(GetSpellId(), mod->i, this, apply))
	{ 
		return;
	}

	uint32 displayId = 0;
	CreatureInfo* ci = CreatureNameStorage.LookupEntry(mod->m_miscValue);

	if(ci)
		displayId = ci->Male_DisplayID;

	if(p_target && p_target->m_MountSpellId)
		m_target->RemoveAura(p_target->m_MountSpellId);

	if( GetSpellProto()->MechanicsType == MECHANIC_POLYMORPHED && m_target )
	{
		if( apply ) 
			m_target->m_special_state |= UNIT_STATE_POLYMORPH;
		else
			m_target->m_special_state &= ~UNIT_STATE_POLYMORPH;
	}
   // SetPositive();
	switch( GetSpellProto()->Id )
	{
		case 20584://wisp
			m_target->SetUInt32Value( UNIT_FIELD_DISPLAYID, apply ? 10045:m_target->GetUInt32Value( UNIT_FIELD_NATIVEDISPLAYID ) );
		break;

		case 30167: // Red Ogre Costume
		{
			if( apply )
				m_target->SetUInt32Value( UNIT_FIELD_DISPLAYID, 11549 );
			else
				m_target->SetUInt32Value( UNIT_FIELD_DISPLAYID, m_target->GetUInt32Value( UNIT_FIELD_NATIVEDISPLAYID ) );
		}break;

		case 41301: // Time-Lost Figurine
		{
			if( apply )
				m_target->SetUInt32Value( UNIT_FIELD_DISPLAYID, 18628 );
			else
				m_target->SetUInt32Value( UNIT_FIELD_DISPLAYID, m_target->GetUInt32Value( UNIT_FIELD_NATIVEDISPLAYID ) );
		}break;

		case 16739: // Orb of Deception
		{
			if( apply )
			{
				if(m_target->getRace() == RACE_ORC)
				{
					if( m_target->getGender() == 0 )
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10139);
					else
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10140);
				}
				if(m_target->getRace() == RACE_TAUREN)
				{
					if( m_target->getGender() == 0 )
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10136);
					else
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10147);
				}
				if(m_target->getRace() == RACE_TROLL)
				{
					if( m_target->getGender() == 0 )
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10135);
					else
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10134);
				}
				if(m_target->getRace() == RACE_UNDEAD)
				{
					if( m_target->getGender() == 0 )
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10146);
					else
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10145);
				}
				if(m_target->getRace() == RACE_BLOODELF)
				{
					if( m_target->getGender() == 0 )
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 17829);
					else
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 17830);
				}

				if(m_target->getRace() == RACE_GNOME)
				{
					if( m_target->getGender() == 0 )
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10148);
					else
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10149);
				}
				if(m_target->getRace() == RACE_DWARF)
				{
					if( m_target->getGender() == 0 )
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10141);
					else
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10142);
				}
				if(m_target->getRace() == RACE_HUMAN)
				{
					if( m_target->getGender() == 0 )
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10137);
					else
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10138);
				}
				if(m_target->getRace() == RACE_NIGHTELF)
				{
					if( m_target->getGender() == 0 )
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10143);
					else
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 10144);
				}
				if(m_target->getRace() == RACE_DRAENEI)
				{
					if( m_target->getGender() == 0 )
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 17827);
					else
						m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, 17828);
				}
			}
			else
				m_target->SetUInt32Value( UNIT_FIELD_DISPLAYID, m_target->GetUInt32Value( UNIT_FIELD_NATIVEDISPLAYID ) );
		}break;

		case 42365:	// murloc costume
			m_target->SetUInt32Value( UNIT_FIELD_DISPLAYID, apply ? 21723 : m_target->GetUInt32Value( UNIT_FIELD_NATIVEDISPLAYID ) );
			break;

		case 118://polymorph
		case 851:
		case 5254:
		case 12824:
		case 12825:
		case 12826:
		case 13323:
		case 15534:
		case 22274:
		case 23603:
		case 28270:	 // Polymorph: Cow
		case 28271:	 // Polymorph: Turtle
		case 28272:	 // Polymorph: Pig
		case 61025:  // Polymorph: Serpent
		case 61305:  // Polymorph: Black Cat
		case 61721:  // Polymorph: Rabbit
		case 61780:  // Polymorph: Turkey
			{
				if(!displayId)
				{
					switch(GetSpellProto()->Id)
					{
					case 28270:	 // Cow
						displayId = 1060;
						break;

					case 28272:	 // Pig
						displayId = 16356 + RandomUInt(2);
						break;

					case 28271:	 // Turtle
						displayId = 16359 + RandomUInt(2);
						break;

					default:
						displayId = 856;
						break;

					}
				}

				if(apply)
				{
					if (GetUnitCaster() != NULL && m_target->GetTypeId() == TYPEID_UNIT)
						m_target->GetAIInterface()->AttackReaction(GetUnitCaster(), 1, GetSpellId());

					Unit *u_caster = GetUnitCaster();
					if( ( displayId == 856 || displayId == 857 ) && u_caster && u_caster->IsPlayer() && SafePlayerCast( u_caster )->HasGlyphWithID( GLYPH_MAGE_PENGUIN ) == true )
						displayId = 28216;

					m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, displayId);

					// remove the current spell (for channelers)
					if(m_target->m_currentSpell && m_target->GetGUID() != m_casterGuid &&
						m_target->m_currentSpell->getState() == SPELL_STATE_CASTING )
					{
						m_target->m_currentSpell->safe_cancel();
					}

					sEventMgr.AddEvent(this, &Aura::EventPeriodicHeal1,(uint32)1000,EVENT_AURA_PERIODIC_HEAL,1000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
					m_target->polySpell = GetSpellProto()->Id;
					//some reported that sheeps keep melee fighting
					if( m_target->IsPlayer() )
						SafePlayerCast( m_target )->EventAttackStop();
					//this glyph will remove DOTS from the target
					if( u_caster && u_caster->IsPlayer() && SafePlayerCast( u_caster )->HasGlyphWithID( GLYPH_MAGE_POLYMORPH ) == true )
					{
						for(uint32 x=MAX_POSITIVE_AURAS;x<m_target->m_auras_neg_size;x++)
							if( m_target->m_auras[x] && ( m_target->m_auras[x]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_DAMAGING ) && m_target->m_auras[x]->GetSpellProto()->quick_tickcount > 1 )
								m_target->m_auras[x]->Remove();
					}
				}
				else
				{
					m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, m_target->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID));
					m_target->polySpell = 0;
				}
			}break;

		case 19937:
			{
				if (apply)
				{
					// TODO: Sniff the spell / item, we need to know the real displayID
					// guessed this may not be correct
					// human = 7820
					// dwarf = 7819
					// halfling = 7818
					// maybe 7842 as its from a lesser npc
					m_target->SetUInt32Value (UNIT_FIELD_DISPLAYID, 7842);
				}
				else
				{
					m_target->SetUInt32Value (UNIT_FIELD_DISPLAYID, m_target->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID));
				}
			}break;
		case 47585:  // priest - Dispersion
			{
				if(apply)
				{
					// remove the caster from imparing movements
					m_target->RemoveAllAurasByMechanic( MECHANIC_ENSNARED, -1, false );
					m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, displayId);

					//ammount is in pct
					// Walla:
					// The wrong way to regen mana.. there is a spell for that
					// http://www.wowhead.com/spell=49766
					//mod->m_amount = m_target->GetUInt32Value(UNIT_FIELD_MAXPOWER1) * 6 / 100;
					//sEventMgr.AddEvent(this, &Aura::EventPeriodicEnergize,(uint32)mod->m_amount,(uint32)POWER_TYPE_MANA, EVENT_AURA_PERIODIC_ENERGIZE,1000,6,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
				}
				else
				{
					m_target->SetUInt32Value(UNIT_FIELD_DISPLAYID, m_target->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID));
				}
			}break;

		default:
		{
			if(!displayId) 
			{ 
				return;
			}

			if (apply)
				{
					m_target->SetUInt32Value (UNIT_FIELD_DISPLAYID, displayId);
				}
				else
				{
					m_target->SetUInt32Value (UNIT_FIELD_DISPLAYID, m_target->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID));
				}
		}break;
	};

	if( m_target )
		m_target->EventModelChange();
}

void Aura::SpellAuraModSpellCritChance(bool apply)
{
	int32 amt;
	if(apply)
	{
		amt = mod->m_amount;
		if(amt<0)
			SetNegative();
		else
			SetPositive();
	}
	else
		amt = -mod->m_amount;

	m_target->spellcritperc += amt;

	if( m_target->IsPlayer() )
	{
		SafePlayerCast( m_target )->SetSpellCritFromSpell( SafePlayerCast( m_target )->GetSpellCritFromSpell() + amt );
		SafePlayerCast( m_target )->UpdateChanceFields();
	}
}

void Aura::SpellAuraIncreaseSwimSpeed(bool apply)
{
	if(apply)
	{
		if(m_target->isAlive())  SetPositive();
		m_target->m_swimSpeed = 0.04722222f*(100+mod->m_amount);
	}
	else
		m_target->m_swimSpeed = PLAYER_NORMAL_SWIM_SPEED;
	if(m_target->GetTypeId() == TYPEID_PLAYER)
	{
		WorldPacket data(SMSG_FORCE_SWIM_SPEED_CHANGE, 17);
		data << m_target->GetNewGUID();
		data << (uint32)2;
		data << m_target->m_swimSpeed;
		SafePlayerCast( m_target )->GetSession()->SendPacket(&data);
	}
}

void Aura::SpellAuraModCratureDmgDone(bool apply)
{
	if(m_target->GetTypeId() == TYPEID_PLAYER)
	{
		if(apply)
		{
			for(uint32 x = 0; x < CREATURE_TYPES; x++)
				if(mod->m_miscValue & (((uint32)1)<<x))
					SafePlayerCast( m_target )->IncreaseDamageByType[x+1] += mod->m_amount;

			mod->m_amount < 0 ? SetNegative() : SetPositive();
		}
		else
			for(uint32 x = 0; x < CREATURE_TYPES; x++)
				if(mod->m_miscValue & (((uint32)1)<<x) )
					SafePlayerCast( m_target )->IncreaseDamageByType[x+1] -= mod->m_amount;
	}
}

void Aura::SpellAuraPacifySilence(bool apply)
{
	// Can't Attack or Cast Spells
	if(apply)
	{
		if(m_spellProto->Id == 24937)
			SetPositive();
		else
			SetNegative();

		m_target->m_pacified++;
		m_target->m_silenced++;
		m_target->m_special_state |= UNIT_STATE_PACIFY | UNIT_STATE_SILENCE;
		m_target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED | UNIT_FLAG_SILENCED);

		if(m_target->m_currentSpell && m_target->GetGUID() != m_casterGuid &&
			m_target->m_currentSpell->getState() == SPELL_STATE_CASTING )
			{
				m_target->m_currentSpell->safe_cancel();
			}
	}
	else
	{
		m_target->m_pacified--;

		if(m_target->m_pacified == 0)
		{
			m_target->m_special_state &= ~UNIT_STATE_PACIFY;
			m_target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
		}

		m_target->m_silenced--;

		if(m_target->m_silenced == 0)
		{
			m_target->m_special_state &= ~UNIT_STATE_SILENCE;
			m_target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SILENCED);
		}
	}
}

void Aura::SpellAuraModScale(bool apply)
{
	if( apply )
		m_target->ObjectSizeMods.push_front( mod );
	else
		m_target->ObjectSizeMods.remove( mod );
	m_target->UpdateSizeMod();
}

void Aura::SpellAuraPeriodicHealthFunnel(bool apply)
{
	if(apply)
	{
		uint32 amt = mod->m_amount;
		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHasteDots() );
		}
		if( period < 500 )
			period = 500;
		sEventMgr.AddEvent(this, &Aura::EventPeriodicHealthFunnel, amt,
			EVENT_AURA_PERIODIC_HEALTH_FUNNEL, period , 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

void Aura::EventPeriodicHealthFunnel(uint32 amount)
{
	//Blood Siphon
	//Deals 200 damage per second.
	//Feeding Hakkar 1000 health per second.
	Unit* m_caster = GetUnitCaster();
	if(!m_caster)
	{ 
		return;
	}
	if(m_target->isAlive() && m_caster->isAlive())
	{

		m_caster->DealDamage(m_target, amount, 0, 0, GetSpellId(),false);
		uint32 newHealth = m_caster->GetUInt32Value(UNIT_FIELD_HEALTH) + 1000;

		uint32 mh = m_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
		if(newHealth <= mh)
			m_caster->SetUInt32Value(UNIT_FIELD_HEALTH, newHealth);
		else
			m_caster->SetUInt32Value(UNIT_FIELD_HEALTH, mh);

		m_target->SendSpellPeriodicAuraLog(m_target, m_target, m_spellProto->Id, m_spellProto->School, 1000, 0, 0, FLAG_PERIODIC_LEECH, 0);

		m_caster->RemoveAurasByHeal();
	}
}

void Aura::SpellAuraPeriodicManaLeech(bool apply)
{
	if(apply)
	{
		uint32 amt=mod->m_amount;

		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHasteDots() );
		}
		if( period < 500 )
			period = 500;

		sEventMgr.AddEvent(this, &Aura::EventPeriodicManaLeech,amt,mod->i,
			EVENT_AURA_PERIODIC_LEECH, period ,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

void Aura::EventPeriodicManaLeech(uint32 amount,uint32 effect_index)
{
	Unit* m_caster = GetUnitCaster();
	if(!m_caster)
	{ 
		return;
	}
	if(m_target->isAlive() && m_caster->isAlive())
	{
		int32 take_amt = (int32)min( amount , m_target->GetUInt32Value( UNIT_FIELD_POWER1 ) );

		switch( m_spellProto->NameHash )
		{
			case SPELL_HASH_VIPER_STING:
			{
				if( m_target->GetUInt32Value( UNIT_FIELD_POWER1 ) * ( take_amt / 100.0f ) < m_caster->GetUInt32Value(UNIT_FIELD_MAXPOWER1) * 0.02f )
					take_amt = float2int32( m_target->GetUInt32Value( UNIT_FIELD_POWER1 ) * ( take_amt / 100.0f ) );
				else
					take_amt = float2int32( m_caster->GetUInt32Value(UNIT_FIELD_MAXPOWER1) * 0.02f );
			}break;
			case SPELL_HASH_DRAIN_MANA: // Warlock - Drain mana 
			{
				if( m_target->GetUInt32Value( UNIT_FIELD_POWER1 ) * take_amt / 100 < m_caster->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) * 6 / 100 )
					take_amt = float2int32( m_target->GetUInt32Value( UNIT_FIELD_POWER1 ) * ( take_amt / 100.0f ) );
				else
					take_amt = int32( m_caster->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) * 6 / 100 );
			}break;
		}

		// Drained amount should be reduced by resilence 
		if(m_target->IsPlayer())
		{
			float amt_reduction_pct = 2.0f * SafePlayerCast(m_target)->CalcRating( PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE ) / 100.0f;
			if( amt_reduction_pct > 0.8 )
				amt_reduction_pct = 0.8f;
			take_amt = float2int32( take_amt - (take_amt * amt_reduction_pct) );
		}

		int32 add_amt = (int32)MIN( float2int32( take_amt * GetSpellProto()->EffectConversionCoef[effect_index] ), (int32)m_target->GetUInt32Value( UNIT_FIELD_POWER1 ) );
		uint32 cm = m_caster->GetUInt32Value(UNIT_FIELD_POWER1) + add_amt;
		uint32 mm = m_caster->GetUInt32Value(UNIT_FIELD_MAXPOWER1);
		if(cm <= mm)
			m_caster->SetUInt32Value(UNIT_FIELD_POWER1, cm);
		else
			m_caster->SetUInt32Value(UNIT_FIELD_POWER1, mm);
		m_target->ModUnsigned32Value(UNIT_FIELD_POWER1, -take_amt);
	}
}

void Aura::SpellAuraModCastingSpeed(bool apply)
{
	float change;

	if(apply)
		change = -float(mod->m_amount / 100.0f); //value is positiv and represents a decrease : 1 - x%
	else
		change = float(mod->m_amount / 100.0f);

	m_target->ModFloatValue(UNIT_MOD_CAST_SPEED, change );
}

void Aura::SpellAuraFeignDeath(bool apply)
{
	if( m_target->IsPlayer() )
	{
		Player* pTarget = SafePlayerCast( m_target );
		WorldPacket data(50);
		if( apply )
		{
			pTarget->EventAttackStop();
			pTarget->SetFlag( UNIT_FIELD_FLAGS_2, 1 );
			pTarget->SetFlag( UNIT_FIELD_FLAGS, UNIT_FLAG_FEIGN_DEATH );
			//pTarget->SetFlag( UNIT_FIELD_FLAGS, UNIT_FLAG_DEAD );
			pTarget->SetFlag( UNIT_DYNAMIC_FLAGS, U_DYN_FLAG_DEAD );
			//pTarget->SetUInt32Value( UNIT_NPC_EMOTESTATE, EMOTE_STATE_DEAD );

			data.SetOpcode( SMSG_START_MIRROR_TIMER );
			data << uint32( TIMER_FEIGNDEATH );		// type
			data << uint32( GetDuration() );
			data << uint32( GetDuration() );
			data << uint32( 0xFFFFFFFF );
			data << uint8( 0 );
			data << uint32( m_spellProto->Id );		// ???
			pTarget->GetSession()->SendPacket( &data );

			data.Initialize( SMSG_CLEAR_TARGET );
			data << pTarget->GetGUID();
//			pTarget->setDeathState(DEAD);

			//now get rid of mobs agro. pTarget->CombatStatus.AttackersForgetHate() - this works only for already attacking mobs
		    for(std::set<Object*>::iterator itr = pTarget->GetInRangeSetBegin(); itr != pTarget->GetInRangeSetEnd(); itr++ )
			{
				if((*itr)->IsUnit() && SafeUnitCast((*itr))->isAlive())
				{
					if((*itr)->GetTypeId()==TYPEID_UNIT)
						SafeUnitCast(*itr)->GetAIInterface()->RemoveThreatByPtr( pTarget );
					
					//if this is player and targeting us then we interrupt cast
					if( (*itr)->IsPlayer() )
					{
						Player* plr = SafePlayerCast( *itr );

						if( plr->isCasting() && plr->GetSelection() == pTarget->GetGUID() )
							plr->CancelSpell( NULL ); //cancel current casting spell

						plr->GetSession()->SendPacket( &data );
					}
				}
			}
			pTarget->setDeathState(ALIVE);
		}
		else
		{
			pTarget->RemoveFlag(UNIT_FIELD_FLAGS_2, 1);
			pTarget->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_FEIGN_DEATH);
			pTarget->RemoveFlag(UNIT_DYNAMIC_FLAGS, U_DYN_FLAG_DEAD);
			//pTarget->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DEAD);
			//pTarget->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
			data.SetOpcode(SMSG_STOP_MIRROR_TIMER);
			data << uint32(2);
			pTarget->GetSession()->SendPacket(&data);
		}
	}
}

void Aura::SpellAuraModDisarm(bool apply)
{
	if(apply)
	{
		if( p_target != NULL && p_target->IsInFeralForm() ) 
		{ 
			return;
		}

		SetNegative();

		m_target->disarmed = true;
		m_target->m_special_state |= UNIT_STATE_DISARMED;
		m_target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISARMED);
	}
	else
	{
		m_target->disarmed = false;
		m_target->m_special_state &= ~UNIT_STATE_DISARMED;
		m_target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISARMED);
	}
	if( m_target && m_target->IsPlayer() )
		SafePlayerCast( m_target )->UpdateAttackSpeed();
}

void Aura::SpellAuraModStalked(bool apply)
{
	if(apply)
	{
		m_target->stalkedby = m_casterGuid;
		SetNegative();
	}
	else
	{
		m_target->stalkedby = 0;
	}
}

void Aura::SpellAuraSchoolAbsorb(bool apply)
{
	Absorb *ab;
	if(apply)
	{
		SetPositive();

		int32 val = mod->m_amount;
		Player * plr = SafePlayerCast( GetUnitCaster() );
		if( plr )
		{
			//This will fix talents that affects damage absorved.
//			int flat = 0;
//			SM_FIValue( plr->SM_FMiscEffect, &flat, GetSpellProto()->SpellGroupType );
//			val += float2int32( float( val * flat ) / 100.0f );

			//For spells Affected by Bonus Healing we use Dspell_coef_override.
			if( GetSpellProto()->fixed_dddhcoef >= 0 )
				val += float2int32( float( plr->HealDoneMod ) * GetSpellProto()->fixed_dddhcoef );
			//For spells Affected by Bonus Damage we use OTspell_coef_override.
			else if( GetSpellProto()->fixed_hotdotcoef >= 0 )
				val += float2int32( float( plr->GetDamageDoneMod( GetSpellProto()->School ) ) * GetSpellProto()->fixed_hotdotcoef );
		}

		ab = new Absorb;
		ab->amt = val;
		ab->spellid = GetSpellId();
		ab->caster = m_casterGuid;
		
		//maybe later other spells will use it
		if( GetSpellProto()->NameHash == SPELL_HASH_ANTI_MAGIC_SHELL )
			ab->MaxAbsorbCoeff = 0.75f;

		//maybe later other spells will use it
		if( GetSpellProto()->NameHash == SPELL_HASH_THE_GENERAL_S_HEART )
			ab->MaxAbsorbPerHit = 205;

		for(uint32 x=0;x<7;x++)
			if (mod->m_miscValue & (((uint32)1)<<x) )
				ab->schools[x]=true;
			else
				ab->schools[x]=false;
		m_target->Absorbs.push_front(ab);
		//store this custome structure to make sure we delete the right one on aura remove
		temp_custom_structure_holder = ab;
	}
	else
	{
		m_target->Absorbs.SafeRemove( (Absorb*)temp_custom_structure_holder, temp_custom_structure_holder != NULL );
	}
}

void Aura::SpellAuraModSpellCritChanceSchool(bool apply)
{
	if(apply)
	{
		for(uint32 x=0;x<7;x++)
			if (mod->m_miscValue & (((uint32)1)<<x))
				m_target->SpellCritChanceSchool[x] += mod->m_amount;
		if(mod->m_amount < 0)
			SetNegative();
		else
			SetPositive();
	}
	else
	{
		for(uint32 x=0;x<7;x++)
		{
			if (mod->m_miscValue & (((uint32)1)<<x) )
			{
				m_target->SpellCritChanceSchool[x] -= mod->m_amount;
				/*if(m_target->SpellCritChanceSchool[x] < 0)
					m_target->SpellCritChanceSchool[x] = 0;*/
			}
		}
	}
	if(m_target->IsPlayer())
		SafePlayerCast( m_target )->UpdateChanceFields();
}

void Aura::SpellAuraModPowerCost(bool apply)
{
	int32 val = (apply) ? mod->m_amount : -mod->m_amount;
	if (apply)
	{
		if(val > 0)
			SetNegative();
		else
			SetPositive();
	}
	for(uint32 x=0;x<7;x++)
		if (mod->m_miscValue & (((uint32)1)<<x) )
			m_target->ModFloatValue(UNIT_FIELD_POWER_COST_MULTIPLIER+x,val/100.0f);
}

void Aura::SpellAuraModPowerCostSchool(bool apply)
{
	if(apply)
	{
		for(uint32 x=1;x<7;x++)
			if (mod->m_miscValue & (((uint32)1)<<x) )
				m_target->PowerCostMod[x] += mod->m_amount;
	}
	else
	{
		for(uint32 x=1;x<7;x++)
		{
			if (mod->m_miscValue & (((uint32)1)<<x) )
			{
				m_target->PowerCostMod[x] -= mod->m_amount;
			}
		}
	}
}

void Aura::SpellAuraReflectSpellsSchool(bool apply)
{
	if(apply)
	{
		CommitPointerListNode<struct ReflectSpellSchool> *itr;
		m_target->m_reflectSpellSchool.BeginLoop();
		for(itr = m_target->m_reflectSpellSchool.begin(); itr != m_target->m_reflectSpellSchool.end();itr = itr->Next() )
			if(GetSpellProto()->Id == itr->data->spellId)
				m_target->m_reflectSpellSchool.SafeRemove(itr,1);
		m_target->m_reflectSpellSchool.EndLoopAndCommit();

		ReflectSpellSchool *rss = new ReflectSpellSchool;

		rss->chance = mod->m_amount;
		rss->spellId = GetSpellId();
		rss->require_aura_hash = 0;
		if(m_spellProto->Attributes == 0x400D0 && m_spellProto->AttributesEx == 0)
		{
			rss->school = (int)(log10((float)mod->m_miscValue) / log10((float)2));
		}
		else
			rss->school = m_spellProto->School;

		m_target->m_reflectSpellSchool.push_front(rss);
	}
	else
	{
		CommitPointerListNode<struct ReflectSpellSchool> *itr;
		m_target->m_reflectSpellSchool.BeginLoop();
		for(itr = m_target->m_reflectSpellSchool.begin(); itr != m_target->m_reflectSpellSchool.end();itr = itr->Next() )
			if(GetSpellProto()->Id == itr->data->spellId)
				m_target->m_reflectSpellSchool.SafeRemove(itr,1);
		m_target->m_reflectSpellSchool.EndLoopAndCommit();
	}
}

void Aura::SpellAuraModLanguage(bool apply)
{
	if(apply)
		m_target->m_modlanguage = mod->m_miscValue;
	else
		m_target->m_modlanguage = -1;
}

void Aura::SpellAuraAddFarSight(bool apply)
{
	if(apply)
	{
		if(m_target->GetTypeId() != TYPEID_PLAYER)
		{ 
			return;
		}

		//FIXME:grep aka Nublex will fix this
		//Make update circle bigger here
	}
	else
	{
		//Destroy new updated objects here if they are still out of update range
		//w/e
	}
}

void Aura::SpellAuraMechanicImmunity(bool apply)
{
//sLog.outString( "Aura::SpellAuraMechanicImmunity begun." );
	if(apply)
	{
		//sLog.outString( "mod->m_miscValue = %u" , (uint32) mod->m_miscValue );
		//sLog.outString( "Incrementing MechanicsDispels (current value: %u, new val: %u)" , m_target->MechanicsDispels[mod->m_miscValue] , m_target->MechanicsDispels[mod->m_miscValue] + 1 );
		assert(mod->m_miscValue < MECHANIC_TOTAL);
		m_target->MechanicsDispels[mod->m_miscValue]++;

		if(mod->m_miscValue != MECHANIC_HEALING && mod->m_miscValue != MECHANIC_INVULNERABLE && mod->m_miscValue != MECHANIC_SHIELDED) // dont remove bandages, Power Word and protection effect
		{
			// Supa's test run of Unit::RemoveAllAurasByMechanic 
			if( m_target ) 
			{	// just to be sure?
				m_target->RemoveAllAurasByMechanic( (uint32)mod->m_miscValue , (uint32)(-1) , false );

				if( mod->m_miscValue == MECHANIC_ROOTED && m_spellProto->NameHash == SPELL_HASH_BLINK )
				{
					m_target->RemoveAllAurasByMechanic( MECHANIC_STUNNED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_SAPPED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_INCAPACIPATED , (uint32)(-1) , false );
					for(uint32 x= MAX_POSITIVE_AURAS; x < MAX_NEGATIVE_AURAS1(m_target); ++x)
						if(m_target->m_auras[x])
							for(uint32 y = 0; y < 3; ++y)
								switch(m_target->m_auras[x]->GetSpellProto()->EffectApplyAuraName[y])
								{
									case SPELL_AURA_MOD_STUN:
									case SPELL_AURA_MOD_ROOT:
										m_target->m_auras[x]->Remove();
										y=100;	//removed aura, do not use it anymore !
								}
				}
				else if( mod->m_miscValue == MECHANIC_ROOTED && m_spellProto->NameHash == SPELL_HASH_HAND_OF_FREEDOM && m_target->HasPassiveAurasWithNameHash( SPELL_HASH_DIVINE_PURPOSE ) )
				{
					//only with Divine Purpose
					m_target->RemoveAllAurasByMechanic( MECHANIC_STUNNED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_SAPPED , (uint32)(-1) , false );
				}
				else if( m_spellProto->NameHash == SPELL_HASH_PVP_TRINKET || m_spellProto->NameHash == SPELL_HASH_EVERY_MAN_FOR_HIMSELF )
				{
					m_target->RemoveAllAurasByMechanic( MECHANIC_CHARMED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_DISORIENTED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_DISTRACED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_FLEEING , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_ROOTED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_ENSNARED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_STUNNED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_FROZEN , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_INCAPACIPATED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_POLYMORPHED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_HORRIFIED , (uint32)(-1) , false );
					m_target->RemoveAllAurasByMechanic( MECHANIC_SAPPED , (uint32)(-1) , false );
					// insignia of the A/H
					for(uint32 x= MAX_POSITIVE_AURAS; x < MAX_NEGATIVE_AURAS1(m_target); ++x)
						if(m_target->m_auras[x])
							for(uint32 y = 0; y < 3; ++y)
								switch(m_target->m_auras[x]->GetSpellProto()->EffectApplyAuraName[y])
								{
									case SPELL_AURA_MOD_STUN:
									case SPELL_AURA_MOD_CONFUSE:
									case SPELL_AURA_MOD_ROOT:
									case SPELL_AURA_MOD_FEAR:
									case SPELL_AURA_MOD_DECREASE_SPEED:
										m_target->m_auras[x]->Remove();
										y=100;	//removed aura, do not use it anymore !
								}
				}
			}
		}
		else
			SetNegative();
	}
	else if( m_target->MechanicsDispels[mod->m_miscValue] > 0 )
		m_target->MechanicsDispels[mod->m_miscValue]--;
}

void Aura::SpellAuraMounted(bool apply)
{
	if(!p_target) 
	{ 
		return;
	}

	/*Shady: Is it necessary? Stealth should be broken since all spells with Mounted SpellEffect don't have "does not break stealth" flag (except internal Video mount spell). 
	So commented, cause we don't need useless checks and hackfixes*/
	/* if(m_target->IsStealth())
	{
		uint32 id = m_target->m_stealth;
		m_target->m_stealth = 0;
		m_target->RemoveAura(id);
	}*/

	if(apply)
	{
		SetPositive();

		//p_target->AdvanceSkillLine(762); // advance riding skill

		if(p_target->m_bg)
			p_target->m_bg->HookOnMount(p_target);

		if(p_target->m_MountSpellId)
			m_target->RemoveAura(p_target->m_MountSpellId);

		m_target->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_MOUNT);

		p_target->m_MountSpellId = m_spellProto->Id;

		if( p_target->GetShapeShift() && p_target->GetShapeShift() != FORM_BATTLESTANCE && p_target->GetShapeShift() != FORM_DEFENSIVESTANCE && p_target->GetShapeShift() != FORM_BERSERKERSTANCE && p_target->m_ShapeShifted != m_spellProto->Id )
			p_target->RemoveAura( p_target->m_ShapeShifted );

		//check if this mount is a vehicle. If it is then we spawn one and mount the player in it
		CreatureProto* cp = CreatureProtoStorage.LookupEntry(mod->m_miscValue);
		if( cp && cp->vehicleId )
			p_target->ConvertToVehicle( cp, false, true );
		uint32 displayId;
		if( p_target->mount_look_override == 0 )
		{
			//hackfix for invincible - non flying zones
//			if( (GetSpellProto()->NameHash == SPELL_HASH_INVINCIBLE || GetSpellProto()->NameHash == SPELL_HASH_CELESTIAL_STEED )
//				m_target->GetMapMgr()->GetMapId() != 530 && m_target->GetMapMgr()->GetMapId() != 571 )
//				mod->m_miscValue = GetSpellProto()->EffectMiscValue[ 1 ];	//this is plain wrong !

			CreatureInfo* ci = CreatureNameStorage.LookupEntry(mod->m_miscValue);
			if(!ci) 
			{ 
				return;
			}
			displayId = ci->Male_DisplayID;

		}
		else 
			displayId = p_target->mount_look_override;
		if(!displayId)
		{ 
			return;
		}

		p_target->flying_aura = 0;
		m_target->SetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID , displayId);
		//m_target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_MOUNTED_TAXI);

/*
		// Zack : disabled due to exploits
		// 1) summon was not always the same
		// 2) people were able to heal pet very easely
		//desummon summons
		if( p_target->GetSummon() != NULL )
		{
			p_target->GetSummon()->Remove( false, true, false ); // just remove for later re-call
			mod->fixed_amount[mod->i] = 1;
		}*/
	}
	else
	{
		p_target->m_MountSpellId = 0;
		p_target->flying_aura = 0;
		m_target->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, 0);
		//m_target->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_MOUNTED_TAXI);
			
		//if we had pet then respawn
//		if( mod->fixed_amount[mod->i]==1 )
//			p_target->SpawnActivePet();// get pet back
		p_target->RemoveAurasByInterruptFlag( AURA_INTERRUPT_ON_DISMOUNT );
		p_target->DestoryVehicle();	//only does it if we were owner. But we were trust me !
	}
}

void Aura::SpellAuraModDamagePercDone(bool apply)
{
	float val = (apply) ? mod->m_amount/100.0f : -mod->m_amount/100.0f;

	switch (GetSpellId()) //dirty or mb not fix bug with wand specializations
	{
	case 6057:
	case 6085:
	case 14524:
	case 14525:
	case 14526:
	case 14527:
	case 14528:
		return;
	}
	if(m_target->IsPlayer())
	{
		if(GetSpellProto()->EquippedItemClass==-1)//does not depend on weapon
			for(uint32 x=0;x<7;x++)
				if (mod->m_miscValue & (((uint32)1)<<x) )
					m_target->ModFloatValue(PLAYER_FIELD_MOD_DAMAGE_DONE_PCT + x, val); // display to client (things that are weapon dependant dont get displayed)
		if(mod->m_miscValue & 1)
		{
			if(apply)
			{
				WeaponModifier *md = new WeaponModifier;
				md->value = val;
				md->wclass = GetSpellProto()->EquippedItemClass;
				md->subclass = GetSpellProto()->EquippedItemSubClass;
				md->spellentry = GetSpellProto();
				p_target->damagedone.push_front( md );
			}
			else
			{
				SimplePointerListNode<WeaponModifier> *i;
				for( i=p_target->damagedone.begin();i!=p_target->damagedone.end();i = i->Next() )
					if( i->data->spellentry == GetSpellProto() )
					{
						p_target->damagedone.remove( i, 1 );
						break;
					}
			}
		}
	}
	else
	{
		for(uint32 x=0;x<7;x++)
			if (mod->m_miscValue & (((uint32)1)<<x) )
				SafeCreatureCast(m_target)->ModDamageDonePct[x] += val;
	}
	m_target->CalcDamage();
}

void Aura::SpellAuraModPercStat(bool apply)
{
	int32 val;
	if(apply)
	{
		val = mod->m_amount;
		if(val<0)
			SetNegative();
		else
			SetPositive();
	}
	else
		val= -mod->m_amount;

	if (mod->m_miscValue == -1)//all stats
	{
		if(m_target->IsPlayer())
		{
			for(uint32 x=0;x<5;x++)
			{
				if(mod->m_amount>0)
					SafePlayerCast( m_target )->StatModPctPos[x] += val;
				else
					SafePlayerCast( m_target )->StatModPctNeg[x] -= val;

				SafePlayerCast( m_target )->CalcStat(x);
			}

			SafePlayerCast( m_target )->UpdateStats();
			SafePlayerCast( m_target )->UpdateChances();
		}
		else
		{
			for(uint32 x=0;x<5;x++)
			{
				SafeCreatureCast(m_target)->StatModPct[x] += val;
				SafeCreatureCast(m_target)->CalcStat(x);
			}
		}
	}
	else
	{
		ASSERT(mod->m_miscValue < 5);
		if(m_target->IsPlayer())
		{
			if(mod->m_amount>0)
				SafePlayerCast( m_target )->StatModPctPos[mod->m_miscValue] += val;
			else
				SafePlayerCast( m_target )->StatModPctNeg[mod->m_miscValue] -= val;

			SafePlayerCast( m_target )->CalcStat(mod->m_miscValue);

			SafePlayerCast( m_target )->UpdateStats();
			SafePlayerCast( m_target )->UpdateChances();
		}
		else if(m_target->GetTypeId() == TYPEID_UNIT)
		{
			SafeCreatureCast(m_target)->StatModPct[mod->m_miscValue]+=val;
			SafeCreatureCast(m_target)->CalcStat(mod->m_miscValue);
		}
	}
}

void Aura::SpellAuraSplitDamage(bool apply)
{
	Unit * caster;

	if( !m_target || !m_target->IsUnit() )
	{ 
		return;
	}

	caster = SafeUnitCast( GetCaster() );
	if(!caster)
	{ 
		return;
	}

	if( GetSpellProto()->c_is_flags & SPELL_FLAG_IS_DMGSPLIT_CASTER_TARGET )
	{
		if( caster->m_damageSplitTarget == NULL )
			caster->m_damageSplitTarget = new DamageSplitTarget;

		if(apply)
		{
			caster->m_damageSplitTarget->m_flatDamageSplit = 0;
			caster->m_damageSplitTarget->m_spellId = GetSpellProto()->Id;
	//		caster->m_damageSplitTarget->m_pctDamageSplit = mod->m_miscValue / 100.0f;	//wtf, this is school mask not value
			caster->m_damageSplitTarget->m_pctDamageSplit = mod->m_amount / 100.0f;
			caster->m_damageSplitTarget->damage_type = mod->m_type;
			caster->m_damageSplitTarget->creator = (void*)this;
			caster->m_damageSplitTarget->m_target = m_target->GetGUID();
		}
		else if( caster->m_damageSplitTarget )
		{
			delete caster->m_damageSplitTarget;
			caster->m_damageSplitTarget = NULL;
		}
	}

	if( ( GetSpellProto()->c_is_flags & SPELL_FLAG_IS_DMGSPLIT_TARGET_CASTER ) || ( GetSpellProto()->c_is_flags & ( SPELL_FLAG_IS_DMGSPLIT_TARGET_CASTER | SPELL_FLAG_IS_DMGSPLIT_CASTER_TARGET ) ) == 0 )
	{
		if( m_target->m_damageSplitTarget == NULL )
			m_target->m_damageSplitTarget = new DamageSplitTarget;

		if(apply)
		{
			m_target->m_damageSplitTarget->m_flatDamageSplit = 0;
			m_target->m_damageSplitTarget->m_spellId = GetSpellProto()->Id;
	//		m_target->m_damageSplitTarget->m_pctDamageSplit = mod->m_miscValue / 100.0f;	//wtf, this is school mask not value
			m_target->m_damageSplitTarget->m_pctDamageSplit = mod->m_amount / 100.0f;
			m_target->m_damageSplitTarget->damage_type = mod->m_type;
			m_target->m_damageSplitTarget->creator = (void*)this;
			m_target->m_damageSplitTarget->m_target = caster->GetGUID();
		}
		else if( m_target->m_damageSplitTarget )
		{
			delete m_target->m_damageSplitTarget;
			m_target->m_damageSplitTarget = NULL;
		}
	}
}

void Aura::SpellAuraModRegen(bool apply)
{
	if(apply)//seems like only positive
	{
		SetPositive ();
		sEventMgr.AddEvent(this, &Aura::EventPeriodicHeal1,(uint32)((this->GetSpellProto()->EffectBasePoints[mod->i]+1)/5)*3,
			EVENT_AURA_PERIODIC_REGEN,3000,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

void Aura::SpellAuraPeriodicDummy(bool apply)
{
	if( apply )
	{
		SetPositive();
		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHasteDots() );
		}
		if( period < 500 )
			period = 500;
		mod->fixed_amount[0] = 0;	//just in case we need to count something :P
		sEventMgr.AddEvent(this, &Aura::SpellAuraPeriodicDummyTrigger,(uint32)mod->i,
			EVENT_PERIODIC_DUMMY_AURA_TRIGGER, period ,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

void Aura::SpellAuraPeriodicDummyTrigger(uint32 mod_i)
{
	switch( m_spellProto->NameHash )
	{
		case SPELL_HASH_ASPECT_OF_THE_VIPER:
			if( p_target )
				EventPeriodicEnergizeVariable((uint32)m_modList[mod_i].m_amount,(uint32)m_modList[mod_i].m_miscValue);
		break;
		case SPELL_HASH_MANA_BARRIER:	//boss fight spell
			{
				int32 missing_health = m_target->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) - m_target->GetUInt32Value( UNIT_FIELD_HEALTH );
				int32 convert_mana_to_health;
				if( missing_health > (int32)m_target->GetUInt32Value( UNIT_FIELD_POWER1 ) )
					convert_mana_to_health = (int32)m_target->GetUInt32Value( UNIT_FIELD_POWER1 );
				else
					convert_mana_to_health = missing_health;
				m_target->ModUnsigned32Value( UNIT_FIELD_HEALTH, convert_mana_to_health );
				m_target->ModUnsigned32Value( UNIT_FIELD_POWER1, -convert_mana_to_health );
			}
			break;
		case SPELL_HASH_MIRRORED_SOUL:
			{
				//this is only executed on the boss, rest just suck the dmg up
				if( m_target->GetEntry() != 36502 )
					return;
				//is this first tick ?
				if( m_modList[ mod_i ].fixed_amount[0] == 0 )
					m_modList[ mod_i ].fixed_amount[0] = m_target->GetUInt32Value( UNIT_FIELD_HEALTH );
				int32 missing_health = m_target->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) - m_target->GetUInt32Value( UNIT_FIELD_HEALTH );
				if( missing_health <= 0 )
					return;
				uint32 dealdamage = missing_health * 20 / 100;
				//search for the victim 
				m_target->AquireInrangeLock(); //make sure to release lock before exit function !
				std::set<Object*>::iterator itr;
				for( itr = m_target->GetInRangeSetBegin(); itr != m_target->GetInRangeSetEnd(); itr++ )
				{
					if( (*itr) == m_target || !(*itr)->IsUnit() || !SafeUnitCast((*itr))->isAlive())
						continue;
					
					//yes, it is the same aura
					if( SafeUnitCast((*itr))->HasAurasWithNameHash( SPELL_HASH_MIRRORED_SOUL ) )
					{
						m_target->DealDamage( SafeUnitCast((*itr)), dealdamage, 0,0, 69051 );
						//break; //- more then 1 target ?
					}
				}
				m_target->ReleaseInrangeLock();						
			}break;
		default:
			EventPeriodicDrink( uint32(float2int32(float(m_modList[mod_i].m_amount)/5.0f)));
	}
}

void Aura::EventPeriodicEnergizeVariable( uint32 amount, uint32 type )
{
	uint32 POWER_TYPE = UNIT_FIELD_POWER1 + type;
	
	ASSERT(POWER_TYPE<=UNIT_FIELD_POWER5);
	uint32 curEnergy = m_target->GetUInt32Value( POWER_TYPE );
	uint32 maxEnergy = m_target->GetUInt32Value( POWER_TYPE + 6 );

	switch( m_spellProto->NameHash )
	{
		case SPELL_HASH_ASPECT_OF_THE_VIPER:
			float regen, manaPct;
			// http://www.wowwiki.com/Aspect_of_the_Viper
			// MP5Viper = Intellect  22/35  ( 0.9 - Manacurrent / Manamax ) + Intellect  0.11 -- by wowwiki
			// MP5Viper = Intellect  ( 0.55 - 22/35  ( Manacurrent / Manamax - 0.2 ) -- by emsy... 55 is stored in DBC, maybe blizz changes it in future
			// We're including also the Effect[1]:Dummy (35% of player's level) from the AotV in this
			//   it's missing some values in dbc plus it saves one event this way
							
			manaPct = (float)curEnergy / (float)maxEnergy;
			if( manaPct < 0.2f )
				manaPct = 0.2f;
			if( manaPct > 0.9f )
				manaPct = 0.9f;

			regen = ( (float)amount / 100 - 22.0f / 35.0f * (manaPct - 0.2f) ) * (float)p_target->GetUInt32Value( UNIT_FIELD_STAT3 ) + (float)p_target->getLevel()*m_spellProto->EffectBasePoints[1]/100;
			amount = (int)regen;
		break;
		default:
			//something
			;
	}

	if( GetUnitCaster() != NULL )
		GetUnitCaster()->Energize( m_target, m_spellProto->Id, amount, type );
}

void Aura::EventPeriodicDrink(uint32 amount)
{
	uint32 v = m_target->GetUInt32Value(UNIT_FIELD_POWER1) + amount;
	if( v > m_target->GetUInt32Value(UNIT_FIELD_MAXPOWER1) )
		v = m_target->GetUInt32Value(UNIT_FIELD_MAXPOWER1);

	m_target->SetUInt32Value(UNIT_FIELD_POWER1, v);
	m_target->SendSpellPeriodicAuraLog(m_target, m_target, m_spellProto->Id, m_spellProto->School, v, 0, 0, FLAG_PERIODIC_ENERGIZE, 0);
}

void Aura::EventPeriodicHeal1(uint32 amount)
{
	if(!m_target->isAlive())
	{ 
		return;
	}

	uint32 ch = m_target->GetUInt32Value(UNIT_FIELD_HEALTH);
	ch+=amount;
	uint32 mh = m_target->GetUInt32Value(UNIT_FIELD_MAXHEALTH);

	if(ch>mh)
		m_target->SetUInt32Value(UNIT_FIELD_HEALTH,mh);
	else
		m_target->SetUInt32Value(UNIT_FIELD_HEALTH,ch);

	if(GetSpellProto()->AuraInterruptFlags & AURA_INTERRUPT_ON_STAND_UP)
	{
		m_target->Emote(EMOTE_ONESHOT_EAT);
	}
	else
	{
		if(!(m_spellProto->BGR_one_buff_on_target & SPELL_TYPE_ARMOR))
			SendPeriodicHealAuraLog( amount );
	}

	m_target->RemoveAurasByHeal();
}

void Aura::SpellAuraModPowerRegen(bool apply)
{
	if(!mod->m_amount)
	{ 
		return;
	}

	if(apply)
	{
		if (mod->m_amount>0)
			SetPositive();
		else
			SetNegative();
		//because you can change power type with some auras
		if( mod->m_miscValue == m_target->GetPowerType() )
			mod->fixed_amount[0] = mod->m_amount;
		else
			mod->fixed_amount[0] = 0;
	}
	if ( m_target->IsPlayer() && mod->fixed_amount[0] )
	{
		int32 val = (apply) ? mod->fixed_amount[0]: -mod->fixed_amount[0];
		SafePlayerCast( m_target )->m_ModInterrMRegen +=val;
		SafePlayerCast( m_target )->UpdateStats();
	}
}

void Aura::SpellAuraChannelDeathItem(bool apply)
{
	SetNegative(); //this should always be negative as npcs remove negative auras on death

	if(apply)
	{
		//dont need for now
	}
	else
	{
		if( m_target->GetTypeId() == TYPEID_UNIT || m_target->GetTypeId() == TYPEID_PLAYER )
		{
			if ( m_target->GetTypeId() == TYPEID_UNIT && SafeCreatureCast(m_target)->GetCreatureInfo() != NULL && SafeCreatureCast(m_target)->GetCreatureInfo()->Type == CRITTER )
			{ 
				return;
			}

			if(m_target->IsDead())
			{
				Player *pCaster = m_target->GetMapMgr()->GetPlayer( m_casterGuid );
				if(!pCaster)
				{ 
					return;
				}
				/*int32 delta=pCaster->getLevel()-m_target->getLevel();
				if(abs(delta)>5)
					return;*/

				uint32 itemid = GetSpellProto()->EffectItemType[mod->i];

				ItemPrototype *proto = ItemPrototypeStorage.LookupEntry(itemid);
				if(pCaster->GetItemInterface()->CalculateFreeSlots(proto) > 0)
				{
					Item *item = objmgr.CreateItem(itemid,pCaster);
					if(!item) 
					{ 
						return;
					}


					item->SetUInt64Value(ITEM_FIELD_CREATOR,pCaster->GetGUID());
					if(!pCaster->GetItemInterface()->AddItemToFreeSlot(&item))
					{
						pCaster->GetItemInterface()->BuildInventoryChangeError(0, 0, INV_ERR_INVENTORY_FULL);
						item->DeleteMe();
						return;
					}
					/*WorldPacket data(45);
					pCaster->GetSession()->BuildItemPushResult(&data, pCaster->GetGUID(), 1, 1, itemid ,0,0xFF,1,0xFFFFFFFF);
					pCaster->SendMessageToSet(&data, true);					*/
					SlotResult * lr = pCaster->GetItemInterface()->LastSearchResult();
					pCaster->GetSession()->SendItemPushResult(item,true,false,true,true,lr->ContainerSlot,lr->Slot,1);
				}
			}
		}
	}
}

void Aura::SpellAuraModDamagePercTaken(bool apply)
{
	float val;
	if(apply)
	{
		val = mod->m_amount/100.0f;
		if(val <= 0)
			SetPositive();
		else
			SetNegative();
	}
	else
	{
		val= -mod->m_amount/100.0f;
	}

	if( m_spellProto->NameHash == SPELL_HASH_ARDENT_DEFENDER ) // Ardent Defender it only applys on 20% hp :/
	{
		m_target->DamageTakenPctModOnHP35 += val;
		return;
	}

	for(uint32 x=0;x<7;x++)
		if (mod->m_miscValue & (((uint32)1)<<x) )
			m_target->DamageTakenPctMod[x]+=val;
}

void Aura::SpellAuraModRegenPercent(bool apply)
{
	if(apply)
		m_target->PctRegenModifier += mod->m_amount;
	else
		m_target->PctRegenModifier -= mod->m_amount;
}

void Aura::SpellAuraPeriodicDamagePercent(bool apply)
{
	if(apply)
	{
		//uint32 gr = GetSpellProto()->SpellGroupType;
		//if(gr)
		//{
		//	Unit*c=GetUnitCaster();
		//	if(c)
		//	{
		//		SM_FIValue(c->SM_FDOT,(int32*)&dmg,gr);
		//		SM_PIValue(c->SM_PDOT,(int32*)&dmg,gr);
		//	}
		//}

		/*if(m_spellProto->Id == 28347) //Dimensional Siphon
		{
			uint32 dmg = (m_target->GetUInt32Value(UNIT_FIELD_MAXHEALTH)*5)/100;
			sEventMgr.AddEvent(this, &Aura::EventPeriodicDamagePercent, dmg,
				EVENT_AURA_PERIODIC_DAMAGE_PERCENT, 1000, 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}
		else*/
		{
			uint32 dmg = mod->m_amount;

			//hasting affects ticks too
			int32 period = GetSpellProto()->EffectAmplitude[mod->i];
			Unit *Unitc = GetUnitCaster();
			if( Unitc )
			{
				SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
				period = (uint32)(period * Unitc->GetSpellHasteDots() );
			}
			if( period < 500 )
				period = 500;

			sEventMgr.AddEvent(this, &Aura::EventPeriodicDamagePercent, dmg,
				EVENT_AURA_PERIODIC_DAMAGE_PERCENT, period ,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}
		SetNegative();
	}
}

void Aura::EventPeriodicDamagePercent(uint32 amount)
{
	//DOT
	if(!m_target->isAlive())
	{ 
		return;
	}
	if(m_target->SchoolImmunityList[GetSpellProto()->School])
	{ 
		return;
	}

	uint32 damage = float2int32(amount/100.0f*m_target->GetUInt32Value(UNIT_FIELD_MAXHEALTH));

	Unit * c = GetUnitCaster();

	if( m_target->m_damageSplitTarget)
	{
		damage = m_target->DoDamageSplitTarget(damage, GetSpellProto()->School, false);
	}

	if(c)
		c->SpellNonMeleeDamageLog(m_target, GetSpellProto()->Id, damage, pSpellId==0, true);
	else
		m_target->SpellNonMeleeDamageLog(m_target, GetSpellProto()->Id, damage, pSpellId==0, true);
}

void Aura::SpellAuraModResistChance(bool apply)
{
	apply ? m_target->m_resistChance = mod->m_amount : m_target->m_resistChance = 0;
}

void Aura::SpellAuraModDetectRange(bool apply)
{
	Unit*m_caster=GetUnitCaster();
	if(!m_caster)
	{ 
		return;
	}
	if(apply)
	{
		SetNegative();
		m_caster->setDetectRangeMod(m_target->GetGUID(), mod->m_amount);
	}
	else
	{
		m_caster->unsetDetectRangeMod(m_target->GetGUID());
	}
}

void Aura::SpellAuraPreventsFleeing(bool apply)
{
	// Curse of Recklessness
}

void Aura::SpellAuraModUnattackable(bool apply)
{
/*
		Also known as Apply Aura: Mod Uninteractible
		Used by: Spirit of Redemption, Divine Intervention, Phase Shift, Flask of Petrification
		It uses one of the UNIT_FIELD_FLAGS, either UNIT_FLAG_NOT_SELECTABLE or UNIT_FLAG_NOT_ATTACKABLE_2
*/
}

void Aura::SpellAuraInterruptRegen(bool apply)
{
	if(apply)
		m_target->m_interruptRegen++;
	else
	{
		m_target->m_interruptRegen--;
		  if(m_target->m_interruptRegen < 0)
			m_target->m_interruptRegen = 0;
	}
}

void Aura::SpellAuraGhost(bool apply)
{
	if(m_target->GetTypeId() == TYPEID_PLAYER)
	{
		m_target->m_invisible = apply;

		if(apply)
		{
			SetNegative();
			SafePlayerCast( m_target )->SetMovement(MOVE_WATER_WALK);
		}
		else
			SafePlayerCast( m_target )->SetMovement(MOVE_LAND_WALK);
	}
}

void Aura::SpellAuraMagnet(bool apply)
{
	if(apply)
	{
		Unit *caster = GetUnitCaster();
		if (!caster)
		{ 
			return;
		}
		SetPositive();
		m_target->m_magnetcaster = caster->GetGUID();
		caster->m_magnetcaster = 0xFF000001;	//we presume we can absorb always 1 
	}
	else
	{
		if( m_target )
			m_target->m_magnetcaster = 0;
		Unit *caster = GetUnitCaster();
		if( caster )
			caster->m_magnetcaster = 0;
	}
}

void Aura::SpellAuraManaShield(bool apply)
{
	if(apply)
	{
		SetPositive();
		m_target->m_manashieldamt = mod->m_amount ;
		m_target->m_manaShieldId = GetSpellId();
	}
	else
	{
		m_target->m_manashieldamt = 0;
		m_target->m_manaShieldId = 0;
	}
}

void Aura::SpellAuraSkillTalent(bool apply)
{
	if (m_target->IsPlayer())
	{
		if(apply)
		{
			SetPositive();
			SafePlayerCast( m_target )->_ModifySkillBonus(mod->m_miscValue,mod->m_amount);
		}
		else
			SafePlayerCast( m_target )->_ModifySkillBonus(mod->m_miscValue,-mod->m_amount);

		SafePlayerCast( m_target )->UpdateStats();
	}
}

void Aura::SpellAuraModAttackPower(bool apply)
{
	if(mod->m_amount<0)
		SetNegative();
	else
		SetPositive();

	m_target->ModUnsigned32Value(UNIT_FIELD_ATTACK_POWER_MODS,apply? mod->m_amount : -mod->m_amount);

	m_target->CalcDamage();
}

void Aura::SpellAuraVisible(bool apply)
{
	//Show positive spells on target
	if(apply)
	{
		SetNegative();
	}
}

void Aura::SpellAuraModResistancePCT(bool apply)
{
	uint32 Flag = mod->m_miscValue;
	int32 amt;
	if(apply)
	{
		amt=mod->m_amount;
	 //   if(amt>0)SetPositive();
	   // else SetNegative();
	}
	else
		amt= -mod->m_amount;

	for(uint32 x=0;x<7;x++)
	{
		if(Flag & (((uint32)1)<< x))
		{
			if(m_target->GetTypeId() == TYPEID_PLAYER)
			{
				if(mod->m_amount>0)
				{
					SafePlayerCast( m_target )->ResistanceModPctPos[x] += amt;
				}
				else
				{
					SafePlayerCast( m_target )->ResistanceModPctNeg[x] -= amt;
				}
				SafePlayerCast( m_target )->CalcResistance(x);

			}
			else if(m_target->GetTypeId() == TYPEID_UNIT)
			{
				SafeCreatureCast(m_target)->ResistanceModPct[x] += amt;
				SafeCreatureCast(m_target)->CalcResistance(x);
			}
		}
	}
}

void Aura::SpellAuraModCreatureAttackPower(bool apply)
{
	if( apply )
	{
		for( uint32 x = 0; x < CREATURE_TYPES; x++ )
			if( mod->m_miscValue & ( ( ( uint32 )1 ) << x ) )
				m_target->CreatureAttackPowerMod[x+1] += mod->m_amount;

		if( mod->m_amount > 0 )
			SetPositive();
		else
			SetNegative();
	}
	else
	{
		for( uint32 x = 0; x < CREATURE_TYPES; x++ )
		{
			if( mod->m_miscValue & ( ( ( uint32 )1 ) << x ) )
			{
				m_target->CreatureAttackPowerMod[x+1] -= mod->m_amount;
			}
		}
	}
	m_target->CalcDamage();
}

void Aura::SpellAuraModTotalThreat( bool apply )
{	
	if( apply )
	{
		if( mod->m_amount < 0 )
			SetPositive();
		else
			SetNegative();

		m_target->ModThreatModifyer( mod->m_amount );
	}
	else
		m_target->ModThreatModifyer(-(mod->m_amount));
}

void Aura::SpellAuraWaterWalk( bool apply )
{
	SetPositive();

	if( !m_target->IsPlayer() )
	{ 
		return;
	}
	if( apply )
		SafePlayerCast( m_target )->SetMovement(MOVE_WATER_WALK);
	else
		SafePlayerCast( m_target )->SetMovement(MOVE_LAND_WALK);
}

void Aura::SpellAuraFeatherFall( bool apply )
{
	SetPositive();

	if( !m_target->IsPlayer() )
	{ 
		return;
	}
	if( apply )
		SafePlayerCast( m_target )->SetMovement(MOVE_FEATHER_FALL);
	else
		SafePlayerCast( m_target )->SetMovement(MOVE_NORMAL_FALL);
}

void Aura::SpellAuraHover( bool apply )
{
	SetPositive();

	if( !m_target->IsPlayer() )
	{ 
		return;
	}
	if( apply )
		SafePlayerCast( m_target )->SetMovement(MOVE_HOVER);
	else
		SafePlayerCast( m_target )->SetMovement(MOVE_NO_HOVER);
}

void Aura::SpellAuraAddPctMod( bool apply )
{
	int32 val = apply ? mod->m_amount : -mod->m_amount;
	uint32 *AffectedGroups = GetSpellProto()->EffectSpellGroupRelation[mod->i];

//	sLog.outDebug("%s: AffectedGroups %I64x ,the smt type %u, val=%d",__FUNCTION__,AffectedGroups,mod->m_miscValue, val);
	switch( mod->m_miscValue )//let's generate warnings for unknown types of modifiers
	{
	case SMT_CRITICAL:
		SendModifierLog( &m_target->SM_CriticalChance, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_DURATION:
		SendModifierLog( &m_target->SM_PDur, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_RADIUS:
		SendModifierLog( &m_target->SM_PRadius, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_RANGE:
		SendModifierLog( &m_target->SM_PRange, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_CAST_TIME:
		SendModifierLog( &m_target->SM_PCastTime, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_COST:
		SendModifierLog( &m_target->SM_PCost, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_CRITICAL_DAMAGE:
		SendModifierLog( &m_target->SM_PCriticalDamage, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_SPELL_VALUE_DOT:
		SendModifierLog( &m_target->SM_PDOT, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_NONINTERRUPT:
		SendModifierLog( &m_target->SM_PNonInterrupt, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_JUMP_REDUCE:
		SendModifierLog( &m_target->SM_PJumpReduce, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_EFFECT_BONUS:
		SendModifierLog( &m_target->SM_PEffectBonus, val, AffectedGroups, mod->m_miscValue, true );
		break;
	case SMT_EFFECT_TARGET:
		SendModifierLog( &m_target->SM_PEffectTargetBonus, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_DAMAGE_DONE:
		SendModifierLog( &m_target->SM_PDamageBonus, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_MISC_EFFECT:
		SendModifierLog( &m_target->SM_PMiscEffect, val, AffectedGroups, mod->m_miscValue, true );
		break;

	case SMT_PENALTY:
		SendModifierLog( &m_target->SM_PPenalty, val, AffectedGroups, mod->m_miscValue, true );
		break;
	//TODO: disabled until clarified
	/*
	case SMT_ATTACK_POWER_BONUS:
		SendModifierLog(&m_target->SM_PAPBonus,val,AffectedGroups,mod->m_miscValue,true);
		break;
	*/
	case SMT_COOLDOWN_DECREASE:
	case SMT_CAST_COOLDOWN:
		SendModifierLog( &m_target->SM_PCooldownTime, val, AffectedGroups, mod->m_miscValue, true );
		break;

	//there are 2 spells in 2.1.1 that will only need attack power bonus
	case SMT_ATTACK_POWER_AND_DMG_BONUS:
		{
			if(GetSpellId()==36563 || GetSpellId()==37186)
			{
				SendModifierLog( &m_target->SM_PDamageBonus, val, AffectedGroups, mod->m_miscValue, true );
			}
			else
			{
				//these are seal of crusader spells
				SendModifierLog( &m_target->SM_PDamageBonus, val, AffectedGroups, mod->m_miscValue, true );
				SendModifierLog( &m_target->SM_PAPBonus, val, AffectedGroups, mod->m_miscValue, true );
			}
		}break;
	case SMT_CHARGES:
		SendModifierLog(&m_target->SM_PCharges, val, AffectedGroups,mod->m_miscValue);
		break;
	case SMT_THREAT_REDUCED:
		SendModifierLog(&m_target->SM_PThreat, val, AffectedGroups, mod->m_miscValue, true);
		break;
	//TODO:
	/*
	case SMT_TRIGGER:
	case SMT_TIME:
		break;
	*/
	//unknown Modifier type
	case SMT_RESIST_DISPEL:
		SendModifierLog( &m_target->SM_PRezist_dispell, val, AffectedGroups, mod->m_miscValue, true );
		break;
	//!!!!!!!! these are custom
	case SMT_ADD_TO_EFFECT_VALUE_1:
		SendModifierLog(&m_target->SM_PAddEffect1, val, AffectedGroups,SMT_MISC_EFFECT, true);
		break;
	case SMT_ADD_TO_EFFECT_VALUE_2:
		SendModifierLog(&m_target->SM_PAddEffect2, val, AffectedGroups,SMT_MISC_EFFECT, true);
		break;
	case SMT_ADD_TO_EFFECT_VALUE_3:
		SendModifierLog(&m_target->SM_PAddEffect3, val, AffectedGroups,SMT_MISC_EFFECT, true);
		break;
	default:
		sLog.outError( "Unknown spell modifier type %u in spell %u.<<--report this line to the developer\n", mod->m_miscValue, GetSpellId() );
		//don't add val, though we could formaly could do,but as we don't know what it is-> no sense
		break;
	}
}


void Aura::SendModifierLog(int32 **ObjectSMValues,int32 newval,uint32 *AffectsSMMask,uint8 type, uint8 pct )
{
	//WorldPacket data( SMSG_SET_FLAT_SPELL_MODIFIER + pct, 6 );
	packetSMSG_SET_FLAT_SPELL_MODIFIER data;

	if( *ObjectSMValues == 0 )
	{
		*ObjectSMValues = new int32[SPELL_GROUPS];
		for( uint32 x = 0; x < 32; x++ )
		{
			uint32 tmask = 1 << x;
			for( uint32 i=0;i<3;i++)
				if( tmask & AffectsSMMask[i] )
				{
					(*ObjectSMValues)[x+i*32] = newval;
					if( !m_target->IsPlayer() )
						continue;

					data.group = x+i*32;
					data.type = type;
					data.v = newval;
					if( pct )
						SafePlayerCast(m_target)->GetSession()->OutPacket( SMSG_SET_PCT_SPELL_MODIFIER, sizeof( packetSMSG_SET_FLAT_SPELL_MODIFIER ), &data );
					else
						SafePlayerCast(m_target)->GetSession()->OutPacket( SMSG_SET_FLAT_SPELL_MODIFIER, sizeof( packetSMSG_SET_FLAT_SPELL_MODIFIER ), &data );
				}
				else
					(*ObjectSMValues)[x+i*32] = 0;
		}
	}
	else
	{
		for( uint32 x = 0; x < 32; x++ )
		{
			uint32 tmask = 1 << x;
			for( uint32 i=0;i<3;i++)
				if( tmask & AffectsSMMask[i] )
				{
					(*ObjectSMValues)[x+i*32] += newval;
					if( !m_target->IsPlayer() )
						continue;

					data.group = x+i*32;
					data.type = type;
					data.v = (*ObjectSMValues)[x+i*32];
					SafePlayerCast(m_target)->GetSession()->OutPacket( SMSG_SET_FLAT_SPELL_MODIFIER+ pct, sizeof( packetSMSG_SET_FLAT_SPELL_MODIFIER ), &data );
				}
		}
	}
}

/*
void Aura::SpellAuraAddTargetTrigger(bool apply)
{
	if (m_target == NULL)
	{ 
		return;
	}

	if( apply )
	{
		ProcTriggerSpell pts;
		pts.parentId = GetSpellProto()->Id;
		pts.caster = m_casterGuid;
		int charges = GetSpellProto()->procCharges;
		if( (GetSpellProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && u_caster != NULL )
		{
			SM_FIValue( u_caster->SM_FCharges, &charges, GetSpellProto()->SpellGroupType );
			SM_PIValue( u_caster->SM_PCharges, &charges, GetSpellProto()->SpellGroupType );
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
			float spell_flat_modifers=0;
			float spell_pct_modifers=0;
			SM_FIValue(u_caster->SM_FCharges,&spell_flat_modifers,GetSpellProto()->SpellGroupType);
			SM_FIValue(u_caster->SM_PCharges,&spell_pct_modifers,GetSpellProto()->SpellGroupType);
			if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
				printf("!!!!!spell charge bonus mod flat %f , spell range bonus pct %f , spell range %f, spell group %u\n",spell_flat_modifers,spell_pct_modifers,maxRange,m_spellInfo->SpellGroupType);
#endif
		}
		pts.procCharges = charges;
		pts.i = mod->i;
		pts.LastTrigger = 0;

		if(GetSpellProto()->EffectTriggerSpell[mod->i])
			pts.spellId=GetSpellProto()->EffectTriggerSpell[mod->i];
		else
		{
			sLog.outDebug("Warning,trigger spell is null for spell %u",GetSpellProto()->Id);
			return;
		}
		m_target->m_procSpells.push_front(pts);
		sLog.outDebug("%u is registering %u chance %u flags %u charges %u triggeronself %u interval %u\n",pts.origId,pts.spellId,pts.procChance,m_spellProto->procFlags & ~PROC2_TARGET_SELF,charges,m_spellProto->procFlags & PROC2_TARGET_SELF,m_spellProto->proc_interval);
	}
	else
	{
		for(std::list<struct ProcTriggerSpell>::iterator itr = m_target->m_procSpells.begin();itr != m_target->m_procSpells.end();itr++)
		{
			if(itr->parentId == GetSpellId() && itr->caster == m_casterGuid && !itr->deleted)
			{
				itr->deleted = true;
				break; //only 1 instance of a proc spell per caster ?
			}
		}
	}
}*/

void Aura::SpellAuraModPowerRegPerc(bool apply)
{
	if( mod->m_miscValue < 0 || mod->m_miscValue >= POWER_TYPE_COUNT )
	{
		sLog.outDebug("Spell %u has missing regen mod type \n", GetSpellProto()->Id );
		return;
	}
	if( mod->m_miscValue == POWER_TYPE_RUNES && m_target->IsPlayer() )
	{
		float val;
		if(apply)
			val = ((float)(mod->m_amount))/100.0f;
		else
			val = -((float)(mod->m_amount))/100.0f;
		SafePlayerCast( m_target )->ModFloatValue( PLAYER_RUNE_REGEN_1 + GetSpellProto()->EffectMiscValueB[ mod->i ], val );
	}
	else
	{
		if(apply)
			m_target->PctPowerRegenModifier[mod->m_miscValue] += ((float)(mod->m_amount))/100.0f;
		else
			m_target->PctPowerRegenModifier[mod->m_miscValue] -= ((float)(mod->m_amount))/100.0f;

		if (m_target->IsPlayer())
			SafePlayerCast( m_target )->UpdateStats();
	}
}

void Aura::SpellAuraOverrideClassScripts(bool apply)
{
	Unit *caster = GetUnitCaster();
	if( m_target->IsPlayer() == false )
	{ 
		return;
	}
	//misc value is spell to add
	//spell familyname && grouprelation

	Player *p_target = SafePlayerCast( m_target );

	switch( GetSpellProto()->NameHash )
	{
		case SPELL_HASH_TORMENT_THE_WEAK:
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = mod->m_amount;
				so->ApplyHandler = &HandleTormentTheWeak;
				//no effect on custom handlers
//				so->required_namehash[0] = SPELL_HASH_FROSTFIRE_BOLT;.....
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_SOUL_SIPHON:
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = mod->m_amount / 3;
				so->ApplyHandler = &HandleSoulSiphon;
				//no effect on custom handlers
//				so->required_namehash[0] = SPELL_HASH_DRAIN_LIFE;
//				so->required_namehash[1] = SPELL_HASH_DRAIN_SOUL;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_SHATTER:
		{
			uint32 val = 0;
			if( GetSpellProto()->Id == 11170 )
				val = 17;	//stupid value is in description
			else if( GetSpellProto()->Id == 11170 )
				val = 34;	//stupid value is in description
			else if( GetSpellProto()->Id == 11170 )
				val = 50;	//stupid value is in description
			if( apply )
				p_target->m_RootedCritChanceBonus += val;
			else if( p_target->m_RootedCritChanceBonus >= val )
				p_target->m_RootedCritChanceBonus -= val;
			else
				p_target->m_RootedCritChanceBonus = 0;
		}break;
		case SPELL_HASH_GLYPH_OF_LESSER_HEALING_WAVE:
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 + mod->m_amount;
				so->ApplyHandler = &HandleGlyphOfLesserHealingWave;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_GLYPH_OF_REGROWTH:
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 + mod->m_amount;
				so->ApplyHandler = &HandleGlyphOfRegrowth;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_INCREASED_LESSER_HEALING_WAVE:	//there are 3
		case SPELL_HASH_SAVAGE_TOTEM_OF_THE_THIRD_WIND:
		case SPELL_HASH_HATEFUL_TOTEM_OF_THE_THIRD_WIND:
		case SPELL_HASH_DEADLY_TOTEM_OF_THE_THIRD_WIND:
		case SPELL_HASH_LK_ARENA_4_TOTEM_OF_THE_THIRD_WIND:
		case SPELL_HASH_LK_ARENA_5_TOTEM_OF_THE_THIRD_WIND:
		case SPELL_HASH_LK_ARENA_6_TOTEM_OF_THE_THIRD_WIND:
		case SPELL_HASH_COPY_OF_DEADLY_TOTEM_OF_THE_THIRD_WIND:
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount[0] = mod->m_amount;	//the heal effect
				so->required_namehash[0] = SPELL_HASH_LESSER_HEALING_WAVE;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_INCREASED_FLASH_OF_LIGHT_HEALING:
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount[0] = mod->m_amount;	//the heal effect
				so->required_namehash[0] = SPELL_HASH_FLASH_OF_LIGHT;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_INCREASED_SHOCK_DAMAGE:	
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount[0] = mod->m_amount;	
				so->required_namehash[0] = SPELL_HASH_FROST_SHOCK;
				so->required_namehash[1] = SPELL_HASH_EARTH_SHOCK;
				so->required_namehash[2] = SPELL_HASH_FLAME_SHOCK;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_IMPROVED_MOONFIRE:	
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount[0] = mod->m_amount;	
				so->mod_amount[1] = mod->m_amount;	
				so->required_namehash[0] = SPELL_HASH_MOONFIRE;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_MOLTEN_FURY:	
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 + mod->m_amount;	
				so->mod_amount_pct[1] = 100 + mod->m_amount;	
				so->mod_amount_pct[2] = 100 + mod->m_amount;	
				so->ApplyHandler = &HandleMoltenFury;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_INCREASED_LIGHTNING_DAMAGE:	
		case SPELL_HASH_TOTEM_OF_HEX:	
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount[0] = mod->m_amount;	
				so->required_namehash[0] = SPELL_HASH_CHAIN_LIGHTNING;
				so->required_namehash[1] = SPELL_HASH_LIGHTNING_BOLT;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_INCREASED_REJUVENATION_HEALING:	
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount[0] = mod->m_amount;	
				so->mod_amount[1] = mod->m_amount;	
				so->mod_amount[2] = mod->m_amount;	
				so->required_namehash[0] = SPELL_HASH_REJUVENATION;
				so->required_aura_type[0] = SPELL_AURA_PERIODIC_HEAL;
				so->required_aura_type[1] = SPELL_AURA_PERIODIC_HEAL;
				so->required_aura_type[2] = SPELL_AURA_PERIODIC_HEAL;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_IMPROVED_CONSECRATION:	
		case SPELL_HASH_LIBRAM_OF_RESURGENCE:	
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				if( GetSpellProto()->Id == 38422 )
					so->mod_amount_pct[0] = 100 + mod->m_amount;	
				else
					so->mod_amount[0] = mod->m_amount;	
				so->required_namehash[0] = SPELL_HASH_CONSECRATION;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_IMPROVED_STARFIRE:	
		case SPELL_HASH_IDOL_OF_THE_SHOOTING_STAR:	
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount[0] = mod->m_amount;	
				so->required_namehash[0] = SPELL_HASH_STARFIRE;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_STARFIRE_BONUS:	
		{
			if( apply )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 + mod->m_amount;	
				so->ApplyHandler = &HandleStarfireBonus;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_DEATH_S_EMBRACE:	
		{
			if( apply && mod->i == 0 )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 + mod->m_amount;	
				so->mod_amount_pct[1] = 100 + GetSpellProto()->EffectBasePoints[1] + 1;	
				so->ApplyHandler = &HandleDeatsEmbrace;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_TEST_OF_FAITH:	
		{
			if( apply && mod->i == 0 )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 + mod->m_amount;	
				so->ApplyHandler = &HandleTestOfFaith;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_MERCILESS_COMBAT:	
		{
			if( apply && mod->i == 0 )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 + mod->m_amount;	
				so->ApplyHandler = &HandleMercilessCombat;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_RAGE_OF_RIVENDARE:	
		{
			if( apply && mod->i == 0 )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 + mod->m_amount;	
				so->mod_amount_pct[1] = 100 + mod->m_amount;	
				so->mod_amount_pct[2] = 100 + mod->m_amount;	
				so->ApplyHandler = &HandleRageOfRivedare;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_TUNDRA_STALKER:	
		{
			if( apply && mod->i == 0 )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 + mod->m_amount;	
				so->ApplyHandler = &HandleTundraStalker;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_MARKED_FOR_DEATH_53241:	
		case SPELL_HASH_MARKED_FOR_DEATH_67823:	
		{
			if( apply && mod->i == 0 )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 + mod->m_amount;	
				so->ApplyHandler = &HandleMarkedForDeath;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_NOURISH_HEAL_BOOST:	
		{
			if( apply && mod->i == 0 )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 + mod->m_amount;	
				so->ApplyHandler = &HandleNourishHealBoost;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_ASPECT_MASTERY:	
		{
			if( apply && mod->i == 0 )
			{
				SpellEffectOverrideScript *so = new SpellEffectOverrideScript;
				so->mod_amount_pct[0] = 100 - (GetSpellProto()->EffectBasePoints[0] + 1);	
				so->mod_amount[1] = (GetSpellProto()->EffectBasePoints[1] + 1);	
				so->mod_amount_pct[2] = 100 + GetSpellProto()->EffectBasePoints[2] + 1;	
				so->ApplyHandler = &HandleAspectMastery;
				//std stuff
				so->ori_spell_id = GetSpellProto()->Id;
				p_target->mSpellOverrideMap.push_front( so );
				mod->extension = (void*)so;
			}
		}break;
		case SPELL_HASH_ENIGMA_BLIZZARD_BONUS:
		{
		}break;
	};

	if( apply == false )
	{
		SimplePointerListNode<SpellEffectOverrideScript> *itr,*itr2;
		for(itr = p_target->mSpellOverrideMap.begin(); itr != p_target->mSpellOverrideMap.end();)
		{
			itr2 = itr;
			itr = itr->Next();
			if( (void*)(itr2->data) == mod->extension )
			{
				if( itr2->data->RemoveHandler ) 
					itr2->data->RemoveHandler( this, GetUnitCaster(), p_target, mod->m_amount, mod->i, itr2->data );
				p_target->mSpellOverrideMap.remove( itr2, 1 );
			}
		}
	}
	//Adding bonus to effect
/*	switch(mod->m_miscValue)
	{
		//----Shatter---
		// Increases crit chance against rooted targets by (Rank * 10)%.
		case 849:
		case 910:
		case 911:
		case 912:
		case 913:
			if (m_target->IsPlayer())
			{
				int32 val = (apply) ? (mod->m_miscValue-908)*10 : -(mod->m_miscValue-908)*10;
				if (mod->m_miscValue==849)
					val = (apply) ? 10 : -10;
				SafePlayerCast( m_target )->m_RootedCritChanceBonus += val;
			}
			break;
// ----?
		case 3736:	//
		case 4415:
		case 4418:
		case 4554:
		case 4555:
		case 4953:
		case 5142:
		case 5147:
		case 5148:
			{
			if(apply)
			{
				OverrideIdMap::iterator itermap = objmgr.mOverrideIdMap.find(mod->m_miscValue);
                if(itermap == objmgr.mOverrideIdMap.end())
                 {
                     sLog.outError("Unable to find override with overrideid: %u", mod->m_miscValue);
                     break;
                 }

				std::list<SpellEntry *>::iterator itrSE = itermap->second->begin();

				SpellOverrideMap::iterator itr = plr->mSpellOverrideMap.find((*itrSE)->Id);

				if(itr != plr->mSpellOverrideMap.end())
				{
					ScriptOverrideList::iterator itrSO;
					for(itrSO = itr->second->begin(); itrSO != itr->second->end(); ++itrSO)
					{
						if((*itrSO)->id == (uint32)mod->m_miscValue)
						{
							if((int32)(*itrSO)->mod_amount > mod->m_amount)
							{
								(*itrSO)->mod_amount = mod->m_amount;
							}
							return;
						}
					}
					classScriptOverride *cso = new classScriptOverride;
					cso->mod_amount = mod->m_amount;
					cso->id = mod->m_miscValue;
					itr->second->push_back(cso);
				}
				else
				{
					classScriptOverride *cso = new classScriptOverride;
					if( cso == NULL )
						return;
					cso->mod_amount = mod->m_amount;
					cso->id = mod->m_miscValue;
					ScriptOverrideList *lst = new ScriptOverrideList();
					lst->push_back(cso);

					for(;itrSE != itermap->second->end(); ++itrSE)
					{
						plr->mSpellOverrideMap.insert( SpellOverrideMap::value_type( (*itrSE)->Id, lst) );
					}
				}
			}
			else
			{
				OverrideIdMap::iterator itermap = objmgr.mOverrideIdMap.find(mod->m_miscValue);
				SpellOverrideMap::iterator itr = plr->mSpellOverrideMap.begin(), itr2;
				while(itr != plr->mSpellOverrideMap.end())
				{
					std::list<SpellEntry *>::iterator itrSE = itermap->second->begin();
					for(;itrSE != itermap->second->end(); ++itrSE)
					{
						if(itr->first == (*itrSE)->Id)
						{
							itr2 = itr++;
							plr->mSpellOverrideMap.erase(itr2);
							break;
						}
					}
					// Check if the loop above got to the end, if so it means the item wasn't found
					// and the itr wasn't incremented so increment it now.
					if(itrSE == itermap->second->end())   
						itr++;
				}
			}
		}break;
//		case 19421: //hunter : Improved Hunter's Mark
//		case 19422:
//		case 19423:
//		case 19424:
//		case 19425:
//			{
//				//this shoul actually add a new functionality to the spell and not override it. There is a lot to decode and to be done here
//			}break;
		case 4992: // Warlock: Soul Siphon
		case 4993:
			{
				if(m_target) 
				{
					if( apply )
						m_target->m_soulSiphon.max+= mod->m_amount;
					else
						m_target->m_soulSiphon.max-= mod->m_amount;
				}
			}break;
		case 7871://Glyph of Lesser Healing Wave
			{
				if( m_target->IsPlayer() == false )
					return;
				Player *target = SafePlayerCast(m_target);
				if( GetSpellProto()->NameHash != SPELL_HASH_GLYPH_OF_LESSER_HEALING_WAVE )
				{
					if( apply )
					{
						classScriptOverride *handler;
						if( target->mSpellOverrideMapNameHash[ SPELL_HASH_LESSER_HEALING_WAVE ] )
							handler = target->mSpellOverrideMapNameHash[ SPELL_HASH_LESSER_HEALING_WAVE ];
						else
							handler = new classScriptOverride;
						handler->mod_amount_pct += mod->m_amount;
						handler->requires_special_test =  true;
					}
					else if( target->mSpellOverrideMapNameHash[ SPELL_HASH_LESSER_HEALING_WAVE ] )
						target->mSpellOverrideMapNameHash[ SPELL_HASH_LESSER_HEALING_WAVE ]->mod_amount_pct -= mod->m_amount;
				}
			}break;
	default:
		sLog.outError("Unknown override report to devs: %u", mod->m_miscValue);
	};
	*/
}

void Aura::SpellAuraModRangedDamageTaken(bool apply)
{
	if(apply)
		m_target->RangedDamageTaken += mod->m_amount;
	else
	{
		m_target->RangedDamageTaken -= mod->m_amount;;
		if( m_target->RangedDamageTaken < 0)
			m_target->RangedDamageTaken = 0;
	}
}

void Aura::SpellAuraModHealing(bool apply)
{
	int32 val;
	if(apply)
	{
		 val = mod->m_amount;
		 /*if(val>0)
			 SetPositive();
		 else
			 SetNegative();*/
	}
	else
		val=-mod->m_amount;

	m_target->HealTakenMod += val;
}

void Aura::SpellAuraIgnoreRegenInterrupt(bool apply)
{
	if(!m_target->IsPlayer())
	{ 
		return;
	}

	if(apply)
		SafePlayerCast( m_target )->PctIgnoreRegenModifier += ((float)(mod->m_amount))/100;
	else
		SafePlayerCast( m_target )->PctIgnoreRegenModifier -= ((float)(mod->m_amount))/100;
}

void Aura::SpellAuraModMechanicResistance(bool apply)
{
	if(apply)
	{
		assert( mod->m_miscValue < MECHANIC_TOTAL );
		m_target->MechanicsResistancesPCT[mod->m_miscValue]+=mod->m_amount;

		if(mod->m_miscValue != MECHANIC_HEALING && mod->m_miscValue != MECHANIC_INVULNERABLE && mod->m_miscValue != MECHANIC_SHIELDED ) // dont remove bandages, Power Word and protection effect
			SetPositive();
		else
			SetNegative();
	}
	else
		m_target->MechanicsResistancesPCT[mod->m_miscValue]-=mod->m_amount;
}

void Aura::SpellAuraModHealingPCT(bool apply)
{
	int32 val;
	if(apply)
	{
		 val = mod->m_amount;
		 if(val<0)
			SetNegative();
		 else
			SetPositive();
	}
	else
		val=-mod->m_amount;

	m_target->HealTakenPctMod += val;
}

void Aura::SpellAuraUntrackable(bool apply)
{
    if(apply)
        m_target->SetFlag(UNIT_FIELD_BYTES_1, STANDSTATE_FLAG_UNTRACKABLE);
    else
        m_target->RemoveFlag(UNIT_FIELD_BYTES_1, STANDSTATE_FLAG_UNTRACKABLE);
}

void Aura::SpellAuraModRangedAttackPower(bool apply)
{
	if(apply)
	{
		if(mod->m_amount > 0)
			SetPositive();
		else
			SetNegative();
		m_target->ModUnsigned32Value(UNIT_FIELD_RANGED_ATTACK_POWER_MODS,mod->m_amount);
	}
	else
		m_target->ModUnsigned32Value(UNIT_FIELD_RANGED_ATTACK_POWER_MODS,-mod->m_amount);

	m_target->CalcDamage();
}

void Aura::SpellAuraModMeleeDamageTaken(bool apply)
{
	if(apply)
	{
		if(mod->m_amount > 0)//does not exist but let it be
			SetNegative();
		else
			SetPositive();
		m_target->DamageTakenMod[0] += mod->m_amount;
	}
	else
		m_target->DamageTakenMod[0] -= mod->m_amount;
}

void Aura::SpellAuraModMeleeDamageTakenPct(bool apply)
{
	if(apply)
	{
		if(mod->m_amount>0)//does not exist but let it be
			SetNegative();
		else
			SetPositive();
		m_target->DamageTakenPctMod[0]+=mod->m_amount/100.0f;
	}
	else
		m_target->DamageTakenPctMod[0]-=mod->m_amount/100.0f;
}

void Aura::SpellAuraRAPAttackerBonus(bool apply)
{
	if(apply)
	{
		m_target->RAPvModifier += mod->m_amount;
	}
	else
		m_target->RAPvModifier -= mod->m_amount;
}

void Aura::SpellAuraModIncreaseSpeedAlways(bool apply)
{
	if(apply)
	{
		SetPositive();
//		m_target->m_speedModifier += mod->m_amount;
		if( (GetSpellProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) )
		{
			int32 speedmod=0;
			SM_FIValue(m_target->SM_FSpeedMod,&speedmod,GetSpellProto()->SpellGroupType);
			mod->m_amount += speedmod;
		}
		m_target->speedIncreaseMap.push_front( mod );
	}
	else
	{
//		m_target->m_speedModifier -= mod->m_amount;
		m_target->speedIncreaseMap.remove( mod );
	}

	if( m_target->GetSpeedIncrease() )
		m_target->UpdateSpeed();
}

void Aura::SpellAuraModIncreaseEnergyPerc( bool apply )
{
	SetPositive();
	uint32 maxField = UNIT_FIELD_MAXPOWER1 + mod->m_miscValue;

	if(apply)
	{
		mod->fixed_amount[ 0 ] = m_target->GetModPUInt32Value( maxField, mod->m_amount );
		m_target->ModUnsigned32Value( maxField, mod->fixed_amount[ 0 ] );
		if( m_target->IsPlayer() && maxField == UNIT_FIELD_MAXPOWER1 )
			SafePlayerCast( m_target )->SetManaFromSpell( ( SafePlayerCast(m_target) )->GetManaFromSpell() + mod->fixed_amount[ 0 ] );
	}
	else
	{
		m_target->ModUnsigned32Value( maxField, -mod->fixed_amount[ 0 ] );
		if( m_target->IsPlayer() && maxField == UNIT_FIELD_MAXPOWER1 )
			SafePlayerCast( m_target )->SetManaFromSpell( (SafePlayerCast(m_target) )->GetManaFromSpell() - mod->fixed_amount[ 0 ] );
	}
}

void Aura::SpellAuraModIgnoreArmorForWeapon( bool apply )
{
	if (m_target->IsPlayer())
	{
		if(apply)
		{
			WeaponModifier *md;
			md = new WeaponModifier;
			// weapon_target_armor_pct_ignore = 1 + value
			// new armor = armor * weapon_target_armor_pct_ignore
			md->value = float(mod->m_amount) / -100.0f;	
			md->wclass = GetSpellProto()->EquippedItemClass;
			md->subclass = GetSpellProto()->EquippedItemSubClass;
			md->spellentry = GetSpellProto();
			p_target->ignore_armor_pct.push_front( md );
		}
		else
		{
			SimplePointerListNode<WeaponModifier> *i;
			for( i=p_target->ignore_armor_pct.begin();i!=p_target->ignore_armor_pct.end();i = i->Next())
				if( i->data->spellentry == GetSpellProto() )
				{
					p_target->ignore_armor_pct.remove( i, 1 );
					break;
				}
		}
		SafePlayerCast( m_target )->UpdateChances();
	}
}

void Aura::SpellAuraModIncreaseMaxHealthPerc( bool apply )
{
	SetPositive();
	if( apply )
	{
		mod->fixed_amount[ 0 ] = m_target->GetModPUInt32Value( UNIT_FIELD_MAXHEALTH, mod->m_amount );
		m_target->ModUnsigned32Value( UNIT_FIELD_MAXHEALTH, mod->fixed_amount[ 0 ] );
		m_target->ModUnsigned32Value( UNIT_FIELD_HEALTH, mod->fixed_amount[ 0 ] );
		if( m_target->IsPlayer() )
			( ( Player* )m_target )->SetHealthFromSpell( ( SafePlayerCast(m_target) )->GetHealthFromSpell() + mod->fixed_amount[ 0 ] );
		else if( m_target->IsPet() )
		{
			SafePetCast( m_target )->SetHealthFromSpell( ( SafePetCast(m_target) )->GetHealthFromSpell() + mod->fixed_amount[ 0 ] );
			SafePetCast( m_target )->CalcStat( STAT_STAMINA );
		}
	}
	else
	{
		m_target->ModUnsigned32Value( UNIT_FIELD_MAXHEALTH, -mod->fixed_amount[ 0 ] );
		if( (int32)m_target->GetUInt32Value( UNIT_FIELD_HEALTH ) > mod->fixed_amount[ 0 ] )
			m_target->ModUnsigned32Value( UNIT_FIELD_HEALTH, -mod->fixed_amount[ 0 ] );
		else if( m_target->isAlive() )
			//according to wowhead health is reseted to 1% min
			m_target->SetUInt32Value( UNIT_FIELD_HEALTH, m_target->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) / 100 );
		//how on earth ?
		if( m_target->GetUInt32Value( UNIT_FIELD_HEALTH ) > m_target->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
			m_target->SetUInt32Value( UNIT_FIELD_HEALTH, m_target->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) );
		if( m_target->IsPlayer() )
			( ( Player* )m_target )->SetHealthFromSpell( (SafePlayerCast(m_target) )->GetHealthFromSpell() - mod->fixed_amount[ 0 ] );
		else if( m_target->IsPet() )
		{
			SafePetCast( m_target )->SetHealthFromSpell( ( SafePetCast(m_target) )->GetHealthFromSpell() - mod->fixed_amount[ 0 ] );
			SafePetCast( m_target )->CalcStat( STAT_STAMINA );
		}
	}
}

void Aura::SpellAuraModManaRegInterrupt( bool apply )
{
	if( m_target->IsPlayer() )
	{
		if( apply )
			SafePlayerCast( m_target )->m_ModInterrMRegenPCT += mod->m_amount;
		else
			SafePlayerCast( m_target )->m_ModInterrMRegenPCT -= mod->m_amount;

		SafePlayerCast( m_target )->UpdateStats();
	}
}

void Aura::SpellAuraModTotalStatPerc(bool apply)
{
	int32 val;
	if(apply)
	{
	   val= mod->m_amount;
	}
	else
	   val= -mod->m_amount;

	if (mod->m_miscValue == -1)//all stats
	{
		if(m_target->IsPlayer())
		{
			for(uint32 x=0;x<5;x++)
			{
				if(mod->m_amount>0)
					SafePlayerCast( m_target )->TotalStatModPctPos[x] += val;
				else
					SafePlayerCast( m_target )->TotalStatModPctNeg[x] -= val;
				SafePlayerCast( m_target )->CalcStat(x);
			}

			SafePlayerCast( m_target )->UpdateStats();
			SafePlayerCast( m_target )->UpdateChances();
		}
		else if(m_target->GetTypeId() == TYPEID_UNIT)
		{
			for(uint32 x=0;x<5;x++)
			{
				SafeCreatureCast(m_target)->TotalStatModPct[x] += val;
				SafeCreatureCast(m_target)->CalcStat(x);
			}
		}
	}
	else
	{
		ASSERT(mod->m_miscValue < 5);
		if(m_target->IsPlayer())
		{
			//druid hearth of the wild should add more features based on form
			if( m_spellProto->NameHash == SPELL_HASH_HEART_OF_THE_WILD )
			{
				//we should remove effect first
				SafePlayerCast( m_target )->EventTalentHearthOfWildChange( false );
				//set new value
				if( apply )
					SafePlayerCast( m_target )->SetTalentHearthOfWildPCT( val );
				else
					SafePlayerCast( m_target )->SetTalentHearthOfWildPCT( 0 ); //this happens on a talent reset
				//reapply
				SafePlayerCast( m_target )->EventTalentHearthOfWildChange( true );
			}

			if( mod->m_amount > 0 )
				SafePlayerCast( m_target )->TotalStatModPctPos[mod->m_miscValue] += val;
			else
				SafePlayerCast( m_target )->TotalStatModPctNeg[mod->m_miscValue] -= val;

			SafePlayerCast( m_target )->CalcStat( mod->m_miscValue );
			SafePlayerCast( m_target )->UpdateStats();
			SafePlayerCast( m_target )->UpdateChances();
		}
		else if( m_target->GetTypeId() == TYPEID_UNIT )
		{
			SafeCreatureCast( m_target )->TotalStatModPct[mod->m_miscValue]+=val;
			SafeCreatureCast( m_target )->CalcStat(mod->m_miscValue);
		}
	}
}

void Aura::SpellAuraModHaste( bool apply )
{
	//blade flurry - attack a nearby opponent
	if( m_spellProto->NameHash == SPELL_HASH_BLADE_FLURRY )
	{
		if( apply )
			m_target->AddExtraStrikeTarget(GetSpellProto(), 0);
		else
			m_target->RemoveExtraStrikeTarget(GetSpellProto());
	}

	if( mod->m_amount < 0 )
		SetNegative();
	else
		SetPositive();

	if( m_target->GetTypeId() == TYPEID_PLAYER )
	{
		if( apply )
		{
			SafePlayerCast( m_target )->ModAttackSpeed( mod->m_amount, MOD_MELEE );
		}
		else
		{
			SafePlayerCast( m_target )->ModAttackSpeed( -mod->m_amount, MOD_MELEE );
		}

		SafePlayerCast(m_target)->UpdateAttackSpeed();
	}
	else
	{
		if( apply )
		{
			mod->fixed_amount[ 0 ] = m_target->GetModPUInt32Value( UNIT_FIELD_BASEATTACKTIME, mod->m_amount );
			mod->fixed_amount[ 1 ] = m_target->GetModPUInt32Value( UNIT_FIELD_BASEATTACKTIME_1, mod->m_amount );

			if( (int32)m_target->GetUInt32Value ( UNIT_FIELD_BASEATTACKTIME ) <= mod->fixed_amount[ 0 ] )
				mod->fixed_amount[ 0 ] = m_target->GetUInt32Value ( UNIT_FIELD_BASEATTACKTIME ); //watch it, a negative timer might be bad ;)
			if( (int32)m_target->GetUInt32Value ( UNIT_FIELD_BASEATTACKTIME_1 ) <= mod->fixed_amount[ 1 ] )
				mod->fixed_amount[ 1 ] = m_target->GetUInt32Value ( UNIT_FIELD_BASEATTACKTIME_1 );//watch it, a negative timer might be bad ;)

			m_target->ModUnsigned32Value( UNIT_FIELD_BASEATTACKTIME, -mod->fixed_amount[ 0 ] );
			m_target->ModUnsigned32Value( UNIT_FIELD_BASEATTACKTIME_1, -mod->fixed_amount[ 1 ] );
			
			if ( m_target->IsCreature() )
				SafeCreatureCast( m_target )->m_speedFromHaste += mod->fixed_amount[ 0 ];
		}
		else
		{
			m_target->ModUnsigned32Value( UNIT_FIELD_BASEATTACKTIME, mod->fixed_amount[ 0 ] );
			m_target->ModUnsigned32Value( UNIT_FIELD_BASEATTACKTIME_1, mod->fixed_amount[ 1 ] );

			if ( m_target->IsCreature() )
				SafeCreatureCast( m_target )->m_speedFromHaste -= mod->fixed_amount[ 0 ];
		}
	}
}

void Aura::SpellAuraForceReaction( bool apply )
{
	map<uint32,uint32>::iterator itr;
	Player * p_target = SafePlayerCast( m_target );
	if( !m_target->IsPlayer() )
	{ 
		return;
	}

	if( apply )
	{
		itr = p_target->m_forcedReactions.find( mod->m_miscValue );
		if( itr != p_target->m_forcedReactions.end() )
			itr->second = mod->m_amount;
		else
			p_target->m_forcedReactions.insert( make_pair( mod->m_miscValue, mod->m_amount ) );
	}
	else
		p_target->m_forcedReactions.erase( mod->m_miscValue );

	WorldPacket data( SMSG_SET_FORCED_REACTIONS, ( 8 * p_target->m_forcedReactions.size() ) + 4 );
	data << uint32(p_target->m_forcedReactions.size());
	for( itr = p_target->m_forcedReactions.begin(); itr != p_target->m_forcedReactions.end(); ++itr )
	{
		data << itr->first;
		data << itr->second;
	}

	p_target->GetSession()->SendPacket( &data );
}

void Aura::SpellAuraModRangedHaste( bool apply )
{
	if( mod->m_amount < 0 )
		SetNegative();
	else
		SetPositive();

	if( m_target->GetTypeId() == TYPEID_PLAYER )
	{
		if( apply )
			SafePlayerCast( m_target )->ModAttackSpeed( mod->m_amount, MOD_RANGED );
		else
			SafePlayerCast( m_target )->ModAttackSpeed( -mod->m_amount, MOD_RANGED );
		
		SafePlayerCast( m_target )->UpdateAttackSpeed();
	}
	else
	{
		if( apply )
		{
			mod->fixed_amount[ 0 ] = m_target->GetModPUInt32Value(UNIT_FIELD_RANGEDATTACKTIME,mod->m_amount);
			m_target->ModUnsigned32Value(UNIT_FIELD_RANGEDATTACKTIME, -mod->fixed_amount[ 0 ]);
		}
		else m_target->ModUnsigned32Value(UNIT_FIELD_RANGEDATTACKTIME, mod->fixed_amount[ 0 ]);
	}
}

void Aura::SpellAuraModRangedAmmoHaste( bool apply )
{
	SetPositive();
	if( !m_target->IsPlayer() )
	{ 
		return;
	}

	if( apply )
		SafePlayerCast( m_target )->ModAttackSpeed( mod->m_amount, MOD_RANGED );
	else
		SafePlayerCast( m_target )->ModAttackSpeed( -mod->m_amount, MOD_RANGED );

	SafePlayerCast( m_target )->UpdateAttackSpeed();
}

void Aura::SpellAuraModResistanceExclusive(bool apply)
{
	SpellAuraModResistance(apply);
}

//!! this works hand in hand with add combo points. One ads them the other one removes them
void Aura::SpellAuraRetainComboPoints(bool apply)
{
	Unit *uc =GetUnitCaster();

	if( apply == false && uc && uc->IsPlayer() )
		SafePlayerCast( uc )->RemoveComboPoints( mod->m_amount );
}

void Aura::SpellAuraResistPushback(bool apply)
{
	//DK:This is resist for spell casting delay
	//Only use on players for now

	if(m_target->IsPlayer())
	{
		int32 val;
		if(apply)
		{
			val = mod->m_amount;
			SetPositive();
		}
		else
			val=-mod->m_amount;

		for(uint32 x=0;x<7;x++)
		{
			if (mod->m_miscValue & (((uint32)1)<<x) )
			{
				SafePlayerCast( m_target )->SpellDelayResist[x] += val;
			}
		}
	}
}

void Aura::SpellAuraModShieldBlockPCT( bool apply )
{
	if( p_target != NULL )
	{
		if( apply )
		{
			p_target->m_modblockabsorbvaluePCT += ( uint32 )mod->m_amount;

		}
		else
		{
			p_target->m_modblockabsorbvaluePCT -= ( uint32 )mod->m_amount;

		}
		p_target->UpdateStats();
	}
}

void Aura::SpellAuraTrackStealthed(bool apply)
{
	Unit * c;
	if((c=GetUnitCaster()) == 0)
	{ 
		return;
	}

	c->trackStealth = apply;
}

void Aura::SpellAuraModDetectedRange(bool apply)
{
	if(!m_target->IsPlayer())
	{ 
		return;
	}
	if(apply)
	{
		SetPositive();
		SafePlayerCast( m_target )->DetectedRange += mod->m_amount;
	}
	else
	{
		SafePlayerCast( m_target )->DetectedRange -= mod->m_amount;
	}
}

void Aura::SpellAuraSplitDamageFlat(bool apply)
{
	if( !m_target || !m_target->IsUnit() )
	{ 
		return;
	}

	if (m_target->m_damageSplitTarget)
	{
		delete m_target->m_damageSplitTarget;
		m_target->m_damageSplitTarget = NULL;
	}

	if(apply)
	{
		DamageSplitTarget *ds = new DamageSplitTarget;
		ds->m_flatDamageSplit = mod->m_miscValue;
		ds->m_spellId = GetSpellProto()->Id;
		ds->m_pctDamageSplit = 0;
		ds->damage_type = mod->m_type;
		ds->creator = (void*)this;
		ds->m_target = GetCaster()->GetGUID();
		m_target->m_damageSplitTarget = ds;
//		printf("registering dmg split %u, amout= %u \n",ds->m_spellId, mod->m_amount, mod->m_miscValue, mod->m_type);
	}
}

void Aura::SpellAuraModStealthLevel(bool apply)
{
	if(apply)
	{
		SetPositive();
		m_target->m_stealthLevel += mod->m_amount;
	}
	else
		m_target->m_stealthLevel -= mod->m_amount;
}

void Aura::SpellAuraModUnderwaterBreathing(bool apply)
{
	if(m_target->GetTypeId() == TYPEID_PLAYER)
	{
		uint32 m_UnderwaterMaxTimeSaved = SafePlayerCast( m_target )->m_UnderwaterMaxTime;
		if( apply )
			SafePlayerCast( m_target )->m_UnderwaterMaxTime *= (1 + mod->m_amount / 100 );
		else
			SafePlayerCast( m_target )->m_UnderwaterMaxTime /= (1 + mod->m_amount / 100 );
                SafePlayerCast( m_target )->m_UnderwaterTime *= SafePlayerCast( m_target )->m_UnderwaterMaxTime / m_UnderwaterMaxTimeSaved;
	}
}

void Aura::SpellAuraSafeFall(bool apply)
{
	SetPositive();

	if( !m_target->IsPlayer() )
	{ 
		return;
	}
	if( apply )
		( SafePlayerCast(m_target) )->m_safeFall += mod->m_amount;
	else
		( SafePlayerCast(m_target) )->m_safeFall -= mod->m_amount;
}

void Aura::SpellAuraCrowdControlImmunity(bool apply)
{
	SetPositive();

uint32 cc_mechanics[] = {
    MECHANIC_CHARMED ,
    MECHANIC_DISORIENTED, // 2
    MECHANIC_DISARMED, // 3
    MECHANIC_DISTRACED, // 4
    MECHANIC_FLEEING, // 5
    MECHANIC_GRIPPED, // 6
    MECHANIC_ROOTED, // 7
    MECHANIC_SILENCED, // 9
    MECHANIC_ASLEEP, // 10
    MECHANIC_ENSNARED, // 11
	MECHANIC_STUNNED, // 12
	MECHANIC_FROZEN, // 13
	MECHANIC_INCAPACIPATED, // 14
	MECHANIC_POLYMORPHED, // 17
	MECHANIC_BANISHED, // 18
	MECHANIC_SHACKLED, // 20
	MECHANIC_INFECTED, // 22
	MECHANIC_TURNED, // 23
	MECHANIC_HORRIFIED, // 24
	MECHANIC_INTERRUPTED, // 26
	MECHANIC_DAZED, // 27
	MECHANIC_SAPPED, // 30
	0
		};
	//seems to be mechanic immunity but with more then 1 value
	if(apply)
	{
		for(int i=0;cc_mechanics[i] !=0;i++)
		{
			m_target->MechanicsDispels[cc_mechanics[i]]++;
			m_target->RemoveAllAurasByMechanic( cc_mechanics[i] , (uint32)(-1) , false );
		}
	}
	else
		for(int i=0;cc_mechanics[i] !=0;i++)
			if( m_target->MechanicsDispels[cc_mechanics[i]] > 0 )
				m_target->MechanicsDispels[cc_mechanics[i]]--;
}

void Aura::SpellAuraModReputationAdjust(bool apply)
{
	/*SetPositive();
	bool updateclient = true;
	if(IsPassive())
		updateclient = false;	 // dont update client on passive

	if(m_target->GetTypeId()==TYPEID_PLAYER)
	{
		if(apply)
			  SafePlayerCast( m_target )->modPercAllReputation(mod->m_amount, updateclient);
		  else
			SafePlayerCast( m_targe t)->modPercAllReputation(-mod->m_amount, updateclient);
	}*/

	// This is _actually_ "Reputation gains increased by x%."
	// not increase all rep by x%.

	if(m_target->GetTypeId() == TYPEID_PLAYER)
	{
		SetPositive();
		if(apply)
			SafePlayerCast( m_target )->pctReputationMod += mod->m_amount;
		else
			SafePlayerCast( m_target )->pctReputationMod -= mod->m_amount;
	}
}

void Aura::SpellAuraNoPVPCredit(bool apply)
{
	if(m_target->GetTypeId() != TYPEID_PLAYER)
	{ 
		return;
	}

	Player* pPlayer = SafePlayerCast( m_target );

	if (apply)
		pPlayer->m_honorless++;
	else
		pPlayer->m_honorless--;
}

void Aura::SpellAuraModHealthRegInCombat(bool apply)
{
	// demon armor etc, they all seem to be 5 sec.
	if(apply)
	{
		sEventMgr.AddEvent(this, &Aura::EventPeriodicHeal1, uint32(mod->m_amount), EVENT_AURA_PERIODIC_HEALINCOMB, 5000, 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

void Aura::EventPeriodicBurn(uint32 amount, uint32 misc)
{
	Unit*m_caster = GetUnitCaster();

	if(!m_caster)
	{ 
		return;
	}

	if(m_target->isAlive() && m_caster->isAlive())
	{
		if(m_target->SchoolImmunityList[GetSpellProto()->School])
		{ 
			return;
		}

		uint32 field = UNIT_FIELD_POWER1 + misc;

		uint32 Amount = (uint32)min( amount, m_target->GetUInt32Value( field ) );
		uint32 newHealth = m_target->GetUInt32Value(field) - Amount ;

		m_target->SendSpellPeriodicAuraLog(m_target, m_target, m_spellProto->Id, m_spellProto->School, newHealth, 0, 0, FLAG_PERIODIC_DAMAGE, 0);
		m_caster->DealDamage(m_target, Amount, 0, 0, GetSpellProto()->Id);
	}
}

void Aura::SpellAuraPowerBurn(bool apply)
{
	//0 mana,1 rage, 3 energy
	if(apply)
	{
		//hasting affects ticks too
		int32 period = GetSpellProto()->EffectAmplitude[mod->i];
		Unit *Unitc = GetUnitCaster();
		if( Unitc )
		{
			SM_FIValue(Unitc->SM_FTime,&period,GetSpellProto()->SpellGroupType);
			period = (uint32)(period * Unitc->GetSpellHasteDots() );
		}
		if( period < 500 )
			period = 500;

		sEventMgr.AddEvent(this, &Aura::EventPeriodicBurn, uint32(mod->m_amount), (uint32)mod->m_miscValue, EVENT_AURA_PERIODIC_BURN, period , 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

void Aura::SpellAuraModCritDmgPhysical(bool apply)
{
	if(m_target->IsPlayer())
	{
		if(apply)
		{
			SafePlayerCast( m_target )->m_modphyscritdmgPCT += (uint32)mod->m_amount;
		}
		else
		{
			SafePlayerCast( m_target )->m_modphyscritdmgPCT -= (uint32)mod->m_amount;
		}
	}
}


void Aura::SpellAuraWaterBreathing( bool apply )
{
   if( m_target->GetTypeId() == TYPEID_PLAYER )
   {
	   if( apply )
	   {
			SetPositive();
			WorldPacket data( 4 );
			data.SetOpcode( SMSG_STOP_MIRROR_TIMER );
			data << uint32( 1 );
			SafePlayerCast( m_target )->GetSession()->SendPacket( &data );
			SafePlayerCast( m_target )->m_UnderwaterState = 0;
	   }

	   SafePlayerCast( m_target )->m_bUnlimitedBreath = apply;
   }
}

void Aura::SpellAuraAPAttackerBonus(bool apply)
{
	if(apply)
	{
		m_target->APvModifier += mod->m_amount;
	}
	else
		m_target->APvModifier -= mod->m_amount;
}


void Aura::SpellAuraModAttackPowerPct(bool apply)
{
	//!!probably there is a flag or something that will signal if randeg or melee attack power !!! (still missing)
//	if(m_target->IsPlayer())
	{
		if(apply)
		{
			m_target->ModFloatValue(UNIT_FIELD_ATTACK_POWER_MULTIPLIER,(float)mod->m_amount/100);
		}
		else
			m_target->ModFloatValue(UNIT_FIELD_ATTACK_POWER_MULTIPLIER,-(float)mod->m_amount/100);
		m_target->CalcDamage();
	}
}

void Aura::SpellAuraModRangedAttackPowerPct(bool apply)
{
    if(m_target->IsPlayer())
	{
		m_target->ModFloatValue(UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER,((apply)?1:-1)*(float)mod->m_amount/100);
        m_target->CalcDamage();
    }
}

void Aura::SpellAuraIncreaseDamageTypePCT(bool apply)
{
	if(m_target->GetTypeId() == TYPEID_PLAYER)
	{
		if(apply)
		{
			for(uint32 x = 0; x < CREATURE_TYPES; x++)
				if (mod->m_miscValue & (((uint32)1)<<x) )
					SafePlayerCast( m_target )->IncreaseDamageByTypePCT[x+1] += ((float)(mod->m_amount))/100;;
			if(mod->m_amount < 0)
				SetNegative();
			else
				SetPositive();
		}
		else
		{
			for(uint32 x = 0; x < CREATURE_TYPES; x++)
			{
				if (mod->m_miscValue & (((uint32)1)<<x) )
					SafePlayerCast( m_target )->IncreaseDamageByTypePCT[x+1] -= ((float)(mod->m_amount))/100.0f;
			}
		}
	}
}

void Aura::SpellAuraIncreaseCricticalTypePCT(bool apply)
{
	if(m_target->GetTypeId() == TYPEID_PLAYER)
	{
		if(apply)
		{
			for(uint32 x = 0; x < CREATURE_TYPES; x++)
				if (mod->m_miscValue & (((uint32)1)<<x) )
					SafePlayerCast( m_target )->IncreaseCricticalByTypePCT[x+1] += ((float)(mod->m_amount))/100.0f;
			if(mod->m_amount < 0)
				SetNegative();
			else
				SetPositive();
		}
		else
		{
			for(uint32 x = 0; x < CREATURE_TYPES; x++)
			{
				if (mod->m_miscValue & (((uint32)1)<<x) )
					SafePlayerCast( m_target )->IncreaseCricticalByTypePCT[x+1] -= ((float)(mod->m_amount))/100.0f;
			}
		}
	}
}

void Aura::SpellAuraIncreasePartySpeed(bool apply)
{
	if(m_target->GetTypeId() == TYPEID_PLAYER && m_target->isAlive() && m_target->GetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID) == 0)
	{
		if(apply)
		{
//			m_target->m_speedModifier += mod->m_amount;
			if( (GetSpellProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) )
			{
				int32 speedmod=0;
				SM_FIValue(m_target->SM_FSpeedMod,&speedmod,GetSpellProto()->SpellGroupType);
				mod->m_amount += speedmod;
			}
			m_target->speedIncreaseMap.push_front( mod );
		}
	}
	if( apply == false )
	{
//		m_target->m_speedModifier -= mod->m_amount;
		m_target->speedIncreaseMap.remove( mod );
	}
	if( m_target->GetSpeedIncrease() )
		m_target->UpdateSpeed();
}

void Aura::SpellAuraIncreaseSpellDamageByAttribute(bool apply)
{
	if(m_target->IsPlayer() == false )
		return;

	int32 val;

	uint32 stat = m_spellProto->EffectMiscValueB[ mod->i ];

	if( stat > 5 )
		stat = 3;

	if(apply)
	{
		val = mod->m_amount;
		if(val<0)
			SetNegative();
		else
			SetPositive();

		mod->fixed_amount[ 0 ] = m_target->GetUInt32Value(UNIT_FIELD_STAT0 + stat) * val / 100;
	}
	else
		val = -mod->fixed_amount[ 0 ];

	for(uint32 x=0;x<7;x++)
		if (mod->m_miscValue & (((uint32)1)<<x) )
		{
			if( apply )
				m_target->ModUnsigned32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS + x, mod->fixed_amount[ 0 ] );
			else
				m_target->ModUnsigned32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS + x, -mod->fixed_amount[ 0 ] );
		}
	SafePlayerCast( m_target )->UpdateChanceFields();
}

void Aura::SpellAuraModSpellDamageByAP(bool apply)
{
	int32 val;

	if(apply)
	{
		Unit *u_caster = GetUnitCaster();
		if( u_caster == NULL )
			return;
		val = mod->m_amount * u_caster->GetAP() / 100;
		if(val<0)
			SetNegative();
		else
			SetPositive();

		mod->fixed_amount[ 0 ] = val; //we wish to have the same amount when we are removing the spell as when we were applying !
	}
	else
		val = -mod->fixed_amount[ 0 ];

	if(m_target->IsPlayer())
	{
		for(uint32 x=0;x<7;x++)
			if (mod->m_miscValue & (((uint32)1)<<x) )
				m_target->ModUnsigned32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS + x, val );
		SafePlayerCast( m_target )->UpdateChanceFields();
	}
}

void Aura::SpellAuraIncreaseHealingByAttribute(bool apply)
{
	int32 val;

	uint32 stat = m_spellProto->EffectMiscValue[ mod->i ];
	if( stat > 5 )
		stat = 3;

	if( stat >=5 )
	{
		sLog.outError("Aura::SpellAuraIncreaseHealingByAttribute::Unknown spell attribute type %u in spell %u.\n",mod->m_miscValue,GetSpellId());
		return;
	}

	if(apply)
	{
		//we wish to have the same amount when we are removing the spell as when we were applying !
		val = mod->m_amount;
		if(val<0)
			SetNegative();
		else
			SetPositive();
	}
	else
		val = -mod->m_amount;

	if(m_target->IsPlayer())
	{
		SafePlayerCast( m_target )->SpellHealDoneByAttribute[stat] += ((float)(val))/100.0f;
		
		//this will never reflect instant changes
		if( apply )
		{
			mod->fixed_amount[ mod->i ] = val * m_target->GetUInt32Value(UNIT_FIELD_STAT0 + stat) / 100 ;
			m_target->ModUnsigned32Value(PLAYER_FIELD_MOD_HEALING_DONE_POS, mod->fixed_amount[ mod->i ]);
		}
		else
			m_target->ModUnsigned32Value(PLAYER_FIELD_MOD_HEALING_DONE_POS, -mod->fixed_amount[ mod->i ]);

		SafePlayerCast( m_target )->UpdateChanceFields();
	}
}

void Aura::SpellAuraModHealingByAP(bool apply)
{
	int32 val;

	if(apply)
	{
		Unit *u_caster = GetUnitCaster();
		if( u_caster == NULL )
			return;
		val = mod->m_amount * u_caster->GetAP() / 100;
		if(val<0)
			SetNegative();
		else
			SetPositive();

		mod->fixed_amount[0] = val; //we wish to have the same amount when we are removing the spell as when we were applying !
	}
	else
		val = -mod->fixed_amount[0];

	if(m_target->IsPlayer())
	{
		m_target->HealDoneMod += val;
		m_target->ModUnsigned32Value(PLAYER_FIELD_MOD_HEALING_DONE_POS, val);
		SafePlayerCast( m_target )->UpdateChanceFields();
	}
}

void Aura::SpellAuraAddFlatModifier(bool apply)
{
	int32 val = apply?mod->m_amount:-mod->m_amount;
	uint32 *AffectedGroups = GetSpellProto()->EffectSpellGroupRelation[mod->i];

//	sLog.outDebug("%s: AffectedGroups %I64x smt type %u\n", __FUNCTION__, AffectedGroups, mod->m_miscValue);
	switch (mod->m_miscValue)//let's generate warnings for unknown types of modifiers
	{
	case SMT_CRITICAL:
		SendModifierLog(&m_target->SM_CriticalChance,val,AffectedGroups,mod->m_miscValue);
		break;

	case SMT_DURATION:
		SendModifierLog(&m_target->SM_FDur,val,AffectedGroups,mod->m_miscValue);
		break;

	case SMT_RADIUS:
		SendModifierLog(&m_target->SM_FRadius,val,AffectedGroups,mod->m_miscValue);
		break;

	case SMT_RANGE:
		SendModifierLog(&m_target->SM_FRange,val,AffectedGroups,mod->m_miscValue);
		break;

	case SMT_CAST_TIME:
		SendModifierLog(&m_target->SM_FCastTime,val,AffectedGroups,mod->m_miscValue);
		break;

	case SMT_COST:
		SendModifierLog(&m_target->SM_FCost,val,AffectedGroups,mod->m_miscValue);
		break;

	case SMT_SPELL_VALUE_DOT:
		SendModifierLog(&m_target->SM_FDOT,val,AffectedGroups,mod->m_miscValue);
		break;

	case SMT_ADDITIONAL_TARGET:
		SendModifierLog(&m_target->SM_FAdditionalTargets,val,AffectedGroups,mod->m_miscValue);
		break;

	case SMT_DAMAGE_DONE:
		SendModifierLog(&m_target->SM_FDamageBonus,val,AffectedGroups,mod->m_miscValue);
		break;

	case SMT_EFFECT_BONUS:
		SendModifierLog(&m_target->SM_FEffectBonus,val,AffectedGroups,mod->m_miscValue,true);
		break;

	case SMT_EFFECT_TARGET:
		SendModifierLog(&m_target->SM_FEffectTargetBonus,val,AffectedGroups,mod->m_miscValue,true);
		break;

	case SMT_MISC_EFFECT:
		SendModifierLog(&m_target->SM_FMiscEffect,val,AffectedGroups,mod->m_miscValue);
		break;

	case SMT_HITCHANCE:
		SendModifierLog(&m_target->SM_FHitchance,val,AffectedGroups,mod->m_miscValue);
		break;

		// as far as I know its not yet used!!!
	case SMT_PENALTY:
//		SendModifierLog(&m_target->SM_FPenalty,val,AffectedGroups,mod->m_miscValue);
		//all values seem to be pct. Based of 8/8 spells
		SendModifierLog(&m_target->SM_PPenalty,val,AffectedGroups,mod->m_miscValue,true);
		break;

	case SMT_COOLDOWN_DECREASE:
	case SMT_CAST_COOLDOWN:
		SendModifierLog(&m_target->SM_FCooldownTime, val, AffectedGroups,mod->m_miscValue);
		break;

	case SMT_TRIGGER:
		SendModifierLog(&m_target->SM_FChanceOfSuccess,val,AffectedGroups,mod->m_miscValue);
		break;

	case SMT_CHARGES:
		SendModifierLog(&m_target->SM_FCharges, val, AffectedGroups,mod->m_miscValue);
		break;
	case SMT_THREAT_REDUCED:
		SendModifierLog(&m_target->SM_FThreat, val, AffectedGroups,mod->m_miscValue);
		break;
/*	case SMT_TRIGGER:*/
	case SMT_TIME:
		SendModifierLog(&m_target->SM_FTime, val, AffectedGroups, mod->m_miscValue);
		break;
	case SMT_RESIST_DISPEL:
		SendModifierLog(&m_target->SM_FRezist_dispell, val, AffectedGroups,mod->m_miscValue);
		break;
	//!!!!!!!! these are custom
	case SMT_ADD_TO_EFFECT_VALUE_1:
		SendModifierLog(&m_target->SM_FAddEffect1, val, AffectedGroups,SMT_MISC_EFFECT);
		break;
	case SMT_ADD_TO_EFFECT_VALUE_2:
		SendModifierLog(&m_target->SM_FAddEffect2, val, AffectedGroups,SMT_MISC_EFFECT);
		break;
	case SMT_ADD_TO_EFFECT_VALUE_3:
		SendModifierLog(&m_target->SM_FAddEffect3, val, AffectedGroups,SMT_MISC_EFFECT);
		break;
	default://unknown Modifier type
		sLog.outError("Unknown spell modifier type %u in spell %u.<<--report this line to the developer\n",	mod->m_miscValue,GetSpellId());
		//don't add val, though we could formaly could do,but as we don't know what it is-> no sense
		break;
	}
	//Hunter's BeastMastery talents.
/*	if( m_target->IsPlayer() )
	{
		Pet * p = SafePlayerCast(m_target)->GetSummon();
		if( p )
		{
			switch( GetSpellProto()->NameHash )
			{
			case SPELL_HASH_UNLEASHED_FURY:
				p->LoadPetAuras(0);
				break;
			case SPELL_HASH_THICK_HIDE:
				p->LoadPetAuras(1);
				break;
			case SPELL_HASH_ENDURANCE_TRAINING:
				p->LoadPetAuras(2);
				break;
//			case SPELL_HASH_BESTIAL_SWIFTNESS:
//				p->LoadPetAuras(3);
//				break;
			case SPELL_HASH_BESTIAL_DISCIPLINE:
				p->LoadPetAuras(4);
				break;
			case SPELL_HASH_FEROCITY:
				p->LoadPetAuras(5);
				break;
			case SPELL_HASH_ANIMAL_HANDLER:
				p->LoadPetAuras(6);
				break;
			case SPELL_HASH_CATLIKE_REFLEXES:
				p->LoadPetAuras(7);
				break;
			case SPELL_HASH_SERPENT_S_SWIFTNESS:
				p->LoadPetAuras(8);
				break;
			}
		}
	}*/
}


void Aura::SpellAuraModHealingDone(bool apply)
{
	int32 val;

	if( m_target->getClass() == DEATHKNIGHT )
	{ 
		return;
	}

	if(apply)
	{
		val=mod->m_amount;
		if(val<0)
			SetNegative();
		else
			SetPositive();
	}
	else
		val = -mod->m_amount;

//	for(uint32 x=0;x<7;x++)
//		if (mod->m_miscValue  & (((uint32)1)<<x) )
//			m_target->HealDoneMod[x] += val;
	m_target->HealDoneMod += val;

	if(m_target->IsPlayer())
	{
		SafePlayerCast( m_target )->UpdateChanceFields();
		m_target->SetUInt32Value(PLAYER_FIELD_MOD_HEALING_DONE_POS, m_target->GetUInt32Value(PLAYER_FIELD_MOD_HEALING_DONE_POS) + val);
	}
}

void Aura::SpellAuraModHealingDonePct(bool apply)
{
	int32 val;
	if(apply)
	{
		val=mod->m_amount;
		if(val<0)
			SetNegative();
		else
			SetPositive();
	}
	else
		val=-mod->m_amount;

/*	for(uint32 x=0;x<7;x++)
	{
		if (mod->m_miscValue  & (((uint32)1)<<x) )
		{
			m_target->HealDonePctMod[x] += val;
		}
	}*/
	m_target->HealDonePctMod += val;
	if( p_target )
	{
		//i wonder which one of these 2 needs to be modded
		p_target->SetUInt32Value( PLAYER_FIELD_MOD_HEALING_PCT, m_target->HealDonePctMod );
		p_target->SetUInt32Value( PLAYER_FIELD_MOD_HEALING_DONE_PCT, m_target->HealDonePctMod );
	}
}

void Aura::SpellAuraEmphaty(bool apply)
{
	SetPositive();
	Unit * caster = GetUnitCaster();
	if(caster == 0 || !m_target || caster->GetTypeId() != TYPEID_PLAYER)
	{ 
		return;
	}

	// Show extra info about beast
	uint32 dynflags = m_target->GetUInt32Value(UNIT_DYNAMIC_FLAGS);
	if(apply)
		dynflags |= U_DYN_FLAG_PLAYER_INFO;

	m_target->BuildFieldUpdatePacket(SafePlayerCast(caster), UNIT_DYNAMIC_FLAGS, dynflags);
}

void Aura::SpellAuraModOffhandDamagePCT(bool apply)
{
	//Used only by talents of rogue and warrior;passive,positive
	if(m_target->GetTypeId() == TYPEID_PLAYER)
	{
		if(apply)
		{
			SetPositive();
			SafePlayerCast( m_target )->offhand_dmg_mod *= (100+mod->m_amount)/100.0f;
		}
		else
			SafePlayerCast( m_target )->offhand_dmg_mod /= (100+mod->m_amount)/100.0f;

		m_target->CalcDamage();
	}
}

void Aura::SpellAuraModPenetration(bool apply) // armor penetration & spell penetration
{
	if( m_spellProto->NameHash == SPELL_HASH_SERRATED_BLADES )
	{
		if(!m_target->IsPlayer())
		{ 
			return;
		}

		Player *plr = SafePlayerCast(m_target);
		if( apply )
		{
			mod->fixed_amount[ 0 ] = 0;
			if( m_spellProto->Id == 14171 )
				mod->fixed_amount[ 0 ] = m_target->getLevel() * 267;
			else if( m_spellProto->Id == 14172 )
				mod->fixed_amount[ 0 ] =  m_target->getLevel() * 543;
			else if( m_spellProto->Id == 14173 )
				mod->fixed_amount[ 0 ] =  m_target->getLevel() * 800;
			plr->TargetResistRedModFlat[0] += mod->fixed_amount[ 0 ] / 100.0f;
		}
		else
		{
			plr->TargetResistRedModFlat[0] -= mod->fixed_amount[ 0 ] / 100.0f;
		}
		return;
	}
	if(apply)
	{
		if(mod->m_amount < 0)
			SetPositive();
		else
			SetNegative();

		for(uint32 x=0;x<7;x++)
		{
			if (mod->m_miscValue & (((uint32)1)<<x))
				m_target->TargetResistRedModFlat[x] -= mod->m_amount;
		}

		if(m_target->IsPlayer()){
			if(mod->m_miscValue & 124)
				m_target->ModSignedInt32Value(PLAYER_FIELD_MOD_TARGET_RESISTANCE, mod->m_amount);
			if(mod->m_miscValue & 1)
				m_target->ModSignedInt32Value(PLAYER_FIELD_MOD_TARGET_PHYSICAL_RESISTANCE, mod->m_amount);
		}
	}
	else
	{
		for(uint32 x=0;x<7;x++)
		{
			if (mod->m_miscValue & (((uint32)1)<<x))
				m_target->TargetResistRedModFlat[x] += mod->m_amount;
		}
		if(m_target->IsPlayer()){
			if(mod->m_miscValue & 124)
				m_target->ModSignedInt32Value(PLAYER_FIELD_MOD_TARGET_RESISTANCE, -mod->m_amount);
			if(mod->m_miscValue & 1)
				m_target->ModSignedInt32Value(PLAYER_FIELD_MOD_TARGET_PHYSICAL_RESISTANCE, -mod->m_amount);
		}
	}
}

void Aura::SpellAuraIncreaseArmorByPctInt(bool apply)
{
	uint32 i_Int = m_target->GetUInt32Value(UNIT_FIELD_STAT3);

	int32 amt = float2int32(i_Int * ((float)mod->m_amount / 100.0f));
	amt *= (!apply) ? -1 : 1;

	for(uint32 x=0;x<7;x++)
	{
		if(mod->m_miscValue & (((uint32)1)<< x))
		{
			if(m_target->GetTypeId() == TYPEID_PLAYER)
			{
				SafePlayerCast( m_target )->FlatResistanceModifierPos[x] += amt;
				SafePlayerCast( m_target )->CalcResistance(x);
			}
			else if(m_target->GetTypeId() == TYPEID_UNIT)
			{
				SafeCreatureCast(m_target)->FlatResistanceMod[x] += amt;
				SafeCreatureCast(m_target)->CalcResistance(x);
			}
		}
	}
}

void Aura::SpellAuraReduceAttackerMHitChance(bool apply)
{
	if (!m_target->IsPlayer())
	{ 
		return;
	}
	if(apply)
		SafePlayerCast( m_target )->m_resist_hit[ MOD_MELEE ] += mod->m_amount;
	else
		SafePlayerCast( m_target )->m_resist_hit[ MOD_MELEE ] -= mod->m_amount;
}

void Aura::SpellAuraReduceAttackerRHitChance(bool apply)
{
	if (!m_target->IsPlayer())
	{ 
		return;
	}
	if(apply)
		SafePlayerCast( m_target )->m_resist_hit[ MOD_RANGED ] += mod->m_amount;
	else
		SafePlayerCast( m_target )->m_resist_hit[ MOD_RANGED ] -= mod->m_amount;
}

void Aura::SpellAuraReduceAttackerSHitChance(bool apply)
{
	if (!m_target->IsPlayer())
	{ 
		return;
	}
	if(apply)
		SafePlayerCast( m_target )->m_resist_hit[ MOD_SPELL ] -= mod->m_amount;
	else
		SafePlayerCast( m_target )->m_resist_hit[ MOD_SPELL ] += mod->m_amount;
}

void Aura::SpellAuraReduceEnemyMCritChance(bool apply)
{
	if(!m_target->IsPlayer())
	{ 
		return;
	}
	if(apply)
	{
		//value is negative percent
		SafePlayerCast( m_target )->res_M_crit_set(SafePlayerCast( m_target )->res_M_crit_get()+mod->m_amount);
	}
	else
	{
		SafePlayerCast( m_target )->res_M_crit_set(SafePlayerCast( m_target )->res_M_crit_get()-mod->m_amount);
	}
}

void Aura::SpellAuraReduceEnemyRCritChance(bool apply)
{
	if(!m_target->IsPlayer())
	{ 
		return;
	}
	if(apply)
	{
		//value is negative percent
		SafePlayerCast( m_target )->res_R_crit_set(SafePlayerCast( m_target )->res_R_crit_get()+mod->m_amount);
	}
	else
	{
		SafePlayerCast( m_target )->res_R_crit_set(SafePlayerCast( m_target )->res_R_crit_get()-mod->m_amount);
	}
}

void Aura::SpellAuraLimitSpeed( bool apply )
{
	int32 amount = ( apply ) ? mod->m_amount : -mod->m_amount;
	m_target->m_maxSpeed += (float)amount;
	m_target->UpdateSpeed();
}

void Aura::SpellAuraIncreaseTimeBetweenAttacksPCT(bool apply)
{
	int32 val =  (apply) ? mod->m_amount : -mod->m_amount;
	float pct_value = -val/100.0f; //value is negative representing a decrease : 1 + x%
	m_target->ModFloatValue(UNIT_MOD_CAST_SPEED,pct_value);
}

void Aura::SpellAuraMeleeHaste( bool apply )
{
	if( mod->m_amount < 0 )
		SetNegative();
	else 
		SetPositive();
	
	if( m_target->IsPlayer() )
	{
		if( apply )
			SafePlayerCast( m_target )->ModAttackSpeed( mod->m_amount, MOD_MELEE );
		else
			SafePlayerCast( m_target )->ModAttackSpeed( -mod->m_amount, MOD_MELEE );

		SafePlayerCast(m_target)->UpdateAttackSpeed();
	}
	else
	{
		if( apply )
		{
			mod->fixed_amount[0] = m_target->GetModPUInt32Value( UNIT_FIELD_BASEATTACKTIME, mod->m_amount );
			mod->fixed_amount[1] = m_target->GetModPUInt32Value( UNIT_FIELD_BASEATTACKTIME_1, mod->m_amount );

			if( (int32)m_target->GetUInt32Value ( UNIT_FIELD_BASEATTACKTIME ) <= mod->fixed_amount[0] )
				mod->fixed_amount[0] = m_target->GetUInt32Value ( UNIT_FIELD_BASEATTACKTIME );
			if( (int32)m_target->GetUInt32Value ( UNIT_FIELD_BASEATTACKTIME_1 ) <= mod->fixed_amount[1] )
				mod->fixed_amount[1] = m_target->GetUInt32Value ( UNIT_FIELD_BASEATTACKTIME_1 );

			m_target->ModUnsigned32Value( UNIT_FIELD_BASEATTACKTIME, -mod->fixed_amount[0] );
			m_target->ModUnsigned32Value( UNIT_FIELD_BASEATTACKTIME_1, -mod->fixed_amount[1] );
		}
		else
		{
			m_target->ModUnsigned32Value( UNIT_FIELD_BASEATTACKTIME, mod->fixed_amount[0] );
			m_target->ModUnsigned32Value( UNIT_FIELD_BASEATTACKTIME_1, mod->fixed_amount[1] );
		}
	}
}

/*
void Aura::SpellAuraIncreaseSpellDamageByInt(bool apply)
{
	 float val;
	 if(apply)
	 {
		 val = mod->m_amount/100.0f;
		 if(mod->m_amount>0)
			 SetPositive();
		 else
			 SetNegative();
	 }
	 else
		val =- mod->m_amount/100.0f;

	if(m_target->IsPlayer())
	{
		for(uint32 x=1;x<7;x++)
		{
			if (mod->m_miscValue & (((uint32)1)<<x) )
			{
				SafePlayerCast( m_target )->SpellDmgDoneByInt[x]+=val;
			}
		}
	}
}

void Aura::SpellAuraIncreaseHealingByInt(bool apply)
{
	 float val;
	 if(apply)
	 {
		 val = mod->m_amount/100.0f;
		 if(val>0)
			 SetPositive();
		 else
			 SetNegative();
	 }
	 else
		val =- mod->m_amount/100.0f;

	if(m_target->IsPlayer())
	{
		for(uint32 x=1;x<7;x++)
		{
   //		 if (mod->m_miscValue & (((uint32)1)<<x) )
			{
				SafePlayerCast( m_target )->SpellHealDoneByInt[x]+=val;
			}
		}
	}
}
*/
void Aura::SpellAuraModAttackerCritChance(bool apply)
{
	int32 val  = (apply) ? mod->m_amount : -mod->m_amount;
	m_target->AttackerCritChanceMod[0] +=val;
}

void Aura::SpellAuraIncreaseAllWeaponSkill(bool apply)
{
	if (m_target->GetTypeId() == TYPEID_PLAYER)
	{
		if(apply)
		{
			SetPositive();
//			SafePlayerCast( m_target )->ModSkillBonusType(SKILL_TYPE_WEAPON, mod->m_amount);
			//since the frikkin above line does not work we have to do it manually
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_SWORDS, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_AXES, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_BOWS, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_GUNS, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_MACES, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_2H_SWORDS, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_STAVES, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_2H_MACES, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_2H_AXES, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_DAGGERS, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_CROSSBOWS, mod->m_amount);
//			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_SPEARS, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_WANDS, mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_POLEARMS, mod->m_amount);
		}
		else
		{
//			SafePlayerCast( m_target )->ModSkillBonusType(SKILL_TYPE_WEAPON, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_SWORDS, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_AXES, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_BOWS, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_GUNS, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_MACES, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_2H_SWORDS, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_STAVES, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_2H_MACES, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_2H_AXES, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_DAGGERS, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_CROSSBOWS, -mod->m_amount);
//			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_SPEARS, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_WANDS, -mod->m_amount);
			SafePlayerCast( m_target )->_ModifySkillBonus(SKILL_POLEARMS, -mod->m_amount);
		}

		SafePlayerCast( m_target )->UpdateStats();
	}
}

void Aura::SpellAuraIncreaseHitRate( bool apply )
{
	if( !m_target->IsPlayer() )
	{ 
		return;
	}
	
	SafePlayerCast( m_target )->ModifyBonuses( SPELL_HIT_RATING, mod->m_amount, apply );
	SafePlayerCast( m_target )->UpdateStats();
}

void Aura::SpellAuraIncreaseRageFromDamageDealtPCT(bool apply)
{
	if(!m_target->IsPlayer())
	{ 
		return;
	}

	SafePlayerCast( m_target )->rageFromDamageDealt += (apply) ? mod->m_amount : -mod->m_amount;
}

int32 Aura::event_GetInstanceID()
{
	return m_target->event_GetInstanceID();
}

void Aura::SpellAuraReduceCritMeleeAttackDmg(bool apply)
{
	if(!m_target)
	{ 
		return;
	}

	signed int val;
	if(apply)
		val = mod->m_amount;
	else
		val = -mod->m_amount;

	for(uint32 x=1;x<7;x++)
		if (mod->m_miscValue & (((uint32)1)<<x) )
			m_target->CritMeleeDamageTakenPctMod[x] += val/100.0f;
}

void Aura::SpellAuraReduceCritRangedAttackDmg(bool apply)
{
	if(!m_target)
	{ 
		return;
	}

	signed int val;
	if(apply)
		val = mod->m_amount;
	else
		val = -mod->m_amount;

	for(uint32 x=1;x<7;x++)
		if (mod->m_miscValue & (((uint32)1)<<x) )
			m_target->CritRangedDamageTakenPctMod[x] += val/100.0f;
}

void Aura::SpellAuraEnableFlight(bool apply)
{
	if(apply)
	{
		m_target->EnableFlight();
		m_target->m_flyspeedModifier += mod->m_amount;
		m_target->UpdateSpeed();
		if(m_target->IsPlayer())
		{
			SafePlayerCast( m_target )->flying_aura = m_spellProto->Id;
		}
	}
	else
	{
		m_target->DisableFlight();
		m_target->m_flyspeedModifier -= mod->m_amount;
		m_target->UpdateSpeed();
		if(m_target->IsPlayer())
		{
			SafePlayerCast( m_target )->flying_aura = 0;
		}
	}
}

void Aura::SpellAuraEnableFlightWithUnmountedSpeed(bool apply)
{
	// Used in flight form (only so far)
	if(apply)
	{
		m_target->EnableFlight();
		m_target->m_flyspeedModifier += mod->m_amount;
		m_target->UpdateSpeed();
		if(m_target->IsPlayer())
		{
			SafePlayerCast( m_target )->flying_aura = m_spellProto->Id;
		}
	}
	else
	{
		m_target->DisableFlight();
		m_target->m_flyspeedModifier -= mod->m_amount;
		m_target->UpdateSpeed();
		if(m_target->IsPlayer())
		{
			SafePlayerCast( m_target )->flying_aura = 0;
		}
	}
}

void Aura::SpellAuraIncreaseMovementAndMountedSpeed( bool apply )
{
	if( apply )
		m_target->m_mountedspeedModifier += mod->m_amount;
	else
		m_target->m_mountedspeedModifier -= mod->m_amount;
	m_target->UpdateSpeed();
}

void Aura::SpellAuraIncreaseFlightSpeed( bool apply )
{
	if( apply )
		m_target->m_flyspeedModifier += mod->m_amount;
	else
		m_target->m_flyspeedModifier -= mod->m_amount;
	m_target->UpdateSpeed();
}


void Aura::SpellAuraIncreaseRating( bool apply )
{
	int v = apply ? mod->m_amount : -mod->m_amount;

	if( !m_target->IsPlayer() )
	{ 
		return;
	}

	// WEAPON_SKILL_RATING = 11 => EXPERTISE_RATING_2 = 37
	static const uint32 translate_to_item[25] = 
	{
		WEAPON_SKILL_RATING,
		DEFENSE_RATING,
		DODGE_RATING,
		PARRY_RATING,
		SHIELD_BLOCK_RATING,
		MELEE_HIT_RATING,
		RANGED_HIT_RATING,
		SPELL_HIT_RATING,
		MELEE_CRITICAL_STRIKE_RATING,
		RANGED_CRITICAL_STRIKE_RATING,
		SPELL_CRITICAL_STRIKE_RATING,
		RESILIENCE_RATING,	//MELEE_HIT_AVOIDANCE_RATING,
		RESILIENCE_RATING,	//RANGED_HIT_AVOIDANCE_RATING,
		RESILIENCE_RATING,	//SPELL_HIT_AVOIDANCE_RATING,
		MELEE_CRITICAL_AVOIDANCE_RATING,
		RANGED_CRITICAL_AVOIDANCE_RATING,
		SPELL_CRITICAL_AVOIDANCE_RATING,
		MELEE_HASTE_RATING,
		RANGED_HASTE_RATING,
		SPELL_HASTE_RATING,
		0,		//PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL
		0,		//PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL
		HIT_AVOIDANCE_RATING,
		EXPERTISE_RATING,
		ARMOR_PENETRATION_RATING
	};
	uint32 mask = mod->m_miscValue;
	Player* plr = SafePlayerCast( m_target );
	//MELEE_CRITICAL_AVOIDANCE_RATING + RANGED_CRITICAL_AVOIDANCE_RATING + SPELL_CRITICAL_AVOIDANCE_RATING
	//comes only as combination of them  - ModifyBonuses() not adding them individually anyhow
/*	if( ( mod->m_miscValue & (0x0004000|0x0008000|0x0010000) ) == (0x0004000|0x0008000|0x0010000) )
	{
			plr->ModifyBonuses( RESILIENCE_RATING, mod->m_amount, apply );
			mask &= ~(0x0004000|0x0008000|0x0010000);
	}*/

	//weapon skill is 0 and it is special
	for( uint32 x = 1; x <= 24; x++ )//skip x=0
		if( ( ( ( uint32 )1 ) << x ) & mask )
			plr->ModifyBonuses( translate_to_item[ x ], mod->m_amount, apply );


	if( mod->m_miscValue & 1 )//weapon skill
	{
		std::map<uint32, uint32>::iterator i;
		for( uint32 y = 0; y < 20; y++ )
			if( m_spellProto->EquippedItemSubClass & ( ( ( uint32 )1 ) << y ) )
			{
					i = SafePlayerCast( m_target )->m_wratings.find( y );
					if( i == SafePlayerCast( m_target )->m_wratings.end() )//no prev
					{
						SafePlayerCast( m_target )->m_wratings[y] = v;
					}else
					{
						i->second += v;
						if( i->second == 0 )
							SafePlayerCast( m_target )->m_wratings.erase( i );
					}
			}
	}

	plr->UpdateStats();
}

void Aura::EventPeriodicRegenManaStatPct(uint32 perc,uint32 stat)
{
	if(m_target->IsDead())
	{ 
		return;
	}

	//blizz says no
//	m_target->Energize( m_target, GetSpellId(), (m_target->GetUInt32Value(UNIT_FIELD_STAT0 + stat)*perc)/100, POWER_TYPE_MANA );

	uint32 mana = m_target->GetUInt32Value(UNIT_FIELD_POWER1) + (m_target->GetUInt32Value(UNIT_FIELD_STAT0 + stat)*perc)/100;
	if(mana <= m_target->GetUInt32Value(UNIT_FIELD_MAXPOWER1))
		m_target->SetUInt32Value(UNIT_FIELD_POWER1, mana);
	else
		m_target->SetUInt32Value(UNIT_FIELD_POWER1, m_target->GetUInt32Value(UNIT_FIELD_MAXPOWER1));
}


void Aura::SpellAuraRegenManaStatPCT(bool apply)
{
	if(apply)
	{
		SetPositive();
		sEventMgr.AddEvent(this, &Aura::EventPeriodicRegenManaStatPct,(uint32)mod->m_amount,(uint32)mod->m_miscValue,  EVENT_AURA_REGEN_MANA_STAT_PCT, 5000, 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
	else
	{
		//on aura remove all events are also removed.
	}
}
void Aura::SpellAuraRatingBasedOnStat(bool apply)
{
	//value based on stat
	if( apply && GetSpellProto()->EffectMiscValueB[mod->i] < 5 )
		mod->m_amount = m_target->GetUInt32Value( UNIT_FIELD_STAT0 + GetSpellProto()->EffectMiscValueB[mod->i]) * mod->m_amount / 100;

	int v = apply ? mod->m_amount : -mod->m_amount;

	if( !m_target->IsPlayer() )
	{ 
		return;
	}

	// WEAPON_SKILL_RATING = 11 => EXPERTISE_RATING_2 = 37
	Player* plr = SafePlayerCast( m_target );
	for( uint32 x = 1; x <= EXPERTISE_RATING_2 - WEAPON_SKILL_RATING; x++ )//skip x=0
		if( ( ( ( uint32 )1 ) << x ) & mod->m_miscValue )
			plr->ModifyBonuses( WEAPON_SKILL_RATING + x, mod->m_amount, apply );

	//MELEE_CRITICAL_AVOIDANCE_RATING + RANGED_CRITICAL_AVOIDANCE_RATING + SPELL_CRITICAL_AVOIDANCE_RATING
	//comes only as combination of them  - ModifyBonuses() not adding them individually anyhow
	if( mod->m_miscValue & (0x0004000|0x0008000|0x0010000) )
			plr->ModifyBonuses( RESILIENCE_RATING, mod->m_amount, apply );

	if( mod->m_miscValue & 1 )//weapon skill
	{
		std::map<uint32, uint32>::iterator i;
		for( uint32 y = 0; y < 20; y++ )
			if( m_spellProto->EquippedItemSubClass & ( ( ( uint32 )1 ) << y ) )
			{
					i = SafePlayerCast( m_target )->m_wratings.find( y );
					if( i == SafePlayerCast( m_target )->m_wratings.end() )//no prev
					{
						if( apply == true )
							SafePlayerCast( m_target )->m_wratings[y] = v;
					}else
					{
						i->second += v;
						if( i->second == 0 )
							SafePlayerCast( m_target )->m_wratings.erase( i );
					}
			}
	}

	plr->UpdateStats();
}

void Aura::SpellAuraFinishingMovesCannotBeDodged(bool apply)
{
	if(apply)
	{
		if( !m_target->IsPlayer() )
		{ 
			return;
		}

		SafePlayerCast( m_target )->m_finishingmovesdodge = true;
	}
	else
	{
		if( !m_target->IsPlayer() )
		{ 
			return;
		}

		SafePlayerCast( m_target )->m_finishingmovesdodge = false;
	}
}

void Aura::SpellAuraModStealthDetection(bool apply)
{
	if(apply)
	{
		m_target->m_stealthDetectBonus += 9999;
	}
	else
		m_target->m_stealthDetectBonus -= 9999;
}

void Aura::SpellAuraIncreaseMaxHealth(bool apply)
{
	int32 amount;
	if( apply )
		amount = mod->m_amount;
	else
		amount = -mod->m_amount;

	if( m_target->IsPlayer() )
	{
		SafePlayerCast( m_target )->SetHealthFromSpell( SafePlayerCast( m_target )->GetHealthFromSpell() + amount );
		SafePlayerCast( m_target )->UpdateStats();
	}
	else m_target->ModUnsigned32Value( UNIT_FIELD_MAXHEALTH, amount);
}

void Aura::SpellAuraSpiritOfRedemption(bool apply)
{
	if(!m_target->IsPlayer())
	{ 
		return;
	}

	if(apply)
	{
		m_target->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.5);
		m_target->SetUInt32Value(UNIT_FIELD_HEALTH, 1);
		SpellEntry * sorInfo = dbcSpell.LookupEntry(27792);
		if(!sorInfo) 
		{ 
			return;
		}
		Spell * sor = SpellPool.PooledNew();
		sor->Init(m_target, sorInfo, true, NULL);
		SpellCastTargets targets;
		targets.m_unitTarget = m_target->GetGUID();
		sor->prepare(&targets);
	}
	else
	{
		m_target->SetFloatValue(OBJECT_FIELD_SCALE_X, 1);
		m_target->RemoveAura(27792);
		m_target->SetUInt32Value(UNIT_FIELD_HEALTH, 0);
	}
}

void Aura::SpellAuraIncreaseAttackerSpellCrit(bool apply)
{
	int32 val = mod->m_amount;

	if (apply)
	{
		if (mod->m_amount>0)
			SetNegative();
		else
			SetPositive();
	}
	else
		val = -val;

	for(uint32 x=0;x<7;x++)
	{
		if (mod->m_miscValue & (((uint32)1)<<x))
			m_target->AttackerCritChanceMod[x] += val;
	}
}

void Aura::SpellAuraIncreaseRepGainPct(bool apply)
{
	if(p_target)
	{
		SetPositive();
		if(apply)
			p_target->pctReputationMod += mod->m_amount;//re use
		else
			p_target->pctReputationMod -= mod->m_amount;//re use
	}
}

void Aura::SpellAuraIncreaseExpGainPct(bool apply)
{
	if(p_target)
	{
		SetPositive();
		if(apply)
			p_target->XPModBonusPCT += mod->m_amount;//re use
		else
			p_target->XPModBonusPCT -= mod->m_amount;//re use
	}
}

void Aura::SpellAuraIncreaseRangedAPStatPCT(bool apply)
{

	if( mod->m_miscValue > 5 )
	{ 
		return;
	}

	if( apply )
	{
		if( mod->m_amount > 0 )
			SetPositive();
		else
			SetNegative();

		mod->fixed_amount[ 0 ] = m_target->GetUInt32Value( UNIT_FIELD_STAT0 + mod->m_miscValue ) * mod->m_amount / 100;
		m_target->ModUnsigned32Value( UNIT_FIELD_RANGED_ATTACK_POWER_MODS, mod->fixed_amount[ 0 ] );
	}
	else
		m_target->ModUnsigned32Value( UNIT_FIELD_RANGED_ATTACK_POWER_MODS, -mod->fixed_amount[ 0 ] );

	m_target->CalcDamage();
}

/* not used
void Aura::SpellAuraModRangedDamageTakenPCT(bool apply)
{
	if(apply)
		m_target->RangedDamageTakenPct += mod->m_amount;
	else
		m_target->RangedDamageTakenPct -= mod->m_amount;
}*/

void Aura::SpellAuraModBlockValue(bool apply)
{
	if( p_target != NULL)
 	{
		int32 amt;
 		if( apply )
 		{
			amt = mod->m_amount;
			if( amt < 0 )
				SetNegative();
			else
				SetPositive();
 		}
		else
		{
			amt = -mod->m_amount;
		}
		p_target->m_modblockvaluefromspells += amt;
		p_target->UpdateStats();
	}
}

void Aura::SendInterrupted(uint8 result, Object * m_caster)
{
	if( !m_caster->IsInWorld() )
	{ 
		return;
	}

	sStackWolrdPacket( data, SMSG_SPELL_FAILURE, 20 );
	if( m_caster->IsPlayer() )
	{
		data << m_caster->GetNewGUID();
		data << m_spellProto->Id;
		data << uint8( result );
		SafePlayerCast( m_caster )->GetSession()->SendPacket( &data );
	}

	//Zack : is there a reason we need to send others spell fail reason ? Isn't this personal ?
	data.Initialize( SMSG_SPELL_FAILED_OTHER );
	data << m_caster->GetNewGUID();
	data << m_spellProto->Id;
	m_caster->SendMessageToSet( &data, true );
	/**/

	m_interrupted = (int16)result;
}

void Aura::SendChannelUpdate(uint32 time, Object * m_caster)
{
	WorldPacket data(MSG_CHANNEL_UPDATE, 18);
	data << m_caster->GetNewGUID();
	data << time;

	m_caster->SendMessageToSet(&data, true);
}

void Aura::SpellAuraExpertieseModifier(bool apply)
{
	if( !p_target )
	{ 
		return;
	}
	if( apply )
		p_target->ModUnsigned32Value( PLAYER_RATING_MODIFIER_EXPERTISE, mod->m_amount );
	else
		p_target->ModUnsigned32Value( PLAYER_RATING_MODIFIER_EXPERTISE, -mod->m_amount );
	p_target->UpdateStats();
}

void Aura::SpellAuraModPossessPet(bool apply)
{
	Unit *caster = GetUnitCaster();
	Player* pCaster;
	if( caster != NULL && caster->IsPlayer() && caster->IsInWorld() )
		pCaster = SafePlayerCast( caster );
	else
		return;

	if( !m_target->IsPet() || pCaster->GetSummon() != m_target )
	{ 
		return;
	}


	if( apply )
	{
		pCaster->Possess( m_target );
		pCaster->SpeedCheatDelay( GetDuration() );
	}
	else
	{
		pCaster->UnPossess();

	}
}

void Aura::SpellAuraReduceEffectDuration(bool apply){
	if(!m_target->IsPlayer())
	{ 
		return;
	}

	int32 val;
	if(apply)
	{
		SetPositive();
		val = mod->m_amount; // TODO Only maximum effect should be used for Silence or Interrupt effects reduction
	}
	else
		val = -mod->m_amount;

	if(mod->m_miscValue > 0 && mod->m_miscValue < MECHANIC_TOTAL)
		SafePlayerCast( m_target )->MechanicDurationPctMod[mod->m_miscValue] += val;
}

void Aura::HandleAuraControlVehicle(bool apply)
{
	//we are casting this spell as player. Just making sure in future noone is dumb enough to forget that
	Unit *cu = GetUnitCaster();
	if( !cu || !cu->IsPlayer() || !m_target->IsUnit() )
	{ 
		return;
	}

	Player *pcaster = SafePlayerCast( cu );

	if( pcaster->GetSummon() )
		pcaster->GetSummon()->Dismiss();

    WorldPacket data(SMSG_CONTROL_VECHICLE, 0);
    pcaster->GetSession()->SendPacket(&data);

	return;

	if( apply )
	{
		WorldPacket data(SMSG_CLIENT_CONTROL_UPDATE, 9);
		data << m_target->GetNewGUID();
		data << (uint8)1; // we are going to loose control !
		pcaster->GetSession()->SendPacket(&data);

//		pcaster->controlled_vehicle = SafeUnitCast( m_target );
//		pcaster->SetUInt64Value( UNIT_FIELD_CHARM, pcaster->controlled_vehicle->GetGUID() );
//		pcaster->SetUInt64Value( PLAYER_FARSIGHT, pcaster->controlled_vehicle->GetGUID() ); //focus camera on this 

		//add mana to the vehicle. It is supposed to already have mana
		for(int i=0;i<7;i++)
		{
			if( m_target->GetUInt32Value( UNIT_FIELD_MAXPOWER1 + i) < 100 )
				m_target->SetUInt32Value( UNIT_FIELD_MAXPOWER1 + i, 100000 );
			m_target->SetUInt32Value( UNIT_FIELD_POWER1 + i, m_target->GetUInt32Value( UNIT_FIELD_MAXPOWER1 + i ) );
		}

		//root the player
		pcaster->Root();
	
		//show the interface for the vehicle
		WorldPacket data2(SMSG_CONTROL_VECHICLE, 0);
		pcaster->GetSession()->SendPacket(&data2);

		//port ourselfs on it
		pcaster->SetPosition( m_target->GetPosition() );
		float o = m_target->GetOrientation();
		pcaster->SetOrientation( o );
/*		WorldPacket data3(MSG_MOVE_TELEPORT_ACK, 74);
		data3 << pcaster->GetNewGUID();
		data3 << uint32(1); // no idea really
		data3 << uint32(0x200); // enable block for sending the guid and the floats
		data3 << uint16(0);
		data3 << uint32( getMSTime() ); //got a strong feeling this is something else
//		data3 << uint32( 0 ); //got a strong feeling this is something else
		data3 << pcaster->GetPosition();
		data3 << pcaster->GetOrientation();
		data3 << m_target->GetGUID(); //!!!need to change this to have a vehicle GUID 
		data3 << float( 0.213100001216 ); // maybe orientation for vehicle seat ?
		data3 << float( 0 );
		data3 << float( 1.86570000648 ); // maybe orientation for vehicle seat ?
		data3 << float( 0 );
		data3 << float( 1.86570000648 ); // some orientation or not ?
		data3 << uint32( 0 );
		data3 << uint8( 0 );
		pcaster->GetSession()->SendPacket(&data3);/**/

		//the pet spells. These should be fetched from some dbc i guess
		/*{
			if( m_target->IsCreature() )
			{
				Creature *vehicle = SafeCreatureCast( m_target );
				if( vehicle->GetCreatureInfo() )
				{
					CreatureSpellDataEntry * SpellData = dbcCreatureSpellData.LookupEntry( vehicle->GetCreatureInfo()->SpellDataID );
					if( SpellData )
						for( uint32 i = 0; i < 3; ++i )
							if( SpellData->Spells[i] != 0 )
								AddSpell( dbcSpell.LookupEntry( SpellData->Spells[i] ), false ); //add spell to pet
				}

		}*/

		//these are sent after we receive the tel ack

		//set our speed to the speed of the controlled vehicle
		WorldPacket data5(SMSG_FORCE_RUN_SPEED_CHANGE, 0);
		data5 << m_target->GetNewGUID();
		data5 << pcaster->m_PositionUpdateCounter++;
		data5 << uint8( 1 );
		data5 << float( 40 );
		pcaster->GetSession()->SendPacket(&data5);

		WorldPacket data4(SMSG_PET_SPELLS, 62);
		data4 << m_target->GetGUID();
		data4 << uint32(1);
		data4 << uint32(0);
		data4 << uint32(0x101);
		data4 << uint32(0x0800CC28); //cc28 = 52264 = 
		data4 << uint32(0x0900CC2C);
		data4 << uint32(0x0A000000);
		data4 << uint32(0x0B000000);
		data4 << uint32(0x0C000000);
		data4 << uint32(0x0D000000);
		data4 << uint32(0x0E000000);
		data4 << uint32(0x0F000000);
		data4 << uint32(0x10000000);
		data4 << uint32(0x11000000);
		data4 << uint16(0x0);
		pcaster->GetSession()->SendPacket(&data4);
	}
	else
	{
		WorldPacket data(SMSG_CLIENT_CONTROL_UPDATE, 9);
		data << m_target->GetNewGUID();
		data << (uint8)0;
		pcaster->GetSession()->SendPacket(&data);

		pcaster->SetUInt64Value( UNIT_FIELD_CHARM, 0 );
		pcaster->SetUInt64Value( PLAYER_FARSIGHT, 0 );

		//make the sound of the vehicle. I'm sure this should be dinamic from somewhere :P
		WorldPacket data2(SMSG_PET_DISMISS_SOUND, 16);
		data2 << uint32(0x41);
		data2 << m_target->GetPosition();
		pcaster->GetSession()->SendPacket(&data2);

//		pcaster->controlled_vehicle = NULL;

		//unroot the player
		pcaster->Unroot();

		//put him near vehicle. Or not ?

		//need to send him no more pet spells ?
		WorldPacket data3(SMSG_PET_SPELLS, 8);
		data3 << uint32(0);
		data3 << uint32(0);
		pcaster->GetSession()->SendPacket(&data3);
	}
}

void Aura::SpellAuraConvertRune(bool apply)
{
	if( !m_target->IsPlayer() )
	{ 
		return;
	}
	if( m_spellProto->EffectMiscValueB[ mod->i ] > TOTAL_RUNE_TYPES 
		|| m_spellProto->EffectMiscValue[ mod->i ] > TOTAL_RUNE_TYPES
		)
		return;
	Player *ptarget = SafePlayerCast( m_target );
	if (apply)
	{
		SetPositive();
		int selected_slot = -1;
		for(int j=TOTAL_USED_RUNES-1;j>=0;j--)
			if( ptarget->m_rune_types[j] == m_spellProto->EffectMiscValue[ mod->i ] )
			{
				selected_slot = j;
				break;
			}
		mod->fixed_amount[ 0 ] = selected_slot;
		if( selected_slot == -1 )
			return; //cannot convert
		ptarget->m_rune_types[ mod->fixed_amount[ 0 ] ] = m_spellProto->EffectMiscValueB[ mod->i ];
		ptarget->ConvertRuneIcon( mod->fixed_amount[ 0 ], m_spellProto->EffectMiscValueB[ mod->i ] );
	}
	else
	{
		if( mod->fixed_amount[ 0 ] == -1 )
			return; //could not convert
		ptarget->m_rune_types[ mod->fixed_amount[ 0 ] ] = m_spellProto->EffectMiscValue[ mod->i ];
		ptarget->ConvertRuneIcon( mod->fixed_amount[ 0 ] , m_spellProto->EffectMiscValue[ mod->i ] );
	}
}

void Aura::SpellAuraAddHealth(bool apply)
{
	if (apply)
	{
		SetPositive();
		m_target->ModUnsigned32Value(UNIT_FIELD_MAXHEALTH, mod->m_amount);
		m_target->ModUnsigned32Value(UNIT_FIELD_HEALTH, mod->m_amount);
	}
	else
	{
		m_target->ModUnsigned32Value(UNIT_FIELD_MAXHEALTH, -mod->m_amount);
		uint32 maxHealth = m_target->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
		if(m_target->GetUInt32Value(UNIT_FIELD_HEALTH) > maxHealth)
			m_target->SetUInt32Value(UNIT_FIELD_MAXHEALTH, maxHealth);
	}
}

//!!! this is defenetly spell id/name/group based -> need to be remade
void Aura::SpellAuraRemoveReagentCost(bool apply)
{
	if(!m_target->IsPlayer())
	{ 
		return;
	}

	if (apply)
	{
		SafePlayerCast(m_target)->removeReagentCost = true;
	}
	else
	{
		SafePlayerCast(m_target)->removeReagentCost = false;
	}
}

void Aura::SpellAuraIgnoreShapeshift( bool apply )
{
	if(!m_target->IsPlayer())
	{ 
		return;
	}

	if( apply )
	{
		m_visualSlot = 255 - 3;
		SafePlayerCast(m_target)->ignoreShapeShiftChecks = true;
		sEventMgr.AddEvent( this, &Aura::SendIgnoreStateAura, EVENT_SEND_PACKET_TO_PLAYER_AFTER_LOGIN, 5000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
		m_flags |= NEED_STATEIGNORE_RESEND_ON_MAPCHANGE;
		//need to make these to be resent on changing maps
//		if( GetDuration() != (uint32)(-1) )
//			sEventMgr.AddEvent( this, &Aura::SendIgnoreStateAura, GetSpellId(), 3, EVENT_SEND_PACKET_TO_PLAYER_AFTER_LOGIN, 5*60*1000, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
	}
	else
	{
		SafePlayerCast(m_target)->ignoreShapeShiftChecks = false;
	}
}

void Aura::Refresh_SpellAuraIncreaseAPBasedOnArmor(uint32 mod_i)
{
	//!!!! AMG fix this. We are removed while we are handling aura !!! This is mem corruption
	if( !m_target )
		return; //yes this is possible

	//remove previous applied value
	m_target->ModUnsigned32Value(UNIT_FIELD_ATTACK_POWER_MODS,-m_modList[mod_i].fixed_amount[ 0 ]);

	//get new value and reapply it
	uint32 effect_value = GetSpellProto()->EffectBasePoints[1] + 1;
	uint32 armor_bonus_per_effect_value = ( GetSpellProto()->EffectBasePoints[0] + 1 ) * ( GetSpellProto()->EffectBasePoints[1] + 1 );
	m_modList[mod_i].fixed_amount[ 0 ] = m_target->GetUInt32Value( UNIT_FIELD_RESISTANCES ) * effect_value / armor_bonus_per_effect_value;
	m_target->ModUnsigned32Value(UNIT_FIELD_ATTACK_POWER_MODS,m_modList[mod_i].fixed_amount[ 0 ]);
	m_target->CalcDamage();
}

void Aura::SpellAuraIncreaseAPBasedOnArmor( bool apply )
{
	if( !m_target->IsUnit() )
	{ 
		return;
	}

	if(mod->m_amount<0)
		SetNegative();
	else
		SetPositive();

	if( apply )
	{
		mod->fixed_amount[ 0 ] = 0;
		Refresh_SpellAuraIncreaseAPBasedOnArmor(mod->i);
		sEventMgr.AddEvent(this, &Aura::Refresh_SpellAuraIncreaseAPBasedOnArmor, mod->i, 
			EVENT_AURA_PERIODIC_UPDATE, AURA_SpellAuraIncreaseAPBasedOnArmor_REFRESH_INTERVAL ,0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
	else
	{
		m_target->ModUnsigned32Value(UNIT_FIELD_ATTACK_POWER_MODS,-mod->fixed_amount[ 0 ]);
		mod->fixed_amount[ 0 ] = 0;
		m_target->CalcDamage();
	}
}

//not sure - only killing spree and bladestorm used this effect. They need to cast but no other spell
void Aura::SpellAuraModNoCast( bool apply )
{
//	SpellAuraModSilence( apply );
//	SpellAuraPacifySilence( apply );
	if( apply )
	{
		Unit *u_caster = GetUnitCaster();
		if( u_caster ) 
		{
			uint32 dur = GetDuration();
			if( dur )
				u_caster->SchoolCastPrevent[ GetSpellProto()->School ]=dur+500+getMSTime();
			else
				u_caster->SchoolCastPrevent[ GetSpellProto()->School ]=2500+getMSTime(); //crap
		}
	}
}

void Aura::SpellAuraModDMGTakenMechanic( bool apply )
{
	if( apply )
		m_target->ModDamageTakenByMechFlat[ GetSpellProto()->MechanicsType ] += mod->m_amount;
	else
		m_target->ModDamageTakenByMechFlat[ GetSpellProto()->MechanicsType ] -= mod->m_amount;
}

void Aura::SpellAuraModHasteAndCastSpeed( bool apply )
{
	SpellAuraModHaste( apply );
	SpellAuraModCastingSpeed( apply );
}

void Aura::SpellAuraModFaction( bool apply )
{
	if( m_target == NULL || m_target->IsPlayer() == false )
		return;
	Player *p_target = SafePlayerCast(m_target);
	if( apply )
	{
		mod->fixed_amount[ 0 ] = p_target->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE);
		p_target->SetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE, mod->m_miscValue );
		p_target->_setFaction();
	}
	else
	{
		p_target->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, mod->fixed_amount[ 0 ] );
		p_target->_setFaction();
	}
}

void Aura::SpellAuraModXPAndRepGainPCT( bool apply )
{
	if( m_target == NULL || m_target->IsPlayer() == false )
		return;
	Player *p_target = SafePlayerCast(m_target);
	if( apply )
	{
		p_target->XPModBonusPCT += mod->m_amount;
		p_target->pctReputationMod += mod->m_amount;
	}
	else
	{
		p_target->XPModBonusPCT -= mod->m_amount;
		p_target->pctReputationMod -= mod->m_amount;
	}
}

void Aura::SpellAuraModHonorGainPCT( bool apply )
{
	if( m_target == NULL || m_target->IsPlayer() == false )
		return;
	Player *p_target = SafePlayerCast(m_target);
	if( apply )
	{
		p_target->HonorModBonusPCT += mod->m_amount;
	}
	else
	{
		p_target->HonorModBonusPCT -= mod->m_amount;
	}
}

void Aura::SpellAuraModFlyghtSpeedPCT( bool apply )
{
	if( apply )
	{
		SetPositive();
		mod->fixed_amount[ 0 ] = m_target->m_flyspeedModifier * mod->m_amount / 100;
		m_target->m_flyspeedModifier += mod->fixed_amount[ 0 ];
	}
	else
	{
		m_target->m_flyspeedModifier -= mod->fixed_amount[ 0 ];
	}
	m_target->UpdateSpeed();
}


void Aura::SpellAuraModMountedSpeedPCT( bool apply )
{
	if( apply )
	{
		SetPositive();
		mod->fixed_amount[ 0 ] = m_target->m_mountedspeedModifier * mod->m_amount / 100;
		m_target->m_mountedspeedModifier += mod->fixed_amount[ 0 ];
	}
	else
	{
		m_target->m_mountedspeedModifier -= mod->fixed_amount[ 0 ];
	}
	m_target->UpdateSpeed();
}

void Aura::SpellAuraModOffensiveMagicalDurationPCT( bool apply )
{
	if( apply )
	{
		m_target->OffensiveMagicalDurationModPCT += mod->m_amount;	//value is already negative
	}
	else
	{
		m_target->OffensiveMagicalDurationModPCT -= mod->m_amount;
	}
}

void Aura::SpellAuraAuraSchoolImmunity( bool apply )
{
	if(apply)
	{
		//fixme me may be negative
		Unit * c = GetUnitCaster();
		if(c)
		{
			if(isAttackable(c,m_target))
				SetNegative();
			else
				SetPositive();
		}
		else
			SetPositive();

		for(uint32 i = 0; i < 7; i++)
			if(mod->m_miscValue & (1<<i))
			{
				m_target->AuraSchoolImmunityList[i]++;
				m_target->RemoveAurasOfSchool(i, false, true);
			}
	}
	else
	{
		for(int i = 0; i < 7; i++)
			if( ( mod->m_miscValue & (1<<i) ) && m_target->AuraSchoolImmunityList[i]>0 )
				m_target->AuraSchoolImmunityList[i]--;
	}
}

void Aura::SpellAuraCritHealDoneModPct( bool apply )
{
	if( m_target == NULL )
		return;
	if(apply)
	{
		m_target->HealCritDonePctMod += mod->m_amount;
	}
	else
	{
		m_target->HealCritDonePctMod -= mod->m_amount;
	}
}

void Aura::SpellAuraModDeflectChance(bool apply)
{
	if (!m_target->IsPlayer())
	{ 
		return;
	}
	if(apply)
	{
		SafePlayerCast( m_target )->m_resist_hit[ MOD_SPELL ] += mod->m_amount;
		SafePlayerCast( m_target )->m_resist_hit[ MOD_MELEE ] += mod->m_amount;
		SafePlayerCast( m_target )->m_resist_hit[ MOD_RANGED ] += mod->m_amount;
	}
	else
	{
		SafePlayerCast( m_target )->m_resist_hit[ MOD_SPELL ] -= mod->m_amount;
		SafePlayerCast( m_target )->m_resist_hit[ MOD_MELEE ] -= mod->m_amount;
		SafePlayerCast( m_target )->m_resist_hit[ MOD_RANGED ] -= mod->m_amount;
	}
}

void Aura::SpellAuraPhase(bool apply)
{
	if ( m_target )
	{
//		if ( m_target->GetAuraStackCount(SPELL_AURA_PHASE) > 1 )
		if ( m_target->m_phase != 1 )
		{
			if ( m_target->IsPlayer() )
				SafePlayerCast(m_target)->GetSession()->SystemMessage("You can have only one phase aura!");
			Remove();
			return;
		}

		if (apply)
			m_target->Phase( PHASE_SET, m_spellProto->EffectMiscValue[mod->i] );
		else
			m_target->Phase( PHASE_RESET );

		if ( m_target->IsPlayer() )
		{
			sStackWolrdPacket( data, SMSG_SET_PHASE_SHIFT, 8);
			data << uint32(m_target->m_phase);
			SafePlayerCast(m_target)->GetSession()->SendPacket(&data);
		}
	}
}


void Aura::SpellAuraMirrorDMG(bool apply)
{
	if(apply)
	{
		//create a proc on any dmg
		ProcTriggerSpell *pts = new ProcTriggerSpell( GetSpellProto() );
		pts->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
		pts->caster = m_casterGuid;	//we will deal dmg on this guy
		pts->procChance = 100;
		pts->procCharges = 0;
		pts->created_with_value = mod->m_amount;
		pts->spellId = 71948;		//we will use this for all spells since we need to force deal dmg to friendly
		m_target->m_procSpells.push_front(pts);
	}
	else
	{
		CommitPointerListNode<ProcTriggerSpell> *itr;
		for(itr = m_target->m_procSpells.begin();itr != m_target->m_procSpells.end();itr = itr->Next() )
			if(itr->data->origId == GetSpellId() && itr->data->caster == m_casterGuid && !itr->data->deleted)
			{
				itr->data->deleted = true;
				break; //only 1 instance of a proc spell per caster ? //zack : not true
			}
	}
}

void Aura::SpellAuraOpenStableUI(bool apply)
{
	if( apply )
	{
		Unit *uc = GetUnitCaster();
		if( uc == NULL || uc->IsPlayer() == false )
			return;
		Player *pc = SafePlayerCast( uc );
		if( pc->GetSession() == NULL || pc->IsInWorld() == false )
			return;
		pc->GetSession()->SendStabledPetList( pc->GetGUID() );
	}
}
