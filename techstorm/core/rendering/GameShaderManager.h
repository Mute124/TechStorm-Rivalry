#pragma once
#include "../../Common.h"
#include "GameShaders.h"


class GameShaderManager final {
public:

	static void init() {
	}

	static inline void push(Shader shader, const char *name) {
		_shaders[name] = shader;
	}


	static inline Shader get(const char* name) {
		return _shaders[name];
	}

	static inline int getLoc(const char* shdrName, const char* locationName) {
		return GetShaderLocation(_shaders[shdrName], locationName);
	}

	static inline void clear() {
		_shaders.clear();
	}

	

private:

	static inline int _registeredShaders = 0;
	static inline std::map<const char *, Shader> _shaders;
};