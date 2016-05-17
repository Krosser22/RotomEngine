/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/sceneManager.h"
#include "general/window.h"

ROTOM::Scene *actualScene;
ROTOM::Scene *nextScene;
bool sceneChanged = true;

void ROTOM::StartSceneManager(Scene *newScene) {
  nextScene = newScene;
  actualScene = newScene;
  SetScene(newScene);

  while (WindowIsOpened()) {
    if (sceneChanged) {
      SetScene(nextScene);
      sceneChanged = false;
    }
    actualScene = nextScene;
  }
}

void ROTOM::ChangeScene(Scene *newScene) {
  nextScene = newScene;
  sceneChanged = true;
}