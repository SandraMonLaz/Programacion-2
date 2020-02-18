#include "FighterViewer.h"

void FighterViewer::init(){
	texture_ = game_->getTextureMngr()->getTexture(Resources::Airplanes);
	tr_ = GETCMP1_(Transform);
}

void FighterViewer::draw() {
	SDL_Rect clip;
	clip.x = 47; clip.y = 90; clip.h = 250; clip.w = 207;
	SDL_Rect dest;
	dest.x = tr_->getPos().getX(); dest.y = tr_->getPos().getY(); dest.h = tr_->getH(); dest.w = tr_->getW();
	texture_->render(dest,tr_->getRot(),clip);
}