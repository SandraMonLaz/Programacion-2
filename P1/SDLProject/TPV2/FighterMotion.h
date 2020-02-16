#pragma once
#include "Component.h"
#include "Transform.h"
#include "Entity.h"

class FighterMotion : public Component
{
private:
	Transform* tr_;
	double drag_;
public:
	FighterMotion() : Component(ecs::FighterMotion), drag_(0.6){}
	~FighterMotion() {};
	void init() override;
	void update() override;
};

