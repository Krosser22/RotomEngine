/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __CAMERA_MOVEMENT_H__
#define __CAMERA_MOVEMENT_H__

#include "node/camera.h"

namespace ROTOM {
  class CameraMovement {
  public:
    CameraMovement() {};
    ~CameraMovement() {};

    float movementSpeed_ = 0.05f;
    float rotationSpeed_ = 0.5f;
    float scrollSpeed_ = 0.05f;

    void setCameraToMove(Camera *camera);

    void input();

    void update();
    
  private:
    Camera *camera_;

    glm::fvec3 cameraPos_ = glm::fvec3(2.2f, 2.2f, 2.2f);
    glm::fvec3 cameraFront_ = glm::fvec3(0.0f, 0.0f, 1.0f);
    glm::fvec3 cameraUp_ = glm::fvec3(0.0f, 1.0f, 0.0f);
    glm::fvec3 cameraRot_ = glm::fvec3(0.0f, 0.0f, 0.0f);

    float yaw_ = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
    float pitch_ = 0.0f;
    float lastX_ = 1280 * 0.5f;
    float lastY_ = 720 * 0.5f;
    float fov_ = 45.0f;
    float xoffset_ = 0.0f;
    float yoffset_ = 0.0f;
    glm::fvec3 front_;
    glm::fvec3 rotX = glm::fvec3(1.0f, 0.0f, 0.0f);
    glm::fvec3 rotY = glm::fvec3(0.0f, 1.0f, 0.0f);
    glm::fvec3 rotZ = glm::fvec3(0.0f, 0.0f, 1.0f);

    void movement();

    void rotation();

    void scroll();
  };
}

#endif //__CAMERA_MOVEMENT_H__