#include "FighterGunSystem.h"
#include "Transform.h"
#include "BulletSystem.h"


void FighterGunSystem::update()
{
	Transform* tr_ = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);
	if (mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::noParado) {
		InputHandler* ih = InputHandler::instance();
		if (ih->keyDownEvent()) {
			if (time_ < game_->getTime() && ih->isKeyDown(SDLK_SPACE)) {
				Vector2D bulletPos =  tr_->position_ + Vector2D(tr_->width_ / 2, tr_->height_ / 2) + Vector2D(0, -(tr_->width_+ 5.0)).rotate(tr_->rotation_);
				Vector2D bulletVel = Vector2D(0, -1).rotate(tr_->rotation_) * 2;

				msg::ShootMsg msg(bulletPos, bulletVel, 5, 5);
				mngr_->send(msg);
				time_ += 250;
			}
		}
	}
}
