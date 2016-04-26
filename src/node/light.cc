/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/light.h"
#include "render/graphics.h"
#include <glm/gtc/matrix_transform.hpp>

ROTOM::Light::Light(char *name) {
  type_ = kNodeType_Light;

  name_ = name;

  specularIntensity_[0] = 0.1f;
  specularIntensity_[1] = 0.1f;
  specularIntensity_[2] = 0.1f;

  std::shared_ptr<Material> lightMaterial = std::shared_ptr<Material>(new Material());
  lightMaterial->setShaderFromPath("basics/1_Basic.vertx", "basics/1_Basic.frag");
  setGeometry(std::shared_ptr<Geometry>(new Geometry()));
  setMaterial(lightMaterial);

  setupOrtho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
  view_ = glm::fmat4();
}

ROTOM::Light::~Light() {}

void ROTOM::Light::setupOrtho(const float left, const float right, const float bottom, const float top, const float znear, const float zfar) {
  projection_ = glm::ortho(left, right, bottom, top, znear, zfar);
}

float *ROTOM::Light::projectionMatrix() {
  return glm::value_ptr(projection_);
}

float *ROTOM::Light::viewMatrix() {
  return glm::value_ptr(view_);
}

float *ROTOM::Light::spaceMatrix() {
  glm::fmat4 spaceMatrix = projection_ * view_;
  return glm::value_ptr(spaceMatrix);
}