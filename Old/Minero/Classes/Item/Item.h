#pragma once
#include "../../../Common.h"

typedef enum ItemTypes {
    Placeable,
    Consumable,
    Ranged,
    Melee,
    
}itype;

class ItemDictionary {
    
};

class Item {
    public:

    Item() {}



    ItemTypes itemtype;
    Model itemModel;

    virtual void Update() {

    }


};