#pragma once
#include "lib/raylib.h"
#include "Globals.h"

class Textures
{
    public:
        int LoadTextures() {
            // Resolve Game location
            const char *Game_path = GetWorkingDirectory();
            
            // Load all textures.
            LoadDirectoryFiles("C:/git/Minero/raylib/projects/VSCode/resources/textures");
        }
        Textures() {


        }
};