#include "BulletsMotion.h"

void BulletsMotion::init() {
	pool_ = GETCMP1_(BulletPool)->getPool();
}
void BulletsMotion::update() {
	for (auto& o : pool_) {
		if (o->inUse()) {
			o->setPos(o->getPosX() + o->getVel().getX(), o->getPosY() + o->getVel().getY());	//suma la velocidad a la bala

			if (o->getPosX() > game_->getWindowWidth() || o->getPosX() < 0 ||		//Si se sale por los laterales
				o->getPosY() > game_->getWindowHeight() || o->getPosY() < 0) {		//Si se sale por arriba o abajo
				o->setUse(false);
			}   
		}
	}
}
