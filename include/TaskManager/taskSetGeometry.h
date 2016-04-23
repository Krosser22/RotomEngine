/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __TASK_SET_GEOMETRY_H__
#define __TASK_SET_GEOMETRY_H__

#include "task.h"
#include "node/geometry.h"

namespace ROTOM {
  class TaskSetGeometry : public Task {
  public:
    TaskSetGeometry();
    virtual ~TaskSetGeometry();

    virtual void run();

    void setInput(const char *path, Geometry *geometry);

  private:
    char *path_;
    Geometry *geometry_;
  };
}

#endif //__TASK_SET_GEOMETRY_H__