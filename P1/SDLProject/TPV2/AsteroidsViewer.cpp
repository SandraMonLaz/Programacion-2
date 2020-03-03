#include "AsteroidsViewer.h"

void AsteroidsViewer::init() {
	texture_ = game_->getTextureMngr()->getTexture(Resources::Asteroid);
	pool = GETCMP1_(AsteroidPool)->getPool();
}
void AsteroidsViewer::draw() {
	for (auto& o : pool) {
		if (o->inUse()) {
			SDL_Rect dest = { o->getPosX(),o->getPosY(),o->getW(),o->getH() };
			texture_->render(dest, o->getRot());
		}
	}
}