#pragma once
#include "../../../lib/raylib.h"
#include "PlayerHealthBar.h"

class PlayerHealthComp
{

public:
    HealthBar *healthBar;
    
    PlayerHealthComp(int maxHP)
    {
        healthBar = new HealthBar();

        healthBar->hp = 100;
        healthBar->maxHP = maxHP;
    }

    ~PlayerHealthComp() {
        delete this;
    }

    void DamagePlayer(float damage)
    {
        healthBar->hp -= damage;
    }

    void HealPlayer(int heal)
    {
        healthBar->hp += heal;
    }

    int GetMaxHealth()
    {
        return healthBar->maxHP;
    }

    int GetHealth()
    {
        return healthBar->hp;
    }
};