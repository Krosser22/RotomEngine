/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/files.h"
#include "general/input.h"
#include "general/time.h"
#include "general/window.h"
#include "scenes/movementScene.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void ROTOM::MovementScene::init() {
  //GetCamera()->setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(0.0f, 0.0f, 0.0f);

  geometry_ = std::shared_ptr<Geometry>(new Geometry());
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material("../../../../img/texture.png"));
  material->setShaderFromPath("basics/4_SpecularLight.vertx", "basics/4_SpecularLight.frag");

  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable("1"));
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable("2"));
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable("3"));
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable("4"));

  drawable1->setGeometry(geometry_);
  drawable1->setMaterial(material);
  drawable1->setParent(getRoot());
  //drawable1->setPositionZ(-5.0f);

  drawable2->setGeometry(geometry_);
  drawable2->setMaterial(material);
  drawable2->setParent(drawable1);
  drawable2->setPositionX(1.0f);

  drawable3->setGeometry(geometry_);
  drawable3->setMaterial(material);
  drawable3->setParent(drawable2);
  drawable3->setPositionX(1.0f);

  drawable4->setGeometry(geometry_);
  drawable4->setMaterial(material);
  drawable4->setParent(drawable3);
  drawable4->setPositionX(1.0f);

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(1.00f, 0.0f, 3.50f);
  light->materialSettings()->color_[0] = 0.8f;
  light->materialSettings()->color_[1] = 0.6f;
  light->materialSettings()->color_[2] = 0.4f;
  light->specularIntensity[0] = 1.0f;
  light->specularIntensity[1] = 1.0f;
  light->specularIntensity[2] = 1.0f;
  AddLight(light);
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
  /*float sin_time = sin(TIME::appTime()) * 0.022f;
  getRoot()->getChildAt(0)->moveX(sin_time);
  getRoot()->getChildAt(0)->getChildAt(0)->moveY(sin_time);
  getRoot()->getChildAt(0)->getChildAt(0)->getChildAt(0)->moveZ(sin_time);*/

  Node *node = getRoot()->getChildAt(0)->getChildAt(0).get();
  node->setRotationX(node->rotation().x + 0.01f);

  // Camera/View transformation
  glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  getCamera()->setViewMatrix(glm::value_ptr(view));
}

void ROTOM::MovementScene::draw() {
  /*if (getLight().size() > 0) {
    ImGui::Begin("Light");
    {
      ImGui::DragFloat3("LightPosition", &getLight().at(0).lightPositionX, 10.0f, -10000.0f, 10000.0f, "%.2f", 1.0f);
      ImGui::DragFloat3("LightColor", &getLight().at(0).lightColorX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
      ImGui::DragFloat4("specularIntensity", &getLight().at(0).specularIntensityX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    }
    ImGui::End();
  }

  ImGui::Begin("Material");
  {
    float *shininess = &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.shininess_;
    if (ImGui::DragFloat("Shininess", shininess, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f)) {
      ((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.shininess_ = *shininess;
    }

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
  ImGui::End();*/
}
