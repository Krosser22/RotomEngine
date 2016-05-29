/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "scene.h"
#include "render/displayList.h"

namespace ROTOM {
  //Initializes the window
  void WindowInit(const unsigned int width, const unsigned int height);

  //Return if the window is opened
  bool WindowIsOpened();

  //Destroys the window
  void WindowDestroy();

  //Returns the width of the window
  int WindowWidth();
  
  //Returns the height of the window
  int WindowHeight();

  //Sets the scene that is going to be used
  void SetScene(Scene *newScene);

  //Render the scene from the perspective of a camera
  void RenderScene(float *projectionMatrix, float *viewMatrix, float *viewPosition);

  //Render the postProcess
  void RenderPostProcess(Drawable *drawable);

  //It will return the actual displayList
  DisplayList *GetActualDisplayList();

  //Must be declared by the user in order to use this library
  int main(int argc, char **argv);
}

#endif //__WINDOW_H__