/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __PROCEDURAL_SCENE_H__
#define __PROCEDURAL_SCENE_H__

#include "general/scene.h"
#include "node/chunk.h"

namespace ROTOM {
  class ProceduralScene : public Scene {
  public:
    ProceduralScene() {};
    ~ProceduralScene() {};

    void init();

    void input();

    void update();

    void draw();

    void destroy() {};
    
  private:
    std::shared_ptr<Chunk> chunk_;
  };
}

#endif //__PROCEDURAL_SCENE_H__