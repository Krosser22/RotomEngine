/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "scenes/defaultScene.h"
#include "general/input.h"
#include "general/time.h"
#include "general/window.h"

void ROTOM::DefaultScene::init() {
  getCamera()->setupPerspective(glm::radians(45.0f), (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getRoot()->setPositionZ(-4.0f);

  geometry_ = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Material> material1 = std::shared_ptr<Material>(new Material("../../../../img/texture1.png"));
  std::shared_ptr<Material> material2 = std::shared_ptr<Material>(new Material("../../../../img/texture2.png"));
  std::shared_ptr<Material> material3 = std::shared_ptr<Material>(new Material("../../../../img/texture3.png"));
  std::shared_ptr<Material> material4 = std::shared_ptr<Material>(new Material());
  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable("1"));
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable("2"));
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable("3"));
  std::shared_ptr<Drawable> drawable[amount_];

  drawable1->setGeometry(geometry_);
  drawable1->setMaterial(material1);
  drawable1->setParent(getRoot());
  drawable1->setPositionZ(-5.0f);

  drawable2->setGeometry(geometry_);
  drawable2->setMaterial(material2);
  drawable2->setParent(drawable1);

  drawable3->setGeometry(geometry_);
  drawable3->setMaterial(material3);
  drawable3->setParent(drawable2);

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->specularIntensity_[0] = 0.1f;
  light->specularIntensity_[1] = 0.1f;
  light->specularIntensity_[2] = 0.1f;
  AddLight(light);

  const float separation = -2.2f;
  const float pos_x_started = 15.0f;
  const float pos_y_started = 7.0f;
  const float pos_z_started = -5.0f;
  const int rows = 15;
  const int cols = 15;
  float pos[3] = { 0.0f, 0.0f, 0.0f };
  for (int i = 0; i < amount_; ++i) {
    pos[0] = ((i % cols) * separation) + pos_x_started;
    pos[1] = ((i / (cols * rows)) * separation) + pos_y_started;
    pos[2] = (((i / cols) % rows) * separation) + pos_z_started;
    drawable[i] = std::shared_ptr<Drawable>(new Drawable("i"));
    drawable[i]->setGeometry(geometry_);
    drawable[i]->setMaterial(material4);
    drawable[i]->setParent(drawable1);
    drawable[i]->setPosition(pos);
  }
}

void ROTOM::DefaultScene::input() {
  //Add Cube
  if (INPUT::IsKeyPressed('R')) {
    static float posX = -2.0f;
    std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
    std::shared_ptr<Drawable> drawableNew = std::shared_ptr<Drawable>(new Drawable("input"));
    drawableNew->setGeometry(geometry_);
    drawableNew->setMaterial(material);
    drawableNew->setParent(getRoot()->getChildAt(0));
    drawableNew->setPositionX(posX);
    posX -= 1.0f;
  }

  getCamera()->input();
}

void ROTOM::DefaultScene::update() {
  float sin_time = sin(TIME::appTime()) * 0.022f;
  getRoot()->getChildAt(0)->moveX(sin_time);
  getRoot()->getChildAt(0)->getChildAt(0)->moveY(sin_time);
  getRoot()->getChildAt(0)->getChildAt(0)->getChildAt(0)->moveZ(sin_time);

  getCamera()->update();
}