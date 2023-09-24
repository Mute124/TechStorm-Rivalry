#pragma once

#include "ConfigRegistry.h"

class ConfigMan 
{
    public:

        ConfigMan() {
            Logman::CustomLog(LOG_INFO, "New Config Manager instance created.", NULL);
        };
        
        static inline ConfigRegistry *configregistry = new ConfigRegistry();

};