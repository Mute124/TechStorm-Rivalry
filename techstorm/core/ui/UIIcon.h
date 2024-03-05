#pragma once
#include "UIElement.h"

// Provides the implementation for UIIcons.
class UIIcon : public UIElement {
public:

	void customDraw() override {
		DrawTextureEx(this->icon, this->position, 0.0f, 1.0f, this->color);
	}
protected:
	bool isRogue = false;
	Texture2D icon;

	UIIcon(Vector2 anchor, Vector3 offset) {
		this->anchor = anchor;
		this->color = WHITE;
	}
};
