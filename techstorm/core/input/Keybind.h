#pragma once
#include "../../Common.h"

typedef struct Keybind {
	KeyboardKey* key;
	const char* name;
	Task* onPress;
};

