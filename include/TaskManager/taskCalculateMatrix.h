/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __TASK_CALCULATE_MATRIX_H__
#define __TASK_CALCULATE_MATRIX_H__

#include "task.h"
#include "node/node.h"

namespace ROTOM {
  class TaskCalculateMatrix : public Task {
  public:
    TaskCalculateMatrix(TaskType taskType = TaskType_CalculateMatrix);
    virtual ~TaskCalculateMatrix();

    virtual void run();

    void setInput(unsigned int root);

    void runOnNode(unsigned int node);

  private:
    unsigned int root_;
  };
}

#endif //__TASK_CALCULATE_MATRIX_H__