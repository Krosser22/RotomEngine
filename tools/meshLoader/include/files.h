/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __FILES_H__
#define __FILES_H__

#include "geometry.h"

namespace ROTOM {
  namespace FILES {
    void Load_file(const char *path, std::shared_ptr<char[]> source);

    //Use this just for testing because it load faster the obj file but it will not be optimized
    void Load_OBJ(const char *pathWithoutExtensionFile, std::shared_ptr<Geometry::GeometryData> obj_data, bool reloadFile = true);

    //Recomended
    void Load_OBJ(const char* basePath, const char* nameWithoutExtension, std::shared_ptr<Geometry::GeometryData> obj_data, bool reloadFile = true);

    void Load_ROTOM_OBJ(const char *path, std::shared_ptr<ROTOM::Geometry::GeometryData> obj_data);

    void Save_ROTOM_OBJ(const char *path, ROTOM::Geometry::GeometryData *obj_data);
  }
}

#endif __FILES_H__