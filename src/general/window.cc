/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/window.h"
#include "general/hud.h"
#include "general/input.h"
#include "render/graphics.h"
#include "taskManager/taskCalculateMatrix.h"
#include "taskManager/taskManager.h"

static ROTOM::CommandDrawObject commandDrawObject;
static ROTOM::DisplayList displayList;
static ROTOM::TaskCalculateMatrix taskCalculateNodesMatrix;
static ROTOM::Scene *scene;

void ROTOM::WindowInit(unsigned int width, unsigned int height) {
  GRAPHICS::windowInit(width, height);
}

bool WindowIsOpened() {
  if (!ROTOM::GRAPHICS::windowShouldClose()) {
    //Input
    ROTOM::INPUT::Update();

    //Clear Screen
    ROTOM::GRAPHICS::clear();

    //Update TaskManager
    taskCalculateNodesMatrix.setInput(scene->getRoot().get());
    ROTOM::TASKMANAGER::addTask(&taskCalculateNodesMatrix);

    //Update Scene
    //assert(scene);
    scene->input();
    scene->update();
    scene->draw();

    //Render from the camera perspective
    ROTOM::RenderScene(scene->getCamera()->projectionMatrix(), scene->getCamera()->viewMatrix());

    //Render HUD
    ROTOM::HUD::Draw();

    ROTOM::GRAPHICS::swapBuffers();
    return true;
  }
  return false;
}

void ROTOM::WindowDestroy() {
  ROTOM::GRAPHICS::windowDestroy();
}

int ROTOM::WindowWidth() {
  return GRAPHICS::screenWidth();
}

int ROTOM::WindowHeight() {
  return GRAPHICS::screenHeight();
}

void ROTOM::SetScene(Scene *newScene) {
  if (scene != nullptr) {
    scene->destroy();
  }
  scene = newScene;
  scene->setRoot(std::shared_ptr<Node>(new Node("Root")));
  scene->init();
  HUD::Init(scene->getRoot(), scene->getLight(), scene->getCamera());
  while (WindowIsOpened()) { ; }
  scene->destroy();
  scene = nullptr;
}

void ROTOM::RenderScene(float *projectionMatrix, float *viewMatrix) {
  commandDrawObject.setInput(scene->getRoot(), scene->getLight(), projectionMatrix, viewMatrix);
  displayList.addCommand(&commandDrawObject);
  displayList.draw();
}

ROTOM::DisplayList *ROTOM::GetActualDisplayList() {
  return &displayList;
}