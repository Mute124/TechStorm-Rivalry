#pragma once
#include "../TechStorm.h"
#include "../gameScreen/MenuCamera.h"
#include "UIElement.h"

namespace TechStorm {
	/*
	* Manages UIElements, containers, and any UIElement derivatives.
	*
	* rogue elements are those that DO NOT belong to any container, but since elements need a parent container, they are put into the predesignated rogue container (always at index 0)
	*
	* TODO:
	*	Add push to container function
	*
	*/
	class UIMan {
	public:

		// constructor, creates the designated rogue container.
		UIMan() {
		}

		void initUIMan() {
			UIContainer::start();
			addRogueContainer();

			currentInstance = this;
			SetTextLineSpacing(48);
		}

		void drawUI(EDrawType drawType) {
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

		// push a rogue element
		void pushRogueElement(UIElement* element) {
			containers[0]->addChild(element);
		}

		// a container that holds all rogue UIElements. Always will be zero.
		void addRogueContainer() {
			pushContainer(new UIContainer(), true, true);
		}

		void removeContainer(int id) {
			this->containers.erase(id);
		}

		// TODO: this
		void clearUI(int id) {
		}

		void flushUI() {
			for (auto& cont : containers) {
				cont.second->clear();
			}
		}

		static UIMan* getUIInstance() {
			return currentInstance;
		}

		// murder the uiman, muahahaha
		void endUIMan() {
			delete this;
		}

		// get a UIcontainer
		UIContainer* getContainer(int container) {
			return containers[container];
		}

		// update ze elements.
		void updateUI() {
			for (auto& container : containers) {
				container.second->update();
			}
		}
	private:

		// set to 1 as 0 is always the rogue container
		int containerCount = 1;

		// get a free ID.
		int assignId() {
			return containerCount;
			containerCount++;
		}

		// global instance of this class.
		static inline UIMan* currentInstance;

		// holds what it says, containers!
		std::map<int, UIContainer*> containers;
	};
}
