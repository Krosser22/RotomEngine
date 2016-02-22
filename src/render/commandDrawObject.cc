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
    draw((Drawable *)root_->getChildAt(i).get());
  }
}

void ROTOM::CommandDrawObject::setRoot(Node *root) {
  root_ = root;
}

void ROTOM::CommandDrawObject::setProjectionMatrix(float *projectionMatrix) {
  projectionMatrix_ = projectionMatrix;
}

void ROTOM::CommandDrawObject::setViewMatrix(float *viewMatrix) {
  viewMatrix_ = viewMatrix;
}

void ROTOM::CommandDrawObject::setLight(Light *light) {
  light_ = light;
}

void ROTOM::CommandDrawObject::draw(Drawable *drawable) {
  GRAPHICS::drawMaterial(drawable, projectionMatrix_, viewMatrix_, light_);
  drawChilds(drawable);
}

void ROTOM::CommandDrawObject::drawChilds(Drawable *drawable) {
  for (unsigned int i = 0; i < drawable->childCount(); ++i) {
    draw((Drawable *)drawable->getChildAt(i).get());
  }
}