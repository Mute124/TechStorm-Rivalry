#include "UIElement.h"

namespace TechStorm {
	void TechStorm::UIElement::init() {
	}

	void TechStorm::UIElement::drawElement() {}

	void TechStorm::UIElement::updateElement() {}

	void TechStorm::UIElement::onDestroy() {
		delete this;
	}

	void TechStorm::UIElement::setContainer(UIContainer* container) {
		this->parent = container;
	}

	void TechStorm::UIContainer::start() {
		UIElement::font = LoadFont("Data/gui/fonts/Tektur-VariableFont_wdth,wght.ttf");
	}

	void TechStorm::UIContainer::update() {
		if (!isSleeping) {
			std::function<void()> updateFunc = [this]() {
				for (auto& element : children) {

					// check if it should be deleted.
					if (element.second->deleteMe) {
						killChild(element.first);
						Logman::Log(TextFormat("Child #%i Killed", element.first));
					}
					else {
						if (element.second == nullptr) {
							continue;
						}
						else {
							element.second->updateElement();
						}
					}
				}
				};

			std::thread* updater = new std::thread(updateFunc);
			updater->detach();
		}
	}

	//

	bool TechStorm::UIContainer::isAsleep() const {
		return this->isSleeping == true;
	}

	// amimir

	void TechStorm::UIContainer::sleep() {
		this->isSleeping = true;
	}

	/*
	* Rise and shine, Mr.Freeman. Rise and... shine. Not that I... wish to imply you have been sleeping on the job. No one is more deserving of a rest...
	* and all the effort in the world would have gone to waste until... well, let's just say your hour has... come again.
	* The right man in the wrong place can make all the difference in the world. So, wake up, Mister Freeman. Wake up and... smell the ashes...
	*/

	void TechStorm::UIContainer::wake() {
		this->isSleeping = false;
	}

	// Let this container it is their time to shine!

	void TechStorm::UIContainer::drawChildren(EDrawType drawMode) {
		for (auto& element : children) {
			if (element.second->drawTime == drawMode && element.second != nullptr) {
				element.second->drawElement();
			}
			else {
				continue;
			}
		}
	}

	void TechStorm::UIContainer::onChildrenDraw() {}

	void TechStorm::UIContainer::addChild(UIElement* element) {
		int newID = assignID();

		element->id = newID;

		element->setContainer(this);

		children[newID] = element;
	}

	void TechStorm::UIContainer::onChildAdded() {}

	// abduct the child and yeet it!

	UIElement* TechStorm::UIContainer::getChild(int id) {
		return children[id];
	}

	void TechStorm::UIContainer::clear() {
		for (auto& element : children) {
			element.second->deleteMe = true;
		}
	}

	void TechStorm::UIContainer::onClear() {}

	// threat eliminated! (It gets deleted next frame.)

	void TechStorm::UIContainer::killChild(int target) {
		children.at(target)->onDestroy();
		children.erase(target);
	}

	void TechStorm::UIContainer::kill() {
		for (auto& child : children) {
			if (child.second != nullptr) {
				killChild(child.first);
			}
		}
	}

	void TechStorm::UIContainer::onChildKilled() {}

	// Use if you are a child element, signifying the container should exit, for example a button that exits the menu

	void TechStorm::UIContainer::requestKill() {
		shouldKill = true;
	}

	int TechStorm::UIContainer::assignID() {
		return elements;
		elements++;
	}
}
