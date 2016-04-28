/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "proceduralScene.h"
#include "general/input.h"
#include "general/window.h"
#include <glm/gtc/matrix_transform.hpp>

void ROTOM::ProceduralScene::init() {
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  //Material1: Color
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  material->setShaderFromPath("basics/5_SpecularLight_Blinn-Phong.vertx", "basics/5_SpecularLight_Blinn-Phong.frag");

  //Root
  getRoot()->setPosition(-5.0f, -10.0f, -28.0f);

  //Chunk
  chunk_ = std::shared_ptr<Chunk>(new Chunk("Chunk"));
  chunk_->init(getRoot(), 25, 1, 1);

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(1.0f, 1.0f, -2.0f);
  AddLight(light);
}

void ROTOM::ProceduralScene::input() {
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

void ROTOM::ProceduralScene::movement() {
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

void ROTOM::ProceduralScene::rotation() {
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

  glm::fvec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(front);
}

void ROTOM::ProceduralScene::scroll() {
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

void ROTOM::ProceduralScene::update() {
  chunk_->update();

  // Camera/View transformation
  getCamera()->setViewMatrix(glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp));
}

void ROTOM::ProceduralScene::draw() {

}