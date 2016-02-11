/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "window.h"
#include "sound.h"
#include "taskManager.h"
#include "security.h"

int main(int argc, char** argv) {
  ROTOM::TaskManager::init();
  ROTOM::SOUND::init(); //Hardware check
  ROTOM::main(argc, argv);
  ROTOM::TaskManager::destroy();
  ROTOM::WindowDestroy();
  //ROTOM::SECURITY::checkSecurityCount();
  return 0;
}