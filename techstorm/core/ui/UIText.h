#pragma once
#include "UIMan.h"
#include "UIElement.h"

// A text element. automatically pushes to the UIMan if no container is defined.
class UITextElement : public UIElement {
public:

	// constructors

	// Please define the parent container or it will be made a rogue.
	UITextElement(const char* text, Vector2 anchor, Vector2 Offset, Color color, float size, float spacing, int parentContainerID = 0) {
		this->anchor = anchor;
		this->offset = Offset;
		this->text = text;
		this->fontSize = size;
		this->fontSpacing = spacing;

		// push to uiman
		UIMan::getInstance()->pushRogueElement(this);
	}
};
