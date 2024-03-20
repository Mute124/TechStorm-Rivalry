#pragma once
#include "../../Common.h"
#include "Asset.h"

class AssetLoader {
public:
	bool done;

	AssetLoader() {
	}

	template<typename T>
	Asset<T> getAsset(const char* name) {
		return assets[name];
	}

	void flush() {
		assets.clear();
	}

private:
	std::map<const char*, Asset<std::any>> assets;
};
