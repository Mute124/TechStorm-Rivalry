#pragma once
#include "../../common.h"
#include "Gameobject2D.h"
#include "../ECS/ECSMan.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>



using namespace std;

class GameObject abstract 
{
public:

	virtual void draw() abstract {

		Logman::Log("Gameobj");
	}
	virtual ~GameObject()
	{

	}

	virtual void onUpdate() {}; // Called every frame

	virtual void onDestroy() const = 0; // NOTE : This deletes the object and shall be overridden for custom behaviors

	Vector3 position;
	Model model;
	float scale;
	Color tint;
	Shader shdr;
};

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

//	void renderObjects2D() {
	//	for (auto& obj : objects2DVector) {
			//obj->draw();
		//}
	//}

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

//	void update2D() {
//		for (auto& obj : objects2DVector) {
//			obj->onUpdate();
	//	}
	//}

	void pushObject(GameObject* obj) {
		objectsVector.push_back(obj);
	}

	//void pushObject2D(GameObject2D* obj) {
		//objects2DVector.push_back(obj);
	//}

	vector<GameObject*> objectsVector;
	//vector<GameObject2D*> objects2DVector;
};

// Example game object
class ExampleObject : public GameObject {
public:
	ExampleObject(/*Initialization Variables*/) {
		// Startup code. Done only once
		
	}
	void draw() override {
		// On draw
	}
	void onUpdate() override {
		// tasks to do on each update. 
	}
	// What to do when destroyed.
	void onDestroy() const override {
		delete this;
	}

	// Other methods


	// Other variables.

private:
	// Variables that will only be used by this class
};