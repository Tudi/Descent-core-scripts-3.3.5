/*

Purpuse : make modifications in dbc file for ascent project to set values that are missing for spells in able to work
Warning : Output result is changed in order to obtain ascent specific data. Do not try to use or interpret data for anything else
Warning : SpellEntry + sql_translation_table + SPELL_ENTRY must have the same structure !!!

project status : not finished yet..not tested

*/

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>
#include <windows.h>

#include "../../../src/arcemu-shared/Database/dbcfile.h"
#include "../../../src/arcemu-shared/crc32.cpp"

#include "defines.h"

DBCFile dbc;

//make this after the main
void dump_as_sql(TCHAR *inf);

void print_usage()
{
	printf("Usage ex: Spell_Fixes.exe -conv inf=Spell.dbc\n");
	printf("parameters: -h output this help message\n");
	printf("parameters: -conv dump DBC as sql\n");
	printf("parameters: inf= specify the input filename(no spaces)\n");
}

//-dofix inf=spell.dbc
//-conv inf=spell.dbc
void main(int argc, TCHAR* argv[])
{
	int dotask=0;
	TCHAR file_name[300];//store the input filename
	file_name[0]=0;

	//make sure it is morron proof. Ever met a guy clicking all the next buttons in an install kit without reading 1 line ? :P
	if(argc<=1)
	{
//		printf("For safety mesures this program cannot be run without parameters. Type -h for help\n");
		print_usage();
		//exit(1);
		sprintf(file_name,"Spell.dbc");
		dotask = 2;
	}
	//maybe right now we do not have a lot of options but what the hack, let's make it fancy :)
	for (int i=1; i<argc; i++)
	{
		int arglen=(int)strlen(argv[i]);
		if (strnicmp(argv[i],"-h",2)==0) print_usage();
		if (strnicmp(argv[i],"-conv",5)==0) dotask=2;
		if (strnicmp(argv[i],"-imp",4)==0) dotask=3;
		if (strnicmp(argv[i],"inf=",4)==0) strcpy(file_name,argv[i]+4);
		
	}

	//we will work with this anyway. This whole tool is about this var :P
	if(strlen(file_name)<2)
	{
		printf("This tool is designed for some special purpuse and it needs an imput file \n");
		print_usage();
		exit(1);
	}

	dbc.open(file_name);

	if(!dbc.getFieldCount())
	{
		printf("error, could not open dbc file\n");
		exit(1);
	}
	else printf("Opened DBC with %u fields and %u rows\n",(int)dbc.getFieldCount(),(int)dbc.getRecordCount());

	switch(dotask)
	{
		case 2:		dump_as_sql(file_name);		break;
		default:								break;
	}
//	getch();
}

__int64 getfilesize(TCHAR *infname)
{
	FILE *inf=fopen(infname,"r");
	if(!inf)
	{
		printf("error ocured while opening file\n");
		exit(1);
	}
	fpos_t len;
	fseek(inf,0,SEEK_END);
	fgetpos(inf,&len);
	fclose(inf);
	return len;
}

void dump_as_sql(TCHAR *inf)
{
	if(SPELL_COLUMN_COUNT!=dbc.getFieldCount())
	{
		printf("error,column counts do not match update code for latest dbc format, us %u them %u\n",SPELL_COLUMN_COUNT,dbc.getFieldCount());
		exit(1);
	}

	printf("will start dumping data into sql file (only requested fields!)\n");

	FILE *fsql=fopen("dbc_spell.sql","w");

	//drop table if already exist
	fprintf(fsql,"%s","DROP TABLE IF EXISTS `dbc_spell`;\n");

	//create the table
	fprintf(fsql,"%s","CREATE TABLE dbc_spell (\n");

	uint32 i2=0;
	for(uint32 i=0;i<SPELL_COLUMN_COUNT;i++)
		if(spellentryFormat[i]!='x')
		{
			if(spellentryFormat[i]=='u')
				fprintf(fsql,"\t `%s` INT (11) UNSIGNED DEFAULT '0' NOT NULL,\n",sql_translation_table[i2][1]);
			else if(spellentryFormat[i]=='i')
				fprintf(fsql,"\t `%s` INT (11) DEFAULT '0' NOT NULL,\n",sql_translation_table[i2][1]);
			else if(spellentryFormat[i]=='f')
				fprintf(fsql,"\t `%s` FLOAT DEFAULT '0' NOT NULL,\n",sql_translation_table[i2][1]);
			else if(spellentryFormat[i]=='s')
				fprintf(fsql,"\t `%s` VARCHAR(2000),\n",sql_translation_table[i2][1]);
			i2++;
		}

	fprintf(fsql,"%s","PRIMARY KEY(id), UNIQUE(id), INDEX(id));\n");

	fprintf(fsql,"\n\n");
	//start dumping the data from the DBC

	char tstr[2000];
	for(uint32 j=0;j<dbc.getRecordCount();j++)
	{
		//we start a new insert block
		if((j % SQL_INSERTS_PER_QUERY) == 0)
		{
			i2=0;
			fprintf(fsql,"%s","INSERT INTO dbc_spell (");
			for(uint32 i=0;i<SPELL_COLUMN_COUNT-1;i++)
				if(spellentryFormat[i]!='x')
				{
					fprintf(fsql,"`%s`,",sql_translation_table[i2][1]);
					i2++;
				}
			fprintf(fsql,"`%s`) values \n",sql_translation_table[i2][1]);
			fprintf(fsql," (");
		}
		else
			fprintf(fsql,",(");
		for(uint32 i=0;i<SPELL_COLUMN_COUNT;i++)
			if(spellentryFormat[i]!='x')
			{
				if(i!=0)
					fprintf(fsql,",");
				if(spellentryFormat[i]=='u')
					fprintf(fsql,"%u",dbc.getRecord(j).getUInt(i));
				else if(spellentryFormat[i]=='i')
					fprintf(fsql,"%d",dbc.getRecord(j).getInt(i));
				else if(spellentryFormat[i]=='f')
					fprintf(fsql,"%f",dbc.getRecord(j).getFloat(i));
				else if(spellentryFormat[i]=='s')
				{
					const char *dstr=dbc.getRecord(j).getString(i);
					int otherindex=0;
					for(unsigned int k=0;k<=strlen(dstr);k++)
						if(dstr[k]=='\'' || dstr[k]=='"')
						{
							tstr[otherindex++] = '\\';
							tstr[otherindex++] = dstr[k];
						}
						else
							tstr[otherindex++] = dstr[k];
					fprintf(fsql,"\"%s\"",tstr);
				}
			}
		//we need to end an insert block
		if(((j+1) % SQL_INSERTS_PER_QUERY)==0)
			fprintf(fsql,");\n");
		else fprintf(fsql,")\n");
	}
	fprintf(fsql,";");

	fprintf(fsql,"\n\n");

	fclose(fsql);
}
