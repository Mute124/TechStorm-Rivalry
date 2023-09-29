#pragma once
#include "../../../lib/tomlplusplus-3.3.0/tomlplusplus-3.3.0/toml.hpp"
#include <map>
#include <vector>
#include "../Logging/Logman.h"
#include "../../../lib/raylib.h"

// Components
#include "ConfigFile.h"
#include "ConfigRegistrySearcher.h"

class ConfigRegistry
{
public:
    ConfigRegistry() {

    }

    ~ConfigRegistry() {
        delete ConfigSecretary;
    }


    bool IsFileRegistered(const char *FileName)
    {
        return ConfigSecretary->DoesFileExist(registry, FileName);
    }

    // Get a config FileName
    ConfigFile GetFile(const char *FileName)
    {
        return ConfigSecretary->FindFile(registry, FileName);
    }

    // register a config FileName into the registry
    void RegisterFile(const char *FileName)
    {
        registry.push_back(ConfigFile(FileName));
    }

    // Flush the registry, WILL NOT SAVE!
    int Flush()
    {
        ConfigFile::Flush();
        bool issuccessful = registry.empty();
        return issuccessful;
    }

    

    ConfigRegistrySecretary *ConfigSecretary = new ConfigRegistrySecretary(); // Searching component
private:

    std::vector<ConfigFile> registry;
};