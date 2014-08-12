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

#include "StdAfx.h"
#include "AuthCodes.h"

//UpdateMask Player::m_visibleUpdateMask;
#define COLLISION_MOUNT_CHECK_INTERVAL 1000

Player::Player( uint32 guid ) : m_mailBox(guid)
{
	m_objectTypeId = TYPEID_PLAYER;
	internal_object_type = INTERNAL_OBJECT_TYPE_PLAYER;
	m_valuesCount = PLAYER_END;
	m_uint32Values = _fields;

	memset(m_uint32Values, 0,(PLAYER_END)*sizeof(uint32));
	m_updateMask.SetCount(PLAYER_END);
	SetUInt32Value( OBJECT_FIELD_TYPE,TYPE_PLAYER|TYPE_UNIT|TYPE_OBJECT);
	SetUInt32Value( OBJECT_FIELD_GUID,guid);
	SetFloatValue( UNIT_FIELD_HOVERHEIGHT, 1 );
//	SetUInt32Value( PLAYER_FIELD_KNOWN_CURRENCIES, 0x1800 ); //enable pvp curency
#ifndef CATACLYSM_SUPPORT
	SetUInt32Value( PLAYER_FIELD_KNOWN_CURRENCIES, 0xFFFFFFFB ); //if i'm not wrong then only middle 7 bits are used
#endif
//	SetUInt32Value( PLAYER_FIELD_KNOWN_CURRENCIES + 1, 0xFFFFFFFF ); //if i'm not wrong then only middle 7 bits are used
	SetUInt32Value( UNIT_FIELD_MAXPOWER7, 1000 ); //if i'm not wrong then only middle 7 bits are used
	SetUInt32Value( PLAYER_FIELD_MAX_LEVEL, 80 );
	SetUInt32Value( UNIT_FIELD_FLAGS_2, UNIT_FLAG2_ENABLE_POWER_REGEN );
	SetFloatValue( PLAYER_RUNE_REGEN_1, 0.100000f ); 
	SetFloatValue( PLAYER_RUNE_REGEN_1+1, 0.100000f );
	SetFloatValue( PLAYER_RUNE_REGEN_1+2, 0.100000f );
	SetFloatValue( PLAYER_RUNE_REGEN_1+3, 0.100000f ); //death runes do not regen
	//i'm sure there is a better way for these
	SetUInt32Value( PLAYER_FIELD_GLYPH_SLOTS_1, 21 );
	SetUInt32Value( PLAYER_FIELD_GLYPH_SLOTS_1+1, 22 );
	SetUInt32Value( PLAYER_FIELD_GLYPH_SLOTS_1+2, 23 );
	SetUInt32Value( PLAYER_FIELD_GLYPH_SLOTS_1+3, 24 );
	SetUInt32Value( PLAYER_FIELD_GLYPH_SLOTS_1+4, 25 );
	SetUInt32Value( PLAYER_FIELD_GLYPH_SLOTS_1+5, 26 );
	m_wowGuid.Init(GetGUID());

	m_finishingmovesdodge	= false;
	// resurrector			= 0;
	SpellCrtiticalStrikeRatingBonus	= 0;
	SpellHasteRatingBonus	= 0.0f;
	m_lifetapbonus			= 0;
	info					= NULL;				 // Playercreate info
	SoulStone				= 0;
	SoulStoneReceiver		= 0;
	misdirectionTarget		= 0;
	bReincarnation			= false;
	removeReagentCost		= false;
	m_session				= 0;
	TrackingSpell			= 0;
	m_status				= 0;
	offhand_dmg_mod			= 0.5;
	m_walkSpeed				= 2.5f;
	m_runSpeed				= PLAYER_NORMAL_RUN_SPEED;
	m_isMoving				= false;
	last_moved				= 0;
	strafing				= false;
	jumping					=  false;
	moving					= false;
	m_ShapeShifted			= 0;
	m_curTarget				= 0;
	m_curSelection			= 0;
	m_lootGuid				= 0;
	m_Summon				= NULL;

	m_PetNumberMax			= 0;
	m_lastShotTime			= 0;

	m_H_regenTimer			= 0;
	m_P_regenTimer			= 0;
	m_onTaxi				= false;
	
	m_taxi_pos_x			= 0;
	m_taxi_pos_y			= 0;
	m_taxi_pos_z			= 0;
	m_taxi_ride_time		= 0;

	// Attack related variables
	m_blockfromspellPCT		= 0;
	m_critfromspell			= 0;
	m_spellcritfromspell	= 0;
	m_hitfromspell			= 0;

	m_healthfromspell		= 0;
	m_manafromspell			= 0;
	m_healthfromitems		= 0;
	m_manafromitems			= 0;

	m_talentresettimes		= 0;

	m_nextSave				= getMSTime() + sWorld.getIntRate(INTRATE_SAVE);

	m_currentSpell			= NULL;
	m_resurrectHealth		= m_resurrectMana = 0;

	m_GroupInviter			= 0;
	
	LFG_comment = "";
	LFG_roles = 0;
	LFG_joined_queue = 0;
	RB_map_id = 0;
	RB_type = 0;
	
/*	for(int i=0;i<MAX_LFG_QUEUE_ID;i++)
	{
		LfgType[i]=0;
		LfgDungeonId[i]=0;
	}

	m_Autojoin = false;
	m_AutoAddMem = false;
	LfmDungeonId=0;
	LfmType=0;
//	m_lfgMatch = NULL;
	m_lfgInviterGuid = 0;
	*/

	m_invitersGuid		  = 0;

	m_currentMovement	   = MOVE_UNROOT;
	m_isGmInvisible		 = false;

	//DK
	m_invitersGuid		  = 0;

	//Trade
	ResetTradeVariables();

	//Duel
	DuelingWith			 = NULL;
	m_duelCountdownTimer	= 0;
	m_duelStatus			= 0;
	m_duelState			 = DUEL_STATE_FINISHED;		// finished

	//WayPoint
	waypointunit			= NULL;

	//PVP
	//PvPTimeoutEnabled	   = false;

	//Tutorials
	for ( int aX = 0 ; aX < 8 ; aX++ )
		m_Tutorials[ aX ] = 0x00;

	m_lootGuid			  = 0;
	m_banned				= false;

	//Bind possition
	m_bind_pos_x			= 0;
	m_bind_pos_y			= 0;
	m_bind_pos_z			= 0;
	m_bind_mapid			= 0;
	m_bind_zoneid		   = 0;

	// Rest
	m_timeLogoff			= 0;
	m_isResting			 = 0;
	m_restState			 = 0;
	m_restAmount			= 0;
	m_afk_reason			= "";
	m_playedtime[0]		 = 0;
	m_playedtime[1]		 = 0;
	m_playedtime[2]		 = (uint32)UNIXTIME;

	m_AllowAreaTriggerPort  = true;

	// Battleground
	m_bgEntryPointMap	   = 0;
	m_bgEntryPointX		 = 0;	
	m_bgEntryPointY		 = 0;
	m_bgEntryPointZ		 = 0;
	m_bgEntryPointO		 = 0;
	m_bgQueueType = 0;
	m_bgQueueInstanceId = 0;
	m_bgIsQueued = false;
	m_bg = 0;

	m_bgHasFlag			 = false;
	m_bgEntryPointInstance  = 0;

	// gm stuff
	//m_invincible			= false;
	bGMTagOn				= false;
	CooldownCheat		   = false;
	CastTimeCheat		   = false;
	PowerCheat			  = false;
	FlyCheat				= false;
	
	//FIX for professions
	weapon_proficiency	  = 0x4000;//2^14
	//FIX for shit like shirt etc
	armor_proficiency	   = 1;

	m_bUnlimitedBreath	  = false;
	m_UnderwaterState	   = 0;
	m_UnderwaterTime		= 180000;
	m_UnderwaterMaxTime	 = 180000;
	m_UnderwaterLastDmg	 = getMSTime();
	m_SwimmingTime		  = 0;
	m_BreathDamageTimer	 = 0;

	//transport shit
	m_TransporterGUID		= 0;
	m_TransporterX			= 0.0f;
	m_TransporterY			= 0.0f;
	m_TransporterZ			= 0.0f;
	m_TransporterO			= 0.0f;
	m_TransporterTime		= 0.0f;
	m_lockTransportVariables= false;

	// Autoshot variables
	m_AutoShotTarget		= 0;
	m_onAutoShot			= false;
	m_AutoShotDuration		= 0;
	m_AutoShotAttackTimer	= 0;
	m_AutoShotSpell			= NULL;

	m_AttackMsgTimer		= 0;

//	timed_quest_slot		= 0;
	m_GM_SelectedGO			= 0;

	for(uint32 x = 0;x < 7; x++)
	{
		FlatResistanceModifierPos[x] = 0;
		FlatResistanceModifierNeg[x] = 0;
		BaseResistanceModPctPos[x] = 0;
		BaseResistanceModPctNeg[x] = 0; 
		ResistanceModPctPos[x] = 0;
		ResistanceModPctNeg[x] = 0;
		SpellDelayResist[x] = 0;
	} 
		
	for(uint32 a = 0; a < 5; a++)
		SpellHealDoneByAttribute[a] = 0;

	for(uint32 x = 0; x < 5; x++)
	{
		FlatStatModPos[x] = 0;
		FlatStatModNeg[x] = 0;
		StatModPctPos[x] = 0;
		StatModPctNeg[x] = 0;
		TotalStatModPctPos[x] = 0;
		TotalStatModPctNeg[x] = 0;
	}


	for(uint32 x = 0; x < CREATURE_TYPES; x++)
	{
		IncreaseDamageByType[x] = 0;
		IncreaseDamageByTypePCT[x] = 0;
		IncreaseCricticalByTypePCT[x] = 0;
	}

	PctIgnoreRegenModifier  = 0.0f;
	m_retainedrage          = 0;
	DetectedRange		   = 0;

	m_targetIcon			= 0;
	bShouldHaveLootableOnCorpse = false;
	m_MountSpellId		  = 0;
	bHasBindDialogOpen	  = false;
	m_CurrentCharm		  = 0;
	m_CurrentTransporter	= NULL;
	m_SummonedObject		= NULL;
	m_currentLoot		   = (uint64)NULL;
	pctReputationMod		= 0;
	roll					= 0;
	mUpdateCount			= 0;
    mCreationCount          = 0;
    bCreationBuffer.reserve(40000);
	bUpdateBuffer.reserve(30000);//ought to be > than enough ;)
	mOutOfRangeIds.reserve(1000);
	mOutOfRangeIdCount	  = 0;

	bProcessPending		 = false;
	for(int i = 0; i < 25; ++i)
		m_questlog[i] = NULL;

	m_ItemInterface		 = new ItemInterface(this);
	CurrentGossipMenu	   = NULL;

	SDetector =  new SpeedCheatDetector;

	cannibalize			 = false;

	m_AreaID				= 0;
	m_actionsDirty		  = false;
	cannibalizeCount		= 0;
	rageFromDamageDealt	 = 0;
	rageFromDamageTaken	 = 0;

	m_honorToday			= 0;
	m_honorYesterday		= 0;
	m_honorPoints		   = 0;
	m_killsToday			= 0;
	m_killsYesterday		= 0;
	m_killsLifetime		 = 0;
	m_honorless			 = 0;
	m_lastSeenWeather	   = 0;
	m_attacking			 = false;
	
	m_myCorpseLowGuid				= 0;
	bCorpseCreateable	   = true;
	blinked				 = false;
	m_explorationTimer	  = getMSTime();
	linkTarget			  = 0;
	AuraStackCheat			 = false;
	TriggerpassCheat = false;
	m_pvpTimer			  = 0;
	m_globalCooldown = 0;
	m_lastHonorResetTime	= 0;
	tutorialsDirty = true;
	m_TeleportState = 1;
	m_beingPushed = false;
	for(int i = 0; i < NUM_CHARTER_TYPES; ++i)
		m_charters[i]=NULL;
	for(int i = 0; i < NUM_ARENA_TEAM_TYPES; ++i)
		m_arenaTeams[i]=NULL;

	flying_aura = 0;
	resend_speed = false;
	rename_pending = false;
	for( uint32 i=0;i<128;i++)
		reputationByListId[i] = 0;

	m_comboTarget = 0;
	m_comboPoints = 0;

	SetFloatValue(UNIT_FIELD_ATTACK_POWER_MULTIPLIER, 0.0f);
	SetFloatValue(UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER, 0.0f);

	UpdateLastSpeeds();

	m_resist_critical[0]=m_resist_critical[1]=0;
	for( uint32 x = 0; x < 3; x++ )
	{
		m_resist_hit[x]		= 0.0f;
		m_attack_speed[x]	= 1.0f;
	}
	ok_to_remove = false;
	m_modphyscritdmgPCT = 0;
	m_RootedCritChanceBonus = 0;

	m_ModInterrMRegenPCT = 0;
	m_ModInterrMRegen =0;
	m_RegenManaOnSpellResist=0;
//	m_rap_mod_pct = 0;
	m_modblockabsorbvaluePCT = 0;
	m_modblockvaluefromspells = 0;
	m_summoner = m_summonInstanceId = m_summonMapId = 0;
	m_spellcomboPoints = 0;
	m_pendingBattleground = 0;
	m_deathVision = false;
	m_resurrecter = 0;
	last_heal_spell = NULL;
	m_playerInfo = NULL;
	m_sentTeleportPosition.ChangeCoords(999999.0f,999999.0f,999999.0f);
	m_PositionUpdateCounter=1;
	m_arenaPoints = 0;
	for(uint32 i=0;i<NUM_SPELL_TYPE_INDEX;i++)
		m_spellIndexTypeTargets[i] = 0;
	m_base_runSpeed = m_runSpeed;
	m_base_walkSpeed = m_walkSpeed;
	m_arenateaminviteguid=0;
	m_arenaPoints=0;
	m_honorRolloverTime=0;
	hearth_of_wild_pct = 0;
	raidgrouponlysent=false;
	loot.gold=0;
	m_waterwalk=false;
	m_setwaterwalk=false;
	m_areaSpiritHealer_guid=0;
	m_CurrentTaxiPath=NULL;
	m_setflycheat = false;
	m_fallDisabledUntil = 0;
	m_mountCheckTimer = 0;
	m_taxiMapChangeNode = 0;
	this->OnLogin();

#ifdef ENABLE_COMPRESSED_MOVEMENT
	m_movementBuffer.reserve(5000);
#endif
	
	m_requiresNoAmmo = false;
	m_safeFall = 0;
	m_noFallDamage = false;
	z_axisposition = 0.0f;
	m_passOnLoot = false;
	m_changingMaps = true;
	m_outStealthDamageBonusPct = m_outStealthDamageBonusPeriod = m_outStealthDamageBonusTimer = 0;
	m_flyhackCheckTimer = 0;
	m_achievement_points = 0;
//	controlled_vehicle = NULL;

	for(int i=0;i<TOTAL_USED_RUNES;i++)
		m_runes[i] = MAX_RUNE_VALUE;
	m_rune_types[0] = RUNE_BLOOD;	m_rune_types[1] = RUNE_BLOOD;
	m_rune_types[2] = RUNE_FROST;	m_rune_types[3] = RUNE_FROST;
	m_rune_types[4] = RUNE_UNHOLY;	m_rune_types[5] = RUNE_UNHOLY;

//	m_custom_flags = 0;
	m_Talent_point_mods = 0;
	weapon_target_armor_pct_ignore = 1;
	m_dmg_made_since_login = 0;
	m_heal_made_since_login = 0;
	m_dmg_received_since_login = 0;
	m_heal_received_since_login = 0;
	m_dmg_made_last_time = 0;
	last_received_move_opcode = 0;
	ignoreShapeShiftChecks = false;
	m_talentSpecsCount = 1;
	m_talentActiveSpec = 0;
	m_tanlentSpecRespecTimer = getMSTime() + RESPECT_COOLDOWN_INTERVAL;
	for(int i=0;i<MAX_SPEC_COUNT;i++)
		for(int j=0;j<GLYPHS_COUNT;j++)
			m_specs[i].glyphs[j]=0;
	has_mixology_talent = 0;
	has_alchemist_stone_effect = 0;
	pet_extra_talent_points = 0;

	item_level_sum = 0;
	item_enchant_level_sum = 0;
	item_count_sum = 0;

	dungeon_difficulty = DUNGEON_DIFFICULTY_NORMAL;
	raid_difficulty = RAID_DIFFICULTY_10MAN_NORMAL;

	int rate = sWorld.getIntRate(INTRATE_COMPRESSION);
	if( rate > Z_BEST_COMPRESSION )
		rate = Z_BEST_COMPRESSION;
	else if( rate < Z_DEFAULT_COMPRESSION )
		rate = Z_DEFAULT_COMPRESSION;

	// set up stream
	zlib_stream.zalloc = Z_NULL;
	zlib_stream.zfree  = Z_NULL;
	zlib_stream.opaque = Z_NULL;
	
	if( deflateInit(&zlib_stream, rate) != Z_OK )
		ASSERT( false );

	last_casted_enemy_spell = NULL;
	mount_look_override = 0;
	last_mana_regen_stamp = getMSTime();
	mana_burn_target = mana_burn_target_cast = 0;

	only_player_gm = "";	//default GMs are only player based. There are admins who have account based GM
	XPModBonusPCT = 0;
	HonorModBonusPCT = 0;
	SummonPosAdjuster.SetCenterUnit( this );
	ModAbillityAPBonusCoef = 0.0f;
	IgnoreSpellSpecialCasterStateRequirement = 0;
	m_safe_fall = false;
	m_time_sync_send_counter = 0;
#if GM_STATISTICS_UPDATE_INTERVAL > 0 
	m_GM_statistics = NULL;
#endif
}

void Player::OnLogin()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
}

Player::~Player ( )
{
	Virtual_Destructor( );
}

void Player::Virtual_Destructor ( )
{
/*	if(!ok_to_remove)
	{
		printf("Player deleted from non-logoutplayer!\n");
		OutputCrashLogLine("Player deleted from non-logoutplayer!");
#if (defined( WIN32 ) || defined( WIN64 ) )
		CStackWalker sw;
		sw.ShowCallstack();
#endif
	}*/
	sEventMgr.RemoveEvents( this );
	//fallthrough destructor(player -> Unit) would make acces higher level structures that got freed
	RemoveAllAuras();

	//only once or on second delete it will set newly logged in player to offline state
	if( IsPlayer() )
		objmgr.RemovePlayer(this);

	if(m_bg)
	{
		m_bg->RemovePlayer(this, true);
		m_bg = NULL;
	}

	if( IsInWorld() )
		RemoveFromWorld();

	if(m_session)
	{
		m_session->SetPlayer(0);
		if(!ok_to_remove)
			m_session->Disconnect();
		m_session = NULL;
	}
	ok_to_remove = false; //we were deleted. It is not ok to delete us again :P

	Player * pTarget;
	if(mTradeTarget != 0)
	{
		pTarget = GetTradeTarget();
		ResetTradeVariables();
		if(pTarget)
			pTarget->ResetTradeVariables();
	}

	if( ObjectMgr::getSingletonPtr() != NULL )
		pTarget = objmgr.GetPlayer(GetInviter());
	else 
		pTarget = NULL;

	if(pTarget)
		pTarget->SetInviter(0);

	if( m_Summon )
		m_Summon->Remove( true, false );

	if(DuelingWith != 0)
		DuelingWith->DuelingWith = 0;
	DuelingWith = 0;

	CleanupGossipMenu();
	ASSERT(!IsInWorld());

	// delete m_talenttree

	CleanupChannels();

	for(int i = 0; i < 25; ++i)
		if(m_questlog[i] != NULL)
		{
			delete m_questlog[i];
			m_questlog[i] = NULL;
		} 

	for(SplineMap::iterator itr = _splineMap.begin(); itr != _splineMap.end(); ++itr)
	{
		delete itr->second;
		itr->second = NULL;
	}
	_splineMap.clear();

	if(m_ItemInterface)
	{
		delete m_ItemInterface;
		m_ItemInterface = NULL;
	}

	for(ReputationMap::iterator itr = m_reputation.begin(); itr != m_reputation.end(); ++itr)
	{
		delete itr->second;
		itr->second = NULL;
	}
	for( int i=0;i<128;i++)
		if( reputationByListId[i] )
		{
			//delete reputationByListId[i]; this shared by m_reputation
			reputationByListId[i] = NULL;
		}
	m_reputation.clear();

	if(m_playerInfo)
	{
		m_playerInfo->m_loggedInPlayer=NULL;
		//need to remove this chain or on second delete it will set newly logged in player to offline state
		m_playerInfo = NULL;	//might be cool for debugging to keep this link
	}

	if( SDetector )
	{
		delete SDetector;
		SDetector = NULL;
	}

	while( delayedPackets.size() )
	{
		WorldPacket * pck = delayedPackets.next();
		delete pck;
	}

	std::map<uint32,AchievementVal*>::iterator itr;
	for(itr=m_achievements.begin();itr!=m_achievements.end();itr++)
	{
		delete itr->second;
		itr->second = NULL;
	}
	m_achievements.clear();

	tocritchance.clear( 1 );
	damagedone.clear( 1 );
	ignore_armor_pct.clear( 1 );

	std::map< uint32, PlayerPet* >::iterator itrp = m_Pets.begin();
	for( ; itrp != m_Pets.end(); itrp++ )
	{
		delete itrp->second;
		itrp->second = NULL;
	}
	m_Pets.clear();
	m_itemsets.clear( 1 );

	m_skills.clear();

	//!!! this is creating mem corruption sometimes. Actually this gets corrupted from soemthing else
	//m_cooldownMap[COOLDOWN_TYPE_SPELL].clear();
	//m_cooldownMap[COOLDOWN_TYPE_CATEGORY].clear();	//wtf mem corruption ?!?!?!?

	if( zlib_stream.state != Z_NULL && deflateEnd(&zlib_stream) != Z_OK)
		ASSERT( false );

	Unit::Virtual_Destructor();
	//avoid Unit destructor referencing to this object ass player after creature destructor call
	//if unit destructor will acces player fields after destructor it could create memcorruptions
	m_objectTypeId = TYPEID_UNUSED;
	internal_object_type = INTERNAL_OBJECT_TYPE_UNIT;
	PossibleGoSummons.clear( 1 );
	LFG_dungeons.SafeClear( );	ASSERT( LFG_dungeons.begin() == NULL );
	m_EquipmentSets.SafeClear( );	ASSERT( m_EquipmentSets.begin() == NULL );
#if GM_STATISTICS_UPDATE_INTERVAL > 0 
	if( m_GM_statistics )
	{
		CharacterDatabase.Execute("update gm_activity_statistics set time_active = time_active + %u, commands_executed = commands_executed + %u, mails_sent = mails_sent + %u, global_chat_messages = global_chat_messages + %u, wisper_chat_messages = wisper_chat_messages + %u, summons_made = summons_made + %u, appear_made = appear_made + %u,tickets_deleted = tickets_deleted + %u, walk_tel_distance_sum = walk_tel_distance_sum + %u where guid = %u",m_GM_statistics->time_active/1000,m_GM_statistics->commands_executed,m_GM_statistics->mails_sent,m_GM_statistics->global_chat_messages,m_GM_statistics->wisper_chat_messages,m_GM_statistics->summons_made,m_GM_statistics->appear_made,m_GM_statistics->tickets_deleted,(uint32)(sqrt(m_GM_statistics->walk_tel_distance_sum)),(uint32)GetGUID());
		delete m_GM_statistics;
		m_GM_statistics = NULL;
	}
#endif
}

ARCEMU_INLINE uint32 GetSpellForLanguage(uint32 SkillID)
{
	switch(SkillID)
	{
	case SKILL_LANG_COMMON:
		return 668;
		break;

	case SKILL_LANG_ORCISH:
		return 669;
		break;

	case SKILL_LANG_TAURAHE:
		return 670;
		break;

	case SKILL_LANG_DARNASSIAN:
		return 671;
		break;

	case SKILL_LANG_DWARVEN:
		return 672;
		break;

	case SKILL_LANG_THALASSIAN:
		return 813;
		break;

	case SKILL_LANG_DRACONIC:
		return 814;
		break;

	case SKILL_LANG_DEMON_TONGUE:
		return 815;
		break;

	case SKILL_LANG_TITAN:
		return 816;
		break;

	case SKILL_LANG_OLD_TONGUE:
		return 817;
		break;

	case SKILL_LANG_GNOMISH:
		return 7430;
		break;

	case SKILL_LANG_TROLL:
		return 7341;
		break;

	case SKILL_LANG_GUTTERSPEAK:
		return 17737;
		break;

	case SKILL_LANG_DRAENEI:
		return 29932;
		break;
	}

	return 0;
}

///====================================================================
///  Create
///  params: p_newChar
///  desc:   data from client to create a new character
///====================================================================
bool Player::Create(WorldPacket& data )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint8 race,class_,gender,skin,face,hairStyle,hairColor,facialHair,outfitId;

	// unpack data into member variables
	data >> m_name;
	
	// correct capitalization
	CapitalizeString(m_name);

	data >> race >> class_ >> gender >> skin >> face;
	data >> hairStyle >> hairColor >> facialHair >> outfitId;

	info = objmgr.GetPlayerCreateInfo(race, class_);
	if(!info)
	{
		// info not found... disconnect
		//sCheatLog.writefromsession(m_session, "tried to create invalid player with race %u and class %u", race, class_);
		SoftDisconnect();
		return false;
	}

	// check that the account CAN create TBC characters, if we're making some
	if(race >= RACE_BLOODELF && !m_session->HasFlag(ACCOUNT_FLAG_XPACK_01 | ACCOUNT_FLAG_XPACK_02))
	{
		//sCheatLog.writefromsession(m_session, "tried to create player with race %u and class %u but no expansion flags", race, class_);
		SoftDisconnect();
		return false;
	}

	m_mapId = info->mapId;
	m_zoneId = info->zoneId;
	m_position.ChangeCoords(info->positionX, info->positionY, info->positionZ);
	m_bind_pos_x = info->positionX;
	m_bind_pos_y = info->positionY;
	m_bind_pos_z = info->positionZ;
	m_bind_mapid = info->mapId;
	m_bind_zoneid = info->zoneId;
	m_isResting = 0;
	m_restAmount = 0;
	m_restState = 0;

	for(uint32 i=0;i<TAXIMASK_SIZE;i++)
		m_taximask[i] = 0;
	
	// set race dbc
	myRace = dbcCharRace.LookupEntry(race);
	myClass = dbcCharClass.LookupEntry(class_);
	if(!myRace || !myClass)
	{
		// information not found
		sCheatLog.writefromsession(m_session, "tried to create invalid player with race %u and class %u, dbc info not found", race, class_);
		SoftDisconnect();
		return false;
	}

	if(myRace->team_id == 7)
		m_team = 0;
	else
		m_team = 1;

	uint8 powertype = (uint8)(myClass->power_type);

	// Automatically add the race's taxi hub to the character's taximask at creation time ( 1 << (taxi_node_id-1) )
	switch(race)
	{
	case RACE_TAUREN:	m_taximask[0]= 2097152;		break;
	case RACE_HUMAN:	m_taximask[0]= 2;			break;
	case RACE_DWARF:	m_taximask[0]= 32;			break;
	case RACE_GNOME:	m_taximask[0]= 32;			break;
	case RACE_ORC:		m_taximask[0]= 4194304;		break;
	case RACE_TROLL:	m_taximask[0]= 4194304;		break;
	case RACE_UNDEAD:	m_taximask[0]= 1024;		break;
	case RACE_NIGHTELF:	m_taximask[0]= 100663296;	break;
	case RACE_BLOODELF:	m_taximask[2]= 131072;		break;
	case RACE_DRAENEI:	m_taximask[2]= 536870912;	break;
	}

	// Set Starting stats for char
	//SetFloatValue(OBJECT_FIELD_SCALE_X, ((race==RACE_TAUREN)?1.3f:1.0f));
	SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
	SetUInt32Value(UNIT_FIELD_HEALTH, info->health);
	SetUInt32Value(UNIT_FIELD_POWER1, info->mana );
	//SetUInt32Value(UNIT_FIELD_POWER2, 0 ); // this gets devided by 10
	SetUInt32Value(UNIT_FIELD_POWER3, info->focus );
	SetUInt32Value(UNIT_FIELD_POWER4, info->energy );
   
	SetUInt32Value(UNIT_FIELD_MAXHEALTH, info->health);
	SetUInt32Value(UNIT_FIELD_MAXPOWER1, info->mana );
	SetUInt32Value(UNIT_FIELD_MAXPOWER2, info->rage );
	SetUInt32Value(UNIT_FIELD_MAXPOWER3, info->focus );
	SetUInt32Value(UNIT_FIELD_MAXPOWER4, info->energy );
	
	//THIS IS NEEDED
	SetUInt32Value(UNIT_FIELD_BASE_HEALTH, info->health);
	SetUInt32Value(UNIT_FIELD_BASE_MANA, info->mana );
	SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, info->factiontemplate );
	SetUInt32Value(UNIT_FIELD_LEVEL, sWorld.start_level);
	SetGold( sWorld.GoldStartAmount);
	if( class_ == DEATHKNIGHT && sWorld.start_level < 55 )
	{
		SetUInt32Value(UNIT_FIELD_LEVEL, 55 );
//		m_Talent_point_mods = -( 55 - 9 ); //DK class gains talent points from quests
	}
	Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL, ACHIEVEMENT_UNUSED_FIELD_VALUE, ACHIEVEMENT_UNUSED_FIELD_VALUE, GetUInt32Value( UNIT_FIELD_LEVEL ),ACHIEVEMENT_EVENT_ACTION_SET_MAX );
	//ApplyLevelInfo(Info, sWorld.start_level);

	SetUInt32Value(UNIT_FIELD_BYTES_0, ( ( race ) | ( class_ << 8 ) | ( gender << 16 ) | ( powertype << 24 ) ) );
	//UNIT_FIELD_BYTES_1	(standstate) | (unk1) | (unk2) | (attackstate)
	SetByte(UNIT_FIELD_BYTES_2,1,UNIT_BYTE2_FLAG_PVP);
	if(class_ == WARRIOR)
		SetShapeShift(FORM_BATTLESTANCE);

	SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);
	SetUInt32Value(UNIT_FIELD_STAT0, info->strength );
	SetUInt32Value(UNIT_FIELD_STAT1, info->ability );
	SetUInt32Value(UNIT_FIELD_STAT2, info->stamina );
	SetUInt32Value(UNIT_FIELD_STAT3, info->intellect );
	SetUInt32Value(UNIT_FIELD_STAT4, info->spirit );
	SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 0.388999998569489f );
	SetFloatValue(UNIT_FIELD_COMBATREACH, 1.5f   );
	if(race != RACE_BLOODELF)
	{
		SetUInt32Value(UNIT_FIELD_DISPLAYID, info->displayId + gender );
		SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, info->displayId + gender );
	} else	{
		SetUInt32Value(UNIT_FIELD_DISPLAYID, info->displayId - gender );
		SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, info->displayId - gender );
	}
	EventModelChange();
	//SetFloatValue(UNIT_FIELD_MINDAMAGE, info->mindmg );
	//SetFloatValue(UNIT_FIELD_MAXDAMAGE, info->maxdmg );
	SetUInt32Value(UNIT_FIELD_ATTACK_POWER, info->attackpower );
	SetUInt32Value(PLAYER_BYTES, ((skin) | (face << 8) | (hairStyle << 16) | (hairColor << 24)));
	//PLAYER_BYTES_2							   GM ON/OFF	 BANKBAGSLOTS   RESTEDSTATE
   // SetUInt32Value(PLAYER_BYTES_2, (facialHair | (0xEE << 8) | (0x01 << 16) | (0x02 << 24)));
	SetUInt32Value(PLAYER_BYTES_2, (facialHair /*| (0xEE << 8)*/  | (0x02 << 24)));//no bank slot by default!

	//PLAYER_BYTES_3						   DRUNKENSTATE				 PVPRANK
	SetUInt32Value(PLAYER_BYTES_3, ((gender) | (0x00 << 8) | (0x00 << 16) | (GetPVPRank() << 24)));
	SetByte(PLAYER_BYTES_3, 3, 0);                     // BattlefieldArenaFaction (0 or 1)
	SetUInt32Value(PLAYER_NEXT_LEVEL_XP, 400);
	SetUInt32Value(PLAYER_FIELD_BYTES, PLAYER_BYTES_FLAG_HUMAN_CONTROL );
#ifndef CATACLYSM_SUPPORT
	SetUInt32Value(PLAYER_CHARACTER_POINTS2,2);
#endif
	SetFloatValue(UNIT_MOD_CAST_SPEED, 1.0f);
	SetUInt32Value(PLAYER_FIELD_MAX_LEVEL, sWorld.m_levelCap);
	
  
	for(uint32 x=0;x<7;x++)
		SetFloatValue(PLAYER_FIELD_MOD_DAMAGE_DONE_PCT+x, 1.00);

	SetUInt32Value(PLAYER_FIELD_WATCHED_FACTION_INDEX, 0xEEEEEEEE);

	m_StableSlotCount = 0;
	Item *item;

	for(std::set<uint32>::iterator sp = info->spell_list.begin();sp!=info->spell_list.end();sp++)
	{
		Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LEARN_SPELL,(*sp),ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_SET);
		SpellEntry *spe = dbcSpell.LookupEntryForced( (*sp) );
		if( spe && spe->spell_skilline )
		{
			Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILLLINE_SPELLS,spe->spell_skilline[0],ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
			Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LINE_SPELL2,spe->spell_skilline[0],ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
		}
		mSpells.insert((*sp));
	}

	m_FirstLogin = true;

	skilllineentry * se;
	for(std::list<CreateInfo_SkillStruct>::iterator ss = info->skills.begin(); ss!=info->skills.end(); ss++)
	{
		se = dbcSkillLine.LookupEntry(ss->skillid);
		if(se->type != SKILL_TYPE_LANGUAGE)
			_AddSkillLine(se->id, ss->currentval, ss->maxval);
	}
	_UpdateMaxSkillCounts();
	//Chances depend on stats must be in this order!
	//UpdateStats();
	//UpdateChances();
	
	_InitialReputation();

	// Add actionbars
	for(std::list<CreateInfo_ActionBarStruct>::iterator itr = info->actionbars.begin();itr!=info->actionbars.end();++itr)
	{
		setAction(itr->button, itr->action, itr->type, itr->misc);
	}

	for(std::list<CreateInfo_ItemStruct>::iterator is = info->items.begin(); is!=info->items.end(); is++)
	{
		if ( (*is).protoid != 0)
		{
			item=objmgr.CreateItem((*is).protoid,this);
			if(item)
			{
				item->SetUInt32Value(ITEM_FIELD_STACK_COUNT,(*is).amount);
				if((*is).slot<INVENTORY_SLOT_BAG_END)
				{
					if( GetItemInterface()->SafeAddItem(item, INVENTORY_SLOT_NOT_SET, (*is).slot) == ADD_ITEM_RESULT_ERROR )
					{
						item->DeleteMe();
						item = NULL;
					}
				}
				else
				{
					if( !GetItemInterface()->AddItemToFreeSlot(&item) )
					{
						item->DeleteMe();
						item = NULL;
					}
				}
			}
		}
	}

	sHookInterface.OnCharacterCreate(this);
	load_health = m_uint32Values[UNIT_FIELD_HEALTH];
	load_mana = m_uint32Values[UNIT_FIELD_POWER1];

	return true;
}


void Player::Update( uint32 p_time )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(!IsInWorld())
	{ 
		return;
	}

	Unit::Update( p_time );
	//it is possible we got removed while updating
	if(!IsInWorld())
	{ 
		return;
	}
	uint32 mstime = getMSTime();

#if GM_STATISTICS_UPDATE_INTERVAL > 0 
	if( m_GM_statistics && HasFlag(PLAYER_FLAGS, PLAYER_FLAG_AFK) == 0 )
	{
		float dist_x = m_GM_statistics->last_pos_x - GetPositionX();
		float dist_y = m_GM_statistics->last_pos_y - GetPositionY();
		m_GM_statistics->walk_tel_distance_sum += dist_x * dist_x + dist_y * dist_y;
		m_GM_statistics->last_pos_x = GetPositionX();
		m_GM_statistics->last_pos_y = GetPositionY();
		if( m_GM_statistics->next_afk_update < mstime )
		{
			m_GM_statistics->time_active += GM_STATISTICS_UPDATE_INTERVAL;
			m_GM_statistics->next_afk_update = mstime + GM_STATISTICS_UPDATE_INTERVAL;
		}
	}
#endif
	if(m_attacking)
	{
		// Check attack timer.
		if(mstime >= m_attackTimer)
			_EventAttack(false);

		if( m_dualWield && mstime >= m_attackTimer_1 )
			_EventAttack( true );
	}

	if( m_onAutoShot )
	{
		if( m_AutoShotAttackTimer > (int32)p_time )
		{
			//sLog.outDebug( "HUNTER AUTOSHOT 0) %i, %i", m_AutoShotAttackTimer, p_time );
			m_AutoShotAttackTimer -= p_time;
		}
		else
		{
			//sLog.outDebug( "HUNTER AUTOSHOT 1) %i", p_time );
			EventRepeatSpell();
		}
	}
	else if(m_AutoShotAttackTimer > 0)
	{
		if(m_AutoShotAttackTimer > (int32)p_time)
			m_AutoShotAttackTimer -= p_time;
		else
			m_AutoShotAttackTimer = 0;
	}
	
	// Breathing
	if( m_UnderwaterState & UNDERWATERSTATE_UNDERWATER )
	{
		// keep subtracting timer
		if( m_UnderwaterTime )
		{
			// not taking dmg yet
			if(p_time >= m_UnderwaterTime)
				m_UnderwaterTime = 0;
			else
				m_UnderwaterTime -= p_time;
		}

		if( !m_UnderwaterTime )
		{
			// check last damage dealt timestamp, and if enough time has elapsed deal damage
			if( mstime >= m_UnderwaterLastDmg )
			{
				uint32 damage = m_uint32Values[UNIT_FIELD_MAXHEALTH] / 10;
				WorldPacket data(SMSG_ENVIRONMENTALDAMAGELOG, 21);
				data << GetGUID() << uint8(DAMAGE_DROWNING) << damage << uint64(0);
				SendMessageToSet(&data, true);

				DealDamage(this, damage, 0, 0, 0);
				if( damage >= GetUInt32Value( UNIT_FIELD_HEALTH ) )
					Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM,1,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
				m_UnderwaterLastDmg = mstime + 1000;
			}
		}
	}
	else
	{
		// check if we're not on a full breath timer
		if(m_UnderwaterTime < m_UnderwaterMaxTime)
		{
			// regenning
			m_UnderwaterTime += (p_time * 10);

			if(m_UnderwaterTime >= m_UnderwaterMaxTime)
			{
				m_UnderwaterTime = m_UnderwaterMaxTime;
				StopMirrorTimer(1);
			}
		}
	}

	// Lava Damage
	if(m_UnderwaterState & UNDERWATERSTATE_LAVA)
	{
		// check last damage dealt timestamp, and if enough time has elapsed deal damage
		if(mstime >= m_UnderwaterLastDmg)
		{
			uint32 damage = m_uint32Values[UNIT_FIELD_MAXHEALTH] / 5;
			WorldPacket data(SMSG_ENVIRONMENTALDAMAGELOG, 21);
			data << GetGUID() << uint8(DAMAGE_LAVA) << damage << uint64(0);
			SendMessageToSet(&data, true);

			if( damage >= GetUInt32Value( UNIT_FIELD_HEALTH ) )
				Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM,3,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);

			DealDamage(this, damage, 0, 0, 0);
			m_UnderwaterLastDmg = mstime + 1000;
		}
	}
	if(m_UnderwaterState & UNDERWATERSTATE_SLIME)
	{
		// check last damage dealt timestamp, and if enough time has elapsed deal damage
		if(mstime >= m_UnderwaterLastDmg)
		{
			uint32 damage = m_uint32Values[UNIT_FIELD_MAXHEALTH] / 5;
			WorldPacket data(SMSG_ENVIRONMENTALDAMAGELOG, 21);
			data << GetGUID() << uint8(DAMAGE_SLIME) << damage << uint64(0);
			SendMessageToSet(&data, true);

			if( damage >= GetUInt32Value( UNIT_FIELD_HEALTH ) )
				Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM,5,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);

			DealDamage(this, damage, 0, 0, 0);
			m_UnderwaterLastDmg = mstime + 1000;
		}
	}

	// Autosave
	if(mstime >= m_nextSave)
		SaveToDB(false);

	if(m_CurrentTransporter && !m_lockTransportVariables)
	{
		// Update our position, using trnasporter X/Y
		float c_tposx = m_CurrentTransporter->GetPositionX() + m_TransporterX;
		float c_tposy = m_CurrentTransporter->GetPositionY() + m_TransporterY;
		float c_tposz = m_CurrentTransporter->GetPositionZ() + m_TransporterZ;
		SetPosition(c_tposx, c_tposy, c_tposz, GetOrientation(), false);
	}

	// Exploration
	if(mstime >= m_explorationTimer)
	{
		_EventExploration();
		m_explorationTimer = mstime + 3000;
	}

	if(m_pvpTimer)
	{
		if(p_time >= m_pvpTimer)
		{
			RemovePvPFlag();
			RemoveFFAPvPFlag();
			m_pvpTimer = 0;
		}
		else
		{
			m_pvpTimer -= p_time;
		}
	}

	if (sWorld.Collision) 
	{
		if(m_MountSpellId != 0 && mstime >= m_mountCheckTimer)
		{
			if( CollideInterface.IsIndoor( m_mapId, m_position ) )
			{
				RemoveAura( m_MountSpellId );
				m_MountSpellId = 0;
			}
			m_mountCheckTimer = mstime + COLLISION_MOUNT_CHECK_INTERVAL;
		}

		if( mstime >= m_flyhackCheckTimer )
		{
			_FlyhackCheck();
			m_flyhackCheckTimer = mstime + 10000; 
		}
	}
#define _DEBUG_SPELLS_BY_CASTING_ALL_
#ifdef _DEBUG_SPELLS_BY_CASTING_ALL_
#define FIRST_SPELL_TO_START_CASTING	1
#define STOP_CASTING_AT_ID				FIRST_SPELL_TO_START_CASTING + 11000
	static int next_spell_to_cast=FIRST_SPELL_TO_START_CASTING;
	static int next_spell_to_cast_target=FIRST_SPELL_TO_START_CASTING;
	static uint64 selection_guid=0;
	static float recall_to_x=0.0f,recall_to_y,recall_to_z;
	static int recall_map=0;
	if(( next_spell_to_cast!=FIRST_SPELL_TO_START_CASTING || GetUInt32Value( UNIT_FIELD_MAXHEALTH ) == 99999 ) && isCasting() == false && IsInWorld() )
	{
		if( recall_to_x == 0 )
		{
			recall_map = GetMapId();
			recall_to_x = GetPositionX();
			recall_to_y = GetPositionY();
			recall_to_z = GetPositionZ();
		}
		if( next_spell_to_cast > STOP_CASTING_AT_ID )
			return;
		if( m_curSelection && selection_guid == 0 )
			selection_guid = m_curSelection;
		if( m_curSelection == 0 && selection_guid == 0 )
			return;
		Unit *pVictim = NULL;
		SpellCastTargets target_mob,target_us;
		//restore our HP
		SetUInt32Value( UNIT_FIELD_HEALTH, GetUInt32Value( UNIT_FIELD_MAXHEALTH ) );
		//restore mana
		SetUInt32Value( UNIT_FIELD_POWER1, GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) );
		//revive
		if( IsDead() )
		{
			ResurrectPlayer();
			SetMovement(MOVE_UNROOT);
		}
		clearStateFlag( UF_TARGET_DIED );
		RemoveFlag( UNIT_FIELD_FLAGS, UNIT_FLAG_DEAD );
		//some spells require us leaving combat
		CombatStatus.Vanished();
		ExitVehicle();
		//get the next spell to cast
		SpellEntry *sp;
		while( next_spell_to_cast < 70000 
			&& ( ( sp = dbcSpell.LookupEntryForced( next_spell_to_cast++ ) ) == NULL 
					|| sp->Effect[0] == SPELL_EFFECT_TELEPORT_UNITS 
					|| sp->Effect[1] == SPELL_EFFECT_TELEPORT_UNITS
					|| sp->Effect[2] == SPELL_EFFECT_TELEPORT_UNITS
					)
			);
		printf("!!!!!!!!!will try to cast spell %u\n",next_spell_to_cast-1);
		{
			FILE *f=fopen("lastcast.txt","a");
			fprintf(f,"%u\n",sp->Id );
			fclose(f);
		}
		target_us.m_targetMask = TARGET_FLAG_UNIT;
		target_us.m_unitTarget = GetGUID();
		target_us.guid = GetNewGUID();
		target_us.m_srcX = target_us.m_destX = GetPositionX();
		target_us.m_srcY = target_us.m_destY = GetPositionX();
		target_us.m_srcZ = target_us.m_destZ = GetPositionX();
		if(selection_guid)
		{
			pVictim = GetMapMgr()->GetUnit(selection_guid);
			if( !pVictim )
			{
				selection_guid = 0;
				return;
			}
			//in case felt underground
			if( this->GetDistanceSq( recall_to_x, recall_to_y, recall_to_z ) > 15*15 )
				SafeTeleport( recall_map, 0, recall_to_x, recall_to_y, recall_to_z, GetOrientation() );
//			if( pVictim->GetDistanceSq( this ) > 30*30 )
//			{
//				if( pVictim->GetPositionZ() < GetPositionZ()+20)
//					pVictim->SetPositionZ(pVictim->GetPositionZ() + 10);
//				SafeTeleport( pVictim->GetMapMgr(), pVictim->GetPosition() );
//			}
			//restore unit HP
			pVictim->SetUInt32Value( UNIT_FIELD_HEALTH, pVictim->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) );
			//restore mana
			pVictim->SetUInt32Value( UNIT_FIELD_POWER1, pVictim->GetUInt32Value( UNIT_FIELD_MAXPOWER1 ) );
			//revive
			if( pVictim->IsDead() )
				pVictim->setDeathState( ALIVE );
			pVictim->clearStateFlag( UF_TARGET_DIED );
			pVictim->RemoveFlag( UNIT_FIELD_FLAGS, UNIT_FLAG_DEAD );
			//some spells require us leaving combat
			pVictim->CombatStatus.Vanished();
			//fill spell info
			target_mob.m_targetMask = TARGET_FLAG_UNIT;
			target_mob.m_unitTarget = pVictim->GetGUID();
			target_mob.guid = pVictim->GetNewGUID();
			target_mob.m_srcX = target_mob.m_destX = pVictim->GetPositionX();
			target_mob.m_srcY = target_mob.m_destY = pVictim->GetPositionX();
			target_mob.m_srcZ = target_mob.m_destZ = pVictim->GetPositionX();
			SpellEntry *sp;
			while( next_spell_to_cast_target < 70000 && ( sp = dbcSpell.LookupEntryForced( next_spell_to_cast_target++ ) ) == NULL );
			printf("!!!!!!!!!mob is trying to cast spell %u\n",next_spell_to_cast_target-1);
			Spell *spell = SpellPool.PooledNew();
//			spell->Init( pVictim, sp , false, NULL);
			spell->Init( pVictim, sp , true, NULL);//insta
			spell->prepare( &target_us );
		}
		//if we are full of auras
		if( m_auras_pas_size > 20 )
			for( uint32 x = MAX_AURAS; x < m_auras_pas_size; x++ )
				if( m_auras[x] )
					m_auras[x]->Remove();
		if( m_auras_pos_size > 20 )
			for(uint32 i = FIRST_AURA_SLOT; i < m_auras_pos_size; ++i)
				if( m_auras[i]!=NULL)
					m_auras[i]->Remove();
		if( m_auras_neg_size > 20 )
			for(uint32 i = MAX_POSITIVE_AURAS; i < m_auras_neg_size; ++i)
				if( m_auras[i]!=NULL )
					m_auras[i]->Remove();
		SetSelection( selection_guid );
		Spell *spell = SpellPool.PooledNew();
//		spell->Init( this, sp , false, NULL);
		spell->Init( this, sp , true, NULL);//insta
		spell->prepare( &target_mob );
	}
#endif
}

void Player::EventDismount(uint32 money, float x, float y, float z)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	ModGold( -(int32)money );

	SetPosition(x, y, z, true);
	if(!m_taxiPaths.size())
		SetTaxiState(false);

	SetTaxiPath(NULL);
	UnSetTaxiPos();
	m_taxi_ride_time = 0;

	SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID , 0);
	RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_MOUNTED_TAXI);
	RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);

	SetPlayerSpeed(RUN, m_runSpeed);

	sEventMgr.RemoveEvents(this, EVENT_PLAYER_TAXI_INTERPOLATE);

	// Save to database on dismount
	SaveToDB(false);

	// If we have multiple "trips" to do, "jump" on the next one :p
	if(m_taxiPaths.size())
	{
		TaxiPath * p = *m_taxiPaths.begin();
		m_taxiPaths.erase(m_taxiPaths.begin());
		TaxiStart(p, taxi_model_id, 0);
	}
}

void Player::_EventAttack( bool offhand )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if (m_currentSpell)
	{
        if(m_currentSpell->GetProto()->ChannelInterruptFlags != 0) // this is a channeled spell - ignore the attack event
        { 
            return;
        }
		m_currentSpell->safe_cancel();
		setAttackTimer(500, offhand);
		return;
	}

	if( IsFeared() || IsStunned() )
	{ 
		return;
	}

	Unit *pVictim = NULL;
	if(m_curSelection)
		pVictim = GetMapMgr()->GetUnit(m_curSelection);
	
	//Can't find victim, stop attacking
	if(!pVictim )
	{
		sLog.outDetail("Player::Update:  No valid current selection to attack, stopping attack\n");
		setHRegenTimer(5000); //prevent clicking off creature for a quick heal
		EventAttackStop();
		return;
	}
	if( isAttackable(this,pVictim) == false )
	{
		EventAttackStop();
		return;
	}

	if (!canReachWithAttack(pVictim))
	{
		if(m_AttackMsgTimer != 1)
		{
			m_session->OutPacket(SMSG_ATTACKSWING_NOTINRANGE);
			m_AttackMsgTimer = 1;
		}
		setAttackTimer(300, offhand);
	}
	else if(!isInFront(pVictim))
	{
		// We still have to do this one.
		if(m_AttackMsgTimer != 2)
		{
			m_session->OutPacket(SMSG_ATTACKSWING_BADFACING);
			m_AttackMsgTimer = 2;
		}
		setAttackTimer(300, offhand);
	}
	else
	{
		m_AttackMsgTimer = 0;
		
		// Set to weapon time.
		setAttackTimer(0, offhand);

		//pvp timeout reset
		if(pVictim->IsPlayer())
		{
			if (SafePlayerCast(pVictim)->cannibalize)
			{
				sEventMgr.RemoveEvents(pVictim, EVENT_CANNIBALIZE);
				pVictim->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
				SafePlayerCast(pVictim)->cannibalize = false;
			}
		}

		if(this->IsStealth())
		{
			RemoveAura( m_stealth );
			SetStealth(0);
		}

		if (!GetOnMeleeSpell() || offhand)
		{
			Strike( pVictim, ( offhand ? OFFHAND : MELEE ), NULL, 0, 0, 0, false, false );
				
		} 
		else 
		{ 
			SpellEntry *spellInfo = dbcSpell.LookupEntry( GetOnMeleeSpell() );
			Spell *spell = SpellPool.PooledNew();
			spell->Init( this, spellInfo, true, NULL );
			spell->extra_cast_number = GetOnMeleeSpellEcn();
			SpellCastTargets targets;
			targets.m_unitTarget = GetSelection();
			spell->prepare(&targets);
			SetOnMeleeSpell( 0 );
		}
	}
}

void Player::_EventCharmAttack()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(!m_CurrentCharm)
	{ 
		sLog.outDebug("Received charm attack command but we do not have a charm.Exiting");
		return;
	}

	Unit *pVictim = NULL;
	if(!IsInWorld())
	{
		m_CurrentCharm=0;
		sEventMgr.RemoveEvents(this,EVENT_PLAYER_CHARM_ATTACK);
		sLog.outDebug("We are not in world.Exiting");
		return;
	}

	if(m_curSelection == 0)
	{
		sEventMgr.RemoveEvents(this, EVENT_PLAYER_CHARM_ATTACK);
		sLog.outDebug("We have nothing selected to attack.Exiting");
		return;
	}

	pVictim= GetMapMgr()->GetUnit(m_curSelection);

	//Can't find victim, stop attacking
	if (!pVictim)
	{
		sLog.outError( "WORLD: "I64FMT" doesn't exist.",m_curSelection);
		sLog.outDetail("Player::Update:  No valid current selection to attack, stopping attack\n");
		this->setHRegenTimer(5000); //prevent clicking off creature for a quick heal
		clearStateFlag(UF_ATTACKING);
		EventAttackStop();
	}
	else
	{
		Unit *currentCharm = GetMapMgr()->GetUnit( m_CurrentCharm );

		if( !currentCharm )
		{ 
			sLog.outDebug("Current charm cannot be found on this map.Exiting");
			return;
		}

		if (!currentCharm->canReachWithAttack(pVictim))
		{
			if(m_AttackMsgTimer == 0)
			{
				//m_session->OutPacket(SMSG_ATTACKSWING_NOTINRANGE);
				m_AttackMsgTimer = 2000;		// 2 sec till next msg.
			}
			// Shorten, so there isnt a delay when the client IS in the right position.
			sEventMgr.ModifyEventTimeLeft(this, EVENT_PLAYER_CHARM_ATTACK, 100);	
		}
		else if(!currentCharm->isInFront(pVictim))
		{
			if(m_AttackMsgTimer == 0)
			{
				m_session->OutPacket(SMSG_ATTACKSWING_BADFACING);
				m_AttackMsgTimer = 2000;		// 2 sec till next msg.
			}
			// Shorten, so there isnt a delay when the client IS in the right position.
			sEventMgr.ModifyEventTimeLeft(this, EVENT_PLAYER_CHARM_ATTACK, 100);	
		}
		else
		{
			//if(pVictim->GetTypeId() == TYPEID_UNIT)
			//	pVictim->GetAIInterface()->StopMovement(5000);

			//pvp timeout reset
			/*if(pVictim->IsPlayer())
			{
				if( SafePlayerCast( pVictim )->DuelingWith == NULL)//Dueling doesn't trigger PVP
					SafePlayerCast( pVictim )->PvPTimeoutUpdate(false); //update targets timer

				if(DuelingWith == NULL)//Dueling doesn't trigger PVP
					PvPTimeoutUpdate(false); //update casters timer
			}*/

			if (!currentCharm->GetOnMeleeSpell())
			{
				currentCharm->Strike( pVictim, MELEE, NULL, 0, 0, 0, false, false );
			} 
			else 
			{ 
				SpellEntry *spellInfo = dbcSpell.LookupEntry(currentCharm->GetOnMeleeSpell());
				currentCharm->SetOnMeleeSpell(0);
				Spell *spell = SpellPool.PooledNew();
				spell->Init(currentCharm,spellInfo,true,NULL);
				SpellCastTargets targets;
				targets.m_unitTarget = GetSelection();
				spell->prepare(&targets);
				//delete spell;		 // deleted automatically, no need to do this.
			}
		}
	}   
}

void Player::EventAttackStart()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	m_attacking = true;
	if(m_MountSpellId)
        RemoveAura(m_MountSpellId);
}

void Player::EventAttackStop()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( m_CurrentCharm != 0 )
		sEventMgr.RemoveEvents(this, EVENT_PLAYER_CHARM_ATTACK);

	m_attacking = false;
}

void Player::_EventExploration()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if (IsDead())
	{ 
		return;
	}

	if (!IsInWorld())
	{ 
		return;
	}

	if(m_position.x > _maxX || m_position.x < _minX || m_position.y > _maxY || m_position.y < _minY)
	{ 
		return;
	}

//	uint16 new_area_id = GetMapMgr()->GetAreaID( GetPositionX(), GetPositionY() );
    uint16 new_area_id = sTerrainMgr.GetAreaID( GetMapId(), GetPositionX(), GetPositionY(), GetPositionZ() );
	if( new_area_id != 0xFFFF )
		SetAreaID( new_area_id );

	//exploration needs area, rest needs the zone id
	AreaTable * at = dbcArea.LookupEntryForced( GetAreaID() );
	if(at == NULL)
	{ 
		uint32 new_zone_id = GetProbableZoneIdForLocation( GetMapId(), GetPositionX(), GetPositionY() );
		at = dbcArea.LookupEntryForced( new_zone_id );
		if(at == NULL)
		{
			sLog.outDebug("Exploration : Missing area ID for this map(%u) and coordinate %f %f",GetMapId(), GetPositionX(), GetPositionY());
			return;
		}
		SetAreaID( new_zone_id ); //the best we have right now, we should use are though 
	}

	uint32 map_zone_id;
	//fucking dalaran is floating above CrystalsongForest. Due to overlays, dbc would return IcecrownGlacier 
	if( ( GetAreaID() == 2817 || at->ZoneId == 2817 ) && GetPositionZ() > 310 )
	{
		map_zone_id = 4395;
		SetAreaID( 4613 );
		at = dbcArea.LookupEntryForced( GetAreaID() );
	}
	else
		//this fails due to overlays
//		map_zone_id = GetZoneIdForLocation( GetMapMgr()->GetMapId(), GetPositionX(), GetPositionY() );
		//this fails because of wrong data
		map_zone_id = at->ZoneId; 

	if( map_zone_id == 0 )
		map_zone_id = at->AreaId;	//area and zone is the same atm

	if( map_zone_id )
	{
		//update our zone. I hope DBC has right values and this never fails :(
		if( map_zone_id != m_zoneId )
			EventZoneChange( map_zone_id );
		//check if area is correct for the new zone
//		AreaTable * at = dbcArea.LookupEntry( GetAreaID() );
//		if( at == NULL || ( at && at->ZoneId && at->ZoneId != map_zone_id ) )
//			SetAreaID( map_zone_id ); //we teleported or something and we have no area information at this point
	}

	int offset = at->explorationFlag / 32;
	offset += PLAYER_EXPLORED_ZONES_1;

	uint32 val = (uint32)(1 << (at->explorationFlag % 32));
	uint32 currFields = GetUInt32Value(offset);

	bool rest_on = false;
	// Check for a restable area
    if(at->AreaFlags & AREA_CITY_AREA || at->AreaFlags & AREA_CITY)
	{
		// check faction
		if((at->category == AREAC_ALLIANCE_TERRITORY && GetTeam() == 0) || (at->category == AREAC_HORDE_TERRITORY && GetTeam() == 1) )
		{
			rest_on = true;
		}
		else if(at->category != AREAC_ALLIANCE_TERRITORY && at->category != AREAC_HORDE_TERRITORY)
		{
			rest_on = true;
		}
	}
	else
	{
        //second AT check for subzones.
        if(at->ZoneId)
        {
            AreaTable * at2 = dbcArea.LookupEntry(at->ZoneId);
            if(at2 && ((at2->AreaFlags & AREA_CITY_AREA) || (at2 && at2->AreaFlags & AREA_CITY)))
            {
                if((at2->category == AREAC_ALLIANCE_TERRITORY && GetTeam() == 0) || (at2->category == AREAC_HORDE_TERRITORY && GetTeam() == 1) )
				{
					rest_on = true;
				}
				else if(at2->category != AREAC_ALLIANCE_TERRITORY && at2->category != AREAC_HORDE_TERRITORY)
				{
					rest_on = true;
				}
            }
		}
	}

	if (rest_on)
	{
		if(!m_isResting) ApplyPlayerRestState(true);
	}
	else
	{
		if(m_isResting)
		{
			if (sWorld.Collision) {
				const LocationVector & loc = GetPosition();
				if(!CollideInterface.IsIndoor(GetMapId(), loc.x, loc.y, loc.z + 2.0f))
					ApplyPlayerRestState(false);
			} else {
				ApplyPlayerRestState(false);
			}
		}
	}

	if( !(currFields & val) && !GetTaxiState() && !m_TransporterGUID)//Unexplored Area		// bur: we dont want to explore new areas when on taxi
	{
		SetUInt32Value(offset, (uint32)(currFields | val));

		uint32 explore_xp = at->level * 10;
		explore_xp *= float2int32(sWorld.getRate(RATE_EXPLOREXP));

		WorldPacket data(SMSG_EXPLORATION_EXPERIENCE, 8);
		data << at->AreaId << explore_xp;
		m_session->SendPacket(&data);

		if(getLevel() < GetUInt32Value(PLAYER_FIELD_MAX_LEVEL) && explore_xp)
			GiveXP(explore_xp, 0, false);

		//see if we get achievement on this exploration
		// we explore an area. Areas are part of zones. Overlays are a group of areas. Zones might contain multiple overlays(i think)
		// todo : do not complete whole achievement until we explore all subparts of it. Right now as you see one zone you complete the whole set of achievements
		uint32 just_discovered_area = at->AreaId;
		for(uint32 ovrlayitr=0; ovrlayitr < dbcWorldMapOverlayStore.GetNumRows(); ovrlayitr++)
		{
			WorldMapOverlay *overlay = dbcWorldMapOverlayStore.LookupRow( ovrlayitr );
			if( overlay == NULL )
				continue; //wtf ? We just iterate through rows and we ran out of them ?
			if( overlay->areaID == just_discovered_area 
				|| overlay->areaID_2 == just_discovered_area
				|| overlay->areaID_3 == just_discovered_area
				|| overlay->areaID_4 == just_discovered_area )
			{
				Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_EXPLORE_AREA, overlay->ID, ACHIEVEMENT_UNUSED_FIELD_VALUE, 1, ACHIEVEMENT_EVENT_ACTION_SET);
			}
		}
	}
}

void Player::EventDeath()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if (m_state & UF_ATTACKING)
		EventAttackStop();

	if (m_onTaxi)
		sEventMgr.RemoveEvents(this, EVENT_PLAYER_TAXI_DISMOUNT);

	if(!IS_INSTANCE(GetMapId()) && !sEventMgr.HasEvent(this,EVENT_PLAYER_FORECED_RESURECT)) //Should never be true 
		sEventMgr.AddEvent(this,&Player::RepopRequestedPlayer,EVENT_PLAYER_FORECED_RESURECT,PLAYER_FORCED_RESURECT_INTERVAL,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT); //in case he forgets to release spirit (afk or something)

	RemoveNegativeAuras();
	SetDrunkValue(0);
}

void Player::GiveTalent(uint32 talents)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 currtps = GetUInt32Value(PLAYER_CHARACTER_POINTS1);
	SetUInt32Value(PLAYER_CHARACTER_POINTS1,currtps+talents);
}

///  This function sends the message displaying the purple XP gain for the char
///  It assumes you will send out an UpdateObject packet at a later time.
void Player::GiveXP(uint32 xp, const uint64 &guid, bool allowbonus)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE

	//no levelups while dead. Some say that this makes them invincible and unable to revive
	if( getDeathState() != ALIVE )
		return;

	if ( xp < 1 )
	{ 
		return;
	}

	if(getLevel() >= GetUInt32Value(PLAYER_FIELD_MAX_LEVEL))
	{ 
		return;
	}

	//in case PVP xp was enabled and playyer leveld to much then we sould remove player from BG
	if( m_bg && m_bg->GetLevelGroup() != GetLevelGrouping( GetUInt32Value(UNIT_FIELD_LEVEL ) ) )
	{
//		m_bg->RemovePlayer( this, false );	//this crashes the realm !!
		return;
	}

	uint32 restxp = xp;

	//add reststate bonus (except for quests)
	if( allowbonus )
	{
		xp = xp + xp * XPModBonusPCT / 100;
		if(m_restState == RESTSTATE_RESTED)
		{
			restxp = SubtractRestXP(xp);
			xp += restxp;
		}
		if( m_team == 0 )
			xp = float2int32( xp * sWorld.AlianceExtraXPRate );
		else
			xp = float2int32( xp * sWorld.HordeExtraXPRate );
	}

	UpdateRestState();
	SendLogXPGain(guid,xp,restxp,guid == 0 ? true : false);

	/*
	uint32 curXP = GetUInt32Value(PLAYER_XP);
	uint32 nextLvlXP = GetUInt32Value(PLAYER_NEXT_LEVEL_XP);
	uint32 newXP = curXP + xp;
	uint32 level = GetUInt32Value(UNIT_FIELD_LEVEL);
	bool levelup = false;

	if(m_Summon != NULL && m_Summon->GetUInt32Value(UNIT_CREATED_BY_SPELL) == 0)
		m_Summon->GiveXP(xp);

	uint32 TotalHealthGain = 0, TotalManaGain = 0;
	uint32 cl=getClass();
	// Check for level-up
	while (newXP >= nextLvlXP)
	{
		levelup = true;
		// Level-Up!
		newXP -= nextLvlXP;  // reset XP to 0, but add extra from this xp add
		level ++;	// increment the level
		if( level > 9)
		{
			//Give Talent Point
			uint32 curTalentPoints = GetUInt32Value(PLAYER_CHARACTER_POINTS1);
			SetUInt32Value(PLAYER_CHARACTER_POINTS1,curTalentPoints+1);
		}
	}
	*/

	int32 newxp = m_uint32Values[PLAYER_XP] + xp;
	int32 nextlevelxp = lvlinfo->XPToNextLevel;
	uint32 level = m_uint32Values[UNIT_FIELD_LEVEL];
	LevelInfo * li;
	bool levelup = false;

	while(newxp >= nextlevelxp && newxp > 0)
	{
		++level;
		li = objmgr.GetLevelInfo(getRace(), getClass(), level);
		if (li == NULL) 
		{ 
			return;
		}
		newxp -= nextlevelxp;
		nextlevelxp = li->XPToNextLevel;
		levelup = true;

		if(level > 9)
			ModUnsigned32Value(PLAYER_CHARACTER_POINTS1, 1);

		if(level >= GetUInt32Value(PLAYER_FIELD_MAX_LEVEL))
			break;
	}

	if(level > GetUInt32Value(PLAYER_FIELD_MAX_LEVEL))
		level = GetUInt32Value(PLAYER_FIELD_MAX_LEVEL);

	if(levelup)
	{
		m_playedtime[0] = 0; //Reset the "Current level played time"

		SetUInt32Value(UNIT_FIELD_LEVEL, level);
		LevelInfo * oldlevel = lvlinfo;
		lvlinfo = objmgr.GetLevelInfo(getRace(), getClass(), level);
		if (lvlinfo == NULL) 
		{ 
			return;
		}
		CalculateBaseStats();

		// Generate Level Info Packet and Send to client
        SendLevelupInfo(
            level,
            lvlinfo->HP - oldlevel->HP,
            lvlinfo->Mana - oldlevel->Mana,
            lvlinfo->Stat[0] - oldlevel->Stat[0],
            lvlinfo->Stat[1] - oldlevel->Stat[1],
            lvlinfo->Stat[2] - oldlevel->Stat[2],
            lvlinfo->Stat[3] - oldlevel->Stat[3],
            lvlinfo->Stat[4] - oldlevel->Stat[4]);
	
		_UpdateMaxSkillCounts();
		UpdateStats();
		//UpdateChances();
		
		// Set next level conditions
		SetUInt32Value(PLAYER_NEXT_LEVEL_XP, lvlinfo->XPToNextLevel);

		// ScriptMgr hook for OnPostLevelUp
		sHookInterface.OnPostLevelUp(this);

		// Set stats
		for(uint32 i = 0; i < 5; ++i)
		{
			BaseStats[i] = lvlinfo->Stat[i];
			CalcStat(i);
		}
		//set full hp and mana
		SetUInt32Value(UNIT_FIELD_HEALTH,GetUInt32Value(UNIT_FIELD_MAXHEALTH));
		SetUInt32Value(UNIT_FIELD_POWER1,GetUInt32Value(UNIT_FIELD_MAXPOWER1));

		// if warlock has summonned pet, increase its level too
		if(info->class_ == WARLOCK)
		{
			if((m_Summon != NULL) && (m_Summon->IsInWorld()) && (m_Summon->isAlive())) 
			{
				m_Summon->ModUnsigned32Value(UNIT_FIELD_LEVEL, 1);
				m_Summon->ApplyStatsForLevel();
			}
		}
		Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,level,ACHIEVEMENT_EVENT_ACTION_SET_MAX);
		UpdateGlyphsAvail();
	}

	// Set the update bit
	SetUInt32Value(PLAYER_XP, newxp);
	
	HandleProc(PROC_ON_GAIN_EXPIERIENCE, this, NULL);
}

void Player::smsg_InitialSpells()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	PlayerCooldownMap::iterator itr, itr2;

	uint16 spellCount = (uint16)mSpells.size();
	size_t itemCount = m_cooldownMap[0].size() + m_cooldownMap[1].size();
	uint32 mstime = getMSTime();
	size_t pos;

	WorldPacket data(SMSG_INITIAL_SPELLS, 5 + (spellCount * 4) + (itemCount * 4) );
	data << uint8(0);
	data << uint16(spellCount); // spell count

	SpellSet::iterator sitr;
	for (sitr = mSpells.begin(); sitr != mSpells.end(); ++sitr)
	{
		// todo: check out when we should send 0x0 and when we should send 0xeeee
		// this is not slot,values is always eeee or 0,seems to be cooldown
		data << uint32(*sitr);				   // spell id
		data << uint16(0x0000);	 
	}

	pos = data.wpos();
	data << uint16( 0 );		// placeholder

	itemCount = 0;
	for( itr = m_cooldownMap[COOLDOWN_TYPE_SPELL].begin(); itr != m_cooldownMap[COOLDOWN_TYPE_SPELL].end(); )
	{
		itr2 = itr++;

		// don't keep around expired cooldowns
		if( itr2->second.ExpireTime < mstime || (itr2->second.ExpireTime - mstime) < 10000 )
		{
			m_cooldownMap[COOLDOWN_TYPE_SPELL].erase( itr2 );
			continue;
		}

		data << uint32( itr2->first );						// spell id
		data << uint16( itr2->second.ItemId );				// item id
		data << uint16( 0 );								// spell category
		data << uint32( itr2->second.ExpireTime - mstime );	// cooldown remaining in ms (for spell)
		data << uint32( 0 );								// cooldown remaining in ms (for category)

		++itemCount;

#ifdef _DEBUG
		Log.Debug("InitialSpells", "sending spell cooldown for spell %u to %u ms", itr2->first, itr2->second.ExpireTime - mstime);
#endif
	}

	for( itr = m_cooldownMap[COOLDOWN_TYPE_CATEGORY].begin(); itr != m_cooldownMap[COOLDOWN_TYPE_CATEGORY].end(); )
	{
		itr2 = itr++;

		// don't keep around expired cooldowns
		if( itr2->second.ExpireTime < mstime || (itr2->second.ExpireTime - mstime) < 10000 )
		{
			m_cooldownMap[COOLDOWN_TYPE_CATEGORY].erase( itr2 );
			continue;
		}

		data << uint32( itr2->second.SpellId );				// spell id
		data << uint16( itr2->second.ItemId );				// item id
		data << uint16( itr2->first );						// spell category
		data << uint32( 0 );								// cooldown remaining in ms (for spell)
		data << uint32( itr2->second.ExpireTime - mstime );	// cooldown remaining in ms (for category)

		++itemCount;

#ifdef _DEBUG
		Log.Debug("InitialSpells", "sending category cooldown for cat %u to %u ms", itr2->first, itr2->second.ExpireTime - mstime);
#endif
	}

	
#ifdef USING_BIG_ENDIAN
	*(uint16*)&data.contents()[pos] = swap16((uint16)itemCount);
#else
	*(uint16*)&data.contents()[pos] = (uint16)itemCount;
#endif

	GetSession()->SendPacket(&data);

	uint32 v = 0;
//	GetSession()->OutPacket(SMSG_SERVER_BUCK_DATA, 4, &v);
	//Log::getSingleton( ).outDetail( "CHARACTER: Sent Initial Spells" );
}

void Player::_SavePet(QueryBuffer * buf)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// Remove any existing info
	if(buf == NULL)
		CharacterDatabase.Execute("DELETE FROM playerpets WHERE ownerguid=%u", GetUInt32Value(OBJECT_FIELD_GUID));
	else
		buf->AddQuery("DELETE FROM playerpets WHERE ownerguid=%u", GetUInt32Value(OBJECT_FIELD_GUID));

	if( m_Summon && m_Summon->IsInWorld() && m_Summon->GetPetOwner() == this )	// update PlayerPets array with current pet's info
	{
		PlayerPet*pPet = GetPlayerPet( m_Summon->GetUInt32Value( UNIT_FIELD_PETNUMBER ) );
		if(!pPet || pPet->active == false)
			m_Summon->UpdatePetInfo(true);
		else m_Summon->UpdatePetInfo(false);

		if(!m_Summon->Summon)	   // is a pet
		{
			// save pet spellz
			PetSpellMap::iterator itr;
			uint32 pn = m_Summon->GetUInt32Value( UNIT_FIELD_PETNUMBER );
			if(buf == NULL)
				CharacterDatabase.Execute("DELETE FROM playerpetspells WHERE petnumber=%u and ownerguid=%u", pn,GetLowGUID() );
			else
				buf->AddQuery("DELETE FROM playerpetspells WHERE petnumber=%u and ownerguid=%u", pn,GetLowGUID() );

			for(itr = m_Summon->mSpells.begin(); itr != m_Summon->mSpells.end(); ++itr)
			{
				if(buf == NULL)
					CharacterDatabase.Execute("INSERT INTO playerpetspells VALUES(%u, %u, %u, %u)", GetLowGUID(), pn, itr->first->Id, itr->second);
				else
					buf->AddQuery("INSERT INTO playerpetspells VALUES(%u, %u, %u, %u)", GetLowGUID(), pn, itr->first->Id, itr->second);
			}
			//talents are special spells :)
			std::map<uint32, uint8>::iterator itr2;
			for(itr2 = m_Summon->m_talents.begin(); itr2 != m_Summon->m_talents.end(); ++itr2)
			{
				uint32 talententry = itr2->first;
				uint16 rank_as_flags = itr2->second;
				rank_as_flags |= PET_ACTION_SPELL_IS_TALENT;
				if(buf == NULL)
					CharacterDatabase.Execute("INSERT INTO playerpetspells VALUES(%u, %u, %u, %u)", GetLowGUID(), pn, talententry, rank_as_flags);
				else
					buf->AddQuery("INSERT INTO playerpetspells VALUES(%u, %u, %u, %u)", GetLowGUID(), pn, talententry, rank_as_flags);
			}
		}
	}

	std::stringstream ss;

	for(std::map<uint32, PlayerPet*>::iterator itr = m_Pets.begin(); itr != m_Pets.end(); itr++)
	{
		ss.rdbuf()->str("");
		ss << "REPLACE INTO playerpets VALUES('"
			<< GetLowGUID() << "','"
			<< itr->second->number << "','"
			<< CharacterDatabase.EscapeString(itr->second->name) << "','"
			<< itr->second->entry << "','"
			<< itr->second->fields << "','"
			<< itr->second->xp << "','"
			<< (itr->second->active ?  1 : 0) + itr->second->stablestate * 10 << "','"
			<< itr->second->level << "','"
//			<< itr->second->loyaltyxp << "','"
			<< itr->second->actionbar << "','"
			<< itr->second->happinessupdate << "','"
			<< itr->second->summon << "','"
//			<< itr->second->loyaltypts << "','"
//			<< itr->second->loyaltyupdate << "','"
			<< (long)itr->second->reset_time << "','"
			<< itr->second->reset_cost << "','"
			<< itr->second->spellid << "')";
			
		if(buf == NULL)
			CharacterDatabase.ExecuteNA(ss.str().c_str());
		else
			buf->AddQueryStr(ss.str());
	}
}

void Player::_SavePetSpells(QueryBuffer * buf)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	
	// Remove any existing
	if(buf == NULL)
		CharacterDatabase.Execute("DELETE FROM playersummonspells WHERE ownerguid=%u", GetLowGUID());
	else
		buf->AddQuery("DELETE FROM playersummonspells WHERE ownerguid=%u", GetLowGUID());

	// Save summon spells
	map<uint32, set<uint32> >::iterator itr = SummonSpells.begin();
	for(; itr != SummonSpells.end(); ++itr)
	{
		set<uint32>::iterator it = itr->second.begin();
		for(; it != itr->second.end(); ++it)
		{
			if(buf == NULL)
				CharacterDatabase.Execute("INSERT INTO playersummonspells VALUES(%u, %u, %u)", GetLowGUID(), itr->first, (*it));
			else
				buf->AddQuery("INSERT INTO playersummonspells VALUES(%u, %u, %u)", GetLowGUID(), itr->first, (*it));
		}
	}
}

void Player::AddSummonSpell(uint32 Entry, uint32 SpellID)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SpellEntry * sp = dbcSpell.LookupEntry(SpellID);
	map<uint32, set<uint32> >::iterator itr = SummonSpells.find(Entry);
	if(itr == SummonSpells.end())
		SummonSpells[Entry].insert(SpellID);
	else
	{
		set<uint32>::iterator it3;
		for(set<uint32>::iterator it2 = itr->second.begin(); it2 != itr->second.end();)
		{
			it3 = it2++;
			if(dbcSpell.LookupEntry(*it3)->NameHash == sp->NameHash)
				itr->second.erase(it3);
		}
		itr->second.insert(SpellID);
	}
}

void Player::RemoveSummonSpell(uint32 Entry, uint32 SpellID)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	map<uint32, set<uint32> >::iterator itr = SummonSpells.find(Entry);
	if(itr != SummonSpells.end())
	{
		itr->second.erase(SpellID);
		if(itr->second.size() == 0)
			SummonSpells.erase(itr);
	}
}

set<uint32>* Player::GetSummonSpells(uint32 Entry)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	map<uint32, set<uint32> >::iterator itr = SummonSpells.find(Entry);
	if(itr != SummonSpells.end())
	{
		return &(itr->second);
	}
	return 0;
}

void Player::_LoadPet(QueryResult * result)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	m_PetNumberMax=0;
	if(!result)
	{ 
		return;
	}

	do
	{
		Field *fields = result->Fetch();
		fields = result->Fetch();

		PlayerPet *pet = new PlayerPet;
		uint32 ind=1;
		pet->number  = fields[ind++].GetUInt32();
		pet->name	= fields[ind++].GetString();
		pet->entry   = fields[ind++].GetUInt32();
		pet->fields  = fields[ind++].GetString();
		pet->xp	  = fields[ind++].GetUInt32();
		pet->active  = fields[ind].GetInt8()%10 > 0 ? true : false;
		pet->stablestate = fields[ind++].GetInt8() / 10;
		pet->level   = fields[ind++].GetUInt32();
//		pet->loyaltyxp = fields[ind++].GetUInt32();
		pet->actionbar = fields[ind++].GetString();
		pet->happinessupdate = fields[ind++].GetUInt32();
		pet->summon = (fields[ind++].GetUInt32()>0 ? true : false);
//		pet->loyaltypts = fields[ind++].GetUInt32();
//		pet->loyaltyupdate = fields[ind++].GetUInt32();
		pet->reset_time = fields[ind++].GetUInt32();
		pet->reset_cost = fields[ind++].GetUInt32();
		pet->spellid = fields[ind++].GetUInt32();

		m_Pets[pet->number] = pet;
		
		if(pet->number > m_PetNumberMax)
			m_PetNumberMax =  pet->number;
	}while(result->NextRow());
}

void Player::SpawnPet(uint32 pet_number)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	std::map<uint32, PlayerPet*>::iterator itr = m_Pets.find(pet_number);
	if(itr == m_Pets.end())
	{
		sLog.outError("PET SYSTEM: "I64FMT" Tried to load invalid pet %d", GetGUID(), pet_number);
		return;
	}
	Pet *pPet = objmgr.CreatePet( itr->second->entry , pet_number );
	pPet->LoadFromDB( this, itr->second );
	
	if( itr->second->spellid )
	{
		//if demonic sacrifice auras are still active, remove them
		RemoveAura( 18789 );
		RemoveAura( 18790 );
		RemoveAura( 18791 );
		RemoveAura( 18792 );
		RemoveAura( 35701 );
	}
}

void Player::SpawnActivePet()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( m_Summon != NULL || !isAlive() )
	{ 
		return;
	}

	std::map< uint32, PlayerPet* >::iterator itr = m_Pets.begin();
	for( ; itr != m_Pets.end(); itr++ )
		if( itr->second->stablestate == STABLE_STATE_ACTIVE && itr->second->active )
		{
			SpawnPet( itr->first );
			return;
		}
}

void Player::_LoadPetSpells(QueryResult * result)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	std::stringstream query;
	std::map<uint32, std::list<uint32>* >::iterator itr;
	uint32 entry = 0;
	uint32 spell = 0;

	if(result)
	{
		do
		{
			Field *fields = result->Fetch();
			entry = fields[1].GetUInt32();
			spell = fields[2].GetUInt32();
			AddSummonSpell(entry, spell);
		}
		while( result->NextRow() ); 
	}
}

void Player::addSpell(uint32 spell_id, bool skip_skill_add_due_to_load )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SpellSet::iterator iter = mSpells.find(spell_id);
	if(iter != mSpells.end())
	{ 
		return;
	}
		
	Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LEARN_SPELL,spell_id,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_SET);
	SpellEntry *spe = dbcSpell.LookupEntryForced( spell_id );
	if( spe && spe->spell_skilline )
	{
		Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILLLINE_SPELLS,spe->spell_skilline[0],ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
		Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LINE_SPELL2,spe->spell_skilline[0],ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	}
	mSpells.insert(spell_id);
	if(IsInWorld())
	{
		sStackWolrdPacket( learnspell, SMSG_LEARNED_SPELL, 8);
		learnspell << spell_id;
//		learnspell << uint16( 0 );	//from 3.2
		m_session->SendPacket( &learnspell );
	}

	// Check if we're a deleted spell
	iter = mDeletedSpells.find(spell_id);
	if(iter != mDeletedSpells.end())
		mDeletedSpells.erase(iter);

	// Check if we're logging in.
	if( ! IsInWorld() || skip_skill_add_due_to_load == true )
	{ 
		return;
	}

	SpellEntry *sp = dbcSpell.LookupEntryForced( spell_id );
	//maybe we should not even add this spell ?
	if( !sp )
		return;

	//should we make sure when changing specs to remove / readd this spell ? Spells that depend on talents have this
	if( sp->spell_learn_is_linked_to_talent )
		m_specs[ m_talentActiveSpec ].SpecSpecificSpells.insert( spell_id );

	// Add the skill line for this spell if we don't already have it.
	for(uint32 i=0;i<sp->spell_skilline_assoc_counter;i++)
	{
		if( !_HasSkillLine( sp->spell_skilline[ i ] ) )
		{
			skilllineentry * skill = dbcSkillLine.LookupEntry( sp->spell_skilline[ i ] );
			SpellEntry * spell = dbcSpell.LookupEntry(spell_id);
			uint32 max = 1;
			Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL,skill->id,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_SET_MAX);
			switch(skill->type)
			{
				case SKILL_TYPE_PROFESSION:
					max=75*((spell->RankNumber)+1);
#ifndef CATACLYSM_SUPPORT
					ModUnsigned32Value( PLAYER_CHARACTER_POINTS2, -1 ); // we are learning a proffesion, so substract a point.
#endif
					break;
				case SKILL_TYPE_SECONDARY:
					max=75*((spell->RankNumber)+1);
					break;
				case SKILL_TYPE_WEAPON:
					max=5*getLevel();
					break;
				case SKILL_TYPE_CLASS:
				case SKILL_TYPE_ARMOR:
					if(skill->id == SKILL_LOCKPICKING
	//					|| skill->id == SKILL_POISONS
						)
						max=5*getLevel();
					break;
			};

			_AddSkillLine( sp->spell_skilline[ i ], 1, max);
			_UpdateMaxSkillCounts();
		}
	}
}

//===================================================================================================================
//  Set Create Player Bits -- Sets bits required for creating a player in the updateMask.
//  Note:  Doesn't set Quest or Inventory bits
//  updateMask - the updatemask to hold the set bits
//===================================================================================================================
void Player::_SetCreateBits(UpdateMask *updateMask, Player *target) const
{
	if(target == this)
	{
		Object::_SetCreateBits(updateMask, target);
	}
	else
	{
		UpdateMask *m=sWorld.create_update_for_other_masks[ TYPEID_PLAYER ];
		for(uint32 index = 0; index < m_valuesCount; index++)
		{
			if(m_uint32Values[index] != 0 
				&& m->GetBit(index)
				)
				updateMask->SetBit(index);
		}
	}
}
/*
void Player::_SetUpdateBits(UpdateMask *updateMask, Player *target) const
{
	if(target == this)
	{
		Object::_SetUpdateBits(updateMask, target);
	}
	else
	{
		Object::_SetUpdateBits(updateMask, target);
		*updateMask &= Player::m_visibleUpdateMask;
	}
}

void Player::InitVisibleUpdateBits()
{
	Player::m_visibleUpdateMask.SetCount(PLAYER_END);
	Player::m_visibleUpdateMask.SetBit(OBJECT_FIELD_GUID);
	Player::m_visibleUpdateMask.SetBit(OBJECT_FIELD_TYPE);
	Player::m_visibleUpdateMask.SetBit(OBJECT_FIELD_SCALE_X);

	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_SUMMON);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_SUMMON+1);

	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_TARGET);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_TARGET+1);

	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_HEALTH);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_POWER1);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_POWER2);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_POWER3);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_POWER4);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_POWER5);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_POWER7);

	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_MAXHEALTH);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_MAXPOWER1);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_MAXPOWER2);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_MAXPOWER3);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_MAXPOWER4);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_MAXPOWER5);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_MAXPOWER7);

	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_LEVEL);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_FACTIONTEMPLATE);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_BYTES_0);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_FLAGS);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_FLAGS_2);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_AURASTATE);
//	for(uint32 i = UNIT_FIELD_AURA; i <= UNIT_FIELD_AURASTATE; i ++)
//		Player::m_visibleUpdateMask.SetBit(i);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_BASEATTACKTIME);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_BASEATTACKTIME+1);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_BOUNDINGRADIUS);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_COMBATREACH);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_DISPLAYID);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_NATIVEDISPLAYID);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_MOUNTDISPLAYID);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_BYTES_1);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_MOUNTDISPLAYID);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_PETNUMBER);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_PET_NAME_TIMESTAMP);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_CHANNEL_OBJECT);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_CHANNEL_OBJECT+1);
	Player::m_visibleUpdateMask.SetBit(UNIT_CHANNEL_SPELL);
	Player::m_visibleUpdateMask.SetBit(UNIT_DYNAMIC_FLAGS);
	Player::m_visibleUpdateMask.SetBit(UNIT_NPC_EMOTESTATE);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_HOVERHEIGHT);

	Player::m_visibleUpdateMask.SetBit(PLAYER_FLAGS);
	Player::m_visibleUpdateMask.SetBit(PLAYER_BYTES);
	Player::m_visibleUpdateMask.SetBit(PLAYER_BYTES_2);
	Player::m_visibleUpdateMask.SetBit(PLAYER_BYTES_3);
	Player::m_visibleUpdateMask.SetBit(PLAYER_GUILD_TIMESTAMP);
	Player::m_visibleUpdateMask.SetBit(PLAYER_DUEL_TEAM);
	Player::m_visibleUpdateMask.SetBit(PLAYER_DUEL_ARBITER);
	Player::m_visibleUpdateMask.SetBit(PLAYER_DUEL_ARBITER+1);
	Player::m_visibleUpdateMask.SetBit(PLAYER_GUILDID);
	Player::m_visibleUpdateMask.SetBit(PLAYER_GUILDRANK);
	Player::m_visibleUpdateMask.SetBit(PLAYER_CHOSEN_TITLE);
	Player::m_visibleUpdateMask.SetBit(UNIT_FIELD_BYTES_2);

	for(uint16 i = 0; i < EQUIPMENT_SLOT_END; i++)
	{
//		Player::m_visibleUpdateMask.SetBit((uint16)(PLAYER_VISIBLE_ITEM_1_0 + (i*(PLAYER_VISIBLE_ITEM_2_CREATOR - PLAYER_VISIBLE_ITEM_1_CREATOR)))); // visual items for other players
//		Player::m_visibleUpdateMask.SetBit((uint16)(PLAYER_VISIBLE_ITEM_1_0+1 + (i*(PLAYER_VISIBLE_ITEM_2_CREATOR - PLAYER_VISIBLE_ITEM_1_CREATOR)))); // visual items for other players
		Player::m_visibleUpdateMask.SetBit( PLAYER_VISIBLE_ITEM_1_ENTRYID + 2*i ); // visual items for other players
		Player::m_visibleUpdateMask.SetBit( PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + 2*i ); // visual items for other players
	}
	/* fuck i hate const - burlex */
	/*if(target && target->GetGroup() == const_cast<Player*>(this)->GetGroup() && const_cast<Player*>(this)->GetSubGroup() == target->GetSubGroup())
	{
	// quest fields are the same for party members
	for(uint32 i = PLAYER_QUEST_LOG_1_01; i < PLAYER_QUEST_LOG_25_2; ++i)
	Player::m_visibleUpdateMask.SetBit(i);
	}*/
//}


void Player::DestroyForPlayer( Player *target, uint8 anim )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	Unit::DestroyForPlayer( target, 0 );
}

#define IS_ARENA(x) ( (x) >= BATTLEGROUND_ARENA_2V2 && (x) <= BATTLEGROUND_ARENA_5V5 )

void Player::SaveToDB(bool bNewCharacter /* =false */)
{
	//shit happens somehow. Logoutplayer calls savetodb for an inexistent player object :(
	//need to figure out how on earth player object gets deleted and not removed from worldsession
	if( !IsPlayer() || deleted != OBJ_AVAILABLE )
		return;

	bool in_arena = false;
	QueryBuffer * buf = NULL;
	if(!bNewCharacter)
		buf = new QueryBuffer;

	if( m_bg != NULL && IS_ARENA( m_bg->GetType() ) )
		in_arena = true;

#ifndef CATACLYSM_SUPPORT
	if(m_uint32Values[PLAYER_CHARACTER_POINTS2]>2)
		m_uint32Values[PLAYER_CHARACTER_POINTS2]=2;
#endif
 
	//Calc played times
	uint32 playedt = (uint32)UNIXTIME - m_playedtime[2];
	m_playedtime[0] += playedt;
	m_playedtime[1] += playedt;
	m_playedtime[2] += playedt;
	
	std::stringstream ss;
	ss << "REPLACE INTO characters VALUES ("
		
	<< GetLowGUID() << ", "
	<< GetSession()->GetAccountId() << ","

	// stat saving
	<< "'" << m_name << "', "
	<< uint32(getRace()) << ","
	<< uint32(getClass()) << ","
	<< uint32(getGender()) << ",";

	if(m_uint32Values[UNIT_FIELD_FACTIONTEMPLATE] != info->factiontemplate)
		ss << m_uint32Values[UNIT_FIELD_FACTIONTEMPLATE] << ",";
	else
		ss << "0,";

	ss << uint32(getLevel()) << ","
	<< m_uint32Values[PLAYER_XP] << ","
	
	// dump exploration data
	<< "'";

	for(uint32 i = PLAYER_EXPLORED_ZONES_1-PLAYER_EXPLORED_ZONES_1; i < PLAYER_REST_STATE_EXPERIENCE-PLAYER_EXPLORED_ZONES_1; ++i)
		ss << m_uint32Values[PLAYER_EXPLORED_ZONES_1 + i] << ",";

	ss << "','";

	// dump skill data
	/*for(uint32 i=PLAYER_SKILL_INFO_1_1;i<PLAYER_CHARACTER_POINTS1;i+=3)
	{
		if(m_uint32Values[i])
		{
			ss << m_uint32Values[i] << ","
			  << m_uint32Values[i+1]<< ",";
		}
	}*/

	/*for(uint32 i = PLAYER_SKILL_INFO_1_1; i < PLAYER_CHARACTER_POINTS1; ++i)
		ss << m_uint32Values[i] << " ";
	*/

	for(SkillMap::iterator itr = m_skills.begin(); itr != m_skills.end(); ++itr)
	{
		if(itr->first && itr->second.Skill->type != SKILL_TYPE_LANGUAGE)
		{
			ss << itr->first << ";"
				<< itr->second.CurrentValue << ";"
				<< itr->second.MaximumValue << ";";
		}
	}

	uint32 player_flags = m_uint32Values[PLAYER_FLAGS];
	{
		// Remove un-needed and problematic player flags from being saved :p
		if(player_flags & PLAYER_FLAG_PARTY_LEADER)
			player_flags &= ~PLAYER_FLAG_PARTY_LEADER;
		if(player_flags & PLAYER_FLAG_AFK)
			player_flags &= ~PLAYER_FLAG_AFK;
		if(player_flags & PLAYER_FLAG_DND)
			player_flags &= ~PLAYER_FLAG_DND;
		if(player_flags & PLAYER_FLAG_GM)
			player_flags &= ~PLAYER_FLAG_GM;
		if(player_flags & PLAYER_IS_PVP_CLIENT_SIDE_FLAGS)
			player_flags &= ~PLAYER_IS_PVP_CLIENT_SIDE_FLAGS;
		if(player_flags & PLAYER_FLAG_FREE_FOR_ALL_PVP)
			player_flags &= ~PLAYER_FLAG_FREE_FOR_ALL_PVP;
	}

	ss << "', "
	<< m_uint32Values[PLAYER_FIELD_WATCHED_FACTION_INDEX] << ","
	<< m_uint32Values[PLAYER_CHOSEN_TITLE]<< ","
	<< GetUInt64Value(PLAYER_FIELD_KNOWN_TITLES) << ","
	<< GetGold() << ","
#ifdef CATACLYSM_SUPPORT
	<< uint32( 0 ) << ","
	<< uint32( 0 ) << ",";
#else 
	<< m_uint32Values[PLAYER_AMMO_ID] << ","
	<< m_uint32Values[PLAYER_CHARACTER_POINTS2] << ",";
#endif

	if (m_uint32Values[PLAYER_CHARACTER_POINTS1] > (uint32)max(0,( PLAYER_LEVEL_CAP - 9 + m_Talent_point_mods )) &&  ! GetSession()->HasGMPermissions())
            SetUInt32Value(PLAYER_CHARACTER_POINTS1, max(0,(PLAYER_LEVEL_CAP - 9 + m_Talent_point_mods)));
	ss << m_uint32Values[PLAYER_CHARACTER_POINTS1] << ","
	<< load_health << ","
	<< load_mana << ","
	<< uint32(GetPVPRank()) << ","
	<< m_uint32Values[PLAYER_BYTES] << ","
	<< m_uint32Values[PLAYER_BYTES_2] << ","
	<< player_flags << ","
	<< m_uint32Values[PLAYER_FIELD_BYTES] << ",";

	if( in_arena )
	{
		// if its an arena, save the entry coords instead
		ss << "'" << m_bgEntryPointX << "', ";
		ss << "'" << m_bgEntryPointY << "', ";
		ss << "'" << m_bgEntryPointZ << "', ";
		ss << "'" << m_bgEntryPointO << "', ";
		ss << m_bgEntryPointMap << ", ";
	}
	else
	{
		// save the normal position
		ss << "'" << m_position.x << "', "
		<< "'" << m_position.y << "', "
		<< "'" << m_position.z << "', "
		<< "'" << m_position.o << "', "
		<< m_mapId << ", ";
	}

	ss << m_zoneId << ", '";
		
	for(uint32 i = 0; i < TAXIMASK_SIZE; i++ )
		ss << m_taximask[i] << " ";
	ss << "', "
	
	<< m_banned << ", '"
	<< CharacterDatabase.EscapeString(m_banreason) << "', "
	<< (uint32)UNIXTIME << ",";
	
	//online state
	if(GetSession()->_loggingOut || bNewCharacter)
	{
		ss << "0,";
	}else
	{
		ss << "1,";
	}

	ss	 
	<< "'" << m_bind_pos_x			 << "', "
	<< "'" << m_bind_pos_y			 << "', "
	<< "'" << m_bind_pos_z			 << "', "
	<< m_bind_mapid			 << ", "
	<< m_bind_zoneid			<< ", "
		
	<< uint32(m_isResting)	  << ", "
	<< uint32(m_restState)	  << ", "
	<< uint32(m_restAmount)	 << ", '"
	  
	<< uint32(m_playedtime[0])  << " "
	<< uint32(m_playedtime[1])  << " "
	<< uint32(playedt)		  << " ', "
	<< uint32(m_deathState)	 << ", "

	<< m_talentresettimes	   << ", "
	<< m_FirstLogin			 << ", "
	<< rename_pending
	<< "," << m_arenaPoints << ","
	<< (uint32)m_StableSlotCount << ",";
	
	// instances
	if( in_arena )
	{
		ss << m_bgEntryPointInstance << ", ";
	}
	else
	{
		ss << m_instanceId		   << ", ";
	}

	ss << m_bgEntryPointMap	  << ", " 
	<< "'" << m_bgEntryPointX		<< "', " 
	<< "'" << m_bgEntryPointY		<< "', " 
	<< "'" << m_bgEntryPointZ		<< "', "
	<< "'" << m_bgEntryPointO		<< "', "
	<< m_bgEntryPointInstance << ", ";

	// taxi
	if(m_onTaxi&&m_CurrentTaxiPath) {
		ss << m_CurrentTaxiPath->GetID() << ", ";
		ss << lastNode << ", ";
		ss << GetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID);
	} else {
		ss << "0, 0, 0";
	}
	
	ss << "," << (m_CurrentTransporter ? m_CurrentTransporter->GetEntry() : (uint32)0);
	ss << ",'" << m_TransporterX << "','" << m_TransporterY << "','" << m_TransporterZ << "'";
	ss << ",'";

	// Dump spell data to stringstream
	SpellSet::iterator spellItr = mSpells.begin();
	for(; spellItr != mSpells.end(); ++spellItr)
	{
		ss << uint32(*spellItr) << ",";
	}
	ss << "','";
	// Dump deleted spell data to stringstream
	spellItr = mDeletedSpells.begin();
	for(; spellItr != mDeletedSpells.end(); ++spellItr)
	{
		ss << uint32(*spellItr) << ",";
	}

	ss << "','";
	// Dump reputation data
	ReputationMap::iterator iter = m_reputation.begin();
	for(; iter != m_reputation.end(); ++iter)
		if( iter->second ) //how can get this to NULL ? Seems like a memory alloc error
	{
		ss << int32(iter->first) << "," << int32(iter->second->flag) << "," << int32(iter->second->baseStanding) << "," << int32(iter->second->standing) << ",";
	}
	ss << "','";
	
	// Add player action bars
	for(uint32 i = 0; i < PLAYER_ACTION_BUTTON_COUNT; ++i)
	{
		ss << uint32(mActions[i].Action) << ","
			<< uint32(mActions[i].Misc) << ","
			<< uint32(mActions[i].Type) << ",";
	}
	ss << "','";

	if(!bNewCharacter)
		SaveAuras(ss);

//	ss << LoadAuras;
	ss << "','";

	// Add player finished quests
	set<uint32>::iterator fq = m_finishedQuests.begin();
	for(; fq != m_finishedQuests.end(); ++fq)
	{
		ss << (*fq) << ",";
	}

	ss << "', '";
	DailyMutex.Acquire();
	set<uint32>::iterator fdq = m_finishedDailies.begin();
	for(; fdq != m_finishedDailies.end(); fdq++)
	{
		ss << (*fdq) << ",";
	}
	DailyMutex.Release();
	ss << "', ";
	ss << m_honorRolloverTime << ", ";
	ss << m_killsToday << ", " << m_killsYesterday << ", " << m_killsLifetime << ", ";
	ss << m_honorToday << ", " << m_honorYesterday << ", ";
	ss << m_honorPoints << ", ";
    ss << GetInstanceDifficulty() << ",";

	//save the status of our achievements
	ss << m_achievement_points << ", ";
	ss << "'";
	std::map<uint32,AchievementVal*>::iterator itr;
	for(itr=m_achievements.begin();itr!=m_achievements.end();itr++)
		ss << itr->first << "," << itr->second->completed_at_stamp << ","<< itr->second->cur_value << ",";
	ss << "'"; //achievements end

	ss << ",'" << m_Talent_point_mods << "'"; //talent point mods

	ss << ",'" << only_player_gm << "'";

	//save glyps
	for(int specc=0;specc<=1;specc++)
	{
		ss << ",'";
		for(uint32 i=0;i<GLYPHS_COUNT;i++)
			ss << m_specs[specc].glyphs[i] << ",";
		ss <<"'";
	}

	//talent specs
	for(int specc=0;specc<=1;specc++)
	{
		std::map<uint32, uint8>::iterator itrtal;
		ss << ",'";
		for(itrtal = m_specs[specc].talents.begin(); itrtal != m_specs[specc].talents.end(); itrtal++)
		{
			ss << uint32(itrtal->first) << ',' ;	// TalentId
			ss << uint32(itrtal->second) << ',' ;	// TalentRank
		}
		ss <<"'";
	}

	ss << "," << (uint32)(m_talentSpecsCount) << "," << (uint32)(m_talentActiveSpec) << "";

	//spec specific spells
	for(int specc=0;specc<=1;specc++)
	{
		SpellSet::iterator specs_itr;
		ss << ",'";
		for(specs_itr = m_specs[specc].SpecSpecificSpells.begin(); specs_itr != m_specs[specc].SpecSpecificSpells.end(); specs_itr++)
			ss << uint32( *specs_itr ) << ',' ;	
		ss <<"'";
	}

	ss << "," << GetUInt64Value(PLAYER_FIELD_KNOWN_TITLES1) << ",";
	ss << GetUInt64Value(PLAYER_FIELD_KNOWN_TITLES2) << ",";
	ss << "'" << m_name_suffix.c_str() << "', '";

	DailyMutex.Acquire();
	fdq = m_finishedWeeklies.begin();
	for(; fdq != m_finishedWeeklies.end(); fdq++)
	{
		ss << (*fdq) << ",";
	}
	DailyMutex.Release();
	ss << "'";

	ss << ")";
	//sLog.outDebug( "%s",ss.str().c_str() );

	if(bNewCharacter)
		CharacterDatabase.WaitExecuteNA(ss.str().c_str());
	else
		buf->AddQueryStr(ss.str());

	//Save Other related player stuff

	// Inventory
	 GetItemInterface()->mSaveItemsToDatabase(bNewCharacter, buf);

	// save quest progress
	_SaveQuestLogEntry(buf);

	// Tutorials
	_SaveTutorials(buf);

	// GM Ticket
	//TODO: Is this really necessary? Tickets will allways be saved on creation, update and so on...
	GM_Ticket* ticket = objmgr.GetGMTicketByPlayer(GetGUID());
	if(ticket != NULL)
		objmgr.SaveGMTicket(ticket, buf);

	// Cooldown Items
	_SavePlayerCooldowns( buf );
	
	// Pets
	if(getClass() == HUNTER || getClass() == WARLOCK)
	{
		_SavePet(buf);
		_SavePetSpells(buf);
	}
	m_nextSave = getMSTime() + sWorld.getIntRate(INTRATE_SAVE);

	// equipment sets if player has any defined
	_SaveEquipmentSets( buf );

	if(buf)
		CharacterDatabase.AddQueryBuffer(buf);
}

void Player::_SaveQuestLogEntry(QueryBuffer * buf)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	for(std::set<uint32>::iterator itr = m_removequests.begin(); itr != m_removequests.end(); ++itr)
	{
		if(buf == NULL)
			CharacterDatabase.Execute("DELETE FROM questlog WHERE player_guid=%u AND quest_id=%u", GetLowGUID(), (*itr));
		else
			buf->AddQuery("DELETE FROM questlog WHERE player_guid=%u AND quest_id=%u", GetLowGUID(), (*itr));
	}

	m_removequests.clear();

	for(int i = 0; i < 25; ++i)
	{
		if(m_questlog[i] != NULL)
			m_questlog[i]->SaveToDB(buf);
	}
}

bool Player::canCast(SpellEntry *m_spellInfo)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if ( m_spellInfo->EquippedItemClass != 0 && m_spellInfo->EquippedItemClass != -1
		&& m_spellInfo->EquippedItemSubClass != 0 && m_spellInfo->EquippedItemSubClass != -1
		)
	{
		uint32 subclassflags = 0;
		if( GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND) )
			subclassflags |= (1 << GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND)->GetProto()->SubClass);
		if( GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND) )
			subclassflags |= (1 << GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND)->GetProto()->SubClass);
		if( GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_RANGED) )
			subclassflags |= (1 << GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_RANGED)->GetProto()->SubClass);
		if( (m_spellInfo->EquippedItemSubClass & subclassflags) == 0)
		{ 
			return false;
		}
	}
	return true;
}

void Player::RemovePendingPlayer()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(m_session)
	{
		uint8 respons = CHAR_LOGIN_NO_CHARACTER;		// CHAR_LOGIN_NO_CHARACTER
		m_session->OutPacket(SMSG_CHARACTER_LOGIN_FAILED, 1, &respons);
		m_session->m_loggingInPlayer = NULL;
	}

	ok_to_remove = true;
	sGarbageCollection.AddObject( this );
}

bool Player::LoadFromDB(uint32 guid)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	AsyncQuery * q = new AsyncQuery( new SQLClassCallbackP0<Player>(this, &Player::LoadFromDBProc) );
	q->AddQuery("SELECT * FROM characters WHERE guid=%u AND forced_rename_pending = 0",guid);
	q->AddQuery("SELECT * FROM tutorials WHERE playerId=%u",guid);
	q->AddQuery("SELECT cooldown_type, cooldown_misc, cooldown_expire_time, cooldown_spellid, cooldown_itemid FROM playercooldowns WHERE player_guid=%u", guid);
	q->AddQuery("SELECT * FROM questlog WHERE player_guid=%u",guid);
	q->AddQuery("SELECT * FROM playeritems WHERE ownerguid=%u ORDER BY containerslot ASC", guid);
	q->AddQuery("SELECT * FROM playerpets WHERE ownerguid=%u ORDER BY petnumber", guid);
	q->AddQuery("SELECT * FROM playersummonspells where ownerguid=%u ORDER BY entryid", guid);
	q->AddQuery("SELECT * FROM mailbox WHERE player_guid = %u", guid);

	// social
	q->AddQuery("SELECT friend_guid, note FROM social_friends WHERE character_guid = %u", guid);
	q->AddQuery("SELECT character_guid FROM social_friends WHERE friend_guid = %u", guid);
	q->AddQuery("SELECT ignore_guid FROM social_ignores WHERE character_guid = %u", guid);

	q->AddQuery("SELECT * FROM character_equipmentsets WHERE guid=%u", guid);

	// queue it!
	m_uint32Values[OBJECT_FIELD_GUID] = guid;
	CharacterDatabase.QueueAsyncQuery(q);
	return true;
}

void Player::LoadFromDBProc(QueryResultVector & results)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 field_index = 2;
#define get_next_field fields[field_index++]

	if(GetSession() == NULL || results.size() < 8)		// should have 8 queryresults for aplayer load.
	{
		Log.Error ("Player::LoadFromDB",
				"Player login query size failed! guid = %u size %u",
				GetLowGUID (),results.size());
		RemovePendingPlayer();
		return;
	}

	QueryResult *result = results[0].result;
	if(!result)
	{
		Log.Error ("Player::LoadFromDB",
				"Player login query failed! guid = %u",
				GetLowGUID ());
		RemovePendingPlayer();
		return;
	}

	if (result->GetFieldCount () != 96)
	{
		Log.Error ("Player::LoadFromDB",
				"Expected 96 fields from the database, "
				"but received %u!",
				(unsigned int) result->GetFieldCount ());
		RemovePendingPlayer();
		return;
	}

	Field *fields = result->Fetch();

	if(fields[1].GetUInt32() != m_session->GetAccountId())
	{
		sCheatLog.writefromsession(m_session, "player tried to load character not belonging to them (guid %u, on account %u)",
			fields[0].GetUInt32(), fields[1].GetUInt32());
		RemovePendingPlayer();
		return;
	}

	uint32 banned = fields[32].GetUInt32();
	if(banned && (banned < 100 || banned > (uint32)UNIXTIME))
	{
		RemovePendingPlayer();
		return;
	}

	// Load name
	m_name = get_next_field.GetString();
   
	// Load race/class from fields
	setRace(get_next_field.GetUInt8());
	setClass(get_next_field.GetUInt8());
	setGender(get_next_field.GetUInt8());
	uint32 cfaction = get_next_field.GetUInt32();
	
	// set race dbc
	myRace = dbcCharRace.LookupEntryForced(getRace());
	myClass = dbcCharClass.LookupEntryForced(getClass());
	if(!myClass || !myRace)
	{
		// bad character
		if( !myClass )
		{
			printf("guid %u failed to login, no class dbc found. (class %u )\n", (unsigned int)GetLowGUID(), (unsigned int)getClass());
			printf("number of rows in class dbc = %u \n",dbcCharClass.GetNumRows());
			for(uint32 i=0;i<dbcCharClass.GetNumRows();i++)
			{
				CharClassEntry *t = dbcCharClass.LookupRow(i);
				printf("\t !!! this is row %u and entry is %u \n",i,t->class_id);
			}
		}
		if( !myRace )
		{
			printf("guid %u failed to login, no race dbc found. (race %u)\n", (unsigned int)GetLowGUID(), (unsigned int)getRace());
			printf("number of rows in race dbc = %u \n",dbcCharRace.GetNumRows());
			for(uint32 i=0;i<dbcCharRace.GetNumRows();i++)
			{
				CharRaceEntry *t = dbcCharRace.LookupRow(i);
				printf("\t !!! this is row %u and entry is %u \n",i,t->race_id);
			}
		}
		Log.Error ("Player::LoadFromDB",
				"Player login failed! guid = %u, Could not find correct race and class info",
				GetLowGUID ());
		RemovePendingPlayer();
		return;
	}

	if(myRace->team_id == 7)
	{
		m_bgTeam = m_team = 0;
	}
	else
	{
		m_bgTeam = m_team = 1;
	}

	SetNoseLevel();

	// set power type
	SetPowerType(myClass->power_type);

	// obtain player create info
	info = objmgr.GetPlayerCreateInfo(getRace(), getClass());
	if(!info)
	{
		sLog.outError("%s: player guid %u has no playerCreateInfo!\n", (unsigned int)GetLowGUID());
		RemovePendingPlayer();
		return;
	}

	// set level
	m_uint32Values[UNIT_FIELD_LEVEL] = get_next_field.GetUInt32();
	/*if(m_uint32Values[UNIT_FIELD_LEVEL] > PLAYER_LEVEL_CAP)
		m_uint32Values[UNIT_FIELD_LEVEL] = PLAYER_LEVEL_CAP;*/

	// obtain level/stats information
	lvlinfo = objmgr.GetLevelInfo(getRace(), getClass(), getLevel());
	
	if(!lvlinfo)
	{
		printf("guid %u level %u class %u race %u levelinfo not found!\n", (unsigned int)GetLowGUID(), (unsigned int)getLevel(), (unsigned int)getClass(), (unsigned int)getRace());
		RemovePendingPlayer();
		return;
	}
	
	CalculateBaseStats();

	// set xp
	m_uint32Values[PLAYER_XP] = get_next_field.GetUInt32();
	
	// Process exploration data.
	uint32 Counter = 0;
	char * end;
	char * start = (char*)get_next_field.GetString();//buff;
	while(Counter < PLAYER_REST_STATE_EXPERIENCE - PLAYER_EXPLORED_ZONES_1 ) 
	{
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		SetUInt32Value(PLAYER_EXPLORED_ZONES_1 + Counter, atol(start));
		start = end +1;
		Counter++;
	}

	// Process skill data.
	Counter = 0;
	start = (char*)get_next_field.GetString();//buff;
	
	// new format
	const ItemProf * prof;
	if(!strchr(start, ' ') && !strchr(start,';'))
	{
		/* no skills - reset to defaults */
		for(std::list<CreateInfo_SkillStruct>::iterator ss = info->skills.begin(); ss!=info->skills.end(); ss++)
		{
			if(ss->skillid && ss->currentval && ss->maxval && !::GetSpellForLanguage(ss->skillid))
				_AddSkillLine(ss->skillid, ss->currentval, ss->maxval);		
		}
	}
	else
	{
		char * f = strdup_local(start);
		start = f;
		if(!strchr(start,';'))
		{
			/* old skill format.. :< */
			uint32 v1,v2,v3;
			PlayerSkill sk;
			for(;;)
			{
				end = strchr(start, ' ');
				if(!end)
					break;

				*end = 0;
				v1 = atol(start);
				start = end + 1;

				end = strchr(start, ' ');
				if(!end)
					break;

				*end = 0;
				v2 = atol(start);
				start = end + 1;

				end = strchr(start, ' ');
				if(!end)
					break;

				v3 = atol(start);
				start = end + 1;
				if(v1 & 0xffff)
				{
					sk.Reset(v1 & 0xffff);
					if( sk.Skill == NULL )
						continue;
					sk.CurrentValue = v2 & 0xffff;
					sk.MaximumValue = (v2 >> 16) & 0xffff;

					if( !sk.CurrentValue )
						sk.CurrentValue = 1;

					m_skills.insert( make_pair(sk.Skill->id, sk) );
				}
			}
		}
		else
		{
			uint32 v1,v2,v3;
			PlayerSkill sk;
			for(;;)
			{
				end = strchr(start, ';');
				if(!end)
					break;

				*end = 0;
				v1 = atol(start);
				start = end + 1;

				end = strchr(start, ';');
				if(!end)
					break;

				*end = 0;
				v2 = atol(start);
				start = end + 1;

				end = strchr(start, ';');
				if(!end)
					break;

				v3 = atol(start);
				start = end + 1;

				/* add the skill */
				if(v1)
				{
					sk.Reset(v1);
					if( sk.Skill == NULL )
						continue;
					sk.CurrentValue = v2;
					sk.MaximumValue = v3;

					if( !sk.CurrentValue )
						sk.CurrentValue = 1;

					m_skills.insert(make_pair(v1, sk));
				}
			}
		}
		free(f);
	}

	for(SkillMap::iterator itr = m_skills.begin(); itr != m_skills.end(); ++itr)
	{
		if(itr->first == SKILL_RIDING)
		{
			itr->second.CurrentValue = itr->second.MaximumValue;
		}

		prof = GetProficiencyBySkill(itr->first);
		if(prof)
		{
			if(prof->itemclass==4)
				armor_proficiency|=prof->subclass;
			else
				weapon_proficiency|=prof->subclass;
		}
		//it would be enough to run this only once 
		AutoLearnSkillRankSpells(itr->second.Skill->id, itr->second.CurrentValue);
	}

	// set the rest of the stuff
	m_uint32Values[ PLAYER_FIELD_WATCHED_FACTION_INDEX ]	= get_next_field.GetUInt32();
	m_uint32Values[ PLAYER_CHOSEN_TITLE ]					= get_next_field.GetUInt32();
	SetUInt64Value( PLAYER_FIELD_KNOWN_TITLES,				get_next_field.GetUInt64() );
	SetGold(												get_next_field.GetUInt32() );
#ifdef CATACLYSM_SUPPORT
	get_next_field.GetUInt32();
	get_next_field.GetUInt32();
#else
	m_uint32Values[ PLAYER_AMMO_ID ]						= get_next_field.GetUInt32();
	m_uint32Values[ PLAYER_CHARACTER_POINTS2 ]				= get_next_field.GetUInt32();
#endif
	m_uint32Values[ PLAYER_CHARACTER_POINTS1 ]				= get_next_field.GetUInt32();
	load_health												= get_next_field.GetUInt32();
	load_mana												= get_next_field.GetUInt32();
	SetUInt32Value( UNIT_FIELD_HEALTH, load_health );
	uint8 pvprank = get_next_field.GetUInt8();
	SetUInt32Value( PLAYER_BYTES, get_next_field.GetUInt32() );
	SetUInt32Value( PLAYER_BYTES_2, get_next_field.GetUInt32() );
	SetUInt32Value( PLAYER_BYTES_3, getGender() | ( pvprank << 24 ) );
	SetUInt32Value( PLAYER_FLAGS, get_next_field.GetUInt32() );
//	SetUInt32Value( PLAYER_FLAGS, 262176 );
//	SetUInt32Value( UNIT_FIELD_AURASTATE, 4194304 );
	SetUInt32Value( PLAYER_FIELD_BYTES, get_next_field.GetUInt32() );
	//m_uint32Values[0x22]=(m_uint32Values[0x22]>0x46)?0x46:m_uint32Values[0x22];

	m_position.x										= get_next_field.GetFloat();
	m_position.y										= get_next_field.GetFloat();
	m_position.z										= get_next_field.GetFloat();
	m_position.o										= get_next_field.GetFloat();

	m_mapId												= get_next_field.GetUInt32();
	m_zoneId											= get_next_field.GetUInt32();

	// Calculate the base stats now they're all loaded
	for(uint32 i = 0; i < 5; ++i)
		CalcStat(i);

  //  for(uint32 x = PLAYER_SPELL_CRIT_PERCENTAGE1; x < PLAYER_SPELL_CRIT_PERCENTAGE06 + 1; ++x)
	///	SetFloatValue(x, 0.0f);

	for(uint32 x = PLAYER_FIELD_MOD_DAMAGE_DONE_PCT; x < PLAYER_FIELD_MOD_HEALING_DONE_POS; ++x)
		SetFloatValue(x, 1.0f);

	// Normal processing...
//	UpdateMaxSkills();
	UpdateStats();
	//UpdateChances();

	// Initialize 'normal' fields
	//SetFloatValue(OBJECT_FIELD_SCALE_X, ((getRace()==RACE_TAUREN)?1.3f:1.0f));
	SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0f);
	//SetUInt32Value(UNIT_FIELD_POWER2, 0);
	SetUInt32Value(UNIT_FIELD_POWER3, info->focus);
	SetUInt32Value(UNIT_FIELD_POWER4, info->energy );
	SetUInt32Value(UNIT_FIELD_MAXPOWER2, info->rage );
	SetUInt32Value(UNIT_FIELD_MAXPOWER3, info->focus );
	SetUInt32Value(UNIT_FIELD_MAXPOWER4, info->energy );
	if(getClass() == WARRIOR)
		SetShapeShift(FORM_BATTLESTANCE);

//	SetByte(UNIT_FIELD_BYTES_2,1,0); //clear pvp. We will set it if it is required
	SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);
	SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 0.388999998569489f );
	SetFloatValue(UNIT_FIELD_COMBATREACH, 1.5f   );

	if(getRace() != 10)
	{
		SetUInt32Value(UNIT_FIELD_DISPLAYID, info->displayId + getGender() );
		SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, info->displayId + getGender() );
	} else	{
		SetUInt32Value(UNIT_FIELD_DISPLAYID, info->displayId - getGender() );
		SetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID, info->displayId - getGender() );
	}
	EventModelChange();

	SetFloatValue(UNIT_MOD_CAST_SPEED, 1.0f);
	SetUInt32Value(PLAYER_FIELD_MAX_LEVEL, sWorld.m_levelCap);
	SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, info->factiontemplate);
	if(cfaction)
	{
		SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, info->factiontemplate);
		// re-calculate team
		switch(cfaction)
		{
		case 1:	// human
		case 3:	// dwarf
		case 4: // ne
		case 8:	// gnome
		case 927:	// dreinei
			m_team = m_bgTeam = 0;
			break;

		default:
			m_team = m_bgTeam = 1;
			break;
		}
	}
 
	LoadTaxiMask( get_next_field.GetString() );

	m_banned = get_next_field.GetUInt32(); //Character ban
	m_banreason = get_next_field.GetString();
	m_timeLogoff = get_next_field.GetUInt32();
	field_index++;
	
	m_bind_pos_x = get_next_field.GetFloat();
	m_bind_pos_y = get_next_field.GetFloat();
	m_bind_pos_z = get_next_field.GetFloat();
	m_bind_mapid = get_next_field.GetUInt32();
	m_bind_zoneid = get_next_field.GetUInt32();

	m_isResting = get_next_field.GetUInt8();
	m_restState = get_next_field.GetUInt8();
	m_restAmount = get_next_field.GetUInt32();


	std::string tmpStr = get_next_field.GetString();
	m_playedtime[0] = (uint32)atoi((const char*)strtok((char*)tmpStr.c_str()," "));
	m_playedtime[1] = (uint32)atoi((const char*)strtok(NULL," "));

	m_deathState = (DeathState)get_next_field.GetUInt32();
	m_talentresettimes = get_next_field.GetUInt32();
	m_FirstLogin = get_next_field.GetBool();
	rename_pending = get_next_field.GetBool();
	m_arenaPoints = get_next_field.GetUInt32();
	if (m_arenaPoints > 5000) m_arenaPoints = 5000;
	for(uint32 z = 0; z < NUM_CHARTER_TYPES; ++z)
		m_charters[z] = objmgr.GetCharterByGuid(GetGUID(), (CharterTypes)z);
	for(uint32 z = 0; z < NUM_ARENA_TEAM_TYPES; ++z)
	{
		m_arenaTeams[z] = objmgr.GetArenaTeamByGuid(GetLowGUID(), z);
		if(m_arenaTeams[z] != NULL)
			m_arenaTeams[z]->InitMemberPlayerFields( this );
	}

	m_StableSlotCount = get_next_field.GetUInt32();
	m_instanceId = get_next_field.GetUInt32();
	m_bgEntryPointMap = get_next_field.GetUInt32();
	m_bgEntryPointX = get_next_field.GetFloat();
	m_bgEntryPointY = get_next_field.GetFloat();
	m_bgEntryPointZ = get_next_field.GetFloat();
	m_bgEntryPointO = get_next_field.GetFloat();
	m_bgEntryPointInstance = get_next_field.GetUInt32();	

	uint32 taxipath = get_next_field.GetUInt32();
	TaxiPath *path = NULL;
	if(taxipath)
	{
		path = sTaxiMgr.GetTaxiPath(taxipath);
		lastNode = get_next_field.GetUInt32();
		if(path)
		{
			SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, get_next_field.GetUInt32());
			SetTaxiPath(path);
			m_onTaxi = true;
		}
		else
			field_index++;
	}
	else
	{
		field_index++;
		field_index++;
	}

	m_TransporterGUID = get_next_field.GetUInt32();
	if(m_TransporterGUID)
	{
		Transporter * t = objmgr.GetTransporter(GUID_LOPART(m_TransporterGUID));
		m_TransporterGUID = t ? t->GetGUID() : 0;
	}

	m_TransporterX = get_next_field.GetFloat();
	m_TransporterY = get_next_field.GetFloat();
	m_TransporterZ = get_next_field.GetFloat();
	
	// Load Spells from CSV data.
	start = (char*)get_next_field.GetString();//buff;
	SpellEntry * spProto;
	//if no spells then reset to default
	if( strchr(start,',') == NULL )
	{
		info = objmgr.GetPlayerCreateInfo(getRace(), getClass());
		for(std::set<uint32>::iterator sp = info->spell_list.begin();sp!=info->spell_list.end();sp++)
			if(*sp)
				mSpells.insert(*sp);
	}
	else
	{
		while(true) 
		{
			end = strchr(start,',');
			if(!end)
				break;
			*end=0;
			//mSpells.insert(atol(start));
			uint32 spell_id = atol(start);
//language fix 2 : added in rev 800 and remove around rev 1000 pls
if( spell_id == 814 || spell_id == 815 || spell_id == 816 )
{
	start = end +1;
	continue;
}
			spProto = dbcSpell.LookupEntryForced( spell_id );
			if(spProto)
				mSpells.insert(spProto->Id);			
			start = end +1;
		}
	}

	start = (char*)get_next_field.GetString();//buff;
	while(true) 
	{
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		spProto = dbcSpell.LookupEntryForced(atol(start));
		if(spProto)
			mDeletedSpells.insert(spProto->Id);
		start = end +1;
	}

	// Load Reputatation CSV Data
	start =(char*) get_next_field.GetString();
	FactionDBC * factdbc ;
	FactionReputation * rep;
	uint32 id;
	int32 basestanding;
	int32 standing;
	uint32 fflag;
	while(true) 
	{
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		id = atol(start);
		start = end +1;

		end = strchr(start,',');
		if(!end)break;
		*end=0;
		fflag = atol(start);
		start = end +1;
		
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		basestanding = atoi(start);//atol(start);
		start = end +1;
		
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		standing  = atoi(start);// atol(start);
		start = end +1;

		// listid stuff
		factdbc = dbcFaction.LookupEntryForced(id);
		if ( factdbc == NULL || factdbc->RepListId < 0 ) continue;
		ReputationMap::iterator rtr = m_reputation.find(id);
		if(rtr != m_reputation.end())
		{
			delete rtr->second;
			rtr->second = NULL;
		}

		rep = new FactionReputation;
		rep->baseStanding = basestanding;
		rep->standing = standing;
		rep->flag = fflag;
		m_reputation[id]=rep;
		reputationByListId[factdbc->RepListId] = rep;
	}

	if(!m_reputation.size())
		_InitialReputation();

	// Load saved actionbars
	start =  (char*)get_next_field.GetString();
	Counter =0;
	while(Counter < PLAYER_ACTION_BUTTON_COUNT)
	{
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		mActions[Counter].Action = (uint16)atol(start);
		start = end +1;
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		mActions[Counter].Misc = (uint8)atol(start);
		start = end +1;
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		mActions[Counter++].Type = (uint8)atol(start);
		start = end +1;
	}
	
	//LoadAuras = get_next_field.GetString();
	start = (char*)get_next_field.GetString();//buff;
	do 
	{
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		LoginAura la;
		la.id = atol(start);
		start = end +1;
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		la.dur = atol(start);
		start = end +1;
		end = strchr(start,',');
        if(!end)break;
        *end=0;
        la.positive = (start!=NULL);
        start = end +1;
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		la.charges = atol(start);
		start = end +1;
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		la.mod_ammount = atol(start);
		start = end +1;
		loginauras.push_back(la);
	} while(true);

	// Load saved finished quests

	start =  (char*)get_next_field.GetString();
	while(true)
	{
		end = strchr(start,',');
		if(!end)break;
		*end=0;
		m_finishedQuests.insert(atol(start));
		start = end +1;
	}
	
	start = (char*)get_next_field.GetString();
	while(true)
	{
		end = strchr(start,',');
		if(!end) break;
		*end = 0;
		m_finishedDailies.insert(atol(start));
		start = end +1;
	}
	
	m_honorRolloverTime = get_next_field.GetUInt32();
	m_killsToday = get_next_field.GetUInt32();
	m_killsYesterday = get_next_field.GetUInt32();
	m_killsLifetime = get_next_field.GetUInt32();
	
	m_honorToday = get_next_field.GetUInt32();
	m_honorYesterday = get_next_field.GetUInt32();
	m_honorPoints = get_next_field.GetUInt32();
	if (m_honorPoints > 75000) m_honorPoints = 75000;

	RolloverHonor();
    //instance_difficulty = get_next_field.GetUInt32();
	get_next_field.GetUInt32();

	//load achievement status
	m_achievement_points = get_next_field.GetUInt32();
	start = (char*)get_next_field.GetString();//buff;
	while(start) 
	{
		AchievementVal *newachi = new AchievementVal;
		uint32 achiid;

		end = strchr(start,',');
		if(!end)
		{
			delete newachi;
			newachi = NULL;
			break;
		}
		*end=0;
		achiid = atol(start);
		start = end +1;

		end = strchr(start,',');
		if(!end)
		{
			delete newachi;
			newachi = NULL;
			break;
		}
		*end=0;
		newachi->completed_at_stamp = atol(start);
		start = end +1;

		end = strchr(start,',');
		if(!end)
		{
			delete newachi;
			newachi = NULL;
			break;
		}
		*end=0;
		newachi->cur_value = atol(start);
		start = end +1;

		m_achievements[ achiid ] = newachi;
	};
	//end loading achievements

	//talent point mods
	m_Talent_point_mods = get_next_field.GetInt32();

	//load GM status override
	start = (char*)get_next_field.GetString();//buff;
	if( GetSession()->HasPermissions() == false && start && strlen(start)>0 && GetSession() )
	{
		only_player_gm = start;//buff;
		GetSession()->LoadSecurity( only_player_gm );
	}
#ifdef FORCED_GM_TRAINEE_MODE
	if( GetSession()->HasPermissions() && !GetSession()->HasGMPermissions() )
	{
		//force GM mode
		bGMTagOn = true;
		SetFlag(PLAYER_FLAGS, PLAYER_FLAG_GM);	// <GM>
		//force him to be friendly to all
		SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE,35);
		_setFaction();
		//set basic setup
		m_setflycheat = true;
		bInvincible = true;
		TriggerpassCheat = true;
		m_isGmInvisible = true;
//		m_invisible = true;
		SetUInt32Value(UNIT_FIELD_LEVEL,80);
		addSpell(58984);
		addSpell(1787);
		addSpell(11392);
		m_speedModifier = 200;
		//rune shield visible only
		{
			SpellCastTargets targets( GetGUID() );
			SpellEntry *spellInfo = dbcSpell.LookupEntry( 37729 );
			Spell *spell = SpellPool.PooledNew();
			spell->Init( this, spellInfo ,true, NULL);
			spell->forced_duration = 60000000;
			spell->forced_basepoints[0] = 0;
			spell->forced_basepoints[1] = 0;
			spell->forced_basepoints[2] = 0;
			spell->prepare(&targets);

			spellInfo = dbcSpell.LookupEntry( 41431 );
			spell = SpellPool.PooledNew();
			spell->Init( this, spellInfo ,true, NULL);
			spell->forced_duration = 60000000;
			spell->forced_basepoints[0] = 0;
			spell->forced_basepoints[1] = 0;
			spell->forced_basepoints[2] = 0;
			spell->prepare(&targets);
		}
	}
#endif

	//load spec glyphs
	for(int spec_ind=0;spec_ind<=1;spec_ind++)
	{
		start = (char*)get_next_field.GetString();//buff;
		uint32 glyphcounter=0;
		while(start) 
		{
			uint32 glyph_id;

			end = strchr(start,',');
			if(!end)
				break;
			*end=0;
			glyph_id = atol(start);
			start = end +1;

			if( !glyph_id || dbcGlyphPropertiesStore.LookupEntryForced( glyph_id ) == NULL )
			{
				glyphcounter++;	//this needs to be incremented all the time
				continue;
			}

			//don't load more then we could handle
			if( glyphcounter >= GLYPHS_COUNT )
				break; 
			m_specs[spec_ind].glyphs[ glyphcounter ] = glyph_id;
			glyphcounter++;	//this needs to be incremented all the time
		};
	}
	//load talent specs
	for(int spec_ind=0;spec_ind<=1;spec_ind++)
	{
		start = (char*)get_next_field.GetString();//buff;
		while(start) 
		{
			uint32 talent_entry;
			uint32 talent_rank;

			end = strchr(start,',');
			if(!end)
				break;
			*end=0;
			talent_entry = atol(start);
			start = end +1;

			end = strchr(start,',');
			if(!end)
				break;
			*end=0;
			talent_rank = atol(start);
			start = end +1;

			m_specs[spec_ind].talents[ talent_entry ] = talent_rank;
		};
	}
	m_talentSpecsCount = get_next_field.GetUInt32() % ( MAX_SPEC_COUNT + 1);
	if( m_talentSpecsCount == 0 )
		m_talentSpecsCount = 1;
	m_talentActiveSpec = get_next_field.GetUInt32() % m_talentSpecsCount;

	//load spec specific spells
	for(int spec_ind=0;spec_ind<=1;spec_ind++)
	{
		start = (char*)get_next_field.GetString();//buff;
		while(true && start) 
		{
			end = strchr(start,',');
			if(!end)break;
			*end=0;
			uint32 spell_id = atol(start);
			m_specs[spec_ind].SpecSpecificSpells.insert( spell_id );
			start = end +1;
		}
	}

	//load active glyphs
	for(int i=0;i<GLYPHS_COUNT;i++)
	{
		uint32 glyph_id = m_specs[ m_talentActiveSpec ].glyphs[ i ];
		if( !glyph_id )
			continue;
		GlyphPropertiesEntry *glyphprops = dbcGlyphPropertiesStore.LookupEntry( glyph_id );
		if( glyphprops == NULL )
			continue;
		SetUInt32Value( PLAYER_FIELD_GLYPHS_1 + i, glyph_id );
		
		//also apply the glyph effect to the player
		SpellEntry *spellInfo = dbcSpell.LookupEntry( glyphprops->SpellId ); //we already modified this spell on server loading so it must exist
		Spell *spell = SpellPool.PooledNew();
		spell->Init( this, spellInfo ,true, NULL );
		SpellCastTargets targets( GetGUID() );
		spell->prepare(&targets);
	}

	HonorHandler::RecalculateHonorFields(this);
	
	for(uint32 x=0;x<5;x++)
		BaseStats[x]=GetUInt32Value(UNIT_FIELD_STAT0+x);
  
	_setFaction();
   
	//class fixes
	switch(getClass())
	{
	case PALADIN:
		armor_proficiency|=(1<<7);//LIBRAM
		break;
	case DRUID:
		armor_proficiency|=(1<<8);//IDOL
		break;
	case SHAMAN:
		armor_proficiency|=(1<<9);//TOTEM
		break;
	case DEATHKNIGHT:
		armor_proficiency |= ( 1 << 10 );//SIGIL
		break;
	case WARLOCK:
	case HUNTER:
		_LoadPet(results[5].result);
        _LoadPetSpells(results[6].result);
	break;
	}

	if(m_session->CanUseCommand('c'))
		_AddLanguages(true);
	else
		_AddLanguages(false);

	OnlineTime	= (uint32)UNIXTIME;
	if(GetGuildId())
		SetUInt32Value(PLAYER_GUILD_TIMESTAMP, (uint32)UNIXTIME);

	SetUInt64Value( PLAYER_FIELD_KNOWN_TITLES1,				get_next_field.GetUInt64() );
	SetUInt64Value( PLAYER_FIELD_KNOWN_TITLES2,				get_next_field.GetUInt64() );

	m_name_suffix = get_next_field.GetString();

	//load weekly quests
	start = (char*)get_next_field.GetString();
	while(true)
	{
		end = strchr(start,',');
		if(!end) break;
		*end = 0;
		m_finishedWeeklies.insert(atol(start));
		start = end +1;
	}

#undef get_next_field

	// load properties

	_LoadTutorials( results[1].result );
	_LoadPlayerCooldowns( results[2].result);
	_LoadQuestLogEntry( results[3].result );
	m_ItemInterface->mLoadItemsFromDatabase( results[4].result );
	_LoadEquipmentSets( results[11].result );

	m_mailBox.Load(results[7].result);

	// SOCIAL
	if( results[8].result != NULL )			// this query is "who are our friends?"
	{
		result = results[8].result;
		do 
		{
			fields = result->Fetch();
			if( strlen( fields[1].GetString() ) )
				m_friends.insert( make_pair( fields[0].GetUInt32(), strdup_local(fields[1].GetString()) ) );
			else
				m_friends.insert( make_pair( fields[0].GetUInt32(), (char*)NULL) );

		} while (result->NextRow());
	}

	if( results[9].result != NULL )			// this query is "who has us in their friends?"
	{
		result = results[9].result;
		do 
		{
			m_hasFriendList.insert( result->Fetch()[0].GetUInt32() );
		} while (result->NextRow());
	}

	if( results[10].result != NULL )		// this query is "who are we ignoring"
	{
		result = results[10].result;
		do 
		{
			m_ignores.insert( result->Fetch()[0].GetUInt32() );
		} while (result->NextRow());
	}

	// END SOCIAL

	m_session->FullLogin(this);
	m_session->m_loggingInPlayer=NULL;

	if( !isAlive() )
	{
		//we should have a corpse but what if it got deleted form DB ?
		Corpse *mcorpse = objmgr.GetCorpseByOwner(GetLowGUID());
		if( mcorpse )
			m_myCorpseLowGuid = mcorpse->GetLowGUID();
	}
	//Set current RestState
	else if( m_isResting) 		// We are resting at an inn , turn on Zzz
		ApplyPlayerRestState(true);

	// check for multiple gems with unique-equipped flag
	uint32 count;
	uint32 uniques[64];
	int nuniques=0;

	for( uint32 x = EQUIPMENT_SLOT_START; x < EQUIPMENT_SLOT_END; ++x )
	{
		ItemInterface *itemi = GetItemInterface();
		Item * it = itemi->GetInventoryItem(x);

		if( it != NULL )
		{
			for( count=0; count<it->GetSocketsCount(); count++ )
			{
				EnchantmentInstance *ei = it->GetEnchantment(2+count);

				if (ei && ei->Enchantment && ei->Enchantment->GemEntry)
				{
					ItemPrototype * ip = ItemPrototypeStorage.LookupEntry(ei->Enchantment->GemEntry);
					
					if (ip && ip->Flags & ITEM_FLAG_UNIQUE_EQUIP && 
						itemi->IsEquipped(ip->ItemId))
					{
						int i;

						for (i=0; i<nuniques; i++)
						{
							if (uniques[i] == ip->ItemId)
							{
								// found a duplicate unique-equipped gem, remove it
								it->RemoveEnchantment(2+count);
								break;
							}
						}

						if (i == nuniques) // not found
							uniques[nuniques++] = ip->ItemId;
					}
				}
			}
		}
	}
#if GM_STATISTICS_UPDATE_INTERVAL > 0 
	if( GetSession()->HasPermissions() )
	{
		//create data holder
		m_GM_statistics = new GM_statistics;
		//just in case this is first login we create db persistent holder also, if not first then this query is ignored
		CharacterDatabase.Execute("Insert ignore into gm_activity_statistics (guid,name,acc) values (%u,'%s',%u)",getPlayerInfo()->guid,getPlayerInfo()->name,getPlayerInfo()->acct);
		m_GM_statistics->next_afk_update = getMSTime();
		m_GM_statistics->last_pos_x = GetPositionX();
		m_GM_statistics->last_pos_y = GetPositionY();
	}
#endif
}

void Player::SetPersistentInstanceId(Instance *pInstance)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(pInstance == NULL)
	{ 
		return;
	}

	// Skip this handling for flagged GMs.
	if(bGMTagOn)
	{ 
		return;
	}

	// Bind instance to "my" group.
	if(m_playerInfo && m_playerInfo->m_Group && pInstance->m_creatorGroup == 0)
		pInstance->m_creatorGroup = m_playerInfo->m_Group->GetID();

	// Skip handling for non-persistent instances.
	if(!IS_PERSISTENT_INSTANCE(pInstance))
	{ 
		return;
	}

	// Set instance for group if not done yet.
	if( m_playerInfo && m_playerInfo->m_Group )
	{
		uint32 group_saved_instance_id = m_playerInfo->m_Group->GetSavedInstance( pInstance->m_mapId, pInstance->instance_difficulty );
		if( group_saved_instance_id == GROUP_SAVED_INSTANCE_MISSING || !sInstanceMgr.InstanceExists( pInstance->m_mapId, group_saved_instance_id ))
		{
			m_playerInfo->m_Group->AddSavedInstance( pInstance->m_mapId,pInstance->instance_difficulty,pInstance->m_instanceId);
			m_playerInfo->m_Group->SaveToDB();
		}
	}

	// Instance is not saved yet (no bosskill)
	if(!pInstance->m_persistent)
	{
		SetPersistentInstanceId(pInstance->m_mapId, pInstance->instance_difficulty, 0);
	}
	// Set instance id to player.
	else
	{
		SetPersistentInstanceId(pInstance->m_mapId, pInstance->instance_difficulty, pInstance->m_instanceId);
	}
	sLog.outDebug("Added player %u to saved instance %u on map %u.", (uint32)GetGUID(), pInstance->m_instanceId, pInstance->m_mapId);
}

void Player::SetPersistentInstanceId(uint32 mapId, uint32 difficulty, uint32 instanceId)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(mapId >= NUM_MAPS || difficulty >= NUM_INSTANCE_MODES || m_playerInfo == NULL)
	{ 
		return;
	}
	m_playerInfo->savedInstanceIdsLock.Acquire();
	PlayerInstanceMap::iterator itr = m_playerInfo->savedInstanceIds[difficulty].find(mapId);
	if(itr == m_playerInfo->savedInstanceIds[difficulty].end())
	{
		if(instanceId != 0)
			m_playerInfo->savedInstanceIds[difficulty].insert(PlayerInstanceMap::value_type(mapId, instanceId));
	}
	else
	{
		if(instanceId == 0)
			m_playerInfo->savedInstanceIds[difficulty].erase(itr);
		else
			(*itr).second = instanceId;
	}
	m_playerInfo->savedInstanceIdsLock.Release();
	CharacterDatabase.Execute("REPLACE INTO `instanceids` (`playerguid`, `mapid`, `mode`, `instanceid`) VALUES ( %u, %u, %u, %u )", m_playerInfo->guid, mapId, difficulty, instanceId);
}

void Player::RolloverHonor()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 current_val = (g_localTime.tm_year << 16) | g_localTime.tm_yday;
	if( current_val != m_honorRolloverTime )
	{
		m_honorRolloverTime = current_val;
		m_honorYesterday = m_honorToday;
		m_killsYesterday = m_killsToday;
		m_honorToday = m_killsToday = 0;
	}
}

void Player::_LoadQuestLogEntry(QueryResult * result)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	QuestLogEntry *entry;
	Quest *quest;
	Field *fields;
	uint32 questid;
	uint32 baseindex;
	
	// clear all fields
	for(int i = 0; i < 25; ++i)
	{
		baseindex = PLAYER_QUEST_LOG_1_1 + (i * QUEST_LOG_SIZE);
		SetUInt32Value(baseindex + 0, 0);
		SetUInt32Value(baseindex + 1, 0);
		SetUInt32Value(baseindex + 2, 0);
		SetUInt32Value(baseindex + 3, 0);
	}

	int slot = 0;

	if(result)
	{
		do 
		{
			fields = result->Fetch();
			questid = fields[1].GetUInt32();
			quest = QuestStorage.LookupEntry(questid);
			slot = fields[2].GetUInt32();
			ASSERT(slot != -1);
			
			// remove on next save if bad quest
			if(!quest)
			{
				m_removequests.insert(questid);
				continue;
			}
			if(m_questlog[slot] != 0)
				continue;
			
			entry = new QuestLogEntry;
			entry->Init(quest, this, slot);
			entry->LoadFromDB(fields);
			entry->UpdatePlayerFields();

		} while(result->NextRow());
	}
}

QuestLogEntry* Player::GetQuestLogForEntry(uint32 quest)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	for(int i = 0; i < 25; ++i)
	{
		if(m_questlog[i] == ((QuestLogEntry*)0x00000001))
			m_questlog[i] = NULL;

		if(m_questlog[i] != NULL)
		{
			if(m_questlog[i]->GetQuest() && m_questlog[i]->GetQuest()->id == quest)
			{ 
				return m_questlog[i];
			}
		}
	}
	return NULL;
	/*uint32 x = PLAYER_QUEST_LOG_1_1;
	uint32 y = 0;
	for(; x < PLAYER_VISIBLE_ITEM_1_CREATOR && y < 25; x += 3, y++)
	{
		if(m_uint32Values[x] == quest)
			return m_questlog[y];
	}
	return NULL;*/
}

void Player::SetQuestLogSlot(QuestLogEntry *entry, uint32 slot)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	m_questlog[slot] = entry;
}

void Player::AddToWorld()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	FlyCheat = false;
	m_setflycheat=false;
	// check transporter
	if(m_TransporterGUID && m_CurrentTransporter)
	{
		SetPosition(m_CurrentTransporter->GetPositionX() + m_TransporterX,
			m_CurrentTransporter->GetPositionY() + m_TransporterY,
			m_CurrentTransporter->GetPositionZ() + m_TransporterZ,
			GetOrientation(), false);
	}

	// If we join an invalid instance and get booted out, this will prevent our stats from doubling :P
	if(IsInWorld())
	{ 
		return;
	}

	m_beingPushed = true;
	Object::AddToWorld();
	
	// Add failed.
	if(m_mapMgr == NULL)
	{
		// eject from instance
		m_beingPushed = false;
		EjectFromInstance();
		return;
	}

	if(m_session)
		m_session->SetInstance( m_mapMgr->GetInstanceID() );

	if( GetMapMgr()->instance_difficulty > INSTANCE_MODE_DUNGEON_NORMAL )
	{
		sStackWolrdPacket( data, SMSG_INSTANCE_DIFFICULTY, 15 );
		if( GetMapMgr()->instance_difficulty == INSTANCE_MODE_RAID_25_MAN )
		{
			data << (uint32)(1);
			data << (uint32)(0);
		}
		else if( GetMapMgr()->instance_difficulty == INSTANCE_MODE_RAID_10_MAN )
		{
			data << (uint32)(0);
			data << (uint32)(0);
		}
		else if( GetMapMgr()->instance_difficulty == INSTANCE_MODE_RAID_10_MAN_HEROIC )
		{
			data << (uint32)(0);
			data << (uint32)(1);	//no idea - you can put whatever you want, it has no effect
		}
		else if( GetMapMgr()->instance_difficulty == INSTANCE_MODE_RAID_25_MAN_HEROIC )
		{
			data << (uint32)(1);	//max is 2 and above values have same effect
			data << (uint32)(1);	//no idea - you can put whatever you want, it has no effect
		}
		else if( GetMapMgr()->instance_difficulty == INSTANCE_MODE_DUNGEON_HEROIC )
		{
			data << (uint32)(3);	//max is 2 and above values have same effect
			data << (uint32)(0);	//no idea - you can put whatever you want, it has no effect
		}
		else if( GetMapMgr()->instance_difficulty == INSTANCE_MODE_DUNGEON_NORMAL )
		{
			data << (uint32)(2);	//max is 2 and above values have same effect
			data << (uint32)(0);	//no idea - you can put whatever you want, it has no effect
		}
		GetSession()->SendPacket(&data);
	}

	sStackWolrdPacket( data, SMSG_BINDPOINTUPDATE, 21);
    data << m_bind_pos_x;
    data << m_bind_pos_y;
    data << m_bind_pos_z;
    data << m_bind_mapid;
    data << m_bind_zoneid;
    GetSession()->SendPacket( &data );

	//resend all auras or else player will not see them
	sEventMgr.AddEvent(SafeUnitCast(this),&Unit::SendAllAurasToPlayer,GetLowGUID(),EVENT_SEND_AURAS_TO_PLAYER,AURA_SEND_DELAY,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	sEventMgr.AddEvent(SafePlayerCast(this),&Player::SendTimeSyncRequest,EVENT_SEND_AURAS_TO_PLAYER,AURA_SEND_DELAY,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
}

void Player::AddToWorld(MapMgr * pMapMgr)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	FlyCheat = false;
	m_setflycheat=false;
	// check transporter
	if(m_TransporterGUID && m_CurrentTransporter)
	{
		SetPosition(m_CurrentTransporter->GetPositionX() + m_TransporterX,
			m_CurrentTransporter->GetPositionY() + m_TransporterY,
			m_CurrentTransporter->GetPositionZ() + m_TransporterZ,
			GetOrientation(), false);
	}

	// If we join an invalid instance and get booted out, this will prevent our stats from doubling :P
	if(IsInWorld())
	{ 
		return;
	}

	m_beingPushed = true;
	Object::AddToWorld(pMapMgr);

	// Add failed.
	if(m_mapMgr == NULL)
	{
		// eject from instance
		m_beingPushed = false;
		EjectFromInstance();
		return;
	}

	if(m_session)
		m_session->SetInstance( m_mapMgr->GetInstanceID() );

	//relocate item events. I wonder if there are any 
}

void Player::OnPrePushToWorld()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SendInitialLogonPackets();
}

void Player::OnPushToWorld()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 class_ = getClass();
	uint32 startlevel = max(sWorld.start_level,55);
	if(m_TeleportState == 2)   // Worldport Ack
		OnWorldPortAck();

	SpeedCheatReset();
	m_beingPushed = false;
	AddItemsToWorld();
	m_lockTransportVariables = false;

	// delay the unlock movement packet


	sWorld.mInWorldPlayerCount++;

	if ( m_playerInfo->lastOnline + 900 < UNIXTIME ) // did we logged out for more than 15 minutes?
		m_ItemInterface->RemoveAllConjured();

	Unit::OnPushToWorld();
   
	/*
	if(m_FirstLogin)
	{
		sHookInterface.OnFirstEnterWorld(this);
		LevelInfo * Info = objmgr.GetLevelInfo(getRace(), getClass(), sWorld.start_level);
		ApplyLevelInfo(Info, sWorld.start_level);
		m_FirstLogin = false;
	}
	*/

	if(m_FirstLogin)
	{
		sHookInterface.OnFirstEnterWorld(this);
		if(class_ == DEATHKNIGHT)
		{
			LevelInfo * Info = objmgr.GetLevelInfo(getRace(), class_, startlevel);
			ApplyLevelInfo(Info, startlevel);
		}
		else
		{
		  LevelInfo * Info = objmgr.GetLevelInfo(getRace(), class_, sWorld.start_level);
		  ApplyLevelInfo(Info, sWorld.start_level);		
		}
		m_FirstLogin = false;
	} 

	sHookInterface.OnEnterWorld(this);
	CALL_INSTANCE_SCRIPT_EVENT( m_mapMgr, OnZoneChange )( this, m_zoneId, 0 ); 
	CALL_INSTANCE_SCRIPT_EVENT( m_mapMgr, OnPlayerEnter )( this );

	if(m_TeleportState == 1)		// First world enter
		CompleteLoading();

	m_TeleportState = 0;

	if(GetTaxiState())
	{
		if( m_taxiMapChangeNode != 0 )
		{
			lastNode = m_taxiMapChangeNode;
		}

		// Create HAS to be sent before this!
		ProcessPendingUpdates();
		TaxiStart(GetTaxiPath(), 
			GetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID),
			lastNode);

		m_taxiMapChangeNode = 0;
	}

	if(flying_aura && !(m_mapId == 530 || m_mapId == 571) )
	{
		RemoveAura(flying_aura);
		flying_aura = 0;
	}
	if( m_MountSpellId )
		RemoveAura( m_MountSpellId );
	//these auras are marked as not visible but we need to resend them on map change
	for(uint32 i=MAX_AURAS;i<MAX_AURAS + MAX_PASSIVE_AURAS;i++)
		if( m_auras[i] && (m_auras[i]->m_flags & NEED_STATEIGNORE_RESEND_ON_MAPCHANGE) )
			sEventMgr.AddEvent( m_auras[i], &Aura::SendIgnoreStateAura, EVENT_SEND_PACKET_TO_PLAYER_AFTER_LOGIN, 5000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
			

	//resend all auras or else player will not see them
//	sEventMgr.AddEvent(SafeUnitCast(this),&Unit::SendAllAurasToPlayer,GetLowGUID(),EVENT_SEND_AURAS_TO_PLAYER,AURA_SEND_DELAY,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
//	sEventMgr.AddEvent(SafePlayerCast(this),&Player::SendTimeSyncRequest,EVENT_SEND_AURAS_TO_PLAYER,AURA_SEND_DELAY,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
//	SendAllAurasToPlayer( GetLowGUID() );
	SendTimeSyncRequest();

	/* send weather */
	sWeatherMgr.SendWeather(this);

	SetUInt32Value( UNIT_FIELD_HEALTH, ( load_health > m_uint32Values[UNIT_FIELD_MAXHEALTH] ? m_uint32Values[UNIT_FIELD_MAXHEALTH] : load_health ));
	SetUInt32Value( UNIT_FIELD_POWER1, ( load_mana > m_uint32Values[UNIT_FIELD_MAXPOWER1] ? m_uint32Values[UNIT_FIELD_MAXPOWER1] : load_mana ));

	if( !GetSession()->HasPermissions() )
		GetItemInterface()->CheckAreaItems(); 

#ifdef ENABLE_COMPRESSED_MOVEMENT
	//sEventMgr.AddEvent(this, &Player::EventDumpCompressedMovement, EVENT_PLAYER_FLUSH_MOVEMENT, World::m_movementCompressInterval, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	MovementCompressor->AddPlayer(this);
#endif

	if( m_mapMgr)
	{
		if( m_bg != m_mapMgr->m_battleground )
		{
			m_bg = m_mapMgr->m_battleground;
			if( m_bg )
				m_bg->PortPlayer( this, true );
		}
		SetMapId( m_mapMgr->GetMapId() );
	}
	else SetMapId( -1 );

	if( m_bg != NULL )
	{
		m_bg->OnAddPlayer( this ); // add buffs and so, must be after zone update and related aura removal
		m_bg->OnPlayerPushed( this );
	}

	z_axisposition = 0.0f;
	m_changingMaps = false;

	_EventExploration();
	UpdatePvPArea(true);
}

void Player::RemoveFromWorld()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(raidgrouponlysent)
		event_RemoveEvents(EVENT_PLAYER_EJECT_FROM_INSTANCE);

	load_health = m_uint32Values[UNIT_FIELD_HEALTH];
	load_mana = m_uint32Values[UNIT_FIELD_POWER1];

	if(m_bg)
	{
		if( BattlegroundManager.IsValidBGPointer( m_bg ) )
			m_bg->RemovePlayer(this, true);
		m_bg = NULL;
	}

	RemoveFieldSummon();

	// Cancel trade if it's active.
	Player * pTarget;
	if(mTradeTarget != 0)
	{
		pTarget = GetTradeTarget();
		if(pTarget)
			pTarget->ResetTradeVariables();
		ResetTradeVariables();
	}
	//clear buyback
	GetItemInterface()->EmptyBuyBack();
	
	for(uint32 x=0;x<4;x++)
	{
		if(m_TotemSlots[x])
			m_TotemSlots[x]->TotemExpire();
	}

	ClearSplinePackets();

	if( m_Summon )
	{
		m_Summon->GetAIInterface()->SetPetOwner(0);
		m_Summon->Remove( true, false );
		m_Summon = NULL;
	}

	if(m_SummonedObject)
	{
/*		if(m_SummonedObject->GetInstanceID() != GetInstanceID())
		{
			if( m_SummonedObject->IsGameObject() )
				sEventMgr.AddEvent(m_SummonedObject, &GameObject::Despawn, 0, EVENT_GAMEOBJECT_EXPIRE, 100, 1,0);
		}
		else
		{
			if(m_SummonedObject->GetTypeId() == TYPEID_PLAYER)
			{

			}
			else
			{
				if(m_SummonedObject->IsInWorld())
				{
					m_SummonedObject->RemoveFromWorld(true);
				}
				delete m_SummonedObject;
			}
		} */
		if( m_SummonedObject->IsGameObject() )
			sEventMgr.AddEvent( SafeGOCast(m_SummonedObject), &GameObject::Despawn, (uint32)0, EVENT_GAMEOBJECT_EXPIRE, 100, 1,0);
		m_SummonedObject = NULL;
	}
	if( DuelingWith )
	{
		EndDuel( DUEL_STATE_FINISHED );
		DuelingWith = NULL;
	}

	if(IsInWorld())
	{
		RemoveItemsFromWorld();
		Unit::RemoveFromWorld(false);
	}

	sWorld.mInWorldPlayerCount--;
#ifdef ENABLE_COMPRESSED_MOVEMENT
	MovementCompressor->RemovePlayer(this);
	m_movementBufferLock.Acquire();
	m_movementBuffer.clear();
	m_movementBufferLock.Release();
	//sEventMgr.RemoveEvents(this, EVENT_PLAYER_FLUSH_MOVEMENT);
	
#endif

	if(GetTaxiState())
		event_RemoveEvents( EVENT_PLAYER_TAXI_INTERPOLATE );

	m_changingMaps = true;
}

ScalingStatValuesEntry *GetScalingStatEntryByLevel(uint32 level)
{
	for(uint32 x=0; x < dbcScalingStatValues.GetNumRows(); x++)
	{
		ScalingStatValuesEntry * sse = dbcScalingStatValues.LookupRow(x);
		if( sse && sse->level == level )
		{ 
			return sse;
		}
	}

	return NULL;
}

// TODO: perhaps item should just have a list of mods, that will simplify code
void Player::_ApplyItemMods(Item* item, int16 slot, bool apply, bool justdrokedown /* = false */, bool skip_stat_apply /* = false  */)
{
	if (slot >= EQUIPMENT_SLOT_END)
	{ 
		return;
	}

	ASSERT( item );
	ItemPrototype* proto = item->GetProto();

	//fast check to skip mod applying if the item doesnt meet the requirements.
	if( item->GetUInt32Value( ITEM_FIELD_DURABILITY ) == 0 && item->GetUInt32Value( ITEM_FIELD_MAXDURABILITY ) && justdrokedown == false )
	{ 
		return;
	}

	//these are used by blizz to generate some mob strengths in instances. Ex : The eye : dragonlings health and dmg
	if( apply )
	{
		Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_EQUIP_ITEM,proto->ItemId,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
		item_level_sum += proto->ItemLevel;
		item_count_sum++;
//test idiot hack to make DK rune strike work with 2H weapons. Is this even correct ?
//if( proto->InventoryType == INVTYPE_2HWEAPON )
//	SetUInt64Value( PLAYER_FIELD_INV_SLOT_HEAD + (EQUIPMENT_SLOT_OFFHAND*2),  item->GetGUID() );
	}
	else
	{
		if( item_level_sum >= proto->ItemLevel )
			item_level_sum -= proto->ItemLevel;
		if( item_count_sum )
			item_count_sum--;
//if( proto->InventoryType == INVTYPE_2HWEAPON )
//	SetUInt64Value( PLAYER_FIELD_INV_SLOT_HEAD + (EQUIPMENT_SLOT_OFFHAND*2),  0 );
	}

	//check for rnd prop
	item->ApplyRandomProperties( apply );

	//Items Set check
	uint32 setid = proto->ItemSet;

	// These season pvp itemsets are interchangeable and each set group has the same
	// bonuses if you have a full set made up of parts from any of the 3 similar sets
	// you will get the highest sets bonus

	// TODO: make a config for server so they can configure which season is active season

	// * Gladiator's Battlegear
	if( setid == 701 || setid == 736 || setid == 567 )
		setid = 736;
	
	// * Gladiator's Dreadgear
	if( setid == 702 || setid == 734 || setid == 568 )
		setid = 734;

	// * Gladiator's Earthshaker
	if( setid == 703 || setid == 732 || setid == 578 )
		setid= 732;

	// * Gladiator's Felshroud
	if( setid == 704 || setid == 735 || setid == 615 )
		setid = 735;

	// * Gladiator's Investiture
	if( setid == 705 || setid == 728 || setid == 687 )
		setid = 728;

	// * Gladiator's Pursuit
	if( setid == 706 || setid == 723 || setid == 586 )
		setid = 723;

	// * Gladiator's Raiment
	if( setid == 707 || setid == 729 || setid == 581 )
		setid = 729;

	// * Gladiator's Redemption
	if( setid == 708 || setid == 725 || setid == 690 )
		setid = 725;

	// * Gladiator's Refuge
	if( setid == 709 || setid == 720 || setid == 685 )
		setid = 720;

	// * Gladiator's Regalia
	if( setid == 710 || setid == 724 || setid == 579 )
		setid = 724;

	// * Gladiator's Sanctuary
	if( setid == 711 || setid == 721 || setid == 584 )
		setid = 721;

	// * Gladiator's Thunderfist
	if( setid == 712 || setid == 733 || setid == 580 )
		setid = 733;

	// * Gladiator's Vestments
	if( setid == 713 || setid == 730 || setid == 577 )
		setid = 730;

	// * Gladiator's Vindication
	if( setid == 714 || setid == 726 || setid == 583 )
		setid = 726;

	// * Gladiator's Wartide
	if( setid == 715 || setid == 731 || setid == 686 )
		setid = 731;

	// * Gladiator's Wildhide
	if( setid == 716 || setid == 722 || setid == 585 )
		setid = 722;

	// Set
	if( setid != 0 )
	{
		ItemSetEntry* set = dbcItemSet.LookupEntry( setid );
		ASSERT( set );
		ItemSet* Set = NULL;
		SimplePointerListNode<ItemSet> *i;
		for( i = m_itemsets.begin(); i != m_itemsets.end(); i = i->Next() )
		{
			if( i->data->setid == setid )
			{   
				Set = i->data;
				break;
			}
		}

		if( apply )
		{
			if( Set == NULL ) 
			{
				Set = new ItemSet;
				if( Set == NULL )
					return;
				Set->itemscount = 1;
				Set->setid = setid;
			}
			else
				Set->itemscount++;

			if( !set->RequiredSkillID || ( _GetSkillLineCurrent( set->RequiredSkillID, true ) >= set->RequiredSkillAmt ) )
			{
				for( uint32 x=0;x<8;x++)
				{
					if( Set->itemscount==set->itemscount[x])
					{//cast new spell
						SpellEntry *info = dbcSpell.LookupEntry( set->SpellID[x] );
						Spell * spell = SpellPool.PooledNew();
						spell->Init( this, info, true, NULL );
						SpellCastTargets targets;
						targets.m_unitTarget = this->GetGUID();
						spell->prepare( &targets );
					}
				}
			}
			if( i == m_itemsets.end() )
			{
				m_itemsets.push_front( Set );
				Set = NULL;
			}
		}
		else
		{
			if( Set )
			{
				for( uint32 x = 0; x < 8; x++ )
				if( Set->itemscount == set->itemscount[x] )
					this->RemoveAura( set->SpellID[x], GetGUID() );
	   
				Set->itemscount--;
				if( Set->itemscount == 0 )
					m_itemsets.remove( i->data, 1 );
			}
		}
	}
 
	// Resistances
	//TODO: FIXME: can there be negative resistances from items?
	if( proto->FireRes )
	{
		if( apply )
			FlatResistanceModifierPos[2] += proto->FireRes;
		else
			FlatResistanceModifierPos[2] -= proto->FireRes;
		CalcResistance( 2 );
	}
		
	if( proto->NatureRes )
	{
		if( apply )
			FlatResistanceModifierPos[3] += proto->NatureRes;
		else
			FlatResistanceModifierPos[3] -= proto->NatureRes;
		CalcResistance( 3 );
	}

	if( proto->FrostRes )
	{
		if( apply )
			FlatResistanceModifierPos[4] += proto->FrostRes;
		else
			FlatResistanceModifierPos[4] -= proto->FrostRes;
		CalcResistance( 4 );	
	}

	if( proto->ShadowRes )
	{
		if( apply )
			FlatResistanceModifierPos[5] += proto->ShadowRes;
		else
			FlatResistanceModifierPos[5] -= proto->ShadowRes;
		CalcResistance( 5 );	
	}
	 
	if( proto->ArcaneRes )
	{
		if( apply )
			FlatResistanceModifierPos[6] += proto->ArcaneRes;
		else
			FlatResistanceModifierPos[6] -= proto->ArcaneRes;
		CalcResistance( 6 );
	}
	
	/* Heirloom scaling items */
	if(proto->ScalingStatsEntry != 0)
	{
		ScalingStatDistributionEntry *ssdrow = dbcScalingStatDistribution.LookupEntry( proto->ScalingStatsEntry );
		//ScalingStatValuesEntry *ssvrow = dbcScalingStatValues.LookupEntry( SSVDBCEByLevel[ getLevel() ] );
		ScalingStatValuesEntry *ssvrow = GetScalingStatEntryByLevel( MIN( getLevel(), ssdrow->maxlevel ) );
        if(ssdrow && ssvrow)
        {
			//base stats
			for(uint32 i=0;i<MAX_SSDE_COLUMN;i++)
			{
				if(ssdrow->stat[i] < 0)
					continue;
				uint32 StatType = ssdrow->stat[i];
				uint32 StatMod  = ssdrow->statmodifier[i];
				uint32 StatMultiplier = ssvrow->getssdMultiplier( proto->ScalingStatsFlag );
				int32 StatValue = StatMod*StatMultiplier/10000;
				ModifyBonuses(StatType,StatValue,apply);
			}
			//spell power
			int32 spellbonus = ssvrow->getSpellBonus(proto->ScalingStatsFlag);
			if( spellbonus != 0 )
				ModifyBonuses(SPELL_POWER,spellbonus,apply);
			//phisical resistance = armor
			int32 ssvarmor = ssvrow->getArmorMod(proto->ScalingStatsFlag);
			if( apply == false )
				ssvarmor = -ssvarmor;
		    // Add armor bonus from ArmorDamageModifier if > 0
		    if (proto->ArmorDamageModifier > 0)
				ssvarmor += uint32(proto->ArmorDamageModifier);
			if( ssvarmor != 0 )
			{
				BaseResistance[0 ] += ssvarmor;
				CalcResistance( 0 );
			}

			//dmg mods
			int32 extraDPS = ssvrow->getDPSMod(proto->ScalingStatsFlag);
			if( extraDPS != 0 )
			{
				float average = extraDPS * proto->Delay / 1000.0f;
				float scaledmindmg = 0.7f * average;
				float scaledmaxdmg = 1.3f * average;
				if( proto->InventoryType == INVTYPE_RANGED || proto->InventoryType == INVTYPE_RANGEDRIGHT || proto->InventoryType == INVTYPE_THROWN )	
				{	
					BaseRangedDamage[0] += apply ? scaledmindmg : -scaledmindmg;
					BaseRangedDamage[1] += apply ? scaledmaxdmg : -scaledmaxdmg;
				}
				else
				{
					if( slot == EQUIPMENT_SLOT_OFFHAND )
					{
						BaseOffhandDamage[0] = apply ? scaledmindmg : 0;
						BaseOffhandDamage[1] = apply ? scaledmaxdmg : 0;
					}
					else
					{
						BaseDamage[0] = apply ? scaledmindmg : 1;
						BaseDamage[1] = apply ? scaledmaxdmg : 1;
					}
				}
			}
        }
	/* Normal items */
	}
	else
	{
		// Stats
		for( int i = 0; i < 10; i++ )
		{
			int32 val = proto->Stats[i].Value;
			if( val == 0 )
				continue;
			ModifyBonuses( proto->Stats[i].Type, val, apply );
		}

		// Armor
		if( proto->Armor )
		{
			if( apply )
				BaseResistance[0 ]+= proto->Armor;  
			else  
				BaseResistance[0] -= proto->Armor;
			CalcResistance( 0 );
		}

		// Damage
		if( proto->Damage[0].Min )
		{
			if( proto->InventoryType == INVTYPE_RANGED || proto->InventoryType == INVTYPE_RANGEDRIGHT || proto->InventoryType == INVTYPE_THROWN )	
			{	
				BaseRangedDamage[0] += apply ? proto->Damage[0].Min : -proto->Damage[0].Min;
				BaseRangedDamage[1] += apply ? proto->Damage[0].Max : -proto->Damage[0].Max;
			}
			else
			{
				if( slot == EQUIPMENT_SLOT_OFFHAND )
				{
					BaseOffhandDamage[0] = apply ? proto->Damage[0].Min : 0;
					BaseOffhandDamage[1] = apply ? proto->Damage[0].Max : 0;
				}
				else
				{
					BaseDamage[0] = apply ? proto->Damage[0].Min : 1;
					BaseDamage[1] = apply ? proto->Damage[0].Max : 1;
				}
			}
		}
	} // end of the scalingstats else branch

	// Misc
	if( apply )
	{
		// Apply all enchantment bonuses
		item->ApplyEnchantmentBonuses();

		for( int k = 0; k < 5; k++ )
		{
			// stupid fucked dbs
			if( item->GetProto()->Spells[k].Id == 0 )
				continue;

			if( item->GetProto()->Spells[k].Trigger == 1 )
			{
				SpellEntry* spells = dbcSpell.LookupEntry( item->GetProto()->Spells[k].Id );
				if( spells )
				{
					if( spells->RequiredShapeShift )
					{
						AddShapeShiftSpell( spells->Id );
						continue;
					}

					Spell *spell = SpellPool.PooledNew();
					spell->Init( this, spells ,true, NULL );
					SpellCastTargets targets;
					targets.m_unitTarget = this->GetGUID();
					spell->castedItemId = item->GetEntry();
					spell->prepare( &targets );
				}

			}
			else if( item->GetProto()->Spells[k].Trigger == 2 )
			{
				SpellEntry* sp = dbcSpell.LookupEntryForced( item->GetProto()->Spells[k].Id );
				if( sp )
				{
					ProcTriggerSpell *ts = new ProcTriggerSpell(sp);
					ts->spellId = item->GetProto()->Spells[k].Id;
					ts->origId = 0;	//is this bad ? Yes it is ! Self proc is bad !
					ts->procChance = 5;
					ts->caster = this->GetGUID();
					ts->procFlags = PROC_ON_MELEE_ATTACK;
					m_procSpells.push_front( ts );	
				}
			}
		}
	}
	else
	{
		// Remove all enchantment bonuses
		item->RemoveEnchantmentBonuses();
		for( int k = 0; k < 5; k++ )
		{
			if( item->GetProto()->Spells[k].Trigger == 1 )
			{
				SpellEntry* spells = dbcSpell.LookupEntry( item->GetProto()->Spells[k].Id );
				if( spells->RequiredShapeShift )
					RemoveShapeShiftSpell( spells->Id );
				else
					RemoveAura( item->GetProto()->Spells[k].Id ); 
			}
			else if( item->GetProto()->Spells[k].Trigger == 2 )
			{
				// Debug: i changed this a bit the if was not indented to the for
				// so it just set last one to deleted looks like unintended behaviour
				// because you can just use end()-1 to remove last so i put the if
				// into the for
				CommitPointerListNode<ProcTriggerSpell> *itr;
				for(itr = m_procSpells.begin();itr != m_procSpells.end();itr = itr->Next() )
					if( itr->data->spellId == item->GetProto()->Spells[k].Id && itr->data->deleted == false )
					{
						//m_procSpells.erase(i);
						itr->data->deleted = true;
						break;
					}
			}
		}
	}
	
	if( !apply ) // force remove auras added by using this item
	{
		for(uint32 k = 0; k < MAX_POSITIVE_AURAS; ++k)
		{
			Aura* m_aura = this->m_auras[k];
			if( m_aura != NULL && m_aura->m_castedItemId && m_aura->m_castedItemId == proto->ItemId )
				m_aura->Remove();
		}
	}

	if( !skip_stat_apply )
		UpdateStats();
}


void Player::SetMovement(uint8 pType)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(13);

	switch(pType)
	{
	case MOVE_ROOT:
		{
			data.SetOpcode(SMSG_FORCE_MOVE_ROOT);
			data << GetNewGUID();
			data << m_PositionUpdateCounter++;
			m_currentMovement = MOVE_ROOT;
		}break;
	case MOVE_UNROOT:
		{
			data.SetOpcode(SMSG_FORCE_MOVE_UNROOT);
			data << GetNewGUID();
			data << m_PositionUpdateCounter++;
			m_currentMovement = MOVE_UNROOT;
		}break;
	case MOVE_WATER_WALK:
		{
			m_setwaterwalk=true;
			data.SetOpcode(SMSG_MOVE_WATER_WALK);
			data << GetNewGUID();
			data << m_PositionUpdateCounter++;
		}break;
	case MOVE_LAND_WALK:
		{
			m_setwaterwalk=false;
			data.SetOpcode(SMSG_MOVE_LAND_WALK);
			data << GetNewGUID();
			data << m_PositionUpdateCounter++;
		}break;
	case MOVE_FEATHER_FALL:
		{
			data.SetOpcode(SMSG_MOVE_FEATHER_FALL);
			data << GetNewGUID();
			data << m_PositionUpdateCounter++;
			m_safe_fall = true;
		}break;
	case MOVE_NORMAL_FALL:
		{
			data.SetOpcode(SMSG_MOVE_NORMAL_FALL);
			data << GetNewGUID();
			data << m_PositionUpdateCounter++;
			m_safe_fall = false;
		}break;
	case MOVE_HOVER:
		{
			m_setwaterwalk=true;
			data.SetOpcode(SMSG_MOVE_SET_HOVER);
			data << GetNewGUID();
			data << m_PositionUpdateCounter++;
			m_safe_fall = true;
		}break;
	case MOVE_NO_HOVER:
		{
			m_setwaterwalk=false;
			data.SetOpcode(SMSG_MOVE_UNSET_HOVER);
			data << GetNewGUID();
			data << m_PositionUpdateCounter++;
			m_safe_fall = false;
		}break;
	default:break;
	}

	if(data.size() > 0)
		SendMessageToSet(&data, true);
}

void Player::SetPlayerSpeed(uint8 SpeedType, float value)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	/*WorldPacket data(18);
	data << GetNewGUID();
	data << m_PositionUpdateCounter++;
	
	if(SpeedType == RUN)			// nfi what this is.. :/
		data << uint8(1);

	data << value;*/
	WorldPacket data(50);
	/*if(SpeedType==FLY)
	{
		data << GetNewGUID();
		data << m_PositionUpdateCounter++;

		if(SpeedType == RUN)			// nfi what this is.. :/
			data << uint8(1);

		data << value;
	}
	else
	{
		data << GetNewGUID();
		data << uint32(0);
		data << uint8(0);
		data << uint32(getMSTime());
		data << GetPosition();
		data << m_position.o;
		data << uint32(0);
		data << value;
	}*/
	if( SpeedType != SWIMBACK )
	{
		data << GetNewGUID();
		data << m_PositionUpdateCounter++;
		if( SpeedType == RUN )
			data << uint8(1);

		data << value;
	}
	else
	{
		data << GetNewGUID();
		data << uint32(0);
		data << uint8(0);
		data << uint32(getMSTime());
		data << GetPosition();
		data << m_position.o;
		data << uint32(0);
		data << value;
	}
	
	switch(SpeedType)
	{
	case RUN:
		{
			if(value == m_lastRunSpeed)
			{ 
				return;
			}

			data.SetOpcode(SMSG_FORCE_RUN_SPEED_CHANGE);
			m_runSpeed = value;
			m_lastRunSpeed = value;
		}break;
	case RUNBACK:
		{
			if(value == m_lastRunBackSpeed)
			{ 
				return;
			}

			data.SetOpcode(SMSG_FORCE_RUN_BACK_SPEED_CHANGE);
			m_backWalkSpeed = value;
			m_lastRunBackSpeed = value;
		}break;
	case SWIM:
		{
			if(value == m_lastSwimSpeed)
			{ 
				return;
			}

			data.SetOpcode(SMSG_FORCE_SWIM_SPEED_CHANGE);
			m_swimSpeed = value;
			m_lastSwimSpeed = value;
		}break;
	case SWIMBACK:
		{
			if(value == m_lastBackSwimSpeed)
				break;

			data.SetOpcode(SMSG_FORCE_SWIM_BACK_SPEED_CHANGE);
			m_backSwimSpeed = value;
			m_lastBackSwimSpeed = value;
		}break;
	case FLY:
		{
			if(value == m_lastFlySpeed)
			{ 
				return;
			}

			data.SetOpcode(SMSG_FORCE_FLIGHT_SPEED_CHANGE);
			m_flySpeed = value;
			m_lastFlySpeed = value;
		}break;
	default:
	return;
	}

	//other clients use our speed to estimate our next position
	SendMessageToSet(&data , true);
///	GetSession()->SendPacket( &data );
}

//!!!!!!!!!!! seems like last uint32 if it is not 1 then it will disable the menu !
void Player::SendDungeonDifficulty()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	sStackWolrdPacket( data, MSG_SET_DUNGEON_DIFFICULTY, 15);
	data << (uint32)dungeon_difficulty;
    data << (uint32)0x1;
//    data << (uint32)InGroup();
//	data << (uint32)IsGroupLeader();	//maybe just group leader should see this menu ?
	data << (uint32)1;	//enable / disable menu ?
    GetSession()->SendPacket(&data);
}

//!!!!!!!!!!! seems like last uint32 if it is not 1 then it will disable the menu !
void Player::SendRaidDifficulty()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	sStackWolrdPacket( data, MSG_SET_RAID_DIFFICULTY, 15);
	data << (uint32)raid_difficulty;
    data << (uint32)0x1;
//    data << (uint32)InGroup();
//	data << (uint32)IsGroupLeader();	//maybe just group leader should see this menu ?
	data << (uint32)0;	//enable / disable menu ?
    GetSession()->SendPacket(&data);
}

void Player::RepopRequestedPlayer()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( m_myCorpseLowGuid != 0 )
	{
		GetSession()->SendNotification( NOTIFICATION_MESSAGE_NO_PERMISSION );
		return;
	}

	if( m_CurrentTransporter != NULL )
	{
		m_CurrentTransporter->RemovePlayer( this );
		m_CurrentTransporter = NULL;
		m_TransporterGUID = 0;

		ResurrectPlayer();
		RepopAtGraveyard( GetPositionX(), GetPositionY(), GetPositionZ(), GetMapId() );
		return;
	}

	MapInfo * pMapinfo;

	sEventMgr.RemoveEvents( this, EVENT_PLAYER_FORECED_RESURECT ); //in case somebody resurrected us before this event happened

	// Set death state to corpse, that way players will lose visibility
	setDeathState( CORPSE );
	
	// Update visibility, that way people wont see running corpses :P
	UpdateVisibility(); //-> if we remove ourself here then will they see the updates we are setting here ?

	// If we're in battleground, remove the skinnable flag.. has bad effects heheh
	RemoveFlag( UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE );

	bool corpse = (m_bg != NULL) ? m_bg->CreateCorpse( this ) : true;

	if( corpse )
		CreateCorpse();
	
	SetUInt32Value( UNIT_FIELD_HEALTH, 1 );

	//not sure if required at all. Found it in 3.3.2 client
//	sStackWolrdPacket(data,SMSG_PRE_RESURRECT,12);
//	data << this->GetNewGUID();
//	GetSession()->SendPacket( &data );

	//8326 --for all races but ne,  9036 20584--ne
	SpellCastTargets tgt;
	tgt.m_unitTarget=this->GetGUID();
   
	if(getRace()==RACE_NIGHTELF)
	{
		SpellEntry *inf=dbcSpell.LookupEntry(20584);
		Spell*sp=SpellPool.PooledNew();
		sp->Init(this,inf,true,NULL);
		sp->prepare(&tgt);
		inf=dbcSpell.LookupEntry(9036);
		sp=SpellPool.PooledNew();
		sp->Init(this,inf,true,NULL);
		sp->prepare(&tgt);
	}
	else
	{
	
		SpellEntry *inf=dbcSpell.LookupEntry(8326);
		Spell*sp=SpellPool.PooledNew();
		sp->Init(this,inf,true,NULL);
		sp->prepare(&tgt);
	}

	StopMirrorTimer(0);
	StopMirrorTimer(1);
	StopMirrorTimer(2);
	
	SetFlag(PLAYER_FLAGS, PLAYER_FLAG_DEATH_WORLD_ENABLE);

	SetMovement(MOVE_UNROOT);
	SetMovement(MOVE_WATER_WALK);

	if( corpse )
	{
		SpawnCorpseBody();

		// Send Spirit Healer Location 
		WorldPacket data( SMSG_DEATH_RELEASE_LOC, 16 );
		data << m_mapId << m_position;
		m_session->SendPacket( &data );

		// Corpse reclaim delay 
		if( getLevel() > 10 )
		{
			WorldPacket data2( SMSG_CORPSE_RECLAIM_DELAY, 4 );
			data2 << (uint32)( CORPSE_RECLAIM_TIME_MS );
			GetSession()->SendPacket( &data2 );
		}
	}

	pMapinfo = WorldMapInfoStorage.LookupEntry( GetMapId() );
	if( pMapinfo != NULL )
	{
		if( HAS_GRAVEYARDS_MAP( pMapinfo ) )
		{
			RepopAtGraveyard( GetPositionX(), GetPositionY(), GetPositionZ(), GetMapId() );
		}
		else
		{
			RepopAtGraveyard( pMapinfo->repopx, pMapinfo->repopy, pMapinfo->repopz, pMapinfo->repopmapid );
		}
	}
	else
	{
		RepopAtGraveyard( GetPositionX(), GetPositionY(), GetPositionZ(), GetMapId() );
	}
	
	if( m_myCorpseLowGuid != 0 )
	{
		Corpse *mcorpse = objmgr.GetCorpse( m_myCorpseLowGuid );
		if( mcorpse ) 
		{
			if( getLevel() > 10 )
				mcorpse->ResetDeathClock();
		}
		else 
			m_myCorpseLowGuid = 0;
	}
	
	if( pMapinfo )
	{
		switch( pMapinfo->mapid )
		{
			case 550: //The Eye
			case 552: //The Arcatraz
			case 553: //The Botanica
			case 554: //The Mechanar
				ResurrectPlayer();
				break;
		}
	}
}

void Player::ResurrectPlayer()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE

	//who cares ?
//	sStackWolrdPacket(data1,SMSG_DEATH_RELEASE_LOC,20);
//	data1 << uint32(0xFFFFFFFF) << float(0) << float(0) << float(0);
//	GetSession()->SendPacket( &data1 );

	sEventMgr.RemoveEvents(this,EVENT_PLAYER_FORECED_RESURECT); //in case somebody resurected us before this event happened
	if( m_resurrectHealth )
		SetUInt32Value( UNIT_FIELD_HEALTH, (uint32)min( m_resurrectHealth, m_uint32Values[UNIT_FIELD_MAXHEALTH] ) );
	if( m_resurrectMana )
		SetUInt32Value( UNIT_FIELD_POWER1, (uint32)min( m_resurrectMana, m_uint32Values[UNIT_FIELD_MAXPOWER1] ) );

	m_resurrectHealth = m_resurrectMana = 0;

	SpawnCorpseBones();
	
	if(getRace()==RACE_NIGHTELF)
	{
		RemoveAura(20584);
		RemoveAura(9036);
	}else
		RemoveAura(8326);

	RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_DEATH_WORLD_ENABLE);
	setDeathState(ALIVE);
	UpdateVisibility();
	if ( m_resurrecter && IsInWorld()
		//don't pull players inside instances with this trick. Also fixes the part where you were able to double item bonuses
		&& m_resurrectInstanceID == GetInstanceID() 
		)
	{
		SafeTeleport( m_resurrectMapId, m_resurrectInstanceID, m_resurrectPosition );
	}
	m_resurrecter = 0;
	SetMovement(MOVE_LAND_WALK);
	UpdatePvPArea( true );	//!!this will remove PVP flag in friendly places. Really helps some noobs that want to end farming

	//Zack : shit on grill. So auras should be removed on player death instead of making this :P
	//wee can afford this bullshit atm since auras are lost uppon death -> no immunities
	for(uint32 i = 0; i < 7; i++)
		SchoolImmunityList[i]=0;
}

void Player::KillPlayer()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(getDeathState() != ALIVE) //You can't kill what has no life.
	{ 
		return;
	}
		
	setDeathState(JUST_DIED);

	// Battleground stuff
	if(m_bg)
		m_bg->HookOnPlayerDeath(this);

	EventDeath();
	//could not find the what filters this but there are multiple cases for this. Ex arena, BG ...
	Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_DEATH,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_DEATH_AT_MAP,GetMapId(),ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_DEATH,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	//hmmm there are variations for these. Not sure how to filter them, like 10 man raid / 10 man instance ? Arent't these the same ?
	Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_DEATH_IN_DUNGEON,((GetMapMgr()->GetMapInfo()->playerlimit+4)/5)*5,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	
	m_session->OutPacket(SMSG_CANCEL_COMBAT);
	m_session->OutPacket(SMSG_CANCEL_AUTO_REPEAT);

	SetMovement(MOVE_ROOT);

	StopMirrorTimer(0);
	StopMirrorTimer(1);
	StopMirrorTimer(2);

	SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED); //player death animation, also can be used with DYNAMIC_FLAGS <- huh???
	SetUInt32Value( UNIT_DYNAMIC_FLAGS, 0x00 );
	if(this->getClass() == WARRIOR) //rage resets on death
		SetUInt32Value(UNIT_FIELD_POWER2, 0);

	sHookInterface.OnDeath(this);
}

void Player::CreateCorpse()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	Corpse *pCorpse;
	uint32 _uf, _pb, _pb2, _cfb1, _cfb2;

	//remove other corpse
	Corpse * c = objmgr.GetCorpseByOwner( GetLowGUID() );
	// !!!! wtf ? corpse and event holder are not in sync ? mapmanager got deleted while corpse was not removed from it ?
	if( c && c->IsInWorld() && c->GetMapCell() )
	{
		sEventMgr.AddEvent(c, &Corpse::SpawnBones, EVENT_CORPSE_SPAWN_BONES, 1, 1, 0);
	}

	if(!this->bCorpseCreateable)
	{
		bCorpseCreateable = true;   // for next time
		return; // no corpse allowed!
	}

	pCorpse = objmgr.CreateCorpse();
	pCorpse->SetInstanceID(GetInstanceID());
	pCorpse->Create(this, GetMapId(), GetPositionX(),
		GetPositionY(), GetPositionZ(), GetOrientation());

	_uf = GetUInt32Value(UNIT_FIELD_BYTES_0);
	_pb = GetUInt32Value(PLAYER_BYTES);
	_pb2 = GetUInt32Value(PLAYER_BYTES_2);

	uint8 race	   = (uint8)(_uf);
	uint8 skin	   = (uint8)(_pb);
	uint8 face	   = (uint8)(_pb >> 8);
	uint8 hairstyle  = (uint8)(_pb >> 16);
	uint8 haircolor  = (uint8)(_pb >> 24);
	uint8 facialhair = (uint8)(_pb2);

	_cfb1 = ((0x00) | (race << 8) | (0x00 << 16) | (skin << 24));
	_cfb2 = ((face) | (hairstyle << 8) | (haircolor << 16) | (facialhair << 24));

	pCorpse->SetZoneId( GetZoneId() );
	pCorpse->SetUInt32Value( CORPSE_FIELD_BYTES_1, _cfb1 );
	pCorpse->SetUInt32Value( CORPSE_FIELD_BYTES_2, _cfb2 );
	pCorpse->SetUInt32Value( CORPSE_FIELD_FLAGS, 4 );
	pCorpse->SetUInt32Value( CORPSE_FIELD_DISPLAY_ID, GetUInt32Value(UNIT_FIELD_DISPLAYID) );

	if(m_bg)
	{
		// remove our lootable flags
		RemoveFlag(UNIT_DYNAMIC_FLAGS, U_DYN_FLAG_LOOTABLE);
		RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);
		
		loot.gold = 0;

		pCorpse->generateLoot();
		if(bShouldHaveLootableOnCorpse)
		{
			pCorpse->SetUInt32Value(CORPSE_FIELD_DYNAMIC_FLAGS, 1); // sets it so you can loot the plyr
		}
		else
		{
			// hope this works
			pCorpse->SetUInt32Value(CORPSE_FIELD_FLAGS, 60);
		}

		// now that our corpse is created, don't do it again
		bShouldHaveLootableOnCorpse = false;
	}
	else
	{
		pCorpse->loot.gold = 0;
	}

	uint32 iDisplayID = 0;
	uint16 iIventoryType = 0;
	uint32 _cfi = 0;
	Item * pItem;
	for (int8 i = 0; i < EQUIPMENT_SLOT_END; i++)
	{
		if(( pItem = GetItemInterface()->GetInventoryItem(i)) != 0)
		{
			iDisplayID = pItem->GetProto()->DisplayInfoID;
			iIventoryType = (uint16)pItem->GetProto()->InventoryType;

			_cfi =  (uint16(iDisplayID)) | (iIventoryType)<< 24;
			pCorpse->SetUInt32Value(CORPSE_FIELD_ITEM + i,_cfi);
		}
	}
	//save corpse in db for future use
	pCorpse->SaveToDB();
}

void Player::SpawnCorpseBody()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	Corpse *pCorpse;

	pCorpse = objmgr.GetCorpseByOwner(this->GetLowGUID());
	if( pCorpse == NULL )
		return;
	if( !pCorpse->IsInWorld() )
	{
		if(bShouldHaveLootableOnCorpse && pCorpse->GetUInt32Value(CORPSE_FIELD_DYNAMIC_FLAGS) != 1)
			pCorpse->SetUInt32Value(CORPSE_FIELD_DYNAMIC_FLAGS, 1); // sets it so you can loot the plyr

		if(m_mapMgr == 0)
			pCorpse->AddToWorld();
		else
			pCorpse->PushToWorld(m_mapMgr);
	}
	m_myCorpseLowGuid = pCorpse->GetLowGUID();
}

void Player::SpawnCorpseBones()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	Corpse *pCorpse;
	pCorpse = objmgr.GetCorpseByOwner(GetLowGUID());
	m_myCorpseLowGuid = 0;
	if(pCorpse && pCorpse->GetMapCell())
	{
		if (pCorpse->IsInWorld() && pCorpse->GetCorpseState() == CORPSE_STATE_BODY)
		{
			if( pCorpse->GetInstanceID() != GetInstanceID() )
			{
				//let the other eventmanager make the changes to avoid thread concurency
				sEventMgr.AddEvent(pCorpse, &Corpse::SpawnBones, EVENT_CORPSE_SPAWN_BONES, 100, 1,0);
				objmgr.RemoveCorpse( pCorpse ); //holy leaking shit
			}
			else
				pCorpse->SpawnBones();
		}
		else
		{
			//Cheater!
		}
	}
}

void Player::DeathDurabilityLoss(double percent)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	m_session->OutPacket(SMSG_DURABILITY_DAMAGE_DEATH);
	uint32 pDurability;
	uint32 pMaxDurability;
	int32 pNewDurability;
	Item * pItem;

	for (int8 i = 0; i < EQUIPMENT_SLOT_END; i++)
	{
		if((pItem = GetItemInterface()->GetInventoryItem(i)) != 0)
		{
			pMaxDurability = pItem->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
			pDurability =  pItem->GetUInt32Value(ITEM_FIELD_DURABILITY);
			if(pDurability)
			{
				pNewDurability = (uint32)(pMaxDurability*percent);
				pNewDurability = (pDurability - pNewDurability);
				if(pNewDurability < 0) 
					pNewDurability = 0;

				if(pNewDurability <= 0) 
					ApplyItemMods(pItem, i, false, true);

				pItem->SetUInt32Value(ITEM_FIELD_DURABILITY,(uint32)pNewDurability);
				pItem->m_isDirty = true;
			}
		}
	}
}

void Player::RepopAtGraveyard(float ox, float oy, float oz, uint32 mapid)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
   
	bool first = true;
	//float closestX = 0, closestY = 0, closestZ = 0, closestO = 0;
	StorageContainerIterator<GraveyardTeleport> * itr;

	LocationVector src(ox, oy, oz);
	LocationVector dest(0, 0, 0, 0);
	LocationVector temp;
	float closest_dist = 999999.0f;
	float dist;

	if(m_bg && m_bg->HookHandleRepop(this))
	{
		return;
	}
	else
	{
//		uint32 areaid = sInstanceMgr.GetMap(mapid)->GetAreaID(ox,oy);
	    uint32 areaid = sTerrainMgr.GetAreaID( mapid, ox, oy, 0.0f );
		AreaTable * at = dbcArea.LookupEntry(areaid);
		if(!at) 
		{ 
			return;
		}

		//uint32 mzone = ( at->ZoneId ? at->ZoneId : at->AreaId);

		itr = GraveyardStorage.MakeIterator();
		while(!itr->AtEnd())
		{
			GraveyardTeleport *pGrave = itr->Get();
			if((pGrave->MapId == mapid && pGrave->FactionID == GetTeam() || pGrave->MapId == mapid && pGrave->FactionID == 3)
				|| (pGrave->MapId == mapid && pGrave->FactionID == GetTeam() || pGrave->MapId == mapid && pGrave->FactionID == 3))
			{
				temp.ChangeCoords(pGrave->X, pGrave->Y, pGrave->Z);
				dist = src.DistanceSq(temp);
				if( first || dist < closest_dist )
				{
					first = false;
					closest_dist = dist;
					dest = temp;
				}
			}

			if(!itr->Inc())
				break;
		}
		itr->Destruct();
	}

	if(sHookInterface.OnRepop(this) && dest.x != 0 && dest.y != 0 && dest.z != 0)
	{
		SafeTeleport(mapid, 0, dest);
	}


//	//correct method as it works on official server, and does not require any damn sql
//	//no factions! no zones! no sqls! 1word: blizz-like
//	float closestX , closestY , closestZ ;
//	uint32 entries=sWorldSafeLocsStore.GetNumRows();
//	GraveyardEntry*g;
//	uint32 mymapid=mapid
//	float mx=ox,my=oy;
//	float last_distance=9e10;
//
//	for(uint32 x=0;x<entries;x++)
//	{
//		g=sWorldSafeLocsStore.LookupEntry(x);
//		if(g->mapid!=mymapid)continue;
//		float distance=(mx-g->x)*(mx-g->x)+(my-g->y)*(my-g->y);
//		if(distance<last_distance)
//		{
//			closestX=g->x;
//			closestY=g->y;
//			closestZ=g->z;
//			last_distance=distance;
//		}
//	
//	
//	}
//	if(last_distance<1e10)
//#endif
}

void Player::JoinedChannel(Channel *c)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( c != NULL )
		m_channels.insert(c);
}

void Player::LeftChannel(Channel *c)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( c != NULL )
		m_channels.erase(c);
}

void Player::CleanupChannels()
{
	set<Channel *>::iterator i;
	Channel * c;
	for(i = m_channels.begin(); i != m_channels.end();)
	{
		c = *i;
		++i;
		
		c->Part(this);
	}
}

void Player::SendInitialActions()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(SMSG_ACTION_BUTTONS, PLAYER_ACTION_BUTTON_SIZE + 1);
	data << uint8(1);	// some bool - 0 or 1. seems to work both ways
	data.append( (char*)&mActions[0], PLAYER_ACTION_BUTTON_SIZE );
	m_session->SendPacket(&data);
}

//we receive the values inversed from the packet. If we change that then all players loose the bars
void Player::setAction(uint8 button, uint16 action, uint8 type, uint8 misc)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( button >= PLAYER_ACTION_BUTTON_COUNT )
		return; //packet hack to crash server
	mActions[button].Action = action;
	mActions[button].Type = type;
	mActions[button].Misc = misc;
}

//Groupcheck
bool Player::IsGroupMember(Player *plyr)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(m_playerInfo->m_Group != NULL)
	{ 
		return m_playerInfo->m_Group->HasMember(plyr->m_playerInfo);
	}

	return false;
}

int32 Player::GetOpenQuestSlot()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	for (uint32 i = 0; i < 25; ++i)
		if (m_questlog[i] == NULL)
		{ 
			return i;
		}

	return -1;
}

void Player::AddToFinishedQuests(uint32 quest_id)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//maybe that shouldn't be an assert, but i'll leave it for now
	//ASSERT(m_finishedQuests.find(quest_id) == m_finishedQuests.end());
	//Removed due to crash
	//If it failed though, then he's probably cheating. 
	if (m_finishedQuests.find(quest_id) != m_finishedQuests.end())
	{ 
		return;
	}

	m_finishedQuests.insert(quest_id);
}

bool Player::HasFinishedQuest(uint32 quest_id)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	return (m_finishedQuests.find(quest_id) != m_finishedQuests.end());
}


bool Player::GetQuestRewardStatus(uint32 quest_id)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	return HasFinishedQuest(quest_id);
}

//From Mangos Project
void Player::_LoadTutorials(QueryResult * result)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	
	if(result)
	{
		 Field *fields = result->Fetch();
		 for (int iI=0; iI<8; iI++) 
			 m_Tutorials[iI] = fields[iI + 1].GetUInt32();
	}
	tutorialsDirty = false;
}

void Player::_SaveTutorials(QueryBuffer * buf)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(tutorialsDirty)
	{
		if(buf == NULL)
			CharacterDatabase.Execute("REPLACE INTO tutorials VALUES('%u','%u','%u','%u','%u','%u','%u','%u','%u')", GetLowGUID(), m_Tutorials[0], m_Tutorials[1], m_Tutorials[2], m_Tutorials[3], m_Tutorials[4], m_Tutorials[5], m_Tutorials[6], m_Tutorials[7]);
		else
			buf->AddQuery("REPLACE INTO tutorials VALUES('%u','%u','%u','%u','%u','%u','%u','%u','%u')", GetLowGUID(), m_Tutorials[0], m_Tutorials[1], m_Tutorials[2], m_Tutorials[3], m_Tutorials[4], m_Tutorials[5], m_Tutorials[6], m_Tutorials[7]);

		tutorialsDirty = false;
	}
}

uint32 Player::GetTutorialInt(uint32 intId )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	ASSERT( intId < 8 );
	return m_Tutorials[intId];
}

void Player::SetTutorialInt(uint32 intId, uint32 value)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(intId >= 8)
	{ 
		return;
	}

	ASSERT( (intId < 8) );
	m_Tutorials[intId] = value;
	tutorialsDirty = true;
}

//Player stats calculation for saving at lvl up, etc
/*void Player::CalcBaseStats()
{//SafePlayerCast( this )->getClass() == HUNTER ||
	//TODO take into account base stats at create
	uint32 AP, RAP;
	//Save AttAck power
	if(getClass() == ROGUE || getClass() == HUNTER)
	{
		AP = GetBaseUInt32Value(UNIT_FIELD_STAT0) + GetBaseUInt32Value(UNIT_FIELD_STAT1);
		RAP = (GetBaseUInt32Value(UNIT_FIELD_STAT1) * 2);
		SetBaseUInt32Value(UNIT_FIELD_ATTACK_POWER, AP);
		SetBaseUInt32Value(UNIT_FIELD_RANGED_ATTACK_POWER, RAP);
	}
	else
	{
		AP = (GetBaseUInt32Value(UNIT_FIELD_STAT0) * 2);
		RAP = (GetBaseUInt32Value(UNIT_FIELD_STAT1) * 2);
		SetBaseUInt32Value(UNIT_FIELD_ATTACK_POWER, AP);
		SetBaseUInt32Value(UNIT_FIELD_RANGED_ATTACK_POWER, RAP);
	}

}*/

void Player::UpdateHit(int32 hit)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
   /*std::list<Affect*>::iterator i;
	Affect::ModList::const_iterator j;
	Affect *aff;
	uint32 in = hit;
	for (i = GetAffectBegin(); i != GetAffectEnd(); i++)
	{
		aff = *i;
		for (j = aff->GetModList().begin();j != aff->GetModList().end(); j++)
		{
			Modifier mod = (*j);
			if ((mod.GetType() == SPELL_AURA_MOD_HIT_CHANCE))
			{
				SpellEntry *spellInfo = sSpellStore.LookupEntry(aff->GetSpellId());
				if (this->canCast(spellInfo))
					in += mod.GetAmount();
			}
		}
	}
	SetHitFromSpell(in);*/
}

float Player::GetDefenseChance(uint32 opLevel)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	float chance;

	chance = float( _GetSkillLineCurrent( SKILL_DEFENSE, true ) - ( opLevel * 5.0f ) );
	chance += CalcRating( PLAYER_RATING_MODIFIER_DEFENCE );	//this is skill and not a PCT value
	chance = floorf( chance ) * 0.04f; // defense skill is treated as an integer on retail

	return chance;
}

#define BASE_BLOCK_CHANCE 5.0f
#define BASE_PARRY_CHANCE 5.0f

// Gets dodge chances before defense skill is applied
float Player::GetDodgeChance()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 pClass = (uint32)getClass();
	float chance;
	
	// base dodge chance
	chance = baseDodge[pClass];

	// dodge from agility
	chance += float( GetUInt32Value( UNIT_FIELD_STAT1 ) / dodgeRatio[getLevel()-1][pClass] );

	// dodge from dodge rating
	chance += CalcRating( PLAYER_RATING_MODIFIER_DODGE );

	// dodge from spells
	chance += GetDodgeFromSpell();

	return MIN(max( chance, 0.0f ),PLAYER_DODGE_CAP_PCT); // make sure we dont have a negative chance
}

// Gets block chances before defense skill is applied
// Assumes the caller will check for shields
float Player::GetBlockChance()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	float chance;

	// base block chance
	chance = BASE_BLOCK_CHANCE;
	
	// block rating
	chance += CalcRating( PLAYER_RATING_MODIFIER_BLOCK );
	
	// block chance from spells
	chance += GetBlockFromSpell();

	return max( chance, 0.0f ); // make sure we dont have a negative chance
}

// Get parry chances before defense skill is applied
float Player::GetParryChance()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	float chance;

	// base parry chance
	chance = BASE_PARRY_CHANCE;
	
	// parry rating
	chance += CalcRating( PLAYER_RATING_MODIFIER_PARRY );

	// parry chance from spells
	chance += GetParryFromSpell();

	return MIN(max( chance, 0.0f ),PLAYER_PARRY_CAP_PCT); // make sure we dont have a negative chance
}

void Player::UpdateChances()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 pClass = (uint32)getClass();
	uint32 pLevel = (getLevel() > PLAYER_LEVEL_CAP_DBC) ? PLAYER_LEVEL_CAP_DBC : getLevel();

	float tmp = 0;
	float defence_contribution = 0;

	// avoidance from defense skill
	defence_contribution = GetDefenseChance( pLevel );

	// dodge
	tmp = GetDodgeChance();
	tmp += defence_contribution;
	tmp = min( tmp, 95.0f );
	SetFloatValue( PLAYER_DODGE_PERCENTAGE, tmp );

	// block
	Item* it = this->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
	if( it != NULL && it->GetProto()->InventoryType == INVTYPE_SHIELD )
	{
		tmp = GetBlockChance();
		tmp += defence_contribution;
		tmp = min( tmp, 95.0f );
	}
	else
		tmp = 0.0f;

	SetFloatValue( PLAYER_BLOCK_PERCENTAGE, tmp );

	//parry
	tmp = GetParryChance();
	tmp += defence_contribution;
	tmp = min( tmp, 95.0f );
	SetFloatValue( PLAYER_PARRY_PERCENTAGE, tmp );

	//critical
	gtFloat* baseCrit = dbcMeleeCritBase.LookupRow(pClass-1);
	gtFloat* CritPerAgi = dbcMeleeCrit.LookupRow(pLevel - 1 + (pClass-1)*100);

	if( !baseCrit || !CritPerAgi )
	{
		sLog.outDebug("Could not find dbcMeleeCritBase or dbcMeleeCrit entry ");
		return;
	}
	tmp = 100*(baseCrit->val + GetUInt32Value( UNIT_FIELD_STAT1 ) * CritPerAgi->val);

	Item* tItemMelee = GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
	Item* tItemRanged = GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_RANGED );

	float melee_bonus = 0;
	float ranged_bonus = 0;

	//-1 = any weapon
	SimplePointerListNode<WeaponModifier> *itr;
	for(itr = tocritchance.begin(); itr != tocritchance.end(); itr = itr->Next() )
	{
		WeaponModifier *wpm = itr->data;
		if( wpm->wclass == -1 || ( tItemMelee != NULL && ( ( 1 << tItemMelee->GetProto()->SubClass ) & wpm->subclass ) ) )
			melee_bonus += wpm->value;
		if( wpm->wclass == -1 || ( tItemRanged != NULL && ( ( 1 << tItemRanged->GetProto()->SubClass ) & wpm->subclass ) ) )
			ranged_bonus += wpm->value;
	}
	weapon_target_armor_pct_ignore = 1;
	for(itr = ignore_armor_pct.begin(); itr != ignore_armor_pct.end(); itr = itr->Next() )
		if( itr->data->wclass == -1 || ( tItemMelee != NULL && ( 1 << tItemMelee->GetProto()->SubClass & itr->data->subclass ) ) )
			weapon_target_armor_pct_ignore += itr->data->value;

	float cr = tmp + CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT ) + melee_bonus;
	SetFloatValue( PLAYER_CRIT_PERCENTAGE, min( cr, 95.0f ) );

	float rcr = tmp + CalcRating( PLAYER_RATING_MODIFIER_RANGED_CRIT ) + ranged_bonus;
	SetFloatValue( PLAYER_RANGED_CRIT_PERCENTAGE, min( rcr, 95.0f ) );

	gtFloat* SpellCritBase  = dbcSpellCritBase.LookupRow(pClass-1);
	gtFloat* SpellCritPerInt = dbcSpellCrit.LookupRow(pLevel - 1 + (pClass-1)*100);

	spellcritperc = 100*(SpellCritBase->val + GetUInt32Value( UNIT_FIELD_INTELLECT ) * SpellCritPerInt->val) +
		this->GetSpellCritFromSpell() +
		this->CalcRating( PLAYER_RATING_MODIFIER_SPELL_CRIT );
	UpdateChanceFields();
}

void Player::UpdateChanceFields()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// Update spell crit values in fields
	for(uint32 i = 0; i < 7; ++i)
	{
		SetFloatValue(PLAYER_SPELL_CRIT_PERCENTAGE1 + i, SpellCritChanceSchool[i]+spellcritperc);
	}
}

void Player::ModAttackSpeed( int32 mod, ModType type )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( mod == 0 )
	{ 
		return;
	}

	if( mod > 0 )
		m_attack_speed[ type ] *= 1.0f + ( ( float )mod / 100.0f );
	else
		m_attack_speed[ type ] /= 1.0f + ( ( float )( - mod ) / 100.0f );
}

void Player::UpdateAttackSpeed()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 speed = 2000;
	Item *weap ;

	if( GetShapeShift() == FORM_CAT )
	{
		speed = 1000;
	}
	else if( GetShapeShift() == FORM_BEAR || GetShapeShift() == FORM_DIREBEAR )
	{
		speed = 2500;
	}
	else if( !disarmed )//regular
	{
		weap = GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND) ;
		if( weap != NULL )
			speed = weap->GetProto()->Delay;
	}
	SetUInt32Value( UNIT_FIELD_BASEATTACKTIME,
		( uint32 )( (float) speed / ( m_attack_speed[ MOD_MELEE ] * ( 1.0f + CalcRating( PLAYER_RATING_MODIFIER_MELEE_HASTE ) / 100.0f ) ) ) );
	
	weap = GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
	if( weap != NULL && weap->GetProto()->Class == ITEM_CLASS_WEAPON )
	{
		speed = weap->GetProto()->Delay;
		SetUInt32Value( UNIT_FIELD_BASEATTACKTIME_1,
			( uint32 )( (float) speed / ( m_attack_speed[ MOD_MELEE ] * ( 1.0f + CalcRating( PLAYER_RATING_MODIFIER_MELEE_HASTE ) / 100.0f ) ) ) );
	}
	else
		SetUInt32Value( UNIT_FIELD_BASEATTACKTIME_1, 2000 );
	
	weap = GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_RANGED );
	if( weap != NULL )
	{
		speed = weap->GetProto()->Delay;
		SetUInt32Value( UNIT_FIELD_RANGEDATTACKTIME,
			( uint32 )( (float) speed / ( m_attack_speed[ MOD_RANGED ] * ( 1.0f + CalcRating( PLAYER_RATING_MODIFIER_RANGED_HASTE ) / 100.0f ) ) ) );
	}
	else
		SetUInt32Value( UNIT_FIELD_RANGEDATTACKTIME, 2000 );
}

void Player::UpdateStats()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
   
	UpdateAttackSpeed();

	// formulas from wowwiki

	int32 AP = 0;
	int32 RAP = 0;

	uint32 str = GetUInt32Value(UNIT_FIELD_STAT0);
	uint32 agi = GetUInt32Value(UNIT_FIELD_STAT1);
	uint32 lev = getLevel();

	// Attack power
	uint32 cl = getClass();   
	switch (cl)
	{
	case DRUID:
		AP = str * 2 - 20;

		// lev * 2 and lev * 3 bonus to attack power is already added elsewhere (in Cat Form and Bear From aura i think)
		/* if( GetShapeShift() == FORM_CAT )
			AP += agi + lev * 2;

		if( GetShapeShift() == FORM_BEAR || GetShapeShift() == FORM_DIREBEAR )
			AP += lev * 3; */
		if (GetShapeShift() == FORM_CAT)
			AP += agi; 

		break;

	case ROGUE:
		//AP = lev * 2 + str + agi - 20;
		//RAP = lev + agi * 2 - 20;
		//AP = str + agi - 20;
		AP = lev * 2 + str + agi - 20;
		RAP = lev + agi - 10;
		break;

	case HUNTER:
		//AP = lev* 2 + str + agi - 20;
		//RAP = (lev + agi)*2 - 20;
		AP = lev * 2 + str + agi - 20;
		RAP = lev * 2 + agi - 10;
		break;

	case SHAMAN:
		AP = (lev+str)*2 + agi - 20;
		break;
		
	case PALADIN:
		//AP = lev * 3 + str * 2 - 20;
		//AP = str * 2 - 20;
		AP = lev * 3 + str * 2 - 20;
		break;

	case DEATHKNIGHT:
		//AP = lev * 3 + str * 2 - 20;
		//AP = str * 2 - 20;
		AP = lev * 3 + str * 2 - 20;
		break;

	case WARRIOR:
		//AP = lev * 3 + str * 2 - 20;
		//RAP = (lev+agi)*2 - 20;
		//AP = str * 2 - 20;
		AP = lev * 3 + str * 2 - 20;
		RAP = lev + agi - 10;
		break;

	default://mage,priest,warlock
		AP = str - 10;
	}

	/* modifiers */
//	RAP += int32(float(float(m_rap_mod_pct) * float(float(m_uint32Values[UNIT_FIELD_STAT3]) / 100.0f)));

	if( RAP < 0 )RAP = 0;
	if( AP < 0 )AP = 0;

	int32 FeralAP = 0;
	if( IsInFeralForm() )
	{
		Item* MainHandWeapon = GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
		if( MainHandWeapon != NULL && MainHandWeapon->GetProto()->Class == ITEM_CLASS_WEAPON )
		{
			//calc DPS
			float speed = MainHandWeapon->GetProto()->Delay / 1000.0f;
			float avgDMG = 0;
			avgDMG += (MainHandWeapon->GetProto()->Damage[0].Min + MainHandWeapon->GetProto()->Damage[0].Max)/2.0f;
			avgDMG += (MainHandWeapon->GetProto()->Damage[1].Min + MainHandWeapon->GetProto()->Damage[1].Max)/2.0f;
			float DPS = avgDMG / speed;
			if( DPS > 54.3f )
				FeralAP += (int32)((DPS - 54.3f)*14.0f);
		}
		//rare case. Might happen with fist weapons
		Item* OffHandWeapon = GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
		if( OffHandWeapon != NULL && OffHandWeapon->GetProto()->Class == ITEM_CLASS_WEAPON )
		{
			//calc DPS
			float speed = OffHandWeapon->GetProto()->Delay / 1000.0f;
			float avgDMG = 0;
			avgDMG += (OffHandWeapon->GetProto()->Damage[0].Min + OffHandWeapon->GetProto()->Damage[0].Max)/2.0f;
			avgDMG += (OffHandWeapon->GetProto()->Damage[1].Min + OffHandWeapon->GetProto()->Damage[1].Max)/2.0f;
			float DPS = avgDMG / speed;
			if( DPS > 54.3f )
				FeralAP += (int32)((DPS - 54.3f)*14.0f);
		}
	}

	SetUInt32Value( UNIT_FIELD_ATTACK_POWER, AP + FeralAP );
	SetUInt32Value( UNIT_FIELD_RANGED_ATTACK_POWER, RAP ); 

	/*
	//zack : disabled, but stats already contain level specific stamina bonus
	int32 hpdelta = 128;
	int32 manadelta = 128;
	LevelInfo* lvlinfo = objmgr.GetLevelInfo( this->getRace(), this->getClass(), lev );

	if( lvlinfo != NULL )
	{
		hpdelta = lvlinfo->Stat[2] * 10;
		manadelta = lvlinfo->Stat[3] * 15;
	}

	lvlinfo = objmgr.GetLevelInfo( this->getRace(), this->getClass(), 1 );

	if( lvlinfo != NULL )
	{
		hpdelta -= lvlinfo->Stat[2] * 10;
		manadelta -= lvlinfo->Stat[3] * 15;
	}*/

	int32 hp = GetUInt32Value( UNIT_FIELD_BASE_HEALTH );

	int32 stat_bonus = GetUInt32Value( UNIT_FIELD_STAMINA );	//contains all the mods including level specific stamina and base stamina
//	if ( stat_bonus < 0 )
//		stat_bonus = 0; //cannot have negative stats
	int32 bonus = stat_bonus * 10 + m_healthfromspell + m_healthfromitems;

//	int32 res = hp + bonus + hpdelta;
	int32 res = hp + bonus;
	int32 oldmaxhp = GetUInt32Value( UNIT_FIELD_MAXHEALTH );

	if( res < hp ) 
		res = hp;
	SetUInt32Value( UNIT_FIELD_MAXHEALTH, res );

	if( ( int32 )GetUInt32Value( UNIT_FIELD_HEALTH ) > res )
		SetUInt32Value( UNIT_FIELD_HEALTH, res );
	else if( ( cl == DRUID) && ( GetShapeShift() == FORM_BEAR || GetShapeShift() == FORM_DIREBEAR ) )
	{
		res = float2int32( ( float )GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * ( float )GetUInt32Value( UNIT_FIELD_HEALTH ) / float( oldmaxhp ) );
		SetUInt32Value( UNIT_FIELD_HEALTH, res );
	}

	if( cl != WARRIOR && cl != ROGUE )
	{
		// MP
		int32 mana = GetUInt32Value( UNIT_FIELD_BASE_MANA );

		stat_bonus = GetUInt32Value( UNIT_FIELD_INTELLECT );	//contains all the mods including level specific stamina and base stamina
//		if ( stat_bonus < 0 )
//			stat_bonus = 0; //avoid of having negative mana
		bonus = stat_bonus * 15 + m_manafromspell + m_manafromitems ;

//		res = mana + bonus + manadelta;
		res = mana + bonus;
		if( res < mana )
			res = mana;	
		SetUInt32Value(UNIT_FIELD_MAXPOWER1, res);

		if((int32)GetUInt32Value(UNIT_FIELD_POWER1)>res)
			SetUInt32Value(UNIT_FIELD_POWER1,res);

		//Manaregen
		const static float BaseRegen[80] = {0.034965f, 0.034191f, 0.033465f, 0.032526f, 0.031661f, 0.031076f, 0.030523f, 0.029994f, 0.029307f, 0.028661f, 0.027584f, 0.026215f, 0.025381f, 0.024300f, 0.023345f, 0.022748f, 0.021958f, 0.021386f, 0.020790f, 0.020121f, 0.019733f, 0.019155f, 0.018819f, 0.018316f, 0.017936f, 0.017576f, 0.017201f, 0.016919f, 0.016581f, 0.016233f, 0.015994f, 0.015707f, 0.015464f, 0.015204f, 0.014956f, 0.014744f, 0.014495f, 0.014302f, 0.014094f, 0.013895f, 0.013724f, 0.013522f, 0.013363f, 0.013175f, 0.012996f, 0.012853f, 0.012687f, 0.012539f, 0.012384f, 0.012233f, 0.012113f, 0.011973f, 0.011859f, 0.011714f, 0.011575f, 0.011473f, 0.011342f, 0.011245f, 0.011110f, 0.010999f, 0.010700f, 0.010522f, 0.010290f, 0.010119f, 0.009968f, 0.009808f, 0.009651f, 0.009553f, 0.009445f, 0.009327f, 0.0093f, 0.0092f, 0.0091f, 0.009f, 0.0089f, 0.0088f, 0.0087f, 0.0086f, 0.0085f, 0.0084f };
		uint32 Spirit = GetUInt32Value( UNIT_FIELD_STAT4 );
		uint32 Intellect = GetUInt32Value( UNIT_FIELD_STAT3 );
		uint32 level = getLevel();
		if(level > 80) 
			level = 80;
		float amt = ( 0.001f + sqrt((float)Intellect) * Spirit * BaseRegen[level-1] )*PctPowerRegenModifier[POWER_TYPE_MANA];
//		SetFloatValue(UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER,(amt+m_ModInterrMRegen));
//		SetFloatValue(UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER,(amt*m_ModInterrMRegenPCT/100.0f+m_ModInterrMRegen*0.2f));
		//something makes the client regenerate mana faster then the server. Maybe because values are expected to be in seconds instead 2 seconds ?
		SetFloatValue(UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER,(amt+m_ModInterrMRegen)/2);
		SetFloatValue(UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER,(amt*m_ModInterrMRegenPCT/100.0f+m_ModInterrMRegen*0.2f)/2);
	}

	// Spell haste rating
//	float haste = 1.0f + CalcRating( PLAYER_RATING_MODIFIER_SPELL_HASTE ) / 100.0f;
	float haste = CalcRating( PLAYER_RATING_MODIFIER_SPELL_HASTE ) / 100.0f;
	if( haste != SpellHasteRatingBonus )
	{
		float value = GetFloatValue( UNIT_MOD_CAST_SPEED ) + SpellHasteRatingBonus - haste; // remove previous mod and apply current
		
		SetFloatValue( UNIT_MOD_CAST_SPEED, value );
		SpellHasteRatingBonus = haste;	// keep value for next run
	}


	// Shield Block
	Item* shield = GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
	if( shield != NULL && shield->GetProto()->InventoryType == INVTYPE_SHIELD )
	{
		int32 block_multiplier = 100 + m_modblockabsorbvaluePCT;
		if( block_multiplier < 100 )
			block_multiplier = 100;

		int32 blockable_damage = ( shield->GetProto()->Block + m_modblockvaluefromspells + str / 2 ) * block_multiplier / 100 ;
		SetUInt32Value( PLAYER_SHIELD_BLOCK, blockable_damage );
	}
	else
	{
		SetUInt32Value( PLAYER_SHIELD_BLOCK, 0 );
	}

	// Expertise
	// Expertise is somewhat tricky. Expertise on items is expertise "rating" where as "expertise"
	// on the character sheet is the rating modified by a factor. The bonus % this value gives is
	// actually the "rating" modified by another factor.
	// eg. 100 expertise rating from items
	// 100 / 3.92 = 25 expertise
	// 100 / 15.77 = 6.3% reduced dodge/parry chances
	SetUInt32Value( PLAYER_EXPERTISE, (uint32) CalcRating( PLAYER_RATING_MODIFIER_EXPERTISE ) ); // value displayed in char sheet
	//SetUInt32Value( PLAYER_RATING_MODIFIER_EXPERTISE2, GetUInt32Value( PLAYER_RATING_MODIFIER_EXPERTISE ) );

	UpdateChances();
	CalcDamage();
}

uint32 Player::SubtractRestXP(uint32 amount)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(GetUInt32Value(UNIT_FIELD_LEVEL) >= GetUInt32Value(PLAYER_FIELD_MAX_LEVEL))		// Save CPU, don't waste time on this if you've reached max_level
		amount = 0;

	int32 restAmount = m_restAmount - (amount << 1);									// remember , we are dealing with xp without restbonus, so multiply by 2

	if( restAmount < 0)
		m_restAmount = 0;
	else
		m_restAmount = restAmount;

	Log.Debug("REST","Subtracted %d rest XP to a total of %d", amount, m_restAmount);
	UpdateRestState();																	// Update clients interface with new values.
	return amount;
}

void Player::AddCalculatedRestXP(uint32 seconds)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// At level one, players will all start in the normal tier. 
	// When a player rests in a city or at an inn they will gain rest bonus at a very slow rate. 
	// Eight hours of rest will be needed for a player to gain one "bubble" of rest bonus. 
	// At any given time, players will be able to accumulate a maximum of 30 "bubbles" worth of rest bonus which 
	// translates into approximately 1.5 levels worth of rested play (before your character returns to normal rest state).
	// Thanks to the comforts of a warm bed and a hearty meal, players who rest or log out at an Inn will 
	// accumulate rest credit four times faster than players logged off outside of an Inn or City. 
	// Players who log out anywhere else in the world will earn rest credit four times slower.
	// http://www.worldofwarcraft.com/info/basics/resting.html


	// Define xp for a full bar ( = 20 bubbles)
	uint32 xp_to_lvl = uint32(lvlinfo->XPToNextLevel);

	// get RestXP multiplier from config.
	float bubblerate = sWorld.getRate(RATE_RESTXP);

	// One bubble (5% of xp_to_level) for every 8 hours logged out.
	// if multiplier RestXP (from ascent.config) is f.e 2, you only need 4hrs/bubble.
	uint32 rested_xp = uint32(0.05f * xp_to_lvl * ( seconds / (3600 * ( 8 / bubblerate))));

	// if we are at a resting area rest_XP goes 4 times faster (making it 1 bubble every 2 hrs)
	if (m_isResting)
		rested_xp <<= 2;

	// Add result to accumulated rested XP
	m_restAmount += uint32(rested_xp);

	// and set limit to be max 1.5 * 20 bubbles * multiplier (1.5 * xp_to_level * multiplier)
	if (m_restAmount > xp_to_lvl + (uint32)((float)( xp_to_lvl >> 1 ) * bubblerate ))
		m_restAmount = xp_to_lvl + (uint32)((float)( xp_to_lvl >> 1 ) * bubblerate );

	Log.Debug("REST","Add %d rest XP to a total of %d, RestState %d", rested_xp, m_restAmount,m_isResting);

	// Update clients interface with new values.
	UpdateRestState();
}

void Player::UpdateRestState()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(m_restAmount && GetUInt32Value(UNIT_FIELD_LEVEL) < GetUInt32Value(PLAYER_FIELD_MAX_LEVEL))
		m_restState = RESTSTATE_RESTED;
	else
		m_restState = RESTSTATE_NORMAL;

	// Update RestState 100%/200%
	SetUInt32Value(PLAYER_BYTES_2, ((GetUInt32Value(PLAYER_BYTES_2) & 0x00FFFFFF) | (m_restState << 24)));

	//update needle (weird, works at 1/2 rate)
	SetUInt32Value(PLAYER_REST_STATE_EXPERIENCE, m_restAmount >> 1);
}

void Player::ApplyPlayerRestState(bool apply)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(apply)
	{
		m_restState = RESTSTATE_RESTED;
		m_isResting = true;
		SetFlag(PLAYER_FLAGS, PLAYER_FLAG_RESTING);	//put zzz icon
	}
	else
	{
		m_isResting = false;
		RemoveFlag(PLAYER_FLAGS,PLAYER_FLAG_RESTING);	//remove zzz icon
	}
	UpdateRestState();
}

#define CORPSE_VIEW_DISTANCE 1600 // 40*40

bool Player::CanSee(Object* obj) // * Invisibility & Stealth Detection - Partha *
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE

	//wtf bug detection ? Somehow some ppl DC and get stuck in visibility list of other players creating corrupted mem access
	if( deleted != OBJ_AVAILABLE || obj->deleted != OBJ_AVAILABLE )
	{
		return false;	//noway to see a deleted object :P
	}

	if (obj == this)
	{
	   return true;	//!! is this safe ? It will make us get pushed into visibility list thus might make us get removed from world ?
	}

	uint32 object_type = obj->GetTypeId();

	if(getDeathState() == CORPSE) // we are dead and we have released our spirit
	{
		if(object_type == TYPEID_PLAYER)
		{
			Player *pObj = SafePlayerCast(obj);

			if( m_myCorpseLowGuid )
			{
				Corpse *mcorpse = objmgr.GetCorpse( m_myCorpseLowGuid );
				if( mcorpse && mcorpse->GetDistanceSq(obj) <= CORPSE_VIEW_DISTANCE)
					return !pObj->m_isGmInvisible; // we can see all players within range of our corpse except invisible GMs
			}

			if(m_deathVision) // if we have arena death-vision we can see all players except invisible GMs
			{ 
				return !pObj->m_isGmInvisible;
			}

			return (pObj->getDeathState() == CORPSE); // we can only see players that are spirits
		}

		if( m_myCorpseLowGuid )
		{
			if( m_myCorpseLowGuid == obj->GetLowGUID() ) 
			{ 
				return true;
			}

			Corpse *mcorpse = objmgr.GetCorpse( m_myCorpseLowGuid );
			if( mcorpse && mcorpse->GetDistanceSq(obj) <= CORPSE_VIEW_DISTANCE)
				return true; // we can see everything within range of our corpse
		}

		if(m_deathVision) // if we have arena death-vision we can see everything
		{ 
			return true;
		}

		if(object_type == TYPEID_UNIT)
		{
			Unit *uObj = SafeUnitCast(obj);

			return uObj->IsSpiritHealer(); // we can't see any NPCs except spirit-healers
		}

		return false;
	}
	//------------------------------------------------------------------

	if (!(m_phase & obj->m_phase)) //What you can't see, you can't see, no need to check things further.
		return false;

	if( obj->IsUnit() && obj->GetUInt64Value( UNIT_FIELD_CREATEDBY ) == GetGUID() )
		return true; //we can see our own creations always

	switch(object_type) // we are alive or we haven't released our spirit yet
	{			
		case TYPEID_PLAYER:
			{
				Player *pObj = SafePlayerCast(obj);

				if(pObj->m_invisible) // Invisibility - Detection of Players
				{
					if(pObj->getDeathState() == CORPSE)
						return bGMTagOn; // only GM can see players that are spirits

					if(GetGroup() && pObj->GetGroup() == GetGroup() // can see invisible group members except when dueling them
							&& DuelingWith != pObj)
						return true;

					if(pObj->stalkedby == GetGUID()) // Hunter's Mark / MindVision is visible to the caster
					{ 
						return true;
					}

					if(m_invisDetect[INVIS_FLAG_NORMAL] < 1 // can't see invisible without proper detection
							|| pObj->m_isGmInvisible) // can't see invisible GM
						return bGMTagOn; // GM can see invisible players

					if( pObj->GetUInt64Value( UNIT_FIELD_CREATEDBY ) == GetGUID() )
						return true; //we can see our own creations alwa
				}

				if( m_invisible && pObj->m_invisDetect[m_invisFlag] < 1 ) // Invisible - can see those that detect, but not others
				{ 
					return m_isGmInvisible;
				}

				if(pObj->IsStealth()) // Stealth Detection (  I Hate Rogues :P  )
				{
					if(GetGroup() && pObj->GetGroup() == GetGroup() // can see stealthed group members except when dueling them
							&& DuelingWith != pObj)
						return true;

					if(pObj->stalkedby == GetGUID()) // Hunter's Mark / MindVision is visible to the caster
					{ 
						return true;
					}

					if(isInFront(pObj)) // stealthed player is in front of us
					{
						// Detection Range = 5yds + (Detection Skill - Stealth Skill)/5
#define STEALTH_DETECTION_FROM_LEVEL 0.25f	//at level 80 we should see like 30 yards away ?
//						if(getLevel() < PLAYER_LEVEL_CAP_BLIZZLIKE)
							detectRange = 5.0f + getLevel()*STEALTH_DETECTION_FROM_LEVEL + 0.2f * (float)(GetStealthDetectBonus() - pObj->GetStealthLevel());
//						else
//							detectRange = 75.0f + 0.2f * (float)(GetStealthDetectBonus() - pObj->GetStealthLevel());
						// Hehe... stealth skill is increased by 5 each level and detection skill is increased by 5 each level too.
						// This way, a level 70 should easily be able to detect a level 4 rogue (level 4 because that's when you get stealth)
						//	detectRange += 0.2f * ( getLevel() - pObj->getLevel() );
						if(detectRange < 1.0f) detectRange = 1.0f; // Minimum Detection Range = 1yd
					}
					else // stealthed player is behind us
					{
						if(GetStealthDetectBonus() > 1000) return true; // immune to stealth
						else detectRange = 0.0f;
					}

					detectRange += GetFloatValue(UNIT_FIELD_BOUNDINGRADIUS); // adjust range for size of player
					detectRange += pObj->GetFloatValue(UNIT_FIELD_BOUNDINGRADIUS); // adjust range for size of stealthed player
					//sLog.outString( "Player::CanSee(%s): detect range = %f yards (%f ingame units), cansee = %s , distance = %f" , pObj->GetName() , detectRange , detectRange * detectRange , ( GetDistance2dSq(pObj) > detectRange * detectRange ) ? "yes" : "no" , GetDistanceSq(pObj) );
					if(GetDistanceSq(pObj) > detectRange * detectRange)
						return bGMTagOn; // GM can see stealthed players
				}

				return !pObj->m_isGmInvisible;
			}
		//------------------------------------------------------------------

		case TYPEID_UNIT:
		{
				
				Unit *uObj = SafeUnitCast(obj);
					
				if(uObj->IsSpiritHealer()) // can't see spirit-healers when alive
				{ 
					return false;
				}

				if(uObj->m_invisible // Invisibility - Detection of Units
						&& m_invisDetect[uObj->m_invisFlag] < 1) // can't see invisible without proper detection
					return bGMTagOn; // GM can see invisible units
				
				if( m_invisible && uObj->m_invisDetect[m_invisFlag] < 1 ) // Invisible - can see those that detect, but not others
				{ 
					return m_isGmInvisible;
				}

				return true;
			}
		//------------------------------------------------------------------

		case TYPEID_GAMEOBJECT:
			{
				GameObject *gObj = SafeGOCast(obj);

				if(gObj->invisible) // Invisibility - Detection of GameObjects
				{
					uint64 owner = gObj->GetUInt64Value(OBJECT_FIELD_CREATED_BY);

					if(GetGUID() == owner) // the owner of an object can always see it
					{ 
						return true;
					}

					if(GetGroup())
					{
						PlayerInfo * inf = objmgr.GetPlayerInfo((uint32)owner);
						if(inf && GetGroup()->HasMember(inf))
						{ 
							return true;
						}
					}

					if(m_invisDetect[gObj->invisibilityFlag] < 1) // can't see invisible without proper detection
						return bGMTagOn; // GM can see invisible objects
				}

				return true;
			}					
		//------------------------------------------------------------------

		default:
			return true;
	}
}

void Player::AddInRangeObject(Object* pObj)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//Send taxi move if we're on a taxi
	if (m_CurrentTaxiPath && (pObj->GetTypeId() == TYPEID_PLAYER))
	{
		uint32 ntime = getMSTime();

		if (ntime > m_taxi_ride_time)
			m_CurrentTaxiPath->SendMoveForTime( this, SafePlayerCast( pObj ), ntime - m_taxi_ride_time);
		/*else
			m_CurrentTaxiPath->SendMoveForTime( this, SafePlayerCast( pObj ), m_taxi_ride_time - ntime);*/
	}

	Unit::AddInRangeObject(pObj);

	//if the object is a unit send a move packet if they have a destination
	if(pObj->GetTypeId() == TYPEID_UNIT)
	{
		//add an event to send move update have to send guid as pointer was causing a crash :(
		//sEventMgr.AddEvent( SafeCreatureCast( pObj )->GetAIInterface(), &AIInterface::SendCurrentMove, this->GetGUID(), EVENT_UNIT_SENDMOVE, 200, 1);
		SafeCreatureCast( pObj )->GetAIInterface()->SendCurrentMove(this);
	}
}

void Player::OnRemoveInRangeObject(Object* pObj)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//if (/*!CanSee(pObj) && */IsVisible(pObj))
	//{
		//RemoveVisibleObject(pObj);
	//}

	//object was deleted before reaching here
	if (pObj == NULL)
	{ 
		return;
	}

	if (pObj->GetGUID() == GetUInt64Value(UNIT_FIELD_SUMMON))
	{
		RemoveFieldSummon();
	}

	m_visibleObjects.erase(pObj);
	Unit::OnRemoveInRangeObject(pObj);

	if( pObj->GetGUID() == m_CurrentCharm )
	{
		Unit *p =GetMapMgr()->GetUnit( m_CurrentCharm );
		if( !p )
		{ 
			return;
		}

		UnPossess();
		if(m_currentSpell)
			m_currentSpell->cancel();	   // cancel the spell
		m_CurrentCharm=0;

		if( p->m_temp_summon && p->GetTypeId() == TYPEID_UNIT )
			SafeCreatureCast( p )->SafeDelete();
	}
 
	if(pObj == m_Summon)
	{
		if(m_Summon->IsSummon())
		{
			m_Summon->Dismiss();
		}
		else
		{
			m_Summon->Remove( true, false);
		}
		if(m_Summon)
		{
			m_Summon->ClearPetOwner();
			m_Summon = 0;
		}
	}

	/* wehee loop unrolling */
/*	if(m_spellTypeTargets[0] == pObj)
		m_spellTypeTargets[0] = NULL;
	if(m_spellTypeTargets[1] == pObj)
		m_spellTypeTargets[1] = NULL;
	if(m_spellTypeTargets[2] == pObj)
		m_spellTypeTargets[2] = NULL;*/
	if(pObj->IsUnit())
	{
		for(uint32 x = 0; x < NUM_SPELL_TYPE_INDEX; ++x)
			if(m_spellIndexTypeTargets[x] == pObj->GetGUID())
				m_spellIndexTypeTargets[x] = 0;
	}
}

void Player::ClearInRangeSet()
{
	m_visibleObjects.clear();
	Unit::ClearInRangeSet();
}

void Player::EventCannibalize(uint32 amount)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 amt = (GetUInt32Value(UNIT_FIELD_MAXHEALTH)*amount)/100;
	
	uint32 newHealth = GetUInt32Value(UNIT_FIELD_HEALTH) + amt;
	
	if(newHealth <= GetUInt32Value(UNIT_FIELD_MAXHEALTH))
		SetUInt32Value(UNIT_FIELD_HEALTH, newHealth);
	else
		SetUInt32Value(UNIT_FIELD_HEALTH, GetUInt32Value(UNIT_FIELD_MAXHEALTH));

	cannibalizeCount++;
	if(cannibalizeCount == 5)
		SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);

	WorldPacket data(SMSG_PERIODICAURALOG, 48);
	data << GetNewGUID();				   // caster guid
	data << GetNewGUID();				   // target guid
	data << (uint32)(20577);				// spellid
	data << (uint32)1;					  // unknown?? need resource?
	data << (uint32)FLAG_PERIODIC_HEAL;		// aura school
	data << amt;							// amount of done to target / heal / damage
	data << (uint32)this->GetOverHeal(amt);					  // overkill
	data << (uint32)0;							// school
	data << (uint32)0;					  // res 
	data << (uint32)0;					  // abs
	SendMessageToSet(&data, true);
}

void Player::LoadTaxiMask(const char* data)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	vector<string> tokens = StrSplit(data, " ");

	int index;
	vector<string>::iterator iter;

	for (iter = tokens.begin(), index = 0;
		(index < TAXIMASK_SIZE) && (iter != tokens.end()); ++iter, ++index)
	{
		m_taximask[index] = atol((*iter).c_str());
	}
}

bool Player::HasQuestForItem(uint32 itemid)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	Quest *qst;
	for( uint32 i = 0; i < 25; ++i )
	{
		if( m_questlog[i] != NULL )
		{
			qst = m_questlog[i]->GetQuest();

			// Check the item_quest_association table for an entry related to this item
			QuestAssociationList *tempList = QuestMgr::getSingleton().GetQuestAssociationListForItemId( itemid );
			if( tempList != NULL )
			{
				QuestAssociationList::iterator it;
				for (it = tempList->begin(); it != tempList->end(); ++it)
				{
					if ( ((*it)->qst == qst) && (GetItemInterface()->GetItemCount( itemid ) < (*it)->item_count) )
					{
						return true;
					} // end if
				} // end for
			} // end if
			
			// No item_quest association found, check the quest requirements
			if( !qst->count_required_item )
				continue;

			for( uint32 j = 0; j < 6; ++j )
				if( qst->required_item[j] == itemid && ( (int32)GetItemInterface()->GetItemCount( itemid ) < qst->required_itemcount[j] ) )
				{ 
					return true;
				}
		}
	}
	return false;
}


//scriptdev2
bool Player::HasItemCount( uint32 item, uint32 count, bool inBankAlso )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	return (m_ItemInterface->GetItemCount(item, inBankAlso) == count);
}


/*Loot type MUST be
1-corpse, go
2-skinning/herbalism/minning
3-Fishing
*/
void Player::SendLoot(uint64 guid,uint8 loot_type)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	
	Group * m_Group = m_playerInfo->m_Group;
	if(!IsInWorld()) 
	{ 
		return;
	}
	Loot * pLoot = NULL;
	uint32 guidtype = GET_TYPE_FROM_GUID(guid);
	int8 loot_method = -1;

	if(guidtype == HIGHGUID_TYPE_UNIT)
	{
		Creature* pCreature = GetMapMgr()->GetCreature( guid );
		if(!pCreature)
		{ 
			return;
		}
		//check loot stealing ?
		pLoot=&pCreature->loot;
		m_currentLoot = pCreature->GetGUID();
		loot_method = pCreature->m_lootMethod;
		if ( loot_method < 0 )
		{
			loot_method = PARTY_LOOT_FFA;
			pCreature->m_lootMethod = PARTY_LOOT_FFA;
		}
	}else if(guidtype == HIGHGUID_TYPE_GAMEOBJECT)
	{
		GameObject* pGO = GetMapMgr()->GetGameObject( guid );
		if(!pGO)
		{ 
			return;
		}
		pGO->SetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_STATE,0);
		pLoot=&pGO->loot;
		m_currentLoot = pGO->GetGUID();
	}
	else if((guidtype == HIGHGUID_TYPE_PLAYER) )
	{
		Player *p=GetMapMgr()->GetPlayer( guid );
		if(!p)
		{ 
			return;
		}
		pLoot=&p->loot;
		m_currentLoot = p->GetGUID();
	}
	else if( (guidtype == HIGHGUID_TYPE_CORPSE))
	{
		Corpse *pCorpse = objmgr.GetCorpse((uint32)guid);
		if(!pCorpse)
		{ 
			return;
		}
		pLoot=&pCorpse->loot;
		m_currentLoot = pCorpse->GetGUID();
	}
	else if( (guidtype == HIGHGUID_TYPE_ITEM) )
	{
		Item *pItem = GetItemInterface()->GetItemByGUID(guid);
		if(!pItem)
		{ 
			return;
		}
		pLoot = pItem->loot;
		m_currentLoot = pItem->GetGUID();
	}

	if(!pLoot)
	{
		// something whack happened.. damn cheaters..
		return;
	}

	// add to looter set
	pLoot->looters.insert(GetLowGUID());
		
	WorldPacket data, data2(28);
	data.SetOpcode (SMSG_LOOT_RESPONSE);
   
   
	m_lootGuid = guid;

			
	data << guid;
	data << loot_type;//loot_type;
	data << pLoot->gold;
	data << (uint8) 0;//loot size reserve

	  
	std::vector<__LootItem>::iterator iter=pLoot->items.begin();
	uint32 count=0;
	uint8 slottype = 0;
   
	for(uint32 x=0;iter!=pLoot->items.end();iter++,x++)
	{ 
		if (iter->iItemsCount == 0)
			continue;

		LooterSet::iterator itr = iter->has_looted.find(GetLowGUID());
		if (iter->has_looted.end() != itr)
			continue;

		ItemPrototype* itemProto =iter->item.itemproto;
		if (!itemProto)		   
			continue;

		// check if it's on ML if so only quest items and ffa loot should be shown based on mob
		if ( loot_method == PARTY_LOOT_MASTER && m_Group && m_Group->GetLooter() != m_playerInfo )
			// pass on all ffa_loot and the grey / white items
			if ( !iter->ffa_loot && !(itemProto->Quality < m_Group->GetThreshold()) )
				continue;

		//quest items check. type 4/5
        //quest items that dont start quests.
        if((itemProto->Bonding == ITEM_BIND_QUEST) && !(itemProto->QuestId) && !HasQuestForItem(iter->item.itemproto->ItemId))
            continue;
        if((itemProto->Bonding == ITEM_BIND_QUEST2) && !(itemProto->QuestId) && !HasQuestForItem(iter->item.itemproto->ItemId))
            continue;

        //quest items that start quests need special check to avoid drops all the time.
        if((itemProto->Bonding == ITEM_BIND_QUEST) && (itemProto->QuestId) && GetQuestLogForEntry(itemProto->QuestId))
            continue;
        if((itemProto->Bonding == ITEM_BIND_QUEST2) && (itemProto->QuestId) && GetQuestLogForEntry(itemProto->QuestId))
            continue;

        if((itemProto->Bonding == ITEM_BIND_QUEST) && (itemProto->QuestId) && HasFinishedQuest(itemProto->QuestId))
            continue;
        if((itemProto->Bonding == ITEM_BIND_QUEST2) && (itemProto->QuestId) && HasFinishedQuest(itemProto->QuestId))
            continue;

        //check for starting item quests that need questlines.
        if((itemProto->QuestId && itemProto->Bonding != ITEM_BIND_QUEST && itemProto->Bonding != ITEM_BIND_QUEST2))
        {
            bool HasRequiredQuests = true;
            Quest * pQuest = QuestStorage.LookupEntry(itemProto->QuestId);
            if(pQuest)
            {
				uint32 finishedCount = 0;

                //check if its a questline.
                for(int32 i = 0; i < pQuest->count_requiredquests; i++)
                {
                    if(pQuest->required_quests[i])
                    {
                        if(!HasFinishedQuest(pQuest->required_quests[i]) || GetQuestLogForEntry(pQuest->required_quests[i]))
                        {
							if (!(pQuest->quest_flags & QUEST_FLAG_ONLY_ONE_REQUIRED)) {
								HasRequiredQuests = false;
								break;
							}
						}
						else
						{
							finishedCount++;
						}
                    }
                }

				if (pQuest->quest_flags & QUEST_FLAG_ONLY_ONE_REQUIRED) {
					if (finishedCount == 0) continue;
				} else {
	                if(!HasRequiredQuests)
    	                continue;
				}
            }
        } 


		slottype = 0;
		if(m_Group != NULL && loot_type < 2)
		{
			switch(loot_method)
			{
			case PARTY_LOOT_MASTER:
				slottype = 2;
				break;
			case PARTY_LOOT_GROUP:
			case PARTY_LOOT_RR:
			case PARTY_LOOT_NBG:
				slottype = 1;
				break;
			default:
				slottype = 0;
				break;
			}
			// only quality items are distributed
			if(itemProto->Quality < m_Group->GetThreshold())
			{
				slottype = 0;
			}

			/* if all people passed anyone can loot it? :P */
			if(iter->passed)
				slottype = 0;					// All players passed on the loot

			//if it is ffa loot and not an masterlooter
			if(iter->ffa_loot)
				slottype = 0;
		}

		data << uint8(x); 
		data << uint32(itemProto->ItemId);
		data << uint32(iter->iItemsCount);//nr of items of this type
		data << uint32(iter->item.displayid); 
		//data << uint32(iter->iRandomSuffix ? iter->iRandomSuffix->id : 0);
		//data << uint32(iter->iRandomProperty ? iter->iRandomProperty->ID : 0);
		if(iter->iRandomSuffix)
		{
			data << Item::GenerateRandomSuffixFactor(itemProto);
			data << uint32(-int32(iter->iRandomSuffix->id));
		}
		else if(iter->iRandomProperty)
		{
			data << uint32(0);
			data << uint32(iter->iRandomProperty->ID);
		}
		else
		{
			data << uint32(0);
			data << uint32(0);
		}

		data << slottype;   // "still being rolled for" flag
		
		if(slottype == 1)
		{
			if(iter->roll == NULL && !iter->passed)
			{
				int32 ipid = 0;
				uint32 factor=0;
				if(iter->iRandomProperty)
					ipid=iter->iRandomProperty->ID;
				else if(iter->iRandomSuffix)
				{
					ipid = -int32(iter->iRandomSuffix->id);
					factor=Item::GenerateRandomSuffixFactor(iter->item.itemproto);
				}

				if(iter->item.itemproto)
				{
					iter->roll = new LootRoll(60000, (m_Group != NULL ? m_Group->MemberCount() : 1),  guid, x, iter->item.itemproto->ItemId, factor, uint32(ipid), GetMapMgr());
					
					/*
					0C BA 0E D0 0E 00 30 F1 guid 
					00 00 00 00 slot
					7A 16 00 00 item
					00 26 81 8E random factor
					00 00 00 00 randomid
					01 00 00 00 item count 
					60 EA 00 00 timer
					07 roll type mask ?
					*/
					data2.Initialize(SMSG_LOOT_START_ROLL);
					data2 << guid;
					data2 << GetMapId();
					data2 << x;
					data2 << uint32(iter->item.itemproto->ItemId);
					data2 << uint32(factor);
					if(iter->iRandomProperty)
						data2 << uint32(iter->iRandomProperty->ID);
					else if(iter->iRandomSuffix)
						data2 << uint32(ipid);
					else
						data2 << uint32(0);

					data2 << uint32(iter->iItemsCount);
					data2 << uint32(60000); // countdown
					data2 << uint8( 0x0F );                      // 3.3 - roll type mask ? found values : F,D,7,
				}

				Group * pGroup = m_playerInfo->m_Group;
				if(pGroup)
				{
					pGroup->Lock();
					for(uint32 i = 0; i < pGroup->GetSubGroupCount(); ++i)
					{
						for(GroupMembersSet::iterator itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
						{
							if((*itr)->m_loggedInPlayer && (*itr)->m_loggedInPlayer->GetItemInterface()->CanReceiveItem(itemProto, iter->iItemsCount) == 0)
							{
								if( (*itr)->m_loggedInPlayer->m_passOnLoot )
									iter->roll->PlayerRolled( (*itr)->m_loggedInPlayer, 3 );		// passed
								else
									(*itr)->m_loggedInPlayer->GetSession()->SendPacket(&data2);
							}
						}
					}
					pGroup->Unlock();
				}
				else
				{
					GetSession()->SendPacket(&data2);
				}
			}			
		}
		count++;
	}
	data.wpos (13);
	data << (uint8)count;

	GetSession ()->SendPacket(&data);
	SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOOTING);
}

void Player::EventAllowTiggerPort(bool enable)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	m_AllowAreaTriggerPort = enable;
}

uint32 Player::CalcTalentResetCost(uint32 resetnum)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	
	if(resetnum ==0 ) 
	{ 
		return  10000;
	}
	else
	{
		if(resetnum>10)
		{ 
		return  500000;
		}
		else 
	return resetnum*50000;
	}
}

void Player::SendTalentResetConfirm()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(MSG_TALENT_WIPE_CONFIRM, 12);
	data << GetGUID();
	data << CalcTalentResetCost(GetTalentResetTimes());
	GetSession()->SendPacket(&data);
}
void Player::SendPetUntrainConfirm()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	Pet* pPet = GetSummon();
	if( pPet == NULL )
	{ 
		return;
	}
	WorldPacket data( SMSG_PET_UNLEARN_CONFIRM, 12 );
	data << pPet->GetGUID();
	data << pPet->GetUntrainCost();
	GetSession()->SendPacket( &data );
}

int32 Player::CanShootRangedWeapon( uint32 spellid, Unit* target, bool autoshot )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SpellEntry* spellinfo = dbcSpell.LookupEntry( spellid );

	if( spellinfo == NULL )
	{ 
		return -1;
	}
	//sLog.outString( "Canshootwithrangedweapon!?!? spell: [%u] %s" , spellinfo->Id , spellinfo->Name );

	// Check if Morphed
	if( polySpell > 0 )
	{ 
		return SPELL_FAILED_NOT_SHAPESHIFT;
	}

	// Check ammo
	Item* itm = GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_RANGED );
	if( itm == NULL )
	{ 
		return SPELL_FAILED_NO_AMMO;
	}

	// Check ammo level
#ifndef CATACLYSM_SUPPORT
	ItemPrototype * iprot=ItemPrototypeStorage.LookupEntry(GetUInt32Value(PLAYER_AMMO_ID));
	if( iprot && getLevel()< iprot->RequiredLevel)
	{ 
		return SPELL_FAILED_LOWLEVEL;
	}
#endif

	// Player has clicked off target. Fail spell.
	if( m_curSelection != m_AutoShotTarget )
	{ 
		return SPELL_FAILED_INTERRUPTED;
	}

	// Check if target is allready dead
	if( target->IsDead() )
	{ 
		return SPELL_FAILED_TARGETS_DEAD;
	}

	// Check if in line of sight (need collision detection).
	if (sWorld.Collision) {
		if (GetMapId() == target->GetMapId() && !CollideInterface.CheckLOS(GetMapId(),GetPositionNC(),target->GetPositionNC()))
		{ 
			return SPELL_FAILED_LINE_OF_SIGHT;
		}
	}

	// Check if we aren't casting another spell allready
	if( GetCurrentSpell() )
	{ 
		return -1;
	}
   
	// Supalosa - The hunter ability Auto Shot is using Shoot range, which is 5 yards shorter.
	// So we'll use 114, which is the correct 35 yard range used by the other Hunter abilities (arcane shot, concussive shot...)
	uint8 fail = 0;
	uint32 rIndex = autoshot ? 114 : spellinfo->rangeIndex;
	SpellRange* range = dbcSpellRange.LookupEntry( rIndex );
	float minrange = GetMinRange( range );
	float dist = CalcDistance( this, target );
	float maxr = GetMaxRange( range ) + 2.52f;

	if( Need_SM_Apply(spellinfo) )
	{
		SM_FFValue( this->SM_FRange, &maxr, spellinfo->SpellGroupType );
		SM_PFValue( this->SM_PRange, &maxr, spellinfo->SpellGroupType );
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		float spell_flat_modifers=0;
		float spell_pct_modifers=0;
		SM_FFValue(this->SM_FRange,&spell_flat_modifers,spellinfo->SpellGroupType);
		SM_FFValue(this->SM_PRange,&spell_pct_modifers,spellinfo->SpellGroupType);
		if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
			printf("!!!!!spell range bonus mod flat %f , spell range bonus pct %f , spell range %f, spell group %u\n",spell_flat_modifers,spell_pct_modifers,maxr,spellinfo->SpellGroupType);
#endif
	}

	//float bonusRange = 0;
	// another hackfix: bonus range from hunter talent hawk eye: +2/4/6 yard range to ranged weapons
	//if(autoshot)
	//SM_FFValue( SM_FRange, &bonusRange, dbcSpell.LookupEntry( 75 )->SpellGroupType ); // HORRIBLE hackfixes :P
	// Partha: +2.52yds to max range, this matches the range the client is calculating.
	// see extra/supalosa_range_research.txt for more info
	//bonusRange = 2.52f;
	//sLog.outString( "Bonus range = %f" , bonusRange );

	// check if facing target
	if(!isInFront(target))
	{
		fail = SPELL_FAILED_UNIT_NOT_INFRONT;
	}
 
	// Check ammo count
#ifndef CATACLYSM_SUPPORT
	if( m_requiresNoAmmo == false && iprot && itm->GetProto()->SubClass != ITEM_SUBCLASS_WEAPON_WAND )
	{
		uint32 ammocount = GetItemInterface()->GetItemCount(iprot->ItemId);
		if(ammocount == 0)
			fail = SPELL_FAILED_NO_AMMO;
	}
#endif

	// Check for too close
	if( spellid != SPELL_RANGED_WAND )//no min limit for wands
		if( minrange > dist )
			fail = SPELL_FAILED_TOO_CLOSE;
	
	if( dist > maxr )
	{
		//	sLog.outString( "Auto shot failed: out of range (Maxr: %f, Dist: %f)" , maxr , dist );
		fail = SPELL_FAILED_OUT_OF_RANGE;
	}

	if( spellid == SPELL_RANGED_THROW )
	{
		if( itm != NULL ) // no need for this
			if( itm->GetProto() )
				if( GetItemInterface()->GetItemCount( itm->GetProto()->ItemId ) == 0 )
					fail = SPELL_FAILED_NO_AMMO;
	} 
/*  else
	{
		if(GetUInt32Value(PLAYER_AMMO_ID))//for wand
			if(this->GetItemInterface()->GetItemCount(GetUInt32Value(PLAYER_AMMO_ID)) == 0)
				fail = SPELL_FAILED_NO_AMMO;
	}
*/
	if( fail > 0 )// && fail != SPELL_FAILED_OUT_OF_RANGE)
	{
		//SendCastResult( autoshot ? 75 : spellid, fail, 0, 0 );
		packetSMSG_CASTRESULT cr;
		cr.SpellId = autoshot ? 75 : spellid;
		cr.ErrorMessage = fail;
		cr.MultiCast = 0;
		m_session->OutPacket( SMSG_CAST_FAILED, sizeof(packetSMSG_CASTRESULT), &cr );
		if( fail != SPELL_FAILED_OUT_OF_RANGE )
		{
			uint32 spellid2 = autoshot ? 75 : spellid;
			m_session->OutPacket( SMSG_CANCEL_AUTO_REPEAT, 4, &spellid2 );
		}
		//sLog.outString( "Result for CanShootWIthRangedWeapon: %u" , fail );
		//sLog.outDebug( "Can't shoot with ranged weapon: %u (Timer: %u)" , fail , m_AutoShotAttackTimer );
		return fail;
	}

	return 0;
}

void Player::EventRepeatSpell()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( !m_curSelection || !IsInWorld() )
	{ 
		return;
	}
	
	Unit* target = GetMapMgr()->GetUnit( m_curSelection );
	if( target == NULL )
	{
		m_AutoShotAttackTimer = 0; //avoid flooding client with error mesages
		m_onAutoShot = false;
		//sLog.outDebug( "Can't cast Autoshot: Target changed! (Timer: %u)" , m_AutoShotAttackTimer );
		return;
	}

	//m_AutoShotDuration = m_uint32Values[UNIT_FIELD_RANGEDATTACKTIME];
	// Zack : spell hasting added
	m_AutoShotDuration = std::max(1000,float2int32(float(m_uint32Values[UNIT_FIELD_RANGEDATTACKTIME])* GetSpellHaste() ));

	if( m_isMoving )
	{
		//sLog.outDebug( "HUNTER AUTOSHOT 2) %i, %i", m_AutoShotAttackTimer, m_AutoShotDuration );
		//m_AutoShotAttackTimer = m_AutoShotDuration;//avoid flooding client with error mesages
		//sLog.outDebug( "Can't cast Autoshot: You're moving! (Timer: %u)" , m_AutoShotAttackTimer );
		m_AutoShotAttackTimer = 100; // shoot when we can
		return;
	}

	int32 f = this->CanShootRangedWeapon( m_AutoShotSpell->Id, target, true );

	if( f != 0 )
	{
		if( f != SPELL_FAILED_OUT_OF_RANGE )
		{
			m_AutoShotAttackTimer = 0; 
			m_onAutoShot=false;
		}
		else if( m_isMoving )
		{
			m_AutoShotAttackTimer = 100;
		}
		else
		{
			m_AutoShotAttackTimer = m_AutoShotDuration;//avoid flooding client with error mesages
		}
		return;
	}
	else
	{		
		m_AutoShotAttackTimer = m_AutoShotDuration;
	
		Spell* sp = SpellPool.PooledNew();
		sp->Init( this, m_AutoShotSpell, true, NULL );
		SpellCastTargets tgt( m_curSelection );
		sp->prepare( &tgt );
	}
}

bool Player::HasSpell(uint32 spell)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	return mSpells.find(spell) != mSpells.end();
}

bool Player::HasSpellwithNameHash(uint32 hash)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SpellSet::iterator it,iter;
	for(iter= mSpells.begin();iter != mSpells.end();)
	{
		it = iter++;
		uint32 SpellID = *it;
		SpellEntry *e = dbcSpell.LookupEntry(SpellID);
		if(e->NameHash == hash)
		{ 
			return true;
		}
	}
	return false;
}

bool Player::HasDeletedSpell(uint32 spell)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	return (mDeletedSpells.count(spell) > 0);
}

void Player::removeSpellByHashName(uint32 hash)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SpellSet::iterator it,iter;
	
	for(iter= mSpells.begin();iter != mSpells.end();)
	{
		it = iter++;
		uint32 SpellID = *it;
		SpellEntry *e = dbcSpell.LookupEntry(SpellID);
		if(e->NameHash == hash)
		{
			if(info->spell_list.find(e->Id) != info->spell_list.end())
				continue;

			RemoveAllAuras(SpellID,GetGUID());
			if( e->NameHash == SPELL_HASH_DUAL_WIELD )
				RemoveAndMailItemFromSlot( EQUIPMENT_SLOT_OFFHAND );
#ifdef USING_BIG_ENDIAN
			uint32 swapped = swap32(SpellID);
			m_session->OutPacket(SMSG_REMOVED_SPELL, 4, &swapped);
#else
			m_session->OutPacket(SMSG_REMOVED_SPELL, 4, &SpellID);		
#endif
			mSpells.erase(it);
			SpellSet::iterator sp_itr = m_specs[ m_talentActiveSpec ].SpecSpecificSpells.find( SpellID );
			if( sp_itr != m_specs[ m_talentActiveSpec ].SpecSpecificSpells.end() )
				m_specs[ m_talentActiveSpec ].SpecSpecificSpells.erase( sp_itr );
		}
	}

	for(iter= mDeletedSpells.begin();iter != mDeletedSpells.end();)
	{
		it = iter++;
		uint32 SpellID = *it;
		SpellEntry *e = dbcSpell.LookupEntry(SpellID);
		if(e->NameHash == hash)
		{
			if(info->spell_list.find(e->Id) != info->spell_list.end())
				continue;

			RemoveAllAuras(SpellID,GetGUID());
#ifdef USING_BIG_ENDIAN
			uint32 swapped = swap32(SpellID);
			m_session->OutPacket(SMSG_REMOVED_SPELL, 4, &swapped);
#else
			m_session->OutPacket(SMSG_REMOVED_SPELL, 4, &SpellID);		
#endif
			mDeletedSpells.erase(it);
		}
	}
}

bool Player::removeSpell(uint32 SpellID, bool MoveToDeleted, bool SupercededSpell, uint32 SupercededSpellID)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SpellSet::iterator it,iter = mSpells.find(SpellID);
	if(iter != mSpells.end())
	{
		mSpells.erase(iter);
		RemoveAllAuras(SpellID,GetGUID());

		SpellSet::iterator sp_itr = m_specs[ m_talentActiveSpec ].SpecSpecificSpells.find( SpellID );
		if( sp_itr != m_specs[ m_talentActiveSpec ].SpecSpecificSpells.end() )
			m_specs[ m_talentActiveSpec ].SpecSpecificSpells.erase( sp_itr );
	}
	else
	{
		return false;
	}

/*	//added by Zack. As code got complicated people started to neglect when to add spell to "deletedspell" list or not
	//"deletedspell" has the purpuse to not send spells to trainer that were already teached once
	//when we reset talents or professions we wish to clear "deletedspell" list too
	SpellEntry *e = dbcSpell.LookupEntry(SpellID);
	if( !HasSpellwithNameHash( e->NameHash ) )
		for(iter= mDeletedSpells.begin();iter != mDeletedSpells.end();)
		{
			it = iter++;
			SpellEntry *e1 = dbcSpell.LookupEntry( *it );
			if(e1->NameHash == e->NameHash)
				mDeletedSpells.erase(it);
		}*/

	if(MoveToDeleted)
		mDeletedSpells.insert(SpellID);

	if(!IsInWorld())
	{ 
		return true;
	}

	if(SupercededSpell)
	{
		WorldPacket data(SMSG_SUPERCEDED_SPELL, 8);
		data << SpellID << SupercededSpellID;
		m_session->SendPacket(&data);
	}
	else
	{
#ifdef USING_BIG_ENDIAN
		uint32 swapped = swap32(SpellID);
		m_session->OutPacket(SMSG_REMOVED_SPELL, 4, &swapped);
#else
		m_session->OutPacket(SMSG_REMOVED_SPELL, 4, &SpellID);		
#endif
	}

	return true;
}

bool Player::removeDeletedSpell( uint32 SpellID )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SpellSet::iterator it = mDeletedSpells.find( SpellID );
	if ( it == mDeletedSpells.end() )
	{ 
		return false;
	}
	
	mDeletedSpells.erase( it );
	return true;
}

void Player::EventActivateGameObject(GameObject* obj)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	obj->BuildFieldUpdatePacket(this, GAMEOBJECT_DYNAMIC, 1 | 8);
}

void Player::EventDeActivateGameObject(GameObject* obj)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	obj->BuildFieldUpdatePacket(this, GAMEOBJECT_DYNAMIC, 0);
}

void Player::EventTimedQuestExpire(Quest *qst, QuestLogEntry *qle, uint32 log_slot)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket fail;
	sQuestMgr.BuildQuestFailed(&fail, qst->id);
	GetSession()->SendPacket(&fail);
	CALL_QUESTSCRIPT_EVENT(qle, OnQuestCancel)(this);
	qle->Finish();
}

void Player::RemoveQuestsFromLine(int skill_line)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	for (int i = 0; i < 25; i++)
	{
		if (m_questlog[i])
		{
			Quest* qst = m_questlog[i]->GetQuest();
			if (qst && qst->required_tradeskill == skill_line)
			{
				m_questlog[i]->Finish();
	
				// Remove all items given by the questgiver at the beginning
				for(uint32 j = 0; j < 4; j++)
					if(qst->receive_items[j])
						GetItemInterface()->RemoveItemAmt(qst->receive_items[j], 1 );
			}
		}
	}

	set<uint32>::iterator itr,itr2;
	for (set<uint32>::iterator itr2 = m_finishedQuests.begin(); itr2 != m_finishedQuests.end();)
	{
		itr = itr2;
		itr2++;
		Quest * qst = QuestStorage.LookupEntry((*itr));
		if (qst && qst->required_tradeskill == skill_line)
			m_finishedQuests.erase(itr);
	}

	UpdateNearbyGameObjects();
}
//scriptdev2

void Player::AreaExploredOrEventHappens( uint32 questId )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	sQuestMgr.AreaExplored(this,questId);
}

void Player::SendInitialLogonPackets()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// Initial Packets... they seem to be re-sent on port.
//	m_session->OutPacket(SMSG_SET_REST_START_OBSOLETE, 4, &m_timeLogoff);

	//Proficiencies
    //SendSetProficiency(4,armor_proficiency);
    //SendSetProficiency(2,weapon_proficiency);
	packetSMSG_SET_PROFICICENCY pr;
	pr.ItemClass = 4;
	pr.Profinciency = armor_proficiency;
	m_session->OutPacket( SMSG_SET_PROFICIENCY, sizeof(packetSMSG_SET_PROFICICENCY), &pr );
	pr.ItemClass = 2;
	pr.Profinciency = weapon_proficiency;
	m_session->OutPacket( SMSG_SET_PROFICIENCY, sizeof(packetSMSG_SET_PROFICICENCY), &pr );
  
	//Tutorial Flags
	WorldPacket data;
	data.Initialize( SMSG_TUTORIAL_FLAGS );
	for (int i = 0; i < 8; i++)
		data << uint32( m_Tutorials[i] );
	GetSession()->SendPacket(&data);

	//Initial Spells
	smsg_InitialSpells();

	//no idea what this does. Really now.
	data.Initialize( SMSG_SERVER_BUCK_DATA );
	data << uint32( 0 );
	GetSession()->SendPacket(&data);

	//Initial Actions
	SendInitialActions();

	//Factions
	smsg_InitialFactions();

	//talents
	smsg_TalentsInfo(false, 0, 0);

	//i guess this will be an empty packet most of the time ?
	SendEquipmentSetList();

	data.Initialize(SMSG_LOGIN_SETTIMESPEED);
	data << (uint32)TimeToGametime( UNIXTIME );
//	data << (float)0.016666675359f;  // Normal Game Speed
	data << (float)0.015436676437f;  // Abnormal Game Speed to trick cheat engine to find it
	data << uint32( 0 );
	GetSession()->SendPacket( &data );

	sLog.outDetail("WORLD: Sent initial logon packets for %s.", GetName());
}

void Player::Reset_Spells()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	PlayerCreateInfo *info = objmgr.GetPlayerCreateInfo(getRace(), getClass());
	ASSERT(info);

	std::list<uint32> spelllist;
	
	for(SpellSet::iterator itr = mSpells.begin(); itr!=mSpells.end(); itr++)
	{
		spelllist.push_back((*itr));
	}

	for(std::list<uint32>::iterator itr = spelllist.begin(); itr!=spelllist.end(); itr++)
	{
		removeSpell((*itr), false, false, 0);
	}

	for(std::set<uint32>::iterator sp = info->spell_list.begin();sp!=info->spell_list.end();sp++)
	{
		if(*sp)
		{
			addSpell(*sp);
		}
	}

	// give us a chance to properly relearn spells
	mDeletedSpells.clear();

	// this is needed to respec talents also
	for(uint32 i=0;i<MAX_SPEC_COUNT;i++)
	{
		m_specs[i].SpecSpecificSpells.clear();
	}

	//if we have multi talent speccing then we should readd those to enable menu for changing specs
	if( m_talentSpecsCount == MAX_SPEC_COUNT )
	{
		addSpell( 63644 );
		addSpell( 63645 );
	}
}

void Player::RemoveAndMailItemFromSlot(uint8 slot)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( slot > EQUIPMENT_SLOT_END )
	{ 
		return;
	}

	if( !GetItemInterface() )
	{ 
		return;
	}

	Item *SrcItem = GetItemInterface()->SafeRemoveAndRetreiveItemFromSlot(INVENTORY_SLOT_NOT_SET, slot, false);

	RemoveAndMailItem( &SrcItem );
}

void Player::RemoveAndMailItem(Item **it)
{
	Item *SrcItem = *it;

	if( SrcItem == NULL )
		return;

	if( !GetItemInterface() )
	{ 
		return;
	}

	GetItemInterface()->SafeRemoveAndRetreiveItemByGuid( SrcItem->GetGUID(), false);

	//let's try top find a free spot for it
	SlotResult sr = GetItemInterface()->FindFreeInventorySlot( SrcItem->GetProto() );
	if( sr.Result == true )
	{
		GetItemInterface()->SafeAddItem( SrcItem, sr.ContainerSlot, sr.Slot );
		SrcItem->m_isDirty = true;
		return;
	}

	// Buy a bigger bag next time, Right now we mail it.
	stringstream ss;
	ss << "INSERT INTO mailbox_insert_queue values ( ";
	ss << GetGUID() << ",";
	ss << GetGUID() << ",";
	ss << "'Talent reseted'" << ",";
	ss << "'Titan`s grip was unlearned while you had this equipped.'" << ",";
	ss << 1 << ",";
	ss << 0 << ",";
	ss << SrcItem->GetProto()->ItemId << ",";
	ss << 1 << ");";
	QueryResult *result = CharacterDatabase.Query( ss.str().c_str() );

	SrcItem->DeleteFromDB();
	SrcItem->DeleteMe();
	*it = NULL;
}

void Player::Reset_Talents()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SetUInt32Value( PLAYER_FLAGS, GetUInt32Value( PLAYER_FLAGS ) & ~PLAYER_FLAGS_CUSTOM_FORCE_TALENTRESET);
	uint8 playerClass = getClass();
	unsigned int numRows = dbcTalent.GetNumRows();
	for (unsigned int i = 0; i < numRows; i++)		  // Loop through all talents.
	{
		TalentEntry *tmpTalent = dbcTalent.LookupRow(i);
		if(!tmpTalent)
			continue; //should not ocur
		//this is a normal talent (i hope )
		for (int j = 0; j < 5; j++)
		{
			if (tmpTalent->RankID[j] != 0)
			{
				SpellEntry *spellInfo;
				spellInfo = dbcSpell.LookupEntry( tmpTalent->RankID[j] );
				if(spellInfo)
				{
					if (spellInfo->NameHash == SPELL_HASH_DUAL_WIELD)
					{
						if (getClass() != SHAMAN)
							continue; //only shamans should lose it when they reset talents - opti
					}
					if( spellInfo->NameHash == SPELL_HASH_TITAN_S_GRIP && GetItemInterface() && getClass() == WARRIOR ) 
					{
						Item * it = GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
						if( it )
							RemoveAndMailItemFromSlot( EQUIPMENT_SLOT_OFFHAND );
					}
					for(int k=0;k<3;k++)
						if(spellInfo->Effect[k] == SPELL_EFFECT_LEARN_SPELL)
						{
							//removeSpell(spellInfo->EffectTriggerSpell[k], false, 0, 0);
							//remove higher ranks of this spell too (like earth shield lvl 1 is talent and the rest is thought from trainer) 
							SpellEntry *spellInfo2;
							spellInfo2 = dbcSpell.LookupEntry( spellInfo->EffectTriggerSpell[k] );
							if(spellInfo2)
								removeSpellByHashName(spellInfo2->NameHash);
						}

					//make sure pets that get bonus from owner do not stack it up
					//Zack better remove the whole pet cause they alway found a new way for this to exploit :(
//					if( getClass() == HUNTER && GetSummon() )
//						GetSummon()->RemoveAura( spellInfo->Id );

					//remove them all in 1 shot
					removeSpellByHashName(spellInfo->NameHash);
				}
			}
			else
				break;
		}
	}
	int32 lev_now = getLevel();
	int32 levpoints=MIN( MAX( lev_now - 9, 0 ), PLAYERS_RECEIVE_TALENTPOINTS_WITH_LEVEL);
	int32 new_points = levpoints + m_Talent_point_mods;

	if( new_points < 0 )
		new_points = 0; //DK have -46 points at the start and they get them from quests.

	m_specs[ m_talentActiveSpec ].talents.clear();
	m_specs[ m_talentActiveSpec ].SpecSpecificSpells.clear();
	SetUInt32Value(PLAYER_CHARACTER_POINTS1, new_points ); 
	smsg_TalentsInfo(false,0,0);
	//stupid hunter talent beast mastery
	if( pet_extra_talent_points )
		ForceAllPetTalentAndSpellReset();

	//Dismiss any pets -> auras that influenced pet are not removed when removing from owner
	if(GetSummon())
	{
		if(GetSummon()->GetUInt32Value(UNIT_CREATED_BY_SPELL) > 0)
			GetSummon()->Dismiss();				// warlock summon -> dismiss
		else
			GetSummon()->Remove(false, true);	// hunter pet -> just remove for later re-call
		SetSummon( NULL );
	}
}

void Player::Reset_ToLevel1()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	RemoveAllAuras();
	// clear aura fields
/*	for(int i=UNIT_FIELD_AURA;i<UNIT_FIELD_AURASTATE;++i)
	{
		SetUInt32Value(i, 0);
	}*/
	SetUInt32Value(UNIT_FIELD_LEVEL, 1);
	PlayerCreateInfo *info = objmgr.GetPlayerCreateInfo(getRace(), getClass());
	ASSERT(info);

	SetUInt32Value(UNIT_FIELD_HEALTH, info->health);
	SetUInt32Value(UNIT_FIELD_POWER1, info->mana );
	SetUInt32Value(UNIT_FIELD_POWER2, 0 ); // this gets devided by 10
	SetUInt32Value(UNIT_FIELD_POWER3, info->focus );
	SetUInt32Value(UNIT_FIELD_POWER4, info->energy );
	SetUInt32Value(UNIT_FIELD_MAXHEALTH, info->health);
	SetUInt32Value(UNIT_FIELD_BASE_HEALTH, info->health);
	SetUInt32Value(UNIT_FIELD_BASE_MANA, info->mana);
	SetUInt32Value(UNIT_FIELD_MAXPOWER1, info->mana );
	SetUInt32Value(UNIT_FIELD_MAXPOWER2, info->rage );
	SetUInt32Value(UNIT_FIELD_MAXPOWER3, info->focus );
	SetUInt32Value(UNIT_FIELD_MAXPOWER4, info->energy );
	SetUInt32Value(UNIT_FIELD_STAT0, info->strength );
	SetUInt32Value(UNIT_FIELD_STAT1, info->ability );
	SetUInt32Value(UNIT_FIELD_STAT2, info->stamina );
	SetUInt32Value(UNIT_FIELD_STAT3, info->intellect );
	SetUInt32Value(UNIT_FIELD_STAT4, info->spirit );
	SetUInt32Value(UNIT_FIELD_ATTACK_POWER, info->attackpower );
	SetUInt32Value(PLAYER_CHARACTER_POINTS1,max(m_Talent_point_mods,0));
#ifndef CATACLYSM_SUPPORT
	SetUInt32Value(PLAYER_CHARACTER_POINTS2,2);
#endif
	for(uint32 x=0;x<7;x++)
		SetFloatValue(PLAYER_FIELD_MOD_DAMAGE_DONE_PCT+x, 1.00);

}

void Player::CalcResistance(uint32 type)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	int32 res;
	int32 pos;
	int32 neg;
	ASSERT(type < 7);
	pos=(BaseResistance[type]*BaseResistanceModPctPos[type])/100;
	neg=(BaseResistance[type]*BaseResistanceModPctNeg[type])/100;

	pos+=FlatResistanceModifierPos[type];
	neg+=FlatResistanceModifierNeg[type];
	res=BaseResistance[type]+pos-neg;
	if(type==0)res+=m_uint32Values[UNIT_FIELD_STAT1]*2;//fix armor from agi
	if(res<0)res=0;
	pos+=(res*ResistanceModPctPos[type])/100;
	neg+=(res*ResistanceModPctNeg[type])/100;
	res=pos-neg+BaseResistance[type];
	if(type==0)res+=m_uint32Values[UNIT_FIELD_STAT1]*2;//fix armor from agi

	if( res < 0 )
		res = 1;

	SetUInt32Value(UNIT_FIELD_RESISTANCEBUFFMODSPOSITIVE+type,pos);
	SetUInt32Value(UNIT_FIELD_RESISTANCEBUFFMODSNEGATIVE+type,-neg);
	SetUInt32Value(UNIT_FIELD_RESISTANCES+type,res>0?res:0);
	
	if( GetSummon() )
		GetSummon()->CalcResistance( type );//Re-calculate pet's too.
}


void Player::UpdateNearbyGameObjects()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	this->AquireInrangeLock(); //make sure to release lock before exit function !
	for (Object::InRangeSet::iterator itr = GetInRangeSetBegin(); itr != GetInRangeSetEnd(); ++itr)
	{
		if((*itr)->GetTypeId() == TYPEID_GAMEOBJECT)
		{
			bool activate_quest_object = false;
			GameObject *go = SafeGOCast(*itr);
			QuestLogEntry *qle;
			GameObjectInfo *info;

			info = go->GetInfo();
			bool deactivate = false;
			if(info &&
				(info->goMap.size() || info->itemMap.size()) )
			{
				for(GameObjectGOMap::iterator itr = go->GetInfo()->goMap.begin();
					itr != go->GetInfo()->goMap.end();
					++itr)
				{
					if((qle = GetQuestLogForEntry(itr->first->id)) != 0)
					{
						for(int32 i = 0; i < qle->GetQuest()->count_required_mob; ++i)
						{
							if(qle->GetQuest()->required_mob[i] == go->GetEntry() &&
								(int32)qle->GetMobCount(i) < qle->GetQuest()->required_mobcount[i])
							{
								activate_quest_object = true;
								break;
							}
						}
						if(activate_quest_object)
							break;
					}
				}

				if(!activate_quest_object)
				{
					for(GameObjectItemMap::iterator itr = go->GetInfo()->itemMap.begin();
						itr != go->GetInfo()->itemMap.end();
						++itr)
					{
						for(std::map<uint32, uint32>::iterator it2 = itr->second.begin();
							it2 != itr->second.end(); 
							++it2)
						{
							if(GetItemInterface()->GetItemCount(it2->first) < it2->second)
							{
								activate_quest_object = true;
								break;
							}
						}
						if(activate_quest_object)
							break;
					}
				}

				if(!activate_quest_object)
				{
					deactivate = true;
				}
			}
			bool bPassed = !deactivate;
			if((*itr)->GetByte(GAMEOBJECT_BYTES_1, GAMEOBJECT_BYTES_TYPEID) == GAMEOBJECT_TYPE_QUESTGIVER)
			{
				if(SafeGOCast((*itr))->m_quests)
				{
					if(SafeGOCast((*itr))->m_quests->size() > 0)
					{
						std::list<QuestRelation*>::iterator itr2 = SafeGOCast((*itr))->m_quests->begin();
						for(;itr2!=SafeGOCast((*itr))->m_quests->end();++itr2)
						{
							uint32 status = sQuestMgr.CalcQuestStatus(NULL, this, (*itr2)->qst, (*itr2)->type, false);
							if(status == QMGR_QUEST_CHAT || status == QMGR_QUEST_AVAILABLE || status == QMGR_QUEST_REPEATABLE || status == QMGR_QUEST_FINISHED)
							{
								// Activate gameobject
								EventActivateGameObject(SafeGOCast(*itr));
								bPassed = true;
								break;
							}
						}
					}
				}
			}
			if(!bPassed) 
				EventDeActivateGameObject(SafeGOCast(*itr));
		}
	}
	this->ReleaseInrangeLock();
}


void Player::EventTaxiInterpolate()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(!m_CurrentTaxiPath || m_mapMgr==NULL) 
	{ 
		return;
	}

	float x,y,z;
	x = y = z = 0.0f;
	uint32 ntime = getMSTime();

	if (ntime > m_taxi_ride_time)
		m_CurrentTaxiPath->SetPosForTime(x, y, z, ntime - m_taxi_ride_time, &lastNode, m_mapId);
	/*else
		m_CurrentTaxiPath->SetPosForTime(x, y, z, m_taxi_ride_time - ntime, &lastNode);*/

	if(x < _minX || x > _maxX || y < _minY || y > _maxX)
	{ 
		return;
	}

	SetPosition(x,y,z,0);
}

void Player::TaxiStart(TaxiPath *path, uint32 modelid, uint32 start_node)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	int32 mapchangeid = -1;
	float mapchangex,mapchangey,mapchangez = 0.0f;
	uint32 cn = m_taxiMapChangeNode;

	m_taxiMapChangeNode = 0;

	if(this->m_MountSpellId)
		RemoveAura(m_MountSpellId);
	//also remove morph spells
	if(GetUInt32Value(UNIT_FIELD_DISPLAYID)!=GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID))
	{
		RemoveAllAuraType(SPELL_AURA_TRANSFORM);
		RemoveAllAuraType(SPELL_AURA_MOD_SHAPESHIFT);
	}
	
	SetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID, modelid );
	SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_MOUNTED_TAXI);
	SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);

	SetTaxiPath(path);
	SetTaxiPos();
	SetTaxiState(true);
	m_taxi_ride_time = getMSTime();

	//uint32 traveltime = uint32(path->getLength() * TAXI_TRAVEL_SPEED); // 36.7407
	float traveldist = 0;

	float lastx = 0, lasty = 0, lastz = 0;
	TaxiPathNode *firstNode = path->GetPathNode(start_node);
	uint32 add_time = 0;

	// temporary workaround for taximodes with changing map
	if (path->GetID() == 766 || path->GetID() == 767 || path->GetID() == 771 || path->GetID() == 772)
	{
		JumpToEndTaxiNode(path);
		return;
	}

	if(start_node)
	{
		TaxiPathNode *pn = path->GetPathNode(0);
		float dist = 0;
		lastx = pn->x;
		lasty = pn->y;
		lastz = pn->z;
		for(uint32 i = 1; i <= start_node; ++i)
		{
			pn = path->GetPathNode(i);
			if(!pn)
			{
				JumpToEndTaxiNode(path);
				return;
			}

			dist += CalcDistance(lastx, lasty, lastz, pn->x, pn->y, pn->z);
			lastx = pn->x;
			lasty = pn->y;
			lastz = pn->z;
		}
		add_time = uint32( dist * TAXI_TRAVEL_SPEED );
		lastx = lasty = lastz = 0;
	}
	size_t endn = path->GetNodeCount();
	if(m_taxiPaths.size())
		endn-= 2;

	for(uint32 i = start_node; i < endn; ++i)
	{
		TaxiPathNode *pn = path->GetPathNode(i);

		// temporary workaround for taximodes with changing map
		if (!pn || path->GetID() == 766 || path->GetID() == 767 || path->GetID() == 771 || path->GetID() == 772)
		{
			JumpToEndTaxiNode(path);
			return;
		}

		if( pn->mapid != m_mapId )
		{
			endn = (i - 1);
			m_taxiMapChangeNode = i;

			mapchangeid = (int32)pn->mapid;
			mapchangex = pn->x;
			mapchangey = pn->y;
			mapchangez = pn->z;
			break;
		}

		if(!lastx || !lasty || !lastz)
		{
			lastx = pn->x;
			lasty = pn->y;
			lastz = pn->z;
		} else {			
			float dist = CalcDistance(lastx,lasty,lastz,
				pn->x,pn->y,pn->z);
			traveldist += dist;
			lastx = pn->x;
			lasty = pn->y;
			lastz = pn->z;
		}
	}

	uint32 traveltime = uint32(traveldist * TAXI_TRAVEL_SPEED);

	if( start_node > endn || (endn - start_node) > 200 )
		return;

	WorldPacket data(SMSG_MONSTER_MOVE, 38 + ( (endn - start_node) * 12 ) );
	data << GetNewGUID();
	data << uint8(0);
	data << firstNode->x << firstNode->y << firstNode->z;
	data << m_taxi_ride_time;
	data << uint8( 0 );
	data << uint32( MONSTER_MOVE_FLAG_FLY );
	data << uint32( traveltime );

	if(!cn)
		m_taxi_ride_time -= add_time;
	
	data << uint32( endn - start_node );
//	uint32 timer = 0, nodecount = 0;
//	TaxiPathNode *lastnode = NULL;

	for(uint32 i = start_node; i < endn; i++)
	{
		TaxiPathNode *pn = path->GetPathNode(i);
		if(!pn)
		{
			JumpToEndTaxiNode(path);
			return;
		}

		data << pn->x << pn->y << pn->z;
	}

	SendMessageToSet(&data, true);
  
	sEventMgr.AddEvent(this, &Player::EventTaxiInterpolate, 
		EVENT_PLAYER_TAXI_INTERPOLATE, 900, 0,0);

	if( mapchangeid < 0 )
	{
		TaxiPathNode *pn = path->GetPathNode((uint32)path->GetNodeCount() - 1);
		sEventMgr.AddEvent(this, &Player::EventDismount, path->GetPrice(), 
			pn->x, pn->y, pn->z, EVENT_PLAYER_TAXI_DISMOUNT, traveltime, 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT); 
//		SpeedCheatDelay( traveltime );
	}
	else
	{
		sEventMgr.AddEvent( this, &Player::EventTeleportTaxi, (uint32)mapchangeid, mapchangex, mapchangey, mapchangez, EVENT_PLAYER_TELEPORT, traveltime, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

void Player::JumpToEndTaxiNode(TaxiPath * path)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// this should *always* be safe in case it cant build your position on the path!
	TaxiPathNode * pathnode = path->GetPathNode((uint32)path->GetNodeCount()-1);
	if(!pathnode) 
	{ 
		return;
	}

	ModGold( -(int32)path->GetPrice());

	SetTaxiState(false);
	SetTaxiPath(NULL);
	UnSetTaxiPos();
	m_taxi_ride_time = 0;

	SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID , 0);
	RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_MOUNTED_TAXI);
	RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);

	SetPlayerSpeed(RUN, m_runSpeed);

	SafeTeleport(pathnode->mapid, 0, LocationVector(pathnode->x, pathnode->y, pathnode->z));

	// Start next path if any remaining
	if(m_taxiPaths.size())
	{
		TaxiPath * p = *m_taxiPaths.begin();
		m_taxiPaths.erase(m_taxiPaths.begin());
		TaxiStart(p, taxi_model_id, 0);
	}
}

void Player::LearnAllSpellsFromSkillLine(uint32 skill_line,bool skip_talents, bool class_specific)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 cnt = dbcSkillLineSpell.GetNumRows();
	for(uint32 i=0; i < cnt; i++)
	{
		skilllinespell * spsk = dbcSkillLineSpell.LookupRow( i );
		if( spsk && spsk->skilline == skill_line )
		{
			//let's make advanced checks
//			if( only_trainable == true )
			{
				SpellEntry *sp = dbcSpell.LookupEntryForced( spsk->spell );
				if( !sp )
					continue;
				//spells that are either talents or learned by talents
				if( sp->spell_learn_is_linked_to_talent == true && skip_talents == true )
					continue;
				//Zack : well some spells that are passively learned through talents should be added also ? Like paladin 
				//spell does not cost anything and it is instant cast. not sure if this is right but it is strange
/*				if( sp->manaCost == 0 && sp->ManaCostPercentage == 0 && sp->manaCostPerlevel == 0 && sp->manaPerSecond == 0 && sp->manaPerSecondPerLevel == 0 
					&& sp->RuneCostID == 0
					&& sp->CastingTimeIndex == 1 )
					continue;
				//abillity like skills are learned only last rank
				if( sp->powerType != POWER_TYPE_MANA && spsk->next )
				{
					removeSpell( spsk->spell, false, true,spsk->next);
					continue;
				}*/
				//some spells depend on race (seal of blood )
				//non class dependent skill spells are the talents or professions
				if( class_specific == true 
//					&& spsk->classMask	- add this if you want to learn talents too
					&& (spsk->classMask & getClassMask()) == 0 )
					continue;
				if( spsk->raceMask && (spsk->raceMask & getRaceMask() ) == 0 )
					continue;
				if( spsk->excludeRace != 0 && (spsk->excludeRace & getRaceMask() ) != 0 )
					continue;
				if(	spsk->excludeClass != 0 && (spsk->excludeClass & getClassMask() ) != 0 )
					continue;
				//spell does not depend on a level. talents and procs use this
				//if( sp->maxLevel == 0 )
				//	continue; 
			}
			addSpell( spsk->spell );
		}
	}
}

void Player::RemoveSpellsFromLine(uint32 skill_line)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 cnt = dbcSkillLineSpell.GetNumRows();
	for(uint32 i=0; i < cnt; i++)
	{
		skilllinespell * sp = dbcSkillLineSpell.LookupRow(i);
		if(sp)
		{
			if(sp->skilline == skill_line)
			{
				// Check ourselves for this spell, and remove it..
				if ( !removeSpell(sp->spell, 0, 0, 0) )
					// if we didnt unlearned spell check deleted spells
					removeDeletedSpell( sp->spell );
			}
		}
	}
}

void Player::CalcStat( uint32 type )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	int32 res;
	ASSERT( type < 5 );

	int32 pos = (int32)((int32)BaseStats[type] * (int32)StatModPctPos[type] ) / 100 + (int32)FlatStatModPos[type];
	int32 neg = (int32)((int32)BaseStats[type] * (int32)StatModPctNeg[type] ) / 100 + (int32)FlatStatModNeg[type];
	res = pos + (int32)BaseStats[type] - neg;
	if( res > 1 )
	{
		pos += ( res * (int32)SafePlayerCast( this )->TotalStatModPctPos[type] ) / 100;
		neg += ( res * (int32)SafePlayerCast( this )->TotalStatModPctNeg[type] ) / 100;
		res = pos + BaseStats[type] - neg;
	}
	else if( res <= 0 )
		res = 1;

	SetUInt32Value( UNIT_FIELD_POSSTAT0 + type, pos );
	SetUInt32Value( UNIT_FIELD_NEGSTAT0 + type, -neg );
	SetUInt32Value( UNIT_FIELD_STAT0 + type, res > 0 ?res : 0 );
	if( type == STAT_AGILITY )
	   CalcResistance( 0 );

	if( GetSummon() && ( type == STAT_STAMINA || type == STAT_INTELLECT ) )
		GetSummon()->CalcStat( type );//Re-calculate pet's too
}

void Player::RegenerateMana(bool is_interrupted)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//if (m_interruptRegen)
	//	return;

	uint32 time_diff = getMSTime() - last_mana_regen_stamp;
	last_mana_regen_stamp = getMSTime();
	uint32 cur = GetUInt32Value(UNIT_FIELD_POWER1);
	uint32 mm = GetUInt32Value(UNIT_FIELD_MAXPOWER1);
	if(cur >= mm)
	{ 
		return;
	}
	float amt;

	if( is_interrupted )
	{
		amt = GetFloatValue(UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER);
		amt *= time_diff*2/1000; //floats are Mana Regen Per Sec. Regen Applied every 2 secs so real value =X*2 . Shady
	}
	else
	{
		amt = GetFloatValue(UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER);
		amt *= time_diff*2/1000; //floats are Mana Regen Per Sec. Regen Applied every 2 secs so real value =X*2 . Shady
	}

	// !!!only experimental to see if it syncs better the client sided mana updated value!!!
//	amt *= 1.33f;	

	//Apply shit from conf file
	amt *= sWorld.getRate(RATE_POWER1);

	if((amt<=1.0)&&(amt>0))//this fixes regen like 0.98
	{
		if(is_interrupted)
		{ 
			return;
		}
		cur++;
	}
	else
		cur += float2int32(amt);	
	if( cur >= mm)
		cur = mm;
	SetUInt32Value(UNIT_FIELD_POWER1,cur);
	UpdatePowerAmm();
}

void Player::RegenetateRunicPower()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//if out of combat then we will start decreasing runic power aswell
	if( !CombatStatus.IsInCombat() )
	{
		if( GetUInt32Value( UNIT_FIELD_POWER7 ) )
		{
			if( GetUInt32Value( UNIT_FIELD_POWER7 ) < 25 )
				SetUInt32Value( UNIT_FIELD_POWER7, 0 );
			else 
				ModSignedInt32Value( UNIT_FIELD_POWER7, -25 );
			UpdatePowerAmm();
		}
	}
	else 
	{
		
		uint32 time_diff = getMSTime() - last_mana_regen_stamp;
		last_mana_regen_stamp = getMSTime();
		float amt = (float)m_ModInterrMRegen;
		if( !amt )
			return; //this only gets a value after some talent from Dk
		amt *= time_diff/1000; //we store stuff as regen per secs
		amt *= PctPowerRegenModifier[POWER_TYPE_RUNIC_POWER];	//not dead sure this is ok
		uint32 new_val = float2int32(amt) + GetUInt32Value(UNIT_FIELD_POWER7);	
		if( new_val >= GetUInt32Value(UNIT_FIELD_MAXPOWER7))
			new_val = GetUInt32Value(UNIT_FIELD_MAXPOWER7);
		SetUInt32Value(UNIT_FIELD_POWER7,new_val);
		UpdatePowerAmm();
	}
}

void Player::RegenerateHealth( bool inCombat )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 level = getLevel();
	if( level >= PLAYER_LEVEL_CAP_DBC )
		level = PLAYER_LEVEL_CAP_DBC;
	gtFloat* HPRegenBase = dbcHPRegenBase.LookupRow(level-1 + (getClass()-1)*100);
	gtFloat* HPRegen =  dbcHPRegen.LookupRow(level-1 + (getClass()-1)*100);

	uint32 cur = GetUInt32Value(UNIT_FIELD_HEALTH);
	uint32 mh = GetUInt32Value(UNIT_FIELD_MAXHEALTH);
	if(cur >= mh)
	{ 
		return;
	}

	float amt = (m_uint32Values[UNIT_FIELD_STAT4]*HPRegen->val+HPRegenBase->val*100) + RegenModifier;

	if (PctRegenModifier)
		amt+= (amt * PctRegenModifier) / 100;

	amt *= sWorld.getRate(RATE_HEALTH);//Apply shit from conf file
	//Near values from official
	// wowwiki: Health Regeneration is increased by 33% while sitting.
	if(m_isResting)
		amt = amt * 1.33f;

	if(inCombat)
		amt *= PctIgnoreRegenModifier;

	if(amt != 0)
	{
		if(amt > 0)
		{
			if(amt <= 1.0f)//this fixes regen like 0.98
				cur++;
			else
				cur += float2int32(amt);
			SetUInt32Value(UNIT_FIELD_HEALTH,(cur>=mh) ? mh : cur);
		}
		else
			DealDamage(this, float2int32(-amt), 0, 0, 0);
	}
}

void Player::LooseRage(int32 decayValue)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//Rage is lost at a rate of 3 rage every 3 seconds. 
	//The Anger Management talent changes this to 2 rage every 3 seconds.
	uint32 cur = GetUInt32Value(UNIT_FIELD_POWER2);
    uint32 newrage = ((int)cur <= decayValue) ? 0 : cur-decayValue;
    if (newrage > 1000 )
	  newrage = 1000;

    SetUInt32Value(UNIT_FIELD_POWER2,newrage);

	UpdatePowerAmm();
}

void Player::RegenerateEnergy()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 cur = GetUInt32Value(UNIT_FIELD_POWER4);
	uint32 mh = GetUInt32Value(UNIT_FIELD_MAXPOWER4);
	if(cur >= mh)
	{ 
		return;
	}
	float amt = 20.0f * PctPowerRegenModifier[POWER_TYPE_ENERGY];

	cur += float2int32(amt);
	SetUInt32Value(UNIT_FIELD_POWER4,(cur>=mh) ? mh : cur);

	UpdatePowerAmm();
}

//most of the time this should return 1
uint32 Player::GeneratePetNumber()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
/*
	awsome and not
	uint32 val = m_PetNumberMax + 1;
	for (uint32 i = 1; i < m_PetNumberMax; i++)
		if(m_Pets.find(i) == m_Pets.end())
			return i;					   // found a free one
			*/

	sWorld.Global_Pet_id++;
//	if( sWorld.Global_Pet_id == 0 )
//		sWorld.Global_Pet_id = 1;

	return sWorld.Global_Pet_id;
}

void Player::RemovePlayerPet(uint32 pet_number)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	std::map<uint32, PlayerPet*>::iterator itr = m_Pets.find(pet_number);
	if(itr != m_Pets.end())
	{
		delete itr->second;
		itr->second = NULL;
		m_Pets.erase(itr);
		EventDismissPet();
//		RemoveFlag(PLAYER_FIELD_BYTES,PLAYER_BYTES_FLAG_HAS_PET);
		//hmmm this should have been deleted elsewhere
		CharacterDatabase.Execute("DELETE FROM playerpetspells WHERE petnumber=%u and ownerguid=%u", pet_number,GetLowGUID());
	}
}
#ifndef CLUSTERING
void Player::_Relocate(uint32 mapid, const LocationVector & v, bool sendpending, bool force_new_world, uint32 instance_id)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//this func must only be called when switching between maps!
	WorldPacket data(41);
	if(sendpending && mapid != m_mapId && force_new_world)
	{
		data.SetOpcode(SMSG_TRANSFER_PENDING);
		data << mapid;
		GetSession()->SendPacket(&data);
	}

	if(m_mapId != mapid || force_new_world)
	{
		uint32 status = sInstanceMgr.PreTeleport(mapid, this, instance_id);
		if(status != INSTANCE_OK)
		{
			data.Initialize(SMSG_TRANSFER_ABORTED);
			data << mapid << status;
			GetSession()->SendPacket(&data);
			return;
		}

		if(instance_id)
			m_instanceId=instance_id;

		if(IsInWorld())
		{
			RemoveFromWorld();
		}

		data.Initialize(SMSG_NEW_WORLD);
		data << (uint32)mapid << v << v.o;
		GetSession()->SendPacket( &data );
		SetMapId(mapid);

	}
	else
	{
		// via teleport ack msg
		WorldPacket * data = BuildTeleportAckMsg(v);
		m_session->SendPacket(data);
		delete data;
		data = NULL;
	}
	SetPlayerStatus(TRANSFER_PENDING);
	m_sentTeleportPosition = v;
	SetPosition(v);
	SpeedCheatReset();

	z_axisposition = 0.0f;
	//Dismount before teleport
	if( m_MountSpellId )
		RemoveAura( m_MountSpellId );
}
#endif

// Player::AddItemsToWorld
// Adds all items to world, applies any modifiers for them.

void Player::AddItemsToWorld()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	Item * pItem;
	for(uint32 i = 0; i < MAX_INVENTORY_SLOT; i++)
	{
		pItem = GetItemInterface()->GetInventoryItem(i);
		if( pItem != NULL )
		{
			pItem->PushToWorld(m_mapMgr);
			
			if(i < INVENTORY_SLOT_BAG_END)	  // only equipment slots get mods.
			{
				_ApplyItemMods(pItem, i, true, false, true);
			}

			if(pItem->IsContainer() && GetItemInterface()->IsBagSlot(i))
			{
				for(uint32 e=0; e < pItem->GetProto()->ContainerSlots; e++)
				{
					Item *item = SafeContainerCast(pItem)->GetItem(e);
					if(item)
					{
						item->PushToWorld(m_mapMgr);
					}
				}
			}
		}
	}

	UpdateStats();
}

// Player::RemoveItemsFromWorld
// Removes all items from world, reverses any modifiers.

void Player::RemoveItemsFromWorld()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	Item * pItem;
	for(uint32 i = 0; i < MAX_INVENTORY_SLOT; i++)
	{
		pItem = m_ItemInterface->GetInventoryItem((int8)i);
		if(pItem)
		{
			if(pItem->IsInWorld())
			{
				if(i < EQUIPMENT_SLOT_END)	  // only equipment slots get mods.
				{
					_ApplyItemMods(pItem, i, false, false, true);
				}
				pItem->RemoveFromWorld();
			}
	
			if(pItem->IsContainer() && GetItemInterface()->IsBagSlot(i))
			{
				for(uint32 e=0; e < pItem->GetProto()->ContainerSlots; e++)
				{
					Item *item = SafeContainerCast(pItem)->GetItem(e);
					if(item && item->IsInWorld())
					{
						item->RemoveFromWorld();
					}
				}
			}
		}
	}

	UpdateStats();
}

uint32 Player::BuildCreateUpdateBlockForPlayer(ByteBuffer *data, Player *target )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	int count = 0;
	if(target == this)
	{
		// we need to send create objects for all items.
		count += GetItemInterface()->m_CreateForPlayer(data);
	}
	count += Unit::BuildCreateUpdateBlockForPlayer(data, target);
	return count;
}

void Player::Kick(uint32 delay /* = 0 */)
{
	if(!delay)
	{
		_Kick();
	} else {
		sChatHandler.BlueSystemMessageToPlr(this, "You will be removed from the server in %u seconds.", (uint32)(delay/1000));
		sEventMgr.AddEvent(this, &Player::_Kick, EVENT_PLAYER_KICK, 1000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
}

void Player::_Kick()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	sEventMgr.RemoveEvents(this, EVENT_PLAYER_KICK);
	// remove now
	GetSession()->LogoutPlayer(true);
}

void Player::ClearCategoryCooldownForSpell(uint32 spell_id)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// remove cooldown data from Server side lists
	PlayerCooldownMap::iterator itr, itr2;
	SpellEntry * spe = dbcSpell.LookupEntry(spell_id);
	if(!spe) 
	{ 
		return;
	}

	for( itr = m_cooldownMap[COOLDOWN_TYPE_CATEGORY].begin(); itr != m_cooldownMap[COOLDOWN_TYPE_CATEGORY].end(); )
	{
		itr2 = itr++;
		if( itr2->first == spe->Category )
			m_cooldownMap[COOLDOWN_TYPE_CATEGORY].erase( itr2 );
	}
	m_globalCooldown = 0;
}


void Player::ClearCooldownForSpell(uint32 spell_id)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
		//client side cooldown might be out of sync compared to server. Clear it even if we do not have cooldown 
	sStackWolrdPacket( data,SMSG_CLEAR_COOLDOWN, 16);
	data << spell_id << GetGUID();
	GetSession()->SendPacket(&data);

	// remove cooldown data from Server side lists
	PlayerCooldownMap::iterator itr, itr2;
	SpellEntry * spe = dbcSpell.LookupEntry(spell_id);
	if(!spe) 
	{ 
		return;
	}

	for(uint32 i = 0; i < NUM_COOLDOWN_TYPES; ++i)
	{
		for( itr = m_cooldownMap[i].begin(); itr != m_cooldownMap[i].end(); )
		{
			itr2 = itr++;
			if( ( i == COOLDOWN_TYPE_CATEGORY && itr2->first == spe->Category ) ||
				( i == COOLDOWN_TYPE_SPELL && itr2->first == spe->Id ) )
			{
				m_cooldownMap[i].erase( itr2 );
			}
		}
	}
}

void Player::ClearCooldownsOnLine(uint32 skill_line, uint32 called_from)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// found an easier way.. loop spells, check skill line
	SpellSet::const_iterator itr;
	for(itr = mSpells.begin(); itr != mSpells.end(); ++itr)
	{
		if((*itr) == called_from)	   // skip calling spell.. otherwise spammies! :D
			continue;

		SpellEntry *sp = dbcSpell.LookupEntryForced( (*itr) );
		if( sp == NULL || 
			( sp->spell_skilline[ 0 ] != skill_line
				&& sp->spell_skilline[ 1 ] != skill_line )
			)
			continue;

		ClearCooldownForSpell( sp->Id );
	}

	/*
	// this is better when on client side some spells get bugged cooldown and server would not clear cooldown for those.
	skilllinespell *sk;
	sk = dbcSkillLineSpell.LookupEntryForced( skill_line );
	if( sk )
	{
		SpellEntry *sp = dbcSpell.LookupEntryForced( sk->spell );
		while( sp )
		{
			ClearCooldownForSpell( sp->Id );
			sp = dbcSpell.LookupEntryForced( sp->spell_learn_next_level_spell );
		}
	}
	*/
}

//we could just iterate through player cooldowns but sometimes client has different info then server and cooldowns lock testing of new spells 
void Player::ResetAllCooldowns()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 guid = (uint32)GetSelection();

	switch(getClass())
	{
		case WARRIOR:
		{
			ClearCooldownsOnLine(26, guid);
			ClearCooldownsOnLine(256, guid);
			ClearCooldownsOnLine(257 , guid);
		} break;
		case PALADIN:
		{
			ClearCooldownsOnLine(594, guid);
			ClearCooldownsOnLine(267, guid);
			ClearCooldownsOnLine(184, guid);
		} break;
		case HUNTER:
		{
			ClearCooldownsOnLine(50, guid);
			ClearCooldownsOnLine(51, guid);
			ClearCooldownsOnLine(163, guid);
		} break;
		case ROGUE:
		{
			ClearCooldownsOnLine(253, guid);
			ClearCooldownsOnLine(38, guid);
			ClearCooldownsOnLine(39, guid);
		} break;
		case PRIEST:
		{
			ClearCooldownsOnLine(56, guid);
			ClearCooldownsOnLine(78, guid);
			ClearCooldownsOnLine(613, guid);
		} break;
		case SHAMAN:
		{
			ClearCooldownsOnLine(373, guid);
			ClearCooldownsOnLine(374, guid);
			ClearCooldownsOnLine(375, guid);
		} break;
		case MAGE:
		{
			ClearCooldownsOnLine(6, guid);
			ClearCooldownsOnLine(8, guid);
			ClearCooldownsOnLine(237, guid);
		} break;
		case WARLOCK:
		{
			ClearCooldownsOnLine(355, guid);
			ClearCooldownsOnLine(354, guid);
			ClearCooldownsOnLine(593, guid);
		} break;
		case DRUID:
		{
			ClearCooldownsOnLine(573, guid);
			ClearCooldownsOnLine(574, guid);
			ClearCooldownsOnLine(134, guid);
		} break;

		default: 
	return; break;
	}
}

//!!! if we update data for objects not created yet, sometimes client combat log breaks
void Player::PushUpdateData(ByteBuffer *data, uint32 updatecount)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( updatecount == 0 )
		return;

	// imagine the bytebuffer getting appended from 2 threads at once! :D
	_bufferS.Acquire();

	// unfortunately there is no guarantee that all data will be compressed at a ratio
	// that will fit into 2^16 bytes ( stupid client limitation on server packets )
	// so if we get more than 63KB of update data, force an update and then append it
	// to the clean buffer.
	if( (data->size() + bUpdateBuffer.size() ) >= MAX_SEND_BUFFER_SIZE_TO_SEND )
		ProcessPendingUpdates( true );	//avoid deadlocks

	mUpdateCount += updatecount;
	bUpdateBuffer.append(*data);

	// add to process queue
	if(m_mapMgr && !bProcessPending)
	{
		bProcessPending = true;
		m_mapMgr->PushToProcessed(this);
	}
	
	_bufferS.Release();
}

//!!! if we create and destroy data in the same packet then client will freak out and break combat log
void Player::PushOutOfRange(const WoWGuid & guid)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	_bufferS.Acquire();
	mOutOfRangeIds << guid;
	++mOutOfRangeIdCount;

	// add to process queue
	if(m_mapMgr && !bProcessPending)
	{
		bProcessPending = true;
		m_mapMgr->PushToProcessed(this);
	}
	_bufferS.Release();
}

void Player::PushCreationData(ByteBuffer *data, uint32 updatecount)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( updatecount == 0 )
		return;

    // imagine the bytebuffer getting appended from 2 threads at once! :D
	_bufferS.Acquire();

	// unfortunately there is no guarantee that all data will be compressed at a ratio
	// that will fit into 2^16 bytes ( stupid client limitation on server packets )
	// so if we get more than 63KB of update data, force an update and then append it
	// to the clean buffer.
	if( (data->size() + bCreationBuffer.size() + mOutOfRangeIds.size() ) >= MAX_SEND_BUFFER_SIZE_TO_SEND )
		ProcessPendingUpdates( true );

	mCreationCount += updatecount;
	bCreationBuffer.append(*data);

	// add to process queue
	if(m_mapMgr && !bProcessPending)
	{
		bProcessPending = true;
		m_mapMgr->PushToProcessed(this);
	}
	
	_bufferS.Release();

}

void Player::ProcessPendingUpdates(bool skip_lock)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( skip_lock == false )
		_bufferS.Acquire();
    if(!bUpdateBuffer.size() && !mOutOfRangeIds.size() && !bCreationBuffer.size())
	{
		if( skip_lock == false )
			_bufferS.Release();
		return;
	}

	size_t destroy_size = mOutOfRangeIds.size() * 8 + 4 + 1; //well aprox
	size_t create_size = bCreationBuffer.size();
	size_t updates_size = bUpdateBuffer.size();
	size_t c;
#ifdef CATACLYSM_SUPPORT
	#define BLOCKCOUNT_INDEX 2
	#define BLOCKCOUNT_CONTENT_INDEX 6
	*(uint32*)&update_buffer[ 0 ] = 0; // cromon says this is mapid. Does anyone care ?
#else
	#define BLOCKCOUNT_INDEX 0
	#define BLOCKCOUNT_CONTENT_INDEX 4
#endif
	c = BLOCKCOUNT_CONTENT_INDEX;

    *(uint32*)&update_buffer[ BLOCKCOUNT_INDEX ] = 0;	

	//add x type of blocks
	//the part that really sucks about this is sending destroy before create. Client freaks out about these :(
	//somehow we should not send/destroy at all
	if( mOutOfRangeIdCount 
		//i wonder if this will be possible at all :(
//		&& bCreationBuffer.size() == 0
//		&& bUpdateBuffer.size() == 0
		)
	{
		*(uint32*)&update_buffer[ BLOCKCOUNT_INDEX ]	+= 1;
		update_buffer[c]								= UPDATETYPE_OUT_OF_RANGE_OBJECTS;			 ++c;
		*(uint32*)&update_buffer[c]						= mOutOfRangeIdCount;						  c += 4;
	    memcpy(&update_buffer[c], mOutOfRangeIds.contents(), mOutOfRangeIds.size());   c += mOutOfRangeIds.size();
	    mOutOfRangeIds.clear();
	    mOutOfRangeIdCount = 0;
	}

	//check if we could add another type of blocks
	if( c + bCreationBuffer.size() >= MAX_SEND_BUFFER_SIZE_TO_SEND )
	{
	    if(c < (size_t)sWorld.compression_threshold || !CompressAndSendUpdateBuffer((uint32)c, update_buffer))
		    m_session->OutPacket(SMSG_UPDATE_OBJECT, (uint16)c, update_buffer);// send uncompressed packet -> because we failed
		c = BLOCKCOUNT_CONTENT_INDEX;
		*(uint32*)&update_buffer[ BLOCKCOUNT_INDEX ]	= 0;
	}

	//add x type of blocks
	if( bCreationBuffer.size() )
    {
		*(uint32*)&update_buffer[ BLOCKCOUNT_INDEX ]	+= mCreationCount;
		memcpy(&update_buffer[c], bCreationBuffer.contents(), bCreationBuffer.size());  c += bCreationBuffer.size();
	    bCreationBuffer.clear();
	    mCreationCount = 0;
    }

	//check if we could add another type of blocks
	if( c + bUpdateBuffer.size() >= MAX_SEND_BUFFER_SIZE_TO_SEND )
//		if( c > 4 )
	{
	    if(c < (size_t)sWorld.compression_threshold || !CompressAndSendUpdateBuffer((uint32)c, update_buffer))
		    m_session->OutPacket(SMSG_UPDATE_OBJECT, (uint16)c, update_buffer);// send uncompressed packet -> because we failed
		c = BLOCKCOUNT_CONTENT_INDEX;
		*(uint32*)&update_buffer[ BLOCKCOUNT_INDEX ]	= 0;
	}

	if(bUpdateBuffer.size())
	{
		*(uint32*)&update_buffer[ BLOCKCOUNT_INDEX ]	+= mUpdateCount;
		memcpy(&update_buffer[c], bUpdateBuffer.contents(), bUpdateBuffer.size());  c += bUpdateBuffer.size();
		bUpdateBuffer.clear();
		mUpdateCount = 0;
	}

	// compress update packet
	// while we said 350 before, i'm gonna make it 500 :D
	if( c > BLOCKCOUNT_CONTENT_INDEX )
		if( c < (size_t)sWorld.compression_threshold || !CompressAndSendUpdateBuffer((uint32)c, update_buffer))
				m_session->OutPacket(SMSG_UPDATE_OBJECT, (uint16)c, update_buffer);// send uncompressed packet -> because we failed
	
	bProcessPending = false;
	if( skip_lock == false )
		_bufferS.Release();
//	delete [] update_buffer;

	// send any delayed packets
	WorldPacket * pck;
	while(delayedPackets.size())
	{
		pck = delayedPackets.next();
		//printf("Delayed packet opcode %u sent.\n", pck->GetOpcode());
		m_session->SendPacket(pck);
		delete pck;
	}

	// resend speed if needed
	if(resend_speed)
	{
		SetPlayerSpeed(RUN, m_runSpeed);
		SetPlayerSpeed(FLY, m_flySpeed);
		resend_speed=false;
	}
}

bool Player::CompressAndSendUpdateBuffer(uint32 size, const uint8* update_buffer)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( size == 0 )
		return true;

	//reset deflate variables
	deflateReset( &zlib_stream );

	// set up zlib_stream pointers
	zlib_stream.next_out  = (Bytef*)zlib_update_buffer+4;
	zlib_stream.avail_out = MAX_SEND_BUFFER_SIZE;
	zlib_stream.next_in   = (Bytef*)update_buffer;
	zlib_stream.avail_in  = size;

	//deflate
	int ret = deflate(&zlib_stream, Z_FINISH); 

	//for some strange reason we did not manage to deflate it : destination buffer too small probably
	if( ret != Z_STREAM_END ) 
	{
		ASSERT( 0 );
		return false;
	}

	ASSERT( zlib_stream.avail_out != 0 && zlib_stream.avail_in == 0 );

	//check if we got an even larger output then input. If so then we send it uncompressed
	if( zlib_stream.total_out + 4 > size ) 
		return false;

	// fill in the full size of the compressed stream
	*(uint32*)&zlib_update_buffer[0] = size;

	// send it
	m_session->OutPacket(SMSG_COMPRESSED_UPDATE_OBJECT, (uint16)zlib_stream.total_out + 4, zlib_update_buffer);

	return true;
}

void Player::ClearAllPendingUpdates()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	_bufferS.Acquire();
	bProcessPending = false;
	mUpdateCount = 0;
	bUpdateBuffer.clear();
	_bufferS.Release();
}

void Player::AddSplinePacket(uint64 guid, ByteBuffer* packet)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SplineMap::iterator itr = _splineMap.find(guid);
	if(itr != _splineMap.end())
	{
		delete itr->second;
		itr->second = NULL;
		_splineMap.erase(itr);
	}
	_splineMap.insert( SplineMap::value_type( guid, packet ) );
}

ByteBuffer* Player::GetAndRemoveSplinePacket(uint64 guid)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SplineMap::iterator itr = _splineMap.find(guid);
	if(itr != _splineMap.end())
	{
		ByteBuffer *buf = itr->second;
		_splineMap.erase(itr);
		return buf;
	}
	return NULL;
}

void Player::ClearSplinePackets()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SplineMap::iterator it2;
	for(SplineMap::iterator itr = _splineMap.begin(); itr != _splineMap.end();)
	{
		it2 = itr;
		++itr;
		delete it2->second;
		it2->second = NULL;
		_splineMap.erase(it2);
	}
	_splineMap.clear();
}



bool Player::ExitInstance()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(!m_bgEntryPointX)
	{ 
		return false;
	}

	RemoveFromWorld();

	SafeTeleport(m_bgEntryPointMap, m_bgEntryPointInstance, LocationVector(
		m_bgEntryPointX, m_bgEntryPointY, m_bgEntryPointZ, m_bgEntryPointO));

	return true;
}

void Player::SaveEntryPoint(uint32 mapId)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	
	if(IS_INSTANCE(GetMapId()))
		return; // dont save if we're not on the main continent.
	//otherwise we could end up in an endless loop :P
	MapInfo * pMapinfo = WorldMapInfoStorage.LookupEntry(mapId);

	if(pMapinfo)
	{
		m_bgEntryPointX = pMapinfo->repopx;
		m_bgEntryPointY = pMapinfo->repopy;
		m_bgEntryPointZ = pMapinfo->repopz;
		m_bgEntryPointO = GetOrientation();
		m_bgEntryPointMap = pMapinfo->repopmapid;
		m_bgEntryPointInstance = GetInstanceID();
	}
	else
	{
		m_bgEntryPointMap	 = 0;
		m_bgEntryPointX		 = 0;	
		m_bgEntryPointY		 = 0;
		m_bgEntryPointZ		 = 0;
		m_bgEntryPointO		 = 0;
		m_bgEntryPointInstance  = 0;
	}
}

void Player::CleanupGossipMenu()
{
	if(CurrentGossipMenu)
	{
		delete CurrentGossipMenu;
		CurrentGossipMenu = NULL;
	}
}

void Player::Gossip_Complete()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	GetSession()->OutPacket(SMSG_GOSSIP_COMPLETE, 0, NULL);
	CleanupGossipMenu();
}


void Player::CloseGossip()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	Gossip_Complete();
}

void Player::PrepareQuestMenu(uint64 guid )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 TextID = 820;
    objmgr.CreateGossipMenuForPlayer(&PlayerTalkClass, guid, TextID, this);
}

void Player::SendGossipMenu( uint32 TitleTextId, uint64 npcGUID )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	PlayerTalkClass->SetTextID(TitleTextId);
	PlayerTalkClass->SendTo(this);
}

QuestStatus Player::GetQuestStatus( uint32 quest_id )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 status = sQuestMgr.CalcQuestStatus( this, quest_id);
	switch (status)
	{
		case QMGR_QUEST_NOT_FINISHED: 
	return QUEST_STATUS_INCOMPLETE;
		case QMGR_QUEST_FINISHED: 
	return QUEST_STATUS_COMPLETE;
		case QMGR_QUEST_NOT_AVAILABLE: 
	return QUEST_STATUS_UNAVAILABLE;
	}
	return QUEST_STATUS_UNAVAILABLE;
}


void Player::EventZoneChange(uint32 ZoneId)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	bool is_new_zone = ( m_zoneId != ZoneId );
	uint32 oldzone = m_zoneId;
	m_zoneId = ZoneId;

	/* how the f*ck is this happening */
	if( m_playerInfo == NULL )
	{
		m_playerInfo = objmgr.GetPlayerInfo(GetLowGUID());
		if( m_playerInfo == NULL )
		{
			SoftDisconnect();
			return;
		}
	}

	if( is_new_zone )
		UpdatePvPArea( false );

	m_playerInfo->lastZone = ZoneId;
	sHookInterface.OnZone(this, ZoneId);
	CALL_INSTANCE_SCRIPT_EVENT( m_mapMgr, OnZoneChange )( this, ZoneId, oldzone );

	//only zones have category value set
	AreaTable * at = dbcArea.LookupEntry( ZoneId );
	if(at && (at->category == AREAC_SANCTUARY || (at->AreaFlags & AREA_SANCTUARY) ) )
	{
		Unit * pUnit = (GetSelection() == 0) ? 0 : (m_mapMgr ? m_mapMgr->GetUnit(GetSelection()) : 0);
		if(pUnit && DuelingWith != pUnit)
		{
			EventAttackStop();
			smsg_AttackStop(pUnit);
		}

		if(m_currentSpell)
		{
			Unit * target = m_currentSpell->GetUnitTarget();
			if(target && target != DuelingWith && target != this)
				m_currentSpell->cancel();
		}
	}

	// zone might change on area change. Sometimes new ZoneID = 0 so we use ZoneID = AreaId. 
	// chat changes based on what zone we stand. Some Areas belong to no zone, those are base zones and not areas
	// change to zone name, not area name. Find area for this zone
	if( !m_channels.empty() && at )
	{
		// leave channels that are for this zone (area ? ) and join new ones
		std::set<Channel*>::iterator itr,nextitr;
		for( nextitr = m_channels.begin() ; nextitr != m_channels.end() ;)
		{
			itr = nextitr;
			++nextitr;
			Channel * chn;
			chn = (*itr);
			// Check if this is a custom channel (i.e. global)
			if( !( chn->m_flags & 0x10 ) )
				continue;

			if( chn->m_flags & 0x40 ) // LookingForGroup - constant among all zones
				continue;

			char updatedName[95];
			ChatChannelDBC * pDBC;
			pDBC = dbcChatChannels.LookupEntryForced( chn->m_id );
			if( !pDBC )
			{
				Log.Error( "ChannelMgr" , "Invalid channel entry %u for %s" , chn->m_id , chn->m_name.c_str() );
				return;
			}
			snprintf( updatedName , 95 , pDBC->name_pattern[0] , at->name );
			Channel * newChannel = channelmgr.GetCreateChannel( updatedName , this , chn->m_id );
			if( newChannel == NULL )
			{
				Log.Error( "ChannelMgr" , "Could not create channel %s!" , updatedName );
				return; // whoops?
			}
			//Log.Notice( "ChannelMgr" , "LEAVING CHANNEL %s" , chn->m_name.c_str() );
			//Log.Notice( "ChannelMgr" , "JOINING CHANNEL %s" , newChannel->m_name.c_str() );
			if( chn != newChannel ) // perhaps there's no need
			{
				Log.Debug("ChannelJoin", "%s", updatedName);
				// join new channel
				newChannel->AttemptJoin( this , "", true );
				// leave the old channel
				chn->Part( this , true );
			}
		}
	}
	RemoveAurasByZoneChange();
}

void Player::SendTradeUpdate()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	Player * pTarget = GetTradeTarget();
	if( !pTarget )
	{ 
		return;
	}

	WorldPacket data( SMSG_TRADE_STATUS_EXTENDED, 532 );
	/*data << uint8(1);
	data << uint32(2) << uint32(2);
	data << mTradeGold << uint32(0);*/
	data << uint8(1);
	data << uint32(0x19);
	data << m_tradeSequence;
	data << m_tradeSequence++;
	data << mTradeGold << uint32(0);
	
	uint8 count = 0;
	// Items
	for( uint32 Index = 0; Index < 7; ++Index )
	{
		Item * pItem = mTradeItems[ Index ];
		if(pItem != 0)
		{
			count++;
			ItemPrototype * pProto = pItem->GetProto();
			ASSERT( pProto != 0 );

			data << uint8( Index );

			data << pProto->ItemId;
			data << pProto->DisplayInfoID;
			data << pItem->GetUInt32Value( ITEM_FIELD_STACK_COUNT );	// Amount		   OK
			
			// Enchantment stuff
			data << uint32(0);											// unknown
			data << pItem->GetUInt64Value( ITEM_FIELD_GIFTCREATOR );	// gift creator	 OK
			data << pItem->GetUInt32Value( ITEM_FIELD_ENCHANTMENT_1_1 );	// Item Enchantment OK
			for( uint8 i = 2; i < 5; i++ )								// Gem enchantments
			{
				if( pItem->GetEnchantment(i) != NULL && pItem->GetEnchantment(i)->Enchantment != NULL )
					data << pItem->GetEnchantment(i)->Enchantment->Id;
				else 
					data << uint32( 0 );
			}
			data << pItem->GetUInt64Value( ITEM_FIELD_CREATOR );		// item creator	 OK
			data << pItem->GetUInt32Value( ITEM_FIELD_SPELL_CHARGES );	// Spell Charges	OK

			data << uint32( pItem->GetItemRandomSuffixFactor() );		// seems like time stamp or something like that
			data << pItem->GetUInt32Value( ITEM_FIELD_RANDOM_PROPERTIES_ID );
			data << pProto->LockId;										// lock ID		  OK
			data << pItem->GetUInt32Value( ITEM_FIELD_MAXDURABILITY );
			data << pItem->GetUInt32Value( ITEM_FIELD_DURABILITY );
		}
	}
	data.resize( 21 + count * 73 );
	pTarget->GetSession()->SendPacket(&data);
}

void Player::RequestDuel(Player *pTarget)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// We Already Dueling or have already Requested a Duel

	if( DuelingWith != NULL )
	{ 
		return;
	}

	if( m_duelState != DUEL_STATE_FINISHED )
	{ 
		return;
	}

	SetDuelState( DUEL_STATE_REQUESTED );

	//Setup Duel
	pTarget->DuelingWith = this;
	DuelingWith = pTarget;

	//Get Flags position
	float dist = CalcDistance(pTarget);
	dist = dist * 0.5f; //half way
	float x = (GetPositionX() + pTarget->GetPositionX()*dist)/(1+dist) + cos(GetOrientation()+(float(M_PI)/2))*2;
	float y = (GetPositionY() + pTarget->GetPositionY()*dist)/(1+dist) + sin(GetOrientation()+(float(M_PI)/2))*2;
	float z = (GetPositionZ() + pTarget->GetPositionZ()*dist)/(1+dist);

	//Create flag/arbiter
	GameObject* pGameObj = GetMapMgr()->CreateGameObject(21680);
	pGameObj->CreateFromProto(21680,GetMapId(), x, y, z, GetOrientation());
	pGameObj->SetInstanceID(GetInstanceID());

	//Spawn the Flag
	pGameObj->SetUInt64Value(OBJECT_FIELD_CREATED_BY, GetGUID());
	pGameObj->SetUInt32Value(GAMEOBJECT_FACTION, GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
	pGameObj->SetUInt32Value(GAMEOBJECT_LEVEL, GetUInt32Value(UNIT_FIELD_LEVEL));

	//Assign the Flag 
	SetUInt64Value(PLAYER_DUEL_ARBITER,pGameObj->GetGUID());
	pTarget->SetUInt64Value(PLAYER_DUEL_ARBITER,pGameObj->GetGUID());

	pGameObj->PushToWorld(m_mapMgr);

	WorldPacket data(SMSG_DUEL_REQUESTED, 16);
	data << pGameObj->GetGUID();
	data << GetGUID();
	pTarget->GetSession()->SendPacket(&data);
}

void Player::DuelCountdown()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( DuelingWith == NULL )
	{ 
		return;
	}

	m_duelCountdownTimer -= 1000;

	if( m_duelCountdownTimer < 0 )
		m_duelCountdownTimer = 0;

	if( m_duelCountdownTimer == 0 )
	{
		// Start Duel.
		SetUInt32Value( UNIT_FIELD_POWER2, 0 );
		DuelingWith->SetUInt32Value( UNIT_FIELD_POWER2, 0 );

		//Give the players a Team
		DuelingWith->SetUInt32Value( PLAYER_DUEL_TEAM, 1 ); // Duel Requester
		SetUInt32Value( PLAYER_DUEL_TEAM, 2 );

		SetDuelState( DUEL_STATE_STARTED );
		DuelingWith->SetDuelState( DUEL_STATE_STARTED );

		sEventMgr.RemoveEvents( this, EVENT_PLAYER_DUEL_BOUNDARY_CHECK );
		sEventMgr.AddEvent( this, &Player::DuelBoundaryTest, EVENT_PLAYER_DUEL_BOUNDARY_CHECK, 500, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
		sEventMgr.RemoveEvents( DuelingWith, EVENT_PLAYER_DUEL_BOUNDARY_CHECK );
		sEventMgr.AddEvent( DuelingWith, &Player::DuelBoundaryTest, EVENT_PLAYER_DUEL_BOUNDARY_CHECK, 500, 0, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
	}
}

void Player::DuelBoundaryTest()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//check if in bounds
	if(!IsInWorld())
	{ 
		return;
	}

	GameObject * pGameObject = GetMapMgr()->GetGameObject( GetUInt64Value(PLAYER_DUEL_ARBITER) );
	if(!pGameObject)
	{
		EndDuel(DUEL_WINNER_RETREAT);
		return;
	}

	float Dist = CalcDistance(pGameObject);

	if(Dist > 75.0f)
	{
		// Out of bounds
		if(m_duelStatus == DUEL_STATUS_OUTOFBOUNDS)
		{
			// we already know, decrease timer by 500
			m_duelCountdownTimer -= 500;
			if(m_duelCountdownTimer == 0)
			{
				// Times up :p
				DuelingWith->EndDuel(DUEL_WINNER_RETREAT);
			}
		}
		else
		{
			// we just went out of bounds
			// set timer
			m_duelCountdownTimer = 10000;

			// let us know
#ifdef USING_BIG_ENDIAN
			uint32 swapped = swap32(m_duelCountdownTimer);
			m_session->OutPacket(SMSG_DUEL_OUTOFBOUNDS, 4, &swapped);
#else
			m_session->OutPacket(SMSG_DUEL_OUTOFBOUNDS, 4, &m_duelCountdownTimer);
#endif
			m_duelStatus = DUEL_STATUS_OUTOFBOUNDS;
		}
	}
	else
	{
		// we're in range
		if(m_duelStatus == DUEL_STATUS_OUTOFBOUNDS)
		{
			// just came back in range
			m_session->OutPacket(SMSG_DUEL_INBOUNDS);
			m_duelStatus = DUEL_STATUS_INBOUNDS;
		}
	}
}

void Player::EndDuel(uint8 WinCondition)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( m_duelState == DUEL_STATE_FINISHED )
	{
		//if loggingout player requested a duel then we have to make the cleanups
		if( GetUInt32Value(PLAYER_DUEL_ARBITER) )
		{
			GameObject* arbiter = m_mapMgr ? GetMapMgr()->GetGameObject( GetUInt64Value(PLAYER_DUEL_ARBITER) ) : 0;

			if( arbiter != NULL )
			{
				arbiter->RemoveFromWorld( true );
				sGarbageCollection.AddObject( arbiter );
				arbiter = NULL;
			}
		}
		//we do not wish to lock the other player in duel state
		if( DuelingWith )
		{
			DuelingWith->SetUInt64Value( PLAYER_DUEL_ARBITER, 0 );
			DuelingWith->SetUInt32Value( PLAYER_DUEL_TEAM, 0 );
			DuelingWith->DuelingWith = NULL;
			sEventMgr.RemoveEvents( DuelingWith, EVENT_PLAYER_DUEL_BOUNDARY_CHECK );
			sEventMgr.RemoveEvents( DuelingWith, EVENT_PLAYER_DUEL_COUNTDOWN );
		}
		SetUInt64Value( PLAYER_DUEL_ARBITER, 0 );
		SetUInt32Value( PLAYER_DUEL_TEAM, 0 );
		DuelingWith = NULL;
		//the duel did not start so we are not in combat or cast any spells yet.
		return;
	}

	// Remove the events
	sEventMgr.RemoveEvents( this, EVENT_PLAYER_DUEL_COUNTDOWN );
	sEventMgr.RemoveEvents( this, EVENT_PLAYER_DUEL_BOUNDARY_CHECK );

	for( uint32 x = 0; x < MAX_AURAS; ++x )
	{
		if( m_auras[x] == NULL )
			continue;
		if( m_auras[x]->WasCastInDuel() )
			m_auras[x]->Remove();
	}

	m_duelState = DUEL_STATE_FINISHED;

	if( DuelingWith == NULL )
	{ 
		return;
	}

	sEventMgr.RemoveEvents( DuelingWith, EVENT_PLAYER_DUEL_BOUNDARY_CHECK );
	sEventMgr.RemoveEvents( DuelingWith, EVENT_PLAYER_DUEL_COUNTDOWN );

	// spells waiting to hit
	sEventMgr.RemoveEvents(this, EVENT_SPELL_DAMAGE_HIT);

	for( uint32 x = 0; x < MAX_AURAS; ++x )
	{
		if( DuelingWith->m_auras[x] == NULL )
			continue;
		if( DuelingWith->m_auras[x]->WasCastInDuel() )
			DuelingWith->m_auras[x]->Remove();
	}

	DuelingWith->m_duelState = DUEL_STATE_FINISHED;

	if( WinCondition == DUEL_WINNER_KNOCKOUT )	//retreat is loose condition
		Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_WIN_DUEL,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
	else
		Event_Achiement_Received( ACHIEVEMENT_CRITERIA_TYPE_LOSE_DUEL,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
#ifdef GENERATE_CLASS_BALANCING_STATISTICS
	if( WinCondition == DUEL_WINNER_KNOCKOUT 
		&& getLevel() == DuelingWith->getLevel() 
		&& getClass() != DuelingWith->getClass()
		&& GetHealthPct() < 75	//we received some DMG, this was not some : test my skills and you die fight
		)
	{
			//players should have similar gear - 100 means they have very similar gear score
			int32 plr1_str = item_level_sum / ( item_count_sum + 1 );
			int32 plr2_str = DuelingWith->item_level_sum / ( DuelingWith->item_count_sum + 1 );
			float difference_pct_score1 = ( (float)abs(plr1_str - plr2_str) / (float)( plr1_str + plr2_str + 1 ) );
			//no naked player testing dmg on other
			if( difference_pct_score1 <= 0.25 )
				CharacterDatabase.Execute("Update war_balancer set c=c+5 where A=%d and v=%d",getClass(),DuelingWith->getClass());
	}
#endif

	//Announce Winner
	WorldPacket data( SMSG_DUEL_WINNER, 500 );
	data << uint8( WinCondition );
	data << GetName() << DuelingWith->GetName();
	SendMessageToSet( &data, true );

	data.Initialize( SMSG_DUEL_COMPLETE );
	data << uint8( 1 );
	SendMessageToSet( &data, true );

	//Clear Duel Related Stuff

	GameObject* arbiter = m_mapMgr ? GetMapMgr()->GetGameObject( GetUInt64Value(PLAYER_DUEL_ARBITER) ) : 0;

	if( arbiter != NULL )
	{
		arbiter->RemoveFromWorld( true );
		sGarbageCollection.AddObject( arbiter );
		arbiter = NULL;
	}

	SetUInt64Value( PLAYER_DUEL_ARBITER, 0 );
	DuelingWith->SetUInt64Value( PLAYER_DUEL_ARBITER, 0 );

	SetUInt32Value( PLAYER_DUEL_TEAM, 0 );
	DuelingWith->SetUInt32Value( PLAYER_DUEL_TEAM, 0 );

	EventAttackStop();
	DuelingWith->EventAttackStop();

	// Call off pet
	if( this->GetSummon() != NULL )
	{
		this->GetSummon()->CombatStatus.Vanished();
		this->GetSummon()->GetAIInterface()->SetUnitToFollow( this );
		this->GetSummon()->GetAIInterface()->HandleEvent( EVENT_FOLLOWOWNER, this->GetSummon(), 0 );
		this->GetSummon()->GetAIInterface()->WipeTargetList();
	}

	// removing auras that kills players after if low HP
	/*RemoveNegativeAuras(); NOT NEEDED. External targets can always gank both duelers with DoTs. :D
	DuelingWith->RemoveNegativeAuras();*/
	RemoveDuelAuras();
	DuelingWith->RemoveDuelAuras();

	//Stop Players attacking so they don't kill the other player
	m_session->OutPacket( SMSG_CANCEL_COMBAT );
	DuelingWith->m_session->OutPacket( SMSG_CANCEL_COMBAT );

	smsg_AttackStop( DuelingWith );
	DuelingWith->smsg_AttackStop( this );

	DuelingWith->m_duelCountdownTimer = 0;
	m_duelCountdownTimer = 0;

	DuelingWith->DuelingWith = NULL;
	DuelingWith = NULL;
}

void Player::StopMirrorTimer(uint32 Type)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
#ifdef USING_BIG_ENDIAN
	uint32 swapped = swap32(Type);
	m_session->OutPacket(SMSG_STOP_MIRROR_TIMER, 4, &swapped);
#else
	m_session->OutPacket(SMSG_STOP_MIRROR_TIMER, 4, &Type);
#endif
}

void Player::EventTeleport(uint32 mapid, float x, float y, float z)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SafeTeleport(mapid, 0, LocationVector(x, y, z));
}

void Player::EventTeleportTaxi(uint32 mapid, float x, float y, float z)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(mapid == 530 && !m_session->HasFlag(ACCOUNT_FLAG_XPACK_01 | ACCOUNT_FLAG_XPACK_02))
	{
		WorldPacket msg(SMSG_MOTD, 50);
		msg << uint32(3) << "You must have The Burning Crusade Expansion to access this content." << uint8(0);
		m_session->SendPacket(&msg);
		RepopAtGraveyard(GetPositionX(), GetPositionY(), GetPositionZ(), GetMapId());
		return;
	}
	if(mapid == 571 && !m_session->HasFlag(ACCOUNT_FLAG_XPACK_02))
	{
		WorldPacket msg(SMSG_MOTD, 50);
		msg << uint32(3) << "You must have The Wrath Of The Lich King Expansion to access this content." << uint8(0);
		m_session->SendPacket(&msg);
		RepopAtGraveyard(GetPositionX(), GetPositionY(), GetPositionZ(), GetMapId());
		return;
	}
	_Relocate(mapid, LocationVector(x, y, z), (mapid==GetMapId() ? false:true), true, 0);
	_EventExploration();
}

void Player::ApplyLevelInfo(LevelInfo* Info, uint32 Level)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint8 class_ = getClass();
	ASSERT(Info != NULL);

	// Apply level
	SetUInt32Value(UNIT_FIELD_LEVEL, Level);

	// Set next level conditions
	SetUInt32Value(PLAYER_NEXT_LEVEL_XP, Info->XPToNextLevel);

	// Set stats
	for(uint32 i = 0; i < 5; ++i)
	{
		BaseStats[i] = Info->Stat[i];
		CalcStat(i);
	}

	// Set health / mana
	SetUInt32Value(UNIT_FIELD_HEALTH, Info->HP);
	SetUInt32Value(UNIT_FIELD_MAXHEALTH, Info->HP);
	SetUInt32Value(UNIT_FIELD_POWER1, Info->Mana);
	SetUInt32Value(UNIT_FIELD_MAXPOWER1, Info->Mana);

	// Calculate talentpoints
	uint32 TalentPoints = 0;
	/*
	if(Level >= 10)
		TalentPoints = Level - 9;
	*/

	/* lvl55 Deathknights don't have talentpoints */

	uint32 lev=getLevel();
	int32 new_points;
	if(lev>9)
		new_points = lev - 9 + m_Talent_point_mods;
	else 
		new_points = 0 + m_Talent_point_mods;

	if( new_points < 0 )
		new_points = 0; //DK have -46 points at the start and they get them from quests.

	SetUInt32Value(PLAYER_CHARACTER_POINTS1, new_points ); 


	// Set base fields
	SetUInt32Value(UNIT_FIELD_BASE_HEALTH, Info->HP);
	SetUInt32Value(UNIT_FIELD_BASE_MANA, Info->Mana);

	_UpdateMaxSkillCounts();
	UpdateStats();
	//UpdateChances();	
	m_playerInfo->lastLevel = Level;

	sLog.outDetail("Player %s set parameters to level %u", GetName(), Level);
}

void Player::BroadcastMessage(const char* Format, ...)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	va_list l;
	va_start(l, Format);
	char Message[1024];
	vsnprintf(Message, 1024, Format, l);
	va_end(l);

	WorldPacket * data = sChatHandler.FillSystemMessageData(Message);
	m_session->SendPacket(data);
	delete data;
	data = NULL;
}
/*
const double BaseRating []= {
	2.5,//weapon_skill_ranged!!!!
	1.5,//defense=comba_r_1
	12,//dodge
	20,//parry=3
	5,//block=4
	10,//melee hit
	10,//ranged hit
	8,//spell hit=7
	14,//melee critical strike=8
	14,//ranged critical strike=9
	14,//spell critical strike=10
	0,//
	0,
	0,
	25,//resilience=14
	25,//resil .... meaning unknown
	25,//resil .... meaning unknown
	10,//MELEE_HASTE_RATING=17
	10,//RANGED_HASTE_RATING=18
	10,//spell_haste_rating = 19???
	2.5,//melee weapon skill==20
	2.5,//melee second hand=21

};
*/
float Player::CalcRating( uint32 index )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 relative_index = index - (PLAYER_FIELD_COMBAT_RATING_1);
	float rating = float(m_uint32Values[index]);
	/*if( relative_index <= 10 || ( relative_index >= 14 && relative_index <= 21 ) )
	{
		double rating = (double)m_uint32Values[index];
		int level = getLevel();
		if( level < 10 )//this is not dirty fix -> it is from wowwiki
			level = 10;
		double cost;
		if( level < 60 )
			cost = ( double( level ) - 8.0 ) / 52.0;
		else
			cost = 82.0 / ( 262.0 - 3.0 *  double( level ) );
		return float( rating / ( BaseRating[relative_index] * cost ) );
	}
	else
		return 0.0f;*/

	uint32 level = m_uint32Values[UNIT_FIELD_LEVEL];
	if( level > 100 )
		level = 100;

//	CombatRatingDBC * pDBCEntry = dbcCombatRating.LookupEntryForced( relative_index * 100 + level - 1 );
	CombatRatingDBC * pDBCEntry = dbcCombatRating.LookupRow( relative_index * 100 + level - 1 );
	if( pDBCEntry == NULL )
		return rating;
	else
	{
		float trating;
		if( index == PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE || index == PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE || index == PLAYER_RATING_MODIFIER_RANGED_CRIT_RESILIENCE )
			trating = MIN( 1200, rating );
		else
			trating = rating;
		return (trating / pDBCEntry->val);
	}
}

bool Player::SafeTeleport(uint32 MapID, uint32 InstanceID, float X, float Y, float Z, float O)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	return SafeTeleport(MapID, InstanceID, LocationVector(X, Y, Z, O));
}

bool Player::SafeTeleport(uint32 MapID, uint32 InstanceID, const LocationVector & vec)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SpeedCheatDelay( 2000 );
	if ( GetTaxiState() )
	{
		sEventMgr.RemoveEvents( this, EVENT_PLAYER_TELEPORT );
		sEventMgr.RemoveEvents( this, EVENT_PLAYER_TAXI_DISMOUNT );
		sEventMgr.RemoveEvents( this, EVENT_PLAYER_TAXI_INTERPOLATE );
		SetTaxiState( false );
		SetTaxiPath( NULL );
		UnSetTaxiPos();
		m_taxi_ride_time = 0;
		SetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID , 0 );
		RemoveFlag( UNIT_FIELD_FLAGS, UNIT_FLAG_MOUNTED_TAXI );
		RemoveFlag( UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER );
		SetPlayerSpeed( RUN, m_runSpeed );
	}
	if ( m_TransporterGUID )
	{
		Transporter * pTrans = objmgr.GetTransporter( GUID_LOPART( m_TransporterGUID ) );
		if ( pTrans && !m_lockTransportVariables )
		{
			pTrans->RemovePlayer( this );
			m_CurrentTransporter = NULL;
			m_TransporterGUID = 0;
		}
	}
#ifdef CLUSTERING
	/* Clustering Version */
	MapInfo * mi = WorldMapInfoStorage.LookupEntry(MapID);

	// Lookup map info
	if(mi && mi->flags & WMI_INSTANCE_XPACK_01 && !m_session->HasFlag(ACCOUNT_FLAG_XPACK_01))
	{
		WorldPacket msg(SMSG_MOTD, 50);
		msg << uint32(3) << "You must have The Burning Crusade Expansion to access this content." << uint8(0);
		m_session->SendPacket(&msg);
		return false;
	}

	uint32 instance_id;
	bool map_change = false;
	if(mi && mi->type == 0)
	{
		// single instance map
		if(MapID != m_mapId)
		{
			map_change = true;
			instance_id = 0;
		}
	}
	else
	{
		// instanced map
		if(InstanceID != GetInstanceID())
			map_change = true;

		instance_id = InstanceID;
	}

	if(map_change)
	{
		WorldPacket data(SMSG_TRANSFER_PENDING, 4);
		data << uint32(MapID);
		GetSession()->SendPacket(&data);
		sClusterInterface.RequestTransfer(this, MapID, instance_id, vec);
		return;
	}

	m_sentTeleportPosition = vec;
	SetPosition(vec);
	ResetHeartbeatCoords();

	WorldPacket * data = BuildTeleportAckMsg(vec);
	m_session->SendPacket(data);
	delete data;
#else
	/* Normal Version */
	bool instance = false;
	MapInfo * mi = WorldMapInfoStorage.LookupEntry(MapID);

	if(InstanceID && (uint32)m_instanceId != InstanceID)
	{
		instance = true;
		this->SetInstanceID(InstanceID);
	}
	else if(m_mapId != MapID)
	{
		instance = true;
	}

	if (sWorld.Collision == 0) {
		// if we are mounted remove it
		if( m_MountSpellId )
			RemoveAura( m_MountSpellId );
	}

	// make sure player does not drown when teleporting from under water
	if (m_UnderwaterState & UNDERWATERSTATE_UNDERWATER)
		m_UnderwaterState &= ~UNDERWATERSTATE_UNDERWATER;

	if(flying_aura && !( MapID == 530 || MapID == 571 ) )
	{
		RemoveAura(flying_aura);
		flying_aura = 0;
	}

	// Lookup map info
	if(mi && mi->flags & WMI_INSTANCE_XPACK_01 && !m_session->HasFlag(ACCOUNT_FLAG_XPACK_01 | ACCOUNT_FLAG_XPACK_02))
	{
		WorldPacket msg(SMSG_MOTD, 50);
		msg << uint32(3) << "You must have The Burning Crusade Expansion to access this content." << uint8(0);
		m_session->SendPacket(&msg);
		return false;
	}
	if(mi && mi->flags & WMI_INSTANCE_XPACK_02 && !m_session->HasFlag(ACCOUNT_FLAG_XPACK_02))
	{
		WorldPacket msg(SMSG_MOTD, 50);
		msg << uint32(3) << "You must have The Wrath of the Lich King Expansion to access this content." << uint8(0);
		m_session->SendPacket(&msg);
		return false;
	}

	_Relocate(MapID, vec, true, instance, InstanceID);
	_EventExploration();
	return true;
#endif
}

/*
void Player::ForceZoneUpdate()
{
	if(!GetMapMgr()) 
	{ 
		return;
	}

	uint16 areaId = GetMapMgr()->GetAreaID(GetPositionX(), GetPositionY());
	AreaTable * at = dbcArea.LookupEntry(areaId);
	if(!at) 
	{ 
		return;
	}

	SetAreaID( areaId );

	if(at->ZoneId && at->ZoneId != m_zoneId)
		ZoneUpdate(at->ZoneId);

	UpdatePvPArea();
}*/

void Player::SafeTeleport(MapMgr * mgr, const LocationVector & vec)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( mgr ==  NULL )
	{ 
	   return;
	}

	if(flying_aura && !(mgr->GetMapId()==530 || mgr->GetMapId()==571) ) {
		RemoveAura(flying_aura);
		flying_aura=0;
	}

	if(IsInWorld())
		RemoveFromWorld();

	m_mapId = mgr->GetMapId();
	m_instanceId = mgr->GetInstanceID();
	WorldPacket data(SMSG_TRANSFER_PENDING, 20);
	data << mgr->GetMapId();
	GetSession()->SendPacket(&data);

	data.Initialize(SMSG_NEW_WORLD);
	data << mgr->GetMapId() << vec << vec.o;
	GetSession()->SendPacket(&data);

	SetPlayerStatus(TRANSFER_PENDING);
	m_sentTeleportPosition = vec;
	SetPosition(vec);
	SpeedCheatReset();
	_EventExploration();
}

void Player::SetGuildId(uint32 guildId)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
#ifndef CATACLYSM_SUPPORT
	if(IsInWorld())
	{
		const uint32 field = PLAYER_GUILDID;
		sEventMgr.AddEvent(static_cast<Object*>(this), &Object::EventSetUInt32Value, field, guildId, EVENT_PLAYER_SEND_PACKET, 1,
			1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
	else
	{
		SetUInt32Value(PLAYER_GUILDID,guildId);
	}
#endif
}

void Player::SetGuildRank(uint32 guildRank)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(IsInWorld())
	{
		const uint32 field = PLAYER_GUILDRANK;
		sEventMgr.AddEvent(static_cast<Object*>(this), &Object::EventSetUInt32Value, field, guildRank, EVENT_PLAYER_SEND_PACKET, 1,
			1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}
	else
	{
		SetUInt32Value(PLAYER_GUILDRANK,guildRank);
	}
}

void Player::UpdatePvPArea(bool just_teleported)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// do not trust damn bugget dbc or missing map files. If bg -> pvp on
	if( m_bg )
	{
		SetPvPFlag();
		if( m_bg->GetType() == BATTLEGROUND_ARENA_2V2 || m_bg->GetType() == BATTLEGROUND_ARENA_3V3 || m_bg->GetType() == BATTLEGROUND_ARENA_5V5 )
			SetFFAPvPFlag();
		return;
	}
	AreaTable * at = dbcArea.LookupEntryForced( GetAreaID() );
	if(at == NULL)
	{ 
		uint32 guessed_areaID;
		if( GetMapMgr() )
		{
//			guessed_areaID = GetMapMgr()->GetAreaID( GetPositionX(), GetPositionY() );
		    guessed_areaID = sTerrainMgr.GetAreaID( GetMapId(), GetPositionX(), GetPositionY(), GetPositionZ() );
			at = dbcArea.LookupEntryForced( guessed_areaID );
		}
		if(at == NULL)
			return;
		SetAreaID( guessed_areaID );
	}

#ifdef PVP_REALM_MEANS_CONSTANT_PVP
	//zack : This might be huge crap. I have no idea how it is on blizz but i think a pvp realm should alow me to gank anybody anywhere :(
	if(sWorld.GetRealmType() == REALM_PVP)
    {
		SetPvPFlag();
		return;
    }
#endif

	AreaTable * zone_for_area;
	if( at->ZoneId == 0 )
		zone_for_area = at;	//should not happen
	else
		zone_for_area = dbcArea.LookupEntryForced( at->ZoneId );

	if( zone_for_area == NULL )
		return;

	if( just_teleported )
	{
		if ( zone_for_area != NULL && isAlive() && ( zone_for_area->category == AREAC_CONTESTED || ( GetTeam() == 0 && zone_for_area->category == AREAC_HORDE_TERRITORY ) || ( GetTeam() == 1 && zone_for_area->category == AREAC_ALLIANCE_TERRITORY ) ) )
			CastSpell(this, PLAYER_HONORLESS_TARGET_SPELL, true);
	}

	// This is where all the magic happens :P
    if((zone_for_area->category == AREAC_ALLIANCE_TERRITORY && GetTeam() == 0) || (zone_for_area->category == AREAC_HORDE_TERRITORY && GetTeam() == 1))
	{
		if( IsPvPFlagged() && m_pvpTimer == 0 )
		{
			// I'm flagged and I just walked into a zone of my type. Start the 5min counter.
			ResetPvPTimer();
		}
        return;
	}
    else if((zone_for_area->category == AREAC_ALLIANCE_TERRITORY && GetTeam() == 1) || (zone_for_area->category == AREAC_HORDE_TERRITORY && GetTeam() == 0))
	{
		RemoveFFAPvPFlag();
		SetPvPFlag();
		StopPvPTimer();
        return;
	}
	else if( zone_for_area->category == AREAC_SANCTUARY )
	{
		RemovePvPFlag();
		RemoveFFAPvPFlag();
		StopPvPTimer();
		return;
	}
	else if( zone_for_area->category == AREAC_CONTESTED )
	{
		//we made sure to not have this flag set for other areas 
		if( at->AreaFlags & AREA_PVP_ARENA )				// ffa pvp arenas will come later 
        {
		    SetFFAPvPFlag();
			SetPvPFlag();
			StopPvPTimer();
        }
        else
        {
		    RemoveFFAPvPFlag();
			if(sWorld.GetRealmType() == REALM_PVP)
			{
				//automaticaly sets pvp flag on contested territorys.
				SetPvPFlag();
				StopPvPTimer();
				RemoveFFAPvPFlag();
			}
        }
	}
}

void Player::BuildFlagUpdateForNonGroupSet(uint32 index, uint32 flag)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
    Object *curObj;
	this->AquireInrangeLock(); //make sure to release lock before exit function !
	for (Object::InRangeSet::iterator iter = GetInRangeSetBegin(); iter != GetInRangeSetEnd();)
	{
		curObj = *iter;
		iter++;
        if(curObj->IsPlayer())
        {
            Group* pGroup = SafePlayerCast( curObj )->GetGroup();
            if( pGroup != NULL && pGroup == GetGroup())
            {
				//TODO: huh? if this is unneeded change the if to the inverse and don't waste jmp space
            }
            else
            {
                BuildFieldUpdatePacket( SafePlayerCast( curObj ), index, flag );
            }
        }
    }
	this->ReleaseInrangeLock();
}

/*
void Player::LoginPvPSetup()
{
	// Make sure we know our area ID.
	_EventExploration();

	if( m_AreaID == 0 )
		m_AreaID = GetMapMgr()->GetAreaID(GetPositionX(), GetPositionY());

	AreaTable * at = dbcArea.LookupEntry( ( m_AreaID != 0 ) ? m_AreaID : m_zoneId );

	if ( at != NULL && isAlive() && ( at->category == AREAC_CONTESTED || ( GetTeam() == 0 && at->category == AREAC_HORDE_TERRITORY ) || ( GetTeam() == 1 && at->category == AREAC_ALLIANCE_TERRITORY ) ) )
		CastSpell(this, PLAYER_HONORLESS_TARGET_SPELL, true);

#ifdef PVP_REALM_MEANS_CONSTANT_PVP
	//zack : This might be huge crap. I have no idea how it is on blizz but i think a pvp realm should alow me to gank anybody anywhere :(
	if(sWorld.GetRealmType() == REALM_PVP)
    {
		SetPvPFlag();
		return;
    }
#endif
}*/

void Player::PvPToggle()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	AreaTable * at = dbcArea.LookupEntryForced(( m_AreaID != 0 ) ? m_AreaID : m_zoneId);
	if(at == NULL)
	{ 
		return;
	}
	//arenas just have FFA all the time. No toggleing here pls
	if( at->AreaFlags & AREA_PVP_ARENA )				// ffa pvp arenas will come later 
	{
		StopPvPTimer();
		SetFFAPvPFlag();
		SetPvPFlag();
		return;
	}
	else
		RemoveFFAPvPFlag();

	//battlegrounds, do not let people disable PVP
	if( GetMapMgr() && DISABLE_PVP_TOGGLE_MAP( GetMapMgr()->GetMapInfo() ) )
	{
		StopPvPTimer();
		SetPvPFlag();
		return;
	}

	AreaTable * zone_for_area;
	if( at->ZoneId == 0 )
		zone_for_area = at;
	else
		zone_for_area = dbcArea.LookupEntryForced( at->ZoneId );

	if( zone_for_area == NULL )
		return;

	//no pvp in sanctuary
	if( zone_for_area->category == AREAC_SANCTUARY )
	{
		StopPvPTimer();
		RemovePvPFlag();
		return;
	}

#ifdef PVP_REALM_MEANS_CONSTANT_PVP
	//zack : This might be huge crap. I have no idea how it is on blizz but i think a pvp realm should alow me to gank anybody anywhere :(
	if(sWorld.GetRealmType() == REALM_PVP)
    {
		SetPvPFlag();
		return;
    }
#endif

	//togle flag in friendly teritory is possible for both PVP and PVE
    if((zone_for_area->category == AREAC_ALLIANCE_TERRITORY && GetTeam() == 0) || (zone_for_area->category == AREAC_HORDE_TERRITORY && GetTeam() == 1))
	{
		//we were cooling down and we toggledd PVP back
	    if( m_pvpTimer > 0 )
		{
			StopPvPTimer();
			SetPvPFlag();
			return;
		}
		//toggle off after 5 minutes
		if( IsPvPFlagged() )
		{
			ResetPvPTimer();
			return;
		}
		//enable PVP
		else
		{
			StopPvPTimer();
			SetPvPFlag();
	        return;
		}
	}
	//togle flag in enemy teritory is not possible for PVP and possible in PVE
    else if(
		(zone_for_area->category == AREAC_ALLIANCE_TERRITORY && GetTeam() == 1) 
		|| (zone_for_area->category == AREAC_HORDE_TERRITORY && GetTeam() == 0)
		|| zone_for_area->category == AREAC_CONTESTED
		)
	{
		//we can both togle in contested teritory in PVE realm. PVP has auto enable / disable pvp( i hope)
		if( sWorld.GetRealmType() == REALM_PVP && zone_for_area->category != AREAC_CONTESTED )
		{
			return;
		}
		else
		{
			//we opted for disabling then we changed our mind
			if( m_pvpTimer > 0 )
			{
				StopPvPTimer();
				SetPvPFlag();
				return;
			}
			//toggle off after 5 minutes
			if( IsPvPFlagged() )
			{
				ResetPvPTimer();
				return;
			}
			//enable PVP
			else
			{
				StopPvPTimer();
				SetPvPFlag();
				return;
			}
		}
	}
}

void Player::ResetPvPTimer()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	 m_pvpTimer = sWorld.getIntRate(INTRATE_PVPTIMER);
	 SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_PVP_STATUS_COOLDOWN);
	 RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_PVP_TOGGLE );
}

void Player::CalculateBaseStats()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(!lvlinfo) 
	{ 
		return;
	}

	memcpy(&BaseStats[0], lvlinfo->Stat, sizeof(uint32) * 5);

	LevelInfo * levelone = objmgr.GetLevelInfo(this->getRace(),this->getClass(),1);
	if (levelone == NULL)
	{
		sLog.outError("%s (%d): NULL pointer", __FUNCTION__, __LINE__);
		return;
	}
	SetUInt32Value(UNIT_FIELD_MAXHEALTH, lvlinfo->HP);
	SetUInt32Value(UNIT_FIELD_BASE_HEALTH, lvlinfo->HP - (lvlinfo->Stat[2]-levelone->Stat[2])*10);
	SetUInt32Value(PLAYER_NEXT_LEVEL_XP, lvlinfo->XPToNextLevel);
	
	
	if(GetPowerType() == POWER_TYPE_MANA)
	{
		SetUInt32Value(UNIT_FIELD_BASE_MANA, lvlinfo->Mana - (lvlinfo->Stat[3]-levelone->Stat[3])*15);
		SetUInt32Value(UNIT_FIELD_MAXPOWER1, lvlinfo->Mana);
	}
}

void Player::CompleteLoading()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	
    // cast passive initial spells	  -- grep note: these shouldnt require plyr to be in world
	SpellSet::iterator itr,itr2;
	SpellEntry *info;
	SpellCastTargets targets;
	targets.m_unitTarget = this->GetGUID();
	targets.m_targetMask = 0x2;
//	bool has_titans_grip = false;

	// warrior has to have battle stance
/*	if( getClass() == WARRIOR )
	{
		// battle stance passive
		CastSpell(this, dbcSpell.LookupEntry(2457), true);
	}*/

	for (itr2 = mSpells.begin(); itr2 != mSpells.end();)
	{
		itr = itr2;
		itr2++;	//some spells unlearn spells. Playercreate spells ex
		info = dbcSpell.LookupEntry(*itr);

		if(	info  
			&& (info->Attributes & ATTRIBUTES_PASSIVE)  // passive
			&& !( info->c_is_flags & SPELL_FLAG_IS_EXPIREING_WITH_PET ) //on pet summon talents
			&& !( info->c_is_flags & SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST ) //like health pct dependent will get autocast on health change event
			 ) 
		{
//			if( info && info->NameHash == SPELL_HASH_TITAN_S_GRIP )
//				has_titans_grip = true;
			if( info->RequiredShapeShift )
			{
				if( !( ((uint32)1 << (GetShapeShift()-1)) & info->RequiredShapeShift ) )
					continue;
			}

			Spell * spell=SpellPool.PooledNew();
			spell->Init(this,info,true,NULL);
			spell->prepare(&targets);
		}
	}

	std::list<LoginAura>::iterator i =  loginauras.begin();

	for ( ; i != loginauras.end(); i++ )
	{

		SpellEntry * sp = dbcSpell.LookupEntry((*i).id);

		if ( sp->c_is_flags & SPELL_FLAG_IS_EXPIREING_WITH_PET )
			continue; //do not load auras that only exist while pet exist. We should recast these when pet is created anyway

		Aura * aura = AuraPool.PooledNew();
		aura->Init(sp,(*i).dur,this,this);
		if ( !(*i).positive ) // do we need this? - vojta
			aura->SetNegative();

		bool first_effect=true;
		for ( uint32 x = 0; x < 3; x++ )
			if ( sp->Effect[x]==SPELL_EFFECT_APPLY_AURA )
			{
				if( first_effect )
				{
					first_effect = false;
					aura->AddMod( sp->EffectApplyAuraName[x], (*i).mod_ammount, sp->EffectMiscValue[x], x );
				}
				else
					aura->AddMod( sp->EffectApplyAuraName[x], sp->EffectBasePoints[x]+1, sp->EffectMiscValue[x], x );
			}

		if ( sp->procCharges > 0 && (*i).charges > 0 )
		{
			for ( uint32 x = 0; x < (*i).charges - 1; x++ )
			{
				Aura * a = AuraPool.PooledNew();
				a->Init( sp, (*i).dur, this, this );
				this->AddAura( a );
			}
			if ( m_chargeSpells.find( sp->Id ) == m_chargeSpells.end() && !( sp->procFlags2 & PROC2_REMOVEONUSE ) )
			{
				SpellCharge charge;
				charge.count = (*i).charges;
//				charge.spellId = sp->Id;
				charge.spe=sp;
				if( aura->GetSpellProto()->procFlagsRemove )
					charge.ProcFlag=sp->procFlagsRemove;
				else
					charge.ProcFlag=sp->procFlags;
				m_chargeSpells.insert( make_pair( sp->Id , charge ) );
			}
		}
		this->AddAura( aura );
	}
	// this needs to be after the cast of passive spells, because it will cast ghost form, after the remove making it in ghost alive, if no corpse.
	//death system checkout
	if(GetUInt32Value(UNIT_FIELD_HEALTH) <= 0 && !HasFlag(PLAYER_FLAGS, PLAYER_FLAG_DEATH_WORLD_ENABLE))
	{
		setDeathState(CORPSE);
	}
	else if(HasFlag(PLAYER_FLAGS, PLAYER_FLAG_DEATH_WORLD_ENABLE))
	{
		// Check if we have an existing corpse.
		Corpse * corpse = objmgr.GetCorpseByOwner(GetLowGUID());
		if(corpse == 0)
		{
			sEventMgr.AddEvent(this, &Player::RepopAtGraveyard, GetPositionX(),GetPositionY(),GetPositionZ(), GetMapId(), EVENT_PLAYER_CHECKFORCHEATS, 1000, 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}
		else
		{
			// Set proper deathstate
			setDeathState(CORPSE);
		}
	}
	else if(getDeathState() == JUST_DIED && !HasActiveAura(8326))
	{
		//RepopRequestedPlayer();
		sEventMgr.AddEvent(this, &Player::RepopRequestedPlayer, EVENT_PLAYER_CHECKFORCHEATS, 1000, 1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	}

	RemoveFlag(PLAYER_FIELD_BYTES,PLAYER_BYTES_FLAG_HAS_PET);

	// useless logon spell- this makes a blue splash ( i think )
//	Spell *logonspell = SpellPool.PooledNew();
//	logonspell->Init(this, dbcSpell.LookupEntry(836), false, NULL);
//	logonspell->prepare(&targets);

	// Banned
	if(IsBanned())
	{
		Kick(10000);
		BroadcastMessage("This character is not allowed to play.");
		BroadcastMessage("You have been banned for: %s", GetBanReason().c_str());
	}

	if(m_playerInfo->m_Group)
	{
		sEventMgr.AddEvent(this, &Player::EventGroupFullUpdate, EVENT_UNK, 100, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);

		//m_playerInfo->m_Group->Update();
	}

	if(raidgrouponlysent)
	{
		WorldPacket data2(SMSG_RAID_GROUP_ONLY, 8);
		data2 << uint32(0xFFFFFFFF) << uint32(0);
		GetSession()->SendPacket(&data2);
		raidgrouponlysent=false;
	}

	sInstanceMgr.BuildSavedInstancesForPlayer(this);
	CombatStatus.UpdateFlag();
	sEventMgr.AddEvent(SafeUnitCast(this),&Unit::UpdatePowerAmm,true,EVENT_SEND_PACKET_TO_PLAYER_AFTER_LOGIN,LOGIN_CIENT_SEND_DELAY,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
	UpdateGlyphsAvail();
	//ability to force players reset their talents from db
	if( GetUInt32Value( PLAYER_FLAGS ) & PLAYER_FLAGS_CUSTOM_FORCE_TALENTRESET)
	{
//		sEventMgr.AddEvent(SafePlayerCast(this),&Player::Reset_Talents,EVENT_SEND_PACKET_TO_PLAYER_AFTER_LOGIN,LOGIN_CIENT_SEND_DELAY*2,1,0);
		if( m_talentSpecsCount > 1 )
		{
		
			uint32 old_active = m_talentActiveSpec;
			m_talentActiveSpec = 0;
			Reset_Talents();
			m_talentActiveSpec = 1;
			Reset_Talents();
			m_talentActiveSpec = old_active;
		}
		else
			Reset_Talents();
	}

	if( GetMapMgr() )
		GetMapMgr()->SendInitialWorldState( this );

	sStackWolrdPacket( data, SMSG_GAMETIME_UPDATE, 12);
	data << TimeToGametime( UNIXTIME ) << uint32(0);
	GetSession()->SendPacket(&data);

//	RemoveFlag(PLAYER_FIELD_BYTES,PLAYER_BYTES_FLAG_HAS_PET);
//	SetFlag(PLAYER_FIELD_BYTES, PLAYER_BYTES_FLAG_HAS_PET ); //disable pets until they are crash free

	// warrior had titans grip then he respecced and dual wield weapon is still in hand
/*	if( getClass() == WARRIOR && has_titans_grip == false && GetItemInterface())
	{
		Item * it = GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
		if( it )
			RemoveAndMailItemFromSlot( EQUIPMENT_SLOT_OFFHAND );
	}*/
}

void Player::OnWorldPortAck()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//only rezz if player is porting to a instance portal
	MapInfo *pMapinfo = WorldMapInfoStorage.LookupEntry(GetMapId());
	if(IsDead() && pMapinfo && HAS_GRAVEYARDS_MAP( pMapinfo ) == false )
	{
		// resurrector = 0; // ceberwow: This should be seriously BUG.It makes player statz stackable.
		ResurrectPlayer();
	}

	if(pMapinfo)
	{
		WorldPacket data(4);
		if(pMapinfo->HasFlag(WMI_INSTANCE_WELCOME) && GetMapMgr())
		{
			std::string welcome_msg;
			welcome_msg = "Welcome to ";
			welcome_msg += string(GetSession()->LocalizedMapName(pMapinfo->mapid));
			welcome_msg += ". ";
//			if(pMapinfo->type != INSTANCE_DUNGEON && !(pMapinfo->type == INSTANCE_MULTIMODE && IS_HEROIC_INSTANCE_DIFFICULTIE( GetInstanceDifficulty() ) ) && m_mapMgr->pInstance)
			if( IS_HEROIC_INSTANCE_DIFFICULTIE( GetInstanceDifficulty() ) )
			{
				/*welcome_msg += "This instance is scheduled to reset on ";
				welcome_msg += asctime(localtime(&m_mapMgr->pInstance->m_expiration));*/
				welcome_msg += "This instance is scheduled to reset on ";
				welcome_msg += ConvertTimeStampToDataTime((uint32)m_mapMgr->pInstance->m_expiration);
			}
			sChatHandler.SystemMessage(m_session, welcome_msg.c_str());
		}
	}

	SpeedCheatReset();
}

void Player::ModifyBonuses( uint32 type, int32 val, bool apply )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// Added some updateXXXX calls so when an item modifies a stat they get updated
	// also since this is used by auras now it will handle it for those
	int32 _val = val;
	if( !apply )
		val = -val;

	switch ( type ) 
		{
		case POWER:
			{
				ModUnsigned32Value( UNIT_FIELD_MAXPOWER1, val );
				m_manafromitems += val;
			}break;
		case HEALTH:
			{
				ModUnsigned32Value( UNIT_FIELD_MAXHEALTH, val );
				m_healthfromitems += val;
			}break;
		case AGILITY:	//modify agility
		case STRENGTH:	//modify strength
		case INTELLECT:	//modify intellect
		case SPIRIT:	//modify spirit
		case STAMINA:	//modify stamina
			{
				uint8 convert[] = {1, 0, 3, 4, 2};
				if( _val > 0 )
					FlatStatModPos[ convert[ type - 3 ] ] += val;
				else
					FlatStatModNeg[ convert[ type - 3 ] ] -= val;
				CalcStat( convert[ type - 3 ] );
			}break;
		case WEAPON_SKILL_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_RANGED_SKILL, val ); // ranged
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL, val ); // melee main hand
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL, val ); // melee off hand
			}break;
		case DEFENSE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_DEFENCE, val );
			}break;
		case DODGE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_DODGE, val );
			}break;
		case PARRY_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_PARRY, val );
			}break;
		case SHIELD_BLOCK_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_BLOCK, val );
			}break;
		case MELEE_HIT_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_MELEE_HIT, val );
			}break;
		case RANGED_HIT_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_RANGED_HIT, val );
			}break;
		case SPELL_HIT_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_SPELL_HIT, val );
			}break;
		case MELEE_CRITICAL_STRIKE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_MELEE_CRIT, val );
			}break;
		case RANGED_CRITICAL_STRIKE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_RANGED_CRIT, val );
			}break;
		case SPELL_CRITICAL_STRIKE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_SPELL_CRIT, val );
			}break;
		case MELEE_HIT_AVOIDANCE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_MELEE_HIT_AVOIDANCE, val );
			}break;
		case RANGED_HIT_AVOIDANCE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_RANGED_HIT_AVOIDANCE, val );
			}break;
		case SPELL_HIT_AVOIDANCE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_SPELL_HIT_AVOIDANCE, val );
			}break;
		case MELEE_CRITICAL_AVOIDANCE_RATING:
			{

			}break;
		case RANGED_CRITICAL_AVOIDANCE_RATING:
			{

			}break;
		case SPELL_CRITICAL_AVOIDANCE_RATING:
			{

			}break;
		case MELEE_HASTE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_MELEE_HASTE, val );//melee
			}break;
		case RANGED_HASTE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_RANGED_HASTE, val );//ranged
			}break;
		case SPELL_HASTE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_SPELL_HASTE, val );//spell
			}break;
		case HIT_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_MELEE_HIT, val );//melee
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_RANGED_HIT, val );//ranged
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_SPELL_HIT, val );
			}break;
		case CRITICAL_STRIKE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_MELEE_CRIT, val );//melee
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_RANGED_CRIT, val );//ranged
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_SPELL_CRIT, val );
			}break;
		case HIT_AVOIDANCE_RATING:// this is guessed based on layout of other fields
			{
				//ModUnsigned32Value( PLAYER_RATING_MODIFIER_MELEE_HIT_AVOIDANCE, val );//melee
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_RANGED_HIT_AVOIDANCE, val );//ranged
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_SPELL_HIT_AVOIDANCE, val );//spell
			}break;
		case EXPERTISE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_EXPERTISE, val );
			}break;
		case RESILIENCE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE, val );//melee
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_RANGED_CRIT_RESILIENCE, val );//ranged
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_SPELL_CRIT_RESILIENCE, val );//spell
			}break;
		case RANGED_ATTACK_POWER:
			{
				ModUnsigned32Value( UNIT_FIELD_RANGED_ATTACK_POWER_MODS, val );
			}break;
/*
		//special case
		case FERAL_ATTACK_POWER:
			{
				ModUnsigned32Value( UNIT_FIELD_RANGED_ATTACK_POWER_MODS, val );
			}break;
			*/
		case HEALING_DONE:
			{
//				if( getClass() != DEATHKNIGHT && getClass() != ROGUE && getClass() != WARRIOR 
//					&& getClass() != HUNTER 
//					)
				{
//					for(uint32 school=1;school < 7; ++school)
//						HealDoneMod[school] += val;
					HealDoneMod += val;
					ModUnsigned32Value( PLAYER_FIELD_MOD_HEALING_DONE_POS, val );
				}
			}break;
		case DAMAGE_DONE:	//spell
			{
//				if( getClass() != DEATHKNIGHT && getClass() != ROGUE && getClass() != WARRIOR 
//					&& getClass() != HUNTER 
//					)
				{
					for(uint32 ind=1;ind<7;ind++)
						ModUnsigned32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS+ind, val );
				}
			}break;
		case MANA_REGENERATION:
			{
				//item mana regen is for 5 seconds but we store values ingame for regen / sec
				m_ModInterrMRegen += val / 5;
			}break;
		case HASTE_RATING:
			{
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_MELEE_HASTE, val );//melee
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_RANGED_HASTE, val );//ranged
				ModUnsigned32Value( PLAYER_RATING_MODIFIER_SPELL_HASTE, val ); // Spell
			}break;
			//i think formula is not the same. Value might not be same for spell power and healing also
		case SPELL_POWER:
			{
//				if( getClass() != DEATHKNIGHT && getClass() != ROGUE && getClass() != WARRIOR 
//					&& getClass() != HUNTER 
//					)
				{
					ModUnsigned32Value( PLAYER_FIELD_MOD_HEALING_DONE_POS, (int32)(val * SPELL_POWER_TO_HEALING_POWER_CONVERSION_FACTOR) );
					for(uint32 ind=1;ind<7;ind++)
					{
						ModUnsigned32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS + ind, val );
//						HealDoneMod[ind] += (int32)(val * SPELL_POWER_TO_HEALING_POWER_CONVERSION_FACTOR);
					}
					HealDoneMod += (int32)(val * SPELL_POWER_TO_HEALING_POWER_CONVERSION_FACTOR);
				}
			}break;
		case ATTACK_POWER:
			{
				ModUnsigned32Value(UNIT_FIELD_ATTACK_POWER_MODS, val);
				ModUnsigned32Value(UNIT_FIELD_RANGED_ATTACK_POWER_MODS, val); //maybe just mellee ?	
			}break;
		case ARMOR_PENETRATION_RATING:
			{
				ModUnsigned32Value(PLAYER_RATING_MODIFIER_ARMOR_PENETRATION_RATING, val);
			}break;
		case HEALTH_REGEN:
			{
				//check this !
				RegenModifier += val;
			}break;
		case SPELL_PENETRATION:
			{
				//check this !
				for(uint32 x=0;x<7;x++)
					TargetResistRedModFlat[x] += val;
				ModSignedInt32Value(PLAYER_FIELD_MOD_TARGET_RESISTANCE, val);
				ModSignedInt32Value(PLAYER_FIELD_MOD_TARGET_PHYSICAL_RESISTANCE, val);
			}break;
		case BLOCK_VALUE:
			{
				//check this !
				m_modblockvaluefromspells += val;
			}break;
		}
}

bool Player::CanSignCharter(Charter * charter, Player * requester)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(charter==NULL || requester==NULL)
	{ 
		return false;
	}

	if(charter->CharterType >= CHARTER_TYPE_ARENA_2V2 && m_arenaTeams[charter->CharterType-1] != NULL)
	{ 
		return false;
	}
	
	if(charter->CharterType == CHARTER_TYPE_GUILD && IsInGuild())
	{ 
		return false;
	}

	if(m_charters[charter->CharterType] || requester->GetTeam() != GetTeam())
	{ 
		return false;
	}
	else
		return true;
}

void Player::SaveAuras(stringstream &ss)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	
	for ( uint32 x = FIRST_AURA_SLOT; x < MAX_AURAS; x++ )
		if ( m_auras[x] != NULL && m_auras[x]->GetTimeLeft() > 3000 )
		{
			Aura * aur = m_auras[x];
			bool skip = false;
			for ( uint32 i = 0; i < 3; ++i )
			{
				if(aur->m_spellProto->Effect[i] == SPELL_EFFECT_APPLY_AREA_AURA || aur->m_spellProto->Effect[i] == SPELL_EFFECT_APPLY_AREA_AURA2 || aur->m_spellProto->Effect[i] == SPELL_EFFECT_ADD_FARSIGHT)
				{
					skip = true;
					break;
				}
			}

			if ( skip ) 
				continue;

			//food spells mostly
			if( aur->GetSpellProto()->AuraInterruptFlags & AURA_INTERRUPT_ON_STAND_UP )
				continue;

			if( aur->pSpellId )
				continue; //these auras were gained due to some proc. We do not save these eighter to avoid exploits of not removing them

			if ( aur->m_spellProto->c_is_flags & ( SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_NOT_SAVED_ON_LOGOUT) )
				continue;

			//aura charges have no mods except 1
			if( aur->m_modcount == 0 )
				continue;

			if( aur->IsPassive() )
				continue;

			uint32 charges = 1;
			if( aur->m_visualSlot < MAX_VISIBLE_AURAS )
				charges = m_auraStackCount[ aur->m_visualSlot ];

			ss << aur->GetSpellId() << "," << aur->GetTimeLeft() << "," << aur->IsPositive() << "," << charges << "," << aur->m_modList[0].m_amount << ",";
		}
}

void Player::SetShapeShift(uint8 ss)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint8 old_ss = GetByte( UNIT_FIELD_BYTES_2, 3 );
	uint8 old_ss2 = old_ss;
	if( old_ss == FORM_NORMAL )
		old_ss2 = FORM_CUSTOM_NORMAL;	//well, the value 0 is not detected by us ?
	SetByte( UNIT_FIELD_BYTES_2, 3, ss );

	//frikkin hackfixes
	if( getClass() == DRUID )
		RemoveAuraPosByNameHash( SPELL_HASH_STARFALL );

	//remove auras that we should not have
	for( uint32 x = 0; x < MAX_AURAS + MAX_PASSIVE_AURAS; x++ )
	{
		if( m_auras[x] != NULL )
		{
			uint32 reqss = m_auras[x]->GetSpellProto()->RequiredShapeShift;
			if( reqss != 0 && m_auras[x]->IsPositive() )
			{
				if( old_ss > 0 
					&& old_ss != FORM_SHADOW  
					&& old_ss != FORM_STEALTH  
					)								// 28 = FORM_SHADOW - Didn't find any aura that required this form
													// not sure why all priest spell proto's RequiredShapeShift are set [to 134217728]
				{
					if(  ( ((uint32)1 << (old_ss-1)) & reqss ) &&		// we were in the form that required it
						!( ((uint32)1 << (ss-1) & reqss) ) )			// new form doesnt have the right form
					{
						m_auras[x]->Remove();
						continue;
					}
					//trying to detect non shifted form requirement
					if( old_ss2 != old_ss && ( ((uint32)1 << (old_ss2-1)) & reqss ) &&		// we were in the form that required it
						!( ((uint32)1 << (ss-1) & reqss) ) )
					{
						m_auras[x]->Remove();
						continue;
					}
				}
			}

			if( this->getClass() == DRUID )
			{
				switch( m_auras[x]->GetSpellProto()->MechanicsType)
				{
                case MECHANIC_ROOTED: //Rooted
                case MECHANIC_ENSNARED: //Movement speed
                case MECHANIC_POLYMORPHED:  //Polymorphed
					{
						m_auras[x]->Remove();
					}
					break;
				default:
					break;
				}

				/*Shady: is this check neccessary? anyway m_auras[x]!=NULL check already done in next iteration. Commented*/
				//if( m_auras[x] == NULL )
				//	break;
			}
		} 
	}

	// apply any talents/spells we have that apply only in this form.
	set<uint32>::iterator itr;
	SpellEntry * sp;
	Spell * spe;
	SpellCastTargets t(GetGUID());

	for( itr = mSpells.begin(); itr != mSpells.end(); ++itr )
	{
		sp = dbcSpell.LookupEntry( *itr );
		if( sp->apply_on_shapeshift_change || (
			( sp->Attributes & ATTRIBUTES_PASSIVE )		// passive/talent
			&& !( sp->c_is_flags & SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST ) ) )
		{
			if( sp->RequiredShapeShift && ((uint32)1 << (ss-1)) & sp->RequiredShapeShift )
			{
				spe = SpellPool.PooledNew();
				spe->Init( this, sp, true, NULL );
				spe->prepare( &t );
			}
		}
	}

	// now dummy-handler stupid hacky fixed shapeshift spells (leader of the pack, etc)
	{
		//avoid list corruption we backup original and 
		SpellSet tset = mShapeShiftSpells;
		for( itr = tset.begin(); itr != tset.end(); ++itr )
		{
			sp = dbcSpell.LookupEntry( *itr );
			if( sp->RequiredShapeShift && ((uint32)1 << (ss-1)) & sp->RequiredShapeShift )
			{
				spe = SpellPool.PooledNew();
				spe->Init( this, sp, true, NULL );
				spe->prepare( &t );
			}
		}
	}

	UpdateStats();
	UpdateChances();
}

void Player::CalcDamage()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	float delta;
	float r;
	int ss = GetShapeShift();
/////////////////MAIN HAND
		float ap_bonus = GetAP()/14/1000.0f;	//1000 cause weapon speed is in MS
		delta = (float)GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS ) - (float)GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_NEG );

		if(IsInFeralForm())
		{
			float tmp = 1; // multiplicative damage modifier
			SimplePointerListNode<WeaponModifier>	*i;
			for (i = damagedone.begin(); i!=damagedone.end();i = i->Next())
			{
				if (i->data->wclass == (uint32) - 1) // applying only "any weapon" modifiers
					tmp += i->data->value;
			}
			uint32 lev = getLevel();
			float feral_damage; // average base damage before bonuses and modifiers
			uint32 x; // itemlevel of the two hand weapon with dps equal to cat or bear dps

			if (ss == FORM_CAT)
			{
				if (lev < 42) x = lev - 1;
				else if (lev < 46) x = lev;
				else if (lev < 49) x = 2 * lev - 45;
				else if (lev < 60) x = lev + 4;
				else x = 64; 

				// 3rd grade polinom for calculating blue two-handed weapon dps based on itemlevel (from Hyzenthlei)
				if (x <= 28) feral_damage = 1.563e-03f * x*x*x - 1.219e-01f * x*x + 3.802e+00f * x - 2.227e+01f;
				else if (x <= 41) feral_damage = -3.817e-03f * x*x*x + 4.015e-01f * x*x - 1.289e+01f * x + 1.530e+02f;
				else feral_damage = 1.829e-04f * x*x*x - 2.692e-02f * x*x + 2.086e+00f * x - 1.645e+01f;

				r = feral_damage * 0.79f + delta + ap_bonus * 1000.0f;
				r *= tmp;
				SetFloatValue(UNIT_FIELD_MINDAMAGE,r>0?r:0);

				r = feral_damage * 1.21f + delta + ap_bonus * 1000.0f;
				r *= tmp;
				SetFloatValue(UNIT_FIELD_MAXDAMAGE,r>0?r:0);
			}
			else // Bear or Dire Bear Form
			{
				if (ss == FORM_BEAR) x = lev;
				else x = lev + 5; // DIRE_BEAR dps is slightly better than bear dps
				if (x > 70) x = 70;

				// 3rd grade polinom for calculating green two-handed weapon dps based on itemlevel (from Hyzenthlei)
				if (x <= 30) feral_damage = 7.638e-05f * x*x*x + 1.874e-03f * x*x + 4.967e-01f * x + 1.906e+00f;
				else if (x <= 44) feral_damage = -1.412e-03f * x*x*x + 1.870e-01f * x*x - 7.046e+00f * x + 1.018e+02f;
				else feral_damage = 2.268e-04f * x*x*x - 3.704e-02f * x*x + 2.784e+00f * x - 3.616e+01f;
				feral_damage *= 2.5f; // Bear Form attack speed

				r = feral_damage * 0.79f + delta + ap_bonus * 2500.0f;
				r *= tmp;
				SetFloatValue(UNIT_FIELD_MINDAMAGE,r>0?r:0);

				r = feral_damage * 1.21f + delta + ap_bonus * 2500.0f;
				r *= tmp;
				SetFloatValue(UNIT_FIELD_MAXDAMAGE,r>0?r:0);
			}

			return;
		}

//////no druid ss	
		uint32 speed=2000;
		Item *it = GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
		
		if(!disarmed)
		{	
			if(it)
				speed = it->GetProto()->Delay;
		}
		
		float bonus=ap_bonus*speed;
		float tmp = 1;
		SimplePointerListNode<WeaponModifier>	*i;
		for (i = damagedone.begin(); i!=damagedone.end();i = i->Next())
		{
			if( ( i->data->wclass == -1 ) || //any weapon
				(it && ( (1 << it->GetProto()->SubClass) & i->data->subclass) )
				)
				tmp+=i->data->value;
		}
		
		r = BaseDamage[0]+delta+bonus;
		r *= tmp;
		SetFloatValue(UNIT_FIELD_MINDAMAGE,r>0?r:0);
	
		r = BaseDamage[1]+delta+bonus;
		r *= tmp;
		SetFloatValue(UNIT_FIELD_MAXDAMAGE,r>0?r:0);

		uint32 cr = 0;
		if( it )
		{
			if( SafePlayerCast( this )->m_wratings.size() )
			{
				std::map<uint32, uint32>::iterator itr = m_wratings.find( it->GetProto()->SubClass );
				if( itr != m_wratings.end() )
					cr=itr->second;
			}
		}
		SetUInt32Value( PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL, cr );
		/////////////// MAIN HAND END

		/////////////// OFF HAND START
		cr = 0;
		it = SafePlayerCast( this )->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
		if(it)
		{
			if(!disarmed)
			{
				speed =it->GetProto()->Delay;
			}
			else speed  = 2000;
			
			bonus = ap_bonus * speed;
			tmp = 1;
			for(i = damagedone.begin();i!=damagedone.end();i = i->Next() )
			{
				if((i->data->wclass==(uint32)-1) || //any weapon
					(( (1 << it->GetProto()->SubClass) & i->data->subclass)  )
					)
					tmp+=i->data->value;
			}

			r = (BaseOffhandDamage[0]+delta+bonus)*offhand_dmg_mod;
			r *= tmp;
			SetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE,r>0?r:0);
			r = (BaseOffhandDamage[1]+delta+bonus)*offhand_dmg_mod;
			r *= tmp;
			SetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE,r>0?r:0);
			if(m_wratings.size ())
			{
				std::map<uint32, uint32>::iterator itr=m_wratings.find(it->GetProto()->SubClass);
				if(itr!=m_wratings.end())
					cr=itr->second;
			}
		}
		SetUInt32Value( PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL, cr );

/////////////second hand end
///////////////////////////RANGED
		cr=0;
		if((it = GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_RANGED)) != 0)
		{
			tmp = 1;
			for(i = damagedone.begin();i != damagedone.end();i = i->Next() )
			{
				if( (i->data->wclass == (uint32)-1) || //any weapon
					( ((1 << it->GetProto()->SubClass) & i->data->subclass)  ))
					tmp+=i->data->value;
			}

			if(it->GetProto()->SubClass != 19)//wands do not have bonuses from RAP & ammo
			{
//				ap_bonus = (GetUInt32Value(UNIT_FIELD_RANGED_ATTACK_POWER)+(int32)GetUInt32Value(UNIT_FIELD_RANGED_ATTACK_POWER_MODS))/14000.0;
				//modified by Zack : please try to use premade functions if possible to avoid forgetting stuff
				ap_bonus = GetRAP()/14000.0f;
				bonus = ap_bonus*it->GetProto()->Delay;
				
#ifndef CATACLYSM_SUPPORT
				if( GetUInt32Value(PLAYER_AMMO_ID) && !m_requiresNoAmmo )
				{
					ItemPrototype * xproto=ItemPrototypeStorage.LookupEntry(GetUInt32Value(PLAYER_AMMO_ID));
					if(xproto)
					{
						bonus+=((xproto->Damage[0].Min+xproto->Damage[0].Max)*it->GetProto()->Delay)/2000.0f;
					}
				}
#endif
			}
			else bonus =0;
			
			r = BaseRangedDamage[0]+delta+bonus;
			r *= tmp;
			SetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE,r>0?r:0);

			r = BaseRangedDamage[1]+delta+bonus;
			r *= tmp;
			SetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE,r>0?r:0);
			
		
			if(m_wratings.size ())
			{
				std::map<uint32, uint32>::iterator i=m_wratings.find(it->GetProto()->SubClass);
				if(i != m_wratings.end())
					cr=i->second;
			}
		
		}
		SetUInt32Value( PLAYER_RATING_MODIFIER_RANGED_SKILL, cr );

/////////////////////////////////RANGED end
		if( GetSummon() )
			GetSummon()->CalcDamage();//Re-calculate pet's too

}

uint32 Player::GetMainMeleeDamage(uint32 AP_owerride)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	float r;
	int ss = GetShapeShift();
/////////////////MAIN HAND
	float ap_bonus;
	if(AP_owerride) 
		ap_bonus = AP_owerride/14000.0f;
	else 
		ap_bonus = GetAP()/14000.0f;
	if(IsInFeralForm())
	{
		if(ss == FORM_CAT)
			r = ap_bonus * 1000.0f;
		else
			r = ap_bonus * 2500.0f;
		return float2int32(r);
	}
//////no druid ss	
	uint32 speed=2000;
	Item *it = GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
	if(!disarmed)
	{	
		if(it)
			speed = it->GetProto()->Delay;
	}
	r = ap_bonus*speed;
	return float2int32(r);
}

void Player::EventPortToGM(Unit *p)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SafeTeleport(p->GetMapId(),p->GetInstanceID(),p->GetPosition());
}

void Player::UpdateComboPoints()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// fuck bytebuffers :D
	unsigned char buffer[10];
	uint32 c = 2;

	// check for overflow
	if(m_comboPoints > 5)
		m_comboPoints = 5;
	
	if(m_comboPoints < 0)
		m_comboPoints = 0;

	if(m_comboTarget != 0)
	{
		Unit * target = (m_mapMgr != NULL) ? m_mapMgr->GetUnit(m_comboTarget) : NULL;
		if(!target || target->IsDead() || GetSelection() != m_comboTarget)
		{
			buffer[0] = buffer[1] = 0;
		}
		else
		{
			c = FastGUIDPack(m_comboTarget, buffer, 0);
			buffer[c++] = m_comboPoints;
		}
	}
	else
		buffer[0] = buffer[1] = 0;

	m_session->OutPacket(SMSG_UPDATE_COMBO_POINTS, c, buffer);
}

void Player::SendAreaTriggerMessage(const char * message, ...)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	va_list ap;
	va_start(ap, message);
	char msg[500];
	vsnprintf(msg, 500, message, ap);
	va_end(ap);

	WorldPacket data(SMSG_AREA_TRIGGER_MESSAGE, 6 + strlen(msg));
	data << (uint32)0 << msg << (uint8)0x00;
	m_session->SendPacket(&data);
}

void Player::removeSoulStone()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(!this->SoulStone) 
	{ 
		return;
	}
	uint32 sSoulStone = 0;
	switch(this->SoulStone)
	{
	case 3026:
		{
			sSoulStone = 20707;
		}break;
	case 20758:
		{
			sSoulStone = 20762;
		}break;
	case 20759:
		{
			sSoulStone = 20763;
		}break;
	case 20760:
		{
			sSoulStone = 20764;
		}break;
	case 20761:
		{
			sSoulStone = 20765;
		}break;
	case 27240:
		{
			sSoulStone = 27239;
		}break;
	}
	this->RemoveAura(sSoulStone);
	this->SoulStone = this->SoulStoneReceiver = 0; //just incase
}

void Player::SoftDisconnect()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
      sEventMgr.RemoveEvents(this, EVENT_PLAYER_SOFT_DISCONNECT);
	  WorldSession *session=GetSession();
      session->LogoutPlayer(true);
	  session->Disconnect();
}

void Player::SetNoseLevel()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// Set the height of the player
	switch (getRace())
	{
		case RACE_HUMAN:
		// female
			if (getGender()) m_noseLevel = 1.72f;
			// male
			else m_noseLevel = 1.78f;
		break;
		case RACE_ORC:
			if (getGender()) m_noseLevel = 1.82f;
			else m_noseLevel = 1.98f;
		break;
		case RACE_DWARF:
		if (getGender()) m_noseLevel = 1.27f;
			else m_noseLevel = 1.4f;
		break;
		case RACE_NIGHTELF:
			if (getGender()) m_noseLevel = 1.84f;
			else m_noseLevel = 2.13f;
		break;
		case RACE_UNDEAD:
			if (getGender()) m_noseLevel = 1.61f;
			else m_noseLevel = 1.8f;
		break;
		case RACE_TAUREN:
			if (getGender()) m_noseLevel = 2.48f;
			else m_noseLevel = 2.01f;
		break;
		case RACE_GNOME:
			if (getGender()) m_noseLevel = 1.06f;
			else m_noseLevel = 1.04f;
		break;
		case RACE_TROLL:
			if (getGender()) m_noseLevel = 2.02f;
			else m_noseLevel = 1.93f;
		break;
		case RACE_GOBLIN:
			if (getGender()) m_noseLevel = 1.06f;
			else m_noseLevel = 1.04f;
		break;
		case RACE_BLOODELF:
			if (getGender()) m_noseLevel = 1.83f;
			else m_noseLevel = 1.93f;
		break;
		case RACE_DRAENEI:
			if (getGender()) m_noseLevel = 2.09f;
			else m_noseLevel = 2.36f;
		break;
		case RACE_WORGEN:
			if (getGender()) m_noseLevel = 2.48f;
			else m_noseLevel = 2.01f;
		break;
	}
}

void Player::Possess(Unit * pTarget)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( m_CurrentCharm)
	{ 
		return;
	}

	m_CurrentCharm = pTarget->GetGUID();
	if(pTarget->GetTypeId() == TYPEID_UNIT)
	{
		// unit-only stuff.
		pTarget->setAItoUse(false);
		pTarget->GetAIInterface()->StopMovement(0);
		pTarget->m_redirectSpellPackets = this;
	}

	m_noInterrupt++;
	SetUInt64Value(UNIT_FIELD_CHARM, pTarget->GetGUID());
	SetUInt64Value(PLAYER_FARSIGHT, pTarget->GetGUID());

	pTarget->SetUInt64Value(UNIT_FIELD_CHARMEDBY, GetGUID());
	pTarget->SetCharmTempVal(pTarget->GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
	pTarget->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
	pTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED_CREATURE);

	SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);
	
	/* send "switch mover" packet */
	WorldPacket data1( SMSG_CLIENT_CONTROL_UPDATE, 10 );
	data1 << pTarget->GetNewGUID() << uint8(1);
	m_session->SendPacket(&data1);

	/* update target faction set */
	pTarget->_setFaction();
//	pTarget->UpdateOppFactionSet();


	/* build + send pet_spells packet */
	if(pTarget->m_temp_summon)
	{ 
		return;
	}
	
	if( !( pTarget->IsPet() && SafePetCast( pTarget ) == m_Summon ) )
	{
		list<uint32> avail_spells;
		SimplePointerListNode<AI_Spell> *itr2;
		for(itr2 = pTarget->GetAIInterface()->m_spells.begin(); itr2 != pTarget->GetAIInterface()->m_spells.end();itr2 = itr2->next)
			if(itr2->data->agent == AGENT_SPELL)
				avail_spells.push_back(itr2->data->spell->Id);
		list<uint32>::iterator itr;

		WorldPacket data(SMSG_PET_SPELLS, avail_spells.size() * 4 + 24);
		data << pTarget->GetGUID();
		data << uint32(0x00000001);//unk1
		data << uint32(0x00000000);//unk1
		data << uint32(0x00000101);//unk2

		// First spell is attack.
		data << uint32(PET_SPELL_ATTACK);

		// Send the actionbar
		itr = avail_spells.begin();
		for(uint32 i = 1; i < 10; ++i)
		{
			if(itr != avail_spells.end())
			{
				data << uint16((*itr)) << uint16(DEFAULT_SPELL_STATE);
				++itr;
			}
			else
				data << uint16(0) << uint8(0) << uint8(i+5);
		}
		// Send the rest of the spells.
		data << uint8(avail_spells.size());
		for(itr = avail_spells.begin(); itr != avail_spells.end(); ++itr)
			data << uint16(*itr) << uint16(DEFAULT_SPELL_STATE);
		
		data << uint64(0);
		m_session->SendPacket(&data);
	}
	
}

void Player::UnPossess()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( !m_CurrentCharm )
	{ 
		return;
	}

	Unit * pTarget = GetMapMgr()->GetUnit( m_CurrentCharm ); 
	if( !pTarget )
	{ 
		return;
	}

	m_CurrentCharm = 0;

	SpeedCheatReset();

	if(pTarget->GetTypeId() == TYPEID_UNIT)
	{
		// unit-only stuff.
		pTarget->setAItoUse(true);
		pTarget->m_redirectSpellPackets = 0;
	}

	m_noInterrupt--;
	SetUInt64Value(PLAYER_FARSIGHT, 0);
	SetUInt64Value(UNIT_FIELD_CHARM, 0);
	pTarget->SetUInt64Value(UNIT_FIELD_CHARMEDBY, 0);

	RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOCK_PLAYER);
	pTarget->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED_CREATURE);
	pTarget->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, pTarget->GetCharmTempVal());
	pTarget->_setFaction();
//	pTarget->UpdateOppFactionSet();

	/* send "switch mover" packet */
	WorldPacket data(SMSG_CLIENT_CONTROL_UPDATE, 12);
	data << GetNewGUID() << uint8(1);
	m_session->SendPacket(&data);

	if(pTarget->m_temp_summon)
	{ 
		return;
	}
 
	if( pTarget->IsPet() && SafePetCast( pTarget ) != m_Summon )
	{
		data.Initialize( SMSG_PET_SPELLS );
		data << uint64( 0 );
		data << uint32(0x00000000);
		m_session->SendPacket( &data );
	}
}

void Player::SummonRequest(uint32 Requestor, uint32 ZoneID, uint32 MapID, uint32 InstanceID, const LocationVector & Position)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	m_summonInstanceId = InstanceID;
	m_summonPos = Position;
	m_summoner = Requestor;
	m_summonMapId = MapID;

	WorldPacket data(SMSG_SUMMON_REQUEST, 16);
	data << uint64(Requestor) << ZoneID << uint32(120000);		// 2 minutes
	m_session->SendPacket(&data);
}
/*
/*
void Player::RemoveFromBattlegroundQueue()
{
	if(!m_pendingBattleground)
		return;

	m_pendingBattleground->RemovePendingPlayer(this);
	sChatHandler.SystemMessage(m_session, "You were removed from the queue for the battleground for not joining after 2 minutes.");
	m_pendingBattleground = 0;
}*/

void Player::_AddSkillLine(uint32 SkillLine, uint32 Curr_sk, uint32 Max_sk)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	skilllineentry * CheckedSkill = dbcSkillLine.LookupEntry(SkillLine);
	if (!CheckedSkill) //skill doesn't exist, exit here
	{ 
		return;
	}

	// force to be within limits
	Curr_sk = ( Curr_sk > PLAYER_SKILL_CAP ? PLAYER_SKILL_CAP : ( Curr_sk <1 ? 1 : Curr_sk ) );
	Max_sk = ( Max_sk > PLAYER_SKILL_CAP ? PLAYER_SKILL_CAP : Max_sk );
	Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL,SkillLine,ACHIEVEMENT_UNUSED_FIELD_VALUE,Curr_sk,ACHIEVEMENT_EVENT_ACTION_SET_MAX);
	Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LEVEL,SkillLine,ACHIEVEMENT_UNUSED_FIELD_VALUE,Max_sk/75,ACHIEVEMENT_EVENT_ACTION_SET_MAX);
	ItemProf * prof;
	SkillMap::iterator itr = m_skills.find(SkillLine);
	if(itr != m_skills.end())
	{
		if( (Curr_sk > itr->second.CurrentValue && Max_sk >= itr->second.MaximumValue) || (Curr_sk == itr->second.CurrentValue && Max_sk > itr->second.MaximumValue) )
		{
			itr->second.CurrentValue = Curr_sk;
			itr->second.MaximumValue = Max_sk;
			_UpdateMaxSkillCounts();
			AutoLearnSkillRankSpells(SkillLine, Curr_sk);
		}
	}
	else
	{
		PlayerSkill inf;
		inf.Skill = CheckedSkill;
		inf.MaximumValue = Max_sk;
		inf.CurrentValue = ( inf.Skill->id != SKILL_RIDING ? Curr_sk : Max_sk );
		inf.BonusValue = 0;
		m_skills.insert( make_pair( SkillLine, inf ) );
		_UpdateSkillFields();
		AutoLearnSkillRankSpells(SkillLine, Curr_sk);
	}
	//Add to proficiency
	prof=(ItemProf *)GetProficiencyBySkill(SkillLine);
	if( prof != 0)
	{
		packetSMSG_SET_PROFICICENCY pr;
		pr.ItemClass = prof->itemclass;
		if(prof->itemclass==4)
		{
				armor_proficiency|=prof->subclass;
				//SendSetProficiency(prof->itemclass,armor_proficiency);
				pr.Profinciency = armor_proficiency;
		}
		else
		{
				weapon_proficiency|=prof->subclass;
				//SendSetProficiency(prof->itemclass,weapon_proficiency);
				pr.Profinciency = weapon_proficiency;
		}
		m_session->OutPacket( SMSG_SET_PROFICIENCY, sizeof( packetSMSG_SET_PROFICICENCY ), &pr );
	}
}

void Player::_UpdateSkillFields()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 f = PLAYER_SKILL_INFO_1_1;
	/* Set the valid skills */
	for(SkillMap::iterator itr = m_skills.begin(); itr != m_skills.end();)
	{
		if(!itr->first)
		{
			SkillMap::iterator it2 = itr++;
			m_skills.erase(it2);
			continue;
		}

		if(itr->second.Skill->type == SKILL_TYPE_PROFESSION)
			SetUInt32Value(f++, itr->first | 0x10000);
		else
			SetUInt32Value(f++, itr->first);

		SetUInt32Value(f++, (itr->second.MaximumValue << 16) | itr->second.CurrentValue);
		SetUInt32Value(f++, itr->second.BonusValue);
		++itr;
		//omg. more skills than wow has
		if(f == PLAYER_CHARACTER_POINTS1)
			break;
	}

	/* Null out the rest of the fields */
	for(; f < PLAYER_CHARACTER_POINTS1; ++f)
	{
		if(m_uint32Values[f] != 0)
			SetUInt32Value(f, 0);
	}
}

bool Player::_HasSkillLine(uint32 SkillLine)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	return (m_skills.find(SkillLine) != m_skills.end());
}

void Player::_AdvanceSkillLine(uint32 SkillLine, uint32 Count /* = 1 */)
{
	SkillMap::iterator itr = m_skills.find(SkillLine);
	if(itr == m_skills.end())
	{
		/* Add it */
		_AddSkillLine(SkillLine, Count, getLevel() * 5);
		Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL,SkillLine,ACHIEVEMENT_UNUSED_FIELD_VALUE,Count,ACHIEVEMENT_EVENT_ACTION_SET_MAX);
		_UpdateMaxSkillCounts();
		sHookInterface.OnAdvanceSkillLine(this, SkillLine, Count);
	}
	else
	{	
		uint32 curr_sk = itr->second.CurrentValue;
		itr->second.CurrentValue = min(curr_sk + Count,itr->second.MaximumValue);
		Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL,SkillLine,ACHIEVEMENT_UNUSED_FIELD_VALUE,itr->second.CurrentValue,ACHIEVEMENT_EVENT_ACTION_SET_MAX);
		if (itr->second.CurrentValue > curr_sk)
		{
			_UpdateSkillFields();
			sHookInterface.OnAdvanceSkillLine(this, SkillLine, curr_sk);
			AutoLearnSkillRankSpells(SkillLine, itr->second.CurrentValue);
		}
	}
}

uint32 Player::_GetSkillLineMax(uint32 SkillLine)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SkillMap::iterator itr = m_skills.find(SkillLine);
	return (itr == m_skills.end()) ? 0 : itr->second.MaximumValue;
}

uint32 Player::_GetSkillLineCurrent(uint32 SkillLine, bool IncludeBonus /* = true */)
{
	SkillMap::iterator itr = m_skills.find(SkillLine);
	if(itr == m_skills.end())
	{ 
		return 0;
	}

	return (IncludeBonus ? itr->second.CurrentValue + itr->second.BonusValue : itr->second.CurrentValue);
}

void Player::_RemoveSkillLine(uint32 SkillLine)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SkillMap::iterator itr = m_skills.find(SkillLine);
	if(itr == m_skills.end())
	{ 
		return;
	}

	m_skills.erase(itr);
	_UpdateSkillFields();
}

void Player::_UpdateMaxSkillCounts()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	bool dirty = false;
	uint32 new_max;
	for(SkillMap::iterator itr = m_skills.begin(); itr != m_skills.end(); ++itr)
	{
		if(itr->second.Skill->type == SKILL_TYPE_WEAPON || itr->second.Skill->id == SKILL_LOCKPICKING 
//			|| itr->second.Skill->id == SKILL_POISONS
			)
		{
			new_max = 5 * getLevel();
		}
		else if (itr->second.Skill->type == SKILL_TYPE_LANGUAGE)
		{
			new_max = 300;
		}
		else if (itr->second.Skill->type == SKILL_TYPE_PROFESSION || itr->second.Skill->type == SKILL_TYPE_SECONDARY)
		{
			new_max = itr->second.MaximumValue;
			//Zack : why on earth was this fix put here ?
			if( new_max > PLAYER_SKILL_CAP )
				new_max = PLAYER_SKILL_CAP;
		}
		else
		{
			new_max = 1;
		}

		// force to be within limits
		if (new_max > PLAYER_SKILL_CAP)
			new_max = PLAYER_SKILL_CAP;
		if (new_max < 1)
			new_max = 1;

	
		if(itr->second.MaximumValue != new_max)
		{
			dirty = true;
			itr->second.MaximumValue = new_max;
		}
		if (itr->second.CurrentValue > new_max)
		{
			dirty = true;
			itr->second.CurrentValue = new_max;
		}
	}

	if(dirty)
		_UpdateSkillFields();
}

void Player::_ModifySkillBonus(uint32 SkillLine, int32 Delta)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SkillMap::iterator itr = m_skills.find(SkillLine);
	if(itr == m_skills.end())
	{ 
		return;
	}

	itr->second.BonusValue += Delta;
	_UpdateSkillFields();
}

void Player::_ModifySkillBonusByType(uint32 SkillType, int32 Delta)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	bool dirty = false;
	for(SkillMap::iterator itr = m_skills.begin(); itr != m_skills.end(); ++itr)
	{
		if(itr->second.Skill->type == SkillType)
		{
			itr->second.BonusValue += Delta;
			dirty=true;
		}
	}

	if(dirty)
		_UpdateSkillFields();
}

/** Maybe this formula needs to be checked?
 * - Burlex
 */

float PlayerSkill::GetSkillUpChance()
{
	float diff = float(MaximumValue - CurrentValue);
	return (diff * 100.0f / float(MaximumValue));
}

void Player::_RemoveLanguages()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	for(SkillMap::iterator itr = m_skills.begin(), it2; itr != m_skills.end();)
	{
		if(itr->second.Skill->type == SKILL_TYPE_LANGUAGE)
		{
			it2 = itr++;
			m_skills.erase(it2);
		}
		else
			++itr;
	}
}

void PlayerSkill::Reset(uint32 Id)
{
	MaximumValue = 0;
	CurrentValue = 0;
	BonusValue = 0;
	Skill = (Id == 0) ? NULL : dbcSkillLine.LookupEntryForced(Id);
}

void Player::_AddLanguages(bool All)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	/** This function should only be used at login, and after _RemoveLanguages is called.
	 * Otherwise weird stuff could happen :P
	 * - Burlex
	 */

	PlayerSkill sk;
	skilllineentry * en;
	uint32 spell_id;
	static uint32 skills[] = { SKILL_LANG_COMMON, SKILL_LANG_ORCISH, SKILL_LANG_DWARVEN, SKILL_LANG_DARNASSIAN, SKILL_LANG_TAURAHE, SKILL_LANG_THALASSIAN,
		SKILL_LANG_TROLL, SKILL_LANG_GUTTERSPEAK, SKILL_LANG_DRAENEI, 0 };
	
	if(All)
	{
		for(uint32 i = 0; skills[i] != 0; ++i)
		{
			if(!skills[i])
				break;

            sk.Reset(skills[i]);
			sk.MaximumValue = sk.CurrentValue = 300;
			if( sk.Skill == NULL )
				continue;
			m_skills.insert( make_pair(skills[i], sk) );
			if((spell_id = ::GetSpellForLanguage(skills[i])) != 0)
				addSpell(spell_id, true);
		}
	}
	else
	{
		for(list<CreateInfo_SkillStruct>::iterator itr = info->skills.begin(); itr != info->skills.end(); ++itr)
		{
			en = dbcSkillLine.LookupEntry(itr->skillid);
			if(en->type == SKILL_TYPE_LANGUAGE)
			{
				sk.Reset(itr->skillid);
				sk.MaximumValue = sk.CurrentValue = 300;
				if( sk.Skill == NULL )
					continue;
				m_skills.insert( make_pair(itr->skillid, sk) );
				if((spell_id = ::GetSpellForLanguage(itr->skillid)) != 0)
					addSpell(spell_id, true);
			}
		}
	}

	_UpdateSkillFields();
}

float Player::GetSkillUpChance(uint32 id)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SkillMap::iterator itr = m_skills.find(id);
	if(itr == m_skills.end())
	{ 
		return 0.0f;
	}

	return itr->second.GetSkillUpChance();
}

void Player::_RemoveAllSkills()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	m_skills.clear();
	_UpdateSkillFields();
}

void Player::_AdvanceAllSkills(uint32 count)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( count == 0 )
		return;
	bool dirty=false;
	for(SkillMap::iterator itr = m_skills.begin(); itr != m_skills.end(); ++itr)
	{
		if(itr->second.CurrentValue != itr->second.MaximumValue)
		{
			itr->second.CurrentValue += count;
			if(itr->second.CurrentValue >= itr->second.MaximumValue)
				itr->second.CurrentValue = itr->second.MaximumValue;
			dirty=true;
		}
	}

	if(dirty)
		_UpdateSkillFields();
}

void Player::_ModifySkillMaximum(uint32 SkillLine, uint32 NewMax)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// force to be within limits
	NewMax = ( NewMax > PLAYER_SKILL_CAP ? PLAYER_SKILL_CAP : NewMax );

	SkillMap::iterator itr = m_skills.find(SkillLine);
	if(itr == m_skills.end())
	{ 
		return;
	}

	//Zack : removed if, what about down leveling ?
	if(NewMax != itr->second.MaximumValue)
	{
		if(SkillLine == SKILL_RIDING)
			itr->second.CurrentValue = NewMax;

		itr->second.MaximumValue = NewMax;
		_UpdateSkillFields();
	}
}

void Player::AutoLearnSkillRankSpells(uint32 SkillLine, uint32 curr_sk)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	// check for learn new spells (professions), from SkillLineAbility.dbc
	skilllinespell* sls;
	uint32 rowcount = dbcSkillLineSpell.GetNumRows();
	SpellEntry* sp;
	uint32 removeSpellId = 0;
	for( uint32 idx = 0; idx < rowcount; ++idx )
	{
		sls = dbcSkillLineSpell.LookupRow( idx );
		// add new "automatic-acquired" spell
		if( (sls->skilline == SkillLine) 
			&& (sls->acquireMethod == 1)	//there are 88 spells like this in 3.3.3 client
			&& (sls->raceMask == 0 || (sls->raceMask & getRaceMask()) )
			&& (sls->classMask == 0 || (sls->classMask & getClassMask()) )
			&& (sls->excludeRace == 0 || (sls->excludeRace & getRaceMask()) == 0 )
			&& (sls->excludeClass == 0 || (sls->excludeClass & getClassMask()) == 0 )
			&& curr_sk >= sls->minSkillLineRank
			)
		{
			sp = dbcSpell.LookupEntry( sls->spell );
			if( sp 
//				&& (getLevel() >= sp->baseLevel) 
				)
			{
				// Player is able to learn this spell; check if they already have it, or a higher rank (shouldn't, but just in case)
				bool addThisSpell = true;
				SpellEntry* se;
				for(SpellSet::iterator itr2,itr = mSpells.begin(); itr != mSpells.end();)
				{
					itr2 = itr;
					++itr;
					se = dbcSpell.LookupEntry( *itr2 );
					if(se->NameHash == sp->NameHash) 
					{
						if(se->RankNumber >= sp->RankNumber)
						{
							// Player already has this spell, or a higher rank. Don't add it.
							// Stupid profession related spells for "skinning" having the same namehash and not ranked
							if( sp->Id != 32605 && sp->Id != 32606 && sp->Id != 49383 )
								addThisSpell = false;
							break;
						}
						//previous rank is smaller. Remove it. This is like Toughness that would stack all 7 ranks and make you uber strong
						//another example is that heal from herbalism that has cooldown separate for each rank
						else 
//							if( sp->Attributes & ATTRIBUTES_PASSIVE )
						{
							mSpells.erase( itr2 );
						}
					}
				}
				if( addThisSpell )
				{
					addSpell( sls->spell );
					if( sls->prev )
						removeSpell( sls->prev, true, true, sls->spell );
					// if passive spell, apply it now
					if(
						( sp->Attributes & ATTRIBUTES_PASSIVE )
						&& !( sp->c_is_flags & SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST ) //like health pct dependent will get autocast on health change event
						)
					{
						SpellCastTargets targets;
						targets.m_unitTarget = this->GetGUID();
						targets.m_targetMask = TARGET_FLAG_UNIT;
						Spell* spell = SpellPool.PooledNew();
						if( spell == NULL )
						{ 
							return;
						}
						spell->Init(this,sp,true,NULL);
						spell->prepare(&targets);
					}
				}
			}
		}
	}
}

void Player::RemoveSpellTargets(uint32 Type, Unit* target)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( m_spellIndexTypeTargets[Type] != 0 )
	{
		Unit * pUnit = m_mapMgr ? m_mapMgr->GetUnit(m_spellIndexTypeTargets[Type]) : NULL;
		if( pUnit != NULL && pUnit != target ) //some auras can stack on target. There is no need to remove them if target is same as previous one
		{
			pUnit->RemoveAurasByBuffIndexType(Type, GetGUID());
			m_spellIndexTypeTargets[Type] = 0;
		}
	}
}

void Player::RemoveSpellIndexReferences(uint32 Type)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	m_spellIndexTypeTargets[Type] = 0;
}

void Player::SetSpellTargetType(uint32 Type, Unit* target)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	m_spellIndexTypeTargets[Type] = target->GetGUID();
}

void Player::RecalculateHonor()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	HonorHandler::RecalculateHonorFields(this);
}

//wooot, crapy code rulez.....NOT
void Player::EventTalentHearthOfWildChange(bool apply)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(!hearth_of_wild_pct)
	{ 
		return;
	}

	//druid hearth of the wild should add more features based on form
	int tval;
	if(apply)
		tval = hearth_of_wild_pct;
	else tval = -hearth_of_wild_pct;

	uint32 SS=GetShapeShift();

	//increase stamina if :
	if(SS==FORM_BEAR || SS==FORM_DIREBEAR)
	{
		TotalStatModPctPos[STAT_STAMINA] += tval; 
		CalcStat(STAT_STAMINA);	
		UpdateStats();
		UpdateChances();
	}
	//increase attackpower if :
	else if(SS==FORM_CAT)
	{
		SetFloatValue(UNIT_FIELD_ATTACK_POWER_MULTIPLIER,GetFloatValue(UNIT_FIELD_ATTACK_POWER_MULTIPLIER)+float(tval/200.0f));
		SetFloatValue(UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER, GetFloatValue(UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER)+float(tval/200.0f));
		UpdateStats();
		UpdateChances();
	}
}

void Player::EventGroupFullUpdate()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(m_playerInfo->m_Group)
	{
		//m_playerInfo->m_Group->Update();
		m_playerInfo->m_Group->UpdateAllOutOfRangePlayersFor(this);
	}
}

void Player::EjectFromInstance()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(m_bgEntryPointX && m_bgEntryPointY && m_bgEntryPointZ && !IS_INSTANCE(m_bgEntryPointMap))
	{
		if(SafeTeleport(m_bgEntryPointMap, m_bgEntryPointInstance, m_bgEntryPointX, m_bgEntryPointY, m_bgEntryPointZ, m_bgEntryPointO))
		{ 
			return;
		}
	}

	SafeTeleport(m_bind_mapid, 0, m_bind_pos_x, m_bind_pos_y, m_bind_pos_z, 0);
}

bool Player::HasQuestSpell(uint32 spellid) //Only for Cast Quests
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if (quest_spells.size()>0 && quest_spells.find(spellid) != quest_spells.end())
	{ 
		return true;
	}
	return false;
}
void Player::RemoveQuestSpell(uint32 spellid) //Only for Cast Quests
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if (quest_spells.size()>0)
		quest_spells.erase(spellid);
}

bool Player::HasQuestMob(uint32 entry) //Only for Kill Quests
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if (quest_mobs.size()>0 && quest_mobs.find(entry) != quest_mobs.end())
	{ 
		return true;
	}
	return false;
}

bool Player::HasQuest(uint32 entry) 
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	for(uint32 i=0;i<25;i++)
	{
		if ( m_questlog[i] != NULL && m_questlog[i]->GetQuest()->id == entry)
		{ 
		return true;
		}
	}
	return false;
}

void Player::RemoveQuestMob(uint32 entry) //Only for Kill Quests
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if (quest_mobs.size()>0)
		quest_mobs.erase(entry);
}

PlayerInfo::~PlayerInfo()
{
	if(m_Group)
	{
		m_Group->RemovePlayer(this);
		m_Group = NULL;
	}
}

void Player::CopyAndSendDelayedPacket(WorldPacket * data)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket * data2 = new WorldPacket(*data);
	delayedPackets.add(data2);
}

void Player::SendMeetingStoneQueue(uint32 DungeonId, uint8 Status)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(SMSG_MEETINGSTONE_SETQUEUE, 5);
	data << DungeonId << Status;
	m_session->SendPacket(&data);
}

void Player::PartLFGChannel()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	Channel * pChannel = channelmgr.GetChannel("LookingForGroup", this);
	if( pChannel == NULL )
	{ 
		return;
	}

	/*for(list<Channel*>::iterator itr = m_channels.begin(); itr != m_channels.end(); ++itr)
	{
		if( (*itr) == pChannel )
		{
			pChannel->Part(this);
			return;
		}
	}*/
	if( m_channels.find( pChannel) == m_channels.end() )
	{ 
		return;
	}

	pChannel->Part( this );
}

void Player::EventSummonPetCastSpell( Pet *new_pet, uint32 SpellID )
{
	SpellEntry *spellInfo = dbcSpell.LookupEntry( SpellID );
	if( spellInfo->c_is_flags & SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER )
	{
		this->RemoveAllAuras( SpellID, this->GetGUID() ); //this is required since unit::addaura does not check for talent stacking
		SpellCastTargets targets( this->GetGUID() );
		Spell *spell = SpellPool.PooledNew();
		spell->Init(this, spellInfo ,true, NULL);	//we cast it as a proc spell, maybe we should not !
		spell->prepare(&targets);
	}
	if( spellInfo->c_is_flags & SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET )
	{
		this->RemoveAllAuras( SpellID, this->GetGUID() ); //this is required since unit::addaura does not check for talent stacking
		SpellCastTargets targets( new_pet->GetGUID() );
		Spell *spell = SpellPool.PooledNew();
		spell->Init(this, spellInfo ,true, NULL);	//we cast it as a proc spell, maybe we should not !
		spell->prepare(&targets);
	}
}

//if we charmed or simply summoned a pet, this function should get called
void Player::EventSummonPet( Pet *new_pet )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if ( !new_pet )
		return ; //another wtf error

	//recast talents that are supposed to be casted on summon
	SpellSet::iterator it,iter;
	for(iter= mSpells.begin();iter != mSpells.end();)
	{
		it = iter++;
		uint32 SpellID = *it;
		EventSummonPetCastSpell( new_pet, SpellID );
	}
	//also reactivate glyphs taht require a summon
	for(int i=0;i<GLYPHS_COUNT;i++)
	{
		uint32 glyph_id = m_specs[ m_talentActiveSpec ].glyphs[ i ];
		if( !glyph_id )
			continue;
		GlyphPropertiesEntry *glyphprops = dbcGlyphPropertiesStore.LookupEntry( glyph_id );
		if( glyphprops == NULL )
			continue;
		EventSummonPetCastSpell( new_pet, glyphprops->SpellId );
	}
	//there are talents that stop working after you gain pet
	for(uint32 x=0;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_EXPIREING_ON_PET)
			m_auras[x]->Remove();
	//pet should inherit some of the talents from caster
	//new_pet->InheritSMMods(); //not required yet. We cast full spell to have visual effect too
	SetUInt64Value( UNIT_FIELD_SUMMON, new_pet->GetGUID() );
//	SetFlag(PLAYER_FIELD_BYTES, PLAYER_BYTES_FLAG_HAS_PET );
}

//if pet/charm died or whatever hapened we should call this function
//!! note function might get called multiple times :P
void Player::EventDismissPet()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	for(uint32 x=0;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
		if(m_auras[x] && (m_auras[x]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_EXPIREING_WITH_PET) )
		{
			SpellEntry *sp = m_auras[x]->GetSpellProto();
			for(uint32 i=0;i<3;i++)
				if( sp->Effect[i] == SPELL_EFFECT_TRIGGER_SPELL && sp->EffectTriggerSpell[i] )
					RemoveAura( sp->EffectTriggerSpell[i] );
			if( m_auras[x] )
				m_auras[x]->Remove();
		}
//	RemoveFlag(PLAYER_FIELD_BYTES,PLAYER_BYTES_FLAG_HAS_PET);
}

void Player::ForceAllPetTalentAndSpellReset()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//wipe all spells. We will auto relearn them at next login :)
	CharacterDatabase.Execute("DELETE FROM playerpetspells WHERE ownerguid=%u", GetLowGUID());
	//also reset active pet talents
	if( GetSummon() )
		GetSummon()->WipeTalents();
	//now how the hack i reset TP for offlines ? Better let player reset them :P
}

#ifdef ENABLE_COMPRESSED_MOVEMENT

CMovementCompressorThread *MovementCompressor;

void Player::AppendMovementData(uint32 op, uint32 sz, const uint8* data)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//printf("AppendMovementData(%u, %u, 0x%.8X)\n", op, sz, data);
	m_movementBufferLock.Acquire();
	m_movementBuffer << uint8(sz + 2);
	m_movementBuffer << uint16(op);
	m_movementBuffer.append( data, sz );
	m_movementBufferLock.Release();
}

bool CMovementCompressorThread::run()
{
	set<Player*>::iterator itr;
	while(running)
	{
		m_listLock.Acquire();
		for(itr = m_players.begin(); itr != m_players.end(); ++itr)
		{
			(*itr)->EventDumpCompressedMovement();
		}
		m_listLock.Release();
		Sleep(World::m_movementCompressInterval);
	}

	return true;
}

void CMovementCompressorThread::AddPlayer(Player * pPlayer)
{
	m_listLock.Acquire();
	m_players.insert(pPlayer);
	m_listLock.Release();
}

void CMovementCompressorThread::RemovePlayer(Player * pPlayer)
{
	m_listLock.Acquire();
	m_players.erase(pPlayer);
	m_listLock.Release();
}

void Player::EventDumpCompressedMovement()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( m_movementBuffer.size() == 0 )
	{ 
		return;
	}

	m_movementBufferLock.Acquire();
	uint32 size = (uint32)m_movementBuffer.size();
	uint32 destsize = size + size/10 + 16;
	int rate = World::m_movementCompressRate;
	if(size >= 40000 && rate < 6)
		rate = 6;
	if(size <= 100)
		rate = 0;			// don't bother compressing packet smaller than this, zlib doesnt really handle them well

	// set up stream
	z_stream stream;
	stream.zalloc = 0;
	stream.zfree  = 0;
	stream.opaque = 0;

	if(deflateInit(&stream, rate) != Z_OK)
	{
		sLog.outError("deflateInit failed.");
		m_movementBufferLock.Release();
		return;
	}

	uint8 *buffer = new uint8[destsize];

	// set up stream pointers
	stream.next_out  = (Bytef*)buffer+4;
	stream.avail_out = destsize;
	stream.next_in   = (Bytef*)m_movementBuffer.contents();
	stream.avail_in  = size;

	// call the actual process
	if(deflate(&stream, Z_NO_FLUSH) != Z_OK ||
		stream.avail_in != 0)
	{
		sLog.outError("deflate failed.");
		delete [] buffer;
		m_movementBufferLock.Release();
		return;
	}

	// finish the deflate
	if(deflate(&stream, Z_FINISH) != Z_STREAM_END)
	{
		sLog.outError("deflate failed: did not end stream");
		delete [] buffer;
		m_movementBufferLock.Release();
		return;
	}

	// finish up
	if(deflateEnd(&stream) != Z_OK)
	{
		sLog.outError("deflateEnd failed.");
		delete [] buffer;
		m_movementBufferLock.Release();
		return;
	}

	// fill in the full size of the compressed stream
#ifdef USING_BIG_ENDIAN
	*(uint32*)&buffer[0] = swap32(size);
#else
	*(uint32*)&buffer[0] = size;
#endif

	// send it
	m_session->OutPacket(SMSG_COMPRESSED_MOVES, (uint16)stream.total_out + 4, buffer);
	//printf("Compressed move compressed from %u bytes to %u bytes.\n", m_movementBuffer.size(), stream.total_out + 4);

	// cleanup memory
	delete [] buffer;
	m_movementBuffer.clear();
	m_movementBufferLock.Release();
}
#endif

void Player::AddShapeShiftSpell(uint32 id)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SpellEntry * sp = dbcSpell.LookupEntry( id );
	mShapeShiftSpells.insert( id );

	if( sp->RequiredShapeShift && ((uint32)1 << (GetShapeShift()-1)) & sp->RequiredShapeShift )
	{
		Spell * spe = SpellPool.PooledNew();
		spe->Init( this, sp, true, NULL );
		SpellCastTargets t(this->GetGUID());
		spe->prepare( &t );
	}
}

void Player::RemoveShapeShiftSpell(uint32 id)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	mShapeShiftSpells.erase( id );
	RemoveAura( id );
}

// COOLDOWNS
void Player::_Cooldown_Add(uint32 Type, uint32 Misc, uint32 Time, uint32 SpellId, uint32 ItemId, uint32 after_combat_cooldown)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	PlayerCooldownMap::iterator itr = m_cooldownMap[Type].find( Misc );
	if( itr != m_cooldownMap[Type].end( ) )
	{
		if( itr->second.ExpireTime < Time )
		{
			if( after_combat_cooldown )
			{
				itr->second.ExpireTime = PLAYER_SPELL_COOLDOWN_NOT_STARTED;
				itr->second.ExpiretimeAfterCombat = Time;
			}
			else
			{
				itr->second.ExpireTime = Time;
				itr->second.ExpiretimeAfterCombat = 0;
			}
			itr->second.ItemId = ItemId;
			itr->second.SpellId = SpellId;
		}
	}
	else
	{
		PlayerCooldown cd;
		if( after_combat_cooldown )
		{
			cd.ExpireTime = PLAYER_SPELL_COOLDOWN_NOT_STARTED;
			cd.ExpiretimeAfterCombat = Time;
		}
		else
		{
			cd.ExpireTime = Time;
			cd.ExpiretimeAfterCombat = 0;
		}
		cd.ItemId = ItemId;
		cd.SpellId = SpellId;

		m_cooldownMap[Type].insert( make_pair( Misc, cd ) );
	}

#ifdef _DEBUG
	Log.Debug("Cooldown", "added cooldown for type %u misc %u time %u item %u spell %u", Type, Misc, Time - getMSTime(), ItemId, SpellId);
#endif
}

void Player::Cooldown_Add(SpellEntry * pSpell, Item * pItemCaster)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 mstime = getMSTime();
	int32 cool_time;

	if( pSpell->CategoryRecoveryTime > 0 && pSpell->Category )
	{
		cool_time = pSpell->CategoryRecoveryTime;
		if( Need_SM_Apply(pSpell) )
		{
			SM_FIValue(SM_FCooldownTime, &cool_time, pSpell->SpellGroupType);
			SM_PIValue(SM_PCooldownTime, &cool_time, pSpell->SpellGroupType);
		}

		//haste rating affecting global cooldown
		cool_time = float2int32( cool_time * GetSpellHaste() );
		//no spams at all please
		if( cool_time < 1500 )
			cool_time = 1500;
		_Cooldown_Add( COOLDOWN_TYPE_CATEGORY, pSpell->Category, mstime + cool_time, pSpell->Id, pItemCaster ? pItemCaster->GetProto()->ItemId : 0 );
	}
	
	if( pSpell->RecoveryTime > 0 )
	{
		cool_time = pSpell->RecoveryTime;
		if( Need_SM_Apply(pSpell) )
		{
			SM_FIValue(SM_FCooldownTime, &cool_time, pSpell->SpellGroupType);
			SM_PIValue(SM_PCooldownTime, &cool_time, pSpell->SpellGroupType);
		}

		//haste rating affecting global cooldown
		cool_time = float2int32( cool_time * GetSpellHaste() );
		//no spams at all please
		if( cool_time < 1500 )
			cool_time = 1500;
		_Cooldown_Add( COOLDOWN_TYPE_SPELL, pSpell->Id, mstime + cool_time, pSpell->Id, pItemCaster ? pItemCaster->GetProto()->ItemId : 0 );
	}
}

void Player::Cooldown_AddStart(SpellEntry * pSpell)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( pSpell->StartRecoveryTime == 0 )
	{ 
		return;
	}

	uint32 mstime = getMSTime();
	int32 atime = float2int32( float( pSpell->StartRecoveryTime ) * GetSpellHaste() );


	if( atime < 1000 )	// global cooldown is limited to 1s
		atime = 1000;

	if( pSpell->StartRecoveryCategory )		// if we have a different cool category to the actual spell category - only used by few spells
		_Cooldown_Add( COOLDOWN_TYPE_CATEGORY, pSpell->StartRecoveryCategory, mstime + atime, pSpell->Id, 0 );
	/*else if( pSpell->Category )				// cooldowns are grouped
		_Cooldown_Add( COOLDOWN_TYPE_CATEGORY, pSpell->Category, mstime + pSpell->StartRecoveryTime, pSpell->Id, 0 );*/
	//all spells that are not triggered have at least 1.5 ms cooldown time
//	else									// no category, so it's a gcd
	{
#ifdef _DEBUG
		Log.Debug("Cooldown", "Global cooldown adding: %u ms", atime );
#endif
		m_globalCooldown = mstime + atime;
	}
}

bool Player::Cooldown_CanCast(SpellEntry * pSpell)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	PlayerCooldownMap::iterator itr;
	uint32 mstime = getMSTime();

	if( pSpell->Category )
	{
		itr = m_cooldownMap[COOLDOWN_TYPE_CATEGORY].find( pSpell->Category );
		if( itr != m_cooldownMap[COOLDOWN_TYPE_CATEGORY].end( ) )
		{
			if( mstime < itr->second.ExpireTime )
			{ 
				return false;
			}
			else
				//Zack : this is corrupting the whole thing somehow. Need to remake all later
				m_cooldownMap[COOLDOWN_TYPE_CATEGORY].erase( itr );
		}		
	}

	itr = m_cooldownMap[COOLDOWN_TYPE_SPELL].find( pSpell->Id );
	if( itr != m_cooldownMap[COOLDOWN_TYPE_SPELL].end( ) )
	{
		if( mstime < itr->second.ExpireTime )
		{ 
			return false;
		}
		else
			//Zack : this is corrupting the whole thing somehow. Need to remake all later
			m_cooldownMap[COOLDOWN_TYPE_SPELL].erase( itr );
	}

	if( pSpell->StartRecoveryTime && m_globalCooldown )			/* gcd doesn't affect spells without a cooldown it seems */
	{
		if( mstime < m_globalCooldown )
		{ 
			return false;
		}
		else
			m_globalCooldown = 0;
	}

	return true;
}

void Player::Cooldown_AddItem(ItemPrototype * pProto, uint32 x, uint32 after_combat_cooldown)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( pProto->Spells[x].CategoryCooldown <= 0 && pProto->Spells[x].Cooldown <= 0 )
	{ 
		return;
	}

	ItemSpell * isp = &pProto->Spells[x];
	uint32 mstime = getMSTime();

	if( after_combat_cooldown && CombatStatus.IsInCombat() == false )
	{
		packetSMSG_COOLDOWN_EVENT data;
		data.guid = GetGUID();
		data.spellid = isp->Id;
		OutPacketToSet( SMSG_COOLDOWN_EVENT, sizeof( packetSMSG_COOLDOWN_EVENT ), &data, true );
		after_combat_cooldown = 0;
	}

	if( isp->CategoryCooldown > 0)
		_Cooldown_Add( COOLDOWN_TYPE_CATEGORY, isp->Category, isp->CategoryCooldown + mstime, isp->Id, pProto->ItemId, after_combat_cooldown );

	if( isp->Cooldown > 0 )
		_Cooldown_Add( COOLDOWN_TYPE_SPELL, isp->Id, isp->Cooldown + mstime, isp->Id, pProto->ItemId , after_combat_cooldown );
}

void Player::StartOutOfCombatCooldowns()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	PlayerCooldownMap::iterator itr;
	packetSMSG_COOLDOWN_EVENT data;
	data.guid = GetGUID();
	for(itr = m_cooldownMap[COOLDOWN_TYPE_SPELL].begin();itr!=m_cooldownMap[COOLDOWN_TYPE_SPELL].end();itr++)
		if( itr->second.ExpireTime == PLAYER_SPELL_COOLDOWN_NOT_STARTED )
		{
			data.spellid = itr->second.SpellId;
			itr->second.ExpireTime = itr->second.ExpiretimeAfterCombat;
			OutPacketToSet( SMSG_COOLDOWN_EVENT, sizeof( packetSMSG_COOLDOWN_EVENT ), &data, true );
		}
	for(itr = m_cooldownMap[COOLDOWN_TYPE_CATEGORY].begin();itr!=m_cooldownMap[COOLDOWN_TYPE_CATEGORY].end();itr++)
		if( itr->second.ExpireTime == PLAYER_SPELL_COOLDOWN_NOT_STARTED )
		{
			data.spellid = itr->second.SpellId;
			itr->second.ExpireTime = itr->second.ExpiretimeAfterCombat;
			OutPacketToSet( SMSG_COOLDOWN_EVENT, sizeof( packetSMSG_COOLDOWN_EVENT ), &data, true );
		}
}

#define COOLDOWN_SKIP_SAVE_IF_MS_LESS_THAN 10000

void Player::_SavePlayerCooldowns(QueryBuffer * buf)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	PlayerCooldownMap::iterator itr;
	PlayerCooldownMap::iterator itr2;
	uint32 i;
	uint32 seconds;
	uint32 mstime = getMSTime();

	// clear them (this should be replaced with an update queue later)
	if( buf != NULL )
		buf->AddQuery("DELETE FROM playercooldowns WHERE player_guid = %u", m_uint32Values[OBJECT_FIELD_GUID] );		// 0 is guid always
	else
		CharacterDatabase.Execute("DELETE FROM playercooldowns WHERE player_guid = %u", m_uint32Values[OBJECT_FIELD_GUID] );		// 0 is guid always

	for( i = 0; i < NUM_COOLDOWN_TYPES; ++i )
	{
		itr = m_cooldownMap[i].begin( );
		for( ; itr != m_cooldownMap[i].end( ); )
		{
			itr2 = itr++;

			// expired ones - no point saving, nor keeping them around, wipe em
			if( mstime >= itr2->second.ExpireTime )
			{
				m_cooldownMap[i].erase( itr2 );	//just a very vague huntch this is creating some multi threading issues. Like e are erasing and using it somewhere else.
				continue;
			}
			
			// skip small cooldowns which will end up expiring by the time we log in anyway
			if( ( itr2->second.ExpireTime - mstime ) < COOLDOWN_SKIP_SAVE_IF_MS_LESS_THAN )
				continue;

			// work out the cooldown expire time in unix timestamp format
			// burlex's reason: 30 day overflow of 32bit integer, also
			// under windows we use GetTickCount() which is the system uptime, if we reboot
			// the server all these timestamps will appear to be messed up.
			
			uint32 rawtime;
			if( itr2->second.ExpireTime == PLAYER_SPELL_COOLDOWN_NOT_STARTED )
				rawtime = itr2->second.ExpiretimeAfterCombat;
			else 
				rawtime = itr2->second.ExpireTime;
			uint32 diffMS = (rawtime - mstime);

			//avoid saving mem corruptions
			SpellEntry *sp = dbcSpell.LookupEntryForced( itr2->second.SpellId );
			if( sp != NULL )
			{
				if( i == COOLDOWN_TYPE_CATEGORY && diffMS > sp->CategoryRecoveryTime )
					continue;
				else if( i == COOLDOWN_TYPE_SPELL && diffMS > sp->RecoveryTime )
					continue;
			}
			else
				continue;

			seconds = diffMS / 1000;

			// this shouldnt ever be nonzero because of our check before, so no check needed
			
			if( buf != NULL )
			{
				buf->AddQuery( "INSERT INTO playercooldowns VALUES(%u, %u, %u, %u, %u, %u)", m_uint32Values[OBJECT_FIELD_GUID],
					i, itr2->first, seconds + (uint32)UNIXTIME, itr2->second.SpellId, itr2->second.ItemId );
			}
			else
			{
				CharacterDatabase.Execute( "INSERT INTO playercooldowns VALUES(%u, %u, %u, %u, %u, %u)", m_uint32Values[OBJECT_FIELD_GUID],
					i, itr2->first, seconds + (uint32)UNIXTIME, itr2->second.SpellId, itr2->second.ItemId );
			}
		}
	}
}

void Player::_LoadPlayerCooldowns(QueryResult * result)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( result == NULL )
	{ 
		return;
	}

	// we should only really call getMSTime() once to avoid user->system transitions, plus
	// the cost of calling a function for every cooldown the player has
	uint32 mstime = getMSTime();
	uint32 type;
	uint32 misc;
	uint32 rtime;
	uint32 realtime;
	uint32 itemid;
	uint32 spellid;
	uint32 local_unixtime = (uint32)UNIXTIME;	//conversion acceptable since we are not going to restart server in ages

	do 
	{
		type = result->Fetch()[0].GetUInt32();
		misc = result->Fetch()[1].GetUInt32();
		rtime = result->Fetch()[2].GetUInt32();
		spellid = result->Fetch()[3].GetUInt32();
		itemid = result->Fetch()[4].GetUInt32();

		if( type >= NUM_COOLDOWN_TYPES )
			continue;

		// remember the cooldowns were saved in unix timestamp format for the reasons outlined above,
		// so restore them back to mstime upon loading

		if( local_unixtime >= rtime )
			continue;

		rtime -= local_unixtime;

		if( rtime < 10 )	//10 seconds is just not worth loading
			continue;

		rtime = rtime * 1000;	//convert into milliseconds

		//see if this cooldown is bugged ? Maybe there was a spellfix meantime we had this issue
		SpellEntry *sp = dbcSpell.LookupEntryForced( spellid );
		if( sp != NULL )
		{
			if( type == COOLDOWN_TYPE_CATEGORY && rtime >= sp->CategoryRecoveryTime )
				continue;
			else if( type == COOLDOWN_TYPE_SPELL && rtime >= sp->RecoveryTime )
				continue;
		}
		else 
			continue;	//wtf ? item cooldown but without spell ? 

		realtime = mstime + rtime;

		// apply it back into cooldown map
		PlayerCooldown cd;
		cd.ExpireTime = realtime;
		cd.ItemId = itemid;
		cd.SpellId = spellid;
		m_cooldownMap[type].insert( make_pair( misc, cd ) );

	} while ( result->NextRow( ) );
}

void Player::_FlyhackCheck()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(!sWorld.antihack_flight || m_TransporterGUID != 0 || GetTaxiState() || (sWorld.no_antihack_on_gm && GetSession()->HasPermissions()))
	{ 
		return;
	}

	MovementInfo * mi = GetSession()->GetMovementInfo();
	if(!mi) return; //wtf?

	// Falling, CCs, etc. All stuff that could potentially trap a player in mid-air.
	if(!(mi->flags & (MOVEFLAG_FALLING | MOVEFLAG_SWIMMING | MOVEFLAG_LEVITATE | MOVEFLAG_FEATHER_FALL)) &&
		!(m_special_state & (UNIT_STATE_CHARM | UNIT_STATE_FEAR | UNIT_STATE_ROOT | UNIT_STATE_STUN | UNIT_STATE_POLYMORPH | UNIT_STATE_CONFUSE | UNIT_STATE_FROZEN))
		&& !flying_aura && !FlyCheat)
	{
		float t_height = CollideInterface.GetHeight(GetMapId(), GetPositionX(), GetPositionY(), GetPositionZ() + 2.0f);
		if(t_height == WMO_VMAP_VALUE_NOT_INITIALIZED || t_height == NO_WMO_HEIGHT )
			t_height = GetMapMgr()->GetLandHeight(GetPositionX(), GetPositionY());
		if(t_height == WMO_VMAP_VALUE_NOT_INITIALIZED || t_height == NO_WMO_HEIGHT) // Can't rely on anyone these days...
		{ 
			return;
		}

		float p_height = GetPositionZ();

		int32 diff = float2int32(p_height - t_height);
		if(diff < 0)
			diff = -diff;

		if(t_height != p_height && (uint32)diff > sWorld.flyhack_threshold)
		{
			// Fly hax!
			EventTeleport(GetMapId(), GetPositionX(), GetPositionY(), t_height + 2.0f); // relog fix.
			sCheatLog.writefromsession(GetSession(), "Caught fly hacking on map %u hovering %u over the terrain.", GetMapId(), diff);
			GetSession()->Disconnect();
		}
	}
}

/************************************************************************/
/* SOCIAL                                                               */
/************************************************************************/

void Player::Social_AddFriend(const char * name, const char * note)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(SMSG_FRIEND_STATUS, 10);
	map<uint32, char*>::iterator itr;

	// lookup the player
	PlayerInfo* info = objmgr.GetPlayerInfoByName(name);
	Player* player = objmgr.GetPlayer(name, false);

	if( info == NULL || ( player != NULL && player->GetSession() && player->GetSession()->HasPermissions() ) )
	{
		data << uint8(FRIEND_NOT_FOUND);
		m_session->SendPacket(&data);
		return;
	}

	// team check
	if( info->team != m_playerInfo->team  && m_session->permissioncount == 0 && !sWorld.interfaction_friend)
	{
		data << uint8(FRIEND_ENEMY) << uint64(info->guid);
		m_session->SendPacket(&data);
		return;
	}

	// are we ourselves?
	if( info == m_playerInfo )
	{
		data << uint8(FRIEND_SELF) << GetGUID();
		m_session->SendPacket(&data);
		return;
	}

	m_socialLock.Acquire();
	itr = m_friends.find(info->guid);
	if( itr != m_friends.end() )
	{
		data << uint8(FRIEND_ALREADY) << uint64(info->guid);
		m_session->SendPacket(&data);
		m_socialLock.Release();
		return;
	}

	if( info->m_loggedInPlayer != NULL )
	{
		data << uint8(FRIEND_ADDED_ONLINE);
		data << uint64(info->guid);
		if( note != NULL )
			data << note;
		else
			data << uint8(0);

		data << uint8(1);
		data << info->m_loggedInPlayer->GetZoneId();
		data << info->lastLevel;
		data << uint32(info->cl);

		info->m_loggedInPlayer->m_socialLock.Acquire();
		info->m_loggedInPlayer->m_hasFriendList.insert( GetLowGUID() );
		info->m_loggedInPlayer->m_socialLock.Release();
	}
	else
	{
		data << uint8(FRIEND_ADDED_OFFLINE);
		data << uint64(info->guid);
	}

	if( note != NULL )
		m_friends.insert( make_pair(info->guid, strdup_local(note)) );
	else
		m_friends.insert( make_pair(info->guid, (char*)NULL) );

	m_socialLock.Release();
	m_session->SendPacket(&data);

	// dump into the db
	CharacterDatabase.Execute("INSERT INTO social_friends VALUES(%u, %u, \"%s\")",
		GetLowGUID(), info->guid, note ? CharacterDatabase.EscapeString(string(note)).c_str() : "");
}

void Player::Social_RemoveFriend(uint32 guid)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(SMSG_FRIEND_STATUS, 10);
	map<uint32, char*>::iterator itr;

	// are we ourselves?
	if( guid == GetLowGUID() )
	{
		data << uint8(FRIEND_SELF) << GetGUID();
		m_session->SendPacket(&data);
		return;
	}

	m_socialLock.Acquire();
	itr = m_friends.find(guid);
	if( itr != m_friends.end() )
	{
		if( itr->second != NULL )
			free(itr->second);

		m_friends.erase(itr);
	}

	data << uint8(FRIEND_REMOVED);
	data << uint64(guid);

	m_socialLock.Release();

	Player * pl = objmgr.GetPlayer( (uint32)guid );
	if( pl != NULL )
	{
		pl->m_socialLock.Acquire();
		pl->m_hasFriendList.erase( GetLowGUID() );
		pl->m_socialLock.Release();
	}

	m_session->SendPacket(&data);

	// remove from the db
	CharacterDatabase.Execute("DELETE FROM social_friends WHERE character_guid = %u AND friend_guid = %u", 
		GetLowGUID(), (uint32)guid);
}

void Player::Social_SetNote(uint32 guid, const char * note)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	map<uint32,char*>::iterator itr;

	m_socialLock.Acquire();
	itr = m_friends.find(guid);

	if( itr == m_friends.end() )
	{
		m_socialLock.Release();
		return;
	}

	if( itr->second != NULL )
		free(itr->second);

	if( note != NULL )
		itr->second = strdup_local( note );
	else
		itr->second = NULL;

	m_socialLock.Release();
	CharacterDatabase.Execute("UPDATE social_friends SET note = \"%s\" WHERE character_guid = %u AND friend_guid = %u",
		note ? CharacterDatabase.EscapeString(string(note)).c_str() : "", GetLowGUID(), guid);
}

void Player::Social_AddIgnore(const char * name)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(SMSG_FRIEND_STATUS, 10);
	set<uint32>::iterator itr;
	PlayerInfo * info;

	// lookup the player
	info = objmgr.GetPlayerInfoByName(name);
	if( info == NULL )
	{
		data << uint8(FRIEND_IGNORE_NOT_FOUND);
		m_session->SendPacket(&data);
		return;
	}

	// are we ourselves?
	if( info == m_playerInfo )
	{
		data << uint8(FRIEND_IGNORE_SELF) << GetGUID();
		m_session->SendPacket(&data);
		return;
	}

	m_socialLock.Acquire();
	itr = m_ignores.find(info->guid);
	if( itr != m_ignores.end() )
	{
		data << uint8(FRIEND_IGNORE_ALREADY) << uint64(info->guid);
		m_session->SendPacket(&data);
		m_socialLock.Release();
		return;
	}

	data << uint8(FRIEND_IGNORE_ADDED);
	data << uint64(info->guid);

	m_ignores.insert( info->guid );

	m_socialLock.Release();
	m_session->SendPacket(&data);

	// dump into db
	CharacterDatabase.Execute("INSERT INTO social_ignores VALUES(%u, %u)", GetLowGUID(), info->guid);
}

void Player::Social_RemoveIgnore(uint32 guid)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(SMSG_FRIEND_STATUS, 10);
	set<uint32>::iterator itr;

	// are we ourselves?
	if( guid == GetLowGUID() )
	{
		data << uint8(FRIEND_IGNORE_SELF) << GetGUID();
		m_session->SendPacket(&data);
		return;
	}

	m_socialLock.Acquire();
	itr = m_ignores.find(guid);
	if( itr != m_ignores.end() )
	{
		m_ignores.erase(itr);
	}

	data << uint8(FRIEND_IGNORE_REMOVED);
	data << uint64(guid);

	m_socialLock.Release();

	m_session->SendPacket(&data);

	// remove from the db
	CharacterDatabase.Execute("DELETE FROM social_ignores WHERE character_guid = %u AND ignore_guid = %u", 
		GetLowGUID(), (uint32)guid);
}

bool Player::Social_IsIgnoring(PlayerInfo * m_info)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	bool res;
	m_socialLock.Acquire();
	if( m_ignores.find( m_info->guid ) == m_ignores.end() )
		res = false;
	else
		res = true;

	m_socialLock.Release();
	return res;
}

bool Player::Social_IsIgnoring(uint32 guid)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	bool res;
	m_socialLock.Acquire();
	if( m_ignores.find( guid ) == m_ignores.end() )
		res = false;
	else
		res = true;

	m_socialLock.Release();
	return res;
}

void Player::Social_TellFriendsOnline()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( m_hasFriendList.empty() || ( GetSession() && GetSession()->HasPermissions() ) )
	{ 
		return;
	}

	WorldPacket data(SMSG_FRIEND_STATUS, 22);
	set<uint32>::iterator itr;
	Player * pl;
	data << uint8( FRIEND_ONLINE ) << GetGUID() << uint8( 1 );
	data << GetAreaID() << getLevel() << uint32(getClass());

	m_socialLock.Acquire();
	for( itr = m_hasFriendList.begin(); itr != m_hasFriendList.end(); ++itr )
	{
		pl = objmgr.GetPlayer(*itr);
		if( pl != NULL )
			pl->GetSession()->SendPacket(&data);
	}
	m_socialLock.Release();
}

void Player::Social_TellFriendsOffline()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( m_hasFriendList.empty() || ( GetSession() && GetSession()->HasPermissions() ) )
	{ 
		return;
	}

	WorldPacket data(SMSG_FRIEND_STATUS, 10);
	set<uint32>::iterator itr;
	Player * pl;
	data << uint8( FRIEND_OFFLINE ) << GetGUID() << uint8( 0 );

	m_socialLock.Acquire();
	for( itr = m_hasFriendList.begin(); itr != m_hasFriendList.end(); ++itr )
	{
		pl = objmgr.GetPlayer(*itr);
		if( pl != NULL )
			pl->GetSession()->SendPacket(&data);
	}
	m_socialLock.Release();
}

void Player::Social_SendFriendList(uint32 flag)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(SMSG_CONTACT_LIST, 500);
	map<uint32,char*>::iterator itr;
	set<uint32>::iterator itr2;
	Player * plr;

	m_socialLock.Acquire();

	data << flag;
	data << uint32( m_friends.size() + m_ignores.size() );
	for( itr = m_friends.begin(); itr != m_friends.end(); ++itr )
	{
		// guid
		data << uint64( itr->first );

		// friend/ignore flag.
		// 1 - friend
		// 2 - ignore
		// 3 - muted?
		data << uint32( 1 );

		// player note
		if( itr->second != NULL )
			data << itr->second;
		else
			data << uint8(0);

		// online/offline flag
		plr = objmgr.GetPlayer( itr->first );
		if( plr != NULL )
		{
			data << uint8( 1 );
			data << plr->GetZoneId();
			data << plr->getLevel();
			data << uint32( plr->getClass() );
		}
		else
			data << uint8( 0 );
	}

	for( itr2 = m_ignores.begin(); itr2 != m_ignores.end(); ++itr2 )
	{
		// guid
		data << uint64( (*itr2) );
		
		// ignore flag - 2
		data << uint32( 2 );

		// no note
		data << uint8( 0 );
	}

	m_socialLock.Release();
	m_session->SendPacket(&data);
}

void Player::SpeedCheatDelay(uint32 ms_delay)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
 
//	SDetector->SkipSamplingUntil( getMSTime() + ms_delay ); 
	//add tripple latency to avoid client handleing the spell effect with delay and we detect as cheat
//	SDetector->SkipSamplingUntil( getMSTime() + ms_delay + GetSession()->GetLatency() * 3 ); 
	//add constant value to make sure the effect packet was sent to client from network pool
//	SDetector->SkipSamplingUntil( getMSTime() + ms_delay + GetSession()->GetLatency() * 2 + 2000 ); //2 second should be enough to send our packets to client
	//started using client provided stamps to avoid using packet latency
	SDetector->SkipSamplingFor( ms_delay );
}

void Player::SpeedCheatReset()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
 
	SDetector->EventSpeedChange(); 
}

uint32 Player::GetMaxPersonalRating()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 maxrating = 0;
	int i;

	ASSERT(m_playerInfo != NULL);

	for (i=0; i<NUM_ARENA_TEAM_TYPES; i++)
	{
		if(m_arenaTeams[i] != NULL)
		{
			ArenaTeamMember *m = m_arenaTeams[i]->GetMemberByGuid(m_playerInfo->guid);
			if (m)
			{
				if (m->PersonalRating > maxrating) maxrating = m->PersonalRating;
			}
			else
			{
				sLog.outError("%s: GetMemberByGuid returned NULL for player guid = %u\n", __FUNCTION__, m_playerInfo->guid);
			}
		}
	}

	return maxrating;
}

void Player::SetKnownTitle( RankTitles title, bool set )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	
	if( title > PVPTITLE_END || 
		( set == true && HasKnownTitle( title ) == true ) )
	{ 
		return;
	}

	//maybe later this will be extended ?
	if( GetTeam() == 1 && title>=PVPTITLE_SCOUT && title<=PVPTITLE_HIGH_WARLORD )
		Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_OWN_PVP_RANK,title-13,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_SET);
	else if( GetTeam() == 0 && title>=PVPTITLE_PRIVATE && title<=PVPTITLE_GRAND_MARSHAL )
		Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_OWN_PVP_RANK,title,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_SET);

	uint32	int_index = title / 32;
	if( int_index > ( PLAYER_FIELD_KNOWN_TITLES2 - PLAYER_FIELD_KNOWN_TITLES ) )
		return;	//invalid title
	uint32	bitmask = 1 << ( title % 32 );
	uint32  current = GetUInt32Value( PLAYER_FIELD_KNOWN_TITLES + int_index );
	if( set )
		SetUInt32Value( PLAYER_FIELD_KNOWN_TITLES + int_index, current | bitmask );
	else
		SetUInt32Value( PLAYER_FIELD_KNOWN_TITLES + int_index, current & ( ~bitmask ) );
	
//	if( title >= PVPTITLE_END ) // to avoid client crash
//	{ 
//		return;
//	}
	
	//search for DBC entry that will have this title (lame -> this is used only by quests !)
/*	CharTitlesEntry *ce = NULL;
	for(uint32 x=0; x < dbcCharTitle.GetNumRows(); x++)
	{
		ce = dbcCharTitle.LookupRow(x);
		if( ce->bit_index == title )
			break;
	}
	if( ce && ce->bit_index == title )*/
	{
		WorldPacket data( SMSG_TITLE_EARNED, 8 );
//		data << uint32( ce->ID ) << uint32( set ? 1 : 0 );
		data << uint32( title ) << uint32( set ? 1 : 0 );
		m_session->SendPacket( &data );
	}
}

void Player::FullHPMP()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if(IsDead())
		ResurrectPlayer();
    SetUInt32Value(UNIT_FIELD_HEALTH, GetUInt32Value(UNIT_FIELD_MAXHEALTH));
    SetUInt32Value(UNIT_FIELD_POWER1, GetUInt32Value(UNIT_FIELD_MAXPOWER1));
    SetUInt32Value(UNIT_FIELD_POWER4, GetUInt32Value(UNIT_FIELD_MAXPOWER4));
}

bool Player::Achiement_Has_Finished(uint32 achicritentry)
{
	return ( m_achievements[ achicritentry ]->completed_at_stamp > 0 );
}

void Player::Achiement_Remove(uint32 AchievementID)
{
	std::map<uint32,AchievementVal*>::iterator itr = m_achievements.find( AchievementID );
	if( itr != m_achievements.end() )
	{
		delete itr->second;
		m_achievements.erase( itr );
	}
}

bool Player::Achiement_Finished_Add(uint32 achicritentry)
{
	bool ret = false;
	AchievementCriteriaEntry *ace = dbcAchievementCriteriaStore.LookupEntryForced( achicritentry );
	if( ace == NULL )
		return false;

	//check if this achievement is even for us
	AchievementEntry *achi = dbcAchievementStore.LookupEntry( ace->referredAchievement );
	if( achi == NULL )
		return false;

	if( !m_achievements[ achicritentry ] )
	{
		ret = true;
		m_achievements[ achicritentry ] = new AchievementVal;
		if( m_achievements[ achicritentry ] == NULL )
			return false; // no frikin way
	}

	m_achievement_points += achi->points;
	m_achievements[ achicritentry ]->completed_at_stamp = (uint32)UNIXTIME;
	SendAchievmentEarned( ace->referredAchievement );
	//this might loop several times !
	Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ARCHIEVEMENT,ace->referredAchievement,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
		
	//if we got here then we could update our status
	m_achievements[ achicritentry ]->cur_value = ace->raw.requiredAchievementRelatedCount;

	return ret;
}

//really need to work on the speed of this. This will be called on a lot of events
//pentry_0 and pentry_1 kinda represent values from DBC col 3 and 4. But only if check is required to be made on these 2 columns
//the actual value would be stored in pvalue that can be added or set to status counter
//if status counter is above a tresh hold given by template then the rewards should be added to player
//counter limit most of the time is also stored on col 4, in this case pentry_1 == ACHIEVEMENT_UNUSED_FIELD_VALUE, and pvalue = val and action = ACHIEVEMENT_EVENT_ACTION_SET
void Player::Event_Achiement_Received(uint32 achievementtype,uint32 check_1,uint32 check_2,uint32 pvalue,uint32 action)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( achievementtype >= ACHIEVEMENT_CRITERIA_TYPE_TOTAL )
	{
		sLog.outDebug("Player received achievement greater then max we know about : %u (exiting)",achievementtype);
		return;
	}
	std::list<AchievementCriteriaEntry*>::iterator itr;
    for (itr = dbcBoostedAchievementLookup[achievementtype].begin(); itr != dbcBoostedAchievementLookup[achievementtype].end(); itr++)
    {
		uint32 achicritentry = (*itr)->ID;

		//we will send only this if it is required for this type
		if( check_1 != ACHIEVEMENT_UNUSED_FIELD_VALUE && (*itr)->raw.requiredAchievementRelatedEntry != check_1 )
			continue;
		//if pentry_1 != ACHIEVEMENT_UNUSED_FIELD_VALUE then col 4 is not counter value but requires a check instead with fixed value 
		if( check_2 != ACHIEVEMENT_UNUSED_FIELD_VALUE && (*itr)->raw.requiredAchievementRelatedCount != check_2 )
			continue;

		//special tests :(
		if( achievementtype == ACHIEVEMENT_CRITERIA_TYPE_DAMAGE_DONE && (*itr)->healing_done.mapid != GetMapId() )
			continue;
		else if( achievementtype == ACHIEVEMENT_CRITERIA_TYPE_HEALING_DONE && (*itr)->healing_done.mapid != GetMapId() )
			continue;
		else if( achievementtype == ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS && ( (*itr)->healing_done.mapid != 0 && (*itr)->healing_done.mapid != GetMapId() ) )
			continue;

		//check if this achievement is even for us
		AchievementEntry *achi = dbcAchievementStore.LookupEntry( (*itr)->referredAchievement );
		if( !achi 
			|| achi->points == 0 //wtf ? why have things like this ? just a showoff ?
			|| !( achi->factionFlag == -1 || GetTeam()==(1-achi->factionFlag))
			|| !( achi->mapID == -1 || achi->mapID == GetMapId() )
//			|| ((criteria->groupFlag & ACHIEVEMENT_CRITERIA_GROUP_NOT_IN_GROUP) && GetGroup() )
			)
			continue;
		if( (*itr)->requires_heroic_instance && IS_HEROIC_INSTANCE_DIFFICULTIE( GetMapMgr()->instance_difficulty ) == false )
			continue;
		if( (*itr)->requires_player_count == 5 && GetMapMgr()->instance_difficulty != INSTANCE_MODE_DUNGEON_NORMAL && GetMapMgr()->instance_difficulty != INSTANCE_MODE_DUNGEON_HEROIC )
			continue;
		else if( (*itr)->requires_player_count == 10 && GetMapMgr()->instance_difficulty != INSTANCE_MODE_RAID_10_MAN && GetMapMgr()->instance_difficulty != INSTANCE_MODE_RAID_10_MAN_HEROIC )
			continue;
		else if( (*itr)->requires_player_count == 25 && GetMapMgr()->instance_difficulty != INSTANCE_MODE_RAID_25_MAN && GetMapMgr()->instance_difficulty != INSTANCE_MODE_RAID_25_MAN_HEROIC )
			continue;
		if( (*itr)->requires_arenta_team_type_check != 0 && ( m_bg == NULL || (*itr)->requires_arenta_team_type_check != m_bg->GetArenaTeamType() ) )
			continue;

		if( !m_achievements[ achicritentry ] )
		{
			m_achievements[ achicritentry ] = new AchievementVal;
			if( m_achievements[ achicritentry ] == NULL )
				continue; // no frikin way
		}

		uint32 new_val;

		if( action == ACHIEVEMENT_EVENT_ACTION_SET )
			new_val = pvalue;
		if( action == ACHIEVEMENT_EVENT_ACTION_SET_MAX )
			new_val = MAX( pvalue, m_achievements[ achicritentry ]->cur_value );
		else if ( action == ACHIEVEMENT_EVENT_ACTION_ADD )
			new_val = m_achievements[ achicritentry ]->cur_value + pvalue;

		if( check_2 != ACHIEVEMENT_UNUSED_FIELD_VALUE // make sure column is actually a counter column
				|| ( new_val >= (*itr)->raw.requiredAchievementRelatedCount 
						&& m_achievements[ achicritentry ]->completed_at_stamp == 0 //not yet completed test
//						&& m_achievements[ achicritentry ]->cur_value < (*itr)->raw.requiredAchievementRelatedCount //not yet completed test
						)
			)
			{
				m_achievements[ achicritentry ]->completed_at_stamp = (uint32)UNIXTIME;
				//check if this is a grouped achievement. Completing one requires to complete many more.
				bool has_completed_all = true;
				uint32 requires_multi_complete = 0;
				std::list<AchievementCriteriaEntry*>::iterator itr2;
				for (itr2 = dbcBoostedAchievementLookup[achievementtype].begin(); itr2 != dbcBoostedAchievementLookup[achievementtype].end(); itr2++)
					if( (*itr2)->referredAchievement == (*itr)->referredAchievement && m_achievements.find( (*itr2)->ID ) == m_achievements.end() )
					{
						requires_multi_complete++;
						has_completed_all = false; 
						break;
					}
				//sadly we are not awarding grouped achievement as long as sub achievements are not completed
				if( has_completed_all == true )
				{
					if( requires_multi_complete > 1 )
						for (itr2 = dbcBoostedAchievementLookup[achievementtype].begin(); itr2 != dbcBoostedAchievementLookup[achievementtype].end(); itr2++)
							if( (*itr2)->referredAchievement == (*itr)->referredAchievement )
								m_achievements[ (*itr2)->ID ]->cur_value &= ~ACHIVEMENTS_EVIL_PENDING_STATUS_FLAG;
					SendAchievmentEarned( (*itr)->referredAchievement );
					m_achievement_points += achi->points;
					GiveAchievementReward( achi );
					//this might loop several times !
					Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ARCHIEVEMENT,(*itr)->referredAchievement,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
				}
				else
				{
					new_val |= ACHIVEMENTS_EVIL_PENDING_STATUS_FLAG;
					SendAchievmentStatus( (*itr)->ID, 1, TimeToGametime( UNIXTIME ) );
				}
			}
			
		//hmm, packet spam much ? 
		if( m_achievements[ achicritentry ]->cur_value != new_val && m_achievements[ achicritentry ]->completed_at_stamp == 0 )
			SendAchievmentStatus( (*itr)->ID, 1, TimeToGametime( UNIXTIME ) );
		//if we got here then we could update our status
		m_achievements[ achicritentry ]->cur_value = new_val;
    }

}

void Player::SendAchievmentEarned( uint32 archiId, uint32 at_stamp )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
    WorldPacket data( SMSG_ACHIEVEMENT_EARNED, 30);
	data << GetNewGUID();      
    data << uint32( archiId );
	if( at_stamp != 0 )
		data << uint32( at_stamp ); //seems to be something that increases in time. Also seems to a large enough value for time
	else 
		data << uint32( TimeToGametime( UNIXTIME ) );
	data << uint32(0);
	GetSession()->SendPacket(&data);
}

//wtf does this do ? How can i check the effect of this anyway ? Made this before SMSG_ACHIEVEMENT_EARNED :P
void Player::SendAchievmentStatus( uint32 criteriaid, uint32 new_value, uint32 at_stamp )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	/*
	noob warlock
	E2 14 00 00 - some index ? does not seem to be criteria id though
	01 - is this related to the indexes ? Seems to be 1 all the time
	2B - some index ?
	0F 82 43 97 01 - packed guid
	00 00 00 00 
	B4 82 94 08 
	00 00 00 00 
	00 00 00 00

	E2 14 00 00 01 2B 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	E2 14 00 00 01 53 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	E3 14 00 00 01 BB 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	E4 14 00 00 01 15 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	E5 14 00 00 01 15 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	E8 14 00 00 01 18 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	E6 14 00 00 01 16 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	E7 14 00 00 01 18 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	EA 14 00 00 01 2A 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	EA 14 00 00 01 52 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	EA 14 00 00 01 55 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	EA 14 00 00 01 57 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	EA 14 00 00 01 5E 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	EA 14 00 00 01 62 0F 82 43 97 01 00 00 00 00 B4 82 94 08 00 00 00 00 00 00 00 00
	*/
    WorldPacket data( SMSG_CRITERIA_UPDATE, 30);
    data << uint32(criteriaid);
	data << uint8(1);
	data << uint8(1); //this is some ID or something maybe merge with previous value ? Maybe it is value for criteria ?
	data << GetNewGUID();      
	data << uint32(0);
	if( at_stamp )
		data << uint32( TimeToGametime( at_stamp ) ); // -sometimes it is durations
	else
		data << uint32( TimeToGametime( UNIXTIME ) ); // -sometimes it is durations
	data << uint32(0); //duration
	data << uint32(0); //duration left
	GetSession()->SendPacket(&data);
}
/*
//send completed criterias to client
void Player::SendAllAchievementStatus()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	std::map<uint32,AchievementVal*>::iterator itr;
	for(itr=m_achievements.begin();itr!=m_achievements.end();itr++)
	{
//		uint32 critentry = itr->first;
//		AchievementCriteriaEntry *criteria = dbcAchievementCriteriaStore.LookupEntry( critentry );
//		if( !critentry ) continue; //wtf ?
//		if( criteria->requiredAchievementRelatedCount > itr->second )
		SendAchievmentStatus( itr->first, itr->second->cur_value, itr->second->completed_at_stamp );
	}
}


void Player::SendAllAchievementEarned()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	std::map<uint32,AchievementVal*>::iterator itr;
	for(itr=m_achievements.begin();itr!=m_achievements.end();itr++)
	{
		uint32 critentry = itr->first;
		AchievementCriteriaEntry *criteria = dbcAchievementCriteriaStore.LookupEntry( critentry );
		if( !criteria ) 
			continue; //wtf ?
		if( criteria->raw.requiredAchievementRelatedCount <= itr->second->cur_value )
			SendAchievmentEarned( criteria->referredAchievement );
	}
}*/

//this packet might get huge in time. Might reach over 1.2 MByte !
void Player::SendAllAchievementData()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(SMSG_ALL_ACHIEVEMENT_DATA, m_achievements.size() * 3 * 4 + 4);
	uint32 found_finished=0;

	//generate block of finished acheivemnts
	std::map<uint32,AchievementVal*>::iterator itr;
	for(itr=m_achievements.begin();itr!=m_achievements.end();itr++)
	{
		uint32 critentry = itr->first;
		AchievementCriteriaEntry *criteria = dbcAchievementCriteriaStore.LookupEntry( critentry );
		if( !criteria ) 
			continue; //wtf ?
		if( itr->second->completed_at_stamp != 0 && ( itr->second->cur_value & ACHIVEMENTS_EVIL_PENDING_STATUS_FLAG )==0)
		{
			found_finished++;
			data << uint32( criteria->referredAchievement );
			data << uint32( TimeToGametime( itr->second->completed_at_stamp ) ); // -sometimes it is durations
		}
	}
	data << int32(-1);  //terminator like a null terminated string
	for(itr=m_achievements.begin();itr!=m_achievements.end();itr++)
	{
		uint32 critentry = itr->first;
		AchievementCriteriaEntry *criteria = dbcAchievementCriteriaStore.LookupEntry( critentry );
		if( !criteria ) 
			continue; //wtf ?
		if( itr->second->completed_at_stamp == 0 || ( itr->second->cur_value & ACHIVEMENTS_EVIL_PENDING_STATUS_FLAG )!=0 )
		{
			found_finished++;
			//now the block for those : SMSG_CRITERIA_UPDATE
			//sometimes this is duration left
			data << uint32( criteria->ID );
//			data << uint8( 1 );	//this is bitmask for the size of the value. Like packed GUID
//			data << uint8( 1 ); //probably not since it does not fit into this size. Also seems to change from time to time
			data.appendPackGUID( itr->second->cur_value & ~ACHIVEMENTS_EVIL_PENDING_STATUS_FLAG );
			data << GetNewGUID();
			data << uint32( 0 ); //no idea. was always 0
			data << uint32( TimeToGametime( itr->second->completed_at_stamp ) ); //seems to be something that increases in time. Also seems to a large enough value for time
			data << uint32(0); //duration
			data << uint32(0); //duration left
		}
	}
	data << int32(-1);

	if( found_finished )
		GetSession()->SendPacket(&data);		
}

void Player::GiveAchievementReward(AchievementEntry const* entry)
{
	if( entry == NULL )
	{
		return;
	}
	struct AchievementReward
	{
		uint32 type;   //! type(s) of reward(s), ACHIEVEMENT_REWARDTYPE_NONE | ACHIEVEMENT_REWARDTYPE_ITEM | ACHIEVEMENT_REWARDTYPE_TITLE | ACHIEVEMENT_REWARDTYPE_SPELL
		uint32 itemId; //! itemId of item reward
		uint32 rankId; //! rankId of title reward
		uint32 spellId; //! spellId of spell reward
	};
	enum ACHIEVEMENT_REWARDTYPES
	{
		ACHIEVEMENT_REWARDTYPE_NONE		= 0,
		ACHIEVEMENT_REWARDTYPE_TITLE	= 1, 
		ACHIEVEMENT_REWARDTYPE_ITEM		= 2, 
		ACHIEVEMENT_REWARDTYPE_SPELL	= 4, 
	};
	AchievementReward r;
	r.type = ACHIEVEMENT_REWARDTYPE_NONE;
	r.itemId = 0;
	r.rankId = 0;
	r.spellId = 0;

	if( strlen(entry->rewardName) > 0 )
	{
		switch(entry->unknown2)
		{
			case 0x0000000b: // Title Reward: The Flawless Victor
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_FLAWLESS_VICTOR;
				break;
			case 0x000000b6: // Title Reward: Champion of the Frozen Wastes
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_CHAMPION_OF_THE_FROZEN_WASTES;
				break;
			case 0x00000229: // Title Reward: Guardian of Cenarius
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_GUARDIAN_OF_CENARIUS;
				break;
			case 0x00000244: // Title Reward: Salty
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_SALTY;
				break;
			case 1672: // Title: Of the Ashen Verdict
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_ASHEN_VERDICT;
				break;
			case 1522: // Reward: Little Fawn's Salt Lick
				r.type = ACHIEVEMENT_REWARDTYPE_ITEM;
				r.itemId = 44841;
				break;
/*			case 0x000005f2: // Reward: Reeking Pet Carrier
				r.type = ACHIEVEMENT_REWARDTYPE_ITEM;
				r.itemId = 40653;
				break;*/
			case 0x0000066c: // Reward: Title & Loremaster's Colors
				r.type = ACHIEVEMENT_REWARDTYPE_ITEM | ACHIEVEMENT_REWARDTYPE_TITLE;
				r.itemId = 43300;
				r.rankId = PVPTITLE_LOREMASTER;
				break;
			case 3936: // Reward: Pilgrim Title & Plump Turkey Pte
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL | ACHIEVEMENT_REWARDTYPE_TITLE;
				r.spellId = 61773;
				r.rankId = PVPTITLE_THE_PILGRIM;
				break;
			case 0x000006a4: // Title Reward: The Magic Seeker
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_MAGIC_SEEKER;
				break;
			case 0x000006a7: // Reward: Black War Bear [Horde]
				// spellId 60018 or 60019 ?
				r.type = ACHIEVEMENT_REWARDTYPE_ITEM;
				r.itemId = 44224;
				break;
			case 0x000006a8: // Reward: Black War Bear [Alliance]
				// spellId 60018 or 60019 ?
				r.type = ACHIEVEMENT_REWARDTYPE_ITEM;
				r.itemId = 44223;
				break;
			case 0x00000749: // Reward: The Schools of Arcane Magic - Mastery
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 59983;
				break;
			case 4007: // Reward: Perky Pug
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 70613;
				break;
			case 4156: // Reward: Icebound Frostbrood Vanquisher
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 72807;
				break;
			case 0x0000076a: // Title Reward: Conqueror of Naxxramas
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_CONQUEROR_OF_NAXXRAMAS;
				break;
			case 4148: // Title: Bane of the Fallen King
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_BANE_OF_FALLEN_KING;
				break;
			case 4179: // Title: The Kingslayer
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_KINGSLAYER;
				break;
			case 0x000007fc: // Reward: Black Proto-Drake
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 59976;
				break;
			case 0x00000858: // Title Reward: Elder
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_ELDER;
				break;
			case 0x0000085b: // Title Reward: The Argent Champion
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_ARGENT_CHAMPION;
				break;
			case 2143: // Title Reward: Conqueror of Ulduar
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_CONQUEROR_OF_ULDUAR;
				break;
			case 2292: // Title Reward: Champion of Ulduar
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_CHAMPION_OF_ULDUAR;
				break;
/*			case 0x0000085f: // Title Reward: The Immortal
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_IMMORTAL;
				break; 
			case 0x000008f4: // Title Reward: The Undying
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_UNDYING;
				break; */
			case 0x00000975: // Title: Bloodsail Admiral
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_BLOODSAIL_ADMIRAL;
				break;
			case 0x000009d3: // Title Reward: Brewmaster
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_BREWMASTER;
				break;
			case 0x000009db: // Title Reward: Matron/Patron
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = (getGender()==1) ? /* Matron */ PVPTITLE_MATRON : /* Patron */ PVPTITLE_PATRON;
				break;
			case 0x00000a03: // Title Reward: Conqueror
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_CONQUEROR;
				break;
			case 0x00000ab1: // Title Reward: The Diplomat
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_DIPLOMAT;
				break;
			case 0x00000ac7: // Title Reward: The Explorer
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_EXPLORER;
				break;
			case 0x00000b6c: // Title Reward: Justicar
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_JUSTICAR;
				break;
			case 0x00000b9e: // Title Reward: Flame Warden
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_FLAME_WARDEN;
				break;
			case 0x00000b9f: // Title Reward: Flame Keeper
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_FLAME_KEEPER;
				break;
			case 2821: // Title: the Light of Dawn
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_LIGHT_OF_DAWN;
				break;
			case 2938: // Title Reward: The Insane
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_INSANE;
				break;
			case 0x00000bb1: // Reward: Titanium Seal of Dalaran
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 60650;
				break;
			case 2328: // Reward: Blue Dragonhawk Mount
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 61996;
				break;
			case 3203: // Reward: Bloodbathed Frostbrood Vanquisher
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 72808;
				break;
			case 0x00000be0: // Reward: Tabard of the Achiever
				r.type = ACHIEVEMENT_REWARDTYPE_ITEM;
				r.itemId = 40643;
				break;
			case 3387: // Reward: Tabard of Conquest
				r.type = ACHIEVEMENT_REWARDTYPE_ITEM;
				r.itemId = GetTeam() ? 49054 : 49052;
				break;
			case 0x00000c14: // Title Reward: Merrymaker
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_MERRYMAKER;
				break;
			case 0x00000c78: // Title Reward: The Love Fool
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_LOVE_FOOL;
				break;
			case 3795: // Title Reward: of Silvermoon
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_OF_SILVERMOON;
				break;
			case 3796: // Title Reward: of the Exodar
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_OF_THE_EXODAR;
				break;
			case 3797: // Title Reward: of Ironforge
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_OF_IRONFORGE;
				break;
			case 3798: // Title Reward: of the Undercity
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_OF_THE_UNDERCITY;
				break;
			case 3799: // Title Reward: of Gnomeregan
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_OF_GNOMEREGAN;
				break;
			case 3800: // Title Reward: of Stormwind
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_OF_STORMWIND;
				break;
			case 3801: // Title Reward: of Darnassus
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_OF_DARNASSUS;
				break;
			case 3802: // Title Reward: of Orgrimmar
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_OF_ORGRIMMAR;
				break;
			case 3803: // Title Reward: of Orgrimmar
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_OF_THUNDERBLUFF;
				break;
			case 3804: // Title Reward: of Sen'jin
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_OF_SENJIN;
				break;
			case 3805: // Title Reward: The Grand Crusader
			case 3806: // Title Reward: Crusader. Unlocks Crusader dailies at the Argent Tournament.
			case 3807: // Title Reward: Crusader. Unlocks Crusader dailies at the Argent Tournament.
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_GRAND_CRUSADER;
				break;
			case 3848: // Title Reward: Death's Demise
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_DEATHS_DEMISE;
				break;
			case 3869: // Title Reward: The Celestial Defender
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_CELESTIAL_DEFENDER;
				break;
			case 3049: // Title: the Patient
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_PATIENT;
				break;
			case 3202: // Title Reward: the Noble
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_NOBLE;
				break;
			case 0x00000cb4: // Title Reward: Of the Nightfall [Normal] Title Reward: Twilight Vanquisher [Heroic]
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = (entry->ID == 2051) ? /* Normal */ PVPTITLE_OF_THE_NIGHTFALL : /* Heroic ID==2054 */ PVPTITLE_TWILIGHT_VANQUISHER;
				break;
			case 0x00000cec: // Title Reward: Obsidian Slayer
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_OBSIDIAN_SLAYER;
				break;
			case 0x00000d2c: // Title Reward: Battlemaster
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_BATTLEMASTER;
				break;
			case 0x00000d2d: // Title Reward: Battlemaster
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_BATTLEMASTER;
				break;
			case 0x00000d2e: // Title Reward: Ambassador
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_AMBASSADOR;
				break;
			case 0x00000d2f: // Title Reward: Ambassador
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_AMBASSADOR;
				break;
			case 0x00000d56: // Title Reward: The Seeker
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_SEEKER;
				break;
			case 0x00000d74: // Reward: Albino Drake
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 60025;
				break;
			case 0x00000d7d: // Title Reward: Of the Horde or Of the Alliance
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = (GetTeam()==1) ? /* Horde */ PVPTITLE_OF_THE_HORDE : /* Alliance */ PVPTITLE_OF_THE_ALLIANCE;
				break;
			case 0x00000da5: // Reward: Tabard of the Explorer
				r.type = ACHIEVEMENT_REWARDTYPE_ITEM;
				r.itemId = 43348;
				break;
			case 0x00000da6: // Reward: Red Proto-Drake
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 59961;
				break;
			case 3876: // Reward: Rusted Proto-Drake 
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 63963;
				break;
			case 3877: // Reward: Ironbound Proto-Drake 
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 63956;
				break;
			case 0x00000da7: // Title: Jenkins
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_JENKINS;
				break;
			case 0x00000dab: // Reward: Plagued Proto-Drake
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 60021;
				break;
			case 0x00000dac: // Reward: Violet Proto-Drake
				r.type = ACHIEVEMENT_REWARDTYPE_SPELL;
				r.spellId = 60024;
				break;
			case 0x00000dba: // Title Reward: The Hallowed
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_HALLOWED;
				break;
			case 0x00000e0b: // Reward: Tabard of Brute Force
				r.type = ACHIEVEMENT_REWARDTYPE_ITEM;
				r.itemId = 43349;
			case 0x00000e10: // Title Reward: Arena Master
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_ARENA_MASTER;
				break;
			case 0x00000e12: // Title Reward: The Exalted
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_THE_EXALTED;
				break;
			case 0x00000e5e: // Title Reward: Chef
				r.type = ACHIEVEMENT_REWARDTYPE_TITLE;
				r.rankId = PVPTITLE_CHEF;
				break;
			default:
				break;
		}
		if( r.type & ACHIEVEMENT_REWARDTYPE_TITLE )
		{
			SetKnownTitle(static_cast< RankTitles >(r.rankId), true);
//			SetChosenTitle(0 );
		}
		if( r.type & ACHIEVEMENT_REWARDTYPE_ITEM )
		{
			// How does this work? Add item directly to inventory, or send through mail?
			ItemPrototype* it = ItemPrototypeStorage.LookupEntry(r.itemId);
			if( it )
			{
				Item *item;
				item = objmgr.CreateItem(r.itemId, this);
				if( item == NULL )
				{
					// this is bad - item not found in db or unable to be created for some reason
					GetSession()->SendNotification("Unable to create item with id %lu!", r.itemId);
					return;
				}
				item->SetStackCount(  1);
				if( it->Bonding==ITEM_BIND_ON_PICKUP )
				{
					if( it->Flags & ITEM_FLAG_ACCOUNTBOUND )
					{
						// any "accountbound" items for achievement rewards?  maybe later...
						item->AccountBind();
					}
					else
					{
						item->SoulBind();
					}
				}

				if( !GetItemInterface()->AddItemToFreeSlot(&item) )
				{
					// this is bad. inventory full. maybe we should mail it instead?
					GetSession()->SendNotification("No free slots were found in your inventory!");
					if( item )
						item->DeleteMe();
					return;
				}
			}
		}
		if( r.type & ACHIEVEMENT_REWARDTYPE_SPELL )
		{
			addSpell(r.spellId);
		}
	}
}

//	 0x3F = 0x01 | 0x02 | 0x04 | 0x08 | 0x10 | 0x20 for 80 level
//			minor|Major |minor |Major |minor |Major
static const uint8 glyphMask[PLAYER_LEVEL_CAP_BLIZZLIKE+1] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //lvl 0-14, no glyphs
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, //lvl 15-29, 1 Minor 1 Major
	11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, //lvl 30-49, 1 Minor 2 Major
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, //lvl 50-69, 2 Minor 2 Major
	31, 31, 31, 31, 31, 31, 31, 31, 31, 31, //lvl 70-79, 3 Minor 2 Major
	63 //lvl 80, 3 Minor 3 Major
};

void Player::UpdateGlyphsAvail()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//enable glyphs for player
	uint8	level = getLevel();
/*	uint8	enable_steps[6]={0,15,30,50,70,80};
	uint32	enable_mask = 0;
	for(uint32 ind=0;ind<6;ind++)
		if( level >= enable_steps[ ind ] )
			enable_mask |= (1 << ind);
	SetUInt32Value( PLAYER_GLYPHS_ENABLED, enable_mask );
	*/
	if( level > PLAYER_LEVEL_CAP_BLIZZLIKE )
		level = PLAYER_LEVEL_CAP_BLIZZLIKE;
	SetUInt32Value( PLAYER_GLYPHS_ENABLED, glyphMask[level] );
}

uint8 Player::GetFullRuneCount(uint8 type)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint8 ret=0;
	for(int j=0;j<TOTAL_USED_RUNES;j++)
		if( m_rune_types[j] == type && m_runes[j] == MAX_RUNE_VALUE )
			ret++;
	return ret;
}

uint8 Player::TakeFullRuneCount(uint8 type, uint8 count)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( count == 0 )
	{ 
		return 0;
	}
	uint8 tcount = count;
	for(int j=0;j<TOTAL_USED_RUNES;j++)
		if( m_rune_types[j] == type && m_runes[j] == MAX_RUNE_VALUE )
		{
			m_runes[j] = 0; //consume rune
			UpdateRuneIcon( j );
			tcount--;
			if( tcount == 0 )
			{ 
				return 0;
			}
		}
	return tcount;
}


void Player::UpdateRuneIcon(uint8 rune_index)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	/*
	!this is not reuired anymore since it is handled in spell go Packet
	if( rune_index >= TOTAL_USED_RUNES )
		return; //wtf ?
	if( m_runes[ rune_index ] == MAX_RUNE_VALUE ) 
		ConvertRuneIcon( rune_index, m_rune_types[ rune_index ] );
	else if( m_runes[ rune_index ] == 0 ) 
		ConvertRuneIcon( rune_index, RUNE_NOTIMPLEMENTED );
	*/
}

void Player::ConvertRuneIcon(uint8 index,uint8 dst_rune_type)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( index >= TOTAL_USED_RUNES )
		return; //wtf ?
	WorldPacket data(SMSG_CONVERT_RUNE, 2);
	data << (uint8)index;
	data << (uint8)dst_rune_type;
	GetSession()->SendPacket(&data);
};

void Player::UpdateRuneCooldowns()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(SMSG_RESYNC_RUNES, TOTAL_USED_RUNES * 2);
	for(uint32 i = 0; i < TOTAL_USED_RUNES; ++i)
	{
		data << uint8( m_runes[ i ] );
		//we do not store partial values. Feel free to compute it from rune value :P
		if( m_runes[ i ] == MAX_RUNE_VALUE )
			data << uint8( 0 );
		else 
			data << uint8( 255 );     // passed cooldown time (0-255)
	}
	GetSession()->SendPacket(&data);
}

void Player::ClearRuneCooldown(uint8 index)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(SMSG_ADD_RUNE_POWER, 4);
	data << uint32(1 << index);                             // mask (0x00-0x3F probably)
	GetSession()->SendPacket(&data);
}

void Player::SetFFAPvPFlag()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
	SetFlag(PLAYER_FLAGS, PLAYER_FLAG_FREE_FOR_ALL_PVP);
	//while in times we will have this removed
	SetFlag(PLAYER_FLAGS, PLAYER_FLAG_PVP_TOGGLE);

	//set pet or summon as pvper
	if( GetSummon() && !GetSummon()->IsFFAPvPFlagged()  )
		GetSummon()->SetFFAPvPFlag();

	//set totem pvp flags
	for(uint32 i=0;i<4;i++)
		if( m_TotemSlots[i] &&  m_TotemSlots[i]->IsFFAPvPFlagged() == false )
			m_TotemSlots[i]->SetFFAPvPFlag();
}

void Player::RemoveFFAPvPFlag()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
   if(!IsFFAPvPFlagged()) 
   { 
   	return;
   }

	if( GetSummon() )
		GetSummon()->RemoveFFAPvPFlag();

   RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
   RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_FREE_FOR_ALL_PVP);
}

void Player::SetPvPFlag()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
/*	if( !IsPvPFlagged() )
	{
		AreaTable* at = dbcArea.LookupEntry( GetAreaID() );
		if( at && at->AreaFlags & AREA_SANCTUARY )
			return; //no pvp in sanctuary zones
	} */

	// reset the timer as well..
	StopPvPTimer(); //stop will make us not wait for the cooldown anymore !
	//while in times we will have this removed
	SetFlag(PLAYER_FLAGS, PLAYER_FLAG_PVP_TOGGLE);
	//make sure to remove all effects that were not ment to be used in PVPs
	RemoveAurasByInterruptFlag( AURA_INTERRUPT_CUSTOM_ON_PVP );

//		SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP);
	SetByteFlag(UNIT_FIELD_BYTES_2,1,UNIT_BYTE2_FLAG_PVP);

	//set pet or summon as pvper
	if( GetSummon() && !GetSummon()->IsPvPFlagged() )
		GetSummon()->SetPvPFlag();

	//set totem pvp flags
	for(uint32 i=0;i<4;i++)
		if( m_TotemSlots[i] && m_TotemSlots[i]->IsPvPFlagged() == false )
			m_TotemSlots[i]->SetPvPFlag();

}

void Player::RemovePvPFlag()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
//	if( !IsPvPFlagged() )
//		return;
	//battlegrounds, do not let people disable PVP
	if( GetMapMgr() && DISABLE_PVP_TOGGLE_MAP( GetMapMgr()->GetMapInfo() ) )
	{
		StopPvPTimer();
		SetPvPFlag();
		return;
	}

	if( GetSummon() )
		GetSummon()->RemovePvPFlag();

	StopPvPTimer();	//will also remove countdown flag
//		RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP);
	RemoveFlag(PLAYER_FLAGS, PLAYER_FLAG_PVP_TOGGLE ); //show client side that we are pvp disabled
	RemoveByteFlag(UNIT_FIELD_BYTES_2,1,UNIT_BYTE2_FLAG_PVP);
}

void Player::fill_talent_info_in_packet( WorldPacket &data )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	data << uint32( GetUInt32Value(PLAYER_CHARACTER_POINTS1) ); // Unspent talents
	data << uint8(m_talentSpecsCount);
	data << uint8(m_talentActiveSpec); // unk
	for(uint8 s = 0; s < m_talentSpecsCount; s++)
	{
		PlayerSpec spec = m_specs[s];
		// Send Talents
		data << uint8(spec.talents.size());
		std::map<uint32, uint8>::iterator itr;
		for(itr = spec.talents.begin(); itr != spec.talents.end(); itr++)
		{
			data << uint32(itr->first);	// TalentId
			data << uint8(itr->second);	// TalentRank
		}
//		if( self )
		{
			// Send Glyph info
			data << uint8(GLYPHS_COUNT);
			for(uint8 i = 0; i < GLYPHS_COUNT; i++)
				data << uint16(spec.glyphs[i]);
		}
//		else
//			data << uint8( 0 );
	}
}

void Player::smsg_TalentsInfo(bool update, uint32 newTalentId, uint8 newTalentRank)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	WorldPacket data(SMSG_TALENTS_INFO, 1000);
	update = false;
	data << uint8(update);
	if(update)	// send just the update
	{
		uint8 count = 1;
		data << uint32(GetUInt32Value(PLAYER_CHARACTER_POINTS1)); // Unspent talents
		data << uint8(count);
		for(uint8 i = 0; i < count; i++)
		{
			data << uint32(newTalentId); // unk	talentid?
			data << uint8(newTalentRank); // unk	rank?
		}
	} 
	else	// initialize sending all info
	{
		uint8 talent_max_rank = 0;
		fill_talent_info_in_packet( data );
	}
	GetSession()->SendPacket(&data);
}

//we already added spell in our spellbook
void Player::Event_Learn_Talent( uint32 newTalentId, uint8 newTalentRank, uint8 point_consume )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	m_specs[ m_talentActiveSpec ].talents[ newTalentId ] = newTalentRank;
	SetUInt32Value( PLAYER_CHARACTER_POINTS1, GetUInt32Value(PLAYER_CHARACTER_POINTS1) - point_consume );
	smsg_TalentsInfo( true, newTalentId, newTalentRank );
}

 //remove old talents active on us and apply new ones
void Player::Switch_Talent_Spec()
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	//Dismiss any pets
	if(GetSummon())
	{
		if(GetSummon()->GetUInt32Value(UNIT_CREATED_BY_SPELL) > 0)
			GetSummon()->Dismiss();				// warlock summon -> dismiss
		else
			GetSummon()->Remove(false, true);	// hunter pet -> just remove for later re-call
		SetSummon( NULL );
	}
	//!!! Need to make = add support for multi speccing pets also

	//just so we do not do useless stuff we check old and new spec and not make changes regarding same talents
	uint32 old_spec_id = m_talentActiveSpec;
	uint32 new_spec_id = ( m_talentActiveSpec + 1 ) % m_talentSpecsCount;//same as : 1-m_talentActiveSpec

	//now set active spec 
	m_talentActiveSpec = new_spec_id;	// so removespell would not corrupt the iteration

	//remove old spells -> this will also remove talents and their auras
	SpellSet::iterator sp_itr,t_sp_itr;
	for( sp_itr = m_specs[ old_spec_id ].SpecSpecificSpells.begin();sp_itr != m_specs[ old_spec_id ].SpecSpecificSpells.end(); sp_itr++ )
	{
		//check for common data
		t_sp_itr = m_specs[ new_spec_id ].SpecSpecificSpells.find( *sp_itr );
		if( t_sp_itr != m_specs[ new_spec_id ].SpecSpecificSpells.end() )
			continue;

		removeSpell( *sp_itr, false, false, 0 );
	}

	//remove old glyphs
	for(int i=0;i<GLYPHS_COUNT;i++)
	{
		uint32 glyph_id = m_specs[ old_spec_id ].glyphs[ i ];
		if( !glyph_id )
			continue;
		GlyphPropertiesEntry *glyphprops = dbcGlyphPropertiesStore.LookupEntry( glyph_id );
		if( glyphprops == NULL )
			continue;
		SetUInt32Value( PLAYER_FIELD_GLYPHS_1 + i, 0 );

		//remove the effect
		RemoveAura( glyphprops->SpellId );
	}

	//calculate new TP count
	//first count the number of points invested in the new tree
	std::map<uint32, uint8>::iterator treeitr;
	int32 points_used_up=0;
	for( treeitr = m_specs[ new_spec_id ].talents.begin();treeitr != m_specs[ new_spec_id ].talents.end();treeitr++)
		points_used_up += treeitr->second + 1;
	uint32 new_TP_count = max(0,int32( GetMaxTP() - points_used_up));
	SetUInt32Value( PLAYER_CHARACTER_POINTS1, new_TP_count );

	//add new spells and talents. Passive spells are casted as they are considered auras
	for( sp_itr = m_specs[ new_spec_id ].SpecSpecificSpells.begin();sp_itr != m_specs[ new_spec_id ].SpecSpecificSpells.end(); sp_itr++ )
	{
		//check for common data
		t_sp_itr = m_specs[ old_spec_id ].SpecSpecificSpells.find( *sp_itr );
		if( t_sp_itr != m_specs[ old_spec_id ].SpecSpecificSpells.end() )
			continue;

		//add spell to our spellbook
		addSpell( *sp_itr, true );

		//if this is a talent then cast the effect of it
		SpellEntry *spellInfo = dbcSpell.LookupEntry( *sp_itr ); 
		if( spellInfo == NULL 
			|| ( spellInfo->Attributes & ATTRIBUTES_PASSIVE ) == 0 
			|| ( spellInfo->c_is_flags & SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST ) //like health pct dependent will get autocast on health change event
			)
			continue;
		Spell *spell = SpellPool.PooledNew();
		spell->Init( this, spellInfo ,true, NULL );
		SpellCastTargets targets( GetGUID() );
		spell->prepare(&targets);
	}

	//apply new glyphs 
	for(int i=0;i<GLYPHS_COUNT;i++)
	{
		uint32 glyph_id = m_specs[ new_spec_id ].glyphs[ i ];
		if( !glyph_id )
			continue;
		GlyphPropertiesEntry *glyphprops = dbcGlyphPropertiesStore.LookupEntry( glyph_id );
		if( glyphprops == NULL )
			continue;
		SetUInt32Value( PLAYER_FIELD_GLYPHS_1 + i, glyph_id );
		
		//also apply the glyph effect to the player
		SpellEntry *spellInfo = dbcSpell.LookupEntry( glyphprops->SpellId ); //we already modified this spell on server loading so it must exist
		Spell *spell = SpellPool.PooledNew();
		spell->Init( this, spellInfo ,true, NULL );
		SpellCastTargets targets( GetGUID() );
		spell->prepare(&targets);
	}

	//resend talent info
	smsg_TalentsInfo( false, 0, 0 );
}

void Player::GroupUninvite(Player *targetPlayer, PlayerInfo *targetInfo)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if ( targetPlayer == NULL && targetInfo == NULL )
	{
		GetSession()->SendPartyCommandResult( this, 0, "", ERR_PARTY_CANNOT_FIND);
		return;
	}

	if ( !InGroup() || targetInfo->m_Group != GetGroup() )
	{
		GetSession()->SendPartyCommandResult( this, 0, "", ERR_PARTY_IS_NOT_IN_YOUR_PARTY);
		return;
	}

	if ( !IsGroupLeader() || ( targetInfo->m_loggedInPlayer && targetInfo->m_loggedInPlayer->m_bg ) )	// bg group
	{
		if( this != targetPlayer)
		{
			GetSession()->SendPartyCommandResult( this, 0, "", ERR_PARTY_YOU_ARE_NOT_LEADER);
			return;
		}
	}

	if(m_bg)
	{ 
		return;
	}

	Group *group = GetGroup();

	if(group)
		group->RemovePlayer(targetInfo);
}


void Player::EventReduceDrunk(bool full)
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint16 drunk = GetUInt32Value(PLAYER_BYTES_3) & 0xFFFF;

	if(full) 
		drunk = 0;
	else if( drunk >= 256 )
		drunk -= 256;
	else
		drunk = 0;

	SetDrunkValue( drunk );
	if( drunk == 0 ) 
		sEventMgr.RemoveEvents(this, EVENT_PLAYER_REDUCEDRUNK);
}

DrunkenState Player::GetDrunkenstateByValue( uint16 value )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( value >= 23000 )
		return DRUNKEN_SMASHED;
	if( value >= 12800 )
		return DRUNKEN_DRUNK;
	if( value & 0xFFFE )
		return DRUNKEN_TIPSY;
	return DRUNKEN_SOBER;
}

void Player::SetDrunkValue( uint16 newDrunkenValue, uint32 itemId )
{
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	uint32 m_drunk = GetDrunkValue();
	uint32 oldDrunkenState = Player::GetDrunkenstateByValue( m_drunk );

	m_drunk = newDrunkenValue;
	SetUInt32Value( PLAYER_BYTES_3, ( GetUInt32Value( PLAYER_BYTES_3 ) & 0xFFFF0001 ) | ( m_drunk & 0xFFFE ) );

	uint32 newDrunkenState = Player::GetDrunkenstateByValue( m_drunk );

	if( newDrunkenState == oldDrunkenState )
		return;

	// special drunk invisibility detection
	if( newDrunkenState >= DRUNKEN_DRUNK )
		m_invisDetect[ INVIS_FLAG_UNKNOWN6 ] = 100;
	else
		m_invisDetect[ INVIS_FLAG_UNKNOWN6 ] = 0;

	UpdateVisibility();

	WorldPacket data( SMSG_CROSSED_INEBRIATION_THRESHOLD, (8+4+4) );
	data << GetGUID();
	data << uint32( newDrunkenState );
	data << uint32( itemId );
	SendMessageToSet( &data, true );
}

void Player::HandleSpellLoot( uint32 itemid )
{
	Loot loot;
	std::vector< __LootItem >::iterator itr;

	lootmgr.FillItemLoot( &loot, itemid );

	for( itr = loot.items.begin(); itr != loot.items.end(); ++itr )
	{
		uint32 looteditemid = itr->item.itemproto->ItemId;
		uint32 count = itr->iItemsCount;

		m_ItemInterface->AddItemById( looteditemid, count, 0 );
	}
}
/************************************************************************/
/* Talent Anti-Cheat                                                    */
/************************************************************************/

/*
	mage - arcane - 81			
	mage - fire - 41
	mage - frost - 61

	rogue - assassination - 182
	rogue - combat - 181
	rogue - subelty - 183

	warlock - afflication - 302
	warlock - demonology - 303
	warlock - destruction - 301

	warrior - arms - 161
	warrior - fury - 163
	warrior - protection - 164

	shaman - elemental - 261
	shaman - enchantment - 263
	shaman - restoration - 262

	paladin - holy - 382
	paladin - protection - 383
	paladin - retribution - 381

	priest - dicipline - 201
	priest - holy - 202
	priest - shadow - 203

	hunter - beast - 361
	hunter - marksmanship - 363
	hunter - survival - 362

	druid - balance - 283
	druid - feral combat - 281
	druid - restoration - 282
*/

static const uint32 TalentTreesPerClass[DRUID+1][3] =  {
	{ 0, 0, 0 },		// NONE
	{ 161, 163, 164 },	// WARRIOR
	{ 382, 383, 381 },	// PALADIN
	{ 361, 363, 362 },	// HUNTER
	{ 182, 181, 183 },	// ROGUE
	{ 201, 202, 203 },	// PRIEST
	{ 398, 399, 400 },	// DEATHKNIGHT
	{ 261, 263, 262 },	// SHAMAN
	{ 81, 41, 61 },		// MAGE
	{ 302, 303, 301 },	// WARLOCK
	{ 0, 0, 0 },		// NONE
	{ 283, 281, 282 },	// DRUID
};

void Player::LearnTalent(uint32 talent_id, uint32 requested_rank, bool isPreviewed )
{
	uint32 CurTalentPoints = GetUInt32Value(PLAYER_CHARACTER_POINTS1);

	int32 TP_needed;
	if( isPreviewed == false )
		TP_needed = 1;
	else 
		TP_needed = requested_rank + 1;

	if( (int32)CurTalentPoints < TP_needed )
	{ 
		sLog.outDebug("LearnTalent: Have not enough talentpoints to spend");
		return;
	}

	if (requested_rank > 4)
	{ 
		sLog.outDebug("LearnTalent: Requested rank is greater then 4");
		return;
	}

	TalentEntry * talentInfo = dbcTalent.LookupEntryForced( talent_id );
	if(!talentInfo)
	{
		sLog.outDebug("Could not find talent %u with rank %u in talent DBC \n",talent_id,requested_rank);
		return;
	}
  
	// Check if it requires another talent
	if (talentInfo->DependsOn > 0)
	{
		TalentEntry *depTalentInfo = NULL;
		depTalentInfo = dbcTalent.LookupEntryForced(talentInfo->DependsOn);
		if( depTalentInfo == NULL )
		{
			sLog.outDebug("Could not find talent dependency %u for talent %u \n",talentInfo->DependsOn,talent_id);
			return;
		}
		bool hasEnoughRank = false;
		for (int i = talentInfo->DependsOnRank; i < 5; i++)
		{
			if (depTalentInfo->RankID[i] != 0)
			{
				if (HasSpell(depTalentInfo->RankID[i]))
				{
					hasEnoughRank = true;
					break;
				}
			}
		}
		if (!hasEnoughRank)
		{
			sLog.outDebug("Talent does not have dependency, depends on rank %u and talent(not spell) %u with spell %u\n",talentInfo->DependsOnRank,talentInfo->DependsOn,depTalentInfo->RankID[0]);
			for (int i = talentInfo->DependsOnRank; i < 5; i++)
				if (depTalentInfo->RankID[i] != 0 )
					sLog.outDebug(" \t Need to have spell %u fro rank %u\n",depTalentInfo->RankID[i],i);
			return;
		}
	}

	// Find out how many points we have in this field
	uint32 spentPoints = 0;

	uint32 tTree = talentInfo->TalentTree;
	uint32 cl = getClass();
	int i;

	for(i = 0; i < 3; ++i)
		if(tTree == TalentTreesPerClass[cl][i])
			break;

	if(i == 3)
	{
		// cheater!
		SoftDisconnect();
		sLog.outDebug("LearnTalent: Talent is not for our class");
		return;
	}

	if (talentInfo->Row > 0)
	{
		for (uint32 i = 0; i < dbcTalent.GetNumRows(); i++)		  // Loop through all talents.
		{
			// Someday, someone needs to revamp
			TalentEntry *tmpTalent = dbcTalent.LookupRow(i);
			if (tmpTalent)								  // the way talents are tracked
			{
				if (tmpTalent->TalentTree == tTree)
				{
					for (int j = 0; j < 5; j++)
					{
						if (tmpTalent->RankID[j] != 0)
						{
							if (HasSpell(tmpTalent->RankID[j]))
							{
								spentPoints += j + 1;
							//	break;
							}
						}
						else 
							break;
					}
				}
			}
		}
	}

	uint32 spellid = talentInfo->RankID[requested_rank];
	if( spellid == 0 )
	{
		sLog.outDetail("Talent: %u Rank: %u = 0", talent_id, requested_rank);
	}
	else
	{
		if(spentPoints < (talentInfo->Row * 5))			 // Min points spent
		{
			sLog.outDebug("LearnTalent: Not enough points invested in tree");
			return;
		}

		if(requested_rank > 0)
		{
			if(talentInfo->RankID[requested_rank-1] && !HasSpell(talentInfo->RankID[requested_rank-1]) && !isPreviewed)
			{
				// cheater
				sLog.outDebug("LearnTalent: Missing required rank");
				return;
			}
		}
		for (uint32 i=requested_rank; i<5; ++i)
			if (talentInfo->RankID[i] != 0 && HasSpell(talentInfo->RankID[i]))
			{
				sLog.outDebug("LearnTalent: Has rank %u higher already higher or equal.Spell id %u",i,talentInfo->RankID[i]);
				return; // cheater
			}

		if( !HasSpell(spellid) )
		{
			addSpell(spellid);			
	
			SpellEntry *spellInfo = dbcSpell.LookupEntry( spellid );	 
			//make sure pets that get bonus from owner do not stack it up
			if( getClass() == HUNTER && GetSummon() )
				GetSummon()->RemoveAllAuras( spellInfo->NameHash,0 );
			
			if(requested_rank > 0 )
			{
				uint32 respellid = talentInfo->RankID[requested_rank-1];
				if(respellid)
				{
					removeSpell(respellid, false, false, 0);
					RemoveAllAuras(respellid,0);

					SpellEntry *spellInfo = dbcSpell.LookupEntry( respellid );	 
					if( getClass() == HUNTER && GetSummon() )
						GetSummon()->RemoveAllAuras( spellInfo->NameHash, 0 );
				}
			}

			if( spellInfo->RequiredShapeShift == 0 || ( (uint32)1 << (GetShapeShift()-1) & spellInfo->RequiredShapeShift ) != 0 )
			{
				if( (((spellInfo->Attributes & ATTRIBUTES_PASSIVE) 
						&& !( spellInfo->c_is_flags & SPELL_FLAG_IS_CONDITIONAL_PASSIVE_CAST )) //like health pct dependent will get autocast on health change event
					|| (spellInfo->Effect[0] == SPELL_EFFECT_LEARN_SPELL ||
							spellInfo->Effect[1] == SPELL_EFFECT_LEARN_SPELL ||
							spellInfo->Effect[2] == SPELL_EFFECT_LEARN_SPELL) )
					)
				{
					Spell*sp=SpellPool.PooledNew();
					sp->Init(this,spellInfo,true,NULL);
					SpellCastTargets tgt;
					tgt.m_unitTarget=GetGUID();
					sp->prepare(&tgt);
				}
				if( ((spellInfo->c_is_flags & (SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER)) != 0 && GetSummon() ) )
					EventSummonPetCastSpell( GetSummon(), spellInfo->Id );
			}

			Event_Learn_Talent( talent_id, requested_rank, TP_needed );
		}
	}
}

bool  Player::HasGlyphWithID(uint32 glyphID )
{
	for(int i=0;i<GLYPHS_COUNT;i++)
		if( m_specs[ m_talentActiveSpec ].glyphs[ i ] == glyphID )
			return true;
	return false;
}

//blizz is sending this every now and then
void Player::SendTimeSyncRequest()
{
	sStackWolrdPacket( data, SMSG_TIME_SYNC_REQ, 6);
	data << uint32(m_time_sync_send_counter);
	GetSession()->SendPacket( &data );

	m_time_sync_send_counter++;
}

ARCEMU_INLINE GameObject*  Player::GetSelectedGo()
{ 
	INSTRUMENT_TYPECAST_CHECK_PLAYER_OBJECT_TYPE
	if( m_GM_SelectedGO ) 
		return GetMapMgr()->GetGameObject( m_GM_SelectedGO );
	return NULL;
}

ARCEMU_INLINE Player * Player::GetTradeTarget()
{
	if(!IsInWorld()) 
		return 0;
	return m_mapMgr->GetPlayer( mTradeTarget );
}

void Player::SendItemPushResult( bool created, bool recieved, bool sendtoset, bool newitem, uint8 destbagslot, uint32 destslot, uint32 count, uint32 entry, uint32 suffix, uint32 randomprop, uint32 stack ){

    WorldPacket data( SMSG_ITEM_PUSH_RESULT, 8 + 4 + 4 + 4 + 1 + 4 + 4 + 4 + 4 + 4 + 4 );

    data << uint64( GetGUID() );

    if( recieved )
        data << uint32( 1 );
    else
        data << uint32( 0 );

    if( created )
        data << uint32( 1 );
    else
        data << uint32( 0 );

    data << uint32( 1 );
    data << uint8( destbagslot );

    if( newitem )
        data << uint32( destslot );
    else
        data << uint32( -1 );

    data << uint32( entry );
    data << uint32( suffix );
    data << uint32( randomprop );
    data << uint32( count );
    data << uint32( stack );

    if( sendtoset && InGroup() )
        GetGroup()->SendPacketToAll( &data );
    else
        m_session->SendPacket( &data );

}

uint32 Player::GetInitialFactionId()
{
	
	PlayerCreateInfo * pci = objmgr.GetPlayerCreateInfo(getRace(), getClass());
	if( pci )
		return pci->factiontemplate;
	else 
		return 35;
} 

void Player::SendTriggerMovie(uint32 movieId)
{
	sStackWolrdPacket(data, SMSG_TRIGGER_MOVIE, 6 );
    data << movieId;
	m_session->SendPacket( &data );
}

void Player::LFG_UpdateClientUI(uint8 updateType)
{
    bool queued = false;
    bool extrainfo = false;

    switch(updateType)
    {
    case LFG_UPDATETYPE_JOIN_PROPOSAL:
    case LFG_UPDATETYPE_ADDED_TO_QUEUE:
        queued = true;
        extrainfo = true;
        break;
    //case LFG_UPDATETYPE_CLEAR_LOCK_LIST: // TODO: Sometimes has extrainfo - Check ocurrences...
    case LFG_UPDATETYPE_PROPOSAL_BEGIN:
        extrainfo = true;
        break;
    }
	/*
	05 
	01 
	00 
	00 00
	01 
	E3 00 00 02 
	75 62 65 72 20 67 65 61 72 20 73 63 6F 72 65 21 00
	*/
	sStackWolrdPacket( data, SMSG_LFG_UPDATE_PLAYER, 2000 );
    data << uint8(updateType);                              // Lfg Update type
    data << uint8(extrainfo);                               // Extra info
    if (extrainfo)
    {
        data << uint8(queued);                              // Join the queue
        data << uint8(0);                                   // unk - Always 0
        data << uint8(0);                                   // unk - Always 0

		uint32 counter_pos,counter_val;
		counter_pos = data.GetSize();
		counter_val = 0;
        data << uint8( 0 );									//size holder
		CommitPointerListNode<LFG_store>	*itr;
		LFG_dungeons.BeginLoop();
        for( itr = LFG_dungeons.begin(); itr != LFG_dungeons.end(); itr = itr->Next() )
		{
			uint32 combined_val = ((uint32)itr->data->type << 24) | itr->data->map_id;
            data << uint32(combined_val);
			counter_val++;
		}
		LFG_dungeons.EndLoopAndCommit();
		data.WriteAtPos( (uint8)counter_val, counter_pos );

        data << LFG_comment;
    }
    m_session->SendPacket(&data);
}

void Player::LFG_PartyUpdateClientUI(uint8 updateType)
{
     bool join = false;
    bool extrainfo = false;
    bool queued = false;

    switch(updateType)
    {
    case LFG_UPDATETYPE_JOIN_PROPOSAL:
        extrainfo = true;
        break;
    case LFG_UPDATETYPE_ADDED_TO_QUEUE:
        extrainfo = true;
        join = true;
        queued = true;
        break;
    case LFG_UPDATETYPE_CLEAR_LOCK_LIST:
        // join = true;  // TODO: Sometimes queued and extrainfo - Check ocurrences...
        queued = true;
        break;
    case LFG_UPDATETYPE_PROPOSAL_BEGIN:
        extrainfo = true;
        join = true;
        break;
    }

	/*
	05 type
	01 extra info
	00 join 
	00 queue
	00 00 00 00 00 unk
	01 counter
	01 01 00 02 
	00 comment

	05 
	01 
	00 
	00 
	00 00 00 00 00 
	00 
	01 01 00 02 74 00
	*/
	sStackWolrdPacket( data, SMSG_LFG_UPDATE_PARTY, 2000 );
    data << uint8(updateType);                              // Lfg Update type
    data << uint8(extrainfo);                               // Extra info
    if (extrainfo)
    {
		data << uint8(join);                                // LFG Join
        data << uint8(queued);                              // Join the queue
        data << uint8(0);                                   // unk - Always 0
        data << uint8(0);                                   // unk - Always 0
        for (uint8 i = 0; i < 3; ++i)
            data << uint8(0);                               // unk - Always 0

		uint32 counter_pos,counter_val;
		counter_pos = data.GetSize();
		counter_val = 0;
        data << uint8( 0 );									//size holder
		CommitPointerListNode<LFG_store>	*itr;
		LFG_dungeons.BeginLoop();
        for( itr = LFG_dungeons.begin(); itr != LFG_dungeons.end(); itr = itr->Next() )
		{
			uint32 combined_val = ((uint32)itr->data->type << 24) | itr->data->map_id;
            data << uint32(combined_val);
			counter_val++;
		}
		LFG_dungeons.EndLoopAndCommit();
		data.WriteAtPos( (uint8)counter_val, counter_pos );

        data << LFG_comment;
    }
    m_session->SendPacket(&data);
}

void Player::LFG_JoinResponse(uint8 checkResult, uint8 checkValue)
{
    if (checkResult == LFG_JOIN_PARTY_NOT_MEET_REQS)        // Should never happen - its handled in Mgr
        return;
	sStackWolrdPacket( data, SMSG_LFG_JOIN_RESULT, 10 );
    data << uint32(checkResult);                            // Check Result
    data << uint32(checkValue);                             // Check Value
    m_session->SendPacket(&data);
}

bool Player::RB_IsLookingFor( uint32 map_id, uint32 type )
{
	CommitPointerListNode<LFG_store>	*itr;
	LFG_dungeons.BeginLoop();
    for( itr = LFG_dungeons.begin(); itr != LFG_dungeons.end(); itr = itr->Next() )
		if( itr->data->type == type && itr->data->map_id == map_id )
		{
			LFG_dungeons.EndLoopAndCommit();
			return true;
		}
	LFG_dungeons.EndLoopAndCommit();
	return false;
}

void Player::SendEquipmentSetList()
{
    uint32 count = 0;
	sStackWolrdPacket( data , SMSG_EQUIPMENT_SET_LIST, MAX_EQUIPMENT_SET_INDEX * EQUIPMENT_SLOT_END * 4 + MAX_EQUIPMENT_SET_INDEX * 100 );
	uint32 counter_pos,counter_val;
	counter_pos = data.GetSize();
	counter_val = 0;
    data << uint32(counter_val);  // count placeholder
	CommitPointerListNode<EquipmentSet>	*itr;
	m_EquipmentSets.BeginLoop();
    for(itr = m_EquipmentSets.begin(); itr != m_EquipmentSets.end(); itr = itr->Next() )
    {
        FastGUIDPack( data, itr->data->Guid );
        data << uint32(counter_val);
        data << itr->data->Name;
        data << itr->data->IconName;
        for(uint32 j = 0; j < EQUIPMENT_SLOT_END; ++j )
            FastGUIDPack( data, itr->data->ItemGUIDS[ j ] );
        ++counter_val;                                            
    }
	m_EquipmentSets.EndLoopAndCommit();
    data.WriteAtPos( (uint32)counter_val, counter_pos );
//	if( counter_val ) //do we need to send empty packet at all ? No spams kk
		GetSession()->SendPacket(&data);
}

void Player::DeleteEquipmentSet( uint64 GUID )
{
	CommitPointerListNode<EquipmentSet>	*itr;
	m_EquipmentSets.BeginLoop();
    for(itr = m_EquipmentSets.begin(); itr != m_EquipmentSets.end(); itr = itr->Next() )
		if( itr->data->Guid == GUID )
		{
			CharacterDatabase.Execute( "delete from character_equipmentsets where setguid='%u'",GET_LOWGUID_PART( itr->data->Guid ));
			m_EquipmentSets.SafeRemove( itr, 1 );
			break;
		}
	m_EquipmentSets.EndLoopAndCommit();
}

//!! need to check, if there is only 1 set then there is no need to save it cause he will not be able to swap it with anything else anyway
void Player::_SaveEquipmentSets(QueryBuffer * buf)
{
	//don't be stupid and try to trick your own code :P
	if( buf == NULL )
		return;

	std::stringstream ss;
	CommitPointerListNode<EquipmentSet>	*itr;
	m_EquipmentSets.BeginLoop();
    for(itr = m_EquipmentSets.begin(); itr != m_EquipmentSets.end(); itr = itr->Next() )
		if( itr->data->need_save == true )
	{
		ss.rdbuf()->str("");
		ss << "REPLACE INTO character_equipmentsets VALUES('"
			<< GetLowGUID() << "','"
			<< itr->data->Guid << "','"					//is this safe ?
			<< CharacterDatabase.EscapeString(itr->data->Name) << "','"
			<< CharacterDatabase.EscapeString(itr->data->IconName) << "',";
		for(uint32 i=0;i<EQUIPMENT_SLOT_END-1;i++)
			ss << ((uint32)GET_LOWGUID_PART( itr->data->ItemGUIDS[i] )) << ",";
		ss << ((uint32)GET_LOWGUID_PART( itr->data->ItemGUIDS[EQUIPMENT_SLOT_END-1] )) << ")";
		buf->AddQueryStr(ss.str());
	}
	m_EquipmentSets.EndLoopAndCommit();
}


void Player::_LoadEquipmentSets(QueryResult *result)
{
    if (!result)
        return;

    uint32 count = 0;
	m_EquipmentSets.BeginLoop();
    do
    {
        Field *fields = result->Fetch();

        EquipmentSet *eqSet = new EquipmentSet;
        eqSet->Guid			= fields[1].GetUInt32();
        eqSet->Name			= fields[2].GetString();
        eqSet->IconName		= fields[3].GetString();
        for(uint32 i = 0; i < EQUIPMENT_SLOT_END; ++i)
		{
            eqSet->ItemGUIDS[i] = fields[4+i].GetUInt32();
			if( eqSet->ItemGUIDS[i] > 1 )	//0 and 1 are reserved values here !
				eqSet->ItemGUIDS[i] = CONVERT_LOWGUID_TO_FULLGUID_ITEM( eqSet->ItemGUIDS[i] );
		}

        m_EquipmentSets.push_front( eqSet );
    
		++count;
        if(count >= MAX_EQUIPMENT_SET_INDEX)                // client limit
            break;
    } while (result->NextRow());
	m_EquipmentSets.EndLoopAndCommit();
}

float UnitToUnitPossitionAdjuster::GetUnitAngle(const uint64 &guid)
{
	UpdateCircle();
	//this unit might not be pushed to world yet !
	CircleingUnits.push_back( guid );	
	float angle_per_mob;
	angle_per_mob = 2.0f * M_PI / ( CircleingUnits.size() + 1);	
	//maybe 0 should be at -2*M_PI ?
	return ( -2 * M_PI + angle_per_mob * ( CircleingUnits.size() - 1 ) );
}

void UnitToUnitPossitionAdjuster::UpdateCircle()
{
	//no spams pls
//	if( GetTickCount() < NextUpdateStamp )
//		return;
//	NextUpdateStamp = GetTickCount() + UNIT_POSITIONING_UPDATE_INTERVAL;

	//sanity check
	if( CenterUnit == NULL || CenterUnit->GetMapMgr() == NULL )
	{
		CircleingUnits.clear();
		return;
	}

	//update our list to see who is still attacking us
	std::list<Unit *>	ValidUnits;
	for(std::list<uint64>::iterator itr=CircleingUnits.begin(); itr!=CircleingUnits.end(); )
	{
		std::list<uint64>::iterator itr2 = itr;
		itr++;
		//check if unit still exists
		Unit *t = CenterUnit->GetMapMgr()->GetUnit( *itr2 );
		if( t )
			ValidUnits.push_back( t );
		else
			CircleingUnits.erase( itr2 );
	}
	//now rearrange the mobs considering a new one will be inserted in the list
	uint32 unit_count = (uint32)(ValidUnits.size());
	if( unit_count == 0 )
		return;
	float angle_per_mob;
	angle_per_mob = 2.0f * M_PI / ValidUnits.size();
	float cur_angle = -2.0*M_PI;
	std::list<Unit *>::iterator	itru;
	for(std::list<Unit*>::iterator itru=ValidUnits.begin(); itru!=ValidUnits.end(); itru++)
		if( *itru && (*itru)->GetAIInterface() )
		{
			(*itru)->GetAIInterface()->SetUnitToFollowAngle( cur_angle );
			cur_angle += angle_per_mob;
		}
}
