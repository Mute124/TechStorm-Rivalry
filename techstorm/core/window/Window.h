#pragma once
#include "../../common.h"

typedef struct WindowSize {
	int width;
	int height;
};

typedef struct WindowProperties {
	WindowSize size;
	char* title;
	ConfigFlags* flags;

	bool isActive;
};

class Window abstract
{
public:

	WindowProperties properties;

	virtual void init() = 0;
	virtual void destroy() = 0;
};
