#pragma once
#include "../scripting/IScriptable.h"
#include "../registry/Registry.h"
#include "EUITypes.h"
#include "EDrawType.h"

class UIContainer;

class UIElement {
public:

	UIElement() {
		this->position = Vector2Add(this->offset, this->anchor);
		this->drawTime = EDrawType::DRAW_FINAL;
	}

	void draw() {
		UpdateInfo();
		if (debugMode) {
			DrawCircleV(cursorPos, 4.0f, YELLOW);
			DrawCircleV(mouseDelta, 8.0f, RED);
		}

		if (isActive && isVisible) {
			customDraw();
		}
	}

	// override this to add your own features
	virtual void customDraw() {
	}

	void onUpdate() {
		if (isActive) {
			if (this->checkDrawEligibility) {
				if (isActive || alwaysVisible) {
					this->drawable = true;
				}
				else {
					if (isVisible) {
						this->drawable = true;
					}
				}
				this->checkDrawEligibility = false;
			}

			UpdateInfo();
			customUpdate();
		}
	}

	virtual void customUpdate() {
	}

	static void UpdateInfo() {
		cursorPos = GetMousePosition();
		mouseDelta = GetMouseDelta();
	}

	virtual void onDestroy() {
	}

	void kill() {
		delete this;
	}

	void setContainer(UIContainer* container) {
		this->parent = container;
	}

	// globals

	// cursor crap
	static inline Vector2 cursorPos;
	static inline Vector2 mouseDelta;

	static inline bool debugMode = true;
	static inline bool inUIMode;

	// the id inside of it's container.
	int id;

	// it's "nickname" globally
	int globalID;

	Vector2 anchor;
	Vector2 position;
	Vector2 offset;

	Rectangle bounds;
	Rectangle outline;

	// use if you want to be able to move the element around.
	Vector2 velocity;

	int width;
	int height;
	int	scrollIndex;

	// persistance flag.
	bool alwaysVisible;
	bool shouldUpdate;
	bool isVisible;
	bool isActive;
	bool isHovered;
	// can 3d objects clip this?
	bool isClippable = false;
	// should post process affects get calculated for this aswell?
	bool affectedByPost;

	bool drawable = true;

	bool checkDrawEligibility;

	// whether or not the element is suicidal, and should be executed immediatly
	bool deleteMe = false;

	EDrawType drawTime;
	EUIType uiType;
	UIContainer* parent;
};

// The UI container not only contains all elements, but also manages them aswell.
class UIContainer {
public:

	virtual void update() {
		if (!isSleeping) {
			for (auto& element : children) {
				// check if it should be deleted.
				if (element.second->deleteMe) {
					element.second->onDestroy();
					killChild(element.second->id);
				}
				else {
					element.second->UpdateInfo();
					element.second->onUpdate();
				}
			}
		}
	}

	bool isAsleep() {
		return this->isSleeping == true;
	}

	// amimir
	void sleep() {
		this->isSleeping = true;
	}

	// ugh... 5 more minutes! please (he did not get 5 more minutes)
	void wake() {
		this->isSleeping = false;
	}

	// Let this container it is their time to shine!
	void drawChildren(EDrawType drawMode) {
		for (auto& element : children) {
			if (element.second->drawTime == drawMode) {
				element.second->UpdateInfo();
				element.second->draw();
			}
			else {
				continue;
			}
		}
	}

	void addChild(UIElement* element) {
		int newID = assignID();

		element->id = newID;

		element->setContainer(this);

		children[newID] = element;
	}

	// abduct the child and yeet it!
	UIElement* getChild(int id) {
		return children[id];
	}

	void clear() {
		children.empty();
	}

	const char* containerTag;

	int containerID;
	// threat eliminated! (It gets deleted next frame.)
	void killChild(int target) {
		this->children[target]->isVisible = false;
		this->children.erase(target);
		elements--;
	}
private:

	int elements = 0;

	int assignID() {
		return elements;
		elements++;
	}

	bool isSleeping = true;
	std::map<int, UIElement*> children;
};