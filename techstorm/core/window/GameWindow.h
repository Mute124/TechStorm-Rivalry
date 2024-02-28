#pragma once
#include "Window.h"
#include "ConfigFlag.h"
#include <raylib.h>
class GameWindow : public Window
{
public:

	GameWindow(int width, int height, char* title, ConfigFlags flags[], Layer* renderLayer) : renderLayer(renderLayer) {
		this->properties = WindowProperties({ width, height }, title, flags, false);
	}

	void init() final override {
		this->properties.isActive = true;

		std::function<void()> windowInit = [this]() {
			// todo: Set config flags, init window.
			};

		//renderLayer->passivePush();
		//renderLayer->passivePush(InitWindow(this->properties.size.width, this->properties.size.height, this->properties.title));
	}

	void destroy() final override {
		delete renderLayer;
	}

	WindowSize getSize() {
		return this->properties.size;
	}

	WindowProperties getProperties() {
		return this->properties;
	}

protected:
	Layer* renderLayer;
};
