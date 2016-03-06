/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __DEFAULT_SCENE_H__
#define __DEFAULT_SCENE_H__

#include "general/scene.h"
#include <memory>

namespace ROTOM {
  class DefaultScene : public ROTOM::Scene {
  public:
    DefaultScene() {};
    ~DefaultScene() {};

    void init();

    void input();

    void update();

    void draw() {};

    void destroy() {};

    static const int amount_ = 1722;
    std::shared_ptr<Geometry> geometry_;
  };
}

#endif //__DEFAULT_SCENE_H__