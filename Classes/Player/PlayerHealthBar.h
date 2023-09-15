#pragma once
#include "../lib/raylib.h"

class HealthBar
{
public:
    float CalculatePercentage(int hp, int max_hp)
    {
        int percentage = (float)hp / (float)max_hp;
        return percentage;
    }

    void Draw(Vector2 position, int hp, int max_hp)
    {
        int percentage = CalculatePercentage(hp, max_hp);

        DrawRectangle(position.x, position.y, 100, 20, BLACK);
        DrawRectangleLines(position.x, position.y, 100, 20, RED);
        DrawRectangle(position.x, position.y, 100 * percentage, 20, GREEN);
    };
};