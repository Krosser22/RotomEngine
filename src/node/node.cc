/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "node/node.h"
#include "render/graphics.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"

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

ROTOM::Node::Node() {
  ID_ = nextNodeID++;
  assert("ERROR: Too many Nodes created" && ID_ < kNodeDataAmount);

  setPosition(0.0f, 0.0f, 0.0f);
  setRotation(0.0f, 0.0f, 0.0f);
  setScale(1.0f, 1.0f, 1.0f);

  nodeData[ID_].parent = -1; //TODO - Change this to 0 to set the root the 0 node of the array
  nodeData[ID_].geometry = NULL;
  nodeData[ID_].material = NULL;
  setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings()));
};

ROTOM::Node::~Node() {
  // Properly de-allocate all resources once they've outlived their purpose
  GRAPHICS::releaseMaterial(nodeData[ID_].material->shaderData_.shaderProgram);

  if (nodeData[ID_].parent != -1) {
    removeChild(nodeData[ID_].parent, ID_);
  }

  while (nodeData[ID_].childs.size() > 0) {
    //nodeData[ID_].childs.at(nodeData[ID_].childs.size() - 1)->~Node();
    nodeData[ID_].childs.pop_back();
  }
}

unsigned int ROTOM::Node::ID() {
  return ID_;
}

void ROTOM::Node::move(const float movement[3]) {
  setPosition(nodeData[ID_].position.x + movement[0], nodeData[ID_].position.y + movement[1], nodeData[ID_].position.z + movement[2]);
}

void ROTOM::Node::move(const float x, const float y, const float z) {
  setPosition(nodeData[ID_].position.x + x, nodeData[ID_].position.y + y, nodeData[ID_].position.z + z);
}

void ROTOM::Node::moveX(const float movementX) {
  setPosition(nodeData[ID_].position.x + movementX, nodeData[ID_].position.y, nodeData[ID_].position.z);
}

void ROTOM::Node::moveY(const float movementY) {
  setPosition(nodeData[ID_].position.x, nodeData[ID_].position.y + movementY, nodeData[ID_].position.z);
}

void ROTOM::Node::moveZ(const float movementZ) {
  setPosition(nodeData[ID_].position.x, nodeData[ID_].position.y, nodeData[ID_].position.z + movementZ);
}

void ROTOM::Node::setPosition(const float position[3]) {
  setPosition(position[0], position[1], position[2]);
}

void ROTOM::Node::setPosition(const float x, const float y, const float z) {
  nodeData[ID_].position.x = x;
  nodeData[ID_].position.y = y;
  nodeData[ID_].position.z = z;
  setModelLocalDirty();
}

glm::vec3 ROTOM::Node::position() {
  return nodeData[ID_].position;
}

void ROTOM::Node::setPositionX(const float positionX) {
  nodeData[ID_].position.x = positionX;
  setPosition(positionX, nodeData[ID_].position.y, nodeData[ID_].position.z);
}

float ROTOM::Node::positionX() {
  return nodeData[ID_].position.x;
}

void ROTOM::Node::setPositionY(const float positionY) {
  setPosition(nodeData[ID_].position.x, positionY, nodeData[ID_].position.z);
}

float ROTOM::Node::positionY() {
  return nodeData[ID_].position.y;
}

void ROTOM::Node::setPositionZ(const float positionZ) {
  setPosition(nodeData[ID_].position.x, nodeData[ID_].position.y, positionZ);
}

float ROTOM::Node::positionZ() {
  return nodeData[ID_].position.z;
}

void ROTOM::Node::setRotation(const float rotation[3]) {
  setRotation(rotation[0], rotation[1], rotation[2]);
}

void ROTOM::Node::setRotation(const float x, const float y, const float z) {
  nodeData[ID_].rotation.x = x;
  nodeData[ID_].rotation.y = y;
  nodeData[ID_].rotation.z = z;
  setModelLocalDirty();
}

glm::vec3 ROTOM::Node::rotation() {
  return nodeData[ID_].rotation;
}

void ROTOM::Node::setRotationX(const float rotationX) {
  setRotation(rotationX, nodeData[ID_].rotation.y, nodeData[ID_].rotation.z);
}

float ROTOM::Node::rotationX() {
  return nodeData[ID_].rotation.x;
}

void ROTOM::Node::setRotationY(const float rotationY) {
  setRotation(nodeData[ID_].rotation.x, rotationY, nodeData[ID_].rotation.z);
}

float ROTOM::Node::rotationY() {
  return nodeData[ID_].rotation.y;
}

void ROTOM::Node::setRotationZ(const float rotationZ) {
  setRotation(nodeData[ID_].rotation.x, nodeData[ID_].rotation.y, rotationZ);
}

float ROTOM::Node::rotationZ() {
  return nodeData[ID_].rotation.z;
}

void ROTOM::Node::setScale(const float scale[3]) {
  setScale(scale[0], scale[1], scale[2]);
}

void ROTOM::Node::setScale(const float x, const float y, const float z) {
  nodeData[ID_].scale.x = x;
  nodeData[ID_].scale.y = y;
  nodeData[ID_].scale.z = z;
  setModelLocalDirty();
}

glm::vec3 ROTOM::Node::scale() {
  return nodeData[ID_].scale;
}

void ROTOM::Node::setScaleX(const float scaleX) {
  setScale(scaleX, nodeData[ID_].scale.y, nodeData[ID_].scale.z);
}

float ROTOM::Node::scaleX() {
  return nodeData[ID_].scale.x;
}

void ROTOM::Node::setScaleY(const float scaleY) {
  setScale(nodeData[ID_].scale.x, scaleY, nodeData[ID_].scale.z);
}

float ROTOM::Node::scaleY() {
  return nodeData[ID_].scale.y;
}

void ROTOM::Node::setScaleZ(const float scaleZ) {
  setScale(nodeData[ID_].scale.x, nodeData[ID_].scale.y, scaleZ);
}

float ROTOM::Node::scaleZ() {
  return nodeData[ID_].scale.z;
}

void ROTOM::Node::setModelLocal(glm::mat4 modelLocal) {
  nodeData[ID_].modelLocal = modelLocal;
  nodeData[ID_].dirtyModelLocal = false;
  nodeData[ID_].dirtyModelWorld = true;
}

glm::mat4 *ROTOM::Node::modelLocal() {
  return &nodeData[ID_].modelLocal;
}

bool ROTOM::Node::isDirtyModelLocal() {
  return nodeData[ID_].dirtyModelLocal;
}

void ROTOM::Node::setModelWorld(glm::mat4 modelWorld) {
  nodeData[ID_].modelWorld = modelWorld;
  nodeData[ID_].dirtyModelWorld = false;
}

glm::mat4 *ROTOM::Node::modelWorld() {
  return &nodeData[ID_].modelWorld;
}

bool ROTOM::Node::isDirtyModelWorld() {
  return nodeData[ID_].dirtyModelWorld;
}

void ROTOM::Node::setParent(unsigned int parent) {
  setParent(ID_, parent);
}

unsigned int ROTOM::Node::parent() {
  return nodeData[ID_].parent;
}

void ROTOM::Node::addChild(unsigned int child) {
  addChild(ID_, child);
}

void ROTOM::Node::removeChild(unsigned int child) {
  removeChild(ID_, child);
}

unsigned int ROTOM::Node::getChildAt(unsigned int i) {
  return getChildAt(ID_, i);
}

const unsigned int ROTOM::Node::childCount() {
  return nodeData[ID_].childs.size();
}

void ROTOM::Node::setModelLocalDirty() {
  if (!nodeData[ID_].dirtyModelLocal) {
    alertChildsModelWorldChanged();
  }
}

void ROTOM::Node::alertChildsModelWorldChanged() {
  nodeData[ID_].dirtyModelLocal = true;
  for (unsigned int i = 0; i < nodeData[ID_].childs.size(); ++i) {
    nodeData[nodeData[ID_].childs.at(i)].dirtyModelWorld = true;
  }
}

void ROTOM::Node::setGeometry(std::shared_ptr<Geometry> geometry) {
  nodeData[ID_].geometry = geometry;
}

std::shared_ptr<ROTOM::Geometry> ROTOM::Node::geometry() {
  return nodeData[ID_].geometry;
}

void ROTOM::Node::setMaterial(std::shared_ptr<Material> material) {
  nodeData[ID_].material = material;
}

std::shared_ptr<ROTOM::Material> ROTOM::Node::material() {
  return nodeData[ID_].material;
}

void ROTOM::Node::setMaterialSettings(std::shared_ptr<MaterialSettings> materialSettings) {
  nodeData[ID_].materialSettings = materialSettings;
}

std::shared_ptr<ROTOM::MaterialSettings> ROTOM::Node::materialSettings() {
  return nodeData[ID_].materialSettings;
}