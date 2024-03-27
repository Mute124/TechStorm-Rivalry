#pragma once
#include "uVec4.h"

namespace TechStorm {
	// universal color
	class uColor : public uVec4i {
	public:

		// converts raylib color into this.
		uColor(Color color);

		uColor(int r, int g, int b, int a);

		// operator to turn this into a raylib compatible Color.
		virtual operator Color() const;

	private:
		Vector4 m_convertToColor(Color& color);
	};
}
