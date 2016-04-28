/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "taskManager/taskCalculateCameraMatrix.h"
#include <glm/gtc/matrix_transform.hpp>

ROTOM::TaskCalculateCameraMatrix::TaskCalculateCameraMatrix() {}

ROTOM::TaskCalculateCameraMatrix::~TaskCalculateCameraMatrix() {}

void ROTOM::TaskCalculateCameraMatrix::run() {
  if (camera_->isDirtyViewMatrix()) {
    camera_->setViewMatrix(glm::lookAt(camera_->position(), camera_->rotation(), glm::fvec3(0.0f, 1.0f, 0.0f)));
  }
}

void ROTOM::TaskCalculateCameraMatrix::setInput(Camera *camera) {
  camera_ = camera;
}