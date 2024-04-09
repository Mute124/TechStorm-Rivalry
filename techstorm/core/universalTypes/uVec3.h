#pragma once
#include <raylib.h>
#include <Jolt/Jolt.h>
#include <glm/glm.hpp>

namespace TechStorm {

	// Forward declaration
	template<typename T>
	class uVec3;

	// Overload subtraction operator for subtracting Jolt's Vector3 from uVec3
	template<typename T>
	uVec3<T> operator-(const uVec3<T>& lhs, const JPH::Vec3& rhs) {
		return uVec3<T>(lhs.x - static_cast<T>(rhs.GetX()), lhs.y - static_cast<T>(rhs.GetY()), lhs.z - static_cast<T>(rhs.GetZ()));
	}

	// Overload subtraction operator for subtracting Raylib's Vector3 from uVec3
	template<typename T>
	uVec3<T> operator-(const uVec3<T>& lhs, const Vector3& rhs) {
		return uVec3<T>(lhs.x - static_cast<T>(rhs.x), lhs.y - static_cast<T>(rhs.y), lhs.z - static_cast<T>(rhs.z));
	}

	// this is a base form, T will be the what type the x, y, and z will be. This is UNIVERSAL, meaning it works with raylib, glm, and Jolt.
	template<typename T>
	class uVec3 {
	public:

		T x, y, z;

		uVec3(T x, T y, T z) : x(x), y(y), z(z) {
		}

		uVec3() : x(0), y(0), z(0) {
		}

		uVec3(const uVec3<T>& inV) : x(inV.x), y(inV.y), z(inV.z) {
		}

		uVec3(glm::vec3 inV) : x(inV.x), y(inV.y), z(inV.z) {}

		uVec3(JPH::Vec3 inV) : x(inV.GetX()), y(inV.GetY()), z(inV.GetZ()) {}

		uVec3(Vector3& inV) : x(inV.x), y(inV.y), z(inV.z) {}

		uVec3(const Vector3& inV) : x(inV.x), y(inV.y), z(inV.z) {}

		uVec3(const T* inV) : x(inV[0]), y(inV[1]), z(inV[2]) {}

		uVec3(const T& inV) : x(inV), y(inV), z(inV) {}

		// returns the sum of all values.
		virtual T sum() {
			return x + y + z;
		}

		// the multiplicative product of all values
		virtual T product() {
			return x * y * z;
		}

		// returns the length of the vector
		virtual T length() const {
			return sqrt(x * x + y * y + z * z);
		}

		// returns the squared length of the vector
		virtual T length_sq() const {
			return x * x + y * y + z * z;
		}

		// returns the dot product
		virtual T dot(const uVec3<T>& inV) const {
			return x * inV.x + y * inV.y + z * inV.z;
		}

		// returns the distance
		virtual T dist(const uVec3<T>& inV) const {
			return (x - inV.x) * (x - inV.x) + (y - inV.y) * (y - inV.y) + (z - inV.z) * (z - inV.z);
		}

		// returns the squared distance
		virtual T dist_sq(const uVec3<T>& inV) const {
			return (x - inV.x) * (x - inV.x) + (y - inV.y) * (y - inV.y) + (z - inV.z) * (z - inV.z);
		}

		// Set the vector to a set value
		virtual void set(T inX, T inY, T inZ) {
			x = inX;
			y = inY;
			z = inZ;
		}

		// set the vector to a set value
		virtual void set(T inV) {
			this->set(inV, inV, inV);
		}

		// set the vector to a set vector
		virtual void set(const uVec3<T>& inV) {
			this->set(inV.x, inV.y, inV.z);
		}

		// Sets the vector to the result of a single value function.
		virtual void set(std::function<T()> inF) {
			const T result = inF();
			this->set(result, result, result);
		}

		// sets the value of this vector by the result of a 3 dimensional function
		virtual void set(std::function<uVec3<T>()> inF) {
			this->set(inF());
		}

		// Change the vector by a vector
		virtual void changeBy(const uVec3<T>& inV) {
			x += inV.x;
			y += inV.y;
			z += inV.z;
		}

		// change the vector by 3 set values
		virtual void changeBy(T inX, T inY, T inZ) {
			x = inX;
			y = inY;
			z = inZ;
		}

		// Changes the value of this vector by the result of a single value function.
		virtual void changeBy(std::function<T()> inF) {
			const T result = inF();
			this->changeBy(result, result, result);
		}

		// Changes the value of this vector by the result of a 3 dimensional function.
		virtual void changeBy(std::function < uVec3<T>()> inF) {
			this->changeBy(inF());
		}

		// returns the rounded vector
		virtual uVec3<T> round() const {
			return uVec3<T>(std::round(x), std::round(y), std::round(z));
		}

		// returns the floor
		virtual uVec3<T> floor() const {
			return uVec3<T>(std::floor(x), std::floor(y), std::floor(z));
		}

		// returns the ceiling
		virtual uVec3<T> ceil() const {
			return uVec3<T>(std::ceil(x), std::ceil(y), std::ceil(z));
		}

		// returns the absolute value of the vector
		virtual uVec3<T> abs() const {
			return uVec3<T>(std::abs(x), std::abs(y), std::abs(z));
		}

		// returns the max of the vector
		virtual uVec3<T> max(const uVec3<T>& inV) const {
			return uVec3<T>(std::max(x, inV.x), std::max(y, inV.y), std::max(z, inV.z));
		}

		// returns the min of the vector
		virtual uVec3<T> min(const uVec3<T>& inV) const {
			return uVec3<T>(std::min(x, inV.x), std::min(y, inV.y), std::min(z, inV.z));
		}

		// returns a negated (inverted) vector
		virtual uVec3<T> negate() const {
			return uVec3<T>(-x, -y, -z);
		}

		// returns a normalized vector in a scale
		virtual uVec3<T> normalize(T inScale) const {
			return uVec3<T>(x / inScale, y / inScale, z / inScale);
		}

		// returns the normalized vector
		virtual uVec3<T> normalize() const {
			return normalize(length());
		}

		// returns the cross product of the vector
		virtual uVec3<T> cross(const uVec3<T>& inV) const {
			return uVec3<T>(y * inV.z - z * inV.y, z * inV.x - x * inV.z, x * inV.y - y * inV.x);
		}

		// returns the interpolation of the vector
		virtual uVec3<T> lerp(const uVec3<T>& inV, T inT) const {
			return uVec3<T>(x + (inV.x - x) * inT, y + (inV.y - y) * inT, z + (inV.z - z) * inT);
		}

		// returns a float version of the vector, aka floatify
		virtual uVec3<float> floatify() const {
			return uVec3<float>(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
		}

		// Clamps the vector
		virtual uVec3<T> clamp(const uVec3<T>& inMin, const uVec3<T>& inMax) {
			return uVec3<T>(std::clamp(x, inMin.x, inMax.x), std::clamp(y, inMin.y, inMax.y), std::clamp(z, inMin.z, inMax.z));
		}

		// Adds this vector to another
		virtual uVec3<T> add(const uVec3<T>& inV) {
			return uVec3<T>(x + inV.x, y + inV.y, z + inV.z);
		}

		// Adds this vector with a single value
		virtual uVec3<T> add(const T& inV) {
			return uVec3<T>(x + inV, y + inV, z + inV);
		}

		// Subtracts this vector from another
		virtual uVec3<T> subtract(const uVec3<T>& inV) {
			return uVec3<T>(x - inV.x, y - inV.y, z - inV.z);
		}

		// Subtracts this vector from a single value
		virtual uVec3<T> subtract(const T& inV) {
			return uVec3<T>(x - inV, y - inV, z - inV);
		}

		// Multiplies this vector by another
		virtual uVec3<T> multiply(const uVec3<T>& inV) {
			return uVec3<T>(x * inV.x, y * inV.y, z * inV.z);
		}

		// Multiplies this vector by a single value
		virtual uVec3<T> multiply(const T& inV) {
			return uVec3<T>(x * inV, y * inV, z * inV);
		}

		// Divides this vector by another
		virtual uVec3<T> divide(const uVec3<T>& inV) {
			return uVec3<T>(x / inV.x, y / inV.y, z / inV.z);
		}

		// Divides this vector by a single value
		virtual uVec3<T> divide(const T& inV) {
			return uVec3<T>(x / inV, y / inV, z / inV);
		}

		// Transforms this vector
		virtual uVec3<T> transform(const uVec3<T>& inV) {
			return uVec3<T>(x * inV.x, y * inV.y, z * inV.z);
		}

		// Transforms this vector by a single value
		virtual uVec3<T> transform(const T& inV) {
			return uVec3<T>(x * inV, y * inV, z * inV);
		}

		// Gets the distance between two float vectors
		static float Distf(const uVec3<float>& inV1, const uVec3<float>& inV2) {
			return sqrt((inV1.x - inV2.x) * (inV1.x - inV2.x) + (inV1.y - inV2.y) * (inV1.y - inV2.y) + (inV1.z - inV2.z) * (inV1.z - inV2.z));
		}

		// Gets the angle between two float vectors
		static float Anglef(const uVec3<float>& inV1, const uVec3<float>& inV2) {
			return glm::degrees(acos(inV1.dot(inV2) / (inV1.length() * inV2.length())));
		}

		// Gets the angle between two double vectors
		static double Angled(const uVec3<double>& inV1, const uVec3<double>& inV2) {
			return glm::degrees(acos(inV1.dot(inV2) / (inV1.length() * inV2.length())));
		}

		// Zeros out the vector
		static uVec3<T> Zero() {
			return uVec3<T>(0, 0, 0);
		}

		// Ones out the vector
		static uVec3<T> One() {
			return uVec3<T>(1, 1, 1);
		}

		virtual uVec3<T>& operator=(const uVec3<T>& inV) {
			x = inV.x;
			y = inV.y;
			z = inV.z;
			return *this;
		}

		virtual uVec3<T>& operator+=(const uVec3<T>& inV) {
			x += inV.x;
			y += inV.y;
			z += inV.z;
			return *this;
		}

		virtual uVec3<T>& operator-=(const uVec3<T>& inV) {
			x -= inV.x;
			y -= inV.y;
			z -= inV.z;
			return *this;
		}

		virtual bool operator==(const uVec3<T>& inV) const {
			return x == inV.x && y == inV.y && z == inV.z;
		}

		virtual bool operator!=(const uVec3<T>& inV) const {
			return x != inV.x || y != inV.y || z != inV.z;
		}

		virtual uVec3<T> operator+(const uVec3<T>& inV) const {
			return uVec3<T>(x + inV.x, y + inV.y, z + inV.z);
		}

		virtual uVec3<T> operator-(const uVec3<T>& inV) const {
			return uVec3<T>(x - inV.x, y - inV.y, z - inV.z);
		}

		virtual operator glm::vec3() const {
			return glm::vec3(x, y, z);
		}

		virtual operator JPH::Vec3() const {
			return JPH::Vec3(x, y, z);
		}

		virtual operator Vector3() const {
			return Vector3{ (float)x, (float)y, (float)z };
		}

		operator uVec3<double>() const {
			return uVec3<double>(x, y, z);
		}
		operator uVec3<float>() const {
			return uVec3<float>(x, y, z);
		}
		operator uVec3<int>() const {
			return uVec3<int>(x, y, z);
		}
	};

	class uVec3f;
	class uVec3d;

	class uVec3i : public uVec3<int> {
	public:
		uVec3i(const int& inV) : uVec3<int>(inV, inV, inV) {}

		uVec3i() = default;

		uVec3i(const int& inX, const int& inY, const int& inZ) : uVec3<int>(inX, inY, inZ) {}

		uVec3i(const uVec3i& inV) : uVec3<int>(inV) {}
	};

	class uVec3f : public uVec3<float> {
	public:

		uVec3f(const uVec3f& inV) : uVec3<float>(inV) {}

		uVec3f(const float& inV) : uVec3<float>(inV, inV, inV) {}

		uVec3f() = default;

		uVec3f(const float& inX, const float& inY, const float& inZ) : uVec3<float>(inX, inY, inZ) {}

		uVec3f(const JPH::Vec3& inV) : uVec3<float>(inV) {}

		uVec3f(const glm::vec3& inV) : uVec3<float>(inV) {}

		uVec3f(const Vector3& inV) : uVec3<float>(inV) {}

		// Note : This only will TRUNCATE the vector, not round it!
		virtual operator uVec3i() const {
			return uVec3i((int)this->x, (int)this->y, (int)this->z);
		}
	};

	class uVec3d : public uVec3<double> {
	public:
		uVec3d(const uVec3d& inV) : uVec3<double>(inV) {}

		uVec3d(const float& inV) : uVec3<double>(inV, inV, inV) {}

		uVec3d() = default;

		uVec3d(const double& inX, const double& inY, const double& inZ) : uVec3<double>(inX, inY, inZ) {}

		uVec3d(const JPH::Vec3& inV) : uVec3<double>(inV) {}

		uVec3d(const glm::vec3& inV) : uVec3<double>(inV) {}

		// Note : This only will TRUNCATE the vector, not round it!
		virtual operator uVec3i() const {
			return uVec3i((int)this->x, (int)this->y, (int)this->z);
		}
	};
}
