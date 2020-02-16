#pragma once
#include "Component.h"
#include "Texture.h"
#include "Transform.h"
#include "Entity.h"

class FighterViewer : public Component
{
private:
	Texture* texture_ = nullptr;
	Transform* tr_ = nullptr;
public:
	FighterViewer() : Component(ecs::FighterViewer) {};
	virtual ~FighterViewer() {};
	void init() override;
	void draw() override;
};

