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
#include <imgui.h>

static ROTOM::CommandDrawObject commandDrawObject;
static ROTOM::DisplayList displayList;
static ROTOM::TaskCalculateMatrix taskCalculateNodesMatrix;
static ROTOM::Scene *scene;

void ROTOM::WindowInit(unsigned int width, unsigned int height) {
  GRAPHICS::windowInit(width, height);
}

bool ROTOM::WindowIsOpened() {
  if (!ROTOM::GRAPHICS::windowShouldClose()) {
    //Input
    ROTOM::INPUT::Update();

    //Clear Screen
    ROTOM::GRAPHICS::clear();

    //Update TaskManager
    taskCalculateNodesMatrix.setInput(scene->getRoot().get());
    ROTOM::TASKMANAGER::addTask(&taskCalculateNodesMatrix);

    //Update Scene
    assert(scene);
    scene->input();
    scene->update();

    //Draw Scene
    scene->draw();

    //Render from the camera perspective
    ROTOM::RenderScene(scene->getCamera()->projectionMatrix(), scene->getCamera()->viewMatrix(), scene->getCamera()->position());

    //PostProcess
    scene->postDraw();

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
  assert(&scene);
  scene = newScene;
  scene->setRoot(std::shared_ptr<Node>(new Node("Root")));
  scene->init();
  HUD::Init(scene->getRoot(), scene->getDirectionalLights(), scene->getSpotLights(), scene->getCamera());
}

void ROTOM::RenderScene(float *projectionMatrix, float *viewMatrix, float *viewPosition) {
  commandDrawObject.setInput(scene->getRoot(), scene->getDirectionalLights(), scene->getSpotLights(), projectionMatrix, viewMatrix, viewPosition);
  displayList.addCommand(&commandDrawObject);
  displayList.draw();
}

void ROTOM::RenderPostProcess(Drawable *drawable) {
  CommandDrawObjectData commandDrawObjectData;
  Material *material = drawable->material().get();
  Geometry *geometry = drawable->geometry().get();
  commandDrawObjectData.visible = drawable->visible_;
  commandDrawObjectData.shadows = drawable->shadows_;
  commandDrawObjectData.materialSettings = *drawable->materialSettings().get();
  commandDrawObjectData.shaderData = material->shaderData_;
  commandDrawObjectData.geometry_VAO = *geometry->VAO();
  commandDrawObjectData.geometry_veterCount = geometry->vertexCount();
  commandDrawObjectData.material_texture = material->texture();
  commandDrawObjectData.materialData = material->materialData_;
  float *worldMatrix = glm::value_ptr(*drawable->worldMatrix());
  for (int i = 0; i < 16; ++i) {
    commandDrawObjectData.drawable_worldMatrix[i] = worldMatrix[i];
  }
  //GRAPHICS::drawObject(&commandDrawObjectData, scene->getDirectionalLights(), scene->getSpotLights(), projectionMatrix, viewMatrix, viewPosition);
}

ROTOM::DisplayList *ROTOM::GetActualDisplayList() {
  return &displayList;
}