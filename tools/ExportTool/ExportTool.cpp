#include "AssetPacker.h"
#define _CRT_SECURE_NO_WARNINGS

#define RAYGUI_IMPLEMENTATION
#pragma warning(disable : 4996)
#include <raygui.h>
#define VERSION "Export-Tool v0.0.1"
#define MAX_INPUT_CHARS 248

int main() {
	InitWindow(800, 800, VERSION);

	bool exportAssetsBtnPressed = false;
	GuiLoadStyle("../../data/gui/styles/default.rgs");

	float width = 200.0f;
	float height = 200.0f;
	char name[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for null terminator char '\0'
	int letterCount = 0;
	int framesCounter = 0;
	int waitTimer = 0;

	bool getAssetDir = false;
	bool getAssetOutputDir = false;

	const char* usrInput = "";
	Image cursor = LoadImage("../../resources/textures/cursor.png");
	Texture curTex = LoadTextureFromImage(cursor);
	DisableCursor();
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		exportAssetsBtnPressed = GuiButton(Rectangle{
			GetScreenWidth() / 8.0f,
			GetScreenHeight() / 4.0f,
			width, height
			}, "Export Assets");
		bool see = true;

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
				waitTimer = GetFrameTime() + 10;
			}
		}
		else {
			waitTimer--;
		}

		if (IsKeyDown(KEY_ENTER)) {

			//parseCommand(name);

			usrInput = name;

			printf(usrInput);
			for (int i = 0; i < MAX_INPUT_CHARS; i++) {
				letterCount--;
				if (letterCount < 0) letterCount = 0;
				name[letterCount] = '\0';
			}
		}

		if (exportAssetsBtnPressed || getAssetDir) {
			int input = GuiTextInputBox(Rectangle{ GetScreenWidth() / 4.0f, GetScreenHeight() / 4.0f, width, height }, "Where is the game's resource & data folder located (relevant to this!)?", "text", "Next", name, 8, &see);
			getAssetDir = true;
			if (input == 0) {
				getAssetDir = false;
			}
			else if (input == 1) {

				//bool directoriesExist = DirectoryExists() && DirectoryExists(TextFormat("%s/data", usrInput));
							// NOTE: Only allow keys in range [32..125]
				name[letterCount - 1] = NULL; // Add null terminator at the end of the string.
				letterCount--;

				AssetPacker packer = AssetPacker();

				packer.run(TextFormat("%s/resources", usrInput), TextFormat("%s/resources", usrInput));

				//printf((const char*)exeExists);
				for (int i = 0; i < MAX_INPUT_CHARS; i++) {
					letterCount--;
					if (letterCount < 0) letterCount = 0;
					name[letterCount] = '\0';
				}

				//if (exeExists&&)
			}

			//else if (getAssetOutputDir) {
				//int input = GuiTextInputBox(Rectangle{ GetScreenWidth() / 4.0f, GetScreenHeight() / 4.0f, width, height }, "Where is the .exe file?", "text", "no", name, 8, &see);
		}

		DrawTexture(curTex, GetMouseX(), GetMouseY(), WHITE);
		ClearBackground(DARKBLUE);
		EndDrawing();
	}

	//printf(GetWorkingDirectory());
	printf("\nAll tasks have been completed... Goodbye!\n");
	return 0;
}
