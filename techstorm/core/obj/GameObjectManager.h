#pragma once
#include "Gameobject.h"

#include "../../Common.h"

class GameobjectManager final {
public:

	void renderObjects()
	{
		for (auto& obj : objectsVector)
		{
			obj->draw();
			obj->onUpdate();
		}
	}



	void flushBuffer()
	{
		// we have to use this implementation due to each object can have their own behavior.
		for (auto& obj : objectsVector)
		{
			obj->onDestroy();
		}
	}

	void updateObjects() {

		for (auto& obj : objectsVector)
		{
			obj->onUpdate();
		}
	}


	void pushObject(GameObject* obj) {
		objectsVector.push_back(obj);
	}

	std::vector<GameObject*> objectsVector;
	

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