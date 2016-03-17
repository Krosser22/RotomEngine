/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
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

  private:
    Node *root_;

    void calculateNode(Node *node);

    //This will not ask if the World matrix must be calculated, it will just calculate the matrix without asking
    void calculateNodeForSure(Node *node);
  };
}

#endif //__TASK_CALCULATE_MATRIX_H__