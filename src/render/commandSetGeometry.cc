/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "render/commandSetGeometry.h"
#include "render/graphics.h"

ROTOM::CommandSetGeometry::CommandSetGeometry() {}

ROTOM::CommandSetGeometry::~CommandSetGeometry() {}

void ROTOM::CommandSetGeometry::run() {
  GRAPHICS::releaseGeometry(geometry_->VAO(), geometry_->EBO(), geometry_->VBO());
  geometry_->setVertexCount(geometryData_->data.size() / 8);
  //loadGeometry(&geometryData_->get()->data[0], &geometryData->get()->index[0], geometryData->get()->data.size() / 8);

  GRAPHICS::loadGeometry(&geometry_->VAO(), &geometry_->EBO(), &geometry_->VBO(), sizeof(float) * numberOfElementsPerVertex_, vertexCount_, vertex, index);
}

void ROTOM::CommandSetGeometry::setInput(std::shared_ptr<Geometry::GeometryData> geometryData, Geometry *geometry) {
  geometryData_ = geometryData;
  geometry_ = geometry;
}
