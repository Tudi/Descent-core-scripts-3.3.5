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
#define SWIMMING_TOLERANCE_LEVEL -0.08f
#define MOVEMENT_PACKET_TIME_DELAY 400	//might be caused by emu sending packet in delayed mode

void WorldSession::HandleMoveWorldportAckOpcode( WorldPacket & recv_data )
{
	GetPlayer()->SetPlayerStatus(NONE);
	if(_player->IsInWorld())
	{
		// get outta here
		return;
	}
	sLog.outDebug( "WORLD: got MSG_MOVE_WORLDPORT_ACK." );
	
	if(_player->m_CurrentTransporter && _player->GetMapId() != _player->m_CurrentTransporter->GetMapId())
	{
		/* wow, our pc must really suck. */
		Transporter * pTrans = _player->m_CurrentTransporter;
		float c_tposx = pTrans->GetPositionX() + _player->m_TransporterX;
		float c_tposy = pTrans->GetPositionY() + _player->m_TransporterY;
		float c_tposz = pTrans->GetPositionZ() + _player->m_TransporterZ;

		WorldPacket dataw(SMSG_NEW_WORLD, 20);
		dataw << pTrans->GetMapId() << c_tposx << c_tposy << c_tposz << _player->GetOrientation();
		SendPacket(&dataw);
	}
	else
	{
		_player->m_TeleportState = 2;
		_player->AddToWorld();
	}
}

void WorldSession::HandleMoveTeleportAckOpcode( WorldPacket & recv_data )
{
//	uint64 guid;
	WoWGuid guid;
	recv_data >> guid;
//	if(guid == _player->GetGUID())
	if(guid.GetOldGuid() == _player->GetGUID())
	{
		if(sWorld.antihack_teleport && !(HasPermissions() && sWorld.no_antihack_on_gm) && _player->GetPlayerStatus() != TRANSFER_PENDING)
		{
			/* we're obviously cheating */
			sCheatLog.writefromsession(this, "Used teleport hack, disconnecting.");
			GetPlayer()->SoftDisconnect();
			return;
		}

		if(sWorld.antihack_teleport && !(HasPermissions() && sWorld.no_antihack_on_gm) && _player->m_position.Distance2DSq(_player->m_sentTeleportPosition) > 625.0f)	/* 25.0f*25.0f */
		{
			/* cheating.... :( */
			sCheatLog.writefromsession(this, "Used teleport hack {2}, disconnecting.");
			GetPlayer()->SoftDisconnect();
			return;
		}

		sLog.outDebug( "WORLD: got MSG_MOVE_TELEPORT_ACK." );
		GetPlayer()->SetPlayerStatus(NONE);
		if( GetPlayer()->m_rooted <= 0 )
			GetPlayer()->SetMovement(MOVE_UNROOT);
		_player->SpeedCheatReset();

		if(_player->m_sentTeleportPosition.x != 999999.0f)
		{
//			_player->m_position = _player->m_sentTeleportPosition;
			_player->SetPosition( _player->m_sentTeleportPosition );
			_player->m_sentTeleportPosition.ChangeCoords(999999.0f,999999.0f,999999.0f);
		}

		if(GetPlayer()->GetSummon() != NULL)		// move pet too
			GetPlayer()->GetSummon()->SetPosition((GetPlayer()->GetPositionX() + 2), (GetPlayer()->GetPositionY() + 2), GetPlayer()->GetPositionZ(), float(M_PI));
	}

}

void _HandleBreathing(MovementInfo &movement_info, Player * _player, WorldSession * pSession)
{

	// no water breathing is required
	if( !sWorld.BreathingEnabled || _player->FlyCheat || _player->m_bUnlimitedBreath || !_player->isAlive() || _player->bInvincible )
	{
		// player is flagged as in water or lava or slime
		if( _player->m_UnderwaterState & (UNDERWATERSTATE_SWIMMING |UNDERWATERSTATE_LAVA | UNDERWATERSTATE_SLIME ) )
			_player->m_UnderwaterState &= ~(UNDERWATERSTATE_SWIMMING |UNDERWATERSTATE_LAVA | UNDERWATERSTATE_SLIME );

		// player is flagged as under water
		if( _player->m_UnderwaterState & UNDERWATERSTATE_UNDERWATER )
		{
			_player->m_UnderwaterState &= ~UNDERWATERSTATE_UNDERWATER;
			WorldPacket data(SMSG_START_MIRROR_TIMER, 20);
			data << uint32( TIMER_BREATH ) << _player->m_UnderwaterTime << _player->m_UnderwaterMaxTime << int32(-1) << uint32(0);
			pSession->SendPacket(&data);
		}

		// player is above water level
		if( pSession->m_bIsWLevelSet )
		{
			if( ( movement_info.z + _player->m_noseLevel ) > pSession->m_wLevel )
			{
				_player->RemoveAurasByInterruptFlag( AURA_INTERRUPT_ON_LEAVE_WATER );
				// unset swim session water level
				pSession->m_bIsWLevelSet = false;
			}
		}

		return;
	}

	//check lava and slime
	uint8 terraininfo = sTerrainMgr.GetLiquidFlags( _player->GetMapId(), movement_info.x, movement_info.y, movement_info.z );
	if( terraininfo & MAP_LIQUID_TYPE_MAGMA )
		_player->m_UnderwaterState |= UNDERWATERSTATE_LAVA;
	if( terraininfo & MAP_LIQUID_TYPE_SLIME )
		_player->m_UnderwaterState |= UNDERWATERSTATE_SLIME;

	//player is swiming and not flagged as in the water
	if( movement_info.flags & MOVEFLAG_SWIMMING && !( _player->m_UnderwaterState & UNDERWATERSTATE_SWIMMING ) )
	{
		// dismount if mounted
		_player->RemoveAurasByInterruptFlag( AURA_INTERRUPT_ON_ENTER_WATER );

		// get water level only if it was not set before
		if( !pSession->m_bIsWLevelSet )
		{
			// water level is somewhere below the nose of the character when entering water
			pSession->m_wLevel = movement_info.z + _player->m_noseLevel * 0.95f;
			pSession->m_bIsWLevelSet = true;
		}

		_player->m_UnderwaterState |= UNDERWATERSTATE_SWIMMING;
	}

	// player is not swimming and is not stationary and is flagged as in the water
	if( ( movement_info.flags & ( MOVEFLAG_SWIMMING | MOVEFLAG_MOVE_STOP ) ) == 0 && _player->m_UnderwaterState & UNDERWATERSTATE_SWIMMING )
	{
		// player is above water level
		if( ( movement_info.z + _player->m_noseLevel ) > pSession->m_wLevel )
		{
			_player->RemoveAurasByInterruptFlag( AURA_INTERRUPT_ON_LEAVE_WATER );
	
			// unset swim session water level
			pSession->m_bIsWLevelSet = false;

			_player->m_UnderwaterState &= ~UNDERWATERSTATE_SWIMMING;
		}
	}

	// player is flagged as in the water and is not flagged as under the water
	if( _player->m_UnderwaterState & UNDERWATERSTATE_SWIMMING && !( _player->m_UnderwaterState & UNDERWATERSTATE_UNDERWATER ) )
	{
		//the player is in the water and has gone under water, requires breath bar.
		if( ( movement_info.z + _player->m_noseLevel ) < pSession->m_wLevel )
		{
			_player->m_UnderwaterState |= UNDERWATERSTATE_UNDERWATER;
			WorldPacket data(SMSG_START_MIRROR_TIMER, 20);
			data << uint32( TIMER_BREATH ) << _player->m_UnderwaterTime << _player->m_UnderwaterMaxTime << int32(-1) << uint32(0);
			pSession->SendPacket(&data);
		}
	}

	// player is flagged as in the water and is flagged as under the water
	if( _player->m_UnderwaterState & UNDERWATERSTATE_SWIMMING && _player->m_UnderwaterState & UNDERWATERSTATE_UNDERWATER )
	{
		//the player is in the water but their face is above water, no breath bar neeeded.
		if( ( movement_info.z + _player->m_noseLevel ) > pSession->m_wLevel )
		{
			_player->m_UnderwaterState &= ~UNDERWATERSTATE_UNDERWATER;
			WorldPacket data(SMSG_START_MIRROR_TIMER, 20);
			data << uint32( TIMER_BREATH ) << _player->m_UnderwaterTime << _player->m_UnderwaterMaxTime << int32(10) << uint32(0);
			pSession->SendPacket(&data);
		}
	}

	// player is flagged as not in the water and is flagged as under the water
	if( !( _player->m_UnderwaterState & UNDERWATERSTATE_SWIMMING ) && _player->m_UnderwaterState & UNDERWATERSTATE_UNDERWATER )
	{
		//the player is out of the water, no breath bar neeeded.
		if( ( movement_info.z + _player->m_noseLevel ) > pSession->m_wLevel )
		{
			_player->m_UnderwaterState &= ~UNDERWATERSTATE_UNDERWATER;
			WorldPacket data(SMSG_START_MIRROR_TIMER, 20);
			data << uint32( TIMER_BREATH ) << _player->m_UnderwaterTime << _player->m_UnderwaterMaxTime << int32(10) << uint32(0);
			pSession->SendPacket(&data);
		}
	}

}

// Zack : i'm not shitting you. There is a hack to move some other player by chaning the "mover guid" inside the packet 
// to prevent this we should know the active mover guid all the time and skip all other packets
void WorldSession::HandleMovementOpcodes( WorldPacket & recv_data )
{
	bool moved = true;
	
	if(!_player->IsInWorld() || _player->m_uint32Values[UNIT_FIELD_CHARMEDBY] || _player->GetPlayerStatus() == TRANSFER_PENDING || _player->GetTaxiState())
	{ 
		return;
	}

	// spell cancel on movement, for now only fishing is added
	Object * t_go = _player->m_SummonedObject;
	if (t_go)
	{
		if (t_go->GetEntry() == GO_FISHING_BOBBER)
			SafeGOCast(t_go)->EndFishing(GetPlayer(),true);
	}

	/************************************************************************/
	/* Clear standing state to stand.				                        */
	/************************************************************************/
	if( recv_data.GetOpcode() == MSG_MOVE_START_FORWARD )
		_player->SetStandState( STANDSTATE_STAND );
	/************************************************************************/
	/* Make sure the packet is the correct size range.                      */
	/************************************************************************/
	if (recv_data.size() > sizeof(MovementInfo) + 16) 
	{ 
		GetPlayer()->SoftDisconnect(); 
		return; 
	}

	/************************************************************************/
	/* Read Movement Data Packet                                            */
	/************************************************************************/
	movement_info.init(recv_data);

	//stupid WPE hack that crashes other clients
	if( *(uint32*)&movement_info.z == 0xFFFFFFFE || movement_info.z <= -5000 || movement_info.z >= 5000 )
	{
		sCheatLog.writefromsession(this, "Player %s is probably WPE plane hacking with z = %f.",_player->GetName(),movement_info.z);
		GetPlayer()->SoftDisconnect();
		return; //!! do not send corrupted packet to others or they will 132 crash
	}

	//WPE FLYHACK enable check
	if( recv_data.GetOpcode() == CMSG_MOVE_SET_FLY 
		&& !(!sWorld.antihack_flight || _player->m_TransporterGUID != 0 || _player->GetTaxiState() || (sWorld.no_antihack_on_gm && _player->GetSession()->HasPermissions()) )
		&& !_player->flying_aura && !_player->FlyCheat
		)
	{
		_player->BroadcastMessage( "Flyhack detected. In case server was wrong then make a report how to reproduce this case. You will be logged out in 7 seconds." );
		sCheatLog.writefromsession( _player->GetSession(), "Caught %s fly hacking", _player->GetName() );
		sEventMgr.AddEvent( _player, &Player::_Kick, EVENT_PLAYER_KICK, 7000, 1, 0 );
	}

	/************************************************************************/
	/* Update player movement state                                         */
	/************************************************************************/
	
	switch( recv_data.GetOpcode() )
	{
	case MSG_MOVE_START_FORWARD:
	case MSG_MOVE_START_BACKWARD:
		_player->moving = true;
		break;
	case MSG_MOVE_START_STRAFE_LEFT:
	case MSG_MOVE_START_STRAFE_RIGHT:
		_player->strafing = true;
		break;
/*	case MSG_MOVE_JUMP:
		_player->jumping = true;
		break;*/
	case MSG_MOVE_STOP:
		_player->moving = false;
		break;
	case MSG_MOVE_STOP_STRAFE:
		_player->strafing = false;
		break;
/*	case MSG_MOVE_FALL_LAND:
		_player->jumping = false;
		break;*/
	default:
		moved = false;
		break;
	}
	
	if( moved )
	{
		if( !_player->moving && !_player->strafing && !_player->jumping )
			_player->m_isMoving = false;
		else
			_player->m_isMoving = true;
		_player->last_moved = getMSTime();
	}

	//update the detector -> make sure hearthbeat messages are not eaten by below code !
	if( sWorld.antihack_speed )
	{
		if( !_player->GetTaxiState() && _player->m_TransporterGUID == 0 )
		{
			// simplified: just take the fastest speed. less chance of fuckups too
			float speed = ( _player->flying_aura ) ? _player->m_flySpeed : ( _player->m_swimSpeed >_player-> m_runSpeed ) ? _player->m_swimSpeed : _player->m_runSpeed;

			_player->SDetector->AddSample( movement_info.x, movement_info.y, movement_info.time, speed );

			if( _player->SDetector->IsCheatDetected() )
				_player->SDetector->ReportCheater( _player );
		}
		else
			_player->SDetector->EventSpeedChange();
	}

	//avoid accepting client spamming us with updates. If the change is so small it is not worth updating then ignore whole packet
#define UNWORTHY_POS_UPDATE_SIZE 0.25
#define UNWORTHY_ORIENTATION_UPDATE_SIZE ( 6.28 / 32 )
	if( recv_data.GetOpcode() == _player->last_received_move_opcode
		&& abs( _player->GetPositionX() - movement_info.x ) < UNWORTHY_POS_UPDATE_SIZE
		&& abs( _player->GetPositionY() - movement_info.y ) < UNWORTHY_POS_UPDATE_SIZE
		&& abs( _player->GetPositionZ() - movement_info.z ) < UNWORTHY_POS_UPDATE_SIZE
		&& abs( _player->GetOrientation() - movement_info.orientation ) < UNWORTHY_ORIENTATION_UPDATE_SIZE )
	{
//printf("!!!!!!! eliminated packet sending\n");
		return;
	}
	_player->last_received_move_opcode = recv_data.GetOpcode();

	if( _player->GetVehicle() && movement_info.guid_320.GetOldGuid() == _player->GetVehicle()->GetGUID() )
	{
		Vehicle *veh = _player->GetVehicle( );
		if( veh && veh->GetVehicleController() == _player )
			veh->MoveVehicle( movement_info.x, movement_info.y, movement_info.z, movement_info.orientation );
	}

	// if we are simply moving.
	// todo need to check and confirm all this
	//check infinit fall
	if( ( movement_info.flags & MOVEFLAG_FALLING ) 
		&& abs( _player->z_axisposition - movement_info.z ) > 200
		)
	{
		float suggested_z = _player->GetMapMgr()->GetLandHeight( _player->GetPositionX(), _player->GetPositionY(), movement_info.z );
		if( suggested_z != VMAP_VALUE_NOT_INITIALIZED )
		{
			_player->SafeTeleport( _player->GetMapId(), _player->GetInstanceID(), _player->GetPositionX(), _player->GetPositionY(), suggested_z+10, _player->GetOrientation() );
		}
	}
//printf("prinf Our height %f and suggested one %f flags %u and f2 %u\n",movement_info.z,sSVMaps.GetHeight( _player->GetMapId(), movement_info.x, movement_info.y, movement_info.z ),movement_info.flags,movement_info.flag16);
//printf("prinf Our height %f and suggested one %f \n",movement_info.z,sTerrainMgr.GetHeight( _player->GetMapId(), movement_info.x, movement_info.y, movement_info.z ));
//printf("prinf area id %d, liquid flags %d \n",sTerrainMgr.GetAreaID( _player->GetMapId(), movement_info.x, movement_info.y, movement_info.z ),sTerrainMgr.GetLiquidFlags( _player->GetMapId(), movement_info.x, movement_info.y, movement_info.z ));
	//add this sample to our heightMapCollector
	if( 
//		movement_info.flags <= MOVEFLAG_STRAFE_RIGHT 
		movement_info.flags <= (1 << 7 ) 
		&& movement_info.movementflags == 0 
		&& recv_data.GetOpcode() != MSG_MOVE_FALL_LAND
		&& movement_info.FallTime == 0
		&& _player->GetTaxiState() == false
		&& _player->m_TransporterGUID == 0
		)
	{
		sSVMaps.AddSample( _player->GetMapId(), movement_info.x, movement_info.y, movement_info.z );
//		printf("!!! add sample !! and f1 = %u and f2 = %u, ft = %u\n",movement_info.flags,movement_info.flag16,movement_info.FallTime );
	}

//printf("opcode %u and difs %f,%f,%f,%f\n",_player->last_received_move_opcode,abs( _player->GetPositionX() - movement_info.x ),abs( _player->GetPositionY() - movement_info.y ),abs( _player->GetPositionZ() - movement_info.z ),abs( _player->GetOrientation() - movement_info.orientation ));

	/*Anti Multi-Jump Check*/
	if( recv_data.GetOpcode() == MSG_MOVE_JUMP && _player->jumping == true && !GetPermissionCount())
	{
		sCheatLog.writefromsession(this, "Detected jump hacking for player %s",_player->GetName() );
		GetPlayer()->SoftDisconnect();
		return;
	}
	if( recv_data.GetOpcode() == MSG_MOVE_FALL_LAND || (movement_info.flags & MOVEFLAG_SWIMMING) )
		_player->jumping = false;
	if( !_player->jumping && (recv_data.GetOpcode() == MSG_MOVE_JUMP || (movement_info.flags & MOVEFLAG_FALLING)))
		_player->jumping = true;

	/************************************************************************/
	/* Remove Emote State                                                   */
	/************************************************************************/
	if(_player->m_uint32Values[UNIT_NPC_EMOTESTATE])
		_player->SetUInt32Value(UNIT_NPC_EMOTESTATE,0);

	/************************************************************************/
	/* Make sure the co-ordinates are valid.                                */
	/************************************************************************/
	if( !((movement_info.y >= _minY) && (movement_info.y <= _maxY)) || !((movement_info.x >= _minX) && (movement_info.x <= _maxX)) )
	{
		GetPlayer()->SoftDisconnect();
		return;
	}

	/************************************************************************/
	/* Dump movement flags - Wheee!                                         */
	/************************************************************************/
#if 0
	printf("=========================================================\n");
	printf("Full movement flags: 0x%.8X\n", movement_info.flags);
	uint32 z, b;
	for(z = 1, b = 1; b < 32;)
	{
		if(movement_info.flags & z)
			printf("   Bit %u (0x%.8X or %u) is set!\n", b, z, z);

		z <<= 1;
		b+=1;
	}
	printf("=========================================================\n");
#endif

	/************************************************************************/
	/* Orientation dumping                                                  */
	/************************************************************************/
#if 0
	printf("Packet: 0x%03X (%s)\n", recv_data.GetOpcode(), LookupName( recv_data.GetOpcode(), g_worldOpcodeNames ) );
	printf("Orientation: %.10f\n", movement_info.orientation);
#endif

	/************************************************************************/
	/* Calculate the timestamp of the packet we have to send out            */
	/************************************************************************/
	size_t pos = (size_t)m_MoverWoWGuid.GetNewGuidLen() + 1;
	/************************************************************************/
	/* Copy into the output buffer.                                         */
	/************************************************************************/
	if(_player->m_inRangePlayers.size())
	{
		int32 move_time;
//		move_time = (movement_info.time - (mstime - m_clientTimeDelay)) + MOVEMENT_PACKET_TIME_DELAY + mstime;
		//zack : client sends time as he's getmstime(). Server ads lag compensation to server getmstime() and sends to other clients
		// destination client tries to compensate lag. If we send a smaller timestamp, he will move target frither then he is
		// if we send larger timestamp then it will start moving after X seconds as moving at src client
		// do we need to add lag to destination client or only source client ?
//			move_time = movement_info.time + 4000; - used as experiment : others see me react after 4 seconds delay
		//we need to sincronize the 2 clocks for the 2 clients
//		move_time = getMSTime() + _latency + 100; // let's have a relative value to be able to track lag for different clients
		move_time = getMSTime() + _latency; // maybe client will handle latency compensation ?
//		memcpy(&movement_packet[pos], recv_data.contents(), recv_data.size());
		memcpy(movement_packet, recv_data.contents(), recv_data.size());	//3.2 movement packet includes mover guid
		*(uint32*)&movement_packet[pos+6] = move_time;

		/************************************************************************/
		/* Distribute to all inrange players.                                   */
		/************************************************************************/
		for(set<Player*>::iterator itr = _player->m_inRangePlayers.begin(); itr != _player->m_inRangePlayers.end(); ++itr)
		{
			//removing client lag compensation. I think this is handled by client. Or we need to add it at each syncronized packet not just movement
//			*(uint32*)&movement_packet[pos+6] = uint32(move_time + (*itr)->GetSession()->m_clientTimeDelay);
//			*(uint32*)&movement_packet[pos+6] = uint32(move_time - (*itr)->GetSession()->_latency);
			/**/
//printf("our client delay %d, he's client delay %u, our latency %u, he's latency %u\n",m_clientTimeDelay,(*itr)->GetSession()->m_clientTimeDelay,_latency,(*itr)->GetSession()->_latency);
#if defined(ENABLE_COMPRESSED_MOVEMENT) && defined(ENABLE_COMPRESSED_MOVEMENT_FOR_PLAYERS)
			if( _player->GetPositionNC().Distance2DSq((*itr)->GetPosition()) >= World::m_movementCompressThreshold )
				(*itr)->AppendMovementData( recv_data.GetOpcode(), uint16(recv_data.size() + pos), movement_packet );
			else
				(*itr)->GetSession()->OutPacket(recv_data.GetOpcode(), uint16(recv_data.size() + pos), movement_packet);
#else
			(*itr)->GetSession()->OutPacket(recv_data.GetOpcode(), uint16(recv_data.size() + pos), movement_packet);			
#endif
		}
	}

	/************************************************************************/
	/* Falling damage checks                                                */
	/************************************************************************/

	if( _player->blinked )
	{
		_player->blinked = false;
		_player->m_fallDisabledUntil = UNIXTIME + 5;
		_player->SpeedCheatDelay( 1000 ); //some say they managed to trigger system with knockback. Maybe they moved in air ?
	}
	else
	{
		if( recv_data.GetOpcode() == MSG_MOVE_FALL_LAND )
		{
			// player has finished falling
			//if _player->z_axisposition contains no data then set to current position
			if( !_player->z_axisposition )
				_player->z_axisposition = movement_info.z;

			// calculate distance fallen
			uint32 falldistance = float2int32( _player->z_axisposition - movement_info.z );

			/*Safe Fall*/
			if( (int32)falldistance > _player->m_safeFall )
				falldistance -= _player->m_safeFall;
			else
				falldistance = 1;
			if( _player->m_safe_fall == true )
				falldistance = 1;

			//checks that player has fallen more than 12 units, otherwise no damage will be dealt
			//falltime check is also needed here, otherwise sudden changes in Z axis position, such as using !recall, may result in death			
			if( _player->isAlive() && !_player->bInvincible && falldistance > 12 && ( UNIXTIME >= _player->m_fallDisabledUntil ) 
//				&& movement_info.FallTime > 2000	//seems like this is only sent if we jump off something and not when we break a flight
				)
			{
				// 1.7% damage for each unit fallen on Z axis over 13
				uint32 health_loss = float2int32( float( _player->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) * ( ( falldistance - 12 ) * 0.017 ) ) );
													
				if( health_loss >= _player->GetUInt32Value( UNIT_FIELD_HEALTH ) )
				{
					health_loss = _player->GetUInt32Value( UNIT_FIELD_HEALTH );
					_player->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM,2,ACHIEVEMENT_UNUSED_FIELD_VALUE,1,ACHIEVEMENT_EVENT_ACTION_ADD);
				}
				else
					_player->Event_Achiement_Received(ACHIEVEMENT_CRITERIA_TYPE_FALL_WITHOUT_DYING,ACHIEVEMENT_UNUSED_FIELD_VALUE,ACHIEVEMENT_UNUSED_FIELD_VALUE,falldistance*1000,ACHIEVEMENT_EVENT_ACTION_SET_MAX);

				_player->SendEnvironmentalDamageLog( _player->GetGUID(), DAMAGE_FALL, health_loss );
				_player->DealDamage( _player, health_loss, 0, 0, 0 );

				//_player->RemoveStealth(); // ceberwow : why again? lost stealth by AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN already. 
			}
			_player->z_axisposition = 0.0f;
		}
		else
			//whilst player is not falling, continuosly update Z axis position.
			//once player lands this will be used to determine how far he fell.
			if( !( movement_info.flags & MOVEFLAG_FALLING ) )
				_player->z_axisposition = movement_info.z;
	}

	/************************************************************************/
	/* Transporter Setup                                                    */
	/************************************************************************/
	if(!_player->m_lockTransportVariables)
	{
		if(_player->m_TransporterGUID && !movement_info.transGuid)
		{
			/* we left the transporter we were on */
			if(_player->m_CurrentTransporter)
			{
				_player->m_CurrentTransporter->RemovePlayer(_player);
				_player->m_CurrentTransporter = NULL;
			}

			_player->m_TransporterGUID = 0;
			_player->SpeedCheatReset();
		}
		else if(movement_info.transGuid)
		{
			if(!_player->m_TransporterGUID)
			{
				/* just walked into a transport */
				if(_player->IsMounted())
					_player->RemoveAura(_player->m_MountSpellId);

				_player->m_CurrentTransporter = objmgr.GetTransporter(GUID_LOPART(movement_info.transGuid));
				if(_player->m_CurrentTransporter)
					_player->m_CurrentTransporter->AddPlayer(_player);

				/* set variables */
				_player->m_TransporterGUID = movement_info.transGuid;
				_player->m_TransporterTime = movement_info.transTime;
				_player->m_TransporterX = movement_info.transX;
				_player->m_TransporterY = movement_info.transY;
				_player->m_TransporterZ = movement_info.transZ;
			}
			else
			{
				/* no changes */
				_player->m_TransporterTime = movement_info.transTime;
				_player->m_TransporterX = movement_info.transX;
				_player->m_TransporterY = movement_info.transY;
				_player->m_TransporterZ = movement_info.transZ;
			}
		}
		/*float x = movement_info.x - movement_info.transX;
		float y = movement_info.y - movement_info.transY;
		float z = movement_info.z - movement_info.transZ;
		Transporter* trans = _player->m_CurrentTransporter;
		if(trans) sChatHandler.SystemMessageToPlr(_player, "Client t pos: %f %f\nServer t pos: %f %f   Diff: %f %f", x,y, trans->GetPositionX(), trans->GetPositionY(), trans->CalcDistance(x,y,z), trans->CalcDistance(movement_info.x, movement_info.y, movement_info.z));*/
	}

	/************************************************************************/
	/* Anti-Speed Hack Checks                                               */
	/************************************************************************/

	

	/************************************************************************/
	/* Breathing System                                                     */
	/************************************************************************/
	_HandleBreathing(movement_info, _player, this);

	/************************************************************************/
	/* Remove Spells                                                        */
	/************************************************************************/
	uint32 flags = AURA_INTERRUPT_ON_MOVEMENT;
	if( !( movement_info.flags & MOVEFLAG_SWIMMING || movement_info.flags & MOVEFLAG_FALLING ) )
		flags |= AURA_INTERRUPT_ON_LEAVE_WATER;
	if( movement_info.flags & MOVEFLAG_SWIMMING )
		flags |= AURA_INTERRUPT_ON_ENTER_WATER;
	if( movement_info.flags & ( MOVEFLAG_TURN_LEFT | MOVEFLAG_TURN_RIGHT ) )
		flags |= AURA_INTERRUPT_ON_TURNING;
	_player->RemoveAurasByInterruptFlag( flags );

	/************************************************************************/
	/* Update our position in the server.                                   */
	/************************************************************************/
	if( _player->m_CurrentCharm && _player->GetMapMgr() )
	{
		Unit *cc = _player->GetMapMgr()->GetUnit( _player->m_CurrentCharm );
		if( cc )
			cc->SetPosition(movement_info.x, movement_info.y, movement_info.z, movement_info.orientation);
	}
	else
	{
		if(!_player->m_CurrentTransporter) 
		{
			if( !_player->SetPosition(movement_info.x, movement_info.y, movement_info.z, movement_info.orientation) )
			{
				_player->SetUInt32Value(UNIT_FIELD_HEALTH, 0);
				_player->KillPlayer();
			}
		}
		else
		{
			_player->SetPosition(movement_info.x, movement_info.y, movement_info.z, 
				movement_info.orientation + movement_info.transO, false);
		}
	}	
}

void WorldSession::HandleMoveTimeSkippedOpcode( WorldPacket & recv_data )
{
	
}

void WorldSession::HandleMoveNotActiveMoverOpcode( WorldPacket & recv_data )
{

}


void WorldSession::HandleSetActiveMoverOpcode( WorldPacket & recv_data )
{
	// set current movement object
	uint64 guid;
	recv_data >> guid;

	if(guid != m_MoverWoWGuid.GetOldGuid())
	{
		// make sure the guid is valid and we aren't cheating
		if( !(_player->m_CurrentCharm == guid) &&
			!(_player->GetGUID() == guid) )
		{
			// cheater!
			return;
		}

		// generate wowguid
		if(guid != 0)
			m_MoverWoWGuid.Init(guid);
		else
			m_MoverWoWGuid.Init(_player->GetGUID());

		// set up to the movement packet
		movement_packet[0] = m_MoverWoWGuid.GetNewGuidMask();
		memcpy(&movement_packet[1], m_MoverWoWGuid.GetNewGuid(), m_MoverWoWGuid.GetNewGuidLen());
	}
}

void WorldSession::HandleMoveSplineCompleteOpcode(WorldPacket &recvPacket)
{

}

void WorldSession::HandleMountSpecialAnimOpcode(WorldPacket &recvdata)
{
	WorldPacket data(SMSG_MOUNTSPECIAL_ANIM,8);
	data << _player->GetGUID();
	_player->SendMessageToSet(&data, true);
}

void WorldSession::HandleWorldportOpcode(WorldPacket & recv_data)
{
	uint32 unk;
	uint32 mapid;
	float x,y,z,o;
	recv_data >> unk >> mapid >> x >> y >> z >> o;

	//printf("\nTEST: %u %f %f %f %f", mapid, x, y, z, o);
	
	if(!_player->IsInWorld())
	{ 
		return;
	}

	if(!HasGMPermissions())
	{
		SendNotification("You do not have permission to use this function.");
		return;
	}

	LocationVector vec(x,y,z,o);
	_player->SafeTeleport(mapid,0,vec);
}

void WorldSession::HandleTeleportToUnitOpcode(WorldPacket & recv_data)
{
	uint8 unk;
	Unit * target;
	recv_data >> unk;

	if(!_player->IsInWorld())
	{ 
		return;
	}

	if(!HasGMPermissions())
	{
		SendNotification("You do not have permission to use this function.");
		return;
	}

	if( (target = _player->GetMapMgr()->GetUnit(_player->GetSelection())) == NULL )
	{ 
		return;
	}

	_player->SafeTeleport(_player->GetMapId(), _player->GetInstanceID(), target->GetPosition());
}

void WorldSession::HandleTeleportCheatOpcode(WorldPacket & recv_data)
{
	float x,y,z,o;
	LocationVector vec;

	if(!HasGMPermissions())
	{
		SendNotification("You do not have permission to use this function.");
		return;
	}

	recv_data >> x >> y >> z >> o;
	vec.ChangeCoords(x,y,z,o);
	_player->SafeTeleport(_player->GetMapId(),_player->GetInstanceID(),vec);
}

void MovementInfo::init(WorldPacket & data)
{
	transGuid = 0;
	unk13 = 0;
	data >> guid_320;	//mover guid ?
	data >> flags >> movementflags >> time;
	data >> x >> y >> z >> orientation;

	if (flags & MOVEFLAG_TAXI)
		data >> transGuid >> transX >> transY >> transZ >> transO >> transTime >> transSeat;

	if (flags & (MOVEFLAG_SWIMMING | MOVEFLAG_AIR_SWIMMING) || movementflags & 0x20)
		data >> pitch;

	data >> unklast;

	if (flags & MOVEFLAG_FALLING || flags & MOVEFLAG_REDIRECTED)
		data >> FallTime >> jump_sinAngle >> jump_cosAngle >> jump_xySpeed;

	if (flags & MOVEFLAG_SPLINE_MOVER)
		data >> spline_unk;

	if(data.rpos() != data.wpos())
	{
		if(data.rpos() + 4 == data.wpos())
			data >> unk13;
		else
			sLog.outDebug("Extra bits of movement packet left");
	}
	else unk13 = 0;
/*
{SERVER} Packet: (0x00EE) MSG_MOVE_HEARTBEAT PacketSize = 41 TimeStamp = 3167171
CF 8C 61 0C 02 80
01 
01 00 20 00
00 00 
78 51 3F D9 time
64 E6 0C C6 -x
72 4E 02 44 -y
67 50 8B 42 -z
2C C8 5B 40 -o
00 00 00 80 
A5 03 00 00 
{SERVER} Packet: (0x00DA) MSG_MOVE_SET_FACING PacketSize = 37 TimeStamp = 3167171
CF 54 9A 0F 01 80 
01 
04 00 00 00
00 00
5E 4C 3F D9
99 89 0B C6
41 75 1B 44 
C0 0B C7 42 
0A DD 78 40 
F7 00 00 00 
{CLIENT} Packet: (0x00B5) MSG_MOVE_START_FORWARD PacketSize = 30 TimeStamp = 3258093
09 00 00 00
00 00 
A8 B6 31 00
B4 D6 0B C6
3E 7C 06 C3
A2 33 A7 42
2A EB AD 40
00 00 00 00 
{SERVER} Packet: (0x00B5) MSG_MOVE_START_FORWARD PacketSize = 37 TimeStamp = 3267000
CF 64 B6 0F 02 80 01 
11 00 00 00 
00 00 
81 D1 40 D9 E2 91 0A C6 F6 79 20 C3 F4 3B A0 42 66 2D 76 3F B8 02 00 00 

	*/
}

/*
void MovementInfo::write(WorldPacket & data)
{
	data << flags << movementflags << getMSTime();

	data << x << y << z << orientation;

	if (flags & MOVEFLAG_TAXI)
		data << transGuid << transX << transY << transZ << transO << transTime << transSeat;

	if (flags & (MOVEFLAG_SWIMMING | MOVEFLAG_AIR_SWIMMING) || flag16 & 0x20)
		data << pitch;

	data << unklast;

	if (flags & MOVEFLAG_FALLING || flags & MOVEFLAG_REDIRECTED)
		data << FallTime << jump_sinAngle << jump_cosAngle << jump_xySpeed;

	if (flags & MOVEFLAG_SPLINE_MOVER)
		data << spline_unk;
	
	if(unk13)
		data << unk13;
}*/
