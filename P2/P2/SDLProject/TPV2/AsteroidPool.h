#pragma once
#include "ecs.h"
#include "Entity.h"
#include "ImageComponent.h"
#include "ObjectPool.h"
#include "Singleton.h"
#include "Transform.h"
#include "AsteroidLifetime.h"


class AsteroidPool : public Singleton<AsteroidPool> {
	friend Singleton<AsteroidPool>;
public:
	virtual ~AsteroidPool() {
	}

	template<typename ...Targs>
	inline static Entity* construct(Targs&&...args) {
		return AsteroidPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity* p) {
		AsteroidPool::instance()->destroy_(p);
	}

	inline Entity* construct_(Vector2D pos, Vector2D vel, double width, double height, int generations) {
		Entity* e = pool_.getObj();
		if (e != nullptr) {
			e->setActive(true);
			Transform* tr = e->getComponent<Transform>(ecs::Transform);
			tr->position_.set(pos);
			tr->width_ = width;
			tr->height_ = height;
			e->getComponent<AsteroidLifetime>(ecs::AsteroidLifetime)->gen_ = generations;
		}
		return e;
	}

	inline void destroy_(Entity* p) {
		pool_.relObj(p);
	}

private:
	AsteroidPool() :
		AsteroidPool(10) {
	}
	AsteroidPool(std::size_t n) :
		pool_(n) {
		for (Entity* e : pool_.getPool()) {
			e->addComponent<Transform>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Asteroid));
			e->addComponent<AsteroidLifetime>();
		}
	}

	ObjectPool<Entity> pool_;
};

