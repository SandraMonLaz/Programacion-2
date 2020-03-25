#include "Asteroids.h"
#include "SDL_macros.h"

Asteroids::Asteroids():
        fighterSystem(nullptr), 
        fighterGunSystem(nullptr),
        asteroidsSystem(nullptr),
        renderGunSystem(nullptr),
        bulletSystem(nullptr),
        collisionSystem(nullptr),
        gameCtrlSystem(nullptr) {
    initGame();
}

void Asteroids::start()
{
    exit = false;
    auto ih = InputHandler::instance();

    while (!exit) {
        Uint32 startTime = game->getTime();
        SDL_SetRenderDrawColor(game->getRenderer(), COLOR(0x00AAAAFF));
        SDL_RenderClear(game->getRenderer());

        ih->update();
        if (ih->keyDownEvent()) {
            if (ih->isKeyDown(SDLK_ESCAPE)) {
                exit = true;
                break;
            }
        }

        mngr->refresh();

        fighterSystem->update();
        fighterGunSystem->update();
        asteroidsSystem->update();
        bulletSystem->update();
        collisionSystem->update();
        gameCtrlSystem->update();
        renderGunSystem->update();


        SDL_RenderPresent(game->getRenderer());

        Uint32 frameTime = game->getTime() - startTime;
        if (frameTime < 10)
            SDL_Delay(10 - frameTime);
    }
}

void Asteroids::closeGame() {
    delete mngr;
}

void Asteroids::initGame()
{
    game = SDLGame::init("Asteroids", _WINDOWWIDTH, _WINDOWHEIGHT);
    BulletPool::init(20);
    AsteroidPool::init(20);
    mngr = new Manager(game);
    fighterSystem = mngr->addSystem<FighterSystem>();
    fighterGunSystem = mngr->addSystem<FighterGunSystem>();
    asteroidsSystem = mngr->addSystem<AsteroidSystem>();
    renderGunSystem = mngr->addSystem<RenderGunSystem>();
    bulletSystem = mngr->addSystem<BulletSystem>();
    collisionSystem = mngr->addSystem<CollisionSystem>();
    gameCtrlSystem = mngr->addSystem<GameCtrlSystem>();
}
