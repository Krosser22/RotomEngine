/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/files.h"
#include "general/time.h"
#include "general/window.h"
#include "scenes/movementScene.h"
#include "imgui.h"

void ROTOM::MovementScene::init() {
  //GetCamera()->setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(0.0f, 0.0f, 0.0f);

  geometry = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Material> material1 = std::shared_ptr<Material>(new Material("../../../../img/texture1.png"));
  std::shared_ptr<Material> material2 = std::shared_ptr<Material>(new Material("../../../../img/texture2.png"));
  std::shared_ptr<Material> material3 = std::shared_ptr<Material>(new Material("../../../../img/texture3.png"));
  std::shared_ptr<Material> material4 = std::shared_ptr<Material>(new Material());
  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable());
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable());
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable());
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable());

  drawable1->setGeometry(geometry);
  drawable1->setMaterial(material1);
  drawable1->setParent(getRoot());
  drawable1->setPositionZ(-5.0f);

  drawable2->setGeometry(geometry);
  drawable2->setMaterial(material2);
  drawable2->setParent(drawable1);
  drawable2->setPositionX(1.0f);

  drawable3->setGeometry(geometry);
  drawable3->setMaterial(material3);
  drawable3->setParent(drawable2);
  drawable3->setPositionX(1.0f);

  drawable4->setGeometry(geometry);
  drawable4->setMaterial(material4);
  drawable4->setParent(drawable3);
  drawable4->setPositionX(1.0f);
}

void ROTOM::MovementScene::input() {
  ImGuiIO& io = ImGui::GetIO();
  if (io.KeysDown['h']) printf("H");
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

void ROTOM::MovementScene::update() {
  /*float sin_time = sin(TIME::appTime()) * 0.022f;
  getRoot()->getChildAt(0)->moveX(sin_time);
  getRoot()->getChildAt(0)->getChildAt(0)->moveY(sin_time);
  getRoot()->getChildAt(0)->getChildAt(0)->getChildAt(0)->moveZ(sin_time);*/

  //updateCamera();
}

void ROTOM::MovementScene::draw() {
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("%d Objects = %d Vertex", 4, geometry->vertexCount() * 4);
  
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
    ImGui::DragFloat("Shininess", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.shininess_, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularMaterial", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.specularMaterial_[0], 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();
}

void ROTOM::MovementScene::moveCamera(char key) {
  //printf("%c\n", key);
  /*const float *temp_forward = getCamera()->forward();
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
  }*/
}

void ROTOM::MovementScene::rotateCamera() {
  /*getCamera()->rotation()[0] += (float)((mx_last_frame - mx) * 0.4);
  getCamera()->rotation()[1] -= (float)((my_last_frame - my));

  //min and max X rotation
  if (getCamera()->rotation()[0] < -max_rot) getCamera()->rotation()[0] += max_rot;
  if (getCamera()->rotation()[0] > max_rot) getCamera()->rotation()[0] -= max_rot;

  //min and max Y rotation
  if (getCamera()->rotation()[1] < 0) getCamera()->rotation()[1] = 0;
  if (getCamera()->rotation()[1] > max_rot) getCamera()->rotation()[1] = 650;*/
}

void ROTOM::MovementScene::updateCamera() {
  /*mx_last_frame = mx;
  my_last_frame = my;
  //mx = ESAT::MousePositionX();
  //my = ESAT::MousePositionY();

  float *a = (float *)GameState.camera->view_matrix();
  printf("%f %f %f %f\n", a[0], a[4], a[8], a[12]);
  printf("%f %f %f %f\n", a[1], a[5], a[9], a[13]);
  printf("%f %f %f %f\n", a[2], a[6], a[10], a[14]);
  printf("%f %f %f %f\n\n", a[3], a[7], a[11], a[15]);
  float view[3];
  float p = sin(-getCamera()->position()[1] / 200) * 220;
  view[0] = -p*cos(getCamera()->rotation()[0] / 100);
  view[1] = -cos(-getCamera()->rotation()[1] / 200) * 220;
  view[2] = -p*sin(getCamera()->rotation()[0] / 100);

  //getCamera()->setPosition(camera_pos);
  getCamera()->setViewTarget(view);*/
}
