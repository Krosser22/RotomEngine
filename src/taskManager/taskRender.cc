/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "taskManager/taskRender.h"

ROTOM::TaskRender::TaskRender(TaskType taskType) {
  taskType_ = taskType;
}

ROTOM::TaskRender::~TaskRender() {}

void ROTOM::TaskRender::run() {
  /*if (displayList_->isValid_) {
    printf("The DisplayList is slow\n");
  }*/
  displayList_->isValid_ = true;
}

void ROTOM::TaskRender::setInput(DisplayList *displayList) {
  displayList_ = displayList;
}
