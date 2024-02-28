#pragma once
#include "../scripting/IScriptable.h"
#include "../registry/Registry.h"
#include "EUITypes.h"
#include "EDrawType.h"

class UIContainer;

class UIElement {
public:
	static inline Vector2 cursorPos;
	static inline Vector2 mouseDelta;
	static inline bool debugMode = true;
	static inline bool inUIMode;
	static inline Font font = LoadFont("Data/gui/fonts/Tektur-VariableFont_wdth,wght.ttf");
	const char* text;
	int id; // the id inside of it's container.
	float fontSize = (float)font.baseSize;
	float fontSpacing = 2.0f;
	int globalID; // it's "nickname" globally
	Vector2 anchor = Vector2Zero();
	Vector2 position = Vector2Zero();
	Vector2 offset = Vector2Zero();
	Rectangle bounds;
	Rectangle outline;
	Color color = BLUE;
	Vector2 velocity = Vector2Zero(); // use if you want to be able to move the element around.
	int width;
	int height;
	int	scrollIndex;
	bool alwaysVisible;	// persistance flag.
	bool shouldUpdate;
	bool isVisible;
	bool isActive;
	bool isHovered;
	bool isClippable = false;// can 3d objects clip this?
	bool affectedByPost = false; // should post process affects get calculated for this aswell?
	bool drawable = true;
	bool checkDrawEligibility;
	bool deleteMe = false;	// whether or not the element is suicidal, and should be executed immediatly
	EDrawType drawTime;
	EUIType uiType = EUI_NULL;
	UIContainer* parent;

	UIElement() {
		this->position = Vector2Add(this->offset, this->anchor);
		this->drawTime = EDrawType::DRAW_FINAL;
	}

	void draw() {
		UpdateInfo();
		if (debugMode) {
		}

		if (isActive && isVisible) {
			if (this->uiType == EUI_TEXT) {
			}

			switch (this->uiType)
			{
			case EUI_TEXT:
				DrawTextEx(font, this->text, this->position, this->fontSize, this->fontSpacing, this->color);
				break;
			default:
				break;
			}

			customDraw();
		}
	}

	// override this to add your own features
	virtual void customDraw() {}

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

protected:

	void SetType(EUIType type) {
		this->uiType = type;
	}
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
