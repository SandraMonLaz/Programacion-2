#pragma once
#include "System.h"
#include "GameState.h"
#include "Manager.h"

class FighterGunSystem : public System
{
public:
	FighterGunSystem() : System(ecs::_sys_FighterGun), time_(game_->getTime()) {};
	~FighterGunSystem() {}

	void update() override;
private:
	double time_;
};

