#pragma once
#include "../TechStorm.h"

namespace TechStorm {
	typedef union AppGlobalUnion {
	};

	typedef struct AppGlobal {
		AppGlobalUnion data;
	};

	typedef struct AppGlobal_ptr {
		AppGlobalUnion* data;
	};
}
