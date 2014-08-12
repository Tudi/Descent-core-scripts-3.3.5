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
// Class WorldSocket - Main network code functions, handles
// reading/writing of all packets.

#include "StdAfx.h"
#include "AuthCodes.h"

/* echo send/received packets to console */
//#define ECHO_PACKET_LOG_TO_CONSOLE 1

#ifndef CLUSTERING
#pragma pack(push, 1)
struct ClientPktHeader
{
	uint16 size;
	uint32 cmd;
};

struct ServerPktHeader
{
	uint16 size;
	uint16 cmd;
};
struct ServerPktHeaderLarge
{
	uint8  size_extension;
	uint16 size;
	uint16 cmd;
};
#pragma pack(pop)

WorldSocket::WorldSocket(SOCKET fd) : Socket(fd, sWorld.SocketSendBufSize, sWorld.SocketRecvBufSize)
{
	Authed = false;
	mSize = mOpcode = mRemaining = 0;
	_latency = 0;
	mSession = NULL;
	mSeed = 0x9B6B99 + RandomUInt() % 0xFFFF;
	pAuthenticationPacket = NULL;
	mQueued = false;
	mRequestID = 0;
	m_nagleEanbled = false;
	m_fullAccountName = NULL;
#ifdef USE_PACKET_COMPRESSION
	m_CompressedPacketsInputBuffer.reserve( WORLDSOCKET_SENDBUF_SIZE );
	m_CompressedPacketsInBuffer = 0;
#endif
}

WorldSocket::~WorldSocket()
{
	WorldPacket * pck;
	while((pck = _queue.Pop()) != 0)
		delete pck;
	_queue.Clear();	//this is already empty !

	if(pAuthenticationPacket)
	{
		delete pAuthenticationPacket;
		pAuthenticationPacket = NULL;
	}

	if(mSession)
	{
		mSession->SetSocket(NULL);
		mSession=NULL;
	}

	if( m_fullAccountName != NULL )
	{
		delete m_fullAccountName;
		m_fullAccountName = NULL;
	}
}

void WorldSocket::OnDisconnect()
{
	if(mSession)
	{
		mSession->SetSocket( NULL );
		mSession=NULL;
	}

	if(mRequestID != 0)
	{
		sLogonCommHandler.UnauthedSocketClose(mRequestID);
		mRequestID = 0;
	}

	if(mQueued)
	{
		sWorld.RemoveQueuedSocket(this);	// Remove from queued sockets.
		mQueued=false;
	}
}

void WorldSocket::OutPacket(uint16 opcode, size_t len, const void* data, bool skip_compression)
{
	OUTPACKET_RESULT res;
	if( (len + 10) > WORLDSOCKET_SENDBUF_SIZE )
	{
		printf("WARNING: Tried to send a packet of %u bytes (which is too large) to a socket. Opcode was: %u (0x%03X)\n", (unsigned int)len, (unsigned int)opcode, (unsigned int)opcode);
		return;
	}

#ifdef CATACLYSM_SUPPORT
	if( opcode == 0 )
		return;
#endif

	//can we/should we queue this as a compressed packet ?
#ifdef USE_PACKET_COMPRESSION
	if( 
//		len > 0 && 
		len <= (255-2) 
//		&& GetLatency() >= USE_PACKET_COMPRESSION 
		&& mSession && mSession->GetPlayer() && mSession->GetPlayer()->IsInWorld()
		&& skip_compression == false 
		&& opcode != SMSG_COMPRESSED_UPDATE_OBJECT 
		&& opcode != SMSG_COMPRESSED_MOVES 
		&& opcode != SMSG_PONG	//cheating latency with a quick reply ? 
		)
	{
		queueLock.Acquire();
		//if appending this next buffer will exceed our socket send buffer before we enter update loop then we try to send first tehn recheck if we can add it
		if( m_CompressedPacketsInputBuffer.size() + (len + 10) > WORLDSOCKET_SENDBUF_SIZE )
			UpdateCompressedPackets();
		//check if we can queue it now
		if( m_CompressedPacketsInputBuffer.size() + (len + 10) < WORLDSOCKET_SENDBUF_SIZE )
		{
			m_CompressedPacketsInputBuffer << uint8( len + 2 );
			m_CompressedPacketsInputBuffer << uint16( opcode );
			m_CompressedPacketsInputBuffer.append( (const char*)data, len );
			m_CompressedPacketsInBuffer++;
			queueLock.Release();
			return;
		}
		//if we got here it means that for some reason we was not able to queue it and we should try to send it normally or queue it normally
		queueLock.Release();
	}
#endif

	res = _OutPacket(opcode, len, data);
	if(res == OUTPACKET_RESULT_SUCCESS)
		return;

	if(res == OUTPACKET_RESULT_NO_ROOM_IN_BUFFER)
	{
		/* queue the packet */
		queueLock.Acquire();
		WorldPacket * pck = new WorldPacket(opcode, len);
		if(len) 
			pck->append((const uint8*)data, len);
		_queue.Push(pck);
		queueLock.Release();
	}
}

#ifdef USE_PACKET_COMPRESSION
void WorldSocket::UpdateCompressedPackets(bool nolock)
{
	if( 
//		m_CompressedPacketsInputBuffer.size() == 0 || 
		m_CompressedPacketsInBuffer == 0 )
	{
		return;
	}

	if( nolock == false )
		queueLock.Acquire();

	//there is no point in compressing less then 200 bytes. Zlib simply cannot compress such a small size
//	if( m_CompressedPacketsInputBuffer.size() < 200 && m_CompressedPacketsInBuffer < 5 )
	if( m_CompressedPacketsInputBuffer.size() * m_CompressedPacketsInBuffer < 200 )	//if there are multiple small packets then maybe it is wiser to just send them all as 1 packet. Not dead sure how this impacts network. I hope it has a positiv effect. In theory it has none.
	{
		if( nolock == false )
			queueLock.Release();
		//send the packets 1 by 1 as non compressed
		uint8 *next_content = (uint8 *)m_CompressedPacketsInputBuffer.contents(); //1 is size, 2 is opcode
		for(uint32 i=0;i<m_CompressedPacketsInBuffer;i++)
		{
			uint16 opcode = *((uint16*)(&next_content[1]));
			size_t len = (size_t)next_content[0] - 2;
			const void* data = (const void*)(next_content+3);
			OutPacket( opcode, len, data, true );
			next_content = next_content + len + 2 + 1;
		}
		m_CompressedPacketsInputBuffer.clear();
		m_CompressedPacketsInBuffer = 0;
		return;
	}
	m_CompressedPacketsInBuffer = 0;

	uint32 size = (uint32)m_CompressedPacketsInputBuffer.size();
	uint32 destsize = size + size/10 + 16;

	int rate = sWorld.getIntRate(INTRATE_COMPRESSION);
	if( rate > Z_BEST_COMPRESSION )
		rate = Z_BEST_COMPRESSION;
	else if( rate < Z_DEFAULT_COMPRESSION )
		rate = Z_DEFAULT_COMPRESSION;
	if( size <= sWorld.compression_threshold )
		rate = Z_NO_COMPRESSION;			// don't bother compressing packet smaller than this, zlib doesnt really handle them well

	// set up stream
	z_stream stream;
	stream.zalloc = 0;
	stream.zfree  = 0;
	stream.opaque = 0;

	if( deflateInit(&stream, rate) != Z_OK )
	{
		sLog.outError("deflateInit for compressed packets failed.");
		if( nolock == false )
			queueLock.Release();
		return;
	}

	uint8 *buffer = &m_CompressedPacketsOutBuffer[0];

	// set up stream pointers
	stream.next_out  = (Bytef*)buffer+4;
	stream.avail_out = destsize;
	stream.next_in   = (Bytef*)m_CompressedPacketsInputBuffer.contents();
	stream.avail_in  = size;

	// call the actual process
	if( deflate(&stream, Z_NO_FLUSH) != Z_OK 
		|| stream.avail_in != 0 
		|| deflate(&stream, Z_FINISH) != Z_STREAM_END	// finish the deflate
		|| deflateEnd(&stream) != Z_OK //finish up
		)
	{
		sLog.outError("deflate for compressed packets failed.");
		//no point entering an error loop, just dump the errored data :(
		m_CompressedPacketsInputBuffer.clear();
		if( nolock == false )
			queueLock.Release();
		return;
	}

	// fill in the full size of the compressed stream
#ifdef USING_BIG_ENDIAN
	*(uint32*)&buffer[0] = swap32(size);
#else
	*(uint32*)&buffer[0] = size;
#endif

	// send it and skip readding it to compressed buffer ;)
	//no no no, use the other send way 
	//_OutPacket( SMSG_COMPRESSED_MOVES, (uint16)stream.total_out + 4, buffer );

	//we sent it, move on kk 
	m_CompressedPacketsInputBuffer.clear();

	if( nolock == false )
		queueLock.Release();

	//send it the normal way, in case we cannot add it to socket buffer then queue sending it
	//send it after releasing mutex to avoid looping lock..though nobody cares
	OutPacket( SMSG_COMPRESSED_MOVES, (uint16)stream.total_out + 4, buffer );
}
#endif

void WorldSocket::UpdateQueuedPackets()
{
	queueLock.Acquire();

#ifdef USE_PACKET_COMPRESSION
	UpdateCompressedPackets( true );
#endif

	if(!_queue.HasItems())
	{
		queueLock.Release();
		return;
	}

	WorldPacket * pck;
	while( (pck = _queue.front()) != 0 )
	{
		/* try to push out as many as you can */
		switch(_OutPacket(pck->GetOpcode(), pck->size(), pck->size() ? pck->contents() : NULL))
		{
		case OUTPACKET_RESULT_SUCCESS:
			{
				delete pck;
				_queue.pop_front();
			}break;

		case OUTPACKET_RESULT_NO_ROOM_IN_BUFFER:
			{
				/* still connected */
				queueLock.Release();
				return;
			}break;

		default:
			{
				/* kill everything in the buffer if we are not connected anymore*/
				while((pck == _queue.Pop()))
					delete pck;
				queueLock.Release();
				return;
			}break;
		}
	}
	queueLock.Release();
}

OUTPACKET_RESULT WorldSocket::_OutPacket(uint16 opcode, size_t len, const void* data)
{
	bool rv;
	if(!IsConnected())
		return OUTPACKET_RESULT_NOT_CONNECTED;

	BurstBegin();
	//if((m_writeByteCount + len + 4) >= m_writeBufferSize)
	if( GetWriteBuffer().GetSpace() < (len+4) )
	{
		BurstEnd();
		return OUTPACKET_RESULT_NO_ROOM_IN_BUFFER;
	}

	// Packet logger :)
	sWorldLog.LogPacket((uint32)len, opcode, (const uint8*)data, 1);

	// Encrypt the packet
	// First, create the header.
	if( len <= 0x7FFF )
	{
		ServerPktHeader Header;
		Header.cmd = opcode;
		Header.size = ntohs((uint16)len + 2);
		_crypt.EncryptSend((uint8*)&Header, sizeof (ServerPktHeader));
		// Pass the header to our send buffer
		rv = BurstSend((const uint8*)&Header, sizeof (ServerPktHeader));
	}
	else
	{
		ServerPktHeaderLarge Header;
		Header.cmd = opcode;
		Header.size = ntohs((uint16)len + 2);
		Header.size_extension = 0x80 | ( 0xFF & ( len>>16 ) );
		_crypt.EncryptSend((uint8*)&Header, sizeof (ServerPktHeaderLarge));
		// Pass the header to our send buffer
		rv = BurstSend((const uint8*)&Header, sizeof (ServerPktHeaderLarge));
	}

	// Pass the rest of the packet to our send buffer (if there is any)
	if(len > 0 && rv)
	{
		rv = BurstSend((const uint8*)data, (uint32)len);
	}

	if(rv) BurstPush();
	BurstEnd();
	return rv ? OUTPACKET_RESULT_SUCCESS : OUTPACKET_RESULT_SOCKET_ERROR;
}

void WorldSocket::OnConnect()
{
	sWorld.mAcceptedConnections++;
	_latency = getMSTime();

//	OutPacket(SMSG_AUTH_CHALLENGE, 4, &mSeed);
	sStackWolrdPacket(data,SMSG_AUTH_CHALLENGE,40+10);
#ifndef CATACLYSM_SUPPORT
	data << uint32(1);
	data << mSeed;

    BigNumber seed1;
    seed1.SetRand(16 * 8);
    data.Write(seed1.AsByteArray(), 16);               // new encryption seeds

    BigNumber seed2;
    seed2.SetRand(16 * 8);
    data.Write(seed2.AsByteArray(), 16);               // new encryption seeds
#else
	/*
	85 2F D9 5F D7 43 A8 48 ?
	01 connection index
	08 B9 C5 E0 seed
	03 67 61 40 8B 80 85 90 FA 14 51 6C 91 6D B1 CB 28 CC 2A 75 E5 DF B8 E9 ?
	*/
    BigNumber seed1;
    seed1.SetRand(16 * 8);
	data.Write(seed1.AsByteArray(), 8);               // new encryption seeds

	data << uint8(1);	//connection index (secondary connection before world login is 1)
	data << mSeed;

    BigNumber seed2;
    seed2.SetRand(24 * 8);
    data.Write(seed2.AsByteArray(), 24);               // new encryption seeds
#endif
	SendPacket(&data);
}

void WorldSocket::_HandleAuthSession(WorldPacket* recvPacket)
{
	std::string account;
	_latency = getMSTime() - _latency;

#ifndef CATACLYSM_SUPPORT
	uint32 unk2,unk3;
	uint32	unk4,unk5,unk6,unk7,unk8;
	try
	{
		*recvPacket >> mClientBuild;
		*recvPacket >> unk2;
		*recvPacket >> account;
		*recvPacket >> unk3;
		*recvPacket >> mClientSeed;
		*recvPacket >> unk4;
		*recvPacket >> unk5;
		if( mClientBuild >= 12340 )
			*recvPacket >> unk6 >> unk7 >> unk8;
	}
	catch(ByteBuffer::error &)
	{
		sLog.outDetail("Incomplete copy of AUTH_SESSION Received.");
		return;
	}
#else
	if( recvPacket->size() < 48 )
	{
		sLog.outDetail("Incomplete copy of CMSG_AUTH_SESSION Received.");
		return;
	}
/*
D6 CC 22 E3 01 60 00 00 00 00 9E 00 AA 89 00 00 00 00 04 37 - 20 bytes
01 00 00 00 - 4 bytes
95 33 - client build 13205 
FD A4 8A 83 0C 00 00 00 00 00 00 00 00 E9  - 12 bytes
EC AA C0 78 seed ?
79 00 00 00 00 D4 65 51 - 8 crap
03 01 00 00 - addonsize (259 instead 149 ?)
3B 03 00 00 - addon uncompressed ( 827 ) -> next is compressed addon cause of ZIP header
78 9C 75 D2 C1 4E C3 30 0C 06 E0 F2 1E 7B 13 4E 6B 27 AA 8A F5 42 C3 19 B9 89 97 5A 4D E2 CA 4D 07 DD 7B F0 BE 50 21 21 26 DC 5C 3F C7 8A 7F E7 50 14 45 19 E8 76 03 71 6F F5 42 C1 BD 36 C5 EF B9 97 8A 53 16 0E 6A 41 93 E6 09 6D FE B6 87 F8 7E 38 DF D9 D1 0E 84 57 8C 98 76 5C EC 00 C8 81 FD AA F6 3E 0A 26 D0 6F 2E 36 13 27 D5 4A 90 1E 65 1E 78 DA E1 9C 03 5E 08 83 6B 29 51 84 49 2B A2 E4 28 79 B5 41 05 01 93 03 D1 88 63 0F F9 CC 7E D7 0C 7E 64 1D 27 B0 F9 05 C8 3D 09 44 9C 95 34 4E D8 2F DE 30 87 59 69 50 87 75 1A D4 E7 D6 6D 35 80 9E 7F DD 76 8B 5C 71 D5 71 DB 7C 09 69 54 B5 C9 18 3B B6 23 E6 BD 98 5A B0 C2 AA 6C 53 EA 80 17 16 FF D3 F0 FF FC 66 CB 5D 1F C4 50 C4 16 12 78 D4 B6 62 78 44 FD AB 18 01 87 DD 48 21 EC 31 25 94 BF F6 F8 79 7A FE 02 7E FB F2 B0 
54 55 44 49 00 account
*/
	recvPacket->read_skip( 20 + 4 );	//this is digest + crap 
	uint16 smallclientbuild;
	*recvPacket >> (uint16)(smallclientbuild);	mClientBuild = smallclientbuild;
	recvPacket->read_skip( 14 );	//this is digest + crap 
	*recvPacket >> mClientSeed;
	recvPacket->read_skip( 8 );
	uint32 addonsize;
	*recvPacket >> addonsize;
	recvPacket->read_skip( addonsize );
	*recvPacket >> account;
	//rest needs to be read for addon info to be processed
#endif

	// Send out a request for this account.
	mRequestID = sLogonCommHandler.ClientConnected(account, this);
	
	if(mRequestID == 0xFFFFFFFF)
	{
		sLog.outDetail("Invalid Authrequest. Logonserver never received account %s connection.",account);
		Disconnect();
		return;
	}

	// shitty hash !
	m_fullAccountName = new string( account );

	// Set the authentication packet 
    pAuthenticationPacket = recvPacket;
}

void WorldSocket::InformationRetreiveCallback(WorldPacket & recvData, uint32 requestid)
{
	if(requestid != mRequestID)
		return;

	uint32 error;
	recvData >> error;

	if(error != 0 || pAuthenticationPacket == NULL)
	{
		// something happened wrong @ the logon server
		OutPacket(SMSG_AUTH_RESPONSE, 1, "\x0D");
		return;
	}

	// Extract account information from the packet.
	string AccountName;
	const string * ForcedPermissions;
	uint32 AccountID;
	string GMFlags;
	uint8 AccountFlags;
	string lang = "enUS";
	
	recvData >> AccountID >> AccountName >> GMFlags >> AccountFlags;
	ForcedPermissions = sLogonCommHandler.GetForcedPermissions(AccountName);
	if( ForcedPermissions != NULL )
		GMFlags.assign(ForcedPermissions->c_str());

	sLog.outDebug( " >> got information packet from logon: `%s` ID %u (request %u)", AccountName.c_str(), AccountID, mRequestID);
//	sLog.outColor(TNORMAL, "\n");

	mRequestID = 0;
	// Pull the session key.
	
	uint8 K[40];
	recvData.read(K, 40);

	_crypt.Init(K);
	
	BigNumber BNK;
	BNK.SetBinary(K, 40);

	//checking if player is already connected
    //disconnect corrent player and login this one(blizzlike)

	if(recvData.rpos() != recvData.wpos())
		recvData.read((uint8*)lang.data(), 4);

	WorldSession *session = sWorld.FindSession( AccountID );
	if( session)
	{
		if(session->_player != NULL && session->_player->GetMapMgr() == NULL)
		{
			Log.Debug("WorldSocket","_player found without m_mapmgr during logon, trying to remove him [player %s, map %d, instance %d].", session->_player->GetName(), session->_player->GetMapId(), session->_player->GetInstanceID() );
			if(objmgr.GetPlayer(session->_player->GetLowGUID()))
				objmgr.RemovePlayer(session->_player);
			session->LogoutPlayer(false);
		}
		// AUTH_FAILED = 0x0D
		session->Disconnect();
		
		// clear the logout timer so he times out straight away
		session->SetLogoutTimer(1);

		// we must send authentication failed here.
		// the stupid newb can relog his client.
		// otherwise accounts dupe up and disasters happen.
		OutPacket(SMSG_AUTH_RESPONSE, 1, "\x15");
		return;
	}

	Sha1Hash sha;

	uint8 digest[20];
#ifdef CATACLYSM_SUPPORT
/*
CDS__WriteInt8(v2, v3->AuthSessionDigest[4]);
CDS__WriteInt8(v2, v3->AuthSessionDigest[8]);
CDS__WriteInt8(v2, v3->AuthSessionDigest[14]);
CDS__WriteInt8(v2, v3->AuthSessionDigest[17]);
CDS__WriteInt8(v2, v3->field_56C);
CDS__WriteInt8(v2, v3->AuthSessionDigest[3]);
CDS__WriteInt32(v2, v3->RealmId);
CDS__WriteInt8(v2, v3->AuthSessionDigest[5]);
CDS__WriteInt8(v2, v3->field_544);
CDS__WriteInt8(v2, v3->AuthSessionDigest[0]);
CDS__WriteInt8(v2, v3->AuthSessionDigest[10]);
CDS__WriteInt32(v2, v3->field_568);
CDS__WriteInt8(v2, v3->AuthSessionDigest[12]);
CDS__WriteInt8(v2, v3->AuthSessionDigest[6]);
CDS__WriteInt32(v2, v3->RealmSiteId);
CDS__WriteInt16(v2, v3->Build);
CDS__WriteInt8(v2, v3->AuthSessionDigest[7]);
CDS__WriteInt8(v2, v3->AuthSessionDigest[11]);
CDS__WriteInt8(v2, v3->AuthSessionDigest[16]);
CDS__WriteInt8(v2, v3->AuthSessionDigest[18]);
CDS__WriteInt8(v2, v3->AuthSessionDigest[13]);
CDS__WriteInt64(v2, v3->UnkAuthULONG);
CDS__WriteInt8(v2, v3->AuthSessionDigest[15]);
CDS__WriteInt32(v2, v3->ClientSeed);
CDS__WriteInt8(v2, v3->AuthSessionDigest[9]);
CDS__WriteInt32(v2, v3->RealmRegion);
CDS__WriteInt8(v2, v3->AuthSessionDigest[1]);
CDS__WriteInt8(v2, v3->AuthSessionDigest[2]);
CDS__WriteInt8(v2, v3->AuthSessionDigest[19]);
  */
	pAuthenticationPacket->ResetRead();
	*pAuthenticationPacket >> digest[4];
	*pAuthenticationPacket >> digest[8];
	*pAuthenticationPacket >> digest[14];
	*pAuthenticationPacket >> digest[17];
	pAuthenticationPacket->read_skip( 1 );
	*pAuthenticationPacket >> digest[3];
	pAuthenticationPacket->read_skip( 4 );
	*pAuthenticationPacket >> digest[5];
	pAuthenticationPacket->read_skip( 1 );
	*pAuthenticationPacket >> digest[0];
	*pAuthenticationPacket >> digest[10];
	pAuthenticationPacket->read_skip( 4 );
	*pAuthenticationPacket >> digest[12];
	*pAuthenticationPacket >> digest[6];
	pAuthenticationPacket->read_skip( 4 + 2 );
	*pAuthenticationPacket >> digest[7];
	*pAuthenticationPacket >> digest[11];
	*pAuthenticationPacket >> digest[16];
	*pAuthenticationPacket >> digest[18];
	*pAuthenticationPacket >> digest[13];
	pAuthenticationPacket->read_skip( 8 );
	*pAuthenticationPacket >> digest[15];
	pAuthenticationPacket->read_skip( 4 );
	*pAuthenticationPacket >> digest[9];
	pAuthenticationPacket->read_skip( 4 );
	*pAuthenticationPacket >> digest[1];
	*pAuthenticationPacket >> digest[2];
	*pAuthenticationPacket >> digest[19];
#else
	pAuthenticationPacket->read(digest, 20);
#endif

	uint32 t = 0;
	if( m_fullAccountName == NULL )				// should never happen !
		sha.UpdateData(AccountName);
	else
	{
		sha.UpdateData(*m_fullAccountName);
		
		// this is unused now. we may as well free up the memory.
		delete m_fullAccountName;
		m_fullAccountName = NULL;
	}

	sha.UpdateData((uint8 *)&t, 4);
	sha.UpdateData((uint8 *)&mClientSeed, 4);
	sha.UpdateData((uint8 *)&mSeed, 4);
	sha.UpdateBigNumbers(&BNK, NULL);
	sha.Finalize();

	if (memcmp(sha.GetDigest(), digest, 20))
	{
		// AUTH_UNKNOWN_ACCOUNT = 21
		OutPacket(SMSG_AUTH_RESPONSE, 1, "\x15");
		return;
	}

	// Allocate session
	WorldSession * pSession = new WorldSession(AccountID, AccountName, this);
	mSession = pSession;
	ASSERT(mSession);
	pSession->deleteMutex.Acquire();
	
	// Set session properties
	pSession->SetClientBuild(mClientBuild);
	pSession->LoadSecurity(GMFlags);
	pSession->SetAccountFlags(AccountFlags);
	pSession->language = sLocalizationMgr.GetLanguageId(lang);

	if(recvData.rpos() != recvData.wpos())
		recvData >> pSession->m_muted;
	if( pSession->GetSocket() )
	{
		uint32 local_mute_expire = objmgr.GetIPMuteExpire( pSession->GetSocket()->GetRemoteIP().c_str() );
		if( local_mute_expire > pSession->m_muted )
			pSession->m_muted = local_mute_expire;
	}

	for(uint32 i = 0; i < 8; ++i)
		pSession->SetAccountData(i, NULL, true, 0);

	// queue the account loading
	/*AsyncQuery * aq = new AsyncQuery( new SQLClassCallbackP1<World, uint32>(World::getSingletonPtr(), &World::LoadAccountDataProc, AccountID) );
	aq->AddQuery("SELECT * FROM account_data WHERE acct = %u", AccountID);
	CharacterDatabase.QueueAsyncQuery(aq);*/
	if(sWorld.m_useAccountData)
	{
		QueryResult * pResult = CharacterDatabase.Query("SELECT * FROM account_data WHERE acct = %u", AccountID);
		if( pResult == NULL )
			CharacterDatabase.Execute("INSERT INTO account_data VALUES(%u, '', '', '', '', '', '', '', '', '')", AccountID);
		else
		{
			size_t len;
			const char * data;
			char * d;
			for(int i = 0; i < 8; ++i)
			{
				data = pResult->Fetch()[1+i].GetString();
				len = data ? strlen(data) : 0;
				if(len > 1)
				{
					d = new char[len+1];
					memcpy(d, data, len+1);
					pSession->SetAccountData(i, d, true, (uint32)len);
				}
			}

			delete pResult;
			pResult = NULL;
		}
	}

	Log.Debug("Auth", "%s from %s:%u [%ums]", AccountName.c_str(), GetRemoteIP().c_str(), GetRemotePort(), _latency);
#ifdef SESSION_CAP
	if( sWorld.GetSessionCount() >= SESSION_CAP )
	{
		OutPacket(SMSG_AUTH_RESPONSE, 1, "\x0D");
		Disconnect();
		return;
	}
#endif

	// Check for queue.
	if( (sWorld.GetSessionCount() < sWorld.GetPlayerLimit()) || pSession->HasGMPermissions() ) {
		Authenticate();
	} else {
		// Queued, sucker.
		uint32 Position = sWorld.AddQueuedSocket(this);
		mQueued = true;
		Log.Debug("Queue", "%s added to queue in position %u", AccountName.c_str(), Position);

		// Send packet so we know what we're doing
		UpdateQueuePosition(Position);
	}

	pSession->deleteMutex.Release();
}

void WorldSocket::Authenticate()
{
	WorldSession * pSession = mSession;
	ASSERT(pAuthenticationPacket);
	mQueued = false;

	if(!pSession) 
		return;
	pSession->deleteMutex.Acquire();

	sStackWolrdPacket(data,0,500);
	data.Initialize(SMSG_AUTH_RESPONSE);
    data << uint8 (AUTH_OK);
    data << uint32 (0);                                   // BillingTimeRemaining
    data << uint8 (0);                                    // BillingPlanFlags
    data << uint32 (0);                                   // BillingTimeRested
	if(pSession->HasFlag(ACCOUNT_FLAG_XPACK_03) && sWorld.realmAllowTBCcharacters)
		data << uint8 ( 3 );                       // 0 - normal, 1 - TBC, must be set in database manually for each account
	if(pSession->HasFlag(ACCOUNT_FLAG_XPACK_02) && sWorld.realmAllowTBCcharacters)
//		OutPacket(SMSG_AUTH_RESPONSE, 11, "\x0C\x30\x78\x00\x00\x00\x00\x00\x00\x00\x02");
//		OutPacket(SMSG_AUTH_RESPONSE, 11, "\x0C\x14\xA3\x78\xEE\x02\x00\x00\x00\x00\x02");
//		OutPacket(SMSG_AUTH_RESPONSE, 11, "\x0C\x68\x10\x00\x00\x00\x00\x00\x00\x00\x02");
		data << uint8 ( 2 );                       // 0 - normal, 1 - TBC, must be set in database manually for each account
	else if(pSession->HasFlag(ACCOUNT_FLAG_XPACK_01) && sWorld.realmAllowTBCcharacters)
//		OutPacket(SMSG_AUTH_RESPONSE, 11, "\x0C\x14\xA3\x78\xEE\x02\x00\x00\x00\x00\x01");
		data << uint8 ( 1 );                       // 0 - normal, 1 - TBC, must be set in database manually for each account
	else
//		OutPacket(SMSG_AUTH_RESPONSE, 11, "\x0C\x14\xA3\x78\xEE\x02\x00\x00\x00\x00\x00");
		data << uint8 ( 0 );                       // 0 - normal, 1 - TBC, must be set in database manually for each account

#ifdef CATACLYSM_SUPPORT
	data << uint8 ( 0 );                       
#endif

	SendPacket(&data);

	data.Initialize( SMSG_CLIENTCACHE_VERSION );
	data << uint32( sWorld.ClientCacheVersion );
    SendPacket(&data);

	sAddonMgr.SendAddonInfoPacket(pAuthenticationPacket, (uint32)pAuthenticationPacket->rpos(), pSession);

	//new in 3.1.1. No idea what it is atm
	//OutPacket(UMSG_UNKNOWN_1195, 4, "\x01\x00\x00\x00");

	pSession->_latency = _latency;

	delete pAuthenticationPacket;
	pAuthenticationPacket = NULL;

	if(mSession)
	{
		sWorld.AddSession(mSession);
		sWorld.AddGlobalSession(mSession);

/*		if(pSession->HasFlag(ACCOUNT_FLAG_XTEND_INFO))
			sWorld.AddExtendedSession(pSession);*/

		if(pSession->HasGMPermissions() && mSession)
			sWorld.gmList.insert(pSession);
	}

	pSession->deleteMutex.Release();
}

void WorldSocket::UpdateQueuePosition(uint32 Position)
{
	WorldPacket QueuePacket(SMSG_AUTH_RESPONSE, 17);
	QueuePacket << uint8(0x1B) << uint8(0x2C) << uint8(0x73) << uint8(0) << uint8(0);
	QueuePacket << uint32(0) << uint8(0) << uint8(0);
	QueuePacket << Position;
	QueuePacket << uint8(1);
	SendPacket(&QueuePacket);
}

void WorldSocket::_HandlePing(WorldPacket* recvPacket)
{
	uint32 ping;
	if(recvPacket->size() < 4)
	{
		sLog.outString("Socket closed due to incomplete ping packet.");
		Disconnect();
		return;
	}

	*recvPacket >> ping;
	*recvPacket >> _latency;

	if(mSession)
	{
		int32 ping_timediff = (int32)UNIXTIME - (int32)mSession->m_lastPing;
//		sLog.outDebug( "Ping diff is %d ", ping_timediff);
		if( ping_timediff <= 29 )	//client will send this packet every 30 seconds. Even if we mess it up once then it should get fixed on next send
		{
			mSession->m_ClientTimeSpeedHackDetectionCount++;
			if( mSession->m_ClientTimeSpeedHackDetectionCount > CLIENT_TIMESPEED_CHEAT_TRIGGER_DC )
			{
				if( mSession->_player )
				{
					mSession->_player->BroadcastMessage( "Time Speedhack detected. In case server was wrong then make a report how to reproduce this case. You will be logged out in 7 seconds." );
					sCheatLog.writefromsession( mSession, "Caught %s time speed hacking last occurence with speed: %d instead of 30", mSession->_player->GetName(), ping_timediff );
					sEventMgr.AddEvent( mSession->_player, &Player::_Kick, EVENT_PLAYER_KICK, 7000, 1, 0 );
				}
				else
					mSession->Disconnect();
				return;
			}
		}
		else
			mSession->m_ClientTimeSpeedHackDetectionCount = 0;

		mSession->_latency = _latency;
		mSession->m_lastPing = (uint32)UNIXTIME;
		mSession->m_lastRecvPacket = (uint32)UNIXTIME;	//ping is handled without packet queueing
	}

#ifdef USING_BIG_ENDIAN
	swap32(&ping);
#endif

	OutPacket(SMSG_PONG, 4, &ping);

#if (defined( WIN32 ) || defined( WIN64 ) ) && ENABLE_NAGLE_ALGORITHM > 0
	// Dynamically change nagle buffering status based on latency.
	//if(_latency >= 250)
	// I think 350 is better, in a MMO 350 latency isn't that big that we need to worry about reducing the number of packets being sent.
	if(_latency >= 350)
	{
		if(!m_nagleEanbled)
		{
			u_long arg = 0;
			setsockopt(GetFd(), 0x6, 0x1, (const char*)&arg, sizeof(arg));
			m_nagleEanbled = true;
		}
	}
	else
	{
		if(m_nagleEanbled)
		{
			u_long arg = 1;
			setsockopt(GetFd(), 0x6, 0x1, (const char*)&arg, sizeof(arg));
			m_nagleEanbled = false;
		}
	}
#endif
}

void WorldSocket::OnRead()
{
	for(;;)
	{
		// Check for the header if we don't have any bytes to wait for.
		if(mRemaining == 0)
		{
			if(GetReadBuffer().GetSize() < 6)
			{
				// No header in the packet, let's wait.
				return;
			}

			// Copy from packet buffer into header local var
			ClientPktHeader Header;
			GetReadBuffer().Read((uint8*)&Header, 6);

			// Decrypt the header
			_crypt.DecryptRecv((uint8*)&Header, sizeof (ClientPktHeader));
			mRemaining = mSize = ntohs(Header.size) - 4;
			mOpcode = Header.cmd;
		}

		if(mRemaining > 0)
		{
			//in case we cannot store this packet due to corrupted header then we try to drop it
			if( GetReadBuffer().GetSpace() < mRemaining )
			{
//				ASSERT( false ); //packet header was wrong and now we are dumping the packet
				mRemaining = mSize = mOpcode = 0;
				//disconnect or something
				if( mSession )
					mSession->Disconnect();
//printf("!!!!we have space %u and we would need %u \n",GetReadBuffer().GetSpace(),mRemaining);
				return;
			}
			if( GetReadBuffer().GetSize() < mRemaining )
			{
				// We have a fragmented packet. Wait for the complete one before proceeding.
				return;
			}
		}

		WorldPacket * Packet;
		Packet = new WorldPacket(mOpcode, mSize);
		Packet->resize(mSize);

		if(mRemaining > 0)
		{
			// Copy from packet buffer into our actual buffer.
			///Read(mRemaining, (uint8*)Packet->contents());
			GetReadBuffer().Read((uint8*)Packet->contents(), mRemaining);
		}

		sWorldLog.LogPacket(mSize, mOpcode, mSize ? Packet->contents() : NULL, 0);
		mRemaining = mSize = mOpcode = 0;

		// Check for packets that we handle
		switch(Packet->GetOpcode())
		{
		case CMSG_PING:
			{
				_HandlePing(Packet);
				delete Packet;
				Packet = NULL;
			}break;
		case CMSG_AUTH_SESSION:
			{
				_HandleAuthSession(Packet);
				//delete Packet;	-> do not delete it, we keep reference to it !
				Packet = NULL;
			}break;
		default:
			{
#ifdef _DEBUG
				Log.Notice("WorldSocket", "Got packet with opcode: %04X and name %s", Packet->GetOpcode(),LookupName(Packet->GetOpcode(), g_worldOpcodeNames));
#endif
				//this is to fix some old code bug where disconnect would have removed session socket but not remove socket session
				if( mSession && mSession->_socket == NULL )
					mSession = NULL;
				if( mSession )
					mSession->QueuePacket(Packet);
				else
				{
					delete Packet;
					Packet = NULL;
				}
			}break;
		}
	}
}

#endif

void WorldLog::LogPacket(uint32 len, uint16 opcode, const uint8* data, uint8 direction)
{
#ifdef ECHO_PACKET_LOG_TO_CONSOLE
	sLog.outString("[%s]: %s %s (0x%03X) of %u bytes.", direction ? "SERVER" : "CLIENT", direction ? "sent" : "received",
		LookupName(opcode, g_worldOpcodeNames), opcode, len);
#endif

	if(bEnabled)
	{
		mutex.Acquire();
		unsigned int line = 1;
		unsigned int countpos = 0;
		uint16 lenght = len;
		unsigned int count = 0;

		fprintf(m_file, "{%s} Packet: (0x%04X) %s PacketSize = %u stamp = %u\n", (direction ? "SERVER" : "CLIENT"), opcode,
			LookupName(opcode, g_worldOpcodeNames), lenght, getMSTime() );
		fprintf(m_file, "|------------------------------------------------|----------------|\n");
		fprintf(m_file, "|00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |0123456789ABCDEF|\n");
		fprintf(m_file, "|------------------------------------------------|----------------|\n");

		if(lenght > 0)
		{
			fprintf(m_file, "|");
			for (count = 0 ; count < lenght ; count++)
			{
				if (countpos == 16)
				{
					countpos = 0;

					fprintf(m_file, "|");

					for (unsigned int a = count-16; a < count;a++)
					{
						if ((data[a] < 32) || (data[a] > 126))
							fprintf(m_file, ".");
						else
							fprintf(m_file, "%c",data[a]);
					}

					fprintf(m_file, "|\n");

					line++;
					fprintf(m_file, "|");
				}

				fprintf(m_file, "%02X ",data[count]);

				//FIX TO PARSE PACKETS WITH LENGHT < OR = TO 16 BYTES.
				if (count+1 == lenght && lenght <= 16)
				{
					for (unsigned int b = countpos+1; b < 16;b++)
						fprintf(m_file, "   ");

					fprintf(m_file, "|");

					for (unsigned int a = 0; a < lenght;a++)
					{
						if ((data[a] < 32) || (data[a] > 126))
							fprintf(m_file, ".");
						else
							fprintf(m_file, "%c",data[a]);
					}

					for (unsigned int c = count; c < 15;c++)
						fprintf(m_file, " ");

					fprintf(m_file, "|\n");
				}

				//FIX TO PARSE THE LAST LINE OF THE PACKETS WHEN THE LENGHT IS > 16 AND ITS IN THE LAST LINE.
				if (count+1 == lenght && lenght > 16)
				{
					for (unsigned int b = countpos+1; b < 16;b++)
						fprintf(m_file, "   ");

					fprintf(m_file, "|");

					unsigned short print = 0;

					for (unsigned int a = line * 16 - 16; a < lenght;a++)
					{
						if ((data[a] < 32) || (data[a] > 126))
							fprintf(m_file, ".");
						else
							fprintf(m_file, "%c",data[a]);

						print++;
					}

					for (unsigned int c = print; c < 16;c++)
						fprintf(m_file, " ");

					fprintf(m_file, "|\n");
				}

				countpos++;
			}
		}
		fprintf(m_file, "-------------------------------------------------------------------\n\n");
		fflush(m_file);
		mutex.Release();
	}
}
