/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __MESH_LOADER_SCENE_H__
#define __MESH_LOADER_SCENE_H__

#include "scene.h"
#include "drawable.h"
#include <memory>

namespace ROTOM {
  class MeshLoaderScene : public ROTOM::Scene {
  public:
    MeshLoaderScene() {};
    ~MeshLoaderScene() {};

    void init();

    void input();

    void update();

    void draw();

    void destroy() {};
    
    std::shared_ptr<Geometry> geometry;

  private:
    void moveCamera(char key);

    void rotateCamera();

    void updateCamera();
  };
}

#endif //__MESH_LOADER_SCENE_H__