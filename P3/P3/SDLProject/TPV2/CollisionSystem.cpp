#include "CollisionSystem.h"

#include "Collisions.h"
#include "BulletsSystem.h"
#include "FighterInfo.h"
#include "GameCtrlSystem.h"
#include "Transform.h"
#include "Manager.h"

CollisionSystem::CollisionSystem() :
		System(ecs::_sys_Collision) {
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::update() {
	auto gameCtrlSys = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	if (gameCtrlSys->getState() != GameCtrlSystem::RUNNING)
		return;

	if (mngr_->getClientId() == 0) {
		int roundOver = -1;

		for (auto& f : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
			auto fTR = f->getComponent<Transform>(ecs::Transform);

			for (auto& b : mngr_->getGroupEntities(ecs::_grp_Bullets)) {
				if (!b->isActive())
					continue;

				auto bTR = b->getComponent<Transform>(ecs::Transform);

				if (Collisions::collidesWithRotation(bTR->position_, bTR->width_,
					bTR->height_, bTR->rotation_, fTR->position_, fTR->width_,
					fTR->height_, fTR->rotation_)) {

					auto id = f->getComponent<FighterInfo>(ecs::FighterInfo)->fighterId;
					if (roundOver == -1) roundOver = id;
					else roundOver = 2;
				}
			}
		}

		if (roundOver > -1) mngr_->send<msg::FighterDead>(roundOver);

		Transform* tr1_ = mngr_->getGroupEntities(ecs::_grp_Fighters)[0]->getComponent<Transform>(ecs::Transform);
		Transform* tr2_ = mngr_->getGroupEntities(ecs::_grp_Fighters)[1]->getComponent<Transform>(ecs::Transform);

		if (Collisions::collidesWithRotation(tr1_->position_, tr1_->width_,
			tr1_->height_, tr1_->rotation_, tr2_->position_, tr2_->width_,
			tr2_->height_, tr2_->rotation_)) {
			mngr_->send<msg::Message>(msg::_FIGHTER_COLLISION_);
		}

		tr1_ = nullptr;
		tr2_ = nullptr;
	}
}

