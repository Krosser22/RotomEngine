/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "scenes/geometryScene.h"
#include "general/time.h"
#include "general/window.h"

void ROTOM::GeometryScene::init() {
  getCamera()->setupPerspective(glm::radians(45.0f), (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  //Root
  getRoot()->setPosition(0.0f, 5.0f, -12.0f);

  //Light
  clearLight();
  std::shared_ptr<DirectionalLight> light = std::shared_ptr<DirectionalLight>(new DirectionalLight("light"));
  light->setParent(getRoot());
  light->setPosition(0.0f, 0.0f, -10.0f);
  AddLight(light);

  //Nodes
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  std::shared_ptr<Geometry> geometry = std::shared_ptr<Geometry>(new Geometry());
  geometry->loadGeometry("Monkey/Monkey");
  std::shared_ptr<Drawable> drawable[amount];
  const float separation = -2.2f;
  const float pos_x_started = 15.0f;
  const float pos_y_started = 7.0f;
  const float pos_z_started = -5.0f;
  const int rows = 15;
  const int cols = 15;
  float pos[3] = { 0.0f, 0.0f, 0.0f };
  for (int i = 0; i < amount; ++i) {
    pos[0] = ((i % cols) * separation) + pos_x_started;
    pos[1] = ((i / (cols * rows)) * separation) + pos_y_started;
    pos[2] = (((i / cols) % rows) * separation) + pos_z_started;
    drawable[i] = std::shared_ptr<Drawable>(new Drawable("Drawable"));
    drawable[i]->setGeometry(geometry);
    drawable[i]->setMaterial(material);
    drawable[i]->setParent(getRoot());
    drawable[i]->setPosition(pos);
  }
}

void ROTOM::GeometryScene::input() {
  getCamera()->input();
}

void ROTOM::GeometryScene::update() {
  float sin_time = sin(TIME::appTime()) * 0.022f;
  getRoot()->move(sin_time, sin_time, sin_time);

  getCamera()->update();
}