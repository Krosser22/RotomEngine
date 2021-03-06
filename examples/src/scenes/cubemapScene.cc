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
  std::shared_ptr<Material> materialReflect = std::shared_ptr<Material>(new Material("../../../../img/texture.png"));
  materialReflect->setShaderFromPath("reflect.vertx", "reflect.frag");

  std::shared_ptr<Material> materialRefract = std::shared_ptr<Material>(new Material("../../../../img/texture.png"));
  materialRefract->setShaderFromPath("refract.vertx", "refract.frag");

  //Drawables
  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable("1"));
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable("2"));
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable("3"));
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable("4"));

  drawable1->setGeometry(geometry);
  drawable1->setMaterial(materialReflect);
  drawable1->setParent(getRoot());

  drawable2->setGeometry(geometry);
  drawable2->setMaterial(materialRefract);
  drawable2->setParent(drawable1);
  drawable2->setPositionX(1.0f);

  drawable3->setGeometry(geometry);
  drawable3->setMaterial(materialReflect);
  drawable3->setParent(drawable2);
  drawable3->setPositionX(1.0f);

  drawable4->setGeometry(geometry);
  drawable4->setMaterial(materialRefract);
  drawable4->setParent(drawable3);
  drawable4->setPositionX(1.0f);

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