#pragma once
#include "../Logging/Logman.h"
#include "ConfigFile.h"
#include <vector>

// Component class of ConfigRegistry
class ConfigRegistrySecretary {
    public:
        ConfigRegistrySecretary() {}

        static inline ConfigFile FindFile(std::vector<ConfigFile> &Dataset, const char *TargetFile) {
            ConfigFile file;
            if (DoesFileExist(Dataset, TargetFile)) {
                for (int i = 0; i < Dataset.size(); i++) {
                    if (Dataset[i].file.entry.FilePath == TargetFile) {
                        file = Dataset[i];
                    }
                }
            } 
            return file;
        }

        static inline bool DoesFileExist(std::vector<ConfigFile> &Dataset, const char *TargetFile) {
            bool found;
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