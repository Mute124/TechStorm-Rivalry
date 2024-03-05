#pragma once
#include "../core/utils/Math.h"
#include "../core/ui/UIElement.h"

class UIFadingMsg : public UIElement {
public:
	void init(float fadeTime, const char* txt, Vector2 anchor, Vector2 offset = Vector2{ 0, 0 }) {
		this->fadeTime = fadeTime;
		this->fadeDelta = abs(100.0f / fadeTime);
		this->text = txt;
		this->anchor = anchor;
		this->offset = offset;
		this->setOpacity(0.0f);

		this->SetType(EUI_TEXT);
	}

	virtual void customUpdate() override {
		if (this->opacity >= 100.0f) {
			this->opacity += fadeDelta;
			this->setOpacity(this->opacity);
		}
	}

	~UIFadingMsg() {
		delete this;
	}
private:
	float fadeTimer = 0.0f;
	float fadeDelta;
	float fadeTime = 1.0f;
};
