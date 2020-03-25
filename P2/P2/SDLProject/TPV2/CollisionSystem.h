#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "Transform.h"
#include "GameState.h"
#include "BulletSystem.h"
#include "AsteroidSystem.h"
#include "FighterSystem.h"
class CollisionSystem: public System {
public:
	CollisionSystem() :	System(ecs::_sys_Collisions) {}
	~CollisionSystem() {}

	// - si el juego está parado no hacer nada.
	// - comprobar colisiones usando el esquema abajo (nota las instrucciones break
	// y continue, piensa porque son necesarias).
	void update() override {
		if (mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::noParado) {
			for (auto &a : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
				Entity* fighter = mngr_->getHandler(ecs::_hdlr_Fighter);
				Transform* trA = a->getComponent<Transform>(ecs::Transform);
				Transform* trF = fighter->getComponent<Transform>(ecs::Transform);
				if (Collisions::collidesWithRotation(trA->position_, trA->width_, trA->height_, trA->rotation_, trF->position_, trF->width_, trF->height_, trF->rotation_)) {
					mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->onCollisionWithAsteroid(fighter);
					break;
				}
				for (auto& b : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
					Transform* trB = b->getComponent<Transform>(ecs::Transform);
					if (!b->isActive()) continue;
					if (!a->isActive()) break;
					if (Collisions::collidesWithRotation(trA->position_, trA->width_, trA->height_, trA->rotation_, trB->position_, trB->width_, trB->height_, trB->rotation_)) {
						mngr_->getSystem<BulletSystem>(ecs::_sys_Bullets)->onCollisionWithAsteroid(b, a);
						mngr_->getSystem<AsteroidSystem>(ecs::_sys_Asteroids)->onCollisionWithBullet(a, b);
					}
				}
			}
		}
	}
};
