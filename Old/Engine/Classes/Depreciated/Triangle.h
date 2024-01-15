#pragma once
#include "Globals.h"
#include "lib/raylib.h"
#include "Gameobj.h"

class Triangle : public GameObject {
  private:

public:
    Triangle() {
    }
    int GetType() const override {}

    void Draw() const override {
        DrawTriangle3D(t_verticies.v1, t_verticies.v2, t_verticies.v3, GREEN);
    }

    void SetModel() const override {}
};