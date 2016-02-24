/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "node/node.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"

ROTOM::Node::Node() {
  ID_ = nextID++;
  assert("ERROR: Too many Nodes created" && ID_ < kNodeDataAmount);

  setPosition(0.0f, 0.0f, 0.0f);
  setRotation(0.0f, 0.0f, 0.0f);
  setScale(1.0f, 1.0f, 1.0f);

  parent_ = -1; //TODO - Change this to 0 to set the root the 0 node of the array
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

unsigned int ROTOM::Node::ID() {
  return ID_;
}

void ROTOM::Node::move(const float movement[3]) {
  setPosition(nodeData[ID_].v_position_.x + movement[0], nodeData[ID_].v_position_.y + movement[1], nodeData[ID_].v_position_.z + movement[2]);
}

void ROTOM::Node::move(const float x, const float y, const float z) {
  setPosition(nodeData[ID_].v_position_.x + x, nodeData[ID_].v_position_.y + y, nodeData[ID_].v_position_.z + z);
}

void ROTOM::Node::moveX(const float movementX) {
  setPosition(nodeData[ID_].v_position_.x + movementX, nodeData[ID_].v_position_.y, nodeData[ID_].v_position_.z);
}

void ROTOM::Node::moveY(const float movementY) {
  setPosition(nodeData[ID_].v_position_.x, nodeData[ID_].v_position_.y + movementY, nodeData[ID_].v_position_.z);
}

void ROTOM::Node::moveZ(const float movementZ) {
  setPosition(nodeData[ID_].v_position_.x, nodeData[ID_].v_position_.y, nodeData[ID_].v_position_.z + movementZ);
}

void ROTOM::Node::setPosition(const float position[3]) {
  setPosition(position[0], position[1], position[2]);
}

void ROTOM::Node::setPosition(const float x, const float y, const float z) {
  nodeData[ID_].v_position_.x = x;
  nodeData[ID_].v_position_.y = y;
  nodeData[ID_].v_position_.z = z;
  setModelLocalDirty();
}

glm::vec3 ROTOM::Node::position() {
  return nodeData[ID_].v_position_;
}

void ROTOM::Node::setPositionX(const float positionX) {
  nodeData[ID_].v_position_.x = positionX;
  setPosition(positionX, nodeData[ID_].v_position_.y, nodeData[ID_].v_position_.z);
}

float ROTOM::Node::positionX() {
  return nodeData[ID_].v_position_.x;
}

void ROTOM::Node::setPositionY(const float positionY) {
  setPosition(nodeData[ID_].v_position_.x, positionY, nodeData[ID_].v_position_.z);
}

float ROTOM::Node::positionY() {
  return nodeData[ID_].v_position_.y;
}

void ROTOM::Node::setPositionZ(const float positionZ) {
  setPosition(nodeData[ID_].v_position_.x, nodeData[ID_].v_position_.y, positionZ);
}

float ROTOM::Node::positionZ() {
  return nodeData[ID_].v_position_.z;
}

void ROTOM::Node::setRotation(const float rotation[3]) {
  setRotation(rotation[0], rotation[1], rotation[2]);
}

void ROTOM::Node::setRotation(const float x, const float y, const float z) {
  nodeData[ID_].v_rotation_.x = x;
  nodeData[ID_].v_rotation_.y = y;
  nodeData[ID_].v_rotation_.z = z;
  setModelLocalDirty();
}

glm::vec3 ROTOM::Node::rotation() {
  return nodeData[ID_].v_rotation_;
}

void ROTOM::Node::setRotationX(const float rotationX) {
  setRotation(rotationX, nodeData[ID_].v_rotation_.y, nodeData[ID_].v_rotation_.z);
}

float ROTOM::Node::rotationX() {
  return nodeData[ID_].v_rotation_.x;
}

void ROTOM::Node::setRotationY(const float rotationY) {
  setRotation(nodeData[ID_].v_rotation_.x, rotationY, nodeData[ID_].v_rotation_.z);
}

float ROTOM::Node::rotationY() {
  return nodeData[ID_].v_rotation_.y;
}

void ROTOM::Node::setRotationZ(const float rotationZ) {
  setRotation(nodeData[ID_].v_rotation_.x, nodeData[ID_].v_rotation_.y, rotationZ);
}

float ROTOM::Node::rotationZ() {
  return nodeData[ID_].v_rotation_.z;
}

void ROTOM::Node::setScale(const float scale[3]) {
  setScale(scale[0], scale[1], scale[2]);
}

void ROTOM::Node::setScale(const float x, const float y, const float z) {
  nodeData[ID_].v_scale_.x = x;
  nodeData[ID_].v_scale_.y = y;
  nodeData[ID_].v_scale_.z = z;
  setModelLocalDirty();
}

glm::vec3 ROTOM::Node::scale() {
  return nodeData[ID_].v_scale_;
}

void ROTOM::Node::setScaleX(const float scaleX) {
  setScale(scaleX, nodeData[ID_].v_scale_.y, nodeData[ID_].v_scale_.z);
}

float ROTOM::Node::scaleX() {
  return nodeData[ID_].v_scale_.x;
}

void ROTOM::Node::setScaleY(const float scaleY) {
  setScale(nodeData[ID_].v_scale_.x, scaleY, nodeData[ID_].v_scale_.z);
}

float ROTOM::Node::scaleY() {
  return nodeData[ID_].v_scale_.y;
}

void ROTOM::Node::setScaleZ(const float scaleZ) {
  setScale(nodeData[ID_].v_scale_.x, nodeData[ID_].v_scale_.y, scaleZ);
}

float ROTOM::Node::scaleZ() {
  return nodeData[ID_].v_scale_.z;
}

void ROTOM::Node::setModelLocal(glm::mat4 modelLocal) {
  nodeData[ID_].m_modelLocal_ = modelLocal;
  nodeData[ID_].b_dirtyModelLocal_ = false;
  nodeData[ID_].b_dirtyModelWorld_ = true;
}

glm::mat4 *ROTOM::Node::modelLocal() {
  return &nodeData[ID_].m_modelLocal_;
}

bool ROTOM::Node::isDirtyModelLocal() {
  return nodeData[ID_].b_dirtyModelLocal_;
}

void ROTOM::Node::setModelWorld(glm::mat4 modelWorld) {
  nodeData[ID_].m_modelWorld_ = modelWorld;
  nodeData[ID_].b_dirtyModelWorld_ = false;
}

glm::mat4 *ROTOM::Node::modelWorld() {
  return &nodeData[ID_].m_modelWorld_;
}

bool ROTOM::Node::isDirtyModelWorld() {
  return nodeData[ID_].b_dirtyModelWorld_;
}

void ROTOM::Node::setParent(unsigned int parent) {
  //TODO - Para que al attacharle un nuevo padre no se teletransporte [La inversa del padre nuevo] * [tu matriz world]
  nodeData[ID_].m_modelLocal_ = glm::inverse(*parent->modelWorld()) * nodeData[ID_].m_modelWorld_;

  glm::quat rotation;
  glm::vec3 skew;
  glm::vec4 perspective;
  glm::decompose(nodeData[ID_].m_modelLocal_, nodeData[ID_].v_scale_, rotation, nodeData[ID_].v_position_, skew, perspective);
  nodeData[ID_].v_rotation_ = glm::vec3(*glm::value_ptr(rotation)); //TODO - Change the variable type of rotation to glm::quat
  nodeData[ID_].v_rotation_.x = glm::degrees(rotation.x);
  nodeData[ID_].v_rotation_.y = glm::degrees(rotation.y);
  nodeData[ID_].v_rotation_.z = glm::degrees(rotation.z);

  if (parent_) {
    parent_->removeChild(shared_from_this());
  }
  parent_ = parent;
  parent_->addChild(shared_from_this());
  
  nodeData[ID_].b_dirtyModelWorld_ = true;

  nodeData[ID_].m_modelWorld_ = *parent->modelWorld() * nodeData[ID_].m_modelLocal_;
}

unsigned int ROTOM::Node::parent() {
  return parent_;
}

void ROTOM::Node::addChild(unsigned int child) {
  childs_.push_back(child);
  if (child->parent_.get() != this) {
    child->setParent(shared_from_this());
  }
}

void ROTOM::Node::removeChild(unsigned int child) {
  for (unsigned int i = 0; i < childs_.size(); ++i) {
    if (child.get() == childs_.at(i).get()) {
      childs_.erase(childs_.begin() + i);
    }
  }
}

unsigned int ROTOM::Node::getChildAt(unsigned int i) {
  return childs_.at(i);
}

const unsigned int ROTOM::Node::childCount() {
  return childs_.size();
}

void ROTOM::Node::setModelLocalDirty() {
  if (!nodeData[ID_].b_dirtyModelLocal_) {
    alertChildsModelWorldChanged();
  }
}

void ROTOM::Node::alertChildsModelWorldChanged() {
  nodeData[ID_].b_dirtyModelLocal_ = true;
  for (unsigned int i = 0; i < childs_.size(); ++i) {
    nodeData[childs_.at(i)->ID()].b_dirtyModelWorld_ = true;
  }
}
