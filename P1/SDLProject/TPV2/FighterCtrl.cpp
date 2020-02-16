#include "FighterCtrl.h"
#include "InputHandler.h"

void FighterCtrl::init() {
	tr_ = GETCMP1_(Transform);
}
void FighterCtrl::update() {
	InputHandler* ih = InputHandler::instance();
	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_UP)) {
			Vector2D newVel;
			newVel = tr_->getVel() + Vector2D(0, -1).rotate(tr_->getRot()) * THRUST;

			tr_->setVel(newVel);
		}
		else if (ih->isKeyDown(SDLK_LEFT)) {
			tr_->setRot(tr_->getRot() - 5);
		}
		else if (ih->isKeyDown(SDLK_RIGHT)) {
			tr_->setRot(tr_->getRot() + 5);
		}
	}
}