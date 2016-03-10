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
  MESHLOADER::Load_OBJ(path_, geometry_, false);
  //if (hud.contentListName.at(i).find("\\") != -1) {
  //MESHLOADER::Load_OBJ(path, this);
  /*} else {
  MESHLOADER::Load_OBJ(kPath_objFiles, hud.contentListName.at(i).c_str(), geometry);
  }*/

  //std::shared_ptr<Geometry::GeometryData> obj_data = std::shared_ptr<Geometry::GeometryData>(new Geometry::GeometryData);
  //ROTOM::MESHLOADER::Load_OBJ(kPath_objFiles, nameWithoutExtension_, obj_data);
}

void ROTOM::TaskSetGeometry::setInput(const char *path, Geometry *geometry) {
  path_ = (char *)path;
  geometry_ = geometry;
}
