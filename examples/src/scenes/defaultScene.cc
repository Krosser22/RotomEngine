/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/files.h"
#include "general/input.h"
#include "general/time.h"
#include "general/window.h"
#include "scenes/defaultScene.h"
#include "imgui.h"

void ROTOM::DefaultScene::init() {
  //GetCamera()->setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(0.0f, 0.0f, 0.0f);

  geometry_ = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Material> material1 = std::shared_ptr<Material>(new Material("../../../../img/texture1.png"));
  std::shared_ptr<Material> material2 = std::shared_ptr<Material>(new Material("../../../../img/texture2.png"));
  std::shared_ptr<Material> material3 = std::shared_ptr<Material>(new Material("../../../../img/texture3.png"));
  std::shared_ptr<Material> material4 = std::shared_ptr<Material>(new Material());
  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable());
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable());
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable());
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
    drawable[i] = std::shared_ptr<Drawable>(new Drawable());
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
    std::shared_ptr<Drawable> drawableNew = std::shared_ptr<Drawable>(new Drawable());
    drawableNew->setGeometry(geometry_);
    drawableNew->setMaterial(material);
    drawableNew->setParent(getRoot()->getChildAt(0));
    drawableNew->setPositionX(posX);
    posX -= 1.0f;
  }
}

void ROTOM::DefaultScene::update() {
  float sin_time = sin(TIME::appTime()) * 0.022f;
  getRoot()->getChildAt(0)->moveX(sin_time);
  getRoot()->getChildAt(0)->getChildAt(0)->moveY(sin_time);
  getRoot()->getChildAt(0)->getChildAt(0)->getChildAt(0)->moveZ(sin_time);
}

void ROTOM::DefaultScene::draw() {
  ImGui::Begin("Input");
  {
    /*if (ImGui::Button("Detach")) {
      if (root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->parent() == root_.getChildAt(0)->getChildAt(0)) {
        root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->setParent(root_.getChildAt(0));
      } else {
        root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->setParent(root_.getChildAt(0)->getChildAt(0));
      }
    }*/
  }
  ImGui::End();

  if (getLight().size() > 0) {
    ImGui::Begin("Light");
    {
      ImGui::DragFloat3("LightPosition", &getLight().at(0).lightPositionX, 10.0f, -10000.0f, 10000.0f, "%.2f", 1.0f);
      ImGui::DragFloat3("LightColor", &getLight().at(0).lightColorX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
      ImGui::DragFloat4("specularIntensity", &getLight().at(0).specularIntensityX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    }
    ImGui::End();
  }

  ImGui::Begin("Material");
  {
    ImGui::DragFloat("Shininess", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.shininess_, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularMaterial", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.specularMaterial_[0], 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();
}
