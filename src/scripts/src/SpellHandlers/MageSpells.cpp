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

bool ColdSnap(uint32 i, Spell * pSpell)
{
    if(!pSpell->p_caster) return true;
    pSpell->p_caster->ClearCooldownsOnLine(6, pSpell->GetProto()->Id);
    return true;
}

class MirrorImage : public CreatureAIScript
{
public:
   ADD_CREATURE_FACTORY_FUNCTION(MirrorImage);

   AI_Spell owner_spells[10];
   uint32	stored_spells;

   void SetupDefaultSpellbookSpell(uint32 page)
   {
		owner_spells[page].agent = AGENT_SPELL;
		owner_spells[page].entryId = 0;	
		owner_spells[page].global_cooldown = 2000;
		owner_spells[page].cooldown = 3000;
		owner_spells[page].initial_cooldown = 0;
		owner_spells[page].max_hp_pct = 0;
		owner_spells[page].maxrange = 30;
		owner_spells[page].min_hp_pct = 0;
		owner_spells[page].minrange = 0;
		owner_spells[page].procChance = 50;
		owner_spells[page].procCount = 0;
		owner_spells[page].shout_before_cast = NULL;
		owner_spells[page].spell = NULL;
		owner_spells[page].spelltargetType = TTYPE_SINGLETARGET;
   }
   //constructor
    MirrorImage(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		Player *owner = _unit->GetMapMgr()->GetPlayer( _unit->GetUInt64Value( UNIT_FIELD_CREATEDBY ) );
		if( owner )
		{
			_unit->SetUInt32Value( UNIT_FIELD_BYTES_0, owner->GetUInt32Value( UNIT_FIELD_BYTES_0 ) ); 
			_unit->SetUInt32Value( UNIT_FIELD_FLAGS, 8 );
			_unit->SetUInt32Value( UNIT_FIELD_FLAGS_2, 2064 );
			_unit->SetUInt32Value( UNIT_CREATED_BY_SPELL, 58834 );
			_unit->SetUInt32Value( UNIT_FIELD_BYTES_2, owner->GetUInt32Value( UNIT_FIELD_BYTES_2 ) );//weapon sheath and rest
			_unit->SetUInt32Value( UNIT_FIELD_DISPLAYID, owner->GetUInt32Value( UNIT_FIELD_DISPLAYID ) );
			_unit->SetFloatValue( UNIT_FIELD_BOUNDINGRADIUS, 0.383000f );
			_unit->SetFloatValue( UNIT_FIELD_COMBATREACH, 1.500000f );
			int mainhandfield = PLAYER_VISIBLE_ITEM_1_ENTRYID + (EQUIPMENT_SLOT_MAINHAND * (PLAYER_VISIBLE_ITEM_2_ENTRYID - PLAYER_VISIBLE_ITEM_1_ENTRYID));
			_unit->SetUInt32Value( UNIT_VIRTUAL_ITEM_SLOT_ID, owner->GetUInt32Value( mainhandfield ) );
			int moffhandfield = PLAYER_VISIBLE_ITEM_1_ENTRYID + (EQUIPMENT_SLOT_OFFHAND * (PLAYER_VISIBLE_ITEM_2_ENTRYID - PLAYER_VISIBLE_ITEM_1_ENTRYID));
			_unit->SetUInt32Value( UNIT_VIRTUAL_ITEM_SLOT_ID_1, owner->GetUInt32Value( moffhandfield ) );
		}

		RegisterAIUpdateEvent( 2000 );
		if( _unit->GetAIInterface() )
			_unit->GetAIInterface()->disable_melee = true;
		stored_spells = 0;
		SetupDefaultSpellbookSpell( stored_spells );
		owner_spells[stored_spells].spell = dbcSpell.LookupEntryForced( 42842 );
		stored_spells++;
    }
    void AIUpdate()
    {
		//check if casting
		if( _unit->isCasting() )
			return;
		//check if we still have an owner
		Player *owner = _unit->GetMapMgr()->GetPlayer( _unit->GetUInt32Value( UNIT_FIELD_CREATEDBY ) );
		if( owner == NULL )
			return;
		//do we have a target ? If not then try to agro owner selection :P
		Unit *target = _unit->GetAIInterface()->GetNextTarget();
		if( target == NULL && owner->GetSelection() )
		{
			target = _unit->GetMapMgr()->GetUnit( owner->GetSelection() );
			if( target && isAttackable( _unit, target ) )
				_unit->GetAIInterface()->AttackReaction( target, 1 );
		}
		if( owner->last_casted_enemy_spell != NULL && stored_spells < 10-1 )
		{
			//check if we have this spell
			bool have_it = false;
			for(uint32 i=0;i<stored_spells;i++)
				if( owner_spells[i].spell == owner->last_casted_enemy_spell )
				{
					have_it = true;
					break;
				}
			if( have_it == false )
			{
				//reset spellbook ? = cast owner last spell
//				stored_spells = 0;
				//keep building up a spellbook
				SetupDefaultSpellbookSpell( stored_spells );
				owner_spells[ stored_spells ].global_cooldown = owner->last_casted_enemy_spell->CategoryRecoveryTime;
				owner_spells[ stored_spells ].maxrange = sqrt( owner->last_casted_enemy_spell->base_range_or_radius_sqr );
				owner_spells[ stored_spells ].spell = owner->last_casted_enemy_spell;
				owner_spells[ stored_spells ].cooldown = owner->last_casted_enemy_spell->RecoveryTime;
				stored_spells++;
			}
		}
		uint32 tickNow = GetTickCount();
		for(int32 i=stored_spells-1;i>=0;i--)
			if( owner_spells[ i ].cooldowntime > tickNow || RandomUInt() % 100 < owner_spells[ i ].procChance 
				)
				continue;
			else
				_unit->GetAIInterface()->SetNextSpell( &owner_spells[ i ] );
	}
};

void SetupMageSpells(ScriptMgr * mgr)
{
    mgr->register_dummy_spell(11958, &ColdSnap);
	mgr->register_creature_script( 31216, &MirrorImage::Create);	//mirror image
}
