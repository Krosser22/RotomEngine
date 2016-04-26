/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "proceduralScene.h"
#include "general/input.h"
#include "general/procedural.h"
#include "general/window.h"

void ROTOM::ProceduralScene::init() {
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  //Material1: Color
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  material->setShaderFromPath("basics/5_SpecularLight_Blinn-Phong.vertx", "basics/5_SpecularLight_Blinn-Phong.frag");

  //Root
  getRoot()->setPosition(-5.0f, -10.0f, -28.0f);

  //Chunk
  chunk_ = std::shared_ptr<Chunk>(new Chunk("Chunk"));
  chunk_->init(getRoot());

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(1.0f, 1.0f, -2.0f);
  AddLight(light);
}

void ROTOM::ProceduralScene::input() {
  static float x = 0, y = 0, z = 0;
  static const float amount_change = 0.01f;

  if (INPUT::IsKeyDown('W')) {
    x += amount_change;
  }

  if (INPUT::IsKeyDown('S')) {
    x -= amount_change;
  }

  if (INPUT::IsKeyDown('A')) {
    y += amount_change;
  }

  if (INPUT::IsKeyDown('D')) {
    y -= amount_change;
  }

  if (INPUT::IsKeyDown('Q')) {
    z += amount_change;
  }

  if (INPUT::IsKeyDown('E')) {
    z -= amount_change;
  }

  //printf("%f, %f, %f = %f\n", x, y, z, PROCEDURAL::perlinNoise(x, y, z));
}

void ROTOM::ProceduralScene::update() {

}

void ROTOM::ProceduralScene::draw() {

}