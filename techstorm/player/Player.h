#pragma once
#include "../Common.h"
#include "../globalobj/Block.h"
#include "../inventory/Item.h"
#include "../inventory/EquipSlot.h"

#include "CameraComp.h"
#include "PlayerHealthComp.h"
#include "PlayerController.h"

#include "PlayerCharacter.h"

#define STARTINGHP 100
#define MAX_AFFLICTIONS 20



class Player : public PlayerCharacter
{
public:
	Player() {}

	// main constructor
	Player(Vector3 StartingPos, int MaxHP, const Model model, int CameraMode)
	{
		this->initCharacter(1.5f, 0.5f, -1.0f, 0.5f);
		this->healthBar = new HealthBar();
		
		this->position = StartingPos;
		this->model = model;

		this->cameraMode = CameraMode;
	};

	void init() {

	}


	// do not fucking touch this or it does some voodoo shit.
	virtual ~Player() {
		delete this;
	}

	void onDestroy() const override{

	}
	bool doDraw = true;

private:

	// why, just why
	static void CheckForBlockPlacement(MouseButton Trigger, Ray ray)
	{
		/*
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					std::vector<GameObject *> objects = RequestObjectList();
					// Loop through all the objects and check for a collision, then poof!
					for (auto &obj : objects)
					{
						if (obj->GetType() == BLOCK)
						{
							Block *block = static_cast<Block *>(obj);

							// Check for a collision between the mouse ray and the block's
							// bounding box
							if (Global::Math::CheckCollisionRayBox(ray, block->GetBounds(), NULL))
							{
								// Remove the block from the vector and free its memory
								std::vector<GameObject *>::iterator it =
									std::find(objects.begin(), objects.end(), obj);
								if (it != objects.end())
								{
									objects.erase(it);
								}
								break;
							}
						}
					}
				}*/
	}
};

