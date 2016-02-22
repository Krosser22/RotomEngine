/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "drawable.h"
#include "render/graphics.h"

ROTOM::Drawable::Drawable() {
  geometry_ = NULL;
  material_ = NULL;
  setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings()));
}

ROTOM::Drawable::Drawable(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material, std::shared_ptr<Node> parent) {
  setGeometry(geometry);
  setMaterial(material);
  setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings()));
  setParent(parent);
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