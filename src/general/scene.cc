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

void ROTOM::Scene::addDirectionalLight(std::shared_ptr<DirectionalLight> light) {
  directionalLights_.push_back(light);
}

std::vector<std::shared_ptr<ROTOM::DirectionalLight>> ROTOM::Scene::getDirectionalLights() {
  return directionalLights_;
}

void ROTOM::Scene::addSpotLight(std::shared_ptr<SpotLight> light) {
  spotLights_.push_back(light);
}

std::vector<std::shared_ptr<ROTOM::SpotLight>> ROTOM::Scene::getSpotLights() {
  return spotLights_;
}

void ROTOM::Scene::clearLights() {
  directionalLights_.clear();
  spotLights_.clear();
}

ROTOM::Camera *ROTOM::Scene::getCamera() {
  return &camera_;
}