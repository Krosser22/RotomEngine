/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __TASK_RENDER_H__
#define __TASK_RENDER_H__

#include "task.h"
#include "render/displayList.h"

namespace ROTOM {
  class TaskRender : public Task {
  public:
    TaskRender();
    virtual ~TaskRender();

    virtual void run();

    void setInput(DisplayList *displayList);

  private:
    DisplayList *displayList_;
  };
}

#endif //__TASK_RENDER_H__