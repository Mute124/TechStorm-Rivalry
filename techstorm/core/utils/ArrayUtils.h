#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>

int getArrayLength(int sizeOfArray, int typeSize) {
	return sizeOfArray / typeSize;
}

template<typename T>
int getArrayLength(T data[]) {
	return sizeof(data) / sizeof(T);
}

/*
template<typename T>
class Array {
public:

	// Divides the memory size of the array by the size of the datatype.
	int length() {
		return sizeof(data) / sizeof(T);
	}

	// get size in memory
	int size() {
		return sizeof(data);
	}

	// turn to a C string
	const char* toCStr() {
		return (const char*)data;
	}

	// turn to a C++ string
	std::string toStr() {
		return (std::string)this->data;
	}

	// Clear a slot
	void clear(int slot) {
		data[slot] = nullptr;
	}

	// flush array.
	void flush() {
		data = nullptr[];
	}

	// returns true if the data at the slot is equal to the compare.
	bool equals(T compare, int slot) {
		return data[slot] == compare;
	}

	T data[];
};*/
