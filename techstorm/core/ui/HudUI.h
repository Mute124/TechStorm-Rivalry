#pragma once
#include "UIMenu.h"

namespace TechStorm {
	class HudUI abstract : public UIMenu {
	public:
		virtual void initMenu(Application& game) {
			UIMenu::initMenu(game);
			this->awakeMenu();
		}
	};
}
