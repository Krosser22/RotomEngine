/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __COMMAND_H__
#define __COMMAND_H__

namespace ROTOM {
  class Command {
  public:
    Command();
    virtual ~Command();

    virtual void run() = 0;
  };
}

#endif //__COMMAND_H__