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

void ROTOM::ProceduralScene::init() {
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  geometry_ = std::shared_ptr<Geometry>(new Geometry());

  //Material1: Color
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  material->setShaderFromPath("basics/5_SpecularLight_Blinn-Phong.vertx", "basics/5_SpecularLight_Blinn-Phong.frag");

  //Root
  getRoot()->setPositionX(-2.9f);

  //Drawable
  std::shared_ptr<Drawable> drawable = std::shared_ptr<Drawable>(new Drawable("Drawable"));
  drawable->setGeometry(geometry_);
  drawable->setMaterial(material);
  drawable->setParent(getRoot());
  drawable->setPositionZ(-5.0f);

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(1.0f, 1.0f, -2.0f);
  AddLight(light);
}

void ROTOM::ProceduralScene::input() {

}

void ROTOM::ProceduralScene::update() {
  Node *node = getRoot()->getChildAt(0).get();
  node->setRotationZ(node->rotation().z + 0.01f);
}