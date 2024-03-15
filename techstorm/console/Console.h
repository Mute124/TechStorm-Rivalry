#pragma once
#include "../Common.h"
#include "../core/ui/UIElement.h"
#include "../Game.h"

#define MAX_INPUT_CHARS 32

namespace Console {
	class ConsoleUI {
	public:
		char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
		int letterCount = 0;

		Rectangle textBox = { Game::screenMiddle.x - 100, 180, 225, 50 };
		bool mouseOnText = false;

		int framesCounter = 0;
		ConsoleUI() {
			//this->drawTime = DRAW_CLIPPABLE;
			///name = *RL_MALLOC(sizeof(char*) * MAX_INPUT_CHARS + 1);
		}

		void draw() {
			//DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY);

			DrawRectangleRec(textBox, LIGHTGRAY);
			if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
			else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

			Vector2 pos = Vector2{ textBox.x + 5, textBox.y + 8 };
			DrawTextEx(UIElement::font, this->name, pos, (float)UIElement::font.baseSize, 2.0f, MAROON);

			DrawText(TextFormat("INPUT CHARS: %i/%i", this->letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);
			if (this->letterCount < MAX_INPUT_CHARS)
			{
				// Draw blinking underscore char
				if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
			}
			//else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
		}

		void update() {
			if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
			else mouseOnText = false;
			if (mouseOnText)
			{
				// Set the window's cursor to the I-Beam
				SetMouseCursor(MOUSE_CURSOR_IBEAM);

				// Get char pressed (unicode character) on the queue
				char key = GetCharPressed();

				// Check if more characters have been pressed on the same frame
				while (key > 0)
				{
					// NOTE: Only allow keys in range [32..125]
					if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
					{
						name[letterCount] = key;
						name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
						letterCount++;
					}

					key = GetCharPressed();  // Check next character in the queue
				}

				if (IsKeyDown(KEY_BACKSPACE))
				{
					letterCount--;
					if (letterCount < 0) letterCount = 0;
					name[letterCount] = '\0';
				}
			}
			else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

			if (mouseOnText) framesCounter++;
			else framesCounter = 0;
		}
	};

	// parses everything
	class ConsoleBrain {
	};
}
