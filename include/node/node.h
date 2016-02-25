/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
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
  struct NodeData {
    bool dirtyModelLocal;
    bool dirtyModelWorld;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 modelLocal;
    glm::mat4 modelWorld;

    unsigned int parent;
    std::vector<unsigned int> childs;
    std::shared_ptr<Geometry> geometry;
    std::shared_ptr<Material> material;
    std::shared_ptr<MaterialSettings> materialSettings;
  };

  static NodeData nodeData[ROTOM::kNodeDataAmount];
  static unsigned int nextNodeID = 0;

  class Node {
  public:
    Node();
    virtual ~Node();

    unsigned int ID();

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

    void setParent(unsigned int parent);
    unsigned int parent();

    void addChild(unsigned int  child);
    void removeChild(unsigned int  child);
    unsigned int getChildAt(unsigned int i);
    const unsigned int childCount();

    void setGeometry(std::shared_ptr<Geometry> geometry);
    std::shared_ptr<Geometry> geometry();

    void setMaterial(std::shared_ptr<Material> material);
    std::shared_ptr<Material> material();

    void setMaterialSettings(std::shared_ptr<MaterialSettings> materialSettings);
    std::shared_ptr<MaterialSettings> materialSettings();

  protected:
    unsigned int ID_;

    void setParent(unsigned int node, unsigned int parent);
    void addChild(unsigned int node, unsigned int child);
    void removeChild(unsigned int node, unsigned int child);
    unsigned int getChildAt(unsigned int node, unsigned int i);

    void setModelLocalDirty();

    //Change the flag b_dirtyModelWorld_ of the children
    void alertChildsModelWorldChanged();
  };
}

#endif //__NODE_H__