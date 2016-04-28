/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/scene.h"

ROTOM::Camera camera_;
std::shared_ptr<ROTOM::Node> root_;
std::vector<std::shared_ptr<ROTOM::Light>> lights_;

void ROTOM::Scene::setRoot(std::shared_ptr<Node> root) {
  root_ = root;
}

std::shared_ptr<ROTOM::Node> ROTOM::Scene::getRoot() {
  return root_;
}

void ROTOM::Scene::AddLight(std::shared_ptr<Light> light) {
  lights_.push_back(light);
}

std::vector<std::shared_ptr<ROTOM::Light>> ROTOM::Scene::getLight() {
  return lights_;
}

ROTOM::Camera *ROTOM::Scene::getCamera() {
  return &camera_;
}