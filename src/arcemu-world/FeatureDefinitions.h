#ifndef _FEATURE_DEFINITIONS_H_
#define _FEATURE_DEFINITIONS_H_

#ifdef _DEBUG
	#ifdef _CRTDBG_MAP_ALLOC
//		#define _CRTDBG_MAP_ALLOC_TEST_MEM		//some temp mem checking
		//use these only if you are not using external memory debuggers
		#ifndef SCRIPTLIB
			#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
			#define new DEBUG_NEW
		#endif
	#endif
	#if !defined(_CRTDBG_MAP_ALLOC) && !defined(WIN64) && !defined(SCRIPTLIB) && !defined(X64)
		#define USE_INTERNAL_MEM_LEAK_TRACKER
		#include "mmgr.h"
	#endif
#else
#endif

#define PRINTMEMUSAGEONLOAD
#define DISABLE_COLLISION_LOAD	1	//has a lot of mem leaks :)
#define DISABLE_GUID_RECYCLING	1	//this will leak memory like hell. BUT i needed it to debug some guid collision issue

#ifdef PRINTMEMUSAGEONLOAD
	#define	printmem(x,y) sLog.outDebug(x,y);
#else
	#define	printmem(x,y) //
#endif

//#define FORCED_GM_TRAINEE_MODE			1 //this means he cannot switch off GM mode. He has fixed DMG and health. Forced faction. No spell casts
#define FORCED_GM_BAN_LIMITATION			60*60 //given in seconds. Noob GMs are not supposed to give bigger bans then this. This is to avoid GM revenges
//#define MINIMIZE_NETWORK_TRAFIC			//this is used for very high player concentrations to send spell packets only to duelling players
//#define GENERATE_CLASS_BALANCING_STATISTICS	1	//used to bust urban legends of QQ players that say that some class is uber imba due to emu bugs
//! you need to search in files and additionall enable this !
//#define USE_OLD_EVENT_MANAGER			//the new event manager is using pools for the event lists. Stats say alloc and dealoc eats up 2 GB RAM / 5 minutes

//put 0 to disable this feature, else put a few minute size in milliseconds to monitor when GM goes AFK
#define GM_STATISTICS_UPDATE_INTERVAL		(1*60*1000)

//#define USE_PACKET_COMPRESSION				0		//counted in milliseconds. undefine to disable this feature
#define ENABLE_NAGLE_ALGORITHM				0		//nagle can reduce huge overhead for some packets. Might also create a lot of lag in case he has nothing else to group up packets with
#define CLIENT_TIMESPEED_CHEAT_TRIGGER_DC	3		//if ping packets will come with a higher rate then normal then there is a chance that client is using timespeed cheat ?

//#define CATACLYSM_SUPPORT					1		//disable this in case i forget about it. This will be used to force emu to try to support basic cataclysm support
#endif