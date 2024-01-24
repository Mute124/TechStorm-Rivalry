#pragma once
#include <vector>
#include <stdio.h>
#include <stdlib.h>

template<typename T>
struct Layer {

	
	const char* LAYERNAME;
	std::vector<T*> layerObjects;
};