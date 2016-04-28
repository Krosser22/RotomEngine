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

    void move(const float movement[3]);
    void move(const float x, const float y, const float z);
    void moveX(const float movementX);
    void moveY(const float movementY);
    void moveZ(const float movementZ);

    void setPosition(const float position[3]);
    void setPosition(const float x, const float y, const float z);
    glm::fvec3 position();
    void setPositionX(const float positionX);
    float positionX();
    void setPositionY(const float positionY);
    float positionY();
    void setPositionZ(const float positionZ);
    float positionZ();

    void setRotation(const float rotation[3]);
    void setRotation(const float x, const float y, const float z);
    glm::fvec3 rotation();
    void setRotationX(const float rotationX);
    float rotationX();
    void setRotationY(const float rotationY);
    float rotationY();
    void setRotationZ(const float rotationZ);
    float rotationZ();

    void setViewMatrix(glm::fmat4 viewMatrix);
    void setViewMatrix(glm::fvec3 eye, glm::fvec3 center, glm::fvec3 up);
    float *viewMatrix();
    bool isDirtyViewMatrix();

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
    bool dirtyViewMatrix_;
    glm::fvec3 position_;
    glm::fvec3 rotation_;
    glm::fvec3 target_;
    glm::fmat4 viewMatrix_;
    glm::fmat4 projectionMatrix_;
  };
}

#endif //__CAMERA_H__