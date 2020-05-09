#include "NetworkingSystem.h"

#include "messages.h"
#include "Manager.h"
#include "GameCtrlSystem.h"

NetworkingSystem::NetworkingSystem() :
		System(ecs::_sys_NetWorking) {

}

NetworkingSystem::~NetworkingSystem() {
}

void NetworkingSystem::recieve(const msg::Message &msg) {
	if (msg.senderClientId == mngr_->getClientId()) {
		game_->getNetworking()->send(msg);
	}
}

void NetworkingSystem::update() {
	auto net = game_->getNetworking();
	msg::Message *msg = net->recieve();

	while (msg != nullptr) {
		switch (msg->id) {
		case msg::_CLIENT_DISCONNECTED:
			mngr_->forwardMsg<msg::ClientDisconnectedMsg>(msg->senderClientId, static_cast<msg::ClientDisconnectedMsg*>(msg)->clientId);
			break;
		case msg::_PLAYER_INFO:
			mngr_->forwardMsg<msg::PlayerInfo>(msg->senderClientId, static_cast<msg::PlayerInfo*>(msg)->name);
			break;
		case msg::_FIGHTER_INFO: {
			msg::FighterInfoMessage* info = static_cast<msg::FighterInfoMessage*>(msg);
			mngr_->forwardMsg<msg::FighterInfoMessage>(msg->senderClientId, info->x, info->y, info->rotation);
			break;
		}
		case msg::_BULLET_SHOOT_INFO: {
			msg::BulletShootMessage* info = static_cast<msg::BulletShootMessage*>(msg);
			mngr_->forwardMsg<msg::BulletShootMessage>(msg->senderClientId, info->x, info->y, info->velx, info->vely, info->w, info->h);
			break;
		}
		case msg::_START_REQUEST_: 
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_START_REQUEST_);
			break;
		case msg::_START_GAME_:
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_START_GAME_);
			break;
		case msg::_FIGHTER_DEAD_:
			mngr_->forwardMsg<msg::FighterDead>(msg->senderClientId, static_cast<msg::FighterDead*>(msg)->fighterId);
			break;
		case msg::_FIGHTER_COLLISION_:
			mngr_->forwardMsg<msg::Message>(msg->senderClientId, msg::_FIGHTER_COLLISION_);
			break;
		default:
			assert(false);
			break;
		}

		msg = net->recieve();
	}

}
