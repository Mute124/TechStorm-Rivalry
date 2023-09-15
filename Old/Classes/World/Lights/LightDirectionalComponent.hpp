#pragma once
#include "../../lib/raylib.h"
#include "../../Logging/Logman.hpp"
#include "../../lib/rlights.h"
#include "LightGizmoComponent.hpp"



// I think you know what it is
class DirectionalLightComponent : public LightComponent {
public:

    // DirectionalLightComponent constructor
    // Initializes a new instance of the DirectionalLightComponent class
    // Parameters:
    //   position: The position of the light
    //   target: The target of the light
    //   color: The color of the light
    //   isenabled: Whether the light is enabled or not
    DirectionalLightComponent(Vector3 position, Vector3 target, Color color, bool isenabled) 
    {
        data.light = new Light(CreateLight(LIGHT_DIRECTIONAL, position, target, color, Main::postProcessShader));
        Logman::CustomLog(LOG_INFO, "Directional Light Component Created", NULL);
    };
    




    /**
     * Get the light.
     *
     * @return the light
     */
    Light GetLight() {
        return *data.light;
    }

    /**
     * Draws a gizmo to represent the directional light.
     *
     * @param None
     *
     * @return None
     *
     * @throws None
     */
    void DrawGizmo() {
        BeginDrawing();

            BeginMode3D(Main::GetPlayer().getSelfCamera());
                DrawLine3D(GetLight().position, GetLight().target, RED);
            EndMode3D();

        EndDrawing();
        // Draw a gizmo to represent the directional light here
    }
};