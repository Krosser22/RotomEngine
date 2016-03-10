/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

//#include "general/sound.h"
#include "general/time.h"
#include "general/window.h"
//#include "render/renderManager.h"
#include "taskManager/taskManager.h"

int main(int argc, char** argv) {
  ROTOM::TIME::Chronometer c;
  printf("Starting the managers.\n");
  c.start();

  ROTOM::TASKMANAGER::init();
  {
    //ROTOM::SOUND::init();
    printf("Time to start the managers: %0.2f.\n\n", c.end());
    ROTOM::main(argc, argv);
  }
  ROTOM::TASKMANAGER::destroy();

  return 0;
}