#include "FighterGunSystem.h"
#include "Transform.h"
#include "BulletSystem.h"


void FighterGunSystem::update()
{
	Transform* tr_ = mngr_->getGroupEntities(ecs::_hdlr_Fighter)[0]->getComponent<Transform>(ecs::Transform);
	if (mngr_->getGroupEntities(ecs::_hdlr_GameState)[0]->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::noParado) {
		InputHandler* ih = InputHandler::instance();
		if (ih->keyDownEvent()) {
			if (time_ < game_->getTime() && ih->isKeyDown(SDLK_SPACE)) {
				Vector2D bulletPos =  tr_->position_ + Vector2D(tr_->width_ / 2, tr_->height_ / 2) + Vector2D(0, -(tr_->width_+ 5.0)).rotate(tr_->rotation_);
				Vector2D bulletVel = Vector2D(0, -1).rotate(tr_->rotation_) * 2;

				mngr_->getSystem<BulletSystem>(ecs::_sys_Bullets)->shoot(bulletPos, bulletVel, 5, 5);
				time_ += 250;
			}
		}
	}
}
