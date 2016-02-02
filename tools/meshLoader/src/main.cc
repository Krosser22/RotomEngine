/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "camera.h"
#include "commandDrawObject.h"
#include "displayList.h"
#include "geometry.h"
#include "imgui.h"
#include "sound.h"
#include "drawable.h"
#include "files.h"
#include "time.h"
#include "window.h"

//General data info
struct Data {
  ROTOM::DisplayList displayList;
  ROTOM::Camera camera;
  ROTOM::Drawable root;
} data;

int ROTOM::main(int argc, char** argv) {
  ROTOM::WindowInit(1600, 900);

  //General data
  float camera_position[3] = { 0.0f, 0.0f, -500.0f };
  data.camera.setPosition(camera_position);
  data.camera.setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  data.camera.setupPerspective(45.0f, (float)ROTOM::WindowWidth() / (float)ROTOM::WindowHeight(), 0.1f, 1000.0f);
  data.displayList.setCamera(&data.camera);

  ROTOM::CommandDrawObject commandDrawObject(&data.root);
  ROTOM::Geometry geometry;
  ROTOM::Material material;
  //material.setTexture("../../../deps/img/defaultTexture.png");

  ROTOM::Drawable drawable(&geometry, &material, &data.root);
  float node_position[3] = { 0.0f, 1.0f, -5.0f };
  float node_rotation[3] = { 0.0f, 0.0f, 0.0f };
  float node_scale[3] = { 1.0f, 1.0f, 1.0f };

  //Sound
  //sound::init();

  //LoadObj
  EDK3::scoped_ptr<ROTOM::Geometry::GeometryData> obj_data;
  obj_data.alloc();
  ROTOM::TIME::Chronometer t_load_OBJ, t_save_from_OBJ_to_ROTOM, t_load_ROTOM;

  const char *base_path = "../../../deps/obj/";
  const char *path = "Blonde/";
  const char *name = "Blonde";
  const char *old_ext = ".obj";
  const char *new_ext = ".rotom";

  char final_path[256];
  strcpy(final_path, base_path);
  strcat(final_path, path);
  strcat(final_path, name);
  strcat(final_path, old_ext);

  char new_path[256];
  strcpy(new_path, base_path);
  strcat(new_path, name);
  strcat(new_path, new_ext);

  printf(".................................\n");
  //Normal Loading
  printf(".Loading OBJ  : ");
  t_load_OBJ.start();
  ROTOM::FILES::Load_OBJ2(final_path, obj_data.get());
  printf("%f seconds.\n", t_load_OBJ.end());

  //Saving from OBJ to ROTOM
  printf(".OBJ to ROTOM : ");
  t_save_from_OBJ_to_ROTOM.start();
  ROTOM::FILES::Save_ROTOM_OBJ(new_path, obj_data.get());
  printf("%f seconds.\n", t_save_from_OBJ_to_ROTOM.end());

  //ROTOM Loading
  printf(".Loading ROTOM: ");
  t_load_ROTOM.start();
  ROTOM::FILES::Load_ROTOM_OBJ(new_path, &obj_data);
  printf("%f seconds.\n", t_load_ROTOM.end());
  printf(".................................\n");

  geometry.loadGeometry(&obj_data);

  while (ROTOM::WindowIsOpened()) {
    //update
    data.displayList.addCommand(&commandDrawObject);
    drawable.setPosition(node_position);
    drawable.setRotation(node_rotation);
    drawable.setScale(node_scale);
    //...
    
    //draw 3D
    data.displayList.runAll();
    //...

    //draw 2D (IMGUI)
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::DragFloat3("Position", node_position, -50.0f, 50.0f);
    ImGui::DragFloat3("Rotation", node_rotation, -50.0f, 50.0f);
    ImGui::DragFloat3("Scale", node_scale, -50.0f, 50.0f);
    //...
  }
  ROTOM::WindowDestroy();
  return 0;
}

int main(int argc, char** argv) {
  ROTOM::main(argc, argv);
  return 0;
}