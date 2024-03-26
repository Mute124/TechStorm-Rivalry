#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

const char* StrToCStr(string str) {
	return str.c_str();
}

string CStrToStr(const char* cstr) {
	return (string)cstr;
}
