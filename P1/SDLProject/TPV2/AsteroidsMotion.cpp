#include "AsteroidsMotion.h"

void AsteroidsMotion::update() {
	
	for (auto& o : pool_) {
		if (o->inUse()) {
			o->setPos(o->getPosX() + o->getVel().getX(), o->getPosY() + o->getVel().getY());
			o->setRot(o->getRot() + 0.5);

			if (o->getPosX() > game_->getWindowWidth())   //Si se sale por la dcha
				o->setPos(0, o->getPosY()); 
			if (o->getPosX() < 0)						 //Si se sale por la izq		 
				o->setPos(game_->getWindowWidth(), o->getPosY());		
			if (o->getPosY() > game_->getWindowHeight()) //Si se sale por la dcha
				o->setPos(o->getPosX(), 0);								
			if (o->getPosY() < 0)						//Si se sale por la izq
				o->setPos(o->getPosX(), game_->getWindowHeight());	   
		}
	}
}