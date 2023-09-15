#pragma once
#include "../lib/raylib.h"
#include "../Core/Main.hpp"
#include "../Logging/Logman.hpp"
#include "../Gameobj.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>


struct GizmoData {
    bool shouldDrawGizmo; // should Gizmo Draw
    
};

// Simple Game Object for debugging
class Gizmo : public GameObject { 
    public:
        Gizmo() : id(RegisterObj(this)) {}

        void onDestroy() const override {}

        

        int GetId() const override {
            return this->id;
        }

        int GetType() const override {
            return GIZMO;
        }

        virtual void EnableGizmo()
        {
            
        }

        virtual void DisableGizmo()
        {
        }
      
    
        virtual bool IsGizmoEnabled() {
            return data.shouldDrawGizmo;
        }

        GizmoData data;
    

        int id;
};

/*
    Ignore this.

void DrawGizmoObject()
        {
            BeginDrawing();

                BeginMode3D(Main::GetPlayer().getSelfCamera());
                    DrawLine3D(GetLight().position, GetLight().target, RED);
                    DrawSphereWires(GetLight().position, 3.0f, 2.0f, 4.0f, BLACK );
                EndMode3D();

            EndDrawing();
        }
*/