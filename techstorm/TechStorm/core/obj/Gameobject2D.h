#pragma once
#include "Gameobject.h"

// TODO: implement into game object manager, add different draw options.
class GameObject2D abstract {
public:

	virtual void draw() {
	}

	virtual ~GameObject2D()
	{
	}

	virtual void onUpdate() {}; // Called every frame

	virtual void onDestroy() const = 0; // NOTE : This deletes the object and shall be overridden for custom behaviors
};
