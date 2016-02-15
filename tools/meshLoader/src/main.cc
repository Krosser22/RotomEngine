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

int ROTOM::main(int argc, char** argv) {
  ROTOM::WindowInit(1600, 900);

  float camera_position[3] = { 0.0f, 0.0f, 500.0f };
  ROTOM::Camera camera;
  camera.setViewMatrix(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))));
  camera.setupPerspective(45.0f, (float)ROTOM::WindowWidth() / (float)ROTOM::WindowHeight(), 0.1f, 1000.0f);
  camera.setPosition(camera_position);

  std::shared_ptr<ROTOM::Geometry> geometry(new ROTOM::Geometry());
  std::shared_ptr<ROTOM::Material> material(new ROTOM::Material("../../../../obj/Sirus5ColonialCity/Maps/1ab2.jpg"));
  ROTOM::GeneralShaderData generalShaderData;
  material->generalShaderData_ = &generalShaderData;
  ROTOM::Drawable drawable(geometry, material, camera.root());
  drawable.setPositionZ(-500.0f);
  std::shared_ptr<ROTOM::Geometry::GeometryData> obj_data(new ROTOM::Geometry::GeometryData);
  ROTOM::TIME::Chronometer t_load_OBJ, t_save_from_OBJ_to_ROTOM, t_load_ROTOM;

#define OBJ_BLONDE
//#define OBJ_IRONMAN
//#define OBJ_SIRIUS_5_COLONIAL_CITY
#ifdef OBJ_BLONDE
  const char *base_path = "../../../../obj/";
  const char *path = "Blonde/";
  const char *name = "Blonde";
  const char *old_ext = ".obj";
  const char *new_ext = ".rotom";
#elif defined OBJ_IRONMAN
  const char *base_path = "../../../../obj/";
  const char *path = "IronMan/";
  const char *name = "IronMan";
  const char *old_ext = ".obj";
  const char *new_ext = ".rotom";
#elif defined OBJ_SIRIUS_5_COLONIAL_CITY
  const char *base_path = "../../../../obj/";
  const char *path = "Sirus5ColonialCity/";
  const char *name = "sirus_city";
  const char *old_ext = ".obj";
  const char *new_ext = ".rotom";
#endif

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
  ROTOM::FILES::Load_ROTOM_OBJ(new_path, obj_data);
  printf("%f seconds.\n", t_load_ROTOM.end());
  printf(".................................\n");

  geometry->loadGeometry(&obj_data);

  while (ROTOM::WindowIsOpened()) {
    //update
    //drawable.setPosition(drawable.po);
    //drawable.setRotation(node_rotation);
    //drawable.setScale(node_scale);
    //...
    
    //draw 3D
    camera.doRender();
    //...

    //draw 2D (IMGUI)
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    //ImGui::DragFloat3("Position", node_position, -50.0f, 50.0f);
    //ImGui::DragFloat3("Rotation", node_rotation, -50.0f, 50.0f);
    //ImGui::DragFloat3("Scale", node_scale, -50.0f, 50.0f);
    //...
  }
  return 0;
}