#pragma once
#include <stdlib.h>
#include <map>
#include <string>

//todo: This
class VectorRegistry
{
public:
};

namespace TechStorm {
	template<typename SortType, typename T>
	class MRegistry_Base abstract {
	public:

		virtual std::map<SortType, T*> getRegistry() {
			return registry;
		}

		virtual std::map<SortType, T*>* getRegistryPtr() {
			return &registry;
		}

		// Get a entry witheld in this registry
		virtual T* getEntry(SortType id) {
			return registry[id];
		}

		// Get the next available slot. Use this if you need to assign an ID to an object before pushing it.
		virtual int getNextEntrySlot() {
			return objectCount + 1;
		}

		// Adds it to registry and gives you it's slot
		virtual int addEntry(T* object) {
			objectCount++;
			this->registry[objectCount] = object;
			return objectCount;
		}

		virtual void removeEntry(SortType id) {
			m_mapRegistry.erase(id);
		}

		virtual void updateEntries() {}

		virtual void findEntry(SortType id) {}

		virtual void flushRegistry() {
			m_mapRegistry.clear();
		}

	protected:

		int m_objectCount = 0;
		std::map<SortType, T*, std::less<SortType>> m_mapRegistry;
	};
	template<typename T>
	class MRegistry {
	public:

		T* getItem(int id) {
			return registry[id];
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

		virtual void updateRegistry() {}

		void flushConfig() {
			registry.clear();
		}

		int getCount() {
			return objectCount;
		}
	private:

		int objectCount = 0;
		std::map<int, T*> registry;
	};

	// extended MRegistry that allows you to set the map's find type
	template<typename SortType, typename T>
	class MRegistry_Ext {
	public:

		std::map<SortType, T*> get() {
			return registry;
		}

		std::map<SortType, T*>* getPtr() {
			return &registry;
		}

		T* getItem(SortType id) {
			return registry[id];
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

		void Remove(SortType id) {
			registry.erase(id);
		}

		virtual void updateObjects() {}

		virtual void find(SortType id) {}

		void flushConfig() {
			registry.clear();
		}

	private:

		int objectCount = 0;
		std::map<SortType, T*, std::less<SortType>> registry;
	};

	template<typename T>
	class MRegistry_Str {
	public:

		T* getEntry(std::string name) {
			return registry[name];
		}

		// Get the next available slot. Use this if you need to assign an ID to an object before pushing it.
		int GetNextSlot() {
			return objectCount + 1;
		}

		// Adds it to registry and gives you it's slot
		int addEntry(T* object, std::string name) {
			objectCount++;
			this->registry[name] = object;
			return objectCount;
		}

		void Remove(int id) {
			registry.erase(id);
		}

		virtual void updateObjects() {}

		void flushConfig() {
			registry.clear();
		}

		bool entryExists(std::string entry) {
			return nullptr != registry.at(entry);
		}

	private:

		int objectCount = 0;
		std::map<std::string, T*> registry;
	};

	template<typename T>
	class MRegistry_CSTR {
	protected:
		T* getEntry(const char* name) {
			return registry[name];
		}

		// Get the next available slot. Use this if you need to assign an ID to an object before pushing it.
		int GetNextSlot() {
			return objectCount + 1;
		}

		// Adds it to registry and gives you it's slot
		int addEntry(T* object) {
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

		int objectCount = 0;
		std::map<const char*, T*> registry;
	};
}
