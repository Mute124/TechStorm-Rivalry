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

	bool isConditionMet;

	bool operator<(const InputAction& other) const {
		// Define the logic for comparison here
		// For example:
		return this->key < other.key;
	}
};

class InputLayer final : public Layer {
public:



	/**
	 * @brief Pure virtual function to initialize the layer
	 */
	void init() final override {

	}

	// goes through map, check if key is pressed, and calls doIfPressed or doIfNotPressed depending on if not a nullptr. Also checks it's watch condition and follows it.
	// Note: THIS IS A THREADED FUNCTION
	void update() {
		Logman::Log("InputLayer::update()");

		InputActionFactory* factory = new InputActionFactory();
		while (!exit) {
			for (auto& pair : this->keyMap) {
				KeyboardKey watchKey = pair.first->key;

				EWatchCondition condition = pair.first->condition;
				watchKey = pair.first->key;
				bool isConditionMet = IsKeyDown(watchKey);
				

				if (isConditionMet) {
					factory->CallAction(pair.first);
					pair.second = pair.first->isConditionMet;
				}
			}
		}

		this->RemoveAllInputs();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	void AddInput(KeyboardKey key, std::function<void()> doIfPressed) {
		if (key != 0 && doIfPressed != nullptr) {
			this->keyMap[InputActionFactory::makeAction(key, doIfPressed, nullptr)] = false;
		}
	}

	void AddInput(KeyboardKey key, std::function<void()> doIfPressed, std::function<void()> doIfNotPressed) {
		if (key != 0 && doIfPressed != nullptr && doIfNotPressed != nullptr) {
			this->keyMap[InputActionFactory::makeAction(key, doIfPressed, doIfNotPressed)] = false;
		}
	}

	void AddInput(InputAction* action) {
		this->keyMap[action] = false;
	}

	void RemoveAllInputs() {
		this->keyMap.clear();
	}

private:

	class InputActionFactory {
	public:

		static inline InputAction* makeAction(KeyboardKey key, std::function<void()> doIfPressed, std::function<void()> doIfNotPressed) {
			InputAction action;
			action.key = key;
			action.doIfPressed = doIfPressed;
			action.doIfNotPressed = doIfNotPressed;
			return new InputAction(action);
		}

		void CallAction(InputAction* action) {
			try {
				action->isConditionMet = true;
				if (action->doIfPressed != nullptr) {
					action->doIfPressed();
				}
				if (action->doIfNotPressed != nullptr) {
					action->doIfNotPressed();
				}
			}
			catch (std::exception& e) {
				Logman::Error(
					TextFormat(
						"Error in InputActionFactory::CallAction: {} : %s",
						e.what()
					)
				);
			}
		}
	};

	// Calls first pair if key is pressed, second pair if key is not pressed (leave null if not needed)
	// WHY WONT THIS WOOOORRRKKKK HOLY HELL
	std::map<InputAction*, bool, std::less<InputAction*>> keyMap;
};