/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "taskManager/taskSetGeometry.h"
#include "meshLoader.h"

ROTOM::TaskSetGeometry::TaskSetGeometry() {}

ROTOM::TaskSetGeometry::~TaskSetGeometry() {}

void ROTOM::TaskSetGeometry::run() {
  MESHLOADER::Load_OBJ(nameWithoutExtension_, geometry_);

  //std::shared_ptr<Geometry::GeometryData> obj_data = std::shared_ptr<Geometry::GeometryData>(new Geometry::GeometryData);
  //ROTOM::MESHLOADER::Load_OBJ(kPath_objFiles, nameWithoutExtension_, obj_data);
}

void ROTOM::TaskSetGeometry::setInput(const char *nameWithoutExtension, Geometry *geometry) {
  nameWithoutExtension_ = (char *)nameWithoutExtension;
  geometry_ = geometry;
}
