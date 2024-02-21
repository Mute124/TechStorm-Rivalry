#pragma once
#include <tinyxml2.h>
#include "Logman.h"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include "IEquippable.h"



using namespace std;
class EquipmentMan
{
public:

	map<int, IEquippable*> equippablesMap;
	vector<IEquippable*> equippablesVector;


};

