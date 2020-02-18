#include "AsteroidPool.h"
#include "RandomNumberGenerator.h"

void AsteroidPool::generateAsteroids(int n) {
	Asteroid* o = op_.getObj();
	for (int i = 0; i < n; ++i) {
		RandomNumberGenerator* r = game_->getRandGen();
		double pX = r->nextInt(0, game_->getWindowWidth());
		double pY = r->nextInt(0, game_->getWindowHeight());

		Vector2D c = Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2) + Vector2D(r->nextInt(50, -50), r->nextInt(50, -50));
		c = Vector2D(c.getX() - pX, c.getY() - pY).normalize() * (r->nextInt(1, 10) / 10.0);

		o->setPos(pX, pY);
		o->setVel(c);
		o->setUse(true);
		
	}
}

void AsteroidPool::disableAll() {

}

void AsteroidPool::onCollision(Asteroid* a, Bullet* b) {

}
