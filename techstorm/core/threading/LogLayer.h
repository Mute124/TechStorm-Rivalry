#pragma once
#include "layer.h"
#include "../logging/Logman.h"

class LogLayer : public Layer, public Logman{
public:

	void init() final override {
		
	}

	void Log(const char* msg) {
		
	}
private:
	
};