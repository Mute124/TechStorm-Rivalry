#pragma once
#include "RenderLayer.h"
#include "WorkerLayer.h"
#include "InputLayer.h"
class Layers final {
public:

	static inline RenderLayer* renderLayer;
	static inline WorkerLayer* workerLayer;
	static inline InputLayer* inputLayer;

	static inline std::thread workerThread;

	static inline void init() {
		renderLayer = new RenderLayer();
		workerLayer = new WorkerLayer();
		inputLayer = new InputLayer();

		
	}

	static inline void destroy() {
		delete renderLayer;
		delete workerLayer;
		delete inputLayer;
	}
};