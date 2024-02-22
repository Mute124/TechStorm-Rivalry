#pragma once
#include "../../Game.h"
#include "Layer.h"
#include "Layers.h"

class MainLayer {
public:

	MainLayer() {
		layers = new Layers();
		layers->init();
	}

	void run() {
		
	}
	
	static inline Layers* layers;
	static inline Game *game;
};