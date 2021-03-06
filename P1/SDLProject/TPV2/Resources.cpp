#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_ {
//
		{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 }, //
		{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_ {
//
		{ Blank, "resources/images/blank.png" }, //
		{ TennisBall, "resources/images/tennis_ball.png" }, //
		{ KeyBoardIcon, "resources/images/keyboard.png" }, //
		{ MouseIcon, "resources/images/mouse.png" }, //
		{ AIIcon, "resources/images/ai.png" }, //
		{ SpaceShips, "resources/images/spaceships.png" }, //
		{ Airplanes, "resources/images/airplanes.png" }, //
		{ Star, "resources/images/star.png" }, //
		{ Heart, "resources/images/heart.png" }, //
		{ Asteroid, "resources/images/asteroid.png" }, //
		{ Bullet, "resources/images/whiterect.png" } //
};

vector<Resources::TextMsgInfo> Resources::messages_ {
//
		{ PressAnyKey, "Press Any Key to Start", { COLOR(0xaaffbbff) }, ARIAL24 }, //
		{ GameOverLost, "Game Over! You lost!", { COLOR(0xffffbbff) }, ARIAL24 }, //
		{ GameOverWon, "Game Over! You won!", { COLOR(0xffffbbff) }, ARIAL24 } //
};

vector<Resources::MusicInfo> Resources::musics_ {
//
		{ Beat, "resources/sound/beat.wav" }, //
		{ Cheer, "resources/sound/cheer.wav" }, //
		{ Boooo, "resources/sound/boooo.wav" }, //
		{ ImperialMarch, "resources/sound/imperial_march.wav" } //
};

vector<Resources::SoundInfo> Resources::sounds_ {
//
		{ Gunshot, "resources/sound/GunShot.wav" }, //
		{ Explosion, "resources/sound/explosion.wav" } //
};

