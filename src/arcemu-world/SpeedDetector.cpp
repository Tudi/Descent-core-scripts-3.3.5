#include "StdAfx.h"

#define USE_CLIENT_TIME							//if we can use this then it is awsome. If not then it sucks

#ifdef USE_CLIENT_TIME
	#define SPDT_SAMPLINGRATE							50		// if speed is 8 then in 100 MS we move 0.8 yards	
	#define CHEAT_ALARMS_TO_TRIGGER_CHEAT				12		// if x alarms stack up over time then it is time to kick the player
	//if player has default speed 9 and has lag 3 seconds 30 yards is normal to happen, so we double it and make 60 yards a tel hack
	#define CHEAT_TELEPORT_PLAYER_JUMP_MIN				60		// do not trigger for blink and other spells (retrieve corpse)
	#define PACKET_LAG_CONSIDERED_TOO_SMALL				200		// in case we turn then we should not monitor speed. This could be used by hacker to constantly turn to avoid detection
	#define PACKET_LAG_CONSIDERED_TOO_MUCH				20000	// 2 sec lag is something more then we could trust
	#define CHEAT_MIN_SPEED_CONSIDERED_SIGNIFICANT		0.7f	// even float calculation have limits. Accept this error
	#define CHEAT_MIN_SPEED_PCT_CONSIDERED_SIGNIFICANT	0.2f	// even float calculation have limits. Accept this error
	#define CHEAT_MIN_SPEED_CONSIDERED_TEL_HACK			10.0f	// even float calculation have limits. Accept this error
#else
	#define SPDT_SAMPLINGRATE							50		// if speed is 8 then in 100 MS we move 0.8 yards	
	#define CHEAT_ALARMS_TO_TRIGGER_CHEAT				25		// if x alarms stack up over time then it is time to kick the player
	//if player has default speed 9 and has lag 3 seconds 30 yards is normal to happen, so we double it and make 60 yards a tel hack
	#define CHEAT_TELEPORT_PLAYER_JUMP_MIN				60		// do not trigger for blink and other spells (retrieve corpse)
	#define PACKET_LAG_CONSIDERED_TOO_SMALL				200		// in case we turn then we should not monitor speed. This could be used by hacker to constantly turn to avoid detection
	#define PACKET_LAG_CONSIDERED_TOO_MUCH				20000	// 2 sec lag is something more then we could trust
	#define CHEAT_MIN_SPEED_CONSIDERED_SIGNIFICANT		2.0f	// even float calculation have limits. Accept this error
	#define CHEAT_MIN_SPEED_PCT_CONSIDERED_SIGNIFICANT	0.3f	// even float calculation have limits. Accept this error
	#define CHEAT_MIN_SPEED_CONSIDERED_TEL_HACK			3.0f	// even float calculation have limits. Accept this error
#endif

SpeedCheatDetector::SpeedCheatDetector()
{
	EventSpeedChange();
	bigest_hacked_speed_dif = 0;
	cheat_threat = 0;
	last_stamp = last_server_stamp = 0;
	is_tel_hack_trigger = 0;
}

void SpeedCheatDetector::EventSpeedChange()
{
#ifdef _DEBUG
	sLog.outDebug("Speedchange Event occured prevspeed=%f\n",last_used_speed);
#endif
	last_x = 0;	//required for tel hack detect
	last_used_speed = 0;
	last_server_stamp = getMSTime() + 10000;
	continues_speed_overflow = 0;
}

void SpeedCheatDetector::SkipSamplingFor(int ms_delay)
{
	last_server_stamp = getMSTime() + ms_delay;
	last_used_speed = 0;	//will make speed chage reset event trigger
}

//void SpeedCheatDetector::AddSample(float x, float y, int server_stamp, int client_stamp, float player_speed)
void SpeedCheatDetector::AddSample(float x, float y, int client_stamp, float player_speed)
{
	int time_dif_server = getMSTime() - last_server_stamp;
	//don't flood with calculations. Small values might get lost in calculations
	//also takes care of the delaying of the speed detector
	if( time_dif_server <= PACKET_LAG_CONSIDERED_TOO_SMALL )
		return;
#ifdef USE_CLIENT_TIME
	int time_dif = client_stamp - last_stamp;
	//hack detection reusing same packet and having same timestamp
//	if( time_dif < PACKET_LAG_CONSIDERED_TOO_SMALL && time_dif_server > PACKET_LAG_CONSIDERED_TOO_MUCH )
//		return;
#endif
	//funny to have so much lag and not yet DC-ed. We help him get DC-ed
/*	if( time_dif_server >= PACKET_LAG_CONSIDERED_TOO_MUCH && last_stamp != 0 ) 
	{
		//this is used just in case client forgot to send us the usual every 500 ms heartbeat msg
		//abs is for out of order packets. Should not happen though
		float desync_coef =  abs( (float)time_dif / (float)time_dif_server );
		if( desync_coef > 1.2f || desync_coef < 0.8f )
		{
			cheat_threat = CHEAT_ALARMS_TO_TRIGGER_CHEAT;
			bigest_hacked_speed_dif = 0;
			return;
		}
	}*/
	//we use this to delay sampling in case of teleport
//	if( server_stamp - last_server_stamp <= SPDT_SAMPLINGRATE )
//		return;
	//we reset the system in case the monitored player changed it's speed. A small loss to avoid false triggers
	if( player_speed != last_used_speed )
	{
		EventSpeedChange();
		last_used_speed = player_speed;
	}
	//seems like we are monitored an interval. Check if we detected any speed hack in it
	else if(
//		time_dif < PACKET_LAG_CONSIDERED_TOO_MUCH &&	//this was used by JESUS to skip detection
//		time_dif > PACKET_LAG_CONSIDERED_TOO_SMALL &&	//could reuse packet with WPE and have 0 timediff all the time
		last_stamp != 0 )
	{
		//get current speed
		float dif_x = x - last_x;
		float dif_y = y - last_y;
		float dist = sqrt(dif_x*dif_x + dif_y * dif_y);
#ifdef USE_CLIENT_TIME
		float cur_speed = dist / ((float)time_dif / 1000.0f);
#else
		float cur_speed = dist / ((float)time_dif_server / 1000.0f);
#endif
		float speed_diff = cur_speed - player_speed;
		//0 sec time diff = 0% error 1 sec = 100% error chance, 100 MS = 10% for speed 8 = 0.8 yards
#ifdef _DEBUG
//		sLog.outDebug("adding speed sample dist=%f tdif=%u sp(ok)=%f sp=%f spd=%f\n",dist,time_dif,player_speed,cur_speed,speed_diff);
//		sLog.outDebug("speed=%.2f,shouldbe=%.2f,cheat=%.2f,threat=%d,time=%d,dist=%.2f\n",cur_speed,player_speed,cur_speed-player_speed,cheat_threat,time_dif_server,dist);
#endif
		if( speed_diff > CHEAT_MIN_SPEED_CONSIDERED_SIGNIFICANT && cur_speed/player_speed > CHEAT_MIN_SPEED_PCT_CONSIDERED_SIGNIFICANT)
		{
			if( speed_diff > bigest_hacked_speed_dif )
				bigest_hacked_speed_dif = speed_diff;

			//in case of a teleport this might raise warning by 5 but if not a hacker then this resets at the next update
			int32 X_times_speed = float2int32( cur_speed / player_speed );
			continues_speed_overflow += 1 + MIN( MAX(0,X_times_speed - 1), CHEAT_ALARMS_TO_TRIGGER_CHEAT / 4 );
//printf("speed x times %d,overflow count %d, threath %d, speed %.2f instead %f.2,diff %f.2",X_times_speed,continues_speed_overflow,cheat_threat,cur_speed,player_speed,cur_speed-player_speed);
			cheat_threat += continues_speed_overflow;

//			cheat_threat++;
		}
		else
		{
//			if( continues_speed_overflow > 0 )
//				continues_speed_overflow--;
			continues_speed_overflow = 0;
			if( cheat_threat > 0 )
				cheat_threat--;
		}

		if( sWorld.antihack_teleport 
			&& last_x != 0
			//make sure it was not some normal spell. A 40 Yard jump is not that serious
			&& dist > CHEAT_TELEPORT_PLAYER_JUMP_MIN
			&& speed_diff > CHEAT_MIN_SPEED_CONSIDERED_TEL_HACK	// do not trigger if this is normal (really fast mounts)
			)
		{
			cheat_threat = CHEAT_ALARMS_TO_TRIGGER_CHEAT;
			bigest_hacked_speed_dif = dist;
			is_tel_hack_trigger = 1;
		}

	}
	//mark that we are having an update server side
	last_server_stamp = getMSTime();
	//also mark client stamp so we can know this was a fair update
	last_stamp = client_stamp;
	last_x = x;
	last_y = y;
}

void SpeedCheatDetector::ReportCheater(Player *_player)
{
	if( ( sWorld.no_antihack_on_gm && _player->GetSession()->HasPermissions() ) )
		return; // do not check GMs speed been the config tells us not to.

	//toshik is wonderfull and i can't understand how he managed to make this happen
/*	if( bigest_hacked_speed_dif <= CHEAT_MIN_SPEED_CONSIDERED_SIGNIFICANT )
	{
		cheat_threat = 0;
		EventSpeedChange();
		return;
	}*/

	float speed = ( _player->flying_aura ) ? _player->m_flySpeed : ( _player->m_swimSpeed > _player->m_runSpeed ) ? _player->m_swimSpeed : _player->m_runSpeed;
	if( is_tel_hack_trigger )
	{
		_player->BroadcastMessage( "Teleport hack detected. In case server was wrong then make a report how to reproduce this case. You will be logged out in 7 seconds." );
		sCheatLog.writefromsession( _player->GetSession(), "Caught %s Teleport hacking last occurence with dist: %f ", _player->GetName(), bigest_hacked_speed_dif );
	}
	else 
	{
		_player->BroadcastMessage( "Speedhack detected. In case server was wrong then make a report how to reproduce this case. You will be logged out in 7 seconds." );
		sCheatLog.writefromsession( _player->GetSession(), "Caught %s speed hacking last occurence with speed: %f instead of %f", _player->GetName(), speed + bigest_hacked_speed_dif, speed );
	}

//	_player->EjectFromInstance(); //maybe this is not good.

	string sReason;
	if( is_tel_hack_trigger )
		sReason = "Tel hack";
	else
		sReason = "Speedhack";
	uint32 uBanTime = (uint32)UNIXTIME + 5*60; //5 minutes ban
	//_player->SetBanned( uBanTime, sReason );

	sEventMgr.AddEvent( _player, &Player::_Kick, EVENT_PLAYER_KICK, 7000, 1, 0 );

	//next check will be very far away
	last_stamp = 0x0FFFFFFF;
	cheat_threat = -100; //no more reports this session (unless flooding server :P :D )
}

char SpeedCheatDetector::IsCheatDetected()
{ 
	return cheat_threat >= CHEAT_ALARMS_TO_TRIGGER_CHEAT; 
}