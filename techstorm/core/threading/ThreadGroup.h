#pragma once
#include "Thread.h"
#include <map>
#include "../utils/task.h"
#include "ThreadGroupTask.h"

using namespace std;

class ThreadGroup {
public:

	ThreadGroup() {}

	ThreadGroup(const char* groupName, int groupSize) {
		init(groupName, groupSize);
	}

	ThreadGroup(const char* groupName) {
		init(groupName, 1);
	}

	void init(const char* groupName, int groupSize) {
		this->groupName = groupName;
		this->groupID = _assignGroupID();
		for (int i = 0; i < groupSize; i++) {
			Thread* t = new Thread(this->groupID);
			threads.insert(pair<int, Thread*>(i, t));
		}

		TechStorm::Logman::Log(groupName);
	}

	void addTask(ThreadGroupTask* task) {

		// go through map, find first idle thread and give it a task.
		for (auto& thread : threads) {
			if (thread.second->isIdle) {
				thread.second->addTask(task);
				break;
			}
		}
	}

	void addTask(std::function<void()> task) {
		addTask(new ThreadGroupTask(task));
	}

	void addTask(std::unique_ptr<ThreadGroupTask> task) {
		addTask(std::move(task));
	}

	void exit() {
		for (auto& thread : threads) {
			thread.second->exit();
		}
	}

	void join() {
		for (auto& thread : threads) {
			thread.second->join();
		}
	}

private:
	const char* groupName;
	int groupID;

	static inline int _groupCount = 0;
	static int _assignGroupID() {
		return _groupCount;
		_groupCount++;
	}

	map<int, Thread*> threads;
};
