/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include "task.h"

namespace ROTOM {
  namespace TASKMANAGER {
    void init();

    void destroy();

    void addTask(Task *task);
  }
}

#endif //__TASK_MANAGER_H__