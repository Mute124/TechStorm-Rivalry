#pragma once
#include "../../../lib/raylib.h"
#include "../../../lib/rlights.h"

class Flashlight {
    private:
        Light m_light_source;
        Vector3 position;
    public:
        Light GetLight() {
            return this->m_light_source;
        }
        
        Flashlight(Camera PlayerCameraData, Shader shader) : m_light_source() {
            this->m_light_source = CreateLight(LIGHT_DIRECTIONAL, PlayerCameraData.position, PlayerCameraData.target, WHITE, shader);
        }

        ~Flashlight() {

        }
        // this is meant to turn on and off the flashlight
        void Switch() {}
        
        /**
         * Updates the shader with the player position and target.
         *
         * @param shader the shader to update
         * @param PlayerPos the position of the player
         * @param PlayerTarget the target of the player
         *
         * @throws ErrorType description of error
         */
        void Update(Shader shader, Vector3 PlayerPos, Vector3 PlayerTarget) {
            this->m_light_source.position = PlayerPos;
            this->m_light_source.target = PlayerTarget;
            UpdateLightValues(shader, this->m_light_source);
        }
        
    
};