#pragma once
#include "System.h"
#include "Entity.h"
#include "Transform.h"
#include "Health.h"
#include "ImageComponent.h"
#include "Manager.h"

class FighterSystem : public System
{
public:
	FighterSystem() : System(ecs::_sys_Fighter) {};
	~FighterSystem() {};
	// Crea la entidad del caza, añade sus componentes (Transform, Health, etc.)
	// y la asocia con el handler _hndlr_Fighter.
	void init() override;
	void update() override;
	void recieve(const msg::Message& msg) override;
private:
	// Pone el caza en el centro con velocidad 0 y rotación 0. 
	void onCollisionWithAsteroid(Entity* a);

	const double THRUST = 0.5;
	const double ANGLE = 10.0;
	double maxVel = 5.5;
	double drag_ = 0.45;
};

