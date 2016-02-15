/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "camera.h"
#include "drawable.h"
#include "imgui.h"
#include "text.h"
#include "time.h"
#include "window.h"
#include "scene.h"

int ROTOM::main(int argc, char** argv) {
  WindowInit(1280, 720);
  Scene scene;

  scene.camera_.setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  scene.camera_.setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  scene.camera_.setPosition(0.0f, 0.0f, 0.0f);

  std::shared_ptr<Geometry> geometry(new Geometry());
  std::shared_ptr<Material> material1(new Material("../../../../img/texture1.png"));
  std::shared_ptr<Material> material2(new Material("../../../../img/texture2.png"));
  std::shared_ptr<Material> material3(new Material("../../../../img/texture3.png"));
  std::shared_ptr<Material> material4(new Material());

  Drawable drawable1, drawable2, drawable3;
  drawable1.setGeometry(geometry);
  drawable1.setMaterial(material1);
  drawable1.setParent(&scene.root_);
  drawable1.setPosition(0.0f, 0.0f, -5.0f);
  drawable2.setGeometry(geometry);
  drawable2.setMaterial(material2);
  drawable2.setParent(&drawable1);
  drawable2.setPosition(0.0f, 0.0f, 0.0f);
  drawable3.setGeometry(geometry);
  drawable3.setMaterial(material3);
  drawable3.setParent(&drawable2);
  drawable3.setPosition(0.0f, 0.0f, 0.0f);

  const int amount = 2722;
  const float separation = -2.2f;
  const float pos_x_started = 15.0f;
  const float pos_y_started = 7.0f;
  const float pos_z_started = -5.0f;
  const int rows = 15;
  const int cols = 15;
  float pos[3] = { 0.0f, 0.0f, 0.0f };
  Drawable d[amount];
  for (int i = 0; i < amount; ++i) {
    pos[0] = ((i % cols) * separation) + pos_x_started;
    pos[1] = ((i / (rows * cols)) * separation) + pos_y_started;
    pos[2] = (((i / cols) % rows) * separation) + pos_z_started;
    d[i].setGeometry(geometry);
    d[i].setMaterial(material4);
    d[i].setParent(&drawable1);
    d[i].setPosition(pos);
  }

  //std::shared_ptr<std::string> source(new std::string);
  //ROTOM::read_file("../../../../shaders/shader.frag", source);

  while (WindowIsOpened()) {
    //Update
    float sin_time = sin(TIME::appTime()) * 0.022f;
    drawable1.moveX(sin_time);
    drawable2.moveY(sin_time);
    drawable3.moveZ(sin_time);
    //...

    //Draw 3D
    scene.update();
    //...

    //Draw 2D (IMGUI)
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::Text("%d Cubes * 6 faces * 2 Triangles * 3 Points = %d Points", amount + 3, (amount + 3) * 6 * 2 * 3);

    ImGui::Begin("Input");
    {
      if (ImGui::Button("Detach")) {
        if (drawable3.parent() == &drawable2) {
          drawable3.setParent(&drawable1);
        } else {
          drawable3.setParent(&drawable2);
        }
      }

      ImGui::DragFloat3("LightPosition", &scene.lights_.at(0).lightPositionX, 10.0f, -10000.0f, 10000.0f, "%.2f", 1.0f);
      ImGui::DragFloat3("LightColor", &scene.lights_.at(0).lightColorX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
      ImGui::DragFloat("Shininess", &drawable1.material()->shininess_, 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
      ImGui::DragFloat4("specularIntensity", &scene.lights_.at(0).specularIntensityX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
      ImGui::DragFloat4("specularMaterial", drawable1.material()->specularMaterial_, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    }
    ImGui::End();
    //...
  }
  return 0;
}

/*
---------
---ASK---
---------
More than 1 Light



----------
---DONE---
----------


-----------
---DOING---
-----------


----------
---TODO---
----------
+Add LUA
+Use my render list with IMGUI
+Add a class DB with SQLite or another library to save the game
+add asset importer http://assimp.sourceforge.net/
*/