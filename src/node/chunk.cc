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

#define CHUNK_SIDE 4
#define VERTEX_SIDE 32
#define INDEX_SIDE 6
#define AREA_CHUNK_SIDE (CHUNK_SIDE * CHUNK_SIDE)
#define GEOMETRY_VERTEX_SIDE (VERTEX_SIDE * AREA_CHUNK_SIDE)
#define GEOMETRY_INDEX_SIDE (INDEX_SIDE * AREA_CHUNK_SIDE)

struct ChunkGlobalData {
  ChunkGlobalData() {
    maxHeight = 256;
    amountOfChange = 0.01f;
  }

  std::shared_ptr<ROTOM::Drawable> drawable;
  std::shared_ptr<ROTOM::Geometry> geometry;
  std::shared_ptr<ROTOM::Material> material;
  ROTOM::Camera *camera;

  int maxHeight;
  float amountOfChange;

} chunkGlobalData;

static float chunkVertex[GEOMETRY_VERTEX_SIDE] = {
  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
  0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
};

static int chunkIndex[GEOMETRY_INDEX_SIDE] = {
  0, 1, 3,
  1, 2, 3,
};

const int stepPos1X =      0, stepPos1Y =      1, stepPos1Z =      2;
const int stepPos2X =  8 + 0, stepPos2Y =  8 + 1, stepPos2Z =  8 + 2;
const int stepPos3X = 16 + 0, stepPos3Y = 16 + 1, stepPos3Z = 16 + 2;
const int stepPos4X = 24 + 0, stepPos4Y = 24 + 1, stepPos4Z = 24 + 2;

void ROTOM::Chunk::init(std::shared_ptr<Node> parent, Camera *camera, unsigned int maxHeight) {
  chunkGlobalData.camera = camera;
  chunkGlobalData.maxHeight = maxHeight;
  
  chunkGlobalData.material = std::shared_ptr<Material>(new Material());
  chunkGlobalData.material->setShaderFromPath("shadows/1_Basic.vertx", "shadows/1_Basic.frag");
  
  chunkGlobalData.geometry = std::shared_ptr<Geometry>(new Geometry());
  chunkGlobalData.geometry->loadGeometry(chunkVertex, chunkIndex, GEOMETRY_VERTEX_SIDE);
  for (unsigned int i = 0; i < AREA_CHUNK_SIDE; ++i) {
    //Vertex
    for (unsigned int j = 0; j < VERTEX_SIDE; ++j) {
      chunkVertex[i * VERTEX_SIDE + j] = chunkVertex[j];
    }

    //Index
    for (unsigned int j = 0; j < INDEX_SIDE; ++j) {
      chunkIndex[i * INDEX_SIDE + j] = chunkIndex[j] + (i * 4);
    }
  }
  updateGeometry();

  chunkGlobalData.drawable = std::shared_ptr<Drawable>(new Drawable("Drawable"));
  chunkGlobalData.drawable->setParent(parent);
  chunkGlobalData.drawable->setMaterial(chunkGlobalData.material);
  chunkGlobalData.drawable->setMaterialSettings(std::shared_ptr<MaterialSettings>(new MaterialSettings()));
  chunkGlobalData.drawable->setGeometry(chunkGlobalData.geometry);

  float pos[3] = { 0.0f, 0.0f, 0.0f };
  pos[0] = chunkGlobalData.camera->position()[0];
  pos[2] = chunkGlobalData.camera->position()[2];
  pos[1] = PROCEDURAL::perlinNoise(pos[0], 0.0f, pos[2]);
  chunkGlobalData.drawable->setPosition(pos);
}

void ROTOM::Chunk::update() {
  if (INPUT::IsKeyDown('W') || INPUT::IsKeyDown('A') || INPUT::IsKeyDown('S') || INPUT::IsKeyDown('D')) {
    //chunkGlobalData.drawable->setPosition(
    //  chunkGlobalData.camera->position()[0],
    //  PROCEDURAL::perlinNoise(chunkGlobalData.camera->position()[0], 1.0f, chunkGlobalData.camera->position()[2]),
    //  chunkGlobalData.camera->position()[2]);
    updateGeometry();
  }
}

void ROTOM::Chunk::setMaxHeight(unsigned int maxHeight) {
  chunkGlobalData.maxHeight = maxHeight;
}

void ROTOM::Chunk::updateGeometry() {
  chunkGlobalData.geometry->loadGeometry(chunkVertex, chunkIndex, AREA_CHUNK_SIDE);
  int totalStep = 0;
  float camPosX = chunkGlobalData.camera->position()[0];
  float camPosZ = chunkGlobalData.camera->position()[2] + CHUNK_SIDE;

  //camPosX = 0.0f;
  //camPosZ = 0.0f;
  for (unsigned int z = 0; z < CHUNK_SIDE; ++z) {
    for (unsigned int x = 0; x < CHUNK_SIDE; ++x) {
      chunkVertex[stepPos1X + totalStep] = camPosX + x + 1;
      chunkVertex[stepPos1Z + totalStep] = camPosZ + z + 0;
      chunkVertex[stepPos1Y + totalStep] = PROCEDURAL::perlinNoise(chunkVertex[stepPos1X + totalStep], 0.0f, chunkVertex[stepPos1Z + totalStep]);
      printf("%0.2f %0.2f %0.2f\n", chunkVertex[stepPos1X + totalStep], chunkVertex[stepPos1Y + totalStep], chunkVertex[stepPos1Z + totalStep]);

      chunkVertex[stepPos2X + totalStep] = camPosX + x + 1;
      chunkVertex[stepPos2Z + totalStep] = camPosZ + z + 1;
      chunkVertex[stepPos2Y + totalStep] = PROCEDURAL::perlinNoise(chunkVertex[stepPos2X + totalStep], 0.0f, chunkVertex[stepPos2Z + totalStep]);
      printf("%0.2f %0.2f %0.2f\n", chunkVertex[stepPos2X + totalStep], chunkVertex[stepPos2Y + totalStep], chunkVertex[stepPos2Z + totalStep]);

      chunkVertex[stepPos3X + totalStep] = camPosX + x + 0;
      chunkVertex[stepPos3Z + totalStep] = camPosZ + z + 1;
      chunkVertex[stepPos3Y + totalStep] = PROCEDURAL::perlinNoise(chunkVertex[stepPos3X + totalStep], 0.0f, chunkVertex[stepPos3Z + totalStep]);
      printf("%0.2f %0.2f %0.2f\n", chunkVertex[stepPos3X + totalStep], chunkVertex[stepPos3Y + totalStep], chunkVertex[stepPos3Z + totalStep]);

      chunkVertex[stepPos4X + totalStep] = camPosX + x + 0;
      chunkVertex[stepPos4Z + totalStep] = camPosZ + z + 0;
      chunkVertex[stepPos4Y + totalStep] = PROCEDURAL::perlinNoise(chunkVertex[stepPos4X + totalStep], 0.0f, chunkVertex[stepPos4Z + totalStep]);
      printf("%0.2f %0.2f %0.2f\n", chunkVertex[stepPos4X + totalStep], chunkVertex[stepPos4Y + totalStep], chunkVertex[stepPos4Z + totalStep]);
      totalStep += VERTEX_SIDE;
    }
  }
}

//https://www.youtube.com/watch?v=-K8QNpzgKUY