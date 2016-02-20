/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "scenes/defaultScene.h"
#include "imgui.h"
#include "text.h"
#include "time.h"
#include "window.h"

void ROTOM::DefaultScene::init() {
  //GetCamera()->setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  GetCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  GetCamera()->setPosition(0.0f, 0.0f, 0.0f);

  geometry = std::shared_ptr<Geometry>(new Geometry());
  material1 = std::shared_ptr<Material>(new Material("../../../../img/texture1.png"));
  material2 = std::shared_ptr<Material>(new Material("../../../../img/texture2.png"));
  material3 = std::shared_ptr<Material>(new Material("../../../../img/texture3.png"));
  material4 = std::shared_ptr<Material>(new Material());

  drawable1 = std::shared_ptr<Drawable>(new Drawable());
  drawable2 = std::shared_ptr<Drawable>(new Drawable());
  drawable3 = std::shared_ptr<Drawable>(new Drawable());

  drawable1->setGeometry(geometry);
  drawable1->setMaterial(material1);
  drawable1->setParent(GetRoot());
  drawable1->setPosition(0.0f, 0.0f, -5.0f);
  drawable2->setGeometry(geometry);
  drawable2->setMaterial(material2);
  drawable2->setParent(drawable1);
  drawable2->setPosition(0.0f, 0.0f, 0.0f);
  drawable3->setGeometry(geometry);
  drawable3->setMaterial(material3);
  drawable3->setParent(drawable2);
  drawable3->setPosition(0.0f, 0.0f, 0.0f);

  const float separation = -2.2f;
  const float pos_x_started = 15.0f;
  const float pos_y_started = 7.0f;
  const float pos_z_started = -5.0f;
  const int rows = 15;
  const int cols = 15;
  float pos[3] = { 0.0f, 0.0f, 0.0f };
  printf("Creating array of drawables\n");
  for (int i = 0; i < amount; ++i) {
    //printf("Creating Node: %d/%d\n", i, amount);
    pos[0] = ((i % cols) * separation) + pos_x_started;
    pos[1] = ((i / (cols * rows)) * separation) + pos_y_started;
    pos[2] = (((i / cols) % rows) * separation) + pos_z_started;
    drawable[i] = std::shared_ptr<Drawable>(new Drawable());
    drawable[i]->setGeometry(geometry);
    drawable[i]->setMaterial(material4);
    drawable[i]->setParent(drawable1);
    drawable[i]->setPosition(pos);
  }
}

void ROTOM::DefaultScene::update() {
  float sin_time = sin(TIME::appTime()) * 0.022f;
  GetRoot()->getChildAt(0)->moveX(sin_time);
  GetRoot()->getChildAt(0)->getChildAt(0)->moveY(sin_time);
  GetRoot()->getChildAt(0)->getChildAt(0)->getChildAt(0)->moveZ(sin_time);
}

void ROTOM::DefaultScene::draw() {
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("%d Cubes * 6 faces * 2 Triangles * 3 Points = %d Points", amount + 3, (amount + 3) * 6 * 2 * 3);
  
  ImGui::Begin("Input");
  {
    /*if (ImGui::Button("Detach")) {
      if (root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->parent() == root_.getChildAt(0)->getChildAt(0)) {
        root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->setParent(root_.getChildAt(0));
      } else {
        root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->setParent(root_.getChildAt(0)->getChildAt(0));
      }
    }*/

    ImGui::DragFloat3("LightPosition", &GetLight().at(0).get()->lightPositionX, 10.0f, -10000.0f, 10000.0f, "%.2f", 1.0f);
    ImGui::DragFloat3("LightColor", &GetLight().at(0).get()->lightColorX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularIntensity", &GetLight().at(0).get()->specularIntensityX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    //ImGui::DragFloat("Shininess", &(((Drawable *)(root_.getChildAt(0)->getChildAt(0)))->material()->shininess_), 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
    //ImGui::DragFloat4("specularMaterial", (((Drawable *)(root_.getChildAt(0)->getChildAt(0)))->material()->specularMaterial_), 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();
}
