/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __SHADER_SCENE_H__
#define __SHADER_SCENE_H__

#include "general/scene.h"
#include <memory>

namespace ROTOM {
  class ShaderScene : public ROTOM::Scene {
  public:
    ShaderScene() {};
    ~ShaderScene() {};

    void init();

    void input() {};

    void update();

    void draw();

    void destroy() {};
    
  private:
    std::shared_ptr<Geometry> geometry_;
    std::shared_ptr<Drawable> drawableLight_;
  };
}

#endif //__SHADER_SCENE_H__