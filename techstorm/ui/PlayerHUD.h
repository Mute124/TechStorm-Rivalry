#pragma once
#include "Crosshair.h"
#include "../core/ui/UIMenu.h"

namespace TechStormRivalry {
	class PlayerHUD : public TechStorm::UIMenu {
	public:
		PlayerHUD(Game* game) {
			addChild(new Crosshair(Vector2Zero()));
		}
	};
}
