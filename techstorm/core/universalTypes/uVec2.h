#pragma once
#include <raylib.h>
#include <Jolt/Jolt.h>
#include <glm/glm.hpp>

namespace TechStorm {

	// Forward declaration
	template<typename T>
	class uVec2;

	// Overload subtraction operator for subtracting Raylib's Vector3 from uVec2
	template<typename T>
	uVec2<T> operator-(const uVec2<T>& lhs, const Vector2& rhs) {
		return uVec2<T>(lhs.x - static_cast<T>(rhs.x), lhs.y - static_cast<T>(rhs.y));
	}

	// this is a base form, T will be the what type the x, y, and z will be. This is UNIVERSAL, meaning it works with raylib, glm, and Jolt.
	template<typename T>
	class uVec2 {
	public:

		T x, y;

		uVec2(T x, T y) : x(x), y(y) {
		}

		uVec2() : x(0), y(0) {
		}

		uVec2(const uVec2<T>& inV) : x(inV.x), y(inV.y) {
		}

		uVec2(glm::vec2 inV) : x(inV.x), y(inV.y) {}

		uVec2(Vector2& inV) : x(inV.x), y(inV.y) {}

		uVec2(const Vector2& inV) : x(inV.x), y(inV.y) {}

		uVec2(const T* inV) : x(inV[0]), y(inV[1]) {}

		uVec2(const T& inV) : x(inV), y(inV) {}

		// returns the sum of all values.
		virtual T sum() {
			return x + y;
		}

		// the multiplicative product of all values
		virtual T product() {
			return x * y;
		}

		// returns the length of the vector
		virtual T length() const {
			return sqrt(x * x + y * y);
		}

		// returns the squared length of the vector
		virtual T length_sq() const {
			return x * x + y * y;
		}

		// returns the dot product
		virtual T dot(const uVec2<T>& inV) const {
			return x * inV.x + y * inV.y;
		}

		// returns the distance
		virtual T dist(const uVec2<T>& inV) const {
			return (x - inV.x) * (x - inV.x) + (y - inV.y) * (y - inV.y);
		}

		// returns the squared distance
		virtual T dist_sq(const uVec2<T>& inV) const {
			return (x - inV.x) * (x - inV.x) + (y - inV.y) * (y - inV.y);
		}

		// Set the vector to a set value
		virtual void set(T inX, T inY) {
			x = inX;
			y = inY;
		}

		// set the vector to a set value
		virtual void set(T inV) {
			this->set(inV, inV);
		}

		// set the vector to a set vector
		virtual void set(const uVec2<T>& inV) {
			this->set(inV.x, inV.y);
		}

		// Sets the vector to the result of a single value function.
		virtual void set(std::function<T()> inF) {
			const T result = inF();
			this->set(result, result);
		}

		// sets the value of this vector by the result of a 3 dimensional function
		virtual void set(std::function<uVec2<T>()> inF) {
			this->set(inF());
		}

		// Change the vector by a vector
		virtual void changeBy(const uVec2<T>& inV) {
			x += inV.x;
			y += inV.y;
		}

		// change the vector by 3 set values
		virtual void changeBy(T inX, T inY) {
			x = inX;
			y = inY;
		}

		// Changes the value of this vector by the result of a single value function.
		virtual void changeBy(std::function<T()> inF) {
			const T result = inF();
			this->changeBy(result, result);
		}

		// Changes the value of this vector by the result of a 3 dimensional function.
		virtual void changeBy(std::function < uVec2<T>()> inF) {
			this->changeBy(inF());
		}

		// returns the rounded vector
		virtual uVec2<T> round() const {
			return uVec2<T>(std::round(x), std::round(y));
		}

		// returns the floor
		virtual uVec2<T> floor() const {
			return uVec2<T>(std::floor(x), std::floor(y));
		}

		// returns the ceiling
		virtual uVec2<T> ceil() const {
			return uVec2<T>(std::ceil(x), std::ceil(y));
		}

		// returns the absolute value of the vector
		virtual uVec2<T> abs() const {
			return uVec2<T>(std::abs(x), std::abs(y));
		}

		// returns the max of the vector
		virtual uVec2<T> max(const uVec2<T>& inV) const {
			return uVec2<T>(std::max(x, inV.x), std::max(y, inV.y));
		}

		// returns the min of the vector
		virtual uVec2<T> min(const uVec2<T>& inV) const {
			return uVec2<T>(std::min(x, inV.x), std::min(y, inV.y));
		}

		// returns a negated (inverted) vector
		virtual uVec2<T> negate() const {
			return uVec2<T>(-x, -y);
		}

		// returns a normalized vector in a scale
		virtual uVec2<T> normalize(T inScale) const {
			return uVec2<T>(x / inScale, y / inScale);
		}

		// returns the normalized vector
		virtual uVec2<T> normalize() const {
			return normalize(length());
		}

		// returns the interpolation of the vector
		virtual uVec2<T> lerp(const uVec2<T>& inV, T inT) const {
			return uVec2<T>(x + (inV.x - x) * inT, y + (inV.y - y) * inT);
		}

		// returns a float version of the vector, aka floatify
		virtual uVec2<float> floatify() const {
			return uVec2<float>(static_cast<float>(x), static_cast<float>(y));
		}

		// Clamps the vector
		virtual uVec2<T> clamp(const uVec2<T>& inMin, const uVec2<T>& inMax) {
			return uVec2<T>(std::clamp(x, inMin.x, inMax.x), std::clamp(y, inMin.y, inMax.y));
		}

		// Adds this vector to another
		virtual uVec2<T> add(const uVec2<T>& inV) {
			return uVec2<T>(x + inV.x, y + inV.y);
		}

		// Adds this vector with a single value
		virtual uVec2<T> add(const T& inV) {
			return uVec2<T>(x + inV, y + inV);
		}

		// Subtracts this vector from another
		virtual uVec2<T> subtract(const uVec2<T>& inV) {
			return uVec2<T>(x - inV.x, y - inV.y);
		}

		// Subtracts this vector from a single value
		virtual uVec2<T> subtract(const T& inV) {
			return uVec2<T>(x - inV, y - inV);
		}

		// Multiplies this vector by another
		virtual uVec2<T> multiply(const uVec2<T>& inV) {
			return uVec2<T>(x * inV.x, y * inV.y);
		}

		// Multiplies this vector by a single value
		virtual uVec2<T> multiply(const T& inV) {
			return uVec2<T>(x * inV, y * inV);
		}

		// Divides this vector by another
		virtual uVec2<T> divide(const uVec2<T>& inV) {
			return uVec2<T>(x / inV.x, y / inV.y);
		}

		// Divides this vector by a single value
		virtual uVec2<T> divide(const T& inV) {
			return uVec2<T>(x / inV, y / inV);
		}

		// Transforms this vector
		virtual uVec2<T> transform(const uVec2<T>& inV) {
			return uVec2<T>(x * inV.x, y * inV.y);
		}

		// Transforms this vector by a single value
		virtual uVec2<T> transform(const T& inV) {
			return uVec2<T>(x * inV, y * inV);
		}

		// Gets the distance between two float vectors
		static float Distf(const uVec2<float>& inV1, const uVec2<float>& inV2) {
			return sqrt((inV1.x - inV2.x) * (inV1.x - inV2.x) + (inV1.y - inV2.y) * (inV1.y - inV2.y));
		}

		// Gets the angle between two float vectors
		static float Anglef(const uVec2<float>& inV1, const uVec2<float>& inV2) {
			return glm::degrees(acos(inV1.dot(inV2) / (inV1.length() * inV2.length())));
		}

		// Gets the angle between two double vectors
		static double Angled(const uVec2<double>& inV1, const uVec2<double>& inV2) {
			return glm::degrees(acos(inV1.dot(inV2) / (inV1.length() * inV2.length())));
		}

		// Zeros out the vector
		static uVec2<T> Zero() {
			return uVec2<T>(0, 0);
		}

		// Ones out the vector
		static uVec2<T> One() {
			return uVec2<T>(1, 1);
		}

		virtual uVec2<T>& operator=(const uVec2<T>& inV) {
			x = inV.x;
			y = inV.y;
			return *this;
		}

		virtual uVec2<T>& operator+=(const uVec2<T>& inV) {
			x += inV.x;
			y += inV.y;
			return *this;
		}

		virtual uVec2<T>& operator-=(const uVec2<T>& inV) {
			x -= inV.x;
			y -= inV.y;

			return *this;
		}

		virtual bool operator==(const uVec2<T>& inV) const {
			return x == inV.x && y == inV.y;
		}

		virtual bool operator!=(const uVec2<T>& inV) const {
			return x != inV.x || y != inV.y;
		}

		virtual uVec2<T> operator+(const uVec2<T>& inV) const {
			return uVec2<T>(x + inV.x, y + inV.y);
		}

		virtual uVec2<T> operator-(const uVec2<T>& inV) const {
			return uVec2<T>(x - inV.x, y - inV.y);
		}

		virtual operator glm::vec2() const {
			return glm::vec2(x, y);
		}

		virtual operator Vector2() const {
			return Vector2{ (float)x, (float)y };
		}

		operator uVec2<double>() const {
			return uVec2<double>(x, y);
		}
		operator uVec2<float>() const {
			return uVec2<float>(x, y);
		}
		operator uVec2<int>() const {
			return uVec2<int>(x, y);
		}
	};

	class uVec2f;
	class uVec2d;

	class uVec2i : public uVec2<int> {
	public:
		uVec2i(const int& inV) : uVec2<int>(inV, inV) {}

		uVec2i() = default;

		uVec2i(const int& inX, const int& inY) : uVec2<int>(inX, inY) {}

		uVec2i(const uVec2i& inV) : uVec2<int>(inV) {}
	};

	class uVec2f : public uVec2<float> {
	public:

		uVec2f(const uVec2f& inV) : uVec2<float>(inV) {}

		uVec2f(const float& inV) : uVec2<float>(inV, inV) {}

		uVec2f() = default;

		uVec2f(const float& inX, const float& inY) : uVec2<float>(inX, inY) {}

		uVec2f(const glm::vec2& inV) : uVec2<float>(inV) {}

		uVec2f(const Vector2& inV) : uVec2<float>(inV) {}

		// Note : This only will TRUNCATE the vector, not round it!
		virtual operator uVec2i() const {
			return uVec2i((int)this->x, (int)this->y);
		}
	};

	class uVec2d : public uVec2<double> {
	public:
		uVec2d(const uVec2d& inV) : uVec2<double>(inV) {}

		uVec2d(const float& inV) : uVec2<double>(inV, inV) {}

		uVec2d() = default;

		uVec2d(const double& inX, const double& inY) : uVec2<double>(inX, inY) {}

		uVec2d(const glm::vec2& inV) : uVec2<double>(inV) {}

		// Note : This only will TRUNCATE the vector, not round it!
		virtual operator uVec2i() const {
			return uVec2i((int)this->x, (int)this->y);
		}
	};
}
