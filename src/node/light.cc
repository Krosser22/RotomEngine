/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/light.h"
#include "render/graphics.h"
#include <glm/gtx/transform.hpp>

ROTOM::Light::Light(char *name) {
  type_ = kNodeType_Light;

  name_ = name;

  specularIntensity_[0] = 1.0f;
  specularIntensity_[1] = 1.0f;
  specularIntensity_[2] = 1.0f;

  std::shared_ptr<Material> lightMaterial = std::shared_ptr<Material>(new Material("../../../../img/transparent.png"));
  lightMaterial->setShaderFromPath("basics/1_Basic.vertx", "basics/1_Basic.frag");
  setGeometry(std::shared_ptr<Geometry>(new Geometry()));
  setMaterial(lightMaterial);

  setupOrtho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.0f);
  rotation_[0] = -90.0f;
}

ROTOM::Light::~Light() {}

void ROTOM::Light::setupOrtho(const float left, const float right, const float bottom, const float top, const float znear, const float zfar) {
  projection_ = glm::ortho(left, right, bottom, top, znear, zfar);
}

float *ROTOM::Light::projectionMatrix() {
  return glm::value_ptr(projection_);
}

float *ROTOM::Light::viewMatrix() {
  view_ = glm::rotate(view_, rotation_.x, rotX);
  view_ = glm::rotate(view_, rotation_.y, rotY);
  view_ = glm::rotate(view_, rotation_.z, rotZ);
  view_ = glm::translate(-position_);
  return glm::value_ptr(view_);
}

float *ROTOM::Light::spaceMatrix() {
  lightSpaceMatrix_ = projection_ * *viewMatrix();
  return glm::value_ptr(lightSpaceMatrix_);
}