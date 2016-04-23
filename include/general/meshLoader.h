/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __MESH_LOADER_H__
#define __MESH_LOADER_H__

#include "node/geometry.h"

namespace ROTOM {
  namespace MESHLOADER {
    //Use this just for testing because it load faster the obj file but it will not be optimized
    void Load_OBJ(const char *pathWithoutExtensionFile, Geometry *geometry, bool reloadFile = true);
    
    //Recomended
    void Load_OBJ(const char* path, const char* nameWithoutExtension, Geometry *geometry, bool reloadFile = true);

    void Load_ROTOM_OBJ(const char *path, std::shared_ptr<Geometry::GeometryData> obj_data);

    void Save_ROTOM_OBJ(const char *path, std::shared_ptr<Geometry::GeometryData> obj_data);
  }
}

#endif //__MESH_LOADER_H__