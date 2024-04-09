#include "uBool.h"

inline TechStorm::uBool::uBool(const uBool& inV) : value(inV.value) {}

inline TechStorm::uBool::uBool(bool inV) : value(inV) {}

inline TechStorm::uBool::uBool(const char* inV) : value(strcmp(inV, "true") == 0) {}

inline TechStorm::uBool::uBool(char inV) : value(inV == '1') {}

inline TechStorm::uBool::uBool(std::string inV) : value(inV == "true") {}

inline TechStorm::uBool::uBool(const std::string& inV) : value(inV == "true") {}


// constructor that converts an int to a bool.

inline TechStorm::uBool::uBool(int inV) : value(inV == 1) {}

inline TechStorm::uBool::uBool() : value(false) {}

inline std::string TechStorm::uBool::asString() const {
	return value ? "true" : "false";
}

inline const char* TechStorm::uBool::asCString() const {
	return value ? "true" : "false";
}

inline int TechStorm::uBool::asInt() const {
	if (value) {
		return 1;
	}
	else {
		return 0;
	}
}

inline const char* TechStorm::uBool::asIntCStr() const {
	if (value) {
		return "1";
	}
	else {
		return "0";
	}
}

inline char TechStorm::uBool::asChar() const {
	if (value) {
		return '1';
	}
	else {
		return '0';
	}
}

inline std::string TechStorm::uBool::asIntStr() const {
	if (value) {
		return "1";
	}
	else {
		return "0";
	}
}

inline bool TechStorm::uBool::getValue() const {
	return value;
}

inline bool* TechStorm::uBool::getValuePtr() {
	return &value;
}

// switches the value, true -> false, false -> true


// sets the value

inline void TechStorm::uBool::setValue(bool inV) {
	value = inV;
}

// sets the value

inline void TechStorm::uBool::setValue(const bool& inV) {
	value = inV;
}

inline void TechStorm::uBool::switchValue() {
	value = !value;
}

// returns true if the value is true

inline bool TechStorm::uBool::isTrue() const {
	return value == true;
}

inline bool TechStorm::uBool::isFalse() const {
	return value == false;
}

inline void TechStorm::uBool::doIfTrue(const std::function<void()>& inV) {
	if (isTrue())
	{
		inV();
	}
}

inline void TechStorm::uBool::doIfFalse(const std::function<void()>& inV) {
	if (isFalse()) {
		inV();
	}
}

inline uBool& TechStorm::uBool::operator=(const uBool& inV) {
	value = inV.value;
}

inline TechStorm::uBool::operator bool() {
	return value;
}

inline TechStorm::uBool::operator bool() const {
	return value;
}

inline TechStorm::uBool::operator int() {
	return value;
}

inline TechStorm::uBool::operator int() const {
	return value;
}

inline TechStorm::uBool::operator std::string() {
	return asString();
}

inline TechStorm::uBool::operator std::string() const {
	return asString();
}

inline TechStorm::uBool::operator const char* () {
	return asCString();
}

inline TechStorm::uBool::operator const char* () const {
	return asCString();
}

inline TechStorm::uBool::operator char() {
	return asChar();
}

inline TechStorm::uBool::operator char() const {
	return asChar();
}

// sets the value

inline void TechStorm::uBool::setValue(bool& inV) {
	value = inV;
}
