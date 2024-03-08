#pragma once
#include "../scripting/IScriptable.h"
#include "../registry/Registry.h"
#include "EUITypes.h"
#include "EDrawType.h"

class UIContainer;

// Note, Icons are not natively supported. You have to implement the logic yourself sorry.
class UIElement {
public:
	static inline Vector2 cursorPos = Vector2Zero();
	static inline Vector2 mouseDelta = Vector2Zero();
	static inline bool debugMode = true;
	static inline Font font;
	const char* text = "null";
	int id = 0; // the id inside of it's container.
	float fontSize = (float)font.baseSize;
	float fontSpacing = 2.0f;
	float opacity = 100.0f;
	int globalID = 0; // it's "nickname" globally
	Vector2 anchor = Vector2Zero();
	Vector2 position = Vector2Zero();
	Vector2 offset = Vector2Zero();
	Rectangle bounds = Rectangle{ 0.0f, 0.0f, 0.0f, 0.0f };
	Rectangle outline = Rectangle{ 0.0f, 0.0f, 0.0f, 0.0f };
	Color color = BLUE;
	Vector2 velocity = Vector2Zero(); // use if you want to be able to move the element around.
	int width = 0;
	int height = 0;
	int	scrollIndex = 0;
	bool alwaysVisible = false;	// persistance flag.
	bool isVisible = false;
	bool isActive = true;
	bool isHovered = false;
	bool isClippable = false;// can 3d objects clip this?
	bool affectedByPost = false; // should post process affects get calculated for this aswell?
	bool drawable = true;
	bool checkDrawEligibility = false;
	bool deleteMe = false;	// whether or not the element is suicidal, and should be executed immediatly
	bool outlined = false;
	bool opacityDirty = true;
	EDrawType drawTime = DRAW_FINAL;
	EUIType uiType = EUI_NULL;
	UIContainer* parent;

	UIElement() {
		this->position = Vector2Add(this->offset, this->anchor);

		//this->bounds.width = Vector2Distance()
		this->drawTime = EDrawType::DRAW_FINAL;
	}

	UIElement(Vector2 anchor, Vector2 offset, int width, int height, Color color) : anchor(anchor), offset(offset), width(width), height(height), color(color) {
		this->position = Vector2Add(this->offset, this->anchor);

		this->bounds.height = Vector2Distance(anchor, offset);
		this->bounds.width = Vector2Distance(anchor, offset);
		this->bounds.x = this->position.x;
		this->bounds.y = this->position.y;

		//this->bounds.width = Vector2Distance()
		this->drawTime = EDrawType::DRAW_FINAL;
	}

	void draw() {
		UpdateInfo();

		/*
		*
		*		if (debugMode) {
			// draw element bounds dimensions.
			DrawTextEx(font, TextFormat("Bounds : (w: %f, h: %f)", this->bounds.width, this->bounds.height), Vector2{ this->bounds.x, this->bounds.y + (this->fontSize / 2) }, this->fontSize / 2, this->fontSpacing, GREEN);

			// draw anchor pos text
			Vector2 anchorText = Vector2{ this->anchor.x, this->anchor.y + (this->fontSize) };
			DrawTextEx(font, TextFormat("Anchor : (x: %f, y: %f)", this->anchor.x, this->anchor.y), anchorText, this->fontSize / 2, this->fontSpacing, GREEN);

			// draw anchor.
			DrawCircleV(this->anchor, 5.0f, RED);
		}
		*/

		if (isActive && isVisible) {
			if (this->uiType = EUI_TEXT) {
				DrawTextEx(font, this->text, this->position, this->fontSize, this->fontSpacing, this->color);
			}

			customDraw();
		}
	}

	// override this to add your own features
	virtual void customDraw() {}

	void onUpdate() {
		if (isActive) {
			if (this->opacityDirty) {
				this->color.a = this->opacity;
				this->opacityDirty = false;
			}
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

			this->anchor = cursorPos;
			this->position = Vector2Add(this->offset, this->anchor);

			this->bounds.height = height;
			this->bounds.width = width;
			this->bounds.x = this->position.x;
			this->bounds.y = this->position.y;
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

	void setOpacity(float opacity) {
		this->opacity = opacity;
		this->opacityDirty = true;
	}

protected:

	void SetType(EUIType type) {
		this->uiType = type;
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
			customUpdate();
		}
	}

	virtual void customUpdate() {
	}

	//
	bool isAsleep() {
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
			if (element.second->drawTime == drawMode) {
				element.second->UpdateInfo();
				element.second->draw();
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
		children.empty();
	}

	virtual void onClear() {}

	const char* containerTag;

	int containerID;
	// threat eliminated! (It gets deleted next frame.)
	void killChild(int target) {
		this->children[target]->isVisible = false;
		this->children.erase(target);
		elements--;
	}

	virtual void onChildKilled() {}
private:

	int elements = 0;

	int assignID() {
		return elements;
		elements++;
	}

	bool isSleeping = true;
	std::map<int, UIElement*> children;
};
