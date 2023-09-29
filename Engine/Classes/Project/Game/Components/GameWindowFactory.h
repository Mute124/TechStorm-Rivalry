#pragma once
#include "../../../../../lib/raylib.h"

#include <vector>

class GameWindowFactory
{
public:
    GameWindowFactory() {}

    // Manufacture a window. NOTE : this finalizes the window! do your stamping before calling this.
    void ManufactureWindow(int width, int height, const char *title)
    {
        InitWindow(width, height, title);
    };
    
    void StampFlag(ConfigFlags flag)
    {
        SetConfigFlags(flag);
    }

private:
};