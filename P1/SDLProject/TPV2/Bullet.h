#pragma once
#include "Vector2D.h"

class Bullet
{
private:
	Vector2D pos;
	double rot, h, w;
	Vector2D vel;
	bool inUse_ = false;
public:
	Bullet() :pos(), vel(Vector2D()), rot(), h(), w() {};
	~Bullet() {};
	inline bool inUse() { return inUse_; }
	inline Vector2D getPos() { return pos; }
	inline double getPosX() { return pos.getX(); }
	inline double getPosY() { return pos.getY(); }
	inline Vector2D getVel() { return vel; }
	inline double getRot() { return rot; }
	inline double getH() { return h; }
	inline double getW() { return w; }


	inline void setPos(double x, double y) { pos.setX(x); pos.setY(y); };
	inline void setVel(Vector2D v) { vel = v; };
	inline void setRot(double r) { rot = r; };
	inline void setUse(bool use) { inUse_ = use; };
	inline void setH(double nH) { h = nH; };
	inline void setW(double nW) { w = nW; };


};

