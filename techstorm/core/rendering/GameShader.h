#pragma once
#include "../../Common.h"
#include "GameShaderManager.h"

class GameShader {
public:

	static inline void setManager(GameShaderManager* manager) {
		GameShader::manager = manager;
	}

	GameShader(const char* vs, const char* fs, int shdrPosition) {
		
	}

	GameShader(const char* vs, const char* fs) {

	}

	Shader getShader() {
		return this->shdr;
	}

	bool isShaderEmpty() {
		return this->isEmpty;
	}

	int getLoc(ShaderLocationIndex index) {
		return this->shdrLocations[index];
	}

	void setLoc(ShaderLocationIndex index, int loc) {
		this->shdrLocations[index] = loc;
	}

	int getID() {
		return this->id;
	}
	
	const char* getName() {
		return this->name;
	}


protected:

	static GameShaderManager* manager;

	int id;
	const char* name;
	int pos;
	Shader shdr;
	bool isEmpty;
	std::map<ShaderLocationIndex, int> shdrLocations;
	
private:


	
};