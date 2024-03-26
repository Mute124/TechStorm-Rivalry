#pragma once
#include "ESystemStatus.h"

typedef struct StressReport {
	ESystemWorkLoadStatus systemStress;
	bool isStressed = this->systemStress > ESystemWorkLoadStatus::ESYSTEMWORKLOADSTATUS_MEDIUM;
};
