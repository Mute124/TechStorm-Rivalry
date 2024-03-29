#pragma once
#include <raylib.h>
#include <glm/glm.hpp>

namespace TechStorm {

	// Forward declaration
	template<typename T>
	class uVec2Base;

	// Overload subtraction operator for subtracting Raylib's Vector3 from uVec3Base
	template<typename T>
	uVec2Base<T> operator-(const uVec2Base<T>& lhs, const Vector2& rhs) {
		return uVec2Base<T>(lhs.x - static_cast<T>(rhs.x), lhs.y - static_cast<T>(rhs.y));
	}

	// this is a base form, T will be the what type the x, y, and z will be. This is UNIVERSAL, meaning it works with raylib and glm.
	template<typename T>
	class uVec2Base abstract {
	public:

		// data
		T x;
		T y;

		// constructors

		// No parameters provided so it will be set to zero.
		uVec2Base() :
			x((T)0),
			y((T)0)
		{}

		// Normal construction from values
		uVec2Base(T x, T y) :
			x(x),
			y(y) {}

		uVec2Base(Vector2& val) :
			x((T)val.x),
			y((T)val.y) {
		}

		// functions

		// operators

		// Comparison Operators
		virtual bool operator==(const uVec2Base& other) const
		{
			return x == other.x && y == other.y;
		}

		// Math Operators

		// Conversion Operators
		virtual operator Vector2() const {
			return Vector2{ (float)this->x, (float)this->y };
		}

		// Conversion operator to glm::vec3
		virtual operator glm::vec2() const {
			return glm::vec2(x, y);
		}
	};

	class uVec2f;
	class uVec2d;

	class uVec2i : public uVec2Base<int> {
	public:
		uVec2i() : uVec2Base() {}
		uVec2i(int x, int y) : uVec2Base(x, y) {}
		uVec2i(Vector2& val) : uVec2Base(val) {}
	};

	class uVec2f : public uVec2Base<float> {
	public:

		uVec2f() : uVec2Base() {}
		uVec2f(float x, float y) : uVec2Base(x, y) {}
		uVec2f(Vector2& val) : uVec2Base(val) {}
		uVec2f(Vector2 val) : uVec2Base(val) {}

		// Note : This only will TRUNCATE the vector, not round it!
		virtual operator uVec2i() const {
			return uVec2i((int)this->x, (int)this->y);
		}
	};

	class uVec2d : public uVec2Base<double> {
	public:
		uVec2d() : uVec2Base() {}
		uVec2d(double x, double y) : uVec2Base(x, y) {}

		uVec2d(Vector2& val) : uVec2Base(val) {}

		// Note : This only will TRUNCATE the vector, not round it!
		virtual operator uVec2i() const {
			return uVec2i((int)this->x, (int)this->y);
		}
	};
}
