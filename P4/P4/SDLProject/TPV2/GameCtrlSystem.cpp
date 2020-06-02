#include "GameCtrlSystem.h"

#include "FoodSystem.h"
#include "SDLGame.h"
#include "Manager.h"
#include "GameState.h"
#include "GhostsSystem.h"
#include "PacManSystem.h"
#include "messages.h"


GameCtrlSystem::GameCtrlSystem() :
		System(ecs::_sys_GameCtrl), //
		gameState_(nullptr) {
}


void GameCtrlSystem::init() {
	Entity *e = mngr_->addEntity();
	gameState_ = e->addComponent<GameState>();
	mngr_->setHandler(ecs::_hdlr_GameStateEntity, e);
}

void GameCtrlSystem::update() {

	if ( gameState_->state_ == GameState::RUNNING )
		return;

	auto ih = game_->getInputHandler();

	if ( ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
		switch ( gameState_->state_) {
		case GameState::READY:
			gameState_->state_ = GameState::RUNNING;
			mngr_->send<msg::Message>(msg::_GAME_START);
			break;
		case GameState::OVER:
			gameState_->state_ = GameState::READY;
			gameState_->score_ = 0;
			gameState_->won_ = false;
			mngr_->send<msg::Message>(msg::_READY);
			break;
		default:
			assert(false); // should not be rechable
			break;
		}
	}
}

void GameCtrlSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_PACMANDEAD: onPacManDeath(); break;
	case msg::_NOMOREFOOD: onNoMoreFood(); break;
	default:
		break;
	}
}

void GameCtrlSystem::onPacManDeath() {
	mngr_->send<msg::GameOver>(false);
	gameState_->state_ = GameState::OVER;
	gameState_->won_ = false;
}

void GameCtrlSystem::onNoMoreFood() {
	mngr_->send<msg::GameOver>(true);
	gameState_->state_ = GameState::OVER;
	gameState_->won_ = true;
}
