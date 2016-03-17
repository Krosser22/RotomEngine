/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "taskManager/taskRender.h"

ROTOM::TaskRender::TaskRender() {}

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
