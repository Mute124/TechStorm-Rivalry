#pragma once
#include "../Common.h"
#include "../core/ui/UIElement.h"
#include "../Game.h"

namespace TechStormRivalry {
	class Crosshair : public TechStorm::UIElement {
	public:
		float offset = 100.0f;
		Vector2 middle;
		Crosshair(Vector2 mid) {
			this->drawTime = DRAW_FINAL;
			this->middle = mid;
		}

		void drawElement() override {

			// top line
			DrawLineV({ middle.x, middle.y + offset }, { middle.x, middle.y + (offset * 2) }, GRAY);
		}
	};
}
