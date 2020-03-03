#include "AsteroidPool.h"
#include "RandomNumberGenerator.h"
#include "Vector2D.h"

void AsteroidPool::generateAsteroids(int n) {

	for (int i = 0; i < n; ++i) {
		//Canculamos los valores rnd
		Asteroid* o = op_.getObj();
		if (o != nullptr) {
			RandomNumberGenerator* r = game_->getRandGen();
			double pX = 0, pY = 0;
			calculatePos(i, pX, pY);
			int gen = r->nextInt(1, 3);
			Vector2D c = Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2) + Vector2D(r->nextInt(-50, 50), r->nextInt(-50, 50));
			c = Vector2D(c.getX() - pX, c.getY() - pY).normalize() * (r->nextInt(1, 10) / 10.0);

			//Ponemos los valores determinados
			o->setUse(true);
			o->setPos(pX, pY);
			o->setVel(c);
			o->setGen(gen);
			o->setH(20 + 3 * gen);
			o->setW(20 + 3 * gen);

			numAsteroids_++;
		}
	}
}

void AsteroidPool::disableAll() {
	vector<Asteroid*> pool = op_.getPool();
	for (auto& o : pool) {
		o->setUse(false);
	}
	numAsteroids_ = 0;
}

void AsteroidPool::onCollision(Asteroid* a, Bullet* b) {
	a->setUse(false);
	numAsteroids_--;
	if (a->getGen() > 0) {
		for (int i = 0; i < 2; ++i) {
			Vector2D v = a->getVel().rotate(i * 45);
			Vector2D p;
			p.setX(a->getPosX() + v.normalize().getX());
			p.setY(a->getPosY() + v.normalize().getY());

			Asteroid* o = op_.getObj();
			o->setGen(a->getGen() - 1);
			o->setH(20 + 3 * o->getGen());
			o->setW(20 + 3 * o->getGen());
			o->setUse(true);
			o->setPos(p.getX(), p.getY());
			o->setVel(v);
			numAsteroids_++;
		}
	}
}

void AsteroidPool::calculatePos(int i, double& x, double& y)
{
	RandomNumberGenerator* r = game_->getRandGen();
	if (i % 2 == 0) {
		x = r->nextInt(0, game_->getWindowWidth());
		if (r->nextInt(0, 2) == 1) y = game_->getWindowHeight();
	}
	else {
		y = r->nextInt(0, game_->getWindowHeight());
		if (r->nextInt(0, 2) == 1) x = game_->getWindowWidth();
	}


}
