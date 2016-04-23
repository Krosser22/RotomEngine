/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "taskManager/taskSetGeometry.h"
#include "general/meshLoader.h"

ROTOM::TaskSetGeometry::TaskSetGeometry() {}

ROTOM::TaskSetGeometry::~TaskSetGeometry() {}

void ROTOM::TaskSetGeometry::run() {
  MESHLOADER::Load_OBJ(path_, geometry_, false);
}

void ROTOM::TaskSetGeometry::setInput(const char *path, Geometry *geometry) {
  path_ = (char *)path;
  geometry_ = geometry;
}
