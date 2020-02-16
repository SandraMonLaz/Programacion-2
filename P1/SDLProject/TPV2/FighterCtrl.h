#pragma once
#include "Component.h"
#include "Transform.h"
#include "Entity.h"

#define THRUST 0.5;

class FighterCtrl :	public Component
{
private:
	Transform* tr_ = nullptr;
public:
	FighterCtrl() : Component(ecs::FighterCtrl) {}
	~FighterCtrl(){}
	void init();
	void update() override;
};

