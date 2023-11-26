#pragma once

#include "Engine/Classes/Project/Game/Game.h"

class Minero {
    public:
        Minero() {
            game.StartGame();
        }

        Game game;
};