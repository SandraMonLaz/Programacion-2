#include "ScoreViewer.h"

void ScoreViewer::init()
{
	score_ = GETCMP1_(ScoreManager);
}

void ScoreViewer::draw()
{
	SDL_Rect d = { game_->getWindowWidth() / 4, game_->getWindowHeight() / 4 ,
					   game_->getWindowWidth() / 2, game_->getWindowHeight() / 5 };

	if (score_->getState() == score_->terminado) {
		texture_ = game_->getTextureMngr()->getTexture(Resources::GameOverWon);
		texture_->render(d);
	}
	else if (score_->getState() == score_->noTerminado) {
		texture_ = game_->getTextureMngr()->getTexture(Resources::GameOverLost);
		texture_->render(d);
	}
}
