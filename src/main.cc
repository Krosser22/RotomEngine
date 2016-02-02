/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "window.h"
#include "sound.h"

int main(int argc, char** argv) {
  ROTOM::Sound::init(); //Hardware check
  ROTOM::main(argc, argv);
  ROTOM::WindowDestroy();
  return 0;
}