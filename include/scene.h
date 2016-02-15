/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __SCENE_H__
#define __SCENE_H__

#include "camera.h"
#include "light.h"
#include <vector>

namespace ROTOM {
  class Scene {
  public:
    Scene() {};
    ~Scene() {};

    void init();

    void update() {};

    void draw();

    void destroy();

    Node *getRoot();

  protected:
    Camera camera_;
    Node root_;
    std::vector<Light> lights_;
  };
}

#endif //__CAMERA_H__