#pragma once
#include "lib/raylib.h"
#include <thread>
class HeightMap {
    public:
        HeightMap(int Width, int Height, int offsetX, int offsetY, float Scale) {

            
            heightmap = GenImagePerlinNoise(Width, Height, offsetX, offsetY, Scale);
            ExportImage(heightmap, "heightmap.png");
            UnloadImage(heightmap);
        }

        ~HeightMap() {
            delete this;
        }

        Image GetHeightMap() {
            return heightmap;
        }


    private:
        Image heightmap;


};