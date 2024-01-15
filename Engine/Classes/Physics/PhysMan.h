#pragma once
#include <ctype.h>

#include "../../../../build/_deps/physx-src/physx/include/PxPhysicsAPI.h"

#include "../Logging/Logman.h"


using namespace physx;

class PhysMan
{

private:
    class PxAllocatorCallback
    {
    public:
        virtual ~PxAllocatorCallback() {}
        virtual void *allocate(size_t size, const char *typeName, const char *filename, int line) = 0;
        virtual void deallocate(void *ptr) = 0;
    };

    class UserErrorCallback : public PxErrorCallback
    {
    public:
        virtual void reportError(PxErrorCode::Enum code, const char *message, const char *file, int line)
        {
            // error processing implementation
            Logman::CustomLog(LOG_ERROR, TextFormat("Error %i : %s", code, message), NULL);
        }
    };
};