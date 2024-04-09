#pragma once
template<typename T>
struct ListEntry
{
	T entry;
	const char* tag;
	const char* name;
	int id;
};
