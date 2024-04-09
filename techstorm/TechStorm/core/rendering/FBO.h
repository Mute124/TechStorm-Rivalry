#pragma once
#include <raylib.h>
#include "../factories/Factory.h"

namespace TechStorm {
	class FBO : virtual Factory<RenderTexture> {
	public:

		FBO* getFBO() {
			return this;
		}
	};
}
