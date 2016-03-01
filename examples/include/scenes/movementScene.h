/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __MOVEMENT_SCENE_H__
#define __MOVEMENT_SCENE_H__

#include "general/scene.h"
#include <memory>

namespace ROTOM {
  class MovementScene : public ROTOM::Scene {
  public:
    MovementScene() {};
    ~MovementScene() {};

    void init();

    void input();

    void update();

    void draw();

    void destroy() {};

    std::shared_ptr<Geometry> geometry;

  private:
    void moveCamera(char key);

    void rotateCamera();

    void updateCamera();
  };
}

#endif //__MOVEMENT_SCENE_H__