/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/drawable.h"
#include "render/graphics.h"

ROTOM::Drawable::Drawable() {
  type_ = kNodeType_Drawable;
  setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings()));
  visible_ = true;
  shadows_ = true;
}

ROTOM::Drawable::Drawable(char *name) {
  type_ = kNodeType_Drawable;
  name_ = name;
  setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings()));
  visible_ = true;
  shadows_ = true;
}

ROTOM::Drawable::~Drawable() {}

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

void ROTOM::Drawable::setMaterialSettings(std::shared_ptr<MaterialSettings> materialSettings) {
  materialSettings_ = materialSettings;
}

std::shared_ptr<ROTOM::MaterialSettings> ROTOM::Drawable::materialSettings() {
  return materialSettings_;
}