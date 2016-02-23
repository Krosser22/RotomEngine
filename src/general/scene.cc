/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/scene.h"

static ROTOM::Camera camera_;
static std::shared_ptr<ROTOM::Node> root_;
static std::vector<std::shared_ptr<ROTOM::Light>> lights_;

std::shared_ptr<ROTOM::Node> ROTOM::Scene::getRoot() {
  return root_;
}

void ROTOM::Scene::setRoot(std::shared_ptr<ROTOM::Node> root) {
  root_ = root;
}

ROTOM::Camera *ROTOM::Scene::getCamera() {
  return &camera_;
}

std::vector<std::shared_ptr<ROTOM::Light>> ROTOM::Scene::getLight() {
  return lights_;
}

void ROTOM::Scene::AddLight(std::shared_ptr<Light> light) {
  lights_.push_back(light);
}