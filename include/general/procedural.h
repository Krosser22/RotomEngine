/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __PROCEDURAL_H__
#define __PROCEDURAL_H__

namespace ROTOM {
  namespace PROCEDURAL {
    float perlinNoise(float x, float y, float z, int x_wrap = 0, int y_wrap = 0, int z_wrap = 0);
  }
}

#endif //__PROCEDURAL_H__