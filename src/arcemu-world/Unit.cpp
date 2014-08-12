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


static float AttackToRageConversionTable[PLAYER_LEVEL_CAP + 1]=
{
	0.0f,
	0.499999998893f,
	0.34874214056f,
	0.267397170992f,
	0.216594535676f,
	0.181852997475f,
	0.156596678244f,
	0.137408407814f,
	0.12233646474f,
	0.110185074062f,
	0.100180723915f,
	0.0918008940243f,
	0.084679891259f,
	0.0785541194583f,
	0.0732287738371f,
	0.0685567746212f,
	0.0644249954237f,
	0.0607450001819f,
	0.0574466557344f,
	0.0544736297718f,
	0.0517801553458f,
	0.0493286648502f,
	0.0470880325642f,
	0.0450322506478f,
	0.0431394187932f,
	0.0413909641335f,
	0.0397710324301f,
	0.0382660082118f,
	0.0368641330875f,
	0.035555199573f,
	0.0343303035574f,
	0.0331816427126f,
	0.0321023511953f,
	0.0310863632415f,
	0.0301282999279f,
	0.0292233746364f,
	0.0283673137143f,
	0.0275562895548f,
	0.0267868638875f,
	0.0260559395055f,
	0.0253607190016f,
	0.0246986693537f,
	0.0240674914139f,
	0.0234650935281f,
	0.0228895686471f,
	0.0223391744027f,
	0.0218123157088f,
	0.0213075295236f,
	0.0208234714647f,
	0.02035890402f,
	0.019912686137f,
	0.0194837640053f,
	0.0190711628769f,
	0.0186739797893f,
	0.0182913770778f,
	0.0179225765793f,
	0.0175668544424f,
	0.0172235364711f,
	0.0168919939405f,
	0.0165716398271f,
	0.0162619254091f,
	0.0159623371939f,
	0.0156723941359f,
	0.0153916451144f,
	0.0151196666436f,
	0.0148560607885f,
	0.0146004532678f,
	0.0143524917226f,
	0.0141118441351f,
	0.0138781973828f,
	0.0136512559131f,
	0.01362205913f ,
	0.01354440962f ,
	0.01348274765f ,
	0.01340676809f ,
	0.01332876726f ,
	0.01325120442f ,
	0.01317125412f ,
	0.01309125463f ,
	0.0130112556f ,
	0.01293125565f ,
	0.01285125579f ,
	0.01277125582f ,
	0.01269125582f ,
	0.01261125589f ,
	0.0125312559f ,
	0.0124512559f ,
	0.0123712559f ,
	0.0122912559f ,
	0.01221125591f ,
	0.01213125591f ,
	0.01205125591f ,
	0.01197125591f ,
	0.01189125591f ,
	0.01181125591f ,
	0.01173125591f ,
	0.01165125591f ,
	0.01157125591f ,
	0.01149125591f ,
	0.01141125591f ,
	0.01133125591f ,
	0.01125125591f ,
	0.01117125591f ,
	0.01109125591f ,
	0.01101125591f ,
	0.01093125591f ,
	0.01085125591f ,
	0.01077125591f ,
	0.01069125591f ,
	0.01061125591f ,
	0.01053125591f ,
	0.01045125591f ,
	0.01037125591f ,
	0.01029125591f ,
	0.01021125591f ,
	0.01013125591f ,
	0.01005125591f ,
	0.00997125591f ,
	0.00989125591f ,
	0.00981125591f ,
	0.00973125591f ,
	0.00965125591f ,
	0.00957125591f ,
	0.00949125591f ,
	0.00941125591f ,
	0.00933125591f ,
	0.00925125591f ,
	0.00917125591f ,
	0.00909125591f ,
	0.00901125591f ,
	0.00893125591f ,
	0.00885125591f ,
	0.00877125591f ,
	0.00869125591f ,
	0.00861125591f ,
	0.00853125591f ,
	0.00845125591f ,
	0.00837125591f ,
};

Unit::Unit()
{
	int i;

	m_attackTimer = 0;
	m_attackTimer_1 = 0;
	m_dualWield = false;

	m_fearmodifiers = 0;
	m_state = 0;
	m_special_state = 0;
	m_deathState = ALIVE;
	m_currentSpell = NULL;
	m_meleespell = 0;
	m_addDmgOnce = 0;
	m_TotemSlots[0] = NULL;
	m_TotemSlots[1] = NULL;
	m_TotemSlots[2] = NULL;
	m_TotemSlots[3] = NULL;
	m_ObjectSlots[0] = 0;
	m_ObjectSlots[1] = 0;
	m_ObjectSlots[2] = 0;
	m_ObjectSlots[3] = 0;
	m_silenced = 0;
	disarmed   = false;

	//DK:modifiers
	PctRegenModifier = 0;
	RegenModifier = 0;
	for( i = 0; i < POWER_TYPE_COUNT; i++ )
		PctPowerRegenModifier[i] = 1;
	m_speedModifier = 0;
	m_slowdown = 0;
	m_speedup = 0;
	m_mountedspeedModifier=0;
	m_maxSpeed = 0;
	for(i=0;i<MECHANIC_TOTAL;i++)
	{
		MechanicsDispels[i]=0;
		MechanicsResistancesPCT[i]=0;
		ModDamageTakenByMechCoef[i]=0;
		ModDamageTakenByMechFlat[i]=0;
		MechanicDurationPctMod[i]=0;
	}

	//SM
	SM_CriticalChance=0;
	SM_FDur=0;//flat
	SM_PDur=0;//pct
	SM_FRadius=0;
	SM_FRange=0;
	SM_PCastTime=0;
	SM_FCastTime=0;
	SM_PCriticalDamage=0;
	SM_FDOT=0;
	SM_PDOT=0;
	SM_FEffectBonus=0;
	SM_FEffectTargetBonus=0;
	SM_PEffectBonus=0;
	SM_PEffectTargetBonus=0;
	SM_FDamageBonus=0;
	SM_PDamageBonus=0;
	SM_PMiscEffect=0;
	SM_FMiscEffect=0;
	SM_FHitchance=0;
	SM_PRange=0;//pct
	SM_PRadius=0;
	SM_PAPBonus=0;
	SM_PCost=0;
	SM_FCost=0;
	SM_FAdditionalTargets=0;
	SM_PJumpReduce=0;
	SM_FSpeedMod=0;
	SM_PNonInterrupt=0;
	//SM_FPenalty=0;
	SM_PPenalty=0;
	SM_FCooldownTime = 0;
	SM_PCooldownTime = 0;
	SM_FChanceOfSuccess = 0;
	SM_FRezist_dispell = 0;
	SM_PRezist_dispell = 0;
	SM_FCharges = 0;
	SM_PCharges = 0;
	SM_FThreat = 0;
	SM_PThreat = 0;
	SM_FTime = 0;
	SM_FAddEffect1 = SM_FAddEffect2 = SM_FAddEffect3 = SM_PAddEffect1 = SM_PAddEffect2 = SM_PAddEffect3 = NULL;

	m_pacified = 0;
	m_interruptRegen = 0;
	m_resistChance = 0;
	m_powerRegenPCT = 0;
	RAPvModifier=0;
	APvModifier=0;
	stalkedby=0;

	m_stunned = 0;
	m_manashieldamt=0;
	m_rooted = 0;
	m_triggerSpell = 0;
	m_triggerDamage = 0;
	m_canMove = 0;
	m_noInterrupt = 0;
	m_modlanguage = -1;
	m_magnetcaster = 0;
	
	critterPet = NULL;
	summonPet = NULL;

	m_useAI = false;
	for(i=0;i<10;i++)
		dispels[i]=0;
	for(i=0;i<CREATURE_TYPES;i++)
	{
		CreatureAttackPowerMod[i] = 0;
		CreatureRangedAttackPowerMod[i] = 0;
	}

	m_invisibility = 0;
	m_invisible = false;
	m_invisFlag = INVIS_FLAG_NORMAL;

	for(i = 0; i < INVIS_FLAG_TOTAL; i++)
		m_invisDetect[i] = 0;

	m_stealthLevel = 0;
	m_stealthDetectBonus = 0;
	m_stealth = 0;
	m_can_stealth = true;

	for(i=0;i<5;i++)
		BaseStats[i]=0;

	m_H_regenTimer = 2000;
	m_P_regenTimer = 2000;

	//	if(GetTypeId() == TYPEID_PLAYER) //only player for now
	//		CalculateActualArmor();

	m_aiInterface = new AIInterface();
	m_aiInterface->Init(this, AITYPE_AGRO, MOVEMENTTYPE_NONE);

	m_emoteState = 0;
	m_oldEmote = 0;	
	
	BaseDamage[0]=0;
	BaseOffhandDamage[0]=0;
	BaseRangedDamage[0]=0;
	BaseDamage[1]=0;
	BaseOffhandDamage[1]=0;
	BaseRangedDamage[1]=0;

	m_CombatUpdateTimer = 0;
	for(i=0;i<SCHOOL_COUNT;i++)
	{
		SchoolImmunityList[i] = 0;
		AuraSchoolImmunityList[i] = 0;
		BaseResistance[i] = 0;
//		HealDoneMod[i] = 0;
//		HealDonePctMod[i] = 0;
//		HealTakenMod[i] = 0;
//		HealTakenPctMod[i] = 0;
		DamageTakenMod[i] = 0;
//		DamageDoneModPCT[i]= 0;
		SchoolCastPrevent[i]=0;
		DamageTakenPctMod[i] = 0;
		SpellCritChanceSchool[i] = 0;
		PowerCostMod[i] = 0;
		TargetResistRedModFlat[i] = 0; // armor penetration & spell penetration
		AttackerCritChanceMod[i]=0;
		CritMeleeDamageTakenPctMod[i]=0;
		CritRangedDamageTakenPctMod[i]=0;
		m_generatedThreatModifyerPCT[i] = 0;
	}
	HealDonePctMod = 0;
	HealCritDonePctMod = 0;
	HealDoneMod = 0;
	HealTakenMod = 0;
	HealTakenPctMod = 0;
	DamageTakenPctModOnHP35 = 1;
	RangedDamageTaken = 0;

	for(i = 0; i < 5; i++)
	{
		m_detectRangeGUID[i] = 0;
		m_detectRangeMOD[i] = 0;
	}

	trackStealth = false;

	m_threatModifyer = 0;
	
	// diminishing return stuff
	for(uint32 i=0;i<DIMINISHCOUNT;i++)
	{
		m_diminishCount[i] = 0;
		m_diminishExpireStamp[i] = 0;
	}
	for(uint32 i=0;i<MAX_VISIBLE_AURAS;i++)
		m_auraStackCount[i] = 0;

	dynObj = 0;
	pLastSpell = 0;
	m_flyspeedModifier = 0;
	bInvincible = false;
	m_redirectSpellPackets = 0;
	can_parry = false;
	spellcritperc = 0;

	polySpell = 0;
	RangedDamageTaken = 0;
	m_procCounter = 0;
	m_damgeShieldsInUse = false;
//	fearSpell = 0;
	m_extraAttackCounter_lock = false;
	CombatStatus.SetUnit(this);
	m_temp_summon=false;
//	m_spellsbusy=false;
	m_interruptedRegenTime = 0;
	m_hitfrommeleespell	 = 0;
	m_damageSplitTarget = NULL;
	m_extrastriketarget = 0;
	m_extrastriketargetc = 0;
	trigger_on_stun = 0;
	trigger_on_stun_chance = 100;
	trigger_on_stun_victim = 0;
	trigger_on_stun_chance_victim = 100;
	m_soulSiphon.amt = 0;
	m_soulSiphon.max = 0;
	ModelHalfSize = 1.0f; //worst case unit size. (Should be overwritten)

	m_blockfromspell		= 0;
	m_dodgefromspell		= 0;
	m_parryfromspell		= 0;

	m_damageShields.clear();
	m_reflectSpellSchool.SafeClear();	
	m_procSpells.SafeClear();			
	m_chargeSpells.clear();				
	tmpAura.clear();
	m_extraStrikeTargets.SafeClear();	
	//since auras are cleared these lists are theoretically empty
	m_auras_pos_size = FIRST_AURA_SLOT + 1;
	m_auras_neg_size = MAX_POSITIVE_AURAS + 1;
	m_auras_pas_size = MAX_AURAS + 1;
	for(uint32 i=0;i<MAX_AURAS + MAX_PASSIVE_AURAS;i++)
		m_auras[i] = NULL;
	m_chain = NULL;
	OffensiveMagicalDurationModPCT = 100;	//no mods
	m_vehicle_data = NULL;
	m_CurrentVehicleSeat = VEHICLE_PASSENGER_SLOT_INVALID;
//	m_aura_packet_serialization = 0;
	m_vehicle_data = NULL;
}

Unit::~Unit()
{
	Virtual_Destructor();
}

void Unit::Virtual_Destructor( )
{
	ObjectLock.Acquire();
	sEventMgr.RemoveEvents( this );

	//start to remove badptrs, if you delete from the heap null the ptr's damn!
	RemoveAllAuras();

	if( m_chain != NULL )
	{
		m_chain->RemoveUnit(this);
		m_chain = NULL;
	}

	if( SM_CriticalChance != NULL ) {
		delete [] SM_CriticalChance;
		SM_CriticalChance = NULL;
	}

	if( SM_FDur != NULL ) {
		delete [] SM_FDur;
		SM_FDur = NULL;
	}
	
	if( SM_PDur != NULL ) {
		delete [] SM_PDur;
		SM_PDur = NULL;
	}

	if( SM_FRadius != NULL ) {
		delete [] SM_FRadius;
		SM_FRadius = NULL;
	}

	if( SM_FRange != NULL ) {
		delete [] SM_FRange;
		SM_FRange = NULL;
	}

	if( SM_PCastTime != NULL ) {
		delete [] SM_PCastTime;
		SM_PCastTime = NULL;
	}

	if(SM_FCastTime != NULL ) {
		delete [] SM_FCastTime;
		SM_FCastTime = NULL;
	}

	if(SM_PCriticalDamage != NULL ) {
		delete [] SM_PCriticalDamage;
		SM_PCriticalDamage = NULL;
	}

	if(SM_FDOT != NULL ) {
		delete [] SM_FDOT;
		SM_FDOT = NULL;
	}

	if(SM_PDOT != NULL ) {
		delete [] SM_PDOT;
		SM_PDOT = NULL;
	}

	if(SM_PEffectBonus != NULL ) {
		delete [] SM_PEffectBonus;
		SM_PEffectBonus = NULL;
	}

	if(SM_PEffectTargetBonus != NULL ) {
		delete [] SM_PEffectTargetBonus;
		SM_PEffectTargetBonus = NULL;
	}

	if(SM_FEffectBonus != NULL ) {
		delete [] SM_FEffectBonus;
		SM_FEffectBonus = NULL;
	}

	if(SM_FEffectTargetBonus != NULL ) {
		delete [] SM_FEffectTargetBonus;
		SM_FEffectTargetBonus = NULL;
	}

	if(SM_FDamageBonus != NULL ) {
		delete [] SM_FDamageBonus;
		SM_FDamageBonus = NULL;
	}

	if(SM_PDamageBonus != NULL ) {
		delete [] SM_PDamageBonus;
		SM_PDamageBonus = NULL;
	}

	if(SM_PMiscEffect != NULL ) {
		delete [] SM_PMiscEffect;
		SM_PMiscEffect = NULL;
	}

	if(SM_FMiscEffect != NULL ) {
		delete [] SM_FMiscEffect;
		SM_FMiscEffect = NULL;
	}

	if(SM_FHitchance != NULL ) {
		delete [] SM_FHitchance;
		SM_FHitchance = NULL;
	}

	if(SM_PRange != NULL ) {
		delete [] SM_PRange;
		SM_PRange = NULL;
	}

	if(SM_PRadius != NULL ) {
		delete [] SM_PRadius;
		SM_PRadius = NULL;
	}

	if(SM_PAPBonus != NULL ) {
		delete [] SM_PAPBonus;
		SM_PAPBonus = NULL;
	}

	if(SM_PCost != NULL ) {
		delete [] SM_PCost;
		SM_PCost = NULL;
	}

	if(SM_FCost != NULL ) {
		delete [] SM_FCost;
		SM_FCost = NULL;
	}

	if(SM_FAdditionalTargets != NULL ) {
		delete [] SM_FAdditionalTargets;
		SM_FAdditionalTargets = NULL;
	}

	if(SM_PJumpReduce != NULL ) {
		delete [] SM_PJumpReduce;
		SM_PJumpReduce = NULL;
	}

	if(SM_FSpeedMod != NULL ) {
		delete [] SM_FSpeedMod;
		SM_FSpeedMod = NULL;
	}

	if(SM_PNonInterrupt != NULL ) {
		delete [] SM_PNonInterrupt;
		SM_PNonInterrupt = NULL;
	}

//	if(SM_FPenalty != NULL ) {
//		delete [] SM_FPenalty;
//		SM_FPenalty = NULL;
//	}

	if(SM_PPenalty != NULL ) {
		delete [] SM_PPenalty;
		SM_PPenalty = NULL;
	}

	if(SM_FCooldownTime != NULL ) {
		delete [] SM_FCooldownTime;
		SM_FCooldownTime = NULL;
	}

	if(SM_PCooldownTime != NULL ) {
		delete [] SM_PCooldownTime;
		SM_PCooldownTime = NULL;
	}

	if(SM_FChanceOfSuccess != NULL ) {
		delete [] SM_FChanceOfSuccess;
		SM_FChanceOfSuccess = NULL;
	}

	if(SM_FRezist_dispell != NULL ) {
		delete [] SM_FRezist_dispell;
		SM_FRezist_dispell = NULL;
	}

	if(SM_PRezist_dispell != NULL ) {
		delete [] SM_PRezist_dispell;
		SM_PRezist_dispell = NULL;
	}

	if(SM_FCharges != NULL ) {
		delete [] SM_FCharges;
		SM_FCharges = NULL;
	}

	if(SM_PCharges != NULL ) {
		delete [] SM_PCharges;
		SM_PCharges = NULL;
	}

	if(SM_FThreat != NULL ) {
		delete [] SM_FThreat;
		SM_FThreat = NULL;
	}

	if(SM_PThreat != NULL ) {
		delete [] SM_PThreat;
		SM_PThreat = NULL;
	}

	if(SM_FTime != NULL ) {
		delete [] SM_FTime;
		SM_FTime = NULL;
	}

	if(SM_FAddEffect1 != NULL ) {
		delete [] SM_FAddEffect1;
		SM_FAddEffect1 = NULL;
	}

	if(SM_FAddEffect2 != NULL ) {
		delete [] SM_FAddEffect2;
		SM_FAddEffect2 = NULL;
	}

	if(SM_FAddEffect3 != NULL ) {
		delete [] SM_FAddEffect3;
		SM_FAddEffect3 = NULL;
	}

	if(SM_PAddEffect1 != NULL ) {
		delete [] SM_PAddEffect1;
		SM_PAddEffect1 = NULL;
	}

	if(SM_PAddEffect2 != NULL ) {
		delete [] SM_PAddEffect2;
		SM_PAddEffect2 = NULL;
	}

	if(SM_PAddEffect3 != NULL ) {
		delete [] SM_PAddEffect3;
		SM_PAddEffect3 = NULL;
	}

	if( m_aiInterface )
	{
		delete m_aiInterface;
		m_aiInterface = NULL;
	}

	if( m_currentSpell ) 
	{
		m_currentSpell->cancel();
		m_currentSpell = NULL;
	}

	if( m_damageSplitTarget ) 
	{
		delete m_damageSplitTarget;
		m_damageSplitTarget = NULL;
	}

	//well we should have moved stuff from here much earlier
	m_extraStrikeTargets.SafeClear( );	ASSERT( m_extraStrikeTargets.begin() == NULL );
	m_extra_attacks.SafeClear( );		ASSERT( m_extra_attacks.begin() == NULL );

	//auras that are left in the queu to be added to the mob but for some reason they were never processed
	std::map<uint32,Aura*>::iterator tmpAuraitr;
	for( tmpAuraitr = tmpAura.begin(); tmpAuraitr != tmpAura.end(); tmpAuraitr++)
		tmpAuraitr->second->Remove();
	tmpAura.clear();

	// reflects not created by auras need to be deleted manually
	m_reflectSpellSchool.SafeClear( );	ASSERT( m_reflectSpellSchool.begin() == NULL );

	m_damageShields.clear();
	m_procSpells.SafeClear( );		ASSERT( m_procSpells.begin() == NULL );
	m_chargeSpells.clear();
	ExitVehicle();
	if( m_vehicle_data && m_vehicle_data->GetOwner() == this )
		DestoryVehicle();

	//empty loot
	loot.items.clear();
	ObjectLock.Release();
	Object::Virtual_Destructor();
}

void Unit::Update( uint32 p_time )
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	
	Object::Update( p_time );	//99% this does nothing

	_UpdateSpells( p_time );

	if(!IsDead())
	{
		//-----------------------POWER & HP REGENERATION-----------------
/* Please dont do temp fixes. Better report to me. Thx. Shady */
        if( p_time >= m_H_regenTimer )
		    RegenerateHealth();
	    else
		    m_H_regenTimer -= p_time;

		if( p_time >= m_P_regenTimer )
		{
			RegeneratePower( false );
			m_interruptedRegenTime=0;
		}
		else
		{
			m_P_regenTimer -= p_time;
			if (m_interruptedRegenTime)
			{
				if(p_time>=m_interruptedRegenTime)
					RegeneratePower( true );
				else
					m_interruptedRegenTime -= p_time;
			}
		}

		if(m_aiInterface != NULL && m_useAI)
			m_aiInterface->Update(p_time);

		// if health changed since last time. 
		// must be here to avoid deadlocks
//		if(HasUpdateField( UNIT_FIELD_HEALTH ))	//this shit fails to trigger when not regnerating health :S
		if( GetUInt32Value(UNIT_FIELD_HEALTH) != GetUInt32Value(UNIT_FIELD_MAXHEALTH) )
			EventHealthChangeSinceLastUpdate();
	}
}

bool Unit::canReachWithAttack(Unit *pVictim)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( GetMapId() != pVictim->GetMapId() )
	{ 
		return false;
	}

//	float targetreach = pVictim->GetFloatValue(UNIT_FIELD_COMBATREACH);
	float selfreach;
	if( IsPlayer() )
		selfreach = 5.0f; // minimum melee range, UNIT_FIELD_COMBATREACH is too small and used eg. in melee spells
	else
		selfreach = m_floatValues[UNIT_FIELD_COMBATREACH];

	float targetradius;
//	targetradius = pVictim->m_floatValues[UNIT_FIELD_BOUNDINGRADIUS]; //this is plain wrong. Represents i have no idea what :)
	targetradius = pVictim->GetModelHalfSize();
	float selfradius;;
//	selfradius = m_floatValues[UNIT_FIELD_BOUNDINGRADIUS];
	selfradius = GetModelHalfSize();
//	float targetscale = pVictim->m_floatValues[OBJECT_FIELD_SCALE_X];
//	float selfscale = m_floatValues[OBJECT_FIELD_SCALE_X];

	//float distance = sqrt(GetDistanceSq(pVictim));
	float delta_x = pVictim->GetPositionX() - GetPositionX();
	float delta_y = pVictim->GetPositionY() - GetPositionY();
	float distance = sqrt(delta_x*delta_x + delta_y*delta_y);


//	float attackreach = (((targetradius*targetscale) + selfreach) + (((selfradius*selfradius)*selfscale)+1.50f));
	float attackreach = targetradius + selfreach + selfradius;

	//formula adjustment for player side.
	if( IsPlayer() )
	{
/*
		if( attackreach <= 8 && attackreach >= 5 && targetradius >= 1.80f)
			attackreach = 11; //giant type units

		if( attackreach > 11)
			attackreach = 11; //distance limited to max 11 yards attack range //max attack distance

		if( attackreach < 5 )
			attackreach = 5; //normal units with too small reach.

		//range can not be less than 5 yards - this is normal combat range, SCALE IS NOT SIZE
*/
		// latency compensation!!
		// figure out how much extra distance we need to allow for based on our movespeed and latency.
		if( pVictim->IsPlayer() && SafePlayerCast( pVictim )->m_isMoving )
		{
			// this only applies to PvP.
			uint32 lat = SafePlayerCast( pVictim )->GetSession() ? SafePlayerCast( pVictim )->GetSession()->GetLatency() : 0;

			// if we're over 500 get fucked anyway.. your gonna lag! and this stops cheaters too
			lat = ( lat > 500 ) ? 500 : lat;

			// calculate the added distance
			attackreach += ( m_runSpeed * 0.001f ) * float( lat );
		}

		if( SafePlayerCast( this )->m_isMoving )
		{
			// this only applies to PvP.
			uint32 lat = SafePlayerCast( this )->GetSession() ? SafePlayerCast( this )->GetSession()->GetLatency() : 0;

			// if we're over 500 get fucked anyway.. your gonna lag! and this stops cheaters too
			lat = ( lat > 500) ? 500 : lat;

			// calculate the added distance
			attackreach += ( m_runSpeed * 0.001f ) * float( lat );
		}
	}
	return ( distance <= attackreach );
}

void Unit::GiveGroupXP(Unit *pVictim, Player *PlayerInGroup)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(!PlayerInGroup) 
	{ 
		return;
	}
	if(!pVictim) 
	{ 
		return;
	}
	if(!PlayerInGroup->InGroup()) 
	{ 
		return;
	}
	Group *pGroup = PlayerInGroup->GetGroup();
	uint32 xp;
	if(!pGroup) 
	{ 
		return;
	}

	//Get Highest Level Player, Calc Xp and give it to each group member
	Player *pHighLvlPlayer = NULL;
	Player *pGroupGuy = NULL;
	  int active_player_count=0;
	Player *active_player_list[MAX_GROUP_SIZE_RAID];//since group is small we can afford to do this ratehr then recheck again the whole active player set
	int total_level=0;
	float xp_mod = 1.0f;

/*	if(pGroup->GetGroupType() == GROUP_TYPE_RAID)
	{   //needs to change
		//Calc XP
		xp = CalculateXpToGive(pVictim, PlayerInGroup);
		xp /= pGroup->MemberCount();

		GroupMembersSet::iterator itr;
		for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++)
		{
			for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
			{
				if((*itr)->getLevel() < sWorld.LevelCap)
					(*itr)->GiveXP(xp, pVictim->GetGUID(), true);
			}
		}
	}
	else if(pGroup->GetGroupType() == GROUP_TYPE_PARTY) */
	//change on 2007 04 22 by Zack
	//we only take into count players that are near us, on same map
	GroupMembersSet::iterator itr;
	pGroup->Lock();
	for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++) {
		for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
		{
			pGroupGuy = (*itr)->m_loggedInPlayer;
			if( pGroupGuy && 
				pGroupGuy->isAlive() && 
//				PlayerInGroup->GetInstanceID()==pGroupGuy->GetInstanceID() &&
				pVictim->GetMapMgr() == pGroupGuy->GetMapMgr() && 
				pGroupGuy->GetDistanceSq(pVictim)<100*100
				)
			{
				active_player_list[active_player_count]=pGroupGuy;
				active_player_count++;
				total_level += pGroupGuy->getLevel();
				if(pHighLvlPlayer)
				{
					if(pGroupGuy->getLevel() > pHighLvlPlayer->getLevel())
						pHighLvlPlayer = pGroupGuy;
				}
				else 
					pHighLvlPlayer = pGroupGuy;
			}
		}
	}
	pGroup->Unlock();
	if(active_player_count<1) //killer is always close to the victim. This should never execute
	{
		if(PlayerInGroup == 0)
		{
			PlayerInfo * pleaderinfo = pGroup->GetLeader();
			if(!pleaderinfo->m_loggedInPlayer)
			{ 
				return;
			}

			PlayerInGroup = pleaderinfo->m_loggedInPlayer;
		}

		xp = CalculateXpToGive(pVictim, PlayerInGroup);
		PlayerInGroup->GiveXP(xp, pVictim->GetGUID(), true);
	}
	else
	{
		if( pGroup->GetGroupType() == GROUP_TYPE_PARTY)
		{
			if(active_player_count==3)
				xp_mod=1.1666f;
			else if(active_player_count==4)
				xp_mod=1.3f;
			else if(active_player_count==5)
				xp_mod=1.4f;
			else xp_mod=1;//in case we have only 2 members ;)
		}
		else if(pGroup->GetGroupType() == GROUP_TYPE_RAID)
			xp_mod=0.5f;

		if(pHighLvlPlayer == 0)
		{
			PlayerInfo * pleaderinfo = pGroup->GetLeader();
			if(!pleaderinfo->m_loggedInPlayer)
			{ 
				return;
			}

			pHighLvlPlayer = pleaderinfo->m_loggedInPlayer;
		}

		xp = CalculateXpToGive(pVictim, pHighLvlPlayer);
		//i'm not sure about this formula is correct or not. Maybe some brackets are wrong placed ?
		for(int i=0;i<active_player_count;i++)
		{
			Player * plr = active_player_list[i];
			uint32 giveXpToPlayer = float2int32( ( ( xp * plr->getLevel() ) / total_level ) * xp_mod);
			plr->GiveXP(giveXpToPlayer , pVictim->GetGUID(), true );

			active_player_list[i]->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_LASTKILLWITHHONOR);
			if(!sEventMgr.HasEvent(active_player_list[i],EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE))
			{
				sEventMgr.AddEvent(SafeUnitCast(active_player_list[i]),&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_LASTKILLWITHHONOR,EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE,20000,1,0);
			}
			else
			{
				sEventMgr.ModifyEventTimeLeft(active_player_list[i],EVENT_LASTKILLWITHHONOR_FLAG_EXPIRE,20000);
			}

			if ( plr->GetSummon() && plr->GetSummon()->CanGainXP() )
			{
				uint32 pet_xp = (int)(CalculateXpToGive( pVictim, plr->GetSummon() ) * xp_mod); // vojta: this isn't blizzlike probably but i have no idea, feel free to correct it
				if ( pet_xp > 0 )
					plr->GetSummon()->GiveXP( pet_xp );
			}
		}
	}
		/* old code start before 2007 04 22
		GroupMembersSet::iterator itr;
		for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++)
		{
			for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
			{
				pGroupGuy = (*itr);
				if(pGroupGuy)
				{
					if(pHighLvlPlayer)
					{
						if(pGroupGuy->getLevel() > pHighLvlPlayer->getLevel())
						{
							pHighLvlPlayer = pGroupGuy;
						}
					}
					else
						pHighLvlPlayer = pGroupGuy;
				}
			}
		}

		//Calc XP
		xp = CalculateXpToGive(pVictim, pHighLvlPlayer);
		uint32 giveXP = 0;

		for(uint32 i = 0; i < pGroup->GetSubGroupCount(); i++)
		{
			for(itr = pGroup->GetSubGroup(i)->GetGroupMembersBegin(); itr != pGroup->GetSubGroup(i)->GetGroupMembersEnd(); ++itr)
			{
				pGroupGuy = (*itr);
				giveXP = xp * pGroupGuy->getLevel() / (pHighLvlPlayer->getLevel() + pGroupGuy->getLevel());
				if(pGroupGuy->getLevel() < sWorld.LevelCap)
					pGroupGuy->GiveXP(giveXP, pVictim->GetGUID(), true);
			}
		}
	}*/
}

//needed cause memory menager crashes for external allocations :(
void Unit::RegisterScriptProcStruct( ProcTriggerSpell &pts )
{
	ProcTriggerSpell *ptsc = new ProcTriggerSpell( pts );	//core allocation instead of external one ?
	m_procSpells.push_front( ptsc );
}

uint32 Unit::HandleProc( uint32 flag, Unit* victim, SpellEntry* CastingSpell, int32 dmg, int32 Abs )
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	//why would anyone call it without flags ? Well ..ask "strike"
	if( flag == 0 )
		return 0;
//	if( IsPlayer() && SafePlayerCast(this)->m_onTaxi == true )
//		return;
	++m_procCounter; // !!! do not forget to decrease this before exit !!
	/* hmm whats a reasonable value here */
	if( m_procCounter > 5 )
	{
		/* something has proceed over 10 times in a loop :/ dump the spellids to the crashlog, as the crashdump will most likely be useless. */
		// BURLEX FIX ME!
		//OutputCrashLogLine("HandleProc %u SpellId %u (%s) %u", flag, spellId, sSpellStore.LookupString(sSpellStore.LookupEntry(spellId)->Name), m_procCounter);
		--m_procCounter;
		return 0;
	}

	uint32 now_in_ms = getMSTime();
	uint32 resisted_dmg = 0;
	ProcHandlerContextShare context;
	context.in_Caller = this;
	context.in_Victim = victim;
	context.in_CastingSpell = CastingSpell;
	context.in_dmg = dmg;
	context.in_abs = Abs;
	context.out_dmg_absorb = 0;
	context.in_events_filter_flags = flag;

	ProcTriggerSpell	*itr2;
	CommitPointerListNode<ProcTriggerSpell> *itr;
	m_procSpells.BeginLoop();
	for(itr = m_procSpells.begin();itr != m_procSpells.end();itr = itr->Next() )
	{
		itr2 = itr->data;
		if( itr2->deleted )
		{
			if( m_procCounter == 1 )	//if this is a nested proc then we should have this set to TRUE by the father proc
				m_procSpells.SafeRemove( itr, 1 );
			continue;
		}

		//flags can be mixed, we test them in mixed way. Maybe we should handle each one ?
		if( ! (itr2->procFlags & flag ) )
			continue;

		if( CastingSpell != NULL )
		{
			//this is to avoid spell proc on spellcast loop. We use dummy that is same for both spells
			//if( CastingSpell->Id == itr2->spellId )
			if( 
//				CastingSpell->Id == itr2->origId || // seed of corruption and pyroclasm proc on self 
				CastingSpell->Id == itr2->spellId 
//				&& (CastingSpell->c_is_flags & SPELL_FLAG_IS_PROC_TRIGGER_PROC) == 0	//some rare spells do not have a proc just get scripted. If we marked this spell then let him proc on self
				)
			{
				//printf("WOULD CRASH HERE ON PROC: CastingId: %u, OrigId: %u, SpellId: %u\n", CastingSpell->Id, itr2->origId, itr2->spellId);
				continue;
			}
		}

		uint32 spellId = itr2->spellId;
		if( !spellId )
			continue; //there are procs without spells ?
		
		//lookupentry returns first spell for wrong ids to avoid crash, there is no need for NULL check
		SpellEntry* spe  = dbcSpell.LookupEntry( spellId );

		uint32 origId = itr2->origId;

		if( origId == 0 )
			origId = itr2->spellId; // item procs have it like this !

		SpellEntry* ospinfo = dbcSpell.LookupEntry( origId );//no need to check if exists or not since we were not able to register this trigger if it would not exist :P

		uint32 proc_Chance = itr2->procChance;

//		SM_FIValue( SM_FChanceOfSuccess, (int32*)&proc_Chance, ospinfo->SpellGroupType );
		if( !Rand( proc_Chance ) )
			continue;

		//check if we can trigger due to time limitation
		if( itr2->procInterval )
		{
			if( itr2->LastTrigger + itr2->procInterval > now_in_ms )
				continue; //we can't trigger it yet.
		}

		//since we did not allow to remove auras like these with interrupt flag we have to remove them manually.
		if( itr2->procFlags2 & PROC2_REMOVEONUSE )
			RemoveAura( origId );

		int dmg_overwrite = 0, dmg_overwrite1 = 0, dmg_overwrite2 = 0;

		SpellCastTargets targets( victim->GetGUID() );
		if( itr2->procFlags2 & PROC2_TARGET_SELF )
			targets.m_unitTarget = GetGUID();

		if( spe->ProcOnNameHash[0] != 0 )
		{
			if( CastingSpell == NULL )
				continue;

			if( CastingSpell->NameHash != spe->ProcOnNameHash[0] &&
				CastingSpell->NameHash != spe->ProcOnNameHash[1] &&
				CastingSpell->NameHash != spe->ProcOnNameHash[2] )
				continue;
		}
		if( ospinfo->ProcOnNameHash[0] != 0 )
		{
			if( CastingSpell == NULL )
				continue;

			if( CastingSpell->NameHash != ospinfo->ProcOnNameHash[0] &&
				CastingSpell->NameHash != ospinfo->ProcOnNameHash[1] &&
				CastingSpell->NameHash != ospinfo->ProcOnNameHash[2] )
				continue;
		}

		if( spe->ProcHandler )
		{
			context.in_event = itr2;
			context.in_OwnerSpell = ospinfo;
			context.out_handler_result = PROC_HANDLER_CONTINUE_TO_NEXT;
			context.out_dmg_absorb = 0;
			context.out_dmg_overwrite[ 0 ] = context.out_dmg_overwrite[ 1 ] = context.out_dmg_overwrite[ 2 ] = 0;
			spe->ProcHandler( &context );
			if( context.out_handler_result == PROC_HANDLER_CONTINUE_TO_NEXT )
			{
				//!!mark it as procced !! -> only if handler return is not early exited !!
//				if( itr2->LastTrigger <= now_in_ms - itr2->procInterval )	//avoid custom mods to this value
//					itr2->LastTrigger = now_in_ms; // consider it triggered
				continue;
			}
			dmg_overwrite = context.out_dmg_overwrite[ 0 ];
			dmg_overwrite1 = context.out_dmg_overwrite[ 1 ];
			dmg_overwrite2 = context.out_dmg_overwrite[ 2 ];
			resisted_dmg += context.out_dmg_absorb;
		}

		itr2->LastTrigger = now_in_ms; // consider it triggered

		SpellEntry *spellInfo = dbcSpell.LookupEntry( spellId );
		Spell *spell = SpellPool.PooledNew();
		spell->Init(this, spellInfo ,true, NULL);
		spell->forced_basepoints[0] = dmg_overwrite;
		spell->forced_basepoints[1] = dmg_overwrite1;
		spell->forced_basepoints[2] = dmg_overwrite2;
		spell->ProcedOnSpell = CastingSpell;
		spell->pSpellId=origId;
//printf("!!!!! wil proc spell with target guid %u \n",(uint32)(targets.m_unitTarget) & LOWGUID_ENTRY_MASK);
		spell->prepare(&targets);
	}
	m_procSpells.EndLoopAndCommit();

	std::map<uint32,struct SpellCharge>::iterator iter,iter2;
	uint32 bulky_time = getMSTime();
	for( iter2 = m_chargeSpells.begin(); iter2!= m_chargeSpells.end(); iter2++)
	{
		if(iter2->second.count)
		{
			//trying to fix proc spells that proc and get removed on same cycle : ex clearcasting procs on casting and gets removed on next casting
			if( iter2->second.created_at_stamp >= bulky_time )
				continue;
			//if we procced these then we should not remove them
			if( CastingSpell == iter2->second.spe)
				continue;
			if((iter2->second.ProcFlag & flag))
			{
				//Fixes for spells that dont lose charges when dmg is absorbd
				if( dmg == 0 && 0 != (iter2->second.ProcFlag & ( PROC_ON_CRIT_HIT_VICTIM | PROC_ON_PHYSICAL_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_CRIT_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_ANY_DAMAGE_VICTIM | PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK | PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_PHYSICAL_ATTACK | PROC_ON_CRIT_ATTACK))) 
					continue;

				if( iter2->second.spe->ChargeHandler )
				{
					context.out_handler_result = PROC_HANDLER_CONTINUE_TO_NEXT;
					iter2->second.spe->ChargeHandler( &context );
					if( context.out_handler_result == PROC_HANDLER_CONTINUE_TO_NEXT )
						continue;
				}

				sLog.outDebug("Removing aura %u as charge expanded,remaining charges %u",iter2->second.spe->Id,iter2->second.count);
				this->RemoveAura(iter2->second.spe->Id);
			}
		}
	}

	if( m_procCounter > 0 )
		--m_procCounter;
	if( m_procCounter == 0 )
	{
		//atomic list parsing - my ass
		for( iter = m_chargeSpells.begin(); iter!= m_chargeSpells.end();)
		{
			iter2=iter++;
			if( iter2->second.count <= 0 )
				m_chargeSpells.erase(iter2);
		}
	}

	return resisted_dmg;
}

//damage shield is a triggered spell by owner to atacker
void Unit::HandleProcDmgShield(uint32 flag, Unit* attacker)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	//make sure we do not loop dmg procs
	if(this==attacker || !attacker)
	{ 
		return;
	}
	if(m_damgeShieldsInUse)
	{ 
		return;
	}
	m_damgeShieldsInUse = true;
	//charges are already removed in handleproc
	sStackWolrdPacket(data,SMSG_SPELLDAMAGESHIELD,40);
	std::list<DamageProc>::iterator i;
	std::list<DamageProc>::iterator i2;
	std::list<DamageProc> tlist = m_damageShields;	//cause dealdamage might change the list !
	for(i = tlist.begin();i != tlist.end();)     // Deal Damage to Attacker
	{
		i2 = i++; //we should not proc on proc.. not get here again.. not needed.Better safe then sorry.
		if(	(flag & (*i2).m_flags) )
		{
			if(PROC_SCRIPTED_PROCTEST & (*i2).m_flags)
			{
				data.Initialize(SMSG_SPELLDAMAGESHIELD);
				data << this->GetGUID();
				data << attacker->GetGUID();
				data << (*i2).m_spellId;
				data << (*i2).m_damage;
				data << uint32(attacker->GetOverkill((*i2).m_damage));
				data << ( 1 << (*i2).m_school );
#ifdef MINIMIZE_NETWORK_TRAFIC
				SendMessageToDuel( &data );
#else
				SendMessageToSet(&data,true);
#endif
				this->DealDamage(attacker,(*i2).m_damage,0,0,(*i2).m_spellId);
			}
			else
			{
				SpellEntry	*ability=dbcSpell.LookupEntry((*i2).m_spellId);
				this->Strike( attacker, RANGED, ability, 0, 0, (*i2).m_damage, true, true );//can dmg shields miss at all ?
			}
		}
	}
	m_damgeShieldsInUse = false;
}

/*
void Unit::HandleProcSpellOnSpell(Unit* Victim,uint32 damage,bool critical)
{
}
*/
bool Unit::isCasting()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	return (m_currentSpell != NULL);
}

bool Unit::IsInInstance()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	MapInfo *pMapinfo = WorldMapInfoStorage.LookupEntry(this->GetMapId());
	if(pMapinfo)
	{ 
		return ( IS_MAP_INSTANCE( pMapinfo ) );
	}

	return false;
}

void Unit::RegenerateHealth()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	m_H_regenTimer = 2000;//set next regen time 

	if(!isAlive() || GetUInt32Value( UNIT_FIELD_HEALTH ) == 0 )
	{ 
		return;
	}

	// player regen
	if(this->IsPlayer())
	{
		// These only NOT in combat
		if(!CombatStatus.IsInCombat())
		{
			SafePlayerCast( this )->RegenerateHealth(false);
		}
		else
			SafePlayerCast( this )->RegenerateHealth(true);
	}
	else
	{
		// Only regen health out of combat
		if(!CombatStatus.IsInCombat())
			SafeCreatureCast(this)->RegenerateHealth();
	}
}

void Unit::RegeneratePower(bool isinterrupted)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
    // This is only 2000 IF the power is not rage
	if ( isinterrupted )
		m_interruptedRegenTime = 2000;
	else
		m_P_regenTimer = 2000;//set next regen time 

	if(!isAlive())
	{ 
		return;
	}

	// player regen
	if(this->IsPlayer())
	{
		uint32 powertype = GetPowerType();
		switch(powertype)
		{
		case POWER_TYPE_MANA:
			SafePlayerCast( this )->RegenerateMana(isinterrupted);
			break;
		case POWER_TYPE_ENERGY:
			SafePlayerCast( this )->RegenerateEnergy();
			break;

		case POWER_TYPE_RAGE:
			{
				// These only NOT in combat
				if(!CombatStatus.IsInCombat())
				{
					m_P_regenTimer = 3000;
					SafePlayerCast( this )->LooseRage( 30 - SafePlayerCast( this )->m_ModInterrMRegen );
				}
				else
				{
					m_P_regenTimer = 3000;
					if( SafePlayerCast( this )->m_ModInterrMRegen )
						SafePlayerCast( this )->LooseRage( -( SafePlayerCast( this )->m_ModInterrMRegen ) );
				}

			}break;
		case POWER_TYPE_RUNIC_POWER:
			{
//				m_P_regenTimer = 1000; //who needs this blizzlike shit to spam us, we double everything :P
//				m_P_regenTimer = 2000; //less updates spam since 1 / 2 = 5 = int32 ;)
				//death runes get converted through spell and do not regenerate
				for(int i=0;i<TOTAL_USED_RUNES;i++)
					if( SafePlayerCast( this )->m_runes[i] < MAX_RUNE_VALUE )
					{
//						SafePlayerCast( this )->m_runes[i] += SafePlayerCast( this )->GetFloatValue( PLAYER_RUNE_REGEN_1 + SafePlayerCast( this )->m_rune_types[ i ] );
						SafePlayerCast( this )->m_runes[i] += 2*SafePlayerCast( this )->GetFloatValue( PLAYER_RUNE_REGEN_1 + SafePlayerCast( this )->m_rune_types[ i ] );
						if( SafePlayerCast( this )->m_runes[i] > MAX_RUNE_VALUE )
							SafePlayerCast( this )->m_runes[i] = MAX_RUNE_VALUE;
						SafePlayerCast( this )->UpdateRuneIcon(i);
					}
				SafePlayerCast( this )->RegenetateRunicPower();
			}break;
		}
		
		/*

		There is a problem here for druids.
		Druids when shapeshifted into bear have 2 power with different regen timers
		a) Mana (which regenerates while shapeshifted
		b) Rage

		Mana has a regen timer of 2 seconds
		Rage has a regen timer of 3 seconds

		I think the only viable way of fixing this is to have 2 different timers
		to check each individual power.

		Atm, mana is being regen at 3 seconds while shapeshifted...

		*/


		// druids regen mana when shapeshifted
		if(getClass() == DRUID && powertype != POWER_TYPE_MANA)
			SafePlayerCast( this )->RegenerateMana(isinterrupted);
	}
	else
	{
		uint32 powertype = GetPowerType();
		switch(powertype)
		{
		case POWER_TYPE_MANA:
			SafeCreatureCast(this)->RegenerateMana();
			break;
		case POWER_TYPE_FOCUS:
			SafeCreatureCast(this)->RegenerateFocus();
			m_P_regenTimer = 4000;
			break;
		}
	}
}

void Unit::CalculateResistanceReduction(Unit *pVictim,dealdamage * dmg, SpellEntry* ability)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	float AverageResistance = 0.0f;
	float ArmorReduce;

	if((*dmg).school_type == 0)//physical
	{		
		float weapon_target_armor_ignore_mod;
		ArmorReduce = TargetResistRedModFlat[0];
		if(this->IsPlayer())
		{
			weapon_target_armor_ignore_mod = SafePlayerCast( this )->weapon_target_armor_pct_ignore;
			//seems like client gets bigger values somehow. Like 20% boost
			weapon_target_armor_ignore_mod -= SafePlayerCast( this )->CalcRating( PLAYER_RATING_MODIFIER_ARMOR_PENETRATION_RATING ) / 100.0f;
//printf("!!!!!!!!weapon_target_armor_pct_ignore = %f\n",weapon_target_armor_pct_ignore);
			if( weapon_target_armor_ignore_mod <= 0.40f )
				weapon_target_armor_ignore_mod = 0.40f;
			else if( weapon_target_armor_ignore_mod > 1.0f )
				weapon_target_armor_ignore_mod = 1.0f;
		}
		else
		{
			weapon_target_armor_ignore_mod = 1.0f;
		}

		if(ArmorReduce >= pVictim->GetResistance(0))		// fully penetrated :O
		{ 
			return;
		}

//		double Reduction = double(pVictim->GetResistance(0)) / double(pVictim->GetResistance(0)+400+(85*getLevel()));
		//dmg reduction formula from xinef
		float Reduction = 0;
		float victim_res = pVictim->GetResistance(0) * weapon_target_armor_ignore_mod;
		if(getLevel() < 60) 
			Reduction = float(victim_res - ArmorReduce) / float(victim_res+400+(85*getLevel()));
		else if(getLevel() > 59 && getLevel() < PLAYER_LEVEL_CAP) 
			Reduction = float(victim_res - ArmorReduce) / float(victim_res-22167.5f+(467.5f*getLevel()));
		//
		else 
			Reduction = float(victim_res - ArmorReduce) / float(victim_res+10557.5);
		if(Reduction > 0.75f) 
			Reduction = 0.75f;
		else if(Reduction < 0) 
			Reduction = 0;
		if(Reduction)
		{
//			dmg[0].resisted_damage += (uint32)(dmg[0].full_damage*Reduction);
			dmg[0].full_damage = (uint32)(dmg[0].full_damage*(1-Reduction));	  // no multiply by 0
		}
	}
	else
	{
		// applying resistance to other type of damage 
//		int32 RResist = float2int32( float(pVictim->GetResistance( (*dmg).school_type ) + ((pVictim->getLevel() > getLevel()) ? (pVictim->getLevel() - this->getLevel()) * 5 : 0)) - TargetResistRedModFlat[(*dmg).school_type] ); 
		int32 RResist;
		if( pVictim->getLevel() > getLevel() )
			RResist = float2int32( float(pVictim->GetResistance( (*dmg).school_type ) + (pVictim->getLevel() - this->getLevel()) * 5 ) - TargetResistRedModFlat[(*dmg).school_type] ); 
		else 
			RResist = float2int32( float(pVictim->GetResistance( (*dmg).school_type )) - TargetResistRedModFlat[(*dmg).school_type] ); 
		if (RResist<0)
			RResist = 0;
		AverageResistance = (float)(RResist) / (float)(getLevel() * 5) * 0.75f;
		  if(AverageResistance > 0.75f)
			AverageResistance = 0.75f;

		  // NOT WOWWIKILIKE but i think it's actual to add some fullresist chance frome resistances
		  if (!ability || !(ability->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY))
		  {
			  float Resistchance=(float)pVictim->GetResistance( (*dmg).school_type)/(float)pVictim->getLevel();
			  Resistchance*=Resistchance;
			  if(Rand(Resistchance))
				  AverageResistance=1.0f;
		  }

		if(AverageResistance>0)
			(*dmg).resisted_damage = (uint32)(((*dmg).full_damage)*AverageResistance);
		else 
			(*dmg).resisted_damage=0; 
	}
	//maybe gather from here and there and add resiliance here ? Right now it is found in : dealdamage
}

uint32 Unit::GetSpellDidHitResult( Unit* pVictim, uint32 weapon_damage_type, SpellEntry* ability )
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	Item * it = NULL;
	float hitchance          = 0.0f;
	float dodge				 = 0.0f;
	float parry				 = 0.0f;
	float block				 = 0.0f;

	float hitmodifier		 = 0;
	int32 self_skill;
	int32 victim_skill;
	uint32 SubClassSkill	 = SKILL_UNARMED;

	bool backAttack			 = !pVictim->isInFront( this ); // isInBack is bugged!
	uint32 vskill            = 0;

	//==========================================================================================
	//==============================Victim Skill Base Calculation===============================
	//==========================================================================================
	if( pVictim->IsPlayer() )
	{
		vskill = SafePlayerCast( pVictim )->_GetSkillLineCurrent( SKILL_DEFENSE );
		if( weapon_damage_type != RANGED && !backAttack )
		{
			//--------------------------------block chance----------------------------------------------
			block = pVictim->GetFloatValue(PLAYER_BLOCK_PERCENTAGE); //shield check already done in Update chances
			//--------------------------------dodge chance----------------------------------------------
			if( pVictim->m_stunned <= 0 ) 
			{
				dodge = pVictim->GetFloatValue( PLAYER_DODGE_PERCENTAGE );
			}
			//--------------------------------parry chance----------------------------------------------
			if( pVictim->can_parry && !pVictim->disarmed )
			{
				if( SafePlayerCast( pVictim )->HasSpell( 3127 ) || SafePlayerCast( pVictim )->HasSpell( 18848 ) )
				{
					parry = pVictim->GetFloatValue( PLAYER_PARRY_PERCENTAGE );
				}
			}
		}
		victim_skill = float2int32( vskill + SafePlayerCast( pVictim )->CalcRating( PLAYER_RATING_MODIFIER_DEFENCE ) );
	}
	//--------------------------------mob defensive chances-------------------------------------
	else
	{
		if( weapon_damage_type != RANGED && !backAttack )
			dodge = pVictim->GetUInt32Value(UNIT_FIELD_STAT1) / 14.5f; // what is this value?
		victim_skill = pVictim->getLevel() * 5;
		if(pVictim->m_objectTypeId == TYPEID_UNIT) 
		{ 
			Creature * c = SafeCreatureCast(pVictim);
			if(c&&c->GetCreatureInfo()&&c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS)
			{
				victim_skill = std::max(victim_skill,((int32)this->getLevel()+3)*5); //used max to avoid situation when lowlvl hits boss.
			}
		} 
	}
	//==========================================================================================
	//==============================Attacker Skill Base Calculation=============================
	//==========================================================================================
	if(this->IsPlayer())
	{	  
		self_skill = 0;
		Player* pr = SafePlayerCast( this );
		hitmodifier = pr->GetHitFromMeleeSpell();  

		switch( weapon_damage_type )
		{
		case MELEE:   // melee main hand weapon
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
			hitmodifier += pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT );
			if( pVictim->IsPlayer() )
				hitmodifier -= SafePlayerCast( pVictim )->m_resist_hit[ MOD_MELEE ];
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL ) );
			break;
		case OFFHAND: // melee offhand weapon (dualwield)
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
			hitmodifier += pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT );
			if( pVictim->IsPlayer() )
				hitmodifier -= SafePlayerCast( pVictim )->m_resist_hit[ MOD_MELEE ];
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL ) );
			break;
		case RANGED:  // ranged weapon
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_RANGED );
			hitmodifier += pr->CalcRating( PLAYER_RATING_MODIFIER_RANGED_HIT );
			if( pVictim->IsPlayer() )
				hitmodifier -= SafePlayerCast( pVictim )->m_resist_hit[ MOD_RANGED ];
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_RANGED_SKILL ) );
			break;
		}

		// erm. some spells don't use ranged weapon skill but are still a ranged spell and use melee stats instead
		// i.e. hammer of wrath
		if( ability )
		{
			if( ability->NameHash == SPELL_HASH_HAMMER_OF_WRATH ) 
			{
				it = pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
				hitmodifier += pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT );
				self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL ) );
			}
			else if( ability->NameHash == SPELL_HASH_AVENGER_S_SHIELD ) 
			{
				self_skill = pr->_GetSkillLineCurrent( SKILL_DEFENSE );
			}
		}
		if(it && it->GetProto())
			SubClassSkill = GetSkillByProto(it->GetProto()->Class,it->GetProto()->SubClass);
		else
			SubClassSkill = SKILL_UNARMED;

		if(SubClassSkill==SKILL_FIST_WEAPONS) 
			SubClassSkill = SKILL_UNARMED;

		//chances in feral form don't depend on weapon skill
		if(SafePlayerCast( this )->IsInFeralForm()) 
		{
			uint8 form = SafePlayerCast( this )->GetShapeShift();
			if(form == FORM_CAT || form == FORM_BEAR || form == FORM_DIREBEAR)
			{
				SubClassSkill = SKILL_FERAL_COMBAT;
				// Adjust skill for Level * 5 for Feral Combat
				self_skill += pr->getLevel() * 5;
			}
		}


		self_skill += pr->_GetSkillLineCurrent(SubClassSkill);
	}
	else
	{
		self_skill = this->getLevel() * 5;
		if(m_objectTypeId == TYPEID_UNIT) 
		{ 
			Creature * c = SafeCreatureCast(this);
			if(c&&c->GetCreatureInfo()&&c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS)
				self_skill = std::max(self_skill,((int32)pVictim->getLevel()+3)*5);//used max to avoid situation when lowlvl hits boss.
		} 
	}
	//==========================================================================================
	//==============================Special Chances Base Calculation============================
	//==========================================================================================
	//<THE SHIT> to avoid Linux bug. 
	float diffVcapped = (float)self_skill;
	if(int32(pVictim->getLevel()*5)>victim_skill)
		diffVcapped -=(float)victim_skill;
	else
		diffVcapped -=(float)(pVictim->getLevel()*5);

	float diffAcapped = (float)victim_skill;
	if(int32(this->getLevel()*5)>self_skill)
		diffAcapped -=(float)self_skill;
	else
		diffAcapped -=(float)(this->getLevel()*5);
	//<SHIT END>

	//--------------------------------by victim state-------------------------------------------
	if(pVictim->IsPlayer()&&pVictim->GetStandState()) //every not standing state is >0
	{
		hitchance = 100.0f;
	}
	//--------------------------------by damage type and by weapon type-------------------------
	if( weapon_damage_type == RANGED ) 
	{
		dodge=0.0f;
		parry=0.0f;
	}

	//--------------------------------by skill difference---------------------------------------
	float vsk = (float)self_skill - (float)victim_skill;
	dodge = std::max( 0.0f, dodge - vsk * 0.04f );
	if( parry )
		parry = std::max( 0.0f, parry - vsk * 0.04f );
	if( block )
		block = std::max( 0.0f, block - vsk * 0.04f );

	if( vsk > 0 )
		hitchance = std::max( hitchance, 95.0f + vsk * 0.02f + hitmodifier );
	else
	{
		if( pVictim->IsPlayer() )
			hitchance = std::max( hitchance, 95.0f + vsk * 0.1f + hitmodifier ); //wowwiki multiplier - 0.04 but i think 0.1 more balanced
		else
			hitchance = std::max( hitchance, 100.0f + vsk * 0.6f + hitmodifier ); //not wowwiki but more balanced
	}

	if( ability && (ability->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) )
	{
		SM_FFValue( SM_FHitchance, &hitchance, ability->SpellGroupType );
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		float spell_flat_modifers=0;
		SM_FFValue(SM_FHitchance,&spell_flat_modifers,ability->SpellGroupType);
		if(spell_flat_modifers!=0 )
			printf("!!!!!spell resist mod flat %f,  spell resist bonus %f, spell group %u\n",spell_flat_modifers,hitchance,ability->SpellGroupType);
#endif
	}

	if( ability && ability->Attributes & ATTRIBUTES_CANT_BE_DPB )
	{
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}
	float Roll = RandomFloat(100.0f);
	float miss_chance = MAX(0.0f,100.0f-hitchance);
	float chances[4];
	chances[0]=miss_chance;
	chances[1]=chances[0]+dodge;
	chances[2]=chances[1]+parry;
	chances[3]=chances[2]+block;
	static const uint32 roll_results[5] = { SPELL_DID_HIT_MISS,SPELL_DID_HIT_DODGE,SPELL_DID_HIT_DEFLECT,SPELL_DID_HIT_BLOCK,SPELL_DID_HIT_SUCCESS };


#ifdef USE_DIMINISHING_FOR_DODGE_BLOCK_MISS_PARRY
	// apply diminishing returns 
	// not really what we want but similar
	// we actually diminish the time when the victim can avoid us. No time means we can hit him
	// wowwiki says that cap is around 80%, that means that every 3rd hit should be working on target
	// note that this is inverse thinking, attacker is eating up the dodge chance over time of a victim. Each attacker has it's own timer
	{
		uint32 rawduration,td;
		if( ability || weapon_damage_type == MELEE )
			rawduration = GetUInt32Value( UNIT_FIELD_BASEATTACKTIME );
		else
			rawduration = GetUInt32Value( UNIT_FIELD_BASEATTACKTIME_1 );
		uint32 r = 0;
		while( r<4 )
		{
			//grrr, we need to not apply diminishing when having special spell effects on us that increase chances to imba values
			if( Roll <= chances[r] )
			{
				td = rawduration;	//after X hits we should be able to hit at least once
				ApplyDiminishingReturnTimer( &td, this, DIMINISHING_GROUP_MISS_DODGE_PARRY_BLOCK );	//because it is cumulative
				if( td != 0 )
					return roll_results[r];
				else
					return SPELL_DID_HIT_SUCCESS;	//we diminished hit avoidance enough,we need to hit now
			}
			r++;
		}
		return SPELL_DID_HIT_SUCCESS;
	}
#else
	//==========================================================================================
	//==============================One Roll Processing=========================================
	//==========================================================================================
	//--------------------------------cummulative chances generation----------------------------

	//--------------------------------roll------------------------------------------------------
	uint32 r = 0;
	while (r<4&&Roll>chances[r])
	{
		r++;
	}
	return roll_results[r];
#endif
}

void Unit::Strike( Unit* pVictim, uint32 weapon_damage_type, SpellEntry* ability, int32 add_damage, int32 pct_dmg_mod, uint32 exclusive_damage, bool disable_proc, bool skip_hit_check )
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
//==========================================================================================
//==============================Unacceptable Cases Processing===============================
//==========================================================================================
	if(!pVictim->isAlive() || !isAlive()  || IsStunned() || IsPacified() || IsFeared())
	{ 
		return;
	}

	if( skip_hit_check == false && !isInFront(pVictim))
	{
		if(IsPlayer())
		{
			SafePlayerCast( this )->GetSession()->OutPacket(SMSG_ATTACKSWING_BADFACING);
			return;
		}
	}

//==========================================================================================
//==============================Variables Initialization====================================
//==========================================================================================
	dealdamage dmg			  = {0,0,0};
	
	Item * it = NULL;
	
	float hitchance          = 0.0f;
	float dodge				 = 0.0f;
	float parry				 = 0.0f;
	float glanc              = 0.0f;
	float block				 = 0.0f;
	float crit				 = 0.0f;
	float crush              = 0.0f;

	uint32 targetEvent		 = 0;
	uint32 hit_status		 = 0;

	uint32 blocked_damage	 = 0;
	int32  realdamage		 = 0;

	uint32 vstate			 = 1;
	uint32 aproc			 = 0;
	uint32 vproc			 = 0;
	   
	float hitmodifier		 = 0;
	int32 self_skill;
	int32 victim_skill;
	uint32 SubClassSkill	 = SKILL_UNARMED;

	bool backAttack			 = !pVictim->isInFront( this );
	uint32 vskill            = 0;
	bool disable_dR			 = false;
	
	if(ability)
		dmg.school_type = ability->School;
	else
	{
		if (GetTypeId() == TYPEID_UNIT)
			dmg.school_type = SafeCreatureCast( this )->BaseAttackType;
		else
			dmg.school_type = SCHOOL_NORMAL;
	}

//==========================================================================================
//==============================Victim Skill Base Calculation===============================
//==========================================================================================
	if(pVictim->IsPlayer())
	{
		Player* plr = SafePlayerCast( pVictim );
		vskill = plr->_GetSkillLineCurrent( SKILL_DEFENSE );

		if( !backAttack )
		{
			// not an attack from behind so we may dodge/parry/block

			uint32 pClass = plr->getClass();
			uint32 pLevel = (getLevel() > PLAYER_LEVEL_CAP) ? PLAYER_LEVEL_CAP : getLevel();

			if ( weapon_damage_type != RANGED )
			{
				// cannot dodge/parry ranged attacks

				if(pVictim->m_stunned<=0)
				{
					// can dodge as long as we're not stunned
					dodge = plr->GetDodgeChance();
				}

				if(pVictim->can_parry && !disarmed)
				{
					// can parry as long as we're not disarmed
					parry = plr->GetParryChance();
				}
			}
			// can block ranged attacks

			// Is an offhand equipped and is it a shield?
			Item* it2 = plr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
			if( it2 != NULL && it2->GetProto()->InventoryType == INVTYPE_SHIELD )
			{
				block = plr->GetBlockChance();
			}
		}
		victim_skill = float2int32( vskill + floorf( plr->CalcRating( PLAYER_RATING_MODIFIER_DEFENCE ) ) );
	}
//--------------------------------mob defensive chances-------------------------------------
	else
	{
		// not a player, must be a creature
		Creature* c = SafeCreatureCast( pVictim );

		// mobs can dodge attacks from behind
		if ( weapon_damage_type != RANGED && pVictim->m_stunned <= 0 )
		{
			dodge = pVictim->GetUInt32Value( UNIT_FIELD_AGILITY ) / 14.5f;
			dodge += pVictim->GetDodgeFromSpell();
		}

		if ( !backAttack )
		{
			// can parry attacks from the front
			// TODO different bosses have different parry rates (db patch?)
			if ( !disarmed ) // TODO this is wrong
			{
				parry = c->GetBaseParry();
				parry += pVictim->GetParryFromSpell();
			}

			// TODO add shield check/block chance here
			// how do we check what the creature has equipped?
		}

		victim_skill = pVictim->getLevel() * 5;
		if ( pVictim->m_objectTypeId == TYPEID_UNIT ) 
		{ 
			if ( c != NULL && c->GetCreatureInfo() && c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS )
			{
				victim_skill = std::max( victim_skill, ( (int32)getLevel() + 3 ) * 5 ); //used max to avoid situation when lowlvl hits boss.
			}
		} 
	}
	//i know i know we already set the attack timer, but let's try to make sure anyway
	//not sure if this breaks anything but seems like DK's have insane DMG for some reason. Maybe they melee strike after ability = insane DPS ?
	setAttackTimer(0,weapon_damage_type!=0);
	if( weapon_damage_type == RANGED && IsPlayer() )
		SafePlayerCast( this )->m_AutoShotAttackTimer = SafePlayerCast( this )->m_AutoShotDuration;
//==========================================================================================
//==============================Attacker Skill Base Calculation=============================
//==========================================================================================
	if( this->IsPlayer() )
	{	  
		self_skill = 0;
		Player* pr = SafePlayerCast( this );
		hitmodifier = pr->GetHitFromMeleeSpell();  
		
		switch( weapon_damage_type )
		{
		case MELEE:   // melee main hand weapon
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_MAINHAND );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_MAIN_HAND_SKILL ) );
			if (it && it->GetProto())
				dmg.school_type = it->GetProto()->Damage[0].Type;
			break;
		case OFFHAND: // melee offhand weapon (dualwield)
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_OFF_HAND_SKILL ) );
			hit_status |= HITSTATUS_DUALWIELD;//animation
			if (it && it->GetProto())
				dmg.school_type = it->GetProto()->Damage[0].Type;
			break;
		case RANGED:  // ranged weapon
			it = disarmed ? NULL : pr->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_RANGED );
			self_skill = float2int32( pr->CalcRating( PLAYER_RATING_MODIFIER_RANGED_SKILL ) );
			if (it && it->GetProto())
				dmg.school_type = it->GetProto()->Damage[0].Type;
			break;
		}

		if(it && it->GetProto())
		{
			SubClassSkill = GetSkillByProto(it->GetProto()->Class,it->GetProto()->SubClass);
			if(SubClassSkill==SKILL_FIST_WEAPONS) 
				SubClassSkill = SKILL_UNARMED;
		}
		else
			SubClassSkill = SKILL_UNARMED;


		//chances in feral form don't depend on weapon skill
		if(pr->IsInFeralForm()) 
		{
			SubClassSkill = SKILL_FERAL_COMBAT;
			self_skill += pr->getLevel() * 5;
		}

		self_skill += pr->_GetSkillLineCurrent(SubClassSkill);
		crit = GetFloatValue(PLAYER_CRIT_PERCENTAGE);
	}
	else
	{
		self_skill = this->getLevel() * 5;
		if(m_objectTypeId == TYPEID_UNIT) 
		{ 
			Creature * c = SafeCreatureCast(this);
			if(c&&c->GetCreatureInfo()&&c->GetCreatureInfo()->Rank == ELITE_WORLDBOSS)
				self_skill = std::max(self_skill,((int32)pVictim->getLevel()+3)*5);//used max to avoid situation when lowlvl hits boss.
		} 
		crit = 5.0f; //will be modified later
	}
//==========================================================================================
//==============================Special Chances Base Calculation============================
//==========================================================================================

//--------------------------------crushing blow chance--------------------------------------
	//http://www.wowwiki.com/Crushing_blow
	if (pVictim->IsPlayer() && !this->IsPlayer() && !ability && !dmg.school_type)
	{
		int32 baseDefense = SafePlayerCast(pVictim)->_GetSkillLineCurrent(SKILL_DEFENSE, false);
		int32 skillDiff = self_skill - baseDefense;
		if ( skillDiff >= 15)
			crush = -15.0f + 2.0f * skillDiff; 
		else 
			crush = 0.0f;
	}
//--------------------------------glancing blow chance--------------------------------------
	//http://www.wowwiki.com/Glancing_blow
	// did my own quick research here, seems base glancing against equal level mob is about 5%
	// and goes up 5% each level. Need to check this further.
	float diffAcapped = victim_skill - std::min((float)self_skill, getLevel() * 5.0f);

	if (this->IsPlayer() && !pVictim->IsPlayer() && !ability)
	{
		glanc = 5.0f + diffAcapped;
		if(glanc<0)
			glanc = 0.0f;
	}
//==========================================================================================
//==============================Advanced Chances Modifications==============================
//==========================================================================================
//--------------------------------by talents------------------------------------------------
	if(pVictim->IsPlayer())
	{
		if( weapon_damage_type != RANGED )
		{
			crit += SafePlayerCast(pVictim)->res_M_crit_get();
			hitmodifier += SafePlayerCast(pVictim)->m_resist_hit[ MOD_MELEE ];
		}
		else 
		{
			crit += SafePlayerCast(pVictim)->res_R_crit_get(); //this could be ability but in that case we overwrite the value
			hitmodifier += SafePlayerCast(pVictim)->m_resist_hit[ MOD_RANGED ];
		}
	}
	
	if( IsCreature() )
		crit += SafeCreatureCast(this)->crit_chance_mod;

	crit += (float)(pVictim->AttackerCritChanceMod[0]);
//--------------------------------by skill difference---------------------------------------

	float vsk = (float)(self_skill - victim_skill);
	dodge = std::max( 0.0f, dodge - vsk * 0.04f );
	if( parry )
		parry = std::max( 0.0f, parry - vsk * 0.04f );
	if( block )
		block = std::max( 0.0f, block - vsk * 0.04f );

	crit += pVictim->IsPlayer() ? vsk * 0.04f : min( vsk * 0.2f, 0.0f ); 

	// http://www.wowwiki.com/Miss
	float misschance;
	float ask = -vsk;
	if (pVictim->IsPlayer())
	{
		if (ask > 0)
			misschance = ask * 0.04f;
		else
			misschance = ask * 0.02f;
	}
	else
	{
		if (ask <= 10)
			misschance = ask * 0.1f;
		else
			misschance = 2 + (ask - 10) * 0.4f;
	}
	hitchance = 100.0f - misschance; // base miss chances are worked out further down

	if(ability && Need_SM_Apply( ability ) )
	{
		SM_FFValue(SM_CriticalChance,&crit,ability->SpellGroupType);
		SM_FFValue(SM_FHitchance,&hitchance,ability->SpellGroupType);
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		float spell_flat_modifers=0;
		SM_FFValue(SM_CriticalChance,&spell_flat_modifers,ability->SpellGroupType);
		if(spell_flat_modifers!=0)
			printf("!!!!spell critchance mod flat %f ,spell group %u\n",spell_flat_modifers,ability->SpellGroupType);
#endif
	}
//--------------------------------by ratings------------------------------------------------
	crit -= pVictim->IsPlayer() ? SafePlayerCast(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE ) * 2 : 0.0f;
	if(crit<0) 
		crit=0.0f;
	if (this->IsPlayer())
	{
		Player* plr = SafePlayerCast(this);
		hitmodifier += (weapon_damage_type == RANGED) ? plr->CalcRating( PLAYER_RATING_MODIFIER_RANGED_HIT ) : plr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT );
		dodge -= plr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT_AVOIDANCE ); // EXPERTISE will give you expertise skill, EXPERTISE2 gives you the % bonus from the rating
		if(dodge<0) dodge=0.0f;
		parry -= plr->CalcRating( PLAYER_RATING_MODIFIER_MELEE_HIT_AVOIDANCE );
		if(parry<0) parry=0.0f;
	}
	

//--------------------------------by damage type and by weapon type-------------------------
	if( weapon_damage_type == RANGED ) 
	{
		dodge=0.0f;
		parry=0.0f;
		glanc=0.0f;
	}

	if ( this->IsPlayer() )
	{
		it = SafePlayerCast( this )->GetItemInterface()->GetInventoryItem( EQUIPMENT_SLOT_OFFHAND );
		if ( !ability && it != NULL
		 && (it->GetProto()->InventoryType == INVTYPE_WEAPON || it->GetProto()->InventoryType == INVTYPE_WEAPONOFFHAND))
		{
			// offhand weapon can either be a 1 hander weapon or an offhander weapon
			hitmodifier -= 24.0f; //dualwield miss chance
		}
		else
		{
			hitmodifier -= 5.0f; // base miss chance
		}
	}
	else
	{
		// mobs base hit chance
		hitmodifier -= 5.0f;
	}

	hitchance += hitmodifier;

	//Hackfix for Surprise Attacks
	if(  this->IsPlayer() && ability && SafePlayerCast( this )->m_finishingmovesdodge && ability->c_is_flags & SPELL_FLAG_IS_FINISHING_MOVE)
			dodge = 0.0f;

	if( skip_hit_check )
	{
		hitchance = 100.0f;
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}

	if( ability != NULL && ability->Attributes & ATTRIBUTES_CANT_BE_DPB )
	{
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
	}

//--------------------------------by victim state-------------------------------------------
	if(pVictim->IsPlayer()&&pVictim->GetStandState()) //every not standing state is >0
	{
		hitchance = 100.0f;
		dodge = 0.0f;
		parry = 0.0f;
		block = 0.0f;
		crush = 0.0f;
		crit = 100.0f;
	}
	if(backAttack)
	{
		if(pVictim->IsPlayer())
		{
			//However mobs can dodge attacks from behind
			dodge = 0.0f;
		}
		parry = 0.0f;
		block = 0.0f;
	}
//==========================================================================================
//==============================One Roll Processing=========================================
//==========================================================================================
//--------------------------------cummulative chances generation----------------------------
	float miss_chance = MAX(0.0f,100.0f-hitchance);
	float Roll = RandomFloat(100.0f);
	uint32 r = 0;
	float chances[7];
	chances[0]=miss_chance;
	chances[1]=chances[0]+dodge;
	chances[2]=chances[1]+parry;
	chances[3]=chances[2]+glanc;
	chances[4]=chances[3]+block;
	chances[5]=chances[4]+crit;
	chances[6]=chances[5]+crush;
#ifdef USE_DIMINISHING_FOR_DODGE_BLOCK_MISS_PARRY
	// apply diminishing returns 
	// not really what we want but similar
	// we actually diminish the time when the victim can avoid us. No time means we can hit him
	// wowwiki says that cap is around 80%, that means that every 3rd hit should be working on target
	// note that this is inverse thinking, attacker is eating up the dodge chance over time of a victim. Each attacker has it's own timer
	{
		uint32 rawduration,td;
		if( ability || weapon_damage_type == MELEE )
			rawduration = GetUInt32Value( UNIT_FIELD_BASEATTACKTIME );
		else
			rawduration = GetUInt32Value( UNIT_FIELD_BASEATTACKTIME_1 );

		while (r<5)
		{
			if( Roll<=chances[r])
			{
				//do diminishmisses
				td = rawduration;	//after X hits we should be able to hit at least once
				ApplyDiminishingReturnTimer( &td, this, DIMINISHING_GROUP_MISS_DODGE_PARRY_BLOCK );	//because it is cumulative
				if( td != 0 )
					break;
			}
			r++;
		}
		while (r<7&&Roll>chances[r])
			r++;
	}
#else
	//printf("%s:-\n", IsPlayer() ? "Player" : "Mob");
	//printf(" miss: %.2f\n", chances[0]);
	//printf("dodge: %.2f\n", dodge);
	//printf("parry: %.2f\n", parry);
	//printf("glanc: %.2f\n", glanc);
	//printf("block: %.2f\n", block);
	//printf(" crit: %.2f\n", crit);
	//printf("crush: %.2f\n", crush);

//--------------------------------roll------------------------------------------------------
	while (r<7&&Roll>chances[r])
		r++;
#endif
//--------------------------------postroll processing---------------------------------------
	uint32 abs = 0;

	switch(r)
	{ 
//--------------------------------miss------------------------------------------------------
	case 0:
		hit_status |= HITSTATUS_MISS;
		// dirty ai agro fix
		if(pVictim->GetTypeId() == TYPEID_UNIT && pVictim->GetAIInterface()->GetNextTarget() == NULL)
			pVictim->GetAIInterface()->AttackReaction(this, 1, 0);
		break;
//--------------------------------dodge-----------------------------------------------------
	case 1:
		// dirty ai agro fix
		if(pVictim->GetTypeId() == TYPEID_UNIT && pVictim->GetAIInterface()->GetNextTarget() == NULL)
			pVictim->GetAIInterface()->AttackReaction(this, 1, 0);

		CALL_SCRIPT_EVENT(pVictim, OnTargetDodged)(this);
		CALL_SCRIPT_EVENT(this, OnDodged)(this);
		targetEvent = 1;
		vstate = DODGE;
		vproc |= PROC_ON_DODGE_VICTIM;
		pVictim->Emote(EMOTE_ONESHOT_PARRYUNARMED);			// Animation
		if( pVictim->IsPlayer() )
		{
			//allmighty warrior overpower
			if( this->IsPlayer() && SafePlayerCast( this )->getClass() == WARRIOR )
			{
				SafePlayerCast( this )->AddComboPoints( pVictim->GetGUID(), 1 );
				SafePlayerCast( this )->UpdateComboPoints();
				if( !sEventMgr.HasEvent( SafePlayerCast( this ), EVENT_COMBO_POINT_CLEAR_FOR_TARGET ) )
					sEventMgr.AddEvent( SafePlayerCast( this ), &Player::NullComboPoints, (uint32)EVENT_COMBO_POINT_CLEAR_FOR_TARGET, (uint32)5000, (uint32)1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
				else
					sEventMgr.ModifyEventTimeLeft( SafePlayerCast( this ), EVENT_COMBO_POINT_CLEAR_FOR_TARGET, 5000 );
			}
			pVictim->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_DODGE_BLOCK);	//SB@L: Enables spells requiring dodge
			if(!sEventMgr.HasEvent(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE))
				sEventMgr.AddEvent(pVictim,&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_DODGE_BLOCK,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000,1,0);
			else 
				sEventMgr.ModifyEventTimeLeft(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000);
		}
		break;
//--------------------------------parry-----------------------------------------------------
	case 2:
		// dirty ai agro fix
		if(pVictim->GetTypeId() == TYPEID_UNIT && pVictim->GetAIInterface()->GetNextTarget() == NULL)
			pVictim->GetAIInterface()->AttackReaction(this, 1, 0);

		CALL_SCRIPT_EVENT(pVictim, OnTargetParried)(this);
		CALL_SCRIPT_EVENT(this, OnParried)(this);
		targetEvent = 3;
		vstate = PARRY;
		vproc |= PROC_ON_DODGE_VICTIM;	//hmm, we should have special parry proc flag but as i seen these 2 go in same handler
		pVictim->Emote(EMOTE_ONESHOT_PARRYUNARMED);			// Animation
		if(pVictim->IsPlayer())
		{
			pVictim->SetFlag( UNIT_FIELD_AURASTATE,AURASTATE_FLAG_PARRY );	//SB@L: Enables spells requiring parry
			if(!sEventMgr.HasEvent( pVictim, EVENT_PARRY_FLAG_EXPIRE ) )
				sEventMgr.AddEvent( pVictim, &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_PARRY,EVENT_PARRY_FLAG_EXPIRE, 5000, 1, 0 );
			else 
				sEventMgr.ModifyEventTimeLeft( pVictim, EVENT_PARRY_FLAG_EXPIRE, 5000 );
			if( SafePlayerCast( pVictim )->getClass() == 1 || SafePlayerCast( pVictim )->getClass() == 4 )//warriors for 'revenge' and rogues for 'riposte'
			{
				pVictim->SetFlag( UNIT_FIELD_AURASTATE,AURASTATE_FLAG_DODGE_BLOCK );	//SB@L: Enables spells requiring dodge
				if(!sEventMgr.HasEvent( pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE ) )
					sEventMgr.AddEvent( pVictim, &Unit::EventAurastateExpire, (uint32)AURASTATE_FLAG_DODGE_BLOCK, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000, 1, 0 );
				else 
					sEventMgr.ModifyEventTimeLeft( pVictim, EVENT_DODGE_BLOCK_FLAG_EXPIRE, 5000 );
			}
		}
		break;
//--------------------------------not miss,dodge or parry-----------------------------------
	default:
		hit_status |= HITSTATUS_HITANIMATION;//hit animation on victim
		if( pVictim->SchoolImmunityList[ SCHOOL_NORMAL ] )
		{
			vstate = IMMUNE;		
			dmg.resisted_damage = dmg.full_damage = realdamage = 0;	//i know we already set these. But morron protection can never hurt
		}
		else
	{
//--------------------------------state proc initialization---------------------------------
			vproc |= PROC_ON_ANY_DAMAGE_VICTIM;			
			if( weapon_damage_type != RANGED )
			{
				aproc |= PROC_ON_MELEE_ATTACK;
				vproc |= PROC_ON_MELEE_ATTACK_VICTIM;
			}
			else
			{
				aproc |= PROC_ON_RANGED_ATTACK;
				vproc |= PROC_ON_RANGED_ATTACK_VICTIM;
//				if(ability && ability->Id==3018 && IsPlayer() && getClass()==HUNTER)
//					aproc |= PROC_ON_AUTO_SHOT_HIT;
			}
//--------------------------------base damage calculation-----------------------------------
			dmg_storage_struct tdmg;
			tdmg.base_min = tdmg.base_max = 0;
			tdmg.flat_mod_add = 0;
			tdmg.pct_mod_add = 0;
			if(exclusive_damage)
				tdmg.base_min = tdmg.base_max = exclusive_damage;
			else
			{
				if( weapon_damage_type == MELEE && ability )
					CalculateDamage( this, pVictim, MELEE, ability->SpellGroupType, ability, tdmg );
				else			
					CalculateDamage( this, pVictim, weapon_damage_type, 0, ability, tdmg );
			}

			if(ability && Need_SM_Apply( ability ))
			{	
//				SM_FIValue(((Unit*)this)->SM_FDamageBonus,&dmg.full_damage,ability->SpellGroupType);
//				SM_PIValue(((Unit*)this)->SM_PDamageBonus,&dmg.full_damage,ability->SpellGroupType);
				SM_FIValue(((Unit*)this)->SM_FDamageBonus,&tdmg.flat_mod_add,ability->SpellGroupType);
				SM_FIValue(((Unit*)this)->SM_PDamageBonus,&tdmg.pct_mod_add,ability->SpellGroupType);
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
				int spell_flat_modifers=0;
				int spell_pct_modifers=0;
				SM_FIValue(((Unit*)this)->SM_FDamageBonus,&spell_flat_modifers,ability->SpellGroupType);
				SM_FIValue(((Unit*)this)->SM_PDamageBonus,&spell_pct_modifers,ability->SpellGroupType);
				if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
					printf("!!!!!spell dmg bonus mod flat %d , spell dmg bonus pct %d , spell dmg bonus %d, spell group %u\n",spell_flat_modifers,spell_pct_modifers,dmg.full_damage,ability->SpellGroupType);
#endif
			}
			tdmg.flat_mod_add += pVictim->DamageTakenMod[dmg.school_type];
			if( weapon_damage_type == RANGED )
			{
				tdmg.flat_mod_add += pVictim->RangedDamageTaken;
			}
			
			if( ability && ability->MechanicsType == MECHANIC_BLEEDING )
				disable_dR = true; 
			
//			if( pct_dmg_mod > 0 )
				tdmg.pct_mod_add += pct_dmg_mod;

			tdmg.flat_mod_add += add_damage;	//add damage is extra for spells like scourgestrike : does 40% weapon dmg + x

			tdmg.pct_mod_add += float2int32( pVictim->DamageTakenPctMod[ dmg.school_type ] * 100.0f);
			tdmg.pct_mod_add += float2int32((GetDamageDonePctMod(dmg.school_type)-1) * 100.0f);

//			if( dmg.school_type != SCHOOL_NORMAL )
//				tdmg.pct_mod_add += float2int32((GetDamageDonePctMod( dmg.school_type ) - 1) * 100.0f);

			if( ability != NULL 
//				&& ability->NameHash == SPELL_HASH_SHRED 
				)
			{
				tdmg.pct_mod_add += float2int32(pVictim->ModDamageTakenByMechCoef[MECHANIC_BLEEDING]);
				tdmg.flat_mod_add += pVictim->ModDamageTakenByMechFlat[MECHANIC_BLEEDING];
			}

			//pet happiness state dmg modifier
			if( IsPet() && !SafePetCast(this)->IsSummon() )
			{
//				dmg.full_damage = ( dmg.full_damage <= 0 ) ? 0 : float2int32( dmg.full_damage * SafePetCast( this )->GetHappinessDmgMod() );
				tdmg.pct_mod_add += float2int32( SafePetCast( this )->GetHappinessDmgMod() * 100.0f);
			}

			//should pct mod mod flat mod ? Not sure about this formula, but pct mods sould not mod each other for sure.
			int32 dmg_diff = tdmg.base_max - tdmg.base_min;
			dmg_diff = MAX( 1, dmg_diff );
			dmg.full_damage = tdmg.base_min + ( RandomUInt() % dmg_diff );
			dmg.full_damage += dmg.full_damage * tdmg.pct_mod_add / 100;
			dmg.full_damage += tdmg.flat_mod_add;

			if(dmg.full_damage < 0)
				dmg.full_damage = 0;
//--------------------------------check for special hits------------------------------------
			switch(r)
			{
//--------------------------------glancing blow---------------------------------------------
			case 3:
				{
					float low_dmg_mod = 1.5f - (0.05f * diffAcapped);
					if(this->getClass() == MAGE || this->getClass() == PRIEST || this->getClass() == WARLOCK) //casters = additional penalty.
					{
						low_dmg_mod -= 0.7f;
					}
					if(low_dmg_mod<0.01)
						low_dmg_mod = 0.01f;
					if(low_dmg_mod>0.91)
						low_dmg_mod = 0.91f;
					float high_dmg_mod = 1.2f - (0.03f * diffAcapped);
					if(this->getClass() == MAGE || this->getClass() == PRIEST || this->getClass() == WARLOCK) //casters = additional penalty.
					{
						high_dmg_mod -= 0.3f;
					}
					if(high_dmg_mod>0.99)
						high_dmg_mod = 0.99f;
					if(high_dmg_mod<0.2)
						high_dmg_mod = 0.2f;

					float damage_reduction = (high_dmg_mod + low_dmg_mod) / 2.0f;
					if(damage_reduction > 0)
					{
							dmg.full_damage = float2int32(damage_reduction * float(dmg.full_damage));
					}
					hit_status |= HITSTATUS_GLANCING;
				}
				break;
//--------------------------------block-----------------------------------------------------
			case 4:
				{
					Item* shield = SafePlayerCast( pVictim )->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_OFFHAND);
					if( shield != NULL )
					{
						targetEvent = 2;
						pVictim->Emote(EMOTE_ONESHOT_PARRYSHIELD);// Animation

						if( shield->GetProto()->InventoryType == INVTYPE_SHIELD )
						{
//							uint32 block_multiplier = 100 + SafePlayerCast( pVictim )->m_modblockabsorbvaluePCT;
//							if( block_multiplier < 100 )
//								block_multiplier = 100;
//							blocked_damage = float2int32( shield->GetProto()->Block + SafePlayerCast( pVictim )->m_modblockvaluefromspells + pVictim->GetUInt32Value( PLAYER_RATING_MODIFIER_BLOCK ) )) + pVictim->GetUInt32Value( UNIT_FIELD_STAT0 ) / 2 )) ) * block_multiplier);
//							blocked_damage = ( shield->GetProto()->Block + SafePlayerCast( pVictim )->m_modblockvaluefromspells + pVictim->GetUInt32Value( UNIT_FIELD_STAT0 ) / 2 ) * block_multiplier);
							blocked_damage = pVictim->GetUInt32Value( PLAYER_SHIELD_BLOCK );
						}
						else
						{
							blocked_damage = 0;
						}

						if(dmg.full_damage <= (int32)blocked_damage)
							vstate = BLOCK;
						if( blocked_damage )
						{
							CALL_SCRIPT_EVENT(pVictim, OnTargetBlocked)(this, blocked_damage);
							CALL_SCRIPT_EVENT(this, OnBlocked)(pVictim, blocked_damage);
							vproc |= PROC_ON_BLOCK_VICTIM;
						}
						if( pVictim->IsPlayer() )//not necessary now but we'll have blocking mobs in future
						{            
							pVictim->SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_DODGE_BLOCK);	//SB@L: Enables spells requiring dodge
							if(!sEventMgr.HasEvent(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE))
								sEventMgr.AddEvent(pVictim,&Unit::EventAurastateExpire,(uint32)AURASTATE_FLAG_DODGE_BLOCK,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000,1,0);
							else 
								sEventMgr.ModifyEventTimeLeft(pVictim,EVENT_DODGE_BLOCK_FLAG_EXPIRE,5000);
						}
					}
				}
				break;
//--------------------------------critical hit----------------------------------------------
			case 5:
			{
					hit_status |= HITSTATUS_CRICTICAL;
					int32 dmgbonus;
					if( weapon_damage_type != RANGED )
						dmgbonus = dmg.full_damage / 2;	//150% dmg
					else
						dmgbonus = dmg.full_damage;	//200% dmg
					//sLog.outString( "DEBUG: Critical Strike! Full_damage: %u" , dmg.full_damage );
					if(ability && Need_SM_Apply( ability ) )
					{
						int32 dmg_bonus_pct = 100;
						SM_FIValue(SM_PCriticalDamage,&dmg_bonus_pct,ability->SpellGroupType);
						dmgbonus = float2int32( float(dmgbonus) * (float(dmg_bonus_pct)/100.0f) );
					}
					
					//sLog.outString( "DEBUG: After CritMeleeDamageTakenPctMod: %u" , dmg.full_damage );
					if(IsPlayer())
					{
						if( weapon_damage_type != RANGED )
						{
							float critextra=float(SafePlayerCast( this )->m_modphyscritdmgPCT);
							dmg.full_damage += int32((float(dmg.full_damage)*critextra/100.0f));
						}
						if(!pVictim->IsPlayer())
							dmg.full_damage += float2int32(dmg.full_damage*SafePlayerCast( this )->IncreaseCricticalByTypePCT[(SafeCreatureCast(pVictim))->GetCreatureInfo() ? (SafeCreatureCast(pVictim))->GetCreatureInfo()->Type : 0]);
					//sLog.outString( "DEBUG: After IncreaseCricticalByTypePCT: %u" , dmg.full_damage );
					}

					dmg.full_damage += dmgbonus;

					if( weapon_damage_type == RANGED )
						dmg.full_damage = dmg.full_damage - float2int32(dmg.full_damage * CritRangedDamageTakenPctMod[dmg.school_type]);
					else 
						dmg.full_damage = dmg.full_damage - float2int32(dmg.full_damage * CritMeleeDamageTakenPctMod[dmg.school_type]);

					if(pVictim->IsPlayer())
					{
						//Resilience is a special new rating which was created to reduce the effects of critical hits against your character.
						float dmg_reduction_pct = 2.2f * SafePlayerCast(pVictim)->CalcRating( PLAYER_RATING_MODIFIER_MELEE_CRIT_RESILIENCE ) / 100.0f;
						if( dmg_reduction_pct > 0.8f )
							dmg_reduction_pct = 0.8f; //we cannot resist more then he is criticalling us, there is no point of the critical then :P
						dmg.full_damage = float2int32( dmg.full_damage - dmg.full_damage*dmg_reduction_pct );
						//sLog.outString( "DEBUG: After Resilience check: %u" , dmg.full_damage );
					}
					
					if (pVictim->GetTypeId() == TYPEID_UNIT && SafeCreatureCast(pVictim)->GetCreatureInfo() && SafeCreatureCast(pVictim)->GetCreatureInfo()->Rank != ELITE_WORLDBOSS)
						pVictim->Emote( EMOTE_ONESHOT_WOUNDCRITICAL );
					vproc |= PROC_ON_CRIT_HIT_VICTIM;
					aproc |= PROC_ON_CRIT_ATTACK;
					if( weapon_damage_type == RANGED )
					{
						vproc |= PROC_ON_RANGED_CRIT_ATTACK_VICTIM;
						aproc |= PROC_ON_RANGED_CRIT_ATTACK;
					}

					if( IsPlayer() )
					{
						uint32 toset = AURASTATE_FLAG_CRITICAL;
						this->SetFlag( UNIT_FIELD_AURASTATE, toset );
						if( !sEventMgr.HasEvent( this, EVENT_CRIT_FLAG_EXPIRE ) )
							sEventMgr.AddEvent( this, &Unit::EventAurastateExpire, toset , EVENT_CRIT_FLAG_EXPIRE, 5000, 1, 0 );
						else sEventMgr.ModifyEventTimeLeft( this, EVENT_CRIT_FLAG_EXPIRE, 5000 );
					}

					CALL_SCRIPT_EVENT(pVictim, OnTargetCritHit)(this, float(dmg.full_damage));
					CALL_SCRIPT_EVENT(this, OnCritHit)(pVictim, float(dmg.full_damage));
				}
				break;
//--------------------------------crushing blow---------------------------------------------
			case 6:
				hit_status |= HITSTATUS_CRUSHINGBLOW;
				dmg.full_damage = (dmg.full_damage * 3) >> 1;
				break;
//--------------------------------regular hit-----------------------------------------------
			default:
				break;	
			}
//==========================================================================================
//==============================Post Roll Damage Processing=================================
//==========================================================================================
//--------------------------absorption------------------------------------------------------
			uint32 dm = dmg.full_damage;
			abs = pVictim->AbsorbDamage(dmg.school_type,(uint32*)&dm);
		
			if(dmg.full_damage > (int32)blocked_damage)
			{
			
				uint32 sh = pVictim->ManaShieldAbsorb(dmg.full_damage);
//--------------------------armor reducing--------------------------------------------------
				if(sh)
				{
					dmg.full_damage -= sh;
					if(dmg.full_damage && !disable_dR)
						CalculateResistanceReduction(pVictim,&dmg, ability);
					dmg.full_damage += sh;
					abs+=sh;
				}
				else if(!disable_dR)
					CalculateResistanceReduction(pVictim,&dmg, ability);	
			}

			if(abs)
				vproc |= PROC_ON_ABSORB;

			if (dmg.school_type == SCHOOL_NORMAL)
			{
				abs+=dmg.resisted_damage;
				dmg.resisted_damage=0;
			}

			realdamage = dmg.full_damage-abs-dmg.resisted_damage-blocked_damage;
			if(realdamage < 0)
			{
				realdamage = 0;
				vstate = IMMUNE;
				hit_status |= HITSTATUS_BLOCK;//ABSORBED;
			}
		}
		break;
	}

//==========================================================================================
//==============================Post Roll Special Cases Processing==========================
//==========================================================================================
//------------------------------- Special Effects Processing
	// Paladin: Blessing of Sacrifice, and Warlock: Soul Link
	if( pVictim->m_damageSplitTarget )
	{
//		dmg.full_damage = pVictim->DoDamageSplitTarget(dmg.full_damage, dmg.school_type, true);
//		realdamage = dmg.full_damage;
		//zack : why remove spell efects impact ?
		realdamage = pVictim->DoDamageSplitTarget(realdamage, dmg.school_type, true);
	}

	//--------------------------special states processing---------------------------------------
	if(pVictim->GetTypeId() == TYPEID_UNIT)
	{
		if(pVictim->GetAIInterface() && (pVictim->GetAIInterface()->getAIState()== STATE_EVADE ||
										(pVictim->GetAIInterface()->GetIsSoulLinked() && pVictim->GetAIInterface()->getSoullinkedWith() != this)))
		{
			vstate = EVADE;
			realdamage = 0;
			dmg.full_damage = 0;
			dmg.resisted_damage = 0;
		}
	}
	if(pVictim->bInvincible == true)
	{
		dmg.resisted_damage = dmg.full_damage; //godmode
	}
//--------------------------dirty fixes-----------------------------------------------------
	//vstate=1-wound,2-dodge,3-parry,4-interrupt,5-block,6-evade,7-immune,8-deflect	
	// the above code was remade it for reasons : damage shield needs moslty same flags as handleproc + dual wield should proc too ?
	if (ability && ability->noproc)
	{
		disable_proc = true;
	}
	if( !disable_proc && weapon_damage_type != OFFHAND )
	{
		int32 resisted_dmg;

		//damage shield must come before handleproc to not loose 1 charge : speel gets removed before last charge
		if( realdamage > 0 || vproc & PROC_ON_BLOCK_VICTIM )
		{
			pVictim->HandleProcDmgShield(vproc,this);
			HandleProcDmgShield(aproc,pVictim);
		}
		this->HandleProc(aproc,pVictim, ability,realdamage,abs); //maybe using dmg.resisted_damage is better sometimes but then if using godmode dmg is resisted instead of absorbed....bad

		if( realdamage > 0 )
			vproc |= PROC_ON_ANY_DAMAGE_VICTIM;

		resisted_dmg = pVictim->HandleProc(vproc,this, ability,realdamage,abs);

		if (resisted_dmg)
		{
//			dmg.resisted_damage+= resisted_dmg;
			abs += resisted_dmg;	//using as temporary until figure out properlogs :(
//			dmg.full_damage -= resisted_dmg;
			if( realdamage < resisted_dmg )
				realdamage = 0;
			else
				realdamage -= resisted_dmg;
		}
	}
//--------------------------spells triggering-----------------------------------------------
	if(realdamage > 0 && ability == 0)
	{
		if( IsPlayer() && SafePlayerCast( this )->m_onStrikeSpells.size() )
		{
			SpellCastTargets targets;
			targets.m_unitTarget = pVictim->GetGUID();
			targets.m_targetMask = 0x2;
			Spell* cspell;

			// Loop on hit spells, and strike with those.
			for( map< SpellEntry*, pair< uint32, uint32 > >::iterator itr = SafePlayerCast( this )->m_onStrikeSpells.begin();
				itr != SafePlayerCast( this )->m_onStrikeSpells.end(); ++itr )
			{
				if( itr->second.first )
				{
					// We have a *periodic* delayed spell.
					uint32 t = getMSTime();
					if( t > itr->second.second )  // Time expired
					{
						// Set new time
						itr->second.second = t + itr->second.first;
					}

					// Cast.
					cspell = SpellPool.PooledNew();
					cspell->Init(this, itr->first, true, NULL);
					cspell->prepare(&targets);
				}
				else
				{
					cspell = SpellPool.PooledNew();
					cspell->Init(this, itr->first, true, NULL);
					cspell->prepare(&targets);
				}			
			}
		}

		if( IsPlayer() && SafePlayerCast( this )->m_onStrikeSpellDmg.size() )
		{
			map< uint32, OnHitSpell >::iterator it2 = SafePlayerCast( this )->m_onStrikeSpellDmg.begin();
			map< uint32, OnHitSpell >::iterator itr;
			uint32 min_dmg, max_dmg, range, dmg2;
			for(; it2 != SafePlayerCast( this )->m_onStrikeSpellDmg.end(); )
			{
				itr = it2;
				++it2;

				min_dmg = itr->second.mindmg;
				max_dmg = itr->second.maxdmg;
				range = min_dmg - max_dmg;
				dmg2 = min_dmg;
				if(range) range += RandomUInt(range);

				SpellNonMeleeDamageLog(pVictim, itr->second.spellid, dmg2, true);
			}
		}

		// refresh judgements
		Aura *taur=NULL;
		for( uint32 x = FIRST_AURA_SLOT; x < MAX_NEGATIVE_AURAS1(pVictim); x++ )
		{
			taur = pVictim->m_auras[x];
			if( taur != NULL && taur->GetUnitCaster() != NULL && taur->GetUnitCaster()->GetGUID() == GetGUID() && taur->GetSpellProto()->BGR_one_buff_from_caster_on_1target == SPELL_TYPE_INDEX_JUDGEMENT )
			{
				taur->ResetTimeLeft();
				sEventMgr.ModifyEventTimeLeft(taur, EVENT_AURA_REMOVE, taur->GetDuration());
				pVictim->ModVisualAuraStackCount(taur, 0);
			}
		}
	}
	
//==========================================================================================
//==============================Data Sending================================================
//==========================================================================================
	if( !ability )
	{
		if( dmg.full_damage > 0 )
		{
			if( dmg.full_damage <= (int32)abs )
				hit_status |= HITSTATUS_ABSORBED;
			else if (dmg.full_damage <= (int32)dmg.resisted_damage)
			{
				hit_status |= HITSTATUS_RESIST;
				dmg.resisted_damage = dmg.full_damage;
			}
		}

		if( dmg.full_damage < 0 )
			dmg.full_damage = 0;

		if( realdamage < 0 )
			realdamage = 0;

		SendAttackerStateUpdate(this, pVictim, &dmg, realdamage, abs, blocked_damage, hit_status, vstate);
	}
	else
	{
		if( realdamage > 0 )//FIXME: add log for miss,block etc for ability and ranged
		{
			// here we send "dmg.resisted_damage" for "AbsorbedDamage", "0" for "ResistedDamage", and "false" for "PhysicalDamage" even though "School" is "SCHOOL_NORMAL"   o_O
			if( ability->spell_id_client )
				SendSpellNonMeleeDamageLog( this, pVictim, ability->spell_id_client, realdamage, dmg.school_type, dmg.resisted_damage, 0, false, blocked_damage, ( ( hit_status & HITSTATUS_CRICTICAL ) != 0 ), true );
			else
				SendSpellNonMeleeDamageLog( this, pVictim, ability->Id, realdamage, dmg.school_type, dmg.resisted_damage, 0, false, blocked_damage, ( ( hit_status & HITSTATUS_CRICTICAL ) != 0 ), true );
		}
		else if(realdamage==0)
		{	
			SendSpellLog(this,pVictim,ability->Id,SPELL_LOG_RESIST);
		}
		//FIXME: add log for miss,block etc for ability and ranged
		//example how it works
		//SendSpellLog(this,pVictim,ability->Id,SPELL_LOG_MISS);
	}

//==========================================================================================
//==============================Damage Dealing==============================================
//==========================================================================================

	if(realdamage)
	{
		DealDamage(pVictim, realdamage, 0, targetEvent, 0);
		//pVictim->HandleProcDmgShield(PROC_ON_MELEE_ATTACK_VICTIM,this);
//		HandleProcDmgShield(PROC_ON_MELEE_ATTACK_VICTIM,pVictim);

		if(pVictim->GetCurrentSpell())
			pVictim->GetCurrentSpell()->AddTime(0);
	}
	else
	{		
		// have to set attack target here otherwise it wont be set
		// because dealdamage is not called.
		// setAttackTarget(pVictim);
		this->CombatStatus.OnDamageDealt( pVictim );
	}
//==========================================================================================
//==============================Post Damage Dealing Processing==============================
//==========================================================================================
//--------------------------durability processing-------------------------------------------
	if(pVictim->IsPlayer())
	{
		SafePlayerCast( pVictim )->GetItemInterface()->ReduceItemDurability();
		if( !this->IsPlayer() )
		{
			Player *pr = SafePlayerCast( pVictim );
			if( Rand( pr->GetSkillUpChance( SKILL_DEFENSE ) * sWorld.getRate( RATE_SKILLCHANCE ) ) )
			{
				pr->_AdvanceSkillLine( SKILL_DEFENSE, float2int32( 1.0f * sWorld.getRate(RATE_SKILLRATE)));
				pr->UpdateChances();
			}
		}
		else
		{
			 SafePlayerCast( this )->GetItemInterface()->ReduceItemDurability();
		}
	}
	else
	{
		if(this->IsPlayer())//not pvp
		{
			SafePlayerCast( this )->GetItemInterface()->ReduceItemDurability();
			Player* pr = SafePlayerCast( this );
			if( Rand( pr->GetSkillUpChance( SubClassSkill) * sWorld.getRate( RATE_SKILLCHANCE ) ) )
			{
				pr->_AdvanceSkillLine( SubClassSkill, float2int32( 1.0f * sWorld.getRate(RATE_SKILLRATE)));
				//pr->UpdateChances();
			}
		}
	}
	//--------------------------rage processing-------------------------------------------------
	//http://www.wowwiki.com/Formulas:Rage_generation

	if( dmg.full_damage && IsPlayer() && GetPowerType() == POWER_TYPE_RAGE && !ability)
	{
		float val;
		uint32 level = getLevel();
		float conv;
		if( level <= PLAYER_LEVEL_CAP )
			conv = AttackToRageConversionTable[ level ];
		else 
			conv = 3.75f / (0.0091107836f * level * level + 3.225598133f * level + 4.2652911f);

		// Hit Factor
		float f = ( weapon_damage_type == OFFHAND ) ? 1.75f : 3.5f;

		if( hit_status & HITSTATUS_CRICTICAL )
			f *= 2.0f;

		float s = 1.0f;

		// Weapon speed (normal)
		Item* weapon = ( SafePlayerCast( this )->GetItemInterface())->GetInventoryItem( INVENTORY_SLOT_NOT_SET, ( weapon_damage_type == OFFHAND ? EQUIPMENT_SLOT_OFFHAND : EQUIPMENT_SLOT_MAINHAND ) );
		if( weapon == NULL )
		{
			if( weapon_damage_type == OFFHAND )
				s = GetUInt32Value( UNIT_FIELD_BASEATTACKTIME_1 ) / 1000.0f;
			else
				s = GetUInt32Value( UNIT_FIELD_BASEATTACKTIME ) / 1000.0f;
		}
		else
		{
			uint32 entry = weapon->GetEntry();
			ItemPrototype* pProto = ItemPrototypeStorage.LookupEntry( entry );
			if( pProto != NULL )
			{
				s = pProto->Delay / 1000.0f;
			}
		}

		val = conv * dmg.full_damage + f * s / 2.0f;
		val *= ( 1 + ( SafePlayerCast( this )->rageFromDamageDealt / 100.0f ) );
		val *= 10;

		//float r = ( 7.5f * dmg.full_damage / c + f * s ) / 2.0f;
		//float p = ( 1 + ( SafePlayerCast( this )->rageFromDamageDealt / 100.0f ) );
		//sLog.outDebug( "Rd(%i) d(%i) c(%f) f(%f) s(%f) p(%f) r(%f) rage = %f", realdamage, dmg.full_damage, c, f, s, p, r, val );

		ModUnsigned32Value( UNIT_FIELD_POWER2, (int32)val );
		if( GetUInt32Value( UNIT_FIELD_POWER2 ) > 1000 )
			ModUnsigned32Value( UNIT_FIELD_POWER2, 1000 - GetUInt32Value( UNIT_FIELD_POWER2 ) );
		UpdatePowerAmm();

	}

	// I am receiving damage!
	if( dmg.full_damage && pVictim->IsPlayer() && pVictim->GetPowerType() == POWER_TYPE_RAGE && pVictim->CombatStatus.IsInCombat() )
	{
		float val;
		float level = (float)getLevel();

		// Conversion Value
		float c = 0.0091107836f * level * level + 3.225598133f * level + 4.2652911f;

		val = 2.5f * dmg.full_damage / c;

		// Berserker Rage Effect + 35% rage when taking damage by Aziel
		if ( pVictim->HasActiveAura(18499) )
			val *= 1.35f;

		val *= 10;

		//sLog.outDebug( "Rd(%i) d(%i) c(%f) rage = %f", realdamage, dmg.full_damage, c, val );

		pVictim->ModUnsigned32Value( UNIT_FIELD_POWER2, (int32)val );
		if( pVictim->GetUInt32Value( UNIT_FIELD_POWER2) > 1000 )
			pVictim->ModUnsigned32Value( UNIT_FIELD_POWER2, 1000 - pVictim->GetUInt32Value( UNIT_FIELD_POWER2 ) );
		UpdatePowerAmm();

	}
		
	RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_START_ATTACK);
//--------------------------extra strikes processing----------------------------------------
	if(!m_extraAttackCounter_lock)
	{
		m_extraAttackCounter_lock = true;
	
		uint32 time_now = getMSTime();
		m_extra_attacks.BeginLoop();
		for(CommitPointerListNode<ExtraAttack> *itr = m_extra_attacks.begin();itr != m_extra_attacks.end();itr = itr->Next() )
		{
			ExtraAttack *i = itr->data;
			if( i->count && i->next_proc_stamp <  time_now )
			{
				//this might get changed when we strike !
				i->count--;

				Strike( pVictim, i->dmg_type, i->sp, i->add_dmg, i->pct_dmg_mod, 0, false, false);

				i->next_proc_stamp = time_now + i->sp->proc_interval;
			}
		}
		m_extra_attacks.EndLoopAndCommit();
		m_extraAttackCounter_lock = false;
	}

	if(m_extrastriketargetc > 0 && m_extrastriketarget == 0)
	{
		m_extrastriketarget = 1;

		m_extraStrikeTargets.BeginLoop();
		for(CommitPointerListNode<ExtraStrike> *itx = m_extraStrikeTargets.begin();itx != m_extraStrikeTargets.end(); itx = itx->Next() )
		{
			ExtraStrike *ex = itx->data;

			if (ex->deleted) 
				continue;

			for(set<Object*>::iterator itr = m_objectsInRange.begin(); itr != m_objectsInRange.end(); ++itr)
			{
				if (!(*itr) || (*itr) == pVictim || !(*itr)->IsUnit())
					continue;

				if(GetDistanceSq(*itr) < (3.0f*3.0f) && isAttackable(this, (*itr)) && (*itr)->isInFront(this) && !SafeUnitCast((*itr))->IsPacified())
				{
					// Sweeping Strikes hits cannot be dodged, missed or parried (from wowhead)
					bool skip_hit_check2 = ex->spell_info->Id == 12328 ? true : false;
					//zack : should we use the spell id the registered this extra strike when striking ? It would solve a few proc on proc problems if so ;)
//					Strike( SafeUnitCast( *itr ), weapon_damage_type, ability, add_damage, pct_dmg_mod, exclusive_damage, false, skip_hit_check );
					Strike( SafeUnitCast( *itr ), weapon_damage_type, ex->spell_info, add_damage, pct_dmg_mod, exclusive_damage, false, skip_hit_check2 );
					break;
				}
			}

			// Sweeping Strikes charges are used up regardless whether there is a secondary target in range or not. (from wowhead)
			if (ex->charges > 0)
			{
				ex->charges--;
				if (ex->charges <= 0)
				{
					ex->deleted = true;
					m_extrastriketargetc--;
				}
			}
		}
		m_extraStrikeTargets.EndLoopAndCommit();

		m_extrastriketarget = 0;
	}
}	

void Unit::smsg_AttackStop(Unit* pVictim)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(!pVictim)
	{ 
		return;
	}

	sStackWolrdPacket( data, SMSG_ATTACKSTOP, 50 );
	if( IsPlayer() )
	{
		data << pVictim->GetNewGUID();
		data << uint8(0);
		data << uint32(0);
		SafePlayerCast( this )->GetSession()->SendPacket( &data );
		data.Initialize( SMSG_ATTACKSTOP );
	}

	data << GetNewGUID();
	data << pVictim->GetNewGUID();
	data << uint32(0);
	SendMessageToSet(&data, true );
	// stop swinging, reset pvp timeout

	if( pVictim->IsPlayer() )
	{
		pVictim->CombatStatusHandler_ResetPvPTimeout();
		CombatStatusHandler_ResetPvPTimeout();
	}
	else
	{
		if( !IsPlayer() || getClass() == ROGUE )
		{
			m_cTimer = getMSTime() + 5000;
			sEventMgr.RemoveEvents( this, EVENT_COMBAT_TIMER ); 
			sEventMgr.AddEvent( this, &Unit::EventUpdateFlag, EVENT_COMBAT_TIMER, 5000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
			if( pVictim->IsUnit() ) // there could be damage coming from objects/enviromental
				sEventMgr.AddEvent( pVictim, &Unit::EventUpdateFlag, EVENT_COMBAT_TIMER, 5000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );		}
		else
		{
			pVictim->CombatStatus.RemoveAttacker( this, GetGUID() );
			CombatStatus.RemoveAttackTarget( pVictim );
		}
	}
}

void Unit::smsg_AttackStop(const uint64 &victimGuid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	sStackWolrdPacket( data, SMSG_ATTACKSTOP , 50);
	data << GetNewGUID();
	FastGUIDPack(data, victimGuid);
	data << uint32( 0 );
	SendMessageToSet(&data, IsPlayer());
}

void Unit::smsg_AttackStart(Unit* pVictim)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
    // Prevent user from ignoring attack speed and stopping and start combat really really fast
    /*if(!isAttackReady())
        setAttackTimer(uint32(0));
    else if(!canReachWithAttack(pVictim))
    {
        setAttackTimer(uint32(500));
        //pThis->GetSession()->OutPacket(SMSG_ATTACKSWING_NOTINRANGE);
    }
    else if(!isInFront(pVictim))
    {
        setAttackTimer(uint32(500));
        //pThis->GetSession()->OutPacket(SMSG_ATTACKSWING_NOTINRANGE);
    }*/

    // Send out ATTACKSTART
    sStackWolrdPacket( data,SMSG_ATTACKSTART, 20 );
    data << GetGUID();
    data << pVictim->GetGUID();
//    SendMessageToSet(&data, true);
    SendMessageToSet(&data, false);
    sLog.outDebug( "WORLD: Sent SMSG_ATTACKSTART" );

    // FLAGS changed so other players see attack animation
    //    addUnitFlag(UNIT_FLAG_COMBAT);
    //    setUpdateMaskBit(UNIT_FIELD_FLAGS );
    if(GetTypeId() == TYPEID_PLAYER)
    {
        Player* pThis = SafePlayerCast( this );
        if( pThis->cannibalize)
        {
            sEventMgr.RemoveEvents(pThis, EVENT_CANNIBALIZE);
            pThis->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
            pThis->cannibalize = false;
        }
    }
}

uint16	Unit::FindVisualSlot(Aura *a,bool IsPos)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( a == NULL )
	{ 
		return AURA_IN_PROCESS_TO_ADD;
	}
	uint32 from,to;
	uint32 SpellId = a->GetSpellId();
	if( IsPos )
	{
		from = FIRST_AURA_SLOT;
//		to = m_auras_pos_size;
		to = MAX_AURAS;	//!!PASSIVE AURAS CAN ALSO BE VISIBLE => more visual auras then real auras!
	}
	else
	{
		from = MAX_POSITIVE_AURAS;
		to = m_auras_neg_size;
	}
	//check for already visual same aura
	for(uint32 i=from;i<to;i++)
		if( m_auras[i] && m_auras[i] != a && m_auras[i]->GetSpellId() == SpellId 
			// && maybe we should also check if caster is the same for aura. Is it worth spamming the space ? Let's just group them
			)
			return m_auras[i]->m_visualSlot;
	//try to find an empty slot
	for(uint32 i=from;i<to;i++)
		if( m_auraStackCount[i] == 0 ) 
			return i;
	//worst case scenario due to bugs
	return AURA_INVALID_VISUAL_SLOT;
}

void Unit::AddAura(Aura *aur)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( !(m_mapId == 530 || m_mapId == 571) )
	{
		for( uint32 i = 0; i < 3; ++i )
		{
			// Can't use flying auras in non-outlands.
			if( aur->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_ENABLE_FLIGHT2 || aur->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_ENABLE_FLIGHT_NO_SPEED )
			{
				sLog.outDebug("Unit : addaura : removing aura without add since it cannot be casted except on specific maps = %s\n",aur->GetSpellProto()->Name );
				sEventMgr.RemoveEvents(aur);	//no events atm ?
				AuraPool.PooledDelete( aur );
				return;
			}
		}
	}
	
	if( aur->GetSpellProto()->School && SchoolImmunityList[aur->GetSpellProto()->School] )
	{
		sLog.outDebug("Unit : addaura : removing aura without add since we are immune to it = %s\n",aur->GetSpellProto()->Name );
		sEventMgr.RemoveEvents(aur);	//no events atm ?
		AuraPool.PooledDelete( aur );
		return;
	}

	uint16 first_free_slot=AURA_IN_PROCESS_TO_ADD;
    if( !aur->IsPassive() )
	{
		//uint32 aurName = aur->GetSpellProto()->Name;
		//uint32 aurRank = aur->GetSpellProto()->Rank;
		uint32 maxStack = aur->GetSpellProto()->maxstack;
		if( aur->GetSpellProto()->procCharges > 0 )
		{
			int32 charges = aur->GetSpellProto()->procCharges;
			if( (aur->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD) && aur->GetUnitCaster() != NULL )
			{
				SM_FIValue( aur->GetUnitCaster()->SM_FCharges, &charges, aur->GetSpellProto()->SpellGroupType );
				SM_PIValue( aur->GetUnitCaster()->SM_PCharges, &charges, aur->GetSpellProto()->SpellGroupType );
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
				float spell_flat_modifers=0;
				float spell_pct_modifers=0;
				SM_FIValue(aur->GetUnitCaster()->SM_FCharges,&spell_flat_modifers,aur->GetSpellProto()->SpellGroupType);
				SM_FIValue(aur->GetUnitCaster()->SM_PCharges,&spell_pct_modifers,aur->GetSpellProto()->SpellGroupType);
				if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
					printf("!!!!!spell charge bonus mod flat %f , spell range bonus pct %f , spell range %f, spell group %u\n",spell_flat_modifers,spell_pct_modifers,maxRange,m_spellInfo->SpellGroupType);
#endif
			}
			//some auras build up charges, for those maxstack is larger then 1 add
			if( charges > (int32)maxStack )
				maxStack=charges;
		}
		if( IsPlayer() && SafePlayerCast( this )->AuraStackCheat )
			maxStack = 999;

		SpellEntry * info = aur->GetSpellProto();
		//uint32 flag3 = aur->GetSpellProto()->Flags3;

		AuraCheckResponse acr;
		WorldPacket data( 21 );
		bool deleteAur = false;

		//check if we already have this aura by this caster -> update duration
		// Nasty check for Blood Fury debuff (spell system based on namehashes is bs anyways)
		{
			uint32 f = 0;
			uint32 start,end;
			if( aur->IsPositive() )
			{
				start = FIRST_AURA_SLOT;
				end = m_auras_pos_size;
			}
			else
			{
				start = MAX_POSITIVE_AURAS;
				end = m_auras_neg_size;
			}
			for( uint32 x = start; x < end; x++ )
			{
				if( m_auras[x] )
				{
					// Check for auras by specific type.
					// Check for auras with the same name and a different rank.					
					if( info->BGR_one_buff_on_target > 0
						&& (m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & info->BGR_one_buff_on_target)
						&& maxStack == 0)
					{
						if( ( info->BGR_one_buff_on_target_skip_caster_check == true || m_auras[x]->m_casterGuid == aur->m_casterGuid )
							|| ( m_auras[x]->GetSpellProto()->NameHash == info->NameHash && aur->IsPositive() )	//if maxstack == 0 then these should never stack
							)
						{
							sLog.outDebug("Unit : addaura : removing aura without add since target cannot have more = %s\n",aur->GetSpellProto()->Name );
							deleteAur = true;
							//refresh the timer
							if( m_auras[x]->GetSpellProto()->Id == aur->GetSpellProto()->Id )
							{
								//update duration,the same aura (update the whole stack whenever we cast a new one)
								m_auras[x]->ResetTimeLeft();
								//important to use new duration because due to diminishing returns refreshmight get smaller!
								sEventMgr.ModifyEventTimeLeft(m_auras[x], EVENT_AURA_REMOVE, aur->GetDuration());
								m_auras[x]->UpdateModifiers();
								ModVisualAuraStackCount(m_auras[x], 0);
							}
							break;
						}
					}
					else
					{
						acr = AuraCheck( aur, m_auras[x], maxStack );
						if(acr.Error == AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT)
						{
							sLog.outDebug("Unit : addaura : removing aura without add since target has better = %s\n",aur->GetSpellProto()->Name );
							deleteAur = true;
							//refresh the timer
							if( m_auras[x]->GetSpellProto()->Id == aur->GetSpellProto()->Id )
							{
								//update duration,the same aura (update the whole stack whenever we cast a new one)
								m_auras[x]->ResetTimeLeft();
								//important to use new duration because due to diminishing returns refreshmight get smaller!
								sEventMgr.ModifyEventTimeLeft(m_auras[x], EVENT_AURA_REMOVE, aur->GetDuration());
								m_auras[x]->UpdateModifiers();
								ModVisualAuraStackCount(m_auras[x], 0);
							}
							break;
						}
						else if(acr.Error == AURA_CHECK_RESULT_LOWER_BUFF_PRESENT)
						{
							// remove the lower aura
							m_auras[x]->Remove();
							// no more checks on bad ptr
							first_free_slot = x;
							break;
						}
						else if( acr.Error == AURA_CHECK_RESULT_CANNOT_STACK )
						{
							sLog.outDebug("Unit : addaura : removing aura without add since target cannot stack more = %s\n",aur->GetSpellProto()->Name );
							deleteAur = true;
							//refresh the timer
							if( m_auras[x]->GetSpellProto()->Id == aur->GetSpellProto()->Id )
							{
								//update duration,the same aura (update the whole stack whenever we cast a new one)
								uint32 end2=x+1;
								if( m_auras[x]->GetSpellProto()->maxstack > 1 )
									end2=end; 
								for( uint32 y = x; y < end2; y++ )
									if( m_auras[y] && m_auras[y]->GetSpellProto()->Id == aur->GetSpellProto()->Id )
									{
										m_auras[y]->ResetTimeLeft();
										//important to use new duration because due to diminishing returns refreshmight get smaller!
										sEventMgr.ModifyEventTimeLeft(m_auras[y], EVENT_AURA_REMOVE, aur->GetDuration());
										m_auras[y]->UpdateModifiers();
									}
								ModVisualAuraStackCount(m_auras[x], 0);
							}
							break;
						}
						//all stacks should have time refreshed 
						//!!! todo -> refresh all auras due to premature exit !!!
						if( m_auras[x]->GetSpellProto()->Id == aur->GetSpellProto()->Id )
						{
							//update duration,the same aura (update the whole stack whenever we cast a new one)
							m_auras[x]->ResetTimeLeft();
							//important to use new duration because due to diminishing returns refresh might get smaller!
							sEventMgr.ModifyEventTimeLeft(m_auras[x], EVENT_AURA_REMOVE, aur->GetDuration());
						}
					}					   
				}
				else if( first_free_slot == AURA_IN_PROCESS_TO_ADD )
				{
					first_free_slot = x;
					if( x + 1 == end )
					{
						if( aur->IsPositive() && m_auras_pos_size < MAX_POSITIVE_AURAS)
							m_auras_pos_size++;
						else if( m_auras_neg_size < MAX_AURAS )
							m_auras_neg_size++;
					}
				}
			}
		}

		if(deleteAur)
		{
			sEventMgr.RemoveEvents(aur);
			AuraPool.PooledDelete( aur );
			return;
		}
	}
	//this is for passive auras
	else
	{
		for( uint32 x = MAX_AURAS; x < m_auras_pas_size; x++ )
			if( !m_auras[x] )
			{
				first_free_slot = x;
				if( x + 1 == m_auras_pas_size && m_auras_pas_size < MAX_AURAS + MAX_PASSIVE_AURAS ) //if this was the last value of the list then we can extend it
					m_auras_pas_size++;
				break;
			}
	}
			
//printf("!!!!! the 3 vals pos = %u, neg = %u, pas = %u\n",m_auras_pos_size - 0,m_auras_neg_size - MAX_POSITIVE_AURAS,m_auras_pas_size - MAX_AURAS);

	//Zack : if all mods were resisted it means we did not apply anything and we do not need to delete this spell eighter
	// also abandon if there are no more free slots to add this aura to
	if( first_free_slot == AURA_IN_PROCESS_TO_ADD )
	{
		//notify client that we are imune to this spell ?
		sLog.outDebug("Unit : addaura : removing aura without add since target has no more slots left = %s\n",aur->GetSpellProto()->Name );
		sEventMgr.RemoveEvents(aur);
		AuraPool.PooledDelete( aur );
		return;
	}

/*	
	//some auras need this to ne sent. Just can't recall one :)
	WorldPacket data(SMSG_AURACASTLOG, 28);
	data << aur->m_casterGuid;
	data << GetGUID();
	data << aur->GetSpellId();
	data << uint64(0);
	SendMessageToSet(&data, true);*/

	// this is temporary aura. It is not added to unit until effect is applied
	aur->m_auraSlot = AURA_IN_PROCESS_TO_ADD;	
	aur->ApplyModifiers(true);

	//there is a chance that apply modifiers will actually try to cancel this aura because it calls some interrupt that will remove aura from list before it gets applied
	if( 
		//aur->m_deleted == true || 
		aur->TargetWasImuneToMods() )
	{
		sLog.outDebug("Unit : addaura : removing aura without add since target resisted all mods = %s\n",aur->GetSpellProto()->Name );
		aur->Remove();
		return;
	}
	if( m_auras[ first_free_slot ] != NULL )
	{
		//while applying effect of this aura we might have added other aura to the selected slot
		first_free_slot = AURA_IN_PROCESS_TO_ADD;
		if( aur->IsPassive() )
		{
			for( uint32 x = MAX_AURAS; x < m_auras_pas_size; x++ )
				if( m_auras[x] == NULL )
				{
					first_free_slot = x;
					if( x + 1 == m_auras_pas_size && m_auras_pas_size < MAX_AURAS + MAX_PASSIVE_AURAS ) //if this was the last value of the list then we can extend it
						m_auras_pas_size++;
					break;
				}
		}
		else if( aur->IsPositive() )
		{
			for( uint32 x = FIRST_AURA_SLOT; x < m_auras_pos_size; x++ )
				if( m_auras[x] == NULL )
				{
					first_free_slot = x;
					if( x + 1 == m_auras_pos_size && m_auras_pos_size < MAX_POSITIVE_AURAS ) //if this was the last value of the list then we can extend it
						m_auras_pos_size++;
					break;
				}
		}
		else
		{
			for( uint32 x = MAX_POSITIVE_AURAS; x < m_auras_neg_size; x++ )
				if( m_auras[x] == NULL )
				{
					first_free_slot = x;
					if( x + 1 == m_auras_neg_size && m_auras_neg_size < MAX_AURAS ) //if this was the last value of the list then we can extend it
						m_auras_neg_size++;
					break;
				}
		}
	}
	//we just ran out of slots ?
	if( first_free_slot == AURA_IN_PROCESS_TO_ADD )
	{
		sLog.outDebug("Unit : addaura : removing aura without add since target had no more free slots = %s\n",aur->GetSpellProto()->Name );
		aur->Remove();
		return;
	}
	//register this aura
	aur->m_auraSlot = first_free_slot;
	m_auras[ first_free_slot ] = aur;

	aur->m_visualSlot=AURA_INVALID_VISUAL_SLOT;
	//search for a visual slot
	// if aura is not passive, will have icon client side or has flag to forced show
	if( aur->IsVisible() )
	{
		aur->m_visualSlot = FindVisualSlot( aur , aur->IsPositive() );
		ModVisualAuraStackCount(aur, 1); //this might fail but there is no biggie about it :P
	}

	// We add 500ms here to allow for the last tick in DoT spells. This is a dirty hack, but at least it doesn't crash like my other method.
	// - Burlex
	if(aur->GetDuration() > 0)
	{
		sEventMgr.AddEvent(aur, &Aura::Remove, EVENT_AURA_REMOVE, aur->GetDuration() + 500, 1,
			EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT | EVENT_FLAG_DELETES_OBJECT);
	}

	//aur->RelocateEvents();

	if( aur->GetSpellProto()->MechanicsType == MECHANIC_ENRAGED )
		SetFlag( UNIT_FIELD_AURASTATE, AURASTATE_FLAG_ENRAGE );

	// Reaction from enemy AI - note that we are also adding threath in a lot of other places. This might be useless
	// this does not include refreshed aura threath
	Unit *pCaster = aur->GetUnitCaster();
	uint32 InterruptInvincible = (aur->GetSpellProto()->AuraInterruptFlags & AURA_INTERRUPT_ON_INVINCIBLE);
	if(	!aur->IsPositive() 
//		&& IsCreature()	//is it worth agroing non AI using units ?
		&& pCaster != this
		&& pCaster	//wow this actually happened to me
		&& pCaster->isAlive()
		&& this->isAlive()
		&& ( aur->GetSpellProto()->ThreatForSpellCoef 
//			|| aur->IsCombatStateAffecting() 
		) )	  // Creature
	{
		pCaster->CombatStatus.OnDamageDealt(this);
		//max 3 mods
		uint32 aura_mod_sum=0;
		for(uint32 i=0;i<aur->m_modcount;i++)
			aura_mod_sum += aur->m_modList[i].m_amount;
		if( aura_mod_sum <= 0 )
			aura_mod_sum = 1;
		if(( aur->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_HEALING ) == 0 )
			m_aiInterface->AttackReaction(pCaster, aura_mod_sum, aur->GetSpellId());
	}

	//!!!! attackreaction can remove this newly added aura !!!
	if( InterruptInvincible && pCaster)
	{
		pCaster->RemoveStealth();
		pCaster->RemoveInvisibility();
		pCaster->RemoveAllAuraByNameHash(SPELL_HASH_ICE_BLOCK);
		pCaster->RemoveAllAuraByNameHash(SPELL_HASH_DIVINE_SHIELD);
		pCaster->RemoveAllAuraByNameHash(SPELL_HASH_BLESSING_OF_PROTECTION);
	}
}


bool Unit::RemoveAura(Aura *aur)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	aur->Remove();
	return true;
}

//also used to remove talents so it needs to check passive ones too
bool Unit::RemoveAura(uint32 spellId)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId )
		{
			m_auras[x]->Remove();
			return true;
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId )
		{
			m_auras[x]->Remove();
			return true;
		}
	//this can be speed up, if we know passive \pos neg
	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId )
		{
			m_auras[x]->Remove();
			return true;
		}
	return false;
}

bool Unit::RemoveAuras(uint32 * SpellIds)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(!SpellIds || *SpellIds == 0)
	{ 
		return false;
	}

	uint32 x,y;
	bool res = false;
	for(x=FIRST_AURA_SLOT;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
		if(m_auras[x])
			for(y=0;SpellIds[y] != 0;++y)
				if(m_auras[x]->GetSpellId()==SpellIds[y])
				{
					m_auras[x]->Remove();
					res = true;
				}
	return res;
}

uint32 Unit::RemoveAuraByHeal(uint32 Slot)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	uint32 res = 0;
	if ( m_auras[Slot] )
	{
		switch( m_auras[Slot]->GetSpellId() )
		{
			// remove after heal
			case 35321:
			case 38363:
			case 39215:
			{
				m_auras[Slot]->Remove();
				res = 1;
			} break;
			// remove when healed to 100%
			case 31956:
			case 38801:
			case 43093:
			{
				if ( GetUInt32Value( UNIT_FIELD_HEALTH ) == GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
				{
					m_auras[Slot]->Remove();
					res = 1;
				}
			} break;
			// remove at p% health
			case 38772:
			{
				uint32 p = m_auras[Slot]->GetSpellProto()->EffectBasePoints[1];
				if ( GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * p <= GetUInt32Value( UNIT_FIELD_HEALTH ) * 100 )
				{
					m_auras[Slot]->Remove();
					res = 1;
				}
			} break;
		}
	}
	return res;
}

uint32 Unit::RemoveAurasByHeal()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	uint32 res = 0;
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		res += RemoveAuraByHeal( x );
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		res += RemoveAuraByHeal( x );
	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		res += RemoveAuraByHeal( x );

	return res;
}

//apart from spells loosing a charge you probably wanted to use removeallauras to make sure all charges and invisible parts are removed
bool Unit::RemoveAura(uint32 spellId, const uint64 &guid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
   
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId && m_auras[x]->m_casterGuid == guid)
		{
			m_auras[x]->Remove();
			return true;
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId && m_auras[x]->m_casterGuid == guid)
		{
			m_auras[x]->Remove();
			return true;
		}
	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId && m_auras[x]->m_casterGuid == guid)
		{
			m_auras[x]->Remove();
			return true;
		}
	return false;
}

bool Unit::RemoveAuraByNameHash(uint32 namehash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash)
		{
			m_auras[x]->Remove();
			return true;
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash)
		{
			m_auras[x]->Remove();
			return true;
		}
/*	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash)
		{
			m_auras[x]->Remove();
			return true;
		}*/
	return false;
}

bool Unit::RemoveAuraPos(uint32 spellId,const uint64 &guid,bool check_passive)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( check_passive == true && IsVisibleAura( dbcSpell.LookupEntryForced( spellId ) ) )
	{
		if( guid==0 )
		{
			for(uint32 x=MAX_AURAS;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
				if(m_auras[x])
					if(m_auras[x]->GetSpellProto()->Id==spellId )
					{
						m_auras[x]->Remove();
						return true;
					}
		}
		else
		{
			for(uint32 x=MAX_AURAS;x<MAX_AURAS+MAX_PASSIVE_AURAS;x++)
				if(m_auras[x])
					if(m_auras[x]->GetSpellProto()->Id==spellId && m_auras[x]->m_casterGuid == guid )
					{
						m_auras[x]->Remove();
						return true;
					}
		}
		return false;
	}
	if( guid==0 )
	{
		for(uint32 x=FIRST_AURA_SLOT;x<MAX_POSITIVE_AURAS;x++)
			if(m_auras[x])
				if(m_auras[x]->GetSpellProto()->Id==spellId )
				{
					m_auras[x]->Remove();
					return true;
				}
	}
	else
	{
		for(uint32 x=FIRST_AURA_SLOT;x<MAX_POSITIVE_AURAS;x++)
			if(m_auras[x])
				if(m_auras[x]->GetSpellProto()->Id==spellId && m_auras[x]->m_casterGuid == guid )
				{
					m_auras[x]->Remove();
					return true;
				}
	}
	return false;
}

bool Unit::RemoveAuraPosByNameHash(uint32 namehash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<MAX_POSITIVE_AURAS;x++)
		if(m_auras[x])
			if(m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				return true;
			}
	return false;
}

bool Unit::RemoveAuraNegByNameHash(uint32 namehash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				return true;
			}
	return false;
}

bool Unit::RemoveAllAuras(uint32 spellId, const uint64 &guid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
   
	bool res = false;
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId && (!guid || m_auras[x]->m_casterGuid == guid) )
		{
			m_auras[x]->Remove();
			res = true;
//			return true;	//all auras !
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId && (!guid || m_auras[x]->m_casterGuid == guid) )
		{
			m_auras[x]->Remove();
			res = true;
//			return true;	//all auras !
		}
	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId && (!guid || m_auras[x]->m_casterGuid == guid) )
		{
			m_auras[x]->Remove();
			res = true;
//			return true;	//all auras !
		}	
	return res;
}

bool Unit::RemoveAllAuraByNameHash(uint32 namehash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	bool res = false;
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				res=true;
			}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				res=true;
			}
	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				res=true;
			}
	return res;
}

uint32 Unit::RemoveAllPosAuraByNameHash(uint32 namehash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	uint32 res = 0;
	for(uint32 x=FIRST_AURA_SLOT;x<MAX_POSITIVE_AURAS;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				res++;
			}
	return res;
}

uint32 Unit::RemoveAllNegAuraByNameHash(uint32 namehash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	uint32 res = 0;
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash)
			{
				m_auras[x]->Remove();
				res++;
			}
	return res;
}

void Unit::RemoveNegativeAuras()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x])
		{
            if(m_auras[x]->GetSpellProto()->AttributesExC & CAN_PERSIST_AND_CASTED_WHILE_DEAD)
                continue;
            else
            {
			    m_auras[x]->Remove();
            }
		}
}

void Unit::RemoveAllAuras()
{
	bool found_auras;
	do
	{
		found_auras = false;
		for(uint32 x=FIRST_AURA_SLOT;x<MAX_AURAS + MAX_PASSIVE_AURAS;x++)
			if(m_auras[x])
			{
				m_auras[x]->Remove();
				found_auras = true;
			}
	//funny huh? Some auras add auras on remove ;) We want ALL auras cleared !
	}while( found_auras == true );
}

//ex:to remove morph spells
void Unit::RemoveAllAuraType(uint32 auratype)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x])
		{
			SpellEntry *proto=m_auras[x]->GetSpellProto();
			if(proto->EffectApplyAuraName[0]==auratype || proto->EffectApplyAuraName[1]==auratype || proto->EffectApplyAuraName[2]==auratype)
				RemoveAura(m_auras[x]->GetSpellId());//remove all morph auras containig to this spell (like wolf motph also gives speed)
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x])
		{
			SpellEntry *proto=m_auras[x]->GetSpellProto();
			if(proto->EffectApplyAuraName[0]==auratype || proto->EffectApplyAuraName[1]==auratype || proto->EffectApplyAuraName[2]==auratype)
				RemoveAura(m_auras[x]->GetSpellId());//remove all morph auras containig to this spell (like wolf motph also gives speed)
		}
/*	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x])
		{
			SpellEntry *proto=m_auras[x]->GetSpellProto();
			if(proto->EffectApplyAuraName[0]==auratype || proto->EffectApplyAuraName[1]==auratype || proto->EffectApplyAuraName[2]==auratype)
				RemoveAura(m_auras[x]->GetSpellId());//remove all morph auras containig to this spell (like wolf motph also gives speed)
		}*/
}


//ex:to remove morph spells
void Unit::RemoveAllAuraFromSelfType2(uint32 auratype, uint32 butskip_hash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x])
		{
			SpellEntry *proto=m_auras[x]->GetSpellProto();
			if( proto->BGR_one_buff_from_caster_on_self == auratype 
				&& proto->NameHash != butskip_hash
				&& m_auras[x]->GetCaster() == this 
				)
				RemoveAura(m_auras[x]->GetSpellId());//remove all morph auras containig to this spell (like wolf motph also gives speed)
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x])
		{
			SpellEntry *proto=m_auras[x]->GetSpellProto();
			if( proto->BGR_one_buff_from_caster_on_self == auratype 
				&& proto->NameHash != butskip_hash
				&& m_auras[x]->GetCaster() == this 
				)
				RemoveAura(m_auras[x]->GetSpellId());//remove all morph auras containig to this spell (like wolf motph also gives speed)
		}
}

/*
bool Unit::SetAurDuration(uint32 spellId,Unit* caster,uint32 duration)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	Aura*aur=FindAura(spellId,caster->GetGUID());
	if(!aur)
	{ 
		return false;
	}
	aur->SetDuration(duration);
	sEventMgr.ModifyEventTimeLeft(aur, EVENT_AURA_REMOVE, duration);
			
	if( aur->m_visualSlot < MAX_VISIBLE_AURAS )
	{
		uint8 flags;
		flags = 0; // do not send guid
		flags |= VISUALAURA_FLAG_VISIBLE; //seems to be always present
		if( aur->m_casterGuid == GetGUID() )
			flags |= VISUALAURA_FLAG_SELF_CAST;
		if( !aur->IsPositive() )
			flags |= VISUALAURA_FLAG_NEGATIVE; 
		else
			flags |= VISUALAURA_FLAG_UNK_POS | VISUALAURA_FLAG_REMOVABLE;
		if( aur->GetDuration() != (uint32)-1 ) //yes it is stupid to force -1 to be uint32 but that is the way it is made elsewhere
			flags |= VISUALAURA_FLAG_HAS_DURATION; 
		sStackWolrdPacket( data, SMSG_AURA_UPDATE, 50);
		FastGUIDPack(data, GetGUID());
		data << uint8(aur->m_visualSlot);
		data << uint32(aur->GetSpellId());
		data << (uint8)flags;
//		data << (uint8)(m_aura_packet_serialization++);
		data << (uint8)(aur->GetSpellProto()->maxLevel);
		data << uint8(m_auraStackCount[aur->m_visualSlot]);

		if( (flags & VISUALAURA_FLAG_SELF_CAST)==0 )
			FastGUIDPack(data, aur->m_casterGuid);

		//seems like this depends on flag 0x20
		if( flags & VISUALAURA_FLAG_HAS_DURATION )
			data << uint32(aur->GetDuration()) << uint32(aur->GetTimeLeft());
		SendMessageToSet(&data, true);
	}
			
	return true;
}


bool Unit::SetAurDuration(uint32 spellId,uint32 duration)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	Aura*aur=FindAura(spellId);

	if(!aur) 
	{ 
		return false;
	}
	

	aur->SetDuration(duration);
	sEventMgr.ModifyEventTimeLeft(aur, EVENT_AURA_REMOVE, duration);
		
	if( aur->m_visualSlot && aur->m_visualSlot < MAX_VISIBLE_AURAS )
	{
		uint8 flags;
		flags = 0; // do not send guid
		flags |= VISUALAURA_FLAG_VISIBLE; //seems to be always present
		if( aur->m_casterGuid == GetGUID() )
			flags |= VISUALAURA_FLAG_SELF_CAST;
		if( !aur->IsPositive() )
			flags |= VISUALAURA_FLAG_NEGATIVE; 
		else
			flags |= VISUALAURA_FLAG_UNK_POS | VISUALAURA_FLAG_REMOVABLE;
		if( aur->GetDuration() != (uint32)-1 ) //yes it is stupid to force -1 to be uint32 but that is the way it is made elsewhere
			flags |= VISUALAURA_FLAG_HAS_DURATION; 
		sStackWolrdPacket( data, SMSG_AURA_UPDATE, 50);
		FastGUIDPack(data, GetGUID());
		data << uint8(aur->m_visualSlot);
		data << uint32(aur->GetSpellId());
		data << (uint8)flags;
///		data << (uint8)(m_aura_packet_serialization++);
		data << (uint8)(aur->GetSpellProto()->maxLevel);
		data << uint8(m_auraStackCount[aur->m_visualSlot]);

		if( (flags & VISUALAURA_FLAG_SELF_CAST)==0 )
			FastGUIDPack(data, aur->m_casterGuid);

		//seems like this depends on flag 0x20
		if( flags & VISUALAURA_FLAG_HAS_DURATION )
			data << uint32(aur->GetDuration()) << uint32(aur->GetTimeLeft());
		SendMessageToSet(&data, true);
	}

	return true;
}*/

Aura* Unit::FindAuraByNameHash(uint32 namehash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash)
		{ 
				return m_auras[x];
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash)
		{ 
				return m_auras[x];
		}
	return NULL;
}

Aura* Unit::FindAuraByNameHash(uint32 namehash,const uint64 &guid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash && m_auras[x]->m_casterGuid == guid)
		{ 
				return m_auras[x];
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash && m_auras[x]->m_casterGuid == guid)
		{ 
				return m_auras[x];
		}
	return NULL;
}

Aura* Unit::FindAuraPassiveByNameHash(uint32 namehash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash==namehash )
		{ 
				return m_auras[x];
		}
	return NULL;
}

Aura* Unit::FindAura(uint32 spellId)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId)
		{ 
			return m_auras[x];
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId)
		{ 
			return m_auras[x];
		}
	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellId)
		{ 
			return m_auras[x];
		}
	return NULL;
}

Aura* Unit::FindAura(uint32 spellId, const uint64 &guid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId() == spellId && m_auras[x]->m_casterGuid == guid)
		{ 
				return m_auras[x];
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId() == spellId && m_auras[x]->m_casterGuid == guid)
		{ 
				return m_auras[x];
		}
	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId() == spellId && m_auras[x]->m_casterGuid == guid)
		{ 
				return m_auras[x];
		}
	return NULL;
}

void Unit::_UpdateSpells( uint32 time )
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	/* to avoid deleting the current spell */
	if(m_currentSpell != NULL)
	{
//		m_spellsbusy=true;
		m_currentSpell->update(time);
//		m_spellsbusy=false;
	}
}

void Unit::CastSpellDelayed( uint64 targetGuid, uint32 SpellID, uint32 Delay)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
//	sEventMgr.AddEvent( this, &Unit::CastSpell, (uint64)targetGuid, (uint32)SpellID, (bool)false, (uint32)EVENT_DELAYED_SPELLCAST, Delay, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
	sEventMgr.AddEvent( this, &Unit::EventCastSpell2, (uint64)targetGuid, (uint32)SpellID, (uint32)EVENT_DELAYED_SPELLCAST, Delay, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT );
}

void Unit::castSpell( Spell * pSpell )
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	// check if we have a spell already casting etc
	if(m_currentSpell && pSpell != m_currentSpell)
	{
/*	
		//removed by zack : Spell system does not really handle well paralel casting. We are forced to cancel previous cast
		//eventually make creatures be able to cast secondary spell that is tracked or figure out where is this deleted
		if(m_spellsbusy)
		{
			// shouldn't really happen. but due to spell sytem bugs there are some cases where this can happen.
			sEventMgr.AddEvent(this,&Unit::CancelSpell,m_currentSpell,EVENT_UNIT_DELAYED_SPELL_CANCEL,1,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
		}
		else*/
		m_currentSpell->cancel();
	}

	m_currentSpell = pSpell;
	pLastSpell = pSpell->GetProto();
}

int32 Unit::GetSpellDmgBonus(Unit *pVictim, SpellEntry *spellInfo,int32 base_dmg, int32 DOTticks)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	int32 plus_damage = 0;
	Unit* caster = this;
	uint32 school = spellInfo->School;

	if( spellInfo->c_is_flags & SPELL_FLAG_IS_NOT_USING_DMG_BONUS )
	{ 
		return 0;
	}

//------------------------------by school---------------------------------------------------
	plus_damage += caster->GetDamageDoneMod(school);
	plus_damage += pVictim->DamageTakenMod[school];
	plus_damage += pVictim->ModDamageTakenByMechFlat[spellInfo->MechanicsType];
//------------------------------by victim type----------------------------------------------
	if(pVictim->IsCreature() && SafeCreatureCast(pVictim)->GetCreatureInfo() && caster->IsPlayer() )
		plus_damage += SafePlayerCast(caster)->IncreaseDamageByType[SafeCreatureCast(pVictim)->GetCreatureInfo()->Type]; //this might create a crash. Leaving it like this to detect new creature types :)
//==========================================================================================
//==============================+Spell Damage Bonus Modifications===========================
//==========================================================================================
//------------------------------by cast duration--------------------------------------------
	float dmgdoneaffectperc = 1.0f;
	//Bonus to DD part
	if( spellInfo->fixed_dddhcoef >= 0 && DOTticks <= 1 )
		plus_damage = float2int32( float( plus_damage ) * spellInfo->fixed_dddhcoef );
	//Bonus to DoT part
	else if( spellInfo->fixed_hotdotcoef >= 0 && DOTticks > 1 )
	{
		plus_damage = float2int32( float( plus_damage ) * spellInfo->fixed_hotdotcoef );
		if( caster->IsPlayer() )
		{
			int durmod = 0;
			SM_FIValue(caster->SM_FDur, &durmod, spellInfo->SpellGroupType);
			plus_damage += float2int32( float( plus_damage * durmod ) / 15000.0f );
		}
	}

	//------------------------------by downranking----------------------------------------------
	//DOT-DD (Moonfire-Immolate-IceLance-Pyroblast)(Hack Fix)
#ifdef USE_SPELL_DOWNRANKING
	if( IsPlayer() )	//not sure if this is true but a lot of mob spells have really small spell levels and some custom realms get very low dmg
	{
		if( GetUInt32Value( UNIT_FIELD_LEVEL ) > spellInfo->maxLevel )
			dmgdoneaffectperc = (22 + (int32)MAX(spellInfo->spellLevel,spellInfo->maxLevel) - (int32)GetUInt32Value( UNIT_FIELD_LEVEL )) / 20.0f;
		if( dmgdoneaffectperc < 0 )
			dmgdoneaffectperc = 0.0f;
		else if( dmgdoneaffectperc > 1 )
			dmgdoneaffectperc = 1.0f;
	}
#endif
//==========================================================================================
//==============================Bonus Adding To Main Damage=================================
//==========================================================================================
	int32 bonus_damage = float2int32(plus_damage * dmgdoneaffectperc);

	//bonus_damage +=pVictim->DamageTakenMod[school]; Bad copy-past i guess :P
	int dmg_bonus_pct_mod=100;
	if((spellInfo->c_is_flags & SPELL_FLAG_IS_REQUIRING_SM_MOD))
	{
		SM_FIValue(caster->SM_FDamageBonus, &bonus_damage, spellInfo->SpellGroupType);
		SM_FIValue(caster->SM_PPenalty, &dmg_bonus_pct_mod, spellInfo->SpellGroupType);		
		SM_FIValue(caster->SM_PDamageBonus,&dmg_bonus_pct_mod,spellInfo->SpellGroupType);
//		bonus_damage += (base_dmg+bonus_damage)*dmg_bonus_pct/100;
//		bonus_damage += bonus_damage*dmg_bonus_pct/100;
#ifdef COLLECTION_OF_UNTESTED_STUFF_AND_TESTERS
		spell_flat_modifers=0;
		spell_pct_modifers=0;
		SM_FIValue(caster->SM_FDamageBonus,&spell_flat_modifers,spellInfo->SpellGroupType);
		SM_FIValue(caster->SM_PDamageBonus,&spell_pct_modifers,spellInfo->SpellGroupType);
		if(spell_flat_modifers!=0 || spell_pct_modifers!=0)
			printf("!!!!!spell dmg bonus mod flat %d , spell dmg bonus pct %d , spell dmg bonus %d, spell group %u\n",spell_flat_modifers,spell_pct_modifers,bonus_damage,spellInfo->SpellGroupType);
#endif
	}
//------------------------------by school----------------------------------------------
	float summaryPCTmod = caster->GetDamageDonePctMod(school)-1; //value is initialized with 1
	summaryPCTmod += pVictim->DamageTakenPctMod[school];
//	summaryPCTmod += caster->DamageDoneModPCT[school];	// BURLEX FIXME
	summaryPCTmod += pVictim->ModDamageTakenByMechCoef[spellInfo->MechanicsType];
	int32 res = (int32)((base_dmg+bonus_damage)*summaryPCTmod + bonus_damage*dmg_bonus_pct_mod/100);
	if( res < 0 )
		res = 0;
	return res;
}

int32 Unit::GetSpellHealBonus(Unit *pVictim, SpellEntry *spellInfo,int32 base_heal, int32 HOTticks)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	int32 bonus = 0;
	uint32 school = spellInfo->School;

	if( spellInfo->Spell_value_is_scripted == true )
	{ 
		return 0;
	}

	//Basic bonus
	if( CanClassReceiveDMGOrHealBonus( ) )
		bonus += HealDoneMod;
	bonus += pVictim->HealTakenMod;

	//Bonus from Intellect & Spirit
	if( IsPlayer() )
	{
		Player *p_caster = SafePlayerCast(this);
		for(uint32 a = 0; a < 5; a++)
			bonus += float2int32(p_caster->SpellHealDoneByAttribute[a] * (float)p_caster->GetUInt32Value(UNIT_FIELD_STAT0 + a));
	}

	//Spell Coefficient
	if( spellInfo->fixed_hotdotcoef >= 0 && HOTticks > 1 
//		&& (spellInfo->spell_coef_flags & SPELL_FLAG_IS_HOT_SPELL)
		) 
		bonus = float2int32( float( bonus ) * spellInfo->fixed_hotdotcoef );	//!!whole bonus will bedivided at the end
	else if( spellInfo->fixed_dddhcoef >= 0 && HOTticks <= 1 
//		&& (spellInfo->spell_coef_flags & SPELL_FLAG_IS_DH_SPELL)
		) //Bonus to DH part
			bonus = float2int32( float( bonus ) * spellInfo->fixed_dddhcoef );

	int32 spell_power_bonus_pct = 0;
	SM_FIValue( SM_PPenalty, &spell_power_bonus_pct, spellInfo->SpellGroupType );
	if( spell_power_bonus_pct )
		bonus += HealDoneMod * spell_power_bonus_pct / 100 / spellInfo->quick_tickcount;

//Downranking
#ifdef USE_SPELL_DOWNRANKING
	float downrank1 = 1.0f;
	if( GetUInt32Value( UNIT_FIELD_LEVEL ) > spellInfo->maxLevel )
		downrank1 = (22 + (int32)MAX(spellInfo->spellLevel,spellInfo->maxLevel) - (int32)GetUInt32Value( UNIT_FIELD_LEVEL )) / 20.0f;
	if( downrank1 < 0 )
		downrank1 = 0.0f;
	if( downrank1 < 1 )
		bonus = int32(bonus * downrank1); 
#endif
	int32 limited_mod = MAX(pVictim->HealTakenPctMod,-50);	//there is a logic in auras which stack and which not. THIS IS A HACKFIX !
	bonus += base_heal * ( HealDonePctMod + limited_mod ) / 100;

	if (Need_SM_Apply(spellInfo))
		SM_PIValue(SM_PDamageBonus,&bonus,spellInfo->SpellGroupType);

	if( bonus < 0 )
		bonus = 0;
	
	bonus = bonus / HOTticks;

	return bonus;
}

void Unit::InterruptSpell()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(m_currentSpell)
	{
/*		//ok wtf is this
		//m_currentSpell->SendInterrupted(SPELL_FAILED_INTERRUPTED);
		//m_currentSpell->cancel();
		if(m_spellsbusy)
		{
			// shouldn't really happen. but due to spell sytem bugs there are some cases where this can happen.
			sEventMgr.AddEvent(this,&Unit::CancelSpell,m_currentSpell,EVENT_UNIT_DELAYED_SPELL_CANCEL,1,1,EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
			m_currentSpell=NULL;
		}
		else*/
			m_currentSpell->safe_cancel();
	}
}

void Unit::DeMorph()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	// hope it solves it :)
	uint32 displayid = this->GetUInt32Value(UNIT_FIELD_NATIVEDISPLAYID);
	this->SetUInt32Value(UNIT_FIELD_DISPLAYID, displayid);
	EventModelChange();
}

void Unit::Emote(EmoteType emote)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(emote == 0)
	{ 
		return;
	}

	sStackWolrdPacket( data, SMSG_EMOTE, 20 );
	data << uint32(emote);
	data << this->GetGUID();
	SendMessageToSet (&data, true);
}

void Unit::SendChatMessageToPlayer(uint8 type, uint32 lang, const char *msg, Player *plr)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	size_t UnitNameLength = 0, MessageLength = 0;
	CreatureInfo *ci = (IsCreature()) ? SafeCreatureCast(this)->GetCreatureInfo() : NULL;

	if(ci == NULL || plr == NULL)
	{ 
		return;
	}

	UnitNameLength = strlen((char*)ci->Name) + 1;
	MessageLength = strlen((char*)msg) + 1;
	//wtf mem error ?
	if( UnitNameLength > 200 || MessageLength > 200 )
	{
		return; 
	}

	sStackWolrdPacket( data, SMSG_MESSAGECHAT, 35 + 1000 );
	data << type;
	data << lang;
	data << GetGUID();
	data << uint32(0);			// new in 2.1.0
	data << uint32(UnitNameLength);
	data << ci->Name;
	data << uint64(0);
	data << uint32(MessageLength);
	data << msg;
	data << uint8(0x00);
	plr->GetSession()->SendPacket(&data);
}

void Unit::SendChatMessageAlternateEntry(uint32 entry, uint8 type, uint32 lang, const char * msg)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	size_t UnitNameLength = 0, MessageLength = 0;
	CreatureInfo *ci;

	ci = CreatureNameStorage.LookupEntry(entry);
	if(!ci)
	{ 
		return;
	}

	UnitNameLength = strlen((char*)ci->Name) + 1;
	MessageLength = strlen((char*)msg) + 1;
	//wtf mem error ?
	if( UnitNameLength > 200 || MessageLength > 200 )
	{
		return; 
	}

	sStackWolrdPacket( data, SMSG_MESSAGECHAT, 750 );
	data << type;
	data << lang;
	data << GetGUID();
	data << uint32(0);			// new in 2.1.0
	data << uint32(UnitNameLength);
	data << ci->Name;
	data << uint64(0);
	data << uint32(MessageLength);
	data << msg;
	data << uint8(0x00);
	SendMessageToSet(&data, true);
}

void Unit::SendChatMessage(uint8 type, uint32 lang, const char *msg)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	size_t UnitNameLength = 0, MessageLength = 0;
	CreatureInfo *ci = (IsCreature()) ? SafeCreatureCast(this)->GetCreatureInfo() : NULL;

	if(ci == NULL)
	{ 
		return;
	}

	UnitNameLength = strlen((char*)ci->Name) + 1;
	MessageLength = strlen((char*)msg) + 1;
	//wtf mem error ?
	if( UnitNameLength > 200 || MessageLength > 200 )
	{
		return; 
	}

	sStackWolrdPacket( data, SMSG_MESSAGECHAT, 35 + 1000 );
	data << type;
	data << lang;
	data << GetGUID();
	data << uint32(0);			// new in 2.1.0
	data << uint32(UnitNameLength);
	data << ci->Name;
	data << uint64(0);
	data << uint32(MessageLength);
	data << msg;
	data << uint8(0x00);
	SendMessageToSet(&data, true);
}

void Unit::WipeHateList()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
 
	GetAIInterface()->WipeHateList(); 
}
void Unit::ClearHateList()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	GetAIInterface()->ClearHateList();
}

void Unit::WipeTargetList() 
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
 
	GetAIInterface()->WipeTargetList(); 
}

void Unit::AddInRangeObject(Object* pObj)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if((pObj->GetTypeId() == TYPEID_UNIT) || (pObj->GetTypeId() == TYPEID_PLAYER))
	{
//		if( isHostile( this, (Unit*)pObj ) )
//			m_oppFactsInRange.insert(pObj);

//		if ( isFriendly( this, (Unit*)pObj ) )
//			m_sameFactsInRange.insert(pObj);

		// commented - this code won't work anyway due to objects getting added in range before they are created - burlex
		/*if( GetTypeId() == TYPEID_PLAYER )
		{
			if( SafePlayerCast( this )->InGroup() )
			{
				if( pObj->GetTypeId() == TYPEID_UNIT )
				{
					if(((Creature*)pObj)->Tagged)
					{
						if( SafePlayerCast( this )->GetGroup()->HasMember( pObj->GetMapMgr()->GetPlayer( (uint32)((Creature*)pObj)->TaggerGuid ) ) )
						{
							uint32 Flags;
							Flags = ((Creature*)pObj)->m_uint32Values[UNIT_DYNAMIC_FLAGS];
							Flags |= U_DYN_FLAG_TAPPED_BY_PLAYER;
							ByteBuffer buf1(500);
							((Creature*)pObj)->BuildFieldUpdatePacket(&buf1, UNIT_DYNAMIC_FLAGS, Flags);
							SafePlayerCast( this )->PushUpdateData( &buf1, 1 );
						}
					}
				}
			}
		}		*/
	}

	Object::AddInRangeObject(pObj);
}//427

void Unit::OnRemoveInRangeObject(Object* pObj)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
//	m_oppFactsInRange.erase(pObj);
//	m_sameFactsInRange.erase(pObj);

	if(pObj->GetTypeId() == TYPEID_UNIT || pObj->GetTypeId() == TYPEID_PLAYER)
	{
		/*if(m_useAI)*/

		Unit *pUnit = SafeUnitCast(pObj);
		GetAIInterface()->CheckTarget(pUnit);

		if(GetUInt64Value(UNIT_FIELD_CHARM) == pObj->GetGUID())
			if(m_currentSpell)
				m_currentSpell->cancel();

        Object::OnRemoveInRangeObject(pObj);
        if(critterPet == pObj)
		{
			critterPet->SafeDelete();
			critterPet = 0;
		}
	}
    else
    {
        Object::OnRemoveInRangeObject(pObj);
    }
}

void Unit::ClearInRangeSet()
{
	Object::ClearInRangeSet();
}

//Events
void Unit::EventAddEmote(EmoteType emote, uint32 time)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	m_oldEmote = GetUInt32Value(UNIT_NPC_EMOTESTATE);
	SetUInt32Value(UNIT_NPC_EMOTESTATE,emote);
	sEventMgr.AddEvent(this, &Creature::EmoteExpire, EVENT_UNIT_EMOTE, time, 1,0);
}

void Unit::EmoteExpire()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	SetUInt32Value(UNIT_NPC_EMOTESTATE, m_oldEmote);
	sEventMgr.RemoveEvents(this, EVENT_UNIT_EMOTE);
}


uint32 Unit::GetResistance(uint32 type)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	return GetUInt32Value(UNIT_FIELD_RESISTANCES+type);
}

void Unit::MoveToWaypoint(uint32 wp_id)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(this->m_useAI && this->GetAIInterface() != NULL)
	{
		AIInterface *ai = GetAIInterface();
		WayPoint *wp = ai->getWayPoint(wp_id);
		if(!wp)
		{
			sLog.outString("WARNING: Invalid WP specified in MoveToWaypoint.");
			return;
		}

		ai->m_currentWaypoint = wp_id;
		if(wp->flags!=0)
			ai->m_moveRun = true;
		ai->MoveTo(wp->x, wp->y, wp->z, 0);
	}
}

bool Unit::CanClassReceiveDMGOrHealBonus()
{
	if( IsCreature() )
		return true;
	//warriors, DKs should not have spell power bonus
	static bool class_power_enabler[12]={ false, false, true, true, false, true, false, true, true, true, true, true };
	if( getClass() < 12 )
		return class_power_enabler[ getClass() ];
	return false;
}

int32 Unit::GetDamageDoneMod(uint32 school)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE

	//some class like warrior get dmg from AP and not SP
	if( CanClassReceiveDMGOrHealBonus() == false )
		return 0;

	if (school < SCHOOL_COUNT)
	{
		if( this->IsPlayer() )
		{ 
		   return (int32)GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_POS + school ) - (int32)GetUInt32Value( PLAYER_FIELD_MOD_DAMAGE_DONE_NEG + school );
		}
		else
		   return SafeCreatureCast( this )->ModDamageDone[school];
	}
	else
		sLog.outDebug("[NOTICE] You have bad DB, spell school = %u\n",school);
	return 0;
}
	
float Unit::GetDamageDonePctMod(uint32 school)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if (school < SCHOOL_COUNT)
	{
	    if(this->IsPlayer())
	    { 
		   return m_floatValues[PLAYER_FIELD_MOD_DAMAGE_DONE_PCT+school];
	    }
		else
		   return SafeCreatureCast(this)->ModDamageDonePct[school];
	}
	else
		sLog.outDebug("[NOTICE] You have bad DB, spell school = %u\n",school);
	return 0;
}

void Unit::CalcDamage()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( IsPlayer() )
		SafePlayerCast( this )->CalcDamage();
	else
	{
		if( IsPet() )
		{
			SafePetCast(this)->UpdateSP();
			SafePetCast(this)->UpdateAP();
		}
		float r;
		float delta;
		float mult;
	
		float ap_bonus = float(GetAP())/14000.0f;

		float bonus = ap_bonus * ( GetUInt32Value(UNIT_FIELD_BASEATTACKTIME) + SafeCreatureCast( this )->m_speedFromHaste );
	
		delta = float(SafeCreatureCast(this)->ModDamageDone[0]);
		mult = float(SafeCreatureCast(this)->ModDamageDonePct[0]);
		r = ( BaseDamage[0] + bonus ) * mult + delta;
		// give some diversity to pet damage instead of having a 77-78 damage range (as an example)
		SetFloatValue(UNIT_FIELD_MINDAMAGE,r > 0 ? ( IsPet() ? r * 0.9f : r ) : 0 );
		r = ( BaseDamage[1] + bonus ) * mult + delta;
		SetFloatValue(UNIT_FIELD_MAXDAMAGE, r > 0 ? ( IsPet() ? r * 1.1f : r ) : 0 );
	
	//	SetFloatValue(UNIT_FIELD_MINRANGEDDAMAGE,BaseRangedDamage[0]*mult+delta);
	//	SetFloatValue(UNIT_FIELD_MAXRANGEDDAMAGE,BaseRangedDamage[1]*mult+delta);
  
	}	
}

//returns absorbed dmg
uint32 Unit::ManaShieldAbsorb(uint32 dmg)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(!m_manashieldamt)
	{ 
		return 0;
	}
	//mana shield group->16. the only

	uint32 mana = GetUInt32Value(UNIT_FIELD_POWER1);
	int32 effectbonus = SM_PEffectBonus ? SM_PEffectBonus[16] : 0;

	int32 potential = (mana*50)/((100+effectbonus));
	if(potential>m_manashieldamt)
		potential = m_manashieldamt;

	if((int32)dmg<potential)
		potential = dmg;

	uint32 cost = (potential*(100+effectbonus))/50;

	SetUInt32Value(UNIT_FIELD_POWER1,mana-cost);
	m_manashieldamt -= potential;
	if(!m_manashieldamt)
		RemoveAura(m_manaShieldId);
	return potential;	
}

// grep: Remove any AA spells that aren't owned by this player.
//		 Otherwise, if he logs out and in and joins another group,
//		 he'll apply it to them.
/*
void Unit::RemoveAllAreaAuras()
{
	AuraList::iterator itr,it1;
	for(itr = m_auras.begin();itr!=m_auras.end();)
	{
		it1 = itr++;
		if(((*it1)->m_spellProto->Effect[0] == SPELL_EFFECT_APPLY_AREA_AURA ||
			(*it1)->m_spellProto->Effect[1] == SPELL_EFFECT_APPLY_AREA_AURA ||
			(*it1)->m_spellProto->Effect[2] == SPELL_EFFECT_APPLY_AREA_AURA) && (*it1)->GetCaster() != this)
		{
			(*it1)->Remove();
			m_auras.erase(it1);
		} 
	}
}
*/
int32 Unit::AbsorbDamage( uint32 School, uint32* dmg )
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( dmg == NULL )
		return 0;

	if( School >= SPELL_SCHOOL_COUNT )
		return 0;
	
	if( bInvincible )
	{
		uint32 ret = *dmg;
		*dmg = 0;
		return ret;
	}

	uint32 abs = 0;
	CommitPointerListNode<Absorb> *i;
	Absorbs.BeginLoop();
	for( i = Absorbs.begin(); i != Absorbs.end(); i = i->Next() )
	{
		Absorb *tabs = i->data;
		if(tabs->schools[ School ] )
		{
			uint32 toabsorb = *dmg;
			if( tabs->MaxAbsorbCoeff )
			{
				float coef = tabs->MaxAbsorbCoeff;	//this is smaller then 1 !
				float tdmg = (float)(*dmg);
				toabsorb = float2int32(coef*tdmg);
			}
			if( tabs->MaxAbsorbPerHit < toabsorb )
				toabsorb = tabs->MaxAbsorbPerHit;
			// toabsorb <= dmg
			if( (int32)toabsorb >= tabs->amt )//remove this absorb
			{
				//decrease dmg with amount max we can absorb
				(*dmg) -= tabs->amt;
				abs += tabs->amt;
				tabs->amt = 0;			//mark to delte us

				RemoveAura( tabs->spellid );
//				Absorbs.erase( i );		//also made in remove aura
				if(!*dmg)//absorbed all dmg
					break;		
			}
			else //absorb "full" dmg - well sometimes there is a fallthrough
			{
				abs += toabsorb;
				tabs->amt -= toabsorb;
				*dmg -= toabsorb;	//0 most of the time but can be maxabsorb or falltrough
				break;
			}
		}
	}
	Absorbs.EndLoopAndCommit();

	return abs;
}

bool Unit::setDetectRangeMod(const uint64 &guid, int32 amount)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	int next_free_slot = -1;
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == 0 && next_free_slot == -1)
		{
			next_free_slot = i;
		}
		if(m_detectRangeGUID[i] == guid)
		{
			m_detectRangeMOD[i] = amount;
			return true;
		}
	}
	if(next_free_slot != -1)
	{
		m_detectRangeGUID[next_free_slot] = guid;
		m_detectRangeMOD[next_free_slot] = amount;
		return true;
	}
	return false;
}

void Unit::unsetDetectRangeMod(const uint64 &guid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == guid)
		{
			m_detectRangeGUID[i] = 0;
			m_detectRangeMOD[i] = 0;
		}
	}
}

int32 Unit::getDetectRangeMod(const uint64 &guid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(int i = 0; i < 5; i++)
	{
		if(m_detectRangeGUID[i] == guid)
		{
			return m_detectRangeMOD[i];
		}
	}
	return 0;
}

void Unit::SetStandState(uint8 standstate)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	//only take actions if standstate did change.
	StandState bef = GetStandState();
	if( bef == standstate )
	{ 
		return;
	}

	SetByte( UNIT_FIELD_BYTES_1, 0, standstate );
	if( standstate == STANDSTATE_STAND )//standup
		RemoveAurasByInterruptFlag(AURA_INTERRUPT_ON_STAND_UP);

	if( m_objectTypeId == TYPEID_PLAYER )
		SafePlayerCast( this )->GetSession()->OutPacket( SMSG_STANDSTATE_UPDATE, 1, &standstate );
}

void Unit::RemoveAurasByInterruptFlag(uint32 flag)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	Aura * a;
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
	{
		a = m_auras[x];
		if(a == NULL)
			continue;
		
		//some spells do not get removed all the time only at specific intervals
		if((a->m_spellProto->AuraInterruptFlags & flag) && !(a->m_spellProto->procFlags2 & PROC2_REMOVEONUSE))
		{
			a->Remove();
//			m_auras[x] = NULL;	//remove might trigger aura add and put it in same slot as the removed one. Do not use this !
		}
	}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
	{
		a = m_auras[x];
		if(a == NULL)
			continue;
		
		//some spells do not get removed all the time only at specific intervals
		if((a->m_spellProto->AuraInterruptFlags & flag) && !(a->m_spellProto->procFlags2 & PROC2_REMOVEONUSE))
		{
			a->Remove();
//			m_auras[x] = NULL;	//remove might trigger aura add and put it in same slot as the removed one. Do not use this !
		}
	}
}

bool Unit::HasAura(uint32 spellid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()== spellid)
		{ 
			return true;
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()== spellid)
		{ 
			return true;
		}
	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()== spellid)
		{ 
			return true;
		}

		return false;
}

uint32 Unit::CountNegAuraWithNamehash(uint32 namehash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	uint32 count=0;
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == namehash)
			count++;

	return count;
}

void Unit::DropAurasOnDeath()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<MAX_AURAS;x++)
        if(m_auras[x])
        {
            if(	(m_auras[x]->GetSpellProto()->AttributesExC & CAN_PERSIST_AND_CASTED_WHILE_DEAD)
				&& m_auras[x]->IsPositive() )
                continue;
            else
		        m_auras[x]->Remove();
        }
}

void Unit::UpdateSpeed()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(GetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID) == 0)
	{
		if(IsPlayer())
			m_runSpeed = m_base_runSpeed*(1.0f + ((float)m_speedModifier)/100.0f);
		else
		{
			m_runSpeed = m_base_runSpeed*(1.0f + ((float)m_speedModifier)/100.0f);
			AIInterface *tai = GetAIInterface();
			if( tai )
			{
				tai->m_walkSpeed = m_walkSpeed*0.001f;//move distance per ms time 
				tai->m_runSpeed = m_runSpeed*0.001f;//move/ms
				tai->m_flySpeed = m_flySpeed*0.001f;
			}
		}
	}
	else
	{
		if(IsPlayer())
		{
			m_runSpeed = m_base_runSpeed*(1.0f + ((float)m_mountedspeedModifier)/100.0f);
			m_runSpeed += (m_speedModifier<0) ? (m_base_runSpeed*((float)m_speedModifier)/100.0f) : 0;
		}
		else
		{
			m_runSpeed = m_base_runSpeed*(1.0f + ((float)m_mountedspeedModifier)/100.0f);
			m_runSpeed += (m_speedModifier<0) ? (m_base_runSpeed*((float)m_speedModifier)/100.0f) : 0;
			AIInterface *tai = GetAIInterface();
			if( tai )
			{
				tai->m_walkSpeed = m_walkSpeed*0.001f;//move distance per ms time 
				tai->m_runSpeed = m_runSpeed*0.001f;//move/ms
				tai->m_flySpeed = m_flySpeed*0.001f;
			}
		}
	}

	

	m_flySpeed = PLAYER_NORMAL_FLIGHT_SPEED*(1.0f + ((float)m_flyspeedModifier)/100.0f);

	// Limit speed due to effects such as http://www.wowhead.com/?spell=31896 [Judgement of Justice]
	if( m_maxSpeed && m_runSpeed > m_maxSpeed )
	{
		m_runSpeed = m_maxSpeed;
	}

	if(IsPlayer())
	{
		if(SafePlayerCast(this)->m_changingMaps)
			SafePlayerCast( this )->resend_speed = true;
		else
		{
			SafePlayerCast( this )->SetPlayerSpeed(RUN, m_runSpeed);
			SafePlayerCast( this )->SetPlayerSpeed(FLY, m_flySpeed);
		}
	}
}

bool Unit::HasActiveAura(uint32 spellid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellid)
		{ 
			return true;
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellid)
		{ 
			return true;
		}

	return false;
}

bool Unit::HasNegAuraWithMechanic(uint32 mechanic)
{
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if( m_auras[x] && m_auras[x]->GetSpellProto()->MechanicsType == mechanic )
		{ 
			return true;
		}

	return false;
}

bool Unit::HasAuraWithMechanic(uint32 mechanic)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if( m_auras[x] && m_auras[x]->GetSpellProto()->MechanicsType == mechanic )
		{ 
			return true;
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if( m_auras[x] && m_auras[x]->GetSpellProto()->MechanicsType == mechanic )
		{ 
			return true;
		}

	return false;
}

bool Unit::HasActiveAura(uint32 spellid,const uint64 &guid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellid && m_auras[x]->m_casterGuid==guid)
		{ 
			return true;
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellId()==spellid && m_auras[x]->m_casterGuid==guid)
		{ 
			return true;
		}

	return false;
}

void Unit::EventSummonPetExpire()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(summonPet)
	{
		if(summonPet->GetEntry() == 7915)//Goblin Bomb
		{
			SpellEntry *spInfo = dbcSpell.LookupEntry(13259);
			if(!spInfo)
			{ 
				return;
			}

			Spell*sp=SpellPool.PooledNew();
			sp->Init(summonPet,spInfo,true,NULL);
			SpellCastTargets tgt;
			tgt.m_unitTarget=summonPet->GetGUID();
			sp->prepare(&tgt);
		}
		else
		{
			summonPet->RemoveFromWorld(false, true);
			sGarbageCollection.AddObject( summonPet );
			summonPet = NULL;
		}
	}
	sEventMgr.RemoveEvents(this, EVENT_SUMMON_PET_EXPIRE);
}

uint8 Unit::CastSpell(Unit* Target, SpellEntry* Sp, bool triggered)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( Sp == NULL )
	{ 
		return SPELL_FAILED_UNKNOWN;
	}

	Spell *newSpell = SpellPool.PooledNew();
	newSpell->Init(this, Sp, triggered, 0);
	SpellCastTargets targets(0);
	if(Target)
	{
		targets.m_targetMask |= TARGET_FLAG_UNIT;
		targets.m_unitTarget = Target->GetGUID();
	}
	else
	{
		newSpell->GenerateTargets(&targets);
	}
	return newSpell->prepare(&targets);
}

uint8 Unit::CastSpell(Unit* Target, uint32 SpellID, bool triggered)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	SpellEntry * ent = dbcSpell.LookupEntry(SpellID);
	if(ent == NULL) 
	{ 
		return SPELL_FAILED_UNKNOWN;
	}

	return CastSpell(Target, ent, triggered);
}

uint8 Unit::CastSpell(const uint64 &targetGuid, SpellEntry* Sp, bool triggered)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( Sp == NULL )
	{ 
		return SPELL_FAILED_UNKNOWN;
	}

	SpellCastTargets targets(targetGuid);
	Spell *newSpell = SpellPool.PooledNew();
	newSpell->Init(this, Sp, triggered, 0);
	return newSpell->prepare(&targets);
}

uint8 Unit::CastSpell(uint64 targetGuid, uint32 SpellID, bool triggered)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	SpellEntry * ent = dbcSpell.LookupEntry(SpellID);
	if(ent == 0) 
	{ 
		return SPELL_FAILED_UNKNOWN;
	}

	return CastSpell(targetGuid, ent, triggered);
}
void Unit::CastSpellAoF(float x,float y,float z,SpellEntry* Sp, bool triggered)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( Sp == NULL )
	{ 
		return;
	}

	SpellCastTargets targets;
	targets.m_destX = x;
	targets.m_destY = y;
	targets.m_destZ = z;
	targets.m_targetMask=TARGET_FLAG_DEST_LOCATION;
	Spell *newSpell = SpellPool.PooledNew();
	newSpell->Init(this, Sp, triggered, 0);
	newSpell->prepare(&targets);
}

void Unit::PlaySpellVisual(const uint64 &target, uint32 spellVisual)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	WorldPacket data(SMSG_PLAY_SPELL_VISUAL, 12);
	data << target << spellVisual;
	SendMessageToSet(&data, true);
}

void Unit::Root()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	this->m_special_state |= UNIT_STATE_ROOT;

	if(m_objectTypeId == TYPEID_PLAYER)
	{
		SafePlayerCast( this )->SetMovement(MOVE_ROOT);
	}
	else
	{
		m_aiInterface->m_canMove = false;
		m_aiInterface->StopMovement(1);
	}
}

void Unit::Unroot()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	this->m_special_state &= ~UNIT_STATE_ROOT;

	if(m_objectTypeId == TYPEID_PLAYER)
	{
		SafePlayerCast( this )->SetMovement(MOVE_UNROOT);
	}
	else
	{
		m_aiInterface->m_canMove = true;
	}
}

void Unit::RemoveAurasByBuffType(uint32 buff_type, const uint64 &guid, uint32 skip, bool skip_caster_check)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( skip_caster_check == true || guid == 0 )
	{
		for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
			if(m_auras[x] && (m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & buff_type) && m_auras[x]->GetSpellId()!=skip)
					m_auras[x]->Remove();
		for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
			if(m_auras[x] && (m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & buff_type) && m_auras[x]->GetSpellId()!=skip)
					m_auras[x]->Remove();
		//windfury is passive :(
		for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
			if(m_auras[x] && (m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & buff_type) && m_auras[x]->GetSpellId()!=skip)
					m_auras[x]->Remove();
	}
	else
	{
		for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
			if(m_auras[x] && (m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & buff_type) && m_auras[x]->GetSpellId()!=skip)
				if(m_auras[x]->m_casterGuid == guid)
					m_auras[x]->Remove();
		for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
			if(m_auras[x] && (m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & buff_type) && m_auras[x]->GetSpellId()!=skip)
				if(m_auras[x]->m_casterGuid == guid)
					m_auras[x]->Remove();
		//windfury is passive :(
		for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
			if(m_auras[x] && (m_auras[x]->GetSpellProto()->BGR_one_buff_on_target & buff_type) && m_auras[x]->GetSpellId()!=skip)
					m_auras[x]->Remove();
	}
}

void Unit::RemoveAurasByBuffIndexType(uint32 buff_index_type, const uint64 &guid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->BGR_one_buff_from_caster_on_1target == buff_index_type)
			if(!guid || (guid && m_auras[x]->m_casterGuid == guid))
				m_auras[x]->Remove();
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->BGR_one_buff_from_caster_on_1target == buff_index_type)
			if(!guid || (guid && m_auras[x]->m_casterGuid == guid))
				m_auras[x]->Remove();
}

AuraCheckResponse Unit::AuraCheck(Aura *new_aura, Aura *old_aura, uint32 MaxStackNow)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	AuraCheckResponse resp;

	if( new_aura == NULL || old_aura == NULL 
		|| new_aura->GetSpellProto()->NameHash != old_aura->GetSpellProto()->NameHash //compare auras of same type only
//		|| new_aura->GetSpellProto()->activeIconID == 0		//non visible auras always stack ?
		|| old_aura->m_visualSlot > MAX_VISIBLE_AURAS		//invisible auras stack
		|| MaxStackNow > m_auraStackCount[ old_aura->m_visualSlot ] //they could still stack more
		|| new_aura->GetSpellProto()->maxstack != old_aura->GetSpellProto()->maxstack //stacking rule does not match
		|| ( new_aura->m_casterGuid != old_aura->m_casterGuid && (old_aura->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_DAMAGING) != 0 )//damaging spells always stack if not from same caster
		)
	{
		resp.Error = AURA_CHECK_RESULT_NONE;
//		resp.Misc  = 0;
		return resp;
	}
	resp.Error = AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT;
	uint32 min_modcount = MIN(MIN( new_aura->m_modcount, old_aura->m_modcount ),MAX_AURA_MOD_COUNT);
	for( uint32 i=0;i<min_modcount;i++)
		if( new_aura->m_modList[i].m_amount > old_aura->m_modList[i].m_amount )
		{
			resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;
			break;
		}
	if( 
		resp.Error == AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT										//not decided strength yet
		&& new_aura->GetSpellProto()->NameHash == old_aura->GetSpellProto()->NameHash			//compare auras of same type only
		&& old_aura->m_visualSlot < MAX_VISIBLE_AURAS											//invisible auras stack
		//aura has not yet been added, no visual slot
		&& new_aura->IsVisible() == true														//proc spells, 1 is visible the one is not
		&& ( (old_aura->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_DAMAGING) == 0				//damaging spells always stack if not from same caster
				|| new_aura->m_casterGuid == old_aura->m_casterGuid )
		&& MaxStackNow <= m_auraStackCount[ old_aura->m_visualSlot ]	//they could still stack more
		&& new_aura->GetSpellProto()->maxstack == old_aura->GetSpellProto()->maxstack			//stacking rule must match
		)
	{
		resp.Error = AURA_CHECK_RESULT_CANNOT_STACK;
//		resp.Misc  = 0;
		return resp;
	}
	return resp;
}

AuraCheckResponse Unit::AuraCheck(uint32 name_hash, uint32 rank, Object *caster)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	AuraCheckResponse resp;

	// no error for now
	resp.Error = AURA_CHECK_RESULT_NONE;
//	resp.Misc  = 0;

	// look for spells with same namehash
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
	{
//		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash && m_auras[x]->GetCaster()==caster)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash
			//check if we can stack it more
			&& (m_auras[x]->GetSpellProto()->maxstack < 1 || m_auras[x]->m_visualSlot > MAX_VISIBLE_AURAS || m_auras[x]->GetSpellProto()->maxstack <= m_auraStackCount[ m_auras[x]->m_visualSlot ] )
			)
		{
			// we've got an aura with the same name as the one we're trying to apply
//			resp.Misc = m_auras[x]->GetSpellProto()->Id;

			// compare the rank to our applying spell
			if(m_auras[x]->GetSpellProto()->RankNumber > rank)
				resp.Error = AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT;
			else
				resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;

			// we found something, save some loops and exit
			return resp;
		}
	}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
	{
//		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash && m_auras[x]->GetCaster()==caster)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash
			//check if we can stack it more
			&& (m_auras[x]->GetSpellProto()->maxstack < 1 || m_auras[x]->m_visualSlot > MAX_VISIBLE_AURAS || m_auras[x]->GetSpellProto()->maxstack <= m_auraStackCount[ m_auras[x]->m_visualSlot ] )
			)
		{
			// we've got an aura with the same name as the one we're trying to apply
//			resp.Misc = m_auras[x]->GetSpellProto()->Id;

			// compare the rank to our applying spell
			if(m_auras[x]->GetSpellProto()->RankNumber > rank)
				resp.Error = AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT;
			else
				resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;

			// we found something, save some loops and exit
			return resp;
		}
	}

	// return it back to our caller
	return resp;
}
/*
AuraCheckResponse Unit::AuraCheck(uint32 name_hash, uint32 rank, Aura* aur, Object *caster)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	AuraCheckResponse resp;

	// no error for now
	resp.Error = AURA_CHECK_RESULT_NONE;
	resp.Misc  = 0;

	// look for spells with same namehash
//	if(aur->GetSpellProto()->NameHash == name_hash && aur->GetCaster()==caster)
	if(aur->GetSpellProto()->NameHash == name_hash)
	{
		// we've got an aura with the same name as the one we're trying to apply
		resp.Misc = aur->GetSpellProto()->Id;

		// compare the rank to our applying spell
		if(aur->GetSpellProto()->RankNumber > rank)
			resp.Error = AURA_CHECK_RESULT_HIGHER_BUFF_PRESENT;
		else
			resp.Error = AURA_CHECK_RESULT_LOWER_BUFF_PRESENT;
	}

	// return it back to our caller
	return resp;
}*/

void Unit::OnPushToWorld()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<MAX_AURAS + MAX_PASSIVE_AURAS;x++)
		if( m_auras[x] != NULL )
			m_auras[x]->event_Relocate();
}

void Unit::RemoveFromWorld(bool free_guid)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	CombatStatus.OnRemoveFromWorld();
	sHookInterface.OnRemoveFromWorld( this );
	if(critterPet != 0)
	{
		critterPet->RemoveFromWorld(false, true);
		critterPet = 0;
	}
	ExitVehicle();

	if(dynObj != 0)
		dynObj->Remove();

	for(uint32 i = 0; i < 4; ++i)
	{
		if(m_ObjectSlots[i] != 0)
		{
			GameObject * obj = m_mapMgr->GetGameObject(m_ObjectSlots[i]);
			if(obj)
				obj->ExpireAndDelete();

			m_ObjectSlots[i] = 0;
		}
	}

	std::list<uint64>::iterator gitr;
	for( gitr = m_guardians.begin(); gitr != m_guardians.end(); gitr++ )
	{
		Creature *tc = GetMapMgr()->GetCreature( (*gitr) );
		if( tc )
			tc->Despawn( 0, 0 );
	}
	m_guardians.clear();

	//area auras expire when we leave world
	for(uint32 x = FIRST_AURA_SLOT; x < MAX_AURAS+MAX_PASSIVE_AURAS; ++x)
		if( m_auras[x] != NULL )
			m_auras[x]->RemoveAA();	//!! this removes auras only from targets. We ar enot included here !

	Object::RemoveFromWorld(free_guid);

	for(uint32 x = FIRST_AURA_SLOT; x < MAX_AURAS+MAX_PASSIVE_AURAS; ++x)
	{
		if(m_auras[x] != NULL )
		{
			//how can this happen ?
			if( m_auras[x]->m_deleted != 0 )
			{
//				m_auras[x] = NULL;
				printf("!!OMG, this aura is deleted but it is still on player! %d - %s \n",m_auras[x]->GetSpellProto()->Id,m_auras[x]->GetSpellProto()->Name);
				continue;
			}
			//!!!relocate after remove from world
			m_auras[x]->event_Relocate();
		}
	}

	m_aiInterface->WipeReferences();
}

void Unit::RemoveAurasByInterruptFlagButSkip_slot(uint32 flag, uint32 skip,uint32 skiphash,uint32 slot)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	Aura * a;
	a = m_auras[slot];
	//some spells do not get removed all the time only at specific intervals
	if( (a->m_spellProto->AuraInterruptFlags & flag) 
		&& (a->m_spellProto->Id != skip) 
//		&& a->m_spellProto->proc_interval == 0	- why the hell was this put here ?
		)
	{
		//the black sheeps of sociaty
//			if(a->m_spellProto->AuraInterruptFlags & AURA_INTERRUPT_ON_CAST_SPELL)
		{
			switch( a->GetSpellProto()->NameHash )
			{
				case SPELL_HASH_VANISH:
				case SPELL_HASH_STEALTH:
					{
						//do not remove these on poison ticks
						SpellEntry *sp = dbcSpell.LookupEntryForced( skip );
						if( sp && ( sp->c_is_flags & SPELL_FLAG_IS_POISON ) )	//crap, we should know if this is "flag" is comming from other people on us or our speels are ticking on others
//						if( sp && sp->quick_tickcount > 1 )	//DOTs on target does not remove our stealth. Is this a bullshit report ?
							return;
					}break;
			}
			switch(a->GetSpellProto()->Id)
			{
				//paladin divine favor
				case 20216:
					{
						if( skiphash != SPELL_HASH_FLASH_OF_LIGHT 
							&& skiphash != SPELL_HASH_HOLY_LIGHT 
							&& skiphash != SPELL_HASH_HOLY_SHOCK 
							)
						{ 
							return;
						}
					}break;
				//DK : Frost Fever does not remove Hungering Cold
				case 51209:
					{
						if( skip == 55095 )
						{ 
							return;
						}
					}break;
				case 34936:	// Backlash
					{
						if( skiphash != SPELL_HASH_SHADOW_BOLT 
							&& skiphash != SPELL_HASH_INCINERATE
							)
						{ 
							return;
						}
					}break;
				case 17941: //Shadow Trance
					{
						if( skiphash != SPELL_HASH_SHADOW_BOLT )
						{ 
							return;
						}
					}break;
				case 49203: //Hungering Cold
					{
						if( skiphash == SPELL_HASH_FROST_FEVER || skiphash == SPELL_HASH_BLOOD_PLAGUE )
						{
							return;
						}
					}break;
			}
		}
		a->Remove();
	}
}

void Unit::RemoveAurasByInterruptFlagButSkip(uint32 flag, uint32 skip,uint32 skiphash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if( m_auras[x] )
			RemoveAurasByInterruptFlagButSkip_slot(flag,skip,skiphash,x);
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if( m_auras[x] )
			RemoveAurasByInterruptFlagButSkip_slot(flag,skip,skiphash,x);
//	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
//		if( m_auras[x] )
//			RemoveAurasByInterruptFlagButSkip_slot(flag,skip,skiphash,x);
}

void Unit::RemoveAurasByZoneChange()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( !IsPlayer() || !IsInWorld() )
		return; //right now zoning is not made for non players :(
//	uint16 plrarea = SafePlayerCast(this)->GetMapMgr()->GetAreaID( GetPositionX(), GetPositionY() );
    uint16 plrarea = sTerrainMgr.GetAreaID( GetMapId(), GetPositionX(), GetPositionY(), GetPositionZ() );
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->RequiresAreaId )
		{
			AreaGroup *ag = dbcAreaGroup.LookupEntry( m_auras[x]->GetSpellProto()->RequiresAreaId );
			if( !ag )
				continue;
			for( uint8 i = 0; i < 7; i++ )
				if( ag->AreaId[i] != 0 && ag->AreaId[i] != plrarea )
				{	
				    m_auras[x]->Remove();
					break;
				}
		}
}

void Unit::RemoveDuelAuras()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->WasCastInDuel() )
		    m_auras[x]->Remove();
}

int Unit::HasAurasWithNameHash(uint32 name_hash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
		{ 
			return m_auras[x]->m_spellProto->Id;
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
		{ 
			return m_auras[x]->m_spellProto->Id;
		}
/*	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
			return m_auras[x]->m_spellProto->Id;*/

	return 0;
}

int Unit::HasPosAurasWithNameHash(uint32 name_hash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
		{ 
			return m_auras[x]->m_spellProto->Id;
		}

	return 0;
}

int Unit::HasPassiveAurasWithNameHash(uint32 name_hash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
		{ 
			return m_auras[x]->m_spellProto->Id;
		}
	return 0;
}

bool Unit::HasNegativeAuraWithNameHash(uint32 name_hash)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x = MAX_POSITIVE_AURAS; x < m_auras_neg_size; ++x)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->NameHash == name_hash)
		{ 
			return true;
		}

	return false;
}

bool Unit::HasNegativeAura(uint32 spell_id)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x = MAX_POSITIVE_AURAS; x < m_auras_neg_size; ++x)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->Id == spell_id)
		{ 
			return true;
		}

	return false;
}

uint32 Unit::GetDKDiseaseCount()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	uint32 ret=0;
	ret += HasNegativeAura( 55095 ); //frost feaver
	ret += HasNegativeAura( 55078 ); //blood plague

	return ret;
}

uint32 Unit::CountAura(uint32 spell_id)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	uint32 ret=0;
	for(uint32 x = FIRST_AURA_SLOT; x < m_auras_pos_size; ++x)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->Id == spell_id)
			ret++;
	for(uint32 x = MAX_POSITIVE_AURAS; x < m_auras_neg_size; ++x)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->Id == spell_id)
			ret++;

	return ret;
}

bool Unit::IsPoisoned()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_POISON)
		{ 
			return true;
		}
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_POISON)
		{ 
			return true;
		}
	for(uint32 x=MAX_AURAS;x<m_auras_pas_size;x++)
		if(m_auras[x] && m_auras[x]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_POISON)
		{ 
			return true;
		}

	return false;
}

uint32 Unit::ModVisualAuraStackCount(Aura *aur, int32 count)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( !aur )
	{ 
		sLog.outDebug("ModVisualAuraStackCount : Aura is NULL! Exiting");
		return 0;
	}

	uint16 slot = aur->m_visualSlot;

	if( slot >= MAX_VISIBLE_AURAS)
	{ 
		sLog.outDebug("ModVisualAuraStackCount : Aura visual slot is invalid! Exiting");
		return 0;
	}

	if(count < 0 && m_auraStackCount[slot] <= -count )
	{
		m_auraStackCount[ slot ] = 0;
		sStackWolrdPacket( data, SMSG_AURA_UPDATE, 25);
		data << GetNewGUID();
		data << uint8(slot);
		data << uint32(0);
		SendMessageToSet(&data, true);
	}
	else
	{
		m_auraStackCount[ slot ] += count;
		uint8 flags;
		flags = 0; // do not send guid
		flags |= VISUALAURA_FLAG_VISIBLE_1 | VISUALAURA_FLAG_VISIBLE_2 | VISUALAURA_FLAG_VISIBLE_3; //seems to be always present
		if( aur->m_casterGuid == GetGUID() )
			flags |= VISUALAURA_FLAG_SELF_CAST;
		if( !aur->IsPositive() )
			flags |= VISUALAURA_FLAG_NEGATIVE; 
		else
			flags |= VISUALAURA_FLAG_REMOVABLE;
		if( aur->GetDuration() != (uint32)-1 ) //yes it is stupid to force -1 to be uint32 but that is the way it is made elsewhere
			flags |= VISUALAURA_FLAG_HAS_DURATION; 

		//only send negative auras for creatures
//		if( (!aur->IsPositive() && IsCreature()) || IsPet() || IsPlayer() )
		{
			sStackWolrdPacket( data, SMSG_AURA_UPDATE, 50 );
			data << GetNewGUID();
			data << uint8(slot);
			data << uint32(aur->GetSpellId());
			data << (uint8)flags;
			data << (uint8)(aur->GetSpellProto()->maxLevel);
			data << uint8(m_auraStackCount[slot]);

			//flag 0x8 is the non self buff- Does not seem to be true, found spell that does not have this flag but has no guid either
			// maybe it is a combination of flags that makes it to be sent
			if( (flags & VISUALAURA_FLAG_SELF_CAST)==0 )
				FastGUIDPack(data, aur->m_casterGuid);

			//seems like this depends on flag 0x20
			if( (flags & VISUALAURA_FLAG_HAS_DURATION) )
				data << uint32(aur->GetDuration()) << uint32(aur->GetTimeLeft());
			SendMessageToSet(&data, true);
		}
	}

	return m_auraStackCount[slot];
}

void Unit::SendAllAurasToPlayer(uint32 GUID)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( !GetMapMgr() )
		return; //not in world anymore ?
	Player *plr = GetMapMgr()->GetPlayer( GUID );
	SendAurasToPlayer( plr );

	//need to move this to a new function. But it's 1 AM ..:(
	if( plr && IsPlayer() )
	{
		Player *pPlayer = SafePlayerCast( this );
		if( plr->GetVehicle() && plr->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VEHICLE) )
		{
			sStackWolrdPacket( data, SMSG_CONVERT_VEHICLE, 9+4);
			data << plr->GetNewGUID() ;
			data << uint32( plr->GetCurrentVehicleID() );
			pPlayer->GetSession()->SendPacket( &data );
		}
		if( pPlayer->GetVehicle() && pPlayer->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_VEHICLE) )
		{
			sStackWolrdPacket( data, SMSG_CONVERT_VEHICLE, 9+4);
			data << pPlayer->GetNewGUID() ;
			data << uint32( pPlayer->GetCurrentVehicleID() );
			plr->GetSession()->SendPacket( &data );
		}
	}
}

inline void AddVisualAuraToPacket( Unit *u, Aura *aur, StackWorldPacket &data )	
{	
	if( aur	
		&& aur->m_visualSlot < MAX_VISIBLE_AURAS		
		&& aur->m_modcount != 0	//these are charges for charge spells that have no effect other then visual placeholder	
		)
	{	
		data << (uint8)aur->m_visualSlot; //slot	
		data << aur->GetSpellId(); //spell		

		uint8 flags;	
		flags = 0; // do not send guid	
		flags |= VISUALAURA_FLAG_VISIBLE_1 | VISUALAURA_FLAG_VISIBLE_2 | VISUALAURA_FLAG_VISIBLE_3; //seems to be always present	
		if( aur->m_casterGuid == u->GetGUID() )	
			flags |= VISUALAURA_FLAG_SELF_CAST;	

		if( !aur->IsPositive() )	
			flags |= VISUALAURA_FLAG_NEGATIVE; 
		else	
			flags |= VISUALAURA_FLAG_REMOVABLE;	
		if( aur->GetDuration() != (uint32)-1 ) //yes it is stupid to force -1 to be uint32 but that is the way it is made elsewhere 
			flags |= VISUALAURA_FLAG_HAS_DURATION;	

		data << (uint8)flags;	
		data << (uint8)(aur->GetSpellProto()->maxLevel);	//might need to send aura caster serialization here and not ours !	
		data << uint8( u->m_auraStackCount[ aur->m_visualSlot ] );	

		if( (flags & VISUALAURA_FLAG_SELF_CAST)==0 )	
			FastGUIDPack(data, aur->m_casterGuid);	

		//seems like this depends on flag 0x20	
		if( (flags & VISUALAURA_FLAG_HAS_DURATION) )	
			data << uint32(aur->GetDuration()) << uint32(aur->GetTimeLeft());	
	}	
}	


void Unit::SendAurasToPlayer(Player *plr)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE

	if( !plr )
	{ 
		return;
	}

//	uint16 send_flags;
//	if( !IsPlayer() && !IsPet() )
//		send_flags = VISUALAURA_FLAG_NEGATIVE; //send only negative buffs for mobs
//	else 
//		send_flags = 0xFF;

	sStackWolrdPacket(data,SMSG_AURA_UPDATE_ALL,(MAX_AURAS+MAX_PASSIVE_AURAS) * 25 + 8);
	data << GetNewGUID();
	for( uint32 i=POS_AURAS_START; i<MAX_POSITIVE_AURAS1(this); i++ )
		AddVisualAuraToPacket(this,m_auras[i],data);
	for( uint32 i=NEG_AURAS_START; i<MAX_NEGATIVE_AURAS1(this); i++ )
		AddVisualAuraToPacket(this,m_auras[i],data);
	for( uint32 i=PAS_AURAS_START; i<MAX_PASSIVE_AURAS1(this); i++ )
		AddVisualAuraToPacket(this,m_auras[i],data);

	if( data.GetSize() > 8 )
		plr->GetSession()->SendPacket( &data );
}

void Unit::RemoveAurasOfSchool(uint32 School, bool Positive, bool Immune)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( Positive )
		for(uint32 x=FIRST_AURA_SLOT;x<m_auras_pos_size;x++)
			if(m_auras[x]  && m_auras[x]->GetSpellProto()->School == School && (Immune==false || (m_auras[x]->GetSpellProto()->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY)==0 ) )
				m_auras[x]->Remove();
	for(uint32 x=MAX_POSITIVE_AURAS;x<m_auras_neg_size;x++)
		if(m_auras[x]  && m_auras[x]->GetSpellProto()->School == School && (Immune==false || (m_auras[x]->GetSpellProto()->Attributes & ATTRIBUTES_IGNORE_INVULNERABILITY)==0 ) )
			m_auras[x]->Remove();
}

void Unit::EnableFlight()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(m_objectTypeId != TYPEID_PLAYER || SafePlayerCast(this)->m_changingMaps)
	{
		WorldPacket data(SMSG_MOVE_SET_CAN_FLY, 13);
		data << GetNewGUID();
		data << uint32(2);
		SendMessageToSet(&data, true);

		if( IsPlayer() )
		{
			SafePlayerCast( this )->m_setflycheat = true;
		}
	}
	else
	{
		WorldPacket * data = new WorldPacket(SMSG_MOVE_SET_CAN_FLY, 13);
		*data << GetNewGUID();
		*data << uint32(2);
		SendMessageToSet(data, false);
		SafePlayerCast( this )->z_axisposition = 0.0f;
		SafePlayerCast( this )->delayedPackets.add( data );
		SafePlayerCast( this )->m_setflycheat = true;
	}
}

void Unit::DisableFlight()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(m_objectTypeId != TYPEID_PLAYER || SafePlayerCast(this)->m_changingMaps)
	{
		WorldPacket data(SMSG_MOVE_UNSET_CAN_FLY, 13);
		data << GetNewGUID();
		data << uint32(5);
		SendMessageToSet(&data, true);

		if( IsPlayer() )
			SafePlayerCast( this )->m_setflycheat = false;
	}
	else
	{
		WorldPacket * data = new WorldPacket( SMSG_MOVE_UNSET_CAN_FLY, 13 );
		*data << GetNewGUID();
		*data << uint32(5);
		SendMessageToSet(data, false);
		SafePlayerCast( this )->z_axisposition = 0.0f;
		SafePlayerCast( this )->delayedPackets.add( data );
		SafePlayerCast( this )->m_setflycheat = false;
	}
}

bool Unit::IsDazed()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
/*	for(uint32 x = FIRST_AURA_SLOT; x < m_auras_pos_size; ++x)
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ENSNARED)
				return true;
			for(uint32 y=0;y<3;y++)
				if(m_auras[x]->GetSpellProto()->EffectMechanic[y]==MECHANIC_ENSNARED)
					return true;
		}*/
	for(uint32 x = MAX_POSITIVE_AURAS; x < m_auras_neg_size; ++x)
		if(m_auras[x])
		{
			if(m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ENSNARED)
			{ 
				return true;
			}
			for(uint32 y=0;y<3;y++)
				if(m_auras[x]->GetSpellProto()->EffectMechanic[y]==MECHANIC_ENSNARED)
				{ 
					return true;
				}
		}

	return false;

}

void Unit::UpdateVisibility()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	ByteBuffer buf(2500);
	InRangeSet::iterator itr, it3;
	uint32 count;
	bool can_see;
	bool is_visible;
	Player *pl;
	Object * pObj;
	Player * plr;

	if( m_objectTypeId == TYPEID_PLAYER )
	{
		plr = SafePlayerCast( this );
		for( itr = m_objectsInRange.begin(); itr != m_objectsInRange.end();)
		{
			pObj = (*itr);
			++itr;

			can_see = plr->CanSee(pObj);
			is_visible = plr->GetVisibility(pObj, &it3);
			if(can_see)
			{
				if(!is_visible)
				{
					buf.clear();
					count = pObj->BuildCreateUpdateBlockForPlayer( &buf, plr );
					plr->PushCreationData(&buf, count);
					plr->AddVisibleObject(pObj);
				}
			}
			else
			{
				if(is_visible)
				{
//					pObj->DestroyForPlayer(plr);
					plr->PushOutOfRange( pObj->GetGUID() );
					plr->RemoveVisibleObject(it3);
				}
			}

			if( pObj->GetTypeId() == TYPEID_PLAYER )
			{
				pl = SafePlayerCast( pObj );
				can_see = pl->CanSee( plr );
				is_visible = pl->GetVisibility( plr, &it3 );
				if( can_see )
				{
					if(!is_visible)
					{
						buf.clear();
						count = plr->BuildCreateUpdateBlockForPlayer( &buf, pl );
						pl->PushCreationData(&buf, count);
						pl->AddVisibleObject(plr);
					}
				}
				else
				{
					if(is_visible)
					{
//						plr->DestroyForPlayer(pl);
						pl->PushOutOfRange( plr->GetGUID() );
						pl->RemoveVisibleObject(it3);
					}
				}
			}
		}
	}
	else			// For units we can save a lot of work
	{
		for(set<Player*>::iterator it2 = GetInRangePlayerSetBegin(); it2 != GetInRangePlayerSetEnd(); ++it2)
		{
			can_see = (*it2)->CanSee(this);
			is_visible = (*it2)->GetVisibility(this, &itr);
			if(!can_see)
			{
				if(is_visible)
				{
//					DestroyForPlayer(*it2);
					(*it2)->PushOutOfRange( GetGUID() );
					(*it2)->RemoveVisibleObject(itr);
				}
			}
			else
			{
				if(!is_visible)
				{
					buf.clear();
					count = BuildCreateUpdateBlockForPlayer(&buf, *it2);
					(*it2)->PushCreationData(&buf, count);
					(*it2)->AddVisibleObject(this);
				}
			}
		}
	}
}

void Unit::RemoveSoloAura(uint32 type)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	switch(type)
	{
		case 1:// Polymorph
		{
			if(!polySpell) 
			{ 
				return;
			}
			if(HasActiveAura(polySpell))
				RemoveAura(polySpell);
		}break;
/*		case 2:// Sap
		{
			if(!sapSpell) return;
			if(HasActiveAura(sapSpell))
				RemoveAura(sapSpell);
		}break;
		case 3:// Fear (Warlock)
		{
			if(!fearSpell) return;
			if(HasActiveAura(fearSpell))
				RemoveAura(fearSpell);
		}break;*/
		default:
			{
			sLog.outDebug("Warning: we are trying to remove a soloauratype that has no handle");
			}break;
	}
}

void Unit::EventHealthChangeSinceLastUpdate()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	int pct = GetHealthPct();

	if( IsPlayer() )
	{
		if( getClass() == MAGE )
		{
			Player *plr = SafePlayerCast( this );
			uint32 proc_spell = 0;
			//hackfix for Mage talent !!! Fiery Payback
			if( pct < 35 )
			{
				//add once
				if( !HasFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_HEALTH_BELOW_35_PCT ) )
				{
					if( plr->HasSpell( 44440 ) )
						proc_spell = 44440;
					else if( plr->HasSpell( 44441 ) )
						proc_spell = 44441;
				}
				if( proc_spell )
				{
					SpellCastTargets targets( GetGUID() );
					SpellEntry *spellInfo = dbcSpell.LookupEntry( proc_spell );
					Spell *spell = SpellPool.PooledNew();
					spell->Init(this, spellInfo ,true, NULL);
					spell->prepare(&targets);
				}
			}
			//remove once if it was added
			else if( HasFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_HEALTH_BELOW_35_PCT ) )
			{
				RemoveAllAuras( 44440, GetGUID() );
				RemoveAllAuras( 44441, GetGUID() );
			}
		}
		else if( getClass() == DEATHKNIGHT )
		{
			Player *plr = SafePlayerCast( this );
			uint32 proc_spell = 0;
			//hackfix for DK talent !!! Will of the Necropolis
			if( pct < 35 )
			{
				if( !HasFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_HEALTH_BELOW_35_PCT ) )
				{
					if( plr->HasSpell( 49189 ) )
						proc_spell = 52284;
					else if( plr->HasSpell( 50149 ) )
						proc_spell = 52285;
					else if( plr->HasSpell( 50150 ) )
						proc_spell = 52286;
				}
			}
			else if( HasFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_HEALTH_BELOW_35_PCT ) )
			{
				RemoveAllAuras( 52284, GetGUID() );
				RemoveAllAuras( 52285, GetGUID() );
				RemoveAllAuras( 52286, GetGUID() );
			}

			//hackfix for DK talent Blood Gorged
			if( pct > 75 )
			{
				//hp is above 75% and we did not set the flag yet
				if( !HasFlag(UNIT_FIELD_AURASTATE,AURASTATE_HEALTH_ABOVE_75_PCT ) )
				{
					if( plr->HasSpell( 61154 ) )
						proc_spell = 50096;
					else if( plr->HasSpell( 61155 ) )
						proc_spell = 50108;
					else if( plr->HasSpell( 61156 ) )
						proc_spell = 50109;
					else if( plr->HasSpell( 61157 ) )
						proc_spell = 50110;
					else if( plr->HasSpell( 61158 ) )
						proc_spell = 50111;
				}
			}
			//HP is below 75%, if we did not cast the spell yet then we cast it now
			else if( HasFlag(UNIT_FIELD_AURASTATE,AURASTATE_HEALTH_ABOVE_75_PCT ) )
			{
				RemoveAllAuras( 50096, GetGUID() );
				RemoveAllAuras( 50108, GetGUID() );
				RemoveAllAuras( 50109, GetGUID() );
				RemoveAllAuras( 50110, GetGUID() );
				RemoveAllAuras( 50111, GetGUID() );
			}
			if( proc_spell )
			{
				SpellCastTargets targets( GetGUID() );
				SpellEntry *spellInfo = dbcSpell.LookupEntry( proc_spell );
				Spell *spell = SpellPool.PooledNew();
				spell->Init(this, spellInfo ,true, NULL);
				spell->prepare(&targets);
			}
		}
	}

	if(pct<75)
	{
		if(pct<35)
		{
			if(pct<20)
				SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_HEALTH_BELOW_20_PCT);
			else
				RemoveFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_HEALTH_BELOW_20_PCT);

			SetFlag(UNIT_FIELD_AURASTATE,AURASTATE_FLAG_HEALTH_BELOW_35_PCT);
		}
		else
			RemoveFlag(UNIT_FIELD_AURASTATE , AURASTATE_FLAG_HEALTH_BELOW_35_PCT | AURASTATE_FLAG_HEALTH_BELOW_20_PCT);
		RemoveFlag(UNIT_FIELD_AURASTATE , AURASTATE_HEALTH_ABOVE_75_PCT);
	}
	else
	{
		SetFlag(UNIT_FIELD_AURASTATE , AURASTATE_HEALTH_ABOVE_75_PCT);
		RemoveFlag(UNIT_FIELD_AURASTATE , AURASTATE_FLAG_HEALTH_BELOW_35_PCT | AURASTATE_FLAG_HEALTH_BELOW_20_PCT);
	}
}

int32 Unit::GetAP()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
    int32 baseap = GetUInt32Value(UNIT_FIELD_ATTACK_POWER) + GetUInt32Value(UNIT_FIELD_ATTACK_POWER_MODS);
    float totalap = float(baseap)*(GetFloatValue(UNIT_FIELD_ATTACK_POWER_MULTIPLIER)+1);
	if(totalap>=0)
	{ 
		return float2int32(totalap);
	}
	return	0;
}

int32 Unit::GetRAP()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
    int32 baseap = GetUInt32Value(UNIT_FIELD_RANGED_ATTACK_POWER) + GetUInt32Value(UNIT_FIELD_RANGED_ATTACK_POWER_MODS);
    float totalap = float(baseap)*(GetFloatValue(UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER)+1);
	if(totalap>=0)
	{ 
		return float2int32(totalap);
	}
	return	0;
}

bool Unit::GetSpeedDecrease()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	int32 before=m_speedModifier;
	m_speedModifier -= m_slowdown;
	m_slowdown = 0;
	SimplePointerListNode< Modifier > *itr;
	for(itr = speedReductionMap.begin(); itr != speedReductionMap.end(); itr = itr->Next() )
		m_slowdown = MIN( m_slowdown, itr->data->m_amount );

	if(m_slowdown<-100)
		m_slowdown = -100; //do not walk backwards !

	m_speedModifier += m_slowdown;
	//save bandwidth :P
	if(m_speedModifier!=before)
	{ 
		return true;
	}
	return false;
}

bool Unit::GetSpeedIncrease()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	int32 before=m_speedModifier;
	m_speedModifier -= m_speedup;
	m_speedup = 0;

	SimplePointerListNode< Modifier > *itr;
	for(itr = speedIncreaseMap.begin(); itr != speedIncreaseMap.end(); itr = itr->Next() )
		m_speedup = MAX( m_speedup, itr->data->m_amount );

	m_speedModifier += m_speedup;
	//save bandwidth :P
	if(m_speedModifier!=before)
	{ 
		return true;
	}
	return false;
}

void Unit::UpdateSizeMod()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( ObjectSizeMods.HasValues() == false )
	{
		SetFloatValue( OBJECT_FIELD_SCALE_X, 1.0f );
		return;
	}
	int MinScaleDowns = 0,MaxScaleUps = 0;

	SimplePointerListNode< Modifier > *itr;
	for(itr = ObjectSizeMods.begin(); itr != ObjectSizeMods.end(); itr = itr->Next() )
	{
		MinScaleDowns = MIN( MinScaleDowns, itr->data->m_amount );
		MaxScaleUps = MAX( MaxScaleUps, itr->data->m_amount );
	}

	int32 avg = 0, avg_c = 0;
	if( MinScaleDowns < 0 )
	{
		avg = avg + 100 + MinScaleDowns;
		avg_c++;
	}
	if( MaxScaleUps > 0 )
	{
		avg = avg + 100 + MaxScaleUps;
		avg_c++;
	}
	if( avg_c > 0.0f )
		SetFloatValue( OBJECT_FIELD_SCALE_X, (float)avg / (float)avg_c / 100.0f );
}

void Unit::EventCastSpell(Unit * Target, SpellEntry * Sp)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	Spell * pSpell = SpellPool.PooledNew();
	pSpell->Init(Target, Sp, true, NULL);
	SpellCastTargets targets(Target->GetGUID());
	pSpell->prepare(&targets);
}

void Unit::SetFacing(float newo)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	SetOrientation(newo);
	/*WorldPacket data(40);
	data.SetOpcode(MSG_MOVE_SET_FACING);
	data << GetNewGUID();
	data << (uint32)0; //flags
	data << (uint32)0; //time
	data << GetPositionX() << GetPositionY() << GetPositionZ() << newo;
	data << (uint32)0; //unk
	SendMessageToSet( &data, false );*/

	/*WorldPacket data(SMSG_MONSTER_MOVE, 60);
	data << GetNewGUID();
	data << m_position << getMSTime();
	data << uint8(4) << newo;
	data << uint32(0x00000000);		// flags
	data << uint32(0);				// time
	data << m_position;				// position
	SendMessageToSet(&data, true);*/
	
	m_aiInterface->SendMoveToPacket(m_position.x,m_position.y,m_position.z,m_position.o,1,MONSTER_MOVE_FLAG_RUN); // MoveFlags = 0x100 (run)
}

//summons are as guardians but there can only be one of them at a time
Unit* Unit::create_summon(uint32 summon_entry,uint32 duration, uint32 lvl, GameObject * obj, LocationVector * Vec)
{
	RemoveFieldSummon();
	Unit *tguard = create_guardian( summon_entry, duration, lvl, obj, Vec );
	if( tguard )
		SetUInt64Value(UNIT_FIELD_SUMMON, tguard->GetGUID());
	return tguard;
}

//guardians are temporary spawn that will inherit master faction and will folow them. Apart from that they have their own mind
Unit* Unit::create_guardian(uint32 guardian_entry,uint32 duration, uint32 lvl, GameObject * obj, LocationVector * Vec, SpellEntry *CreatedBy)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	CreatureProto * proto = CreatureProtoStorage.LookupEntry(guardian_entry);
	CreatureInfo * info = CreatureNameStorage.LookupEntry(guardian_entry);
	
	if(!proto || !info)
	{
		sLog.outDetail("Warning : Missing summon creature template %u !",guardian_entry);
		return NULL;
	}
	//well this is a really rare case
	if( GetMapMgr() == NULL )
	{
		return NULL;	
	}
	
	Creature* p = GetMapMgr()->CreateCreature(guardian_entry);
	p->SetInstanceID(GetMapMgr()->GetInstanceID());
	p->m_phase = GetPhase();

	//update guardian list and see if we could add more
	std::list<uint64>::iterator gitr,gitr2;
	for( gitr2 = m_guardians.begin(); gitr2 != m_guardians.end();)
	{
		gitr = gitr2;
		gitr2++;
		Creature *tc = GetMapMgr()->GetCreature( (*gitr) );
		if( tc == NULL )
			m_guardians.erase( gitr );
	}
	//avoid creating infinit guardians !
	if( m_guardians.size() > 30 )
		return NULL;
	m_guardians.push_back( p->GetGUID() );

	float m_fallowAngle = GetSummonAngle( p->GetGUID() );
	float x = 3 * ( cosf( m_fallowAngle + GetOrientation() ) );
	float y = 3 * ( sinf( m_fallowAngle + GetOrientation() ) );
	float z = 0;
	
	if( Vec )
	{
		x += Vec->x;
		y += Vec->y;
		z += Vec->z;
		p->Load(proto, x, y, z);	
	}
	//Summoned by a GameObject?
	else if ( !obj ) 
	{
		x += GetPositionX();
		y += GetPositionY();
		z += GetPositionZ();
		p->Load(proto, x, y, z);
	}
	else //if so, we should appear on it's location ;)
	{
		x += obj->GetPositionX();
		y += obj->GetPositionY();
		z += obj->GetPositionZ();
		p->Load(proto, x, y, z);
	}

	uint32 spawn_level;
	if ( lvl != 0 )
		spawn_level = lvl;
	else
		spawn_level = getLevel();

	/* MANA */
	p->SetPowerType(POWER_TYPE_MANA);
	p->SetUInt32Value(UNIT_FIELD_MAXPOWER1,p->GetUInt32Value(UNIT_FIELD_MAXPOWER1)+28+10*spawn_level);
	p->SetUInt32Value(UNIT_FIELD_POWER1,p->GetUInt32Value(UNIT_FIELD_POWER1)+28+10*spawn_level);
	/* HEALTH */
	p->SetUInt32Value(UNIT_FIELD_MAXHEALTH,p->GetUInt32Value(UNIT_FIELD_MAXHEALTH)+28+30*spawn_level);
	p->SetUInt32Value(UNIT_FIELD_HEALTH,p->GetUInt32Value(UNIT_FIELD_HEALTH)+28+30*spawn_level);
	/* LEVEL */
	p->SetUInt32Value(UNIT_FIELD_LEVEL, spawn_level);

	/* adjust damage - most stuff need scripting as they scale based on AP or SP*/
	uint32 dominant_power_value;
	if( getClass() == WARRIOR || getClass() == ROGUE || getClass() == DEATHKNIGHT )
		dominant_power_value = GetAP();
	else if( getClass() == WARLOCK )
		dominant_power_value = GetDamageDoneMod(SCHOOL_SHADOW);
	else if( getClass() == MAGE )
		dominant_power_value = MAX(MAX(GetDamageDoneMod(SCHOOL_FIRE), GetDamageDoneMod(SCHOOL_FROST)), GetDamageDoneMod(SCHOOL_ARCANE) );
	else if( getClass() == PRIEST )
		dominant_power_value = MAX(GetDamageDoneMod(SCHOOL_HOLY), GetDamageDoneMod(SCHOOL_SHADOW) );
	else if( getClass() == HUNTER )
		dominant_power_value = GetRAP();
	else if( getClass() == PALADIN )
		dominant_power_value = MAX( GetDamageDoneMod(SCHOOL_HOLY), GetAP() );
	else if( getClass() == SHAMAN || getClass() == DRUID )
		dominant_power_value = MAX( GetDamageDoneMod(SCHOOL_NATURE), GetAP() );
	else
		dominant_power_value = 400 / spawn_level; //240 dmg using 12% formula at lvl 80

	float dmg_now = MAX( getLevel(), dominant_power_value * 6 / 100.0f );	//default dmg in case we have none is aprox 6% of dominant owner power

	//not dead sure this is used all the time
	if( CreatedBy != NULL && Need_SM_Apply(CreatedBy) )
	{
		int32 flat_bonus = 0;
		int32 pct_bonus = 100;
		SM_FIValue(SM_FDamageBonus,&flat_bonus,CreatedBy->SpellGroupType);
		SM_FIValue(SM_PDamageBonus,&pct_bonus,CreatedBy->SpellGroupType);
		dmg_now = flat_bonus + dmg_now * pct_bonus / 100.0f;
	}
	float max_dmg = dmg_now + dmg_now / 2;

	p->SetFloatValue( UNIT_FIELD_MINDAMAGE, dmg_now );
	p->SetFloatValue( UNIT_FIELD_MAXDAMAGE, max_dmg );

//	p->SetUInt32Value( UNIT_FIELD_BYTES_0, 133120 );
//	p->SetUInt32Value( UNIT_FIELD_FLAGS, 8 );
//	p->SetUInt32Value( UNIT_FIELD_FLAGS_2, 2048 );
//	p->SetUInt32Value( UNIT_CREATED_BY_SPELL, 58834 );
//	p->SetUInt32Value( UNIT_FIELD_BYTES_2, 257 );
	p->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, GetGUID());
    p->SetUInt64Value(UNIT_FIELD_CREATEDBY, GetGUID());
	p->SetUInt32Value( UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED );
    p->SetZoneId(GetZoneId());
	p->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE,GetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE));
	p->_setFaction();

	p->GetAIInterface()->Init(p,AITYPE_PET,MOVEMENTTYPE_NONE,this);
	p->GetAIInterface()->SetUnitToFollow(this);
	p->GetAIInterface()->SetUnitToFollowAngle(m_fallowAngle);
	p->GetAIInterface()->SetFollowDistance(3.0f);
//	p->m_noRespawn = true;

	p->PushToWorld(GetMapMgr());

	if( duration )
		sEventMgr.AddEvent(p, &Creature::SummonExpire, EVENT_SUMMON_EXPIRE, duration, 1,0);

	//if owner is in combat then agro target
	if( CombatStatus.IsInCombat() )
	{
		Unit *topA = GetTopOwner();
		Unit *Possible_target = NULL;
		if( topA->IsPlayer() )
		{
			Possible_target = topA->GetMapMgr()->GetUnit( topA->CombatStatus.GetPrimaryAttackTarget() );	//cause we can target other for heal
			// maybe no agro yet ? Try to target selection
			if( Possible_target == NULL )
				Possible_target = topA->GetMapMgr()->GetUnit( topA->GetUInt64Value( UNIT_FIELD_TARGET ) );
		}
		else
		{
			Possible_target = topA->GetMapMgr()->GetUnit( topA->GetUInt64Value( UNIT_FIELD_TARGET ) );
		}

		if( Possible_target && isAttackable( this, Possible_target ) )
			p->GetAIInterface()->AttackReaction( Possible_target, 1, 0 );
	}

	return p;//lol, will compiler make the pointer conversion ?

}

float Unit::get_chance_to_daze(Unit *target)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
//	if(GetTypeId()!=TYPEID_UNIT)
//		return 0.0f;
	float attack_skill = float( getLevel() ) * 5.0f;
	float defense_skill;
	if( target->IsPlayer() )
		defense_skill = float( SafePlayerCast( target )->_GetSkillLineCurrent( SKILL_DEFENSE, false ) );
	else defense_skill = float( target->getLevel() * 5 );
	if( !defense_skill )
		defense_skill = 1;
	float chance_to_daze = attack_skill * 20 / defense_skill;//if level is equal then we get a 20% chance to daze
	chance_to_daze = chance_to_daze * std::min(target->getLevel() / 30.0f, 1.0f );//for targets below level 30 the chance decreses
	if( chance_to_daze > 40 )
	{ 
		return 40.0f;
	}
	else
		return chance_to_daze;
}

void CombatStatusHandler::ClearMyHealers()
{
	// this is where we check all our healers
	HealedSet::iterator i;
	Player * pt;
	for(i = m_healers.begin(); i != m_healers.end(); ++i)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*i);
		if(pt != NULL)
			pt->CombatStatus.RemoveHealed(m_Unit);
	}

	m_healers.clear();
}

void CombatStatusHandler::WeHealed(Unit * pHealTarget)
{
	if(pHealTarget->GetTypeId() != TYPEID_PLAYER || m_Unit->GetTypeId() != TYPEID_PLAYER || pHealTarget == m_Unit)
	{ 
		return;
	}

	if(pHealTarget->CombatStatus.IsInCombat())
	{
		m_healed.insert(pHealTarget->GetLowGUID());
		pHealTarget->CombatStatus.m_healers.insert(m_Unit->GetLowGUID());
	}

	UpdateFlag();
}

void CombatStatusHandler::RemoveHealed(Unit * pHealTarget)
{
	m_healed.erase(pHealTarget->GetLowGUID());
	UpdateFlag();
}

void CombatStatusHandler::UpdateFlag()
{
	bool n_status = InternalIsInCombat();
	if(n_status != m_lastStatus)
	{
		m_lastStatus = n_status;
		if(n_status)
		{
			//printf(I64FMT" is now in combat.\n", m_Unit->GetGUID());
			m_Unit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
			if(!m_Unit->hasStateFlag(UF_ATTACKING)) m_Unit->addStateFlag(UF_ATTACKING);
		}
		else
		{
			//printf(I64FMT" is no longer in combat.\n", m_Unit->GetGUID());
			m_Unit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_COMBAT);
			if(m_Unit->hasStateFlag(UF_ATTACKING)) 
				m_Unit->clearStateFlag(UF_ATTACKING);
			if( m_Unit->IsPlayer() )
				SafePlayerCast(m_Unit)->StartOutOfCombatCooldowns();

			// remove any of our healers from combat too, if they are able to be.
			ClearMyHealers();
		}
	}
}

bool CombatStatusHandler::InternalIsInCombat()
{
	if(m_Unit->IsPlayer() && m_Unit->GetMapMgr() && m_Unit->GetMapMgr()->IsCombatInProgress())
	{ 
		return true;
	}

	if(m_healed.size() > 0)
	{ 
		return true;
	}

	if(m_attackTargets.size() > 0)
	{ 
		return true;
	}

	if(m_attackers.size() > 0)
	{ 
		return true;
	}

	return false;
}

void CombatStatusHandler::AddAttackTarget(const uint64& guid)
{
	if(guid == m_Unit->GetGUID())
	{ 
		return;
	}

	m_attackTargets.insert(guid);
	//printf("Adding attack target "I64FMT" to "I64FMT"\n", guid, m_Unit->GetGUID());
	if(m_Unit->GetTypeId() == TYPEID_PLAYER &&
		m_primaryAttackTarget != guid)			// players can only have one attack target.
	{
		if(m_primaryAttackTarget)
			ClearPrimaryAttackTarget();

		m_primaryAttackTarget = guid;
	}

	UpdateFlag();
}

void CombatStatusHandler::ClearPrimaryAttackTarget()
{
	//printf("ClearPrimaryAttackTarget for "I64FMT"\n", m_Unit->GetGUID());
	if(m_primaryAttackTarget != 0)
	{
		Unit * pt = m_Unit->GetMapMgr()->GetUnit(m_primaryAttackTarget);
		if(pt != NULL)
		{
			// remove from their attacker set. (if we have no longer got any DoT's, etc)
			if(!IsAttacking(pt))
			{
				pt->CombatStatus.RemoveAttacker(m_Unit, m_Unit->GetGUID());
				m_attackTargets.erase(m_primaryAttackTarget);
			}
			
			m_primaryAttackTarget = 0;
		}
		else
		{
			m_attackTargets.erase(m_primaryAttackTarget);
			m_primaryAttackTarget = 0;
		}
	}

	UpdateFlag();
}

bool CombatStatusHandler::IsAttacking(Unit * pTarget)
{
	// check the target for any of our DoT's.
	for(uint32 i = MAX_POSITIVE_AURAS; i < MAX_NEGATIVE_AURAS1(pTarget); ++i)
		if(pTarget->m_auras[i] != NULL)
			if( m_Unit->GetGUID() == pTarget->m_auras[i]->m_casterGuid
//				&& pTarget->m_auras[i]->IsCombatStateAffecting()
				&& ( pTarget->m_auras[i]->GetSpellProto()->c_is_flags & SPELL_FLAG_IS_DAMAGING )
				)
			{ 
				return true;
			}

	// place any additional checks here
	return false;
}

void CombatStatusHandler::RemoveAttackTarget(Unit * pTarget)
{
	// called on aura remove, etc.
	AttackerMap::iterator itr = m_attackTargets.find(pTarget->GetGUID());
	if(itr == m_attackTargets.end())
	{ 
		return;
	}

	if(!IsAttacking(pTarget))
	{
		//printf("Removing attack target "I64FMT" on "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());
		m_attackTargets.erase(itr);
		if(m_primaryAttackTarget == pTarget->GetGUID())
			m_primaryAttackTarget = 0;

		UpdateFlag();
	}
	/*else
		printf("Cannot remove attack target "I64FMT" from "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());*/
}

void CombatStatusHandler::RemoveAttacker(Unit * pAttacker, const uint64 &guid)
{
	AttackerMap::iterator itr = m_attackers.find(guid);
	if(itr == m_attackers.end())
	{ 
		return;
	}

	if( (!pAttacker) || (!pAttacker->CombatStatus.IsAttacking(m_Unit)) )
	{
		//printf("Removing attacker "I64FMT" from "I64FMT"\n", guid, m_Unit->GetGUID());
		m_attackers.erase(itr);
		UpdateFlag();
	}
	/*else
	{
		printf("Cannot remove attacker "I64FMT" from "I64FMT"\n", guid, m_Unit->GetGUID());
	}*/
}

void CombatStatusHandler::OnDamageDealt(Unit * pTarget)
{
	// we added an aura, or dealt some damage to a target. they need to have us as an attacker, and they need to be our attack target if not.
	//printf("OnDamageDealt to "I64FMT" from "I64FMT"\n", pTarget->GetGUID(), m_Unit->GetGUID());
	if(pTarget == m_Unit)
	{ 
		return;
	}

	//no need to be in combat if dead
	if( !pTarget->isAlive() || !m_Unit->isAlive() )
	{ 
		return;
	}

	AttackerMap::iterator itr = m_attackTargets.find(pTarget->GetGUID());
	if(itr == m_attackTargets.end())
		AddAttackTarget(pTarget->GetGUID());

	itr = pTarget->CombatStatus.m_attackers.find(m_Unit->GetGUID());
	if(itr == pTarget->CombatStatus.m_attackers.end())
		pTarget->CombatStatus.AddAttacker(m_Unit->GetGUID());

	// update the timeout
	m_Unit->CombatStatusHandler_ResetPvPTimeout();
}

void CombatStatusHandler::AddAttacker(const uint64 &guid)
{
	m_attackers.insert(guid);
	UpdateFlag();
}

void CombatStatusHandler::ClearAttackers()
{
	// this is a FORCED function, only use when the reference will be destroyed.
	AttackerMap::iterator itr = m_attackTargets.begin();
	Unit * pt;
	for(; itr != m_attackTargets.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetUnit(*itr);
		if(pt)
		{
			pt->CombatStatus.m_attackers.erase(m_Unit->GetGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	for(itr = m_attackers.begin(); itr != m_attackers.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetUnit(*itr);
		if(pt)
		{
			pt->CombatStatus.m_attackTargets.erase(m_Unit->GetGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	m_attackers.clear();
	m_attackTargets.clear();
	m_primaryAttackTarget = 0;
	UpdateFlag();
}

void CombatStatusHandler::ClearHealers()
{

	if( m_Unit->GetMapMgr() == NULL )
		return; //wierd crash bug

	HealedSet::iterator itr = m_healed.begin();
	Player * pt;
	for(; itr != m_healed.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*itr);
		if(pt)
		{
			pt->CombatStatus.m_healers.erase(m_Unit->GetLowGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	for(itr = m_healers.begin(); itr != m_healers.end(); ++itr)
	{
		pt = m_Unit->GetMapMgr()->GetPlayer(*itr);
		if(pt)
		{
			pt->CombatStatus.m_healed.erase(m_Unit->GetLowGUID());
			pt->CombatStatus.UpdateFlag();
		}
	}

	m_healed.clear();
	m_healers.clear();
	UpdateFlag();
}

void CombatStatusHandler::OnRemoveFromWorld()
{
	ClearAttackers();
	ClearHealers();
}

bool CombatStatusHandler::IsInCombat()
{
	if (m_Unit == NULL || !m_Unit->IsInWorld())
	{ 
		return false;
	}

	switch (m_Unit->GetTypeId())
	{
		case TYPEID_UNIT:
		{
			if (m_Unit->IsPet() && SafePetCast(m_Unit)->GetPetAction() == PET_ACTION_ATTACK)
			{ 
				return true;
			}
			else if (m_Unit->IsPet())
			{ 
				return m_lastStatus;
			}
			else
			{
				return m_Unit->GetAIInterface()->getAITargetsCount()==0? false:true;
			}
		} break;
		case TYPEID_PLAYER:
		{
			if (SafePlayerCast(m_Unit)->GetSummon() != NULL && SafePlayerCast(m_Unit)->GetSummon()->GetPetOwner() == m_Unit && SafePlayerCast(m_Unit)->GetSummon()->CombatStatus.IsInCombat())
			{ 
				return true;
			}

			return m_lastStatus;
		} break;
		default: 
	return false;
	}
}

void Unit::CombatStatusHandler_ResetPvPTimeout()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(!IsPlayer())
	{ 
		return;
	}

	if( sEventMgr.HasEvent( this, EVENT_ATTACK_TIMEOUT ) )
		sEventMgr.ModifyEventTimeLeft( this, EVENT_ATTACK_TIMEOUT, 5000 );
	else
		sEventMgr.AddEvent(this, &Unit::CombatStatusHandler_UpdatePvPTimeout, EVENT_ATTACK_TIMEOUT, 5000, 1, EVENT_FLAG_DO_NOT_EXECUTE_IN_WORLD_CONTEXT);
}

void Unit::CombatStatusHandler_UpdatePvPTimeout()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	CombatStatus.TryToClearAttackTargets();	
}

void Unit::Heal(Unit *target, uint32 SpellId, uint32 amount)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
//Static heal
	if(!target || !SpellId || !amount)
	{ 
		return;
	}

	sStackWolrdPacket( data, SMSG_SPELLHEALLOG, 50 );
	data << target->GetNewGUID();
	data << this->GetNewGUID();
	data << uint32(SpellId);  
	data << uint32(amount);   
	if( target->IsUnit() )
		data << uint32( SafeUnitCast(target)->GetOverHeal( amount ) );	// overheal
	else
		data << uint32( amount );
	data << uint32( 0 );
	data << uint16(0);	 //this is critical message
#ifdef MINIMIZE_NETWORK_TRAFIC
	SendMessageToDuel( &data );
#else
	this->SendMessageToSet(&data,true);
#endif

	uint32 ch=target->GetUInt32Value(UNIT_FIELD_HEALTH);
	uint32 mh=target->GetUInt32Value(UNIT_FIELD_MAXHEALTH);
	if(mh!=ch)
	{
		ch += amount;
		if(ch > mh)
		{
			target->SetUInt32Value(UNIT_FIELD_HEALTH, mh);
			amount += mh-ch;
		}
		else 
			target->SetUInt32Value(UNIT_FIELD_HEALTH, ch);

		target->RemoveAurasByHeal();
	}
}
void Unit::Energize( Unit* target, uint32 SpellId, uint32 amount, uint32 type )
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	//Static energize
	if( !target || !SpellId || !amount )
	{ 
		return;
	}
	
	uint32 amount2;
	if( getClass() == DEATHKNIGHT  && IsPlayer() && type <= TOTAL_NORMAL_RUNE_TYPES )
	{
		Player *p = SafePlayerCast( this );
		for(int j=0;j<TOTAL_USED_RUNES;j++)
			if( p->m_rune_types[j] == type && p->m_runes[j] != MAX_RUNE_VALUE )
			{
				p->m_runes[j] = MAX_RUNE_VALUE;
				p->UpdateRuneIcon( j );
			}
		return; // there is not need to send packet now
	}
	else if( type <= 7 )
	{
		uint32 cur = target->GetUInt32Value( UNIT_FIELD_POWER1 + type );
		uint32 max = target->GetUInt32Value( UNIT_FIELD_MAXPOWER1 + type );
		
		/*if( max == cur ) // can we show null power gains in client? eg. zero happiness gain should be show...
			return;*/

		if( cur + amount > max )
			amount2 = max - cur;
		else
			amount2 = amount;

		target->SetUInt32Value( UNIT_FIELD_POWER1 + type, cur + amount2 );
	}

	sStackWolrdPacket( datamr, SMSG_SPELLENERGIZELOG, 50 );
	datamr << target->GetNewGUID();
	datamr << this->GetNewGUID();
	datamr << SpellId;
	datamr << type;
	datamr << amount;
#ifdef MINIMIZE_NETWORK_TRAFIC
	SendMessageToDuel( &datamr );
#else
	SendMessageToSet( &datamr, true ); /**/
#endif
	//same shit but blizz used this. No idea why
/*	WorldPacket datamr( SMSG_PERIODICAURALOG, 30 );
	datamr << target->GetNewGUID();
	datamr << this->GetNewGUID();
	datamr << SpellId;
	datamr << uint32(1); //just 1
	datamr << uint32( FLAG_PERIODIC_HEAL + FLAG_PERIODIC_LEECH ); //well i know this is wrong but client used this
	datamr << uint32( type ); 
	datamr << amount; //if amount is 0 then it is not shown
	SendMessageToSet( &datamr, true ); /**/
}

void Unit::InheritSMMods(Unit *inherit_from)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(inherit_from == NULL)
	{ 
		return;
	}
	if(inherit_from->SM_CriticalChance)
	{
		if(SM_CriticalChance==0)
			SM_CriticalChance = new int32[SPELL_GROUPS];
		memcpy(SM_CriticalChance,inherit_from->SM_CriticalChance,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FDur)
	{
		if(SM_FDur==0)
			SM_FDur = new int32[SPELL_GROUPS];
		memcpy(SM_FDur,inherit_from->SM_FDur,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PDur)
	{
		if(SM_PDur==0)
			SM_PDur = new int32[SPELL_GROUPS];
		memcpy(SM_PDur,inherit_from->SM_PDur,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRadius)
	{
		if(SM_PRadius==0)
			SM_PRadius = new int32[SPELL_GROUPS];
		memcpy(SM_PRadius,inherit_from->SM_PRadius,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FRadius)
	{
		if(SM_FRadius==0)
			SM_FRadius = new int32[SPELL_GROUPS];
		memcpy(SM_FRadius,inherit_from->SM_FRadius,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FRange)
	{
		if(SM_FRange==0)
			SM_FRange = new int32[SPELL_GROUPS];
		memcpy(SM_FRange,inherit_from->SM_FRange,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCastTime)
	{
		if(SM_PCastTime==0)
			SM_PCastTime = new int32[SPELL_GROUPS];
		memcpy(SM_PCastTime,inherit_from->SM_PCastTime,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FCastTime)
	{
		if(SM_FCastTime==0)
			SM_FCastTime = new int32[SPELL_GROUPS];
		memcpy(SM_FCastTime,inherit_from->SM_FCastTime,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCriticalDamage)
	{
		if(SM_PCriticalDamage==0)
			SM_PCriticalDamage = new int32[SPELL_GROUPS];
		memcpy(SM_PCriticalDamage,inherit_from->SM_PCriticalDamage,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FDOT)
	{
		if(SM_FDOT==0)
			SM_FDOT = new int32[SPELL_GROUPS];
		memcpy(SM_FDOT,inherit_from->SM_FDOT,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PDOT)
	{
		if(SM_PDOT==0)
			SM_PDOT = new int32[SPELL_GROUPS];
		memcpy(SM_PDOT,inherit_from->SM_PDOT,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FEffectBonus)
	{
		if(SM_FEffectBonus==0)
			SM_FEffectBonus = new int32[SPELL_GROUPS];
		memcpy(SM_FEffectBonus,inherit_from->SM_FEffectBonus,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FEffectTargetBonus)
	{
		if(SM_FEffectTargetBonus==0)
			SM_FEffectTargetBonus = new int32[SPELL_GROUPS];
		memcpy(SM_FEffectTargetBonus,inherit_from->SM_FEffectTargetBonus,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PEffectBonus)
	{
		if(SM_PEffectBonus==0)
			SM_PEffectBonus = new int32[SPELL_GROUPS];
		memcpy(SM_PEffectBonus,inherit_from->SM_PEffectBonus,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PEffectTargetBonus)
	{
		if(SM_PEffectTargetBonus==0)
			SM_PEffectTargetBonus = new int32[SPELL_GROUPS];
		memcpy(SM_PEffectTargetBonus,inherit_from->SM_PEffectTargetBonus,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FDamageBonus)
	{
		if(SM_FDamageBonus==0)
			SM_FDamageBonus = new int32[SPELL_GROUPS];
		memcpy(SM_FDamageBonus,inherit_from->SM_FDamageBonus,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PDamageBonus)
	{
		if(SM_PDamageBonus==0)
			SM_PDamageBonus = new int32[SPELL_GROUPS];
		memcpy(SM_PDamageBonus,inherit_from->SM_PDamageBonus,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PMiscEffect)
	{
		if(SM_PMiscEffect==0)
			SM_PMiscEffect = new int32[SPELL_GROUPS];
		memcpy(SM_PMiscEffect,inherit_from->SM_PMiscEffect,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FMiscEffect)
	{
		if(SM_FMiscEffect==0)
			SM_FMiscEffect = new int32[SPELL_GROUPS];
		memcpy(SM_FMiscEffect,inherit_from->SM_FMiscEffect,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FHitchance)
	{
		if(SM_FHitchance==0)
			SM_FHitchance = new int32[SPELL_GROUPS];
		memcpy(SM_FHitchance,inherit_from->SM_FHitchance,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRange)
	{
		if(SM_PRange==0)
			SM_PRange = new int32[SPELL_GROUPS];
		memcpy(SM_PRange,inherit_from->SM_PRange,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRadius)
	{
		if(SM_PRadius==0)
			SM_PRadius = new int32[SPELL_GROUPS];
		memcpy(SM_PRadius,inherit_from->SM_PRadius,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PAPBonus)
	{
		if(SM_PAPBonus==0)
			SM_PAPBonus = new int32[SPELL_GROUPS];
		memcpy(SM_PAPBonus,inherit_from->SM_PAPBonus,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCost)
	{
		if(SM_PCost==0)
			SM_PCost = new int32[SPELL_GROUPS];
		memcpy(SM_PCost,inherit_from->SM_PCost,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FCost)
	{
		if(SM_FCost==0)
			SM_FCost = new int32[SPELL_GROUPS];
		memcpy(SM_FCost,inherit_from->SM_FCost,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FAdditionalTargets)
	{
		if(SM_FAdditionalTargets==0)
			SM_FAdditionalTargets = new int32[SPELL_GROUPS];
		memcpy(SM_FAdditionalTargets,inherit_from->SM_FAdditionalTargets,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PJumpReduce)
	{
		if(SM_PJumpReduce==0)
			SM_PJumpReduce = new int32[SPELL_GROUPS];
		memcpy(SM_PJumpReduce,inherit_from->SM_PJumpReduce,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FSpeedMod)
	{
		if(SM_FSpeedMod==0)
			SM_FSpeedMod = new int32[SPELL_GROUPS];
		memcpy(SM_FSpeedMod,inherit_from->SM_FSpeedMod,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PNonInterrupt)
	{
		if(SM_PNonInterrupt==0)
			SM_PNonInterrupt = new int32[SPELL_GROUPS];
		memcpy(SM_PNonInterrupt,inherit_from->SM_PNonInterrupt,sizeof(int32)*SPELL_GROUPS);
	}
//	if(inherit_from->SM_FPenalty)
//	{
//		if(SM_FPenalty==0)
//			SM_FPenalty = new int32[SPELL_GROUPS];
//		memcpy(SM_FPenalty,inherit_from->SM_FPenalty,sizeof(int32)*SPELL_GROUPS);
//	}
	if(inherit_from->SM_FCooldownTime)
	{
		if(SM_FCooldownTime==0)
			SM_FCooldownTime = new int32[SPELL_GROUPS];
		memcpy(SM_FCooldownTime,inherit_from->SM_FCooldownTime,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCooldownTime)
	{
		if(SM_PCooldownTime==0)
			SM_PCooldownTime = new int32[SPELL_GROUPS];
		memcpy(SM_PCooldownTime,inherit_from->SM_PCooldownTime,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FChanceOfSuccess)
	{
		if(SM_FChanceOfSuccess==0)
			SM_FChanceOfSuccess = new int32[SPELL_GROUPS];
		memcpy(SM_FChanceOfSuccess,inherit_from->SM_FChanceOfSuccess,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FRezist_dispell)
	{
		if(SM_FRezist_dispell==0)
			SM_FRezist_dispell = new int32[SPELL_GROUPS];
		memcpy(SM_FRezist_dispell,inherit_from->SM_FRezist_dispell,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PRezist_dispell)
	{
		if(SM_PRezist_dispell==0)
			SM_PRezist_dispell = new int32[SPELL_GROUPS];
		memcpy(SM_PRezist_dispell,inherit_from->SM_PRezist_dispell,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FCharges)
	{
		if(SM_FCharges==0)
			SM_FCharges = new int32[SPELL_GROUPS];
		memcpy(SM_FCharges,inherit_from->SM_FCharges,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PCharges)
	{
		if(SM_PCharges==0)
			SM_PCharges = new int32[SPELL_GROUPS];
		memcpy(SM_PCharges,inherit_from->SM_PCharges,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FThreat)
	{
		if(SM_FThreat==0)
			SM_FThreat = new int32[SPELL_GROUPS];
		memcpy(SM_FThreat,inherit_from->SM_FThreat,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PThreat)
	{
		if(SM_PThreat==0)
			SM_PThreat = new int32[SPELL_GROUPS];
		memcpy(SM_PThreat,inherit_from->SM_PThreat,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FTime)
	{
		if(SM_FTime==0)
			SM_FTime = new int32[SPELL_GROUPS];
		memcpy(SM_FTime,inherit_from->SM_FTime,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FAddEffect1)
	{
		if(SM_FAddEffect1==0)
			SM_FAddEffect1 = new int32[SPELL_GROUPS];
		memcpy(SM_FAddEffect1,inherit_from->SM_FAddEffect1,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FAddEffect2)
	{
		if(SM_FAddEffect2==0)
			SM_FAddEffect2 = new int32[SPELL_GROUPS];
		memcpy(SM_FAddEffect2,inherit_from->SM_FAddEffect2,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_FAddEffect3)
	{
		if(SM_FAddEffect3==0)
			SM_FAddEffect3 = new int32[SPELL_GROUPS];
		memcpy(SM_FAddEffect3,inherit_from->SM_FAddEffect3,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PAddEffect1)
	{
		if(SM_PAddEffect1==0)
			SM_PAddEffect1 = new int32[SPELL_GROUPS];
		memcpy(SM_PAddEffect1,inherit_from->SM_PAddEffect1,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PAddEffect2)
	{
		if(SM_PAddEffect2==0)
			SM_PAddEffect2 = new int32[SPELL_GROUPS];
		memcpy(SM_PAddEffect2,inherit_from->SM_PAddEffect2,sizeof(int32)*SPELL_GROUPS);
	}
	if(inherit_from->SM_PAddEffect3)
	{
		if(SM_PAddEffect3==0)
			SM_PAddEffect3 = new int32[SPELL_GROUPS];
		memcpy(SM_PAddEffect3,inherit_from->SM_PAddEffect3,sizeof(int32)*SPELL_GROUPS);
	}
}

void CombatStatusHandler::TryToClearAttackTargets()
{
	AttackerMap::iterator i, i2;
	Unit * pt;

	for(i = m_attackTargets.begin(); i != m_attackTargets.end();)
	{
		i2 = i++;
		pt = m_Unit->GetMapMgr()->GetUnit(*i2);
		if(pt == NULL)
		{
			m_attackTargets.erase(i2);
			continue;
		}

		RemoveAttackTarget(pt);
		pt->CombatStatus.RemoveAttacker(m_Unit,m_Unit->GetGUID());
	}
}

void CombatStatusHandler::AttackersForgetHate()
{
	AttackerMap::iterator i, i2;
	Unit * pt;

	for(i = m_attackTargets.begin(); i != m_attackTargets.end();)
	{
		i2 = i++;
		pt = m_Unit->GetMapMgr()->GetUnit(*i2);
		if(pt == NULL)
		{
			m_attackTargets.erase(i2);
			continue;
		}

		if(pt->GetAIInterface())
			pt->GetAIInterface()->RemoveThreatByPtr(m_Unit);
	}
}

void Unit::CancelSpell(Spell * ptr)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
/*
	if(ptr)
		ptr->cancel();
	else */
	if(m_currentSpell)
	{
		// this logically might seem a little bit twisted
		// crash situation : an already deleted spell will be called to get canceled by eventmanager
		// solution : We should not delay spell canceling more then second spell canceling.
		// problem : might remove spells that should not be removed. Not sure about it :(
		// sEventMgr.RemoveEvents(this,EVENT_UNIT_DELAYED_SPELL_CANCEL);
		m_currentSpell->safe_cancel();
	}
}

void Unit::EventStrikeWithAbility(uint64 guid, SpellEntry * sp, uint32 damage)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	Unit * victim = m_mapMgr ? m_mapMgr->GetUnit(guid) : NULL;
	if(victim)
		Strike( victim, RANGED, sp, 0, 0, 0, false, true );
}

void Unit::DispelAll(bool positive)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( positive )
	{
		for(uint32 i = FIRST_AURA_SLOT; i < m_auras_pos_size; ++i)
			if( m_auras[i]!=NULL)
				m_auras[i]->Remove();
	}
	else 
		for(uint32 i = MAX_POSITIVE_AURAS; i < m_auras_neg_size; ++i)
			if( m_auras[i]!=NULL )
				m_auras[i]->Remove();
}

/* bool Unit::RemoveAllAurasByMechanic (renamed from MechanicImmunityMassDispel)
- Removes all auras on this unit that are of a specific mechanic.
- Useful for things like.. Apply Aura: Immune Mechanic, where existing (de)buffs are *always supposed* to be removed.
- I'm not sure if this goes here under unit.
* Arguments:
	- uint32 MechanicType
		*

* Returns;
	- False if no buffs were dispelled, true if more than 0 were dispelled.
*/
bool Unit::RemoveAllAurasByMechanic( uint32 MechanicType , uint32 MaxDispel = -1 , bool HostileOnly = true )
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	//sLog.outString( "Unit::MechanicImmunityMassDispel called, mechanic: %u" , MechanicType );
	uint32 DispelCount = MaxDispel;
	uint32 start_at;

	if( HostileOnly )
		start_at = MAX_POSITIVE_AURAS;
	else
		start_at = FIRST_AURA_SLOT;

	for(uint32 x = start_at ; x < m_auras_neg_size ; x++ )
		if( m_auras[x] )
		{
			if( m_auras[x]->GetSpellProto()->MechanicsType == MechanicType ) // Remove all mechanics of type MechanicType (my english goen boom)
			{
				//sLog.outString( "Removed aura. [AuraSlot %u, SpellId %u]" , x , m_auras[x]->GetSpellId() );
				m_auras[x]->Remove(); // EZ-Remove
				DispelCount--;
				if( DispelCount == 0 )
				{ 
					return true;
				}
			}
			else if( MechanicType == MECHANIC_ENSNARED ) // if got immunity for slow, remove some that are not in the mechanics
			{
				for( int i=0 ; i<3 ; i++ )
				{
					// SNARE + ROOT
					if( m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_DECREASE_SPEED || m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_ROOT )
					{
						m_auras[x]->Remove();
						break;
					}
				}
			}
		}
	return ( DispelCount != MaxDispel );
}

void Unit::RemoveAllMovementImpairing()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for( uint32 x = MAX_POSITIVE_AURAS; x < m_auras_neg_size; x++ )
	{
		if( m_auras[x] != NULL )
		{
			if( m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ROOTED 
				|| m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_ENSNARED
				|| m_auras[x]->GetSpellProto()->MechanicsType == MECHANIC_DAZED)

			{
				m_auras[x]->Remove();
			}
			else
			{
				for( int i = 0; i < 3; i++ )
				{
					if( m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_DECREASE_SPEED 
					|| m_auras[x]->GetSpellProto()->EffectApplyAuraName[i] == SPELL_AURA_MOD_ROOT )
					{
						m_auras[x]->Remove();
						break;
					}
				}
			}
		}
	}
}

void Unit::setAttackTimer(int32 time, bool offhand)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(!time)
		time = offhand ? m_uint32Values[UNIT_FIELD_BASEATTACKTIME_1] : m_uint32Values[UNIT_FIELD_BASEATTACKTIME];

	time = std::max(1000,float2int32(float(time)*GetSpellHaste()));

	if(time>300000)		// just in case.. shouldn't happen though
		time=offhand ? m_uint32Values[UNIT_FIELD_BASEATTACKTIME_1] : m_uint32Values[UNIT_FIELD_BASEATTACKTIME];

	if(offhand)
		m_attackTimer_1 = getMSTime() + time;
	else
		m_attackTimer = getMSTime() + time;
}

bool Unit::isAttackReady(bool offhand)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if(offhand)
	{ 
		return (getMSTime() >= m_attackTimer_1) ? true : false;
	}
	else
		return (getMSTime() >= m_attackTimer) ? true : false;
}

void Unit::ReplaceAIInterface(AIInterface *new_interface) 
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
 
	delete m_aiInterface;	//be carefull when you do this. Might screw unit states !
	m_aiInterface = new_interface; 
}

void Unit::EventUpdateFlag()  
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
  
	CombatStatus.UpdateFlag(); 
}

bool Unit::HasAurasOfNameHashWithCaster(uint32 namehash, Unit * caster)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(uint32 i = MAX_POSITIVE_AURAS; i < m_auras_neg_size; ++i)
		if( m_auras[i] && m_auras[i]->GetSpellProto()->NameHash == namehash && m_auras[i]->GetCasterGUID() == caster->GetGUID() )
		{ 
			return true;
		}

	return false;
}

void Unit::EventModelChange()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	UnitModelSizeEntry  *newmodelhalfsize = NULL;

	//mounts are bigger then normal size
	if( GetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID ) )
		newmodelhalfsize = UnitModelSizeStorage.LookupEntry( GetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID ) );
	if( newmodelhalfsize == NULL )
		newmodelhalfsize = UnitModelSizeStorage.LookupEntry( GetUInt32Value( UNIT_FIELD_DISPLAYID ) );

	if( newmodelhalfsize )
	{
		ModelHalfSize = newmodelhalfsize->HalfSize;
//		if( IsCreature() && SafeCreatureCast(this)->GetProto() )
//			ModelHalfSize *=  SafeCreatureCast(this)->GetProto()->BoundingRadius;
	}
	else
		ModelHalfSize = 1.0f; //baaad, but it happens :(
}

void Unit::RemoveFieldSummon()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	uint64 guid = GetUInt64Value(UNIT_FIELD_SUMMON);
	if(guid && GetMapMgr())
	{
		Creature *summon = GetMapMgr()->GetCreature(guid);
		if (summon)
		{
			summon->RemoveFromWorld(false,true);
			summon->SafeDelete();
		}
		SetUInt64Value(UNIT_FIELD_SUMMON, 0);
	}
}

//what is an Immobilize spell ? Have to add it later to spell effect handler
void Unit::EventStunOrImmobilize(Unit *proc_target, bool is_victim)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if ( this == proc_target )
		return; //how and why would we stun ourselfs

	int32 t_trigger_on_stun,t_trigger_on_stun_chance;
	if( is_victim == false )
	{
		t_trigger_on_stun = trigger_on_stun;
		t_trigger_on_stun_chance = trigger_on_stun_chance;
	}
	else
	{
		t_trigger_on_stun = trigger_on_stun_victim;
		t_trigger_on_stun_chance = trigger_on_stun_chance_victim;
	}

	if( t_trigger_on_stun )
	{
		if( t_trigger_on_stun_chance < 100 && !Rand( t_trigger_on_stun_chance ) )
		{ 
			return;
		}

		SpellEntry *spellInfo = dbcSpell.LookupEntry(t_trigger_on_stun);

		if(!spellInfo)
		{ 
			return;
		}

		Spell *spell = SpellPool.PooledNew();
		spell->Init(this, spellInfo ,true, NULL);
		SpellCastTargets targets;

		if ( spellInfo->procFlags2 & PROC2_TARGET_SELF )
			targets.m_unitTarget = GetGUID();
		else if ( proc_target ) 
			targets.m_unitTarget = proc_target->GetGUID();
		else 
			targets.m_unitTarget = GetGUID();
		spell->prepare(&targets);
	}
}
void Unit::RemoveExtraStrikeTarget(SpellEntry *spell_info)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(CommitPointerListNode<ExtraStrike> *i = m_extraStrikeTargets.begin();i != m_extraStrikeTargets.end(); i = i->Next() )
	{
		if(i->data->deleted == false && spell_info == i->data->spell_info)
		{
			m_extrastriketargetc--;
			i->data->deleted = true;
		}
	}
}

void Unit::AddExtraStrikeTarget(SpellEntry *spell_info, uint32 charges)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	for(CommitPointerListNode<ExtraStrike> *i = m_extraStrikeTargets.begin();i != m_extraStrikeTargets.end(); i = i->Next() )
	{
		//a pointer check or id check ...should be the same
		if(spell_info == i->data->spell_info)
		{
			if (i->data->deleted == true)
			{
				i->data->deleted = false;
				m_extrastriketargetc++;
			}
			i->data->charges = charges;
			return;
		}
	}

	ExtraStrike *es = new ExtraStrike;

	es->spell_info = spell_info;
	es->charges = charges;
	es->deleted = false;
	m_extraStrikeTargets.push_front(es);
	m_extrastriketargetc++;
}

uint32 Unit::DoDamageSplitTarget(uint32 res, uint32 school_type, bool melee_dmg)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	Unit * splittarget;
	uint32 splitdamage, tmpsplit;
	DamageSplitTarget * ds = m_damageSplitTarget;
		
	splittarget = (GetMapMgr() != NULL) ? GetMapMgr()->GetUnit( ds->m_target ) : NULL;
	if( splittarget != NULL && res > 0 && splittarget->isAlive() ) 
	{
		// calculate damage
		tmpsplit = ds->m_flatDamageSplit;
		if( tmpsplit > res)
			tmpsplit = res; // prevent < 0 damage
		if( tmpsplit > splittarget->GetUInt32Value( UNIT_FIELD_HEALTH ) )
			tmpsplit = splittarget->GetUInt32Value( UNIT_FIELD_HEALTH );
		splitdamage = tmpsplit;
		res -= tmpsplit;

		tmpsplit = float2int32( ds->m_pctDamageSplit * res );
		if( tmpsplit > res )
			tmpsplit = res;
		if( tmpsplit > splittarget->GetUInt32Value( UNIT_FIELD_HEALTH ) )
			tmpsplit = splittarget->GetUInt32Value( UNIT_FIELD_HEALTH );
		splitdamage += tmpsplit;
		res -= tmpsplit;

		if( splitdamage )
		{
			splittarget->DealDamage(splittarget, splitdamage, 0, ds->m_spellId, 0);

			// Send damage log
			if (melee_dmg) 
			{
				dealdamage sdmg;

				sdmg.full_damage = splitdamage;
				sdmg.resisted_damage = 0;
				sdmg.school_type = school_type;
				SendAttackerStateUpdate(this, splittarget, &sdmg, splitdamage, 0, 0, 0, ATTACK);
			}
			else 
			{
				SendSpellNonMeleeDamageLog(this, splittarget, ds->m_spellId, splitdamage, school_type, 0, 0, true, 0, 0, true);
			}
		}
	}

	return res;
}

void Unit::UpdatePowerAmm(bool forced)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( !IsPlayer() 
		|| !SafePlayerCast(this)->GetSession()
		|| ( forced==false && m_updateMask.GetBit( UNIT_FIELD_POWER1 + GetPowerType() ) == 0) //there is a small chance there is no power update needed
		)
		return;
	sStackWolrdPacket( data, SMSG_POWER_UPDATE, 10);
	FastGUIDPack(data, GetGUID());
	data << uint8( GetPowerType() );
	data << GetUInt32Value( UNIT_FIELD_POWER1 + GetPowerType() );
//	SendMessageToSet(&data, true); //we make the power fields private and send this packet to all players
	SafePlayerCast(this)->GetSession()->SendPacket(&data); //we send packet only to self. Rest of players get power amm from A9
}
/*
void Unit::SendHealLog(Object *from,uint32 spell,uint32 amm,bool self)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( !amm )
	{ 
		return;
	}

	sStackWolrdPacket( data, SMSG_SPELLHEALLOG, 50 );
	data << GetNewGUID();
	data << from->GetNewGUID();
	data << spell;
	data << amm;
	data << uint8(0); //critical
#ifdef MINIMIZE_NETWORK_TRAFIC
	SendMessageToDuel( &data );
#else
	SendMessageToSet(&data, true);
#endif
}*/

bool Unit::IsPvPFlagged()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
   return HasByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_PVP);
}

void Unit::SetPvPFlag()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
    SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_PVP);

	if( GetUInt32Value( UNIT_FIELD_CREATEDBY ) && GetMapMgr() )
	{
		Unit *owner = GetMapMgr()->GetUnit( GetUInt64Value( UNIT_FIELD_CREATEDBY ) );
		if( owner && owner!=this && !owner->IsPvPFlagged() )
			owner->SetPvPFlag();
	}
}

//! Removal
void Unit::RemovePvPFlag()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
   RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_PVP);
}

bool Unit::IsFFAPvPFlagged()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
 
   return HasByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
}

void Unit::SetFFAPvPFlag()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
    SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);

	if( GetUInt32Value( UNIT_FIELD_CREATEDBY ) && GetMapMgr() )
	{
		Unit *owner = GetMapMgr()->GetUnit( GetUInt64Value( UNIT_FIELD_CREATEDBY ) );
		if( owner && owner!=this && !owner->IsFFAPvPFlagged() )
			owner->SetFFAPvPFlag();
	}
}

void Unit::RemoveFFAPvPFlag()
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
   RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
}

//draw weapon while in combat or restore sheath
void Unit::SetWeaponSheath(uint8 new_sheath)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	if( new_sheath == WEAPON_SHEATH_RESTORE_SPAWN )
	{
		if( IsCreature() )
		{
			Creature *pcr = SafeCreatureCast(this);
			if( pcr->m_spawn )
				SetByte(UNIT_FIELD_BYTES_2, 0, (uint8)pcr->m_spawn->bytes2);
			else 
				SetByte(UNIT_FIELD_BYTES_2, 0, WEAPON_SHEATH_NONE);
		}
		else
			SetByte(UNIT_FIELD_BYTES_2, 0, WEAPON_SHEATH_NONE);
	}
	else 
		SetByte(UNIT_FIELD_BYTES_2, 0, new_sheath);
}

void Unit::SetPower(uint32 type, int32 value)
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
   uint32 maxpower = GetUInt32Value(UNIT_FIELD_MAXPOWER1 + type);
   if(value < 0)
      value = 0;
   else if(value > (int32)maxpower)
      value = maxpower;
   SetUInt32Value(UNIT_FIELD_POWER1 + type, value);
}

void Unit::AddExtraAttack( ExtraAttack *ea )
{
	INSTRUMENT_TYPECAST_CHECK_UNIT_OBJECT_TYPE
	//check if we are stacking aura that is giving extra strikes. We do not proc all extra strikes at once for these
	for(CommitPointerListNode<ExtraAttack> *i = m_extra_attacks.begin();i != m_extra_attacks.end();i = i->Next() )
		if( i->data->sp == ea->sp )
		{
			i->data->count += ea->count;	//merge auras of same 
			delete ea;
			return;
		}
	m_extra_attacks.push_front( ea );
}

Unit *Unit::GetTopOwner()
{
	Unit *topA = this;
	//this is made with loop because. Ex : totems that spawn mobs -> mob -> totem -> owner
	while( topA && topA->GetUInt32Value( UNIT_FIELD_CREATEDBY ) && topA->GetMapMgr() )
	{
		Unit *ttopA = topA->GetMapMgr()->GetUnit( topA->GetUInt32Value( UNIT_FIELD_CREATEDBY ) );
		if( ttopA == topA || ttopA == NULL )
			break;	//someone managed to self create. Met god yet ?
		topA = ttopA;
	}
	return topA;
}

Group *Unit::GetGroup() 
{
	Unit *topA = GetTopOwner();
	if( topA->IsPlayer() )
		return SafePlayerCast( topA )->GetGroup();
	return NULL; 
}

bool Unit::CanCastVehicleSpell( uint32 spellID )
{
	Vehicle * vehicle = GetVehicle();
	if( vehicle != NULL )
		return vehicle->CanCastSpell( spellID );
	return false;
} 

void UnitChain::AddUnit(Unit* u)
{
	m_units.insert(u);
	u->m_chain = this;
}

void UnitChain::RemoveUnit(Unit* u)
{
	m_units.erase(u);
	u->m_chain = NULL;

	if (m_units.size() == 0 && !m_persist)
		delete this;
}
