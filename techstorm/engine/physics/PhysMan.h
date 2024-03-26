#include "Layers.h"
#include <Jolt/Physics/PhysicsSystem.h>

#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Collision/Shape/HeightFieldShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>

class Jolt {
	Jolt() {
	}
	// Set the physics system
	virtual void	SetPhysicsSystem(JPH::PhysicsSystem* inPhysicsSystem) { mPhysicsSystem = inPhysicsSystem; mBodyInterface = &inPhysicsSystem->GetBodyInterface(); }

	// Set the job system
	void			SetJobSystem(JPH::JobSystem* inJobSystem) { mJobSystem = inJobSystem; }

	// Set the temp allocator
	void			SetTempAllocator(JPH::TempAllocator* inTempAllocator) { mTempAllocator = inTempAllocator; }

	virtual void	Initialize() { }

	// Number used to scale the terrain and camera movement to the scene
	virtual float	GetWorldScale() const { return 1.0f; }

	// If this test implements a contact listener, it should be returned here
	virtual JPH::ContactListener* GetContactListener() { return nullptr; }

	JPH::PhysicsSystem* getPhysicsSystem() {
		return this->mPhysicsSystem;
	}

	// Utility function to create a static floor body
	JPH::Body& CreateFloor(float inSize = 200.0f) {
		const float scale = GetWorldScale();

		JPH::Body& floor = *mBodyInterface->CreateBody(JPH::BodyCreationSettings(new JPH::BoxShape(scale * JPH::Vec3(0.5f * inSize, 1.0f, 0.5f * inSize), 0.0f), JPH::RVec3(scale * JPH::Vec3(0.0f, -1.0f, 0.0f)), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING));
		mBodyInterface->AddBody(floor.GetID(), JPH::EActivation::DontActivate);
		return floor;
	}

	// Utility function to create a floor consisting of very large triangles
	JPH::Body& CreateLargeTriangleFloor() {
		using namespace JPH;
		TriangleList triangles = {
		Triangle(Float3(427.941376f, 0.000027f, -456.470642f), Float3(427.941376f, 0.000024f, -399.411774f), Float3(512.0f, 0.000031f, -511.999969f)),
		Triangle(Float3(0.0f, 0.000031f, -511.999969f), Float3(28.529310f, 0.000027f, -456.470642f), Float3(427.941376f, 0.000027f, -456.470642f)),
		Triangle(Float3(427.941376f, 0.000027f, -456.470642f), Float3(512.0f, 0.000031f, -511.999969f), Float3(0.0f, 0.000031f, -511.999969f)),
		Triangle(Float3(285.294067f, 0.000027f, -456.470642f), Float3(399.411804f, 0.000024f, -399.411774f), Float3(313.823395f, 0.000027f, -456.470642f)),
		Triangle(Float3(313.823395f, 0.000027f, -456.470642f), Float3(399.411804f, 0.000024f, -399.411774f), Float3(342.352936f, 0.000027f, -456.470642f)),
		Triangle(Float3(342.352936f, 0.000027f, -456.470642f), Float3(399.411804f, 0.000024f, -399.411774f), Float3(370.882507f, 0.000027f, -456.470642f)),
		Triangle(Float3(399.411804f, 0.000024f, -399.411774f), Float3(427.941376f, 0.000024f, -399.411774f), Float3(370.882507f, 0.000027f, -456.470642f)),
		Triangle(Float3(370.882507f, 0.000027f, -456.470642f), Float3(427.941376f, 0.000024f, -399.411774f), Float3(399.411804f, 0.000027f, -456.470642f)),
		Triangle(Float3(399.411804f, 0.000027f, -456.470642f), Float3(427.941376f, 0.000024f, -399.411774f), Float3(427.941376f, 0.000027f, -456.470642f)),
		Triangle(Float3(256.764771f, 0.000027f, -456.470642f), Float3(399.411804f, 0.000024f, -399.411774f), Float3(285.294067f, 0.000027f, -456.470642f)),
		Triangle(Float3(85.588173f, 0.000027f, -456.470642f), Float3(399.411804f, 0.000024f, -399.411774f), Float3(114.117729f, 0.000027f, -456.470642f)),
		Triangle(Float3(114.117729f, 0.000027f, -456.470642f), Float3(399.411804f, 0.000024f, -399.411774f), Float3(142.647034f, 0.000027f, -456.470642f)),
		Triangle(Float3(142.647034f, 0.000027f, -456.470642f), Float3(399.411804f, 0.000024f, -399.411774f), Float3(171.176590f, 0.000027f, -456.470642f)),
		Triangle(Float3(171.176590f, 0.000027f, -456.470642f), Float3(399.411804f, 0.000024f, -399.411774f), Float3(199.705902f, 0.000027f, -456.470642f)),
		Triangle(Float3(199.705902f, 0.000027f, -456.470642f), Float3(399.411804f, 0.000024f, -399.411774f), Float3(228.235214f, 0.000027f, -456.470642f)),
		Triangle(Float3(228.235214f, 0.000027f, -456.470642f), Float3(399.411804f, 0.000024f, -399.411774f), Float3(256.764771f, 0.000027f, -456.470642f)),
		Triangle(Float3(85.588173f, 0.000024f, -399.411774f), Float3(399.411804f, 0.000024f, -399.411774f), Float3(85.588173f, 0.000027f, -456.470642f)),
		Triangle(Float3(427.941376f, 0.000024f, -399.411774f), Float3(512.0f, 0.000019f, -313.823364f), Float3(512.0f, 0.000031f, -511.999969f)),
		Triangle(Float3(399.411804f, 0.000024f, -399.411774f), Float3(512.0f, 0.000019f, -313.823364f), Float3(427.941376f, 0.000024f, -399.411774f)),
		Triangle(Float3(285.294067f, 0.000024f, -399.411774f), Float3(512.0f, 0.000019f, -313.823364f), Float3(313.823395f, 0.000024f, -399.411774f)),
		Triangle(Float3(313.823395f, 0.000024f, -399.411774f), Float3(512.0f, 0.000019f, -313.823364f), Float3(342.352936f, 0.000024f, -399.411774f)),
		Triangle(Float3(342.352936f, 0.000024f, -399.411774f), Float3(512.0f, 0.000019f, -313.823364f), Float3(370.882507f, 0.000024f, -399.411774f)),
		Triangle(Float3(370.882507f, 0.000024f, -399.411774f), Float3(512.0f, 0.000019f, -313.823364f), Float3(399.411804f, 0.000024f, -399.411774f)),
		Triangle(Float3(256.764771f, 0.000024f, -399.411774f), Float3(512.0f, 0.000019f, -313.823364f), Float3(285.294067f, 0.000024f, -399.411774f)),
		Triangle(Float3(228.235214f, 0.000024f, -399.411774f), Float3(512.0f, 0.000019f, -313.823364f), Float3(256.764771f, 0.000024f, -399.411774f)),
		Triangle(Float3(199.705902f, 0.000024f, -399.411774f), Float3(512.0f, 0.000019f, -313.823364f), Float3(228.235214f, 0.000024f, -399.411774f)),
		Triangle(Float3(228.235214f, 0.000019f, -313.823364f), Float3(512.0f, 0.000019f, -313.823364f), Float3(199.705902f, 0.000024f, -399.411774f)),
		Triangle(Float3(142.647034f, 0.000024f, -399.411774f), Float3(228.235214f, 0.000019f, -313.823364f), Float3(171.176590f, 0.000024f, -399.411774f)),
		Triangle(Float3(171.176590f, 0.000024f, -399.411774f), Float3(228.235214f, 0.000019f, -313.823364f), Float3(199.705902f, 0.000024f, -399.411774f)),
		Triangle(Float3(85.588173f, 0.000022f, -370.882477f), Float3(228.235214f, 0.000019f, -313.823364f), Float3(142.647034f, 0.000024f, -399.411774f)),
		Triangle(Float3(85.588173f, 0.000022f, -370.882477f), Float3(199.705902f, 0.000019f, -313.823364f), Float3(228.235214f, 0.000019f, -313.823364f)),
		Triangle(Float3(114.117729f, 0.000024f, -399.411774f), Float3(85.588173f, 0.000022f, -370.882477f), Float3(142.647034f, 0.000024f, -399.411774f)),
		Triangle(Float3(85.588173f, 0.000024f, -399.411774f), Float3(85.588173f, 0.000022f, -370.882477f), Float3(114.117729f, 0.000024f, -399.411774f)),
		Triangle(Float3(28.529310f, 0.000019f, -313.823364f), Float3(199.705902f, 0.000019f, -313.823364f), Float3(85.588173f, 0.000022f, -370.882477f)),
		Triangle(Float3(57.058865f, 0.000019f, -313.823364f), Float3(0.0f, 0.000017f, -285.294037f), Float3(85.588173f, 0.000019f, -313.823364f)),
		Triangle(Float3(28.529310f, 0.000019f, -313.823364f), Float3(0.0f, 0.000017f, -285.294037f), Float3(57.058865f, 0.000019f, -313.823364f)),
		Triangle(Float3(28.529310f, 0.000027f, -456.470642f), Float3(0.0f, 0.000017f, -285.294037f), Float3(57.058865f, 0.000027f, -456.470642f)),
		Triangle(Float3(0.0f, 0.000017f, -285.294037f), Float3(28.529310f, 0.000027f, -456.470642f), Float3(0.0f, 0.000031f, -511.999969f)),
		Triangle(Float3(0.0f, 0.000017f, -285.294037f), Float3(85.588173f, 0.000022f, -370.882477f), Float3(85.588173f, 0.000024f, -399.411774f)),
		Triangle(Float3(0.0f, 0.000017f, -285.294037f), Float3(85.588173f, 0.000024f, -399.411774f), Float3(57.058865f, 0.000027f, -456.470642f)),
		Triangle(Float3(57.058865f, 0.000027f, -456.470642f), Float3(85.588173f, 0.000024f, -399.411774f), Float3(85.588173f, 0.000027f, -456.470642f)),
		Triangle(Float3(399.411804f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(456.470673f, 0.000019f, -313.823364f)),
		Triangle(Float3(456.470673f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(512.0f, 0.000019f, -313.823364f)),
		Triangle(Float3(228.235214f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(256.764771f, 0.000019f, -313.823364f)),
		Triangle(Float3(256.764771f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(285.294067f, 0.000019f, -313.823364f)),
		Triangle(Float3(285.294067f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(313.823395f, 0.000019f, -313.823364f)),
		Triangle(Float3(313.823395f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(342.352936f, 0.000019f, -313.823364f)),
		Triangle(Float3(342.352936f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(370.882507f, 0.000019f, -313.823364f)),
		Triangle(Float3(370.882507f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(399.411804f, 0.000019f, -313.823364f)),
		Triangle(Float3(0.0f, 0.000017f, -285.294037f), Float3(0.0f, 0.000009f, -142.647018f), Float3(512.0f, 0.000003f, -57.058861f)),
		Triangle(Float3(199.705902f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(228.235214f, 0.000019f, -313.823364f)),
		Triangle(Float3(171.176590f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(199.705902f, 0.000019f, -313.823364f)),
		Triangle(Float3(0.0f, 0.000017f, -285.294037f), Float3(512.0f, 0.000003f, -57.058861f), Float3(85.588173f, 0.000019f, -313.823364f)),
		Triangle(Float3(85.588173f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(142.647034f, 0.000019f, -313.823364f)),
		Triangle(Float3(142.647034f, 0.000019f, -313.823364f), Float3(512.0f, 0.000003f, -57.058861f), Float3(171.176590f, 0.000019f, -313.823364f)),
		Triangle(Float3(485.0f, 0.000002f, -28.529308f), Float3(512.0f, 0.0f, 0.0f), Float3(512.0f, 0.000002f, -28.529308f)),
		Triangle(Float3(512.0f, 0.0f, 0.0f), Float3(427.941376f, 0.000002f, -28.529308f), Float3(285.294067f, 0.000002f, -28.529308f)),
		Triangle(Float3(456.470673f, 0.000002f, -28.529308f), Float3(512.0f, 0.0f, 0.0f), Float3(485.0f, 0.000002f, -28.529308f)),
		Triangle(Float3(427.941376f, 0.000002f, -28.529308f), Float3(512.0f, 0.0f, 0.0f), Float3(456.470673f, 0.000002f, -28.529308f)),
		Triangle(Float3(171.176590f, 0.0f, 0.0f), Float3(512.0f, 0.0f, 0.0f), Float3(285.294067f, 0.000002f, -28.529308f)),
		Triangle(Float3(285.294067f, 0.000002f, -28.529308f), Float3(512.0f, 0.000002f, -28.529308f), Float3(512.0f, 0.000003f, -57.058861f)),
		Triangle(Float3(0.0f, 0.000009f, -142.647018f), Float3(285.294067f, 0.000002f, -28.529308f), Float3(512.0f, 0.000003f, -57.058861f)),
		Triangle(Float3(0.0f, 0.000007f, -114.117722f), Float3(171.176590f, 0.0f, 0.0f), Float3(0.0f, 0.000009f, -142.647018f)),
		Triangle(Float3(0.0f, 0.0f, 0.0f), Float3(171.176590f, 0.0f, 0.0f), Float3(0.0f, 0.000007f, -114.117722f)),
		Triangle(Float3(0.0f, 0.000009f, -142.647018f), Float3(171.176590f, 0.0f, 0.0f), Float3(285.294067f, 0.000002f, -28.529308f))
		};

		MeshShapeSettings mesh_settings(triangles);
		mesh_settings.SetEmbedded();
		BodyCreationSettings floor_settings(&mesh_settings, RVec3(-256.0f, 0.0f, 256.0f), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
		Body& floor = *mBodyInterface->CreateBody(floor_settings);
		mBodyInterface->AddBody(floor.GetID(), EActivation::DontActivate);
		return floor;
	}

	// Create an uneven terrain floor body
	JPH::Body& CreateMeshTerrain() {}
	JPH::Body& CreateHeightFieldTerrain() {}

protected:

	JPH::JobSystem* mJobSystem = nullptr;
	JPH::PhysicsSystem* mPhysicsSystem = nullptr;
	JPH::BodyInterface* mBodyInterface = nullptr;
	JPH::DebugRenderer* mDebugRenderer = nullptr;
	JPH::TempAllocator* mTempAllocator = nullptr;
};
