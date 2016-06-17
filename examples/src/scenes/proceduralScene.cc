/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "scenes/proceduralScene.h"
#include "general/input.h"
#include "general/window.h"
#include <glm/gtc/matrix_transform.hpp>

void ROTOM::ProceduralScene::init() {
  //Camera
  getCamera()->setupPerspective(glm::radians(45.0f), (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(0.0f, 2.0f, 0.0f);
  
  //Light
  clearLights();
  std::shared_ptr<DirectionalLight> light = std::shared_ptr<DirectionalLight>(new DirectionalLight("light"));
  light->setParent(getRoot());
  light->setPosition(0.0f, 10.0f, 0.0f);
  addDirectionalLight(light);

  //Chunk
  chunk_ = std::shared_ptr<Chunk>(new Chunk("Chunk"));
  chunk_->init(getRoot(), getCamera(), 10);
}

void ROTOM::ProceduralScene::input() {
  getCamera()->input();
}

void ROTOM::ProceduralScene::update() {
  chunk_->update();
}