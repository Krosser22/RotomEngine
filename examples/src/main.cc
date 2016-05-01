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
#include "scenes/proceduralScene.h"
#include "scenes/renderToTextureScene.h"
#include "scenes/shaderScene.h"
#include "scenes/shadowScene.h"
#include "scenes/soundScene.h"

int ROTOM::main(int argc, char** argv) {
  TIME::Chronometer c;
  printf("Creating the window.\n");
  c.start();
  WindowInit(1024, 512);
  printf("Time to create the windows: %0.2f.\n\n", c.end());

  //DefaultScene scene;
  //DepthScene scene;
  //GeometryScene scene;
  //MeshLoaderScene scene;
  //MovementScene scene;
  //ProceduralScene scene;
  //RenderToTextureScene scene;
  //ShaderScene scene;
  ShadowScene scene;
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
+Shadows --> GPU gems 3 (Webpage) parte 2
+Shadows --> Real time shadows (Book)


----------
---TODO---
----------
+Create a texture class to make sure the texture is well deleted when it has taken by none other object

+Cambiar el glBindTexture por glSetActiveTexture

+glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //TODO - Make this an option to choose

+Load a obj with more than one texture

+Investigate Geometry shaders to make the procedural scene

+Compile the sound library to allow me to use it on release

+Add LUA

+Use my render list with IMGUI
*/