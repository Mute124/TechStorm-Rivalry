#pragma once
#include <map>
#include "threadGroup.h"

class ThreadGroups {
public:

	static inline ThreadGroup& getThreadGroup(const std::string& name) {
		return threadGroups[name];
	}

	static inline void push(std::string name, Task *task) {
		threadGroups[name].addTask(task);
	
	}

	ThreadGroups() {
		threadGroups["main"] = ThreadGroup("main");
		threadGroups["input"] = ThreadGroup("input");
		threadGroups["audio"] = ThreadGroup("audio");
		threadGroups["worker"] = ThreadGroup("worker");
	}

	static inline void exit() {
		for (auto& group : threadGroups) {
			group.second.exit();
		}
		threadGroups.clear();

	}

	static inline void join() {
		for (auto& group : threadGroups) {
			group.second.join();
		}
	}

	static inline std::map<std::string, ThreadGroup> threadGroups;
};