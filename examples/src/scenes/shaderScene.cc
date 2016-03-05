/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/files.h"
#include "general/input.h"
#include "general/time.h"
#include "general/window.h"
#include "scenes/shaderScene.h"
#include "imgui.h"

void ROTOM::ShaderScene::init() {
  //GetCamera()->setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(0.0f, 0.0f, 0.0f);

  geometry_ = std::shared_ptr<Geometry>(new Geometry());

  //Material1: Color
  std::shared_ptr<Material> material1 = std::shared_ptr<Material>(new Material());
  {
    std::shared_ptr<std::string> verterShaderSource1 = std::shared_ptr<std::string>(new std::string());
    std::shared_ptr<std::string> fragmentShaderSource1 = std::shared_ptr<std::string>(new std::string());
    FILES::ReadFile("../../../../shaders/shader1_Basic.vertx", verterShaderSource1);
    FILES::ReadFile("../../../../shaders/shader1_Basic.frag", fragmentShaderSource1);
    material1->setShader(verterShaderSource1.get()->data(), fragmentShaderSource1.get()->data());
  }

  //Material2: Color + Texture
  std::shared_ptr<Material> material2 = std::shared_ptr<Material>(new Material("../../../../img/texture1.png"));
  {
    std::shared_ptr<std::string> verterShaderSource2 = std::shared_ptr<std::string>(new std::string());
    std::shared_ptr<std::string> fragmentShaderSource2 = std::shared_ptr<std::string>(new std::string());
    FILES::ReadFile("../../../../shaders/shader2_Texture.vertx", verterShaderSource2);
    FILES::ReadFile("../../../../shaders/shader2_Texture.frag", fragmentShaderSource2);
    material2->setShader(verterShaderSource2.get()->data(), fragmentShaderSource2.get()->data());
  }

  //Material3: Color + Texture + DiffuseLight
  std::shared_ptr<Material> material3 = std::shared_ptr<Material>(new Material("../../../../img/texture2.png"));
  {
    std::shared_ptr<std::string> verterShaderSource3 = std::shared_ptr<std::string>(new std::string());
    std::shared_ptr<std::string> fragmentShaderSource3 = std::shared_ptr<std::string>(new std::string());
    FILES::ReadFile("../../../../shaders/shader3_DiffuseLight.vertx", verterShaderSource3);
    FILES::ReadFile("../../../../shaders/shader3_DiffuseLight.frag", fragmentShaderSource3);
    material3->setShader(verterShaderSource3.get()->data(), fragmentShaderSource3.get()->data());
  }

  //Material4: Color + Texture + DiffuseLight + SpecularLight
  std::shared_ptr<Material> material4 = std::shared_ptr<Material>(new Material("../../../../img/texture3.png"));
  {
    std::shared_ptr<std::string> verterShaderSource4 = std::shared_ptr<std::string>(new std::string());
    std::shared_ptr<std::string> fragmentShaderSource4 = std::shared_ptr<std::string>(new std::string());
    FILES::ReadFile("../../../../shaders/shader4_SpecularLight.vertx", verterShaderSource4);
    FILES::ReadFile("../../../../shaders/shader4_SpecularLight.frag", fragmentShaderSource4);
    material4->setShader(verterShaderSource4.get()->data(), fragmentShaderSource4.get()->data());
  }

  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable("1"));
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable("2"));
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable("3"));
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable("4"));

  drawable1->setGeometry(geometry_);
  drawable1->setMaterial(material1);
  drawable1->setParent(getRoot());
  drawable1->setPositionZ(-5.0f);

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

  drawableLight_ = std::shared_ptr<Drawable>(new Drawable("light"));
  drawableLight_->setGeometry(geometry_);
  drawableLight_->setMaterial(material1);
  drawableLight_->setParent(getRoot());

  std::shared_ptr<Light> light1 = std::shared_ptr<Light>(new Light());
  AddLight(light1);

  std::shared_ptr<Light> light2 = std::shared_ptr<Light>(new Light());
  AddLight(light2);
}

void ROTOM::ShaderScene::update() {
  //float sinTime = sin(TIME::appTime()) * 0.022f;
  Node *node = getRoot()->getChildAt(0)->getChildAt(0).get();
  node->setRotationX(node->rotation().x + 0.01f);

  drawableLight_->setPosition(getLight().at(0)->lightPosition[0], getLight().at(0)->lightPosition[1], getLight().at(0)->lightPosition[2]);
}

void ROTOM::ShaderScene::draw() {

}
