#pragma once
#include "../Gameobj.h"

class Skybox : public GameObject {
    public:
        Skybox() : id(RegisterObj(this)) {
            
        };
        
        void Draw() override {};

    private:
        const int id;
};