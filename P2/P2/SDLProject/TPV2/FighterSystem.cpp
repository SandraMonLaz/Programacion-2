#include "FighterSystem.h"
#include "GameState.h"
#include "GameCtrlSystem.h"

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
	Transform* m = a->getComponent<Transform>(ecs::Transform);
	Health* health= a->getComponent<Health>(ecs::Health);
	m->position_.set(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2));
	m->velocity_.set(Vector2D(0, 0));
	m->rotation_ = 0;


	if (health->health_ > 0 && health->hasDied()) mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDead(GameState::noTerminado);
	else mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDead(GameState::parado);
}

void FighterSystem::init()
{
	Entity* f = mngr_->addEntity();
	f->addComponent<Health>();
	f->addComponent<Transform>(Vector2D(game_->getWindowWidth()/2,game_->getWindowHeight()/2),Vector2D(0,0), 207 / 5, 250 / 5,0);
	f->addComponent<ImageComponent>(game_->getTextureMngr()->getTexture(Resources::Airplanes));

	mngr_->setHandler(ecs::_hdlr_Fighter, f);
	f->setActive(true);
}

void FighterSystem::update()
{
	Transform* tr_ = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);
	if (mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::noParado) {
		InputHandler* ih = InputHandler::instance();
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_UP)) {
				Vector2D newVel;
				newVel = tr_->velocity_ + Vector2D(0, -1).rotate(tr_->rotation_) * THRUST;
				if (newVel.magnitude() < maxVel) tr_->velocity_.set(newVel);
			}
			else if (ih->isKeyDown(SDLK_LEFT)) {
				tr_->rotation_ -= ANGLE;
			}
			else if (ih->isKeyDown(SDLK_RIGHT)) {
				tr_->rotation_ += ANGLE;
			}
		}

		if (tr_->position_.getX() + (tr_->width_ / 2) > game_->getWindowWidth()) {		    //Si se pasa por la dcha
			tr_->position_.setX(game_->getWindowWidth() - tr_->width_ / 2);
			tr_->velocity_.setX(tr_->velocity_.getX() * (-drag_));
		}
		else if (tr_->position_.getX() - tr_->width_ / 2 < 0) {							//Si se pasa por la izq
			tr_->position_.setX(0 + tr_->width_ / 2);
			tr_->velocity_.setX(tr_->velocity_.getX() * (-drag_));
		}
		else if (tr_->position_.getY() - tr_->height_ / 2 < 0) {							//Si se pasa por arriba
			tr_->position_.setY(0 + tr_->height_ / 2);
			tr_->velocity_.setY(tr_->velocity_.getY() * (-drag_));
		}
		else if (tr_->position_.getY() + tr_->height_ / 2 > game_->getWindowHeight()) {	//Si se pasa por abajo
			tr_->position_.setY(game_->getWindowHeight() - tr_->height_ / 2);
			tr_->velocity_.setY(tr_->velocity_.getY() * (-drag_));
		}
		else {
			tr_->position_.set(tr_->position_ + tr_->velocity_ * drag_);							//Sino se mueve
		}
	}
}
