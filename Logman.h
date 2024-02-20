#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#pragma warning(disable : 4996)
// handles logging
class Logman {
public:
	Logman() {
		SetTraceLogCallback(this->customLog);
	}

	~Logman() {
		delete this;
	}


	// store data into a log file following the logman format
	static void Store(const char* message) {
		
	}

	static void log(const char* message) {
		customLog(LOG_INFO, message, NULL);
	}

	static void Error(const char* message) {
		customLog(LOG_ERROR, message, NULL);
	}

	static void Warn(const char* message) {
		customLog(LOG_WARNING, message, NULL);
	}
	

	// I dont even know what va_list is...
	static void customLog(int msgType, const char* text, va_list args = 0)
	{

		char timeStr[64] = { 0 };
		
		
		// Works, but isnt the best. eh fuck it
		time_t now = time(NULL);
		struct tm* tm_info = localtime(&now);

		strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
		printf("[%s] ", timeStr);

		switch (msgType)
		{
		case LOG_INFO:
			printf("[INFO] : ");
			break;
		case LOG_ERROR:
			printf("[ERROR]: ");
			break;
		case LOG_WARNING:
			printf("[WARN] : ");
			break;
		case LOG_DEBUG:
			printf("[DEBUG]: ");
			break;
		default:
			break;
		}

		vprintf(text, args);
		printf("\n");
	}

	

private:

};