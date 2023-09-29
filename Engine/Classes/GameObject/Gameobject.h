#pragma once
#include "../../../lib/raylib.h"
#include "../../DataSets/Globals.h"
#include "../Logging/Logman.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <mutex>
typedef enum type
{
  BLOCK = 0, // Game object is a block
  PLAYER = 1, // Player object.
  SKYBOX,
  VEHICLE,
  WORLDFLOOR

} objtype;

#include "../Lists/Registry.h"

// TODO : Make this...
class GameObjectRegistry;

// used for organization reasons and makes C++ less torture.
// TODO : Refactor for sake of sanity...
class GameObject
{

public:

RenderTexture2D LoadRenderTextureDepthTex(int width, int height)
{
    RenderTexture2D target = { 0 };

    target.id = rlLoadFramebuffer(width, height);   // Load an empty framebuffer

    if (target.id > 0)
    {
        rlEnableFramebuffer(target.id);

        // Create color texture (default to RGBA)
        target.texture.id = rlLoadTexture(0, width, height, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
        target.texture.width = width;
        target.texture.height = height;
        target.texture.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
        target.texture.mipmaps = 1;

        // Create depth texture buffer (instead of raylib default renderbuffer)
        target.depth.id = rlLoadTextureDepth(width, height, false);
        target.depth.width = width;
        target.depth.height = height;
        target.depth.format = 19;       //DEPTH_COMPONENT_24BIT?
        target.depth.mipmaps = 1;

        // Attach color texture and depth texture to FBO
        rlFramebufferAttach(target.id, target.texture.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D, 0);
        rlFramebufferAttach(target.id, target.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);

        // Check if fbo is complete with attachments (valid)
        if (rlFramebufferComplete(target.id)) TRACELOG(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", target.id);

        rlDisableFramebuffer();
    }
    else TRACELOG(LOG_WARNING, "FBO: Framebuffer object can not be created");

    return target;
}

// Unload render texture from GPU memory (VRAM)
void UnloadRenderTextureDepthTex(RenderTexture2D target)
{
    if (target.id > 0)
    {
        // Color texture attached to FBO is deleted
        rlUnloadTexture(target.texture.id);
        rlUnloadTexture(target.depth.id);

        // NOTE: Depth texture is automatically
        // queried and deleted before deleting framebuffer
        rlUnloadFramebuffer(target.id);
    }
}
  typedef struct

  {
    float *l = new float();
    float *w = new float();
    float *h = new float();
  } ObjDim; // TODO : is this needed?

  virtual void Draw() {};

  virtual ~GameObject()
  {
    for (auto &GameObject : GameObjects)
    {
      GameObject->onDestroy();
      delete GameObject;
    }
  }

  static inline GameObject *SearchById(int id) {
    return GameObjects[id];
  }

  static inline auto *SearchByType(int type) {

    for (auto &GameObject : GameObjects) {
      if (GameObject->GetType() == type)
      {
        
        return GameObject;
        break;
      }
    }
  }

  virtual int GetType() const = 0 ;

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

  virtual void Test() {};

  virtual void onUpdate() {}; // Called every frame

  virtual void onCollision() {};

  virtual void onDestroy() const = 0; // NOTE : This deletes the object and shall be overridden for custom behaviors

  virtual int GetId() const = 0;

  virtual BoundingBox GetBoundingBox() {};

  virtual bool CheckCollision(GameObject *Orgin, int id) {
    for (auto &GameObject : GameObjects)
    {
        if (CheckCollisionBoxes(Orgin->GetBoundingBox(), GameObject->GetBoundingBox()))
        {
          if (id == GameObject->GetId()) {
            continue;
          } else {
            return true;
            break;
          }
        }
    }
  };

  static inline void UpdateRegistry(std::vector<GameObject *> objects) {
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
  static void Update()
  {
    
    for (auto &GameObject : GameObjects)
    {
      Render();
      // do all lambda stuff
      GameObject->onUpdate();
    }
  }
  virtual Vector3 GetPosition() {};

  static inline std::vector<int> ids; // is this needed?

  static inline void Sync(std::vector<GameObject *> objs) {
    
    GameObjects = objs;

    
    
  } 

  static inline std::vector<GameObject *> RequestObjectList() {
    return GameObjects;
  }

  static inline GameObject *RequestObject(int id) {
    return SearchById(id);
  }


  static inline auto PushObject(GameObject *&&_obj) {
    Logman::CustomLog(LOG_INFO, "GameObject : Pushing new object into buffer...", 0);
    GameObjects.push_back(_obj);
    _obj = nullptr;
  }

  static inline void FlushBuffer() {
    for (auto &obj : GameObjects) {
      obj->onDestroy();

    }
  }
  static void Render()
  {
    
    for (auto &GameObject : GameObjects)
    {
      GameObject->Draw();
    }
    
  }

  static inline std::vector<GameObject *> GameObjects; // game objects
private:



  static inline auto Search() {

  }

  Global::Tag IgnoredTags[10] = {
      "skybox",
      "light",
      "lighting",
      "cubemap",
      "sky"
      };

  objtype type; // TODO : is this needed?

  friend class GameObjectRegistry;


};
