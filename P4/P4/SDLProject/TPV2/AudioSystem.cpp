#include "AudioSystem.h"
#include "SDLGame.h"


void AudioSystem::init()
{
	game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);
}

void AudioSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_GAME_START: game_->getAudioMngr()->haltMusic();	break;
	case msg::_GAME_OVER: {
		game_->getAudioMngr()->haltMusic();
		if(static_cast<const msg::GameOver&>(msg).win)
			game_->getAudioMngr()->playChannel(Resources::PacMan_Won, 0);
		else 
			game_->getAudioMngr()->playChannel(Resources::PacMan_Death, 0);
		break;
	}
	case msg::_READY: game_->getAudioMngr()->playMusic(Resources::PacMan_Intro); break;
	case msg::_EATFRUIT:game_->getAudioMngr()->playChannel(Resources::PacMan_Eat, 0); break;
	default: break;
	}
}
