/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/time.h"
#include "general/window.h"
#include "scenes/geometryScene.h"

void ROTOM::GeometryScene::init() {
  //GetCamera()->setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(0.0f, 0.0f, 0.0f);

  geometry = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  std::shared_ptr<Drawable> drawable[amount];
  geometry->loadGeometry("Monkey/Monkey");

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(0.0f, 0.0f, -10.0f);
  AddLight(light);

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
    drawable[i] = std::shared_ptr<Drawable>(new Drawable("i"));
    drawable[i]->setGeometry(geometry);
    drawable[i]->setMaterial(material);
    drawable[i]->setParent(getRoot());
    drawable[i]->setPosition(pos);
  }
}

void ROTOM::GeometryScene::update() {
  float sin_time = sin(TIME::appTime()) * 0.022f;
  getRoot()->move(sin_time, sin_time, sin_time);
}