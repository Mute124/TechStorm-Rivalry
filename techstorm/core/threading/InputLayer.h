#pragma once
#include "Layer.h"
#include "../logging/Logman.h"
#include <map>
#include <functional>

typedef enum EWatchCondition {
	CONDITION_NULL,
	CONDITION_PRESSED,
	CONDITION_PRESSED_REPEAT,
	CONDITION_DOWN,
	CONDITION_UP,

};

class InputAction {
public:
	KeyboardKey getKey() { return this->key; }
	std::function<void()> getDoIfPressed() { return this->doIfPressed; }
	std::function<void()> getDoIfNotPressed() { return this->doIfNotPressed; }

	KeyboardKey key;
	std::function<void()> doIfPressed;
	std::function<void()> doIfNotPressed;

	EWatchCondition condition = EWatchCondition::CONDITION_NULL;
};


class InputLayer final : public Layer {
public:
	/**
	 * @brief Pure virtual function to initialize the layer
	 */
	void init() final override {
		Logman::log("InputLayer::init()");

		this->keyMap.clear();
		this->push([this]() { this->update(); });
	}

	// goes through map, check if key is pressed, and calls doIfPressed or doIfNotPressed depending on if not a nullptr. Also checks it's watch condition and follows it.
	// Note: THIS IS A THREADED FUNCTION
	void update() {

		InputActionFactory *inputActionFactory = new InputActionFactory();
		while (!exit) {
			for (auto& pair : this->keyMap) {
				if (pair.first.key != KEY_NULL) {
					EWatchCondition condition = pair.first.condition;

					// go through condition of the input action and check if it's met and call the doIfPressed or doIfNotPressed functions
					switch (condition) {
					case EWatchCondition::CONDITION_PRESSED:
						if (IsKeyPressed(pair.first.key)) {
							inputActionFactory->CallAction(pair.first);
						}
						break;

					case EWatchCondition::CONDITION_PRESSED_REPEAT:
						if (IsKeyPressedRepeat(pair.first.key)) {
							inputActionFactory->CallAction(pair.first);
						}
						break;

					case EWatchCondition::CONDITION_DOWN:
						if (IsKeyDown(pair.first.key)) {
							inputActionFactory->CallAction(pair.first);
						}
						break;

					case EWatchCondition::CONDITION_UP:
						if (IsKeyUp(pair.first.key)) {
							inputActionFactory->CallAction(pair.first);
						}
						break;

					default:
						break;

						
					}	
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		std::this_thread::yield();
	}


	void AddInput(KeyboardKey key, std::function<void()> doIfPressed) {
		this->keyMap[InputActionFactory::makeAction(key, doIfPressed, nullptr)] = false;
	}

	void AddInput(KeyboardKey key, std::function<void()> doIfPressed, std::function<void()> doIfNotPressed) {
		this->keyMap[InputActionFactory::makeAction(key, doIfPressed, doIfNotPressed)] = false;
	}


	void RemoveAllInputs() {
		this->keyMap.clear();
	}

private:

	class InputActionFactory {
	public:
		static inline InputAction makeAction(KeyboardKey key, std::function<void()> doIfPressed, std::function<void()> doIfNotPressed) {
			InputAction action;
			action.key = key;
			action.doIfPressed = doIfPressed;
			action.doIfNotPressed = doIfNotPressed;
			return action;
		}

		void CallAction(InputAction action) {
			try {
				if (action.doIfPressed != nullptr) {
					action.doIfPressed();
				}
				if (action.doIfNotPressed != nullptr) {
					action.doIfNotPressed();
				}
			}
			catch (std::exception e) {
				Logman::log(e.what());
			}
		}
	};


	// Calls first pair if key is pressed, second pair if key is not pressed (leave null if not needed)
	// WHY WONT THIS WOOOORRRKKKK HOLY HELL
	std::map<InputAction, bool> keyMap;
};