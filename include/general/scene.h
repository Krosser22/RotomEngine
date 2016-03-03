/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
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

    void drawHUD();

    std::shared_ptr<Node> getRoot();

    void setRoot(std::shared_ptr<Node> root);

    Camera *getCamera();

    std::vector<Light> getLight();

    void AddLight(Light light);

  private:
    int nodes_ = 0;
    int vertexCount_ = 0;

    void updateInfo();
  };
}

#endif //__SCENE_H__