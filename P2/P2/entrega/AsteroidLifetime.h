#pragma once
#include "Component.h"
struct AsteroidLifetime : public Component
{
	AsteroidLifetime() : Component(ecs::AsteroidLifetime), gen_(0) {}

	int gen_;
};

