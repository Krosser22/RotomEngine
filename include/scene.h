/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __SCENE_H__
#define __SCENE_H__

#include "camera.h"
#include "light.h"
#include <vector>

namespace ROTOM {
  class Scene {
  public:
    Scene(); //Init
    ~Scene(); //Destroy

    void update();

    Camera camera_;
    Node root_;
    std::vector<Light> lights_;

  private:
    DisplayList displayList_;
    CommandDrawObject commandDrawObject_;
    std::shared_ptr<TaskCalculateMatrix> taskCalculateMatrix_;
  };
}

#endif //__CAMERA_H__