#include "Asteroid.h"

inline void Asteroid::setPos(double x, double y)
{
	posX = x; posY = y;
}

inline void Asteroid::setVel(Vector2D v)
{
	vel = v;
}

inline void Asteroid::setRot(double r)
{
	rot = r;
}

inline void Asteroid::setGen(double g)
{
	gen = g;
}

inline void Asteroid::setUse(bool use)
{
	inUse_ = use;
}
