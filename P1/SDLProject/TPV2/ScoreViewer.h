#pragma once
#include "Component.h"
#include "ScoreManager.h"
#include "Entity.h"

class ScoreViewer :	public Component
{
private:
	ScoreManager* score_ = nullptr;
	Texture* texture_ = nullptr;
public:
	ScoreViewer() :Component(ecs::ScoreViewer) {};
	~ScoreViewer() {};
	void init() override;
	void draw() override;
};

