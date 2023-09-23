#pragma once
#include "lib/raylib.h"
#include "Logman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
class Monitor {

public:
    Monitor() : id(GetCurrentMonitor()), physicalWidth(GetMonitorWidth(GetCurrentMonitor())), physicalHeight(GetMonitorHeight(GetCurrentMonitor())), ScreenWidth(GetScreenWidth()), ScreenHeight(GetScreenHeight()), monitorHz(GetMonitorRefreshRate(GetCurrentMonitor())) {
        Logman::CustomLog(LOG_INFO, TextFormat("Monitor with the id %i has been registered", id), NULL);
    };


    
    private:
        const int id;
        int Position;
        const int physicalWidth;
        const int physicalHeight;

        const int monitorHz;

        const int ScreenWidth;
        const int ScreenHeight;

};