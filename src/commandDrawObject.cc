/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "commandDrawObject.h"
#include "security.h"
#include "graphics.h"

ROTOM::CommandDrawObject::CommandDrawObject() {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_CommandDrawObject);
}

ROTOM::CommandDrawObject::~CommandDrawObject() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_CommandDrawObject);
}

void ROTOM::CommandDrawObject::run() {
  for (unsigned int i = 0; i < root_->childCount(); ++i) {
    draw((Drawable *)root_->getChildAt(i));
  }
}

void ROTOM::CommandDrawObject::setRoot(Node *root) {
  root_ = root;
}

void ROTOM::CommandDrawObject::setProjectionMatrix(float *projectionMatrix) {
  projectionMatrix_ = projectionMatrix;
}

void ROTOM::CommandDrawObject::draw(Drawable *drawable) {
  GRAPHICS::useMaterial(&drawable->material()->shaderData_, drawable, projectionMatrix_);
  drawChilds(drawable);
}

void ROTOM::CommandDrawObject::drawChilds(Drawable *drawable) {
  for (unsigned int i = 0; i < drawable->childCount(); ++i) {
    draw((Drawable *)drawable->getChildAt(i));
  }
}