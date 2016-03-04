/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __LIGHT_H__
#define __LIGHT_H__

namespace ROTOM {
  struct Light {
    float lightPosition[3];
    float lightColor[4];
    float specularIntensity[4];

    Light() {
      lightPosition[0] = 10.0f;
      lightPosition[1] = 10.0f;
      lightPosition[2] = 10.0f;

      lightColor[0] = 1.0f;
      lightColor[1] = 1.0f;
      lightColor[2] = 1.0f;
      lightColor[3] = 1.0f;

      specularIntensity[0] = 0.0f;
      specularIntensity[1] = 0.0f;
      specularIntensity[2] = 0.0f;
      specularIntensity[3] = 0.0f;
    }
  };
}

#endif //__LIGHT_H__