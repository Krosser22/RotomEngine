/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/light.h"
#include "render/graphics.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtc/type_ptr.hpp"

unsigned int textureDepthbuffer;
unsigned int depthFramebuffer;
ROTOM::Material *matToRenderDepthTexture;

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
}

ROTOM::Light::~Light() {}

void ROTOM::Light::setupOrtho(const float left, const float right, const float bottom, const float top, const float znear, const float zfar) {
  projection_ = glm::ortho(left, right, bottom, top, znear, zfar);
}

float *ROTOM::Light::projectionMatrix() {
  return glm::value_ptr(projection_);
}

//TODO - Change this
float *ROTOM::Light::viewMatrix() {
  return (float *)glm::value_ptr(glm::lookAt(position(), glm::fvec3(0.0f), glm::fvec3(0.0f, 1.0f, 0.0f)));
}

//TODO - Change this
float *ROTOM::Light::spaceMatrix() {
  return (float *)glm::value_ptr(projection_ * glm::lookAt(position(), glm::fvec3(0.0f), glm::fvec3(0.0f, 1.0f, 0.0f)));
}

void ROTOM::Light::renderDepthToTexture(Material *material) {
  GRAPHICS::setRenderDepthTexture(material, &textureDepthbuffer, &depthFramebuffer);
  matToRenderDepthTexture = material;
}

void ROTOM::Light::beginRenderDepthToTexture() {
  matToRenderDepthTexture->texture_ = textureDepthbuffer;
  GRAPHICS::beginFramebuffer(depthFramebuffer);
}

void ROTOM::Light::endRenderDepthToTexture() {
  GRAPHICS::endFramebuffer();
}