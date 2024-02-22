#pragma once
#include <iostream>
#include <assert.h>
#include <raylib.h>
#include <queue>
#include <functional>
#include <thread>
#include "../logging/logman.h"

class Layer abstract {
public:

	/**
	 * @brief Pure virtual function to initialize the layer
	 */
	virtual void init() = 0;

	// Pushes tasks into the passive task queue, use if you want to do something before initialization, like loading resources/library into a thread.
	void passivePush(std::function<void()> task) {
		if (task) {
			passiveTaskQueue.push(std::move(task));
		}
	}

	/**
	 * @brief Pushes a task into the task queue
	 * @param task The task to be pushed
	 */
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

	/**
	 * @brief Sets the exit flag to true, indicating shutdown
	 */
	void shutdown() {
		this->exit = true;
	}

protected:
	/**
	 * @brief Asserts that the task queue is not empty before starting
	 */
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