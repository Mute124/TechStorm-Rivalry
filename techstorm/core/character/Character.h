#pragma once
// local includes
#include "CharacterComponent.h"
#include "../obj/Gameobject.h"

#include "../../Common.h"
#include "../ecs/ECSMan.h"

#include "../threading/ThreadGroups.h"

typedef struct CharacterStat {
	float val;
	float valChange;
	const char* name;
};

// A game character abstract class
class Character abstract : public GameObject, public IScriptable
{
public:

	// use derived class's constructor instead of this!
	void init() final override
	{
		this->addStats(
			std::vector<CharacterStat>
		{
			CharacterStat{
					0.0f,
					0.0f,
					"boredom"
			},
				CharacterStat{
						0.0f,
						0.0f,
						"happiness"
			},
				CharacterStat{
					100.0f,
					0.0f,
					"health"
			},
				CharacterStat{
					0.0f,
					0.0f,
					"stress"
			},
				CharacterStat{
				0.0f,
				0.0f,
				"hunger"
			},
				CharacterStat{
				0.0f,
				0.0f,
				"thirst"
			}
		}
		);
		
		ScriptManager::addScript(this);

	}

	void debugDraw() {
		
	}

	void update() final override {
		tick();
	}

	// updates values of health
	void tick() {
		for (auto& stat : stats) {
			stat.second.val += stat.second.valChange;
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

	void end() final override {

	}

protected:

	bool isDead;
	bool isRunning;
	bool isWalking;

	Ray* target;

	std::map<const char*, CharacterStat> stats;
};
