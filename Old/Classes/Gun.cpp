#include "Gun.h"

Gun::Gun(Camera PlayerCam, Shader shader, Shader Cubemap) : m_player_cam(PlayerCam), shader(shader), m_cubemap_shader(Cubemap)
{
    LoadGunModel();

    this->m_position = Vector3AddValue(m_player_cam.position, 2.0f);
}

void Gun::Draw()
{
    DrawModel(this->m_model, Vector3AddValue(m_player_cam.position, 2.0f), 1.0f, WHITE);
}

Gun::~Gun()
{
    delete this;
}

