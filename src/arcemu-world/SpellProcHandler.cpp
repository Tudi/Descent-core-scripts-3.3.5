#include "StdAfx.h"

#define REGISTER_HANDLER( spell ) sp = dbcSpell.LookupEntryForced( spell ); \
	ASSERT( sp->ProcHandler == 0 ); \
	sp->ProcHandler = &PH_##spell;
#define REGISTER_SAMEHANDLER(spell,copy_from) sp = dbcSpell.LookupEntryForced( spell ); \
	ASSERT( sp->ProcHandler == 0 ); \
	sp->ProcHandler = &PH_##copy_from;

void PH_71948( ProcHandlerContextShare *context )
{
	int32 dmg_to_deal = context->in_dmg - context->in_abs;
	dmg_to_deal = dmg_to_deal * context->in_event->created_with_value / 100;
	if( dmg_to_deal <= 0 )
		return;
	Unit *target = context->in_Caller->GetMapMgr()->GetUnit( context->in_event->caster );
	if( target == NULL )
		return;
	context->in_Caller->DealDamage( target, dmg_to_deal, 0, 0, context->in_event->origId );
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_44450( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;

	int32 addcost = context->in_CastingSpell->manaCost * ( context->in_OwnerSpell->EffectBasePoints[0] + 1 ) / 100;
	if( (context->in_Caller->GetUInt32Value(UNIT_FIELD_POWER1) - addcost) < 0 )
		context->in_Caller->SetUInt32Value(UNIT_FIELD_POWER1, 0);
	else
		context->in_Caller->ModUnsigned32Value(UNIT_FIELD_POWER1, -addcost);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_69369( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL || context->in_Caller->IsPlayer() == false )
		return;
	//requires finishing move
	if( ( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE	) == 0 )
		return;
	uint32 chance = SafePlayerCast( context->in_Caller )->m_comboPoints * 20;
	if( RandomUInt() % 100 > chance )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_48391( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() && SafePlayerCast( context->in_Caller )->GetShapeShift() != FORM_MOONKIN )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_48540( ProcHandlerContextShare *context )
{
	//set return early just in case we forget to set it later :P
	//the casted spell depends on the power type of the target
	uint32 spellId;
	switch( context->in_Victim->GetPowerType() )
	{
		case POWER_TYPE_MANA : spellId = 48542;			break;
		case POWER_TYPE_ENERGY : spellId = 48540;		break;
		case POWER_TYPE_RAGE : spellId = 48541;			break;
		case POWER_TYPE_RUNIC_POWER : spellId = 48543;	break;
		default: 
			return;
	}
	SpellCastTargets targets( context->in_Victim->GetGUID() );	//druid casted on us and we got hit by it
	SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init( context->in_Caller, spellInfo ,true, NULL );
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId= context->in_OwnerSpell->Id;
	spell->prepare(&targets);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_16959( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	Player * p = SafePlayerCast( context->in_Caller );
	if( p->GetShapeShift() != FORM_BEAR && p->GetShapeShift() != FORM_DIREBEAR )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_34299( ProcHandlerContextShare *context )
{
	if( context->in_Caller->HasAura( 34300 ) )
	{
		//rank2 : should heal 4% of max health and restore 8% maxmana
		context->out_dmg_overwrite[0] = context->in_Caller->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * 4 / 100;
		context->in_Caller->Energize( context->in_Caller, 34299, context->in_Caller->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) * 8 / 100, POWER_TYPE_MANA);
	}
	else if( context->in_Caller->HasAura( 34297 ) )
	{
		//rank1 : should heal 2% of max health and restore 4% maxmana
		context->out_dmg_overwrite[0] = context->in_Caller->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * 2 / 100;
		context->in_Caller->Energize( context->in_Caller, 34299, context->in_Caller->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) * 4 / 100, POWER_TYPE_MANA);
	}
	else
		return;

	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_58179( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_SHRED &&
		context->in_CastingSpell->NameHash != SPELL_HASH_MAUL &&
		context->in_CastingSpell->NameHash != SPELL_HASH_MANGLE__CAT_ &&
		context->in_CastingSpell->NameHash != SPELL_HASH_MANGLE__BEAR_ ) 
		return;

	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_16953( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_Caller->IsPlayer() == false )
		return;
	Player * p = SafePlayerCast( context->in_Caller );
	if( p->GetShapeShift() != FORM_CAT || (
		context->in_CastingSpell->NameHash != SPELL_HASH_CLAW &&
		context->in_CastingSpell->NameHash != SPELL_HASH_RAKE &&
		context->in_CastingSpell->NameHash != SPELL_HASH_RAVAGE &&
		context->in_CastingSpell->NameHash != SPELL_HASH_SHRED ) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
} 

void PH_14189( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->Effect[0] != SPELL_EFFECT_ADD_COMBO_POINTS &&
		context->in_CastingSpell->Effect[1] != SPELL_EFFECT_ADD_COMBO_POINTS &&
		context->in_CastingSpell->Effect[2] != SPELL_EFFECT_ADD_COMBO_POINTS )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_31616( ProcHandlerContextShare *context )
{
	//yep, another special case: Nature's grace
	if( context->in_Caller->GetHealthPct() > 30 )
		return;
	context->out_dmg_overwrite[0] = context->in_Caller->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * ( context->in_OwnerSpell->EffectBasePoints[0] + 1) / 100;
	//no idea about this value :S
	if( context->in_Victim->GetAIInterface() )
		context->in_Victim->GetAIInterface()->modThreatByPtr( context->in_Caller, -context->out_dmg_overwrite[0]*2 );

	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_37309( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	if( SafePlayerCast( context->in_Caller )->GetShapeShift() != FORM_BEAR ||
		SafePlayerCast( context->in_Caller )->GetShapeShift() != FORM_DIREBEAR )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_37310( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	if( SafePlayerCast( context->in_Caller )->GetShapeShift() != FORM_BEAR ||
		SafePlayerCast( context->in_Caller )->GetShapeShift() != FORM_DIREBEAR )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_5530( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	//warrior/rogue mace specialization can trigger only when using maces
	Item* it;
	if( SafePlayerCast( context->in_Caller )->GetItemInterface() )
	{
		it = SafePlayerCast( context->in_Caller )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
		if( it != NULL && it->GetProto() )
		{
			uint32 reqskill = GetSkillByProto( it->GetProto()->Class, it->GetProto()->SubClass );
			if( reqskill != SKILL_MACES && reqskill != SKILL_2H_MACES )
				return;
		}
		else
			return; //no weapon no joy
	}
	else
		return; //no weapon no joy
	//let's recalc chance to cast since we have a full 100 all time on this one
	//how lame to get talentpointlevel for this spell :(
	//float chance=it->GetProto()->Delay*100*talentlevel/60000;
	uint32 talentlevel = 0;
	switch( context->in_OwnerSpell->Id )
	{
		//mace specialization
		case 12284:	{talentlevel = 1;}break;
		case 12701:	{talentlevel = 2;}break;
		case 12702:	{talentlevel = 3;}break;
		case 12703:	{talentlevel = 4;}break;
		case 12704:	{talentlevel = 5;}break;

		//Unbridled Wrath
		case 12999:	{talentlevel = 1;}break;
		case 13000:	{talentlevel = 2;}break;
		case 13001:	{talentlevel = 3;}break;
		case 13002:	{talentlevel = 4;}break;
	}

	float chance = float( it->GetProto()->Delay ) * float( talentlevel ) / 600.0f;
	if( !Rand( chance ) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_47294( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	context->out_dmg_absorb = context->in_Caller->GetUInt32Value( PLAYER_SHIELD_BLOCK ) * (context->in_OwnerSpell->EffectBasePoints[0] + 1) / 100;
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_58872( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;

	int32 deal_dmg = context->in_Caller->GetUInt32Value( PLAYER_SHIELD_BLOCK ) * (context->in_OwnerSpell->EffectBasePoints[0] + 1) / 100;
	if( deal_dmg )
//		DealDamage( victim, deal_dmg, 0, 0, ospinfo->Id );
		context->in_Caller->SpellNonMeleeDamageLog( context->in_Victim, 21075, deal_dmg, true);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_57514( ProcHandlerContextShare *context )
{
	if( context->in_Caller->HasAurasWithNameHash( SPELL_HASH_DEFENSIVE_STANCE ) == false )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_16459( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	if( SafePlayerCast( context->in_Caller )->GetItemInterface())
	{
		Item* it = SafePlayerCast( context->in_Caller )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
		if( it != NULL && it->GetProto() )
		{
			uint32 reqskill=GetSkillByProto( it->GetProto()->Class, it->GetProto()->SubClass );
			if( reqskill != SKILL_SWORDS && reqskill != SKILL_2H_SWORDS )
				return;
		}
		else
			return; //no weapon no joy
	}
	else
		return; //no weapon no joy
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_12721( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	Item* it;
	if( SafePlayerCast( context->in_Caller )->GetItemInterface())
	{
		it = SafePlayerCast( context->in_Caller )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
		if( it != NULL && it->GetProto() )
		{
			//class 2 means weapons ;)
			if( it->GetProto()->Class != 2 )
				return;
		}
		else return; //no weapon no joy
	}
	else return; //no weapon no joy
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_52437( ProcHandlerContextShare *context )
{
	//enable execute anytime
	context->in_Victim->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_HEALTH_BELOW_20_PCT);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_12964( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	//let's recalc chance to cast since we have a full 100 all time on this one
	Item* it;
	if( SafePlayerCast( context->in_Caller )->GetItemInterface() )
	{
		it = SafePlayerCast( context->in_Caller )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
		if( !( it != NULL && it->GetProto() ) )
			return; //no weapon no joy
	}
	else
		return; //no weapon no joy
	//float chance=float(it->GetProto()->Delay)*float(talentlevel)/600.0f;
	uint32 talentlevel = 0;
	switch( context->in_OwnerSpell->Id )
	{
		//mace specialization
		case 12284:	{talentlevel = 1;}break;
		case 12701:	{talentlevel = 2;}break;
		case 12702:	{talentlevel = 3;}break;
		case 12703:	{talentlevel = 4;}break;
		case 12704:	{talentlevel = 5;}break;

		//Unbridled Wrath
		case 12999:	{talentlevel = 1;}break;
		case 13000:	{talentlevel = 2;}break;
		case 13001:	{talentlevel = 3;}break;
		case 13002:	{talentlevel = 4;}break;
	}

	float chance = float( it->GetProto()->Delay ) * float(talentlevel ) / 300.0f; //zack this had a very low proc rate. Kinda liek a waisted talent
	uint32 myroll = RandomUInt( 100 );
	if( myroll > chance )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_12654( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->School != SCHOOL_FIRE )
		return;
	SpellEntry* spellInfo = dbcSpell.LookupEntryForced( context->in_event->spellId ); //we already modified this spell on server loading so it must exist
//	int32 fire_spell_dmg = context->in_CastingSpell->quick_tickcount * ( context->in_dmg - context->in_abs );
	int32 fire_spell_dmg =	( context->in_dmg - context->in_abs );	//if we multiply by dots then ignite will do 9x fireball dmg ...100k ?
	context->out_dmg_overwrite[0] = ( context->in_OwnerSpell->EffectBasePoints[0] + 1 ) * fire_spell_dmg / 100;
	context->out_dmg_overwrite[0] = context->out_dmg_overwrite[0] / spellInfo->quick_tickcount;	//over 2 seconds with 2 ticks ?
	if( context->out_dmg_overwrite[0] < 0 || context->out_dmg_overwrite[0] > 100000 ) 
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_64343( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( ( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) == 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_44401( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_ARCANE_BLAST &&
		context->in_CastingSpell->NameHash != SPELL_HASH_ARCANE_BARRAGE && 
		context->in_CastingSpell->NameHash != SPELL_HASH_FIREBALL && 
		context->in_CastingSpell->NameHash != SPELL_HASH_FROSTBOLT && 
		context->in_CastingSpell->NameHash != SPELL_HASH_FROSTFIRE_BOLT ) 
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_48108( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	//only trigger effect for specified spells
	//sadly this will also be called on DOT ticks. Would need to detect only direct casts
	if( context->in_CastingSpell->NameHash != SPELL_HASH_FIREBALL &&
		context->in_CastingSpell->NameHash != SPELL_HASH_FIRE_BLAST && 
		context->in_CastingSpell->NameHash != SPELL_HASH_SCORCH && 
		context->in_CastingSpell->NameHash != SPELL_HASH_FROSTFIRE_BOLT && 
		context->in_CastingSpell->NameHash != SPELL_HASH_LIVING_BOMB ) 
	{
		context->in_event->created_with_value = 0;
		return;
	}
	//this is a spellcast but it is not a critical hit. We will wait for the event when spell hits the target and if that is not crit then we may reset counter to 0
	if( ( context->in_events_filter_flags & PROC_ON_SPELL_HIT ) == 0 )
		return;
	//we hit the target with correct spell but it is not critical then we may reset the counter
	if( ( context->in_events_filter_flags & PROC_ON_SPELL_CRIT_HIT ) == 0 )
	{
		context->in_event->created_with_value = 0;
		return;
	}
	context->in_event->created_with_value++;
	//need 2 consecutive casts like above list
	if( context->in_event->created_with_value < 2 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_37116( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	Player* mPlayer = SafePlayerCast(context->in_Caller);
	if (!mPlayer->IsInFeralForm() || 
		(mPlayer->GetShapeShift() != FORM_CAT &&
		mPlayer->GetShapeShift() != FORM_BEAR &&
		mPlayer->GetShapeShift() != FORM_DIREBEAR))
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_52916( ProcHandlerContextShare *context )
{
	//we award to the caster of this aura 1 combo point
	Player *caster = context->in_Caller->GetMapMgr()->GetPlayer( context->in_event->caster );
	if( caster )
	{
		if( caster->m_comboTarget )
			caster->AddComboPoints( caster->m_comboTarget, 1 );
		else 
			caster->AddComboPoints( caster->GetSelection(), 1 );
	}
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_31228( ProcHandlerContextShare *context )
{
	//we already got triggered and we are soacking up dmg now
	if( context->in_event->created_with_value > (int32)getMSTime() )
	{
		//now add an aura that will absorb 90% of damage for 3 seconds
		if( context->in_dmg - context->in_abs > 0 )
			context->out_dmg_absorb += (context->in_dmg - context->in_abs) * 90/100;
		return;
	}
	if( context->in_event->created_with_value + 57000 < (int32)getMSTime() ) //very evil, need to store secondary counter somewhere
	{
		//is this a killer blow ?
		int32 new_health = (int32)context->in_Caller->GetHealth() - (context->in_dmg - context->in_abs);
		if( new_health <= 0 )
		{
			//check proc chance 
			uint32 procchance = context->in_OwnerSpell->EffectBasePoints[0] + 1;
			if( Rand( procchance ) )
			{
				uint32 new_health = context->in_Caller->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * 10 / 100;
				context->in_Caller->SetHealth( new_health );
				context->in_event->created_with_value = getMSTime() + 4000; // start soacking dmg
				context->out_dmg_absorb += (context->in_dmg - context->in_abs) + 5;
			}
		}
	}
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_31665( ProcHandlerContextShare *context )
{
	//if this is proc on steathing then we let it just pass
	//if it is casted when removing stealth then we force duration 6 seconds
	if( context->in_events_filter_flags & PROC_ON_AURA_REMOVE )
	{
		context->in_Caller->RemoveAuraByNameHash( SPELL_HASH_MASTER_OF_SUBTLETY );	//does not remove the original talent aura
		//now proc a new spell with forced duration
		SpellCastTargets targets( context->in_Caller->GetGUID() );
		SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
		Spell *spell = SpellPool.PooledNew();
		spell->Init(context->in_Caller, spellInfo ,true, NULL);
		spell->forced_duration = 6000;
		spell->forced_basepoints[0] = context->in_OwnerSpell->EffectBasePoints[0] + 1;
		spell->ProcedOnSpell = context->in_CastingSpell;
		spell->pSpellId=context->in_OwnerSpell->Id;
		spell->prepare(&targets);
		return;
	}
	context->out_dmg_overwrite[0] = context->in_OwnerSpell->EffectBasePoints[0] + 1;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_31125( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	//only trigger effect for specified spells
	if( context->in_CastingSpell->NameHash != SPELL_HASH_BACKSTAB && //backstab
		context->in_CastingSpell->NameHash != SPELL_HASH_SINISTER_STRIKE && //sinister strike
		context->in_CastingSpell->NameHash != SPELL_HASH_SHIV && //shiv
		context->in_CastingSpell->NameHash != SPELL_HASH_GOUGE ) //gouge
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_1120( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	SafePlayerCast( context->in_Caller )->GetItemInterface()->AddItemById( 6265, 1, 0 );
}

void PH_27285( ProcHandlerContextShare *context )
{
	bool can_proc_now = false;
	//if we proced on spell tick
	if( context->in_events_filter_flags & PROC_ON_SPELL_HIT_VICTIM )
	{
		if( !context->in_CastingSpell )
			return;
		//only trigger effect for specified spells
		if( context->in_CastingSpell->NameHash != SPELL_HASH_SEED_OF_CORRUPTION )						
			return;
		//this spell builds up in time
		if( context->in_dmg - context->in_abs > 0 )
			context->in_event->procCharges += context->in_dmg - context->in_abs;
		if( (int32)context->in_event->procCharges >= context->in_OwnerSpell->EffectBasePoints[ 1 ] && //if charge built up
			context->in_dmg < (int32)context->in_Caller->GetUInt32Value( UNIT_FIELD_HEALTH ) ) //if this is not a killer blow
			can_proc_now = true;
	}
	else 
		can_proc_now = true; //target died
	if( can_proc_now == false )
		return;
	Unit *new_caster = context->in_Victim;
	if( new_caster && new_caster->isAlive() )
	{
		SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId ); //we already modified this spell on server loading so it must exist
		Spell *spell = SpellPool.PooledNew();
		spell->Init( new_caster, spellInfo ,true, NULL );
		SpellCastTargets targets2;
		targets2.m_destX = context->in_Caller->GetPositionX();
		targets2.m_destY = context->in_Caller->GetPositionY();
		targets2.m_destZ = context->in_Caller->GetPositionZ();
		spell->prepare(&targets2);
	}
	context->in_event->deleted = true;
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_18371( ProcHandlerContextShare *context )
{
	context->out_dmg_overwrite[0] = ( context->in_OwnerSpell->EffectBasePoints[2] + 1 ) * context->in_Caller->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_31117( ProcHandlerContextShare *context )
{
	context->out_dmg_overwrite[0] = ( context->in_OwnerSpell->EffectBasePoints[0] + 1 ) * 9;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_63106( ProcHandlerContextShare *context )
{
	context->out_dmg_overwrite[0] = ( context->in_OwnerSpell->EffectBasePoints[0] + 1 ) * (context->in_dmg - context->in_abs) / 100;
	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_54181( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( ( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) == 0 )
		return;
	context->out_dmg_overwrite[0] = ( context->in_OwnerSpell->EffectBasePoints[0] + 1 ) * (context->in_dmg - context->in_abs) / 100;
	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_47422( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_DRAIN_LIFE && 
		context->in_CastingSpell->NameHash != SPELL_HASH_DRAIN_SOUL &&
		context->in_CastingSpell->NameHash != SPELL_HASH_SHADOW_BOLT &&
		context->in_CastingSpell->NameHash != SPELL_HASH_HAUNT )
		return;

	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

//!! i'm not sure this code is even used anymore
void PH_25228( ProcHandlerContextShare *context )
{
	//we need a pet for this, else we do not trigger it at all
	if( context->in_Caller->IsPlayer() == false )
		return;
	Unit* new_caster;
	if( SafePlayerCast( context->in_Caller )->GetSummon() )
		new_caster = SafePlayerCast( context->in_Caller )->GetSummon();
	else if( context->in_Caller->GetUInt64Value( UNIT_FIELD_CHARM ) )
		new_caster = context->in_Caller->GetMapMgr()->GetUnit( context->in_Caller->GetUInt64Value( UNIT_FIELD_CHARM ) );
	else
		new_caster = NULL;
	if( new_caster != NULL && new_caster->isAlive() )
	{
		SpellEntry* spellInfo = dbcSpell.LookupEntry( 25228 ); //we already modified this spell on server loading so it must exist
		Spell* spell = SpellPool.PooledNew();
		spell->Init( new_caster, spellInfo, true, NULL );
		spell->forced_basepoints[0] = context->in_dmg;
		SpellCastTargets targets2;
		targets2.m_unitTarget = context->in_Caller->GetGUID();
		spell->prepare( &targets2 );
	}
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_32386( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
/*	if( context->in_CastingSpell->NameHash != SPELL_HASH_CORRUPTION && // Corruption
		context->in_CastingSpell->NameHash != SPELL_HASH_CURSE_OF_AGONY && //CoA
		context->in_CastingSpell->NameHash != SPELL_HASH_SIPHON_LIFE && //Siphon Life
		context->in_CastingSpell->NameHash != SPELL_HASH_SEED_OF_CORRUPTION ) //SoC
		return; */

	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_18118( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL || context->in_CastingSpell->spell_skilline[0] != SKILL_DESTRUCTION )
		return;

	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_54370( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	//only trigger effect for specified spells
	if(!(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
		return;
	//depending on school we change the ID of the cast spell
	uint32 school_spells[SCHOOL_COUNT]={0,54370,54371,54375,54372,54374,54373};
	uint32 spellId = school_spells[ context->in_CastingSpell->School ];

	SpellEntry* spellInfo = dbcSpell.LookupEntry( spellId ); 
	Spell* spell = SpellPool.PooledNew();
	spell->Init( context->in_Caller, spellInfo, true, NULL );
	SpellCastTargets targets2( context->in_Caller->GetGUID() );
	spell->prepare( &targets2 );

	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_30294( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_SHADOW_BOLT && 
		context->in_CastingSpell->NameHash != SPELL_HASH_SOUL_FIRE &&
		context->in_CastingSpell->NameHash != SPELL_HASH_INCINERATE && 
		context->in_CastingSpell->NameHash != SPELL_HASH_CONFLAGRATE && 
		context->in_CastingSpell->NameHash != SPELL_HASH_SHADOWBURN && 
		context->in_CastingSpell->NameHash != SPELL_HASH_SEARING_PAIN )
		return;

	context->out_dmg_overwrite[0] = ( context->in_dmg - context->in_abs ) * (context->in_OwnerSpell->EffectBasePoints[0]+1)/100;
	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}


void PH_54227( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_RAPID_FIRE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_56654( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_RAPID_KILLING )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_6150( ProcHandlerContextShare *context )
{
	//nasty :(. We need this active aspect
	if( context->in_Caller->HasAurasWithNameHash( SPELL_HASH_ASPECT_OF_THE_HAWK ) == 0 
		&& context->in_Caller->HasAurasWithNameHash( SPELL_HASH_ASPECT_OF_THE_DRAGONHAWK ) == 0 )
		return;
	context->out_dmg_overwrite[0] = context->in_OwnerSpell->EffectBasePoints[1]+1;

	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_53295( ProcHandlerContextShare *context )
{
	//dmg is the dispelled spell id
	SpellEntry *spd = dbcSpell.LookupEntryForced( context->in_dmg );
	if( spd == NULL || spd->NameHash != SPELL_HASH_WYVERN_STING )
		return;
	//cast on target this spell
	SpellCastTargets targets2( context->in_Victim->GetGUID() );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spd ,true, NULL);
//	spell->forced_duration = 6000;	//crap, this is complicated :P
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId=context->in_OwnerSpell->Id;
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_57669( ProcHandlerContextShare *context )
{
	if( context->in_Caller->getClass() == WARLOCK )
	{
		context->out_dmg_overwrite[0] = context->in_Caller->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) *(context->in_OwnerSpell->EffectBasePoints[0]+1)/100;
		//energize self
		context->in_Caller->Energize( context->in_Caller, 57669, context->out_dmg_overwrite[0], POWER_TYPE_MANA );
		//and our demon
		if( context->in_Caller->IsPlayer() && SafePlayerCast(context->in_Caller)->GetSummon() )
			context->in_Caller->Energize( SafePlayerCast(context->in_Caller)->GetSummon(), 57669, context->out_dmg_overwrite[0], POWER_TYPE_MANA );
		context->in_event->LastTrigger = getMSTime(); // consider it triggered
		//also has a chance to restore mana for others in party
		if( Rand( context->in_OwnerSpell->EffectBasePoints[1]+1 ) == false )
			return;
	}
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_54648( ProcHandlerContextShare *context )
{
	//actually cast it on the caster that put this aura on us
	SpellCastTargets targets2( context->in_event->caster );
	Spell *spell = SpellPool.PooledNew();
	SpellEntry *spd = dbcSpell.LookupEntryForced( context->in_event->spellId );
	spell->Init(context->in_Caller, spd ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId=context->in_OwnerSpell->Id;
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_44413( ProcHandlerContextShare *context )
{
	//When you absorb damage your spell damage is increased by $s1% of the amount absorbed for $44413d.  
	//Total spell damage increase cannot exceed 5% of your health.
	context->out_dmg_overwrite[0] = (context->in_OwnerSpell->EffectBasePoints[0] + 1) * context->in_abs / 100;
	if( context->out_dmg_overwrite[0] > (int32)context->in_Caller->GetUInt32Value( UNIT_FIELD_HEALTH ) * 5 / 100 )
		context->out_dmg_overwrite[0] = (int32)context->in_Caller->GetUInt32Value( UNIT_FIELD_HEALTH ) * 5 / 100;
	//for sake of people reporting it as not working
	if( context->out_dmg_overwrite[0] < 1 )
		context->out_dmg_overwrite[0] = 1;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_28682( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	//only trigger effect for specified spells
	if( !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING)
		|| context->in_CastingSpell->School != SCHOOL_FIRE )
		return;
	if( ( context->in_events_filter_flags & PROC_ON_SPELL_CRIT_HIT ) != 0 
//							&& CastingSpell->quick_tickcount == 1 
		)
	{
//							itr2->procCharges++;
//							if( itr2->procCharges >= 3 ) //whatch that number cause it depends on original stack count !
		context->in_event->created_with_value++;
		if( context->in_event->created_with_value >= 4 ) //whatch that number cause it depends on original stack count !
		{
//								RemoveAllAuraByNameHash( SPELL_HASH_COMBUSTION );
			context->in_Caller->RemoveAllAuras( 11129,0 );
			context->in_Caller->RemoveAllAuras( 28682,0 );
			return;
		}
	}
}

void PH_12579( ProcHandlerContextShare *context )
{
	// Winter's Chill shouldn't proc on self
	if (context->in_Victim == context->in_Caller) 
		return;
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	//only trigger effect for specified spells
	if(!(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
		return;
	//only frost spels
	if( context->in_CastingSpell->School != SCHOOL_FROST )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_63675( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	context->out_dmg_overwrite[0] = (context->in_CastingSpell->EffectBasePoints[0] + 1) * (context->in_OwnerSpell->EffectBasePoints[1]+1) * context->in_CastingSpell->quick_tickcount / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_63544( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	context->out_dmg_overwrite[0] = (context->in_CastingSpell->EffectBasePoints[0] + 1) * (context->in_OwnerSpell->EffectBasePoints[1]+1) * context->in_CastingSpell->quick_tickcount / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_41637( ProcHandlerContextShare *context )
{
	//victim got a hit in the face so we jump on next injured target
	//find aura on self and get it's value
	Aura *pa = context->in_Caller->FindAura( context->in_OwnerSpell->Id );
	if( !pa || !context->in_Caller->GetMapMgr() )
		return; //omg we have this proc on us and on second check we don't ? Return instead of continue since this seems to be a corupted object

	//check if we jumped proctimes
	if( pa->GetModAmount( 0 ) == 1 )
		return;

	//we use same caster as firts caster to be able to get heal bonuses !
	Unit *oricaster = context->in_Caller->GetMapMgr()->GetUnit( pa->GetCasterGUID() );
	if( !oricaster || !oricaster->IsPlayer() )
		return;

	//the nasty part : get a new target ^^
	Player *p_caster = SafePlayerCast(oricaster);
	Player *First_new_target,*Next_new_target,*First_whatever;
	First_new_target = Next_new_target = First_whatever = NULL;
//	bool passed_prev_target = false;
	SubGroup * pGroup = p_caster->GetGroup() ? p_caster->GetGroup()->GetSubGroup(p_caster->GetSubGroup()) : 0;

	if(pGroup)
	{
		p_caster->GetGroup()->Lock();

		float range=GetMaxRange(dbcSpellRange.LookupEntry(context->in_OwnerSpell->rangeIndex));
		range*=range;

		GroupMembersSet::iterator itr;
		for(itr = pGroup->GetGroupMembersBegin();itr != pGroup->GetGroupMembersEnd(); ++itr)
		{
			if(!(*itr)->m_loggedInPlayer || !(*itr)->m_loggedInPlayer->isAlive() )
				continue;

			//we cannot retarget self
			if( (*itr)->m_loggedInPlayer == context->in_Caller ) 
//			{
//				passed_prev_target = true;
				continue;
//			}

			if( IsInrange(p_caster,(*itr)->m_loggedInPlayer, range) )
			{

				if( !First_whatever )
					First_whatever = (*itr)->m_loggedInPlayer;

				//we target stuff that has no full health. No idea if we must fill target list or not :(
				if( First_whatever && (*itr)->m_loggedInPlayer->GetUInt32Value( UNIT_FIELD_HEALTH ) == (*itr)->m_loggedInPlayer->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
					continue;

				//first targatable player in group (like make circular buffer from normal list)
				if( !First_new_target )
					First_new_target = (*itr)->m_loggedInPlayer; 

//				if( passed_prev_target )
				{
					if( Next_new_target==NULL || Next_new_target->GetHealthPct() > (*itr)->m_loggedInPlayer->GetHealthPct() )
						Next_new_target = (*itr)->m_loggedInPlayer;
//					break;
				}
			}
		}
		p_caster->GetGroup()->Unlock();
	}
	if( First_new_target && !Next_new_target )
		Next_new_target = First_new_target; //we passed end of the list and it is time to restart it

	if( !Next_new_target )
		Next_new_target = First_whatever; //we passed end of the list and it is time to restart it

	if( !Next_new_target )
		Next_new_target = p_caster; //we passed end of the list and it is time to restart it

	if( Next_new_target )
	{
		Spell *spell = SpellPool.PooledNew();
		spell->Init( p_caster, context->in_OwnerSpell ,true, NULL);
		spell->forced_basepoints[0] = pa->GetModAmount( 0 ) - 1 ;
		SpellCastTargets targets2( Next_new_target->GetGUID() ); //no target so spelltargeting will get an injured party member
		spell->prepare( &targets2 );
	}
	//do the healing on this target
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_15258( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	if( context->in_CastingSpell->School != SCHOOL_SHADOW || !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) ) //we need damaging spells for this, so we suppose all shadow spells casted on target are dmging spells = Wrong
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_15473( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return; //hmm, how on earth did they use this talent ?
	if( SafePlayerCast( context->in_Caller )->GetShapeShift() != FORM_SHADOW )
		return;
	//remove movement imparing effects from caster
	context->in_Caller->RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_15363( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell || !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_27813( ProcHandlerContextShare *context )
{
 	if( context->in_Caller->IsPlayer() == false )
		return; //hmm, how on earth did they use this talent ?
	if( context->in_dmg <= 0 )
        return;
    SpellEntry *parentproc= dbcSpell.LookupEntry(context->in_OwnerSpell->Id);
	SpellEntry *spellInfo = dbcSpell.LookupEntry(context->in_event->spellId);
	if (!parentproc || !spellInfo)
		return;
	int32 val = parentproc->EffectBasePoints[0] + 1;
    Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->forced_basepoints[0] = (val*context->in_dmg)/(spellInfo->quick_tickcount)/100; //per tick
    SpellCastTargets targets2( context->in_Caller->GetGUID() );
    spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_51945( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell || !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_52179( ProcHandlerContextShare *context )
{
	//self stun ? noway
	if( context->in_Victim == context->in_Caller )
		return;
	if( context->in_CastingSpell->MechanicsType != MECHANIC_SILENCED
		&& context->in_CastingSpell->MechanicsType != MECHANIC_STUNNED
		&& context->in_CastingSpell->MechanicsType != MECHANIC_FLEEING )
		return;
	SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->forced_basepoints[0] = -context->in_OwnerSpell->EffectBasePoints[0] - 1;
	spell->forced_duration = context->in_CastingSpell->quick_duration_min;
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId=context->in_OwnerSpell->Id;
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_70831( ProcHandlerContextShare *context )
{
	//get the count of Maelstrom Weapon
	Aura *p = context->in_Caller->FindAura( 53817 );
	if( ( p && p->m_visualSlot < MAX_VISIBLE_AURAS && context->in_Caller->m_auraStackCount[ p->m_visualSlot ] == 5 ) == false )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_29177( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	//only trigger effect for specified spells
	if( !(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING)) 
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_63375( ProcHandlerContextShare *context )
{
	context->out_dmg_overwrite[0] = context->in_Caller->GetUInt32Value( UNIT_FIELD_BASE_MANA ) * (context->in_CastingSpell->EffectBasePoints[0] + 1) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_16177( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( !(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING) ) //healing spell
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_8026( ProcHandlerContextShare *context )
{
 	if( context->in_Caller->IsPlayer() == false )
		return; 
	Item * mh = SafePlayerCast( context->in_Caller )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );

	if( mh != NULL)
	{
		SpellEntry *spe = dbcSpell.LookupEntry( context->in_event->spellId );
		uint32 base = mh->GetProto()->Delay * (spe->EffectBasePoints[0] + 1) / 2000;
		uint32 min = base / 77 ;
		uint32 max = base / 25 ;
		context->out_dmg_overwrite[0] = min + RandomUInt( max - min );
	}
	else
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_16246( ProcHandlerContextShare *context )
{
	if( context->in_OwnerSpell->Id == 39805 )
		return; // Lightning Overload Proc is already free
	if( context->in_CastingSpell == NULL )
		return;
	if(context->in_CastingSpell->NameHash!=SPELL_HASH_LIGHTNING_BOLT&&
		context->in_CastingSpell->NameHash!=SPELL_HASH_CHAIN_LIGHTNING&&
		context->in_CastingSpell->NameHash!=SPELL_HASH_EARTH_SHOCK&&
		context->in_CastingSpell->NameHash!=SPELL_HASH_FLAME_SHOCK&&
		context->in_CastingSpell->NameHash!=SPELL_HASH_FROST_SHOCK)
		return;
	SpellCastTargets targets2( context->in_Victim->GetGUID() ); //no target so spelltargeting will get an injured party member
	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init( context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId=context->in_OwnerSpell->Id;
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_33010( ProcHandlerContextShare *context )
{
 	if( context->in_Caller->IsPlayer() == false )
		return; 
	Item *it;
	SpellEntry *sp_for_the_logs;
	if(SafePlayerCast( context->in_Caller )->GetItemInterface())
	{
		it = SafePlayerCast( context->in_Caller )->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
		if(it)
		{
			EnchantmentInstance * Enchantment = it->GetEnchantment(ITEM_ENCHANT_SLOT_TEMPORARY2);
			if( Enchantment )
			{
				uint32 tspellid;
				if( Enchantment->Enchantment->Id == 283 )
					tspellid = 8232;
				else if( Enchantment->Enchantment->Id == 284 )
					tspellid = 8235;
				else if( Enchantment->Enchantment->Id == 525 )
					tspellid = 10486;
				else if( Enchantment->Enchantment->Id == 1669 )
					tspellid = 16362;
				else if( Enchantment->Enchantment->Id == 2636 )
					tspellid = 25505;
				else if( Enchantment->Enchantment->Id == 3785 )
					tspellid = 58801;
				else if( Enchantment->Enchantment->Id == 3786 )
					tspellid = 58803;
				else if( Enchantment->Enchantment->Id == 3787 )
					tspellid = 58804;
				else return;
				sp_for_the_logs = dbcSpell.LookupEntry( tspellid );
			}
			else return;
		}
		else return;
	}
	else return;

	uint32 AP_owerride = sp_for_the_logs->EffectBasePoints[1] + 1;
	//we have to recalc the value of this spell
	uint32 dmg2 = SafePlayerCast( context->in_Caller )->GetMainMeleeDamage(AP_owerride);
	context->in_Caller->Strike( context->in_Victim, MELEE, sp_for_the_logs, dmg2, 0, 0, true, false );
	if( SafePlayerCast( context->in_Caller )->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND) )
		context->in_Caller->Strike( context->in_Victim, MELEE, sp_for_the_logs, dmg2, 0, 0, true, false );
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_14157( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	//we need a finishing move for this 
	if(!(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE) || context->in_Victim==context->in_Caller)
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_14181( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	int32 proc_Chance2;
	//chance is based actually on combopoint count and not 100% always 
	if( ( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE) && context->in_Caller->IsPlayer())
		proc_Chance2 = SafePlayerCast( context->in_Caller )->m_comboPoints*context->in_OwnerSpell->EffectBasePoints[1];
	else 
		return;
	if(!Rand(proc_Chance2))
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_58427( ProcHandlerContextShare *context )
{
	if( context->in_events_filter_flags & PROC_ON_AURA_REMOVE )
	{
		Aura *a = context->in_Caller->FindAura( 58427 );
		if( a )	//maybe manually removed it ?
		{
			a->SetDuration( 20000 );
			a->ResetTimeLeft();
			if( sEventMgr.HasEvent( a, EVENT_AURA_REMOVE ) )
				sEventMgr.ModifyEventTimeLeft(a, EVENT_AURA_REMOVE, 20000);
			else
				sEventMgr.AddEvent(a, &Aura::Remove, EVENT_AURA_REMOVE, a->GetDuration(), 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT | EVENT_FLAG_DELETES_OBJECT);
			context->in_Caller->ModVisualAuraStackCount(a, 0);
		}
		return;
	}
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

/*
void PH_31234( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	if(!(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE))
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
} */

void PH_32861( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell && ( context->in_Caller == context->in_Victim || !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) ) ) //no self casts allowed or beneficial spells
		return;//this should not ocur unless we made a fuckup somewhere
	context->in_Caller->SpellNonMeleeDamageLog( context->in_Victim, context->in_OwnerSpell, context->in_OwnerSpell->EffectBasePoints[0]+1, true );
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

/*
void PH_15269( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	if( context->in_CastingSpell->School != SCHOOL_SHADOW || !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}
*/

void PH_12536( ProcHandlerContextShare *context )
{
	//requires damageing spell
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	if( !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_52752( ProcHandlerContextShare *context )
{
 	if( context->in_Caller->IsPlayer() == false )
		return; 
	uint64 new_target = Spell::FindLowestHealthRaidMember( SafePlayerCast( context->in_Caller ), 1600); // within 40 yards
	if( new_target == 0 )	// shouldn't happen
		return;

	SpellCastTargets targets2( new_target ); //no target so spelltargeting will get an injured party member
	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->forced_basepoints[0] = context->in_dmg * (context->in_OwnerSpell->EffectBasePoints[0] + 1) / 100; 
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_54748( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell || !(HasMechanic(context->in_CastingSpell, MECHANIC_SILENCED) || 
		HasMechanic(context->in_CastingSpell, MECHANIC_INTERRUPTED)))
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_12494( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	//frost
	if( context->in_CastingSpell->School != SCHOOL_FROST )
		return;
	//need to have chill effect-> wtf is a chill effect ?
	if( (context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_CHILL_SPELL) == 0 )
		return;
	//fingers of frost set flag frozen and remove it on remove
	if( context->in_event->spellId == 44544 || context->in_event->spellId == 74396 )
		context->in_Victim->SetFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_FROZEN );
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_57761( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	//frost
	if( context->in_CastingSpell->School != SCHOOL_FROST )
		return;
	//damaging
	if( (context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING) == 0 )
		return;
	//speel needs to have chill effect -> no idea :S, all ?
	if( (context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_CHILL_SPELL) == 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_12484( ProcHandlerContextShare *context )
{
	if(  context->in_Victim == context->in_Caller ) //Blizzard
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_29077( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
//	if( CastingSpell->School!=SCHOOL_FIRE && CastingSpell->School!=SCHOOL_FROST) //fire and frost criticals
//		continue;
	int32 costpct = context->in_Caller->GetUInt32Value( UNIT_FIELD_BASE_MANA ) * context->in_CastingSpell->ManaCostPercentage / 100;
	context->out_dmg_overwrite[0] = (context->in_CastingSpell->manaCost + costpct)* ( context->in_OwnerSpell->EffectBasePoints[0] + 1 ) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_51185( ProcHandlerContextShare *context )
{
	context->out_dmg_overwrite[0] = context->in_OwnerSpell->EffectBasePoints[ 0 ] + 1; //!! not same as next !
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_51178( ProcHandlerContextShare *context )
{
	context->out_dmg_overwrite[0] = context->in_OwnerSpell->EffectBasePoints[ 1 ] + 1;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_13810( ProcHandlerContextShare *context )
{
	if( context->in_Caller->m_ObjectSlots[ 0 ] == NULL ) 
		return; //no trap active ?
	GameObject *trap = context->in_Caller->GetMapMgr()->GetGameObject( context->in_Caller->m_ObjectSlots[0] );

	SpellCastTargets targets2; //no target so spelltargeting will get an injured party member
	targets2.m_targetMask = TARGET_FLAG_SOURCE_LOCATION;
	targets2.m_srcX = trap->GetPositionX();
	targets2.m_srcY = trap->GetPositionY();
	targets2.m_srcZ = trap->GetPositionZ();

	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_62606( ProcHandlerContextShare *context )
{
	uint8 shapeshift = context->in_Caller->GetByte( UNIT_FIELD_BYTES_2, 3 );
	if( shapeshift != FORM_BEAR && shapeshift != FORM_DIREBEAR )
		return;
	context->out_dmg_overwrite[0] = context->in_Caller->GetAP() * ( context->in_OwnerSpell->EffectBasePoints[0] + 1 ) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_34075( ProcHandlerContextShare *context )
{
 	if( context->in_Caller->IsPlayer() == false )
		return; 
	//crazy formula : maxmana * weaponspeed/100
	uint32 maxMana = context->in_Caller->GetUInt32Value( UNIT_FIELD_MAXPOWER1 );
	uint32 weaponspeed = 2000;
	Item *pItem;
	if( (pItem = SafePlayerCast( context->in_Caller )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND)) != 0)
		if( pItem->GetProto() )
			weaponspeed = pItem->GetProto()->Delay;
	context->out_dmg_overwrite[0] = weaponspeed * maxMana / 1000 / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_34720( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	uint32 mana_cost_prev = context->in_Caller->GetUInt32Value( UNIT_FIELD_POWER1 ) * context->in_CastingSpell->ManaCostPercentage / 100 + context->in_CastingSpell->manaCost;
	context->out_dmg_overwrite[0] = mana_cost_prev * 40 / 100;
//	Energize( this, 34720, dmg_overwrite, POWER_TYPE_MANA );
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_63468( ProcHandlerContextShare *context )
{
	SpellEntry *spe = dbcSpell.LookupEntry( context->in_event->spellId );
	context->out_dmg_overwrite[0] = context->in_dmg * ( context->in_OwnerSpell->EffectBasePoints[0] + 1) / 100;
	context->out_dmg_overwrite[0] = context->out_dmg_overwrite[0] / spe->quick_tickcount;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_47753( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( (context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ) == 0 )
		return;
	context->out_dmg_overwrite[0] = context->in_dmg * ( context->in_OwnerSpell->EffectBasePoints[0] + 1 ) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_63731( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	context->out_dmg_overwrite[0] = ( context->in_CastingSpell->manaCost + context->in_CastingSpell->ManaCostPercentage * context->in_Caller->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) / 100 ) * ( context->in_OwnerSpell->EffectBasePoints[0] + 1 );
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_33619( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	//make a direct strike then exit rest of handler
	context->out_dmg_overwrite[0] = context->in_abs * ( context->in_OwnerSpell->EffectBasePoints[0] + 1 ) / 100;
	//somehow we should make this not cause any threat (tobedone)
//	SpellNonMeleeDamageLog( victim, power_word_id, dmg_overwrite, false, true );
	context->in_Caller->SpellNonMeleeDamageLog( context->in_Victim, 33619, context->out_dmg_overwrite[0], false, true );
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
	return;
	//or the old traditional way ? What if this gets resisted and stuff ?
//	dmg_overwrite = Abs * ( ospinfo->EffectBasePoints[0] + 1 ) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_47930( ProcHandlerContextShare *context )
{
	//only proc on friendly target (pennance will target enemy also)
	if( isAttackable( context->in_Victim, context->in_Caller, false ) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_35542( ProcHandlerContextShare *context )
{
 	if( context->in_Caller->IsPlayer() == false )
		return; 
	if(context->in_dmg )
		return;
	//this needs offhand weapon
	Item* it = SafePlayerCast( context->in_Caller )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
	if( it == NULL || it->GetProto()->InventoryType != INVTYPE_WEAPON )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_66233( ProcHandlerContextShare *context )
{
	//Damage that takes you below 35% health is reduced by 20%.  
	int32 new_health = (int32)context->in_Caller->GetHealth() - context->in_dmg + context->in_abs;
	if( new_health < 0 )
		return;	//seems like we are doomed
	if( new_health * 100 / context->in_Caller->GetUInt32Value(UNIT_FIELD_MAXHEALTH) > 35 )
		return;
	context->out_dmg_absorb += (context->in_dmg + context->in_abs) * (context->in_OwnerSpell->EffectBasePoints[0] + 1)/100;
	//do not enable it -> this spell has 2 proc events !
//	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_66235( ProcHandlerContextShare *context )
{
 	if( context->in_Caller->IsPlayer() == false )
		return; 
	//Damage that takes you below 35% health is reduced by 20%.  
	int32 new_health = (int32)context->in_Caller->GetHealth() - ( context->in_dmg - context->in_abs);
	if( new_health > 0 )
		return;	
	context->out_dmg_absorb += (-new_health) + 5;	//avoid death
	//400 defense skill gets you no heal
	int32 defense_skill = SafePlayerCast( context->in_Caller )->_GetSkillLineCurrent( SKILL_DEFENSE );
//						defense_skill = MAX( 0, defense_skill - 400); - good
	defense_skill = MAX( 0, defense_skill - 300); // - not good but people report it as a bug if it works blizzlike :(
	uint32 heal_pct = defense_skill * 100 / 140 * (context->in_OwnerSpell->EffectBasePoints[1] + 1) / 100;
	uint32 heal_flat = context->in_Caller->GetUInt32Value(UNIT_FIELD_MAXHEALTH) * heal_pct / 100;
	uint32 dmg_overwrite = heal_flat;
	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->forced_basepoints[0] = dmg_overwrite;
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId=context->in_OwnerSpell->Id;
//printf("!!!!! wil proc spell with target guid %u \n",(uint32)(targets.m_unitTarget) & LOWGUID_ENTRY_MASK);
	SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
//	context->in_event->LastTrigger = getMSTime(); // consider it triggered
	context->in_event->LastTrigger = getMSTime() + 60000 * 2; // consider it triggered and do not let it trigger again for a while
}

void PH_63521( ProcHandlerContextShare *context )
{
	Aura *taur = context->in_Caller->FindAura( 54428 );
	if( taur )
	{
		taur->ResetTimeLeft();
		sEventMgr.ModifyEventTimeLeft(taur, EVENT_AURA_REMOVE, taur->GetDuration());
		context->in_Caller->ModVisualAuraStackCount(taur, 0);
	}
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_20178( ProcHandlerContextShare *context )
{
	//do not proc it on abilities like extra attacks
	if( context->in_CastingSpell != NULL )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_31934( ProcHandlerContextShare *context )
{
	int32 res = (context->in_dmg - context->in_abs)/2;
	if( res > 0 )
		context->out_dmg_absorb += res;
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_20272( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL || context->in_Victim != context->in_Caller )
		return;
	uint32 mana_cost_prev = context->in_Caller->GetUInt32Value( UNIT_FIELD_POWER1 ) * context->in_CastingSpell->ManaCostPercentage / 100 + context->in_CastingSpell->manaCost;
	uint32 dmg_overwrite = mana_cost_prev * (context->in_OwnerSpell->EffectBasePoints[1] + 1) / 100;
	context->in_Caller->Energize( context->in_Caller, 20272, dmg_overwrite, POWER_TYPE_MANA );
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_31930( ProcHandlerContextShare *context )
{
	context->in_Caller->Energize( context->in_Caller, context->in_OwnerSpell->Id, context->in_Caller->GetUInt32Value( UNIT_FIELD_BASE_MANA ) * 25 / 100, POWER_TYPE_MANA );
	SpellEntry *spellInfo = dbcSpell.LookupEntry( 57669 );//replenish the whole party
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId=context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_61840( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_WISDOM &&
		context->in_CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_JUSTICE &&
		context->in_CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_LIGHT &&
		context->in_CastingSpell->NameHash != SPELL_HASH_CRUSADER_STRIKE &&
		context->in_CastingSpell->NameHash != SPELL_HASH_DIVINE_STORM )
		return;
	context->out_dmg_overwrite[0] = (context->in_OwnerSpell->EffectBasePoints[0] + 1) * ( context->in_dmg - context->in_abs ) / 100;
	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_54203( ProcHandlerContextShare *context )
{
	const uint32 tickcount = 12000 / 2000; // hehe, never do this ;P
	context->out_dmg_overwrite[0] = ( context->in_OwnerSpell->EffectBasePoints[0] + 1 ) * ( context->in_dmg - context->in_abs ) / (100  * tickcount );
	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_31786( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	//trigger only on heal spell cast by NOT us
	if( context->in_Victim == context->in_Caller )
		return; 
//	if( !( CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ) )
//		continue; 
	//this is not counting the bonus effects on heal
	context->out_dmg_overwrite[0] = context->in_dmg * (context->in_OwnerSpell->EffectBasePoints[0] + 1 ) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_25997( ProcHandlerContextShare *context )
{
	if( context->in_Victim == context->in_Caller )
		return; //not self casted crits
	//requires damageing spell
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	if(!(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
		return;

	//this should contain the same values as the fixed ones
	context->out_dmg_overwrite[0] = ( context->in_dmg *  (context->in_OwnerSpell->EffectBasePoints[0] + 1 )) / 100 ; //only half dmg

	/*
	provided by a patch to give same result ?
	if(itr2->origId == 9799)
		dmg_overwrite = (dmg *  15) / 100;
	
	if(itr2->origId == 25988)
		dmg_overwrite = ( dmg *  30) / 100;
		*/

	int32 half_health = context->in_Caller->GetUInt32Value(UNIT_FIELD_HEALTH) >> 1;
	if( context->out_dmg_overwrite[0] > half_health )
		context->out_dmg_overwrite[0] = half_health ;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_31828( ProcHandlerContextShare *context )
{
	//we should test is damage is from enviroment or not :S
	context->out_dmg_absorb += context->in_dmg/2;
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_53654( ProcHandlerContextShare *context )
{
	//requires damageing spell
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	if(!(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
		return;

	//duplicate this healing spell to be casted on original aura caster
	//note that we hacked this itr2->caster value to contain the redirection target value
	//instant heal 100% of the spell casted on other raid target member
	//now we should get the heal amount with caster bonus and all
	uint32 dmg_overwrite = 0;
	if( IsHealingEffect( context->in_CastingSpell, 2 ) )
		dmg_overwrite = (context->in_CastingSpell->EffectBasePoints[2] + 1) * context->in_CastingSpell->quick_tickcount;
	else if( IsHealingEffect( context->in_CastingSpell, 1 ) )
		dmg_overwrite = (context->in_CastingSpell->EffectBasePoints[1] + 1) * context->in_CastingSpell->quick_tickcount;
	else	//might fail the heal test due to scripted spells
		dmg_overwrite = (context->in_CastingSpell->EffectBasePoints[0] + 1) * context->in_CastingSpell->quick_tickcount;

	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->forced_basepoints[0] = dmg_overwrite;
	spell->static_dmg[0] = 1;
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId=context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_event->caster ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_59052( ProcHandlerContextShare *context )
{
	//reset cooldown on Howling Blast
	if( context->in_Caller->IsPlayer() )
	{
		SafePlayerCast(context->in_Caller)->ClearCooldownForSpell( 49184 );
		SafePlayerCast(context->in_Caller)->ClearCooldownForSpell( 51409 );
		SafePlayerCast(context->in_Caller)->ClearCooldownForSpell( 51410 );
		SafePlayerCast(context->in_Caller)->ClearCooldownForSpell( 51411 );
	}
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_51911( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;	//noway check
	//requires direct spell damage
	if( context->in_CastingSpell->quick_tickcount != 1 )
		return;
	//just in case checks for masochists
	if( context->in_Victim == context->in_Caller )
		return;
	//chance if parry chance
	float proc_chance = context->in_Caller->GetFloatValue( PLAYER_PARRY_PERCENTAGE );
	if( Rand( proc_chance ) == false )
		return;
	int tabs = ( context->in_dmg - context->in_abs ) * ( context->in_OwnerSpell->EffectBasePoints[0] + 1 ) / 100;
	if( tabs < 0 )
		tabs = 0;
	context->out_dmg_absorb += tabs;
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_71519( ProcHandlerContextShare *context )
{
	uint32 spellId = 0;
	if( context->in_Caller->getClass() == DEATHKNIGHT)
	{
		//DK: Str, Haste, Crit
		const uint32 spells[3] = {71484,71492,71491};
		spellId = spells[ RandomUInt() % 3 ];
	}
	else if( context->in_Caller->getClass() == DRUID )
	{
		//Druid: Str, Agi, Haste
		const uint32 spells[3] = {71484,71485,71492};
		spellId = spells[ RandomUInt() % 3 ];
	}
	else if( context->in_Caller->getClass() == HUNTER )
	{
		//Hunter: Agi, Crit, AP
		const uint32 spells[3] = {71485,71487,71486};
		spellId = spells[ RandomUInt() % 3 ];
	}
	else if( context->in_Caller->getClass() == PALADIN )
	{
		//Paladin: Str, Haste, Crit
		const uint32 spells[3] = {71484,71492,71487};
		spellId = spells[ RandomUInt() % 3 ];
	}
	else if( context->in_Caller->getClass() == ROGUE )
	{
		//Rogue: Agi, Haste, AP
		const uint32 spells[3] = {71485,71492,71486};
		spellId = spells[ RandomUInt() % 3 ];
	}
	else if( context->in_Caller->getClass() == WARRIOR )
	{
		//Warrior: Str, Crit, Haste
		const uint32 spells[3] = {71484,71487,71492};
		spellId = spells[ RandomUInt() % 3 ];
	}
	else 
//							if( getClass() == SHAMAN )	//and rest of the classes
	{
		//Shaman: Agi, AP, Haste
		const uint32 spells[3] = {71485,71486,71492};
		spellId = spells[ RandomUInt() % 3 ];
	}
	SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );//replenish the whole party
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId=context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_event->caster ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_71633( ProcHandlerContextShare *context )
{
	if( context->in_Caller->GetHealthPct() > context->in_OwnerSpell->EffectBasePoints[0] )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_40972( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if(!(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
		return;
	//Melee attacks which reduce you below $s1% health cause you to gain $71633s1 armor for $71633d.  Cannot occur more than once every 30 sec.
	if( context->in_Caller->GetHealthPct() > context->in_OwnerSpell->EffectBasePoints[0] )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_71566( ProcHandlerContextShare *context )
{
	//Each time your spells heal a target you have a chance to cause another nearby friendly target to be instantly healed for $71610s1.
	if( context->in_CastingSpell == NULL )
		return;
	if(!(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_71610( ProcHandlerContextShare *context )
{
	//Each time your spells heal a target you have a chance to cause another nearby friendly target to be instantly healed for $71610s1.
	if( context->in_CastingSpell == NULL )
		return;
	if(!(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING))
		return;
	//need to find a new target with low health
	context->in_Caller->AquireInrangeLock(); //make sure to release lock before exit function !
	Unit *minHPunit = NULL;
	std::set<Object*>::iterator itr;
	for( itr = context->in_Caller->GetInRangeSetBegin(); itr != context->in_Caller->GetInRangeSetEnd(); itr++ )
	{
		if( !(*itr)->IsUnit() || !SafeUnitCast((*itr))->isAlive())
			continue;

		//we target stuff that has no full health. No idea if we must fill target list or not :(
		if( (*itr)->GetUInt32Value( UNIT_FIELD_HEALTH ) == (*itr)->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
			continue;

		if( !isAttackable(context->in_Caller,(*itr)) )
		{
			if( minHPunit == NULL )
				minHPunit = SafeUnitCast(*itr);
			else if( minHPunit->GetHealthPct() > SafeUnitCast(*itr)->GetHealthPct() )
				minHPunit = SafeUnitCast(*itr);
		}
	}
	context->in_Caller->ReleaseInrangeLock();	

	if( minHPunit == NULL )
		minHPunit = context->in_Caller;

	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );//replenish the whole party
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId=context->in_OwnerSpell->Id;
	SpellCastTargets targets2( minHPunit->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_72418( ProcHandlerContextShare *context )
{
	//needs benficial spell
	if( isAttackable(context->in_Caller,context->in_Victim ) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_60530( ProcHandlerContextShare *context )
{
	//needs benficial spell
	if( context->in_CastingSpell == NULL )
		return;
	//need direct spells
	if( context->in_CastingSpell->EffectAmplitude[0] != 0 && context->in_CastingSpell->EffectAmplitude[1] != 0 && context->in_CastingSpell->EffectAmplitude[2] != 0 )
		return;
	if( ( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ) == 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_71888( ProcHandlerContextShare *context )
{
	uint32 spellId;
	//the casted spell depends on the power type of the target
	switch( context->in_Victim->GetPowerType() )
	{
		case POWER_TYPE_MANA : spellId = 71888;			break;
		case POWER_TYPE_ENERGY : spellId = 71887;		break;
		case POWER_TYPE_RAGE : spellId = 71886;			break;
		default: return;
	}
	SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_71881( ProcHandlerContextShare *context )
{
	uint32 spellId;
	//the casted spell depends on the power type of the target
	switch( context->in_Victim->GetPowerType() )
	{
		case POWER_TYPE_MANA : spellId = 71881;			break;
		case POWER_TYPE_ENERGY : spellId = 71882;		break;
		case POWER_TYPE_RAGE : spellId = 71882;			break;
		default: return;
	}
	SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_72416( ProcHandlerContextShare *context )
{
	//needs harmfull spell
	if( isAttackable(context->in_Caller,context->in_Victim ) == false )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_71564( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	//need direct spells
	if( context->in_CastingSpell->EffectAmplitude[0] != 0 && context->in_CastingSpell->EffectAmplitude[1] != 0 && context->in_CastingSpell->EffectAmplitude[2] != 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_33370( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	//need direct spells
	if( !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_67354( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_MANGLE__BEAR_ 
		&& context->in_CastingSpell->NameHash != SPELL_HASH_MANGLE__CAT_
		&& context->in_CastingSpell->NameHash != SPELL_HASH_LACERATE
		&& context->in_CastingSpell->NameHash != SPELL_HASH_SWIPE
		&& context->in_CastingSpell->NameHash != SPELL_HASH_SHRED
		)
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_60520( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) && !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ))
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_60518( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ))
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_53372( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ))
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_45055( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ))
		return;
	//need periodic spells
	if( context->in_CastingSpell->EffectAmplitude[0] == 0 && context->in_CastingSpell->EffectAmplitude[1] == 0 && context->in_CastingSpell->EffectAmplitude[2] == 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_38324( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ))
		return;
	//need periodic spells
	if( context->in_CastingSpell->EffectAmplitude[0] == 0 && context->in_CastingSpell->EffectAmplitude[1] == 0 && context->in_CastingSpell->EffectAmplitude[2] == 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_75493( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING ))
		return;
	//need direct spells
	if( context->in_CastingSpell->EffectAmplitude[0] != 0 || context->in_CastingSpell->EffectAmplitude[1] != 0 || context->in_CastingSpell->EffectAmplitude[2] != 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_379( ProcHandlerContextShare *context )
{
	context->out_dmg_overwrite[0] = context->in_OwnerSpell->EffectBasePoints[0] + 1; ;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_30675( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_dmg <= 0 )
		return;	//never, i tell you that never !
	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_CastingSpell->Id );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->forced_basepoints[0] = context->in_dmg / 2;	//half damage but same spell
	spell->static_dmg[0] = 1;	//do not double add the spell power coefficient
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_63685( ProcHandlerContextShare *context )
{
	//target needs to ne at min N yards
	if( context->in_Victim == NULL )
		return;
	SpellEntry *spe = dbcSpell.LookupEntry( context->in_event->spellId );
	float r = ( spe->EffectBasePoints[ 0 ] + 1.0f );
	if( context->in_Caller->GetDistance2dSq( context->in_Victim ) < r * r )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_48517( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_STARFIRE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_48518( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_WRATH )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_37379( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if (context->in_CastingSpell->School != SCHOOL_SHADOW || !(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING))
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_71905( ProcHandlerContextShare *context )
{
	//count the number of soul shards on us
	SpellEntry *spe = dbcSpell.LookupEntry( context->in_event->spellId );
	uint32 count = context->in_Caller->CountAura( 71905 );
	if( count == spe->maxstack )
	{
		context->in_Caller->RemoveAllAuras( 71905, 0 );	//soul fragment
		context->in_Caller->RemoveAllAuras( 72521, 0 );	//shadowmourne effect low 
		context->in_Caller->RemoveAllAuras( 72523, 0 );	//shadowmourne effect high
		uint32 spellId = 71904;	//Chaos Bane
		SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
		Spell *spell = SpellPool.PooledNew();
		spell->Init(context->in_Caller, spellInfo ,true, NULL);
		spell->ProcedOnSpell = context->in_CastingSpell;
		spell->pSpellId = context->in_OwnerSpell->Id;
		SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
		spell->prepare(&targets2);
		context->in_event->LastTrigger = getMSTime(); // consider it triggered
		return;
	}
	//visual effect some souls around the caster
//	if( count == 0 )
	{
		SpellEntry *spellInfo = dbcSpell.LookupEntry( 72521 );
		Spell *spell = SpellPool.PooledNew();
		spell->Init(context->in_Caller, spellInfo ,true, NULL);
		spell->ProcedOnSpell = context->in_CastingSpell;
		spell->forced_duration = 60000;
		spell->pSpellId = context->in_OwnerSpell->Id;
		SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
		spell->prepare(&targets2);
	}
	//visual effect some souls around the caster with larger area
	if( count >= 5 )
	{
		SpellEntry *spellInfo = dbcSpell.LookupEntry( 72523 );
		Spell *spell = SpellPool.PooledNew();
		spell->Init(context->in_Caller, spellInfo ,true, NULL);
		spell->ProcedOnSpell = context->in_CastingSpell;
		spell->forced_duration = 60000;
		spell->pSpellId = context->in_OwnerSpell->Id;
		SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
		spell->prepare(&targets2);
	}
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_71432( ProcHandlerContextShare *context )
{
	//count the number of soul shards on us
	SpellEntry *spe = dbcSpell.LookupEntry( context->in_event->spellId );
	uint32 count = context->in_Caller->CountAura( 71432 );
	if( count == spe->maxstack )
	{
		context->in_Caller->RemoveAllAuras( 71432, 0 );
		uint32 spellId = 71433;	
		SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
		Spell *spell = SpellPool.PooledNew();
		spell->Init(context->in_Caller, spellInfo ,true, NULL);
		spell->ProcedOnSpell = context->in_CastingSpell;
		spell->pSpellId = context->in_OwnerSpell->Id;
		SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
		spell->prepare(&targets2);
		context->in_event->LastTrigger = getMSTime(); // consider it triggered
		return;
	}
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_37378( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->School != SCHOOL_FIRE || !(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_37196( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if (
		context->in_CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_JUSTICE &&
		context->in_CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_LIGHT &&
		context->in_CastingSpell->NameHash != SPELL_HASH_JUDGEMENT_OF_WISDOM
		)
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_37656( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_40452( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_MANGLE__BEAR_ || context->in_CastingSpell->NameHash != SPELL_HASH_MANGLE__CAT_)
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_40445( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_STARFIRE )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_40446( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_REJUVENATION )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_40441( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_SHADOW_WORD__PAIN )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_40440( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_RENEW )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_40461( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	//we need a finishing move for this 
	if(!(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE) || context->in_Victim==context->in_Caller)
		return;
	if( context->in_Caller->IsPlayer() == false )
		return;
	//chance is combo point based
	uint32 combo_points = SafePlayerCast( context->in_Caller )->m_comboPoints;
	if( Rand( combo_points * 20 ) == false )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_37445( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->NameHash != SPELL_HASH_REPLENISH_MANA )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_16886( ProcHandlerContextShare *context )
{
	// Remove aura if it exists so it gets reapplied
	if ( context->in_Caller->HasAura(16886))
		context->in_Caller->RemoveAura(16886);
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_48504( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( context->in_CastingSpell->Id == 48503)
		return; //do not loop proc
	context->out_dmg_overwrite[0] = context->in_dmg * (context->in_OwnerSpell->EffectBasePoints[0] + 1) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_48503( ProcHandlerContextShare *context )
{
	context->out_dmg_overwrite[0] = context->in_event->created_with_value;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_64411( ProcHandlerContextShare *context )
{
//	if( dmg == -1 )
//		continue;//this is general proc. We need heal proc with an ammount
	if( context->in_CastingSpell == NULL )
		return;
//	if(!(CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING)) //requires healing spell.
//		continue;
	SpellEntry *spe = dbcSpell.LookupEntry( context->in_event->spellId );
	context->out_dmg_overwrite[0] = context->in_dmg * (spe->EffectBasePoints[0] + 1) / 100;
	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_65006( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( !(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING) && !(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING)) //requires healing spell.
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_60229( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	if( !(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING) && !(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING)) //requires healing spell.
		return;
    SpellEntry *spellInfo;
	Spell *spell;
	SpellCastTargets targets2( context->in_Caller->GetGUID() );
	uint32 spell_id,maxstat_value=0;
	if( context->in_Caller->GetUInt32Value( UNIT_FIELD_STRENGTH ) > maxstat_value )
	{
		maxstat_value = context->in_Caller->GetUInt32Value( UNIT_FIELD_STRENGTH );
		spell_id = 60229;//Increases your Strength by $s1 for $d.
	}
	if( context->in_Caller->GetUInt32Value( UNIT_FIELD_AGILITY ) > maxstat_value )
	{
		maxstat_value = context->in_Caller->GetUInt32Value( UNIT_FIELD_AGILITY );
		spell_id = 60233;//Increases your Agility by $s1 for $d.
	}
	if( context->in_Caller->GetUInt32Value( UNIT_FIELD_INTELLECT ) > maxstat_value )
	{
		maxstat_value = context->in_Caller->GetUInt32Value( UNIT_FIELD_INTELLECT );
		spell_id = 60234;//Increases your Intellect by $s1 for $d.
	}
	if( context->in_Caller->GetUInt32Value( UNIT_FIELD_SPIRIRT ) > maxstat_value )
	{
		maxstat_value = context->in_Caller->GetUInt32Value( UNIT_FIELD_SPIRIRT );
		spell_id = 60235;//Increases your Spirit by $s1 for $d.
	}
	spellInfo = dbcSpell.LookupEntry(spell_id);	
	if (spellInfo)
	{
		spell = SpellPool.PooledNew();
		spell->Init(context->in_Caller, spellInfo ,true, NULL);
		spell->prepare(&targets2);
	}
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_51124( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell != NULL )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_50362( ProcHandlerContextShare *context )
{
	if( context->in_Caller == context->in_Victim )
		return; //do not become "immune" to our spells
	if( context->in_CastingSpell == NULL || context->in_CastingSpell->School == SCHOOL_NORMAL || context->in_CastingSpell->School >= SCHOOL_COUNT )
		return;
	if( !isAttackable(context->in_Caller,context->in_Victim) )
		return; //friendly spells should not trigger it
	uint32 new_proc_id[SCHOOL_COUNT]={0,50490,50362,50488,50485,50489,50486};
	uint32 spellId = new_proc_id[ context->in_CastingSpell->School ];
	SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_50475( ProcHandlerContextShare *context )
{
	if( context->in_dmg < 1 )
		return; //we calculate our value based on our damage
	uint32 maxdif = context->in_Caller->GetUInt32Value(UNIT_FIELD_MAXHEALTH) - context->in_Caller->GetUInt32Value(UNIT_FIELD_HEALTH);
	//removed. Let them see the logs
//						if( maxdif == 0 )
//							continue;//nothing to heal
	int32 actual_dmg = context->in_dmg - context->in_abs;
	if( actual_dmg < 0 ) 
		actual_dmg = 0;
//	int32 toheal = (context->in_OwnerSpell->EffectBasePoints[1] + 1) * actual_dmg / 100;
	int32 toheal = context->in_event->created_with_value * actual_dmg / 100;	//so that improved blood presence mods the value properly
//						if( toheal > maxdif )
//							toheal = maxdif;
	if( toheal > 500 )
		toheal = 500;	// !!!hardcoded hack fix. Some people manage to get insane DMG that constatly heals them more then they get damage
	Spell *spell = SpellPool.PooledNew();
	SpellEntry *spe = dbcSpell.LookupEntry( context->in_event->spellId );
	spell->Init(context->in_Caller, spe ,true, NULL);	//hmmm maybe for the logs we need ospinfo ? description says we need : 50371
	spell->SetUnitTarget( context->in_Caller );
	spell->Heal( toheal );
	SpellPool.PooledDelete( spell );
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

/*
void PH_53136( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;
	//hardcoded in spell desc :S
	uint32 chance = 25;
	if( context->in_OwnerSpell->Id == 53138 ) //level 2
		chance = 50;
	if( context->in_CastingSpell->NameHash == SPELL_HASH_OBLITERATE )
		chance *= 2;
	if( !Rand( chance ) )
		return; 
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}*/

void PH_51789( ProcHandlerContextShare *context )
{
	context->out_dmg_overwrite[0] = context->in_OwnerSpell->EffectBasePoints[0] + 1;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_50163( ProcHandlerContextShare *context )
{
	//target needs to hold XP or honor. Kinda quick test
	if( !( context->in_Victim && context->in_Caller->getLevel() != PLAYER_LEVEL_CAP && abs( (int32)context->in_Caller->getLevel() - (int32)context->in_Victim->getLevel() ) < 10 ) )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_50181( ProcHandlerContextShare *context )
{
	//target needs to hold XP or honor. Kinda quick test
	if( !( context->in_Victim && context->in_Caller->getLevel() != PLAYER_LEVEL_CAP && abs( (int32)context->in_Caller->getLevel() - (int32)context->in_Victim->getLevel() ) < 10 ) )
		return;
	context->out_dmg_overwrite[0] = (context->in_OwnerSpell->EffectBasePoints[0] + 1) * context->in_Caller->GetUInt32Value(UNIT_FIELD_MAXHEALTH) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_51460( ProcHandlerContextShare *context )
{
	//need auto attacks = normal phisical attacks
	if( context->in_CastingSpell != NULL )
		return;
	context->out_dmg_overwrite[0] = (context->in_OwnerSpell->EffectBasePoints[0] + 1) * ( context->in_dmg - context->in_abs ) / 100;
	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_50526( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	float proc_chance = context->in_Caller->GetFloatValue( PLAYER_CRIT_PERCENTAGE );
	if( Rand( proc_chance ) == false )
		return;
	context->out_dmg_overwrite[0] = (context->in_OwnerSpell->EffectBasePoints[0] + 1) * ( context->in_dmg - context->in_abs ) / 100;
	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_50536( ProcHandlerContextShare *context )
{
	//we need the damaging death coil not the healing one
	if( context->in_Caller == context->in_Victim )
		return;
	if( context->in_Caller->IsPlayer() == false )
		return;
	context->out_dmg_overwrite[0] = (context->in_OwnerSpell->EffectBasePoints[0] + 1) * ( context->in_dmg - context->in_abs ) / 100;
	if( context->out_dmg_overwrite[0] <= 0 || context->out_dmg_overwrite[0] > 5000 )
		return;
	//talk about hardcoded shit
	if( SafePlayerCast(context->in_Caller)->HasGlyphWithID( GLYPH_DEATHKNIGHT_UNHOLY_BLIGHT ) )
		context->out_dmg_overwrite[0] += context->out_dmg_overwrite[0] * 40 / 100;	
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_40471( ProcHandlerContextShare *context )
{
	uint32 spellId;
	if( context->in_CastingSpell == NULL )
		return;
	else if( context->in_CastingSpell->NameHash == SPELL_HASH_JUDGEMENT_OF_WISDOM ||
		context->in_CastingSpell->NameHash == SPELL_HASH_JUDGEMENT_OF_JUSTICE ||
		context->in_CastingSpell->NameHash == SPELL_HASH_JUDGEMENT_OF_LIGHT)
		spellId = 40472;
	else if( context->in_CastingSpell->NameHash == SPELL_HASH_FLASH_OF_LIGHT ||
		context->in_CastingSpell->NameHash == SPELL_HASH_HOLY_LIGHT )
		spellId = 40471;
	else 
		return; //not good for us
	SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_57319( ProcHandlerContextShare *context )
{
	uint32 spellId;
	if( context->in_Victim->GetPowerType() == POWER_TYPE_RAGE )
		spellId = 57320;
	else if( context->in_Victim->GetPowerType() == POWER_TYPE_RUNIC_POWER )
		spellId = 57321;
	else 
		return; //not good for us
	SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init( context->in_Caller, spellInfo ,true, NULL );
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_Victim->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_67371( ProcHandlerContextShare *context )
{
	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init( context->in_Caller, spellInfo ,true, NULL );
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_67696( ProcHandlerContextShare *context )
{
	//needs beneficial spell
	if( !context->in_CastingSpell || IsSpellBenefic(context->in_CastingSpell) == false )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_64713( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell || IsSpellHarmfull(context->in_CastingSpell) == false )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_67772( ProcHandlerContextShare *context )
{
	uint32 spellId = context->in_event->spellId;
	//we choose spell based on atribute
	if( context->in_Caller->GetUInt32Value( UNIT_FIELD_STRENGTH ) > context->in_Caller->GetUInt32Value( UNIT_FIELD_AGILITY ) )
		spellId = 67773;
	SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init( context->in_Caller, spellInfo ,true, NULL );
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_67703( ProcHandlerContextShare *context )
{
	uint32 spellId = context->in_event->spellId;
	//we choose spell based on atribute
	if( context->in_Caller->GetUInt32Value( UNIT_FIELD_STRENGTH ) > context->in_Caller->GetUInt32Value( UNIT_FIELD_AGILITY ) )
		spellId = 67708;
	SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init( context->in_Caller, spellInfo ,true, NULL );
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	SpellCastTargets targets2( context->in_Caller->GetGUID() ); //no target so spelltargeting will get an injured party member
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_67713( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell || (context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) == 0 )
		return;
	uint32 spellId = context->in_event->spellId;
	//You gain a Mote of Flame each time you cause a damaging spell critical strike.  When you reach $s1 Motes, they will release, firing a Pillar of Flame for $67714s1 damage.  Mote of Flame cannot be gained more often than once every 2 sec.
	if( context->in_Caller->CountAura( spellId ) == context->in_OwnerSpell->EffectBasePoints[0] )
	{
		context->in_Caller->RemoveAllAuras( spellId, 0 );
		spellId = 67714;
		SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
		Spell *spell = SpellPool.PooledNew();
		spell->Init(context->in_Caller, spellInfo ,true, NULL);
		spell->ProcedOnSpell = context->in_CastingSpell;
		spell->pSpellId = context->in_OwnerSpell->Id;
		SpellCastTargets targets2( context->in_Victim->GetGUID() ); //no target so spelltargeting will get an injured party member
		spell->prepare(&targets2);
		context->in_event->LastTrigger = getMSTime(); // consider it triggered
		return;
	}
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_67759( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell || (context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) == 0 )
		return;
	uint32 spellId = context->in_event->spellId;
	//You gain a Mote of Flame each time you cause a damaging spell critical strike.  When you reach $s1 Motes, they will release, firing a Pillar of Flame for $67714s1 damage.  Mote of Flame cannot be gained more often than once every 2 sec.
	if( context->in_Caller->CountAura( spellId ) == context->in_OwnerSpell->EffectBasePoints[0] )
	{
		context->in_Caller->RemoveAllAuras( spellId, 0 );
		spellId = 67760;
		SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
		Spell *spell = SpellPool.PooledNew();
		spell->Init(context->in_Caller, spellInfo ,true, NULL);
		spell->ProcedOnSpell = context->in_CastingSpell;
		spell->pSpellId = context->in_OwnerSpell->Id;
		SpellCastTargets targets2( context->in_Victim->GetGUID() ); //no target so spelltargeting will get an injured party member
		spell->prepare(&targets2);
		context->in_event->LastTrigger = getMSTime(); // consider it triggered
		return;
	}
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_64569( ProcHandlerContextShare *context )
{
	if( context->in_Caller->GetHealthPct() >= 35 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_50895( ProcHandlerContextShare *context )
{
	context->out_dmg_overwrite[0] = ( ( context->in_dmg - context->in_abs ) *  (context->in_OwnerSpell->EffectBasePoints[0] + 1 )) / 100;	//just proc a periodic DMG on target with fixed value. Note that spell ID is wrong
	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_2054( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell || (context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) == 0 || ( context->in_CastingSpell->School != SCHOOL_SHADOW && context->in_CastingSpell->School != SCHOOL_FROST ) )
		return;

	context->out_dmg_overwrite[0] = ( ( context->in_dmg - context->in_abs ) *  (context->in_OwnerSpell->EffectBasePoints[0] + 1 )) / 100;

	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_64801( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;

	context->out_dmg_overwrite[0] = ( context->in_CastingSpell->EffectBasePoints[0] + 1 ) * context->in_CastingSpell->quick_tickcount;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_70802( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
/*	if( CastingSpell->NameHash != SPELL_HASH_EVISCERATE &&
		CastingSpell->NameHash != SPELL_HASH_SLICE_AND_DICE &&
		CastingSpell->NameHash != SPELL_HASH_ENVENOM &&
		CastingSpell->NameHash != SPELL_HASH_DEADLY_THROW &&
		CastingSpell->NameHash != SPELL_HASH_EXPOSE_ARMOR &&
		CastingSpell->NameHash != SPELL_HASH_KIDNEY_SHOT &&
		CastingSpell->NameHash != SPELL_HASH_RUPTURE
		)
		continue; */
	//we need a finishing move for this 
	if(!(context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE) || context->in_Victim==context->in_Caller)
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_71023( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	context->out_dmg_overwrite[0] = (context->in_OwnerSpell->EffectBasePoints[0]+1)*( context->in_dmg - context->in_abs )/100;
	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_70809( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	context->out_dmg_overwrite[0] = (context->in_OwnerSpell->EffectBasePoints[0]+1)*( context->in_dmg - context->in_abs )/100/context->in_OwnerSpell->quick_tickcount;
	if( context->out_dmg_overwrite[0] <= 0 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}
/*
void PH_70799( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_CastingSpell->NameHash == SPELL_HASH_FLASH_HEAL && context->in_Caller->IsPlayer() )
	{
		SafePlayerCast(this)->ClearCooldownForSpell( 47540 ); //pennance
		SafePlayerCast(this)->ClearCooldownForSpell( 53005 ); //pennance
		SafePlayerCast(this)->ClearCooldownForSpell( 53006 ); //pennance
		SafePlayerCast(this)->ClearCooldownForSpell( 53007 ); //pennance
		SafePlayerCast(this)->ClearCooldownForSpell( 34861 ); //Circle of Healing
		SafePlayerCast(this)->ClearCooldownForSpell( 34863 ); //Circle of Healing
		SafePlayerCast(this)->ClearCooldownForSpell( 34864 ); //Circle of Healing
		SafePlayerCast(this)->ClearCooldownForSpell( 34865 ); //Circle of Healing
		SafePlayerCast(this)->ClearCooldownForSpell( 34866 ); //Circle of Healing
		SafePlayerCast(this)->ClearCooldownForSpell( 48088 ); //Circle of Healing
		SafePlayerCast(this)->ClearCooldownForSpell( 48089 ); //Circle of Healing
		RemoveAura( 70799 );
		itr2->LastTrigger = now_in_ms; // consider it triggered
		continue;
	}
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}*/

void PH_70664( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell || context->in_Caller != context->in_Victim )
		return;

	Unit *new_target = NULL;
	//get a random target and also apply the rejuvenation spell
	std::set<Object*>::iterator itr;
	context->in_Caller->AquireInrangeLock(); //make sure to release lock before exit function !
	for( itr = context->in_Caller->GetInRangeSetBegin(); itr != context->in_Caller->GetInRangeSetEnd(); itr++ )
	{
		if( !(*itr)->IsUnit() || !SafeUnitCast((*itr))->isAlive())
			continue;

		//we target stuff that has no full health. No idea if we must fill target list or not :(
		if( (*itr)->GetUInt32Value( UNIT_FIELD_HEALTH ) == (*itr)->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
			continue;

		if( SafeUnitCast(*itr)->HasAura( context->in_CastingSpell->Id ) )
			continue;

		if( !isAttackable(context->in_Caller,(*itr)) )
		{
			new_target = SafeUnitCast(*itr);
			break;
		}
	}
	context->in_Caller->ReleaseInrangeLock();
	if( new_target )
	{
		Spell *spell = SpellPool.PooledNew();
		spell->Init(context->in_Caller, context->in_CastingSpell ,true, NULL);
		SpellCastTargets targets2( new_target->GetGUID() );
		spell->prepare(&targets2);
		context->in_event->LastTrigger = getMSTime(); // consider it triggered
	}
}

void PH_70765( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	if( context->in_Caller->IsPlayer() )
		SafePlayerCast(context->in_Caller)->ClearCooldownForSpell( 53385 ); //divine storm
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_69734( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell )
		return;
	uint32 spellId;
	SpellCastTargets targets2( context->in_Victim->GetGUID() ); //no target so spelltargeting will get an injured party member
	if( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING )
		spellId = 62402;
	else if( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_HEALING )
	{
		spellId = 69734;
		targets2.m_unitTarget = context->in_Caller->GetGUID();
	}
	else
		return;
	SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->pSpellId = context->in_OwnerSpell->Id;
	spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_70657( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == true )
	{
		if( SafePlayerCast(context->in_Caller)->GetFullRuneCount( RUNE_BLOOD ) != 0 ||
			SafePlayerCast(context->in_Caller)->GetFullRuneCount( RUNE_FROST ) != 0 ||
			SafePlayerCast(context->in_Caller)->GetFullRuneCount( RUNE_UNHOLY ) != 0 )
			return;
	}
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_72260( ProcHandlerContextShare *context )
{
	//get saurfang GUID
	Creature *saurfang = context->in_Caller->GetMapMgr()->GetCreature( context->in_event->caster );
	//self heal the mofo
	if( saurfang )
		saurfang->CastSpell( context->in_event->caster, 72260, true );
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_72255( ProcHandlerContextShare *context )
{
	//actaully cast this spell on all players that have 72293
	std::set<Object*>::iterator itr,itr3;
	for( itr3 = context->in_Caller->GetInRangeSetBegin(); itr3 != context->in_Caller->GetInRangeSetEnd(); )
	{
		itr = itr3;
		itr3++;
		if( !((*itr)->IsUnit()) || !SafeUnitCast((*itr))->isAlive() )
			continue;

		if( SafeUnitCast((*itr))->HasNegativeAura( 72293 ) == false )
			continue;
		context->in_Caller->CastSpell( SafeUnitCast((*itr)), 72255, true );
	}
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_55533( ProcHandlerContextShare *context )
{
	if( context->in_Victim == context->in_Caller )
		return;
	context->out_dmg_overwrite[0] = context->in_dmg * (context->in_OwnerSpell->EffectBasePoints[0] + 1) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_48090( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPet() && SafePetCast(context->in_Caller)->GetPetOwner() )
		context->out_dmg_overwrite[0] = (context->in_OwnerSpell->EffectBasePoints[0] + 1) * SafePetCast(context->in_Caller)->GetPetOwner()->GetDamageDoneMod( SCHOOL_SHADOW ) / 100;
	else
		context->out_dmg_overwrite[0] = (context->in_OwnerSpell->EffectBasePoints[0] + 1) * context->in_Caller->GetDamageDoneMod( SCHOOL_SHADOW ) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_54425( ProcHandlerContextShare *context )
{
	context->out_dmg_overwrite[0] = context->in_OwnerSpell->EffectBasePoints[2] + 1;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_48210( ProcHandlerContextShare *context )
{
	SpellCastTargets targets2( context->in_event->caster );
	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	spell->forced_basepoints[0] = context->in_event->created_with_value;
	spell->pSpellId = context->in_OwnerSpell->Id;
	spell->prepare(&targets2);
	context->in_event->deleted = true;
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}
/*
void PH_16953( ProcHandlerContextShare *context )
{
	if( !context->in_CastingSpell || 
		context->in_CastingSpell->Id == 14189 ||
		context->in_CastingSpell->Id == 16953 ||
		context->in_CastingSpell->Id == 16959 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}*/

void PH_20268( ProcHandlerContextShare *context )
{
	uint32 base_mana = context->in_Victim->GetUInt32Value( UNIT_FIELD_BASE_MANA );
	if( base_mana == 0 )
		return; //maybe this is not a caster at all
	SpellEntry *spellInfo = dbcSpell.LookupEntry(context->in_event->spellId );
	context->out_dmg_overwrite[0] = (spellInfo->EffectBasePoints[0] + 1) * base_mana / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_20167( ProcHandlerContextShare *context )
{
	uint32 AP = context->in_Caller->GetAP();
	uint32 SPH = context->in_Caller->GetDamageDoneMod( SCHOOL_HOLY );
	context->out_dmg_overwrite[0] = ( AP + SPH ) * 15 / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_20267( ProcHandlerContextShare *context )
{
	uint32 AP = context->in_Victim->GetAP();
	uint32 SPH = context->in_Victim->GetDamageDoneMod( SCHOOL_HOLY );
	context->out_dmg_overwrite[0] = ( AP + SPH ) * 10 / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_34919( ProcHandlerContextShare *context )
{
	// try to get from ourself the caster of this buff
	Aura *ta = context->in_Caller->FindAuraByNameHash( SPELL_HASH_VAMPIRIC_TOUCH, context->in_Victim->GetGUID() );
	 //ofc we have aura but maybe not from attacker
	if( !ta )
		return;
	Unit *ac = ta->GetUnitCaster();
	if( !ac || ac != context->in_Victim )
		return;
	//now make the orignal caster cast this spell
	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
    Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Victim, spellInfo ,true, NULL);
    SpellCastTargets targets2( context->in_Victim->GetGUID() );
    spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_15290( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == NULL )
		return;//this should not ocur unless we made a fuckup somewhere
	if( context->in_CastingSpell->School != SCHOOL_SHADOW || !( context->in_CastingSpell->c_is_flags & SPELL_FLAG_IS_DAMAGING ) ) //we need damaging spells for this, so we suppose all shadow spells casted on target are dmging spells = Wrong
		return;
	//need single targeting spell dmg and not AOE
	if( context->in_CastingSpell->spell_coef_flags & SPELL_FLAG_AOE_SPELL )
		return;
	context->out_dmg_overwrite[0] = context->in_dmg * ( context->in_OwnerSpell->EffectBasePoints[0] + 1) / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_63654( ProcHandlerContextShare *context )
{
	uint32 spellId;
	if( context->in_Caller->GetPowerType() == POWER_TYPE_RAGE )
		spellId = 63653;
	else if( context->in_Caller->GetPowerType() == POWER_TYPE_RUNIC_POWER )
		spellId = 63652;
	else if( context->in_Caller->GetPowerType() == POWER_TYPE_ENERGY )
		spellId = 63655;
	else return;
	//energize ourself too
	//if( victim != this )
	//	this->CastSpell( victim, 47755, true );
	context->in_Caller->Energize( context->in_Victim, 47755, context->in_Victim->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) * 25 / 1000, POWER_TYPE_MANA );
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_974( ProcHandlerContextShare *context )
{
	SpellEntry *spellInfo = dbcSpell.LookupEntry(context->in_event->spellId );
	Spell *spell = SpellPool.PooledNew();
	spell->Init(context->in_Caller, spellInfo ,true, NULL);
	spell->ProcedOnSpell = context->in_CastingSpell;
	//Spell *spell = new Spell(this,spellInfo,false,0,true,false);
	spell->pSpellId=context->in_event->spellId;
	spell->SpellEffectDummy(0);
	SpellPool.PooledDelete( spell );
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_50424( ProcHandlerContextShare *context )
{
	if( context->in_Victim && context->in_Victim != context->in_Caller )
	{
		SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
		context->out_dmg_overwrite[0] = (spellInfo->EffectBasePoints[0] + 1) * context->in_Victim->GetUInt32Value(UNIT_FIELD_MAXHEALTH) / 100;
		//some bug protection, no way for this to heal like owner has 100k health
		if( context->out_dmg_overwrite[0] > 1200 )
			context->out_dmg_overwrite[0] = 1200;
	}
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_34650( ProcHandlerContextShare *context )
{
	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
    Spell *spell = SpellPool.PooledNew();
	spell->Init( context->in_Caller, spellInfo ,true, NULL);
    SpellCastTargets targets2( context->in_Caller->GetUInt64Value( UNIT_FIELD_CREATEDBY ) );
    spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

void PH_50454( ProcHandlerContextShare *context )
{
	//we restore master health 
//	dmg_overwrite = ( dmg - Abs ) * 150 / 100;	//wowhead formula
	int32 dmg_overwrite = ( context->in_dmg - context->in_abs ) * 15 / 100;	//wowhead formula
	if( dmg_overwrite <= 0 )
		return;
	//sanity check
	if( dmg_overwrite > 500 )
		return;	
	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
    Spell *spell = SpellPool.PooledNew();
	spell->Init( context->in_Caller, spellInfo ,true, NULL);
	spell->forced_basepoints[0] = dmg_overwrite;
    SpellCastTargets targets2( context->in_Caller->GetUInt64Value( UNIT_FIELD_CREATEDBY ) );
    spell->prepare(&targets2);
	context->in_event->LastTrigger = getMSTime(); // consider it triggered
}

//dazed can come from a lot of spell !
void PH_50411( ProcHandlerContextShare *context )
{
	if( context->in_OwnerSpell->NameHash == SPELL_HASH_BRAMBLES )
	{
		//only daze if we have barkskin aura on us
		if( context->in_events_filter_flags & PROC_ON_MELEE_ATTACK_VICTIM )
		{
			if( Rand( context->in_OwnerSpell->EffectBasePoints[2] + 1 + 10 ) == false )
				return;
			if( context->in_Caller->HasPassiveAurasWithNameHash( SPELL_HASH_BARKSKIN ) == 0 )
				return;
			context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
		}
		if( context->in_events_filter_flags & PROC_ON_CAST_SPELL )
		{
			if( context->in_CastingSpell == NULL || context->in_CastingSpell->NameHash != SPELL_HASH_FORCE_OF_NATURE )
				return;
			//find our treants and cast the boost spell on them
			std::list<uint64>::iterator gitr,gitr2;
			for( gitr2 = context->in_Caller->m_guardians.begin(); gitr2 != context->in_Caller->m_guardians.end();)
			{
				gitr = gitr2;
				gitr2++;
				Creature *tc = context->in_Caller->GetMapMgr()->GetCreature( (*gitr) );
				if( tc == NULL )
				{
					context->in_Caller->m_guardians.erase( gitr );
					continue;
				}
				if( tc->GetEntry() == 1964 )
					tc->CastSpell( tc, 50419, true );
			}
			return;
		}
	}
}

void PH_30824( ProcHandlerContextShare *context )
{
	SpellEntry *spellInfo = dbcSpell.LookupEntry( context->in_event->spellId );
	context->out_dmg_overwrite[0] = (spellInfo->EffectBasePoints[0] + 1) * context->in_Caller->GetAP() / 100;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_47223( ProcHandlerContextShare *context )
{
	//should proc only on imp fire spell criticals
	if( context->in_Caller->IsCreature() == false )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_63165( ProcHandlerContextShare *context )
{
	//needs target to have less then x% health
	if( context->in_Victim->GetHealthPct() > context->in_OwnerSpell->EffectBasePoints[1] + 1 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_15571( ProcHandlerContextShare *context )
{
	//do not proc without dmg
	if( context->in_dmg - context->in_abs <= 0 )
		return;
	//do not proc if this is a dot
	if( context->in_CastingSpell && context->in_CastingSpell->quick_tickcount > 1 )
		return;
	context->out_handler_result = PROC_HANDLER_CONTINUE_EXECUTION;
}

void PH_50384( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsUnit() == false )
		return;
	//this is effect apply
	int32 val = 0;
	if( ( context->in_events_filter_flags & PROC_ON_CAST_SPELL ) != 0 && context->in_event->custom_holder == 0 )
	{
		context->in_event->custom_holder = (void*)1;	//make sure to apply and remove effect only once in case chained cast is used for "presence"
		context->in_event->created_with_value = context->in_Caller->GetUInt32Value( UNIT_FIELD_STAMINA ) * (context->in_OwnerSpell->EffectBasePoints[0] + 1)/100;
		val = context->in_event->created_with_value;
	}
	else if( ( context->in_events_filter_flags & PROC_ON_AURA_REMOVE ) != 0 && context->in_event->custom_holder != 0 )
	{
		context->in_event->custom_holder = 0;	//make sure to apply and remove effect only once in case chained cast is used for "presence"
		val = -context->in_event->created_with_value;
	}

	if( val )
	{
		if( context->in_Caller->IsPlayer() )
		{
			SafePlayerCast( context->in_Caller )->FlatStatModPos[ STAT_STAMINA ] += val;
			SafePlayerCast( context->in_Caller )->CalcStat( STAT_STAMINA );
			SafePlayerCast( context->in_Caller )->UpdateStats();
			SafePlayerCast( context->in_Caller )->UpdateChances();
		}
		else if( context->in_Caller->IsCreature() )
		{
			SafeCreatureCast( context->in_Caller )->FlatStatMod[ STAT_STAMINA ] += val;
			SafeCreatureCast( context->in_Caller )->CalcStat( STAT_STAMINA );
		}
	}
	//!! do not continue execution cause this is a self proc -> would loop to "infinit"
}

void PH_50365( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsUnit() == false )
		return;
	//this is effect apply
	static const uint32 blood_presence_id = 48266;
	if( ( context->in_events_filter_flags & PROC_ON_CAST_SPELL ) != 0 && context->in_event->custom_holder == 0 )
	{
		context->in_event->custom_holder = (void*)1;	//make sure to apply and remove effect only once in case chained cast is used for "presence"
		ProcTriggerSpell *pts = new ProcTriggerSpell( dbcSpell.LookupEntryForced( blood_presence_id ) );
		pts->procChance = context->in_OwnerSpell->procChance;
		pts->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK | PROC_ON_SPELL_HIT;
		pts->spellId = 50475;
		pts->created_with_value = context->in_OwnerSpell->EffectBasePoints[0] + 1;	//max health pct restore
		pts->caster = context->in_Caller->GetGUID();		//orginally blizz made it so beacon registers this cast
		context->in_Caller->m_procSpells.push_front(pts);	//if caster casts a healing spell
	}
	//this is the aura remove proc and also our proc event remove
	else if( ( context->in_events_filter_flags & PROC_ON_AURA_REMOVE ) != 0 && context->in_event->custom_holder != 0 )
	{
		context->in_event->custom_holder = 0;	//make sure to apply and remove effect only once in case chained cast is used for "presence"
		uint64 tcasterguid = context->in_Caller->GetGUID();
		CommitPointerListNode<ProcTriggerSpell> *itr;
		for(itr = context->in_Caller->m_procSpells.begin();itr != context->in_Caller->m_procSpells.end();itr = itr->Next() )
			if(itr->data->origId == blood_presence_id && itr->data->caster == tcasterguid && !itr->data->deleted)
			{
				itr->data->deleted = true;
				break;
			}
	}
	//!! do not continue execution cause this is a self proc -> would loop to "infinit"
}

void PH_49772( ProcHandlerContextShare *context )
{
	if( context->in_Caller->IsPlayer() == false )
		return;
	//dam it, in unholly presence increase rune regen
	if( context->in_CastingSpell->NameHash == SPELL_HASH_UNHOLY_PRESENCE )
	{
		context->in_Caller->RemoveAura( 63622 );
		if( ( context->in_events_filter_flags & PROC_ON_CAST_SPELL ) != 0 )
		{
			SpellEntry *spellInfo = dbcSpell.LookupEntry( 63622 );
			Spell *spell = SpellPool.PooledNew();
			spell->Init( context->in_Caller, spellInfo ,true, NULL);
			spell->forced_basepoints[0] = context->in_OwnerSpell->EffectBasePoints[1] + 1;
			spell->forced_basepoints[1] = context->in_OwnerSpell->EffectBasePoints[1] + 1;
			spell->forced_basepoints[2] = context->in_OwnerSpell->EffectBasePoints[1] + 1;
			SpellCastTargets targets2( context->in_Caller->GetGUID() );
			spell->prepare(&targets2);
		}
	}
	else
	{
		//this is effect apply
		if( ( context->in_events_filter_flags & PROC_ON_CAST_SPELL ) != 0 && context->in_event->custom_holder == 0 )
		{
			Modifier *tm = new Modifier;
			tm->m_amount = context->in_OwnerSpell->EffectBasePoints[0] + 1;	//retain X speed
			context->in_event->custom_holder = (void*)tm;	//make sure to apply and remove effect only once in case chained cast is used for "presence"
			context->in_Caller->speedIncreaseMap.push_front( tm );
		}
		//this is the aura remove proc and also our proc event remove
		else if( ( context->in_events_filter_flags & PROC_ON_AURA_REMOVE ) != 0 && context->in_event->custom_holder != 0 )
		{
			context->in_Caller->speedIncreaseMap.remove( (Modifier *)context->in_event->custom_holder );
			delete context->in_event->custom_holder;
			context->in_event->custom_holder = NULL;
		}
		if( context->in_Caller->GetSpeedIncrease() )
			context->in_Caller->UpdateSpeed();
	}
	//!! do not continue execution cause this is a self proc -> would loop to "infinit"
}

void PH_65661( ProcHandlerContextShare *context )
{
	if( context->in_CastingSpell == false )
		return;
	uint32 spell_id = 0;
	if( context->in_CastingSpell->NameHash == SPELL_HASH_DEATH_STRIKE )
		spell_id = 66953;	//blizz implemented this in more then 1 way. He has some specially made spells but combat log merges dmg...
	else if( context->in_CastingSpell->NameHash == SPELL_HASH_OBLITERATE )
		spell_id = 66974;
	else if( context->in_CastingSpell->NameHash == SPELL_HASH_PLAGUE_STRIKE )
		spell_id = 66992;
	else if( context->in_CastingSpell->NameHash == SPELL_HASH_RUNE_STRIKE )
		spell_id = 66217;
	else if( context->in_CastingSpell->NameHash == SPELL_HASH_BLOOD_STRIKE )
		spell_id = 66979;
	else if( context->in_CastingSpell->NameHash == SPELL_HASH_FROST_STRIKE )
		spell_id = 66962;
	if( spell_id )
	{
		SpellEntry *spellInfo = dbcSpell.LookupEntry( spell_id );
		Spell *spell = SpellPool.PooledNew();
		spell->Init( context->in_Caller, spellInfo ,true, NULL);
		SpellCastTargets targets2( context->in_Victim->GetGUID() );
		spell->pSpellId = context->in_event->spellId;
		spell->prepare( &targets2 );
		context->in_event->LastTrigger = getMSTime(); // consider it triggered
	}
	//!! do not continue execution cause this is a self proc -> would loop to "infinit"
}

void RegisterProcHandlers()
{
	SpellEntry *sp;
	//Threat of Thassarian
	REGISTER_HANDLER( 65661 );
	//Improved Unholy Presence
	REGISTER_HANDLER( 49772 );
	//Improved Blood Presence
	REGISTER_HANDLER( 50365 );
	//Improved Frost Presence
	REGISTER_HANDLER( 50384 );
	//hunter - Aspect of the Cheetah
	REGISTER_HANDLER( 15571 );
	//warlock - Decimation
	REGISTER_HANDLER( 63165 );
	REGISTER_SAMEHANDLER( 63167, 63165 );
	//warlock - empowered imp
	REGISTER_HANDLER( 47223 );
	//druid -> Shamanistic Rage
	REGISTER_HANDLER( 30824 );
	//druid -> Brambles
	REGISTER_HANDLER( 50411 );
	//Health Leech -> DK bloodworms
	REGISTER_HANDLER( 50454 );
	//Mana Leech -> priest shadowfiend
	REGISTER_HANDLER( 34650 );
	//DK - Mark of Blood
	REGISTER_HANDLER( 50424 );
	//shaman - Earth Shield
	REGISTER_HANDLER( 974 );
	REGISTER_SAMEHANDLER( 32593, 974 );
	REGISTER_SAMEHANDLER( 32594, 974 );
	//priest - Rapture
	REGISTER_HANDLER( 63654 );
	//priest - Vampiric Embrace
	REGISTER_HANDLER( 15290 );
	//priest - Vampiric Touch
	REGISTER_HANDLER( 34919 );
	//Judgement of Light -> a chance of healing the attacker for ${0.10*$SPH+0.10*$AP}.
	REGISTER_HANDLER( 20267 );
	//seal of Light -> a chance of healing paladin for ${0.15*$AP+0.15*$SPH}
	REGISTER_HANDLER( 20167 );
	//Judgement of Wisdom -> restore pct mana of the attacker = mob is victim and ex hunter attacks
	REGISTER_HANDLER( 20268 );
	//Primal Fury - cat form
	REGISTER_HANDLER( 16953 );
	//Primal Fury - bear and direbear form
	REGISTER_HANDLER( 16959 );
	//warlock Haunt
	REGISTER_HANDLER( 48210 );
	REGISTER_SAMEHANDLER( 50091, 48210 );
	//warlock Improved Felhunter
	REGISTER_HANDLER( 54425 );
	//Demonic Pact
	REGISTER_HANDLER( 48090 );
	//Glyph of Healing Wave
	REGISTER_HANDLER( 55533 );
	//Mark of the Fallen Champion -> dmg proc
	REGISTER_HANDLER( 72255 );
	//Mark of the Fallen Champion -> heal proc
	REGISTER_HANDLER( 72260 );
	//Item - Death Knight T10 Melee 4P Bonus
	REGISTER_HANDLER( 70657 );
	//Purified Shard of the Scale - Equip Effect
	REGISTER_HANDLER( 69734 );
	//Shiny Shard of the Scale - Equip Effect
	REGISTER_SAMEHANDLER( 62402, 69734 );
	//Item - Paladin T10 Retribution 2P Bonus
	REGISTER_HANDLER( 70765 );
	//Item - Priest T10 Healer 2P Bonus
	REGISTER_HANDLER( 70664 );
	//Item - Priest T10 Healer 4P Bonus
//	REGISTER_HANDLER( 70799 );
	//Item - Priest T10 Healer 2P Bonus
	REGISTER_HANDLER( 70809 );
	//Item - Druid T10 Balance 4P Bonus
	REGISTER_HANDLER( 71023 );
	//Item - Rogue T10 4P Bonus
	REGISTER_HANDLER( 70802 );
	//Item - Druid T8 Restoration 4P Bonus
	REGISTER_HANDLER( 64801 );
	//item - Frozen Shadoweave
	REGISTER_HANDLER( 2054 );
	//Item - Shaman T8 Elemental 4P Bonus
	REGISTER_HANDLER( 50895 );
	//item : Enchant Weapon - Blood Draining
	REGISTER_HANDLER( 64569 );
	REGISTER_SAMEHANDLER( 75477, 64569 );
	REGISTER_SAMEHANDLER( 75480, 64569 );
	//Shard of Flame
	REGISTER_HANDLER( 67759 );
	//Mote of Flame
	REGISTER_HANDLER( 67713 );
	//Paragon - ver 2
	REGISTER_HANDLER( 67772 );
	//Paragon - ver 1
	REGISTER_HANDLER( 67703 );
	//Flame of the Heavens
	REGISTER_HANDLER( 64713 );
	//Volatile Power
	REGISTER_SAMEHANDLER( 67743, 64713 );
	//Elusive Power
	REGISTER_SAMEHANDLER( 67669, 64713 );
	// trinket spells like deat's verdic : 6 TOC items
	REGISTER_HANDLER( 67696 );
	// paladin - Item - Paladin T9 Retribution Relic (Seal of Vengeance)
	REGISTER_HANDLER( 67371 );
	// paladin - blessing of sanctuary
	REGISTER_HANDLER( 57319 );
	// Enduring Light
	REGISTER_HANDLER( 40471 );
	// Deathknight - Unholy Blight
	REGISTER_HANDLER( 50536 );
	// Deathknight - Wandering Plague
	REGISTER_HANDLER( 50526 );
	// DK - Necrosis
	REGISTER_HANDLER( 51460 );
	// DK - Vendetta
	REGISTER_HANDLER( 50181 );
	// DK - Butchery
	REGISTER_HANDLER( 50163 );
	// DK - Blade Barrier
	REGISTER_HANDLER( 51789 );
	// DK - Abomination's Might
//	REGISTER_HANDLER( 53136 );
	// DK - Blood Presence
	REGISTER_HANDLER( 50475 );
	// DK - Acclimation
	REGISTER_HANDLER( 50362 );
	// DK - killing machine only procs on normal melee attacks and not abbilities
	REGISTER_HANDLER( 51124 );
	// DK - Blood-Caked Blade - also melee only
	REGISTER_SAMEHANDLER( 50463, 51124);
	//Darkmoon Card: Greatness
	REGISTER_HANDLER( 60229);
	//item - Eye of the Broodmother
	REGISTER_HANDLER( 65006);
	//item - Val'anyr Hammer of Ancient Kings
	REGISTER_HANDLER( 64411);
	//Living Seed the heal proc
	REGISTER_HANDLER( 48503);
	//Living Seed
	REGISTER_HANDLER( 48504);
	//druid - Nature's Grace
	REGISTER_HANDLER( 16886);
	//using a mana gem grants you 225 spell damage for 15 sec
	REGISTER_HANDLER( 37445);
	//http://www.wowhead.com/?item=32492 Ashtongue Talisman of Lethality
	REGISTER_HANDLER( 40461);
	//http://www.wowhead.com/?item=32490 Ashtongue Talisman of Acumen
	REGISTER_HANDLER( 40440);
	//http://www.wowhead.com/?item=32490 Ashtongue Talisman of Acumen
	REGISTER_HANDLER( 40441);
	//Rejuvenation has a 25% chance to grant up to 210 healing for 8 sec
	REGISTER_HANDLER( 40446);
	//Starfire has a 25% chance to grant up to 150 spell damage for 8 sec
	REGISTER_HANDLER( 40445);
	//http://www.wowhead.com/?item=32486 Ashtongue Talisman of Equilibrium
	REGISTER_HANDLER( 40452);
	//http://www.wowhead.com/?item=32496  Memento of Tyrande
	REGISTER_HANDLER( 37656);
	//Epiphany :Each spell you cast can trigger an Epiphany, increasing your mana regeneration by 24 for 30 sec.
	REGISTER_SAMEHANDLER( 28804, 37656);
	//Judgements of the Just
	REGISTER_HANDLER( 37196);
	REGISTER_SAMEHANDLER( 43838, 37196);
	REGISTER_SAMEHANDLER( 68055, 37196);
	//item - Shadowflame Hellfire and RoF
	REGISTER_HANDLER( 37378 );
	//Item - Anger Capacitor
	REGISTER_HANDLER( 71432 );
	//Item - Shadowmourne Legendary
	REGISTER_HANDLER( 71905 );
	//SETBONUSES
	REGISTER_HANDLER( 37379 );
	//druid - Eclipse - part 1
	REGISTER_HANDLER( 48517 );
	//druid - Eclipse - part 2
	REGISTER_HANDLER( 48518 );
	//Freeze
	REGISTER_HANDLER( 63685 );
	//shaman - Lightning Overload
	REGISTER_HANDLER( 30675 );
	//shaman - Earth Shield
	REGISTER_HANDLER( 379 );
	//HoTs on Heals - //periodic healing spell
	REGISTER_HANDLER( 38324 );
	//Eyes of Twilight - //direct healing spell
	REGISTER_HANDLER( 75493);
	//Eyes of Twilight
	REGISTER_SAMEHANDLER( 75494, 75493);
	//Augment Pain - //periodic damaging spell
	REGISTER_HANDLER( 45055 );
	//Item - Icecrown 25 Heroic Caster Trinket 2
	REGISTER_SAMEHANDLER( 71636, 45055);
	//Item - Icecrown 25 Normal Caster Trinket 2
	REGISTER_SAMEHANDLER( 71605, 45055);
	//Power of the Great Ones - all damaging
	REGISTER_HANDLER( 53372 );
	//Charged
	REGISTER_SAMEHANDLER( 37234, 53372);
	//Energized
	REGISTER_SAMEHANDLER( 37214, 53372);
	//Relentlessness
	REGISTER_SAMEHANDLER( 37601, 53372);
	//http://www.wowhead.com/?item=32488 Ashtongue Talisman of Insight
	REGISTER_SAMEHANDLER( 40483, 53372);
	//Talisman of Troll Divinity	- need to make direct casts !
	REGISTER_HANDLER( 60518 );
	//Charm of the Witch Doctor
	REGISTER_SAMEHANDLER( 43821, 60518);
	//Healing Discount  - all healing
	REGISTER_SAMEHANDLER( 37706, 60518);
	//item - Band of the Eternal Restorer
	REGISTER_SAMEHANDLER( 35087, 60518);
	//Vial of the Sunwel
	REGISTER_SAMEHANDLER( 45062, 60518);
	//Wave Trance
	REGISTER_SAMEHANDLER( 39950, 60518);
	//Ribbon of Sacrifice
	REGISTER_SAMEHANDLER( 38333, 60518);
	//Spark of Life
	REGISTER_HANDLER( 60520 );
	//Item - Druid T9 Feral Relic (Lacerate, Swipe, Mangle, and Shred)
	REGISTER_HANDLER( 67354 );
	//Spell Haste Trinket http://www.wowhead.com/?item=28190 scarab of the infinite cicle
	REGISTER_HANDLER( 33370 );
	//Charm of Mighty Mojo
	REGISTER_SAMEHANDLER( 43819, 33370);
	//Item - Chamber of Aspects 25 Nuker Trinket
	REGISTER_SAMEHANDLER( 75466, 33370);
	//Item - Chamber of Aspects 25 Heroic Nuker Trinket
	REGISTER_SAMEHANDLER( 75473, 33370);
	//Deadly Precision - direct cast and not over time
	REGISTER_HANDLER( 71564 );
	//Item - Icecrown Reputation Ring Caster Trigger
	REGISTER_HANDLER( 72416 );
	//Item - Icecrown 25 Normal Caster Weapon Proc
	REGISTER_SAMEHANDLER( 71843, 72416);
	//Volatile Power
	REGISTER_SAMEHANDLER( 67735, 72416);
	//Forgotten Knowledge
	REGISTER_SAMEHANDLER( 38317, 72416);
	//Item - Icecrown 25 Normal Caster Trinket 1 Base
	REGISTER_SAMEHANDLER( 71601, 72416);
	//Item - Icecrown 25 Heroic Caster Trinket 1 Base
	REGISTER_SAMEHANDLER( 71644, 72416);
	//item - Band of the Eternal Sage
	REGISTER_SAMEHANDLER( 35084, 72416);
	//Item - Icecrown 25 Normal Dagger Proc
	REGISTER_HANDLER( 71881 );
	//Item - Icecrown 25 Heroic Dagger Proc
	REGISTER_HANDLER( 71888 );
	//Forethought Talisman
	REGISTER_HANDLER( 60530 );
	//Item - Icecrown Reputation Ring Healer Trigger
	REGISTER_HANDLER( 72418 );
	//Item - Paladin T10 Holy Relic (Holy Shock)
	REGISTER_SAMEHANDLER( 71192, 72418);
	//Escalating Power
	REGISTER_SAMEHANDLER( 67739, 72418);
	//Escalating Power
	REGISTER_SAMEHANDLER( 67723, 72418);
	//Coliseum 5 Healer Trinket
	REGISTER_SAMEHANDLER( 67666, 72418);
	//Item - Icecrown 25 Normal Healer Trinket 2
	REGISTER_HANDLER( 71610 );
	//Item - Icecrown 25 Heroic Healer Trinket 2
	REGISTER_SAMEHANDLER( 71641, 71610);
	//Item - Icecrown Dungeon Healer Trinket
	REGISTER_HANDLER( 71566 );
	//Bonus Healing
	REGISTER_HANDLER( 40972 );
	//Item - Icecrown 25 Normal Tank Trinket 1
	REGISTER_HANDLER( 71633 );
	REGISTER_SAMEHANDLER( 71639, 71633);
	REGISTER_SAMEHANDLER( 52419, 71633);
	REGISTER_SAMEHANDLER( 45058, 71633);
	//Item - Icecrown 25 Normal Melee Trinket
	REGISTER_HANDLER( 71519 );
	//Death Knight - Spell Deflection
	REGISTER_HANDLER( 51911 );
	//DK - Rime
	REGISTER_HANDLER( 59052 );
	//paladin - beacon of light
	REGISTER_HANDLER( 53654 );
	//paladin - Blessed Life
	REGISTER_HANDLER( 31828 );
	//paladin - Eye for an Eye
	REGISTER_HANDLER( 25997 );
	//paladin - Spiritual Attunement
	REGISTER_HANDLER( 31786 );
	//Paladin - Sheath of Light
	REGISTER_HANDLER( 54203 );
	//Paladin - Righteous Vengeance
	REGISTER_HANDLER( 61840 );
	//Paladin - Judgements of the Wise
	REGISTER_HANDLER( 31930 );
	//Paladin - Illumination
	REGISTER_HANDLER( 20272 );
	//Paladin - Reckoning
	REGISTER_HANDLER( 20178 );
	//Paladin - Guarded by The Light
	REGISTER_HANDLER( 63521 );
	//Paladin - Ardent Defender - part that absorbs if HP is less then 35%
	REGISTER_HANDLER( 66233 );
	//Paladin - Ardent Defender - part that heals if HP it is a killer blow
	REGISTER_HANDLER( 66235 );
	//rogue - combat potency
	REGISTER_HANDLER( 35542 );
	REGISTER_SAMEHANDLER( 35545, 35542);
	REGISTER_SAMEHANDLER( 35546, 35542);
	REGISTER_SAMEHANDLER( 35547, 35542);
	REGISTER_SAMEHANDLER( 35548, 35542);
	//priest - Grace 
	REGISTER_HANDLER( 47930 );
	//priest - Reflective Shield 
	REGISTER_HANDLER( 33619 );
	//priest - Serendipity
/*	REGISTER_HANDLER( 63731 );
	REGISTER_SAMEHANDLER( 63734, 63731);
	REGISTER_SAMEHANDLER( 63735, 63731);*/
	//priest - Divine Aegis
	REGISTER_HANDLER( 47753 );
	//Piercing Shots
	REGISTER_HANDLER( 63468 );
	//Hunter - Thrill of the Hunt
	REGISTER_HANDLER( 34720 );
	//hunter - aspect of the viper
	REGISTER_HANDLER( 34075 );
	//druid - Savage Defense
	REGISTER_HANDLER( 62606 );
	//Hunter - frost trap should trigger at the location of the trap and not the target
	REGISTER_HANDLER( 13810 );
	//druid - King of the Jungle 1
	REGISTER_HANDLER( 51185 );
	//druid - King of the Jungle 2
	REGISTER_HANDLER( 51178 );
	//mage - Master of Elements
	REGISTER_HANDLER( 29077 );
	//mage - Improved Blizzard
	REGISTER_HANDLER( 12484 );
	REGISTER_SAMEHANDLER( 12485, 12484);
	REGISTER_SAMEHANDLER( 12486, 12484);
	// Brain Freeze
	REGISTER_HANDLER( 57761 );
	// frostbite
	REGISTER_HANDLER( 12494 );
	// fingers of frost
	REGISTER_SAMEHANDLER( 44544, 12494);
	REGISTER_SAMEHANDLER( 74396, 12494);
	// Burning Determination
	REGISTER_HANDLER( 54748 );
	// Ancestral Awakening
	REGISTER_HANDLER( 52752 );
	// mage - Arcane Concentration
	REGISTER_HANDLER( 12536 );
	// Priest - blackout
//	REGISTER_HANDLER( 15269 );
	// Priest - Shadowguard
	REGISTER_HANDLER( 32861 );
	REGISTER_SAMEHANDLER( 38379, 32861);
/*	// rogue - Find Weakness
	REGISTER_HANDLER( 31234 );
	REGISTER_SAMEHANDLER( 31235, 31234);
	REGISTER_SAMEHANDLER( 31236, 31234);
	REGISTER_SAMEHANDLER( 31237, 31234);
	REGISTER_SAMEHANDLER( 31238, 31234);*/
	// rogue - Overkill
	REGISTER_HANDLER( 58427 );
	// rogue - Relentless Strikes
	REGISTER_HANDLER( 14181 );
	// rogue - Ruthlessness
	REGISTER_HANDLER( 14157 );
	// shaman - windfury weapon
	REGISTER_HANDLER( 33010 );
	// Clearcasting
	REGISTER_HANDLER( 16246 );
	// Flametongue Weapon
	REGISTER_HANDLER( 8026 );
	REGISTER_SAMEHANDLER( 8028, 8026);
	REGISTER_SAMEHANDLER( 8029, 8026);
	REGISTER_SAMEHANDLER( 10445, 8026);
	REGISTER_SAMEHANDLER( 16343, 8026);
	REGISTER_SAMEHANDLER( 16344, 8026);
	REGISTER_SAMEHANDLER( 25488, 8026);
	REGISTER_SAMEHANDLER( 58786, 8026);
	REGISTER_SAMEHANDLER( 58787, 8026);
	REGISTER_SAMEHANDLER( 58788, 8026);
	// shaman - Ancestral Fortitude
	REGISTER_HANDLER( 16177 );
	REGISTER_SAMEHANDLER( 16236, 16177);
	REGISTER_SAMEHANDLER( 16237, 16177);
	// shaman - Improved Stormstrike
	REGISTER_HANDLER( 63375 );
	// shaman - Elemental Devastation
	REGISTER_HANDLER( 29177 );
	REGISTER_SAMEHANDLER( 29178, 29177);
	REGISTER_SAMEHANDLER( 30165, 29177);
	// shaman - Item - Shaman T10 Enhancement 4P Bonus
	REGISTER_HANDLER( 70831 );
	// Astral Shift
	REGISTER_HANDLER( 52179 );
	// Earthliving
	REGISTER_HANDLER( 51945 );
	REGISTER_SAMEHANDLER( 51990, 51945);
	REGISTER_SAMEHANDLER( 51997, 51945);
	REGISTER_SAMEHANDLER( 51998, 51945);
	REGISTER_SAMEHANDLER( 51999, 51945);
	REGISTER_SAMEHANDLER( 52000, 51945);
	// priest - Blessed Recovery
	REGISTER_HANDLER( 27813 );
	REGISTER_SAMEHANDLER( 27817, 27813);
	REGISTER_SAMEHANDLER( 27818, 27813);
	// priest - Inspiration
	REGISTER_HANDLER( 15363 );
	REGISTER_SAMEHANDLER( 14893, 15363);
	REGISTER_SAMEHANDLER( 15357, 15363);
	REGISTER_SAMEHANDLER( 15359, 15363);
	// priest - Improved Shadowform
	REGISTER_HANDLER( 15473 );
	// priest - Shadow Weaving
	REGISTER_HANDLER( 15258 );
	// priest - prayer of mending
	REGISTER_HANDLER( 41637 );
	// priest - Empowered Renew
	REGISTER_HANDLER( 63544 );
	// priest - Improved Devouring Plague
	REGISTER_HANDLER( 63675 );
	// mage - Winter's Chill
	REGISTER_HANDLER( 12579 );
	// mage - Combustion
	REGISTER_HANDLER( 28682 );
	// mage - Incanter's Absorption
	REGISTER_HANDLER( 44413 );
	// mage - Focus Magic
	REGISTER_HANDLER( 54648 );
	// warlock - Soul Leech
	// hunter - Hunting Party
	REGISTER_HANDLER( 57669 );
	// hunter : Noxious Stings
	REGISTER_HANDLER( 53295 );
	// hunter : Improved Aspect of the Hawk
	REGISTER_HANDLER( 6150 );
	// hunter - Rapid Recuperation proc 1
	REGISTER_HANDLER( 54227 );
	// hunter - Rapid Recuperation proc 2
	REGISTER_HANDLER( 56654 );
	// warlock - Soul Leech
	REGISTER_HANDLER( 30294 );
	// warlock - Nether Protection
	REGISTER_HANDLER( 54370 );
	// warlock - Aftermath
	REGISTER_HANDLER( 18118 );
	// warlock - Shadow Embrace
	REGISTER_HANDLER( 32386 );
	REGISTER_SAMEHANDLER( 32388, 32386);
	REGISTER_SAMEHANDLER( 32389, 32386);
	REGISTER_SAMEHANDLER( 32390, 32386);
	REGISTER_SAMEHANDLER( 32391, 32386);
	// warlock soul link
	REGISTER_HANDLER( 25228 );
	// warlock - Everlasting Affliction
	REGISTER_HANDLER( 47422 );
	// warlock - Fel Synergy
	REGISTER_HANDLER( 54181 );
	// warlock - Siphon Life
	REGISTER_HANDLER( 63106 );
	// warlock - Unstable Affliction
	REGISTER_HANDLER( 31117 );
	// warlock - Improved Drain Soul
	REGISTER_HANDLER( 18371 );
	// warlock - Seed of Corruption
	REGISTER_HANDLER( 27285 );
	// warlock - drain soul
	REGISTER_HANDLER( 1120 );
	// rogue - blade twisting
	REGISTER_HANDLER( 31125 );
	// rogue - Master of Subtlety
	REGISTER_HANDLER( 31665 );
	// rogue - Cheat Death
	REGISTER_HANDLER( 31228 );
	// rogue - Honor Among Thieves
	REGISTER_HANDLER( 52916 );
	// druid - Primal Fury
	REGISTER_HANDLER( 37116 );
	REGISTER_SAMEHANDLER( 37117, 37116);
	// hot streak
	REGISTER_HANDLER( 48108 );
	// Missile Barrage
	REGISTER_HANDLER( 44401 );
	// impact
	REGISTER_HANDLER( 64343 );
	// Mage ignite talent only for fire dmg
	REGISTER_HANDLER( 12654 );
	// warrior - Unbridled Wrath
	REGISTER_HANDLER( 12964 );
	// warrior - Sudden Death
//	REGISTER_HANDLER( 52437 );
	// deep wound requires a melee weapon
	REGISTER_HANDLER( 12721 );
	// sword specialization
	REGISTER_HANDLER( 16459 );
//	REGISTER_SAMEHANDLER( 4350, 16459);
	// Improved Defensive Stance
	REGISTER_HANDLER( 57514 );
	REGISTER_SAMEHANDLER( 57516, 57514);
	//Damage Shield
	REGISTER_HANDLER( 58872 );
	//Critical Block
	REGISTER_HANDLER( 47294 );
	//Mace Stun Effect
	REGISTER_HANDLER( 5530 );
	//Bloodlust cat
	REGISTER_HANDLER( 37310 );
	//Bloodlust bear
	REGISTER_HANDLER( 37309 );
	//Nature's Guardian
	REGISTER_HANDLER( 31616 );
	//seal fate
	REGISTER_HANDLER( 14189 );
	//general proc handler for aura 300 -> mirror dmg on caster
	REGISTER_HANDLER( 71948 );
	// Burnout
	REGISTER_HANDLER( 44450 );
	// druid - Predator's Swiftness
	REGISTER_HANDLER( 69369 );
	// Druid - Owlkin Frenzy
	REGISTER_HANDLER( 48391 );
	// Druid - Revitalize
	REGISTER_HANDLER( 48540 );
	// Druid - Improved Leader of the Pack
	REGISTER_HANDLER( 34299 );
	// Druid - Infected Wounds
	REGISTER_HANDLER( 58179 );
	REGISTER_SAMEHANDLER( 58180, 58179);
	REGISTER_SAMEHANDLER( 58181, 58179);
	// Druid - Blood Frenzy Proc
//	REGISTER_HANDLER( 16953 );
}
