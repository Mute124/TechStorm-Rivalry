#pragma once
#include "../../../lib/tomlplusplus-3.3.0/tomlplusplus-3.3.0/toml.hpp"
#include "../../DataSets/ListEntry.h"
#include "../../DataSets/File/File.h"

#include "ConfigTypeConverter.h"
#include "ConfigMan.h"
class ConfigFile
{
public:
    // FilePath path goes in here
    ConfigFile(const char *File)
    {
        file.id = AssignId(); // Assign the file's id;

        file.entry.FilePath = File;
        file.entry.Data = toml::parse_file(File);
        file.tag = "Config";
        file.entry.isLoaded = true; // signals that this is ready.
    }

    ConfigFile()
    {
        // creates a Null.
    }

    ConfigFile *Get() {
        return this;
    }

    // The solution to the issue of not being able to get a int from a config file.
    int GetIntEntry(const char *section, const char *entry)
    {
        // convert from int64_t to int
        toml::table tbl = *(file.entry.Data[section][entry].as_table()); // Tableize

        int result = tbl[section][entry].as_integer()->operator int64_t &();

        return result;
    }

    bool GetBoolEntry(const char *section, const char *entry)
    {
        toml::table tbl = *(file.entry.Data[section][entry].as_table());

        bool result = bool{tbl[section][entry].as_boolean()->operator const bool &()};

        return result;
    }

    // since VSCode complains, this needs to be here.
    static void Innit() {
        ConfigFileCount = 0;
    }

    // reset count
    static inline void Flush()
    {
        ConfigFileCount = 0;
    }

    ListEntry<File<toml::v3::parse_result>> file;

private:
    static inline int AssignId()
    {
        int id = ConfigFileCount;
        ConfigFileCount += 1;
        return id;
    }

    static int ConfigFileCount; // Corrosponds with place in what list it is in
};
