#pragma once
#include <vector>

#include "CollisionSystem.h"
#include "GameCtrlSystem.h"
#include "AsteroidSystem.h"
#include "BulletSystem.h"
#include "FighterSystem.h"
#include "FighterGunSystem.h"
#include "Manager.h"
#include "RenderGunSystem.h"
#include "SDLGame.h"
#include "BulletPool.h"
#include "AsteroidPool.h"

class Asteroids
{
public:
	Asteroids();
	virtual ~Asteroids() {}

    void start();
    void stop();

private:
    void initGame();
    void closeGame();

    SDLGame* game;
    Manager* mngr;
    bool exit;

    FighterSystem* fighterSystem;
    FighterGunSystem* fighterGunSystem;
    AsteroidSystem* asteroidsSystem;
    RenderGunSystem* renderGunSystem;
    BulletSystem* bulletSystem;
    CollisionSystem* collisionSystem;
    GameCtrlSystem* gameCtrlSystem;
    
    const static int _WINDOWWIDTH = 640;
    const static int _WINDOWHEIGHT = 480;
};

