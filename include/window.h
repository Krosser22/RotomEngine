/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __WINDOW_H__
#define __WINDOW_H__

namespace ROTOM {
  //Initializes the window
  bool WindowInit(const unsigned int width, const unsigned int height);
  
  //Destroys the window
  void WindowDestroy();

  //Returns if the window is opened
  bool WindowIsOpened();
  
  //Returns the height of the window
  int WindowHeight();
  
  //Returns the width of the window
  int WindowWidth();
  
  //Must be declared by the user in order to use this library
  int main(int argc, char **argv);
}

#endif //__WINDOW_H__