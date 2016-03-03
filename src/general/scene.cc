/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/scene.h"
#include "general/window.h"
#include "imgui.h"

static ROTOM::Camera camera_;
static std::shared_ptr<ROTOM::Node> root_;
static std::vector<ROTOM::Light> lights_;

void ROTOM::Scene::updateInfo() {

}

void ROTOM::Scene::drawHUD() {
  //ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));

  // Menu
  if (ImGui::BeginMenuBar())
  {
    if (ImGui::BeginMenu("Menu"))
    {
      //ShowExampleMenuFile();
      updateInfo();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Examples"))
    {
      bool open = true;
      ImGui::MenuItem("Main menu bar", NULL, &open);
      //ImGui::MenuItem("Console", NULL, &show_app_console);
      //ImGui::MenuItem("Log", NULL, &show_app_log);
      //ImGui::MenuItem("Simple layout", NULL, &show_app_layout);
      //ImGui::MenuItem("Long text display", NULL, &show_app_long_text);
      //ImGui::MenuItem("Auto-resizing window", NULL, &show_app_auto_resize);
      //ImGui::MenuItem("Simple overlay", NULL, &show_app_fixed_overlay);
      //ImGui::MenuItem("Manipulating window title", NULL, &show_app_manipulating_window_title);
      //ImGui::MenuItem("Custom rendering", NULL, &show_app_custom_rendering);
      //ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
      //ImGui::MenuItem("Metrics", NULL, &show_app_metrics);
      //ImGui::MenuItem("About ImGui", NULL, &show_app_about);
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }

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

std::shared_ptr<ROTOM::Node> ROTOM::Scene::getRoot() {
  return root_;
}

void ROTOM::Scene::setRoot(std::shared_ptr<Node> root) {
  root_ = root;
}

ROTOM::Camera *ROTOM::Scene::getCamera() {
  return &camera_;
}

std::vector<ROTOM::Light> ROTOM::Scene::getLight() {
  return lights_;
}

void ROTOM::Scene::AddLight(Light light) {
  lights_.push_back(light);
}