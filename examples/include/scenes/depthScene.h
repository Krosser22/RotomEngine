/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __DEPTH_SCENE_H__
#define __DEPTH_SCENE_H__

#include "general/scene.h"
#include "general/CameraMovement.h"

namespace ROTOM {
  class DepthScene : public Scene {
  public:
    DepthScene() {};
    ~DepthScene() {};

    void init();

    void input();

    void update();

    void draw() {};

    void destroy() {};
    
  private:
    static const int amount = 100;
    std::shared_ptr<Geometry> geometry_;
    std::shared_ptr<Drawable> drawableBase_;
    CameraMovement cameraMovement_;
  };
}

#endif //__DEPTH_SCENE_H__