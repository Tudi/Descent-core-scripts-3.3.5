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

void CreateDummySpell(uint32 id)
{
	const char * name = "Dummy Trigger";
	SpellEntry * sp = new SpellEntry;
	memset(sp, 0, sizeof(SpellEntry));
	sp->Id = id;
	sp->Attributes = 384;
	sp->AttributesEx = 268435456;
	sp->AttributesExB = 4;
	sp->CastingTimeIndex=1;
	sp->procChance=0;
	sp->rangeIndex=13;
	sp->EquippedItemClass=uint32(-1);
	sp->Effect[0]=SPELL_EFFECT_DUMMY;
	sp->EffectImplicitTargetA[0]=EFF_TARGET_SELF;
	sp->NameHash=crc32((const unsigned char*)name, (unsigned int)strlen(name));
	sp->dmg_multiplier[0]=1.0f;
	sp->StanceBarOrder=-1;
	dbcSpell.SetRow(id,sp);
//	sWorld.dummyspells.push_back(sp);
} 

inline void swapval( int32 &a, int32 &b ){	int32 c; c=a; a=b; b=c; }
inline void swapval( uint32 &a, uint32 &b ){	uint32 c; c=a; a=b; b=c; }
inline void swapval( float &a, float &b ){	float c; c=a; a=b; b=c; }

inline void SetAllSpellCoef(SpellEntry *sp,float new_val)
{
	sp->fixed_dddhcoef = new_val;
	sp->fixed_hotdotcoef = new_val;
}

void SpellEntryEffectSwap(SpellEntry *src,SpellEntry *dst,uint32 indsrc,uint32 inddst)
{
	if( indsrc>2 || inddst>2 )
		return;
	swapval( dst->Effect[ inddst ], src->Effect[ indsrc ]);
	swapval( dst->EffectDieSides[ inddst ], src->EffectDieSides[ indsrc ]);
//	swapval( dst->EffectBaseDice[ inddst ], src->EffectBaseDice[ indsrc ]);
//	swapval( dst->EffectDicePerLevel[ inddst ], src->EffectDicePerLevel[ indsrc ]);
	swapval( dst->EffectRealPointsPerLevel[ inddst ], src->EffectRealPointsPerLevel[ indsrc ]);
	swapval( dst->EffectBasePoints[ inddst ], src->EffectBasePoints[ indsrc ]);
	swapval( dst->EffectMechanic[ inddst ], src->EffectMechanic[ indsrc ]);
	swapval( dst->EffectImplicitTargetA[ inddst ], src->EffectImplicitTargetA[ indsrc ]);
	swapval( dst->EffectImplicitTargetB[ inddst ], src->EffectImplicitTargetB[ indsrc ]);
	swapval( dst->EffectRadiusIndex[ inddst ], src->EffectRadiusIndex[ indsrc ]);
	swapval( dst->EffectApplyAuraName[ inddst ], src->EffectApplyAuraName[ indsrc ]);
	swapval( dst->EffectAmplitude[ inddst ], src->EffectAmplitude[ indsrc ]);
	swapval( dst->EffectConversionCoef[ inddst ], src->EffectConversionCoef[ indsrc ]);
	swapval( dst->EffectChainTarget[ inddst ], src->EffectChainTarget[ indsrc ]);
	swapval( dst->EffectItemType[ inddst ], src->EffectItemType[ indsrc ]);
	swapval( dst->EffectMiscValue[ inddst ], src->EffectMiscValue[ indsrc ]);
	swapval( dst->EffectMiscValueB[ inddst ], src->EffectMiscValueB[ indsrc ]);
	swapval( dst->EffectTriggerSpell[ inddst ], src->EffectTriggerSpell[ indsrc ]);
	swapval( dst->EffectPointsPerComboPoint[ inddst ], src->EffectPointsPerComboPoint[ indsrc ]);
	swapval( dst->EffectSpellGroupRelation[ inddst ][0], src->EffectSpellGroupRelation[ indsrc ][0]);
	swapval( dst->EffectSpellGroupRelation[ inddst ][1], src->EffectSpellGroupRelation[ indsrc ][1]);
	swapval( dst->EffectSpellGroupRelation[ inddst ][2], src->EffectSpellGroupRelation[ indsrc ][2]);
	swapval( dst->SpellGroupType[ inddst ], src->SpellGroupType[ indsrc ]);
	swapval( dst->dmg_multiplier[ inddst ], src->dmg_multiplier[ indsrc ]);
}

void SpellEntryEffectCopy(SpellEntry *src,SpellEntry *dst,uint32 indsrc,uint32 inddst)
{
	if( indsrc>2 || inddst>2 )
		return;
	dst->Effect[ inddst ] = src->Effect[ indsrc ];
	dst->EffectDieSides[ inddst ] = src->EffectDieSides[ indsrc ];
//	dst->EffectBaseDice[ inddst ] = src->EffectBaseDice[ indsrc ];
//	dst->EffectDicePerLevel[ inddst ] = src->EffectDicePerLevel[ indsrc ];
	dst->EffectRealPointsPerLevel[ inddst ] = src->EffectRealPointsPerLevel[ indsrc ];
	dst->EffectBasePoints[ inddst ] = src->EffectBasePoints[ indsrc ];
	dst->EffectMechanic[ inddst ] = src->EffectMechanic[ indsrc ];
	dst->EffectImplicitTargetA[ inddst ] = src->EffectImplicitTargetA[ indsrc ];
	dst->EffectImplicitTargetB[ inddst ] = src->EffectImplicitTargetB[ indsrc ];
	dst->EffectRadiusIndex[ inddst ] = src->EffectRadiusIndex[ indsrc ];
	dst->EffectApplyAuraName[ inddst ] = src->EffectApplyAuraName[ indsrc ];
	dst->EffectAmplitude[ inddst ] = src->EffectAmplitude[ indsrc ];
	dst->EffectConversionCoef[ inddst ] = src->EffectConversionCoef[ indsrc ];
	dst->EffectChainTarget[ inddst ] = src->EffectChainTarget[ indsrc ];
	dst->EffectItemType[ inddst ] = src->EffectItemType[ indsrc ];
	dst->EffectMiscValue[ inddst ] = src->EffectMiscValue[ indsrc ];
	dst->EffectMiscValueB[ inddst ] = src->EffectMiscValueB[ indsrc ];
	dst->EffectTriggerSpell[ inddst ] = src->EffectTriggerSpell[ indsrc ];
	dst->EffectPointsPerComboPoint[ inddst ] = src->EffectPointsPerComboPoint[ indsrc ];
	dst->EffectSpellGroupRelation[ inddst ][0] = src->EffectSpellGroupRelation[ indsrc ][0];
	dst->EffectSpellGroupRelation[ inddst ][1] = src->EffectSpellGroupRelation[ indsrc ][1];
	dst->EffectSpellGroupRelation[ inddst ][2] = src->EffectSpellGroupRelation[ indsrc ][2];
	dst->SpellGroupType[ inddst ] = src->SpellGroupType[ indsrc ];
	dst->dmg_multiplier[ inddst ] = src->dmg_multiplier[ indsrc ];
}

#define SetSpellPowerCoeffsAll(sp,x) 			{ sp->fixed_dddhcoef = x;	\
			sp->fixed_hotdotcoef = x; }

//instead making a jumped cast we use directly copy
void SpellEntryCopyToEntry(SpellEntry *src,SpellEntry *dst)
{
	uint32 temp_entry = dst->Id; //-> the only thing we save from old spell
	memcpy(dst,src,sizeof(SpellEntry));
	dst->Id = temp_entry;
}

void Apply112SpellFixes()
{
	SpellEntry * sp;
	// Spell 1455 Proc Chance (Life Tap Rank 2)
	sp = dbcSpell.LookupEntryForced(1455);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 1456 Proc Chance (Life Tap Rank 3)
	sp = dbcSpell.LookupEntryForced(1456);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 3391 Proc Chance (Thrash )
	sp = dbcSpell.LookupEntryForced(3391);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 8033 Proc Chance (Frostbrand Weapon Rank 1)
	sp = dbcSpell.LookupEntryForced(8033);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 8034 Proc Chance (Frostbrand Attack Rank 1)
	sp = dbcSpell.LookupEntryForced(8034);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 8037 Proc Chance (Frostbrand Attack Rank 2)
	sp = dbcSpell.LookupEntryForced(8037);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 8182 Proc Chance (Frost Resistance Rank 1)
	sp = dbcSpell.LookupEntryForced(8182);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 8185 Proc Chance (Fire Resistance Rank 1)
	sp = dbcSpell.LookupEntryForced(8185);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 8516 Proc Chance (Windfury Totem Rank 1)
//	sp = dbcSpell.LookupEntryForced(8516);
	//if(sp != NULL)
//		sp->procChance = 10;

	// Spell 10456 Proc Chance (Frostbrand Weapon Rank 3)
	sp = dbcSpell.LookupEntryForced(10456);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 10458 Proc Chance (Frostbrand Attack Rank 3)
	sp = dbcSpell.LookupEntryForced(10458);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 10476 Proc Chance (Frost Resistance Rank 2)
	sp = dbcSpell.LookupEntryForced(10476);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 10477 Proc Chance (Frost Resistance Rank 3)
	sp = dbcSpell.LookupEntryForced(10477);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 10534 Proc Chance (Fire Resistance Rank 2)
	sp = dbcSpell.LookupEntryForced(10534);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 10535 Proc Chance (Fire Resistance Rank 3)
	sp = dbcSpell.LookupEntryForced(10535);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 10608 Proc Chance (Windfury Totem Rank 2)
	//sp = dbcSpell.LookupEntryForced(10608);
	//if(sp != NULL)
	//	sp->procChance = 10;

	// Spell 10610 Proc Chance (Windfury Totem Rank 3)
//	sp = dbcSpell.LookupEntryForced(10610);
	//if(sp != NULL)
//		sp->procChance = 10;

	// Spell 11175 Group Relation (Permafrost Rank 1)
	//Increases the duration of your Chill effects by $/1000;S1 $lsec:secs;, reduces the target's speed by an additional $s2%, and reduces the target's healing received by $s3%.
	sp = dbcSpell.LookupEntryForced(11175);
	//if(sp != NULL) 
	{
		sp->EffectMiscValue[1] = SMT_MISC_EFFECT;
		sp->EffectBasePoints[1] = MIN( sp->EffectBasePoints[1],sp->EffectBasePoints[2] );
		sp->Effect[2] = SPELL_EFFECT_NULL;
	}
	sp = dbcSpell.LookupEntryForced(12569);
	//if(sp != NULL)
	{
		sp->EffectMiscValue[1] = SMT_MISC_EFFECT;
		sp->EffectBasePoints[1] = MIN( sp->EffectBasePoints[1],sp->EffectBasePoints[2] );
		sp->Effect[2] = SPELL_EFFECT_NULL;
	}
	sp = dbcSpell.LookupEntryForced(12571);
	//if(sp != NULL) 
	{
		sp->EffectMiscValue[1] = SMT_MISC_EFFECT;
		sp->EffectBasePoints[1] = MIN( sp->EffectBasePoints[1],sp->EffectBasePoints[2] );
		sp->Effect[2] = SPELL_EFFECT_NULL;
	}

	// Spell 12284 Proc Chance (Mace Specialization Rank 1)
	sp = dbcSpell.LookupEntryForced(12284);
	//if(sp != NULL)
		sp->procChance = 1;

	// Spell 12292 Proc Chance (Death Wish )
	sp = dbcSpell.LookupEntryForced(12292);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 12322 Proc Chance (Unbridled Wrath Rank 1)
	sp = dbcSpell.LookupEntryForced(12322);
	//if(sp != NULL)
		sp->procChance = 8;

	// Spell 23689 Proc Chance (Darkmoon Card: Heroism)
	sp = dbcSpell.LookupEntryForced(23689);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 12701 Proc Chance (Mace Specialization Rank 2)
	sp = dbcSpell.LookupEntryForced(12701);
	//if(sp != NULL)
		sp->procChance = 2;

	// Spell 12702 Proc Chance (Mace Specialization Rank 3)
	sp = dbcSpell.LookupEntryForced(12702);
	//if(sp != NULL)
		sp->procChance = 3;

	// Spell 12703 Proc Chance (Mace Specialization Rank 4)
	sp = dbcSpell.LookupEntryForced(12703);
	//if(sp != NULL)
		sp->procChance = 4;

	// Spell 12704 Proc Chance (Mace Specialization Rank 5)
	sp = dbcSpell.LookupEntryForced(12704);
	//if(sp != NULL)
		sp->procChance = 6;

	// Spell 12999 Proc Chance (Unbridled Wrath Rank 2)
	sp = dbcSpell.LookupEntryForced(12999);
	//if(sp != NULL)
		sp->procChance = 16;

	// Spell 13000 Proc Chance (Unbridled Wrath Rank 3)
	sp = dbcSpell.LookupEntryForced(13000);
	//if(sp != NULL)
		sp->procChance = 24;

	// Spell 13001 Proc Chance (Unbridled Wrath Rank 4)
	sp = dbcSpell.LookupEntryForced(13001);
	//if(sp != NULL)
		sp->procChance = 32;

	// Spell 13002 Proc Chance (Unbridled Wrath Rank 5)
	sp = dbcSpell.LookupEntryForced(13002);
	//if(sp != NULL)
		sp->procChance = 40;

	// Spell 14076 Proc Chance (Dirty Tricks Rank 1)
	sp = dbcSpell.LookupEntryForced(14076);
	//if(sp != NULL)
		sp->procChance = 30;

	// Spell 14094 Proc Chance (Dirty Tricks Rank 2)
	sp = dbcSpell.LookupEntryForced(14094);
	//if(sp != NULL)
		sp->procChance = 60;

	// Spell 14177 Group Relation\Interrupt Flag (Cold Blood )
	sp = dbcSpell.LookupEntryForced(14177);
	//if(sp != NULL) 
	{
		sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_HOSTILE_SPELL_INFLICTED;
//		sp->procCharges++; //no idea if this is required 
	}

	// Spell 15494 Proc Chance (Fury of Forgewright )
	sp = dbcSpell.LookupEntryForced(15494);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 15600 Proc Chance (Hand of Justice )
	sp = dbcSpell.LookupEntryForced(15600);
	//if(sp != NULL)
		sp->procChance = 2;

	// Spell 15601 Proc Chance (Hand of Justice )
	sp = dbcSpell.LookupEntryForced(15601);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 15642 Proc Chance (Ironfoe )
	sp = dbcSpell.LookupEntryForced(15642);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 16246 Group Relation (Clearcasting )
	sp = dbcSpell.LookupEntryForced(16246);
	//if(sp != NULL)
	{
		sp->procCharges = 2; // Should be 2 but now 1 is used when spell triggers leaving 2
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	// Spell 16352 Proc Chance (Frostbrand Attack Rank 4)
	sp = dbcSpell.LookupEntryForced(16352);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 16353 Proc Chance (Frostbrand Attack Rank 5)
	sp = dbcSpell.LookupEntryForced(16353);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 16355 Proc Chance (Frostbrand Weapon Rank 4)
	sp = dbcSpell.LookupEntryForced(16355);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 16356 Proc Chance (Frostbrand Weapon Rank 5)
	sp = dbcSpell.LookupEntryForced(16356);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 16459 Proc Chance (Sword Specialization )
	sp = dbcSpell.LookupEntryForced(16459);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 16843 Proc Chance (Crimson Fury )
	sp = dbcSpell.LookupEntryForced(16843);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 16850 Proc Chance (Celestial Focus Rank 1)
	sp = dbcSpell.LookupEntryForced(16850);
	//if(sp != NULL)
	{
		sp->procChance = 3;
		sp->ProcOnNameHash[0] = SPELL_HASH_STARFIRE;
	}

	// Spell 16923 Proc Chance (Celestial Focus Rank 2)
	sp = dbcSpell.LookupEntryForced(16923);
	//if(sp != NULL)
	{
		sp->procChance = 6;
		sp->ProcOnNameHash[0] = SPELL_HASH_STARFIRE;
	}

	// Spell 16924 Proc Chance (Celestial Focus Rank 3)
	sp = dbcSpell.LookupEntryForced(16924);
	//if(sp != NULL)
	{
		sp->procChance = 9;
		sp->ProcOnNameHash[0] = SPELL_HASH_STARFIRE;
	}

	// Spell 18797 Proc Chance (Flurry Axe )
	sp = dbcSpell.LookupEntryForced(18797);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 18803 Proc Chance (Focus )
	sp = dbcSpell.LookupEntryForced(18803);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 19105 Proc Chance (MHTest01 Effect )
	sp = dbcSpell.LookupEntryForced(19105);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 19109 Proc Chance (MHTest02 Effect )
	sp = dbcSpell.LookupEntryForced(19109);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 20178 Proc Chance (Reckoning )
	sp = dbcSpell.LookupEntryForced(20178);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 21919 Proc Chance (Thrash )
	sp = dbcSpell.LookupEntryForced(21919);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 23158 Proc Chance (Concussive Shot Cooldown Reduction )
	sp = dbcSpell.LookupEntryForced(23158);
	//if(sp != NULL)
		sp->procChance = 4;

	// Spell 26022 Proc Chance (Pursuit of Justice Rank 1)
	sp = dbcSpell.LookupEntryForced(26022);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 26023 Proc Chance (Pursuit of Justice Rank 2)
	sp = dbcSpell.LookupEntryForced(26023);
	//if(sp != NULL)
		sp->procChance = 100;

	// Spell 27035 Proc Chance (Sword Specialization (OLD) )
//	sp = dbcSpell.LookupEntryForced(27035);
	//if(sp != NULL)
//		sp->procChance = 10;

	// Spell 27521 Proc Chance (Mana Restore )
	sp = dbcSpell.LookupEntryForced(27521);
	//if(sp != NULL)
		sp->procChance = 2;

	// Spell 27867 Proc Chance (Freeze )
	sp = dbcSpell.LookupEntryForced(27867);
	//if(sp != NULL)
		sp->procChance = 2;

	// Spell 25500 Proc Chance (Frostbrand Weapon Rank 6)
	sp = dbcSpell.LookupEntryForced(25500);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 25501 Proc Chance (Frostbrand Attack Rank 6)
	sp = dbcSpell.LookupEntryForced(25501);
	//if(sp != NULL)
		sp->procChance = 10;

	// Spell 38617 Proc Chance (Frostbrand Attack )
	sp = dbcSpell.LookupEntryForced(38617);
	//if(sp != NULL)
		sp->procChance = 10;
}

void MarkSpellLineAsTalentSpecSpecific(SpellEntry *sp)
{
	//get skill line of this spell
	uint32 skillline = sp->spell_skilline[0];
/*	do
	{
		sp->spell_learn_is_linked_to_talent = true;
		sp = dbcSpell.LookupEntryForced( sp->spell_learn_next_level_spell );
	}while( sp );*/
	for(uint32 x=0; x < dbcSkillLineSpell.GetNumRows(); x++)
	{
		skilllinespell * spsk = dbcSkillLineSpell.LookupRow(x);
		if( spsk->skilline != skillline )
			continue;
		SpellEntry *spt = dbcSpell.LookupEntryForced( spsk->spell );
		if( !spt || spt->NameHash != sp->NameHash )
			continue;
		spt->spell_learn_is_linked_to_talent = true;
	}
}

//link spell to skill lines. 
//a spell can be in multiple lines but most of the time only in 1
//set spell next level id
void SetSpellSkillines()
{
	//set spell skilline
	for(uint32 x=0; x < dbcSkillLineSpell.GetNumRows(); x++)
	{
		skilllinespell * spsk = dbcSkillLineSpell.LookupRow(x);
		SpellEntry *sp = dbcSpell.LookupEntryForced( spsk->spell );
		if( !sp )
			continue;
		//just a shortcut so we do not have to search for spell skilline then get "next" of the skilline
		//!! maybe just pet spells have this set. Player spells do not have it
		sp->spell_learn_next_level_spell = spsk->next;
		if( sp->spell_skilline_assoc_counter >= SPELL_SKILL_LINK_LIMIT )
			continue;
		sp->spell_skilline[ sp->spell_skilline_assoc_counter ] = spsk->skilline;
		sp->spell_skilline_assoc_counter++;
		//try to find a prev for this skill in case we need to remove it while learning
		for(uint32 y=0; y < dbcSkillLineSpell.GetNumRows(); y++)
		{
			skilllinespell * spsk2 = dbcSkillLineSpell.LookupRow(y);
			if( spsk2->next == spsk->Id )
			{
				spsk->prev = spsk2->Id;
				break;
			}
		}
	}
}

void SetSpellTalentLines()
{
	uint32 i,j;
	for(i = 0; i < dbcTalent.GetNumRows(); ++i)
	{
		TalentEntry * tal = dbcTalent.LookupRow(i);
		for(j = 0; j < 5; ++j)
			if(tal->RankID[j] != 0)
			{
				//as quick lookup we add these info to spells structs
				SpellEntry *sp = dbcSpell.LookupEntryForced( tal->RankID[j] );
				//if( sp != NULL )
				{
					if( sp->talent_entry_assoc_counter < SPELL_SKILL_LINK_LIMIT )
					{
						sp->talent_entry[sp->talent_entry_assoc_counter] = tal;
						sp->talent_entry_rank[sp->talent_entry_assoc_counter] = j;
	//					sp->talent_tree[sp->talent_entry_assoc_counter] = tal->TalentTree;
						sp->talent_entry_assoc_counter++;
					}
					MarkSpellLineAsTalentSpecSpecific( sp );
				}
				for(uint32 k=0;k<3;k++)
					if( sp->Effect[ k ] == SPELL_EFFECT_LEARN_SPELL 
						|| sp->Effect[ k ] == SPELL_EFFECT_LEARN_PET_SPELL 
						//these are only marked since skillines would teach us when using ".learn all"
						//we are not learning these in standard way
						|| sp->Effect[ k ] == SPELL_EFFECT_TRIGGER_SPELL
						|| sp->EffectApplyAuraName[ k ] == SPELL_AURA_PROC_TRIGGER_SPELL
						)
					{
						SpellEntry *sp2 = dbcSpell.LookupEntryForced( sp->EffectTriggerSpell[ k ] );
						if( sp2 )
							MarkSpellLineAsTalentSpecSpecific( sp2 );
					}
			}
	}
}

void SetSpellSkill()
{
	for(uint32 i = 0; i < dbcSkillLineSpell.GetNumRows(); i++)
	{
		skilllinespell *sps = dbcSkillLineSpell.LookupRow(i);
		if (sps)
		{
			SpellEntry *sp = dbcSpell.LookupEntryForced( sps->spell );
			if( sp )
				sp->spell_skill = sps;
		}
	}
}

//comes after loading spells, items ....
void LoadSpellForcedTargetting()
{
	QueryResult *spt_sql = WorldDatabase.Query(	"SELECT * FROM Spell_Forced_Targetting" );

	if(spt_sql)
	{
		do 
		{
			Field *fields = spt_sql->Fetch();
			uint32 spellid = fields[0].GetUInt32();
			uint32 tt = fields[1].GetUInt32();
			uint32 tv = fields[2].GetUInt32();
			SpellEntry *sp = dbcSpell.LookupEntryForced( spellid );
			if( sp )
			{
				sp->required_target_type = tt + 1;
				sp->required_target_value.push_back( tv );
			}
		} while(spt_sql->NextRow());
		delete spt_sql;
		spt_sql = NULL;
	}
}

void ApplyNormalFixes()
{
	Log.Notice("World", "Setting Spell SkillLines....");
	SetSpellSkillines();
	Log.Notice("World", "Setting Spell Skills....");
	SetSpellSkill();
	//Updating spell.dbc

	Log.Notice("World", "Processing %u spells...", dbcSpell.GetNumRows());
	Apply112SpellFixes();

	uint32 i;
	uint32 cnt = dbcSpell.GetNumRows();
	uint32 effect;
	// Relation Groups

	for(uint32 x=0; x < cnt; x++)
	{
		// Read every SpellEntry row
		SpellEntry * sp = dbcSpell.LookupRow(x);

		uint32 rank = 0;
		uint32 namehash = 0;

		sp->self_cast_only = false;
		sp->apply_on_shapeshift_change = false;
		sp->chained_cast = NULL;

		// hash the name
		//!!!!!!! representing all strings on 32 bits is dangerous. There is a chance to get same hash for a lot of strings ;)
        namehash = crc32((const unsigned char*)sp->Name, (unsigned int)strlen(sp->Name));
		sp->NameHash   = namehash; //need these set before we start processing spells

		float radius=std::max(::GetRadius(dbcSpellRadius.LookupEntry(sp->EffectRadiusIndex[0])),::GetRadius(dbcSpellRadius.LookupEntry(sp->EffectRadiusIndex[1])));
		radius=std::max(::GetRadius(dbcSpellRadius.LookupEntry(sp->EffectRadiusIndex[2])),radius);
		radius=std::max(GetMaxRange(dbcSpellRange.LookupEntry(sp->rangeIndex)),radius);
		sp->base_range_or_radius_sqr = radius*radius;

		sp->ai_target_type = GetAiTargetType( sp );
		// NEW SCHOOLS AS OF 2.4.0:
		/* (bitwise)
		SCHOOL_NORMAL = 1,
		SCHOOL_HOLY   = 2,
		SCHOOL_FIRE   = 4,
		SCHOOL_NATURE = 8,
		SCHOOL_FROST  = 16,
		SCHOOL_SHADOW = 32,
		SCHOOL_ARCANE = 64
		*/

		//charge auras should still stack anytime :P
		if( sp->procCharges > (int32)sp->maxstack )
			sp->maxstack = sp->procCharges;
		// Save School as SchoolMask, and set School as an index
		sp->SchoolMask = sp->School;
		for (i=0; i<SCHOOL_COUNT; i++)
		{
			if (sp->School & (1<<i))
			{
				sp->School = i;
				break;
			}
		}

		//spells that self cast leading to stack consume = 0 size dump
		for(uint32 k=0;k<3;k++)
		{
			if( sp->Effect[ k ] == SPELL_EFFECT_TRIGGER_SPELL && sp->EffectTriggerSpell[k] == sp->Id )
			{
				sp->Effect[ k ] = SPELL_EFFECT_NULL;
				sp->EffectTriggerSpell[k] = 0; 
			}
			if( sp->Effect[ k ] == SPELL_EFFECT_APPLY_AREA_AURA || sp->Effect[ k ] == SPELL_EFFECT_APPLY_AREA_AURA2 )
				sp->AttributesEx |= ATTRIBUTESEX_VISIBLE;	//visible for caster also even though it is considered passive aura
		}

		// correct caster/target aura states
		if( sp->CasterAuraState > 1 )
			sp->CasterAuraState = 1 << ( sp->CasterAuraState - 1 );
		if( sp->TargetAuraState > 1 )
			sp->TargetAuraState = 1 << ( sp->TargetAuraState - 1 );

		// apply on shapeshift change
		if( sp->NameHash == SPELL_HASH_TRACK_HUMANOIDS )
			sp->apply_on_shapeshift_change = true;

		// Unleashed Rage
		if( sp->NameHash == SPELL_HASH_UNLEASHED_RAGE)
			sp->procFlags = PROC_ON_CRIT_ATTACK;

//		if( sp->NameHash == SPELL_HASH_BLOOD_FURY || sp->NameHash == SPELL_HASH_SHADOWSTEP )
//			sp->always_apply = true;

		//no idea wtf for this is. Appeared in 3.2.x client
		for(int i=0;i<8;i++)
			if( sp->Reagent[i] == -1 || sp->Reagent[i] == 4294967294 )
			{
				sp->Reagent[i] = 0;
				sp->ReagentCount[i] = 0;
			}

		//there are some spells that change the "damage" value of 1 effect to another : devastate = bonus first then damage
		//this is a total bullshit so remove it when spell system supports effect overwriting
		for( uint32 col1_swap = 0; col1_swap < 2 ; col1_swap++ )
			for( uint32 col2_swap = col1_swap + 1 ; col2_swap < 3 ; col2_swap++ )
				if( sp->Effect[col1_swap] == SPELL_EFFECT_WEAPON_PERCENT_DAMAGE && sp->Effect[col2_swap] == SPELL_EFFECT_DUMMYMELEE )
					SpellEntryEffectSwap(sp,sp,col1_swap,col2_swap);

		for(uint32 b=0;b<3;++b)
		{
/*			if( sp->EffectTriggerSpell[b] != 0 && dbcSpell.LookupEntryForced(sp->EffectTriggerSpell[b]) == NULL)
			{
				// proc spell referencing non-existant spell. create a dummy spell for use w/ it. 
				CreateDummySpell(sp->EffectTriggerSpell[b]);
			}*/

			if( sp->Attributes & ATTRIBUTES_ONLY_OUTDOORS && sp->EffectApplyAuraName[b] == SPELL_AURA_MOUNTED )
			{
				sp->Attributes &= ~ATTRIBUTES_ONLY_OUTDOORS;
			}

			// fill in more here
			/*switch( sp->EffectImplicitTargetA[b] )
			{
			case 1:
			case 9:
				sp->self_cast_only = true;
				break;
			}

			// fill in more here too
			switch( sp->EffectImplicitTargetB[b] )
			{
			case 1:
			case 9:
				sp->self_cast_only = true;
				break;
			}*/
		}

		/*if( sp->self_cast_only && !(sp->Attributes&64))
			printf("SPELL SELF CAST ONLY: %s %u\n", sp->Name, sp->Id);*/

		if(!strcmp(sp->Name, "Hearthstone") || !strcmp(sp->Name, "Stuck") || !strcmp(sp->Name, "Astral Recall"))
			sp->self_cast_only = true;

		uint32 max_amplitude = MAX(MAX(sp->EffectAmplitude[0],sp->EffectAmplitude[1]),sp->EffectAmplitude[2]);
		bool does_not_expire_aura = false;
		sp->quick_duration_min = max_amplitude;
        if(sp->DurationIndex)
        {
            SpellDuration *sd=dbcSpellDuration.LookupEntry(sp->DurationIndex);
            if(sd)
            {
				//base duration to which we add dur2 that is based on level
				//duration 3 is limitation to dur1+dur2 ? false if you ask me 
				sp->quick_duration_min = MAX( sd->Duration3, sd->Duration1 );
				if( sd->Duration2 )
					sp->quick_duration_min = MIN( sp->quick_duration_min, sd->Duration2 );
            }
            else
			{
//                sp->quick_duration_min = (uint32)-1; //this is huge
				does_not_expire_aura = true;
			}
        }
		else 
		{
			sp->quick_duration_min = MAX( sp->quick_duration_min, 1); //avoid division by 0 errors ?
			does_not_expire_aura = true;
		}
		sp->quick_maxAmplitude = max_amplitude;
		sp->quick_ExtendDuration = 0;
		if( does_not_expire_aura == false && max_amplitude > 0 )
		{
			sp->quick_tickcount = MAX(1,sp->quick_duration_min / MAX(1,max_amplitude));
			if( sp->quick_duration_min != (uint32)-1)
			{
				if( sp->quick_tickcount <= 1 )
					sp->quick_ExtendDuration = 100;	//just 1 tick over all.Let's not double duration
				else
					sp->quick_ExtendDuration = sp->quick_maxAmplitude + 100;
			}
		}
		else
			sp->quick_tickcount = 1;	//consider spell not having ticks at all

		sp->proc_interval = DEFAULT_SPELL_PROC_INTERVAL;//trigger at each event but no spams pls
		sp->c_is_flags = 0;
		sp->spell_coef_flags = 0;
		sp->fixed_dddhcoef = -1.0f;
		sp->fixed_hotdotcoef = -1.0f;

		if( sp->Effect[0] == SPELL_EFFECT_APPLY_AURA || sp->Effect[0] == SPELL_EFFECT_APPLY_AREA_AURA || sp->Effect[0] == SPELL_EFFECT_APPLY_AREA_AURA2 ||
			sp->Effect[1] == SPELL_EFFECT_APPLY_AURA || sp->Effect[1] == SPELL_EFFECT_APPLY_AREA_AURA || sp->Effect[1] == SPELL_EFFECT_APPLY_AREA_AURA2 ||
			sp->Effect[2] == SPELL_EFFECT_APPLY_AURA || sp->Effect[2] == SPELL_EFFECT_APPLY_AREA_AURA || sp->Effect[2] == SPELL_EFFECT_APPLY_AREA_AURA2 
			)
			sp->c_is_flags |= SPELL_FLAG_IS_BUFF;

		if( sp->spell_skilline[0] && ( sp->spell_skilline[0] == SKILL_FIRST_AID 
			|| sp->spell_skilline[0] == SKILL_BLACKSMITHING
			|| sp->spell_skilline[0] == SKILL_LEATHERWORKING
			|| sp->spell_skilline[0] == SKILL_ALCHEMY
			|| sp->spell_skilline[0] == SKILL_HERBALISM
			|| sp->spell_skilline[0] == SKILL_COOKING
			|| sp->spell_skilline[0] == SKILL_MINING
			|| sp->spell_skilline[0] == SKILL_TAILORING
			|| sp->spell_skilline[0] == SKILL_ENGINEERING
			|| sp->spell_skilline[0] == SKILL_ENCHANTING
			|| sp->spell_skilline[0] == SKILL_FISHING
			|| sp->spell_skilline[0] == SKILL_SKINNING
			|| sp->spell_skilline[0] == SKILL_JEWELCRAFTING
			|| sp->spell_skilline[0] == SKILL_INSCRIPTION
			|| sp->spell_skilline[0] == SKILL_RUNEFORGING
			|| sp->spell_skilline[0] == SKILL_ARCHAEOLOGY ) )
				sp->c_is_flags |= SPELL_FLAG_IS_DISABLE_OTHER_SPELL_CPROC;	//maybe not for all but mostly all
//		if( sp->spell_skilline[0] &&
//			( sp->EffectApplyAuraName[0] == SPELL_AURA_ADD_FLAT_MODIFIER || sp->EffectApplyAuraName[1] == SPELL_AURA_ADD_FLAT_MODIFIER || sp->EffectApplyAuraName[2] == SPELL_AURA_ADD_FLAT_MODIFIER ||
//				sp->EffectApplyAuraName[0] == SPELL_AURA_ADD_PCT_MODIFIER || sp->EffectApplyAuraName[1] == SPELL_AURA_ADD_PCT_MODIFIER || sp->EffectApplyAuraName[2] == SPELL_AURA_ADD_PCT_MODIFIER ) )
//		{
//			sp->RequiredPlayerClass = xxx;
//		}
		

		// parse rank text
		if( !sscanf( sp->Rank, "Rank %u", (unsigned int*)&rank) )
			rank = 0;

		else if( namehash == SPELL_HASH_ARCANE_SHOT )		
			sp->c_is_flags |= SPELL_FLAG_IS_NOT_USING_DMG_BONUS;

		else if( namehash == SPELL_HASH_SERPENT_STING )	
		{
			sp->c_is_flags |= SPELL_FLAG_IS_NOT_USING_DMG_BONUS;
			sp->fixed_dddhcoef = 0.0000000001f;
			sp->fixed_hotdotcoef = 0.0000000001f;
		}

		if( sp->School == SCHOOL_FROST )
		{
		/*	if( sp->EffectApplyAuraName[0] == SPELL_AURA_MOD_ROOT 
				|| sp->EffectApplyAuraName[1] == SPELL_AURA_MOD_ROOT 
				|| sp->EffectApplyAuraName[2] == SPELL_AURA_MOD_ROOT )
				sp->c_is_flags |= SPELL_FLAG_IS_CHILL_SPELL;*/
			//spell is decreasing speed -> not sure about this part
			if( sp->EffectApplyAuraName[0] == SPELL_AURA_MOD_DECREASE_SPEED
				|| sp->EffectApplyAuraName[1] == SPELL_AURA_MOD_DECREASE_SPEED 
				|| sp->EffectApplyAuraName[2] == SPELL_AURA_MOD_DECREASE_SPEED )
				sp->c_is_flags |= SPELL_FLAG_IS_CHILL_SPELL;
			else if( ( sp->EffectApplyAuraName[0] == SPELL_AURA_MOD_HASTE && sp->EffectBasePoints[0] < 0 )
				|| ( sp->EffectApplyAuraName[1] == SPELL_AURA_MOD_HASTE && sp->EffectBasePoints[1] < 0 ) 
				|| ( sp->EffectApplyAuraName[2] == SPELL_AURA_MOD_HASTE && sp->EffectBasePoints[2] < 0 )
				)
				sp->c_is_flags |= SPELL_FLAG_IS_CHILL_SPELL;
		}
		
		if( namehash == SPELL_HASH_DEEP_WOUND 
			|| namehash == SPELL_HASH_CHILLED )
			sp->c_is_flags |= SPELL_FLAG_IS_PROC_TRIGGER_PROC;

		//Rogue: Posion time fix for 2.3
		if( strstr( sp->Name, "Crippling Poison") && sp->Effect[0] == 54 ) //I, II
			sp->EffectBasePoints[0] = 3599;
		if( strstr( sp->Name, "Mind-numbing Poison") && sp->Effect[0] == 54 ) //I,II,III
			sp->EffectBasePoints[0] = 3599;
		if( strstr( sp->Name, "Instant Poison") && sp->Effect[0] == 54 ) //I,II,III,IV,V,VI,VII    
			sp->EffectBasePoints[0] = 3599;
		if( strstr( sp->Name, "Deadly Poison") && sp->Effect[0] == 54 ) //I,II,III,IV,V,VI,VII
			sp->EffectBasePoints[0] = 3599;
		if( strstr( sp->Name, "Wound Poison") && sp->Effect[0] == 54 ) //I,II,III,IV,V
			sp->EffectBasePoints[0] = 3599;
		if( strstr( sp->Name, "Anesthetic Poison") && sp->Effect[0] == 54 ) //I
			sp->EffectBasePoints[0] = 3599;

        if( strstr( sp->Name, "Sharpen Blade") && sp->Effect[0] == 54 ) //All BS stones
            sp->EffectBasePoints[0] = 3599;

		//these mostly do not mix so we can use else 
        // look for seal, etc in name
        if( strstr( sp->Name, "Blessing") && strstr( sp->Name, "mproved") == NULL )
		{
			//there should be levels for this, you may stak GBOM with BOK for example
           sp->BGR_one_buff_on_target |= SPELL_TYPE_BLESSING;
		}
        else if( strstr( sp->Name, "Curse"))
            sp->BGR_one_buff_on_target |= SPELL_TYPE_CURSE;
        else if( strstr( sp->Name, "Corruption"))
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_CORRUPTION;
		}
        else if( strstr( sp->Name, "Aspect") && (sp->Attributes & ATTRIBUTES_PASSIVE) == 0  )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_ASPECT;
			sp->BGR_one_buff_on_target_skip_caster_check = true;
		}
        else if( (strstr( sp->Name, "Sting") || strstr( sp->Name, "sting"))  && (sp->Attributes & ATTRIBUTES_PASSIVE) == 0 )
            sp->BGR_one_buff_on_target |= SPELL_TYPE_STING;
        // don't break armor items!
        else if((strstr( sp->Name, "Fel Armor") || strstr( sp->Name, "Frost Armor") || strstr( sp->Name, "Ice Armor") || strstr( sp->Name, "Mage Armor") || strstr( sp->Name, "Molten Armor") || strstr( sp->Name, "Demon Skin") || strstr( sp->Name, "Demon Armor"))  && (sp->Attributes & ATTRIBUTES_PASSIVE) == 0)
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_ARMOR;
			sp->BGR_one_buff_on_target_skip_caster_check = true;
		}
        else if( strstr( sp->Name, "Aura") 
			&& !strstr( sp->Name, "Trueshot") && !strstr( sp->Name, "Moonkin")
			&& !strstr( sp->Name, "Crusader") && !strstr( sp->Name, "Sanctity") && !strstr( sp->Name, "Devotion") && !strstr( sp->Name, "Retribution") && !strstr( sp->Name, "Concentration") && !strstr( sp->Name, "Shadow Resistance") && !strstr( sp->Name, "Frost Resistance") && !strstr( sp->Name, "Fire Resistance")
			)
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_AURA;
			sp->BGR_one_buff_on_target_skip_caster_check = true;
		}
		else if( strstr( sp->Name, "Track")==sp->Name)
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_TRACK;
			sp->BGR_one_buff_on_target_skip_caster_check = true;
		}
		else if( namehash == SPELL_HASH_GIFT_OF_THE_WILD || namehash == SPELL_HASH_MARK_OF_THE_WILD )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_MARK_GIFT;
			sp->BGR_one_buff_on_target_skip_caster_check = true;	//cause name is not the same and it would stack otherwise
		}
		else if( namehash == SPELL_HASH_IMMOLATION_TRAP || namehash == SPELL_HASH_FREEZING_TRAP || namehash == SPELL_HASH_FROST_TRAP || namehash == SPELL_HASH_EXPLOSIVE_TRAP || namehash == SPELL_HASH_SNAKE_TRAP )
            sp->BGR_one_buff_on_target |= SPELL_TYPE_HUNTER_TRAP;
		else if( namehash == SPELL_HASH_ARCANE_INTELLECT || namehash == SPELL_HASH_ARCANE_BRILLIANCE || namehash == SPELL_HASH_DALARAN_INTELLECT || namehash == SPELL_HASH_DALARAN_BRILLIANCE )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_MAGE_INTEL;
			sp->BGR_one_buff_on_target_skip_caster_check = true;	//cause name is not the same and it would stack otherwise
		}
		else if( namehash == SPELL_HASH_AMPLIFY_MAGIC || namehash == SPELL_HASH_DAMPEN_MAGIC )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_MAGE_MAGI;
			sp->BGR_one_buff_on_target_skip_caster_check = true;	//cause name is not the same and it would stack otherwise
		}
		else if( namehash == SPELL_HASH_FIRE_WARD || namehash == SPELL_HASH_FROST_WARD )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_MAGE_WARDS;
			sp->BGR_one_buff_on_target_skip_caster_check = true;	//cause name is not the same and it would stack otherwise
		}
		else if( namehash == SPELL_HASH_SHADOW_PROTECTION || namehash == SPELL_HASH_PRAYER_OF_SHADOW_PROTECTION )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_PRIEST_SH_PPROT;
			sp->BGR_one_buff_on_target_skip_caster_check = true;	//cause name is not the same and it would stack otherwise
		}
		else if( namehash == SPELL_HASH_WATER_SHIELD || namehash == SPELL_HASH_EARTH_SHIELD || namehash == SPELL_HASH_LIGHTNING_SHIELD )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SHIELD;
			sp->BGR_one_buff_on_target_skip_caster_check = true;
		}
		else if( namehash == SPELL_HASH_POWER_WORD__FORTITUDE || namehash == SPELL_HASH_PRAYER_OF_FORTITUDE )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_FORTITUDE;
			sp->BGR_one_buff_on_target_skip_caster_check = true;	//cause name is not the same and it would stack otherwise
		}
		else if( namehash == SPELL_HASH_DIVINE_SPIRIT || namehash == SPELL_HASH_PRAYER_OF_SPIRIT )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SPIRIT;
			sp->BGR_one_buff_on_target_skip_caster_check = true;
		}
		else if( namehash == SPELL_HASH_WINDFURY_WEAPON__PASSIVE_ || namehash == SPELL_HASH_WINDFURY_WEAPON )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_WINDFURRY;
			sp->BGR_one_buff_on_target_skip_caster_check = true;	//cause name is not the same and it would stack otherwise
		}
		else if( namehash == SPELL_HASH_FLAMETONGUE_WEAPON__PASSIVE_ || namehash == SPELL_HASH_FLAMETONGUE_WEAPON )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_FLAMETONGUE;
			sp->BGR_one_buff_on_target_skip_caster_check = true;	//cause name is not the same and it would stack otherwise
		}
//		else if( strstr( sp->Name, "Curse of Weakness") || strstr( sp->Name, "Curse of Agony") || strstr( sp->Name, "Curse of Recklessness") || strstr( sp->Name, "Curse of Tongues") || strstr( sp->Name, "Curse of the Elements") || strstr( sp->Name, "Curse of Idiocy") || strstr( sp->Name, "Curse of Shadow") || strstr( sp->Name, "Curse of Doom"))
//		else if(namehash==4129426293 || namehash==885131426 || namehash==626036062 || namehash==3551228837 || namehash==2784647472 || namehash==776142553 || namehash==3407058720 || namehash==202747424)
//		else if( strstr( sp->Name, "Curse of "))
//            type |= SPELL_TYPE_WARLOCK_CURSES;
//		else if( strstr( sp->Name, "Immolate") || strstr( sp->Name, "Conflagrate"))
//			sp->BGR_one_buff_on_target |= SPELL_TYPE_WARLOCK_IMMOLATE;
		else if( strstr( sp->Name, "Amplify Magic") || strstr( sp->Name, "Dampen Magic"))
		{
			sp->BGR_one_buff_on_target |= SPELL_TYPE_MAGE_AMPL_DUMP;
			sp->BGR_one_buff_on_target_skip_caster_check = true;
		}
        else if( strstr( sp->Description, "Battle Elixir"))
            sp->BGR_one_buff_on_target |= SPELL_TYPE_ELIXIR_BATTLE;
        else if( strstr( sp->Description, "Guardian Elixir"))
            sp->BGR_one_buff_on_target |= SPELL_TYPE_ELIXIR_GUARDIAN;
        else if( strstr( sp->Description, "Battle and Guardian elixir"))
            sp->BGR_one_buff_on_target |= SPELL_TYPE_ELIXIR_FLASK;
		else if( namehash == SPELL_HASH_HUNTER_S_MARK )		// hunter's mark
		{
			sp->BGR_one_buff_on_target |= SPELL_TYPE_HUNTER_MARK;
			sp->BGR_one_buff_on_target_skip_caster_check = true;
		}
        else if( namehash == SPELL_HASH_COMMANDING_SHOUT || namehash == SPELL_HASH_BATTLE_SHOUT )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_WARRIOR_SHOUT;
			sp->BGR_one_buff_on_target_skip_caster_check = true;
		}
		else if( strstr( sp->Description, "Finishing move")==sp->Description)
			sp->c_is_flags |= SPELL_FLAG_IS_FINISHING_MOVE;
        else if( strstr( sp->Name, "Presence") && strstr( sp->Description, "Only one") )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_PRESENCE;
			sp->BGR_one_buff_on_target_skip_caster_check = true;
		}
		else if( namehash == SPELL_HASH_FROST_SHOCK || namehash == SPELL_HASH_EARTH_SHOCK || namehash == SPELL_HASH_FLAME_SHOCK )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SHOCK;
			sp->BGR_one_buff_on_target_skip_caster_check = true;	//cause name is not the same and it would stack otherwise
		}

		if( IsDamagingSpell( sp ) )
			sp->c_is_flags |= SPELL_FLAG_IS_DAMAGING;
		if( IsHealingSpell( sp ) )
			sp->c_is_flags |= SPELL_FLAG_IS_HEALING;
		if( IsTargetingStealthed( sp ) )
			sp->c_is_flags |= SPELL_FLAG_IS_TARGETINGSTEALTHED;
		if( sp->EffectApplyAuraName[ 0 ] == SPELL_AURA_PERIODIC_HEAL || sp->EffectApplyAuraName[ 1 ] == SPELL_AURA_PERIODIC_HEAL || sp->EffectApplyAuraName[ 2 ] == SPELL_AURA_PERIODIC_HEAL )
			sp->c_is_flags |= SPELL_FLAG_IS_HEAL_OVER_TIME;
		

		if( sp->MechanicsType == MECHANIC_INVULNERABLE && sp->Id != 25771) // Cast spell Forbearance
			sp->chained_cast = dbcSpell.LookupEntryForced(25771);
		else if( sp->MechanicsType == MECHANIC_HEALING && sp->Id != 11196) // Cast spell Recently Bandaged
			sp->chained_cast = dbcSpell.LookupEntryForced(11196);
		else if( sp->MechanicsType == MECHANIC_SHIELDED && sp->Id != 6788) // Cast spell Weakened Soul
			sp->chained_cast = dbcSpell.LookupEntryForced(6788);
		else if( sp->Id == 45438) // Cast spell Hypothermia for Ice Block
			sp->chained_cast = dbcSpell.LookupEntryForced(41425);

		//mixology targets
		if(  ( sp->Effect[0] == SPELL_EFFECT_APPLY_AURA || sp->Effect[0] == SPELL_EFFECT_NULL ) 
					 && ( sp->Effect[1] == SPELL_EFFECT_APPLY_AURA || sp->Effect[1] == SPELL_EFFECT_NULL ) 
					 && ( sp->Effect[2] == SPELL_EFFECT_APPLY_AURA || sp->Effect[2] == SPELL_EFFECT_NULL ) 
					 && ( strstr(sp->Name, "flask") || strstr(sp->Name, "elixir") || strstr(sp->Name, "Flask") || strstr(sp->Name, "Elixir") 
						|| strstr(sp->Description, "flask") || strstr(sp->Description, "elixir") || strstr(sp->Description, "Flask") || strstr(sp->Description, "Elixir") )
					 )
			sp->c_is_flags |= SPELL_FLAG_IS_FLASK_OR_ELIXIR | SPELL_FLAG_IS_REQ_ITEM_CASTER_MOD_CHK;
		//alchemist stone targets
		if(  
				//( sp->c_is_flags & (SPELL_FLAG_IS_HEALING | SPELL_FLAG_IS_HEAL_OVER_TIME) ) ||
				sp->Effect[0] == SPELL_EFFECT_ENERGIZE || sp->Effect[0] == SPELL_EFFECT_ENERGIZE_MAXPOWER_PCT
				|| sp->Effect[1] == SPELL_EFFECT_ENERGIZE || sp->Effect[1] == SPELL_EFFECT_ENERGIZE_MAXPOWER_PCT
				|| sp->Effect[2] == SPELL_EFFECT_ENERGIZE || sp->Effect[2] == SPELL_EFFECT_ENERGIZE_MAXPOWER_PCT
				|| sp->Effect[0] == SPELL_EFFECT_HEAL || sp->Effect[0] == SPELL_EFFECT_HEAL_MAX_HEALTH || sp->Effect[0] == SPELL_EFFECT_HEAL_MAXHEALTH_PCT
				|| sp->Effect[1] == SPELL_EFFECT_HEAL || sp->Effect[1] == SPELL_EFFECT_HEAL_MAX_HEALTH || sp->Effect[1] == SPELL_EFFECT_HEAL_MAXHEALTH_PCT
				|| sp->Effect[2] == SPELL_EFFECT_HEAL || sp->Effect[2] == SPELL_EFFECT_HEAL_MAX_HEALTH || sp->Effect[2] == SPELL_EFFECT_HEAL_MAXHEALTH_PCT
/*				|| sp->EffectApplyAuraName[0] == SPELL_AURA_MOD_TOTAL_MANA_REGEN_PCT || sp->EffectApplyAuraName[0] == SPELL_AURA_REGEN_MANA_STAT_PCT || sp->EffectApplyAuraName[0] == SPELL_AURA_MOD_TOTAL_HEALTH_REGEN_PCT || sp->EffectApplyAuraName[0] == SPELL_AURA_MOD_TOTAL_MANA_REGEN_PCT 
				|| sp->EffectApplyAuraName[1] == SPELL_AURA_MOD_TOTAL_MANA_REGEN_PCT || sp->EffectApplyAuraName[1] == SPELL_AURA_REGEN_MANA_STAT_PCT || sp->EffectApplyAuraName[1] == SPELL_AURA_MOD_TOTAL_HEALTH_REGEN_PCT || sp->EffectApplyAuraName[1] == SPELL_AURA_MOD_TOTAL_MANA_REGEN_PCT 
				|| sp->EffectApplyAuraName[2] == SPELL_AURA_MOD_TOTAL_MANA_REGEN_PCT || sp->EffectApplyAuraName[2] == SPELL_AURA_REGEN_MANA_STAT_PCT || sp->EffectApplyAuraName[2] == SPELL_AURA_MOD_TOTAL_HEALTH_REGEN_PCT || sp->EffectApplyAuraName[2] == SPELL_AURA_MOD_TOTAL_MANA_REGEN_PCT 
				|| sp->EffectApplyAuraName[0] == SPELL_AURA_MOD_POWER_REGEN || sp->EffectApplyAuraName[0] == SPELL_AURA_MOD_REGEN || sp->EffectApplyAuraName[0] == SPELL_AURA_DRINK_NEW || sp->EffectApplyAuraName[0] == SPELL_AURA_MOD_PERCENT_REGEN || sp->EffectApplyAuraName[0] == SPELL_AURA_MOD_POWER_REGEN_PERCENT || sp->EffectApplyAuraName[0] == SPELL_AURA_REGEN_MANA_STAT_PCT 
				|| sp->EffectApplyAuraName[1] == SPELL_AURA_MOD_POWER_REGEN || sp->EffectApplyAuraName[1] == SPELL_AURA_MOD_REGEN || sp->EffectApplyAuraName[1] == SPELL_AURA_DRINK_NEW || sp->EffectApplyAuraName[1] == SPELL_AURA_MOD_PERCENT_REGEN || sp->EffectApplyAuraName[1] == SPELL_AURA_MOD_POWER_REGEN_PERCENT || sp->EffectApplyAuraName[1] == SPELL_AURA_REGEN_MANA_STAT_PCT 
				|| sp->EffectApplyAuraName[2] == SPELL_AURA_MOD_POWER_REGEN || sp->EffectApplyAuraName[2] == SPELL_AURA_MOD_REGEN || sp->EffectApplyAuraName[2] == SPELL_AURA_DRINK_NEW || sp->EffectApplyAuraName[2] == SPELL_AURA_MOD_PERCENT_REGEN || sp->EffectApplyAuraName[2] == SPELL_AURA_MOD_POWER_REGEN_PERCENT || sp->EffectApplyAuraName[2] == SPELL_AURA_REGEN_MANA_STAT_PCT */
					 )
			sp->c_is_flags |= SPELL_FLAG_IS_ALCHEMIST_STONE_TARGET | SPELL_FLAG_IS_REQ_ITEM_CASTER_MOD_CHK;

		sp->ThreatForSpellCoef = 1.0f;
		//all negative buffs do treat unless specified othervise
		int32 tsp = sp->EffectBasePoints[0]+sp->EffectBasePoints[1]+sp->EffectBasePoints[2]+3+10; //make sure we have some base threath
		if( tsp <= 0 )
			sp->ThreatForSpell = 15;
		else
			sp->ThreatForSpell = tsp;
        if( strstr( sp->Description, " threat") )
		{
			if( strstr( sp->Description, " high amount") || strstr( sp->Description, " large amount") )
			{
				sp->ThreatForSpellCoef = 4; //boost threath output -> 1 threath hit = 4 heals ?
			}
			//this will influence other spells actually
			else if( strstr( sp->Description, "reduc") || strstr( sp->Description, " low") )
			{
				sp->ThreatForSpell = 10; //make sure we have some base threath
				sp->ThreatForSpellCoef = 0.25; 
			}
			else if( strstr( sp->Description, " no threat") )
			{
				sp->ThreatForSpell = 0; //make sure we have some no base threath
				sp->ThreatForSpellCoef = 0.0f; 
			}
			//this will influence other spells actually
			else if( strstr( sp->Description, " increases") )
			{
				sp->ThreatForSpellCoef = 2; //boost threath output -> 1 threath hit = 4 heals ?
			}
			else if( strstr( sp->Description, " moderate") || strstr( sp->Description, " additional") || strstr( sp->Description, " generat") 
				 || strstr( sp->Description, " additonal") //lol at blizz typo
				)
			{
				sp->ThreatForSpellCoef = 2; //boost threath output -> 1 threath hit = 4 heals ?
			}
		}

		//stupid spell ranking problem
		if( sp->spellLevel==0)
		{
			uint32 new_level=0;
			if( strstr( sp->Name, "Apprentice "))
				new_level = 1;
			else if( strstr( sp->Name, "Journeyman "))
				new_level = 2;
			else if( strstr( sp->Name, "Expert "))
				new_level = 3;
			else if( strstr( sp->Name, "Artisan "))
				new_level = 4;
			else if( strstr( sp->Name, "Master "))
				new_level = 5;
			if(new_level!=0)
			{
				uint32 teachspell=0;
				if(sp->Effect[0]==SPELL_EFFECT_LEARN_SPELL)
					teachspell = sp->EffectTriggerSpell[0];
				else if(sp->Effect[1]==SPELL_EFFECT_LEARN_SPELL)
					teachspell = sp->EffectTriggerSpell[1];
				else if(sp->Effect[2]==SPELL_EFFECT_LEARN_SPELL)
					teachspell = sp->EffectTriggerSpell[2];
				if(teachspell)
				{
					SpellEntry *spellInfo;
					spellInfo = dbcSpell.LookupEntryForced(teachspell);
					spellInfo->spellLevel = new_level;
					sp->spellLevel = new_level;
				}
			}
		}

		/*FILE * f = fopen("C:\\spells.txt", "a");
		fprintf(f, "case 0x%08X:		// %s\n", namehash, sp->Name);
		fclose(f);*/

		// find diminishing status
		sp->DiminishStatus = GetDiminishingGroup(namehash);

		//another grouping rule

		//Quivers, Ammo Pouches and Thori'dal the Star's Fury
		if( ( namehash == SPELL_HASH_HASTE && sp->Attributes & 0x10000 ) || sp->Id == 44972 )
		{
			sp->Attributes &= ~ATTRIBUTES_PASSIVE;//Otherwise we couldn't remove them
			sp->BGR_one_buff_on_target |= SPELL_TYPE_QUIVER_HASTE;
		}
		
		switch(namehash)
		{
//		case SPELL_HASH_SANCTITY_AURA:		
		case SPELL_HASH_DEVOTION_AURA:		
		case SPELL_HASH_RETRIBUTION_AURA:		
		case SPELL_HASH_CONCENTRATION_AURA:		
		case SPELL_HASH_SHADOW_RESISTANCE_AURA:		
		case SPELL_HASH_FIRE_RESISTANCE_AURA:		
		case SPELL_HASH_FROST_RESISTANCE_AURA:		
		case SPELL_HASH_CRUSADER_AURA:		
			sp->BGR_one_buff_from_caster_on_self = SPELL_TYPE2_PALADIN_AURA;
			break;
		case SPELL_HASH_HUNTER_S_MARK:		// Hunter's mark
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_MARK;
			break;
		case SPELL_HASH_POLYMORPH:			// Polymorph
		case SPELL_HASH_POLYMORPH__CHICKEN:	// Polymorph: Chicken
//		case SPELL_HASH_POLYMORPH__PIG:		// Polymorph: Pig
		case SPELL_HASH_POLYMORPH__SHEEP:	// Polymorph: Sheep
		case SPELL_HASH_POLYMORPH__SPIDER:	// Polymorph: Sheep
//		case SPELL_HASH_POLYMORPH__TURTLE:	// Polymorph: Turtle
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_POLYMORPH;
			break;

		case SPELL_HASH_FEAR:				// Fear
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_FEAR;
			break;

		case SPELL_HASH_SAP:				// Sap
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_SAP;
			break;

		case SPELL_HASH_SCARE_BEAST:		// Scare Beast
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_SCARE_BEAST;
			break;

		case SPELL_HASH_HIBERNATE:			// Hibernate
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_HIBERNATE;
			break;

		case SPELL_HASH_EARTH_SHIELD:		// Earth Shield
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_EARTH_SHIELD;
			break;

		case SPELL_HASH_CYCLONE:			// Cyclone
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_CYCLONE;
			break;

		case SPELL_HASH_BANISH:				// Banish
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_BANISH;
			break;

		case SPELL_HASH_JUDGEMENT_OF_LIGHT:
		case SPELL_HASH_JUDGEMENT_OF_WISDOM:
		case SPELL_HASH_JUDGEMENT_OF_JUSTICE:
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_JUDGEMENT;
			break;

			//pet spell cooldowns are messed up most of the time :(
		case SPELL_HASH_BITE:
		case SPELL_HASH_CLAW:
		case SPELL_HASH_SMACK:
			if( sp->CategoryRecoveryTime == 0 )
				sp->CategoryRecoveryTime = 2000; //2 sec
			break;
		case SPELL_HASH_GROW:
		case SPELL_HASH_STING:
		case SPELL_HASH_SWIPE:
			if( sp->CategoryRecoveryTime == 0 )
				sp->CategoryRecoveryTime = 5000; //5 sec
			break;
		case SPELL_HASH_FROSTSTORM_BREATH:
		case SPELL_HASH_POISON_SPIT:
		case SPELL_HASH_FIRE_BREATH:
		case SPELL_HASH_LAVA_BREATH:
		case SPELL_HASH_LIGHTNING_BREATH:
		case SPELL_HASH_SPORE_CLOUD:
		case SPELL_HASH_DEMORALIZING_SCREECH:
		case SPELL_HASH_PROWL:
		case SPELL_HASH_ACID_SPIT:
		case SPELL_HASH_RAKE:
		case SPELL_HASH_GORE:
		case SPELL_HASH_SCORPID_POISON:
		case SPELL_HASH_MONSTROUS_BITE:
		case SPELL_HASH_SPIRIT_STRIKE:
		case SPELL_HASH_WARP:
			if( sp->CategoryRecoveryTime == 0 )
				sp->CategoryRecoveryTime = 10000; //10 sec
			break;
		case SPELL_HASH_TENDON_RIP:
			if( sp->CategoryRecoveryTime == 0 )
				sp->CategoryRecoveryTime = 20000; //20 sec
			break;
		case SPELL_HASH_PUMMEL:
			if( sp->CategoryRecoveryTime == 0 )
				sp->CategoryRecoveryTime = 30000; //30 sec
			break;
		case SPELL_HASH_NETHER_SHOCK:
		case SPELL_HASH_RAVAGE:
		case SPELL_HASH_PIN:
		case SPELL_HASH_VENOM_WEB_SPRAY:
		case SPELL_HASH_DUST_CLOUD:
		case SPELL_HASH_FURIOUS_HOWL:
			if( sp->CategoryRecoveryTime == 0 )
				sp->CategoryRecoveryTime = 40000; //40 sec
			break;
		case SPELL_HASH_SONIC_BLAST:
		case SPELL_HASH_SNATCH:
		case SPELL_HASH_STAMPEDE:
		case SPELL_HASH_SERENITY_DUST:
		case SPELL_HASH_SAVAGE_REND:
		case SPELL_HASH_SHELL_SHIELD:
			if( sp->CategoryRecoveryTime == 0 )
				sp->CategoryRecoveryTime = 60000; //60 sec
			break;
		case SPELL_HASH_BAD_ATTITUDE:
			if( sp->CategoryRecoveryTime == 0 )
				sp->CategoryRecoveryTime = 120000; //120 sec
			break;
		}

		switch(namehash)
		{
			case SPELL_HASH_STEADY_SHOT:		sp->EffectHandler = &HandleSteadyShot; break;
			case SPELL_HASH_DEADLY_POISON:		sp->EffectHandler = &HandleDeadlyPoison; break;
			case SPELL_HASH_INSTANT_POISON:		sp->EffectHandler = &HandleInstantPoison; break;
			case SPELL_HASH_WOUND_POISON:		sp->EffectHandler = &HandleWoundPoison; break;
			case SPELL_HASH_ARCANE_SHOT:		sp->EffectHandler = &HandleArcaneShot; break;
			case SPELL_HASH_SERPENT_STING:		sp->EffectHandler = &HandleSerpentSting; break;
			case SPELL_HASH_KILL_SHOT:			sp->EffectHandler = &HandleKillShot; break;
			case SPELL_HASH_EVISCERATE:			sp->EffectHandler = &HandleEviscerate; break;
			case SPELL_HASH_DIVINE_SPIRIT:		sp->EffectHandler = &HandleDivineSpiritPrayerOfSpirit; break;
			case SPELL_HASH_PRAYER_OF_SPIRIT:	sp->EffectHandler = &HandleDivineSpiritPrayerOfSpirit; break;
			case SPELL_HASH_SEAL_OF_LIGHT:		sp->EffectHandler = &HandleSealOfLight; break;
			case SPELL_HASH_FLASH_OF_LIGHT:		sp->EffectHandler = &HandleFlashOfLight; break;
			case SPELL_HASH_DIVINE_STORM:		sp->EffectHandler = &HandleFlashOfLight; break;
			case SPELL_HASH_HYSTERIA:			sp->EffectHandler = &HandleHysteria; break;
			case SPELL_HASH_REND:				sp->EffectHandler = &HandleRend; break;
			case SPELL_HASH_FEROCIOUS_BITE:		sp->EffectHandler = &HandleFerociousBite; break;
			case SPELL_HASH_FAERIE_FIRE__FERAL_:				sp->EffectHandler = &HandleFaerieFire; break;
			case SPELL_HASH_INFINITE_REPLENISHMENT___WISDOM:	sp->EffectHandler = &HandleReplenishment1; break;
			case SPELL_HASH_VICTORY_RUSH:		sp->EffectHandler = &HandleVictoryRush; break;
			case SPELL_HASH_OWLKIN_FRENZY:		sp->EffectHandler = &HandleOwlkinFrenzy; break;
			case SPELL_HASH_INNERVATE:			sp->EffectHandler = &HandleInnervate; break;
			case SPELL_HASH_GARROTE:			sp->EffectHandler = &HandleGarotte; break;
			case SPELL_HASH_RUPTURE:			sp->EffectHandler = &HandleRupture; break;
			case SPELL_HASH_RIP:				sp->EffectHandler = &HandleRip; break;
			case SPELL_HASH_EXPLOSIVE_SHOT:		sp->EffectHandler = &HandleExplosiveShot; break;
			case SPELL_HASH_BLACK_ARROW:		sp->EffectHandler = &HandleBlackArrow; break;
			case SPELL_HASH_REVENGE:			sp->EffectHandler = &HandleRevenge; break;
			case SPELL_HASH_MONGOOSE_BITE:		sp->EffectHandler = &HandleMangooseBite; break;
			case SPELL_HASH_SWIPE__BEAR_:		sp->EffectHandler = &HandleSwipeBear; break;
			case SPELL_HASH_HAMMER_OF_THE_RIGHTEOUS:			sp->EffectHandler = &HandleHammerOfRightous; break;
			case SPELL_HASH_SHIELD_OF_RIGHTEOUSNESS:			sp->EffectHandler = &HandleShieldOfRightous; break;
			case SPELL_HASH_EXORCISM:			sp->EffectHandler = &HandleExorcism; break;
			case SPELL_HASH_SHATTERING_THROW:	sp->EffectHandler = &HandleShatteringThrow; break;
			case SPELL_HASH_GOUGE:				sp->EffectHandler = &HandleGauge; break;
			case SPELL_HASH_DEATH_STRIKE:		sp->EffectHandler = &HandleDeathStrike; break;
			case SPELL_HASH_BLOOD_BOIL:			sp->EffectHandler = &HandleBloodBoil; break;
			case SPELL_HASH_BLOOD_STRIKE:		sp->EffectHandler = &HandleBloodStrikeObliterate; break;
			case SPELL_HASH_OBLITERATE:			sp->EffectHandler = &HandleBloodStrikeObliterate; break;
			case SPELL_HASH_HEART_STRIKE:		sp->EffectHandler = &HandleHearthStrike; break;
			case SPELL_HASH_SCOURGE_STRIKE:		sp->EffectHandler = &HandleScourgeStrike; break;
			case SPELL_HASH_BLOOD_CAKED_STRIKE:	sp->EffectHandler = &HandleBloodCakedStrike; break;
			case SPELL_HASH_ANTI_MAGIC_SHELL:	sp->EffectHandler = &HandleAntiMagicShell; break;
			case SPELL_HASH_PLAGUE_STRIKE:		sp->EffectHandler = &HandlePlagueStrike; break;
			case SPELL_HASH_RUNE_STRIKE:		sp->EffectHandler = &HandleRuneStrike; break;
			case SPELL_HASH_ICE_LANCE:			sp->EffectHandler = &HandleIceLance; break;
			case SPELL_HASH_CHAOS_BANE:			sp->EffectHandler = &HandleChaosBane; break;
			case SPELL_HASH_TYMPANIC_TANTRUM:	sp->EffectHandler = &HandleTympanicTantum; break;
			case SPELL_HASH_CONFLAGRATE:		sp->EffectHandler = &HandleConflagrate; break;
			case SPELL_HASH_HAND_OF_RECKONING:	sp->EffectHandler = &HandleHandOfReckoning; break;
			case SPELL_HASH_AVENGER_S_SHIELD:	sp->EffectHandler = &HandleAvangersShield; break;
			case SPELL_HASH_VAMPIRIC_EMBRACE:	sp->EffectHandler = &HandleVampiricEmbrace; break;
			case SPELL_HASH_ENVENOM:			sp->EffectHandler = &HandleEnvenom; break;
			case SPELL_HASH_CONSECRATION:		sp->EffectHandler = &HandleConsecration; break;
//			case SPELL_HASH_MUTILATE:			sp->EffectHandler = &HandleMutilate; break;
			default:break;
		}
		switch(sp->Id)
		{
			case 57669:			sp->EffectHandler = &HandleReplenishment2; break;
			case 20572:			sp->EffectHandler = &HandleBloodFury; break;
			case 31804:			sp->EffectHandler = &HandleJudgeSealOfVengeanceSealOfCorruption; break;
			case 53733:			sp->EffectHandler = &HandleJudgeSealOfVengeanceSealOfCorruption; break;
			case 25742:			sp->EffectHandler = &HandleSealOfRightous; break;
			case 53742:			sp->EffectHandler = &HandleHolyVengeanceBloodCorruption; break;
			case 31803:			sp->EffectHandler = &HandleHolyVengeanceBloodCorruption; break;
			default:break;
		}
		// HACK FIX: Break roots/fear on damage.. this needs to be fixed properly!
		if(!(sp->AuraInterruptFlags & AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN))
		{
			for(uint32 z = 0; z < 3; ++z) 
			{
				if(sp->EffectApplyAuraName[z] == SPELL_AURA_MOD_FEAR ||
					sp->EffectApplyAuraName[z] == SPELL_AURA_MOD_ROOT)
				{
					sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;
					break;
				}

				if( ( sp->Effect[z] == SPELL_EFFECT_SCHOOL_DAMAGE && sp->Spell_Dmg_Type == SPELL_DMG_TYPE_MELEE ) || sp->Effect[z] == SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL || sp->Effect[z] == SPELL_EFFECT_WEAPON_DAMAGE || sp->Effect[z] == SPELL_EFFECT_WEAPON_PERCENT_DAMAGE || sp->Effect[z] == SPELL_EFFECT_DUMMYMELEE )
					sp->is_melee_spell = true;
				//omg dodge fireballs !
				if( ( sp->Effect[z] == SPELL_EFFECT_SCHOOL_DAMAGE && sp->Spell_Dmg_Type == SPELL_DMG_TYPE_RANGED ) )
				{
					//Log.Notice( "SpellFixes" , "Ranged Spell: %u [%s]" , sp->Id , sp->Name );
					sp->is_ranged_spell = true;
				}
			}
		}


		if( sp->School 
			&& sp->EffectApplyAuraName[0] != SPELL_AURA_MOD_POSSESS
			&& sp->EffectApplyAuraName[1] != SPELL_AURA_MOD_POSSESS
			&& sp->EffectApplyAuraName[2] != SPELL_AURA_MOD_POSSESS
			&& sp->is_melee_spell == false
			)
			sp->c_is_flags |= SPELL_FLAG_IS_ALLOW_MAGNET_TARGET;

		// set extra properties
		sp->RankNumber = rank;

		uint32 pr=sp->procFlags;
		for(uint32 y=0;y < 3; y++)
		{
			// get the effect number from the spell
			effect = sp->Effect[y];
			if(effect==SPELL_EFFECT_APPLY_AURA)
			{
				uint32 aura = sp->EffectApplyAuraName[y];
				if( aura == SPELL_AURA_PROC_TRIGGER_SPELL ||
					aura == SPELL_AURA_PROC_TRIGGER_DAMAGE
					)//search for spellid in description
				{
					pr=0;

					uint32 len = (uint32)strlen(sp->Description);
					for(i = 0; i < len; ++i)
						sp->Description[i] = tolower(sp->Description[i]);
					//dirty code for procs, if any1 got any better idea-> u are welcome
					//139944 --- some magic number, it will trigger on all hits etc
						//for seems to be smth like custom check
					if( strstr( sp->Description,"your ranged criticals"))
						pr|=PROC_ON_RANGED_CRIT_ATTACK;
					if( strstr( sp->Description,"chance on hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"takes damage"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( sp->Description,"attackers when hit"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"character strikes an enemy"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"strike you with a melee attack"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"target casts a spell"))
						pr|=PROC_ON_CAST_SPELL;
                    if( strstr( sp->Description,"your harmful spells land"))
                        pr|=PROC_ON_CAST_SPELL;
                    if( strstr( sp->Description,"on spell critical hit"))
                        pr|=PROC_ON_SPELL_CRIT_HIT;
                    if( strstr( sp->Description,"spell critical strikes"))
                        pr|=PROC_ON_SPELL_CRIT_HIT;
                    if( strstr( sp->Description,"being able to resurrect"))
                        pr|=PROC_ON_DIE;
					if( strstr( sp->Description,"any damage caused"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( sp->Description,"the next melee attack against the caster"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"when successfully hit"))
						pr|=PROC_ON_MELEE_ATTACK ;
					if( strstr( sp->Description,"an enemy on hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"when it hits"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"when successfully hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"on a successful hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"damage to attacker on hit"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"on a hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"strikes you with a melee attack"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"when caster takes damage"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( sp->Description,"when the caster is using melee attacks"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"when struck in combat") || strstr(sp->Description,"When struck in combat"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"successful melee attack"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"chance per attack"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"chance per hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"that strikes a party member"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"when hit by a melee attack"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"landing a melee critical strike"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( sp->Description,"your critical strikes"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( sp->Description,"whenever you deal ranged damage"))
						pr|=PROC_ON_RANGED_ATTACK;
//					if( strstr( sp->Description,"whenever you deal melee damage"))
					if( strstr( sp->Description,"you deal melee damage"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"your melee attacks"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"damage with your Sword"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"when struck in melee combat"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"any successful spell cast against the priest"))
						pr|=PROC_ON_SPELL_HIT_VICTIM;
					if( strstr( sp->Description,"the next melee attack on the caster"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"striking melee or ranged attackers"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM|PROC_ON_RANGED_ATTACK_VICTIM;
					if( strstr( sp->Description,"when damaging an enemy in melee"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"victim of a critical strike"))
						pr|=PROC_ON_CRIT_HIT_VICTIM;
					if( strstr( sp->Description,"on successful melee or ranged attack"))
						pr|=PROC_ON_MELEE_ATTACK|PROC_ON_RANGED_ATTACK;
					if( strstr( sp->Description,"enemy that strikes you in melee"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"after getting a critical strike"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( sp->Description,"whenever damage is dealt to you"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( sp->Description,"when ranged or melee damage is dealt"))
						pr|=PROC_ON_MELEE_ATTACK|PROC_ON_RANGED_ATTACK;
					if( strstr( sp->Description,"damaging melee attacks"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"on melee or ranged attack"))
						pr|=PROC_ON_MELEE_ATTACK|PROC_ON_RANGED_ATTACK;
					if( strstr( sp->Description,"on a melee swing"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"Chance on melee"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"spell criticals against you"))
						pr|=PROC_ON_SPELL_CRIT_HIT_VICTIM;
					if( strstr( sp->Description,"after being struck by a melee or ranged critical hit"))
						pr|=PROC_ON_CRIT_HIT_VICTIM;
//					if( strstr( sp->Description,"on a critical hit"))
					if( strstr( sp->Description,"critical hit"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( sp->Description,"strikes the caster"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"a spell, melee or ranged attack hits the caster"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( sp->Description,"after dealing a critical strike"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( sp->Description,"each melee or ranged damage hit against the priest"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM|PROC_ON_RANGED_ATTACK_VICTIM;				
					if( strstr( sp->Description, "a chance to deal additional"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description, "chance to get an extra attack"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description, "melee attacks has"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description, "any damage spell hits a target"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( sp->Description, "giving each melee attack a chance"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description, "damage when hit"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM; //myabe melee damage ?
					if( strstr( sp->Description, "gives your"))
					{
						if( strstr( sp->Description, "melee"))
							pr|=PROC_ON_MELEE_ATTACK;
						else if( strstr( sp->Description,"sinister strike, backstab, gouge and shiv"))
							pr|=PROC_ON_CAST_SPELL;
						else if( strstr( sp->Description,"chance to daze the target"))
							pr|=PROC_ON_CAST_SPELL;
						else if( strstr( sp->Description,"finishing moves"))
							pr|=PROC_ON_CAST_SPELL;
						//we should find that specific spell (or group) on what we will trigger
						else pr|=PROC_ON_CAST_SPELL;
					}
					if( strstr( sp->Description, "chance to add an additional combo") && strstr(sp->Description, "critical") )
						pr|=PROC_ON_CRIT_ATTACK;
					else if( strstr( sp->Description, "chance to add an additional combo"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( sp->Description, "victim of a melee or ranged critical strike"))
						pr|=PROC_ON_CRIT_HIT_VICTIM;
					if( strstr( sp->Description, "getting a critical effect from"))
						pr|=PROC_ON_SPELL_CRIT_HIT_VICTIM;
					if( strstr( sp->Description, "damaging attack is taken"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( sp->Description, "struck by a Stun or Immobilize"))
						pr|=PROC_ON_SPELL_HIT_VICTIM;
					if( strstr( sp->Description, "melee critical strike"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( sp->Name, "Bloodthirst"))
					{
						pr|=PROC_ON_MELEE_ATTACK;
						sp->procFlags2 |= PROC2_TARGET_SELF;
					}
					if( strstr( sp->Description, "experience or honor"))
						pr|=PROC_ON_GAIN_EXPIERIENCE;
					if( strstr( sp->Description,"your next offensive ability"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( sp->Description,"hit by a melee or ranged attack"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
					if( strstr( sp->Description,"enemy strikes the caster"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"melee and ranged attacks against you"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
					if( strstr( sp->Description,"when a block occurs"))
						pr|=PROC_ON_BLOCK_VICTIM;
					if( strstr( sp->Description,"dealing a critical strike from a weapon swing, spell, or ability"))
						pr|=PROC_ON_CRIT_ATTACK|PROC_ON_SPELL_CRIT_HIT;
					if( strstr( sp->Description,"dealing a critical strike from a weapon swing, spell, or ability"))
						pr|=PROC_ON_CRIT_ATTACK|PROC_ON_SPELL_CRIT_HIT;
					if( strstr( sp->Description,"shadow bolt critical strikes increase shadow damage"))
						pr|=PROC_ON_SPELL_CRIT_HIT;
					if( strstr( sp->Description,"next offensive ability"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( sp->Description,"after being hit with a shadow or fire spell"))
						pr|=PROC_ON_SPELL_LAND_VICTIM;
					if( strstr( sp->Description,"giving each melee attack"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"each strike has"))
						pr|=PROC_ON_MELEE_ATTACK;		
					if( strstr( sp->Description,"your Fire damage spell hits"))
						pr|=PROC_ON_CAST_SPELL;		//this happens only on hit ;)
					if( strstr( sp->Description,"corruption, curse of agony, siphon life and seed of corruption spells also cause"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( sp->Description,"pain, mind flay and vampiric touch spells also cause"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( sp->Description,"shadow damage spells have"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( sp->Description,"on successful spellcast"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( sp->Description,"your spell criticals have"))
						pr|=PROC_ON_SPELL_CRIT_HIT | PROC_ON_SPELL_CRIT_HIT_VICTIM;
					if( strstr( sp->Description,"after dodging their attack"))
					{
						pr|=PROC_ON_DODGE_VICTIM;
						if( strstr( sp->Description,"add a combo point"))
							sp->procFlags2 |= PROC2_TARGET_SELF;
					}
					if( strstr( sp->Description,"fully resisting"))
						pr|=PROC_ON_RESIST_VICTIM;
					if( strstr( sp->Description,"Your Shadow Word: Pain, Mind Flay and Vampiric Touch spells also cause the target"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( sp->Description,"chance on spell hit"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( sp->Description,"your melee and ranged attacks"))
						pr|=PROC_ON_MELEE_ATTACK|PROC_ON_RANGED_ATTACK;
//					if( strstr( sp->Description,"chill effect to your Blizzard"))
//						pr|=PROC_ON_CAST_SPELL;	
					//////////////////////////////////////////////////
					//proc dmg flags
					//////////////////////////////////////////////////
					if( strstr( sp->Description,"each attack blocked"))
						pr|=PROC_ON_BLOCK_VICTIM;
					if( strstr( sp->Description,"into flame, causing an additional"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"victim of a critical melee strike"))
						pr|=PROC_ON_CRIT_HIT_VICTIM;
					if( strstr( sp->Description,"damage to melee attackers"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"target blocks a melee attack"))
						pr|=PROC_ON_BLOCK_VICTIM;
					if( strstr( sp->Description,"ranged and melee attacks to deal"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
					if( strstr( sp->Description,"damage on hit"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( sp->Description,"chance on hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( sp->Description,"after being hit by any damaging attack"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( sp->Description,"striking melee or ranged attackers"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
					if( strstr( sp->Description,"damage to attackers when hit"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"striking melee attackers"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( sp->Description,"whenever the caster takes damage"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( sp->Description,"damage on every attack"))
						pr|=PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
					if( strstr( sp->Description,"chance to reflect Fire spells"))
						pr|=PROC_ON_SPELL_HIT_VICTIM;
					if( strstr( sp->Description,"hunter takes on the aspects of a hawk"))
					{
						pr|= PROC_ON_RANGED_ATTACK;
						sp->procFlags2 |= PROC2_TARGET_SELF;
					}
//					if( strstr( sp->Description,"successful auto shot attacks"))
//						pr|=PROC_ON_AUTO_SHOT_HIT;
					if( strstr( sp->Description,"after getting a critical effect from your"))
						pr=PROC_ON_SPELL_CRIT_HIT;
//					if( strstr( sp->Description,"Your critical strikes from Fire damage"))
//						pr|=PROC_ON_SPELL_CRIT_HIT;
				}//end "if procspellaura"
				//dirty fix to remove auras that should expire on event and they are not
//				else if( sp->procCharges>0)
//				{
					//there are at least 185 spells that should loose charge uppon some event.Be prepared to add more here !
					// ! watch it cause this might conflict with our custom modified spells like : lighning shield !

					//spells like : Presence of Mind,Nature's Swiftness, Inner Focus,Amplify Curse,Coup de Grace
					//SELECT * FROM dbc_spell where proc_charges!=0 and (effect_aura_1=108 or effect_aura_2=108 and effect_aura_3=108) and description!=""
//					if(aura == SPELL_AURA_ADD_PCT_MODIFIER)
//						sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_CAST_SPELL;
					//most of them probably already have these flags...not sure if we should add to all of them without checking
/*					if( strstr( sp->Description, "melee"))
						sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_START_ATTACK;
					if( strstr( sp->Description, "ranged"))
						sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_START_ATTACK;*/
//				}
			}//end "if aura"
		}//end "for each effect"
		sp->procFlags = pr;

		//Spells Not affected by Bonus Healing
		if(sp->NameHash == SPELL_HASH_LESSER_HEROISM) //Lesser Heroism
			sp->fixed_dddhcoef = 0.0f;
		else if(sp->NameHash == SPELL_HASH_HEROISM) //Heroism, a.k.a. Darkmoon Card: Heroism
			sp->fixed_dddhcoef = 0.0f;
		else if(sp->NameHash == SPELL_HASH_CITRINE_PENDANT_OF_GOLDEN_HEALING) //Citrine Pendant of Golden Healing
			sp->fixed_dddhcoef = 0.0f;
		else if(sp->NameHash == SPELL_HASH_LIVING_RUBY_PENDANT) //Living Ruby Pendant
			sp->fixed_dddhcoef = 0.0f;
		else if(sp->NameHash == SPELL_HASH_EARTH_SHIELD) //Earth Shield
			sp->fixed_dddhcoef = 0.15f;		//says wowwiki
		else if(sp->NameHash == SPELL_HASH_HOLY_NOVA)
			sp->fixed_dddhcoef = 0.20f;
		else if(sp->NameHash == SPELL_HASH_VAMPIRIC_EMBRACE)
			sp->fixed_dddhcoef = 0.0f;
//		else if(sp->NameHash == SPELL_HASH_STARFALL)
//			sp->fixed_dddhcoef = 0.20f;

		if( strstr( sp->Description, "Must remain seated"))
		{
			sp->RecoveryTime = 1000;
			sp->CategoryRecoveryTime = 1000;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		// procintervals
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//omg lighning shield trigger spell id's are all wrong ?
		//if you are bored you could make thiese by hand but i guess we might find other spells with this problem..and this way it's safe
		if( strstr( sp->Name, "Lightning Shield" ) && sp->EffectTriggerSpell[0] )
		{
			//check if we can find in the desription
			char *startofid = strstr(sp->Description, "for $");
			if( startofid )
			{
				startofid += strlen("for $");
				sp->EffectTriggerSpell[0] = atoi( startofid ); //get new lightning shield trigger id
			}
			sp->proc_interval = 3000; //few seconds
			sp->procFlags2 |= PROC2_REMOVEONUSE;
		}
		//mage ignite talent should proc only on some chances
		else if( strstr( sp->Name, "Ignite") && sp->Id>=11119 && sp->Id<=12848 && sp->EffectApplyAuraName[0] == 4 )
		{
			//check if we can find in the desription
			char *startofid=strstr(sp->Description, "an additional ");
			if(startofid)
			{
				startofid += strlen("an additional ");
				sp->EffectBasePoints[0]=atoi(startofid); //get new value. This is actually level*8 ;)
			}
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA; //aura
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL; //force him to use procspell effect
			sp->EffectTriggerSpell[0] = 12654; //evil , but this is good for us :D
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT; //add procflag here since this was not processed with the others !
			sp->fixed_dddhcoef = 0.00001f;
			sp->fixed_hotdotcoef = 0.00001f;
			SpellEntry *sp2 = dbcSpell.LookupEntryForced( 12654 );
			SetAllSpellCoef( sp2, 0.0001f);
		}
		// Winter's Chill handled by frost school
		else if( strstr( sp->Name, "Winter's Chill"))
		{
			sp->School = 4;
		}
		//more triggered spell ids are wrong. I think blizz is trying to outsmart us :S
		//Chain Heal all ranks %50 heal value (49 + 1)
		else if( strstr( sp->Name, "Chain Heal"))
		{
			sp->EffectDieSides[0] = 49;
		}
/*		else if( sp->Effect[0] = SPELL_EFFECT_DUMMY && strstr( sp->Name, "Holy Shock"))
		{
			//check if we can find in the desription
			char *startofid=strstr(sp->Description, "causing $");
			if(startofid)
			{
				startofid += strlen("causing $");
				sp->EffectTriggerSpell[0] = atoi(startofid);
				sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
				sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_SINGLE_ENEMY;
			}
			//check if we can find in the desription
			startofid=strstr(sp->Description, " or $");
			if(startofid)
			{
				startofid += strlen(" or $");
				sp->EffectTriggerSpell[1]=atoi(startofid);
				sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
				sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_SINGLE_FRIEND;
			}
		}*/
		else if( strstr( sp->Name, "Touch of Weakness"))
		{
			//check if we can find in the desription
			char *startofid=strstr(sp->Description, "cause $");
			if(startofid)
			{
				startofid += strlen("cause $");
				sp->EffectTriggerSpell[0] = atoi(startofid);
				sp->EffectTriggerSpell[1]=sp->EffectTriggerSpell[0]; //later versions of this spell changed to eff[1] the aura
				sp->procFlags = uint32(PROC_ON_MELEE_ATTACK_VICTIM);
			}
		}
		else if( strstr( sp->Name, "Firestone Passive"))
		{
			//Enchants the main hand weapon with fire, granting each attack a chance to deal $17809s1 additional fire damage.
			//check if we can find in the desription
			char * startofid=strstr(sp->Description, "to deal $");
			if(startofid)
			{
				startofid += strlen("to deal $");
				sp->EffectTriggerSpell[0] = atoi(startofid);
				sp->EffectApplyAuraName[0] = 42;
				sp->procFlags = PROC_ON_MELEE_ATTACK;
				sp->procChance = 50;
			}
		}
		//some procs trigger at intervals
		else if( strstr( sp->Name, "Water Shield"))
		{
			sp->proc_interval = 3000; //few seconds
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
		}
		else if( strstr( sp->Name, "Shadowguard"))
		{
			sp->proc_interval = 3000; //few seconds
			sp->procFlags |= PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
		}
		else if( strstr( sp->Name, "Poison Shield"))
		{
			sp->proc_interval = 3000; //few seconds
			sp->procFlags2 |= PROC2_REMOVEONUSE;
		}
		else if( strstr( sp->Name, "Infused Mushroom"))
		{
			sp->proc_interval = 10000; //10 seconds
			sp->procFlags2 |= PROC2_REMOVEONUSE;
		}
		else if( strstr( sp->Name, "Aviana's Purpose"))
		{
			sp->proc_interval = 10000; //10 seconds
			sp->procFlags2 |= PROC2_REMOVEONUSE;
		}
		//don't change to namehash since we are searching only a protion of the name
 		else if( strstr( sp->Name, "Crippling Poison"))
		{
			//sp->SpellGroupType[0] |= 16384; //some of them do have the flags but i's hard to write down those some from 130 spells
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
			sp->NameHash = SPELL_HASH_CRIPPLING_POISON;//cause each rank has new name :S
		}
		else if( strstr( sp->Name, "Mind-numbing Poison"))
		{
			//sp->SpellGroupType[0] |= 32768; //some of them do have the flags but i's hard to write down those some from 130 spells
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
			sp->NameHash = SPELL_HASH_MIND_NUMBING_POISON;//cause each rank has new name :S
		}
		else if( strstr( sp->Name, "Instant Poison"))
		{
			//sp->SpellGroupType[0] |= 8192; //some of them do have the flags but i's hard to write down those some from 130 spells
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
//			sp->procChance = 20;	//this is now PPM based
			sp->NameHash = SPELL_HASH_INSTANT_POISON;//cause each rank has new name :S
		}
		else if( strstr( sp->Name, "Deadly Poison"))
		{
			//sp->SpellGroupType[0] |= 65536; //some of them do have the flags but i's hard to write down those some from 130 spells
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
			sp->procChance = 30;	
			sp->NameHash = SPELL_HASH_DEADLY_POISON;//cause each rank has new name :S
		}
		else if( strstr( sp->Name, "Wound Poison"))
		{
			//sp->SpellGroupType[0] |= 268435456; //some of them do have the flags but i's hard to write down those some from 130 spells
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
			sp->BGR_one_buff_on_target |= SPELL_TYPE_POISON;	//avoid reducing heal to 0%
//			sp->procChance = 50;	//this is now PPM based
			sp->NameHash = SPELL_HASH_WOUND_POISON; //cause each rank has new name :S
		}
		else if( strstr( sp->Name, "Scorpid Poison") )
		{
			// groups?
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
		}

		//warlock - shadow bolt
//		if( sp->NameHash == SPELL_HASH_SHADOW_BOLT )
			//sp->SpellGroupType[0] |= 1; //some of them do have the flags but i's hard to write down those some from 130 spells

/*		else if( strstr( sp->Name, "Anesthetic Poison"))
			sp->SpellGroupType[0] |= 0; //not yet known ? 
		else if( strstr( sp->Name, "Blinding Powder"))
			sp->SpellGroupType[0] |= 0; //not yet known ?
		else 
		if( sp->NameHash == SPELL_HASH_ILLUMINATION )
			sp->EffectTriggerSpell[0] = 20272;*/  // broken trigger spell, do not use
		//sp->dummy=result;
/*		//if there is a proc spell and has 0 as charges then it's probably going to triger infinite times. Better not save these
		if( sp->procCharges==0)
			sp->procCharges=-1;*/
//		if( sp->NameHash == SPELL_HASH_ILLUMINATION )
//			sp->procFlags2 |= PROC2_TARGET_SELF;

		// Set default mechanics if we don't already have one
		if( !sp->MechanicsType )
		{
			//Set Silencing spells mechanic.
			if( sp->EffectApplyAuraName[0] == 27 || 
				sp->EffectApplyAuraName[1] == 27 ||
				sp->EffectApplyAuraName[2] == 27 )
				sp->MechanicsType = MECHANIC_SILENCED;
	
			//Set Stunning spells mechanic.
			if( sp->EffectApplyAuraName[0] == 12 || 
				sp->EffectApplyAuraName[1] == 12 ||
				sp->EffectApplyAuraName[2] == 12 )
				sp->MechanicsType = MECHANIC_STUNNED;
	
			//Set Fearing spells mechanic
			if( sp->EffectApplyAuraName[0] == 7 || 
				sp->EffectApplyAuraName[1] == 7 ||
				sp->EffectApplyAuraName[2] == 7 )
				sp->MechanicsType = MECHANIC_FLEEING;
		
			//Set Interrupted spells mech
			if( sp->Effect[0] == SPELL_EFFECT_INTERRUPT_CAST || 
				sp->Effect[1] == SPELL_EFFECT_INTERRUPT_CAST ||
				sp->Effect[2] == SPELL_EFFECT_INTERRUPT_CAST )
				sp->MechanicsType = MECHANIC_INTERRUPTED;
		}

//		if( sp->proc_interval != 0 )
//			sp->procFlags2 |= PROC2_REMOVEONUSE;

		/* Decapitate */
		if( sp->NameHash == SPELL_HASH_DECAPITATE )
			sp->procChance = 30;

		//shaman - shock, has no spellgroup.very dangerous move !
//		if( sp->NameHash == SPELL_HASH_SHOCK )
			//sp->SpellGroupType[0] = 4;

		//mage - fireball. Only some of the spell has the flags 
//		if( sp->NameHash == SPELL_HASH_FIREBALL )
			//sp->SpellGroupType[0] |= 1;

		if( sp->NameHash == SPELL_HASH_BLESSING_OF_PROTECTION )
			sp->MechanicsType = MECHANIC_INVULNERABLE;
		//else if( sp->NameHash == SPELL_HASH_POWER_WORD__SHIELD )
//			sp->MechanicsType = MECHANIC_INVULNERABLE;
		//maybe all root or loast control effects ?
		else if( sp->NameHash == SPELL_HASH_FROST_NOVA )
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;	//removed in 3.3.3 ?
		else if( sp->NameHash == SPELL_HASH_ENTANGLING_ROOTS )
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;	//removed in 3.3.3 ?
		else if( sp->NameHash == SPELL_HASH_FEAR )
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;	//removed in 3.3.3 ?
		else if( sp->NameHash == SPELL_HASH_PSYCHIC_SCREAM )
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;	//removed in 3.3.3 ?
		else if( sp->NameHash == SPELL_HASH_DRAGON_S_BREATH )
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;	//removed in 3.3.3 ?
		else if( sp->NameHash == SPELL_HASH_SHOCKWAVE )
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;	//removed in 3.3.3 ?
		else if( sp->NameHash == SPELL_HASH_STEALTH )
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ENTER_COMBAT | AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;	//removed in 3.3.3 ?

		/* hackfix for this - FIX ME LATER - Burlex */
		if( namehash == SPELL_HASH_SEAL_FATE )
			sp->procFlags = 0;

		if(	namehash == SPELL_HASH_DEATH_AND_DECAY )
			sp->DK_AP_spell_bonus[0] = 1.68f;
		if(	namehash == SPELL_HASH_FROST_FEVER )
			sp->DK_AP_spell_bonus[0] = 0.055f * 1.15f * sp->quick_tickcount;
		if(	namehash == SPELL_HASH_BLOOD_PLAGUE )
			sp->DK_AP_spell_bonus[0] = 0.055f * 1.15f * sp->quick_tickcount;
		if( namehash == SPELL_HASH_PLAGUE_STRIKE ||
			namehash == SPELL_HASH_RUNE_STRIKE ||
			namehash == SPELL_HASH_BLOOD_STRIKE || 
			namehash == SPELL_HASH_HEART_STRIKE ||
			namehash == SPELL_HASH_SCOURGE_STRIKE || 
			namehash == SPELL_HASH_BLOOD_CAKED_STRIKE ||
			namehash == SPELL_HASH_DEATH_STRIKE ||
			namehash == SPELL_HASH_FROST_STRIKE ||
			namehash == SPELL_HASH_OBLITERATE
			)
			sp->DK_AP_spell_bonus[0] = 1.0f;
		if(	namehash == SPELL_HASH_HOWLING_BLAST )
		{
			sp->DK_AP_spell_bonus[0] = 0.20f;
			sp->DK_AP_spell_bonus[1] = 0.20f;
		}
		else if(	namehash == SPELL_HASH_DEATH_COIL )
		{
			sp->DK_AP_spell_bonus[0] = 0.15f;
			sp->DK_AP_spell_bonus[1] = 0.15f;
		}
		else if(	namehash == SPELL_HASH_BLOOD_BOIL )
			sp->DK_AP_spell_bonus[0] = 0.06f;
		else if(	namehash == SPELL_HASH_DEATH_AND_DECAY )
			sp->DK_AP_spell_bonus[0] = 0.0475f;
		else if(	namehash == SPELL_HASH_ICY_TOUCH )
			sp->DK_AP_spell_bonus[0] = 0.10f;
		else if(	namehash == SPELL_HASH_UNHOLY_BLIGHT )
			sp->DK_AP_spell_bonus[0] = 0.013f;

		if(
			((sp->Attributes & ATTRIBUTES_TRIGGER_COOLDOWN) && (sp->AttributesEx & ATTRIBUTESEX_NOT_BREAK_STEALTH)) //rogue cold blood
			|| ((sp->Attributes & ATTRIBUTES_TRIGGER_COOLDOWN) && (!sp->AttributesEx || sp->AttributesEx & ATTRIBUTESEX_REMAIN_OOC))
			)
			sp->c_is_flags |= SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE;


		///	SPELLS CAN CRIT ///
		sp->spell_can_crit = true; // - except in special cases noted in this section
		sp->spell_DOT_can_crit = true;

		if( sp->NameHash == SPELL_HASH_LIGHTNING_SHIELD ) // not a mistake, the correct proc spell for lightning shield is also called lightning shield
			sp->spell_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_INSECT_SWARM ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_ENTANGLING_ROOTS ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_LACERATE ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_RIP ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_SERPENT_STING ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_EXPLOSIVE_TRAP ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_WYVERN_STING ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_PYROBLAST ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_IGNITE ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_FIREBALL ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_FROSTFIRE_BOLT ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_SEAL_OF_VENGEANCE ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_SEAL_OF_CORRUPTION ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_CONSECRATION ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_HOLY_FIRE ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_CURSE_OF_AGONY ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_SEED_OF_CORRUPTION ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_SHADOW_FLAME ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_BLOOD_PLAGUE ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_DEATH_AND_DECAY ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_FROST_FEVER ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_REND ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_RUPTURE ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_GARROTE ) 
			sp->spell_DOT_can_crit = false;
		else if( sp->NameHash == SPELL_HASH_FLAME_SHOCK ) 
			sp->spell_DOT_can_crit = true;	//Instantly sears the target with fire, causing $s1 Fire damage immediately and $o2 Fire damage over $d. This periodic damage may critically strike and will occur more rapidly based on the caster's spell haste.

		if( sp->EffectApplyAuraName[0] == SPELL_AURA_MOUNTED )
		{
			//this should already be set, seems like some mounts are missing it and leads to speed stacking exploit
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_CAST_SPELL | AURA_INTERRUPT_ON_MOUNT;
			//mount summons instead of speed, just copy effect from somewhere else.
			//these are vehicles. Need to remove this hack later
	//		sp = dbcSpell.LookupEntryForced( 60424 ); //ex : Mekgineer's Chopper
			if( ( sp->EffectApplyAuraName[1] != SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED && sp->EffectApplyAuraName[2] != SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED && strstr( sp->Description, "This is") )
	//			sp->Effect[1] == 28 
				)
			{
				SpellEntry *sp2 = dbcSpell.LookupEntryForced( 23223 ); //Swift White Mechanostrider
				//if( sp2 )
				{
					SpellEntryEffectCopy(sp2,sp,1,1);//haste effect
					sp->EffectBasePoints[1] = 100; //hehe 1.5 horse power for fun :D
				}
			}
		}
		
		// THESE FIXES ARE GROUPED FOR CODE CLEANLINESS.
		//Mend Pet
		if( sp->NameHash == SPELL_HASH_MEND_PET )
			sp->ChannelInterruptFlags = 0;
			
			/*
			// Concussive Shot, Distracting Shot, Silencing Shot - ranged spells
			if( sp->NameHash == SPELL_HASH_CONCUSSIVE_SHOT || sp->NameHash == SPELL_HASH_DISTRACTING_SHOT || sp->NameHash == SPELL_HASH_SILENCING_SHOT || sp->NameHash == SPELL_HASH_SCATTER_SHOT || sp->NameHash == SPELL_HASH_TRANQUILIZING_SHOT )
				sp->is_ranged_spell = true;

			// All stings - ranged spells
			if( sp->NameHash == SPELL_HASH_SERPENT_STING || sp->NameHash == SPELL_HASH_SCORPID_STING || sp->NameHash == SPELL_HASH_VIPER_STING || sp->NameHash == SPELL_HASH_WYVERN STING )
				sp->is_ranged_spell = true;
			*/
			// come to think of it... anything *castable* requiring a ranged weapon is a ranged spell -.-
			// Note that talents etc also come under this, however it does not matter
			// if they get flagged as ranged spells because is_ranged_spell is only used for
			// differentiating between resistable and physically avoidable spells.
//			if( sp->EquippedItemClass == 2 && sp->EquippedItemSubClass & 262156 ) // 4 + 8 + 262144 ( becomes item classes 2, 3 and 18 which correspond to bow, gun and crossbow respectively)
//				sp->is_ranged_spell = true;

		//////////////////////////////////////////
		// ROGUE								//
		//////////////////////////////////////////

		// Insert rogue spell fixes here
		if( sp->NameHash == SPELL_HASH_REMORSELESS_ATTACKS )
			sp->procFlags = PROC_ON_GAIN_EXPIERIENCE;

		if( sp->NameHash == SPELL_HASH_UNFAIR_ADVANTAGE )
			sp->procFlags = PROC_ON_DODGE_VICTIM;


		//////////////////////////////////////////
		// PRIEST								//
		//////////////////////////////////////////
		if( sp->NameHash == SPELL_HASH_BORROWED_TIME )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
		}

		// Insert priest spell fixes here
		// Mind Flay,reduces target's movement speed by 50%
		if ( sp->NameHash == SPELL_HASH_MIND_FLAY )
		{
			sp->EffectApplyAuraName[2] = SPELL_AURA_PERIODIC_DAMAGE;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SINGLE_ENEMY;
			sp->Effect[0] = SPELL_EFFECT_NULL;	//remove dummy effect
			sp->c_is_flags |= SPELL_FLAG_IS_DAMAGING;
		}

		if( sp->NameHash == SPELL_HASH_TIDAL_WAVES )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_CHAIN_HEAL;
			sp->ProcOnNameHash[1] = SPELL_HASH_RIPTIDE;
		}

		//Earthliving Weapon
		if( sp->NameHash == SPELL_HASH_EARTHLIVING_WEAPON__PASSIVE_)
			sp->procFlags = PROC_ON_CAST_SPELL;
		
//junk code to get me has :P 
//if( sp->Id==11267 || sp->Id==11289 || sp->Id==6409)
//	printf("!!!!!!! name %s , id %u , hash %u \n",sp->Name,sp->Id, namehash);
	}


	/////////////////////////////////////////////////////////////////
	//SPELL COEFFICIENT SETTINGS START
	//////////////////////////////////////////////////////////////////

	for(uint32 x=0; x < cnt; x++)
	{
		// get spellentry
		SpellEntry * sp = dbcSpell.LookupRow(x);

		for( uint8 i = 0 ; i < 3 ; i++ )
		{
			//Flag for DoT and HoT
			if( sp->EffectApplyAuraName[i] == SPELL_AURA_PERIODIC_DAMAGE )
				sp->spell_coef_flags |= SPELL_FLAG_IS_DOT_SPELL;
			if(	sp->EffectApplyAuraName[i] == SPELL_AURA_PERIODIC_HEAL )
				sp->spell_coef_flags |= SPELL_FLAG_IS_HOT_SPELL;
			if(	sp->EffectApplyAuraName[i] == SPELL_AURA_PERIODIC_LEECH )
				sp->spell_coef_flags |= SPELL_FLAG_IS_DOT_SPELL | SPELL_FLAG_IS_HOT_SPELL;

			//Flag for DD or DH
			if ( sp->EffectApplyAuraName[i] == SPELL_AURA_PERIODIC_TRIGGER_SPELL && sp->EffectTriggerSpell[i] )
			{
				SpellEntry * spz;
				spz = dbcSpell.LookupEntryForced( sp->EffectTriggerSpell[i] );
				if( spz )
				{	
					if(spz->Effect[i] == SPELL_EFFECT_SCHOOL_DAMAGE )
						sp->spell_coef_flags |= SPELL_FLAG_IS_DD_SPELL;
					if( spz->Effect[i] == SPELL_EFFECT_HEAL)
						sp->spell_coef_flags |= SPELL_FLAG_IS_DH_SPELL;
				}
			}
			if (sp->Effect[i] == SPELL_EFFECT_SCHOOL_DAMAGE )
				sp->spell_coef_flags |= SPELL_FLAG_IS_DD_SPELL;
			if (sp->Effect[i] == SPELL_EFFECT_HEAL)
				sp->spell_coef_flags |= SPELL_FLAG_IS_DH_SPELL;
		}

		for(uint8 i = 0 ; i < 3; i++)
		{
			switch (sp->EffectImplicitTargetA[i])
			{
				//AoE
			case EFF_TARGET_ALL_TARGETABLE_AROUND_LOCATION_IN_RADIUS:
			case EFF_TARGET_ALL_ENEMY_IN_AREA:
			case EFF_TARGET_ALL_ENEMY_IN_AREA_INSTANT:
			case EFF_TARGET_ALL_PARTY_AROUND_CASTER:
			case EFF_TARGET_ALL_ENEMIES_AROUND_CASTER:
			case EFF_TARGET_IN_FRONT_OF_CASTER:
			case EFF_TARGET_ALL_ENEMY_IN_AREA_CHANNELED:
			case EFF_TARGET_ALL_ENEMY_AT_ENEMY_IN_AREA_CHANNELED:
			case EFF_TARGET_ALL_FRIENDLY_IN_AREA:
			case EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME:
			case EFF_TARGET_ALL_PARTY:
			case EFF_TARGET_LOCATION_INFRONT_CASTER:
			case EFF_TARGET_BEHIND_TARGET_LOCATION:
			case EFF_TARGET_LOCATION_INFRONT_CASTER_AT_RANGE:
				{
					sp->spell_coef_flags |= SPELL_FLAG_AOE_SPELL;
					break;
				}
			}	
		}

		for(uint8 i = 0 ; i < 3 ; i++)
		{
			switch (sp->EffectImplicitTargetB[i])
			{
				//AoE
			case EFF_TARGET_ALL_TARGETABLE_AROUND_LOCATION_IN_RADIUS:
			case EFF_TARGET_ALL_ENEMY_IN_AREA:
			case EFF_TARGET_ALL_ENEMY_IN_AREA_INSTANT:
			case EFF_TARGET_ALL_PARTY_AROUND_CASTER:
			case EFF_TARGET_ALL_ENEMIES_AROUND_CASTER:
			case EFF_TARGET_IN_FRONT_OF_CASTER:
			case EFF_TARGET_ALL_ENEMY_IN_AREA_CHANNELED:
			case EFF_TARGET_ALL_ENEMY_AT_ENEMY_IN_AREA_CHANNELED:
			case EFF_TARGET_ALL_FRIENDLY_IN_AREA:
			case EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME:
			case EFF_TARGET_ALL_PARTY:
			case EFF_TARGET_LOCATION_INFRONT_CASTER:
			case EFF_TARGET_BEHIND_TARGET_LOCATION:
			case EFF_TARGET_LOCATION_INFRONT_CASTER_AT_RANGE:
				{
					sp->spell_coef_flags |= SPELL_FLAG_AOE_SPELL;
					break;
				}
			}	
		}

		//Special Cases
		//Holy Light & Flash of Light
		if(sp->NameHash == SPELL_HASH_HOLY_LIGHT ||	sp->NameHash == SPELL_HASH_FLASH_OF_LIGHT)
			sp->spell_coef_flags |= SPELL_FLAG_IS_DH_SPELL;

		//Additional Effect (not healing or damaging)
		for( uint8 i = 0 ; i < 3 ; i++ )
		{
			if( sp->Effect[i] == 0)
				continue;

			switch (sp->Effect[i])
			{
			case SPELL_EFFECT_SCHOOL_DAMAGE:
			case SPELL_EFFECT_ENVIRONMENTAL_DAMAGE:
			case SPELL_EFFECT_HEALTH_LEECH:
			case SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL:
			case SPELL_EFFECT_ADD_EXTRA_ATTACKS:
			case SPELL_EFFECT_WEAPON_PERCENT_DAMAGE:
			case SPELL_EFFECT_POWER_BURN:
			case SPELL_EFFECT_ATTACK:
			case SPELL_EFFECT_HEAL:
//			case SPELL_EFFECT_HEALTH_FUNNEL:
			case SPELL_EFFECT_HEAL_MAX_HEALTH:
			case SPELL_EFFECT_DUMMY:
				continue;
			}

			switch (sp->EffectApplyAuraName[i])
			{
			case SPELL_AURA_PERIODIC_DAMAGE:
			case SPELL_AURA_PROC_TRIGGER_DAMAGE:
			case SPELL_AURA_PERIODIC_DAMAGE_PERCENT:
			case SPELL_AURA_POWER_BURN:
			case SPELL_AURA_PERIODIC_HEAL:
			case SPELL_AURA_MOD_INCREASE_HEALTH:
			case SPELL_AURA_PERIODIC_HEALTH_FUNNEL:
			case SPELL_AURA_DUMMY:
				continue;
			}

			sp->spell_coef_flags |= SPELL_FLAG_ADITIONAL_EFFECT;
			break;

		}

		//Calculating fixed coeficients
		//Channeled spells
		if( sp->ChannelInterruptFlags != 0 )
		{
			float Duration = float( GetDuration( dbcSpellDuration.LookupEntry( sp->DurationIndex ) ));
//			if(Duration < 1500) Duration = 1500;
//			else if(Duration > 7000) Duration = 7000;
			sp->fixed_hotdotcoef = (Duration / 3500.0f);		//according to wiki
//			sp->fixed_hotdotcoef = (Duration / 1500.0f);		//not correct but spells were dealing low dmg compared to blizz
			if( sp->spell_coef_flags & (SPELL_FLAG_IS_HOT_SPELL|SPELL_FLAG_IS_DH_SPELL) )
				sp->fixed_hotdotcoef *= 1.8f;
			sp->fixed_dddhcoef = sp->fixed_hotdotcoef;
			if( sp->spell_coef_flags & SPELL_FLAG_AOE_SPELL )
			{
				sp->fixed_dddhcoef *= 0.5f;
				sp->fixed_hotdotcoef *= 0.5f;
			}		

			//!!make so triggered spell inherits the bonus coeffs
			SpellEntry *sp2;
			sp2 = dbcSpell.LookupEntryForced( sp->EffectTriggerSpell[0] );
			if( sp2 && ( sp2->CastingTimeIndex <= 1 || sp2->CastingTimeIndex == 200 || sp2->CastingTimeIndex == 205 ) )
			{
				sp2->fixed_hotdotcoef = sp->fixed_hotdotcoef / sp->quick_tickcount;
				sp2->fixed_dddhcoef = sp->fixed_dddhcoef / sp->quick_tickcount;
			}
			sp2 = dbcSpell.LookupEntryForced( sp->EffectTriggerSpell[1] );
			if( sp2 && ( sp2->CastingTimeIndex <= 1 || sp2->CastingTimeIndex == 200 || sp2->CastingTimeIndex == 205 ) )
			{
				sp2->fixed_hotdotcoef = sp->fixed_hotdotcoef / sp->quick_tickcount;
				sp2->fixed_dddhcoef = sp->fixed_dddhcoef / sp->quick_tickcount;
			}
			sp2 = dbcSpell.LookupEntryForced( sp->EffectTriggerSpell[2] );
			if( sp2 && ( sp2->CastingTimeIndex <= 1 || sp2->CastingTimeIndex == 200 || sp2->CastingTimeIndex == 205 ) )
			{
				sp2->fixed_hotdotcoef = sp->fixed_hotdotcoef / sp->quick_tickcount;
				sp2->fixed_dddhcoef = sp->fixed_dddhcoef / sp->quick_tickcount;
			}

			if( sp->spell_coef_flags & SPELL_FLAG_ADITIONAL_EFFECT )
				sp->fixed_hotdotcoef *= 0.95f;
			if( sp->spell_coef_flags & SPELL_FLAG_AOE_SPELL )
				sp->fixed_hotdotcoef *= 0.5f;
		}
		//spells that are triggered by channeling spells will have something else then 0
		if( sp->fixed_dddhcoef == -1.0f )
		{
			//Setting Cast Time Coefficient
			SpellCastTime *sd = dbcSpellCastTime.LookupEntry(sp->CastingTimeIndex);
			float casttime_coef = 0;
			float castaff = float(GetCastTime(sd));
			if(castaff < 1500) 
				castaff = 1500;
			else if(castaff > 7000) 
				castaff = 7000;

			casttime_coef = castaff / 3500;	
			if( sp->spell_coef_flags & SPELL_FLAG_IS_DH_SPELL )
				casttime_coef *= 1.88f;
			//direct spell coefficients
			sp->fixed_dddhcoef = casttime_coef;

			//Standard spells - DOWNRANKING !
	/*		else if( (sp->spell_coef_flags & SPELL_FLAG_IS_DD_OR_DH_SPELL) && !(sp->spell_coef_flags & SPELL_FLAG_IS_DOT_OR_HOT_SPELL) )
			{
				sp->fixed_dddhcoef = sp->casttime_coef;
				if( sp->spell_coef_flags & SPELL_FLAG_ADITIONAL_EFFECT )
					sp->fixed_dddhcoef *= 0.95f;
				if( sp->spell_coef_flags & SPELL_FLAG_AOE_SPELL )
					sp->fixed_dddhcoef *= 0.5f;
			}*/

			//Over-time spells
			//if(sp->spell_coef_flags & SPELL_FLAG_IS_DD_OR_DH_SPELL) == 0 ) //not a DD spell. But we do not care since we make the test live
			{
				if( sp->spell_coef_flags & ( SPELL_FLAG_IS_DOT_SPELL | SPELL_FLAG_IS_HOT_SPELL ) ) 
				{
					float Duration = float( GetDuration( dbcSpellDuration.LookupEntry( sp->DurationIndex ) ));
					sp->fixed_hotdotcoef = (Duration / 15000.0f);

					if( sp->spell_coef_flags & SPELL_FLAG_ADITIONAL_EFFECT )
						sp->fixed_hotdotcoef *= 0.95f;
				}
				//healing spells get extra bonus
				if( sp->spell_coef_flags & SPELL_FLAG_IS_HOT_SPELL )
					sp->fixed_hotdotcoef *= 1.8f;
			}
			//Combined standard and over-time spells
			if( (sp->spell_coef_flags & ( SPELL_FLAG_IS_DOT_SPELL | SPELL_FLAG_IS_HOT_SPELL ))
				&&
				(sp->spell_coef_flags & ( SPELL_FLAG_IS_DD_SPELL | SPELL_FLAG_IS_DH_SPELL ))
				)
			{
	//			float Portion_to_Over_Time = (Duration / 15000.0f) / ((Duration / 15000.0f) + sp->casttime_coef );
	//			float Portion_to_Standard = 1.0f - Portion_to_Over_Time;
	//			sp->fixed_dddhcoef = casttime_coef * Portion_to_Standard;
	//			sp->fixed_hotdotcoef = (Duration / 15000.0f) * Portion_to_Over_Time;
				//according to wowwiki
				//x = Duration / 15
				//y = Cast Time / 3.5
				//CDoT = x2 / (x + y)
				//CDD = y2 / (x + y)
				//!!!! atm code will use DOT coeff for mixed spells !!!
				float Duration = float( GetDuration( dbcSpellDuration.LookupEntry( sp->DurationIndex ) ));
				float CastTime = float(GetCastTime(sd));
				if(CastTime < 1500) 
					CastTime = 1500;
				else if(CastTime > 7000) 
					CastTime = 7000;
				float x = Duration / 15000.0f;
				float y = CastTime / 3500.0f;
				sp->fixed_dddhcoef = y * y / (x + y );
				sp->fixed_hotdotcoef = x * x / ( x + y );

				if( sp->spell_coef_flags & SPELL_FLAG_ADITIONAL_EFFECT )
				{
					sp->fixed_dddhcoef *= 0.95f;
					sp->fixed_hotdotcoef *= 0.95f;
				}
			}
			if( sp->spell_coef_flags & SPELL_FLAG_AOE_SPELL )
			{
				sp->fixed_dddhcoef *= 0.5f;
				sp->fixed_hotdotcoef *= 0.5f;
			}		
		}
		///////////////
		// !!! big HAX to make spells blizzlike. I bet there is a good explanation for this !!!
		///////////////
/*		if( sp->spell_coef_flags & ( SPELL_FLAG_IS_HEALING | SPELL_FLAG_IS_HOT_SPELL | SPELL_FLAG_IS_HEAL_OVER_TIME ) ) 
		{
			sp->fixed_dddhcoef += 0.2f;
			sp->fixed_hotdotcoef += 0.2f;
		} */

		//////////////////////////////////////////
		// SHAMAN								//
		//////////////////////////////////////////

		// Insert shaman spell fixes here

		// Frostbrand Weapon - 10% spd coefficient
		if( sp->NameHash == SPELL_HASH_FROSTBRAND_ATTACK )
			sp->fixed_dddhcoef = 0.1f;

		// Fire Nova - 0% spd coefficient
		if( sp->NameHash == SPELL_HASH_FIRE_NOVA )
			sp->fixed_dddhcoef = 0.0f;

		// Searing Totem - 8% spd coefficient
		if( sp->NameHash == SPELL_HASH_ATTACK )
			sp->fixed_dddhcoef = 0.08f;

		// Healing Stream Totem - 8% healing coefficient
		if( sp->NameHash == SPELL_HASH_HEALING_STREAM )
			sp->fixed_hotdotcoef = 0.08f;
		else if( sp->NameHash == SPELL_HASH_MIND_FLAY )
			sp->fixed_hotdotcoef = 0.30f * sp->quick_tickcount;	//cause it is based on dot and not total
		else if( sp->NameHash == SPELL_HASH_DEVOURING_PLAGUE )
			sp->fixed_hotdotcoef = 0.20f * sp->quick_tickcount;	//cause it is based on dot and not total

	}

	//Settings for special cases
	QueryResult * resultx = WorldDatabase.Query("SELECT * FROM spell_coef_override");
	if( resultx != NULL )
	{
		do 
		{
			Field * f;
			f = resultx->Fetch();
			SpellEntry * sp = dbcSpell.LookupEntryForced( f[0].GetUInt32() );
			if( sp != NULL )
			{
				sp->fixed_dddhcoef = f[2].GetFloat();
				sp->fixed_hotdotcoef = f[3].GetFloat();
			}
			else
				Log.Warning("SpellCoefOverride", "Has nonexistant spell %u.", f[0].GetUInt32());
		} while( resultx->NextRow() );
		delete resultx;
		resultx = NULL;
	}

	//Fully loaded coefficients, we must share channeled coefficient to its triggered spells
/*	for(uint32 x=0; x < cnt; x++)
	{
		// get spellentry
		SpellEntry * sp = dbcSpell.LookupRow(x);
		SpellEntry * spz;

		//Case SPELL_AURA_PERIODIC_TRIGGER_SPELL
		for( uint8 i = 0 ; i < 3 ; i++ )
		{
			if ( sp->EffectApplyAuraName[i] == SPELL_AURA_PERIODIC_TRIGGER_SPELL )
			{
				spz = dbcSpell.LookupEntryForced( sp->EffectTriggerSpell[i] );
				if( spz != NULL ) 
				{
					//we must set bonus per tick on triggered spells now (i.e. Arcane Missiles)
					if( sp->ChannelInterruptFlags != 0 )
					{
						float Duration = float( GetDuration( dbcSpellDuration.LookupEntry( sp->DurationIndex ) ));
						float amp = float(sp->EffectAmplitude[i]);
						sp->fixed_dddhcoef = sp->fixed_hotdotcoef * amp / Duration;
					}			
					spz->fixed_dddhcoef = sp->fixed_dddhcoef;
					//we must set bonus per tick on triggered spells now (i.e. Arcane Missiles)
					if( sp->ChannelInterruptFlags != 0 )
					{
						float Duration = float( GetDuration( dbcSpellDuration.LookupEntry( sp->DurationIndex ) ));
						float amp = float(sp->EffectAmplitude[i]);
						sp->fixed_hotdotcoef *= amp / Duration;
					}
					spz->fixed_hotdotcoef = sp->fixed_hotdotcoef;
					break;
				}
			}
		}
	}	*/

	/////////////////////////////////////////////////////////////////
	//SPELL COEFFICIENT SETTINGS END
	/////////////////////////////////////////////////////////////////
	SpellEntry *sp,*sp2;

	EnchantEntry* Enchantment;

	// Flametongue totem
	Enchantment = dbcEnchant.LookupEntryForced( 124 );
	if( Enchantment != NULL )
	{
		Enchantment->type[0] = 1;
		Enchantment->spell[0] = 8253;
	}
	Enchantment = dbcEnchant.LookupEntryForced( 285 );
	if( Enchantment != NULL )
	{
		Enchantment->type[0] = 1;
		Enchantment->spell[0] = 8248;
	}
	Enchantment = dbcEnchant.LookupEntryForced( 543 );
	if( Enchantment != NULL )
	{
		Enchantment->type[0] = 1;
		Enchantment->spell[0] = 10523;
	}
	Enchantment = dbcEnchant.LookupEntryForced( 1683 );
	if( Enchantment != NULL )
	{
		Enchantment->type[0] = 1;
		Enchantment->spell[0] = 16389;
	}
	Enchantment = dbcEnchant.LookupEntryForced( 2637 );
	if( Enchantment != NULL )
	{
		Enchantment->type[0] = 1;
		Enchantment->spell[0] = 25555;
	}

	/********************************************************
	 * Windfury Enchantment
	 ********************************************************/
	sp = dbcSpell.LookupEntryForced( 33757 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_MELEE_ATTACK; //we do not need proc on spell ;)
		sp->EffectTriggerSpell[0] = 33010; //for the logs and rest
		sp->procChance = 20;
		sp->proc_interval = 8000;//http://www.wowwiki.com/Windfury_Weapon
		sp->maxstack = 1;
	}
		
/*	Enchantment = dbcEnchant.LookupEntryForced( 283 );
	if( Enchantment != NULL )
		Enchantment->spell[0] = 33757; //this is actually good
	Enchantment = dbcEnchant.LookupEntryForced( 284 );
	if( Enchantment != NULL )
		Enchantment->spell[0] = 33757; 
	Enchantment = dbcEnchant.LookupEntryForced( 525 );
	if( Enchantment != NULL )
		Enchantment->spell[0] = 33757; 
	Enchantment = dbcEnchant.LookupEntryForced( 1669 );
	if( Enchantment != NULL )
		Enchantment->spell[0] = 33757; 
	Enchantment = dbcEnchant.LookupEntryForced( 2636 );
	if( Enchantment != NULL )
		Enchantment->spell[0] = 33757; 
	Enchantment = dbcEnchant.LookupEntryForced( 3785 );
	if( Enchantment != NULL )
		Enchantment->spell[0] = 33757; 
	Enchantment = dbcEnchant.LookupEntryForced( 3786 );
	if( Enchantment != NULL )
		Enchantment->spell[0] = 33757; 
	Enchantment = dbcEnchant.LookupEntryForced( 3787 );
	if( Enchantment != NULL )
		Enchantment->spell[0] = 33757; */

	/**********************************************************
	 *	PROFFESION - Enchant Cloak - Major Resistance
	 **********************************************************/
	sp = dbcSpell.LookupEntryForced( 27962 );
	//if( sp != NULL )
		sp->EffectMiscValue[0] = 2998;
	sp = dbcSpell.LookupEntryForced( 36285 );
	//if( sp != NULL )
		sp->EffectMiscValue[0] = 2998;

	/**********************************************************
	 *	Wand Shoot
	 **********************************************************/
//	sp = dbcSpell.LookupEntryForced( 5019 );
//	//if( sp != NULL )
		//sp->SpellGroupType[0] = 134217728;

	/**********************************************************
	 * Berserking - TROLL'S RACIAL SPELL
	 **********************************************************/
/*	sp = dbcSpell.LookupEntryForced( 20554 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 26635;
	}
	sp = dbcSpell.LookupEntryForced( 26296 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 26635;
	}
	sp = dbcSpell.LookupEntryForced( 26297 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 26635;
	}*/

//	sp = dbcSpell.LookupEntryForced( 20134 ); // << --- WTF?
	//if( sp != NULL )
//		sp->procChance = 50;

	/**********************************************************
	* Mana Tap - BLOOD ELF RACIAL
	**********************************************************/
	sp = dbcSpell.LookupEntryForced( 28734 );
	//if( sp != NULL )
//		sp->Effect[0] = SPELL_EFFECT_POWER_BURN; // should be Power Burn, not Power Drain. Power Drain leeches mana which is incorrect.
		//Zazk : tested on retail and it is only leech and not burn !
		sp->Effect[0] = SPELL_EFFECT_POWER_DRAIN; // should be Power Burn, not Power Drain. Power Drain leeches mana which is incorrect.

	/**********************************************************
	 * thrown - add a 1.6 second cooldown
	 **********************************************************/
	const static uint32 thrown_spells[] = {SPELL_RANGED_GENERAL,SPELL_RANGED_THROW,SPELL_RANGED_WAND, 26679, 29436, 37074, 41182, 41346, 0};
	for(i = 0; thrown_spells[i] != 0; ++i)
	{
		sp = dbcSpell.LookupEntryForced( thrown_spells[i] );
		//if( sp != NULL && sp->RecoveryTime==0 && sp->StartRecoveryTime == 0 )
			sp->RecoveryTime = 1600;
		sp->AttributesExB &= ~( FLAGS3_REQ_BEHIND_TARGET );	//throw had this buget in 3.2
	}

	/**********************************************************
	 * Wands
	 **********************************************************/
	sp = dbcSpell.LookupEntryForced( SPELL_RANGED_WAND );
	//if( sp != NULL )
		sp->Spell_Dmg_Type = SPELL_DMG_TYPE_RANGED;

	/**********************************************************
	 * Misc stuff (questfixes etc)
	 **********************************************************/

	sp = dbcSpell.LookupEntryForced( 30877 );
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetB[0]=0;
	}

	sp = dbcSpell.LookupEntryForced(23179);
	//if( sp != NULL )
		sp->EffectMiscValue[0] = 1434;

	// list of guardians that should inherit casters level
	//fire elemental
	sp = dbcSpell.LookupEntryForced(32982); 
	//if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_INHERITING_LEVEL;
	//Earth elemental
	sp = dbcSpell.LookupEntryForced(33663); 
	//if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_INHERITING_LEVEL;

	//Storm, Earth and Fire
	sp = dbcSpell.LookupEntryForced(51483); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 64695;
		sp->ProcOnNameHash[0] = SPELL_HASH_EARTHBIND_TOTEM;
		sp->procChance = sp->EffectBasePoints[1] + 1;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced(51485); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 64695;
		sp->ProcOnNameHash[0] = SPELL_HASH_EARTHBIND_TOTEM;
		sp->procChance = sp->EffectBasePoints[1] + 1;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced(51486); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 64695;
		sp->ProcOnNameHash[0] = SPELL_HASH_EARTHBIND_TOTEM;
		sp->procChance = sp->EffectBasePoints[1] + 1;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	//////////////////////////////////////////////////////
	// CLASS-SPECIFIC SPELL FIXES						//
	//////////////////////////////////////////////////////

/*		// !!! not sure this is good !!! have to test
		// Hunter's mark r1
		sp = dbcSpell.LookupEntryForced( 1130 ); 
		//if( sp != NULL )
			sp->maxstack = (sp->EffectBasePoints[1]*3) / (sp->EffectBasePoints[1]/10);
		sp = dbcSpell.LookupEntryForced( 14323 ); 
		//if( sp != NULL )
			sp->maxstack = (sp->EffectBasePoints[1]*3) / (sp->EffectBasePoints[1]/10);
		sp = dbcSpell.LookupEntryForced( 14324 ); 
		//if( sp != NULL )
			sp->maxstack = (sp->EffectBasePoints[1]*3) / (sp->EffectBasePoints[1]/10);
		sp = dbcSpell.LookupEntryForced( 14325 ); 
		//if( sp != NULL )
			sp->maxstack = (sp->EffectBasePoints[1]*3) / (sp->EffectBasePoints[1]/10);
			*/

	//////////////////////////////////////////
	// MAGE								//
	//////////////////////////////////////////


	// Shattered Barrier
	sp = dbcSpell.LookupEntryForced(44745);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 55080;
		sp->ProcOnNameHash[0] = SPELL_HASH_ICE_BARRIER;
		sp->procFlags = PROC_ON_AURA_REMOVE;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced(54787);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 55080;
		sp->ProcOnNameHash[0] = SPELL_HASH_ICE_BARRIER;
		sp->procFlags = PROC_ON_AURA_REMOVE;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	}

	// Burnout
	sp = dbcSpell.LookupEntryForced(44449);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 44450;
		sp->EffectImplicitTargetA[1] = 1;
		sp->procChance = 100;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}
	sp = dbcSpell.LookupEntryForced(44469);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 44450;
		sp->EffectImplicitTargetA[1] = 1;
		sp->procChance = 100;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}
	sp = dbcSpell.LookupEntryForced(44470);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 44450;
		sp->EffectImplicitTargetA[1] = 1;
		sp->procChance = 100;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}
	sp = dbcSpell.LookupEntryForced(44471);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 44450;
		sp->EffectImplicitTargetA[1] = 1;
		sp->procChance = 100;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}
	sp = dbcSpell.LookupEntryForced(44472);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 44450;
		sp->EffectImplicitTargetA[1] = 1;
		sp->procChance = 100;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}
	// Setup
	sp = dbcSpell.LookupEntryForced(13983);
	//if(sp != NULL)
	{
		sp->proc_interval = 1000;
		sp->procFlags = PROC_ON_RESIST_VICTIM | PROC_ON_DODGE_VICTIM;
		sp->procChance = 33;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced(14070);
	//if(sp != NULL)
	{
		sp->proc_interval = 1000;
		sp->procFlags = PROC_ON_RESIST_VICTIM | PROC_ON_DODGE_VICTIM;
		sp->procChance = 66;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced(14071);
	//if(sp != NULL)
	{
		sp->proc_interval = 1000;
		sp->procFlags = PROC_ON_RESIST_VICTIM | PROC_ON_DODGE_VICTIM;
		sp->procChance = 100;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	}
	// Brain Freeze rank 1
	sp = dbcSpell.LookupEntryForced( 44546 );
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 44548 );
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 44549 );
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//brain freez proc
	sp = dbcSpell.LookupEntryForced( 57761 );
	//if(sp != NULL)
	{
		sp->procCharges = 1;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	//Arcane Potency
	sp = dbcSpell.LookupEntryForced( 31571 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 57529;
		sp->ProcOnNameHash[0] = SPELL_HASH_CLEARCASTING;
		sp->ProcOnNameHash[1] = SPELL_HASH_PRESENCE_OF_MIND;
	}
	sp = dbcSpell.LookupEntryForced( 31572 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 57531;
		sp->ProcOnNameHash[0] = SPELL_HASH_CLEARCASTING;
		sp->ProcOnNameHash[1] = SPELL_HASH_PRESENCE_OF_MIND;
	}
	//Arcane Potency procs
	sp = dbcSpell.LookupEntryForced( 57529 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procCharges = 1;
		sp->AuraInterruptFlags = 0;
	}
	sp = dbcSpell.LookupEntryForced( 57531 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procCharges = 1;
		sp->AuraInterruptFlags = 0;
	}

	if( sp->NameHash == SPELL_HASH_IMPROVED_COUNTERSPELL )
		sp->procFlags = PROC_ON_CAST_SPELL;

	//////////////////////////////////////////
	// WARLOCK								//
	//////////////////////////////////////////

	// Insert warlock spell fixes here

	//Empowered Imp
	sp = dbcSpell.LookupEntryForced( 47220 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp->procChance = sp->EffectBasePoints[1]+1;
		sp->procFlags2 |= PROC2_TARGET_SELF;	//well actually owner
		sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 47283;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_PET_MASTER;
	}
	sp = dbcSpell.LookupEntryForced( 47221 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp->procChance = sp->EffectBasePoints[1]+1;
		sp->procFlags2 |= PROC2_TARGET_SELF;	//well actually owner
		sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 47283;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_PET_MASTER;
	}
	sp = dbcSpell.LookupEntryForced( 47223 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp->procChance = sp->EffectBasePoints[1]+1;
		sp->procFlags2 |= PROC2_TARGET_SELF;	//well actually owner
		sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 47283;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_PET_MASTER;
	}

	//warlock set that can be exploited by DK class to increase health uber much
	//oblivion rainment
	sp = dbcSpell.LookupEntryForced( 37376 );
	//if( sp != NULL )
		sp->RequiredPlayerClass = ( 1 << WARLOCK );
	sp = dbcSpell.LookupEntryForced( 37375 );
	//if( sp != NULL )
		sp->RequiredPlayerClass = ( 1 << WARLOCK );

	//Improved Shadow Bolt 
	sp = dbcSpell.LookupEntryForced( 17793 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
	}
	sp = dbcSpell.LookupEntryForced( 17796 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
	}
	sp = dbcSpell.LookupEntryForced( 17801 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
	}
	sp = dbcSpell.LookupEntryForced( 17802 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
	}
	sp = dbcSpell.LookupEntryForced( 17803 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
	}

	//Decimation
	sp = dbcSpell.LookupEntryForced( 63156 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
		sp->ProcOnNameHash[ 1 ] = SPELL_HASH_INCINERATE;
		sp->ProcOnNameHash[ 2 ] = SPELL_HASH_SOUL_FIRE;
	}
	sp = dbcSpell.LookupEntryForced( 63158 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
		sp->ProcOnNameHash[ 1 ] = SPELL_HASH_INCINERATE;
		sp->ProcOnNameHash[ 2 ] = SPELL_HASH_SOUL_FIRE;
	}

	//Warlock Everlasting Affliction 
	sp = dbcSpell.LookupEntryForced( 47201 );
	//if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 47202 );
	//if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 47203 );
	//if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 47204 );
	//if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 47205 );
	//if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;

	//Warlock Haunt 
	sp = dbcSpell.LookupEntryForced( 48181 );
	//if( sp != NULL )
	{
		//get previous dmg then register a cast on aura remove on the target to cast it on us
		sp->Effect[1] = SPELL_EFFECT_SCRIPT_EFFECT;
		sp->procFlags2 |= PROC2_REMOVEONUSE;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HAUNT;
	}
	sp = dbcSpell.LookupEntryForced( 59161 );
	//if( sp != NULL )
	{
		//get previous dmg then register a cast on aura remove on the target to cast it on us
		sp->Effect[1] = SPELL_EFFECT_SCRIPT_EFFECT;
		sp->procFlags2 |= PROC2_REMOVEONUSE;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HAUNT;
	}
	sp = dbcSpell.LookupEntryForced( 59163 );
	//if( sp != NULL )
	{
		//get previous dmg then register a cast on aura remove on the target to cast it on us
		sp->Effect[1] = SPELL_EFFECT_SCRIPT_EFFECT;
		sp->procFlags2 |= PROC2_REMOVEONUSE;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HAUNT;
	}
	sp = dbcSpell.LookupEntryForced( 59164 );
	//if( sp != NULL )
	{
		//get previous dmg then register a cast on aura remove on the target to cast it on us
		sp->Effect[1] = SPELL_EFFECT_SCRIPT_EFFECT;
		sp->procFlags2 |= PROC2_REMOVEONUSE;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HAUNT;
	}
	sp = dbcSpell.LookupEntryForced( 48181 );
	//if( sp != NULL )
	{
		//get previous dmg then register a cast on aura remove on the target to cast it on us
		sp->Effect[1] = SPELL_EFFECT_SCRIPT_EFFECT;
		sp->procFlags2 |= PROC2_REMOVEONUSE;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HAUNT;
	}
	sp = dbcSpell.LookupEntryForced( 48210 );
	sp2 = dbcSpell.LookupEntryForced( 50091 );
	//if( sp != NULL )
		SpellEntryEffectCopy( sp, sp2, 0, 0 );

	//Warlock Improved Felhunter 
	sp = dbcSpell.LookupEntryForced( 54037 );
	//if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 54425;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BITE;
		sp->EffectImplicitTargetA[ 2 ] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 54038 );
	//if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 54425;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BITE;
		sp->EffectImplicitTargetA[ 2 ] = EFF_TARGET_PET;
	}

	//Warlock Improved Fear 
	sp = dbcSpell.LookupEntryForced( 53754 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_AURA_REMOVE;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 60946;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FEAR;
	}
	sp = dbcSpell.LookupEntryForced( 53759 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_AURA_REMOVE;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 60947;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FEAR;
	}

	//Warlock Shadowflame 
	sp = dbcSpell.LookupEntryForced( 47897 );
	//if( sp != NULL )
	{
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[1] = sp->EffectImplicitTargetA[0];
		sp->EffectTriggerSpell[1] = 47960;
	}
	sp = dbcSpell.LookupEntryForced( 61290 );
	//if( sp != NULL )
	{
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[1] = sp->EffectImplicitTargetA[0];
		sp->EffectTriggerSpell[1] = 61291;
	}

	//Warlock Metamorphosis
	sp = dbcSpell.LookupEntryForced( 47241 );
	//if( sp != NULL )
	{
		sp->AuraInterruptFlags &= ~AURA_INTERRUPT_ON_CAST_SPELL;	//some say this happens
		sp->Attributes |= ATTRIBUTES_CANT_CANCEL;	//not sure if this is correct. Description says you can use your seplls but client will try to cancel the aura when you cast a spell
	}
	//Shadow Cleave
	sp = dbcSpell.LookupEntryForced( 50581 );
	//if( sp != NULL )
	{
		SetSpellPowerCoeffsAll(sp,0.55f);	//wowhead said it crit for 2.5k for 3k SP
		sp->maxLevel = PLAYER_LEVEL_CAP_BLIZZLIKE;	//if not then downranking nerfs power to 10%
		sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MAGIC;	//wowhead said it also pierces armor.Crap if it magic then it is intant cast and not on next attack :S
	}

	//Warlock Chaos bolt 
	sp = dbcSpell.LookupEntryForced( 50796 );
	//if( sp != NULL )
	{
		sp->Attributes |= ATTRIBUTES_IGNORE_INVULNERABILITY;
		sp->Effect[0] = SPELL_EFFECT_DUMMY;	//scripting this to avoid absorbtion
		sp->School = 2;
	}
	sp = dbcSpell.LookupEntryForced( 59170 );
	//if( sp != NULL )
	{
		sp->Attributes |= ATTRIBUTES_IGNORE_INVULNERABILITY;
		sp->Effect[0] = SPELL_EFFECT_DUMMY;	//scripting this to avoid absorbtion
		sp->School = 2;
	}		
	sp = dbcSpell.LookupEntryForced( 59171 );
	//if( sp != NULL )
	{
		sp->Attributes |= ATTRIBUTES_IGNORE_INVULNERABILITY;
		sp->Effect[0] = SPELL_EFFECT_DUMMY;	//scripting this to avoid absorbtion
		sp->School = 2;
	}		
	sp = dbcSpell.LookupEntryForced( 59172 );
	//if( sp != NULL )
	{
		sp->Attributes |= ATTRIBUTES_IGNORE_INVULNERABILITY;	
		sp->Effect[0] = SPELL_EFFECT_DUMMY;	//scripting this to avoid absorbtion
		sp->School = 2;
	}
	// End Warlock chaos bolt

	//////////////////////////////////////////
	// DRUID								//
	//////////////////////////////////////////

	// Insert druid spell fixes here
	/* Note: when applying spell hackfixes, please follow a template */
	//Mangle (Cat)
	sp = dbcSpell.LookupEntryForced( 33876 );
	//if(sp != NULL)
		sp->chained_cast = dbcSpell.LookupEntryForced( 34071 );	//award 1 combo pint. Missing since 3.3
	sp = dbcSpell.LookupEntryForced( 33982 );
	//if(sp != NULL)
		sp->chained_cast = dbcSpell.LookupEntryForced( 34071 );	//award 1 combo pint. Missing since 3.3
	sp = dbcSpell.LookupEntryForced( 33983 );
	//if(sp != NULL)
		sp->chained_cast = dbcSpell.LookupEntryForced( 34071 );	//award 1 combo pint. Missing since 3.3
	sp = dbcSpell.LookupEntryForced( 48565 );
	//if(sp != NULL)
		sp->chained_cast = dbcSpell.LookupEntryForced( 34071 );	//award 1 combo pint. Missing since 3.3
	sp = dbcSpell.LookupEntryForced( 48566 );
	//if(sp != NULL)
		sp->chained_cast = dbcSpell.LookupEntryForced( 34071 );	//award 1 combo pint. Missing since 3.3
	//////////////////////////////////////////
	// WARRIOR								//
	//////////////////////////////////////////

	// Insert warrior spell fixes here
		//Shockwave
		sp = dbcSpell.LookupEntryForced( 46968 );
		//if(sp != NULL)
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MELEE;
		//Concussion Blow
		sp = dbcSpell.LookupEntryForced( 12809 );
		//if(sp != NULL)
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MELEE;
		//Thunder Clap
		sp = dbcSpell.LookupEntryForced( 6343 );
		//if(sp != NULL)
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MELEE;
		sp = dbcSpell.LookupEntryForced( 8198 );
		//if(sp != NULL)
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MELEE;
		sp = dbcSpell.LookupEntryForced( 8204 );
		//if(sp != NULL)
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MELEE;
		sp = dbcSpell.LookupEntryForced( 8205 );
		//if(sp != NULL)
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MELEE;
		sp = dbcSpell.LookupEntryForced( 11580 );
		//if(sp != NULL)
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MELEE;
		sp = dbcSpell.LookupEntryForced( 11581 );
		//if(sp != NULL)
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MELEE;
		sp = dbcSpell.LookupEntryForced( 25264 );
		//if(sp != NULL)
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MELEE;
		sp = dbcSpell.LookupEntryForced( 47501 );
		//if(sp != NULL)
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MELEE;
		sp = dbcSpell.LookupEntryForced( 47502 );
		//if(sp != NULL)
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MELEE;
		//Critical Block
		sp = dbcSpell.LookupEntryForced( 47294 );
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_BLOCK_VICTIM;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->EffectTriggerSpell[0] = 47294;	//self proc !
		}
		sp = dbcSpell.LookupEntryForced( 47295 );
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_BLOCK_VICTIM;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->EffectTriggerSpell[0] = 47294;	//self proc !
		}
		sp = dbcSpell.LookupEntryForced( 47296 );
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_BLOCK_VICTIM;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->EffectTriggerSpell[0] = 47294;	//self proc !
		}

		//Damage Shield
		sp = dbcSpell.LookupEntryForced( 58872 );
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_BLOCK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->EffectTriggerSpell[0] = 58872;	//self proc !
		}
		sp = dbcSpell.LookupEntryForced( 58874 );
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_BLOCK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->EffectTriggerSpell[0] = 58872;	//self proc !
		}
		sp = dbcSpell.LookupEntryForced( 59653 );
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_BLOCK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->EffectTriggerSpell[0] = 58872;	//self proc !
		}

		//Sword and Board
		sp = dbcSpell.LookupEntryForced( 46951 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_DEVASTATE;
			sp->ProcOnNameHash[1] = SPELL_HASH_REVENGE;
		}
		sp = dbcSpell.LookupEntryForced( 46952 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_DEVASTATE;
			sp->ProcOnNameHash[1] = SPELL_HASH_REVENGE;
		}
		sp = dbcSpell.LookupEntryForced( 46953 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_DEVASTATE;
			sp->ProcOnNameHash[1] = SPELL_HASH_REVENGE;
		}
		sp = dbcSpell.LookupEntryForced( 50227 );
		//if(sp != NULL)
			sp->Effect[0] = SPELL_EFFECT_DUMMY;

		//Improved Defensive Stance
		sp = dbcSpell.LookupEntryForced( 29593 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_BLOCK_VICTIM | PROC_ON_DODGE_VICTIM;
		sp = dbcSpell.LookupEntryForced( 29594 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_BLOCK_VICTIM | PROC_ON_DODGE_VICTIM;

		//slam
		sp = dbcSpell.LookupEntryForced( 1464 );
		//if(sp != NULL)
		{
			sp->Effect[0] =	SPELL_EFFECT_WEAPON_DAMAGE;
			sp->spell_id_client = 50782;
		}
		sp = dbcSpell.LookupEntryForced( 8820 );
		//if(sp != NULL)
		{
			sp->Effect[0] =	SPELL_EFFECT_WEAPON_DAMAGE;
			sp->spell_id_client = 50782;
		}
		sp = dbcSpell.LookupEntryForced( 11604 );
		//if(sp != NULL)
		{
			sp->Effect[0] =	SPELL_EFFECT_WEAPON_DAMAGE;
			sp->spell_id_client = 50782;
		}
		sp = dbcSpell.LookupEntryForced( 11605 );
		//if(sp != NULL)
		{
			sp->Effect[0] =	SPELL_EFFECT_WEAPON_DAMAGE;
			sp->spell_id_client = 50782;
		}
		sp = dbcSpell.LookupEntryForced( 25241 );
		//if(sp != NULL)
		{
			sp->Effect[0] =	SPELL_EFFECT_WEAPON_DAMAGE;
			sp->spell_id_client = 50782;
		}
		sp = dbcSpell.LookupEntryForced( 25242 );
		//if(sp != NULL)
		{
			sp->Effect[0] =	SPELL_EFFECT_WEAPON_DAMAGE;
			sp->spell_id_client = 50782;
		}
		sp = dbcSpell.LookupEntryForced( 47474 );
		//if(sp != NULL)
		{
			sp->Effect[0] =	SPELL_EFFECT_WEAPON_DAMAGE;
			sp->spell_id_client = 50782;
		}
		sp = dbcSpell.LookupEntryForced( 47475 );
		//if(sp != NULL)
		{
			sp->Effect[0] =	SPELL_EFFECT_WEAPON_DAMAGE;
			sp->spell_id_client = 50782;
		}

		//juggernaut
		sp = dbcSpell.LookupEntryForced( 64976 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CHARGE;
			sp->AttributesEx &= ~1024;
			sp->AttributesEx |= ATTRIBUTES_PASSIVE;
		}
		//Warbringer
		sp = dbcSpell.LookupEntryForced( 57499 );
		//if(sp != NULL)
		{
			sp->AttributesEx &= ~1024;
			sp->AttributesEx |= ATTRIBUTES_PASSIVE;
		}

		// Sword specialization
		sp = dbcSpell.LookupEntryForced(12281);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procChance = 1;
		}
		sp = dbcSpell.LookupEntryForced(13960);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procChance = 1;
		}
		sp = dbcSpell.LookupEntryForced(12812);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procChance = 2;
		}
		sp = dbcSpell.LookupEntryForced(13961);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procChance = 2;
		}
		sp = dbcSpell.LookupEntryForced(12813);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procChance = 3;
		}
		sp = dbcSpell.LookupEntryForced(13962);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procChance = 3;
		}
		sp = dbcSpell.LookupEntryForced(12814);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procChance = 4;
		}
		sp = dbcSpell.LookupEntryForced(13963);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procChance = 4;
		}
		sp = dbcSpell.LookupEntryForced(12815);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procChance = 5;
		}
		sp = dbcSpell.LookupEntryForced(13964);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procChance = 5;
		}

		//Warrior - Rampage
		sp = dbcSpell.LookupEntryForced( 29801 );
		//if(sp != NULL)
			sp->RequiredShapeShift = 0;
		//Warrior - Safeguard
		sp = dbcSpell.LookupEntryForced( 46945 );
		//if(sp != NULL)
		{
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_INTERVENE;
			sp->procFlags = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 46949 );
		//if(sp != NULL)
		{
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_INTERVENE;
			sp->procFlags = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 46946 );
		//if(sp != NULL)
			sp->rangeIndex = 4;	//30 yards
		sp = dbcSpell.LookupEntryForced( 46947 );
		//if(sp != NULL)
			sp->rangeIndex = 4;	//30 yards
		//Warrior - Gag Order
		sp = dbcSpell.LookupEntryForced( 12311 );
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHIELD_BASH;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HEROIC_THROW;
			sp->procFlags = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 12958 );
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHIELD_BASH;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HEROIC_THROW;
			sp->procFlags = PROC_ON_CAST_SPELL;
		}

		//Warrior - Improved Revenge
		sp = dbcSpell.LookupEntryForced( 64382 );
		//if(sp != NULL)
		{
			sp->EffectImplicitTargetB[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;	//or just scripted
			sp->EffectImplicitTargetB[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;	//or just scripted
		}
		sp = dbcSpell.LookupEntryForced( 64380 );
		//if(sp != NULL)
		{
			sp->EffectImplicitTargetB[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;	//or just scripted
			sp->EffectImplicitTargetB[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;	//or just scripted
		}

		//Warrior - Improved Revenge
		sp = dbcSpell.LookupEntryForced( 12797 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_REVENGE;
		}
		sp = dbcSpell.LookupEntryForced( 12799 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_REVENGE;
		}

		//Warrior - Anger Management
		sp = dbcSpell.LookupEntryForced( 12296 );
		//if(sp != NULL)
			sp->EffectBasePoints[0] = 10; //1 rage per 3 seconds. War regen is 3 sec already

		//Warrior - Sudden Death
		sp = dbcSpell.LookupEntryForced( 29723 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 2000;
		}
		sp = dbcSpell.LookupEntryForced( 29724 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 29725 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 52437 );
		//if(sp != NULL)
			sp->procCharges = 0;	//the proc expires on time and not on next hit or cast
		
		//Furious Attacks
		sp = dbcSpell.LookupEntryForced( 46910 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 5000;
		}
		sp = dbcSpell.LookupEntryForced( 46911 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 2000;
		}

		//Warrior - Improved Whirlwind
		sp = dbcSpell.LookupEntryForced( 29721 );
		//if(sp != NULL)
			sp->EffectSpellGroupRelation[0][1] = dbcSpell.LookupEntryForced( 1680 )->SpellGroupType[1];
		sp = dbcSpell.LookupEntryForced( 29776 );
		//if(sp != NULL)
			sp->EffectSpellGroupRelation[0][1] = dbcSpell.LookupEntryForced( 1680 )->SpellGroupType[1];

		//Warrior - Bloodsurge
		sp = dbcSpell.LookupEntryForced( 46913 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_HEROIC_STRIKE;
			sp->ProcOnNameHash[1] = SPELL_HASH_BLOODTHIRST;
			sp->ProcOnNameHash[2] = SPELL_HASH_WHIRLWIND;
		}
		sp = dbcSpell.LookupEntryForced( 46914 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_HEROIC_STRIKE;
			sp->ProcOnNameHash[1] = SPELL_HASH_BLOODTHIRST;
			sp->ProcOnNameHash[2] = SPELL_HASH_WHIRLWIND;
		}
		sp = dbcSpell.LookupEntryForced( 46915 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_HEROIC_STRIKE;
			sp->ProcOnNameHash[1] = SPELL_HASH_BLOODTHIRST;
			sp->ProcOnNameHash[2] = SPELL_HASH_WHIRLWIND;
		}

		//Taste for Blood
		sp = dbcSpell.LookupEntryForced( 56636 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_SPELL_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_REND;
			sp->proc_interval = 7000;
		}
		sp = dbcSpell.LookupEntryForced( 56637 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_SPELL_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_REND;
			sp->proc_interval = 7000;
		}
		sp = dbcSpell.LookupEntryForced( 56638 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_SPELL_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_REND;
			sp->proc_interval = 7000;
		}
		sp = dbcSpell.LookupEntryForced( 60503 );
		//if(sp != NULL)
			sp->AuraInterruptFlags = 0;	//someone said this is getting removed all the time :S

		//Warrior - Enrage Procflags
		sp = dbcSpell.LookupEntryForced( 12317 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
		sp = dbcSpell.LookupEntryForced( 13045 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
		sp = dbcSpell.LookupEntryForced( 13046 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
		sp = dbcSpell.LookupEntryForced( 13047 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
		sp = dbcSpell.LookupEntryForced( 13048 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
		/* Remove the charges only on melee attacks */
		sp = dbcSpell.LookupEntryForced( 12880 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 14201 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 14202 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 14203 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 14204 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_MELEE_ATTACK;

		//Warrior - Blood Craze Procflags
		sp = dbcSpell.LookupEntryForced( 16487 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->proc_interval = 6000;
		}
		sp = dbcSpell.LookupEntryForced( 16489 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->proc_interval = 6000;
		}
		sp = dbcSpell.LookupEntryForced( 16492 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->proc_interval = 6000;
		}
	
		//Warrior - Deep Wounds
		sp = dbcSpell.LookupEntryForced( 12834 );
		//if(sp != NULL)
		{
			sp->EffectTriggerSpell[0] = 12721;
			sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT;
		}
		sp = dbcSpell.LookupEntryForced( 12849 );
		//if(sp != NULL)
		{
			sp->EffectTriggerSpell[0] = 12721;
			sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT;
		}
		sp = dbcSpell.LookupEntryForced( 12867 );
		//if(sp != NULL)
		{
			sp->EffectTriggerSpell[0] = 12721;
			sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT;
		}

		//Warrior - Charge Rank 1
		sp = dbcSpell.LookupEntryForced(100);
		//if(sp != NULL)
		{
			sp->Effect[1] = SPELL_EFFECT_ENERGIZE;
			sp->EffectMiscValue[1] = POWER_TYPE_RAGE;
		}
		//Warrior - Charge Rank 2
		sp = dbcSpell.LookupEntryForced(6178);
		//if(sp != NULL)
		{
			sp->Effect[1] = SPELL_EFFECT_ENERGIZE;
			sp->EffectMiscValue[1] = POWER_TYPE_RAGE;
		}
		//Warrior - Charge Rank 3
		sp = dbcSpell.LookupEntryForced(11578);
		//if(sp != NULL)
		{
			sp->Effect[1] = SPELL_EFFECT_ENERGIZE;		
			sp->EffectMiscValue[1] = POWER_TYPE_RAGE;
		}

		//Warrior - Improved Hamstring Rank 1
		sp = dbcSpell.LookupEntryForced(12289);
		//if(sp != NULL)
		{
			sp->EffectTriggerSpell[1]=23694;// Improved Hamstring : Immobilized. 5 seconds remaining.
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
			sp->ProcOnNameHash[0]= SPELL_HASH_HAMSTRING;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
//			sp->procChance = 5;
		}
		//Warrior - Improved Hamstring Rank 2
		sp = dbcSpell.LookupEntryForced(12668);
		//if(sp != NULL)
		{
			sp->EffectTriggerSpell[1]=23694;// Improved Hamstring : Immobilized. 5 seconds remaining.
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
			sp->ProcOnNameHash[0]= SPELL_HASH_HAMSTRING;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
//			sp->procChance = 10;
		}
		//Warrior - Improved Hamstring Rank 3
		sp = dbcSpell.LookupEntryForced(23695);
		//if(sp != NULL)
		{
			sp->EffectTriggerSpell[1]=23694;// Improved Hamstring : Immobilized. 5 seconds remaining.
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
			sp->ProcOnNameHash[0]= SPELL_HASH_HAMSTRING;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
//			sp->procChance = 15;
		}

		//Warrior - Retaliation
		sp = dbcSpell.LookupEntryForced( 20230 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6; //aura
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 22858; //evil , but this is good for us :D
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM; //add procflag here since this was not processed with the others !
		}

		//"bloodthirst" new version is ok but old version is wrong from now on :(
		sp = dbcSpell.LookupEntryForced( 23881 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64; //cast on us, it is good
			sp->EffectTriggerSpell[1] = 23885; //evil , but this is good for us :D
		}
		sp = dbcSpell.LookupEntryForced( 23892 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64;
			sp->EffectTriggerSpell[1] = 23886; //evil , but this is good for us :D
		}
		sp = dbcSpell.LookupEntryForced( 23893 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64; //
			sp->EffectTriggerSpell[1] = 23887; //evil , but this is good for us :D
		}
		sp = dbcSpell.LookupEntryForced( 23894 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64; //
			sp->EffectTriggerSpell[1] = 23888; //evil , but this is good for us :D
		}
		sp = dbcSpell.LookupEntryForced( 25251 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64; //aura
			sp->EffectTriggerSpell[1] = 25252; //evil , but this is good for us :D
		}
		sp = dbcSpell.LookupEntryForced( 30335 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64; //aura
			sp->EffectTriggerSpell[1] = 30339; //evil , but this is good for us :D
		}
		//rend
		sp = dbcSpell.LookupEntryForced( 772 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//insta dmg part
			sp->EffectBasePoints[1] *= 5; //wtf ?
		}
		sp = dbcSpell.LookupEntryForced( 6546 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//insta dmg part
			sp->EffectBasePoints[1] *= 5; //wtf ?
		}
		sp = dbcSpell.LookupEntryForced( 6547 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//insta dmg part
			sp->EffectBasePoints[1] *= 5; //wtf ?
		}
		sp = dbcSpell.LookupEntryForced( 6548 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//insta dmg part
			sp->EffectBasePoints[1] *= 5; //wtf ?
		}
		sp = dbcSpell.LookupEntryForced( 11572 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//insta dmg part
			sp->EffectBasePoints[1] *= 5; //wtf ?
		}
		sp = dbcSpell.LookupEntryForced( 11573 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//insta dmg part
			sp->EffectBasePoints[1] *= 5; //wtf ?
		}
		sp = dbcSpell.LookupEntryForced( 11574 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//insta dmg part
			sp->EffectBasePoints[1] *= 5; //wtf ?
		}
		sp = dbcSpell.LookupEntryForced( 25208 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//insta dmg part
			sp->EffectBasePoints[1] *= 5; //wtf ?
		}
		sp = dbcSpell.LookupEntryForced( 46845 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//insta dmg part
			sp->EffectBasePoints[1] *= 5; //wtf ?
		}
		sp = dbcSpell.LookupEntryForced( 47465 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//insta dmg part
			sp->EffectBasePoints[1] *= 5; //wtf ?
		}

		//warrior - Rampage
		sp = dbcSpell.LookupEntryForced( 29801 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}

		// Trauma Rank 1
		sp = dbcSpell.LookupEntryForced( 46854 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		// Trauma Rank 2
		sp = dbcSpell.LookupEntryForced( 46855 );
		//if(sp != NULL)
			sp->procFlags = PROC_ON_CRIT_ATTACK;

		//warrior - second wind should trigger on self
		sp = dbcSpell.LookupEntryForced( 29841 );
		//if( sp != NULL )
		{
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 10000;
		}
		sp = dbcSpell.LookupEntryForced( 29842 );
		//if( sp != NULL )
		{
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 10000;
		}

		//warrior - Berserker Rage
		sp = dbcSpell.LookupEntryForced( 18499 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;//Forcing a dummy aura, so we can add the missing 4th effect.
			sp->Effect[1] = 0;
			sp->Effect[2] = 0;
		}

		//warrior - improved berserker rage
		sp = dbcSpell.LookupEntryForced( 20500 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_BERSERKER_RAGE;
		}
		sp = dbcSpell.LookupEntryForced( 20501 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_BERSERKER_RAGE;
		}

		//warrior - Blood Frenzy
		sp = dbcSpell.LookupEntryForced( 29836 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_REND;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_DEEP_WOUND;
		}
		sp = dbcSpell.LookupEntryForced( 29859 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_REND;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_DEEP_WOUND;
		}
		sp = dbcSpell.LookupEntryForced( 30069 );
		//if( sp != NULL )
			sp->DurationIndex = AURA_DURATION_INDEX_10_SECONDS;	//default is infinit
		sp = dbcSpell.LookupEntryForced( 30070 );
		//if( sp != NULL )
			sp->DurationIndex = AURA_DURATION_INDEX_10_SECONDS;	//default is infinit

		//warrior - Unbridled Wrath
		sp = dbcSpell.LookupEntryForced( 12322 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 12999 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 13000 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 13001 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 13002 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}

		// Insert warrior spell fixes here
		// Wrecking Crew Rank 1
		sp = dbcSpell.LookupEntryForced( 46867 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 56611 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 56612 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 56613 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 56614 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		//Warrior - Overpower Rank 1
		sp = dbcSpell.LookupEntryForced(7384);
		//if(sp != NULL)
			sp->Attributes |= ATTRIBUTES_CANT_BE_DPB;
		//Warrior - Overpower Rank 2
		sp = dbcSpell.LookupEntryForced(7887);
		//if(sp != NULL)
			sp->Attributes |= ATTRIBUTES_CANT_BE_DPB;
		//Warrior - Overpower Rank 3
		sp = dbcSpell.LookupEntryForced(11584);
		//if(sp != NULL)
			sp->Attributes |= ATTRIBUTES_CANT_BE_DPB;
		//Warrior - Overpower Rank 4
		sp = dbcSpell.LookupEntryForced(11585);
		//if(sp != NULL)
			sp->Attributes |= ATTRIBUTES_CANT_BE_DPB;
		//Warrior - Tactical Mastery Rank 1
		sp = dbcSpell.LookupEntry(0x00003007);
		//if(sp != NULL)
			sp->RequiredShapeShift = 0x00070000;
		//Warrior - Tactical Mastery Rank 2
		sp = dbcSpell.LookupEntry(0x00003184);
		//if(sp != NULL)
			sp->RequiredShapeShift = 0x00070000;
		//Warrior - Tactical Mastery Rank 3
		sp = dbcSpell.LookupEntry(0x00003185);
		//if(sp != NULL)
			sp->RequiredShapeShift = 0x00070000;
		//Heroic Throw
		sp = dbcSpell.LookupEntryForced( 57755 );
		//if( sp != NULL )
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;
		//Heroic Fury
		sp = dbcSpell.LookupEntryForced( 60970 );
		//if( sp != NULL )
			sp->Effect[0] = SPELL_EFFECT_DUMMY;
		//Shockwave Damage
		sp = dbcSpell.LookupEntryForced( 46968 );
		//if(sp!=NULL)
			SpellEntryEffectSwap(sp,sp,0,1);	//first damage then stun so dmg would not remove stun
		//Ranger: Intervene stop attack
		sp = dbcSpell.LookupEntryForced( 3411 );
		//if( sp != NULL )
			sp->Attributes |= ATTRIBUTES_STOP_ATTACK;

		//////////////////////////////////////////
		// DRUID								//
		//////////////////////////////////////////

		//Feral charge -> spawns an npc ? Remove that
		sp = dbcSpell.LookupEntryForced(49376); 
		if( sp != NULL )
			sp->Effect[1] = SPELL_EFFECT_TELEPORT_UNITS;	

		//Revitalize
		/*
		//when casting REJUVENATION we add a proc aura to the target also to energize him 
		sp = dbcSpell.LookupEntryForced(48539); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_REJUVENATION;
			sp->ProcOnNameHash[1] = SPELL_HASH_WILD_GROWTH;
			sp->EffectTriggerSpell[0] = 48540;
			sp->Effect[1] = SPELL_EFFECT_NULL;	
			sp->procChance = 5;
			sp->proc_interval = 500;
		}
		sp = dbcSpell.LookupEntryForced(48544); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_REJUVENATION;
			sp->ProcOnNameHash[1] = SPELL_HASH_WILD_GROWTH;
			sp->EffectTriggerSpell[0] = 48540;
			sp->Effect[1] = SPELL_EFFECT_NULL;	
			sp->procChance = 25;
			sp->proc_interval = 500;
		}
		sp = dbcSpell.LookupEntryForced(48545); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_REJUVENATION;
			sp->ProcOnNameHash[1] = SPELL_HASH_WILD_GROWTH;
			sp->EffectTriggerSpell[0] = 48540;
			sp->Effect[1] = SPELL_EFFECT_NULL;	
			sp->procChance = 50;
			sp->proc_interval = 500;
		} */
		//the proc for it
		sp = dbcSpell.LookupEntryForced(48542); // -> mana restore spell
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE_MAXPOWER_PCT;	
			sp->EffectMiscValue[1] = 0; // energize mana as pct and not fixed value
		}

		//Wild Growth
		sp = dbcSpell.LookupEntryForced(48438); 
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_CUSTOM_RAID_INRANGE;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->MaxTargets = 5;
			sp->Effect[1] = SPELL_EFFECT_NULL;	
			sp->Effect[2] = SPELL_EFFECT_NULL;	
		}
		sp = dbcSpell.LookupEntryForced(53248); 
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_CUSTOM_RAID_INRANGE;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->MaxTargets = 5;
			sp->Effect[1] = SPELL_EFFECT_NULL;	
			sp->Effect[2] = SPELL_EFFECT_NULL;	
		}
		sp = dbcSpell.LookupEntryForced(53249); 
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_CUSTOM_RAID_INRANGE;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->MaxTargets = 5;
			sp->Effect[1] = SPELL_EFFECT_NULL;	
			sp->Effect[2] = SPELL_EFFECT_NULL;	
		}
		sp = dbcSpell.LookupEntryForced(53251); 
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_CUSTOM_RAID_INRANGE;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->MaxTargets = 5;
			sp->Effect[1] = SPELL_EFFECT_NULL;	
			sp->Effect[2] = SPELL_EFFECT_NULL;	
		}

		//Intensity
		sp = dbcSpell.LookupEntryForced(17106); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_ENRAGE;
		}
		sp = dbcSpell.LookupEntryForced(17107); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_ENRAGE;
		}
		sp = dbcSpell.LookupEntryForced(17108); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_ENRAGE;
		}

		//savage roar -> merge chain spell
		sp = dbcSpell.LookupEntryForced(52610); 
		sp2 = dbcSpell.LookupEntryForced(62071); 
		//if( sp != NULL )
			sp->EffectApplyAuraName[1] = sp2->EffectApplyAuraName[0];

		//Force of Nature
		sp = dbcSpell.LookupEntryForced(33831); 
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_INHERITING_LEVEL;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF; //some land under target is used that gathers multiple targets ...
			sp->EffectImplicitTargetA[1] = EFF_TARGET_NONE;
		}

		// Spell 22570 (Maim Rank 1)
		sp = dbcSpell.LookupEntryForced(22570);
		//if( sp != NULL )
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;

		//////////////////////////////////////////
		// PALADIN								//
		//////////////////////////////////////////

		// Insert paladin spell fixes here

		//Divine Favor
		sp = dbcSpell.LookupEntryForced( 20216 );
		//if( sp != NULL )
		{
			sp->AuraInterruptFlags = AURA_INTERRUPT_ON_CAST_SPELL;
		}

		//Righteous Fury
		sp = dbcSpell.LookupEntryForced( 25780 );
		//if( sp != NULL )
			sp->EffectBasePoints[0] *= 3;	//hackfix to help paladins hold agro

		//Righteous Vengeance
		sp = dbcSpell.LookupEntryForced( 53380 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 61840;
		}
		sp = dbcSpell.LookupEntryForced( 53381 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 61840;
		}
		sp = dbcSpell.LookupEntryForced( 53382 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 61840;
		}
		sp = dbcSpell.LookupEntryForced( 61840 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll( sp, 0.0f );

		//Hammer of the Righteous
		sp = dbcSpell.LookupEntryForced( 53595 );
		//if( sp != NULL )
		{
			sp->EffectChainTarget[ 0 ] = 3;
			SetSpellPowerCoeffsAll( sp, 0.0f );
		}

		//Swift Retribution
		sp = dbcSpell.LookupEntryForced( 53379 );
		//if( sp != NULL )
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_ATTACKSPEED;
		sp = dbcSpell.LookupEntryForced( 53484 );
		//if( sp != NULL )
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_ATTACKSPEED;
		sp = dbcSpell.LookupEntryForced( 53648 );
		//if( sp != NULL )
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_ATTACKSPEED;

		//Forbearance
		sp = dbcSpell.LookupEntryForced( 25771 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
			sp->DispelType = 66666; //this shoud be invalid
			sp->chained_cast = dbcSpell.LookupEntryForced( 61987 );	//Avenging Wrath Marker -> also avoid casting for this spell
		}

		// Divine storm
		sp = dbcSpell.LookupEntryForced( 53385 );
		//if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,2,0);
//			sp->Effect[0] = SPELL_EFFECT_WEAPON_PERCENT_DAMAGE;
//			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
//			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
//			sp->EffectRadiusIndex[0] = SPELL_RADIUS_INDEX_2YARDS;
			sp->Effect[1] = SPELL_EFFECT_HEAL;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectDieSides[1] = -1;
			sp->MaxTargets = 3;
			sp->Effect[2] = SPELL_EFFECT_NULL;
			sp->EffectRadiusIndex[0] = sp->EffectRadiusIndex[2]; //8 yards
			sp->EffectRadiusIndex[1] = sp->EffectRadiusIndex[2]; //8 yards
		}

		// Sacred Shield
		sp = dbcSpell.LookupEntryForced( 53601 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 6000;
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_SACRED_SHIELD;
		}
		sp = dbcSpell.LookupEntryForced( 58597 );
		//if( sp != NULL )
			sp->maxstack = 1;

		// blessing of sanctuary
		sp = dbcSpell.LookupEntryForced( 20911 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_DODGE_VICTIM | PROC_ON_BLOCK_VICTIM;
			sp->procChance = 100;

			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;

			//!!make sure there is no namehash_collision
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND;
			sp->EffectTriggerSpell[1] = 67480;	//strength and stamina

			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[2] = 57319;	//restore mana or some energy
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SINGLE_FRIEND;
			sp->procFlags = PROC_ON_DODGE_VICTIM | PROC_ON_BLOCK_VICTIM;
		}
		//!!make sure there is no namehash_collision
		sp = dbcSpell.LookupEntryForced( 67480 );
		//if( sp != NULL )
		{
			sp->NameHash = SPELL_HASH_BLESSING_OF_SANCTUARY_CUSTOM;
			sp->BGR_one_buff_on_target = 0;
		}

		// greater blessing of sanctuary
		sp = dbcSpell.LookupEntryForced( 25899 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_DODGE_VICTIM | PROC_ON_BLOCK_VICTIM;
			sp->procChance = 100;

			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;

			//!!make sure there is no namehash_collision
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_AREAEFFECT_PARTY_AND_CLASS;
			sp->EffectTriggerSpell[1] = 67480;	//strength and stamina

			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[2] = 57319;	//restore mana or some energy
			sp->EffectImplicitTargetA[2] = EFF_TARGET_AREAEFFECT_PARTY_AND_CLASS;
			sp->procFlags = PROC_ON_DODGE_VICTIM | PROC_ON_BLOCK_VICTIM;
		}
/*		//improved blessing of kings
		sp = dbcSpell.LookupEntryForced( 59295 );
		//if( sp != NULL )
			sp->EffectMiscValue[ 0 ] = SMT_MISC_EFFECT;
		sp = dbcSpell.LookupEntryForced( 59296 );
		//if( sp != NULL )
			sp->EffectMiscValue[ 0 ] = SMT_MISC_EFFECT;
		sp = dbcSpell.LookupEntryForced( 59297 );
		//if( sp != NULL )
			sp->EffectMiscValue[ 0 ] = SMT_MISC_EFFECT;
		sp = dbcSpell.LookupEntryForced( 59298 );
		//if( sp != NULL )
			sp->EffectMiscValue[ 0 ] = SMT_MISC_EFFECT;*/

		//Seals of the Pure
		sp = dbcSpell.LookupEntryForced( 20224 );
		//if( sp != NULL )
		{
			sp->EffectSpellGroupRelation[0][1] |= 536870912;	// Seal of Righteousness
			sp->EffectMiscValue[0] = SMT_MISC_EFFECT;	
			sp->EffectMiscValue[1] = SMT_MISC_EFFECT;	
		}
		sp = dbcSpell.LookupEntryForced( 20225 );
		//if( sp != NULL )
		{
			sp->EffectSpellGroupRelation[0][1] |= 536870912;	// Seal of Righteousness
			sp->EffectMiscValue[0] = SMT_MISC_EFFECT;	
			sp->EffectMiscValue[1] = SMT_MISC_EFFECT;	
		}
		sp = dbcSpell.LookupEntryForced( 20330 );
		//if( sp != NULL )
		{
			sp->EffectSpellGroupRelation[0][1] |= 536870912;	// Seal of Righteousness
			sp->EffectMiscValue[0] = SMT_MISC_EFFECT;	
			sp->EffectMiscValue[1] = SMT_MISC_EFFECT;	
		}
		sp = dbcSpell.LookupEntryForced( 20331 );
		//if( sp != NULL )
		{
			sp->EffectSpellGroupRelation[0][1] |= 536870912;	// Seal of Righteousness
			sp->EffectMiscValue[0] = SMT_MISC_EFFECT;	
			sp->EffectMiscValue[1] = SMT_MISC_EFFECT;	
		}
		sp = dbcSpell.LookupEntryForced( 20332 );
		//if( sp != NULL )
		{
			sp->EffectSpellGroupRelation[0][1] |= 536870912;	// Seal of Righteousness
			sp->EffectMiscValue[0] = SMT_MISC_EFFECT;	
			sp->EffectMiscValue[1] = SMT_MISC_EFFECT;	
		}

		// Holy Shield
		sp = dbcSpell.LookupEntryForced( 20925 ); // -- rank 1
		//if( sp != NULL )
			sp->procFlags = PROC_ON_BLOCK_VICTIM;
		sp = dbcSpell.LookupEntryForced( 20927 ); // -- rank 2
		//if( sp != NULL )
			sp->procFlags = PROC_ON_BLOCK_VICTIM;
		sp = dbcSpell.LookupEntryForced( 20928 ); // -- rank 3
		//if( sp != NULL )
			sp->procFlags = PROC_ON_BLOCK_VICTIM;
		sp = dbcSpell.LookupEntryForced( 27179 ); // -- rank 4
		//if( sp != NULL )
			sp->procFlags = PROC_ON_BLOCK_VICTIM;

		// paladin - Vindication
/*		sp = dbcSpell.LookupEntryForced( 26021 );
		//if( sp != NULL )
		{
			sp->procChance = 30;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		}*/
		sp = dbcSpell.LookupEntryForced( 26016 );
		//if( sp != NULL )
		{
			sp->procChance = 30;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		}
		sp = dbcSpell.LookupEntryForced( 9452 );
		//if( sp != NULL )
		{
			sp->procChance = 30;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		}

		/**********************************************************
		 *	Blessing of Light
		 **********************************************************/
/*		sp = dbcSpell.LookupEntryForced( 19977 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
			sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		}
		sp = dbcSpell.LookupEntryForced( 19978 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
			sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		}
		sp = dbcSpell.LookupEntryForced( 19979 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
			sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		}
		sp = dbcSpell.LookupEntryForced( 27144 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
			sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		}
		sp = dbcSpell.LookupEntryForced( 32770 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
			sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		}*/

		//Seal of Blood
		sp = dbcSpell.LookupEntryForced( 31892 );
		//if( sp != NULL )
		{
			sp->procChance = 100;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 31893;
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SEAL;
			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
			sp->proc_interval = 2000; //avoid spell spam
		}
		sp = dbcSpell.LookupEntryForced( 31893 );
		//if( sp != NULL )
		{
			sp->EffectBasePoints[0] = 21;	//seems like this is fixed 22% acording to description text
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
			sp->Effect[2] = SPELL_EFFECT_NULL;
			sp->fixed_dddhcoef = 0.0f;
		}
		//Seal of the Martyr
		sp = dbcSpell.LookupEntryForced( 53720 );
		//if( sp != NULL )
		{
			sp->procChance = 100;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 53719;
			sp->Effect[1] = SPELL_EFFECT_NULL; 
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SEAL;
			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
			sp->proc_interval = 2000; //avoid spell spam
		}
		sp = dbcSpell.LookupEntryForced( 53719 );
		//if( sp != NULL )
		{
			sp->EffectBasePoints[0] = 21;	//seems like this is fixed 22% acording to description text
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
			sp->Effect[2] = SPELL_EFFECT_NULL;
			sp->fixed_dddhcoef = 0.0f;
		}
		//Seal of Justice
		sp = dbcSpell.LookupEntryForced( 20164 );
		//if( sp != NULL )
		{
			sp->procChance = 25;
			sp->proc_interval = 60000/6;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SEAL;
			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
		}
		// 	Judgement of Justice
		sp = dbcSpell.LookupEntryForced( 53407 );
		sp2 = dbcSpell.LookupEntryForced( 20184 );
		//if( sp != NULL )
		{
			sp->CasterAuraState = 0; //nasty hackfix. Client makes the check for us 
			SpellEntryEffectCopy(sp2,sp,0,1);
			//and set duration too 
			sp2 = dbcSpell.LookupEntryForced( 20185 );
			sp->DurationIndex = sp2->DurationIndex;
			sp->procChance = 40;
		}
		//Seal of Light
		sp = dbcSpell.LookupEntryForced( 20165 );
		//if( sp != NULL )
		{
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SEAL;
			sp->procFlags = PROC_ON_MELEE_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 60;
			sp->proc_interval = 6000;	//some say 30%;
			sp->Effect[1] = SPELL_EFFECT_NULL;
//			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
//			sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;
//			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
			sp->fixed_dddhcoef = 0.0f;
			sp->Spell_value_is_scripted = true;
		}
		sp = dbcSpell.LookupEntryForced( 20167 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_DUEL; // whatever se are sending spell will accept it
			SetAllSpellCoef( sp, 0.00001f);
		}
		// Judgement of Light
		sp = dbcSpell.LookupEntryForced( 20271 );
		//if( sp != NULL )
		{
			sp->procChance = 40;
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
			sp->EffectTriggerSpell[1] = 20267;
			//and set duration too 
			sp2 = dbcSpell.LookupEntryForced( 20185 );
			sp->DurationIndex = sp2->DurationIndex;
			sp->CasterAuraState = 0; //nasty hackfix. Client makes the check for us 
			sp->fixed_dddhcoef = 0.0f;
			sp->Spell_value_is_scripted = true;
		}
		sp = dbcSpell.LookupEntryForced( 20267 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_DUEL; // whatever se are sending spell will accept it
			sp->fixed_dddhcoef = 0.0f;
			sp->Spell_value_is_scripted = true;
		}
		//Seal of Righteousness
		sp = dbcSpell.LookupEntryForced( 21084 );
		//if( sp != NULL )
		{
			sp->spell_can_crit = false;
			sp->procChance = 100;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 500; //second weapon is not procing it
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->EffectTriggerSpell[0] = 25742;
			sp->Effect[1] = SPELL_EFFECT_NULL; 
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SEAL;
			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
			sp->proc_interval = 2000; //avoid spell spam
		}
		sp2 = dbcSpell.LookupEntryForced( 25742 );
		//if( sp != NULL )
		{
			sp2->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;
			sp2->EffectBasePoints[0] = sp->EffectBasePoints[0];
			sp2->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
			sp->fixed_dddhcoef = 0.0f;
		}
		//Seal of Command
		sp = dbcSpell.LookupEntryForced( 20375 );
		//if( sp != NULL )
		{
			sp->spell_can_crit = false;
			sp->procChance = 100;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->EffectTriggerSpell[0] = 20424;
			sp->Effect[1] = SPELL_EFFECT_NULL; 
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SEAL;
			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
			sp->proc_interval = 60000 / 7; //wowwiki says 7 times a minute
//			sp->rangeIndex = 2;	//combat range = 5 yards
			sp->rangeIndex = 96;//2 yards since ppl QQed that 5 is too much
			sp->MaxTargets = 2;	//additional targets
		}
		//ws good from the start
//		sp2 = dbcSpell.LookupEntryForced( 20424 );
		//if( sp != NULL )
//		{
//			sp2->Effect[0] = SPELL_EFFECT_WEAPON_PERCENT_DAMAGE;
//			sp2->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
//		}
		//Seal of Wisdom
		sp = dbcSpell.LookupEntryForced( 20166 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK ;
			sp->proc_interval = 6000;	//some say 30%;
			sp->procChance = 60;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->Effect[1] = SPELL_EFFECT_NULL;
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SEAL;
//			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
//			sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;
//			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 20168 );
		//if( sp != NULL )
			SetAllSpellCoef( sp, 0.00001f);
		// Judgement of Wisdom
		sp = dbcSpell.LookupEntryForced( 53408 );
		//if( sp != NULL )
		{
			sp->procChance = 40;
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
			sp->EffectTriggerSpell[1] = 20268;
			//and set duration too 
			sp2 = dbcSpell.LookupEntryForced( 20186 );
			sp->DurationIndex = sp2->DurationIndex;
			sp->CasterAuraState = 0; //nasty hackfix. Client makes the check for us 
		}
		sp = dbcSpell.LookupEntryForced( 20268 );
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_DUEL; // whatever se are sending spell will accept it
		// Seal of Vengeance
		sp = dbcSpell.LookupEntryForced( 31801 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->EffectTriggerSpell[0] = 31803;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->Effect[1] = SPELL_EFFECT_NULL;
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SEAL;
			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
			sp->proc_interval = 2000; //avoid spell spam
		}
		//avoid boosting already calculated value
		sp = dbcSpell.LookupEntryForced( 31803 );
		//if( sp != NULL )
			sp->fixed_hotdotcoef = 0.0f;
		//Seal of Corruption
		sp = dbcSpell.LookupEntryForced( 53736 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->EffectTriggerSpell[0] = 53742;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->Effect[1] = SPELL_EFFECT_NULL;
			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
            sp->BGR_one_buff_on_target |= SPELL_TYPE_SEAL;
			sp->proc_interval = 2000; //avoid spell spam
		}
		//avoid boosting already calculated value
		sp = dbcSpell.LookupEntryForced( 53742 );
		//if( sp != NULL )
			sp->fixed_hotdotcoef = 0.0f;

		// 	Judgements of the Just
		sp = dbcSpell.LookupEntryForced( 53695 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 68055;
			sp->EffectMiscValue[2] = SMT_DURATION;
			sp->EffectSpellGroupRelation[2][0] = 134217728;	//Seal of Justice
		}
		sp = dbcSpell.LookupEntryForced( 53696 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 68055;
			sp->EffectMiscValue[2] = SMT_DURATION;
			sp->EffectSpellGroupRelation[2][0] = 134217728;	//Seal of Justice
		}
		/**********************************************************
		 * Reckoning
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 20177 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 9000; //avoid proc while it is active
		}
		sp = dbcSpell.LookupEntryForced( 20179 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 9000; //avoid proc while it is active
		}
		sp = dbcSpell.LookupEntryForced( 20180 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 9000; //avoid proc while it is active
		}
		sp = dbcSpell.LookupEntryForced( 20181 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 9000; //avoid proc while it is active
		}
		sp = dbcSpell.LookupEntryForced( 20182 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 9000; //avoid proc while it is active
		}

		/**********************************************************
		 * Reckoning Effect
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 20178 );
		//if( sp != NULL )
		{
			sp->procChance = 100;
			sp->procFlags = PROC_ON_MELEE_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 2000; //avoid proc while it is active
		}
		
		//Infusion of Light
		sp = dbcSpell.LookupEntryForced( 53569 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procFlagsRemove = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_HOLY_SHOCK;
			sp->procCharges = 1;
		}
		sp = dbcSpell.LookupEntryForced( 53576 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_HOLY_SHOCK;
			sp->procFlagsRemove = PROC_ON_CAST_SPELL;
			sp->procCharges = 1;
		}
		//exorcism no extra bonuses pls
		sp = dbcSpell.LookupEntryForced( 879 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll(sp,0.000001f);
		sp = dbcSpell.LookupEntryForced( 5614 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll(sp,0.000001f);
		sp = dbcSpell.LookupEntryForced( 5615 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll(sp,0.000001f);
		sp = dbcSpell.LookupEntryForced( 10312 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll(sp,0.000001f);
		sp = dbcSpell.LookupEntryForced( 10313 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll(sp,0.000001f);
		sp = dbcSpell.LookupEntryForced( 10314 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll(sp,0.000001f);
		sp = dbcSpell.LookupEntryForced( 27138 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll(sp,0.000001f);
		sp = dbcSpell.LookupEntryForced( 48800 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll(sp,0.000001f);
		sp = dbcSpell.LookupEntryForced( 48801 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll(sp,0.000001f);

		//Paladin - Concentration Aura
		sp = dbcSpell.LookupEntryForced( 19746 );
		//if( sp != NULL )
			sp->RequiredShapeShift = 0;

		//Paladin - Guarded by the Light
		sp = dbcSpell.LookupEntryForced( 53583 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 53585 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;

		//Paladin - Ardent Defender
		//Damage that takes you below 35% health is reduced by 20%.  In addition, attacks which would otherwise kill you cause you to be healed by up to 30% of your maximum health (amount healed based on defense).  This healing effect cannot occur more often than once every 2 min.
		sp = dbcSpell.LookupEntryForced( 31850 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
			//effect to save player from death
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 66235;
			//effect to heal player on dmg
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 66233;
			sp->proc_interval = 1;	//all dmg
		}
		sp = dbcSpell.LookupEntryForced( 31851 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
			//effect to save player from death
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 66235;
			//effect to heal player on dmg
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 66233;
			sp->proc_interval = 1;	//all dmg
		}		
		sp = dbcSpell.LookupEntryForced( 31852 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
			//effect to save player from death
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 66235;
			//effect to heal player on dmg
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 66233;
			sp->proc_interval = 1;	//all dmg
		}
		sp = dbcSpell.LookupEntryForced( 66235 );
		//if( sp != NULL )
			sp->spell_id_client = sp->Id;//maybe this way we will see it ?

		//Paladin - Shield of the Templar
		sp = dbcSpell.LookupEntryForced( 53709 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_AVENGER_S_SHIELD;
		}
		sp = dbcSpell.LookupEntryForced( 53710 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_AVENGER_S_SHIELD;
		}
		sp = dbcSpell.LookupEntryForced( 53711 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_AVENGER_S_SHIELD;
		}

		//Paladin - Hand of Reckoning
		sp = dbcSpell.LookupEntryForced( 62124 );
		//if( sp != NULL )
		{
			SetSpellPowerCoeffsAll(sp, 0.0f );
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;	//missing for some reason
		}


		//Paladin - Illumination
		sp = dbcSpell.LookupEntryForced( 20210 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FLASH_OF_LIGHT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HOLY_LIGHT;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_HOLY_SHOCK;
			sp->EffectTriggerSpell[ 0 ] = 20272;	
		}
		sp = dbcSpell.LookupEntryForced( 20212 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FLASH_OF_LIGHT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HOLY_LIGHT;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_HOLY_SHOCK;
			sp->EffectTriggerSpell[ 0 ] = 20272;	
		}
		sp = dbcSpell.LookupEntryForced( 20213 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FLASH_OF_LIGHT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HOLY_LIGHT;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_HOLY_SHOCK;
			sp->EffectTriggerSpell[ 0 ] = 20272;	
		}
		sp = dbcSpell.LookupEntryForced( 20214 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FLASH_OF_LIGHT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HOLY_LIGHT;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_HOLY_SHOCK;
			sp->EffectTriggerSpell[ 0 ] = 20272;	
		}
		sp = dbcSpell.LookupEntryForced( 20215 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FLASH_OF_LIGHT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HOLY_LIGHT;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_HOLY_SHOCK;
			sp->EffectTriggerSpell[ 0 ] = 20272;	
		}

		//Paladin - Sacred Cleansing
		sp = dbcSpell.LookupEntryForced( 53551 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_CLEANSE;
		}
		sp = dbcSpell.LookupEntryForced( 53552 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_CLEANSE;
		}
		sp = dbcSpell.LookupEntryForced( 53553 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_CLEANSE;
		}

		//Paladin - Judgements of the Pure
		sp = dbcSpell.LookupEntryForced( 53671 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 53673 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 54151 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 54154 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 54155 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
		}

		/**********************************************************
		 * Eye for an Eye
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 9799 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 25997;
			sp->fixed_dddhcoef = 0.0f; 
		}
		sp = dbcSpell.LookupEntryForced( 25988 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 25997;
			sp->fixed_dddhcoef = 0.0f; 
		}
		sp = dbcSpell.LookupEntryForced( 25997 );
		//if( sp != NULL )
			sp->fixed_dddhcoef = 0.0f;

		/**********************************************************
		 * Blessed Life
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 31828 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
			sp->EffectTriggerSpell[0] = 31828;	//self proc !
		}
		sp = dbcSpell.LookupEntryForced( 31829 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
			sp->EffectTriggerSpell[0] = 31828;	//self proc !
		}
		sp = dbcSpell.LookupEntryForced( 31830 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
			sp->EffectTriggerSpell[0] = 31828;	//self proc !
		}
		//Paladin - Hammer of Justice - Interrupt effect
		sp = dbcSpell.LookupEntryForced( 853 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 32747;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		}
		sp = dbcSpell.LookupEntryForced( 5588 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 32747;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		}
		sp = dbcSpell.LookupEntryForced( 5589 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 32747;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		}
		sp = dbcSpell.LookupEntryForced( 10308 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 32747;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		}

		/**********************************************************
		 * Light's Grace
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 31833 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HOLY_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 31835 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HOLY_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 31836 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HOLY_LIGHT;
		}

		//paladin - Spiritual Attunement 
		sp = dbcSpell.LookupEntryForced( 31785 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_HEAL_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 31786;
		}
		sp = dbcSpell.LookupEntryForced( 33776 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_LAND_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 31786;
		}

//		sp = dbcSpell.LookupEntryForced( 31895 );
		//if( sp != NULL )
//			sp->procChance = 20;

		// paladin - Holy Guidance
		sp = dbcSpell.LookupEntryForced( 31837 );
		//if( sp != NULL )
			sp->EffectMiscValueB[1] = 3;	//increase healing by intellect
		sp = dbcSpell.LookupEntryForced( 31838 );
		//if( sp != NULL )
			sp->EffectMiscValueB[1] = 3;	//increase healing by intellect
		sp = dbcSpell.LookupEntryForced( 31839 );
		//if( sp != NULL )
			sp->EffectMiscValueB[1] = 3;	//increase healing by intellect
		sp = dbcSpell.LookupEntryForced( 31840 );
		//if( sp != NULL )
			sp->EffectMiscValueB[1] = 3;	//increase healing by intellect
		sp = dbcSpell.LookupEntryForced( 31841 );
		//if( sp != NULL )
			sp->EffectMiscValueB[1] = 3;	//increase healing by intellect

		// paladin - Sanctified Retribution
		sp = dbcSpell.LookupEntryForced( 31869 );
		//if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_2;
			sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
		}

		//Paladin - Improved Lay on Hands
		sp = dbcSpell.LookupEntryForced( 20234 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LAY_ON_HANDS_633;
		}
		sp = dbcSpell.LookupEntryForced( 20235 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LAY_ON_HANDS_633;
		}

		//Paladin - Crusader Strike
		sp = dbcSpell.LookupEntryForced( 35395 );
		//if( sp != NULL )
			sp->noproc = true;

		//Paladin -  Heart of the Crusader
		sp = dbcSpell.LookupEntryForced( 20335 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 21183;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 100;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 20336 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 54498;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 100;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 20337 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 54499;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 100;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
		}

		//Paladin - Judgements of the Wise
		sp = dbcSpell.LookupEntryForced( 31876 );
		//if( sp !=NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectTriggerSpell[0] = 31930;
			sp->proc_interval = 10000;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 31877 );
		//if( sp !=NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectTriggerSpell[0] = 31930;
			sp->proc_interval = 10000;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 31878 );
		//if( sp !=NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectTriggerSpell[0] = 31930;
			sp->proc_interval = 10000;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 57669 );
		//if( sp !=NULL )
		{
			sp->EffectAmplitude[0] = 5000;
			sp->RequiredShapeShift = 0;
		}

		//Paladin - The Art of War
		sp = dbcSpell.LookupEntryForced( 53486 );
		//if( sp !=NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 60000 / 7;
		}
		sp = dbcSpell.LookupEntryForced( 53488 );
		//if( sp !=NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 60000 / 7;
		}
		sp = dbcSpell.LookupEntryForced( 53489 );
		//if( sp !=NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL; //charge removal
			sp->procCharges = 1;
		}
		sp = dbcSpell.LookupEntryForced( 59578 );
		//if( sp !=NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL; //charge removal
			sp->procCharges = 1;
		}

        // Paladin - Improved Devotion Aura
        sp = dbcSpell.LookupEntryForced( 20138 );
        //if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;	//for the armor
			sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_2;	//for the heal
		}
        sp = dbcSpell.LookupEntryForced( 20139 );
        //if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;	//for the armor
			sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_2;	//for the heal
		}
        sp = dbcSpell.LookupEntryForced( 20140 );
        //if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;	//for the armor
			sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_2;	//for the heal
		}

        // Paladin - Devotion Aura
        sp = dbcSpell.LookupEntryForced( 465 );
        //if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HEALING_PCT;
			sp->EffectBasePoints[1] = 0;	//so that Improved Devotion Aura may mod it
		}
        sp = dbcSpell.LookupEntryForced( 10290 );
        //if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HEALING_PCT;
			sp->EffectBasePoints[1] = 0;	//so that Improved Devotion Aura may mod it
		}
        sp = dbcSpell.LookupEntryForced( 643 );
        //if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HEALING_PCT;
			sp->EffectBasePoints[1] = 0;	//so that Improved Devotion Aura may mod it
		}
        sp = dbcSpell.LookupEntryForced( 10291 );
        //if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HEALING_PCT;
			sp->EffectBasePoints[1] = 0;	//so that Improved Devotion Aura may mod it
		}
        sp = dbcSpell.LookupEntryForced( 1032 );
        //if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HEALING_PCT;
			sp->EffectBasePoints[1] = 0;	//so that Improved Devotion Aura may mod it
		}
        sp = dbcSpell.LookupEntryForced( 10292 );
        //if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HEALING_PCT;
			sp->EffectBasePoints[1] = 0;	//so that Improved Devotion Aura may mod it
		}
        sp = dbcSpell.LookupEntryForced( 10293 );
        //if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HEALING_PCT;
			sp->EffectBasePoints[1] = 0;	//so that Improved Devotion Aura may mod it
		}
        sp = dbcSpell.LookupEntryForced( 27149 );
        //if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HEALING_PCT;
			sp->EffectBasePoints[1] = 0;	//so that Improved Devotion Aura may mod it
		}
        sp = dbcSpell.LookupEntryForced( 48941 );
        //if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HEALING_PCT;
			sp->EffectBasePoints[1] = 0;	//so that Improved Devotion Aura may mod it
		}
        sp = dbcSpell.LookupEntryForced( 48942 );
        //if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HEALING_PCT;
			sp->EffectBasePoints[1] = 0;	//so that Improved Devotion Aura may mod it
		}

        // Paladin - Beacon of Light -> Light's Beacon
		// X casts spell on Y that periodically will cast spell on raid members
		// Light's Beacon is checking if players receive a heal spell, if caster is the
        sp = dbcSpell.LookupEntryForced( 53563 );
        //if( sp != NULL )
        {
			//create a copy so we cast it on target just for visual effect
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_FRIEND;
			sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
			sp->EffectTriggerSpell[0] = 53654;	
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 100;
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_FOCUS_MAGIC;
        }

        // Paladin - Sheath of Light
        sp = dbcSpell.LookupEntryForced( 53501 );
        //if( sp != NULL )
        {
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 54203;
			sp->ProcOnNameHash[0] = SPELL_HASH_FLASH_OF_LIGHT;
			sp->ProcOnNameHash[1] = SPELL_HASH_HOLY_LIGHT;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectMiscValue[2] = 126;	// do not mod melee dmg jsut spell dmg
        }
        sp = dbcSpell.LookupEntryForced( 53502 );
        //if( sp != NULL )
        {
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 54203;
			sp->ProcOnNameHash[0] = SPELL_HASH_FLASH_OF_LIGHT;
			sp->ProcOnNameHash[1] = SPELL_HASH_HOLY_LIGHT;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectMiscValue[2] = 126;	// do not mod melee dmg jsut spell dmg
        }
        sp = dbcSpell.LookupEntryForced( 53503 );
        //if( sp != NULL )
        {
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 54203;
			sp->ProcOnNameHash[0] = SPELL_HASH_FLASH_OF_LIGHT;
			sp->ProcOnNameHash[1] = SPELL_HASH_HOLY_LIGHT;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectMiscValue[2] = 126;	// do not mod melee dmg jsut spell dmg
        }

	//////////////////////////////////////////
	// HUNTER								//
	//////////////////////////////////////////

	// Insert hunter spell fixes here
		//freezing arrow
		sp = dbcSpell.LookupEntryForced(60192);
		sp2 = dbcSpell.LookupEntryForced(60202);
		//if(sp != NULL)
		//if(sp != NULL)
			SpellEntryEffectCopy(sp2,sp,0,0);

		//Explosive Shot
		sp = dbcSpell.LookupEntryForced(53301);
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//first tick is instant
		}
		sp = dbcSpell.LookupEntryForced(60051);
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//first tick is instant
		}
		sp = dbcSpell.LookupEntryForced(60052);
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//first tick is instant
		}
		sp = dbcSpell.LookupEntryForced(60053);
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;
			SpellEntryEffectCopy(sp,sp,0,1);
			sp->Effect[1] = SPELL_EFFECT_SCHOOL_DAMAGE;	//first tick is instant
		}

		//lock and load
		sp = dbcSpell.LookupEntryForced(56342);// Lock and Load
		//if(sp != NULL)
		{
			sp->procChance = 33;
			sp->procFlags = PROC_ON_TRAP_TRIGGER;
			sp->proc_interval = 30000;
		}
		sp = dbcSpell.LookupEntryForced(56343);
		//if(sp != NULL)
		{
			sp->procChance = 66;
			sp->procFlags = PROC_ON_TRAP_TRIGGER;
			sp->proc_interval = 30000;
		}
		sp = dbcSpell.LookupEntryForced(56344);
		//if(sp != NULL)
		{
			sp->procChance = 100;
			sp->procFlags = PROC_ON_TRAP_TRIGGER;
			sp->proc_interval = 30000;
		}
		//Piercing Shots
		sp = dbcSpell.LookupEntryForced( 53234 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_AIMED_SHOT;
			sp->ProcOnNameHash[1] = SPELL_HASH_STEADY_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_CHIMERA_SHOT;
			sp->EffectTriggerSpell[0] = 63468;
		}
		sp = dbcSpell.LookupEntryForced( 53237 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_AIMED_SHOT;
			sp->ProcOnNameHash[1] = SPELL_HASH_STEADY_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_CHIMERA_SHOT;
			sp->EffectTriggerSpell[0] = 63468;
		}
		sp = dbcSpell.LookupEntryForced( 53238 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_AIMED_SHOT;
			sp->ProcOnNameHash[1] = SPELL_HASH_STEADY_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_CHIMERA_SHOT;
			sp->EffectTriggerSpell[0] = 63468;
		}

		//Wild quiver rank 1
		sp = dbcSpell.LookupEntryForced( 53215 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_ATTACK;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 53254;
			sp->procChance = 4;
		}

		sp = dbcSpell.LookupEntryForced( 53216 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_ATTACK;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 53254;
			sp->procChance = 7;
		}

		sp = dbcSpell.LookupEntryForced( 53217 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_ATTACK;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 53254;
			sp->procChance = 10;
		}

		// hunter : Deterrence
		sp = dbcSpell.LookupEntryForced( 19263 );
		//if( sp != NULL )
		{
			//as long as parry is diminishing returned this will never have the 100% parry chance effect. We make the player phisical immune ?
			sp->EffectApplyAuraName[1] = SPELL_AURA_SCHOOL_IMMUNITY;
			sp->EffectMiscValue[1] = 1;	//phisical attacks :P
		}

		//hunter : Aspect of the Viper
		sp = dbcSpell.LookupEntryForced( 34074 );
		//if( sp != NULL )
		{
			SpellEntryEffectCopy(sp,sp,0,2);	//duration and targetting
			sp->procFlags = PROC_ON_RANGED_ATTACK | PROC_ON_MELEE_ATTACK;
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[2] = 34075;
		}
		sp = dbcSpell.LookupEntryForced( 34075 );
		//if( sp != NULL )
			sp->spell_id_client = 34074;//maybe this way we will see it ?

		//hunter : Endurance Training
		sp = dbcSpell.LookupEntryForced( 19583 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19584 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19585 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19586 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19587 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}

		//hunter : beast mastery
		sp = dbcSpell.LookupEntryForced( 53270 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_NULL;
			sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		}
		//Hunter : Explosive Trap
		sp = dbcSpell.LookupEntryForced( 13813 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_TRAP_TRIGGER;
			sp->EffectTriggerSpell[1] = 13812;
		}
		sp = dbcSpell.LookupEntryForced( 14316 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_TRAP_TRIGGER;
			sp->EffectTriggerSpell[1] = 14314;
		}
		sp = dbcSpell.LookupEntryForced( 14317 );
		//if( sp != NULL )
		{	
			sp->procFlags = PROC_ON_TRAP_TRIGGER;
			sp->EffectTriggerSpell[1] = 14315;
		}
		sp = dbcSpell.LookupEntryForced( 27025 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_TRAP_TRIGGER;
			sp->EffectTriggerSpell[1] = 27026;
		}
		//Snakes from Snake Trap cast this, shouldn't stack
		sp = dbcSpell.LookupEntryForced( 25810 );
		//if( sp != NULL )
			sp->maxstack = 1;
		sp = dbcSpell.LookupEntryForced( 25809 );
		//if( sp != NULL )
			sp->maxstack = 1;
		//Frost Trap
		sp = dbcSpell.LookupEntryForced( 13809 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_TRAP_TRIGGER;
			sp->EffectTriggerSpell[0] = 13810;
			sp->EffectRadiusIndex[0] = 13;	//10 yards instead 2
		};
		//frost trap spell registered on gameobject_names->sound
		sp = dbcSpell.LookupEntryForced( 63487 );
		//if( sp != NULL )
			sp->EffectRadiusIndex[0] = 13;	//10 yards instead 2
/*		//Hunter - disengage
		sp = dbcSpell.LookupEntryForced( 781 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_KNOCK_BACK;
//			sp->EffectBasePoints[0] = 50; //well not really
//			sp->EffectMiscValue[0] = 300; //nope not good
			sp->EffectBasePoints[0] = 200; //well not really
			sp->EffectMiscValue[0] = 75; //nope not good
		}*/
		//hunter - Sniper Training
		sp = dbcSpell.LookupEntryForced( 53302 );
		//if( sp != NULL )
			sp->EffectTriggerSpell[0] = 64418;	
		sp = dbcSpell.LookupEntryForced( 53303 );
		//if( sp != NULL )
			sp->EffectTriggerSpell[0] = 64419;	
		sp = dbcSpell.LookupEntryForced( 53304 );
		//if( sp != NULL )
			sp->EffectTriggerSpell[0] = 64420;	
//		sp = dbcSpell.LookupEntryForced( 64418 );
		//if( sp != NULL )
//			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_MOVEMENT;
//		sp = dbcSpell.LookupEntryForced( 64419 );
		//if( sp != NULL )
//			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_MOVEMENT;
//		sp = dbcSpell.LookupEntryForced( 64420 );
		//if( sp != NULL )
//			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_MOVEMENT;
		//Hunter - Bestial Wrath
		sp = dbcSpell.LookupEntryForced( 19574 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;	
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_MOVEMENT;
		}
		//Hunter - The Beast Within
		sp = dbcSpell.LookupEntryForced( 34692 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 100;
			sp->EffectTriggerSpell[0] = 34471;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_BESTIAL_WRATH;
		}
		sp = dbcSpell.LookupEntryForced( 34471 );
		//if( sp != NULL )
			sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;

		//Hunter - Go for the Throat
		sp = dbcSpell.LookupEntryForced( 34950 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;
		sp = dbcSpell.LookupEntryForced( 34954 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;
		sp = dbcSpell.LookupEntryForced( 34952 );
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp = dbcSpell.LookupEntryForced( 34953 );
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;

		// hunter - Improved Revive Pet
		sp = dbcSpell.LookupEntryForced( 19575 );
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_NULL;		//!!! this would make some spells gain insane bonuses due to flag collision
		sp = dbcSpell.LookupEntryForced( 24443 );
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_NULL;		//!!! this would make some spells gain insane bonuses due to flag collision
		// Hunter - Improved Wing Clip
		/*sp = dbcSpell.LookupEntryForced( 19228 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPECIFIC_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_WING_CLIP;
		}
		sp = dbcSpell.LookupEntryForced( 19232 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPECIFIC_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_WING_CLIP;
		}
		sp = dbcSpell.LookupEntryForced( 19233 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPECIFIC_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_WING_CLIP;
		}*/

		// Hunter - Master Tactician
		sp = dbcSpell.LookupEntryForced( 34506 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 34507 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 34508 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 34838 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 34839 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}

		// Hunter - Spirit Bond
		sp = dbcSpell.LookupEntryForced( 19578 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 19579;
		}
		sp = dbcSpell.LookupEntryForced( 20895 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 24529;
		}
		sp = dbcSpell.LookupEntryForced( 19579 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA; //we should do the same for player too as we did for pet
			sp->EffectApplyAuraName[1] = sp->EffectApplyAuraName[0];
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
			sp->EffectBasePoints[1] = sp->EffectBasePoints[0];
			sp->EffectAmplitude[1] = sp->EffectAmplitude[0];
			sp->EffectDieSides[1] = sp->EffectDieSides[0];
		}
		sp = dbcSpell.LookupEntryForced( 24529 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA; //we should do the same for player too as we did for pet
			sp->EffectApplyAuraName[1] = sp->EffectApplyAuraName[0];
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
			sp->EffectBasePoints[1] = sp->EffectBasePoints[0];
			sp->EffectAmplitude[1] = sp->EffectAmplitude[0];
			sp->EffectDieSides[1] = sp->EffectDieSides[0];
		}

		//Hunter Silencing Shot
		//http://www.naxxramas.net/bug_list/showreport.php?bugid=234 NTY
		sp = dbcSpell.LookupEntryForced(34490);
		//if(sp != NULL)
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_SILENCE ;
		}

		// Hunter - Serpent's Swiftness
		sp = dbcSpell.LookupEntryForced( 34466 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HASTE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 34467 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HASTE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 34468 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HASTE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 34469 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HASTE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 34470 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HASTE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		}

		// Hunter - Cobra Strikes
		sp = dbcSpell.LookupEntryForced( 53256 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_ARCANE_SHOT;
			sp->ProcOnNameHash[1] = SPELL_HASH_STEADY_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_KILL_SHOT;
		}
		sp = dbcSpell.LookupEntryForced( 53259 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_ARCANE_SHOT;
			sp->ProcOnNameHash[1] = SPELL_HASH_STEADY_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_KILL_SHOT;
		}
		sp = dbcSpell.LookupEntryForced( 53260 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_ARCANE_SHOT;
			sp->ProcOnNameHash[1] = SPELL_HASH_STEADY_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_KILL_SHOT;
		}
		sp = dbcSpell.LookupEntryForced( 53257 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->procCharges = 2;
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		}

		// Hunter - Ferocious Inspiration
		sp = dbcSpell.LookupEntryForced( 34455 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
			sp->Effect[0] = SPELL_EFFECT_FORCE_CAST;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->EffectTriggerSpell[0] = 75593;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT ; //maybe target master ?
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->Effect[1] = 0; //remove this
		}
		sp = dbcSpell.LookupEntryForced( 34459 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
			sp->Effect[0] = SPELL_EFFECT_FORCE_CAST;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->EffectTriggerSpell[0] = 75446;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT ; 
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->Effect[1] = 0; //remove this
		}
		sp = dbcSpell.LookupEntryForced( 34460 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
			sp->Effect[0] = SPELL_EFFECT_FORCE_CAST;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->EffectTriggerSpell[0] = 75447;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->Effect[1] = 0; //remove this
		}
		sp = dbcSpell.LookupEntryForced( 75446 );
		//if( sp != NULL )
			sp->RequiredShapeShift = 0;
		sp = dbcSpell.LookupEntryForced( 75447 );
		//if( sp != NULL )
			sp->RequiredShapeShift = 0;
		sp = dbcSpell.LookupEntryForced( 75593 );
		//if( sp != NULL )
			sp->RequiredShapeShift = 0;

		// Hunter - Focused Fire
		sp = dbcSpell.LookupEntryForced( 35029 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 35060;
//			sp->chained_cast = 35060;	//use this to remove it on aura remove
		}
		sp = dbcSpell.LookupEntryForced( 35030 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 35061;
//			sp->chained_cast = 35060;	//use this to remove it on aura remove
		}
		sp = dbcSpell.LookupEntryForced( 35060 );
		//if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp = dbcSpell.LookupEntryForced( 35061 );
		//if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;

		// Hunter - Thrill of the Hunt
		sp = dbcSpell.LookupEntryForced( 34497 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 34720;
		}
		sp = dbcSpell.LookupEntryForced( 34498 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 34720;
		}
		sp = dbcSpell.LookupEntryForced( 34499 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 34720;
		}

		// Hunter	-	Ferocity
		sp = dbcSpell.LookupEntryForced(19612);
		//if( sp != NULL)
		{
			sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced(19599);
		//if( sp != NULL)
		{
			sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced(19600);
		//if( sp != NULL)
		{
			sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced(19601);
		//if( sp != NULL)
		{
			sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced(19602);
		//if( sp != NULL)
		{
			sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		// Hunter	-	Thick	Hide
		sp = dbcSpell.LookupEntryForced(19609);
		//if( sp != NULL)
		{
			sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_RESISTANCE;
			sp->EffectBasePoints[0]	*= 10;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced(19610);
		//if( sp != NULL)
		{
			sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_RESISTANCE;	
			sp->EffectBasePoints[0]	*= 10;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}

		// Hunter	-	Endurance	Training
/*		sp = dbcSpell.LookupEntryForced(19583);
		//if( sp != NULL)
		{
			sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced(19584);
		//if( sp != NULL)
		{
			sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced(19585);
		//if( sp != NULL)
		{
			sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced(19586);
		//if( sp != NULL)
		{
			sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced(19587);
		//if( sp != NULL)
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}*/
		// Hunter - kill command
		sp = dbcSpell.LookupEntryForced( 34026 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
			sp->EffectMiscValue[0] = 127;	//except fizical ? But pet attacks are mostly abilities = fizical
			sp->EffectBasePoints[0] = 59;	//totally fucked up spell
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		// Hunter - Feign Death
		sp = dbcSpell.LookupEntryForced( 5384 );
		//if( sp != NULL )
			sp->ThreatForSpellCoef = 0;
		// Eagle eye
		sp = dbcSpell.LookupEntryForced( 6197 );
		//if( sp != NULL )
			sp->ThreatForSpellCoef = 0;
		// Hunter - Expose Weakness
		sp = dbcSpell.LookupEntryForced( 34500 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 34502 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 34503 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}

		//Hunter - Frenzy
		sp = dbcSpell.LookupEntryForced( 19621 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 19615;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		}
		sp = dbcSpell.LookupEntryForced( 19622 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 19615;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		}
		sp = dbcSpell.LookupEntryForced( 19623 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 19615;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		}
		sp = dbcSpell.LookupEntryForced( 19624 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 19615;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		}
		sp = dbcSpell.LookupEntryForced( 19625 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 19615;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		}

		//Hunter : Pathfinding
		sp = dbcSpell.LookupEntryForced( 19559 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp = dbcSpell.LookupEntryForced( 19560 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
//		sp = dbcSpell.LookupEntryForced( 5131 );
//		//if( sp != NULL )
			//sp->SpellGroupType[0] = 2097152;
//		sp = dbcSpell.LookupEntryForced( 13160 );
//		//if( sp != NULL )
			//sp->SpellGroupType[0] = 2097152;

		//Hunter : Rapid Killing - might need to add honor trigger too here. I'm guessing you receive Xp too so i'm avoiding double proc
		sp = dbcSpell.LookupEntryForced( 34948 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_GAIN_EXPIERIENCE ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 34949 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_GAIN_EXPIERIENCE ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 35098 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp = dbcSpell.LookupEntryForced( 35099 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;

		//we need to adress this somehow : shot
//		sp = dbcSpell.LookupEntryForced( 3018 );
//		//if( sp != NULL )
			//sp->SpellGroupType[0] = 4;

		//Concussive Barrage
		sp = dbcSpell.LookupEntryForced( 35100 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT | PROC_ON_RANGED_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_CHIMERA_SHOT;
			sp->ProcOnNameHash[1] = SPELL_HASH_MULTI_SHOT;
		}
		sp = dbcSpell.LookupEntryForced( 35102 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT | PROC_ON_RANGED_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_CHIMERA_SHOT;
			sp->ProcOnNameHash[1] = SPELL_HASH_MULTI_SHOT;
		}

		//Hunting Party
		sp = dbcSpell.LookupEntryForced( 53290 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 57669;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_ARCANE_SHOT;
			sp->ProcOnNameHash[1] = SPELL_HASH_EXPLOSIVE_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_STEADY_SHOT;
		}
		sp = dbcSpell.LookupEntryForced( 53291 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 57669;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_ARCANE_SHOT;
			sp->ProcOnNameHash[1] = SPELL_HASH_EXPLOSIVE_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_STEADY_SHOT;
		}
		sp = dbcSpell.LookupEntryForced( 53292 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 57669;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK;
			sp->ProcOnNameHash[0] = SPELL_HASH_ARCANE_SHOT;
			sp->ProcOnNameHash[1] = SPELL_HASH_EXPLOSIVE_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_STEADY_SHOT;
		}

		//hunter : Improved Aspect of the Monkey 
		//wow dragonhawk does not have a dodge effect at all ? so how can we mod that ?
		sp = dbcSpell.LookupEntryForced( 19549 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp = dbcSpell.LookupEntryForced( 19550 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp = dbcSpell.LookupEntryForced( 19551 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;

		//Hunter - Aspect of the Dragonhawk
	/*	sp = dbcSpell.LookupEntryForced( 61846 );
		sp2 = dbcSpell.LookupEntryForced( 61848 );
		//if( sp != NULL && sp2 != NULL)
		{
			SpellEntryEffectCopy(sp2,sp,0,1);
			sp->SpellGroupType[0] |= sp2->SpellGroupType[0];
			sp->SpellGroupType[1] |= sp2->SpellGroupType[1];
			sp->SpellGroupType[2] |= sp2->SpellGroupType[2];
		}
		sp = dbcSpell.LookupEntryForced( 61847 );
		//if( sp != NULL && sp2 != NULL)
		{
			SpellEntryEffectCopy(sp2,sp,0,1);
			sp->SpellGroupType[0] |= sp2->SpellGroupType[0];
			sp->SpellGroupType[1] |= sp2->SpellGroupType[1];
			sp->SpellGroupType[2] |= sp2->SpellGroupType[2];
		}*/
		sp = dbcSpell.LookupEntryForced( 61846 );
		//if( sp != NULL && sp2 != NULL)
			sp->chained_cast = dbcSpell.LookupEntryForced( 61848 );
		sp = dbcSpell.LookupEntryForced( 61847 );
		//if( sp != NULL && sp2 != NULL)
			sp->chained_cast = dbcSpell.LookupEntryForced( 61848 );
		sp = dbcSpell.LookupEntryForced( 61848 );
		//if( sp != NULL && sp2 != NULL)
		{
			sp->BGR_one_buff_on_target = 0;	//allow it to be cast with 61846 or 61847
			sp->maxstack = 1;
		}

		//hunter : Aspect Mastery
		sp = dbcSpell.LookupEntryForced( 53265 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_OVERRIDE_CLASS_SCRIPTS;		//mod my balls
//			sp->Effect[1] = SPELL_EFFECT_NULL;	- keep it for visual ?
//			sp->Effect[2] = SPELL_EFFECT_NULL;	- keep it for visual ?
		}

		//hunter : Unleashed Fury
		sp = dbcSpell.LookupEntryForced( 19616 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;		//mod my balls
			sp->EffectMiscValue[0] = 127;	// all or jsut phisical ?
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19617 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;		//mod my balls
			sp->EffectMiscValue[0] = 127;	// all or jsut phisical ?
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19618 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;		//mod my balls
			sp->EffectMiscValue[0] = 127;	// all or jsut phisical ?
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19619 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;		//mod my balls
			sp->EffectMiscValue[0] = 127;	// all or jsut phisical ?
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19620 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;		//mod my balls
			sp->EffectMiscValue[0] = 127;	// all or jsut phisical ?
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}

		//hunter : Ferocity
		sp = dbcSpell.LookupEntryForced( 19598 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;		//mod my balls
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19599 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;		//mod my balls
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19600 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;		//mod my balls
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19601 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;		//mod my balls
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}
		sp = dbcSpell.LookupEntryForced( 19602 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;		//mod my balls
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		}

		//hunter : Kindred Spirits
		sp = dbcSpell.LookupEntryForced( 56314 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_FORCE_CAST;
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->EffectTriggerSpell[0]=57447;
//			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_INCREASE_SPEED;
//			sp->EffectImplicitTargetB[1]= EFF_TARGET_PET;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[1]= EFF_TARGET_SELF;
			sp->EffectTriggerSpell[1]=57485;	//speed self
		}
		sp = dbcSpell.LookupEntryForced( 56315 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_FORCE_CAST;
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->EffectTriggerSpell[0]=57452;
//			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_INCREASE_SPEED;
//			sp->EffectImplicitTargetB[1]= EFF_TARGET_PET;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[1]= EFF_TARGET_SELF;
			sp->EffectTriggerSpell[1]=57484;	//speed self
		}
		sp = dbcSpell.LookupEntryForced( 56316 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_FORCE_CAST;
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->EffectTriggerSpell[0]=57453;
//			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_INCREASE_SPEED;
//			sp->EffectImplicitTargetB[1]= EFF_TARGET_PET;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[1]= EFF_TARGET_SELF;
			sp->EffectTriggerSpell[1]=57483;	//speed self
		}
		sp = dbcSpell.LookupEntryForced( 56317 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_FORCE_CAST;
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->EffectTriggerSpell[0]=57457;
//			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_INCREASE_SPEED;
//			sp->EffectImplicitTargetB[1]= EFF_TARGET_PET;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[1]= EFF_TARGET_SELF;
			sp->EffectTriggerSpell[1]=57482;	//speed self
		}
		sp = dbcSpell.LookupEntryForced( 56318 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_FORCE_CAST;
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->EffectTriggerSpell[0]=57458;	//dmg mod
//			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_INCREASE_SPEED;
//			sp->EffectImplicitTargetB[1]= EFF_TARGET_PET;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[1]= EFF_TARGET_SELF;
			sp->EffectTriggerSpell[1]=57475;	//speed self
		}
		sp = dbcSpell.LookupEntryForced( 57447 );
		//if( sp != NULL )
			sp->maxstack += 1;
		sp = dbcSpell.LookupEntryForced( 57452 );
		//if( sp != NULL )
			sp->maxstack += 1;
		sp = dbcSpell.LookupEntryForced( 57453 );
		//if( sp != NULL )
			sp->maxstack += 1;
		sp = dbcSpell.LookupEntryForced( 57457 );
		//if( sp != NULL )
			sp->maxstack += 1;
		sp = dbcSpell.LookupEntryForced( 57458 );
		//if( sp != NULL )
			sp->maxstack += 1;
		sp = dbcSpell.LookupEntryForced( 57485 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectImplicitTargetB[0]= EFF_TARGET_PET;
			sp->maxstack += 2;
			sp->RequiredShapeShift = 0;
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		}
		sp = dbcSpell.LookupEntryForced( 57484 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectImplicitTargetB[0]= EFF_TARGET_PET;
			sp->maxstack += 2;
			sp->RequiredShapeShift = 0;
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		}
		sp = dbcSpell.LookupEntryForced( 57483 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectImplicitTargetB[0]= EFF_TARGET_PET;
			sp->maxstack += 2;
			sp->RequiredShapeShift = 0;
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		}
		sp = dbcSpell.LookupEntryForced( 57482 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectImplicitTargetB[0]= EFF_TARGET_PET;
			sp->maxstack += 2;
			sp->RequiredShapeShift = 0;
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		}
		sp = dbcSpell.LookupEntryForced( 57475 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectImplicitTargetB[0]= EFF_TARGET_PET;
			sp->maxstack += 2;
			sp->RequiredShapeShift = 0;
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		}

		//hunter : Hunter's Mark
		sp = dbcSpell.LookupEntryForced( 53338 );
		//if( sp != NULL )
			sp->ThreatForSpellCoef = 0.0;

		//hunter : Improved Hunter's Mark
		sp = dbcSpell.LookupEntryForced( 19421 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_2;	
		sp = dbcSpell.LookupEntryForced( 19422 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_2;	
		sp = dbcSpell.LookupEntryForced( 19423 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_2;	

		//hunter : Improved Arcane Shot
		sp = dbcSpell.LookupEntryForced( 19454 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp = dbcSpell.LookupEntryForced( 19455 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp = dbcSpell.LookupEntryForced( 19456 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;

		//hunter : Improved Tracking
		sp = dbcSpell.LookupEntryForced( 52783 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_2;
		sp = dbcSpell.LookupEntryForced( 52785 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_2;
		sp = dbcSpell.LookupEntryForced( 52786 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_2;
		sp = dbcSpell.LookupEntryForced( 52787 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_2;
		sp = dbcSpell.LookupEntryForced( 52788 );
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_2;

		//hunter : Counterattack
		sp = dbcSpell.LookupEntryForced( 19306 );
		//if( sp != NULL )
			sp->EffectHandler = &HandleCounterAttack;
		sp = dbcSpell.LookupEntryForced( 20909 );
		//if( sp != NULL )
			sp->EffectHandler = &HandleCounterAttack;
		sp = dbcSpell.LookupEntryForced( 20910 );
		//if( sp != NULL )
			sp->EffectHandler = &HandleCounterAttack;
		sp = dbcSpell.LookupEntryForced( 27067 );
		//if( sp != NULL )
			sp->EffectHandler = &HandleCounterAttack;
		sp = dbcSpell.LookupEntryForced( 48998 );
		//if( sp != NULL )
			sp->EffectHandler = &HandleCounterAttack;
		sp = dbcSpell.LookupEntryForced( 48999 );
		//if( sp != NULL )
			sp->EffectHandler = &HandleCounterAttack;

		//hunter : Improved Steady Shot
		sp = dbcSpell.LookupEntryForced( 53221 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_STEADY_SHOT;
		}
		sp = dbcSpell.LookupEntryForced( 53222 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_STEADY_SHOT;
		}
		sp = dbcSpell.LookupEntryForced( 53224 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_STEADY_SHOT;
		}

		//hunter : Spirit Bond
		sp = dbcSpell.LookupEntryForced( 19578 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->chained_cast = dbcSpell.LookupEntryForced( 19579 );		//why not copy effect from spell ?
			sp->Effect[0] = SPELL_EFFECT_DUMMY;
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->EffectImplicitTargetA[1]= EFF_TARGET_SELF;
			sp->Effect[1] = SPELL_EFFECT_NULL;
		}
		sp = dbcSpell.LookupEntryForced( 20895 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->chained_cast = dbcSpell.LookupEntryForced( 24529 );		//why not copy effect from spell ?
			sp->Effect[0] = SPELL_EFFECT_DUMMY;
			sp->EffectImplicitTargetA[0]= EFF_TARGET_PET;
			sp->EffectImplicitTargetA[1]= EFF_TARGET_SELF;
			sp->Effect[1] = SPELL_EFFECT_NULL;
		}

		//hunter : Intimidation
		sp = dbcSpell.LookupEntryForced( 7093 );
		//if( sp != NULL )
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;

		//hunter : Animal Handler
		sp = dbcSpell.LookupEntryForced( 34453 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_ATTACK_POWER_PCT;	
			sp->EffectImplicitTargetA[1]= EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 34454 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_ATTACK_POWER_PCT;	
			sp->EffectImplicitTargetA[1]= EFF_TARGET_PET;
		}

		//hunter : Thick Hide
		sp = dbcSpell.LookupEntryForced( 19609 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_RESISTANCE_PCT;	//we do not have defense rating for pets :(
			sp->EffectMiscValue[0] = 1;	//phisical
		}
		sp = dbcSpell.LookupEntryForced( 19610 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_RESISTANCE_PCT;	//we do not have defense rating for pets :(
			sp->EffectMiscValue[0] = 1;	//phisical
		}
		sp = dbcSpell.LookupEntryForced( 19612 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_RESISTANCE_PCT;	//we do not have defense rating for pets :(
			sp->EffectMiscValue[0] = 1;	//phisical
		}

		//hunter : Noxious Stings
		sp = dbcSpell.LookupEntryForced( 53295 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 53295;	//self proc
			sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM;
		}

		//Warlock : Lava Flows
		// and when your Flame Shock is dispelled your spell casting speed is increased by 10% for 6 sec.
		sp = dbcSpell.LookupEntryForced( 51480 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 64694;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM;
			sp->ProcOnNameHash[0] = SPELL_HASH_FLAME_SHOCK;
		}

		sp = dbcSpell.LookupEntryForced( 51481 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 65263;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM;
			sp->ProcOnNameHash[0] = SPELL_HASH_FLAME_SHOCK;
		}

		sp = dbcSpell.LookupEntryForced( 51482 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 65264;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM;
			sp->ProcOnNameHash[0] = SPELL_HASH_FLAME_SHOCK;
		}

		sp = dbcSpell.LookupEntryForced( 53296 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 53295;	//self proc
			sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM;
		}
		sp = dbcSpell.LookupEntryForced( 53297 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 53295;	//self proc
			sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM;
		}

		//hunter : Rapid Recuperation
		sp = dbcSpell.LookupEntryForced( 53228 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 56654;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_RAPID_FIRE;
			sp->ProcOnNameHash[1] = SPELL_HASH_RAPID_KILLING;
			sp->c_is_flags |= SPELL_FLAG_IS_PROC_TRIGGER_PROC;	//rapid killing is a proc
		}
		sp = dbcSpell.LookupEntryForced( 53232 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 58882;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_RAPID_FIRE;
			sp->ProcOnNameHash[1] = SPELL_HASH_RAPID_KILLING;
			sp->c_is_flags |= SPELL_FLAG_IS_PROC_TRIGGER_PROC;	//rapid killing is a proc
		}
		sp = dbcSpell.LookupEntryForced( 58883 );	//this is proc and it is retarded
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE_MAXPOWER_PCT;
			sp->EffectBasePoints[0] = 1;
		}

		//hunter : Improved Aspect of the Hawk
		sp = dbcSpell.LookupEntryForced( 19552 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 6150;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->Effect[1] = SPELL_EFFECT_NULL;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->procChance = sp->EffectBasePoints[0]+1;
		}
		sp = dbcSpell.LookupEntryForced( 19553 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 6150;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->Effect[1] = SPELL_EFFECT_NULL;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->procChance = sp->EffectBasePoints[0]+1;
		}
		sp = dbcSpell.LookupEntryForced( 19554 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 6150;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->Effect[1] = SPELL_EFFECT_NULL;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->procChance = sp->EffectBasePoints[0]+1;
		}
		sp = dbcSpell.LookupEntryForced( 19555 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 6150;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->Effect[1] = SPELL_EFFECT_NULL;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->procChance = sp->EffectBasePoints[0]+1;
		}
		sp = dbcSpell.LookupEntryForced( 19556 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 6150;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->Effect[1] = SPELL_EFFECT_NULL;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->procChance = sp->EffectBasePoints[0]+1;
		}

		//Hunter : Wyvern Sting
		sp = dbcSpell.LookupEntryForced( 19386 );
		//if( sp != NULL )
		{
//			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
//			sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
//			sp->EffectAmplitude[1] = sp->quick_duration_min;
//			sp->EffectTriggerSpell[1] = 24131;
//			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
			sp->aura_remove_cast = dbcSpell.LookupEntryForced( 24131 );
		}
		sp = dbcSpell.LookupEntryForced( 24132 );
		//if( sp != NULL )
		{
//			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
//			sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
//			sp->EffectAmplitude[1] = sp->quick_duration_min;
//			sp->EffectTriggerSpell[1] = 24134;
//			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
			sp->aura_remove_cast = dbcSpell.LookupEntryForced( 24134 );
		}
		sp = dbcSpell.LookupEntryForced( 24133 );
		//if( sp != NULL )
		{
//			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
//			sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
//			sp->EffectAmplitude[1] = sp->quick_duration_min;
//			sp->EffectTriggerSpell[1] = 24135;
//			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
			sp->aura_remove_cast = dbcSpell.LookupEntryForced( 24135 );
		}
		sp = dbcSpell.LookupEntryForced( 27068 );
		//if( sp != NULL )
		{
//			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
//			sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
//			sp->EffectAmplitude[1] = sp->quick_duration_min;
//			sp->EffectTriggerSpell[1] = 27069;
//			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
			sp->aura_remove_cast = dbcSpell.LookupEntryForced( 27069 );
		}
		sp = dbcSpell.LookupEntryForced( 49011 );
		//if( sp != NULL )
		{
//			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
//			sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
//			sp->EffectAmplitude[1] = sp->quick_duration_min;
//			sp->EffectTriggerSpell[1] = 49009;
//			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
			sp->aura_remove_cast = dbcSpell.LookupEntryForced( 49009 );
		}
		sp = dbcSpell.LookupEntryForced( 49012 );
		//if( sp != NULL )
		{
//			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
//			sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
//			sp->EffectAmplitude[1] = sp->quick_duration_min;
//			sp->EffectTriggerSpell[1] = 49010;
//			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
			sp->aura_remove_cast = dbcSpell.LookupEntryForced( 49010 );
		}
		//hunter pet : growl
		sp = dbcSpell.LookupEntryForced( 2649 );
		//if( sp != NULL )
			sp->EffectBasePoints[0] *= 4;	//hackfix to help pet hold agro
		sp = dbcSpell.LookupEntryForced( 14916 );
		//if( sp != NULL )
			sp->EffectBasePoints[0] *= 4;	//hackfix to help pet hold agro
		sp = dbcSpell.LookupEntryForced( 14917 );
		//if( sp != NULL )
			sp->EffectBasePoints[0] *= 4;	//hackfix to help pet hold agro
		sp = dbcSpell.LookupEntryForced( 14918 );
		//if( sp != NULL )
			sp->EffectBasePoints[0] *= 4;	//hackfix to help pet hold agro
		sp = dbcSpell.LookupEntryForced( 14919 );
		//if( sp != NULL )
			sp->EffectBasePoints[0] *= 4;	//hackfix to help pet hold agro
		sp = dbcSpell.LookupEntryForced( 14920 );
		//if( sp != NULL )
			sp->EffectBasePoints[0] *= 4;	//hackfix to help pet hold agro
		sp = dbcSpell.LookupEntryForced( 14921 );
		//if( sp != NULL )
			sp->EffectBasePoints[0] *= 4;	//hackfix to help pet hold agro
		sp = dbcSpell.LookupEntryForced( 27047 );
		//if( sp != NULL )
			sp->EffectBasePoints[0] *= 4;	//hackfix to help pet hold agro
		sp = dbcSpell.LookupEntryForced( 61676 );
		//if( sp != NULL )
			sp->EffectBasePoints[0] *= 4;	//hackfix to help pet hold agro

		//Hunter : Misdirection
		sp = dbcSpell.LookupEntryForced( 34477 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE;
			//this is hack, implement threat redirection
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_THREAT;	//well we are misisng the threath proxy aura :(
			sp->EffectMiscValue[1] = 127;
			sp->EffectBasePoints[1] = -1000;
		}

		//Hunter : Intimidation
		sp = dbcSpell.LookupEntryForced( 19577 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->procCharges = 1;
		}

		//Hunter : Entrapment
		sp = dbcSpell.LookupEntryForced( 19184 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_TRAP_TRIGGER;
		sp = dbcSpell.LookupEntryForced( 19387 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_TRAP_TRIGGER;
		sp = dbcSpell.LookupEntryForced( 19388 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_TRAP_TRIGGER;
		
		/* aspect of the pack - change to AA */
		sp = dbcSpell.LookupEntryForced( 13159 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;

		/* aspect of the cheetah - add proc flags */
		sp = dbcSpell.LookupEntryForced( 5118 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;

	//////////////////////////////////////////
	// ROGUE								//
	//////////////////////////////////////////

	// Insert rogue spell fixes here
		//Gouge
		sp = dbcSpell.LookupEntryForced( 1776);
		//if( sp != NULL )
			sp->FacingCasterFlags = TARGET_FACE_CASTER;

		//improved kick
		sp = dbcSpell.LookupEntryForced( 13754 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_KICK;
		}
		sp = dbcSpell.LookupEntryForced( 13867 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_KICK;
		}

		//Savage Combat
		sp = dbcSpell.LookupEntryForced( 51682 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_INSTANT_POISON;
			sp->ProcOnNameHash[1] = SPELL_HASH_WOUND_POISON;
			sp->ProcOnNameHash[2] = SPELL_HASH_MIND_NUMBING_POISON;
			sp->c_is_flags |= SPELL_FLAG_IS_PROC_TRIGGER_PROC;
		}
		sp = dbcSpell.LookupEntryForced( 58413 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_INSTANT_POISON;
			sp->ProcOnNameHash[1] = SPELL_HASH_WOUND_POISON;
			sp->ProcOnNameHash[2] = SPELL_HASH_MIND_NUMBING_POISON;
			sp->c_is_flags |= SPELL_FLAG_IS_PROC_TRIGGER_PROC;
		}

		//Initiative
		sp = dbcSpell.LookupEntryForced( 13976 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_CHEAP_SHOT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_AMBUSH;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_GARROTE;
		}
		sp = dbcSpell.LookupEntryForced( 13979 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_CHEAP_SHOT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_AMBUSH;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_GARROTE;
		}
		sp = dbcSpell.LookupEntryForced( 13980 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_CHEAP_SHOT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_AMBUSH;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_GARROTE;
		}

		//mutilate should not require facing
		sp = dbcSpell.LookupEntryForced( 1329 );
		//if( sp != NULL )
			sp->FacingCasterFlags &= ~( CASTER_FACE_FACING | CASTER_FACE_FACING_WIDE | CASTER_FACE_FACING_WIDE2 );
		sp = dbcSpell.LookupEntryForced( 34411 );
		//if( sp != NULL )
			sp->FacingCasterFlags &= ~( CASTER_FACE_FACING | CASTER_FACE_FACING_WIDE | CASTER_FACE_FACING_WIDE2 );
		sp = dbcSpell.LookupEntryForced( 34412 );
		//if( sp != NULL )
			sp->FacingCasterFlags &= ~( CASTER_FACE_FACING | CASTER_FACE_FACING_WIDE | CASTER_FACE_FACING_WIDE2 );
		sp = dbcSpell.LookupEntryForced( 34413 );
		//if( sp != NULL )
			sp->FacingCasterFlags &= ~( CASTER_FACE_FACING | CASTER_FACE_FACING_WIDE | CASTER_FACE_FACING_WIDE2 );
		sp = dbcSpell.LookupEntryForced( 48663 );
		//if( sp != NULL )
			sp->FacingCasterFlags &= ~( CASTER_FACE_FACING | CASTER_FACE_FACING_WIDE | CASTER_FACE_FACING_WIDE2 );
		sp = dbcSpell.LookupEntryForced( 48666 );
		//if( sp != NULL )
			sp->FacingCasterFlags &= ~( CASTER_FACE_FACING | CASTER_FACE_FACING_WIDE | CASTER_FACE_FACING_WIDE2 );
		/**********************************************************
		 *	Garrote - this is used? 
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 37066 );
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;

		//stealth is not a chargetspell
		sp = dbcSpell.LookupEntryForced( 1784 );
		//if( sp != NULL )
			sp->procCharges = 0;
		sp = dbcSpell.LookupEntryForced( 1785 );
		//if( sp != NULL )
			sp->procCharges = 0;
		sp = dbcSpell.LookupEntryForced( 1786 );
		//if( sp != NULL )
			sp->procCharges = 0;
		sp = dbcSpell.LookupEntryForced( 1787 );
		//if( sp != NULL )
			sp->procCharges = 0;

		//Cheap Shot
		sp = dbcSpell.LookupEntryForced( 1833 );
		//if( sp != NULL )
		{
			sp->FacingCasterFlags = 0;
			sp->AttributesExB &= ~FLAGS3_REQ_BEHIND_TARGET;
		}

		//rogue - Hunger For Blood
		sp = dbcSpell.LookupEntryForced( 51662 );
		sp2 = dbcSpell.LookupEntryForced( 63848 );
		//if( sp != NULL )
		{
			SpellEntryEffectCopy( sp2, sp, 0, 0 );
			sp->DurationIndex = sp2->DurationIndex;
		}

		//rogue - Unfair Advantage
		sp = dbcSpell.LookupEntryForced( 51672 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_DODGE_VICTIM;
		sp = dbcSpell.LookupEntryForced( 51674 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_DODGE_VICTIM;

		//rogue - Killing Spree
		sp = dbcSpell.LookupEntryForced( 51690 );
		//if( sp != NULL )
		{
			//increase DMG for duration
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;	
			sp->EffectTriggerSpell[0] = 61851;
			//setup teleportation spell
			sp->Effect[1] = SPELL_EFFECT_DUMMY;	
			sp->EffectAmplitude[1] = 500;
			sp->EffectTriggerSpell[1] = 57840;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_LOCATION_TO_SUMMON;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->MaxTargets = 5;
			sp->EffectRadiusIndex[0] = sp->EffectRadiusIndex[1] = sp->EffectRadiusIndex[2] = 13;
			sp->maxstack = 2;	//so that the other effects like bonus dmg can stack with us
		}
		sp = dbcSpell.LookupEntryForced( 61851 );		//the increase dmg spell. why separate ?
		//if( sp != NULL )
		{
			sp->maxstack = 2;	//so that the other effects like periodic trigger can stack with us
			sp->Effect[0] = SPELL_EFFECT_NULL;		//wtf summon effect
			sp->EffectRadiusIndex[0] = sp->EffectRadiusIndex[1] = sp->EffectRadiusIndex[2] = 13;
		}
		//this is killin spree teleportation spell that we are going to attach the 2 melee attack spells
		sp = dbcSpell.LookupEntryForced( 57840 );
		//if( sp != NULL )
		{
			//teleport to the enemy
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			//increase DMG for duration
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;	
			sp->EffectTriggerSpell[1] = 57841;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
			//setup teleportation spell
			sp->Effect[2] = SPELL_EFFECT_TRIGGER_SPELL;	
			sp->EffectTriggerSpell[2] = 57842;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SINGLE_ENEMY;
			sp->EffectRadiusIndex[0] = sp->EffectRadiusIndex[1] = sp->EffectRadiusIndex[2] = 13;
		}
		//we are not accepting the way blizz made this spell. they made : hit + tel + hit -> we : tel + hit + hit
		sp = dbcSpell.LookupEntryForced( 57841 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_NULL;	
			sp->EffectRadiusIndex[0] = sp->EffectRadiusIndex[1] = sp->EffectRadiusIndex[2] = 13;
		}
/*		//rogue - Find Weakness.
		sp = dbcSpell.LookupEntryForced( 31233 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 31239 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 31240 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 31241 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 31242 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;*/

		//rogue - Cloak of Shadows.
		sp = dbcSpell.LookupEntryForced( 31224 ); 
		//if( sp != NULL )
			sp->Effect[1] = SPELL_EFFECT_DUMMY;

		//rogue - Camouflage.
		sp = dbcSpell.LookupEntryForced( 13975 ); 
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_3;
		sp = dbcSpell.LookupEntryForced( 14062 ); 
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_3;
		sp = dbcSpell.LookupEntryForced( 14063 ); 
		//if( sp != NULL )
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_3;
/*		sp = dbcSpell.LookupEntryForced( 14064 ); 
		//if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		}
		sp = dbcSpell.LookupEntryForced( 14065 ); 
		//if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		}*/

		//rogue - Vanish : remove imparing shit
		sp = dbcSpell.LookupEntryForced( 1856 );
		//if( sp != NULL )
		{
			sp->Effect[1] =  SPELL_EFFECT_DUMMY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 1857 );
		//if( sp != NULL )
		{
			sp->Effect[1] =  SPELL_EFFECT_DUMMY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 26889 );
		//if( sp != NULL )
		{
			sp->Effect[1] =  SPELL_EFFECT_DUMMY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		}

		// rogue - shadowstep
//		sp = dbcSpell.LookupEntryForced( 36554 );
//		//if( sp != NULL )
//			sp->AttributesEx |= ATTRIBUTESEX_NOT_BREAK_STEALTH;

		//rogue - Honor Among Thieves
		sp = dbcSpell.LookupEntryForced( 51698 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK;
			sp->proc_interval = 1000;
		}
		sp = dbcSpell.LookupEntryForced( 51700 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK;
			sp->proc_interval = 1000;
		}
		sp = dbcSpell.LookupEntryForced( 51701 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK;
			sp->proc_interval = 1000;
		}

		//rogue - Cheat Death
		sp = dbcSpell.LookupEntryForced( 31228 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
			sp->proc_interval = 1;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 31228;	//!!self proc
		}
		sp = dbcSpell.LookupEntryForced( 31229 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
			sp->proc_interval = 1;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 31228;	//!!self proc
		}
		sp = dbcSpell.LookupEntryForced( 31230 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
			sp->proc_interval = 1;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 31228;	//!!self proc
		}

		// rogue - Blind (Make it able to miss!)
		sp = dbcSpell.LookupEntryForced( 2094 );
		//if( sp != NULL )
		{
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_RANGED;
			sp->is_ranged_spell = true; 
		}
		//rogue - Waylay.
		sp = dbcSpell.LookupEntryForced( 51692 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT;
			sp->ProcOnNameHash[0] = SPELL_HASH_AMBUSH;
		}
		sp = dbcSpell.LookupEntryForced( 51696 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT ;
			sp->ProcOnNameHash[0] = SPELL_HASH_AMBUSH;
		}
		//rogue - Master of Subtlety
		sp = dbcSpell.LookupEntryForced( 31221 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_AURA_REMOVE;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_STEALTH;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 31665;
			sp->Attributes &= ~ATTRIBUTES_REQ_STEALTH;
		}
		sp = dbcSpell.LookupEntryForced( 31222 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_AURA_REMOVE;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_STEALTH;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 31665;
			sp->Attributes &= ~ATTRIBUTES_REQ_STEALTH;
		}
		sp = dbcSpell.LookupEntryForced( 31223 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_AURA_REMOVE;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_STEALTH;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 31665;
			sp->Attributes &= ~ATTRIBUTES_REQ_STEALTH;
		}
		//rogue - Shadowstep
		sp = dbcSpell.LookupEntryForced( 36563 ); 
		//if( sp != NULL )
		{
			sp->EffectMiscValue[2] = SMT_ADD_TO_EFFECT_VALUE_3;
//			sp->EffectTriggerSpell[1] = 36554;
//			sp->EffectTriggerSpell[2] = 44373;
//			sp->procFlags = PROC_ON_CAST_SPELL;	
		}
		// Still related to shadowstep - prevent the trigger spells from breaking stealth.
		sp = dbcSpell.LookupEntryForced( 44373 );
		//if( sp )
			sp->AttributesEx |= ATTRIBUTESEX_NOT_BREAK_STEALTH;
		sp = dbcSpell.LookupEntryForced( 36563 );
		//if( sp )
			sp->AttributesEx |= ATTRIBUTESEX_NOT_BREAK_STEALTH;
		sp = dbcSpell.LookupEntryForced( 36554 );
		//if( sp != NULL )
			sp->AttributesEx |= ATTRIBUTESEX_NOT_BREAK_STEALTH;

		//Deadly Brew
		sp = dbcSpell.LookupEntryForced( 51625 );
		//if( sp != NULL ) 
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 3409;	//cripling poison
			sp->procFlags = PROC_ON_CAST_SPELL;	//proc on proc might fail ?
			sp->ProcOnNameHash[0] = SPELL_HASH_INSTANT_POISON;
			sp->ProcOnNameHash[1] = SPELL_HASH_WOUND_POISON;
			sp->ProcOnNameHash[2] = SPELL_HASH_MIND_NUMBING_POISON;
		}
		sp = dbcSpell.LookupEntryForced( 51626 );
		//if( sp != NULL ) 
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 3409;	//cripling poison
			sp->procFlags = PROC_ON_CAST_SPELL;	//proc on proc might fail ?
			sp->ProcOnNameHash[0] = SPELL_HASH_INSTANT_POISON;
			sp->ProcOnNameHash[1] = SPELL_HASH_WOUND_POISON;
			sp->ProcOnNameHash[2] = SPELL_HASH_MIND_NUMBING_POISON;
		}

		//rogue - Overkill
		sp = dbcSpell.LookupEntryForced( 58426 );
		//if( sp != NULL ) 
		{
			//some event to start 20 sec countdown on unstealth
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 58427;
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_AURA_REMOVE;
			sp->ProcOnNameHash[0] = SPELL_HASH_STEALTH;
			sp->Attributes &= ~ATTRIBUTES_REQ_STEALTH;
			sp->AttributesEx |= ATTRIBUTESEX_NOT_BREAK_STEALTH;
		}
		sp = dbcSpell.LookupEntryForced( 58427 );
		//if( sp != NULL ) 
		{
			sp->Attributes &= ~ATTRIBUTES_REQ_STEALTH;
			sp->AttributesEx |= ATTRIBUTESEX_NOT_BREAK_STEALTH; 
		}

		//rogue - Seal Fate
		sp = dbcSpell.LookupEntryForced( 14186 );
		//if( sp != NULL ) 
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 14189;
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->procChance = 20;
		}
		sp = dbcSpell.LookupEntryForced( 14190 );
		//if( sp != NULL ) 
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 14189;
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->procChance = 40;
		}
		sp = dbcSpell.LookupEntryForced( 14193 );
		//if( sp != NULL ) 
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 14189;
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->procChance = 60;
		}
		sp = dbcSpell.LookupEntryForced( 14194 );
		//if( sp != NULL ) 
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 14189;
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->procChance = 80;
		}
		sp = dbcSpell.LookupEntryForced( 14195 );
		//if( sp != NULL ) 
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 14189;
			sp->procFlags = PROC_ON_CRIT_ATTACK;
			sp->procChance = 100;
		}
		//Improved Sprint
		sp = dbcSpell.LookupEntryForced( 13743 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SPRINT;
		}
		sp = dbcSpell.LookupEntryForced( 13875 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SPRINT;
		}
		//garrot
		sp = dbcSpell.LookupEntryForced( 703 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 8631 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 8632 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 8633 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 11289 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 11290 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 26839 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 26884 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;

		//rupture
		sp = dbcSpell.LookupEntryForced( 1943 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 8639 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 8640 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 11273 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 11274 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 11275 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 26867 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		//Relentless Strikes
		sp = dbcSpell.LookupEntryForced( 14179 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;//proc spell
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectBasePoints[1] = 4; //client showes 20% chance but whe do not have it ? :O
		}
		sp = dbcSpell.LookupEntryForced( 58422 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;//proc spell
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectBasePoints[1] = 8; //client showes 20% chance but whe do not have it ? :O
		}
		sp = dbcSpell.LookupEntryForced( 58423 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;//proc spell
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectBasePoints[1] = 12; //client showes 20% chance but whe do not have it ? :O
		}
		sp = dbcSpell.LookupEntryForced( 58424 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;//proc spell
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectBasePoints[1] = 16; //client showes 20% chance but whe do not have it ? :O
		}
		sp = dbcSpell.LookupEntryForced( 58425 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;//proc spell
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectBasePoints[1] = 20; //client showes 20% chance but whe do not have it ? :O
		}
		//rogue - intiative
		sp = dbcSpell.LookupEntryForced( 13976 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->ProcOnNameHash[0] = SPELL_HASH_AMBUSH;
			sp->ProcOnNameHash[1] = SPELL_HASH_CHEAP_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_GARROTE;
		}

		//rogue - Glyph of Blurred Speed
		sp = dbcSpell.LookupEntryForced( 58039 );
		//if( sp != NULL )
		{
			sp->Effect[0] =  SPELL_EFFECT_APPLY_AREA_AURA2;
			sp->EffectApplyAuraName[0] = SPELL_AURA_WATER_WALK;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 100;
			sp->ProcOnNameHash[0] = SPELL_HASH_SPRINT;
		}

		sp = dbcSpell.LookupEntryForced( 13979 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->ProcOnNameHash[0] = SPELL_HASH_AMBUSH;
			sp->ProcOnNameHash[1] = SPELL_HASH_CHEAP_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_GARROTE;
		}
		sp = dbcSpell.LookupEntryForced( 13980 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = sp->EffectBasePoints[0]+1;
			sp->ProcOnNameHash[0] = SPELL_HASH_AMBUSH;
			sp->ProcOnNameHash[1] = SPELL_HASH_CHEAP_SHOT;
			sp->ProcOnNameHash[2] = SPELL_HASH_GARROTE;
		}

	//////////////////////////////////////////
	// PRIEST								//
	//////////////////////////////////////////

	// Insert priest spell fixes here

	//Guardian Spirit
	sp = dbcSpell.LookupEntryForced( 48153 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_DIE;
		sp->procChance = 100;
		sp->ProcOnNameHash[0] = SPELL_HASH_GUARDIAN_SPIRIT;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 48153;	
	}

	sp = dbcSpell.LookupEntryForced( 48153 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_HEAL_MAXHEALTH_PCT;
	}

	//Rapture
	sp = dbcSpell.LookupEntryForced( 47535 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_AURA_REMOVE;
		sp->procChance = 100;
		sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 63654;	
		sp->Effect[1] = SPELL_EFFECT_NULL;	//remove this effect. We will force trigger it when target has the shield absorbed
	}
	sp = dbcSpell.LookupEntryForced( 47536 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_AURA_REMOVE;
		sp->procChance = sp->EffectBasePoints[1] + 1;
		sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 63654;	
		sp->Effect[1] = SPELL_EFFECT_NULL;	//remove this effect. We will force trigger it when target has the shield absorbed
	}
	sp = dbcSpell.LookupEntryForced( 47537 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_AURA_REMOVE;
		sp->procChance = sp->EffectBasePoints[1] + 1;
		sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 63654;	
		sp->Effect[1] = SPELL_EFFECT_NULL;	//remove this effect. We will force trigger it when target has the shield absorbed
	}
	sp = dbcSpell.LookupEntryForced( 63654 ); 
	//if( sp != NULL )
		sp->Effect[0] = SPELL_EFFECT_ENERGIZE_MAXPOWER_PCT;

	//Improved Devouring Plague
	sp = dbcSpell.LookupEntryForced( 63625 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 63675;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEVOURING_PLAGUE;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 63626 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 63675;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEVOURING_PLAGUE;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 63627 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 63675;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEVOURING_PLAGUE;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 100;
	}

	//Renewed Hope
	sp = dbcSpell.LookupEntryForced( 57470 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
	}
	sp = dbcSpell.LookupEntryForced( 57472 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
	}

	//Improved Flash Heal -> not blizzlike !
	sp = dbcSpell.LookupEntryForced( 63504 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[ 0 ] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[ 0 ] = SMT_CRITICAL;
	}
	sp = dbcSpell.LookupEntryForced( 63505 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[ 0 ] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[ 0 ] = SMT_CRITICAL;
	}
	sp = dbcSpell.LookupEntryForced( 63506 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[ 0 ] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[ 0 ] = SMT_CRITICAL;
	}

	//Circle of Healing
	sp = dbcSpell.LookupEntryForced( 34861 ); 
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_ALL_RAID;
		sp->EffectImplicitTargetB[ 0 ] = EFF_TARGET_NONE;
		sp->EffectChainTarget[0] = 5;
	}
	sp = dbcSpell.LookupEntryForced( 34863 ); 
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_ALL_RAID;
		sp->EffectImplicitTargetB[ 0 ] = EFF_TARGET_NONE;
		sp->EffectChainTarget[0] = 5;
	}
	sp = dbcSpell.LookupEntryForced( 34864 ); 
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_ALL_RAID;
		sp->EffectImplicitTargetB[ 0 ] = EFF_TARGET_NONE;
		sp->EffectChainTarget[0] = 5;
	}
	sp = dbcSpell.LookupEntryForced( 34865 ); 
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_ALL_RAID;
		sp->EffectImplicitTargetB[ 0 ] = EFF_TARGET_NONE;
		sp->EffectChainTarget[0] = 5;
	}
	sp = dbcSpell.LookupEntryForced( 34866 ); 
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_ALL_RAID;
		sp->EffectImplicitTargetB[ 0 ] = EFF_TARGET_NONE;
		sp->EffectChainTarget[0] = 5;
	}
	sp = dbcSpell.LookupEntryForced( 48088 ); 
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_ALL_RAID;
		sp->EffectImplicitTargetB[ 0 ] = EFF_TARGET_NONE;
		sp->EffectChainTarget[0] = 5;
	}
	sp = dbcSpell.LookupEntryForced( 48089 ); 
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_ALL_RAID;
		sp->EffectImplicitTargetB[ 0 ] = EFF_TARGET_NONE;
		sp->EffectChainTarget[0] = 5;
	}
	//Hymn of Hope
	sp = dbcSpell.LookupEntryForced( 64901 ); 
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_ALL_PARTY_AROUND_CASTER;
		sp->EffectImplicitTargetB[ 0 ] = EFF_TARGET_NONE;
		sp->Effect[ 1 ] = SPELL_EFFECT_NULL;
		sp->AuraInterruptFlags &= ~AURA_INTERRUPT_ON_CAST_SPELL;
		sp->RecoveryTime = 6*60*1000;	//6 minutes ?
	}
	sp = dbcSpell.LookupEntryForced( 64904 ); 
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_SINGLE_FRIEND;
		sp->EffectImplicitTargetB[ 0 ] = EFF_TARGET_NONE;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT;
		sp->EffectMiscValue[1] = 0;
		sp->EffectImplicitTargetA[ 1 ] = EFF_TARGET_SINGLE_FRIEND;
		sp->EffectImplicitTargetB[ 1 ] = EFF_TARGET_NONE;
		sp->maxstack = 1;	//so it will stack with casting spell
	}

	//Weakened Soul
	sp = dbcSpell.LookupEntryForced( 6788 ); 
	//if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
		sp->ThreatForSpellCoef = 0;
	}

	//Vampiric Touch
	sp = dbcSpell.LookupEntryForced( 34914 );	//in 3.2.2 this is scripted effect
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 34919;
		sp->ProcOnNameHash[0] = SPELL_HASH_MIND_BLAST;
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 34916 );	//in 3.2.2 this is scripted effect
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 34919;
		sp->ProcOnNameHash[0] = SPELL_HASH_MIND_BLAST;
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 34917 );	//in 3.2.2 this is scripted effect
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 34919;
		sp->ProcOnNameHash[0] = SPELL_HASH_MIND_BLAST;
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 48159 );	//in 3.2.2 this is scripted effect
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 34919;
		sp->ProcOnNameHash[0] = SPELL_HASH_MIND_BLAST;
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 48160 );	//in 3.2.2 this is scripted effect
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 34919;
		sp->ProcOnNameHash[0] = SPELL_HASH_MIND_BLAST;
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM;
		sp->procChance = 100;
	}
	//the effect itself
	sp = dbcSpell.LookupEntryForced( 34919 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_ENERGIZE_MAXPOWER_PCT;
		sp->EffectBasePoints[0] = 0;	//1% is fixed in description
	}

	// Vampiric Embrace -> make it proc
	sp = dbcSpell.LookupEntryForced( 15286 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 15290;
		sp->procFlags = PROC_ON_SPELL_HIT;
		sp->procChance = 100;
		SetAllSpellCoef(sp,0.0f);
		sp->Spell_value_is_scripted = true;
	}
	sp2 = dbcSpell.LookupEntryForced( 15290 ); 
	//if( sp != NULL )
	{
		sp2->EffectBasePoints[0] = sp->EffectBasePoints[0];
		sp2->EffectImplicitTargetA[ 0 ] = EFF_TARGET_ALL_RAID; // our target party
		sp2->Effect[1] = SPELL_EFFECT_NULL;	//will heall all raid including self with eff 1
		sp2->SpellGroupType[ 0 ] = sp->SpellGroupType[ 0 ];
		sp2->SpellGroupType[ 1 ] = sp->SpellGroupType[ 1 ];
		sp2->SpellGroupType[ 2 ] = sp->SpellGroupType[ 2 ];
		SetAllSpellCoef(sp,0.0f);
		sp->Spell_value_is_scripted = true;
	}

	// Improved Vampiric Embrace
	sp = dbcSpell.LookupEntryForced( 27839 ); 
	//if( sp != NULL )
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;

	// Psychic Horror
	sp = dbcSpell.LookupEntryForced( 64058 ); 
	//if( sp != NULL )
		sp->maxstack = 1;	//so it can stack with trigger mother spell

	//Shadowform
	sp = dbcSpell.LookupEntryForced( 47569 ); 
	//if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE;
	// Improved Shadowform -> make fade remove movement impairing effects
	sp = dbcSpell.LookupEntryForced( 47569 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_FADE;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 15473;
		sp->procChance = 50;
	}
	sp = dbcSpell.LookupEntryForced( 47570 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_FADE;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 15473;
		sp->procChance = 100;
	}

	// Misery
	sp = dbcSpell.LookupEntryForced( 33191 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_SHADOW_WORD__PAIN;
		sp->ProcOnNameHash[1] = SPELL_HASH_MIND_FLAY;
		sp->ProcOnNameHash[2] = SPELL_HASH_VAMPIRIC_TOUCH;
	}
	sp = dbcSpell.LookupEntryForced( 33192 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_SHADOW_WORD__PAIN;
		sp->ProcOnNameHash[1] = SPELL_HASH_MIND_FLAY;
		sp->ProcOnNameHash[2] = SPELL_HASH_VAMPIRIC_TOUCH;
	}
	sp = dbcSpell.LookupEntryForced( 33193 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_SHADOW_WORD__PAIN;
		sp->ProcOnNameHash[1] = SPELL_HASH_MIND_FLAY;
		sp->ProcOnNameHash[2] = SPELL_HASH_VAMPIRIC_TOUCH;
	}

	// Borrowed Time
	sp = dbcSpell.LookupEntryForced( 52795 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectSpellGroupRelation[1][0] = 1; //effect power word shield
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
	}
	sp = dbcSpell.LookupEntryForced( 52797 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectSpellGroupRelation[1][0] = 1; //effect power word shield
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
	}
	sp = dbcSpell.LookupEntryForced( 52798 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectSpellGroupRelation[1][0] = 1; //effect power word shield
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
	}
	sp = dbcSpell.LookupEntryForced( 52799 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectSpellGroupRelation[1][0] = 1; //effect power word shield
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
	}
	sp = dbcSpell.LookupEntryForced( 52800 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectSpellGroupRelation[1][0] = 1; //effect power word shield
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
	}

	// Grace
	sp = dbcSpell.LookupEntryForced( 47516 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_FLASH_HEAL;
		sp->ProcOnNameHash[1] = SPELL_HASH_GREATER_HEAL;
		sp->ProcOnNameHash[2] = SPELL_HASH_PENANCE;
	}
	sp = dbcSpell.LookupEntryForced( 47517 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_FLASH_HEAL;
		sp->ProcOnNameHash[1] = SPELL_HASH_GREATER_HEAL;
		sp->ProcOnNameHash[2] = SPELL_HASH_PENANCE;
	}
	sp = dbcSpell.LookupEntryForced( 47930 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HEALING_PCT; //should receive healing bonus from priest only
		sp->EffectMiscValue[1] = 127;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_DUEL;			 //anything we target
	}

	// Pain and Suffering
	sp = dbcSpell.LookupEntryForced( 47580 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->ProcOnNameHash[0] = SPELL_HASH_MIND_FLAY;
	}
	sp = dbcSpell.LookupEntryForced( 47581 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->ProcOnNameHash[0] = SPELL_HASH_MIND_FLAY;
	}
	sp = dbcSpell.LookupEntryForced( 47582 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->ProcOnNameHash[0] = SPELL_HASH_MIND_FLAY;
	}
	sp = dbcSpell.LookupEntryForced( 47948 ); 
	//if( sp != NULL )
		sp->Effect[0] = SPELL_EFFECT_DUMMY;

	 //priest - Divine Hymn
	 sp = dbcSpell.LookupEntryForced( 64844 );
	 // if( sp != NULL )
	 {
		 sp->MaxTargets = 3;
		 sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
		 sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
		 sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
		 sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
	 }

	 //priest - Holy Concentration
	 sp = dbcSpell.LookupEntryForced( 34753 );
	// //if( sp != NULL )
	 {
		 sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_SPELL_CRIT_HIT_VICTIM;
		 sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FLASH_HEAL;
		 sp->ProcOnNameHash[ 1 ] = SPELL_HASH_BINDING_HEAL;
		 sp->ProcOnNameHash[ 2 ] = SPELL_HASH_GREATER_HEAL;
	 }
	 sp = dbcSpell.LookupEntryForced( 34859 );
	 //if( sp != NULL )
	 {
		 sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_SPELL_CRIT_HIT_VICTIM;
		 sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FLASH_HEAL;
		 sp->ProcOnNameHash[ 1 ] = SPELL_HASH_BINDING_HEAL;
		 sp->ProcOnNameHash[ 2 ] = SPELL_HASH_GREATER_HEAL;
	 }
	 sp = dbcSpell.LookupEntryForced( 34860 );
	 //if( sp != NULL )
	 {
		 sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_SPELL_CRIT_HIT_VICTIM;
		 sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FLASH_HEAL;
		 sp->ProcOnNameHash[ 1 ] = SPELL_HASH_BINDING_HEAL;
		 sp->ProcOnNameHash[ 2 ] = SPELL_HASH_GREATER_HEAL;
	 }
/*	// Test of Faith
	sp = dbcSpell.LookupEntryForced( 47558 ); 
	//if( sp != NULL )
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_HEALING_DONE_PERCENT;
	sp = dbcSpell.LookupEntryForced( 47559 ); 
	//if( sp != NULL )
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_HEALING_DONE_PERCENT;
	sp = dbcSpell.LookupEntryForced( 47560 ); 
	//if( sp != NULL )
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_HEALING_DONE_PERCENT;
		*/

	// Empowered Renew
	sp = dbcSpell.LookupEntryForced( 63534 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_RENEW;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 63544;
	}
	sp = dbcSpell.LookupEntryForced( 63542 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_RENEW;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 63544;
	}
	sp = dbcSpell.LookupEntryForced( 63543 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_RENEW;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 63544;
	}
	sp = dbcSpell.LookupEntryForced( 63544 ); 
	//if( sp != NULL )
		sp->spell_id_client = sp->Id;	//we are sure we want the logs to show us and not original spell id


	// Serendipity
	sp = dbcSpell.LookupEntryForced( 63730 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_BINDING_HEAL;
		sp->ProcOnNameHash[1] = SPELL_HASH_FLASH_HEAL;
	}
	sp = dbcSpell.LookupEntryForced( 63733 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->ProcOnNameHash[0] = SPELL_HASH_BINDING_HEAL;
		sp->ProcOnNameHash[1] = SPELL_HASH_FLASH_HEAL;
	}
	sp = dbcSpell.LookupEntryForced( 63737 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_BINDING_HEAL;
		sp->ProcOnNameHash[1] = SPELL_HASH_FLASH_HEAL;
	}


/*	// Improved Divine Spirit
	sp = dbcSpell.LookupEntryForced( 33174 ); 
	//if( sp != NULL )
		sp->Effect[ 1 ] = SPELL_EFFECT_NULL;
	sp = dbcSpell.LookupEntryForced( 33182 ); 
	//if( sp != NULL )
		sp->Effect[ 1 ] = SPELL_EFFECT_NULL;*/

	// Martyrdom
	sp = dbcSpell.LookupEntryForced( 14531 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 14774 ); 
	//if( sp != NULL )
	{
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM ;
	}

	// Divine Aegis
	sp = dbcSpell.LookupEntryForced( 47509 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp->procChance = 100;
		sp->EffectApplyAuraName[ 0 ] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[ 0 ] = 47753;
	}
	sp = dbcSpell.LookupEntryForced( 47511 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp->procChance = 100;
		sp->EffectApplyAuraName[ 0 ] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[ 0 ] = 47753;
	}
	sp = dbcSpell.LookupEntryForced( 47515 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp->procChance = 100;
		sp->EffectApplyAuraName[ 0 ] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[ 0 ] = 47753;
	}

	// levitate -> just make hover be last move change
	sp = dbcSpell.LookupEntryForced( 1706 ); 
	//if( sp != NULL )
		SpellEntryEffectSwap(sp,sp,1,2);

	//Mind Sear - Effect rank 1
	sp = dbcSpell.LookupEntryForced( 48045 ); 
	//if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 53023 ); 
	//if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
	sp2 = dbcSpell.LookupEntryForced( 49821 ); 
	//if( sp2 != NULL )
	{
		sp2->rangeIndex = sp->rangeIndex;
		sp2->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMY_AT_ENEMY_IN_AREA_CHANNELED;
		sp2->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
	}
	sp2 = dbcSpell.LookupEntryForced( 53022 ); 
	//if( sp2 != NULL )
	{
		sp2->rangeIndex = sp->rangeIndex;
		sp2->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMY_AT_ENEMY_IN_AREA_CHANNELED;
		sp2->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
	}

	//penance 
	sp = dbcSpell.LookupEntryForced( 47540 );
	sp2 = dbcSpell.LookupEntryForced( 47758 );
	//if( sp != NULL && sp2 != NULL )
	{
		sp->DurationIndex = sp2->DurationIndex;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 47666;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
		sp->EffectAmplitude[0] = sp2->EffectAmplitude[1]; //not a bug, eff 0 uses amplitude 1
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 47750;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND;
		sp->EffectAmplitude[1] = sp2->EffectAmplitude[1];
		sp->SpellGroupType[2] = sp2->SpellGroupType[2];
		sp->quick_tickcount = 3;
		sp->quick_ExtendDuration = 1000;
	}
	sp = dbcSpell.LookupEntryForced( 47750 );
	//if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_FRIEND;
	sp = dbcSpell.LookupEntryForced( 53005 );
	sp2 = dbcSpell.LookupEntryForced( 47758 );
	//if( sp != NULL && sp2 != NULL )
	{
		sp->DurationIndex = sp2->DurationIndex;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 52998;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
		sp->EffectAmplitude[0] = sp2->EffectAmplitude[1]; //not a bug, eff 0 uses amplitude 1
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 52983;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND;
		sp->EffectAmplitude[1] = sp2->EffectAmplitude[1];
		sp->SpellGroupType[2] = sp2->SpellGroupType[2];
		sp->quick_tickcount = 3;
		sp->quick_ExtendDuration = 1000;
	}
	sp = dbcSpell.LookupEntryForced( 52983 );
	//if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_FRIEND;
	sp = dbcSpell.LookupEntryForced( 53006 );
	sp2 = dbcSpell.LookupEntryForced( 47758 );
	//if( sp != NULL && sp2 != NULL )
	{
		sp->DurationIndex = sp2->DurationIndex;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 52999;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
		sp->EffectAmplitude[0] = sp2->EffectAmplitude[1]; //not a bug, eff 0 uses amplitude 1
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 52984;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND;
		sp->EffectAmplitude[1] = sp2->EffectAmplitude[1];
		sp->SpellGroupType[2] = sp2->SpellGroupType[2];
		sp->quick_tickcount = 3;
		sp->quick_ExtendDuration = 1000;
	}
	sp = dbcSpell.LookupEntryForced( 52984 );
	//if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_FRIEND;
	sp = dbcSpell.LookupEntryForced( 53007 );
	sp2 = dbcSpell.LookupEntryForced( 47758 );
	//if( sp != NULL && sp2 != NULL )
	{
		sp->DurationIndex = sp2->DurationIndex;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 53000;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
		sp->EffectAmplitude[0] = sp2->EffectAmplitude[1]; //not a bug, eff 0 uses amplitude 1
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 52985;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND;
		sp->EffectAmplitude[1] = sp2->EffectAmplitude[1];
		sp->SpellGroupType[2] = sp2->SpellGroupType[2];
		sp->quick_tickcount = 3;
		sp->quick_ExtendDuration = 1000;
	}
	sp = dbcSpell.LookupEntryForced( 52985 );
	//if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_FRIEND;

		// Prayer of mending. !very very overwriten
		// how it is after rewriten : we simply proc on damage and prochandler will get new target + do healing
		sp = dbcSpell.LookupEntryForced( 33076 );
		//if( sp != NULL )
		{
			//we use this heal spell when we jump to other player
			SpellEntry *healsp = dbcSpell.LookupEntryForced( sp->EffectTriggerSpell[1] );
			if( healsp )
			{
				healsp->Effect[0] = SPELL_EFFECT_HEAL;
				healsp->Effect[1] = healsp->Effect[2] = SPELL_EFFECT_NULL;
				healsp->EffectBasePoints[0] = sp->EffectBasePoints[0];
//				healsp->EffectBaseDice[0] = sp->EffectBaseDice[0];
//				healsp->EffectDicePerLevel[0] = sp->EffectDicePerLevel[0];
				healsp->EffectDieSides[0] = sp->EffectDieSides[0];
				healsp->EffectImplicitTargetA[0] = EFF_TARGET_PARTY_MEMBER;
			}
			//this spell is just to register the proc
			SpellEntry *procsp = dbcSpell.LookupEntryForced( sp->EffectTriggerSpell[0] );
			if( procsp )
			{
				procsp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
				healsp->Effect[1] = healsp->Effect[2] = SPELL_EFFECT_NULL;
				procsp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
				procsp->EffectBasePoints[0] = sp->procCharges - 1; //we loose 1 charge each time we cast so we need this value mobile
				procsp->EffectImplicitTargetA[0] = EFF_TARGET_PARTY_MEMBER; //we jump on an injured party member
				procsp->EffectTriggerSpell[0] = sp->EffectTriggerSpell[1]; //!we proc self but our system does not allow proc loops !
				procsp->procCharges = 1;
				procsp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM ;
				sp->procFlags2 |= PROC2_TARGET_SELF;
			}
			//simplify old system with a simple cast spell
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->Effect[1] = SPELL_EFFECT_NULL;
			sp->Effect[2] = SPELL_EFFECT_NULL;
		}

		// Spirit Tap
		sp = dbcSpell.LookupEntryForced( 15270 ); //rank 1
		//if( sp != NULL )
		{
//			sp->procFlags = PROC_ON_TARGET_DIE;
			sp->procFlags = PROC_ON_GAIN_EXPIERIENCE;
		}
		sp = dbcSpell.LookupEntryForced( 15335 ); //rank 2
		//if( sp != NULL )
		{
//			sp->procFlags = PROC_ON_TARGET_DIE;
			sp->procFlags = PROC_ON_GAIN_EXPIERIENCE;
		}
		sp = dbcSpell.LookupEntryForced( 15336 ); //rank 3
		//if( sp != NULL )
		{
//			sp->procFlags = PROC_ON_TARGET_DIE;
			sp->procFlags = PROC_ON_GAIN_EXPIERIENCE;
		}
		sp = dbcSpell.LookupEntryForced( 15337 ); //rank 4
		//if( sp != NULL )
		{
//			sp->procFlags = PROC_ON_TARGET_DIE;
			sp->procFlags = PROC_ON_GAIN_EXPIERIENCE;
		}
		sp = dbcSpell.LookupEntryForced( 15338 ); //rank 5
		//if( sp != NULL )
		{
//			sp->procFlags = PROC_ON_TARGET_DIE;
			sp->procFlags = PROC_ON_GAIN_EXPIERIENCE;
		}

		/**********************************************************
		 *	Holy Nova
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 15237 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64;
			sp->EffectTriggerSpell[1] = 23455;
		}
		sp = dbcSpell.LookupEntryForced( 15430 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64;
			sp->EffectTriggerSpell[1] = 23458;
		}
		sp = dbcSpell.LookupEntryForced( 15431 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64;
			sp->EffectTriggerSpell[1] = 23459;
		}
		sp = dbcSpell.LookupEntryForced( 27799 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64;
			sp->EffectTriggerSpell[1] = 27803;
		}
		sp = dbcSpell.LookupEntryForced( 27800 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64;
			sp->EffectTriggerSpell[1] = 27804;
		}
		sp = dbcSpell.LookupEntryForced( 27801 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64;
			sp->EffectTriggerSpell[1] = 27805;
		}
		sp = dbcSpell.LookupEntryForced( 25331 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64;
			sp->EffectTriggerSpell[1] = 25329;
		}
		sp = dbcSpell.LookupEntryForced( 48077 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64;
			sp->EffectTriggerSpell[1] = 48075;
		}
		sp = dbcSpell.LookupEntryForced( 48078 );
		//if( sp != NULL )
		{
			sp->Effect[1] = 64;
			sp->EffectTriggerSpell[1] = 48076;
		}

		//Priest: Blessed Recovery
		sp = dbcSpell.LookupEntryForced(27811);
		//if(sp != NULL)
		{
			sp->EffectTriggerSpell[0] = 27813;
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
		}
		sp = dbcSpell.LookupEntryForced(27815);
		//if(sp != NULL)
		{
			sp->EffectTriggerSpell[0] = 27817;
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
		}
		sp = dbcSpell.LookupEntryForced(27816);
		//if(sp != NULL)
		{
			sp->EffectTriggerSpell[0] = 27818;
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
		}
		//priest- Blessed Resilience
		sp = dbcSpell.LookupEntryForced( 33142 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
			sp->procChance = 20;
		}
		sp = dbcSpell.LookupEntryForced( 33145 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
			sp->procChance = 40;
		}
		sp = dbcSpell.LookupEntryForced( 33146 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
			sp->procChance = 60;
		}

		//priest- Focused Will
		sp = dbcSpell.LookupEntryForced( 45234 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
		sp = dbcSpell.LookupEntryForced( 45243 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;
		sp = dbcSpell.LookupEntryForced( 45244 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM;

/*		//Priest: Shadowguard
		sp = dbcSpell.LookupEntryForced( 18137 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->proc_interval = 3000; //every 3 seconds
			sp->EffectTriggerSpell[0] = 28377;
		}
		sp = dbcSpell.LookupEntryForced( 19308 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->proc_interval = 3000; //every 3 seconds
			sp->EffectTriggerSpell[0] = 28378;
		}
		sp = dbcSpell.LookupEntryForced( 19309 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->proc_interval = 3000; //every 3 seconds
			sp->EffectTriggerSpell[0] = 28379;
		}
		sp = dbcSpell.LookupEntryForced( 19310 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->proc_interval = 3000; //every 3 seconds
			sp->EffectTriggerSpell[0] = 28380;
		}
		sp = dbcSpell.LookupEntryForced( 19311 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->proc_interval = 3000; //every 3 seconds
			sp->EffectTriggerSpell[0] = 28381;
		}
		sp = dbcSpell.LookupEntryForced( 19312 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->proc_interval = 3000; //every 3 seconds
			sp->EffectTriggerSpell[0] = 28382;
		}
		sp = dbcSpell.LookupEntryForced( 25477 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->proc_interval = 3000; //every 3 seconds
			sp->EffectTriggerSpell[0] = 28385;
		}*/

		//Priest - Wand Specialization
		sp = dbcSpell.LookupEntryForced( 14524 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		}
		sp = dbcSpell.LookupEntryForced( 14525 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		}
		sp = dbcSpell.LookupEntryForced( 14526 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		}
		sp = dbcSpell.LookupEntryForced( 14527 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		}
		sp = dbcSpell.LookupEntryForced( 14528 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		}

		//priest -  Blackout
/*		sp = dbcSpell.LookupEntryForced( 15268 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 15323 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 15324 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 15325 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 15326 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;*/

		//priest -  Shadow Weaving
		sp = dbcSpell.LookupEntryForced( 15257 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 15258;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 15331 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 15258;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 15332 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 15258;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		}

		//Priest - Inspiration proc spell
		sp = dbcSpell.LookupEntryForced( 14893 );
		//if( sp != NULL )
			sp->rangeIndex = 4;
		sp = dbcSpell.LookupEntryForced( 15357 );
		//if( sp != NULL )
			sp->rangeIndex = 4;
		sp = dbcSpell.LookupEntryForced( 15359 );
		//if( sp != NULL )
			sp->rangeIndex = 4;

		//priest - Body and Soul
		sp = dbcSpell.LookupEntryForced( 64127 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
		}
		sp = dbcSpell.LookupEntryForced( 64129 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
		}
		
		//priest - Dispersion
		sp = dbcSpell.LookupEntryForced( 47585 );
		//if( sp != NULL )
		{
			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[2] = 49766;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
			sp->EffectAmplitude[2] = 1000;
		}

		//priest - surge of light
		sp = dbcSpell.LookupEntryForced( 33150 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procFlagsRemove = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 33154 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procFlagsRemove = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 33151 );
		//if( sp != NULL )
		{
//			sp->AuraInterruptFlags = AURA_INTERRUPT_ON_CAST_SPELL;
			sp->procCharges = 1;
			sp->procFlags = PROC_ON_CAST_SPELL;	//we want to interrupt on specific spell cast not just crits
		}
		// priest - Reflective Shield
		sp = dbcSpell.LookupEntryForced( 33201 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ABSORB;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 33619; //!! WRONG spell, we will make direct dmg here
		}
		sp = dbcSpell.LookupEntryForced( 33202 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ABSORB;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 33619; //!! WRONG spell, we will make direct dmg here
		}


	//////////////////////////////////////////
	// SHAMAN								//
	//////////////////////////////////////////

	// Insert shaman spell fixes here
		//Astral Shift
		sp = dbcSpell.LookupEntryForced( 51474 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_NULL;
			sp->procFlags = PROC_ON_SPELL_LAND_VICTIM;
		}
		sp = dbcSpell.LookupEntryForced( 51478 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_NULL;
			sp->procFlags = PROC_ON_SPELL_LAND_VICTIM;
		}
		sp = dbcSpell.LookupEntryForced( 51479 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_NULL;
			sp->procFlags = PROC_ON_SPELL_LAND_VICTIM;
		}
		sp = dbcSpell.LookupEntryForced( 52179 );		//the proc
		//if( sp != NULL )
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
			
		//Earthen Power
		sp = dbcSpell.LookupEntryForced( 51523 );	
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 59566;
			sp->procChance = sp->EffectBasePoints[1] + 1;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_EARTHBIND_TOTEM;	//not just on cast but all the time ? :(
		}
		sp = dbcSpell.LookupEntryForced( 51524 );	
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 59566;
			sp->procChance = sp->EffectBasePoints[1] + 1;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_EARTHBIND_TOTEM;	//not just on cast but all the time ? :(
		}
		//Frozen Power
		sp = dbcSpell.LookupEntryForced( 63373 );	
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 63685;
			sp->procChance = sp->EffectBasePoints[1] + 1;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_FROST_SHOCK;
		}
		sp = dbcSpell.LookupEntryForced( 63374 );	
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 63685;
			sp->procChance = sp->EffectBasePoints[1] + 1;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_FROST_SHOCK;
		}
		//Grounding Totem Effect
		sp = dbcSpell.LookupEntryForced( 8178 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;				//no need for area aura if totems are spamming spells anyway
			sp->DurationIndex = AURA_DURATION_INDEX_10_SECONDS;		//don't leave an infinit passive aura on targets
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
		}
		//Tremor Totem
		sp = dbcSpell.LookupEntryForced( 8146 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_DUMMY;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->Effect[1] = SPELL_EFFECT_NULL;
			sp->Effect[2] = SPELL_EFFECT_NULL;
		}

		//Mana Spring Totem
		sp = dbcSpell.LookupEntryForced( 52031 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52032;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 52033 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52032;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 52034 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52032;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 52035 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52032;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 52036 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52032;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 58778 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52032;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 58779 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52032;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 58780 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52032;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 52031 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52032;			//according to dbc
		}

		//Healing Stream Totem
		sp = dbcSpell.LookupEntryForced( 52041 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_HEAL;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52042;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 52046 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_HEAL;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52042;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 52047 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_HEAL;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52042;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 52048 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_HEAL;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52042;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 52049 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_HEAL;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52042;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 52050 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_HEAL;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52042;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 58759 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_HEAL;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52042;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 58760 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_HEAL;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52042;			//according to dbc
		}
		sp = dbcSpell.LookupEntryForced( 58761 );	
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_HEAL;
			SetSpellPowerCoeffsAll(sp, 0.08f);
			sp->spell_id_client = 52042;			//according to dbc
		}

		//totem of wrath
		sp = dbcSpell.LookupEntryForced( 57658 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}
		sp = dbcSpell.LookupEntryForced( 57660 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}
		sp = dbcSpell.LookupEntryForced( 57662 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}
		sp = dbcSpell.LookupEntryForced( 57663 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}
		//the effect 2
		sp = dbcSpell.LookupEntryForced( 30708 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->DurationIndex = 3; // 1 minute
		}

		//fire nova ( totem )
		sp = dbcSpell.LookupEntryForced( 1535 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 8349;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 19823;	//only visual fire nova
			sp->c_is_flags |= SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
		}
		sp = dbcSpell.LookupEntryForced( 8349 );
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
		//if( sp != NULL )
		sp = dbcSpell.LookupEntryForced( 8498 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 8502;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 19823;	//only visual fire nova
			sp->c_is_flags |= SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
		}
		sp = dbcSpell.LookupEntryForced( 8502 );
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
		sp = dbcSpell.LookupEntryForced( 8499 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 8503;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 19823;	//only visual fire nova
			sp->c_is_flags |= SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
		}
		sp = dbcSpell.LookupEntryForced( 8503 );
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
		sp = dbcSpell.LookupEntryForced( 11314 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 11306;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 19823;	//only visual fire nova
			sp->c_is_flags |= SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
		}
		sp = dbcSpell.LookupEntryForced( 11306 );
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
		sp = dbcSpell.LookupEntryForced( 11315 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 11307;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 19823;	//only visual fire nova
			sp->c_is_flags |= SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
		}
		sp = dbcSpell.LookupEntryForced( 11307 );
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
		sp = dbcSpell.LookupEntryForced( 25546 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 25535;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 19823;	//only visual fire nova
			sp->c_is_flags |= SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
		}
		sp = dbcSpell.LookupEntryForced( 25535 );
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
		sp = dbcSpell.LookupEntryForced( 25547 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 25537;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 19823;	//only visual fire nova
			sp->c_is_flags |= SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
		}
		sp = dbcSpell.LookupEntryForced( 25537 );
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
		sp = dbcSpell.LookupEntryForced( 61649 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 61650;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 19823;	//only visual fire nova
			sp->c_is_flags |= SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
		}
		sp = dbcSpell.LookupEntryForced( 61650 );
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
		sp = dbcSpell.LookupEntryForced( 61657 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 61654;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME;
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 19823;	//only visual fire nova
			sp->c_is_flags |= SPELL_FLAG_IS_TRIGGERED_BY_TARGET;
		}
		sp = dbcSpell.LookupEntryForced( 61654 );
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;

		//Call of the Elements 
		sp = dbcSpell.LookupEntryForced( 66842 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->Effect[0] = SPELL_EFFECT_DUMMY; //button 132,133,134,135
		}
		//Call of the Ancestors 
		sp = dbcSpell.LookupEntryForced( 66843 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->Effect[0] = SPELL_EFFECT_DUMMY; //button 136,137,138,139
		}
		//Call of the Spirits 
		sp = dbcSpell.LookupEntryForced( 66844 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->Effect[0] = SPELL_EFFECT_DUMMY; //button 140,141,142,143
		}

		//Flametongue totem 
		sp = dbcSpell.LookupEntryForced( 52109 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}
		sp = dbcSpell.LookupEntryForced( 52110 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}
		sp = dbcSpell.LookupEntryForced( 52111 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}
		sp = dbcSpell.LookupEntryForced( 52112 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}
		sp = dbcSpell.LookupEntryForced( 52113 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}
		sp = dbcSpell.LookupEntryForced( 58651 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}
		sp = dbcSpell.LookupEntryForced( 58654 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}
		sp = dbcSpell.LookupEntryForced( 58655 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_RAID;
			sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		}

		//Flametongue Weapon
		sp = dbcSpell.LookupEntryForced( 10444 );	//global visual thingie
		//if( sp != NULL )
			SetSpellPowerCoeffsAll(sp, 0.000001f);
		sp = dbcSpell.LookupEntryForced( 10400 );	//this is enchantment spell
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 8026;	//this is id to proc
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 1000;
		}
		sp = dbcSpell.LookupEntryForced( 8026 );	//stupid dummy effect
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;	// !!! dmg is high because : EffectRealPointsPerLevel
			sp->spell_id_client = 10444;			//according to dbc this does the dmg
			SetSpellPowerCoeffsAll(sp, 0.000001f);
		}

		sp = dbcSpell.LookupEntryForced( 15567 );	//this is enchantment spell
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 8028;	//this is id to proc
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 1000;
		}
		sp = dbcSpell.LookupEntryForced( 8028 );	//stupid dummy effect
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;	// !!! dmg is high because : EffectRealPointsPerLevel
			sp->spell_id_client = 10444;			//according to dbc this does the dmg
			SetSpellPowerCoeffsAll(sp, 0.000001f);
		}
	
		sp = dbcSpell.LookupEntryForced( 15568 );	//this is enchantment spell
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 8029;	//this is id to proc
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 1000;
		}
		sp = dbcSpell.LookupEntryForced( 8029 );	//stupid dummy effect
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;	// !!! dmg is high because : EffectRealPointsPerLevel
			sp->spell_id_client = 10444;			//according to dbc this does the dmg
			SetSpellPowerCoeffsAll(sp, 0.000001f);
		}
	
		sp = dbcSpell.LookupEntryForced( 15569 );	//this is enchantment spell
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 10445;	//this is id to proc
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 1000;
		}
		sp = dbcSpell.LookupEntryForced( 10445 );	//stupid dummy effect
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;	// !!! dmg is high because : EffectRealPointsPerLevel
			sp->spell_id_client = 10444;			//according to dbc this does the dmg
			SetSpellPowerCoeffsAll(sp, 0.000001f);
		}	
	
		sp = dbcSpell.LookupEntryForced( 16311 );	//this is enchantment spell
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 16343;	//this is id to proc
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 1000;
		}
		sp = dbcSpell.LookupEntryForced( 16343 );	//stupid dummy effect
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;	// !!! dmg is high because : EffectRealPointsPerLevel
			sp->spell_id_client = 10444;			//according to dbc this does the dmg
			SetSpellPowerCoeffsAll(sp, 0.000001f);
		}	
	
		sp = dbcSpell.LookupEntryForced( 16312 );	//this is enchantment spell
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 16344;	//this is id to proc
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 1000;
		}
		sp = dbcSpell.LookupEntryForced( 16344 );	//stupid dummy effect
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;	// !!! dmg is high because : EffectRealPointsPerLevel
			sp->spell_id_client = 10444;			//according to dbc this does the dmg
			SetSpellPowerCoeffsAll(sp, 0.000001f);
		}	
	
		sp = dbcSpell.LookupEntryForced( 16313 );	//this is enchantment spell
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 25488;	//this is id to proc
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 1000;
		}
		sp = dbcSpell.LookupEntryForced( 25488 );	//stupid dummy effect
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;	// !!! dmg is high because : EffectRealPointsPerLevel
			sp->spell_id_client = 10444;			//according to dbc this does the dmg
			SetSpellPowerCoeffsAll(sp, 0.000001f);
		}	
	
		sp = dbcSpell.LookupEntryForced( 58784 );	//this is enchantment spell
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 58786;	//this is id to proc
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 1000;
		}
		sp = dbcSpell.LookupEntryForced( 58786 );	//stupid dummy effect
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;	// !!! dmg is high because : EffectRealPointsPerLevel
			sp->spell_id_client = 10444;			//according to dbc this does the dmg
			SetSpellPowerCoeffsAll(sp, 0.000001f);
		}	
	
		sp = dbcSpell.LookupEntryForced( 58791 );	//this is enchantment spell
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 58787;	//this is id to proc
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 1000;
		}
		sp = dbcSpell.LookupEntryForced( 58787 );	//stupid dummy effect
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;	// !!! dmg is high because : EffectRealPointsPerLevel
			sp->spell_id_client = 10444;			//according to dbc this does the dmg
			SetSpellPowerCoeffsAll(sp, 0.000001f);
		}	
	
		sp = dbcSpell.LookupEntryForced( 58792 );	//this is enchantment spell
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 58788;	//this is id to proc
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->proc_interval = 1000;
			sp->procChance = 20;
		}
		sp = dbcSpell.LookupEntryForced( 58788 );	//stupid dummy effect
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE;	// !!! dmg is high because : EffectRealPointsPerLevel
			sp->spell_id_client = 10444;			//according to dbc this does the dmg
			SetSpellPowerCoeffsAll(sp, 0.000001f);
		}	

		//Unleashed Rage
		sp = dbcSpell.LookupEntryForced( 30802 );
		//if( sp != NULL )
		{
			//but why ?
			sp->RequiredShapeShift = 0;
		}
		sp = dbcSpell.LookupEntryForced( 30808 );
		//if( sp != NULL )
		{
			//but why ?
			sp->RequiredShapeShift = 0;
		}
		sp = dbcSpell.LookupEntryForced( 30809 );
		//if( sp != NULL )
		{
			//but why ?
			sp->RequiredShapeShift = 0;
		}
		//Elemental Oath
		sp = dbcSpell.LookupEntryForced( 51466 );
		//if( sp != NULL )
		{
			//missing effect
/*			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_FLAT_MODIFIER;
			sp->EffectMiscValue[1] = SMT_MISC_EFFECT;
			sp->EffectBasePoints[1] = 4;
			sp->EffectSpellGroupRelation[1][0] = 0;
			sp->EffectSpellGroupRelation[1][1] = 0x00004000; // Clearcasting */
			//but why ?
			sp->RequiredShapeShift = 0;
		}
		sp = dbcSpell.LookupEntryForced( 51470 );
		//if( sp != NULL )
		{
			//missing effect
/*			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_FLAT_MODIFIER;
			sp->EffectMiscValue[1] = SMT_MISC_EFFECT;
			sp->EffectBasePoints[1] = 9;
			sp->EffectSpellGroupRelation[1][0] = 0;
			sp->EffectSpellGroupRelation[1][1] = 0x00004000; // Clearcasting */
			//but why ?
			sp->RequiredShapeShift = 0;
		}
		// Flurry
		sp = dbcSpell.LookupEntryForced( 12319 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp = dbcSpell.LookupEntryForced( 12971 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp = dbcSpell.LookupEntryForced( 12972 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp = dbcSpell.LookupEntryForced( 12973 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp = dbcSpell.LookupEntryForced( 12974 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp = dbcSpell.LookupEntryForced( 16256 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp = dbcSpell.LookupEntryForced( 16281 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp = dbcSpell.LookupEntryForced( 16282 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp = dbcSpell.LookupEntryForced( 16283 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp = dbcSpell.LookupEntryForced( 16284 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;
		// Flurry proc
		sp = dbcSpell.LookupEntryForced( 12966 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 12967 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 12968 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 12969 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 12970 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 16257 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 16277 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 16278 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 16279 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 16280 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		/**********************************************************
		 *	Shamanistic Rage
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 30823 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced( 30824 );
		//if( sp != NULL )
			sp->spell_id_client = sp->Id;

		//hex gets removed on dmg
		sp = dbcSpell.LookupEntryForced( 51514 );
		//if( sp != NULL )
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;

		//summon only 1 elemental totem
		sp = dbcSpell.LookupEntryForced( 2894 );
		//if( sp != NULL && sp->Id == 2894 )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_TOTEM_FIRE; //remove this targeting. it is enough to get 1 target

		//summon only 1 elemental totem
		sp = dbcSpell.LookupEntryForced( 2062 );
		//if( sp != NULL && sp->Id == 2062 )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_TOTEM_EARTH; //remove this targeting. it is enough to get 1 target

		/**********************************************************
		 *	Elemental Focus
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 16164 );
		//if( sp != NULL && sp->Id == 16164 )
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;

		/**********************************************************
		 *	Stormstrike
		 **********************************************************/
//		sp = dbcSpell.LookupEntryForced( 17364 );
//		//if( sp != NULL && sp->Id == 17364 )
//			sp->Effect[0]=0 ;
//			sp->procFlags=PROC_ON_SPELL_HIT_VICTIM ;

		/**********************************************************
		 *	Bloodlust
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 2825 );
		//if( sp != NULL )
			sp->chained_cast = dbcSpell.LookupEntryForced( 57724 );	//sated

		/**********************************************************
		 *	Heroism
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 32182 );
		//if( sp != NULL )
			sp->chained_cast = dbcSpell.LookupEntryForced( 57723 );	//Exhaustion

		//sated
		sp = dbcSpell.LookupEntryForced( 57724 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
			sp->ThreatForSpellCoef = 0;
		}
		//Exhaustion
		sp = dbcSpell.LookupEntryForced( 57723 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
			sp->ThreatForSpellCoef = 0;
		}
		//if( sp != NULL )
		/**********************************************************
		 *	Lightning Overload 
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 30675 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 30675;	//self proc !
			sp->proc_interval = 1000;	//avoid cast on cast loop
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LIGHTNING_BOLT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_CHAIN_LIGHTNING;
		}
		sp = dbcSpell.LookupEntryForced( 30678 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 30675;	//self proc !
			sp->proc_interval = 1000;	//avoid cast on cast loop
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LIGHTNING_BOLT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_CHAIN_LIGHTNING;
		}
		sp = dbcSpell.LookupEntryForced( 30679 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 30675;	//self proc !
			sp->proc_interval = 1000;	//avoid cast on cast loop
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LIGHTNING_BOLT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_CHAIN_LIGHTNING;
		}
/*		sp = dbcSpell.LookupEntryForced( 30680 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 39805;//proc something (we will owerride this)
			sp->procFlags = PROC_ON_SPELL_HIT;
		}
		sp = dbcSpell.LookupEntryForced( 30681 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 39805;//proc something (we will owerride this)
			sp->procFlags = PROC_ON_SPELL_HIT;
		}*/
		/**********************************************************
		 *	Purge 
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 370 ); 
		//if( sp != NULL )
			sp->DispelType = DISPEL_MAGIC;
		sp = dbcSpell.LookupEntryForced( 8012 ); 
		//if( sp != NULL )
			sp->DispelType = DISPEL_MAGIC;
		sp = dbcSpell.LookupEntryForced( 27626 ); 
		//if( sp != NULL )
			sp->DispelType = DISPEL_MAGIC;
		sp = dbcSpell.LookupEntryForced( 33625 ); 
		//if( sp != NULL )
			sp->DispelType = DISPEL_MAGIC;

		/**********************************************************
		 *	Eye of the Storm
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 29062 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
		sp = dbcSpell.LookupEntryForced( 29064 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
		sp = dbcSpell.LookupEntryForced( 29065 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;

		/**********************************************************
		 *	Shamanistic Focus
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 43338 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;

		sp = dbcSpell.LookupEntryForced( 43339 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
		}

		//some say earth shock should interrup spell cast. Others say it shoud not
/*		sp = dbcSpell.LookupEntryForced( 8042 ); 
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_INTERRUPT_CAST;
		sp = dbcSpell.LookupEntryForced( 8044 ); 
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_INTERRUPT_CAST;
		sp = dbcSpell.LookupEntryForced( 8045 ); 
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_INTERRUPT_CAST;
		sp = dbcSpell.LookupEntryForced( 8046 ); 
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_INTERRUPT_CAST;
		sp = dbcSpell.LookupEntryForced( 10412 ); 
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_INTERRUPT_CAST;
		sp = dbcSpell.LookupEntryForced( 10413 ); 
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_INTERRUPT_CAST;
		sp = dbcSpell.LookupEntryForced( 10414 ); 
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_INTERRUPT_CAST;
		sp = dbcSpell.LookupEntryForced( 25454 ); 
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_INTERRUPT_CAST;
		sp = dbcSpell.LookupEntryForced( 49230 ); 
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_INTERRUPT_CAST;
		sp = dbcSpell.LookupEntryForced( 49231 ); 
		//if( sp != NULL )
			sp->Effect[2] = SPELL_EFFECT_INTERRUPT_CAST;
			*/

		//shaman - Feral Spirit
		sp = dbcSpell.LookupEntryForced( 51533 ); 
		//if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_IS_INHERITING_LEVEL;

		//shaman - Elemental Mastery
		sp = dbcSpell.LookupEntryForced( 16166 ); 
		//if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE;

		//shaman - Improved Stormstrike
		sp = dbcSpell.LookupEntryForced( 51521 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_STORMSTRIKE;
		}
		sp = dbcSpell.LookupEntryForced( 51522 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_STORMSTRIKE;
		}
		//You have a $s1% chance to instantly gain mana as if you consumed a Water Shield Orb when you gain a critical effect from your Healing Wave or Riptide spells, a ${$m1*0.6}% chance when you gain a critical effect from your Lesser Healing Wave spell, and a ${$m1*0.3}% chance when you gain a critical effect from your Chain Heal spell.
		//shaman - Improved Water Shield
		sp = dbcSpell.LookupEntryForced( 16180 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 23575;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->procChance = sp->EffectBasePoints[0] + 1;
		}
		sp = dbcSpell.LookupEntryForced( 16196 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 23575;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->procChance = sp->EffectBasePoints[0] + 1;
		}
		sp = dbcSpell.LookupEntryForced( 16198 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 23575;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT_VICTIM;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->procChance = sp->EffectBasePoints[0] + 1;
		}
		sp = dbcSpell.LookupEntryForced( 23575 ); 
		//if( sp != NULL )
			sp->spell_id_client = sp->Id;

		//shaman - Improved Chain Heal
		sp = dbcSpell.LookupEntryForced( 30873 ); 
		//if( sp != NULL )
		{
			sp->EffectDieSides[0] = 0;
		}
		sp = dbcSpell.LookupEntryForced( 30872 ); 
		//if( sp != NULL )
		{
			sp->EffectDieSides[0] = 0;
		}

		//shaman - Improved Windfury Totem
		sp = dbcSpell.LookupEntryForced( 29193 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0]=SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectApplyAuraName[1]=SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
			sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
		}
		sp = dbcSpell.LookupEntryForced( 29192 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0]=SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectApplyAuraName[1]=SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
			sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
		}

		// Shaman - Improved Fire Totems
		sp = dbcSpell.LookupEntryForced( 16544 ); 
		//if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_DURATION;
		}
		sp = dbcSpell.LookupEntryForced( 16086 ); 
		//if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_DURATION;
		}

		// Shaman Arena totems fix
		// Totem of Survival
		sp = dbcSpell.LookupEntryForced( 46097 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 43860 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 43861 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 43862 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;

		// Totem of Indomitability
		sp = dbcSpell.LookupEntryForced( 43859 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 46096 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 43857 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 43858 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
		}

		// Totem of Third WInd
		sp = dbcSpell.LookupEntryForced( 46098 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LESSER_HEALING_WAVE;
		}
		sp = dbcSpell.LookupEntryForced( 34138 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LESSER_HEALING_WAVE;
		}
		sp = dbcSpell.LookupEntryForced( 42370 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LESSER_HEALING_WAVE;
		}
		sp = dbcSpell.LookupEntryForced( 43728 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LESSER_HEALING_WAVE;
		}
		sp = dbcSpell.LookupEntryForced( 60556 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LESSER_HEALING_WAVE;
		}
		sp = dbcSpell.LookupEntryForced( 60557 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LESSER_HEALING_WAVE;
		}
		sp = dbcSpell.LookupEntryForced( 60558 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LESSER_HEALING_WAVE;
		}
		sp = dbcSpell.LookupEntryForced( 60559 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LESSER_HEALING_WAVE;
		}

		//shaman - Elemental Weapons
		sp = dbcSpell.LookupEntryForced( 29080 ); 
		//if( sp != NULL )
		{
			sp->EffectMiscValue[1] = SMT_DAMAGE_DONE;
			sp->EffectMiscValue[2] = SMT_DAMAGE_DONE;
		}
		sp = dbcSpell.LookupEntryForced( 29079 ); 
		//if( sp != NULL )
		{
			sp->EffectMiscValue[1] = SMT_DAMAGE_DONE;
			sp->EffectMiscValue[2] = SMT_DAMAGE_DONE;
		}
		sp = dbcSpell.LookupEntryForced( 16266 ); 
		//if( sp != NULL )
		{
			sp->EffectMiscValue[1] = SMT_DAMAGE_DONE;
			sp->EffectMiscValue[2] = SMT_DAMAGE_DONE;
		}
	 
		// Magma Totem - 0% spd coefficient
		sp = dbcSpell.LookupEntryForced( 25550 ); 
		//if( sp != NULL )
			sp->fixed_dddhcoef = 0.0f;
		sp = dbcSpell.LookupEntryForced( 10581 ); 
		//if( sp != NULL )
			sp->fixed_dddhcoef = 0.0f;
		sp = dbcSpell.LookupEntryForced( 10580 ); 
		//if( sp != NULL )
			sp->fixed_dddhcoef = 0.0f;
		sp = dbcSpell.LookupEntryForced( 10579 ); 
		//if( sp != NULL )
			sp->fixed_dddhcoef = 0.0f;
		sp = dbcSpell.LookupEntryForced( 8187 ); 
		//if( sp != NULL )
			sp->fixed_dddhcoef = 0.0f;


		/**********************************************************
		 *	Healing Way
		 **********************************************************/
/*		Zack : disabled this to not create confusion that it is working. Burlex deleted code so it needs to be reverted in order to work
		sp = dbcSpell.LookupEntryForced( 29202 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
            sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
            sp->EffectImplicitTargetA[0] = EFF_TARGET_SCRIPTED_OR_SINGLE_TARGET;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HEALING_WAVE;
		}
		sp = dbcSpell.LookupEntryForced( 29205 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
            sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
            sp->EffectImplicitTargetA[0] = EFF_TARGET_SCRIPTED_OR_SINGLE_TARGET;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HEALING_WAVE;
		}
		sp = dbcSpell.LookupEntryForced( 29206 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
            sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
            sp->EffectImplicitTargetA[0] = EFF_TARGET_SCRIPTED_OR_SINGLE_TARGET;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HEALING_WAVE;
		}
		//mod spell effect from caster
		sp = dbcSpell.LookupEntryForced( 29203 ); 
		//if( sp != NULL )
			sp->EffectApplyAuraName[ 0 ] = PROC_ON_CAST_SPELL;*/

		/**********************************************************
		 *	Elemental Devastation
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 29179 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp = dbcSpell.LookupEntryForced( 29180 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp = dbcSpell.LookupEntryForced( 30160 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;

		/**********************************************************
		 *	Ancestral healing
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 16176 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp = dbcSpell.LookupEntryForced( 16235 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp = dbcSpell.LookupEntryForced( 16240 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;

		/**********************************************************
		 *	Ancestral healing proc spell
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 16177 );
		//if( sp != NULL )
			sp->rangeIndex = 4;
		sp = dbcSpell.LookupEntryForced( 16236 );
		//if( sp != NULL )
			sp->rangeIndex = 4;
		sp = dbcSpell.LookupEntryForced( 16237 );
		//if( sp != NULL )
			sp->rangeIndex = 4;

		//wrath of air totem targets sorounding creatures instead of us
		sp = dbcSpell.LookupEntryForced( 2895 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}

		sp = dbcSpell.LookupEntryForced( 20608 ); //Reincarnation
		//if( sp != NULL )
		{
			for(uint32 i=0;i<8;i++)
			{
				if( sp->Reagent[i])
				{
					sp->Reagent[i] = 0;
					sp->ReagentCount[i] = 0;
				}
			}
		}

		//shaman - Maelstrom Weapon
		sp = dbcSpell.LookupEntryForced( 51528 ); 
		//if( sp != NULL )
		{
			sp->procFlags |= PROC_ON_MELEE_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 60;
		}
		sp = dbcSpell.LookupEntryForced( 51529 ); 
		//if( sp != NULL )
		{
			sp->procFlags |= PROC_ON_MELEE_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 70;
		}
		sp = dbcSpell.LookupEntryForced( 51530 ); 
		//if( sp != NULL )
		{
			sp->procFlags |= PROC_ON_MELEE_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 80;
		}
		sp = dbcSpell.LookupEntryForced( 51531 ); 
		//if( sp != NULL )
		{
			sp->procFlags |= PROC_ON_MELEE_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 90;
		}
		sp = dbcSpell.LookupEntryForced( 51532 ); 
		//if( sp != NULL )
		{
			sp->procFlags |= PROC_ON_MELEE_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 100;
		}
		//this is proc -> set remove condition
		sp = dbcSpell.LookupEntryForced( 53817 ); 
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		//shaman - Rockbiter Weapon
		sp = dbcSpell.LookupEntryForced( 8017 ); 
		//if( sp != NULL )
			sp->EffectBasePoints[1] = 1800;	//this is duration for enchants :(
		sp = dbcSpell.LookupEntryForced( 8018 ); 
		//if( sp != NULL )
			sp->EffectBasePoints[1] = 1800;	//this is duration for enchants :(
		sp = dbcSpell.LookupEntryForced( 8019 ); 
		//if( sp != NULL )
			sp->EffectBasePoints[1] = 1800;	//this is duration for enchants :(
		sp = dbcSpell.LookupEntryForced( 10399 ); 
		//if( sp != NULL )
			sp->EffectBasePoints[1] = 1800;	//this is duration for enchants :(

		//shaman - Earth Shield
		sp = dbcSpell.LookupEntryForced( 974 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->proc_interval = 3000; //few seconds
			sp->EffectTriggerSpell[0] = 379;
		}
		sp = dbcSpell.LookupEntryForced( 32593 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->proc_interval = 3000; //few seconds
			sp->EffectTriggerSpell[0] = 379;
		}
		sp = dbcSpell.LookupEntryForced( 32594 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->proc_interval = 3000; //few seconds
			sp->EffectTriggerSpell[0] = 379;
		}
		sp = dbcSpell.LookupEntryForced( 49283 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->proc_interval = 3000; //few seconds
			sp->EffectTriggerSpell[0] = 379;
		}
		sp = dbcSpell.LookupEntryForced( 49284 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->proc_interval = 3000; //few seconds
			sp->EffectTriggerSpell[0] = 379;
		}

		//shaman - Ancestral Awakening
		sp = dbcSpell.LookupEntryForced( 51558 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectTriggerSpell[0] = 52752;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HEALING_WAVE;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_LESSER_HEALING_WAVE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_RIPTIDE;
		}
		sp = dbcSpell.LookupEntryForced( 51557 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectTriggerSpell[0] = 52752;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HEALING_WAVE;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_LESSER_HEALING_WAVE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_RIPTIDE;
		}
		sp = dbcSpell.LookupEntryForced( 51558 ); 
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectTriggerSpell[0] = 52752;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HEALING_WAVE;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_LESSER_HEALING_WAVE;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_RIPTIDE;
		}
		sp = dbcSpell.LookupEntryForced( 52752 ); 
		//if( sp != NULL )
		{
			SetAllSpellCoef(sp,0.0f);
			sp->spell_can_crit = false;
			sp->spell_id_client = sp->Id;
		}
		// Nature's Guardian
		sp = dbcSpell.LookupEntryForced( 30881 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM | 
				PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_ANY_DAMAGE_VICTIM;
			sp->proc_interval = 30000;
			sp->EffectTriggerSpell[0] = 31616;
		}
		sp = dbcSpell.LookupEntryForced( 30883 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM | 
				PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_ANY_DAMAGE_VICTIM;
			sp->proc_interval = 30000;
			sp->EffectTriggerSpell[0] = 31616;
		}
		sp = dbcSpell.LookupEntryForced( 30884 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM | 
				PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_ANY_DAMAGE_VICTIM;
			sp->proc_interval = 30000;
			sp->EffectTriggerSpell[0] = 31616;
		}
		sp = dbcSpell.LookupEntryForced( 30885 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM | 
				PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_ANY_DAMAGE_VICTIM;
			sp->proc_interval = 30000;
			sp->EffectTriggerSpell[0] = 31616;
		}
		sp = dbcSpell.LookupEntryForced( 30886 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM | 
				PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_ANY_DAMAGE_VICTIM;
			sp->proc_interval = 30000;
			sp->EffectTriggerSpell[0] = 31616;
		}
		//mana tide totem tick
		sp = dbcSpell.LookupEntryForced( 39610 ); 
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE_MAXPOWER_PCT;
			sp->EffectBasePoints[0] = 5;
		}
		//////////////////////////////////////////
		// SHAMAN WRATH OF AIR TOTEM			//
		//////////////////////////////////////////
		sp = dbcSpell.LookupEntryForced( 2895 ); 
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}

	//////////////////////////////////////////
	// MAGE								//
	//////////////////////////////////////////

	// Insert mage spell fixes here
		
		//Invisibility
		sp = dbcSpell.LookupEntryForced( 66 );
		sp2 = dbcSpell.LookupEntryForced( 32612 );
		//if( sp != NULL )
		{
			SpellEntryEffectCopy(sp2,sp,1,0);
			SpellEntryEffectCopy(sp2,sp,2,1);
			sp->DurationIndex = sp2->DurationIndex;
			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_CAST_SPELL;
		}

		//Mirror Image -> this is not finished. But at least make them spawn
		sp = dbcSpell.LookupEntryForced( 55342 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SUMMON;
			sp->EffectMiscValue[0] = 31216;		//some gnomes on the field
			sp->EffectMiscValueB[0] = 1021;
			sp->EffectBasePoints[0] = 2;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->Effect[1] = SPELL_EFFECT_NULL;
			sp->Effect[2] = SPELL_EFFECT_NULL;
			sp->c_is_flags |= SPELL_FLAG_IS_INHERITING_LEVEL;
		}

		//Hypothermia
		sp = dbcSpell.LookupEntryForced( 41425 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
			sp->DispelType = 66666; //this shoud be invalid
		}
		//deserter
		sp = dbcSpell.LookupEntryForced( 26013 );
		//if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;

		//Improved Counterspell 
		sp = dbcSpell.LookupEntryForced( 11255 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_COUNTERSPELL;
		}
		sp = dbcSpell.LookupEntryForced( 12598 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_COUNTERSPELL;
		}

		//Missile Barrage 
		sp = dbcSpell.LookupEntryForced( 44404 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 54486 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 54488 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 54489 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 54490 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 44401 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procCharges = 1;
		}

		//Hot Streak 
		sp = dbcSpell.LookupEntryForced( 44445 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48108;
			sp->Effect[1] = SPELL_EFFECT_NULL;
		}
		sp = dbcSpell.LookupEntryForced( 44446 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48108;
			sp->Effect[1] = SPELL_EFFECT_NULL;
		}
		sp = dbcSpell.LookupEntryForced( 44448 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48108;
			sp->Effect[1] = SPELL_EFFECT_NULL;
		}
		sp = dbcSpell.LookupEntryForced( 48108 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procCharges = 1;
		}

		//Impact
		sp = dbcSpell.LookupEntryForced( 11103 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 12357 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		sp = dbcSpell.LookupEntryForced( 12358 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;
		//proc of the talent aura
		sp = dbcSpell.LookupEntryForced( 64343 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procCharges = 1;	//next fire blast
		}
		sp = dbcSpell.LookupEntryForced( 12355 );
		//if( sp != NULL )
			sp->ProcOnNameHash[0] = SPELL_HASH_FIRE_BLAST;
	    
		//Firestarter - *Rank 1*
		sp = dbcSpell.LookupEntryForced( 44442 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_BLAST_WAVE;
			sp->ProcOnNameHash[1] = SPELL_HASH_DRAGON_S_BREATH;
		}
		sp = dbcSpell.LookupEntryForced( 44443 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_BLAST_WAVE;
			sp->ProcOnNameHash[1] = SPELL_HASH_DRAGON_S_BREATH;
		}
		sp = dbcSpell.LookupEntryForced( 54741 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procCharges = 1;
		}

		//Improved Blink - *Rank 1*
		sp = dbcSpell.LookupEntryForced( 31569 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_BLINK;
		}
		sp = dbcSpell.LookupEntryForced( 31570 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_BLINK;
		}

		//Mage - Torment the Weak
		sp = dbcSpell.LookupEntryForced( 29447 );
		//if( sp != NULL )
			sp->EffectApplyAuraName[0] = SPELL_AURA_OVERRIDE_CLASS_SCRIPTS;
		sp = dbcSpell.LookupEntryForced( 55339 );
		//if( sp != NULL )
			sp->EffectApplyAuraName[0] = SPELL_AURA_OVERRIDE_CLASS_SCRIPTS;
		sp = dbcSpell.LookupEntryForced( 55340 );
		//if( sp != NULL )
			sp->EffectApplyAuraName[0] = SPELL_AURA_OVERRIDE_CLASS_SCRIPTS;

		//Mage - Arcane Blast
		sp = dbcSpell.LookupEntryForced( 30451 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 36032;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[1] = SPELL_HASH_ARCANE_BLAST;
		}

		// Updated ranks by Joker
		// Arcane Blast
		sp = dbcSpell.LookupEntryForced( 42894 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 36032;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[1] = SPELL_HASH_ARCANE_BLAST;
		}

		sp = dbcSpell.LookupEntryForced( 42896 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 36032;
			sp->procFlags = PROC_ON_CAST_SPELL;
		}

		sp = dbcSpell.LookupEntryForced( 42897 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 36032;
			sp->procFlags = PROC_ON_CAST_SPELL;
		}
	
		//mage - Arcane Blast Proc
		sp = dbcSpell.LookupEntryForced( 36032 );
		{
			sp->procFlags = 0;
			sp->maxstack = 4;
			sp->procCharges = 0;
			sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
		}

		//Incanter's Absorption
		sp = dbcSpell.LookupEntryForced( 44394 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ABSORB ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 44413;
			sp->proc_interval = 10000;	//no spam ok ?
		}
		sp = dbcSpell.LookupEntryForced( 44395 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ABSORB ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 44413;
			sp->proc_interval = 10000;	//no spam ok ?
		}
		sp = dbcSpell.LookupEntryForced( 44396 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ABSORB ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 44413;
			sp->proc_interval = 10000;	//no spam ok ?
		}

		// Arcane Concentration
		sp = dbcSpell.LookupEntryForced( 11213 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 12574 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 12575 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 12576 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 12577 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		//Clearcasting
		sp = dbcSpell.LookupEntryForced( 12536 );
		//if( sp != NULL )
		{
			sp->AuraInterruptFlags &= ~(AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN | AURA_INTERRUPT_ON_CAST_SPELL | AURA_INTERRUPT_ON_HOSTILE_SPELL_INFLICTED);
			sp->procCharges = 1; //1 is removed on apply, 1 is used on spell cast, 1 is left ?
//			sp->EffectBasePoints[0] = -101;	//why the hack put value 1000 then say that you only use 100 ?
		}

/*		//Mage - Wand Specialization. Not the forst thing we messed up. Blizz uses attack as magic and wandds as weapons :S
		sp = dbcSpell.LookupEntryForced( 6057 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		}
		sp = dbcSpell.LookupEntryForced( 6085 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		}*/
		//Mage - ice lance should have around 60% spell power coef
		sp = dbcSpell.LookupEntryForced( 30455 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll( sp, 0.1429f );
		sp = dbcSpell.LookupEntryForced( 42913 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll( sp, 0.1429f );
		sp = dbcSpell.LookupEntryForced( 42914 );
		//if( sp != NULL )
			SetSpellPowerCoeffsAll( sp, 0.1429f );
		//Mage - Spell Power
		sp = dbcSpell.LookupEntryForced( 35578 );
		//if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_CRITICAL_DAMAGE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		}
		sp = dbcSpell.LookupEntryForced( 35581 );
		//if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_CRITICAL_DAMAGE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		}

		//Mage - Elemental Precision
		sp = dbcSpell.LookupEntryForced( 29438 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_COST;
		}
		sp = dbcSpell.LookupEntryForced( 29439 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_COST;
		}
		sp = dbcSpell.LookupEntryForced( 29440 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_COST;
		}

		//Burning Determination
		sp = dbcSpell.LookupEntryForced( 54747 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM;
		sp = dbcSpell.LookupEntryForced( 54749 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM;

		//Mage - Improved Blizzard
		sp = dbcSpell.LookupEntryForced( 11185 );
		//if( sp != NULL )
		{    
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 12484;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_BLIZZARD;
		}
		sp = dbcSpell.LookupEntryForced( 12487 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 12485;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_BLIZZARD;
		}
		sp = dbcSpell.LookupEntryForced( 12488 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 12486;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_BLIZZARD;
		}

		//mage - Combustion
		sp = dbcSpell.LookupEntryForced( 11129 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 28682;
			sp->procFlags = PROC_ON_SPELL_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procCharges = 0;
			sp->c_is_flags |= SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE;
		}
		sp = dbcSpell.LookupEntryForced( 28682 );
		//if( sp != NULL )
			sp->procCharges = -1;	//let the proc stack with mother spell

		//mage - Empowered Fire
		sp = dbcSpell.LookupEntryForced( 31656 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 67545;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_IGNITE;
		}
		sp = dbcSpell.LookupEntryForced( 31657 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 67545;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_IGNITE;
		}
		sp = dbcSpell.LookupEntryForced( 31658 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 67545;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_IGNITE;
		}
		sp = dbcSpell.LookupEntryForced( 67545 );
		//if( sp != NULL )
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE_MAXPOWER_PCT;

		//mage - Master of Elements
		sp = dbcSpell.LookupEntryForced( 29074 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 29077;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 100;
		}
		sp = dbcSpell.LookupEntryForced( 29075 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 29077;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 100;
		}
		sp = dbcSpell.LookupEntryForced( 29076 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 29077;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 100;
		}

		//mage: Blazing Speed
		sp = dbcSpell.LookupEntryForced( 31641 ); 
		//if( sp != NULL )
			sp->EffectTriggerSpell[0] = 31643;
		sp = dbcSpell.LookupEntryForced( 31642 );
		//if( sp != NULL )
			sp->EffectTriggerSpell[0] = 31643;

		//mage talent "frostbite". we make it to be dummy
		sp = dbcSpell.LookupEntryForced( 11071 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = sp->EffectBasePoints[0] + 1;
		}
		sp = dbcSpell.LookupEntryForced( 12496 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = sp->EffectBasePoints[0] + 1;
		}
		sp = dbcSpell.LookupEntryForced( 12497 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = sp->EffectBasePoints[0] + 1;
		}

		// Enduring Winter
		sp = dbcSpell.LookupEntryForced( 44557 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_FROSTBOLT;
		}
		sp = dbcSpell.LookupEntryForced( 44560 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_FROSTBOLT;
		}
		sp = dbcSpell.LookupEntryForced( 44561 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_FROSTBOLT;
		}

		// Fingers of Frost rank 1
		sp = dbcSpell.LookupEntryForced( 44543 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->EffectTriggerSpell[0] = 74396;
		}
		sp = dbcSpell.LookupEntryForced( 44545 );
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->EffectTriggerSpell[0] = 74396;
		}
		
		//Fingers of frost proc
		sp = dbcSpell.LookupEntryForced( 74396 );
		//if( sp != NULL )
		{
			sp->procCharges = 2;	//do we even need this ?
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
		}

		//Mage - Arcane shielding
		sp = dbcSpell.LookupEntryForced( 11252 );
		//if( sp != NULL )
			sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp = dbcSpell.LookupEntryForced( 12605 );
		//if( sp != NULL )
			sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;

		//Mage - Summon Water Elemental
		sp = dbcSpell.LookupEntryForced( 31687 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_SUMMON;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_DYNAMIC_OBJECT;
			sp->EffectMiscValue[0] = 510;
			sp->EffectMiscValueB[0] = 67;
		}

		//Mage - Focus Magic
		sp = dbcSpell.LookupEntryForced( 54646 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = 100;	//script this
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectTriggerSpell[1] = 54648;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_DUEL;
			sp->BGR_one_buff_from_caster_on_1target = SPELL_TYPE_INDEX_FOCUS_MAGIC;
		}
		//Mage - Arcane Empowerment
		sp = dbcSpell.LookupEntryForced( 31579 );
		//if( sp != NULL )
			sp->RequiredShapeShift = 0;
		sp = dbcSpell.LookupEntryForced( 31582 );
		//if( sp != NULL )
			sp->RequiredShapeShift = 0;
		sp = dbcSpell.LookupEntryForced( 31583 );
		//if( sp != NULL )
			sp->RequiredShapeShift = 0;

		//Mage - Improved Scorch
		sp = dbcSpell.LookupEntryForced( 11095 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance =33;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SCORCH;
		}
		sp = dbcSpell.LookupEntryForced( 12872 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL; 
			sp->procChance =66;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SCORCH;
		}
		sp = dbcSpell.LookupEntryForced( 12873 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance =100;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SCORCH;
		}
		// mage - Frost Warding
		sp = dbcSpell.LookupEntryForced( 11189 );
		//if( sp != NULL )
		{
			sp->procChance = 10;
		}
		sp = dbcSpell.LookupEntryForced( 28332 );
		//if( sp != NULL )
		{
			sp->procChance = 20;
		}

		// mage - Conjure Refreshment Table
		sp = dbcSpell.LookupEntryForced( 43985 );
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_DYNAMIC_OBJECT;

		//living bomb
		sp = dbcSpell.LookupEntryForced( 44457 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
			sp->EffectAmplitude[1] = 14500;
			sp->EffectTriggerSpell[1] = sp->EffectBasePoints[1] + 1;
		}
		sp = dbcSpell.LookupEntryForced( 55359 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
			sp->EffectAmplitude[1] = 14500;
			sp->EffectTriggerSpell[1] = sp->EffectBasePoints[1] + 1;
		}
		sp = dbcSpell.LookupEntryForced( 55360 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
			sp->EffectAmplitude[1] = 14500;
			sp->EffectTriggerSpell[1] = sp->EffectBasePoints[1] + 1;
		}
	//////////////////////////////////////////
	// WARLOCK								//
	//////////////////////////////////////////

	// Insert warlock spell fixes here
		//Fel Synergy
		sp = dbcSpell.LookupEntryForced( 47230 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 54181;
			sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE ;
		}
		sp = dbcSpell.LookupEntryForced( 47231 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 54181;
			sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE ;
		}
		sp = dbcSpell.LookupEntryForced( 54181 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->spell_id_client = sp->Id;
		}

		//conflagrate
		sp = dbcSpell.LookupEntryForced( 17962 );
		//if( sp != NULL )
		{
			sp->EffectBasePoints[0] = sp->EffectBasePoints[1];
			sp->EffectBasePoints[1] = sp->EffectBasePoints[2];
			sp->fixed_dddhcoef = 0.8f;
			sp->fixed_hotdotcoef = 0.8f;
		}
		//Backdraft
		sp = dbcSpell.LookupEntryForced( 47258 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CONFLAGRATE;
		}
		sp = dbcSpell.LookupEntryForced( 47259 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CONFLAGRATE;
		}
		sp = dbcSpell.LookupEntryForced( 47260 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CONFLAGRATE;
		}
		sp = dbcSpell.LookupEntryForced( 54277 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procCharges = 3;
		}

		//Molten Core
		sp = dbcSpell.LookupEntryForced( 47245 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE ;	//cast spell falg is to be able to test removal condition :(
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CORRUPTION;
		}
		sp = dbcSpell.LookupEntryForced( 47246 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE ;	//cast spell falg is to be able to test removal condition :(
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CORRUPTION;
		}
		sp = dbcSpell.LookupEntryForced( 47247 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE ;	//cast spell falg is to be able to test removal condition :(
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CORRUPTION;
		}
		sp = dbcSpell.LookupEntryForced( 47383 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL ;	
		sp = dbcSpell.LookupEntryForced( 71162 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL ;	
		sp = dbcSpell.LookupEntryForced( 71165 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL ;	

		//Demonic Circle: summon
		sp = dbcSpell.LookupEntryForced( 48018 );
		//if( sp != NULL )
			sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY; //we just need this to be visible 
		//Demonic Circle: Teleport
		sp = dbcSpell.LookupEntryForced( 48020 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_DUMMY;
			sp->casterAuraSpell = 0;
		}
		
		//metamophosis side effects are "passive" to stack
		sp = dbcSpell.LookupEntryForced( 54817 );
		//if( sp != NULL )
			sp->Attributes |= ATTRIBUTES_PASSIVE;
		sp = dbcSpell.LookupEntryForced( 54879 );
		//if( sp != NULL )
			sp->Attributes |= ATTRIBUTES_PASSIVE;
		sp = dbcSpell.LookupEntryForced( 61610 );
		//if( sp != NULL )
			sp->Attributes |= ATTRIBUTES_PASSIVE;
		//Unstable Affliction
		sp = dbcSpell.LookupEntryForced( 30108 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 31117;
			sp->procChance = 100;
			sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 30404 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 31117;
			sp->procChance = 100;
			sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 30405 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 31117;
			sp->procChance = 100;
			sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 31117 );
		//if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;

		/**********************************************************
		 *	Nether Protection
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 30299 );
		//if( sp != NULL )
		{
			sp->proc_interval = 8000;
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectTriggerSpell[0] = 54370;
		}
		sp = dbcSpell.LookupEntryForced( 30301 );
		//if( sp != NULL )
		{
			sp->proc_interval = 8000;
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectTriggerSpell[0] = 54370;
		}
		sp = dbcSpell.LookupEntryForced( 30302 );
		//if( sp != NULL )
		{
			sp->proc_interval = 8000;
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectTriggerSpell[0] = 54370;
		}
		//Demonic Pact
		sp = dbcSpell.LookupEntryForced( 47236 );
		//if( sp != NULL )
		{
			sp->proc_interval = 20000;
			sp->procFlags |= PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_CRIT_ATTACK;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48090;
			sp->EffectImplicitTargetA[0]=EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER;
		}
		sp = dbcSpell.LookupEntryForced( 47237 );
		//if( sp != NULL )
		{
			sp->proc_interval = 20000;
			sp->procFlags |= PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_CRIT_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48090;
			sp->EffectImplicitTargetA[0]=EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER;
		}
		sp = dbcSpell.LookupEntryForced( 47238 );
		//if( sp != NULL )
		{
			sp->proc_interval = 20000;
			sp->procFlags |= PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_CRIT_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48090;
			sp->EffectImplicitTargetA[0]=EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER;
		}
		sp = dbcSpell.LookupEntryForced( 47239 );
		//if( sp != NULL )
		{
			sp->proc_interval = 20000;
			sp->procFlags |= PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_CRIT_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48090;
			sp->EffectImplicitTargetA[0]=EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER;
		}
		sp = dbcSpell.LookupEntryForced( 47240 );
		//if( sp != NULL )
		{
			sp->proc_interval = 20000;
			sp->procFlags |= PROC_ON_SPELL_CRIT_HIT | PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_CRIT_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48090;
			sp->EffectImplicitTargetA[0]=EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER;
		}
		sp = dbcSpell.LookupEntryForced( 48090 );
		//if( sp != NULL )
		{
			sp->RequiredShapeShift = 0;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		// warlock - Master Conjuror
		sp = dbcSpell.LookupEntryForced( 18767 );
		//if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_MISC_EFFECT;	//SMT_PCT_EFFECT_VALUE_2 - need to implement this
			sp->EffectMiscValue[1] = SMT_MISC_EFFECT;
		}
		sp = dbcSpell.LookupEntryForced( 18768 );
		//if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
			sp->EffectMiscValue[1] = SMT_MISC_EFFECT;
		}
		/**********************************************************
		 *	Backlash
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 34935 );
		//if( sp != NULL )
		{
			sp->proc_interval = 8000;
			sp->procFlags |= PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 34938 );
		//if( sp != NULL )
		{
			sp->proc_interval = 8000;
			sp->procFlags |= PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 34939 );
		//if( sp != NULL )
		{
			sp->proc_interval = 8000;
			sp->procFlags |= PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 34936 );
		//if( sp != NULL )
		{
			sp->AuraInterruptFlags = AURA_INTERRUPT_ON_CAST_SPELL;
		}

		/**********************************************************
		 *	Demonic Knowledge
		 **********************************************************/
		sp = dbcSpell.LookupEntryForced( 35691 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[0]=EFF_TARGET_PET;
			sp->EffectTriggerSpell[0] = 35696;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER;
		}
		sp = dbcSpell.LookupEntryForced( 35692 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE;
			sp->EffectImplicitTargetA[0]=EFF_TARGET_PET;
			sp->EffectTriggerSpell[0] = 35696;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER;
		}
		sp = dbcSpell.LookupEntryForced( 35693 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[0]=EFF_TARGET_PET;
			sp->EffectTriggerSpell[0] = 35696;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER;
		}
		sp = dbcSpell.LookupEntryForced( 35696 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY; //no effect here
			sp->EffectImplicitTargetA[0]=EFF_TARGET_PET;
			sp->RequiredShapeShift = 0;
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		}

		//warlock: Aftermath
		sp = dbcSpell.LookupEntryForced( 18119 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_CONFLAGRATE;
		}
		sp = dbcSpell.LookupEntryForced( 18120 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_CONFLAGRATE;
		}
		//warlock: Eradication
		sp = dbcSpell.LookupEntryForced( 47195 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->ProcOnNameHash[0] = SPELL_HASH_CORRUPTION;
		}
		sp = dbcSpell.LookupEntryForced( 47196 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->ProcOnNameHash[0] = SPELL_HASH_CORRUPTION;
		}
		sp = dbcSpell.LookupEntryForced( 47197 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->ProcOnNameHash[0] = SPELL_HASH_CORRUPTION;
		}
		//warlock -  Seed of Corruption
		sp = dbcSpell.LookupEntryForced( 27243 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 27285;
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_DIE;
			sp->procChance = 100;
		}

		//warlock -  soul link
		sp = dbcSpell.LookupEntryForced( 19028 );
		//if( sp != NULL )
		{
			sp->Effect[0]= SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 25228;
		}
		sp = dbcSpell.LookupEntryForced( 25228 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_DMGSPLIT_CASTER_TARGET;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}

		//warlock: Nightfall
		sp = dbcSpell.LookupEntryForced( 18094 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 17941;
			sp->procFlags = PROC_ON_ANY_HOSTILE_ACTION ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance += 10;	//hacks, ppl QQ this does not work due to low proc rate :(
		}
		sp = dbcSpell.LookupEntryForced( 18095 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 17941;
			sp->procFlags = PROC_ON_ANY_HOSTILE_ACTION ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance += 10;	//hacks, ppl QQ this does not work due to low proc rate :(
		}
		//Shadow Trance should be removed on the first SB
		sp = dbcSpell.LookupEntryForced( 17941 );
		//if( sp != NULL )
		{
			sp->AuraInterruptFlags = AURA_INTERRUPT_ON_CAST_SPELL;
		}

		//warlock: Empowered Corruption
		sp = dbcSpell.LookupEntryForced( 32381 );
		//if( sp != NULL )
		{
			sp->EffectBasePoints[0] *= 6;
		}
		sp = dbcSpell.LookupEntryForced( 32382 );
		//if( sp != NULL )
		{
			sp->EffectBasePoints[0] *= 6;
		}
		sp = dbcSpell.LookupEntryForced( 32383 );
		//if( sp != NULL )
		{
			sp->EffectBasePoints[0] *= 6;
		}

		//warlock: Improved Enslave Demon
/*		sp = dbcSpell.LookupEntryForced( 18821 );
		//if( sp != NULL )
		{
			sp->EffectMiscValue[0] = SMT_SPELL_VALUE_DOT;
			sp->EffectBasePoints[0] = -(sp->EffectBasePoints[0]+2);
		}*/

		//warlock - Demonic Sacrifice
		sp = dbcSpell.LookupEntryForced( 18789 );
		//if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_ON_PET;
		sp = dbcSpell.LookupEntryForced( 18790 );
		//if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_ON_PET;
		sp = dbcSpell.LookupEntryForced( 18791 );
		//if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_ON_PET;
		sp = dbcSpell.LookupEntryForced( 18792 );
		//if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_ON_PET;
		sp = dbcSpell.LookupEntryForced( 35701 );
		//if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_ON_PET;

		//warlock - Demonic Tactics
		sp = dbcSpell.LookupEntryForced( 30242 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 0; //disble this. This is just blizz crap. Pure proove that they suck :P
			sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
			sp->EffectApplyAuraName[2] = SPELL_AURA_MOD_SPELL_CRIT_CHANCE; //lvl 1 has it fucked up :O
			sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		}
		sp = dbcSpell.LookupEntryForced( 30245 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 0; //disble this. This is just blizz crap. Pure proove that they suck :P
			sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
			sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		}
		sp = dbcSpell.LookupEntryForced( 30246 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 0; //disble this. This is just blizz crap. Pure proove that they suck :P
			sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
			sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		}
		sp = dbcSpell.LookupEntryForced( 30247 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 0; //disble this. This is just blizz crap. Pure proove that they suck :P
			sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
			sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		}
		sp = dbcSpell.LookupEntryForced( 30248 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 0; //disble this. This is just blizz crap. Pure proove that they suck :P
			sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
			sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		}

		//warlock - Demonic Resilience
		sp = dbcSpell.LookupEntryForced( 30319 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		}
		sp = dbcSpell.LookupEntryForced( 30320 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		}
		sp = dbcSpell.LookupEntryForced( 30321 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		}

		//warlock - Improved Health Funnel
		sp = dbcSpell.LookupEntryForced( 18703 );
		//if( sp != NULL )
		{
			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
			sp->procChance = 100;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_HEALTH_FUNNEL;
			sp->EffectTriggerSpell[2] = 60955;
		}
		sp = dbcSpell.LookupEntryForced( 18704 );
		//if( sp != NULL )
		{
			sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
			sp->procChance = 100;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_HEALTH_FUNNEL;
			sp->EffectTriggerSpell[2] = 60956;
		}
		sp2 = dbcSpell.LookupEntryForced( 60955 );
		//if( sp2 != NULL )
			sp2->DurationIndex=dbcSpell.LookupEntryForced( 47856 )->DurationIndex;
		sp2 = dbcSpell.LookupEntryForced( 60956 );
		//if( sp2 != NULL )
			sp2->DurationIndex=dbcSpell.LookupEntryForced( 47856 )->DurationIndex;

		//warlock - Improved Imp
		sp = dbcSpell.LookupEntryForced( 18694 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 18695 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 18696 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}

		//warlock - Improved Voidwalker
		sp = dbcSpell.LookupEntryForced( 18705 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 18706 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 18707 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}

		//warlock - Improved Succubus
		sp = dbcSpell.LookupEntryForced( 18754 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 18755 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 18756 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		}

		//warlock - Fel Intellect
		sp = dbcSpell.LookupEntryForced( 18731 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
			sp->EffectMiscValue[0] = 3;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 18743 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
			sp->EffectMiscValue[0] = 3;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 18744 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
			sp->EffectMiscValue[0] = 3;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}

		//warlock - Fel Stamina
/*		sp = dbcSpell.LookupEntryForced( 18748 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
			sp->EffectMiscValue[0] = 2;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 18749 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
			sp->EffectMiscValue[0] = 2;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}
		sp = dbcSpell.LookupEntryForced( 18750 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
			sp->EffectMiscValue[0] = 2;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		}*/

		//warlock - Improved Demonic Tactics
		sp = dbcSpell.LookupEntryForced( 54347 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_SPELL_CRIT_CHANCE;
			sp->EffectHandler = &HandleImprovedDemonicTactics;
		}
		sp = dbcSpell.LookupEntryForced( 54348 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_SPELL_CRIT_CHANCE;
			sp->EffectHandler = &HandleImprovedDemonicTactics;
		}
		sp = dbcSpell.LookupEntryForced( 54349 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_SPELL_CRIT_CHANCE;
			sp->EffectHandler = &HandleImprovedDemonicTactics;
		}

		//warlock - Unholy Power
		sp = dbcSpell.LookupEntryForced( 18769 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			//now how the heck to mod imp fireball only ? i think that is he's only attack no ?
			sp->EffectMiscValue[0] = g_spellSchoolConversionTable[ SCHOOL_NORMAL ] | g_spellSchoolConversionTable[ SCHOOL_FIRE ] ;
		}
		sp = dbcSpell.LookupEntryForced( 18770 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			//now how the heck to mod imp fireball only ? i think that is he's only attack no ?
			sp->EffectMiscValue[0] = g_spellSchoolConversionTable[ SCHOOL_NORMAL ] | g_spellSchoolConversionTable[ SCHOOL_FIRE ] ;
		}
		sp = dbcSpell.LookupEntryForced( 18771 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			//now how the heck to mod imp fireball only ? i think that is he's only attack no ?
			sp->EffectMiscValue[0] = g_spellSchoolConversionTable[ SCHOOL_NORMAL ] | g_spellSchoolConversionTable[ SCHOOL_FIRE ] ;
		}
		sp = dbcSpell.LookupEntryForced( 18772 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			//now how the heck to mod imp fireball only ? i think that is he's only attack no ?
			sp->EffectMiscValue[0] = g_spellSchoolConversionTable[ SCHOOL_NORMAL ] | g_spellSchoolConversionTable[ SCHOOL_FIRE ] ;
		}
		sp = dbcSpell.LookupEntryForced( 18773 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
			//now how the heck to mod imp fireball only ? i think that is he's only attack no ?
			sp->EffectMiscValue[0] = g_spellSchoolConversionTable[ SCHOOL_NORMAL ] | g_spellSchoolConversionTable[ SCHOOL_FIRE ] ;
		}

		//warlock - Master Demonologist - 25 spells here
		sp = dbcSpell.LookupEntryForced( 23785 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 23784;
		}
		sp = dbcSpell.LookupEntryForced( 23822 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 23830;
		}
		sp = dbcSpell.LookupEntryForced( 23823 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 23831;
		}
		sp = dbcSpell.LookupEntryForced( 23824 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 23832;
		}
		sp = dbcSpell.LookupEntryForced( 23825 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 35708;
		}
		//and the rest
		sp = dbcSpell.LookupEntryForced( 23784 );
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp = dbcSpell.LookupEntryForced( 23830 );
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp = dbcSpell.LookupEntryForced( 23831 );
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp = dbcSpell.LookupEntryForced( 23832 );
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp = dbcSpell.LookupEntryForced( 35708 );
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp = dbcSpell.LookupEntryForced( 23759 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		}
		sp = dbcSpell.LookupEntryForced( 23760 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		}
		sp = dbcSpell.LookupEntryForced( 23761 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		}
		sp = dbcSpell.LookupEntryForced( 23762 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		}
		sp = dbcSpell.LookupEntryForced( 23826 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		}
		sp = dbcSpell.LookupEntryForced( 23827 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		}
		sp = dbcSpell.LookupEntryForced( 23828 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		}
		sp = dbcSpell.LookupEntryForced( 23829 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		}
		for(uint32 i=23833;i<=23844;i++)
		{
			sp = dbcSpell.LookupEntryForced( i );
			//if( sp != NULL )
			{
				sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
				sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			}
		}
		sp = dbcSpell.LookupEntryForced( 35702 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->Effect[1] = 0; //hacks, we are handling this in another way
		}
		sp = dbcSpell.LookupEntryForced( 35703 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->Effect[1] = 0; //hacks, we are handling this in another way
		}
		sp = dbcSpell.LookupEntryForced( 35704 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->Effect[1] = 0; //hacks, we are handling this in another way
		}
		sp = dbcSpell.LookupEntryForced( 35705 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->Effect[1] = 0; //hacks, we are handling this in another way
		}
		sp = dbcSpell.LookupEntryForced( 35706 );
		//if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->Effect[1] = 0; //hacks, we are handling this in another way
		}

		//warlock - Soulshatter
		sp = dbcSpell.LookupEntryForced( 29858 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_REDUCE_THREAT_PERCENT;		//reduce by 50% -> no visual :(
			sp->chained_cast = dbcSpell.LookupEntryForced( 32835 );	//reduce by 50%	-> has visual effect also
		}

		//warlock - Drain Soul
		sp = dbcSpell.LookupEntryForced( 1120 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 30;
			sp->EffectTriggerSpell[2] = 1120;	//self proc = must break execution
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_DRAIN_SOUL;
		}
		sp = dbcSpell.LookupEntryForced( 8288 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 30;
			sp->EffectTriggerSpell[2] = 1120;	//self proc = must break execution
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_DRAIN_SOUL;
		}
		sp = dbcSpell.LookupEntryForced( 8289 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 30;
			sp->EffectTriggerSpell[2] = 1120;	//self proc = must break execution
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_DRAIN_SOUL;
		}
		sp = dbcSpell.LookupEntryForced( 11675 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 30;
			sp->EffectTriggerSpell[2] = 1120;	//self proc = must break execution
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_DRAIN_SOUL;
		}
		sp = dbcSpell.LookupEntryForced( 27217 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 30;
			sp->EffectTriggerSpell[2] = 1120;	//self proc = must break execution
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_DRAIN_SOUL;
		}
		sp = dbcSpell.LookupEntryForced( 47855 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 30;
			sp->EffectTriggerSpell[2] = 1120;	//self proc = must break execution
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_DRAIN_SOUL;
		}

		//warlock - Improved Drain Soul
		sp = dbcSpell.LookupEntryForced( 18213 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_TARGET_DIE;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 100;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 18371;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->Effect[2] = 0 ; //remove this effect
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_DRAIN_SOUL;
		}
		sp = dbcSpell.LookupEntryForced( 18372 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_TARGET_DIE ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 100;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 18371;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->Effect[2] = 0 ; //remove this effect
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_DRAIN_SOUL;
		}
		sp = dbcSpell.LookupEntryForced( 18372 );
		//if( sp != NULL )
			sp->spell_id_client = sp->Id;

		//Nightfall
		sp = dbcSpell.LookupEntryForced( 18094 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_CORRUPTION;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_DRAIN_LIFE;
		}
		sp = dbcSpell.LookupEntryForced( 18095 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_CORRUPTION;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_DRAIN_LIFE;
		}

		//warlock - Shadow Embrace
		sp = dbcSpell.LookupEntryForced( 32385 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HAUNT;
		}
		sp = dbcSpell.LookupEntryForced( 32387 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HAUNT;
		}
		sp = dbcSpell.LookupEntryForced( 32392 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HAUNT;
		}
		sp = dbcSpell.LookupEntryForced( 32393 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HAUNT;
		}
		sp = dbcSpell.LookupEntryForced( 32394 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SHADOW_BOLT;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_HAUNT;
		}

		//warlock - soul leech
		sp = dbcSpell.LookupEntryForced( 30293 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 30294;
			sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 30295 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 30294;
			sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 30296 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 30294;
			sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 30294 );
		//if( sp != NULL )
		{
			sp->spell_id_client = sp->Id;	//do not let proc overrite us
			sp->c_is_flags |= SPELL_FLAG_IS_PROC_TRIGGER_PROC;
		}

		//warlock - Improved Soul Leech
		sp = dbcSpell.LookupEntryForced( 54117 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 57669;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SOUL_LEECH;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 54300;
		}
		sp = dbcSpell.LookupEntryForced( 54118 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 57669;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SOUL_LEECH;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 59117;
		}
		sp = dbcSpell.LookupEntryForced( 54300 );
		//if( sp != NULL )
			sp->EffectImplicitTargetB[0] = EFF_TARGET_PET;
		sp = dbcSpell.LookupEntryForced( 59117 );
		//if( sp != NULL )
			sp->EffectImplicitTargetB[0] = EFF_TARGET_PET;

		//warlock - Siphon Life
		sp = dbcSpell.LookupEntryForced( 63108 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 63106;
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_CORRUPTION;
		}
		sp = dbcSpell.LookupEntryForced( 63106 );
		//if( sp != NULL )
			sp->spell_id_client = sp->Id;	//do not let proc overrite us

		//warlock - Pyroclasm
		sp = dbcSpell.LookupEntryForced( 18073 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SEARING_PAIN;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_CONFLAGRATE;
		}
		sp = dbcSpell.LookupEntryForced( 18096 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SEARING_PAIN;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_CONFLAGRATE;
		}
		sp = dbcSpell.LookupEntryForced( 63245 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_SEARING_PAIN;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_CONFLAGRATE;
		}

	//////////////////////////////////////////
	// DRUID								//
	//////////////////////////////////////////
	//Furor
	sp = dbcSpell.LookupEntryForced( 17056 );
	//if( sp != NULL )
		sp->RequiredShapeShift = (1 << (FORM_CAT-1)) | (1 << (FORM_BEAR-1)) | (1 << (FORM_DIREBEAR-1)) | (1 << (FORM_MOONKIN-1));
	sp = dbcSpell.LookupEntryForced( 17058 );
	//if( sp != NULL )
		sp->RequiredShapeShift = (1 << (FORM_CAT-1)) | (1 << (FORM_BEAR-1)) | (1 << (FORM_DIREBEAR-1)) | (1 << (FORM_MOONKIN-1));
	sp = dbcSpell.LookupEntryForced( 17059 );
	//if( sp != NULL )
		sp->RequiredShapeShift = (1 << (FORM_CAT-1)) | (1 << (FORM_BEAR-1)) | (1 << (FORM_DIREBEAR-1)) | (1 << (FORM_MOONKIN-1));
	sp = dbcSpell.LookupEntryForced( 17060 );
	//if( sp != NULL )
		sp->RequiredShapeShift = (1 << (FORM_CAT-1)) | (1 << (FORM_BEAR-1)) | (1 << (FORM_DIREBEAR-1)) | (1 << (FORM_MOONKIN-1));
	sp = dbcSpell.LookupEntryForced( 17061 );
	//if( sp != NULL )
		sp->RequiredShapeShift = (1 << (FORM_CAT-1)) | (1 << (FORM_BEAR-1)) | (1 << (FORM_DIREBEAR-1)) | (1 << (FORM_MOONKIN-1));
	//Druid: improved barkskin
	sp = dbcSpell.LookupEntryForced( 63410 );
	//if( sp != NULL )
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_2;
	sp = dbcSpell.LookupEntryForced( 63411 );
	//if( sp != NULL )
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_2;
	//Druid: Leader of the pack should not be removed by proc due to same namehash
	sp = dbcSpell.LookupEntryForced( 17007 );
	//if( sp != NULL )
		sp->NameHash = SPELL_HASH_LEADER_OF_THE_PACK_17007;
	sp = dbcSpell.LookupEntryForced( 24932 );
	//if( sp != NULL )
	{
		sp->RequiredShapeShift = (1 << (FORM_CAT-1)) | (1 << (FORM_BEAR-1)) | (1 << (FORM_DIREBEAR-1));
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 0;
		sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_RANGED_CRIT_ATTACK;
		sp->proc_interval = 6000;	//every 6 seconds
		sp->EffectTriggerSpell[1] = 34299;
	}
	//Improved Leader of the Pack
	sp = dbcSpell.LookupEntryForced( 34297 );
	//if( sp != NULL )
		sp->EffectMiscValue[0] = SMT_TRIGGER;	//-add the proc chance that had 0 until now

	// Insert druid spell fixes here
		//Infected Wounds
		sp = dbcSpell.LookupEntryForced(48483);
		//if(sp != NULL)
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced(48484);
		//if(sp != NULL)
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp = dbcSpell.LookupEntryForced(48485);
		//if(sp != NULL)
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;

		//King of the Jungle
		sp = dbcSpell.LookupEntryForced(48492);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_ENRAGE;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_TIGER_S_FURY;
			sp->EffectApplyAuraName[ 0 ] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[ 0 ] = 51185;
			sp->EffectApplyAuraName[ 1 ] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[ 1 ] = 51178;
		}
		sp = dbcSpell.LookupEntryForced(48494);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_ENRAGE;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_TIGER_S_FURY;
			sp->EffectApplyAuraName[ 0 ] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[ 0 ] = 51185;
			sp->EffectApplyAuraName[ 1 ] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[ 1 ] = 51178;
		}
		sp = dbcSpell.LookupEntryForced(48495);
		//if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_ENRAGE;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_TIGER_S_FURY;
			sp->EffectApplyAuraName[ 0 ] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[ 0 ] = 51185;
			sp->EffectApplyAuraName[ 1 ] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[ 1 ] = 51178;
		}

		sp = dbcSpell.LookupEntryForced(51185); //enrage proc
		sp2 = dbcSpell.LookupEntryForced(5229); //enrage
		//if(sp != NULL)
			sp->DurationIndex = sp2->DurationIndex;

		//Starfall
		sp2 = dbcSpell.LookupEntryForced( 50286 );
		sp = dbcSpell.LookupEntryForced( 48505 );
		//if( sp != NULL )
		{
			sp->EffectTriggerSpell[0] = 50288;
//			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_MOVEMENT;
//			sp->RequiredShapeShift = (1 << (FORM_CUSTOM_NORMAL-1));
		}
		sp = dbcSpell.LookupEntryForced( 50288 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_ALL_ENEMY_IN_AREA;
			sp->EffectRadiusIndex[0] = sp2->EffectRadiusIndex[0];
			SetAllSpellCoef(sp,0.08f);
			sp->MaxTargets = 2;
//			sp->spell_can_crit = false;		//wowhead says it does crit
//			sp->spell_DOT_can_crit = false;
		}
		sp = dbcSpell.LookupEntryForced( 53199 );
		//if( sp != NULL )
		{
			sp->EffectTriggerSpell[0] = 53191;
//			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_MOVEMENT;
//			sp->RequiredShapeShift = (1 << (FORM_CUSTOM_NORMAL-1));
		}
		sp = dbcSpell.LookupEntryForced( 53191 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_ALL_ENEMY_IN_AREA;
			sp->EffectRadiusIndex[0] = sp2->EffectRadiusIndex[0];
			SetAllSpellCoef(sp,0.08f);
			sp->MaxTargets = 2;
//			sp->spell_can_crit = false;		//wowhead says it does crit
//			sp->spell_DOT_can_crit = false;
		}
		sp = dbcSpell.LookupEntryForced( 53200 );
		//if( sp != NULL )
		{
			sp->EffectTriggerSpell[0] = 53194;
//			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_MOVEMENT;
//			sp->RequiredShapeShift = (1 << (FORM_CUSTOM_NORMAL-1));
		}
		sp = dbcSpell.LookupEntryForced( 53194 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_ALL_ENEMY_IN_AREA;
			sp->EffectRadiusIndex[0] = sp2->EffectRadiusIndex[0];
			SetAllSpellCoef(sp,0.08f);
			sp->MaxTargets = 2;
//			sp->spell_can_crit = false;		//wowhead says it does crit
//			sp->spell_DOT_can_crit = false;
		}
		sp = dbcSpell.LookupEntryForced( 53201 );
		//if( sp != NULL )
		{
			sp->EffectTriggerSpell[0] = 53195;
//			sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_MOVEMENT;
//			sp->RequiredShapeShift = (1 << (FORM_CUSTOM_NORMAL-1));
		}
		sp = dbcSpell.LookupEntryForced( 53195 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
			sp->EffectImplicitTargetB[0] = EFF_TARGET_ALL_ENEMY_IN_AREA;
			sp->EffectRadiusIndex[0] = sp2->EffectRadiusIndex[0];
			SetAllSpellCoef(sp,0.08f);
			sp->MaxTargets = 2;
//			sp->spell_can_crit = false;		//wowhead says it does crit
//			sp->spell_DOT_can_crit = false;
		}
		//Earth and Moon
		sp = dbcSpell.LookupEntryForced( 48506 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_WRATH;
			sp->ProcOnNameHash[1] = SPELL_HASH_STARFIRE;
		}
		sp = dbcSpell.LookupEntryForced( 48510 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_WRATH;
			sp->ProcOnNameHash[1] = SPELL_HASH_STARFIRE;
		}
		sp = dbcSpell.LookupEntryForced( 48511 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_WRATH;
			sp->ProcOnNameHash[1] = SPELL_HASH_STARFIRE;
		}

		//Savage Defense
		sp = dbcSpell.LookupEntryForced( 62600 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 62606 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
			sp->procCharges = 1;
		}

		sp = dbcSpell.LookupEntryForced( 24866 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 24864;
		}

		//Druid: Dire Bear Form (Passive)
		//! this spell scales with level
		sp = dbcSpell.LookupEntryForced( 9635 );
		//if( sp != NULL )
			sp->SpellGroupType[2] = 0;	//maybe some spell is moding this ? Players report that bear form gives huge amount of bonuses

		//Druid: Feral Swiftness
		sp = dbcSpell.LookupEntryForced( 17002 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 24867;
			sp->RequiredShapeShift = (1<<(FORM_CAT-1));
		}
		sp = dbcSpell.LookupEntryForced( 24866 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 24864;
			sp->RequiredShapeShift = (1<<(FORM_CAT-1));
		}
		sp = dbcSpell.LookupEntryForced( 24864 );
		//if( sp != NULL )
			sp->RequiredShapeShift = (1<<(FORM_BEAR-1))|(1<<(FORM_DIREBEAR-1))|(1<<(FORM_CAT-1));
		sp = dbcSpell.LookupEntryForced( 24867 );
		//if( sp != NULL )
			sp->RequiredShapeShift = (1<<(FORM_BEAR-1))|(1<<(FORM_DIREBEAR-1))|(1<<(FORM_CAT-1));

		//Owlkin Frenzy
		sp = dbcSpell.LookupEntryForced( 48389 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 48392 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 48393 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}

		//Eclipse
		sp = dbcSpell.LookupEntryForced( 48516 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_WRATH;
			sp->ProcOnNameHash[1] = SPELL_HASH_STARFIRE;
			sp->EffectTriggerSpell[0]   =   48517;//Damage Done by Wrath 20% more
			sp->EffectTriggerSpell[1]   =   48518;//Crit Chance of Starfire 30% more
			sp->procChance  =   33;
			sp->proc_interval   =   30000;
		}
		sp = dbcSpell.LookupEntryForced( 48521 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_WRATH;
			sp->ProcOnNameHash[1] = SPELL_HASH_STARFIRE;
			sp->EffectTriggerSpell[0]   =   48517;//Damage Done by Wrath 20% more
			sp->EffectTriggerSpell[1]   =   48518;//Crit Chance of Starfire 30% more
			sp->procChance  =   66;
			sp->proc_interval   =   30000;
		}
		sp = dbcSpell.LookupEntryForced( 48525 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_WRATH;
			sp->ProcOnNameHash[1] = SPELL_HASH_STARFIRE;
			sp->EffectTriggerSpell[0]   =   48517;//Damage Done by Wrath 20% more
			sp->EffectTriggerSpell[1]   =   48518;//Crit Chance of Starfire 30% more
			sp->procChance  =   100;
			sp->proc_interval   =   30000;
		}

		//Druid: Natural Perfection
		sp = dbcSpell.LookupEntryForced( 33881 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
		sp = dbcSpell.LookupEntryForced( 33882 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
		sp = dbcSpell.LookupEntryForced( 33883 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;

		//Druid: Frenzied Regeneration
		sp = dbcSpell.LookupEntryForced( 22842 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 22845;
		}
/*		sp = dbcSpell.LookupEntryForced( 22895 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 22845;
		}
		sp = dbcSpell.LookupEntryForced( 22896 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 22845;
		}
		sp = dbcSpell.LookupEntryForced( 26999 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 22845;
		}*/

		//Typhoon - targettting should be around caster
		sp = dbcSpell.LookupEntryForced( 61391 ); 
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_LOCATION_TO_SUMMON;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_LOCATION_TO_SUMMON;
		}
		sp = dbcSpell.LookupEntryForced( 61390 ); 
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_LOCATION_TO_SUMMON;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_LOCATION_TO_SUMMON;
		}
		sp = dbcSpell.LookupEntryForced( 61388 ); 
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_LOCATION_TO_SUMMON;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_LOCATION_TO_SUMMON;
		}
		sp = dbcSpell.LookupEntryForced( 61387 ); 
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_LOCATION_TO_SUMMON;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_LOCATION_TO_SUMMON;
		}
		sp = dbcSpell.LookupEntryForced( 53227 ); 
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_LOCATION_TO_SUMMON;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_LOCATION_TO_SUMMON;
		}

		//Druid - Celestial Focus
		sp = dbcSpell.LookupEntryForced( 16850 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 16923 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 16924 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
		}

		//druid - Primal Fury (talent)
		sp = dbcSpell.LookupEntryForced( 37116 );
		//if( sp != NULL )
			sp->RequiredShapeShift = 0;
		
		sp = dbcSpell.LookupEntryForced( 37117 );
		//if( sp != NULL )
			sp->RequiredShapeShift = 0;

		//druid - Blood Frenzy (proc)
		sp = dbcSpell.LookupEntryForced( 16954 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;

		sp = dbcSpell.LookupEntryForced( 16952 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CRIT_ATTACK;

		//druid - Primal Fury (proc)
		sp = dbcSpell.LookupEntryForced( 16961 );
		//if( sp != NULL ) 
			sp->procFlags = PROC_ON_CRIT_ATTACK;

		sp = dbcSpell.LookupEntryForced( 16958 );
		//if( sp != NULL ) 
			sp->procFlags = PROC_ON_CRIT_ATTACK;

		//Bash - Interrupt effect
		sp = dbcSpell.LookupEntryForced( 5211 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 32747;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		}
		sp = dbcSpell.LookupEntryForced( 6798 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 32747;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		}
		sp = dbcSpell.LookupEntryForced( 8983 );
		//if( sp != NULL )
		{
			sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[1] = 32747;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		}

		//druid - Intensity
		sp = dbcSpell.LookupEntryForced( 17106 );
		//if( sp != NULL )
		{
		   sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		   sp->procFlags = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 17107 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			 sp->procFlags = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 17108 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL;
		}
		//Nature's Grasp
		sp = dbcSpell.LookupEntryForced( 16689 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6; 
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 339; 
			sp->Effect[1] = 0; 
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		}
		sp = dbcSpell.LookupEntryForced( 16810 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6; 
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 1062; 
			sp->Effect[1] = 0; 
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		}
		sp = dbcSpell.LookupEntryForced( 16811 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6; 
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 5195; 
			sp->Effect[1] = 0; 
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		}
		sp = dbcSpell.LookupEntryForced( 16812 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6; 
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 5196; 
			sp->Effect[1] = 0; 
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		}
		sp = dbcSpell.LookupEntryForced( 16813 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6; 
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 9852; 
			sp->Effect[1] = 0; 
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		}
		sp = dbcSpell.LookupEntryForced( 17329 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6; 
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 9853; 
			sp->Effect[1] = 0; 
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		}
		sp = dbcSpell.LookupEntryForced( 27009 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6; 
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 26989; 
			sp->Effect[1] = 0; 
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		}
		sp = dbcSpell.LookupEntryForced( 53312 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6; 
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 53313; 
			sp->Effect[1] = 0; 
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM ;
			sp->procFlags2 |= PROC2_REMOVEONUSE;
			sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		}
		//pounce
		sp = dbcSpell.LookupEntryForced( 9007 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
		}
		sp = dbcSpell.LookupEntryForced( 9824 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
		}
		sp = dbcSpell.LookupEntryForced( 9826 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
		}
		sp = dbcSpell.LookupEntryForced( 27007 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_BLEEDING;
		}
		//rip
		sp = dbcSpell.LookupEntryForced( 1079 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 9492 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 9493 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 9752 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 9894 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 9896 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 27008 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		//rake
		sp = dbcSpell.LookupEntryForced( 1822 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 1823 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 1824 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 9904 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		sp = dbcSpell.LookupEntryForced( 27003 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;
		//lacerate
		sp = dbcSpell.LookupEntryForced( 33745 );
		//if( sp != NULL )
			sp->MechanicsType = MECHANIC_BLEEDING;

		//Pounce 
		sp = dbcSpell.LookupEntryForced( 9005 );
		//if( sp != NULL )
			sp->AttributesExB &= ~FLAGS3_REQ_BEHIND_TARGET; //not valid in 3.3.3 ?
		sp = dbcSpell.LookupEntryForced( 9823 );
		//if( sp != NULL )
			sp->AttributesExB &= ~FLAGS3_REQ_BEHIND_TARGET; //not valid in 3.3.3 ?
		sp = dbcSpell.LookupEntryForced( 9827 );
		//if( sp != NULL )
			sp->AttributesExB &= ~FLAGS3_REQ_BEHIND_TARGET; //not valid in 3.3.3 ?
		sp = dbcSpell.LookupEntryForced( 27006 );
		//if( sp != NULL )
			sp->AttributesExB &= ~FLAGS3_REQ_BEHIND_TARGET; //not valid in 3.3.3 ?
		sp = dbcSpell.LookupEntryForced( 49803 );
		//if( sp != NULL )
			sp->AttributesExB &= ~FLAGS3_REQ_BEHIND_TARGET; //not valid in 3.3.3 ?

		//Pounce Bleed
		sp = dbcSpell.LookupEntryForced( 9007 );
		//if( sp != NULL )
			sp->DurationIndex = 85;
		sp = dbcSpell.LookupEntryForced( 9824 );
		//if( sp != NULL )
			sp->DurationIndex = 85;
		sp = dbcSpell.LookupEntryForced( 9826 );
		//if( sp != NULL )
			sp->DurationIndex = 85;
		sp = dbcSpell.LookupEntryForced( 27007 );
		//if( sp != NULL )
			sp->DurationIndex = 85;

		//Druid: Master Shapeshifter
		sp = dbcSpell.LookupEntryForced( 48411 );
		//if( sp != NULL )
			sp->RequiredShapeShift = (1<<(FORM_TREE-1)) | (1<<(FORM_BEAR-1)) | (1<<(FORM_CAT-1)) | (1<<(FORM_MOONKIN-1));
		sp = dbcSpell.LookupEntryForced( 48412 );
		//if( sp != NULL )
			sp->RequiredShapeShift = (1<<(FORM_TREE-1)) | (1<<(FORM_BEAR-1)) | (1<<(FORM_CAT-1)) | (1<<(FORM_MOONKIN-1));
		sp = dbcSpell.LookupEntryForced( 48418 );
		//if( sp != NULL )
			sp->RequiredShapeShift = (1<<(FORM_BEAR-1));
		sp = dbcSpell.LookupEntryForced( 48420 );
		//if( sp != NULL )
			sp->RequiredShapeShift = (1<<(FORM_CAT-1));
		sp = dbcSpell.LookupEntryForced( 48421 );
		//if( sp != NULL )
			sp->RequiredShapeShift = (1<<(FORM_MOONKIN-1));
		sp = dbcSpell.LookupEntryForced( 48422 );
		//if( sp != NULL )
			sp->RequiredShapeShift = (1<<(FORM_TREE-1));

		//Druid: Improved Tree of Life
		sp = dbcSpell.LookupEntryForced( 48535 );
		//if( sp != NULL )
			sp->RequiredShapeShift = (1<<(FORM_TREE-1));
		sp = dbcSpell.LookupEntryForced( 48536 );
		//if( sp != NULL )
			sp->RequiredShapeShift = (1<<(FORM_TREE-1));
		sp = dbcSpell.LookupEntryForced( 48537 );
		//if( sp != NULL )
			sp->RequiredShapeShift = (1<<(FORM_TREE-1));

		//Druid: Brambles
		sp = dbcSpell.LookupEntryForced( 16836 );
		//if( sp != NULL )
		{
			//mod Thorns and Entangling Roots
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_DAMAGE_DONE;	//hmm, only lvl 2 is messed up by blizz
			sp->EffectSpellGroupRelation[0][0] = sp->EffectSpellGroupRelation[0][0] | sp->EffectSpellGroupRelation[1][0];
			sp->EffectSpellGroupRelation[0][1] = sp->EffectSpellGroupRelation[0][1] | sp->EffectSpellGroupRelation[1][1];
			sp->EffectSpellGroupRelation[0][2] = sp->EffectSpellGroupRelation[0][2] | sp->EffectSpellGroupRelation[1][2];
			//mod force of nature
			sp->EffectMiscValue[1] = SMT_DAMAGE_DONE;	//hmm, only lvl 2 is messed up by blizz
			sp->EffectBasePoints[1] = sp->EffectBasePoints[2];
			sp->EffectSpellGroupRelation[1][0] = 0;
			sp->EffectSpellGroupRelation[1][1] = 512;
			//register prof for force of nature
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->EffectTriggerSpell[2] = 50411;
			sp->proc_interval = 1;
		}
		sp = dbcSpell.LookupEntryForced( 16839 );
		//if( sp != NULL )
		{
			//mod Thorns and Entangling Roots
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_DAMAGE_DONE;	//hmm, only lvl 2 is messed up by blizz
			sp->EffectSpellGroupRelation[0][0] = sp->EffectSpellGroupRelation[0][0] | sp->EffectSpellGroupRelation[1][0];
			sp->EffectSpellGroupRelation[0][1] = sp->EffectSpellGroupRelation[0][1] | sp->EffectSpellGroupRelation[1][1];
			sp->EffectSpellGroupRelation[0][2] = sp->EffectSpellGroupRelation[0][2] | sp->EffectSpellGroupRelation[1][2];
			//mod force of nature
			sp->EffectMiscValue[1] = SMT_DAMAGE_DONE;	//hmm, only lvl 2 is messed up by blizz
			sp->EffectBasePoints[1] = sp->EffectBasePoints[2];
			sp->EffectSpellGroupRelation[1][0] = 0;
			sp->EffectSpellGroupRelation[1][1] = 512;
			//register prof for force of nature
			//attacks done to you while you have Barkskin active have a $s3% chance to daze the target for 3 sec.
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->EffectTriggerSpell[2] = 50411;
			sp->proc_interval = 1;
		}
		sp = dbcSpell.LookupEntryForced( 16840 );
		//if( sp != NULL )
		{
			//mod Thorns and Entangling Roots
			sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
			sp->EffectMiscValue[0] = SMT_DAMAGE_DONE;	//hmm, only lvl 2 is messed up by blizz
			sp->EffectSpellGroupRelation[0][0] = sp->EffectSpellGroupRelation[0][0] | sp->EffectSpellGroupRelation[1][0];
			sp->EffectSpellGroupRelation[0][1] = sp->EffectSpellGroupRelation[0][1] | sp->EffectSpellGroupRelation[1][1];
			sp->EffectSpellGroupRelation[0][2] = sp->EffectSpellGroupRelation[0][2] | sp->EffectSpellGroupRelation[1][2];
			//mod force of nature
			sp->EffectMiscValue[1] = SMT_DAMAGE_DONE;	//hmm, only lvl 2 is messed up by blizz
			sp->EffectBasePoints[1] = sp->EffectBasePoints[2];
			sp->EffectSpellGroupRelation[1][0] = 0;
			sp->EffectSpellGroupRelation[1][1] = 512;
			//register prof for force of nature
			//attacks done to you while you have Barkskin active have a $s3% chance to daze the target for 3 sec.
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK_VICTIM;
			sp->EffectTriggerSpell[2] = 50411;
			sp->proc_interval = 1;
		}
		//the treant proc spell
		sp = dbcSpell.LookupEntryForced( 50419 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_MELEE_ATTACK;

		//Druid: Natural Shapeshifter
		sp = dbcSpell.LookupEntryForced( 16833 );
		//if( sp != NULL )
			sp->DurationIndex = 21;
		sp = dbcSpell.LookupEntryForced( 16834 );
		//if( sp != NULL )
			sp->DurationIndex = 21;
		sp = dbcSpell.LookupEntryForced( 16835 );
		//if( sp != NULL )
			sp->DurationIndex = 21;

		// druid - Naturalist
		sp = dbcSpell.LookupEntryForced( 17069 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
			sp->EffectMiscValue[1] = 1;  
		}
		sp = dbcSpell.LookupEntryForced( 17070 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
			sp->EffectMiscValue[1] = 1; 
		}
		sp = dbcSpell.LookupEntryForced( 17071 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
			sp->EffectMiscValue[1] = 1; 
		}
		sp = dbcSpell.LookupEntryForced( 17072 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
			sp->EffectMiscValue[1] = 1;
		}
		sp = dbcSpell.LookupEntryForced( 17073 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
			sp->EffectMiscValue[1] = 1; 
		}

		// druid - Nature's Grace
		sp = dbcSpell.LookupEntryForced( 16880 );
		//if( sp != NULL )
		{
            sp->procFlags = PROC_ON_SPELL_CRIT_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 61345 );
		//if( sp != NULL )
		{
            sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 61346 );
		//if( sp != NULL )
		{
            sp->procFlags = PROC_ON_SPELL_CRIT_HIT ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}

		// Druid: Omen of Clarity
		sp = dbcSpell.LookupEntryForced( 16864 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_CRIT_ATTACK | PROC_ON_CAST_SPELL;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->proc_interval = 20000;	//3ppm
		}
		sp = dbcSpell.LookupEntryForced( 16870 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procCharges = 1;
			sp->proc_interval = 20000;
		}

		// Druid: Living Seed
		sp = dbcSpell.LookupEntryForced( 48496 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48504;
		}
		sp = dbcSpell.LookupEntryForced( 48499 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48504;
		}
		sp = dbcSpell.LookupEntryForced( 48500 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48504;
		}
		//this is applied on target !
		sp = dbcSpell.LookupEntryForced( 48504 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 48503;
		}
		//this is a proccharge spell that needs removal on trigger
		sp = dbcSpell.LookupEntryForced( 48503 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_HOSTILE_ACTION ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}

		uint32 mm = (1<<(FORM_BEAR-1))|(1<<(FORM_DIREBEAR-1))|(1<<(FORM_MOONKIN-1))|(1<<(FORM_CAT-1));

		//Predatory Strikes
		sp = dbcSpell.LookupEntryForced( 16972 );
		//if( sp != NULL )s
		{
			sp->RequiredShapeShift = mm;
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;	//we will test the casting spell manually
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 16974 );
		//if( sp != NULL )
		{
			sp->RequiredShapeShift = mm;
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;	//we will test the casting spell manually
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 16975 );
		//if( sp != NULL )
		{
			sp->RequiredShapeShift = mm;
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;	//we will test the casting spell manually
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}

		mm = (1<<(FORM_MOONKIN-1));
		//Moonkin Form (Passive)
		sp = dbcSpell.LookupEntryForced( 24905 );
		//if( sp != NULL )
			sp->RequiredShapeShift = mm;
		sp = dbcSpell.LookupEntryForced( 24907 );
		//if( sp != NULL )
			sp->RequiredShapeShift = mm;

		//Improved Moonkin Form
		sp = dbcSpell.LookupEntryForced( 50170 );
		//if( sp != NULL )
			sp->RequiredShapeShift = mm;
		sp = dbcSpell.LookupEntryForced( 50171 );
		//if( sp != NULL )
			sp->RequiredShapeShift = mm;
		sp = dbcSpell.LookupEntryForced( 50172 );
		//if( sp != NULL )
			sp->RequiredShapeShift = mm;

		//Faerie Fire (Feral)
		sp = dbcSpell.LookupEntryForced( 16857 );
		//if( sp != NULL )
		{
			sp->Effect[2] = SPELL_EFFECT_SCHOOL_DAMAGE;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SINGLE_ENEMY;
		}
	//////////////////////////////////////////
	// ITEMS								//
	//////////////////////////////////////////

	// Insert items spell fixes here

		//Vigilance of the Colossus
		sp = dbcSpell.LookupEntryForced( 33089 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_BLOCK_VICTIM ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		//throw ice - some quest item
		sp = dbcSpell.LookupEntryForced( 56099 );
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;	//maybe location of this GO ? 192124
		//Item - stonestatue - stone healing
		sp = dbcSpell.LookupEntryForced( 32790 );
		//if( sp != NULL )
			sp->DurationIndex = 5;	//5 minutes
		sp = dbcSpell.LookupEntryForced( 32788 );
		//if( sp != NULL )
			sp->DurationIndex = 5;	//5 minutes
		sp = dbcSpell.LookupEntryForced( 32787 );
		//if( sp != NULL )
			sp->DurationIndex = 5;	//5 minutes
		sp = dbcSpell.LookupEntryForced( 32253 );
		//if( sp != NULL )
			sp->DurationIndex = 5;	//5 minutes
		sp = dbcSpell.LookupEntryForced( 32792 );
		//if( sp != NULL )
			sp->DurationIndex = 5;	//5 minutes

		//Item - Shadowmourne Legendary
		sp = dbcSpell.LookupEntryForced( 71903 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 71905;
		}
		sp = dbcSpell.LookupEntryForced( 71904 );//chaos bane
		//if( sp != NULL )
			sp->EffectImplicitTargetB[0] = EFF_TARGET_LOCATION_TO_SUMMON;	//land under caster

		//Compact Harvest Reaper
		sp = dbcSpell.LookupEntryForced( 4078 );
		//if( sp != NULL )
		{
			sp->DurationIndex = 6;
		}

		//Graccu's Mince Meat Fruitcake
		sp = dbcSpell.LookupEntryForced(25990);
		//if( sp != NULL )
		{
			sp->EffectAmplitude[1] = 1000;
		}

		//Extract Gas 
		sp = dbcSpell.LookupEntryForced( 30427 );
		//if( sp != NULL )
		{
			sp->Effect[0] = SPELL_EFFECT_DUMMY;
		}

		//Relic - Idol of the Unseen Moon
		sp = dbcSpell.LookupEntryForced( 43739 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 43740;
		}

		//Lunar Grace - Idol of the Unseen Moon proc
		sp = dbcSpell.LookupEntryForced( 43740 );
		//if( sp != NULL )
		{
			sp->ProcOnNameHash[0] = SPELL_HASH_MOONFIRE;
		}

		//Relic - Idol of Terror
		sp = dbcSpell.LookupEntryForced( 43737 );
		//if( sp != NULL )
		{    
			sp->proc_interval = 10001; //block proc when is already active.. (Primal Instinct duration = 10 sec)
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 43738;
			sp->procChance=85;
		}

		//Primal Instinct - Idol of Terror proc
		sp = dbcSpell.LookupEntryForced( 43738 );
		//if( sp != NULL )
		{    
			sp->self_cast_only = true;
			sp->ProcOnNameHash[0] = SPELL_HASH_MANGLE__CAT_;
			sp->ProcOnNameHash[1] = SPELL_HASH_MANGLE__BEAR_;
		}

		//Tome of Fiery Redemption
		sp = dbcSpell.LookupEntryForced( 37197 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 37198;
			sp->procChance = 15;
		}

		//Thunderfury
		sp = dbcSpell.LookupEntryForced( 21992 );
		//if( sp != NULL )
		{
			sp->Effect[2] = SPELL_EFFECT_TRIGGER_SPELL;
			sp->EffectTriggerSpell[2] = 27648;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
		}

		//Energized 
		sp = dbcSpell.LookupEntryForced( 43750 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LIGHTNING_BOLT;
		}

		//Spell Haste Trinket
		sp = dbcSpell.LookupEntryForced( 33297 ); 
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}

		//Spell Focus Trigger (Mystical Skyfire Diamond)
		sp = dbcSpell.LookupEntryForced( 32837 );
		//if( sp != NULL )
			sp->procChance = 15;

		// Band of the Eternal Sage
		sp = dbcSpell.LookupEntryForced( 35083 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;

		// Band of the Eternal Restorer 
		sp = dbcSpell.LookupEntryForced( 35086 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;

		// Ashtongue Talisman of Shadows 
		sp = dbcSpell.LookupEntryForced( 40478 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_CORRUPTION;
		}

		// Ashtongue Talisman of Swiftness
		sp = dbcSpell.LookupEntryForced( 40485 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_STEADY_SHOT;
		}

		// Ashtongue Talisman of Valor
		sp = dbcSpell.LookupEntryForced( 40458 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_MORTAL_STRIKE;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_BLOODTHIRST;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_SHIELD_SLAM;
		}

		// Memento of Tyrande
		sp = dbcSpell.LookupEntryForced( 37655 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;

		// Ashtongue Talisman of Insight
		sp = dbcSpell.LookupEntryForced( 40482 );
		//if( sp != NULL )
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;

		//Ashtongue Talisman of Equilibrium
		sp = dbcSpell.LookupEntryForced( 40442 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = 40;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectTriggerSpell[0] = 40452;
			sp->maxstack = 1;
			sp->Effect[1] = 6;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = 25;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectTriggerSpell[1] = 40445;
			sp->maxstack = 1;
			sp->Effect[2] = 6;
			sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = 25;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectTriggerSpell[2] = 40446;
			sp->maxstack = 1;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_MANGLE__BEAR_;
			sp->ProcOnNameHash[ 1 ] = SPELL_HASH_MANGLE__CAT_;
			sp->ProcOnNameHash[ 2 ] = SPELL_HASH_STARFIRE;
		}

		//Ashtongue Talisman of Acumen
		sp = dbcSpell.LookupEntryForced( 40438 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = 10;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectTriggerSpell[0] = 40441;
			sp->maxstack = 1;
			sp->Effect[1] = 6;
			sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = 10;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectTriggerSpell[1] = 40440;
			sp->maxstack = 1;
		}
		// Drums of war targets sorounding party members instead of us
		sp = dbcSpell.LookupEntryForced( 35475 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}
		// Symbol of Hope targets sorounding party members instead of us
/*		sp = dbcSpell.LookupEntryForced( 32548 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}*/

		// Drums of Battle targets sorounding party members instead of us
		sp = dbcSpell.LookupEntryForced( 35476 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}

		// Drums of Panic targets sorounding creatures instead of us
		sp = dbcSpell.LookupEntryForced( 35474 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}

		// Drums of Restoration targets sorounding party members instead of us
		sp = dbcSpell.LookupEntryForced( 35478 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}
		// Drums of Speed targets sorounding party members instead of us
		sp = dbcSpell.LookupEntryForced( 35477 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}

		// Dragonspine Trophy - Magtheridon Melee Trinket
 		sp = dbcSpell.LookupEntryForced( 34774 );
		//if( sp != NULL )
		{
			sp->procChance = 6;
			sp->procFlags  = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->proc_interval = uint32(60000 / 1.5f);
		}
		// Romulo's Poison
 		sp = dbcSpell.LookupEntryForced( 34586 );
		//if( sp != NULL )
		{
			sp->procChance = 6;
			sp->procFlags  = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->proc_interval = uint32(60000 / 1.5f);
		}
		//Ashtongue Talisman of Lethality
		sp = dbcSpell.LookupEntryForced( 40460 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = 100;	//well it is combo point based
			sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
			sp->EffectTriggerSpell[0] = 40461;
//			sp->maxstack = 1;
		}

		//Serpent-Coil Braid
		sp = dbcSpell.LookupEntryForced( 37447 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = 100;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectTriggerSpell[0] = 37445;
			sp->maxstack = 1;
		}

		// Band of the Eternal Champion
		sp = dbcSpell.LookupEntryForced( 35080 );
		//if( sp != NULL )
		{
			sp->procFlags  = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->proc_interval = 60000;
		}
		// Band of the Eternal Sage
		sp = dbcSpell.LookupEntryForced( 35083 );
		//if( sp != NULL )
		{
			sp->procFlags  = PROC_ON_CAST_SPELL;
			sp->proc_interval = 60000;
		}
		// Band of the Eternal Restorer
		sp = dbcSpell.LookupEntryForced( 35086 );
		//if( sp != NULL )
		{
			sp->procFlags  = PROC_ON_CAST_SPELL;
			sp->proc_interval = 60000;
		}
		// Band of the Eternal Defender
		sp = dbcSpell.LookupEntryForced( 35077 );
		//if( sp != NULL )
		{
			sp->procFlags  = PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
			sp->proc_interval = 60000;
		}	

		//Item Set: Malorne Harness
		sp = dbcSpell.LookupEntryForced( 37306 );
		//if( sp != NULL )
		{
			sp->procChance = 4;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		}
		sp = dbcSpell.LookupEntryForced( 37311 );
		//if( sp != NULL )
		{
			sp->procChance = 4;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		}

		//Item Set: Deathmantle
		sp = dbcSpell.LookupEntryForced( 37170 );
		//if( sp != NULL )
		{
			sp->procChance = 4;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		}

		//Item Set: Netherblade
		sp = dbcSpell.LookupEntryForced( 37168 );
		//if( sp != NULL )
		{
			sp->procChance = 15;
			//sp->procFlags = PROC_ON_CAST_SPELL; Need new flag - PROC_ON_FINISH_MOVE;
		}

		//Item Set: Tirisfal Regalia
		sp = dbcSpell.LookupEntryForced( 37443 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		}

		//Item Set: Avatar Regalia
		sp = dbcSpell.LookupEntryForced( 37600 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 6;
		}

		//Item Set: Incarnate Raiment
		sp = dbcSpell.LookupEntryForced( 37568 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FLASH_HEAL;
		}

		//Item Set: Voidheart Raiment
		sp = dbcSpell.LookupEntryForced( 37377 );
		//if( sp != NULL )
		{
			sp->Effect[0] = 6;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = 5;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->proc_interval = 20;
			sp->EffectTriggerSpell[0] = 37379;
		}
		sp = dbcSpell.LookupEntryForced( 39437 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procChance = 20;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->proc_interval = 2000;
			sp->EffectTriggerSpell[0] = 37378;
		}

		//Item Set: Cataclysm Raiment
		sp = dbcSpell.LookupEntryForced( 37227 );
		//if( sp != NULL )
		{
			sp->proc_interval = 60000;
			sp->procChance = 100;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		}

		//Item Set: Cataclysm Regalia
		sp = dbcSpell.LookupEntryForced( 37228 );
		//if( sp != NULL )
		{
			sp->procChance = 7;
			sp->procFlags = PROC_ON_CAST_SPELL;
		}
		sp = dbcSpell.LookupEntryForced( 37237 );
		//if( sp != NULL )
		{
			sp->procChance = 25;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_LIGHTNING_BOLT;
		}

		//Item Set: Cataclysm Harness
		sp = dbcSpell.LookupEntryForced( 37239 );
		//if( sp != NULL )
		{
			sp->procChance = 2;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		}

		//Item Set: Cyclone Regalia
		sp = dbcSpell.LookupEntryForced( 37213 );
		//if( sp != NULL )
		{
			sp->procChance = 11;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		}

		//Item Set: Crystalforge Armor
		sp = dbcSpell.LookupEntryForced( 37191 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HOLY_SHIELD;
		}

		//Item Set: Crystalforge Battlegear
		sp = dbcSpell.LookupEntryForced( 37195 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 6;
		}

		//Item Set: Crystalforge Raiment
		sp = dbcSpell.LookupEntryForced( 37189 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->proc_interval = 60000;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_FLASH_OF_LIGHT;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_HOLY_LIGHT;
		}
		sp = dbcSpell.LookupEntryForced( 37188 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
		}

		//Item Set: Destroyer Armor
		sp = dbcSpell.LookupEntryForced( 37525 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
			sp->procChance = 7;
		}

		//Item Set: Destroyer Battlegear
		sp = dbcSpell.LookupEntryForced( 37528 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 100;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_OVERPOWER;
		}

		//Item Set: Warbringer Armor
		sp = dbcSpell.LookupEntryForced( 37516 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 100;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_REVENGE;
		}

		//all Drums 
		sp = dbcSpell.LookupEntryForced( 35474 );
		//if( sp != NULL )
		{
			sp->RequiredShapeShift = 0;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}
		sp = dbcSpell.LookupEntryForced( 35475 );
		//if( sp != NULL )
		{
			sp->RequiredShapeShift = 0;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}
		sp = dbcSpell.LookupEntryForced( 35476 );
		//if( sp != NULL )
		{
			sp->RequiredShapeShift = 0;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}
		sp = dbcSpell.LookupEntryForced( 35477 );
		//if( sp != NULL )
		{
			sp->RequiredShapeShift = 0;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}
		sp = dbcSpell.LookupEntryForced( 35478 );
		//if( sp != NULL )
		{
			sp->RequiredShapeShift = 0;
			sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
			sp->EffectImplicitTargetA[2] = 0;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetB[1] = 0;
			sp->EffectImplicitTargetB[2] = 0;
		}

		//this an on equip item spell(2824) :  ice arrow(29501)
		sp = dbcSpell.LookupEntryForced( 29501 );
		//if( sp != NULL )
		{
			sp->procChance = 30;//some say it is triggered every now and then
			sp->procFlags = PROC_ON_RANGED_ATTACK;
		}

		//Purify helboar meat
		sp = dbcSpell.LookupEntryForced( 29200 );
		//if( sp != NULL )
		{
			sp->Reagent[1] = 0;
			sp->ReagentCount[1] = 0;
			sp->Effect[0] = 24;
		}

		//Big Blizzard Bear
		sp = dbcSpell.LookupEntryForced( 58983 );
		sp2 = dbcSpell.LookupEntryForced( 41514 );
		//if( sp != NULL )
			SpellEntryEffectCopy(sp2,sp,2,2);//normal speed
		//Magic Broom
		sp = dbcSpell.LookupEntryForced( 47977 );
		sp2 = dbcSpell.LookupEntryForced( 41514 );
		//if( sp != NULL )
			SpellEntryEffectCopy(sp2,sp,2,2);//normal speed

		//Recently Bandaged
		sp = dbcSpell.LookupEntryForced( 11196 );
		//if( sp != NULL )
		{
			sp->MechanicsType = MECHANIC_HEALING;
			sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
			sp->ThreatForSpellCoef = 0;
		}
			
		// - Warrior - Warbringer Armor
		// 2 pieces: You have a chance each time you parry to gain Blade Turning, absorbing 200 damage for 15 sec.
		// SPELL ID = 37514 (http://www.wowhead.com/?spell=37514)

		sp = dbcSpell.LookupEntryForced( 37514 );
		//if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 37515;
			sp->procChance = 25;
		}
		
		//Thorium Grenade
		sp = dbcSpell.LookupEntryForced(19769);
		//if(sp != NULL)
		{
			sp->InterruptFlags |= ~(CAST_INTERRUPT_ON_MOVEMENT);
		}

		//M73 Frag Grenade
		sp = dbcSpell.LookupEntryForced(13808);
		//if(sp != NULL)
		{
			sp->InterruptFlags |= ~(CAST_INTERRUPT_ON_MOVEMENT);
		}

		//Iron Grenade
		sp = dbcSpell.LookupEntryForced(4068);
		//if(sp != NULL)
		{
			sp->InterruptFlags |= ~(CAST_INTERRUPT_ON_MOVEMENT);
		}

		//Frost Grenade
		sp = dbcSpell.LookupEntryForced(39965);
		//if(sp != NULL)
		{
			sp->InterruptFlags |= ~(CAST_INTERRUPT_ON_MOVEMENT);
		}

		//Adamantine Grenade
		sp = dbcSpell.LookupEntryForced(30217);
		//if(sp != NULL)
		{
			sp->InterruptFlags |= ~(CAST_INTERRUPT_ON_MOVEMENT);
		}
		
		//trinket death's verdict or death's choice ....rest of the TOC trinkets 
		sp = dbcSpell.LookupEntryForced( 67698 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 67752 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 67702 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE | PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->EffectTriggerSpell[0] = 67703;	//might get overwritten based on stat
			sp->procChance = 30;
			sp->proc_interval = 6000;
		}
		sp = dbcSpell.LookupEntryForced( 67771 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE | PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->EffectTriggerSpell[0] = 67772;	//might get overwritten based on stat
			sp->procChance = 30;
			sp->proc_interval = 6000;
		}
		//You gain a Mote of Flame each time you cause a damaging spell critical strike.  When you reach $s1 Motes, they will release, firing a Pillar of Flame for $67714s1 damage.  Mote of Flame cannot be gained more often than once every 2 sec.
		sp = dbcSpell.LookupEntryForced( 67712 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->EffectTriggerSpell[0] = 67713;	
			sp->proc_interval = 2000;
		}
		sp = dbcSpell.LookupEntryForced( 67758 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->EffectTriggerSpell[0] = 67759;	
			sp->proc_interval = 2000;
		}
		//Blood of the Old God
		sp = dbcSpell.LookupEntryForced( 64792 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_RANGED_CRIT_ATTACK;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		//Comet's Trail
		sp = dbcSpell.LookupEntryForced( 64786 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		//Mjolnir Runestone
		sp = dbcSpell.LookupEntryForced( 65020 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		//Rising Fury
		sp = dbcSpell.LookupEntryForced( 67747 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		//Dark Matter
		sp = dbcSpell.LookupEntryForced( 65025 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		//Flame of the Heavens
		sp = dbcSpell.LookupEntryForced( 64714 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		//Show of Faith
		sp = dbcSpell.LookupEntryForced( 64738 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		//Volatile Power
		sp = dbcSpell.LookupEntryForced( 67744 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		sp2 = dbcSpell.LookupEntryForced( 67743 );	//proc
		//if( sp2 != NULL )
			sp2->DurationIndex = sp->DurationIndex;

		//Jom Gabbar
		sp = dbcSpell.LookupEntryForced( 29602 );
		sp2 = dbcSpell.LookupEntryForced( 29604 );	//proc
		//if( sp2 != NULL )
			sp2->DurationIndex = sp->DurationIndex;

		//Rising Fury
		sp = dbcSpell.LookupEntryForced( 67738 );
		sp2 = dbcSpell.LookupEntryForced( 67737 );	//proc
		//if( sp2 != NULL )
			sp2->DurationIndex = sp->DurationIndex;

		//Volatile Power
		sp = dbcSpell.LookupEntryForced( 67736 );
		sp2 = dbcSpell.LookupEntryForced( 67735 );	//proc
		//if( sp2 != NULL )
			sp2->DurationIndex = sp->DurationIndex;


		//Hardening Armor
		sp = dbcSpell.LookupEntryForced( 67728 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		sp2 = dbcSpell.LookupEntryForced( 67727 );	//proc
		//if( sp2 != NULL )
			sp2->DurationIndex = sp->DurationIndex;
		//Hardening Armor
		sp = dbcSpell.LookupEntryForced( 67742 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		sp2 = dbcSpell.LookupEntryForced( 67741 );	//proc
		//if( sp2 != NULL )
			sp2->DurationIndex = sp->DurationIndex;
		//Meteoric Inspiration
		sp = dbcSpell.LookupEntryForced( 64999 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
		}
		sp2 = dbcSpell.LookupEntryForced( 65000 );	//proc
		//if( sp2 != NULL )
			sp2->DurationIndex = sp->DurationIndex;
		//Deadly Gladiator's Totem of Survival
		sp = dbcSpell.LookupEntryForced( 60572 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_EARTH_SHOCK;
			sp->ProcOnNameHash[1] = SPELL_HASH_FLAME_SHOCK;
			sp->ProcOnNameHash[2] = SPELL_HASH_FROST_SHOCK;
		}
		//Hateful Gladiator's Totem of Survival
		sp = dbcSpell.LookupEntryForced( 60571 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_EARTH_SHOCK;
			sp->ProcOnNameHash[1] = SPELL_HASH_FLAME_SHOCK;
			sp->ProcOnNameHash[2] = SPELL_HASH_FROST_SHOCK;
		}
		//LK Arena 4 Gladiator's Totem of Survival
		sp = dbcSpell.LookupEntryForced( 60573 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_EARTH_SHOCK;
			sp->ProcOnNameHash[1] = SPELL_HASH_FLAME_SHOCK;
			sp->ProcOnNameHash[2] = SPELL_HASH_FROST_SHOCK;
		}
		//LK Arena 5 Gladiator's Totem of Survival
		sp = dbcSpell.LookupEntryForced( 60574 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_EARTH_SHOCK;
			sp->ProcOnNameHash[1] = SPELL_HASH_FLAME_SHOCK;
			sp->ProcOnNameHash[2] = SPELL_HASH_FROST_SHOCK;
		}
		//Deadly Totem of Indomitability
		sp = dbcSpell.LookupEntryForced( 60548 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_LAVA_LASH;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//Hateful Totem of Indomitability
		sp = dbcSpell.LookupEntryForced( 60546 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_LAVA_LASH;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//LK Arena 4 Totem of Indomitability
		sp = dbcSpell.LookupEntryForced( 60550 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_LAVA_LASH;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//LK Arena 5 Totem of Indomitability
		sp = dbcSpell.LookupEntryForced( 60552 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_LAVA_LASH;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//Item - Shaman T9 Enhancement Relic (Lava Lash)
		sp = dbcSpell.LookupEntryForced( 67392 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_LAVA_LASH;
		}
		//Item - Shaman T9 Elemental Relic (Lightning Bolt)
		sp = dbcSpell.LookupEntryForced( 67386 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_LIGHTNING_BOLT;
		}
		//Totem of the Elemental Plane
		sp = dbcSpell.LookupEntryForced( 60770 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_LIGHTNING_BOLT;
		}
		//Item - Shaman T9 Restoration Relic (Chain Heal)
		sp = dbcSpell.LookupEntryForced( 67389 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CHAIN_HEAL;
		}
		//Nax 25 Melee Shaman Totem
		sp = dbcSpell.LookupEntryForced( 60765 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_STORMSTRIKE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//Deadly Gladiator's Libram of Fortitude
		sp = dbcSpell.LookupEntryForced( 60633 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CRUSADER_STRIKE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//Hateful Gladiator's Libram of Fortitude
		sp = dbcSpell.LookupEntryForced( 60632 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CRUSADER_STRIKE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//LK Arena 4 Gladiator's Libram of Fortitude
		sp = dbcSpell.LookupEntryForced( 60634 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CRUSADER_STRIKE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//LK Arena 5 Gladiator's Libram of Fortitude
		sp = dbcSpell.LookupEntryForced( 60635 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CRUSADER_STRIKE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//Item - Paladin T8 Protection Relic
		sp = dbcSpell.LookupEntryForced( 64955 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_HOLY_SHIELD;
		}
		//Item - Paladin T9 Holy Relic (Judgement)
		sp = dbcSpell.LookupEntryForced( 67363 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_HOLY_LIGHT;
		}
		//Item - Paladin T9 Protection Relic (Hammer of The Righteous)
		sp = dbcSpell.LookupEntryForced( 67379 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_HAMMER_OF_THE_RIGHTEOUS;
		}
		//Item - Paladin T9 Retribution Relic (Seal of Vengeance)
		sp = dbcSpell.LookupEntryForced( 67365 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
//			sp->procFlags2 = PROC2_TARGET_SELF;
//			sp->ProcOnNameHash[0] = SPELL_HASH_SEAL_OF_VENGEANCE;
//			sp->ProcOnNameHash[1] = SPELL_HASH_SEAL_OF_CORRUPTION;
			sp->ProcOnNameHash[0] = SPELL_HASH_HOLY_VENGEANCE;
			sp->ProcOnNameHash[1] = SPELL_HASH_BLOOD_CORRUPTION;
			sp->proc_interval = 20000;
		}
		//Libram of Obstruction
		sp = dbcSpell.LookupEntryForced( 60794 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[1] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
			sp->ProcOnNameHash[2] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
		}
		//Libram of Reciprocation
		sp = dbcSpell.LookupEntryForced( 60818 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_JUDGEMENT_OF_JUSTICE;
			sp->ProcOnNameHash[1] = SPELL_HASH_JUDGEMENT_OF_LIGHT;
			sp->ProcOnNameHash[2] = SPELL_HASH_JUDGEMENT_OF_WISDOM;
			//must be casted on seal of command. Now how to check that ?
		}
		//Deadly Gladiator's Death Knight Relic
		sp = dbcSpell.LookupEntryForced( 60686 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_PLAGUE_STRIKE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//LK Arena 6 Gladiator's Death Knight Relic
		sp = dbcSpell.LookupEntryForced( 60686 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_PLAGUE_STRIKE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 60555;
		}
		//LK Arena 6 Gladiator's Libram of Fortitude
		sp = dbcSpell.LookupEntryForced( 60636 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_CRUSADER_STRIKE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 60555;
		}
		//Hateful Gladiator's Death Knight Relic
		sp = dbcSpell.LookupEntryForced( 60685 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_PLAGUE_STRIKE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//LK Arena 4 Gladiator's Death Knight Relic
		sp = dbcSpell.LookupEntryForced( 60687 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_PLAGUE_STRIKE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//LK Arena 5 Gladiator's Death Knight Relic
		sp = dbcSpell.LookupEntryForced( 60688 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_PLAGUE_STRIKE;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		}
		//Icy Touch Defense Increase
		sp = dbcSpell.LookupEntryForced( 62147 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_ICY_TOUCH;
		}
		//Item - Death Knight T8 Tank Relic
		sp = dbcSpell.LookupEntryForced( 64964 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_RUNE_STRIKE;
		}
		//Item - Death Knight T9 Tank Relic (Rune Strike)
		sp = dbcSpell.LookupEntryForced( 67381 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_RUNE_STRIKE;
		}
		//Item - Death Knight T9 Melee Relic (Rune Strike)
		sp = dbcSpell.LookupEntryForced( 67384 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_DEATH_STRIKE;
			sp->ProcOnNameHash[1] = SPELL_HASH_OBLITERATE;
			sp->ProcOnNameHash[2] = SPELL_HASH_SCOURGE_STRIKE;
			sp->procChance = 30;
			sp->proc_interval = 6000;
		}
		//Sigil of Haunted Dreams
		sp = dbcSpell.LookupEntryForced( 60826 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procFlags2 = PROC2_TARGET_SELF;
			sp->ProcOnNameHash[0] = SPELL_HASH_HEART_STRIKE;
			sp->ProcOnNameHash[1] = SPELL_HASH_BLOOD_STRIKE;
		}

		sp = dbcSpell.LookupEntryForced( 40475 );		// Black temple melee trinket
		//if( sp != NULL )
		{
			sp->procChance = 50;
			sp->proc_interval = uint32(60000 / 1.0f);
		}

		// Band of the Eternal Champion: reduced proc rate
		sp = dbcSpell.LookupEntryForced( 35080 );
		//if( sp != NULL )
			sp->procChance = 5;

		// Band of the Eternal Sage: reduced proc rate
		sp = dbcSpell.LookupEntryForced( 35083 );
		//if( sp != NULL )
			sp->procChance = 5;

		// Band of the Eternal Defender: reduced proc rate
		sp = dbcSpell.LookupEntryForced( 35077 );
		//if( sp != NULL )
			sp->procChance = 5;

		// Band of the Eternal Restorer: reduced proc rate
		sp = dbcSpell.LookupEntryForced( 35086 );
		//if( sp != NULL )
			sp->procChance = 5;

		// Deadly Throw Interrupt
		sp = dbcSpell.LookupEntryForced( 32748 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_RANGED_ATTACK | PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[ 0 ] = SPELL_HASH_DEADLY_THROW;
		}

		//Figurine - Shadowsong Panther
		sp = dbcSpell.LookupEntryForced( 46784 );		//	http://www.wowhead.com/?item=35702
		//if( sp != NULL )
			sp->AttributesEx |= ATTRIBUTESEX_NOT_BREAK_STEALTH;

		// Infernal Protection
		sp = dbcSpell.LookupEntryForced(36488);			//	http://www.wowhead.com/?spell=36488
		//if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_FRIEND;
		//Sundial of the Exiled
		sp = dbcSpell.LookupEntryForced(60063);
		if(sp != NULL)
		{
			sp->procFlags = PROC_ON_SPELL_HIT;
			sp->procChance = 10;
			sp->proc_interval = 45000;
		}

		//Je'Tze's Bell
		sp = dbcSpell.LookupEntryForced(49622);
		if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 10;
			sp->proc_interval = 45000;
		}

		//Tears of Bitter Anguish
		sp = dbcSpell.LookupEntryForced(58901);
		if(sp != NULL)
		{
			sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_CRIT_ATTACK;
			sp->procChance = 10;
			sp->proc_interval = 60000;
		}

		//Embrace of the Spider
		sp = dbcSpell.LookupEntryForced(60490);
		if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 10;
			sp->proc_interval = 30000;
		}

		//Dying Curse
		sp = dbcSpell.LookupEntryForced(60493);
		if(sp != NULL)
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 15;
			sp->proc_interval = 45000;
		}

		//Fury of the Five Flights
		sp = dbcSpell.LookupEntryForced(60313);
		if(sp != NULL)
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
			sp->procChance = 100;
			sp->maxstack = 20;
		}

		//Vial of the Sunwell
		sp = dbcSpell.LookupEntryForced( 45059 );
		//if( sp != NULL )
		{	
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 100;		
		}	
		sp = dbcSpell.LookupEntryForced( 45062 ); 
		//if( sp != NULL )
		{	
			sp->self_cast_only = true;	
			sp->procChance = 100;	
		}

		//Pendant of the Violet Eye
		sp = dbcSpell.LookupEntryForced( 29601 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL ;
			sp->procFlags2 |= PROC2_TARGET_SELF;
			sp->procChance = 100;
		}
		sp = dbcSpell.LookupEntryForced( 35095 );
		//if( sp != NULL )
		{
			sp->self_cast_only = true;
			sp->procChance = 100;
		}
				
		sp = dbcSpell.LookupEntryForced( 38332 );		// Ribbon of Sacrifice
		//if( sp != NULL )
			sp->procFlags = PROC_ON_CAST_SPELL;

		sp = dbcSpell.LookupEntryForced( 32642 );		// Sporegarr - Petrified Lichen Guard
		//if( sp != NULL )
		{	
			sp->procFlags = PROC_ON_BLOCK_VICTIM;
			sp->procChance = 100;
		}

        //Flow of Knowledge
		sp = dbcSpell.LookupEntryForced ( 62114 );
        if(sp != NULL )
		{
			//sp->EffectTriggerSpell[1] = 60064;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 10;
			sp->proc_interval = 45000;
		}
		//Forge Ember
		sp = dbcSpell.LookupEntryForced ( 60473 );
        if(sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 10;
			sp->proc_interval = 45000;
		}
		//Sundial of the Exiled
		sp = dbcSpell.LookupEntryForced ( 60063 );
        if(sp != NULL )
		{
			//sp->EffectTriggerSpell[1] = 60064;
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->procChance = 10;
			sp->proc_interval = 45000;
		}

		sp = dbcSpell.LookupEntryForced( 44856 );		// Bash'ir Phasing Device
		//if( sp != NULL )
			sp->RequiresAreaId = 3864;

		sp = dbcSpell.LookupEntryForced( 27997 );		//Spellsurge
		//if( sp != NULL )
		{
			sp->proc_interval = 30000; // Wowhead Comment
			sp->procChance = 3; //Enchantment Text
		}

		//Enchant Weapon - Deathfrost
		sp = dbcSpell.LookupEntryForced( 46662 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		}

		// Sigil of the Unfaltering Knight
		sp = dbcSpell.LookupEntryForced( 62147 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_ICY_TOUCH;
			sp->procChance = 100;
			sp->proc_interval = 45000;
		}

		// Deadly Gladiator's Death Knight Relic
/*		sp = dbcSpell.LookupEntryForced( 60686 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_PLAGUE_STRIKE;
			sp->procChance = 100;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 60549;
		}
		// Deadly Gladiator's Idol of Resolve
		sp = dbcSpell.LookupEntryForced( 60696 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_PLAGUE_STRIKE;
			sp->procChance = 100;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 60549;
		}
		// Deadly Gladiator's Libram of Fortitude
		sp = dbcSpell.LookupEntryForced( 60633 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_PLAGUE_STRIKE;
			sp->procChance = 100;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 60549;
		}
		// Deadly Totem of Indomitability
		sp = dbcSpell.LookupEntryForced( 60548 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_PLAGUE_STRIKE;
			sp->procChance = 100;
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->EffectTriggerSpell[0] = 60549;
		}
		sp = dbcSpell.LookupEntryForced( 60549 );
		//if( sp != NULL )
		{
			// it have 2 same effects dunno why
			sp->EffectApplyAuraName[1] = 0;
			sp->EffectBasePoints[1] = 0;
		}*/

		// Sigil of Haunted Dreams
		sp = dbcSpell.LookupEntryForced( 60826 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
			sp->ProcOnNameHash[1] = SPELL_HASH_HEART_STRIKE;
			sp->procChance = 15;
			sp->proc_interval = 45000;
		}

		// Vestige of Haldor
		sp = dbcSpell.LookupEntryForced( 60306 );
		//if( sp != NULL )
		{
			sp->proc_interval = 45000;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		}

		// Majestic Dragon Figurine
		sp = dbcSpell.LookupEntryForced( 60524 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
		}

		// Anvil of Titans
		sp = dbcSpell.LookupEntryForced( 62115 );
		//if( sp != NULL )
		{
			sp->proc_interval = 45000;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		}

		// Soul of the Dead
		sp = dbcSpell.LookupEntryForced( 60537 );
		//if( sp != NULL )
		{
			sp->proc_interval = 45000;
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
			sp->procFlags2 |= PROC2_TARGET_SELF;
		}
		sp = dbcSpell.LookupEntryForced( 60538 );
		//if( sp != NULL )
			sp->spell_id_client = sp->Id;

		// Illustration of the Dragon Soul
		sp = dbcSpell.LookupEntryForced( 60485 );
		//if( sp != NULL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
		}

		// Grim Toll
		sp = dbcSpell.LookupEntryForced( 60436 );
		//if( sp != NULL )
		{
			sp->proc_interval = 45000;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		}

		// Meteorite Whetstone
		sp = dbcSpell.LookupEntryForced( 60301 );
		//if( sp != NULL )
		{
			sp->proc_interval = 45000;
			sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		}

		// Sonic Booster
		sp = dbcSpell.LookupEntryForced( 54707 );
		//if( sp != NULL )
		{
			sp->proc_interval = 60000;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
		}

		//Totem of the Third Wind - bad range
		SpellEntry * sp_healing_wave = dbcSpell.LookupEntryForced( 8004 );
		sp = dbcSpell.LookupEntryForced( 34132 );
		//if( sp != NULL )
		{
			sp->rangeIndex = sp_healing_wave->rangeIndex;
		}
		sp = dbcSpell.LookupEntryForced( 42371 );
		//if( sp != NULL )
		{
			sp->rangeIndex = sp_healing_wave->rangeIndex;
		}
		sp = dbcSpell.LookupEntryForced( 43729 );
		//if( sp != NULL )
		{
			sp->rangeIndex = sp_healing_wave->rangeIndex;
		}
		sp = dbcSpell.LookupEntryForced( 46099 );
		//if( sp != NULL )
		{
			sp->rangeIndex = sp_healing_wave->rangeIndex;
		}
	//////////////////////////////////////////////////////
	// GAME-OBJECT SPELL FIXES                          //
	//////////////////////////////////////////////////////

	// Blessing of Zim'Torga
	sp = dbcSpell.LookupEntryForced( 51729 );
	if( sp )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SCRIPTED_OR_SINGLE_TARGET;
		sp->c_is_flags |= SPELL_FLAG_IS_FORCEDBUFF;
	}

	// Blessing of Zim'Abwa
	sp = dbcSpell.LookupEntryForced( 51265 );
	if( sp )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SCRIPTED_OR_SINGLE_TARGET;
		sp->c_is_flags |= SPELL_FLAG_IS_FORCEDBUFF;
	}

	// Blessing of Zim'Rhuk
	sp = dbcSpell.LookupEntryForced( 52051 );
	if( sp )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SCRIPTED_OR_SINGLE_TARGET;
		sp->c_is_flags |= SPELL_FLAG_IS_FORCEDBUFF;
	}

		//////////////////////////////////////////
		// BOSSES								//
		//////////////////////////////////////////

		// Insert boss spell fixes here
		//Emerald Vigor
		sp = dbcSpell.LookupEntryForced( 70873 );
		//if( sp != NULL )
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_DUEL;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_DUEL;
			sp->EffectImplicitTargetA[2] = EFF_TARGET_DUEL;
		}

		//Blastenheimer 5000 Ultra Cannon
		sp = dbcSpell.LookupEntryForced( 24832 );
		//if( sp != NULL )
			sp->EffectTriggerSpell[2] = 24742;
			// Restore Soul
			sp = dbcSpell.LookupEntryForced( 72595 );
			//if( sp != NULL )
			{
				sp->Effect[0] = SPELL_EFFECT_DUMMY;
				sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			}
			// Will of Sartharion
			sp = dbcSpell.LookupEntryForced( 61254 );
			//if( sp != NULL )
			{
				sp->DurationIndex = 3; // 1 minute
				sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_FRIENDLY_IN_AREA;
				sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
			}
			// Power of Vesperon
			sp = dbcSpell.LookupEntryForced( 61251 );
			//if( sp != NULL )
			{
				sp->DurationIndex = 3; // 1 minute
				sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
				sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
			}
			// Twilight Revenge
			sp = dbcSpell.LookupEntryForced( 60639 );
			//if( sp != NULL )
			{
				sp->DurationIndex = 3; // 1 minute
				sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
			}
			// Power of Shadron
			sp = dbcSpell.LookupEntryForced( 58105 );
			//if( sp != NULL )
			{
				sp->DurationIndex = 3; // 1 minute
				sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
				sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
			}
			// Power of Tenebron
			sp = dbcSpell.LookupEntryForced( 61248 );
			//if( sp != NULL )
			{
				sp->DurationIndex = 3; // 1 minute
				sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
				sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
			}
			// Berserk
			sp = dbcSpell.LookupEntryForced( 61632 );
			//if( sp != NULL )
			{
				sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
				sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
				sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
				sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
				sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
				sp->EffectImplicitTargetB[2] = EFF_TARGET_NONE;
			}
		
			// Dark Glare
			sp = dbcSpell.LookupEntryForced( 26029 );
			//if( sp != NULL )
				sp->cone_width = 15.0f; // 15 degree cone

			// Drain Power (Malacrass) // bugged - the charges fade even when refreshed with new ones. This makes them everlasting.
			sp = dbcSpell.LookupEntryForced( 44131 );
 			//if( sp != NULL )
				sp->DurationIndex = 21; //infinit
			sp = dbcSpell.LookupEntryForced( 44132 );
			//if( sp != NULL )
				sp->DurationIndex = 21; //infinit


	/****************************************/
	//	YAY DK spell hacks xD 
	/****************************************/
	// death knight
	//death knight

	//rune strike -> messed up spell. Instead of using normal required aurastate. It will require an aura :S
	CreateDummySpell( 56817 );
	sp = dbcSpell.LookupEntryForced( 56817 );
	//if( sp != NULL )
	{
		sp->procCharges = 1;
		sp->procFlagsRemove = PROC_ON_CAST_SPELL; 
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
		sp->DurationIndex = 25;	//3 minutes ? i think it is too much
		sp->AttributesEx |= ATTRIBUTESEX_VISIBLE;
	}
	sp = dbcSpell.LookupEntryForced( 56816 );	//this needs to be in playercreateinfo
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_DODGE_VICTIM; 
		sp->Attributes |= ATTRIBUTES_PASSIVE;
	}

	//Threat of Thassarian
	sp = dbcSpell.LookupEntryForced( 65661 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 65661;	//self proc MUST HANDLE IT !
		sp->procChance = sp->EffectBasePoints[0] + 1;
	}
	sp = dbcSpell.LookupEntryForced( 66191 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 65661;	//self proc MUST HANDLE IT !
		sp->procChance = sp->EffectBasePoints[0] + 1;
	}
	sp = dbcSpell.LookupEntryForced( 66192 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 65661;	//self proc MUST HANDLE IT !
		sp->procChance = sp->EffectBasePoints[0] + 1;
	}

	//Bloodworms
	sp = dbcSpell.LookupEntryForced( 49027 );
	//if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK ; 
	sp = dbcSpell.LookupEntryForced( 49542 );
	//if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK ; 
	sp = dbcSpell.LookupEntryForced( 49543 );
	//if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK ; 

	//Spell Deflection
	sp = dbcSpell.LookupEntryForced( 49145 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM ; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 51911;
		sp->procChance = 100;	//we will custom roll for this
	}
	sp = dbcSpell.LookupEntryForced( 49495 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM ; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 51911;
		sp->procChance = 100;	//we will custom roll for this
	}
	sp = dbcSpell.LookupEntryForced( 49497 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM ; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 51911;
		sp->procChance = 100;	//we will custom roll for this
	}

	//Wandering Plague
	sp = dbcSpell.LookupEntryForced( 49217 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE ; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 50526;
		sp->ProcOnNameHash[0] = SPELL_HASH_FROST_FEVER;
		sp->ProcOnNameHash[1] = SPELL_HASH_BLOOD_PLAGUE;
		sp->procChance = 100;	//we will custom roll for this
	}
	sp = dbcSpell.LookupEntryForced( 49654 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE ; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 50526;
		sp->ProcOnNameHash[0] = SPELL_HASH_FROST_FEVER;
		sp->ProcOnNameHash[1] = SPELL_HASH_BLOOD_PLAGUE;
		sp->procChance = 100;	//we will custom roll for this
	}
	sp = dbcSpell.LookupEntryForced( 49655 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE ; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 50526;
		sp->ProcOnNameHash[0] = SPELL_HASH_FROST_FEVER;
		sp->ProcOnNameHash[1] = SPELL_HASH_BLOOD_PLAGUE;
		sp->procChance = 100;	//we will custom roll for this
	}
	sp = dbcSpell.LookupEntryForced( 50526 );
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
		sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
	}

	//Improved Icy Talons
	sp = dbcSpell.LookupEntryForced( 55610 );
	//if( sp != NULL )
		sp->RequiredShapeShift = 0;

	//Unholy Blight
	sp = dbcSpell.LookupEntryForced( 49194 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE ; //maybe description also refers to spell damage ?
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 50536;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEATH_COIL;
	}

	//Hysteria
	sp = dbcSpell.LookupEntryForced( 49016 );
	//if( sp != NULL )
		sp->SpellGroupType[0] = 0;	//some say this is 1 hitting people. Maybe some spell is modding value ?

	//Anti-Magic Zone
	sp = dbcSpell.LookupEntryForced( 51052 );
	//if( sp != NULL )
	{
		sp->EffectBasePoints[0] = 0;
		sp->EffectMiscValueB[0] = 713l;	//make it summon guardians
	}
	//army of the dead
	sp = dbcSpell.LookupEntryForced( 42650 );
	//if( sp != NULL )
		sp->rangeIndex = 3; // whatever just not 0
	sp = dbcSpell.LookupEntryForced( 42651 );
	//if( sp != NULL )
		sp->EffectMiscValueB[1] = 713l;	//make it summon guardians

	//Dancing Rune Weapon
	//no idea if this is a summon or just a visual. Atm i will try a visual
	sp = dbcSpell.LookupEntryForced( 49028 );
	//if( sp != NULL )
	{
		sp->Effect[1] = SPELL_EFFECT_NULL;
		sp->Effect[2] = SPELL_EFFECT_NULL;
		sp->c_is_flags |= SPELL_FLAG_IS_INHERITING_LEVEL;
	}
	//death grip is actually some other spell which ofc does not have cooldown
	sp = dbcSpell.LookupEntryForced( 49576 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 49560;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
		sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
		sp->FacingCasterFlags = 0; //does not require facing
	}
	sp = dbcSpell.LookupEntryForced( 49560 ); //some version of death grip was targeting multiple targets. We do not want that
	//if( sp != NULL )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
		sp->EffectImplicitTargetB[0] = EFF_TARGET_SINGLE_ENEMY;
		sp->FacingCasterFlags = 0; //does not require facing
	}

	//death pact use only scripted target gathering
	sp = dbcSpell.LookupEntryForced( 48743 );
	//if( sp != NULL )
	{
//		sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME; //scripted targeting
//		sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
//		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME; //scripted targeting
//		sp->EffectImplicitTargetB[1] = EFF_TARGET_NONE;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF; //this is heal
		sp->EffectImplicitTargetB[2] = EFF_TARGET_NONE;
		sp->spell_can_crit = false;
		sp->Spell_value_is_scripted = true;
	}

	//death and decay -> stupid drink effect. Need to make some research about it
	sp = dbcSpell.LookupEntryForced( 43265 ); 
	//if( sp != NULL )
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;		
	sp = dbcSpell.LookupEntryForced( 49936 ); 
	//if( sp != NULL )
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;		
	sp = dbcSpell.LookupEntryForced( 49937 ); 
	//if( sp != NULL )
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;		
	sp = dbcSpell.LookupEntryForced( 49938 ); 
	//if( sp != NULL )
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;

	//Death Strike
	sp = dbcSpell.LookupEntryForced( 49998 ); 
	//if( sp != NULL )
	{
		sp->Effect[2] = SPELL_EFFECT_HEAL; //from dummy to heal
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 49999 ); 
	//if( sp != NULL )
	{
		sp->Effect[2] = SPELL_EFFECT_HEAL; //from dummy to heal
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 45463 ); 
	//if( sp != NULL )
	{
		sp->Effect[2] = SPELL_EFFECT_HEAL; //from dummy to heal
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 49923 ); 
	//if( sp != NULL )
	{
		sp->Effect[2] = SPELL_EFFECT_HEAL; //from dummy to heal
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 49924 ); 
	//if( sp != NULL )
	{
		sp->Effect[2] = SPELL_EFFECT_HEAL; //from dummy to heal
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
	}

	//Improved Frost Presence
	sp = dbcSpell.LookupEntryForced( 50384 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_AURA_REMOVE ; 
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 50384;	//self proc ! needs early exit
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_PRESENCE;
		sp->ProcOnNameHash[1] = SPELL_HASH_UNHOLY_PRESENCE;
		sp->proc_interval = 1;
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_3;//mod the frost presence properly
	}
	sp = dbcSpell.LookupEntryForced( 50385 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_AURA_REMOVE ; 
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 50384;	//self proc ! needs early exit
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_PRESENCE;
		sp->ProcOnNameHash[1] = SPELL_HASH_UNHOLY_PRESENCE;
		sp->proc_interval = 1;
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_3;//mod the frost presence properly
	}

	//Improved Blood Presence
	sp = dbcSpell.LookupEntryForced( 50365 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_AURA_REMOVE ; 
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 50365;	//self proc ! needs early exit
		sp->ProcOnNameHash[0] = SPELL_HASH_FROST_PRESENCE;
		sp->ProcOnNameHash[1] = SPELL_HASH_UNHOLY_PRESENCE;
		sp->proc_interval = 1;
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_2;//mod the frost presence properly
		sp->EffectSpellGroupRelation[1][0] = 8388608;
	}
	sp = dbcSpell.LookupEntryForced( 50371 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_AURA_REMOVE ; 
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 50365;	//self proc ! needs early exit
		sp->ProcOnNameHash[0] = SPELL_HASH_FROST_PRESENCE;
		sp->ProcOnNameHash[1] = SPELL_HASH_UNHOLY_PRESENCE;
		sp->proc_interval = 1;
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_2;//mod the frost presence properly
		sp->EffectSpellGroupRelation[1][0] = 8388608;
	}

	//Improved Unholy Presence
	sp = dbcSpell.LookupEntryForced( 50391 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_AURA_REMOVE ; 
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 49772;	
		sp->ProcOnNameHash[0] = SPELL_HASH_FROST_PRESENCE;
		sp->ProcOnNameHash[1] = SPELL_HASH_BLOOD_PRESENCE;
		sp->ProcOnNameHash[2] = SPELL_HASH_UNHOLY_PRESENCE;
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->EffectTriggerSpell[1] = 63622;
		sp->proc_interval = 1;
	}
	sp = dbcSpell.LookupEntryForced( 50392 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_AURA_REMOVE ; 
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 49772;	
		sp->ProcOnNameHash[0] = SPELL_HASH_FROST_PRESENCE;
		sp->ProcOnNameHash[1] = SPELL_HASH_BLOOD_PRESENCE;
		sp->ProcOnNameHash[2] = SPELL_HASH_UNHOLY_PRESENCE;
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->EffectTriggerSpell[1] = 63622;
		sp->proc_interval = 1;
	}
	//this spell will make the runes charge up faster
	sp = dbcSpell.LookupEntryForced( 63622 ); 
	//if( sp != NULL )
	{
	}

	//Blood Presence
	sp2 = dbcSpell.LookupEntryForced( 50371 );
	sp = dbcSpell.LookupEntryForced( 48266 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK | PROC_ON_SPELL_HIT ; //maybe description also refers to spell damage ?
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 50475;
		sp->EffectBasePoints[1] = sp2->EffectBasePoints[0];
	}

	//Frost Presence
	sp = dbcSpell.LookupEntryForced( 48263 ); 
	sp2 = dbcSpell.LookupEntryForced( 61261 ); 
	//if( sp != NULL && sp2 != NULL)
	{
		//description does not say it will increase threath. So we are replacing the effect with correct one
		SpellEntryEffectCopy(sp2,sp,0,1);//max hp
	}

	//Unholy Presence
	sp = dbcSpell.LookupEntryForced( 48265 ); 
	sp2 = dbcSpell.LookupEntryForced( 49772 ); 
	//if( sp != NULL && sp2 != NULL)
	{
		//description does not say it will increase threath. So we are replacing the effect with correct one
		SpellEntryEffectCopy(sp2,sp,0,2);//haste effect
		sp->EffectMiscValue[1] = SMT_COOLDOWN_DECREASE;
	}
	
	//Abomination's Might
	sp = dbcSpell.LookupEntryForced( 53137 ); 
	//if( sp != NULL )
		sp->RequiredShapeShift = 0;
	sp = dbcSpell.LookupEntryForced( 53138 ); 
	//if( sp != NULL )
		sp->RequiredShapeShift = 0;

	//Blade Barrier
	sp = dbcSpell.LookupEntryForced( 49182 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_SCRIPTED_PROCTEST ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 49500 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_SCRIPTED_PROCTEST ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 49501 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_SCRIPTED_PROCTEST ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 55225 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_SCRIPTED_PROCTEST;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 55226 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_SCRIPTED_PROCTEST ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 100;
	}

	//Butchery
	sp = dbcSpell.LookupEntryForced( 48979 ); 
	//if( sp != NULL )
	{
		sp->EffectBasePoints[ 1 ] = (sp->EffectBasePoints[ 1 ] + 1) / 5 - 1; //regen value is for 5 seconds. but we really care for / sec value
		sp->procFlags = PROC_ON_TARGET_DIE ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 50163;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 49483 ); 
	//if( sp != NULL )
	{
		sp->EffectBasePoints[ 1 ] = (sp->EffectBasePoints[ 1 ] + 1) / 5 - 1; //regen value is for 5 seconds. but we really care for / sec value
		sp->procFlags = PROC_ON_TARGET_DIE ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 50163;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 50163 ); 
	//if( sp != NULL )
		sp->EffectBasePoints[ 0 ] = (sp->EffectBasePoints[ 0 ] + 1) * 10 - 1 ;//well runic power is 10x stored but blizz forgot that

	//Death Coil 
	sp = dbcSpell.LookupEntryForced( 47541 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE; //damage enemy if we can find one
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
		SpellEntryEffectCopy(sp,sp,0,1);
		sp->Effect[1] = SPELL_EFFECT_HEAL; //heal friendly undead
//		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND; //damn, how to check an undead ?
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME; //damn, how to check an undead ?
		sp->EffectBasePoints[1] = (int32)(sp->EffectBasePoints[0]*1.5f);
	}
	sp = dbcSpell.LookupEntryForced( 49892 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE; //damage enemy if we can find one
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
		SpellEntryEffectCopy(sp,sp,0,1);
		sp->Effect[1] = SPELL_EFFECT_HEAL; //heal friendly undead
//		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND; //damn, how to check an undead ?
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME; //damn, how to check an undead ?
		sp->EffectBasePoints[1] = (int32)(sp->EffectBasePoints[0]*1.5f);
	}
	sp = dbcSpell.LookupEntryForced( 49893 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE; //damage enemy if we can find one
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
		SpellEntryEffectCopy(sp,sp,0,1);
		sp->Effect[1] = SPELL_EFFECT_HEAL; //heal friendly undead
//		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND; //damn, how to check an undead ?
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME; //damn, how to check an undead ?
		sp->EffectBasePoints[1] = (int32)(sp->EffectBasePoints[0]*1.5f);
	}
	sp = dbcSpell.LookupEntryForced( 49894 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE; //damage enemy if we can find one
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
		SpellEntryEffectCopy(sp,sp,0,1);
		sp->Effect[1] = SPELL_EFFECT_HEAL; //heal friendly undead
//		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND; //damn, how to check an undead ?
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME; //damn, how to check an undead ?
		sp->EffectBasePoints[1] = (int32)(sp->EffectBasePoints[0]*1.5f);
	}
	sp = dbcSpell.LookupEntryForced( 49895 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_SCHOOL_DAMAGE; //damage enemy if we can find one
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
		SpellEntryEffectCopy(sp,sp,0,1);
		sp->Effect[1] = SPELL_EFFECT_HEAL; //heal friendly undead
//		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND; //damn, how to check an undead ?
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_SCRIPTED_OR_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME; //damn, how to check an undead ?
		sp->EffectBasePoints[1] = (int32)(sp->EffectBasePoints[0]*1.5f);
	}

	//death charger -> should not cost anything
	sp = dbcSpell.LookupEntryForced( 48778 ); 
	//if( sp != NULL )
	{
		sp->powerType = POWER_TYPE_RUNIC_POWER;
		sp->manaCost = 0;
	}

	//shadow of death -> do not make player invincible
/*	sp = dbcSpell.LookupEntryForced( 49157 ); 
	//if( sp != NULL )
		sp->Effect[0] = SPELL_EFFECT_NULL;*/

	//Scent of Blood
	sp = dbcSpell.LookupEntryForced( 49004 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->Effect[1] = SPELL_EFFECT_NULL;
		sp->Effect[2] = SPELL_EFFECT_NULL; //these are registering same spell multiple times
	}
	sp = dbcSpell.LookupEntryForced( 49508 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_FLAT_MODIFIER;
		sp->EffectMiscValue[1] = SMT_CHARGES;
		sp->EffectSpellGroupRelation[1][0] = 64; //hope it is not taken :P
		sp->EffectBasePoints[1] = 0; // +1 
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->Effect[2] = SPELL_EFFECT_NULL; //these are registering same spell multiple times 
	}
	sp = dbcSpell.LookupEntryForced( 49509 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_FLAT_MODIFIER;
		sp->EffectMiscValue[1] = SMT_CHARGES;
		sp->EffectSpellGroupRelation[1][0] = 64; //hope it is not taken :P
		sp->EffectBasePoints[1] = 1; // +1 
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->Effect[2] = SPELL_EFFECT_NULL; //these are registering same spell multiple times
	}
	sp = dbcSpell.LookupEntryForced( 50421 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50422;
		sp->SpellGroupType[0] = 64;//hope it is not taken :P
		sp->procCharges = 1;
	}
	sp = dbcSpell.LookupEntryForced( 50422 ); 
	//if( sp != NULL )
		sp->EffectBasePoints[0] = (sp->EffectBasePoints[0] + 1) / 2 - 1; //no idea why butvalue is double

	//Merciless Combat
	sp = dbcSpell.LookupEntryForced( 49024 ); 
	//if( sp != NULL )
		sp->TargetAuraState = 0;
	sp = dbcSpell.LookupEntryForced( 49538 ); 
	//if( sp != NULL )
		sp->TargetAuraState = 0;

	//Death Rune Mastery
	sp = dbcSpell.LookupEntryForced( 49467 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50807;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->EffectTriggerSpell[1] = 50808;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEATH_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_OBLITERATE;
	}
	sp = dbcSpell.LookupEntryForced( 50033 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50807;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->EffectTriggerSpell[1] = 50808;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEATH_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_OBLITERATE;
	}
	sp = dbcSpell.LookupEntryForced( 50034 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50807;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->EffectTriggerSpell[1] = 50808;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEATH_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_OBLITERATE;
	}
	sp = dbcSpell.LookupEntryForced( 50807 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_CONVERT_RUNE;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->EffectMiscValue[0] = RUNE_UNHOLY;
		sp->EffectMiscValueB[0] = RUNE_DEATH;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_CONVERT_RUNE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->EffectMiscValue[1] = RUNE_UNHOLY;
		sp->EffectMiscValueB[1] = RUNE_DEATH;
		sp->DurationIndex = 3; //1 minute, what is the duration on blizz ?
		sp->NameHash = SPELL_HASH_DEATH_RUNE_MASTERY_50807; //make it be able to stack !
	}
	sp = dbcSpell.LookupEntryForced( 50808 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_CONVERT_RUNE;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->EffectMiscValue[0] = RUNE_FROST;
		sp->EffectMiscValueB[0] = RUNE_DEATH;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_CONVERT_RUNE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->EffectMiscValue[1] = RUNE_FROST;
		sp->EffectMiscValueB[1] = RUNE_DEATH;
		sp->DurationIndex = 3; //1 minute, what is the duration on blizz ?
		sp->NameHash = SPELL_HASH_DEATH_RUNE_MASTERY_50808; //make it be able to stack !
	}/**/
	sp = dbcSpell.LookupEntryForced( 49467 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50807;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEATH_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_OBLITERATE;
	}
	sp = dbcSpell.LookupEntryForced( 50033 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50807;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEATH_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_OBLITERATE;
	}
	sp = dbcSpell.LookupEntryForced( 50034 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50807;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEATH_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_OBLITERATE;
	}
	sp = dbcSpell.LookupEntryForced( 50807 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_CONVERT_RUNE;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->EffectMiscValue[0] = RUNE_UNHOLY;
		sp->EffectMiscValueB[0] = RUNE_DEATH;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_CONVERT_RUNE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->EffectMiscValue[1] = RUNE_FROST;
		sp->EffectMiscValueB[1] = RUNE_DEATH;
		sp->DurationIndex = 3; //1 minute, what is the duration on blizz ?
		sp->NameHash = SPELL_HASH_DEATH_RUNE_MASTERY_50807; //make it be able to stack !
	}

	//Improved Rune Tap
	sp = dbcSpell.LookupEntryForced( 48985 ); 
	//if( sp != NULL )
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
	sp = dbcSpell.LookupEntryForced( 49488 ); 
	//if( sp != NULL )
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
	sp = dbcSpell.LookupEntryForced( 49489 ); 
	//if( sp != NULL )
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;

	//Vendetta
	sp = dbcSpell.LookupEntryForced( 49015 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_TARGET_DIE ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50181;
	}
	sp = dbcSpell.LookupEntryForced( 50154 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_TARGET_DIE ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50181;
	}
	sp = dbcSpell.LookupEntryForced( 55136 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_TARGET_DIE ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50181;
	}

	//Bloody Strikes
	sp = dbcSpell.LookupEntryForced( 48977 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_COST;
		//force this for us
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp->EffectSpellGroupRelation[1][0] = sp->EffectSpellGroupRelation[0][0];
	}
	sp = dbcSpell.LookupEntryForced( 49394 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_COST;
		//force this for us
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp->EffectSpellGroupRelation[1][0] = sp->EffectSpellGroupRelation[0][0];
	}
	sp = dbcSpell.LookupEntryForced( 49395 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_COST;
		//force this for us
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[1] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp->EffectSpellGroupRelation[1][0] = sp->EffectSpellGroupRelation[0][0];
	}

	//Mark of Blood
	sp = dbcSpell.LookupEntryForced( 49005 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 100;
		sp->EffectTriggerSpell[0] = 50424;
		sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE | PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		sp->procCharges = 20;	//max 20 hits
		sp->AuraInterruptFlags = 0;
	}
	sp = dbcSpell.LookupEntryForced( 50424 );
	//if( sp != NULL )
	{
		SetAllSpellCoef( sp, 0.00001f);	//just make sure value does not get bogues
		sp->spell_id_client = sp->Id;
	}
	

	//Bloody Vengeance
	sp = dbcSpell.LookupEntryForced( 48988 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 49503 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 49504 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	}

	//Hysteria
	sp = dbcSpell.LookupEntryForced( 49016 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PERIODIC_DAMAGE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
	}

	//Icy Talons
	sp = dbcSpell.LookupEntryForced( 50880 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 50882;
		sp->ProcOnNameHash[0] = SPELL_HASH_ICY_TOUCH;
	}
	sp = dbcSpell.LookupEntryForced( 50882 ); 
	//if( sp != NULL )
	{
		SpellEntryEffectCopy(sp,sp,0,1);
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		sp->EffectBasePoints[1] = -sp->EffectBasePoints[1]-1;
	}
	sp = dbcSpell.LookupEntryForced( 50884 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 58575;
		sp->ProcOnNameHash[0] = SPELL_HASH_ICY_TOUCH;
	}
	sp = dbcSpell.LookupEntryForced( 58575 ); 
	//if( sp != NULL )
	{
		SpellEntryEffectCopy(sp,sp,0,1);
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		sp->EffectBasePoints[1] = -sp->EffectBasePoints[1]-1;
	}
	sp = dbcSpell.LookupEntryForced( 50885 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 58576;
		sp->ProcOnNameHash[0] = SPELL_HASH_ICY_TOUCH;
	}
	sp = dbcSpell.LookupEntryForced( 58576 ); 
	//if( sp != NULL )
	{
		SpellEntryEffectCopy(sp,sp,0,1);
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		sp->EffectBasePoints[1] = -sp->EffectBasePoints[1]-1;
	}
	sp = dbcSpell.LookupEntryForced( 50886 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 58577;
		sp->ProcOnNameHash[0] = SPELL_HASH_ICY_TOUCH;
	}
	sp = dbcSpell.LookupEntryForced( 58577 ); 
	//if( sp != NULL )
	{
		SpellEntryEffectCopy(sp,sp,0,1);
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		sp->EffectBasePoints[1] = -sp->EffectBasePoints[1]-1;
	}
	sp = dbcSpell.LookupEntryForced( 50887 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 58578;
		sp->ProcOnNameHash[0] = SPELL_HASH_ICY_TOUCH;
	}
	sp = dbcSpell.LookupEntryForced( 58578 ); 
	//if( sp != NULL )
	{
		SpellEntryEffectCopy(sp,sp,0,1);
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_ENEMY;
		sp->EffectBasePoints[1] = -sp->EffectBasePoints[1]-1;
	}

	//Sudden Doom
	sp = dbcSpell.LookupEntryForced( 49018 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_HEART_STRIKE;
		sp->EffectTriggerSpell[0] = 49895; //!!should be somewhat level dependent !
		sp->proc_interval = 60000 / 15;	//15 ppm ?
	}
	sp = dbcSpell.LookupEntryForced( 49529 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_HEART_STRIKE;
		sp->EffectTriggerSpell[0] = 49895; //!!should be somewhat level dependent !
		sp->proc_interval = 60000 / 15;	//15 ppm ?
	}
	sp = dbcSpell.LookupEntryForced( 49530 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_HEART_STRIKE;
		sp->EffectTriggerSpell[0] = 49895; //!!should be somewhat level dependent !
		sp->proc_interval = 60000 / 15;	//15 ppm ?
	}

	//Killing Machine
	sp = dbcSpell.LookupEntryForced( 51123 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->proc_interval = 18000;
	}
	sp = dbcSpell.LookupEntryForced( 51127 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->proc_interval = 16000;
	}
	sp = dbcSpell.LookupEntryForced( 51128 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->proc_interval = 14000;
	}
	sp = dbcSpell.LookupEntryForced( 51129 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->proc_interval = 12000;
	}
	sp = dbcSpell.LookupEntryForced( 51130 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->proc_interval = 10000;
	}
	sp = dbcSpell.LookupEntryForced( 51124 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->proc_interval = 8000;
	}
	sp = dbcSpell.LookupEntryForced( 51124 ); 
	//if( sp != NULL )
	{
		sp->procCharges = 1;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	//Bone Shield
	sp = dbcSpell.LookupEntryForced( 49222 ); 
	//if( sp != NULL )
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;

	//Deathchill
	sp = dbcSpell.LookupEntryForced( 49796 ); 
	//if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;

	//Chill of the Grave
	sp = dbcSpell.LookupEntryForced( 49149 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_FLAT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_COST;
		sp->EffectSpellGroupRelation[0][0] = 2;
		sp->EffectSpellGroupRelation[0][1] = 2;
	}
	sp = dbcSpell.LookupEntryForced( 50115 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_FLAT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_COST;
		sp->EffectSpellGroupRelation[0][0] = 2;
		sp->EffectSpellGroupRelation[0][1] = 2;
	}

	//Will of the Necropolis
	sp = dbcSpell.LookupEntryForced( 49189 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_DUMMY;
		sp->Effect[1] = SPELL_EFFECT_NULL;
	}
	sp = dbcSpell.LookupEntryForced( 50149 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_DUMMY;
		sp->Effect[1] = SPELL_EFFECT_NULL;
	}
	sp = dbcSpell.LookupEntryForced( 50150 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_DUMMY;
		sp->Effect[1] = SPELL_EFFECT_NULL;
	}
	sp = dbcSpell.LookupEntryForced( 52284 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
		sp->EffectBasePoints[0] = (sp->EffectBasePoints[0] + 2)*(-1);
	}
	sp = dbcSpell.LookupEntryForced( 52285 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
		sp->EffectBasePoints[0] = (sp->EffectBasePoints[0] + 2)*(-1);
	}
	sp = dbcSpell.LookupEntryForced( 52286 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
		sp->EffectBasePoints[0] = (sp->EffectBasePoints[0] + 2)*(-1);
	}

	//Blood Gorged
	sp = dbcSpell.LookupEntryForced( 61154 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 61155 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 61156 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 61157 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 61158 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
	}

	//Rime
	sp = dbcSpell.LookupEntryForced( 49188 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_OBLITERATE;
	}
	sp = dbcSpell.LookupEntryForced( 56822 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_OBLITERATE;
	}
	sp = dbcSpell.LookupEntryForced( 59057 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_OBLITERATE;
	}
	sp = dbcSpell.LookupEntryForced( 59052 ); 
	//if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;

	//Endless Winter
	sp = dbcSpell.LookupEntryForced( 49137 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_CHAINS_OF_ICE;
	}
	sp = dbcSpell.LookupEntryForced( 49657 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_CHAINS_OF_ICE;
	}

	sp = dbcSpell.LookupEntryForced( 45524 ); 
	//if( sp != NULL )
	{
		sp->EffectBasePoints[0] = sp->EffectBasePoints[0] / 2;
	}
	
	// Glyph of Heart Strike
	// Your Heart Strike also reduces the movement speed of your target by $58617s1% for $58617d.
	sp = dbcSpell.LookupEntryForced( 58616 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->ProcOnNameHash[0] = SPELL_HASH_HEART_STRIKE;
	}
	// Glyph of Chains of Ice
	// Your Chains of Ice also causes 144 to 156 Frost damage, increased by your attack power.
	sp = dbcSpell.LookupEntryForced( 58620 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_CHAINS_OF_ICE;
	}
	// Glyph of Howling Blast
	// Your Howling Blast ability now infects your targets with Frost Fever.
	sp = dbcSpell.LookupEntryForced( 63335 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_HOWLING_BLAST;
	}

	//chains of ice proc
//	sp = dbcSpell.LookupEntryForced( 47805 ); 
	//if( sp != NULL )
//		sp->EffectBasePoints[0] = -sp->EffectBasePoints[0];	//instead of speed slow ?

	//Acclimation
	sp = dbcSpell.LookupEntryForced( 49200 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_LAND_VICTIM ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50362;
	}
	sp = dbcSpell.LookupEntryForced( 50151 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_LAND_VICTIM ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50362;
	}
	sp = dbcSpell.LookupEntryForced( 50152 ); 
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_LAND_VICTIM ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 50362;
	}

	//Chilblains
	sp = dbcSpell.LookupEntryForced( 50040 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->EffectTriggerSpell[0] = 50434;
		sp->ProcOnNameHash[0] = SPELL_HASH_FROST_FEVER;
	}
	sp = dbcSpell.LookupEntryForced( 50041 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->EffectTriggerSpell[0] = 50435;
		sp->ProcOnNameHash[0] = SPELL_HASH_FROST_FEVER;
	}
	sp = dbcSpell.LookupEntryForced( 50043 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->EffectTriggerSpell[0] = 50436;
		sp->ProcOnNameHash[0] = SPELL_HASH_FROST_FEVER;
	}

	//Blood of the North
	sp = dbcSpell.LookupEntryForced( 54639 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 45529;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_PESTILENCE;
	}
	sp = dbcSpell.LookupEntryForced( 54638 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 45529;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_PESTILENCE;
	}
	sp = dbcSpell.LookupEntryForced( 54637 ); 
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 45529;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_PESTILENCE;
	}

	//Pestilence
	sp = dbcSpell.LookupEntryForced( 50842 ); 
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_SCRIPT_EFFECT;
		sp->Effect[1] = SPELL_EFFECT_NULL;
		sp->Effect[2] = SPELL_EFFECT_NULL;
	}

	//Hungering Cold -> you learn a talent that does nothing ? :S	
	sp = dbcSpell.LookupEntryForced( 49203 ); 
	//if( sp != NULL )
	{
		//Frost Fever
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 55095;
		sp->EffectRadiusIndex[0] = 13; //everyone knows that is 10 yards :P
		sp->EffectImplicitTargetA[0] = EFF_TARGET_LOCATION_TO_SUMMON;
		
		//the visual effect
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 51209;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 51209 ); 
	//if( sp != NULL )
	{
		sp->procCharges = 0;
		sp->AuraInterruptFlags = AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;
		sp->Effect[1] = SPELL_EFFECT_NULL;
		sp->Effect[2] = SPELL_EFFECT_NULL;
	}

	//Frost Fever
	sp = dbcSpell.LookupEntryForced( 55095 );
	//if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_PROC_TRIGGER_PROC;
	//blood plague
	sp = dbcSpell.LookupEntryForced( 55078 );
	//if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_PROC_TRIGGER_PROC;

	//Rune Strike
	sp = dbcSpell.LookupEntryForced( 56815 );
	//if( sp != NULL )
		sp->Attributes = ATTRIBUTES_CANT_BE_DPB;
	
	//Frost Strike
	sp = dbcSpell.LookupEntryForced( 49143 );
	//if( sp != NULL )
		sp->Attributes = ATTRIBUTES_CANT_BE_DPB;
	sp = dbcSpell.LookupEntryForced( 51416 );
	//if( sp != NULL )
		sp->Attributes = ATTRIBUTES_CANT_BE_DPB;   
	sp = dbcSpell.LookupEntryForced( 51417 );
	//if( sp != NULL )
		sp->Attributes = ATTRIBUTES_CANT_BE_DPB;
	sp = dbcSpell.LookupEntryForced( 51418 );
	//if( sp != NULL )
		sp->Attributes = ATTRIBUTES_CANT_BE_DPB;     
	sp = dbcSpell.LookupEntryForced( 51419 );
	//if( sp != NULL )
		sp->Attributes = ATTRIBUTES_CANT_BE_DPB;   
	sp = dbcSpell.LookupEntryForced( 55268 );
	//if( sp != NULL )
		sp->Attributes = ATTRIBUTES_CANT_BE_DPB;   


	//Morbidity
	sp = dbcSpell.LookupEntryForced( 48963 );
	//if( sp != NULL )
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
	sp = dbcSpell.LookupEntryForced( 49564 );
	//if( sp != NULL )
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
	sp = dbcSpell.LookupEntryForced( 49565 );
	//if( sp != NULL )
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;

	//Necrosis
	sp = dbcSpell.LookupEntryForced( 51459 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 51460;
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		sp->proc_interval = 2000;
	}
	sp = dbcSpell.LookupEntryForced( 51462 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 51460;
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
	}
	sp = dbcSpell.LookupEntryForced( 51463 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 51460;
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
	}
	sp = dbcSpell.LookupEntryForced( 51464 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 51460;
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
	}
	sp = dbcSpell.LookupEntryForced( 51465 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 51460;
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
	}

	//Scourge Strike
	sp = dbcSpell.LookupEntryForced( 55090 );
	//if( sp != NULL )
		sp->Effect[1] = SPELL_EFFECT_WEAPON_PERCENT_DAMAGE;
	sp = dbcSpell.LookupEntryForced( 55265 );
	//if( sp != NULL )
		sp->Effect[1] = SPELL_EFFECT_WEAPON_PERCENT_DAMAGE;
	sp = dbcSpell.LookupEntryForced( 55270 );
	//if( sp != NULL )
		sp->Effect[1] = SPELL_EFFECT_WEAPON_PERCENT_DAMAGE;
	sp = dbcSpell.LookupEntryForced( 55271 );
	//if( sp != NULL )
		sp->Effect[1] = SPELL_EFFECT_WEAPON_PERCENT_DAMAGE;

	//Blood-Caked Strike
	sp = dbcSpell.LookupEntryForced( 50463 );
	//if( sp != NULL )
		SpellEntryEffectSwap(sp,sp,0,1);
	sp = dbcSpell.LookupEntryForced( 61895 );
	//if( sp != NULL )
		SpellEntryEffectSwap(sp,sp,0,1);

	//Impurity
	sp = dbcSpell.LookupEntryForced( 49220 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
	}
	sp = dbcSpell.LookupEntryForced( 49633 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
	}
	sp = dbcSpell.LookupEntryForced( 49635 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
	}
	sp = dbcSpell.LookupEntryForced( 49636 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
	}
	sp = dbcSpell.LookupEntryForced( 49638 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
	}

	//Crypt Fever
	sp = dbcSpell.LookupEntryForced( 49032 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_PLAGUE;
		sp->ProcOnNameHash[1] = SPELL_HASH_FROST_FEVER;
		sp->EffectTriggerSpell[0] = 50508;
	}
	sp2 = dbcSpell.LookupEntryForced( 50508 );
	//if( sp != NULL )
	{
		sp2->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp2->EffectMiscValue[0] = SMT_EFFECT_TARGET;
		sp2->EffectSpellGroupRelation[0][0] = sp->EffectSpellGroupRelation[0][0];
		sp2->EffectSpellGroupRelation[0][1] = sp->EffectSpellGroupRelation[0][1];
		sp2->EffectSpellGroupRelation[0][2] = sp->EffectSpellGroupRelation[0][2];
	}
	sp = dbcSpell.LookupEntryForced( 49631 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_PLAGUE;
		sp->ProcOnNameHash[1] = SPELL_HASH_FROST_FEVER;
		sp->EffectTriggerSpell[0] = 50509;
	}
	sp2 = dbcSpell.LookupEntryForced( 50509 );
	//if( sp != NULL )
	{
		sp2->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp2->EffectMiscValue[0] = SMT_EFFECT_TARGET;
		sp2->EffectSpellGroupRelation[0][0] = sp->EffectSpellGroupRelation[0][0];
		sp2->EffectSpellGroupRelation[0][1] = sp->EffectSpellGroupRelation[0][1];
		sp2->EffectSpellGroupRelation[0][2] = sp->EffectSpellGroupRelation[0][2];
	}
	sp = dbcSpell.LookupEntryForced( 49632 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_PLAGUE;
		sp->ProcOnNameHash[1] = SPELL_HASH_FROST_FEVER;
		sp->EffectTriggerSpell[0] = 50510;
	}
	sp2 = dbcSpell.LookupEntryForced( 50510 );
	//if( sp != NULL )
	{
		sp2->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp2->EffectMiscValue[0] = SMT_EFFECT_TARGET;
		sp2->EffectSpellGroupRelation[0][0] = sp->EffectSpellGroupRelation[0][0];
		sp2->EffectSpellGroupRelation[0][1] = sp->EffectSpellGroupRelation[0][1];
		sp2->EffectSpellGroupRelation[0][2] = sp->EffectSpellGroupRelation[0][2];
	}

	//Desolation
	sp = dbcSpell.LookupEntryForced( 66799 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
	}
	sp = dbcSpell.LookupEntryForced( 66814 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
	}
	sp = dbcSpell.LookupEntryForced( 66815 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
	}
	sp = dbcSpell.LookupEntryForced( 66816 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
	}
	sp = dbcSpell.LookupEntryForced( 66817 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_STRIKE;
	}

	//Desecration -> fucked up spell. creates npc that has aura to boost us and slow enemy
	sp = dbcSpell.LookupEntryForced( 55666 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_PLAGUE_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_SCOURGE_STRIKE;
	}
	sp = dbcSpell.LookupEntryForced( 55667 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_PLAGUE_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_SCOURGE_STRIKE;
	}
	sp = dbcSpell.LookupEntryForced( 68766 );
	//if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
/*	//pls do not spawn npc
	sp = dbcSpell.LookupEntryForced( 63592 );
	//if( sp != NULL )
		sp->Effect[0] = SPELL_EFFECT_NULL;
	sp = dbcSpell.LookupEntryForced( 63593 );
	//if( sp != NULL )
		sp->Effect[0] = SPELL_EFFECT_NULL;
	sp = dbcSpell.LookupEntryForced( 63594 );
	//if( sp != NULL )
		sp->Effect[0] = SPELL_EFFECT_NULL;
	sp = dbcSpell.LookupEntryForced( 63595 );
	//if( sp != NULL )
		sp->Effect[0] = SPELL_EFFECT_NULL;
	sp = dbcSpell.LookupEntryForced( 55651 );
	//if( sp != NULL )
		sp->Effect[0] = SPELL_EFFECT_NULL;*/


	//On a Pale Horse
	sp = dbcSpell.LookupEntryForced( 49146 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 51267 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
	}

	//Blood-Caked Blade
	sp = dbcSpell.LookupEntryForced( 49219 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 49627 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 49628 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
	}

	//Reaping
	sp = dbcSpell.LookupEntryForced( 49208 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 45529;
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_BOIL;
		sp->ProcOnNameHash[1] = SPELL_HASH_BLOOD_STRIKE;
	}
	sp = dbcSpell.LookupEntryForced( 56834 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 45529;
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_BOIL;
		sp->ProcOnNameHash[1] = SPELL_HASH_BLOOD_STRIKE;
	}
	sp = dbcSpell.LookupEntryForced( 56835 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 45529;
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_BOIL;
		sp->ProcOnNameHash[1] = SPELL_HASH_BLOOD_STRIKE;
	}

/*	//Summon Gargoyle
	sp = dbcSpell.LookupEntryForced( 49206 );
	//if( sp != NULL )
		sp->DurationIndex = 9; // 30 sec*/
	//raise dead
	sp = dbcSpell.LookupEntryForced( 46584 );
	//if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_DUMMY;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_DUEL;
		sp->EffectImplicitTargetB[0] = EFF_TARGET_NONE;
		sp->Effect[1] = SPELL_EFFECT_NULL;
		sp->Effect[2] = SPELL_EFFECT_NULL;
		sp->c_is_flags |= SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE;
	}

	////////////////////////////////////////////////
	// misc fixes
	////////////////////////////////////////////////
	//Blood Mirror - boss spell
	sp = dbcSpell.LookupEntryForced(70821);
	//if(sp != NULL)
	{
		sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM;
		sp->proc_interval = 0;	//all dmg, we will have a lot of attackers
		sp->EffectTriggerSpell[0]	=	70821;	//self proc cause we handle it 
	}
	//Mirrored Soul - boss spell
	sp = dbcSpell.LookupEntryForced(69051);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_DRINK_NEW;
		sp->EffectAmplitude[0] = 2000;			//spam or to not to spam
	}
	//Blood Link - boss spell
	sp = dbcSpell.LookupEntryForced(72178);
	//if(sp != NULL)
	{
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->procFlags	=	PROC_ON_CAST_SPELL;
		sp->Effect[1] = SPELL_EFFECT_NULL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BOILING_BLOOD;
		sp->ProcOnNameHash[1] = SPELL_HASH_BLOOD_NOVA;
		sp->EffectTriggerSpell[0]	=	72371;
	}
	//Mark of the Fallen Champion - boss spell for heal proc
	sp = dbcSpell.LookupEntryForced(72293);
	//if(sp != NULL)
	{
		sp->procFlags =	PROC_ON_TARGET_DIE;
		sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
	}
	//Mark of the Fallen Champion - boss spell for dmg proc
	sp = dbcSpell.LookupEntryForced(72256);
	//if(sp != NULL)
		sp->procFlags =	PROC_ON_MELEE_ATTACK;
	//Blood Mirror - boss spell
	sp = dbcSpell.LookupEntryForced(71510);
	//if(sp != NULL)
		sp->EffectApplyAuraName[0] = SPELL_AURA_SPLIT_DAMAGE;
	//Slime Puddle - boss spell
	sp = dbcSpell.LookupEntryForced(70346);
	//if(sp != NULL)
		sp->EffectRadiusIndex[0] = 15;	//3 yards
	//Dreamwalker's Rage - boss spell
	sp = dbcSpell.LookupEntryForced(71189);
	//if(sp != NULL)
		sp->Effect[0] = SPELL_EFFECT_INSTANT_KILL;	
	//Mana Barrier - boss spell
	sp = dbcSpell.LookupEntryForced(70842);
	//if(sp != NULL)
		sp->EffectApplyAuraName[0] = SPELL_AURA_DRINK_NEW;	
	//Unleashed Souls - boss spell
	sp = dbcSpell.LookupEntryForced(68967);
	//if(sp != NULL)
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;	
	//Ball Lightning - boss spell
	sp = dbcSpell.LookupEntryForced(52780);
	//if(sp != NULL)
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;	
		
/*	//Ranged Weapon Specialization
	sp = dbcSpell.LookupEntryForced( 19507 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectMiscValue[0] = 1;
	};
	sp = dbcSpell.LookupEntryForced( 19508 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectMiscValue[0] = 1;
	};
	sp = dbcSpell.LookupEntryForced( 19509 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectMiscValue[0] = 1;
	};
	sp = dbcSpell.LookupEntryForced( 19510 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectMiscValue[0] = 1;
	};
	sp = dbcSpell.LookupEntryForced( 19511 );
	//if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectMiscValue[0] = 1;
	};*/

	//Glyph of Bloodthirst
	sp = dbcSpell.LookupEntryForced(58369);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
	}
	//Glyph of Vanish - has no affect :(
/*	sp = dbcSpell.LookupEntryForced(63320);
	//if(sp != NULL)
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;	//!!omg save us from this ! */
	//Glyph of Life Tap
	sp = dbcSpell.LookupEntryForced(63320);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_LIFE_TAP;
		sp->ProcOnNameHash[1] = SPELL_HASH_DARK_PACT;
		sp->EffectTriggerSpell[0] = 63321;
	}
	//Glyph of Shadowflame
	sp = dbcSpell.LookupEntryForced(63310);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_SHADOWFLAME;
		sp->EffectTriggerSpell[0] = 63311;
	}
	//Glyph of Heroic Strike
	sp = dbcSpell.LookupEntryForced(58357);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->ProcOnNameHash[0] = SPELL_HASH_HEROIC_STRIKE;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 58362;
	}
	//Glyph of Hamstring
	sp = dbcSpell.LookupEntryForced(58372);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_HAMSTRING;
	}
	//Glyph of Blocking
	sp = dbcSpell.LookupEntryForced(58375);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_SHIELD_SLAM;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 58374;
	}
	// Glyph of Enraged Regeneration
	sp = dbcSpell.LookupEntryForced(63327);
//	if(sp != NULL)
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1; 
	// Glyph of Revenge
	sp = dbcSpell.LookupEntryForced(58364);
//	if(sp != NULL)
	{
	   sp->procFlags = PROC_ON_CAST_SPELL;
	   sp->ProcOnNameHash[0] = SPELL_HASH_REVENGE;
	}
	//Glyph of Corruption
	sp = dbcSpell.LookupEntryForced(56218);
	if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0]	=	17941;
		sp->procFlags	=	PROC_ON_CAST_SPELL;
		sp->procChance = 4;
		sp->ProcOnNameHash[0] = SPELL_HASH_CORRUPTION;
	}
	// Glyph of Rune Tap
	sp = dbcSpell.LookupEntryForced(59327); 
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_RUNE_TAP;
		sp->Effect[0] = SPELL_EFFECT_NULL; //the proc already heals for 10% no need for extra 10% leading to 20%
	}
	sp = dbcSpell.LookupEntryForced(59754); 
	//if(sp != NULL)
		sp->spell_id_client = sp->Id;	//combat log issue
	// Glyph of Icy Touch
	sp = dbcSpell.LookupEntryForced(58631); 
	//if(sp != NULL)
	{
//		sp->procFlags = PROC_ON_CAST_SPELL ;
//		sp->procFlags2 |= PROC2_TARGET_SELF;
//		sp->ProcOnNameHash[0] = SPELL_HASH_ICY_TOUCH;
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1; 
	}
	// Glyph of Renewed Life
	sp = dbcSpell.LookupEntryForced(58059);
	//if(sp != NULL)
	{
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
	}
	// Glyph of Healing Wave
	sp = dbcSpell.LookupEntryForced(55440);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0]	= SPELL_AURA_PROC_TRIGGER_SPELL ;
		sp->procFlags2				|= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0]	= 55533;
		sp->procFlags				= PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0]		= SPELL_HASH_HEALING_WAVE;
	}
	// Glyph of Prayer of Healing
/*	sp = dbcSpell.LookupEntryForced(55680);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0]   =   56161;
		sp->procFlags   =   PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced(56176);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0]   =   56161;
		sp->procFlags   =   PROC_ON_CAST_SPELL;
	}*/
	sp = dbcSpell.LookupEntryForced( 32837 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0]		= SPELL_HASH_DEATH_COIL;
	}
	// Evocation for Glyph of Evocation
	sp = dbcSpell.LookupEntryForced(12051);
	//if(sp != NULL)
		sp->EffectHandler = &HandleEvocationGlyph;
	// Glyph of Ice Armor
	sp = dbcSpell.LookupEntryForced(56384);
	//if(sp != NULL)
	{
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;	//!!beware of the misc effect !
		sp->Effect[1] = SPELL_EFFECT_NULL;
	}
	// Glyph of Frostbolt
	sp = dbcSpell.LookupEntryForced(56370);
	//if(sp != NULL)
	{
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
	}
	// Glyph of Imp
	sp = dbcSpell.LookupEntryForced(56248);
	//if(sp != NULL)
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER;
		sp->EffectImplicitTargetA[ 0 ] = EFF_TARGET_PET;
	}
	// Libram of Mending
	sp = dbcSpell.LookupEntryForced( 43741 );
	//if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 100;
		sp->ProcOnNameHash[0] = SPELL_HASH_HOLY_LIGHT;
	}
	// Mystical Skyfire Diamond
	sp = dbcSpell.LookupEntryForced( 32837 );
	//if( sp != NULL )
	{
		sp->proc_interval       =       45000;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	// Lightweave Embroidery
	sp = dbcSpell.LookupEntryForced( 55776 );
	//if( sp != NULL )
	{
		sp->proc_interval       =       60000;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	// Swordguard Embroidery
	sp = dbcSpell.LookupEntryForced( 55776 );
	//if( sp != NULL )
	{
		sp->proc_interval       =       60000;
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	}
	// Chuchu's Tiny Box of Horrors
	sp = dbcSpell.LookupEntryForced( 61618 );
	//if( sp != NULL )
	{
		sp->proc_interval       =       45000;
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	}        
	//Noise Machine - Sonic Shield
	sp = dbcSpell.LookupEntryForced(54808);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0]  =   SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0]   =   55019;
		sp->procFlags   =   PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval   =   60000;
		sp->procChance  =   50;
	}
	//Pendulum of Telluric Currents
	sp = dbcSpell.LookupEntryForced(60482);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0]  =   SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0]   =   60483;
		sp->procFlags   =   PROC_ON_CAST_SPELL;
		sp->procChance  =   15;
	}

	//Create Totem of Issliruk
	sp = dbcSpell.LookupEntryForced(46816);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Aqual Quintessence
	sp = dbcSpell.LookupEntryForced(21357);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Aqual Quintessence
	sp = dbcSpell.LookupEntryForced(21357);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Banner of Provocation
	sp = dbcSpell.LookupEntryForced(27755);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Ectoplasmic Distiller
	sp = dbcSpell.LookupEntryForced(27752);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Eternal Quintessence
	sp = dbcSpell.LookupEntryForced(28439);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Frostwolf Assault Order (DND)
	sp = dbcSpell.LookupEntryForced(21654);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Extra-Dimensional Ghost Revealer
	sp = dbcSpell.LookupEntryForced(27754);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Incomplete Banner of Provocation
	sp = dbcSpell.LookupEntryForced(27756);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Replacement Illidari Tabard
	sp = dbcSpell.LookupEntryForced(41633);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Replacement Map
	sp = dbcSpell.LookupEntryForced(31446);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Replacement Whistle
	sp = dbcSpell.LookupEntryForced(40886);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//Create Restorative Draught
	sp = dbcSpell.LookupEntryForced(28149);
	//if(sp != NULL)
	{
		sp->Reagent[0] = 0;
	}

	//resurrection sickness
	sp = dbcSpell.LookupEntryForced( 15007 );
	//if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
	//ghost form
	sp = dbcSpell.LookupEntryForced( 8326 );
	//if( sp != NULL)
		sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;

	// sending packet after mounting seems to remove mount visual
	// Flying Carpet
//	sp = dbcSpell.LookupEntryForced( 61309 );
	//if( sp != NULL)
//		SpellEntryEffectSwap( sp,sp,0,2);
//	sp = dbcSpell.LookupEntryForced( 61451 );
	//if( sp != NULL)
//		SpellEntryEffectSwap( sp,sp,0,2);

	//enchant : Rune of the Fallen Crusader
	sp = dbcSpell.LookupEntryForced(53344);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
	}
	//item : Mark of Conquest
	sp = dbcSpell.LookupEntryForced( 33510 );
	//if( sp != NULL)
	{
		sp->procChance = 50;
		sp->proc_interval = 2000; //no spams please
	}
	sp = dbcSpell.LookupEntryForced(60442);// Bandit's Insignia
	//if(sp != NULL)
	{
		sp->proc_interval	=	15000;
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		SetAllSpellCoef(sp,0.0f);
	}
	sp = dbcSpell.LookupEntryForced(60442);// Bandit's Insignia
	//if(sp != NULL)
		sp->spell_id_client = sp->Id;

	//item : Val'anyr Hammer of Ancient Kings
	sp = dbcSpell.LookupEntryForced( 64415 );
	//if( sp != NULL)
	{
		sp->procFlags = PROC_ON_HEAL_SPELL;
		sp->proc_interval = 2000; //no spams please
	}
	//need this to be shield like power word
	sp = dbcSpell.LookupEntryForced( 64411 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_SCHOOL_ABSORB;
		sp->EffectBasePoints[0] = 14;
		sp->EffectMiscValue[0] = 127; //absorb on all schools
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_FRIEND;	//any target
		sp->BGR_one_buff_on_target &= ~SPELL_TYPE_BLESSING;	//don't remove other blessings :)
	}

	//item : avatar of flame
	sp = dbcSpell.LookupEntryForced( 15636 );
	//if( sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp->proc_interval = 2000; //no spams please
	}
	//item : Enchant Swordguard Embroidery
	sp = dbcSpell.LookupEntryForced( 64571 );
	//if( sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	}
	//item : Enchant Weapon - Blood Draining
	sp = dbcSpell.LookupEntryForced( 64571 );
	//if( sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->proc_interval = 2000; //no spams please
		sp->EffectTriggerSpell[0] = 64569; //this is false !! it stacks an aura that heals only if below 35% health
	}
	//item : Nitro Boosts -> should be cast spell but we simply copy whole spell over thsi one (in case that works out)
	sp = dbcSpell.LookupEntryForced( 55004 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 54861;
	}

	//Item - Rogue T9 2P Bonus (Rupture)
	sp = dbcSpell.LookupEntryForced(67209);
	//if(sp != NULL)
	{
		sp->procFlags   =   PROC_ON_SPELL_HIT;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_RUPTURE;
		sp->procChance = 20;	//well it was 2% which i think it is like nothing and players report it as bug
		sp->procCharges = 1;
	}
	//Item - Warrior T8 Melee 2P Bonus
	sp = dbcSpell.LookupEntryForced(64938);
	//if(sp != NULL)
	{
		sp->procFlags   =   PROC_ON_SPELL_CRIT_HIT | PROC_ON_CRIT_ATTACK;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_HEROIC_STRIKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_SLAM;
	}
	//Item - Rogue T8 2P Bonus
	sp = dbcSpell.LookupEntryForced(64914);
	//if(sp != NULL)
	{
		sp->procFlags   =   PROC_ON_SPELL_HIT;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEADLY_POISON;
	}
	//Item - Priest T8 Healer 4P Bonus
	sp = dbcSpell.LookupEntryForced(64912);
	//if(sp != NULL)
	{
		sp->procFlags   =   PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_POWER_WORD__SHIELD;
	}
	//Item - Priest T8 Shadow 4P Bonus
	sp = dbcSpell.LookupEntryForced(64908);
	//if(sp != NULL)
	{
		sp->procFlags   =   PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_MIND_BLAST;
	}
	//Item - Druid T8 Feral 2P Bonus
	sp = dbcSpell.LookupEntryForced(64752);
	//if(sp != NULL)
	{
		sp->procFlags   =   PROC_ON_SPELL_HIT;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->procChance = 20;	//well it was 2% which i think it is like nothing and players report it as bug
		sp->ProcOnNameHash[0] = SPELL_HASH_RAKE;
		sp->ProcOnNameHash[1] = SPELL_HASH_RIP;
		sp->ProcOnNameHash[2] = SPELL_HASH_LACERATE;
	} 
	//Item - Bleed Cost Reduction
	sp = dbcSpell.LookupEntryForced(60176);
	//if(sp != NULL)
	{
		sp->procFlags   =   PROC_ON_SPELL_HIT;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_REND;
		sp->ProcOnNameHash[1] = SPELL_HASH_DEEP_WOUNDS;
	} 
	sp = dbcSpell.LookupEntryForced( 61571 );
	//if( sp != NULL )
	{
		sp->AuraInterruptFlags = 0;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procCharges = 1;
	}
	//Item - Life Tap Bonus Spirit
	sp = dbcSpell.LookupEntryForced(60172);
	//if(sp != NULL)
	{
		sp->procFlags   =   PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_LIFE_TAP;
	} 
	//Item - Corruption Triggers Crit
	sp = dbcSpell.LookupEntryForced(60170);
	//if(sp != NULL)
	{
		sp->procFlags   =   PROC_ON_SPELL_HIT;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_CORRUPTION;
		sp->ProcOnNameHash[1] = SPELL_HASH_IMMOLATE;
	} 
	sp = dbcSpell.LookupEntryForced( 61595 );
	//if( sp != NULL )
	{
		sp->AuraInterruptFlags = 0;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procCharges = 1;
	}
	//Item - Kill Command Pet Boost
	sp = dbcSpell.LookupEntryForced(60143);
	//if(sp != NULL)
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectBasePoints[0] = 4;
	} 
	//Item - Oblit/Scourge Strike Runic Power Up
	sp = dbcSpell.LookupEntryForced(60132);
	//if(sp != NULL)
	{
		sp->procFlags   =   PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_OBLITERATE;
		sp->ProcOnNameHash[1] = SPELL_HASH_SCOURGE_STRIKE;
		sp->ProcOnNameHash[2] = SPELL_HASH_DEATH_STRIKE;
	} 
	//Item - Moonkin Starfire Bonus
	sp = dbcSpell.LookupEntryForced(46832);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags   =   PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_WRATH;
	} 
	sp = dbcSpell.LookupEntryForced(46833);
	//if(sp != NULL)
		sp->procCharges = 1;
	//Item - Item - Priest T9 Healing 4P Bonus (Divine Aegis and Empowered Renew)
	sp = dbcSpell.LookupEntryForced(67202);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp->EffectSpellGroupRelation[0][0] = 64;		//don't do this !
		sp->EffectSpellGroupRelation[0][1] = 16777216;	//don't do this !
		sp->EffectSpellGroupRelation[0][2] = 0;			//don't do this !
	} 
	//Item - Item - Priest T9 Healing 2P Bonus (Prayer of Mending)
	sp = dbcSpell.LookupEntryForced(67201);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_ADD_TO_EFFECT_VALUE_1;
		sp->EffectSpellGroupRelation[0][0] = 0;		//don't do this !
		sp->EffectSpellGroupRelation[0][1] = 32;	//don't do this !
		sp->EffectSpellGroupRelation[0][2] = 0;		//don't do this !
	} 
	//Item - Item - Shaman T8 Elemental 4P Bonus
	sp = dbcSpell.LookupEntryForced(64928);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_LIGHTNING_BOLT;
		sp->EffectTriggerSpell[0] = 50895;		//!! wrong spell but could not find better :(
	} 
	sp = dbcSpell.LookupEntryForced(50895);
	//if(sp != NULL)
		sp->spell_id_client = 64928;
	//Item - Druid T8 Restoration 4P Bonus
	sp = dbcSpell.LookupEntryForced(64760);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_REJUVENATION;
		sp->EffectTriggerSpell[0] = 64801;		
	} 
	sp = dbcSpell.LookupEntryForced(64801);
	//if(sp != NULL)
		sp->spell_id_client = 774;	//!! meed logs for correct combat log info
	//Item - Death Knight T8 Melee 4P Bonus
/*	sp = dbcSpell.LookupEntryForced(64736);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		sp->EffectSpellGroupRelation[0][0] = 0;		//don't do this !
		sp->EffectSpellGroupRelation[0][1] = 0;		//don't do this !
		sp->EffectSpellGroupRelation[0][2] = 2;		//don't do this !
	} */
	//Item - Fists of Fury
	sp = dbcSpell.LookupEntryForced(41989);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags |= PROC_ON_MELEE_ATTACK;
	} 
	//Item - The Twin Blades of Azzinoth
	sp = dbcSpell.LookupEntryForced(41434);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags |= PROC_ON_MELEE_ATTACK;
	} 
	//Item - Frozen Shadoweave
	sp = dbcSpell.LookupEntryForced( 39372 );
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags |= PROC_ON_SPELL_HIT;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 2054;		//just heal :( 99% this is wrong
	} 
	//Item - Mana Regen Proc
	sp = dbcSpell.LookupEntryForced( 38427 );
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags |= PROC_ON_MELEE_ATTACK;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->procChance = 20;
	} 
	//Item - Alacrity of the Elements
	sp = dbcSpell.LookupEntryForced( 65005 );
	//if(sp != NULL)
	{
		sp->procFlags |= PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	} 
	//Item - Death Knight T8 DPS Relic
	//!!! zack need to implement flat mod to some specific effect only cause this is modding weapon pct dmg and that is huge
/*	sp = dbcSpell.LookupEntryForced( 64962 );
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_FLAT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		sp->EffectBasePoints[0] = sp->EffectBasePoints[1];		//according to description
		sp->EffectSpellGroupRelation[0][0] = 0;		//don't do this !
		sp->EffectSpellGroupRelation[0][1] = 0;		//don't do this !
		sp->EffectSpellGroupRelation[0][2] = 1;		//don't do this !
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_FLAT_MODIFIER;
		sp->EffectMiscValue[1] = SMT_MISC_EFFECT;
		sp->EffectBasePoints[1] = sp->EffectBasePoints[2];		//according to description
		sp->EffectSpellGroupRelation[1][0] = 0;		//don't do this !
		sp->EffectSpellGroupRelation[1][1] = 4;		//don't do this !
		sp->EffectSpellGroupRelation[1][2] = 0;		//don't do this !
	} */
	//Item - Paladin T8 Holy Relic
	sp = dbcSpell.LookupEntryForced( 64956 );
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_FLAT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		sp->EffectBasePoints[0] = sp->EffectBasePoints[0] * 2;		//spell power -> heal power
	} 
	//Item - Item - Druid T8 Balance Relic
	sp = dbcSpell.LookupEntryForced( 64950 );
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_FLAT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		sp->EffectBasePoints[0] = sp->EffectBasePoints[0];
		sp->EffectSpellGroupRelation[0][0] = 2097152;	//don't do this !
		sp->EffectSpellGroupRelation[0][1] = 0;			//don't do this !
		sp->EffectSpellGroupRelation[0][2] = 0;			//don't do this !
	} 
	//Item - Item - Druid T8 Restoration Relic
	sp = dbcSpell.LookupEntryForced( 64949 );
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_FLAT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		sp->EffectBasePoints[0] = sp->EffectBasePoints[0] * 2;		//spell power -> heal power
		sp->EffectSpellGroupRelation[0][0] = 0;			//don't do this !
		sp->EffectSpellGroupRelation[0][1] = 33554432;	//don't do this !
		sp->EffectSpellGroupRelation[0][2] = 0;			//don't do this !
	} 
	//Item - Glory of the Jouster
	sp = dbcSpell.LookupEntryForced( 63251 );
	//if(sp != NULL)
	{
		sp->procFlags |= PROC_ON_MELEE_ATTACK;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->procChance = 20;
	} 
	//Item - Chains of Ice Frost Rune Refresh
	sp = dbcSpell.LookupEntryForced( 62459 );
	//if(sp != NULL)
	{
		sp->procFlags |= PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_CHAINS_OF_ICE;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->procChance = 20;
	} 
	//some whatever GM spell to make them visible to players
	sp = dbcSpell.LookupEntryForced( 37729 );
	//if( sp != NULL)
		sp->Attributes |=ATTRIBUTES_CANT_CANCEL;	
	//some whatever GM spell to root player
	sp = dbcSpell.LookupEntryForced( 39258 );
	//if( sp != NULL)
		sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;	
	//GM spell : uber heal over time to be self cast only
	sp = dbcSpell.LookupEntryForced( 30839 );
	//if( sp != NULL)
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;	
	//GM spell : uber heal over time to be self cast only
	sp = dbcSpell.LookupEntryForced( 1908 );
	//if( sp != NULL)
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;	
	//Item - Warrior T10 Melee 2P Bonus
	sp = dbcSpell.LookupEntryForced(70854);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_SPELL_HIT;
		sp->ProcOnNameHash[0] = SPELL_HASH_DEEP_WOUNDS;
	} 
	//Item - Warrior T10 Melee 4P Bonus
	//You have a $s1% chance for your Bloodsurge and Sudden Death talents to grant 2 charges of their effect instead of 1, reduce the global cooldown on Execute or Slam by ${$m3/-1000}.1 sec, and for the duration of the effect to be increased by $s2%.
/*	sp = dbcSpell.LookupEntryForced(70847);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 70847;	//self proc ? :O
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOODSURGE;
		sp->ProcOnNameHash[1] = SPELL_HASH_SUDDEN_DEATH;
	}  */
	//Item - Warlock T10 4P Bonus
	sp = dbcSpell.LookupEntryForced(70841);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_SPELL_HIT;
		sp->ProcOnNameHash[0] = SPELL_HASH_IMMOLATE;
		sp->ProcOnNameHash[1] = SPELL_HASH_UNSTABLE_AFFLICTION;
	} 
	//Item - Shaman T10 Enhancement 4P Bonus
	sp = dbcSpell.LookupEntryForced(70832);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 70831;	//self proc ? :O
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_MAELSTROM_WEAPON;
	} 
	//Item - Shaman T10 Enhancement 2P Bonus
	sp = dbcSpell.LookupEntryForced(70830);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_SHAMANISTIC_RAGE;
	} 
/*	//Item - Shaman T10 Elemental 2P Bonus
	sp = dbcSpell.LookupEntryForced(70811);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 70811;	//self proc ? :O
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_LIGHTNING_BOLT;
		sp->ProcOnNameHash[1] = SPELL_HASH_CHAIN_LIGHTNING;
	} */
	//Item - Shaman T10 Restoration 4P Bonus
	sp = dbcSpell.LookupEntryForced(70808);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 70809;	
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT_VICTIM;
		sp->ProcOnNameHash[0] = SPELL_HASH_CHAIN_HEAL;
	} 
	//Item - Shaman T10 Restoration 2P Bonus
	sp = dbcSpell.LookupEntryForced(70807);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_RIPTIDE;
	} 
	//Item - Rogue T10 2P Bonus
	sp = dbcSpell.LookupEntryForced(70805);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_TRICKS_OF_THE_TRADE;
	} 
	//Item - Rogue T10 4P Bonus
	sp = dbcSpell.LookupEntryForced(70803);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
	} 
	//Item - Priest T10 Healer 4P Bonus
/*	sp = dbcSpell.LookupEntryForced(70798);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_CIRCLE_OF_HEALING;
		sp->ProcOnNameHash[1] = SPELL_HASH_PENANCE;
	} 
	sp = dbcSpell.LookupEntryForced(70799);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectTriggerSpell[0] = 70799;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_FLASH_HEAL;
		sp->ProcOnNameHash[1] = SPELL_HASH_CIRCLE_OF_HEALING;
		sp->ProcOnNameHash[2] = SPELL_HASH_PENANCE;
		sp->procCharges = 0;
	}*/
	//Item - Priest T10 Healer 2P Bonus
	sp = dbcSpell.LookupEntryForced(70770);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 70809;	//self proc ? :O
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_FLASH_HEAL;
	} 
	//Item - Paladin T10 Retribution 2P Bonus
	sp = dbcSpell.LookupEntryForced(70765);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 70765;	//self proc ? :O
	} 
	//Item - Paladin T10 Protection 4P Bonus
	sp = dbcSpell.LookupEntryForced(70761);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_DIVINE_PLEA;
	} 
	//Item - Paladin T10 Holy 4P Bonus
	sp = dbcSpell.LookupEntryForced(70756);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_HOLY_SHOCK;
	} 
	sp = dbcSpell.LookupEntryForced(70757);
	//if(sp != NULL)
	{
		sp->procCharges = 1;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	//Item - Paladin T10 Holy 2P Bonus
	sp = dbcSpell.LookupEntryForced(70755);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 71166;	
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_DIVINE_ILLUMINATION;
	} 
	sp = dbcSpell.LookupEntryForced(71166);
	//if(sp != NULL)
	{
		sp->DurationIndex = AURA_DURATION_INDEX_15_SECONDS;
		sp->NameHash = SPELL_HASH_DIVINE_ILLUMINATION_custom; //or it will remove other divine illumination
	}
	//Item - Mage T10 2P Bonus
	sp = dbcSpell.LookupEntryForced(70752);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 70753;	
		sp->procFlags = PROC_ON_AURA_REMOVE;
		sp->ProcOnNameHash[0] = SPELL_HASH_HOT_STREAK;
		sp->ProcOnNameHash[1] = SPELL_HASH_MISSILE_BARRAGE;
		sp->ProcOnNameHash[2] = SPELL_HASH_BRAIN_FREEZE;
	} 
	//Item - Mage T10 4P Bonus
	sp = dbcSpell.LookupEntryForced(70748);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_MIRROR_IMAGE;
	} 
	//Item - Hunter T10 4P Bonus
	sp = dbcSpell.LookupEntryForced(70730);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_SERPENT_STING;
		sp->ProcOnNameHash[1] = SPELL_HASH_WYVERN_STING;
	} 
	//Item - Hunter T10 2P Bonus
	sp = dbcSpell.LookupEntryForced(70727);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_RANGED_ATTACK;
	} 
	//Item - Druid T10 Balance 4P Bonus
	sp = dbcSpell.LookupEntryForced(70723);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 71023;	
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp->ProcOnNameHash[0] = SPELL_HASH_STARFIRE;
		sp->ProcOnNameHash[1] = SPELL_HASH_WRATH;
	} 
	//Item - Druid T10 Balance 2P Bonus
	sp = dbcSpell.LookupEntryForced(70718);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 70721;	
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_CLEARCASTING;
	} 
	//Item - Druid T10 Restoration 4P Bonus (Rejuvenation)
	sp = dbcSpell.LookupEntryForced(70664);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 70664;	//!self proc
		sp->procFlags = PROC_ON_HEAL_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_REJUVENATION;
		sp->procChance = 10;
	} 
	//Item - Druid T10 Restoration 2P Bonus
/*	sp = dbcSpell.LookupEntryForced(70658);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 70664;	//!self proc
		sp->procFlags = PROC_ON_SPELL_HIT;
		sp->ProcOnNameHash[0] = SPELL_HASH_WILD_GROWTH;
	} */
	//Item - Death Knight T10 Melee 4P Bonus
	sp = dbcSpell.LookupEntryForced(70656);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_SCRIPTED_PROCTEST;
	} 
	//Item - Death Knight T10 Tank 4P Bonus
	sp = dbcSpell.LookupEntryForced(70652);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BLOOD_TAP;
	} 
	//Item - Death Knight T10 Tank 2P Bonus
	sp = dbcSpell.LookupEntryForced(70650);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		sp->EffectSpellGroupRelation[0][0] = 32;
	} 
	//Purified Shard of the Scale - Equip Effect
	sp = dbcSpell.LookupEntryForced(69755);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 69734;	
		sp->procFlags = PROC_ON_CAST_SPELL;
	} 

	//Item - Chamber of Aspects 25 Melee Trinket
	sp = dbcSpell.LookupEntryForced(75455);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE | PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
//		sp->proc_interval = 45000;
	}
	//Item - Chamber of Aspects 25 Heroic Melee Trinket
	sp = dbcSpell.LookupEntryForced(75457);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE | PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
//		sp->proc_interval = 45000;
	}

	//Item - Chamber of Aspects 25 Nuker Trinket
	sp = dbcSpell.LookupEntryForced(75465);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_ANY_SPELL_DAMAGE_DONE;
//		sp->proc_interval = 45000;
	}
	//Item - Chamber of Aspects 25 Heroic Nuker Trinket
	sp = dbcSpell.LookupEntryForced(75474);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_ANY_SPELL_DAMAGE_DONE;
//		sp->proc_interval = 45000;
	}

	//Item - Chamber of Aspects 25 Tank Trinket
	sp = dbcSpell.LookupEntryForced(75475);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 45000;
	}
	//Item - Chamber of Aspects 25 Heroic Tank Trinket
	sp = dbcSpell.LookupEntryForced(75481);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 45000;
	}

	//Eyes of Twilight
	sp = dbcSpell.LookupEntryForced(75490);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
//		sp->proc_interval = 45000;
	}
	//Eyes of Twilight
	sp = dbcSpell.LookupEntryForced(75495);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
//		sp->proc_interval = 45000;
	}

	//Item - Icecrown 10 Heroic Tank Trinket
	sp = dbcSpell.LookupEntryForced(71578);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 2000;
	}
	//Item - Icecrown 10 Normal Tank Trinket
	sp = dbcSpell.LookupEntryForced(71576);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 2000;
	}

	//Item - Icecrown 10 Normal Melee Trinket
	sp = dbcSpell.LookupEntryForced(71402);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE | PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		sp->procChance = 20;
		sp->proc_interval = 45000;
	}
	//Item - Icecrown 10 Heroic Melee Trinket
	sp = dbcSpell.LookupEntryForced(71540);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE | PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		sp->procChance = 30;
		sp->proc_interval = 45000;
	}
	//Item - Icecrown 25 Normal Melee Trinket
	sp = dbcSpell.LookupEntryForced(71519);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 71519;	//!self proc
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		sp->proc_interval = 90000;		//cause spell duration is 30 sec
		sp->procChance = 30;	//no idea really
	}
	//Item - Icecrown 25 Heroic Melee Trinket
	sp = dbcSpell.LookupEntryForced(71562);
	//if(sp != NULL)
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 71519;	//!self proc
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		sp->proc_interval = 90000;		//cause spell duration is 30 sec
		sp->procChance = 30;	//no idea really
	}

	//Item - Icecrown Reputation Ring Healer Trigger
	sp = dbcSpell.LookupEntryForced(72419);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Item - Icecrown Reputation Ring Caster Trigger
	sp = dbcSpell.LookupEntryForced(72417);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Item - Icecrown Reputation Ring Tank Trigger
	sp = dbcSpell.LookupEntryForced(72415);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
	//Item - Icecrown Reputation Ring Melee
	sp = dbcSpell.LookupEntryForced(72413);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	//Item - Icecrown 25 Normal Caster Weapon Proc
	sp = dbcSpell.LookupEntryForced(71845);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Item - Icecrown 25 Normal Ranged Weapon Proc
	sp = dbcSpell.LookupEntryForced(71835);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_RANGED_ATTACK;
	//Item - Icecrown 25 Normal Tank Trinket 1
	sp = dbcSpell.LookupEntryForced(71634);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
	//Item - Icecrown 25 Heroic Tank Trinket 1
	sp = dbcSpell.LookupEntryForced(71640);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
	//Item - Icecrown 25 Normal Healer Trinket 2
	sp = dbcSpell.LookupEntryForced(71611);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Item - Icecrown 25 Heroic Healer Trinket 2
	sp = dbcSpell.LookupEntryForced(71642);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Item - Icecrown 25 Emblem Healer Trinket
	sp = dbcSpell.LookupEntryForced(71585);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Item - Icecrown 10 Normal Caster Trinket
	sp = dbcSpell.LookupEntryForced(71571);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE;
		sp->proc_interval = 1;	//they say this procs all the time
	}
	//Item - Icecrown Dungeon Healer Trinket
	sp = dbcSpell.LookupEntryForced(71567);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Item - Icecrown Dungeon Melee Trinket
	sp = dbcSpell.LookupEntryForced(71404);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_RANGED_CRIT_ATTACK;
	//Item - Icecrown 25 Emblem Melee Trinket
	sp = dbcSpell.LookupEntryForced(71397);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
		sp->proc_interval = 1001;	//each attack ...
	}
	//Item - Icecrown 25 Heroic Dagger Proc
	sp = dbcSpell.LookupEntryForced(71892);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 71888;
		sp->procChance = 20;
	}
	//Item - Icecrown 25 Normal Dagger Proc
	sp = dbcSpell.LookupEntryForced(71880);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 71881;
		sp->procChance = 20;
	}
	//Item - Icecrown 25 Normal Slow Melee Weapon Proc
	sp = dbcSpell.LookupEntryForced(71876);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp->procChance = 20;
	}
	//Item - Icecrown 25 Heroic Tank Weapon Proc
	sp = dbcSpell.LookupEntryForced(71873);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp->procChance = 20;
	}
	//Item - Icecrown 25 Normal Tank Weapon Proc
	sp = dbcSpell.LookupEntryForced(71871);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp->procChance = 20;
	}
	//Item - Icecrown 25 Heroic Healer Weapon Proc
	sp = dbcSpell.LookupEntryForced(71868);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_HEAL_SPELL;
		sp->procChance = 20;
	}
	//Item - Icecrown 25 Normal Healer Weapon Proc
	sp = dbcSpell.LookupEntryForced(71865);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_HEAL_SPELL;
		sp->procChance = 20;
	}
	//Item - Icecrown 25 Heroic Ranged Weapon Proc
	sp = dbcSpell.LookupEntryForced(71836);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_RANGED_ATTACK;
	//Item - Icecrown 25 Normal Caster Trinket 1 Base
	sp = dbcSpell.LookupEntryForced(71602);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Item - Icecrown 25 Heroic Caster Trinket 1 Base
	sp = dbcSpell.LookupEntryForced(71645);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Item - Icecrown 25 Normal Caster Trinket 1 Base - the proc
	dbcSpell.LookupEntryForced(71600)->DurationIndex = dbcSpell.LookupEntryForced(71601)->DurationIndex;
	//Item - Icecrown 25 Heroic Caster Trinket 1 Base - the proc
	dbcSpell.LookupEntryForced(71643)->DurationIndex = dbcSpell.LookupEntryForced(71644)->DurationIndex;

	//Item - Icecrown 25 Normal Caster Trinket 2
	sp = dbcSpell.LookupEntryForced(71606);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_SPELL_HIT;
		sp->proc_interval = 45000;
	}
	//Item - Icecrown 25 Heroic Caster Trinket 2
	sp = dbcSpell.LookupEntryForced(71637);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->proc_interval = 45000;
	}
	//Item - Icecrown 25 Heroic Caster Trinket 2
	sp = dbcSpell.LookupEntryForced(71637);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_SPELL_HIT;
		sp->proc_interval = 45000;
	}
	//Item - Icecrown 10 Normal Tank Trinket
	sp = dbcSpell.LookupEntryForced(71576);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
	//Deadly Precision
	sp = dbcSpell.LookupEntryForced(71563);
	//if(sp != NULL)
	{
//		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
//		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
//		sp->EffectTriggerSpell[0] = 71564;
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 71564;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 71564;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->Effect[2] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 71564;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
		sp->chained_cast = dbcSpell.LookupEntryForced(71564); //still need 1 more cast to get 5
	}
	//Anger Capacitor
	sp = dbcSpell.LookupEntryForced(71545);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 71432;
	}
	//Anger Capacitor
	sp = dbcSpell.LookupEntryForced(71406);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 71432;
	}
	//Unsated Craving - !!! no description !!!
	sp = dbcSpell.LookupEntryForced(71168);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	//Item - Paladin T10 Protection Relic (Shield of Righteousness)
	sp = dbcSpell.LookupEntryForced(71194);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_SHIELD_OF_RIGHTEOUSNESS;
	}
	//Item - Death Knight T10 Tank Relic (Runestrike)
	sp = dbcSpell.LookupEntryForced(71228);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_RUNE_STRIKE;
	}
	//Item - Death Knight T10 DPS Relic (Obliterate, Scourge Strike, Death Strike)
	sp = dbcSpell.LookupEntryForced(71226);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_OBLITERATE;
		sp->ProcOnNameHash[1] = SPELL_HASH_SCOURGE_STRIKE;
		sp->ProcOnNameHash[2] = SPELL_HASH_DEATH_STRIKE;
	}
	//Item - Shaman T10 Restoration Relic (Riptide)
	sp = dbcSpell.LookupEntryForced(71217);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_RIPTIDE;
	}
	//Item - Shaman T10 Enhancement Relic (Stormstrike)
	sp = dbcSpell.LookupEntryForced(71214);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_STORMSTRIKE;
	}
	//Item - Shaman T10 Elemental Relic (Shocks)
	sp = dbcSpell.LookupEntryForced(71198);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
		sp->ProcOnNameHash[0] = SPELL_HASH_FLAME_SHOCK;
	}
	//Item - Paladin T10 Holy Relic (Holy Shock)
	sp = dbcSpell.LookupEntryForced(71191);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_HOLY_SHOCK;
	}
	//Item - Paladin T10 Retribution Relic (Crusader Strike)
	sp = dbcSpell.LookupEntryForced(71186);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->ProcOnNameHash[0] = SPELL_HASH_CRUSADER_STRIKE;
		sp->proc_interval = 1;	//they say this procs all the time
	}
	//Item - Druid T10 Restoration Relic (Rejuvenation)
	sp = dbcSpell.LookupEntryForced(71178);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
		sp->ProcOnNameHash[0] = SPELL_HASH_REJUVENATION;
	}
	//Item - Druid T10 Balance Relic (Moonfire and Insect Swarm)
	sp = dbcSpell.LookupEntryForced(71176);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
		sp->ProcOnNameHash[0] = SPELL_HASH_INSECT_SWARM;
		sp->ProcOnNameHash[1] = SPELL_HASH_MOONFIRE;
	}
	//Item - Druid T10 Feral Relic (Rake and Lacerate)
	sp = dbcSpell.LookupEntryForced(71174);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT | PROC_ON_MELEE_ATTACK;
		sp->ProcOnNameHash[0] = SPELL_HASH_LACERATE;
		sp->ProcOnNameHash[1] = SPELL_HASH_RAKE;
	}
	//Escalating Power
	sp = dbcSpell.LookupEntryForced(67740);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Escalating Power
	sp = dbcSpell.LookupEntryForced(67726);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Rising Fury
	sp = dbcSpell.LookupEntryForced(67738);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	//Volatile Power
	sp = dbcSpell.LookupEntryForced(67736);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Coliseum 5 Melee Trinket
	sp = dbcSpell.LookupEntryForced(67672);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
	//Coliseum 5 CasterTrinket
	sp = dbcSpell.LookupEntryForced(67670);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Coliseum 5 Healer Trinket
	sp = dbcSpell.LookupEntryForced(67667);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Coliseum 5 Tank Trinket
	sp = dbcSpell.LookupEntryForced(67653);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 45000;
	}
	//Item - Druid T9 Balance Relic (Moonfire)
	sp = dbcSpell.LookupEntryForced(67361);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
		sp->ProcOnNameHash[0] = SPELL_HASH_MOONFIRE;
	}
	//Item - Druid T9 Restoration Relic (Rejuvenation)
	sp = dbcSpell.LookupEntryForced(67356);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
		sp->ProcOnNameHash[0] = SPELL_HASH_REJUVENATION;
	}
	//Item - Druid T9 Feral Relic (Lacerate, Swipe, Mangle, and Shred)
	sp = dbcSpell.LookupEntryForced(67353);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
		sp->ProcOnNameHash[0] = SPELL_HASH_LACERATE;
		sp->ProcOnNameHash[1] = SPELL_HASH_SWIPE;
		sp->ProcOnNameHash[2] = SPELL_HASH_MANGLE;
		sp->EffectTriggerSpell[0] = 67354;
	}
	//Bonus Mana Regen
	sp = dbcSpell.LookupEntryForced(65002);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Blessed Book of Nagrand
	sp = dbcSpell.LookupEntryForced(32403);
	//if(sp != NULL)
		sp->EffectApplyAuraName[0] = SPELL_AURA_OVERRIDE_CLASS_SCRIPTS;
	//Item - Druid T8 Feral Relic
	sp = dbcSpell.LookupEntryForced(64952);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT;
		sp->ProcOnNameHash[0] = SPELL_HASH_MANGLE__BEAR_;
		sp->ProcOnNameHash[1] = SPELL_HASH_MANGLE__CAT_;
	}
	//The General's Heart
	sp = dbcSpell.LookupEntryForced(64764);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
	//Justice
	sp = dbcSpell.LookupEntryForced(61324);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->ProcOnNameHash[0] = SPELL_HASH_DIVINE_STORM;
	}
	//LK Arena 5 Gladiator's Idol of Steadfastness
	sp = dbcSpell.LookupEntryForced(60724);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_MOONFIRE;
	}
	//LK Arena 4 Gladiator's Idol of Steadfastness
	sp = dbcSpell.LookupEntryForced(60722);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procFlags2 = PROC2_TARGET_SELF;
		sp->ProcOnNameHash[0] = SPELL_HASH_MOONFIRE;
	}
	//Deadly Gladiator's Idol of Steadfastness
	sp = dbcSpell.LookupEntryForced(60719);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_MOONFIRE;
	}
	//Hateful Gladiator's Idol of Steadfastness
	sp = dbcSpell.LookupEntryForced(60717);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_MOONFIRE;
	}
	//Savage Gladiator's Idol of Steadfastness
	sp = dbcSpell.LookupEntryForced(60710);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_MOONFIRE;
	}
	//Savage Gladiator's Totem of Survival
	sp = dbcSpell.LookupEntryForced(60564);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_SHOCK;
	}
	//Forethought Talisman
	sp = dbcSpell.LookupEntryForced(60529);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Spark of Life
	sp = dbcSpell.LookupEntryForced(60519);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Talisman of Troll Divinity
	sp = dbcSpell.LookupEntryForced(60517);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Soul Preserver
	sp = dbcSpell.LookupEntryForced(60510);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;

	//Extract of Necromatic Power
	sp = dbcSpell.LookupEntryForced(60487);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_SPELL_HIT;
	sp = dbcSpell.LookupEntryForced( 60488 );
	//if( sp != NULL )
		sp->spell_id_client = sp->Id;

	//Signet of Edward the Odd
	sp = dbcSpell.LookupEntryForced(60317);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_RANGED_ATTACK | PROC_ON_MELEE_ATTACK;
	//Essence of Gossamer
	sp = dbcSpell.LookupEntryForced(60221);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
	//Rage of the Unraveller
	sp = dbcSpell.LookupEntryForced(60066);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CRIT_ATTACK;
	//Flow of Time
	sp = dbcSpell.LookupEntryForced(60061);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_SPELL_HIT | PROC_ON_CAST_SPELL;
	//Frenzyheart Fury
	sp = dbcSpell.LookupEntryForced(59818);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_TARGET_DIE;
	//Oracle Ablutions
	sp = dbcSpell.LookupEntryForced(59787);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_TARGET_DIE;
	//Chagrin
	sp = dbcSpell.LookupEntryForced(59345);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_RANGED_ATTACK | PROC_ON_MELEE_ATTACK;
	//Worg Tooth Oatmeal Stout
	sp = dbcSpell.LookupEntryForced(58444);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	//Airy Pale Ale
	sp = dbcSpell.LookupEntryForced(58442);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Increased Spirit
	sp = dbcSpell.LookupEntryForced(57907);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_MOONFIRE;
	}
	//Chilling Blow
	sp = dbcSpell.LookupEntryForced(55755);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	//Argent Fury
	sp = dbcSpell.LookupEntryForced(55747);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_RANGED_ATTACK | PROC_ON_MELEE_ATTACK;
	//Chilled Shot
	sp = dbcSpell.LookupEntryForced(55735);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_RANGED_ATTACK;
	//Purified Spirit
	sp = dbcSpell.LookupEntryForced(54838);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Star of Light
	sp = dbcSpell.LookupEntryForced(54738);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Power of the Great Ones
	sp = dbcSpell.LookupEntryForced(53371);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_RANGED_ATTACK | PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;
	//Retaliation
	sp = dbcSpell.LookupEntryForced(52423);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_DODGE_VICTIM;
	//Deflection
	sp = dbcSpell.LookupEntryForced(52420);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
	//Snap and Snarl
	sp = dbcSpell.LookupEntryForced(52020);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->ProcOnNameHash[0] = SPELL_HASH_SHRED;
		sp->ProcOnNameHash[1] = SPELL_HASH_SWIPE;
	}
	//Venomous Breath Aura
	sp = dbcSpell.LookupEntryForced(51414);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
	//Venture Company Beatdown!
	sp = dbcSpell.LookupEntryForced(51352);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_TARGET_DIE;
	//Venture Company Beatdown!
	sp = dbcSpell.LookupEntryForced(51346);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_TARGET_DIE;
	//Elemental Tenacity
	sp = dbcSpell.LookupEntryForced(48837);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_SHOCK;
	}
	//Primal Instinct
	sp = dbcSpell.LookupEntryForced(48833);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_MELEE_ATTACK;
		sp->ProcOnNameHash[0] = SPELL_HASH_MANGLE__BEAR_;
		sp->ProcOnNameHash[1] = SPELL_HASH_MANGLE__CAT_;
	}
	//Black Bow of the Betrayer
	sp = dbcSpell.LookupEntryForced(46939);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_RANGED_ATTACK;
	//Brutal Libram of Justice
	sp = dbcSpell.LookupEntryForced(46092);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_FLASH_OF_LIGHT;
	}
	//Item - T7 Melee Trinket Base
	sp = dbcSpell.LookupEntryForced(45355);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
	//Item - Sunwell Dungeon Melee Trinket
	sp = dbcSpell.LookupEntryForced(45354);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	//Evasive Maneuvers
	sp = dbcSpell.LookupEntryForced(45057);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
	//Augment Pain
	sp = dbcSpell.LookupEntryForced(45054);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_SPELL_HIT;
	//Charm of the Raging Defender
	sp = dbcSpell.LookupEntryForced(43822);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
	//Charm of the Witch Doctor
	sp = dbcSpell.LookupEntryForced(43820);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectTriggerSpell[0] = 43821;
	}
	//Charm of Mighty Mojo
	sp = dbcSpell.LookupEntryForced(43818);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Charm of the Bloodletter
	sp = dbcSpell.LookupEntryForced(43816);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	//Fire Extinguisher
	sp = dbcSpell.LookupEntryForced(55037);
	//if(sp != NULL)
		sp->Effect[0] = SPELL_EFFECT_NULL;
	//Elemental Strength
	sp = dbcSpell.LookupEntryForced(43748);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_SHOCK;
	}
	//Elemental Strength
	sp = dbcSpell.LookupEntryForced(43745);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_CRUSADER_S_COMMAND;
	}
	//Vengeful Libram of Justice
	sp = dbcSpell.LookupEntryForced(43726);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_FLASH_OF_LIGHT;
	}
	//Merciless Libram of Justice
	sp = dbcSpell.LookupEntryForced(42368);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_FLASH_OF_LIGHT;
	}
	//Fury of the Crashing Waves
	sp = dbcSpell.LookupEntryForced(42083);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CRIT_ATTACK;
	//Aviana's Will
	sp = dbcSpell.LookupEntryForced(41262);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_TARGET_DIE;
	//Aviana's Purpose
	sp = dbcSpell.LookupEntryForced(41260);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_TARGET_DIE;
	//Bonus Healing
	sp = dbcSpell.LookupEntryForced(40971);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Illidan Tank Shield
	sp = dbcSpell.LookupEntryForced(40407);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
	//Siphon Essence
	sp = dbcSpell.LookupEntryForced(40291);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	//Aura of Vengeance
	sp = dbcSpell.LookupEntryForced(39444);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
	//Aura of Wrath
	sp = dbcSpell.LookupEntryForced(39442);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_ANY_SPELL_DAMAGE_DONE;
	//Aura of the Crusade
	sp = dbcSpell.LookupEntryForced(39438);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
	//Crit Proc Spell Damage
	sp = dbcSpell.LookupEntryForced(38347);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	//Forgotten Knowledge
	sp = dbcSpell.LookupEntryForced(38319);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//HoTs on Heals
	sp = dbcSpell.LookupEntryForced(38299);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_CAST_SPELL;
	//Santos' Blessing
	sp = dbcSpell.LookupEntryForced(38290);
	//if(sp != NULL)
		sp->procFlags = PROC_ON_RANGED_ATTACK;
	//Healing Discount
	sp = dbcSpell.LookupEntryForced(37705);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectTriggerSpell[0] = 37706;
	}
	//Improved Battle Shout
	sp = dbcSpell.LookupEntryForced(37536);
	//if(sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->ProcOnNameHash[0] = SPELL_HASH_BATTLE_SHOUT;
	}

	//Shiny Shard of the Scale - Equip Effect
	sp = dbcSpell.LookupEntryForced(69739);
	//if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 62402;
		sp->procFlags = PROC_ON_CAST_SPELL;
	} 
	//rocket boots
	sp2 = dbcSpell.LookupEntryForced( 13141 );
	sp = dbcSpell.LookupEntryForced( 51582 );
	//if( sp != NULL)
	{
		SpellEntryEffectCopy( sp2,sp,0,0);
		sp->DurationIndex = sp2->DurationIndex;
	}
	//Holiday - Valentine - Romantic Picnic Near Basket Check
	sp = dbcSpell.LookupEntryForced( 45119 );
	sp2 = dbcSpell.LookupEntryForced( 45093 );
	//if( sp != NULL)
	{
		SpellEntryEffectCopy( sp2,sp,0,0);
		sp->EffectMiscValue[0] = 187267; //anything
	}

	//Release of Light - missing cooldown from item Bauble of True Blood
	sp = dbcSpell.LookupEntryForced( 71607 );
	//if( sp != NULL)
	{
		sp->DurationIndex = 4; //2 minutes - no, this is not related to cooldown !
		sp->RecoveryTime = 2*60*1000;	//2 minutes
	}

	//Cast Fishing Net - missing cooldown from item 
	sp = dbcSpell.LookupEntryForced( 29866 );
	//if( sp != NULL)
	{
		sp->DurationIndex = 4; //2 minutes - no, this is not related to cooldown !
		sp->RecoveryTime = 2*60*1000;	//2 minutes
	}

	//fish feast 
	sp = dbcSpell.LookupEntryForced( 57426 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF; //anything
	}
//	sp2 = dbcSpell.LookupEntryForced( 57079 );
	//if( sp != NULL)
//		sp2->EffectBasePoints[1] = sp2->EffectBasePoints[1]*30/5;	//when used, this spell should have this effect actually
	sp2 = dbcSpell.LookupEntryForced( 57073 );
	//if( sp != NULL)
		sp2->AuraInterruptFlags |= AURA_INTERRUPT_ON_STAND_UP | AURA_INTERRUPT_ON_MOVEMENT;
	sp2 = dbcSpell.LookupEntryForced( 45548 );
	//if( sp != NULL)
		sp2->AuraInterruptFlags |= AURA_INTERRUPT_ON_STAND_UP | AURA_INTERRUPT_ON_MOVEMENT;
	sp = dbcSpell.LookupEntryForced( 57397 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;	
		sp->EffectTriggerSpell[0] = 45548; //health
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF; //anything
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;	
		sp->EffectTriggerSpell[1] = 57073; //mana
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF; //anything
		sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;	
		sp->EffectApplyAuraName[2] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 57294; //57079 well fed -> sadly this needs to be scripted to add SP or AP depending on 
		sp->EffectAmplitude[2] = 10000;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF; //anything
		sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_STAND_UP | AURA_INTERRUPT_ON_MOVEMENT;
		sp->DurationIndex = sp2->DurationIndex;	//same
	}
	sp = dbcSpell.LookupEntryForced( 57294 );
	//if( sp != NULL)
		sp->chained_cast = dbcSpell.LookupEntryForced( 59690 );	//Well Fed (DND) -> needs extra setup

	//Small Feast - not all used 58474,7353,45548,57073,58477,7353,29119,58479,406 
	sp = dbcSpell.LookupEntryForced( 58474 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF; //anything
	}
	sp2 = dbcSpell.LookupEntryForced( 45548 );
	sp = dbcSpell.LookupEntryForced( 58475 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;	
		sp->EffectTriggerSpell[0] = 45548; //health
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF; //anything
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;	
		sp->EffectTriggerSpell[1] = 57073; //mana
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF; //anything
		sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;	
		sp->EffectApplyAuraName[2] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 57079; //well fed
		sp->EffectAmplitude[2] = 10000;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF; //anything
		sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_STAND_UP | AURA_INTERRUPT_ON_MOVEMENT;
		sp->DurationIndex = sp2->DurationIndex;	//same
		sp->chained_cast = dbcSpell.LookupEntryForced( 58479 );	//Nearly Well Fed
	}
	sp = dbcSpell.LookupEntryForced( 58479 );
	//if( sp != NULL)
		sp->AuraInterruptFlags = 0;

	//Great Feast - 57301,57337,45548,57073,57338,7353,57294,59690
	sp = dbcSpell.LookupEntryForced( 57301 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF; //anything
	}
	sp2 = dbcSpell.LookupEntryForced( 45548 );
	sp = dbcSpell.LookupEntryForced( 57337 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;	
		sp->EffectTriggerSpell[0] = 45548; //health
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF; //anything
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;	
		sp->EffectTriggerSpell[1] = 57073; //mana
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF; //anything
		sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;	
		sp->EffectApplyAuraName[2] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 57294; //well fed
		sp->EffectAmplitude[2] = 10000;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF; //anything
		sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_STAND_UP | AURA_INTERRUPT_ON_MOVEMENT;
		sp->DurationIndex = sp2->DurationIndex;	//same
	}

	//Gigantic Feast -> spells used (58465,58466,45548,57073,58467,406,58468)
	sp = dbcSpell.LookupEntryForced( 58465 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF; //anything
	}
	sp2 = dbcSpell.LookupEntryForced( 45548 );
	sp = dbcSpell.LookupEntryForced( 58466 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;	
		sp->EffectTriggerSpell[0] = 45548; //health
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF; //anything
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;	
		sp->EffectTriggerSpell[1] = 57073; //mana
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF; //anything
		sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;	
		sp->EffectApplyAuraName[2] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 57338; //57079 well fed -> sadly this needs to be scripted to add SP or AP depending on 
		sp->EffectAmplitude[2] = 10000;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF; //anything
		sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_STAND_UP | AURA_INTERRUPT_ON_MOVEMENT;
		sp->DurationIndex = sp2->DurationIndex;	//same
		sp->chained_cast = dbcSpell.LookupEntryForced( 58468 );	//Hugely Well Fed
	}
	sp = dbcSpell.LookupEntryForced( 58468 );
	//if( sp != NULL)
		sp->AuraInterruptFlags = 0;

	//Invincible - the mount
	sp = dbcSpell.LookupEntryForced( 72286 );
	//if( sp != NULL)
	{
/*		SpellEntry *sp2 = dbcSpell.LookupEntryForced( 32345 ); //Peep the Phoenix Mount
		//if( sp2 )
		{
			SpellEntryEffectCopy(sp2,sp,1,1);//haste effect
			SpellEntryEffectCopy(sp2,sp,2,2);//haste effect
		}
		sp->EffectMiscValue[1] = 27153;	//headless horseman ?
		
		sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_CAST_SPELL | AURA_INTERRUPT_ON_MOUNT; */
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->Effect[1] = SPELL_EFFECT_NULL;	
	}
	//celestial steed - the mount - this mount actually casts some other spells depending on the place you are
	sp = dbcSpell.LookupEntryForced( 75614 );
	//if( sp != NULL)
	{
/*		SpellEntry *sp2 = dbcSpell.LookupEntryForced( 32345 ); //Peep the Phoenix Mount
		//if( sp2 )
		{
			SpellEntryEffectCopy(sp2,sp,1,1);//haste effect
			SpellEntryEffectCopy(sp2,sp,2,2);//haste effect
		}
		sp->EffectMiscValue[1] = 27153;	//headless horseman ?*/
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->Effect[1] = SPELL_EFFECT_NULL;	
	}
	//Winged Steed of the Ebon Blade
	sp = dbcSpell.LookupEntryForced( 54729 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->Effect[1] = SPELL_EFFECT_NULL;	
	}
	//Headless Horseman's Mount
	sp = dbcSpell.LookupEntryForced( 48025 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->Effect[1] = SPELL_EFFECT_NULL;	
	}
	//Big Love Rocket
	sp = dbcSpell.LookupEntryForced( 71342 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->Effect[1] = SPELL_EFFECT_NULL;	
	}
	//X-53 Touring Rocket
	sp = dbcSpell.LookupEntryForced( 75973 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->Effect[1] = SPELL_EFFECT_NULL;	
	}
	//Blazing Hippogryph
	sp = dbcSpell.LookupEntryForced( 75973 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->Effect[1] = SPELL_EFFECT_NULL;	
	}
	//Magic Rooster
	sp = dbcSpell.LookupEntryForced( 75973 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_NULL;	
		sp->Effect[1] = SPELL_EFFECT_NULL;	
	}
	

	//Eye of the Broodmother
	sp = dbcSpell.LookupEntryForced( 65007 );
	//if( sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->proc_interval = 2000; //no spams please
	}
	//Pandora's Plea
	sp = dbcSpell.LookupEntryForced( 64742 );
	//if( sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->proc_interval = 2000; //no spams please
	}
	//Darkmoon Card: Death
	sp = dbcSpell.LookupEntryForced( 57352 );
	//if( sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK | PROC_ON_SPELL_HIT;
		sp->proc_interval = 45000;
	}
	//Pyrite Infuser
	sp = dbcSpell.LookupEntryForced( 65013 );
	//if( sp != NULL)
	{
		sp->procFlags = PROC_ON_CRIT_ATTACK | PROC_ON_RANGED_CRIT_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->proc_interval = 45000;
	}
	//Reflection of Torment
	sp = dbcSpell.LookupEntryForced( 33648 );
	//if( sp != NULL)
		sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_CRIT_ATTACK;
	//Skyshatter Harness - t6 set
	sp = dbcSpell.LookupEntryForced( 38432 );
	//if( sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL; //force him to use procspell effect
		sp->EffectTriggerSpell[0] = 38430; 
		sp->ProcOnNameHash[0] = SPELL_HASH_STORMSTRIKE;
	}
	//Warglaive of Azzinoth set bonus
	sp = dbcSpell.LookupEntryForced( 41434 );
	//if( sp != NULL)
	{
		sp->proc_interval = 2000; //no spams please
		sp->procChance = 5;
	}
	//Parasitic Serpent : using this for custom item :P
	sp = dbcSpell.LookupEntryForced( 23867 );
	//if( sp != NULL)
	{
		sp->proc_interval = 4000; //no spams please
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
	}
	sp = dbcSpell.LookupEntryForced( 23865 );
	//if( sp != NULL)
	{
		sp->proc_interval = 1000; //no spams please
		sp->maxstack = 10; 
	}
	//Darkmoon Card: Greatness
	sp = dbcSpell.LookupEntryForced( 57345 );
	//if( sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_HIT | PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
		sp->EffectTriggerSpell[0] = 60229;
	}
	//Darkmoon Card: Berserker!
	sp = dbcSpell.LookupEntryForced( 57351 );
	//if( sp != NULL)
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_MELEE_ATTACK_VICTIM ;
		sp->procFlags2 |= PROC2_TARGET_SELF;
	}
	//tentacle call
	sp = dbcSpell.LookupEntryForced( 26391 );
	//if( sp != NULL)
	{
		sp->spell_skilline[0] = 0;
		skilllinespell * spsk = dbcSkillLineSpell.LookupEntryForced( 18994 );
		spsk->skilline = 0;
	}
	//constrictor tentacle
	sp = dbcSpell.LookupEntryForced( 64125 );
	//if( sp != NULL)
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
	sp = dbcSpell.LookupEntryForced( 64126 );
	//if( sp != NULL)
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
	//Ashtongue Talisman of Zeal
	//Flash of Light and Holy Light have a 15% chance to grant your target $40471o healing over $40471d, and your Judgements have a 50% chance to inflict $40472o damage on their target over $40472d.
	sp = dbcSpell.LookupEntryForced( 40470 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA; //aura
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL; //force him to use procspell effect
		sp->EffectTriggerSpell[0] = 40471; 
		sp->procFlags = PROC_ON_CAST_SPELL; //add procflag here since this was not processed with the others !
		sp->procChance = 50; //well actually 15% for heal spell
		sp->proc_interval = 10000; //never ever spam anything :P
	}

	// Glyph of Drain Soul
	// Your Drain Soul ability occasionally creates an additional soul shard.
	sp = dbcSpell.LookupEntryForced( 58070 );
	//if( sp != NULL)
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;					//aura
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL; //force him to use procspell effect
		sp->EffectTriggerSpell[0] = 58068;							// The spell that creates the soul shard.
		sp->procFlags = PROC_ON_SPELL_HIT;							// this is a channeled spell, so I hope it's the right proc.
		sp->procChance = 20;										// 20% sounds fine, but it's not blizzlike.
		sp->proc_interval = 10000;									// never ever spam anything :P <- as tudi said
		sp->ProcOnNameHash[ 0 ] = SPELL_HASH_DRAIN_SOUL;			// Will proc only on drain soul spells.
	}

	//warsong gulch flags were not removed in some client rev
	sp = dbcSpell.LookupEntryForced( 23333 );
	//if( sp != NULL)
		sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_MOUNT;
	sp = dbcSpell.LookupEntryForced( 23335 );
	//if( sp != NULL)
		sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_MOUNT;
	//Honor Points +2000
	sp = dbcSpell.LookupEntryForced( 61700 );
	//if( sp != NULL)
		sp->EffectBasePoints[0] = 2000;
	//Honor Points +10000
	sp = dbcSpell.LookupEntryForced( 59869 );
	//if( sp != NULL)
		sp->EffectBasePoints[0] = 1000;

	//boss ai has missing range
	sp = dbcSpell.LookupEntryForced( 69146 );
	//if( sp != NULL)
		sp->rangeIndex = 137;	//8 yards
	sp = dbcSpell.LookupEntryForced( 69076 );
	//if( sp != NULL)
		sp->rangeIndex = 137;	//8 yards
	sp = dbcSpell.LookupEntryForced( 70842 );
	//if( sp != NULL)
		sp->DurationIndex = 21;	//infinit
	//racial (facial) - shadowmeld
	sp = dbcSpell.LookupEntryForced( 58984 );
	//if( sp != NULL)
		sp->InterruptFlags |= AURA_INTERRUPT_ON_ENTER_COMBAT | AURA_INTERRUPT_ON_START_ATTACK | AURA_INTERRUPT_ON_CAST_SPELL;
		

	//do not save these auras on logout 
	dbcSpell.LookupEntryForced( 73762 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;
	dbcSpell.LookupEntryForced( 73824 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;
	dbcSpell.LookupEntryForced( 73825 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;
	dbcSpell.LookupEntryForced( 73826 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;
	dbcSpell.LookupEntryForced( 73827 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;
	dbcSpell.LookupEntryForced( 73828 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;

	dbcSpell.LookupEntryForced( 73816 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;
	dbcSpell.LookupEntryForced( 73818 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;
	dbcSpell.LookupEntryForced( 73819 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;
	dbcSpell.LookupEntryForced( 73820 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;
	dbcSpell.LookupEntryForced( 73821 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;
	dbcSpell.LookupEntryForced( 73822 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;

	dbcSpell.LookupEntryForced( 69127 )->c_is_flags |= SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT;

	//do not cast these on login or learn 
	dbcSpell.LookupEntryForced( 44440 )->c_is_flags |= SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST;
	dbcSpell.LookupEntryForced( 44441 )->c_is_flags |= SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST;

	dbcSpell.LookupEntryForced( 49189 )->c_is_flags |= SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST;
	dbcSpell.LookupEntryForced( 50149 )->c_is_flags |= SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST;
	dbcSpell.LookupEntryForced( 50150 )->c_is_flags |= SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST;

	dbcSpell.LookupEntryForced( 61154 )->c_is_flags |= SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST;
	dbcSpell.LookupEntryForced( 61155 )->c_is_flags |= SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST;
	dbcSpell.LookupEntryForced( 61156 )->c_is_flags |= SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST;
	dbcSpell.LookupEntryForced( 61157 )->c_is_flags |= SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST;
	dbcSpell.LookupEntryForced( 61158 )->c_is_flags |= SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST;

	//after we set all group flags we can set only 1 bit to mark the check of all values
	for(uint32 x=0; x < dbcSpell.GetNumRows(); x++)
	{
		SpellEntry * sp = dbcSpell.LookupRow(x);

		//don't ask me about these 2 :P. Just random fix in src
/*		if( sp->spellIconID==457) 
			sp->EffectItemType[0]=1;
		if( sp->spellIconID==86) 
			sp->EffectItemType[0]=256;*/

		if( sp->SpellGroupType[0] || sp->SpellGroupType[1] || sp->SpellGroupType[2] )
			sp->c_is_flags |= SPELL_FLAG_IS_REQUIRING_SM_MOD;

	}

	Log.Notice("World", "Setting Spell TalentLines and Spec Specific Spells....");
	SetSpellTalentLines();

	//generate namehashes. This is used only rarely :P
/*	std::map<uint32,uint32> tempstore;
	std::map<std::string,uint32> collisionstore;
	tempstore.clear();
	//first check for define collisions
	for(uint32 x=0; x < dbcSpell.GetNumRows(); x++)
	{
		SpellEntry * sp = dbcSpell.LookupRow(x);

		//print stuff only once;
		if( tempstore[sp->NameHash] )
			continue;
		tempstore[ sp->NameHash ] = 1;

		//we generate a name that is uasable in C++ as define
		char tempname[500];
		strcpy(tempname,sp->Name);
		uint32 len=strlen(sp->Name);
		for(uint32 i=0;i<len;i++)
		{
            tempname[i] = toupper(tempname[i]);
			if( !((tempname[i] >= 'A' && tempname[i] <= 'Z') || (tempname[i] >= '0' && tempname[i] <= '9'))	)
				tempname[i] = '_';
		}

		if( collisionstore[ tempname ] == 1 )
			collisionstore[ tempname ] = 2;
		if( collisionstore[ tempname ] )
			continue;
		collisionstore[ tempname ] = 1;
	}
	tempstore.clear();
	for(uint32 x=0; x < dbcSpell.GetNumRows(); x++)
	{
		SpellEntry * sp = dbcSpell.LookupRow(x);

		//print stuff only once;
		if( tempstore[sp->NameHash] )
			continue;
		tempstore[ sp->NameHash ] = 1;

		//we generate a name that is uasable in C++ as define
		char tempname[500];
		strcpy(tempname,sp->Name);
		uint32 len=strlen(sp->Name);
		for(uint32 i=0;i<len;i++)
		{
            tempname[i] = toupper(tempname[i]);
			if( !((tempname[i] >= 'A' && tempname[i] <= 'Z') || (tempname[i] >= '0' && tempname[i] <= '9'))	)
				tempname[i] = '_';
		}
		if( collisionstore[ tempname ] == 2 )
		{
			char tempname2[500];
			sprintf(tempname2,"%s_%u",tempname,sp->Id);
			printf("#define SPELL_HASH_%-70s 0x%08X\n",tempname2,sp->NameHash);
		}
		else
			printf("#define SPELL_HASH_%-70s 0x%08X\n",tempname,sp->NameHash);
	}/**/
#include "../arcemu-customs/custom_procflag_sets.cpp"
}

void ApplyItemEnchantFixes()
{
	uint32 Next_safe_group_id = dbcItemLimitCategory.LookupRow( dbcItemLimitCategory.GetNumRows() - 1 )->CategoryId + 1;
	//make sure to have enchantment application limit for some gems
	for(uint32 x=0; x < dbcEnchant.GetNumRows(); x++)
	{
		EnchantEntry * ee = dbcEnchant.LookupRow(x);
		if( ee->GemEntry )
		{
			ItemPrototype *ip = ItemPrototypeStorage.LookupEntry( ee->GemEntry );
			if( !ip )
				continue;
			if( ( ip->Flags & ITEM_FLAG_UNIQUE_EQUIP )
				|| ( ip->Flags & ITEM_FLAG_EVENT_REQ )		//seems like for gems only this makes then unique. I wonder if it is true for all ?
				|| ip->Unique != 0
				)
			{
				ee->custom_enchant_group = Next_safe_group_id++;
				ee->custom_enchant_maxstack = 1;
			}
			if( ip->ItemLimitCategory )
			{
				ItemLimitCategory *il = dbcItemLimitCategory.LookupEntry( ip->ItemLimitCategory );
				if( il )
				{
					ee->custom_enchant_group = ip->ItemLimitCategory;
					ee->custom_enchant_maxstack = il->MaxStack;
				}
			}
			ee->custom_GearScore = ip->ItemLevel;
		}
		if( ee->custom_GearScore == 0 )
		{
			//try to get spell level
			SpellEntry *sp;
			for(uint32 kk=0;kk<3;kk++)
			{
				sp = dbcSpell.LookupEntryForced( ee->spell[kk] );
				if( sp )
				{
					ee->custom_GearScore = MAX( ee->custom_GearScore, MAX( 271, sp->spellLevel * 3 ) );
//					ee->custom_GearScore = MAX( (int32)ee->custom_GearScore, sp->EffectBasePoints[0] );
				}
			}
		}
		if( ee->custom_GearScore == 0 )
			ee->custom_GearScore = 10;
	}
	//unique gems should also be applied only once
}

void ApplyAreaFixes()
{
	for(uint32 x=0; x < dbcArea.GetNumRows(); x++)
	{
		AreaTable *ae = dbcArea.LookupRow(x);

		//make sure to set arena flags 
		if( strstr(ae->name,"Arena"))
			ae->AreaFlags |= AREA_PVP_ARENA;
		else
			ae->AreaFlags &= ~AREA_PVP_ARENA;	//make sure we do not trigger FFA flags anywhere else

		//no pvp in ebony hold please
		if( ae->mapId == 609 || ae->AreaId == 4544)
			ae->category = AREAC_SANCTUARY;
		// no pvp in event area please
		else if (ae->mapId == 169)
			ae->category = AREAC_SANCTUARY;
		
	}
	//gurubashi arena is an open battle ring
	AreaTable *ae;
	ae = dbcArea.LookupEntry( 2177 );	//the ring
	if( ae )
		ae->AreaFlags |= AREA_PVP_ARENA;
	ae = dbcArea.LookupEntry( 1741 );	//preparation ring
	if( ae )
		ae->AreaFlags &= ~AREA_PVP_ARENA;
	//circle of blood arena has missing "arena" in name
	ae = dbcArea.LookupEntry( 3775 );	//the ring
	if( ae )
		ae->AreaFlags |= AREA_PVP_ARENA;
	//maul arena has missing "arena" in name
	ae = dbcArea.LookupEntry( 3217 );	//the ring
	if( ae )
		ae->AreaFlags |= AREA_PVP_ARENA;

	for(uint32 x=0; x < dbcWorldMapZoneStore.GetNumRows(); x++)
	{
		WorldMapAreaEntry *ae = dbcWorldMapZoneStore.LookupRow(x);
		//dalaran has missing values
		if( ae->zone_id == 4395 )
		{
			ae->min_x = 5567;
			ae->max_x = 6040;
			ae->min_y = 410;
			ae->max_y = 806;
		}
	}
}
