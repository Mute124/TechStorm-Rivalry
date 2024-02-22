#pragma once
#include <stdlib.h>
#include <map>
#include <string>

//todo: This
class VectorRegistry
{
public:
	
	
};

template<typename T>
class MRegistry {
public:

	T* getConfig(int id) {
		return registry[id];
	}

	// Get the next available slot. Use this if you need to assign an ID to an object before pushing it.
	int GetNextSlot() {
		return objectCount+1;
	}

	// Adds it to registry and gives you it's slot
	int Add(T* object) {
		objectCount++;
		this->registry[objectCount] = object;
		return objectCount;
	}

	void Remove(int id) {
		registry.erase(id);
	}

	virtual void updateObjects() {}

	void flushConfig() {
		registry.clear();
	}

private:

	int objectCount = 0;
	std::map<int, T*> registry;
};

template<typename T>
class MRegistry_Str {
public:

	T* getConfig(std::string name) {
		return registry[name];
	}

	// Get the next available slot. Use this if you need to assign an ID to an object before pushing it.
	int GetNextSlot() {
		return objectCount + 1;
	}

	// Adds it to registry and gives you it's slot
	int Add(T* object) {
		objectCount++;
		this->registry[objectCount] = object;
		return objectCount;
	}

	void Remove(int id) {
		registry.erase(id);
	}

	virtual void updateObjects() {}

	void flushConfig() {
		registry.clear();
	}

private:

	int objectCount = 0;
	std::map<std::string, T*> registry;
};
