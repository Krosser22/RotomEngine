/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "scene.h"

namespace ROTOM {
  void StartSceneManager(Scene *newScene);

  void ChangeScene(Scene *newScene);
}

#endif //__SCENE_MANAGER_H__