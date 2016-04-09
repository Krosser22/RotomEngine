/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __RENDER_TO_TEXTURE_SCENE_H__
#define __RENDER_TO_TEXTURE_SCENE_H__

#include "general/scene.h"
#include <memory>

namespace ROTOM {
  class RenderToTextureScene : public Scene {
  public:
    RenderToTextureScene() {};
    ~RenderToTextureScene() {};

    void init();

    void input();

    void update();

    void draw();

    void destroy() {};
    
  private:
    std::shared_ptr<Geometry> geometry_;
    std::shared_ptr<Material> materialRenderToTexture_;

    glm::fvec3 cameraPos = glm::fvec3(0.0f, 0.0f, 3.0f);
    glm::fvec3 cameraFront = glm::fvec3(0.0f, 0.0f, -1.0f);
    glm::fvec3 cameraUp = glm::fvec3(0.0f, 1.0f, 0.0f);
    float yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX = 1280 / 2.0;
    float lastY = 720 / 2.0;
    float fov = 45.0f;

    float movementSpeed = 0.05f; // Change this value to your liking
    float rotationSpeed = 0.5f;	// Change this value to your liking
    float scrollSpeed = 0.05f; // Change this value to your liking

    void movement();

    void rotation();

    void scroll();
  };
}

#endif //__RENDER_TO_TEXTURE_SCENE_H__