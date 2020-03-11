#include "GameCtrlSystem.h"
#include "Manager.h"
#include "SDLGame.h"

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

	if ( e->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::parado && InputHandler::instance()->isKeyDown(SDLK_KP_ENTER)) {
		//mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->addAsteroids(10);
		e->getComponent<GameState>(ecs::GameState)->currentState_ = GameState::noParado;
		e->getComponent<Score>(ecs::Score)->points_ = 0;
		e->getComponent<Health>(ecs::Health)->health_ = 3;
	}
}
