#pragma once
// local includes
#include "CharacterComponent.h"
#include "../core/obj/Gameobject.h"

#include "../Common.h"
#include "../core/ecs/ECSMan.h"

#include "../core/threading/ThreadGroups.h"

#include "../core/utils/Math.h"

#include "IMoveableCharacter.h"

// A game character abstract class
class Character abstract : public GameObject
{
public:

	/*
	* Classifications are based off of real wound classifications. Green (minor), yellow(moderate), and red(critical)
	*
	* Minor severity denotes it is in early stage of healing, and most likely to recover with adequate care
	*
	* Moderate severity denotes it should get more medical attention and treatment than minor ones, but is unlikely to become lethal.
	*
	* Critical severity denotes it NEEDS medical attention
	*
	*/
	enum EStatSeverity {
		SEVERITY_NULL,
		SEVERITY_MINOR,
		SEVERITY_MODERATE,
		SEVERITY_CRITICAL
	};

	class CharacterStat {
	public:
		// Set isBad to true if it should start AT ZERO
		CharacterStat(bool isBad, float delta, const char* name) : name(name) {
			if (!isBad) {
				this->val = 100.0f;
			}
			else {
				this->val = 0.0f;
			}

			this->deltaVal = delta;
		}

		// Set isBad to true if it should start AT ZERO.
		CharacterStat(bool isBad, const char* name) : name(name) {
			if (!isBad) {
				this->val = 100.0f;
			}
			else {
				this->val = 0.0f;
			}

			this->deltaVal = 0.0f;
		}

		CharacterStat() {
		}

		// Note: THE DELTA MUST BE POSITIVE!
		void treat(float delta) {
			this->isTreated = true;
			this->treatmentDelta = -delta;
		}

		// adds the changeVal parameter to the deltaVal
		void changeDelta(float delta) {
			this->previousDelta = this->deltaVal;
			this->deltaVal += delta;
		}

		// calculate this stat's new state.
		void tick() {
			/*
			* incremental delta is calculated based on the slope of the previous and current delta times treatmentDelta + the stat's base severity delta.
			* equation looks like below
			*
			* idelta = tDelta(pDelta - cDelta) + bSeverity
			*
			*
			*/

			this->severityDelta = (deltaVal * treatmentDelta) * 100.0f;
			this->val += (deltaVal * treatmentDelta) * 100.0f;
		}

		float val;
		float deltaVal;

		const char* name;
		bool isBad;
		bool isTreated;

	protected:
		// used to calculate incremental severity
		float previousDelta;
		float severityDelta;

		float treatmentDelta;
		float incrementalDelta;
	};

protected:

	Ray* target;

	std::map<const char*, CharacterStat> stats;

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

		std::vector<CharacterStat> stats = {
			CharacterStat{
				true,
				"boredom"
			}
		};

		this->addStats(stats);
	}

	// updates values of health
	void tick() {
		for (auto& stat : stats) {
			stat.second.tick();
		}

		// update vitals
		if (this->health <= 0.0f) {
			this->isDead = true;
		}
	}

	void addStat(CharacterStat stat) {
		this->stats[stat.name] = stat;
	}

	void addStats(std::vector<CharacterStat> stats) {
		for (int i = 0; i < stats.size(); i++) {
			addStat(stats[i]);
		}
	}

	void damage(float delta) {
		this->health -= delta;
	}

	void printDebugStatement() {
		Logman::Log(TextFormat("Speed : %i", this->speed));
	}
};
