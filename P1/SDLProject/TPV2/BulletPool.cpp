#include "BulletPool.h"

void BulletPool::shoot(Vector2D pos, Vector2D vel, double w, double h) {
	Bullet* aux = op_.getObj();
	if (aux != nullptr) {
		aux->setPos(pos.getX(), pos.getY());
		aux->setVel(vel);
		aux->setW(w);
		aux->setH(h);
		aux->setRot(Vector2D(0, -1).angle(vel));
		aux->setUse(true);

		aux = nullptr;
	}
}

void BulletPool::disableAll() {
	vector<Bullet*> pool = op_.getPool();
	for (auto& o : pool) {
		o->setUse(false);
	}
}
void BulletPool::onCollision(Bullet* a, Asteroid* b) {
	a->setUse(false);
}
