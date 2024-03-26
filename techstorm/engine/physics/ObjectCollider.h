#pragma once
#include "../../Common.h"
#include "Collision.h"

class ObjectCollider {
public:
	BoundingBox collider;
	bool drawCollider = false;

	void createCollider(Model* model) {
		collider = GetModelBoundingBox(*model);
	}

	virtual void onCollide(Collision* other) {
	}

	// called ONCE on collision entry
	virtual void collisionEntry(Collision* other) {
	}

	// called each frame while there is still a collision.
	virtual void collisionUpdate(Collision* other) {
	}

	virtual void collisionExit() {}
};
