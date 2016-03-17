/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __MESH_LOADER_SCENE_H__
#define __MESH_LOADER_SCENE_H__

#include "general/scene.h"
#include "taskManager/taskSetGeometry.h"
#include "taskManager/taskManager.h"
#include <memory>

namespace ROTOM {
  class MeshLoaderScene : public Scene {
  public:
    MeshLoaderScene() {};
    ~MeshLoaderScene() {};

    void init();

    void input();

    void update();

    void draw() {};

    void destroy() {};

  private:
    bool rotating_;
    TaskSetGeometry taskSetGeometry_;
  };
}

#endif //__MESH_LOADER_SCENE_H__