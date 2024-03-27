#include "uColor.h"

// converts raylib color into this.

TechStorm::uColor::uColor(Color color) : uVec4i(m_convertToColor(color)) {
}

TechStorm::uColor::uColor(int r, int g, int b, int a) : uVec4i(r, g, b, a) {
}

// operator to turn this into a raylib compatible Color.

TechStorm::uColor::operator Color() const {
	return Color{ static_cast<unsigned char>(this->x), static_cast<unsigned char>(this->y), static_cast<unsigned char>(this->z), static_cast<unsigned char>(this->w) };
}

Vector4 TechStorm::uColor::m_convertToColor(Color& color) {
	return Vector4{ static_cast<float>(color.r), static_cast<float>(color.g), static_cast<float>(color.b), static_cast<float>(color.a) };
}
