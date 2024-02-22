#pragma once

// use only for large data
class DataPackage
{
public:

	// pack into char *
	template<typename T>
	void pack(T data) {
		this->size = sizeof(T);
		this->data = new char[size];
		memcpy(this->data, &data, size);
	}

	// unpack back into a type
	template<typename T>
	T unpack() {
		T result;
		memcpy(&result, this->data, sizeof(T));
		return result;
	}
	

	DataPackage get() {
		return *this;
	}
private:
	char *data = nullptr;
	int size = 0;
};