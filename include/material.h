/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

namespace ROTOM {
  class Material {
  public:
    Material();
    Material(const char *texturePath);
    ~Material();

    //Build and compile the shader program
    void setShader(const char *vertexShaderSource, const char *fragmentShaderSource);

    //Set the color of the object (0.0f - 1.0f)
    void setColor(const float r, const float g, const float b, const float a = 1.0f);
    const float *color();

    //Set the texture of the object
    void setTexture(const char *texturePath);
    const unsigned int texture();

    //Return the width and the height of a texture
    void textureSize(int &width, int &height);

    const unsigned int shaderProgram();

  private:
    float color_[4];
    unsigned int texture_;
    int textureWidth_;
    int textureHeight_;
    unsigned int shaderProgram_;
  };
}

#endif //__MATERIAL_H__