#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Asteroid.h"
#include "Bullet.h"

class AsteroidPool : public Component
{
private:
	int numAsteroids_;
	ObjectPool<Asteroid, 30> op_;
public:
	AsteroidPool() : Component(ecs::AsteroidPool) , op_([](Asteroid* o) { return o->inUse(); }), numAsteroids_(0) {}
	~AsteroidPool() {};

	void generateAsteroids(int n);
	void disableAll();
	void onCollision(Asteroid* a, Bullet* b);
	inline int getNumOfAsteroid() { return numAsteroids_; }
	inline vector<Asteroid*> getPool() { return op_.getPool(); }
};

