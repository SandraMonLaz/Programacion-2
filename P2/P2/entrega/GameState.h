#pragma once
#include "Component.h"
struct GameState : public Component
{
	enum State { terminado, noTerminado, parado, noParado};

	GameState(): Component(ecs::GameState), currentState_(parado) {}

	State currentState_;
};

