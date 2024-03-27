#pragma once
#include "UIElement.h"
#include "../../Game.h"
#include "../../console/Console.h"
namespace TechStorm {
	class UIMenu : public UIContainer {
	public:

		// Only call when the menu is finalized and all elements are added!
		virtual void initMenu(Game& game) {
			game.pushContainer(this, false, false);
		}

		virtual void drawMenu() {
			this->drawChildren(DRAW_FINAL);
		}

		virtual void update() override {
		}

		virtual void awakeMenu() {
			this->wake();
		}

		virtual void sleepMenu() {
			this->sleep();
		}

		virtual void destruct() {
			this->clear();
		}
	};
}
