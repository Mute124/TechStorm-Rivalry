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


    template <typename T>
    T GetEntryinFile(const char *file, const char *section, const char *entry)
    {
        GetFile(file)->GetEntry<T>(section, entry);
    }

    bool IsFileRegistered(const char *file) {
        return Searcher->DoesFileExist(registry, file);
    }

    // Get a config file
    ConfigFile *GetFile(const char *file) {
        ConfigFile result = std::move(Searcher->FindFile(registry, file));
        return &result;
    }

    // register a config file into the registry
    void RegisterFile(const char *file) {
        registry.push_back(ConfigFile(file));
    }

    // Flush the registry, WILL NOT SAVE!
    int Flush() {
       ConfigFile::Flush();
       bool issuccessful = registry.empty();
       return issuccessful;
    }

private:

    ConfigRegistrySearcher *Searcher = new ConfigRegistrySearcher(); // Searching component
    std::vector<ConfigFile> registry;
};