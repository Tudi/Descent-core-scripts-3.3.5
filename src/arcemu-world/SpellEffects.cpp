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

pSpellEffect SpellEffectsHandler[TOTAL_SPELL_EFFECTS]={
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_NULL - 0
		&Spell::SpellEffectInstantKill,				//SPELL_EFFECT_INSTAKILL - 1
		&Spell::SpellEffectSchoolDMG,				//SPELL_EFFECT_SCHOOL_DAMAGE - 2
		&Spell::SpellEffectDummy,					//SPELL_EFFECT_DUMMY - 3
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_PORTAL_TELEPORT - 4
		&Spell::SpellEffectTeleportUnits,			//SPELL_EFFECT_TELEPORT_UNITS - 5
		&Spell::SpellEffectApplyAura,				//SPELL_EFFECT_APPLY_AURA - 6
		&Spell::SpellEffectEnvironmentalDamage,		//SPELL_EFFECT_ENVIRONMENTAL_DAMAGE - 7
		&Spell::SpellEffectPowerDrain,				//SPELL_EFFECT_POWER_DRAIN - 8
		&Spell::SpellEffectHealthLeech,				//SPELL_EFFECT_HEALTH_LEECH - 9
		&Spell::SpellEffectHeal,					//SPELL_EFFECT_HEAL - 10
		&Spell::SpellEffectBind,					//SPELL_EFFECT_BIND - 11
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_PORTAL - 12
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_RITUAL_BASE - 13
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_RITUAL_SPECIALIZE - 14
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL - 15
		&Spell::SpellEffectQuestComplete,			//SPELL_EFFECT_QUEST_COMPLETE - 16
		&Spell::SpellEffectWeapondamageNoschool,	//SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL - 17
		&Spell::SpellEffectResurrect,				//SPELL_EFFECT_RESURRECT - 18
		&Spell::SpellEffectAddExtraAttacks,			//SPELL_EFFECT_ADD_EXTRA_ATTACKS - 19
		&Spell::SpellEffectDodge,					//SPELL_EFFECT_DODGE - 20
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_EVADE - 21
		&Spell::SpellEffectParry,					//SPELL_EFFECT_PARRY - 22
		&Spell::SpellEffectBlock,					//SPELL_EFFECT_BLOCK - 23
		&Spell::SpellEffectCreateItem,				//SPELL_EFFECT_CREATE_ITEM - 24
		&Spell::SpellEffectWeapon,					//SPELL_EFFECT_WEAPON - 25
		&Spell::SpellEffectDefense,					//SPELL_EFFECT_DEFENSE - 26
		&Spell::SpellEffectPersistentAA,			//SPELL_EFFECT_PERSISTENT_AREA_AURA - 27
		&Spell::SpellEffectSummon,					//SPELL_EFFECT_SUMMON - 28
		&Spell::SpellEffectLeap,					//SPELL_EFFECT_LEAP - 29
		&Spell::SpellEffectEnergize,				//SPELL_EFFECT_ENERGIZE - 30
		&Spell::SpellEffectWeaponDmgPerc,			//SPELL_EFFECT_WEAPON_PERCENT_DAMAGE - 31
		&Spell::SpellEffectTriggerMissile,			//SPELL_EFFECT_TRIGGER_MISSILE - 32
		&Spell::SpellEffectOpenLock,				//SPELL_EFFECT_OPEN_LOCK - 33
		&Spell::SpellEffectTranformItem,			//SPELL_EFFECT_TRANSFORM_ITEM - 34
		&Spell::SpellEffectApplyAA,					//SPELL_EFFECT_APPLY_AREA_AURA - 35
//		&Spell::SpellEffectNULL,					// seems to be a scripted effect in 303 - 35 Increases stuff but seems to everything. 147 spells use it
		&Spell::SpellEffectLearnSpell,				//SPELL_EFFECT_LEARN_SPELL - 36
		&Spell::SpellEffectSpellDefense,			//SPELL_EFFECT_SPELL_DEFENSE - 37
		&Spell::SpellEffectDispel,					//SPELL_EFFECT_DISPEL - 38
		&Spell::SpellEffectLanguage,				//SPELL_EFFECT_LANGUAGE - 39
		&Spell::SpellEffectDualWield,				//SPELL_EFFECT_DUAL_WIELD - 40
//		&Spell::SpellEffectSummonWild,				//SPELL_EFFECT_SUMMON_WILD - 41
		&Spell::SpellEffectNULL,					//this is some move related effect now. Ex: leap, jump, tel - 41
//		&Spell::SpellEffectSummonGuardian,			//SPELL_EFFECT_SUMMON_GUARDIAN - 42
		&Spell::SpellEffectDummy,					//this is some move related effect now. Ex: pull, knock, tel - 42
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER - 43
		&Spell::SpellEffectSkillStep,				//SPELL_EFFECT_SKILL_STEP - 44
		&Spell::SpellEffectAddHonor,				//SPELL_ADD_HONOR - 45
		&Spell::SpellEffectSpawn,					//SPELL_EFFECT_SPAWN - 46
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_TRADE_SKILL - 47
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_STEALTH - 48
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_DETECT - 49
		&Spell::SpellEffectSummonObject,			//SPELL_EFFECT_SUMMON_OBJECT - 50
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_FORCE_CRITICAL_HIT - 51 NA
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_GUARANTEE_HIT - 52 NA
		&Spell::SpellEffectEnchantItem,				//SPELL_EFFECT_ENCHANT_ITEM - 53
		&Spell::SpellEffectEnchantItemTemporary,	//SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY - 54
		&Spell::SpellEffectTameCreature,			//SPELL_EFFECT_TAMECREATURE - 55
		&Spell::SpellEffectSummonPet,				//SPELL_EFFECT_SUMMON_PET	- 56
		&Spell::SpellEffectLearnPetSpell,			//SPELL_EFFECT_LEARN_PET_SPELL - 57
		&Spell::SpellEffectWeapondamage,			//SPELL_EFFECT_WEAPON_DAMAGE - 58
		&Spell::SpellEffectOpenLockItem,			//SPELL_EFFECT_OPEN_LOCK_ITEM - 59
		&Spell::SpellEffectProficiency,				//SPELL_EFFECT_PROFICIENCY - 60
		&Spell::SpellEffectSendEvent,				//SPELL_EFFECT_SEND_EVENT - 61
		&Spell::SpellEffectPowerBurn,				//SPELL_EFFECT_POWER_BURN - 62
		&Spell::SpellEffectThreat,					//SPELL_EFFECT_THREAT - 63
		&Spell::SpellEffectTriggerSpell,			//SPELL_EFFECT_TRIGGER_SPELL - 64
//		&Spell::SpellEffectHealthFunnel,			//SPELL_EFFECT_HEALTH_FUNNEL - 65
		&Spell::SpellEffectApplyAA,					//SPELL_EFFECT_APPLY_AREA_AURA - 65
		&Spell::SpellEffectPowerFunnel,				//SPELL_EFFECT_POWER_FUNNEL - 66
		&Spell::SpellEffectHealMaxHealth,			//SPELL_EFFECT_HEAL_MAX_HEALTH - 67
		&Spell::SpellEffectInterruptCast,			//SPELL_EFFECT_INTERRUPT_CAST - 68
		&Spell::SpellEffectDistract,				//SPELL_EFFECT_DISTRACT - 69
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_PULL - 70
		&Spell::SpellEffectPickpocket,				//SPELL_EFFECT_PICKPOCKET - 71
		&Spell::SpellEffectAddFarsight,				//SPELL_EFFECT_ADD_FARSIGHT - 72
		&Spell::SpellEffectSummonPossessed,			//SPELL_EFFECT_SUMMON_POSSESSED - 73
//		&Spell::SpellEffectCreateSummonTotem,		//SPELL_EFFECT_SUMMON_TOTEM - 74
		&Spell::SpellEffectEquipGlyph,				//SPELL_EFFECT_APPLY_GLYPH - 74
		&Spell::SpellEffectHealMechanical,			//SPELL_EFFECT_HEAL_MECHANICAL - 75
		&Spell::SpellEffectSummonObjectWild,		//SPELL_EFFECT_SUMMON_OBJECT_WILD - 76
		&Spell::SpellEffectScriptEffect,			//SPELL_EFFECT_SCRIPT_EFFECT - 77
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_ATTACK - 78
		&Spell::SpellEffectSanctuary,				//SPELL_EFFECT_SANCTUARY - 79
		&Spell::SpellEffectAddComboPoints,			//SPELL_EFFECT_ADD_COMBO_POINTS - 80
		&Spell::SpellEffectCreateHouse,				//SPELL_EFFECT_CREATE_HOUSE - 81
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_BIND_SIGHT - 82
		&Spell::SpellEffectDuel,					//SPELL_EFFECT_DUEL - 83
		&Spell::SpellEffectStuck,					//SPELL_EFFECT_STUCK - 84
		&Spell::SpellEffectSummonPlayer,			//SPELL_EFFECT_SUMMON_PLAYER - 85
		&Spell::SpellEffectActivateObject,			//SPELL_EFFECT_ACTIVATE_OBJECT - 86
		&Spell::SpellEffectWMODamage,				//SPELL_EFFECT_WMO_DAMAGE - 87
		&Spell::SpellEffectWMORepair,				//SPELL_EFFECT_WMO_REPAIR - 88
		&Spell::SpellEffectSummonTotem,				//SPELL_EFFECT_SUMMON_TOTEM_SLOT3 - 89
		&Spell::SpellEffectSummonTotem,				//SPELL_EFFECT_SUMMON_TOTEM_SLOT4 - 90
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_THREAT_ALL - 91 UNUSED
		&Spell::SpellEffectEnchantHeldItem,			//SPELL_EFFECT_ENCHANT_HELD_ITEM - 92
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_SUMMON_PHANTASM - 93 OLD
		&Spell::SpellEffectSelfResurrect,			//SPELL_EFFECT_SELF_RESURRECT - 94
		&Spell::SpellEffectSkinning,				//SPELL_EFFECT_SKINNING - 95
		&Spell::SpellEffectCharge,					//SPELL_EFFECT_CHARGE - 96
		&Spell::SpellEffectSummonCritter,			//SPELL_EFFECT_SUMMON_CRITTER - 97
		&Spell::SpellEffectKnockBack,				//SPELL_EFFECT_KNOCK_BACK - 98
		&Spell::SpellEffectDisenchant,				//SPELL_EFFECT_DISENCHANT - 99
		&Spell::SpellEffectInebriate,				//SPELL_EFFECT_INEBRIATE - 100
		&Spell::SpellEffectFeedPet,					//SPELL_EFFECT_FEED_PET - 101
		&Spell::SpellEffectDismissPet,				//SPELL_EFFECT_DISMISS_PET - 102
		&Spell::SpellEffectReputation,				//SPELL_EFFECT_REPUTATION - 103
		&Spell::SpellEffectSummonObjectSlot,		//SPELL_EFFECT_SUMMON_OBJECT_SLOT1 - 104
		&Spell::SpellEffectSummonObjectSlot,		//SPELL_EFFECT_SUMMON_OBJECT_SLOT2 - 105
		&Spell::SpellEffectSummonObjectSlot,		//SPELL_EFFECT_SUMMON_OBJECT_SLOT3 - 106
		&Spell::SpellEffectSummonObjectSlot,		//SPELL_EFFECT_SUMMON_OBJECT_SLOT4 - 107
		&Spell::SpellEffectDispelMechanic,			//SPELL_EFFECT_DISPEL_MECHANIC - 108
		&Spell::SpellEffectSummonDeadPet,			//SPELL_EFFECT_SUMMON_DEAD_PET - 109
		&Spell::SpellEffectDestroyAllTotems,		//SPELL_EFFECT_DESTROY_ALL_TOTEMS - 110
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_DURABILITY_DAMAGE - 111
		&Spell::SpellEffectSummonDemon,				//SPELL_EFFECT_SUMMON_DEMON - 112
		&Spell::SpellEffectResurrectNew,			//SPELL_EFFECT_RESURRECT_NEW - 113
		&Spell::SpellEffectAttackMe,				//SPELL_EFFECT_ATTACK_ME - 114
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_DURABILITY_DAMAGE_PCT - 115
		&Spell::SpellEffectSkinPlayerCorpse,		//SPELL_EFFECT_SKIN_PLAYER_CORPSE - 116
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_SPIRIT_HEAL - 117//Not used
		&Spell::SpellEffectSkill,					//SPELL_EFFECT_SKILL - 118
		&Spell::SpellEffectApplyPetAura,			//SPELL_EFFECT_APPLY_PET_AURA - 119
		&Spell::SpellEffectNULL,					//SPELL_EFFECT_TELEPORT_GRAVEYARD - 120//Not used
		&Spell::SpellEffectDummyMelee,				//SPELL_EFFECT_DUMMYMELEE	- 121
		&Spell::SpellEffectNULL,					// unknown - 122 //not used
		&Spell::SpellEffectFilming,					//SPELL_EFFECT_FILMING - 123 // http://www.thottbot.com/?sp=27998: flightpath 
		&Spell::SpellEffectPlayerPull,				//SPELL_EFFECT_PLAYER_PULL - 124 - http://thottbot.com/e2312
		&Spell::SpellEffectReduceThreatPercent,		//SPELL_EFFECT_REDUCE_THREAT_PERCENT - 125 // Reduce Threat by % //http://www.thottbot.com/?sp=32835
		&Spell::SpellEffectSpellSteal,				//SPELL_EFFECT_SPELL_STEAL - 126 // Steal Beneficial Buff (Magic) //http://www.thottbot.com/?sp=30449
		&Spell::SpellEffectProspecting,				// unknown - 127 // Search 5 ore of a base metal for precious gems.  This will destroy the ore in the process.
		&Spell::SpellEffectApplyAura128,			// unknown - 128 // Adjust a stats by %: Mod Stat // ITS FLAT
		&Spell::SpellEffectApplyAura,				// unknown - 129 // Mod Dmg % (Spells)
		&Spell::SpellEffectRedirectThreat,// unknown - 130 // http://www.thottbot.com/s34477
		&Spell::SpellEffectNULL,					// unknown - 131 // test spell
		&Spell::SpellEffectNULL,					// unknown - 132 // no spells
		&Spell::SpellEffectForgetSpecialization,	//SPELL_EFFECT_FORGET_SPECIALIZATION - 133 // http://www.thottbot.com/s36441 // I think this is a gm/npc spell
		&Spell::SpellEffectKillCredit,				// SPELL_EFFECT_KILL_CREDIT - 134 // related to summoning objects and removing them, http://www.thottbot.com/s39161
		&Spell::SpellEffectNULL,					// unknown - 135 // no spells
		&Spell::SpellEffectHealMaxHealthPCT,		// SPELL_EFFECT_HEAL_MAXHEALTH_PCT - 136 // http://www.thottbot.com/s41542 and http://www.thottbot.com/s39703
		&Spell::SpellEffectEnergizeMaxEnergyPct,	// SPELL_EFFECT_ENERGIZE_MAXPOWER_PCT - 137 // http://www.thottbot.com/s41542 - restore max mana pct
		&Spell::SpellEffectKnockBack,				// unknown - 138 // related to superjump or even "*jump" spells http://www.thottbot.com/?e=Unknown%20138
		&Spell::SpellEffectNULL,					// unknown - 139 // no spells
		&Spell::SpellEffectTriggerSpell,			// - 140 - triggers a spell from target back to caster - used at Malacrass f.e.
		&Spell::SpellEffectNULL,					// unknown - 141 // triggers spell, magic one,  (Mother spell) http://www.thottbot.com/s41065
		&Spell::SpellEffectTriggerSpellWithValue,	//SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE - 142 // triggers some kind of "Put spell on target" thing... (dono for sure) http://www.thottbot.com/s40872 and http://www.thottbot.com/s33076
		&Spell::SpellEffectApplyAura,				// unknown - 143 // Master -> deamon effecting spell, http://www.thottbot.com/s25228 and http://www.thottbot.com/s35696
		&Spell::SpellEffectNULL, // unknown - 144 // no spells
		&Spell::SpellEffectNULL, // Rune regen/empower - 145 
		&Spell::SpellEffectRuneToPower, // Temporally change blood rune to death rune - 146
		&Spell::SpellEffectNULL, // SPELL_EFFECT_QUEST_FAIL - 147 // http://thottbot.com/s46070
		&Spell::SpellEffectNULL, // school dmg - 148 
		&Spell::SpellEffectCharge, // charge - 149
		&Spell::SpellEffectNULL, // - 150 
		&Spell::SpellEffectSummonTarget, // SPELL_EFFECT_SUMMON_TARGET - 151 // trigger ritual of summoning
		&Spell::SpellEffectNULL, // summon refered friend (acc setting not used for emus) - 152
		&Spell::SpellEffectCreatePet, // SPELL_EFFECT_TAME_CREATURE - 153 // http://thottbot.com/s46686 , http://thottbot.com/s46716 , http://thottbot.com/s46717, http://thottbot.com/s46718 ...  // spelleffect summon pet ??
		&Spell::SpellEffectTeachTaxiPath, //  - 154
		&Spell::SpellEffectNULL, // remove 2 hand requirement for items - 155
		&Spell::SpellEffectEnchantItem, // SPELL_EFFECT_ADD_SOCKET - add socket to item - 156
		&Spell::SpellEffectCreateItem, // also creates a lot if gems - discover recipes - 157
		&Spell::SpellEffectMilling, // Milling - 158
		&Spell::SpellEffectRenamePet, // Ability to rename pet. Seems to be client sided - 159
		&Spell::SpellEffectNULL, //160
		&Spell::SpellEffectSetTalentSpecsCount, //161 Sets number of talent specs available to the player
		&Spell::SpellEffectActivateTalentSpec, //162 Activates one of talent specs
};

char* SpellEffectNames[TOTAL_SPELL_EFFECTS] = {
	"NULL",
	"INSTANT_KILL",              //    1
	"SCHOOL_DAMAGE",             //    2
	"DUMMY",                     //    3
	"PORTAL_TELEPORT",           //    4
	"TELEPORT_UNITS",            //    5
	"APPLY_AURA",                //    6
	"ENVIRONMENTAL_DAMAGE",      //    7
	"POWER_DRAIN",               //    8
	"HEALTH_LEECH",              //    9
	"HEAL",                      //    10
	"BIND",                      //    11
	"PORTAL",                    //    12
	"RITUAL_BASE",               //    13
	"RITUAL_SPECIALIZE",         //    14
	"RITUAL_ACTIVATE_PORTAL",    //    15
	"QUEST_COMPLETE",            //    16
	"WEAPON_DAMAGE_NOSCHOOL",    //    17
	"RESURRECT",                 //    18
	"ADD_EXTRA_ATTACKS",         //    19
	"DODGE",                     //    20
	"EVADE",                     //    21
	"PARRY",                     //    22
	"BLOCK",                     //    23
	"CREATE_ITEM",               //    24
	"WEAPON",                    //    25
	"DEFENSE",                   //    26
	"PERSISTENT_AREA_AURA",      //    27
	"SUMMON",                    //    28
	"LEAP",                      //    29
	"ENERGIZE",                  //    30
	"WEAPON_PERCENT_DAMAGE",     //    31
	"TRIGGER_MISSILE",           //    32
	"OPEN_LOCK",                 //    33
	"TRANSFORM_ITEM",            //    34
	"APPLY_AREA_AURA",           //    35
	"LEARN_SPELL",               //    36
	"SPELL_DEFENSE",             //    37
	"DISPEL",                    //    38
	"LANGUAGE",                  //    39
	"DUAL_WIELD",                //    40
	"SUMMON_WILD",               //    41
	"SUMMON_GUARDIAN",           //    42
	"TELEPORT_UNITS_FACE_CASTER",//    43
	"SKILL_STEP",                //    44
	"SPELL_EFFECT_ADD_HONOR",    //    45
	"SPAWN",                     //    46
	"TRADE_SKILL",               //    47
	"STEALTH",                   //    48
	"DETECT",                    //    49
	"SUMMON_OBJECT",             //    50
	"FORCE_CRITICAL_HIT",        //    51
	"GUARANTEE_HIT",             //    52
	"ENCHANT_ITEM",              //    53
	"ENCHANT_ITEM_TEMPORARY",    //    54
	"TAMECREATURE",              //    55
	"SUMMON_PET",                //    56
	"LEARN_PET_SPELL",           //    57
	"WEAPON_DAMAGE",             //    58
	"OPEN_LOCK_ITEM",            //    59
	"PROFICIENCY",               //    60
	"SEND_EVENT",                //    61
	"POWER_BURN",                //    62
	"THREAT",                    //    63
	"TRIGGER_SPELL",             //    64
//	"HEALTH_FUNNEL",             //    65
	"APPLY_AREA_AURA",           //    65
	"CREATE_MANA_GEM",           //    66
	"HEAL_MAX_HEALTH",           //    67
	"INTERRUPT_CAST",            //    68
	"DISTRACT",                  //    69
	"PULL",                      //    70
	"PICKPOCKET",                //    71
	"ADD_FARSIGHT",              //    72
	"UNTRAIN_TALENTS",           //    73
	"SPELL_EFFECT_APPLY_GLYPH",  //    74
	"HEAL_MECHANICAL",           //    75
	"SUMMON_OBJECT_WILD",        //    76
	"SCRIPT_EFFECT",             //    77
	"ATTACK",                    //    78
	"SANCTUARY",                 //    79
	"ADD_COMBO_POINTS",          //    80
	"CREATE_HOUSE",              //    81
	"BIND_SIGHT",                //    82
	"DUEL",                      //    83
	"STUCK",                     //    84
	"SUMMON_PLAYER",             //    85
	"ACTIVATE_OBJECT",           //    86
	"WMO_DAMAGE",				 //    87
	"WMO_REPAIR",				 //    88
	"WMO_CHANGE",				 //    89
	"KILL_CREDIT",				 //    90
	"THREAT_ALL",                //    91
	"ENCHANT_HELD_ITEM",         //    92
	"SUMMON_PHANTASM",           //    93
	"SELF_RESURRECT",            //    94
	"SKINNING",                  //    95
	"CHARGE",                    //    96
	"SUMMON_CRITTER",            //    97
	"KNOCK_BACK",                //    98
	"DISENCHANT",                //    99
	"INEBRIATE",                 //    100
	"FEED_PET",                  //    101
	"DISMISS_PET",               //    102
	"REPUTATION",                //    103
	"SUMMON_OBJECT_SLOT1",       //    104
	"SUMMON_OBJECT_SLOT2",       //    105
	"SUMMON_OBJECT_SLOT3",       //    106
	"SUMMON_OBJECT_SLOT4",       //    107
	"DISPEL_MECHANIC",           //    108
	"SUMMON_DEAD_PET",           //    109
	"DESTROY_ALL_TOTEMS",        //    110
	"DURABILITY_DAMAGE",         //    111
	"SUMMON_DEMON",              //    112
	"RESURRECT_FLAT",            //    113
	"ATTACK_ME",                 //    114
	"DURABILITY_DAMAGE_PCT",     //    115
	"SKIN_PLAYER_CORPSE",        //    116
	"SPIRIT_HEAL",               //    117
	"SKILL",                     //    118
	"APPLY_PET_AURA",            //    119
	"TELEPORT_GRAVEYARD",        //    120
	"DUMMYMELEE",                //    121
	"UNKNOWN1",                  //    122
	"FILMING",                   //    123
	"PLAYER_PULL",               //    124
	"UNKNOWN4",                  //    125
	"UNKNOWN5",                  //    126
	"PROSPECTING",               //    127
	"UNKNOWN7",                  //    128
	"APPLY_AURA",                //    129
	"UNKNOWN10",                 //    130
	"UNKNOWN11",                 //    131
	"UNKNOWN12",                 //    132
	"FORGET_SPECIALIZATION",     //    133
	"UNKNOWN14",                 //    134
	"UNKNOWN15",                 //    135
	"SPELL_EFFECT_HEAL_MAXHEALTH_PCT",                 //    136
	"SPELL_EFFECT_ENERGIZE_MAXPOWER_PCT",                 //    137
	"UNKNOWN18",                 //    138
	"UNKNOWN19",                 //    139
	"SPELL_EFFECT_FORCE_CAST",   //    140
	"UNKNOWN21",                 //    141
	"TRIGGER_SPELL_WITH_VALUE",  //    142
	"PET-MASTER AURA",           //    143
	"UNKNOWN23",                 //    144
	"UNKNOWN24",                 //    145
	"UNKNOWN25",                 //    146
	"QUEST_FAIL",                //    147
	"UNKNOWN26",                 //    148
	"UNKNOWN27",                 //    149
	"UNKNOWN28",                 //    150
	"SUMMON_TARGET",             //    151
	"UNKNOWN29",                 //    152
	"TAME_CREATURE",             //    153
	"?",						 //    154
	"?",						 //    155
	"ADD_SOCKET",				 //    156
	"CREATE_ITEM_2",             //    157
	"MILLING",				     //    158
	"ALLOW_RENAME_PET",          //    159
	"UNKNOWN160",		         //    160
	"SET_SPEC_COUNT",            //    161
	"SET_ACTIVE_SPEC",           //    162
};

void Spell::SpellEffectNULL(uint32 i)
{
	sLog.outDebug("Unhandled spell effect %u in spell %u.\n",GetProto()->Effect[i],GetProto()->Id);
}

void Spell::SpellEffectInstantKill(uint32 i)
{
	if(!unitTarget || !unitTarget->isAlive())
	{ 
		return;
	}

	//Sacrifice: if spell caster has "void walker" pet, pet dies and spell caster gets a 
	/*Sacrifices the Voidwalker, giving its owner a shield that will absorb 
	305 damage for 30 sec. While the shield holds, spellcasting will not be \
	interrupted by damage.*/

	/*
	Demonic Sacrifice

	When activated, sacrifices your summoned demon to grant you an effect that lasts 
	30 minutes. The effect is canceled if any Demon is summoned. 
	Imp: Increases your Fire damage by 15%. 
	Voidwalker: Restores 3% of total Health every 4 sec. 
	Succubus: Increases your Shadow damage by 15%. 
	Felhunter: Restores 2% of total Mana every 4 sec.

	When activated, sacrifices your summoned demon to grant you an effect that lasts $18789d.  The effect is canceled if any Demon is summoned.

	Imp: Increases your Fire damage by $18789s1%.

	Voidwalker: Restores $18790s1% of total Health every $18790t1 sec.

	Succubus: Increases your Shadow damage by $18791s1%.

	Felhunter: Restores $18792s1% of total Mana every $18792t1 sec.

	*/
	uint32 spellId = GetProto()->Id;

	switch(spellId)
	{
	case 3617://Goblin Bomb Suicide
		{
			if(m_caster->GetTypeId() != TYPEID_UNIT)
				break;
			Unit *caster = m_caster->GetMapMgr()->GetPlayer(m_caster->GetUInt32Value(UNIT_FIELD_SUMMONEDBY));
			caster->summonPet->RemoveFromWorld(false,true);
			sGarbageCollection.AddObject( caster->summonPet );
			caster->summonPet = NULL;
		}break;
	case 7814:
	case 7815:
	case 7816:
	case 7876:
	case 7877:
	case 7878:
	case 11778:
	case 11779:
	case 11780:
	case 15968:
	case 15969:
	case 18128:
	case 18129:
	case 20398:
	case 20399:
	case 20400:
	case 20401:
	case 20402:
		{
		}break;

	case 29364:	// encapsulate voidwalker
		{
			return;
		}break;
	case 18788: //Demonic Sacrifice (508745)
		uint32 spellid1 = 0;
		switch(unitTarget->GetEntry())
		{
			case 416: //Imp
			{   
				spellid1 = 18789;
		
			}break;
			case 417: //Felhunter
			{
				spellid1 = 18792;
		
			}break;
			case 1860: //VoidWalker
			{
				spellid1 = 18790;
			}break;
			case 1863: //Succubus
			{
				spellid1 = 18791;
			}break;
			case 17252: //felguard
			{
				spellid1 = 35701;
			}break;
		}
		//now caster gains this buff
		if (spellid1)
		{
			SpellEntry *sp = dbcSpell.LookupEntry(spellid1);
			if (sp) u_caster->CastSpell(u_caster, sp, true);
		}
	}

	switch( GetProto()->NameHash )
	{
	case SPELL_HASH_DEATH_PACT:
		{}break;	//allow the kill on our minions, special test is used to avoid people exploiting isnta kill spells
	case SPELL_HASH_SACRIFICE:
		{
			if( !u_caster->IsPet() )
			{ 
				return;
			}

			SafePetCast(u_caster)->Dismiss( );
			return;
		}break;
	case SPELL_HASH_DEMONIC_SACRIFICE:
		{
			if( !p_caster->IsPlayer() )
			{ 
				return;
			}

			SafePetCast(unitTarget)->Dismiss( );
			return;
		}break;

	default:
		{
			// moar cheaters
			if( p_caster == NULL || (u_caster != NULL && u_caster->IsPet() ) )
			{ 
				return;
			}

			if( p_caster->GetSession()->GetPermissionCount() == 0 )
			{ 
				return;
			}
		}
	}
	//instant kill effects don't have a log
	//m_caster->SpellNonMeleeDamageLog(unitTarget, GetProto()->Id, unitTarget->GetUInt32Value(UNIT_FIELD_HEALTH), true);
//	m_caster->DealDamage(unitTarget, unitTarget->GetUInt32Value(UNIT_FIELD_HEALTH)*100, 0, 0, 0);
	unitTarget->SetUInt32Value( UNIT_FIELD_HEALTH, 1 );
	m_caster->DealDamage(unitTarget, 0x0F000000, 0, 0, 0);
	WorldPacket data(SMSG_SPELLINSTAKILLLOG, 100);
	data << m_caster->GetGUID() << unitTarget->GetGUID() << spellId;
	m_caster->SendMessageToSet(&data, true);
}

void Spell::SpellEffectSchoolDMG(uint32 i) // dmg school
{
	if(!unitTarget || !unitTarget->isAlive())
	{ 
		return;
	}

	if(unitTarget->SchoolImmunityList[GetProto()->School])
	{
		SendCastResult(SPELL_FAILED_IMMUNE);
		return;
	}
   
	int32 dmg;
	bool static_damage=false;

	{
		dmg = damage;
		switch(GetProto()->NameHash)
		{
			case SPELL_HASH_MOLTEN_ARMOR:		// fire armor, is static damage
			case SPELL_HASH_FIRE_STRIKE:
			case SPELL_HASH_LIGHTNING_STRIKE:
				static_damage=true;
			break;
			//Shockwave Damage
			//Concussion Blow
			case SPELL_HASH_SHOCKWAVE:
			case SPELL_HASH_CONCUSSION_BLOW:
			{
				dmg = float2int32( float( u_caster->GetAP() ) * 0.75f );
			}break;
		}
	}

	// check for no more damage left (chains)
	if(!dmg) 
		return;

	/*********************************************************************
	CONFLAGRATE SHOULD REMOVE THE IMMOLATE DEBUFF
	**********************************************************************/
//	if( GetProto()->NameHash == SPELL_HASH_CONFLAGRATE && ( p_caster == NULL || p_caster->HasGlyphWithID( GLYPH_WARLOCK_CONFLAGRATE ) == false ) )
//		unitTarget->RemoveAuraByNameHash(SPELL_HASH_IMMOLATE );
//		unitTarget->RemoveFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_IMMOLATE );

	if( dmg < 0 )
		return;

	//make sure there are no value overflows anywhere
	if( dmg > 100000 )
		return;

	if(GetProto()->speed > 0 && m_triggeredSpell == false )
	{
		//FIXME:Use this one and check player movement and update distance
		//It now only checks the first distance and hits the player after time expires.
		//sEventMgr.AddEvent(this, &Spell::_DamageRangeUpdate, (uint32)100, EVENT_SPELL_DAMAGE_HIT, 100, 0);
		float dist = m_caster->CalcDistance( unitTarget );
		float time = ((dist*1000.0f)/GetProto()->speed);
		if(time <= 500)
		{
			SpellEntry *ID_for_the_logs ;
			if( GetProto()->spell_id_client )
				ID_for_the_logs = dbcSpell.LookupEntry( GetProto()->spell_id_client );	//this might get to be null. Dirty client has more spells then us. CHEATER !
			else
				ID_for_the_logs = GetProto();
			m_caster->SpellNonMeleeDamageLog(unitTarget, ID_for_the_logs, dmg, pSpellId==0, static_dmg[i] != 0, false, 1, chaincast_jump_pct_mod);
		}
		else
		{
			damageToHit = dmg;
			/*sEventMgr.AddEvent(m_caster, &Object::SpellNonMeleeDamageLog,
				unitTarget,GetProto()->Id,dmg, EVENT_SPELL_DAMAGE_HIT, uint32(time), 1);*/
			sEventMgr.AddEvent(m_caster, &Object::EventSpellDamage, unitTarget->GetGUID(), 
				GetProto()->Id, (uint32)dmg, EVENT_SPELL_DAMAGE_HIT, uint32(time), 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}
	}
	else
	{
		if( GetType() == SPELL_DMG_TYPE_MAGIC )		
		{
			static_damage = static_damage || (static_dmg[i] != 0);
			m_caster->SpellNonMeleeDamageLog( unitTarget, GetProto(), dmg, pSpellId == 0, static_damage, false, 1, chaincast_jump_pct_mod );
		}
		else 
		{
			if( u_caster != NULL )
			{
				uint32 _type;
				if( GetType() == SPELL_DMG_TYPE_RANGED )
					_type = RANGED;
				else
				{
					if (GetProto()->AttributesExC & 0x1000000)
						_type =  OFFHAND;
					else
						_type = MELEE;
				}
				u_caster->Strike( unitTarget, _type, GetProto(), 0, 0, dmg, pSpellId == 0, true );
			}
		}
	}   
	if(GetProto()->EffectChainTarget[i])//chain
	{
		int32 reduce_reduce = 0;	
		if((GetProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && u_caster)
			SM_FIValue(u_caster->SM_PJumpReduce,&reduce_reduce,GetProto()->SpellGroupType);
		chaincast_jump_pct_mod = float2int32( chaincast_jump_pct_mod * GetProto()->dmg_multiplier[i] ) + reduce_reduce;
	}
}

void Spell::SpellEffectDummy(uint32 i) // Dummy(Scripted events)
{
	uint32 spellId = GetProto()->Id;
	
	// Try a dummy SpellHandler
	if(sScriptMgr.CallScriptedDummySpell(spellId, i, this))
	{ 
		return;
	}

	if( i_caster && i_caster->GetProto() )
	{
		uint32 item_entry = i_caster->GetProto()->ItemId;

		switch(item_entry)
		{
#include "../arcemu-customs/custom_item_handlers.cpp"
			default:break;
		};
	}

	switch( GetProto()->NameHash )
	{
		case SPELL_HASH_COLD_SNAP:
		{
			if( p_caster )
				p_caster->ClearCooldownsOnLine( SKILL_FROST, GetProto()->Id );
		}break;
		case SPELL_HASH_SAVAGE_ROAR:
		{
			if( p_caster && p_caster->m_comboPoints )
			{
				forced_duration = 9000 + p_caster->m_comboPoints * 5000;	//this will be used for effect 1 = aura
				Dur = forced_duration;
			}
		}break;
		case SPELL_HASH_VANISH:
		{
			if( u_caster )
				u_caster->RemoveAllMovementImpairing();
		}break;
		case SPELL_HASH_BLADED_ARMOR://Increases your attack power by $s1 for every $s2 armor value you have.
			{
				if( u_caster )
					forced_basepoints[1] = (GetProto()->EffectBasePoints[1] + 1)*u_caster->GetUInt32Value( UNIT_FIELD_RESISTANCES ) / damage;
			}break;
		case SPELL_HASH_KILLING_SPREE:
			{
				if( u_caster == NULL || unitTarget == NULL )
					return;
				//push the other events back with 1 trigger period
				sEventMgr.DelayEventTrigger( u_caster, EVENT_KILLING_SPREE_PROC, GetProto()->EffectAmplitude[i] );
				//register a new trigger
				uint64 guid = unitTarget->GetGUID();
				sEventMgr.AddEvent(u_caster, &Unit::EventCastSpell2, guid, GetProto()->EffectTriggerSpell[i],
					EVENT_KILLING_SPREE_PROC, GetProto()->EffectAmplitude[i], 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			}break;
		case SPELL_HASH_CALL_OF_THE_ELEMENTS:
			{
				if( p_caster )
				{
					uint32 totem;
					totem = p_caster->GetAction( 132 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
					totem = p_caster->GetAction( 133 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
					totem = p_caster->GetAction( 134 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
					totem = p_caster->GetAction( 135 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
				}
			}break;
		case SPELL_HASH_CALL_OF_THE_ANCESTORS:
			{
				if( p_caster )
				{
					uint32 totem;
					totem = p_caster->GetAction( 136 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
					totem = p_caster->GetAction( 137 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
					totem = p_caster->GetAction( 138 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
					totem = p_caster->GetAction( 139 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
				}
			}break;
		case SPELL_HASH_CALL_OF_THE_SPIRITS:
			{
				if( p_caster )
				{
					uint32 totem;
					totem = p_caster->GetAction( 140 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
					totem = p_caster->GetAction( 141 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
					totem = p_caster->GetAction( 142 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
					totem = p_caster->GetAction( 143 );
					if( totem )
					{
						p_caster->ClearCategoryCooldownForSpell( totem );
						p_caster->CastSpell( p_caster, totem, false );
					}
				}
			}break;
	};

	switch(spellId)
	{
#include "../arcemu-customs/custom_spell_effects.cpp"
		//Readiness
		case 23989:
			{
				if( p_caster == NULL )
					return;
				uint32 insiginificant_cooldown = getMSTime() + 500;
				PlayerCooldownMap::iterator itr, itr2;
				for(uint32 i = 0; i < NUM_COOLDOWN_TYPES; ++i)
				{
					for( itr = p_caster->m_cooldownMap[i].begin(); itr != p_caster->m_cooldownMap[i].end(); )
					{
						itr2 = itr++;
						//clear all category cooldowns
						if( i == COOLDOWN_TYPE_CATEGORY )
						{
							p_caster->m_cooldownMap[i].erase( itr2 );
						}
						else 
						{
							SpellEntry * spe = dbcSpell.LookupEntry( itr2->first );
							if( spe->NameHash == SPELL_HASH_BESTIAL_WRATH || spe->NameHash == SPELL_HASH_READINESS )
								continue;
							//if we send too many packets the client chokes on it and does a 3 second lag :(
							if( itr2->second.ExpireTime > insiginificant_cooldown )
							{
								sStackWolrdPacket( data, SMSG_CLEAR_COOLDOWN, 16);
								data << itr2->first << p_caster->GetGUID();
								p_caster->GetSession()->SendPacket(&data);
							}

							p_caster->m_cooldownMap[i].erase( itr2 );
						}
					}
				}
			}break;
		//some quest spell - Throw Ice
		case 56099:
			{
				std::set<Object*>::iterator itr,itr2;
				m_caster->AquireInrangeLock(); //make sure to release lock before exit function !
				for( itr2 = m_caster->GetInRangeSetBegin(); itr2 != m_caster->GetInRangeSetEnd(); )
				{
					itr = itr2;
					itr2++;
					if( (*itr)->IsGameObject() == false || (*itr)->GetEntry() != 192124 )
						continue;
					
					GameObject *go = u_caster->GetMapMgr()->CreateGameObject(192127);
					if( go == NULL )
					{
						sLog.outDebug("Missing GO proto 192127");
						return;
					}
//					go->CreateFromProto( 192127, m_caster->GetMapId(), m_caster->GetPositionX() + RandomUInt( 3 ), m_caster->GetPositionY() + RandomUInt( 3 ), m_caster->GetPositionZ(), m_caster->GetOrientation() );
					go->CreateFromProto( 192127, (*itr)->GetMapId(), (*itr)->GetPositionX(), (*itr)->GetPositionY(), (*itr)->GetPositionZ(), (*itr)->GetOrientation() );
					go->SetUInt64Value( OBJECT_FIELD_CREATED_BY, m_caster->GetGUID() );
					go->SetInstanceID( m_caster->GetInstanceID() );
					go->PushToWorld( m_caster->GetMapMgr() );
					sEventMgr.AddEvent(go, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, 5*60*1000, 1,0);
					break;
				}
				m_caster->ReleaseInrangeLock();
			}break;
		//Well of Souls - boss spell
		case 68820:
			{
				//show jumping anymation ?
				sStackWolrdPacket( data, SMSG_MOVE_KNOCK_BACK, 150);
				data << m_caster->GetNewGUID();
				data << getMSTime();
				data << cosf(m_caster->GetOrientation()) << sinf(m_caster->GetOrientation());
				data << float( sqrt( m_caster->GetDistance2dSq( unitTarget ) ) );
				data << float(-10.0f);	//this is some height factor
				m_caster->SendMessageToSet(&data,false);
				//mobs insta teleport :P
				u_caster->SetPosition(unitTarget->GetPosition(), true);
				u_caster->CastSpellDelayed( unitTarget->GetGUID(), 68853, 2000 );
			}break;
//		case SPELL_HASH_RESTORE_SOUL:	//revive players that we see
		case 72595:
		{
			std::set<Object*>::iterator itr,itr2;
			m_caster->AquireInrangeLock(); //make sure to release lock before exit function !
			for( itr2 = m_caster->GetInRangeSetBegin(); itr2 != m_caster->GetInRangeSetEnd(); )
			{
				itr = itr2;
				itr2++;
				if( !((*itr)->IsPlayer()) || SafeUnitCast((*itr))->isAlive() == true )
					continue;
				Player *pt = SafePlayerCast((*itr));
				pt->SetMovement(MOVE_UNROOT);
				pt->ResurrectPlayer();
				pt->SetUInt32Value(UNIT_FIELD_HEALTH, pt->GetUInt32Value(UNIT_FIELD_MAXHEALTH) );
			}
			m_caster->ReleaseInrangeLock();
		}break;
		case 64323: //Book of Glyph Mastery
			{
				if( p_caster )
				{
					p_caster->addSpell( 64276, 1 );
					p_caster->addSpell( 64256, 1 );
					p_caster->addSpell( 64277, 1 );
					p_caster->addSpell( 64268, 1 );
					p_caster->addSpell( 64295, 1 );
					p_caster->addSpell( 64294, 1 );
					p_caster->addSpell( 64271, 1 );
					p_caster->addSpell( 64303, 1 );
					p_caster->addSpell( 64297, 1 );
					p_caster->addSpell( 64274, 1 );
					p_caster->addSpell( 64317, 1 );
					p_caster->addSpell( 64280, 1 );
					p_caster->addSpell( 64305, 1 );
					p_caster->addSpell( 64279, 1 );
					p_caster->addSpell( 64312, 1 );
					p_caster->addSpell( 64273, 1 );
					p_caster->addSpell( 64253, 1 );
					p_caster->addSpell( 64315, 1 );
					p_caster->addSpell( 64288, 1 );
					p_caster->addSpell( 64281, 1 );
					p_caster->addSpell( 64278, 1 );
					p_caster->addSpell( 64291, 1 );
					p_caster->addSpell( 64316, 1 );
					p_caster->addSpell( 64254, 1 );
					p_caster->addSpell( 64300, 1 );
					p_caster->addSpell( 64284, 1 );
					p_caster->addSpell( 64298, 1 );
					p_caster->addSpell( 64283, 1 );
					p_caster->addSpell( 64257, 1 );
					p_caster->addSpell( 64304, 1 );
					p_caster->addSpell( 64285, 1 );
					p_caster->addSpell( 64248, 1 );
					p_caster->addSpell( 64275, 1 );
					p_caster->addSpell( 64318, 1 );
					p_caster->addSpell( 64309, 1 );
					p_caster->addSpell( 64314, 1 );
					p_caster->addSpell( 64313, 1 );
					p_caster->addSpell( 64282, 1 );
					p_caster->addSpell( 64246, 1 );
					p_caster->addSpell( 64289, 1 );
					p_caster->addSpell( 64251, 1 );
					p_caster->addSpell( 64307, 1 );
					p_caster->addSpell( 64249, 1 );
					p_caster->addSpell( 64286, 1 );
					p_caster->addSpell( 64311, 1 );
					p_caster->addSpell( 64252, 1 );
					p_caster->addSpell( 64308, 1 );
					p_caster->addSpell( 64296, 1 );
					p_caster->addSpell( 64250, 1 );
					p_caster->addSpell( 64302, 1 );
					p_caster->addSpell( 64247, 1 );
					p_caster->addSpell( 65245, 1 );
					p_caster->addSpell( 64287, 1 );
					p_caster->addSpell( 64310, 1 );
					p_caster->addSpell( 64299, 1 );
					p_caster->addSpell( 64255, 1 );
					p_caster->addSpell( 64270, 1 );
					p_caster->addSpell( 64296, 1 );
				}
			}break;
	/*****************************************
	 *	Class Spells
	 *****************************************/	
		case 59566: //Earthen Power
		{
			if( unitTarget )
			{
				for(uint32 x=MAX_POSITIVE_AURAS;x<unitTarget->m_auras_neg_size;x++)
					if( unitTarget->m_auras[x] && unitTarget->m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ENSNARED )
						unitTarget->m_auras[x]->Remove();
			}
		}break;
		case 8146: //Tremor Totem
		{
			if( unitTarget )
			{
//				for(uint32 x=MAX_POSITIVE_AURAS;x<unitTarget->m_auras_neg_size;x++)
				//some charm effects get to be positiv. We need to remove those too
				for(uint32 x=0;x<unitTarget->m_auras_neg_size;x++)
					if( unitTarget->m_auras[x] && 
						( unitTarget->m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_CHARMED 
						|| unitTarget->m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ASLEEP 
						|| unitTarget->m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_FLEEING 
						)
						)
					{ 
							unitTarget->m_auras[x]->Remove();
					}
			}
		}break;
		case 64981: //Summon Random Vanquished Tentacle
		{
			//summon one of these tentacles
			uint32 tentaclespells[3]={64982,64984,64983};
            SpellCastTargets targets( m_caster->GetGUID() );
			SpellEntry *spellInfo = dbcSpell.LookupEntry( tentaclespells[ RandomUInt() % 3 ] );
			if (spellInfo)
			{
				Spell *spell = SpellPool.PooledNew();
				spell->Init( m_caster, spellInfo ,true, NULL);
				spell->prepare(&targets);
			}
		}break;
		case 47948: //Pain and Suffering
		{
			// refresh the Shadow Word: pain ticks on target
			if( unitTarget )
			{
				Aura *taur = unitTarget->FindAuraByNameHash( SPELL_HASH_SHADOW_WORD__PAIN, m_caster->GetGUID() );
				if( taur )
				{
					taur->ResetTimeLeft();
					sEventMgr.ModifyEventTimeLeft(taur, EVENT_AURA_REMOVE, taur->GetDuration());
					unitTarget->ModVisualAuraStackCount(taur, 0);
					sEventMgr.ModifyEventTimeLeft(taur, EVENT_AURA_PERIODIC_DAMAGE, taur->GetDuration());
				}
			}
		}break;
		case 46584: //Raise Dead
		{
			if(p_caster	!= NULL)
			{
				float x = p_caster->GetPositionX()+rand()%25;
				float y = p_caster->GetPositionY()+rand()%25;
				float z = p_caster->GetPositionZ();
				//let's try to find a nearby humanoid corpse target


				CreatureInfo * ci = CreatureNameStorage.LookupEntry(26125);
				CreatureProto * cp = CreatureProtoStorage.LookupEntry(26125);
				if( !ci || !cp )
					return;
					
				LocationVector *vec = new LocationVector(x,y,z);
				Pet *summon = objmgr.CreatePet(26125,p_caster->GeneratePetNumber() );
				summon->SetPower( POWER_TYPE_ENERGY, (uint32)100 );
				summon->SetUInt32Value( UNIT_FIELD_POWER4, (uint32)100 );
				if(p_caster->HasSpell(52143))
				{	
					summon->CreateAsSummon(26125, ci, NULL, p_caster, GetProto(), 6, 0, vec); // considered pet
					summon->AddSpell(dbcSpell.LookupEntry(47481), true); // Gnaw
					summon->AddSpell(dbcSpell.LookupEntry(47482), true); // Leap 
					summon->AddSpell(dbcSpell.LookupEntry(47484), true); // Huddle
					summon->AddSpell(dbcSpell.LookupEntry(47468), true); // Claw
				}
				else
					summon->CreateAsSummon(26125, ci, NULL, p_caster, GetProto(), 6, 120000, vec); // 2 min duration
					
				summon->CastSpell(summon,50142,true);
				delete vec;
				vec = NULL;
			}
		}break;
	case 49560:	//DK : death grip -> pulls target close to DK
		{
			if( !u_caster || !unitTarget || unitTarget == u_caster )
				break; //no conditions to make do our stuff

			float distt = sqrt( unitTarget->GetDistance2dSq( u_caster ) );

			if( distt + 2.0f <= unitTarget->GetModelHalfSize() )
				break;//he is close enough to us. Np need to pull

			float speed = 137.0f / 15.0f; //well this is just 1 example from blizz :p
			uint32 timetofly = (uint32)(distt * speed);
			float raise_mob_to_height = unitTarget->GetPositionZ() + distt * 250.f / 9.0f; //seems a lot 
//			float raise_mob_to_height = distt * 250.f / 9.0f; //seems a lot 
			float dist;
			if( unitTarget->GetModelHalfSize() > u_caster->GetModelHalfSize() )
				dist = unitTarget->GetModelHalfSize(); 
			else 
				dist = u_caster->GetModelHalfSize();
			float angle = (unitTarget->calcAngle(unitTarget->GetPositionX(), unitTarget->GetPositionY(), u_caster->GetPositionX(), m_caster->GetPositionY()) * float(M_PI) ) / 180.0f;
			angle += (float)(M_PI); // is it me or the fromula is putting mob behind me all the time ? 
//printf("!!!raise mob height is %f and angle is %f\n",raise_mob_to_height,angle);
			float x = u_caster->GetPositionX()+dist * cosf(angle);
			float y = u_caster->GetPositionY()+dist * sinf(angle);
			float z = u_caster->GetPositionZ()+2.0f;
			unitTarget->SetPosition(x,y,z,unitTarget->GetOrientation(), true );

			WorldPacket data(SMSG_MONSTER_MOVE, 60);
			data << unitTarget->GetNewGUID();
			data << uint8(0);
			data << unitTarget->GetPositionX() << unitTarget->GetPositionY() << unitTarget->GetPositionZ();
			data << getMSTime();
			data << uint8(0);
			data << (uint32)(MONSTER_MOVE_FLAG_RUN | MONSTER_MOVE_FLAG_ARC_JUMP); //make mob seem to jump into air and fall infront of us
			data << timetofly; 
			data << raise_mob_to_height; //not really sure about this one
			data << uint32( 0 );
			data << uint32(1);	  // 1 waypoint
			data << x << y << z;
			unitTarget->SendMessageToSet( &data, true );
			if( playerTarget )
			{
				playerTarget->SpeedCheatDelay( timetofly + 1000 );
				if( playerTarget->m_MountSpellId )
					playerTarget->RemoveAura(playerTarget->m_MountSpellId);
			}
		}break;
	/*************************
	 * MAGE SPELLS
	 *************************
	 * IDs:
	 *	11189 Frost Warding   -	RANK 1,		STATUS: DONE
	 *  28332 Frost Warding   -	RANK 2,		STATUS: DONE
	 *  11094 Molten Shields  -	RANK 1,		STATUS: DONE
	 *  13043 Molten Shields  -	RANK 2,		STATUS: DONE

	 *  --------------------------------------------
	 *************************/
	
	/*
		Frost Warding
		Increases the armor and resistances given by your Frost Armor and Ice Armor spells by X%.  In addition, gives your Frost Ward a X% chance to reflect Frost spells and effects while active.
		
		Effect #1	Apply Aura: Add % Modifier (8)

		Effect #2	Apply Aura: Dummy
		11189, 28332
	*/
	case 11189:
	case 28332:
		{
			if(!unitTarget)
				break;
			CommitPointerListNode<struct ReflectSpellSchool> *itr;
			unitTarget->m_reflectSpellSchool.BeginLoop();
			for(itr = unitTarget->m_reflectSpellSchool.begin(); itr != unitTarget->m_reflectSpellSchool.end();itr = itr->Next() )
				if(GetProto()->Id == itr->data->spellId)
					unitTarget->m_reflectSpellSchool.SafeRemove(itr,1);
			unitTarget->m_reflectSpellSchool.EndLoopAndCommit();

			ReflectSpellSchool *rss = new ReflectSpellSchool;
			rss->chance = GetProto()->procChance;
			rss->spellId = GetProto()->Id;
			rss->require_aura_hash = SPELL_HASH_FROST_WARD; 
			rss->school = SCHOOL_FROST;				

			unitTarget->m_reflectSpellSchool.push_front(rss);
		}break;
	/*
		Molten Shields	Rank 2
		Causes your Fire Ward to have a 20% chance to reflect Fire spells while active. In addition, your Molten Armor has a 100% chance to affect ranged and spell attacks.
		Effect #1	Apply Aura: Dummy
		11904,13043
	*/
	case 11904:
	case 13043:
		{
			if(!unitTarget)
				break;
			CommitPointerListNode<struct ReflectSpellSchool> *itr;
			unitTarget->m_reflectSpellSchool.BeginLoop();
			for(itr = unitTarget->m_reflectSpellSchool.begin(); itr != unitTarget->m_reflectSpellSchool.end();itr = itr->Next() )
				if(GetProto()->Id == itr->data->spellId)
					unitTarget->m_reflectSpellSchool.SafeRemove(itr,1);
			unitTarget->m_reflectSpellSchool.EndLoopAndCommit();
 
			ReflectSpellSchool *rss = new ReflectSpellSchool;
			rss->chance = GetProto()->EffectBasePoints[0];
			rss->spellId = GetProto()->Id;
			rss->require_aura_hash = SPELL_HASH_FIRE_WARD; 
			rss->school = SCHOOL_FIRE;		

			unitTarget->m_reflectSpellSchool.push_front(rss);
		}break;
	//heroic fury clear intercept cooldown
	case 60970:
		{
			if(p_caster && p_caster->HasSpell(20252))
				p_caster->ClearCooldownForSpell(20252);
			
		}break;

	/*************************
	 * ROGUE SPELLS
	 *************************
	 * IDs:
	 * 14185 Preparation		STATUS: DONE
	 *  --------------------------------------------
	 * 35729 Cloak of Shadows	STATUS: DONE
	 *  --------------------------------------------
	 *************************/

	case 5938: //shiv
	{
		if( p_caster == NULL || unitTarget == NULL )
			return;

		p_caster->CastSpell(unitTarget->GetGUID(),5940,true);

		if( p_caster->GetItemInterface() )
		{
			Item *it = p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
			if( it == NULL )
				return;
		
			EnchantmentInstance * ench = it->GetEnchantment( 1 ); // temp enchantment slot
			if(ench)
			{
				EnchantEntry* Entry = ench->Enchantment;
				for( uint32 c = 0; c < 3; c++ )
				{
					if( Entry->type[c] && Entry->spell[c] )
					{
						SpellEntry *sp = dbcSpell.LookupEntry( Entry->spell[c] );
						if( sp == NULL )
							return;
					
						if( sp->c_is_flags & SPELL_FLAG_IS_POISON )
						{
							p_caster->CastSpell(unitTarget->GetGUID(),Entry->spell[c], true);
						}
					}
				}
			}
		}

	} break;
	//Sword and Board
	case 50227:
		{
			if( !p_caster )
				return;

			uint32 ClearSpellId[8] = { 23922,23923,23924,23925,25258,30356,47487,47488 };

			for(i = 0; i < 8; ++i)
				if( p_caster->HasSpell( ClearSpellId[i] ) )
					p_caster->ClearCooldownForSpell( ClearSpellId[i] );
		}break;
	/*
		Preparation
		When activated, this ability immediately finishes the cooldown on your Evasion, Sprint, Vanish, Cold Blood, Shadowstep and Premeditation abilities.		
		
		Effect	Dummy
	*/
	case 14185:
		{
			if( !p_caster )
				return;

			uint32 ClearSpellId[11] =
			{
			5277,  /* Evasion - Rank 1 */
			26669, /* Evasion - Rank 2 */
			2983,  /* Sprint  - Rank 1 */
			8696,  /* Sprint  - Rank 2 */
			11305, /* Sprint  - Rank 3 */
			1856,  /* Vanish  - Rank 1 */
			1857,  /* Vanish  - Rank 2 */
			26889, /* Vanish  - Rank 3 */
			14177, /* Cold Blood       */
			14183, /* Premeditation    */
			36554  /* Shadowstep       */
			};

			for(i = 0; i < 11; ++i)
			{
				if( p_caster->HasSpell( ClearSpellId[i] ) )
					p_caster->ClearCooldownForSpell( ClearSpellId[i] );
			}
		}break;
	/*
		Cloak of Shadows
		Instantly removes all existing harmful spell effects and increases your chance to resist all spells by 90% for 5 sec.  Does not remove effects that prevent you from using Cloak of Shadows.
		
		Effect #1	Apply Aura: Mod Attacker Spell Hit Chance (126)
			Value: -90
		Effect #2	Trigger Spell
			Spell #35729 <--- THIS SPELL
	*/
	case 35729:
	case 31224:	//changed by zack since trigger spell is not present anymore
		{
			if( !unitTarget || !unitTarget->isAlive())
				return;

			Aura * pAura;
			for(uint32 i = MAX_POSITIVE_AURAS; i < MAX_NEGATIVE_AURAS1(unitTarget); ++i)
			{
				pAura = unitTarget->m_auras[i];
				if( pAura != NULL && !pAura->IsPassive() && !pAura->IsPositive() && !(pAura->GetSpellProto()->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY) 
					&& pAura->GetSpellProto()->School != 0	//bleed effects are fizical
					)
				{
					pAura->Remove();
				}
			}
		}break;

	/*************************
	 * PALADIN SPELLS
	 *************************
	 * IDs:
	 * 31789 Righteous Defense		STATUS: DONE
	 *  --------------------------------------------
	 * 18350 illumination			STATUS: DONE
	 *  --------------------------------------------
	 *************************/

	/*
		Righteous Defense
		Come to the defense of a friendly target, commanding up to 3 enemies attacking the target to attack the Paladin instead.
		
		Effect #1	Dummy
			Radius: 5 yards

		Effect #2	Trigger Spell
			Spell #31980
	*/
	case 31789:
		{
			//we will try to lure 3 enemies from our target
			if(!unitTarget || !u_caster)
				break;
			Unit *targets[3];
			int targets_got=0;
			for(std::set<Object*>::iterator itr = unitTarget->GetInRangeSetBegin(), i2; itr != unitTarget->GetInRangeSetEnd(); )
			{
				i2 = itr++;
				// don't add objects that are not units and that are dead
				if((*i2)->GetTypeId()!= TYPEID_UNIT || !((Unit*)(*i2))->isAlive())
					continue;
		        
				Creature *cr=SafeCreatureCast(*i2);
				if(cr->GetAIInterface()->GetNextTarget()==unitTarget)
					targets[targets_got++]=cr;
				if(targets_got==3)
					break;
			}
			for(int i=0;i<targets_got;i++)
			{
				//set threat to this target so we are the msot hated
				uint32 threat_to_him = targets[i]->GetAIInterface()->getThreatByPtr( unitTarget );
				uint32 threat_to_us = targets[i]->GetAIInterface()->getThreatByPtr(u_caster);
				int threat_dif = threat_to_him - threat_to_us;
				if(threat_dif>0)//should not happen
					targets[i]->GetAIInterface()->modThreatByPtr(u_caster,threat_dif);
				targets[i]->GetAIInterface()->AttackReaction(u_caster,1,0);
				targets[i]->GetAIInterface()->SetNextTarget(u_caster);
			}
		}break;
	/*
		Illumination
		After getting a critical effect from your Flash of Light, Holy Light, or Holy Shock heal spell, gives you a X% chance to gain mana equal to 60% of the base cost of the spell.
		
		Effect #1	Apply Aura: Proc Trigger Spell
			Proc chance: 20%
			Spell #18350 <-- THIS SPELL	
		Effect #2	Apply Aura: Override Class Scripts (2689)
			Value: 60
	*/
	case 18350:
		{
			switch( m_triggeredByAura==NULL ? pSpellId : m_triggeredByAura->GetSpellId() )
			{
			case 20210:
			case 20212:
			case 20213:
			case 20214:
			case 20215:
				{
					if(!p_caster) 
						return;
					SpellEntry * sp = p_caster->last_heal_spell ? p_caster->last_heal_spell : GetProto();
					p_caster->Energize( p_caster, 20272, 60 * u_caster->GetUInt32Value( UNIT_FIELD_BASE_MANA ) * sp->ManaCostPercentage / 10000, POWER_TYPE_MANA );
				}break;
			case 38443:
				{
					// Shaman - Skyshatter Regalia - Two Piece Bonus
					// it checks for earth, air, water, fire totems and triggers Totemic Mastery spell 38437.
					if(!p_caster) return;
					if(p_caster->m_TotemSlots[0] && p_caster->m_TotemSlots[1] && p_caster->m_TotemSlots[2] && p_caster->m_TotemSlots[3])
					{
						Aura *aur = AuraPool.PooledNew();
						aur->Init(dbcSpell.LookupEntry(38437), 5000, p_caster, p_caster);
						for( uint32 i=0; i<3; i++ ) 
							aur->AddMod( aur->GetSpellProto()->EffectApplyAuraName[i], aur->GetSpellProto()->EffectBasePoints[i]+1, aur->GetSpellProto()->EffectMiscValue[i], i );
						p_caster->AddAura(aur);
					}
				}break;
			default:
				return;
			}
		}break;
	/*************************
	 * PRIEST SPELLS
	 *************************
	 * IDs:
	 * 34433 Shadowfiend	STATUS: ToDo
	 *  --------------------------------------------
	 *************************/
	/*
		Creates a shadowy fiend to attack the target.  Caster receives mana when the Shadowfiend deals damage.  Lasts 15 sec.
		Effect #1	Summon (19668)
		Effect #2	Trigger Spell
					Spell #41967 <--- THIS SPELL
	*/
	/*case 41967:
		{
		}break;
	*/

	/*************************
	 * SHAMAN SPELLS
	 *************************
	 * IDs:
	 * NO SPELLS
	 *  --------------------------------------------
	 *************************/

	/*************************
	 * WARLOCK SPELLS
	 *************************
	 * IDs:
	 * 19028 Soul Link				STATUS: ToDo
	 *  --------------------------------------------
	 * 19028 soul link effect		STATUS: DONE
	 *  --------------------------------------------
	 *************************/

	/*
		Soul Link
		When active, 20% of all damage taken by the caster is taken by your Imp, Voidwalker, Succubus, Felhunter, Felguard, or enslaved demon instead.  That damage cannot be prevented.  In addition, both the demon and master will inflict 5% more damage.  Lasts as long as the demon is active and controlled.
		
		Effect	Dummy
	*/

//	case 19028:
//		{
//		}break;

	/*
		Soul Link - EFFECT
		20% of damage taken by master is split with demon. All damage increased by 5%.
	*/
	case 25228:
		{
			if(!u_caster || !u_caster->isAlive() || !unitTarget || !unitTarget->isAlive())
				return;
			uint32 pet_dmg = this->forced_basepoints[0]*20/100;
			if( pet_dmg )
			{
				unitTarget->ModUnsigned32Value(UNIT_FIELD_HEALTH,pet_dmg);
				unitTarget->DealDamage(u_caster,pet_dmg,0,0,25228,false);
			}
		}break;
	//Demonic Circle
	case 48020:
		{
			if( !p_caster )
				return;
		
			GameObject *DemonicCircle = p_caster->GetMapMgr()->GetGameObject( p_caster->m_ObjectSlots[0] );
			if( DemonicCircle )
			{
				if( DemonicCircle->GetDistance2dSq( p_caster ) <= 40*40 )
				{
					p_caster->SafeTeleport( DemonicCircle->GetMapId(), DemonicCircle->GetInstanceID(), DemonicCircle->GetPosition());
					p_caster->RemoveAllAurasByMechanic( MECHANIC_ENSNARED, 0xFFFF, false );
				}
				else
					SendCastResult(SPELL_FAILED_OUT_OF_RANGE);
			}
			else
				SendCastResult(SPELL_FAILED_BAD_TARGETS);
		}break;

	/*************************
		Non-Class spells
		- Done
	 *************************/
	/*
		Poultryizer
		Turns the target into a chicken for 15 sec.   Well, that is assuming the transmogrification polarity has not been reversed...
	*/
	case 30507:
		{
			if( !unitTarget || !unitTarget->isAlive())
				return;

			u_caster->CastSpell(unitTarget->GetGUID(),30501,true);
		}break;
	/*
		Six Demon Bag
		Blasts enemies in front of you with the power of wind, fire, all that kind of thing!
	*/
	case 14537:
		{
			if( !unitTarget || !unitTarget->isAlive())
				return;

			uint32 ClearSpellId[6] = { 8401,8408,930,118,1680,10159 };
			int min = 1;
			uint32 effect = min + int( ((6-min)+1) * rand() / (RAND_MAX + 1.0) );
			
			u_caster->CastSpell(unitTarget, ClearSpellId[effect] ,true);
		}break;

	case 30427: // Extract Gas
		{
			bool check = false;
			uint32 cloudtype = 0;
			Creature *creature = 0;

			if(!p_caster)
				return;

			for(Object::InRangeSet::iterator i = p_caster->GetInRangeSetBegin(); i != p_caster->GetInRangeSetEnd(); ++i)
			{
				if((*i)->GetTypeId() == TYPEID_UNIT)
				{
					creature=SafeCreatureCast((*i));
					cloudtype=creature->GetEntry();
					if(cloudtype == 24222 || cloudtype == 17408 || cloudtype == 17407 || cloudtype == 17378)
					{
						if(p_caster->GetDistance2dSq((*i)) < 400)
						{
							p_caster->SetSelection(creature->GetGUID());
							check = true;
							break;
						}
					}
				}
			}
			
			if(check)
			{
				uint32 item, count = 0;
				item = count = 3+(rand()%3);
			
				if (cloudtype==24222) item=22572;//-air
				if (cloudtype==17408) item=22576;//-mana
				if (cloudtype==17407) item=22577;//-shadow
				if (cloudtype==17378) item=22578;//-water

				Item *add = p_caster->GetItemInterface()->FindItemLessMax(item, count, false);
				if (!add)
				{
					ItemPrototype* proto = ItemPrototypeStorage.LookupEntry(item);
					SlotResult slotresult;

					slotresult = p_caster->GetItemInterface()->FindFreeInventorySlot(proto);
					if(!slotresult.Result)
					{
						p_caster->GetItemInterface()->BuildInventoryChangeError(NULL, NULL, INV_ERR_INVENTORY_FULL);
						return;
					}
					Item * it=objmgr.CreateItem(item,p_caster);  
					it->SetUInt32Value( ITEM_FIELD_STACK_COUNT, count);
					p_caster->GetItemInterface()->SafeAddItem(it,slotresult.ContainerSlot, slotresult.Slot);
					creature->Despawn(3500,creature->GetProto()->RespawnTime);
				}
				else
				{
					add->SetCount(add->GetUInt32Value(ITEM_FIELD_STACK_COUNT) + count);
					add->m_isDirty = true;
					creature->Despawn(3500,creature->GetProto()->RespawnTime);
				}
			}
		}break;

	//curse of agony(18230) = periodic damage increased in 
	//flag 2031678
/*	case 34120:
		{//steady shot
		if(unitTarget)
		if(unitTarget->IsDazed())
		{
//			u_caster->SpellNonMeleeDamageLog(unitTarget,spellId,damage,false);
			u_caster->SpellNonMeleeDamageLog(unitTarget,spellId,damage,pSpellId==0);
		}
		
		}break;*/
	case 1454://life tap
	case 1455:
	case 1456:
	case 11687:
	case 11688:
	case 11689:
	case 27222:
	case 57946:
		{//converts base+1 points of health into mana
		if(!p_caster || !playerTarget)
			return;

		uint32 spirit_pct = GetProto()->RankNumber * 100;
		if( spirit_pct > 300 ) 
			spirit_pct = 300;
		uint32 damage = ( ( ( GetProto()->EffectBasePoints[i] + 1 ) * ( 100 + playerTarget->m_lifetapbonus ) ) / 100 ) + spirit_pct * playerTarget->GetUInt32Value( UNIT_FIELD_SPIRIRT ) / 100;
		if( damage >= playerTarget->GetUInt32Value( UNIT_FIELD_HEALTH ) )
			damage = MAX((int32)playerTarget->GetUInt32Value( UNIT_FIELD_HEALTH ) - 5, 0 );
		if( damage == 0 )
			return;
		p_caster->DealDamage( playerTarget, damage, 0, 0, spellId );
		p_caster->Energize( playerTarget, spellId, damage, POWER_TYPE_MANA );
		}break;
	case 974:
	case 32593:
	case 32594:
		{
			if(!pSpellId) return;
			SpellEntry *spellInfo = dbcSpell.LookupEntry(pSpellId);
			if(!spellInfo) return;
			uint32 heal32 = CalculateEffect(i,u_caster);
			unitTarget=u_caster; // Should heal caster :p
			if(heal32)
				Heal(heal32);
		}break;
	case 28730: //Arcane Torrent (Mana)
		{
			// for each mana tap, gives you (2.17*level+9.136) mana
			if( !unitTarget || !p_caster) 
				return;

			if(!unitTarget->isAlive() || unitTarget->getClass()==WARRIOR || unitTarget->getClass() == ROGUE)
				return;

			uint32 count = 0;
			for(uint32 x = 0; x < MAX_NEGATIVE_AURAS1(unitTarget); ++x)
			{
				if(unitTarget->m_auras[x] && unitTarget->m_auras[x]->GetSpellId() == 28734)
				{
					unitTarget->m_auras[x]->Remove();
					++count;
				}
			}

			uint32 gain = (uint32)(count * (2.17*p_caster->getLevel()+9.136));
			p_caster->Energize( unitTarget, 28730, gain, POWER_TYPE_MANA );
		}break;
	case 39610://Mana Tide
		{
			if(unitTarget == NULL || unitTarget->IsDead() || unitTarget->getClass() == WARRIOR || unitTarget->getClass() == ROGUE)
 				return;
 			uint32 gain = (uint32) (unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1)*0.06);
			unitTarget->Energize( unitTarget, 16191, gain, POWER_TYPE_MANA );
		}break;
	case 20577:// Cannibalize
		{
			if(!p_caster)
				return;
			bool check = false;
			float rad = GetRadius(i);
			rad *= rad;
			for(Object::InRangeSet::iterator i = p_caster->GetInRangeSetBegin(); i != p_caster->GetInRangeSetEnd(); ++i)
			{
				if((*i)->GetTypeId() == TYPEID_UNIT)
				{
					if(SafeCreatureCast((*i))->getDeathState() == CORPSE)
					{
						CreatureInfo *cn = SafeCreatureCast((*i))->GetCreatureInfo();
							if(cn && (cn->Type == HUMANOID || cn->Type == UNDEAD) )
							{
								if(p_caster->GetDistance2dSq((*i)) < rad)
								{
									check = true;
									break;
								}
							}
						
					}
				}
			}
			
			if(check)
			{
				p_caster->cannibalize = true;
				p_caster->cannibalizeCount = 0;
				sEventMgr.AddEvent(p_caster, &Player::EventCannibalize, uint32(7),
					EVENT_CANNIBALIZE, 2000, 5,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
				p_caster->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_CANNIBALIZE);
			}
		}break;
	case 23074:// Arcanite Dragonling
	case 23075:// Mithril Mechanical Dragonling
	case 23076:// Mechanical Dragonling
	case 23133:// Gnomish Battle Chicken
		{
			uint32 spell_id;
			switch(GetProto()->Id)
			{
                case 23074: spell_id = 19804; break;
                case 23075: spell_id = 12749; break;
                case 23076: spell_id =  4073; break;
                case 23133: spell_id = 13166; break;
				default: 
					return;
			}
			u_caster->CastSpell(u_caster,spell_id,true);
		}break;
	case 23725:// Gift of Life
		{
			if(!playerTarget)
				break;

			SpellCastTargets tgt;
			tgt.m_unitTarget = playerTarget->GetGUID();
			SpellEntry * inf =dbcSpell.LookupEntry(23782);
			Spell * spe = SpellPool.PooledNew();
			spe->Init(u_caster,inf,true,NULL);
			spe->prepare(&tgt);

		}break;
	case 12975:// Last Stand
		{
			if(!playerTarget)
				break;
			SpellCastTargets tgt;
			tgt.m_unitTarget = playerTarget->GetGUID();
			SpellEntry * inf =dbcSpell.LookupEntry(12976);
			Spell * spe = SpellPool.PooledNew();
			spe->Init(u_caster,inf,true,NULL);
			spe->prepare(&tgt);
		}break;
	/*************************
		Non-Class spells
		- ToDo
	 *************************/
	case 6668:// Red Firework
		{
			// Shoots a firework into the air that bursts into a thousand red stars
		}break;
	case 8344:// Universal Remote
		{
			//FIXME:Allows control of a mechanical target for a short time.  It may not always work and may just root the machine or make it very very angry.  Gnomish engineering at its finest.
		}break;
	case 9976:// Polly Eats the E.C.A.C.
		{
			//FIXME: Don't know what this does
		}break;
	case 10137:// Fizzule's Whistle
		{
			//FIXME:Blow on the whistle to let Fizzule know you're an ally
			//This item comes after a finish of quest at venture co.
			//You must whistle this every time you reach there to make Fizzule
			//ally to you.
		}break;
	case 11540:// Blue Firework
		{
			//Shoots a firework into the air that bursts into a thousand blue stars
		}break;
	case 11541:// Green Firework
		{
			//Shoots a firework into the air that bursts into a thousand green stars
		}break;
	case 11542:// Red Streaks Firework
		{
			//Shoots a firework into the air that bursts into a thousand red streaks
		}break;
	case 11543:// Red, White and Blue Firework
		{
			//Shoots a firework into the air that bursts into red, white and blue stars
		}break;
	case 11544:// Yellow Rose Firework
		{
			//Shoots a firework into the air that bursts in a yellow pattern
		}break;
	case 12151:// Summon Atal'ai Skeleton
		{
			//8324	Atal'ai Skeleton

			//FIXME:Add here remove in time event
		}break;
	case 13006:// Shrink Ray
		{
			//FIXME:Schematic is learned from the gnomish engineering trainer. The gnomish/gobblin engineering decision is made when you are lvl40+ and your engineering is 200+. Interestingly, however, when this item fails to shrink the target, it can do a variety of things, such as...
			//-Make you bigger (attack power +250)
			//-Make you smaller (attack power -250)
			//-Make them bigger (same effect as above)
			//-Make your entire party bigger
			//-Make your entire party smaller
			//-Make every attacking enemy bigger
			//-Make ever attacking enemy smaller
			//Works to your advantage for the most part (about 70% of the time), but don't use in high-pressure situations, unless you're going to die if you don't. Could tip the scales the wrong way.
			//Search for spells of this


			//13004 - grow <- this one
			//13010 - shrink <-this one
			//
		}break;
	case 13180:// Gnomish Mind Control Cap
		{
			// FIXME:Take control of humanoid target by chance(it can be player)
		}break;
	case 13278:// Gnomish Death Ray
		{
			// FIXME:The devices charges over time using your life force and then directs a burst of energy at your opponent
			//Drops life			
		}break;
	case 13280:// Gnomish Death Ray
		{
			//FIXME: Drop life
		}break;
	case 17816:// Sharp Dresser
		{
			//Impress others with your fashion sense
		}break;
	case 21343:// Snowball
		{
		}break;
	case 23645:// Hourglass Sand
		{
			//Indeed used at the Chromo fight in BWL. Chromo has a stunning debuff, uncleansable, unless you have hourglass sand. This debuff will stun you every 4 seconds, for 4 seconds. It is resisted a lot though. Mage's and other casters usually have to do this fight with the debuff on, healers, tanks and hunters will get some to cure themselves from the debuff
		}break;
	case 24325:// Pagle's Point Cast - Create Mudskunk Lure
		{
			//FIXME:Load with 5 Zulian Mudskunks, and then cast from Pagle's Point in Zul'Gurub
		}
	case 24392:// Frosty Zap
		{
			//FIXME:Your Frostbolt spells have a 6% chance to restore 50 mana when cast.
			//damage == 50
		}break;
	case 25822:// Firecrackers
		{
			//FIXME:Find firecrackers
		}break;
	case 26373:// Lunar Invititation
		{
			//FIXME: Teleports the caster from within Greater Moonlight
		}break;
	case 26374:// Elune's Candle
		{
			//FIXME:Shoots a firework at target
		}break;
	case 26889:// Give Friendship Bracelet
		{
			//Give to a Heartbroken player to cheer them up
			//laugh emote
		}break;
	case 27662:// Throw Cupid's Dart
		{
			//FIXME:Shoot a player, and Kwee Q. Peddlefeet will find them! (Only works on players with no current critter pets.)
		}break;
	case 28414:// Call Ashbringer
		{
			//http://www.thottbot.com/?i=53974
		}break;
	case 28806:// Toss Fuel on Bonfire
		{
			//FIXME:Dont know what this dummy does
		}break;
	case 7669:// Bethor's Potion
		{
			// related to Hex of Ravenclaw,
			// its a dispell spell.
			//FIXME:Dont know whats the usage of this dummy
		}break;
	case 8283:// Snufflenose Command
		{
			//FIXME:Quest Blueleaf Tubers
			//For use on a Snufflenose Gopher
		}break;
	case 8913:// Sacred Cleansing
		{
			//FIXME:Removes the protective enchantments around Morbent Fel
			//Quest Morbent Fel
		}break;
	case 9962://Capture Treant
		{
			//Quest Treant Muisek 
		}break;
	case 10113:// Flare Gun's flare
		{
			//FIXME:Quest Deep Cover
			//1543 may need to cast this
			//2 flares and the /salute
		}break;
	case 10617:// Release Rageclaw
		{
			//Quest Druid of the Claw
			//Use on the fallen body of Rageclaw
		}break;
	case 11402:// Shay's Bell
		{
			//FIXME:Quest Wandering Shay
			//Ring to call Shay back to you
		}break;
	case 11548:// Summon Spider God
		{
			//FIXME:Quest Summoning Shadra  (Elite)
			//Use at the Shadra'Alor Altar to summon the spider god
		}break;
	case 11610:// Gammerita Turtle Camera
		{
			//Quest The Super Snapper FX 
		}break;
	case 11886:// Capture Wildkin
		{
			//Quest Testing the Vessel
			//Shrink and Capture a Fallen Wildkin
		}break;
	case 11887:// Capture Hippogryph
		{
			//FIXME:Same with 11888
			//Quest Hippogryph Muisek 
		}break;
	case 11888:// Capture Faerie Dragon
		{
			//FIXME:Check Faerie Dragon Muisek is killed or not if its killed update quest
			//And allow create of fearie Dragon which is effect 1
			//Quest: Faerie Dragon Muisek
		}break;
	case 11889:// Capture Mountain Giant
		{
			//FIXME:Same with 11888
			//Quest: Mountain Giant Muisek
		}break;
	case 12189:// Summon Echeyakee
		{
			//3475	Echeyakee

			//FIXME:Quest Echeyakee
		}break;
	case 12283:// Xiggs Signal Flare
		{
			//Quest Signal for Pickup
			//To be used at the makeshift helipad in Azshara. It will summon Pilot Xiggs Fuselighter to pick up the tablet rubbings
		}break;
	case 12938:// Fel Curse
		{
			//FIXME:Makes near target killable(servants of Razelikh the Defiler)
		}break;
	case 14247:// Blazerunner Dispel
		{
			//FIXME:Quest Aquementas and some more
		}break;
	case 14250:// Capture Grark
		{
			//Quest Precarious Predicament
		}break;
	case 14813:// Rocknot's Ale
		{
			//you throw the mug
			//and the guy gets pissed well everyone gets pissed and he crushes the door so you can get past
			//maybe after like 30 seconds so you can get past.  but lke I said I have never done it myself 
			//so i am not 100% sure what happens.
		}break;
	case 15991://Revive Ringo
		{
			//Quest A Little Help From My Friends 
			//Revive Ringo with water
		}break;
	case 15998:// Capture Worg Pup
		{
			//FIXME:Ends Kibler's Exotic Pets  (Dungeon) quest
		}break;
	case 16031:// Releasing Corrupt Ooze
		{
			//FIXME:Released ooze moves to master ooze and "Merged Ooze Sample"
			//occurs after some time.This item helps to finish quest
		}break;
	case 16378:// Temperature Reading
		{
			//FIXME:Quest Finding the Source
			//Take a reading of the temperature at a hot spot.
		}break;
	case 17166:// Release Umi's Yeti
		{
			//Quest Are We There, Yeti?
			//Select Umi's friend and click to release the Mechanical Yeti
		}break;
	case 17271:// Test Fetid Skull
		{
			//FIXME:Marauders of Darrowshire
			//Wave over a Fetid skull to test its resonance
		}break;
	case 18153:// Kodo Kombobulator
		{
			//FIXME:Kodo Roundup Quest
			//Kodo Kombobulator on any Ancient, Aged, or Dying Kodo to lure the Kodo to follow (one at a time)
		}break;
	case 19250:// Placing Smokey's Explosives
		{
			//This is something related to quest i think
		}break;
	case 19512:// Apply Salve
		{
			//FIXME:Cure a sickly animal afflicted by the taint of poisoning
		}break;
	case 20804:// Triage 
		{
			//Quest Triage
			//Use on Injured, Badly Injured, and Critically Injured Soldiers
		}break;
	case 21050:// Melodious Rapture
		{
			//Quest Deeprun Rat Roundup 
		}break;
	case 21332:// Aspect of Neptulon
		{
			//FIXME:Used on plagued water elementals in Eastern Plaguelands
			//Quest:Poisoned Water
		}break;
	case 21960:// Manifest Spirit
		{
			//FIXME:Forces the spirits of the first centaur Kahns to manifest in the physical world
			//thats a quest
			//its for maraudon i think
			//u use that on the spirit mobs
			//to release them
		}break;
	case 23359:// Transmogrify!
		{
			//Quest Zapped Giants 
			//Zap a Feralas giant into a more manageable form
		}break;
	case 27184:// Summon Mor Grayhoof
		{
			//16044	Mor Grayhoof Trigger
			//16080	Mor Grayhoof

			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;
	case 27190:// Summon Isalien
		{
			//16045	Isalien Trigger
			//16097	Isalien

			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;
	case 27191:// Summon the remains of Jarien and Sothos
		{
			/*
			16046	Jarien and Sothos Trigger
			16101	Jarien
			16103	Spirit of Jarien
			
			16102	Sothos
			16104	Spirit of Sothos
			*/

			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;
	case 27201:// Summon the spirit of Kormok
		{
			/*16047	Kormok Trigger
			16118	Kormok
			*/
			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;
	case 27202:// Summon Lord Valthalak
		{
			/*
			16042	Lord Valthalak
			16048	Lord Valthalak Trigger
			16073	Spirit of Lord Valthalak

			*/
			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;
	case 27203:// Summon the spirits of the dead at haunted locations
		{
			//Related to quests The Left Piece of Lord Valthalak's Amulet  (Dungeon)
			//and The Right Piece of Lord Valthalak's Amulet  (Dungeon)
		}break;
	case 27517:// Use this banner at the Arena in Blackrock Depths to challenge Theldren
		{
			//This is used to make Theldren spawn at the place where it used
			//I couldnt find theldrin, and his men in creature names database
			//Someone has to write this and this is related to The Challange quest
			/*By moving to the center grate, you trigger the arena event. 
			A random group of mobs (spiders, worms, bats, raptors) spawns, 
			and you have to kill them. After the last one dies, and a small 
			break, a boss mob spawns. Successfully completing this event 
			turns the arena spectators from red to yellow*/
		}break;
	case 29858: //Soulshatter
		{
			if( !u_caster || !u_caster->isAlive() || !unitTarget || !unitTarget->isAlive() )
				return;

			u_caster->CastSpell(unitTarget, 32835, false);
		}break;
	}										 
}

void Spell::SpellEffectTeleportUnits( uint32 i )  // Teleport Units
{
	uint32 spellId = GetProto()->Id;

	if( unitTarget == NULL )
	{ 
		return;
	}

	// Try a dummy SpellHandler
	if( sScriptMgr.CallScriptedDummySpell( spellId, i, this ) )
	{ 
		return;
	}

	// Shadowstep
	if( ( GetProto()->NameHash == SPELL_HASH_SHADOWSTEP || GetProto()->NameHash == SPELL_HASH_KILLING_SPREE 
		|| GetProto()->NameHash == SPELL_HASH_FERAL_CHARGE___CAT )
		&& p_caster && p_caster->IsInWorld() )
	{
		// this is rather tricky actually. we have to calculate the orientation of the creature/player, and then calculate a little bit of distance behind that. */
		float ang;

		if( unitTarget == m_caster )
		{
			/* try to get a selection */
 			unitTarget = m_caster->GetMapMgr()->GetUnit(p_caster->GetSelection());
			if( (unitTarget == NULL ) || !isAttackable(p_caster, unitTarget, !(GetProto()->c_is_flags & SPELL_FLAG_IS_TARGETINGSTEALTHED) ) || (unitTarget->CalcDistance(p_caster) > 28.0f))
			{ 
				return;
			}
		}

		if( unitTarget->GetTypeId() == TYPEID_UNIT )
		{
			if( unitTarget->GetUInt64Value( UNIT_FIELD_TARGET ) != 0 )
			{
				// We're chasing a target. We have to calculate the angle to this target, this is our orientation.
				ang = m_caster->calcAngle(m_caster->GetPositionX(), m_caster->GetPositionY(), unitTarget->GetPositionX(), unitTarget->GetPositionY());

				// convert degree angle to radians 
				ang = ang * float(M_PI) / 180.0f;
			}
			else
			{
				// Our orientation has already been set.
				ang = unitTarget->GetOrientation();
			}
		}
		else
		{
			// Players orientation is sent in movement packets
			ang = unitTarget->GetOrientation();
		}

		// avoid teleporting into the model on scaled models
		const static float shadowstep_distance = 1.6f * unitTarget->GetFloatValue(OBJECT_FIELD_SCALE_X);
		float new_x = unitTarget->GetPositionX() - (shadowstep_distance * cosf(ang));
		float new_y = unitTarget->GetPositionY() - (shadowstep_distance * sinf(ang));
		
		/* Send a movement packet to "charge" at this target. Similar to warrior charge. */
		p_caster->z_axisposition = 0.0f;
		p_caster->SafeTeleport(p_caster->GetMapId(), p_caster->GetInstanceID(), LocationVector(new_x, new_y, (unitTarget->GetPositionZ() + 0.3f), unitTarget->GetOrientation()));
		
		return;
	}

	/* TODO: Remove Player From bg */

	if(unitTarget->GetTypeId() == TYPEID_PLAYER)
		HandleTeleport(spellId, unitTarget);
}

void Spell::SpellEffectApplyAura(uint32 i)  // Apply Aura
{
	if(!unitTarget)
	{ 
		return;
	}
	// can't apply stuns/fear/polymorph/root etc on boss
	if ( !playerTarget )
	{
		if (u_caster && (u_caster != unitTarget))
		{
			Creature * c = SafeCreatureCast( unitTarget );
			if (c)
			{

				/*
				Charm (Mind Control, enslave demon): 1
				Confuse (Blind etc): 2
				Fear: 4
				Root: 8
				Silence : 16
				Stun: 32
				Sheep: 64
				Banish: 128
				Sap: 256
				Frozen : 512
				Ensnared 1024
				Sleep 2048
				Taunt (aura): 4096
				Decrease Speed (Hamstring) (aura): 8192
				Spell Haste (Curse of Tongues) (aura): 16384
				Interrupt Cast: 32768
				Mod Healing % (Mortal Strike) (aura): 65536
				Total Stats % (Vindication) (aura): 131072
				*/

				//Spells with Mechanic also add other ugly auras, but if the main aura is the effect --> immune to whole spell
				if (c->GetProto() && c->GetProto()->modImmunities)
				{
					bool immune = false;
					if (m_spellInfo->MechanicsType)
					{
						switch(m_spellInfo->MechanicsType)
						{
						case MECHANIC_CHARMED:
							if (c->GetProto()->modImmunities & 1)
								immune = true;
							break;
						case MECHANIC_DISORIENTED:
							if (c->GetProto()->modImmunities & 2)
								immune = true;
							break;
						case MECHANIC_FLEEING:
							if (c->GetProto()->modImmunities & 4)
								immune = true;
							break;
						case MECHANIC_ROOTED:
							if (c->GetProto()->modImmunities & 8)
								immune = true;
							break;
						case MECHANIC_SILENCED:
							if ( c->GetProto()->modImmunities & 16)
								immune = true;
							break;
						case MECHANIC_STUNNED:
							if (c->GetProto()->modImmunities & 32)
								immune = true;
							break;
						case MECHANIC_POLYMORPHED:
							if (c->GetProto()->modImmunities & 64)
								immune = true;
							break;
						case MECHANIC_BANISHED:
							if (c->GetProto()->modImmunities & 128)
								immune = true;
							break;
						case MECHANIC_SAPPED:
							if (c->GetProto()->modImmunities & 256)
								immune = true;
							break;
						case MECHANIC_FROZEN:
							if (c->GetProto()->modImmunities & 512)
								immune = true;
							break;
						case MECHANIC_ENSNARED:
							if (c->GetProto()->modImmunities & 1024)
								immune = true;
							break;
						case MECHANIC_ASLEEP:
							if (c->GetProto()->modImmunities & 2048)
								immune = true;
							break;
						}
					}
					if (!immune)
					{
						// Spells wich do more than just one thing (damage and the effect) dont have a mechanic and we should only cancel the aura to be placed
						switch (m_spellInfo->EffectApplyAuraName[i])
						{
						case SPELL_AURA_MOD_CONFUSE:
							if (c->GetProto()->modImmunities & 2)
								immune = true;
							break;
						case SPELL_AURA_MOD_FEAR:
							if (c->GetProto()->modImmunities & 4)
								immune = true;
							break;
						case SPELL_AURA_MOD_TAUNT:
							if (c->GetProto()->modImmunities & 4096)
								immune = true;
							break;
						case SPELL_AURA_MOD_STUN:
							if (c->GetProto()->modImmunities & 32)
								immune = true;
							break;
						case SPELL_AURA_MOD_SILENCE:
							if ((c->GetProto()->modImmunities & 32768) || (c->GetProto()->modImmunities & 16))
								immune = true;
							break;
						case SPELL_AURA_MOD_DECREASE_SPEED:
							if (c->GetProto()->modImmunities & 8192)
								immune = true;
							break;
						case SPELL_AURA_INCREASE_CASTING_TIME_PCT:
							if (c->GetProto()->modImmunities & 16384)
								immune = true;
							break;
						case SPELL_AURA_MOD_LANGUAGE: //hacky way to prefer that the COT icon is set to mob
							if (c->GetProto()->modImmunities & 16384)
								immune = true;
							break;
						case SPELL_AURA_MOD_HEALING_DONE_PERCENT:
							if (c->GetProto()->modImmunities & 65536)
								immune = true;
							break;
						case SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE:
							if (c->GetProto()->modImmunities & 131072)
								immune = true;
							break;
						}
					}
					if (immune)
					{ 
						return;
					}
				}
			}
		}
	}
	
	// avoid map corruption.
	if(unitTarget->GetInstanceID()!=m_caster->GetInstanceID())
	{ 
		return;
	}
	//aura immunity used only by magic shell atm
	if( unitTarget->AuraSchoolImmunityList[ GetProto()->School ] && isAttackable( m_caster, unitTarget ) )
	{
		return;
	}
	//check if we already have stronger aura
	Aura *pAura;

	std::map<uint32,Aura*>::iterator itr=unitTarget->tmpAura.find(GetProto()->Id);
	//if we do not make a check to see if the aura owner is the same as the caster then we will stack the 2 auras and they will not be visible client sided
	if(itr==unitTarget->tmpAura.end())
	{
		uint32 Duration = this->GetDuration();
		if( u_caster && GetProto()->EffectAmplitude[i] > 0 
//			&& (GetProto()->c_is_flags & (SPELL_FLAG_IS_HEALING|SPELL_FLAG_IS_DAMAGING)) -> spells like arcane missiles should also "expire" and cast more quickly
			)
		{
//			Duration += GetProto()->EffectAmplitude[i];	//frikkin hackfix to make periodic triggers do the last tick
			Duration = (uint32)(Duration * u_caster->GetSpellHasteDots());
		}
		
		// Handle diminishing returns, if it should be resisted, it'll make duration 0 here.
		if(!(GetProto()->Attributes & ATTRIBUTES_PASSIVE)) // Passive
		{
			::ApplyDiminishingReturnTimer(&Duration, unitTarget, GetProto());
			//would be cool to know if aura is negative before we apply it
			if( GetProto()->School != SCHOOL_NORMAL && isAttackable( m_caster, unitTarget ) == true )
				Duration = Duration * unitTarget->OffensiveMagicalDurationModPCT / 100;
		}

		if(!Duration)
		{
			//maybe add some resist messege to client here ?
			sLog.outDebug("Spell apply aura error : Spell %u - %s has no duration \n",GetProto()->Id,GetProto()->Name);
			return;
		}
		pAura=AuraPool.PooledNew();
		if(g_caster && g_caster->GetUInt32Value(OBJECT_FIELD_CREATED_BY) && g_caster->m_summoner)
			 pAura->Init(GetProto(), Duration, g_caster->m_summoner, unitTarget, i_caster);
		else
			pAura->Init(GetProto(), Duration, m_caster, unitTarget, i_caster);

		pAura->pSpellId = pSpellId; //this is required for triggered spells
		
		unitTarget->tmpAura[GetProto()->Id] = pAura;		
	}
	else
	{
		 pAura=itr->second;
	} 

	if( forced_miscvalues[i] )
		pAura->AddMod(GetProto()->EffectApplyAuraName[i],damage,forced_miscvalues[i],i);
	else
		pAura->AddMod(GetProto()->EffectApplyAuraName[i],damage,GetProto()->EffectMiscValue[i],i);

	switch(GetProto()->Id)
	{
	case 38177: // Blackwhelp Net
		{
			p_caster->CastSpell(unitTarget, 38178, true);
			if( unitTarget->IsCreature() )
				SafeCreatureCast(unitTarget)->Despawn(1000, 360000);
		} break;
	}

}

void Spell::SpellEffectPowerDrain(uint32 i)  // Power Drain
{
	if(!unitTarget || !unitTarget->isAlive())
	{ 
		return;
	}

	uint32 powerField = UNIT_FIELD_POWER1+GetProto()->EffectMiscValue[i];
	uint32 curPower = unitTarget->GetUInt32Value(powerField);
	if( powerField == UNIT_FIELD_POWER1 && unitTarget->IsPlayer() )
	{
		Player* mPlayer = SafePlayerCast( unitTarget );
		if( mPlayer->IsInFeralForm() )
		{ 
			return;
		}

		// Resilience - reduces the effect of mana drains by (CalcRating*2)%.
//		damage *= float2int32( 1 - ( ( SafePlayerCast(unitTarget)->CalcRating( PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE ) * 2 ) / 100.0f ) );
	}
	uint32 amt = damage + ( ( u_caster->GetDamageDoneMod( GetProto()->School ) * 80 ) / 100 );
	if(amt>curPower)
		amt=curPower;
	unitTarget->SetUInt32Value(powerField,curPower-amt);
	u_caster->Energize( u_caster, GetProto()->Id, amt, GetProto()->EffectMiscValue[i] );
}

void Spell::SpellEffectHealthLeech(uint32 i) // Health Leech
{
	if(!unitTarget || !unitTarget->isAlive())
	{ 
		return;
	}

	uint32 curHealth = unitTarget->GetUInt32Value(UNIT_FIELD_HEALTH);
	uint32 heal_amt = float2int32( damage * GetProto()->EffectConversionCoef[i] );
	if(heal_amt > curHealth)
	{
		heal_amt = curHealth;
	}
	m_caster->DealDamage(unitTarget, damage, 0, 0, GetProto()->Id);

	uint32 playerCurHealth = m_caster->GetUInt32Value(UNIT_FIELD_HEALTH);
	uint32 playerMaxHealth = m_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH);

	if(playerCurHealth + heal_amt > playerMaxHealth)
	{
		m_caster->SetUInt32Value(UNIT_FIELD_HEALTH, playerMaxHealth);
	}
	else
	{
		m_caster->SetUInt32Value(UNIT_FIELD_HEALTH, playerCurHealth + heal_amt);		   
	}
}

void Spell::SpellEffectHeal(uint32 i) // Heal
{
	{
		//yep, the usual special case. This one is shaman talent : Nature's guardian
		//health is below 30%, we have a mother spell to get value from
		switch (GetProto()->Id)
		{
		case 31616:
			{
				if(unitTarget && unitTarget->IsPlayer() && pSpellId && unitTarget->GetHealthPct()<30)
				{
					//check for that 10 second cooldown
					SpellEntry *spellInfo = dbcSpell.LookupEntry(pSpellId );
					if(spellInfo)
					{
						//heal value is receivad by the level of current active talent :s
						//maybe we should use CalculateEffect(uint32 i) to gain SM benefits
						int32 value = 0;
						int32 basePoints = spellInfo->EffectBasePoints[i]+1;//+(m_caster->getLevel()*basePointsPerLevel);
						int32 randomPoints = spellInfo->EffectDieSides[i];
						if(randomPoints <= 1)
							value = basePoints;
						else
							value = basePoints + rand() % randomPoints;
						//the value is in percent. Until now it's a fixed 10%
						Heal(unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH)*value/100,false, i);
					}
				}
			}break;
		case 34299: //Druid: Improved Leader of the PAck
			{
				if (!unitTarget->IsPlayer() || !unitTarget->isAlive())
					break;

				Player* mPlayer = SafePlayerCast( unitTarget );
				if( !mPlayer->IsInFeralForm() || (
					mPlayer->GetShapeShift() != FORM_CAT &&
					mPlayer->GetShapeShift() != FORM_BEAR &&
					mPlayer->GetShapeShift() != FORM_DIREBEAR ) )
					break;
				uint32 max = mPlayer->GetUInt32Value( UNIT_FIELD_MAXHEALTH );
				uint32 val = float2int32( ( ( mPlayer->FindAura( 34300 ) ) ? 0.04f : 0.02f ) * max );
				if (val)
					mPlayer->Heal(mPlayer,34299,(uint32)(val));
			}break;
		case 22845: // Druid: Frenzied Regeneration
			{
				if (!unitTarget->IsPlayer() || !unitTarget->isAlive())
					break;
				Player* mPlayer = SafePlayerCast( unitTarget );
				if (!mPlayer->IsInFeralForm() || 
					(mPlayer->GetShapeShift() != FORM_BEAR &&
					mPlayer->GetShapeShift() != FORM_DIREBEAR))
					break;
				uint32 val = mPlayer->GetUInt32Value(UNIT_FIELD_POWER2);
				if (val>100)
					val = 100;
				mPlayer->SetUInt32Value(UNIT_FIELD_POWER2,mPlayer->GetUInt32Value(UNIT_FIELD_POWER2)-val);
				if (val)
				{
//					mPlayer->Heal(mPlayer,22845,uint32(val*3/100));
					//(val/10)*(0.3/100)
					if( ProcedOnSpell )
//						mPlayer->Heal(mPlayer,ProcedOnSpell->Id,uint32(mPlayer->GetUInt32Value(UNIT_FIELD_MAXHEALTH)*val*3/10000));
//						mPlayer->Heal(mPlayer,ProcedOnSpell->Id,uint32(mPlayer->GetUInt32Value(UNIT_FIELD_BASE_HEALTH)*val*3/10000));
						mPlayer->Heal(mPlayer,ProcedOnSpell->Id,uint32(mPlayer->GetUInt32Value(UNIT_FIELD_MAXHEALTH)*val*3/10000/2));	//hacks cause some druids got unkillable
					else
						mPlayer->Heal(mPlayer,22845,uint32(mPlayer->GetUInt32Value(UNIT_FIELD_MAXHEALTH)*val*3/10000/2));
//						mPlayer->Heal(mPlayer,22845,uint32(mPlayer->GetUInt32Value(UNIT_FIELD_BASE_HEALTH)*val*3/10000));
				}
			}break;
		case 18562: //druid - swiftmend
			{
				if( unitTarget )
				{
					uint32 ticks_for_insta_heal = 18000;
					//consume rejuvenetaion and regrowth
					Aura * taura = unitTarget->FindAuraByNameHash( SPELL_HASH_REGROWTH ); //Regrowth
					if( taura == NULL )
					{
						taura = unitTarget->FindAuraByNameHash( SPELL_HASH_REJUVENATION );//Rejuvenation
						ticks_for_insta_heal = 12000;
					}
					if( taura != NULL 
//						&& taura->m_modcount == 1 //should have 1 aura, else ...wtf ?
						)
					{
						Modifier *mod = &taura->m_modList[0];
						uint32 heal_ticks = mod->m_amount;
						uint32 bonus = u_caster->GetSpellHealBonus( unitTarget, taura->GetSpellProto(), heal_ticks, taura->GetSpellProto()->quick_tickcount );
						heal_ticks += bonus;

						uint32 new_dmg = heal_ticks * ticks_for_insta_heal / mod->fixed_amount[0];
						
						if( p_caster == NULL || p_caster->HasGlyphWithID( GLYPH_DRUID_SWIFTMEND ) == false )
							unitTarget->RemoveAura( taura );	//consume aura
						else
						{
							//should we set the aurastate here again ? Cause swiftmend eat it up
						}

						Heal((int32)new_dmg,false, i);
					}

				}
			}break;
			//Bloodthirst
			case 23880:
			{
				if(unitTarget)
					Heal(unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH)/100);
			}break;
			//Death pact
			case 48743:
			{
//				if(unitTarget && unitTarget->GetUInt64Value( UNIT_FIELD_CREATEDBY ) == u_caster->GetGUID() )
				if( p_caster && p_caster->GetSummon() )
				{
					Unit *ttarget = unitTarget;
					unitTarget = u_caster; //we always heal the caster
//					Heal(ttarget->GetUInt32Value(UNIT_FIELD_BASE_HEALTH)*damage/100);
					Heal(u_caster->GetUInt32Value(UNIT_FIELD_MAXHEALTH)*damage/100);
					unitTarget = ttarget;
					if( p_caster && p_caster->GetSummon() )
						p_caster->GetSummon()->Dismiss();
					else if( unitTarget->IsCreature() )
						SafeCreatureCast( unitTarget )->Despawn( 1, 0 );

				}
			}break;
		default:
			Heal((int32)damage,false, i);
			break;
		}
	}
	if(GetProto()->EffectChainTarget[i])//chain
	{
		int32 reduce_reduce = 0;	
		if((GetProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && u_caster)
			SM_FIValue(u_caster->SM_PJumpReduce,&reduce_reduce,GetProto()->SpellGroupType);
		chaincast_jump_pct_mod = float2int32( chaincast_jump_pct_mod * GetProto()->dmg_multiplier[i] ) + reduce_reduce;
	}
}

void Spell::SpellEffectQuestComplete(uint32 i) // Quest Complete
{
	if ( p_caster == NULL ) 
	{ 
		return;
	}
	QuestLogEntry * en = p_caster->GetQuestLogForEntry( GetProto()->EffectMiscValue[i] );
	if ( en != NULL && !en->CanBeFinished() )
	{
		en->HackComplete();
		en->SendQuestComplete();
	}
}

//wand->
void Spell::SpellEffectWeapondamageNoschool(uint32 i) // Weapon damage + (no School)
{
	if(!unitTarget ||!u_caster)
	{ 
		return;
	}

	//avoid dmg overflows
	if( damage < 0 || damage > 100000 )
	{ 
		return;
	}

	if( GetType() == SPELL_DMG_TYPE_RANGED && GetProto()->speed > 0.0f )
	{
		float time = (m_caster->CalcDistance(unitTarget) * 1000.0f) / GetProto()->speed;
		if(time <= 100.0f)
			u_caster->Strike( unitTarget, RANGED, GetProto(), 0, 0, 0, false, true );
		else
			sEventMgr.AddEvent(u_caster,&Unit::EventStrikeWithAbility,unitTarget->GetGUID(),
				GetProto(), (uint32)damage, EVENT_SPELL_DAMAGE_HIT, float2int32(time), 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
	else
		u_caster->Strike( unitTarget, ( GetType() == SPELL_DMG_TYPE_RANGED ? RANGED : MELEE ), GetProto(), damage, 0, 0, false, true );
}

void Spell::SpellEffectAddExtraAttacks(uint32 i) // Add Extra Attacks
{
	if(!u_caster)
	{ 
		return;
	}

	ExtraAttack *nea = new ExtraAttack;
	nea->sp = GetProto();
	nea->count = damage;
	//maybe set more details here ?

	u_caster->AddExtraAttack( nea );
}

void Spell::SpellEffectDodge(uint32 i)
{
	//i think this actually enbles the skill to be able to dodge melee+ranged attacks
	//value is static and sets value directly which will be modified by other factors
	//this is only basic value and will be overwiten elsewhere !!!
//	if(unitTarget->IsPlayer())
//		unitTarget->SetFloatValue(PLAYER_DODGE_PERCENTAGE,damage);
}

void Spell::SpellEffectParry(uint32 i)
{
	if(unitTarget)
		unitTarget->setcanperry(true);
}

void Spell::SpellEffectBlock(uint32 i)
{
	//i think this actually enbles the skill to be able to block melee+ranged attacks
	//value is static and sets value directly which will be modified by other factors
//	if(unitTarget->IsPlayer())
//		unitTarget->SetFloatValue(PLAYER_BLOCK_PERCENTAGE,damage);
}

void Spell::SpellEffectCreateItem(uint32 i) // Create item 
{
	if(!p_caster || unitTarget == NULL || unitTarget->IsPlayer() == false )
	{ 
		return;
	}

	Item* newItem;
	Item *add;
	uint8 slot;
	SlotResult slotresult;

	skilllinespell* skill = GetProto()->spell_skill;

	for(int j=0; j<3; j++) // now create the Items
	{
		ItemPrototype *m_itemProto;
		uint32 entry = GetProto()->EffectItemType[j];
		//Darkmoon Card of the North -> will create a card from one of the many, stats say you need to create around 90 cards to get 1 set
		if( entry == 44318 ) 
		{
			uint32 randomentry[]={44260,44261,44262,44263,44264,44265,44266,44267,44268,44269,44270,44271,44272,44273,44274,44275,44286,44287,44288,44289,44290,44291,44292,44293,44277,44278,44279,44280,44281,44282,44284,44285};
			uint32 randomentrycount = sizeof(randomentry) / sizeof(uint32);
			entry = randomentry[ RandomUInt() % randomentrycount ];
		}
		m_itemProto = ItemPrototypeStorage.LookupEntry( entry );
		if (!m_itemProto)
			continue;

		if(GetProto()->EffectItemType[j] == 0)
			continue;

		uint32 item_count = MAX(1,damage);

		// tailoring specializations get +1 cloth bonus
		switch(GetProto()->Id)
		{
		case 36686: //Shadowcloth
			if(p_caster->HasSpell(26801)) item_count += 1;
			break;
		case 26751: // Primal Mooncloth
			if(p_caster->HasSpell(26798)) item_count += 1;
			break;
		case 31373: //Spellcloth
			if(p_caster->HasSpell(26797)) item_count += 1;
			break;
		}

		// item count cannot be more than allowed in a single stack
		if (item_count > m_itemProto->MaxCount)
			item_count = m_itemProto->MaxCount;

		// item count cannot be more than item unique value
		if (m_itemProto->Unique && item_count > m_itemProto->Unique)
			item_count = m_itemProto->Unique;

		Player *pTarget = SafePlayerCast( unitTarget );	//we checked unittarget to be player on casting the spell

		if(pTarget->GetItemInterface()->CanReceiveItem(m_itemProto, item_count)) //reversed since it sends >1 as invalid and 0 as valid
		{
			SendCastResult(SPELL_FAILED_TOO_MANY_OF_ITEM);
			return;
		}

		slot = 0;
		add = pTarget->GetItemInterface()->FindItemLessMax(GetProto()->EffectItemType[j],item_count, false);
		if (!add)
		{
			slotresult = pTarget->GetItemInterface()->FindFreeInventorySlot(m_itemProto);
			if(!slotresult.Result)
			{
				  SendCastResult(SPELL_FAILED_TOO_MANY_OF_ITEM);
				  return;
			}
			
			newItem =objmgr.CreateItem(GetProto()->EffectItemType[i],pTarget);
			newItem->SetUInt64Value(ITEM_FIELD_CREATOR,m_caster->GetGUID());
			newItem->SetUInt32Value(ITEM_FIELD_STACK_COUNT, item_count);

			if (m_itemProto->RandomPropId)
			{
				RandomProps * iRandomProperty = lootmgr.GetRandomProperties(m_itemProto);
				if( iRandomProperty )
				{
					newItem->SetRandomProperty(iRandomProperty->ID);
					newItem->ApplyRandomProperties(false);
				}
			}
			if (m_itemProto->RandomSuffixId)
			{
				ItemRandomSuffixEntry * iRandomSuffix = lootmgr.GetRandomSuffix(m_itemProto);
				if( iRandomSuffix )
				{
					newItem->SetRandomSuffix(iRandomSuffix->id);
					newItem->ApplyRandomProperties(false);
				}
			}

			AddItemResult res = pTarget->GetItemInterface()->SafeAddItem(newItem,slotresult.ContainerSlot, slotresult.Slot);
			if( res == ADD_ITEM_RESULT_OK )
			{
				/*WorldPacket data(45);
				pTarget->GetSession()->BuildItemPushResult(&data, pTarget->GetGUID(), 1, item_count, GetProto()->EffectItemType[i] ,0,0xFF,1,0xFFFFFFFF);
				pTarget->SendMessageToSet(&data, true);*/
				pTarget->GetSession()->SendItemPushResult(newItem,true,false,true,true,slotresult.ContainerSlot,slotresult.Slot,item_count);
			} 
			else if( res == ADD_ITEM_RESULT_ERROR )
			{
				newItem->DeleteMe();
				newItem = NULL;
			}
		} 
		else 
		{
			//scale item_count down if total stack will be more than 20
			if(add->GetUInt32Value(ITEM_FIELD_STACK_COUNT) + item_count > m_itemProto->MaxCount )
			{
				uint32 item_count_filled;
				item_count_filled = m_itemProto->MaxCount - add->GetUInt32Value(ITEM_FIELD_STACK_COUNT);
				add->SetCount(m_itemProto->MaxCount);
				add->m_isDirty = true;

				slotresult = pTarget->GetItemInterface()->FindFreeInventorySlot(m_itemProto);
				if(!slotresult.Result)
					item_count = item_count_filled;
				else
				{
					newItem =objmgr.CreateItem(GetProto()->EffectItemType[i],pTarget);
					newItem->SetUInt64Value(ITEM_FIELD_CREATOR,m_caster->GetGUID());
					newItem->SetUInt32Value(ITEM_FIELD_STACK_COUNT, item_count - item_count_filled);
					if(pTarget->GetItemInterface()->SafeAddItem(newItem,slotresult.ContainerSlot, slotresult.Slot) == ADD_ITEM_RESULT_ERROR )
					{
						newItem->DeleteMe();
						newItem = NULL;
						item_count = item_count_filled;
					}
					else
						pTarget->GetSession()->SendItemPushResult(newItem, true, false, true, true, slotresult.ContainerSlot, slotresult.Slot, item_count);
                }
			}
			else
			{
				add->SetCount(add->GetUInt32Value(ITEM_FIELD_STACK_COUNT) + item_count);
				add->m_isDirty = true;
				pTarget->GetSession()->SendItemPushResult(add, true,false,true,false,pTarget->GetItemInterface()->GetBagSlotByGuid(add->GetGUID()),0xFFFFFFFF,item_count);
			}

			/*WorldPacket data(45);
			pTarget->GetSession()->BuildItemPushResult(&data, pTarget->GetGUID(), 1, item_count, GetProto()->EffectItemType[i] ,0,0xFF,1,0xFFFFFFFF);
			pTarget->SendMessageToSet(&data, true);*/
		}
		// skill up
		if ( skill != NULL )
			DetermineSkillUp( skill->skilline );
	}
	if ( skill != NULL )
	{
		// profession discoveries
		uint32 discovered_recipe = 0;
		std::set<ProfessionDiscovery*>::iterator itr = objmgr.ProfessionDiscoveryTable.begin();
		for ( ; itr != objmgr.ProfessionDiscoveryTable.end(); itr++ )
		{
			ProfessionDiscovery * pf = ( *itr );
			if ( pf != NULL && GetProto()->Id == pf->SpellId && p_caster->_GetSkillLineCurrent( skill->skilline ) >= pf->SkillValue && !p_caster->HasSpell( pf->SpellToDiscover ) && Rand( pf->Chance ) )
			{
				discovered_recipe = pf->SpellToDiscover;
				break;
			}
		}
		// if something discovered learn p_caster that recipe and broadcast message
		if ( discovered_recipe != 0 )
		{
			SpellEntry * se = dbcSpell.LookupEntry( discovered_recipe );
			if ( se != NULL )
			{
				p_caster->addSpell( discovered_recipe );
				p_caster->BroadcastMessage( "DISCOVERY! %s has discovered how to create %s",p_caster->GetName(), se->Name );
//				char msg[256];
//				sprintf( msg, "%sDISCOVERY! %s has discovered how to create %s.|r", MSG_COLOR_GOLD, p_caster->GetName(), se->Name );
//				WorldPacket * data;
//				data = sChatHandler.FillMessageData( CHAT_MSG_SYSTEM, LANG_UNIVERSAL,  msg, p_caster->GetGUID(), 0 );
//				p_caster->GetMapMgr()->SendChatMessageToCellPlayers( p_caster, data, 2, 1, LANG_UNIVERSAL, p_caster->GetSession() );
//				delete data;
//				data = NULL;
			}
		}
	}
}

void Spell::SpellEffectWeapon(uint32 i)
{
	if( playerTarget == NULL )
	{ 
		return;
	}

	uint32 skill = 0;
	uint32 spell = 0;

	switch( this->GetProto()->Id )
	{
	case 201:    // one-handed swords
		{
			skill = SKILL_SWORDS;
		}break;
	case 202:   // two-handed swords
		{
			skill = SKILL_2H_SWORDS;
		}break;
	case 203:   // Unarmed
		{
			skill = SKILL_UNARMED;
		}break;
	case 199:   // two-handed maces
		{
			skill = SKILL_2H_MACES;
		}break;
	case 198:   // one-handed maces
		{
			skill = SKILL_MACES;
		}break;
	case 197:   // two-handed axes
		{
			skill = SKILL_2H_AXES;
		}break;
	case 196:   // one-handed axes
		{
			skill = SKILL_AXES;
		}break;
	case 5011: // crossbows
		{
			skill = SKILL_CROSSBOWS;
			spell = SPELL_RANGED_GENERAL;
		}break;
	case 227:   // staves
		{
			skill = SKILL_STAVES;
		}break;
	case 1180:  // daggers
		{
			skill = SKILL_DAGGERS;
		}break;
	case 200:   // polearms
		{
			skill = SKILL_POLEARMS;
		}break;
	case 15590: // fist weapons
		{
			skill = SKILL_UNARMED;
		}break;
	case 264:   // bows
		{
			skill = SKILL_BOWS;
			spell = SPELL_RANGED_GENERAL;
		}break;
	case 266: // guns
		{
			skill = SKILL_GUNS;
			spell = SPELL_RANGED_GENERAL;
		}break;
	case 2567:  // thrown
		{
			skill = SKILL_THROWN;
		}break;
	case 5009:  // wands
		{
			skill = SKILL_WANDS;
//			spell = SPELL_RANGED_GENERAL;
			spell = SPELL_RANGED_WAND;
		}break;
	//case 3386:  // spears
	//	skill = 0;   // ??!!
	//	break;
	default:
		{
			skill = 0;
			sLog.outDebug("WARNING: Could not determine skill for spell id %d (SPELL_EFFECT_WEAPON)", this->GetProto()->Id);
		}break;
	}

	// Don't add skills to players logging in.
	/*if((GetProto()->Attributes & ATTRIBUTES_PASSIVE) && playerTarget->m_TeleportState == 1)
		return;*/

	if(skill)
	{
		if(spell)
			playerTarget->addSpell(spell);
		
		// if we do not have the skill line
		if(!playerTarget->_HasSkillLine(skill))
		{
			playerTarget->_AddSkillLine(skill, 1, playerTarget->getLevel()*5);
		}
		else // unhandled.... if we have the skill line
		{
		}
	}
}

void Spell::SpellEffectDefense(uint32 i)
{
	//i think this actually enbles the skill to be able to use defense
	//value is static and sets value directly which will be modified by other factors
	//this is only basic value and will be overwiten elsewhere !!!
//	if(unitTarget->IsPlayer())
//		unitTarget->SetFloatValue(UNIT_FIELD_RESISTANCES,damage);
}

void Spell::SpellEffectPersistentAA(uint32 i) // Persistent Area Aura
{
	if(m_AreaAura == true || !m_caster->IsInWorld())
	{ 
		return;
	}
	//create only 1 dyn object
	uint32 dur = GetDuration();
	float r = GetRadius(i);

	//Note: this code seems to be useless
	//this must be only source point or dest point
	//this AREA aura it's apllied on area
	//it can'be on unit or self or item or object
	//uncomment it if i'm wrong
	//We are thinking in general so it might be useful later DK
	
	// grep: this is a hack!
	// our shitty dynobj system doesnt support GO casters, so we gotta
	// kinda have 2 summoners for traps that apply AA.
	DynamicObject * dynObj = m_caster->GetMapMgr()->CreateDynamicObject();
	 
	if(g_caster && g_caster->m_summoner && !unitTarget)
	{
		Unit * caster = g_caster->m_summoner;
		dynObj->Create(caster, this, g_caster->GetPositionX(), g_caster->GetPositionY(), g_caster->GetPositionZ(), dur, r, damage );
		m_AreaAura = true;
		return;
	}
		
	switch(m_targets.m_targetMask)
	{		
	case TARGET_FLAG_SELF:
		{
			dynObj->Create(u_caster, this,	m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ(), dur,r, damage);		 
		}break;
	case TARGET_FLAG_UNIT:
		{
			if(!unitTarget||!unitTarget->isAlive())
				break;
			dynObj->Create( u_caster, this, unitTarget->GetPositionX(), unitTarget->GetPositionY(), unitTarget->GetPositionZ(),	dur, r, damage);
		}break;
	case TARGET_FLAG_OBJECT:
		{
			if(!unitTarget)
				break;
			if(!unitTarget->isAlive())
				break;
			dynObj->Create(u_caster, this, unitTarget->GetPositionX(), unitTarget->GetPositionY(), unitTarget->GetPositionZ(),dur, r, damage);
		}break;
	case TARGET_FLAG_SOURCE_LOCATION:
		{
			dynObj->SetInstanceID(m_caster->GetInstanceID());
			dynObj->Create(u_caster, this, m_targets.m_srcX,m_targets.m_srcY, m_targets.m_srcZ, dur,r, damage);
		}break;
	case TARGET_FLAG_DEST_LOCATION:
		{
			dynObj->SetInstanceID(m_caster->GetInstanceID());
			dynObj->Create(u_caster?u_caster:g_caster->m_summoner, this,m_targets.m_destX, m_targets.m_destY, m_targets.m_destZ,dur,r, damage);
		}break;
	default:
		return;
	}   
	
	if(u_caster && GetProto()->ChannelInterruptFlags > 0)
	{
		u_caster->SetUInt64Value(UNIT_FIELD_CHANNEL_OBJECT,dynObj->GetGUID());
		u_caster->SetUInt32Value(UNIT_CHANNEL_SPELL,GetProto()->Id);
	}
	m_AreaAura = true;	
}

void Spell::SpellEffectSummon(uint32 i) // Summon
{
	switch(m_spellInfo->EffectMiscValueB[i])
	{
		case 63:
		case 81:
		case 82:
		case 83:
		case 121:
			{
				SpellEffectSummonTotem(i);
				return;
			}
		case 41:
		case 407:
		case 1341:
		case 1841:
			{
				SpellEffectSummonCritter(i);
				return;
			}
		case 61:	//water elemental (depracated)
		case 881:
		case 669:
		case 208: //dancing blade is summon or just visual aura ?
		case 1161:
		case 1021: //mage mirror image
		case 1964: //force of nature
		case 1562: //force of nature
		case 2301: //snake trap
		case 713: //blood worms
			{
				SpellEffectSummonGuardian(i);
				return;
			}
		case 64:	//water elemental (depracated)
		case 1141:	//lightwell
			{
				SpellEffectSummonWild(i);
				return;
			}
		case 65:
		case 428:
			{
				SpellEffectSummonPossessed(i);
				return;
			}
		case 66:
			{
				SpellEffectSummonDemon(i);
				return;
			}
	}	

	if( !u_caster )
	{ 
		sLog.outDebug("Summoning non standard way is not allowed by mobs. Exiting\n");
		return;
	}

	/* This is for summon water elemenal, etc */
	CreatureInfo * ci = CreatureNameStorage.LookupEntry(GetProto()->EffectMiscValue[i]);
	CreatureProto * cp = CreatureProtoStorage.LookupEntry(GetProto()->EffectMiscValue[i]);
	if( !ci || !cp )
	{ 
		sLog.outDebug("Cannot summon mobs without existing proto %u\n",GetProto()->EffectMiscValue[i]);
		return;
	}

	if(GetProto()->EffectMiscValue[i] == 510 && p_caster)	// Water Elemental
	{
		Pet *summon = objmgr.CreatePet( GetProto()->EffectMiscValue[i],p_caster->GeneratePetNumber() );
		summon->SetInstanceID(u_caster->GetInstanceID());
		summon->CreateAsSummon(GetProto()->EffectMiscValue[i], ci, NULL, p_caster, GetProto(), 1,  GetDuration() );
		summon->SetUInt32Value(UNIT_FIELD_LEVEL, u_caster->getLevel());
		summon->AddSpell(dbcSpell.LookupEntryForced(31707), true);
		summon->AddSpell(dbcSpell.LookupEntryForced(33395), true);
		summon->SendSpellsToOwner(); // some said it does not have castbar
		summon->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, u_caster->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
		summon->_setFaction();

		u_caster->SetUInt64Value(UNIT_FIELD_SUMMON, summon->GetGUID());
	}
	else if(GetProto()->EffectMiscValue[i] == 19668 && p_caster)
	{
		Pet *summon = objmgr.CreatePet( GetProto()->EffectMiscValue[i],p_caster->GeneratePetNumber() );
		summon->SetInstanceID(u_caster->GetInstanceID());
		summon->CreateAsSummon(GetProto()->EffectMiscValue[i], ci, NULL, p_caster, GetProto(), 1,  GetDuration() );
		summon->SetUInt32Value(UNIT_FIELD_LEVEL, u_caster->getLevel());
		summon->AddSpell(dbcSpell.LookupEntryForced(63619), true);
		summon->SendSpellsToOwner(); // some said it does not have castbar
		summon->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, u_caster->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
		summon->_setFaction();

		u_caster->SetUInt64Value(UNIT_FIELD_SUMMON, summon->GetGUID());
	}
	else	//just for cases that we did not inspect before. Try to use scripts if possible
	{
		//only one summon at a time
		uint32 summon_duration = GetDuration();
		if( summon_duration < 2000 )
			summon_duration = 10000;	
		Unit *new_sum = u_caster->create_summon( m_spellInfo->EffectMiscValue[i], summon_duration );
	}
}

void Spell::SpellEffectLeap(uint32 i) // Leap
{
	float radius = GetRadius(i);

	// remove movement impeding auras
	u_caster->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN);

	if (sWorld.Collision) 
	{
		float ori = m_caster->GetOrientation();				
		float posX = m_caster->GetPositionX()+(radius*(cosf(ori)));
		float posY = m_caster->GetPositionY()+(radius*(sinf(ori)));
		float z = CollideInterface.GetHeight(m_caster->GetMapId(), posX, posY, m_caster->GetPositionZ() + 2.0f);
		if(z == NO_WMO_HEIGHT)		// not found height, or on adt
			z = m_caster->GetMapMgr()->GetLandHeight(posX,posY);

		if( fabs( z - m_caster->GetPositionZ() ) >= 10.0f )
		{ 
			return;
		}

		LocationVector dest(posX, posY, z + 2.0f, ori);
		LocationVector destest(posX, posY, dest.z, ori);
		LocationVector src(m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ() + 2.0f);

		if(CollideInterface.GetFirstPoint(m_caster->GetMapId(), src, destest, dest, -1.5f))
		{
			// hit an object new point is in dest.
			// is this necessary?
			dest.z = CollideInterface.GetHeight(m_caster->GetMapId(), dest.x, dest.y, dest.z + 2.0f);
		}
		else
			dest.z = z;

		dest.o = u_caster->GetOrientation();
		if(p_caster)
		{
			p_caster->blinked = true;
			p_caster->SafeTeleport( p_caster->GetMapId(), p_caster->GetInstanceID(), dest );
		}
		else
		{
			u_caster->SetPosition(dest, true);
		}
	} 
	else 
	{
		if(!p_caster) 
		{ 
			return;
		}

		WorldPacket data(SMSG_MOVE_KNOCK_BACK, 50);
		data << p_caster->GetNewGUID();
		data << getMSTime();
		data << cosf(p_caster->GetOrientation()) << sinf(p_caster->GetOrientation());
		data << radius;
		data << float(-10.0f);	//this is some height factor
		p_caster->GetSession()->SendPacket(&data);
		p_caster->SpeedCheatReset();	//should start sampling again after we land
		//m_caster->SendMessageToSet(&data, true);
	}
}

void Spell::SpellEffectEnergize(uint32 i) // Energize
{
	if(!unitTarget || !unitTarget->isAlive())
	{ 
		return;
	}

	uint32 modEnergy = 0;
	//yess there is always someone special : shamanistic rage - talent
	if(GetProto()->Id==30824)
		modEnergy = damage*GetUnitTarget()->GetAP()/100;
	//paladin - Spiritual Attunement 
	else if(GetProto()->Id==31786 && ProcedOnSpell)
	{
		SpellEntry *motherspell=dbcSpell.LookupEntry(pSpellId);
		if(motherspell)
		{
			//heal amount from procspell (we only proced on a heal spell)
			uint32 healamt=0;
			if(ProcedOnSpell->Effect[0]==SPELL_EFFECT_HEAL || ProcedOnSpell->Effect[0]==SPELL_EFFECT_SCRIPT_EFFECT)
				healamt=ProcedOnSpell->EffectBasePoints[0]+1;
			else if(ProcedOnSpell->Effect[1]==SPELL_EFFECT_HEAL || ProcedOnSpell->Effect[1]==SPELL_EFFECT_SCRIPT_EFFECT)
				healamt=ProcedOnSpell->EffectBasePoints[1]+1;
			else if(ProcedOnSpell->Effect[2]==SPELL_EFFECT_HEAL || ProcedOnSpell->Effect[2]==SPELL_EFFECT_SCRIPT_EFFECT)
				healamt=ProcedOnSpell->EffectBasePoints[2]+1;
			modEnergy = (motherspell->EffectBasePoints[0]+1)*(healamt)/100;
		}
	}
	else if (GetProto()->Id==2687)
	{
		modEnergy = damage;
		if( p_caster != NULL )
		{
			/*for(set<uint32>::iterator itr = p_caster->mSpells.begin(); itr != p_caster->mSpells.end(); ++itr)
			{
				if(*itr == 12818)
					modEnergy += 60;
				else if(*itr == 12301)
					modEnergy += 30;
			}*/
			if(p_caster->mSpells.find(12818) != p_caster->mSpells.end())
				modEnergy += 60;
			if(p_caster->mSpells.find(12301) != p_caster->mSpells.end())
				modEnergy += 30;
		}
	}
	else  
        modEnergy = damage;

	uint32 ID_for_the_logs;
	if( GetProto()->spell_id_client )
		ID_for_the_logs = GetProto()->spell_id_client;
	else
		ID_for_the_logs = GetProto()->Id;
	u_caster->Energize( unitTarget, ID_for_the_logs, modEnergy, GetProto()->EffectMiscValue[i] );
}

void Spell::SpellEffectEnergizeMaxEnergyPct(uint32 i)
{
	if(!unitTarget || !unitTarget->isAlive())
	{ 
		return;
	}

	if( GetProto()->EffectMiscValue[i] > 5 )
	{ 
		return;
	}

	uint32 maxEnergy = unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1 + GetProto()->EffectMiscValue[i]);
	u_caster->Energize( unitTarget, GetProto()->Id, maxEnergy * damage / 100, GetProto()->EffectMiscValue[i] );
}

void Spell::SpellEffectWeaponDmgPerc(uint32 i) // Weapon Percent damage
{
	if(!unitTarget  || !u_caster)
	{ 
		return;
	}

	if( GetType() == SPELL_DMG_TYPE_MAGIC )
	{
		dmg_storage_struct tdmg;
		float fdmg;
		CalculateDamage( u_caster, unitTarget, MELEE, 0, GetProto(), tdmg );
		int32 dmg_diff = tdmg.base_max - tdmg.base_min;
		dmg_diff = MAX( 1, dmg_diff );
		fdmg = (float)(tdmg.base_min + ( RandomUInt() % dmg_diff ));
		fdmg = (float)(fdmg * tdmg.pct_mod_add / 100);
		fdmg += (float)(tdmg.flat_mod_add);

		uint32 dmg = float2int32(fdmg*(float(damage/100.0f)));

		//avoid dmg overflows
		if( dmg < 0 || dmg > 100000 )
		{ 
			return;
		}

		u_caster->SpellNonMeleeDamageLog(unitTarget, GetProto()->Id, dmg, false, static_dmg[i] != 0, false);
	}
	else
	{
		uint32 _type;
		if( GetType() == SPELL_DMG_TYPE_RANGED )
			_type = RANGED;
		else
		{
			if (GetProto()->AttributesExC & 0x1000000)
				_type =  OFFHAND;
			else
				_type = MELEE;
		}

		//avoid dmg overflows
		if( damage < 0 || damage > 100000 || add_damage < 0 || add_damage > 100000 )
		{ 
			return;
		}

		if( GetProto()->NameHash == SPELL_HASH_SEAL_OF_BLOOD || GetProto()->NameHash == SPELL_HASH_SEAL_OF_THE_MARTYR )
			forced_basepoints[1] = damage * (GetProto()->EffectBasePoints[1] + 1 ) / 100;

		int32 add_pct_dmg = damage - 100; // !!! function parameter ads the dmg pct to normal dmg !!! 
		u_caster->Strike( unitTarget, _type, GetProto(), add_damage, add_pct_dmg, 0, false, true );
	}
}

void Spell::SpellEffectTriggerMissile(uint32 i) // Trigger Missile
{
	//Used by mortar team
	//Triggers area affect spell at destinatiom
	if(!m_caster)
	{ 
		return;
	}

	uint32 spellid = GetProto()->EffectTriggerSpell[i];
	if(spellid == 0)
	{ 
		return;
	}

	SpellEntry *spInfo = dbcSpell.LookupEntry(spellid);
	if(!spInfo)
	{ 
		return;
	}

	float spellRadius = GetRadius(i);

	for(std::set<Object*>::iterator itr = m_caster->GetInRangeSetBegin(); itr != m_caster->GetInRangeSetEnd(); itr++ )
	{
		if(!((*itr)->IsUnit()) || !SafeUnitCast((*itr))->isAlive())
			continue;
		Unit *t=SafeUnitCast(*itr);
	
		float r;
		float d=m_targets.m_destX-t->GetPositionX();
		r=d*d;
		d=m_targets.m_destY-t->GetPositionY();
		r+=d*d;
		d=m_targets.m_destZ-t->GetPositionZ();
		r+=d*d;
		if(sqrt(r)> spellRadius)
			continue;
		
		if(!isAttackable(m_caster, SafeUnitCast(*itr)))//Fixme only enemy targets?
			continue;

		Spell*sp=SpellPool.PooledNew();
		sp->Init(m_caster,spInfo,true,NULL);
		SpellCastTargets tgt;
		tgt.m_unitTarget=(*itr)->GetGUID();
		sp->prepare(&tgt);
	}
}

void Spell::SpellEffectOpenLock(uint32 i) // Open Lock
{
	if(!p_caster)
	{ 
		return;
	}
		
	uint8 loottype = 0;

	uint32 locktype=GetProto()->EffectMiscValue[i];
	switch(locktype)
	{
		case LOCKTYPE_DISARM_TRAP:
		{
			if(gameObjTarget && gameObjTarget->GetInfo()->Type == GAMEOBJECT_TYPE_TRAP )
				gameObjTarget->Despawn(0);
		}break;
		case LOCKTYPE_PICKLOCK:
		{
			uint32 v = 0;
			uint32 lockskill = p_caster->_GetSkillLineCurrent(SKILL_LOCKPICKING);

			if(itemTarget)
			{	
				if(!itemTarget->locked)
				{ 
				return;
				}
						
				Lock *lock = dbcLock.LookupEntry( itemTarget->GetProto()->LockId );
				if(!lock) 
				{ 
					return;
				}
				for(int i=0;i<5;i++)
					if(lock->locktype[i] == GO_LOCKTYPE_SKILL_REQ && lock->minlockskill[i] && lockskill >= lock->minlockskill[i])
					{
						v = lock->minlockskill[i];
						itemTarget->locked = false;
						itemTarget->SetFlag(ITEM_FIELD_FLAGS,4); // unlock
						DetermineSkillUp(SKILL_LOCKPICKING,v/5);
						break;
					}
			}
			else if(gameObjTarget)
			{
				GameObjectInfo *info = GameObjectNameStorage.LookupEntry(gameObjTarget->GetEntry());
				if(!info || gameObjTarget->GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE) == 0) 
				{ 
					return;
				}
				Lock *lock = dbcLock.LookupEntry( info->SpellFocus );
				if(lock == 0)
				{ 
					return;
				}

				for(int i=0;i<5;i++)
				{
					if(lock->locktype[i] == GO_LOCKTYPE_SKILL_REQ && lock->minlockskill[i] && lockskill >= lock->minlockskill[i])
					{
						v = lock->minlockskill[i];
						gameObjTarget->SetUInt32Value(GAMEOBJECT_FLAGS, 0);
						gameObjTarget->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 1);
						//Add Fill GO loot here
						if(gameObjTarget->loot.items.size() == 0)
						{
							//lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetEntry(), gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->iInstanceMode ? true : false) : false);
							// zack : blizz recycles gameobject entry. We use something that is same for all entry variations
							lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetInfo()->sound1, gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->instance_difficulty ? true : false) : false);
							DetermineSkillUp(SKILL_LOCKPICKING,v/5); //to prevent free skill up
						}
						loottype = LOOT_CORPSE;
						//End of it
						break;
					}
				}
			}
		}
		break;
		case LOCKTYPE_HERBALISM:
		{
			if(!gameObjTarget) 
			{ 
				return;	  
			}
			
			uint32 v = gameObjTarget->GetGOReqSkill();
			bool bAlreadyUsed = false;
		 
			if(Rand(100.0f)) // 3% chance to fail//why?
			{
				if( SafePlayerCast( m_caster )->_GetSkillLineCurrent( SKILL_HERBALISM ) < v )
				{
					//SendCastResult(SPELL_FAILED_LOW_CASTLEVEL);
					return;
				}
				else
				{
					if( gameObjTarget->loot.items.size() == 0 )
					{
//						lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetEntry(), gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->iInstanceMode ? true : false) : false);
						// zack : blizz recycles gameobject entry. We use something that is same for all entry variations
						lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetInfo()->sound1, gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->instance_difficulty) : 0);
					}
					else
						bAlreadyUsed = true;
				}
				loottype = LOOT_SKINNING;
			}
			else
			{
				/*
				if(rand()%100 <= 30)
				{
					//30% chance to not be able to reskin on fail
					((Creature*)unitTarget)->Skinned = true;
					WorldPacket *pkt=unitTarget->BuildFieldUpdatePacket(UNIT_FIELD_FLAGS,0);
					SafePlayerCast( m_caster )->GetSession()->SendPacket(pkt);
					delete pkt;

				}*/
				SendCastResult(SPELL_FAILED_TRY_AGAIN);
			}
			//Skill up
			if(!bAlreadyUsed) //Avoid cheats with opening/closing without taking the loot
				DetermineSkillUp(SKILL_HERBALISM,v/5); 
		}
		break;
		case LOCKTYPE_MINING:
		{
			if(!gameObjTarget) 
			{ 
				return;
			}

			uint32 v = gameObjTarget->GetGOReqSkill();
			bool bAlreadyUsed = false;

			if( Rand( 100.0f ) ) // 3% chance to fail//why?
			{
				if( SafePlayerCast( m_caster )->_GetSkillLineCurrent( SKILL_MINING ) < v )
				{
					//SendCastResult(SPELL_FAILED_LOW_CASTLEVEL);
					return;
				}
				else if( gameObjTarget->loot.items.size() == 0 )
				{
//					lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetEntry(), gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->iInstanceMode ? true : false) : false);
					// zack : blizz recycles gameobject entry. We use something that is same for all entry variations
					lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetInfo()->sound1, gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->instance_difficulty) : 0);
				}	
				else
					bAlreadyUsed = true;

				loottype = LOOT_SKINNING;
			}
			else
			{
				SendCastResult(SPELL_FAILED_TRY_AGAIN);
			}
			//Skill up
			if(!bAlreadyUsed) //Avoid cheats with opening/closing without taking the loot
				DetermineSkillUp(SKILL_MINING,v/5);
		}
		break;
		case LOCKTYPE_SLOW_OPEN: // used for BG go's
		{
			if(!gameObjTarget ) 
			{ 
				return;
			}
			if(p_caster && p_caster->m_bg)
				if(p_caster->m_bg->HookSlowLockOpen(gameObjTarget,p_caster,this))
				{ 
					return;
				}

			uint32 spellid = !gameObjTarget->GetInfo()->Unknown1 ? 23932 : gameObjTarget->GetInfo()->Unknown1;
			SpellEntry*en=dbcSpell.LookupEntry(spellid);
			Spell *sp=SpellPool.PooledNew();
			sp->Init(p_caster,en,true,NULL);
			SpellCastTargets tgt;
			tgt.m_unitTarget=gameObjTarget->GetGUID();
			sp->prepare(&tgt);
			return;
		}	
		break;
		case LOCKTYPE_QUICK_CLOSE:
			{
				if(!gameObjTarget ) 
				{ 
					return;
				}
				gameObjTarget->EventCloseDoor();
			}
		break;
		default://not profession
		{
			if(!gameObjTarget ) 
			{ 
				return;
			}

			if( gameObjTarget->GetByte( GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPEID ) == GAMEOBJECT_TYPE_GOOBER)
					CALL_GO_SCRIPT_EVENT(gameObjTarget, OnActivate)(SafePlayerCast(p_caster));
			CALL_INSTANCE_SCRIPT_EVENT( gameObjTarget->GetMapMgr(), OnGameObjectActivate )( gameObjTarget, p_caster ); 
			
			if(sQuestMgr.OnActivateQuestGiver(gameObjTarget, p_caster))
			{ 
				return;
			}

			if(sQuestMgr.OnGameObjectActivate(p_caster, gameObjTarget))
			{
				p_caster->UpdateNearbyGameObjects();
				return;
			}

			if(gameObjTarget->loot.items.size() == 0)
			{
				//lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetEntry(), gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->iInstanceMode ? true : false) : false);
				// zack : blizz recycles gameobject entry. We use something that is same for all entry variations
				lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetInfo()->sound1, gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->instance_difficulty) : 0);
			}
			loottype= LOOT_CORPSE ;
		}
		break;
	};
	if( gameObjTarget != NULL && gameObjTarget->GetByte( GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPEID ) == GAMEOBJECT_TYPE_CHEST)
		SafePlayerCast( m_caster )->SendLoot( gameObjTarget->GetGUID(), loottype );
}

void Spell::SpellEffectOpenLockItem(uint32 i)
{
	Unit* caster = u_caster;
	if(!caster && i_caster)
		caster = i_caster->GetOwner();

	if( p_caster != NULL && i_caster != NULL )
	{
		ItemPrototype *ip = i_caster->GetProto();
		if( ip == NULL )
			return;
		else
			p_caster->HandleSpellLoot( ip->ItemId );
	}

	if(!gameObjTarget || !gameObjTarget->IsInWorld()) 
	{ 
		return;
	}
	
	if( caster && caster->IsPlayer() && sQuestMgr.OnGameObjectActivate( (SafePlayerCast(caster)), gameObjTarget ) )
		SafePlayerCast(caster)->UpdateNearbyGameObjects();

	if( p_caster )
	{
		CALL_GO_SCRIPT_EVENT(gameObjTarget, OnActivate)(SafePlayerCast(caster));
		CALL_INSTANCE_SCRIPT_EVENT( gameObjTarget->GetMapMgr(), OnGameObjectActivate )( gameObjTarget, p_caster ); 
	}
	gameObjTarget->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 0);	

	if( gameObjTarget->GetEntry() == 183146)
	{
		gameObjTarget->Despawn(1);
		return;
	}

	if( gameObjTarget->GetByte( GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPEID ) == GAMEOBJECT_TYPE_CHEST)
	{
//		lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetEntry(), gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->iInstanceMode ? true : false) : false);
		// zack : blizz recycles gameobject entry. We use something that is same for all entry variations
		lootmgr.FillGOLoot(&gameObjTarget->loot,gameObjTarget->GetInfo()->sound1, gameObjTarget->GetMapMgr() ? (gameObjTarget->GetMapMgr()->instance_difficulty) : 0);
		if(gameObjTarget->loot.items.size() > 0)
		{
			SafePlayerCast(caster)->SendLoot(gameObjTarget->GetGUID(),LOOT_CORPSE);
		}
	}

	if( gameObjTarget->GetByte( GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPEID ) == GAMEOBJECT_TYPE_DOOR)
		gameObjTarget->SetUInt32Value(GAMEOBJECT_FLAGS, 33);

	if( IS_STATIC_MAP( gameObjTarget->GetMapMgr()->GetMapInfo() ) )//dont close doors for instances
		sEventMgr.AddEvent(gameObjTarget,&GameObject::EventCloseDoor, EVENT_GAMEOBJECT_DOOR_CLOSE,10000,1,0);
	
	sEventMgr.AddEvent(gameObjTarget, &GameObject::Despawn, (uint32)1, EVENT_GAMEOBJECT_ITEM_SPAWN, 6*60*1000, 1, 0);
}

void Spell::SpellEffectProficiency(uint32 i)
{
//	uint32 skill;
//	skilllinespell* skillability = dbcSkillLineSpell.LookupEntryForced( GetProto()->spell_skilline[0] );
//	if (skillability)
//		skill = skillability->skilline;
	if( GetProto()->spell_skilline_assoc_counter == 0 )
		sLog.outDebug("Spell Proficiency that has no skill to teach ! %u \n",GetProto()->Id);

	for(uint32 i=0;i<GetProto()->spell_skilline_assoc_counter;i++)
	{
		skilllineentry* sk = dbcSkillLine.LookupEntry( GetProto()->spell_skilline[i] );
		uint32 skill = sk->id;
		if(skill)
		{
			if(playerTarget)
			{
				//stop spamming ourself with self teach stuff in case of playercreate spells
	//			playerTarget->removeSpell( GetProto()->Id, false, false, 0 );
				if(playerTarget->_HasSkillLine(skill))
				{
					// Increase it by one
				   // playerTarget->AdvanceSkillLine(skill);
				}
				else
				{
					// Don't add skills to players logging in.
					/*if((GetProto()->Attributes & 64) && playerTarget->m_TeleportState == 1)
						return;*/

					if(sk && sk->type == SKILL_TYPE_WEAPON)
						playerTarget->_AddSkillLine(skill, 1, 5*playerTarget->getLevel());
					else
						playerTarget->_AddSkillLine(skill, 1, 1);				
				}
			}
		}
		else
			sLog.outDebug("Spell Proficiency that has no skill to teach ! %u \n",GetProto()->Id);
	}
}

void Spell::SpellEffectSendEvent(uint32 i) //Send Event
{
	//This is mostly used to trigger events on quests or some places

	uint32 spellId = GetProto()->Id;

	// Try a dummy SpellHandler
	if(sScriptMgr.CallScriptedDummySpell(spellId, i, this))
	{ 
		return;
	}

	switch(spellId)
	{

	// WSG Flags
	case 23333:
	case 23335:
		{
			if( !p_caster )
				return;
			/* set the flag holder */
			p_caster->m_bgHasFlag = true;

			if( p_caster->GetTeam() == 1 )
				p_caster->m_bg->SendChatMessage( CHAT_MSG_BG_EVENT_HORDE, p_caster->GetGUID(), "The Alliance flag was picked up by %s!", p_caster->GetName() );
			else
				p_caster->m_bg->SendChatMessage( CHAT_MSG_BG_EVENT_ALLIANCE, p_caster->GetGUID(), "The Horde flag was picked up by %s!", p_caster->GetName() );
		}break;

	// Place Loot
	case 25720: // Places the Bag of Gold at the designated Drop-Off Point.
		{

		}break;

	// Item - Cleansing Vial DND
	case 29297: // Empty the vial near the Bones of Aggonar to cleanse the waters of their demonic taint.
		{
			if( p_caster )
			{
				QuestLogEntry *en=p_caster->GetQuestLogForEntry(9427);
				if(!en)
				{ 
					return;
				}
				en->SendQuestComplete();
			}
		}break;

	//Warlock: Summon Succubus Quest
	case 8674:
	case 9223:
	case 9224:
		{
			if( !p_caster )
				return;
			CreatureInfo * ci = CreatureNameStorage.LookupEntry(5677);
			CreatureProto * cp = CreatureProtoStorage.LookupEntry(5677);
			if( !ci || !cp )
			{ 
				return;
			}

		   Creature * pCreature = p_caster->GetMapMgr()->CreateCreature(cp->Id);
		   pCreature->Load(cp, p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
		   pCreature->_setFaction();
		   pCreature->GetAIInterface()->Init(pCreature,AITYPE_AGRO,MOVEMENTTYPE_NONE);
		   pCreature->GetAIInterface()->taunt(p_caster,true);
		   pCreature->_setFaction();
//		   pCreature->m_noRespawn = true;
		   pCreature->PushToWorld(p_caster->GetMapMgr());
		   sEventMgr.AddEvent(pCreature, &Creature::SafeDelete, EVENT_CREATURE_REMOVE_CORPSE,60000, 1, 0);
		}break;

	//Warlock: Summon Voidwalker Quest
	case 30208:
	case 9221:
	case 9222:
	case 7728:
		{
			if( !p_caster )
				return;
			CreatureInfo * ci = CreatureNameStorage.LookupEntry(5676);
			CreatureProto * cp = CreatureProtoStorage.LookupEntry(5676);
			if( !ci || !cp )
			{ 
				return;
			}

		   Creature * pCreature = p_caster->GetMapMgr()->CreateCreature(cp->Id);
		   pCreature->Load(cp, p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
		   pCreature->_setFaction();
		   pCreature->GetAIInterface()->Init(pCreature,AITYPE_AGRO,MOVEMENTTYPE_NONE);
		   pCreature->GetAIInterface()->taunt(p_caster,true);
		   pCreature->_setFaction();
//		   pCreature->m_noRespawn = true;
		   pCreature->PushToWorld(p_caster->GetMapMgr());
		   sEventMgr.AddEvent(pCreature, &Creature::SafeDelete, EVENT_CREATURE_REMOVE_CORPSE,60000, 1, 0);
		}break;

	//Warlock: Summon Felhunter Quest
	case 8712:
		{
			if( !p_caster )
				return;
			CreatureInfo * ci = CreatureNameStorage.LookupEntry(6268);
			CreatureProto * cp = CreatureProtoStorage.LookupEntry(6268);
			if( !ci || !cp )
			{ 
				return;
			}

		   Creature * pCreature = p_caster->GetMapMgr()->CreateCreature(cp->Id);
		   pCreature->Load(cp, p_caster->GetPositionX(), p_caster->GetPositionY(), p_caster->GetPositionZ());
		   pCreature->_setFaction();
		   pCreature->GetAIInterface()->Init(pCreature,AITYPE_AGRO,MOVEMENTTYPE_NONE);
		   pCreature->GetAIInterface()->taunt(p_caster,true);
		   pCreature->_setFaction();
//		   pCreature->m_noRespawn = true;
		   pCreature->PushToWorld(p_caster->GetMapMgr());
		   sEventMgr.AddEvent(pCreature, &Creature::SafeDelete, EVENT_CREATURE_REMOVE_CORPSE,60000, 1, 0);
		}break;

	}
}

void Spell::SpellEffectApplyAA(uint32 i) // Apply Area Aura
{
	if(!unitTarget || !unitTarget->isAlive())
	{ 
		return;
	}
	if(u_caster!=unitTarget)
	{ 
		return;
	}

	Aura*pAura;
	std::map<uint32,Aura*>::iterator itr=unitTarget->tmpAura.find(GetProto()->Id);
	if(itr==unitTarget->tmpAura.end())
	{
		pAura=AuraPool.PooledNew();
		pAura->Init(GetProto(),GetDuration(),m_caster,unitTarget);
		unitTarget->tmpAura[ GetProto()->Id ]= pAura;
	}
	else 
	{
		pAura=itr->second;	
	}

	if(!sEventMgr.HasEvent(pAura, EVENT_AREAAURA_UPDATE))		/* only add it once */
	{
		float r=GetRadius(i);
		sEventMgr.AddEvent(pAura, &Aura::EventUpdateAA,r*r, EVENT_AREAAURA_UPDATE, 1000, 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);	
	}

	pAura->AddMod(GetProto()->EffectApplyAuraName[i],damage,GetProto()->EffectMiscValue[i],i);
}

void Spell::SpellEffectLearnSpell(uint32 i) // Learn Spell
{
	if(playerTarget == 0 && unitTarget && unitTarget->IsPet())
	{
		// bug in target map fill?
		//playerTarget = m_caster->GetMapMgr()->GetPlayer((uint32)m_targets.m_unitTarget);
		SpellEffectLearnPetSpell(i);
		return;
	}

	if( GetProto()->Id == 483 || GetProto()->Id == 55884 )		// "Learning"
	{
		if( !i_caster || !p_caster )
		{ 
			return;
		}

		uint32 spellid = 0;
		for(int i = 0; i < 5; ++i)
		{
			if( i_caster->GetProto()->Spells[i].Trigger == LEARNING && i_caster->GetProto()->Spells[i].Id != 0 )
			{
				spellid = i_caster->GetProto()->Spells[i].Id;
				break;
			}
		}

		if( !spellid || !dbcSpell.LookupEntryForced(spellid) )
		{ 
			return;
		}

		// learn me!
		p_caster->addSpell( spellid );

		// no normal handler
		return;
	}

	if(playerTarget)
	{
		uint32 spellToLearn = GetProto()->EffectTriggerSpell[i];
		playerTarget->addSpell(spellToLearn);
		//smth is wrong here, first we add this spell to player then we may cast it on player...
		SpellEntry *spellinfo = dbcSpell.LookupEntry(spellToLearn);
 		//remove specializations
		switch(spellinfo->Id)
 		{
		case 26801: //Shadoweave Tailoring
			playerTarget->removeSpell(26798,false,false,0); //Mooncloth Tailoring
			playerTarget->removeSpell(26797,false,false,0); //Spellfire Tailoring
 			break;
		case 26798: // Mooncloth Tailoring
			playerTarget->removeSpell(26801,false,false,0); //Shadoweave Tailoring
			playerTarget->removeSpell(26797,false,false,0); //Spellfire Tailoring
 			break;
		case 26797: //Spellfire Tailoring
			playerTarget->removeSpell(26801,false,false,0); //Shadoweave Tailoring
			playerTarget->removeSpell(26798,false,false,0); //Mooncloth Tailoring
 			break;
 		case 10656: //Dragonscale Leatherworking
			playerTarget->removeSpell(10658,false,false,0); //Elemental Leatherworking
			playerTarget->removeSpell(10660,false,false,0); //Tribal Leatherworking
 			break;
 		case 10658: //Elemental Leatherworking
			playerTarget->removeSpell(10656,false,false,0); //Dragonscale Leatherworking
			playerTarget->removeSpell(10660,false,false,0); //Tribal Leatherworking
 			break;
 		case 10660: //Tribal Leatherworking
			playerTarget->removeSpell(10656,false,false,0); //Dragonscale Leatherworking
			playerTarget->removeSpell(10658,false,false,0); //Elemental Leatherworking
 			break;
 		case 28677: //Elixir Master
			playerTarget->removeSpell(28675,false,false,0); //Potion Master
			playerTarget->removeSpell(28672,false,false,0); //Transmutation Maste
 			break;
 		case 28675: //Potion Master
			playerTarget->removeSpell(28677,false,false,0); //Elixir Master
			playerTarget->removeSpell(28672,false,false,0); //Transmutation Maste
 			break;
 		case 28672: //Transmutation Master
			playerTarget->removeSpell(28675,false,false,0); //Potion Master
			playerTarget->removeSpell(28677,false,false,0); //Elixir Master
 			break;
 		case 20219: //Gnomish Engineer
			playerTarget->removeSpell(20222,false,false,0); //Goblin Engineer
 			break;
 		case 20222: //Goblin Engineer
			playerTarget->removeSpell(20219,false,false,0); //Gnomish Engineer
 			break;
 		case 9788: //Armorsmith
			playerTarget->removeSpell(9787,false,false,0); //Weaponsmith
			playerTarget->removeSpell(17039,false,false,0); //Master Swordsmith
			playerTarget->removeSpell(17040,false,false,0); //Master Hammersmith
			playerTarget->removeSpell(17041,false,false,0); //Master Axesmith
 			break;
 		case 9787: //Weaponsmith
			playerTarget->removeSpell(9788,false,false,0); //Armorsmith
 			break;
 		case 17041: //Master Axesmith
			playerTarget->removeSpell(9788,false,false,0); //Armorsmith
			playerTarget->removeSpell(17040,false,false,0); //Master Hammersmith
			playerTarget->removeSpell(17039,false,false,0); //Master Swordsmith
 			break;
 		case 17040: //Master Hammersmith
			playerTarget->removeSpell(9788,false,false,0); //Armorsmith
			playerTarget->removeSpell(17039,false,false,0); //Master Swordsmith
			playerTarget->removeSpell(17041,false,false,0); //Master Axesmith
 			break;
 		case 17039: //Master Swordsmith
			playerTarget->removeSpell(9788,false,false,0); //Armorsmith
			playerTarget->removeSpell(17040,false,false,0); //Master Hammersmith
			playerTarget->removeSpell(17041,false,false,0); //Master Axesmith
 			break;
 		}
		for(uint32 i=0;i<3;i++)
			if(spellinfo->Effect[i] == SPELL_EFFECT_WEAPON ||
			   spellinfo->Effect[i] == SPELL_EFFECT_PROFICIENCY ||
			   spellinfo->Effect[i] == SPELL_EFFECT_DUAL_WIELD )
			{
				Spell *sp = SpellPool.PooledNew();
				sp->Init(unitTarget, spellinfo, true, NULL);
				SpellCastTargets targets;
				targets.m_unitTarget = unitTarget->GetGUID();
				targets.m_targetMask = 0x02;
				sp->prepare(&targets);
				break;
			}	  
		return;
	}

	// if we got here... try via pet spells..
	SpellEffectLearnPetSpell(i);
}

void Spell::SpellEffectSpellDefense(uint32 i)
{
	//used to enable this ability. We use it all the time ...
}

void Spell::SpellEffectLearnPetSpell(uint32 i)
{
	/*if(unitTarget && m_caster->GetTypeId() == TYPEID_PLAYER)
	{
		if(unitTarget->IsPet() && unitTarget->GetTypeId() == TYPEID_UNIT)
		{
			SafePlayerCast(m_caster)->AddPetSpell(GetProto()->EffectTriggerSpell[i], unitTarget->GetEntry());
		}
	}*/

	if(unitTarget && unitTarget->IsPet() && p_caster)
	{
		Pet * pPet = SafePetCast( unitTarget );
		if(pPet->IsSummon())
			p_caster->AddSummonSpell(unitTarget->GetEntry(), GetProto()->EffectTriggerSpell[i]);
		
		pPet->AddSpell( dbcSpell.LookupEntry( GetProto()->EffectTriggerSpell[i] ), true );
	}
}

void Spell::SpellEffectDispel(uint32 i) // Dispel
{
	if(!u_caster || !unitTarget)
	{ 
		return;
	}

	Aura *aur;
	uint32 start,end;
	if(isAttackable(u_caster,unitTarget))
	{
		start=0;
		end=MAX_POSITIVE_AURAS1(unitTarget);
		if (unitTarget->SchoolImmunityList[GetProto()->School])
		{ 
			return;
		}
	}
	else
	{
		start=MAX_POSITIVE_AURAS;
		end=MAX_NEGATIVE_AURAS1(unitTarget);
	}
	
	WorldPacket data(SMSG_SPELLDISPELLOG, 16);

	for(uint32 x=start;x<end;x++)
	if(unitTarget->m_auras[x])
	{
		aur = unitTarget->m_auras[x];
		//Nothing can dispel resurrection sickness;
		if(!aur->IsPassive() && !(aur->GetSpellProto()->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY))
		{
//			uint32 UARank = 0;
			if(GetProto()->DispelType == DISPEL_ALL)
			{
//				if( aur->m_spellProto && aur->m_spellProto->NameHash == SPELL_HASH_UNSTABLE_AFFLICTION )
//					UARank = aur->m_spellProto->RankNumber;

				data.clear();
				data << m_caster->GetNewGUID();
				data << unitTarget->GetNewGUID();
				data << (uint32)1;//probably dispel type
				data << aur->GetSpellId();
				m_caster->SendMessageToSet(&data,true);
				unitTarget->HandleProc( PROC_ON_PRE_DISPELL_AURA_VICTIM , u_caster , GetProto(), aur->GetSpellId() );
				//handleproc might remove us !				
				if( unitTarget->m_auras[x] == aur )
					unitTarget->RemoveAura(aur);
				if(!--damage)
				{ 
					return;
				}
			}
			else if(aur->GetSpellProto()->DispelType == GetProto()->EffectMiscValue[i])
			{
//				if( aur->m_spellProto && aur->m_spellProto->NameHash == SPELL_HASH_UNSTABLE_AFFLICTION )
//					UARank = aur->m_spellProto->RankNumber;

				data.clear();
				data << m_caster->GetNewGUID();
				data << unitTarget->GetNewGUID();
				data << (uint32)1;
				data << aur->GetSpellId();
				m_caster->SendMessageToSet(&data,true);

				//handleproc might remove us !
				uint32 spid = aur->GetSpellId();
				uint64 cguid = aur->GetCasterGUID();
				unitTarget->HandleProc( PROC_ON_PRE_DISPELL_AURA_VICTIM , u_caster , GetProto(), aur->GetSpellId() );
				unitTarget->RemoveAllAuras(spid,cguid);
				if(!--damage)
				{ 
					return;
				}
			}	
/*			this never gets reached with current code		
			if( UARank != 0 )
			{
				uint32 dmg = 0;
				switch ( UARank ) // BRRR, FUCKING BLIZZ
				{
					case 1:
						dmg = 990;
						break;
					case 2:
						dmg = 1260;
						break;
					case 3:
						dmg = 1575;
						break;
				}
				u_caster->SpellNonMeleeDamageLog(u_caster,31117,dmg,true,true);
			}*/
		}
	}   
}

void Spell::SpellEffectDualWield(uint32 i)
{
	if(m_caster->GetTypeId() != TYPEID_PLAYER) 
	{ 
		return;
	}

	Player *pPlayer = SafePlayerCast( m_caster );

	if( !pPlayer->_HasSkillLine( SKILL_DUAL_WIELD ) )
		 pPlayer->_AddSkillLine( SKILL_DUAL_WIELD, 1, 1 );
	
		// Increase it by one
		//dual wield is 1/1 , it never increases it's not even displayed in skills tab

	//note: probably here must be not caster but unitVictim
}

void Spell::SpellEffectSummonWild(uint32 i)  // Summon Wild
{
	//these are some cretures that have your faction and do not respawn
	//number of creatures is actualy dmg (the usual formula), sometimes =3 sometimes =1
	if( !u_caster || !u_caster->IsInWorld() )
	{ 
		return;
	}
	
	uint32 cr_entry=GetProto()->EffectMiscValue[i];
	CreatureProto * proto = CreatureProtoStorage.LookupEntry(cr_entry);
	CreatureInfo * info = CreatureNameStorage.LookupEntry(cr_entry);
	if(!proto || !info)
	{
		sLog.outDetail("Warning : Missing summon creature template %u used by spell %u!",cr_entry,GetProto()->Id);
		return;
	}
	float x, y, z;
	if( m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION && m_targets.m_destX && m_targets.m_destY && m_targets.m_destZ )
	{
		x = m_targets.m_destX;
		y = m_targets.m_destY;
		z = m_targets.m_destZ;
	}
	else
	{
		x = u_caster->GetPositionX();
		y = u_caster->GetPositionY();
		z = u_caster->GetPositionZ();
	}
	for(int i=0;i<damage;i++)
	{
		float m_fallowAngle=-(float(M_PI)/2*i);
		x += (GetRadius(GetProto()->EffectRadiusIndex[i])*(cosf(m_fallowAngle+u_caster->GetOrientation())));
		y += (GetRadius(GetProto()->EffectRadiusIndex[i])*(sinf(m_fallowAngle+u_caster->GetOrientation())));
		Creature * p = u_caster->GetMapMgr()->CreateCreature(cr_entry);
		//ASSERT(p);
		p->Load(proto, x, y, z);
		p->SetZoneId( m_caster->GetZoneId() );

		if ( p->GetProto() && p->GetProto()->Faction == 35 )
		{
			p->SetUInt64Value( UNIT_FIELD_SUMMONEDBY, m_caster->GetGUID() );
			p->SetUInt64Value( UNIT_FIELD_CREATEDBY, m_caster->GetGUID() );
			p->SetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE, u_caster->GetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE ) );
		}
		else
		{
			p->SetUInt32Value( UNIT_FIELD_FACTIONTEMPLATE, proto->Faction );
		}

		p->m_faction = dbcFactionTemplate.LookupEntry(proto->Faction);
		if(p->m_faction)
			p->m_factionDBC = dbcFaction.LookupEntry(p->m_faction->Faction);
//		p->m_noRespawn = true;
		p->PushToWorld(u_caster->GetMapMgr());
		//make sure they will be desumonized (roxor)
		sEventMgr.AddEvent(p, &Creature::SummonExpire, EVENT_SUMMON_EXPIRE, GetDuration(), 1,0);
	}
}

void Spell::SpellEffectSummonGuardian(uint32 i) // Summon Guardian
{
	GameObject * obj = NULL; //Snake trap part 1
	LocationVector * vec = NULL;
	
	if ( g_caster ) 
	{
		if ( g_caster->m_summoner )
		{
			u_caster = g_caster->m_summoner; //set the caster to the summoner unit
			obj = g_caster; //and keep the trap info
		}
		else
		{
			return;
		}
	}
	else if ( !u_caster )
	{ 
		return;
	}

	uint32 cr_entry = GetProto()->EffectMiscValue[i];
	uint32 level = 0;

	if( GetProto()->c_is_flags & SPELL_FLAG_IS_INHERITING_LEVEL )
		level = u_caster->getLevel();
	/*if ( u_caster->GetTypeId()==TYPEID_PLAYER && itemTarget )
	{
		if (itemTarget->GetProto() && itemTarget->GetProto()->RequiredSkill == SKILL_ENGINEERING)
		{
			uint32 skill202 = SafePlayerCast( m_caster )->_GetSkillLineCurrent(SKILL_ENGINEERING);
			if (skill202>0)
			{
				level = skill202/5;
			}
		}
	}*/
	if( m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION && m_targets.m_destX && m_targets.m_destY && m_targets.m_destZ )
	{
		vec = new LocationVector(m_targets.m_destX,m_targets.m_destY,m_targets.m_destZ);
	}

//	float angle_for_each_spawn = -float(M_PI) * 2 / damage;
	for( int i = 0; i < damage; i++ )
	{
//		float m_fallowAngle = angle_for_each_spawn * i;
		Unit *tu = u_caster->create_guardian(cr_entry,GetDuration(),level,obj,vec, GetProto() );
	}
	if (vec) 
	{
		delete vec;
		vec = NULL;
	}
}

void Spell::SpellEffectSkillStep(uint32 i) // Skill Step
{
	Player*target;
	if(m_caster->GetTypeId() != TYPEID_PLAYER)
	{
		// Check targets
		if( m_targets.m_unitTarget )
		{
			target = objmgr.GetPlayer((uint32)m_targets.m_unitTarget);
			if( target == NULL ) 
			{ 
				return;
			}
		}
		else
			return;
	}
	else
	{
		target = SafePlayerCast( m_caster );
	}
	
	uint32 skill = GetProto()->EffectMiscValue[i];
	if( skill == 242 )
		skill = SKILL_LOCKPICKING; // somehow for lockpicking misc is different than the skill :s

	skilllineentry* sk = dbcSkillLine.LookupEntry( skill );

	if( sk == NULL )
	{ 
		return;
	}

	uint32 max = 1;
	switch( sk->type )
	{
		case SKILL_TYPE_PROFESSION:
		case SKILL_TYPE_SECONDARY:
			max = damage * 75;
			break;
		case SKILL_TYPE_WEAPON:
			max = 5 * target->getLevel();
			break;
		case SKILL_TYPE_CLASS:
		case SKILL_TYPE_ARMOR:
			if( skill == SKILL_LOCKPICKING )
				max = damage * 75;
			else
				max = 1;
			break;
		default: //u cant learn other types in game
			return;
	};

	if( target->_HasSkillLine( skill ) )
	{
		target->_ModifySkillMaximum( skill, max );
	}		
	else
	{
		// Don't add skills to players logging in.
		/*if((GetProto()->Attributes & 64) && playerTarget->m_TeleportState == 1)
			return;*/

#ifndef CATACLYSM_SUPPORT
		if( sk->type == SKILL_TYPE_PROFESSION )
			target->ModUnsigned32Value( PLAYER_CHARACTER_POINTS2, -1 );
#endif
	  
		if( skill == SKILL_RIDING )
			target->_AddSkillLine( skill, max, max );
		else
			target->_AddSkillLine( skill, 1, max );
	}

}

void Spell::SpellEffectSummonObject(uint32 i)
{
	if( !u_caster )
	{ 
		return;
	}

	uint32 entry = GetProto()->EffectMiscValue[i];

	uint32 mapid = u_caster->GetMapId();
	float px = u_caster->GetPositionX();
	float py = u_caster->GetPositionY();
	float pz = u_caster->GetPositionZ();
	float orient = m_caster->GetOrientation();
	float posx = 0,posy = 0,posz = 0;
	
	if( entry == GO_FISHING_BOBBER && p_caster )
	{
		posx = m_targets.m_destX;
		posy = m_targets.m_destY;
		posz = m_targets.m_destZ;

		// Todo / Fix me: This should be loaded / cached
		uint32 zone = p_caster->GetAreaID();
		if( zone == 0 ) // If the player's area ID is 0, use the zone ID instead
			zone = p_caster->GetZoneId();

		uint32 minskill;
		FishingZoneEntry *fishentry = FishingZoneStorage.LookupEntry( zone );
		if( !fishentry ) // Check database if there is fishing area / zone information, if not, return
		{ 
			return;
		}
		
		// Todo / Fix me: Add fishskill to the calculations
		minskill = fishentry->MinSkill;
		SendChannelStart( 20000 ); // 30 seconds
		/*spell->SendSpellStart();
		spell->SendCastResult(SPELL_CANCAST_OK);
		spell->SendSpellGo ();*/

		GameObject *go = u_caster->GetMapMgr()->CreateGameObject(GO_FISHING_BOBBER);

		go->CreateFromProto( GO_FISHING_BOBBER, mapid, posx, posy, posz, orient );
		go->SetUInt32Value( GAMEOBJECT_FLAGS, 0 );
		go->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 0 );
		go->SetUInt64Value( OBJECT_FIELD_CREATED_BY, m_caster->GetGUID() );
		u_caster->SetUInt64Value( UNIT_FIELD_CHANNEL_OBJECT, go->GetGUID() );
			 
		go->SetInstanceID( m_caster->GetInstanceID() );
		go->PushToWorld( m_caster->GetMapMgr() );

		uint64 CasterGuid = m_caster->GetGUID();
		if( lootmgr.IsFishable( zone ) ) // Only set a 'splash' if there is any loot in this area / zone
		{
			uint32 seconds = RandomUInt(17) + 2;
			sEventMgr.AddEvent( go, &GameObject::FishHooked, CasterGuid , EVENT_GAMEOBJECT_FISH_HOOKED, seconds * 1000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
		}
		sEventMgr.AddEvent( go, &GameObject::EndFishingEvent, CasterGuid, false, EVENT_GAMEOBJECT_END_FISHING, 20000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
		p_caster->SetSummonedObject( go );
	}
	else
	{
		posx=px;
		posy=py;		
		GameObjectInfo * goI = GameObjectNameStorage.LookupEntry(entry);
		if(!goI)
		{
			if( p_caster != NULL )
			{
				sChatHandler.BlueSystemMessage(p_caster->GetSession(), "non-existant gameobject %u tried to be created by SpellEffectSummonObject. Report to devs!", entry);
			}
			return;
		}
		if( m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION && m_targets.m_destX && m_targets.m_destY && m_targets.m_destZ )
		{
			posx = m_targets.m_destX;
			posy = m_targets.m_destY;
			pz = m_targets.m_destZ;
		}
		GameObject *go=m_caster->GetMapMgr()->CreateGameObject(entry);
		
		go->SetInstanceID(m_caster->GetInstanceID());
		go->CreateFromProto(entry,mapid,posx,posy,pz,orient);
		go->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 1);
		go->SetUInt64Value(OBJECT_FIELD_CREATED_BY,m_caster->GetGUID());
		go->PushToWorld(m_caster->GetMapMgr());

		//avoid infinit spawns ...could get to be an exploit
		uint32 duration = GetDuration();
		if( duration == (uint32)-1 || duration > 60*60*1000 )
			duration = 10*60*1000;

		sEventMgr.AddEvent(go, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, duration, 1,0);
		if ( entry == 17032 && p_caster ) // this is a portal
		{
			// enable it for party only
			go->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 0 );
			//disable by default
			WorldPacket * pkt = go->BuildFieldUpdatePacket( GAMEOBJECT_BYTES_1, 1 );
			SubGroup * pGroup = p_caster->GetGroup() ? p_caster->GetGroup()->GetSubGroup(p_caster->GetSubGroup()) : NULL;

			if ( pGroup != NULL )
			{
				p_caster->GetGroup()->Lock();
				for ( GroupMembersSet::iterator itr = pGroup->GetGroupMembersBegin(); itr != pGroup->GetGroupMembersEnd(); ++itr )
				{
					if( (*itr)->m_loggedInPlayer && m_caster != (*itr)->m_loggedInPlayer )
						(*itr)->m_loggedInPlayer->GetSession()->SendPacket( pkt );
				}
				p_caster->GetGroup()->Unlock();
			}
			delete pkt;
			pkt = NULL;
		}
		else if (( entry == 36727 || entry == 177193 || entry == 194108 // Portal of Summoning and portal of doom, Ritual of Summoning
			) && p_caster )
		{
			//Player * pTarget = p_caster->GetMapMgr()->GetPlayer( p_caster->GetSelection() );
			Player * pTarget = objmgr.GetPlayer( (uint32)p_caster->GetSelection() );	//selection can be on other maps too
			if ( pTarget == NULL || !pTarget->IsInWorld() )
			{ 
				return;
			}
			if( go->m_ritualmembers == NULL )
			{
				go->m_ritualmembers = new uint64[go->GetInfo()->SpellFocus];
				memset(go->m_ritualmembers,0,sizeof(uint64) * go->GetInfo()->SpellFocus );
			}
			go->m_ritualmembers[0] = p_caster->GetLowGUID();
			go->m_ritualcaster = p_caster->GetLowGUID();
			go->m_ritualtarget = pTarget->GetLowGUID();
			go->m_ritualspell = GetProto()->Id;
		}
		else if (( entry == 186811 || entry == 181622 
			 || entry == 193062	//Refreshment Portal
			 || GetProto()->ChannelInterruptFlags !=0 
			) && p_caster ) // ritual of refreshment, ritual of souls
		{
			if( go->m_ritualmembers == NULL )
			{
				go->m_ritualmembers = new uint64[go->GetInfo()->SpellFocus];
				memset(go->m_ritualmembers,0,sizeof(uint64) * go->GetInfo()->SpellFocus );
			}
			go->m_ritualmembers[0] = p_caster->GetLowGUID();
			go->m_ritualcaster = p_caster->GetLowGUID();
			go->m_ritualtarget = 0;
			go->m_ritualspell = GetProto()->Id;
		}
		else if ( entry == 186812 || entry == 181621 ) // Refreshment Table, Soulwell
		{
			go->charges = goI->sound1;
		}
		else//Lightwell,if there is some other type -- add it
		{
			go->charges = 5;//Max 5 charges
		}
		if( p_caster )
			p_caster->SetSummonedObject(go);
	}
}

void Spell::SpellEffectEnchantItem(uint32 i) // Enchant Item Permanent
{
	if(!itemTarget || !p_caster) 
	{ 
		return;
	}

	//special handling for velums
	if( itemTarget->GetProto()->Class == ITEM_CLASS_TRADEGOODS && itemTarget->GetProto()->SubClass == ITEM_SUBCLASS_VELUM )
	{
		//remove the velum first to give the space for the new item(if it helps at all )
		p_caster->GetItemInterface()->RemoveItemAmt_ProtectPointer( itemTarget->GetProto()->ItemId, 1, &itemTarget);
		//create the scroll
		uint32 scroll_entry = objmgr.VelumEnchantToScrollEntry[ GetProto()->Id ];
		if( scroll_entry <= 0 )
		{
			p_caster->BroadcastMessage( "Velum is missing transformation item. Report this to devs : Velum spell %d missing", GetProto()->Id );
			return;
		}
		ItemPrototype *m_itemProto;
		m_itemProto = ItemPrototypeStorage.LookupEntry( scroll_entry );
		if (!m_itemProto)
			return;
		if(p_caster->GetItemInterface()->CanReceiveItem(m_itemProto, 1))
		{
			SendCastResult(SPELL_FAILED_TOO_MANY_OF_ITEM);
			return;
		}
		Item *add = p_caster->GetItemInterface()->FindItemLessMax(scroll_entry, 1, false);
		if( add )  
		{
			add->SetCount(add->GetUInt32Value(ITEM_FIELD_STACK_COUNT) + 1);
			add->m_isDirty = true;
			p_caster->GetSession()->SendItemPushResult(add, true,false,true,false,p_caster->GetItemInterface()->GetBagSlotByGuid(add->GetGUID()),0xFFFFFFFF,1);
		}
		else
		{
			SlotResult slotresult = p_caster->GetItemInterface()->FindFreeInventorySlot(m_itemProto);
			if(!slotresult.Result)
			{
				  SendCastResult(SPELL_FAILED_TOO_MANY_OF_ITEM);
				  return;
			}
			
			Item *newItem =objmgr.CreateItem(scroll_entry,p_caster);
			newItem->SetUInt64Value(ITEM_FIELD_CREATOR,m_caster->GetGUID());
			newItem->SetUInt32Value(ITEM_FIELD_STACK_COUNT, 1);

			AddItemResult res = p_caster->GetItemInterface()->SafeAddItem(newItem,slotresult.ContainerSlot, slotresult.Slot);
			if( res == ADD_ITEM_RESULT_OK )
				p_caster->GetSession()->SendItemPushResult(newItem,true,false,true,true,slotresult.ContainerSlot,slotresult.Slot,1);
			else if( res == ADD_ITEM_RESULT_ERROR )
			{
				newItem->DeleteMe();
				newItem = NULL;
			}
		}
		return;
	}

	EnchantEntry * Enchantment = dbcEnchant.LookupEntry(GetProto()->EffectMiscValue[i]);
	if(!Enchantment) 
	{ 
		return;
	}

	if(p_caster->GetSession()->GetPermissionCount() > 0)
		sGMLog.writefromsession(p_caster->GetSession(), "enchanted item for %s", itemTarget->GetOwner()->GetName());

	//remove other perm enchantment that was enchanted by profession
	int32 Slot;
	if( GetProto()->Effect[i] == SPELL_EFFECT_ADD_SOCKET )
	{
		//check if we already added a slot via enchantments
		if ( itemTarget->HasEnchantment( Enchantment->Id ) != -1 )
		{ 
			return;
		}
		itemTarget->AddEnchantment(Enchantment, 0, true, true, false, PRISMATIC_ENCHANTMENT_SLOT);
	}
	else
	{
		itemTarget->RemoveProfessionEnchant();
		Slot = itemTarget->AddEnchantment(Enchantment, 0, true, true, false, ITEM_ENCHANT_SLOT_TEMPORARY1);
	}

	if( i_caster == NULL )
		for(uint32 i=0;i<GetProto()->spell_skilline_assoc_counter;i++)
			DetermineSkillUp(GetProto()->spell_skilline[i]);
}

void Spell::SpellEffectEnchantItemTemporary(uint32 i)  // Enchant Item Temporary
{
	if( !itemTarget || !p_caster )
	{
		sLog.outDebug(" Cannot apply temporary enchant %u for spell %u without target or caster",GetProto()->Id,GetProto()->EffectMiscValue[i]);
		return;
	}
	uint32 Duration = damage > 1 ? damage : 1800;

	// dont allow temporary enchants unless we're the owner of the item
	if( itemTarget->GetOwner() != p_caster )
	{
		sLog.outDebug(" Cannot apply temporary enchant %u for spell %u on not owned item",GetProto()->Id,GetProto()->EffectMiscValue[i]);
		return;
	}

	EnchantEntry * Enchantment = dbcEnchant.LookupEntry(GetProto()->EffectMiscValue[i]);
	if(!Enchantment)
	{
		sLog.outDebug(" Enchantment %u for spell %u does not exist",GetProto()->Id,GetProto()->EffectMiscValue[i]);
		return;
	}

	itemTarget->RemoveEnchantment(ITEM_ENCHANT_SLOT_TEMPORARY2);
	int32 Slot = itemTarget->AddEnchantment(Enchantment, Duration, false, true, false, ITEM_ENCHANT_SLOT_TEMPORARY2);
	if(Slot < 0)
		return; // Apply failed

//	skilllinespell* skill = objmgr.GetSpellSkill(GetProto()->Id);
	if( GetProto()->spell_skilline[0] )
		DetermineSkillUp( GetProto()->spell_skilline[0], itemTarget->GetProto()->ItemLevel);
}

void Spell::SpellEffectTameCreature(uint32 i)
{
	if( !p_caster )
	{ 
		return;
	}

    Creature* tame = ( ( unitTarget->GetTypeId() == TYPEID_UNIT ) ? SafeCreatureCast( unitTarget ) : NULL );

	//the target might get removed from world before we manage to tame it
    if( tame == NULL || !tame->IsInWorld() )
    { 
		return;
    }

	// Remove target
	tame->GetAIInterface()->HandleEvent(EVENT_LEAVECOMBAT, p_caster, 0);
	Pet *pPet = objmgr.CreatePet( tame->GetEntry(), p_caster->GeneratePetNumber() );
	pPet->SetInstanceID(p_caster->GetInstanceID());
	//302 - tamed pets are close to tamer level
//	if( tame->getLevel() + 5 < p_caster->getLevel() )
//		tame->SetUInt32Value( UNIT_FIELD_LEVEL, p_caster->getLevel() ); //this will never loop into negative ;)
	pPet->CreateAsSummon(tame->GetEntry(), tame->GetCreatureInfo(), tame, p_caster, NULL, 2, 0);
//	p_caster->SetFlag(PLAYER_FIELD_BYTES,PLAYER_BYTES_FLAG_HAS_PET);
	//tame->SafeDelete();
	//delete tame;
	tame->Despawn(0,tame->GetProto()? tame->GetProto()->RespawnTime:0);
}

void Spell::SpellEffectSummonPet(uint32 i) //summon - pet
{
	if(GetProto()->Id == 883)
	{
		// "Call Pet" spell
		if(!p_caster)
		{ 
			return;
		}

		if(p_caster->GetSummon() != 0)
		{
			p_caster->GetSession()->SendNotification("You already have a pet summoned.");
			return;
		}

		uint32 petno = p_caster->GetUnstabledPetNumber();

		if(petno)
		{
			p_caster->SpawnPet(petno);
		}
		else
		{
			WorldPacket data(SMSG_AREA_TRIGGER_MESSAGE, 50);
			data << uint32(0) << "You do not have any pets to call." << uint8(0);
			p_caster->GetSession()->SendPacket(&data);
		}
		return;
	}
	
	//uint32 entryId = GetProto()->EffectMiscValue[i];

	//VoidWalker:torment, sacrifice, suffering, consume shadows
	//Succubus:lash of pain, soothing kiss, seduce , lesser invisibility
	//felhunter:	 Devour Magic,Paranoia,Spell Lock,	Tainted Blood
 
	if(!p_caster)
	{ 
		return;
	}
	
	// remove old pet
	Pet *old = SafePlayerCast(m_caster)->GetSummon();
	if(old)
		old->Dismiss();		
	
	CreatureInfo *ci = CreatureNameStorage.LookupEntry(GetProto()->EffectMiscValue[i]);
	if(ci)
	{
		if(p_caster->getClass() == WARLOCK)
		{
			//if demonic sacrifice auras are still active, remove them
			//uint32 spids[] = { 18789, 18790, 18791, 18792, 35701, 0 };
			//p_caster->RemoveAuras(spids);
			p_caster->RemoveAura(18789);
			p_caster->RemoveAura(18790);
			p_caster->RemoveAura(18791);
			p_caster->RemoveAura(18792);
			p_caster->RemoveAura(35701);
		}
		Pet *summon = objmgr.CreatePet( GetProto()->EffectMiscValue[i], p_caster->GeneratePetNumber() );
		summon->SetInstanceID(m_caster->GetInstanceID());
		summon->CreateAsSummon(GetProto()->EffectMiscValue[i], ci, NULL, p_caster, GetProto(), 1, 0);
	}
}

void Spell::SpellEffectWeapondamage( uint32 i ) // Weapon damage +
{
	if( unitTarget == NULL || u_caster == NULL )
	{ 
		return;
	}

	// Hacky fix for druid spells where it would "double attack".
	if( GetProto()->Effect[2] == SPELL_EFFECT_WEAPON_PERCENT_DAMAGE || GetProto()->Effect[1] == SPELL_EFFECT_WEAPON_PERCENT_DAMAGE )
	{
		add_damage += damage;
		return;
	}

	uint32 _type;
	if( GetType() == SPELL_DMG_TYPE_RANGED )
		_type = RANGED;
	else
	{
		if (GetProto()->AttributesExC & 0x1000000)
			_type =  OFFHAND;
		else
			_type = MELEE;
	}

	//avoid dmg overflows
	if( damage < 0 || damage > 100000 )
	{ 
		return;
	}

	u_caster->Strike( unitTarget, _type, GetProto(), damage, 0, 0, false, true );
}

void Spell::SpellEffectPowerBurn(uint32 i) // power burn
{
	if(!unitTarget)
	{ 
		return;
	}
	if(!unitTarget->isAlive())
	{ 
		return;
	}
	if (unitTarget->GetPowerType() != POWER_TYPE_MANA)
	{ 
		return;
	}

	//there must be a general flag that sets if value is PCT or direct. This one is pct
	if( GetProto()->NameHash == SPELL_HASH_MANA_BURN )
	{
		uint32 new_dmg = unitTarget->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) * damage / 100;
		uint32 dmg_limit = m_caster->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) * GetProto()->EffectBasePoints[i] * 2 / 100;
		if( new_dmg >= dmg_limit )
			new_dmg = dmg_limit;
		else // dmg_limit > new_dmg
		{
			uint32 extra_dmg = dmg_limit - new_dmg ;
			new_dmg = new_dmg + RandomUInt() % extra_dmg;
		}
		damage = new_dmg;
		//cannot cast more then twice on same target
		if( p_caster )
		{
			if( p_caster->mana_burn_target == unitTarget->GetLowGUID() )
				p_caster->mana_burn_target_cast++;
			else
			{
				p_caster->mana_burn_target_cast = 0;
				p_caster->mana_burn_target = unitTarget->GetLowGUID();
			}
			if( p_caster->mana_burn_target_cast >= 2 )
			{
				SendCastResult( SPELL_FAILED_BAD_TARGETS );
				return;
			}
		}
	}

	if( unitTarget->IsPlayer() )
	{
		Player* mPlayer = SafePlayerCast( unitTarget );
		if( mPlayer->IsInFeralForm() )
		{ 
			return;
		}

		// Resilience - reduces the effect of mana drains by (CalcRating*2)%.
//		damage *= float2int32( 1 - ( ( SafePlayerCast(unitTarget)->CalcRating( PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE ) * 2 ) / 100.0f ) );
	}

	int32 mana = (int32)min( (int32)unitTarget->GetUInt32Value( UNIT_FIELD_POWER1 ), damage );
	unitTarget->ModUnsigned32Value(UNIT_FIELD_POWER1,-mana);
	
	m_caster->SpellNonMeleeDamageLog(unitTarget,GetProto()->Id, (uint32)(mana * GetProto()->EffectConversionCoef[i]), pSpellId==0,true);   
}

void Spell::SpellEffectThreat(uint32 i) // Threat
{
	if(!unitTarget || !unitTarget->isAlive() )
	{ 
		return;
	}

	bool chck = unitTarget->GetAIInterface()->modThreatByPtr(u_caster,damage);
	if(chck == false)
		unitTarget->GetAIInterface()->AttackReaction(u_caster,damage,0);	
}

void Spell::SpellEffectTriggerSpell(uint32 i) // Trigger Spell
{
	SpellEntry *entry = dbcSpell.LookupEntry(GetProto()->EffectTriggerSpell[i]);
	if (entry == NULL) 
	{ 
		return;
	}

	//fucking hackfixes to target selected target in case of multiple targets
	if( GetProto()->Id == 49203 && unitTarget )
	{
		SpellCastTargets targets( unitTarget->GetGUID() );
		Spell *sp = SpellPool.PooledNew();
		sp->Init(m_caster,entry,true,NULL);
		sp->prepare(&targets);
		return;
	}
	SpellCastTargets targets = m_targets;
	Spell *sp = SpellPool.PooledNew();
	if( unitTarget && (( GetProto()->c_is_flags & SPELL_FLAG_IS_TRIGGERED_BY_TARGET ) || GetProto()->Effect[i] == SPELL_EFFECT_FORCE_CAST ) )
		sp->Init(unitTarget,entry,true,NULL);
	else
		sp->Init(m_caster,entry,true,NULL);
	sp->prepare(&targets);
}

void Spell::SpellEffectHealthFunnel(uint32 i) // Health Funnel
{
	if(!unitTarget)
	{ 
		return;		
	}
	if(!unitTarget->isAlive() || !unitTarget->IsPet())
	{ 
		return;
	}

	//does not exist
}

void Spell::SpellEffectPowerFunnel(uint32 i) // Power Funnel
{
	if(!unitTarget)
	{ 
		return;		
	}
	if(!unitTarget->isAlive() || !unitTarget->IsPet())
	{ 
		return;
	}

	//does not exist
}

void Spell::SpellEffectKillCredit( uint32 i )
{
	if ( playerTarget != NULL )
	{
		CreatureProto * cp = CreatureProtoStorage.LookupEntry( m_spellInfo->EffectMiscValue[i] );
		if ( cp != NULL )
			sQuestMgr.OnPlayerKill( playerTarget, m_spellInfo->EffectMiscValue[i], false );
	}
}

void Spell::SpellEffectHealMaxHealthPCT(uint32 i)   // Heal Max Health
{
	if( unitTarget == NULL || !unitTarget->isAlive() )
	{ 
		return;
	}

	uint32 heal = unitTarget->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * damage / 100;
	uint32 dif = unitTarget->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) - unitTarget->GetUInt32Value( UNIT_FIELD_HEALTH );
	if( heal > dif )
		heal = dif;

	if( unitTarget->GetTypeId() == TYPEID_PLAYER)
		 SendHealSpellOnPlayer( SafePlayerCast( m_caster ), SafePlayerCast( unitTarget ), heal, false );

	unitTarget->ModUnsigned32Value( UNIT_FIELD_HEALTH, heal );
}

void Spell::SpellEffectHealMaxHealth(uint32 i)   // Heal Max Health
{
	if( unitTarget == NULL || !unitTarget->isAlive() )
	{ 
		return;
	}

	uint32 dif = unitTarget->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) - unitTarget->GetUInt32Value( UNIT_FIELD_HEALTH );
	if( !dif )
	{
		SendCastResult( SPELL_FAILED_ALREADY_AT_FULL_HEALTH );
		return;
	}

	if( unitTarget->GetTypeId() == TYPEID_PLAYER)
	{
		 SendHealSpellOnPlayer( SafePlayerCast( m_caster ), SafePlayerCast( unitTarget ), dif, false );
	}
	unitTarget->ModUnsigned32Value( UNIT_FIELD_HEALTH, dif );
}

void Spell::SpellEffectInterruptCast(uint32 i) // Interrupt Cast
{
	if(!unitTarget || !unitTarget->isAlive())
	{ 
		return;
	}

	if(!playerTarget)
	{
		if (u_caster && (u_caster != unitTarget))
		{
			unitTarget->GetAIInterface()->AttackReaction(u_caster, 1, m_spellInfo->Id);
			Creature *c = SafeCreatureCast( unitTarget );
			if (c && c->GetProto() && c->GetProto()->modImmunities)
			{
				if (c->GetProto()->modImmunities & 32768)
				{ 
					return;
				}
			}
		}
	}
	// FIXME:This thing prevent target from spell casting too but cant find.
	uint32 school=0;
	if(unitTarget->GetCurrentSpell())
	{
		school=unitTarget->GetCurrentSpell()->GetProto()->School;
	}
	unitTarget->InterruptSpell();
	if(school)//prevent from casts in this school
	{
		int32 duration = GetDuration();
		if(unitTarget->IsPlayer()){		// Check for interruption reducing talents
			int32 DurationModifier = SafePlayerCast( unitTarget )->MechanicDurationPctMod[MECHANIC_INTERRUPTED];
			if(DurationModifier >= - 100)
				duration = (duration*(100+DurationModifier))/100;
		}
		unitTarget->SchoolCastPrevent[school]=duration+getMSTime();
		// TODO: visual!
	}
}

void Spell::SpellEffectDistract(uint32 i) // Distract
{
	//spellId 1725 Distract:Throws a distraction attracting the all monsters for ten sec's
	if(!unitTarget)
	{ 
		return;
	}
	if(!unitTarget->isAlive())
	{ 
		return;
	}

	if(m_targets.m_destX != 0.0f || m_targets.m_destY != 0.0f || m_targets.m_destZ != 0.0f)
	{
//		unitTarget->GetAIInterface()->MoveTo(m_targets.m_destX, m_targets.m_destY, m_targets.m_destZ, 0);
		uint32 Stare_duration=GetDuration();
		if(Stare_duration>30*60*1000)
			Stare_duration=10000;//if we try to stare for more then a half an hour then better not stare at all :P (bug)
		float newo=unitTarget->calcRadAngle(unitTarget->GetPositionX(),unitTarget->GetPositionY(),m_targets.m_destX,m_targets.m_destY);
		unitTarget->GetAIInterface()->StopMovement(Stare_duration);
		unitTarget->SetFacing(newo);
	}

	//Smoke Emitter 164870
	//Smoke Emitter Big 179066
	//Unit Field Target of 
}

void Spell::SpellEffectPickpocket(uint32 i) // pickpocket
{
	//Show random loot based on roll,	
	if(!unitTarget)
		return; // impossible..
	if(!p_caster)
	{ 
		return;
	}

	if(unitTarget->GetTypeId() != TYPEID_UNIT)
	{ 
		return;
	}

	Creature *target = SafeCreatureCast( unitTarget );
	if(target->IsPickPocketed() || target->GetCreatureInfo() == NULL || target->GetCreatureInfo()->Type != HUMANOID )
	{
		SendCastResult(SPELL_FAILED_TARGET_NO_POCKETS);
		return;
	}
			
 // lootmgr.FillPickpocketingLoot(&(SafeCreatureCast(unitTarget))->loot,unitTarget->GetEntry());
	if( target->DificultyProto && target->DificultyProto->loot_pickpocket )
	{
		lootmgr.FillObjectLoot(unitTarget,SafeCreatureCast(unitTarget)->DificultyProto->loot_pickpocket);
		p_caster->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE,2,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	}

	uint32 _rank = target->GetCreatureInfo()->Rank;
	unitTarget->loot.gold = float2int32((_rank+1) * unitTarget->getLevel() * (RandomUInt(5) + 1) * sWorld.getRate(RATE_MONEY));

	p_caster->SendLoot(unitTarget->GetGUID(), LOOT_PICKPOCKETING );
	target->SetPickPocketed(true);
}

void Spell::SpellEffectAddFarsight(uint32 i) // Add Farsight
{
	if(!p_caster)
	{ 
		return;
	}

	float x = m_targets.m_destX;
	float y = m_targets.m_destY;
	float z = m_targets.m_destZ;
	if(x == 0)
		x = m_targets.m_srcX;
	if(y == 0)
		y = m_targets.m_srcY;
	if(z == 0)
		z = m_targets.m_srcZ;

	DynamicObject * dynObj = p_caster->GetMapMgr()->CreateDynamicObject();
	dynObj->Create(u_caster, this, x, y, z, GetDuration(), GetRadius(i), damage );

	ASSERT(dynObj);
/*
	if( dynObj == NULL ) //i <3 burlex :P
	{
		delete dynObj;
		return;
	}
	*/
    dynObj->SetUInt32Value(OBJECT_FIELD_TYPE, 65);
    dynObj->SetUInt32Value(DYNAMICOBJECT_BYTES, 0x80000002);
	dynObj->SetInstanceID(p_caster->GetInstanceID());	
	p_caster->SetUInt64Value(PLAYER_FARSIGHT, dynObj->GetGUID());

	p_caster->GetMapMgr()->ChangeFarsightLocation(p_caster, dynObj);
}

void Spell::SpellEffectSummonPossessed(uint32 i) // eye of kilrog
{
	/*
	m_target->DisableAI();
	pCaster->SetUInt64Value(UNIT_FIELD_SUMMON, 0);
	m_target->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, 0);
	pCaster->SetUInt64Value(UNIT_FIELD_CHARM, m_target->GetGUID());
	m_target->SetUInt64Value(UNIT_FIELD_CHARMEDBY, pCaster->GetGUID());
	pCaster->SetUInt64Value(PLAYER_FARSIGHT, m_target->GetGUID());
	pCaster->m_CurrentCharm = ((Creature*)m_target);
	m_target->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED_CREATURE);
	pCaster->m_noInterrupt = 1;
	pCaster->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);

	WorldPacket data(SMSG_DEATH_NOTIFY_OBSOLETE);
	data << m_target->GetNewGUID() << uint8(1);
	pCaster->GetSession()->SendPacket(&data);
	*/

	CreatureInfo *ci = CreatureNameStorage.LookupEntry(GetProto()->EffectMiscValue[i]);
	if( ci && p_caster )
	{
		Creature* NewSummon = m_caster->GetMapMgr()->CreateCreature(ci->Id);
		// Create
		NewSummon->SetInstanceID(m_caster->GetInstanceID());
		NewSummon->Create( ci->Name, m_caster->GetMapId(), 
			m_caster->GetPositionX()+(3*(cos((float(M_PI)/2)+m_caster->GetOrientation()))), m_caster->GetPositionY()+(3*(cos((float(M_PI)/2)+m_caster->GetOrientation()))), m_caster->GetPositionZ() + 2, m_caster->GetOrientation());

		// Fields
		NewSummon->SetUInt32Value(UNIT_FIELD_LEVEL,m_caster->GetUInt32Value(UNIT_FIELD_LEVEL));
		NewSummon->SetUInt32Value(UNIT_FIELD_DISPLAYID,  ci->Male_DisplayID);
		NewSummon->SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, ci->Male_DisplayID);
		NewSummon->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, m_caster->GetGUID());
		NewSummon->SetUInt64Value(UNIT_FIELD_CREATEDBY, m_caster->GetGUID());
		NewSummon->SetUInt32Value(UNIT_FIELD_HEALTH , 100);
		NewSummon->SetUInt32Value(UNIT_FIELD_MAXHEALTH , 100);
		NewSummon->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, p_caster->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
		NewSummon->SetFloatValue(OBJECT_FIELD_SCALE_X,1.0f);
//		NewSummon->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_ATTACKABLE_9 | UNIT_FLAG_PLAYER_CONTROLLED_CREATURE);

		if(p_caster->IsPvPFlagged())
			NewSummon->SetPvPFlag();
		if(p_caster->IsFFAPvPFlagged())
			NewSummon->SetFFAPvPFlag();

		//Setting faction
		NewSummon->_setFaction();
		NewSummon->m_temp_summon=true;

		// Add To World
		NewSummon->PushToWorld(m_caster->GetMapMgr());
		
		// Force an update on the player to create this guid.
		p_caster->ProcessPendingUpdates();

		//p_caster->SetUInt64Value(UNIT_FIELD_SUMMON, NewSummon->GetGUID());
		p_caster->SetUInt64Value(PLAYER_FARSIGHT, NewSummon->GetGUID());	//not always ? Posssesd should handle this ?
		//p_caster->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);
		p_caster->Possess(NewSummon);
	}/**/
}

//void Spell::SpellEffectCreateSummonTotem(uint32 i)
void Spell::SpellEffectEquipGlyph(uint32 i)
{
	if( !p_caster )
	{ 
		return;
	}

	//check if slot is valid
	if( GLYPHS_COUNT <= GlyphSlot )
	{ 
		return;
	}

	//check if we can even equip this
	uint32 newGlyph = GetProto()->EffectMiscValue[i];

	//check if we already have this glyph equipped
	for(int i=0;i<GLYPHS_COUNT;i++)
		if( p_caster->GetUInt32Value( PLAYER_FIELD_GLYPHS_1 + i ) == newGlyph )
		{
			SendCastResult(SPELL_FAILED_UNIQUE_GLYPH);
			return;
		}

	GlyphPropertiesEntry *glyphprops = dbcGlyphPropertiesStore.LookupEntry( newGlyph );
	GlyphSlotEntry	*glypslot = dbcGlyphSlotStore.LookupEntry( p_caster->GetUInt32Value( PLAYER_FIELD_GLYPH_SLOTS_1 + GlyphSlot ) );
	//should not happen
	if( !glyphprops || !glypslot || glyphprops->TypeFlags != glypslot->TypeFlags )
	{
		sLog.outDebug("We are trying to insert a glyph into slot %u where we have slottype %u glyph is %u we have props %u and slot info %u\n",	GlyphSlot,p_caster->GetUInt32Value( PLAYER_FIELD_GLYPH_SLOTS_1 + GlyphSlot ),newGlyph,glyphprops!=NULL,glypslot!=NULL);
		if( glyphprops && glypslot )
			sLog.outDebug(" Glyph property flags = %u while slot property flags = %u\n",glyphprops->TypeFlags,glypslot->TypeFlags);
		SendCastResult(SPELL_FAILED_INVALID_GLYPH);
		return;
	}

	//remove old glyp if there is one equipped
	uint32 old_glyph = p_caster->GetUInt32Value( PLAYER_FIELD_GLYPHS_1 + GlyphSlot );
	GlyphPropertiesEntry *old_glyphprops = dbcGlyphPropertiesStore.LookupEntry( old_glyph );
	if( old_glyphprops )
		p_caster->RemoveAura( old_glyphprops->SpellId );

	//the new glyph. 
	p_caster->SetUInt32Value( PLAYER_FIELD_GLYPHS_1 + GlyphSlot, newGlyph );
	p_caster->m_specs[ p_caster->m_talentActiveSpec ].glyphs[ GlyphSlot ] = newGlyph;

	//blizz uses this. Not sure we need it or not
//	sStackWolrdPacket( learnspell, SMSG_LEARNED_SPELL, 8);
//	learnspell << spell_id;
//	learnspell << uint16( 0 );	//from 3.2
//	p_caster->m_session->SendPacket( &learnspell );
	p_caster->smsg_TalentsInfo(false, 0, 0);

	//the effect of the glyph
	SpellEntry *spellInfo = dbcSpell.LookupEntry( glyphprops->SpellId ); //we already modified this spell on server loading so it must exist
	Spell *spell = SpellPool.PooledNew();
	spell->Init( p_caster, spellInfo ,true, NULL );
	SpellCastTargets targets( p_caster->GetGUID() );
	spell->prepare(&targets);

	//isn't this auto removed ?
    if( i_caster && p_caster->GetItemInterface() )
		p_caster->GetItemInterface()->SafeFullRemoveItemByGuid( i_caster->GetGUID() );
}

void Spell::SpellEffectHealMechanical(uint32 i)
{
	if(!unitTarget)
	{ 
		return;
	}
	if(unitTarget->GetTypeId() != TYPEID_UNIT)
	{ 
		return;
	}
	if(SafeCreatureCast(unitTarget)->GetCreatureInfo()->Type != MECHANICAL)
	{ 
		return;
	}

	Heal((int32)damage,false, i);
}

void Spell::SpellEffectSummonObjectWild(uint32 i)
{
	if(!u_caster)
	{ 
		return;
	}


	uint32 GOEntry = GetProto()->EffectMiscValue[i];
	//let's check if paleyr already has this summoned. No idea what should be max but atm this is a server crashing exploit
	if( p_caster )
	{
		SimplePointerListNode<GOSummon>	*itr;
		for( itr = p_caster->PossibleGoSummons.begin(); itr != p_caster->PossibleGoSummons.end(); itr = itr->Next() )
			if( itr->data->entry == GOEntry )
			{
				//try to remove this go from world
				GameObject *go = p_caster->GetMapMgr()->GetGameObject( itr->data->GUID );
				if( go )
					go->Despawn( 0 );
				p_caster->PossibleGoSummons.remove( itr, 1 );
				break;
			}
	}

	// spawn a new one
	GameObject *GoSummon = u_caster->GetMapMgr()->CreateGameObject( GOEntry );
	if(!GoSummon->CreateFromProto(GetProto()->EffectMiscValue[i],
		m_caster->GetMapId(), m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ()+1, m_caster->GetOrientation() ))
	{
		sLog.outDebug("Could not create GameObject %u from proto\n",GetProto()->EffectMiscValue[i] );
		sGarbageCollection.AddObject( GoSummon );
		GoSummon = NULL;
		return;
	}
	
	GoSummon->SetInstanceID(m_caster->GetInstanceID());
	GoSummon->SetUInt32Value(GAMEOBJECT_LEVEL, u_caster->getLevel());
	GoSummon->SetUInt64Value(OBJECT_FIELD_CREATED_BY, m_caster->GetGUID());
	GoSummon->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE, 0);
	GoSummon->PushToWorld(u_caster->GetMapMgr());
	GoSummon->SetSummoned(u_caster);
	
	//avoid infinit spawns ...could get to be an exploit
	uint32 duration = GetDuration();
	if( duration == (uint32)-1 || duration > 60*60*1000 )
		duration = 10*60*1000;

	sEventMgr.AddEvent(GoSummon, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, duration, 1,0);

	//antisummonspam
	if( p_caster )
	{
		GOSummon *PCasterAntiSummonSpam = new GOSummon;
		PCasterAntiSummonSpam->entry = GOEntry;
		PCasterAntiSummonSpam->GUID = GoSummon->GetGUID();
		p_caster->PossibleGoSummons.push_front( PCasterAntiSummonSpam );
	}
}

void Spell::SpellEffectScriptEffect(uint32 i) // Script Effect
{
	uint32 spellId = GetProto()->Id;

	// Try a dummy SpellHandler
	if(sScriptMgr.CallScriptedDummySpell(spellId, i, this))
	{ 
		return;
	}

	switch(spellId)
	{
		//Make Player Destroy Totems - note that some versions were made using "reagents" to remove totems. This is only double check
		case 66744:
		{
			Player *p_target = GetPlayerTarget();
			if( p_target && p_target->GetItemInterface() )
			{
				p_target->GetItemInterface()->RemoveItemAmt(5177 ,1);	//water
				p_target->GetItemInterface()->RemoveItemAmt(5175 ,1);	//earth
				p_target->GetItemInterface()->RemoveItemAmt(5176 ,1);	//fire
				p_target->GetItemInterface()->RemoveItemAmt(5178 ,1);	//air
			}
		}break;
		// Invincible
		case 72286:
		{
//			if( apply && p_target )
			{
				Player *p_target = GetPlayerTarget();
				Unit *m_target = unitTarget;
				if(p_target->HasSpell(34091) )
				{
					if( ( m_target->GetMapMgr()->GetMapId() == 530 || m_target->GetMapMgr()->GetMapId() == 571) )
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 72284 ),true);
					else
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 72282 ),true);
				}
				else if(p_target->HasSpell(34090) )
				{
					if( ( m_target->GetMapMgr()->GetMapId() == 530 || m_target->GetMapMgr()->GetMapId() == 571) )
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 72283 ),true);
					else
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 72281 ),true);
				}	
				else if(p_target->HasSpell(33391))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 72282 ),true);
				}
				else if(p_target->HasSpell(33388))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 72281 ),true);
				}
			}
//			else
//			{
//				m_target->RemoveAura(72281);
//				m_target->RemoveAura(72282);
//				m_target->RemoveAura(72283);
//				m_target->RemoveAura(72284);
//			}
		}break;
		// Celestial Steed
		case 75614:
		{
//			if( apply && p_target)
			{
				Player *p_target = GetPlayerTarget();
				Unit *m_target = unitTarget;
				if(p_target->HasSpell(34090) )
				{
					if( ( m_target->GetMapMgr()->GetMapId() == 530 || m_target->GetMapMgr()->GetMapId() == 571) )
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 75618 ),true);
					else
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 76153 ),true);
				}
				else if(p_target->HasSpell(34091) )
				{
					if( ( m_target->GetMapMgr()->GetMapId() == 530 || m_target->GetMapMgr()->GetMapId() == 571) )
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 75617 ),true);
					else
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 75620 ),true);
				}
				else if(p_target->HasSpell(33391))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 75620 ),true);
				}
				else if(p_target->HasSpell(33388))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 75617 ),true);
				}
			}
//			else
//			{
//				m_target->RemoveAura(75618);
//				m_target->RemoveAura(75617);
//				m_target->RemoveAura(75620);
//				m_target->RemoveAura(75619);
//			}
		}break;
		// Headless Horseman's Mount
		case 48025:
		{
//			if( apply && p_target)
			{
				Player *p_target = GetPlayerTarget();
				Unit *m_target = unitTarget;
				if(p_target->HasSpell(34091) )
				{
					if( ( m_target->GetMapMgr()->GetMapId() == 530 || m_target->GetMapMgr()->GetMapId() == 571) )
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 48023 ),true);
					else
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 48024 ),true);
				}
				else if(p_target->HasSpell(34090) )
				{
					if( ( m_target->GetMapMgr()->GetMapId() == 530 || m_target->GetMapMgr()->GetMapId() == 571) )
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 51617 ),true);
					else
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 48024 ),true);
				}
				else if(p_target->HasSpell(33391))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 48024 ),true);
				}
				else if(p_target->HasSpell(33388))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 51621 ),true);
				}
			}
//			else
//			{
//				m_target->RemoveAura(75618);
//				m_target->RemoveAura(75617);
//				m_target->RemoveAura(75620);
//				m_target->RemoveAura(75619);
//			}
		}break;
		// Winged Steed of the Ebon Blade
		case 54729:
		{
//			if( apply && p_target )
			{
				Player *p_target = GetPlayerTarget();
				Unit *m_target = unitTarget;
				if(p_target->HasSpell(34091))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 54727 ),true);
				}
				else
//					if(p_target->HasSpell(34090))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 54726 ),true);
				}
			}
//			else
//			{
//				m_target->RemoveAura(54727);
//				m_target->RemoveAura(54726);
//			}
		}break;
		// Big Love Rocket
		case 71342:
		{
//			if( apply && p_target )
			{
				Player *p_target = GetPlayerTarget();
				Unit *m_target = unitTarget;
				if(p_target->HasSpell(33391) )
				{
					if( ( m_target->GetMapMgr()->GetMapId() == 530 || m_target->GetMapMgr()->GetMapId() == 571) )
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 71347 ),true);
					else
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 71345 ),true);
				}
				else if(p_target->HasSpell(33388))
				{
					if( ( m_target->GetMapMgr()->GetMapId() == 530 || m_target->GetMapMgr()->GetMapId() == 571) )
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 71346 ),true);
					else
						p_target->CastSpell(p_target,dbcSpell.LookupEntry( 71344 ),true);
				}
				else if(p_target->HasSpell(34091))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 71345 ),true);
				}
				else if(p_target->HasSpell(34090))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 71344 ),true);
				}
				else
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 71343 ),true);
				}
			}
//			else
//			{
//				m_target->RemoveAura(71347);
//				m_target->RemoveAura(71346);
//				m_target->RemoveAura(71345);
//				m_target->RemoveAura(71344);
//				m_target->RemoveAura(71343);
//			}
		}break;
		// X-53 Touring Rocket
		case 75973:
		{
//			if( apply && p_target )
			{
				Player *p_target = GetPlayerTarget();
				Unit *m_target = unitTarget;
				if(p_target->HasSpell(34091) && ( m_target->GetMapMgr()->GetMapId() == 530 || m_target->GetMapMgr()->GetMapId() == 571 ) )
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 75972 ),true);
				}
				else if(p_target->HasSpell(34090) && ( m_target->GetMapMgr()->GetMapId() == 530 || m_target->GetMapMgr()->GetMapId() == 571 ) )
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 75957 ),true);
				}
			}
//			else
//			{
//				m_target->RemoveAura(75972);
//				m_target->RemoveAura(75957);
//			}
		}break;
		// Blazing Hippogryph
		case 74856:
		{
//			if( apply )
			{
				Player *p_target = GetPlayerTarget();
				Unit *m_target = unitTarget;
				if(p_target->HasSpell(34091))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 74855 ),true);
				}
				else if(p_target->HasSpell(34090))
				{
					p_target->CastSpell(p_target,dbcSpell.LookupEntry( 74854 ),true);
				}
			}
//			else
//			{
//				m_target->RemoveAura(74855);
//				m_target->RemoveAura(74854);
//			}
		}break;
		// Magic Rooster
		case 65917:
		{
//			if( apply )
			{
				Player *p_target = GetPlayerTarget();
				p_target->CastSpell(p_target,dbcSpell.LookupEntry( 66122 ),true);
			}
//			else
			{
//				m_target->RemoveAura(66122);
			}
		}break;
		//haunt
		case 48181:
		case 59161:
		case 59163:
		case 59164:
			{
				if( p_caster )
				{
					//effect1 should have made a dmg, unless some proc messed it up we should be able to get that
					uint32 eff1_dmg = p_caster->m_dmg_made_last_time;
					ProcTriggerSpell *pts= new ProcTriggerSpell( GetProto() );
					pts->procFlags = PROC_ON_AURA_REMOVE;
					pts->caster = p_caster->GetGUID();	//we will deal dmg on this guy
					pts->procChance = 100;
					pts->procCharges = 1;
					pts->created_with_value = eff1_dmg;
					//pts.spellId = 48210;		//we will use this for all spells since we need to force deal dmg to friendly
					pts->spellId = 50091;		//we will use this for all spells since we need to force deal dmg to friendly
					unitTarget->m_procSpells.push_front(pts);
				}
			}break;
		//Everlasting Affliction
		case 47422:
			{
				Aura *a = unitTarget->FindAuraByNameHash( SPELL_HASH_CORRUPTION, u_caster->GetGUID() );
				if( a )
				{
					a->ResetTimeLeft();
					sEventMgr.ModifyEventTimeLeft(a, EVENT_AURA_REMOVE, a->GetDuration());
					unitTarget->ModVisualAuraStackCount(a, 0);
				}
			}break;
		//master's call
		case 53271:
			{
				if( u_caster )
				{
					u_caster->RemoveAllAurasByMechanic( MECHANIC_ROOTED , (uint32)(-1) , false );
					u_caster->RemoveAllAurasByMechanic( MECHANIC_ENSNARED , (uint32)(-1) , false );
					u_caster->RemoveAllAurasByMechanic( MECHANIC_FROZEN , (uint32)(-1) , false );
					for(uint32 x= MAX_POSITIVE_AURAS; x < MAX_NEGATIVE_AURAS1(u_caster); ++x)
						if(u_caster->m_auras[x])
							for(uint32 y = 0; y < 3; ++y)
								switch(u_caster->m_auras[x]->GetSpellProto()->EffectApplyAuraName[y])
								{
									case SPELL_AURA_MOD_ROOT:
									case SPELL_AURA_MOD_DECREASE_SPEED:
										u_caster->m_auras[x]->Remove();
										y=100;	//removed aura, do not use it anymore !
								}
				}
			}break;
		//there is no break here !!! we remove auras from target too !
		//Escape Artist
		case 20589:
			{
				if( unitTarget )
				{
					unitTarget->RemoveAllAurasByMechanic( MECHANIC_ROOTED , (uint32)(-1) , false );
					unitTarget->RemoveAllAurasByMechanic( MECHANIC_ENSNARED , (uint32)(-1) , false );
					unitTarget->RemoveAllAurasByMechanic( MECHANIC_FROZEN , (uint32)(-1) , false );
					for(uint32 x= MAX_POSITIVE_AURAS; x < MAX_NEGATIVE_AURAS1(unitTarget); ++x)
						if(unitTarget->m_auras[x])
							for(uint32 y = 0; y < 3; ++y)
								switch(unitTarget->m_auras[x]->GetSpellProto()->EffectApplyAuraName[y])
								{
									case SPELL_AURA_MOD_ROOT:
									case SPELL_AURA_MOD_DECREASE_SPEED:
										unitTarget->m_auras[x]->Remove();
										y=100;	//removed aura, do not use it anymore !
								}
				}
			}break;
		//chimera shot
		case 53209:
			{
				if( u_caster &&  unitTarget )
				{
					Aura *a;
					a = unitTarget->FindAuraByNameHash( SPELL_HASH_VIPER_STING );
					if( a )
					{
						a->ResetTimeLeft();
						sEventMgr.ModifyEventTimeLeft(a, EVENT_AURA_REMOVE, a->GetDuration());
						unitTarget->ModVisualAuraStackCount(a, 0);
						u_caster->Energize( u_caster, 53358, unitTarget->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) * 4 / 100 * 60 / 100, POWER_TYPE_MANA );
					}
					else
					{
						a = unitTarget->FindAuraByNameHash( SPELL_HASH_SCORPID_STING );
						if( a )
						{
							a->ResetTimeLeft();
							sEventMgr.ModifyEventTimeLeft(a, EVENT_AURA_REMOVE, a->GetDuration());
							unitTarget->ModVisualAuraStackCount(a, 0);
							u_caster->CastSpell( unitTarget, 53359, true );
						}
						else
						{
							a = unitTarget->FindAuraByNameHash( SPELL_HASH_SERPENT_STING );
							if( a )
							{
								a->ResetTimeLeft();
								sEventMgr.ModifyEventTimeLeft(a, EVENT_AURA_REMOVE, a->GetDuration());
								unitTarget->ModVisualAuraStackCount(a, 0);
								u_caster->SpellNonMeleeDamageLog( unitTarget, 53353, a->m_modList[0].m_amount * 5 * 40 / 100, true );
							}
						}
					}
				}
			}break;
		//Pestilence
		case 50842: //take diseases from target and spread to nearby targets
		{
			Unit *attacktarget = m_caster->GetMapMgr()->GetUnit( m_targets.m_unitTarget );
			if( attacktarget == NULL && p_caster )
				attacktarget = m_caster->GetMapMgr()->GetUnit( p_caster->GetSelection() );
			if( attacktarget )
			{
				Aura *ta,*aur;
				ta = attacktarget->FindAuraByNameHash( SPELL_HASH_FROST_FEVER ); //frost feaver
				if( ta )
				{
					aur = AuraPool.PooledNew();
					aur->Init( ta->GetSpellProto(), ta->GetDuration(), u_caster, unitTarget );
					unitTarget->AddAura(aur);
				}
				ta = attacktarget->FindAura( SPELL_HASH_BLOOD_PLAGUE ); //blood plague
				if( ta )
				{
					aur = AuraPool.PooledNew();
					aur->Init( ta->GetSpellProto(), ta->GetDuration(), u_caster, unitTarget );
					unitTarget->AddAura(aur);
				}
			}
		}break;
		//improved sprint
		case 30918:
			{
				if( !u_caster )
					return;
				for( uint32 x = MAX_POSITIVE_AURAS; x < MAX_NEGATIVE_AURAS1(u_caster); x++ )
				{
					if( u_caster->m_auras[x] != NULL )
					{
						if( u_caster->m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ROOTED 
							|| u_caster->m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ENSNARED ) // Remove roots and slow spells
						{
							u_caster->m_auras[x]->Remove();
						}
						else // if got immunity for slow, remove some that are not in the mechanics
						{
							for( int i = 0; i < 3; i++ )
							{
								if( u_caster->m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_DECREASE_SPEED 
									|| u_caster->m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_ROOT )
								{
									u_caster->m_auras[x]->Remove();
									break;
								}
							}
						}
				   }
				}
			}break;
	// Arcane Missiles
	/*
	case 5143://Rank 1
	case 5144://Rank 2
	case 5145://Rank 3
	case 8416://Rank 4
	case 8417://Rank 5
	case 10211://Rank 6
	case 10212://Rank 7
	case 25345://Rank 8
	{
		if(m_tmpAffect == 0)
		{
			Affect* aff = new Affect(GetProto(),GetDuration(sSpellDuration.LookupEntry(GetProto()->DurationIndex)),m_GetGUID(),m_caster);
			m_tmpAffect = aff;
		}
		if(GetProto()->EffectBasePoints[0] < 0)
			m_tmpAffect->SetNegative();

		m_tmpAffect->SetPeriodicTriggerSpell(GetProto()->EffectTriggerSpell[0],GetProto()->EffectAmplitude[0],damage);
	}break;
	*/

//	case SPELL_HASH_DEMONIC_EMPOWERMENT:	//no namehash to avoid cyclic cast !
	case 47193:	//demonic empowerment
	{
		if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 416 ) //in case it is imp
			unitTarget->CastSpell( unitTarget, 54444, true );
		else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1860 ) //VoidWalker
			unitTarget->CastSpell( unitTarget, 54443, true );
		else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1863 ) //Succubus
			unitTarget->CastSpell( unitTarget, 54436, true );
		else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 417 ) //Felhunter
			unitTarget->CastSpell( unitTarget, 54509, true );
		else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 17252 ) //Felguard
			unitTarget->CastSpell( unitTarget, 54508, true );
	}break;
	// Warlock Healthstones, just how much health does a lock need?
	case 6201:		// Minor Healthstone
		if( !p_caster )
			return;
		if (p_caster->HasSpell(18692))
		{
			CreateItem(19004);
			break;
		}
		if (p_caster->HasSpell(18693))
		{
			CreateItem(19005);
			break;
		}
		CreateItem(5512);
		break;
	case 6202:		// Lesser Healthstone
		if( !p_caster )
			return;
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(19007);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(19006);
			break;
		}
		CreateItem(5511);
		break;
	case 5699:		// Healthstone
		if( !p_caster )
			return;
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(19009);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(19008);
			break;
		}
		CreateItem(5509);
		break;
	case 11729:		// Greater Healthstone
		if( !p_caster )
			return;
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(19011);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(19010);
			break;
		}
		CreateItem(5510);
		break;
	case 11730:		// Major Healthstone
		if( !p_caster )
			return;
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(19013);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(19012);
			break;
		}
		CreateItem(9421);
		break;
	case 27230:		// Master Healthstone
		if( !p_caster )
			return;
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(22105);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(22104);
			break;
		}
		CreateItem(22103);
		break;
	case 47871:		// Demonic Healthstone
		if( !p_caster )
			return;
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(36891);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(36890);
			break;
		}
		CreateItem(36889);
		break;
	case 47878:		// Fel Healthstone
		if( !p_caster )
			return;
		if (p_caster->HasSpell(18693))	// Improved Healthstone (2)
		{
			CreateItem(36894);
			break;
		}
		if (p_caster->HasSpell(18692))	// Improved Healthstone (1)
		{
			CreateItem(36893);
			break;
		}
		CreateItem(36892);
		break;

	// Holy Light
	case 635:
	case 639:
	case 647:
	case 1026:
	case 1042:
	case 3472:
	case 10328:
	case 10329:
	case 10348:
	case 25292:
	case 27135:
	case 27136:
	case 48781:
	case 48782:
	//Flash of light
	case 19750:
	case 19939:
	case 19940:
	case 19941:
	case 19942:
	case 19943:
	case 27137:
	case 48784:
	case 48785:
		if( u_caster->HasAura( 20216 ) )
			Heal((int32)damage, true);
		else
			Heal((int32)damage);
	break;

	// Judgement
	case 53407:	//Judgement of Justice - preventing them from fleeing and limiting their movement speed
		{
			if( unitTarget )
				for(uint32 x= MAX_POSITIVE_AURAS; x < MAX_NEGATIVE_AURAS1(unitTarget); ++x)
					if(unitTarget->m_auras[x])
						for(uint32 y = 0; y < 3; ++y)
							switch(unitTarget->m_auras[x]->GetSpellProto()->EffectApplyAuraName[y])
							{
								case SPELL_AURA_MOD_INCREASE_SPEED:
								case SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED:
									unitTarget->m_auras[x]->Remove();
									y=100;	//removed aura, do not use it anymore !
							}	
		} //no beak, continue execution !
	case 20271: //Judgement of Light - granting attacks made against the judged enemy a chance of healing the attacker for [0.10 * SPH + 0.10 * AP].
	case 53408: //Judgement of Wisdom - giving each attack a chance to restore 2% of the attacker's base mana. 
		{
			if(!unitTarget || !p_caster)
			{ 
				return;
			}

			//get my seal from target
			uint32 judgespell = 0;
			for(uint32 buffitr=FIRST_AURA_SLOT;buffitr<MAX_POSITIVE_AURAS1(p_caster);buffitr++)
				if( p_caster->m_auras[ buffitr ] 
					&& ( p_caster->m_auras[ buffitr ]->GetSpellProto()->BGR_one_buff_on_target & SPELL_TYPE_SEAL ) )
				{
					judgespell = p_caster->m_auras[ buffitr ]->GetSpellProto()->NameHash;
					break;
				}
			
			if( judgespell == SPELL_HASH_SEAL_OF_BLOOD || judgespell == SPELL_HASH_SEAL_OF_THE_MARTYR)
			{
				//instantly causing ${0.26*$mw+0.11*$AP+0.18*$SPH} to ${0.26*$MW+0.11*$AP+0.18*$SPH} Holy damage at the cost of health equal to 33% of the damage caused.
				Item *it;
				float MVS = 0;
				if(p_caster->GetItemInterface())
				{
					it = p_caster->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
					if(it)
						MVS = ( it->GetProto()->Delay + 75 ) / 1000.0f; //yeah that 75 is really strange but at this time it produces blizzlike value :S
				}
				else MVS = p_caster->GetUInt32Value( UNIT_FIELD_BASEATTACKTIME ) / 1000.0f;
				uint32 dmg_to_be_done = (uint32)(0.26f*MVS + p_caster->GetAP()*0.11f + 0.18f*p_caster->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SCHOOL_HOLY));
				int32 HP_before = unitTarget->GetUInt32Value( UNIT_FIELD_HEALTH );
				p_caster->SpellNonMeleeDamageLog(unitTarget,GetProto()->Id,dmg_to_be_done,true,false,false);
				int32 HP_after = unitTarget->GetUInt32Value( UNIT_FIELD_HEALTH );
				uint32 self_dmg = abs(HP_after-HP_before) * 33 / 100;
				p_caster->SpellNonMeleeDamageLog(p_caster,GetProto()->Id,self_dmg,true,false,false);
			}
			else if( judgespell == SPELL_HASH_SEAL_OF_CORRUPTION || judgespell == SPELL_HASH_SEAL_OF_VENGEANCE)
			{
				//will deal ${1+0.22*$SPH+0.14*$AP} Holy damage to an enemy, increased by 10% for each application of Blood Corruption on the target.
				uint32 dmg_to_be_done = 1 + uint32(p_caster->GetAP()*0.14f + 0.22f*p_caster->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SCHOOL_HOLY));
				uint32 aura_count = unitTarget->CountAura( 53742 ); //SPELL_HASH_SEAL_OF_CORRUPTION
				if( aura_count == 0 )
					aura_count = unitTarget->CountAura( 31803 ); //SPELL_HASH_SEAL_OF_VENGEANCE
				aura_count++;
				dmg_to_be_done = dmg_to_be_done * 10 * aura_count / 100;
				p_caster->SpellNonMeleeDamageLog(unitTarget,GetProto()->Id,dmg_to_be_done,true,false,false);
			}
			else if( judgespell == SPELL_HASH_SEAL_OF_JUSTICE || judgespell == SPELL_HASH_SEAL_OF_LIGHT || judgespell == SPELL_HASH_SEAL_OF_WISDOM)
			{
				//will deal ${1+0.25*$SPH+0.16*$AP} Holy damage to an enemy.
				uint32 dmg_to_be_done = 1 + (uint32)(p_caster->GetAP()*0.16f + 0.25f*p_caster->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SCHOOL_HOLY));
				p_caster->SpellNonMeleeDamageLog(unitTarget,GetProto()->Id,dmg_to_be_done,true,false,false);
			}
			else if( judgespell == SPELL_HASH_SEAL_OF_RIGHTEOUSNESS)
			{
				//will cause ${1+0.2*$AP+0.32*$SPH} Holy damage to an enemy.
				uint32 dmg_to_be_done = 1 + (uint32)(p_caster->GetAP()*0.2f + 0.32f*p_caster->GetUInt32Value(PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SCHOOL_HOLY));
				p_caster->SpellNonMeleeDamageLog(unitTarget,GetProto()->Id,dmg_to_be_done,true,false,false);
			}
		}break;
	//warlock - Master Demonologist
	case 23784:
		{
			if( p_caster == NULL || unitTarget == NULL)
				return; //can't imagine how this talent got to anybody else then a player casted on pet
			uint32 casted_spell_id = 0 ;
			uint32 inc_resist_by_level = 0 ;
			uint32 inc_resist_by_level_spell = 0 ;
			if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 416 ) //in case it is imp
				casted_spell_id = 23759 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1860 ) //VoidWalker
				casted_spell_id = 23760 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1863 ) //Succubus
				casted_spell_id = 23761 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 417 ) //Felhunter
			{
				casted_spell_id = 0 ;
				inc_resist_by_level_spell = 23762 ;
				inc_resist_by_level = 20 ;
			}
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 17252 ) //Felguard
			{
				casted_spell_id = 35702 ;
				inc_resist_by_level_spell = 23762 ;
				inc_resist_by_level = 10 ;
			}
			if( casted_spell_id )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				sp->Init( p_caster, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				sp->Init(  unitTarget, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
			if( inc_resist_by_level_spell )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				sp->Init( p_caster, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				sp->Init( unitTarget, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
		}break;
	case 23830:
		{
			if( p_caster == NULL || unitTarget == NULL)
				return; //can't imagine how this talent got to anybody else then a player casted on pet
			uint32 casted_spell_id = 0 ;
			uint32 inc_resist_by_level = 0 ;
			uint32 inc_resist_by_level_spell = 0 ;
			if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 416 ) //in case it is imp
				casted_spell_id = 23826 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1860 ) //VoidWalker
				casted_spell_id = 23841 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1863 ) //Succubus
				casted_spell_id = 23833 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 417 ) //Felhunter
			{
				casted_spell_id = 1 ;
				inc_resist_by_level_spell = 23837 ;
				inc_resist_by_level = 40 ;
			}
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 17252 ) //Felguard
			{
				casted_spell_id = 35703 ;
				inc_resist_by_level_spell = 23837 ;
				inc_resist_by_level = 20 ;
			}
			if( casted_spell_id )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				sp->Init( p_caster, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				sp->Init(  unitTarget, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
			if( inc_resist_by_level_spell )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				sp->Init( p_caster, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				sp->Init( unitTarget, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
		}break;
	case 23831:
		{
			if( p_caster == NULL || unitTarget == NULL)
				return; //can't imagine how this talent got to anybody else then a player casted on pet
			uint32 casted_spell_id = 0 ;
			uint32 inc_resist_by_level = 0 ;
			uint32 inc_resist_by_level_spell = 0 ;
			if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 416 ) //in case it is imp
				casted_spell_id = 23827 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1860 ) //VoidWalker
				casted_spell_id = 23842 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1863 ) //Succubus
				casted_spell_id = 23834 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 417 ) //Felhunter
			{
				casted_spell_id = 0 ;
				inc_resist_by_level_spell = 23838 ;
				inc_resist_by_level = 60 ;
			}
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 17252 ) //Felguard
			{
				casted_spell_id = 35704 ;
				inc_resist_by_level_spell = 23838 ;
				inc_resist_by_level = 30 ;
			}
			if( casted_spell_id )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				sp->Init( p_caster, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				sp->Init(  unitTarget, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
			if( inc_resist_by_level_spell )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				sp->Init( p_caster, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				sp->Init( unitTarget, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
		}break;
	case 23832:
		{
			if( p_caster == NULL || unitTarget == NULL)
				return; //can't imagine how this talent got to anybody else then a player casted on pet
			uint32 casted_spell_id = 0 ;
			uint32 inc_resist_by_level = 0 ;
			uint32 inc_resist_by_level_spell = 0 ;
			if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 416 ) //in case it is imp
				casted_spell_id = 23828 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1860 ) //VoidWalker
				casted_spell_id = 23843 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1863 ) //Succubus
				casted_spell_id = 23835 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 417 ) //Felhunter
			{
				casted_spell_id = 0 ;
				inc_resist_by_level_spell = 23839 ;
				inc_resist_by_level = 80 ;
			}
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 17252 ) //Felguard
			{
				casted_spell_id = 35705 ;
				inc_resist_by_level_spell = 23839 ;
				inc_resist_by_level = 40 ;
			}
			if( casted_spell_id )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				sp->Init( p_caster, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				sp->Init(  unitTarget, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
			if( inc_resist_by_level_spell )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				sp->Init( p_caster, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				sp->Init( unitTarget, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
		}break;
/*		case 34026: //Hunter: Kill Command
		{
			// in this case unitTarget == pet
			if( p_caster == NULL || unitTarget == NULL || unitTarget->getDeathState() != ALIVE )
				return;

			AI_Spell* Sp = SafePetCast( unitTarget )->CreateAISpell( dbcSpell.LookupEntry( 34027 ) );

			Unit* tgt = p_caster->GetMapMgr()->GetUnit( p_caster->GetSelection() );

			if( tgt != NULL && isAttackable( p_caster, tgt ) )
			{
				unitTarget->GetAIInterface()->AttackReaction( tgt, 1 );
				unitTarget->GetAIInterface()->SetNextTarget( tgt );
			}
			else if( unitTarget->CombatStatus.GetPrimaryAttackTarget() == 0 )
				return;				
			unitTarget->GetAIInterface()->SetNextSpell( Sp );
			//TODO: Kill Command - return to previous pet target after cast

         }break; */
		case 35708:
		{
			if( p_caster == NULL || unitTarget == NULL)
				return; //can't imagine how this talent got to anybody else then a player casted on pet
			uint32 casted_spell_id = 0 ;
			uint32 inc_resist_by_level = 0 ;
			uint32 inc_resist_by_level_spell = 0 ;
			if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 416 ) //in case it is imp
				casted_spell_id = 23829 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1860 ) //VoidWalker
				casted_spell_id = 23844 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 1863 ) //Succubus
				casted_spell_id = 23836 ;
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 417 ) //Felhunter
			{
				casted_spell_id = 0 ;
				inc_resist_by_level_spell = 23840 ;
				inc_resist_by_level = 100 ;
			}
			else if ( unitTarget->GetUInt32Value( OBJECT_FIELD_ENTRY ) == 17252 ) //Felguard
			{
				casted_spell_id = 35706 ;
				inc_resist_by_level_spell = 23840 ;
				inc_resist_by_level = 50 ;
			}
			if( casted_spell_id )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				sp->Init( p_caster, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				sp->Init(  unitTarget, dbcSpell.LookupEntry( casted_spell_id ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
			if( inc_resist_by_level_spell )
			{
				//for self
				Spell *sp = SpellPool.PooledNew();
				sp->Init( p_caster, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt( p_caster->GetGUID() );
				sp->prepare( &tgt );
				//for pet
				sp = SpellPool.PooledNew();
				sp->Init( unitTarget, dbcSpell.LookupEntry( inc_resist_by_level_spell ), true, NULL );
				SpellCastTargets tgt1( unitTarget->GetGUID() );
				sp->prepare( &tgt1 );
			}
		}break;
	}
}

void Spell::SpellEffectSanctuary(uint32 i) // Stop all attacks made to you
{
	if(!u_caster)
	{ 
		return;
	}

	//warning this causes crashes !
//	Object::InRangeSet::iterator itr = u_caster->GetInRangeOppFactsSetBegin();
//	Object::InRangeSet::iterator itr_end = u_caster->GetInRangeOppFactsSetEnd();
	//use these instead
	Object::InRangeSet::iterator itr = u_caster->GetInRangeSetBegin();
	Object::InRangeSet::iterator itr_end = u_caster->GetInRangeSetEnd();
	Unit * pUnit;

	if(u_caster->IsPlayer())
		SafePlayerCast(u_caster)->RemoveAllAuraType(SPELL_AURA_MOD_ROOT);

	for( ; itr != itr_end; ++itr )
		if( (*itr)->IsUnit() )
		{
			pUnit = SafeUnitCast(*itr);

			if( pUnit && pUnit->GetTypeId() == TYPEID_UNIT )
				pUnit->GetAIInterface()->RemoveThreatByPtr( unitTarget );
		}
}

void Spell::SpellEffectAddComboPoints(uint32 i) // Add Combo Points
{
	if(!p_caster)
	{ 
		return;
	}
  
	//if this is a procspell Ruthlessness (maybe others later)
	if(pSpellId && GetProto()->Id==14157)
	{
		//it seems this combo adding procspell is going to change combopoint count before they will get reseted. We add it after the reset
		/* burlex - this is wrong, and exploitable.. :/ if someone uses this they will have unlimited combo points */
		//re-enabled this by Zack. Explained why it is used + recheked to make sure initialization is good ...
		// while casting a spell talent will trigger uppon the spell prepare faze
		// the effect of the talent is to add 1 combo point but when triggering spell finishes it will clear the extra combo point
		p_caster->m_spellcomboPoints += damage;
		return;
	}
	p_caster->AddComboPoints(p_caster->GetSelection(), damage);
}

void Spell::SpellEffectCreateHouse(uint32 i) // Create House
{


}

void Spell::SpellEffectDuel(uint32 i) // Duel
{
	if(!p_caster)
	{ 
		return;
	}
	if(!p_caster->isAlive())
	{ 
		return;
	}

	if (p_caster->IsStealth())
	{
		SendCastResult(SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED);
		return; // Player is stealth
	}
	if(!playerTarget)
	{ 
		return;
	}
	if(playerTarget == p_caster)
	{ 
		return;
	}

	/* not implemented yet
	TODO: dueling zones ? ( SPELL_FAILED_NO_DUELING )
	if (player->IsInvisible())
	{
		SendCastResult(SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE);
		return;
	}
	*/

	//Player *pTarget = sObjHolder.GetObject<Player>(player->GetSelection());	   //  hacky.. and will screw up if plr is deselected..
	if (!playerTarget)
	{
		SendCastResult(SPELL_FAILED_BAD_TARGETS);
		return; // invalid Target
	}
	if (!playerTarget->isAlive())
	{
		SendCastResult(SPELL_FAILED_TARGETS_DEAD);
		return; // Target not alive
	}
	if (playerTarget->hasStateFlag(UF_ATTACKING))
	{
		SendCastResult(SPELL_FAILED_TARGET_IN_COMBAT);
		return; // Target in combat with another unit
	}
	if (playerTarget->DuelingWith != NULL)
	{
		SendCastResult(SPELL_FAILED_TARGET_DUELING);
		return; // Already Dueling
	}
	if (playerTarget->m_bg != NULL)
	{
		SendCastResult(SPELL_FAILED_NOT_HERE);
		return; // Already Dueling
	}

	p_caster->RequestDuel(playerTarget);
}

void Spell::SpellEffectStuck(uint32 i)
{
    if(!playerTarget || playerTarget != p_caster)
    { 
        return;
    }

	//remove all auras from him
	for(uint32 buffitr=0;buffitr<MAX_AURAS;buffitr++)
		if( playerTarget->m_auras[ buffitr ] )
			playerTarget->m_auras[ buffitr ]->Remove();

	//revive player to avoid all those tickets about being stuck
	playerTarget->ResurrectPlayer();

	//some noobs miss bind location so we force them in main city
	if( playerTarget->GetBindPositionX() == 0 ) 
	{
		if( playerTarget->GetTeam() == 0 )
			playerTarget->SetBindPoint( -9100,406,93,0,0);
		else
			playerTarget->SetBindPoint( 1371,-4370,27,1,0);
	}

	sEventMgr.AddEvent(playerTarget,&Player::EventTeleport,playerTarget->GetBindMapId(),playerTarget->GetBindPositionX(),playerTarget->GetBindPositionY(),
		playerTarget->GetBindPositionZ(),EVENT_PLAYER_TELEPORT,50,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	/*
	playerTarget->SafeTeleport(playerTarget->GetBindMapId(), 0, playerTarget->GetBindPositionX(), playerTarget->GetBindPositionY(), playerTarget->GetBindPositionZ(), 3.14f);*/
}

void Spell::SpellEffectSummonPlayer(uint32 i)
{
	if( playerTarget == NULL )
	{ 
		return;
	}

	// vojta: from 2.4 players can be summoned on another map
	//if( m_caster->GetMapMgr()->GetMapInfo() && m_caster->GetMapMgr()->GetMapInfo()->type != INSTANCE_NULL && m_caster->GetMapId() != playerTarget->GetMapId())
	//	return;
	if ( m_caster->GetMapMgr()->GetMapInfo() && playerTarget->getLevel() < m_caster->GetMapMgr()->GetMapInfo()->minlevel ) // we need some blizzlike message that player needs level xx - feel free to add it ;)
	{ 
		return;
	}

	playerTarget->SummonRequest( m_caster->GetLowGUID(), m_caster->GetZoneId(), m_caster->GetMapId(), m_caster->GetInstanceID(), m_caster->GetPosition() );
}

void Spell::SpellEffectActivateObject(uint32 i) // Activate Object
{
	/*if(!p_caster)
		return;

	if(!gameObjTarget)
		return;

	gameObjTarget->SetUInt32Value(GAMEOBJECT_DYNAMIC, 1);

	sEventMgr.AddEvent(gameObjTarget, &GameObject::Deactivate, EVENT_GAMEOBJECT_DEACTIVATE, GetDuration(), 1);*/
}

void Spell::SpellEffectSummonTotem(uint32 i) // Summon Totem
{
	if(!p_caster) 
	{ 
		return;
	}

	float x = p_caster->GetPositionX();
	float y = p_caster->GetPositionY();
	uint32 slot = m_spellInfo->EffectImplicitTargetA[i] - EFF_TARGET_TOTEM_EARTH;
	if(slot < 0 || slot > 3)
	{
		sLog.outDebug("Totem slot is : %u and max shoud be 3, i = %u , target = %u \n",slot,i,m_spellInfo->EffectImplicitTargetA[i]);
		return; // Just 4 totems
	}

	switch(m_spellInfo->EffectMiscValueB[i])
	{
	case 63: 
		x -= 1.5f;
		y -= 1.5f;
		break;
	case 81: 
		x -= 1.5f;
		y += 1.5f;
		break;
	case 82:  
		x += 1.5f;
		y -= 1.5f;
		break;
	case 83: 
		x += 1.5f;
		y += 1.5f;
		break;
	default:
		break;
	}

	if(p_caster->m_TotemSlots[slot] != 0)
		p_caster->m_TotemSlots[slot]->TotemExpire();

	uint32 entry = GetProto()->EffectMiscValue[i];

	CreatureInfo* ci = CreatureNameStorage.LookupEntry(entry);
	if(!ci)
	{
		sLog.outDebug("Missing totem creature entry : %u \n",entry);
		return;
	}

	// Obtain the spell we will be casting.
	TotemSpells *TotemSpell = ObjectMgr::getSingleton().GetTotemSpell(GetProto()->Id);
	if(TotemSpell == NULL) 
	{
		sLog.outDebug("Totem %u does not have any spells to cast, exiting\n",entry);
		return;
	}

	Creature * pTotem = p_caster->GetMapMgr()->CreateCreature(entry);

	p_caster->m_TotemSlots[slot] = pTotem;
	pTotem->SetTotemOwner(p_caster);
	pTotem->SetTotemSlot(slot);

	float landh = p_caster->GetMapMgr()->GetLandHeight(x,y);
	float landdiff = landh - p_caster->GetPositionZ();

	if ( landh != VMAP_VALUE_NOT_INITIALIZED || fabs(landdiff) > 4 )
		pTotem->Create(ci->Name, p_caster->GetMapId(), x, y, p_caster->GetPositionZ()+1, p_caster->GetOrientation());
	else
		pTotem->Create(ci->Name, p_caster->GetMapId(), x, y, landh, p_caster->GetOrientation());

	uint32 displayID = 0;

	if( p_caster->GetTeamInitial() == 0 )
	{
		if ( ci->Female_DisplayID != 0 )
		{
			displayID = ci->Female_DisplayID; //this is the nice solution provided by emsy
		}
		else //this is the case when you are using a blizzlike db
		{
			if( ci->Male_DisplayID == 4587 )
				displayID = 19075;
			else if( ci->Male_DisplayID == 4588 )
				displayID = 19073;
			else if( ci->Male_DisplayID == 4589 )
				displayID = 19074;
			else if( ci->Male_DisplayID == 4590 )
				displayID = 19071;
			else if( ci->Male_DisplayID == 4683 )
				displayID = 19074;
			else
				displayID = ci->Male_DisplayID;
		}
	}
	else
	{
		//orc special looks
		if( p_caster->getRace() == RACE_ORC )
		{
			if( ci->Male_DisplayID == 4587 )
				displayID = 30759;
			else if( ci->Male_DisplayID == 4588 )
				displayID = 30757;
			else if( ci->Male_DisplayID == 4589 )
				displayID = 30758;
			else if( ci->Male_DisplayID == 4590 )
				displayID = 30756;
			else
				displayID = ci->Male_DisplayID;
		}
		//troll special looks
		else if( p_caster->getRace() == RACE_TROLL )
		{
			if( ci->Male_DisplayID == 4587 )
				displayID = 30763;
			else if( ci->Male_DisplayID == 4588 )
				displayID = 30761;
			else if( ci->Male_DisplayID == 4589 )
				displayID = 30762;
			else if( ci->Male_DisplayID == 4590 )
				displayID = 30760;
			else
				displayID = ci->Male_DisplayID;
		}
		//rest
		else
			displayID = ci->Male_DisplayID;
	}

	// Set up the creature.
	pTotem->SetUInt32Value(OBJECT_FIELD_ENTRY, entry);
	pTotem->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
	pTotem->SetUInt64Value(UNIT_FIELD_CREATEDBY, p_caster->GetGUID());
	pTotem->SetUInt32Value(UNIT_FIELD_HEALTH, damage);
	pTotem->SetUInt32Value(UNIT_FIELD_MAXHEALTH, damage);
	pTotem->SetUInt32Value(UNIT_FIELD_POWER3, p_caster->getLevel() * 30);
	pTotem->SetUInt32Value(UNIT_FIELD_MAXPOWER3, p_caster->getLevel() * 30);
	pTotem->SetUInt32Value(UNIT_FIELD_LEVEL, p_caster->getLevel());
	pTotem->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, p_caster->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
//	pTotem->SetUInt32Value(UNIT_FIELD_BYTES_0, (1 << 8) | (2 << 16) | (1 << 24)); //race + class...
	pTotem->SetUInt32Value(UNIT_FIELD_BYTES_0, (p_caster->GetUInt32Value( UNIT_FIELD_BYTES_0 ) & 0x00FFFFFF) | (1 << 24));
//	pTotem->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED | UNIT_FLAG_SELF_RES);
	pTotem->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED );
	pTotem->SetUInt32Value(UNIT_FIELD_BASEATTACKTIME, 2000);
	pTotem->SetUInt32Value(UNIT_FIELD_BASEATTACKTIME_1, 2000);
	pTotem->SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 1.0f);
	pTotem->SetFloatValue(UNIT_FIELD_COMBATREACH, 1.0f);
	pTotem->SetUInt32Value(UNIT_FIELD_DISPLAYID, displayID);
	pTotem->SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, ci->Male_DisplayID); //blizzlike :P
	pTotem->SetFloatValue(UNIT_MOD_CAST_SPEED, 1.0f);
	pTotem->SetUInt32Value(UNIT_CREATED_BY_SPELL, GetProto()->Id);
	pTotem->SetUInt32Value(UNIT_FIELD_BYTES_2, 1 ); 
	//inherit pvp setting from owner
	if( p_caster && p_caster->IsPvPFlagged() )
		pTotem->SetPvPFlag();

	// Initialize faction stuff.
	pTotem->_setFaction();

	//added by Zack : Some shaman talents are casted on player but it should be inherited or something by totems
	pTotem->InheritSMMods(p_caster);

	// Totems get spell damage and healing bonus from the Shaman
	for(int school=0;school<7;school++)
	{
		pTotem->ModDamageDone[school] = (int32)(p_caster->GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS + school ) - (int32)p_caster->GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + school ));
//		pTotem->HealDoneMod[school] = p_caster->HealDoneMod[school];
	}
	pTotem->HealDoneMod = p_caster->HealDoneMod;
	for(uint32 a = 0; a < 5; a++)
		pTotem->HealDoneMod += float2int32(p_caster->SpellHealDoneByAttribute[a] * (float)p_caster->GetUInt32Value(UNIT_FIELD_STAT0 + a));
	pTotem->HealDonePctMod = p_caster->HealDonePctMod;
	// Set up AI, depending on our spells.
	uint32 j;
	for( j = 0; j < 3; ++j )
		if( TotemSpell->spells[0]->Effect[j] == SPELL_EFFECT_APPLY_AREA_AURA || TotemSpell->spells[0]->Effect[j] == SPELL_EFFECT_PERSISTENT_AREA_AURA || TotemSpell->spells[0]->EffectApplyAuraName[j] == SPELL_AURA_PERIODIC_TRIGGER_SPELL )
			break;
	// Setup complete. Add us to the world.
	pTotem->PushToWorld(m_caster->GetMapMgr());

	if(j != 3)
	{
		// We're an area aura. Simple. Disable AI and cast the spell.
		pTotem->DisableAI();
		pTotem->GetAIInterface()->totemspell = TotemSpell;

		Spell * pSpell = SpellPool.PooledNew();
		pSpell->Init(pTotem, TotemSpell->spells[0], true, 0);

		SpellCastTargets targets;
		targets.m_destX = pTotem->GetPositionX();
		targets.m_destY = pTotem->GetPositionY();
		targets.m_destZ = pTotem->GetPositionZ();
		targets.m_targetMask = TARGET_FLAG_DEST_LOCATION;

		pSpell->prepare(&targets);
	}
	else
	{
		// We're a casting totem. Switch AI on, and tell it to cast this spell.
		pTotem->EnableAI();
		pTotem->GetAIInterface()->Init(pTotem, AITYPE_TOTEM, MOVEMENTTYPE_NONE, p_caster);
		pTotem->GetAIInterface()->totemspell = TotemSpell;
		int32 totemspelltimer = 3000, totemspelltime = 3000;	// need a proper resource for this.

		switch(TotemSpell->spells[0]->Id)
		{
		case 8167: //Poison Cleansing Totem
		case 8172: //Disease Cleansing Totem
		{
			//Zack : wtf we are overwriting values from DB ?
//			if(TotemSpell->spells[0]->Id == 8167)
//				TotemSpell = dbcSpell.LookupEntry( 8168 );	// Better to use this spell
//			else
//				TotemSpell = dbcSpell.LookupEntry( 8171 );
			pTotem->GetAIInterface()->totemspell = TotemSpell;
			totemspelltime =  5000;
			totemspelltimer = 0; //First tick done immediately
			break;
		}
		case 8146: //Tremor Totem
		{
			totemspelltime = 3000;
			totemspelltimer = 0; //First tick done immediately
			break;
		}
		case 8178: //Grounding Totem
		case 3600: //Earthbind Totem
		{
			totemspelltimer = 0; //First tick done immediately
			break;
		}
		case 8349: //Fire Nova Totem 1
		case 8502: //Fire Nova Totem 2
		case 8503: //Fire Nova Totem 3
		case 11306: //Fire Nova Totem 4
		case 11307: //Fire Nova Totem 5
		case 25535: //Fire Nova Totem 6
		case 25537: //Fire Nova Totem 7
		{
			totemspelltimer =  4000;
			// Improved Fire Totems
			SM_FIValue(p_caster->SM_FDur, &totemspelltimer, TotemSpell->spells[0]->SpellGroupType);
			totemspelltime = totemspelltimer;
			break;
		}
		default:break;
		}

		pTotem->GetAIInterface()->m_totemspelltimer = totemspelltimer;
		pTotem->GetAIInterface()->m_totemspelltime = totemspelltime;
	}

	//in case these are our elemental totems then we should set them up
	if(GetProto()->Id==2062)
		pTotem->GetAIInterface()->Event_Summon_EE_totem(GetDuration());
	else if(GetProto()->Id==2894)
		pTotem->GetAIInterface()->Event_Summon_FE_totem(GetDuration());

//	pTotem->m_noRespawn = true;

	// Set up the deletion event. The totem needs to expire after a certain time, or upon its death.
	sEventMgr.AddEvent(pTotem, &Creature::TotemExpire, EVENT_TOTEM_EXPIRE, GetDuration()+100, 1,0);
}

void Spell::SpellEffectSelfResurrect(uint32 i)
{
	if(!p_caster || !playerTarget)
	{ 
		return;
	}
	if(playerTarget->isAlive())
	{ 
		return;
	}
	uint32 mana;
	uint32 health;
	uint32 class_=unitTarget->getClass();
	
	switch(GetProto()->Id)
	{
	case 3026:
	case 20758:
	case 20759:
	case 20760:
	case 20761:
	case 27240:
		{
			health = GetProto()->EffectMiscValue[i];
			mana = -damage;
		}break;
	case 21169: //Reincarnation. Ressurect with 20% health and mana
		{
			int32 amt = 20;
			if( (GetProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) )
			{
				SM_FIValue(unitTarget->SM_FMiscEffect,&amt,GetProto()->SpellGroupType);
				SM_PIValue(unitTarget->SM_PMiscEffect,&amt,GetProto()->SpellGroupType);
			}
			health = uint32((unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH)*amt)/100);
			mana = uint32((unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1)*amt)/100);
		}
		break;
	default:
		{
			if(damage < 0) 
			{ 
				health = -damage;
				mana = GetProto()->EffectMiscValue[i];
			}
			else
			{ 
				health = uint32(unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH)*damage/100);
				mana = uint32(unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1)*damage/100);
			}
		}break;
        }

	if(class_==WARRIOR||class_==ROGUE)
		mana=0;
	
	playerTarget->m_resurrectHealth = health;
	playerTarget->m_resurrectMana = mana;

	playerTarget->ResurrectPlayer();
	playerTarget->SetMovement(MOVE_UNROOT);

	playerTarget->SetUInt32Value(PLAYER_SELF_RES_SPELL, 0);

	if(GetProto()->Id==21169)
		AddCooldown();
}

void Spell::SpellEffectSkinning(uint32 i)
{
	if( unitTarget == NULL || unitTarget->IsPlayer() )
	{ 
		return;
	}

	uint32 sk = SafePlayerCast( m_caster )->_GetSkillLineCurrent( SKILL_SKINNING );
	uint32 lvl = unitTarget->getLevel();

	if( ( sk >= lvl * 5 ) || ( ( sk + 100 ) >= lvl * 10 ) )
	{
		//Fill loot for Skinning
//		lootmgr.FillSkinningLoot(&(SafeCreatureCast(unitTarget))->loot,unitTarget->GetEntry());
		if( (SafeCreatureCast(unitTarget))->DificultyProto && (SafeCreatureCast(unitTarget))->DificultyProto->loot_skin )
		{
			//dump normal loot
			SafeCreatureCast(unitTarget)->loot.items.clear();	
			SafeCreatureCast(unitTarget)->loot.gold = 0;
			//fill creature loot
			lootmgr.FillObjectLoot(unitTarget,SafeCreatureCast(unitTarget)->DificultyProto->loot_skin);
		}
		SafePlayerCast( m_caster )->SendLoot( unitTarget->GetGUID(), LOOT_SKINNING );
		
		//Not skinable again
		unitTarget->BuildFieldUpdatePacket( p_caster, UNIT_FIELD_FLAGS, 0 );

		//still lootable
		//pkt=unitTarget->BuildFieldUpdatePacket(UNIT_DYNAMIC_FLAGS,U_DYN_FLAG_LOOTABLE);
		//SafePlayerCast( m_caster )->GetSession()->SendPacket(pkt);
		//delete pkt;
		if (!SafeCreatureCast(unitTarget)->Skinned)
			DetermineSkillUp(SKILL_SKINNING,sk<lvl*5?sk/5:lvl);

		SafeCreatureCast(unitTarget)->Skinned = true;
	}
	else
	{
		SendCastResult(SPELL_FAILED_TARGET_UNSKINNABLE);
	}   
			
//	DetermineSkillUp(SKILL_SKINNING,unitTarget->getLevel());
}

void Spell::SpellEffectCharge(uint32 i)
{
	if(!unitTarget)
	{ 
		return;
	}
	//if(!p_caster) who said units can't charge? :P
	//	return;
	if(!unitTarget->isAlive())
	{ 
		return;
	}
	if (u_caster->IsStunned() || u_caster->m_rooted || u_caster->IsPacified() || u_caster->IsFeared())
	{ 
		return;
	}

	float x, y, z;
	float dx,dy;

	//if(unitTarget->GetTypeId() == TYPEID_UNIT)
	//	if(unitTarget->GetAIInterface())
	//		unitTarget->GetAIInterface()->StopMovement(5000);
	if(unitTarget->GetPositionX() == 0.0f || unitTarget->GetPositionY() == 0.0f)
	{ 
		return;
	}
	
	dx=unitTarget->GetPositionX()-m_caster->GetPositionX();
	dy=unitTarget->GetPositionY()-m_caster->GetPositionY();
	if(dx == 0.0f || dy == 0.0f)
	{ 
		return;
	}

	float d = sqrt(dx*dx+dy*dy)-unitTarget->GetFloatValue(UNIT_FIELD_BOUNDINGRADIUS)-m_caster->GetFloatValue(UNIT_FIELD_BOUNDINGRADIUS);
	float alpha = atanf(dy/dx);
	if(dx<0)
		alpha += float(M_PI);

	x = d*cosf(alpha)+m_caster->GetPositionX();
	y = d*sinf(alpha)+m_caster->GetPositionY();
	z = unitTarget->GetPositionZ();

	uint32 time = uint32( (m_caster->CalcDistance(unitTarget) / ((m_caster->m_runSpeed * 3.5) * 0.001f)) + 0.5);

	if( p_caster && p_caster->GetAIInterface() )
		p_caster->GetAIInterface()->SendMoveToPacket(x, y, z, alpha, time, MONSTER_MOVE_FLAG_RUN);
/*	WorldPacket data(SMSG_MONSTER_MOVE, 50);
	data << m_caster->GetNewGUID();
	data << uint8(0);
	data << m_caster->GetPositionX();
	data << m_caster->GetPositionY();
	data << m_caster->GetPositionZ();
	data << getMSTime();
	data << uint8(0x00);
	data << uint32(MONSTER_MOVE_FLAG_RUN);
	data << time;
	data << uint32(1);
	data << x << y << z;*/
	if(unitTarget->GetTypeId() == TYPEID_UNIT)
		unitTarget->GetAIInterface()->StopMovement(2000);

//	u_caster->SendMessageToSet(&data, true);   
	
	u_caster->SetPosition(x,y,z,alpha,true);
	u_caster->addStateFlag(UF_ATTACKING);
	u_caster ->smsg_AttackStart( unitTarget );
	u_caster->setAttackTimer(time, false);
	u_caster->setAttackTimer(time, true);

	// trigger an event to reset speedhack detection
	if( p_caster )
	{
		p_caster->EventAttackStart();
		p_caster->SpeedCheatDelay( time + 1000 );
		p_caster->z_axisposition = 0.0f;
	}
}

void Spell::SpellEffectPlayerPull( uint32 i )
{
	if( unitTarget == NULL || !unitTarget->isAlive() || !unitTarget->IsPlayer() )
	{ 
		return;
	}

	Player* p_target = SafePlayerCast( unitTarget );

	// calculate destination
	float pullD = p_target->CalcDistance( m_caster ) - p_target->GetFloatValue( UNIT_FIELD_BOUNDINGRADIUS ) - m_caster->GetFloatValue( UNIT_FIELD_BOUNDINGRADIUS ) - 1.0f;
	float pullO = p_target->calcRadAngle( p_target->GetPositionX(), p_target->GetPositionY(), m_caster->GetPositionX(), m_caster->GetPositionY() );
	float pullX = p_target->GetPositionX() + pullD * cosf( pullO );
	float pullY = p_target->GetPositionY() + pullD * sinf( pullO );
	float pullZ = m_caster->GetPositionZ() + 0.3f;
	uint32 time = uint32( pullD * 42.0f );

	p_target->SetOrientation( pullO );

	WorldPacket data( SMSG_MONSTER_MOVE, 60 );
	data << p_target->GetNewGUID();
	data << uint8(0);
	data << p_target->GetPositionX() << p_target->GetPositionY() << p_target->GetPositionZ();
	data << getMSTime();
	data << uint8( 4 );
	data << pullO;
	data << uint32( 0x00000100 );
	data << time;
	data << uint32( 1 );
	data << pullX << pullY << pullZ;

	p_target->SendMessageToSet( &data, true );   
}

void Spell::SpellEffectSummonCritter(uint32 i)
{
	if(!u_caster || u_caster->IsInWorld() == false)
	{ 
		return;
	}

	uint32 SummonCritterID = GetProto()->EffectMiscValue[i];

	// GetProto()->EffectDieSides[i] has something to do with dismissing our critter
	// when it is 1, it means to just dismiss it if we already have it
	// when it is 0, it could mean to always summon a new critter, but there seems to be exceptions

	if(u_caster->critterPet)
	{
		// if we already have this critter, we will just dismiss it and return
		if(u_caster->critterPet->GetCreatureInfo() && u_caster->critterPet->GetCreatureInfo()->Id == SummonCritterID)
		{
			u_caster->critterPet->RemoveFromWorld(false,true);
			sGarbageCollection.AddObject( u_caster->critterPet );
			u_caster->critterPet = NULL;
			return;
		}
		// this is a different critter, so we will dismiss our current critter and then go on to summon the new one
		else
		{
			u_caster->critterPet->RemoveFromWorld(false,true);
			sGarbageCollection.AddObject( u_caster->critterPet );
			u_caster->critterPet = NULL;
		}
	}

	if(!SummonCritterID) 
	{ 
		return;
	}

	CreatureInfo * ci = CreatureNameStorage.LookupEntry(SummonCritterID);
	CreatureProto * cp = CreatureProtoStorage.LookupEntry(SummonCritterID);

	if(!ci || !cp) 
	{ 
		return;
	}

	Creature * pCreature = u_caster->GetMapMgr()->CreateCreature(SummonCritterID);
	pCreature->SetInstanceID(u_caster->GetMapMgr()->GetInstanceID());
	pCreature->Load(cp, m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ());
	pCreature->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, 35);
	pCreature->_setFaction();
	pCreature->SetUInt32Value(UNIT_FIELD_LEVEL, 1);
	pCreature->GetAIInterface()->Init(pCreature,AITYPE_PET,MOVEMENTTYPE_NONE,u_caster);
	pCreature->SetFlag( UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED );
	pCreature->GetAIInterface()->SetUnitToFollow(u_caster);
	pCreature->GetAIInterface()->SetUnitToFollowAngle(float(-(M_PI/2)));
	pCreature->GetAIInterface()->SetFollowDistance(GetRadius(GetProto()->EffectRadiusIndex[i]));
	pCreature->GetAIInterface()->disable_melee = true;
	pCreature->bInvincible = true;
//	pCreature->m_noRespawn = true;
	pCreature->PushToWorld(u_caster->GetMapMgr());
	u_caster->critterPet = pCreature;
}

void Spell::SpellEffectKnockBack(uint32 i)
{
	if(unitTarget == NULL || !unitTarget->isAlive() || !m_caster)
	{ 
		return;
	}

	float dx, dy;
	float verticalSpeed = float(GetProto()->EffectBasePoints[i]+1)/10.0f;
	float horizontalSpeed = float(GetProto()->EffectMiscValue[i])/10.0f;

	float orientation;
	if( m_caster == unitTarget )
		orientation = m_caster->GetOrientation()+ 3.14f;
	else
		orientation = m_caster->calcAngle( m_caster->GetPositionX(),m_caster->GetPositionY(), unitTarget->GetPositionX(),unitTarget->GetPositionY() );

	dx = sinf(orientation);
	dy = cosf(orientation);

	if( unitTarget->IsPlayer() == true )
	{
		sStackWolrdPacket( data, SMSG_MOVE_KNOCK_BACK, 70);
		data << unitTarget->GetNewGUID();
		data << getMSTime(); //seems like packet serialization 
		data << dy << dx;
		data << horizontalSpeed;
		data << -verticalSpeed;
		playerTarget->GetSession()->SendPacket(&data);
		playerTarget->blinked = true;
		playerTarget->SpeedCheatDelay( MAX(float2int32( horizontalSpeed ),5000) );
	}
	else
	{
		float aprox_dist = horizontalSpeed / 10.0f;
		float new_x = unitTarget->GetPositionX()+ aprox_dist*dx;
		float new_y = unitTarget->GetPositionY()+ aprox_dist*dy;
		float new_z = unitTarget->GetPositionZ()+2.0f;
		float land_z = unitTarget->GetMapMgr()->GetLandHeight( new_x, new_y, new_z );
		if( land_z != VMAP_VALUE_NOT_INITIALIZED )
			new_z = land_z;
//		unitTarget->SendMessageToSet( &data, true );
		unitTarget->SetPosition( new_x, new_y, new_z, unitTarget->GetOrientation() );
		unitTarget->GetAIInterface()->StopMovement(0);	//aaah crap, how do i do the kickback for mobs ?
	}
}

void Spell::SpellEffectDisenchant( uint32 i )
{
	if( p_caster == NULL )
	{ 
		return;
	}

	Item* it = p_caster->GetItemInterface()->GetItemByGUID( m_targets.m_itemTarget );
	if( it == NULL )
	{
		SendCastResult( SPELL_FAILED_CANT_BE_DISENCHANTED );
		return;
	}

	//Fill disenchanting loot
	p_caster->SetLootGUID( it->GetGUID() );
	if( !it->loot )
	{
		it->loot = new Loot;
		lootmgr.FillItemLoot( it->loot, it->GetEntry() );
		p_caster->Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE,4,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	}

	Log.Debug( "SpellEffect", "Succesfully disenchanted item %d", uint32( itemTarget->GetEntry() ) );
	p_caster->SendLoot( it->GetGUID(), LOOT_DISENCHANTING );

	//We can increase Enchanting skill up to 60 
	uint32 skill = p_caster->_GetSkillLineCurrent( SKILL_ENCHANTING );
	if( skill && skill < 60 )
	{
		if( Rand( 100.0f - float( skill ) * 0.75f ) )
		{
			uint32 SkillUp = float2int32( 1.0f * sWorld.getRate( RATE_SKILLRATE ) );
			if( skill + SkillUp > 60 )
				SkillUp = 60 - skill;

			p_caster->_AdvanceSkillLine( SKILL_ENCHANTING, SkillUp );
		}
	}
	if( it == i_caster )
		i_caster = NULL;
}

void Spell::SpellEffectInebriate(uint32 i) // lets get drunk!
{
	if(!playerTarget)
	{ 
		return;
	}

	uint16 currentDrunk = playerTarget->GetDrunkValue();
	uint16 drunkMod = (uint16)(damage) * 256;
	if( currentDrunk + drunkMod > 0xFFFE )
		currentDrunk = 0xFFFE;
	else
		currentDrunk += drunkMod;
	playerTarget->SetDrunkValue( currentDrunk, i_caster ? i_caster->GetEntry() : 0 );

	sEventMgr.RemoveEvents(playerTarget, EVENT_PLAYER_REDUCEDRUNK);
	sEventMgr.AddEvent(playerTarget, &Player::EventReduceDrunk, false, EVENT_PLAYER_REDUCEDRUNK, 10000, 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
}

void Spell::SpellEffectFeedPet(uint32 i)  // Feed Pet
{
	// food flags and food level are checked in Spell::CanCast()
	if(!itemTarget || !p_caster)
	{ 
		return;
	}
	
	Pet *pPet = p_caster->GetSummon();
	if(!pPet)
	{ 
		return;
	}

	/**	Cast feed pet effect
	- effect is item level and pet level dependent, aura ticks are 35, 17, 8 (*1000) happiness
	- http://petopia.brashendeavors.net/html/articles/basics_feeding.shtml */
	int8 deltaLvl = (int8)(pPet->getLevel() - itemTarget->GetProto()->ItemLevel);
	damage /= 1000; //damage of Feed pet spell is 35000
	if(deltaLvl > 10) damage = damage >> 1;//divide by 2
	if(deltaLvl > 20) damage = damage >> 1;
	damage *= 1000;

	SpellEntry *spellInfo = dbcSpell.LookupEntry(GetProto()->EffectTriggerSpell[i]);
	Spell *sp= SpellPool.PooledNew();
	sp->Init(p_caster,spellInfo,true,NULL);
	sp->forced_basepoints[0] = damage;
	SpellCastTargets tgt;
	tgt.m_unitTarget=pPet->GetGUID();
	sp->prepare(&tgt);

	if(itemTarget->GetUInt32Value(ITEM_FIELD_STACK_COUNT)>1)
	{
		itemTarget->ModUnsigned32Value(ITEM_FIELD_STACK_COUNT, -1);
		itemTarget->m_isDirty=true;
	}
	else
	{
		p_caster->GetItemInterface()->SafeFullRemoveItemByGuid(itemTarget->GetGUID());
		itemTarget=NULL;
	}
}

void Spell::SpellEffectRedirectThreat(uint32 i)
{
	if (!p_caster || !unitTarget)
	{ 
		return;
	}

	if ((unitTarget->GetTypeId() == TYPEID_PLAYER && p_caster->GetGroup() != SafePlayerCast(unitTarget)->GetGroup()) || (unitTarget->GetTypeId() == TYPEID_UNIT && !unitTarget->IsPet()))
	{ 
		return;
	}

	p_caster->SetMisdirectionTarget(unitTarget->GetGUID());
	uint32 maxduration = GetDuration();
	//there was an exploit for people setting this to dead player then mobs would get stuck
	if( maxduration > 20000 )
		maxduration = 20000;
	if( maxduration < 4000 )
		maxduration = 4000;	//misdirect next attack, at least try
	sEventMgr.AddEvent(p_caster,&Player::SetMisdirectionTarget,(uint64)0,EVENT_RESET_MISSDIRECTIONTARGET,maxduration,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	
}

void Spell::SpellEffectReduceThreatPercent(uint32 i)
{
	if (!unitTarget || !unitTarget->IsCreature() || !u_caster || unitTarget->GetAIInterface()->getThreatByPtr(u_caster) == 0)
	{ 
		return;
	}
	unitTarget->GetAIInterface()->modThreatByPtr(u_caster, (int32)unitTarget->GetAIInterface()->getThreatByPtr(u_caster) * damage / 100);
}

void Spell::SpellEffectReputation(uint32 i)
{
	if(!playerTarget)
	{ 
		return;
	}

	//playerTarget->modReputation(GetProto()->EffectMiscValue[i], damage, true);
	playerTarget->ModStanding(GetProto()->EffectMiscValue[i], damage);
}

void Spell::SpellEffectSummonObjectSlot(uint32 i)
{
	if(!u_caster || !u_caster->IsInWorld())
	{ 
		return;
	}

	GameObject *GoSummon = NULL;

	uint32 slot=GetProto()->Effect[i] - SPELL_EFFECT_SUMMON_OBJECT_SLOT1;
	GoSummon = u_caster->m_ObjectSlots[slot] ? u_caster->GetMapMgr()->GetGameObject(u_caster->m_ObjectSlots[slot]) : 0;
	u_caster->m_ObjectSlots[slot] = 0;
	
	if( GoSummon )
	{
		if(GoSummon->GetInstanceID() != u_caster->GetInstanceID())
			GoSummon->ExpireAndDelete();
		else
		{
			if( GoSummon->IsInWorld() )
				GoSummon->RemoveFromWorld(true);
			sGarbageCollection.AddObject( GoSummon );
			GoSummon = NULL;
		}
	}


	// spawn a new one
	GoSummon = u_caster->GetMapMgr()->CreateGameObject(GetProto()->EffectMiscValue[i]);
	float spx,spy,spz,spo;
	if( m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION )
	{
		spx = m_targets.m_destX;
		spy = m_targets.m_destY;
		spz = m_targets.m_destZ;
		spo = m_caster->GetOrientation();
	}
	else if( m_targets.m_targetMask & TARGET_FLAG_SOURCE_LOCATION )
	{
		spx = m_targets.m_srcX;
		spy = m_targets.m_srcY;
		spz = m_targets.m_srcZ;
		spo = m_caster->GetOrientation();
	}
	else if( unitTarget != NULL && ( GetProto()->c_is_flags & SPELL_FLAG_IS_SUMMONING_AT_TARGET ) )
	{
		spx = unitTarget->GetPositionX();
		spy = unitTarget->GetPositionY();
		spz = unitTarget->GetPositionZ();
		spo = unitTarget->GetOrientation();
	}
	else
	{
		spx = m_caster->GetPositionX();
		spy = m_caster->GetPositionY();
		spz = m_caster->GetPositionZ();
		spo = m_caster->GetOrientation();
	}
	if(! GoSummon->CreateFromProto(GetProto()->EffectMiscValue[i], m_caster->GetMapId(), spx, spy, spz, spo ))
	{
		sGarbageCollection.AddObject( GoSummon );
		GoSummon = NULL;
		return;
	}
	
	GoSummon->SetUInt32Value(GAMEOBJECT_LEVEL, u_caster->getLevel());
	GoSummon->SetUInt64Value(OBJECT_FIELD_CREATED_BY, m_caster->GetGUID()); 
	GoSummon->SetInstanceID(m_caster->GetInstanceID());

	if(GoSummon->GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPEID) == GAMEOBJECT_TYPE_TRAP)
	{
		GoSummon->SetUInt64Value(OBJECT_FIELD_CREATED_BY, u_caster->GetGUID());
		GoSummon->invisible = true;
		GoSummon->invisibilityFlag = INVIS_FLAG_TRAP;
		GoSummon->charges = 1;
		GoSummon->checkrate = 1;	//this is in update intervals. avg 50 ms, * 2 = 1 second
		sEventMgr.AddEvent(GoSummon, &GameObject::TrapSearchTarget, EVENT_GAMEOBJECT_TRAP_SEARCH_TARGET, 500, 0,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
	else
	{
		sEventMgr.AddEvent(GoSummon, &GameObject::ExpireAndDelete, EVENT_GAMEOBJECT_EXPIRE, GetDuration(), 1,0);
	}
	GoSummon->PushToWorld(m_caster->GetMapMgr());
	GoSummon->SetSummoned(u_caster);
	u_caster->m_ObjectSlots[slot] = GoSummon->GetLowGUID();
	
/*	if( p_caster && p_caster->GetSession() )
	{
		sStackWolrdPacket(data,SMSG_TOTEM_CREATED,40);
		data << uint8(slot);
		data << GoSummon->GetGUID();
		data << uint32(0);
		data << uint32(0);
		p_caster->GetSession()->SendPacket( &data );
		data.Initialize( SMSG_SPELLLOGEXECUTE );
		data << p_caster->GetNewGUID();
		data << GetProto()->Id;
		data << uint32(1);
		data << GetProto()->SpellVisual;
		data << uint32(1);
		data << GoSummon->GetNewGUID();
		p_caster->GetSession()->SendPacket( &data );
	}*/
}

void Spell::SpellEffectDispelMechanic(uint32 i)
{
	if( !unitTarget || !unitTarget->isAlive() )
	{ 
		return;
	}
	/* this was already working before...	
	uint32 sMisc = GetProto()->EffectMiscValue[i];

	for( uint32 x = 0 ; x<MAX_AURAS ; x++ )
	{
		if( unitTarget->m_auras[x] && !unitTarget->m_auras[x]->IsPositive())
		{
			if( unitTarget->m_auras[x]->GetSpellProto()->MechanicsType == sMisc )
				unitTarget->m_auras[x]->Remove();
		}
	}
	*/
	unitTarget->RemoveAllAurasByMechanic( GetProto()->EffectMiscValue[i] , GetProto()->EffectBasePoints[i] , false );

	/*Shady: if it's about Daze spell - dismount should be done by RemoveAllAurasByMechanic.
	We don't need useless code or hackfixes here, so commented.*/
	//if( playerTarget && GetProto()->NameHash == SPELL_HASH_DAZED && playerTarget->IsMounted() )
	//	playerTarget->RemoveAura(playerTarget->m_MountSpellId);
}

void Spell::SpellEffectSummonDeadPet(uint32 i)
{//this is pet resurrect
	if(!p_caster) 
	{ 
		return;
	}
	Pet *pPet = p_caster->GetSummon();
	if(pPet)
	{
		if( (GetProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) )
		{
			SM_FIValue(p_caster->SM_FMiscEffect,&damage,GetProto()->SpellGroupType);
			SM_PIValue(p_caster->SM_PMiscEffect,&damage,GetProto()->SpellGroupType);
		}

		pPet->SetUInt32Value( UNIT_DYNAMIC_FLAGS, 0 );
		pPet->SetUInt32Value( UNIT_FIELD_HEALTH, ( uint32 )( ( pPet->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * damage ) / 100 ));
		pPet->setDeathState( ALIVE );
		pPet->GetAIInterface()->HandleEvent( EVENT_FOLLOWOWNER, pPet, 0 );
		sEventMgr.RemoveEvents( pPet, EVENT_PET_DELAYED_REMOVE );
		pPet->SendSpellsToOwner();
 	}
}

/* This effect has 2 functions
 * 1. It delete's all current totems from the player
 * 2. It returns a percentage of the mana back to the player
 *
 * Bur kick my ass if this is not safe:P
*/

void Spell::SpellEffectDestroyAllTotems(uint32 i)
{
	if(!p_caster || !p_caster->IsInWorld()) 
	{ 
		return;
	}

	float RetreivedMana = 0.0f;
	for(uint32 x=0;x<4;x++)
	{
		// atm totems are considert creature's
		if(p_caster->m_TotemSlots[x])
		{
			uint32 SpellID = p_caster->m_TotemSlots[x]->GetUInt32Value(UNIT_CREATED_BY_SPELL);
			SpellEntry * sp = dbcSpell.LookupEntry(SpellID);
			if (!sp)
				continue;

			float pts = float(GetProto()->EffectBasePoints[i]+1) / 100.0f;
			RetreivedMana += float(sp->manaCost) * pts;

			p_caster->m_TotemSlots[x]->TotemExpire();
		}

		if(p_caster->m_ObjectSlots[x])
		{
			GameObject * obj = p_caster->GetMapMgr()->GetGameObject(p_caster->m_ObjectSlots[x]);
			if(obj)
			{
				obj->ExpireAndDelete();
			}
			p_caster->m_ObjectSlots[x] = 0;
		}
	}

	p_caster->Energize( p_caster, GetProto()->Id, uint32( RetreivedMana ), POWER_TYPE_MANA );
}

void Spell::SpellEffectSummonDemon(uint32 i)
{
	if(!p_caster/* ||  p_caster->getClass() != WARLOCK */) //summoning a demon shouldn't be warlock only, see spells 25005, 24934, 24810 etc etc
	{ 
		return;
	}
	Pet *pPet = p_caster->GetSummon();
	if(pPet)
	{
		pPet->Dismiss();
	}

	CreatureInfo *ci = CreatureNameStorage.LookupEntry(GetProto()->EffectMiscValue[i]);
	if(ci)
	{
		LocationVector *vec = NULL;
		if( m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION && m_targets.m_destX && m_targets.m_destY && m_targets.m_destZ )
		{
			vec = new LocationVector(m_targets.m_destX, m_targets.m_destY, m_targets.m_destZ);
		}
		pPet = objmgr.CreatePet( GetProto()->EffectMiscValue[i],p_caster->GeneratePetNumber() );
		pPet->SetInstanceID(p_caster->GetInstanceID());
		pPet->CreateAsSummon(GetProto()->EffectMiscValue[i], ci, NULL, p_caster, GetProto(), 1, 300000, vec);
		if (vec) 
		{
			delete vec;
			vec = NULL;
		}
	}
	//Create Enslave Aura if its inferno spell
	if(GetProto()->Id == 1122 && pPet )
	{
		SpellEntry *spellInfo = dbcSpell.LookupEntry(11726);
		
		Spell *sp=SpellPool.PooledNew();
		sp->Init(pPet,spellInfo,true,NULL);
		SpellCastTargets tgt;
		tgt.m_unitTarget=pPet->GetGUID();
		sp->prepare(&tgt);
	}
}

void Spell::SpellEffectResurrect(uint32 i) // Resurrect (Flat)
{
	if(!playerTarget)
	{
		if(!corpseTarget)
		{
			// unit resurrection handler
			if(unitTarget)
			{
				if(unitTarget->GetTypeId()==TYPEID_UNIT && unitTarget->IsPet() && unitTarget->IsDead())
				{
					uint32 hlth = ((uint32)GetProto()->EffectBasePoints[i] > unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH)) ? unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH) : (uint32)GetProto()->EffectBasePoints[i];
					uint32 mana = ((uint32)GetProto()->EffectBasePoints[i] > unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1)) ? unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1) : (uint32)GetProto()->EffectBasePoints[i];

					if(!unitTarget->IsPet())
					{
						sEventMgr.RemoveEvents(unitTarget, EVENT_CREATURE_REMOVE_CORPSE);
					}
					else
					{
						sEventMgr.RemoveEvents(unitTarget, EVENT_PET_DELAYED_REMOVE);
						sEventMgr.RemoveEvents(unitTarget, EVENT_CREATURE_REMOVE_CORPSE);
					}
					unitTarget->SetUInt32Value(UNIT_FIELD_HEALTH, hlth);
					unitTarget->SetUInt32Value(UNIT_FIELD_POWER1, mana);
					unitTarget->SetUInt32Value(UNIT_DYNAMIC_FLAGS, 0);
					unitTarget->setDeathState(ALIVE);
//					SafeCreatureCast(unitTarget)->Tagged=false;
					SafeCreatureCast(unitTarget)->TaggerGroupId=0;
					SafeCreatureCast(unitTarget)->TaggerGuid=0;
					SafeCreatureCast(unitTarget)->loot.gold=0;
					SafeCreatureCast(unitTarget)->loot.looters.clear();
					//clear roll info for items
					SafeCreatureCast(unitTarget)->loot.items.clear();
				}
			}

			return;
		}
		playerTarget = objmgr.GetPlayer(corpseTarget->GetUInt32Value(CORPSE_FIELD_OWNER));
		if(!playerTarget) 
		{ 
			return;
		}
	}

	if(playerTarget->isAlive() || !playerTarget->IsInWorld())
	{ 
		return;
	}

	uint32 health = GetProto()->EffectBasePoints[i];
	uint32 mana = GetProto()->EffectMiscValue[i];
	
	playerTarget->m_resurrectHealth = health;
	playerTarget->m_resurrectMana = mana;

	SendResurrectRequest(playerTarget);   
	playerTarget->SetMovement(MOVE_UNROOT);
}

void Spell::SpellEffectAttackMe(uint32 i)
{
	if(!unitTarget)
	{ 
		return;
	}
	if(!unitTarget->isAlive())
	{ 
		return;
	}

	int32 threat_to_most_hated = (int32)unitTarget->GetAIInterface()->getThreatByPtr( unitTarget->GetAIInterface()->GetMostHated() );
	int32 threat_to_us = (int32)unitTarget->GetAIInterface()->getThreatByPtr( u_caster );
	int32 threat_dif = threat_to_most_hated - threat_to_us;
	if(threat_dif>0)//maybe we are already the most hated ?
		unitTarget->GetAIInterface()->modThreatByPtr( u_caster, threat_dif + 1000 );

	unitTarget->GetAIInterface()->AttackReaction( u_caster, damage, 0 );	
}

void Spell::SpellEffectSkinPlayerCorpse(uint32 i)
{
	Corpse * corpse = 0;
	if(!playerTarget)
	{
		// means we're "skinning" a corpse
		corpse = objmgr.GetCorpse((uint32)m_targets.m_unitTarget);  // hacky
	}
	else if(playerTarget->getDeathState() == CORPSE)	// repopped while we were casting 
	{
		corpse = objmgr.GetCorpse(playerTarget->GetLowGUID());
	}

	if(!m_caster->IsPlayer()) 
	{ 
		return;
	}
 
	if(playerTarget && !corpse)
	{
		if(!playerTarget->m_bg || !playerTarget->IsDead())
		{ 
			return;
		}

		// Set all the lootable stuff on the player. If he repops before we've looted, we'll set the flags
		// on corpse then :p

		playerTarget->bShouldHaveLootableOnCorpse = false;
		playerTarget->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);
		playerTarget->SetFlag(UNIT_DYNAMIC_FLAGS, U_DYN_FLAG_LOOTABLE);

		// Send the loot.
		p_caster->SendLoot(playerTarget->GetGUID(), LOOT_SKINNING);

		// Send a message to the died player, telling him he has to resurrect at the graveyard.
		// Send an empty corpse location too, :P
		
		playerTarget->GetSession()->OutPacket(SMSG_PLAYER_SKINNED, 1, "\x00");
		playerTarget->GetSession()->OutPacket(MSG_CORPSE_QUERY, 1, "\x00");

		// don't allow him to spawn a corpse
		playerTarget->bCorpseCreateable = false;

		// and.. force him to the graveyard and repop him.
		playerTarget->RepopRequestedPlayer();

	}else if(corpse)
	{
		// find the corpses' owner
		Player * owner = objmgr.GetPlayer(corpse->GetUInt32Value(CORPSE_FIELD_OWNER));
		if(owner)
		{
			if(owner->m_bg == NULL)
			{ 
				return;
			}

			owner->GetSession()->OutPacket(SMSG_PLAYER_SKINNED, 1, "\x00");
			owner->GetSession()->OutPacket(MSG_CORPSE_QUERY, 1, "\x00");
		}

		if(corpse->GetUInt32Value(CORPSE_FIELD_DYNAMIC_FLAGS) != 1)
			corpse->SetUInt32Value(CORPSE_FIELD_DYNAMIC_FLAGS, 1); // sets it so you can loot the plyr
		
		// remove skinnable flag
		corpse->SetUInt32Value(CORPSE_FIELD_FLAGS, 5);

		// remove owner association
		corpse->SpawnBones();

		// send loot
		p_caster->SendLoot(corpse->GetGUID(), LOOT_SKINNING);
	}
}

void Spell::SpellEffectSkill(uint32 i)
{
	// Used by professions only
	// Effect should be renamed in RequireSkill

	if ( !p_caster || p_caster->_GetSkillLineMax(GetProto()->EffectMiscValue[i]) >= uint32( damage * 75 ) )
	{ 
		return;
	}
	
	//no multi casts in case of playercreate spell
	//zack:maybe some spells are required by client. Ex : language
//	p_caster->removeSpell( GetProto()->Id, false, false, 0 );

	if ( p_caster->_HasSkillLine( GetProto()->EffectMiscValue[i]) )
		p_caster->_ModifySkillMaximum( GetProto()->EffectMiscValue[i], uint32( damage * 75 ) );
	else
		p_caster->_AddSkillLine( GetProto()->EffectMiscValue[i], 1, uint32( damage * 75 ) );
}

void Spell::SpellEffectApplyPetAura(uint32 i)
{
	SpellEffectApplyAura(i);
}

void Spell::SpellEffectDummyMelee( uint32 i ) // Normalized Weapon damage +
{

	if( unitTarget == NULL || u_caster == NULL )
	{ 
		return;
	}

	if( GetProto()->NameHash == SPELL_HASH_OVERPOWER && p_caster != NULL ) //warrior : overpower - let us clear the event and the combopoint count
	{
		p_caster->NullComboPoints(); //some say that we should only remove 1 point per dodge. Due to cooldown you can't cast it twice anyway..
		sEventMgr.RemoveEvents( p_caster, EVENT_COMBO_POINT_CLEAR_FOR_TARGET );
	}
	else if( GetProto()->NameHash == SPELL_HASH_DEVASTATE)
	{
		//count the number of sunder armors on target
		uint32 sunder_count=0;
		SpellEntry *spellInfo=dbcSpell.LookupEntry(58567);	//sunder armor rank one will be casted in case we will not find a better one on the target
		for(uint32 x = MAX_POSITIVE_AURAS; x < MAX_NEGATIVE_AURAS1(unitTarget); ++x)
		{
			if(unitTarget->m_auras[x] && unitTarget->m_auras[x]->GetSpellProto()->NameHash==SPELL_HASH_SUNDER_ARMOR)
			{
				sunder_count++;
				spellInfo=unitTarget->m_auras[x]->GetSpellProto();
			}
		}
		if(!spellInfo)
			return; //omg how did this happen ?
		//we should also cast sunder armor effect on target with or without dmg
		Spell *spell = SpellPool.PooledNew();
		spell->Init(u_caster, spellInfo ,true, NULL);
		spell->ProcedOnSpell = GetProto();
		spell->pSpellId=GetProto()->Id;
		SpellCastTargets targets(unitTarget->GetGUID());
		spell->prepare(&targets);
		if( p_caster && p_caster->HasGlyphWithID( GLYPH_WARRIOR_DEVASTATE ) )
		{
			Spell *spell = SpellPool.PooledNew();
			spell->Init(u_caster, spellInfo ,true, NULL);
			spell->ProcedOnSpell = GetProto();
			spell->pSpellId=GetProto()->Id;
			SpellCastTargets targets(unitTarget->GetGUID());
			spell->prepare(&targets);
		}
		if(!sunder_count)
			return; //no damage = no joy
		damage = damage*sunder_count;
	}
/*	else if( GetProto()->NameHash == SPELL_HASH_CRUSADER_STRIKE ) // Crusader Strike - refreshes *all* judgements, not just your own
	{
		for( uint32 x = MAX_POSITIVE_AURAS1(unitTarget) ; x <= MAX_NEGATIVE_AURAS1(unitTarget) ; x ++ ) // there are only debuff judgements anyway :P
		{
			if( unitTarget->m_auras[x] && unitTarget->m_auras[x]->GetSpellProto()->BGR_one_buff_from_caster_on_1target == SPELL_TYPE_INDEX_JUDGEMENT )
			{
				// Refresh it!
				// oh noes, they don't stack...
				Aura * aur = unitTarget->m_auras[x];
				SpellEntry * spinfo = aur->GetSpellProto();
				aur->Remove();
				Spell * sp = SpellPool.PooledNew();
				sp->Init( this->u_caster , spinfo , true , NULL );
				
				SpellCastTargets tgt;
				tgt.m_unitTarget = unitTarget->GetGUID();
				sp->prepare( &tgt );
			}
		}
	}*/

	//Hemorrhage
	if( p_caster != NULL && GetProto()->NameHash == SPELL_HASH_HEMORRHAGE )
		p_caster->AddComboPoints(p_caster->GetSelection(), 1);

	// rogue ambush etc
	for (uint32 x =0;x<3;x++)
		if(GetProto()->Effect[x] == SPELL_EFFECT_WEAPON_PERCENT_DAMAGE)
		{
			add_damage = damage * (GetProto()->EffectBasePoints[x]+1) /100;
			return;
		}

	//rogue - mutilate ads dmg if target is poisoned
	uint32 add_pct_dmg_mod = 0;
	if(	GetProto()->NameHash == SPELL_HASH_MUTILATE && unitTarget->IsPoisoned() )
		add_pct_dmg_mod += 20;

	uint32 _type;
	if( GetType() == SPELL_DMG_TYPE_RANGED )
		_type = RANGED;
	else
	{
		if (GetProto()->AttributesExC & 0x1000000)
			_type =  OFFHAND;
		else
			_type = MELEE;
	}
	u_caster->Strike( unitTarget, _type, GetProto(), damage, add_pct_dmg_mod, 0, false, true );
}

void Spell::SpellEffectFilming( uint32 i )
{
	if (!playerTarget || !playerTarget->isAlive() || !u_caster)
	{ 
		return;
	}

	if(playerTarget->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER))
	{ 
		return;
	}

	TaxiPath* taxipath = sTaxiMgr.GetTaxiPath(GetProto()->EffectMiscValue[0]);

	if( !taxipath )
	{ 
		return;
	}

	TaxiNode* taxinode = sTaxiMgr.GetTaxiNode( taxipath->GetSourceNode() );

	if( !taxinode )
	{ 
		return;
	}

	uint32 modelid =0;

	if( playerTarget->GetTeam() )
	{
		CreatureInfo* ci = CreatureNameStorage.LookupEntry( taxinode->horde_mount );
		if(!ci) 
		{ 
			return;
		}
		modelid = ci->Male_DisplayID;
		if(!modelid) 
		{ 
			return;
		}
	}
	else
	{
		CreatureInfo* ci = CreatureNameStorage.LookupEntry( taxinode->alliance_mount );
		if(!ci) 
		{ 
			return;
		}
		modelid = ci->Male_DisplayID;
		if(!modelid) 
		{ 
			return;
		}
	}

	if(playerTarget->GetSummon() != NULL)
	{
		if(playerTarget->GetSummon()->GetUInt32Value(UNIT_CREATED_BY_SPELL) > 0)
			playerTarget->GetSummon()->Dismiss();						   // warlock summon -> dismiss
		else
			playerTarget->GetSummon()->Remove( true, false );					  // hunter pet -> just remove for later re-call
	}

	playerTarget->TaxiStart(taxipath, modelid, 0);
}

void Spell::SpellEffectSpellSteal( uint32 i )
{
	if (!unitTarget || !u_caster || !unitTarget->isAlive())
	{ 
		return;
	}
	if(unitTarget->IsPlayer() && p_caster && p_caster != SafePlayerCast(unitTarget))
	{
		if(SafePlayerCast(unitTarget)->IsPvPFlagged())
			p_caster->SetPvPFlag();
	}

	Aura *aur;
	uint32 start, end;
	if(isAttackable(u_caster,unitTarget))
	{
		start=0;
		end=MAX_POSITIVE_AURAS1(unitTarget);
	}
	else
		return;
	
	WorldPacket data(SMSG_SPELLDISPELLOG, 16);

	for(uint32 x=start;x<end;x++)
	if(unitTarget->m_auras[x])
	{
		aur = unitTarget->m_auras[x];
		if(aur->GetSpellId() != 15007 && !aur->IsPassive() 
			&& ( aur->GetSpellProto()->c_is_flags & (SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET|SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER))==0
			&& aur->GetSpellProto()->talent_entry_assoc_counter == 0 
//			&& aur->IsPositive()	// Zack : We are only checking positiv auras. There is no meaning to check again
			) //Nothing can dispel resurrection sickness
		{
			if(aur->GetSpellProto()->DispelType == DISPEL_MAGIC)
			{
				data.clear();
				data << m_caster->GetNewGUID();
				data << unitTarget->GetNewGUID();
				data << (uint32)1;
				data << aur->GetSpellId();
				m_caster->SendMessageToSet(&data,true);

				uint32 aurdur = ( aur->GetDuration()>120000 ? 120000 : aur->GetDuration() );
				Aura *aura = AuraPool.PooledNew();
				aura->Init(aur->GetSpellProto(), aurdur, u_caster, u_caster );
				aura->SetDuration( aurdur ); // double checking
				uint32 aur_removed = unitTarget->RemoveAllPosAuraByNameHash( aura->GetSpellProto()->NameHash );
				for ( uint32 i = 0; i < 3; i++ )
				{
					if ( aura->GetSpellProto()->Effect[i] )
					{
						aura->AddMod( aura->GetSpellProto()->EffectApplyAuraName[i], aura->GetSpellProto()->EffectBasePoints[i]+1, aura->GetSpellProto()->EffectMiscValue[i], i );
					}
				}
				if( aura->GetSpellProto()->procCharges>0 )
				{
					Aura *aur = NULL;
					for(uint32 i = 0; i<aur_removed-1; i++)
					{
						aur = AuraPool.PooledNew();
						aur->Init( aura->GetSpellProto(), aurdur, u_caster, u_caster );
						aur->SetDuration( aurdur ); // double checking
						u_caster->AddAura(aur);
						aur = NULL;
					}
					if(!(aura->GetSpellProto()->procFlags2 & PROC2_REMOVEONUSE))
					{
						SpellCharge charge;
						charge.count=aur_removed;
//						charge.spellId=aura->GetSpellId();
						charge.spe=aura->GetSpellProto();
						if( aura->GetSpellProto()->procFlagsRemove )
							charge.ProcFlag=aura->GetSpellProto()->procFlagsRemove;
						else
							charge.ProcFlag=aura->GetSpellProto()->procFlags;
						u_caster->m_chargeSpells.insert(make_pair(aura->GetSpellId(),charge));
					}
				}
				u_caster->AddAura(aura);
				break;
			}			
		}
	}   
}

void Spell::SpellEffectProspecting(uint32 i)
{
	if(!p_caster) 
	{ 
		return;
	}

	if(!itemTarget) // this should never happen
	{
		SendCastResult(SPELL_FAILED_CANT_BE_PROSPECTED);
		return;
	}

	//Fill Prospecting loot
	p_caster->SetLootGUID(itemTarget->GetGUID());
	if( !itemTarget->loot )
		{
			itemTarget->loot = new Loot;
			lootmgr.FillItemLoot( itemTarget->loot , itemTarget->GetEntry());
		}

	if ( itemTarget->loot->items.size() > 0 )
	{
		Log.Debug("SpellEffect","Succesfully prospected item %d", uint32(itemTarget->GetEntry()));
		p_caster->SendLoot( itemTarget->GetGUID(), LOOT_PROSPECTING );
	} 
	else // this should never happen either
	{
		Log.Debug("SpellEffect","Prospecting failed, item %d has no loot", uint32(itemTarget->GetEntry()));
		SendCastResult(SPELL_FAILED_CANT_BE_PROSPECTED);
	}
}

void Spell::SpellEffectResurrectNew(uint32 i)
{
	//base p =hp,misc mana
	if(!playerTarget)
	{
		if(!corpseTarget)
		{
			// unit resurrection handler
			if(unitTarget)
			{
				if(unitTarget->GetTypeId()==TYPEID_UNIT && unitTarget->IsPet() && unitTarget->IsDead())
				{
					uint32 hlth = ((uint32)GetProto()->EffectBasePoints[i] > unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH)) ? unitTarget->GetUInt32Value(UNIT_FIELD_MAXHEALTH) : (uint32)GetProto()->EffectBasePoints[i];
					uint32 mana = ((uint32)GetProto()->EffectBasePoints[i] > unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1)) ? unitTarget->GetUInt32Value(UNIT_FIELD_MAXPOWER1) : (uint32)GetProto()->EffectBasePoints[i];

					if(!unitTarget->IsPet())
					{
						sEventMgr.RemoveEvents(unitTarget, EVENT_CREATURE_REMOVE_CORPSE);
					}
					else
					{
						sEventMgr.RemoveEvents(unitTarget, EVENT_PET_DELAYED_REMOVE);
						sEventMgr.RemoveEvents(unitTarget, EVENT_CREATURE_REMOVE_CORPSE);
					}
					unitTarget->SetUInt32Value(UNIT_FIELD_HEALTH, hlth);
					unitTarget->SetUInt32Value(UNIT_FIELD_POWER1, mana);
					unitTarget->SetUInt32Value(UNIT_DYNAMIC_FLAGS, 0);
					unitTarget->setDeathState(ALIVE);
//					SafeCreatureCast(unitTarget)->Tagged=false;
					SafeCreatureCast(unitTarget)->TaggerGroupId=0;
					SafeCreatureCast(unitTarget)->TaggerGuid=0;
					SafeCreatureCast(unitTarget)->loot.gold=0;
					SafeCreatureCast(unitTarget)->loot.looters.clear();
					//clear roll info for items
					SafeCreatureCast(unitTarget)->loot.items.clear();
				}
			}

			return;
		}
		playerTarget = objmgr.GetPlayer(corpseTarget->GetUInt32Value(CORPSE_FIELD_OWNER));
		if(!playerTarget) 
		{ 
			return;
		}
	}

	if(playerTarget->isAlive() || !playerTarget->IsInWorld())
	{ 
		return;
	}
	//resurr
	//playerTarget->resurrector = p_caster->GetLowGUID();
	playerTarget->m_resurrectMapId = m_caster->GetMapId();
	playerTarget->m_resurrectInstanceID = m_caster->GetInstanceID();
	playerTarget->m_resurrectPosition = m_caster->GetPosition();
	playerTarget->m_resurrectHealth = damage;
	playerTarget->m_resurrectMana = GetProto()->EffectMiscValue[i];

	SendResurrectRequest( playerTarget );
}

void Spell::SpellEffectTranformItem(uint32 i)
{
	bool result;
	AddItemResult result2;

	if(!i_caster)
	{ 
		return;
	}
	uint32 itemid=GetProto()->EffectItemType[i];
	if(!itemid)
	{ 
		return;
	}

	//Save durability of the old item
	Player * owner=i_caster->GetOwner();
	uint32 dur= i_caster->GetUInt32Value(ITEM_FIELD_DURABILITY);
	//	int8 slot=owner->GetItemInterface()->GetInventorySlotByGuid(i_caster->GetGUID());
	//	uint32 invt=i_caster->GetProto()->InventoryType;

	   result  = owner->GetItemInterface()->SafeFullRemoveItemByGuid(i_caster->GetGUID());
	if(!result)
	{
		//something went wrong if this happen, item doesnt exist, so it wasnt destroyed.
		return;
	}

	i_caster=NULL;

	Item *it=objmgr.CreateItem(itemid,owner);
	it->SetDurability(dur);
	//additem
	
	   //additem
	result2 = owner->GetItemInterface()->AddItemToFreeSlot(&it);
	if(!result2) //should never get here
	{ 
		owner->GetItemInterface()->BuildInventoryChangeError(NULL,NULL,INV_ERR_BAG_FULL);
		it->DeleteMe();
	}
}

void Spell::SpellEffectEnvironmentalDamage(uint32 i)
{
	if(!playerTarget)
	{ 
		return;
	}

	if(unitTarget->SchoolImmunityList[GetProto()->School])
	{
		SendCastResult(SPELL_FAILED_IMMUNE);
		return;
	}
	//this is GO, not unit	
	m_caster->SpellNonMeleeDamageLog(unitTarget,GetProto()->Id,damage, pSpellId==0, true);
  
	WorldPacket data(SMSG_ENVIRONMENTALDAMAGELOG, 13);
	data << unitTarget->GetGUID();
	data << uint8(DAMAGE_FIRE);
	data << uint32(damage);
	unitTarget->SendMessageToSet( &data, true );
}

void Spell::SpellEffectDismissPet(uint32 i)
{
	// remove pet.. but don't delete so it can be called later
	if(!p_caster)
	{ 
		return;
	}

	Pet *pPet = p_caster->GetSummon();
	if(!pPet)
	{ 
		return;
	}
	pPet->Remove(true, true);
	p_caster->SetSummon(NULL);	//just in case of broken chain
}

void Spell::SpellEffectEnchantHeldItem( uint32 i )
{
	if( playerTarget == NULL )
	{ 
		return;
	}

	Item * item = playerTarget->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
	if( item == NULL )
	{ 
		return;
	}

	uint32 Duration = 1800; // Needs to be found in dbc.. I guess?

	EnchantEntry * Enchantment = dbcEnchant.LookupEntry( GetProto()->EffectMiscValue[i] );
	
	if( Enchantment == NULL )
	{ 
		return;
	}

	item->RemoveEnchantment( ITEM_ENCHANT_SLOT_TEMPORARY2 );
	item->AddEnchantment( Enchantment, Duration, false, true, false, ITEM_ENCHANT_SLOT_TEMPORARY2 );
}

void Spell::SpellEffectAddHonor(uint32 i)
{
	if( playerTarget == NULL )
	{ 
		return;
	}
	uint32 val = GetProto()->EffectBasePoints[i];

	if( GetProto()->AttributesExB & FLAGS3_UNK4 )val /= 10;

	val += 1;

	HonorHandler::AddHonorPointsToPlayer( playerTarget, val );

	WorldPacket data(SMSG_PVP_CREDIT, 16);
	data << val;
	data << uint64(0);
	data << uint32(5);
	playerTarget->GetSession()->SendPacket(&data);
}

void Spell::SpellEffectSpawn(uint32 i)
{
	// this effect is mostly for custom teleporting
	switch(GetProto()->Id)
	{
	  case 10418: // Arugal spawn-in spell , teleports it to 3 locations randomly sneeking players (bastard ;P)   
	  { 
		if(!u_caster || u_caster->IsPlayer())
		{ 
			return;
		}
		 
		static float coord[3][3]= {{-108.9034f,2129.5678f,144.9210f},{-108.9034f,2155.5678f,155.678f},{-77.9034f,2155.5678f,155.678f}};
		
		int i = (int)(rand()%3);
		u_caster->GetAIInterface()->SendMoveToPacket(coord[i][0],coord[i][1],coord[i][2],0.0f,0,u_caster->GetAIInterface()->getMoveFlags());
	  }
	}
}

void Spell::SpellEffectApplyAura128(uint32 i)
{
	if(GetProto()->EffectApplyAuraName[i] != 0)
		SpellEffectApplyAura(i);
}

void Spell::SpellEffectRuneToPower(uint32 i)
{
	if( !p_caster )
		return; //atm only players can have runes
	if( GetProto()->EffectMiscValue[i] >= TOTAL_USED_RUNES )
	{
		sLog.outDebug("Spell is trying to convert unsupported runetype %u",GetProto()->EffectMiscValue[i]);
		return; 
	}

//	p_caster->TakeFullRuneCount( GetProto()->EffectMiscValue[i], damage ); //seems dmg is not 1-2
	p_caster->TakeFullRuneCount( GetProto()->EffectMiscValue[i], 1 );
}

void Spell::SpellEffectTriggerSpellWithValue(uint32 i)
{
	if( unitTarget == NULL )
	{ 
		return;
	}

	SpellEntry* TriggeredSpell = dbcSpell.LookupEntryForced(GetProto()->EffectTriggerSpell[i]);
	if( TriggeredSpell == NULL )
	{ 
		return;
	}

	Spell *sp=SpellPool.PooledNew();
	sp->Init(m_caster,dbcSpell.LookupEntry(TriggeredSpell->Id),true,NULL);

	for(uint32 x=0;x<3;x++)
	{
		if( i==x )
			sp->forced_basepoints[x] = damage;	//prayer of mending should inherit heal bonus ?
		else
			sp->forced_basepoints[x] = TriggeredSpell->EffectBasePoints[i];

	}

	SpellCastTargets tgt(unitTarget->GetGUID());
	sp->prepare(&tgt);
}

void Spell::SpellEffectSummonTarget(uint32 i) // ritual of summoning
{
	if ( unitTarget == NULL )
	{ 
		return;
	}

	SpellEffectTriggerSpell( i );
}

void Spell::SpellEffectForgetSpecialization(uint32 i)
{
	if (!playerTarget)
	{ 
		return;
	}

	uint32 spellid = GetProto()->EffectTriggerSpell[i];
	playerTarget->removeSpell( spellid, false, false, 0);

	sLog.outDebug("Player %u have forgot spell %u from spell %u ( caster: %u)", playerTarget->GetLowGUID(), spellid, GetProto()->Id, m_caster->GetLowGUID());
}

void Spell::SpellEffectMilling(uint32 i)
{
	if(!p_caster) 
	{ 
		return;
	}

	if(!itemTarget) // this should never happen
	{
		SendCastResult(SPELL_FAILED_CANT_BE_PROSPECTED);
		return;
	}

	//Fill Prospecting loot
	p_caster->SetLootGUID(itemTarget->GetGUID());
	if( !itemTarget->loot )
		{
			itemTarget->loot = new Loot;
			lootmgr.FillItemLoot( itemTarget->loot , itemTarget->GetEntry());
		}

	if ( itemTarget->loot->items.size() > 0 )
	{
		Log.Debug("SpellEffect","Succesfully milled item %d", uint32(itemTarget->GetEntry()));
		p_caster->SendLoot( itemTarget->GetGUID(), LOOT_MILLING );
	} 
	else // this should never happen either
	{
		Log.Debug("SpellEffect","Milling failed, item %d has no loot", uint32(itemTarget->GetEntry()));
		SendCastResult(SPELL_FAILED_CANT_BE_PROSPECTED);
	}
}

void Spell::SpellEffectSetTalentSpecsCount(uint32 i)
{
	if(!p_caster)
	{ 
		return;
	}

	p_caster->m_talentSpecsCount = damage % MAX_SPEC_COUNT;

	// Send update
//	p_caster->smsg_TalentsInfo(false, 0, 0);
}

void Spell::SpellEffectActivateTalentSpec(uint32 i)
{
	if(!p_caster)
	{ 
		return;
	}

	//if times has not expired yet
	if( p_caster->m_tanlentSpecRespecTimer > getMSTime() )
	{
		p_caster->BroadcastMessage("Talent switching is still cooling down, remaining %u seconds",(p_caster->m_tanlentSpecRespecTimer - getMSTime())/1000);
		return;
	}

	//remove offhand whatever item and mail it to the owner
	if( p_caster->HasSpellwithNameHash( SPELL_HASH_TITAN_S_GRIP ) && p_caster->GetItemInterface() && p_caster->getClass() == WARRIOR ) 
	{
		Item * it = p_caster->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
		if( it )
			p_caster->RemoveAndMailItemFromSlot( EQUIPMENT_SLOT_OFFHAND );
	}

	//spamming same spell ? Nothing to switch ?
	uint32 new_spec = GetProto()->EffectBasePoints[i] % p_caster->m_talentSpecsCount;
	if( p_caster->m_talentActiveSpec == new_spec )
		return;
	
	//cannot switch in conditions
	if(p_caster->CombatStatus.IsInCombat())
	{
		SendCastResult(SPELL_FAILED_AFFECTING_COMBAT);
		return;
	}
	else if(p_caster->m_bg)
	{
		uint32 Type = p_caster->m_bg->GetType();
		if(Type >= BATTLEGROUND_ARENA_2V2 && Type <= BATTLEGROUND_ARENA_5V5)
		{
			SendCastResult(SPELL_FAILED_AFFECTING_COMBAT); // does the job
			return;
		}
		else
		{
			if(p_caster->m_bg->HasStarted())
			{
				SendCastResult(SPELL_FAILED_AFFECTING_COMBAT); // does the job
			}
		}
	}

	// 1 = primary, 2 = secondary
//	p_caster->m_talentActiveSpec = damage % p_caster->m_talentSpecsCount;
	// Send update
//	p_caster->smsg_TalentsInfo(false, 0, 0);
	p_caster->Switch_Talent_Spec();
	p_caster->m_tanlentSpecRespecTimer = getMSTime() + RESPECT_COOLDOWN_INTERVAL;

	//reset powers
	p_caster->SetPower(p_caster->GetPowerType(), 0);
	p_caster->UpdatePowerAmm( );
}

void Spell::SpellEffectRenamePet( uint32 i )
{
	if( !unitTarget || !unitTarget->IsPet() || 
		!SafePetCast(unitTarget)->GetPetOwner() || SafePetCast(unitTarget)->GetPetOwner()->getClass() != HUNTER )
		return;

	unitTarget->SetByte( UNIT_FIELD_BYTES_2, 2, UNIT_BYTE2_FLAG_RENAME|UNIT_BYTE2_FLAG_PET_DETAILS );
}

void Spell::SpellEffectBind(uint32 i)
{
	if(!playerTarget || !playerTarget->isAlive() || !m_caster)
		return;

	WorldPacket data(45);
	uint32 zoneid = playerTarget->GetZoneId();
	uint32 mapid = playerTarget->GetMapId();
	if(GetProto()->EffectMiscValue[i])
	{
		zoneid = GetProto()->EffectMiscValue[i];
		AreaTable * at = dbcArea.LookupEntry(zoneid);
		if(!at)
			return;
		mapid = at->mapId;
	}

	playerTarget->SetBindPoint(playerTarget->GetPositionX(), playerTarget->GetPositionY(), playerTarget->GetPositionZ(), mapid, zoneid);

	data.Initialize(SMSG_BINDPOINTUPDATE);
	data << playerTarget->GetBindPositionX() << playerTarget->GetBindPositionY() << playerTarget->GetBindPositionZ() << playerTarget->GetBindMapId() << playerTarget->GetBindZoneId();
	playerTarget->GetSession()->SendPacket( &data );

	data.Initialize(SMSG_PLAYERBOUND);
	data << m_caster->GetGUID() << playerTarget->GetBindZoneId();
	playerTarget->GetSession()->SendPacket(&data);
}

void Spell::SpellEffectLanguage(uint32 i)
{
/*	if(!playerTarget || !GetProto()->EffectMiscValue[i])
		return;

	if( GetProto()->EffectMiscValue[i] >= 15 )
	{
		sLog.outDebug(" Learn Language index out of range %u\n",GetProto()->EffectMiscValue[i]);
	}

	uint32 skills[15][2] = {
	{ 0, 0 },
	{ SKILL_LANG_ORCISH, 669 },
	{ SKILL_LANG_DARNASSIAN, 671 },
	{ SKILL_LANG_TAURAHE, 670 },
	{ SKILL_LANG_DWARVEN, 672 },
	{ SKILL_LANG_COMMON, 668 },
	{ SKILL_LANG_DEMON_TONGUE, 815 },
	{ SKILL_LANG_TITAN, 816 },
	{ SKILL_LANG_THALASSIAN, 813 },
	{ SKILL_LANG_DRACONIC, 814 },
	{ 0, 0 },
	{ SKILL_LANG_GNOMISH, 7430 },
	{ SKILL_LANG_TROLL, 7431 },
	{ SKILL_LANG_GUTTERSPEAK, 17737 },
	{ SKILL_LANG_DRAENEI, 29932 },
	};

	if(skills[GetProto()->EffectMiscValue[i]][0])
	{
		playerTarget->_AddSkillLine(skills[GetProto()->EffectMiscValue[i]][0], 300, 300);   
		playerTarget->addSpell(skills[GetProto()->EffectMiscValue[i]][1]);
	}

	//no multi casts in case of playercreate spell
	playerTarget->removeSpell( GetProto()->Id, false, false, 0 );
	*/
}

void Spell::SpellEffectCreatePet(uint32 i)
{
	if( !playerTarget )
		return;

	if(playerTarget->GetSummon())
	{
		playerTarget->GetSummon()->Remove( true, true );
		playerTarget->SetSummon( NULL );
	}
	CreatureInfo *ci = CreatureNameStorage.LookupEntry( GetProto()->EffectMiscValue[i] );
	if( ci )
	{
		Pet *pPet = objmgr.CreatePet( GetProto()->EffectMiscValue[i], playerTarget->GeneratePetNumber() );
		pPet->CreateAsSummon( GetProto()->EffectMiscValue[i], ci, NULL, playerTarget, GetProto(), 1, 0 );
	}
}

void Spell::SpellEffectTeachTaxiPath( uint32 i )
{
	if( !playerTarget || !GetProto()->EffectTriggerSpell[i] )
		return;

	playerTarget->removeSpell( GetProto()->Id, false, false, 0 );
	uint8 field = (uint8)((GetProto()->EffectTriggerSpell[i] - 1) / 32);
	uint32 submask = 1<<((GetProto()->EffectTriggerSpell[i]-1)%32);

	// Check for known nodes
	if (!(playerTarget->GetTaximask(field) & submask))
	{
		playerTarget->SetTaximask(field, (submask | playerTarget->GetTaximask(field)) );

		playerTarget->GetSession()->OutPacket(SMSG_NEW_TAXI_PATH);

		//Send packet
		WorldPacket update(SMSG_TAXINODE_STATUS, 9);
		update << uint64( 0 ) << uint8( 1 );
		playerTarget->GetSession()->SendPacket( &update );
	}
}

void Spell::SpellEffectWMODamage(uint32 i)
{
	if(gameObjTarget && gameObjTarget->GetInfo() && gameObjTarget->GetInfo()->Type == GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING)
		gameObjTarget->TakeDamage(uint32(damage), m_caster, p_caster, m_spellInfo->Id);
}

void Spell::SpellEffectWMORepair(uint32 i)
{
	if(gameObjTarget && gameObjTarget->GetInfo()->Type == GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING)
		gameObjTarget->Rebuild();
}
