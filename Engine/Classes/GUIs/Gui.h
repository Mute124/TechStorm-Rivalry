#pragma once
#include "../../../lib/raylib.h"
#include "../Component.h"

class GUI {
    public:


        GUI() {
            
        }

        GUI(Vector2 dimensions, Vector2 position, Color backdrop) {
            this->dimensions = dimensions;
            this->position = position;
            this->backdrop = backdrop;
        }
        
        virtual void onStart() {
            
        }

        virtual void onUpdate() {
            
        }

        virtual void Draw() {

            
        }

        ~GUI() {
            delete this;
        }
    Vector2 dimensions;
    Vector2 position;

    Color backdrop;


};