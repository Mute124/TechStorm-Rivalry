#pragma once
#include "../ecs/Component.h"
#include "../utils/Task.h"

class InputComponent : public ScriptedComponent {
public:

	InputComponent(Task onTrigger, KeyboardKey trigger) : onTrigger(onTrigger), trigger(trigger) {
		this->init();
		
	}

	void setTrigger(KeyboardKey trigger) {
		this->trigger = trigger;
	}

	bool isTriggered() {
		return isTriggered;
	}

	void update() override {
		triggered = IsKeyPressed(trigger);
	}

	void init() override {
		triggered = false;
		
	}

	void end() override {

	}

private:
	KeyboardKey trigger;
	bool triggered;

	Task onTrigger;
};