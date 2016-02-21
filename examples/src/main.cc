/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "window.h"
#include "scenes/defaultScene.h"
#include "scenes/soundScene.h"
#include "scenes/meshLoaderScene.h"
#include "time.h"

int ROTOM::main(int argc, char** argv) {
  TIME::Chronometer c;
  printf("Creating window.\n");
  c.start();
  WindowInit(1280, 720);
  printf("Time to create the windows: %f.\n\n\n", c.end());

  DefaultScene scene;
  //SoundScene scene;
  //MeshLoaderScene scene;
  SetScene(&scene);
  return 0;
}

/*
---------
---ASK---
---------
GetRoot() Donde???
fileManager ??? Lo que mas tarda es la creación de la ventana, seguido del acceso a ficheros


----------
---DONE---
----------


-----------
---DOING---
-----------


----------
---TODO---
----------
+The threads of the taskManager must stop when they have no task to do.
+The taskManager must start the render with a task.
+Add LUA
+Use my render list with IMGUI
*/