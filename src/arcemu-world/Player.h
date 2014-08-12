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

#ifndef _PLAYER_H
#define _PLAYER_H

//safe way to handle arrays in debug mode
#include <array>
#include "FeatureDefinitions.h"

class BGScore;
class Channel;
class Creature;
class Battleground;
class TaxiPath;
class GameObject;
class Transporter;
class Corpse;
class Guild;
class GuildRank;
class Pet;
class Charter;
class LFGMatch;
struct LevelInfo;
class SpeedDetector;
class Vehicle;
class SpellEffectOverrideScript;
class Instance;
class MapMgr;
struct LFG_store;

#define MAX_PET_NO 3
#define PLAYER_NORMAL_RUN_SPEED 7.9867f	//why not round ? to avoid memory hackers to find it :)
#define PLAYER_NORMAL_SWIM_SPEED 4.722222f
#define PLAYER_NORMAL_FLIGHT_SPEED 8.132f
#define PLAYER_HONORLESS_TARGET_SPELL 2479
#define MONSTER_NORMAL_RUN_SPEED 8.01f
/* action button defines */
#define PLAYER_ACTION_BUTTON_COUNT 145
#define PLAYER_ACTION_BUTTON_SIZE PLAYER_ACTION_BUTTON_COUNT * sizeof(ActionButton)
#define MAX_SPEC_COUNT 2
#define RESPECT_COOLDOWN_INTERVAL		5*60*1000
#define GLYPHS_COUNT (PLAYER_GLYPHS_ENABLED - PLAYER_FIELD_GLYPHS_1)

#define PLAYER_LEVEL_CAP_BLIZZLIKE					80
#define PLAYER_LEVEL_CAP							137
#define PLAYER_LEVEL_CAP_DBC						100
#define PLAYER_ARENA_MIN_LEVEL						70
#define PLAYER_SKILL_CAP							450
#define REQUIRED_LEVEL_TO_MAKE_DK					55
#define PLAYERS_RECEIVE_TALENTPOINTS_WITH_LEVEL		(90-9)	//1 point per level from level 9

#define ACHIEVEMENT_SEND_DELAY 1000 //we have this delay of sending auras to other players so client will have time to create object first
#define LOGIN_CIENT_SEND_DELAY 1000 //we have this delay of sending auras to other players so client will have time to create object first

#define MAX_SEND_BUFFER_SIZE			65535
#define MAX_SEND_BUFFER_SIZE_TO_SEND	64000	//maybe some network cards will freak out of large packets ?

//====================================================================
//  Inventory
//  Holds the display id and item type id for objects in
//  a character's inventory
//====================================================================

#define TOTAL_NORMAL_RUNE_TYPES 3
#define TOTAL_USED_RUNES (TOTAL_NORMAL_RUNE_TYPES*2)
#define TOTAL_RUNE_TYPES 4
//#define TOTAL_RUNE_AVAIL 8

#define TAXIMASK_SIZE 16	//last time was 12 but 4 bytes for safety in case i forget to increase it next time :)

enum Classes
{
	WARRIOR = 1,
	PALADIN = 2,
	HUNTER = 3,
	ROGUE = 4,
	PRIEST = 5,
	DEATHKNIGHT = 6,
	SHAMAN = 7,
	MAGE = 8,
	WARLOCK = 9,
	DRUID = 11,
	PLAYER_CLASS_TYPE_COUNT
};

enum Races
{
	RACE_HUMAN = 1,
	RACE_ORC = 2,
	RACE_DWARF = 3,
	RACE_NIGHTELF = 4,
	RACE_UNDEAD = 5,
	RACE_TAUREN = 6,
	RACE_GNOME = 7,
	RACE_TROLL = 8,
	RACE_GOBLIN = 9,
	RACE_BLOODELF = 10,
	RACE_DRAENEI = 11,
	RACE_WORGEN = 12,
};

enum ShapeshiftForm
{
   FORM_NORMAL              = 0,
   FORM_CAT                 = 1,
   FORM_TREE                = 2,
   FORM_TRAVEL              = 3,
   FORM_AQUA                = 4,
   FORM_BEAR                = 5,
   FORM_AMBIENT             = 6,
   FORM_GHOUL               = 7,
   FORM_DIREBEAR            = 8,
   FORM_CUSTOM_NORMAL		= 9,		// added manually to be able to detect non transformed mode
   FORM_CREATUREBEAR        = 14,
   FORM_GHOSTWOLF           = 16,
   FORM_BATTLESTANCE        = 17,
   FORM_DEFENSIVESTANCE     = 18,
   FORM_BERSERKERSTANCE     = 19,
   FORM_ZOMBIE              = 21,
   FORM_DEMON               = 22,
   FORM_SWIFT               = 27,
   FORM_SHADOW              = 28,
   FORM_FLIGHT              = 29,
   FORM_STEALTH             = 30,
   FORM_MOONKIN             = 31,
   FORM_SPIRITOFREDEMPTION  = 32,
   FORM_RESURRECT_AS_GHOUL	= 127,
   FORM_NORMAL_FORM			= 268435456,	//having this means you are not transformed = form 29 ?
   FORM_TOTAL_COUNT
};

enum PlayerStatus
{
	NONE			 = 0,
	TRANSFER_PENDING = 1,
};

enum DrunkenState
{
	DRUNKEN_SOBER	= 0,
	DRUNKEN_TIPSY	= 1,
	DRUNKEN_DRUNK	= 2,
	DRUNKEN_SMASHED	= 3
};

enum RankTitles
{
	PVPTITLE_NONE							= 0,
	PVPTITLE_PRIVATE						= 1,
	PVPTITLE_CORPORAL						= 2,
	PVPTITLE_SERGEANT						= 3,
	PVPTITLE_MASTER_SERGEANT				= 4,
	PVPTITLE_SERGEANT_MAJOR					= 5,
	PVPTITLE_KNIGHT							= 6,
	PVPTITLE_KNIGHT_LIEUTENANT				= 7,
	PVPTITLE_KNIGHT_CAPTAIN					= 8,
	PVPTITLE_KNIGHT_CHAMPION				= 9,
	PVPTITLE_LIEUTENANT_COMMANDER			= 10,
	PVPTITLE_COMMANDER						= 11,
	PVPTITLE_MARSHAL						= 12,
	PVPTITLE_FIELD_MARSHAL					= 13,
	PVPTITLE_GRAND_MARSHAL					= 14,
	PVPTITLE_SCOUT							= 15,
	PVPTITLE_GRUNT							= 16,
	PVPTITLE_HSERGEANT						= 17,
	PVPTITLE_SENIOR_SERGEANT				= 18,
	PVPTITLE_FIRST_SERGEANT					= 19,
	PVPTITLE_STONE_GUARD					= 20,
	PVPTITLE_BLOOD_GUARD					= 21,
	PVPTITLE_LEGIONNAIRE					= 22,
	PVPTITLE_CENTURION						= 23,
	PVPTITLE_CHAMPION						= 24,
	PVPTITLE_LIEUTENANT_GENERAL				= 25,
	PVPTITLE_GENERAL						= 26,
	PVPTITLE_WARLORD						= 27,
	PVPTITLE_HIGH_WARLORD					= 28,
	PVPTITLE_GLADIATOR						= 29,
	PVPTITLE_DUELIST						= 30,
	PVPTITLE_RIVAL							= 31,
	PVPTITLE_CHALLENGER						= 32,
	PVPTITLE_SCARAB_LORD					= 33,
	PVPTITLE_CONQUEROR						= 34,
	PVPTITLE_JUSTICAR						= 35,
	PVPTITLE_CHAMPION_OF_THE_NAARU			= 36,
	PVPTITLE_MERCILESS_GLADIATOR			= 37,
	PVPTITLE_OF_THE_SHATTERED_SUN			= 38,
	PVPTITLE_HAND_OF_ADAL					= 39,
	PVPTITLE_VENGEFUL_GLADIATOR				= 40,
	PVPTITLE_BATTLEMASTER					= 41,
	PVPTITLE_THE_SEEKER						= 42,
	PVPTITLE_ELDER							= 43,
	PVPTITLE_FLAME_WARDEN					= 44,
	PVPTITLE_FLAME_KEEPER					= 45,
	PVPTITLE_THE_EXALTED					= 46,
	PVPTITLE_THE_EXPLORER					= 47,
	PVPTITLE_THE_DIPLOMAT					= 48,
	PVPTITLE_BRUTAL_GLADIATOR				= 49,
	PVPTITLE_ARENA_MASTER					= 50,
	PVPTITLE_SALTY							= 51,
	PVPTITLE_CHEF							= 52,
	PVPTITLE_THE_SUPREME					= 53,
	PVPTITLE_OF_THE_TEN_STORMS				= 54,
	PVPTITLE_OF_THE_EMERALD_DREAM			= 55,
	PVPTITLE_DEADLY_GLADIATOR				= 56,
	PVPTITLE_PROPHET						= 57,
	PVPTITLE_THE_MALEFIC					= 58,
	PVPTITLE_STALKER						= 59,
	PVPTITLE_OF_THE_EBON_BLADE				= 60,
	PVPTITLE_ARCHMAGE						= 61,
	PVPTITLE_WARBRINGER						= 62,
	PVPTITLE_ASSASSIN						= 63,
	PVPTITLE_GRAND_MASTER_ALCHEMIST			= 64,
	PVPTITLE_GRAND_MASTER_BLACKSMITH		= 65,
	PVPTITLE_IRON_CHEF						= 66,
	PVPTITLE_GRAND_MASTER_ENCHANTER			= 67,
	PVPTITLE_GRAND_MASTER_ENGINEER			= 68,
	PVPTITLE_DOCTOR							= 69,
	PVPTITLE_GRAND_MASTER_ANGLER			= 70,
	PVPTITLE_GRAND_MASTER_HERBALIST			= 71,
	PVPTITLE_GRAND_MASTER_SCRIBE			= 72,
	PVPTITLE_GRAND_MASTER_JEWLCRAFTER		= 73,
	PVPTITLE_GRAND_MASTER_LETHERWORKER		= 74,
	PVPTITLE_GRAND_MASTER_MINER				= 75,
	PVPTITLE_GRAND_MASTER_SKINNER			= 76,
	PVPTITLE_GRAND_MASTER_TAILOR			= 77,
	PVPTITLE_OF_QUEL_THALAS					= 78,
	PVPTITLE_OF_ARGUS						= 79,
	PVPTITLE_OF_KHAZ_MODAN					= 80,
	PVPTITLE_OF_GNOMEREGAN					= 81,
	PVPTITLE_THE_LION_HEARTHED				= 82,
	PVPTITLE_CHAMPION_OF_ELUNE				= 83,
	PVPTITLE_HERO_OF_ORGIMMAR				= 84,
	PVPTITLE_PLAINSRUNNER					= 85,
	PVPTITLE_OF_THE_DARKSPEARTRIPE			= 86,
	PVPTITLE_THE_FORSAKEN					= 87,
	PVPTITLE_THE_MAGIC_SEEKER				= 88,
	PVPTITLE_TWILIGHT_VANQUISHER			= 89,
	PVPTITLE_CONQUEROR_OF_NAXXRAMAS			= 90,
	PVPTITLE_HERO_OF_NORTHREND				= 91,
	PVPTITLE_THE_HALLOWED					= 92,
	PVPTITLE_LOREMASTER						= 93,
	PVPTITLE_OF_THE_ALLIANCE				= 94,
	PVPTITLE_OF_THE_HORDE					= 95,
	PVPTITLE_THE_FLAWLESS_VICTOR			= 96,
	PVPTITLE_CHAMPION_OF_THE_FROZEN_WASTES	= 97,
	PVPTITLE_AMBASSADOR						= 98,
	PVPTITLE_THE_ARGENT_CHAMPION			= 99,
	PVPTITLE_GUARDIAN_OF_CENARIUS			= 100,
	PVPTITLE_BREWMASTER						= 101,
	PVPTITLE_MERRYMAKER						= 102,
	PVPTITLE_THE_LOVE_FOOL					= 103,
	PVPTITLE_MATRON							= 104,
	PVPTITLE_PATRON							= 105,
	PVPTITLE_OBSIDIAN_SLAYER				= 106,
	PVPTITLE_OF_THE_NIGHTFALL				= 107,
	PVPTITLE_THE_IMMORTAL					= 108,
	PVPTITLE_THE_UNDYING					= 109,
	PVPTITLE_JENKINS						= 110,
	PVPTITLE_BLOODSAIL_ADMIRAL				= 111,
	PVPTITLE_THE_INSANE						= 112,
	PVPTITLE_OF_THE_EXODAR					= 113,
	PVPTITLE_OF_DARNASSUS					= 114,
	PVPTITLE_OF_IRONFORGE					= 115,
	PVPTITLE_OF_STORMWIND					= 116,
	PVPTITLE_OF_ORGRIMMAR					= 117,
	PVPTITLE_OF_SENJIN						= 118,
	PVPTITLE_OF_SILVERMOON					= 119,
	PVPTITLE_OF_THUNDERBLUFF				= 120,
	PVPTITLE_OF_THE_UNDERCITY				= 121,
	PVPTITLE_THE_NOBLE						= 122,
	PVPTITLE_CRUSADER						= 123,
	PVPTITLE_DEATHS_DEMISE					= 124,
	PVPTITLE_CELESTIAL_DEFENDER				= 125,
	PVPTITLE_CONQUEROR_OF_ULDUAR			= 126,
	PVPTITLE_CHAMPION_OF_ULDUAR				= 127,
	PVPTITLE_VANQUISHER						= 128,
	PVPTITLE_STARCALLER						= 129,
	PVPTITLE_THE_ASTRAL_WALKER				= 130,
	PVPTITLE_HERALD_OF_THE_TITANS			= 131,
	PVPTITLE_FURIOUS_GLADIATOR				= 132,
	PVPTITLE_THE_PILGRIM					= 133,
	PVPTITLE_RELENTLESS_GLADIATOR			= 134,
	PVPTITLE_GRAND_CRUSADER					= 135,
	PVPTITLE_THE_ARGENT_DEFENDER			= 136,
	PVPTITLE_THE_PATIENT					= 137,
	PVPTITLE_LIGHT_OF_DAWN					= 138,
	PVPTITLE_BANE_OF_FALLEN_KING			= 139,
	PVPTITLE_KINGSLAYER						= 140,
	PVPTITLE_ASHEN_VERDICT					= 141,
	PVPTITLE_WRATHFULL_GLADIATOR			= 142,
	PVPTITLE_END							= 143,
};

enum Player_Custom_Flags
{
//	PLAYER_CUSTOM_FLAG_IGNORES_SPELL_STATE_REQUIREMENTS			= 1,
};

enum PvPAreaStatus
{
    AREA_ALLIANCE = 1,
    AREA_HORDE = 2,
    AREA_CONTESTED = 3,
    AREA_PVPARENA = 4,
};

enum PlayerMovementType
{
    MOVE_ROOT			= 1,
    MOVE_UNROOT			= 2,
    MOVE_WATER_WALK		= 3,
    MOVE_LAND_WALK		= 4,
    MOVE_FEATHER_FALL	= 5,
    MOVE_NORMAL_FALL	= 6,
    MOVE_HOVER			= 7,
    MOVE_NO_HOVER		= 8,
};

enum PlayerSpeedType
{
    RUN	            = 1,
    RUNBACK         = 2,
    SWIM	        = 3,
    SWIMBACK        = 4,
    WALK	        = 5,
    FLY	            = 6,
};

enum Standing
{
    STANDING_HATED,
    STANDING_HOSTILE,
    STANDING_UNFRIENDLY,
    STANDING_NEUTRAL,
    STANDING_FRIENDLY,
    STANDING_HONORED,
    STANDING_REVERED,
    STANDING_EXALTED
};

enum PlayerFlags
{
    PLAYER_FLAG_PARTY_LEADER		= 0x01,
    PLAYER_FLAG_AFK					= 0x02,
    PLAYER_FLAG_DND					= 0x04,
    PLAYER_FLAG_GM					= 0x08,
    PLAYER_FLAG_DEATH_WORLD_ENABLE  = 0x10,
    PLAYER_FLAG_RESTING				= 0x20,
    PLAYER_FLAG_UNKNOWN1            = 0x40,
    PLAYER_FLAG_FREE_FOR_ALL_PVP	= 0x80,
    PLAYER_FLAG_UNKNOWN2            = 0x100,
    PLAYER_FLAG_PVP_TOGGLE			= 0x200,
    PLAYER_FLAG_NOHELM				= 0x400,
    PLAYER_FLAG_NOCLOAK				= 0x800,
    PLAYER_FLAG_NEED_REST_3_HOURS	= 0x1000,
    PLAYER_FLAG_NEED_REST_5_HOURS	= 0x2000,
	PLAYER_FLAGS_PVP_STATUS_COOLDOWN= 0x40000,
	PLAYER_FLAGS_CUSTOM_FORCE_TALENTRESET = 0x20000000,
};

enum PlayerByteFlags
{
	//seems like having pet can also make us have flag 4 ? need more research
	PLAYER_BYTES_FLAG_HAS_PET			= 0x01, //client does not let you tame another pet
//	PLAYER_BYTES_FLAG_NO_HUMAN_CONTROL	= 0x04, //not sure, just guessing since it was there on logout
	PLAYER_BYTES_FLAG_HUMAN_CONTROL		= 0x08,
};

//#define PLAYER_IS_PVP_CLIENT_SIDE_FLAGS ( PLAYER_FLAG_PVP_TOGGLE | PLAYER_FLAGS_PVP_STATUS )
#define PLAYER_IS_PVP_CLIENT_SIDE_FLAGS ( PLAYER_FLAG_PVP_TOGGLE )

enum CharterTypes
{
	CHARTER_TYPE_GUILD			= 0,
	CHARTER_TYPE_ARENA_2V2		= 1,
	CHARTER_TYPE_ARENA_3V3		= 2,
	CHARTER_TYPE_ARENA_5V5		= 3,
	NUM_CHARTER_TYPES			= 4,
};

enum ArenaTeamTypes
{
	ARENA_TEAM_TYPE_2V2			= 0,
	ARENA_TEAM_TYPE_3V3			= 1,
	ARENA_TEAM_TYPE_5V5			= 2,
	NUM_ARENA_TEAM_TYPES		= 3,
};

enum CooldownTypes
{
	COOLDOWN_TYPE_SPELL			= 0,
	COOLDOWN_TYPE_CATEGORY		= 1,
	NUM_COOLDOWN_TYPES,
};

enum LootType
{
    LOOT_CORPSE                 = 1,
    LOOT_SKINNING               = 2,
    LOOT_FISHING                = 3,
    LOOT_PICKPOCKETING          = 2,                        // 4 unsupported by client, sending LOOT_SKINNING instead
    LOOT_DISENCHANTING          = 2,                        // 5 unsupported by client, sending LOOT_SKINNING instead
    LOOT_PROSPECTING            = 2,                        // 6 unsupported by client, sending LOOT_SKINNING instead
	LOOT_MILLING				= 2,
    LOOT_INSIGNIA               = 2                         // 7 unsupported by client, sending LOOT_SKINNING instead
};

enum ModType
{	
	MOD_MELEE	= 0,
	MOD_RANGED	= 1,
	MOD_SPELL	= 2
};

struct spells
{
	uint16  spellId;
	uint16  slotId;
};

#pragma pack(push,1)
class ActionButton
{
public:
	ActionButton()
	{
		Action = Type = Misc = 0;
	}
	uint16  Action;
	uint8   Type;
	uint8   Misc;
};
#pragma pack(pop)

enum ActionButtonType
{
    ACTION_BUTTON_SPELL     = 0x00,
    ACTION_BUTTON_C         = 0x01,                         // click?
    ACTION_BUTTON_EQSET     = 0x20,
    ACTION_BUTTON_MACRO     = 0x40,
    ACTION_BUTTON_CMACRO    = ACTION_BUTTON_C | ACTION_BUTTON_MACRO,
    ACTION_BUTTON_ITEM      = 0x80
};

struct AchievementVal
{
	AchievementVal(){ cur_value = completed_at_stamp = 0; }
	uint32 cur_value;
	uint32 completed_at_stamp;
};
#define ACHIEVEMENT_EVENT_ACTION_SET		0
#define ACHIEVEMENT_EVENT_ACTION_ADD		1
#define ACHIEVEMENT_EVENT_ACTION_SET_MAX	2

struct CreateInfo_ItemStruct
{
	uint32  protoid;
	uint8   slot;
	uint32  amount;
};

#if GM_STATISTICS_UPDATE_INTERVAL > 0 
struct GM_statistics
{
	GM_statistics() 
	{
		wisper_chat_messages = global_chat_messages = tickets_deleted = time_active = commands_executed = mails_sent = summons_made = appear_made = 0;
		walk_tel_distance_sum = 0.0f;
	}
	uint32 time_active;				//sum of seconds when the GM was not afk. Note that there are anti AFK modules
	uint32 commands_executed;		//all possible commands
	uint32 mails_sent;				//number of tickets he replied (probably)
	uint32 tickets_deleted;			//number of tickets deleted (not all replied?)
	float  walk_tel_distance_sum;	//this is a rough estimation how much he covered from world. If this is small then it is kinda bad, If it is large then he simply moves a lot
	uint32 global_chat_messages;	//got to love GMs that talk a lot
	uint32 wisper_chat_messages;	//maybe he is shy and talks a lot in private only
	uint32 summons_made;			//we all love GMs that talk to people face to face
	uint32 appear_made;				//we love even more GMs that simply appear at others and not harass them while they play
	uint32 next_afk_update;			//just so we do not spam DB. This should not make a bi difference anyway
	float  last_pos_x,last_pos_y;	//so we can create the distance diffs
};
#endif

struct CreateInfo_SkillStruct
{
	uint32  skillid;
	uint32  currentval;
	uint32  maxval;
};

struct CreateInfo_ActionBarStruct
{
	uint32  button;
	uint32  action;
	uint32  type;
	uint32  misc;
};

struct PlayerCreateInfo{
	uint8   index;
	uint8   race;
	uint32  factiontemplate;
	uint8   class_;
	uint32  mapId;
	uint32  zoneId;
	float   positionX;
	float   positionY;
	float   positionZ;
	uint16  displayId;
	uint8   strength;
	uint8   ability;
	uint8   stamina;
	uint8   intellect;
	uint8   spirit;
	uint32  health;
	uint32  mana;
	uint32  rage;
	uint32  focus;
	uint32  energy;
	uint32  attackpower;
	float   mindmg;
	float   maxdmg;
	std::list<CreateInfo_ItemStruct> items;
	std::list<CreateInfo_SkillStruct> skills;
	std::list<CreateInfo_ActionBarStruct> actionbars;
	std::set<uint32> spell_list;
	//uint32 item[10];
	//uint8 item_slot[10];
	//uint16 spell[10];
};

struct DamageSplit
{
	Player* caster;
	Aura*   aura;
	uint32  miscVal;
	union
	{
		uint32 damage;
		float damagePCT;
	};
};

struct LoginAura
{
	uint32	id;
	uint32	dur;
	bool	positive;
	uint32	charges;
	int32	mod_ammount;	//in case caster was someone else then keep mods
};

#define PLAYER_DODGE_CAP_PCT 80		//can't have dodge chance gigher then this. Implemented to avoid exploits
#define PLAYER_PARRY_CAP_PCT 80		//can't have dodge chance gigher then this. Implemented to avoid exploits
// Dodge ( class base ) - UNUSED, Warrior, Paladin, Hunter, Rogue, Priest, UNUSED, Shaman, Mage, Warlock, UNUSED, Druid
const float baseDodge[12] = { 0.0f, 0.7580f, 0.6520f, -5.4500f, -0.5900f, 3.1830f, 0.0f, 1.6750f, 3.4575f, 2.0350f, 0.0f, -1.8720f };

// Dodge ( class ratio ) - UNUSED, Warrior, Paladin, Hunter, Rogue, Priest, UNUSED, Shaman, Mage, Warlock, UNUSED, Druid
// TODO: get proper ratios for all levels, we only have values for level 70 currently
const float dodgeRatio[PLAYER_LEVEL_CAP][12] = {
{0.00000f, 5.00000f, 5.00000f, 5.00000f, 5.00000f, 5.00000f, 5.00000f, 5.00000f, 5.00000f, 5.00000f, 0.00000f, 5.00000f},
{0.00000f, 5.86746f, 5.59599f, 5.88845f, 5.46194f, 5.59599f, 5.86746f, 5.59599f, 5.58584f, 5.59599f, 0.00000f, 5.54265f},
{0.00000f, 6.73492f, 6.19198f, 6.77691f, 5.92389f, 6.19198f, 6.73492f, 6.19198f, 6.17169f, 6.19198f, 0.00000f, 6.08531f},
{0.00000f, 7.60238f, 6.78797f, 7.66536f, 6.38583f, 6.78797f, 7.60238f, 6.78797f, 6.75754f, 6.78797f, 0.00000f, 6.62797f},
{0.00000f, 8.46984f, 7.38396f, 8.55382f, 6.84778f, 7.38396f, 8.46984f, 7.38396f, 7.34339f, 7.38396f, 0.00000f, 7.17063f},
{0.00000f, 9.33730f, 7.97995f, 9.44227f, 7.30973f, 7.97995f, 9.33730f, 7.97995f, 7.92924f, 7.97995f, 0.00000f, 7.71329f},
{0.00000f, 10.2047f, 8.57594f, 10.3307f, 7.77167f, 8.57594f, 10.2047f, 8.57594f, 8.51509f, 8.57594f, 0.00000f, 8.25594f},
{0.00000f, 11.0722f, 9.17194f, 11.2191f, 8.23362f, 9.17194f, 11.0722f, 9.17194f, 9.10094f, 9.17194f, 0.00000f, 8.79860f},
{0.00000f, 11.9396f, 9.76793f, 12.1076f, 8.69557f, 9.76793f, 11.9396f, 9.76793f, 9.68678f, 9.76793f, 0.00000f, 9.34126f},
{0.00000f, 12.8071f, 10.3639f, 12.9960f, 9.15751f, 10.3639f, 12.8071f, 10.3639f, 10.2726f, 10.3639f, 0.00000f, 9.88392f},
{0.00000f, 13.6746f, 10.9599f, 13.8845f, 9.61946f, 10.9599f, 13.6746f, 10.9599f, 10.8584f, 10.9599f, 0.00000f, 10.4265f},
{0.00000f, 14.5420f, 11.5559f, 14.7730f, 10.0814f, 11.5559f, 14.5420f, 11.5559f, 11.4443f, 11.5559f, 0.00000f, 10.9692f},
{0.00000f, 15.4095f, 12.1518f, 15.6614f, 10.5433f, 12.1518f, 15.4095f, 12.1518f, 12.0301f, 12.1518f, 0.00000f, 11.5118f},
{0.00000f, 16.2769f, 12.7478f, 16.5499f, 11.0053f, 12.7478f, 16.2769f, 12.7478f, 12.6160f, 12.7478f, 0.00000f, 12.0545f},
{0.00000f, 17.1444f, 13.3438f, 17.4383f, 11.4672f, 13.3438f, 17.1444f, 13.3438f, 13.2018f, 13.3438f, 0.00000f, 12.5972f},
{0.00000f, 18.0119f, 13.9398f, 18.3268f, 11.9291f, 13.9398f, 18.0119f, 13.9398f, 13.7877f, 13.9398f, 0.00000f, 13.1398f},
{0.00000f, 18.8793f, 14.5358f, 19.2152f, 12.3911f, 14.5358f, 18.8793f, 14.5358f, 14.3735f, 14.5358f, 0.00000f, 13.6825f},
{0.00000f, 19.7468f, 15.1318f, 20.1037f, 12.8530f, 15.1318f, 19.7468f, 15.1318f, 14.9594f, 15.1318f, 0.00000f, 14.2251f},
{0.00000f, 20.6142f, 15.7278f, 20.9921f, 13.3150f, 15.7278f, 20.6142f, 15.7278f, 15.5452f, 15.7278f, 0.00000f, 14.7678f},
{0.00000f, 21.4817f, 16.3238f, 21.8806f, 13.7769f, 16.3238f, 21.4817f, 16.3238f, 16.1311f, 16.3238f, 0.00000f, 15.3105f},
{0.00000f, 22.3492f, 16.9198f, 22.7691f, 14.2389f, 16.9198f, 22.3492f, 16.9198f, 16.7169f, 16.9198f, 0.00000f, 15.8531f},
{0.00000f, 23.2166f, 17.5158f, 23.6575f, 14.7008f, 17.5158f, 23.2166f, 17.5158f, 17.3028f, 17.5158f, 0.00000f, 16.3958f},
{0.00000f, 24.0841f, 18.1118f, 24.5460f, 15.1628f, 18.1118f, 24.0841f, 18.1118f, 17.8886f, 18.1118f, 0.00000f, 16.9384f},
{0.00000f, 24.9516f, 18.7078f, 25.4344f, 15.6247f, 18.7078f, 24.9516f, 18.7078f, 18.4745f, 18.7078f, 0.00000f, 17.4811f},
{0.00000f, 25.8190f, 19.3037f, 26.3229f, 16.0867f, 19.3037f, 25.8190f, 19.3037f, 19.0603f, 19.3037f, 0.00000f, 18.0237f},
{0.00000f, 26.6865f, 19.8997f, 27.2113f, 16.5486f, 19.8997f, 26.6865f, 19.8997f, 19.6462f, 19.8997f, 0.00000f, 18.5664f},
{0.00000f, 27.5539f, 20.4957f, 28.0998f, 17.0106f, 20.4957f, 27.5539f, 20.4957f, 20.2320f, 20.4957f, 0.00000f, 19.1091f},
{0.00000f, 28.4214f, 21.0917f, 28.9882f, 17.4725f, 21.0917f, 28.4214f, 21.0917f, 20.8179f, 21.0917f, 0.00000f, 19.6517f},
{0.00000f, 29.2889f, 21.6877f, 29.8767f, 17.9345f, 21.6877f, 29.2889f, 21.6877f, 21.4037f, 21.6877f, 0.00000f, 20.1944f},
{0.00000f, 30.1563f, 22.2837f, 30.7652f, 18.3964f, 22.2837f, 30.1563f, 22.2837f, 21.9896f, 22.2837f, 0.00000f, 20.7370f},
{0.00000f, 31.0238f, 22.8797f, 31.6536f, 18.8583f, 22.8797f, 31.0238f, 22.8797f, 22.5754f, 22.8797f, 0.00000f, 21.2797f},
{0.00000f, 31.8912f, 23.4757f, 32.5421f, 19.3203f, 23.4757f, 31.8912f, 23.4757f, 23.1613f, 23.4757f, 0.00000f, 21.8224f},
{0.00000f, 32.7587f, 24.0717f, 33.4305f, 19.7822f, 24.0717f, 32.7587f, 24.0717f, 23.7471f, 24.0717f, 0.00000f, 22.3650f},
{0.00000f, 33.6262f, 24.6677f, 34.3190f, 20.2442f, 24.6677f, 33.6262f, 24.6677f, 24.3330f, 24.6677f, 0.00000f, 22.9077f},
{0.00000f, 34.4936f, 25.2637f, 35.2074f, 20.7061f, 25.2637f, 34.4936f, 25.2637f, 24.9188f, 25.2637f, 0.00000f, 23.4503f},
{0.00000f, 35.3611f, 25.8597f, 36.0959f, 21.1681f, 25.8597f, 35.3611f, 25.8597f, 25.5047f, 25.8597f, 0.00000f, 23.9930f},
{0.00000f, 36.2285f, 26.4556f, 36.9843f, 21.6300f, 26.4556f, 36.2285f, 26.4556f, 26.0905f, 26.4556f, 0.00000f, 24.5356f},
{0.00000f, 37.0960f, 27.0516f, 37.8728f, 22.0920f, 27.0516f, 37.0960f, 27.0516f, 26.6764f, 27.0516f, 0.00000f, 25.0783f},
{0.00000f, 37.9635f, 27.6476f, 38.7613f, 22.5539f, 27.6476f, 37.9635f, 27.6476f, 27.2622f, 27.6476f, 0.00000f, 25.6210f},
{0.00000f, 38.8309f, 28.2436f, 39.6497f, 23.0159f, 28.2436f, 38.8309f, 28.2436f, 27.8481f, 28.2436f, 0.00000f, 26.1636f},
{0.00000f, 39.6984f, 28.8396f, 40.5382f, 23.4778f, 28.8396f, 39.6984f, 28.8396f, 28.4339f, 28.8396f, 0.00000f, 26.7063f},
{0.00000f, 40.5658f, 29.4356f, 41.4266f, 23.9398f, 29.4356f, 40.5658f, 29.4356f, 29.0197f, 29.4356f, 0.00000f, 27.2489f},
{0.00000f, 41.4333f, 30.0316f, 42.3151f, 24.4017f, 30.0316f, 41.4333f, 30.0316f, 29.6056f, 30.0316f, 0.00000f, 27.7916f},
{0.00000f, 42.3008f, 30.6276f, 43.2035f, 24.8637f, 30.6276f, 42.3008f, 30.6276f, 30.1914f, 30.6276f, 0.00000f, 28.3343f},
{0.00000f, 43.1682f, 31.2236f, 44.0920f, 25.3256f, 31.2236f, 43.1682f, 31.2236f, 30.7773f, 31.2236f, 0.00000f, 28.8769f},
{0.00000f, 44.0357f, 31.8196f, 44.9804f, 25.7875f, 31.8196f, 44.0357f, 31.8196f, 31.3631f, 31.8196f, 0.00000f, 29.4196f},
{0.00000f, 44.9032f, 32.4156f, 45.8689f, 26.2495f, 32.4156f, 44.9032f, 32.4156f, 31.9490f, 32.4156f, 0.00000f, 29.9622f},
{0.00000f, 45.7706f, 33.0116f, 46.7573f, 26.7114f, 33.0116f, 45.7706f, 33.0116f, 32.5348f, 33.0116f, 0.00000f, 30.5049f},
{0.00000f, 46.6381f, 33.6075f, 47.6458f, 27.1734f, 33.6075f, 46.6381f, 33.6075f, 33.1207f, 33.6075f, 0.00000f, 31.0475f},
{0.00000f, 47.5055f, 34.2035f, 48.5343f, 27.6353f, 34.2035f, 47.5055f, 34.2035f, 33.7065f, 34.2035f, 0.00000f, 31.5902f},
{0.00000f, 48.3730f, 34.7995f, 49.4227f, 28.0973f, 34.7995f, 48.3730f, 34.7995f, 34.2924f, 34.7995f, 0.00000f, 32.1329f},
{0.00000f, 49.2405f, 35.3955f, 50.3112f, 28.5592f, 35.3955f, 49.2405f, 35.3955f, 34.8782f, 35.3955f, 0.00000f, 32.6755f},
{0.00000f, 50.1079f, 35.9915f, 51.1996f, 29.0212f, 35.9915f, 50.1079f, 35.9915f, 35.4641f, 35.9915f, 0.00000f, 33.2182f},
{0.00000f, 50.9754f, 36.5875f, 52.0881f, 29.4831f, 36.5875f, 50.9754f, 36.5875f, 36.0499f, 36.5875f, 0.00000f, 33.7608f},
{0.00000f, 51.8428f, 37.1835f, 52.9765f, 29.9451f, 37.1835f, 51.8428f, 37.1835f, 36.6358f, 37.1835f, 0.00000f, 34.3035f},
{0.00000f, 52.7103f, 37.7795f, 53.8650f, 30.4070f, 37.7795f, 52.7103f, 37.7795f, 37.2216f, 37.7795f, 0.00000f, 34.8462f},
{0.00000f, 53.5778f, 38.3755f, 54.7534f, 30.8690f, 38.3755f, 53.5778f, 38.3755f, 37.8075f, 38.3755f, 0.00000f, 35.3888f},
{0.00000f, 54.4452f, 38.9715f, 55.6419f, 31.3309f, 38.9715f, 54.4452f, 38.9715f, 38.3933f, 38.9715f, 0.00000f, 35.9315f},
{0.00000f, 55.3127f, 39.5675f, 56.5304f, 31.7928f, 39.5675f, 55.3127f, 39.5675f, 38.9792f, 39.5675f, 0.00000f, 36.4741f},
{0.00000f, 56.1801f, 40.1635f, 57.4188f, 32.2548f, 40.1635f, 56.1801f, 40.1635f, 39.5650f, 40.1635f, 0.00000f, 37.0168f},
{0.00000f, 57.0476f, 40.7594f, 58.3073f, 32.7167f, 40.7594f, 57.0476f, 40.7594f, 40.1509f, 40.7594f, 0.00000f, 37.5594f},
{0.00000f, 57.9151f, 41.3554f, 59.1957f, 33.1787f, 41.3554f, 57.9151f, 41.3554f, 40.7367f, 41.3554f, 0.00000f, 38.1021f},
{0.00000f, 58.7825f, 41.9514f, 60.0842f, 33.6406f, 41.9514f, 58.7825f, 41.9514f, 41.3226f, 41.9514f, 0.00000f, 38.6448f},
{0.00000f, 59.6500f, 42.5474f, 60.9726f, 34.1026f, 42.5474f, 59.6500f, 42.5474f, 41.9084f, 42.5474f, 0.00000f, 39.1874f},
{0.00000f, 60.5174f, 43.1434f, 61.8611f, 34.5645f, 43.1434f, 60.5174f, 43.1434f, 42.4943f, 43.1434f, 0.00000f, 39.7301f},
{0.00000f, 61.3849f, 43.7394f, 62.7495f, 35.0265f, 43.7394f, 61.3849f, 43.7394f, 43.0801f, 43.7394f, 0.00000f, 40.2727f},
{0.00000f, 62.2524f, 44.3354f, 63.6380f, 35.4884f, 44.3354f, 62.2524f, 44.3354f, 43.6660f, 44.3354f, 0.00000f, 40.8154f},
{0.00000f, 63.1198f, 44.9314f, 64.5265f, 35.9504f, 44.9314f, 63.1198f, 44.9314f, 44.2518f, 44.9314f, 0.00000f, 41.3581f},
{0.00000f, 63.9873f, 45.5274f, 65.4149f, 36.4123f, 45.5274f, 63.9873f, 45.5274f, 44.8377f, 45.5274f, 0.00000f, 41.9007f},
{0.00000f, 64.8548f, 46.1234f, 66.3034f, 36.8743f, 46.1234f, 64.8548f, 46.1234f, 45.4235f, 46.1234f, 0.00000f, 42.4434f},
{0.00000f, 65.7222f, 46.7194f, 67.1918f, 37.3362f, 46.7194f, 65.7222f, 46.7194f, 46.0094f, 46.7194f, 0.00000f, 42.9860f},
{0.00000f, 66.5897f, 47.3154f, 68.0803f, 37.7982f, 47.3154f, 66.5897f, 47.3154f, 46.5952f, 47.3154f, 0.00000f, 43.5287f},
{0.00000f, 67.4571f, 47.9113f, 68.9687f, 38.2601f, 47.9113f, 67.4571f, 47.9113f, 47.1811f, 47.9113f, 0.00000f, 44.0713f},
{0.00000f, 68.3246f, 48.5073f, 69.8572f, 38.7220f, 48.5073f, 68.3246f, 48.5073f, 47.7669f, 48.5073f, 0.00000f, 44.6140f},
{0.00000f, 69.1921f, 49.1033f, 70.7456f, 39.1840f, 49.1033f, 69.1921f, 49.1033f, 48.3528f, 49.1033f, 0.00000f, 45.1567f},
{0.00000f, 70.0595f, 49.6993f, 71.6341f, 39.6459f, 49.6993f, 70.0595f, 49.6993f, 48.9386f, 49.6993f, 0.00000f, 45.6993f},
{0.00000f, 70.9270f, 50.2953f, 72.5226f, 40.1079f, 50.2953f, 70.9270f, 50.2953f, 49.5245f, 50.2953f, 0.00000f, 46.2420f},
{0.00000f, 71.7944f, 50.8913f, 73.4110f, 40.5698f, 50.8913f, 71.7944f, 50.8913f, 50.1103f, 50.8913f, 0.00000f, 46.7846f},
{0.00000f, 72.6619f, 51.4873f, 74.2995f, 41.0318f, 51.4873f, 72.6619f, 51.4873f, 50.6962f, 51.4873f, 0.00000f, 47.3273f},
{0.00000f, 73.5294f, 52.0833f, 75.1879f, 41.4937f, 52.0833f, 73.5294f, 52.0833f, 51.2820f, 52.0833f, 0.00000f, 47.8700f},
{0.00000f, 74.3968f, 52.6793f, 76.0764f, 41.9557f, 52.6793f, 74.3968f, 52.6793f, 51.8678f, 52.6793f, 0.00000f, 48.4126f},
{0.00000f, 75.2643f, 53.2753f, 76.9648f, 42.4176f, 53.2753f, 75.2643f, 53.2753f, 52.4537f, 53.2753f, 0.00000f, 48.9553f},
{0.00000f, 76.1317f, 53.8713f, 77.8533f, 42.8796f, 53.8713f, 76.1317f, 53.8713f, 53.0395f, 53.8713f, 0.00000f, 49.4979f},
{0.00000f, 76.9992f, 54.4672f, 78.7417f, 43.3415f, 54.4672f, 76.9992f, 54.4672f, 53.6254f, 54.4672f, 0.00000f, 50.0406f},
{0.00000f, 77.8667f, 55.0632f, 79.6302f, 43.8035f, 55.0632f, 77.8667f, 55.0632f, 54.2112f, 55.0632f, 0.00000f, 50.5832f},
{0.00000f, 78.7341f, 55.6592f, 80.5187f, 44.2654f, 55.6592f, 78.7341f, 55.6592f, 54.7971f, 55.6592f, 0.00000f, 51.1259f},
{0.00000f, 79.6016f, 56.2552f, 81.4071f, 44.7274f, 56.2552f, 79.6016f, 56.2552f, 55.3829f, 56.2552f, 0.00000f, 51.6686f},
{0.00000f, 80.4690f, 56.8512f, 82.2956f, 45.1893f, 56.8512f, 80.4690f, 56.8512f, 55.9688f, 56.8512f, 0.00000f, 52.2112f},
{0.00000f, 81.3365f, 57.4472f, 83.1840f, 45.6512f, 57.4472f, 81.3365f, 57.4472f, 56.5546f, 57.4472f, 0.00000f, 52.7539f},
{0.00000f, 82.2040f, 58.0432f, 84.0725f, 46.1132f, 58.0432f, 82.2040f, 58.0432f, 57.1405f, 58.0432f, 0.00000f, 53.2965f},
{0.00000f, 83.0714f, 58.6392f, 84.9609f, 46.5751f, 58.6392f, 83.0714f, 58.6392f, 57.7263f, 58.6392f, 0.00000f, 53.8392f},
{0.00000f, 83.9389f, 59.2352f, 85.8494f, 47.0371f, 59.2352f, 83.9389f, 59.2352f, 58.3122f, 59.2352f, 0.00000f, 54.3818f},
{0.00000f, 84.8064f, 59.8312f, 86.7378f, 47.4990f, 59.8312f, 84.8064f, 59.8312f, 58.8980f, 59.8312f, 0.00000f, 54.9245f},
{0.00000f, 85.6738f, 60.4272f, 87.6263f, 47.9610f, 60.4272f, 85.6738f, 60.4272f, 59.4839f, 60.4272f, 0.00000f, 55.4672f},
{0.00000f, 86.5413f, 61.0232f, 88.5147f, 48.4229f, 61.0232f, 86.5413f, 61.0232f, 60.0697f, 61.0232f, 0.00000f, 56.0098f},
{0.00000f, 87.4087f, 61.6191f, 89.4032f, 48.8849f, 61.6191f, 87.4087f, 61.6191f, 60.6556f, 61.6191f, 0.00000f, 56.5525f},
{0.00000f, 88.2762f, 62.2151f, 90.2917f, 49.3468f, 62.2151f, 88.2762f, 62.2151f, 61.2414f, 62.2151f, 0.00000f, 57.0951f},
{0.00000f, 89.1437f, 62.8111f, 91.1801f, 49.8088f, 62.8111f, 89.1437f, 62.8111f, 61.8273f, 62.8111f, 0.00000f, 57.6378f},
{0.00000f, 90.0111f, 63.4071f, 92.0686f, 50.2707f, 63.4071f, 90.0111f, 63.4071f, 62.4131f, 63.4071f, 0.00000f, 58.1805f},
{0.00000f, 90.8786f, 64.0031f, 92.9570f, 50.7327f, 64.0031f, 90.8786f, 64.0031f, 62.9990f, 64.0031f, 0.00000f, 58.7231f},
{0.00000f, 91.7460f, 64.5991f, 93.8455f, 51.1946f, 64.5991f, 91.7460f, 64.5991f, 63.5848f, 64.5991f, 0.00000f, 59.2658f},
{0.00000f, 92.6135f, 65.1951f, 94.7339f, 51.6565f, 65.1951f, 92.6135f, 65.1951f, 64.1707f, 65.1951f, 0.00000f, 59.8084f},
{0.00000f, 93.4810f, 65.7911f, 95.6224f, 52.1185f, 65.7911f, 93.4810f, 65.7911f, 64.7565f, 65.7911f, 0.00000f, 60.3511f},
{0.00000f, 94.3484f, 66.3871f, 96.5108f, 52.5804f, 66.3871f, 94.3484f, 66.3871f, 65.3424f, 66.3871f, 0.00000f, 60.8937f},
{0.00000f, 95.2159f, 66.9831f, 97.3993f, 53.0424f, 66.9831f, 95.2159f, 66.9831f, 65.9282f, 66.9831f, 0.00000f, 61.4364f},
{0.00000f, 96.0833f, 67.5791f, 98.2878f, 53.5043f, 67.5791f, 96.0833f, 67.5791f, 66.5141f, 67.5791f, 0.00000f, 61.9791f},
{0.00000f, 96.9508f, 68.1751f, 99.1762f, 53.9663f, 68.1751f, 96.9508f, 68.1751f, 67.0999f, 68.1751f, 0.00000f, 62.5217f},
{0.00000f, 97.8183f, 68.7710f, 100.064f, 54.4282f, 68.7710f, 97.8183f, 68.7710f, 67.6858f, 68.7710f, 0.00000f, 63.0644f},
{0.00000f, 98.6857f, 69.3670f, 100.953f, 54.8902f, 69.3670f, 98.6857f, 69.3670f, 68.2716f, 69.3670f, 0.00000f, 63.6070f},
{0.00000f, 99.5532f, 69.9630f, 101.841f, 55.3521f, 69.9630f, 99.5532f, 69.9630f, 68.8575f, 69.9630f, 0.00000f, 64.1497f},
{0.00000f, 100.420f, 70.5590f, 102.730f, 55.8141f, 70.5590f, 100.420f, 70.5590f, 69.4433f, 70.5590f, 0.00000f, 64.6924f},
{0.00000f, 101.288f, 71.1550f, 103.618f, 56.2760f, 71.1550f, 101.288f, 71.1550f, 70.0292f, 71.1550f, 0.00000f, 65.2350f},
{0.00000f, 102.155f, 71.7510f, 104.506f, 56.7380f, 71.7510f, 102.155f, 71.7510f, 70.6150f, 71.7510f, 0.00000f, 65.7777f},
{0.00000f, 103.023f, 72.3470f, 105.395f, 57.1999f, 72.3470f, 103.023f, 72.3470f, 71.2009f, 72.3470f, 0.00000f, 66.3203f},
{0.00000f, 103.890f, 72.9430f, 106.283f, 57.6619f, 72.9430f, 103.890f, 72.9430f, 71.7867f, 72.9430f, 0.00000f, 66.8630f},
{0.00000f, 104.758f, 73.5390f, 107.172f, 58.1238f, 73.5390f, 104.758f, 73.5390f, 72.3726f, 73.5390f, 0.00000f, 67.4056f},
{0.00000f, 105.625f, 74.1350f, 108.060f, 58.5857f, 74.1350f, 105.625f, 74.1350f, 72.9584f, 74.1350f, 0.00000f, 67.9483f},
{0.00000f, 106.492f, 74.7310f, 108.949f, 59.0477f, 74.7310f, 106.492f, 74.7310f, 73.5443f, 74.7310f, 0.00000f, 68.4910f},
{0.00000f, 107.360f, 75.3270f, 109.837f, 59.5096f, 75.3270f, 107.360f, 75.3270f, 74.1301f, 75.3270f, 0.00000f, 69.0336f},
{0.00000f, 108.227f, 75.9229f, 110.726f, 59.9716f, 75.9229f, 108.227f, 75.9229f, 74.7160f, 75.9229f, 0.00000f, 69.5763f},
{0.00000f, 109.095f, 76.5189f, 111.614f, 60.4335f, 76.5189f, 109.095f, 76.5189f, 75.3018f, 76.5189f, 0.00000f, 70.1189f},
{0.00000f, 109.962f, 77.1149f, 112.503f, 60.8955f, 77.1149f, 109.962f, 77.1149f, 75.8876f, 77.1149f, 0.00000f, 70.6616f},
{0.00000f, 110.830f, 77.7109f, 113.391f, 61.3574f, 77.7109f, 110.830f, 77.7109f, 76.4735f, 77.7109f, 0.00000f, 71.2043f},
{0.00000f, 111.697f, 78.3069f, 114.280f, 61.8194f, 78.3069f, 111.697f, 78.3069f, 77.0593f, 78.3069f, 0.00000f, 71.7469f},
{0.00000f, 112.565f, 78.9029f, 115.168f, 62.2813f, 78.9029f, 112.565f, 78.9029f, 77.6452f, 78.9029f, 0.00000f, 72.2896f},
{0.00000f, 113.432f, 79.4989f, 116.056f, 62.7433f, 79.4989f, 113.432f, 79.4989f, 78.2310f, 79.4989f, 0.00000f, 72.8322f},
{0.00000f, 114.300f, 80.0949f, 116.945f, 63.2052f, 80.0949f, 114.300f, 80.0949f, 78.8169f, 80.0949f, 0.00000f, 73.3749f},
{0.00000f, 115.167f, 80.6909f, 117.833f, 63.6672f, 80.6909f, 115.167f, 80.6909f, 79.4027f, 80.6909f, 0.00000f, 73.9175f},
{0.00000f, 116.034f, 81.2869f, 118.722f, 64.1291f, 81.2869f, 116.034f, 81.2869f, 79.9886f, 81.2869f, 0.00000f, 74.4602f},
{0.00000f, 116.902f, 81.8829f, 119.610f, 64.5911f, 81.8829f, 116.902f, 81.8829f, 80.5744f, 81.8829f, 0.00000f, 75.0029f},
{0.00000f, 117.769f, 82.4789f, 120.499f, 65.0530f, 82.4789f, 117.769f, 82.4789f, 81.1603f, 82.4789f, 0.00000f, 75.5455f},
{0.00000f, 118.637f, 83.0748f, 121.387f, 65.5149f, 83.0748f, 118.637f, 83.0748f, 81.7461f, 83.0748f, 0.00000f, 76.0882f},
{0.00000f, 119.504f, 83.6708f, 122.276f, 65.9769f, 83.6708f, 119.504f, 83.6708f, 82.3320f, 83.6708f, 0.00000f, 76.6308f},
{0.00000f, 120.372f, 84.2668f, 123.164f, 66.4388f, 84.2668f, 120.372f, 84.2668f, 82.9178f, 84.2668f, 0.00000f, 77.1735f},
{0.00000f, 121.239f, 84.8628f, 124.053f, 66.9008f, 84.8628f, 121.239f, 84.8628f, 83.5037f, 84.8628f, 0.00000f, 77.7162f},
{0.00000f, 122.107f, 85.4588f, 124.941f, 67.3627f, 85.4588f, 122.107f, 85.4588f, 84.0895f, 85.4588f, 0.00000f, 78.2588f},
{0.00000f, 122.974f, 86.0548f, 125.829f, 67.8247f, 86.0548f, 122.974f, 86.0548f, 84.6754f, 86.0548f, 0.00000f, 78.8015f},
};

/*
Exalted	        1,000	 Access to racial mounts. Capped at 999.7
Revered	        21,000	 Heroic mode keys for Outland dungeons
Honored	        12,000	 10% discount from faction vendors
Friendly	    6,000
Neutral	        3,000
Unfriendly	    3,000	 Cannot buy, sell or interact.
Hostile	        3,000	 You will always be attacked on sight
Hated	        36,000 
*/
enum FactionRating
{
	HATED,
	HOSTILE,
	UNFRIENDLY,
	NEUTRAL,
	FRIENDLY,
	HONORED,
	REVERED,
	EXALTED
};
struct FactionReputation
{
	int32 standing;
	uint8 flag;
	int32 baseStanding;
	ARCEMU_INLINE int32 CalcStanding() { return standing - baseStanding; }
	ARCEMU_INLINE bool Positive() { return standing >= 0; }
};

typedef HM_NAMESPACE::hash_map<uint32, uint32> PlayerInstanceMap;
struct PlayerInfo
{
	~PlayerInfo();
	uint32 guid;
	uint32 acct;
	char * name;
	uint32 race;
	uint32 gender;
	uint32 cl;
	uint32 team;
	
	time_t lastOnline;
	uint32 lastZone;
	uint32 lastLevel;
	Group * m_Group;
	int8 subGroup;
	Mutex savedInstanceIdsLock;
	//PlayerInstanceMap savedInstanceIds[NUM_INSTANCE_MODES];
	tr1::array< PlayerInstanceMap, NUM_INSTANCE_MODES > savedInstanceIds;
#ifdef VOICE_CHAT
	int8 groupVoiceId;
#endif

	Player * m_loggedInPlayer;
	Guild * guild;
	GuildRank * guildRank;
	GuildMember * guildMember;
};
struct PlayerPet
{
	string name;
	uint32 entry;
	string fields;
	uint32 xp;
	bool active;
	char stablestate;
	uint32 number;
	uint32 level;
	uint32 loyaltyxp;
	uint32 happinessupdate;
	string actionbar;
	bool summon;
//	uint32 loyaltypts;
//	uint32 loyaltyupdate;
//	char loyaltylvl;
	time_t reset_time;
	uint32 reset_cost;
	uint32 spellid;
};
enum MeetingStoneQueueStatus
{
	MEETINGSTONE_STATUS_NONE								= 0,
	MEETINGSTONE_STATUS_JOINED_MEETINGSTONE_QUEUE_FOR	   = 1,
	MEETINGSTONE_STATUS_PARTY_MEMBER_LEFT_LFG			   = 2,
	MEETINGSTONE_STATUS_PARTY_MEMBER_REMOVED_PARTY_REMOVED  = 3,
	MEETINGSTONE_STATUS_LOOKING_FOR_NEW_PARTY_IN_QUEUE	  = 4,
	MEETINGSTONE_STATUS_NONE_UNK							= 5,
};
enum ItemPushResultTypes
{
	ITEM_PUSH_TYPE_LOOT			 = 0x00000000,
	ITEM_PUSH_TYPE_RECEIVE		  = 0x00000001,
	ITEM_PUSH_TYPE_CREATE		   = 0x00000002,
};
struct WeaponModifier
{
	int32		wclass;
	int32		subclass;
	float		value;
	SpellEntry	*spellentry;
};
struct PetActionBar
{
	uint32 spell[10];
};

class Spell;
class Item;
class Container;
class WorldSession;
class ItemInterface;
class GossipMenu;
class SpeedCheatDetector;
struct TaxiPathNode;

#define RESTSTATE_RESTED			 1
#define RESTSTATE_NORMAL			 2
#define RESTSTATE_TIRED100		     3
#define RESTSTATE_TIRED50			 4
#define RESTSTATE_EXHAUSTED		     5
#define UNDERWATERSTATE_NONE		 0
#define UNDERWATERSTATE_SWIMMING	 1
#define UNDERWATERSTATE_UNDERWATER   2
#define UNDERWATERSTATE_RECOVERING   4
#define UNDERWATERSTATE_TAKINGDAMAGE 8
#define UNDERWATERSTATE_FATIGUE	     16
#define UNDERWATERSTATE_LAVA		 32
#define UNDERWATERSTATE_SLIME		 64

enum TRADE_STATUS
{
	TRADE_STATUS_PLAYER_BUSY	    = 0x00,
	TRADE_STATUS_PROPOSED		    = 0x01,
	TRADE_STATUS_INITIATED		    = 0x02,
	TRADE_STATUS_CANCELLED		    = 0x03,
	TRADE_STATUS_ACCEPTED		    = 0x04,
	TRADE_STATUS_ALREADY_TRADING    = 0x05,
	TRADE_STATUS_PLAYER_NOT_FOUND   = 0x06,
	TRADE_STATUS_STATE_CHANGED	    = 0x07,
	TRADE_STATUS_COMPLETE		    = 0x08,
	TRADE_STATUS_UNACCEPTED		    = 0x09,
	TRADE_STATUS_TOO_FAR_AWAY	    = 0x0A,
	TRADE_STATUS_WRONG_FACTION	    = 0x0B,
	TRADE_STATUS_FAILED			    = 0x0C,
	TRADE_STATUS_DEAD			    = 0x0D,
	TRADE_STATUS_PETITION		    = 0x0E,
	TRADE_STATUS_PLAYER_IGNORED	    = 0x0F,
    TRADE_STATUS_TARGET_STUNNED		= 0x10,
    TRADE_STATUS_YOU_DEAD			= 0x11,
    TRADE_STATUS_TARGET_DEAD		= 0x12,
    TRADE_STATUS_YOU_LOGOUT			= 0x13,
    TRADE_STATUS_TARGET_LOGOUT		= 0x14,
    TRADE_STATUS_TRIAL_ACCOUNT		= 0x15,                       // Trial accounts can not perform that action
    TRADE_STATUS_ONLY_CONJURED		= 0x16                        // You can only trade conjured items... (cross realm BG related).
};
enum TRADE_DATA
{
	TRADE_GIVE		= 0x00,
	TRADE_RECEIVE	 = 0x01,
};
enum DUEL_STATUS
{
	DUEL_STATUS_OUTOFBOUNDS,
	DUEL_STATUS_INBOUNDS
};
enum DUEL_STATE
{
	DUEL_STATE_REQUESTED,
	DUEL_STATE_STARTED,
	DUEL_STATE_FINISHED
};
enum DUEL_WINNER
{
	DUEL_WINNER_KNOCKOUT,
	DUEL_WINNER_RETREAT,
};
#define PLAYER_ATTACK_TIMEOUT_INTERVAL	5000
#define PLAYER_FORCED_RESURECT_INTERVAL	360000 // 1000*60*6= 6 minutes 

struct PlayerSkill
{
	skilllineentry * Skill;
	uint32 CurrentValue;
	uint32 MaximumValue;
	uint32 BonusValue;
	float GetSkillUpChance();
	void Reset(uint32 Id);
};

enum SPELL_INDEX
{
	SPELL_TYPE_INDEX_MARK			= 1,
	SPELL_TYPE_INDEX_POLYMORPH		= 2,
	SPELL_TYPE_INDEX_FEAR			= 3,
	SPELL_TYPE_INDEX_SAP			= 4,
	SPELL_TYPE_INDEX_SCARE_BEAST	= 5,
	SPELL_TYPE_INDEX_HIBERNATE		= 6,
	SPELL_TYPE_INDEX_EARTH_SHIELD	= 7,
	SPELL_TYPE_INDEX_CYCLONE		= 8,
	SPELL_TYPE_INDEX_BANISH			= 9,
	SPELL_TYPE_INDEX_JUDGEMENT		= 10,	
	SPELL_TYPE_INDEX_FOCUS_MAGIC	= 11,	
	SPELL_TYPE_INDEX_BEACON_OF_LIGHT	= 12,	
	SPELL_TYPE_INDEX_SACRED_SHIELD	= 13,	
	NUM_SPELL_TYPE_INDEX,
};

enum SPELL_INDEX2
{
	SPELL_TYPE2_PALADIN_AURA			= 1,
};

#define PLAYER_RATING_MODIFIER_RANGED_SKILL						(PLAYER_FIELD_COMBAT_RATING_1 + 0)
#define PLAYER_RATING_MODIFIER_DEFENCE							(PLAYER_FIELD_COMBAT_RATING_1 + 1)
#define PLAYER_RATING_MODIFIER_DODGE							(PLAYER_FIELD_COMBAT_RATING_1 + 2)
#define PLAYER_RATING_MODIFIER_PARRY							(PLAYER_FIELD_COMBAT_RATING_1 + 3)
#define PLAYER_RATING_MODIFIER_BLOCK							(PLAYER_FIELD_COMBAT_RATING_1 + 4)
#define PLAYER_RATING_MODIFIER_MELEE_HIT						(PLAYER_FIELD_COMBAT_RATING_1 + 5)
#define PLAYER_RATING_MODIFIER_RANGED_HIT						(PLAYER_FIELD_COMBAT_RATING_1 + 6)
#define PLAYER_RATING_MODIFIER_SPELL_HIT						(PLAYER_FIELD_COMBAT_RATING_1 + 7)
#define PLAYER_RATING_MODIFIER_MELEE_CRIT						(PLAYER_FIELD_COMBAT_RATING_1 + 8)
#define PLAYER_RATING_MODIFIER_RANGED_CRIT						(PLAYER_FIELD_COMBAT_RATING_1 + 9)
#define PLAYER_RATING_MODIFIER_SPELL_CRIT						(PLAYER_FIELD_COMBAT_RATING_1 + 10)
#define PLAYER_RATING_MODIFIER_MELEE_HIT_AVOIDANCE				(PLAYER_FIELD_COMBAT_RATING_1 + 11) // Not 100% sure but the numbers line up
#define PLAYER_RATING_MODIFIER_RANGED_HIT_AVOIDANCE				(PLAYER_FIELD_COMBAT_RATING_1 + 12) // GUESSED
#define PLAYER_RATING_MODIFIER_SPELL_HIT_AVOIDANCE				(PLAYER_FIELD_COMBAT_RATING_1 + 13) // GUESSED
#define PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE			(PLAYER_FIELD_COMBAT_RATING_1 + 14)
#define PLAYER_RATING_MODIFIER_RANGED_CRIT_RESILIENCE			(PLAYER_FIELD_COMBAT_RATING_1 + 15)
#define PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE			(PLAYER_FIELD_COMBAT_RATING_1 + 16)
#define PLAYER_RATING_MODIFIER_MELEE_HASTE						(PLAYER_FIELD_COMBAT_RATING_1 + 17)
#define PLAYER_RATING_MODIFIER_RANGED_HASTE						(PLAYER_FIELD_COMBAT_RATING_1 + 18)
#define PLAYER_RATING_MODIFIER_SPELL_HASTE						(PLAYER_FIELD_COMBAT_RATING_1 + 19)
#define PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL			(PLAYER_FIELD_COMBAT_RATING_1 + 20)
#define PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL				(PLAYER_FIELD_COMBAT_RATING_1 + 21)
#define PLAYER_RATING_MODIFIER_HIT_AVOIDANCE_RATING             (PLAYER_FIELD_COMBAT_RATING_1 + 22)
#define PLAYER_RATING_MODIFIER_EXPERTISE						(PLAYER_FIELD_COMBAT_RATING_1 + 23)
#define PLAYER_RATING_MODIFIER_ARMOR_PENETRATION_RATING         (PLAYER_FIELD_COMBAT_RATING_1 + 24)

class ArenaTeam;
struct PlayerCooldown
{
	uint32	ExpireTime;
	uint32	ItemId;
	uint32	SpellId;
	uint32	ExpiretimeAfterCombat;	//potions will start cooldown after out of combat
};
//hmm and what if time is larger then X bits ? Doomed. It will insta clear server wide cooldown. Lucky client still has value
#define PLAYER_SPELL_COOLDOWN_NOT_STARTED ( 0xFFFFFFFF ) 

#define MAX_EQUIPMENT_SET_INDEX			3                          // client limit is 10 ? FFS how can you handle the complexity ?
#define MAX_EQUIPMENT_SET_INDEX_CLIENT	10                         // 

struct EquipmentSet
{
    EquipmentSet()
    {
        for(int i = 0; i < EQUIPMENT_SLOT_END; ++i)
            ItemGUIDS[i] = 0;
		need_save = false;
    }
    uint64		Guid;		//this is set GUID only used to be able to delete a set, not sure if it has a point in case name is unique
    std::string Name;
    std::string IconName;
    uint64		ItemGUIDS[EQUIPMENT_SLOT_END];
	bool		need_save;
};

//====================================================================
//  Player
//  Class that holds every created character on the server.
//
//  TODO:  Attach characters to user accounts
//====================================================================
typedef std::set<uint32>	                        SpellSet;
//typedef std::list<classScriptOverride*>             ScriptOverrideList;
typedef std::set<uint32>                            SaveSet;
typedef std::map<uint64, ByteBuffer*>               SplineMap;
//typedef std::map<uint32, ScriptOverrideList* >      SpellOverrideMap;
typedef std::map<uint32, uint32>                    SpellOverrideExtraAuraMap;
typedef std::map<uint32, FactionReputation*>        ReputationMap;
typedef std::map<uint32, uint64>                    SoloSpells;
typedef std::map<SpellEntry*, pair<uint32, uint32> >StrikeSpellMap;
typedef std::map<uint32, OnHitSpell >               StrikeSpellDmgMap;
typedef std::map<uint32, PlayerSkill>				SkillMap;
typedef std::set<Player**>							ReferenceSet;
typedef std::map<uint32, PlayerCooldown>			PlayerCooldownMap;

#define UNIT_POSITIONING_UPDATE_INTERVAL		5000	//recon to not spam this since it is only visual thing
//just for visual beauty -> attackers and followers to circle around a unit instead standing at the same spot
class UnitToUnitPossitionAdjuster
{
public:
	// allocate a new position for this unit and adjust other units to stay in circle around us
	float				GetUnitAngle(const uint64 &guid);	//our main function
	//initializations here
	void				SetCenterUnit(Unit *owner)
	{
		CenterUnit = owner;
	}
private:
	Unit				*CenterUnit;				//circle around this
	std::list<uint64>	CircleingUnits;				//these must be all units that will circle around owner
//	uint32				NextUpdateStamp;			//do not spam updates
//	uint32				CircleType;					//attackers or guardians 
	void				UpdateCircle();				//check if units are standing nice and secsy
};

struct GOSummon
{
	uint64	GUID;
	uint32	entry;
};

class SERVER_DECL Player : public Unit
{
	friend class WorldSession;
	friend class Pet;
	friend class SkillIterator;

public:

	Player ( uint32 guid );
	~Player ( );
	void Virtual_Destructor( );

	ARCEMU_INLINE Guild * GetGuild() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_playerInfo->guild; 
	}
	ARCEMU_INLINE GuildMember * GetGuildMember() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_playerInfo->guildMember; 
	}
	ARCEMU_INLINE GuildRank * GetGuildRankS() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_playerInfo->guildRank; 
	}

	void EventGroupFullUpdate();
	void GroupUninvite(Player *player, PlayerInfo *info);

	void GiveTalent(uint32 talents);

	/************************************************************************/
	/* Skill System															*/
	/************************************************************************/

	void _AdvanceSkillLine(uint32 SkillLine, uint32 Count = 1);
	void _AddSkillLine(uint32 SkillLine, uint32 Current, uint32 Max);
	uint32 _GetSkillLineMax(uint32 SkillLine);
	uint32 _GetSkillLineCurrent(uint32 SkillLine, bool IncludeBonus = true);
	void _RemoveSkillLine(uint32 SkillLine);
	void _UpdateMaxSkillCounts();
	void _ModifySkillBonus(uint32 SkillLine, int32 Delta);
	void _ModifySkillBonusByType(uint32 SkillType, int32 Delta);
	bool _HasSkillLine(uint32 SkillLine);
	void LearnAllSpellsFromSkillLine(uint32 skill_line,bool skip_talents, bool class_specific);
	void RemoveSpellsFromLine(uint32 skill_line);
	void _RemoveAllSkills();
	void _RemoveLanguages();
	void _AddLanguages(bool All);
	void _AdvanceAllSkills(uint32 count);
	void _ModifySkillMaximum(uint32 SkillLine, uint32 NewMax);
	void AutoLearnSkillRankSpells( uint32 SkillLine, uint32 curr_sk);

	void RecalculateHonor();

protected:

	void _UpdateSkillFields();

//	uint32 object_separator_shield[200];
	SkillMap m_skills;
	
public:
	// COOLDOWNS
	//PlayerCooldownMap m_cooldownMap[NUM_COOLDOWN_TYPES];
//	uint32 var_col_shield1[50];
	tr1::array< PlayerCooldownMap, NUM_COOLDOWN_TYPES> m_cooldownMap;
//	uint32 var_col_shield2[50];
	uint32 m_globalCooldown;
	void Cooldown_AddStart(SpellEntry * pSpell);
	void Cooldown_Add(SpellEntry * pSpell, Item * pItemCaster);
	void Cooldown_AddItem(ItemPrototype * pProto, uint32 x, uint32 after_combat_cooldown);
	bool Cooldown_CanCast(SpellEntry * pSpell);
	void StartOutOfCombatCooldowns();
	void ClearCooldownsOnLine(uint32 skill_line, uint32 called_from);
	void ResetAllCooldowns();
	void ClearCooldownForSpell(uint32 spell_id);
	//not client side, jsut server side for rapid casting 
	void ClearCategoryCooldownForSpell(uint32 spell_id);

protected:
	void _Cooldown_Add(uint32 Type, uint32 Misc, uint32 Time, uint32 SpellId, uint32 ItemId, uint32 after_combat_cooldown = 0);
	void _LoadPlayerCooldowns(QueryResult * result);
	void _SavePlayerCooldowns(QueryBuffer * buf);

	// END COOLDOWNS

public:

	bool ok_to_remove;
	//uint64 m_spellIndexTypeTargets[NUM_SPELL_TYPE_INDEX];
	tr1::array< uint64, NUM_SPELL_TYPE_INDEX> m_spellIndexTypeTargets;
	void OnLogin();//custom stuff on player login.
	void RemoveSpellTargets(uint32 Type, Unit* target);
	void RemoveSpellIndexReferences(uint32 Type);
	void SetSpellTargetType(uint32 Type, Unit* target);
	void SendMeetingStoneQueue(uint32 DungeonId, uint8 Status);
	void SendDungeonDifficulty();
	void SendRaidDifficulty();

	void AddToWorld();
	void AddToWorld(MapMgr * pMapMgr);
	void RemoveFromWorld();
	void RemoveFromWorld(bool free_guid)	// to overwrite virtual function call
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		RemoveFromWorld();
	}
	bool Create ( WorldPacket &data );
	
	void Update( uint32 time );
//	void BuildEnumData( WorldPacket * p_data );
    void BuildFlagUpdateForNonGroupSet(uint32 index, uint32 flag);
	std::string m_afk_reason;
	void SetAFKReason(std::string reason) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_afk_reason = reason; 
	}
	ARCEMU_INLINE const char* GetName() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_name.c_str(); 
	}
	ARCEMU_INLINE std::string* GetNameString() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return &m_name; 
	}
	void Die();
	//void KilledMonster(uint32 entry, const uint64 &guid);
	void GiveXP(uint32 xp, const uint64 &guid, bool allowbonus);   // to stop rest xp being given
	void ModifyBonuses( uint32 type, int32 val, bool apply );
	std::map<uint32, uint32> m_wratings;

	//ArenaTeam * m_arenaTeams[NUM_ARENA_TEAM_TYPES];
	tr1::array<ArenaTeam *, NUM_ARENA_TEAM_TYPES> m_arenaTeams;
	
    /************************************************************************/
    /* Taxi                                                                 */
    /************************************************************************/
    ARCEMU_INLINE TaxiPath*    GetTaxiPath() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_CurrentTaxiPath; 
	}
    ARCEMU_INLINE bool         GetTaxiState() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_onTaxi; 
	}
    uint32		        GetTaximask( uint8 index )  
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_taximask[index]; 
	}
    void                LoadTaxiMask(const char* data);
    void                TaxiStart(TaxiPath* path, uint32 modelid, uint32 start_node);
    void                JumpToEndTaxiNode(TaxiPath * path);
    void                EventDismount(uint32 money, float x, float y, float z);
    void                EventTaxiInterpolate();

    ARCEMU_INLINE void         SetTaxiState    (bool state) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_onTaxi = state; 
	}
    ARCEMU_INLINE void         SetTaximask     (uint8 index, uint32 value ) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		if( index < TAXIMASK_SIZE ) m_taximask[index] = value; 
	}
    ARCEMU_INLINE void         SetTaxiPath     (TaxiPath *path) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_CurrentTaxiPath = path; 
	}
    ARCEMU_INLINE void         SetTaxiPos()	
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_taxi_pos_x = m_position.x; m_taxi_pos_y = m_position.y; m_taxi_pos_z = m_position.z;
	}
    ARCEMU_INLINE void         UnSetTaxiPos()	
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_taxi_pos_x = 0; m_taxi_pos_y = 0; m_taxi_pos_z = 0; 
	}
 
	// Taxi related variables
	vector<TaxiPath*>   m_taxiPaths;
    TaxiPath*           m_CurrentTaxiPath;
    uint32              taxi_model_id;
	uint32              lastNode;
    uint32              m_taxi_ride_time;
    //uint32              m_taximask[TAXIMASK_SIZE];
	tr1::array<uint32,TAXIMASK_SIZE> m_taximask;
    float               m_taxi_pos_x;
    float               m_taxi_pos_y;
    float               m_taxi_pos_z;
    bool                m_onTaxi;
	uint32				m_taxiMapChangeNode;

    /************************************************************************/
    /* Quests                                                               */
    /************************************************************************/
	bool HasQuests() 
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		for(int i = 0; i < 25; ++i)
		{
			if(m_questlog[i] != 0)
				return true;
		}
		return false;
	}

	int32                GetOpenQuestSlot();
	QuestLogEntry*       GetQuestLogForEntry(uint32 quest);
	ARCEMU_INLINE QuestLogEntry*GetQuestLogInSlot(uint32 slot)  
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_questlog[slot]; 
	}
    ARCEMU_INLINE uint32        GetQuestSharer()                
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_questSharer; 
	}
    
    ARCEMU_INLINE void         SetQuestSharer(uint32 guid)     
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_questSharer = guid; 
	}
    void                SetQuestLogSlot(QuestLogEntry *entry, uint32 slot);
    
    ARCEMU_INLINE void         PushToRemovedQuests(uint32 questid)	
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_removequests.insert(questid);
	}
	ARCEMU_INLINE void			PushToFinishedDailies(uint32 questid) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		DailyMutex.Acquire(); m_finishedDailies.insert(questid); DailyMutex.Release();
	}
	ARCEMU_INLINE bool		HasFinishedDaily(uint32 questid) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return (m_finishedDailies.find(questid) == m_finishedDailies.end() ? false : true); 
	}
	ARCEMU_INLINE bool		HasFinishedWeekly(uint32 questid) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return (m_finishedWeeklies.find(questid) == m_finishedWeeklies.end() ? false : true); 
	}
	ARCEMU_INLINE void			PushToFinishedWeeklies(uint32 questid) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		DailyMutex.Acquire(); m_finishedWeeklies.insert(questid); DailyMutex.Release();
	}
    void                AddToFinishedQuests(uint32 quest_id);
    void                EventTimedQuestExpire(Quest *qst, QuestLogEntry *qle, uint32 log_slot);
	void                RemoveQuestsFromLine(int skill_line);
	void				AreaExploredOrEventHappens( uint32 questId ); // scriptdev2

	bool                HasFinishedQuest(uint32 quest_id);
	bool				GetQuestRewardStatus(uint32 quest_id);
	bool                HasQuestForItem(uint32 itemid);
    bool                CanFinishQuest(Quest* qst);
	bool                HasQuestSpell(uint32 spellid);
	void                RemoveQuestSpell(uint32 spellid);
	bool                HasQuestMob(uint32 entry);
	bool                HasQuest(uint32 entry);
	void                RemoveQuestMob(uint32 entry);

    //Quest related variables
	//uint32 m_questbarrier1[25];
	tr1::array<uint32, 25> m_questbarrier1;
    //QuestLogEntry*      m_questlog[25];
	tr1::array< QuestLogEntry*, 25> m_questlog;
	//uint32 m_questbarrier2[25];
	tr1::array< uint32, 25> m_questbarrier2;
    std::set<uint32>    m_QuestGOInProgress;
    std::set<uint32>    m_removequests;
    std::set<uint32>    m_finishedQuests;
	Mutex				DailyMutex;
	std::set<uint32>	m_finishedDailies;
	std::set<uint32>	m_finishedWeeklies;
    uint32              m_questSharer;
//    uint32              timed_quest_slot;
	std::set<uint32>    quest_spells;
	std::set<uint32>    quest_mobs;

    void EventPortToGM(Unit *p);
	ARCEMU_INLINE uint32 GetTeam() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_team; 
	}
	ARCEMU_INLINE uint32 GetTeamInitial() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return myRace->team_id==7 ? 0 : 1; 
	}
	ARCEMU_INLINE void SetTeam(uint32 t) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_team = t; m_bgTeam=t; 
	}
	ARCEMU_INLINE void ResetTeam() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_team = myRace->team_id==7 ? 0 : 1; m_bgTeam=m_team; 
	}

	ARCEMU_INLINE bool IsInFeralForm()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		int s = GetShapeShift();
		if( s <= 0 )
			return false;

		//Fight forms that do not use player's weapon
		return ( s == FORM_BEAR || s == FORM_DIREBEAR || s == FORM_CAT );
		//Shady: actually ghostwolf form doesn't use weapon too.
	}
	void CalcDamage();
	uint32 GetMainMeleeDamage(uint32 AP_owerride); //i need this for windfury

    ARCEMU_INLINE const uint64& GetSelection( ) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_curSelection; 
	}
	ARCEMU_INLINE const uint64& GetTarget( ) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_curTarget; 
	}
	void SetSelection(const uint64 &guid) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_curSelection = guid; 
	}
	void SetTarget(const uint64 &guid) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_curTarget = guid; 
	}
	
    /************************************************************************/
    /* Spells                                                               */
    /************************************************************************/
	bool HasSpell(uint32 spell);
	bool HasSpellwithNameHash(uint32 hash);
	bool HasDeletedSpell(uint32 spell);
	void smsg_InitialSpells();
	void addSpell(uint32 spell_idy,bool skip_skill_add_due_to_load=false);
	void removeSpellByHashName(uint32 hash);
	bool removeSpell(uint32 SpellID, bool MoveToDeleted, bool SupercededSpell, uint32 SupercededSpellID);
	bool removeDeletedSpell( uint32 SpellID );

    // PLEASE DO NOT INLINE!
    void AddOnStrikeSpell(SpellEntry* sp, uint32 delay)
    {
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
        m_onStrikeSpells.insert( map< SpellEntry*, pair<uint32, uint32> >::value_type( sp, make_pair( delay, 0 ) ) );
    }
    void RemoveOnStrikeSpell(SpellEntry *sp)
    {
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
        m_onStrikeSpells.erase(sp);
    }
    void AddOnStrikeSpellDamage(uint32 spellid, uint32 mindmg, uint32 maxdmg)
    {
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
        OnHitSpell sp;
        sp.spellid = spellid;
        sp.mindmg = mindmg;
        sp.maxdmg = maxdmg;
        m_onStrikeSpellDmg[spellid] = sp;
    }
    void RemoveOnStrikeSpellDamage(uint32 spellid)
    {
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
        m_onStrikeSpellDmg.erase(spellid);
    }

    //Spells variables
    StrikeSpellMap      m_onStrikeSpells;
    StrikeSpellDmgMap   m_onStrikeSpellDmg;
//    SpellOverrideMap						mSpellOverrideMap;
//	std::map<uint32,classScriptOverride*>   mSpellOverrideMapNameHash;	//simple version
	SimplePointerList<SpellEffectOverrideScript>	mSpellOverrideMap;	//special spell effect handlers
    SpellSet            mSpells;
    SpellSet            mDeletedSpells;
	SpellSet			mShapeShiftSpells;

	void AddShapeShiftSpell(uint32 id);
	void RemoveShapeShiftSpell(uint32 id);


    /************************************************************************/
    /* Actionbar                                                            */
    /************************************************************************/
	void                setAction(uint8 button, uint16 action, uint8 type, uint8 misc);
	uint32				GetAction(uint8 button)
	{ 
		if( button >= PLAYER_ACTION_BUTTON_COUNT )
			return 0; 
		return mActions[button].Action;
	}
	void                SendInitialActions();
    bool                m_actionsDirty;
	
    /************************************************************************/
    /* Reputation                                                           */
    /************************************************************************/
	void                ModStanding(uint32 Faction, int32 Value, int32 inloop=0);
	void				ChainedModStanding( uint32 Faction, int32 Value);
	int32               GetStanding(uint32 Faction);
	int32               GetBaseStanding(uint32 Faction);
	void                SetStanding(uint32 Faction, int32 Value, int32 inloop=0);
	void                SetAtWar(uint32 Faction, bool Set);
	bool                IsAtWar(uint32 Faction);
	Standing            GetStandingRank(uint32 Faction);
	bool                IsHostileBasedOnReputation(FactionDBC * dbc);
//	void                UpdateInrangeSetsBasedOnReputation();
	void                Reputation_OnKilledUnit(Unit * pUnit, bool InnerLoop);
	void                Reputation_OnTalk(FactionDBC * dbc);
	static Standing     GetReputationRankFromStanding(int32 Standing_);
	void	SetFactionInactive( uint32 faction, bool set );
	bool	AddNewFaction( FactionDBC * dbc, int32 standing, bool base );
	void	OnModStanding( FactionDBC * dbc, FactionReputation * rep );
	
    /************************************************************************/
    /* Factions                                                             */
    /************************************************************************/
	void smsg_InitialFactions();
    // factions variables
    int32 pctReputationMod;

    /************************************************************************/
    /* PVP                                                                  */
    /************************************************************************/
	ARCEMU_INLINE uint8 GetPVPRank()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return (uint8)((GetUInt32Value(PLAYER_BYTES_3) >> 24) & 0xFF);
	}
	ARCEMU_INLINE void SetPVPRank(int newrank)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		SetUInt32Value(PLAYER_BYTES_3, ((GetUInt32Value(PLAYER_BYTES_3) & 0x00FFFFFF) | (uint8(newrank) << 24)));
	}
	uint32 GetMaxPersonalRating();
	
	ARCEMU_INLINE bool HasKnownTitle( RankTitles title )
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		uint32	int_index = title / 32;
		uint32	bitmask = 1 << ( title % 32 );
		uint32  current = GetUInt32Value( PLAYER_FIELD_KNOWN_TITLES + int_index );
		return ( current & bitmask ) != 0;
	}

	void SetKnownTitle( RankTitles title, bool set );
    /************************************************************************/
    /* Groups                                                               */
    /************************************************************************/
	void                SetInviter(uint32 pInviter) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_GroupInviter = pInviter; 
	}
	ARCEMU_INLINE uint32       GetInviter() 
	{ 
		return m_GroupInviter; 
	}
	ARCEMU_INLINE bool         InGroup() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return (m_playerInfo->m_Group != NULL && !m_GroupInviter); 
	}
	bool                IsGroupLeader()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		if(m_playerInfo->m_Group != NULL)
		{
			if(m_playerInfo->m_Group->GetLeader() == m_playerInfo)
				return true;
		}
		return false;
	}
	ARCEMU_INLINE int          HasBeenInvited() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_GroupInviter != 0; 
	}
	ARCEMU_INLINE Group*       GetGroup() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_playerInfo ? m_playerInfo->m_Group : NULL; 
	}
	ARCEMU_INLINE int8		   GetSubGroup() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_playerInfo->subGroup; 
	}
    bool                IsGroupMember(Player *plyr);
	ARCEMU_INLINE bool         IsBanned()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		if(m_banned)
		{
			if(m_banned < 100 || (uint32)UNIXTIME < m_banned)
				return true;
		}
		return false;
	}
    ARCEMU_INLINE void         SetBanned() { m_banned = 4;}
	ARCEMU_INLINE void         SetBanned(string Reason) { m_banned = 4; m_banreason = Reason;}
	ARCEMU_INLINE void         SetBanned(uint32 timestamp, string& Reason) { m_banned = timestamp; m_banreason = Reason; }
	ARCEMU_INLINE void         UnSetBanned() { m_banned = 0; }
	ARCEMU_INLINE string       GetBanReason() {return m_banreason;}

    /************************************************************************/
    /* Guilds                                                               */
    /************************************************************************/
	ARCEMU_INLINE  bool        IsInGuild() 
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
#ifdef CATACLYSM_SUPPORT
		return false;
#else
		return (m_uint32Values[PLAYER_GUILDID] != 0) ? true : false;
#endif
	}
	ARCEMU_INLINE uint32       GetGuildId() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
#ifdef CATACLYSM_SUPPORT
		return 0;
#else	
		return m_uint32Values[PLAYER_GUILDID]; 
#endif
	}
	void                SetGuildId(uint32 guildId);
	ARCEMU_INLINE uint32       GetGuildRank() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_uint32Values[PLAYER_GUILDRANK]; 
	}
	void                SetGuildRank(uint32 guildRank);
	uint32              GetGuildInvitersGuid() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_invitersGuid; 
	}
	void                SetGuildInvitersGuid( uint32 guid ) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_invitersGuid = guid; 
	}
	void                UnSetGuildInvitersGuid() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_invitersGuid = 0; 
	}
  
    /************************************************************************/
    /* Duel                                                                 */
    /************************************************************************/
    void                RequestDuel(Player *pTarget);
	void                DuelBoundaryTest();
	void                EndDuel(uint8 WinCondition);
	void                DuelCountdown();
	void                SetDuelStatus(uint8 status) 
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_duelStatus = status; 
	}
	ARCEMU_INLINE uint8        GetDuelStatus() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_duelStatus; 
	}
	void                SetDuelState(uint8 state) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_duelState = state; 
	}
	ARCEMU_INLINE uint8        GetDuelState() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_duelState; 
	}
    // duel variables
    Player*             DuelingWith;

    /************************************************************************/
    /* Trade                                                                */
    /************************************************************************/
	void                SendTradeUpdate(void);
	void				ResetTradeVariables()
	{
		mTradeGold = 0;
		memset(&mTradeItems, 0, sizeof(Item*) * 8);
		mTradeStatus = 0;
		mTradeTarget = 0;
		m_tradeSequence = 2;
	}
	
    /************************************************************************/
    /* Pets                                                                 */
    /************************************************************************/
	ARCEMU_INLINE void			SetSummon(Pet *pet) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_Summon = pet; 
	}
	ARCEMU_INLINE Pet*			GetSummon(void) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_Summon; 
	}
	uint32						GeneratePetNumber(void);
	void						RemovePlayerPet(uint32 pet_number);
	ARCEMU_INLINE void			AddPlayerPet(PlayerPet* pet, uint32 index) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_Pets[index] = pet; 
	}
	ARCEMU_INLINE PlayerPet*	GetPlayerPet(uint32 idx)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		std::map<uint32, PlayerPet*>::iterator itr = m_Pets.find(idx);
		if(itr != m_Pets.end()) return itr->second;
		else
			return NULL;
	}
	void						SpawnPet(uint32 pet_number);
	void						SpawnActivePet();

	ARCEMU_INLINE uint8         GetPetCount(void) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return (uint8)m_Pets.size(); 
	}
	ARCEMU_INLINE void			SetStableSlotCount(uint8 count) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_StableSlotCount = count; 
	}
	ARCEMU_INLINE uint8			GetStableSlotCount(void) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_StableSlotCount; 
	}
	uint32						GetUnstabledPetNumber(void)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		if(m_Pets.size() == 0) return 0;
		std::map<uint32, PlayerPet*>::iterator itr = m_Pets.begin();
		for(;itr != m_Pets.end();itr++)
			if(itr->second->stablestate == STABLE_STATE_ACTIVE)
				return itr->first;
		return 0;
	}
	void						EventSummonPet(Pet *new_pet);		//if we charmed or simply summoned a pet, this function should get called
	void						EventSummonPetCastSpell( Pet *new_pet, uint32 SpellID );	//talents that need recasting on pet summon
	void						EventDismissPet();					//if pet/charm died or whatever happned we should call this function
	void						ForceAllPetTalentAndSpellReset();	//this is for hunter talent when we need to reset pet talents even if they are offline

    /************************************************************************/
    /* Item Interface                                                       */
    /************************************************************************/
	ARCEMU_INLINE ItemInterface* GetItemInterface() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_ItemInterface; 
	} // Player Inventory Item storage
	ARCEMU_INLINE void			ApplyItemMods(Item *item, int16 slot, bool apply,bool justdrokedown=false) 
	{  
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		_ApplyItemMods(item, slot, apply,justdrokedown); 
	}
	ARCEMU_INLINE bool			HasItemCount( uint32 item, uint32 count, bool inBankAlso = false );
    // item interface variables
    ItemInterface *     m_ItemInterface;
	
    /************************************************************************/
    /* Loot                                                                 */
    /************************************************************************/
	ARCEMU_INLINE const uint64& GetLootGUID() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_lootGuid; 
	}
	ARCEMU_INLINE void         SetLootGUID(const uint64 &guid) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_lootGuid = guid; 
	}
	void                SendLoot(uint64 guid,uint8 loot_type);
    // loot variables
    uint64              m_lootGuid;
    uint64              m_currentLoot;
    bool                bShouldHaveLootableOnCorpse;

    /************************************************************************/
    /* World Session                                                        */
    /************************************************************************/
	ARCEMU_INLINE WorldSession* GetSession() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_session; 
	}
	void SetSession(WorldSession *s) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_session = s; 
	}
	void SetBindPoint(float x, float y, float z, uint32 m, uint32 v) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_bind_pos_x = x; m_bind_pos_y = y; m_bind_pos_z = z; m_bind_mapid = m; m_bind_zoneid = v;
	}
	void SendDelayedPacket(WorldPacket *data, bool bDeleteOnSend)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		if(data == NULL) 
			return;
		if(GetSession() != NULL) 
			GetSession()->SendPacket(data);
		if(bDeleteOnSend)
			delete data;
	}
	float offhand_dmg_mod;
	float GetSpellTimeMod(uint32 id);
	int GetSpellDamageMod(uint32 id);
	int32 GetSpellManaMod(uint32 id);
	
	// Talents
	// These functions build a specific type of A9 packet
	uint32 __fastcall BuildCreateUpdateBlockForPlayer( ByteBuffer *data, Player *target );
	void DestroyForPlayer( Player *target, uint8 anim = 0);
	void SetTalentHearthOfWildPCT(int value){hearth_of_wild_pct=value;}
	void EventTalentHearthOfWildChange(bool apply);
	
	std::list<LoginAura> loginauras;

    std::set<uint32> OnMeleeAuras;

    /************************************************************************/
    /* Player loading and savings                                           */
    /* Serialize character to db                                            */
    /************************************************************************/
	void SaveToDB(bool bNewCharacter);
	void SaveAuras(stringstream&);
	bool LoadFromDB(uint32 guid);
	void LoadFromDBProc(QueryResultVector & results);

	void LoadNamesFromDB(uint32 guid);
	bool m_FirstLogin;

    /************************************************************************/
    /* Death system                                                         */
    /************************************************************************/
	void SpawnCorpseBody();
	void SpawnCorpseBones();
	void CreateCorpse();
	void KillPlayer();
	void ResurrectPlayer();
	void RepopRequestedPlayer();
	void DeathDurabilityLoss(double percent);
	void RepopAtGraveyard(float ox, float oy, float oz, uint32 mapid);

	uint64 m_resurrecter;
	
    /************************************************************************/
    /* Movement system                                                      */
    /************************************************************************/
	void SetMovement(uint8 pType);
	void SetPlayerSpeed(uint8 SpeedType, float value);
	float GetPlayerSpeed(){return m_runSpeed;}
	uint8 m_currentMovement;
	bool m_isMoving;
	bool moving;
	uint32 last_moved;
	bool strafing;
	bool jumping;
	//Invisibility stuff
	bool m_isGmInvisible;
	
    /************************************************************************/
    /* Channel stuff                                                        */
    /************************************************************************/
	void JoinedChannel(Channel *c);
	void LeftChannel(Channel *c);
	void CleanupChannels();

	/************************************************************************/
	/* Attack stuff															*/
    /************************************************************************/
	void EventAttackStart();
	void EventAttackStop();
	void EventAttackUpdateSpeed() { }
	void EventDeath();
	//Note:ModSkillLine -> value+=amt;ModSkillMax -->value=amt; --wierd
	float GetSkillUpChance(uint32 id);
	//ARCEMU_INLINE std::list<struct skilllines>getSkillLines() { return m_skilllines; }
	float SpellCrtiticalStrikeRatingBonus;
	float SpellHasteRatingBonus;
	void ModAttackSpeed( int32 mod, ModType type );
	void UpdateAttackSpeed();
	float GetDefenseChance(uint32 opLevel);
	float GetDodgeChance();
	float GetBlockChance();
	float GetParryChance();
	void UpdateChances();
	void UpdateStats();
	void UpdateHit(int32 hit);
   
	bool canCast(SpellEntry *m_spellInfo);
	ARCEMU_INLINE float GetSpellCritFromSpell() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_spellcritfromspell; 
	}
	ARCEMU_INLINE float GetHitFromSpell() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_hitfromspell; 
	}
	void SetSpellCritFromSpell(float value) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_spellcritfromspell = value; 
	}
	void SetHitFromSpell(float value) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_hitfromspell = value; 
	}
	ARCEMU_INLINE uint32 GetHealthFromSpell() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_healthfromspell; 
	}
	ARCEMU_INLINE uint32 GetManaFromSpell() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_manafromspell; 
	}
	void SetHealthFromSpell(uint32 value) 
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_healthfromspell = value;
	}
	void SetManaFromSpell(uint32 value) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_manafromspell = value;
	}
	uint32 CalcTalentResetCost(uint32 resetnum);
	void SendTalentResetConfirm();
	void SendPetUntrainConfirm();
	uint32 GetTalentResetTimes() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_talentresettimes; 
	}
	ARCEMU_INLINE void SetTalentResetTimes(uint32 value) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_talentresettimes = value; 
	}
	//////////////////////////////
	//multi talent specing
	//////////////////////////////
	void fill_talent_info_in_packet( WorldPacket &data );
	void smsg_TalentsInfo(bool update, uint32 newTalentId, uint8 newTalentRank);
	uint8 m_talentSpecsCount;
	uint8 m_talentActiveSpec;
	uint32 m_tanlentSpecRespecTimer; //avoid spamming respecing
	struct PlayerSpec
	{
		std::map<uint32, uint8> talents;	// map of <talentId, talentRank>
		//uint16  glyphs[GLYPHS_COUNT];
		tr1::array< uint16, GLYPHS_COUNT > glyphs;
		SpellSet	SpecSpecificSpells;
	};

	//PlayerSpec m_specs[MAX_SPEC_COUNT];
	tr1::array< PlayerSpec, MAX_SPEC_COUNT > m_specs;
				
	void	Event_Learn_Talent( uint32 newTalentId, uint8 newTalentRank, uint8 point_consume = 1 );
	void	Switch_Talent_Spec(); //remove old talents active on us and apply new ones
	uint32	GetMaxTP() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return max(0,(int32)( getLevel() - 9 + m_Talent_point_mods )); 
	}

	// end multi talent specing
	void SetPlayerStatus(uint8 pStatus) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_status = pStatus; 
	}
	ARCEMU_INLINE uint8 GetPlayerStatus() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_status; 
	}
	ARCEMU_INLINE const float& GetBindPositionX( ) 
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_bind_pos_x; 
	}
	ARCEMU_INLINE const float& GetBindPositionY( ) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_bind_pos_y; 
	}
	ARCEMU_INLINE const float& GetBindPositionZ( ) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_bind_pos_z; 
	}
	ARCEMU_INLINE const uint32& GetBindMapId( ) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_bind_mapid; 
	}
	ARCEMU_INLINE const uint32& GetBindZoneId( )
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_bind_zoneid; 
	}
	ARCEMU_INLINE uint8 GetShapeShift()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return GetByte(UNIT_FIELD_BYTES_2,3);
	}

	
	void delayAttackTimer(int32 delay)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		if(!delay)
			return;

		m_attackTimer += delay;
		m_attackTimer_1 += delay;
	}

	void SetShapeShift(uint8 ss);

    //Showing Units WayPoints
	AIInterface* waypointunit;
	
	uint32 m_nextSave;
	//Tutorials
	uint32 GetTutorialInt(uint32 intId );
	void SetTutorialInt(uint32 intId, uint32 value);
	//Base stats calculations
	//void CalcBaseStats();
	// Rest
	uint32 SubtractRestXP(uint32 amount);
	void AddCalculatedRestXP(uint32 seconds);
	void ApplyPlayerRestState(bool apply);
	void UpdateRestState();
	bool m_noFallDamage;
	float z_axisposition;
	int32 m_safeFall;
	// Gossip
	GossipMenu* CurrentGossipMenu;
	void CleanupGossipMenu();
	void Gossip_Complete();
	int m_lifetapbonus;
	uint32 m_lastShotTime;
	bool m_requiresNoAmmo;
	
	// scriptdev2
	GossipMenu* PlayerTalkClass;
	void PrepareQuestMenu( uint64 guid );
	void SendGossipMenu( uint32 TitleTextId, uint64 npcGUID );
	void CloseGossip();
	QuestStatus GetQuestStatus( uint32 quest_id );


	bool m_bUnlimitedBreath;
	uint32 m_UnderwaterTime;
	uint32 m_UnderwaterState;
	uint32 m_SwimmingTime;
	uint32 m_BreathDamageTimer;
	// Visible objects
	bool CanSee(Object* obj);
	ARCEMU_INLINE bool IsVisible(Object* pObj) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return !(m_visibleObjects.find(pObj) == m_visibleObjects.end()); 
	}
	void AddInRangeObject(Object* pObj);
	void OnRemoveInRangeObject(Object* pObj);
	void ClearInRangeSet();
	ARCEMU_INLINE void AddVisibleObject(Object* pObj) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_visibleObjects.insert(pObj); 
	}
	ARCEMU_INLINE void RemoveVisibleObject(Object* pObj) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_visibleObjects.erase(pObj); 
	}
	ARCEMU_INLINE void RemoveVisibleObject(InRangeSet::iterator itr) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_visibleObjects.erase(itr); 
	}
	ARCEMU_INLINE InRangeSet::iterator FindVisible(Object * obj) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_visibleObjects.find(obj); 
	}
	ARCEMU_INLINE void RemoveIfVisible(Object * obj)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		InRangeSet::iterator itr = m_visibleObjects.find(obj);
		if(itr == m_visibleObjects.end())
			return;

		m_visibleObjects.erase(obj);
		PushOutOfRange(obj->GetNewGUID());
	}

	ARCEMU_INLINE bool GetVisibility(Object * obj, InRangeSet::iterator *itr)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		*itr = m_visibleObjects.find(obj);
		return ((*itr) != m_visibleObjects.end());
	}

	ARCEMU_INLINE InRangeSet::iterator GetVisibleSetBegin() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_visibleObjects.begin(); 
	}
	ARCEMU_INLINE InRangeSet::iterator GetVisibleSetEnd() { return m_visibleObjects.end(); }
	
	//Transporters
	bool m_lockTransportVariables;
	uint64 m_TransporterGUID;
	float m_TransporterX;
	float m_TransporterY;
	float m_TransporterZ;
	float m_TransporterO;
	float m_TransporterTime;
	// Misc
	void EventCannibalize(uint32 amount);
	void EventReduceDrunk(bool full);
	bool m_AllowAreaTriggerPort;
	void EventAllowTiggerPort(bool enable);

	uint32 m_modblockabsorbvaluePCT;
	uint32 m_modblockvaluefromspells;
	void SendInitialLogonPackets();
	void Reset_Spells();
	void Reset_Talents();
	void Reset_ToLevel1();
	// Battlegrounds xD
	CBattleground * m_bg;
	CBattleground * m_pendingBattleground;
	uint32 m_bgEntryPointMap;
	float m_bgEntryPointX;	
	float m_bgEntryPointY;
	float m_bgEntryPointZ;
	float m_bgEntryPointO;
	int32 m_bgEntryPointInstance;
	bool m_bgHasFlag;
	bool m_bgIsQueued;
	uint32 m_bgQueueType;
	uint32 m_bgQueueInstanceId;
	void EventRepeatSpell();
	void EventCastRepeatedSpell(uint32 spellid, Unit *target);
	int32 CanShootRangedWeapon(uint32 spellid, Unit *target, bool autoshot);
	int32 m_AutoShotDuration;
	int32 m_AutoShotAttackTimer;
	bool m_onAutoShot;
	uint64 m_AutoShotTarget;
	SpellEntry *m_AutoShotSpell;
	void _InitialReputation();
	void EventActivateGameObject(GameObject* obj);
	void EventDeActivateGameObject(GameObject* obj);
	void UpdateNearbyGameObjects();
	
	void CalcResistance(uint32 type);
	ARCEMU_INLINE float res_M_crit_get()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_resist_critical[0];
	}
	ARCEMU_INLINE void res_M_crit_set(float newvalue)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_resist_critical[0]=newvalue;
	}
	ARCEMU_INLINE float res_R_crit_get()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_resist_critical[1];
	}
	ARCEMU_INLINE void res_R_crit_set(float newvalue)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_resist_critical[1]=newvalue;
	}
	//uint32 FlatResistanceModifierPos[7];
	tr1::array< uint32, 7 > FlatResistanceModifierPos;
	//uint32 FlatResistanceModifierNeg[7];
	tr1::array< uint32, 7 > FlatResistanceModifierNeg;
	//uint32 BaseResistanceModPctPos[7];
	tr1::array< uint32, 7 > BaseResistanceModPctPos;
	//uint32 BaseResistanceModPctNeg[7];
	tr1::array< uint32, 7 > BaseResistanceModPctNeg;
	//uint32 ResistanceModPctPos[7];
	tr1::array< uint32, 7 > ResistanceModPctPos;
	//uint32 ResistanceModPctNeg[7];
	tr1::array< uint32, 7 > ResistanceModPctNeg;
	//float m_resist_critical[2];//when we are a victim we can have talents to decrease chance for critical hit. This is a negative value and it's added to critchances
	tr1::array< float, 2 > m_resist_critical;
	//float m_resist_hit[3]; // 0 = melee; 1= ranged; 2=spells
	tr1::array< float, 3 > m_resist_hit;
	//float m_attack_speed[3];
	tr1::array< float, 3 > m_attack_speed;
	//float SpellHealDoneByAttribute[5][7];
//	tr1::array< tr1::array<float, 7>,5 > SpellHealDoneByAttribute;
	tr1::array<float, 5> SpellHealDoneByAttribute;
	uint32 m_modphyscritdmgPCT;
	uint32 m_RootedCritChanceBonus; // Class Script Override: Shatter

	uint32 m_ModInterrMRegenPCT;
	int32 m_ModInterrMRegen;
	float m_RegenManaOnSpellResist;
	
	//uint32 FlatStatModPos[5];
	tr1::array<uint32, 5> FlatStatModPos;
	//uint32 FlatStatModNeg[5];
	tr1::array<uint32, 5> FlatStatModNeg;
	//uint32 StatModPctPos[5];
	tr1::array<uint32, 5> StatModPctPos;
	//uint32 StatModPctNeg[5];
	tr1::array<uint32, 5> StatModPctNeg;
	//uint32 TotalStatModPctPos[5];
	tr1::array<uint32, 5> TotalStatModPctPos;
	//uint32 TotalStatModPctNeg[5];
	tr1::array<uint32, 5> TotalStatModPctNeg;
	//int32 IncreaseDamageByType[12]; //mod dmg by creature type
	tr1::array<int32, CREATURE_TYPES> IncreaseDamageByType;
	//float IncreaseDamageByTypePCT[12];
	tr1::array<float, CREATURE_TYPES> IncreaseDamageByTypePCT;
	//float IncreaseCricticalByTypePCT[12];
	tr1::array<float, CREATURE_TYPES> IncreaseCricticalByTypePCT;
	int32 DetectedRange;
	float PctIgnoreRegenModifier;
	uint32 m_retainedrage;
/*	
	union {
		float mRatingToPct[37];
		uint32 mRatingToPoint[37]; //block, skill.. cant be decimal values
	};
*/
	ARCEMU_INLINE uint32* GetPlayedtime() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return &m_playedtime[0]; 
	}
	void CalcStat(uint32 t);
	float CalcRating(uint32 t);
	void RecalcAllRatings();
	void RegenerateMana(bool is_interrupted);
	void RegenerateHealth(bool inCombat);
	void RegenerateEnergy();
	void RegenetateRunicPower();
	void LooseRage(int32 value);
	
    uint32 SoulStone;
	uint32 SoulStoneReceiver;
	void removeSoulStone();

    ARCEMU_INLINE uint32 GetSoulStoneReceiver()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return SoulStoneReceiver;
	}
    ARCEMU_INLINE void SetSoulStoneReceiver(uint32 StoneGUID)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		SoulStoneReceiver = StoneGUID;
	}
    ARCEMU_INLINE uint32 GetSoulStone()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return SoulStone;
	}
    ARCEMU_INLINE void SetSoulStone(uint32 StoneID)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		SoulStone = StoneID;
	}

	uint64 misdirectionTarget;

	ARCEMU_INLINE uint64 GetMisdirectionTarget()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return misdirectionTarget;
	}
	void SetMisdirectionTarget(uint64 PlayerGUID)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		misdirectionTarget = PlayerGUID;
	}

	bool bReincarnation;
	bool removeReagentCost;

	SimplePointerList<WeaponModifier>	damagedone;
	SimplePointerList<WeaponModifier>	tocritchance;
	SimplePointerList<WeaponModifier>	ignore_armor_pct;
	float								weapon_target_armor_pct_ignore; //value is already converted into float ! It applies only to melee
	bool cannibalize;
	uint8 cannibalizeCount;
	int32 rageFromDamageDealt;
	int32 rageFromDamageTaken;
	// GameObject commands
	GameObject* GetSelectedGo();
	uint64 m_GM_SelectedGO;
	
#ifndef CLUSTERING
	void _Relocate(uint32 mapid,const LocationVector & v, bool sendpending, bool force_new_world, uint32 instance_id);
#else
	void RelocateCallback(uint32 instance_were_going_to);
#endif
	void AddItemsToWorld();
	void RemoveItemsFromWorld();
	
	uint32 m_ShapeShifted;
	uint32 m_MountSpellId;
    
	ARCEMU_INLINE bool IsMounted() 
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return (m_MountSpellId!=0 ? true : false); 
	}
	
    bool bHasBindDialogOpen;
	bool bGMTagOn;
	uint32 TrackingSpell;
	void _EventCharmAttack();
	void _Kick();
	void Kick(uint32 delay = 0);
	void SoftDisconnect();
	uint64 m_CurrentCharm;
	Transporter * m_CurrentTransporter;
	
	Object * GetSummonedObject () 
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_SummonedObject;
	}
	void SetSummonedObject (Object * t_SummonedObject) 
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_SummonedObject = t_SummonedObject;
	}
	uint32 roll;

	bool bProcessPending;
	Mutex _bufferS;
	void PushUpdateData(ByteBuffer *data, uint32 updatecount);
    void PushCreationData(ByteBuffer *data, uint32 updatecount);
	void PushOutOfRange(const WoWGuid & guid);
	void ProcessPendingUpdates(bool skip_lock=false);
	bool __fastcall CompressAndSendUpdateBuffer(uint32 size, const uint8* update_buffer);
	void ClearAllPendingUpdates();
	
	uint32 GetArmorProficiency() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return armor_proficiency; 
	}
	uint32 GetWeaponProficiency() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return weapon_proficiency; 
	}

	void SpeedCheatDelay(uint32 ms_delay);
	void SpeedCheatReset();

	void AddSplinePacket(uint64 guid, ByteBuffer* packet);
	ByteBuffer* GetAndRemoveSplinePacket(uint64 guid);
	void ClearSplinePackets();
	bool ExitInstance();
	void SaveEntryPoint(uint32 mapId);
	bool CooldownCheat;
	bool CastTimeCheat;
	bool PowerCheat;
	bool FlyCheat;
	void EventZoneChange(uint32 ZoneId);
	ARCEMU_INLINE uint32 GetAreaID() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_AreaID; 
	}
	void SetAreaID(uint32 area) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_AreaID = area; 
	}
	uint32      m_AreaID;
	
	// Instance IDs

	ARCEMU_INLINE uint32 GetPersistentInstanceId(uint32 mapId, uint32 difficulty)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		if(mapId >= NUM_MAPS || difficulty >= NUM_INSTANCE_MODES || m_playerInfo == NULL)
			return 0;
		m_playerInfo->savedInstanceIdsLock.Acquire();
		PlayerInstanceMap::iterator itr = m_playerInfo->savedInstanceIds[difficulty].find(mapId);
		if(itr == m_playerInfo->savedInstanceIds[difficulty].end())
		{
			m_playerInfo->savedInstanceIdsLock.Release();
			return 0;
		}
		m_playerInfo->savedInstanceIdsLock.Release();
		return (*itr).second;
	}

	void SetPersistentInstanceId(Instance *pInstance);
	//Use this method carefully.. 
	void SetPersistentInstanceId(uint32 mapId, uint32 difficulty, uint32 instanceId);
	PlayerInfo *getPlayerInfo() { return m_playerInfo; }

public:
	void StopMirrorTimer(uint32 Type);
	BGScore m_bgScore;
	uint32 m_bgTeam;
	void UpdateChanceFields();
	//Honor Variables
	time_t m_fallDisabledUntil;
	uint32 m_honorToday;
	uint32 m_honorYesterday;
	
	void RolloverHonor();
	uint32 m_honorPoints;
	uint32 m_honorRolloverTime;
	uint32 m_killsToday;
	uint32 m_killsYesterday;
	uint32 m_killsLifetime;
	uint32 m_arenaPoints;
	uint32 m_honorless;
	uint32 m_lastSeenWeather;
	set<Object*> m_visibleFarsightObjects;
	void EventTeleport(uint32 mapid, float x, float y, float z);
	void EventTeleportTaxi(uint32 mapid, float x, float y, float z);
	void ApplyLevelInfo(LevelInfo* Info, uint32 Level);
	void BroadcastMessage(const char* Format, ...);
	map<uint32, set<uint32> > SummonSpells;
	map<uint32, PetSpellMap*> PetSpells;
	void AddSummonSpell(uint32 Entry, uint32 SpellID);
	void RemoveSummonSpell(uint32 Entry, uint32 SpellID);
	set<uint32>* GetSummonSpells(uint32 Entry);
	LockedQueue<WorldPacket*> delayedPackets;
	set<Player *> gmTargets;
	uint32 m_UnderwaterMaxTime;
	uint32 m_UnderwaterLastDmg;
//	ARCEMU_INLINE void setMyCorpse(Corpse * corpse) { myCorpse = corpse; }
//	ARCEMU_INLINE Corpse * getMyCorpse() { return myCorpse; }
	bool bCorpseCreateable;
	uint32 m_resurrectHealth, m_resurrectMana;
	uint32 m_resurrectInstanceID, m_resurrectMapId;
	LocationVector m_resurrectPosition;
	bool blinked;
	uint32 m_explorationTimer;
	// DBC stuff
	CharRaceEntry * myRace;
	CharClassEntry * myClass;
	Unit * linkTarget;
	bool AuraStackCheat;
	bool TriggerpassCheat;
	bool SafeTeleport(uint32 MapID, uint32 InstanceID, float X, float Y, float Z, float O);
	bool SafeTeleport(uint32 MapID, uint32 InstanceID, const LocationVector & vec);
	void SafeTeleport(MapMgr * mgr, const LocationVector & vec);
	void EjectFromInstance();
	bool raidgrouponlysent;
	
	void EventSafeTeleport(uint32 MapID, uint32 InstanceID, LocationVector vec)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		SafeTeleport(MapID, InstanceID, vec);
	}

	// Hack fix here!
//	void ForceZoneUpdate();

	/*****************
	  PVP Stuff
	******************/
	uint32 m_pvpTimer;
	
	void SetPvPFlag();
	//! Removal
	void RemovePvPFlag();
	//! Do this on /pvp off
	ARCEMU_INLINE void ResetPvPTimer();
	//! Stop the timer for pvp off
	ARCEMU_INLINE void StopPvPTimer() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		RemoveFlag(PLAYER_FLAGS, PLAYER_FLAGS_PVP_STATUS_COOLDOWN);
		m_pvpTimer = 0; 
	}
	void SetFFAPvPFlag();
	void RemoveFFAPvPFlag();
	
	//! Called at login to add the honorless buff, etc.
//	void LoginPvPSetup();
	//! Update our pvp area (called when zone changes)
	void UpdatePvPArea(bool just_teleported);
	//! PvP Toggle (called on /pvp)
	void PvPToggle();

	ARCEMU_INLINE uint32 LastHonorResetTime() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return m_lastHonorResetTime; 
	}
	ARCEMU_INLINE void LastHonorResetTime(uint32 val) 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_lastHonorResetTime = val; 
	}
	uint32 OnlineTime;
	bool tutorialsDirty;
	LevelInfo * lvlinfo;
	void CalculateBaseStats();
	uint32 load_health;
	uint32 load_mana;
	void CompleteLoading();
	set<SpellEntry *> castSpellAtLogin;
	void OnPushToWorld();
	void OnPrePushToWorld();
	void OnWorldPortAck();
	uint32 m_TeleportState;
	set<Unit*> visiblityChangableSet;
	bool m_beingPushed;
	bool CanSignCharter(Charter * charter, Player * requester);
	//Charter * m_charters[NUM_CHARTER_TYPES];
	tr1::array< Charter *, NUM_CHARTER_TYPES> m_charters;
	uint32 flying_aura;
	stringstream LoadAuras;
	bool resend_speed;
	bool rename_pending;
//	uint32	instance_difficulty;		//this is the instance type the player is using right now
	//if player is not in group or normal group then use dungeon settings
	uint32	dungeon_difficulty;
	//if player is in raid group then use raid settings
	uint32	raid_difficulty;
	//instance difficulty contains both raid and dungeon values !
	uint32 GetInstanceDifficulty()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		uint32 ret;
		if( GetGroup() )
			ret = GetGroup()->GetInstanceDifficulty();
		else
			ret = dungeon_difficulty;
//		ASSERT( ret < NUM_INSTANCE_MODES );
		return ret;
	}
	ARCEMU_INLINE void SetName(string& name) { m_name = name; }
	ARCEMU_INLINE void SetNameSuffix(const char *name) { m_name_suffix = name; }
	// spell to (delay, last time)
	
	//FactionReputation * reputationByListId[128];
	tr1::array<FactionReputation *,128> reputationByListId;
	
	uint64 m_comboTarget;
	int8 m_comboPoints;
	int8 m_spellcomboPoints; // rogue talent Ruthlessness will change combopoints while consuming them. solutions 1) add post cast prochandling, 2) delay adding the CP
	void UpdateComboPoints();

	ARCEMU_INLINE void AddComboPoints(uint64 target, uint8 count)
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
        if(m_comboTarget == target)
			m_comboPoints += count;
		else
		{
			m_comboTarget = target;
			m_comboPoints = count;
		}
		UpdateComboPoints();
	}
	ARCEMU_INLINE void RemoveComboPoints( uint8 count )
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		if( m_comboPoints >= count )
			m_comboPoints -= count;
		else
			m_comboPoints = 0;
		UpdateComboPoints();
	}

	ARCEMU_INLINE void NullComboPoints() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_comboTarget = 0; m_comboPoints = 0; m_spellcomboPoints=0;
		UpdateComboPoints(); 
	}
	uint32 m_PositionUpdateCounter;

	void SendAreaTriggerMessage(const char * message, ...);
        
	// Trade Target
	//Player *getTradeTarget() {return mTradeTarget;};

	ARCEMU_INLINE Player * GetTradeTarget();

	Item *getTradeItem(uint32 slot) 
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return mTradeItems[slot];
	}
        
	// Water level related stuff (they are public because they need to be accessed fast)
	// Nose level of the character (needed for proper breathing)
	float m_noseLevel;

	/* Mind Control */
	void Possess(Unit * pTarget);
	void UnPossess();

	/* Last Speeds */
	ARCEMU_INLINE void UpdateLastSpeeds()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		m_lastRunSpeed = m_runSpeed;
		m_lastRunBackSpeed = m_backWalkSpeed;
		m_lastSwimSpeed = m_swimSpeed;
		m_lastRunBackSpeed = m_backSwimSpeed;
		m_lastFlySpeed = m_flySpeed;
	}

	void RemoteRevive()
	{
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		ResurrectPlayer();
		SetMovement( MOVE_UNROOT );
		SetPlayerSpeed( RUN, PLAYER_NORMAL_RUN_SPEED );
		SetPlayerSpeed( SWIM, PLAYER_NORMAL_SWIM_SPEED );
		SetMovement( MOVE_LAND_WALK );
		SetUInt32Value( UNIT_FIELD_HEALTH, GetUInt32Value( UNIT_FIELD_MAXHEALTH ) );
	}

	LocationVector m_last_group_position;
	void SummonRequest(uint32 Requestor, uint32 ZoneID, uint32 MapID, uint32 InstanceID, const LocationVector & Position);

#ifdef CLUSTERING
	void EventRemoveAndDelete();
	void PackPlayerData(ByteBuffer & data);
	bool UnpackPlayerData(ByteBuffer & data);
#endif

	bool m_deathVision;
	SpellEntry * last_heal_spell;
	LocationVector m_sentTeleportPosition;

//	void RemoveFromBattlegroundQueue();
	void FullHPMP();
	uint32 m_arenateaminviteguid;

    /************************************************************************/
    /* Spell Packet wrapper Please keep this separated                      */
    /************************************************************************/
    void SendLevelupInfo(uint32 level, uint32 Hp, uint32 Mana, uint32 Stat0, uint32 Stat1, uint32 Stat2, uint32 Stat3, uint32 Stat4);
    void SendLogXPGain(uint64 guid, uint32 NormalXP, uint32 RestedXP, bool type);
    void SendEnvironmentalDamageLog(const uint64 & guid, uint8 type, uint32 damage);
	void SendWorldStateUpdate(uint32 WorldState, uint32 Value);
	void SendCastResult(uint32 SpellId, uint8 ErrorMessage, uint8 MultiCast, uint32 Extra);
	void Gossip_SendPOI(float X, float Y, uint32 Icon, uint32 Flags, uint32 Data, const char* Name);
    /************************************************************************/
    /* End of SpellPacket wrapper                                           */
    /************************************************************************/

	Mailbox m_mailBox;
	bool m_waterwalk;
	bool m_setwaterwalk;
	bool m_safe_fall;
	bool m_setflycheat;
	uint64 m_areaSpiritHealer_guid;
	bool m_finishingmovesdodge;

	ARCEMU_INLINE bool IsAttacking() {return m_attacking; }

//	static void InitVisibleUpdateBits();
//	static UpdateMask m_visibleUpdateMask;

	void CopyAndSendDelayedPacket(WorldPacket * data);
	void PartLFGChannel();
	SpeedCheatDetector	*SDetector;
	PlayerCreateInfo	*GetCreateInfo(){return info;}
protected:
	LocationVector m_summonPos;
	uint32 m_summonInstanceId;
	uint32 m_summonMapId;
	uint32 m_summoner;

	void _SetCreateBits(UpdateMask *updateMask, Player *target) const;
//	void _SetUpdateBits(UpdateMask *updateMask, Player *target) const;

	/* Update system components */
	ByteBuffer bUpdateBuffer;
    ByteBuffer bCreationBuffer;
	uint32 mUpdateCount;
    uint32 mCreationCount;
	uint32 mOutOfRangeIdCount;
	ByteBuffer mOutOfRangeIds;
	SplineMap _splineMap;
	/* End update system */

	void _LoadTutorials(QueryResult * result);
	void _SaveTutorials(QueryBuffer * buf);
	void _SaveInventory(bool firstsave);
	void _SaveQuestLogEntry(QueryBuffer * buf);
	void _LoadQuestLogEntry(QueryResult * result);

	void _LoadPet(QueryResult * result);
	void _LoadPetSpells(QueryResult * result);
	void _SavePet(QueryBuffer * buf);
	void _SavePetSpells(QueryBuffer * buf);
	void _ApplyItemMods( Item* item, int16 slot, bool apply, bool justdrokedown = false, bool skip_stat_apply = false );
	void _EventAttack( bool offhand );
	void _EventExploration();

	// Water level related stuff
	void SetNoseLevel();

	/************************************************************************/
	/* Trade																*/
	/************************************************************************/
	//Item* mTradeItems[8];
	tr1::array< Item *, 8> mTradeItems;
	uint32 mTradeGold;
	uint64 mTradeTarget;
	uint32 mTradeStatus;

    /************************************************************************/
    /* Player Class systems, info and misc things                           */
    /************************************************************************/
    PlayerCreateInfo *info;
	uint32      m_AttackMsgTimer;	// "too far away" and "wrong facing" timer
	bool        m_attacking;
	std::string m_name;	// max 21 character name
	std::string m_name_suffix;		// used by blizz to signal original realm 
	//uint32      m_Tutorials[8];
	tr1::array< uint32, 8 > m_Tutorials; 

    // Character Ban
	uint32      m_banned;
	string      m_banreason;
	Pet*        m_Summon;
	uint32      m_PetNumberMax;
	std::map<uint32, PlayerPet*> m_Pets;
	
    uint32      m_invitersGuid; // It is guild inviters guid ,0 when its not used
    

    // bind
	float m_bind_pos_x;
	float m_bind_pos_y;
	float m_bind_pos_z;
	uint32 m_bind_mapid;
	uint32 m_bind_zoneid;
	SimplePointerList<ItemSet> m_itemsets;
	//Duel
	uint32 m_duelCountdownTimer;
	uint8 m_duelStatus;
	uint8 m_duelState;
	// Rested State Stuff
	uint32 m_timeLogoff;
	// Played time
	//uint32 m_playedtime[3];
	tr1::array< uint32, 3> m_playedtime;
	uint8 m_isResting;
	uint8 m_restState;
	uint32 m_restAmount;
	//combat mods
	float m_blockfromspellPCT;
	float m_critfromspell;
	float m_spellcritfromspell;
	float m_hitfromspell;
	//stats mods
	uint32 m_healthfromspell;
	uint32 m_manafromspell;
	uint32 m_healthfromitems;
	uint32 m_manafromitems;
	
	uint32 armor_proficiency;
	uint32 weapon_proficiency;
	// Talents
	uint32 m_talentresettimes;
	// STATUS
	uint8 m_status;
	// guid of current target
	uint64 m_curTarget;
	// guid of current selection
	uint64 m_curSelection;
	// Raid
	uint8 m_targetIcon;
	//Player Action Bar
	//ActionButton mActions[PLAYER_ACTION_BUTTON_SIZE];
	tr1::array< ActionButton, PLAYER_ACTION_BUTTON_SIZE> mActions;
	// Player Reputation
	ReputationMap m_reputation;
	// Pointer to this char's game client
	WorldSession *m_session;
	// Channels
	std::set<Channel*> m_channels;
	// Visible objects
	std::set<Object*> m_visibleObjects;
	// Groups/Raids
	uint32 m_GroupInviter;
	uint8 m_StableSlotCount;

    // Fishing related
	Object *m_SummonedObject;

    // other system
	//Corpse *    myCorpse;		//and what if map unloads and deletes the corpse ? Invalid pointer reference ?
	uint32		m_myCorpseLowGuid;

	uint32      m_lastHonorResetTime;
	uint32      _fields[PLAYER_END];
	int			hearth_of_wild_pct;		//druid hearth of wild talent used on shapeshifting. We eighter know what is last talent level or memo on learn

	uint32 m_team;
	float       m_lastRunSpeed;
	float       m_lastRunBackSpeed;
	float       m_lastSwimSpeed;
	float       m_lastBackSwimSpeed;
	float       m_lastFlySpeed;

	uint32 m_mountCheckTimer;
	void RemovePendingPlayer();
public:
	void ClearReputations() { m_reputation.clear(); }	//you sure you want to do this ?
#ifdef ENABLE_COMPRESSED_MOVEMENT
	void EventDumpCompressedMovement();
	void AppendMovementData(uint32 op, uint32 sz, const uint8* data);
	Mutex m_movementBufferLock;
	ByteBuffer m_movementBuffer;
#endif

	void addDeletedSpell(uint32 id) { mDeletedSpells.insert( id ); }

	map<uint32, uint32> m_forcedReactions;

	uint32 m_flyhackCheckTimer;
	void _FlyhackCheck();

	bool m_passOnLoot;
	uint32 m_tradeSequence;
	bool m_changingMaps;

	/************************************************************************/
	/* SOCIAL                                                               */
	/************************************************************************/
private:
	/* we may have multiple threads on this(chat) - burlex */
	Mutex m_socialLock;
	map<uint32, char*> m_friends;
	set<uint32> m_ignores;
	set<uint32> m_hasFriendList;

	void Social_SendFriendList(uint32 flag);
	
	void Social_AddFriend(const char * name, const char * note);
	void Social_RemoveFriend(uint32 guid);
	
	void Social_AddIgnore(const char * name);
	void Social_RemoveIgnore(uint32 guid);

	void Social_SetNote(uint32 guid, const char * note);

public:
	bool Social_IsIgnoring(PlayerInfo * m_info);
	bool Social_IsIgnoring(uint32 guid);

	void Social_TellFriendsOnline();
	void Social_TellFriendsOffline();

	/************************************************************************/
	/* end social                                                           */
	/************************************************************************/

	PlayerInfo * m_playerInfo;
	uint32 m_outStealthDamageBonusPct;
	uint32 m_outStealthDamageBonusPeriod;
	uint32 m_outStealthDamageBonusTimer;

    /************************************************************************/
    /* Player Archievements						                            */
    /************************************************************************/
public:
	//this may change in time, We will call it each time a new monitored position is reached
	//it is up to this function to decide if we actually made an archievement in that type or not
	bool Achiement_Finished_Add(uint32 AchievementID); //so we can use it with GM commands
	bool Achiement_Has_Finished(uint32 AchievementID); //so we can use it with GM commands
	void Achiement_Remove(uint32 AchievementID); //so we can use it with GM commands
	void Event_Achiement_Received(uint32 achievementtype,uint32 check_1,uint32 check_2,uint32 mod_val,uint32 action); //entry is not always used
	void GiveAchievementReward(AchievementEntry const* entry);
	void SendAchievmentStatus( uint32 criteriaid, uint32 new_value, uint32 at_stamp=0 );
	void SendAchievmentEarned( uint32 archiId, uint32 at_stamp=0 );
//	void SendAllAchievementEarned();
//	void SendAllAchievementStatus();
	void SendAllAchievementData(); //used on login
	//id and the status
	std::map<uint32,AchievementVal*> m_achievements;
	uint32 m_achievement_points; // for quick check in case it is used as currency
private:
    /************************************************************************/
    /* Player Archievements - end				                            */
    /************************************************************************/
    /************************************************************************/
    /* Player Glyphs							                            */
    /************************************************************************/
	void UpdateGlyphsAvail();
    /************************************************************************/
    /* Player DK Rune sistem					                            */
    /************************************************************************/
public:
	//float m_runes[TOTAL_USED_RUNES]; //runes regen over 10 seconds and they deplete based on spells. Spellcasts replenish runic power
	tr1::array< float, TOTAL_USED_RUNES> m_runes;
	//uint8 m_rune_types[TOTAL_USED_RUNES];
	tr1::array< uint8, TOTAL_USED_RUNES> m_rune_types;
	uint8 GetFullRuneCount(uint8 type);
	uint8 TakeFullRuneCount(uint8 type, uint8 count);
	void UpdateRuneIcon(uint8 rune_index);
	void ConvertRuneIcon(uint8 index,uint8 dst_rune_type);
	void UpdateRuneCooldowns();
	void ClearRuneCooldown(uint8 index);

//	uint32	m_custom_flags;

	void	RemoveAndMailItemFromSlot(uint8 slot);
	void	RemoveAndMailItem(Item **it);

	int32	m_Talent_point_mods;			// DK will receive talent points from quests
	int32	m_dmg_made_since_login;			// some spells use the amount of dmg we did in a period to calculate the effect of the spell
	int32	m_heal_made_since_login;		// used mostly fro statistics.
	int32	m_dmg_received_since_login;		// some spells use the amount of dmg we did in a period to calculate the effect of the spell
	int32	m_heal_received_since_login;	// used mostly fro statistics.
	int32	m_dmg_made_last_time;			// needed for spells
	int32	last_received_move_opcode;		// used to see if we can supress move packets
	bool	ignoreShapeShiftChecks;

	// update (A9) related stuff. Making update packets represents 57% of memory allocations on a live server
	uint8	update_buffer[MAX_SEND_BUFFER_SIZE];			//instead of all those allocations. 1000 players mean 65 Mb ram !
	uint8	zlib_update_buffer[MAX_SEND_BUFFER_SIZE];		//instead of all those allocations. 1000 players mean 65 Mb ram !
	z_stream zlib_stream;

	uint8	has_mixology_talent;			//	only affects potions
	uint8	has_alchemist_stone_effect;		//	only affects potions
	uint8	pet_extra_talent_points;		//  hunters have a talent like this

	//these are used by blizz to generate some mob strengths in instances. Ex : The eye : dragonlings health and dmg
	uint32	item_level_sum;					// used in some formulas to be able to compare player strength 
	uint32	item_enchant_level_sum;			// used in some formulas to be able to compare player strength 
	uint32	item_count_sum;					// to to be able to make avg player strength also
	/************************************************************************/
	/* Drunk system                                                         */
	/************************************************************************/
	void SetDrunkValue( uint16 newDrunkValue, uint32 itemid = 0 );
	uint16 GetDrunkValue() 
	{ 
		INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		return ( GetUInt32Value(PLAYER_BYTES_3) & 0xFFFE); 
	}
	DrunkenState GetDrunkenstateByValue( uint16 value );
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// void HandleSpellLoot( uint32 itemid )
	//  Generates loot for the spell loot item (clams for example) , then adds the generated loot to the Player
	//
	// Parameters:
	//  uint32 itemid   -  unique numerical identifier of the item the Player is looting
	//
	// Return Value:
	//  None.
	///////////////////////////////////////////////////////////////////////////////
	void HandleSpellLoot( uint32 itemid );
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //  void LearnTalent( uint32 talentid, uint32 rank )
    //    Teaches a talentspell to the Player and decreases the available talent points
    //
    //
    //  Parameters:
    //   uint32 talentid     -   unique numeric identifier of the talent (index of talent.dbc )
    //   uint32 rank         -   rank of the talent
	//   bool isPreviewed	 -   true if called from the preview system
    //
    //  Return Value:
    //   None.
    //  
    ////////////////////////////////////////////////////////////////////////////////////////////////
    void LearnTalent( uint32 talentid, uint32 rank, bool isPreviewed = false ); 
	SpellEntry *last_casted_enemy_spell;

	uint32 mount_look_override;
	uint32	mana_burn_target,mana_burn_target_cast;

	uint32 last_mana_regen_stamp;		//cause we need mana regen precision

	std::string only_player_gm;
	int32	XPModBonusPCT;
	int32	HonorModBonusPCT;
	float	ModAbillityAPBonusCoef;		//the amount of DK abilities will benefit this bonus
	int32	IgnoreSpellSpecialCasterStateRequirement;

	UnitToUnitPossitionAdjuster	SummonPosAdjuster;
//	UnitToUnitPossitionAdjuster	*AttackerPosAdjuster;
	float GetSummonAngle(const uint64 &guid){ return SummonPosAdjuster.GetUnitAngle( guid ); }
	//maybe later remake this with triggers. Right now a lot of glyphs have no common effect so it is not worth implementing triggers
	bool  HasGlyphWithID(uint32 glyphID );
	uint32	m_time_sync_send_counter;
	void	SendTimeSyncRequest();
	SimplePointerList<GOSummon>	PossibleGoSummons;	//this does not mean they are all active. This is the list to avoid spawn spamming
	void SendItemPushResult( bool created, bool recieved, bool sendtoset, bool newitem,  uint8 destbagslot, uint32 destslot, uint32 count, uint32 entry, uint32 suffix, uint32 randomprop, uint32 stack );
	uint32 GetInitialFactionId();
	ARCEMU_INLINE void SendTriggerMovie(uint32 movieId);
	//anti gold bug protection. Gold resets after 214k
	ARCEMU_INLINE uint32 Player::GetGold()
	{ 
		return GetUInt32Value(PLAYER_FIELD_COINAGE); 
	}
	ARCEMU_INLINE void Player::SetGold(uint32 new_val)
	{ 
		SetUInt32Value(PLAYER_FIELD_COINAGE,new_val);
	}
	ARCEMU_INLINE void ModGold(int32 mod)
	{ 
		int64 old_gold = GetGold();
		uint32 new_gold;
		if( mod < 0 && old_gold < -mod )
			new_gold = 0;
		else if( old_gold + mod >= 0xFFFFFFFF )
			new_gold = (uint32)0xFFFFFFF0;
		else
			new_gold = (uint32)(old_gold + mod);
		Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_GOLD_VALUE_OWNED,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,new_gold,ACHIEVEMENT_EVENT_ACTION_SET_MAX);
		SetGold(new_gold); 
	}
	ARCEMU_INLINE bool HasGold( uint32 coins ){	return (GetUInt32Value(PLAYER_FIELD_COINAGE) >= coins);	}

	//lfg system
	std::string						LFG_comment;
	uint32							LFG_roles; //(32 bits!)				//he bends over if you drop the soap
	CommitPointerList<LFG_store>	LFG_dungeons;
	uint32							LFG_joined_queue;		//used to aproximate avg wait time based on roles
	uint32							RB_map_id;				//filter server response list : raid browser map id
	uint32							RB_type;				//filter server response list : 10 man, dungeon ....
	void							LFG_UpdateClientUI(uint8 UpdateType);
	void							LFG_PartyUpdateClientUI(uint8 UpdateType);
	void							LFG_JoinResponse(uint8 checkResult, uint8 checkValue);
	bool							RB_IsLookingFor( uint32 map_id, uint32 type );
	uint32							LFG_GetGearScore( ) { return (item_level_sum+item_enchant_level_sum); }	//might not be what you expect it to be. But better then nothing
//	uint32							LFG_selected_MAP_ID;
//	uint8							LFG_selected_Type;
//	bool							LFG_Autojoin;
//	bool							LFG_AutoAddMem;
//	LfgMatch * m_lfgMatch;
//	uint32 m_lfgInviterGuid;
	void EventTimeoutLfgInviter();

	//equipment manager - another aproach coul dbe to simply attach a guid/index to items ?
	CommitPointerList<EquipmentSet> m_EquipmentSets;
	void							SendEquipmentSetList();
	void							DeleteEquipmentSet( uint64 GUID );
	void							_SaveEquipmentSets(QueryBuffer * buf);
	void							_LoadEquipmentSets(QueryResult * result);

	//gm statistic related stuff
#if GM_STATISTICS_UPDATE_INTERVAL > 0 
	GM_statistics					*m_GM_statistics;
#endif
};

class SkillIterator
{
	SkillMap::iterator m_itr;
	SkillMap::iterator m_endItr;
	bool m_searchInProgress;
	Player * m_target;
public:
	SkillIterator(Player* target) : m_searchInProgress(false),m_target(target) {}
	~SkillIterator() { if(m_searchInProgress) { EndSearch(); } }

	void BeginSearch()
	{
		// iteminterface doesn't use mutexes, maybe it should :P
		ASSERT(!m_searchInProgress);
		m_itr = m_target->m_skills.begin();
		m_endItr = m_target->m_skills.end();
		m_searchInProgress=true;
	}

	void EndSearch()
	{
		// nothing here either
		ASSERT(m_searchInProgress);
		m_searchInProgress=false;
	}

	PlayerSkill* operator*() const
	{
		return &m_itr->second;
	}

	PlayerSkill* operator->() const
	{
		return &m_itr->second;
	}

	void Increment()
	{
		if(!m_searchInProgress)
			BeginSearch();

		if(m_itr==m_endItr)
			return;

		++m_itr;
	}

	ARCEMU_INLINE PlayerSkill* Grab() { return &m_itr->second; }
	ARCEMU_INLINE bool End() { return (m_itr==m_endItr)?true:false; }
};

#ifdef ENABLE_COMPRESSED_MOVEMENT

class CMovementCompressorThread : public ThreadBase
{
	bool running;
	Mutex m_listLock;
	set<Player*> m_players;
public:
	CMovementCompressorThread() { running = true; }

	void AddPlayer(Player * pPlayer);
	void RemovePlayer(Player * pPlayer);

	void OnShutdown() { running = false; }
	bool run();
};

extern CMovementCompressorThread * MovementCompressor;

#endif

#endif
