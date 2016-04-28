/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "scenes/depthScene.h"
#include "general/input.h"
#include "general/time.h"
#include "general/window.h"
#include <glm/gtc/matrix_transform.hpp>

void ROTOM::DepthScene::init() {
  cameraMovement_.setCameraToMove(getCamera());
  getCamera()->setupPerspective(glm::radians(45.0f), (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  geometry_ = std::shared_ptr<Geometry>(new Geometry());

  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  material->setShaderFromPath("depthBuffer.vertx", "depthBuffer.frag");

  drawableBase_ = std::shared_ptr<Drawable>(new Drawable("DrawableBase"));
  drawableBase_->setGeometry(geometry_);
  drawableBase_->setMaterial(material);
  drawableBase_->setParent(getRoot());
  drawableBase_->setPosition(-1.0f, -1.0f, 0.0f);

  std::shared_ptr<Drawable> drawable[amount];
  const float separation = -2.0f;
  const float pos_x_started = 8.0f;
  const float pos_y_started = 0.0f;
  const float pos_z_started = 0.0f;
  const int rows = 10;
  const int cols = 10;
  float pos[3] = { 0.0f, 0.0f, 0.0f };
  for (int i = 0; i < amount; ++i) {
    pos[0] = ((i % cols) * separation) + pos_x_started;
    pos[1] = ((i / (cols * rows)) * separation) + pos_y_started;
    pos[2] = (((i / cols) % rows) * separation) + pos_z_started;
    drawable[i] = std::shared_ptr<Drawable>(new Drawable("i"));
    drawable[i]->setGeometry(geometry_);
    drawable[i]->setMaterial(material);
    drawable[i]->setParent(drawableBase_);
    drawable[i]->setPosition(pos);
  }

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(5.0f, 4.0f, 2.0f);
  AddLight(light);

  //Window
  std::shared_ptr<Drawable> drawableWindow = std::shared_ptr<Drawable>(new Drawable("Window"));
  std::shared_ptr<Material> TransparentMaterial = std::shared_ptr<Material>(new Material("../../../../img/window.png"));
  TransparentMaterial->setShaderFromPath("basics/2_Texture.vertx", "basics/2_Texture.frag");
  drawableWindow->setGeometry(geometry_);
  drawableWindow->setMaterial(TransparentMaterial);
  drawableWindow->setParent(getRoot());
  drawableWindow->setPositionX(-1.0f);
}

void ROTOM::DepthScene::input() {
  cameraMovement_.input();
}

void ROTOM::DepthScene::update() {
  drawableBase_->moveZ(sin(TIME::appTime()) * 0.2f);

  cameraMovement_.update();
}