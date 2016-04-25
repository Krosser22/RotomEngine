/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/chunk.h"
#include "render/graphics.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

struct ChunkGlobalData {
  ChunkGlobalData() {
    maxRows = 32;
    maxCols = 32;
    rows = 32;
    cols = 32;
    maxHeight = 256;
  }
  int maxRows;
  int maxCols;
  int rows;
  int cols;
  int maxHeight;
  std::vector<std::shared_ptr<ROTOM::Drawable>> drawables;
} chunkGlobalData;

ROTOM::Chunk::Chunk() {}

ROTOM::Chunk::Chunk(char *name) {}

ROTOM::Chunk::~Chunk() {
  chunkGlobalData.drawables.clear();
}

void ROTOM::Chunk::init(unsigned int rows, unsigned int cols, unsigned int maxHeight) {
  chunkGlobalData.rows = rows;
  chunkGlobalData.cols = cols;
  chunkGlobalData.maxHeight = maxHeight;
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  std::shared_ptr<MaterialSettings> materialSettings = std::shared_ptr<MaterialSettings>(new MaterialSettings());
  std::shared_ptr<Geometry> geometry = std::shared_ptr<Geometry>(new Geometry());
  
  for (int i = 0; i < (float)chunkGlobalData.maxCols * chunkGlobalData.maxRows; ++i) {
    std::shared_ptr<Drawable> drawable = std::shared_ptr<Drawable>(new Drawable("Drawable"));
    chunkGlobalData.drawables.push_back(drawable);
    drawable->setMaterial(material);
    drawable->setMaterialSettings(materialSettings);
    drawable->setGeometry(geometry);
  }

  const float separation = 1.0f;
  float pos[3] = { 0.0f, 0.0f, 0.0f };
  for (unsigned int i = 0; i < chunkGlobalData.drawables.size(); ++i) {
    pos[0] = (i % chunkGlobalData.maxCols) * separation;
    pos[1] = (i / (chunkGlobalData.maxCols * chunkGlobalData.maxRows)) * separation;
    pos[2] = ((i / chunkGlobalData.maxCols) % chunkGlobalData.maxRows) * separation;
    chunkGlobalData.drawables.at(i)->setPosition(pos);
    //printf("%f, %f, %f\n", chunkGlobalData.drawables.at(i)->positionX(), chunkGlobalData.drawables.at(i)->positionY(), chunkGlobalData.drawables.at(i)->positionZ());
  }
}

void ROTOM::Chunk::setRows(unsigned int rows) {
  chunkGlobalData.rows = rows;
}

void ROTOM::Chunk::setCols(unsigned int cols) {
  chunkGlobalData.cols = cols;
}

void ROTOM::Chunk::setMaxHeight(unsigned int maxHeight) {
  chunkGlobalData.maxHeight = maxHeight;
}

void ROTOM::Chunk::move(const float x, const float y, const float z) {
  for (unsigned int i = 0; i < chunkGlobalData.drawables.size(); ++i) {
    chunkGlobalData.drawables.at(i)->move(x, y, z);
  }
}

void ROTOM::Chunk::setParent(std::shared_ptr<Node> parent) {
  for (unsigned int i = 0; i < chunkGlobalData.drawables.size(); ++i) {
    chunkGlobalData.drawables.at(i)->setParent(parent);
  }
}