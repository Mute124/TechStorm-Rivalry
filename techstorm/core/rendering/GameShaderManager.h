#pragma once
#include "../../Common.h"
#include "GameShaders.h"

class GameShaderManager  {
public:
	void push(GameShader shdr, int slot) {
		nextAvailableSlot++;
		shaders[slot] = shdr;
	}

	void push(GameShader shdr) {
		shaders[nextAvailableSlot] = shdr;
		nextAvailableSlot++;
	}

	int pushAndGetSlot(GameShader shdr) {
		shaders[nextAvailableSlot] = shdr;
		return this->nextAvailableSlot;
		nextAvailableSlot++;
	}

	bool IsSlotClear(int slot) {
		return shaders[slot].isShaderEmpty();
	}

private:
	int nextAvailableSlot;
	GameShader shaders[];
};