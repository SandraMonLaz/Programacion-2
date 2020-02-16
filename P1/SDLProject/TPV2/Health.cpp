#include "Health.h"

void Health::init() {
	texture_ = game_->getTextureMngr()->getTexture(Resources::Heart);
}
void Health::draw() {
	SDL_Rect clip;
	clip.x = 0; clip.y = 0; clip.h = 30; clip.w = 30;
	SDL_Rect dest;
	dest.x = 0; dest.y = 0; dest.h = 30; dest.w = 30;

	for(int i = 0; i < lives_; ++i) {
		texture_->render(game_->getRenderer(), dest, 0, &clip);
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