#pragma once
#include <iostream>
#include <assert.h>
#include <raylib.h>
#include <queue>
#include <functional>
#include <thread>
class Layer abstract {
public:
	/**
	 * @brief Pure virtual function to initialize the layer
	 */
	virtual void init() = 0;

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
			throw std::invalid_argument("Task function is null");
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
	void start() {
		assert(!taskQueue.empty());
	}

	void startLoop() {
		while (!WindowShouldClose()) {
			if (this->exit) {
				break;
			}

			if (!taskQueue.empty()) {
				std::function<void()> task = std::move(taskQueue.front());
				taskQueue.pop();
				if (task) {
						std::thread thread = std::thread(task);
						thread.detach();

				}
			}
		}
		assert(taskQueue.empty());
	}
	bool exit = false; ///< Flag to indicate shutdown
	std::queue<std::function<void()>> taskQueue; ///< Queue for storing tasks
};