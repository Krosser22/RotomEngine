/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/hud.h"
#include "general/files.h"
#include "general/input.h"
#include "general/window.h"
#include "general/sceneManager.h"
#include "../examples/include/scenes/cubemapScene.h"
#include "../examples/include/scenes/defaultScene.h"
#include "../examples/include/scenes/depthScene.h"
#include "../examples/include/scenes/geometryScene.h"
#include "../examples/include/scenes/movementScene.h"
#include "../examples/include/scenes/meshLoaderScene.h"
#include "../examples/include/scenes/proceduralScene.h"
#include "../examples/include/scenes/renderToTextureScene.h"
#include "../examples/include/scenes/shaderScene.h"
#include "../examples/include/scenes/shadowScene.h"
#include "../examples/include/scenes/soundScene.h"
#include <imgui.h>

struct HUDDatatrue {
  std::shared_ptr<ROTOM::Node> root;
  std::vector<std::shared_ptr<ROTOM::Light>> lights;
  ROTOM::Camera *camera;
  ROTOM::Node *selected;

  ImGuiWindowFlags window_flags = 0;

  bool opened = true;

  int nextPushID = 0;

  float windowWidth = 0.0f;
  float windowHeight = 0.0f;

  float alpha = 0.0f;

  float leftColumnWidth = 0.0f;
  float rightColumnWidth = 0.0f;

  float menuWidth = 0.0f;
  float menuHeight = 0.0f;
  float menuPositionX = 0.0f;
  float menuPositionY = 0.0f;

  float sceneTreeWidth = 0.0f;
  float sceneTreeHeight = 0.0f;
  float sceneTreePositionX = 0.0f;
  float sceneTreePositionY = 0.0f;

  float detailsWidth = 0.0f;
  float detailsHeight = 0.0f;
  float detailsPositionX = 0.0f;
  float detailsPositionY = 0.0f;

  float contentWidth = 0.0f;
  float contentHeight = 0.0f;
  float contentPositionX = 0.0f;
  float contentPositionY = 0.0f;

  float sceneRenderWidth = 0.0f;
  float sceneRenderHeight = 0.0f;
  float sceneRenderPositionX = 0.0f;
  float sceneRenderPositionY = 0.0f;

  float offsetXAmountPerChild = 10.0f;

  std::string fps;

  char detailsChildCount[8];
  float detailsPosition[3];
  float detailsRotation[3];
  float detailsScale[3];
  char detailsVertexCount[8];

  ROTOM::Content content;

  std::vector<std::string> contentListPath;
  std::vector<std::string> contentListName;

  ROTOM::CubemapScene cubemapScene;
  ROTOM::DefaultScene defaultScene;
  ROTOM::DepthScene depthScene;
  ROTOM::GeometryScene geometryScene;
  ROTOM::MeshLoaderScene meshLoaderScene;
  ROTOM::MovementScene movementScene;
  ROTOM::ProceduralScene proceduralScene;
  ROTOM::RenderToTextureScene renderToTextureScene;
  ROTOM::ShaderScene shaderScene;
  ROTOM::ShadowScene shadowScene;
  ROTOM::SoundScene soundScene;
} hud;

void ROTOM::HUD::Init(std::shared_ptr<Node> r, std::vector<std::shared_ptr<Light>> l, Camera *c) {
  hud.root = r;
  hud.lights = l;
  hud.camera = c;

  hud.window_flags |= ImGuiWindowFlags_NoResize;
  hud.window_flags |= ImGuiWindowFlags_NoMove;
  hud.window_flags |= ImGuiWindowFlags_NoCollapse;
  //hud.window_flags |= ImGuiWindowFlags_ShowBorders;
  //hud.window_flags |= ImGuiWindowFlags_NoTitleBar;
  //hud.window_flags |= ImGuiWindowFlags_NoScrollbar;
  //hud.window_flags |= ImGuiWindowFlags_MenuBar;

  hud.windowWidth = (float)WindowWidth();
  hud.windowHeight = (float)WindowHeight();

  hud.alpha = 1.0f;

  hud.leftColumnWidth = 0.1f;
  hud.rightColumnWidth = 0.15f;

  hud.menuWidth = hud.windowWidth;
  hud.menuHeight = 19.0f;
  hud.menuPositionX = 0.0f;
  hud.menuPositionY = 0.0f;

  hud.sceneTreeWidth = hud.windowWidth * hud.leftColumnWidth;
  hud.sceneTreeHeight = hud.windowHeight - hud.menuHeight;
  hud.sceneTreePositionX = 0.0f;
  hud.sceneTreePositionY = hud.menuHeight;
  
  hud.detailsWidth = hud.windowWidth * hud.rightColumnWidth;
  hud.detailsHeight = hud.windowHeight * 0.5f - hud.menuHeight;
  hud.detailsPositionX = hud.windowWidth - hud.detailsWidth;
  hud.detailsPositionY = hud.menuHeight;
  
  hud.contentWidth = hud.windowWidth * hud.rightColumnWidth;
  hud.contentHeight = hud.windowHeight * 0.5f;
  hud.contentPositionX = hud.windowWidth - hud.contentWidth;
  hud.contentPositionY = hud.detailsPositionY + hud.detailsHeight;
  
  hud.sceneRenderWidth = hud.windowWidth - hud.sceneTreeWidth - hud.detailsWidth;
  hud.sceneRenderHeight = hud.windowHeight - hud.menuHeight;
  hud.sceneRenderPositionX = hud.sceneTreeWidth;
  hud.sceneRenderPositionY = hud.menuHeight;

  hud.content = kContent_None;

  ImGuiStyle& style = ImGui::GetStyle();
  style.WindowRounding = 0.0f;
  style.ChildWindowRounding = 0.0f;
  style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.09f, 0.20f, 1.00f);
  style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.32f, 0.80f, 1.00f);
  style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);


  style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
  //style.Colors[ImGuiCol_TextHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  //style.Colors[ImGuiCol_TextActive] = ImVec4(1.00f, 1.00f, 0.00f, 1.00f);
  style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
  style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
  style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
  style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
  style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
  style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
  style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
  style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
  style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
  style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
  style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
  style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
  style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
  style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
  style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
  style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
  style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
  style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
  style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
  style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
  style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
  style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
  style.Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
  style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
  style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
  style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
  style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
  style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
  style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
  style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
  style.Colors[ImGuiCol_TooltipBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
  style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void ROTOM::HUD::Draw() {
  if (INPUT::IsKeyPressed('P')) {
    hud.opened = !hud.opened;
  }

  DrawMenu();

  if (hud.opened) {
    //ImGui::ShowTestWindow();

    DrawSceneTree();
    DrawDetails();
    DrawContent();
    //DrawSceneRender();
    hud.nextPushID = 0;
  }
}

void ROTOM::HUD::DrawMenu() {
  ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
  if (ImGui::BeginMainMenuBar())
  {
    char fps[256];
    sprintf(fps, "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    hud.fps = fps;
    bool sceneMenuIsOpened = ImGui::BeginMenu("Scenes");
    if (sceneMenuIsOpened) {
      if (ImGui::MenuItem("Cubemap", "1") || (sceneMenuIsOpened && INPUT::IsKeyPressed('1'))) {
        ChangeScene(&hud.cubemapScene);
      }
      if (ImGui::MenuItem("Default", "2") || (sceneMenuIsOpened && INPUT::IsKeyPressed('2'))) {
        ChangeScene(&hud.defaultScene);
      }
      if (ImGui::MenuItem("Depth", "3") || (sceneMenuIsOpened && INPUT::IsKeyPressed('3'))) {
        ChangeScene(&hud.depthScene);
      }
      if (ImGui::MenuItem("Geometry", "4") || (sceneMenuIsOpened && INPUT::IsKeyPressed('4'))) {
        ChangeScene(&hud.geometryScene);
      }
      if (ImGui::MenuItem("MeshLoader", "5") || (sceneMenuIsOpened && INPUT::IsKeyPressed('5'))) {
        ChangeScene(&hud.meshLoaderScene);
      }
      if (ImGui::MenuItem("Movement", "6") || (sceneMenuIsOpened && INPUT::IsKeyPressed('6'))) {
        ChangeScene(&hud.movementScene);
      }
      if (ImGui::MenuItem("Procedural", "7") || (sceneMenuIsOpened && INPUT::IsKeyPressed('7'))) {
        ChangeScene(&hud.proceduralScene);
      }
      if (ImGui::MenuItem("RenderToTexture", "8") || (sceneMenuIsOpened && INPUT::IsKeyPressed('8'))) {
        ChangeScene(&hud.renderToTextureScene);
      }
      if (ImGui::MenuItem("Shader", "9") || (sceneMenuIsOpened && INPUT::IsKeyPressed('9'))) {
        ChangeScene(&hud.shaderScene);
      }
      if (ImGui::MenuItem("Shadow", "0") || (sceneMenuIsOpened && INPUT::IsKeyPressed('0'))) {
        ChangeScene(&hud.shadowScene);
      }
      if (ImGui::MenuItem("Sound", "'") || (sceneMenuIsOpened && INPUT::IsKeyPressed('\''))) {
        ChangeScene(&hud.soundScene);
      }

      ImGui::EndMenu();
    }
    ImGui::MenuItem(hud.fps.c_str());
    ImGui::EndMainMenuBar();
  }
}

void ROTOM::HUD::DrawSceneTree() {
  ImGui::SetNextWindowPos(ImVec2(hud.sceneTreePositionX, hud.sceneTreePositionY));
  ImGui::Begin("SceneTree", &hud.opened, ImVec2(hud.sceneTreeWidth, hud.sceneTreeHeight), hud.alpha, hud.window_flags);
  {
    DrawNodes(hud.root.get(), 0);

    /*for (unsigned int i = 0; i < hud.lights.size(); ++i) {
      DrawLight(hud.lights.at(i).get());
    }*/
  }
  ImGui::End();
}

void ROTOM::HUD::DrawDetails() {
  ImGui::SetNextWindowPos(ImVec2(hud.detailsPositionX, hud.detailsPositionY));
  ImGui::Begin("Details", &hud.opened, ImVec2(hud.detailsWidth, hud.detailsHeight), hud.alpha, hud.window_flags);
  {
    if (hud.selected) {
      switch (hud.selected->type()) {
        case kNodeType_Drawable: {
          DrawDrawable((Drawable *)hud.selected);
          break;
        }
        case kNodeType_Light: {
          DrawLight((Light *)hud.selected);
          break;
        }
        case kNodeType_Node: {
          DrawNode(hud.selected);
          break;
        }
        default: {
          assert("hud.cc > DrawDetails() > selected->type()" && false);
          break;
        }
      }
    }
  }
  ImGui::End();
}

void ROTOM::HUD::DrawContent() {
  ImGui::SetNextWindowPos(ImVec2(hud.contentPositionX, hud.contentPositionY));
  ImGui::Begin("Content Browser", &hud.opened, ImVec2(hud.contentWidth, hud.contentHeight), hud.alpha, hud.window_flags);
  {
    switch (hud.content) {
      case kContent_Geometry: {
        for (unsigned int i = 0; i < hud.contentListName.size(); ++i) {
          if (ImGui::Selectable(hud.contentListName.at(i).c_str(), false)) {
            ((Drawable *)hud.selected)->geometry()->loadGeometry(hud.contentListName.at(i).c_str());
            hud.content = kContent_None;
          }
        }
        break;
      }
      case kContent_Shaders: {
        break;
      }
      case kContent_Texture: {
        break;
      }
      default: {
        break;
      }
    }
  }
  ImGui::End();
}

void ROTOM::HUD::DrawSceneRender() {
  ImGui::SetNextWindowPos(ImVec2(hud.sceneRenderPositionX, hud.sceneRenderPositionY));
  ImGui::Begin("Render", &hud.opened, ImVec2(hud.sceneRenderWidth, hud.sceneRenderHeight), hud.alpha, hud.window_flags);
  {

  }
  ImGui::End();
}

void ROTOM::HUD::DrawNodes(Node *node, float offsetX) {
  ImGui::PushID(hud.nextPushID++);
  if (ImGui::Selectable(node->name(), hud.selected == node)) {
    hud.selected = node;
  }
  ImGui::PopID();

  for (unsigned int i = 0; i < node->childCount(); ++i) {
    DrawNodes(node->getChildAt(i).get(), offsetX + hud.offsetXAmountPerChild);
  }
}

void ROTOM::HUD::DrawNode(Node *node) {
  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Node:");
  ImGui::SameLine();
  ImGui::Text(node->name());

  ImGui::Separator();

  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Childs:");
  ImGui::SameLine();
  sprintf(hud.detailsChildCount, "%d", node->childCount());
  ImGui::Text(hud.detailsChildCount);

  ImGui::Separator();

  hud.detailsPosition[0] = node->position()[0];
  hud.detailsPosition[1] = node->position()[1];
  hud.detailsPosition[2] = node->position()[2];
  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Position:");
  ImGui::PushID(hud.nextPushID++);
  if (ImGui::DragFloat3("", hud.detailsPosition, 0.2f, -100.0f, 100.0f, "%.2f", 1.0f)) {
    node->setPosition(hud.detailsPosition);
  }
  ImGui::PopID();

  ImGui::Separator();

  hud.detailsRotation[0] = node->rotation()[0];
  hud.detailsRotation[1] = node->rotation()[1];
  hud.detailsRotation[2] = node->rotation()[2];
  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Rotation:");
  ImGui::PushID(hud.nextPushID++);
  if (ImGui::DragFloat3("", hud.detailsRotation, 0.2f, -100.0f, 100.0f, "%.2f", 1.0f)) {
    node->setRotation(hud.detailsRotation);
  }
  ImGui::PopID();

  ImGui::Separator();

  hud.detailsScale[0] = node->scale()[0];
  hud.detailsScale[1] = node->scale()[1];
  hud.detailsScale[2] = node->scale()[2];
  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Scale:");
  ImGui::PushID(hud.nextPushID++);
  if (ImGui::DragFloat3("", hud.detailsScale, 0.2f, -100.0f, 100.0f, "%.2f", 1.0f)) {
    node->setScale(hud.detailsScale);
  }
  ImGui::PopID();

  ImGui::Separator();
}

void ROTOM::HUD::DrawDrawable(Drawable *drawable) {
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Drawable");

  ImGui::Separator();
  ImGui::Separator();

  DrawNode(drawable);

  ImGui::Separator();

  if (drawable->geometry()) {
    DrawGeometry(drawable->geometry().get());
  }

  ImGui::Separator();

  if (drawable->material()) {
    DrawMaterial(drawable->material().get());
  }

  ImGui::Separator();

  DrawMaterialSettings(drawable->materialSettings().get());

  ImGui::Separator();
}

void ROTOM::HUD::DrawCamera(Camera *camera) {
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Camera");

  ImGui::Separator();

  //DrawNode(camera);
}

void ROTOM::HUD::DrawLight(Light *light) {
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Light");

  ImGui::Separator();
  ImGui::Separator();

  DrawNode(light);

  ImGui::Separator();

  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Color:");
  ImGui::PushID(hud.nextPushID++);
  ImGui::DragFloat3("", light->materialSettings()->color_, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  ImGui::PopID();

  ImGui::Separator();

  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "SpecularIntensity:");
  ImGui::PushID(hud.nextPushID++);
  ImGui::DragFloat3("", light->specularIntensity_, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
  ImGui::PopID();

  ImGui::Separator();
}

void ROTOM::HUD::DrawGeometry(Geometry *geometry) {
  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "VertexCount:");
  ImGui::SameLine();
  sprintf(hud.detailsVertexCount, "%d", geometry->vertexCount());
  ImGui::Text(hud.detailsVertexCount);

  ImGui::Separator();

  if (ImGui::Button("Change Geometry")) {
    hud.content = kContent_Geometry;
    system("dir /b/s ..\\..\\..\\..\\obj\\*.ROTOM > list_obj.txt");
    std::shared_ptr<std::string> file = std::shared_ptr<std::string>(new std::string());
    FILES::ReadFile("list_obj.txt", file);

    hud.contentListPath.clear();

    char *separator = "\r\n";
    int stringEnd = file->find(separator);
    std::string path = file->substr(0, stringEnd);
    std::string nextPath = file->substr(stringEnd + 2);
    
    if (path.size() > 0) {
      hud.contentListPath.push_back(path);
      stringEnd = nextPath.find(separator);
      while (stringEnd != -1) {
        path = nextPath.substr(0, stringEnd);
        nextPath = nextPath.substr(stringEnd + 2);
        hud.contentListPath.push_back(path);
        stringEnd = nextPath.find(separator);
      }

      hud.contentListName.clear();
      for (unsigned int i = 0; i < hud.contentListPath.size(); ++i) {
        std::string path = hud.contentListPath.at(i);
        std::string name = path.substr(path.find("\\obj\\") + 5);
        name = name.substr(0, name.find(".rotom"));
        hud.contentListName.push_back(name);
      }
    }
  }
}

void ROTOM::HUD::DrawMaterial(Material *material) {
  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Shininess:");
  ImGui::PushID(hud.nextPushID++);
  ImGui::DragFloat("", &material->materialData_.shininess, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
  ImGui::PopID();

  ImGui::Separator();

  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "SpecularLight:");
  ImGui::PushID(hud.nextPushID++);
  ImGui::DragFloat3("", &material->materialData_.specularMaterial[0], 0.01f, 0.0f, 1000.0f, "%.2f", 1.0f);
  ImGui::PopID();

  ImGui::Separator();
}

void ROTOM::HUD::DrawMaterialSettings(MaterialSettings *materialSettings) {
  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Color:");
  ImGui::PushID(hud.nextPushID++);
  ImGui::DragFloat4("", materialSettings->color_, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  ImGui::PopID();

  ImGui::Separator();
}
