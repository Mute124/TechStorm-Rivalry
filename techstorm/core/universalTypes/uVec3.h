#pragma once
#include <raylib.h>
#include <Jolt/Jolt.h>
#include <glm/glm.hpp>

namespace TechStorm {
	// Forward declaration
	template<typename T>
	class uVec3Base;
	// Overload subtraction operator for subtracting Jolt's Vector3 from uVec3Base
	template<typename T>
	uVec3Base<T> operator-(const uVec3Base<T>& lhs, const JPH::Vec3& rhs) {
		return uVec3Base<T>(lhs.x - static_cast<T>(rhs.GetX()), lhs.y - static_cast<T>(rhs.GetY()), lhs.z - static_cast<T>(rhs.GetZ()));
	}

	// Overload subtraction operator for subtracting Raylib's Vector3 from uVec3Base
	template<typename T>
	uVec3Base<T> operator-(const uVec3Base<T>& lhs, const Vector3& rhs) {
		return uVec3Base<T>(lhs.x - static_cast<T>(rhs.x), lhs.y - static_cast<T>(rhs.y), lhs.z - static_cast<T>(rhs.z));
	}

	// this is a base form, T will be the what type the x, y, and z will be. This is UNIVERSAL, meaning it works with raylib, glm, and Jolt.
	template<typename T>
	class uVec3Base abstract {
	public:
		// data
		T x;
		T y;
		T z;

		// constructors

		// No parameters provided so it will be set to zero.
		uVec3Base() :
			x((T)0),
			y((T)0),
			z((T)0) {}

		// Normal construction from values
		uVec3Base(T x, T y, T z) :
			x(x),
			y(y),
			z(z) {}

		// Construct from a Jolt Vector
		uVec3Base(JPH::Vec3& val) :
			x((T)val.GetX()),
			y((T)val.GetY()),
			z((T)val.GetZ()) {}

		uVec3Base(Vector3& val) :
			x((T)val.x),
			y((T)val.y),
			z((T)val.z) {
		}

		// functions

		// resets values
		static void zero() {
			uVec3Base();
		}
		// operators

		// Comparison Operators
		virtual bool operator==(const uVec3Base& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		// Math Operators

		// Conversion Operators
		virtual operator Vector3() const {
			return Vector3{ (float)this->x, (float)this->y, (float)this->z };
		}

		virtual operator JPH::Vec3() const {
			return JPH::Vec3(this->x, this->y, this->z);
		}

		// Conversion operator to glm::vec3
		virtual operator glm::vec3() const {
			return glm::vec3(x, y, z);
		}
	};

	class uVec3f;
	class uVec3d;

	class uVec3i : public uVec3Base<int> {
	public:
		uVec3i() : uVec3Base() {}
		uVec3i(double x, double y, double z) : uVec3Base(x, y, z) {}
		uVec3i(JPH::Vec3& val) : uVec3Base(val) {}
		uVec3i(Vector3& val) : uVec3Base(val) {}
	};

	class uVec3f : public uVec3Base<float> {
	public:

		uVec3f() : uVec3Base() {}
		uVec3f(float x, float y, float z) : uVec3Base(x, y, z) {}
		uVec3f(JPH::Vec3& val) : uVec3Base(val) {}
		uVec3f(Vector3& val) : uVec3Base(val) {}

		// Note : This only will TRUNCATE the vector, not round it!
		virtual operator uVec3i() const {
			return uVec3i((int)this->x, (int)this->y, (int)this->z);
		}
	};

	class uVec3d : public uVec3Base<double> {
	public:
		uVec3d() : uVec3Base() {}
		uVec3d(double x, double y, double z) : uVec3Base(x, y, z) {}
		uVec3d(JPH::Vec3& val) : uVec3Base(val) {}
		uVec3d(Vector3& val) : uVec3Base(val) {}

		// Note : This only will TRUNCATE the vector, not round it!
		virtual operator uVec3i() const {
			return uVec3i((int)this->x, (int)this->y, (int)this->z);
		}
	};
}
