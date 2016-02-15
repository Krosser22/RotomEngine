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

const int amount = 22;

namespace ROTOM {
  class DefaultScene : public ROTOM::Scene {
  public:
    DefaultScene() {};
    ~DefaultScene() {};

    void init();

    void update();

    void draw();

    void destroy();
  };
}

void ROTOM::DefaultScene::init() {
  Scene::init();

  camera_.setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  camera_.setupPerspective(45.0f, (float)WindowWidth() / (float)WindowHeight(), 0.1f, 100.0f);
  camera_.setPosition(0.0f, 0.0f, 0.0f);

  std::shared_ptr<Geometry> geometry(new Geometry());
  std::shared_ptr<Material> material1(new Material("../../../../img/texture1.png"));
  std::shared_ptr<Material> material2(new Material("../../../../img/texture2.png"));
  std::shared_ptr<Material> material3(new Material("../../../../img/texture3.png"));
  std::shared_ptr<Material> material4(new Material());

  std::shared_ptr<Drawable> drawable1(new Drawable());
  std::shared_ptr<Drawable> drawable2(new Drawable());
  std::shared_ptr<Drawable> drawable3(new Drawable());
  drawable1->setGeometry(geometry);
  drawable1->setMaterial(material1);
  drawable1->setParent(Scene::getRoot());
  drawable1->setPosition(0.0f, 0.0f, -5.0f);
  drawable2->setGeometry(geometry);
  drawable2->setMaterial(material2);
  drawable2->setParent(drawable1.get());
  drawable2->setPosition(0.0f, 0.0f, 0.0f);
  drawable3->setGeometry(geometry);
  drawable3->setMaterial(material3);
  drawable3->setParent(drawable2.get());
  drawable3->setPosition(0.0f, 0.0f, 0.0f);

  const float separation = -2.2f;
  const float pos_x_started = 15.0f;
  const float pos_y_started = 7.0f;
  const float pos_z_started = -5.0f;
  const int rows = 15;
  const int cols = 15;
  float pos[3] = { 0.0f, 0.0f, 0.0f };
  for (int i = 0; i < amount; ++i) {
    //printf("Creating Node: %d/%d\n", i, amount);
    std::shared_ptr<Drawable> drawable(new Drawable());
    pos[0] = ((i % cols) * separation) + pos_x_started;
    pos[1] = ((i / (cols * rows)) * separation) + pos_y_started;
    pos[2] = (((i / cols) % rows) * separation) + pos_z_started;
    drawable->setGeometry(geometry);
    drawable->setMaterial(material4);
    drawable->setParent(drawable1.get());
    drawable->setPosition(pos);
  }
  printf("%d\n", Scene::getRoot()->childCount());
}

void ROTOM::DefaultScene::update() {
  Scene::update();

  float sin_time = sin(TIME::appTime()) * 0.022f;
  //root_.getChildAt(0)->moveX(sin_time);
  //root_.getChildAt(0)->getChildAt(0)->moveY(sin_time);
  //root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->moveZ(sin_time);
}

void ROTOM::DefaultScene::draw() {
  Scene::draw();

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::Text("%d Cubes * 6 faces * 2 Triangles * 3 Points = %d Points", amount + 3, (amount + 3) * 6 * 2 * 3);

  ImGui::Begin("Input");
  {
    /*if (ImGui::Button("Detach")) {
      if (root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->parent() == root_.getChildAt(0)->getChildAt(0)) {
        root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->setParent(root_.getChildAt(0));
      } else {
        root_.getChildAt(0)->getChildAt(0)->getChildAt(0)->setParent(root_.getChildAt(0)->getChildAt(0));
      }
    }*/

    ImGui::DragFloat3("LightPosition", &lights_.at(0).lightPositionX, 10.0f, -10000.0f, 10000.0f, "%.2f", 1.0f);
    ImGui::DragFloat3("LightColor", &lights_.at(0).lightColorX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    ImGui::DragFloat4("specularIntensity", &lights_.at(0).specularIntensityX, 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
    //ImGui::DragFloat("Shininess", &(((Drawable *)(root_.getChildAt(0)->getChildAt(0)))->material()->shininess_), 1.0f, 0.0f, 1000.0f, "%.2f", 1.0f);
    //ImGui::DragFloat4("specularMaterial", (((Drawable *)(root_.getChildAt(0)->getChildAt(0)))->material()->specularMaterial_), 0.01f, 0.0f, 1.0f, "%.2f", 1.0f);
  }
  ImGui::End();
}

void ROTOM::DefaultScene::destroy() {
  Scene::destroy();
}

int ROTOM::main(int argc, char** argv) {
  WindowInit(1280, 720);

  DefaultScene defaultScene;
  defaultScene.init();

  //std::shared_ptr<std::string> source(new std::string);
  //ROTOM::read_file("../../../../shaders/shader.frag", source);

  printf("%d\n", defaultScene.getRoot()->childCount());
  while (WindowIsOpened()) {
    //defaultScene.input();
    defaultScene.update();
    defaultScene.draw();
  }
  defaultScene.destroy();
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