#pragma once
#include "../TechStorm.h"
namespace TechStorm {
	typedef enum EDrawMode {
		EDRAW_NULL = 0,
		EDRAW_2D,
		EDRAW_3D
	};

#ifdef TECHSTORM_ENGINE_3D
	const EDrawMode DRAWMODE = EDRAW_3D;
#else
	const EDrawMode DRAWMODE = EDRAW_2D;
#endif // TECHSTORM_ENGINE_3D
}
