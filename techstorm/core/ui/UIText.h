#pragma once
#include "UIMan.h"
#include "UIElement.h"



class UITextElement : public SimpleUIElement {
public:

	void draw() override {
		UIMan::drawText(text, this->anchor);
	}

	UITextElement(Vector2 anchor, const char* text) {
		this->anchor = anchor;
		this->text = text;
		
	}

private:

	const char* text;
};