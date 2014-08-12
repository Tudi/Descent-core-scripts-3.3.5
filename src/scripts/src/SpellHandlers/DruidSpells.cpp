#include "StdAfx.h"
#include "Setup.h"

class ForceOfNature : public CreatureAIScript
{
public:
   ADD_CREATURE_FACTORY_FUNCTION(ForceOfNature);

   //constructor
    ForceOfNature(Creature* pCreature) : CreatureAIScript(pCreature)
    {
		//only handle spell created mobs
		if( pCreature->GetUInt32Value( UNIT_FIELD_CREATEDBY ) == 0 )
			return;

		//health from wowhead
		uint32 health_per_level = 300/61;
		pCreature->SetUInt32Value(UNIT_FIELD_MAXHEALTH, health_per_level * pCreature->getLevel() + 100 );
		pCreature->SetUInt32Value(UNIT_FIELD_HEALTH,pCreature->GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		//low dmg
		Player *owner = _unit->GetMapMgr()->GetPlayer( _unit->GetUInt32Value( UNIT_FIELD_CREATEDBY ) );
		if( owner != NULL )
		{
			float base_dmg = 5.0f + owner->GetDamageDoneMod(SCHOOL_NATURE) * 70.0f / 100.0f;	//around 800-1000 dmg
			if( base_dmg < 150 )
				base_dmg = owner->getLevel() * (1000/80);
			Aura *a = owner->FindAuraPassiveByNameHash( SPELL_HASH_BRAMBLES );
			if( a )
			{
//				base_dmg += base_dmg * a->m_modList[2] / 100;
				base_dmg += base_dmg * (a->GetSpellProto()->EffectBasePoints[2] + 1) / 100;
				//register spell that will stun target
				SpellEntry *sp = dbcSpell.LookupEntryForced( CREATURE_SPELL_TO_DAZE );	
				ProcTriggerSpell pts( sp );
				pts.caster = _unit->GetGUID();
				pts.spellId = sp->Id;	
				pts.procFlags = PROC_ON_MELEE_ATTACK;
				pts.created_with_value = sp->EffectBasePoints[0] + 1;
				pts.procCharges = 0;
				pts.procChance = 15;
				_unit->RegisterScriptProcStruct(pts);
			}
			pCreature->SetFloatValue( UNIT_FIELD_MINDAMAGE, base_dmg );
			pCreature->SetFloatValue( UNIT_FIELD_MAXDAMAGE, base_dmg * 3 / 2 );
		}
//		pCreature->BaseAttackType = SCHOOL_NATURE;
   }
};

void SetupDruidSpells(ScriptMgr * mgr)
{
	mgr->register_creature_script( 1964, &ForceOfNature::Create);	//shadowfiend
}