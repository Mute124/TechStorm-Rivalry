#pragma once
#include "../../Common.h"
#include "../../globalobj/Block.h"
#include "../../inventory/Item.h"
#include "../../inventory/EquipSlot.h"

#define STARTINGHP 100
#define MAX_AFFLICTIONS 20

class PlayerController
{
private:

	int mode;
	float speed;
	float tiltSpeed;
	const float maxTiltRight = 10.0f; // Positive
	const float maxTiltLeft = -10.0f; // Negative
	float crouchSpeed;

	float screenTilt;

	float mouseSensitivity = 0.05f;

	KeyboardKey forward, backward, left, right, jump, crouch, tiltLeft, tiltRight;

	// needs to be optimized, technically we dont need parameters, we can just use this classes variable for it.
	float CalculateCameraTilt() {
		static const float NOCHANGE = 0.0f;

		return NOCHANGE;
	}
public:

	bool isRunning = false;
	bool canMove = true;
	bool isGrounded = false;


	float walkSpeed = 0.03f;
	float runChangeFactor = 43.33f;

	PlayerController(KeyboardKey Forward, KeyboardKey Backward, KeyboardKey Left, KeyboardKey Right, KeyboardKey Jump, KeyboardKey Crouch, int mode) : forward(Forward), backward(Backward), left(Left), right(Right), jump(Jump), crouch(Crouch), mode(mode)
	{
#ifndef tiltLeft
		tiltLeft = KEY_Q;
#endif // !tiltLeft
#ifndef tiltRight
		tiltRight = KEY_E;
#endif // !tiltRight
	}

	void setSpeed(float speed) {
		this->speed = speed;
	}

	void update(Camera* camera)
	{

		if (!this->isRunning) {
			this->isRunning = false;
			setSpeed(this->walkSpeed); //m/s
		}
		else {
			this->isRunning = true;
			setSpeed(this->walkSpeed * runChangeFactor); //m/s
		}
		// Camera PRO usage example (EXPERIMENTAL)
		// This new camera function allows custom movement/rotation values to be directly provided
		// as input parameters, with this approach, rcamera module is internally independent of raylib inputs
		UpdateCameraPro(camera,
			Vector3{
				(IsKeyDown(forward) || IsKeyDown(KEY_UP)) * speed -      // Move forward-backward
				(IsKeyDown(backward) || IsKeyDown(KEY_DOWN)) * speed,
				(IsKeyDown(right) || IsKeyDown(KEY_RIGHT)) * speed -   // Move right-left
				(IsKeyDown(left) || IsKeyDown(KEY_LEFT)) * speed,
				(IsKeyDown(jump)) * speed -                                                 // Move up-down
				(IsKeyDown(crouch)) * speed
			},
			Vector3{
				GetMouseDelta().x * mouseSensitivity,                            // Rotation: yaw
				GetMouseDelta().y * mouseSensitivity,                            // Rotation: pitch
				CalculateCameraTilt()                // Rotation: roll
			},

			GetMouseWheelMove() * 2.0f);                              // Move to target (zoom)
	}
};
class HealthBar
{
public:
	float calculatePercentage(float hp, float max_hp)
	{
		float percentage = (float)hp / (float)max_hp;
		return percentage;
	}

	void draw(Vector2 position)
	{
		float percentage = calculatePercentage(hp, maxHP);

		DrawRectangle((int)position.x, (int)position.y, 100, 20, BLACK);
		DrawRectangleLines((int)position.x, (int)position.y, 100, 20, RED);
		DrawRectangle((int)position.x, (int)position.y, 100 * percentage, 20, GREEN);
	};

	float hp;
	float maxHP;
};
class PlayerHealthComp
{
public:
	HealthBar* healthBar;

	PlayerHealthComp(int maxHP)
	{
		healthBar = new HealthBar();

		healthBar->hp = 100;
		healthBar->maxHP = maxHP;
	}

	~PlayerHealthComp() {
		delete this;
	}

	void damagePlayer(float damage)
	{
		healthBar->hp -= damage;
	}

	void healPlayer(int heal)
	{
		healthBar->hp += heal;
	}

	int getMaxHealth()
	{
		return healthBar->maxHP;
	}

	int getHealth()
	{
		return healthBar->hp;
	}
};
class CameraData
{
public:
	Vector3 position; // Camera position
	Vector3 target;   // Camera target it looks-at
	Vector3 up;       // Camera up vector (rotation over its axis)
	float fovy;       // Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
	int projection;   // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC

	Camera constructToCamera() {
		Camera camera = {
			position,
			target,
			up,
			fovy,
			projection
		};
		return camera;
	}
};

class CameraComp
{
public:
	CameraComp(CameraData cameradata) : camera(cameradata.constructToCamera()) {
	}

	Vector3 getPosition()
	{
		return this->camera.position;
	}

	Vector3 setTarget()
	{
		return this->camera.target;
	}

	Vector3 getUp()
	{
		return this->camera.up;
	}
	float getFOVY()
	{
		return this->camera.fovy;
	}

	float getProjection()
	{
		return this->camera.projection;
	}

	void getPosition(Vector3 value)
	{
		this->camera.position = value;
	}

	void setTarget(Vector3 value)
	{
		this->camera.target = value;
	}

	void setUp(Vector3 value)
	{
		this->camera.up = value;
	}

	void setFOVY(float value)
	{
		this->camera.fovy = value;
	}

	void setProject(float value)
	{
		this->camera.projection = value;
	}

	Camera toCamera(CameraData data) {
		return data.constructToCamera();
	}

	Camera getSelfCamera() {
		return this->camera;
	}

	Camera* getSelfCameraPointer() {
		return &this->camera;
	}

private:

	Camera camera;
};

class Player : public GameObject
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

