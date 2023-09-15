// TODO : Refactor File
#include "GameObj.h"

void GameObject::Draw() const
{

    // no implementation here since it's a pure virtual function
    // derived classes must provide their own implementation
}

GameObject::~GameObject()
{
}

int GameObject::GetType() const {}

bool GameObject::CheckCollision(BoundingBox Orgin)
{

    for (auto &GameObject : GameObjects)
    {


        if (CheckCollisionBoxes(Orgin, GameObject->GetBoundingBox()))
        {
            return true;
            break;
        }
    }
}

/**
 * Registers a game object.
 *
 * @return The size of the G_IDS vector after registering the object.
 *
 * @throws None
 */
int GameObject::RegisterObj()
{
    if (ids.empty())
    {
        ids.reserve(MAX_INSTANCES);
    }

    ids.push_back(ids.size() + 1);
    return ids.size();
}

void GameObject::UnRegisterObj(int id)
{
    GameObjects[id]->onDestroy();
}

void GameObject::onUpdate() const
{
}
