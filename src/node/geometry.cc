/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "node/geometry.h"
#include "render/graphics.h"

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
  vertexCount_ = 0;
  VBO_ = 0;
  VAO_ = 0;
  EBO_ = 0;

  loadGeometry(vertex, index, 36);
}

ROTOM::Geometry::~Geometry() {
  // Properly de-allocate all resources once they've outlived their purpose
  GRAPHICS::releaseGeometry(VAO_, EBO_, VBO_);
}

void ROTOM::Geometry::loadGeometry(float *vertex, int *index, const int vertexCount) {
  vertexCount_ = vertexCount;
  GRAPHICS::loadGeometry(&VAO_, &VBO_, &EBO_, sizeof(float) * numberOfElementsPerVertex_, vertexCount_, vertex, index);
}

void ROTOM::Geometry::loadGeometry(std::shared_ptr<ROTOM::Geometry::GeometryData> *geometryData) {
  loadGeometry(&geometryData->get()->data[0], &geometryData->get()->index[0], geometryData->get()->data.size() / 8);
}

const unsigned int ROTOM::Geometry::vertexCount() {
  return vertexCount_;
}

const unsigned int ROTOM::Geometry::VAO() {
  return VAO_;
}

//const struct aiScene* scene = NULL;
//GLuint scene_list = 0;
//struct aiVector3D scene_min, scene_max, scene_center;

/*void get_bounding_box_for_node(const struct aiNode* nd, struct aiVector3D* min, struct aiVector3D* max, struct aiMatrix4x4* trafo) {
  struct aiMatrix4x4 prev;
  unsigned int n = 0, t;

  prev = *trafo;
  aiMultiplyMatrix4(trafo, &nd->mTransformation);

  for (; n < nd->mNumMeshes; ++n) {
    const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
    for (t = 0; t < mesh->mNumVertices; ++t) {

      struct aiVector3D tmp = mesh->mVertices[t];
      aiTransformVecByMatrix4(&tmp, trafo);

      min->x = aisgl_min(min->x, tmp.x);
      min->y = aisgl_min(min->y, tmp.y);
      min->z = aisgl_min(min->z, tmp.z);

      max->x = aisgl_max(max->x, tmp.x);
      max->y = aisgl_max(max->y, tmp.y);
      max->z = aisgl_max(max->z, tmp.z);
    }
  }

  for (n = 0; n < nd->mNumChildren; ++n) {
    get_bounding_box_for_node(nd->mChildren[n], min, max, trafo);
  }
  *trafo = prev;
}*/

void ROTOM::Geometry::getBoundingBox(struct aiVector3D* min, struct aiVector3D* max) {
  /*struct aiMatrix4x4 trafo;
  aiIdentityMatrix4(&trafo);

  min->x = min->y = min->z = 1e10f;
  max->x = max->y = max->z = -1e10f;
  get_bounding_box_for_node(scene->mRootNode, min, max, &trafo);*/
}