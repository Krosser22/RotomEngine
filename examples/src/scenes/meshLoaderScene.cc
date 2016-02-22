/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "scenes/meshLoaderScene.h"
#include "imgui.h"
#include "drawable.h"
#include "files.h"
#include "window.h"
#include "scene.h"
#include "meshLoader.h"
#include "time.h"

float cameraSpeed = 8.0f;
double mx = 0;
double my = 0;
double mx_last_frame = 0;
double my_last_frame = 0;

float position[3];
float rotation[3];
float scale[3];

#define OBJ_MONKEY
//#define OBJ_BLONDE
//#define OBJ_IRONMAN
//#define OBJ_DRAGON
//#define OBJ_SIRIUS_5_COLONIAL_CITY

#ifdef OBJ_MONKEY
const char *base_path = "../../../../obj/";
const char *name = "Monkey";
#elif defined OBJ_BLONDE
const char *base_path = "../../../../obj/Blonde/";
const char *name = "Blonde";
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
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material("../../../../obj/Sirus5ColonialCity/Maps/1ab2.jpg"));
  std::shared_ptr<Drawable> drawable = std::shared_ptr<Drawable>(new Drawable());
  std::shared_ptr<ROTOM::Geometry::GeometryData> obj_data;

  drawable->setGeometry(geometry);
  drawable->setMaterial(material);
  drawable->setParent(getRoot());
  drawable->setPosition(0.0f, 0.0f, -5.0f);

  obj_data = std::shared_ptr<ROTOM::Geometry::GeometryData>(new ROTOM::Geometry::GeometryData);

  //ROTOM::MESHLOADER::Load_OBJ(finalPath, obj_data, false);
  ROTOM::MESHLOADER::Load_OBJ(base_path, name, obj_data);

  geometry->loadGeometry(&obj_data);

  getRoot()->setPosition(0.0f, 0.0f, -5.0f);

  position[0] = 0.0f;
  position[1] = 0.0f;
  position[2] = 0.0f;
  rotation[0] = 0.0f;
  rotation[1] = 0.0f;
  rotation[2] = 0.0f;
  scale[0] = 1.0f;
  scale[1] = 1.0f;
  scale[2] = 1.0f;
  getRoot()->getChildAt(0)->setPosition(position);
  getRoot()->getChildAt(0)->setRotation(rotation);
  getRoot()->getChildAt(0)->setScale(scale);
}

void ROTOM::MeshLoaderScene::input() {
  /*if (ESAT::MouseButtonPressed(1)) {
  rotate_player();
  } else {
  //Player
  if (ESAT::IsKeyPressed('W')) {
  move_player('W');
  updateCamera();
  }

  if (ESAT::IsKeyPressed('A')) {
  move_player('A');
  updateCamera();
  }

  if (ESAT::IsKeyPressed('S')) {
  move_player('S');
  updateCamera();
  }

  if (ESAT::IsKeyPressed('D')) {
  move_player('D');
  updateCamera();
  }
  }*/
}

void ROTOM::MeshLoaderScene::update() {
  float sin_time = sin(TIME::appTime()) * 20.22f;
  //getRoot()->getChildAt(0)->setRotation(sin_time, sin_time, sin_time);
  //updateCamera();
}

void ROTOM::MeshLoaderScene::draw() {
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("1 Object = %d Points", geometry->vertexCount());

  ImGui::Begin("Input");
  {
    ImGui::DragFloat3("LightPosition", &getLight().at(0).get()->lightPositionX, 10.0f, -10000.0f, 10000.0f, "%.2f", 1.0f);
    ImGui::DragFloat3("LightColor", &getLight().at(0).get()->lightColorX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularIntensity", &getLight().at(0).get()->specularIntensityX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    ImGui::DragFloat("Shininess", &(((Drawable *)(&getRoot()->getChildAt(0))->get())->material()->materialData_.shininess_), 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularMaterial", (((Drawable *)(&getRoot()->getChildAt(0))->get())->material()->materialData_.specularMaterial_), 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    if (ImGui::DragFloat3("Position", &position[0], 1.0f, -1000.0f, 1000.0f, "%.2f", 1.0f)) {
      getRoot()->getChildAt(0)->setPosition(position);
    }
    if (ImGui::DragFloat3("Rotation", &rotation[0], 0.1f, 0.0f, 360.0f, "%.2f", 1.0f)) {
      getRoot()->getChildAt(0)->setRotation(rotation);
    }
    if (ImGui::DragFloat3("Scale", &scale[0], 0.01f, 0.1f, 2.2f, "%.2f", 1.0f)) {
      getRoot()->getChildAt(0)->setScale(scale);
    }
  }
  ImGui::End();
}

void ROTOM::MeshLoaderScene::moveCamera(char key) {
  //printf("%c\n", key);
  const float *temp_forward = getCamera()->forward();
  float forward[3] = { temp_forward[0], temp_forward[1], temp_forward[2] };
  float length = sqrt((forward[0] * forward[0]) + (forward[1] * forward[1]) + (forward[2] * forward[2]));
  for (unsigned int i = 0; i < 3; ++i) {
    forward[i] /= length;
  }

  float *cameraPos = &getCamera()->position()[0];
  switch (key) {
    case 'W':
      cameraPos[0] += (forward[0] * cameraSpeed);
      //camera_pos[1] += (forward[1] * cameraSpeed);
      cameraPos[2] += (forward[2] * cameraSpeed);
      break;
    case 'A':
      cameraPos[0] += (forward[2] * cameraSpeed);
      cameraPos[2] -= (forward[0] * cameraSpeed);
      break;
    case 'S':
      cameraPos[0] -= (forward[0] * cameraSpeed);
      //cameraPos[1] -= (forward[1] * cameraSpeed);
      cameraPos[2] -= (forward[2] * cameraSpeed);
      break;
    case 'D':
      cameraPos[0] -= (forward[2] * cameraSpeed);
      cameraPos[2] += (forward[0] * cameraSpeed);
      break;
  }
}

void ROTOM::MeshLoaderScene::rotateCamera() {
  getCamera()->rotation()[0] += (float)((mx_last_frame - mx) * 0.4);
  getCamera()->rotation()[1] -= (float)((my_last_frame - my));

  //min and max X rotation
  if (getCamera()->rotation()[0] < -max_rot) getCamera()->rotation()[0] += max_rot;
  if (getCamera()->rotation()[0] > max_rot) getCamera()->rotation()[0] -= max_rot;

  //min and max Y rotation
  if (getCamera()->rotation()[1] < 0) getCamera()->rotation()[1] = 0;
  if (getCamera()->rotation()[1] > max_rot) getCamera()->rotation()[1] = 650;
}

void ROTOM::MeshLoaderScene::updateCamera() {
  mx_last_frame = mx;
  my_last_frame = my;
  //mx = ESAT::MousePositionX();
  //my = ESAT::MousePositionY();

  /*float *a = (float *)GameState.camera->view_matrix();
  printf("%f %f %f %f\n", a[0], a[4], a[8], a[12]);
  printf("%f %f %f %f\n", a[1], a[5], a[9], a[13]);
  printf("%f %f %f %f\n", a[2], a[6], a[10], a[14]);
  printf("%f %f %f %f\n\n", a[3], a[7], a[11], a[15]);*/
  float view[3];
  float p = sin(-getCamera()->position()[1] / 200) * 220;
  view[0] = -p*cos(getCamera()->rotation()[0] / 100);
  view[1] = -cos(-getCamera()->rotation()[1] / 200) * 220;
  view[2] = -p*sin(getCamera()->rotation()[0] / 100);

  //getCamera()->setPosition(camera_pos);
  getCamera()->setViewTarget(view);
}
