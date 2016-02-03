/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "camera.h"
#include "security.h"

ROTOM::Camera::Camera() {
  SECURITY::addSecurityCount(SECURITY::MyClass_Camera);

  commandDrawObject_.setRoot(&root_);
  commandDrawObject_.setProjectionMatrix(projectionMatrix());

  taskCalculateMatrix_ = std::shared_ptr<TaskCalculateMatrix>(new TaskCalculateMatrix(TaskType_CalculateMatrix));
};

ROTOM::Camera::~Camera() {
  SECURITY::removeSecurityCount(SECURITY::MyClass_Camera);

  commandDrawObject_.~CommandDrawObject();
  root_.~Node();
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

void ROTOM::Camera::setPosition(const float pos[3]) {
  v_position_ = glm::vec3(pos[0], pos[1], pos[2]);
  b_dirtyView_ = true;
}

float *ROTOM::Camera::position() {
  return glm::value_ptr(v_position_);
}

void ROTOM::Camera::setRotation(const float rot[3]) {
  v_rotation_ = glm::vec3(rot[0], rot[1], rot[2]);
  b_dirtyView_ = true;
}

float *ROTOM::Camera::rotation() {
  return glm::value_ptr(v_rotation_);
}

//void ROTOM::Camera::set_view_direction(const float pos[3]) {}

/*void ROTOM::Camera::set_view_target(const float pos[3]) {
  glm::vec3 cameraDirection;
  glm::vec3 p = glm::vec3(*pos);
  cameraDirection = glm::normalize(p - v_target_);
}*/

/*const float *ROTOM::Camera::target() {
  return glm::value_ptr(v_target_);
}*/

//void ROTOM::Camera::set_up_direction(const float pos[3]) {}

//const float *ROTOM::Camera::up_direction() {}

void ROTOM::Camera::setProjectionMatrix(const float data[16]) {
  m_projection_ = glm::mat4(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
}

float *ROTOM::Camera::projectionMatrix() {
  return glm::value_ptr(m_projection_);
}

void ROTOM::Camera::setViewMatrix(const float data[16]) {
  m_view_ = glm::mat4(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]);
}

float *ROTOM::Camera::viewMatrix() {
  if (b_dirtyView_) {
    cleanViewMatrix();
  }
  return glm::value_ptr(m_view_);
}

ROTOM::Node *ROTOM::Camera::root() {
  return &root_;
}

//void ROTOM::Camera::doCull(const Node *root) {}

void ROTOM::Camera::doRender() {
  taskManager_.waitUntilFinish();

  //DisplayList
  displayList_.addCommand(commandDrawObject_.get());
  displayList_.runAll();

  //TaskManager
  updateTasks();
}

void ROTOM::Camera::cleanViewMatrix() {
  //m_view_ = glm::scale(glm::mat4(), v_scale_);
  m_view_ = glm::rotate(glm::mat4(), v_rotation_[0], glm::vec3(1.0f, 0.0f, 0.0f));
  m_view_ = glm::rotate(m_view_, v_rotation_[1], glm::vec3(0.0f, 1.0f, 0.0f));
  m_view_ = glm::rotate(m_view_, v_rotation_[2], glm::vec3(0.0f, 0.0f, 1.0f));
  m_view_ = glm::translate(m_view_, v_position_);
  b_dirtyView_ = false;
}

void ROTOM::Camera::updateTaskCalculateModel() {
  taskCalculateMatrix_->nextTaskList_.clear();
  taskCalculateMatrix_->clearTask();
  std::shared_ptr<Node *>node = std::make_shared<Node *>(&root_);
  taskCalculateMatrix_->setInput(node);
  taskManager_.addTask(taskCalculateMatrix_);
}

void ROTOM::Camera::updateTasks() {
  updateTaskCalculateModel();
  //updateCalculateViews();
}