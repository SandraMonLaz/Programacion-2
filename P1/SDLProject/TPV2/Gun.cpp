#include "Gun.h"

void Gun::update() {
	InputHandler* ih = InputHandler::instance();
	if (ih->keyDownEvent()) {
		if (time_ < game_->getTime() && ih->isKeyDown(SDLK_SPACE)) {
			//bulletPool_->shoot();
			time_ += 0.25;
		}
	}
}
