#pragma once

#include "../../../lib/raylib.h"
#include "../../../lib/raymath.h"

#include "Velocity.h"
#include "Friction.h"

#include "../Lists/Registry.h"

#include <vector>

#define MAX_COLLIDERS 1000

class RigidBody;
class RigidBodies;
class Collider;

// NOTE: Uses doubles to prevent floating point errors
class RigidBody
{
public:
    RigidBody(BoundingBox *box, double mass) : mass(mass), boundingBox(box)
    {
        RigidBodies::RegisterObject(this);
    }

    ~RigidBody()
    {
        delete this;
    }

    void Update()
    {

        if (!Collider::CheckForCollision(this)) {
            Vector3Add(position, velocity.Get());

            velocity.Change(-airResistance.factor, -airResistance.factor, -airResistance.factor);
        }

    }

    BoundingBox *boundingBox;

    const double mass;

    Velocity velocity;

    Friction airResistance;

    Vector3 position;
    
};



class RigidBodies
{
public:

    static inline void RegisterObject(RigidBody *rigidBody) {
        registry.push_back(rigidBody);
    }
    
    static inline std::vector<RigidBody *> registry;
private:
};

class Collider
{
public:
    bool CheckForCollision(RigidBody orgin)
    {
        bool *hasFound = new bool(false);
        for (int i = 0; i < RigidBodies::registry.size(); i++)
        {
            if (CheckCollisionBoxes(*orgin.boundingBox, RigidBodies::registry[i]->boundingBox))
            {
                hasFound = new bool(true);
                break;
            }
        }

        return hasFound;
        delete hasFound;
    }
};