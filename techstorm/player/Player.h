#pragma once
#include "../Common.h"
#include "../globalobj/Block.h"
#include "../inventory/Item.h"
#include "../inventory/EquipSlot.h"
#include "PlayerCharacter.h"
#include "../core/ui/UIElement.h"
#include "../core/ui/UIMan.h"
#include "Hand.h"
#include "../ui/Crosshair.h"

#define STARTINGHP 100
#define MAX_AFFLICTIONS 20

namespace TechStormRivalry {
	namespace Player {
		class PlayerController : public PlayerCharacter
		{
		protected:

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
			PlayerController* controller;
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

			PlayerController() {
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

			void draw(TechStorm::uVec2i position)
			{
				float percentage = calculatePercentage(hp, maxHP);

				DrawRectangle(position.x, position.y, 100, 20, BLACK);
				DrawRectangleLines(position.x, position.y, 100, 20, RED);
				DrawRectangle(position.x, position.y, 100 * percentage, 20, GREEN);
			};

			float hp;
			float maxHP;
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

			Vector3 getTarget()
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

		class Player : public PlayerController
		{
		private:
			bool startDriving = false;
			int maxHP = STARTINGHP;
		public:
			int cameraMode;
			bool doDraw = true;
			static inline CameraComp* cameraComponent;
			PlayerController* controller = new PlayerController(KEY_W, KEY_S, KEY_A, KEY_D, KEY_SPACE, KEY_C, cameraMode);
			bool isRunning;
			static inline Player* instance;
			Crosshair* crosshair;

			Player() {
			}

			// main constructor
			Player(TechStorm::uVec3f StartingPos, int MaxHP, const Model model, int CameraMode)
				: maxHP(MaxHP),
				cameraMode(CameraMode)
			{
				this->model = model;
				this->position = position;

				cameraComponent = new CameraComp(CameraData{
					   {0.0f, 0.0f, 4.0f},
					   {0.0f, 2.0f, 0.0f},
					   {0.0f, 2.0f, 0.0f},
					   45.0f,
					   0 });

				initCharacter(0.4f, 2.0f, 0.7f, 1.0f);
				instance = this;

				//this->gun = LoadModel("resources/Sniper_Rifle.glb");

				//this->gun.materials[0].shader = Game::renderers->forwardRenderer->pbrShader;
			};

			void onDestroy() const override
			{
				delete this;
			};

			void onUpdate()
			{
				tick();
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
				TechStorm::uVec3f forward = GetCameraForward(cameraComponent->getSelfCameraPointer());

				forward.y -= 0.5f;

				//DrawModel(this->gun, Vector3Add(this->cameraComponent->getPosition(), forward), 0.3f, WHITE);

				//DrawSphere(CameraToWorld(this->cameraComponent->getSelfCamera()), 0.1f, RED);

				// this->gun.transform = MatrixLookAt(CameraToWorld(this->cameraComponent->getSelfCamera()), forward, GetCameraUp(cameraComponent->getSelfCameraPointer()));
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
		};
	}
}
