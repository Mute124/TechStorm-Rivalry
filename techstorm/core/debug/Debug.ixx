#include <raylib.h>
export module Debug;

export template<typename T>
class DebugObject {
public:
	// set trigger key
	void setTriggerKey(KeyboardKey key) {
		triggerKey = key;
	}

	// get trigger key
	KeyboardKey getTriggerKey() {
		return triggerKey;
	}

	// set debug info
	void setDebugInfo(T info) {
		debugInfo = info;
	}

	// get debug info
	T getDebugInfo() {
		return debugInfo;
	}


private:
	T debugInfo;

	KeyboardKey triggerKey;
	
};