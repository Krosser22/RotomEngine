/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <vector>
#include <memory>

namespace ROTOM {
  class Geometry {
  public:
    Geometry();
    ~Geometry();
    
    struct GeometryData {
      std::vector<float> data;
      std::vector<int> index;
    };
    
    //Vertex = p, p, p, n, n, n, uv, uv, ... and again till end
    void loadGeometry(float *vertex, int *index, const int vertexCount);

    void loadGeometry(std::shared_ptr<Geometry::GeometryData> *geometryData);
    
    const unsigned int vertexCount();

    const unsigned int VAO();

    void getBoundingBox(struct aiVector3D* min, struct aiVector3D* max);

  private:
    unsigned int numberOfElementsPerVertex_ = 8; //3 = Only positions, 6 = positions and normals, 8 = positions, normals and UV
    unsigned int vertexCount_;
    unsigned int VBO_, VAO_, EBO_;
  };
}

#endif //__GEOMETRY_H__