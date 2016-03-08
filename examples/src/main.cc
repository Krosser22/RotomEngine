/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/time.h"
#include "general/window.h"
#include "scenes/defaultScene.h"
#include "scenes/geometryScene.h"
#include "scenes/movementScene.h"
#include "scenes/meshLoaderScene.h"
#include "scenes/shaderScene.h"
//#include "scenes/soundScene.h"

int ROTOM::main(int argc, char** argv) {
  TIME::Chronometer c;
  printf("Creating window.\n");
  c.start();
  WindowInit(1280, 720);
  //printf("Time to create the windows: %f.\n\n\n", c.end());

  DefaultScene scene;
  //GeometryScene scene;
  //MeshLoaderScene scene;
  //MovementScene scene;
  //ShaderScene scene;
  //SoundScene scene;
  SetScene(&scene);
  return 0;
}

/*
---------
---ASK---
---------


----------
---DONE---
----------


-----------
---DOING---
-----------


----------
---TODO---
----------
+Make a task (to load files from behind)
+Shadows --> Lo primero es sacar el depth buffer
+Shadows --> GPU gems 3 (Webpage) parte 2
+Shadows --> Real time shadows (Book)
+Add LUA
+Use my render list with IMGUI
*/