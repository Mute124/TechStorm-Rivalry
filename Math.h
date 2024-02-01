/*
	This file is part of the TechStorm Engine. This is simply a set of math functions and algorithms. 


	
	Algorithm Explanations

	Arch Algorithm : 
		Used to ease in a value over time. 

		y is the output
		a is the amplitude
		f is the frequency
		s is the scaling factor (This is needed to scale the algorithm to your needs)
		o is the offset the algorithm will be at on the Y AXIS

		Formula : 
			y = sqrt(a * sin(x *(f/F))^c * s) + o
*/

#pragma once
#include <math.h>

// y = sqrt(a * sin(x *(f/F))^c * s) + o
float ArchAlgorithm(float amplitude, float frequency, float time, float steepness, float offset, float rangeScaleValue, float scaleFactor) {
	return sqrtf(amplitude * powf(sin(time * (frequency / scaleFactor)), steepness) * rangeScaleValue) + offset;
}
	