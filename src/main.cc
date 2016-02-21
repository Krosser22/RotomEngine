/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "window.h"
#include "sound.h"
#include "taskManager/taskManager.h"
#include "render/renderManager.h"
#include "time.h"

int main(int argc, char** argv) {
  ROTOM::TIME::Chronometer c;
  printf("Starting the managers.\n");
  c.start();
  ////////////////////////////////////////////
  ROTOM::TASKMANAGER::init();
  {
    //////////////////////////////////
    ROTOM::RENDERMANAGER::init();
    {
      ROTOM::SOUND::init();
      printf("Time to start the managers: %f.\n\n\n", c.end());
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