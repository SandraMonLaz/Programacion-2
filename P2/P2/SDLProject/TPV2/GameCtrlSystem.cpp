#include "GameCtrlSystem.h"
#include "Manager.h"
#include "SDLGame.h"
#include "AsteroidPool.h"

void GameCtrlSystem::init() {
	Entity* e = mngr_->addEntity();
	e->addComponent<Score>();
	e->addComponent<GameState>();
	e->addComponent<Health>();
	e->addToGroup(ecs::_hdlr_GameState);
	mngr_->setHandler(ecs::_hdlr_GameState, e);
}

void GameCtrlSystem::update() {
	Entity* e = mngr_->getGroupEntities(ecs::_hdlr_GameState)[0];

	if ((e->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::parado ||
		 e->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::noTerminado ||
		 e->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::terminado) &&
		 InputHandler::instance()->isKeyDown(SDLK_KP_ENTER)) {
		
			if (e->getComponent<GameState>(ecs::GameState)->currentState_ != GameState::parado) {
					e->getComponent<Health>(ecs::Health)->health_ = 3;
					e->getComponent<Score>(ecs::Score)->points_ = 0;
			}
			//mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->addAsteroids(10);
			e->getComponent<GameState>(ecs::GameState)->currentState_ = GameState::noParado;
	}
}

void GameCtrlSystem::onFighterDead()
{
	for (auto a : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
		a->setActive(false);
	}

	for (auto a : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
		a->setActive(false);
	}

	Entity* e = mngr_->getGroupEntities(ecs::_hdlr_GameState)[0];

	e->getComponent<GameState>(ecs::GameState)->currentState_ = GameState::noTerminado;
}

void GameCtrlSystem::onAsteroidExtenction()
{
	for (auto a : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
		a->setActive(false);
	}

	for (auto a : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
		a->setActive(false);
	}

	Entity* e = mngr_->getGroupEntities(ecs::_hdlr_GameState)[0];

	e->getComponent<GameState>(ecs::GameState)->currentState_ = GameState::terminado;
}
