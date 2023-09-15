#include "Sun.h"
#include "Logman.h"


void Sun::Update() {
    UpdateLightValues(this->m_shader, this->m_light);
}

Vector4 Sun::GetAmbient() {
    return this->m_ambient_color;
};

Sun::Sun(Vector3 sPosition, Vector3 sTarget, Shader shader, Vector4 ambient_Color) : m_position(sPosition), m_target(sTarget), m_shader(shader), m_ambient_color(ambient_Color) {\
    m_light = CreateLight(LIGHT_POINT, sPosition, sTarget, ambient_Color, shader);
    Logman::CustomLog(LOG_INFO, "Created sun object", 0);
    
}



Sun::~Sun() {
    delete this;
}