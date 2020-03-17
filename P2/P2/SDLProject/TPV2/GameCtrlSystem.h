#pragma once

#include "ecs.h"
#include "System.h"
#include "Score.h"
#include "GameState.h"
#include "Entity.h"
#include "Health.h"

class GameCtrlSystem: public System {
public:

	GameCtrlSystem() : System(ecs::_sys_GameCtrl) {}

	void init() override;
	void update() override;

	void onFighterDead();
	void onAsteroidExtenction();
};

