// Raylib Stuff.

// core Classes
#include "Classes/Core/Main.hpp"





// TODO : Refactor this code into classes and Main class.
int main(void)
{
  
  bool HasDone; // what is this? I dont remember

  /*
                                                  Lights
  _________________________________________________________________________________________________________


      Lights show up on the floor but the sky is just a disgusting piss yellow.
  There should be the skybox.

      Ocean for some fucking reason gets smaller when you get further away from
  land. why? i dont fucking know, because it is special

  */

  // Sun creation
  // Sun[0] = CreateLight(LIGHT_DIRECTIONAL, Vector3{50.0f, 50.0f, 50.0f}, Vector3Zero(), WHITE, postProcessShader);
  //Sun[1] = CreateLight(LIGHT_POINT, Vector3{50.0f, 50.0f, 50.0f}, Vector3Zero(), WHITE, postProcessShader);

  DisableCursor(); // Limit cursor to relative movement inside the window

  // Assignment of shaders

  //--------------------------------------------------------------------------------------

  //Flashlight *flashlight = new Flashlight(player->getSelfCamera(), postProcessShader);



  // Main game loop
  HasDone = false;
  bool CreateSunRay = true;

  Vector3 Orgin =
      Vector3{Main::player->getPosition().x, Main::player->getPosition().y - 10.0f,
              Main::player->getPosition().z};
  //Logman::CustomLog(LOG_DEBUG, "Trace ", NULL);
  //Vector3 testblock = Vector3One();

  //Logman::CustomLog(LOG_DEBUG, "Generating World...", NULL);



  //Logman::CustomLog(LOG_DEBUG, TextFormat("World generated in %d", Starttime - current),NULL);

  //terrain.materials[0].shader = postProcessShader;

  
  // create temp dir if not existant.
  if (!DirectoryExists("temp"))
  {
    system("mkdir temp");
  }
  

  string Command;

  // GameObject::PushObject(new Plane(postProcessShader, Vector3One(), player));

  //GameObject::PushObject(new WorldFloor(postProcessShader, (Vector3){0.0f, -4.0f, 0.0f}));


ExitGame:
  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context

  CloseAudioDevice();

  //--------------------------------------------------------------------------------------

  using namespace std;
  {
    remove("PerlinTest.png");
    remove("HMap.png");
  }


  GameObject::FlushBuffer();
  // delete heightmap;

  return 0;
}

/*
                                            Code Graveyard
_________________________________________________________________________________________________________________________

Wow such empty





*/