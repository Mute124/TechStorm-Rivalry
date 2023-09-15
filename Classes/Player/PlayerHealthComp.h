#pragma once
#include "../lib/raylib.h"
#include "PlayerHealthBar.h"

struct PlayerHealthCompData
{
    int hp;
    const int max_hp = 100;
};

class PlayerHealthComp
{
protected:

    PlayerHealthCompData data;
    HealthBar healthBar;

public:
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