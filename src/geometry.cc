/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "geometry.h"

#include "graphics.h"
#include "security.h"

//Default Square
float vertex[192] = {
  //----POSITIONS-----|------NORMALS-------|----UV----
  //Front side
  0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,   // Top Right
  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // Bottom Right
  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Bottom Left
  -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top Left 

  //Back side
  -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,  // Top Right
  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // Bottom Right
  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,  // Bottom Left
  0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,   // Top Left 
  
  //Left side
  -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // Top Right
  -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // Bottom Right
  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom Left
  -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // Top Left 

  //Righ side
  0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Top Right
  0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Bottom Right
  0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom Left
  0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // Top Left 

  //Top side
  0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Top Right
  0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // Bottom Right
  -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Bottom Left
  -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Top Left 

  //Bottom side
  0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,   // Top Right
  0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // Bottom Right
  -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // Bottom Left
  -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // Top Left 
};

int index[36] = {
  //Front side
  0, 1, 3,
  1, 2, 3,

  //Back side
  4, 5, 7,
  5, 6, 7,

  //Left side
  8, 9, 11,
  9, 10, 11,

  //Right side
  12, 13, 15,
  13, 14, 15,

  //Top side
  16, 17, 19,
  17, 18, 19,

  //Bottom side
  20, 21, 23,
  21, 22, 23,
};

ROTOM::Geometry::Geometry() {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_Geometry);

  vertexCount_ = 0;
  VBO_ = 0;
  VAO_ = 0;
  EBO_ = 0;

  loadGeometry(vertex, index, 36);
}

ROTOM::Geometry::~Geometry() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_Geometry);

  // Properly de-allocate all resources once they've outlived their purpose
  GRAPHICS::releaseGeometry(VAO_, EBO_, VBO_);
}

void ROTOM::Geometry::loadGeometry(float *vertex, int *index, const int vertexCount) {
  vertexCount_ = vertexCount;
  GRAPHICS::loadGeometry(&VAO_, &VBO_, &EBO_, sizeof(float) * numberOfElementsPerVertex_, vertexCount_, vertex, index);
}

void ROTOM::Geometry::loadGeometry(std::shared_ptr<ROTOM::Geometry::GeometryData> *geometryData) {
  loadGeometry(&geometryData->get()->data[0], &geometryData->get()->index[0], geometryData->get()->index.size());
}

const unsigned int ROTOM::Geometry::vertexCount() {
  return vertexCount_;
}

const unsigned int ROTOM::Geometry::VAO() {
  return VAO_;
}