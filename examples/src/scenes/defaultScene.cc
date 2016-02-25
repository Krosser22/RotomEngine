/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/files.h"
#include "general/time.h"
#include "general/window.h"
#include "scenes/defaultScene.h"
#include "imgui.h"

void ROTOM::DefaultScene::init() {
  //GetCamera()->setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(0.0f, 0.0f, 0.0f);

  geometry = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Material> material1 = std::shared_ptr<Material>(new Material("../../../../img/texture1.png"));
  std::shared_ptr<Material> material2 = std::shared_ptr<Material>(new Material("../../../../img/texture2.png"));
  std::shared_ptr<Material> material3 = std::shared_ptr<Material>(new Material("../../../../img/texture3.png"));
  std::shared_ptr<Material> material4 = std::shared_ptr<Material>(new Material());
  std::shared_ptr<Node> node1 = std::shared_ptr<Node>(new Node());
  std::shared_ptr<Node> node2 = std::shared_ptr<Node>(new Node());
  std::shared_ptr<Node> node3 = std::shared_ptr<Node>(new Node());
  std::shared_ptr<Node> node[amount];

  node1->setGeometry(geometry);
  node1->setMaterial(material1);
  node1->setParent(getRoot()->ID());
  node1->setPositionZ(-5.0f);
  node2->setGeometry(geometry);
  node2->setMaterial(material2);
  node2->setParent(node1->ID());
  node3->setGeometry(geometry);
  node3->setMaterial(material3);
  node3->setParent(node2->ID());

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
    node[i] = std::shared_ptr<Node>(new Node());
    node[i]->setGeometry(geometry);
    node[i]->setMaterial(material4);
    node[i]->setParent(node1->ID());
    node[i]->setPosition(pos);
  }
}

void ROTOM::DefaultScene::update() {
  float sin_time = sin(TIME::appTime()) * 0.022f;
  //getRoot()->getChildAt(0)->moveX(sin_time);
  //getRoot()->getChildAt(0)->getChildAt(0)->moveY(sin_time);
  //getRoot()->getChildAt(0)->getChildAt(0)->getChildAt(0)->moveZ(sin_time);
}

void ROTOM::DefaultScene::draw() {
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("%d Objects = %d Vertex", amount + 3, geometry->vertexCount() * (amount + 3));
  
  ImGui::Begin("Input");
  {
    /*if (ImGui::Button("Detach")) {
      if (root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->parent() == root_.getChildAt(0)->getChildAt(0)) {
        root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->setParent(root_.getChildAt(0));
      } else {
        root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->setParent(root_.getChildAt(0)->getChildAt(0));
      }
    }*/

    ImGui::DragFloat3("LightPosition", &getLight().at(0).get()->lightPositionX, 10.0f, -10000.0f, 10000.0f, "%.2f", 1.0f);
    ImGui::DragFloat3("LightColor", &getLight().at(0).get()->lightColorX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularIntensity", &getLight().at(0).get()->specularIntensityX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    //ImGui::DragFloat("Shininess", &(((Drawable *)(root_.getChildAt(0)->getChildAt(0)))->material()->shininess_), 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
    //ImGui::DragFloat4("specularMaterial", (((Drawable *)(root_.getChildAt(0)->getChildAt(0)))->material()->specularMaterial_), 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();
}
