/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

//#include "general/sound.h"
#include "general/window.h"
#include "taskManager/taskManager.h"

int main(int argc, char** argv) {
  ROTOM::TASKMANAGER::init();
  {
    //ROTOM::SOUND::init();
    ROTOM::main(argc, argv);
  }
  ROTOM::TASKMANAGER::destroy();

  return 0;
}