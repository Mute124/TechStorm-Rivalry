#pragma once
#include "Layer.h"
#include "../logging/Logman.h"

class WorkerLayer : public Layer {
public:
	WorkerLayer() {
	}

	~WorkerLayer() {
		this->shutdown();
	}

	void init() final override {
		Logman::log("RenderLayer::init()");
	}


};