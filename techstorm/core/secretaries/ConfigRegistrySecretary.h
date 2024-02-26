#pragma once
#include <raylib.h>
#include <vector>
#include "../fileSystem/File.h"
#include "../config/ConfigFile.h"

class ConfigRegistrySecretary {
public:
	ConfigRegistrySecretary() {}

	static inline ConfigFile findFile(std::vector<ConfigFile>& Dataset, const char* TargetFile) {
		ConfigFile file;
		if (doesFileExist(Dataset, TargetFile)) {
			for (int i = 0; i < Dataset.size(); i++) {
				if (Dataset[i].file.entry.FilePath == TargetFile) {
					file = Dataset[i];
				}
			}
		}
		return file;
	}

	static inline bool doesFileExist(std::vector<ConfigFile>& Dataset, const char* TargetFile) {
		bool found = false;
		for (int i = 0; i < Dataset.size(); i++) {
			if (Dataset[i].file.entry.FilePath == TargetFile) {
				found = true;
			}
		}
		if (!found) {
			found = false;
		}
		return found;
	}
};