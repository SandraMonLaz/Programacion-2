#include "FighterMotion.h"

void FighterMotion::update() {
	if (tr_->getPos().getX() + tr_->getW() / 2 > game_->getWindowWidth()) {		//Si se pasa por la dcha
		tr_->setPosX(game_->getWindowWidth() - tr_->getW() / 2);
		tr_->setVelX(tr_->getVel().getX() * (-drag_));
	}
	else if(tr_->getPos().getX() - tr_->getW() / 2 < 0) {							//Si se pasa por la izq
		tr_->setPosX(0 + tr_->getW() / 2);
		tr_->setVelX(tr_->getVel().getX() * (-drag_));
	}
	else if (tr_->getPos().getY() - tr_->getH() / 2 < 0) {							//Si se pasa por arriba
		tr_->setPosY(0 + tr_->getH() / 2);
		tr_->setVelY(tr_->getVel().getY() * (-drag_));
	}
	else if (tr_->getPos().getY() + tr_->getH() / 2 > game_->getWindowHeight()) {	//Si se pasa por abajo
		tr_->setPosY(game_->getWindowHeight() - tr_->getH() / 2);
		tr_->setVelY(tr_->getVel().getY() * (-drag_));
	}
	else {
		tr_->setPos(tr_->getPos() + tr_->getVel() * drag_);							//Sino se mueve
	}
}

void FighterMotion::init() {
	tr_ = GETCMP1_(Transform);
}