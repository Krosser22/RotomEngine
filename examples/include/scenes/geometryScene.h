/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __GEOMETRY_SCENE_H__
#define __GEOMETRY_SCENE_H__

#include "general/scene.h"
#include <memory>

namespace ROTOM {
  class GeometryScene : public Scene {
  public:
    GeometryScene() {};
    ~GeometryScene() {};

    void init();

    void input() {};

    void update();

    void draw();

    void destroy() {};

    static const int amount = 5000;
    std::shared_ptr<Geometry> geometry;
  };
}

#endif //__GEOMETRY_SCENE_H__