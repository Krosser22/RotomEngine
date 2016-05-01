/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/camera.h"
#include "render/graphics.h"
#include "general/input.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <stdio.h>

ROTOM::Camera::Camera() {
  front_.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  front_.y = sin(glm::radians(pitch_));
  front_.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  front_ = glm::normalize(front_);
}

ROTOM::Camera::~Camera() {}

void ROTOM::Camera::input() {
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

void ROTOM::Camera::movement() {
  if (INPUT::IsKeyDown('W')) position_ += movementSpeed_ * front_; //Forward
  if (INPUT::IsKeyDown('S')) position_ -= movementSpeed_ * front_; //Backward
  if (INPUT::IsKeyDown('A')) position_ += glm::normalize(glm::cross(front_, up_)) * movementSpeed_; //Left
  if (INPUT::IsKeyDown('D')) position_ -= glm::normalize(glm::cross(front_, up_)) * movementSpeed_; //Right
  if (INPUT::IsKeyDown('E')) position_ += glm::normalize(up_) * movementSpeed_; //Up
  if (INPUT::IsKeyDown('Q')) position_ -= glm::normalize(up_) * movementSpeed_; //Down
}

void ROTOM::Camera::rotation() {
  xoffset_ = INPUT::MousePositionX() - lastX_;
  yoffset_ = lastY_ - INPUT::MousePositionY(); // Reversed since y-coordinates go from bottom to left
  lastX_ = INPUT::MousePositionX();
  lastY_ = INPUT::MousePositionY();

  xoffset_ *= rotationSpeed_;
  yoffset_ *= rotationSpeed_;

  yaw_ -= xoffset_;
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
  front_ = glm::normalize(front_);
}

void ROTOM::Camera::scroll() {
  if (fov_ >= 1.0f && fov_ <= 45.0f) {
    fov_ -= INPUT::MouseWheel() * scrollSpeed_;
  }

  if (fov_ <= 1.0f) {
    fov_ = 1.0f;
  }

  if (fov_ >= 45.0f) {
    fov_ = 45.0f;
  }
  //printf("FOV: %f\n", fov_);
}

void ROTOM::Camera::update() {
  //Camera/View transformation
  viewMatrix_ = glm::lookAt(position_, position_ + front_, up_);
}

void ROTOM::Camera::setPosition(float x, float y, float z) {
  position_.x = x;
  position_.y = y;
  position_.z = z;
  viewMatrix_ = glm::lookAt(position_, position_ + front_, up_);
}

float *ROTOM::Camera::position() {
  return glm::value_ptr(position_);
}

void ROTOM::Camera::setYaw(float yaw) {
  yaw_ = yaw;

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
  front_ = glm::normalize(front_);
}

float ROTOM::Camera::yaw() {
  return yaw_;
}

void ROTOM::Camera::setPitch(float pitch) {
  pitch_ = pitch;

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
  front_ = glm::normalize(front_);
}

float ROTOM::Camera::pitch() {
  return pitch_;
}

void ROTOM::Camera::setViewMatrix(glm::fmat4 viewMatrix) {
  viewMatrix_ = viewMatrix;
}

float *ROTOM::Camera::viewMatrix() {
  return glm::value_ptr(viewMatrix_);
}

void ROTOM::Camera::setupPerspective(const float fovy, const float aspect, const float znear, const float zfar) {
  projectionMatrix_ = glm::perspective(fovy, aspect, znear, zfar);
}

void ROTOM::Camera::setupOrtho(const float left, const float right, const float bottom, const float top, const float znear, const float zfar) {
  projectionMatrix_ = glm::ortho(left, right, bottom, top, znear, zfar);
}

void ROTOM::Camera::setupFrustum(const float left, const float right, const float bottom, const float top, const float znear, const float zfar) {
  projectionMatrix_ = glm::frustum(left, right, bottom, top, znear, zfar);
}

float *ROTOM::Camera::projectionMatrix() {
  return glm::value_ptr(projectionMatrix_);
}

/*
//void ROTOM::Camera::setViewMatrix(glm::fvec3 eye, glm::fvec3 center, glm::fvec3 up) {setViewMatrix(glm::lookAt(eye, center, up));}

//void ROTOM::Camera::set_view_direction(const float pos[3]) {}

//void ROTOM::Camera::setViewTarget(const float position[3]) {glm::fvec3 cameraDirection = glm::normalize(position - target_);}

//const float *ROTOM::Camera::target() {return glm::value_ptr(target_);}

//const float *ROTOM::Camera::forward() {return glm::value_ptr(target_ - position_);}

//void ROTOM::Camera::set_up_direction(const float pos[3]) {}

//const float *ROTOM::Camera::up_direction() {}

//void ROTOM::Camera::doCull(const Camera *root) {}

//void ROTOM::Camera::doRender() {}
*/