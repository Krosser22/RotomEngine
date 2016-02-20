/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __COMMAND_CLEAR_H__
#define __COMMAND_CLEAR_H__

#include "command.h"

namespace ROTOM {
  class CommandClear : public Command {
  public:
    CommandClear();
    virtual ~CommandClear();

    void run();
  };
}

#endif //__COMMAND_CLEAR_H__