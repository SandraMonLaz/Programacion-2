#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>

namespace msg {

using msgSizeType = uint32_t;

enum MsgId : uint8_t {
	_CONNECTED, //
	_CONNECTION_REFUSED, //
	_CLIENT_DISCONNECTED, //
	_PLAYER_INFO, //
	_FIGHTER_INFO, //
	_BULLET_SHOOT_INFO, //
	_START_REQUEST_, //
	_START_GAME_, //
	_FIGHTER_DEAD_, //
	_FIGHTER_COLLISION_, //

	//
	_last_MsgId_
};

#pragma pack(push,1)

struct Message {
	Message(msgSizeType size, MsgId id) :
			size(size), senderClientId(0), id(id) {
	}
	Message(MsgId id) :
			Message(sizeof(Message), id) {
	}
	msgSizeType size;
	uint32_t senderClientId;
	MsgId id;
};

struct ConnectedMsg: Message {
	ConnectedMsg(int clientId) : Message(sizeof(ConnectedMsg), _CONNECTED), clientId(clientId) {}
	uint32_t clientId;
};

struct ClientDisconnectedMsg: Message {
	ClientDisconnectedMsg(uint32_t clientId) : Message(sizeof(ClientDisconnectedMsg), _CLIENT_DISCONNECTED), clientId(clientId) {}
	uint32_t clientId;
};

struct FighterInfoMessage : Message {
	FighterInfoMessage(double x, double y, double rot) : Message(sizeof(FighterInfoMessage), _FIGHTER_INFO), x(x), y (y), rotation(rot) {}
	double x;
	double y;
	double rotation;
};

struct BulletShootMessage : Message {
	BulletShootMessage(double x, double y, double velx, double vely, double w, double h) : Message(sizeof(BulletShootMessage), _BULLET_SHOOT_INFO), x(x), y(y), velx(velx), vely(vely), w(w), h(h) {}
	double x, y;
	double velx, vely;
	double w, h;
};

struct FighterDead : Message {
	FighterDead(uint8_t fId) : Message(sizeof(FighterDead), _FIGHTER_DEAD_), fighterId(fId) {}
	uint8_t fighterId;
};

#pragma pack(pop)

}
