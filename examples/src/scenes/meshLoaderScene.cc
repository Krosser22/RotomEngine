/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/files.h"
#include "general/scene.h"
#include "general/time.h"
#include "general/window.h"
#include "scenes/meshLoaderScene.h"
#include "meshLoader.h"
#include "imgui.h"

float cameraSpeed = 8.0f;
double mx = 0;
double my = 0;
double mx_last_frame = 0;
double my_last_frame = 0;

#define OBJ_MONKEY
//#define OBJ_BLONDE
//#define OBJ_DEADPOOL
//#define OBJ_IRONMAN
//#define OBJ_DRAGON
//#define OBJ_SIRIUS_5_COLONIAL_CITY

#ifdef OBJ_MONKEY
const char *base_path = "../../../../obj/";
const char *name = "Monkey";
#elif defined OBJ_BLONDE
const char *base_path = "../../../../obj/Blonde/";
const char *name = "Blonde";
#elif defined OBJ_DEADPOOL
const char *base_path = "../../../../obj/Deadpool/";
const char *name = "Deadpool";
#elif defined OBJ_IRONMAN
const char *base_path = "../../../../obj/Blonde/";
const char *name = "Blonde";
#elif defined OBJ_DRAGON
const char *base_path = "../../../../obj/";
const char *name = "dragon2";
#elif defined OBJ_SIRIUS_5_COLONIAL_CITY
const char *base_path = "../../../../obj/Sirus5ColonialCity/";
const char *name = "sirus_city";
#endif
static const float max_rot = 628.32f; //[0-628.32]

void ROTOM::MeshLoaderScene::init() {
  //GetCamera()->setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(0.0f, 0.0f, 0.0f);

  geometry = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Geometry::GeometryData> obj_data = std::shared_ptr<Geometry::GeometryData>(new Geometry::GeometryData);
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material("../../../../obj/Sirus5ColonialCity/Maps/1ab2.jpg"));
  std::shared_ptr<Drawable> drawable = std::shared_ptr<Drawable>(new Drawable());

  //MESHLOADER::Load_OBJ(finalPath, obj_data, false);
  MESHLOADER::Load_OBJ(base_path, name, obj_data);

  geometry->loadGeometry(&obj_data);

  getRoot()->setPosition(0.0f, 0.0f, -5.0f);

  drawable->setGeometry(geometry);
  drawable->setMaterial(material);
  drawable->setParent(getRoot());
}

void ROTOM::MeshLoaderScene::update() {
  float sin_time = sin(TIME::appTime()) * 2.22f;
  getRoot()->getChildAt(0)->setRotationY(sin_time);
}

void ROTOM::MeshLoaderScene::draw() {
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

    float *position = &getRoot()->getChildAt(0)->position()[0];
    if (ImGui::DragFloat3("Position", &position[0], 1.0f, -1000.0f, 1000.0f, "%.2f", 1.0f)) {
      getRoot()->getChildAt(0)->setPosition(position);
    }

    float *rotation = &getRoot()->getChildAt(0)->rotation()[0];
    if (ImGui::DragFloat3("Rotation", &rotation[0], 0.1f, 0.0f, 360.0f, "%.2f", 1.0f)) {
      getRoot()->getChildAt(0)->setRotation(rotation);
    }

    float *scale = &getRoot()->getChildAt(0)->scale()[0];
    if (ImGui::DragFloat3("Scale", &scale[0], 0.01f, 0.1f, 2.2f, "%.2f", 1.0f)) {
      getRoot()->getChildAt(0)->setScale(scale);
    }
  }
  ImGui::End();
}