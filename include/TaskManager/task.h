/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
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
  enum TaskType {
    TaskType_none = 0,
    TaskType_CalculateMatrix,
    TaskType_Render,
  };

  class Task {
  public:
    Task();
    virtual ~Task();
    
    TaskType taskType_ = TaskType_none;

    virtual void run() = 0;

    //virtual void clearTask() = 0;

    std::vector<std::shared_ptr<Task>> nextTaskList_;
  };
}

#endif //__TASK_H__