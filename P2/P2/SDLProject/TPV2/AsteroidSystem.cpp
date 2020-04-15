#include "AsteroidSystem.h"
#include "AsteroidPool.h"
#include "Manager.h"
#include "GameState.h"
#include "GameCtrlSystem.h"

void AsteroidSystem::calculatePos(int i, double& x, double& y)
{
	RandomNumberGenerator* r = game_->getRandGen();
	if (i % 2 == 0) {
		x = r->nextInt(0, game_->getWindowWidth());
		if (r->nextInt(0, 2) == 1) y = game_->getWindowHeight();
	}
	else {
		y = r->nextInt(0, game_->getWindowHeight());
		if (r->nextInt(0, 2) == 1) x = game_->getWindowWidth();
	}
}

void AsteroidSystem::addAsteroids(int n)
{
	for (int i = 0; i < n; ++i) {
		RandomNumberGenerator* r = game_->getRandGen();
		double pX = 0, pY = 0;
		calculatePos(i, pX, pY);
		int gen = r->nextInt(1, 3);
		Vector2D c = Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2) + Vector2D(r->nextInt(-50, 50), r->nextInt(-50, 50));
		c = Vector2D(c.getX() - pX, c.getY() - pY).normalize() * (r->nextInt(1, 10) / 10.0);

		Entity* e = mngr_->addEntity<AsteroidPool>(Vector2D(pX, pY), c, 20 + 3 * gen, 20 + 3 * gen, gen);

		if (e != nullptr) {
			e->setActive(true);
			e->addToGroup(ecs::_grp_Asteroid);
			numOfAsteroids_++;
		}
	}
}

void AsteroidSystem::onCollisionWithBullet(Entity* a)
{
	a->setActive(false);
	numOfAsteroids_--;
	cout << numOfAsteroids_ << endl;
	mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score)->addPoints();
	if (a->getComponent<AsteroidLifetime>(ecs::AsteroidLifetime)->gen_ > 0) {
		for (int i = 0; i < 2; ++i) {
			Vector2D v = a->getComponent<Transform>(ecs::Transform)->velocity_.rotate(i * 45);
			Vector2D p;
			p.setX(a->getComponent<Transform>(ecs::Transform)->position_.getX() + v.normalize().getX());
			p.setY(a->getComponent<Transform>(ecs::Transform)->position_.getY() + v.normalize().getY());
			double wh = 20 + 3 * (a->getComponent<AsteroidLifetime>(ecs::AsteroidLifetime)->gen_ - 1);

			Entity* e = mngr_->addEntity<AsteroidPool>(p, v, wh, wh, (a->getComponent<AsteroidLifetime>(ecs::AsteroidLifetime)->gen_)-1);
			if (e != nullptr) {
				e->setActive(true);
				e->addToGroup(ecs::_grp_Asteroid);
				numOfAsteroids_++;
			}
		}
	}
	if (numOfAsteroids_ <= 0) mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onAsteroidExtenction();

}

void AsteroidSystem::update()
{
	if (mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<GameState>(ecs::GameState)->currentState_ == GameState::noParado) {
		for (auto& a : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
			if (a->isActive()) {
				Transform* tr = a->getComponent<Transform>(ecs::Transform);

				tr->position_ = tr->position_ + tr->velocity_;
				tr->rotation_ += 0.5;

				if (tr->position_.getX() > game_->getWindowWidth())   //Si se sale por la dcha
					tr->position_.setX(0);
				if (tr->position_.getX() < 0)						 //Si se sale por la izq		 
					tr->position_.setX(game_->getWindowWidth());
				if (tr->position_.getY() > game_->getWindowHeight()) //Si se sale por la dcha
					tr->position_.setY(0);
				if (tr->position_.getY() < 0)						//Si se sale por la izq
					tr->position_.setY(game_->getWindowHeight());
			}
		}
	}
}

void AsteroidSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::ASTEROID_BULLET_COLLISION: {
		onCollisionWithBullet(static_cast<const msg::AsteroidBulletCollisionMsg&>(msg).a);
		break;
	}
	case msg::ADD_ASTEROID_MSG: {
		addAsteroids(static_cast<const msg::AddAsteroidMsg&>(msg).n_);
		break;
	}
	default:
		break;
	}
}




