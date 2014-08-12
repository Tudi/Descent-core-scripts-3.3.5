#ifndef _GARBAGE_COLLECTOR_H_
#define _GARBAGE_COLLECTOR_H_

#include "Singleton.h"

//the whole point of this is to avoid using dead pointers due to thread concurency
//the solution sucks but it comes to patch an already badly syncronized system

// The idea is simple :
// instead direct delete and object we insert it here and mark it as deleted
// references to object should check if this object is marked as deleted. If yes then loose reference before Garbage collector really deletes them

class Object;
class WorldSession;

//#define GARBAGE_DELETE_DELAY				2*60*1000
//#define GARBAGE_DELETE_DELAY_WS				1*60*1000	//must be smaller then char delete or inverse ? Crashes both ways :(
//#define GARBAGE_COLLECTOR_UPDATE_INTERVAL	 ( GARBAGE_DELETE_DELAY / 2)	//do not spam list update

#define GARBAGE_DELETE_DELAY				10*60*1000
#define GARBAGE_DELETE_DELAY_WS				20*60*1000	//must be smaller then char delete or inverse ? Crashes both ways :(
#define GARBAGE_COLLECTOR_UPDATE_INTERVAL	 ( 60000 )	//do not spam list update

class DelayedObjectDeletor: public Singleton<DelayedObjectDeletor>
{
public:
	DelayedObjectDeletor() { NextUpdateStamp = 0; }
	~DelayedObjectDeletor();
	void	AddObject(Object *p);
	//check what needs to be indeed Deleted
	void	Update();	
	//not sure we should use this due to performance issue. However in the future for debugging it might be used
//	bool	HasObject(Object *);
private:
	//expected size of the list is not larger then 1000 elements
	//pets, totems, temp summons.... should be inserted here
	std::map<Object *,uint32>		delete_list;	//store objects in a list and delete them after a while
	Mutex							list_lock;		//make sure to not add/remove from list at the same time
	uint32	NextUpdateStamp;
};

#define sGarbageCollection DelayedObjectDeletor::getSingleton()

#endif