/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

namespace ROTOM {
  struct ShaderData { //TODO - Create a shader class
    unsigned int shaderProgram;
    unsigned int u_color;
    unsigned int u_model;
    unsigned int u_view;
    unsigned int u_projection;
    unsigned int u_lightPosition;
    unsigned int u_lightColor;
    unsigned int u_texture;
    unsigned int u_shininess;
    unsigned int u_specularIntensity;
    unsigned int u_specularMaterial;
  };

  static struct GeneralShaderData {
    float lightPositionX = 0.0f;
    float lightPositionY = 0.0f;
    float lightPositionZ = 0.0f;

    float lightColorX = 1.0f;
    float lightColorY = 1.0f;
    float lightColorZ = 1.0f;
  };
  static GeneralShaderData generalData;

  class Material {
  public:
    Material(const char *texturePath = "../../../../img/texture.png"); //TODO - change this path XD
    ~Material();

    //TODO - Move this to private and create functions to set/get the values
    ShaderData shaderData_;
    GeneralShaderData generalShaderData;
    float shininess_;
    float specularIntensity_[4];
    float specularMaterial_[4];

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
  };
}

#endif //__MATERIAL_H__