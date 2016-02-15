/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "scene.h"

ROTOM::Scene::Scene() {
  if (lights_.size() <= 0) {
    lights_.push_back(Light());
  }
  commandDrawObject_.setLight(&lights_.at(0));
  commandDrawObject_.setProjectionMatrix(camera_.projectionMatrix());
  commandDrawObject_.setRoot(&root_);
  commandDrawObject_.setViewMatrix(camera_.viewMatrix());
  taskCalculateMatrix_ = std::shared_ptr<TaskCalculateMatrix>(new TaskCalculateMatrix(TaskType_CalculateMatrix));
}

ROTOM::Scene::~Scene() {
  commandDrawObject_.~CommandDrawObject();
  root_.~Node();
}

void ROTOM::Scene::update() {
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
