#pragma once
#include "lib/raylib.h"

class Animatable {
    public:
        virtual void AnimationSwitchTrigger();

        virtual void SwitchAnimationIndex();


    private:
        unsigned int animsCount = 0;
        unsigned int animIndex = 0;
        unsigned int animCurrentFrame = 0;
};