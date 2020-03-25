#include "BulletSystem.h"
#include "BulletPool.h"
#include "Manager.h"
#include "GameState.h"


//Crea una nueva bala dada la posicion y la velocidad a la que ha de ir
void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	Entity* e = mngr_->addEntity<BulletPool>(pos, vel, width, height);
	if (mngr_ != nullptr) {
		e->setActive(true);
		mngr_->addToGroup(ecs::_grp_Bullet, e);
	}
}

void BulletSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
	b->setActive(false);
}

void BulletSystem::update()
{
	if (mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::noParado) {
		for (auto& o : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
			if (o->isActive()) {
				Transform* t = o->getComponent<Transform>(ecs::Transform);
				t->position_.set(Vector2D(t->position_.getX() + t->velocity_.getX(), t->position_.getY() + t->velocity_.getY())); //suma la velocidad a la bala

				if (t->position_.getX() > game_->getWindowWidth() || t->position_.getX() < 0 ||		//Si se sale por los laterales
					t->position_.getY() > game_->getWindowHeight() || t->position_.getY() < 0) {	//Si se sale por arriba o abajo
					o->setActive(false);
				}
			}
		}
	}

}
