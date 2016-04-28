/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __TASK_CALCULATE_CAMERA_MATRIX_H__
#define __TASK_CALCULATE_CAMERA_MATRIX_H__

#include "task.h"
#include "node/camera.h"

namespace ROTOM {
  class TaskCalculateCameraMatrix : public Task {
  public:
    TaskCalculateCameraMatrix();
    virtual ~TaskCalculateCameraMatrix();

    virtual void run();

    void setInput(Camera *camera);

  private:
    Camera *camera_;
  };
}

#endif //__TASK_CALCULATE_CAMERA_MATRIX_H__