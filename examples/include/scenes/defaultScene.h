/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __DEFAULT_SCENE_H__
#define __DEFAULT_SCENE_H__

#include "general/scene.h"
#include "node/drawable.h"
#include <memory>

namespace ROTOM {
  class DefaultScene : public ROTOM::Scene {
  public:
    DefaultScene() {};
    ~DefaultScene() {};

    void init();

    void input() {};

    void update();

    void draw();

    void destroy() {};

    static const int amount = 1722;
    std::shared_ptr<Geometry> geometry;
  };
}

#endif //__DEFAULT_SCENE_H__