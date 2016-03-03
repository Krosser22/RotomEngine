/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "taskManager/taskCalculateMatrix.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

ROTOM::TaskCalculateMatrix::TaskCalculateMatrix() {}

ROTOM::TaskCalculateMatrix::~TaskCalculateMatrix() {}

void ROTOM::TaskCalculateMatrix::run() {
  if (root_->isDirtyModelLocal()) {
    glm::mat4 modelLocal;
    modelLocal = glm::scale(glm::mat4(), root_->scale());
    modelLocal = glm::rotate(modelLocal, root_->rotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, root_->rotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, root_->rotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
    modelLocal = glm::translate(modelLocal, root_->position());
    root_->setModelLocal(modelLocal);

    root_->setModelWorld(glm::mat4() * *root_->modelLocal());
  }

  for (unsigned int i = 0; i < root_->childCount(); ++i) {
    calculateNode(root_->getChildAt(i).get());
  }
}

void ROTOM::TaskCalculateMatrix::setInput(Node *root) {
  root_ = root;
}

void ROTOM::TaskCalculateMatrix::calculateNode(Node *node) {
  if (node->isDirtyModelLocal()) {
    glm::mat4 modelLocal;
    modelLocal = glm::scale(glm::mat4(), node->scale());
    modelLocal = glm::rotate(modelLocal, node->rotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, node->rotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, node->rotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
    modelLocal = glm::translate(modelLocal, node->position());
    node->setModelLocal(modelLocal);

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
    glm::mat4 modelLocal;
    modelLocal = glm::scale(glm::mat4(), node->scale());
    modelLocal = glm::rotate(modelLocal, node->rotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, node->rotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, node->rotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
    modelLocal = glm::translate(modelLocal, node->position());
    node->setModelLocal(modelLocal);
  }

  node->setModelWorld(*node->parent()->modelWorld() * *node->modelLocal());

  for (unsigned int i = 0; i < node->childCount(); ++i) {
    calculateNodeForSure(node->getChildAt(i).get());
  }
}