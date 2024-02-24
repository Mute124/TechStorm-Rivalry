#pragma once
#include "Thread.h"
#include <map>
#include "../utils/task.h"

using namespace std;

class ThreadGroup {
public:

	ThreadGroup() {}

	ThreadGroup(const char* groupName, int groupSize) {
		init(groupName, groupSize);
	}

	ThreadGroup(const char *groupName) {
		init(groupName, 1);
	}

	void init(const char* groupName, int groupSize) {
		this->groupName = groupName;
		this->groupID = assignGroupID();
		for (int i = 0; i < groupSize; i++) {
			Thread* t = new Thread(this->groupID);
			threads.insert(pair<int, Thread*>(i, t));
		}

		
		Logman::Log(groupName);
	}

	void addTask(Task* task) {
		// go through map, find first idle thread and give it a task.
		for (auto& thread : threads) {
			if (thread.second->isIdle) {
				thread.second->addTask(task);
				break;
			}
		}
	}

	void addTask(std::function<void()> task) {
		addTask(new Task(task));
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
	const char *groupName;
	int groupID;

	static inline int groupCount = 0;
	static int assignGroupID() {
		return groupCount;
		groupCount++;
	}

	map<int, Thread*> threads;
};