/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/time.h"
#include "general/window.h"
#include "scenes/defaultScene.h"
#include "scenes/depthScene.h"
#include "scenes/geometryScene.h"
#include "scenes/movementScene.h"
#include "scenes/meshLoaderScene.h"
#include "scenes/renderToTextureScene.h"
#include "scenes/shaderScene.h"
//#include "scenes/soundScene.h"

int ROTOM::main(int argc, char** argv) {
  TIME::Chronometer c;
  printf("Creating the window.\n");
  c.start();
  WindowInit(1280, 720);
  printf("Time to create the windows: %0.2f.\n\n", c.end());

  //DefaultScene scene;
  //DepthScene scene;
  //GeometryScene scene;
  //MeshLoaderScene scene;
  //MovementScene scene;
  //RenderToTextureScene scene;
  ShaderScene scene;
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
+Shadows --> Lo primero es sacar el depth buffer
+Shadows --> GPU gems 3 (Webpage) parte 2
+Shadows --> Real time shadows (Book)
Por cada una de las cameras se pintará toda la escena para dicha camera haciendo una pasada por todos los drawables (partiendo desde el root) y todas las lights.
También será necesario hacer una pasada por cada una de las luces para crear las sombras.


----------
---TODO---
----------
+Cambiar el glBindTexture por glSetActiveTexture

+glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //TODO - Make this an option to choose

+Load a obj with more than one texture

+Investigate Geometry shaders to make the procedural scene

+Add LUA

+Use my render list with IMGUI
*/