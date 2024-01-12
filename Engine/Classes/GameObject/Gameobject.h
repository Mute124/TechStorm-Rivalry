#pragma once
#include "../../../common.h"
#include "../../DataSets/Globals.h"
#include "../Logging/Logman.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <mutex>

#include "../Graphics/ObjectMaterial.h"

// Cleaner version. yay! Hopefully to reduce boilerplate


/*
class GameObject {
  public:
    GameObject(MaterialMapProperties properties, bool useDefaultShader, Model model, Color tint, Vector3 spawnPosition) : GameObjectMaterial(new GameObjectMaterial(properties, true)) {

    }

    virtual void Draw() {
      
    }

    virtual void OnUpdate() {

    }




    Vector3 *position;
    Model *model;
    GameObjectMaterial *material;
    Color *tint;


};
*/


// used for organization reasons and makes C++ less torture.
// TODO : Refactor for sake of sanity...
class GameObject
{
public:
  virtual void Draw(){};

  virtual ~GameObject()
  {
    for (auto &GameObject : GameObjects)
    {
      GameObject->onDestroy();
      delete GameObject;
    }
  }

  virtual int GetType() const = 0;

  /**
   * Registers an object.
   *
   * @return The length of the registered object.
   *
   * @throws ErrorType A description of the error.
   */
  static inline int RegisterObj(GameObject *object)
  {
    if (ids.size() == 0)
    {

      ids.resize(MAX_INSTANCES);
      Logman::CustomLog(LOG_WARNING, TextFormat("Id Vector size is 0! setting it to %i", MAX_INSTANCES), NULL);
    }

    long int length = ids.size();
    length++;
    ids.push_back(length);
    return length;

    GameObjects.push_back(object);
  }

  virtual void UnRegisterObj(const int id)
  {
    GameObjects[id]->onDestroy();
  }

  virtual void Test(){};

  virtual void onUpdate(){}; // Called every frame

  virtual void onCollision(){};

  virtual void onDestroy() const = 0; // NOTE : This deletes the object and shall be overridden for custom behaviors

  virtual int GetId() const = 0;

  virtual BoundingBox GetBoundingBox()
  {
    return Global::BoxNull;
  };

  virtual bool CheckCollision(GameObject *Orgin, int id)
  {
    for (auto &GameObject : GameObjects)
    {
      if (CheckCollisionBoxes(Orgin->GetBoundingBox(), GameObject->GetBoundingBox()))
      {
        if (id == GameObject->GetId())
        {
          continue;
        }
        else
        {
          return true;
          break;
        }
      }
    }
  };

  static inline void UpdateRegistry(std::vector<GameObject *> objects)
  {
    GameObjects = objects;
  }

  /**
   * Updates the state of the program.
   *
   * @param None
   *
   * @return None
   *
   * @throws None
   */
  static inline void Update()
  {
    RenderObjects();
    for (auto &GameObject : GameObjects)
    {

      GameObject->onUpdate();
    }
  }
  virtual Vector3 GetPosition()
  {
    return Vector3Zero();
  };

  static inline std::vector<int> ids; // is this needed?

  static inline void PushObject(GameObject *_obj)
  {
    Logman::CustomLog(LOG_INFO, "Pushing object", NULL);
    GameObjects.push_back(_obj);
  }

  static inline void RenderObjects()
  {

    for (auto &obj : GameObjects)
    {
      obj->Draw();
      obj->onUpdate();
    }
  }
  static void FlushBuffer()
  {

    // we have to use this implementation due to each object can have their own behavior.
    for (int i = 0; i < GameObjects.size(); i++)
    {
      GameObjects[i]->onDestroy();
    }
  }
  static inline std::vector<GameObject *> GameObjects; // game objects

};
