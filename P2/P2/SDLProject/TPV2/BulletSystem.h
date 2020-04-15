#pragma once
#include "System.h"
#include "Entity.h"
class BulletSystem : public System
{
public:
	BulletSystem() : System(ecs::_sys_Bullets) {}
	~BulletSystem() {}

	void update() override;
	void recieve(const msg::Message& msg) override;
private:
	void onCollisionWithAsteroid(Entity* b);

};

