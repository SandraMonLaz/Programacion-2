#pragma once
#include "Component.h"
#include "InputHandler.h"
#include "BulletPool.h"
#include "Entity.h"

class Gun : public Component
{
private:
	BulletPool* bulletPool_ = nullptr;
	Transform* tr_ = nullptr;
	double time_;
public:
	Gun(BulletPool* bulletPool) : Component(ecs::Gun), time_(game_->getTime()), bulletPool_(bulletPool) {};
	~Gun() {};
	void init() override;
	void update() override;
};

