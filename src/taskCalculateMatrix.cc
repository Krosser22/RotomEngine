/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "TaskCalculateMatrix.h"
#include "security.h"

ROTOM::TaskCalculateMatrix::TaskCalculateMatrix(TaskType taskType) {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_TaskCalculateModel);

  taskType_ = taskType;
};

ROTOM::TaskCalculateMatrix::~TaskCalculateMatrix() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_TaskCalculateModel);
};

void ROTOM::TaskCalculateMatrix::run() {
  //runOnNode(*(&root_)->get());
  //runOnNode(*root_);

  if ((*root_)->isDirtyModelLocal()) {
    glm::mat4 modelLocal;
    modelLocal = glm::scale(glm::mat4(), (*root_)->scale());
    modelLocal = glm::rotate(modelLocal, (*root_)->rotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, (*root_)->rotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, (*root_)->rotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
    modelLocal = glm::translate(modelLocal, (*root_)->position());
    (*root_)->setModelLocal(modelLocal);
  }

  for (unsigned int i = 0; i < (*root_)->childCount(); ++i) {
    runOnNode((*root_)->getChildAt(i));
  }
}

void ROTOM::TaskCalculateMatrix::clearTask() {
  nextTaskList_.clear();
}

void ROTOM::TaskCalculateMatrix::setInput(std::shared_ptr<Node *> root) {
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
    Node *parent = ((Node *)node->parent());
    glm::mat4 modelWorld = (*parent->modelWorld()) * (*node->modelLocal());
    node->setModelWorld(modelWorld);
  }

  for (unsigned int i = 0; i < node->childCount(); ++i) {
    runOnNode(node->getChildAt(i));
  }
}