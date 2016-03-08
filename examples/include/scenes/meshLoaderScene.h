/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __MESH_LOADER_SCENE_H__
#define __MESH_LOADER_SCENE_H__

#include "general/scene.h"
#include <memory>

namespace ROTOM {
  class MeshLoaderScene : public ROTOM::Scene {
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
  };
}

#endif //__MESH_LOADER_SCENE_H__