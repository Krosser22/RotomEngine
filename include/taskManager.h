/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include "task.h"
#include <memory>

namespace ROTOM {
  namespace TaskManager {
    void init();

    void destroy();

    void addTask(std::shared_ptr<Task> task);

    void waitUntilFinish();
  }
}

#endif //__TASK_MANAGER_H__