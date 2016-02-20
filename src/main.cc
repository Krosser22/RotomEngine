/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "window.h"
#include "sound.h"
#include "taskManager/taskManager.h"
#include "render/renderManager.h"

int main(int argc, char** argv) {
  ////////////////////////////////////////////
  ROTOM::TASKMANAGER::init();
  {
    //////////////////////////////////
    ROTOM::RENDERMANAGER::init();
    {
      ROTOM::SOUND::init();
      ROTOM::main(argc, argv);
    }
    ROTOM::RENDERMANAGER::destroy();
    //////////////////////////////////
  }
  ROTOM::TASKMANAGER::destroy();
  ////////////////////////////////////////////

  ROTOM::WindowDestroy();
  return 0;
}