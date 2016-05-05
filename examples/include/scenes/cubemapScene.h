/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __CUBEMAP_SCENE_H__
#define __CUBEMAP_SCENE_H__

#include "general/scene.h"
#include "render/cubemap.h"

namespace ROTOM {
  class CubemapScene : public Scene {
  public:
    CubemapScene() {};
    ~CubemapScene() {};

    void init();

    void input();

    void update();

    void draw();

    void destroy() {};

  private:
    Cubemap cubemap_;
  };
}

#endif //__CUBEMAP_SCENE_H__