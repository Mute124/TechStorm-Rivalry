#pragma once
#include "../../Common.h"
#include "../../globalobj/Block.h"
#include "../../inventory/Item.h"
#include "../../inventory/EquipSlot.h"

#include "CameraComp.h"
#include "PlayerHealthComp.h"
#include "PlayerController.h"

#include "PlayerCharacter.h"

#define STARTINGHP 100
#define MAX_AFFLICTIONS 20



class Player : public GameObject, public PlayerCharacter
{
public:
	Player() {}

	// main constructor
	Player(Vector3 StartingPos, int MaxHP, const Model model, int CameraMode)
		: position(StartingPos),
		maxHP(MaxHP),
		model(model),
		cameraMode(CameraMode)
	{
		cameraComponent = new CameraComp(CameraData{
			   {0.0f, 0.0f, 4.0f},
			   {0.0f, 2.0f, 0.0f},
			   {0.0f, 2.0f, 0.0f},
			   45.0f,
			   CAMERA_PERSPECTIVE });


		healthComp = new PlayerHealthComp(maxHP);
		instance = this;
	};

	void onDestroy() const override
	{
		delete this;
	};

	void onUpdate() override
	{
		if (cameraMode != CAMERA_FIRST_PERSON) {
			if (this->doDraw) {
				DrawModel(model, this->cameraComponent->getPosition(), 0.2f, GREEN);
			}
		}

		if (controller->canMove) {
			controller->update(cameraComponent->getSelfCameraPointer());
		}

		if (IsKeyDown(KEY_F)) {
			startDriving = true;
		}

		if (IsKeyDown(KEY_V)) {
			startDriving = false;
		}


		// View Sway

	

		if (startDriving) {
			drive();
		}




	};
	// sends player data to the games render
	void draw() override
	{
	}

	// is this even fucking used???
	void drive() {
		CameraMoveForward(cameraComponent->getSelfCameraPointer(), 0.01f, false);
	}

	// do not fucking touch this or it does some voodoo shit.
	virtual ~Player()
	{
		delete cameraComponent;
		delete controller;
		delete this;
	}


	Model model; // Player model
	int cameraMode;

	bool doDraw = true;

	static inline CameraComp* cameraComponent;

	PlayerController* controller = new PlayerController(KEY_W, KEY_S, KEY_A, KEY_D, KEY_SPACE, KEY_C, cameraMode);


	bool isRunning;
	PlayerHealthComp* healthComp;

	static inline Player* instance;

private:

	bool startDriving = false;

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

	// KeyboardKey *CurrentKeyDown;
	Vector3 position;
	Mesh mesh;

	int maxHP = STARTINGHP;
};

