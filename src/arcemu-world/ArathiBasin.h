/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2009 <http://www.ArcEmu.org/>
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
//safe way to handle arrays in debug mode
#include <array>

#define AB_BUFF_RESPAWN_TIME 90000

enum ABBuffs
{
	AB_BUFF_STABLES						= 0,
	AB_BUFF_BLACKSMITH					= 1,
	AB_BUFF_FARM						= 2,
	AB_BUFF_LUMBERMILL					= 3,
	AB_BUFF_MINE						= 4,
	AB_NUM_BUFFS						= 5,
};

enum ABControlPoints
{
	AB_CONTROL_POINT_STABLE				= 0,
	AB_CONTROL_POINT_FARM				= 1,
	AB_CONTROL_POINT_BLACKSMITH			= 2,
	AB_CONTROL_POINT_MINE				= 3,
	AB_CONTROL_POINT_LUMBERMILL			= 4,
	AB_NUM_CONTROL_POINTS				= 5,
};

enum ABSpawnTypes
{
	AB_SPAWN_TYPE_NEUTRAL				= 0,
	AB_SPAWN_TYPE_ALLIANCE_ASSAULT		= 1,
	AB_SPAWN_TYPE_HORDE_ASSAULT			= 2,
	AB_SPAWN_TYPE_ALLIANCE_CONTROLLED	= 3,
	AB_SPAWN_TYPE_HORDE_CONTROLLED		= 4,
	AB_NUM_SPAWN_TYPES					= 5,
};

class ArathiBasin : public CBattleground
{
public:
	tr1::array<GameObject *,AB_NUM_BUFFS> m_buffs;
	tr1::array<GameObject *,AB_NUM_CONTROL_POINTS> m_controlPoints;
	tr1::array<GameObject *,AB_NUM_CONTROL_POINTS> m_controlPointAuras;

protected:
	list<GameObject*> m_gates;

	tr1::array<uint32,2> m_resources;
	tr1::array<uint32,2> m_capturedBases;
	tr1::array<uint32,2> m_lastHonorGainResources;
	tr1::array<uint32,2> m_lastRepGainResources;
	tr1::array<int32,AB_NUM_CONTROL_POINTS> m_basesOwnedBy;
	tr1::array<int32,AB_NUM_CONTROL_POINTS> m_basesLastOwnedBy;
	tr1::array<int32,AB_NUM_CONTROL_POINTS> m_basesAssaultedBy;
	tr1::array<Creature *,AB_NUM_CONTROL_POINTS> m_spiritGuides;
	tr1::array<int32,2> m_nearingVictory;
	uint32 m_lgroup;
	//bool DefFlag[AB_NUM_CONTROL_POINTS][2];
	tr1::array<tr1::array<bool,2>,AB_NUM_CONTROL_POINTS> DefFlag;

public:
	ArathiBasin(MapMgr * mgr, uint32 id, uint32 lgroup, uint32 t);
	~ArathiBasin();

	void HookOnPlayerDeath(Player * plr);
	void HookFlagDrop(Player * plr, GameObject * obj);
	void HookFlagStand(Player * plr, GameObject * obj);
	void HookOnMount(Player * plr);
	void HookOnAreaTrigger(Player * plr, uint32 id);
	bool HookHandleRepop(Player * plr);
	void OnAddPlayer(Player * plr);
	void OnRemovePlayer(Player * plr);
	void OnCreate();
	void HookOnPlayerKill(Player * plr, Player * pVictim);
	void HookOnUnitKill(Player * plr, Unit * pVictim);
	void HookOnHK(Player * plr);
	void HookOnShadowSight();
	void HookGenerateLoot( Player * plr, Object * pCorpse );
	void SpawnBuff(uint32 x);
	LocationVector GetStartingCoords(uint32 Team);
	void HookOnFlagDrop(Player * plr);

	static CBattleground * Create(MapMgr * m, uint32 i, uint32 l, uint32 t) { return new ArathiBasin(m, i, l, t); }

	uint32 GetNameID() { return 40; }
	void OnStart();

	void EventUpdateResources(uint32 Team);
	bool HookSlowLockOpen(GameObject * pGo, Player * pPlayer, Spell * pSpell);

	/* AB Game Mechanics */
	void SpawnControlPoint(uint32 Id, uint32 Type);
	void CaptureControlPoint(uint32 Id, uint32 Team);
	void AssaultControlPoint(Player * pPlayer, uint32 Id);

	void SetIsWeekend(bool isweekend);
};