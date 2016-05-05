/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __CUBEMAP_H__
#define __CUBEMAP_H__

//http://www.custommapmakers.org/skyboxes.php

namespace ROTOM {
  class Cubemap {
  public:
    Cubemap();
    ~Cubemap();

    void init(char *path);

    void draw(float *projectionMatrix, float *viewMatrix);
  };
}

#endif //__CUBEMAP_H__