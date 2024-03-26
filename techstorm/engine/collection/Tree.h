#pragma once
#include "../registry/Registry.h"

#include <vector>
#include <any>

template<typename T>
class Branch {
public:

	std::vector<T> branch;
	const char* name;
};

template<typename T>
class Tree {
public:

	template<typename t>
	std::vector<t> getBranch(const char* branch) {
		return branches[branch];
	}

private:

	std::map<const char*, std::vector<std::any>> branches;
};
