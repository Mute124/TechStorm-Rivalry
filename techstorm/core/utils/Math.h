/*
	Important : All math is using the METRIC system!

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

#include <raylib.h>
//#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

// Speed of light!
#define LIGHT_SPEED (double)299792458.0f

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
inline float ArchAlgorithm(float amplitude, float frequency, float time, float steepness, float offset, float rangeScaleValue, float scaleFactor) {
	float sinValue = sin(time * (frequency / scaleFactor));
	float powValue = powf(sinValue, steepness);
	float result = sqrtf(amplitude * powValue * rangeScaleValue) + offset;
	return result;
}

template<typename T>
inline float DatasetLength(std::vector<T> dataset) {
	return sizeof(dataset) / sizeof(T);
}

/*
* Get the average value in a dataset;
*
* System of equations equation:
*
* x = !dataset[];
* y = x/length
*
*/
template<typename T>
inline float DataSetAverage(std::vector<T> dataset) {
	float sum;
	const int length = DatasetLength<T>(dataset);
	for (int i = 0; i < length; i++) {
		sum += dataset[i];
	}

	return sum / length;
}

/*
*
* Calculate a incremented value (the slope between two values)
*
* f(x,y,z) = x(y - z) + o
*
* x = normalizing factor
* y, z = data points
* o = offset
*/
inline float IncrementDelta(float x, float y, float z, float o) {
	return x * (y - z) + o;
}

/*
* Calculates a point in a 4 point quadrilateral. from the top left point and it's width/height.
*
* Formula :
* L1 = given
* L2 = (L1.x, L1.y - height)
*
* R1 = (L1.x + width, L1.y)
* R2 = (L1.x + width, L1.y - height)
*
* Corners:
*
* Top left L1 (0)
* Top Right R1 (1)
*
* Bottom Left L2 (2)
* Bottom Right R2 (3)
*
*/
inline Vector2 CalculatePoint(Vector2 orgin, float width, float height, int corner) {
	// todo: Calculate any point from any point, width, and height.
	Vector2 point;
	switch (corner) {
	case 0:
		point = orgin;
		break;

	case 1:
		point = { orgin.x + width, orgin.y };
		break;

	case 2:
		point = { orgin.x, orgin.y - height };
		break;

	case 3:
		point = { orgin.x + height, orgin.y - height };
		break;

	default:
		break;
	}

	return point;
}
