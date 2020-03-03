#include "Health.h"

void Health::init() {
	texture_ = game_->getTextureMngr()->getTexture(Resources::Heart);
}
void Health::draw() {
	SDL_Rect dest = { 0,0,30,30 };

	for(int i = 0; i < lives_; ++i) {
		texture_->render(dest);
		dest.x += 35;
	}
}
void Health::resetLives() {
	lives_ = maxLives_;
}
void Health::loseLive() {
	if (lives_ > 0) {
		lives_--;
	}
}