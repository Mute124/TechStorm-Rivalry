#pragma once
#include <iostream>
#include <assert.h>
#include <raylib.h>
#include <queue>
#include <functional>
#include <thread>
#include "../logging/logman.h"
#include "ThreadGroups.h"

class Layer abstract {
public:
	virtual void init() = 0;
	virtual void destroy() = 0;

	void startLayer(ThreadGroup* threadGroup) {
		Logman::Log(
			std::string("starting layer of " + std::string(threadGroup->getName())).c_str()
		);
		this->layerThreadGroup = std::move(threadGroup);
	}

	void startLayer(int threadGroup) {
		this->startLayer(&this->layerThreadGroup[threadGroup]);
	}

	
	void push(std::function<void()> task) {
		if (task) {
			this->layerThreadGroup->assignTask(std::move(task));
		}
		else {
			throw std::invalid_argument("Task function is null!");
		}
	}

	void shutdown() {
		this->layerThreadGroup->shutdown();
	}
protected:
	ThreadGroup *layerThreadGroup;
};

/*
* 
class Layer abstract {
public:


virtual void init() = 0;

// Pushes tasks into the passive task queue, use if you want to do something before initialization, like loading resources/library into a thread.
void passivePush(std::function<void()> task) {
	if (task) {
		passiveTaskQueue.push(std::move(task));
	}
}


void push(std::function<void()> task) {
	if (task) {
		taskQueue.push(std::move(task));
	}
}

// go through the args array and pass them to the task, and push the task into the task queue
template<typename T>
void push(std::function<void(T[])> task, T args[]) {
	if (task) {
		for (int i = 0; args[i] != nullptr; i++) {
			task(args[i]);
		}
		taskQueue.push(task);
	}
	else {
		throw std::invalid_argument("Task function is null!");
	}
}


void shutdown() {
	this->exit = true;
}

protected:

	void startLayer() {
		Logman::Log("Starting Layer");
		// push all the tasks in the passive task queue into the task queue
		for (passiveTaskQueue.size(); !passiveTaskQueue.empty(); passiveTaskQueue.pop()) {
			push(passiveTaskQueue.front());
		}
		std::thread t(&Layer::startLoop, this);
		t.detach();
	}

	void startLoop() {
		Logman::Log("Layer Started");
		while (!WindowShouldClose() && !this->exit) {
			if (!taskQueue.empty()) {
				std::function<void()> task = std::move(taskQueue.front());
				taskQueue.pop();
				if (task) {
					task();
				}
			}
		}

		assert(taskQueue.empty());
	}
	bool exit = false; ///< Flag to indicate shutdown
	std::queue<std::function<void()>> taskQueue; ///< Queue for storing tasks

	std::queue<std::function<void()>> passiveTaskQueue;
};
*/