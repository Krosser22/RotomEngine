/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __LIGHT_H__
#define __LIGHT_H__

namespace ROTOM {
  struct Light {
    float lightPositionX = 100.0f;
    float lightPositionY = 100.0f;
    float lightPositionZ = 100.0f;

    float lightColorX = 1.0f;
    float lightColorY = 1.0f;
    float lightColorZ = 1.0f;

    float specularIntensityX = 0.0f;
    float specularIntensityY = 0.0f;
    float specularIntensityZ = 0.0f;
    float specularIntensityW = 0.0f;
  };
}

#endif //__LIGHT_H__