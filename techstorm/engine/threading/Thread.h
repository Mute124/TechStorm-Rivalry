#pragma once
#include <raylib.h>
#include <thread>
#include <queue>
#include "../utils/Task.h"
#include "../logging/Logman.h"
#include "ThreadGroupTask.h"

class Thread {
public:

	Thread(int groupID, int workerID = 0) {
		Logman::Log("test");
		this->groupID = groupID;
		this->workerID = workerID;
		isRunning = true;
		isBusy = false;
		isRouge = false;
		terminate = false;

		std::string threadName = "Thread " + std::to_string(groupID) + " Worker " + std::to_string(workerID);

		Logman::Log(threadName.c_str());
		std::thread worker(([this, threadName]() {
			Logman::Log(threadName.c_str());
			//Logman::Log(TextFormat("Threadname : %s, localThread var id : %i, this thread : %i", threadName.c_str(), localThread->get_id(), std::this_thread::get_id()));
			while (isRunning && !terminate) {
				// check if we are busy, if not we are idle. Wait until a task is added to the queue.
				if (!isBusy) {
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
				else {
					isIdle = false;
					ThreadGroupTask* task = taskQueue.front();
					taskQueue.pop();
					run(task);
					isBusy = false;
				}

				if (WindowShouldClose()) {
					exit();
				}
			}
			}));

		worker.detach();
	}

	void addTask(ThreadGroupTask* task) {
		taskQueue.push(task);
		this->isBusy = true;
	}

	void exit() {
		isRunning = false;
		terminate = true;
		std::this_thread::yield();
	}

	void join() {
		std::this_thread::yield();
	}
	bool isRunning;
	bool isBusy;
	bool isIdle = !isBusy;
	bool terminate;
	bool isRouge;

	const char* name;

	int groupID;
	int workerID;
private:

	void run(ThreadGroupTask* task) {
		task->get();
	}

	std::queue<ThreadGroupTask*> taskQueue;
};
