#pragma once
#include <raylib/src/raylib.h>

typedef enum ItemTypes {
    Placeable,
    Consumable,
    Ranged,
    Melee,
    
}itype;

class ItemDictionary {
    
}

class Item {
    public:

    Item() {}



    ItemTypes itemtype;
    Model itemModel;

    virtual void Update() {

    }


};