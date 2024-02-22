#pragma once
#include <thread>
#include <functional>

class Thread {
public:
	Thread(std::function<void()> task, int threadGroupID = -1) {
		this->taskFunction = task;
		this->isRunning = false;
		this->isPaused = false;
		this->isTerminated = false;
		this->threadGroupID = threadGroupID;

		this->invokeTask();
	}

	Thread(int groupID) {
		this->isRunning = false;
		this->isPaused = false;
		this->isTerminated = false;
		this->threadGroupID = threadGroupID;
	}

	void join() {
		this->localThread.join();
	}

	void pause() {
		this->isPaused = true;
	}

	void kill() {
		this->isTerminated = true;
		this->isRunning = false;
		this->isPaused = false;
		this->localThread.join();
	}

	std::thread localThread;

	// conditional information
	// is a task being executed
	bool isRunning = false;
	// is the thread idle (opposite of running)
	bool isIdle = !isRunning;

	// is the thread paused
	bool isPaused = false;

	// is the thread terminated (dead, NOT IDLE)
	bool isTerminated = false;

	// has it finished it's task?
	bool finishedTask = false;

	// A rogue thread is a thread that is not part of a thread group
	bool isRogue = threadGroupID < 0;

	// the group it belongs to. -1 = no group and it becomes rogue
	int threadGroupID;



	int getGroupId() {
		return this->threadGroupID;
	}

	bool isAvailable() {
		return this->isIdle;
	}

	void assignTask(std::function<void()> task) {
		this->taskFunction = task;
		this->invokeTask();
	}
private:


	std::function<void()> taskFunction;

	void invokeTask() {
		
		this->localThread = std::thread([this]() {
			if (!this->isPaused && !isTerminated) {
				this->isRunning = true;
				this->finishedTask = false;

				this->taskFunction();

				this->finishedTask = true;
				this->isRunning = false;

			}
		});
		this->localThread.detach();
	}

	
};