/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "window.h"
#include "scenes/defaultScene.h"
#include "scenes/soundScene.h"

int ROTOM::main(int argc, char** argv) {
  WindowInit(1280, 720);
  //DefaultScene scene;
  SoundScene scene;
  SetScene(&scene);
  return 0;
}

/*
---------
---ASK---
---------
GetRoot() Donde???


----------
---DONE---
----------


-----------
---DOING---
-----------


----------
---TODO---
----------
+Add LUA
+Use my render list with IMGUI
+Add a class DB with SQLite or another library to save the game
*/