#pragma once
#include "Component.h"
class ScoreManager : public Component
{
public:
	enum States{
		parado, noParado, terminado, noTerminado
	};
	ScoreManager() : Component(ecs::ScoreManager) {};
	~ScoreManager() {};
	void addPoints(int p) { points_ += p; }
	void setState(States state) { actualState_ = state; }
	int getState() { return actualState_; }
	int getPoints() { return points_; }
	inline void resetPoints() { points_ = 0; };

private:
	int points_ = 0;
	States actualState_ = parado;
	

};

