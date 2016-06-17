/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __DEMO_SCENE_H__
#define __DEMO_SCENE_H__

#include "general/scene.h"
#include "render/renderTarget.h"
#include "render/cubemap.h"
#include "general/sound.h"

namespace ROTOM {
  class DemoScene : public Scene {
  public:
    DemoScene() {};
    ~DemoScene() {};

    void init();

    void input();

    void update();

    void draw();

    void postDraw();

    void destroy();
    
  private:
    std::shared_ptr<Geometry> geometry_;
    std::shared_ptr<Geometry> geometryMutable_;
    std::shared_ptr<Geometry> geometryHUD_;

    std::shared_ptr<Material> material_renderColorToTexture_;
    
    Cubemap cubemap_;

    RenderTarget renderTarget_;

    RenderTarget postProcess_;

    //Basics
    std::shared_ptr<Drawable> drawable_color_;
    std::shared_ptr<Drawable> drawable_texture_;
    std::shared_ptr<Drawable> drawable_diffuseLight_;
    std::shared_ptr<Drawable> drawable_specularLight_;
    std::shared_ptr<Drawable> drawable_Blinn_Phong_;

    //Shadows and lights
    std::shared_ptr<Drawable> drawable_shadow_;
    std::shared_ptr<Drawable> drawable_multipleLights_;

    //Others
    std::shared_ptr<Drawable> drawable_depth_;
    std::shared_ptr<Drawable> drawable_reflect_;
    std::shared_ptr<Drawable> drawable_refract_;
    std::shared_ptr<Drawable> drawable_renderToDepth_;
    std::shared_ptr<Drawable> drawable_screenTexture_;

    //Wall
    std::shared_ptr<Drawable> drawable_wall_;

    //Sound
    SOUND::Sound *sound_;
  };
}

#endif //__DEMO_SCENE_H__