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

#include "RStdAfx.h"
#include "../arcemu-shared/svn_revision.h"
#include <signal.h>

Database * Database_Character;
Database * Database_World;
bool m_stopEvent;
ServerConf sConfig;
GuidInfo sGuidInfo;
#ifdef STAT_SYS
std::string realmName="not defined";
uint32 procCnt = 0;
uint32 startTime = GetTickCount();
uint32 TotalProcTime = 0;
#endif

void _OnSignal(int s)
{
	switch (s)
	{
#if (!defined( WIN32 ) && !defined( WIN64 ) )
	case SIGHUP:
		sWorld.Rehash(true);
		break;
#endif
	case SIGINT:
	case SIGTERM:
	case SIGABRT:
#ifdef _WIN32
	case SIGBREAK:
#endif
		m_stopEvent = true;
		break;
	}
	signal(s, _OnSignal);
}

void _HookSignals()
{
	signal( SIGINT, _OnSignal );
	signal( SIGTERM, _OnSignal );
	signal( SIGABRT, _OnSignal );
#ifdef _WIN32
	signal( SIGBREAK, _OnSignal );
#else
	signal( SIGHUP, _OnSignal );
	signal(SIGUSR1, _OnSignal);
#endif
}

void _UnhookSignals()
{
	signal( SIGINT, 0 );
	signal( SIGTERM, 0 );
	signal( SIGABRT, 0 );
#ifdef _WIN32
	signal( SIGBREAK, 0 );
#else
	signal( SIGHUP, 0 );
#endif

}

#ifdef STAT_SYS
void DumpStats()
{
	//megai2: dumpit

	std::string filename = "stats.html";
	Config.MainConfig.GetString("Cluster", "Statfile", &filename);

	FILE* logfile = fopen(filename.c_str(), "w+");

	fprintf(logfile, "<html><head><title>%s statistics</title></head><body style=\"background-color: #EEE; font-family: Courier; font-size: 10pt\">", realmName.c_str());
	fprintf(logfile, "%s %s realm info</div><br>", "<div style=\" width: 100%; background-color: #888; color: #FFF; text-align: center; font-size: 15pt\">", realmName.c_str());
	if (startTime != 0)
 	{
		uint32 upTime = GetTickCount() - startTime;
		uint32 dUp = upTime / 86400000;
		uint32 hUp = (upTime - (dUp * 86400000)) / 3600000;
                uint32 mUp = (upTime - (hUp * 3600000) - (dUp * 86400000)) / 60000;
                uint32 sUp = (upTime - (mUp * 60000) - (hUp * 3600000) - (dUp * 86400000)) / 1000;
		fprintf(logfile, " Uptime: <b> <i> %u d </i> %u h </b> %u m %u s <br>", 
			dUp, hUp, mUp, sUp);
	} else {
		fprintf(logfile, " <div style=\"text-align: center; color: #F55;\">Offline</div> ");
		return;
 	}
	fprintf(logfile, " Revision: <b> %u %s </b> <br>", BUILD_REVISION, BUILD_TAG);
	
 
	std::string serverPeakColor = "E66";

	if (sClusterMgr.GetServersCount() == 6)
		serverPeakColor = "6F6";
	else if (sClusterMgr.GetServersCount() == 4)
		serverPeakColor = "666";
	else if (sClusterMgr.GetServersCount() < 4 || sClusterMgr.GetServersCount() > 6)
		serverPeakColor = "F66";

	fprintf(logfile, " Active workers peak: <span style=\"color: %s ;\"> %u </span> <br>", serverPeakColor.c_str(), sClusterMgr.GetServersCount());

	if (TotalProcTime / procCnt > 50)
		serverPeakColor = "F66";
 	else
		serverPeakColor = "6F6";

	fprintf(logfile, " Average process time: <span style=\"color: %s \"> %u </span> <br>", serverPeakColor.c_str(), TotalProcTime / procCnt);
	fprintf(logfile, " Total processes count: %u <br>", procCnt);
	fprintf(logfile, " Players online: %u <br>", sClientMgr.GetPlayersCount());
	fprintf(logfile, " Peak players online: %u <br>", sClientMgr.peakOnline);
	fprintf(logfile, " Active sessions: %u <br>" , sClientMgr.GetSessionsCount());

	bool sOnline = sClusterMgr.GetServerByMapId(0) != NULL;

	if (sOnline)
 	{
		fprintf(logfile, "Eastern Kingdoms: <span style=\"color: #0F0 \">online</span> latency: %u <br>", sClusterMgr.GetServerByMapId(0)->latency);
	} else {
		fprintf(logfile, "Eastern Kingdoms: <span style=\"color: #F00 \"><b>offline</b></span><br>");
 	}
 
	sOnline = sClusterMgr.GetServerByMapId(1) != NULL;

	if (sOnline)
 	{
		fprintf(logfile, "Kalimdor: <span style=\"color: #0F0 \">online</span> latency: %u <br>", sClusterMgr.GetServerByMapId(1)->latency);
	} else {
		fprintf(logfile, "Kalimdor: <span style=\"color: #F00 \"><b>offline</b></span><br>");
 	}
 
	sOnline = sClusterMgr.GetServerByMapId(530) != NULL;

	if (sOnline)
	{
		fprintf(logfile, "Outlands: <span style=\"color: #0F0 \">online</span> latency: %u <br>", sClusterMgr.GetServerByMapId(530)->latency);
	} else {
		fprintf(logfile, "Outlands: <span style=\"color: #F00 \"><b>offline</b></span><br>");
	}

	sOnline = sClusterMgr.GetServerByMapId(571) != NULL;

	if (sOnline)
	{
		fprintf(logfile, "Northrend: <span style=\"color: #0F0 \">online</span> latency: %u <br>", sClusterMgr.GetServerByMapId(571)->latency);
	} else {
		fprintf(logfile, "Northrend: <span style=\"color: #F00 \"><b>offline</b></span><br>");
	}

	sOnline = sClusterMgr.GetWorkerServerForNewInstance() != NULL;

	if (sOnline)
	{
		fprintf(logfile, "Instanced world: <span style=\"color: #0F0 \">online</span> latency: %u <br>", sClusterMgr.GetWorkerServerForNewInstance()->latency);
	} else {
		fprintf(logfile, "Instanced world: <span style=\"color: #F00 \"><b>offline</b></span><br>");
	}

	sOnline = sClusterMgr.GetServerByMapId(450) != NULL;

	if (sOnline)
	{
		fprintf(logfile, "Battle world: <span style=\"color: #0F0 \">online</span> latency: %u <br>", sClusterMgr.GetServerByMapId(450)->latency);
	} else {
		fprintf(logfile, "Battle world: <span style=\"color: #F00 \"><b>offline</b></span><br>");
	}

	uint32 actSessions = 0;
        uint32 sumLat = 0;

	if (sClientMgr.GetSessionsCount() != 0)
	{
		fprintf(logfile, "<div style=\" width: 100%s", "%; background-color: #888; color: #FFF; text-align: center; font-size: 15pt\">Sessions info</div>");
		
		for(uint32 j = 1; j <= sClientMgr.GetSessionsCount(); ++j)
		{
			Session* s = sClientMgr.GetSession(j);
			if (!s)
				continue;

			++actSessions;
			sumLat += s->latency;

			fprintf(logfile, "SID: %u, Acc: %s(%u), Latency: %u; &nbsp&nbsp&nbsp ", 
				j, s->GetAccountName().c_str(), s->GetAccountId(), s->latency);

			if(s->GetPlayer())
			{
				std::string classNames[11] = {
					"Воин",
					"Паладин",
					"Охотник",
					"Вор",
					"Жрец",
					"Рыцарь смерти",
					"Шаман",
					"Маг",
					"Колдун",
					"<10>"
					"Друид",
				};

				std::string raceNames[11] = {
					"Человек",
					"Орк",
					"Дварф",
					"Ночной эльф",
					"Нежить",
					"Таурен",
					"Гном",
					"<8>",
					"<9>",
					"Кровавый эльф",
					"Дреней",
				};

				RPlayerInfo* plr = s->GetPlayer();

				uint32 srvID = 0;
				uint32 pendID = s->GetTeleportPendingSID();
				if (s->GetServer())
					srvID = s->GetServer()->GetID();

				if (s->GetNextServer())
					pendID = s->GetNextServer()->GetID();

				std::string mapName = "Unknown";

				if (WorldMapInfoStorage.LookupEntry(plr->MapId))
				{
					mapName.clear();
					mapName.append(WorldMapInfoStorage.LookupEntry(plr->MapId)->name);
				}

				fprintf(logfile, "Player: %s(%u), Class: %s, Race: %s, Level: %u, Guild: %s(%u), Map: %s(%u,%u,%u), Instance: %u<br>",
					plr->Name.c_str(), plr->Guid, classNames[plr->Class-1].c_str(), 
					raceNames[plr->Race-1].c_str(), plr->Level, sClientMgr.GetGuildName(plr->GuildId).c_str(), plr->GuildId,
					mapName.c_str(), plr->MapId, srvID, pendID, plr->InstanceId);
			} else
				fprintf(logfile, "<br>");
		}
		fprintf(logfile, "Average latency: %u <br>", sumLat / actSessions);
	}

	fprintf(logfile, "</body></html>");

	fclose(logfile);

}
#endif

void LoadGuids() 
{

	sGuidInfo.globalOffset = Config.MainConfig.GetIntDefault("Cluster", "realmId", 1);
	sGuidInfo.realmsCnt = Config.MainConfig.GetIntDefault("Cluster", "realmsCnt", 8);

	uint32 maxGuid = (GLOBAL_MAX_GUID / sGuidInfo.realmsCnt) * sGuidInfo.globalOffset;
	uint32 minGuid = (GLOBAL_MAX_GUID / sGuidInfo.realmsCnt) * (sGuidInfo.globalOffset-1);
	uint32 part = (GLOBAL_MAX_GUID / sGuidInfo.realmsCnt) / MAX_ACTIVE_WS;

	QueryResult *qresult;

	for (int8 i = 0;i<MAX_ACTIVE_WS;++i)
	{
		Log.Notice("ObjMgr", "Loading guids for ws %u", i+1);

		qresult = CharacterDatabase.Query( "SELECT MAX(guid) FROM characters WHERE guid > %u AND guid < %u", minGuid + i * part, minGuid + (i + 1) * part);
		if( qresult )
		{
			sGuidInfo.m_hiPlayerGuid[i] = qresult->Fetch()[0].GetUInt32();
			delete qresult;
		}

		qresult = CharacterDatabase.Query("SELECT MAX(guid) FROM playeritems WHERE guid > %u AND guid < %u", minGuid + i * part, minGuid + (i + 1) * part);
		if( qresult )
		{
			sGuidInfo.m_hiItemGuid[i] = (uint32)qresult->Fetch()[0].GetUInt32();
			delete qresult;
		}
	
		qresult = CharacterDatabase.Query("SELECT MAX(guildid) FROM guilds WHERE guildid > %u AND guildid < %u", minGuid + i * part, minGuid + (i + 1) * part);
		if( qresult )
		{
			sGuidInfo.m_hiGuildGuid[i] = (uint32)qresult->Fetch()[0].GetUInt32();
			delete qresult;
		}
		
		qresult = CharacterDatabase.Query("SELECT MAX(message_id) FROM mailbox WHERE message_id > %u AND message_id < %u", minGuid + i * part, minGuid + (i + 1) * part);
		if( qresult )
		{
			sGuidInfo.m_mailGuid[i] = (uint32)qresult->Fetch()[0].GetUInt32();
			delete qresult;
		}
		
		qresult = CharacterDatabase.Query("SELECT MAX(auctionId) FROM auctions WHERE auctionId > %u AND auctionId < %u", minGuid + i * part, minGuid + (i + 1) * part);
		if ( qresult )
		{
			sGuidInfo.m_auctionGuid[i] = (uint32)qresult->Fetch()[0].GetUInt32();
			delete qresult;
		}

		if (sGuidInfo.m_hiPlayerGuid[i] < minGuid + i * part)
			sGuidInfo.m_hiPlayerGuid[i] = minGuid + i * part;

		if (sGuidInfo.m_hiItemGuid[i] < minGuid + i * part)
			sGuidInfo.m_hiItemGuid[i] = minGuid + i * part;

		if (sGuidInfo.m_hiGuildGuid[i] < minGuid + i * part)
			sGuidInfo.m_hiGuildGuid[i] = minGuid + i * part;

		if (sGuidInfo.m_mailGuid[i] < minGuid + i * part)
			sGuidInfo.m_mailGuid[i] = minGuid + i * part;

		if (sGuidInfo.m_auctionGuid[i] < minGuid + i * part)
			sGuidInfo.m_auctionGuid[i] = minGuid + i * part;

		Log.Success("ObjMgr", "item higuid: %u", sGuidInfo.m_hiItemGuid[i]);
		Log.Success("ObjMgr", "char higuid: %u", sGuidInfo.m_hiPlayerGuid[i]);
		Log.Success("ObjMgr", "guild higuid: %u", sGuidInfo.m_hiGuildGuid[i]);
		Log.Success("ObjMgr", "cont higuid: %u", sGuidInfo.m_hiContainerGuid[i]);
		Log.Success("ObjMgr", "mail higuid: %u", sGuidInfo.m_mailGuid[i]);
		Log.Success("ObjMgr", "auction higuid: %u", sGuidInfo.m_auctionGuid[i]);
	}

	//megai2: не учитываем бг группы
	qresult = CharacterDatabase.Query("SELECT MAX(group_id) FROM groups WHERE group_id < 2147483647");
	if( qresult )
	{
		sGuidInfo.m_hiGroupGuid = (uint32)qresult->Fetch()[0].GetUInt32();
		delete qresult;
	}

	Log.Success("ObjMgr", "group higuid: %u", sGuidInfo.m_hiGroupGuid);
}

bool InitDB()
{
	Database_World=NULL;
	Database_Character=NULL;
	string hostname, username, password, database;
	int port = 0;
	int type = 1;
	//string lhostname, lusername, lpassword, ldatabase;
	//int lport = 0;
	//int ltype = 1;
	// Configure Main Database
	
	bool result = Config.MainConfig.GetString( "WorldDatabase", "Username", &username );
	Config.MainConfig.GetString( "WorldDatabase", "Password", &password );
	result = !result ? result : Config.MainConfig.GetString( "WorldDatabase", "Hostname", &hostname );
	result = !result ? result : Config.MainConfig.GetString( "WorldDatabase", "Name", &database );
	result = !result ? result : Config.MainConfig.GetInt( "WorldDatabase", "Port", &port );
	result = !result ? result : Config.MainConfig.GetInt( "WorldDatabase", "Type", &type );
	Database_World = Database::CreateDatabaseInterface(type);

	if(result == false)
	{
		Log.Error( "sql","One or more parameters were missing from WorldDatabase directive." );
		return false;
	}

	// Initialize it
	if( !WorldDatabase.Initialize(hostname.c_str(), (unsigned int)port, username.c_str(),
		password.c_str(), database.c_str(), Config.MainConfig.GetIntDefault( "WorldDatabase", "ConnectionCount", 3 ), 16384 ) )
	{
		Log.Error( "sql","Main database initialization failed. Exiting." );
		return false;
	}

	result = Config.MainConfig.GetString( "CharacterDatabase", "Username", &username );
	Config.MainConfig.GetString( "CharacterDatabase", "Password", &password );
	result = !result ? result : Config.MainConfig.GetString( "CharacterDatabase", "Hostname", &hostname );
	result = !result ? result : Config.MainConfig.GetString( "CharacterDatabase", "Name", &database );
	result = !result ? result : Config.MainConfig.GetInt( "CharacterDatabase", "Port", &port );
	result = !result ? result : Config.MainConfig.GetInt( "CharacterDatabase", "Type", &type );
	Database_Character = Database::CreateDatabaseInterface(type);

	if(result == false)
	{
		Log.Error( "sql","One or more parameters were missing from Database directive." );
		return false;
	}

	// Initialize it
	if( !CharacterDatabase.Initialize( hostname.c_str(), (unsigned int)port, username.c_str(),
		password.c_str(), database.c_str(), Config.MainConfig.GetIntDefault( "CharacterDatabase", "ConnectionCount", 5 ), 16384 ) )
	{
		Log.Error( "sql","Main database initialization failed. Exiting." );
		return false;
	}

	return true;
 
 	Log.Line();
	return true;
}
 
int run(int argc, char *argv[])
{
	UNIXTIME = time(NULL);
	g_localTime = *localtime(&UNIXTIME);

	sLog.Init(1, 1);

    /* Print Banner */
	Log.Notice("Server", "Cluster - Realm Server r%u", BUILD_REVISION);
	Log.Line();

	Log.Notice("Config", "Loading Config Files...\n" );

	if( Config.MainConfig.SetSource("configs/arcemu-world.conf") )
		Log.Success( "Config", ">> configs/arcemu-world.conf" );
	else
	{
		Log.Error( "Config", ">> configs/arcemu-world.conf" );
		return false;
	}

	if(Config.OptionalConfig.SetSource("configs/arcemu-optional.conf"))
		Log.Success( "Config", ">> configs/arcemu-optional.conf");
	else
	{
		Log.Error("Config", ">> configs/arcemu-optional.conf");
		return false;
	}

	if(Config.RealmConfig.SetSource("configs/arcemu-realms.conf"))
		Log.Success( "Config", ">> configs/arcemu-realms.conf" );
	else
	{
		Log.Error( "Config", ">> configs/arcemu-realms.conf" );
		return false;
	}

	new ClusterMgr;
	new ClientMgr;
	ThreadPool.Startup();
	ThreadPool.IntegrityCheck();
	SetThreadName( "Main Thread" );
	Log.Line();

	if (!InitDB())
	{
		Log.Error("Startup", "Database init failed, exiting");
		return -1;
	};

	sLog.Init(Config.MainConfig.GetIntDefault("LogLevel", "File", 1), Config.MainConfig.GetIntDefault("LogLevel", "Screen", 1));
	Log.log_level = Config.MainConfig.GetIntDefault("LogLevel", "Screen", 1);

	Storage_Load();
 	Log.Success("Storage", "DBC Files Loaded...");
 
 	Log.Line();

	//megai2: грузим конфиги
	sConfig.interfaction_chat = Config.OptionalConfig.GetBoolDefault("Interfaction", "InterfactionChat", false);
	sConfig.interfaction_group = Config.OptionalConfig.GetBoolDefault("Interfaction", "InterfactionGroup", false);

 	new SocketMgr;
 	new SocketGarbageCollector;
 	sSocketMgr.SpawnWorkerThreads();
 
	new AddonMgr;

	sClientMgr.LoadGuildNames();//megai2: really shit!
	sClientMgr.LoadPlayerNames();
	sClientMgr.LoadGroups();//megai2: load it

	LoadGuids();

	/* connect to LS */
	new LogonCommHandler;
	sLogonCommHandler.Startup();

	/* main loop */

	uint32 integrCheckTmr = 0;
	m_stopEvent = false;
	std::string hostname;

 	Log.Success("Network", "Network Subsystem Started.");
	Log.Notice("Network", "Opening Client Port...");
 
 	Config.MainConfig.GetString("Listen", "Host", &hostname);

	ListenSocket<WorldSocket> * wsl = new ListenSocket<WorldSocket>(hostname.c_str(), Config.MainConfig.GetIntDefault("Listen", "WorldServerPort", 8129));
 	bool lsc = wsl->IsOpen();
	if( lsc ){
 		ThreadPool.ExecuteTask(wsl);
//		wsl->SetThreadName("Socket | WorldServerPort");
	}
 	Log.Notice("Network", "Opening Server Port...");

 	ListenSocket<WSSocket> * isl = new ListenSocket<WSSocket>(hostname.c_str(), 11010);
 	bool ssc = isl->IsOpen();
	if( ssc ){
 		ThreadPool.ExecuteTask(isl);
//		isl->SetThreadName("Socket | 11010");
	}
 
 	if(!lsc || !ssc)
 	{
 		return 1;
 	}
 
	_HookSignals();
 
	ThreadPool.KillFreeThreads(10);
	HANDLE hThread = GetCurrentThread();
 
	while(!m_stopEvent)
 	{
		uint32 start = getMSTime();
 		//wsl->Update();
 		//isl->Update();
 		sClientMgr.Update();
 		sClusterMgr.Update();
		UNIXTIME = time(NULL);
 		g_localTime = *localtime(&UNIXTIME);
		sSocketGarbageCollector.Update();
#ifdef STAT_SYS
		++procCnt;
#endif
		++integrCheckTmr;
		if (integrCheckTmr == 60 * 50) {
			integrCheckTmr = 0;
			//megai2: я вот думаю а оно вообще надо нам? =)
			//sClientMgr.SaveGroups();
#ifdef STAT_SYS
			DumpStats();
#endif
		}
		uint32 procTime = getMSTime() - start;
#ifdef STAT_SYS
		TotalProcTime += procTime;
#endif
		if (50 > procTime)
			WaitForSingleObject(hThread, (50 - procTime));
	}
 
#ifdef STAT_SYS
	startTime = 0;
	DumpStats();
#endif	

	_UnhookSignals();
	
	// begin server shutdown
	Log.Notice( "Shutdown", "Initiated at %s", ConvertTimeStampToDataTime( (uint32)UNIXTIME).c_str() );

	// send a query to wake it up if its inactive
	Log.Notice( "Database", "Clearing all pending queries..." );

	// kill the database thread first so we don't lose any queries/data
	Database_Character->EndThreads();
	Database_World->EndThreads();

	Log.Notice( "Network", "Shutting down network subsystem." );

	wsl->Close();
	Sleep(200);
	delete wsl;

	isl->Close();
	Sleep(200);
	delete isl;

#if (defined( WIN32 ) || defined( WIN64 ) )
	sSocketMgr.ShutdownThreads();
#endif
	sSocketMgr.CloseAll();

	ThreadPool.Shutdown();

	delete LogonCommHandler::getSingletonPtr();

	Log.Notice( "Database", "Closing Connections..." );
	if (Database_World != NULL)
		delete Database_World;
	if (Database_Character != NULL)
		delete Database_Character;
	Database::CleanupLibs();

	Log.Notice( "Network", "Deleting Network Subsystem..." );
	delete SocketMgr::getSingletonPtr();
	delete SocketGarbageCollector::getSingletonPtr();

	Log.Success( "Shutdown", "Shutdown complete." );

	return 0;
 }
 
int main(int argc, char *argv[])
{
	THREAD_TRY_EXECUTION2
	run(argc, argv);
	THREAD_HANDLE_CRASH2
}

 void OnCrash(bool Terminate)
 {
	printf("shit ><");
 }

