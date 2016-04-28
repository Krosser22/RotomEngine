/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "shadowScene.h"
#include "general/input.h"
#include "general/window.h"
#include <glm/gtc/matrix_transform.hpp>

void ROTOM::ShadowScene::init() {
  //Camera
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  //RenderTarget
  renderTarget_.init(WindowWidth(), WindowHeight());

  //Geometry
  geometry_ = std::shared_ptr<Geometry>(new Geometry());
  geometryFloor_ = std::shared_ptr<Geometry>(new Geometry());
  geometryFloor_->loadGeometry("Nanosuit/nanosuit");

  //ShadowMaterial
  std::shared_ptr<Material> shadowMaterial = std::shared_ptr<Material>(new Material("../../../../img/texture.png"));
  shadowMaterial->setShaderFromPath("shadows/1_Basic.vertx", "shadows/1_Basic.frag");
  //shadowMaterial->setShaderFromPath("basics/5_SpecularLight_Blinn-Phong.vertx", "basics/5_SpecularLight_Blinn-Phong.frag");

  //Material renderDepthToTexture
  std::shared_ptr<Material> materialRenderDepthToTexture = std::shared_ptr<Material>(new Material());
  materialRenderDepthToTexture->setShaderFromPath("renderToDepth.vertx", "renderToDepth.frag");
  materialRenderDepthToTexture->setTexture(renderTarget_.depthTexture());
  
  //Drawables
  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable("1"));
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable("2"));
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable("3"));
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable("4"));
  std::shared_ptr<Drawable> drawable5 = std::shared_ptr<Drawable>(new Drawable("5"));
  std::shared_ptr<Drawable> drawable6 = std::shared_ptr<Drawable>(new Drawable("6"));

  drawable1->setGeometry(geometry_);
  drawable1->setMaterial(shadowMaterial);
  drawable1->setParent(getRoot());

  drawable2->setGeometry(geometry_);
  drawable2->setMaterial(shadowMaterial);
  drawable2->setParent(drawable1);
  drawable2->setPositionX(1.0f);

  drawable3->setGeometry(geometry_);
  drawable3->setMaterial(shadowMaterial);
  drawable3->setParent(drawable2);
  drawable3->setPositionX(1.0f);

  drawable4->setGeometry(geometry_);
  drawable4->setMaterial(shadowMaterial);
  drawable4->setParent(drawable3);
  drawable4->setPositionX(1.0f);

  drawable5->setGeometry(geometryFloor_);
  drawable5->setMaterial(shadowMaterial);
  drawable5->setParent(getRoot());
  drawable5->setPosition(0.0f, -1.0f, -1.0f);

  drawable6->setGeometry(geometry_);
  drawable6->setMaterial(materialRenderDepthToTexture);
  drawable6->setParent(getRoot());
  drawable6->setPosition(0.0f, 1.0f, 0.0f);

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(0.0f, 0.0f, -4.0f);
  light->specularIntensity_[0] = 1.0f;
  light->specularIntensity_[1] = 1.0f;
  light->specularIntensity_[2] = 1.0f;
  AddLight(light);
}

void ROTOM::ShadowScene::input() {
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

void ROTOM::ShadowScene::movement() {
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

void ROTOM::ShadowScene::rotation() {
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

void ROTOM::ShadowScene::scroll() {
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

void ROTOM::ShadowScene::update() {
  if (INPUT::IsKeyDown('Q')) {
    Node *node = getRoot()->getChildAt(0)->getChildAt(0).get();
    node->setRotationX(node->rotation().x + 0.01f);
  }

  // Camera/View transformation
  getCamera()->setViewMatrix(glm::value_ptr(glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp)));
}

void ROTOM::ShadowScene::draw() {
  renderTarget_.begin();
  {
    RenderScene(getLight().begin()->get()->projectionMatrix(), getLight().begin()->get()->viewMatrix());
    //RenderScene(getCamera()->projectionMatrix(), getCamera()->viewMatrix());
  }
  renderTarget_.end();
}