#pragma once
#include "UIMan.h"
#include "UIElement.h"

class UITextElement : public UIElement {
public:

	// constructors
	UITextElement(const char* text, Vector2 anchor, Vector2 Offset) {
		this->anchor = anchor;
		this->offset = Offset;
	}
};
