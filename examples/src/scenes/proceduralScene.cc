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
  getCamera()->setPosition(5.0f, 0.0f, 8.0f);
  getCamera()->setPitch(-18.0f);
  getCamera()->setYaw(-97.0f);

  //Material1: Color
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  material->setShaderFromPath("shadows/1_Basic.vertx", "shadows/1_Basic.frag");

  //Root
  getRoot()->setPosition(-5.0f, -10.0f, -28.0f);

  //Chunk
  chunk_ = std::shared_ptr<Chunk>(new Chunk("Chunk"));
  chunk_->init(getRoot(), getCamera(), 1);

  //Light
  clearLights();
  std::shared_ptr<DirectionalLight> light = std::shared_ptr<DirectionalLight>(new DirectionalLight("light"));
  light->setParent(getRoot());
  light->setPosition(1.0f, 1.0f, -2.0f);
  addDirectionalLight(light);
}

void ROTOM::ProceduralScene::input() {
  getCamera()->input();
}

void ROTOM::ProceduralScene::update() {
  chunk_->update();

  getCamera()->update();
}