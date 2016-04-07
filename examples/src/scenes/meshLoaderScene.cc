/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/input.h"
#include "general/time.h"
#include "general/window.h"
#include "scenes/meshLoaderScene.h"

void ROTOM::MeshLoaderScene::init() {
  //Camera
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  //Geometry
  std::shared_ptr<Geometry> geometry = std::shared_ptr<Geometry>(new Geometry());

  //Material
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material("../../../../obj/Sirus5ColonialCity/Maps/1ab2.jpg"));
  material->setShaderFromPath("basics/4_SpecularLight.vertx", "basics/4_SpecularLight.frag");

  //Drawable
  std::shared_ptr<Drawable> drawable = std::shared_ptr<Drawable>(new Drawable("drawable"));
  getRoot()->setPosition(0.0f, 1.0f, -5.0f);
  drawable->setGeometry(geometry);
  drawable->setMaterial(material);
  drawable->setParent(getRoot());

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setScale(0.1f, 0.1f, 0.1f);
  light->setPositionZ(10.0f);
  AddLight(light);
}

void ROTOM::MeshLoaderScene::input() {
  if (INPUT::IsKeyPressed('Q')) {
    rotating_ = !rotating_;
  }
}

void ROTOM::MeshLoaderScene::update() {
  if (rotating_) {
    getRoot()->getChildAt(0)->setRotationY(getRoot()->getChildAt(0)->rotation().y + 0.01f);
  }
}

void ROTOM::MeshLoaderScene::draw() {
  RenderScene(getCamera());
  RenderImGui();
}
