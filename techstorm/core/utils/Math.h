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
#include <stdlib.h>
#include <stdio.h>

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

template<typename T>
float DatasetLength(std::vector<T> dataset) {
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
float DataSetAverage(std::vector<T> dataset) {
	float sum;
	const int length = DatasetLength<T>(dataset);
	for (int i = 0; i < length; i++ ){
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
float IncrementDelta(float x, float y, float z, float o) {
	return x * (y - z) + o;
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
float IncrementDelta(float x, float y, float z) {
	return IncrementDelta(x, y, z, 0.0f);
}

/*
* Create deltas for a level. (Thresholds)
* 
* f(x) = 
* 
*/
float levelDelta(int levels, int calculateFor, float max) {
	float mean;
	std::vector<float> levelsVec;
	

	if (calculateFor == levels) return max;
	else {
		mean = (calculateFor*max) / levels;

		for (int i = 0; i < levels; i++) {
			if (i == 0) {
				levelsVec.push_back(mean);
			}
			else if (i != max) {
				//(max - mean + levelsVec[i - 1]) / (levels - i)
				levelsVec.push_back((mean + levelsVec[i - 1])/max);
			}
			else if (i == calculateFor) {
				return (mean + levelsVec[i - 1]) / max;
			}
			else {
				levelsVec.push_back(max);
			}
		}
		Logman::Log(TextFormat("mean is : %f", mean));
		for (int i = 0; i < DatasetLength<float>(levelsVec); i++) {
			Logman::Log(TextFormat("Value is : %f", levelsVec[i]));

			//printf((const char*)i);
		}
	}
}
