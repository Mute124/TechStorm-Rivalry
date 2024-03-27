#pragma once
#include "EAssetType.h"

namespace TechStorm {
	template<typename T>
	class Asset {
	public:
		EAssetType type = EASSET_NULL;
		const char* name = "null";
		T* asset = nullptr;

		Asset(EAssetType assetType, const char* name, T asset) {
			this->type = assetType;
			this->name = name;
			this->asset = &asset;
		}
	};
}
