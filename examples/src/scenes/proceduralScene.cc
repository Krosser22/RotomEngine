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
  getCamera()->setupPerspective(glm::radians(45.0f), (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  //Material1: Color
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  material->setShaderFromPath("basics/5_SpecularLight_Blinn-Phong.vertx", "basics/5_SpecularLight_Blinn-Phong.frag");

  //Root
  getRoot()->setPosition(-5.0f, -10.0f, -28.0f);

  //Chunk
  chunk_ = std::shared_ptr<Chunk>(new Chunk("Chunk"));
  chunk_->init(getRoot(), 25, 1, 1);

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(1.0f, 1.0f, -2.0f);
  AddLight(light);
}

void ROTOM::ProceduralScene::input() {
  getCamera()->input();
}

void ROTOM::ProceduralScene::update() {
  chunk_->update();

  getCamera()->update();
}