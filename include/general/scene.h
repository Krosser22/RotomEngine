/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __SCENE_H__
#define __SCENE_H__

#include "node/drawable.h"
#include "node/camera.h"
#include "node/light.h"
#include <memory>

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

    std::shared_ptr<Node> getRoot();

    void setRoot(std::shared_ptr<Node> root);

    Camera *getCamera();

    std::vector<std::shared_ptr<Light>> getLight();

    void AddLight(std::shared_ptr<Light> light);

  private:
    int nodes_ = 0;
    int vertexCount_ = 0;
  };
}

#endif //__SCENE_H__