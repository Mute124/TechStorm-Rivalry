#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include "../../player/Player.h"

class World {
public:
	Player* player;
	World() = default;
	virtual ~World() = default;
};
