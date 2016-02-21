/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __DEFAULT_SCENE_H__
#define __DEFAULT_SCENE_H__

#include "scene.h"
#include "drawable.h"
#include <memory>

const int amount = 1722;

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

    std::shared_ptr<Drawable> drawable1;
    std::shared_ptr<Drawable> drawable2;
    std::shared_ptr<Drawable> drawable3;
    std::shared_ptr<Drawable> drawable[amount];
  };
}

#endif //__DEFAULT_SCENE_H__