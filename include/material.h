/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "materialSettings.h"

namespace ROTOM {
  class Material {
  public:
    Material(const char *texturePath = "../../../../img/texture.png"); //TODO - change this path XD
    ~Material();

    float shininess_;
    float specularMaterial_[4];

    void setShader(MaterialSettings *materialSettings, const char *vertexShaderSource, const char *fragmentShaderSource);

    //Set the texture of the object
    void setTexture(const char *texturePath);
    const unsigned int texture();

    //Return the width and the height of a texture
    void textureSize(int &width, int &height);

  private:
    unsigned int texture_;
    int textureWidth_;
    int textureHeight_;
  };
}

#endif //__MATERIAL_H__