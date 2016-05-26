/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/spotLight.h"
#include "render/graphics.h"
#include "general/window.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

ROTOM::SpotLight::SpotLight(char *name) {
  type_ = kNodeType_Light;

  name_ = name;

  std::shared_ptr<Material> lightMaterial = std::shared_ptr<Material>(new Material("../../../../img/transparent.png"));
  lightMaterial->setShaderFromPath("basics/1_Basic.vertx", "basics/1_Basic.frag");
  setGeometry(std::shared_ptr<Geometry>(new Geometry()));
  setMaterial(lightMaterial);

  setupPerspective(glm::radians(45.0f), (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  visible_ = true;
}

ROTOM::SpotLight::~SpotLight() {}

void ROTOM::SpotLight::setupPerspective(const float fovy, const float aspect, const float znear, const float zfar) {
  projection_ = glm::perspective(fovy, aspect, znear, zfar);
}

float *ROTOM::SpotLight::projectionMatrix() {
  return glm::value_ptr(projection_);
}

float *ROTOM::SpotLight::viewMatrix() {
  glm::fvec3 realFront = glm::rotateX(front_, rotation_.x);
  realFront = glm::rotateY(realFront, rotation_.y);
  realFront = glm::rotateZ(realFront, rotation_.z);
  view_ = glm::lookAt(position_, position_ + realFront, up_);
  return glm::value_ptr(view_);
}

float *ROTOM::SpotLight::spaceMatrix() {
  lightSpaceMatrix_ = projection_ * view_;
  return glm::value_ptr(lightSpaceMatrix_);
}