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
    GRAPHICS::drawMaterial(&commandDrawObjectData_.at(i), &lights_, projectionMatrix_, viewMatrix_);
  }
}

void ROTOM::CommandDrawObject::setInput(std::shared_ptr<Node> root, std::vector<std::shared_ptr<Light>> lights, float projectionMatrix[16], float viewMatrix[16]) {
  lights_ = lights;
  for (int i = 0; i < 16; ++i) {
    projectionMatrix_[i] = projectionMatrix[i];
    viewMatrix_[i] = viewMatrix[i];
  }
  commandDrawObjectData_.clear();
  setInputChilds((Drawable *)root.get());
}

void ROTOM::CommandDrawObject::setData(Drawable *drawable) {
  CommandDrawObjectData commandDrawObjectData;
  Material *material = drawable->material().get();
  Geometry *geometry = drawable->geometry().get();
  commandDrawObjectData.materialSettings = *drawable->materialSettings().get();
  commandDrawObjectData.shaderData = material->shaderData_;
  commandDrawObjectData.geometry_VAO = *geometry->VAO();
  commandDrawObjectData.geometry_veterCount = geometry->vertexCount();
  commandDrawObjectData.material_texture = material->texture();
  commandDrawObjectData.materialData = material->materialData_;
  float *modelWorld = glm::value_ptr(*drawable->modelWorld());
  for (int i = 0; i < 16; ++i) {
    commandDrawObjectData.drawable_modelWorld[i] = modelWorld[i];
  }
  commandDrawObjectData_.push_back(commandDrawObjectData);
  setInputChilds(drawable);
}

void ROTOM::CommandDrawObject::setInputChilds(Drawable *drawable) {
  for (unsigned int i = 0; i < drawable->childCount(); ++i) {
    setData((Drawable *)drawable->getChildAt(i).get());
  }
}