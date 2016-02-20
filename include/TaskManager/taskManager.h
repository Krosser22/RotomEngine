/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include "task.h"

namespace ROTOM {
  namespace TASKMANAGER {
    void init();

    void destroy();

    void addTask(std::shared_ptr<Task> task);

    void waitUntilFinish();
  }
}

#endif //__TASK_MANAGER_H__