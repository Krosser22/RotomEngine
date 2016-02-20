/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "camera.h"
#include "security.h"
#include "taskManager.h"

ROTOM::Camera::Camera() {
  SECURITY::addSecurityCount(SECURITY::MyClass_Camera);
  setPosition(0.0f, 0.0f, 0.0f);
};

ROTOM::Camera::~Camera() {
  SECURITY::removeSecurityCount(SECURITY::MyClass_Camera);
};

void ROTOM::Camera::setupPerspective(const float fovy, const float aspect, const float znear, const float zfar) {
  m_projection_ = glm::perspective(fovy, aspect, znear, zfar);
}

void ROTOM::Camera::setupOrtho(const float left, const float right, const float bottom, const float top, const float znear, const float zfar) {
  m_projection_ = glm::ortho(left, right, bottom, top, znear, zfar);
}

void ROTOM::Camera::setupFrustum(const float left, const float right, const float bottom, const float top, const float znear, const float zfar) {
  m_projection_ = glm::frustum(left, right, bottom, top, znear, zfar);
}

//void ROTOM::Camera::set_view_direction(const float pos[3]) {}

void ROTOM::Camera::setViewTarget(const float pos[3]) {
  glm::vec3 cameraDirection;
  glm::vec3 p = glm::vec3(*pos);
  cameraDirection = glm::normalize(p - v_target_);
}

const float *ROTOM::Camera::target() {
  return glm::value_ptr(v_target_);
}

const float *ROTOM::Camera::forward() {
  return glm::value_ptr(v_target_ - v_position_);
}

//void ROTOM::Camera::set_up_direction(const float pos[3]) {}

//const float *ROTOM::Camera::up_direction() {}

void ROTOM::Camera::setProjectionMatrix(const float data[16]) {
  m_projection_ = glm::mat4(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
}

float *ROTOM::Camera::projectionMatrix() {
  return glm::value_ptr(m_projection_);
}

void ROTOM::Camera::setViewMatrix(const float data[16]) {
  m_modelLocal_ = glm::mat4(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
}

float *ROTOM::Camera::viewMatrix() {
  return glm::value_ptr(m_modelLocal_);
}

//void ROTOM::Camera::doCull(const Node *root) {}

//void ROTOM::Camera::doRender(const Node *root) {}