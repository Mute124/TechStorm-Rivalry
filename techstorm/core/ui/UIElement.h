#pragma once
#include "../TechStorm.h"
#include "../logging/Logman.h"
#include "../registry/Registry.h"
#include "EUITypes.h"
#include "EDrawType.h"

namespace TechStorm {
	class UIContainer;

	class BareUIElement;

	// Note, Icons are not natively supported. You have to implement the logic yourself sorry.
	class UIElement {
	public:
		static inline Font font;
		int id = 0; // the id inside of it's container.
		float fontSize = (float)font.baseSize;
		float fontSpacing = 2.0f;
		int globalID = 0; // it's "nickname" globally
		Vector2 anchor = Vector2Zero();
		bool alwaysVisible = false;	// persistance flag.
		bool isVisible = false;
		bool isActive = true;
		bool drawable = true;
		bool deleteMe = false;	// whether or not the element is suicidal, and should be executed immediatly
		EDrawType drawTime = DRAW_FINAL;
		UIContainer* parent;

		virtual void init() {}

		virtual void drawElement() {}
		virtual void updateElement() {}

		virtual void onDestroy() {
			delete this;
		}

		void setContainer(UIContainer* container) {
			this->parent = container;
		}
	};

	// The UI container not only contains all elements, but also manages them aswell.
	class UIContainer {
	public:

		static void start() {
			UIElement::font = LoadFont("Data/gui/fonts/Tektur-VariableFont_wdth,wght.ttf");
		}

		virtual void update() {
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
		bool isAsleep() const {
			return this->isSleeping == true;
		}

		// amimir
		void sleep() {
			this->isSleeping = true;
		}

		/*
		* Rise and shine, Mr.Freeman. Rise and... shine. Not that I... wish to imply you have been sleeping on the job. No one is more deserving of a rest...
		* and all the effort in the world would have gone to waste until... well, let's just say your hour has... come again.
		* The right man in the wrong place can make all the difference in the world. So, wake up, Mister Freeman. Wake up and... smell the ashes...
		*/
		void wake() {
			this->isSleeping = false;
		}

		// Let this container it is their time to shine!
		void drawChildren(EDrawType drawMode) {
			for (auto& element : children) {
				if (element.second->drawTime == drawMode && element.second != nullptr) {
					element.second->drawElement();
				}
				else {
					continue;
				}
			}
		}

		virtual void onChildrenDraw() {}

		void addChild(UIElement* element) {
			int newID = assignID();

			element->id = newID;

			element->setContainer(this);

			children[newID] = element;
		}

		virtual void onChildAdded() {}

		// abduct the child and yeet it!
		UIElement* getChild(int id) {
			return children[id];
		}

		void clear() {
			for (auto& element : children) {
				element.second->deleteMe = true;
			}
		}

		virtual void onClear() {}

		const char* containerTag;

		int containerID;

		// threat eliminated! (It gets deleted next frame.)
		void killChild(int target) {
			children.at(target)->onDestroy();
			children.erase(target);
		}

		void kill() {
			for (auto& child : children) {
				if (child.second != nullptr) {
					killChild(child.first);
				}
			}
		}

		virtual void onChildKilled() {}

		// Use if you are a child element, signifying the container should exit, for example a button that exits the menu
		virtual void requestKill() {
			shouldKill = true;
		}

	protected:
		bool shouldKill = false;
	private:

		int elements = 0;

		int assignID() {
			return elements;
			elements++;
		}

		bool isSleeping = true;
		std::map<int, UIElement*> children;
	};
}
