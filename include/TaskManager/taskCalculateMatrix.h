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

    void setInput(std::shared_ptr<Node> root);

    void runOnNode(std::shared_ptr<Node> node);

  private:
    std::shared_ptr<Node> root_;
  };
}

#endif //__TASK_CALCULATE_MATRIX_H__