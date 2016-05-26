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
#include "node/directionalLight.h"
#include "node/spotLight.h"

namespace ROTOM {
  class Scene {
  public:
    Scene() {};
    ~Scene() {};

    virtual void init() = 0;

    virtual void input() = 0;

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual void postDraw() = 0;

    virtual void destroy() = 0;

    void setRoot(std::shared_ptr<Node> root);
    std::shared_ptr<Node> getRoot();

    void addDirectionalLight(std::shared_ptr<DirectionalLight> light);
    std::vector<std::shared_ptr<DirectionalLight>> getDirectionalLights();

    void addSpotLight(std::shared_ptr<SpotLight> light);
    std::vector<std::shared_ptr<SpotLight>> getSpotLights();

    void clearLights();

    Camera *getCamera();

  protected:
    ROTOM::Camera camera_;
    std::shared_ptr<ROTOM::Node> root_;
    std::vector<std::shared_ptr<ROTOM::DirectionalLight>> directionalLights_;
    std::vector<std::shared_ptr<ROTOM::SpotLight>> spotLights_;
  };
}

#endif //__SCENE_H__