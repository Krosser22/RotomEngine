/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "material.h"
#include <glm/gtc/type_ptr.hpp>

namespace ROTOM {
  class Camera {
  public:
    Camera();
    ~Camera();

    float movementSpeed_ = 0.05f;
    float rotationSpeed_ = 0.5f;
    float scrollSpeed_ = 0.05f;

    void input();

    void update();

    void setPosition(float x, float y, float z);

    void setViewMatrix(glm::fmat4 viewMatrix);
    //void setViewMatrix(glm::fvec3 eye, glm::fvec3 center, glm::fvec3 up);
    float *viewMatrix();

    void setupPerspective(const float fovy, const float aspect, const float znear, const float zfar);
    void setupOrtho(const float left, const float right, const float bottom, const float top, const float znear, const float zfar);
    void setupFrustum(const float left, const float right, const float bottom, const float top, const float znear, const float zfar);
    float *projectionMatrix();

    //void setViewDirection(const float pos[3]);

    //void setViewTarget(const float pos[3]);
    //const float *target();

    //const float *forward();

    //void setUpDirection(const float pos[3]);
    //const float *upDirection();

    //Determine which objects are visible
    //void doCull(const Node *root);

    //Renders all visible (not culled) objects
    //void doRender();

  private:
    float yaw_ = 90.0f;	// Yaw is initialized to 90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
    float pitch_ = 0.0f;
    float lastX_ = 1280 * 0.5f;
    float lastY_ = 720 * 0.5f;
    float fov_ = 45.0f;
    float xoffset_ = 0.0f;
    float yoffset_ = 0.0f;

    glm::fvec3 position_ = glm::fvec3(0.0f, 0.0f, 0.0f);
    glm::fvec3 front_ = glm::fvec3(0.0f, 0.0f, -1.0f);
    glm::fvec3 up_ = glm::fvec3(0.0f, 1.0f, 0.0f);

    glm::fmat4 viewMatrix_;
    glm::fmat4 projectionMatrix_;

    void movement();

    void rotation();

    void scroll();
  };
}

#endif //__CAMERA_H__