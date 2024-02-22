#pragma once
#include <string>

// converts different TOML types.
//Note: THIS IS ONLY FOR TOML! NOT XML OR ANYTHING ELSE.
class ConfigTypeConverter {
public:

	static int charToInt(const char* value) {
		return textToInteger(value);
	}

	static int textToInteger(const char* value) {
		return atoi(value);
	}

	// converts string into C readable const char *, then passes it to a function.
	static int strToInt(std::string* value) {
		if (value->c_str() == "true") {
			return 1;
		}
		else if (value->c_str() == "false") {
			return 0;
		}
		else {
			const char* charconversion = value->c_str();

			return textToInteger(charconversion);
		}
	}

	// converts string to a boolean
	static bool strToBool(std::string* value) {
		if (value->c_str() == "true") {
			return true;
		}
		else {
			return false;
		}
	}

	static int int64ToInt(int64_t* value) {
		return *value;
	}

private:
};