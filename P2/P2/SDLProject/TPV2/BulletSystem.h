#pragma once
#include "System.h"
#include "Entity.h"
class BulletSystem : public System
{
public:
	BulletSystem() : System(ecs::_sys_Bullets) {}
	void shoot(Vector2D pos, Vector2D vel, double width, double height);
	void onCollisionWithAsteroid(Entity* b, Entity* a);
		
	void update() override;

};

