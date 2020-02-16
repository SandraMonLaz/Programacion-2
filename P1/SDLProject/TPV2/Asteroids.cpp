#include "Asteroids.h"
#include "SDL_macros.h"
#include <assert.h>
#include "Rectangle.h"
#include "FighterViewer.h"
#include "Transform.h"
#include "SDLGame.h"
#include "InputHandler.h"
#include "Health.h"
#include "SDL_macros.h"
#include "FighterCtrl.h"
#include "FighterMotion.h"
using namespace std;

Asteroids::Asteroids() :
	game_(nullptr), //
	entityManager_(nullptr), //
	exit_(false) {
	initGame();
}
Asteroids::~Asteroids() {
	closeGame();
}
void Asteroids::initGame() {

	game_ = SDLGame::init("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	entityManager_ = new EntityManager(game_);

	Entity* ship = entityManager_->addEntity();
	Transform* shipTR = ship->addComponent<Transform>();
	shipTR->setPos(100, 100);
	shipTR->setWH(207/5, 250/5);
	ship->addComponent<FighterViewer>();
	ship->addComponent<FighterMotion>();
	ship->addComponent<FighterCtrl>();
	ship->addComponent<Health>();
	Entity* gameManager = entityManager_->addEntity();
	/*gameManager->addComponent<ScoreManager>(1);
	gameManager->addComponent<GameLogic>(ballTR, leftPaddleTR, rightPaddleTR);
	gameManager->addComponent<ScoreViewer>();
	gameManager->addComponent<GameCtrl>(GETCMP2(ball, Transform));*/
}
void Asteroids::closeGame() {
	delete entityManager_;
}
void Asteroids::start() {
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void Asteroids::stop() {
	exit_ = true;
}

void Asteroids::handleInput() {

	InputHandler* ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) {
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			}
			else {
				SDL_SetWindowFullscreen(game_->getWindow(),
					SDL_WINDOW_FULLSCREEN);
			}
		}
	}

}

void Asteroids::update() {
	entityManager_->update();
}

void Asteroids::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	entityManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}
