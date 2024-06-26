#pragma once
#include <raylib.h>

namespace TechStorm {
	class Display {
	public:
		int winWidth = 800;
		int winHeight = 600;
		Vector2 screenMiddle;
		const char* wintitle = "Title not set!";
		bool isFullscreen = false;
		unsigned int flags;

		void initDisplay(int width, int height, const char* wintitle, unsigned int flags) {
			this->winWidth = width;
			this->winHeight = height;
			this->wintitle = wintitle;
			this->flags = flags;

			SetConfigFlags(flags);
			InitWindow(this->winWidth, this->winHeight, this->wintitle);

			this->screenMiddle = Vector2{
				(float)width / 2.0f,
				(float)height / 2.0f
			};
		}

		void setTitle(const char* wintitle) {
			this->wintitle = wintitle;
		}

		void setFullscreenStatus(bool status) {
			this->isFullscreen = status;
		}
	};
}
