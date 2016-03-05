/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/hud.h"
#include "general/window.h"
#include "imgui.h"

std::shared_ptr<ROTOM::Node> root;
std::vector<std::shared_ptr<ROTOM::Light>> lights;
ROTOM::Camera *camera;
ROTOM::Node *selected;

ImGuiWindowFlags window_flags = 0;

bool opened = true;

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

void ROTOM::HUD::Init(std::shared_ptr<Node> r, std::vector<std::shared_ptr<Light>> l, Camera *c) {
  root = r;
  lights = l;
  camera = c;

  window_flags |= ImGuiWindowFlags_ShowBorders;
  window_flags |= ImGuiWindowFlags_NoResize;
  window_flags |= ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoCollapse;
  //window_flags |= ImGuiWindowFlags_NoTitleBar;
  //window_flags |= ImGuiWindowFlags_NoScrollbar;
  //window_flags |= ImGuiWindowFlags_MenuBar;

  windowWidth = (float)WindowWidth();
  windowHeight = (float)WindowHeight();

  alpha = 1.0f;

  leftColumnWidth = 0.2f;
  rightColumnWidth = 0.25f;

  menuWidth = windowWidth;
  menuHeight = 20.0f;
  menuPositionX = 0.0f;
  menuPositionY = 0.0f;

  sceneTreeWidth = windowWidth * leftColumnWidth;
  sceneTreeHeight = windowHeight - menuHeight;
  sceneTreePositionX = 0.0f;
  sceneTreePositionY = menuHeight;

  detailsWidth = windowWidth * rightColumnWidth;
  detailsHeight = windowHeight * 0.5f - menuHeight;
  detailsPositionX = windowWidth - detailsWidth;
  detailsPositionY = menuHeight;

  contentWidth = windowWidth * rightColumnWidth;
  contentHeight = windowHeight * 0.5f;
  contentPositionX = windowWidth - contentWidth;
  contentPositionY = detailsPositionY + detailsHeight;

  sceneRenderWidth = windowWidth - sceneTreeWidth - detailsWidth;
  sceneRenderHeight = windowHeight - menuHeight;
  sceneRenderPositionX = sceneTreeWidth;
  sceneRenderPositionY = menuHeight;
}

void ROTOM::HUD::Draw() {
  ImGui::ShowTestWindow();

  DrawMenu();
  DrawSceneTree();
  DrawDetails();
  DrawContent();
  //DrawSceneRender();
}

void ROTOM::HUD::DrawMenu() {

}

void ROTOM::HUD::DrawSceneTree() {
  ImGui::SetNextWindowPos(ImVec2(sceneTreePositionX, sceneTreePositionY));
  ImGui::Begin("SceneTree", &opened, ImVec2(sceneTreeWidth, sceneTreeHeight), alpha, window_flags);
  {
    DrawNodes(root.get(), 0);

    for (unsigned int i = 0; i < lights.size(); ++i) {
      DrawLight(lights.at(i).get());
    }
  }
  ImGui::End();
}

void ROTOM::HUD::DrawDetails() {
  ImGui::SetNextWindowPos(ImVec2(detailsPositionX, detailsPositionY));
  ImGui::Begin("Details", &opened, ImVec2(detailsWidth, detailsHeight), alpha, window_flags);
  {
    if (selected) {
      DrawDrawable((Drawable *)selected);
      /*ImGui::Begin("Material");
      {
      float *shininess = &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.shininess_;
      if (ImGui::DragFloat("Shininess", shininess, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f)) {
      ((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.shininess_ = *shininess;
      }

      ImGui::DragFloat4("specularMaterial", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.specularMaterial_[0], 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
      }
      ImGui::End();*/
    }
  }
  ImGui::End();
}

void ROTOM::HUD::DrawContent() {
  ImGui::SetNextWindowPos(ImVec2(contentPositionX, contentPositionY));
  ImGui::Begin("Content", &opened, ImVec2(contentWidth, contentHeight), alpha, window_flags);
  {

  }
  ImGui::End();
}

void ROTOM::HUD::DrawSceneRender() {
  ImGui::SetNextWindowPos(ImVec2(sceneRenderPositionX, sceneRenderPositionY));
  ImGui::Begin("Render", &opened, ImVec2(sceneRenderWidth, sceneRenderHeight), alpha, window_flags);
  {

  }
  ImGui::End();
}

void ROTOM::HUD::DrawNodes(Node *node, float offsetX) {
  if (ImGui::Selectable(node->name_.c_str(), selected == node)) {
    selected = node;
  }

  for (unsigned int i = 0; i < node->childCount(); ++i) {
    DrawNodes(node->getChildAt(i).get(), offsetX + offsetXAmountPerChild);
  }
}

void ROTOM::HUD::DrawNode(Node *node) {
  node->childCount();
  node->position();
  node->rotation();
  node->scale();
}

void ROTOM::HUD::DrawDrawable(Drawable *drawable) {
  ImGui::Text(drawable->name_.c_str());
}

void ROTOM::HUD::DrawCamera(Camera *camera) {

}

void ROTOM::HUD::DrawLight(Light *light) {
  ImGui::Begin("Light");
  {
    ImGui::DragFloat3("LightPosition", light->lightPosition, 1.0f, -100.0f, 100.0f, "%.2f", 1.0f);
    ImGui::DragFloat3("LightColor", light->lightColor, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularIntensity", light->specularIntensity, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();
}

void ROTOM::HUD::DrawGeometry(Geometry *geometry) {

}

void ROTOM::HUD::DrawMaterial(Material *material) {

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