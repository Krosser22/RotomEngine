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
  std::string path = nameWithoutExtension_;
  MESHLOADER::Load_OBJ(path.c_str(), geometry_);

  //std::shared_ptr<Geometry::GeometryData> obj_data = std::shared_ptr<Geometry::GeometryData>(new Geometry::GeometryData);
  //ROTOM::MESHLOADER::Load_OBJ(kPath_objFiles, nameWithoutExtension_, obj_data);
  //geometry_->loadGeometry(&obj_data);
}

void ROTOM::TaskSetGeometry::setInput(const char *nameWithoutExtension, Geometry *geometry) {
  nameWithoutExtension_ = (char *)nameWithoutExtension;
  geometry_ = geometry;
}
