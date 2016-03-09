/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __GEOMETRY_SCENE_H__
#define __GEOMETRY_SCENE_H__

#include "general/scene.h"
#include <memory>

namespace ROTOM {
  class GeometryScene : public ROTOM::Scene {
  public:
    GeometryScene() {};
    ~GeometryScene() {};

    void init();

    void input() {};

    void update();

    void draw();

    void destroy() {};

    static const int amount = 1722;
    std::shared_ptr<Geometry> geometry;
  };
}

#endif //__GEOMETRY_SCENE_H__