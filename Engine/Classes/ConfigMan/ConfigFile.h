#pragma once
#include "../../../lib/tomlplusplus-3.3.0/tomlplusplus-3.3.0/toml.hpp"
#include "../../DataSets/ListEntry.h"
#include "../../DataSets/File/File.h"



class ConfigFile
{
public:
    // File path goes in here
    ConfigFile(const char *File) {
        file.id = AssignId(); // Assign the file's id;

        file.typedata.File = File;
        file.typedata.Data = toml::parse_file(File);
        file.tag = "Config";
        file.typedata.isLoaded = true; // signals that this is ready.        
    }

    ConfigFile() {
        // creates a Null.
    }

    template <typename T>
    T GetEntry(const char *section, const char *entry)
    {
        return file.typedata.Data[section][entry].as<T>();
    }


    // reset count
    static void Flush() {
        ConfigFileCount = 0;
    }

    ListEntry<File<toml::parse_result>> file;

private:
    static inline int AssignId() {
        return ConfigFileCount;
        ConfigFileCount += 1;
    }

    static int ConfigFileCount; // Corrosponds with place in what list it is in
};
