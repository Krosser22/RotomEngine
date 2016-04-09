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
#include <memory>

namespace ROTOM {
  class DepthScene : public Scene {
  public:
    DepthScene() {};
    ~DepthScene() {};

    void init();

    void input();

    void update();

    void draw();

    void destroy() {};
    
  private:
    static const int amount = 100;
    std::shared_ptr<Geometry> geometry_;
    std::shared_ptr<Drawable> drawableBase_;

    glm::fvec3 cameraPos = glm::fvec3(0.0f, 0.0f, 3.0f);
    glm::fvec3 cameraFront = glm::fvec3(0.0f, 0.0f, -1.0f);
    glm::fvec3 cameraUp = glm::fvec3(0.0f, 1.0f, 0.0f);
    float yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX = 1280 / 2.0;
    float lastY = 720 / 2.0;
    float fov = 45.0f;

    float movementSpeed = 0.05f;
    float rotationSpeed = 0.5f;
    float scrollSpeed = 0.05f;

    void movement();

    void rotation();

    void scroll();
  };
}

#endif //__DEPTH_SCENE_H__