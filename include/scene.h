/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __SCENE_H__
#define __SCENE_H__

namespace ROTOM {
  class Scene {
  public:
    Scene() {};
    ~Scene() {};

    virtual void init() = 0 {};

    virtual void input() = 0 {};

    virtual void update() = 0 {};

    virtual void draw() = 0 {};

    virtual void destroy() = 0 {};
  };
}

#endif //__CAMERA_H__