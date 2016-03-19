/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/light.h"

ROTOM::Light::Light(char *name) {
  type_ = kNodeType_Light;

  name_ = name;

  specularIntensity[0] = 0.1f;
  specularIntensity[1] = 0.1f;
  specularIntensity[2] = 0.1f;

  std::shared_ptr<Material> lightMaterial = std::shared_ptr<Material>(new Material());
  lightMaterial->setShaderFromPath("basics/1_Basic.vertx", "basics/1_Basic.frag");
  setGeometry(std::shared_ptr<Geometry>(new Geometry()));
  setMaterial(lightMaterial);
}

ROTOM::Light::~Light() {}
