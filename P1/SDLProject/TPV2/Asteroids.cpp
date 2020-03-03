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
#include "AsteroidPool.h"
#include "AsteroidsMotion.h"
#include "AsteroidsViewer.h"
#include "BulletsMotion.h"
#include "BulletsViewer.h"
#include "Gun.h"
#include "ScoreManager.h"
#include "GameCtrl.h"
#include "ScoreViewer.h"
#include "GameLogic.h"

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

	game_->getAudioMngr()->setChannelVolume(3, 0);
	game_->getAudioMngr()->setChannelVolume(3, 1);
	game_->getAudioMngr()->setMusicVolume(13);
	game_->getAudioMngr()->playMusic(Resources::ImperialMarch);

	entityManager_ = new EntityManager(game_);
	//BulletsPool---------------------------------------------
	Entity* bullets = entityManager_->addEntity();
	bullets->addComponent<BulletPool>();
	bullets->addComponent<BulletsMotion>();
	bullets->addComponent<BulletsViewer>();
	//Nave----------------------------------------------------
	Entity* ship = entityManager_->addEntity();
	Transform* shipTR = ship->addComponent<Transform>();
	shipTR->setPos(game_->getWindowWidth()/2, game_->getWindowHeight() / 2);
	shipTR->setWH(207/5, 250/5);
	ship->addComponent<FighterCtrl>();
	ship->addComponent<FighterViewer>();
	ship->addComponent<FighterMotion>();
	ship->addComponent<Gun>((bullets->getComponent<BulletPool>(ecs::BulletPool)));
	ship->addComponent<Health>();
	//Asteroides----------------------------------------------
	Entity* asteroids = entityManager_->addEntity();
	asteroids->addComponent<AsteroidPool>();
	asteroids->addComponent<AsteroidsMotion>();
	asteroids->addComponent<AsteroidsViewer>();

	Entity* gameManager = entityManager_->addEntity();
	gameManager->addComponent<ScoreManager>();
	gameManager->addComponent<GameCtrl>(GETCMP2(asteroids, AsteroidPool), GETCMP2(ship,Health));
	gameManager->addComponent<GameLogic>(GETCMP2(asteroids, AsteroidPool), GETCMP2(bullets, BulletPool), GETCMP2(ship, Health), GETCMP2(ship, Transform));
	gameManager->addComponent<ScoreViewer>();
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
