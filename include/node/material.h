/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

namespace ROTOM {
  struct ShaderData {
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
    unsigned int u_ambientStrength;
    unsigned int u_eyePosition;
    unsigned int u_lightSpaceMatrix;
  };

  struct MaterialData {
    float shininess;
    float specularMaterial[3];
    float ambientStrength;
  };

  class Material {
  public:
    Material(const char *texturePath = "../../../../img/texture.png");
    ~Material();

    ShaderData shaderData_;
    MaterialData materialData_;

    unsigned int texture_;

    void setShader(const char *vertexShaderSource, const char *fragmentShaderSource);
    void setShaderFromPath(const char *vertexShaderPath, const char *fragmentShaderPath);

    //Set the texture of the object
    void setTexture(unsigned char *texture);
    void setTextureFromPath(const char *path);
    const unsigned int texture();

    //Return the width and the height of a texture
    void textureSize(int &width, int &height);

  private:
    int textureWidth_;
    int textureHeight_;
  };
}

#endif //__MATERIAL_H__