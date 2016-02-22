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
  displayList_->draw();
}

void ROTOM::TaskRender::setInput(DisplayList *displayList) {
  displayList_ = displayList;
}
