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

    std::shared_ptr<Node> getRoot();

    Camera *getCamera();

    std::vector<std::shared_ptr<Light>> getLight();

    void addLight(std::shared_ptr<Light> light);
  };
}

#endif //__CAMERA_H__