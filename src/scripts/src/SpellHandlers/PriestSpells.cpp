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

/*
   How to add a new paladin spell to the dummy spell handler:

      1) Add a new function to handle the spell at the end of this file but before the
         SetupPaladinSpells() function. SetupPaladinSpells() must always be the last function.

      2) Register the dummy spell by adding a new line to the end of the list in the
         SetupPaladinSpells() function.

   Please look at how the other spells are handled and try to use the
   same variable names and formatting style in your new spell handler.
*/

class ShadowFiend : public CreatureAIScript
{
public:
   ADD_CREATURE_FACTORY_FUNCTION(ShadowFiend);

   //constructor
    ShadowFiend(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		//only handle spell created mobs
		if( pCreature->GetUInt32Value( UNIT_FIELD_CREATEDBY ) == 0 )
			return;

		Player *owner = _unit->GetMapMgr()->GetPlayer( _unit->GetUInt32Value( UNIT_FIELD_CREATEDBY ) );
		if( owner )
		{
			uint32 parent_bonus;
			if( owner->IsPlayer() )
				parent_bonus = owner->GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS + SCHOOL_SHADOW ) * 30 / 100;
			else
				parent_bonus = 2300 + (float)(owner->GetDamageDoneMod(SCHOOL_SHADOW)*65/100);
			_unit->SetUInt32Value( UNIT_FIELD_BASEATTACKTIME, 1500 );
			_unit->SetFloatValue(UNIT_FIELD_MINDAMAGE, parent_bonus);
			_unit->SetFloatValue(UNIT_FIELD_MAXDAMAGE, parent_bonus);
			_unit->BaseDamage[0] = parent_bonus;
			_unit->BaseDamage[1] = parent_bonus;
			pCreature->BaseAttackType = SCHOOL_SHADOW;
		}	
		//register spell that will regen mana for caster on melee hit
		SpellEntry *sp = dbcSpell.LookupEntryForced( 34650 );	//Mana Leech
		ProcTriggerSpell pts( sp );
		pts.caster = _unit->GetGUID();
		pts.spellId = sp->Id;
		pts.procFlags = PROC_ON_MELEE_ATTACK;
		pts.created_with_value = sp->EffectBasePoints[0] + 1;
		pts.procCharges = 0;
		pts.procChance = 100;
		_unit->RegisterScriptProcStruct( pts );
   }
};

class LightWell : public CreatureAIScript
{
public:
   ADD_CREATURE_FACTORY_FUNCTION(LightWell);

   //constructor
    LightWell(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		//only handle spell created mobs
		if( pCreature->GetUInt32Value( UNIT_FIELD_CREATEDBY ) == 0 )
			return;

		pCreature->GetAIInterface()->m_canMove = false;
		pCreature->CastSpell(pCreature,59907,true);
   }
};

void SetupPriestSpells(ScriptMgr * mgr)
{
	mgr->register_creature_script( 19668, &ShadowFiend::Create);	//shadowfiend
	mgr->register_creature_script( 31893, &LightWell::Create);		//lightwell
	mgr->register_creature_script( 31894, &LightWell::Create);		//lightwell
	mgr->register_creature_script( 31895, &LightWell::Create);		//lightwell
	mgr->register_creature_script( 31896, &LightWell::Create);		//lightwell
	mgr->register_creature_script( 31897, &LightWell::Create);		//lightwell
	mgr->register_creature_script( 31883, &LightWell::Create);		//lightwell
}