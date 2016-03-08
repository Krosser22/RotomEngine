/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "meshLoader.h"
#include "general/constants.h"
#include "general/files.h"
#include "general/hud.h"
#include "general/input.h"
#include "general/window.h"
#include "imgui.h"

struct HUDData {
  std::shared_ptr<ROTOM::Node> root;
  std::vector<std::shared_ptr<ROTOM::Light>> lights;
  ROTOM::Camera *camera;
  ROTOM::Node *selected;

  ImGuiWindowFlags window_flags = 0;

  bool opened = false;

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
  float *detailsPosition;
  float *detailsRotation;
  float *detailsScale;
  char detailsVertexCount[8];

  ROTOM::Content content;

  std::vector<std::string> contentListPath;
  std::vector<std::string> contentListName;

} hud;

void ROTOM::HUD::Init(std::shared_ptr<Node> r, std::vector<std::shared_ptr<Light>> l, Camera *c) {
  hud.root = r;
  hud.lights = l;
  hud.camera = c;

  hud.window_flags |= ImGuiWindowFlags_ShowBorders;
  hud.window_flags |= ImGuiWindowFlags_NoResize;
  hud.window_flags |= ImGuiWindowFlags_NoMove;
  hud.window_flags |= ImGuiWindowFlags_NoCollapse;
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
    /*if (ImGui::BeginMenu("File"))
    {
      if (ImGui::MenuItem("New", "CTRL+N")) {
      }
      ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();*/

    char fps[256];
    sprintf(fps, "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    hud.fps = fps;
    ImGui::BeginMenu(hud.fps.c_str());
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
        case kNodeType_Camera: {
          DrawCamera((Camera *)hud.selected);
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
            std::shared_ptr<Geometry> geometry = std::shared_ptr<Geometry>(new Geometry());
            std::shared_ptr<Geometry::GeometryData> obj_data = std::shared_ptr<Geometry::GeometryData>(new Geometry::GeometryData);
            std::string path = "../../../../obj/";
            path.append(hud.contentListName.at(i).c_str());

            //if (hud.contentListName.at(i).find("\\") != -1) {
              MESHLOADER::Load_OBJ(path.c_str(), obj_data);
            /*} else {
              MESHLOADER::Load_OBJ("../../../../obj/", hud.contentListName.at(i).c_str(), obj_data);
            }*/

            if (obj_data->data.size() <= 0) {
              assert("hud.cc > DrawContent() > obj_data->data.size()" && false);
            }
            ((Drawable *)hud.selected)->geometry()->loadGeometry(&obj_data);
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
  if (ImGui::Selectable(node->name(), hud.selected == node)) {
    hud.selected = node;
  }

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

  hud.detailsPosition = &node->position()[0];
  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Position:");
  ImGui::PushID(hud.nextPushID++);
  if (ImGui::DragFloat3("", hud.detailsPosition, 0.2f, -100.0f, 100.0f, "%.2f", 1.0f)) {
    node->setPosition(hud.detailsPosition);
  }
  ImGui::PopID();

  ImGui::Separator();

  hud.detailsRotation = &node->rotation()[0];
  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Rotation:");
  ImGui::PushID(hud.nextPushID++);
  if (ImGui::DragFloat3("", hud.detailsRotation, 0.2f, -100.0f, 100.0f, "%.2f", 1.0f)) {
    node->setRotation(hud.detailsRotation);
  }
  ImGui::PopID();

  ImGui::Separator();

  hud.detailsScale = &node->scale()[0];
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

  DrawNode(camera);
}

void ROTOM::HUD::DrawLight(Light *light) {
  ImGui::TextColored(ImVec4(0.4f, 0.4f, 0.4f, 1.0f), "Light");

  ImGui::Separator();
  ImGui::Separator();

  DrawNode(light);

  ImGui::Separator();

  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "Color:");
  ImGui::PushID(hud.nextPushID++);
  ImGui::DragFloat4("", light->lightColor, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  ImGui::PopID();

  ImGui::Separator();

  ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.6f, 1.0f), "SpecularIntensity:");
  ImGui::PushID(hud.nextPushID++);
  ImGui::DragFloat4("", light->specularIntensity, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
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
    system("dir /b/s ..\\..\\..\\..\\obj\\*.obj > list_obj.txt");
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
        name = name.substr(0, name.find(".obj"));
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
  ImGui::DragFloat4("", &material->materialData_.specularMaterial[0], 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
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

#ifdef THIS_WAS_FOR_TESTING
void ShowExampleMenuFile()
{
  ImGui::MenuItem("(dummy menu)", NULL, false, false);
  if (ImGui::MenuItem("New")) {}
  if (ImGui::MenuItem("Open", "Ctrl+O")) {}
  if (ImGui::BeginMenu("Open Recent"))
  {
    ImGui::MenuItem("fish_hat.c");
    ImGui::MenuItem("fish_hat.inl");
    ImGui::MenuItem("fish_hat.h");
    if (ImGui::BeginMenu("More.."))
    {
      ImGui::MenuItem("Hello");
      ImGui::MenuItem("Sailor");
      if (ImGui::BeginMenu("Recurse.."))
      {
        ShowExampleMenuFile();
        ImGui::EndMenu();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMenu();
  }
  if (ImGui::MenuItem("Save", "Ctrl+S")) {}
  if (ImGui::MenuItem("Save As..")) {}
  ImGui::Separator();
  if (ImGui::BeginMenu("Options"))
  {
    static bool enabled = true;
    ImGui::MenuItem("Enabled", "", &enabled);
    ImGui::BeginChild("child", ImVec2(0, 60), true);
    for (int i = 0; i < 10; i++)
      ImGui::Text("Scrolling Text %d", i);
    ImGui::EndChild();
    static float f = 0.5f;
    static int n = 0;
    ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
    ImGui::InputFloat("Input", &f, 0.1f);
    ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
    ImGui::EndMenu();
  }
  if (ImGui::BeginMenu("Colors"))
  {
    for (int i = 0; i < ImGuiCol_COUNT; i++)
      ImGui::MenuItem(ImGui::GetStyleColName((ImGuiCol)i));
    ImGui::EndMenu();
  }
  if (ImGui::BeginMenu("Disabled", false)) // Disabled
  {
    IM_ASSERT(0);
  }
  if (ImGui::MenuItem("Checked", NULL, true)) {}
  if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}

void ROTOM::Scene::updateInfo() {
  ShowExampleMenuFile();
}

void ROTOM::HUD::drawHUD() {
  // Menu
  ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      ShowExampleMenuFile();
      if (ImGui::MenuItem("New", "CTRL+N")) {
        ShowExampleMenuFile();
      }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Edit"))
    {
      if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
      if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
      ImGui::Separator();
      if (ImGui::MenuItem("Cut", "CTRL+X")) {}
      if (ImGui::MenuItem("Copy", "CTRL+C")) {}
      if (ImGui::MenuItem("Paste", "CTRL+V")) {}
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
  
  
  
  //Inspector
  /*ImGui::PushID("foo");
  ImGui::MenuItem("Menu item", "CTRL+M");
  if (ImGui::BeginMenu("Menu inside a regular window"))
  {
    updateInfo();
    ImGui::EndMenu();
  }
  ImGui::PopID();
  ImGui::Separator();*/

  //Information
  /*ImGui::SetNextWindowPos(ImVec2(0.0f, 20.0f));
  ImGui::Begin("Info", (bool*)0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
  {
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("%d Nodes = %d Vertex", nodes_, vertexCount_);
    if (ImGui::Button("Update info")) {
      updateInfo();
    }
  }
  ImGui::End();*/
}
#endif //THIS_WAS_FOR_TESTING