/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "geometry.h"

#include "gl.h"
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

unsigned int index[36] = {
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
  ROTOM::SECURITY::addSecurityCount(ROTOM::SECURITY::MyClass::MyClass_Geometry);

  loadGeometry(vertex, index, 36);
}

ROTOM::Geometry::~Geometry() {
  ROTOM::SECURITY::removeSecurityCount(ROTOM::SECURITY::MyClass::MyClass_Geometry);

  // Properly de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &VAO_);
  glDeleteBuffers(1, &EBO_);
  glDeleteBuffers(1, &VBO_);
}

void ROTOM::Geometry::loadGeometry(const float *vertex, const unsigned int *index, const int vertexCount) {
  vertexCount_ = vertexCount;

  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);
  glGenBuffers(1, &EBO_);

  glBindVertexArray(VAO_); // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).

  int fNumberOfElementsPerVertex = sizeof(GLfloat) * numberOfElementsPerVertex_;
  //Vertex
  glBindBuffer(GL_ARRAY_BUFFER, VBO_); //Bind the buffer to the GL_ARRAY_BUFFER target
  glBufferData(GL_ARRAY_BUFFER, fNumberOfElementsPerVertex * vertexCount_, vertex, GL_STATIC_DRAW); //Copies the previously defined vertex data into the buffer's memory

  //Index
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * vertexCount_, index, GL_STATIC_DRAW);

  //Position attribute
  int numberOfPositions = 3;
  glVertexAttribPointer(0, numberOfPositions, GL_FLOAT, GL_FALSE, fNumberOfElementsPerVertex, (GLvoid*)0);
  glEnableVertexAttribArray(0);

  //Normal attribute
  int numberOfNormals = 3;
  glVertexAttribPointer(1, numberOfNormals, GL_FLOAT, GL_FALSE, fNumberOfElementsPerVertex, (GLvoid*)(numberOfPositions * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
  
  //UV attribute
  int numberOfUVs = 2;
  glVertexAttribPointer(2, numberOfUVs, GL_FLOAT, GL_FALSE, fNumberOfElementsPerVertex, (GLvoid*)((numberOfPositions + numberOfNormals) * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
  glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void ROTOM::Geometry::loadGeometry(std::shared_ptr<ROTOM::Geometry::GeometryData> *geometryData) {
  vertexCount_ = geometryData->get()->index.size();

  if (vertexCount_ <= 0) {
    printf("ERROR: loadGreometry() geometryData is NULL\n");
  } else {
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    glBindVertexArray(VAO_); // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).

    int fNumberOfElementsPerVertex = sizeof(GLfloat) * numberOfElementsPerVertex_;
    //Vertex
    glBindBuffer(GL_ARRAY_BUFFER, VBO_); //Bind the buffer to the GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, fNumberOfElementsPerVertex * vertexCount_, &geometryData->get()->data[0], GL_STATIC_DRAW); //Copies the previously defined vertex data into the buffer's memory

    //Index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * vertexCount_, &geometryData->get()->index[0], GL_STATIC_DRAW);

    //Position attribute
    int numberOfPositions = 3;
    glVertexAttribPointer(0, numberOfPositions, GL_FLOAT, GL_FALSE, fNumberOfElementsPerVertex, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //Normal attribute
    int numberOfNormals = 3;
    glVertexAttribPointer(1, numberOfNormals, GL_FLOAT, GL_FALSE, fNumberOfElementsPerVertex, (GLvoid*)(numberOfPositions * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //UV attribute
    int numberOfUVs = 2;
    glVertexAttribPointer(2, numberOfUVs, GL_FLOAT, GL_FALSE, fNumberOfElementsPerVertex, (GLvoid*)((numberOfPositions + numberOfNormals) * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
  }
}

const unsigned int ROTOM::Geometry::vertexCount() {
  return vertexCount_;
}

const unsigned int ROTOM::Geometry::VAO() {
  return VAO_;
}