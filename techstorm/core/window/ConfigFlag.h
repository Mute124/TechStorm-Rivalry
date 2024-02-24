#pragma once
#include <raylib.h>
#include <map>
#include <vector>
#include <queue>


class ConfigFlag {
public:

	// enable flag
	void stampFlag(ConfigFlags flag) {
		flagStamps[flag] = true;
	}

	// disable flag
	void unstampFlag(ConfigFlags flag) {
		flagStamps[flag] = false;
	}

	// get stamps map
	std::map<ConfigFlags, bool> getStampsMap() {
		return flagStamps;
	}

	// get stamps as an vector
	std::vector<ConfigFlags> getStampsArray() {
		std::vector<ConfigFlags> stampsArray;
		for (const auto& stamp : flagStamps) {
			stampsArray.push_back(stamp.first);
		}
		return stampsArray;
	}

	const char* getFlagName(ConfigFlags flag) {
		switch (flag) {
		case ConfigFlags::FLAG_BORDERLESS_WINDOWED_MODE:
			return "FLAG_BORDERLESS_WINDOWED_MODE";
			break;

		case ConfigFlags::FLAG_FULLSCREEN_MODE:
			return "FLAG_FULLSCREEN_MODE";
			break;

		case ConfigFlags::FLAG_WINDOW_RESIZABLE:
			return "FLAG_WINDOW_RESIZABLE";
			break;

		case ConfigFlags::FLAG_WINDOW_UNDECORATED:
			return "FLAG_WINDOW_UNDECORATED";
			break;

		case ConfigFlags::FLAG_WINDOW_HIDDEN:
			return "FLAG_WINDOW_HIDDEN";
			break;

		case ConfigFlags::FLAG_WINDOW_ALWAYS_RUN:
			return "FLAG_WINDOW_ALWAYS_RUN";
			break;

		case ConfigFlags::FLAG_MSAA_4X_HINT:
			return "FLAG_MSAA_4X_HINT";
			break;

		case ConfigFlags::FLAG_VSYNC_HINT:
			return "FLAG_VSYNC_HINT";
			break;

		case ConfigFlags::FLAG_WINDOW_TRANSPARENT:
			return "FLAG_WINDOW_TRANSPARENT";
			break;

		case ConfigFlags::FLAG_WINDOW_HIGHDPI:
			return "FLAG_WINDOW_HIGHDPI";
			break;

		case ConfigFlags::FLAG_INTERLACED_HINT:
			return "FLAG_INTERLACED_HINT";
			break;

		default:
			return "Unknown flag";
			break;
		}
	}

	static inline int getFlagValue(ConfigFlags flag) {
		switch (flag) {
		case ConfigFlags::FLAG_BORDERLESS_WINDOWED_MODE:
			return ConfigFlags::FLAG_BORDERLESS_WINDOWED_MODE;
			break;

		case ConfigFlags::FLAG_FULLSCREEN_MODE:
			return ConfigFlags::FLAG_FULLSCREEN_MODE;
			break;

		case ConfigFlags::FLAG_WINDOW_RESIZABLE:
			return ConfigFlags::FLAG_WINDOW_RESIZABLE;
			break;

		case ConfigFlags::FLAG_WINDOW_UNDECORATED:
			return ConfigFlags::FLAG_WINDOW_UNDECORATED;
			break;

		case ConfigFlags::FLAG_WINDOW_HIDDEN:
			return ConfigFlags::FLAG_WINDOW_HIDDEN;
			break;

		case ConfigFlags::FLAG_WINDOW_ALWAYS_RUN:
			return ConfigFlags::FLAG_WINDOW_ALWAYS_RUN;
			break;

		case ConfigFlags::FLAG_MSAA_4X_HINT:
			return ConfigFlags::FLAG_MSAA_4X_HINT;
			break;

		case ConfigFlags::FLAG_VSYNC_HINT:
			return ConfigFlags::FLAG_VSYNC_HINT;
			break;

		case ConfigFlags::FLAG_WINDOW_TRANSPARENT:
			return ConfigFlags::FLAG_WINDOW_TRANSPARENT;
			break;

		case ConfigFlags::FLAG_WINDOW_HIGHDPI:
			return ConfigFlags::FLAG_WINDOW_HIGHDPI;
			break;

		case ConfigFlags::FLAG_INTERLACED_HINT:
			return ConfigFlags::FLAG_INTERLACED_HINT;
			break;

		default:
			return 0;
			break;
		}
	}

	// check if flag is stamped
	bool isFlagStamped(ConfigFlags flag) {
		return flagStamps[flag];
	}

	// clear stamps
	void clearStamps() {
		flagStamps.clear();
	}

	// finalize stamps, use them within SetConfigFlags() and log the flags that were stamped
	void finalizeStamps(bool log = false) {
		// function variables initialization
		std::queue<unsigned int> flags;
		unsigned int flagsArray[16];
		int index;

		// get stamps & push it into the queue
		for (auto& flag : flagStamps) {
			if (flag.second == true) {
				flags.push(getFlagValue(flag.first));
			}
		}

		// convert into an array
		for (; !flags.empty(); flags.pop()) {
			flagsArray[index] = flags.front();
			index++;
		}

		// log flags if set to true
		if (log) {
			for (int i = 0; i < index; i++) {
				Logman::Log(getFlagName((ConfigFlags)flagsArray[i]));
			}
		}

		// set flags
		SetConfigFlags(*flagsArray);

	}

	static void testStamps(unsigned int flags) { 
		Logman::Log(std::to_string(flags).c_str());
	}

	// print all stamps
	void logStamps() {
		// get all flags
		for (auto& flag : flagStamps) {
			Logman::Log(ConfigFlag::getFlagName(flag.first));
		}
	}

	// logs all stamp's values
	void logStampValues() {
		// get all flags
		for (auto& flag : flagStamps) {

			std::string str = "Flag: " + std::to_string((int)ConfigFlag::getFlagValue(flag.first)) + " : " + std::to_string(flag.second);
			Logman::Log(str.c_str());
		}
	}

private:
	// A map of flags and if they have been stamped (enabled or disabled)
	std::map<ConfigFlags, bool> flagStamps;

};