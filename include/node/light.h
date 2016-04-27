/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "drawable.h"

namespace ROTOM {
  class Light : public Drawable {
  public:
    Light(char *name);
    virtual ~Light();

    float specularIntensity_[3];

    void setupOrtho(const float left, const float right, const float bottom, const float top, const float znear, const float zfar);

    float *projectionMatrix();

    float *viewMatrix();

    float *spaceMatrix();

  private:
    glm::fmat4 projection_;
  };
}

#endif //__LIGHT_H__