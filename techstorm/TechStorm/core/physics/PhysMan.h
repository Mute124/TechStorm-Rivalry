#include "Layers.h"
#include <Jolt/Physics/PhysicsSystem.h>

#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Collision/Shape/HeightFieldShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>

class Jolt {
	void initJolt() {
	}

protected:

	JPH::JobSystem* mJobSystem = nullptr;
	JPH::PhysicsSystem* mPhysicsSystem = nullptr;
	JPH::BodyInterface* mBodyInterface = nullptr;
	JPH::DebugRenderer* mDebugRenderer = nullptr;
	JPH::TempAllocator* mTempAllocator = nullptr;
};
