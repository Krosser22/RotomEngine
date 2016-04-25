/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/node.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

ROTOM::Node::Node() {
  type_ = kNodeType_Node;
  name_ = "no_name";
  setPosition(0.0f, 0.0f, 0.0f);
  setRotation(0.0f, 0.0f, 0.0f);
  setScale(1.0f, 1.0f, 1.0f);
  parent_ = NULL;
}

ROTOM::Node::Node(char *name) {
  type_ = kNodeType_Node;
  name_ = name;
  setPosition(0.0f, 0.0f, 0.0f);
  setRotation(0.0f, 0.0f, 0.0f);
  setScale(1.0f, 1.0f, 1.0f);
  parent_ = NULL;
}

ROTOM::Node::~Node() {
  if (parent_ != NULL) {
    parent_->removeChild(shared_from_this());
  }

  while (childs_.size() > 0) {
    childs_.at(childs_.size() - 1)->~Node();
    childs_.pop_back();
  }
}

ROTOM::NodeType ROTOM::Node::type() {
  return type_;
}

void ROTOM::Node::setName(char *name) {
  name_ = name;
}

const char *ROTOM::Node::name() {
  return name_.c_str();
}

void ROTOM::Node::move(const float movement[3]) {
  setPosition(position_.x + movement[0], position_.y + movement[1], position_.z + movement[2]);
}

void ROTOM::Node::move(const float x, const float y, const float z) {
  setPosition(position_.x + x, position_.y + y, position_.z + z);
}

void ROTOM::Node::moveX(const float movementX) {
  setPosition(position_.x + movementX, position_.y, position_.z);
}

void ROTOM::Node::moveY(const float movementY) {
  setPosition(position_.x, position_.y + movementY, position_.z);
}

void ROTOM::Node::moveZ(const float movementZ) {
  setPosition(position_.x, position_.y, position_.z + movementZ);
}

void ROTOM::Node::setPosition(const float position[3]) {
  setPosition(position[0], position[1], position[2]);
}

void ROTOM::Node::setPosition(const float x, const float y, const float z) {
  position_.x = x;
  position_.y = y;
  position_.z = z;
  dirtyModelLocal_ = true;
}

glm::fvec3 ROTOM::Node::position() {
  return position_;
}

void ROTOM::Node::setPositionX(const float positionX) {
  position_.x = positionX;
  setPosition(positionX, position_.y, position_.z);
}

float ROTOM::Node::positionX() {
  return position_.x;
}

void ROTOM::Node::setPositionY(const float positionY) {
  setPosition(position_.x, positionY, position_.z);
}

float ROTOM::Node::positionY() {
  return position_.y;
}

void ROTOM::Node::setPositionZ(const float positionZ) {
  setPosition(position_.x, position_.y, positionZ);
}

float ROTOM::Node::positionZ() {
  return position_.z;
}

void ROTOM::Node::setRotation(const float rotation[3]) {
  setRotation(rotation[0], rotation[1], rotation[2]);
}

void ROTOM::Node::setRotation(const float x, const float y, const float z) {
  rotation_.x = x;
  rotation_.y = y;
  rotation_.z = z;
  dirtyModelLocal_ = true;
}

glm::fvec3 ROTOM::Node::rotation() {
  return rotation_;
}

void ROTOM::Node::setRotationX(const float rotationX) {
  setRotation(rotationX, rotation_.y, rotation_.z);
}

float ROTOM::Node::rotationX() {
  return rotation_.x;
}

void ROTOM::Node::setRotationY(const float rotationY) {
  setRotation(rotation_.x, rotationY, rotation_.z);
}

float ROTOM::Node::rotationY() {
  return rotation_.y;
}

void ROTOM::Node::setRotationZ(const float rotationZ) {
  setRotation(rotation_.x, rotation_.y, rotationZ);
}

float ROTOM::Node::rotationZ() {
  return rotation_.z;
}

void ROTOM::Node::setScale(const float scale[3]) {
  setScale(scale[0], scale[1], scale[2]);
}

void ROTOM::Node::setScale(const float x, const float y, const float z) {
  scale_.x = x;
  scale_.y = y;
  scale_.z = z;
  dirtyModelLocal_ = true;
}

glm::fvec3 ROTOM::Node::scale() {
  return scale_;
}

void ROTOM::Node::setScaleX(const float scaleX) {
  setScale(scaleX, scale_.y, scale_.z);
}

float ROTOM::Node::scaleX() {
  return scale_.x;
}

void ROTOM::Node::setScaleY(const float scaleY) {
  setScale(scale_.x, scaleY, scale_.z);
}

float ROTOM::Node::scaleY() {
  return scale_.y;
}

void ROTOM::Node::setScaleZ(const float scaleZ) {
  setScale(scale_.x, scale_.y, scaleZ);
}

float ROTOM::Node::scaleZ() {
  return scale_.z;
}

void ROTOM::Node::setModelLocal(glm::fmat4 modelLocal) {
  modelLocal_ = modelLocal;
  dirtyModelLocal_ = false;
}

glm::fmat4 *ROTOM::Node::modelLocal() {
  return &modelLocal_;
}

bool ROTOM::Node::isDirtyModelLocal() {
  return dirtyModelLocal_;
}

void ROTOM::Node::setModelWorld(glm::fmat4 modelWorld) {
  modelWorld_ = modelWorld;
}

glm::fmat4 *ROTOM::Node::modelWorld() {
  return &modelWorld_;
}

void ROTOM::Node::setParent(std::shared_ptr<Node> parent) {
  //Para que al attacharle un nuevo padre no se teletransporte [La inversa del padre nuevo] * [tu matriz world]
  modelLocal_ = glm::inverse(*parent->modelWorld()) * modelWorld_;

  glm::quat rotation;
  glm::fvec3 skew;
  glm::fvec4 perspective;
  glm::decompose(modelLocal_, scale_, rotation, position_, skew, perspective);
  rotation_ = glm::fvec3(*glm::value_ptr(rotation)); //TODO - Change the variable type of rotation to glm::quat
  rotation_.x = glm::degrees(rotation_.x);
  rotation_.y = glm::degrees(rotation_.y);
  rotation_.z = glm::degrees(rotation_.z);

  if (parent != NULL) {
    parent->removeChild(shared_from_this());
  }
  parent_ = parent;
  parent_->addChild(shared_from_this());

  dirtyModelLocal_ = true;

  modelWorld_ = *parent->modelWorld() * modelLocal_;
}

std::shared_ptr<ROTOM::Node> ROTOM::Node::parent() {
  return parent_;
}

void ROTOM::Node::addChild(std::shared_ptr<Node> child) {
  childs_.push_back(child);
  if (child->parent().get() != this) {
    child->setParent(shared_from_this());
  }
}

void ROTOM::Node::removeChild(std::shared_ptr<Node> child) {
  for (unsigned int i = 0; i < childs_.size(); ++i) {
    if (child == childs_.at(i)) {
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