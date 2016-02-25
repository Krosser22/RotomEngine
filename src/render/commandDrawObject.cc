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

void ROTOM::CommandDrawObject::setInput(std::shared_ptr<Node> root, Light light, float projectionMatrix[16], float viewMatrix[16]) {
  light_ = light;
  for (int i = 0; i < 16; ++i) {
    projectionMatrix_[i] = projectionMatrix[i];
    viewMatrix_[i] = viewMatrix[i];
  }
  commandDrawObjectData_.clear();
  setInputChilds(root.get());
}

void ROTOM::CommandDrawObject::setData(Drawable *node) {
  CommandDrawObjectData commandDrawObjectData;
  commandDrawObjectData.materialSettings = *node->materialSettings().get();
  commandDrawObjectData.shaderData = node->material()->shaderData_;
  commandDrawObjectData.geometry_VAO = node->geometry()->VAO();
  commandDrawObjectData.geometry_veterCount = node->geometry()->vertexCount();
  commandDrawObjectData.material_texture = node->material()->texture();
  commandDrawObjectData.material_shininess = node->material()->materialData_.shininess_;
  commandDrawObjectData.material_specularMaterial[0] = node->material()->materialData_.specularMaterial_[0];
  commandDrawObjectData.material_specularMaterial[1] = node->material()->materialData_.specularMaterial_[1];
  commandDrawObjectData.material_specularMaterial[2] = node->material()->materialData_.specularMaterial_[2];
  commandDrawObjectData.material_specularMaterial[3] = node->material()->materialData_.specularMaterial_[3];
  float *modelWorld = glm::value_ptr(*node->modelWorld());
  for (int i = 0; i < 16; ++i) {
    commandDrawObjectData.drawable_modelWorld[i] = modelWorld[i];
  }
  commandDrawObjectData_.push_back(commandDrawObjectData);
  setInputChilds(node);
}

void ROTOM::CommandDrawObject::setInputChilds(Node *node) {
  for (unsigned int i = 0; i < node->childCount(); ++i) {
    setData((Drawable *)&node->getChildAt(i));
  }
}