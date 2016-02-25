/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "node/drawable.h"
#include "render/graphics.h"

ROTOM::Drawable::Drawable() {
  setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings()));
}

ROTOM::Drawable::~Drawable() {
  // Properly de-allocate all resources once they've outlived their purpose
  GRAPHICS::releaseMaterial(material_->shaderData_.shaderProgram);
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

void ROTOM::Drawable::setMaterialSettings(std::shared_ptr<MaterialSettings> materialSettings) {
  materialSettings_ = materialSettings;
}

std::shared_ptr<ROTOM::MaterialSettings> ROTOM::Drawable::materialSettings() {
  return materialSettings_;
}