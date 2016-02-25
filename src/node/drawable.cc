/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "node/drawable.h"
#include "render/graphics.h"

ROTOM::Drawable::Drawable() {
  drawableID_ = nextDrawableID++;
  assert("ERROR: Too many Drawables created" && drawableID_ < kNodeDataAmount);

  drawableData[drawableID_].geometry = NULL;
  drawableData[drawableID_].material = NULL;
  setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings()));
}

ROTOM::Drawable::Drawable(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material, unsigned int parent) {
  setGeometry(geometry);
  setMaterial(material);
  setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings()));
  setParent(parent);
}

ROTOM::Drawable::~Drawable() {
  // Properly de-allocate all resources once they've outlived their purpose
  GRAPHICS::releaseMaterial(drawableData[drawableID_].material->shaderData_.shaderProgram);
}

unsigned int ROTOM::Drawable::drawableID() {
  return drawableID_;
}

void ROTOM::Drawable::setGeometry(std::shared_ptr<Geometry> geometry) {
  drawableData[drawableID_].geometry = geometry;
}

std::shared_ptr<ROTOM::Geometry> ROTOM::Drawable::geometry() {
  return drawableData[drawableID_].geometry;
}

void ROTOM::Drawable::setMaterial(std::shared_ptr<Material> material) {
  drawableData[drawableID_].material = material;
}

std::shared_ptr<ROTOM::Material> ROTOM::Drawable::material() {
  return drawableData[drawableID_].material;
}

void ROTOM::Drawable::setMaterialSettings(std::shared_ptr<MaterialSettings> materialSettings) {
  drawableData[drawableID_].materialSettings = materialSettings;
}

std::shared_ptr<ROTOM::MaterialSettings> ROTOM::Drawable::materialSettings() {
  return drawableData[drawableID_].materialSettings;
}