#pragma once
#include "Component.h"
#include "AsteroidPool.h"
#include "ScoreManager.h"
#include "Health.h"

class GameCtrl : public Component
{
private:
	AsteroidPool* pool_ = nullptr;
	Health* health_ = nullptr;
	ScoreManager* score_ = nullptr;
	Texture* font_ = nullptr;
	Texture* scoreText_ = nullptr;
public:
	GameCtrl(AsteroidPool* a, Health* h) : Component(ecs::GameCtrl), pool_(a), health_(h) {};
	~GameCtrl() {};
	void init() override;
	void draw() override;
	void update() override;
	void resetGame();
	
};

