/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "scene.h"

static ROTOM::DisplayList displayList_;
static ROTOM::CommandDrawObject commandDrawObject_;
static std::shared_ptr<ROTOM::TaskCalculateMatrix> taskCalculateMatrix_;
static ROTOM::Camera camera_;
static std::shared_ptr<ROTOM::Node> root_;
static std::vector<std::shared_ptr<ROTOM::Light>> lights_;

void ROTOM::Scene::init() {
  root_ = std::shared_ptr<Node>(new Node());
  if (lights_.size() <= 0) {
    lights_.push_back(std::shared_ptr<ROTOM::Light>(new Light()));
  }
  commandDrawObject_.setLight(lights_.at(0).get());
  commandDrawObject_.setProjectionMatrix(camera_.projectionMatrix());
  commandDrawObject_.setRoot(root_.get());
  commandDrawObject_.setViewMatrix(camera_.viewMatrix());
  taskCalculateMatrix_ = std::shared_ptr<TaskCalculateMatrix>(new TaskCalculateMatrix(TaskType_CalculateMatrix));
}

void ROTOM::Scene::draw() {
  ROTOM::TASKMANAGER::waitUntilFinish();

  //DisplayList
  displayList_.addCommand(commandDrawObject_.get());
  displayList_.runAll();

  //TaskManager
  std::shared_ptr<Node *> node = std::make_shared<Node *>(root_.get());
  taskCalculateMatrix_->nextTaskList_.clear();
  taskCalculateMatrix_->clearTask();
  taskCalculateMatrix_->setInput(node);
  ROTOM::TASKMANAGER::addTask(taskCalculateMatrix_);
}

void ROTOM::Scene::destroy() {
  commandDrawObject_.~CommandDrawObject();
  root_.get()->~Node();
}

std::shared_ptr<ROTOM::Node> ROTOM::Scene::getRoot() {
  return root_;
}

ROTOM::Camera *ROTOM::Scene::getCamera() {
  return &camera_;
}

std::vector<std::shared_ptr<ROTOM::Light>> ROTOM::Scene::getLight() {
  return lights_;
}

void ROTOM::Scene::addLight(std::shared_ptr<Light> light) {
  lights_.push_back(light);
}