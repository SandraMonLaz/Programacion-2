#include "GameCtrl.h"
#include "Entity.h"

void GameCtrl::init() {
	score_ = GETCMP1_(ScoreManager);
	font_ = game_->getTextureMngr()->getTexture(Resources::PressAnyKey);
}
void GameCtrl::draw()
{
	string points = "Score: " +  to_string(score_->getPoints());
	Texture scoreFont(game_->getRenderer(), points, game_->getFontMngr()->getFont(Resources::ARIAL16), SDL_Color{ 255, 255, 255 });
	SDL_Rect rect;
	rect.x = game_->getWindowWidth() / 3; rect.y = 20; rect.w = game_->getWindowWidth() / 3; rect.h = 50;
	scoreFont.render(rect);

	if (score_->getState() == score_->parado ||
		score_->getState() == score_->terminado ||
		score_->getState() == score_->noTerminado) {
		SDL_Rect d = { game_->getWindowWidth() / 4, 3*game_->getWindowHeight() / 4 ,
					   game_->getWindowWidth() / 2, game_->getWindowHeight() / 5 };
		font_->render(d);
	
	}
}

void GameCtrl::update()
{
	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (score_->getState() == score_->parado || score_->getState() == score_->terminado || score_->getState() == score_->noTerminado) {
			if (score_->getState() == score_->terminado || score_->getState() == score_->noTerminado) score_->resetPoints();
			pool_->generateAsteroids(5);
			score_->setState(score_->noParado);
		}
	}
}
void GameCtrl::resetGame() {
	health_->resetLives();
}
