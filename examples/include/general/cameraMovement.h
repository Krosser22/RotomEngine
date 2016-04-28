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

    float movementSpeed = 0.05f;
    float rotationSpeed = 0.5f;
    float scrollSpeed = 0.05f;

    void setCameraToMove(Camera *camera);

    void input();

    void update();
    
  private:
    Camera *camera_;

    glm::fvec3 cameraPos = glm::fvec3(0.0f, 0.0f, 2.2f);
    glm::fvec3 cameraFront = glm::fvec3(0.0f, 0.0f, -1.0f);
    glm::fvec3 cameraUp = glm::fvec3(0.0f, 1.0f, 0.0f);

    float yaw = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX = 1280 * 0.5f;
    float lastY = 720 * 0.5f;
    float fov = 45.0f;

    void movement();

    void rotation();

    void scroll();
  };
}

#endif //__CAMERA_MOVEMENT_H__