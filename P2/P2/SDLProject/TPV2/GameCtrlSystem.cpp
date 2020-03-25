#include "GameCtrlSystem.h"
#include "Manager.h"
#include "SDLGame.h"
#include "AsteroidSystem.h"
#include "AsteroidPool.h"

void GameCtrlSystem::init() {
	Entity* e = mngr_->addEntity();
	e->addComponent<Score>();
	e->addComponent<GameState>();
	mngr_->setHandler(ecs::_hdlr_GameState, e);
}

void GameCtrlSystem::update() {
	Entity* e = mngr_->getHandler(ecs::_hdlr_GameState);

	if ((e->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::parado ||
		 e->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::noTerminado ||
		 e->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::terminado) &&
		 InputHandler::instance()->isKeyDown(SDLK_p)) {
		
			if (e->getComponent<GameState>(ecs::GameState)->currentState_ != GameState::parado) {
				mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Health>(ecs::Health)->health_ = 3;
				e->getComponent<Score>(ecs::Score)->points_ = 0;
			}
			mngr_->getSystem<AsteroidSystem>(ecs::_sys_Asteroids)->addAsteroids(5);
			e->getComponent<GameState>(ecs::GameState)->currentState_ = GameState::noParado;
	}
}

void GameCtrlSystem::onFighterDead(GameState::State state)
{
	for (auto a : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
		a->setActive(false);
	}

	for (auto a : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
		a->setActive(false);
	}

	Entity* e = mngr_->getHandler(ecs::_hdlr_GameState);

	e->getComponent<GameState>(ecs::GameState)->currentState_ = state;
}

void GameCtrlSystem::onAsteroidExtenction()
{
	for (auto a : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
		a->setActive(false);
	}

	for (auto a : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
		a->setActive(false);
	}

	Entity* e = mngr_->getHandler(ecs::_hdlr_GameState);

	e->getComponent<GameState>(ecs::GameState)->currentState_ = GameState::terminado;
}
