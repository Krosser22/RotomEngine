/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "taskManager/task.h"

ROTOM::Task::Task() {}

ROTOM::Task::~Task() {}

void ROTOM::Task::clearTask() {
  nextTaskList_.clear();
}