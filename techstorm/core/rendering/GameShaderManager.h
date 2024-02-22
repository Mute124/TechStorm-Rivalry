#pragma once
#include "../../Common.h"
#include "GameShaders.h"


class GameShaderManager final {
public:

	// push shader to a certain slot and if taken it will replace.
	void push(GameShader shdr, int slot) {
		nextAvailableSlot++;
		shaders[slot] = shdr;
	}

	// push shader into array at next available slot
	void push(GameShader shdr) {
		shaders[nextAvailableSlot] = shdr;
		nextAvailableSlot++;
	}

	// push shader into array and get slot number
	int pushAndGetSlot(GameShader shdr) {
		shaders[nextAvailableSlot] = shdr;
		return this->nextAvailableSlot;
		nextAvailableSlot++;
	}
	
	// is the given slot in the array empty
	bool isSlotClear(int slot) {
		return shaders[slot].isShaderEmpty();
	}

	GameShader get(int slot) {
		return shaders[slot];
	}

private:
	int nextAvailableSlot;
	GameShader shaders[];
};