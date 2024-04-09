#pragma once
#include <raylib.h>
#include "../universalTypes/uVec2.h"

namespace TechStorm {
	class Cursor {
	public:
		static inline void enableCursor() {
			EnableCursor();
		}

		static inline void disableCursor() {
			DisableCursor();
		}
	};
}
