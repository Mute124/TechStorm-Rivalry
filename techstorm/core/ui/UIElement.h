#pragma once
#include "UIMan.h"



class UIElement abstract {
public:

	virtual void draw() = 0;

	virtual void update() = 0;

	virtual void onHover() = 0;

	virtual void onClick() = 0;

	virtual void onRelease() = 0;

	virtual void onMove() = 0;

	virtual void onScroll() = 0;

	virtual void onKey() = 0;

	virtual void onChar() = 0;



protected:

	int id;

	Vector2 anchor;
	Vector2 position;

	// use if you want to be able to move the element around.
	Vector2 velocity;

	int width;
	int height;

	bool isVisible;
	bool isActive;
	bool isHovered;

	friend class UIMan;
};

class UIContainer : public UIElement {
public:

	virtual void draw() = 0;

	virtual void update() = 0;

	virtual void onHover() = 0;

	virtual void onClick() = 0;

	virtual void onRelease() = 0;

	virtual void onMove() = 0;

	virtual void onScroll() = 0;

	virtual void onKey() = 0;

	virtual void onChar() = 0;

	protected:
		std::vector<UIElement*> children;
};

// only draw and update need to be defined. 
class SimpleUIElement abstract : public UIElement {
public:

	virtual void draw() = 0;

	virtual void update() = 0;

	virtual void onHover() final override {};

	virtual void onClick() final override {};

	virtual void onRelease() final override {};

	virtual void onMove() final override {};

	virtual void onScroll() final override {};

	virtual void onKey() final override {};

	virtual void onChar() final override {};

};