#pragma once
#include "../Common.h"
#include "../core/ui/UIElement.h"
#include "../Game.h"

#define MAX_INPUT_CHARS 32

namespace Console {
	class ConsoleUI : public UIElement {
	public:
		bool mouseOnText = false;
		bool isHidden = true;
		bool updateBackdrop = true;
		bool beingMoved = false;
		char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
		int letterCount = 0;
		int framesCounter = 0;
		int waitTimer = 0;
		int scrollChange = 0;
		Rectangle textBox = { 0, GetScreenHeight() - (GetScreenHeight() * 0.10f), 500, 50 };
		Rectangle consoleBackDrop;

		ConsoleUI() {
			Game::uiMan->pushRogueElement(this);
		}

		virtual void draw() override {
			if ((this->isVisible) || (this->alwaysVisible)) {
				if (updateBackdrop) {
					if ((this->consoleBackDrop.width >= 0) || (this->consoleBackDrop.height >= 0)) {
						this->consoleBackDrop = Rectangle{
							this->anchor.x + 0,
							this->anchor.y + 0,
							(textBox.width + 5) + (float)scrollChange,
							((float)GetScreenHeight() - (GetScreenHeight() * 0.10f) + 5) + (float)scrollChange
						};
					}
					else {
						this->consoleBackDrop = Rectangle{
							this->anchor.x + 0,
							this->anchor.y + 0,
							(textBox.width + 5) ,
							((float)GetScreenHeight() - (GetScreenHeight() * 0.10f) + 5)
						};
					}

					this->textBox.x = this->anchor.x;
					this->textBox.y = this->anchor.y + GetScreenHeight() - (GetScreenHeight() * 0.10f);

					if ((this->textBox.width >= 0) || (this->textBox.height >= 0)) {
						this->textBox.width += scrollChange;
						this->textBox.height += scrollChange;
					}

					this->updateBackdrop = false;
				}

				//DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY);
				DrawRectangleRec(this->consoleBackDrop, GRAY);

				DrawRectangleRec(textBox, LIGHTGRAY);
				if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
				else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

				Vector2 pos = Vector2{ textBox.x + 5, textBox.y + 8 };
				DrawTextEx(UIElement::font, this->name, pos, (float)UIElement::font.baseSize, 2.0f, MAROON);

				if ((MAX_INPUT_CHARS - this->letterCount) < (MAX_INPUT_CHARS * 0.90)) {
					//DrawText(TextFormat("INPUT CHARS: %i/%i", this->letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);
				}

				if (this->letterCount < MAX_INPUT_CHARS)
				{
					// Draw blinking underscore char
					if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, fontSize - fontSpacing), (int)textBox.y + 12, 40, MAROON);
				}
				//else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
			}
		}

		virtual void onUpdate() {
			if (IsKeyPressed(KEY_SLASH)) {
				this->isVisible = !this->isVisible;
			}

			if ((this->isVisible) || (this->alwaysVisible)) {
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

					if (waitTimer == 0) {
						if (IsKeyDown(KEY_BACKSPACE))
						{
							letterCount--;
							if (letterCount < 0) letterCount = 0;
							name[letterCount] = '\0';
							this->waitTimer = GetFrameTime() + 10;
						}
					}
					else {
						waitTimer--;
					}

					if (IsKeyDown(KEY_ENTER)) {
						parseCommand(name);

						for (int i = 0; i < MAX_INPUT_CHARS; i++) {
							letterCount--;
							if (letterCount < 0) letterCount = 0;
							name[letterCount] = '\0';
						}
					}
				}
				else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

				if ((IsKeyDown(KEY_LEFT_ALT)) && (IsMouseButtonDown(MOUSE_BUTTON_LEFT))) {
					SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
					this->anchor = GetMousePosition();
					updateBackdrop = true;
					beingMoved = true;
				}

				if (IsKeyDown((KEY_LEFT_ALT))) {
					this->scrollChange = GetMouseWheelMove();
					this->updateBackdrop = true;
				}

				if (mouseOnText) framesCounter++;
				else framesCounter = 0;
			}
		}
	private:
		void parseCommand(const char* txt) {
			try
			{
				Logman::Log(TextFormat("Running Command : %s", txt));
				Game::lua->lua.script(txt);
			}
			catch (const std::exception& e)
			{
				Logman::Error(TextFormat("Lua Error : %s", e.what()));
			}
		}
	};
}
