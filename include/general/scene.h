/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __SCENE_H__
#define __SCENE_H__

#include "node/camera.h"
#include "node/node.h"
#include "node/light.h"

namespace ROTOM {
  class Scene {
  public:
    Scene() {};
    ~Scene() {};

    virtual void init() = 0;

    virtual void input() = 0;

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual void destroy() = 0;

    void setRoot(std::shared_ptr<Node> root);
    std::shared_ptr<Node> getRoot();

    void AddLight(std::shared_ptr<Light> light);
    std::vector<std::shared_ptr<Light>> getLight();

    Camera *getCamera();
  };
}

#endif //__SCENE_H__