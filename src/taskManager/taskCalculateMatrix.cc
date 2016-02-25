/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "taskManager/taskCalculateMatrix.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

ROTOM::TaskCalculateMatrix::TaskCalculateMatrix(TaskType taskType) {
  taskType_ = taskType;
}

ROTOM::TaskCalculateMatrix::~TaskCalculateMatrix() {}

void ROTOM::TaskCalculateMatrix::run() {
  //ModelLocal
  if (nodeData[root_].dirtyModelLocal) {
    glm::mat4 modelLocal;
    modelLocal = glm::scale(glm::mat4(), nodeData[root_].scale);
    modelLocal = glm::rotate(modelLocal, nodeData[root_].rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, nodeData[root_].rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, nodeData[root_].rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    modelLocal = glm::translate(modelLocal, nodeData[root_].position);
    nodeData[root_].modelLocal = modelLocal;
  }

  //ModelWorld
  if (nodeData[root_].dirtyModelWorld) {
    glm::mat4 modelWorld = glm::mat4() * nodeData[root_].modelLocal;
    nodeData[root_].modelWorld = modelWorld;
  }

  for (unsigned int i = 0; i < nodeData[root_].childs.size(); ++i) {
    runOnNode(nodeData[root_].childs.at(i));
  }
}

void ROTOM::TaskCalculateMatrix::setInput(unsigned int root) {
  root_ = root;
}

/*void ROTOM::TaskCalculateMatrix::setMyCamera(std::shared_ptr<Camera> camera) {
  camera_ = camera;
}

void ROTOM::TaskCalculateMatrix::runOnCamera() {
  //ModelLocal
  if ((*camera_)->isDirtyModelLocal()) {
    glm::mat4 modelLocal;
    modelLocal = glm::scale(glm::mat4(), (*camera_)->scale());
    modelLocal = glm::rotate(modelLocal, (*camera_)->rotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, (*camera_)->rotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, (*camera_)->rotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
    modelLocal = glm::translate(modelLocal, (*camera_)->position());
    (*camera_)->setModelLocal(modelLocal);
  }

  //ModelWorld
  if ((*camera_)->isDirtyModelWorld()) {
    glm::mat4 modelWorld = (*(*camera_)->parent()->modelWorld()) * (*(*camera_)->modelLocal());
    (*camera_)->setModelWorld(modelWorld);
  }
}*/

void ROTOM::TaskCalculateMatrix::runOnNode(unsigned int node) {
  //ModelLocal
  if (nodeData[node].dirtyModelLocal) {
    glm::mat4 modelLocal;
    modelLocal = glm::scale(glm::mat4(), nodeData[node].scale);
    modelLocal = glm::rotate(modelLocal, nodeData[node].rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, nodeData[node].rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    modelLocal = glm::rotate(modelLocal, nodeData[node].rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    modelLocal = glm::translate(modelLocal, nodeData[node].position);
    nodeData[node].modelLocal = modelLocal;
  }

  //ModelWorld
  if (nodeData[node].dirtyModelWorld) {
    glm::mat4 modelWorld = nodeData[nodeData[node].parent].modelWorld * nodeData[node].modelLocal;
    nodeData[node].modelWorld = modelWorld;
  }

  for (unsigned int i = 0; i < nodeData[node].childs.size(); ++i) {
    runOnNode(nodeData[node].childs.at(i));
  }
}