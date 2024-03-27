#pragma once
#include "../core/utils/Math.h"
#include "../core/ui/UIElement.h"

class UIFadingMsg : public TechStorm::UIElement {
public:

private:
	float fadeTimer = 0.0f;
	float fadeDelta;
	float fadeTime = 1.0f;
};
