/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __TASK_CALCULATE_MATRIX_H__
#define __TASK_CALCULATE_MATRIX_H__

#include "taskManager.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "node.h"

namespace ROTOM {
  class TaskCalculateMatrix : public Task {
  public:
    TaskCalculateMatrix(TaskType taskType = TaskType_CalculateMatrix);
    virtual ~TaskCalculateMatrix();

    virtual void run();

    void clearTask();

    void setInput(std::shared_ptr<ROTOM::Node *> root);

    void runOnNode(Node *node);

  private:
    std::shared_ptr<ROTOM::Node *> root_;
  };
}

#endif //__TASK_CALCULATE_MATRIX_H__