/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/scene.h"

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

void ROTOM::Scene::clearLight() {
  lights_.clear();
}

ROTOM::Camera *ROTOM::Scene::getCamera() {
  return &camera_;
}