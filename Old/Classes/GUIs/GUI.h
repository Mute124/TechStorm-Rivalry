#pragma once
#include "../lib/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <string>


class Gui {
    public:


        virtual void Draw() const = 0;

        virtual void OnUpdate();

        
        virtual ~Gui() {}

    private:
        
        
};