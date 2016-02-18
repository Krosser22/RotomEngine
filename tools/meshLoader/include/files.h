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

    void Load_OBJ(const char* path, const char* basePath, ROTOM::Geometry::GeometryData *obj_data);

    void Load_OBJ2(const char* path, ROTOM::Geometry::GeometryData *obj_data);

    void Load_OBJ3(const char* path, const char* basePath, ROTOM::Geometry::GeometryData *obj_data);

    void Load_ROTOM_OBJ(const char *path, std::shared_ptr<ROTOM::Geometry::GeometryData> obj_data);

    void Save_ROTOM_OBJ(const char *path, ROTOM::Geometry::GeometryData *obj_data);
  }
}

#endif __FILES_H__