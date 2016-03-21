/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "node.h"
#include "glm/gtc/type_ptr.hpp"

namespace ROTOM {
  class Camera : public Node {
  public:
    Camera(char *name);
    ~Camera();

    void setupPerspective(const float fovy, const float aspect, const float znear, const float zfar);

    void setupOrtho(const float left, const float right, const float bottom, const float top, const float znear, const float zfar);

    void setupFrustum(const float left, const float right, const float bottom, const float top, const float znear, const float zfar);

    //void setViewDirection(const float pos[3]);

    void setViewTarget(const float pos[3]);
    const float *target();

    const float *forward();

    //void setUpDirection(const float pos[3]);
    //const float *upDirection();

    void setProjectionMatrix(const float data[16]);
    float *projectionMatrix();

    void setViewMatrix(const float data[16]);
    float *viewMatrix();

    //Determine which objects are visible
    //void doCull(const Node *root);

    //Renders all visible (not culled) objects
    void doRender();

    void renderToTexture(Material *material);

  private:
    glm::vec3 target_;
    glm::mat4 projection_;
  };
}

#endif //__CAMERA_H__