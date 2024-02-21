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

protected:

	static GameShaderManager* manager;

	int pos;
	Shader shdr;
	bool isEmpty;
	
private:
	void load(const char *vs, const char *fs, int position) {
		this->isEmpty = false;
		this->shdr = LoadShader(vs, fs);
		this->pos = position;
		
	}

	void load(const char* vs, const char* fs) {

	}
};