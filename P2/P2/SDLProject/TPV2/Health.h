#pragma once
#include "Component.h"
struct Health : public Component
{
	Health(): Component(ecs::Health), health_(3) {}
	bool hasDied() {
		health_--;
		return (health_ <= 0);
	}
	int health_;
};

