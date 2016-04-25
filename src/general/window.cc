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
#include "taskManager/taskRender.h"
#include "taskManager/taskManager.h"

static ROTOM::CommandDrawObject commandDrawObject;
static ROTOM::DisplayList displayList;
ROTOM::Node cameraNode("CameraNode");
ROTOM::TaskRender taskRender;
ROTOM::TaskCalculateMatrix taskCalculateNodesMatrix;
ROTOM::TaskCalculateMatrix taskCalculateCameraMatrix;
static ROTOM::Scene *scene;

void ROTOM::WindowInit(unsigned int width, unsigned int height) {
  GRAPHICS::windowInit(width, height);

  taskCalculateNodesMatrix.nextTaskList_.push_back(&taskRender);
}

bool WindowIsOpened() {
  if (!ROTOM::GRAPHICS::windowShouldClose()) {
    //Input
    ROTOM::INPUT::Update();

    //Clear Screen
    ROTOM::GRAPHICS::clearScreen();

    //Update TaskManager
    taskCalculateNodesMatrix.setInput(scene->getRoot().get());
    taskCalculateCameraMatrix.setInput(&cameraNode);
    taskRender.setInput(&displayList);
    ROTOM::TASKMANAGER::addTask(&taskCalculateCameraMatrix);
    ROTOM::TASKMANAGER::addTask(&taskCalculateNodesMatrix);

    //Update Scene
    //assert(scene);
    scene->input();
    scene->update();
    scene->draw();

    //Light
    /*for (unsigned int i = 0; i < scene->getLight().size(); ++i) {
    updateDepthFromLight(scene->getLight().at(i).get());
    }*/

    //Render
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
  if (scene != NULL) {
    scene->destroy();
  }
  scene = newScene;
  scene->setRoot(std::shared_ptr<Node>(new Node("Root")));
  scene->init();
  HUD::Init(scene->getRoot(), scene->getLight(), scene->getCamera());
  while (WindowIsOpened()) {
    ;
  }
  WindowDestroy();
  scene->destroy();
}

void updateDepthFromLight(ROTOM::Light *light) {

}

void ROTOM::RenderScene(float *projectionMatrix, float *viewMatrix) {
  //DisplayList
  if (displayList.isValid_) {
    commandDrawObject.setInput(scene->getRoot(), scene->getLight(), projectionMatrix, viewMatrix);
    displayList.isValid_ = false;
  }
  displayList.addCommand(&commandDrawObject);
  displayList.draw();
}

ROTOM::DisplayList *ROTOM::GetActualDisplayList() {
  return &displayList;
}