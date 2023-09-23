#pragma once 
#include "lib/raylib.h"
#include "lib/raymath.h"
#include "Gameobj.h"
#include "Monobehavior.h"

class TestPlane : public GameObject
{
    public:
        TestPlane(Shader shader) : id(RegisterObj(this)), shader(shader){
            this->model.materials[0].shader = shader;
        }

        void Draw() override
        {
            BeginShaderMode(shader);
            DrawModel(model, position, 1.0f, RED);
            EndShaderMode();
        }

        void onUpdate() override {

        }

        Vector3 GetPosition()  override {
            return this->position;
        }

        void onDestroy() const override{
            
        }

        int GetType() const override
        {
            return 0;
        }

        BoundingBox GetBoundingBox()  override {
            return this->Box;
        }

        int GetId() const override {
            return this->id;
        }

        void onCollision() override {
            
        }



    private:
        Shader shader;
        Model model = LoadModelFromMesh(GenMeshPlane(5.0f, 5.0f, 0.0f, 0.0f)); 
        BoundingBox Box = GetModelBoundingBox(model);

        Vector3 position = (Vector3){-10.0f, 10.0f, -10.0f};
        const int id;
};