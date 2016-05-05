/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __DISPLAY_LIST_H__
#define __DISPLAY_LIST_H__

#include "command.h"
#include <vector>

namespace ROTOM {
  class DisplayList {
  public:
    DisplayList();
    ~DisplayList();

    std::vector<Command *> commandList_;

    void addCommand(Command *command);

    void draw();
  };
}

#endif //__DISPLAY_LIST_H__