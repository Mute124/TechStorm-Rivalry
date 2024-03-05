#pragma once
#include "../../Common.h"

class Renderer abstract {
private:
	Camera rendererCamera;
public:
	virtual void BeginDrawing() {
	}
};
