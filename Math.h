#pragma once
#include <math.h>

// y = sqrt(a * sin(x *(f/F))^c * s) + (O * s)
float ArchAlgorithm(float amplitude, float frequency, float time, float steepness, float offset, float rangeScaleValue, float scaleFactor) {
	return sqrtf(amplitude * powf(sin(time * (frequency / scaleFactor)), steepness) * rangeScaleValue) + offset;
}
	