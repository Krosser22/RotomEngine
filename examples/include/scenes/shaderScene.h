/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __SHADER_SCENE_H__
#define __SHADER_SCENE_H__

#include "general/scene.h"

namespace ROTOM {
  class ShaderScene : public Scene {
  public:
    ShaderScene() {};
    ~ShaderScene() {};

    void init();

    void input();

    void update();

    void draw() {};

    void postDraw() {};

    void destroy() {};
    
  private:
    std::shared_ptr<Geometry> geometry_;
  };
}

#endif //__SHADER_SCENE_H__