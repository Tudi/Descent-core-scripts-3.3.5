#include "StdAfx.h"

#define REGISTER_HANDLER( spell ) sp = dbcSpell.LookupEntryForced( spell ); \
	ASSERT( sp->ChargeHandler == 0 ); \
	sp->ChargeHandler = &CH_##spell;
#define REGISTER_SAMEHANDLER(spell,copy_from) sp = dbcSpell.LookupEntryForced( spell ); \
	ASSERT( sp->ChargeHandler == 0 ); \
	sp->ChargeHandler = &CH_##copy_from;

void CH_57529( ProcHandlerContextShare *context )
{
	//need damaging spell
	if( !context->in_CastingSpell )
		return;
	if( !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_47383( ProcHandlerContextShare *context )
{
//	if( (iter2->second.ProcFlag & PROC_ON_CAST_SPELL) == 0 )
//		continue;
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_INCINERATE && context->in_CastingSpell->NameHash != SPELL_HASH_SOUL_FIRE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_53220( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_AIMED_SHOT && context->in_CastingSpell->NameHash != SPELL_HASH_ARCANE_SHOT && context->in_CastingSpell->NameHash != SPELL_HASH_CHIMERA_SHOT )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_69369( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	SpellCastTime *sd = dbcSpellCastTime.LookupEntry( context->in_CastingSpell->CastingTimeIndex );
	if(sd && sd->CastTime==0)
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_60503( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_OVERPOWER )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_64343( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_FIRE_BLAST )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_70757( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_HOLY_LIGHT )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_46833( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_STARFIRE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_53817( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_LIGHTNING_BOLT 
		&& context->in_CastingSpell->NameHash != SPELL_HASH_CHAIN_LIGHTNING 
		&& context->in_CastingSpell->NameHash != SPELL_HASH_LESSER_HEALING_WAVE
		&& context->in_CastingSpell->NameHash != SPELL_HASH_HEALING_WAVE
		&& context->in_CastingSpell->NameHash != SPELL_HASH_CHAIN_HEAL
		&& context->in_CastingSpell->NameHash != SPELL_HASH_HEX 
		)
		return;
	//try to remove all 5 stacks ?
	if(context->in_Caller->RemoveAura( 53817 ))
		if(context->in_Caller->RemoveAura( 53817 ))
			if(context->in_Caller->RemoveAura( 53817 ))
				if(context->in_Caller->RemoveAura( 53817 ))
					context->in_Caller->RemoveAura( 53817 );
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_61595( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_SHADOW_BOLT && context->in_CastingSpell->NameHash != SPELL_HASH_INCINERATE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_57761( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_FIREBALL )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_44544( ProcHandlerContextShare *context )
{
//							if( iter2->second.count == 1 )
//								RemoveFlag(UNIT_FIELD_AURASTATE, AURASTATE_FLAG_FROZEN );
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_63731( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_GREATER_HEAL && context->in_CastingSpell->NameHash != SPELL_HASH_PRAYER_OF_HEALING )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_46916( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_SLAM )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_56453( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_EXPLOSIVE_SHOT && context->in_CastingSpell->NameHash != SPELL_HASH_ARCANE_SHOT )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_58363( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_HEROIC_STRIKE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_16870( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_65156( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_SLAM && context->in_CastingSpell->NameHash != SPELL_HASH_MORTAL_STRIKE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_59578( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_FLASH_OF_LIGHT && context->in_CastingSpell->NameHash != SPELL_HASH_EXORCISM )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_12536( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( ( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) == 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_53672( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_FLASH_OF_LIGHT && context->in_CastingSpell->NameHash != SPELL_HASH_HOLY_LIGHT )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_33151( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_SMITE && context->in_CastingSpell->NameHash != SPELL_HASH_FLASH_HEAL )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_44401( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_ARCANE_MISSILES )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_48108( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_PYROBLAST )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_54741( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_FLAMESTRIKE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_54277( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
//	if( context->in_CastingSpell->NameHash != SPELL_HASH_CONFLAGRATE )
//		return;
	if( context->in_CastingSpell->spell_skilline[0] != SKILL_DESTRUCTION )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_51124( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_ICY_TOUCH && context->in_CastingSpell->NameHash != SPELL_HASH_HOWLING_BLAST && context->in_CastingSpell->NameHash != SPELL_HASH_FROST_STRIKE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_49796( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_ICY_TOUCH && context->in_CastingSpell->NameHash != SPELL_HASH_HOWLING_BLAST && context->in_CastingSpell->NameHash != SPELL_HASH_FROST_STRIKE && context->in_CastingSpell->NameHash != SPELL_HASH_OBLITERATE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_59052( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_HOWLING_BLAST )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_43339( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_EARTH_SHOCK &&
			context->in_CastingSpell->NameHash != SPELL_HASH_FLAME_SHOCK &&
			context->in_CastingSpell->NameHash != SPELL_HASH_FROST_SHOCK )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_12043( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	//Presence of Mind and Nature's Swiftness should only get removed
	//when a non-instant and bellow 10 sec. Also must be nature :>
//	if(!sd->CastTime||sd->CastTime>10000) continue;
	SpellCastTime *sd = dbcSpellCastTime.LookupEntry(context->in_CastingSpell->CastingTimeIndex);
//	if(!sd || sd->CastTime==0 || sd->CastTime>10000)	//this version led to an exploit some say
	if(sd && sd->CastTime==0)
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_23575( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_HEALING_WAVE &&
			context->in_CastingSpell->NameHash != SPELL_HASH_RIPTIDE &&
			context->in_CastingSpell->NameHash != SPELL_HASH_CHAIN_HEAL &&
			context->in_CastingSpell->NameHash != SPELL_HASH_LESSER_HEALING_WAVE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_17116( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
//	if( CastingSpell->School!=SCHOOL_NATURE||(!sd->CastTime||sd->CastTime>10000)) continue;
	SpellCastTime *sd = dbcSpellCastTime.LookupEntry(context->in_CastingSpell->CastingTimeIndex);
//	if( (!sd || sd->CastTime==0 || sd->CastTime>10000 || CastingSpell->School!=SCHOOL_NATURE )
	if( ((sd && sd->CastTime==0) || context->in_CastingSpell->School!=SCHOOL_NATURE )
		&& (context->in_Caller->getClass() == SHAMAN || context->in_Caller->getClass() == DRUID )	//spellsteal exploit to have infinit casts
		) 
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_16166( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if(!(context->in_CastingSpell->School==SCHOOL_FIRE||context->in_CastingSpell->School==SCHOOL_FROST||context->in_CastingSpell->School==SCHOOL_NATURE))
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_14177( ProcHandlerContextShare *context )
{
	if(context->in_Victim==context->in_Caller || isFriendly(context->in_Caller, context->in_Victim))
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_20178( ProcHandlerContextShare *context )
{
	//do not remove ourself when we melee hit due to our own proc
	if( context->in_CastingSpell && context->in_CastingSpell->NameHash == SPELL_HASH_RECKONING )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void CH_56817( ProcHandlerContextShare *context )
{
	//do not remove ourself when we melee hit due to our own proc
	if( context->in_CastingSpell && context->in_CastingSpell->NameHash != SPELL_HASH_RUNE_STRIKE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void RegisterChargeHandlers()
{
	SpellEntry *sp;
	//Rune strike enable aura - we custom made this spell !!
	REGISTER_HANDLER( 56817 );
	//Reckoning - remove only when we actually use the spell
	REGISTER_HANDLER( 20178 );
	//cold blood will get removed on offensive spell
	REGISTER_HANDLER( 14177 );
	//Elemental Mastery
	REGISTER_HANDLER( 16166 );
	//Shaman - Nature's Swiftness
	REGISTER_HANDLER( 17116 );
	REGISTER_SAMEHANDLER( 16188, 17116 );
	//Shaman - Improved Water Shield
	REGISTER_HANDLER( 23575 );
	//Presence of Mind
	REGISTER_HANDLER( 12043 );
	//Shaman - Shamanist Focus
	REGISTER_HANDLER( 43339 );
	//DK - Rime
	REGISTER_HANDLER( 59052 );
	//DK - Deathchill
	REGISTER_HANDLER( 49796 );
	//DK - Killing Machine
	REGISTER_HANDLER( 51124 );
	//warlock - Backdraft - only remove on destruction spells
	REGISTER_HANDLER( 54277 );
	//mage - Firestarter - only remove on flamestrike
	REGISTER_HANDLER( 54741 );
	//mage - Hot Streak
	REGISTER_HANDLER( 48108 );
	//mage - Missile Barrage
	REGISTER_HANDLER( 44401 );
	//priest - surge of light
	REGISTER_HANDLER( 33151 );
	//paladin - Infusion of Light
	REGISTER_HANDLER( 53672 );
	REGISTER_SAMEHANDLER( 54149, 53672 );
	//mage Arcane Concentration - clearcasting
	REGISTER_HANDLER( 12536 );
	//paladin - Art of War
	REGISTER_HANDLER( 59578 );
	REGISTER_SAMEHANDLER( 53489, 59578 );
	//warrior - juggernaut
	REGISTER_HANDLER( 65156 );
	//Druid: Omen of Clarity -> clearcasting
	REGISTER_HANDLER( 16870 );
	//Glyph of Revenge
	REGISTER_HANDLER( 58363 );
	//hunter - lock and load
	REGISTER_HANDLER( 56453 );
	//warrior - Bloodsurge
	REGISTER_HANDLER( 46916 );
	//priest - Serendipity
	REGISTER_HANDLER( 63731 );
	REGISTER_SAMEHANDLER( 63734, 63731 );
	REGISTER_SAMEHANDLER( 63735, 63731 );
	//mage - fringers of frost -> aurastates should have counters
//	REGISTER_HANDLER( 44544 );
//	REGISTER_SAMEHANDLER( 74396, 44544 );
	//mage brain freez
	REGISTER_HANDLER( 57761 );
	//Corruption Triggers Crit
	REGISTER_HANDLER( 61595 );
	//shaman - Maelstrom Weapon
	REGISTER_HANDLER( 53817 );
	//Item - Moonkin Starfire Bonus
	REGISTER_HANDLER( 46833 );
	//Item - Paladin T10 Holy 4P Bonus
	REGISTER_HANDLER( 70757 );
	//Impact
	REGISTER_HANDLER( 64343 );
	//Taste for Blood
	REGISTER_HANDLER( 60503 );
	//Predator's Swiftness
	REGISTER_HANDLER( 69369 );
	//Improved Steady Shot
	REGISTER_HANDLER( 53220 );
	//warlock molten core
	REGISTER_HANDLER( 47383 );
	REGISTER_SAMEHANDLER( 71162, 47383 );
	REGISTER_SAMEHANDLER( 71165, 47383 );
	//mage arcane potency
	REGISTER_HANDLER( 57529 );
	REGISTER_SAMEHANDLER( 57531, 57529 );
}
