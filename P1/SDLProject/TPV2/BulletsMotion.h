#pragma once
#include "Component.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "Entity.h"

class BulletsMotion : public Component
{
public:
	BulletsMotion(): Component(ecs::BulletMotion) {};
	~BulletsMotion() {};

	void init() override;
	void update() override;
private:
	vector<Bullet*> pool_;
};

