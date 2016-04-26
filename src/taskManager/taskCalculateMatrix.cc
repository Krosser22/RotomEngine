/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "taskManager/taskCalculateMatrix.h"
#include <glm/gtc/matrix_transform.hpp>

glm::fmat4 identity = glm::fmat4();
glm::fmat4 modelLocal = glm::fmat4();
glm::fvec3 rotX = glm::fvec3(1.0f, 0.0f, 0.0f);
glm::fvec3 rotY = glm::fvec3(0.0f, 1.0f, 0.0f);
glm::fvec3 rotZ = glm::fvec3(0.0f, 0.0f, 1.0f);

inline void calculateModelLocal(ROTOM::Node *node) {
  modelLocal = glm::scale(identity, node->scale());
  modelLocal = glm::rotate(modelLocal, node->rotation().x, rotX);
  modelLocal = glm::rotate(modelLocal, node->rotation().y, rotY);
  modelLocal = glm::rotate(modelLocal, node->rotation().z, rotZ);
  modelLocal = glm::translate(modelLocal, node->position());
  node->setModelLocal(modelLocal);
}

ROTOM::TaskCalculateMatrix::TaskCalculateMatrix() {}

ROTOM::TaskCalculateMatrix::~TaskCalculateMatrix() {}

void ROTOM::TaskCalculateMatrix::run() {
  if (root_->isDirtyModelLocal()) {
    calculateModelLocal(root_);
    root_->setModelWorld(modelLocal);

    for (unsigned int i = 0; i < root_->childCount(); ++i) {
      calculateNodeForSure(root_->getChildAt(i).get());
    }
  } else {
    for (unsigned int i = 0; i < root_->childCount(); ++i) {
      calculateNode(root_->getChildAt(i).get());
    }
  }
}

void ROTOM::TaskCalculateMatrix::setInput(Node *root) {
  root_ = root;
}

void ROTOM::TaskCalculateMatrix::calculateNode(Node *node) {
  if (node->isDirtyModelLocal()) {
    calculateModelLocal(node);
    node->setModelWorld(*node->parent()->modelWorld() * *node->modelLocal());

    for (unsigned int i = 0; i < node->childCount(); ++i) {
      calculateNodeForSure(node->getChildAt(i).get());
    }
  } else {
    for (unsigned int i = 0; i < node->childCount(); ++i) {
      calculateNode(node->getChildAt(i).get());
    }
  }
}

void ROTOM::TaskCalculateMatrix::calculateNodeForSure(Node *node) {
  if (node->isDirtyModelLocal()) {
    calculateModelLocal(node);
  }
  node->setModelWorld(*node->parent()->modelWorld() * *node->modelLocal());

  for (unsigned int i = 0; i < node->childCount(); ++i) {
    calculateNodeForSure(node->getChildAt(i).get());
  }
}