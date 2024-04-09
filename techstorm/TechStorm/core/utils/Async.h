#pragma once
#include "../../Common.h"
#include <thread>

void DoAsync(std::function<void()> func) {
	std::thread async(func);
	async.detach();
}
