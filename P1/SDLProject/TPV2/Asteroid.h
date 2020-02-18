#pragma once
#include "Transform.h"

class Asteroid 
{
private:
	double posX, posY,rot,gen;
	Vector2D vel;
	bool inUse_ = false;
public:
	Asteroid() : posX(0.0), posY(0.0), vel(Vector2D(0, 0)), rot(0.0), gen(0.0) {};
	~Asteroid() {};
	inline bool inUse() { return inUse_; }
	inline bool getPosX() { return posX; }
	inline bool getPosY() { return posY; }
	inline Vector2D getVel() { return vel; }
	inline double getRot() { return rot; }

	inline void setPos(double x, double y);
	inline void setVel(Vector2D v);
	inline void setRot(double r);
	inline void setGen(double g);
	inline void setUse(bool use);



};

