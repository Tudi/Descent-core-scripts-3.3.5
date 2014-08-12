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

#ifndef WOWSERVER_DYNAMICOBJECT_H
#define WOWSERVER_DYNAMICOBJECT_H

struct SpellEntry;

typedef std::set<uint64>  DynamicObjectList;

class SERVER_DECL DynamicObject : public Object
{
public:
	DynamicObject( uint32 high, uint32 low );
	~DynamicObject( );
	virtual void Virtual_Destructor( );

	void Create(Unit * caster, Spell * pSpell, float x, float y, float z, uint32 duration, float radius,int32 spell_val);
	void UpdateTargets();

	void AddInRangeObject(Object* pObj);
	void OnRemoveInRangeObject(Object* pObj);
	void Remove();

protected:
	
	SpellEntry * m_spellProto;
	Unit * u_caster;
	Player * p_caster;
	Spell* m_parentSpell;
	DynamicObjectList targets;
	int32	spell_value;	//this dyn object was created by some spell of some player, The player had spell mods and we should keep those
	
	uint32 m_aliveDuration;
	uint32 _fields[DYNAMICOBJECT_END];
};

#endif

