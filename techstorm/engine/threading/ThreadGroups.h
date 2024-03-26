#pragma once
#include <map>
#include "threadGroup.h"

#ifdef USE_PROTOTYPE_THREADING

class ThreadGroups {
public:

	static inline ThreadGroup& getThreadGroup(const std::string& name) {
		return *_threadGroups[name];
	}

	static inline void push(std::string name, ThreadGroupTask* task) {
		_threadGroups[name]->addTask(task);
	}

	ThreadGroups() {
		_threadGroups["main"] = new ThreadGroup("main");
		_threadGroups["input"] = new  ThreadGroup("input");
		_threadGroups["audio"] = new ThreadGroup("audio");
		_threadGroups["worker"] = new ThreadGroup("worker");
		_threadGroups["scripting"] = new ThreadGroup("scripting");
	}

	static inline void exit() {
		for (auto& group : _threadGroups) {
			group.second->exit();
		}
		_threadGroups.clear();
	}

	static inline void join() {
		for (auto& group : _threadGroups) {
			group.second->join();
		}
	}

	static inline std::map<std::string, ThreadGroup*> _threadGroups;
};
#else

class ThreadGroups {
public:

	static inline void push(std::string name, ThreadGroupTask* task) {
		_threadGroups[name] = new std::thread(task->get());
	}

	ThreadGroups() {
		_threadGroups["main"] = new std::thread();
		_threadGroups["input"] = new std::thread();
		_threadGroups["audio"] = new std::thread();
		_threadGroups["worker"] = new std::thread();
		_threadGroups["scripting"] = new std::thread();
	}

	static inline void exit() {
		for (auto& group : _threadGroups) {
			group.second->join();
		}
		_threadGroups.clear();
	}
	static inline std::map<std::string, std::thread*> _threadGroups;
};
#endif
