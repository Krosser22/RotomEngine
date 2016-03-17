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

    //float lightColor[3];
    float specularIntensity[3];
  };
}

#endif //__LIGHT_H__