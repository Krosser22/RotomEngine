/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "node.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"

ROTOM::Node::Node() {
  setPosition(0.0f, 0.0f, 0.0f);
  setRotation(0.0f, 0.0f, 0.0f);
  setScale(1.0f, 1.0f, 1.0f);

  parent_ = NULL;

  b_dirtyModelLocal_ = true;
  b_dirtyModelWorld_ = true;
};

ROTOM::Node::~Node() {
  if (parent_ != NULL) {
    parent_->removeChild(shared_from_this());
  }

  while (childs_.size() > 0) {
    childs_.at(childs_.size() - 1)->~Node();
    childs_.pop_back();
  }
}

void ROTOM::Node::move(const float movement[3]) {
  setPosition(v_position_.x + movement[0], v_position_.y + movement[1], v_position_.z + movement[2]);
}

void ROTOM::Node::move(const float x, const float y, const float z) {
  setPosition(v_position_.x + x, v_position_.y + y, v_position_.z + z);
}

void ROTOM::Node::moveX(const float movementX) {
  setPosition(v_position_.x + movementX, v_position_.y, v_position_.z);
}

void ROTOM::Node::moveY(const float movementY) {
  setPosition(v_position_.x, v_position_.y + movementY, v_position_.z);
}

void ROTOM::Node::moveZ(const float movementZ) {
  setPosition(v_position_.x, v_position_.y, v_position_.z + movementZ);
}

void ROTOM::Node::setPosition(const float position[3]) {
  setPosition(position[0], position[1], position[2]);
}

void ROTOM::Node::setPosition(const float x, const float y, const float z) {
  v_position_.x = x;
  v_position_.y = y;
  v_position_.z = z;
  setModelLocalDirty();
}

glm::vec3 ROTOM::Node::position() {
  return v_position_;
}

void ROTOM::Node::setPositionX(const float positionX) {
  v_position_.x = positionX;
  setPosition(positionX, v_position_.y, v_position_.z);
}

float ROTOM::Node::positionX() {
  return v_position_.x;
}

void ROTOM::Node::setPositionY(const float positionY) {
  setPosition(v_position_.x, positionY, v_position_.z);
}

float ROTOM::Node::positionY() {
  return v_position_.y;
}

void ROTOM::Node::setPositionZ(const float positionZ) {
  setPosition(v_position_.x, v_position_.y, positionZ);
}

float ROTOM::Node::positionZ() {
  return v_position_.z;
}

void ROTOM::Node::setRotation(const float rotation[3]) {
  setRotation(rotation[0], rotation[1], rotation[2]);
}

void ROTOM::Node::setRotation(const float x, const float y, const float z) {
  v_rotation_.x = x;
  v_rotation_.y = y;
  v_rotation_.z = z;
  setModelLocalDirty();
}

glm::vec3 ROTOM::Node::rotation() {
  return v_rotation_;
}

void ROTOM::Node::setRotationX(const float rotationX) {
  setRotation(rotationX, v_rotation_.y, v_rotation_.z);
}

float ROTOM::Node::rotationX() {
  return v_rotation_.x;
}

void ROTOM::Node::setRotationY(const float rotationY) {
  setRotation(v_rotation_.x, rotationY, v_rotation_.z);
}

float ROTOM::Node::rotationY() {
  return v_rotation_.y;
}

void ROTOM::Node::setRotationZ(const float rotationZ) {
  setRotation(v_rotation_.x, v_rotation_.y, rotationZ);
}

float ROTOM::Node::rotationZ() {
  return v_rotation_.z;
}

void ROTOM::Node::setScale(const float scale[3]) {
  setScale(scale[0], scale[1], scale[2]);
}

void ROTOM::Node::setScale(const float x, const float y, const float z) {
  v_scale_.x = x;
  v_scale_.y = y;
  v_scale_.z = z;
  setModelLocalDirty();
}

glm::vec3 ROTOM::Node::scale() {
  return v_scale_;
}

void ROTOM::Node::setScaleX(const float scaleX) {
  setScale(scaleX, v_scale_.y, v_scale_.z);
}

float ROTOM::Node::scaleX() {
  return v_scale_.x;
}

void ROTOM::Node::setScaleY(const float scaleY) {
  setScale(v_scale_.x, scaleY, v_scale_.z);
}

float ROTOM::Node::scaleY() {
  return v_scale_.y;
}

void ROTOM::Node::setScaleZ(const float scaleZ) {
  setScale(v_scale_.x, v_scale_.y, scaleZ);
}

float ROTOM::Node::scaleZ() {
  return v_scale_.z;
}

void ROTOM::Node::setModelLocal(glm::mat4 modelLocal) {
  m_modelLocal_ = modelLocal;
  b_dirtyModelLocal_ = false;
  b_dirtyModelWorld_ = true;
}

glm::mat4 *ROTOM::Node::modelLocal() {
  return &m_modelLocal_;
}

bool ROTOM::Node::isDirtyModelLocal() {
  return b_dirtyModelLocal_;
}

void ROTOM::Node::setModelWorld(glm::mat4 modelWorld) {
  m_modelWorld_ = modelWorld;
  b_dirtyModelWorld_ = false;
}

glm::mat4 *ROTOM::Node::modelWorld() {
  return &m_modelWorld_;
}

bool ROTOM::Node::isDirtyModelWorld() {
  return b_dirtyModelWorld_;
}

void ROTOM::Node::setParent(std::shared_ptr<Node> parent) {
  //TODO - Para que al attacharle un nuevo padre no se teletransporte [La inversa del padre nuevo] * [tu matriz world]
  m_modelLocal_ = glm::inverse(*parent->modelWorld()) * m_modelWorld_;

  glm::quat rotation;
  glm::vec3 skew;
  glm::vec4 perspective;
  glm::decompose(m_modelLocal_, v_scale_, rotation, v_position_, skew, perspective);
  v_rotation_ = glm::vec3(*glm::value_ptr(rotation)); //TODO - Change the variable type of rotation to glm::quat
  v_rotation_.x = glm::degrees(rotation.x);
  v_rotation_.y = glm::degrees(rotation.y);
  v_rotation_.z = glm::degrees(rotation.z);

  if (parent_) {
    parent_->removeChild(shared_from_this());
  }
  parent_ = parent;
  parent_->addChild(shared_from_this());
  
  b_dirtyModelWorld_ = true;

  m_modelWorld_ = *parent->modelWorld() * m_modelLocal_;
}

std::shared_ptr<ROTOM::Node> ROTOM::Node::parent() {
  return parent_;
}

void ROTOM::Node::addChild(std::shared_ptr<Node> child) {
  childs_.push_back(child);
  if (child->parent_.get() != this) {
    child->setParent(shared_from_this());
  }
}

void ROTOM::Node::removeChild(std::shared_ptr<Node> child) {
  for (unsigned int i = 0; i < childs_.size(); ++i) {
    if (child.get() == childs_.at(i).get()) {
      childs_.erase(childs_.begin() + i);
    }
  }
}

std::shared_ptr<ROTOM::Node> ROTOM::Node::getChildAt(unsigned int i) {
  return childs_.at(i);
}

const unsigned int ROTOM::Node::childCount() {
  return childs_.size();
}

void ROTOM::Node::setModelLocalDirty() {
  if (!b_dirtyModelLocal_) {
    alertChildsModelWorldChanged();
  }
  b_dirtyModelLocal_ = true;
}

void ROTOM::Node::alertChildsModelWorldChanged() {
  for (unsigned int i = 0; i < childs_.size(); ++i) {
    childs_.at(i)->b_dirtyModelWorld_ = true;
  }
}
