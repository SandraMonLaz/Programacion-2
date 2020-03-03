#pragma once
#include "Component.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "ObjectPool.h"
#include "Vector2D.h"

class BulletPool : public Component
{
private:
	int numAsteroids_;
	ObjectPool<Bullet, 30> op_;
public:
	BulletPool() : Component(ecs::BulletPool), op_([](Bullet* o) { return o->inUse(); }), numAsteroids_(0) {}
	~BulletPool() {};
	void init() override { };

	void shoot(Vector2D pos, Vector2D vel, double w, double h);
	void disableAll();
	void onCollision(Bullet* a, Asteroid* b);
	inline vector<Bullet*> getPool() { return op_.getPool(); }
};

