/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "scenes/cubemapScene.h"
#include "general/input.h"
#include "general/window.h"

void ROTOM::CubemapScene::init() {
  //Camera
  getCamera()->setupPerspective(glm::radians(45.0f), (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(0.0f, 1.0f, -1.0f);

  //Geometry
  std::shared_ptr<Geometry> geometry = std::shared_ptr<Geometry>(new Geometry());

  //Material
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material("../../../../img/texture.png"));

  //Drawables
  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable("1"));
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable("2"));
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable("3"));
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable("4"));

  drawable1->setGeometry(geometry);
  drawable1->setMaterial(material);
  drawable1->setParent(getRoot());

  drawable2->setGeometry(geometry);
  drawable2->setMaterial(material);
  drawable2->setParent(drawable1);
  drawable2->setPositionX(1.0f);

  drawable3->setGeometry(geometry);
  drawable3->setMaterial(material);
  drawable3->setParent(drawable2);
  drawable3->setPositionX(1.0f);

  drawable4->setGeometry(geometry);
  drawable4->setMaterial(material);
  drawable4->setParent(drawable3);
  drawable4->setPositionX(1.0f);

  //Light
  clearLight();
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(2.2f, 0.0f, 2.2f);
  light->materialSettings()->color_[0] = 0.8f;
  light->materialSettings()->color_[1] = 0.6f;
  light->materialSettings()->color_[2] = 0.4f;
  AddLight(light);

  //Cubemap
  cubemap_.init("");
}

void ROTOM::CubemapScene::input() {
  getCamera()->input();
}

void ROTOM::CubemapScene::update() {
  if (INPUT::IsKeyDown('Z')) {
    Node *node = getRoot()->getChildAt(0)->getChildAt(0).get();
    node->setRotationX(node->rotation().x + 0.01f);
  }

  getCamera()->update();
}

void ROTOM::CubemapScene::draw() {
  cubemap_.draw(getCamera()->projectionMatrix(), getCamera()->viewMatrix());
}