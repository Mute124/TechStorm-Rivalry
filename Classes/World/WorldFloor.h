#pragma once
#include "../lib/raylib.h"
#include "../gameobj.h"

#define FLOORSIZE 5.0f

class WorldFloor : public GameObject {
    public:
        WorldFloor(Shader shader, Vector3 position) : id(RegisterObj(this)), shader(shader), position(position) {
            this->model.materials[0].shader = shader;

            this->model.materials[0].shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

        };

        void Draw() override {
            DrawPlane(Vector3Zero(), {100, 100}, BLACK);
        }   


        int GetId() const override {
            return this->id;
        }

        Vector3 GetPosition() override {
            return this->position;
        }

        int GetType() const override {
            return WORLDFLOOR;
        }

        void onDestroy() const override {}

        BoundingBox GetBoundingBox() override {
            return this->Box;
        }
        
    private:
        Vector3 position;
        Shader shader;
        Model model = LoadModelFromMesh(GenMeshPlane(FLOORSIZE, FLOORSIZE, 0.0f, 0.0f));
        
        BoundingBox Box = GetModelBoundingBox(model);
        const int id;
};