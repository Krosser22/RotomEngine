/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "window.h"
#include "sound.h"
#include "taskManager.h"
#include "renderManager.h"
#include "security.h"

int main(int argc, char** argv) {
  ROTOM::SOUND::init(); //Hardware check
  
  ////////////////////////////////////////////
  ROTOM::TASKMANAGER::init();
  {
    //////////////////////////////////
    ROTOM::RENDERMANAGER::init();
    {
      ROTOM::main(argc, argv);
    }
    ROTOM::RENDERMANAGER::destroy();
    //////////////////////////////////
  }
  ROTOM::TASKMANAGER::destroy();
  ////////////////////////////////////////////

  ROTOM::WindowDestroy();
  //ROTOM::SECURITY::checkSecurityCount();
  return 0;
}