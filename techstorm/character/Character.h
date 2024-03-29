#pragma once

// local includes
#include "CharacterComponent.h"
#include "../core/obj/Gameobject.h"
#include "../Common.h"
#include "../core/ecs/ECSMan.h"
#include "../core/threading/ThreadGroups.h"
#include "../core/utils/Math.h"
#include "../TechStorm-Rivalry.h"
#include "IMoveableCharacter.h"
#include "CharacterStat.h"
#include "../affliction/Affliction.h"
#include "../bodyParts/Limb.h"

namespace TechStormRivalry {

	// A game character abstract class
	template<size_t limbs>
	class Character abstract : public TechStorm::GameObject
	{
	protected:

		Ray* target;

		HealthSystem::Limb* limbs[limbs];
		std::map<const char*, CharacterStat*> stats;

	public:

		bool godMode = false;
		bool invisible = false;
		float health = 100.0f;
		bool isDead;
		bool isplayer = false;
		bool running;
		float runDelta;
		bool walking = true;
		float walkDelta;
		bool crawling;

		// subtracts from the runDelta only if crawlRunning;
		float crawlDelta;
		float speed = 0.0f;
		float baseSpeed;

		// how affected is the speed? IMPORTANT: if you need this to decrease the value, set as negative.
		float speedAffectDelta;

		void init(float baseSpeed, float runDelta, float crawlDelta, float walkDelta) {
			this->baseSpeed = baseSpeed;
			this->runDelta = runDelta;
			this->crawlDelta = crawlDelta;
			this->walkDelta = walkDelta;

			this->speed = baseSpeed + speedAffectDelta;
			this->threadSafe = true;
		}

		virtual void setSpeedAffectDelta(float val) {
			this->speedAffectDelta = val;
		}

		virtual void crawl() {
			crawling = true;
			this->speed = baseSpeed + speedAffectDelta;
			this->speed += crawlDelta;
		}

		virtual void run() {
			this->running = true;
			if (this->walking != false) {
				this->walking = false;
			}

			if (crawling) {
				this->speed = baseSpeed + speedAffectDelta;
				this->speed += runDelta + crawlDelta;
			}
			else {
				this->speed = baseSpeed + speedAffectDelta;
				this->speed += runDelta;
			}
		}

		virtual void walk() {
			this->walking = true;
			if (this->running != false) {
				this->running = false;
			}
			if (crawling) {
				this->speed = baseSpeed + speedAffectDelta;
				this->speed += crawlDelta;
			}
			else {
				this->speed = baseSpeed + speedAffectDelta;
				this->speed += walkDelta;
			}
		}

		virtual void stopCrawling() {
			this->crawling = false;
		}

		virtual void stopRunning() {
			this->running = false;
		}

		virtual void stopWalking() {
			this->walking = false;
		}

		bool isStill() const {
			return this->speed == 0.0f;
		}

		void initCharacter(float baseSpeed, float runDelta, float crawlDelta, float walkDelta) {
			this->init(baseSpeed, runDelta, crawlDelta, walkDelta);

			std::vector<CharacterStat*> stats = {
				new CharacterStat {
					true,
					"damnit",
					0.04f
	}
			};

			this->addStats(stats);
		}

		// updates values of health
		void tick() {
			for (auto& stat : stats) {
				stat.second->tick();
			}

			// update vitals
			if (this->health <= 0.0f) {
				this->isDead = true;
			}
		}

		void addStat(CharacterStat* stat) {
			this->stats[stat->name] = stat;
		}

		void addStats(std::vector<CharacterStat*> stats) {
			for (int i = 0; i < stats.size(); i++) {
				addStat(stats[i]);
			}
		}

		void damage(float delta) {
			this->health -= delta;
		}

		void printDebugStatement() {
			TechStorm::Logman::Log(TextFormat("Speed : %i", this->speed));
		}
	};
}
