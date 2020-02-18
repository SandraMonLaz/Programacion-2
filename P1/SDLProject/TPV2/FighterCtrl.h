#pragma once
#include "Component.h"
#include "Transform.h"
#include "Entity.h"

class FighterCtrl :	public Component
{
private:
	const double THRUST = 0.5;
	const double ANGLE = 10.0;
	Transform* tr_ = nullptr;
	double maxVel = 5.5;
public:
	FighterCtrl() : Component(ecs::FighterCtrl) {}
	~FighterCtrl(){}
	void init();
	void update() override;
};

