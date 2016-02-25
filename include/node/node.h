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

    static unsigned int getNewNode();

    static void move(unsigned int node, const float movement[3]);
    static void move(unsigned int node, const float x, const float y, const float z);
    static void moveX(unsigned int node, const float movementX);
    static void moveY(unsigned int node, const float movementY);
    static void moveZ(unsigned int node, const float movementZ);

    static void setPosition(unsigned int node, const float position[3]);
    static void setPosition(unsigned int node, const float x, const float y, const float z);
    static glm::vec3 position(unsigned int node);
    static void setPositionX(unsigned int node, const float positionX);
    static float positionX(unsigned int node);
    static void setPositionY(unsigned int node, const float positionY);
    static float positionY(unsigned int node);
    static void setPositionZ(unsigned int node, const float positionZ);
    static float positionZ(unsigned int node);

    static void setRotation(unsigned int node, const float rotation[3]);
    static void setRotation(unsigned int node, const float x, const float y, const float z);
    static glm::vec3 rotation(unsigned int node);
    static void setRotationX(unsigned int node, const float rotationX);
    static float rotationX(unsigned int node);
    static void setRotationY(unsigned int node, const float rotationY);
    static float rotationY(unsigned int node);
    static void setRotationZ(unsigned int node, const float rotationZ);
    static float rotationZ(unsigned int node);

    static void setScale(unsigned int node, const float scale[3]);
    static void setScale(unsigned int node, const float x, const float y, const float z);
    static glm::vec3 scale(unsigned int node);
    static void setScaleX(unsigned int node, const float scaleX);
    static float scaleX(unsigned int node);
    static void setScaleY(unsigned int node, const float scaleY);
    static float scaleY(unsigned int node);
    static void setScaleZ(unsigned int node, const float scaleZ);
    static float scaleZ(unsigned int node);

    static void setModelLocal(unsigned int node, glm::mat4 modelLocal);
    static glm::mat4 *modelLocal(unsigned int node);
    static bool isDirtyModelLocal(unsigned int node);

    static void setModelWorld(unsigned int node, glm::mat4 modelWorld);
    static glm::mat4 *modelWorld(unsigned int node);
    static bool isDirtyModelWorld(unsigned int node);

    static void setParent(unsigned int node, unsigned int parent);
    static unsigned int parent(unsigned int node);

    static void addChild(unsigned int node, unsigned int  child);
    static void removeChild(unsigned int node, unsigned int  child);
    static unsigned int getChildAt(unsigned int node, unsigned int i);
    static const unsigned int childCount(unsigned int node);

    static void setGeometry(unsigned int node, std::shared_ptr<Geometry> geometry);
    static std::shared_ptr<Geometry> geometry(unsigned int node);

    static void setMaterial(unsigned int node, std::shared_ptr<Material> material);
    static std::shared_ptr<Material> material(unsigned int node);

    static void setMaterialSettings(unsigned int node, std::shared_ptr<MaterialSettings> materialSettings);
    static std::shared_ptr<MaterialSettings> materialSettings(unsigned int node);

  protected:
    //Change the flag b_dirtyModelWorld_ of the children
    static void alertChildsModelWorldChanged(unsigned int node);
  };
}

#endif //__NODE_H__