#include "PlayerController.h"
#include "Logman.h"


PlayerController::PlayerController(Camera camera) : camera(&camera) {
    Logman::CustomLog(LOG_INFO, "Player Controller Created", NULL);
}

void PlayerController::UpdateValues(Camera *camera, int Mode) {
    UpdateCamera(camera, Mode);
}

void PlayerController::CheckInput() {
        // Show Debug shit
    if (IsKeyDown(KEY_END))
    {
      BeginDrawing();
      BeginMode3D(&this->camera);
      // Sun Rays
      DrawLine3D(Sun[0].position, this->camera.target, RED);
      EndMode3D();
      EndDrawing();
    }
}