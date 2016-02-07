/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __NODE_H__
#define __NODE_H__

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"

#include <vector>

namespace ROTOM {
  class Node {
  public:
    Node();
    virtual ~Node();

    void move(const float movement[3]);
    void moveX(const float movementX);
    void moveY(const float movementY);
    void moveZ(const float movementZ);

    void setPosition(const float position[3]);
    void setPosition(const float x, const float y, const float z);
    glm::vec3 position();
    void setPositionX(const float positionX);
    float positionX();
    void setPositionY(const float positionY);
    float positionY();
    void setPositionZ(const float positionZ);
    float positionZ();

    void setRotation(const float rotation[3]);
    void setRotation(const float x, const float y, const float z);
    glm::vec3 rotation();
    void setRotationX(const float rotationX);
    float rotationX();
    void setRotationY(const float rotationY);
    float rotationY();
    void setRotationZ(const float rotationZ);
    float rotationZ();

    void setScale(const float scale[3]);
    void setScale(const float x, const float y, const float z);
    glm::vec3 scale();
    void setScaleX(const float scaleX);
    float scaleX();
    void setScaleY(const float scaleY);
    float scaleY();
    void setScaleZ(const float scaleZ);
    float scaleZ();

    void setModelLocal(glm::mat4 modelLocal);
    glm::mat4 *modelLocal();
    bool isDirtyModelLocal();

    void setModelWorld(glm::mat4 modelWorld);
    glm::mat4 *modelWorld();
    bool isDirtyModelWorld();

    void setParent(Node *parent);
    const Node *parent();

    void addChild(Node *child);
    void removeChild(const Node *child);
    Node *getChildAt(unsigned int i);
    const unsigned int childCount();

  protected:
    glm::vec3 v_position_;
    glm::vec3 v_rotation_;
    glm::vec3 v_scale_;

    glm::mat4 m_modelLocal_;
    glm::mat4 m_modelWorld_;

    bool b_dirtyModelLocal_;
    bool b_dirtyModelWorld_;

    Node *parent_;
    std::vector<Node *> childs_;

    void setModelLocalDirty();

    //Change the flag b_dirtyModelWorld_ of the children
    void alertChildsModelWorldChanged();
  };
}

#endif //__NODE_H__