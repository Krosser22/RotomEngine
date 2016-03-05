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
  getCamera()->setPosition(0.0f, 0.0f, 0.0f);

  geometry = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Geometry::GeometryData> obj_data = std::shared_ptr<Geometry::GeometryData>(new Geometry::GeometryData);
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  std::shared_ptr<Drawable> drawable[amount];
  
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

void ROTOM::GeometryScene::draw() {
  if (getLight().size() > 0) {
    /*ImGui::Begin("Light");
    {
      ImGui::DragFloat3("LightPosition", &getLight().at(0).lightPositionX, 10.0f, -10000.0f, 10000.0f, "%.2f", 1.0f);
      ImGui::DragFloat3("LightColor", &getLight().at(0).lightColorX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
      ImGui::DragFloat4("specularIntensity", &getLight().at(0).specularIntensityX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    }
    ImGui::End();*/
  }

  ImGui::Begin("Material");
  {
    ImGui::DragFloat("Shininess", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.shininess_, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularMaterial", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.specularMaterial_[0], 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();
}
