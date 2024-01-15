#pragma once
#include "lib/raylib.h"

class GameObj2D 
{
    public:
    
        typedef enum type
        {
            GUI = 0
        };
        
        virtual void Draw() const = 0;
        virtual ~GameObj2D() {}

    private:
        Vector2 g_position;
        
};