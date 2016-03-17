/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __RENDER_MANAGER_H__
#define __RENDER_MANAGER_H__

#include "command.h"
#include <memory>

namespace ROTOM {
  namespace RENDERMANAGER {
    void init();

    void destroy();

    void addCommand(std::shared_ptr<Command> command);

    void draw();
  }
}

#endif //__RENDER_MANAGER_H__