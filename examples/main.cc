/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "camera.h"
#include "drawable.h"
#include "geometry.h"
#include "imgui.h"
#include "taskManager.h"
#include "time.h"
#include "window.h"

ROTOM::Drawable drawable1, drawable2, drawable3;
ROTOM::Camera camera;

void hud() {
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

  ImGui::Begin("Input");
  {
    if (ImGui::Button("Detach")) {
      if (drawable3.parent() == &drawable2) {
        drawable3.setParent(&drawable1);
      } else {
        drawable3.setParent(&drawable2);
      }
    }
    ImGui::SliderFloat3("LightPosition", camera.commandDrawObject_.lightPosition_, -1000, 1000);
    ImGui::SliderFloat3("LightColor", camera.commandDrawObject_.lightColor_, -1000, 1000);
    ImGui::SliderFloat("Shininess", &camera.commandDrawObject_.shininess_, 0, 1000);
    ImGui::SliderFloat4("specularIntensity", camera.commandDrawObject_.specularIntensity_, -1000, 1000);
    ImGui::SliderFloat4("specularMaterial", camera.commandDrawObject_.specularMaterial_, -1000, 1000);
  }
  ImGui::End();
}

int ROTOM::main(int argc, char** argv) {
  ROTOM::WindowInit(1280, 720);

  float camera_position[3] = { 0.0f, 0.0f, 0.0f };
  float node1_position[3] = { 0.0f, 0.0f, -5.0f };
  float node2_position[3] = { 0.0f, 0.0f, 0.0f };
  float node3_position[3] = { 0.0f, 0.0f, 0.0f };

  //General Data
  camera.setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  camera.setupPerspective(45.0f, (float)ROTOM::WindowWidth() / (float)ROTOM::WindowHeight(), 0.1f, 100.0f);
  camera.setPosition(camera_position);
  
  std::shared_ptr<ROTOM::Geometry> geometry(new ROTOM::Geometry());

  std::shared_ptr<ROTOM::Material> material1(new ROTOM::Material("../../../../img/texture1.png"));
  std::shared_ptr<ROTOM::Material> material2(new ROTOM::Material("../../../../img/texture2.png"));
  std::shared_ptr<ROTOM::Material> material3(new ROTOM::Material("../../../../img/texture3.png"));
  std::shared_ptr<ROTOM::Material> material4(new ROTOM::Material());

  //ROTOM::Drawable drawable1(geometry, material1, camera.root());
  //ROTOM::Drawable drawable2(geometry, material2, &drawable1);
  //ROTOM::Drawable drawable3(geometry, material3, &drawable2);

  drawable1.setGeometry(geometry);
  drawable2.setGeometry(geometry);
  drawable3.setGeometry(geometry);
  drawable1.setMaterial(material1);
  drawable2.setMaterial(material2);
  drawable3.setMaterial(material3);
  drawable1.setParent(camera.root());
  drawable2.setParent(&drawable1);
  drawable3.setParent(&drawable2);
  
  const int amount = 1722;
  ROTOM::Drawable d[amount];

  float pos[3] = { 0.0f, 0.0f, 0.0f };
  float separation = -2.2f;
  float pos_x_started = 15.0f;
  float pos_y_started = 7.0f;
  float pos_z_started = -5.0f;
  int rows = 15;
  int cols = 15;
  for (int i = 0; i < amount; ++i) {
    pos[0] = ((i % cols) * separation) + pos_x_started;
    pos[1] = ((i / (rows * cols)) * separation) + pos_y_started;
    pos[2] = (((i / cols) % rows) * separation) + pos_z_started;
    d[i].setGeometry(geometry);
    d[i].setMaterial(material4);
    d[i].setParent(&drawable1);
    d[i].setPosition(pos);
  }

  float sin_time = 0.0f;
  node1_position[0] = sin(ROTOM::TIME::appTime()) * 2.2f;
  drawable1.setPosition(node1_position);
  while (ROTOM::WindowIsOpened()) {
    //Update
    sin_time = sin(ROTOM::TIME::appTime()) * 2.2f;
    node1_position[0] = sin_time;
    node2_position[1] = sin_time;
    node3_position[2] = sin_time;
    drawable1.setPosition(node1_position);
    drawable2.setPosition(node2_position);
    drawable3.setPosition(node3_position);
    //...

    //Draw 3D
    camera.doRender();
    //...

    //Draw 2D (IMGUI)
    hud();
    //...
  }
  ROTOM::WindowDestroy();
  return 0;
}

/*
----------
---DONE---
----------


-----------
---DOING---
-----------
+Tasks


----------
---TODO---
----------
+Actualizar genie
+Add LUA
+Use my render list with IMGUI
+Add a class DB with SQLite or another library
+add asset importer http://assimp.sourceforge.net/
*/