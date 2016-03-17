/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "render/commandSetGeometry.h"
#include "render/graphics.h"

ROTOM::CommandSetGeometry::CommandSetGeometry() {}

ROTOM::CommandSetGeometry::~CommandSetGeometry() {}

void ROTOM::CommandSetGeometry::run() {
  GRAPHICS::releaseGeometry(*geometry_->VAO(), *geometry_->EBO(), *geometry_->VBO());
  geometry_->setVertexCount(geometryData_->data.size() / 8);
  GRAPHICS::loadGeometry(geometry_->VAO(), geometry_->EBO(), geometry_->VBO(), sizeof(float) * geometry_->numberOfElementsPerVertex(), geometry_->vertexCount(), &geometryData_->data[0], &geometryData_->index[0]);
}

void ROTOM::CommandSetGeometry::setInput(std::shared_ptr<Geometry::GeometryData> geometryData, Geometry *geometry) {
  geometryData_ = geometryData;
  geometry_ = geometry;
}
