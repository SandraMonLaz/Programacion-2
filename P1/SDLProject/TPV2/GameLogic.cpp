#include "GameLogic.h"

void GameLogic::init()
{
	score_ = GETCMP1_(ScoreManager);
}
void GameLogic::update()
{
	if (score_->getState() == score_->noParado) {
		for (auto o : asteroidsPool_->getPool()) {
			if (o->inUse()) {
				if (Collisions::collidesWithRotation(transform_->getPos(), transform_->getW(), transform_->getH(), transform_->getRot(),
					o->getPos(), o->getW(), o->getH(), o->getRot())) {
					//Desactivamos objetos
					asteroidsPool_->disableAll();
					bulletPool->disableAll();
					//Reseteamos caza y restamos vida
					transform_->setPos(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
					transform_->setVel(Vector2D(0, 0));
					transform_->setRot(0);
					health_->loseLive();
					//Cambiamos de estado
					if (health_->getHp() > 0) score_->setState(score_->parado);
					else {
						GETCMP1_(GameCtrl)->resetGame();
						score_->setState(score_->noTerminado);
					}
				}
				collisionWithBullet(o);
			}
		}
	}
}
void GameLogic::collisionWithBullet(Asteroid* a) {
	for (auto b : bulletPool->getPool()) {
		if (b->inUse()) {
			if (Collisions::collidesWithRotation(a->getPos(), a->getW(), a->getH(), a->getRot(),
				b->getPos(), b->getW(), b->getH(), b->getRot())) {
				bulletPool->onCollision(b, a);
				asteroidsPool_->onCollision(a, b);
				score_->addPoints(1);
				game_->getAudioMngr()->playChannel(Resources::Explosion, 0, 0);
				if (asteroidsPool_->getNumOfAsteroid() == 0) {
					//Desactivamos objetos
					bulletPool->disableAll();
					//Reseteamos caza y restamos vida
					transform_->setPos(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
					transform_->setVel(Vector2D(0, 0));
					transform_->setRot(0);
					health_->resetLives();
					score_->setState(score_->terminado);
				}
			}
		}
	}
}
