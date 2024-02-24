#define UNICODE
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <windows.h>
export module ErrorHandling;

export void throwError() {
	MessageBox(NULL, (LPCWSTR)L"An error has occured.", (LPCWSTR)L"Error!", MB_OK);
}