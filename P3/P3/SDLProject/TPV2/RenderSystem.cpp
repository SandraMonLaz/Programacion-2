#include "RenderSystem.h"

#include "ecs.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "SDL_macros.h"
#include "SDLGame.h"

#include "Image.h"
#include "Transform.h"
#include "Texture.h"

RenderSystem::RenderSystem() :
		System(ecs::_sys_Render) {
}

void RenderSystem::update() {
	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		drawImage(e); // auto cast from unique_ptr to Entity*
	}

	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Bullets))
		drawImage(e); // auto cast from unique_ptr to Entity*

	drawNames();
	drawCtrlMessages();
	drawScore();
}

void RenderSystem::drawImage(Entity *e) {
	Transform *tr = e->getComponent<Transform>(ecs::Transform);
	Texture *tex = e->getComponent<Image>(ecs::Image)->tex_;

	SDL_Rect dest =
	RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
			tr->height_);
	tex->render(dest, tr->rotation_);
}

void RenderSystem::drawNames() {
	Texture name;
	Texture opponentName;
	SDL_Rect rectName = RECT(0, 0, 100, 25);
	SDL_Rect rectOpponentName = RECT(SDLGame::instance()->getWindowWidth() - 200, 0, 100, 25);

	name.loadFromText(SDLGame::instance()->getRenderer(), mngr_->getName(), SDLGame::instance()->getFontMngr()->getFont(Resources::ARIAL24), SDL_Color({0, 0, 0, 255}));
	opponentName.loadFromText(SDLGame::instance()->getRenderer(), mngr_->getOpponentName(), SDLGame::instance()->getFontMngr()->getFont(Resources::ARIAL24), SDL_Color({0, 0, 0, 255}));

	if (mngr_->getClientId() == 0) {
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::WhiteRect)->render(rectName);
		name.render(rectName);
		opponentName.render(rectOpponentName);
	}
	else {
		SDLGame::instance()->getTextureMngr()->getTexture(Resources::WhiteRect)->render(rectOpponentName);
		name.render(rectOpponentName);
		opponentName.render(rectName);
	}
}

void RenderSystem::drawCtrlMessages() {
	auto gameState =
			mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->getState();

	if (gameState == GameCtrlSystem::WAITING) {
		auto msgTex = game_->getTextureMngr()->getTexture(
			Resources::WaitingForPlayer);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}

	if (gameState == GameCtrlSystem::READY || gameState == GameCtrlSystem::ROUNDOVER) {
		auto msgTex = game_->getTextureMngr()->getTexture(
				Resources::PressEnter);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}

	if (gameState == GameCtrlSystem::LOSE) {
		auto msgTex = game_->getTextureMngr()->getTexture(Resources::Lose);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
				(game_->getWindowHeight() - msgTex->getHeight()) / 2);
		msgTex = game_->getTextureMngr()->getTexture(
			Resources::PressEnter);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}

	if (gameState == GameCtrlSystem::WIN) {
		auto msgTex = game_->getTextureMngr()->getTexture(Resources::Winner);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight()) / 2);
	    msgTex = game_->getTextureMngr()->getTexture(
			Resources::PressEnter);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}

	if (gameState == GameCtrlSystem::DRAW) {
		auto msgTex = game_->getTextureMngr()->getTexture(Resources::Draw);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight()) / 2);
		msgTex = game_->getTextureMngr()->getTexture(
			Resources::PressEnter);
		msgTex->render((game_->getWindowWidth() - msgTex->getWidth()) / 2,
			(game_->getWindowHeight() - msgTex->getHeight() - 10));
	}

}

void RenderSystem::drawScore() {
	auto gameCtrl = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	Texture scoreTex(game_->getRenderer(),
			to_string(gameCtrl->getScore(0)) + " - "
					+ to_string(gameCtrl->getScore(1)),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });
	scoreTex.render(game_->getWindowWidth() / 2 - scoreTex.getWidth() / 2, 10);
}
