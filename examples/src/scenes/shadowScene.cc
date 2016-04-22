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
#include "scenes/renderToTextureScene.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void ROTOM::RenderToTextureScene::init() {
  //Camera
  getCamera()->setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);

  //Geometry
  geometry_ = std::shared_ptr<Geometry>(new Geometry());

  //Material
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material("../../../../img/texture.png"));
  material->setShaderFromPath("basics/4_SpecularLight.vertx", "basics/4_SpecularLight.frag");

  //Material renderColorToTexture
  std::shared_ptr<Material> materialRenderColorToTexture;
  materialRenderColorToTexture = std::shared_ptr<Material>(new Material());
  materialRenderColorToTexture->setShaderFromPath("basics/2_Texture.vertx", "basics/2_Texture.frag");

  //Material renderDepthToTexture
  std::shared_ptr<Material> materialRenderDepthToTexture;
  materialRenderDepthToTexture = std::shared_ptr<Material>(new Material());
  materialRenderDepthToTexture->setShaderFromPath("renderToDepth.vertx", "renderToDepth.frag");

  //Material renderDepthToTexture
  std::shared_ptr<Material> materialWithShadows;
  materialWithShadows = std::shared_ptr<Material>(new Material());
  materialWithShadows->setShaderFromPath("shadows/1_Basic.vertx", "shadows/1_Basic.frag");
  
  //Drawables
  std::shared_ptr<Drawable> drawable1 = std::shared_ptr<Drawable>(new Drawable("1"));
  std::shared_ptr<Drawable> drawable2 = std::shared_ptr<Drawable>(new Drawable("2"));
  std::shared_ptr<Drawable> drawable3 = std::shared_ptr<Drawable>(new Drawable("3"));
  std::shared_ptr<Drawable> drawable4 = std::shared_ptr<Drawable>(new Drawable("4"));
  std::shared_ptr<Drawable> drawable5 = std::shared_ptr<Drawable>(new Drawable("5"));

  drawable1->setGeometry(geometry_);
  drawable1->setMaterial(material);
  drawable1->setParent(getRoot());
  drawable1->setPosition(-2.0f, 0.0f, -2.0f);

  drawable2->setGeometry(geometry_);
  drawable2->setMaterial(material);
  drawable2->setParent(drawable1);
  drawable2->setPositionX(1.0f);

  drawable3->setGeometry(geometry_);
  drawable3->setMaterial(materialRenderColorToTexture);
  drawable3->setParent(drawable2);
  drawable3->setPositionX(1.0f);

  drawable4->setGeometry(geometry_);
  drawable4->setMaterial(materialRenderDepthToTexture);
  drawable4->setParent(drawable3);
  drawable4->setPositionX(1.0f);

  drawable5->setGeometry(geometry_);
  drawable5->setMaterial(materialWithShadows);
  drawable5->setParent(drawable4);
  drawable5->setPositionX(1.0f);

  //Light
  std::shared_ptr<Light> light = std::shared_ptr<Light>(new Light("light"));
  light->setParent(getRoot());
  light->setPosition(1.0f, 2.5f, 2.2f);
  light->materialSettings()->color_[0] = 0.8f;
  light->materialSettings()->color_[1] = 0.6f;
  light->materialSettings()->color_[2] = 0.4f;
  light->specularIntensity_[0] = 1.0f;
  light->specularIntensity_[1] = 1.0f;
  light->specularIntensity_[2] = 1.0f;
  AddLight(light);

  getCamera()->renderColorToTexture(materialRenderColorToTexture.get());
  getLight().begin()->get()->renderDepthToTexture(materialRenderDepthToTexture.get());
}

void ROTOM::RenderToTextureScene::input() {
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

void ROTOM::RenderToTextureScene::movement() {
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

void ROTOM::RenderToTextureScene::rotation() {
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

void ROTOM::RenderToTextureScene::scroll() {
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

void ROTOM::RenderToTextureScene::update() {
  if (INPUT::IsKeyDown('Q')) {
    Node *node = getRoot()->getChildAt(0)->getChildAt(0).get();
    node->setRotationX(node->rotation().x + 0.01f);
  }

  // Camera/View transformation
  glm::fmat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  getCamera()->setViewMatrix(glm::value_ptr(view));
}

void ROTOM::RenderToTextureScene::draw() {
  getCamera()->beginRenderColorToTexture();
  RenderScene(getCamera()->projectionMatrix(), getCamera()->viewMatrix());
  getCamera()->endRenderColorToTexture();

  getLight().begin()->get()->beginRenderDepthToTexture();
  RenderScene(getLight().begin()->get()->projectionMatrix(), getCamera()->viewMatrix());
  getLight().begin()->get()->endRenderDepthToTexture();

  RenderImGui();
}
