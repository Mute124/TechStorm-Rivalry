#pragma once
#include <raylib.h>
#include <Jolt/Jolt.h>
#include <glm/glm.hpp>

namespace TechStorm {

	// Forward declaration
	template<typename T>
	class uVec4Base;

	// Overload subtraction operator for subtracting Jolt's Vector3 from uVec3Base
	template<typename T>
	uVec4Base<T> operator-(const uVec4Base<T>& lhs, const JPH::Vec4& rhs) {
		return uVec4Base<T>(lhs.x - static_cast<T>(rhs.GetX()), lhs.y - static_cast<T>(rhs.GetY()), lhs.z - static_cast<T>(rhs.GetZ()), lhs.w - static_cast<T>(rhs.GetW()));
	}

	// Overload subtraction operator for subtracting Raylib's Vector3 from uVec3Base
	template<typename T>
	uVec4Base<T> operator-(const uVec4Base<T>& lhs, const Vector4& rhs) {
		return uVec4Base<T>(lhs.x - static_cast<T>(rhs.x), lhs.y - static_cast<T>(rhs.y), lhs.z - static_cast<T>(rhs.z), lhs.w - static_cast<T>(rhs.w));
	}

	// this is a base form, T will be the what type the x, y, and z will be. This is UNIVERSAL, meaning it works with raylib, glm, and Jolt.
	template<typename T>
	class uVec4Base abstract {
	public:

		// data
		T x;
		T y;
		T z;
		T w;

		// constructors

		// No parameters provided so it will be set to zero.
		uVec4Base() :
			x((T)0),
			y((T)0),
			z((T)0),
			w((T)0) {}

		// Normal construction from values
		uVec4Base(T x, T y, T z, T w) :
			x(x),
			y(y),
			z(z),
			w(w)
		{}

		// Construct from a Jolt Vector
		uVec4Base(JPH::Vec4& val) :
			x((T)val.GetX()),
			y((T)val.GetY()),
			z((T)val.GetZ()),
			w((T)val.GetW())
		{}

		uVec4Base(Vector4& val) :
			x((T)val.x),
			y((T)val.y),
			z((T)val.z),
			w((T)val.w)
		{
		}

		// functions

		// operators

		// Comparison Operators
		virtual bool operator==(const uVec4Base& other) const
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		// Math Operators

		// Subtraction operator for uVec3Base
		uVec4Base operator-(const uVec4Base& rhs) const {
			return uVec4Base(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		}

		// Degrade operator
		uVec4Base operator--() const {
			return uVec4Base(x--, y--, z--, w--);
		}

		// Conversion Operators
		virtual operator Vector4() const {
			return Vector4{ (float)this->x, (float)this->y, (float)this->z, (float)this->w };
		}

		virtual operator JPH::Vec4() const {
			return JPH::Vec4(this->x, this->y, this->z, this->w);
		}

		// Conversion operator to glm::vec3
		virtual operator glm::vec4() const {
			return glm::vec4(this->x, this->y, this->z, this->w);
		}
	};

	class uVec4f;
	class uVec4d;

	class uVec4i : public uVec4Base<int> {
	public:
		uVec4i() : uVec4Base() {}
		uVec4i(int x, int y, int z, int w) : uVec4Base(x, y, z, w) {}
		uVec4i(JPH::Vec4& val) : uVec4Base(val) {}
		uVec4i(Vector4 val) : uVec4Base(val) {}
	};

	class uVec4f : public uVec4Base<float> {
	public:

		uVec4f() : uVec4Base() {}
		uVec4f(float x, float y, float z, float w) : uVec4Base(x, y, z, w) {}
		uVec4f(JPH::Vec4& val) : uVec4Base(val) {}
		uVec4f(Vector4& val) : uVec4Base(val) {}

		// Note : This only will TRUNCATE the vector, not round it!
		virtual operator uVec4i() const {
			return uVec4i((int)this->x, (int)this->y, (int)this->z, (int)this->w);
		}
	};

	class uVec4d : public uVec4Base<double> {
	public:
		uVec4d() : uVec4Base() {}
		uVec4d(double x, double y, double z, double w) : uVec4Base(x, y, z, w) {}
		uVec4d(JPH::Vec4& val) : uVec4Base(val) {}
		uVec4d(Vector4& val) : uVec4Base(val) {}

		// Note : This only will TRUNCATE the vector, not round it!
		virtual operator uVec4i() const {
			return uVec4i((int)this->x, (int)this->y, (int)this->z, (int)this->w);
		}
	};
}
