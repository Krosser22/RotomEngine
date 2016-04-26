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
    rows = 128;
    cols = 128;
    maxHeight = 256;
  }
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

void ROTOM::Chunk::init(std::shared_ptr<Node> parent, unsigned int rows, unsigned int cols, unsigned int maxHeight) {
  chunkGlobalData.rows = rows;
  chunkGlobalData.cols = cols;
  chunkGlobalData.maxHeight = maxHeight;
  std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material());
  std::shared_ptr<MaterialSettings> materialSettings = std::shared_ptr<MaterialSettings>(new MaterialSettings());
  std::shared_ptr<Geometry> geometry = std::shared_ptr<Geometry>(new Geometry());

  const float separation = 1.0f;
  for (int i = 0; i < (float)chunkGlobalData.cols * chunkGlobalData.rows; ++i) {
    std::shared_ptr<Drawable> drawable = std::shared_ptr<Drawable>(new Drawable("Drawable"));
    chunkGlobalData.drawables.push_back(drawable);
    drawable->setParent(parent);
    drawable->setMaterial(material);
    drawable->setMaterialSettings(materialSettings);
    drawable->setGeometry(geometry);

    float pos[3] = { 0.0f, 0.0f, 0.0f };
    pos[0] = ((i / chunkGlobalData.cols) % chunkGlobalData.rows) * separation;
    pos[2] = (i % chunkGlobalData.cols) * separation;
    pos[1] = (i / (chunkGlobalData.cols * chunkGlobalData.rows)) * separation;
    drawable->setPosition(pos);
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