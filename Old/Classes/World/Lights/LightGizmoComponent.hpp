#pragma once
#include "../../lib/raylib.h"
#include "../../Logging/Logman.hpp"
#include "../../lib/rlights.h"
#include "../../Core/Main.hpp"
#include "../../Debug/Gizmo.hpp"

struct LightComponentData
{

    bool isEnabled;
    Light *light;
    ~LightComponentData()
    {

        delete this->light;
    }
};

class LightComponent : public Gizmo
{
public:


    LightComponent()
    {
    }

    /**
     * Enable the light.
     *
     * @throws ErrorType description of error
     */
    virtual void EnableLight()
    {
        Logman::CustomLog(LOG_INFO, "Enabling light...", NULL);
        this->data.light->enabled = true;
        this->data.isEnabled = true;
        Logman::CustomLog(LOG_INFO, "Light Enabled", NULL);
    }

    /**
     * Disables the light.
     *
     * @throws ErrorType description of error
     */

    virtual void DisableLight()
    {
        Logman::CustomLog(LOG_INFO, "Disabling light...", NULL);
        this->data.light->enabled = false;
        this->data.isEnabled = false;
        Logman::CustomLog(LOG_INFO, "Light Disabled", NULL);
    }

    /**
     * Update the directional light properties here
     *
     * @param Main::postProcessShader The post process shader object
     * @param GetLight() The light object
     *
     * @throws ErrorType description of error
     */
    virtual void Update()
    {
        // Update the directional light properties here
        UpdateLightValues(Main::postProcessShader, GetLight());
    }

    virtual Light GetLight()
    {
        return *data.light;
    }

    void Draw() override
    {
        BeginDrawing();
            BeginMode3D(Main::GetPlayer().getSelfCamera());
                DrawLine3D(GetLight().position, GetLight().target, RED);
                DrawSphereWires(GetLight().position, 3.0f, 2.0f, 4.0f, BLACK);
            EndMode3D();
        EndDrawing();
    }

    /**
     * Determines if the function is enabled.
     *
     * @return the value of the isEnabled pointer
     */
    virtual bool IsEnabled()
    {
        return data.isEnabled;
    }

protected:
    LightComponentData data;
};