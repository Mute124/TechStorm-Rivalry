#pragma once
#include "uVec4.h"

namespace TechStorm {
	// universal color.
	class uColor : public uVec4i {
	public:

		int& r() { return x; }
		int& g() { return y; }
		int& b() { return z; }
		int& a() { return w; }

		uColor() : uVec4i() {}
		// converts raylib color into this.
		uColor(Color color) : uVec4i(m_convertToColor(color)) {
		}

		uColor(int r, int g, int b, int a) : uVec4i(r, g, b, a) {
		}

		// operator to turn this into a raylib compatible Color.
		virtual operator Color() const {
			return Color{ static_cast<unsigned char>(this->x), static_cast<unsigned char>(this->y), static_cast<unsigned char>(this->z), static_cast<unsigned char>(this->w) };
		}
		// only the r, g, and b values get returned.
		virtual operator Vector3() const
		{
			return Vector3{ (float)x, (float)y, (float)z };
		}

	private:
		Vector4 m_convertToColor(Color& color) {
			return Vector4{ static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) };
		}
	};
}
