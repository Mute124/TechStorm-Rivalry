#pragma once
#include <queue>

template <typename T>
class Pool_Ptr {
public:

	// gets the front and DOES NOT remove it. if empty returns a new nullptr
	T* get() {
		if (pool.empty()) {
			return nullptr;
		}
		else {
			return pool.front();
		}
	}

	// gets the front and REMOVES it. if empty returns a new nullptr
	T* take() {
		if (!pool.empty()) {
			T* obj = pool.front();
			pool.pop();
			return obj;
		}
		else {
			return nullptr;
		}
	}
	// put into pool
	void dunk(T* obj) {
		pool.push(std::move(obj));
	}

	// get length
	int getLength() {
		return pool.size() / sizeof(T);
	}

	bool isEmpty() {
		return pool.empty();
	}

private:
	std::queue<T*> pool;
};

template<typename T>
class Pool {
public:
	// gets the front and DOES NOT remove it. if empty returns a new nullptr
	T get() {
		if (pool.empty()) {
			return nullptr;
		}
		else {
			return pool.front();
		}
	}

	// gets the front and REMOVES it. if empty returns a new nullptr
	T take() {
		if (!pool.empty()) {
			T obj = pool.front();
			pool.pop();
			return obj;
		}
		else {
			return nullptr;
		}
	}
	// put into pool
	void dunk(T obj) {
		pool.push(std::move(obj));
	}

	// get length
	int getLength() {
		return pool.size() / sizeof(T);
	}

	bool isEmpty() {
		return pool.empty();
	}

	Pool getPool() {
		return this;
	}
private:
	std::queue<T> pool;
};
