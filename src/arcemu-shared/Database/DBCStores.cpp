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

#include "DBCStores.h"
#include "DataStore.h"
#include "NGLog.h"

SERVER_DECL DBCStorage <LFGDungeonEntry>			dbcLFGDungeonStore;
SERVER_DECL DBCStorage <WorldMapAreaEntry>			dbcWorldMapZoneStore;
SERVER_DECL DBCStorage <VehicleSeatEntry>			dbcVehicleSeatEntry;
SERVER_DECL DBCStorage <VehicleEntry>				dbcVehicleEntry;
//SERVER_DECL DBCStorage<CurrencyTypesEntry>			dbcCurrencyTypesStore;
SERVER_DECL DBCStorage<ScalingStatDistributionEntry> dbcScalingStatDistribution;
SERVER_DECL DBCStorage<ScalingStatValuesEntry>		dbcScalingStatValues;
SERVER_DECL DBCStorage<WorldMapOverlay>				dbcWorldMapOverlayStore;
SERVER_DECL DBCStorage<BattlemasterListEntry>		dbcBattlemasterListStore;
SERVER_DECL DBCStorage<ItemLimitCategory>			dbcItemLimitCategory;
SERVER_DECL DBCStorage<AreaGroup>					dbcAreaGroup;
SERVER_DECL DBCStorage<SpellRuneCostEntry>			dbcSpellRuneCostEntry;
SERVER_DECL DBCStorage<GlyphPropertiesEntry>        dbcGlyphPropertiesStore;
SERVER_DECL DBCStorage<GlyphSlotEntry>              dbcGlyphSlotStore;
SERVER_DECL std::list<AchievementCriteriaEntry*>	dbcBoostedAchievementLookup[ACHIEVEMENT_CRITERIA_TYPE_TOTAL];
SERVER_DECL DBCStorage<AchievementEntry>			dbcAchievementStore;
SERVER_DECL DBCStorage<AchievementCriteriaEntry>	dbcAchievementCriteriaStore;
SERVER_DECL DBCStorage<BarberShopStyleEntry>		dbcBarberShopStyleStore;
SERVER_DECL DBCStorage<GtBarberShopCostBaseEntry>	dbcBarberShopCostStore;
SERVER_DECL DBCStorage<GemPropertyEntry>			dbcGemProperty;
SERVER_DECL DBCStorage<ItemSetEntry>				dbcItemSet;
SERVER_DECL DBCStorage<Lock>						dbcLock;
SERVER_DECL DBCStorage<SpellEntry>					dbcSpell;
SERVER_DECL DBCStorage<SpellDuration>				dbcSpellDuration;
SERVER_DECL DBCStorage<SpellRange>					dbcSpellRange;
SERVER_DECL DBCStorage<emoteentry>					dbcEmoteEntry;
SERVER_DECL DBCStorage<SpellRadius>					dbcSpellRadius;
SERVER_DECL DBCStorage<SpellCastTime>				dbcSpellCastTime;
SERVER_DECL DBCStorage<AreaTable>					dbcArea;
SERVER_DECL DBCStorage<FactionTemplateDBC>			dbcFactionTemplate;
SERVER_DECL DBCStorage<FactionDBC>					dbcFaction;
SERVER_DECL DBCStorage<EnchantEntry>				dbcEnchant;
SERVER_DECL DBCStorage<RandomProps>					dbcRandomProps;
SERVER_DECL DBCStorage<skilllinespell>				dbcSkillLineSpell;
SERVER_DECL DBCStorage<skilllineentry>				dbcSkillLine;
SERVER_DECL DBCStorage<DBCTaxiNode>					dbcTaxiNode;
SERVER_DECL DBCStorage<DBCTaxiPath>					dbcTaxiPath;
SERVER_DECL DBCStorage<DBCTaxiPathNode>				dbcTaxiPathNode;
SERVER_DECL DBCStorage<AuctionHouseDBC>				dbcAuctionHouse;
SERVER_DECL DBCStorage<TalentEntry>					dbcTalent;
SERVER_DECL DBCStorage<TalentTabEntry>				dbcTalentTab;
SERVER_DECL DBCStorage<CreatureSpellDataEntry>		dbcCreatureSpellData;
SERVER_DECL DBCStorage<CreatureFamilyEntry>			dbcCreatureFamily;
SERVER_DECL DBCStorage<CharClassEntry>				dbcCharClass;
SERVER_DECL DBCStorage<CharRaceEntry>				dbcCharRace;
SERVER_DECL DBCStorage<MapEntry>					dbcMap;
SERVER_DECL DBCStorage<ItemExtendedCostEntry>		dbcItemExtendedCost;
SERVER_DECL DBCStorage<ItemRandomSuffixEntry>		dbcItemRandomSuffix;
SERVER_DECL DBCStorage<CombatRatingDBC>				dbcCombatRating;
SERVER_DECL DBCStorage<ChatChannelDBC>				dbcChatChannels;
SERVER_DECL DBCStorage<DurabilityQualityEntry>		dbcDurabilityQuality;
SERVER_DECL DBCStorage<DurabilityCostsEntry>		dbcDurabilityCosts;
SERVER_DECL DBCStorage<BankSlotPrice>				dbcBankSlotPrices;
SERVER_DECL DBCStorage<BankSlotPrice>				dbcStableSlotPrices;
SERVER_DECL DBCStorage<gtFloat> dbcMeleeCrit;
SERVER_DECL DBCStorage<gtFloat> dbcMeleeCritBase;
SERVER_DECL DBCStorage<gtFloat> dbcSpellCrit;
SERVER_DECL DBCStorage<gtFloat> dbcSpellCritBase;
SERVER_DECL DBCStorage<gtFloat> dbcMPRegen;
SERVER_DECL DBCStorage<gtFloat> dbcMPRegenBase;
SERVER_DECL DBCStorage<gtFloat> dbcHPRegen;
SERVER_DECL DBCStorage<gtFloat> dbcHPRegenBase;
SERVER_DECL DBCStorage<AreaTriggerEntry> dbcAreaTrigger;
SERVER_DECL DBCStorage<QuestXPEntry> dbcQuestXP;
SERVER_DECL DBCStorage<QuestRewRepEntry> dbcQuestRewRep;
SERVER_DECL DBCStorage<CharTitlesEntry> dbcCharTitle;

const char* LFGDungeonFormat = "nxxxxxxxxxxxxxxxxxuuuuuuuxuxxuxu";
const char* WorldMapZoneFormat = "uuusffffxxx";
const char* VehicleEntryFormat = "uuffffuuuuuuuufffffffffffffffssssfufuxxx";
const char* VehicleSeatEntryFormat = "uuiffffffffffiiiiiifffffffiiifffiiiiiiiffiiiiixxxxxxxxxxxx";
const char* CurrencyTypesEntryFormat = "xnxu";
const char* scalingstatdistributionformat = "uiiiiiiiiiiuuuuuuuuuuu";
const char* scalingstatvaluesformat = "uuuuuuuuuuuuuuuuuuuuuuuu";
const char* WorldMapOverlayStoreFormat="nxiiiixxxxxxxxxxx";
const char* BattlemasterListEntryFormat = "uiiiiiiiiuxxxxxxxxxxxxxxxxxxxxxx";
const char* itemlimitcategoryFormat = "uxxxxxxxxxxxxxxxxxux";
const char* areagroupFormat = "uuuuuuuu";
const char* SpellRuneCostFormat="uuuuu";
const char* GlyphPropertiesFormat="niii";
const char* GlyphSlotFormat="nii";
const char* AchievementFormat=
	"n" // ID
	"i" // factionFlag
	"i" // mapID
	"u" // unknown1
	"sxxxxxxxxxxxxxxx" // name
	"u" // name_flags
	"sxxxxxxxxxxxxxxx" // description
	"u" // desc_flags
	"i" // categoryId
	"i" // points
	"u" // orderInCategory
	"i" // flags
	"u" // flags2
	"sxxxxxxxxxxxxxxx" // rewardName
	"u" // rewardName_flags
	"u" // count
	"u" // refAchievement
;
const char* AchievementCriteriaFormat="iiiiiiiiixxxxxxxxxxxxxxxxxiixix";
const char* BarberShopStyleEntryFormat="nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxi";
const char* BarberShopCostFormat="f";
const char* ItemSetFormat = "usxxxxxxxxxxxxxxxuuuuuuuuuxxxxxxxxxuuuuuuuuuuuuuuuuuu";
const char* LockFormat = "uuuuuuxxxuuuuuxxxuuuuuxxxxxxxxxxx";
const char* EmoteEntryFormat = "uxuuuuxuxuxxxxxxxxx";
const char* skilllinespellFormat = "uuuuuuuuuuuuxx";
const char* EnchantEntrYFormat = "uxuuuuuuuuuuuusxxxxxxxxxxxxxxxxuuuuuux";
const char* GemPropertyEntryFormat = "uuuuu";
const char* skilllineentrYFormat = "uuusxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char* spellentryFormat = "uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuiuuuuuuuuuufuuuuuuuuuuuuuuuuuuuuiuuuuuuuufffiiiiiiuuuuuuuuuuuuuuufffuuuuuuuuuuuuuuufffuuuuuuuuuuuuuusxxxxxxxxxxxxxxxxsxxxxxxxxxxxxxxxxsxxxxxxxxxxxxxxxxsxxxxxxxxxxxxxxxxuuuuuuuuuuuifffuuuuuuuuuuuuuuu";
const char* itemextendedcostFormat = "uuuuuuuuuuuuuuux";
const char* talententryFormat = "uuuuuuuuuxxxxuxxuxxxxxx";
const char* talenttabentryFormat = "uxxxxxxxxxxxxxxxxxxxuxux";
const char* spellcasttimeFormat = "uuxx";
const char* spellradiusFormat = "ufxf";
const char* spellrangeFormat = "uffffxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char* spelldurationFormat = "uuuu";
const char* randompropsFormat = "uxuuuxxxxxxxxxxxxxxxxxxx";
const char* areatableFormat = "uuuuuxxxuxusxxxxxxxxxxxxxxxxuxxxxxxx";
const char* factiontemplatedbcFormat = "uuuuuuuuuuuuuu";
const char* auctionhousedbcFormat = "uuuuxxxxxxxxxxxxxxxxx";
const char* factiondbcFormat = "uiuuuuuuuuiiiiuuuuuxxxxsxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char* dbctaxinodeFormat = "uufffxxxxxxxxxxxxxxxxxuu";
const char* dbctaxipathFormat = "uuuu";
const char* dbctaxipathnodeFormat = "uuuufffuuxx";
const char* creaturespelldataFormat = "uuuuuuuuu";
const char* charraceFormat = "uxxxxxxuxxxuxsxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char* charclassFormat = "uxuxsxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char* creaturefamilyFormat = "ufufuuuuxxsxxxxxxxxxxxxxxxxx";
const char* mapentryFormat = "usuxxsxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char* itemrandomsuffixformat = "uxxxxxxxxxxxxxxxxxxuuuuuuuuuu";
const char* chatchannelformat = "uuxsxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char * durabilityqualityFormat = "uf";
const char * durabilitycostsFormat = "uuuuuuuuuuuuuuuuuuuuuuuuuuuuuu";
const char* bankslotpriceformat = "uu";
const char* gtfloatformat = "f";
const char* areatriggerformat = "uuffffffff";
const char* questxpformat = "uxuuuuuuuux";
const char* questrewrepformat = "ixiiiiiiiii";
const char* chartitleFormat = "uxsxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxu";

template<class T>
bool loader_stub(const char * filename, const char * format, bool ind, T& l, bool loadstrs)
{
	Log.Notice("DBC", "Loading %s.", filename);
	return l.Load(filename, format, ind, loadstrs);
}

#define LOAD_DBC(filename, format, ind, stor, strings) if(!loader_stub(filename, format, ind, stor, strings)) { return false; } 

bool LoadDBCs()
{
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/LFGDungeons.dbc",LFGDungeonFormat,false,dbcLFGDungeonStore, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/WorldMapArea.dbc",WorldMapZoneFormat,false,dbcWorldMapZoneStore, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/Vehicle.dbc",VehicleEntryFormat,true,dbcVehicleEntry, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/VehicleSeat.dbc",VehicleSeatEntryFormat,true,dbcVehicleSeatEntry, false);
//	printf("mem usage : %f\n",GetMemUsage() );
//	LOAD_DBC("DBC/CurrencyTypes.dbc",CurrencyTypesEntryFormat,true,dbcCurrencyTypesStore, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/ScalingStatDistribution.dbc",scalingstatdistributionformat,true,dbcScalingStatDistribution, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/ScalingStatValues.dbc",scalingstatvaluesformat,true,dbcScalingStatValues, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/WorldMapOverlay.dbc", WorldMapOverlayStoreFormat, true, dbcWorldMapOverlayStore, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/BattlemasterList.dbc", BattlemasterListEntryFormat, true, dbcBattlemasterListStore, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/ItemLimitCategory.dbc", itemlimitcategoryFormat, true, dbcItemLimitCategory, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/AreaGroup.dbc", areagroupFormat, true, dbcAreaGroup, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/SpellRuneCost.dbc", SpellRuneCostFormat, true, dbcSpellRuneCostEntry, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/GlyphProperties.dbc", GlyphPropertiesFormat, true, dbcGlyphPropertiesStore, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/GlyphSlot.dbc", GlyphSlotFormat, true, dbcGlyphSlotStore, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/Achievement_Criteria.dbc", AchievementCriteriaFormat, true, dbcAchievementCriteriaStore, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/Achievement.dbc", AchievementFormat, true, dbcAchievementStore, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/BarberShopStyle.dbc", BarberShopStyleEntryFormat, true, dbcBarberShopStyleStore, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/gtBarberShopCostBase.dbc", BarberShopCostFormat, false, dbcBarberShopCostStore, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/ItemSet.dbc", ItemSetFormat, true, dbcItemSet, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/Lock.dbc", LockFormat, true, dbcLock, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/EmotesText.dbc", EmoteEntryFormat, true, dbcEmoteEntry, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/SkillLineAbility.dbc", skilllinespellFormat, false, dbcSkillLineSpell, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/SpellItemEnchantment.dbc", EnchantEntrYFormat, true, dbcEnchant, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/GemProperties.dbc", GemPropertyEntryFormat, true, dbcGemProperty, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/SkillLine.dbc", skilllineentrYFormat, true, dbcSkillLine, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/Spell.dbc", spellentryFormat, true, dbcSpell, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/ItemExtendedCost.dbc", itemextendedcostFormat, true, dbcItemExtendedCost, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/Talent.dbc", talententryFormat, true, dbcTalent, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/TalentTab.dbc", talenttabentryFormat, true, dbcTalentTab, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/SpellCastTimes.dbc", spellcasttimeFormat, true, dbcSpellCastTime, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/SpellRadius.dbc", spellradiusFormat, true, dbcSpellRadius, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/SpellRange.dbc", spellrangeFormat, true, dbcSpellRange, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/SpellDuration.dbc", spelldurationFormat, true, dbcSpellDuration, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/ItemRandomProperties.dbc", randompropsFormat, true, dbcRandomProps, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/AreaTable.dbc", areatableFormat, true, dbcArea, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/FactionTemplate.dbc", factiontemplatedbcFormat, true, dbcFactionTemplate, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/Faction.dbc", factiondbcFormat, true, dbcFaction, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/TaxiNodes.dbc", dbctaxinodeFormat, false, dbcTaxiNode, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/TaxiPath.dbc", dbctaxipathFormat, false, dbcTaxiPath, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/TaxiPathNode.dbc", dbctaxipathnodeFormat, false, dbcTaxiPathNode, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/CreatureSpellData.dbc", creaturespelldataFormat, true, dbcCreatureSpellData, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/CreatureFamily.dbc", creaturefamilyFormat, true, dbcCreatureFamily, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/ChrRaces.dbc", charraceFormat, true, dbcCharRace, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/ChrClasses.dbc", charclassFormat, true, dbcCharClass, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/Map.dbc", mapentryFormat, true, dbcMap, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/AuctionHouse.dbc", auctionhousedbcFormat, true, dbcAuctionHouse, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/ItemRandomSuffix.dbc", itemrandomsuffixformat, true, dbcItemRandomSuffix, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/gtCombatRatings.dbc", gtfloatformat, false, dbcCombatRating, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/ChatChannels.dbc", chatchannelformat, true, dbcChatChannels, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/DurabilityQuality.dbc", durabilityqualityFormat, true, dbcDurabilityQuality, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/DurabilityCosts.dbc", durabilitycostsFormat, true, dbcDurabilityCosts, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/BankBagSlotPrices.dbc", bankslotpriceformat, true, dbcBankSlotPrices, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/StableSlotPrices.dbc", bankslotpriceformat, true, dbcStableSlotPrices, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/gtChanceToMeleeCrit.dbc", gtfloatformat, false, dbcMeleeCrit, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/gtChanceToMeleeCritBase.dbc", gtfloatformat, false, dbcMeleeCritBase, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/gtChanceToSpellCrit.dbc", gtfloatformat, false, dbcSpellCrit, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/gtChanceToSpellCritBase.dbc", gtfloatformat, false, dbcSpellCritBase, false);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/gtRegenMPPerSpt.dbc", gtfloatformat, false, dbcMPRegenBase, false); //it's not a mistake.
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/gtOCTRegenMP.dbc", gtfloatformat, false, dbcMPRegen, false); //it's not a mistake.
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/gtRegenHPPerSpt.dbc", gtfloatformat, false, dbcHPRegenBase, false); //it's not a mistake.
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/gtOCTRegenHP.dbc", gtfloatformat, false, dbcHPRegen, false); //it's not a mistake.
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/AreaTrigger.dbc", areatriggerformat, true, dbcAreaTrigger, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/QuestXP.dbc", questxpformat, false, dbcQuestXP, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/QuestFactionReward.dbc", questrewrepformat, false, dbcQuestRewRep, true);
	printf("mem usage : %f\n",GetMemUsage() );
	LOAD_DBC("DBC/CharTitles.dbc", chartitleFormat, true, dbcCharTitle, true);
	printf("mem usage : %f\n",GetMemUsage() );
	return true;
}


