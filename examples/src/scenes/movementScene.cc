/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/files.h"
#include "general/input.h"
#include "general/time.h"
#include "general/window.h"
#include "scenes/movementScene.h"
#include "imgui.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void ROTOM::MovementScene::init() {
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
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable());

  drawable1->setGeometry(geometry_);
  drawable1->setMaterial(material1);
  drawable1->setParent(getRoot());
  drawable1->setPositionZ(-5.0f);

  drawable2->setGeometry(geometry_);
  drawable2->setMaterial(material2);
  drawable2->setParent(drawable1);
  drawable2->setPositionX(1.0f);

  drawable3->setGeometry(geometry_);
  drawable3->setMaterial(material3);
  drawable3->setParent(drawable2);
  drawable3->setPositionX(1.0f);

  drawable4->setGeometry(geometry_);
  drawable4->setMaterial(material4);
  drawable4->setParent(drawable3);
  drawable4->setPositionX(1.0f);
}

void ROTOM::MovementScene::input() {
  if (INPUT::IsMousePressed(1)) {
    lastX = INPUT::MousePositionX();
    lastY = INPUT::MousePositionY();
  }

  if (INPUT::MouseWheel()) {
    scroll();
  }

  if (INPUT::IsMouseDown(1)) {
    movement();
    rotation();
  }
}

void ROTOM::MovementScene::movement() {
  //Forward
  if (INPUT::IsKeyDown('W')) {
    cameraPos += movementSpeed * cameraFront;
  }

  //Backward
  if (INPUT::IsKeyDown('S')) {
    cameraPos -= movementSpeed * cameraFront;
  }

  //Left
  if (INPUT::IsKeyDown('A')) {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed;
  }

  //Right
  if (INPUT::IsKeyDown('D')) {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed;
  }

  //Up
  if (INPUT::IsKeyDown('E')) {
    cameraPos += glm::normalize(cameraUp) * movementSpeed;
  }

  //Down
  if (INPUT::IsKeyDown('Q')) {
    cameraPos -= glm::normalize(cameraUp) * movementSpeed;
  }
}

void ROTOM::MovementScene::rotation() {
  float xoffset = INPUT::MousePositionX() - lastX;
  float yoffset = lastY - INPUT::MousePositionY(); // Reversed since y-coordinates go from bottom to left
  lastX = INPUT::MousePositionX();
  lastY = INPUT::MousePositionY();

  xoffset *= rotationSpeed;
  yoffset *= rotationSpeed;

  yaw += xoffset;
  pitch += yoffset;

  // Make sure that when pitch is out of bounds, screen doesn't get flipped
  if (pitch > 89.0f) {
    pitch = 89.0f;
  }

  if (pitch < -89.0f) {
    pitch = -89.0f;
  }

  glm::vec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(front);
}

void ROTOM::MovementScene::scroll() {
  if (fov >= 1.0f && fov <= 45.0f) {
    fov -= INPUT::MouseWheel() * scrollSpeed;
  }

  if (fov <= 1.0f) {
    fov = 1.0f;
  }

  if (fov >= 45.0f) {
    fov = 45.0f;
  }
  printf("FOV: %f\n", fov);
}

void ROTOM::MovementScene::update() {
  float sin_time = sin(TIME::appTime()) * 0.022f;
  getRoot()->getChildAt(0)->moveX(sin_time);
  getRoot()->getChildAt(0)->getChildAt(0)->moveY(sin_time);
  getRoot()->getChildAt(0)->getChildAt(0)->getChildAt(0)->moveZ(sin_time);

  // Camera/View transformation
  glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  getCamera()->setViewMatrix(glm::value_ptr(view));
  // Projection 
  glm::mat4 projection = glm::perspective(fov, (float)1280 / (float)720, 0.1f, 100.0f);
  getCamera()->setProjectionMatrix(glm::value_ptr(projection));
}

void ROTOM::MovementScene::draw() {
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("%d Objects = %d Vertex", 4, geometry_->vertexCount() * 4);
  
  ImGui::Begin("Light");
  {
    ImGui::DragFloat3("LightPosition", &getLight().at(0).get()->lightPositionX, 10.0f, -10000.0f, 10000.0f, "%.2f", 1.0f);
    ImGui::DragFloat3("LightColor", &getLight().at(0).get()->lightColorX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularIntensity", &getLight().at(0).get()->specularIntensityX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();

  ImGui::Begin("Material");
  {
    ImGui::DragFloat("Shininess", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.shininess_, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularMaterial", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.specularMaterial_[0], 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();
}
