/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "obj_loader.h"
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

static int aux_value_x = 0;
static int aux_value_y = 0;
static int aux_value_z = 0;
static bool aux_init = false;

bool Obj_loader::init(const char *path, int size_x, int size_y, int size_z) {
  aux_value_x = 0;
  aux_value_y = 0;
  aux_value_z = 0;
  aux_init = false;
  unsigned int size_vertex_ = 0;
  unsigned int size_normal_ = 0;
  unsigned int size_uv_ = 0;
  unsigned int size_index_ = 0;
  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
  std::vector<glm::vec3> temp_vertices, temp_normals;
  std::vector<glm::vec2> temp_uvs;

  FILE *file = fopen(path, "r");
  if (file == NULL){
    printf("ERROR: File doesn't found\n");
    return false;
  }
  
  while (1){
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
      break; // EOF = End Of File. Quit the loop.
    // else : parse lineHeader

    if (strcmp(lineHeader, "v") == 0){
      glm::vec3 vertex;
      int matches = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
      if (matches < 3) {
        printf("ERROR: v[%d]\n", matches);
      }
      if (!aux_init){
        aux_init = true;
        aux_value_x = (int)vertex.x;
        aux_value_y = (int)vertex.y;
        aux_value_z = (int)vertex.z;
      }
      vertex.x -= aux_value_x;
      vertex.y -= aux_value_y;
      vertex.z -= aux_value_z;
      vertex.x *= size_x;
      vertex.y *= size_y;
      vertex.z *= size_z;
      temp_vertices.push_back(vertex);
    } else if (strcmp(lineHeader, "vt") == 0){
      glm::vec2 uv;
      int matches = fscanf(file, "%f %f\n", &uv.x, &uv.y);
      if (matches < 2) {
        printf("ERROR: vt[%d]\n", matches);
      }
      temp_uvs.push_back(uv);
    } else if (strcmp(lineHeader, "vn") == 0){
      glm::vec3 normal;
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
          return false;
          break;
      }
    }
  }
  
  //TRANSFORM !!!!
  std::vector<glm::vec3> out_vertices;
  for (unsigned int i = 0; i < vertexIndices.size(); ++i){
    unsigned int vertexIndex = vertexIndices[i];
    glm::vec3 vertex = temp_vertices[vertexIndex - 1];
    out_vertices.push_back(vertex);
    if (debug) printf("position %f %f %f\n", out_vertices[i].x, out_vertices[i].y, out_vertices[i].z);
  }
  if (debug) printf("\n");
  std::vector<glm::vec2> out_uv;
  for (unsigned int i = 0; i < uvIndices.size(); ++i){
    unsigned int uvIndex = uvIndices[i];
    glm::vec2 uv;
    if (temp_uvs.size() >= uvIndex) {
      uv = temp_uvs[uvIndex - 1];
    } else {
      uv.x = 0;
      uv.y = 0;
    }
    out_uv.push_back(uv);
    if (debug) printf("uv %f %f\n", out_uv[i].x, out_uv[i].y);
  }
  if (debug) printf("\n");
  std::vector<glm::vec3> out_normales;
  for (unsigned int i = 0; i < normalIndices.size(); ++i){
    unsigned int normalesIndex = normalIndices[i];
    glm::vec3 normales;
    if (temp_normals.size() >= normalesIndex) {
      normales = temp_normals[normalesIndex - 1];
    } else {
      normales.x = 0;
      normales.y = 0;
      normales.z = 1;
    }
    out_normales.push_back(normales);
    if (debug) printf("normales %f %f %f\n", out_normales[i].x, out_normales[i].y, out_normales[i].z);
  }
  if (debug) printf("\n");

  //DATA
  size_uv_ = out_vertices.size() * 3;
  size_normal_ = out_vertices.size() * 3 + out_uv.size() * 2;
  unsigned int data_length = out_vertices.size() * 3 + out_uv.size() * 2 + out_normales.size() * 3;
  float *data = new float[data_length];
  for (unsigned int i = 0; i < out_vertices.size(); ++i) {
    data[i * 3] = out_vertices[i].x;
    data[i * 3 + 1] = out_vertices[i].y;
    data[i * 3 + 2] = out_vertices[i].z;
    if(debug) printf("f_position %f %f %f\n", data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
  }
  if (debug) printf("\n");
  for (unsigned int i = 0; i < out_uv.size(); ++i) {
    data[out_vertices.size() * 3 + i * 2] = out_uv[i].x;
    data[out_vertices.size() * 3 + i * 2 + 1] = out_uv[i].y;
    if (debug) printf("f_uv %f %f\n", data[out_vertices.size() * 3 + i * 2], data[out_vertices.size() * 3 + i * 2 + 1]);
  }
  if (debug) printf("\n");
  for (unsigned int i = 0; i < out_normales.size(); ++i) {
    data[out_vertices.size() * 3 + out_uv.size() * 2 + i * 3] = out_normales[i].x;
    data[out_vertices.size() * 3 + out_uv.size() * 2 + i * 3 + 1] = out_normales[i].y;
    data[out_vertices.size() * 3 + out_uv.size() * 2 + i * 3 + 2] = out_normales[i].z;
    if (debug) printf("f_normales %f %f %f\n", data[out_vertices.size() * 3 + out_uv.size() * 2 + i * 3], data[out_vertices.size() * 3 + out_uv.size() * 2 + i * 3 + 1], data[out_vertices.size() * 3 + out_uv.size() * 2 + i * 3 + 2]);
  }
  //EDK3::dev::GPUManager::Instance()->newBuffer(&buffer_data_);
  //buffer_data_->init(data_length * 4);
  //buffer_data_->uploadData(data, data_length * 4, 0);

  /*for (unsigned int i = 0; i < data_length; ++i) {
    printf("%f\n", data[i]);
  }*/

  //INDEX
  size_index_ = vertexIndices.size();
  unsigned int *index = new unsigned int[size_index_];

  for (unsigned int i = 0; i < vertexIndices.size(); ++i) {
    index[i] = i;
    if (debug) if (i % 3 == 0) {
      printf("\nIndex position %d", index[i]);
    } else {
      printf("/%d", index[i]);
    }
  }
  //EDK3::dev::GPUManager::Instance()->newBuffer(&buffer_index_);
  //buffer_index_->init(size_index_ * 4);
  //buffer_index_->uploadData(index, size_index_ * 4, 0);

  /*for (unsigned int i = 0; i < size_index_; ++i) {
    printf("%d\n", index[i]);
  }*/
  return true;
}