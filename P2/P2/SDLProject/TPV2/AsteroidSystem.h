#pragma once
#include "System.h"
#include "Entity.h"

class AsteroidSystem : public System
{
public:
	AsteroidSystem() : System(ecs::_sys_Asteroids), numOfAsteroids_(0) {}
	void addAsteroids(int n);
	void onCollisionWithBullet(Entity* a, Entity* b);
	void update() override;
private:
	std::size_t numOfAsteroids_;

	void calculatePos(int i, double& x, double& y);
};

