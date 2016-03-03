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
  //ModelLocal
  if (root_->isDirtyModelLocal()) {
    glm::mat4 modelLocal;
    modelLocal = glm::scale(glm::mat4(), root_->scale());
    modelLocal = glm::rotate(modelLocal, root_->rotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, root_->rotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, root_->rotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
    modelLocal = glm::translate(modelLocal, root_->position());
    root_->setModelLocal(modelLocal);
  }

  //ModelWorld
  if (root_->isDirtyModelWorld()) {
    //TODO - Check this next line
    glm::mat4 modelWorld = glm::mat4() * *root_->modelLocal();
    root_->setModelWorld(modelWorld);
  }

  for (unsigned int i = 0; i < root_->childCount(); ++i) {
    runOnNode(root_->getChildAt(i).get());
  }
}

void ROTOM::TaskCalculateMatrix::setInput(Node *root) {
  root_ = root;
}

void ROTOM::TaskCalculateMatrix::runOnNode(Node *node) {
  //ModelLocal
  if (node->isDirtyModelLocal()) {
    glm::mat4 modelLocal;
    modelLocal = glm::scale(glm::mat4(), node->scale());
    modelLocal = glm::rotate(modelLocal, node->rotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, node->rotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, node->rotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
    modelLocal = glm::translate(modelLocal, node->position());
    node->setModelLocal(modelLocal);
  }

  //ModelWorld
  if (node->isDirtyModelWorld()) {
    glm::mat4 modelWorld = *node->parent()->modelWorld() * *node->modelLocal();
    node->setModelWorld(modelWorld);
  }

  for (unsigned int i = 0; i < node->childCount(); ++i) {
    runOnNode(node->getChildAt(i).get());
  }
}