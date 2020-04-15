#pragma once
#include "System.h"
#include "SDLGame.h"
class SoundSystem :	public System
{
public:
	SoundSystem() : System(ecs::_sys_Sound) {};
	~SoundSystem() {};

	void init() override {
		game_->getAudioMngr()->setChannelVolume(2, 1);
		game_->getAudioMngr()->setMusicVolume(13);
		game_->getAudioMngr()->playMusic(Resources::ImperialMarch);
	}
	void recieve(const msg::Message& msg) {
		switch (msg.id)
		{
			case msg::SHOOT_MSG: game_->getAudioMngr()->playChannel(Resources::GunShot, 0, 0); break;
			case msg::ASTEROID_BULLET_COLLISION: game_->getAudioMngr()->playChannel(Resources::Explosion, 0, 0); break;
			default: break;
		}
	}
};

