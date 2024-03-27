#pragma once
#include <raylib.h>
#include "uVec3.h"
namespace TechStorm {
	class CameraData
	{
	public:
		uVec3f position; // Camera position
		uVec3f target;   // Camera target it looks-at
		uVec3f up;       // Camera up vector (rotation over its axis)
		float fovy;       // Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
		int projection;   // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
		bool isMain;

		CameraData() {}

		CameraData(Camera camera) {
			this->position = camera.position;
			this->target = camera.target;
			this->up = camera.up;
			this->fovy = camera.fovy;
			this->projection = camera.projection;
		}

		Camera toCamera() {
			return Camera{
				position,
				target,
				up,
				fovy,
				projection
			};
		}

		operator Camera() const {
			return 			Camera{
				position,
				target,
				up,
				fovy,
				projection
			};
		}
	};

	class uCamera : virtual private CameraData {
	private:
		Camera m_camera;
		bool m_isMain;

	public:

		uCamera(CameraData data) : m_camera(data), m_isMain(data.isMain) {
		}
	};
}
