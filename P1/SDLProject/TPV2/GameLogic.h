#pragma once
#include "Component.h"
#include "AsteroidPool.h"
#include "BulletPool.h"
#include "Health.h"
#include "Entity.h"
#include "ScoreManager.h"
#include "Collisions.h"
#include "GameCtrl.h"
class GameLogic :	public Component
{
	AsteroidPool* asteroidsPool_ = nullptr;
	BulletPool* bulletPool = nullptr;
	Health* health_ = nullptr;
	Transform* transform_ = nullptr;
	ScoreManager* score_ = nullptr;
public:
	GameLogic(AsteroidPool* ap, BulletPool* bp, Health* h, Transform* tr) : Component(ecs::GameLogic), 
																			asteroidsPool_(ap), bulletPool(bp), health_(h), transform_(tr) {}
	~GameLogic() {};
	void init() override;
	void update() override;
	void collisionWithBullet(Asteroid* a);
};

