#pragma once
#include "Component.h"
#include "InputHandler.h"

class Gun : public Component
{
private:
	//BulletsPool* bulletPool_;
	double time_;
public:
	Gun() : Component(ecs::Gun), time_(game_->getTime()) {};
	~Gun() {};
	void update() override;
};

