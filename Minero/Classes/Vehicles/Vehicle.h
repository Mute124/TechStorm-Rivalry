#pragma once
#include "../lib/raylib.h"
#include "../lib/raymath.h"
#include "../../../Engine/Classes/GameObject/Gameobject.h"



class Vehicle : public GameObject {
    public:
        void Create(Vector3 position, Model model) {
            
        }



    private:

        Vector3 position;
        Model model;

        Ray raylook;
};