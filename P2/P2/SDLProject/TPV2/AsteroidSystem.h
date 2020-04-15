#pragma once
#include "System.h"
#include "Entity.h"

class AsteroidSystem : public System
{
public:
	AsteroidSystem() : System(ecs::_sys_Asteroids), numOfAsteroids_(0) {}
	~AsteroidSystem() {}
	void update() override;
	void recieve(const msg::Message& msg) override;
private:
	std::size_t numOfAsteroids_;

	void addAsteroids(int n);
	void onCollisionWithBullet(Entity* a);
	void calculatePos(int i, double& x, double& y);
};

