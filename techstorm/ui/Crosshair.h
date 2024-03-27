#pragma once
#include "../core/ui/UIElement.h"

class Crosshair : public TechStorm::UIElement {
public:
	float offset = 100.0f;
	Vector2 middle;
	Crosshair(Vector2 middlePos, TechStorm::UIMan* man) {
		this->drawTime = DRAW_FINAL;
	}

	void drawElement() override {
		// top line
		DrawLineV({ middle.x, middle.y + offset }, { middle.x, middle.y + (offset * 2) }, GRAY);
	}
};
