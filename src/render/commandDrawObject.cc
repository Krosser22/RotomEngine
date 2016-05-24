/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "render/commandDrawObject.h"
#include "render/graphics.h"

ROTOM::CommandDrawObject::CommandDrawObject() {}

ROTOM::CommandDrawObject::~CommandDrawObject() {}

void ROTOM::CommandDrawObject::run() {
  for (unsigned int i = 0; i < commandDrawObjectData_.size(); ++i) {
    GRAPHICS::drawObject(&commandDrawObjectData_.at(i), &lights_, projectionMatrix_, viewMatrix_, viewPosition_);
  }
}

void ROTOM::CommandDrawObject::setInput(std::shared_ptr<Node> root, std::vector<std::shared_ptr<DirectionalLight>> lights, float projectionMatrix[16], float viewMatrix[16], float *viewPosition) {
  lights_ = lights;
  for (int i = 0; i < 16; ++i) {
    projectionMatrix_[i] = projectionMatrix[i];
    viewMatrix_[i] = viewMatrix[i];
  }
  for (int i = 0; i < 3; ++i) {
    viewPosition_[i] = viewPosition[i];
  }
  commandDrawObjectData_.clear();
  setInputChilds((Drawable *)root.get());
}

void ROTOM::CommandDrawObject::setData(Drawable *drawable) {
  CommandDrawObjectData commandDrawObjectData;
  Material *material = drawable->material().get();
  Geometry *geometry = drawable->geometry().get();
  commandDrawObjectData.visible = drawable->visible_;
  commandDrawObjectData.shadows = drawable->shadows_;
  commandDrawObjectData.materialSettings = *drawable->materialSettings().get();
  commandDrawObjectData.shaderData = material->shaderData_;
  commandDrawObjectData.geometry_VAO = *geometry->VAO();
  commandDrawObjectData.geometry_veterCount = geometry->vertexCount();
  commandDrawObjectData.material_texture = material->texture();
  commandDrawObjectData.materialData = material->materialData_;
  float *worldMatrix = glm::value_ptr(*drawable->worldMatrix());
  for (int i = 0; i < 16; ++i) {
    commandDrawObjectData.drawable_worldMatrix[i] = worldMatrix[i];
  }
  commandDrawObjectData_.push_back(commandDrawObjectData);
  setInputChilds(drawable);
}

void ROTOM::CommandDrawObject::setInputChilds(Drawable *drawable) {
  for (unsigned int i = 0; i < drawable->childCount(); ++i) {
    setData((Drawable *)drawable->getChildAt(i).get());
  }
}