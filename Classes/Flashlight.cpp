#include "Flashlight.h"

Flashlight::Flashlight(Camera PlayerCameraData, Shader shader) : m_light_source()
{
    this->m_light_source = CreateLight(LIGHT_DIRECTIONAL, PlayerCameraData.position, PlayerCameraData.target, WHITE, shader);
}

Flashlight::~Flashlight()
{
    delete this;
}

void Flashlight::Switch()
{
    if (this->m_light_source.enabled)
    {
        this->m_light_source.enabled = false;
    }
    else if (!this->m_light_source.enabled)
    {
        this->m_light_source.enabled = true;
    }
}

void Flashlight::Update(Shader shader, Vector3 PlayerPos, Vector3 PlayerTarget)
{
    this->m_light_source.position = PlayerPos;
    this->m_light_source.target = PlayerTarget;
    UpdateLightValues(shader, this->m_light_source);
}

Light Flashlight::GetLight()
{
    return this->m_light_source;
}