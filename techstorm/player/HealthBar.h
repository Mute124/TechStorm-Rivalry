#pragma once
#include "../common.h"

class HealthBar
{
public:
	float calculatePercentage(float hp, float max_hp)
	{
		float percentage = (float)hp / (float)max_hp;
		return percentage;
	}

	void draw(Vector2 position)
	{
		float percentage = calculatePercentage(hp, maxHP);

		DrawRectangle((int)position.x, (int)position.y, 100, 20, BLACK);
		DrawRectangleLines((int)position.x, (int)position.y, 100, 20, RED);
		DrawRectangle((int)position.x, (int)position.y, 100 * percentage, 20, GREEN);
	};

	float hp = 100.0f;
	float maxHP = 100.0f;
};
