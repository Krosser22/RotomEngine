/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/spotLight.h"
#include "render/graphics.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

ROTOM::SpotLight::SpotLight(char *name) {
  type_ = kNodeType_Light;

  name_ = name;

  specularIntensity_[0] = 1.0f;
  specularIntensity_[1] = 1.0f;
  specularIntensity_[2] = 1.0f;

  std::shared_ptr<Material> lightMaterial = std::shared_ptr<Material>(new Material("../../../../img/transparent.png"));
  lightMaterial->setShaderFromPath("basics/1_Basic.vertx", "basics/1_Basic.frag");
  setGeometry(std::shared_ptr<Geometry>(new Geometry()));
  setMaterial(lightMaterial);

  setupOrtho(-22.0f, 22.0f, -22.0f, 22.0f, 1.0f, 10.0f);
  visible_ = true;
}

ROTOM::SpotLight::~SpotLight() {}

void ROTOM::SpotLight::setupOrtho(float left, float right, float bottom, float top, float znear, float zfar) {
  projection_ = glm::ortho(left, right, bottom, top, znear, zfar);
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