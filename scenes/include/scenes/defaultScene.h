/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __DEFAULT_SCENE_H__
#define __DEFAULT_SCENE_H__

#include "general/scene.h"

namespace ROTOM {
  class DefaultScene : public Scene {
  public:
    DefaultScene() {};
    ~DefaultScene() {};

    void init();

    void input();

    void update();

    void draw() {};

    void destroy() {};

    static const int amount_ = 2722;
    std::shared_ptr<Geometry> geometry_;
  };
}

#endif //__DEFAULT_SCENE_H__