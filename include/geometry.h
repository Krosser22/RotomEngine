/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <vector>
#include "scoped_ptr.h"

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
    void loadGeometry(const float *vertex, const unsigned int *index, const int vertexCount);

    void loadGeometry(EDK3::scoped_ptr<ROTOM::Geometry::GeometryData> *geometryData);
    
    const unsigned int vertexCount();

    const unsigned int VAO();

  private:
    unsigned int numberOfElementsPerVertex_ = 8; //3 = Only positions, 6 = positions and normals, 8 = positions, normals and UV
    unsigned int vertexCount_;
    unsigned int VBO_, VAO_, EBO_;
  };
}

#endif //__GEOMETRY_H__