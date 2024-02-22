#pragma once
#include "Layer.h"

class RenderLayer final : public Layer {
public:

	RenderLayer() {
	}

	~RenderLayer() {
		this->shutdown();
	}

	void init() final override {
		Logman::Log("RenderLayer::init()");
	}

	// push the tasks to the render queue
	void render(std::function<void()> task) {
		this->push(task);
	}



};