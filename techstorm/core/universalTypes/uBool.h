#pragma once
#include <string>
#include <functional>

namespace TechStorm {

	// This is a boolean that is universal, meaning it works with raylib, glm, and Jolt. Also provides a bunch of handy utilities. Dont use if memory is an issue as this takes more than a byte (this takes around 16!).
	class uBool {
	private:
		bool value = false;
	public:
		uBool(const uBool& inV);

		uBool(bool inV);

		uBool(const char* inV);

		uBool(char inV);

		uBool(std::string inV);

		uBool(const std::string& inV);

		// constructor that converts an int to a bool.
		uBool(int inV);

		uBool();

		virtual std::string asString() const;

		virtual const char* asCString() const;

		virtual int asInt() const;

		virtual const char* asIntCStr() const;

		virtual char asChar() const;

		virtual std::string asIntStr() const;

		virtual bool getValue() const;

		virtual bool* getValuePtr();

		// sets the value
		virtual void setValue(bool& inV);

		// sets the value
		virtual void setValue(bool inV);

		// sets the value
		virtual void setValue(const bool& inV);

		// switches the value, true -> false, false -> true
		virtual void switchValue();

		// returns true if the value is true
		virtual bool isTrue() const;

		virtual bool isFalse() const;

		virtual void doIfTrue(const std::function<void()>& inV);

		virtual void doIfFalse(const std::function<void()>& inV);

		virtual uBool& operator=(const uBool& inV);

		virtual operator bool();

		virtual operator bool() const;

		virtual operator int();

		virtual operator int() const;

		virtual operator std::string();

		virtual operator std::string() const;

		virtual operator const char* ();

		virtual operator const char* () const;

		virtual operator char();

		virtual operator char() const;
	};
}
