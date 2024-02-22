#pragma once
#include "ForwardRenderer.h"
#include "DeferedRenderer.h"

class Renderers final {
public:

	Renderers() {
		init();
	}

	static inline ForwardRenderer* forwardRenderer;
	static inline DeferedRenderer* deferedRenderer;

	static void init() {
		forwardRenderer = new ForwardRenderer();
		deferedRenderer = new DeferedRenderer();
	}

};