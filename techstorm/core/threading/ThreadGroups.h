#pragma once
#include "ThreadGroup.h"

class ThreadGroups {
public:
	// This group is for worker threads(it does anything that needs to be done in the background)
	static inline ThreadGroup workerThreadGroup; 
	// This group is for main thread. it does anything that needs to be done in the foreground (Not visual)
	static inline ThreadGroup mainThreadGroup;
	// This group is for rendering threads. it does visual stuff. Raylib draw functions run in here.
	static inline ThreadGroup renderThreadGroup;
	// this group is for input threads. it handles input stuff
	static inline ThreadGroup inputThreadGroup;
	// this is for audio threads, it handles audio stuff
	static inline ThreadGroup audioThreadGroup;

	static void init() {
		workerThreadGroup.init();
		mainThreadGroup.init();
		renderThreadGroup.init();
		inputThreadGroup.init();
		audioThreadGroup.init();
	}
};