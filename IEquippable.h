#pragma once
#include "Common.h"
#include "IScriptable.h"
#include "ScriptManager.h"

// 
class IEquippable : public IScriptable
{
public: 

	bool IsEquipped();

	void Equip();

	void Unequip();

	void SetModel(Model model);

private:

	bool equipped = false;

	Model model;
	

	
};

