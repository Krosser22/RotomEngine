/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/cameraMovement.h"
#include "general/input.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <stdio.h>

void ROTOM::CameraMovement::setCameraToMove(Camera *camera) {
  camera_ = camera;
  cameraPos_ = camera_->position();
}

void ROTOM::CameraMovement::input() {
  if (INPUT::IsMousePressed(1)) {
    lastX_ = INPUT::MousePositionX();
    lastY_ = INPUT::MousePositionY();
  }

  if (INPUT::MouseWheel()) {
    scroll();
  }

  if (INPUT::IsMouseDown(1)) {
    movement();
    rotation();
  }
}

void ROTOM::CameraMovement::movement() {
  //Forward
  if (INPUT::IsKeyDown('W')) {
    cameraPos_ += movementSpeed_ * cameraFront_;
  }

  //Backward
  if (INPUT::IsKeyDown('S')) {
    cameraPos_ -= movementSpeed_ * cameraFront_;
  }

  //Left
  if (INPUT::IsKeyDown('A')) {
    cameraPos_ -= glm::normalize(glm::cross(cameraFront_, cameraUp_)) * movementSpeed_;
  }

  //Right
  if (INPUT::IsKeyDown('D')) {
    cameraPos_ += glm::normalize(glm::cross(cameraFront_, cameraUp_)) * movementSpeed_;
  }

  //Up
  if (INPUT::IsKeyDown('E')) {
    cameraPos_ += glm::normalize(cameraUp_) * movementSpeed_;
  }

  //Down
  if (INPUT::IsKeyDown('Q')) {
    cameraPos_ -= glm::normalize(cameraUp_) * movementSpeed_;
  }
}

void ROTOM::CameraMovement::rotation() {
  xoffset_ = INPUT::MousePositionX() - lastX_;
  yoffset_ = lastY_ - INPUT::MousePositionY(); // Reversed since y-coordinates go from bottom to left
  lastX_ = INPUT::MousePositionX();
  lastY_ = INPUT::MousePositionY();

  xoffset_ *= rotationSpeed_;
  yoffset_ *= rotationSpeed_;

  yaw_ += xoffset_;
  pitch_ += yoffset_;

  // Make sure that when pitch is out of bounds, screen doesn't get flipped
  if (pitch_ > 89.0f) {
    pitch_ = 89.0f;
  }

  if (pitch_ < -89.0f) {
    pitch_ = -89.0f;
  }

  front_.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_)); 
  front_.y = sin(glm::radians(pitch_));
  front_.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  cameraFront_ = glm::normalize(front_);
}

void ROTOM::CameraMovement::scroll() {
  if (fov_ >= 1.0f && fov_ <= 45.0f) {
    fov_ -= INPUT::MouseWheel() * scrollSpeed_;
  }

  if (fov_ <= 1.0f) {
    fov_ = 1.0f;
  }

  if (fov_ >= 45.0f) {
    fov_ = 45.0f;
  }
}

void ROTOM::CameraMovement::update() {
  // Camera/View transformation
  camera_->setViewMatrix(glm::lookAt(cameraPos_, cameraPos_ + cameraFront_, cameraUp_));

  cameraRot_ = cameraPos_ + front_;
  printf("%f, %f, %f\n\n", cameraRot_[0], cameraRot_[1], cameraRot_[2]);
  glm::fmat4 view = glm::fmat4();
  view = glm::rotate(view, cameraRot_.y, rotX);
  view = glm::rotate(view, cameraRot_.z, rotY);
  view = glm::translate(view, -cameraPos_);
  //camera_->setViewMatrix(view);


}