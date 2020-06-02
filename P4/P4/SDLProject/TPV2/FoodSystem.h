#pragma once

#include "System.h"

class FoodSystem: public System {
public:
	FoodSystem();
	void init() override;
	void update() override;
	void recieve(const msg::Message& msg);

private:
	void addFood(std::size_t n);
	void disableAll();
	void onEat(Entity *e);
	int numOfFoodPieces_;

};

