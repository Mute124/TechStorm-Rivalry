#include "GameShader.hpp"

#include "../lib/raylib.h"

#include "../lib/raymath.h"
#include "../lib/rcamera.h"


GameShader::GameShader() {

}

bool GameShader::isShaderReady() {
    return this->isReady;
}

void GameShader::EnableShader() {
    BeginShaderMode(*shader);
}

void GameShader::DisableShader() {
    EndShaderMode();
}

void GameShader::UnloadGameShader() {
    UnloadShader(*shader);
}


