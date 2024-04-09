#pragma once
#include "../TechStorm.h"
#include "UIElement.h"

#include <functional>
namespace TechStorm {
	class UIButton : UIElement {
	private:
		Sound m_onClickSound = { 0 };
		Sound m_onHoverSound = { 0 };
		bool m_isClicked = false;
		Rectangle m_rect;
		const char* m_text;

		bool m_hide = false;

	public:

		bool isClicked() {
			return m_isClicked;
		}

		float getX() {
			return this->m_rect.x;
		}

		float getY() {
			return this->m_rect.y;
		}

		Rectangle& getBoundry() {
			return this->m_rect;
		}

		UIButton(Rectangle rect, const char* txt, Sound clickSound, Sound hoverSound) : m_rect(rect), m_text(txt), m_onClickSound(clickSound), m_onHoverSound(hoverSound) {
			SetSoundVolume(m_onClickSound, 25.0f);
		}

		void drawElement() override {
			m_isClicked = GuiButton(this->m_rect, this->m_text);

			// has to be false because it would only play at the end of the collision.
			if (CheckCollisionPointRec(GetMousePosition(), this->m_rect)) {
				PlaySound(m_onHoverSound);
			}

			if (m_isClicked) {
				PlaySound(m_onClickSound);
			}
		}

		void updateElement() override {

		}
	};
}
