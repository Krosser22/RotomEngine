/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/files.h"
#include "general/input.h"
#include "general/time.h"
#include "general/window.h"
#include "scenes/shaderScene.h"
#include "imgui.h"
#include "meshLoader.h"

void ROTOM::ShaderScene::init() {
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  geometry_ = std::shared_ptr<Geometry>(new Geometry());

  //Material1: Color
  std::shared_ptr<Material> material1 = std::shared_ptr<Material>(new Material());
  material1->setShaderFromPath("basics/1_Basic.vertx", "basics/1_Basic.frag");

  //Material2: Color + Texture
  std::shared_ptr<Material> material2 = std::shared_ptr<Material>(new Material());
  material2->setShaderFromPath("basics/2_Texture.vertx", "basics/2_Texture.frag");

  //Material3: Color + Texture + DiffuseLight
  std::shared_ptr<Material> material3 = std::shared_ptr<Material>(new Material());
  material3->setShaderFromPath("basics/3_DiffuseLight.vertx", "basics/3_DiffuseLight.frag");

  //Material4: Color + Texture + DiffuseLight + SpecularLight
  std::shared_ptr<Material> material4 = std::shared_ptr<Material>(new Material());
  material4->setShaderFromPath("basics/4_SpecularLight.vertx", "basics/4_SpecularLight.frag");

  //Material4: Color + Texture + DiffuseLight + SpecularLight
  std::shared_ptr<Material> material5 = std::shared_ptr<Material>(new Material());
  material5->setShaderFromPath("basics/5_SpecularLight_Blinn-Phong.vertx", "basics/5_SpecularLight_Blinn-Phong.frag");

  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable("Drawable_1"));
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable("Drawable_2"));
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable("Drawable_3"));
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable("Drawable_4"));
  std::shared_ptr<Drawable> drawable5 = std::shared_ptr<Drawable>(new Drawable("Drawable_5"));

  getRoot()->setPositionX(-2.0f);

  drawable1->setGeometry(geometry_);
  drawable1->setMaterial(material1);
  drawable1->setParent(getRoot());
  drawable1->setPositionZ(-5.0f);
  drawable1->materialSettings()->color_[0] = 0.0f;
  drawable1->materialSettings()->color_[1] = 0.0f;
  drawable1->materialSettings()->color_[2] = 0.0f;

  drawable2->setGeometry(geometry_);
  drawable2->setMaterial(material2);
  drawable2->setParent(drawable1);
  drawable2->setPositionX(1.0f);

  drawable3->setGeometry(geometry_);
  drawable3->setMaterial(material3);
  drawable3->setParent(drawable2);
  drawable3->setPositionX(1.0f);

  drawable4->setGeometry(geometry_);
  drawable4->setMaterial(material4);
  drawable4->setParent(drawable3);
  drawable4->setPositionX(1.0f);

  drawable5->setGeometry(geometry_);
  drawable5->setMaterial(material5);
  drawable5->setParent(drawable4);
  drawable5->setPositionX(1.0f);

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(1.0f, 1.0f, -2.0f);
  AddLight(light);
}

void ROTOM::ShaderScene::update() {
  //float sinTime = sin(TIME::appTime()) * 0.022f;
  Node *node = getRoot()->getChildAt(0)->getChildAt(0).get();
  node->setRotationX(node->rotation().x + 0.01f);

  //drawableLight_->setPosition(getLight().at(0)->lightPosition[0], getLight().at(0)->lightPosition[1], getLight().at(0)->lightPosition[2]);
}

void ROTOM::ShaderScene::draw() {
  RenderImGui();
}
