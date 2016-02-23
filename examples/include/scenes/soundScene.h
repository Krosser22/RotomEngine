/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __SOUND_SCENE_H__
#define __SOUND_SCENE_H__

#include "general/scene.h"

namespace ROTOM {
  class SoundScene : public ROTOM::Scene {
  public:
    SoundScene() {};
    ~SoundScene() {};

    void init();

    void input() {};

    void update() {};

    void draw();

    void destroy() {};
  };
}

#endif //__DEFAULT_SCENE_H__