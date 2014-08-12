<?php
$spellentry="uint32 Id;                              //1
	uint32 Category;                        //2
	uint32 DispelType;                      //4
	uint32 MechanicsType;                   //5
	uint32 Attributes;                      //6
	uint32 AttributesEx;                    //7
	uint32 AttributesExB;                   //8
	uint32 AttributesExC;                   //9 // Flags to
	uint32 AttributesExD;                   //10 // Flags....
	uint32 AttributesExE;                   //11 // Flags 2.0.1 unknown one
	uint32 AttributesExF;					//12
	uint32 RequiredShapeShift;              //13 // Flags BitMask for shapeshift spells
	uint32 ShapeshiftExclude;               //14-> this is wrong // Flags BitMask for which shapeshift forms this spell can NOT be used in.
	uint32 Targets;                         //15 - N / M
	uint32 TargetCreatureType;              //16
	uint32 RequiresSpellFocus;              //17
	uint32 FacingCasterFlags;				//18
	uint32 CasterAuraState;                 //19
	uint32 TargetAuraState;                 //20
	uint32 ExcludeCasterAuraState;          //21 2.0.1 unknown two
	uint32 ExcludeTargetAuraState;          //22 2.0.1 unknown three
	uint32 req_aura;
	uint32 flags_unk1;
	uint32 ExcludeCasterHasAura;
	uint32 ExcludeTargetHasAura;
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
	uint32 EffectBaseDice[3];               //72 - 74
	float  EffectDicePerLevel[3];           //75 - 77
	float  EffectRealPointsPerLevel[3];     //78 - 80
	int32  EffectBasePoints[3];             //81 - 83
	int32  EffectMechanic[3];               //84 - 86       Related to SpellMechanic.dbc
	uint32 EffectImplicitTargetA[3];        //87 - 89
	uint32 EffectImplicitTargetB[3];        //90 - 92
	uint32 EffectRadiusIndex[3];            //93 - 95
	uint32 EffectApplyAuraName[3];          //96 - 98
	uint32 EffectAmplitude[3];              //99 - 101
	float  Effectunknown[3];                //102 - 104     This value is the $ value from description. Zack : Which one from many ? :D
	uint32 EffectChainTarget[3];            //105 - 107
	uint32 EffectItemType[3];			     //108 - 110	//wotlk dbc
	uint32 EffectMiscValue[3];              //111 - 113
	uint32 EffectMiscValueB[3];             //114 - 116  2.4.3
	uint32 EffectTriggerSpell[3];           //117 - 119
	float  EffectPointsPerComboPoint[3];    //120 - 122
	uint32 Unk302[9];			
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
	uint32 unkflags;                        //197 
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
	uint32 RequiresAreaId;					//214 
	uint32 School;							//215
	uint32 RuneCostID;						//216 from 3.0.1
	//uint32 SpellMissileID;					//217 from 3.0.1
";

$lines = explode("\n",$spellentry);
$formatstr="";
foreach($lines as $key => $value )
{
//	echo "or line is : $value<br>";
	$t=str_replace(array("\t","\n")," ",$value);
	$t=trim($t);
	$t=str_replace("*"," ",$t);
	$t=str_replace(";"," ",$t);
	$len = strlen($t);
	for($i=0;$i<$len;$i++)
		$t=str_replace("  "," ",$t);
//	echo "new line is : $t1<br>";
	$parts = explode(" ",$t);
//	echo $parts[0]." + ".$parts[1]." + ".$parts[2]." <br> ";

	//check type
	$format="!";
	if(strpos("#".$parts[0],"//") != 0 )
		$format="x";
	else if(strpos("#".$parts[0],"uint32") != 0 )
		$format="u";
	else if(strpos("#".$parts[0],"int32") != 0 )
		$format="i";
	else if(strpos("#".$parts[0],"float") != 0 )
		$format="f";
	else if(strpos("#".$parts[0],"char") != 0 )
		$format="s";

	//check count
	$formatc=1;
	$name="";
	if( strpos("#".$parts[1],"[") )
	{
		$subp=substr($parts[1],strpos($parts[1],"["));
		$subp=explode("[",$parts[1]);
		$subp=explode("]",$subp[1]);
		$formatc=(int)($subp[0]);
		$name = substr($parts[1],0,strpos($parts[1],"["));
	}
	else $name = $parts[1];
	if($name=="")
	{
		echo $parts[0]." + ".$parts[1]." + ".$parts[2]." <br> ";
		echo "or line is : $value<br>";
	}


	//add to format string
	for($i=0;$i<$formatc;$i++)
	{
		$formatstr.=$format;
		$outl="";
		$outl .= "{\"";
		if( $format == "u" )
			$outl .= "uint32";
		else if( $format == "i" )
			$outl .= "int32";
		else if( $format == "f" )
			$outl .= "float";
		else if( $format == "s" )
			$outl .= "str";
		else if( $format == "x" )
			continue;
		$outl .= "\",\"".$name;
		if( $formatc > 1 )
			$outl .= "_".($i+1);
		$outl .= "\"},<br>";
		echo $outl;
	}
}
echo "const char* spellentryFormat = \"$formatstr\";<br>";
?>
