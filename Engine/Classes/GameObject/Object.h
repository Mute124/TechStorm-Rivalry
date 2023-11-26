#pragma once
#include "Gameobject.h"
#include "ObjectTransform.h"
#include "../Physics/RigidBody.h"

#include "../../../lib/rlgl.h"
#include "../../../lib/raymath.h"
class Object : public GameObject {
    public:



        Object(Model model, ObjectTransform transform, float roughness) {      

            this->model = model;
            this->transform = new ObjectTransform(transform);
            
        };

        void Destroy() {
            this->~Object();
        }
        
        void onUpdate() override {
            this->rigidbody->Update();
        }


        ObjectTransform *transform;
        Model model;
        
        RigidBody *rigidbody;
        

        TextureCubemap cubemap;
        Texture2D texture;
    private:
        ~Object() {
            delete this;
        }

        void GenCubemap(float roughness) {
            
        }
        
};

