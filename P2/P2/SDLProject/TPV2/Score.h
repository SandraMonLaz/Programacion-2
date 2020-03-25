#pragma once

#include "Component.h"

struct Score: Component {
	Score() : Component(ecs::Score), points_(0) {}

	void addPoints() { points_ += 10; }
	unsigned int points_;
};

