/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __NODE_H__
#define __NODE_H__

#include "geometry.h"
#include "material.h"
#include "materialSettings.h"
#include "general/constants.h"
#include "glm/gtc/type_ptr.hpp"
#include <memory>
#include <vector>

namespace ROTOM {
  class Node : public std::enable_shared_from_this<Node> {
  public:
    Node();
    Node(char *name);
    virtual ~Node();

    NodeType type();

    void setName(char *name);
    const char *name();

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

    void setScale(const float scale[3]);
    void setScale(const float x, const float y, const float z);
    glm::fvec3 scale();
    void setScaleX(const float scaleX);
    float scaleX();
    void setScaleY(const float scaleY);
    float scaleY();
    void setScaleZ(const float scaleZ);
    float scaleZ();

    void setModelLocal(glm::fmat4 modelLocal);
    glm::fmat4 *modelLocal();
    bool isDirtyModelLocal();

    void setModelWorld(glm::fmat4 modelWorld);
    glm::fmat4 *modelWorld();

    void setParent(std::shared_ptr<Node> parent);
    std::shared_ptr<Node> parent();

    void addChild(std::shared_ptr<Node> child);
    void removeChild(std::shared_ptr<Node> child);
    std::shared_ptr<Node> getChildAt(unsigned int i);
    const unsigned int childCount();

  protected:
    NodeType type_;

    std::string name_;

    glm::fvec3 position_;
    glm::fvec3 rotation_;
    glm::fvec3 scale_;
    bool dirtyModelLocal_;
    
    glm::fmat4 modelLocal_;
    glm::fmat4 modelWorld_;

    std::shared_ptr<Node> parent_;
    std::vector<std::shared_ptr<Node>> childs_;
  };
}

#endif //__NODE_H__