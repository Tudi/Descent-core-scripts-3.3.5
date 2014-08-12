/*
 * ArcEmu MMORPG Server
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

#ifndef __SPELLSTORE_H
#define __SPELLSTORE_H

#include "Common.h"
#include "DataStore.h"
#include "Timer.h"

#pragma pack(push,1)

struct LFGDungeonEntry
{
    uint32  ID;                                             // 0
    //char*   name[16];                                     // 1-17 Name lang
	//uint32	name_flags;
    uint32  minlevel;                                       // 18
    uint32  maxlevel;                                       // 19
    uint32  reclevel;                                       // 20
    uint32  recminlevel;                                    // 21
    uint32  recmaxlevel;                                    // 22
    int32	map_id;                                         // 23
    uint32  difficulty;                                     // 24 - heroic or not
    //uint32  unk;                                          // 25
    uint32  type;                                           // 26
    //uint32  unk2;                                         // 27
    //char*   unk3;                                         // 28
    uint32  expansion;                                      // 29
    //uint32  unk4;                                         // 30
    uint32  grouptype;                                      // 31
};

//does not seem to be usable. More like give info what is allowed to be leanrned
struct SkillRaceClassInfo
{
	uint32	Id;
	uint32	skill_ID;
	uint32	race_mask;
	uint32	class_mask;
	uint32	unk_flags;	
	uint32	col_5;		//mostly depracated skills	
	uint32	col_6;		//seems like grouping. Maybe flag based ? Ex : language, riding, profession
	uint32  col_7;		//seems like unavailable skills
};

struct WorldMapAreaEntry
{
	uint32	Id;				//row ID for this dbc
	uint32	map_id;			//map for which this this area is assigned
	uint32	zone_id;		//name of the zone we are delimiting
	char	*name;			//name of the zone
	float	max_y,min_y;
	float	max_x,min_x;
//	int32	unk1,unk2;		//first one seems to be always -1 the other one always 0
};

struct VehicleEntry
{
	uint32 m_ID;
	uint32 m_flags;
	float m_turnSpeed;
	float m_pitchSpeed;
	float m_pitchMin;
	float m_pitchMax;
	uint32 m_seatID[8];
	float m_mouseLookOffsetPitch;
	float m_cameraFadeDistScalarMin;
	float m_cameraFadeDistScalarMax;
	float m_cameraPitchOffset;
	float m_facingLimitRight;
	float m_facingLimitLeft;
	float m_msslTrgtTurnLingering;
	float m_msslTrgtPitchLingering;
	float m_msslTrgtMouseLingering;
	float m_msslTrgtEndOpacity;
	float m_msslTrgtArcSpeed;
	float m_msslTrgtArcRepeat;
	float m_msslTrgtArcWidth;
	float m_msslTrgtImpactRadius[2];
	char* m_msslTrgtArcTexture;
	char* m_msslTrgtImpactTexture;
	char* m_msslTrgtImpactModel[2];
	float m_cameraYawOffset;
	uint32 m_uiLocomotionType;
	float m_msslTrgtImpactTexRadius;
	uint32 m_uiSeatIndicatorType;
	uint32  m_powerType;
};

struct VehicleSeatEntry
{
    uint32  m_ID;                                           // 0
    uint32  m_flags;                                        // 1
    int32   m_attachmentID;                                 // 2
    float   m_attachmentOffsetX;                            // 3
    float   m_attachmentOffsetY;                            // 4
    float   m_attachmentOffsetZ;                            // 5
    float   m_enterPreDelay;                                // 6
    float   m_enterSpeed;                                   // 7
    float   m_enterGravity;                                 // 8
    float   m_enterMinDuration;                             // 9
    float   m_enterMaxDuration;                             // 10
    float   m_enterMinArcHeight;                            // 11
    float   m_enterMaxArcHeight;                            // 12
    int32   m_enterAnimStart;                               // 13
    int32   m_enterAnimLoop;                                // 14
    int32   m_rideAnimStart;                                // 15
    int32   m_rideAnimLoop;                                 // 16
    int32   m_rideUpperAnimStart;                           // 17
    int32   m_rideUpperAnimLoop;                            // 18
    float   m_exitPreDelay;                                 // 19
    float   m_exitSpeed;                                    // 20
    float   m_exitGravity;                                  // 21
    float   m_exitMinDuration;                              // 22
    float   m_exitMaxDuration;                              // 23
    float   m_exitMinArcHeight;                             // 24
    float   m_exitMaxArcHeight;                             // 25
    int32   m_exitAnimStart;                                // 26
    int32   m_exitAnimLoop;                                 // 27
    int32   m_exitAnimEnd;                                  // 28
    float   m_passengerYaw;                                 // 29
    float   m_passengerPitch;                               // 30
    float   m_passengerRoll;                                // 31
    int32   m_passengerAttachmentID;                        // 32
    int32   m_vehicleEnterAnim;                             // 33
    int32   m_vehicleExitAnim;                              // 34
    int32   m_vehicleRideAnimLoop;                          // 35
    int32   m_vehicleEnterAnimBone;                         // 36
    int32   m_vehicleExitAnimBone;                          // 37
    int32   m_vehicleRideAnimLoopBone;                      // 38
    float   m_vehicleEnterAnimDelay;                        // 39
    float   m_vehicleExitAnimDelay;                         // 40
    uint32  m_vehicleAbilityDisplay;                        // 41
    uint32  m_enterUISoundID;                               // 42
    uint32  m_exitUISoundID;                                // 43
    int32   m_uiSkin;                                       // 44
    uint32  m_flagsB;                                       // 45
	bool IsUsable() const { return ((m_flags & 0x2000000)!=0); } 
};

struct CurrencyTypesEntry
{
    //uint32    ID;                                       // 0 not used
    uint32    ItemId;                                     // 1 used as real index
    //uint32    Category;                                 // 2 may be category
    uint32    BitIndex;                                   // 3 bit index in PLAYER_FIELD_KNOWN_CURRENCIES (1 << (index-1))
};

struct WorldMapOverlay
{
	uint32 ID;           // 0
//	uint32 worldMapID;   // 1
	uint32 areaID;       // 2 - index to AreaTable
	uint32 areaID_2;     // 3 - index to AreaTable
	uint32 areaID_3;     // 4 - index to AreaTable
	uint32 areaID_4;     // 5 - index to AreaTable
// any of the four above indexes is enough to uncover the fragment
};


struct BattlemasterListEntry
{
	uint32	bg_index;
	int32	maps[8];
	uint32	instance_type;
//	uint32	max_players_per_faction;	// R.I.P.
//	uint32	min_players_per_faction;	//not anymore
//	uint32	someflags2;
//	uint32	flag; // EOTS AND SOTA have this set to nine, otherwise it's zero
//	uint32  always_true;
//	char	*names[15];
//	uint32	nameflags;
	uint32	min_player_count;		//seems to be valid for 3.3.3 but changed a lot
	uint32  area_or_trigger_id;		//not sure
	uint32	minimum_player_level; // ??? Is it, 3.0.8 doesn't match 3.0.3 numbers
								 // Do not use for now (NAQUADA)
	uint32	maximum_player_level;	//just 80
};

struct AreaGroup
{
	uint32 AreaGroupId;
	uint32 AreaId[ 7 ];
};

struct SpellRuneCostEntry
{
	uint32 Id;
	uint32 costs[ 3 ]; //death rune is optional
	uint32 runic_power_conversion;
};

struct GlyphPropertiesEntry
{
    uint32  Id;
    uint32  SpellId;
    uint32  TypeFlags;
    uint32  Unk1;
};

struct GlyphSlotEntry
{
    uint32  Id;
    uint32  TypeFlags;
    uint32  Order;
};

struct BarberShopStyleEntry
{
    uint32 Id; // 0
    //uint32 type; // 1 value 0 -> hair, value 2 -> facialhair
    //char* name[16]; // 2-17 name of hair style
    //uint32 name_flags; // 18
    //uint32 unk_name[16]; // 19-34, all empty
    //uint32 unk_flags; // 35
    //float unk3; // 36 values 1 and 0,75
    //uint32 race; // 37 race
    //uint32 gender; // 38 0 -> male, 1 -> female
    uint32 hair_id; // 39 real ID to hair/facial hair
};

struct GtBarberShopCostBaseEntry
{
    float   cost;
};

/*
struct AchievementEntry
{
    uint32    ID;                                           // 0
    uint32    factionFlag;                                  // 1 -1=all, 0=horde, 1=alliance
    uint32    mapID;                                        // 2 -1=none
    //uint32 parentAchievement;                             // 3 its Achievement parent (can`t start while parent uncomplete, use its Criteria if don`t have own, use its progress on begin)
    char *name;                                          // 4-19
//    char *name[15+1];                                         // 4-19
    //uint32 name_flags;                                    // 20
    //char *description[16];                                // 21-36
    //uint32 desc_flags;                                    // 37
    uint32    categoryId;                                   // 38
    uint32    points;                                       // 39 reward points
    //uint32 OrderInCategory;                               // 40
    uint32    flags;                                        // 41
    //uint32    icon;                                       // 42 icon (from SpellIcon.dbc)
    //char *titleReward[16];                                // 43-58
    //uint32 titleReward_flags;                             // 59
    uint32 count;                                           // 60 - need this count of completed criterias (own or referenced achievement criterias)
    uint32 refAchievement;                                  // 61 - referenced achievement (counting of all completed criterias)
}; */
struct AchievementEntry
{
	uint32      ID;                                           // 0
	int32       factionFlag;                                  // 1 -1=all, 0=horde, 1=alliance
	int32       mapID;                                        // 2 -1=none
	uint32      unknown1;                                     // 20
	const char* name;                                         // 3-18
	uint32      name_flags;                                   // 19
	const char* description;                                  // 21-36
	uint32      desc_flags;                                   // 37
	uint32      categoryId;                                   // 38 - like exploration achievements
	uint32      points;                                       // 39 reward points
	uint32      orderInCategory;                              // 40
	uint32      flags;                                        // 41
	uint32      unknown2;                                     // 42
	const char* rewardName;                                   // 43-58 title/item reward name
	uint32      rewardName_flags;                             // 59
	uint32      count;                                        // 60
	uint32      refAchievement;                               // 61
};


#define	 ACHIEVEMENT_CRITERIA_COMPLETE_FLAG_ALL  2 //complete one and completes all. ex 689
#define  ACHIEVEMENT_CRITERIA_GROUP_NOT_IN_GROUP 2 //only if not in group

enum AchievementCriteriaTypes
{
    ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE = 0,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_BG = 1,
    ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL = 5,
    ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL = 7,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ARCHIEVEMENT = 8,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST_COUNT = 9,
    // you have to complete a daily quest x times in a row
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST_DAILY = 10,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUESTS_IN_ZONE = 11,
	ACHIEVEMENT_CRITERIA_TYPE_DAMAGE_DONE            = 13,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST = 14,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_BATTLEGROUND= 15,
    ACHIEVEMENT_CRITERIA_TYPE_DEATH_AT_MAP= 16,
    // TODO: this can be both arena and total deaths. Where is this difference in the dbc?
    ACHIEVEMENT_CRITERIA_TYPE_DEATH= 17,
    ACHIEVEMENT_CRITERIA_TYPE_DEATH_IN_DUNGEON = 18,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_RAID = 19,
    ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_CREATURE = 20,
    ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_PLAYER = 23,
    ACHIEVEMENT_CRITERIA_TYPE_FALL_WITHOUT_DYING = 24,
	ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM = 26,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST = 27,
    ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET = 28,
    ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL= 29,
    ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE = 30,
    ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL_AT_AREA = 31,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_ARENA = 32,
    ACHIEVEMENT_CRITERIA_TYPE_PLAY_ARENA = 33,
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SPELL = 34,
    // TODO: this criteria has additional conditions which can not be found in the dbcs
    ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL = 35,
    ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM = 36,
    // TODO: the archievements 1162 and 1163 requires a special rating which can't be found in the dbc
    ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA = 37,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_TEAM_RATING = 38,
    ACHIEVEMENT_CRITERIA_TYPE_REACH_TEAM_RATING = 39,
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LEVEL = 40,
    ACHIEVEMENT_CRITERIA_TYPE_USE_ITEM = 41,
    ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM= 42,
    ACHIEVEMENT_CRITERIA_TYPE_EXPLORE_AREA = 43,
    ACHIEVEMENT_CRITERIA_TYPE_OWN_PVP_RANK= 44,
    ACHIEVEMENT_CRITERIA_TYPE_BUY_BANK_SLOT= 45,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_REPUTATION= 46,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_EXALTED_REPUTATION= 47,
    // noted: rewarded as soon as the player payed, not at taking place at the seat
    ACHIEVEMENT_CRITERIA_TYPE_VISIT_BARBER_SHOP= 48,
    ACHIEVEMENT_CRITERIA_TYPE_EQUIP_EPIC_ITEM = 49,
    // TODO: itemlevel is mentioned in text but not present in dbc
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED_ON_LOOT = 50,
	ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED_ON_LOOT      = 51,
    ACHIEVEMENT_CRITERIA_TYPE_HK_CLASS = 52,
    ACHIEVEMENT_CRITERIA_TYPE_HK_RACE = 53,
    ACHIEVEMENT_CRITERIA_TYPE_DO_EMOTE = 54,
    ACHIEVEMENT_CRITERIA_TYPE_HEALING_DONE = 55,
	ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS      = 56,
    ACHIEVEMENT_CRITERIA_TYPE_EQUIP_ITEM = 57,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_FROM_VENDORS = 59,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TALENTS = 60,
    ACHIEVEMENT_CRITERIA_TYPE_NUMBER_OF_TALENT_RESETS = 61,
	ACHIEVEMENT_CRITERIA_TYPE_MONEY_FROM_QUEST_REWARD= 62,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TRAVELLING = 63,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_AT_BARBER = 65,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_MAIL = 66,
    ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY = 67,
    ACHIEVEMENT_CRITERIA_TYPE_USE_GAMEOBJECT = 68,
    ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2= 69,
    ACHIEVEMENT_CRITERIA_TYPE_SPECIAL_PVP_KILL= 70,
    ACHIEVEMENT_CRITERIA_TYPE_FISH_IN_GAMEOBJECT = 72,
    // TODO: title id is not mentioned in dbc
    ACHIEVEMENT_CRITERIA_TYPE_EARNED_PVP_TITLE = 74,
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILLLINE_SPELLS= 75,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_DUEL = 76,
    ACHIEVEMENT_CRITERIA_TYPE_LOSE_DUEL = 77,
    // TODO: creature type (demon, undead etc.) is not stored in dbc
    ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE_TYPE = 78,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_EARNED_BY_AUCTIONS= 80,
    ACHIEVEMENT_CRITERIA_TYPE_CREATE_AUCTION= 82,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_AUCTION_BID= 83,
    ACHIEVEMENT_CRITERIA_TYPE_WON_AUCTIONS= 84,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_AUCTION_SOLD = 85,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_GOLD_VALUE_OWNED = 86,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_REVERED_REPUTATION = 87,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_HONORED_REPUTATION = 88,
    ACHIEVEMENT_CRITERIA_TYPE_KNOWN_FACTIONS = 89,
    ACHIEVEMENT_CRITERIA_TYPE_LOOT_EPIC_ITEM = 90,
    ACHIEVEMENT_CRITERIA_TYPE_RECEIVE_EPIC_ITEM = 91,
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED = 93,
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED = 94,
//    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEALTH = 95,
//    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_POWER = 96,
//    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_STAT = 97,
//    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_SPELLPOWER = 98,
//    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_ARMOR = 99,
//    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_RATING = 100,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HIT_DEALT = 101,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HIT_RECEIVED = 102,
    ACHIEVEMENT_CRITERIA_TYPE_TOTAL_DAMAGE_RECEIVED = 103,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEAL_CASTED = 104,
    ACHIEVEMENT_CRITERIA_TYPE_TOTAL_HEALING_RECEIVED = 105,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEALING_RECEIVED = 106,
    ACHIEVEMENT_CRITERIA_TYPE_QUEST_ABANDONED = 107,
    ACHIEVEMENT_CRITERIA_TYPE_FLIGHT_PATHS_TAKEN = 108,
    ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE = 109,
    // TODO: target entry is missing
    ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL2 = 110,
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LINE_SPELL2 = 112,
    ACHIEVEMENT_CRITERIA_TYPE_EARN_HONORABLE_KILL = 113,
    ACHIEVEMENT_CRITERIA_TYPE_ACCEPTED_SUMMONINGS = 114,
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_DISENCHANT = 117,
    // 0..114 => 115 criteria types total
    ACHIEVEMENT_CRITERIA_TYPE_TOTAL = 125,
};
 
#define ACHIVEMENTS_EVIL_PENDING_STATUS_FLAG 0x01000000

//should have named this a simple achievemnt entry
struct AchievementCriteriaEntry
{
    uint32  ID;                                             // 0
    uint32  referredAchievement;                            // 1
    uint32  requiredType;                                   // 2
    union
    {
        // ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE          = 0
        // TODO: also used for player deaths..
        struct
        {
            uint32  creatureID;                             // 3
            uint32  creatureCount;                          // 4
        } kill_creature;

        // ACHIEVEMENT_CRITERIA_TYPE_WIN_BG                 = 1
        struct
        {
            uint32  bgMapID;                                // 3
            uint32  winCount;                               // 4
            uint32  additionalRequirement1_type;            // 5 additional requirement 1 type
            uint32  additionalRequirement1_value;           // 6 additional requirement 1 value
            uint32  additionalRequirement2_type;            // 7 additional requirement 2 type
            uint32  additionalRequirement2_value;           // 8 additional requirement 1 value
        } win_bg;

        // ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL            = 5
        struct
        {
            uint32  unused;                                 // 3
            uint32  level;                                  // 4
        } reach_level;

        // ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL      = 7
        struct
        {
            uint32  skillID;                                // 3
            uint32  skillLevel;                             // 4
        } reach_skill_level;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT   = 8
        struct
        {
            uint32  linkedAchievement;                      // 3
        } complete_achievement;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST_COUNT   = 9
        struct
        {
            uint32  unused;                                 // 3
            uint32  totalQuestCount;                        // 4
        } complete_quest_count;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST_DAILY = 10
        struct
        {
            uint32  unused;                                 // 3
            uint32  numberOfDays;                           // 4
        } complete_daily_quest_daily;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUESTS_IN_ZONE = 11
        struct
        {
            uint32  zoneID;                                 // 3
            uint32  questCount;                             // 4
        } complete_quests_in_zone;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST   = 14
        struct
        {
            uint32  unused;                                 // 3
            uint32  questCount;                             // 4
        } complete_daily_quest;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_BATTLEGROUND  = 15
        struct
        {
            uint32  mapID;                                  // 3
        } complete_battleground;

        // ACHIEVEMENT_CRITERIA_TYPE_DEATH_AT_MAP           = 16
        struct
        {
            uint32  mapID;                                  // 3
        } death_at_map;

        // ACHIEVEMENT_CRITERIA_TYPE_DEATH_IN_DUNGEON       = 18
        struct
        {
            uint32  manLimit;                               // 3
        } death_in_dungeon;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_RAID          = 19
        struct
        {
            uint32  groupSize;                              // 3 can be 5, 10 or 25
        } complete_raid;

        // ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_CREATURE     = 20
		// ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_PLAYER		= 23
        struct
        {
            uint32  creatureEntry;                          // 3
        } killed_by_creature;

        // ACHIEVEMENT_CRITERIA_TYPE_FALL_WITHOUT_DYING     = 24
        struct
        {
            uint32  unused;                                 // 3
            uint32  fallHeight;                             // 4
        } fall_without_dying;

        // ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM            = 26
        struct
        {
            uint32 type;                                    // 3, see enum EnviromentalDamage
        } death_from;

        // ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST         = 27
        struct
        {
            uint32  questID;                                // 3
            uint32  questCount;                             // 4
        } complete_quest;

        // ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET        = 28
        // ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2       = 69
        struct
        {
            uint32  spellID;                                // 3
            uint32  spellCount;                             // 4
        } be_spell_target;

        // ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL             = 29
        // ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL2            = 110
        struct
        {
            uint32  spellID;                                // 3
            uint32  castCount;                              // 4
        } cast_spell;

        // ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL_AT_AREA = 31
        struct
        {
            uint32  areaID;                                 // 3 Reference to AreaTable.dbc
            uint32  killCount;                              // 4
        } honorable_kill_at_area;

        // ACHIEVEMENT_CRITERIA_TYPE_WIN_ARENA              = 32
        struct
        {
            uint32  mapID;                                  // 3 Reference to Map.dbc
        } win_arena;

        // ACHIEVEMENT_CRITERIA_TYPE_PLAY_ARENA             = 33
        struct
        {
            uint32  mapID;                                  // 3 Reference to Map.dbc
        } play_arena;

        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SPELL            = 34
        struct
        {
            uint32  spellID;                                // 3 
        } learn_spell;

        // ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM               = 36
        struct
        {
            uint32  itemID;                                 // 3
            uint32  itemCount;                              // 4
        } own_item;

        // ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA        = 37
        struct
        {
            uint32  unused;                                 // 3
            uint32  count;                                  // 4
            uint32  flag;                                   // 5 4=in a row
        } win_rated_arena;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_TEAM_RATING    = 38
        struct
        {
            uint32  teamtype;                               // 3 {2,3,5}
        } highest_team_rating;

        // ACHIEVEMENT_CRITERIA_TYPE_REACH_TEAM_RATING      = 39
        struct
        {
            uint32  teamtype;                               // 3 {2,3,5}
            uint32  teamrating;                             // 4
        } reach_team_rating;

        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LEVEL      = 40
        struct
        {
            uint32  skillID;                                // 3
            uint32  skillLevel;                             // 4 apprentice=1, journeyman=2, expert=3, artisan=4, master=5, grand master=6
        } learn_skill_level;

        // ACHIEVEMENT_CRITERIA_TYPE_USE_ITEM               = 41
        struct
        {
            uint32  itemID;                                 // 3
            uint32  itemCount;                              // 4
        } use_item;

        // ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM              = 42
        struct
        {
            uint32  itemID;                                 // 3
            uint32  itemCount;                              // 4
        } loot_item;

        // ACHIEVEMENT_CRITERIA_TYPE_EXPLORE_AREA           = 43
        struct
        {
            // TODO: This rank is _NOT_ the index from AreaTable.dbc
            uint32  areaReference;                          // 3
        } explore_area;

        // ACHIEVEMENT_CRITERIA_TYPE_OWN_PVP_RANK               = 44
        struct
        {
            // TODO: This rank is _NOT_ the index from CharTitles.dbc
            uint32  rank;                                   // 3
        } own_rank;

        // ACHIEVEMENT_CRITERIA_TYPE_BUY_BANK_SLOT          = 45
        struct
        {
            uint32  unused;                                 // 3
            uint32  numberOfSlots;                          // 4
        } buy_bank_slot;

        // ACHIEVEMENT_CRITERIA_TYPE_GAIN_REPUTATION        = 46
        struct
        {
            uint32  factionID;                              // 3
            uint32  reputationAmount;                       // 4 Total reputation amount, so 42000 = exalted
        } gain_reputation;

        // ACHIEVEMENT_CRITERIA_TYPE_GAIN_EXALTED_REPUTATION= 47
        struct
        {
            uint32  unused;                                 // 3
            uint32  numberOfExaltedFactions;                // 4
        } gain_exalted_reputation;

        // ACHIEVEMENT_CRITERIA_TYPE_VISIT_BARBER_SHOP      = 48
        struct
        {
            uint32 unused;                                  // 3
            uint32 numberOfVisits;                          // 4
        } visit_barber;

        // ACHIEVEMENT_CRITERIA_TYPE_EQUIP_EPIC_ITEM        = 49
        // TODO: where is the required itemlevel stored?
        struct
        {
            uint32  itemSlot;                               // 3
            uint32  count;                                  // 4
        } equip_epic_item;

        // ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED_ON_LOOT      = 50
        struct
        {
            uint32  rollValue;                              // 3
            uint32  count;                                  // 4
        } roll_need_on_loot;
       // ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED_ON_LOOT      = 51
        struct
        {
            uint32  rollValue;                              // 3
            uint32  count;                                  // 4
        } roll_greed_on_loot;

        // ACHIEVEMENT_CRITERIA_TYPE_HK_CLASS               = 52
        struct
        {
            uint32  classID;                                // 3
            uint32  count;                                  // 4
        } hk_class;

        // ACHIEVEMENT_CRITERIA_TYPE_HK_RACE                = 53
        struct
        {
            uint32  raceID;                                 // 3
            uint32  count;                                  // 4
        } hk_race;

        // ACHIEVEMENT_CRITERIA_TYPE_DO_EMOTE               = 54
        // TODO: where is the information about the target stored?
        struct
        {
            uint32  emoteID;                                // 3 enum TextEmotes
            uint32  count;                                  // 4 count of emotes, always required special target or requirements
        } do_emote;
        // ACHIEVEMENT_CRITERIA_TYPE_DAMAGE_DONE            = 13
        // ACHIEVEMENT_CRITERIA_TYPE_HEALING_DONE           = 55
        // ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS      = 56
        struct
        {
            uint32  unused;                                 // 3
            uint32  count;                                  // 4
            uint32  flag;                                   // 5 =3 for battleground healing
            uint32  mapid;                                  // 6
        } healing_done;

        // ACHIEVEMENT_CRITERIA_TYPE_EQUIP_ITEM             = 57
        struct
        {
            uint32  itemID;                                 // 3
            uint32  count;                                  // 4
        } equip_item;

        // ACHIEVEMENT_CRITERIA_TYPE_MONEY_FROM_QUEST_REWARD= 62
        struct
        {
            uint32  unused;                                 // 3
            uint32  goldInCopper;                           // 4
        } quest_reward_money;


        // ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY             = 67
        struct
        {
            uint32  unused;                                 // 3
            uint32  goldInCopper;                           // 4
        } loot_money;

        // ACHIEVEMENT_CRITERIA_TYPE_USE_GAMEOBJECT         = 68
        struct
        {
            uint32  goEntry;                                // 3
            uint32  useCount;                               // 4
        } use_gameobject;

        // ACHIEVEMENT_CRITERIA_TYPE_SPECIAL_PVP_KILL       = 70
        // TODO: are those special criteria stored in the dbc or do we have to add another sql table?
        struct
        {
            uint32  unused;                                 // 3
            uint32  killCount;                              // 4
        } special_pvp_kill;

        // ACHIEVEMENT_CRITERIA_TYPE_FISH_IN_GAMEOBJECT     = 72
        struct
        {
            uint32  goEntry;                                // 3
            uint32  lootCount;                              // 4
        } fish_in_gameobject;

        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILLLINE_SPELLS = 75
        struct
        {
            uint32  skillLine;                              // 3
            uint32  spellCount;                             // 4
        } learn_skillline_spell;

        // ACHIEVEMENT_CRITERIA_TYPE_WIN_DUEL               = 76
        struct
        {
            uint32  unused;                                 // 3
            uint32  duelCount;                              // 4
        } win_duel;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_POWER          = 96
        struct
        {
            uint32  powerType;                              // 3 mana=0, 1=rage, 3=energy, 6=runic power
        } highest_power;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_STAT           = 97
        struct
        {
            uint32  statType;                               // 3 4=spirit, 3=int, 2=stamina, 1=agi, 0=strength
        } highest_stat;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_SPELLPOWER     = 98
        struct
        {
            uint32  spellSchool;                            // 3
        } highest_spellpower;

        // ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_RATING         = 100
        struct
        {
            uint32  ratingType;                             // 3
        } highest_rating;

        // ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE              = 109
        struct
        {
            uint32  lootType;                               // 3 3=fishing, 2=pickpocket, 4=disentchant
            uint32  lootTypeCount;                          // 4
        } loot_type;

        // ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LINE       = 112
        struct
        {
            uint32  skillLine;                              // 3
            uint32  spellCount;                             // 4
        } learn_skill_line;

        // ACHIEVEMENT_CRITERIA_TYPE_EARN_HONORABLE_KILL    = 113
        struct
        {
            uint32  unused;                                 // 3
            uint32  killCount;                              // 4
        } honorable_kill;

        struct
        {
            uint32  requiredAchievementRelatedEntry;        // 3 main requirement
            uint32  requiredAchievementRelatedCount;        // 4 main requirement count
            uint32  additionalRequirement1_type;            // 5 additional requirement 1 type
            uint32  additionalRequirement1_value;           // 6 additional requirement 1 value
            uint32  additionalRequirement2_type;            // 7 additional requirement 2 type
            uint32  additionalRequirement2_value;           // 8 additional requirement 1 value
        } raw;
    };
    //char*  name[16];                                      // 9-24
    //uint32 name_flags;                                    // 25
    uint32  completionFlag;                                 // 26
    uint32  groupFlag;                                      // 27
    //uint32 unk1;                                          // 28 Alway appears with timed events
                                                            // for timed spells it is spell id for
                                                            // timed kills it is creature id
    uint32  timeLimit;                                      // 29 time limit in seconds
    //uint32 showOrder;                                     // 30 show order
	///!!!!!!!!customs !!!!!
	uint32	requires_heroic_instance;						// creature kill type requires instances to have specific mode
	uint32	requires_player_count;							// creature kill type requires instances to have specific mode
	uint32	requires_arenta_team_type_check;				// this seems to available only in the criteria description
};

#define ACHIEVEMENT_UNUSED_FIELD_VALUE	0xFFFFFFFF

struct BankSlotPrice
{
	uint32 Id;
	uint32 Price;
};

struct ItemSetEntry
{
    uint32 id;                  //1
    char* name;                //2
    //uint32 unused_shit[15];      //3 - 9
    uint32 flag;                //10 constant
    uint32 itemid[8];           //11 - 18
    //uint32 more_unused_names[9]; //19 - 27
    uint32 SpellID[8];          //28 - 35
    uint32 itemscount[8];       //36 - 43
    uint32 RequiredSkillID;     //44
    uint32 RequiredSkillAmt;    //45
};

struct Lock
{
    uint32 Id;
    uint32 locktype[5]; // 0 - no lock, 1 - item needed for lock, 2 - min lockping skill needed
    //uint32 unk1[3];
    uint32 lockmisc[5]; // if type is 1 here is a item to unlock, else is unknow for now
    //uint32 unk2[3];
    uint32 minlockskill[5]; // min skill in lockpiking to unlock.
    //uint32 unk3[11];

	/* Actually it is:
	uint32 Id;
    uint32 locktype[8];
    uint32 lockmisc[8];
    uint32 minlockskill[8];
    uint32 action[8];
	*/
};

struct emoteentry
{
    uint32 Id;
    //uint32 name;
    uint32 textid;
    uint32 textid2;
    uint32 textid3;
    uint32 textid4;
    //uint32 unk1;
    uint32 textid5;
    //uint32 unk2;
    uint32 textid6;
    //uint32 unk3;
    //uint32 unk4;
    //uint32 unk5;
    //uint32 unk6;
    //uint32 unk7;
    //uint32 unk8;
    //uint32 unk9;
    //uint32 unk10;
    //uint32 unk11;
};

struct TalentEntry
{
    uint32  TalentID;
    uint32  TalentTree;
    uint32  Row;
    uint32  Col;
    uint32  RankID[5];
    //uint32  unk[4];
    uint32  DependsOn;
    //uint32  unk1[2];
    uint32  DependsOnRank;
    //uint32  unk2[4];
};

struct skilllinespell //SkillLineAbility.dbc
{
    uint32 Id;
    uint32 skilline;
    uint32 spell;
    uint32 raceMask;
	uint32 classMask;
    uint32 excludeRace;
    uint32 excludeClass;
    uint32 minSkillLineRank;
    uint32 next;
    uint32 acquireMethod;
    uint32 grey;
    uint32 green;
    //uint32 unk10;
    //uint32 unk11;
    //uint32 reqTP; //taken out in 303
	//customs 
	uint32 prev;	//customs
};

struct EnchantEntry
{
    uint32 Id;
//	uint32 unk1;
    uint32 type[3];
    int32 min[3];//for compat, in practice min==max
    int32 max[3];
    uint32 spell[3];
    char* Name;
    //uint32 NameAlt1;
    //uint32 NameAlt2;
    //uint32 NameAlt3;
    //uint32 NameAlt4;
    //uint32 NameAlt5;
    //uint32 NameAlt6;
    //uint32 NameAlt7;
    //uint32 NameAlt8;
    //uint32 NameAlt9;
    //uint32 NameAlt10;
    //uint32 NameAlt11;
    //uint32 NameAlt12;
    //uint32 NameAlt13;
    //uint32 NameAlt14;
    //uint32 NameAlt15;
    //uint32 NameFlags;
    uint32 visual;
    uint32 EnchantGroups;
    uint32 GemEntry;
    uint32 unk7;//Gem Related
	uint32 required_skill;
	uint32 required_skill_rank;
	//								//39
	uint32 custom_enchant_group; //this comes from example gem types.There is a high chance this value already exists somewhere
	uint32 custom_enchant_maxstack; //this comes from example gem types
	uint32 custom_GearScore;		//gem level or spell level
};

struct GemPropertyEntry{
    uint32 Entry;
    uint32 EnchantmentID;
    uint32 unk1;//bool - maybe sellable
    uint32 unk2;//bool - maybe sellable
    uint32 SocketMask;
};

struct ItemLimitCategory{
	uint32 CategoryId;
//	uint32 Name1;
//	uint32 NameAlt2;
//	uint32 NameAlt3;
//	uint32 NameAlt4;
//	uint32 NameAlt5;
//	uint32 NameAlt6;
//	uint32 NameAlt7;
//	uint32 NameAlt8;
//	uint32 NameAlt9;
//	uint32 NameAlt10;
//	uint32 NameAlt11;
//	uint32 NameAlt12;
//	uint32 NameAlt13;
//	uint32 NameAlt14;
//	uint32 NameAlt15;
//	uint32 NameAlt16;
//	uint32 NameAlt17;
//	uint32 NameFlags; //not sure they are actually nameflags
	uint32 MaxStack;
//	uint32 unkbool;
};

struct skilllineentry //SkillLine.dbc
{
    uint32 id;
    uint32 type;
    uint32 skillCostsID;
    char* Name;
    //int32 NameAlt1;
    //uint32 NameAlt2;
    //uint32 NameAlt3;
    //uint32 NameAlt4;
    //uint32 NameAlt5;
    //uint32 NameAlt6;
    //uint32 NameAlt7;
    //uint32 NameAlt8;
    //uint32 NameAlt9;
    //uint32 NameAlt10;
    //uint32 NameAlt11;
    //uint32 NameAlt12;
    //uint32 NameAlt13;
    //uint32 NameAlt14;
    //uint32 NameAlt15;
    //uint32 NameFlags;
    //uint32 Description;
    //uint32 DescriptionAlt1;
    //uint32 DescriptionAlt2;
    //uint32 DescriptionAlt3;
    //uint32 DescriptionAlt4;
    //uint32 DescriptionAlt5;
    //uint32 DescriptionAlt6;
    //uint32 DescriptionAlt7;
    //uint32 DescriptionAlt8;
    //uint32 DescriptionAlt9;
    //uint32 DescriptionAlt10;
    //uint32 DescriptionAlt11;
    //uint32 DescriptionAlt12;
    //uint32 DescriptionAlt13;
    //uint32 DescriptionAlt14;
    //uint32 DescriptionAlt15;
    //uint32 DescriptionFlags;
    //uint32 unk2;
    //uint32 TypeText;
    //uint32 TypeTextAlt1;
    //uint32 TypeTextAlt2;
    //uint32 TypeTextAlt3;
    //uint32 TypeTextAlt4;
    //uint32 TypeTextAlt5;
    //uint32 TypeTextAlt6;
    //uint32 TypeTextAlt7;
    //uint32 TypeTextAlt8;
    //uint32 TypeTextAlt9;
    //uint32 TypeTextAlt10;
    //uint32 TypeTextAlt11;
    //uint32 TypeTextAlt12;
    //uint32 TypeTextAlt13;
    //uint32 TypeTextAlt14;
    //uint32 TypeTextAlt15;
    //uint32 TypeTextFlags;
	//uint32 unk3;
};

enum SPELL_EFFECT_OVERRIDE_RETURNS;
class Spell;
class Unit;
struct ProcHandlerContextShare;

enum SpellRequiredTargetTypes
{
	SPELL_TARGET_TYPE_REQUIRE_NO_CHECK			= 0,
	SPELL_TARGET_TYPE_REQUIRE_FACTION_CHECK		= 1,
	SPELL_TARGET_TYPE_REQUIRE_ENTRY_CHECK		= 2,
};

// Struct for the entry in Spell.dbc
struct SpellEntry
{
	uint32 Id;                              //1
	uint32 Category;                        //2
	uint32 DispelType;                      //3
	uint32 MechanicsType;                   //4
	uint32 Attributes;                      //5
	uint32 AttributesEx;                    //6
	uint32 AttributesExB;                   //7
	uint32 AttributesExC;                   //8 // Flags to
	uint32 AttributesExD;                   //9 // Flags....
	uint32 AttributesExE;                   //10 // Flags 2.0.1 unknown one
	uint32 AttributesExF;					//11
	uint32 RequiredShapeShift;              //12 // Flags BitMask for shapeshift spells
    uint32 unk320_1;
	uint32 ShapeshiftExclude;               //13-> this is wrong // Flags BitMask for which shapeshift forms this spell can NOT be used in.
    uint32 unk320_2;
 	uint32 Targets;                         //14 - N / M
    uint32 unk320_3;
	uint32 TargetCreatureType;              //16
	uint32 RequiresSpellFocus;              //17
	uint32 FacingCasterFlags;				//18
	uint32 CasterAuraState;                 //19
	uint32 TargetAuraState;                 //20
	uint32 CasterAuraStateNot;				//21 2.0.1 unknown two
	uint32 TargetAuraStateNot;				//22 2.0.1 unknown three
	uint32 casterAuraSpell;
	uint32 targetAuraSpell;
	uint32 casterAuraSpellNot;
	uint32 targetAuraSpellNot;
	uint32 CastingTimeIndex;                //23
	uint32 RecoveryTime;                    //24
	uint32 CategoryRecoveryTime;            //25 recoverytime
	uint32 InterruptFlags;                  //26
	uint32 AuraInterruptFlags;              //27
	uint32 ChannelInterruptFlags;           //28
	uint32 procFlags;                       //29
	uint32 procChance;                      //30
	int32 procCharges;                      //31
	uint32 maxLevel;                        //32
	uint32 baseLevel;                       //33
	uint32 spellLevel;                      //34
	uint32 DurationIndex;                   //35
	uint32 powerType;                       //36
	uint32 manaCost;                        //37
	uint32 manaCostPerlevel;                //38
	uint32 manaPerSecond;                   //39
	uint32 manaPerSecondPerLevel;           //40
	uint32 rangeIndex;                      //41
	float  speed;                           //42
	uint32 modalNextSpell;                  //43
	uint32 maxstack;                        //44
	uint32 Totem[2];                        //45 - 46
	uint32 Reagent[8];                      //47 - 54
	uint32 ReagentCount[8];                 //55 - 62
	int32 EquippedItemClass;                //63
	uint32 EquippedItemSubClass;            //64
	uint32 RequiredItemFlags;               //65
	uint32 Effect[3];                       //66 - 68
	uint32 EffectDieSides[3];               //69 - 71
//	uint32 EffectBaseDice[3];               //72 - 74
//	float  EffectDicePerLevel[3];           //75 - 77
	float  EffectRealPointsPerLevel[3];     //78 - 80
	int32  EffectBasePoints[3];             //81 - 83
	int32  EffectMechanic[3];               //84 - 86       Related to SpellMechanic.dbc
	uint32 EffectImplicitTargetA[3];        //87 - 89
	uint32 EffectImplicitTargetB[3];        //90 - 92
	uint32 EffectRadiusIndex[3];            //93 - 95
	uint32 EffectApplyAuraName[3];          //96 - 98
	uint32 EffectAmplitude[3];              //99 - 101
	float  EffectConversionCoef[3];         //102 - 104     This value is the $ value from description. Zack : like leech effect
	uint32 EffectChainTarget[3];            //105 - 107
	uint32 EffectItemType[3];			     //108 - 110	//wotlk dbc
	uint32 EffectMiscValue[3];              //111 - 113
	uint32 EffectMiscValueB[3];             //114 - 116  2.4.3
	uint32 EffectTriggerSpell[3];           //117 - 119
	float  EffectPointsPerComboPoint[3];    //120 - 122
	uint32 EffectSpellGroupRelation[3][3];			
	uint32 SpellVisual;                     //123
	uint32 field114;                        //124
	uint32 spellIconID;                     //125
	uint32 activeIconID;                    //126   activeIconID;
	uint32 spellPriority;                   //127
	char* Name;                             //128
	//uint32 NameAlt1;                        //129
	//uint32 NameAlt2;                        //130
	//uint32 NameAlt3;                        //131
	//uint32 NameAlt4;                        //132
	//uint32 NameAlt5;                        //133
	//uint32 NameAlt6;                        //134
	//uint32 NameAlt7;                        //135
	//uint32 NameAlt8;                        //136
	//uint32 NameAlt9;                        //137
	//uint32 NameAlt10;                       //138
	//uint32 NameAlt11;                       //139
	//uint32 NameAlt12;                       //140
	//uint32 NameAlt13;                       //141
	//uint32 NameAlt14;                       //142
	//uint32 NameAlt15;                       //143
	//uint32 NameFlags;                       //144
	char * Rank;                            //145
	//uint32 RankAlt1;                        //146
	//uint32 RankAlt2;                        //147
	//uint32 RankAlt3;                        //148
	//uint32 RankAlt4;                        //149
	//uint32 RankAlt5;                        //150
	//uint32 RankAlt6;                        //151
	//uint32 RankAlt7;                        //152
	//uint32 RankAlt8;                        //153
	//uint32 RankAlt9;                        //154
	//uint32 RankAlt10;                       //155
	//uint32 RankAlt11;                       //156
	//uint32 RankAlt12;                       //157
	//uint32 RankAlt13;                       //158
	//uint32 RankAlt14;                       //159
	//uint32 RankAlt15;                       //160
	//uint32 RankFlags;                       //161
	char * Description;                     //162
	//uint32 DescriptionAlt1;                 //163
	//uint32 DescriptionAlt2;                 //164
	//uint32 DescriptionAlt3;                 //165
	//uint32 DescriptionAlt4;                 //166
	//uint32 DescriptionAlt5;                 //167
	//uint32 DescriptionAlt6;                 //168
	//uint32 DescriptionAlt7;                 //169
	//uint32 DescriptionAlt8;                 //170
	//uint32 DescriptionAlt9;                 //171
	//uint32 DescriptionAlt10;                //172
	//uint32 DescriptionAlt11;                //173
	//uint32 DescriptionAlt12;                //174
	//uint32 DescriptionAlt13;                //175
	//uint32 DescriptionAlt14;                //176
	//uint32 DescriptionAlt15;                //177
	//uint32 DescriptionFlags;                //178
	char * BuffDescription;                 //179
	//uint32 BuffDescriptionAlt1;             //180
	//uint32 BuffDescriptionAlt2;             //181
	//uint32 BuffDescriptionAlt3;             //182
	//uint32 BuffDescriptionAlt4;             //183
	//uint32 BuffDescriptionAlt5;             //184
	//uint32 BuffDescriptionAlt6;             //185
	//uint32 BuffDescriptionAlt7;             //186
	//uint32 BuffDescriptionAlt8;             //187
	//uint32 BuffDescriptionAlt9;             //188
	//uint32 BuffDescriptionAlt10;            //189
	//uint32 BuffDescriptionAlt11;            //190
	//uint32 BuffDescriptionAlt12;            //191
	//uint32 BuffDescriptionAlt13;            //192
	//uint32 BuffDescriptionAlt14;            //193
	//uint32 BuffDescriptionAlt15;            //194
	//uint32 buffdescflags;                   //195
	uint32 ManaCostPercentage;              //196
	uint32 StartRecoveryTime;               //198
	uint32 StartRecoveryCategory;           //199
	uint32 MaxTargetLevel;                   //197 -are you sure ?
	uint32 SpellGroupName;                 //200
	uint32 SpellGroupType[3];				//201+202 //the group type of this spell
	uint32 MaxTargets;                      //203 
	uint32 Spell_Dmg_Type;                  //204   dmg_class Integer      0=None, 1=Magic, 2=Melee, 3=Ranged
	uint32 PreventionType;                  //205   0,1,2 related to Spell_Dmg_Type I think
	int32 StanceBarOrder;                   //206   related to paladin aura's 
	float dmg_multiplier[3];                //207 - 208   if the name is correct I dono
	uint32 MinFactionID;                    //209   only one spellid:6994 has this value = 369 UNUSED
	uint32 MinReputation;                   //210   only one spellid:6994 has this value = 4 UNUSED
	uint32 RequiredAuraVision;              //211  3 spells 1 or 2   
	uint32 TotemCategory[2];				//212-213
	int32  RequiresAreaId;					//214 
	uint32 School;							//215
	uint32 RuneCostID;						//216 from 3.0.1
	uint32 SpellMissileID;					//217 from 3.0.1
	uint32  PowerDisplayId;					//231 Related to PowerDisplay.dbc
    float unk320_4[3];
    uint32 unk320_7;
	uint32 unk330_1;

    /// CUSTOM: these fields are used for the modifications made in the world.cpp
    uint32 DiminishStatus;                  //
    uint32 proc_interval;                   //!!! CUSTOM, <Fill description for variable>
	uint32 procFlags2;						//since old flag list is too small
	uint32 procFlagsRemove;					//charge disipates if these proc flags are met. This is implemented wrongly. We should test the spell that will proc for flags. But we already register procs based on owner spell and not the proccing spell
	//Buff Groupin Rule -> caster can cast this spell only on 1 target. Value represents the group spell is part of. Can be part of only 1 group
	//caster can only cast on 1 target these spells
    uint32 BGR_one_buff_from_caster_on_1target;		//!!! CUSTOM, <Fill description for variable>
	//target can have only buff of this type on self. Value represents the group spell is part of. Can be part of only 1 group
    uint32	BGR_one_buff_on_target;					 //!!! CUSTOM, these are related to creating a item through a spell
	//all positive buffs should have this true and negative buffs as false
	bool	BGR_one_buff_on_target_skip_caster_check;	//addition for previous. 90% of the time check who casted this spell on target. Like blessings should stack
	//caster can have only 1 Aura per spell group, ex pal auras
    uint32 BGR_one_buff_from_caster_on_self;        //!!! CUSTOM, these are related to creating a item through a spell
//    uint32 buffIndexType;					//!!! CUSTOM, <Fill description for variable>
    uint32 c_is_flags;						//!!! CUSTOM, store spell checks in a static way : isdamageind,ishealing
    float DK_AP_spell_bonus[3];				//!!! CUSTOM, does this effect benefit from AP bonus ?
//    uint32 buffType;                        //!!! CUSTOM, these are related to creating a item through a spell
    uint32 RankNumber;                      //!!! CUSTOM, this protects players from having >1 rank of a spell
    uint32 NameHash;                        //!!! CUSTOM, related to custom spells, summon spell quest related spells
	//this is the group the spell will affect : each effect has it's own mask
//    uint32 EffectSpellGroupRelation[3][3];     //!!! this is not contained in client dbc but server must have it
	uint32 ThreatForSpell;					//some basic calculation for spell threath
	float ThreatForSpellCoef;				//theoretically setting this to 0 would make a spell not do threath
	uint32 ProcOnNameHash[3];
	uint32 spell_coef_flags;                                //!!! CUSTOM, store flags for spell coefficient calculations

	float base_range_or_radius_sqr;         //!!! CUSTOM, needed for aoe spells most of the time
	// love me or hate me, all "In a cone in front of the caster" spells don't necessarily mean "in front"
	float cone_width;
	//Spell Coefficient
	float fixed_dddhcoef;                                   //!!! CUSTOM, fixed DD-DH coefficient for some spells
	float fixed_hotdotcoef;                                 //!!! CUSTOM, fixed HOT-DOT coefficient for some spells
	bool Spell_value_is_scripted;							// for fixed spell value calculations this is required.
	int	ai_target_type;
	//!!!!!!!!!!! 1 spell may be present in multiple talent entries ! Ex : pet shared talents = cobra reflexes
#define SPELL_SKILL_LINK_LIMIT 20
	uint32	spell_skilline[SPELL_SKILL_LINK_LIMIT];			//skilline represents the icon in client spellbook
	uint32	spell_skilline_assoc_counter;					//spell may be present in multiple skillines
	TalentEntry *talent_entry[SPELL_SKILL_LINK_LIMIT];		//if this spell is obtained from a talent then we are able to look it up
	uint32	talent_entry_rank[SPELL_SKILL_LINK_LIMIT];		//if this spell is obtained from a talent then we are able to look it up
	uint32	talent_entry_assoc_counter;						//count this spell in how many talent trees is present
	uint32  talent_tree[SPELL_SKILL_LINK_LIMIT];			//multiple talents have multiple trees
	bool	spell_learn_is_linked_to_talent;				//when changing talent spec we need to know which spells to unlearn. If spell was learned by a talent then we need to remove it.
	uint32	spell_learn_next_level_spell;					//used for iterating through all levels of a spell : kinda like selecting spells with same namehash but this is based on SkillLineDBC
	skilllinespell	*spell_skill;							//in case there is one spell would be part of some skillspell
	uint32	spell_id_client;								//use this ID fro client isntead real ID
	uint32	quick_duration_min;
	uint32	quick_tickcount;
	uint32	quick_maxAmplitude;								//so that spells can tick last effect
	uint32	quick_ExtendDuration;
	SpellEntry	*chained_cast;								// cast this spell also when casting the original spell. Used for recently bandaged, forbearance and other spells that require more then 3 effects
	SpellEntry	*aura_remove_cast;							// if spell is dispelled, expires, canceled, this spell is casted by original caster on target(if possible). Used very rarely
	uint32	RequiredPlayerClass;							// this was added for aura 102 and 103 to not be exploitable by other classes

	bool self_cast_only;
	bool apply_on_shapeshift_change;
	bool is_melee_spell;					//!!! CUSTOM,
	bool is_ranged_spell;					//!!! CUSTOM,
	bool spell_can_crit;					//!!! CUSTOM,
	bool spell_DOT_can_crit;				//!!! CUSTOM,
	bool noproc;

	uint32 SchoolMask;						// Custom
	SPELL_EFFECT_OVERRIDE_RETURNS		(*EffectHandler)(Spell *sp,Unit *target, int32 &value, int32 i);	//handle special effect value calculations
	void								(*ProcHandler)(ProcHandlerContextShare *context);	//i hope 1 handler / spell is enough
	void								(*ChargeHandler)(ProcHandlerContextShare *context);	//i hope 1 handler / spell is enough
	uint32								(*CanCastHandler)(Spell *sp);	
	void								(*TargettingOverride[3])(Spell *sp,uint8 i);				//can script each effect how to gather their targettings
	int32					required_target_type;		//player - 1, mob = 2, ... !!! db has value -1 to be mangos compatible
	SimpleVect<uint32>		required_target_value;		//faction for 1 and entry for 2
/*
//3.0.1 client column namings
m_id
m_category
m_castUI
m_dispelType
m_mechanic
m_attributes
m_attributesEx
m_attributesExB
m_attributesExC
m_attributesExD
m_attributesExE
m_attributesExF
m_shapeshiftMask
m_shapeshiftExclude
m_targets
m_targetCreatureType
m_requiresSpellFocus
m_facingCasterFlags
m_casterAuraState
m_targetAuraState
m_excludeCasterAuraState
m_excludeTargetAuraState
m_castingTimeIndex
m_recoveryTime
m_categoryRecoveryTime
m_interruptFlags
m_auraInterruptFlags
m_channelInterruptFlags
m_procTypeMask
m_procChance
m_procCharges
m_maxLevel
m_baseLevel
m_spellLevel
m_durationIndex
m_powerType
m_manaCost
m_manaCostPerLevel
m_manaPerSecond
m_manaPerSecondPerLevel
m_rangeIndex
m_speed
m_modalNextSpell
m_cumulativeAura
m_totem
m_reagent
m_reagentCount
m_equippedItemClass
m_equippedItemSubclass
m_equippedItemInvTypes
m_effect
m_effectDieSides
m_effectBaseDice
m_effectDicePerLevel
m_effectRealPointsPerLevel
m_effectBasePoints
m_effectMechanic
m_implicitTargetA
m_implicitTargetB
m_effectRadiusIndex
m_effectAura
m_effectAuraPeriod
m_effectAmplitude
m_effectChainTargets
m_effectItemType
m_effectMiscValue
m_effectMiscValueB
m_effectTriggerSpell
m_effectPointsPerCombo
m_spellVisualID
m_spellIconID
m_activeIconID
m_spellPriority
m_name_lang
m_nameSubtext_lang
m_description_lang
m_auraDescription_lang
m_manaCostPct
m_startRecoveryCategory
m_startRecoveryTime
m_maxTargetLevel
m_spellClassSet
m_spellClassMask
m_maxTargets
m_defenseType
m_preventionType
m_stanceBarOrder
m_effectChainAmplitude
m_minFactionID
m_minReputation
m_requiredAuraVision
m_requiredTotemCategoryID
m_requiredAreaID
m_schoolMask
m_runeCostID
m_spellMissileID
*/
};

struct ItemExtendedCostEntry
{
    uint32 costid;
    uint32 honor;
    uint32 arena;
	uint32 new_320;
    uint32 item[5];
    uint32 count[5];
	uint32 personalrating;
	//uint32 sometextmaybe; //all pointed to null string
};

struct TalentTabEntry
{
    uint32	TalentTabID;
    //char*	Name;
	//unit32  unk3
	//unit32  unk4
	//unit32  unk5
	//unit32  unk6
	//unit32  unk7
	//unit32  unk8
	//unit32  unk9
	//unit32  unk10
	//unit32  unk11
	//unit32  unk12
	//unit32  unk13
	//unit32  unk14
	//unit32  unk15
	//unit32  unk16
	//unit32  unk17
	//unit32  unk18
	//unit32  unk19
	//unit32  unk20
    uint32	ClassMask;
//	uint32	unk21; //all values are 0
    uint32	TabPage;
    //char*	InternalName;
};

struct SpellCastTime
{
    uint32 ID;
    uint32 CastTime;
    //uint32 unk1;
    //uint32 unk2;
};

struct SpellRadius
{
    uint32 ID;
    float Radius;
    //float unk1;
    float Radius2;
};

struct SpellRange
{
    uint32 ID;
    float minRange;
    float minRangeFriendly;
    float maxRange;
    float maxRangeFriendly;
    //uint32 unks[35];
};

struct SpellDuration
{
    uint32 ID;
    uint32 Duration1;
    uint32 Duration2;
    uint32 Duration3;
};

struct RandomProps
{
    uint32 ID;
    //uint32 name1;
    uint32 spells[3];
    //uint32 unk1;
    //uint32 unk2;
    //uint32 name2;
    //uint32 RankAlt1;
    //uint32 RankAlt2;
    //uint32 RankAlt3;
    //uint32 RankAlt4;
    //uint32 RankAlt5;
    //uint32 RankAlt6;
    //uint32 RankAlt7;
    //uint32 RankAlt8;
    //uint32 RankAlt9;
    //uint32 RankAlt10;
    //uint32 RankAlt11;
    //uint32 RankAlt12;
    //uint32 RankAlt13;
    //uint32 RankAlt14;
    //uint32 RankAlt15;
    //uint32 RankFlags;

};

struct AreaTable
{
    uint32 AreaId;	//area is small. Areas with no zones are base zones actually
    uint32 mapId;	
    uint32 ZoneId;  //zone is very large
    uint32 explorationFlag;
    uint32 AreaFlags;
    //uint32 unk2;
    //uint32 unk3;
    //uint32 unk4;
    uint32 EXP;//not XP
    //uint32 unk5;
    uint32 level;
    char* name;
    //uint32 nameAlt1;
    //uint32 nameAlt2;
    //uint32 nameAlt3;
    //uint32 nameAlt4;
    //uint32 nameAlt5;
    //uint32 nameAlt6;
    //uint32 nameAlt7;
    //uint32 nameAlt8;
    //uint32 nameAlt9;
    //uint32 nameAlt10;
    //uint32 nameAlt11;
    //uint32 nameAlt12;
    //uint32 nameAlt13;
    //uint32 nameAlt14;
    //uint32 nameAlt15;
    //uint32 nameFlags;
    uint32 category;
    //uint32 unk7;
    //uint32 unk8;
    //uint32 unk9;
    //uint32 unk10;
    //uint32 unk11;
    //uint32 unk12;
	//uint32 unk13; //seems to be string
};

struct FactionTemplateDBC
{
    uint32 ID;
    uint32 Faction;
    uint32 FactionGroup;
    uint32 Mask;
    uint32 FriendlyMask;
    uint32 HostileMask;
    uint32 EnemyFactions[4];
    uint32 FriendlyFactions[4];
};

struct AuctionHouseDBC
{
    uint32 id;
    uint32 unk;
    uint32 fee;
    uint32 tax;
    //char* name;
    //char* nameAlt1;
    //char* nameAlt2;
    //char* nameAlt3;
    //char* nameAlt4;
    //char* nameAlt5;
    //char* nameAlt6;
    //char* nameAlt7;
    //char* nameAlt8;
    //char* nameAlt9;
    //char* nameAlt10;
    //char* nameAlt11;
    //char* nameAlt12;
    //char* nameAlt13;
    //char* nameAlt14;
    //char* nameAlt15;
    //char* nameFlags;
};

struct FactionDBC
{
    uint32 ID;
    int32 RepListId;
    uint32 RaceMask[4];
    uint32 ClassMask[4];
    int32 baseRepValue[4];
    uint32 repFlags[4];
    uint32 parentFaction;
    char* Name;
    //uint32 shit[16];
    //uint32 Description;
    //uint32 shit2[16];
};

struct DBCTaxiNode
{
    uint32 id;
    uint32 mapid;
    float x;
    float y;
    float z;
    //uint32 name;
    //uint32 namealt1;
    //uint32 namealt2;
    //uint32 namealt3;
    //uint32 namealt4;
    //uint32 namealt5;
    //uint32 namealt6;
    //uint32 namealt7;
    //uint32 namealt8;
    //uint32 namealt9;
    //uint32 namealt10;
    //uint32 namealt11;
    //uint32 namealt12;
    //uint32 namealt13;
    //uint32 namealt14;
    //uint32 namealt15;
    //uint32 nameflags;
    uint32 horde_mount;
    uint32 alliance_mount;
};

struct DBCTaxiPath
{
    uint32 id;
    uint32 from;
    uint32 to;
    uint32 price;
};

struct DBCTaxiPathNode
{
    uint32 id;
    uint32 path;
    uint32 seq;
    uint32 mapid;
    float x;
    float y;
    float z;
    uint32 unk1;
    uint32 waittime;
    //uint32 unk2;
    //uint32 unk3;
};

struct CreatureSpellDataEntry
{
    uint32 id;
    uint32 Spells[3];
    uint32 PHSpell;
    uint32 Cooldowns[3];
    uint32 PH;
};

struct CharRaceEntry
{
	uint32 race_id;
	//uint32
	//uint32
	//uint32      model_m;
	//uint32      model_f;
	//uint32
	//uint32
	uint32 team_id;
	//uint32
	//uint32
	//uint32
	//uint32
	uint32 cinematic_id;
	//uint32 - 3.3.2
	char* name1;
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
	//uint32
    //uint32      expansion;                                      // 68 (0 - original race, 1 - tbc addon, ...)
};

struct CharClassEntry
{
    uint32 class_id;
    //uint32 unk1;
    uint32 power_type;
    //uint32 unk2;
    char* name;
    //uint32 namealt1;
    //uint32 namealt2;
    //uint32 namealt3;
    //uint32 namealt4;
    //uint32 namealt5;
    //uint32 namealt6;
    //uint32 namealt7;
    //uint32 namealt8;
    //uint32 namealt9;
    //uint32 namealt10;
    //uint32 namealt11;
    //uint32 namealt12;
    //uint32 namealt13;
    //uint32 namealt14;
    //uint32 namealt15;
    //uint32 nameflags;
    //uint32 unk3;
    //uint32 unk4;
    //uint32 unk5;
	//uint32 expansion;
};

struct CreatureFamilyEntry
{
    uint32 ID;
    float minsize;
    uint32 minlevel;
    float maxsize;
    uint32 maxlevel;
    uint32 skilline;
    uint32 tameable;		//second skill line - 270 Generic
    uint32 petdietflags;
//	uint32 unk1; //maybe some flags
//	uint32 unk2; //maybe some flags
    char* name;
    //uint32 namealt1;
    //uint32 namealt2;
    //uint32 namealt3;
    //uint32 namealt4;
    //uint32 namealt5;
    //uint32 namealt6;
    //uint32 namealt7;
    //uint32 namealt8;
    //uint32 namealt9;
    //uint32 namealt10;
    //uint32 namealt11;
    //uint32 namealt12;
    //uint32 namealt13;
    //uint32 namealt14;
    //uint32 namealt15;
    //uint32 nameflags;
    //uint32 iconFile;
};

struct MapEntry
{
    uint32 id;
    char* name_internal;
    uint32 map_type;
	//uint32 unk_33_1;
    //uint32 unk;
    char* real_name;
    //uint32 unk_1;
    //uint32 unk1;
    //uint32 unk2;
    //uint32 unk3;
    //uint32 unk4;
    //uint32 unk5;
    //uint32 unk6;
    //uint32 unk7;
    //uint32 unk8;
    //uint32 unk9;
    //uint32 unk10;
    //uint32 unk11;
    //uint32 unk12;
    //uint32 unk13;
    //uint32 unk14;
    //uint32 unk15;
    //uint32 aunk1;
    //uint32 aunk2;
    //uint32 aunk3;
    //uint32 aunk4;
    //uint32 aunk5;
    //uint32 aunk6;
    //uint32 aunk7;
    //uint32 aunk8;
    //uint32 aunk9;
    //uint32 aunk10;
    //uint32 aunk11;
    //uint32 aunk12;
    //uint32 aunk13;
    //uint32 aunk14;
    //uint32 aunk15;
    //uint32 aunk16;
    //uint32 aunk17;
    //uint32 aunk18;
    //uint32 aunk19;
    //uint32 aunk20;
    //uint32 aunk21;
    //uint32 aunk22;
    //uint32 aunk23;
    //uint32 bunk1;
    //uint32 bunk2;
    //uint32 bunk3;
    //uint32 bunk4;
    //uint32 bunk5;
    //uint32 bunk6;
    //uint32 bunk7;
    //uint32 bunk8;
    //uint32 bunk9;
    //uint32 bunk10;
    //uint32 bunk11;
    //uint32 bunk12;
    //uint32 bunk13;
    //uint32 bunk14;
    //uint32 bunk15;
    //uint32 bunk16;
    //uint32 bunk17;
    //uint32 bunk18;
    //uint32 bunk19;
    //uint32 bunk20;
    //uint32 bunk21;
    //uint32 bunk22;
    //uint32 bunk23;
    //uint32 bunk24;
	//uint32 unk320;
};

struct ItemRandomSuffixEntry
{
	uint32 id;
//	uint32 name;
//	uint32 namealt1;
//	uint32 namealt2;
//	uint32 namealt3;
//	uint32 namealt4;
//	uint32 namealt5;
//	uint32 namealt6;
//	uint32 namealt7;
//	uint32 namealt8;
//	uint32 namealt9;
//	uint32 namealt10;
//	uint32 namealt11;
//	uint32 namealt12;
//	uint32 namealt13;
//	uint32 namealt14;
//	uint32 namealt15;
//	uint32 namealtflags;
//	uint32 desc;
	uint32 enchantments[5];
	uint32 prefixes[5];
};

struct gtFloat
{
	float val;
};

struct CombatRatingDBC
{
	float val;
};

struct ChatChannelDBC
{
	uint32 id;
	uint32 flags;
//	char * NULLString;
	char * name_pattern[16];
};

struct DurabilityQualityEntry
{
    uint32 id;
    float quality_modifier;
};

struct DurabilityCostsEntry
{
    uint32 itemlevel;
    uint32 modifier[29];
};

struct AreaTriggerEntry
{
    uint32    id;				// 0
    uint32    mapid;			// 1
    float     x;				// 2
    float     y;				// 3
    float     z;				// 4
    float     o;				// 5
    float     box_x;			// 6 extent x edge
    float     box_y;			// 7 extent y edge
    float     box_z;			// 8 extent z edge
    float     box_o;			// 9 extent rotation by about z axis
};

struct QuestXPEntry
{
    uint32    level;				// 0
    uint32    rewXP1;				// 2
	uint32    rewXP2;				// 3
	uint32    rewXP3;				// 4
	uint32    rewXP4;				// 5
	uint32    rewXP5;				// 6
	uint32    rewXP6;				// 7
	uint32    rewXP7;				// 8
	uint32    rewXP8;				// 9
};

struct QuestRewRepEntry
{
    uint32   entry;					// 0
    int32    rewRep1;				// 2
	int32    rewRep2;				// 3
	int32    rewRep3;				// 4
	int32    rewRep4;				// 5
	int32    rewRep5;				// 6
	int32    rewRep6;				// 7
	int32    rewRep7;				// 8
	int32    rewRep8;				// 9
	int32    rewRep9;				// 9
};

struct CharTitlesEntry
{
	uint32		ID;
	char*		name;										// Field [2], Name
	uint32		bit_index;									// Field [36], used in PLAYER_CHOSEN_TITLE and (uint32(1) << bit_index) in PLAYER_FIELD_KNOWN_TITLES and PLAYER_FIELD_KNOWN_TITLES_X
};

#define MAX_SSDE_COLUMN	10
struct ScalingStatDistributionEntry
{
	uint32 id;
	int32 stat[MAX_SSDE_COLUMN];				//these are item bonus types, ex : spell_power
	uint32 statmodifier[MAX_SSDE_COLUMN];	
	uint32 maxlevel;
};

struct ScalingStatValuesEntry
{
	uint32 id;
	uint32 level;
    uint32  ssdMultiplier[4];                               // 2-5 Multiplier for ScalingStatDistribution
    uint32  armorMod[4];                                    // 6-9 Armor for level
    uint32  dpsMod[6];                                      // 10-15 DPS mod for level
    uint32  spellBonus;                                     // 16 spell power for level
    uint32  ssdMultiplier2;                                 // 17 there's data from 3.1 dbc ssdMultiplier[3]
    uint32  ssdMultiplier3;                                 // 18 3.3
    uint32  unk2;                                           // 19 unk, probably also Armor for level (flag 0x80000?)
    uint32  armorMod2[4];                                   // 20-23 Armor for level

    uint32  getssdMultiplier(uint32 mask) const
    {
        if (mask & 0x4001F)
        {
            if(mask & 0x00000001) return ssdMultiplier[0];
            if(mask & 0x00000002) return ssdMultiplier[1];
            if(mask & 0x00000004) return ssdMultiplier[2];
            if(mask & 0x00000008) return ssdMultiplier2;
            if(mask & 0x00000010) return ssdMultiplier[3];
            if(mask & 0x00040000) return ssdMultiplier3;
        }
        return 0;
    }

    uint32  getArmorMod(uint32 mask) const
    {
        if (mask & 0x00F001E0)
        {
            if(mask & 0x00000020) return armorMod[0];
            if(mask & 0x00000040) return armorMod[1];
            if(mask & 0x00000080) return armorMod[2];
            if(mask & 0x00000100) return armorMod[3];

            if(mask & 0x00100000) return armorMod2[0];      // cloth
            if(mask & 0x00200000) return armorMod2[1];      // leather
            if(mask & 0x00400000) return armorMod2[2];      // mail
            if(mask & 0x00800000) return armorMod2[3];      // plate
        }
        return 0;
    }

    uint32 getDPSMod(uint32 mask) const
    {
        if (mask & 0x7E00)
        {
            if(mask & 0x00000200) return dpsMod[0];
            if(mask & 0x00000400) return dpsMod[1];
            if(mask & 0x00000800) return dpsMod[2];
            if(mask & 0x00001000) return dpsMod[3];
            if(mask & 0x00002000) return dpsMod[4];
            if(mask & 0x00004000) return dpsMod[5];         // not used?
        }
        return 0;
    }

    uint32 getSpellBonus(uint32 mask) const
    {
        if (mask & 0x00008000)
            return spellBonus;
        return 0;
    }

    uint32 getFeralBonus(uint32 mask) const                 // removed in 3.2.x?
    {
        if (mask & 0x00010000)                              // not used?
            return 0;
        return 0;
    }
};

#pragma pack(pop)

ARCEMU_INLINE float GetRadius(SpellRadius *radius)
{
    return radius->Radius;
}
ARCEMU_INLINE uint32 GetCastTime(SpellCastTime *time)
{
    return time->CastTime;
}
ARCEMU_INLINE float GetMaxRange(SpellRange *range)
{
    return range->maxRange;
}
ARCEMU_INLINE float GetMinRange(SpellRange *range)
{
    return range->minRange;
}
ARCEMU_INLINE uint32 GetDuration(SpellDuration *dur)
{
    return dur->Duration1;
}

//#define SAFE_DBC_CODE_RETURNS			/* undefine this to make out of range/nulls return null. */

template<class T>
class SERVER_DECL DBCStorage
{
	T * m_heapBlock;
	T * m_firstEntry;

	T ** m_entries;
	uint32 m_max;
	uint32 m_numrows;
	uint32 m_stringlength;
	char * m_stringData;

	uint32 rows;
	uint32 cols;
	uint32 useless_shit;
	uint32 header;
	bool	ContentIsEntryOrdered;	//row[0].entry<row[1].entry 

public:
	
	DBCStorage()
	{
		m_heapBlock = NULL;
		m_entries = NULL;
		m_firstEntry = NULL;
		m_max = 0;
		m_numrows = 0;
		m_stringlength=0;
		m_stringData = NULL;
		ContentIsEntryOrdered = true;
	}

	~DBCStorage()
	{
		if(m_heapBlock)
			free(m_heapBlock);
		if(m_entries)
			free(m_entries);
		if( m_stringData != NULL )
			free(m_stringData);
	}

	bool Load(const char * filename, const char * format, bool load_indexed, bool load_strings)
	{
		uint32 i;
		uint32 string_length;
		long pos;

		FILE * f = fopen(filename, "rb");
		if(f == NULL)
			return false;

		/* read the number of rows, and allocate our block on the heap */
		fread(&header,4,1,f);
		fread(&rows, 4, 1, f);
		fread(&cols, 4, 1, f);
		fread(&useless_shit, 4, 1, f);
		fread(&string_length, 4, 1, f);
		pos = ftell(f);

#ifdef USING_BIG_ENDIAN
		swap32(&rows); swap32(&cols); swap32(&useless_shit); swap32(&string_length);
#endif

		if( load_strings )
		{
			fseek( f, 20 + ( rows * cols * 4 ), SEEK_SET );
			m_stringData = (char*)malloc(string_length);
			m_stringlength = string_length;
			if (m_stringData)
				fread( m_stringData, string_length, 1, f );
		}

		fseek(f, pos, SEEK_SET);

		m_heapBlock = (T*)malloc(rows * sizeof(T));
		ASSERT(m_heapBlock);

		/* read the data for each row */
		uint32 prev_entry = 0;	
		for(i = 0; i < rows; ++i)
		{
			memset(&m_heapBlock[i], 0, sizeof(T));
			ReadEntry(f, &m_heapBlock[i], format, cols, filename);

			if(load_indexed)
			{
				/* all the time the first field in the dbc is our unique entry */
				if(*(uint32*)&m_heapBlock[i] > m_max)
					m_max = *(uint32*)&m_heapBlock[i];
			}
			else if( *(uint32*)&m_heapBlock[i] < prev_entry && ContentIsEntryOrdered == true )
			{
				ContentIsEntryOrdered = false;
			}
			//rule of the thumb, rows are ordered by entry in ascending order !Need this for binary search
			//!!!! this is presumed to be never ever be run :P. Blizz already orders entry in DBC
/*			else if( *(uint32*)&m_heapBlock[i] < prev_entry )
			{
				//omg we need to percolate this row to it's correct place
				uint32 should_be_at = 0;
				for( int32 j=i;j>=0;j--)
					if( *(uint32*)&m_heapBlock[j] <= *(uint32*)&m_heapBlock[i] )
					{
						should_be_at = j;
						break;
					}
				//store temp row
				T temp_row;
				memcpy( &temp_row, &m_heapBlock[i], sizeof(T));
				//need to slide all j->i rows by 1 to the end of the memblock
				memcpy( &m_heapBlock[should_be_at+1], &m_heapBlock[should_be_at], sizeof(T)*(i-should_be_at-1));
				//now insert row to it's place
				memcpy( &m_heapBlock[should_be_at], &temp_row, sizeof(T));
			}*/
			prev_entry = *(uint32*)&m_heapBlock[i];
		}

		if(load_indexed)
		{
			m_entries = (T**)malloc(sizeof(T*) * (m_max+1));
			ASSERT(m_entries);

			memset(m_entries, 0, (sizeof(T*) * (m_max+1)));
			for(i = 0; i < rows; ++i)
			{
				if(m_firstEntry == NULL)
					m_firstEntry = &m_heapBlock[i];

				m_entries[*(uint32*)&m_heapBlock[i]] = &m_heapBlock[i];
			}
		}

		m_numrows = rows;

		fclose(f);
		return true;
	}

	void ReadEntry(FILE * f, T * dest, const char * format, uint32 cols, const char * filename)
	{
		const char * t = format;
		uint32 * dest_ptr = (uint32*)dest;
		uint32 c = 0;
		uint32 val;
		size_t len = strlen(format);
		if(len!= cols)
			printf("!!! possible invalid format in file %s (us: %d, them: %u)\n", filename, len, cols);

		while(*t != 0)
		{
			if((++c) > cols)
			{
				++t;
				printf("!!! Read buffer overflow in DBC reading of file %s\n", filename);
				continue;
			}

			fread(&val, 4, 1, f);
			if(*t == 'x')
			{
				++t;
				continue;		// skip!
			}
#ifdef USING_BIG_ENDIAN
			swap32(&val);
#endif
			if(*t == 's')
			{
				char ** new_ptr = (char**)dest_ptr;
				static const char * null_str = "";
				char * ptr;
				if( val < m_stringlength )
					ptr = m_stringData + val;
				else
					ptr = (char*)null_str;

				*new_ptr = ptr;
				new_ptr++;
				dest_ptr = (uint32*)new_ptr;
			}
			else
			{
				*dest_ptr = val;
				dest_ptr++;
			}

			++t;
		}
	}

	ARCEMU_INLINE uint32 GetNumRows()
	{
		return m_numrows;
	}

	T * LookupEntryForced(uint32 i)
	{
		if(m_entries)
		{
			if(i > m_max || m_entries[i] == NULL)
			{
#if 0
				printf("LookupEntryForced failed for entry %u\n", i);
#endif
				return NULL;
			}
			else
				return m_entries[i];
		}
		else
		{
			T *temp = LookupEntry( i );
			if( temp && *(uint32*)temp != i )
				return NULL;
			return temp;
		}
	}

	T * CreateCopy(T * obj)
	{
		T * oCopy = (T*)malloc(sizeof(T));
		ASSERT(oCopy);
		memcpy(oCopy,obj,sizeof(T));
		return oCopy;
	}
	void SetRow(uint32 i, T * t)
	{
		if(i < m_max && m_entries)
			m_entries[i] = t;
	}

	T * LookupEntry(uint32 entry)
	{
		if(m_entries)
		{
			if(entry > m_max || m_entries[entry] == NULL)
				return m_firstEntry;
			else
				return m_entries[entry];
		}
		else
		{
			// removed. Old and absolutly bad. This is not entry but row lookup
			/*{
				if(i >= m_numrows)
					return NULL;
				else
					return &m_heapBlock[i];
			}*/
			//if DBC was entry based oredered : row[0].entry<row[1].entry
			if( ContentIsEntryOrdered )
			{
				//we can use logarithmic search. That is good
				uint32 start = 0;
				uint32 end = m_numrows;
				uint32 length;
				uint32 middle_index;
				do
				{
					length = end - start;
					length = length >> 1;
					middle_index = start + length;
					if( *(uint32*)&m_heapBlock[middle_index] < entry )
						start += length;
					else if( *(uint32*)&m_heapBlock[middle_index] > entry )
						end -= length;
					else 
						return &m_heapBlock[middle_index];
				}while( length != 0 );
				if( *(uint32*)&m_heapBlock[ middle_index ] == entry )
					return &m_heapBlock[middle_index];
				//return NULL;
				return m_firstEntry;	//plain wrong and insane !
			}
			else
			{
				//flat search :(
				for(uint32 i=0;i<m_numrows;i++)
					if( *(uint32*)&m_heapBlock[ i ] == entry )
						return &m_heapBlock[ i ];	
//				return NULL;
				return m_firstEntry;	//plain wrong and insane !
			}
		}
	}

	T * LookupRow(uint32 i)
	{
		if(i >= m_numrows)
			return NULL;
		else
			return &m_heapBlock[i];
	}
};

extern SERVER_DECL DBCStorage <LFGDungeonEntry>				dbcLFGDungeonStore;
extern SERVER_DECL DBCStorage <WorldMapAreaEntry>			dbcWorldMapZoneStore;
extern SERVER_DECL DBCStorage <VehicleSeatEntry>			dbcVehicleSeatEntry;
extern SERVER_DECL DBCStorage <VehicleEntry>				dbcVehicleEntry;
//extern SERVER_DECL DBCStorage <CurrencyTypesEntry>		dbcCurrencyTypesStore;
extern SERVER_DECL DBCStorage <ScalingStatDistributionEntry> dbcScalingStatDistribution;
extern SERVER_DECL DBCStorage <ScalingStatValuesEntry>		dbcScalingStatValues;
extern SERVER_DECL DBCStorage <WorldMapOverlay>				dbcWorldMapOverlayStore;
extern SERVER_DECL DBCStorage <BattlemasterListEntry>		dbcBattlemasterListStore;
extern SERVER_DECL DBCStorage <ItemLimitCategory>			dbcItemLimitCategory; //used for prismatic gems
extern SERVER_DECL DBCStorage <AreaGroup>					dbcAreaGroup;
extern SERVER_DECL DBCStorage <SpellRuneCostEntry>			dbcSpellRuneCostEntry;
extern SERVER_DECL DBCStorage <GlyphPropertiesEntry>        dbcGlyphPropertiesStore;
extern SERVER_DECL DBCStorage <GlyphSlotEntry>              dbcGlyphSlotStore;
extern SERVER_DECL std::list<AchievementCriteriaEntry*>		dbcBoostedAchievementLookup[ACHIEVEMENT_CRITERIA_TYPE_TOTAL];
extern SERVER_DECL DBCStorage<AchievementEntry>				dbcAchievementStore;
extern SERVER_DECL DBCStorage<AchievementCriteriaEntry>		dbcAchievementCriteriaStore;
extern SERVER_DECL DBCStorage<BarberShopStyleEntry>			dbcBarberShopStyleStore;
extern SERVER_DECL DBCStorage<GtBarberShopCostBaseEntry>	dbcBarberShopCostStore;
extern SERVER_DECL DBCStorage<GemPropertyEntry> dbcGemProperty;
extern SERVER_DECL DBCStorage<ItemSetEntry> dbcItemSet;
extern SERVER_DECL DBCStorage<Lock> dbcLock;
extern SERVER_DECL DBCStorage<SpellEntry> dbcSpell;
extern SERVER_DECL DBCStorage<SpellDuration> dbcSpellDuration;
extern SERVER_DECL DBCStorage<SpellRange> dbcSpellRange;
extern SERVER_DECL DBCStorage<emoteentry> dbcEmoteEntry;
extern SERVER_DECL DBCStorage<SpellRadius> dbcSpellRadius;
extern SERVER_DECL DBCStorage<SpellCastTime> dbcSpellCastTime;
extern SERVER_DECL DBCStorage<AreaTable> dbcArea;
extern SERVER_DECL DBCStorage<FactionTemplateDBC> dbcFactionTemplate;
extern SERVER_DECL DBCStorage<FactionDBC> dbcFaction;
extern SERVER_DECL DBCStorage<EnchantEntry> dbcEnchant;
extern SERVER_DECL DBCStorage<RandomProps> dbcRandomProps;
extern SERVER_DECL DBCStorage<skilllinespell> dbcSkillLineSpell;
extern SERVER_DECL DBCStorage<skilllineentry> dbcSkillLine;
extern SERVER_DECL DBCStorage<DBCTaxiNode> dbcTaxiNode;
extern SERVER_DECL DBCStorage<DBCTaxiPath> dbcTaxiPath;
extern SERVER_DECL DBCStorage<DBCTaxiPathNode> dbcTaxiPathNode;
extern SERVER_DECL DBCStorage<AuctionHouseDBC> dbcAuctionHouse;
extern SERVER_DECL DBCStorage<TalentEntry> dbcTalent;
extern SERVER_DECL DBCStorage<TalentTabEntry> dbcTalentTab;
extern SERVER_DECL DBCStorage<CreatureSpellDataEntry> dbcCreatureSpellData;
extern SERVER_DECL DBCStorage<CreatureFamilyEntry> dbcCreatureFamily;
extern SERVER_DECL DBCStorage<CharClassEntry> dbcCharClass;
extern SERVER_DECL DBCStorage<CharRaceEntry> dbcCharRace;
extern SERVER_DECL DBCStorage<MapEntry> dbcMap;
extern SERVER_DECL DBCStorage<ItemExtendedCostEntry> dbcItemExtendedCost;
extern SERVER_DECL DBCStorage<ItemRandomSuffixEntry> dbcItemRandomSuffix;
extern SERVER_DECL DBCStorage<CombatRatingDBC> dbcCombatRating;
extern SERVER_DECL DBCStorage<ChatChannelDBC> dbcChatChannels;
extern SERVER_DECL DBCStorage<DurabilityCostsEntry> dbcDurabilityCosts;
extern SERVER_DECL DBCStorage<DurabilityQualityEntry> dbcDurabilityQuality;
extern SERVER_DECL DBCStorage<BankSlotPrice> dbcBankSlotPrices;
extern SERVER_DECL DBCStorage<BankSlotPrice> dbcStableSlotPrices; //uses same structure as Bank
extern SERVER_DECL DBCStorage<gtFloat> dbcMeleeCrit;
extern SERVER_DECL DBCStorage<gtFloat> dbcMeleeCritBase;
extern SERVER_DECL DBCStorage<gtFloat> dbcSpellCrit;
extern SERVER_DECL DBCStorage<gtFloat> dbcSpellCritBase;
extern SERVER_DECL DBCStorage<gtFloat> dbcMPRegen;
extern SERVER_DECL DBCStorage<gtFloat> dbcMPRegenBase;
extern SERVER_DECL DBCStorage<gtFloat> dbcHPRegen;
extern SERVER_DECL DBCStorage<gtFloat> dbcHPRegenBase;
extern SERVER_DECL DBCStorage<AreaTriggerEntry> dbcAreaTrigger;
extern SERVER_DECL DBCStorage<QuestXPEntry> dbcQuestXP;
extern SERVER_DECL DBCStorage<QuestRewRepEntry> dbcQuestRewRep;
extern SERVER_DECL DBCStorage<CharTitlesEntry> dbcCharTitle; // not used yet

bool LoadDBCs();

#endif
