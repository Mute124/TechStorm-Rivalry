#pragma once
#include "../scripting/ScriptManager.h"
#include "EComponentType.h"
#include "../obj/Gameobject.h"
#include "../registry/Registry.h"

template <typename T>
class ComponentBase abstract : public T {
public:
	T getComponent() {
		return this->comp;
	}

	void setComponent(T value) {
		this->comp = value;
	}

	EComponentType compType;
};

class Component abstract : public ComponentBase<Component> {
public:

	void set(std::any val) {
		this->compval = val;
	}

	std::any compval;
};

class RenderComponent abstract : public Component {
public:
	RenderComponent() {
		this->set(this);
	}
};

class ScriptedComponent abstract : public Component, public IScriptable {
public:

	ScriptedComponent() {
		this->set(this);
	}

	virtual void finalize() {
		
		ScriptManager::addScript(this);
	}

	void init() override {
		
	}

	void update() override {

	}

	void end() override {
		
	}

protected:
	IScriptable* script = nullptr;
};