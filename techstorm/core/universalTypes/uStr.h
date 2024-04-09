#pragma once
#include <algorithm> // for using transform
#include <cctype> // for using toupper
#include <iostream>
#include <string>

namespace TechStorm {
	class uStr {
	protected:
		std::string mStr;

	public:

		uStr() {}

		uStr(std::string& other) : mStr(other) {}

		uStr(const char* const other) : mStr(other) {}

		uStr(uStr& other) : mStr(other.mStr) {}

		// Returns the string as a std::string
		virtual std::string& getStr() {
			return mStr;
		}

		// Returns the c_str()
		virtual const char* cstr() {
			return mStr.c_str();
		}

		// concatenates a std::string, returns a std::string
		virtual std::string strConcat(std::string other) {
			return mStr + other;
		}

		// concatenates a const char*, returns a std::string
		virtual std::string strConcat(const char* other) {
			return mStr + other;
		}

		// concatenates a char, returns a std::string
		virtual std::string strConcat(char other) {
			return mStr + other;
		}

		// concatenates a char, returns a std::string
		virtual std::string strConcat(char* other) {
			return mStr + other;
		}

		// concatenates a uStr, returns a std::string
		virtual std::string strConcat(uStr other) {
			return mStr + other.mStr;
		}

		// concatenates an int, returns a std::string
		virtual std::string strConcat(int other) {
			return mStr + std::to_string(other);
		}

		// concatenates a float, returns a std::string
		virtual std::string strConcat(float other) {
			return mStr + std::to_string(other);
		}

		// concatenates a double, returns a std::string
		virtual std::string strConcat(double other) {
			return mStr + std::to_string(other);
		}

		// concatenates a bool, returns a std::string
		virtual std::string strConcat(bool other) {
			if (other) {
				return mStr + "true";
			}
			else {
				return mStr + "false";
			}
		}

		// concatenates another uStr, returns a uStr
		virtual uStr concat(uStr other) {
			return uStr(mStr + other.mStr);
		}

		// concatenates a std::string, returns a uStr
		virtual uStr concat(std::string other) {
			return uStr(mStr + other);
		}

		// concatenates a const char*, returns a uStr
		virtual uStr concat(const char* other) {
			return uStr(mStr + other);
		}

		// concatenates a char, returns a uStr
		virtual uStr concat(char other) {
			return uStr(mStr + other);
		}

		// concatenates a char, returns a uStr
		virtual uStr concat(char* other) {
			return uStr(mStr + other);
		}

		// concatenates an int, returns a uStr
		virtual uStr concat(int other) {
			return uStr(mStr + std::to_string(other));
		}

		// concatenates a float, returns a uStr
		virtual uStr concat(float other) {
			return uStr(mStr + std::to_string(other));
		}

		// concatenates a double, returns a uStr
		virtual uStr concat(double other) {
			return uStr(mStr + std::to_string(other));
		}

		// concatenates a bool, returns a uStr
		virtual uStr concat(bool other) {
			if (other) {
				return uStr(mStr + "true");
			}
			else {
				return uStr(mStr + "false");
			}
		}

		// Returns the character at the specified index
		virtual char at(int index) {
			return mStr.at(index);
		}

		// Returns the characters between the specified start and end, if end is not specified, returns the characters from start to the end.
		// If start is not specified, returns the characters from the beginning to the end.
		// If start and end are not specified, returns the entire string.
		virtual std::string charsAt(int start, int end) {
			return mStr.substr(start, end - start);
		}

		// Checks if the uStr contains the specified uStr
		virtual bool contains(uStr other) {
			return mStr.find(other.mStr) != std::string::npos;
		}

		// Checks if the uStr contains the specified string
		virtual bool contains(std::string other) {
			return mStr.find(other) != std::string::npos;
		}

		// Checks if the uStr contains the specified string
		virtual bool contains(const char* other) {
			return mStr.find(other) != std::string::npos;
		}

		// Checks if the uStr contains the specified const char
		virtual bool contains(const char other) {
			return mStr.find(other) != std::string::npos;
		}

		// Checks if the uStr contains the specified char
		virtual bool contains(char other) {
			return mStr.find(other) != std::string::npos;
		}

		// Checks if the uStr contains the specified char*
		virtual bool contains(char* other) {
			return mStr.find(other) != std::string::npos;
		}

		// Checks if the uStr contains the specified int
		virtual bool contains(int other) {
			return mStr.find(std::to_string(other)) != std::string::npos;
		}

		// Checks if the uStr contains the specified float
		virtual bool contains(float other) {
			return mStr.find(std::to_string(other)) != std::string::npos;
		}

		// Checks if the uStr contains the specified double
		virtual bool contains(double other) {
			return mStr.find(std::to_string(other)) != std::string::npos;
		}

		// Checks if the uStr contains the specified bool
		virtual bool contains(bool other) {
			if (other) {
				return mStr.find("true") != std::string::npos;
			}
			else {
				return mStr.find("false") != std::string::npos;
			}
		}

		// Returns the length of the string
		virtual int length() {
			return mStr.length();
		}

		// Returns the size of the string
		virtual int64_t size() {
			return mStr.size();
		}

		// Returns the size of the string in memory
		virtual int64_t memorySize() {
			return sizeof(mStr);
		}

		// Clears the string
		virtual void clear() {
			mStr.clear();
		}

		// Clears the character at the specified index
		virtual void clearIndex(int index) {
			mStr.erase(mStr.begin() + index);
		}

		// Transforms this uStr to uppercase, returns a std::string
		virtual std::string toUpperStr() {
			return std::transform(mStr.begin(), mStr.end(), mStr.begin(),
				::toupper)._Ptr;
		}

		// Transforms the specified uStr to uppercase, returns a std::string
		virtual std::string toUpperStr(uStr other) {
			return std::transform(other.mStr.begin(), other.mStr.end(), other.mStr.begin(),
				::toupper)._Ptr;
		}

		// Transforms this uStr to uppercase, returns a uStr
		virtual uStr toUpper() {
			return std::transform(mStr.begin(), mStr.end(), mStr.begin(),
				::toupper)._Ptr;
		}

		// Transforms the specified uStr to uppercase, returns a uStr
		virtual uStr toUpper(uStr other) {
			return std::transform(other.mStr.begin(), other.mStr.end(), other.mStr.begin(),
				::toupper)._Ptr;
		}

		// Transforms this uStr to lowercase, returns a std::string
		virtual std::string toLowerStr() {
			return std::transform(mStr.begin(), mStr.end(), mStr.begin(),
				::tolower)._Ptr;
		}

		// Transforms the specified uStr to lowercase, returns a std::string
		virtual std::string toLowerStr(uStr other) {
			return std::transform(other.mStr.begin(), other.mStr.end(), other.mStr.begin(),
				::tolower)._Ptr;
		}

		// Transforms this uStr to lowercase, returns a uStr
		virtual uStr toLower() {
			return std::transform(mStr.begin(), mStr.end(), mStr.begin(),
				::tolower)._Ptr;
		}

		// Transforms the specified uStr to lowercase, returns a uStr
		virtual uStr toLower(uStr other) {
			return std::transform(other.mStr.begin(), other.mStr.end(), other.mStr.begin(),
				::tolower)._Ptr;
		}

		// Returns this as an int
		virtual operator int() {
			return std::stoi(mStr);
		}

		// Returns this as a float
		virtual operator float() {
			return std::stof(mStr);
		}

		// Returns this as a double
		virtual operator double() {
			return std::stod(mStr);
		}

		// Returns this as a bool
		virtual operator bool() {
			return mStr == "true";
		}

		// Returns this as a const char*
		virtual operator const char* () const {
			return mStr.c_str();
		}

		// Returns this as a std::string
		virtual operator std::string() {
			return mStr;
		}

		// Returns this as a uStr
		virtual operator uStr() {
			return uStr(mStr);
		}

		// Returns the first character of the string
		virtual operator char() {
			return mStr[0];
		}

		// Destructor
		~uStr() {
		}
	};
}
