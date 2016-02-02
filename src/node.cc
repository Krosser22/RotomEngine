/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "node.h"
#include "security.h"

ROTOM::Node::Node() {
  SECURITY::addSecurityCount(ROTOM::SECURITY::MyClass_Node);

  float position[3] = { 0.0f, 0.0f, 0.0f };
  setPosition(position);

  float rotation[3] = { 0.0f, 0.0f, 0.0f };
  setRotation(rotation);

  float scale[3] = { 1.0f, 1.0f, 1.0f };
  setScale(scale);

  parent_ = NULL;

  b_dirtyModelLocal_ = false;
  b_dirtyModelWorld_ = false;

  m_modelLocal_ = glm::mat4();
  m_modelWorld_ = glm::mat4();
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

void ROTOM::Node::setPosition(const float position[3]) {
  v_position_ = glm::vec3(position[0], position[1], position[2]);
  b_dirtyModelLocal_ = true;
  alertChildsModelWorldChanged();
}

glm::vec3 ROTOM::Node::position() {
  return v_position_;
}

void ROTOM::Node::setRotation(const float rotation[3]) {
  v_rotation_ = glm::vec3(rotation[0], rotation[1], rotation[2]);
  b_dirtyModelLocal_ = true;
  alertChildsModelWorldChanged();
}

glm::vec3 ROTOM::Node::rotation() {
  return v_rotation_;
}

void ROTOM::Node::setScale(const float scale[3]) {
  v_scale_ = glm::vec3(scale[0], scale[1], scale[2]);
  b_dirtyModelLocal_ = true;
  alertChildsModelWorldChanged();
}

glm::vec3 ROTOM::Node::scale() {
  return v_scale_;
}

void ROTOM::Node::setModelLocal(glm::mat4 modelLocal) {
  m_modelLocal_ = modelLocal;
  b_dirtyModelLocal_ = false;
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
  //TODO - Para que al attacharle un nuevo padre no se teletransporte [La inversa del padre nuevo] * [tu matriz world]
  m_modelLocal_ = glm::inverse(*parent->modelWorld()) * m_modelWorld_;
  
  glm::quat rotation;
  glm::vec3 skew;
  glm::vec4 perspective;
  glm::decompose(m_modelLocal_, v_scale_, rotation, v_position_, skew, perspective);
  v_rotation_ = glm::vec3(*glm::value_ptr(rotation)); //TODO - Change the variable type of rotation to glm::quat

  if (parent_) {
    parent_->removeChild(this);
  }
  parent_ = parent;
  parent_->addChild(this);
  b_dirtyModelWorld_ = true;
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
