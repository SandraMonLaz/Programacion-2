#include "BulletsViewer.h"

void BulletsViewer::init() {
	texture_ = game_->getTextureMngr()->getTexture(Resources::Bullet);
	pool_ = GETCMP1_(BulletPool)->getPool();
}


void BulletsViewer::draw() {
	for (auto& o : pool_) {
		if (o->inUse()) {
			SDL_Rect dest = { o->getPosX(),o->getPosY(),o->getW(),o->getH() };
			texture_->render(dest, o->getRot());
		}
	}
}
