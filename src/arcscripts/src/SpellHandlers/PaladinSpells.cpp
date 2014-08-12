/*
 * ArcScript Scripts for Arcemu MMORPG Server
 * Copyright (C) 2008-2009 Arcemu Team
 * Copyright (C) 2007 Moon++ <http://www.moonplusplus.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Setup.h"

bool EyeForAnEye(uint32 i, Aura *pAura, bool apply)
{
	Unit *target = pAura->GetTarget();

	if (apply)
		target->AddProcTriggerSpell(25997, pAura->GetSpellProto()->Id, pAura->m_casterGuid, pAura->GetSpellProto()->procChance, PROC_ON_CRIT_HIT_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM | PROC_ON_SPELL_CRIT_HIT_VICTIM, 0, NULL, NULL);
	else
		target->RemoveProcTriggerSpell(25997, pAura->m_casterGuid);

	return true;
}

bool HolyShock(uint32 i, Spell * pSpell) 
{
	Unit* target = pSpell->GetUnitTarget();
	if( target == NULL )
		return true;

	Player* caster = pSpell->p_caster;
	if( caster == NULL )
		return true; 

	uint32 spell_id = 0;

	if( isFriendly(caster, target) )
		switch( pSpell->GetProto()->Id )
		{
			case 20473: spell_id = 25914; break;
			case 20929: spell_id = 25913; break;
			case 20930: spell_id = 25903; break;
			case 27174: spell_id = 27175; break;
			case 33072: spell_id = 33074; break;
			case 48824: spell_id = 48820; break;
			case 48825: spell_id = 48821; break;
		}
	else
		switch( pSpell->GetProto()->Id )
		{
			case 20473: spell_id = 25912; break;
			case 20929: spell_id = 25911; break;
			case 20930: spell_id = 25902; break;
			case 27174: spell_id = 27176; break;
			case 33072: spell_id = 33073; break;
			case 48824: spell_id = 48822; break;
			case 48825: spell_id = 48823; break;
		}

	if( spell_id )
		caster->CastSpell(target, spell_id, false);

	return true;  
}

void SetupPaladinSpells(ScriptMgr * mgr)
{
	mgr->register_dummy_aura(9799, &EyeForAnEye);
	mgr->register_dummy_aura(25988, &EyeForAnEye);

	uint32 HolyShockIds[] = { 20473, 20929, 20930, 27174, 33072, 48824, 48825, 0 };
	mgr->register_dummy_spell(HolyShockIds, &HolyShock);
}
