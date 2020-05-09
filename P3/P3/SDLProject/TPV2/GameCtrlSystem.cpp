#include "GameCtrlSystem.h"

#include <cassert>
#include <cstdint>
#include "ecs.h"
#include "Entity.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "Manager.h"

using ecs::CmpId;

GameCtrlSystem::GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	state_ = WAITING;
	resetScore();
}

void GameCtrlSystem::init() {
	state_ = WAITING;

	mngr_->send<msg::PlayerInfo>(mngr_->getName());
}

void GameCtrlSystem::update() {

	if (state_ != RUNNING && state_ != WAITING ) { 
		InputHandler *ih = game_->getInputHandler();
		if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			mngr_->send<msg::Message>(msg::_START_REQUEST_);
		}
	}
}

void GameCtrlSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_PLAYER_INFO: {
		if (state_ == READY || msg.senderClientId == mngr_->getClientId()) return;
		state_ = READY;
		char n[11];
		strcpy_s(n, static_cast<const msg::PlayerInfo&>(msg).name);
		mngr_->setOpponentName(n);
		mngr_->send<msg::PlayerInfo>(mngr_->getName());
		break;
	}
	case msg::_CLIENT_DISCONNECTED:
		resetMatch();
		break;
	case msg::_START_REQUEST_:
		if (state_ != RUNNING) mngr_->send<msg::Message>(msg::_START_GAME_);
		break;
	case msg::_START_GAME_:
		startGame();
		break;
	case msg::_FIGHTER_DEAD_:
		onFighterDeath(static_cast<const msg::FighterDead&>(msg).fighterId);
		break;
	case msg::_FIGHTER_COLLISION_:
		state_ = ROUNDOVER;
		break;
	default:
		break;
	}
}

void GameCtrlSystem::startGame() {
	if (state_ == DRAW || state_ == LOSE || state_ == WIN) {
		resetScore();
	}
	mngr_->getSystem<FightersSystem>(ecs::_sys_Fighters)->resetFighterPositions();
	state_ = RUNNING;
}

void GameCtrlSystem::onFighterDeath(uint8_t fighterId) {
	assert(fighterId >= 0 && fighterId <= 2);

	uint8_t id = 1 - fighterId; // the id of the other player fighter

	state_ = ROUNDOVER;
	if (fighterId < 2) {	
		score[id]++;
	}
	else {		//2 significa que ha habido doble colision
		score[0]++;
		score[1]++;
	}
	
	if (score[0] == 3 && score[1] == 3) state_ = DRAW;
	else if (score[0] == 3) state_ = mngr_->getClientId() == 0 ? WIN : LOSE;
	else if (score[1] == 3) state_ = mngr_->getClientId() == 1 ? WIN : LOSE;
}

void GameCtrlSystem::resetMatch()
{
	state_ = WAITING;
	resetScore();
}

void GameCtrlSystem::resetScore() {
	score[0] = score[1] = 0;
}
