#include <raylib.h>
#include <memory>
#include "../utils/Task.h"
export module Debug;

// draws a new error box
export void DrawError(int code) {
	// rises up from the bottom right corner, with a red background, black outline, the error code, and then goes back down
	DrawRectangle(500, 500, 100, 100, RED);
	DrawRectangleLines(500, 500, 100, 100, BLACK);
	DrawText("ERROR: " + code, 100, 100, 20, WHITE);
}
