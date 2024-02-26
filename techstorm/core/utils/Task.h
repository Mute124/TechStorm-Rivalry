#pragma once
#include <functional>

// todo: add thread variable support
class Task {
public:

	Task(){}
	Task(std::function<void()> task) {
		this->task = task;
		this->threaded = false;
	}
	std::function<void()> get() {
		return task;
	}

	void run() {
		task();
	}

	void set(std::function<void()> task) {
		this->task = task;
	}

	bool isThreaded() {
		return threaded;
	}

	std::unique_ptr<Task> clone() {
		return std::make_unique<Task>(task);
	}

private:

	bool threaded = false;
	std::function<void()> task;
};
