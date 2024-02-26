#pragma once
#include "../../Common.h"

class DialogBox {
public:

private:

	Vector2 anchor;
	Vector2 position;

	const char *title;
	const char* text;
	
	int width;
	int height;

	Color foreground;
	Color outline;
};
