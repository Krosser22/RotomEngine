/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "node.h"
#include "security.h"

ROTOM::Node::Node() {
  SECURITY::addSecurityCount(SECURITY::MyClass_Node);

  setPositionX(0.0f);
  setPositionY(0.0f);
  setPositionZ(0.0f);

  setRotationX(0.0f);
  setRotationY(0.0f);
  setRotationZ(0.0f);

  setScaleX(1.0f);
  setScaleY(1.0f);
  setScaleZ(1.0f);

  parent_ = NULL;

  b_dirtyModelLocal_ = true;
  b_dirtyModelWorld_ = true;
};

ROTOM::Node::~Node() {
  SECURITY::removeSecurityCount(SECURITY::MyClass_Node);

  if (parent_ != NULL) {
    parent_->removeChild(this);
  }

  while (childs_.size() > 0) {
    childs_.at(childs_.size() - 1)->~Node();
    childs_.pop_back();
  }
}

void ROTOM::Node::move(const float movement[3]) {
  v_position_.x += movement[0];
  v_position_.y += movement[1];
  v_position_.z += movement[2];
}

void ROTOM::Node::moveX(const float movementX) {
  v_position_.x += movementX;
}

void ROTOM::Node::moveY(const float movementY) {
  v_position_.y += movementY;
}

void ROTOM::Node::moveZ(const float movementZ) {
  v_position_.z += movementZ;
}

void ROTOM::Node::setPosition(const float position[3]) {
  v_position_.x = position[0];
  v_position_.y = position[1];
  v_position_.z = position[2];
  b_dirtyModelLocal_ = true;
  alertChildsModelWorldChanged();
}

glm::vec3 ROTOM::Node::position() {
  return v_position_;
}

void ROTOM::Node::setPositionX(const float positionX) {
  v_position_.x = positionX;
}

float ROTOM::Node::positionX() {
  return v_position_.x;
}

void ROTOM::Node::setPositionY(const float positionY) {
  v_position_.y = positionY;
}

float ROTOM::Node::positionY() {
  return v_position_.y;
}

void ROTOM::Node::setPositionZ(const float positionZ) {
  v_position_.z = positionZ;
}

float ROTOM::Node::positionZ() {
  return v_position_.z;
}

void ROTOM::Node::setRotation(const float rotation[3]) {
  v_rotation_ = glm::vec3(rotation[0], rotation[1], rotation[2]);
  b_dirtyModelLocal_ = true;
  alertChildsModelWorldChanged();
}

glm::vec3 ROTOM::Node::rotation() {
  return v_rotation_;
}

void ROTOM::Node::setRotationX(const float rotationX) {
  v_rotation_.x = rotationX;
}

float ROTOM::Node::rotationX() {
  return v_rotation_.x;
}

void ROTOM::Node::setRotationY(const float rotationY) {
  v_rotation_.y = rotationY;
}

float ROTOM::Node::rotationY() {
  return v_rotation_.y;
}

void ROTOM::Node::setRotationZ(const float rotationZ) {
  v_rotation_.z = rotationZ;
}

float ROTOM::Node::rotationZ() {
  return v_rotation_.z;
}

void ROTOM::Node::setScale(const float scale[3]) {
  v_scale_ = glm::vec3(scale[0], scale[1], scale[2]);
  b_dirtyModelLocal_ = true;
  alertChildsModelWorldChanged();
}

glm::vec3 ROTOM::Node::scale() {
  return v_scale_;
}

void ROTOM::Node::setScaleX(const float scaleX) {
  v_scale_.x = scaleX;
}

float ROTOM::Node::scaleX() {
  return v_scale_.x;
}

void ROTOM::Node::setScaleY(const float scaleY) {
  v_scale_.y = scaleY;
}

float ROTOM::Node::scaleY() {
  return v_scale_.y;
}

void ROTOM::Node::setScaleZ(const float scaleZ) {
  v_scale_.z = scaleZ;
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

void ROTOM::Node::setParent(Node *parent) {
  //TODO - Para que al attacharle un nuevo padre no se teletransporte 
  //[La inversa del padre nuevo] * [tu matriz world]
  //m_modelLocal_ = glm::inverse(*parent->modelWorld()) * m_modelWorld_;

  glm::vec3 oldScale;
  glm::quat oldRotation;
  glm::vec3 oldPosition;
  glm::vec3 oldSkew;
  glm::vec4 oldPerspective;
  glm::decompose(m_modelWorld_, oldScale, oldRotation, oldPosition, oldSkew, oldPerspective);
  //v_rotation_ = glm::vec3(*glm::value_ptr(oldRotation)); //TODO - Change the variable type of rotation to glm::quat

  if (parent_) {
    parent_->removeChild(this);
  }
  parent_ = parent;
  parent_->addChild(this);
  b_dirtyModelWorld_ = true;

  glm::mat4 newModelWorld = (*parent->modelWorld()) * (m_modelLocal_);
  glm::vec3 newScale;
  glm::quat newRotation;
  glm::vec3 newPosition;
  glm::vec3 newSkew;
  glm::vec4 newPerspective;
  glm::decompose(newModelWorld, newScale, newRotation, newPosition, newSkew, newPerspective);

  v_scale_ = oldScale + (newScale - oldScale);
  v_rotation_ = glm::vec3(*glm::value_ptr(oldRotation)) + (glm::vec3(*glm::value_ptr(newRotation)) - glm::vec3(*glm::value_ptr(oldRotation)));
  v_position_ = (newPosition + oldPosition);
}

const ROTOM::Node *ROTOM::Node::parent() {
  return parent_;
}

void ROTOM::Node::addChild(Node *child) {
  childs_.push_back(child);
  if (child->parent_ != this) {
    childs_.at(childs_.size() - 1)->setParent(this);
  }
}

void ROTOM::Node::removeChild(const Node *child) {
  for (unsigned int i = 0; i < childs_.size(); ++i) {
    if (child == childs_.at(i)) {
      childs_.erase(childs_.begin() + i);
    }
  }
}

ROTOM::Node *ROTOM::Node::getChildAt(unsigned int i) {
  return childs_.at(i);
}

const unsigned int ROTOM::Node::childCount() {
  return childs_.size();
}

void ROTOM::Node::alertChildsModelWorldChanged() {
  for (unsigned int i = 0; i < childs_.size(); ++i) {
    childs_.at(i)->b_dirtyModelWorld_ = true;
  }
}
