/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __NODE_H__
#define __NODE_H__

#include "glm/gtc/type_ptr.hpp"
#include <memory>
#include <vector>

namespace ROTOM {
  class Node : public std::enable_shared_from_this<Node> {
  public:
    Node();
    virtual ~Node();

    void move(const float movement[3]);
    void move(const float x, const float y, const float z);
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

    void setParent(std::shared_ptr<Node> parent);
    std::shared_ptr<Node> parent();

    void addChild(std::shared_ptr<Node> child);
    void removeChild(std::shared_ptr<Node> child);
    std::shared_ptr<Node> getChildAt(unsigned int i);
    const unsigned int childCount();

  protected:
    glm::vec3 v_position_;
    glm::vec3 v_rotation_;
    glm::vec3 v_scale_;

    glm::mat4 m_modelLocal_;
    glm::mat4 m_modelWorld_;

    bool b_dirtyModelLocal_;
    bool b_dirtyModelWorld_;

    std::shared_ptr<Node> parent_;
    std::vector<std::shared_ptr<Node>> childs_;

    void setModelLocalDirty();

    //Change the flag b_dirtyModelWorld_ of the children
    void alertChildsModelWorldChanged();
  };
}

#endif //__NODE_H__