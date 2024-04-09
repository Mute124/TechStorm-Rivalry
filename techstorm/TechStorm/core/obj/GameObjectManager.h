#pragma once
#include "Gameobject.h"

#include "../../Common.h"

class GameobjectManager final {
public:

	void renderObjects()
	{
		for (auto& obj : threadSafeObjects)
		{
			obj->draw();
			obj->onUpdate();
		}
	}

	void flushBuffer()
	{
		// we have to use this implementation due to each object can have their own behavior.
		for (auto& obj : threadSafeObjects)
		{
			obj->onDestroy();
		}
	}

	void updateObjects() {
		for (auto& obj : threadSafeObjects)
		{
			obj->onUpdate();
		}
	}

	void pushObject(GameObject* obj) {
		threadSafeObjects.push_back(obj);
	}

	std::vector<GameObject*> threadSafeObjects;

	/*
	*
	* 	void renderObjects2D() {
		for (auto& obj : objects2DVector) {
			obj->draw();
		}
	}
	void update2D() {
		for (auto& obj : objects2DVector) {
			obj->onUpdate();
		}
	}
	* std::vector<GameObject2D*> objects2DVector;
	*/
};
