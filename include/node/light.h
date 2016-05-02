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
    glm::fmat4 view_;
    glm::fmat4 projection_;
    glm::fmat4 lightSpaceMatrix_;
    glm::fmat4 identity_ = glm::fmat4();
    glm::fvec3 rotX = glm::fvec3(1.0f, 0.0f, 0.0f);
    glm::fvec3 rotY = glm::fvec3(0.0f, 1.0f, 0.0f);
    glm::fvec3 rotZ = glm::fvec3(0.0f, 0.0f, 1.0f);
  };
}

#endif //__LIGHT_H__