#pragma once
#include <functional>

class Task {
public:

	Task(){}
	Task(std::function<void()> task) {
		this->task = task;
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
private:
	std::function<void()> task;
};
