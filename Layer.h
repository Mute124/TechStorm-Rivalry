#pragma once
#include <vector>
#include <stdio.h>
#include <stdlib.h>

template<typename T>
struct Layer {
	std::vector<T*> layerObjects;
};