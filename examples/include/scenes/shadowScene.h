/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __SHADOW_SCENE_H__
#define __SHADOW_SCENE_H__

#include "general/scene.h"
#include "render/renderTarget.h"

namespace ROTOM {
  class ShadowScene : public Scene {
  public:
    ShadowScene() {};
    ~ShadowScene() {};

    void init();

    void input();

    void update();

    void draw();

    void postDraw();

    void destroy() {};
    
  private:
    RenderTarget renderTarget_;
  };
}

#endif //__SHADOW_SCENE_H__