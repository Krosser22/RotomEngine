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
    TaskCalculateMatrix();
    virtual ~TaskCalculateMatrix();

    virtual void run();

    void setInput(Node *root);

    void runOnNode(Node *node);

  private:
    Node *root_;
  };
}

#endif //__TASK_CALCULATE_MATRIX_H__