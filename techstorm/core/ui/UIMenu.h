#pragma once
#include "UIElement.h"
#include "../../Game.h"

namespace TechStorm {
	class UIMenu abstract : public UIContainer {
	protected:

		Sound m_clickSound;
		Sound m_hoverSound;
	public:

		virtual void drawMenu() {
			UIContainer::drawChildren(DRAW_FINAL);
		}

		virtual void update() override {
			UIContainer::update();
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
