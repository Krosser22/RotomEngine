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
  for (unsigned int i = 0; i < root_->childCount(); ++i) {
    draw(root_->getChildAt(i).get());
  }
}

void ROTOM::CommandDrawObject::setInput(Node *root, Light light, float projectionMatrix[16], float viewMatrix[16]) {
  root_ = root;
  light_ = light;
  for (int i = 0; i < 16; ++i) {
    projectionMatrix_[i] = projectionMatrix[i];
    viewMatrix_[i] = viewMatrix[i];
  }
  setInputChilds(root_);
}

void ROTOM::CommandDrawObject::draw(Node *node) {
  GRAPHICS::drawMaterial((Drawable *)node, light_, projectionMatrix_, viewMatrix_);
  drawChilds(node);
}

void ROTOM::CommandDrawObject::drawChilds(Node *node) {
  for (unsigned int i = 0; i < node->childCount(); ++i) {
    draw(node->getChildAt(i).get());
  }
}

void ROTOM::CommandDrawObject::setInput(Node *node) {
  CommandDrawObjectData commandDrawObjectData;

  -----------llenar estas variables con los datos
  MaterialSettings materialSettings;
  unsigned int geometry_VAO;
  unsigned int geometry_veterCount;
  float drawable_modelWorld[16];
  ShaderData shaderData;
  float material_shininess_;
  float material_specularMaterial_[4];

  commandDrawObjectData_.push_back(commandDrawObjectData);
  setInput(node);
}

void ROTOM::CommandDrawObject::setInputChilds(Node *node) {
  for (unsigned int i = 0; i < node->childCount(); ++i) {
    setInput(node->getChildAt(i).get());
  }
}