/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
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

    float lightColor[4];
    float specularIntensity[4];
  };
}

#endif //__LIGHT_H__