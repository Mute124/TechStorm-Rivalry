#pragma once
#include "../../Common.h"
#include "../gameScreen/MenuCamera.h"
#include "UIElement.h"

class UIMan {
public:
	UIMan() {
		addRogueContainer();
	}

	static inline Font fontTtf;
	static inline void init() {
	}
	void draw(EDrawType drawType) {
		for (auto& container : containers) {
			container.second->drawChildren(drawType);
		}
	}

	// IF ROGUE IT WILL OVERRIDE THE 0 INDEX!
	void pushContainer(UIContainer* container, bool wakeOnPush = false, bool isRogue = false) {
		if (!isRogue) {
			int newID = assignId();
			container->containerID = newID;

			container->wake();

			this->containers[newID] = container;
		}
		else {
			container->wake();

			this->containers[0] = container;
		}
	}

	void pushRogueElement(UIElement* element) {
		containers[0]->addChild(element);
	}

	// a container that holds all rogue UIElements. Always will be zero.
	void addRogueContainer() {
		pushContainer(new UIContainer(), true, true);
	}

	void clear(int id) {
	}

	static UIMan* getInstance() {
		return currentInstance;
	}

	void end() {
		delete this;
	}

	UIContainer* getContainer(int container) {
		return containers[container];
	}

	void update() {
		for (auto& container : containers) {
			container.second->update();
		}
	}
private:
	int containerCount = 1;

	int assignId() {
		return containerCount;
		containerCount++;
	}

	static inline UIMan* currentInstance;

	std::map<int, UIContainer*> containers;

	//MenuCamera* cam = new MenuCamera();
};