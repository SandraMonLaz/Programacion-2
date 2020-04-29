#pragma once
#include <cstddef>
#include "Vector2D.h"
class Entity;
namespace msg {

	using msgType = std::size_t;
	enum MsgId : msgType {
		ASTEROID_BULLET_COLLISION,
		FIGHTER_COLLISION,
		SHOOT_MSG,
		ADD_ASTEROID_MSG,
		ASTEROID_EXTENTION,
		//
		last_MsgId
	};
	struct Message
	{
		Message(MsgId id) : id(id) {};
		MsgId id;
	};
	struct AsteroidBulletCollisionMsg : Message {
		AsteroidBulletCollisionMsg(Entity* a, Entity* b) : Message(ASTEROID_BULLET_COLLISION), a(a), b(b) {}
		Entity * a;
		Entity * b;
	};	

	struct FighterCollisionMsg : Message {
		FighterCollisionMsg(Entity* a) : Message(FIGHTER_COLLISION), a(a) {}
		Entity* a;
	};
	struct ShootMsg : Message {
		ShootMsg(Vector2D pos, Vector2D vel, double w, double h) : Message(SHOOT_MSG), pos_(pos),vel_(vel),width_(w),height_(h) {}
		Vector2D pos_;
		Vector2D vel_;
		double width_;
		double height_;
	};
	struct AddAsteroidMsg : Message {
		AddAsteroidMsg(int n) : Message(ADD_ASTEROID_MSG), n_(n) {}
		int n_;
	};
	struct AsteroidExtentionMsg : Message {
		AsteroidExtentionMsg() : Message(ASTEROID_EXTENTION) {}
	};
}