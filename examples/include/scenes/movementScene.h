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

    std::shared_ptr<Geometry> geometry_;

    float cameraSpeed_ = 0.05f;
    float mxLastFrame_ = 0.0f, myLastFrame_ = 0.0f, mx_ = 0.0f, my_ = 0.0f;
    float cameraPos_[3];
  private:
    void moveCamera(unsigned char key);

    void rotateCamera();

    void updateCamera();
  };
}

#endif //__MOVEMENT_SCENE_H__