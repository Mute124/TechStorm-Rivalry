// manager for the mINI library
#pragma once

#include "lib/mINI-master/src/mini/ini.h" // reads settings files so I dont have to fucking compile each time and can modify variables while game runs.


class MiniMan {
    
    private:
        static const mINI::INIFile file("config.ini");
    public:
        MiniMan() {};

        char *Read(const char *Section) {};
};