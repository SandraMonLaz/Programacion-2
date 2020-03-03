#include "Gun.h"

void Gun::init() {
	tr_ = GETCMP1_(Transform);
}
void Gun::update() {
	InputHandler* ih = InputHandler::instance();
	if (ih->keyDownEvent()) {
		if (time_ < game_->getTime() && ih->isKeyDown(SDLK_SPACE)) {
			Vector2D bulletPos = tr_->getPos() + Vector2D(tr_->getW() / 2, tr_->getH() / 2) + Vector2D(0, -(tr_->getW() + 5.0)).rotate(tr_->getRot());
			Vector2D bulletVel = Vector2D(0, -1).rotate(tr_->getRot()) * 2;

			bulletPool_->shoot(bulletPos, bulletVel, 5, 5);
			time_ += 250;
			game_->getAudioMngr()->playChannel(Resources::Gunshot, 0, 1);
		}
	}
}
