/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __RENDER_TO_TEXTURE_SCENE_H__
#define __RENDER_TO_TEXTURE_SCENE_H__

#include "general/scene.h"
#include "render/renderTarget.h"

namespace ROTOM {
  class RenderToTextureScene : public Scene {
  public:
    RenderToTextureScene() {};
    ~RenderToTextureScene() {};

    void init();

    void input();

    void update();

    void draw();

    void destroy() {};
    
  private:
    std::shared_ptr<Geometry> geometry_;
    RenderTarget renderTarget_;
  };
}

#endif //__RENDER_TO_TEXTURE_SCENE_H__