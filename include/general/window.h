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
  bool WindowInit(const unsigned int width, const unsigned int height);
  
  //Destroys the window
  void WindowDestroy();

  //Sets the scene that is going to be used
  void SetScene(Scene *newScene);
  
  //Returns the height of the window
  int WindowHeight();
  
  //Returns the width of the window
  int WindowWidth();
  
  //Must be declared by the user in order to use this library
  int main(int argc, char **argv);

  //It will return the actual displayList
  DisplayList *GetActualDisplayList();
}

#endif //__WINDOW_H__