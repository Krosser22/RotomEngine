/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "scene.h"

static ROTOM::DisplayList displayList_;
static ROTOM::CommandDrawObject commandDrawObject_;
static std::shared_ptr<ROTOM::TaskCalculateMatrix> taskCalculateMatrix_;

void ROTOM::Scene::init() {
  if (lights_.size() <= 0) {
    lights_.push_back(Light());
  }
  commandDrawObject_.setLight(&lights_.at(0));
  commandDrawObject_.setProjectionMatrix(camera_.projectionMatrix());
  commandDrawObject_.setRoot(&root_);
  commandDrawObject_.setViewMatrix(camera_.viewMatrix());
  taskCalculateMatrix_ = std::shared_ptr<TaskCalculateMatrix>(new TaskCalculateMatrix(TaskType_CalculateMatrix));
}

void ROTOM::Scene::draw() {
  ROTOM::TASKMANAGER::waitUntilFinish();

  //DisplayList
  displayList_.addCommand(commandDrawObject_.get());
  displayList_.runAll();

  //TaskManager
  std::shared_ptr<Node *>node = std::make_shared<Node *>(&root_);
  taskCalculateMatrix_->nextTaskList_.clear();
  taskCalculateMatrix_->clearTask();
  taskCalculateMatrix_->setInput(node);
  ROTOM::TASKMANAGER::addTask(taskCalculateMatrix_);
}

void ROTOM::Scene::destroy() {
  commandDrawObject_.~CommandDrawObject();
  root_.~Node();
}

ROTOM::Node *ROTOM::Scene::getRoot() {
  return &root_;
}
