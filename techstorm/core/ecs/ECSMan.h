#pragma once
#include "../scripting/ScriptManager.h"
#include "../registry/Registry.h"
#include "../logging/Logman.h"
#include "Component.h"
#include "Entity.h"
#include <stdlib.h>
#include <map>
#include <any>
#include <variant>

template<typename comp>
class Components_CSTR : public MRegistry_CSTR<T> {

public:

	void update() {
		
	}
	
	template<typename T>
	void addComponent(T comp) {
		
	}


protected:


};


class ComponentManager {
public:

	std::vector <Component*> comps;
};


/*
class ESCMan : public IScriptable, public MRegistry_Ext<int, Entity> {
public:

	// register a new entity
	void registerEntity(Entity* newEntity) {

		if (newEntity == nullptr) {
			// handle null entity.

		}
		else {
			if (newEntity->id == 0) {
				// assign it a unique ID;
				newEntity->id = makeID();
			}
			// Add logic here to register the new entity
			this->Add(newEntity);
		}



	}

	void kill(Vector3 position) {
		this->Remove(position);
	}

	void TestECS() {
		Logman::Log("ECS Testing..");
		bool pushTestSuccess = false;

		try {
			Entity* newEntity = new Entity();
			this->registerEntity(newEntity);
			pushTestSuccess = true;
		}
		catch (...) {

			Logman::Log("Push Test Failed");
		}

		if (pushTestSuccess) {
			Logman::Log("Push Test Success");
		}

		// test getCloset, give it a bunch of random entities and see if it works.
		try {
			for (int i = 0; i < 100; i++) {
				Entity* newEntity = new Entity();
				this->registerEntity(newEntity);
			}

			Entity* closest = getClosest(Vector3(0, 0, 0));


			Logman::Log(TextFormat("Closest Entity: %s", closest->id));


		} catch (...) {
			Logman::Log("Get Closest Test Failed");
		}
	}

	// bubble sort entities by distance and get the closest entity to a given position.
	Entity* getClosest(Vector3 position) {


Entity* closest = nullptr;
std::map<int, Entity*>* entities = getEntities();

if (entities) {
	float dist = 0;
	for (auto it = entities->begin(); it != entities->end(); it++) {
		if (closest == nullptr) {
			closest = it->second;
			dist = (Vector3Distance(it->first, position));
		}
		else {
			float newDist = (Vector3Distance(it->first, position));
			if (newDist < dist) {
				closest = it->second;
				dist = newDist;
			}
		}
	}
}
	}


private:
	static inline int idCounter = 0;

	int makeID() {
		idCounter++;
		return idCounter;
	}

	std::map<int, Entity*>* getEntities() {
		return this->getPtr();
	}
};

*/
