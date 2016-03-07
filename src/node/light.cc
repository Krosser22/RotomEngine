/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "node/light.h"

ROTOM::Light::Light(char *name) {
  type_ = kNodeType_Light;

  name_ = name;

  lightColor[0] = 1.0f;
  lightColor[1] = 1.0f;
  lightColor[2] = 1.0f;
  lightColor[3] = 1.0f;

  specularIntensity[0] = 0.0f;
  specularIntensity[1] = 0.0f;
  specularIntensity[2] = 0.0f;
  specularIntensity[3] = 0.0f;
}

ROTOM::Light::~Light() {}
