/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "render/commandDrawObject.h"
#include "render/graphics.h"

ROTOM::CommandDrawObject::CommandDrawObject() {}

ROTOM::CommandDrawObject::~CommandDrawObject() {}

void ROTOM::CommandDrawObject::run() {
  for (unsigned int i = 0; i < commandDrawObjectData_.size(); ++i) {
    GRAPHICS::drawMaterial(&commandDrawObjectData_.at(i), &light_, projectionMatrix_, viewMatrix_);
  }
}

void ROTOM::CommandDrawObject::setInput(unsigned int root, Light light, float projectionMatrix[16], float viewMatrix[16]) {
  light_ = light;
  for (int i = 0; i < 16; ++i) {
    projectionMatrix_[i] = projectionMatrix[i];
    viewMatrix_[i] = viewMatrix[i];
  }
  commandDrawObjectData_.clear();
  setInputChilds(root);
}

void ROTOM::CommandDrawObject::setData(unsigned int node) {
  CommandDrawObjectData commandDrawObjectData;
  commandDrawObjectData.materialSettings = *nodeData[node].materialSettings.get();
  commandDrawObjectData.shaderData = nodeData[node].material->shaderData_;
  commandDrawObjectData.geometry_VAO = nodeData[node].geometry->VAO();
  commandDrawObjectData.geometry_veterCount = nodeData[node].geometry->vertexCount();
  commandDrawObjectData.material_texture = nodeData[node].material->texture();
  commandDrawObjectData.material_shininess = nodeData[node].material->materialData_.shininess_;
  commandDrawObjectData.material_specularMaterial[0] = nodeData[node].material->materialData_.specularMaterial_[0];
  commandDrawObjectData.material_specularMaterial[1] = nodeData[node].material->materialData_.specularMaterial_[1];
  commandDrawObjectData.material_specularMaterial[2] = nodeData[node].material->materialData_.specularMaterial_[2];
  commandDrawObjectData.material_specularMaterial[3] = nodeData[node].material->materialData_.specularMaterial_[3];
  float *modelWorld = glm::value_ptr(nodeData[node].modelWorld);
  for (int i = 0; i < 16; ++i) {
    commandDrawObjectData.drawable_modelWorld[i] = modelWorld[i];
  }
  commandDrawObjectData_.push_back(commandDrawObjectData);
  setInputChilds(node);
}

void ROTOM::CommandDrawObject::setInputChilds(unsigned int node) {
  for (unsigned int i = 0; i < nodeData[node].childs.size(); ++i) {
    setData(nodeData[node].childs.at(i));
  }
}