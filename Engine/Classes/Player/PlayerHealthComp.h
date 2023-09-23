#pragma once
#include "../../../lib/raylib.h"
#include "PlayerHealthBar.h"

struct PlayerHealthCompData
{
    HealthBar healthBar = HealthBar();
    int hp;
    const int max_hp = 100;
};

class PlayerHealthComp
{

public:
    PlayerHealthCompData data;
    PlayerHealthComp()
    {
    }

    void DamagePlayer(int damage)
    {
        data.hp -= damage;
    }

    void HealPlayer(int heal)
    {
        data.hp += heal;
    }

    int GetMaxHealth()
    {
        return data.max_hp;
    }

    int GetHealth()
    {
        return data.hp;
    }
};