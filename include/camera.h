/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "commandDrawObject.h"
#include "displayList.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "node.h"
#include "taskManager.h"
#include "taskCalculateMatrix.h"

namespace ROTOM {
  class Camera {
  public:
    Camera();
    ~Camera();

    CommandDrawObject commandDrawObject_;//TODO - Move this to private

    void setupPerspective(const float fovy, const float aspect, const float znear, const float zfar);

    void setupOrtho(const float left, const float right, const float bottom, const float top, const float znear, const float zfar);

    void setupFrustum(const float left, const float right, const float bottom, const float top, const float znear, const float zfar);

    void setPosition(const float pos[3]);
    float *position();

    void setRotation(const float rot[3]);
    float *rotation();
    
    //void setViewDirection(const float pos[3]);

    //void setViewTarget(const float pos[3]);
    //const float *target();

    //void setUpDirection(const float pos[3]);
    //const float *upDirection();

    void setProjectionMatrix(const float data[16]);
    float *projectionMatrix();

    void setViewMatrix(const float data[16]);
    float *viewMatrix();

    Node *root();

    //Determine which objects are visible
    //void doCull(const Node *root);

    //Renders all visible (not culled) objects
    void doRender();

  private:
    glm::vec3 v_position_;
    glm::vec3 v_rotation_;
    //glm::vec3 v_target_;

    glm::mat4 m_view_;
    glm::mat4 m_projection_;

    Node root_;

    DisplayList displayList_;

    bool b_dirtyView_;

    TaskManager taskManager_;

    std::shared_ptr<TaskCalculateMatrix> taskCalculateMatrix_;

    void cleanViewMatrix();

    //Task
    void updateTaskCalculateMatrix();

    void updateTasks();
  };
}

#endif //__CAMERA_H__