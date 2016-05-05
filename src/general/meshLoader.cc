/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "general/constants.h"
#include "general/time.h"
#include "general/meshLoader.h"
#include "render/commandSetGeometry.h"
#include "render/displayList.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tiny_obj_loader.h>
#include <iostream>

void PrintInfo(const std::vector<tinyobj::shape_t>& shapes, const std::vector<tinyobj::material_t>& materials) {
  std::cout << "# of shapes    : " << shapes.size() << std::endl;
  std::cout << "# of materials : " << materials.size() << std::endl;

  for (size_t i = 0; i < shapes.size(); i++) {
    printf("shape[%ld].name = %s\n", i, shapes[i].name.c_str());
    printf("Size of shape[%ld].indices: %ld\n", i, shapes[i].mesh.indices.size());
    //printf("Size of shape[%ld].material_ids: %ld\n", i, shapes[i].mesh.material_ids.size());
    assert((shapes[i].mesh.indices.size() % 3) == 0);
    for (size_t f = 0; f < shapes[i].mesh.indices.size() / 3; f++) {
      printf("  idx[%ld] = %d, %d, %d\n", f, shapes[i].mesh.indices[3 * f + 0], shapes[i].mesh.indices[3 * f + 1], shapes[i].mesh.indices[3 * f + 2]);
    }

    printf("shape[%ld].vertices: %ld\n", i, shapes[i].mesh.positions.size());
    assert((shapes[i].mesh.positions.size() % 3) == 0);
    for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
      printf("  v[%ld] = (%f, %f, %f)\n", v, shapes[i].mesh.positions[3 * v + 0], shapes[i].mesh.positions[3 * v + 1], shapes[i].mesh.positions[3 * v + 2]);
    }
  }

  /*for (size_t i = 0; i < materials.size(); i++) {
    printf("material[%ld].name = %s\n", i, materials[i].name.c_str());
    printf("  material.Ka = (%f, %f ,%f)\n", materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2]);
    printf("  material.Kd = (%f, %f ,%f)\n", materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2]);
    printf("  material.Ks = (%f, %f ,%f)\n", materials[i].specular[0], materials[i].specular[1], materials[i].specular[2]);
    printf("  material.Tr = (%f, %f ,%f)\n", materials[i].transmittance[0], materials[i].transmittance[1], materials[i].transmittance[2]);
    printf("  material.Ke = (%f, %f ,%f)\n", materials[i].emission[0], materials[i].emission[1], materials[i].emission[2]);
    printf("  material.Ns = %f\n", materials[i].shininess);
    printf("  material.Ni = %f\n", materials[i].ior);
    printf("  material.dissolve = %f\n", materials[i].dissolve);
    printf("  material.illum = %d\n", materials[i].illum);
    printf("  material.map_Ka = %s\n", materials[i].ambient_texname.c_str());
    printf("  material.map_Kd = %s\n", materials[i].diffuse_texname.c_str());
    printf("  material.map_Ks = %s\n", materials[i].specular_texname.c_str());
    printf("  material.map_Ns = %s\n", materials[i].specular_highlight_texname.c_str());
    printf("  material.map_bump = %s\n", materials[i].bump_texname.c_str());
    printf("  material.map_d = %s\n", materials[i].alpha_texname.c_str());
    printf("  material.disp = %s\n", materials[i].displacement_texname.c_str());
    std::map<std::string, std::string>::const_iterator it(materials[i].unknown_parameter.begin());
    std::map<std::string, std::string>::const_iterator itEnd(materials[i].unknown_parameter.end());
    for (; it != itEnd; it++) {
      printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
    }
    printf("\n");
  }*/
}

void ROTOM::MESHLOADER::Load_OBJ(const char *pathWithoutExtensionFile, Geometry *geometry, bool reloadFile) {
  //printf(".................................\n");
  //ROTOM::TIME::Chronometer t_load_OBJ, t_save_from_OBJ_to_ROTOM, t_load_ROTOM;
  char basePath[256];
  char finalPath[256];
  char newPath[256];
  const char *old_ext = ".obj";
  const char *new_ext = ".rotom";
  std::shared_ptr<Geometry::GeometryData> obj_data = std::shared_ptr<Geometry::GeometryData>(new Geometry::GeometryData());

  obj_data->data.clear();
  obj_data->index.clear();

  strcpy(basePath, kPath_objFiles);
  strcat(basePath, pathWithoutExtensionFile);

  strcpy(finalPath, basePath);
  strcat(finalPath, old_ext);

  strcpy(newPath, basePath);
  strcat(newPath, new_ext);

  if (reloadFile) {
    //printf(".Loading OBJ  : ");
    //t_load_OBJ.start();

    float aux_value_x = 0.0f;
    float aux_value_y = 0.0f;
    float aux_value_z = 0.0f;
    int size_x = 1;
    int size_y = 1;
    int size_z = 1;

    //true = will make the obj to be in the position (0, 0, 0) - (aux_value_x, aux_value_y, aux_value_z)
    //false = will make the obj to start in the first position that have in the file
    bool aux_init = false;

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::fvec3> temp_vertices, temp_normals;
    std::vector<glm::fvec2> temp_uvs;

    FILE *file = fopen(finalPath, "r");
    if (file == nullptr){
      assert("ERROR: File doesn't found\n" && false);
    } else {
      while (true) {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
          break; // EOF = End Of File. Quit the loop.
        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0){
          glm::fvec3 vertex;
          int matches = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
          if (matches < 3) {
            printf("ERROR: v[%d]\n", matches);
          }
          if (!aux_init){
            aux_init = true;
            aux_value_x = vertex.x;
            aux_value_y = vertex.y;
            aux_value_z = vertex.z;
          }
          vertex.x -= aux_value_x;
          vertex.y -= aux_value_y;
          vertex.z -= aux_value_z;
          vertex.x *= size_x;
          vertex.y *= size_y;
          vertex.z *= size_z;
          temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0){
          glm::fvec2 uv;
          int matches = fscanf(file, "%f %f\n", &uv.x, &uv.y);
          if (matches < 2) {
            printf("ERROR: vt[%d]\n", matches);
          }
          temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0){
          glm::fvec3 normal;
          int matches = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
          if (matches < 3) {
            printf("ERROR: uv[%d]\n", matches);
          }
          temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0){
          unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
          int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
          if (matches != 9 && matches != 2 && matches != 1){
            printf("ERROR: matches [%d]\n", matches);
          }
          switch (matches) {
            case 9:
              vertexIndices.push_back(vertexIndex[0]);
              vertexIndices.push_back(vertexIndex[1]);
              vertexIndices.push_back(vertexIndex[2]);
              uvIndices.push_back(uvIndex[0]);
              uvIndices.push_back(uvIndex[1]);
              uvIndices.push_back(uvIndex[2]);
              normalIndices.push_back(normalIndex[0]);
              normalIndices.push_back(normalIndex[1]);
              normalIndices.push_back(normalIndex[2]);
              break;
            case 2:
              vertexIndices.push_back(vertexIndex[0]);
              uvIndices.push_back(uvIndex[0]);
              matches = fscanf(file, " %d/%d %d/%d\n", &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
              vertexIndices.push_back(vertexIndex[1]);
              vertexIndices.push_back(vertexIndex[2]);
              uvIndices.push_back(uvIndex[0]);
              uvIndices.push_back(uvIndex[1]);
              uvIndices.push_back(uvIndex[2]);
              normalIndices.push_back(-1);
              normalIndices.push_back(-1);
              normalIndices.push_back(-1);
              break;
            case 1:
              vertexIndices.push_back(vertexIndex[0]);
              matches = fscanf(file, "/%d %d//%d %d//%d\n", &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);

              if (matches == 5){
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices.push_back(1);
                uvIndices.push_back(1);
                uvIndices.push_back(1);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
              } else {
                matches = fscanf(file, " %d %d\n", &vertexIndex[1], &vertexIndex[2]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices.push_back(1);
                uvIndices.push_back(1);
                uvIndices.push_back(1);
                normalIndices.push_back(-1);
                normalIndices.push_back(-1);
                normalIndices.push_back(-1);
              }
              break;
            default:
              printf("ERROR: f[%d]\n", matches);
              //return false;
              break;
          }
        }
      }

      ////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////
      //Transform Input
      glm::fvec3 vertex;
      glm::fvec3 normales;
      glm::fvec2 uv;
      std::vector<glm::fvec3> out_vertex;
      std::vector<glm::fvec2> out_uv;
      std::vector<glm::fvec3> out_normal;
      for (unsigned int i = 0; i < vertexIndices.size(); ++i){
        //Position
        vertex = temp_vertices[vertexIndices[i] - 1];
        out_vertex.push_back(vertex);

        //Normales
        if (temp_normals.size() >= normalIndices[i]) {
          normales = temp_normals[normalIndices[i] - 1];
        } else {
          normales.x = 0;
          normales.y = 0;
          normales.z = 1;
        }
        out_normal.push_back(normales);

        //UV
        if (temp_uvs.size() >= uvIndices[i]) {
          uv = temp_uvs[uvIndices[i] - 1];
        } else {
          uv.x = 0;
          uv.y = 0;
        }
        out_uv.push_back(uv);
      }
      ////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////



      ////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////
      //Data Output
      const int vertexSize = 3 + 3 + 2;
      for (unsigned int i = 0; i < out_vertex.size(); ++i) {
        int index = i * vertexSize;

        //Positions
        obj_data->data.push_back(out_vertex[i].x);
        obj_data->data.push_back(out_vertex[i].y);
        obj_data->data.push_back(out_vertex[i].z);

        //Normals
        obj_data->data.push_back(out_normal[i].x);
        obj_data->data.push_back(out_normal[i].y);
        obj_data->data.push_back(out_normal[i].z);

        //UVs
        obj_data->data.push_back(out_uv[i].x);
        obj_data->data.push_back(out_uv[i].y);
      }
      ////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////



      ////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////
      //Index Output
      for (unsigned int i = 0; i < vertexIndices.size(); ++i) {
        obj_data->index.push_back(i);
      }
      ////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////



      ////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////
      //Debug log
      bool debug = false;
      if (false) {
        //Vertex
        for (unsigned int i = 0; i < out_vertex.size(); ++i) {
          int index = i * vertexSize;
          printf("[%f %f %f][%f %f %f][%.3f %.3f]\n",
            obj_data->data.at(index + 0), obj_data->data.at(index + 1), obj_data->data.at(index + 2), //Positions
            obj_data->data.at(index + 3), obj_data->data.at(index + 4), obj_data->data.at(index + 5), //Normals
            obj_data->data.at(index + 6), obj_data->data.at(index + 7)); //UVs
        }

        //Index
        for (unsigned int i = 0; i < vertexIndices.size(); ++i) {
          if (i % 3 == 0) {
            printf("\nIndex position %d", obj_data->index.at(i));
          } else {
            printf("/%d", obj_data->index.at(i));
          }
        }
      }
      ////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////

      //Restart the static values
      aux_value_x = 0;
      aux_value_y = 0;
      aux_value_z = 0;
      aux_init = false;
    }
    //printf("%f seconds.\n", t_load_OBJ.end());

    //printf(".OBJ to ROTOM : ");
    //t_save_from_OBJ_to_ROTOM.start();
    Save_ROTOM_OBJ(newPath, obj_data);
    //printf("%f seconds.\n", t_save_from_OBJ_to_ROTOM.end());
  }

  //printf(".Loading ROTOM: ");
  //t_load_ROTOM.start();
  Load_ROTOM_OBJ(newPath, obj_data);
  //printf("%f seconds.\n", t_load_ROTOM.end());
  //printf(".................................\n");

  geometry->loadGeometry(obj_data);
}

void ROTOM::MESHLOADER::Load_OBJ(const char* path, const char* nameWithoutExtension, Geometry *geometry, bool reloadFile) {
  //printf(".................................\n");
  //ROTOM::TIME::Chronometer t_load_OBJ, t_save_from_OBJ_to_ROTOM, t_load_ROTOM;
  char basePath[256];
  char finalPath[256];
  char newPath[256];
  const char *old_ext = ".obj";
  const char *new_ext = ".rotom";
  std::shared_ptr<Geometry::GeometryData> obj_data = std::shared_ptr<Geometry::GeometryData>(new Geometry::GeometryData());

  obj_data->data.clear();
  obj_data->index.clear();

  strcpy(basePath, kPath_objFiles);
  strcat(basePath, path);

  strcpy(finalPath, basePath);
  strcat(finalPath, nameWithoutExtension);
  strcat(finalPath, old_ext);

  strcpy(newPath, basePath);
  strcat(newPath, nameWithoutExtension);
  strcat(newPath, new_ext);

  if (reloadFile) {
    //printf(".Loading OBJ  : ");
    //t_load_OBJ.start();
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err = tinyobj::LoadObj(shapes, materials, finalPath, basePath);

    if (!err.empty()) {
      printf("ERROR [meshLoader.cc] > Load_OBJ()\n\n");
      std::cerr << err << std::endl;
      system("pause");
    } else {
      //PrintInfo(shapes, materials);

      for (size_t shape = 0; shape < shapes.size(); shape++) {
        //Index
        for (size_t index = 0; index < shapes[shape].mesh.indices.size(); ++index) {
          obj_data->index.push_back(shapes[shape].mesh.indices[index]);
        }

        //Vector
        for (size_t position = 0; position < shapes[shape].mesh.positions.size() / 3; ++position) {
          //Positions
          obj_data->data.push_back(shapes[shape].mesh.positions[3 * position + 0]);
          obj_data->data.push_back(shapes[shape].mesh.positions[3 * position + 1]);
          obj_data->data.push_back(shapes[shape].mesh.positions[3 * position + 2]);

          //Normals
          if (shapes[shape].mesh.normals.size() > position * 3 + 2) {
            obj_data->data.push_back(shapes[shape].mesh.normals[3 * position + 0]);
            obj_data->data.push_back(shapes[shape].mesh.normals[3 * position + 1]);
            obj_data->data.push_back(shapes[shape].mesh.normals[3 * position + 2]);
          } else {
            obj_data->data.push_back(1.0f);
            obj_data->data.push_back(1.0f);
            obj_data->data.push_back(1.0f);
          }

          //UV
          if (shapes[shape].mesh.texcoords.size() > position * 2 + 1) {
            obj_data->data.push_back(shapes[shape].mesh.texcoords[2 * position + 0]);
            obj_data->data.push_back(shapes[shape].mesh.texcoords[2 * position + 1]);
          } else {
            obj_data->data.push_back(1.0f);
            obj_data->data.push_back(1.0f);
          }
        }
      }
    }
    //printf("%f seconds.\n", t_load_OBJ.end());

    //printf(".OBJ to ROTOM : ");
    //t_save_from_OBJ_to_ROTOM.start();
    Save_ROTOM_OBJ(newPath, obj_data);
    //printf("%f seconds.\n", t_save_from_OBJ_to_ROTOM.end());
  }

  //printf(".Loading ROTOM: ");
  //t_load_ROTOM.start();
  Load_ROTOM_OBJ(newPath, obj_data);
  //printf("%f seconds.\n", t_load_ROTOM.end());
  //printf(".................................\n");

  geometry->loadGeometry(obj_data);
}

void ROTOM::MESHLOADER::Load_ROTOM_OBJ(const char *path, std::shared_ptr<Geometry::GeometryData> obj_data) {
  obj_data->data.clear();
  obj_data->index.clear();

  FILE *file = fopen(path, "rb");
  if (file) {
    //IndexCount
    int indexCount = -1;
    fread(&indexCount, sizeof(int), 1, file);

    //DataCount
    int dataCount = -1;
    fread(&dataCount, sizeof(int), 1, file);

    //Index
    int indexAux = 0;
    for (int i = 0; i < indexCount; ++i) {
      fread(&indexAux, sizeof(int), 1, file);
      obj_data->index.push_back(indexAux);
    }
    
    //Data
    float dataAux = -1.0f;
    for (int i = 0; i < dataCount; ++i) {
      fread(&dataAux, sizeof(float), 1, file);
      obj_data->data.push_back(dataAux);
    }
    fclose(file);
  }
}

void ROTOM::MESHLOADER::Save_ROTOM_OBJ(const char *path, std::shared_ptr<Geometry::GeometryData> obj_data) {
  FILE *file = fopen(path, "wb");
  if (file) {
    int indexCount = obj_data->index.size();
    int dataCount = obj_data->data.size();

    //IndexCount
    fwrite(&indexCount, sizeof(int), 1, file);

    //DataCount
    fwrite(&dataCount, sizeof(int), 1, file);

    //Index
    for (int i = 0; i < indexCount; ++i) {
      fwrite(&obj_data->index.at(i), sizeof(int), 1, file);
    }

    //Data
    for (int i = 0; i < dataCount; ++i) {
      fwrite(&obj_data->data.at(i), sizeof(float), 1, file);
    }
    fclose(file);
  }
}
