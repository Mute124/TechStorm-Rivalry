#pragma once
#include <raylib.h>
#include "../TechStorm.h"

namespace TechStorm {
	class CameraData
	{
	public:
		uVec3f position; // Camera position
		uVec3f target;   // Camera target it looks-at
		uVec3f up;       // Camera up vector (rotation over its axis)
		float fovy;       // Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
		int projection;   // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC

		Camera toCamera() {
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

	// You can either use this directly, or you may implement your own as all functions are virtual :)
	class PCamera {
	protected:
#ifdef TECHSTORM_ENGINE_3D
		Camera m_camera;
		int m_cameraMode = CAMERA_FIRST_PERSON;
#else
		Camera2D m_camera;
#endif // TECHSTORM_ENGINE_3D

		float m_moveSpeed;
		float mouseSensitivity = 0.05f;
		KeyboardKey forward, backward, left, right, jump, crouch;
	public:

		virtual void updateCamera() {
		}

		virtual uVec3f getPosition()
		{
			return this->m_camera.position;
		}

		virtual uVec3f getTarget()
		{
			return this->m_camera.target;
		}

		virtual uVec3f getUp()
		{
			return this->m_camera.up;
		}
		virtual float getFOVY()
		{
			return this->m_camera.fovy;
		}

		virtual float getProjection()
		{
			return this->m_camera.projection;
		}

		virtual void getPosition(uVec3f value)
		{
			this->m_camera.position = value;
		}

		virtual void setTarget(uVec3f value)
		{
			this->m_camera.target = value;
		}

		virtual void setUp(uVec3f value)
		{
			this->m_camera.up = value;
		}

		virtual void setFOVY(float value)
		{
			this->m_camera.fovy = value;
		}

		virtual void setProject(float value)
		{
			this->m_camera.projection = value;
		}

		static Camera toCamera(CameraData data) {
			return data.toCamera();
		}

		virtual Camera getSelfCamera() {
			return this->m_camera;
		}

		virtual Camera* getSelfCameraPointer() {
			return &this->m_camera;
		}
	};
}
