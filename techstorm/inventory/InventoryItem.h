#pragma once

class InventoryItem abstract {
public:
	Player* parentPlayer;
	bool consumable = false;

	bool singleUse = false;
	bool medicalItem = false;
	bool deleteMe = false;
	const char* name;
	const char* rarity;
	int uses = -1; // if -1, it has infinite uses.
	int conditionMax;
	float conditionDelta; // Each time the item is used, it

	virtual void use() {
		if (!singleUse) {
		}
	};

	EMaterialTypes* TranslateMaterialType(const char* target) {
		if (target == "Metal") {
			return new EMaterialTypes(METAL);
		}
	}

	EItemRarity* TranslateRarity(const char* target) {
		if (target == "Common") {
			return new EItemRarity(COMMON);
		}
	}

	void SetParentPlayer(Player* player) {
		parentPlayer = player;
	}
};
