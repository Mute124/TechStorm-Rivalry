#pragma once

#include "ConfigRegistry.h"
#include "ConfigTypeConverter.h"

// NOTE : Very much so broken... FUUUUUUUUUUUUUUUUUUUUU
class ConfigMan : public ConfigRegistrySecretary, public ConfigTypeConverter
{
    public:

        ConfigMan() {
            Logman::CustomLog(LOG_INFO, "New Config Manager instance created successfully!", NULL);
        };
    

        ~ConfigMan() {
            delete this;
        }


        static void Innit() {
        
            Registry = new ConfigRegistry();

            ConfigFile::Innit();
            Logman::CustomLog(LOG_INFO, "Loading TOML files from Config folder...", NULL);

            // TODO : Make this automatic.
            Registry->RegisterFile("Config/Engine.toml");
            Registry->RegisterFile("Config/options.toml");

            Logman::CustomLog(LOG_INFO, "Loaded TOML files from Config folder", NULL);

        }
        
        static ConfigRegistry *Registry;

    private:



};