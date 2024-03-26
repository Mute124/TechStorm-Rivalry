#pragma once
#include "UIMan.h"

struct UI3DBillboardData {
	Vector2 anchor;
	const char* txt = "null";
	Rectangle billboard;
	Color color;
};

class UI3DBillboard : public UIElement {
public:

	void init(UI3DBillboardData data) {
		// set to a rogue container.
		this->setContainer(0);

		this->anchor = data.anchor;
		this->uiType = EUI_SHAPE;
		this->bounds = data.billboard;
		this->color = color;
		this->drawTime = DRAW_CLIPPABLE;
	}

protected:

	RenderTexture billboard;

	void customDraw() override {
	}
};
