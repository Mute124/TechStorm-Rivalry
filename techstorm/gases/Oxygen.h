#pragma once
#include "Gas.h"

class Oxygen : public Gas {
public:
	Oxygen() {
		this->gasToxicity = 0.0f;
	}
};
