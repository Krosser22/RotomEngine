/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/chunk.h"
#include "render/graphics.h"
#include "general/input.h"
#include "general/procedural.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <imgui.h>

float distance = 0.1f;
const int chunkSide = 70;
const int vertexSide = 32;
const int indexSide = 6;
const int areaChunkSide = (chunkSide * chunkSide);
const int geometryVertexSide = (vertexSide * areaChunkSide);
const int geometryIndexSide = (indexSide * areaChunkSide);

struct ChunkGlobalData {
  ChunkGlobalData() {
    perlinHeight = 0.8f;
    maxHeight = 256;
    amountOfChange = 0.01f;
  }

  std::shared_ptr<ROTOM::Drawable> drawable;
  std::shared_ptr<ROTOM::Geometry> geometry;
  std::shared_ptr<ROTOM::Material> material;
  std::shared_ptr<ROTOM::MaterialSettings> materialSettings;
  ROTOM::Camera *camera;
  float perlinHeight;
  int maxHeight;
  float amountOfChange;

  float chunkVertex[geometryVertexSide];
  int chunkIndex[geometryIndexSide];

} chunkGlobalData;

float chunkV[vertexSide] = {
  distance, 0.0f,     0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
  distance, 0.0f, distance, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
      0.0f, 0.0f, distance, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      0.0f, 0.0f,     0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f
};

int chunkI[indexSide] = {
  0, 1, 3,
  1, 2, 3
};

static bool isInitialized = false;
void ROTOM::Chunk::init(std::shared_ptr<Node> parent, Camera *camera, unsigned int maxHeight) {
  if (isInitialized) {
    //Data
    chunkGlobalData.camera = camera;
    chunkGlobalData.maxHeight = maxHeight;

    //Material
    chunkGlobalData.material = std::shared_ptr<Material>(new Material("../../../../img/no_texture.png"));
    chunkGlobalData.material->setShaderFromPath("basics/4_SpecularLight.vertx", "basics/4_SpecularLight.frag");
    chunkGlobalData.material->setShaderFromPath("terrain.vertx", "terrain.frag");

    chunkGlobalData.materialSettings = std::shared_ptr<MaterialSettings>(new MaterialSettings());

    //Geometry
    chunkGlobalData.geometry = std::shared_ptr<Geometry>(new Geometry());
    chunkGlobalData.geometry->loadGeometry(chunkGlobalData.chunkVertex, chunkGlobalData.chunkIndex, geometryIndexSide);
    for (unsigned int i = 0; i < areaChunkSide; ++i) {
      //Vertex
      for (unsigned int j = 0; j < vertexSide; ++j) {
        chunkGlobalData.chunkVertex[i * vertexSide + j] = chunkV[j];
      }

      //Index
      for (unsigned int k = 0; k < indexSide; ++k) {
        chunkGlobalData.chunkIndex[i * indexSide + k] = chunkI[k] + (i * 4);
      }
    }

    //Drawable
    chunkGlobalData.drawable = std::shared_ptr<Drawable>(new Drawable("Drawable"));
    chunkGlobalData.drawable->setParent(parent);
    chunkGlobalData.drawable->setGeometry(chunkGlobalData.geometry);
    chunkGlobalData.drawable->setMaterial(chunkGlobalData.material);
    chunkGlobalData.drawable->setMaterialSettings(chunkGlobalData.materialSettings);
    chunkGlobalData.drawable->setPosition(0.0f, 0.0f, 22.0f);

    updateGeometry();
  }
  isInitialized = true;
}

void ROTOM::Chunk::update() {
  if (INPUT::IsKeyDown('W') || INPUT::IsKeyDown('A') || INPUT::IsKeyDown('S') || INPUT::IsKeyDown('D') || INPUT::IsMouseDown(1)) {
    updateGeometry();
    chunkGlobalData.camera->setPositionY(1 + PROCEDURAL::perlinNoise(chunkGlobalData.camera->position()[0], chunkGlobalData.perlinHeight, chunkGlobalData.camera->position()[2]));
  }
  ImGui::DragFloat("Distance", &distance, 0.02f, 0.0f, 1.0f, "%.03f", 0.02f);
}

void ROTOM::Chunk::setMaxHeight(unsigned int maxHeight) {
  chunkGlobalData.maxHeight = maxHeight;
}

void ROTOM::Chunk::updateGeometry() {
  static const int stepPos1X = 0, stepPos1Y = 1, stepPos1Z = 2;
  static const int stepPos2X = 8, stepPos2Y = 9, stepPos2Z = 10;
  static const int stepPos3X = 16, stepPos3Y = 17, stepPos3Z = 18;
  static const int stepPos4X = 24, stepPos4Y = 25, stepPos4Z = 26;

  int totalStep = 0;
  float camPosX = chunkGlobalData.camera->position()[0] - (chunkSide * distance) / 2;
  float camPosZ = chunkGlobalData.camera->position()[2] - (chunkSide * distance) / 2;

  float stepX = 0.0f, stepZ = 0.0f;
  for (unsigned int z = 0; z < chunkSide; ++z) {
    stepX = 0.0f;
    for (unsigned int x = 0; x < chunkSide; ++x) {
      chunkGlobalData.chunkVertex[stepPos1X + totalStep] = stepX + distance;
      chunkGlobalData.chunkVertex[stepPos1Z + totalStep] = stepZ;
      chunkGlobalData.chunkVertex[stepPos1Y + totalStep] = getHeight(camPosX + stepX + distance, chunkGlobalData.perlinHeight, camPosZ + stepZ);

      chunkGlobalData.chunkVertex[stepPos2X + totalStep] = stepX + distance;
      chunkGlobalData.chunkVertex[stepPos2Z + totalStep] = stepZ + distance;
      chunkGlobalData.chunkVertex[stepPos2Y + totalStep] = getHeight(camPosX + stepX + distance, chunkGlobalData.perlinHeight, camPosZ + stepZ + distance);

      chunkGlobalData.chunkVertex[stepPos3X + totalStep] = stepX;
      chunkGlobalData.chunkVertex[stepPos3Z + totalStep] = stepZ + distance;
      chunkGlobalData.chunkVertex[stepPos3Y + totalStep] = getHeight(camPosX + stepX, chunkGlobalData.perlinHeight, camPosZ + stepZ + distance);

      chunkGlobalData.chunkVertex[stepPos4X + totalStep] = stepX;
      chunkGlobalData.chunkVertex[stepPos4Z + totalStep] = stepZ;
      chunkGlobalData.chunkVertex[stepPos4Y + totalStep] = getHeight(camPosX + stepX, chunkGlobalData.perlinHeight, camPosZ + stepZ);
      totalStep += vertexSide;
      stepX += distance;
    }
    stepZ += distance;
  }
  chunkGlobalData.drawable->setPosition(camPosX, 0.0f, camPosZ);
  chunkGlobalData.geometry->loadGeometry(chunkGlobalData.chunkVertex, chunkGlobalData.chunkIndex, geometryIndexSide);
}

float ROTOM::Chunk::getHeight(float x, float y, float z) {

  // Typical Perlin noise
  //double n = pn.noise(10 * x, 10 * y, 0.8);

  double n = PROCEDURAL::perlinNoise(10.0f * x, y, 10.0f * z);
  // Wood like structure
  n = 20.0f * PROCEDURAL::perlinNoise(x, y, z);
  n = n - floor(n);

  // Map the values to the [0, 255] interval, for simplicity we use 
  // tones of grey
  /*image.r[kk] = floor(255 * n);
  image.g[kk] = floor(255 * n);
  image.b[kk] = floor(255 * n);
  kk++;*/
  //chunkGlobalData.drawable->materialSettings()->setColor(floor(1 * n), floor(1 * n), floor(1 * n));

  /*if ((block_start_x > 22 || block_start_x < -22) || (block_start_z > 22 || block_start_z < -22)) {
    int texture_temp = (int)floor(texture_count_of_procedural_map_ * n);
    //printf("%d, %d, %d, %d\n", i, texture_temp, j, texture_temp, texture_temp, texture_temp);
    add(i, (int)floor(height_ * n), j, texture_temp, texture_temp, texture_temp);
  }*/

  return PROCEDURAL::perlinNoise(x, y, z);
}

//https://www.youtube.com/watch?v=-K8QNpzgKUY