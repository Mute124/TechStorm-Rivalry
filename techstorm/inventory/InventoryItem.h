#pragma once
#include "../core/player/Player.h"
#include "../core/scripting/ScriptManager.h"

class InventoryItem abstract {
protected:

	Player* parentPlayer;

	const bool consumable;
	const bool singleUse;

	const char* name;
	const char* rarity;

	int uses;

	int conditionMax;

	IScriptable* ScriptItem = nullptr;

	virtual void use() = 0;

	void SetParentPlayer(Player* player) {
		parentPlayer = player;
	}
};
