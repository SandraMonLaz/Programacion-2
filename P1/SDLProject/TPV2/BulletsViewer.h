#pragma once
#include "Component.h"
#include "Texture.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "Entity.h"

class BulletsViewer : public Component
{
public:
	BulletsViewer(): Component(ecs::BulletsViewer) {}

	void init() override;
	void draw() override;
private:
	Texture* texture_;
	vector<Bullet*> pool_;
};

