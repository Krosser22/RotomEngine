/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "general/hud.h"
#include "imgui.h"

void ROTOM::HUD::Draw(std::shared_ptr<Node> root, std::vector<std::shared_ptr<Light>> lights, Camera *camera) {
  for (unsigned int i = 0; i < lights.size(); ++i) {
    DrawLight(lights.at(i).get());
  }

  /*
  ImGui::Begin("Material");
  {
    float *shininess = &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.shininess_;
    if (ImGui::DragFloat("Shininess", shininess, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f)) {
      ((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.shininess_ = *shininess;
    }

    ImGui::DragFloat4("specularMaterial", &((Drawable *)(getRoot()->getChildAt(0)->getChildAt(0).get()))->material()->materialData_.specularMaterial_[0], 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();*/
}

void ROTOM::HUD::DrawNode(Node *node) {

}

void ROTOM::HUD::DrawDrawable(Drawable *drawable) {

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