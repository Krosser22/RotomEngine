/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/files.h"
#include "general/time.h"
#include "general/window.h"
#include "scenes/geometryScene.h"
#include "meshLoader.h"
#include "imgui.h"

void ROTOM::GeometryScene::init() {
  //GetCamera()->setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  //getCamera()->setPosition(0.0f, 0.0f, 0.0f);

  geometry = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Geometry::GeometryData> obj_data = std::shared_ptr<Geometry::GeometryData>(new Geometry::GeometryData);
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  unsigned int node[amount];
  
  const char *base_path = "../../../../obj/";
  const char *name = "Monkey";
  ROTOM::MESHLOADER::Load_OBJ(base_path, name, obj_data);
  geometry->loadGeometry(&obj_data);

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
    node[i] = Node::getNewNode();
    Node::setGeometry(node[i], geometry);
    Node::setMaterial(node[i], material);
    Node::setParent(node[i], getRoot());
    Node::setPosition(node[i], pos);
  }
}

void ROTOM::GeometryScene::update() {
  float sin_time = sin(TIME::appTime()) * 0.022f;
  Node::move(getRoot(), sin_time, sin_time, sin_time);
}

void ROTOM::GeometryScene::draw() {
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("%d Objects = %d Vertex", amount, geometry->vertexCount() * amount);
  
  ImGui::Begin("Input");
  {
    ImGui::DragFloat3("LightPosition", &getLight().at(0).get()->lightPositionX, 10.0f, -10000.0f, 10000.0f, "%.2f", 1.0f);
    ImGui::DragFloat3("LightColor", &getLight().at(0).get()->lightColorX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();
}
