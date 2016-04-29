/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/camera.h"
#include "render/graphics.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

ROTOM::Camera::Camera() {}

ROTOM::Camera::~Camera() {}

void ROTOM::Camera::move(const float movement[3]) {
  setPosition(position_.x + movement[0], position_.y + movement[1], position_.z + movement[2]);
}

void ROTOM::Camera::move(const float x, const float y, const float z) {
  setPosition(position_.x + x, position_.y + y, position_.z + z);
}

void ROTOM::Camera::moveX(const float movementX) {
  setPosition(position_.x + movementX, position_.y, position_.z);
}

void ROTOM::Camera::moveY(const float movementY) {
  setPosition(position_.x, position_.y + movementY, position_.z);
}

void ROTOM::Camera::moveZ(const float movementZ) {
  setPosition(position_.x, position_.y, position_.z + movementZ);
}

void ROTOM::Camera::setPosition(const float position[3]) {
  setPosition(position[0], position[1], position[2]);
}

void ROTOM::Camera::setPosition(const float x, const float y, const float z) {
  position_.x = x;
  position_.y = y;
  position_.z = z;
  dirtyViewMatrix_ = true;
}

glm::fvec3 ROTOM::Camera::position() {
  return position_;
}

void ROTOM::Camera::setPositionX(const float positionX) {
  setPosition(positionX, position_.y, position_.z);
}

float ROTOM::Camera::positionX() {
  return position_.x;
}

void ROTOM::Camera::setPositionY(const float positionY) {
  setPosition(position_.x, positionY, position_.z);
}

float ROTOM::Camera::positionY() {
  return position_.y;
}

void ROTOM::Camera::setPositionZ(const float positionZ) {
  setPosition(position_.x, position_.y, positionZ);
}

float ROTOM::Camera::positionZ() {
  return position_.z;
}

void ROTOM::Camera::setRotation(const float rotation[3]) {
  setRotation(rotation[0], rotation[1], rotation[2]);
}

void ROTOM::Camera::setRotation(const float x, const float y, const float z) {
  rotation_.x = x;
  rotation_.y = y;
  rotation_.z = z;
  dirtyViewMatrix_ = true;
}

glm::fvec3 ROTOM::Camera::rotation() {
  return rotation_;
}

void ROTOM::Camera::setRotationX(const float rotationX) {
  setRotation(rotationX, rotation_.y, rotation_.z);
}

float ROTOM::Camera::rotationX() {
  return rotation_.x;
}

void ROTOM::Camera::setRotationY(const float rotationY) {
  setRotation(rotation_.x, rotationY, rotation_.z);
}

float ROTOM::Camera::rotationY() {
  return rotation_.y;
}

void ROTOM::Camera::setRotationZ(const float rotationZ) {
  setRotation(rotation_.x, rotation_.y, rotationZ);
}

float ROTOM::Camera::rotationZ() {
  return rotation_.z;
}

void ROTOM::Camera::setViewMatrix(glm::fmat4 viewMatrix) {
  viewMatrix_ = viewMatrix;
  dirtyViewMatrix_ = false;
}

/*void ROTOM::Camera::setViewMatrix(glm::fvec3 eye, glm::fvec3 center, glm::fvec3 up) {
  setViewMatrix(glm::lookAt(eye, center, up));
}*/

float *ROTOM::Camera::viewMatrix() {
  /*viewMatrix_ = glm::rotate(viewMatrix_, rotation_.x, rotX);
  viewMatrix_ = glm::rotate(viewMatrix_, rotation_.y, rotY);
  viewMatrix_ = glm::rotate(viewMatrix_, rotation_.z, rotZ);
  viewMatrix_ = glm::translate(-position_);*/
  return glm::value_ptr(viewMatrix_);
}

bool ROTOM::Camera::isDirtyViewMatrix() {
  return dirtyViewMatrix_;
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

//void ROTOM::Camera::set_view_direction(const float pos[3]) {}

//void ROTOM::Camera::setViewTarget(const float pos[3]) {
//  glm::fvec3 cameraDirection;
//  glm::fvec3 p = glm::fvec3(*pos);
//  cameraDirection = glm::normalize(p - target_);
//}

//const float *ROTOM::Camera::target() {
//  return glm::value_ptr(target_);
//}

//const float *ROTOM::Camera::forward() {
//  return glm::value_ptr(target_ - position_);
//}

//void ROTOM::Camera::set_up_direction(const float pos[3]) {}

//const float *ROTOM::Camera::up_direction() {}

//void ROTOM::Camera::doCull(const Camera *root) {}

//void ROTOM::Camera::doRender() {}