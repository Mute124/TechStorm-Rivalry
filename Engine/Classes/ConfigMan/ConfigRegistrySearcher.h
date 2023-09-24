#pragma once
#include "../Logging/Logman.h"
#include "ConfigFile.h"
#include <vector>

// Component class of ConfigRegistry
class ConfigRegistrySearcher {
    public:
        ConfigRegistrySearcher() {}

        ConfigFile FindFile(std::vector<ConfigFile> &Dataset, const char *TargetFile) {
            if (DoesFileExist(Dataset, TargetFile)) {
                for (int i = 0; i < Dataset.size(); i++) {
                    if (Dataset[i].file.typedata.File == TargetFile) {
                        return Dataset[i];
                    }
                }
            } else {
                return ConfigFile();
            }
        }

        bool DoesFileExist(std::vector<ConfigFile> &Dataset, const char *TargetFile) {
            bool found;
            for (int i = 0; i < Dataset.size(); i++) {
                if (Dataset[i].file.typedata.File == TargetFile) {
                    found = true;
                }
            }
            if (!found) {
                found = false;
            }

            return found;
        }
};