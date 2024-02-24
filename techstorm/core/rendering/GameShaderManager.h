#pragma once
#include "../../Common.h"
#include "GameShaders.h"


class GameShaderManager final {
public:

	static void init() {
	}

	void push(GameShader shader) {
		gameShadersByID[shader.getID()] = &shader;
		gameShadersByName[shader.getName()] = &shader;
	}

	void remove(int id) {
		gameShadersByID.erase(id);
		//todo: go through gameShadersByName and remove that
	}

	GameShader* get(int id) {
		return gameShadersByID[id];
	}

	GameShader* get(const char* name) {
		return gameShadersByName[name];
	}

	void clear() {
		gameShadersByID.clear();
		gameShadersByName.clear();
	}

private:
	static inline std::map<int, GameShader*> gameShadersByID;

	static inline std::map<const char *, GameShader*> gameShadersByName;
};