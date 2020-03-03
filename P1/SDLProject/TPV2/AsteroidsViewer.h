#pragma once
#include "Component.h"
#include "AsteroidPool.h"
#include "Asteroid.h"
#include "Entity.h"
class AsteroidsViewer :	public Component
{
public:
	AsteroidsViewer(): Component(ecs::AsteroidsViewer) {}
	~AsteroidsViewer(){}
	void init();
	void draw() override;
private:
	Texture* texture_;
	vector<Asteroid*> pool;

};

