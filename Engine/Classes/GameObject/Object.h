#pragma once
#include "Gameobject.h"
#include "ObjectTransform.h"
#include "../Physics/RigidBody.h"

#include "../../../lib/rlgl.h"
#include "../../../lib/raymath.h"
class Object : public GameObject {
    public:



        Object(Model model, ObjectTransform transform) {      

            this->model = model;
            this->transform = new ObjectTransform(transform);
            
        };

        void Destroy() {
            this->~Object();
        }
        
        void onUpdate() override {
            
        }

        void Draw() override {
            DrawModel(this->model, this->position, this->scale, )
        }

        Vector3 position;
        float scale;

    
        Model model;

    private:
        ~Object() {
            delete this;
        }

        void GenCubemap(float roughness) {
            
        }
        
};

