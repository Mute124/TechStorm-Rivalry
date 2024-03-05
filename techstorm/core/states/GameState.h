#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <array>

class GameStateManager;

class GameState {
public:
	GameState() = default;

	static inline int screenWidth;
	static inline int screenHeight;
	bool isPaused;
	bool isOnTop;
	bool alwaysOnTop;

	virtual void onSwitch() {
	}

	void switchTo() {
		this->isOnTop = true;
	}
};

class GameStateManager final {
public:
	unsigned int activeGameState;
	vector<GameState*> test;

	unsigned int getActiveState() {
	}
};
