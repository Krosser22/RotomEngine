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

  setupOrtho(-10.0f, 10.0f, 10.0f, -10.0f, 1.0f, 10.0f);
  visible_ = true;
}

ROTOM::Light::~Light() {}

void ROTOM::Light::setupOrtho(const float left, const float right, const float bottom, const float top, const float znear, const float zfar) {
  projection_ = glm::ortho(left, right, bottom, top, znear, zfar);
}

float *ROTOM::Light::projectionMatrix() {
  return glm::value_ptr(projection_);
}

float *ROTOM::Light::viewMatrix() {
  view_ = glm::rotate(identity_, -rotation_.x, rotX_);
  view_ = glm::rotate(view_, -rotation_.y, rotY_);
  view_ = glm::rotate(view_, -rotation_.z, rotZ_);
  view_ = glm::translate(view_, -position_);

  ////////////////////////////////////////////
  ////////////////////////////////////////////
  ////////////////////////////////////////////

  // Make sure that when pitch is out of bounds, screen doesn't get flipped
  //if (rotation_.y > 89.0f) rotation_.y = 89.0f;
  //if (rotation_.y < -89.0f) rotation_.y = -89.0f;
  //front_.x = cos(rotation_.x) * cos(rotation_.y);
  //front_.y = sin(rotation_.y);
  //front_.z = sin(rotation_.x) * cos(rotation_.y);
  //front_ = glm::normalize(front_);
  //view_ = glm::lookAt(position_, position_ + front_, up_);

  ////////////////////////////////////////////
  ////////////////////////////////////////////
  ////////////////////////////////////////////

  //view_ = glm::lookAt(position_, position_ + glm::fvec3(0.0f, 0.0f, 1.0f), glm::fvec3(0.0f, 1.0f, 0.0f));
  return glm::value_ptr(view_);
}

float *ROTOM::Light::spaceMatrix() {
  lightSpaceMatrix_ = projection_ * view_;
  return glm::value_ptr(lightSpaceMatrix_);
}