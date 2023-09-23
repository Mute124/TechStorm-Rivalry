#pragma once
#include "../Logman.h"
#include "../lib/raylib.h"
#include "lib/tomlplusplus-3.3.0/tomlplusplus-3.3.0/toml.hpp"

class ConfigMan
{
public:
    // should use logman, however, this is a test
    ConfigMan(const char *file)
    {
        if (!FileExists(file))
        {
            Logman::CustomLog(LOG_WARNING, TextFormat("Config file not found: %s", file), NULL);
        }
        else
        {

            try
            {
                result = toml::parse_file(file);
            }
            catch (const toml::parse_error &err)
            {
                Logman::CustomLog(LOG_ERROR, TextFormat("Error parsing config file: %s", err.what()), NULL);
            }
        }
    }

    template <typename T>
    T GetEntry(const char *section, const char *entry)
    {
            return result[section][entry].as<T>();
        

    }

private:
    toml::parse_result result;
};