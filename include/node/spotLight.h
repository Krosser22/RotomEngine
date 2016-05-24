/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __SPOT_LIGHT_H__
#define __SPOT_LIGHT_H__

#include "drawable.h"

namespace ROTOM {
  class SpotLight : public Drawable {
  public:
    SpotLight(char *name);
    virtual ~SpotLight();

    float specularIntensity_[3];

    void setupOrtho(float left, float right, float bottom, float top, float znear, float zfar);

    float *projectionMatrix();

    float *viewMatrix();

    float *spaceMatrix();

  private:
    glm::fmat4 view_;
    glm::fmat4 projection_;
    glm::fmat4 lightSpaceMatrix_;
    glm::fmat4 identity_ = glm::fmat4();
    glm::fvec3 rotX_ = glm::fvec3(1.0f, 0.0f, 0.0f);
    glm::fvec3 rotY_ = glm::fvec3(0.0f, 1.0f, 0.0f);
    glm::fvec3 rotZ_ = glm::fvec3(0.0f, 0.0f, 1.0f);
    glm::fvec3 up_ = glm::fvec3(0.0f, 1.0f, 0.0f);
    glm::fvec3 front_ = glm::fvec3(0.0f, 0.0f, 1.0f);
  };
}

#endif //__SPOT_LIGHT_H__