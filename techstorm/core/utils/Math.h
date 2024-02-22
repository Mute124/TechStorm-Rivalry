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
/**
 * Calculate the value of an arched function.
 *
 * @param amplitude - The amplitude of the function
 * @param frequency - The frequency of the function
 * @param time - The time at which the function is evaluated
 * @param steepness - The steepness of the function
 * @param offset - The offset of the function
 * @param rangeScaleValue - The range scale value of the function
 * @param scaleFactor - The scale factor of the function
 *
 * @return The value of the arched function at the given time
 */
float ArchAlgorithm(float amplitude, float frequency, float time, float steepness, float offset, float rangeScaleValue, float scaleFactor) {
	float sinValue = sin(time * (frequency / scaleFactor));
	float powValue = powf(sinValue, steepness);
	float result = sqrtf(amplitude * powValue * rangeScaleValue) + offset;
	return result;
}

