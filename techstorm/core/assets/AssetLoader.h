#pragma once
#include "../../Common.h"
class AssetLoader {
public:
	std::map<const char*, std::any> assets;

	bool done;

	void LoadAssets(const char* assets) {
	}
};
