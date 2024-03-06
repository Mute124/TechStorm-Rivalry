#pragma once
#include "../../common.h"
#include "Gameobject2D.h"
#include "../ECS/ECSMan.h"
#include "../assets/ObjectMaterial.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <functional>
#include <thread>

using namespace std;
class GameobjectManager;
class GameObjectComponent;

/*
* WARNING: ALL DERIVED CLASSES ARE SET AS THREADSAFE BY DEFAULT, YOU ARE RESPONSIBLE FOR CHANGING THIS FLAG IF CHILD IS NOT THREADSAFE!
* Please also note that IF IT IS NOT A DYNAMIC OBJECT, NEITHER IT NOR IT'S COMPONENTS WILL BE UPDATED!
*/
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

	virtual void preDraw() {
	}

	virtual bool isThreadSafe() {
		return threadSafe;
	}

	void addComponent(GameObjectComponent* component) {
		if (!hasComponents) {
			hasComponents = true;
		}
	}

	Vector3 position;
	Model model;
	float scale;
	Color tint;
	Shader shdr;
#ifdef DEBUG
	bool debugMode = true;
#else // DEBUG
	bool debugMode = false;
#endif

	bool isDynamic = false;
	bool threadSafe = true;
	bool hasComponents = false;

	int componentCount = 0;
	std::vector<GameObjectComponent*> components;

	friend class GameobjectManager;
};

// Components only get updated ONCE per frame, Make sure to account for this!
class GameObjectComponent abstract {
public:
	bool isActive = true;
	bool threadSafe = false;

	unsigned int id;
	GameObject* parent;

	virtual void init() {
	}

	virtual void update() {
	}

	virtual void destroy() {
		delete this;
	}
};

class GameobjectManager final {
public:
	vector<GameObject*> threadSafeObjects; // objects that are threadsafe
	vector<GameObject*> nonThreadSafeObjects; // objects that are not threadsafe.
	static inline GameobjectManager* instance;

	GameobjectManager() {
		instance = this;
	}
	void renderObjects()
	{
		for (auto& obj : threadSafeObjects)
		{
			// check for dynamicy.
			if (obj->isDynamic) {
				obj->draw();
				obj->onUpdate();
			}
			else {
				continue;
			}
		}
	}

	// kill them all! EVEN THE CHILDREN
	void flushBuffer()
	{
		// we have to use this implementation due to each object can have their own behavior.
		for (auto& obj : threadSafeObjects)
		{
			obj->onDestroy();
		}

		for (auto& obj : nonThreadSafeObjects) {
			obj->onDestroy();
		}
	}

	void updateObjects() {
		instance = this;
		// update threadsafe objects on another thread
		function<void()> threadsafeUpdate = [this]() {
			for (auto& obj : threadSafeObjects) {
				if (obj->isDynamic) {
					if (obj->hasComponents) {
						for (auto& comp : obj->components) {
							if (comp->threadSafe && comp->isActive) {
								comp->update();
							}
							else {
								continue;
							}
						}
					}

					obj->onUpdate();
				}
				else {
					continue;
				}
			}
			};

		thread threadSafeUpdating(threadsafeUpdate);
		threadSafeUpdating.detach(); // detach

		// update non-threadsafe objects in local thread
		for (auto& obj : nonThreadSafeObjects)
		{
			if (obj->isDynamic) {
				if (obj->hasComponents) {
					for (auto& comp : obj->components) {
						if (!comp->threadSafe && comp->isActive) {
							comp->update();
						}
						else {
							continue;
						}
					}
				}
				obj->onUpdate();
			}
			else {
				continue;
			}
		}
	}

	void pushObject(GameObject* obj) {
		if (obj->isThreadSafe()) {
			threadSafeObjects.push_back(obj);
		}
		else {
			nonThreadSafeObjects.push_back(obj);
		}
	}
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
