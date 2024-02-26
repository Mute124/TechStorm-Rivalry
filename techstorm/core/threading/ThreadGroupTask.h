#pragma once
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <functional>



class ThreadGroupTask {
public:

	static inline ThreadGroupTask* MakeThreadGroupTask(std::function<void()> function) {
		return new ThreadGroupTask(function);
	}

	ThreadGroupTask(std::function<void()> function) : _function(function) {}
	void operator()() {
		_function();
	}

	std::unique_ptr<ThreadGroupTask> clone() {
		return std::make_unique<ThreadGroupTask>(_function);
	}

	void run() {
		_function();
	}

	void setFunction(std::function<void()> function) {
		_function = function;
	}

	// get function
	std::function<void()> get() {
		return _function;
	}

private:
	std::function<void()> _function;
};