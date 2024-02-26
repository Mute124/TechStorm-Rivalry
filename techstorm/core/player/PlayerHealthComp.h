#pragma once

#include "HealthBar.h"

class PlayerHealthComp
{
public:

	

	HealthBar* healthBar;

	PlayerHealthComp(int maxHP)
	{
		healthBar = new HealthBar();

		healthBar->hp = 100;
		healthBar->maxHP = maxHP;
	}

	PlayerHealthComp() {}

	~PlayerHealthComp() {
		delete this;
	}

	void damagePlayer(float damage)
	{
		healthBar->hp -= damage;
	}

	void healPlayer(int heal)
	{
		healthBar->hp += heal;
	}

	int getMaxHealth()
	{
		return healthBar->maxHP;
	}

	int getHealth()
	{
		return healthBar->hp;
	}
};