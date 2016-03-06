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
  std::shared_ptr<Drawable> drawable = std::shared_ptr<Drawable>(new Drawable("drawable"));

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