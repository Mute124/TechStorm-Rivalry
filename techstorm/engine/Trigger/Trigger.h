#pragma once
#include "../../Common.h"

class Trigger abstract {
public:
	BoundingBox triggerBox;
	virtual void onTrigger() {
	}
};
