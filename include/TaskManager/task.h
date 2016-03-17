/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __TASK_H__
#define __TASK_H__

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <memory>

namespace ROTOM {
  class Task {
  public:
    Task();
    virtual ~Task();

    virtual void run() = 0;

    std::vector<Task *> nextTaskList_;
  };
}

#endif //__TASK_H__