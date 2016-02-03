/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "drawable.h"
#include "security.h"

ROTOM::Drawable::Drawable() {
  SECURITY::addSecurityCount(SECURITY::MyClass_Drawable);

  geometry_ = NULL;
  material_ = NULL;
}

ROTOM::Drawable::Drawable(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material, Node *parent) {
  SECURITY::addSecurityCount(SECURITY::MyClass_Drawable);

  setGeometry(geometry);
  setMaterial(material);
  setParent(parent);
}

ROTOM::Drawable::~Drawable() {
  SECURITY::removeSecurityCount(SECURITY::MyClass_Drawable);
}

void ROTOM::Drawable::setGeometry(std::shared_ptr<Geometry> geometry) {
  geometry_ = geometry;
}

std::shared_ptr<ROTOM::Geometry> ROTOM::Drawable::geometry() {
  return geometry_;
}

void ROTOM::Drawable::setMaterial(std::shared_ptr<Material> material) {
  material_ = material;
}

std::shared_ptr<ROTOM::Material> ROTOM::Drawable::material() {
  return material_;
}