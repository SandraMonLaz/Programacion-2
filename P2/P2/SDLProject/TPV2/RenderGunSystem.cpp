#include "RenderGunSystem.h"
#include "GameCtrlSystem.h"

void RenderGunSystem::update()
{
	if (mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::noParado) {
		for (auto a : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
			Transform* t = a->getComponent<Transform>(ecs::Transform);
			SDL_Rect r = { t->position_.getX(), t->position_.getY(), t->width_, t->height_ };
			a->getComponent<ImageComponent>(ecs::ImageComponent)->tex_->render(r, t->rotation_);
		}
		for (auto a : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
			Transform* t = a->getComponent<Transform>(ecs::Transform);
			SDL_Rect r = { t->position_.getX(), t->position_.getY(), t->width_, t->height_ };
			a->getComponent<ImageComponent>(ecs::ImageComponent)->tex_->render(r, t->rotation_);
		}

		//Fighter
		Entity* a = mngr_->getHandler(ecs::_hdlr_Fighter);
		Transform* t = a->getComponent<Transform>(ecs::Transform);
		SDL_Rect r = { t->position_.getX(), t->position_.getY(), t->width_, t->height_ };
		SDL_Rect clip = { 47,  90, 250, 207 };
		a->getComponent<ImageComponent>(ecs::ImageComponent)->tex_->render( r, t->rotation_, clip);
	}

	Texture* texture;

	//---------------------Puntos-------------------

	unsigned int p = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score)->points_;

	string points = "Score: " + to_string(p);
	texture = new Texture(game_->getRenderer() , points, game_->getFontMngr()->getFont(Resources::ARIAL16), SDL_Color{ 255, 255, 255 });
	SDL_Rect rect;
	rect.x = game_->getWindowWidth() / 3; rect.y = 20; rect.w = game_->getWindowWidth() / 3; rect.h = 50;
	texture->render(rect);
	delete texture;

	//---------------------Vida-------------------

	int health = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Health>(ecs::Health)->health_;
	texture = game_->getTextureMngr()->getTexture(Resources::Heart);

	SDL_Rect dest = { 0,0,30,30 };

	for (int i = 0; i < health; ++i) {
		texture->render(dest);
		dest.x += 35;
	}

	//-------------------------GameOver----------------------
	SDL_Rect d = { game_->getWindowWidth() / 4, game_->getWindowHeight() / 4 ,
					   game_->getWindowWidth() / 2, game_->getWindowHeight() / 5 };

	if (mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::terminado) {
		texture = game_->getTextureMngr()->getTexture(Resources::GameOverWon);
		texture->render(d);
	}
	else if (mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::noTerminado) {
		texture = game_->getTextureMngr()->getTexture(Resources::GameOverLost);
		texture->render(d);
	}
	else if (mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::parado){
		texture = game_->getTextureMngr()->getTexture(Resources::PressAnyKey);
		texture->render(d);
	}
}
