#pragma once
#include "Thread.h"
#include "../registry/Pool.h"
#include <map>

// max threads per group.
#define THREAD_GROUP_SIZE 4
// max number of groups. Trust me you don't need more. if you do i'll be very concerned about your code...
#define MAX_GROUPS 6

// ThreadGroup aka group of threads that a layer can have/use. Also provides utilities for said group. 
// WARNING: Threads ARE NOT SHARED. Threads in group share resources. Threads are also NOT THROTTLED. Use with caution. 
class ThreadGroup {
public:
	// add thread to group
	void addThread(Thread thread) {
		if (groupThreads.size() < MAX_GROUPS) {
			for (auto& slot : slots) {
				if (slot.second != true) {
					continue;
				}
				else {
					groupThreads[slot.first] = std::move(thread);
				}
			}
		}
		else {
			// TODO: throw exception
			delete& thread;
			throw "ThreadGroup is full";
		}
	}

	// initialize
	void init() {
		// make sure map is clear
		if (groupThreads.size() > 0) {
			groupThreads.clear();
		}

		// todo: Check CPU capabilities and set limits
	}

	// destroy all threads
	void destroy() {
		this->killAllThreads();
	}

	// check if group is full
	bool isFull() {
		return groupThreads.size() >= THREAD_GROUP_SIZE;
	}

	// get number of slots
	int getSlots() {
		return THREAD_GROUP_SIZE - groupThreads.size();
	}

	// get number of threads
	int getThreadCount() {
		return groupThreads.size();
	}

	void addThreads(int groupId, int count) {
		for (int i = 0; i < count; i++) {
			if (groupThreads.size() < MAX_GROUPS) {
				Thread thread(groupId);
				this->addThread(std::move(thread));
			}
			else {
				break;
			}
		}
	}

	// get thread
	Thread& getThread(int slotId) {
		return groupThreads[slotId];
	}

	// does not actually kill the thread, but rather detaches it.
	void killAllThreads() {
		for (auto& thread : groupThreads) {
			thread.second.kill();
		}

		groupThreads.clear();
	}

	// wait for all threads
	void waitForAllThreads() {
		for (auto& thread : groupThreads) {
			thread.second.join();
		}
		groupThreads.clear();
	}

	// assigns task to the first available worker. However if backed up, it will assign the backed up task first, then the new task.
	// unless a priority.
	void assignTask(std::function<void()> task, bool isPriority = false) {
		bool assignedTask = false;
		for (auto& t : groupThreads) {
			if (t.second.isAvailable())
				
				// assign task, if either not backed up or task is priority. if not a priority task, assign a backed up task first
				if (!isBackedUp xor isPriority) {
					assignedTask = true;
					t.second.assignTask(std::move(task));
				}
				else {
					t.second.assignTask(*std::move(this->taskPool[backedUpIndex].get()));
					backedUpIndex--;
				}
		}
		

		if (!assignedTask) {
			backedUpIndex++;
			this->taskPool[backedUpIndex].dunk(&std::move(task));
			if (!isBackedUp) {
				isBackedUp = true;
			}
		}
		
	}

	static ThreadGroup& getThreadGroup(int groupId) {
		return threadGroups[groupId];
	}

	static Thread& getThreadInGroup(int groupId, int slotId) {
		return threadGroups[groupId].getThread(slotId);
	}

	// reserve a thread.
	static Thread& reserveThread(int groupId) {
		return threadGroups[groupId].getNextAvailable();
	}

	// get own name
	const char *getName() {
		return name;
	}

	const char* setName(const char* name) {
		this->name = name;
	}

	// get name of a group.
	const char* getName(int groupId) {
		return threadGroups[groupId].getName();
	}

	void shutdown() {
		this->killAllThreads();
	}

	void shutdown(int groupId) {
		threadGroups[groupId].killAllThreads();
	}

private:
	


	Thread& getNextAvailable() {
		for (auto& thread : groupThreads) {
			if (thread.second.isAvailable()) {
				return thread.second;
			}
		}
	}

	
	const char *name;
	// map of thread slot, thread
	std::map<int, Thread> groupThreads;
	std::map<int, Pool_Ptr<std::function<void()>>> taskPool;

	bool isBackedUp = false;
	int tasksWaitingCount = 0;
	int backedUpIndex = 0;

	// status of the slots
	std::map<int, bool> slots;
	static inline std::map<int, ThreadGroup> threadGroups;
	

	static inline std::map<int, Pool_Ptr<std::function<void()>>> groupTasks;
	
	
};