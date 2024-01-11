#pragma once
#include "../../../common.h"

class HealthBar
{
public:
    float CalculatePercentage(float hp, float max_hp)
    {
        float percentage = (float)hp / (float)max_hp;
        return percentage;
    }

    void Draw(Vector2 position)
    {
        float percentage = CalculatePercentage(hp, maxHP);

        DrawRectangle((int)position.x, (int)position.y, 100, 20, BLACK);
        DrawRectangleLines((int)position.x, (int)position.y, 100, 20, RED);
        DrawRectangle((int)position.x, (int)position.y, 100 * percentage, 20, GREEN);
    };

    float hp;
    float maxHP;
};