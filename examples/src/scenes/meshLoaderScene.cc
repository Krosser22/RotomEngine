/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/files.h"
#include "general/input.h"
#include "general/scene.h"
#include "general/time.h"
#include "general/window.h"
#include "scenes/meshLoaderScene.h"
#include "meshLoader.h"
#include "imgui.h"

#define OBJ_MONKEY
//#define OBJ_BLONDE
//#define OBJ_DEADPOOL
//#define OBJ_IRONMAN
//#define OBJ_DRAGON
//#define OBJ_SIRIUS_5_COLONIAL_CITY

#ifdef OBJ_MONKEY
const char *basePath = "../../../../obj/";
const char *name = "Monkey";
const char *finalPath = "../../../../obj/Monkey";
#elif defined OBJ_BLONDE
const char *basePath = "../../../../obj/Blonde/";
const char *name = "Blonde";
const char *finalPath = "../../../../obj/Blonde/Blonde";
#elif defined OBJ_DEADPOOL
const char *basePath = "../../../../obj/Deadpool/";
const char *name = "Deadpool";
const char *finalPath = "../../../../obj/Deadpool/Deadpool";
#elif defined OBJ_IRONMAN
const char *basePath = "../../../../obj/Blonde/";
const char *name = "Blonde";
const char *finalPath = "../../../../obj/Blonde/Blonde";
#elif defined OBJ_DRAGON
const char *basePath = "../../../../obj/";
const char *name = "dragon2";
const char *finalPath = "../../../../obj/dragon2";
#elif defined OBJ_SIRIUS_5_COLONIAL_CITY
const char *basePath = "../../../../obj/Sirus5ColonialCity/";
const char *name = "sirus_city";
const char *finalPath = "../../../../obj/Sirus5ColonialCity/sirus_city";
#endif

void ROTOM::MeshLoaderScene::init() {
  //Camera
  //GetCamera()->setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  //Geometry
  std::shared_ptr<Geometry> geometry = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Geometry::GeometryData> obj_data = std::shared_ptr<Geometry::GeometryData>(new Geometry::GeometryData);
  //MESHLOADER::Load_OBJ(finalPath, obj_data, false);
  MESHLOADER::Load_OBJ(basePath, name, obj_data);
  geometry->loadGeometry(&obj_data);

  //Material
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material("../../../../obj/Sirus5ColonialCity/Maps/1ab2.jpg"));
  {
    std::shared_ptr<std::string> verterShaderSource = std::shared_ptr<std::string>(new std::string());
    std::shared_ptr<std::string> fragmentShaderSource = std::shared_ptr<std::string>(new std::string());
    FILES::ReadFile("../../../../shaders/shader3_DiffuseLight.vertx", verterShaderSource);
    FILES::ReadFile("../../../../shaders/shader3_DiffuseLight.frag", fragmentShaderSource);
    //FILES::ReadFile("../../../../shaders/shader4_SpecularLight.vertx", verterShaderSource);
    //FILES::ReadFile("../../../../shaders/shader4_SpecularLight.frag", fragmentShaderSource);
    material->setShader(verterShaderSource.get()->data(), fragmentShaderSource.get()->data());
  }

  //Drawable
  std::shared_ptr<Drawable> drawable = std::shared_ptr<Drawable>(new Drawable("drawable"));
  getRoot()->setPosition(0.0f, 0.0f, -5.0f);
  drawable->setGeometry(geometry);
  drawable->setMaterial(material);
  drawable->setParent(getRoot());

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setGeometry(std::shared_ptr<Geometry>(new Geometry()));
  light->setMaterial(material);
  light->setParent(getRoot());
  light->setScale(0.1f, 0.1f, 0.1f);
  AddLight(light);
}

void ROTOM::MeshLoaderScene::input() {
  if (INPUT::IsKeyPressed('Q')) {
    rotating_ = !rotating_;
  }
}

void ROTOM::MeshLoaderScene::update() {
  if (rotating_) {
    getRoot()->getChildAt(0)->setRotationY(getRoot()->getChildAt(0)->rotation().y + 0.01f);
  }
}