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

#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
#define STAT_SYS
#define GLOBAL_MAX_GUID 0xFFFFFFFF

#define IS_INSTANCE(a) (((a)>1)&&((a)!=530)&&((a)!=571)&&((a)!=449)&&((a)!=450))
#define IS_MAIN_MAP(a) (((a)<2)||((a)==530)||((a)==571)||((a)==449)||((a)==450))
#define MAPID_LIST_MAIN_MAP "0, 1, 530, 571, 449, 450"
#define IS_BG_MAP(a) (((a)==449)||((a)==450)||((a)==489)||((a)==529)||((a)==30)||((a)==566)||((a)==559)||((a)==562)||((a)==607)||((a)==617)||((a)==572))
//megai2: нужно нет? 618

#ifndef _GAME

enum INSTANCE_TYPE
{
	INSTANCE_NULL,
	INSTANCE_RAID,
	INSTANCE_NONRAID,
	INSTANCE_PVP,
	INSTANCE_MULTIMODE,
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
	RACE_BLOODELF = 10,
	RACE_DRAENEI = 11,
};

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
};

struct ServerConf
{
	bool interfaction_chat;	
	bool interfaction_group;
};

#define MAX_ACTIVE_WS 6

struct GuidInfo
{
    union
    {
	    uint32 m_hiItemGuid[MAX_ACTIVE_WS];
	    uint32 m_hiContainerGuid[MAX_ACTIVE_WS];
    };
	uint32 m_hiPlayerGuid[MAX_ACTIVE_WS];
	uint32 m_hiGroupGuid;
	uint32 m_hiGuildGuid[MAX_ACTIVE_WS];
	uint32 m_mailGuid[MAX_ACTIVE_WS];
	uint32 m_auctionGuid[MAX_ACTIVE_WS];

	uint8 globalOffset;
	uint8 realmsCnt;
};

enum ChatMsg
{
	CHAT_MSG_ADDON									= -1,
	CHAT_MSG_SYSTEM                                 = 0,    //28,   CHAT_MSG_SYSTEM                 = 0x00,         0
	CHAT_MSG_SAY									= 1,
	CHAT_MSG_PARTY									= 2,
	CHAT_MSG_RAID									= 3,
	CHAT_MSG_GUILD									= 4,
	CHAT_MSG_OFFICER								= 5,
	CHAT_MSG_YELL									= 6,
	CHAT_MSG_WHISPER								= 7,
	CHAT_MSG_WHISPER_MOB							= 8,//CHAT_MSG_WHISPER_INFORM
	CHAT_MSG_WHISPER_INFORM							= 9,//CHAT_MSG_REPLY
	CHAT_MSG_EMOTE									= 10,
	CHAT_MSG_TEXT_EMOTE								= 11,
	CHAT_MSG_MONSTER_SAY							= 12,
	CHAT_MSG_MONSTER_PARTY							= 13,
	CHAT_MSG_MONSTER_YELL							= 14,
	CHAT_MSG_MONSTER_WHISPER						= 15,
	CHAT_MSG_MONSTER_EMOTE							= 16,
	CHAT_MSG_CHANNEL								= 17,
	CHAT_MSG_CHANNEL_JOIN							= 18,
	CHAT_MSG_CHANNEL_LEAVE							= 19,
	CHAT_MSG_CHANNEL_LIST							= 20,
	CHAT_MSG_CHANNEL_NOTICE							= 21,
	CHAT_MSG_CHANNEL_NOTICE_USER					= 22,
	CHAT_MSG_AFK									= 23,
	CHAT_MSG_DND									= 24,
	CHAT_MSG_IGNORED								= 25,
	CHAT_MSG_SKILL									= 26,
	CHAT_MSG_LOOT									= 27,
    CHAT_MSG_MONEY                                  = 28,
    CHAT_MSG_OPENING                                = 29,
    CHAT_MSG_TRADESKILLS                            = 30,
    CHAT_MSG_PET_INFO                               = 31,
    CHAT_MSG_COMBAT_MISC_INFO                       = 32,
    CHAT_MSG_COMBAT_XP_GAIN                         = 33,
    CHAT_MSG_COMBAT_HONOR_GAIN                      = 34,
    CHAT_MSG_COMBAT_FACTION_CHANGE                  = 35,
	CHAT_MSG_BG_EVENT_NEUTRAL						= 36,
	CHAT_MSG_BG_EVENT_ALLIANCE						= 37,
	CHAT_MSG_BG_EVENT_HORDE							= 38,
	CHAT_MSG_RAID_LEADER							= 39,
	CHAT_MSG_RAID_WARNING							= 40,
	CHAT_MSG_RAID_WARNING_WIDESCREEN				= 41,
    CHAT_MSG_RAID_BOSS_EMOTE                        = 42,
	CHAT_MSG_FILTERED								= 43,
	CHAT_MSG_BATTLEGROUND							= 44,
	CHAT_MSG_BATTLEGROUND_LEADER					= 45,
	CHAT_MSG_RESTRICTED								= 46,
	CHAT_MSG_ACHIEVEMENT							= 47,
    CHAT_MSG_GUILD_ACHIEVEMENT						= 48,
};

enum Languages
{
    LANG_UNIVERSAL                              = 0x00,
    LANG_ORCISH                                 = 0x01,
    LANG_DARNASSIAN                             = 0x02,
    LANG_TAURAHE                                = 0x03,
    LANG_DWARVISH                               = 0x06,
    LANG_COMMON                                 = 0x07,
    LANG_DEMONIC                                = 0x08,
    LANG_TITAN                                  = 0x09,
    LANG_THELASSIAN                             = 0x0A,
    LANG_DRACONIC                               = 0x0B,
    LANG_KALIMAG                                = 0x0C,
    LANG_GNOMISH                                = 0x0D,
    LANG_TROLL                                  = 0x0E,
    LANG_GUTTERSPEAK                            = 0x21,
    LANG_DRAENEI                                = 0x23,
    NUM_LANGUAGES                               = 0x24
};

enum PartyErrors
{
	ERR_PARTY_NO_ERROR					= 0,
	ERR_PARTY_CANNOT_FIND				= 1,
	ERR_PARTY_IS_NOT_IN_YOUR_PARTY		= 2,
	ERR_PARTY_UNK						= 3,
	ERR_PARTY_IS_FULL					= 4,
	ERR_PARTY_ALREADY_IN_GROUP			= 5,
	ERR_PARTY_YOU_ARENT_IN_A_PARTY		= 6,
	ERR_PARTY_YOU_ARE_NOT_LEADER		= 7,
	ERR_PARTY_WRONG_FACTION				= 8,
	ERR_PARTY_IS_IGNORING_YOU			= 9,
};

enum GroupTypes
{
	GROUP_TYPE_PARTY					= 0,
	GROUP_TYPE_BG						= 1,
	GROUP_TYPE_RAID						= 2,
	GROUP_TYPE_BGRAID					= GROUP_TYPE_BG | GROUP_TYPE_RAID,
	GROUP_TYPE_LFD						= 0x08,
};

#define PARTY_LOOT_FFA	  0
#define PARTY_LOOT_MASTER   2
#define PARTY_LOOT_RR	   1
#define PARTY_LOOT_NBG	  4
#define PARTY_LOOT_GROUP	3

enum PartyUpdateFlags
{
	GROUP_UPDATE_FLAG_NONE						= 0,		// 0x00000000
	GROUP_UPDATE_FLAG_ONLINE					= 1,		// 0x00000001  uint8
	GROUP_UPDATE_FLAG_HEALTH					= 2,		// 0x00000002  uint16
	GROUP_UPDATE_FLAG_MAXHEALTH					= 4,		// 0x00000004  uint16
	GROUP_UPDATE_FLAG_POWER_TYPE				= 8,		// 0x00000008  uint16
	GROUP_UPDATE_FLAG_POWER						= 16,		// 0x00000010  uint16
	GROUP_UPDATE_FLAG_MAXPOWER					= 32,		// 0x00000020  uint16
	GROUP_UPDATE_FLAG_LEVEL						= 64,		// 0x00000040  uint16
	GROUP_UPDATE_FLAG_ZONEID					= 128,		// 0x00000080  uint16
	GROUP_UPDATE_FLAG_POSITION					= 256,		// 0x00000100  uint16, uint16
	GROUP_UPDATE_FLAG_PLAYER_AURAS				= 512,		// 0x00000200  uint64, uint16 for each uint64
	GROUP_UPDATE_FLAG_PET_GUID					= 1024,		// 0x00000400  uint64
	GROUP_UPDATE_FLAG_PET_NAME					= 2048,		// 0x00000800  string
	GROUP_UPDATE_FLAG_PET_DISPLAYID				= 4096,		// 0x00001000  uint16
	GROUP_UPDATE_FLAG_PET_HEALTH				= 8192,		// 0x00002000  uint16
	GROUP_UPDATE_FLAG_PET_MAXHEALTH				= 16384,	// 0x00004000  uint16
	GROUP_UPDATE_FLAG_PET_POWER_TYPE			= 32768,	// 0x00008000  uint8
	GROUP_UPDATE_FLAG_PET_POWER					= 65535,	// 0x00010000  uint16
	GROUP_UPDATE_FLAG_PET_MAXPOWER				= 131070,	// 0x00020000  uint16
	GROUP_UPDATE_FLAG_PET_AURAS					= 262144,	// 0x00040000  uint64, uint16 for each uint64
};

enum PartyUpdateFlagGroups
{
	GROUP_UPDATE_TYPE_FULL_CREATE				=	GROUP_UPDATE_FLAG_ONLINE | GROUP_UPDATE_FLAG_HEALTH | GROUP_UPDATE_FLAG_MAXHEALTH |
													GROUP_UPDATE_FLAG_POWER | GROUP_UPDATE_FLAG_LEVEL |
													GROUP_UPDATE_FLAG_ZONEID | GROUP_UPDATE_FLAG_MAXPOWER | GROUP_UPDATE_FLAG_POSITION,
	GROUP_UPDATE_TYPE_FULL_REQUEST_REPLY		=   0x7FFC0BFF,
};

struct Group {	
	uint32 groupId;
	uint8 groupType;
	uint8 subCnt;
	uint8 lootMeth;
	uint8 lootThres;
	uint32 difficulty;
	uint32 leader;
	uint32 mTank;
	uint32 mAssist;
	uint32 members[8][5];
	uint32 timestamp;
	uint32 instanceIds[NUM_MAPS][NUM_INSTANCE_MODES];
	uint32 looter;
	uint32 targetIcons[8];

	bool IsFull() {
		for(int32 i = 0; i < 1 + 7 * groupType; ++i)
			for(uint32 j = 0; j < 5; ++j)
			{
				if (members[i][j] == 0)
					return false;
			}		
		return true;
	}

	bool AddMember(uint32 guid) {
		if (IsFull())
			return false;

		for(int32 i = 0; i < 1 + 7 * groupType; ++i)
			for(uint32 j = 0; j < 5; ++j)
			{
				if (members[i][j] == 0)
				{
					if (i > subCnt)
						subCnt = i;
					members[i][j] = guid;
					return true; 
				}
			}		
		return false;
	}
	bool RemoveMember(uint32 guid) {
		for(int32 i = 0; i < 1 + 7 * groupType; ++i)
			for(uint32 j = 0; j < 5; ++j)
			{
				if (members[i][j] == guid)
				{
					members[i][j] = 0;
					if (guid = leader)
						for(int32 k = 0; k < 1 + 7 * groupType; ++k)
							for(uint32 l = 0; l < 5; ++l)						
								if (members[k][l])
								{
									leader = members[k][l]; 
									return true;
								}
					return true; 
				}
			}		
		return false;
	}
};

#endif

#define PUT_SELF_TO_OTHER 0
#define PUT_OTHER_TO_SELF 1

struct RPlayerInfo
{
	uint32 Guid;
	uint32 AccountId;
	string Name;
	uint32 Level;
	uint32 GuildId;
	float PositionX;
	float PositionY;
	float PositionZ;
	uint32 ZoneId;
	uint8 Race;
	uint8 Team;
	uint8 Class;
	CharClassEntry * DBCClass;
	uint8 Gender;
	uint32 Latency;
	string GMPermissions;
	uint32 Account_Flags;
	uint32 InstanceId;
	uint32 MapId;
	uint32 Sessid;
	bool bGMTag;
	uint32 LootInfo;
	uint32 GuildPrem;
	uint32 GroupID;

	uint32 inviter;
	uint32 guildinviter;

#ifndef _GAME
	/* This stuff is used only by the realm server */
	Group * m_Group;
	uint32 RecoveryMapId;
	LocationVector RecoveryPosition;
	bool onBg;
#else
	uint8 loot_thres;
	uint8 loot_method;
	bool bGroup;
#endif

	void Pack(ByteBuffer& buf)
	{
		buf << Guid << AccountId << Name << PositionX << PositionY << PositionZ << ZoneId << Race << Team << Class << Gender << Latency << GMPermissions
			<< Account_Flags << InstanceId << Level << GuildId << MapId << Sessid << bGMTag << guildinviter << GuildPrem << LootInfo;
#ifndef _GAME
		if (m_Group)
			buf << m_Group->groupId;
		else
			buf << uint32(0);
#else
		buf << GroupID;
#endif
	}

	void Unpack(ByteBuffer & buf)
	{
		buf >> Guid >> AccountId >> Name >> PositionX >> PositionY >> PositionZ >> ZoneId >> Race >> Team >> Class >> Gender >> Latency >> GMPermissions
			>> Account_Flags >> InstanceId >> Level >> GuildId >> MapId >> Sessid >> bGMTag >> guildinviter >> GuildPrem >> LootInfo >> GroupID;
	}

	bool hasGMCommand(char comm)
	{
		// checking properties
		if(GMPermissions == "")
			return false;
		if(comm == 0)
			return false;
		
		// getting commandlist
		for(uint32 i = 0; i < GMPermissions.length(); ++i)
		{
			char c = GMPermissions.at(i);
			c = tolower(c);
			//sLog.outDebug("c=%c %i, comm=%c %i", c, c, comm, comm);

			if(c == 'a')
				return true;
			else 
				if(c == comm)
					return true;
		}
		return false;
	}
	
	uint32 GetTeam(){ return Team; };
};

enum WorkerTypes 
{
	WS_WORLD = 0
};

struct authReply
{
	WorkerTypes WorkerType;
};

struct WorldInstanceInfo
{
	uint32 MapId;
	uint32 InstanceId;
};

#define	UI_LEVEL		1
#define	UI_GUILD		2
#define	UI_ZONE			3
#define	UI_GMTAG		4
#define	UI_GUILDR		5
#define UI_GINVITER		6

#define GT_ITEM			1
#define GT_PLAYER		2
#define GT_CONTAINER	3
#define GT_GUILD		4
#define GT_MAIL			5
#define GT_AUCTION      6

#ifndef _GAME
/* Copied structures from game */
struct SocketInfo {
	uint32 SocketColor;
	uint32 Unk;
};

struct ItemSpell
{
	uint32 Id;
	uint32 Trigger;
	int32 Charges;
	int32 Cooldown;
	uint32 Category;
	int32 CategoryCooldown;
};

struct ItemDamage
{
	float Min;
	float Max;
	uint32 Type;
};

struct ItemStat
{
	uint32 Type;
	int32 Value;
};

struct ItemPrototype
{
	uint32 ItemId;
	uint32 Class;
	uint32 SubClass;
	uint32 unknown_bc;
	char * Name1;
	char * Name2;
	char * Name3;
	char * Name4;
	uint32 DisplayInfoID;
	uint32 Quality;
	uint32 Flags;
	uint32 BuyPrice;
	uint32 SellPrice;
	uint32 InventoryType;
	uint32 AllowableClass;
	uint32 AllowableRace;
	uint32 ItemLevel;
	uint32 RequiredLevel;
	uint32 RequiredSkill;
	uint32 RequiredSkillRank;
	uint32 RequiredSkillSubRank;
	uint32 RequiredPlayerRank1;
	uint32 RequiredPlayerRank2;
	uint32 RequiredFaction;
	uint32 RequiredFactionStanding;
	uint32 Unique;
	uint32 MaxCount;
	uint32 ContainerSlots;
	ItemStat Stats[10];
	ItemDamage Damage[5];
	uint32 Armor;
	uint32 HolyRes;
	uint32 FireRes;
	uint32 NatureRes;
	uint32 FrostRes;
	uint32 ShadowRes;
	uint32 ArcaneRes;
	uint32 Delay;
	uint32 AmmoType;
	float  Range;
	ItemSpell Spells[5];
	uint32 Bonding;
	char * Description;
	uint32 PageId;
	uint32 PageLanguage;
	uint32 PageMaterial;
	uint32 QuestId;
	uint32 LockId;
	uint32 LockMaterial;
	uint32 Field108;
	uint32 RandomPropId;
	uint32 RandomSuffixId;
	uint32 Block;
	uint32 ItemSet;
	uint32 MaxDurability;
	uint32 ZoneNameID;
	uint32 MapID;
	uint32 BagFamily;
	uint32 ToolCategory;
	SocketInfo Sockets[3];
	uint32 SocketBonus;
	uint32 GemProperties;
	uint32 ItemExtendedCost;
	uint32 DisenchantReqSkill;
	uint32 ArmorDamageModifier;
};

struct CreatureInfo
{
	uint32 Id;
	char * Name;
	char * SubName;
	uint32 Flags1;
	uint32 Type;
	uint32 Family;
	uint32 Rank;
	uint32 Unknown1;
	uint32 SpellDataID;
	uint32 DisplayID;
	float unk2;
	float unk3;
	uint8  Civilian;
	uint8  Leader;
};


struct GameObjectInfo
{
	uint32 ID;
	uint32 Type;
	uint32 DisplayID;
	char * Name;
	uint32 SpellFocus;
	uint32 sound1;
	uint32 sound2;
	uint32 sound3;
	uint32 sound4;
	uint32 sound5;
	uint32 sound6;
	uint32 sound7;
	uint32 sound8;
	uint32 sound9;
	uint32 Unknown1;
	uint32 Unknown2;
	uint32 Unknown3;
	uint32 Unknown4;
	uint32 Unknown5;
	uint32 Unknown6;
	uint32 Unknown7;
	uint32 Unknown8;
	uint32 Unknown9;
	uint32 Unknown10;
	uint32 Unknown11;
	uint32 Unknown12;
	uint32 Unknown13;
	uint32 Unknown14;
};

struct ItemPage
{
	uint32 id;
	char * text;
	uint32 next_page;
};


struct Quest
{
	int32 id;
	int32 IsActiveFlags;
	int32 max_level;
	int32 min_level;
	int32 zone_id;
	int32 type;
	int32 suggestedplayers;
	int32 objective_rep_faction;
	int32 objective_rep_value;
	int32 objective_rep_faction2;
	int32 objective_rep_value2;
	int32 next_quest_id;
	int32 rew_xp_rank; // XP Reward level
	int32 reward_money;
	int32 rew_money_at_max_level;
	int32 reward_spell;
	int32 effect_on_player;
	int32 bonushonor;
	float unk_33_2;
	int32 srcitem;
	int32 quest_flags;
	int32 rewardtitleid;
	int32 req_playerkillcount;
	int32 rewardtalents;
	int32 unk_33_3;
	int32 unk_33_4;
	int32 reward_item[4];
	int32 reward_itemcount[4];
	int32 reward_choiceitem[6];
	int32 reward_choiceitemcount[6];
	int32 rew_faction[5];			
	int32 rew_faction_repA[5];	
	int32 rew_faction_repB[5];
	int32 point_mapid;
	float point_x;
	float point_y;
	int32 point_opt;
	char * title;
	char * details;
	char * objectives;
	char * endtext;
	char * unk_33_6;
	int32 required_mob[4];
	int32 required_mobcount[4];
	int32 linkItemId[4];
	int32 linkItemIdCount[4];
	int32 required_item[6];
	int32 required_itemcount[6];
	char * objectivetexts[4];

	// Custom fields start here
	uint32 previous_quest_id;
	uint32 required_races;
	uint32 required_class;
	uint32 required_tradeskill;
	uint32 required_tradeskill_value;
	uint32 required_min_rep_faction;
	uint32 required_min_rep_value;
	uint32 required_max_rep_faction;
	uint32 required_max_rep_value;
	uint32 required_quests[4];
	uint32 receive_items[4];
	uint32 receive_itemcount[4];
	uint32 time;
	int32 required_spell[4];
	uint32 required_triggers[4];
	uint32 special_flags;
	char * completiontext;
	char * incompletetext;
	int32 is_repeatable;

	uint32 count_required_mob;
	uint32 count_requiredquests;
	uint32 count_requiredtriggers;
	uint32 count_receiveitems;
	uint32 count_reward_choiceitem;
	uint32 count_required_item;
	uint32 required_mobtype[4];
	uint32 count_reward_item;
	uint32 reward_xp_as_money;
};


struct GossipText_Text
{
	float Prob;
	char * Text[2];
	uint32 Lang;
	uint32 Emote[6];
};

struct GossipText
{
	uint32 ID;
	GossipText_Text Texts[8];
};

struct MapInfo
{
	uint32 mapid;
	uint32 screenid;
	uint32 type;
	uint32 playerlimit;
	uint32 minlevel;
	float repopx;
	float repopy;
	float repopz;
	uint32 repopmapid;
	char * name;
	uint32 flags;
	uint32 cooldown;
	uint32 lvl_mod_a;
	uint32 required_quest;
	uint32 required_item;

	bool HasFlag(uint32 flag)
	{
		return (flags & flag) != 0;
	}
};

#endif
#endif