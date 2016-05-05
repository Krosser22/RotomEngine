/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/time.h"
#include "general/window.h"
#include "scenes/cubemapScene.h"
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

  //CubemapScene scene;
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

/*****************************************************************************************
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
------------------------------------------------------------------------------------------
-------------------------------------------ASK--------------------------------------------
------------------------------------------------------------------------------------------



\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
------------------------------------------------------------------------------------------
-------------------------------------------DONE-------------------------------------------
------------------------------------------------------------------------------------------



\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
------------------------------------------------------------------------------------------
-------------------------------------------DOING------------------------------------------
------------------------------------------------------------------------------------------
+Procedural scene
http://www.andrewwillmott.com/s2007
http://www.cs.cmu.edu/~ajw/s2007/0251-SphericalWorlds.pdf
http://acko.net/blog/making-worlds-4-the-devils-in-the-details/
http://acko.net/
http://donjon.bin.sh/world/
http://pcg.wikidot.com/pcg-algorithm:world-building
http://donjon.bin.sh/code/world/worldgen-2.2a.c

+Cubemap
http://www.custommapmakers.org/skyboxes.php



\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
------------------------------------------------------------------------------------------
-------------------------------------------TODO-------------------------------------------
------------------------------------------------------------------------------------------
+glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //TODO - Make this an option to choose
+Load a obj with more than one texture
+Investigate Geometry shaders to make the procedural scene
+Add LUA
+Shadows --> GPU gems 3 (Webpage) parte 2
+Shadows --> Real time shadows (Book)



*****************************************************************************************/