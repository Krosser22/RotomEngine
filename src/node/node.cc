/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "node/node.h"
#include "render/graphics.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"

ROTOM::Node::Node() {
  /*setPosition(0.0f, 0.0f, 0.0f);
  setRotation(0.0f, 0.0f, 0.0f);
  setScale(1.0f, 1.0f, 1.0f);

  nodeData[node].parent = -1; //TODO - Change this to 0 to set the root the 0 node of the array
  nodeData[node].geometry = NULL;
  nodeData[node].material = NULL;
  setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings()));*/
};

ROTOM::Node::~Node() {
  // Properly de-allocate all resources once they've outlived their purpose
  /*GRAPHICS::releaseMaterial(nodeData[node].material->shaderData_.shaderProgram);

  if (nodeData[node].parent != -1) {
    removeChild(nodeData[node].parent, node);
  }

  while (nodeData[node].childs.size() > 0) {
    //nodeData[node].childs.at(nodeData[node].childs.size() - 1)->~Node();
    nodeData[node].childs.pop_back();
  }*/
}

unsigned int ROTOM::Node::getNewNode() {
  int ID = nextNodeID++;
  assert("ERROR: Too many Nodes created" && ID < kNodeDataAmount);
  return ID;
}

void ROTOM::Node::move(unsigned int node, const float movement[3]) {
  setPosition(node, nodeData[node].position.x + movement[0], nodeData[node].position.y + movement[1], nodeData[node].position.z + movement[2]);
}

void ROTOM::Node::move(unsigned int node, const float x, const float y, const float z) {
  setPosition(node, nodeData[node].position.x + x, nodeData[node].position.y + y, nodeData[node].position.z + z);
}

void ROTOM::Node::moveX(unsigned int node, const float movementX) {
  setPosition(node, nodeData[node].position.x + movementX, nodeData[node].position.y, nodeData[node].position.z);
}

void ROTOM::Node::moveY(unsigned int node, const float movementY) {
  setPosition(node, nodeData[node].position.x, nodeData[node].position.y + movementY, nodeData[node].position.z);
}

void ROTOM::Node::moveZ(unsigned int node, const float movementZ) {
  setPosition(node, nodeData[node].position.x, nodeData[node].position.y, nodeData[node].position.z + movementZ);
}

void ROTOM::Node::setPosition(unsigned int node, const float position[3]) {
  setPosition(node, position[0], position[1], position[2]);
}

void ROTOM::Node::setPosition(unsigned int node, const float x, const float y, const float z) {
  nodeData[node].position.x = x;
  nodeData[node].position.y = y;
  nodeData[node].position.z = z;
  alertChildsModelWorldChanged(node);
}

glm::vec3 ROTOM::Node::position(unsigned int node) {
  return nodeData[node].position;
}

void ROTOM::Node::setPositionX(unsigned int node, const float positionX) {
  nodeData[node].position.x = positionX;
  setPosition(node, positionX, nodeData[node].position.y, nodeData[node].position.z);
}

float ROTOM::Node::positionX(unsigned int node) {
  return nodeData[node].position.x;
}

void ROTOM::Node::setPositionY(unsigned int node, const float positionY) {
  setPosition(node, nodeData[node].position.x, positionY, nodeData[node].position.z);
}

float ROTOM::Node::positionY(unsigned int node) {
  return nodeData[node].position.y;
}

void ROTOM::Node::setPositionZ(unsigned int node, const float positionZ) {
  setPosition(node, nodeData[node].position.x, nodeData[node].position.y, positionZ);
}

float ROTOM::Node::positionZ(unsigned int node) {
  return nodeData[node].position.z;
}

void ROTOM::Node::setRotation(unsigned int node, const float rotation[3]) {
  setRotation(node, rotation[0], rotation[1], rotation[2]);
}

void ROTOM::Node::setRotation(unsigned int node, const float x, const float y, const float z) {
  nodeData[node].rotation.x = x;
  nodeData[node].rotation.y = y;
  nodeData[node].rotation.z = z;
  alertChildsModelWorldChanged(node);
}

glm::vec3 ROTOM::Node::rotation(unsigned int node) {
  return nodeData[node].rotation;
}

void ROTOM::Node::setRotationX(unsigned int node, const float rotationX) {
  setRotation(node, rotationX, nodeData[node].rotation.y, nodeData[node].rotation.z);
}

float ROTOM::Node::rotationX(unsigned int node) {
  return nodeData[node].rotation.x;
}

void ROTOM::Node::setRotationY(unsigned int node, const float rotationY) {
  setRotation(node, nodeData[node].rotation.x, rotationY, nodeData[node].rotation.z);
}

float ROTOM::Node::rotationY(unsigned int node) {
  return nodeData[node].rotation.y;
}

void ROTOM::Node::setRotationZ(unsigned int node, const float rotationZ) {
  setRotation(node, nodeData[node].rotation.x, nodeData[node].rotation.y, rotationZ);
}

float ROTOM::Node::rotationZ(unsigned int node) {
  return nodeData[node].rotation.z;
}

void ROTOM::Node::setScale(unsigned int node, const float scale[3]) {
  setScale(node, scale[0], scale[1], scale[2]);
}

void ROTOM::Node::setScale(unsigned int node, const float x, const float y, const float z) {
  nodeData[node].scale.x = x;
  nodeData[node].scale.y = y;
  nodeData[node].scale.z = z;
  alertChildsModelWorldChanged(node);
}

glm::vec3 ROTOM::Node::scale(unsigned int node) {
  return nodeData[node].scale;
}

void ROTOM::Node::setScaleX(unsigned int node, const float scaleX) {
  setScale(node, scaleX, nodeData[node].scale.y, nodeData[node].scale.z);
}

float ROTOM::Node::scaleX(unsigned int node) {
  return nodeData[node].scale.x;
}

void ROTOM::Node::setScaleY(unsigned int node, const float scaleY) {
  setScale(node, nodeData[node].scale.x, scaleY, nodeData[node].scale.z);
}

float ROTOM::Node::scaleY(unsigned int node) {
  return nodeData[node].scale.y;
}

void ROTOM::Node::setScaleZ(unsigned int node, const float scaleZ) {
  setScale(node, nodeData[node].scale.x, nodeData[node].scale.y, scaleZ);
}

float ROTOM::Node::scaleZ(unsigned int node) {
  return nodeData[node].scale.z;
}

void ROTOM::Node::setModelLocal(unsigned int node, glm::mat4 modelLocal) {
  nodeData[node].modelLocal = modelLocal;
  nodeData[node].dirtyModelLocal = false;
  nodeData[node].dirtyModelWorld = true;
}

glm::mat4 *ROTOM::Node::modelLocal(unsigned int node) {
  return &nodeData[node].modelLocal;
}

bool ROTOM::Node::isDirtyModelLocal(unsigned int node) {
  return nodeData[node].dirtyModelLocal;
}

void ROTOM::Node::setModelWorld(unsigned int node, glm::mat4 modelWorld) {
  nodeData[node].modelWorld = modelWorld;
  nodeData[node].dirtyModelWorld = false;
}

glm::mat4 *ROTOM::Node::modelWorld(unsigned int node) {
  return &nodeData[node].modelWorld;
}

bool ROTOM::Node::isDirtyModelWorld(unsigned int node) {
  return nodeData[node].dirtyModelWorld;
}

void ROTOM::Node::setParent(unsigned int node, unsigned int parent) {
  //TODO - Para que al attacharle un nuevo padre no se teletransporte [La inversa del padre nuevo] * [tu matriz world]
  nodeData[node].modelLocal = glm::inverse(nodeData[nodeData[node].parent].modelWorld) * nodeData[node].modelWorld;

  glm::quat rotation;
  glm::vec3 skew;
  glm::vec4 perspective;
  glm::decompose(nodeData[node].modelLocal, nodeData[node].scale, rotation, nodeData[node].position, skew, perspective);
  nodeData[node].rotation = glm::vec3(*glm::value_ptr(rotation)); //TODO - Change the variable type of rotation to glm::quat
  nodeData[node].rotation.x = glm::degrees(rotation.x);
  nodeData[node].rotation.y = glm::degrees(rotation.y);
  nodeData[node].rotation.z = glm::degrees(rotation.z);

  if (nodeData[node].parent != -1) {
    removeChild(nodeData[node].parent, node);
  }
  nodeData[node].parent = parent;
  addChild(nodeData[node].parent, node);

  nodeData[node].dirtyModelWorld = true;

  nodeData[node].modelWorld = nodeData[nodeData[node].parent].modelWorld * nodeData[node].modelLocal;
}

unsigned int ROTOM::Node::parent(unsigned int node) {
  return nodeData[node].parent;
}

void ROTOM::Node::addChild(unsigned int node, unsigned int child) {
  nodeData[node].childs.push_back(child);
  if (nodeData[child].parent != node) {
    setParent(child, node);
  }
}

void ROTOM::Node::removeChild(unsigned int node, unsigned int child) {
  for (unsigned int i = 0; i < nodeData[node].childs.size(); ++i) {
    if (child == nodeData[node].childs.at(i)) {
      nodeData[node].childs.erase(nodeData[node].childs.begin() + i);
    }
  }
}

unsigned int ROTOM::Node::getChildAt(unsigned int node, unsigned int i) {
  return nodeData[node].childs.at(i);
}

const unsigned int ROTOM::Node::childCount(unsigned int node) {
  return nodeData[node].childs.size();
}

void ROTOM::Node::setGeometry(unsigned int node, std::shared_ptr<Geometry> geometry) {
  nodeData[node].geometry = geometry;
}

std::shared_ptr<ROTOM::Geometry> ROTOM::Node::geometry(unsigned int node) {
  return nodeData[node].geometry;
}

void ROTOM::Node::setMaterial(unsigned int node, std::shared_ptr<Material> material) {
  nodeData[node].material = material;
}

std::shared_ptr<ROTOM::Material> ROTOM::Node::material(unsigned int node) {
  return nodeData[node].material;
}

void ROTOM::Node::setMaterialSettings(unsigned int node, std::shared_ptr<MaterialSettings> materialSettings) {
  nodeData[node].materialSettings = materialSettings;
}

std::shared_ptr<ROTOM::MaterialSettings> ROTOM::Node::materialSettings(unsigned int node) {
  return nodeData[node].materialSettings;
}

void ROTOM::Node::alertChildsModelWorldChanged(unsigned int node) {
  if (!nodeData[node].dirtyModelLocal) {
    nodeData[node].dirtyModelLocal = true;
    for (unsigned int i = 0; i < nodeData[node].childs.size(); ++i) {
      nodeData[nodeData[node].childs.at(i)].dirtyModelWorld = true;
    }
  }
}