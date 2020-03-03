#pragma once
#include "Component.h"
#include "Asteroid.h"
#include "AsteroidPool.h"
#include "Entity.h"

class AsteroidsMotion :	public Component
{
public:
	AsteroidsMotion() :Component(ecs::AsteroidsMotion) {}
	~AsteroidsMotion() {};

	void init() { pool_ = GETCMP1_(AsteroidPool)->getPool(); };
	void update() override;
private:
	vector<Asteroid*> pool_;
};

