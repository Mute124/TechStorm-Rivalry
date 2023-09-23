#pragma once
#include "lib/raylib.h"
#include "Gameobj.h"

class WorldScreenComp {
    public:

        WorldScreenComp(const char * Text, Vector2 Offset) : text(Text), offset(Offset) {
            
        }

        virtual void DrawTextComp() const = 0 {
            
        }

        
        
    private:

        const char *text;
        Vector2 offset;
        Vector3 objectPosition;
        
        

};