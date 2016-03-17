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
#include "meshLoader.h"
#include "scenes/depthScene.h"
#include "imgui.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void ROTOM::DepthScene::init() {
  //GetCamera()->setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  getCamera()->setPosition(0.0f, 0.0f, 0.0f);

  geometry_ = std::shared_ptr<Geometry>(new Geometry());

  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  {
    std::shared_ptr<std::string> verterShaderSource = std::shared_ptr<std::string>(new std::string());
    std::shared_ptr<std::string> fragmentShaderSource = std::shared_ptr<std::string>(new std::string());
    FILES::ReadFile("../../../../shaders/depth_buffer.vertx", verterShaderSource);
    FILES::ReadFile("../../../../shaders/depth_buffer.frag", fragmentShaderSource);
    material->setShader(verterShaderSource.get()->data(), fragmentShaderSource.get()->data());
  }

  std::shared_ptr<Drawable> drawable[amount];
  const float separation = -2.2f;
  const float pos_x_started = 15.0f;
  const float pos_y_started = 0.0f;
  const float pos_z_started = -5.0f;
  const int rows = 10;
  const int cols = 10;
  float pos[3] = { 0.0f, 0.0f, 0.0f };
  for (int i = 0; i < amount; ++i) {
    pos[0] = ((i % cols) * separation) + pos_x_started;
    pos[1] = ((i / (cols * rows)) * separation) + pos_y_started;
    pos[2] = (((i / cols) % rows) * separation) + pos_z_started;
    drawable[i] = std::shared_ptr<Drawable>(new Drawable("i"));
    drawable[i]->setGeometry(geometry_);
    drawable[i]->setMaterial(material);
    drawable[i]->setParent(getRoot());
    drawable[i]->setPosition(pos);
  }

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  std::shared_ptr<Material> lightMaterial = std::shared_ptr<Material>(new Material());
  {
    std::shared_ptr<std::string> verterShaderSource = std::shared_ptr<std::string>(new std::string());
    std::shared_ptr<std::string> fragmentShaderSource = std::shared_ptr<std::string>(new std::string());
    FILES::ReadFile("../../../../shaders/basics/1_Basic.vertx", verterShaderSource);
    FILES::ReadFile("../../../../shaders/basics/1_Basic.frag", fragmentShaderSource);
    lightMaterial->setShader(verterShaderSource.get()->data(), fragmentShaderSource.get()->data());
  }
  light->setGeometry(geometry_);
  light->setMaterial(lightMaterial);
  light->setParent(getRoot());
  light->setPosition(1.00f, 0.0f, 3.50f);
  AddLight(light);

  getRoot()->setPosition(-5.0f, -1.0f, -1.0f);
}

void ROTOM::DepthScene::input() {
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

void ROTOM::DepthScene::movement() {
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

void ROTOM::DepthScene::rotation() {
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

void ROTOM::DepthScene::scroll() {
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

void ROTOM::DepthScene::update() {
  getRoot()->moveZ(sin(TIME::appTime()) * 0.2);

  // Camera/View transformation
  glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  getCamera()->setViewMatrix(glm::value_ptr(view));
}