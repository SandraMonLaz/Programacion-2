#pragma once
#include "Component.h"

class Health : public Component
{
private:
	Texture* texture_ = nullptr;
	int maxLives_, lives_;
public:
	Health() : Component(ecs::Health), maxLives_(3), lives_(3) {};
	~Health() {};
	void init() override;
	void draw() override;
	void resetLives();
	void loseLive();
	int getHp() { return lives_; }
};

