#pragma once
#define RAYGUI_IMPLEMENTATION
#include "../../Common.h"
#include "../scripting/ScriptManager.h"

class UIMan  {
public:
	static inline Font fontTtf;
	static inline void init() {
		// load default style.
		GuiLoadStyle("Data/gui/styles/default.rgs");

		// load default font.
		fontTtf = LoadFontEx("Data/gui/fonts/Tektur-VariableFont_wdth,wght.ttf", 32, 0, 250);
		SetTextLineSpacing(48);
	}

	static inline void update() {
		for (UIElement* element : elements) {
			element->update();
		}
	}

	static inline void draw() {
		for (UIElement* element : elements) {
			element->draw();
		}
	}

	static inline void drawText(const char* text, Vector2 anchor, Color color) {
		DrawTextEx(fontTtf, text, anchor, 32, 0, RAYWHITE);
	}

	static void push(UIElement* element) {
		elements.push_back(element);
	}

	


private:
	static inline std::vector<UIElement*> elements;

	
};