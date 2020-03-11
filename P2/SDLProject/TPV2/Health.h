#pragma once
#include "Component.h"
struct Health : public Component
{
	Health(): Component(ecs::Health), health_(3) {}

	int health_;
};

