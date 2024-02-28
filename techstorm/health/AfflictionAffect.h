#pragma once
#include "Affectable.h"

typedef struct AfflictionAffect {
	int affects[AFFECTABLE_MAX];
	const int changeFactor;
};
