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
  /*{
    std::shared_ptr<std::string> verterShaderSource4 = std::shared_ptr<std::string>(new std::string());
    std::shared_ptr<std::string> fragmentShaderSource4 = std::shared_ptr<std::string>(new std::string());
    FILES::ReadFile("../../../../shaders/shader3_SpecularLight.vertx", verterShaderSource4);
    FILES::ReadFile("../../../../shaders/shader3_SpecularLight.frag", fragmentShaderSource4);
    material4->setShader(verterShaderSource4.get()->data(), fragmentShaderSource4.get()->data());
  }*/

  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable());
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable());
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable());
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable());

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
}

void ROTOM::ShaderScene::update() {
  float sinTime = sin(TIME::appTime()) * 0.022f;
  getRoot()->getChildAt(0)->getChildAt(0)->setRotation(0.0f, getRoot()->getChildAt(0)->getChildAt(0)->rotation().y + 0.01f, 0.0f);
  getRoot()->getChildAt(0)->moveX(sinTime);
  getRoot()->getChildAt(0)->getChildAt(0)->moveY(sinTime);
  getRoot()->getChildAt(0)->getChildAt(0)->getChildAt(0)->moveZ(sinTime);

}

void ROTOM::ShaderScene::draw() {
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("%d Objects = %d Vertex", 4, geometry_->vertexCount() * 4);
  
  ImGui::Begin("Light");
  {
    ImGui::DragFloat3("LightPosition", &getLight().at(0).get()->lightPositionX, 10.0f, -10000.0f, 10000.0f, "%.2f", 1.0f);
    ImGui::DragFloat3("LightColor", &getLight().at(0).get()->lightColorX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularIntensity", &getLight().at(0).get()->specularIntensityX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();

  ImGui::Begin("Material");
  {
    ImGui::DragFloat("Shininess", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.shininess_, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularMaterial", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.specularMaterial_[0], 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();
}
