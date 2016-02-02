/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __DISPLAY_LIST_H__
#define __DISPLAY_LIST_H__

#include "command.h"
#include <vector>

namespace ROTOM {
  class DisplayList {
  public:
    std::vector<void *> commandList_;

    void addCommand(void *command);

    void clearCommandList();

    void runAll();
  };
}

#endif //__DISPLAY_LIST_H__