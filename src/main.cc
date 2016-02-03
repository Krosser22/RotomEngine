/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "window.h"
#include "sound.h"
#include "security.h"

int main(int argc, char** argv) {
  ROTOM::SOUND::init(); //Hardware check
  ROTOM::main(argc, argv);
  ROTOM::WindowDestroy();
  //ROTOM::SECURITY::checkSecurityCount();
  return 0;
}