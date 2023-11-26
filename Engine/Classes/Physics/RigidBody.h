#pragma once

#include "../../../lib/raylib.h"
#include "../../../lib/raymath.h"

#include "Velocity.h"
#include "Friction.h"

#include "../Lists/Registry.h"

#include <vector>

#define MAX_COLLIDERS 1000

class RigidBodyRegistryEntry;
class RigidBodies;
class Collider;

// NOTE: Uses doubles to prevent floating point errors
class RigidBody
{
public:
    RigidBody(BoundingBox *box, double mass) : mass(mass), boundingBox(box)
    {
    }

    ~RigidBody()
    {
        delete this;
    }

    void Update()
    {
        Vector3Add(this->transform.translation, velocity.Get());

        velocity.Change(-airResistance.factor, -airResistance.factor, -airResistance.factor);
    }

    BoundingBox *boundingBox;

    const double mass;

    Velocity velocity;

    ObjectTransform transform;

    Friction airResistance;
};

class RigidBodyRegistryEntry
{
public:
    RigidBodyRegistryEntry(RigidBody *rigidBody) 
    {
        rigidBodyEntry.data = &rigidBody;
        rigidBodyEntry.RegisterObject(counter);
    }

    ~RigidBodyRegistryEntry() {
        delete this;
    }

    RegistryObject<RigidBody*> rigidBodyEntry = RegistryObject<RigidBody*>();

    static inline RegisteryObjectCounter counter;
};

class RigidBodies
{
public:
    static inline Registry<RigidBodyRegistryEntry> rigidbodies;

private:
};

class Collider
{
public:
    bool CheckForCollision(RigidBody orgin)
    {
        bool *hasFound = new bool(false);
        for (int i = 0; i < RigidBodies::rigidbodies.registry[0]->GetNumberOfObjects(); i++)
        {
            if (CheckCollisionBoxes(*orgin.boundingBox, RigidBodies::rigidbodies.registry[i]->data->rigidBodyEntry.data.boundingBox)
            {
                hasFound = new bool(true);
                break;
            }
        }

        return hasFound;
        delete hasFound;
    }
};