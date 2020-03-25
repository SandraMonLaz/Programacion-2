#include "FighterSystem.h"
#include "GameState.h"

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
	Transform* m = a->getComponent<Transform>(ecs::Transform);
	m->position_.set(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2));
	m->velocity_.set(Vector2D(0, 0));
	m->rotation_ = 0;
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
	}
}
